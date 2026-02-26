/* Doloop (dbra) optimization hooks for Motorola 68k.
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
#include "gimple.h"
#include "tree-pass.h"
#include "ssa.h"
#include "gimple-iterator.h"
#include "cfgloop.h"
#include "tree-scalar-evolution.h"
#include "gimple-ssa.h"
#include "tree-phinodes.h"
#include "ssa-iterators.h"
#include "gimple-pretty-print.h"
#include "tree-pretty-print.h"
#include "df.h"
#include "memmodel.h"
#include "tm_p.h"
#include "insn-config.h"
#include "regs.h"
#include "emit-rtl.h"
#include "recog.h"
#include "cfgrtl.h"
#include "m68k-util.h"

/* dbra counts from N-1 down to -1, so it can handle up to 65536 iterations.  */
static const int DBRA_MAX_ITERATIONS = 65536;

/* Check whether the exit IV of LOOP has uses in the loop body beyond
   the exit test and its own increment.  If it does, the doloop pass
   would create a redundant count-down IV (it never reuses the exit IV),
   wasting a register.

   Returns true if the exit IV has body uses (doloop should be avoided).  */

static bool
exit_iv_has_gimple_body_uses (class loop *loop)
{
  edge exit_e = single_dom_exit (loop);
  if (!exit_e)
    return false;

  gcond *exit_cond = get_loop_exit_condition (exit_e);
  if (!exit_cond)
    return false;

  /* Extract the IV SSA name from the exit condition.  One operand is
     typically the IV, the other is the bound (constant or invariant).  */
  tree lhs = gimple_cond_lhs (exit_cond);
  tree rhs = gimple_cond_rhs (exit_cond);
  tree exit_iv = NULL_TREE;

  if (TREE_CODE (lhs) == SSA_NAME)
    {
      gimple *def = SSA_NAME_DEF_STMT (lhs);
      if (def && gimple_bb (def)
	  && flow_bb_inside_loop_p (loop, gimple_bb (def)))
	exit_iv = lhs;
    }
  if (!exit_iv && TREE_CODE (rhs) == SSA_NAME)
    {
      gimple *def = SSA_NAME_DEF_STMT (rhs);
      if (def && gimple_bb (def)
	  && flow_bb_inside_loop_p (loop, gimple_bb (def)))
	exit_iv = rhs;
    }

  if (!exit_iv)
    return false;

  /* Walk UP the def chain from exit_iv to find the PHI at the loop header.
     The IV may pass through casts (NOP_EXPR) and arithmetic (PLUS_EXPR)
     between the PHI and the exit comparison.  Collect the intermediate
     stmts as the "increment chain" — these are not body uses.

     Example: j_40 = PHI<0, j_34>
              j.1_17 = (unsigned short) j_40    ← incr chain
              _18 = j.1_17 + 1                  ← incr chain
              j_34 = (int16_t) _18              ← incr chain
              if (n > j_34)                     ← exit cond  */
  auto_vec<gimple *, 8> incr_chain;
  gphi *iv_phi = NULL;
  tree phi_result = NULL_TREE;

  {
    tree name = exit_iv;
    for (int depth = 0; depth < 8; depth++)
      {
	gimple *def = SSA_NAME_DEF_STMT (name);
	if (gimple_code (def) == GIMPLE_PHI
	    && gimple_bb (def) == loop->header)
	  {
	    iv_phi = as_a<gphi *> (def);
	    phi_result = name;
	    break;
	  }
	if (gimple_code (def) != GIMPLE_ASSIGN)
	  break;

	incr_chain.safe_push (def);

	/* Walk up: find the first SSA_NAME operand defined inside the loop.  */
	bool found = false;
	for (unsigned i = 1; i < gimple_num_ops (def); i++)
	  {
	    tree op = gimple_op (def, i);
	    if (op && TREE_CODE (op) == SSA_NAME)
	      {
		gimple *op_def = SSA_NAME_DEF_STMT (op);
		if (op_def && gimple_bb (op_def)
		    && flow_bb_inside_loop_p (loop, gimple_bb (op_def)))
		  {
		    name = op;
		    found = true;
		    break;
		  }
	      }
	  }
	if (!found)
	  break;
      }
  }

  if (!iv_phi || !phi_result)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "m68k doloop: cannot find IV PHI "
		 "for exit condition.\n");
      return false;
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "m68k doloop: checking exit IV PHI result ");
      print_generic_expr (dump_file, phi_result);
      fprintf (dump_file, " for body uses.\n");
    }

  /* Check uses of the PHI result (pre-increment IV value).
     Any use inside the loop that is not the exit condition, not the PHI,
     and not part of the increment chain is a body use.  */
  use_operand_p use_p;
  imm_use_iterator iter;
  FOR_EACH_IMM_USE_FAST (use_p, iter, phi_result)
    {
      gimple *use_stmt = USE_STMT (use_p);

      if (is_gimple_debug (use_stmt))
	continue;
      if (use_stmt == exit_cond)
	continue;
      if (use_stmt == iv_phi)
	continue;

      /* Skip stmts in the increment chain.  */
      bool in_chain = false;
      for (unsigned i = 0; i < incr_chain.length (); i++)
	if (use_stmt == incr_chain[i])
	  {
	    in_chain = true;
	    break;
	  }
      if (in_chain)
	continue;

      basic_block use_bb = gimple_bb (use_stmt);
      if (!use_bb || !flow_bb_inside_loop_p (loop, use_bb))
	continue;

      /* This is a body use of the exit IV.  */
      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, "m68k doloop: exit IV ");
	  print_generic_expr (dump_file, phi_result);
	  fprintf (dump_file, " has body use in: ");
	  print_gimple_stmt (dump_file, use_stmt, 0, TDF_SLIM);
	}
      return true;
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "m68k doloop: exit IV has no body uses.\n");

  return false;
}

