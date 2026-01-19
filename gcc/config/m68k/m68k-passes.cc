/* RTL optimization passes for Motorola 68k.
   Copyright (C) 2025 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GCC is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

#define IN_TARGET_CODE 1

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "target.h"
#include "rtl.h"
#include "tree.h"
#include "df.h"
#include "memmodel.h"
#include "tm_p.h"
#include "insn-config.h"
#include "regs.h"
#include "emit-rtl.h"
#include "recog.h"
#include "cfgrtl.h"
#include "context.h"
#include "tree-pass.h"

namespace {

/* Get the next NONDEBUG_INSN_P after INSN in basic block BB.  */

static rtx_insn *
next_nondebug_insn_bb (basic_block bb, rtx_insn *insn)
{
  while (insn)
    {
      insn = NEXT_INSN (insn);
      if (insn && NONDEBUG_INSN_P (insn))
	return BLOCK_FOR_INSN (insn) == bb ? insn : nullptr;
    }
  return nullptr;
}

/* Check if RTX is a MEM with a simple register address (no offset).  */

static bool
mem_reg_p (rtx x, int *pregno)
{
  if (MEM_P (x) && REG_P (XEXP (x, 0)))
    {
      *pregno = REGNO (XEXP (x, 0));
      return true;
    }
  return false;
}

/* Check if RTX is a MEM with (plus (reg) (const_int)) address.
   Returns the offset and register number.  */

static bool
mem_reg_offset_p (rtx x, int *pregno, HOST_WIDE_INT *poffset)
{
  if (MEM_P (x))
    {
      rtx addr = XEXP (x, 0);
      if (GET_CODE (addr) == PLUS
	  && REG_P (XEXP (addr, 0))
	  && CONST_INT_P (XEXP (addr, 1)))
	{
	  *pregno = REGNO (XEXP (addr, 0));
	  *poffset = INTVAL (XEXP (addr, 1));
	  return true;
	}
    }
  return false;
}

/* Check if INSN is a LEA or ADD that increments a register.
   Returns the register number and increment value.  */

static bool
is_reg_increment (rtx_insn *insn, int *pregno, HOST_WIDE_INT *pincr)
{
  rtx set = single_set (insn);
  if (!set)
    return false;

  rtx dest = SET_DEST (set);
  rtx src = SET_SRC (set);

  if (!REG_P (dest))
    return false;

  /* Check for: (set (reg) (plus (reg) (const_int)))  */
  if (GET_CODE (src) == PLUS
      && REG_P (XEXP (src, 0))
      && CONST_INT_P (XEXP (src, 1))
      && REGNO (dest) == REGNO (XEXP (src, 0)))
    {
      *pregno = REGNO (dest);
      *pincr = INTVAL (XEXP (src, 1));
      return true;
    }

  return false;
}

/* Update a memory operand's offset in place.  Returns true on success.  */

static bool
update_mem_offset_inplace (rtx *mem_loc, int regno, HOST_WIDE_INT new_offset)
{
  rtx old_mem = *mem_loc;
  if (!MEM_P (old_mem))
    return false;

  rtx addr = XEXP (old_mem, 0);

  /* Check if this MEM uses the target register with an offset.  */
  if (GET_CODE (addr) != PLUS
      || !REG_P (XEXP (addr, 0))
      || REGNO (XEXP (addr, 0)) != (unsigned) regno
      || !CONST_INT_P (XEXP (addr, 1)))
    return false;

  machine_mode mem_mode = GET_MODE (old_mem);
  rtx reg = gen_rtx_REG (Pmode, regno);

  rtx new_addr;
  if (new_offset == 0)
    new_addr = reg;
  else
    new_addr = gen_rtx_PLUS (Pmode, reg, GEN_INT (new_offset));

  rtx new_mem = gen_rtx_MEM (mem_mode, new_addr);
  MEM_COPY_ATTRIBUTES (new_mem, old_mem);
  *mem_loc = new_mem;
  return true;
}

/* Check if a MEM operand uses the given register with a negative offset.
   Returns the offset if found, or 0 if not.  */

static HOST_WIDE_INT
get_negative_offset (rtx mem, int regno)
{
  if (!MEM_P (mem))
    return 0;

  int mem_regno;
  HOST_WIDE_INT offset;
  if (mem_reg_offset_p (mem, &mem_regno, &offset)
      && mem_regno == regno && offset < 0)
    return offset;

  return 0;
}

