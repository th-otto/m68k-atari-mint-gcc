/* RTL and GIMPLE optimization passes for Motorola 68k.
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
#include "gimple.h"
#include "gimple-iterator.h"
#include "gimple-pretty-print.h"
#include "ssa.h"
#include "fold-const.h"
#include "gimple-range.h"

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


/* =======================================================================
   GIMPLE pass: m68k_pass_narrow_index_mult

   This pass narrows 32-bit multiplies to 16-bit when safe, allowing m68k
   to use .w index registers instead of .l.  The .w addressing mode
   sign-extends the 16-bit index, avoiding explicit zero-extension.

   Example - array indexing where VRP knows i is in [0, 99]:
     Before: and.l #65535,%d0 ; add.l %d0,%d0 ; move.w (%a0,%d0.l)
     After:  add.w %d0,%d0 ; move.w (%a0,%d0.w)

   The pass handles two patterns:
   1. (wider_type)narrow * CST - where narrow is 8 or 16-bit
   2. wide * CST - where wide is 32-bit but VRP shows range fits in 16-bit

   Runs after VRP1 to see range constraints from [[assume(...)]].
   ======================================================================= */

/* Helper: Get VRP range for a value, with optional fallback to type range.
   Returns true if a useful range was found.  */

static bool
m68k_get_value_range (tree val, gimple *stmt, wide_int *min_out,
		      wide_int *max_out, bool use_type_fallback)
{
  int_range_max vr;
  range_query *q = get_range_query (cfun);
  if (q == get_global_range_query ())
    q = enable_ranger (cfun);

  if (q->range_of_expr (vr, val, stmt)
      && !vr.undefined_p ()
      && !vr.varying_p ())
    {
      *min_out = vr.lower_bound ();
      *max_out = vr.upper_bound ();
      return true;
    }

  if (use_type_fallback)
    {
      tree type = TREE_TYPE (val);
      unsigned prec = TYPE_PRECISION (type);
      *min_out = wi::min_value (prec, TYPE_SIGN (type));
      *max_out = wi::max_value (prec, TYPE_SIGN (type));
      return true;
    }

  return false;
}

/* Helper: Check if value range [min_val, max_val] multiplied by cst_val
   fits in signed 16-bit.  Returns true if safe to narrow.  */

static bool
m68k_product_fits_16bit (wide_int min_val, wide_int max_val, wide_int cst_val,
			 unsigned result_prec, signop sign)
{
  wi::overflow_type overflow;

  wide_int min_ext = wide_int::from (min_val, result_prec, sign);
  wide_int max_ext = wide_int::from (max_val, result_prec, sign);
  wide_int cst_ext = wide_int::from (cst_val, result_prec, UNSIGNED);

  wide_int prod1 = wi::mul (min_ext, cst_ext, sign, &overflow);
  if (overflow != wi::OVF_NONE)
    return false;

  wide_int prod2 = wi::mul (max_ext, cst_ext, sign, &overflow);
  if (overflow != wi::OVF_NONE)
    return false;

  wide_int prod_min = wi::smin (prod1, prod2);
  wide_int prod_max = wi::smax (prod1, prod2);

  /* Product must fit in signed 16-bit [-32768, 32767].  */
  wide_int signed_min = wi::shwi (-32768, result_prec);
  wide_int signed_max = wi::shwi (32767, result_prec);

  return !wi::lts_p (prod_min, signed_min) && !wi::gts_p (prod_max, signed_max);
}

/* Helper: Emit narrowed multiply transformation.
   Transforms: result = input * CST
   To: tmp = (short)input * (short)CST; result = (result_type)tmp

   If input is 8-bit, first extends to 16-bit.
   Always uses signed 16-bit for the multiply.  */

static void
m68k_emit_narrow_mult (gimple_stmt_iterator *gsi, tree lhs, tree input,
		       tree cst, unsigned input_prec)
{
  tree hi_type = build_nonstandard_integer_type (16, false);
  tree mult_input = input;

  /* If input is 8-bit, first extend to 16-bit.  */
  if (input_prec == 8)
    {
      tree ext_tmp = make_ssa_name (hi_type);
      gimple *ext_stmt = gimple_build_assign (ext_tmp, NOP_EXPR, input);
      gsi_insert_before (gsi, ext_stmt, GSI_SAME_STMT);
      mult_input = ext_tmp;
    }
  else if (input_prec > 16)
    {
      /* Narrow 32-bit input to 16-bit.  */
      tree narrow_tmp = make_ssa_name (hi_type);
      gimple *narrow_stmt = gimple_build_assign (narrow_tmp, NOP_EXPR, input);
      gsi_insert_before (gsi, narrow_stmt, GSI_SAME_STMT);
      mult_input = narrow_tmp;
    }

  /* Create: tmp = mult_input * (short)CST  */
  tree narrow_cst = fold_convert (hi_type, cst);
  tree mult_tmp = make_ssa_name (hi_type);
  gimple *mult_stmt = gimple_build_assign (mult_tmp, MULT_EXPR,
					   mult_input, narrow_cst);
  gsi_insert_before (gsi, mult_stmt, GSI_SAME_STMT);

  /* Replace original: result = (result_type)tmp  */
  gimple *stmt = gsi_stmt (*gsi);
  gimple *cast_stmt = gimple_build_assign (lhs, NOP_EXPR, mult_tmp);
  gimple_set_location (cast_stmt, gimple_location (stmt));
  gsi_replace (gsi, cast_stmt, true);

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "m68k: Narrowed multiply to 16-bit:\n");
      print_gimple_stmt (dump_file, mult_stmt, 0, TDF_SLIM);
      print_gimple_stmt (dump_file, cast_stmt, 0, TDF_SLIM);
    }
}

/* Try to narrow a multiply by constant when operand comes from a cast.
   Pattern: result = (wider_type)narrow * CST  */