/* Implement TARGET_CAN_USE_DOLOOP_P.
   The dbra instruction operates only on the low 16 bits of a data register,
   supporting a maximum of 65536 iterations (counting from 65535 down to -1).  */

bool
m68k_can_use_doloop_p (const widest_int &iterations,
		       const widest_int &iterations_max,
		       unsigned int loop_depth,
		       bool entered_at_top ATTRIBUTE_UNUSED)
{
  if (!flag_m68k_doloop)
    return false;

  /* ColdFire doesn't have dbra.  */
  if (TARGET_COLDFIRE)
    return false;

  /* Allow up to two levels of loop nesting for dbra.  Each dbra loop
     typically uses ~2 IV registers, so 2 nested loops use ~4 registers,
     roughly 25% of the available register set.  This keeps register
     pressure manageable.  Deeper nesting has diminishing returns.  */
  if (loop_depth > 2)
    return false;

  /* If we know the exact iteration count, check it fits in 16 bits.
     dbra can do up to 65536 iterations (counter 65535 down to -1).  */
  if (iterations != 0)
    return wi::leu_p (iterations, DBRA_MAX_ITERATIONS);

  /* Unknown exact iteration count - check the maximum bound.
     iterations_max == 0 means the maximum is also unknown.  */
  if (iterations_max == 0)
    {
      /* Both iteration count and maximum are unknown.
	 We cannot safely use dbra since we can't guarantee
	 the count fits in 16 bits.  */
      return false;
    }

  /* Maximum is known - check it fits in 16 bits.  */
  return wi::leu_p (iterations_max, DBRA_MAX_ITERATIONS);
}

/* Implement TARGET_PREFERRED_DOLOOP_MODE.
   Always return HImode since dbra operates on 16-bit values.
   The can_use_doloop_p hook ensures iteration counts fit in 16 bits.  */

machine_mode
m68k_preferred_doloop_mode (machine_mode mode ATTRIBUTE_UNUSED)
{
  return HImode;
}

/* Implement TARGET_PREDICT_DOLOOP_P.
   This helps IVOPTS preserve count-based IVs when doloop is likely to be used.
   Without this, IVOPTS at -O2 may transform counted loops into pointer-based
   loops before the DOLOOP pass runs, preventing dbra usage.

   We also check whether the exit IV has uses in the loop body beyond the
   exit test and its own increment.  If it does, the doloop pass would create
   a redundant count-down register (it never reuses the exit IV), wasting a
   data register and potentially causing spills.  In that case we return false
   so IVOPTS does not create a doloop IV candidate.  */

