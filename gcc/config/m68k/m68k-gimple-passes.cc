/* GIMPLE optimization passes for Motorola 68k.
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
#include "gimple-walk.h"
#include "gimple-pretty-print.h"
#include "cfgloop.h"
#include "tree-ssa-loop.h"
#include "tree-scalar-evolution.h"
#include "fold-const.h"
#include "gimplify.h"
#include "gimple-ssa.h"
#include "tree-phinodes.h"
#include "ssa-iterators.h"
#include "stor-layout.h"
#include "gimple-range.h"
#include "context.h"
#include "tree-ssa-alias.h"
#include "tree-cfg.h"
#include "tree-dfa.h"
#include "tree-into-ssa.h"

namespace {

/* =======================================================================
   GIMPLE pass: m68k_pass_autoinc_split

   This pass splits combined pointer increments back into individual
   increments to enable post-increment addressing modes.

   Problem: forwprop combines sequential *ptr++ operations:
     _1 = MEM[base + 0];
     _2 = MEM[base + 4];
     _3 = MEM[base + 8];
     _4 = MEM[base + 12];
     base = base + 16;

   This prevents auto-increment because step (16) != element_size (4).

   Solution: Split back to individual increments:
     _1 = *base;
     base_a = base + 4;
     _2 = *base_a;
     base_b = base_a + 4;
     _3 = *base_b;
     base_c = base_b + 4;
     _4 = *base_c;
     base = base_c + 4;

   This enables IVOPTS and auto-inc-dec to form:
     move.l (%a0)+,(%a1)+  (on m68k and similar targets)
   ======================================================================= */

/* Check if the target benefits from this transformation.
   Only useful for targets with simple auto-increment (step == size)
   but without arbitrary displacement auto-modify.  */

static bool
target_needs_autoinc_split (void)
{
#if !AUTO_INC_DEC
  /* Target has no auto-increment at all, splitting won't help.  */
  return false;
#else
  /* If target has POST_MODIFY_DISP, it can handle any step size,
     so splitting is unnecessary.  */
#if HAVE_POST_MODIFY_DISP || HAVE_PRE_MODIFY_DISP
  return false;
#else
  /* Target has simple auto-increment - splitting may help.  */
  return true;
#endif
#endif
}

/* Information about a memory access in the loop.  */

struct mem_access_info
{
  gimple *stmt;           /* The statement containing the MEM_REF.  */
  tree mem_ref;           /* The MEM_REF itself.  */
  tree base;              /* Base pointer SSA name.  */
  HOST_WIDE_INT offset;   /* Constant offset from base.  */
  bool is_store;          /* True if this is a store, false if load.  */
};

/* Information about a pointer IV and its accesses.  */

struct ptr_iv_info
{
  tree phi_result;        /* SSA name from PHI node.  */
  gphi *phi;              /* The PHI node.  */
  gimple *increment_stmt; /* Statement that increments the pointer.  */
  tree increment_ssa;     /* SSA name of incremented value.  */
  HOST_WIDE_INT step;     /* Total increment step.  */
  vec<mem_access_info> accesses;  /* Memory accesses using this IV.  */
};

/* Comparison function for sorting accesses by offset.  */

static int
compare_access_offset (const void *a, const void *b)
{
  const mem_access_info *ma = (const mem_access_info *) a;
  const mem_access_info *mb = (const mem_access_info *) b;

  if (ma->offset < mb->offset)
    return -1;
  if (ma->offset > mb->offset)
    return 1;
  return 0;
}

/* Check if MEM is a MEM_REF with constant offset from BASE.
   If so, return the offset in *OFFSET_OUT.  */

static bool
get_mem_ref_offset (tree mem, tree base, HOST_WIDE_INT *offset_out)
{
  if (TREE_CODE (mem) != MEM_REF)
    return false;

  tree mem_base = TREE_OPERAND (mem, 0);
  tree mem_offset = TREE_OPERAND (mem, 1);

  if (mem_base != base)
    return false;

  if (TREE_CODE (mem_offset) != INTEGER_CST)
    return false;

  *offset_out = tree_to_shwi (mem_offset);
  return true;
}

/* Collect memory accesses in LOOP that use pointer IV BASE.  */