/* Try to normalize increment position: move increment instructions that
   are followed by negative-offset memory accesses to after those accesses,
   adjusting the offsets to be positive.

   This transforms:
     move.w (%a0),(%a1)
     move.w 2(%a0),2(%a1)
     move.w 4(%a0),4(%a1)
     addq.l #8,%a0             ; increment in middle
     addq.l #8,%a1
     move.w -2(%a0),-2(%a1)    ; negative offset

   Into:
     move.w (%a0),(%a1)
     move.w 2(%a0),2(%a1)
     move.w 4(%a0),4(%a1)
     move.w 6(%a0),6(%a1)      ; -2 + 8 = 6
     addq.l #8,%a0             ; moved to end
     addq.l #8,%a1             ; moved to end

   Returns true if any transformation was made.  */

static bool
try_normalize_increment_position (basic_block bb, rtx_insn *add_insn,
				  int regno, HOST_WIDE_INT incr)
{
  /* Must be an address register (a0-a7 = regs 8-15).  */
  if (regno < 8 || regno > 15)
    return false;

  /* Only handle positive increments.  */
  if (incr <= 0)
    return false;

  /* Collect instructions with negative offsets that need adjustment.  */
  struct insn_to_fix {
    rtx_insn *insn;
    HOST_WIDE_INT src_offset;   /* 0 if src doesn't need fixing */
    HOST_WIDE_INT dest_offset;  /* 0 if dest doesn't need fixing */
  };
  auto_vec<insn_to_fix> fixups;
  rtx_insn *last_fixup_insn = nullptr;

  for (rtx_insn *insn = next_nondebug_insn_bb (bb, add_insn);
       insn;
       insn = next_nondebug_insn_bb (bb, insn))
    {
      rtx set = single_set (insn);
      if (!set)
	break;

      rtx src = SET_SRC (set);
      rtx dest = SET_DEST (set);

      HOST_WIDE_INT src_neg = get_negative_offset (src, regno);
      HOST_WIDE_INT dest_neg = get_negative_offset (dest, regno);

      if (src_neg < 0 || dest_neg < 0)
	{
	  insn_to_fix fix;
	  fix.insn = insn;
	  fix.src_offset = src_neg;
	  fix.dest_offset = dest_neg;
	  fixups.safe_push (fix);
	  last_fixup_insn = insn;
	  continue;
	}

      /* If the register is modified by another instruction, stop.  */
      if (reg_set_p (gen_rtx_REG (Pmode, regno), insn))
	break;

      /* If the register is used in some other way, stop.  */
      if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), PATTERN (insn)))
	break;
    }

  if (fixups.is_empty ())
    return false;

  /* Verify all negative offsets can be adjusted to valid positive offsets.  */
  for (const insn_to_fix &fix : fixups)
    {
      if (fix.src_offset < 0)
	{
	  HOST_WIDE_INT new_off = fix.src_offset + incr;
	  if (new_off < 0 || new_off > 32767)
	    return false;
	}
      if (fix.dest_offset < 0)
	{
	  HOST_WIDE_INT new_off = fix.dest_offset + incr;
	  if (new_off < 0 || new_off > 32767)
	    return false;
	}
    }

  /* Perform the transformation: adjust offsets.  */
  for (const insn_to_fix &fix : fixups)
    {
      rtx set = single_set (fix.insn);

      if (fix.src_offset < 0)
	{
	  HOST_WIDE_INT new_offset = fix.src_offset + incr;
	  update_mem_offset_inplace (&SET_SRC (set), regno, new_offset);
	}
      if (fix.dest_offset < 0)
	{
	  HOST_WIDE_INT new_offset = fix.dest_offset + incr;
	  update_mem_offset_inplace (&SET_DEST (set), regno, new_offset);
	}

      /* Validate the transformed instruction.  */
      INSN_CODE (fix.insn) = -1;
      if (recog_memoized (fix.insn) < 0)
	return false;
    }

  /* Move the increment instruction to after the last fixup instruction.  */
  remove_insn (add_insn);
  add_insn_after (add_insn, last_fixup_insn, bb);

  return true;
}

/* Try to convert a memory access and subsequent offset accesses to POST_INC.
   Returns true if any transformation was made.  */

