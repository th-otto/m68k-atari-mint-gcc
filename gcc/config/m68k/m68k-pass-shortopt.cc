/* 16/32-bit optimization passes for Motorola 68k.
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
#include "ssa.h"
#include "gimple-iterator.h"
#include "gimple-pretty-print.h"
#include "cfgloop.h"
#include "dominance.h"
#include "fold-const.h"
#include "gimple-ssa.h"
#include "tree-phinodes.h"
#include "ssa-iterators.h"
#include "stor-layout.h"
#include "gimple-range.h"
#include "tree-ssa-alias.h"
#include "tree-cfg.h"
#include "tree-dfa.h"
#include "tree-into-ssa.h"
#include "predict.h"

/* ===================== GIMPLE passes ===================== */

namespace {


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

  /* The narrowed multiply is performed in signed 16-bit, so the product has
     to fit in [-32768, 32767].

     Compare in the same signedness the products were computed with.  Using
     signed comparisons on an unsigned product silently accepts the worst
     cases: 65535 * 65537 is 0xFFFFFFFF, which does not overflow 32 bits and
     reads as -1 when interpreted as signed — apparently well inside 16 bits,
     while the real value is over four billion.  That let x * 65537, the idiom
     for replicating a 16-bit pattern into both halves of a word, be narrowed
     to x * 1.  */
  if (sign == UNSIGNED)
    {
      wide_int prod_max_u = wi::umax (prod1, prod2);
      return !wi::gtu_p (prod_max_u, wi::uhwi (32767, result_prec));
    }

  wide_int prod_min = wi::smin (prod1, prod2);
  wide_int prod_max = wi::smax (prod1, prod2);

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
		       tree cst, unsigned input_prec ATTRIBUTE_UNUSED)
{
  tree hi_type = build_nonstandard_integer_type (16, false);
  tree mult_input = input;

  /* Convert input to hi_type (signed 16-bit) if needed.
     This handles 8-bit extension, 32-bit narrowing, and signedness
     conversion for 16-bit unsigned inputs.  */
  if (!useless_type_conversion_p (hi_type, TREE_TYPE (input)))
    {
      tree conv_tmp = make_ssa_name (hi_type);
      gimple *conv_stmt = gimple_build_assign (conv_tmp, NOP_EXPR, input);
      gsi_insert_before (gsi, conv_stmt, GSI_SAME_STMT);
      mult_input = conv_tmp;
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

  /* On 68020+, extb.l extends QI->SI in one instruction (4 cycles),
     same cost as ext.w for QI->HI.  Narrowing 8-bit inputs to HI
     gives no extension benefit and causes combine to produce worse
     shift-based code instead of extb.l + add.l.  */
  if (narrow_prec == 8 && TARGET_68020)
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

  /* Operand must fit in signed 16-bit [-32768, 32767].
     The narrowing converts to signed short and back, so the value must
     be representable as signed 16-bit to preserve semantics.

     Use the correct signedness when comparing range bounds: unsigned
     ranges have min/max as unsigned values, so comparing max_val > 32767
     must use unsigned comparison.  Otherwise UINT_MAX (0xFFFFFFFF)
     would be interpreted as -1 and incorrectly pass the check.  */
  signop rsign = TYPE_SIGN (TREE_TYPE (rhs1));
  wide_int hi_min = wi::shwi (-32768, 32);
  wide_int hi_max = wi::shwi (32767, 32);
  if (rsign == UNSIGNED)
    {
      /* Unsigned operand: values must be in [0, 32767] for signed short.
	 min_val is unsigned so always >= 0.  */
      if (wi::gtu_p (max_val, hi_max))
	return false;
    }
  else
    {
      if (wi::lts_p (min_val, hi_min) || wi::gts_p (max_val, hi_max))
	return false;
    }

  /* Only optimize positive constants (normal array element sizes).
     Negative constants create RTL patterns the backend can't match.  */
  wide_int cst_val = wi::to_wide (rhs2);
  if (wi::neg_p (cst_val, SIGNED))
    return false;

  if (!m68k_product_fits_16bit (min_val, max_val, cst_val, 32, rsign))
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

  if (get_range_query (fun) != get_global_range_query ())
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

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_narrow_index_mult;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_narrow_index_mult (func);
  }

}; /* class m68k_pass_narrow_index_mult */


/* =======================================================================
   GIMPLE pass: m68k_pass_narrow_const_ops

   C integer promotion widens short operands to int before bitwise
   operations.  GCC's forwprop+fold narrows AND back (pulls widening
   cast through), but does NOT narrow shifts, OR, or XOR.  This pass
   narrows constants to match sibling operand types or result truncation
   types, making entire operations narrow.

   Example - bitmask lookup through a shift:
     Before:                              After:
       _7 = _1 & 15;        (short)        _7 = _1 & 15;       (unchanged)
       _3 = (int) _7;       (widen)        _4 = (ushort)32768 >> _7;  (16-bit)
       _4 = 32768 >> _3;    (32-bit)
       _5 = (ushort) _4;    (truncate)

   Runs after forwprop1 which already narrowed AND via fold.
   ======================================================================= */

/* Try to produce a narrow version of OTHER_OP in NARROW_TYPE.
   Returns the narrowed tree, or NULL_TREE on failure.
   If ALLOW_TRUNCATE is false, only reuse a pre-narrowed source or
   narrow a fitting constant (no arbitrary truncation casts).  */

