/* Miscellaneous optimization passes for Motorola 68k.
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

/* RTL pass: m68k_pass_reorder_for_cc

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
  rtx pat = pc_set (branch);
  if (!pat)
    return NULL_RTX;

  rtx cond = SET_SRC (pat);
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

  if (volatile_refs_p (PATTERN (insn)))
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
      rtx_insn *prev = prev_nonnote_nondebug_insn_bb (branch);
      if (!prev)
	{
	  /* BB has only the branch — try cross-BB sink.  */
	  try_cross_bb_sink (bb, branch, tested_reg);
	  continue;
	}

      /* If prev already sets the tested register, CC is optimal.  */
      if (reg_set_p (tested_reg, prev))
	continue;

      /* Search backward for a load of tested_reg within this BB.  */
      rtx_insn *target_load = nullptr;
      for (rtx_insn *insn = prev; insn && BLOCK_FOR_INSN (insn) == bb;
	   insn = prev_nonnote_nondebug_insn_bb (insn))
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
	try_within_bb_reorder (bb, target_load, branch, tested_reg);
      else
	try_cross_bb_sink (bb, branch, tested_reg);
    }

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

} /* Anonymous namespace.  */

/* Factory function for m68k_pass_reorder_for_cc.  */

rtl_opt_pass *
make_m68k_pass_reorder_for_cc (gcc::context *ctxt)
{
  return new m68k_pass_reorder_for_cc (ctxt);
}