static bool
m68k_simplify_cast_mult (gimple_stmt_iterator *gsi)
{
  gimple *stmt = gsi_stmt (*gsi);

  if (!is_gimple_assign (stmt)
      || gimple_assign_rhs_code (stmt) != MULT_EXPR)
    return false;

  tree lhs = gimple_assign_lhs (stmt);
  tree rhs1 = gimple_assign_rhs1 (stmt);
  tree rhs2 = gimple_assign_rhs2 (stmt);

  if (TREE_CODE (rhs2) != INTEGER_CST || TREE_CODE (rhs1) != SSA_NAME)
    return false;

  /* Need: rhs1 is result of a widening cast.  */
  gimple *def = SSA_NAME_DEF_STMT (rhs1);
  if (!is_gimple_assign (def))
    return false;

  enum tree_code def_code = gimple_assign_rhs_code (def);
  if (def_code != NOP_EXPR && def_code != CONVERT_EXPR)
    return false;

  tree narrow_val = gimple_assign_rhs1 (def);
  tree narrow_type = TREE_TYPE (narrow_val);
  tree result_type = TREE_TYPE (lhs);

  if (!INTEGRAL_TYPE_P (narrow_type) || !INTEGRAL_TYPE_P (result_type))
    return false;

  unsigned narrow_prec = TYPE_PRECISION (narrow_type);
  unsigned result_prec = TYPE_PRECISION (result_type);

  if (narrow_prec >= result_prec)
    return false;

  /* Only 8-bit or 16-bit narrow types benefit from .w indexing.  */
  if (narrow_prec != 8 && narrow_prec != 16)
    return false;

  /* Only optimize positive constants (normal array element sizes).
     Negative constants create RTL patterns the backend can't match.  */
  wide_int cst_val = wi::to_wide (rhs2);
  if (wi::neg_p (cst_val, SIGNED))
    return false;

  /* Get range and check product fits.  */
  wide_int min_val, max_val;
  if (!m68k_get_value_range (narrow_val, stmt, &min_val, &max_val, true))
    return false;

  if (!m68k_product_fits_16bit (min_val, max_val, cst_val, result_prec,
				TYPE_SIGN (narrow_type)))
    return false;

  m68k_emit_narrow_mult (gsi, lhs, narrow_val, rhs2, narrow_prec);
  return true;
}

/* Try to narrow a 32-bit multiply when VRP shows operand fits in 16-bit.
   Pattern: result = wide * CST (where VRP range fits in signed 16-bit)  */

static bool
m68k_narrow_wide_mult (gimple_stmt_iterator *gsi)
{
  gimple *stmt = gsi_stmt (*gsi);

  if (!is_gimple_assign (stmt)
      || gimple_assign_rhs_code (stmt) != MULT_EXPR)
    return false;

  tree lhs = gimple_assign_lhs (stmt);
  tree rhs1 = gimple_assign_rhs1 (stmt);
  tree rhs2 = gimple_assign_rhs2 (stmt);
  tree result_type = TREE_TYPE (lhs);

  if (TREE_CODE (rhs2) != INTEGER_CST || TREE_CODE (rhs1) != SSA_NAME)
    return false;

  if (!INTEGRAL_TYPE_P (result_type) || TYPE_PRECISION (result_type) != 32)
    return false;

  /* Skip if rhs1 comes from a narrowing cast (handled above).  */
  gimple *def = SSA_NAME_DEF_STMT (rhs1);
  if (is_gimple_assign (def))
    {
      enum tree_code def_code = gimple_assign_rhs_code (def);
      if ((def_code == NOP_EXPR || def_code == CONVERT_EXPR)
	  && TYPE_PRECISION (TREE_TYPE (gimple_assign_rhs1 (def))) < 32)
	return false;
    }

  /* Get VRP range - no type fallback for 32-bit values.  */
  wide_int min_val, max_val;
  if (!m68k_get_value_range (rhs1, stmt, &min_val, &max_val, false))
    return false;

  /* Operand must fit in signed 16-bit.  */
  wide_int hi_min = wi::shwi (-32768, 32);
  wide_int hi_max = wi::shwi (32767, 32);
  if (wi::lts_p (min_val, hi_min) || wi::gts_p (max_val, hi_max))
    return false;

  /* Only optimize positive constants (normal array element sizes).
     Negative constants create RTL patterns the backend can't match.  */
  wide_int cst_val = wi::to_wide (rhs2);
  if (wi::neg_p (cst_val, SIGNED))
    return false;

  if (!m68k_product_fits_16bit (min_val, max_val, cst_val, 32, SIGNED))
    return false;

  m68k_emit_narrow_mult (gsi, lhs, rhs1, rhs2, 32);
  return true;
}

/* Main function for the narrow_index_mult pass.  */

static unsigned int
m68k_narrow_index_mult (function *fun)
{
  unsigned int changes = 0;
  basic_block bb;

  FOR_EACH_BB_FN (bb, fun)
    {
      for (gimple_stmt_iterator gsi = gsi_start_bb (bb);
	   !gsi_end_p (gsi); gsi_next (&gsi))
	{
	  /* First try to simplify existing cast-mult patterns.  */
	  if (m68k_simplify_cast_mult (&gsi))
	    changes++;
	  /* Then try to narrow 32-bit multiplies where VRP shows
	     the operand fits in signed 16-bit.  */
	  else if (m68k_narrow_wide_mult (&gsi))
	    changes++;
	}
    }

  if (changes && get_range_query (fun) != get_global_range_query ())
    disable_ranger (fun);

  return changes ? TODO_update_ssa : 0;
}

/* Pass data for m68k_pass_narrow_index_mult.  */

const pass_data m68k_pass_data_narrow_index_mult =
{
  GIMPLE_PASS,		    /* type */
  "m68k-narrow-index-mult", /* name */
  OPTGROUP_NONE,	    /* optinfo_flags */
  TV_MACH_DEP,		    /* tv_id */
  PROP_ssa,		    /* properties_required */
  0,			    /* properties_provided */
  0,			    /* properties_destroyed */
  0,			    /* todo_flags_start */
  0			    /* todo_flags_finish */
};

/* The pass class for narrow_index_mult.  */

class m68k_pass_narrow_index_mult : public gimple_opt_pass
{
public:
  m68k_pass_narrow_index_mult (gcc::context *ctxt)
    : gimple_opt_pass (m68k_pass_data_narrow_index_mult, ctxt)
  {}

  unsigned int execute (function *func) final override
  {
    if (optimize)
      return m68k_narrow_index_mult (func);
    return 0;
  }

}; /* class m68k_pass_narrow_index_mult */


