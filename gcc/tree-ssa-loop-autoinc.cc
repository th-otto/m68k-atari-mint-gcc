/* Split combined pointer increments to enable auto-increment addressing.
   Copyright (C) 2025 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/* This pass splits combined pointer increments back into individual
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
*/

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
tree_ssa_autoinc_split (void)
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

namespace {

const pass_data pass_data_autoinc_split =
{
  GIMPLE_PASS, /* type */
  "autoinc_split", /* name */
  OPTGROUP_LOOP, /* optinfo_flags */
  TV_TREE_LOOP_IVOPTS, /* tv_id - share with ivopts for now */
  ( PROP_cfg | PROP_ssa ), /* properties_required */
  0, /* properties_provided */
  0, /* properties_destroyed */
  0, /* todo_flags_start */
  0, /* todo_flags_finish */
};

class pass_autoinc_split : public gimple_opt_pass
{
public:
  pass_autoinc_split (gcc::context *ctxt)
    : gimple_opt_pass (pass_data_autoinc_split, ctxt)
  {}

  /* opt_pass methods: */
  bool gate (function *) final override
  {
    return optimize > 0 && flag_ivopts != 0;
  }

  unsigned int execute (function *) final override
  {
    return tree_ssa_autoinc_split ();
  }

}; // class pass_autoinc_split

} // anon namespace

gimple_opt_pass *
make_pass_autoinc_split (gcc::context *ctxt)
{
  return new pass_autoinc_split (ctxt);
}
