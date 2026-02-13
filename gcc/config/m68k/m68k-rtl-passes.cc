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
#include "cfgloop.h"

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
	  /* Check for read-modify-write patterns like XOR where the register
	     appears in both operands.  get_negative_offset only finds direct
	     MEMs, so if the register is mentioned but we didn't find a
	     negative offset, there's a nested MEM we can't handle.  */
	  rtx reg = gen_rtx_REG (Pmode, regno);
	  bool src_uses_reg = reg_mentioned_p (reg, src);
	  bool dest_uses_reg = reg_mentioned_p (reg, dest);
	  if (src_uses_reg && src_neg == 0)
	    break;  /* Nested MEM in src we can't update */
	  if (dest_uses_reg && dest_neg == 0)
	    break;  /* Nested MEM in dest we can't update */

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
      df_insn_rescan (fix.insn);
    }

  /* Move the increment instruction to after the last fixup instruction.  */
  remove_insn (add_insn);
  add_insn_after (add_insn, last_fixup_insn, bb);
  df_insn_rescan (add_insn);

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

  /* POST_INC modifies the address register.  We cannot use POST_INC if the
     other operand of the first instruction is the same register, because
     that would create conflicting uses (e.g., loading into %a0 from
     memory addressed by %a0 with post-increment).  */
  rtx first_set = single_set (first_insn);
  if (first_set)
    {
      rtx other_op = is_dest ? SET_SRC (first_set) : SET_DEST (first_set);
      if (REG_P (other_op) && (int) REGNO (other_op) == regno)
	return false;
      /* Also check for the register appearing in the other operand.  */
      if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), other_op))
	return false;
    }

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

  /* Add REG_INC note and notify DF about the change.  */
  add_reg_note (first_insn, REG_INC, reg);
  df_insn_rescan (first_insn);

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
      df_insn_rescan (insn);
    }

  /* 3. Adjust or delete the add instruction (if present).  */
  if (add_insn)
    {
      HOST_WIDE_INT remaining = add_incr - current_adj;
      if (remaining == 0)
	{
	  /* Delete the add instruction entirely.  */
	  delete_insn (add_insn);
	}
      else if (remaining > 0)
	{
	  /* Reduce the add value.  */
	  rtx set = single_set (add_insn);
	  rtx src = SET_SRC (set);
	  XEXP (src, 1) = GEN_INT (remaining);
	  INSN_CODE (add_insn) = -1;
	  recog_memoized (add_insn);
	  df_insn_rescan (add_insn);
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
	  bool bb_changed = false;
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
		      bb_changed = true;
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
		      bb_changed = true;
		    }
		}
	    }

	  /* Recompute LUIDs after modifying the basic block.  */
	  if (bb_changed)
	    df_recompute_luids (bb);
	}
    }
  while (made_changes);

  return 0;
}

/* Check whether REGNO is dead on all successor edges of PRED except
   the edge to BB.  Returns true if dead on all other edges.  This
   handles EH edges and other multi-successor scenarios.  */

static bool
reg_dead_on_other_edges (basic_block pred, basic_block bb, int regno)
{
  edge e;
  edge_iterator ei;
  FOR_EACH_EDGE (e, ei, pred->succs)
    {
      if (e->dest == bb)
	continue;
      if (bitmap_bit_p (df_get_live_in (e->dest), regno))
	return false;
    }
  return true;
}

/* Try to convert a load in a predecessor BB followed by an increment at the
   top of this BB into a post-increment load.  This handles the cross-BB
   pattern seen in strcmp-like loops:

     BB_pred:
       move.b (%a0),%d0       ; load
       jeq .Lexit              ; conditional branch (ends BB_pred)
     BB:
       addq.l #1,%a0           ; increment

   Converts to:
     BB_pred:
       move.b (%a0)+,%d0      ; load + increment
       jeq .Lexit
     BB:
       ; addq deleted

   This is safe when the address register is dead on the exit path.  */

static bool
try_cross_bb_postinc (basic_block bb)
{
  bool changed = false;

  /* Process increments near the start of BB.  */
  for (rtx_insn *insn = BB_HEAD (bb); insn; insn = NEXT_INSN (insn))
    {
      if (!NONDEBUG_INSN_P (insn))
	{
	  if (insn == BB_END (bb))
	    break;
	  continue;
	}

      int regno;
      HOST_WIDE_INT incr;
      if (!is_reg_increment (insn, &regno, &incr))
	break;  /* Stop at first non-increment instruction.  */

      /* Remember if this is the last insn so we don't escape the BB.  */
      bool is_last = (insn == BB_END (bb));

      /* Must be an address register (a0-a7 = regs 8-15).  */
      if (regno < 8 || regno > 15)
	{
	  if (is_last) break;
	  continue;
	}

      /* Increment must be positive (post-increment only).  */
      if (incr <= 0)
	{
	  if (is_last) break;
	  continue;
	}

      /* No prior reads of this register in BB before the increment.
	 Check from BB_HEAD to this insn.  */
      bool prior_use = false;
      for (rtx_insn *scan = BB_HEAD (bb); scan != insn;
	   scan = NEXT_INSN (scan))
	{
	  if (!NONDEBUG_INSN_P (scan))
	    continue;
	  if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), PATTERN (scan)))
	    {
	      prior_use = true;
	      break;
	    }
	}
      if (prior_use)
	{
	  if (is_last) break;
	  continue;
	}

      /* Single predecessor.  */
      if (!single_pred_p (bb))
	{
	  if (is_last) break;
	  continue;
	}

      basic_block pred = single_pred (bb);

      /* Skip ENTRY/EXIT pseudo-blocks (they have no real insns).  */
      if (pred->index < NUM_FIXED_BLOCKS)
	{
	  if (is_last) break;
	  continue;
	}

      /* Predecessor must end with a conditional branch.  */
      rtx_insn *branch = BB_END (pred);
      if (!JUMP_P (branch) || !any_condjump_p (branch))
	{
	  if (is_last) break;
	  continue;
	}

      /* Predecessor must have exactly 2 successors (no EH edges etc.).  */
      if (EDGE_COUNT (pred->succs) != 2)
	{
	  if (is_last) break;
	  continue;
	}

      /* Register must be dead on all other successor edges.  */
      if (!reg_dead_on_other_edges (pred, bb, regno))
	{
	  if (is_last) break;
	  continue;
	}

      /* Scan backward from the branch in the predecessor to find a matching
	 load: (set (reg:M dN) (mem:M (reg:SI aX))) where the MEM's mode
	 size equals the increment.  */
      rtx_insn *load_insn = nullptr;
      rtx load_mem = nullptr;
      int is_dest = 0;

      for (rtx_insn *scan = PREV_INSN (branch); scan;
	   scan = PREV_INSN (scan))
	{
	  if (BLOCK_FOR_INSN (scan) != pred)
	    break;
	  if (!NONDEBUG_INSN_P (scan))
	    continue;

	  rtx set = single_set (scan);
	  if (!set)
	    break;  /* Complex insn, stop.  */

	  rtx dest = SET_DEST (set);
	  rtx src = SET_SRC (set);

	  /* Check if this instruction defines or clobbers the address
	     register — if so, stop scanning.  */
	  if (REG_P (dest) && (int) REGNO (dest) == regno)
	    break;

	  /* Check for load: (set (reg:M) (mem:M (reg aX))).  */
	  int mem_regno;
	  if (MEM_P (src) && mem_reg_p (src, &mem_regno)
	      && mem_regno == regno)
	    {
	      if (GET_MODE_SIZE (GET_MODE (src)) == incr)
		{
		  load_insn = scan;
		  load_mem = src;
		  is_dest = 0;
		}
	      break;  /* Found a use, stop regardless.  */
	    }

	  /* Check for store: (set (mem:M (reg aX)) (reg:M)).  */
	  if (MEM_P (dest) && mem_reg_p (dest, &mem_regno)
	      && mem_regno == regno)
	    {
	      if (GET_MODE_SIZE (GET_MODE (dest)) == incr)
		{
		  load_insn = scan;
		  load_mem = dest;
		  is_dest = 1;
		}
	      break;
	    }

	  /* If the register is referenced otherwise, stop.  */
	  if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), PATTERN (scan)))
	    break;
	}

      if (!load_insn)
	continue;

      /* Verify no other use of the address register between load and
	 branch end.  */
      bool intervening_use = false;
      for (rtx_insn *scan = NEXT_INSN (load_insn); scan != branch;
	   scan = NEXT_INSN (scan))
	{
	  if (!NONDEBUG_INSN_P (scan))
	    continue;
	  if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), PATTERN (scan)))
	    {
	      intervening_use = true;
	      break;
	    }
	}
      if (intervening_use)
	continue;

      /* Also check the branch itself doesn't use the address register.  */
      if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), PATTERN (branch)))
	continue;

      /* POST_INC destination != source: can't do move.l (%a0)+,%a0.  */
      rtx set = single_set (load_insn);
      if (!set)
	continue;
      rtx other_op = is_dest ? SET_SRC (set) : SET_DEST (set);
      if (REG_P (other_op) && (int) REGNO (other_op) == regno)
	continue;
      if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), other_op))
	continue;

      /* Build the POST_INC form and validate via recog.  */
      rtx reg = gen_rtx_REG (Pmode, regno);
      machine_mode mode = GET_MODE (load_mem);
      rtx postinc_addr = gen_rtx_POST_INC (Pmode, reg);
      rtx postinc_mem = gen_rtx_MEM (mode, postinc_addr);
      MEM_COPY_ATTRIBUTES (postinc_mem, load_mem);

      if (is_dest)
	SET_DEST (set) = postinc_mem;
      else
	SET_SRC (set) = postinc_mem;

      INSN_CODE (load_insn) = -1;
      if (recog_memoized (load_insn) < 0)
	{
	  /* Restore original.  */
	  if (is_dest)
	    SET_DEST (set) = load_mem;
	  else
	    SET_SRC (set) = load_mem;
	  INSN_CODE (load_insn) = -1;
	  recog_memoized (load_insn);
	  continue;
	}

      /* Success — apply the transformation.  */
      add_reg_note (load_insn, REG_INC, reg);
      df_insn_rescan (load_insn);

      /* Delete the increment instruction.  */
      delete_insn (insn);

      changed = true;

      /* The insn we just deleted may have been the only instruction
	 or the last — restart scan from BB_HEAD.  */
      break;
    }

  return changed;
}