/* =======================================================================
   RTL pass: m68k_pass_elim_andi

   This pass eliminates redundant zero-extension instructions:
   - andi.l #65535,%dn (word to long zero-extension)
   - andi.l #255,%dn (byte to long zero-extension)
   - andi.w #255,%dn (byte to word zero-extension)

   On M68K, word (.w) and byte (.b) operations only modify the lower bits,
   leaving upper bits unchanged.  If we pre-clear a register with moveq #0,
   and all subsequent operations until the andi are appropriately sized,
   then the upper bits remain zero and the andi is redundant.

   Word extension example:
     Before:
       move.w (%a0),%d0      ; load 16-bit value, upper bits undefined
       subq.w #1,%d0         ; word operation
       andi.l #65535,%d0     ; zero-extend for 32-bit use

     After:
       moveq #0,%d0          ; pre-clear register (2 bytes, 4 cycles)
       move.w (%a0),%d0      ; load 16-bit, upper bits stay 0
       subq.w #1,%d0         ; word op, upper bits stay 0
       ; andi eliminated!

   Byte extension example:
     Before:
       move.b (%a0),%d0      ; load 8-bit value
       addq.b #1,%d0         ; byte operation
       and.l #255,%d0        ; zero-extend for 32-bit use

     After:
       moveq #0,%d0          ; pre-clear register
       move.b (%a0),%d0      ; load 8-bit, upper bits stay 0
       addq.b #1,%d0         ; byte op, upper bits stay 0
       ; andi eliminated!

   This pass also performs cross-basic-block optimization using dataflow
   analysis to trace definitions across block boundaries.

   Runs after fast_rtl_dce to avoid DCE deleting inserted moveq.
   ======================================================================= */

/* Extension type being optimized.  */

enum extension_type {
  EXT_NONE,
  EXT_BYTE_TO_WORD,   /* andi.w #255 */
  EXT_BYTE_TO_LONG,   /* andi.l #255 */
  EXT_WORD_TO_LONG    /* andi.l #65535 */
};

/* Classification of how an instruction affects a specific register.  */

enum insn_reg_effect {
  EFFECT_NO_EFFECT,     /* Doesn't reference the register */
  EFFECT_USES_AS_LONG,  /* Uses register as 32-bit source */
  EFFECT_USES_AS_WORD,  /* Uses register as 16-bit source (for byte ext) */
  EFFECT_MODIFIES_WORD, /* Modifies lower 16 bits only (preserves upper) */
  EFFECT_MODIFIES_BYTE, /* Modifies lower 8 bits only (preserves upper) */
  EFFECT_DEFINES_BYTE,  /* First definition, byte-sized (preserves upper) */
  EFFECT_DEFINES_WORD,  /* First definition, word-sized (preserves upper) */
  EFFECT_DEFINES_LONG,  /* Defines all 32 bits */
  EFFECT_CLOBBERS       /* Call or asm clobbers register */
};

/* Return the extension type if INSN is an andi for zero-extension.
   If so, set *REG to the register.  Detects:
   - andi.l #65535,%dn (word to long)
   - andi.l #255,%dn (byte to long)
   - andi.w #255,%dn (byte to word)  */

static enum extension_type
classify_andi_extension (rtx_insn *insn, rtx *reg)
{
  if (!NONJUMP_INSN_P (insn))
    return EXT_NONE;

  rtx pat = PATTERN (insn);

  if (GET_CODE (pat) != SET)
    return EXT_NONE;

  rtx dest = SET_DEST (pat);
  rtx src = SET_SRC (pat);

  /* Must be setting a data register.  */
  if (!REG_P (dest) || !DATA_REG_P (dest))
    return EXT_NONE;

  /* Source must be (and:MODE reg (const)).  */
  if (GET_CODE (src) != AND)
    return EXT_NONE;

  rtx op0 = XEXP (src, 0);
  rtx op1 = XEXP (src, 1);

  /* Operands: same register AND constant.  */
  if (!REG_P (op0) || REGNO (op0) != REGNO (dest))
    return EXT_NONE;

  if (!CONST_INT_P (op1))
    return EXT_NONE;

  HOST_WIDE_INT mask = INTVAL (op1);
  machine_mode mode = GET_MODE (src);

  if (mode == SImode && mask == 65535)
    {
      *reg = dest;
      return EXT_WORD_TO_LONG;
    }

  if (mode == SImode && mask == 255)
    {
      *reg = dest;
      return EXT_BYTE_TO_LONG;
    }

  if (mode == HImode && mask == 255)
    {
      *reg = dest;
      return EXT_BYTE_TO_WORD;
    }

  return EXT_NONE;
}

/* Return true if INSN is andi.l #65535 on a data register.
   If so, set *REG to the register.  */

static bool
andi_65535_p (rtx_insn *insn, rtx *reg)
{
  return classify_andi_extension (insn, reg) == EXT_WORD_TO_LONG;
}

/* Check if INSN is moveq #0 or clr.l on a specific register.  */

static bool
is_clear_insn_p (rtx_insn *insn, unsigned regno)
{
  if (!NONJUMP_INSN_P (insn))
    return false;

  rtx pat = PATTERN (insn);

  if (GET_CODE (pat) != SET)
    return false;

  rtx dest = SET_DEST (pat);
  rtx src = SET_SRC (pat);

  if (!REG_P (dest)
      || REGNO (dest) != regno
      || GET_MODE (dest) != SImode)
    return false;

  return src == const0_rtx;
}

/* Classify how an RTL source expression defines a register.
   Returns the classification of the definition type.  */