static void
collect_mem_accesses (class loop *loop, tree base,
                      vec<mem_access_info> *accesses)
{
  basic_block *bbs = get_loop_body (loop);

  for (unsigned i = 0; i < loop->num_nodes; i++)
    {
      basic_block bb = bbs[i];

      for (gimple_stmt_iterator gsi = gsi_start_bb (bb);
           !gsi_end_p (gsi); gsi_next (&gsi))
        {
          gimple *stmt = gsi_stmt (gsi);

          if (!is_gimple_assign (stmt))
            continue;

          /* Check for load: _x = MEM[base + offset]  */
          if (gimple_assign_load_p (stmt))
            {
              tree rhs = gimple_assign_rhs1 (stmt);
              HOST_WIDE_INT offset;

              if (get_mem_ref_offset (rhs, base, &offset))
                {
                  mem_access_info info;
                  info.stmt = stmt;
                  info.mem_ref = rhs;
                  info.base = base;
                  info.offset = offset;
                  info.is_store = false;
                  accesses->safe_push (info);
                }
            }

          /* Check for store: MEM[base + offset] = _x  */
          if (gimple_store_p (stmt))
            {
              tree lhs = gimple_assign_lhs (stmt);
              HOST_WIDE_INT offset;

              if (get_mem_ref_offset (lhs, base, &offset))
                {
                  mem_access_info info;
                  info.stmt = stmt;
                  info.mem_ref = lhs;
                  info.base = base;
                  info.offset = offset;
                  info.is_store = true;
                  accesses->safe_push (info);
                }
            }
        }
    }

  free (bbs);
}

/* Find the increment statement for pointer PHI_RESULT in LOOP.
   Returns the statement if found, NULL otherwise.
   Sets *STEP to the increment amount and *INC_SSA to the incremented value.  */

static gimple *
find_ptr_increment (class loop *loop, tree phi_result,
                    HOST_WIDE_INT *step, tree *inc_ssa)
{
  gphi *phi = as_a<gphi *> (SSA_NAME_DEF_STMT (phi_result));
  edge latch = loop_latch_edge (loop);
  tree latch_val = PHI_ARG_DEF_FROM_EDGE (phi, latch);

  if (TREE_CODE (latch_val) != SSA_NAME)
    return NULL;

  gimple *inc_stmt = SSA_NAME_DEF_STMT (latch_val);

  if (!is_gimple_assign (inc_stmt))
    return NULL;

  enum tree_code code = gimple_assign_rhs_code (inc_stmt);

  if (code != POINTER_PLUS_EXPR && code != PLUS_EXPR)
    return NULL;

  tree rhs1 = gimple_assign_rhs1 (inc_stmt);
  tree rhs2 = gimple_assign_rhs2 (inc_stmt);

  /* Check that increment is of the form: ptr_new = ptr_old + const  */
  if (TREE_CODE (rhs2) != INTEGER_CST)
    return NULL;

  /* Verify rhs1 is derived from phi_result (possibly through copies).  */
  tree base = rhs1;
  while (TREE_CODE (base) == SSA_NAME)
    {
      if (base == phi_result)
        break;
      gimple *def = SSA_NAME_DEF_STMT (base);
      if (!is_gimple_assign (def)
          || gimple_assign_rhs_code (def) != SSA_NAME)
        return NULL;
      base = gimple_assign_rhs1 (def);
    }

  if (base != phi_result)
    return NULL;

  *step = tree_to_shwi (rhs2);
  *inc_ssa = latch_val;
  return inc_stmt;
}

/* Check if ACCESSES form a sequential pattern suitable for splitting.
   Returns the element size if suitable, 0 otherwise.  */

static HOST_WIDE_INT
check_sequential_accesses (vec<mem_access_info> &accesses, HOST_WIDE_INT step)
{
  unsigned n = accesses.length ();

  if (n < 2)
    return 0;

  /* Sort accesses by offset.  */
  accesses.qsort (compare_access_offset);

  /* Check that first access is at offset 0.  */
  if (accesses[0].offset != 0)
    return 0;

  /* Determine element size from first two accesses.  */
  HOST_WIDE_INT elem_size = accesses[1].offset - accesses[0].offset;

  if (elem_size <= 0)
    return 0;

  /* Verify all accesses are at sequential offsets.  */
  for (unsigned i = 0; i < n; i++)
    {
      if (accesses[i].offset != (HOST_WIDE_INT)(i * elem_size))
        return 0;
    }

  /* Verify combined step equals n * elem_size.  */
  if (step != (HOST_WIDE_INT)(n * elem_size))
    return 0;

  /* Verify element size matches the memory access size.  */
  tree mem_type = TREE_TYPE (accesses[0].mem_ref);
  if (tree_to_uhwi (TYPE_SIZE_UNIT (mem_type)) != (unsigned HOST_WIDE_INT)elem_size)
    return 0;

  return elem_size;
}

/* Perform the transformation: split combined increment into individual
   increments after each memory access.  */