bool
m68k_predict_doloop_p (class loop *loop)
{
  if (!flag_m68k_doloop)
    return false;

  /* ColdFire doesn't have dbra.  */
  if (TARGET_COLDFIRE)
    return false;

  /* Check iteration bounds if available.
     dbra can handle up to 65536 iterations.  */
  if (loop->any_upper_bound
      && wi::gtu_p (loop->nb_iterations_upper_bound, DBRA_MAX_ITERATIONS))
    return false;

  /* For loops with inner loops, check that the outer loop body
     (excluding inner loops) doesn't contain function calls.
     Function calls clobber 4 or 5 caller-saved registers, so avoiding dbra
     in outer loops with calls keeps register pressure under ~25% of the
     register set.  Inner loops still benefit from dbra since they are
     typically hotter and gain more from the optimization.  */
  if (loop->inner != NULL)
    {
      basic_block *bbs = get_loop_body (loop);
      unsigned n_bbs = loop->num_nodes;

      for (unsigned i = 0; i < n_bbs; i++)
	{
	  basic_block bb = bbs[i];

	  /* Skip BBs that are part of inner loops.  */
	  if (bb->loop_father != loop)
	    continue;

	  /* Check all statements in this BB for calls.  */
	  for (gimple_stmt_iterator gsi = gsi_start_bb (bb);
	       !gsi_end_p (gsi); gsi_next (&gsi))
	    {
	      gimple *stmt = gsi_stmt (gsi);
	      if (is_gimple_call (stmt)
		  && !gimple_call_internal_p (stmt))
		{
		  free (bbs);
		  return false;
		}
	    }
	}
      free (bbs);
    }

  /* Check if the exit IV has body uses.  If so, doloop would add a
     redundant count-down register alongside the existing exit IV.  */
  if (exit_iv_has_gimple_body_uses (loop))
    return false;

  /* Predict doloop will be used - tell IVOPTS to preserve count-based IV.  */
  return true;
}

/* Implement TARGET_INVALID_WITHIN_DOLOOP.
   Like the default hook but without the CALL_P rejection.  m68k's dbra uses
   a regular data register for its counter, so calls (which preserve
   callee-saved registers) cannot clobber it.  */

const char *
m68k_invalid_within_doloop (const rtx_insn *insn)
{
  if (tablejump_p (insn, NULL, NULL) || computed_jump_p (insn))
    return "Computed branch in the loop.";
  return NULL;
}

/* RTL-level safety net: check if adding a doloop counter would be harmful.

   The doloop pass creates a fresh count-down register (it never reuses the
   exit IV).  This is always safe when the exit IV has no other uses in the
   loop body — the counter simply replaces the exit comparison.

   When the exit IV DOES have body uses, the counter is redundant: the exit
   IV register must still be maintained for its body uses.  Whether this
   redundancy actually causes harm depends on register pressure.  With low
   pressure, the extra register is free.  With high pressure, it causes
   spills — often to address registers where dbra cannot operate, resulting
   in a slower subq/cmp/jne sequence.

   This function checks both conditions:
   1. Does the exit IV register have uses in the loop body?
   2. If so, is register pressure high enough that the extra register hurts?

   Returns true if doloop should FAIL (exit IV has body uses AND pressure
   is high).  */

/* Register count threshold.  When the exit IV has body uses AND the
   total number of distinct pseudo registers in the loop reaches this,
   adding a doloop counter will likely cause spills.
   m68k has 5 caller-saved registers (d0, d1, d2, a0, a1).  With body
   uses, the doloop counter is redundant — once the loop body needs
   more pseudos than the caller-saved set can hold, the extra counter
   eats into callee-saved registers and risks spills.  */
static const int DOLOOP_REG_COUNT_THRESHOLD = 5;

/* Find the loop from a doloop_end label operand.  The doloop pass passes
   a CODE_LABEL (from block_label()) pointing to the latch block.  */