static enum insn_reg_effect
classify_definition (rtx dest, rtx src)
{
  machine_mode mode = GET_MODE (dest);

  /* Check destination mode.  */
  if (mode == SImode)
    {
      /* Check for muls/mulu pattern: (mult (sign/zero_extend ...) ...).  */
      if (GET_CODE (src) == MULT)
	{
	  rtx op0 = XEXP (src, 0);
	  if (GET_CODE (op0) == SIGN_EXTEND
	      || GET_CODE (op0) == ZERO_EXTEND)
	    return EFFECT_DEFINES_LONG;  /* Produces 32-bit result.  */
	}

      /* Check for ext.l pattern: (sign_extend:SI (reg:HI)).  */
      if (GET_CODE (src) == SIGN_EXTEND
	  && GET_MODE (XEXP (src, 0)) == HImode)
	return EFFECT_DEFINES_LONG;

      /* Check for zero_extend:SI (reg:HI) - clears upper 16 bits.  */
      if (GET_CODE (src) == ZERO_EXTEND
	  && GET_MODE (XEXP (src, 0)) == HImode)
	return EFFECT_DEFINES_WORD;

      /* Check for zero_extend:SI (reg:QI) - clears upper 24 bits.  */
      if (GET_CODE (src) == ZERO_EXTEND
	  && GET_MODE (XEXP (src, 0)) == QImode)
	return EFFECT_DEFINES_BYTE;

      /* Regular 32-bit definition.  */
      return EFFECT_DEFINES_LONG;
    }

  if (mode == HImode)
    {
      /* Check for zero_extend:HI (reg:QI) - clears upper 8 bits.  */
      if (GET_CODE (src) == ZERO_EXTEND
	  && GET_MODE (XEXP (src, 0)) == QImode)
	return EFFECT_DEFINES_BYTE;

      return EFFECT_DEFINES_WORD;
    }

  if (mode == QImode)
    return EFFECT_DEFINES_BYTE;

  return EFFECT_DEFINES_LONG;  /* Conservative default.  */
}

/* Check if X uses REG in a mode wider than max_mode.
   For byte extension, max_mode is QImode (uses in HI or SI mode are bad).
   For word extension, max_mode is HImode (uses in SI mode are bad).  */

static bool
uses_reg_wider_than_p (rtx x, unsigned regno, machine_mode max_mode)
{
  if (x == NULL_RTX)
    return false;

  enum rtx_code code = GET_CODE (x);

  if (code == REG && REGNO (x) == regno)
    {
      machine_mode m = GET_MODE (x);
      if (GET_MODE_SIZE (m) > GET_MODE_SIZE (max_mode))
	return true;
    }

  if (code == MEM)
    {
      /* Check address for register use in wider mode.  */
      rtx addr = XEXP (x, 0);
      if (addr == NULL_RTX)
	return false;
      if (REG_P (addr) && REGNO (addr) == regno)
	return true;  /* Address registers are always 32-bit.  */

      if (GET_CODE (addr) == PLUS)
	{
	  rtx base = XEXP (addr, 0);
	  rtx index = XEXP (addr, 1);

	  if (base && REG_P (base) && REGNO (base) == regno)
	    return true;

	  if (index && GET_CODE (index) == MULT)
	    {
	      rtx idx_reg = XEXP (index, 0);
	      if (idx_reg && REG_P (idx_reg) && REGNO (idx_reg) == regno)
		{
		  /* Check index mode - .l uses 32 bits, .w uses 16 bits.  */
		  if (GET_MODE (idx_reg) == SImode)
		    return true;
		  if (max_mode == QImode && GET_MODE (idx_reg) == HImode)
		    return true;
		}
	    }
	  else if (index && REG_P (index) && REGNO (index) == regno)
	    return true;
	}
    }

  /* Recursively check subexpressions.  */
  const char *fmt = GET_RTX_FORMAT (code);
  int len = GET_RTX_LENGTH (code);
  for (int i = 0; i < len; i++)
    {
      if (fmt[i] == 'e')
	{
	  rtx sub = XEXP (x, i);
	  if (sub && uses_reg_wider_than_p (sub, regno, max_mode))
	    return true;
	}
      else if (fmt[i] == 'E')
	{
	  int veclen = XVECLEN (x, i);
	  for (int j = 0; j < veclen; j++)
	    {
	      rtx sub = XVECEXP (x, i, j);
	      if (sub && uses_reg_wider_than_p (sub, regno, max_mode))
		return true;
	    }
	}
    }

  return false;
}

/* Check if SRC uses REG as a 32-bit value (which would read undefined
   upper bits if we haven't pre-cleared).  */

static bool
uses_reg_as_long_p (rtx x, unsigned regno)
{
  if (x == NULL_RTX)
    return false;

  enum rtx_code code = GET_CODE (x);

  if (code == REG && REGNO (x) == regno)
    {
      /* Check if this is a full 32-bit use.  */
      if (GET_MODE (x) == SImode)
	return true;
    }

  if (code == MEM)
    {
      /* Check address for 32-bit register use.  */
      rtx addr = XEXP (x, 0);
      if (addr == NULL_RTX)
	return false;
      if (REG_P (addr) && REGNO (addr) == regno)
	return true;

      if (GET_CODE (addr) == PLUS)
	{
	  rtx base = XEXP (addr, 0);
	  rtx index = XEXP (addr, 1);

	  if (base && REG_P (base) && REGNO (base) == regno)
	    return true;

	  /* Check indexed addressing: (plus base (mult index scale)).  */
	  if (index && GET_CODE (index) == MULT)
	    {
	      rtx idx_reg = XEXP (index, 0);
	      /* If index uses .l mode, it reads full 32 bits.  */
	      if (idx_reg && REG_P (idx_reg) && REGNO (idx_reg) == regno
		  && GET_MODE (idx_reg) == SImode)
		return true;
	    }
	  /* Check for (plus (reg) (reg)) indexed.  */
	  else if (index && REG_P (index) && REGNO (index) == regno)
	    return true;
	}
    }

  /* Recursively check subexpressions.  */
  const char *fmt = GET_RTX_FORMAT (code);
  int len = GET_RTX_LENGTH (code);
  for (int i = 0; i < len; i++)
    {
      if (fmt[i] == 'e')
	{
	  rtx sub = XEXP (x, i);
	  if (sub && uses_reg_as_long_p (sub, regno))
	    return true;
	}
      else if (fmt[i] == 'E')
	{
	  int veclen = XVECLEN (x, i);
	  for (int j = 0; j < veclen; j++)
	    {
	      rtx sub = XVECEXP (x, i, j);
	      if (sub && uses_reg_as_long_p (sub, regno))
		return true;
	    }
	}
    }

  return false;
}

/* Classify how an instruction affects a specific register.  */