static bool
split_combined_increment (class loop *loop ATTRIBUTE_UNUSED,
                          ptr_iv_info *iv_info,
                          HOST_WIDE_INT elem_size)
{
  vec<mem_access_info> &accesses = iv_info->accesses;
  unsigned n = accesses.length ();

  if (dump_file)
    {
      fprintf (dump_file, "Splitting combined increment: step %ld -> %u x %ld\n",
               (long)iv_info->step, n, (long)elem_size);
    }

  /* Create intermediate pointer SSA names.  */
  tree ptr_type = TREE_TYPE (iv_info->phi_result);
  tree *new_ptrs = XALLOCAVEC (tree, n);

  new_ptrs[0] = iv_info->phi_result;  /* First access uses original PHI result */

  /* Process each access except the last.  */
  for (unsigned i = 0; i < n - 1; i++)
    {
      mem_access_info *acc = &accesses[i];
      gimple_stmt_iterator gsi = gsi_for_stmt (acc->stmt);

      /* Create new pointer: ptr_new = ptr_cur + elem_size  */
      new_ptrs[i + 1] = make_ssa_name (ptr_type);

      tree offset_cst = build_int_cst (sizetype, elem_size);
      gimple *inc_stmt = gimple_build_assign (new_ptrs[i + 1],
                                              POINTER_PLUS_EXPR,
                                              new_ptrs[i], offset_cst);

      /* Insert increment after the memory access.  */
      gsi_insert_after (&gsi, inc_stmt, GSI_NEW_STMT);

      if (dump_file)
        {
          fprintf (dump_file, "  Inserted increment after access %u: ", i);
          print_gimple_stmt (dump_file, inc_stmt, 0, TDF_SLIM);
        }
    }

  /* Rewrite memory accesses to use offset 0 with new base pointers.  */
  for (unsigned i = 0; i < n; i++)
    {
      mem_access_info *acc = &accesses[i];
      tree new_mem_ref;

      /* Build MEM_REF with offset 0 from new base.  */
      tree mem_type = TREE_TYPE (acc->mem_ref);
      tree alias_type = TREE_TYPE (TREE_OPERAND (acc->mem_ref, 1));
      new_mem_ref = build2 (MEM_REF, mem_type, new_ptrs[i],
                            build_int_cst (alias_type, 0));

      /* Replace the memory reference in the statement.  */
      if (acc->is_store)
        gimple_assign_set_lhs (acc->stmt, new_mem_ref);
      else
        gimple_assign_set_rhs1 (acc->stmt, new_mem_ref);

      update_stmt (acc->stmt);

      if (dump_file)
        {
          fprintf (dump_file, "  Rewrote access %u: ", i);
          print_gimple_stmt (dump_file, acc->stmt, 0, TDF_SLIM);
        }
    }

  /* Update the final increment to use the last intermediate pointer.  */
  gimple *old_inc = iv_info->increment_stmt;
  gimple_assign_set_rhs1 (old_inc, new_ptrs[n - 1]);
  gimple_assign_set_rhs2 (old_inc, build_int_cst (sizetype, elem_size));
  update_stmt (old_inc);

  if (dump_file)
    {
      fprintf (dump_file, "  Updated final increment: ");
      print_gimple_stmt (dump_file, old_inc, 0, TDF_SLIM);
    }

  return true;
}

/* Process a single loop, looking for opportunities to split increments.  */

static bool
process_loop (class loop *loop)
{
  bool changed = false;

  /* Look at PHI nodes at loop header for pointer IVs.  */
  for (gphi_iterator gpi = gsi_start_phis (loop->header);
       !gsi_end_p (gpi); gsi_next (&gpi))
    {
      gphi *phi = gpi.phi ();
      tree phi_result = gimple_phi_result (phi);

      /* Only consider pointer types.  */
      if (!POINTER_TYPE_P (TREE_TYPE (phi_result)))
        continue;

      ptr_iv_info iv_info;
      iv_info.phi_result = phi_result;
      iv_info.phi = phi;
      iv_info.accesses.create (8);

      /* Find the increment statement.  */
      iv_info.increment_stmt = find_ptr_increment (loop, phi_result,
                                                   &iv_info.step,
                                                   &iv_info.increment_ssa);
      if (!iv_info.increment_stmt)
        {
          iv_info.accesses.release ();
          continue;
        }

      /* Collect memory accesses using this pointer.  */
      collect_mem_accesses (loop, phi_result, &iv_info.accesses);

      if (iv_info.accesses.length () < 2)
        {
          iv_info.accesses.release ();
          continue;
        }

      /* Check if accesses are sequential and suitable for splitting.  */
      HOST_WIDE_INT elem_size = check_sequential_accesses (iv_info.accesses,
                                                           iv_info.step);
      if (elem_size == 0)
        {
          iv_info.accesses.release ();
          continue;
        }

      if (dump_file)
        {
          fprintf (dump_file, "\nFound splittable pattern in loop %d:\n",
                   loop->num);
          fprintf (dump_file, "  %u accesses, step %ld, elem_size %ld\n",
                   iv_info.accesses.length (), (long)iv_info.step,
                   (long)elem_size);
        }

      /* Perform the transformation.  */
      if (split_combined_increment (loop, &iv_info, elem_size))
        changed = true;

      iv_info.accesses.release ();
    }

  return changed;
}