static tree
m68k_narrow_operand (gimple_stmt_iterator *gsi, tree other_op,
		     tree narrow_type, unsigned narrow_prec,
		     bool allow_truncate)
{
  signop narrow_sign = TYPE_SIGN (narrow_type);

  if (TREE_CODE (other_op) == SSA_NAME)
    {
      /* 7a: other_op comes from a widening cast of a narrow source.  */
      gimple *def = SSA_NAME_DEF_STMT (other_op);
      if (is_gimple_assign (def))
	{
	  enum tree_code code = gimple_assign_rhs_code (def);
	  if (code == NOP_EXPR || code == CONVERT_EXPR)
	    {
	      tree src = gimple_assign_rhs1 (def);
	      tree src_type = TREE_TYPE (src);
	      if (INTEGRAL_TYPE_P (src_type)
		  && TYPE_PRECISION (src_type) <= narrow_prec)
		{
		  if (useless_type_conversion_p (narrow_type, src_type))
		    return src;
		  /* Same or smaller precision, different signedness.  */
		  tree tmp = make_ssa_name (narrow_type);
		  gimple *cast = gimple_build_assign (tmp, NOP_EXPR, src);
		  gsi_insert_before (gsi, cast, GSI_SAME_STMT);
		  return tmp;
		}
	    }
	}

      /* 7c: insert truncation cast.  */
      if (!allow_truncate)
	return NULL_TREE;

      tree tmp = make_ssa_name (narrow_type);
      gimple *cast = gimple_build_assign (tmp, NOP_EXPR, other_op);
      gsi_insert_before (gsi, cast, GSI_SAME_STMT);
      return tmp;
    }
  else if (TREE_CODE (other_op) == INTEGER_CST)
    {
      /* 7b: constant that fits in narrow_type.  */
      if (!wi::fits_to_tree_p (wi::to_wide (other_op), narrow_type))
	return NULL_TREE;
      return fold_convert (narrow_type, other_op);
    }

  return NULL_TREE;
}

/* Try to narrow a bitwise or shift operation through truncation casts.

   Finds: result = (narrow_type) wide_val
   Where: wide_val = X OP CONST  (or CONST OP X)
   And:   OP is BIT_AND, BIT_IOR, BIT_XOR, or RSHIFT_EXPR

   When wide_val has multiple uses, all must be narrowing casts to the same
   precision.  The operation is narrowed once (using unsigned type) and all
   truncation uses are replaced with casts from the narrow result.  */

static bool
m68k_narrow_const_op (gimple_stmt_iterator *gsi)
{
  gimple *stmt = gsi_stmt (*gsi);

  if (!is_gimple_assign (stmt))
    return false;

  enum tree_code stmt_code = gimple_assign_rhs_code (stmt);
  if (stmt_code != NOP_EXPR && stmt_code != CONVERT_EXPR)
    return false;

  tree wide_val = gimple_assign_rhs1 (stmt);

  if (TREE_CODE (wide_val) != SSA_NAME)
    return false;

  tree wide_type = TREE_TYPE (wide_val);

  if (!INTEGRAL_TYPE_P (wide_type))
    return false;

  unsigned wide_prec = TYPE_PRECISION (wide_type);

  /* Defining stmt must be a supported binary op.  */
  gimple *def_stmt = SSA_NAME_DEF_STMT (wide_val);
  if (!is_gimple_assign (def_stmt))
    return false;

  /* LSHIFT_EXPR is excluded: left-shifting widens, so truncating
     operands first can lose significant high bits that shift into
     the narrow result range.  */
  enum tree_code op_code = gimple_assign_rhs_code (def_stmt);
  if (op_code != BIT_AND_EXPR && op_code != BIT_IOR_EXPR
      && op_code != BIT_XOR_EXPR && op_code != RSHIFT_EXPR)
    return false;

  tree rhs1 = gimple_assign_rhs1 (def_stmt);
  tree rhs2 = gimple_assign_rhs2 (def_stmt);

  /* Identify which operand is the constant.  */
  tree const_op, other_op;
  bool const_is_rhs2;
  if (TREE_CODE (rhs2) == INTEGER_CST)
    {
      const_op = rhs2;
      other_op = rhs1;
      const_is_rhs2 = true;
    }
  else if (TREE_CODE (rhs1) == INTEGER_CST)
    {
      const_op = rhs1;
      other_op = rhs2;
      const_is_rhs2 = false;
    }
  else
    return false;

  /* All uses of wide_val must be narrowing casts to the same precision.  */
  unsigned common_prec = 0;
  {
    use_operand_p use_p;
    imm_use_iterator imm_iter;
    FOR_EACH_IMM_USE_FAST (use_p, imm_iter, wide_val)
      {
	gimple *use = USE_STMT (use_p);
	if (is_gimple_debug (use))
	  continue;
	if (!is_gimple_assign (use))
	  return false;
	enum tree_code code = gimple_assign_rhs_code (use);
	if (code != NOP_EXPR && code != CONVERT_EXPR)
	  return false;
	tree lhs_type = TREE_TYPE (gimple_assign_lhs (use));
	if (!INTEGRAL_TYPE_P (lhs_type))
	  return false;
	unsigned prec = TYPE_PRECISION (lhs_type);
	if (prec >= wide_prec)
	  return false;
	if (common_prec == 0)
	  common_prec = prec;
	else if (prec != common_prec)
	  return false;
      }
  }

  if (common_prec != 8 && common_prec != 16)
    return false;

  /* Use unsigned narrow type: bitwise ops are sign-agnostic, and for
     RSHIFT with unsigned constant the shift is logical in both types.  */
  tree op_narrow_type = build_nonstandard_integer_type (common_prec, true);

  /* Constant must fit in unsigned narrow type.  */
  if (!wi::fits_to_tree_p (wi::to_wide (const_op), op_narrow_type))
    return false;

  /* For RSHIFT_EXPR, the first operand is the value being shifted.
     Arbitrary truncation (case 7c) is not safe for the value operand
     because high bits affect lower bits after shifting.  Only allow
     truncation for the shift amount (rhs2).  */
  bool allow_truncate = true;
  if (op_code == RSHIFT_EXPR && const_is_rhs2)
    allow_truncate = false;  /* other_op is rhs1 (value) */

  /* Narrow the other operand, inserting before def_stmt.  */
  gimple_stmt_iterator def_gsi = gsi_for_stmt (def_stmt);
  tree narrow_other = m68k_narrow_operand (&def_gsi, other_op, op_narrow_type,
					   common_prec, allow_truncate);
  if (narrow_other == NULL_TREE)
    return false;

  /* Create the narrow binary op before def_stmt.  */
  tree narrow_const = fold_convert (op_narrow_type, const_op);

  tree new_rhs1, new_rhs2;
  if (const_is_rhs2)
    {
      new_rhs1 = narrow_other;
      new_rhs2 = narrow_const;
    }
  else
    {
      new_rhs1 = narrow_const;
      new_rhs2 = narrow_other;
    }

  tree narrow_result = make_ssa_name (op_narrow_type);
  gimple *narrow_op = gimple_build_assign (narrow_result, op_code,
					   new_rhs1, new_rhs2);
  gimple_set_location (narrow_op, gimple_location (def_stmt));
  gsi_insert_before (&def_gsi, narrow_op, GSI_SAME_STMT);

  /* Replace all truncation uses with casts from the narrow result.
     Collect uses first since replacing modifies the use list.  */
  auto_vec<gimple *> uses;
  {
    imm_use_iterator imm_iter;
    gimple *use_stmt;
    FOR_EACH_IMM_USE_STMT (use_stmt, imm_iter, wide_val)
      {
	if (!is_gimple_debug (use_stmt))
	  uses.safe_push (use_stmt);
      }
  }

  for (unsigned i = 0; i < uses.length (); i++)
    {
      gimple *use = uses[i];
      tree use_lhs = gimple_assign_lhs (use);
      tree use_type = TREE_TYPE (use_lhs);
      gimple_stmt_iterator use_gsi = gsi_for_stmt (use);

      gimple *replacement;
      if (useless_type_conversion_p (use_type, op_narrow_type))
	replacement = gimple_build_assign (use_lhs, narrow_result);
      else
	replacement = gimple_build_assign (use_lhs, NOP_EXPR,
					   narrow_result);

      gimple_set_location (replacement, gimple_location (use));
      gsi_replace (&use_gsi, replacement, true);
    }

  /* Remove the now-dead wide binary op.  */
  gsi_remove (&def_gsi, true);
  release_defs (def_stmt);

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "m68k: Narrowed bitwise/shift op to %d-bit "
	       "(%u uses):\n", common_prec, uses.length ());
      print_gimple_stmt (dump_file, narrow_op, 0, TDF_SLIM);
    }

  return true;
}