/* Main function for the opt_autoinc pass.  */

static unsigned int
m68k_opt_autoinc (function *func)
{
  unsigned int changes = 0;

  /* Phase 1: Cross-BB post-increment conversion.  Repeat until stable
     because each BB may have multiple increments (e.g. both a0 and a1),
     and we break after each successful conversion.  */
  {
    bool made_changes;
    do
      {
	/* (Re-)compute liveness before each iteration.  */
	df_analyze ();
	made_changes = false;
	basic_block bb;
	FOR_EACH_BB_FN (bb, func)
	  {
	    if (try_cross_bb_postinc (bb))
	      {
		changes++;
		made_changes = true;
	      }
	  }
      }
    while (made_changes);
  }

  /* Phase 2: Within-BB post-increment conversion.  */
  basic_block bb;
  FOR_EACH_BB_FN (bb, func)
    {
      bool bb_changed = false;
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
		{
		  changes++;
		  bb_changed = true;
		}
	    }

	  /* Check destination for memory with zero offset.  */
	  if (MEM_P (dest) && mem_reg_p (dest, &regno))
	    {
	      if (try_convert_to_postinc (bb, insn, dest, 1))
		{
		  changes++;
		  bb_changed = true;
		}
	    }
	}

      /* Recompute LUIDs after modifying the basic block, similar to
	 what the upstream auto-inc-dec pass does.  */
      if (bb_changed)
	df_recompute_luids (bb);
    }

  return 0;
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

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_autoinc;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_normalize_autoinc (func);
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

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_autoinc;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_opt_autoinc (func);
  }

}; /* class m68k_pass_opt_autoinc */




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

/* Check if INSN is andi.l #65535 on a memory location.
   If so, set *MEM to the memory RTX.
   Pattern: (set (mem:SI addr) (and:SI (mem:SI addr) (const_int 65535)))  */

static bool
mem_andi_65535_p (rtx_insn *insn, rtx *mem)
{
  if (!NONJUMP_INSN_P (insn))
    return false;

  rtx pat = PATTERN (insn);
  if (GET_CODE (pat) != SET)
    return false;

  rtx dest = SET_DEST (pat);
  rtx src = SET_SRC (pat);

  /* Must be setting a memory location.  */
  if (!MEM_P (dest) || GET_MODE (dest) != SImode)
    return false;

  /* Source must be (and:SI mem (const_int 65535)).  */
  if (GET_CODE (src) != AND || GET_MODE (src) != SImode)
    return false;

  rtx op0 = XEXP (src, 0);
  rtx op1 = XEXP (src, 1);

  /* Handle both operand orders: (and mem const) or (and const mem).  */
  if (CONST_INT_P (op0))
    std::swap (op0, op1);

  /* First operand must be the same memory location.  */
  if (!MEM_P (op0) || !rtx_equal_p (XEXP (op0, 0), XEXP (dest, 0)))
    {
      if (dump_file)
	{
	  fprintf (dump_file, "  mem AND but address mismatch: ");
	  print_rtl_single (dump_file, insn);
	}
      return false;
    }

  if (!CONST_INT_P (op1) || INTVAL (op1) != 65535)
    {
      if (dump_file && MEM_P (op0))
	{
	  fprintf (dump_file, "  mem AND but mask=%lld not 65535: ",
		   (long long) (CONST_INT_P (op1) ? INTVAL (op1) : -1));
	  print_rtl_single (dump_file, insn);
	}
      return false;
    }

  *mem = dest;
  return true;
}

/* Check if ADDR is a simple stack-relative address (sp + const).
   If so, return the constant offset, otherwise return -1.  */

static HOST_WIDE_INT
get_sp_offset (rtx addr)
{
  /* Direct (sp) reference.  */
  if (REG_P (addr) && REGNO (addr) == STACK_POINTER_REGNUM)
    return 0;

  /* (plus:SI (reg:SI sp) (const_int N))  */
  if (GET_CODE (addr) == PLUS)
    {
      rtx base = XEXP (addr, 0);
      rtx offset = XEXP (addr, 1);
      if (REG_P (base) && REGNO (base) == STACK_POINTER_REGNUM
	  && CONST_INT_P (offset))
	return INTVAL (offset);
    }

  return -1;
}

/* Check if INSN clears the low word of a memory location at
   the given stack offset (which should be base_offset + 2 for big-endian).
   Patterns:
   - (set (mem:HI addr) (const_int 0))
   - (set (strict_low_part (mem:HI addr)) (const_int 0))
   - (set (mem:SI addr) (and:SI (mem:SI addr) (const_int -65536)))  */

static bool
is_mem_clrw_at_offset_p (rtx_insn *insn, HOST_WIDE_INT expected_offset)
{
  if (!NONJUMP_INSN_P (insn))
    return false;

  rtx pat = PATTERN (insn);
  if (GET_CODE (pat) != SET)
    return false;

  rtx dest = SET_DEST (pat);
  rtx src = SET_SRC (pat);

  /* Pattern 1: (set (mem:HI addr) (const_int 0))  */
  if (MEM_P (dest) && GET_MODE (dest) == HImode && src == const0_rtx)
    {
      HOST_WIDE_INT offset = get_sp_offset (XEXP (dest, 0));
      return offset == expected_offset;
    }

  /* Pattern 2: (set (strict_low_part (mem:HI addr)) (const_int 0))
     This is the common form for clr.w on memory.  */
  if (GET_CODE (dest) == STRICT_LOW_PART && src == const0_rtx)
    {
      rtx inner = XEXP (dest, 0);
      if (MEM_P (inner) && GET_MODE (inner) == HImode)
	{
	  HOST_WIDE_INT offset = get_sp_offset (XEXP (inner, 0));
	  return offset == expected_offset;
	}
    }

  /* Pattern 3: (set (mem:SI addr) (and:SI (mem:SI addr) (const_int -65536)))
     This is how clr.w is sometimes represented for 32-bit memory.  */
  if (MEM_P (dest) && GET_MODE (dest) == SImode
      && GET_CODE (src) == AND && GET_MODE (src) == SImode)
    {
      rtx op0 = XEXP (src, 0);
      rtx op1 = XEXP (src, 1);
      if (MEM_P (op0) && rtx_equal_p (XEXP (op0, 0), XEXP (dest, 0))
	  && CONST_INT_P (op1))
	{
	  HOST_WIDE_INT mask = INTVAL (op1);
	  if ((mask & 0xFFFFFFFF) == 0xFFFF0000)
	    {
	      /* The SI-mode clr.w is at the base offset, not offset+2.  */
	      HOST_WIDE_INT offset = get_sp_offset (XEXP (dest, 0));
	      return offset == (expected_offset - 2);
	    }
	}
    }

  return false;
}

/* Scan forward from MEM_ANDI to find clr.w at the low word address.
   For big-endian m68k, if ANDI is at offset N, clr.w should be at N+2.
   Returns true if clr.w is found and the ANDI can be eliminated.  */

static bool
mem_clrw_follows_andi_p (basic_block bb, rtx_insn *andi_insn, rtx mem)
{
  HOST_WIDE_INT base_offset = get_sp_offset (XEXP (mem, 0));
  if (base_offset < 0)
    return false;  /* Not a simple sp-relative address.  */

  HOST_WIDE_INT low_word_offset = base_offset + 2;

  /* Scan forward from andi to find clr.w.  */
  rtx_insn *insn;
  bool past_andi = false;

  FOR_BB_INSNS (bb, insn)
    {
      if (insn == andi_insn)
	{
	  past_andi = true;
	  continue;
	}

      if (!past_andi || !NONDEBUG_INSN_P (insn))
	continue;

      /* Found clr.w at the expected low word offset.  */
      if (is_mem_clrw_at_offset_p (insn, low_word_offset))
	return true;

      /* Check if this instruction clobbers our memory location.  */
      rtx pat = PATTERN (insn);
      if (GET_CODE (pat) == SET)
	{
	  rtx dest = SET_DEST (pat);

	  /* If writing to the same memory location (not clr.w), stop.  */
	  if (MEM_P (dest))
	    {
	      HOST_WIDE_INT dest_offset = get_sp_offset (XEXP (dest, 0));
	      /* Check for overlap with our 32-bit location.  */
	      if (dest_offset >= 0
		  && dest_offset >= base_offset
		  && dest_offset < base_offset + 4)
		{
		  /* This write overlaps - check if it's the clr.w.  */
		  if (!is_mem_clrw_at_offset_p (insn, low_word_offset))
		    return false;
		}
	    }
	}

      /* CALL instructions may clobber stack (be conservative).  */
      if (CALL_P (insn))
	return false;
    }

  return false;
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

  if (!REG_P (dest))
    return false;

  /* Direct SImode clear: moveq #0 or clr.l.  */
  if (REGNO (dest) == regno && GET_MODE (dest) == SImode)
    return src == const0_rtx;

  /* DImode set on d0 that clears d1 (low 32 bits of DImode are zero).  */
  if (GET_MODE (dest) == DImode && REGNO (dest) == 0 && regno == 1)
    {
      if (CONST_INT_P (src))
	{
	  HOST_WIDE_INT val = INTVAL (src);
	  return (val & 0xFFFFFFFF) == 0;
	}
    }

  return false;
}

/* Check if INSN clears the low word of a specific register.
   This matches patterns like:
   - (set (strict_low_part (reg:HI N)) (const_int 0))
   - (set reg:SI (and:SI reg:SI (const_int -65536)))  ; 0xFFFF0000  */