static bool
try_convert_to_postinc (basic_block bb, rtx_insn *first_insn,
			rtx mem, int is_dest)
{
  int regno;
  if (!mem_reg_p (mem, &regno))
    return false;

  /* Must be an address register (a0-a7 = regs 8-15).  */
  if (regno < 8 || regno > 15)
    return false;

  machine_mode mode = GET_MODE (mem);
  int size = GET_MODE_SIZE (mode);

  /* Collect instructions that need offset adjustment.  */
  auto_vec<rtx_insn *> fixup_insns;
  rtx_insn *add_insn = nullptr;
  HOST_WIDE_INT expected_offset = size;

  for (rtx_insn *insn = next_nondebug_insn_bb (bb, first_insn);
       insn;
       insn = next_nondebug_insn_bb (bb, insn))
    {
      rtx set = single_set (insn);
      if (!set)
	break;

      rtx dest = SET_DEST (set);
      rtx src = SET_SRC (set);

      /* Check for LEA/ADD that increments our register.  */
      int inc_regno;
      HOST_WIDE_INT incr;
      if (is_reg_increment (insn, &inc_regno, &incr) && inc_regno == regno)
	{
	  if (incr >= size)
	    {
	      add_insn = insn;
	      break;
	    }
	  return false;  /* Increment too small.  */
	}

      /* Check for memory access using our register with expected offset.  */
      int mem_regno;
      HOST_WIDE_INT offset;

      /* Check if register is used in BOTH src and dest - can't handle that
	 case since we'd need to update both operands consistently.  */
      bool src_uses_reg = reg_mentioned_p (gen_rtx_REG (Pmode, regno), src);
      bool dest_uses_reg = reg_mentioned_p (gen_rtx_REG (Pmode, regno), dest);
      if (src_uses_reg && dest_uses_reg)
	return false;

      /* Check source operand.  */
      if (MEM_P (src))
	{
	  if (mem_reg_offset_p (src, &mem_regno, &offset)
	      && mem_regno == regno)
	    {
	      if (offset != expected_offset)
		return false;  /* Offset doesn't match expected sequence.  */
	      fixup_insns.safe_push (insn);
	      expected_offset += size;
	      continue;
	    }
	  else if (mem_reg_p (src, &mem_regno) && mem_regno == regno)
	    {
	      /* Another zero-offset access - can't handle.  */
	      return false;
	    }
	}

      /* Check destination operand.  */
      if (MEM_P (dest))
	{
	  if (mem_reg_offset_p (dest, &mem_regno, &offset)
	      && mem_regno == regno)
	    {
	      if (offset != expected_offset)
		return false;
	      fixup_insns.safe_push (insn);
	      expected_offset += size;
	      continue;
	    }
	  else if (mem_reg_p (dest, &mem_regno) && mem_regno == regno)
	    {
	      return false;
	    }
	}

      /* If the register is used but not in a recognizable pattern, abort.  */
      if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), PATTERN (insn)))
	return false;
    }

  /* Need at least one fixup instruction.  */
  if (fixup_insns.is_empty ())
    return false;

  /* If no add instruction, only proceed if the register is dead
     at the end of the basic block (we can safely modify it).  */
  HOST_WIDE_INT add_incr = 0;
  if (add_insn)
    {
      /* Verify the add increment matches what we expect.  */
      int add_regno;
      if (!is_reg_increment (add_insn, &add_regno, &add_incr))
	return false;

      if (add_incr < expected_offset)
	return false;
    }
  else
    {
      /* No add instruction - check if register is dead.  */
      bitmap live_out = df_get_live_out (bb);
      if (bitmap_bit_p (live_out, regno))
	return false;  /* Register is live, can't safely modify it.  */

      /* Set add_incr to the expected offset so the transformation works.  */
      add_incr = expected_offset;
    }

  /* Now perform the transformation.  */

  /* 1. Convert first instruction to use POST_INC.  */
  rtx reg = gen_rtx_REG (Pmode, regno);
  rtx postinc_addr = gen_rtx_POST_INC (Pmode, reg);
  rtx postinc_mem = gen_rtx_MEM (mode, postinc_addr);
  MEM_COPY_ATTRIBUTES (postinc_mem, mem);

  rtx set = single_set (first_insn);
  if (is_dest)
    SET_DEST (set) = postinc_mem;
  else
    SET_SRC (set) = postinc_mem;

  /* Validate the transformed insn.  */
  INSN_CODE (first_insn) = -1;
  if (recog_memoized (first_insn) < 0)
    {
      /* Transformation not valid, restore original.  */
      if (is_dest)
	SET_DEST (set) = mem;
      else
	SET_SRC (set) = mem;
      INSN_CODE (first_insn) = -1;
      recog_memoized (first_insn);
      return false;
    }

  /* Add REG_INC note.  */
  add_reg_note (first_insn, REG_INC, reg);

  /* 2. Fix up subsequent instructions - reduce their offsets.  */
  HOST_WIDE_INT current_adj = size;
  for (rtx_insn *insn : fixup_insns)
    {
      rtx set = single_set (insn);

      /* Use is_dest to determine which operand to fix - we're processing
	 the same operand type (source vs dest) as the first instruction.  */
      rtx *mem_loc = is_dest ? &SET_DEST (set) : &SET_SRC (set);
      if (!MEM_P (*mem_loc))
	continue;

      rtx old_mem = *mem_loc;
      machine_mode mem_mode = GET_MODE (old_mem);
      int mem_size = GET_MODE_SIZE (mem_mode);

      /* Calculate new offset.  */
      int mem_regno;
      HOST_WIDE_INT old_offset;
      if (!mem_reg_offset_p (old_mem, &mem_regno, &old_offset))
	continue;

      HOST_WIDE_INT new_offset = old_offset - current_adj;

      /* Create new memory reference.  */
      rtx new_addr;
      if (new_offset == 0)
	{
	  /* Use POST_INC.  */
	  new_addr = gen_rtx_POST_INC (Pmode, reg);
	  current_adj += mem_size;
	}
      else
	{
	  /* Use offset addressing.  */
	  new_addr = gen_rtx_PLUS (Pmode, reg, GEN_INT (new_offset));
	}

      rtx new_mem = gen_rtx_MEM (mem_mode, new_addr);
      MEM_COPY_ATTRIBUTES (new_mem, old_mem);
      *mem_loc = new_mem;

      /* Validate.  */
      INSN_CODE (insn) = -1;
      if (recog_memoized (insn) < 0)
	{
	  /* Restore and abort.  */
	  *mem_loc = old_mem;
	  INSN_CODE (insn) = -1;
	  recog_memoized (insn);
	  return false;
	}

      if (new_offset == 0)
	add_reg_note (insn, REG_INC, reg);
    }

  /* 3. Adjust or delete the add instruction (if present).  */
  if (add_insn)
    {
      HOST_WIDE_INT remaining = add_incr - current_adj;
      if (remaining == 0)
	{
	  /* Delete the add instruction entirely.  */
	  SET_INSN_DELETED (add_insn);
	}
      else if (remaining > 0)
	{
	  /* Reduce the add value.  */
	  rtx set = single_set (add_insn);
	  rtx src = SET_SRC (set);
	  XEXP (src, 1) = GEN_INT (remaining);
	  INSN_CODE (add_insn) = -1;
	  recog_memoized (add_insn);
	}
    }

  return true;
}