/* Main entry point for the autoinc split pass.  */

static unsigned int
m68k_autoinc_split (void)
{
  bool changed = false;

  /* Check if target benefits from this transformation.  */
  if (!target_needs_autoinc_split ())
    {
      if (dump_file)
        fprintf (dump_file, "Target does not need autoinc split.\n");
      return 0;
    }

  if (dump_file)
    fprintf (dump_file, "\n;; Autoinc split pass\n\n");

  /* Process each loop.  */
  for (auto loop : loops_list (cfun, LI_FROM_INNERMOST))
    {
      if (loop_outer (loop))  /* Skip outermost pseudo-loop.  */
        {
          if (process_loop (loop))
            changed = true;
        }
    }

  if (changed)
    {
      /* SSA was modified, need to update.  */
      return TODO_update_ssa;
    }

  return 0;
}

const pass_data m68k_pass_data_autoinc_split =
{
  GIMPLE_PASS, /* type */
  "m68k-autoinc-split", /* name */
  OPTGROUP_LOOP, /* optinfo_flags */
  TV_TREE_LOOP_IVOPTS, /* tv_id - share with ivopts for now */
  ( PROP_cfg | PROP_ssa ), /* properties_required */
  0, /* properties_provided */
  0, /* properties_destroyed */
  0, /* todo_flags_start */
  0, /* todo_flags_finish */
};

class m68k_pass_autoinc_split : public gimple_opt_pass
{
public:
  m68k_pass_autoinc_split (gcc::context *ctxt)
    : gimple_opt_pass (m68k_pass_data_autoinc_split, ctxt)
  {}

  /* opt_pass methods: */
  bool gate (function *) final override
  {
    return optimize > 0 && flag_ivopts != 0 && flag_m68k_autoinc;
  }

  unsigned int execute (function *) final override
  {
    return m68k_autoinc_split ();
  }

}; // class m68k_pass_autoinc_split


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
   GIMPLE pass: m68k_pass_reorder_mem

   This pass reorders memory accesses through a base pointer to enable
   sequential access patterns.  Supports both loads and stores.

   Problem: When source code accesses struct fields or array elements in
   non-sequential order, the compiler cannot optimize to post-increment
   addressing or merge adjacent accesses.

   Example:
     s->d = 0;  // offset 6
     s->b = 0;  // offset 2
     s->c = 0;  // offset 4
     s->a = 0;  // offset 0

   This produces scattered accesses that prevent store merging and
   post-increment.  After reordering:
     s->a = 0;  // offset 0
     s->b = 0;  // offset 2
     s->c = 0;  // offset 4
     s->d = 0;  // offset 6

   The sequential pattern enables store merging (two clr.l) and
   post-increment addressing (clr.l (%a0)+).

   The pass uses GCC's alias oracle to verify reordering is safe
   (no RAW/WAR/WAW dependency violations).
   ======================================================================= */

/* Information about a memory access for reordering.  */

struct reorder_mem_info
{
  gimple *stmt;           /* The statement.  */
  tree mem_ref;           /* The MEM_REF tree.  */
  tree base;              /* Base pointer SSA name.  */
  HOST_WIDE_INT offset;   /* Constant offset from base.  */
  HOST_WIDE_INT size;     /* Access size in bytes.  */
  bool is_store;          /* True if store, false if load.  */
  unsigned orig_order;    /* Original position in basic block.  */
  tree store_rhs;         /* For stores: the value being stored.  */
  tree load_lhs;          /* For loads: the SSA name defined.  */
};

/* Check if MEM is a memory reference with constant offset from a base pointer.
   Handles MEM_REF, COMPONENT_REF (struct fields), and ARRAY_REF.
   If so, return the base in *BASE_OUT, offset in *OFFSET_OUT,
   and size in *SIZE_OUT (in bytes).  Returns true on success.  */