/* Main function for the narrow_const_ops pass.  */

static unsigned int
m68k_narrow_const_ops (function *fun)
{
  unsigned int changes = 0;
  basic_block bb;

  FOR_EACH_BB_FN (bb, fun)
    {
      for (gimple_stmt_iterator gsi = gsi_start_bb (bb);
	   !gsi_end_p (gsi); gsi_next (&gsi))
	{
	  if (m68k_narrow_const_op (&gsi))
	    changes++;
	}
    }

  return changes ? TODO_update_ssa : 0;
}

/* Pass data for m68k_pass_narrow_const_ops.  */

const pass_data m68k_pass_data_narrow_const_ops =
{
  GIMPLE_PASS,		    /* type */
  "m68k-narrow-const-ops",  /* name */
  OPTGROUP_NONE,	    /* optinfo_flags */
  TV_MACH_DEP,		    /* tv_id */
  PROP_ssa,		    /* properties_required */
  0,			    /* properties_provided */
  0,			    /* properties_destroyed */
  0,			    /* todo_flags_start */
  0			    /* todo_flags_finish */
};

/* The pass class for narrow_const_ops.  */

class m68k_pass_narrow_const_ops : public gimple_opt_pass
{
public:
  m68k_pass_narrow_const_ops (gcc::context *ctxt)
    : gimple_opt_pass (m68k_pass_data_narrow_const_ops, ctxt)
  {}

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_narrow_const_ops && !TARGET_COLDFIRE;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_narrow_const_ops (func);
  }

}; /* class m68k_pass_narrow_const_ops */

} /* Anonymous namespace for GIMPLE passes.  */

/* Factory function for m68k_pass_narrow_index_mult.  */

gimple_opt_pass *
make_m68k_pass_narrow_index_mult (gcc::context *ctxt)
{
  return new m68k_pass_narrow_index_mult (ctxt);
}

/* Factory function for m68k_pass_narrow_const_ops.  */

gimple_opt_pass *
make_m68k_pass_narrow_const_ops (gcc::context *ctxt)
{
  return new m68k_pass_narrow_const_ops (ctxt);
}


/* ===================== RTL passes ===================== */

namespace {

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

   IMPORTANT: The inserted moveq/clr is a "future zero-extend" — it
   pre-clears upper bits that later sub-word operations will preserve
   through m68k partial-register-write semantics.  GCC's RTL does NOT
   model partial writes: (set (reg:HI %d0) ...) looks like a full def
   of %d0 to every dataflow-based pass.  Any pass that performs dead
   store elimination or liveness analysis (DCE, sched2, etc.) will see
   the moveq as a dead store killed by the subsequent move.w, and
   delete it — leaving garbage in the upper bits.

   The moveq MUST NOT be deleted as long as the later sub-word move
   exists.  The pass rewrites subsequent sub-word operations to use
   strict_low_part, so GCC's dataflow correctly sees the upper bits
   as live.  This allows the pass to run before sched2.
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

  /* Scan forward from the insn after andi to find clr.w.  */
  rtx_insn *insn;