static class loop *
loop_from_doloop_label (rtx label_ref)
{
  rtx label;
  if (LABEL_REF_P (label_ref))
    label = XEXP (label_ref, 0);
  else if (LABEL_P (label_ref))
    label = label_ref;
  else
    return NULL;

  rtx_insn *label_insn = safe_as_a<rtx_insn *> (label);
  if (!label_insn)
    return NULL;

  basic_block label_bb = BLOCK_FOR_INSN (label_insn);
  if (!label_bb)
    return NULL;

  class loop *loop = label_bb->loop_father;
  if (!loop || loop->num == 0)
    return NULL;

  return loop;
}

/* Count the total number of distinct pseudo registers referenced in
   all insns of LOOP.  This captures both live-in values and temporaries
   created within the loop body, giving a better estimate of register
   demand than df_get_live_in alone.  */

static int
loop_pseudo_reg_count (class loop *loop)
{
  basic_block *body = get_loop_body (loop);
  unsigned n_bbs = loop->num_nodes;
  auto_bitmap regs_seen;

  for (unsigned i = 0; i < n_bbs; i++)
    {
      basic_block bb = body[i];
      rtx_insn *insn;
      FOR_BB_INSNS (bb, insn)
	{
	  if (!NONDEBUG_INSN_P (insn))
	    continue;
	  df_ref ref;
	  FOR_EACH_INSN_DEF (ref, insn)
	    {
	      unsigned r = DF_REF_REGNO (ref);
	      if (r >= FIRST_PSEUDO_REGISTER)
		bitmap_set_bit (regs_seen, r);
	    }
	  FOR_EACH_INSN_USE (ref, insn)
	    {
	      unsigned r = DF_REF_REGNO (ref);
	      if (r >= FIRST_PSEUDO_REGISTER)
		bitmap_set_bit (regs_seen, r);
	    }
	}
    }

  free (body);
  return bitmap_count_bits (regs_seen);
}

/* Count uses of REGNO in the loop body beyond the exit comparison
   and its own increment.  Returns the number of insns that reference it.  */

static int
count_iv_rtl_body_uses (class loop *loop, unsigned int iv_regno)
{
  edge exit_e = single_exit (loop);
  if (!exit_e)
    return 0;

  basic_block exit_bb = exit_e->src;
  rtx_insn *tail = BB_END (exit_bb);

  basic_block *body = get_loop_body (loop);
  unsigned n_bbs = loop->num_nodes;
  int use_count = 0;

  for (unsigned i = 0; i < n_bbs; i++)
    {
      basic_block bb = body[i];
      rtx_insn *insn;
      FOR_BB_INSNS (bb, insn)
	{
	  if (!NONDEBUG_INSN_P (insn))
	    continue;

	  /* Skip the exit jump.  */
	  if (insn == tail)
	    continue;

	  /* Skip the IV increment: (set (reg iv) (plus (reg iv) (const))).  */
	  int incr_regno;
	  HOST_WIDE_INT incr_val;
	  if (m68k_is_reg_increment (insn, &incr_regno, &incr_val)
	      && (unsigned int) incr_regno == iv_regno)
	    continue;

	  /* Count insns that mention the IV register.  */
	  if (reg_mentioned_p (regno_reg_rtx[iv_regno], PATTERN (insn)))
	    use_count++;
	}
    }

  free (body);
  return use_count;
}

/* Find the IV register from the exit comparison of LOOP.  Returns the
   register number, or INVALID_REGNUM if not found.  */