static bool
get_mem_ref_base_offset (tree mem, tree *base_out, HOST_WIDE_INT *offset_out,
			 HOST_WIDE_INT *size_out)
{
  /* Use get_ref_base_and_extent to handle all memory reference types.  */
  poly_int64 offset, size, max_size;
  bool reverse;

  tree base = get_ref_base_and_extent (mem, &offset, &size, &max_size, &reverse);

  /* We need constant offset and size.  */
  if (!offset.is_constant () || !size.is_constant ())
    return false;

  /* Size must match max_size (no variable-sized access).  */
  if (!known_eq (size, max_size))
    return false;

  /* For struct field access via pointer, base will be MEM_REF[ptr, 0].
     For direct struct access, base will be the VAR_DECL.
     We want to group by the pointer for indirect access.  */
  if (TREE_CODE (base) == MEM_REF)
    {
      tree ptr = TREE_OPERAND (base, 0);
      tree mem_offset = TREE_OPERAND (base, 1);

      /* Only handle SSA name pointers.  */
      if (TREE_CODE (ptr) != SSA_NAME)
	return false;

      /* Add the MEM_REF's offset to our offset.  */
      if (TREE_CODE (mem_offset) == INTEGER_CST)
	offset += tree_to_shwi (mem_offset) * BITS_PER_UNIT;

      *base_out = ptr;
      *offset_out = offset.to_constant () / BITS_PER_UNIT;
      *size_out = size.to_constant () / BITS_PER_UNIT;
      return true;
    }

  /* For direct memory access (array or local struct), the base is the decl.  */
  if (VAR_P (base) || TREE_CODE (base) == PARM_DECL)
    {
      *base_out = base;
      *offset_out = offset.to_constant () / BITS_PER_UNIT;
      *size_out = size.to_constant () / BITS_PER_UNIT;
      return true;
    }

  return false;
}

/* Check if tree is a memory reference we can analyze.  */

static bool
is_mem_ref_p (tree t)
{
  enum tree_code code = TREE_CODE (t);
  return (code == MEM_REF
	  || code == COMPONENT_REF
	  || code == ARRAY_REF
	  || code == TARGET_MEM_REF);
}

/* Collect memory accesses in basic block BB grouped by base pointer.
   Returns a map from base SSA name to vector of access info.  */

static void
collect_bb_mem_accesses (basic_block bb,
			 hash_map<tree, auto_vec<reorder_mem_info> *> &base_map)
{
  unsigned order = 0;

  for (gimple_stmt_iterator gsi = gsi_start_bb (bb);
       !gsi_end_p (gsi); gsi_next (&gsi), order++)
    {
      gimple *stmt = gsi_stmt (gsi);

      if (!gimple_assign_single_p (stmt))
	continue;

      tree lhs = gimple_assign_lhs (stmt);
      tree rhs = gimple_assign_rhs1 (stmt);

      tree mem_ref = NULL_TREE;
      bool is_store = false;

      /* Check for store: MEM_REF/COMPONENT_REF = value.  */
      if (is_mem_ref_p (lhs))
	{
	  mem_ref = lhs;
	  is_store = true;
	}
      /* Check for load: result = MEM_REF/COMPONENT_REF.  */
      else if (is_mem_ref_p (rhs))
	{
	  mem_ref = rhs;
	  is_store = false;
	}
      else
	continue;

      tree base;
      HOST_WIDE_INT offset, size;
      if (!get_mem_ref_base_offset (mem_ref, &base, &offset, &size))
	continue;

      if (size <= 0)
	continue;

      /* Record this access.  */
      reorder_mem_info info;
      info.stmt = stmt;
      info.mem_ref = mem_ref;
      info.base = base;
      info.offset = offset;
      info.size = size;
      info.is_store = is_store;
      info.orig_order = order;
      info.store_rhs = is_store ? rhs : NULL_TREE;
      info.load_lhs = is_store ? NULL_TREE : lhs;

      /* Add to base's access list.  */
      auto_vec<reorder_mem_info> **slot = base_map.get (base);
      if (!slot)
	{
	  auto_vec<reorder_mem_info> *v = new auto_vec<reorder_mem_info> ();
	  base_map.put (base, v);
	  slot = base_map.get (base);
	}
      (*slot)->safe_push (info);
    }
}

/* Comparison function for sorting by offset.  */

static int
compare_reorder_offset (const void *a, const void *b)
{
  const reorder_mem_info *ma = (const reorder_mem_info *) a;
  const reorder_mem_info *mb = (const reorder_mem_info *) b;

  if (ma->offset < mb->offset)
    return -1;
  if (ma->offset > mb->offset)
    return 1;
  /* Stable sort by original order for same offset.  */
  if (ma->orig_order < mb->orig_order)
    return -1;
  if (ma->orig_order > mb->orig_order)
    return 1;
  return 0;
}