/* Main function for the normalize_autoinc pass.

   This pass normalizes increment positions by moving increment instructions
   that are followed by negative-offset memory accesses to after those
   accesses, adjusting the offsets to be positive.

   This transforms:
     move.w (%a0),(%a1)
     move.w 2(%a0),2(%a1)
     move.w 4(%a0),4(%a1)
     addq.l #8,%a0             ; increment in middle
     addq.l #8,%a1
     move.w -2(%a0),-2(%a1)    ; negative offset

   Into:
     move.w (%a0),(%a1)
     move.w 2(%a0),2(%a1)
     move.w 4(%a0),4(%a1)
     move.w 6(%a0),6(%a1)      ; -2 + 8 = 6
     addq.l #8,%a0             ; moved to end
     addq.l #8,%a1             ; moved to end

   This enables subsequent passes (m68k-autoinc, peephole2) to convert
   all accesses to POST_INC addressing and merge adjacent word accesses
   into long accesses.  */

static unsigned int
m68k_normalize_autoinc (function *func)
{
  unsigned int changes = 0;
  bool made_changes;

  /* Repeat until no more changes are made, since moving one increment
     may expose opportunities for moving others.  */
  do
    {
      made_changes = false;
      basic_block bb;
      FOR_EACH_BB_FN (bb, func)
	{
	  rtx_insn *insn, *next;
	  for (insn = BB_HEAD (bb); insn != BB_END (bb); insn = next)
	    {
	      next = NEXT_INSN (insn);
	      if (!NONDEBUG_INSN_P (insn))
		continue;

	      int regno;
	      HOST_WIDE_INT incr;
	      if (is_reg_increment (insn, &regno, &incr))
		{
		  if (try_normalize_increment_position (bb, insn, regno, incr))
		    {
		      changes++;
		      made_changes = true;
		    }
		}
	    }
	  /* Also check the last instruction.  */
	  if (NONDEBUG_INSN_P (BB_END (bb)))
	    {
	      int regno;
	      HOST_WIDE_INT incr;
	      if (is_reg_increment (BB_END (bb), &regno, &incr))
		{
		  if (try_normalize_increment_position (bb, BB_END (bb), regno, incr))
		    {
		      changes++;
		      made_changes = true;
		    }
		}
	    }
	}
    }
  while (made_changes);

  return changes;
}