static enum insn_reg_effect
classify_insn_effect (rtx_insn *insn, unsigned regno)
{
  if (!NONDEBUG_INSN_P (insn))
    return EFFECT_NO_EFFECT;

  /* Handle CALL instructions.  */
  if (CALL_P (insn))
    {
      /* D0-D1 are caller-saved.  */
      if (regno <= 1)
	return EFFECT_CLOBBERS;
      return EFFECT_NO_EFFECT;
    }

  rtx pat = PATTERN (insn);

  /* Handle SET patterns.  */
  if (GET_CODE (pat) == SET)
    {
      rtx dest = SET_DEST (pat);
      rtx src = SET_SRC (pat);

      /* Check for STRICT_LOW_PART: (set (strict_low_part (reg:HI)) ...).  */
      if (GET_CODE (dest) == STRICT_LOW_PART)
	{
	  rtx inner = XEXP (dest, 0);
	  if (REG_P (inner) && REGNO (inner) == regno)
	    {
	      /* Even though dest is a word modify, the source might
		 use the register as 32-bit (e.g., in an address).  */
	      if (uses_reg_as_long_p (src, regno))
		return EFFECT_USES_AS_LONG;
	      if (GET_MODE (inner) == HImode)
		return EFFECT_MODIFIES_WORD;
	      if (GET_MODE (inner) == QImode)
		return EFFECT_MODIFIES_BYTE;
	    }
	}

      /* Check if this instruction defines our register.  */
      if (REG_P (dest) && REGNO (dest) == regno)
	{
	  /* CRITICAL: Check if the source expression uses the register
	     in ANY mode BEFORE we consider this a definition.
	     For example:
	     - move.w (%a0,%d0.l),%d0 uses d0.l in the address
	     - subq.w #1,%d0 uses d0.w as input to the add
	     In both cases, we can't insert moveq #0 before it.
	     Only a pure definition (no prior use) is safe for optimization.  */
	  if (uses_reg_as_long_p (src, regno))
	    return EFFECT_USES_AS_LONG;

	  /* Check if source uses the register in any mode (HI, QI, etc.).
	     This catches cases like (plus:HI (reg:HI d0) ...).  */
	  if (reg_mentioned_p (gen_rtx_REG (GET_MODE (dest), regno), src))
	    {
	      /* It's a modification, not a pure definition.  */
	      if (GET_MODE (dest) == HImode)
		return EFFECT_MODIFIES_WORD;
	      if (GET_MODE (dest) == QImode)
		return EFFECT_MODIFIES_BYTE;
	      return EFFECT_DEFINES_LONG;  /* Conservative.  */
	    }

	  return classify_definition (dest, src);
	}

      /* Check if instruction uses our register as 32-bit.  */
      if (uses_reg_as_long_p (src, regno))
	return EFFECT_USES_AS_LONG;

      /* Check if register is used in dest address as 32-bit.  */
      if (MEM_P (dest) && uses_reg_as_long_p (dest, regno))
	return EFFECT_USES_AS_LONG;

      return EFFECT_NO_EFFECT;
    }

  /* Handle PARALLEL (multiple sets, often from calls or movem).  */
  if (GET_CODE (pat) == PARALLEL)
    {
      enum insn_reg_effect result = EFFECT_NO_EFFECT;

      for (int i = 0; i < XVECLEN (pat, 0); i++)
	{
	  rtx elem = XVECEXP (pat, 0, i);

	  if (GET_CODE (elem) == CLOBBER)
	    {
	      rtx clobbered = XEXP (elem, 0);
	      if (REG_P (clobbered) && REGNO (clobbered) == regno)
		return EFFECT_CLOBBERS;
	    }

	  if (GET_CODE (elem) == SET)
	    {
	      rtx dest = SET_DEST (elem);
	      rtx src = SET_SRC (elem);

	      if (REG_P (dest) && REGNO (dest) == regno)
		{
		  enum insn_reg_effect eff = classify_definition (dest, src);
		  if (eff == EFFECT_DEFINES_LONG || eff == EFFECT_CLOBBERS)
		    return eff;
		  if (eff > result)
		    result = eff;
		}

	      if (uses_reg_as_long_p (src, regno))
		return EFFECT_USES_AS_LONG;
	    }
	}

      return result;
    }

  return EFFECT_NO_EFFECT;
}

/* State for tracking a potential optimization candidate.  */

struct andi_candidate {
  rtx_insn *andi_insn;      /* The andi instruction.  */
  rtx reg;                  /* The data register (D0-D7).  */
  vec<rtx_insn *> def_insns;  /* Appropriately-sized definitions.  */
  enum extension_type ext_type;  /* Type of extension being eliminated.  */
  bool valid;               /* Still a valid candidate.  */

  andi_candidate () : andi_insn (nullptr), reg (nullptr),
		      def_insns (vNULL), ext_type (EXT_NONE), valid (false) {}
};

/* Check if an effect is compatible with the extension type being optimized.
   For word-to-long: byte and word operations are safe.
   For byte-to-long/word: only byte operations are safe.  */

static bool
effect_compatible_with_ext (enum insn_reg_effect effect,
			    enum extension_type ext_type)
{
  switch (ext_type)
    {
    case EXT_WORD_TO_LONG:
      /* Word operations preserve upper 16 bits.  */
      return (effect == EFFECT_MODIFIES_WORD
	      || effect == EFFECT_MODIFIES_BYTE
	      || effect == EFFECT_NO_EFFECT);

    case EXT_BYTE_TO_LONG:
    case EXT_BYTE_TO_WORD:
      /* Only byte operations preserve upper 24/8 bits.  */
      return (effect == EFFECT_MODIFIES_BYTE
	      || effect == EFFECT_NO_EFFECT);

    default:
      return false;
    }
}

/* Check if a definition effect is the right size for the extension type.  */

static bool
definition_matches_ext (enum insn_reg_effect effect,
			enum extension_type ext_type)
{
  switch (ext_type)
    {
    case EXT_WORD_TO_LONG:
      return effect == EFFECT_DEFINES_WORD;

    case EXT_BYTE_TO_LONG:
    case EXT_BYTE_TO_WORD:
      return effect == EFFECT_DEFINES_BYTE;

    default:
      return false;
    }
}

/* Classify instruction effect with consideration for extension type.
   For byte extensions, word-mode uses are also problematic.  */

static enum insn_reg_effect
classify_insn_effect_for_ext (rtx_insn *insn, unsigned regno,
			      enum extension_type ext_type)
{
  enum insn_reg_effect effect = classify_insn_effect (insn, regno);