/* Check for memory dependency between two accesses.
   Returns true if moving A after B would violate a dependency.

   Dependencies:
   - RAW (true): A writes, B reads same location
   - WAR (anti): A reads, B writes same location
   - WAW (output): A writes, B writes same location (reordering changes
     which write is visible after both complete)  */

static bool
has_mem_dependency (const reorder_mem_info &a, const reorder_mem_info &b)
{
  /* Same base pointer - check if offset ranges overlap.  */
  if (a.base == b.base)
    {
      bool overlap = (a.offset < b.offset + b.size
		      && b.offset < a.offset + a.size);

      if (overlap)
	{
	  /* RAW: A writes, B reads.  */
	  if (a.is_store && !b.is_store)
	    return true;

	  /* WAR: A reads, B writes.  */
	  if (!a.is_store && b.is_store)
	    return true;

	  /* WAW: Both write.  */
	  if (a.is_store && b.is_store)
	    return true;
	}

      /* No overlap with same base = no memory dependency.  */
      return false;
    }

  /* Different bases - use alias oracle.  */
  if (a.is_store && !b.is_store)
    {
      /* RAW: check if B may read what A writes.  */
      if (ref_maybe_used_by_stmt_p (b.stmt, a.mem_ref))
	return true;
    }
  else if (!a.is_store && b.is_store)
    {
      /* WAR: check if B may write what A reads.  */
      if (stmt_may_clobber_ref_p (b.stmt, a.mem_ref))
	return true;
    }
  else if (a.is_store && b.is_store)
    {
      /* WAW: check if both may write same location.  */
      if (refs_may_alias_p (a.mem_ref, b.mem_ref))
	return true;
    }

  return false;
}

/* Check for SSA def-use dependency.
   Returns true if moving A after B would violate a dependency.  */

static bool
has_ssa_dependency (const reorder_mem_info &a, const reorder_mem_info &b)
{
  /* If A is a store, it doesn't define an SSA value that B could use.  */
  if (a.is_store)
    return false;

  /* A is a load - check if B uses the loaded value.  */
  tree def = a.load_lhs;
  if (!def || TREE_CODE (def) != SSA_NAME)
    return false;

  /* Check if B's statement uses def.  */
  ssa_op_iter iter;
  use_operand_p use_p;
  FOR_EACH_SSA_USE_OPERAND (use_p, b.stmt, iter, SSA_OP_USE)
    {
      if (USE_FROM_PTR (use_p) == def)
	return true;
    }

  /* Also check if B is a store and the stored value uses def.  */
  if (b.is_store && b.store_rhs && TREE_CODE (b.store_rhs) == SSA_NAME)
    {
      if (b.store_rhs == def)
	return true;
    }

  return false;
}

/* Check for virtual SSA (memory SSA) dependency.
   Returns true if moving A after B would violate a VDEF/VUSE chain.

   In GIMPLE's memory SSA model:
   - Stores create a new memory version: VDEF(.MEM_new) with VUSE(.MEM_old)
   - Loads read a memory version: VUSE(.MEM_x)

   If A's VDEF is used as B's VUSE, then A must come before B.  */

static bool
has_vssa_dependency (const reorder_mem_info &a, const reorder_mem_info &b)
{
  /* Get A's VDEF (if it defines a memory version).  */
  tree a_vdef = gimple_vdef (a.stmt);
  if (!a_vdef)
    return false;

  /* Get B's VUSE (if it uses a memory version).  */
  tree b_vuse = gimple_vuse (b.stmt);
  if (!b_vuse)
    return false;

  /* If B uses the memory version that A defines, A must come before B.  */
  if (a_vdef == b_vuse)
    return true;

  /* Also check the VUSE chain: if B's VUSE is defined by a statement
     that comes after A in the VDEF chain, there's still a dependency.
     For simplicity, we use a conservative check: if A has a VDEF and
     B has a VUSE, and they're accessing overlapping memory, don't reorder.

     Actually, the memory aliasing checks in has_mem_dependency should
     catch most cases.  The key case we need to handle is when A's VDEF
     is directly used by B's VUSE.  */

  return false;
}

/* Check if a group member being moved past an intervening (non-group)
   statement would violate a dependency.  Returns true if unsafe.  */