static bool
is_clrw_insn_p (rtx_insn *insn, unsigned regno)
{
  if (!NONJUMP_INSN_P (insn))
    return false;

  rtx pat = PATTERN (insn);
  if (GET_CODE (pat) != SET)
    return false;

  rtx dest = SET_DEST (pat);
  rtx src = SET_SRC (pat);

  /* Check for (set (strict_low_part (reg:HI N)) (const_int 0)).  */
  if (GET_CODE (dest) == STRICT_LOW_PART)
    {
      rtx inner = XEXP (dest, 0);
      if (REG_P (inner)
	  && REGNO (inner) == regno
	  && GET_MODE (inner) == HImode
	  && src == const0_rtx)
	return true;
      /* Also handle subreg form.  */
      if (SUBREG_P (inner))
	{
	  rtx subreg_reg = SUBREG_REG (inner);
	  if (REG_P (subreg_reg)
	      && REGNO (subreg_reg) == regno
	      && GET_MODE (inner) == HImode
	      && src == const0_rtx)
	    return true;
	}
    }

  /* Check for (set reg:SI (and:SI reg:SI (const_int -65536))).
     This is how clr.w %dn is represented in RTL.  */
  if (REG_P (dest)
      && REGNO (dest) == regno
      && GET_MODE (dest) == SImode
      && GET_CODE (src) == AND
      && GET_MODE (src) == SImode)
    {
      rtx op0 = XEXP (src, 0);
      rtx op1 = XEXP (src, 1);
      if (REG_P (op0) && REGNO (op0) == regno && CONST_INT_P (op1))
	{
	  HOST_WIDE_INT mask = INTVAL (op1);
	  /* Check for 0xFFFF0000 (or sign-extended -65536).  */
	  if ((mask & 0xFFFFFFFF) == 0xFFFF0000)
	    return true;
	}
    }

  return false;
}

/* Scan forward from ANDI_IDX in BB_INSNS to see if clr.w follows
   for the same register.  If so, the AND is redundant since clr.w
   will clear the bits that AND preserved.
   Returns true if we found clr.w and the AND can be eliminated.  */