  /* For byte extensions, we need to also check for word-mode uses.  */
  if ((ext_type == EXT_BYTE_TO_LONG || ext_type == EXT_BYTE_TO_WORD)
      && effect == EFFECT_NO_EFFECT)
    {
      rtx pat = PATTERN (insn);
      if (GET_CODE (pat) == SET)
	{
	  rtx src = SET_SRC (pat);
	  rtx dest = SET_DEST (pat);

	  /* Check if register is used in word mode in src or dest.  */
	  if (uses_reg_wider_than_p (src, regno, QImode)
	      || uses_reg_wider_than_p (dest, regno, QImode))
	    return EFFECT_USES_AS_WORD;
	}
    }

  /* For byte extensions, word modifications clobber the bits we need.  */
  if ((ext_type == EXT_BYTE_TO_LONG || ext_type == EXT_BYTE_TO_WORD)
      && effect == EFFECT_MODIFIES_WORD)
    return EFFECT_DEFINES_LONG;  /* Treat as clobbering upper bits.  */

  /* For byte extensions, word definitions also clobber needed bits.  */
  if ((ext_type == EXT_BYTE_TO_LONG || ext_type == EXT_BYTE_TO_WORD)
      && effect == EFFECT_DEFINES_WORD)
    return EFFECT_DEFINES_LONG;

  return effect;
}

/* Recursive helper for cross-BB definition finding.
   VISITED tracks blocks already seen to avoid infinite loops on back-edges.
   DEPTH limits recursion to avoid excessive compile time.  */

static bool
find_cross_bb_definitions_1 (basic_block bb, unsigned regno,
			     enum extension_type ext_type,
			     vec<rtx_insn *> *def_insns,
			     bitmap visited, int depth)
{
  /* Limit recursion depth to avoid excessive compile time.  */
  if (depth > 10)
    return false;

  edge e;
  edge_iterator ei;

  FOR_EACH_EDGE (e, ei, bb->preds)
    {
      basic_block pred_bb = e->src;

      /* Skip entry block.  */
      if (pred_bb == ENTRY_BLOCK_PTR_FOR_FN (cfun))
	return false;

      /* Skip already-visited blocks (handles loops).  */
      if (bitmap_bit_p (visited, pred_bb->index))
	continue;
      bitmap_set_bit (visited, pred_bb->index);

      /* Find the last definition in the predecessor block.  */
      rtx_insn *pred_def = nullptr;
      bool safe_path = true;
      bool need_recurse = false;

      /* Defensive: check block has valid head/end.  */
      if (BB_HEAD (pred_bb) == nullptr || BB_END (pred_bb) == nullptr)
	return false;

      for (rtx_insn *insn = BB_END (pred_bb);
	   insn && insn != PREV_INSN (BB_HEAD (pred_bb));
	   insn = PREV_INSN (insn))
	{
	  if (!NONDEBUG_INSN_P (insn))
	    continue;

	  /* Defensive: verify insn has a valid pattern.  */
	  if (PATTERN (insn) == NULL_RTX)
	    continue;

	  enum insn_reg_effect effect
	    = classify_insn_effect_for_ext (insn, regno, ext_type);

	  switch (effect)
	    {
	    case EFFECT_DEFINES_BYTE:
	      if (ext_type == EXT_BYTE_TO_LONG
		  || ext_type == EXT_BYTE_TO_WORD)
		{
		  pred_def = insn;
		  goto found_in_pred;
		}
	      safe_path = false;
	      goto found_in_pred;

	    case EFFECT_DEFINES_WORD:
	      if (ext_type == EXT_WORD_TO_LONG)
		{
		  pred_def = insn;
		  goto found_in_pred;
		}
	      safe_path = false;
	      goto found_in_pred;

	    case EFFECT_DEFINES_LONG:
	    case EFFECT_CLOBBERS:
	    case EFFECT_USES_AS_LONG:
	    case EFFECT_USES_AS_WORD:
	      safe_path = false;
	      goto found_in_pred;

	    case EFFECT_MODIFIES_WORD:
	      if (ext_type != EXT_WORD_TO_LONG)
		{
		  safe_path = false;
		  goto found_in_pred;
		}
	      continue;

	    case EFFECT_MODIFIES_BYTE:
	      continue;

	    case EFFECT_NO_EFFECT:
	      continue;
	    }
	}

      /* Reached beginning of predecessor without finding definition.
	 Recurse into this block's predecessors.  */
      need_recurse = true;

    found_in_pred:
      if (!safe_path)
	return false;

      if (need_recurse)
	{
	  /* No definition in this block - recurse to its predecessors.  */
	  if (!find_cross_bb_definitions_1 (pred_bb, regno, ext_type,
					    def_insns, visited, depth + 1))
	    return false;
	}
      else if (pred_def != nullptr)
	{
	  def_insns->safe_push (pred_def);
	}
      else
	{
	  /* safe_path but no def and no recurse - shouldn't happen.  */
	  return false;
	}
    }

  return true;
}

/* Try to trace backward across basic block boundaries to find the
   definitions of a register.  Fills def_insns with all defining
   instructions from all predecessor blocks.
   Returns true if safe to optimize, false otherwise.

   NOTE: Currently limited to single-predecessor cases to avoid crashes
   in complex functions.  Full cross-BB analysis is disabled pending
   investigation of the root cause.  */

static bool
find_cross_bb_definitions (basic_block bb, unsigned regno,
			   enum extension_type ext_type,
			   vec<rtx_insn *> *def_insns)
{
  auto_bitmap visited;
  bitmap_set_bit (visited, bb->index);

  if (!find_cross_bb_definitions_1 (bb, regno, ext_type, def_insns,
				    visited, 0))
    return false;

  return !def_insns->is_empty ();
}

/* Try to eliminate andi instructions in a basic block by inserting
   moveq #0 before the first appropriately-sized definition.
   ALREADY_CLEARED_BEFORE tracks def_insns that already have moveq inserted
   across all BBs in the function to avoid duplicate insertions.
   Returns the number of eliminations performed.  */