static bool
has_intervening_dependency (const reorder_mem_info &moved, gimple *inter)
{
  /* Check SSA def-use first: does the intervening stmt define a value
     used by the moved stmt?  This must be checked even for non-memory
     statements (e.g., pure computations like casts or shifts).  */
  {
    ssa_op_iter iter;
    use_operand_p use_p;
    FOR_EACH_SSA_USE_OPERAND (use_p, moved.stmt, iter, SSA_OP_USE)
      {
	tree use = USE_FROM_PTR (use_p);
	if (TREE_CODE (use) == SSA_NAME
	    && SSA_NAME_DEF_STMT (use) == inter)
	  return true;
      }
  }

  /* Check reverse SSA: does the moved stmt define a value used by
     the intervening stmt?  */
  if (!moved.is_store && moved.load_lhs
      && TREE_CODE (moved.load_lhs) == SSA_NAME)
    {
      ssa_op_iter iter;
      use_operand_p use_p;
      FOR_EACH_SSA_USE_OPERAND (use_p, inter, iter, SSA_OP_USE)
	{
	  if (USE_FROM_PTR (use_p) == moved.load_lhs)
	    return true;
	}
    }

  /* If the intervening statement doesn't touch memory, no further
     checks needed (SSA deps already handled above).  */
  if (!gimple_vuse (inter))
    return false;

  /* Calls, asm, etc. are conservatively treated as barriers.  */
  if (!is_gimple_assign (inter))
    return true;

  /* Check memory aliasing.  */
  if (moved.is_store)
    {
      /* Moved stmt writes.  Intervening reads or writes same loc?  */
      if (ref_maybe_used_by_stmt_p (inter, moved.mem_ref))
	return true;
      if (gimple_vdef (inter)
	  && stmt_may_clobber_ref_p (inter, moved.mem_ref))
	return true;
    }
  else
    {
      /* Moved stmt reads.  Intervening writes same loc?  */
      if (gimple_vdef (inter)
	  && stmt_may_clobber_ref_p (inter, moved.mem_ref))
	return true;
    }

  return false;
}

/* Check if the given accesses can be safely reordered by offset.
   Returns true if reordering is both safe and beneficial.  */

static bool
can_reorder_accesses (auto_vec<reorder_mem_info> &accesses)
{
  unsigned n = accesses.length ();
  if (n < 2)
    return false;

  /* Build a temporary copy sorted by offset.  */
  auto_vec<reorder_mem_info> sorted;
  sorted.reserve (n);
  for (unsigned i = 0; i < n; i++)
    sorted.quick_push (accesses[i]);
  sorted.qsort (compare_reorder_offset);

  /* Check if already in order.  */
  bool needs_reorder = false;
  for (unsigned i = 1; i < n; i++)
    {
      if (sorted[i].orig_order < sorted[i - 1].orig_order)
	{
	  needs_reorder = true;
	  break;
	}
    }

  if (!needs_reorder)
    return false;

  /* Check all pairs within the group for dependencies that would be
     violated by reordering.  */
  for (unsigned i = 0; i < n; i++)
    {
      for (unsigned j = i + 1; j < n; j++)
	{
	  if (sorted[j].orig_order < sorted[i].orig_order)
	    {
	      /* j originally came first, will now come after i.  */
	      if (has_mem_dependency (sorted[j], sorted[i]))
		return false;
	      if (has_ssa_dependency (sorted[j], sorted[i]))
		return false;
	    }
	}
    }

  /* Find the first and last group members by position.  */
  gimple *first_stmt = accesses[0].stmt;
  gimple *last_stmt = accesses[0].stmt;
  unsigned min_order = accesses[0].orig_order;
  unsigned max_order = accesses[0].orig_order;
  for (unsigned i = 1; i < n; i++)
    {
      if (accesses[i].orig_order < min_order)
	{
	  min_order = accesses[i].orig_order;
	  first_stmt = accesses[i].stmt;
	}
      if (accesses[i].orig_order > max_order)
	{
	  max_order = accesses[i].orig_order;
	  last_stmt = accesses[i].stmt;
	}
    }

  /* If contiguous, no intervening statements to worry about.  */
  if (max_order - min_order + 1 == n)
    return true;

  /* Non-contiguous: check each intervening (non-group) statement
     for dependencies with any group member.  */
  hash_set<gimple *> group_stmts;
  for (unsigned i = 0; i < n; i++)
    group_stmts.add (accesses[i].stmt);

  gimple_stmt_iterator gsi = gsi_for_stmt (first_stmt);
  for (gsi_next (&gsi); gsi_stmt (gsi) != last_stmt; gsi_next (&gsi))
    {
      gimple *inter = gsi_stmt (gsi);

      if (group_stmts.contains (inter) || is_gimple_debug (inter))
	continue;

      /* Conservative: check every group member against this
	 intervening statement.  */
      for (unsigned i = 0; i < n; i++)
	{
	  if (has_intervening_dependency (accesses[i], inter))
	    return false;
	}
    }

  return true;
}

/* Perform the reordering transformation.
   Moves statements so they are ordered by memory offset.  */