static bool
clrw_follows_andi_p (const auto_vec<rtx_insn *> &bb_insns,
		     int andi_idx, unsigned regno)
{
  /* Scan forward, looking for clr.w or any instruction that uses
     the register's low word value (which would invalidate the optimization).  */
  for (unsigned i = andi_idx + 1; i < bb_insns.length (); i++)
    {
      rtx_insn *insn = bb_insns[i];

      /* Found clr.w - the AND is redundant.  */
      if (is_clrw_insn_p (insn, regno))
	return true;

      /* Check if this instruction uses the register's value.  */
      rtx pat = PATTERN (insn);
      if (GET_CODE (pat) == SET)
	{
	  rtx dest = SET_DEST (pat);
	  rtx src = SET_SRC (pat);

	  /* Special case: (set reg:SI (ior:SI reg:SI (const_int N)))
	     where the constant only affects upper 16 bits.  This is how
	     bset #16-31 is represented.  The low word value is not actually
	     used - the ior just adds bits to the upper word.  */
	  if (REG_P (dest) && REGNO (dest) == regno
	      && GET_MODE (dest) == SImode
	      && GET_CODE (src) == IOR
	      && GET_MODE (src) == SImode)
	    {
	      rtx op0 = XEXP (src, 0);
	      rtx op1 = XEXP (src, 1);
	      if (REG_P (op0) && REGNO (op0) == regno && CONST_INT_P (op1))
		{
		  HOST_WIDE_INT val = INTVAL (op1);
		  /* If constant only affects upper 16 bits, continue.  */
		  if ((val & 0xFFFF) == 0)
		    continue;
		}
	    }

	  /* Special case: (set reg:SI (asm_operands ...)) where the
	     register is passed through (empty asm with "+d" constraint).
	     The low bits are preserved but not used for computation.  */
	  if (REG_P (dest) && REGNO (dest) == regno
	      && GET_CODE (src) == ASM_OPERANDS)
	    {
	      /* Check if this is a pass-through: same register in input.  */
	      int ninputs = ASM_OPERANDS_INPUT_LENGTH (src);
	      bool is_passthrough = false;
	      for (int k = 0; k < ninputs; k++)
		{
		  rtx input = ASM_OPERANDS_INPUT (src, k);
		  if (REG_P (input) && REGNO (input) == regno)
		    {
		      is_passthrough = true;
		      break;
		    }
		}
	      if (is_passthrough)
		continue;
	    }

	  /* If source uses the register in SI mode, the low bits matter.  */
	  if (reg_mentioned_p (gen_rtx_REG (SImode, regno), src))
	    return false;

	  /* If dest is a strict_low_part write, the low bits will be overwritten
	     but the upper bits (including what AND preserves) are preserved.
	     Continue scanning.  */
	  if (GET_CODE (dest) == STRICT_LOW_PART)
	    {
	      rtx inner = XEXP (dest, 0);
	      if (REG_P (inner) && REGNO (inner) == regno)
		continue;
	      if (SUBREG_P (inner))
		{
		  rtx subreg_reg = SUBREG_REG (inner);
		  if (REG_P (subreg_reg) && REGNO (subreg_reg) == regno)
		    continue;
		}
	    }

	  /* If dest is the register in any mode, stop scanning.  */
	  if (REG_P (dest) && REGNO (dest) == regno)
	    return false;
	}

      /* For PARALLEL or other complex patterns, be conservative.  */
      if (GET_CODE (pat) == PARALLEL)
	{
	  for (int j = 0; j < XVECLEN (pat, 0); j++)
	    {
	      rtx elem = XVECEXP (pat, 0, j);
	      if (GET_CODE (elem) == SET)
		{
		  rtx src = SET_SRC (elem);
		  if (reg_mentioned_p (gen_rtx_REG (SImode, regno), src))
		    return false;
		}
	    }
	}

      /* CALL instructions clobber d0-d1.  */
      if (CALL_P (insn) && regno <= 1)
	return false;
    }

  return false;  /* Didn't find clr.w.  */
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

      /* Check for DImode sets on d0 which also affect d1.
	 On m68k, DImode values in data registers use d0:d1 pair.
	 A set to (reg:DI d0) also defines d1.  */
      if (REG_P (dest) && GET_MODE (dest) == DImode
	  && REGNO (dest) == 0 && regno == 1)
	{
	  /* DImode set on d0 clears/defines d1 (the low 32 bits).
	     Check if the constant has zeros in the low 32 bits.  */
	  if (CONST_INT_P (src))
	    {
	      HOST_WIDE_INT val = INTVAL (src);
	      if ((val & 0xFFFFFFFF) == 0)
		return EFFECT_DEFINES_LONG;  /* d1 is set to 0.  */
	    }
	  return EFFECT_DEFINES_LONG;  /* d1 is defined by DImode set.  */
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
  unsigned int changes = 0;

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

  /* Pass 2-3: For each candidate, trace backward to find definition and transform.
     Only run if there are register ANDI candidates.  */
  if (!candidates.is_empty ())
    {
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

      /* For EXT_WORD_TO_LONG (and.l #$ffff), check if clr.w follows.
	 If the low word is about to be cleared, the AND is redundant since
	 it only preserves the low 16 bits which will be cleared anyway.
	 This catches patterns like: and.l #$ffff; bset #N; clr.w  */
      if (!cand.valid && cand.ext_type == EXT_WORD_TO_LONG)
	{
	  if (clrw_follows_andi_p (bb_insns, andi_idx, regno))
	    {
	      if (dump_file)
		fprintf (dump_file, "  clr.w follows - AND is redundant!\n");
	      cand.valid = true;
	    }
	}

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

	      /* Check for loop exit pattern: def_bb is in a loop but the
		 AND instruction (in bb) is on a loop exit path.  In this
		 case, we should hoist the clr to the loop preheader rather
		 than inserting it in the hot loop body.  */
	      if (current_loops
		  && bb_loop_depth (def_bb) > bb_loop_depth (bb))
		{
		  if (dump_file)
		    fprintf (dump_file, "  Loop exit pattern: def depth %d > "
			     "use depth %d\n",
			     bb_loop_depth (def_bb), bb_loop_depth (bb));

		  /* Find the loop containing the definition.  */
		  class loop *def_loop = def_bb->loop_father;

		  if (def_loop && def_loop != current_loops->tree_root
		      && def_loop->header && def_loop->latch)
		    {
		      /* Manually find the preheader edge - the edge to the
			 loop header that doesn't come from the latch.  */
		      edge prehdr_edge = NULL;
		      edge e;
		      edge_iterator ei;
		      int non_latch_preds = 0;

		      FOR_EACH_EDGE (e, ei, def_loop->header->preds)
			{
			  if (e->src != def_loop->latch)
			    {
			      prehdr_edge = e;
			      non_latch_preds++;
			    }
			}

		      /* Only use preheader if there's exactly one non-latch
			 predecessor (i.e., a proper preheader exists).  */
		      if (prehdr_edge && non_latch_preds == 1
			  && prehdr_edge->src != ENTRY_BLOCK_PTR_FOR_FN (cfun))
			{
			  basic_block preheader = prehdr_edge->src;

			  /* Check if we already inserted a clr for this
			     register in this preheader.  */
			  unsigned preamble_key = (preheader->index << 4)
						  | (regno & 0xf);
			  if (!bitmap_bit_p (already_cleared_before,
					     preamble_key))
			    {
			      /* Determine clear mode based on extension type.  */
			      machine_mode clr_mode
				= (cand.ext_type == EXT_BYTE_TO_WORD)
				  ? HImode : SImode;
			      rtx clr_reg
				= gen_rtx_REG (clr_mode, regno);
			      rtx clr_pat
				= gen_rtx_SET (clr_reg, const0_rtx);

			      /* Insert before the jump (if any), otherwise
				 after the last insn.  Using emit_insn_before
				 avoids walking past NOTE_INSN_BASIC_BLOCK
				 and corrupting the CFG.  */
			      rtx_insn *prehdr_insn;
			      if (JUMP_P (BB_END (preheader)))
				prehdr_insn
				  = emit_insn_before (clr_pat,
						      BB_END (preheader));
			      else
				prehdr_insn
				  = emit_insn_after (clr_pat,
						     BB_END (preheader));

			      INSN_CODE (prehdr_insn) = -1;
			      if (recog_memoized (prehdr_insn) >= 0)
				{
				  bitmap_set_bit (already_cleared_before,
						  preamble_key);
				  if (dump_file)
				    fprintf (dump_file,
					     "  Hoisted clr.%c d%d to loop "
					     "preheader BB %d\n",
					     clr_mode == HImode ? 'w' : 'l',
					     regno, preheader->index);
				  inserted_insns.safe_push (prehdr_insn);
				  /* Continue to next def_insn - don't insert
				     in loop body.  */
				  continue;
				}
			      else
				{
				  if (dump_file)
				    fprintf (dump_file,
					     "  FAILED: preheader clr not "
					     "recognized\n");
				  delete_insn (prehdr_insn);
				}
			    }
			  else
			    {
			      /* Already have clr in preheader.  */
			      if (dump_file)
				fprintf (dump_file,
					 "  Already have clr in preheader "
					 "for d%d\n", regno);
			      /* Continue to next def_insn.  */
			      continue;
			    }
			}
		    }

		  /* No preheader available - skip this candidate entirely
		     to avoid hoisting into the hot loop body.  */
		  if (dump_file)
		    fprintf (dump_file, "  SKIP: loop exit pattern but no "
			     "preheader available\n");
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
    }  /* End if (!candidates.is_empty()) */

  /* Pass 4: Check for memory ANDI patterns.
     Pattern: andi.l #$ffff, N(sp) followed by clr.w N+2(sp)
     The ANDI preserves low 16 bits, but clr.w clears them - redundant.  */
  if (dump_file)
    fprintf (dump_file, "  Pass 4: Scanning for memory ANDI patterns\n");

  FOR_BB_INSNS (bb, insn)
    {
      if (!NONJUMP_INSN_P (insn))
	continue;

      rtx pat = PATTERN (insn);
      if (GET_CODE (pat) == SET && MEM_P (SET_DEST (pat))
	  && GET_CODE (SET_SRC (pat)) == AND && dump_file)
	{
	  fprintf (dump_file, "  Checking mem AND: ");
	  print_rtl_single (dump_file, insn);
	}

      rtx mem;
      if (mem_andi_65535_p (insn, &mem))
	{
	  if (dump_file)
	    {
	      fprintf (dump_file, "  Found mem andi.l #$ffff: ");
	      print_rtl_single (dump_file, insn);
	    }

	  if (mem_clrw_follows_andi_p (bb, insn, mem))
	    {
	      if (dump_file)
		fprintf (dump_file, "  mem clr.w follows - ANDI is redundant!\n");

	      delete_insn (insn);
	      changes++;

	      if (dump_file)
		fprintf (dump_file, "  Deleted memory ANDI insn.\n");
	    }
	}
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

  /* Ensure loop info is available for preamble hoisting optimization.
     This allows us to detect loop exit patterns and hoist clr instructions
     to loop preheaders instead of into loop bodies.  */
  bool created_loops = false;
  if (current_loops == NULL)
    {
      loop_optimizer_init (AVOID_CFG_MODIFICATIONS);
      created_loops = true;
    }

  /* Track def_insns that already have moveq inserted before them.
     Key is (insn UID << 4) | regno to handle different registers.
     This is shared across all BBs to prevent duplicate insertions
     when multiple BBs reference the same def_insn in a predecessor.
     Also used for preheader insertions with (bb_index << 4) | regno.  */
  auto_bitmap already_cleared_before;

  basic_block bb;
  FOR_EACH_BB_FN (bb, func)
    {
      changes += m68k_elim_andi_bb (bb, already_cleared_before);
    }

  if (dump_file)
    fprintf (dump_file, "m68k-elim-andi: Pass complete, total changes=%d\n",
	     changes);

  /* Clean up loop info if we initialized it.  */
  if (created_loops)
    loop_optimizer_finalize ();

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

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_elim_andi;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_elim_andi (func);
  }

}; /* class m68k_pass_elim_andi */


/* =======================================================================
   RTL pass: m68k_pass_highword_opt

   This pass optimizes high-word field access for small structs passed
   by value in registers:

   1. Extraction: Removes redundant clr.w before swap
      clr.w %d0; swap %d0  ->  swap %d0

   2. Computation: Removes unnecessary ext.l before HImode ops
      swap %d0; ext.l %d0; add.w %d1,%d0  ->  swap %d0; add.w %d1,%d0

   3. Insertion: Converts mask+or to swap+strict_low_part+swap
      swap %d1; clr.w %d1; and.l #65535,%d0; or.l %d1,%d0
      ->  swap %d0; move.w %d1,%d0; swap %d0

   Runs after fast_rtl_dce to avoid premature DCE of inserted code.
   ======================================================================= */

/* Check if INSN is a shift by 16 on a data register.
   Matches patterns: (set reg:SI (SHIFT_CODE:SI reg:SI (const_int 16)))
   where SHIFT_CODE is ASHIFT, ASHIFTRT, or LSHIFTRT.

   If SHIFT_CODE is not UNKNOWN, only matches that specific shift type.
   If SHIFT_CODE is UNKNOWN, matches any shift type and sets *FOUND_CODE.

   Returns the register if found, NULL_RTX otherwise.  */

static rtx
is_shift_by_16_p (rtx_insn *insn, enum rtx_code shift_code,
		  enum rtx_code *found_code = nullptr)
{
  if (!NONJUMP_INSN_P (insn))
    return NULL_RTX;

  rtx pat = PATTERN (insn);
  if (GET_CODE (pat) != SET)
    return NULL_RTX;

  rtx dest = SET_DEST (pat);
  rtx src = SET_SRC (pat);

  if (!REG_P (dest)
      || !DATA_REG_P (dest)
      || GET_MODE (dest) != SImode)
    return NULL_RTX;

  enum rtx_code src_code = GET_CODE (src);
  if (shift_code != UNKNOWN)
    {
      if (src_code != shift_code)
	return NULL_RTX;
    }
  else
    {
      if (src_code != ASHIFT && src_code != ASHIFTRT && src_code != LSHIFTRT)
	return NULL_RTX;
    }

  rtx shift_reg = XEXP (src, 0);
  rtx shift_cnt = XEXP (src, 1);

  if (!REG_P (shift_reg)
      || REGNO (shift_reg) != REGNO (dest)
      || !CONST_INT_P (shift_cnt)
      || INTVAL (shift_cnt) != 16)
    return NULL_RTX;

  if (found_code)
    *found_code = src_code;

  return dest;
}

/* Check if INSN is ext.l (sign_extend:SI from low word of same reg).
   Pattern: (set reg:SI (sign_extend:SI (subreg:HI reg:SI 2)))
   Returns the register if found, NULL_RTX otherwise.  */

static rtx
highword_is_ext_long_p (rtx_insn *insn)
{
  if (!NONJUMP_INSN_P (insn))
    return NULL_RTX;

  rtx pat = PATTERN (insn);
  if (GET_CODE (pat) != SET)
    return NULL_RTX;

  rtx dest = SET_DEST (pat);
  rtx src = SET_SRC (pat);

  if (!REG_P (dest)
      || !DATA_REG_P (dest)
      || GET_MODE (dest) != SImode)
    return NULL_RTX;

  if (GET_CODE (src) != SIGN_EXTEND
      || GET_MODE (XEXP (src, 0)) != HImode)
    return NULL_RTX;

  rtx inner = XEXP (src, 0);

  /* Check for (subreg:HI reg:SI 2) form.  */
  if (GET_CODE (inner) == SUBREG
      && SUBREG_BYTE (inner) == 2
      && REG_P (SUBREG_REG (inner))
      && REGNO (SUBREG_REG (inner)) == REGNO (dest))
    return dest;

  /* Check for direct reg:HI form (same regno).  */
  if (REG_P (inner) && REGNO (inner) == REGNO (dest))
    return dest;

  return NULL_RTX;
}

/* Check if INSN is and.l #65535 on a data register.
   Pattern: (set reg:SI (and:SI reg:SI (const_int 65535)))
   Returns the register if found, NULL_RTX otherwise.  */

static rtx
highword_is_and_65535_p (rtx_insn *insn)
{
  rtx reg;
  if (classify_andi_extension (insn, &reg) == EXT_WORD_TO_LONG)
    return reg;
  return NULL_RTX;
}

/* Check if INSN is or.l #const on a data register, where const's low
   16 bits are zero (e.g., or.l #0xC00000).
   Pattern: (set reg:SI (ior:SI reg:SI (const_int N))) where (N & 0xffff) == 0
   Sets *const_val to the constant value if found.
   Returns the register if found, NULL_RTX otherwise.  */

static rtx
highword_is_ior_high_const_p (rtx_insn *insn, HOST_WIDE_INT *const_val)
{
  if (!NONJUMP_INSN_P (insn))
    return NULL_RTX;

  rtx pat = PATTERN (insn);
  if (GET_CODE (pat) != SET)
    return NULL_RTX;

  rtx dest = SET_DEST (pat);
  rtx src = SET_SRC (pat);

  if (!REG_P (dest)
      || !DATA_REG_P (dest)
      || GET_MODE (dest) != SImode)
    return NULL_RTX;

  if (GET_CODE (src) != IOR)
    return NULL_RTX;

  rtx op0 = XEXP (src, 0);
  rtx op1 = XEXP (src, 1);

  if (!REG_P (op0)
      || REGNO (op0) != REGNO (dest)
      || !CONST_INT_P (op1))
    return NULL_RTX;

  HOST_WIDE_INT val = INTVAL (op1);
  /* Check that low 16 bits are zero - this means the constant only
     affects the high word, so we can use or.w from memory.  */
  if ((val & 0xffff) != 0)
    return NULL_RTX;

  *const_val = val;
  return dest;
}

/* Check if INSN is a memory load to a data register.
   Pattern: (set reg:SI (mem:SI addr))
   Sets *mem_addr to the memory address if found.
   Returns the register if found, NULL_RTX otherwise.  */

static rtx
highword_is_mem_load_p (rtx_insn *insn, rtx *mem_addr)
{
  if (!NONJUMP_INSN_P (insn))
    return NULL_RTX;

  rtx pat = PATTERN (insn);
  if (GET_CODE (pat) != SET)
    return NULL_RTX;

  rtx dest = SET_DEST (pat);
  rtx src = SET_SRC (pat);

  if (!REG_P (dest)
      || !DATA_REG_P (dest)
      || GET_MODE (dest) != SImode)
    return NULL_RTX;

  if (!MEM_P (src) || GET_MODE (src) != SImode)
    return NULL_RTX;

  *mem_addr = XEXP (src, 0);
  return dest;
}

/* Check if INSN is or.l of two registers where dest is one of them.
   Pattern: (set reg0:SI (ior:SI reg0:SI reg1:SI))
   Sets *other_reg to the other operand if found.
   Returns the destination register if found, NULL_RTX otherwise.  */

static rtx
highword_is_ior_regs_p (rtx_insn *insn, rtx *other_reg)
{
  if (!NONJUMP_INSN_P (insn))
    return NULL_RTX;

  rtx pat = PATTERN (insn);
  if (GET_CODE (pat) != SET)
    return NULL_RTX;

  rtx dest = SET_DEST (pat);
  rtx src = SET_SRC (pat);

  if (!REG_P (dest)
      || !DATA_REG_P (dest)
      || GET_MODE (dest) != SImode)
    return NULL_RTX;

  if (GET_CODE (src) != IOR)
    return NULL_RTX;

  rtx op0 = XEXP (src, 0);
  rtx op1 = XEXP (src, 1);

  if (REG_P (op0) && REG_P (op1))
    {
      if (REGNO (op0) == REGNO (dest))
	{
	  *other_reg = op1;
	  return dest;
	}
      if (REGNO (op1) == REGNO (dest))
	{
	  *other_reg = op0;
	  return dest;
	}
    }

  return NULL_RTX;
}

/* Check if INSN uses REG only in HImode (not SImode).
   Used to verify ext.l is unnecessary before HImode operations.  */

static bool
highword_insn_uses_only_himode_p (rtx_insn *insn, unsigned regno)
{
  rtx pat = PATTERN (insn);
  if (GET_CODE (pat) != SET)
    return false;

  rtx src = SET_SRC (pat);
  rtx dest = SET_DEST (pat);

  /* Check source doesn't use reg in SImode.  */
  if (uses_reg_as_long_p (src, regno))
    return false;

  /* Check dest doesn't use reg in SImode (e.g., in address).  */
  if (MEM_P (dest) && uses_reg_as_long_p (dest, regno))
    return false;

  /* Verify it actually uses the register in HImode.  */
  rtx hi_reg = gen_rtx_REG (HImode, regno);
  return reg_mentioned_p (hi_reg, pat);
}

/* Optimize extraction: Replace shift-right by 16 with rotate when safe.
   Transforms:
     lshiftrt:SI by 16 (clr.w; swap) -> rotate:SI by 16 (swap)
     ashiftrt:SI by 16 (swap; ext.l) -> rotate:SI by 16 (swap)

   The lshrsi_16 pattern outputs "clr.w %0; swap %0" which clears upper bits.
   The ashrsi_16 pattern outputs "swap %0; ext.l %0" which sign-extends.

   If the result is only used in HImode (as a short), the upper bits don't
   matter and we can use just "swap" (rotate by 16).

   This is safe because:
   1. The swap moves the high word to the low position
   2. If the result is only used as HImode, upper bits are ignored
   3. Case 1 (low word extraction) returns with just rts, proving
      HImode returns don't require the high word to be cleared
   4. For ashiftrt, signed overflow is UB so ext.l is unnecessary

   Returns true if any optimization was performed.  */

static bool
highword_optimize_extraction (basic_block bb)
{
  bool changed = false;

  for (rtx_insn *insn = BB_HEAD (bb);
       insn && insn != NEXT_INSN (BB_END (bb));
       insn = NEXT_INSN (insn))
    {
      if (!NONDEBUG_INSN_P (insn))
	continue;

      /* Check for lshiftrt:SI by 16 or ashiftrt:SI by 16.  */
      enum rtx_code shift_code;
      rtx shift_reg = is_shift_by_16_p (insn, UNKNOWN, &shift_code);
      if (shift_reg == NULL_RTX
	  || (shift_code != LSHIFTRT && shift_code != ASHIFTRT))
	continue;
      const char *shift_name = (shift_code == LSHIFTRT) ? "lshiftrt" : "ashiftrt";

      unsigned regno = REGNO (shift_reg);

      /* Check if the register is only used in HImode after this insn,
	 or if it's dead.  We can safely use rotate instead of shift
	 in these cases because the upper 16 bits don't matter.  */

      bool upper_bits_matter = false;
      for (rtx_insn *scan = NEXT_INSN (insn);
	   scan && scan != NEXT_INSN (BB_END (bb));
	   scan = NEXT_INSN (scan))
	{
	  if (!NONDEBUG_INSN_P (scan))
	    continue;

	  /* If register is redefined, we're safe - upper bits reset.  */
	  if (reg_set_p (shift_reg, scan))
	    break;

	  /* If register is used in SImode, upper bits matter.  */
	  if (uses_reg_as_long_p (PATTERN (scan), regno))
	    {
	      upper_bits_matter = true;
	      break;
	    }
	}

      /* Also check if reg is live out of BB - be conservative.  */
      if (!upper_bits_matter)
	{
	  bitmap live_out = df_get_live_out (bb);
	  if (bitmap_bit_p (live_out, regno))
	    {
	      /* Live out of block.  For return values (d0), check if
		 the function returns HImode - in that case upper bits
		 don't matter even if live out.  */
	      if (regno == 0)
		{
		  /* Check if function returns HImode.  */
		  tree ret_type = TREE_TYPE (TREE_TYPE (cfun->decl));
		  if (ret_type && INTEGRAL_TYPE_P (ret_type)
		      && TYPE_PRECISION (ret_type) <= 16)
		    {
		      /* Function returns HImode or smaller - upper bits
			 don't matter.  */
		    }
		  else
		    upper_bits_matter = true;
		}
	      else
		upper_bits_matter = true;
	    }
	}

      if (upper_bits_matter)
	continue;

      /* Safe to replace shift with rotate.  */
      if (dump_file)
	{
	  fprintf (dump_file, "m68k-highword-opt: Replacing %s:SI by 16 "
		   "with rotate:SI (d%d):\n", shift_name, regno);
	  print_rtl_single (dump_file, insn);
	}

      /* Create new rotate pattern: (set reg:SI (rotate:SI reg:SI 16))  */
      rtx new_pat = gen_rtx_SET (shift_reg,
				 gen_rtx_ROTATE (SImode, shift_reg,
						 GEN_INT (16)));
      rtx_insn *new_insn = emit_insn_before (new_pat, insn);
      INSN_CODE (new_insn) = -1;  /* Force recog.  */

      /* Delete the old shift insn.  */
      delete_insn (insn);

      /* Update df info.  */
      df_insn_rescan (new_insn);

      changed = true;
    }

  return changed;
}

/* Optimize computation: Remove ext.l before HImode ops.
   Transform: swap %d0; ext.l %d0; add.w %d1,%d0  ->  swap %d0; add.w %d1,%d0

   This is safe because:
   1. The ext.l sign-extends the low word to 32 bits
   2. If the next operation is HImode (add.w), it only affects low 16 bits
   3. Signed overflow in C is undefined behavior

   Returns true if any optimization was performed.  */

static bool
highword_optimize_computation (basic_block bb)
{
  bool changed = false;

  for (rtx_insn *insn = BB_HEAD (bb);
       insn && insn != NEXT_INSN (BB_END (bb));
       insn = NEXT_INSN (insn))
    {
      if (!NONDEBUG_INSN_P (insn))
	continue;

      rtx ext_reg = highword_is_ext_long_p (insn);
      if (ext_reg == NULL_RTX)
	continue;

      unsigned regno = REGNO (ext_reg);

      /* Look for next non-debug insn.  */
      rtx_insn *next = insn;
      while ((next = NEXT_INSN (next)) != NULL
	     && next != NEXT_INSN (BB_END (bb))
	     && DEBUG_INSN_P (next))
	;

      if (next == NULL || next == NEXT_INSN (BB_END (bb)))
	continue;

      /* Check if next insn uses register only in HImode.  */
      if (!highword_insn_uses_only_himode_p (next, regno))
	continue;

      /* Verify register is not used in SImode before being redefined.  */
      bool safe = true;
      for (rtx_insn *scan = NEXT_INSN (next);
	   scan && scan != NEXT_INSN (BB_END (bb));
	   scan = NEXT_INSN (scan))
	{
	  if (!NONDEBUG_INSN_P (scan))
	    continue;

	  if (reg_set_p (ext_reg, scan))
	    break;  /* Redefined - safe.  */

	  if (uses_reg_as_long_p (PATTERN (scan), regno))
	    {
	      safe = false;
	      break;
	    }
	}

      if (!safe)
	continue;

      /* Also check live-out.  */
      bitmap live_out = df_get_live_out (bb);
      if (bitmap_bit_p (live_out, regno))
	continue;

      /* Safe to remove ext.l.  */
      if (dump_file)
	{
	  fprintf (dump_file, "m68k-highword-opt: Removing unnecessary ext.l "
		   "before HImode op (d%d):\n", regno);
	  print_rtl_single (dump_file, insn);
	}

      delete_insn (insn);
      changed = true;
    }

  return changed;
}

/* Optimize insertion: Convert ashift+and+or to swap+move.w+swap.
   Transform:
     ashift:SI %d1,#16 (swap+clr.w); and.l #65535,%d0; or.l %d1,%d0
   To:
     swap %d0; move.w %d1,%d0; swap %d0

   The ashift:SI by 16 pattern (ashlsi_16) outputs "swap; clr.w".
   We replace the whole sequence with swap/move.w/swap which is
   one instruction shorter.

   Prerequisites:
   - value_reg must be dead after the or.l
   - The ashift must have value to insert in low 16 bits originally

   Returns true if any optimization was performed.  */

static bool
highword_optimize_insertion (basic_block bb)
{
  bool changed = false;

  for (rtx_insn *insn = BB_HEAD (bb);
       insn && insn != NEXT_INSN (BB_END (bb)); )
    {
      rtx_insn *next_iter = NEXT_INSN (insn);

      if (!NONDEBUG_INSN_P (insn))
	{
	  insn = next_iter;
	  continue;
	}

      /* Look for: ashift:SI value_reg,#16 (outputs swap+clr.w).  */
      rtx ashift_reg = is_shift_by_16_p (insn, ASHIFT);
      if (ashift_reg == NULL_RTX)
	{
	  insn = next_iter;
	  continue;
	}

      unsigned value_regno = REGNO (ashift_reg);
      rtx_insn *ashift_insn = insn;

      /* Look for: and.l #65535, struct_reg.  Skip notes and debug insns.  */
      rtx_insn *and_insn = ashift_insn;
      while ((and_insn = NEXT_INSN (and_insn)) != NULL
	     && and_insn != NEXT_INSN (BB_END (bb))
	     && !NONDEBUG_INSN_P (and_insn))
	;

      if (and_insn == NULL || and_insn == NEXT_INSN (BB_END (bb)))
	{
	  insn = next_iter;
	  continue;
	}

      rtx and_reg = highword_is_and_65535_p (and_insn);
      if (and_reg == NULL_RTX)
	{
	  insn = next_iter;
	  continue;
	}

      unsigned struct_regno = REGNO (and_reg);
      if (struct_regno == value_regno)
	{
	  insn = next_iter;
	  continue;  /* Must be different registers.  */
	}

      /* Look for: or.l value_reg, struct_reg.  Skip notes and debug insns.  */
      rtx_insn *ior_insn = and_insn;
      while ((ior_insn = NEXT_INSN (ior_insn)) != NULL
	     && ior_insn != NEXT_INSN (BB_END (bb))
	     && !NONDEBUG_INSN_P (ior_insn))
	;

      if (ior_insn == NULL || ior_insn == NEXT_INSN (BB_END (bb)))
	{
	  insn = next_iter;
	  continue;
	}

      rtx ior_other;
      rtx ior_reg = highword_is_ior_regs_p (ior_insn, &ior_other);
      if (ior_reg == NULL_RTX
	  || REGNO (ior_reg) != struct_regno
	  || !REG_P (ior_other)
	  || REGNO (ior_other) != value_regno)
	{
	  insn = next_iter;
	  continue;
	}

      /* Check that value_reg is dead after ior_insn.  */
      if (!find_regno_note (ior_insn, REG_DEAD, value_regno))
	{
	  bitmap live_out = df_get_live_out (bb);
	  if (bitmap_bit_p (live_out, value_regno))
	    {
	      insn = next_iter;
	      continue;
	    }
	}

      /* Found complete pattern! Transform it.  */
      if (dump_file)
	{
	  fprintf (dump_file, "m68k-highword-opt: Found insertion pattern:\n");
	  fprintf (dump_file, "  ashift d%d,#16: ", value_regno);
	  print_rtl_single (dump_file, ashift_insn);
	  fprintf (dump_file, "  and.l #65535,d%d: ", struct_regno);
	  print_rtl_single (dump_file, and_insn);
	  fprintf (dump_file, "  or.l d%d,d%d: ", value_regno, struct_regno);
	  print_rtl_single (dump_file, ior_insn);
	}

      /* Create: swap %d0 (struct register).  */
      rtx struct_reg = gen_rtx_REG (SImode, struct_regno);
      rtx new_swap1_pat = gen_rtx_SET (struct_reg,
				       gen_rtx_ROTATE (SImode, struct_reg,
						       GEN_INT (16)));
      rtx_insn *new_swap1 = emit_insn_before (new_swap1_pat, ashift_insn);

      /* Create: move.w %d1,%d0 (value -> struct low word).
	 The value we want is in the low 16 bits of value_reg BEFORE
	 the ashift.  Since ashift hasn't executed in our new sequence,
	 we can read the original value directly.  */
      rtx value_hi = gen_rtx_REG (HImode, value_regno);
      rtx slp = gen_rtx_STRICT_LOW_PART (VOIDmode,
					 gen_rtx_SUBREG (HImode, struct_reg, 2));
      rtx new_move_pat = gen_rtx_SET (slp, value_hi);
      rtx_insn *new_move = emit_insn_after (new_move_pat, new_swap1);

      /* Create: swap %d0 (back to correct order).  */
      rtx new_swap2_pat = gen_rtx_SET (struct_reg,
				       gen_rtx_ROTATE (SImode, struct_reg,
						       GEN_INT (16)));
      rtx_insn *new_swap2 = emit_insn_after (new_swap2_pat, new_move);

      /* Validate new instructions.  */
      INSN_CODE (new_swap1) = -1;
      INSN_CODE (new_move) = -1;
      INSN_CODE (new_swap2) = -1;

      if (recog_memoized (new_swap1) < 0
	  || recog_memoized (new_move) < 0
	  || recog_memoized (new_swap2) < 0)
	{
	  /* Failed - restore original.  */
	  if (dump_file)
	    fprintf (dump_file, "  FAILED: New insns not recognized\n");
	  delete_insn (new_swap1);
	  delete_insn (new_move);
	  delete_insn (new_swap2);
	  insn = next_iter;
	  continue;
	}

      if (dump_file)
	{
	  fprintf (dump_file, "  Transformed to:\n");
	  fprintf (dump_file, "  swap d%d: ", struct_regno);
	  print_rtl_single (dump_file, new_swap1);
	  fprintf (dump_file, "  move.w d%d,d%d: ", value_regno, struct_regno);
	  print_rtl_single (dump_file, new_move);
	  fprintf (dump_file, "  swap d%d: ", struct_regno);
	  print_rtl_single (dump_file, new_swap2);
	}

      /* Delete original instructions.  */
      delete_insn (ashift_insn);
      delete_insn (and_insn);
      delete_insn (ior_insn);

      /* Update dataflow.  */
      df_insn_rescan (new_swap1);
      df_insn_rescan (new_move);
      df_insn_rescan (new_swap2);

      changed = true;
      insn = NEXT_INSN (new_swap2);
    }

  return changed;
}

/* Optimize mask+or: Transform memory load + mask + or-high-const
   into load-const + or-from-memory-low-word.

   Transform:
     move.l mem, rA          ; (set rA:SI (mem:SI addr))
     and.l #65535, rA        ; (set rA:SI (and:SI rA:SI 65535))
     or.l #high_const, rA    ; (set rA:SI (ior:SI rA:SI high_const))

   Into:
     move.l #high_const, rA  ; (set rA:SI high_const)
     or.w mem+2, rA          ; (set rA:SI (ior:SI (zero_extend:SI (mem:HI addr+2)) rA))

   Where high_const has no bits in the low 16 bits (e.g., 0xC00000).
   This is profitable because:
   - Original: 3 instructions (move.l + and.l + or.l)
   - Optimized: 2 instructions (move.l + or.w)
   - Saves ~4-6 bytes (and.l #65535 = 6 bytes)

   The optimization is safe because:
   1. The AND masks to low 16 bits, discarding the high word from memory
   2. The OR adds a constant with no low bits, so it's equivalent to setting high word
   3. We can read just the low word from memory (at addr+2 for big-endian) and OR

   Returns true if any optimization was performed.  */

static bool
highword_optimize_mask_or (basic_block bb)
{
  bool changed = false;

  for (rtx_insn *insn = BB_HEAD (bb);
       insn && insn != NEXT_INSN (BB_END (bb));
       insn = NEXT_INSN (insn))
    {
      if (!NONDEBUG_INSN_P (insn))
	continue;

      /* Look for: and.l #65535, rA  */
      rtx and_reg = highword_is_and_65535_p (insn);
      if (and_reg == NULL_RTX)
	continue;

      unsigned and_regno = REGNO (and_reg);
      rtx_insn *and_insn = insn;

      /* Find next non-debug insn.  */
      rtx_insn *or_insn = NEXT_INSN (and_insn);
      while (or_insn && or_insn != NEXT_INSN (BB_END (bb))
	     && !NONDEBUG_INSN_P (or_insn))
	or_insn = NEXT_INSN (or_insn);

      if (!or_insn || or_insn == NEXT_INSN (BB_END (bb)))
	continue;

      /* Check for: or.l #high_const, rA (same register, const with no low bits)  */
      HOST_WIDE_INT or_const;
      rtx or_reg = highword_is_ior_high_const_p (or_insn, &or_const);
      if (or_reg == NULL_RTX || REGNO (or_reg) != and_regno)
	continue;

      /* Look backward for the memory load to rA.  */
      rtx mem_addr = NULL_RTX;
      rtx_insn *load_insn = NULL;
      rtx_insn *scan = PREV_INSN (and_insn);

      while (scan && scan != PREV_INSN (BB_HEAD (bb)))
	{
	  if (!NONDEBUG_INSN_P (scan))
	    {
	      scan = PREV_INSN (scan);
	      continue;
	    }

	  /* Check if this insn defines rA.  */
	  rtx load_reg = highword_is_mem_load_p (scan, &mem_addr);
	  if (load_reg != NULL_RTX && REGNO (load_reg) == and_regno)
	    {
	      load_insn = scan;
	      break;
	    }

	  /* If any other insn defines rA, abort.  */
	  if (reg_set_p (and_reg, scan))
	    break;

	  /* If any insn uses rA before the and, the load value might be needed
	     for other purposes, so we can't optimize.  */
	  if (reg_mentioned_p (and_reg, PATTERN (scan)))
	    break;

	  scan = PREV_INSN (scan);
	}

      if (!load_insn || mem_addr == NULL_RTX)
	continue;

      if (dump_file)
	{
	  fprintf (dump_file, "m68k-highword-opt: Found mask+or pattern:\n");
	  fprintf (dump_file, "  Load: ");
	  print_rtl_single (dump_file, load_insn);
	  fprintf (dump_file, "  AND:  ");
	  print_rtl_single (dump_file, and_insn);
	  fprintf (dump_file, "  OR:   ");
	  print_rtl_single (dump_file, or_insn);
	}

      /* Create the new instructions:
	 1. move.l #high_const, rA
	 2. or.w mem+2, rA  using iorsi_zext pattern  */

      /* Compute the address for the low word (addr + 2 for big-endian).  */
      rtx low_addr;
      if (CONST_INT_P (mem_addr))
	low_addr = GEN_INT (INTVAL (mem_addr) + 2);
      else if (REG_P (mem_addr))
	low_addr = gen_rtx_PLUS (Pmode, mem_addr, GEN_INT (2));
      else if (GET_CODE (mem_addr) == PLUS
	       && REG_P (XEXP (mem_addr, 0))
	       && CONST_INT_P (XEXP (mem_addr, 1)))
	low_addr = gen_rtx_PLUS (Pmode, XEXP (mem_addr, 0),
				 GEN_INT (INTVAL (XEXP (mem_addr, 1)) + 2));
      else if (GET_CODE (mem_addr) == PLUS
	       && REG_P (XEXP (mem_addr, 0))
	       && GET_CODE (XEXP (mem_addr, 1)) == PLUS)
	{
	  /* Indexed addressing: (plus reg (plus reg const)) */
	  rtx base = XEXP (mem_addr, 0);
	  rtx index_part = XEXP (mem_addr, 1);
	  if (REG_P (XEXP (index_part, 0)) && CONST_INT_P (XEXP (index_part, 1)))
	    {
	      low_addr = gen_rtx_PLUS (Pmode, base,
				       gen_rtx_PLUS (Pmode,
						     XEXP (index_part, 0),
						     GEN_INT (INTVAL (XEXP (index_part, 1)) + 2)));
	    }
	  else
	    continue; /* Unsupported address form.  */
	}
      else
	continue; /* Unsupported address form.  */

      /* Create: (set rA (const_int or_const))  */
      rtx new_load_pat = gen_rtx_SET (and_reg, GEN_INT (or_const));
      rtx_insn *new_load = emit_insn_before (new_load_pat, and_insn);
      INSN_CODE (new_load) = -1;

      /* Create: (set rA (ior:SI (zero_extend:SI (mem:HI low_addr)) rA))
	 This matches the iorsi_zext pattern and generates "or.w mem, rA".  */
      rtx low_mem = gen_rtx_MEM (HImode, low_addr);
      rtx zext = gen_rtx_ZERO_EXTEND (SImode, low_mem);
      rtx new_or_pat = gen_rtx_SET (and_reg,
				    gen_rtx_IOR (SImode, zext, and_reg));
      rtx_insn *new_or = emit_insn_before (new_or_pat, and_insn);
      INSN_CODE (new_or) = -1;

      if (dump_file)
	{
	  fprintf (dump_file, "  Transformed to:\n");
	  fprintf (dump_file, "  New load: ");
	  print_rtl_single (dump_file, new_load);
	  fprintf (dump_file, "  New OR:   ");
	  print_rtl_single (dump_file, new_or);
	}

      /* Delete the original instructions.  */
      delete_insn (load_insn);
      delete_insn (and_insn);
      delete_insn (or_insn);

      /* Update dataflow.  */
      df_insn_rescan (new_load);
      df_insn_rescan (new_or);

      changed = true;
      insn = NEXT_INSN (new_or);
    }

  return changed;
}

/* Main function for the highword_opt pass.  */

static unsigned int
m68k_highword_opt (function *func)
{
  unsigned int changes = 0;

  if (dump_file)
    fprintf (dump_file, "m68k-highword-opt: Starting pass\n");

  basic_block bb;
  FOR_EACH_BB_FN (bb, func)
    {
      if (dump_file)
	fprintf (dump_file, "m68k-highword-opt: Processing BB %d\n", bb->index);

      /* Run each optimization. Order matters:
	 1. Extraction first (simplest)
	 2. Computation second (depends on swap being present)
	 3. Insertion (most complex struct field insertion)
	 4. Mask+or (memory load + mask + or pattern)  */

      if (highword_optimize_extraction (bb))
	changes++;

      if (highword_optimize_computation (bb))
	changes++;

      if (highword_optimize_insertion (bb))
	changes++;

      if (highword_optimize_mask_or (bb))
	changes++;
    }

  if (dump_file)
    fprintf (dump_file, "m68k-highword-opt: Pass complete, %d changes\n",
	     changes);

  return 0;
}

/* Pass data for m68k_pass_highword_opt.  */

const pass_data m68k_pass_data_highword_opt =
{
  RTL_PASS,		   /* type */
  "m68k-highword-opt",	   /* name */
  OPTGROUP_NONE,	   /* optinfo_flags */
  TV_MACH_DEP,		   /* tv_id */
  0,			   /* properties_required */
  0,			   /* properties_provided */
  0,			   /* properties_destroyed */
  0,			   /* todo_flags_start */
  TODO_df_finish	   /* todo_flags_finish */
};

/* The pass class for highword_opt.  */

class m68k_pass_highword_opt : public rtl_opt_pass
{
public:
  m68k_pass_highword_opt (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_highword_opt, ctxt)
  {}

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_highword_opt;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_highword_opt (func);
  }

}; /* class m68k_pass_highword_opt */

/* -----------------------------------------------------------------------
   Available Copy Elimination Pass

   After inc_dec converts forward-propagated copies back into reg-reg copies
   (e.g., in unrolled loop peels), some copies are redundant because the
   same value is already established on all incoming paths.  This pass
   detects and deletes such copies before IRA, allowing the allocator to
   coalesce the registers and avoid unnecessary move instructions.
   ----------------------------------------------------------------------- */

/* Check if (set DEST SRC) is available at the entry of BB by walking
   predecessors backwards.  DEPTH limits the search to avoid unbounded
   recursion.  Returns true if all predecessor paths establish DEST == SRC
   without any intervening modification of either register.  */

static bool
copy_available_at_entry (basic_block bb, rtx dest, rtx src, int depth)
{
  if (depth <= 0)
    return false;

  edge e;
  edge_iterator ei;

  /* Must have at least one predecessor.  */
  if (EDGE_COUNT (bb->preds) == 0)
    return false;

  FOR_EACH_EDGE (e, ei, bb->preds)
    {
      basic_block pred = e->src;
      bool found = false;

      /* Walk backwards through predecessor's insns.  */
      rtx_insn *insn;
      FOR_BB_INSNS_REVERSE (pred, insn)
	{
	  if (!NONDEBUG_INSN_P (insn))
	    continue;

	  rtx set = single_set (insn);
	  if (set && rtx_equal_p (SET_DEST (set), dest)
	      && rtx_equal_p (SET_SRC (set), src))
	    {
	      /* Found the copy — available on this path.  */
	      found = true;
	      break;
	    }

	  /* If either register is modified, the copy is not available.  */
	  if (reg_set_p (dest, insn) || reg_set_p (src, insn))
	    return false;
	}

      if (!found)
	{
	  /* Reached start of predecessor without finding copy.
	     Recurse into predecessor's predecessors.  */
	  if (!copy_available_at_entry (pred, dest, src, depth - 1))
	    return false;
	}
    }

  return true;
}

/* Main function for the available copy elimination pass.  */

static unsigned int
m68k_avail_copy_elim (function *func)
{
  unsigned int changes = 0;

  if (dump_file)
    fprintf (dump_file, "m68k-avail-copy-elim: Starting pass\n");

  basic_block bb;
  FOR_EACH_BB_FN (bb, func)
    {
      /* Find the first non-debug insn in this BB.  */
      rtx_insn *insn;
      FOR_BB_INSNS (bb, insn)
	{
	  if (NONDEBUG_INSN_P (insn))
	    break;
	}

      if (!insn || !NONDEBUG_INSN_P (insn))
	continue;

      rtx set = single_set (insn);
      if (!set)
	continue;

      rtx dest = SET_DEST (set);
      rtx src = SET_SRC (set);

      /* Only handle simple reg-to-reg copies.  */
      if (!REG_P (dest) || !REG_P (src))
	continue;

      if (copy_available_at_entry (bb, dest, src, 5))
	{
	  if (dump_file)
	    {
	      fprintf (dump_file,
		       "m68k-avail-copy-elim: BB %d: deleting redundant copy "
		       "r%d = r%d\n",
		       bb->index, REGNO (dest), REGNO (src));
	    }

	  delete_insn (insn);
	  changes++;
	}
    }

  if (dump_file)
    fprintf (dump_file,
	     "m68k-avail-copy-elim: Pass complete, %d changes\n", changes);

  return 0;
}

/* Pass data for m68k_pass_avail_copy_elim.  */

const pass_data m68k_pass_data_avail_copy_elim =
{
  RTL_PASS,		       /* type */
  "m68k-avail-copy-elim",     /* name */
  OPTGROUP_NONE,	       /* optinfo_flags */
  TV_MACH_DEP,		       /* tv_id */
  0,			       /* properties_required */
  0,			       /* properties_provided */
  0,			       /* properties_destroyed */
  0,			       /* todo_flags_start */
  0			       /* todo_flags_finish */
};

/* The pass class for avail_copy_elim.  */

class m68k_pass_avail_copy_elim : public rtl_opt_pass
{
public:
  m68k_pass_avail_copy_elim (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_avail_copy_elim, ctxt)
  {}

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_avail_copy_elim;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_avail_copy_elim (func);
  }

}; /* class m68k_pass_avail_copy_elim */