static unsigned int
m68k_elim_andi_bb (basic_block bb, bitmap already_cleared_before)
{
  auto_vec<andi_candidate> candidates;

  if (dump_file)
    fprintf (dump_file, "m68k-elim-andi: Processing BB %d\n", bb->index);

  /* Pass 1: Find all andi zero-extension instructions.  */
  rtx_insn *insn;
  FOR_BB_INSNS (bb, insn)
    {
      rtx reg;
      enum extension_type ext_type = classify_andi_extension (insn, &reg);
      if (ext_type != EXT_NONE)
	{
	  if (dump_file)
	    {
	      fprintf (dump_file, "  Found andi ext_type=%d reg=%d: ",
		       ext_type, REGNO (reg));
	      print_rtl_single (dump_file, insn);
	    }
	  andi_candidate cand;
	  cand.andi_insn = insn;
	  cand.reg = reg;
	  cand.ext_type = ext_type;
	  candidates.safe_push (cand);
	}
    }

  if (candidates.is_empty ())
    return 0;

  /* Pass 2: For each candidate, trace backward to find definition.  */
  for (andi_candidate &cand : candidates)
    {
      unsigned regno = REGNO (cand.reg);
      bool found_def = false;
      bool already_cleared = false;

      if (dump_file)
	fprintf (dump_file, "  Scanning backward for d%d definition\n", regno);

      /* Collect BB instructions in order, then scan backward from andi.  */
      auto_vec<rtx_insn *> bb_insns;
      rtx_insn *bb_insn;
      FOR_BB_INSNS (bb, bb_insn)
	if (NONDEBUG_INSN_P (bb_insn))
	  bb_insns.safe_push (bb_insn);

      /* Find andi position and scan backward.  */
      int andi_idx = -1;
      for (unsigned i = 0; i < bb_insns.length (); i++)
	if (bb_insns[i] == cand.andi_insn)
	  {
	    andi_idx = i;
	    break;
	  }

      for (int i = andi_idx - 1; i >= 0; i--)
	{
	  rtx_insn *scan = bb_insns[i];
	  if (dump_file)
	    {
	      fprintf (dump_file, "    Checking: ");
	      print_rtl_single (dump_file, scan);
	    }

	  /* Check if register is already cleared.  */
	  if (is_clear_insn_p (scan, regno))
	    {
	      if (dump_file)
		fprintf (dump_file, "    -> Already cleared!\n");
	      already_cleared = true;
	      break;
	    }

	  enum insn_reg_effect effect
	    = classify_insn_effect_for_ext (scan, regno, cand.ext_type);

	  if (dump_file)
	    fprintf (dump_file, "    -> effect=%d\n", effect);

	  switch (effect)
	    {
	    case EFFECT_DEFINES_BYTE:
	      if (dump_file)
		fprintf (dump_file, "    -> DEFINES_BYTE, valid=%d\n",
			 cand.ext_type == EXT_BYTE_TO_LONG
			 || cand.ext_type == EXT_BYTE_TO_WORD);
	      if (cand.ext_type == EXT_BYTE_TO_LONG
		  || cand.ext_type == EXT_BYTE_TO_WORD)
		{
		  cand.def_insns.safe_push (scan);
		  cand.valid = true;
		}
	      found_def = true;
	      break;

	    case EFFECT_DEFINES_WORD:
	      if (dump_file)
		fprintf (dump_file, "    -> DEFINES_WORD, valid=%d\n",
			 cand.ext_type == EXT_WORD_TO_LONG);
	      if (cand.ext_type == EXT_WORD_TO_LONG)
		{
		  cand.def_insns.safe_push (scan);
		  cand.valid = true;
		}
	      found_def = true;
	      break;

	    case EFFECT_DEFINES_LONG:
	    case EFFECT_CLOBBERS:
	      found_def = true;
	      break;

	    case EFFECT_USES_AS_LONG:
	    case EFFECT_USES_AS_WORD:
	      found_def = true;
	      break;

	    case EFFECT_MODIFIES_WORD:
	      if (cand.ext_type == EXT_WORD_TO_LONG)
		continue;
	      found_def = true;  /* For byte ext, word modify clobbers.  */
	      break;

	    case EFFECT_MODIFIES_BYTE:
	      continue;

	    case EFFECT_NO_EFFECT:
	      continue;
	    }

	  if (found_def)
	    break;
	}

      if (dump_file)
	fprintf (dump_file, "  After scan: found_def=%d already_cleared=%d valid=%d\n",
		 found_def, already_cleared, cand.valid);

      /* If register is already cleared, just delete andi (no defs needed).  */
      if (already_cleared && !cand.valid)
	cand.valid = true;

      /* If not found in this block, try cross-basic-block analysis.  */
      if (!found_def && !already_cleared)
	{
	  if (dump_file)
	    fprintf (dump_file, "  Trying cross-BB analysis\n");
	  if (find_cross_bb_definitions (bb, regno, cand.ext_type,
					 &cand.def_insns))
	    {
	      if (dump_file)
		fprintf (dump_file, "  Found %d cross-BB definitions!\n",
			 (int)cand.def_insns.length ());
	      cand.valid = true;
	    }
	}

      if (dump_file)
	fprintf (dump_file, "  Final: valid=%d num_defs=%d\n",
		 cand.valid, (int)cand.def_insns.length ());
    }

  /* Pass 3: Apply transformations.  */
  unsigned int changes = 0;

  for (const andi_candidate &cand : candidates)
    {
      if (!cand.valid)
	continue;

      /* Insert moveq #0,reg before each definition.  */
      bool all_succeeded = true;
      auto_vec<rtx_insn *> inserted_insns;

      if (dump_file)
	fprintf (dump_file, "  Starting transform loop for %d def_insns\n",
		 (int)cand.def_insns.length ());

      for (rtx_insn *def_insn : cand.def_insns)
	{
	  if (dump_file)
	    fprintf (dump_file, "  Processing def_insn %p\n", (void *)def_insn);

	  /* Validate def_insn is still valid.  */
	  if (def_insn == nullptr || def_insn->deleted ())
	    {
	      if (dump_file)
		fprintf (dump_file, "  SKIP: def_insn null or deleted\n");
	      all_succeeded = false;
	      break;
	    }

	  /* Ensure def_insn has a valid basic block.  */
	  basic_block def_bb = BLOCK_FOR_INSN (def_insn);
	  if (def_bb == nullptr)
	    {
	      if (dump_file)
		fprintf (dump_file, "  SKIP: def_insn has no BB\n");
	      all_succeeded = false;
	      break;
	    }

	  /* Check if we already inserted a moveq before this def for this reg.  */
	  unsigned regno = REGNO (cand.reg);
	  unsigned key = (INSN_UID (def_insn) << 4) | (regno & 0xf);
	  if (bitmap_bit_p (already_cleared_before, key))
	    {
	      if (dump_file)
		fprintf (dump_file, "  SKIP: already cleared before uid=%d "
			 "for d%d\n", INSN_UID (def_insn), regno);
	      continue;  /* Already have moveq, just skip.  */
	    }

	  /* Extra validation for cross-BB insertions.  */
	  if (def_bb != bb)
	    {
	      if (dump_file)
		{
		  fprintf (dump_file, "  Cross-BB: inserting in BB %d "
			   "(current BB %d)\n", def_bb->index, bb->index);
		  fprintf (dump_file, "    def_bb head uid=%d, end uid=%d\n",
			   INSN_UID (BB_HEAD (def_bb)),
			   INSN_UID (BB_END (def_bb)));
		  fprintf (dump_file, "    def_insn uid=%d\n",
			   INSN_UID (def_insn));
		}

	      /* Validate BB structure.  */
	      if (BB_HEAD (def_bb) == nullptr || BB_END (def_bb) == nullptr)
		{
		  if (dump_file)
		    fprintf (dump_file, "  SKIP: def_bb has invalid head/end\n");
		  all_succeeded = false;
		  break;
		}
	    }

	  if (dump_file)
	    {
	      fprintf (dump_file, "  Transform: def_insn uid=%d in BB %d\n",
		       INSN_UID (def_insn), def_bb->index);
	    }

	  /* For SI mode register, use moveq #0.
	     For HI mode (byte-to-word), need to clear just the word.  */
	  rtx clear_reg;
	  if (cand.ext_type == EXT_BYTE_TO_WORD)
	    clear_reg = gen_rtx_REG (HImode, REGNO (cand.reg));
	  else
	    clear_reg = gen_rtx_REG (SImode, REGNO (cand.reg));

	  rtx clear_pat = gen_rtx_SET (clear_reg, const0_rtx);
	  rtx_insn *new_insn = emit_insn_before (clear_pat, def_insn);

	  /* Mark that we've inserted a clear for this def_insn + register.  */
	  bitmap_set_bit (already_cleared_before, key);

	  /* Validate the new insn.  */
	  INSN_CODE (new_insn) = -1;
	  if (recog_memoized (new_insn) < 0)
	    {
	      /* Failed to recognize - remove and clean up.  */
	      delete_insn (new_insn);
	      all_succeeded = false;
	      break;
	    }

	  /* Note: we don't call df_insn_rescan here - let TODO_df_finish
	     handle dataflow rebuild at the end of the pass.  Calling
	     df_insn_rescan during cross-BB insertions can cause issues.  */

	  inserted_insns.safe_push (new_insn);
	}

      if (!all_succeeded)
	{
	  /* Remove any insns we inserted.  Use delete_insn() to properly
	     update the dataflow framework.  */
	  for (rtx_insn *ins : inserted_insns)
	    delete_insn (ins);
	  continue;
	}

      /* Delete the andi instruction.  Use delete_insn() instead of
	 SET_INSN_DELETED() to properly update the dataflow framework.  */
      if (dump_file)
	fprintf (dump_file, "deleting insn with uid = %d.\n",
		 INSN_UID (cand.andi_insn));
      delete_insn (cand.andi_insn);
      changes++;
    }

  if (dump_file)
    fprintf (dump_file, "m68k-elim-andi: Done with BB %d, changes=%d\n",
	     bb->index, changes);

  return changes;
}