static bool
reorder_mem_accesses (auto_vec<reorder_mem_info> &accesses)
{
  if (!can_reorder_accesses (accesses))
    return false;

  unsigned n = accesses.length ();

  /* Sort by offset.  */
  accesses.qsort (compare_reorder_offset);

  /* Find the earliest original position - this is our insertion point.  */
  unsigned earliest_order = UINT_MAX;
  gimple *earliest_stmt = NULL;
  for (unsigned i = 0; i < n; i++)
    {
      if (accesses[i].orig_order < earliest_order)
	{
	  earliest_order = accesses[i].orig_order;
	  earliest_stmt = accesses[i].stmt;
	}
    }

  if (!earliest_stmt)
    return false;

  /* Move all statements to be consecutive starting at earliest position.
     Process in offset order (which is now the array order).  */
  gimple_stmt_iterator insert_gsi = gsi_for_stmt (earliest_stmt);

  for (unsigned i = 0; i < n; i++)
    {
      gimple *stmt = accesses[i].stmt;

      if (stmt == gsi_stmt (insert_gsi))
	{
	  /* Already in position.  */
	  gsi_next (&insert_gsi);
	}
      else
	{
	  /* Move to current position.  */
	  gimple_stmt_iterator stmt_gsi = gsi_for_stmt (stmt);
	  gsi_move_before (&stmt_gsi, &insert_gsi);
	  /* insert_gsi now points to the statement after the moved one,
	     which is correct for the next iteration.  */
	}
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "m68k: Reordered %u memory accesses by offset\n", n);
      for (unsigned i = 0; i < n; i++)
	{
	  fprintf (dump_file, "  offset %ld: ", (long) accesses[i].offset);
	  print_gimple_stmt (dump_file, accesses[i].stmt, 0, TDF_SLIM);
	}
    }

  return true;
}

/* Main function for the reorder_mem pass.  */

static unsigned int
m68k_reorder_mem (function *fun)
{
  bool changed = false;
  basic_block bb;

  FOR_EACH_BB_FN (bb, fun)
    {
      hash_map<tree, auto_vec<reorder_mem_info> *> base_map;

      /* Collect memory accesses grouped by base pointer.  */
      collect_bb_mem_accesses (bb, base_map);

      /* Try to reorder each group.  */
      for (auto iter = base_map.begin (); iter != base_map.end (); ++iter)
	{
	  auto_vec<reorder_mem_info> *accesses = (*iter).second;

	  if (accesses->length () >= 2)
	    {
	      if (reorder_mem_accesses (*accesses))
		changed = true;
	    }

	  delete accesses;
	}
    }

  if (changed)
    {
      /* Force a complete rebuild of virtual SSA, since we moved
	 statements and their VDEF/VUSE chains are now stale.  */
      mark_virtual_operands_for_renaming (fun);
      return TODO_update_ssa_only_virtuals;
    }

  return 0;
}

/* Pass data for m68k_pass_reorder_mem.  */

const pass_data m68k_pass_data_reorder_mem =
{
  GIMPLE_PASS,		/* type */
  "m68k-reorder-mem",	/* name */
  OPTGROUP_NONE,	/* optinfo_flags */
  TV_MACH_DEP,		/* tv_id */
  PROP_cfg | PROP_ssa,	/* properties_required */
  0,			/* properties_provided */
  0,			/* properties_destroyed */
  0,			/* todo_flags_start */
  0			/* todo_flags_finish */
};

/* The pass class for reorder_mem.  */

class m68k_pass_reorder_mem : public gimple_opt_pass
{
public:
  m68k_pass_reorder_mem (gcc::context *ctxt)
    : gimple_opt_pass (m68k_pass_data_reorder_mem, ctxt)
  {}

  bool gate (function *) final override
  {
    /* Only run at -O2 or higher, not at -Os.  */
    return optimize >= 2 && !optimize_size && flag_m68k_reorder_mem;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_reorder_mem (func);
  }

}; /* class m68k_pass_reorder_mem */

} /* anonymous namespace */

/* Factory function for m68k_pass_autoinc_split.  */

gimple_opt_pass *
make_m68k_pass_autoinc_split (gcc::context *ctxt)
{
  return new m68k_pass_autoinc_split (ctxt);
}

/* Factory function for m68k_pass_narrow_index_mult.  */

gimple_opt_pass *
make_m68k_pass_narrow_index_mult (gcc::context *ctxt)
{
  return new m68k_pass_narrow_index_mult (ctxt);
}

/* Factory function for m68k_pass_reorder_mem.  */

gimple_opt_pass *
make_m68k_pass_reorder_mem (gcc::context *ctxt)
{
  return new m68k_pass_reorder_mem (ctxt);
}