/* =======================================================================
   RTL pass: m68k_pass_reorder_for_cc

   Reorder loads so that the register tested by a conditional branch is
   set by the immediately preceding instruction.  On m68k, move instructions
   set condition codes, and the final pass can elide a tst instruction when
   the preceding move already sets CC for the tested register.

   Example (test_mintlib_strcmp hot loop):
     Before:
       move.b (%a0),%d0        ; CC set for d0
       move.b (%a1),%d1        ; CC now reflects d1
       tst.b %d0               ; must re-test d0
       jeq .L431

     After:
       move.b (%a1),%d1        ; CC reflects d1
       move.b (%a0),%d0        ; CC reflects d0
       jeq .L431               ; tst.b elided

   The pass handles two cases:
   1. Within-BB reorder: move the load of the tested register down to
      right before the branch, when safe.
   2. Cross-BB sink: move a load from a predecessor BB into the current
      BB right before the branch.  */

/* Extract the register tested against zero in a conditional branch.
   Returns the register rtx, or NULL_RTX if not a simple zero test
   of a data register.  */

static rtx
cc_branch_tested_reg (rtx_insn *branch)
{
  rtx pat = PATTERN (branch);
  if (GET_CODE (pat) != SET)
    return NULL_RTX;

  rtx cond = XEXP (pat, 1);
  if (GET_CODE (cond) != IF_THEN_ELSE)
    return NULL_RTX;

  rtx test = XEXP (cond, 0);
  rtx_code code = GET_CODE (test);
  if (code != EQ && code != NE)
    return NULL_RTX;

  rtx op0 = XEXP (test, 0);
  rtx op1 = XEXP (test, 1);

  if (!REG_P (op0) || !CONST_INT_P (op1) || INTVAL (op1) != 0)
    return NULL_RTX;

  if (!DATA_REG_P (op0))
    return NULL_RTX;

  return op0;
}