/* Main function for the opt_autoinc pass.  */

static unsigned int
m68k_opt_autoinc (function *func)
{
  unsigned int changes = 0;

  /* Convert memory accesses to POST_INC.  */
  basic_block bb;
  FOR_EACH_BB_FN (bb, func)
    {
      rtx_insn *insn;
      FOR_BB_INSNS (bb, insn)
	{
	  if (!NONDEBUG_INSN_P (insn))
	    continue;

	  rtx set = single_set (insn);
	  if (!set)
	    continue;

	  rtx dest = SET_DEST (set);
	  rtx src = SET_SRC (set);

	  /* Check source for memory with zero offset.  */
	  int regno;
	  if (MEM_P (src) && mem_reg_p (src, &regno))
	    {
	      if (try_convert_to_postinc (bb, insn, src, 0))
		changes++;
	    }

	  /* Check destination for memory with zero offset.  */
	  if (MEM_P (dest) && mem_reg_p (dest, &regno))
	    {
	      if (try_convert_to_postinc (bb, insn, dest, 1))
		changes++;
	    }
	}
    }

  return changes;
}

/* Pass data for m68k_pass_normalize_autoinc.  */

const pass_data m68k_pass_data_normalize_autoinc =
{
  RTL_PASS,		  /* type */
  "m68k-normalize-autoinc", /* name */
  OPTGROUP_NONE,	  /* optinfo_flags */
  TV_MACH_DEP,		  /* tv_id */
  0,			  /* properties_required */
  0,			  /* properties_provided */
  0,			  /* properties_destroyed */
  0,			  /* todo_flags_start */
  TODO_df_finish	  /* todo_flags_finish */
};

/* The pass class for normalize_autoinc.  */

class m68k_pass_normalize_autoinc : public rtl_opt_pass
{
public:
  m68k_pass_normalize_autoinc (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_normalize_autoinc, ctxt)
  {}

  unsigned int execute (function *func) final override
  {
    if (optimize)
      return m68k_normalize_autoinc (func);
    return 0;
  }

}; /* class m68k_pass_normalize_autoinc */

/* Pass data for m68k_pass_opt_autoinc.  */

const pass_data m68k_pass_data_opt_autoinc =
{
  RTL_PASS,	    /* type */
  "m68k-autoinc",   /* name */
  OPTGROUP_NONE,    /* optinfo_flags */
  TV_MACH_DEP,	    /* tv_id */
  0,		    /* properties_required */
  0,		    /* properties_provided */
  0,		    /* properties_destroyed */
  0,		    /* todo_flags_start */
  TODO_df_finish    /* todo_flags_finish */
};

/* The pass class for opt_autoinc.  */

class m68k_pass_opt_autoinc : public rtl_opt_pass
{
public:
  m68k_pass_opt_autoinc (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_opt_autoinc, ctxt)
  {}

  unsigned int execute (function *func) final override
  {
    if (optimize)
      return m68k_opt_autoinc (func);
    return 0;
  }

}; /* class m68k_pass_opt_autoinc */

} /* anonymous namespace */

/* Factory function for m68k_pass_normalize_autoinc.  */

rtl_opt_pass *
make_m68k_pass_normalize_autoinc (gcc::context *ctxt)
{
  return new m68k_pass_normalize_autoinc (ctxt);
}

/* Factory function for m68k_pass_opt_autoinc.  */

rtl_opt_pass *
make_m68k_pass_opt_autoinc (gcc::context *ctxt)
{
  return new m68k_pass_opt_autoinc (ctxt);
}