  for (insn = NEXT_INSN (andi_insn); insn != NEXT_INSN (BB_END (bb));
       insn = NEXT_INSN (insn))
    {
      if (!NONDEBUG_INSN_P (insn))
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

  /* A SUBREG widening our register reads all bits of the inner reg.
     E.g., (subreg:SI (reg:HI d1) 0) reads all 32 bits of d1.  */
  if (code == SUBREG && REG_P (SUBREG_REG (x))
      && REGNO (SUBREG_REG (x)) == regno)
    {
      machine_mode outer = GET_MODE (x);
      if (GET_MODE_SIZE (outer) > GET_MODE_SIZE (max_mode))
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
   upper bits if we haven't pre-cleared).  Equivalent to
   uses_reg_wider_than_p (x, regno, HImode).  */

static inline bool
uses_reg_as_long_p (rtx x, unsigned regno)
{
  return uses_reg_wider_than_p (x, regno, HImode);
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
  rtx_insn *widen_and_insn; /* Widenable and.w for WORD_TO_LONG.  */

  andi_candidate () : andi_insn (nullptr), reg (nullptr),
		      def_insns (vNULL), ext_type (EXT_NONE), valid (false),
		      widen_and_insn (nullptr) {}
};

/* Check if an effect is compatible with the extension type being optimized.
   For word-to-long: byte and word operations are safe.
   For byte-to-long/word: only byte operations are safe.  */

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

/* Rewrite sub-word definitions of REGNO from START_INSN (inclusive)
   to END_INSN (exclusive) to use strict_low_part.  This tells GCC's
   dataflow that these instructions only write the low part of the
   register, preserving the upper bits set by a preceding moveq #0.
   Without this, GCC treats (set (reg:HI) ...) as a full write and
   DCE deletes the moveq as dead.

   EXT_TYPE determines which modes to convert:
     EXT_WORD_TO_LONG: convert HImode sets (and QImode sets)
     EXT_BYTE_TO_LONG: convert QImode sets
     EXT_BYTE_TO_WORD: convert QImode sets

   Returns true if all conversions succeeded.  */

static bool
rewrite_subword_defs_to_strict_low_part (rtx_insn *start_insn,
					 rtx_insn *end_insn,
					 unsigned int regno,
					 enum extension_type ext_type)
{
  /* Determine the outer mode (the mode of the pre-cleared register).  */
  machine_mode outer_mode
    = (ext_type == EXT_BYTE_TO_WORD) ? HImode : SImode;

  /* Start from start_insn itself (inclusive) — the first definition
     also needs strict_low_part conversion.  */
  for (rtx_insn *insn = start_insn;
       insn && insn != end_insn;
       insn = NEXT_INSN (insn))
    {
      if (!NONDEBUG_INSN_P (insn))
	continue;

      /* Skip call insns — function calls write the full return register
	 per the calling convention, not a partial write.  */
      if (CALL_P (insn))
	continue;

      rtx pat = PATTERN (insn);
      if (GET_CODE (pat) != SET)
	continue;

      rtx dest = SET_DEST (pat);

      /* Skip if not a plain register set on our register.  */
      if (!REG_P (dest) || REGNO (dest) != regno)
	continue;

      machine_mode dest_mode = GET_MODE (dest);

      /* Skip if already SImode (or the outer mode) — no conversion needed.  */
      if (dest_mode == outer_mode || dest_mode == SImode)
	continue;

      /* Determine if this mode should be converted.  */
      bool should_convert = false;
      if (ext_type == EXT_WORD_TO_LONG
	  && (dest_mode == HImode || dest_mode == QImode))
	should_convert = true;
      else if ((ext_type == EXT_BYTE_TO_LONG || ext_type == EXT_BYTE_TO_WORD)
	       && dest_mode == QImode)
	should_convert = true;

      if (!should_convert)
	continue;

      /* Build strict_low_part replacement:
	 (set (strict_low_part (subreg:MODE (reg:OUTER_MODE REGNO) OFFSET))
	      src_with_subreg_refs)
	 Also rewrite (reg:MODE REGNO) references in the source to use
	 the same subreg form, so match_dup 0 in strict_low_part
	 arithmetic patterns can match.  */
      poly_uint64 offset = subreg_lowpart_offset (dest_mode, outer_mode);

      rtx outer_reg = gen_rtx_REG (outer_mode, regno);
      rtx subreg = gen_rtx_SUBREG (dest_mode, outer_reg, offset);
      rtx slp = gen_rtx_STRICT_LOW_PART (VOIDmode, subreg);

      /* Replace (reg:MODE REGNO) with the subreg in the source.
	 Walks the top-level operands of the source expression, which
	 covers all m68k strict_low_part arithmetic patterns (binary
	 ops like plus:HI have the reg at position 0 or 1, unary ops
	 like neg:HI have it at position 0).  */
      rtx new_src = copy_rtx (SET_SRC (pat));
      const char *fmt = GET_RTX_FORMAT (GET_CODE (new_src));
      for (int i = 0; i < GET_RTX_LENGTH (GET_CODE (new_src)); i++)
	{
	  if (fmt[i] == 'e')
	    {
	      rtx op = XEXP (new_src, i);
	      if (REG_P (op) && REGNO (op) == regno
		  && GET_MODE (op) == dest_mode)
		XEXP (new_src, i) = copy_rtx (subreg);
	    }
	}

      rtx new_pat = gen_rtx_SET (slp, new_src);

      /* Try to recognize the new pattern.  */
      rtx old_pat = PATTERN (insn);
      PATTERN (insn) = new_pat;
      INSN_CODE (insn) = -1;
      if (recog_memoized (insn) >= 0
	  && (extract_insn (insn),
	      constrain_operands (1, get_preferred_alternatives (insn))))
	{
	  /* Rescan the insn so DF sees the strict_low_part USE of the
	     upper bits.  Without this, sched2's fast DCE uses stale DF
	     info and incorrectly deletes the preceding moveq pre-clear.  */
	  df_insn_rescan (insn);
	  if (dump_file)
	    {
	      fprintf (dump_file, "  Converted to strict_low_part: ");
	      print_rtl_single (dump_file, insn);
	    }
	}
      else
	{
	  /* Revert — this insn can't use strict_low_part.  */
	  PATTERN (insn) = old_pat;
	  INSN_CODE (insn) = -1;
	  recog_memoized (insn);
	  if (dump_file)
	    {
	      fprintf (dump_file, "  FAILED strict_low_part for: ");
	      print_rtl_single (dump_file, insn);
	    }
	  return false;
	}
    }

  return true;
}

/* Return true if a single clear in LOOP's preheader is enough to keep the
   upper bits of REGNO zero for every iteration.

   Hoisting the clear out of the loop only works while everything inside
   writes REGNO in a mode narrower than CLR_MODE — those are m68k partial
   writes and leave the upper bits alone.  One full-width write is enough to
   destroy the invariant, and the back edge then re-enters the loop without
   the clear being repeated, so from the second iteration onwards the upper
   bits carry that value instead of zero.

   String_Pixel_Width in Vanilla Conquer is the cautionary example: the loop
   body computes "add.l %d3,%d1" and then reloads only the low byte with
   "move.b (%a0)+,%d1", after which %d1 is used as a full 32-bit index into
   the font width table.  With the clear hoisted, every character but the
   first indexed far outside the table.  */

static bool
m68k_loop_keeps_upper_bits_clear_p (class loop *loop, unsigned regno,
				    machine_mode clr_mode)
{
  basic_block *body = get_loop_body (loop);
  bool ok = true;

  for (unsigned i = 0; ok && i < loop->num_nodes; i++)
    {
      rtx_insn *insn;
      FOR_BB_INSNS (body[i], insn)
	{
	  if (!NONDEBUG_INSN_P (insn))
	    continue;

	  /* A call clobbers the caller-saved registers wholesale.  */
	  if (CALL_P (insn)
	      && TEST_HARD_REG_BIT (regs_invalidated_by_call, regno))
	    {
	      ok = false;
	      break;
	    }

	  df_ref def;
	  FOR_EACH_INSN_DEF (def, insn)
	    {
	      if (DF_REF_REGNO (def) != regno)
		continue;

	      rtx reg = DF_REF_REG (def);
	      machine_mode mode = GET_MODE (reg);

	      /* Anything not strictly narrower than the clear touches the
		 upper bits.  Partial writes flagged as such are fine.  */
	      if ((DF_REF_FLAGS (def) & DF_REF_PARTIAL) == 0
		  && !(GET_MODE_SIZE (mode) < GET_MODE_SIZE (clr_mode)))
		{
		  ok = false;
		  break;
		}
	    }

	  if (!ok)
	    break;
	}
    }

  free (body);
  return ok;
}

/* Try to eliminate andi instructions in a basic block by inserting
   moveq #0 before the first appropriately-sized definition.
   ALREADY_CLEARED_BEFORE tracks def_insns that already have moveq inserted
   across all BBs in the function to avoid duplicate insertions.
   Returns the number of eliminations performed.  */

static unsigned int
m68k_elim_andi_bb (basic_block bb, bitmap already_cleared_before,
		   bool *created_loops)
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
      /* Collect BB instructions in order once (reused across candidates).  */
      auto_vec<rtx_insn *> bb_insns;
      rtx_insn *bb_insn;
      FOR_BB_INSNS (bb, bb_insn)
	if (NONDEBUG_INSN_P (bb_insn))
	  bb_insns.safe_push (bb_insn);

      for (andi_candidate &cand : candidates)
    {
      unsigned regno = REGNO (cand.reg);

      bool found_def = false;
      bool already_cleared = false;

      if (dump_file)
	fprintf (dump_file, "  Scanning backward for d%d definition\n", regno);

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
		  found_def = true;
		}
	      else if (cand.ext_type == EXT_WORD_TO_LONG)
		{
		  /* Byte definition only affects bits 0-7.  Continue scanning
		     backward to find a word-level definition (e.g. clr.w)
		     that can be widened to clear bits 16-31.  */
		  continue;
		}
	      else
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
		{
		  /* Check if this is and.w #N with N >= 0, which could be
		     widened to and.l #N to clear bits 16-31.  Record the
		     first (closest to candidate) such instruction.  */
		  if (cand.widen_and_insn == nullptr)
		    {
		      rtx scan_pat = PATTERN (scan);
		      if (GET_CODE (scan_pat) == SET
			  && GET_CODE (SET_SRC (scan_pat)) == AND
			  && REG_P (XEXP (SET_SRC (scan_pat), 0))
			  && REGNO (XEXP (SET_SRC (scan_pat), 0)) == regno
			  && CONST_INT_P (XEXP (SET_SRC (scan_pat), 1))
			  && INTVAL (XEXP (SET_SRC (scan_pat), 1)) >= 0)
			{
			  cand.widen_and_insn = scan;
			  if (dump_file)
			    fprintf (dump_file,
				     "    -> Found widenable and.w #%ld\n",
				     (long) INTVAL (
				       XEXP (SET_SRC (scan_pat), 1)));
			}
		    }
		  continue;
		}
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

      /* Note: a previous optimization here checked if clr.w followed
	 the andi.l #$ffff and deemed the andi redundant ("it only
	 preserves low bits that clr.w will clear").  But andi.l #$ffff
	 also clears the HIGH word (bits 16-31).  Deleting it leaves
	 the high word as garbage, which is wrong when the register is
	 later used in SImode (e.g., move.l dN,d0 for a 4-byte struct
	 argument).  The optimization was removed.  */

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

      /* If still not valid and we found a widenable and.w, use it.  */
      if (!cand.valid && cand.ext_type == EXT_WORD_TO_LONG
	  && cand.widen_and_insn != nullptr)
	{
	  if (dump_file)
	    fprintf (dump_file, "  Found widenable and.w for d%d\n", regno);
	  cand.valid = true;
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

      /* Handle widen_and_insn: widen and.w #N to and.l #N, which
	 clears bits 16-31 as a side effect, making the later
	 and.l #65535 redundant.  */
      if (cand.widen_and_insn != nullptr && cand.def_insns.is_empty ())
	{
	  /* If the widen_and_insn was already deleted by a previous
	     candidate (e.g. a BYTE_TO_WORD on the same register),
	     skip this transformation.  */
	  if (cand.widen_and_insn->deleted ())
	    {
	      if (dump_file)
		fprintf (dump_file, "  SKIP: widen_and_insn already deleted\n");
	      continue;
	    }
	  rtx old_pat = PATTERN (cand.widen_and_insn);
	  rtx mask = XEXP (SET_SRC (old_pat), 1);
	  unsigned widen_regno = REGNO (cand.reg);
	  rtx si_reg = gen_rtx_REG (SImode, widen_regno);
	  rtx new_src = gen_rtx_AND (SImode, si_reg, mask);
	  rtx new_set = gen_rtx_SET (si_reg, new_src);
	  rtx_insn *new_insn
	    = emit_insn_before (new_set, cand.widen_and_insn);
	  INSN_CODE (new_insn) = -1;
	  if (recog_memoized (new_insn) >= 0)
	    {
	      delete_insn (cand.widen_and_insn);
	      delete_insn (cand.andi_insn);
	      changes++;
	      if (dump_file)
		fprintf (dump_file, "  Widened and.w #%ld to and.l, "
			 "deleted and.l #65535 for d%d\n",
			 (long) INTVAL (mask), widen_regno);
	    }
	  else
	    delete_insn (new_insn);
	  continue;  /* Skip normal transformation.  */
	}

      /* Insert moveq #0,reg before each definition.  */
      bool all_succeeded = true;
      auto_vec<rtx_insn *> inserted_insns;
      /* clr.w definitions that were widened to a long clear.  The original
	 must outlive the decision: it is only removed once the candidate has
	 succeeded, so that abandoning the candidate leaves the function with
	 the clear it started with.  */
      auto_vec<rtx_insn *> widened_originals;
      auto_vec<unsigned> claimed_keys;

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

	  /* The clear is executed once, but an andi inside a loop is reached
	     again on every iteration.  That only stays sound while the loop
	     writes the register exclusively through partial writes; a single
	     full-width write leaves the upper bits dirty for the next
	     iteration, and the clear is not repeated.  */
	  if (current_loops == NULL && !*created_loops)
	    {
	      loop_optimizer_init (AVOID_CFG_MODIFICATIONS);
	      *created_loops = true;
	    }
	  if (current_loops)
	    {
	      machine_mode loop_clr_mode
		= (cand.ext_type == EXT_BYTE_TO_WORD) ? HImode : SImode;
	      class loop *use_loop = bb->loop_father;

	      if (use_loop
		  && use_loop != current_loops->tree_root
		  && !m68k_loop_keeps_upper_bits_clear_p (use_loop, regno,
							  loop_clr_mode))
		{
		  if (dump_file)
		    fprintf (dump_file, "  SKIP: loop %d writes d%d at full "
			     "width, a single clear would not hold\n",
			     use_loop->num, regno);
		  /* Abandon the whole candidate — skipping just this clear
		     would leave the andi eliminated with nothing to
		     compensate for it.  */
		  all_succeeded = false;
		  break;
		}
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
		 than inserting it in the hot loop body.  Lazily initialize
		 loop info on first use to avoid the cost for functions
		 with no ANDI patterns.  */
	      if (current_loops == NULL && !*created_loops)
		{
		  loop_optimizer_init (AVOID_CFG_MODIFICATIONS);
		  *created_loops = true;
		}
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
		      /* Determine clear mode based on extension type.  */
		      machine_mode clr_mode
			= (cand.ext_type == EXT_BYTE_TO_WORD)
			  ? HImode : SImode;

		      if (prehdr_edge && non_latch_preds == 1
			  && prehdr_edge->src != ENTRY_BLOCK_PTR_FOR_FN (cfun)
			  && m68k_loop_keeps_upper_bits_clear_p (def_loop,
								 regno,
								 clr_mode))
			{
			  basic_block preheader = prehdr_edge->src;

			  /* Check if we already inserted a clr for this
			     register in this preheader.  */
			  /* Use high bit to avoid collision with insn
			     UID-based keys.  */
			  unsigned preamble_key = (1u << 24)
						  | (preheader->index << 4)
						  | (regno & 0xf);
			  if (!bitmap_bit_p (already_cleared_before,
					     preamble_key))
			    {
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

	  /* If the definition is clr.w (word-mode clear), widen it to
	     moveq #0 (long-mode clear) in-place instead of inserting
	     a separate instruction.  */
	  rtx def_pat = PATTERN (def_insn);
	  if (cand.ext_type == EXT_WORD_TO_LONG
	      && GET_CODE (def_pat) == SET
	      && REG_P (SET_DEST (def_pat))
	      && GET_MODE (SET_DEST (def_pat)) == HImode
	      && SET_SRC (def_pat) == const0_rtx
	      && REGNO (SET_DEST (def_pat)) == regno)
	    {
	      /* Replace clr.w with moveq #0 (clears all 32 bits).  */
	      rtx si_reg = gen_rtx_REG (SImode, regno);
	      rtx wide_pat = gen_rtx_SET (si_reg, const0_rtx);
	      rtx_insn *wide_insn = emit_insn_before (wide_pat, def_insn);
	      INSN_CODE (wide_insn) = -1;
	      if (recog_memoized (wide_insn) >= 0)
		{
		  unsigned key2 = (INSN_UID (def_insn) << 4) | (regno & 0xf);
		  bitmap_set_bit (already_cleared_before, key2);
		  claimed_keys.safe_push (key2);
		  /* Do NOT delete def_insn yet — see widened_originals.
		     Until then both clears are present, which is redundant
		     but correct: the long clear runs first, the word clear
		     immediately after.  */
		  widened_originals.safe_push (def_insn);
		  inserted_insns.safe_push (wide_insn);
		  if (dump_file)
		    fprintf (dump_file, "  Widened clr.w to moveq #0 "
			     "for d%d\n", regno);
		  continue;
		}
	      delete_insn (wide_insn);
	      all_succeeded = false;
	      break;
	    }

	  /* Insert a "future zero-extend": clear the register so that the
	     subsequent sub-word move preserves zeros in the upper bits.
	     This clear MUST NOT be deleted by any later pass — see the
	     pass header comment for why.  */
	  rtx clear_reg;
	  if (cand.ext_type == EXT_BYTE_TO_WORD)
	    clear_reg = gen_rtx_REG (HImode, regno);
	  else
	    clear_reg = gen_rtx_REG (SImode, regno);

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
	     update the dataflow framework.  The widened originals are left
	     untouched — dropping them here would strip the function of a
	     clear that nothing replaces.  */
	  for (rtx_insn *ins : inserted_insns)
	    delete_insn (ins);
	  for (unsigned k : claimed_keys)
	    bitmap_clear_bit (already_cleared_before, k);
	  continue;
	}

      /* Rewrite sub-word definitions between each def_insn and the andi
	 to use strict_low_part.  This tells GCC the upper bits are
	 preserved, preventing DCE from deleting the moveq pre-clear.
	 Only needed when running before sched2 (which has fast DCE).  */
      for (rtx_insn *def_insn : cand.def_insns)
	{
	  if (!rewrite_subword_defs_to_strict_low_part (
		 def_insn, cand.andi_insn, REGNO (cand.reg),
		 cand.ext_type))
	    {
	      if (dump_file)
		fprintf (dump_file, "  strict_low_part rewrite failed, "
			 "reverting\n");
	      all_succeeded = false;
	      break;
	    }
	}

      if (!all_succeeded)
	{
	  for (rtx_insn *ins : inserted_insns)
	    delete_insn (ins);
	  for (unsigned k : claimed_keys)
	    bitmap_clear_bit (already_cleared_before, k);
	  continue;
	}

      /* Delete the andi instruction.  Use delete_insn() instead of
	 SET_INSN_DELETED() to properly update the dataflow framework.  */
      if (dump_file)
	fprintf (dump_file, "deleting insn with uid = %d.\n",
		 INSN_UID (cand.andi_insn));
      delete_insn (cand.andi_insn);

      /* The candidate held; now the superseded word clears can go.  */
      for (rtx_insn *orig : widened_originals)
	delete_insn (orig);

      changes++;
	}
    }

  /* Release inner vecs before candidates goes out of scope.  */
  for (andi_candidate &cand : candidates)
    cand.def_insns.release ();

  /* Pass 4: Check for memory ANDI patterns.
     Pattern: andi.l #$ffff, N(sp) followed by clr.w N+2(sp)
     The ANDI preserves low 16 bits, but clr.w clears them - redundant.  */
  if (dump_file)
    fprintf (dump_file, "  Pass 4: Scanning for memory ANDI patterns\n");

  rtx_insn *next_insn;
  FOR_BB_INSNS_SAFE (bb, insn, next_insn)
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

  /* Loop info is initialized lazily inside m68k_elim_andi_bb when a
     preheader hoisting opportunity is found.  This avoids the cost of
     loop_optimizer_init() for functions with no ANDI patterns.  */
  bool created_loops = false;

  /* Track def_insns that already have moveq inserted before them.
     Key is (insn UID << 4) | regno to handle different registers.
     This is shared across all BBs to prevent duplicate insertions
     when multiple BBs reference the same def_insn in a predecessor.
     Also used for preheader insertions with (bb_index << 4) | regno.  */
  auto_bitmap already_cleared_before;

  basic_block bb;
  FOR_EACH_BB_FN (bb, func)
    {
      changes += m68k_elim_andi_bb (bb, already_cleared_before,
				    &created_loops);
    }

  if (dump_file)
    fprintf (dump_file, "m68k-elim-andi: Pass complete, total changes=%d\n",
	     changes);

  /* Clean up loop info if we initialized it.  Free dominance info too,
     since loop_optimizer_finalize() leaves it alive — without this,
     the immediately following pass (bbro / pass_reorder_blocks) finds
     stale dominator info and its incremental update in merge_blocks()
     can enter an infinite loop in et_splay().  This matches what
     pass_rtl_loop_done does (loop-init.cc:480).  */
  if (created_loops)
    {
      loop_optimizer_finalize ();
      free_dominance_info (CDI_DOMINATORS);
    }

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

	  /* A call passes its register arguments through
	     CALL_INSN_FUNCTION_USAGE, not through PATTERN, so a 32-bit
	     argument held in this register would go unnoticed here — and the
	     call's implicit clobber of the return register must not be taken
	     for a safe redefinition.  Not exotic under -mfastcall, where
	     arguments travel in registers.  */
	  if (CALL_P (scan)
	      && CALL_INSN_FUNCTION_USAGE (scan)
	      && uses_reg_as_long_p (CALL_INSN_FUNCTION_USAGE (scan), regno))
	    {
	      upper_bits_matter = true;
	      break;
	    }

	  /* Check SImode use BEFORE redef — an insn like add.l %d0,%d0
	     both reads and writes, and the read needs correct upper bits.  */
	  if (uses_reg_as_long_p (PATTERN (scan), regno))
	    {
	      upper_bits_matter = true;
	      break;
	    }

	  /* If register is redefined without SImode use, upper bits reset.  */
	  if (reg_set_p (shift_reg, scan))
	    break;
	}

      /* Also check if reg is live out of BB - be conservative.  */
      if (!upper_bits_matter)
	{
	  bitmap live_out = df_get_live_out (bb);
	  if (bitmap_bit_p (live_out, regno))
	    {
	      /* Live out of block.  For return values (d0), check if
		 the function returns HImode - in that case upper bits
		 don't matter even if live out.

		 A HImode return type alone is not enough: d0 being live out
		 does not mean it carries the return value.  It may be live
		 into a successor block that uses it as SImode, and the upper
		 bits would then be garbage.  Only trust the return type when
		 this block flows straight to the exit, so the live-out value
		 really is the returned one.  */
	      if (regno == 0)
		{
		  tree ret_type = TREE_TYPE (TREE_TYPE (cfun->decl));
		  if (single_succ_p (bb)
		      && single_succ (bb) == EXIT_BLOCK_PTR_FOR_FN (cfun)
		      && ret_type && INTEGRAL_TYPE_P (ret_type)
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
      INSN_CODE (new_insn) = -1;
      if (recog_memoized (new_insn) < 0)
	{
	  delete_insn (new_insn);
	  continue;
	}

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
	     && !NONDEBUG_INSN_P (next))
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

	  /* Register arguments of a call live in CALL_INSN_FUNCTION_USAGE
	     rather than in PATTERN, so a 32-bit argument in this register
	     is invisible to the check below, and the call's implicit
	     clobber would otherwise pass for a safe redefinition.  */
	  if (CALL_P (scan)
	      && CALL_INSN_FUNCTION_USAGE (scan)
	      && uses_reg_as_long_p (CALL_INSN_FUNCTION_USAGE (scan), regno))
	    {
	      safe = false;
	      break;
	    }

	  /* Check the SImode use BEFORE the redefinition — an insn like
	     add.l %d0,%d0 both reads and writes, and the read still needs
	     the sign-extended upper bits.  Testing reg_set_p first would
	     accept such an insn as a harmless redefinition.  */
	  if (uses_reg_as_long_p (PATTERN (scan), regno))
	    {
	      safe = false;
	      break;
	    }

	  if (reg_set_p (ext_reg, scan))
	    break;  /* Redefined - safe.  */
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

/* Emit swap+move.w+swap to insert VALUE_REGNO's low 16 bits into the
   high word of STRUCT_REGNO.  The three new insns are emitted before
   BEFORE_INSN.  Returns the last emitted insn, or NULL on failure.  */

static rtx_insn *
emit_highword_insert (unsigned struct_regno, unsigned value_regno,
		      rtx_insn *before_insn)
{
  rtx struct_reg = gen_rtx_REG (SImode, struct_regno);

  /* swap STRUCT_REG  */
  rtx swap1_pat = gen_rtx_SET (struct_reg,
			       gen_rtx_ROTATE (SImode, struct_reg,
					       GEN_INT (16)));
  rtx_insn *swap1 = emit_insn_before (swap1_pat, before_insn);

  /* move.w VALUE_REG, STRUCT_REG (strict_low_part)  */
  rtx value_hi = gen_rtx_REG (HImode, value_regno);
  rtx slp = gen_rtx_STRICT_LOW_PART (VOIDmode,
				     gen_rtx_SUBREG (HImode, struct_reg, 2));
  rtx move_pat = gen_rtx_SET (slp, value_hi);
  rtx_insn *move = emit_insn_after (move_pat, swap1);

  /* swap STRUCT_REG  */
  rtx swap2_pat = gen_rtx_SET (struct_reg,
			       gen_rtx_ROTATE (SImode, struct_reg,
					       GEN_INT (16)));
  rtx_insn *swap2 = emit_insn_after (swap2_pat, move);

  /* Validate.  */
  INSN_CODE (swap1) = -1;
  INSN_CODE (move) = -1;
  INSN_CODE (swap2) = -1;

  if (recog_memoized (swap1) < 0
      || recog_memoized (move) < 0
      || recog_memoized (swap2) < 0)
    {
      if (dump_file)
	fprintf (dump_file, "  FAILED: New insns not recognized\n");
      delete_insn (swap1);
      delete_insn (move);
      delete_insn (swap2);
      return NULL;
    }

  if (dump_file)
    {
      fprintf (dump_file, "  Transformed to:\n");
      fprintf (dump_file, "  swap d%d: ", struct_regno);
      print_rtl_single (dump_file, swap1);
      fprintf (dump_file, "  move.w d%d,d%d: ", value_regno, struct_regno);
      print_rtl_single (dump_file, move);
      fprintf (dump_file, "  swap d%d: ", struct_regno);
      print_rtl_single (dump_file, swap2);
    }

  df_insn_rescan (swap1);
  df_insn_rescan (move);
  df_insn_rescan (swap2);

  return swap2;
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

      rtx_insn *last_new
	= emit_highword_insert (struct_regno, value_regno, ashift_insn);
      if (!last_new)
	{
	  insn = next_iter;
	  continue;
	}

      /* Delete original instructions.  */
      delete_insn (ashift_insn);
      delete_insn (and_insn);
      delete_insn (ior_insn);

      changed = true;
      insn = NEXT_INSN (last_new);
    }

  return changed;
}

/* Optimize bfins: Replace bfins Dn,Dm{#0:#16} with swap+move.w+swap.
   The bfins instruction inserts into the high 16 bits of a register.
   On 68020/030/060, swap+move.w+swap is faster (~6 vs ~10 cycles on 68030).
   Only applied when optimizing for speed; bfins is smaller (4 vs 6 bytes).

   Transform:
     (set (zero_extract:SI reg0 (const_int 16) (const_int 0)) reg1)
   To:
     swap reg0; move.w reg1,reg0; swap reg0

   Returns true if any optimization was performed.  */

static bool
highword_optimize_bfins (basic_block bb)
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

      rtx pat = PATTERN (insn);
      if (GET_CODE (pat) != SET)
	{
	  insn = next_iter;
	  continue;
	}

      rtx dest = SET_DEST (pat);
      rtx src = SET_SRC (pat);

      /* Match (set (zero_extract:SI reg (const 16) (const 0)) reg).  */
      if (GET_CODE (dest) != ZERO_EXTRACT
	  || GET_MODE (dest) != SImode
	  || !REG_P (XEXP (dest, 0))
	  || !DATA_REG_P (XEXP (dest, 0))
	  || !CONST_INT_P (XEXP (dest, 1))
	  || INTVAL (XEXP (dest, 1)) != 16
	  || !CONST_INT_P (XEXP (dest, 2))
	  || INTVAL (XEXP (dest, 2)) != 0
	  || !REG_P (src)
	  || !DATA_REG_P (src))
	{
	  insn = next_iter;
	  continue;
	}

      unsigned struct_regno = REGNO (XEXP (dest, 0));
      unsigned value_regno = REGNO (src);

      if (dump_file)
	{
	  fprintf (dump_file, "m68k-highword-opt: Found bfins insertion "
		   "(d%d -> d%d high word):\n", value_regno, struct_regno);
	  print_rtl_single (dump_file, insn);
	}

      rtx_insn *last_new
	= emit_highword_insert (struct_regno, value_regno, insn);
      if (!last_new)
	{
	  insn = next_iter;
	  continue;
	}

      delete_insn (insn);

      changed = true;
      insn = NEXT_INSN (last_new);
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
	 4. Bfins insertion (68020+ only, speed only)
	 5. Mask+or (memory load + mask + or pattern)  */

      if (highword_optimize_extraction (bb))
	changes++;

      if (highword_optimize_computation (bb))
	changes++;

      if (highword_optimize_insertion (bb))
	changes++;

      /* Replace bfins Dn,Dm{#0:#16} with swap+move.w+swap on 020/030.
	 On 040, swap+move.w+swap is the same speed as bfins.
	 On 060, bfins is faster.  Keep bfins for -Os (4 vs 6 bytes).  */
      if (TARGET_68020 && !TUNE_68040_60
	  && optimize_bb_for_speed_p (bb)
	  && highword_optimize_bfins (bb))
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


} /* Anonymous namespace for RTL passes.  */

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