/* Get the previous NONDEBUG_INSN_P before INSN in basic block BB.  */

static rtx_insn *
prev_nondebug_insn_bb (basic_block bb, rtx_insn *insn)
{
  while (insn)
    {
      insn = PREV_INSN (insn);
      if (!insn || BLOCK_FOR_INSN (insn) != bb)
	return nullptr;
      if (NONDEBUG_INSN_P (insn))
	return insn;
    }
  return nullptr;
}

/* Check whether INSN is a simple load (MEM to REG) setting TARGET_REG.  */

static bool
is_simple_load_of (rtx_insn *insn, rtx target_reg)
{
  rtx set = single_set (insn);
  if (!set)
    return false;

  rtx dest = SET_DEST (set);
  rtx src = SET_SRC (set);

  return (REG_P (dest)
	  && REGNO (dest) == REGNO (target_reg)
	  && MEM_P (src)
	  && !MEM_VOLATILE_P (src));
}

/* Check if any MEM operand in INSN is volatile.  */

static bool
has_volatile_mem (rtx_insn *insn)
{
  rtx set = single_set (insn);
  if (!set)
    return true;

  rtx src = SET_SRC (set);
  rtx dest = SET_DEST (set);

  if (MEM_P (src) && MEM_VOLATILE_P (src))
    return true;
  if (MEM_P (dest) && MEM_VOLATILE_P (dest))
    return true;

  return false;
}