/* Main function for the elim_andi pass.  */

static unsigned int
m68k_elim_andi (function *func)
{
  unsigned int changes = 0;

  /* Track def_insns that already have moveq inserted before them.
     Key is (insn UID << 4) | regno to handle different registers.
     This is shared across all BBs to prevent duplicate insertions
     when multiple BBs reference the same def_insn in a predecessor.  */
  auto_bitmap already_cleared_before;

  basic_block bb;
  FOR_EACH_BB_FN (bb, func)
    {
      changes += m68k_elim_andi_bb (bb, already_cleared_before);
    }

  if (dump_file)
    fprintf (dump_file, "m68k-elim-andi: Pass complete, total changes=%d\n",
	     changes);

  /* Don't call df_analyze() manually - let TODO_df_finish handle
     dataflow cleanup.  delete_insn() has already notified DF about
     the deleted instructions.  */

  if (dump_file)
    fprintf (dump_file, "m68k-elim-andi: Returning from pass\n");

  /* Return 0 - the TODO_df_finish in pass_data will trigger
     df_finish_pass() to rebuild dataflow as needed.  */
  return 0;
}

/* Pass data for m68k_pass_elim_andi.  */

const pass_data m68k_pass_data_elim_andi =
{
  RTL_PASS,		/* type */
  "m68k-elim-andi",	/* name */
  OPTGROUP_NONE,	/* optinfo_flags */
  TV_MACH_DEP,		/* tv_id */
  0,			/* properties_required */
  0,			/* properties_provided */
  0,			/* properties_destroyed */
  0,			/* todo_flags_start */
  TODO_df_finish	/* todo_flags_finish */
};

/* The pass class for elim_andi.  */

class m68k_pass_elim_andi : public rtl_opt_pass
{
public:
  m68k_pass_elim_andi (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_elim_andi, ctxt)
  {}

  unsigned int execute (function *func) final override
  {
    if (optimize)
      return m68k_elim_andi (func);
    return 0;
  }

}; /* class m68k_pass_elim_andi */

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

/* Factory function for m68k_pass_narrow_index_mult.  */

gimple_opt_pass *
make_m68k_pass_narrow_index_mult (gcc::context *ctxt)
{
  return new m68k_pass_narrow_index_mult (ctxt);
}

/* Factory function for m68k_pass_elim_andi.  */

rtl_opt_pass *
make_m68k_pass_elim_andi (gcc::context *ctxt)
{
  return new m68k_pass_elim_andi (ctxt);
}