static unsigned int
find_exit_iv_regno (class loop *loop)
{
  edge exit_e = single_exit (loop);
  if (!exit_e)
    return INVALID_REGNUM;

  basic_block exit_bb = exit_e->src;
  rtx_insn *tail = BB_END (exit_bb);
  if (!JUMP_P (tail))
    return INVALID_REGNUM;

  /* Try the jump pattern: (set (pc) (if_then_else (cond ...) ...)).  */
  rtx jump_pat = PATTERN (tail);
  if (GET_CODE (jump_pat) == SET
      && GET_CODE (SET_SRC (jump_pat)) == IF_THEN_ELSE)
    {
      rtx cond = XEXP (SET_SRC (jump_pat), 0);
      if (COMPARISON_P (cond))
	{
	  rtx op0 = XEXP (cond, 0);
	  rtx op1 = XEXP (cond, 1);
	  if (REG_P (op0) && CONST_INT_P (op1))
	    return REGNO (op0);
	  if (CONST_INT_P (op0) && REG_P (op1))
	    return REGNO (op1);
	  if (REG_P (op0) && REG_P (op1))
	    {
	      /* Two registers: the IV is the one set in the exit BB.  */
	      for (rtx_insn *insn = PREV_INSN (tail);
		   insn && insn != PREV_INSN (BB_HEAD (exit_bb));
		   insn = PREV_INSN (insn))
		{
		  if (!NONDEBUG_INSN_P (insn))
		    continue;
		  rtx set = single_set (insn);
		  if (!set)
		    continue;
		  rtx dest = SET_DEST (set);
		  if (REG_P (dest))
		    {
		      if (REGNO (dest) == REGNO (op0))
			return REGNO (op0);
		      if (REGNO (dest) == REGNO (op1))
			return REGNO (op1);
		    }
		}
	    }
	}
    }

  /* Fall back: look for a COMPARE insn.  */
  for (rtx_insn *insn = PREV_INSN (tail);
       insn && insn != PREV_INSN (BB_HEAD (exit_bb));
       insn = PREV_INSN (insn))
    {
      if (!NONDEBUG_INSN_P (insn))
	continue;
      rtx set = single_set (insn);
      if (!set)
	continue;
      rtx src = SET_SRC (set);
      if (GET_CODE (src) == COMPARE)
	{
	  rtx op0 = XEXP (src, 0);
	  if (GET_CODE (op0) == PLUS && REG_P (XEXP (op0, 0)))
	    op0 = XEXP (op0, 0);
	  if (REG_P (op0))
	    return REGNO (op0);
	  break;
	}
    }

  return INVALID_REGNUM;
}

bool
m68k_doloop_exit_iv_has_body_uses (rtx label_ref)
{
  class loop *loop = loop_from_doloop_label (label_ref);
  if (!loop)
    return false;

  /* Block doloop for multi-exit loops.  On 68000, dbra (12 cycles when
     taken) costs the same as subq+jcc (4+8=12 cycles).  So converting
     a counted exit to dbra saves zero cycles per iteration.  The doloop
     setup (copying count to a new register, preheader bounds check)
     always costs extra — pure overhead with no per-iteration payoff.
     Single-exit loops benefit because doloop eliminates the exit
     comparison entirely (the count-down IS the only exit).  */
  auto_vec<edge> exits = get_loop_exit_edges (loop);
  if (exits.length () > 1)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "m68k doloop: loop %d has %d exit edges, "
		 "blocking doloop (multi-exit overhead).\n",
		 loop->num, (int) exits.length ());
      return true;
    }

  /* Find the exit IV register.  */
  unsigned int iv_regno = find_exit_iv_regno (loop);
  if (iv_regno == INVALID_REGNUM)
    return false;

  /* Count how many insns in the loop body reference the exit IV
     beyond the exit comparison and its increment.  */
  int body_uses = count_iv_rtl_body_uses (loop, iv_regno);

  if (body_uses == 0)
    {
      /* No body uses — the doloop counter simply replaces the exit
	 comparison.  Always safe.  */
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "m68k doloop: loop %d exit IV r%u has no body "
		 "uses, allowing doloop.\n", loop->num, iv_regno);
      return false;
    }

  /* Exit IV has body uses — the doloop counter will be redundant.
     Check total register demand: count distinct pseudo registers used
     in the loop body.  If the count is at or above the allocatable
     register limit, the extra counter will cause spills.  */
  int reg_count = loop_pseudo_reg_count (loop);
  bool block = reg_count >= DOLOOP_REG_COUNT_THRESHOLD;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "m68k doloop: loop %d exit IV r%u has %d body "
	     "uses, %d pseudos in loop (threshold=%d) → %s\n",
	     loop->num, iv_regno, body_uses, reg_count,
	     DOLOOP_REG_COUNT_THRESHOLD, block ? "BLOCK" : "allow");

  return block;
}