/* Collect all registers mentioned in the address of the MEM source
   of a load instruction.  Returns the address rtx.  */

static rtx
load_source_addr (rtx_insn *insn)
{
  rtx set = single_set (insn);
  if (!set)
    return NULL_RTX;
  rtx src = SET_SRC (set);
  if (!MEM_P (src))
    return NULL_RTX;
  return XEXP (src, 0);
}

/* Check whether a load of TESTED_REG (with source address ADDR) can
   safely be moved past INSN.  Returns true if INSN does not interfere
   with the load in any way.  */

static bool
can_move_load_past_p (rtx_insn *insn, rtx tested_reg, rtx addr)
{
  if (!NONDEBUG_INSN_P (insn) || CALL_P (insn) || JUMP_P (insn))
    return false;

  rtx iset = single_set (insn);
  if (!iset)
    return false;

  if (reg_overlap_mentioned_p (tested_reg, PATTERN (insn)))
    return false;

  if (modified_in_p (addr, insn))
    return false;

  if (MEM_P (SET_DEST (iset)))
    return false;

  if (has_volatile_mem (insn))
    return false;

  return true;
}

/* Check that all non-debug insns in [FROM, TO) are safe to move a load
   past.  FROM and TO may be in different BBs; iteration stops at TO or
   when BLOCK_FOR_INSN changes from the starting BB.  */

static bool
range_safe_to_move_load_p (rtx_insn *from, rtx_insn *to,
			   rtx tested_reg, rtx addr)
{
  basic_block bb = BLOCK_FOR_INSN (from);
  for (rtx_insn *insn = from; insn && insn != to; insn = NEXT_INSN (insn))
    {
      if (BLOCK_FOR_INSN (insn) != bb)
	return false;
      if (!NONDEBUG_INSN_P (insn))
	continue;
      if (!can_move_load_past_p (insn, tested_reg, addr))
	return false;
    }
  return true;
}

/* Try within-BB reorder: move TARGET_LOAD down to just before BRANCH.
   Returns true on success.  */

static bool
try_within_bb_reorder (basic_block bb, rtx_insn *target_load,
		       rtx_insn *branch, rtx tested_reg)
{
  rtx addr = load_source_addr (target_load);
  if (!addr)
    return false;

  rtx_insn *after = NEXT_INSN (target_load);
  if (!range_safe_to_move_load_p (after, branch, tested_reg, addr))
    return false;

  remove_insn (target_load);
  add_insn_before (target_load, branch, bb);
  df_insn_rescan (target_load);

  return true;
}

/* Try cross-BB sink: move a load of TESTED_REG from a predecessor into BB,
   right before BRANCH.  Returns true on success.  */

static bool
try_cross_bb_sink (basic_block bb, rtx_insn *branch, rtx tested_reg)
{
  if (!single_pred_p (bb))
    return false;

  basic_block pred = single_pred (bb);

  /* Find the last real insn in pred.  */
  rtx_insn *pred_end = BB_END (pred);
  while (pred_end && !NONDEBUG_INSN_P (pred_end))
    pred_end = PREV_INSN (pred_end);
  if (!pred_end || BLOCK_FOR_INSN (pred_end) != pred)
    return false;

  /* If pred ends with a conditional jump, don't sink — it has multiple
     successors and the load may not reach all of them.  */
  if (JUMP_P (pred_end) && any_condjump_p (pred_end))
    return false;

  /* Search backward in pred for a load of tested_reg.  */
  rtx_insn *target_load = nullptr;
  for (rtx_insn *insn = pred_end; insn && BLOCK_FOR_INSN (insn) == pred;
       insn = PREV_INSN (insn))
    {
      if (!NONDEBUG_INSN_P (insn))
	continue;
      if (is_simple_load_of (insn, tested_reg))
	{
	  target_load = insn;
	  break;
	}
      /* If something else sets tested_reg, stop.  */
      if (reg_set_p (tested_reg, insn))
	return false;
    }

  if (!target_load)
    return false;

  rtx addr = load_source_addr (target_load);
  if (!addr)
    return false;

  /* Check insns after the load in pred, then insns before the branch in bb.  */
  rtx_insn *after = NEXT_INSN (target_load);
  if (!range_safe_to_move_load_p (after, BB_END (pred), tested_reg, addr)
      || !range_safe_to_move_load_p (BB_HEAD (bb), branch, tested_reg, addr))
    return false;

  remove_insn (target_load);
  add_insn_before (target_load, branch, bb);
  df_insn_rescan (target_load);

  return true;
}

/* Main function: reorder loads for CC-based tst elimination.  */

static unsigned int
m68k_reorder_for_cc (function *func)
{
  bool changed = false;
  basic_block bb;

  df_analyze ();

  FOR_EACH_BB_FN (bb, func)
    {
      rtx_insn *branch = BB_END (bb);
      if (!JUMP_P (branch) || !any_condjump_p (branch))
	continue;

      rtx tested_reg = cc_branch_tested_reg (branch);
      if (!tested_reg)
	continue;

      /* Find the insn immediately before the branch.  */
      rtx_insn *prev = prev_nondebug_insn_bb (bb, branch);
      if (!prev)
	{
	  /* BB has only the branch — try cross-BB sink.  */
	  if (try_cross_bb_sink (bb, branch, tested_reg))
	    changed = true;
	  continue;
	}

      /* If prev already sets the tested register, CC is optimal.  */
      if (reg_set_p (tested_reg, prev))
	continue;

      /* Search backward for a load of tested_reg within this BB.  */
      rtx_insn *target_load = nullptr;
      for (rtx_insn *insn = prev; insn && BLOCK_FOR_INSN (insn) == bb;
	   insn = prev_nondebug_insn_bb (bb, insn))
	{
	  if (is_simple_load_of (insn, tested_reg))
	    {
	      target_load = insn;
	      break;
	    }
	  /* If something else defines tested_reg, stop.  */
	  if (reg_set_p (tested_reg, insn))
	    break;
	}

      if (target_load)
	{
	  if (try_within_bb_reorder (bb, target_load, branch, tested_reg))
	    changed = true;
	}
      else
	{
	  /* No definition in this BB — try cross-BB sink.  */
	  if (try_cross_bb_sink (bb, branch, tested_reg))
	    changed = true;
	}
    }

  if (changed)
    df_analyze ();

  return 0;
}

/* Pass data for reorder_for_cc.  */

const pass_data m68k_pass_data_reorder_for_cc =
{
  RTL_PASS,		    /* type */
  "m68k-reorder-cc",	    /* name */
  OPTGROUP_NONE,	    /* optinfo_flags */
  TV_MACH_DEP,		    /* tv_id */
  0,			    /* properties_required */
  0,			    /* properties_provided */
  0,			    /* properties_destroyed */
  0,			    /* todo_flags_start */
  TODO_df_finish	    /* todo_flags_finish */
};

/* The pass class for reorder_for_cc.  */

class m68k_pass_reorder_for_cc : public rtl_opt_pass
{
public:
  m68k_pass_reorder_for_cc (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_reorder_for_cc, ctxt)
  {}

  bool gate (function *) final override
  {
    return optimize > 0;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_reorder_for_cc (func);
  }

}; /* class m68k_pass_reorder_for_cc */

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

/* Factory function for m68k_pass_elim_andi.  */

rtl_opt_pass *
make_m68k_pass_elim_andi (gcc::context *ctxt)
{
  return new m68k_pass_elim_andi (ctxt);
}

/* Factory function for m68k_pass_highword_opt.  */

rtl_opt_pass *
make_m68k_pass_highword_opt (gcc::context *ctxt)
{
  return new m68k_pass_highword_opt (ctxt);
}

/* Factory function for m68k_pass_avail_copy_elim.  */

rtl_opt_pass *
make_m68k_pass_avail_copy_elim (gcc::context *ctxt)
{
  return new m68k_pass_avail_copy_elim (ctxt);
}

/* Factory function for m68k_pass_reorder_for_cc.  */

rtl_opt_pass *
make_m68k_pass_reorder_for_cc (gcc::context *ctxt)
{
  return new m68k_pass_reorder_for_cc (ctxt);
}
