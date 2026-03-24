/* Auto-increment optimization passes for Motorola 68k.
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
#include "df.h"
#include "memmodel.h"
#include "rtl-iter.h"
#include "tm_p.h"
#include "insn-config.h"
#include "regs.h"
#include "emit-rtl.h"
#include "recog.h"
#include "cfgrtl.h"
#include "m68k-util.h"

/* ======================================================================
   GIMPLE pass: m68k_pass_autoinc_split
   ====================================================================== */

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

  /* All accesses must be in the same basic block.  The transformation
     chains SSA names across accesses, so they must be in a single block
     to guarantee SSA dominance.  (With sjlj exceptions, loop bodies can
     have multiple blocks with edges that break dominance.)  */
  basic_block first_bb = gimple_bb (accesses[0].stmt);
  for (unsigned i = 1; i < n; i++)
    {
      if (gimple_bb (accesses[i].stmt) != first_bb)
	return 0;
    }

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

      /* The transformation rewrites the increment statement to use an SSA
	 name defined after the last access.  The increment must be in the
	 same BB as the accesses (which are already verified to be in a
	 single BB by check_sequential_accesses) so the new SSA name
	 dominates its use.  */
      if (gimple_bb (iv_info.increment_stmt)
	  != gimple_bb (iv_info.accesses[0].stmt))
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

} // anonymous namespace (GIMPLE autoinc_split)


/* ======================================================================
   RTL passes: shared helpers, normalize_autoinc, opt_autoinc,
               avail_copy_elim
   ====================================================================== */

namespace {


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

/* Recursively search RTX for MEMs whose address is
   (plus (reg REGNO) (const_int -INCR)) and whose mode size equals INCR.
   If exactly one such MEM is found, set *MEM_LOC to its location and
   return 1.  Returns the count of matching MEMs (0 or 1 means success,
   >1 means ambiguous).  */

static int
find_postinc_candidate (rtx *loc, int regno, HOST_WIDE_INT incr,
			rtx **mem_loc)
{
  rtx x = *loc;
  if (x == NULL_RTX)
    return 0;

  if (MEM_P (x))
    {
      rtx addr = XEXP (x, 0);
      if (GET_CODE (addr) == PLUS
	  && REG_P (XEXP (addr, 0))
	  && (int) REGNO (XEXP (addr, 0)) == regno
	  && CONST_INT_P (XEXP (addr, 1))
	  && INTVAL (XEXP (addr, 1)) == -incr
	  && GET_MODE_SIZE (GET_MODE (x)) == incr)
	{
	  *mem_loc = loc;
	  return 1;
	}
      /* Don't recurse into the MEM's address — we only care about
	 top-level MEMs with the matching pattern.  */
      return 0;
    }

  int count = 0;
  const char *fmt = GET_RTX_FORMAT (GET_CODE (x));
  for (int i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  count += find_postinc_candidate (&XEXP (x, i), regno, incr,
					   mem_loc);
	  if (count > 1)
	    return count;
	}
      else if (fmt[i] == 'E')
	{
	  for (int j = XVECLEN (x, i) - 1; j >= 0; j--)
	    {
	      count += find_postinc_candidate (&XVECEXP (x, i, j), regno,
					       incr, mem_loc);
	      if (count > 1)
		return count;
	    }
	}
    }

  return count;
}

/* Try to merge an increment instruction with the following instruction's
   memory operand into a POST_INC addressing mode.

   This transforms:
     addq.l #N,%aN
     <insn with -N(%aN)>         ; MEM mode size == N

   Into:
     <insn with (%aN)+>          ; POST_INC, addq deleted

   This handles the pattern created by LRA when it decomposes POST_INC
   side effects in cbranch and other patterns.  Works for any instruction
   type (branch, compare, load, store) and any mode size.

   Returns true if the transformation was made.  */

static bool
try_merge_postinc (basic_block bb, rtx_insn *add_insn,
		   int regno, HOST_WIDE_INT incr)
{
  /* Must be an address register (a0-a7 = regs 8-15).  */
  if (regno < 8 || regno > 15)
    return false;

  /* Only handle positive increments.  */
  if (incr <= 0)
    return false;

  /* Find the next real instruction in the same basic block.
     Don't use next_nonnote_nondebug_insn_bb here: it can return a BARRIER
     after an unconditional jump at BB_END (BARRIERs are neither NOTEs
     nor DEBUG_INSNs, so the function doesn't skip them).  */
  rtx_insn *next_insn = next_nonnote_nondebug_insn (add_insn);
  if (!next_insn || !INSN_P (next_insn)
      || BLOCK_FOR_INSN (next_insn) != bb)
    return false;

  /* Find exactly one MEM with matching negative offset.  */
  rtx *mem_loc = nullptr;
  int count = find_postinc_candidate (&PATTERN (next_insn), regno, incr,
				      &mem_loc);
  if (count != 1 || !mem_loc)
    return false;

  /* The address register must not appear as a destination in next_insn
     (apart from inside the MEM we're about to modify).  POST_INC modifies
     the register, so it conflicts with any other write.  */
  rtx set = single_set (next_insn);
  if (set && REG_P (SET_DEST (set))
      && (int) REGNO (SET_DEST (set)) == regno)
    return false;

  /* Save original MEM for rollback.  */
  rtx orig_mem = *mem_loc;

  /* Build POST_INC replacement.  */
  rtx reg = gen_rtx_REG (Pmode, regno);
  machine_mode mode = GET_MODE (orig_mem);
  rtx postinc_addr = gen_rtx_POST_INC (Pmode, reg);
  rtx postinc_mem = gen_rtx_MEM (mode, postinc_addr);
  MEM_COPY_ATTRIBUTES (postinc_mem, orig_mem);

  *mem_loc = postinc_mem;

  /* Validate the transformed instruction.  recog_memoized alone is not
     sufficient: predicates like nonimmediate_operand accept POST_INC, but
     constraint letters may not (e.g. extendsidi2 allows '<' but not '>').
     Use strict=1 since this pass runs after register allocation.  */
  INSN_CODE (next_insn) = -1;
  if (recog_memoized (next_insn) < 0
      || (extract_insn (next_insn),
	  !constrain_operands (1, get_enabled_alternatives (next_insn))))
    {
      /* Restore original.  */
      *mem_loc = orig_mem;
      INSN_CODE (next_insn) = -1;
      recog_memoized (next_insn);
      return false;
    }

  /* Success — apply.  */
  add_reg_note (next_insn, REG_INC, reg);
  df_insn_rescan (next_insn);
  delete_insn (add_insn);

  return true;
}

/* Main function for the normalize_autoinc pass.

   LRA decomposition recovery: merges an increment instruction with the
   immediately following instruction when that instruction uses the register
   with a negative offset equal to the increment and a matching MEM mode size:

     addq.l #1,%a0              →  tst.b (%a0)+
     tst.b -1(%a0)                 (addq deleted)

   This reconstructs POST_INC addressing that LRA decomposed.  Increment
   normalization (moving increments past negative-offset accesses) is now
   handled by the pre-RA pass m68k_pass_opt_autoinc, but LRA may
   re-introduce patterns that need recovery here.  */

static unsigned int
m68k_normalize_autoinc (function *func)
{
  unsigned int changes = 0;
  bool made_changes;

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
	      if (m68k_is_reg_increment (insn, &regno, &incr))
		{
		  if (try_merge_postinc (bb, insn, regno, incr))
		    {
		      changes++;
		      made_changes = true;
		      bb_changed = true;
		      continue;
		    }
		  /* Fall back to increment normalization for patterns
		     that LRA/reload may have re-introduced post-RA.  */
		  if (m68k_try_normalize_increment (bb, insn, regno, incr,
						    true))
		    {
		      changes++;
		      made_changes = true;
		      bb_changed = true;
		    }
		}
	    }
	  if (NONDEBUG_INSN_P (BB_END (bb)))
	    {
	      int regno;
	      HOST_WIDE_INT incr;
	      if (m68k_is_reg_increment (BB_END (bb), &regno, &incr))
		{
		  if (try_merge_postinc (bb, BB_END (bb), regno, incr))
		    {
		      changes++;
		      made_changes = true;
		      bb_changed = true;
		    }
		  else if (m68k_try_normalize_increment (bb, BB_END (bb),
							     regno, incr,
							     true))
		    {
		      changes++;
		      made_changes = true;
		      bb_changed = true;
		    }
		}
	    }

	  if (bb_changed)
	    df_recompute_luids (bb);
	}
    }
  while (made_changes);

  if (dump_file && changes > 0)
    fprintf (dump_file, "m68k-normalize-autoinc: %d changes\n", changes);

  return 0;
}

/* =======================================================================
   RTL pass: m68k_pass_sink_for_rmw

   Pre-RA pass that sinks a hoisted load and duplicates a common store
   into branch BBs, enabling combine to merge load+modify+store into
   a single read-modify-write (RMW) instruction.

   PRE hoists common loads to header BBs.  pass_inc_dec converts them
   to POST_INC.  The store in the merge block uses a compensating
   negative offset.  This separates load/modify/store across BBs,
   preventing combine from creating RMW.

   This pass reassembles them:

     Header:  (set val (mem (post_inc ptr)))     ; hoisted load
              branch
     Branch:  (set out (ior val mask))            ; modify
     Merge:   (set (mem (plus ptr -size)) out)   ; compensating store

   →

     Header:  branch
     Branch:  (set val (mem ptr))                 ; sunk load
              (set out (ior val mask))             ; modify
              (set (mem ptr) out)                  ; sunk store
              (set ptr (plus ptr size))            ; sunk increment

   Then combine merges load+modify+store → (set (mem ptr) (ior (mem ptr) mask))
   and the autoinc pass adds POST_INC → or.w %d3,(%a0)+

   Runs after pass_inc_dec, before pass_combine.
   ======================================================================= */

/* Check if INSN is a modify of REG_VAL using IOR/AND/XOR.
   Returns the operation's other operand (the mask) via *PMASK,
   and the output register via *POUT.  */

static bool
is_rmw_modify_p (rtx_insn *insn, int val_regno, rtx *pmask, rtx *pout)
{
  rtx set = single_set (insn);
  if (!set)
    return false;

  rtx dst = SET_DEST (set);
  rtx src = SET_SRC (set);

  if (!REG_P (dst))
    return false;

  enum rtx_code code = GET_CODE (src);
  if (code != IOR && code != AND && code != XOR)
    return false;

  rtx op0 = XEXP (src, 0);
  rtx op1 = XEXP (src, 1);

  if (REG_P (op0) && (int) REGNO (op0) == val_regno)
    {
      *pmask = op1;
      *pout = dst;
      return true;
    }
  if (REG_P (op1) && (int) REGNO (op1) == val_regno)
    {
      *pmask = op0;
      *pout = dst;
      return true;
    }
  return false;
}

static unsigned int
m68k_sink_for_rmw (function *func)
{
  unsigned int changes = 0;
  basic_block bb;

  FOR_EACH_BB_FN (bb, func)
    {
      /* Header BB must end with a conditional branch.  */
      rtx_insn *branch = BB_END (bb);
      if (!JUMP_P (branch) || !any_condjump_p (branch))
	continue;

      /* Must have exactly 2 successors.  */
      if (EDGE_COUNT (bb->succs) != 2)
	continue;

      /* Find a load with POST_INC in this BB.  */
      rtx_insn *load_insn = nullptr;
      int val_regno = -1;
      int ptr_regno = -1;
      machine_mode load_mode = VOIDmode;
      int load_size = 0;

      for (rtx_insn *insn = BB_HEAD (bb); ; insn = NEXT_INSN (insn))
	{
	  if (NONDEBUG_INSN_P (insn))
	    {
	      rtx set = single_set (insn);
	      if (set && REG_P (SET_DEST (set))
		  && MEM_P (SET_SRC (set))
		  && !MEM_VOLATILE_P (SET_SRC (set)))
		{
		  rtx addr = XEXP (SET_SRC (set), 0);
		  if (GET_CODE (addr) == POST_INC
		      && REG_P (XEXP (addr, 0)))
		    {
		      load_insn = insn;
		      val_regno = REGNO (SET_DEST (set));
		      ptr_regno = REGNO (XEXP (addr, 0));
		      load_mode = GET_MODE (SET_SRC (set));
		      load_size = GET_MODE_SIZE (load_mode);
		      break;
		    }
		}
	    }
	  if (insn == BB_END (bb))
	    break;
	}

      if (!load_insn || val_regno == ptr_regno)
	continue;

      /* Verify: ptr_reg not used in header after the load,
	 and val_reg not used in the branch condition.  */
      rtx ptr_reg = gen_rtx_REG (Pmode, ptr_regno);
      rtx val_reg = gen_rtx_REG (load_mode, val_regno);
      bool safe = true;
      for (rtx_insn *insn = NEXT_INSN (load_insn); ;
	   insn = NEXT_INSN (insn))
	{
	  if (NONDEBUG_INSN_P (insn)
	      && reg_mentioned_p (ptr_reg, PATTERN (insn)))
	    { safe = false; break; }
	  if (insn == BB_END (bb))
	    break;
	}
      if (safe && reg_mentioned_p (val_reg, PATTERN (branch)))
	safe = false;
      if (!safe)
	continue;

      /* Check each branch successor: must have a single modify insn
	 using val_reg, and a single successor (the merge BB).  */
      edge e0 = EDGE_SUCC (bb, 0);
      edge e1 = EDGE_SUCC (bb, 1);
      basic_block succ0 = e0->dest;
      basic_block succ1 = e1->dest;

      /* Each successor must have exactly 1 successor
	 (leading to the merge BB).  */
      if (EDGE_COUNT (succ0->succs) != 1
	  || EDGE_COUNT (succ1->succs) != 1)
	continue;

      basic_block merge0 = EDGE_SUCC (succ0, 0)->dest;
      basic_block merge1 = EDGE_SUCC (succ1, 0)->dest;

      /* Both branches must lead to the same merge BB.  */
      if (merge0 != merge1)
	continue;

      basic_block merge_bb = merge0;

      /* Merge BB must have exactly 2 predecessors.  */
      if (EDGE_COUNT (merge_bb->preds) != 2)
	continue;

      /* Find the modify insn in each successor.  */
      rtx_insn *mod0 = nullptr, *mod1 = nullptr;
      rtx mask0 = nullptr, mask1 = nullptr;
      rtx out0 = nullptr, out1 = nullptr;

      for (rtx_insn *insn = BB_HEAD (succ0); ; insn = NEXT_INSN (insn))
	{
	  if (NONDEBUG_INSN_P (insn))
	    {
	      if (is_rmw_modify_p (insn, val_regno, &mask0, &out0))
		mod0 = insn;
	      break;
	    }
	  if (insn == BB_END (succ0))
	    break;
	}

      for (rtx_insn *insn = BB_HEAD (succ1); ; insn = NEXT_INSN (insn))
	{
	  if (NONDEBUG_INSN_P (insn))
	    {
	      if (is_rmw_modify_p (insn, val_regno, &mask1, &out1))
		mod1 = insn;
	      break;
	    }
	  if (insn == BB_END (succ1))
	    break;
	}

      if (!mod0 || !mod1)
	continue;

      /* Both modifies must write to the same output pseudo.  */
      if (!REG_P (out0) || !REG_P (out1)
	  || REGNO (out0) != REGNO (out1))
	continue;

      int out_regno = REGNO (out0);

      /* Find the store in the merge BB: must be the first real insn,
	 storing out_reg to (plus ptr_reg -load_size).  */
      rtx_insn *store_insn = nullptr;
      for (rtx_insn *insn = BB_HEAD (merge_bb); ;
	   insn = NEXT_INSN (insn))
	{
	  if (NONDEBUG_INSN_P (insn))
	    {
	      rtx set = single_set (insn);
	      if (set && MEM_P (SET_DEST (set))
		  && !MEM_VOLATILE_P (SET_DEST (set))
		  && REG_P (SET_SRC (set))
		  && (int) REGNO (SET_SRC (set)) == out_regno)
		{
		  int mem_regno;
		  HOST_WIDE_INT mem_offset;
		  if (m68k_mem_reg_offset_p (SET_DEST (set),
					     &mem_regno, &mem_offset)
		      && mem_regno == ptr_regno
		      && mem_offset == -load_size)
		    store_insn = insn;
		}
	      break;
	    }
	  if (insn == BB_END (merge_bb))
	    break;
	}

      if (!store_insn)
	continue;

      /* out_reg must be dead after the store.  */
      if (!find_reg_note (store_insn, REG_DEAD, out0))
	continue;

      /* All conditions met — transform.  */

      /* Step 1: Strip POST_INC from the load.  Extract the original
	 pseudo RTXes — reuse them in emitted insns so IRA/LRA track
	 a single pseudo instance (not duplicates from gen_rtx_REG).  */
      rtx load_set = single_set (load_insn);
      rtx orig_val_reg = SET_DEST (load_set);
      rtx load_mem = SET_SRC (load_set);
      rtx orig_postinc_addr = XEXP (load_mem, 0);
      rtx orig_ptr_reg = XEXP (orig_postinc_addr, 0);

      /* Replace (post_inc ptr) with plain ptr.  */
      XEXP (load_mem, 0) = orig_ptr_reg;
      rtx inc_note = find_reg_note (load_insn, REG_INC, nullptr);
      if (inc_note)
	remove_note (load_insn, inc_note);
      INSN_CODE (load_insn) = -1;
      recog_memoized (load_insn);

      /* Get the original store's output register.  */
      rtx store_set = single_set (store_insn);
      rtx orig_out_reg = SET_SRC (store_set);
      rtx orig_store_mem = SET_DEST (store_set);

      /* Step 2: For each branch, emit load + store + increment.  */
      for (int i = 0; i < 2; i++)
	{
	  rtx_insn *mod_insn = (i == 0) ? mod0 : mod1;

	  /* Emit plain load before the modify.  Reuse the pseudo
	     RTXes from the original insns.  */
	  rtx new_mem = gen_rtx_MEM (load_mode, orig_ptr_reg);
	  MEM_COPY_ATTRIBUTES (new_mem, load_mem);
	  rtx new_load_pat = gen_rtx_SET (orig_val_reg, new_mem);
	  rtx_insn *ld = emit_insn_before (new_load_pat, mod_insn);
	  INSN_CODE (ld) = -1;
	  recog_memoized (ld);

	  /* Emit plain store after the modify.  */
	  rtx st_mem = gen_rtx_MEM (load_mode, orig_ptr_reg);
	  MEM_COPY_ATTRIBUTES (st_mem, orig_store_mem);
	  rtx new_store_pat = gen_rtx_SET (st_mem, orig_out_reg);
	  rtx_insn *st = emit_insn_after (new_store_pat, mod_insn);
	  INSN_CODE (st) = -1;
	  recog_memoized (st);

	  /* Emit increment after the store.  The SET_DEST and the
	     first PLUS operand must be the SAME RTX pointer so the
	     "0" matching constraint is satisfied.  */
	  rtx new_incr_pat = gen_rtx_SET (
	    orig_ptr_reg,
	    gen_rtx_PLUS (Pmode, orig_ptr_reg, GEN_INT (load_size)));
	  rtx_insn *inc = emit_insn_after (new_incr_pat, st);
	  INSN_CODE (inc) = -1;
	  recog_memoized (inc);
	}

      /* Step 3: Delete original load from header and store from merge.  */
      delete_insn (load_insn);
      delete_insn (store_insn);

      changes++;

      if (dump_file)
	fprintf (dump_file,
		 "m68k-sink-for-rmw: sank load+store from bb %d/bb %d "
		 "into bb %d and bb %d\n",
		 bb->index, merge_bb->index,
		 succ0->index, succ1->index);
    }

  if (changes > 0)
    {
      /* Rebuild the entire insn stream's DF info so subsequent
	 passes (combine, IRA) see correct defs/uses/liveness.  */
      df_insn_rescan_all ();
    }

  if (dump_file && changes > 0)
    fprintf (dump_file, "m68k-sink-for-rmw: %d transformations\n", changes);

  return 0;
}

/* Pass data for m68k_pass_sink_for_rmw.  */

const pass_data m68k_pass_data_sink_for_rmw =
{
  RTL_PASS,		       /* type */
  "m68k-sink-for-rmw",	       /* name */
  OPTGROUP_NONE,	       /* optinfo_flags */
  TV_MACH_DEP,		       /* tv_id */
  0,			       /* properties_required */
  0,			       /* properties_provided */
  0,			       /* properties_destroyed */
  0,			       /* todo_flags_start */
  0			       /* todo_flags_finish */
};

class m68k_pass_sink_for_rmw : public rtl_opt_pass
{
public:
  m68k_pass_sink_for_rmw (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_sink_for_rmw, ctxt)
  {}

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_autoinc && !TARGET_COLDFIRE;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_sink_for_rmw (func);
  }

}; /* class m68k_pass_sink_for_rmw */

/* =======================================================================
   RTL pass: m68k_pass_sink_postinc

   Moves a POST_INC side-effect from a load to a downstream BB where
   the compensating negative-offset access is.  Then normalize_autoinc
   (which runs after this pass) merges addq + store(-offset) into
   store(POST_INC).

   Problem: PRE hoists a common load to the loop header and pass_inc_dec
   converts it to POST_INC.  The store in a downstream merge block then
   compensates with a negative offset (e.g. -2(%a0)).  This wastes cycles
   on the offset addressing mode.

   Transformation:
     Source BB:
       (set reg (mem (post_inc ptr)))     ; load with POST_INC
       ...                                ; insns not using ptr
     Target BB (post-dominator):
       (set (mem (plus ptr -N)) val)      ; store with compensating offset

   Becomes:
     Source BB:
       (set reg (mem ptr))                ; plain load, no side-effect
     Target BB:
       (set ptr (plus ptr N))             ; inserted addq
       (set (mem (plus ptr -N)) val)      ; store (normalize_autoinc merges)

   Runs post-RA, before normalize_autoinc and peephole2.
   ======================================================================= */

/* Scan BB for uses of REGNO.  Returns:
   - The first insn with a MEM using REGNO at negative offset -INCR
     (a postinc candidate), via *OUT_INSN.  Returns 1.
   - If REGNO is referenced but no candidate found, returns -1.
   - If REGNO is not referenced at all, returns 0.  */

static int
scan_bb_for_postinc_target (basic_block bb, int regno, HOST_WIDE_INT incr,
			    rtx_insn **out_insn)
{
  rtx reg = gen_rtx_REG (Pmode, regno);
  bool reg_seen = false;

  for (rtx_insn *insn = BB_HEAD (bb); ; insn = NEXT_INSN (insn))
    {
      if (NONDEBUG_INSN_P (insn))
	{
	  rtx set = single_set (insn);
	  if (set)
	    {
	      rtx *mem_loc = nullptr;
	      int count = find_postinc_candidate (&PATTERN (insn), regno,
						  incr, &mem_loc);
	      if (count == 1 && mem_loc)
		{
		  *out_insn = insn;
		  return 1;
		}
	    }
	  if (!reg_seen
	      && reg_mentioned_p (reg, PATTERN (insn)))
	    reg_seen = true;
	}
      if (insn == BB_END (bb))
	break;
    }

  return reg_seen ? -1 : 0;
}

static unsigned int
m68k_sink_postinc (function *func)
{
  unsigned int changes = 0;
  basic_block bb;
  bool pdom_valid = false;

  FOR_EACH_BB_FN (bb, func)
    {
      /* Find a load with POST_INC in this BB.  */
      rtx_insn *load_insn = nullptr;
      int ptr_regno = -1;
      HOST_WIDE_INT incr = 0;

      for (rtx_insn *insn = BB_HEAD (bb); ; insn = NEXT_INSN (insn))
	{
	  if (NONDEBUG_INSN_P (insn))
	    {
	      rtx set = single_set (insn);
	      if (set && REG_P (SET_DEST (set)) && MEM_P (SET_SRC (set))
		  && !MEM_VOLATILE_P (SET_SRC (set)))
		{
		  rtx addr = XEXP (SET_SRC (set), 0);
		  if (GET_CODE (addr) == POST_INC
		      && REG_P (XEXP (addr, 0)))
		    {
		      load_insn = insn;
		      ptr_regno = REGNO (XEXP (addr, 0));
		      incr = GET_MODE_SIZE (GET_MODE (SET_SRC (set)));
		      break;
		    }
		}
	    }
	  if (insn == BB_END (bb))
	    break;
	}

      if (!load_insn)
	continue;

      /* Must be an address register (post-RA).  */
      if (ptr_regno < 8 || ptr_regno > 15)
	continue;

      /* Verify: ptr not used in source BB after the load.  */
      rtx ptr_reg = gen_rtx_REG (Pmode, ptr_regno);
      bool ptr_used_after = false;
      for (rtx_insn *insn = NEXT_INSN (load_insn); ;
	   insn = NEXT_INSN (insn))
	{
	  if (NONDEBUG_INSN_P (insn)
	      && reg_mentioned_p (ptr_reg, PATTERN (insn)))
	    {
	      ptr_used_after = true;
	      break;
	    }
	  if (insn == BB_END (bb))
	    break;
	}

      if (ptr_used_after)
	continue;

      /* Walk successor BBs to find where ptr is used with -incr offset.
	 Use BFS limited to a small number of BBs.  */
      basic_block target_bb = nullptr;
      rtx_insn *target_insn = nullptr;
      bool valid = true;

      auto_vec<basic_block> worklist;
      auto_bitmap visited;
      bitmap_set_bit (visited, bb->index);

      edge e;
      edge_iterator ei;
      FOR_EACH_EDGE (e, ei, bb->succs)
	{
	  basic_block dest = e->dest;
	  if (dest == EXIT_BLOCK_PTR_FOR_FN (func)
	      || bitmap_bit_p (visited, dest->index))
	    continue;
	  worklist.safe_push (dest);
	  bitmap_set_bit (visited, dest->index);
	}

      while (!worklist.is_empty () && valid)
	{
	  basic_block cur = worklist.pop ();

	  /* Scan this BB for ptr usage: postinc candidate, other
	     reference, or not referenced at all.  */
	  rtx_insn *neg_insn = nullptr;
	  int scan = scan_bb_for_postinc_target (cur, ptr_regno, incr,
						 &neg_insn);
	  if (scan == 1)
	    {
	      if (target_bb && target_bb != cur)
		{
		  /* Multiple target BBs — too complex.  */
		  valid = false;
		  break;
		}
	      target_bb = cur;
	      if (!target_insn)
		target_insn = neg_insn;
	    }
	  else if (scan == -1)
	    {
	      /* ptr used without -incr offset — unsafe.  */
	      valid = false;
	      break;
	    }
	  else
	    {
	      /* ptr not used here, continue to successors.  */
	      FOR_EACH_EDGE (e, ei, cur->succs)
		{
		  basic_block dest = e->dest;
		  if (dest == EXIT_BLOCK_PTR_FOR_FN (func)
		      || bitmap_bit_p (visited, dest->index))
		    continue;
		  worklist.safe_push (dest);
		  bitmap_set_bit (visited, dest->index);
		}
	    }
	}

      if (!valid || !target_bb || !target_insn)
	continue;

      /* Target BB must post-dominate source BB — ensures the increment
	 happens on every path from the load.  */
      if (!pdom_valid)
	{
	  calculate_dominance_info (CDI_POST_DOMINATORS);
	  pdom_valid = true;
	}
      if (!dominated_by_p (CDI_POST_DOMINATORS, bb, target_bb))
	continue;

      /* Strip POST_INC from the load: (mem (post_inc ptr)) → (mem ptr).
	 Save the original for rollback.  */
      rtx load_src = SET_SRC (single_set (load_insn));
      rtx orig_addr = XEXP (load_src, 0);
      rtx plain_addr = copy_rtx (XEXP (orig_addr, 0));

      XEXP (load_src, 0) = plain_addr;

      /* Remove REG_INC note.  */
      rtx inc_note = find_reg_note (load_insn, REG_INC, nullptr);

      if (inc_note)
	remove_note (load_insn, inc_note);

      /* Revalidate the modified load.  */
      INSN_CODE (load_insn) = -1;
      if (recog_memoized (load_insn) < 0)
	{
	  /* Rollback.  */
	  XEXP (load_src, 0) = orig_addr;
	  if (inc_note)
	    add_reg_note (load_insn, REG_INC, ptr_reg);
	  INSN_CODE (load_insn) = -1;
	  recog_memoized (load_insn);
	  continue;
	}

      /* Insert addq before the target insn in the target BB.  */
      rtx add_set = gen_rtx_SET (copy_rtx (ptr_reg),
				 gen_rtx_PLUS (Pmode,
					       copy_rtx (ptr_reg),
					       GEN_INT (incr)));
      rtx_insn *add_insn = emit_insn_before (add_set, target_insn);

      INSN_CODE (add_insn) = -1;
      if (recog_memoized (add_insn) < 0)
	{
	  /* Rollback.  */
	  delete_insn (add_insn);
	  XEXP (load_src, 0) = orig_addr;
	  if (inc_note)
	    add_reg_note (load_insn, REG_INC, ptr_reg);
	  INSN_CODE (load_insn) = -1;
	  recog_memoized (load_insn);
	  continue;
	}

      df_insn_rescan (load_insn);
      df_insn_rescan (add_insn);
      changes++;

      if (dump_file)
	fprintf (dump_file,
		 "m68k-sink-postinc: moved POST_INC r%d from bb %d "
		 "to addq in bb %d\n",
		 ptr_regno, bb->index, target_bb->index);
    }

  if (pdom_valid)
    free_dominance_info (CDI_POST_DOMINATORS);

  if (dump_file && changes > 0)
    fprintf (dump_file, "m68k-sink-postinc: %d transformations\n", changes);

  return 0;
}

/* Pass data for m68k_pass_sink_postinc.  */

const pass_data m68k_pass_data_sink_postinc =
{
  RTL_PASS,		      /* type */
  "m68k-sink-postinc",	      /* name */
  OPTGROUP_NONE,	      /* optinfo_flags */
  TV_MACH_DEP,		      /* tv_id */
  0,			      /* properties_required */
  0,			      /* properties_provided */
  0,			      /* properties_destroyed */
  0,			      /* todo_flags_start */
  TODO_df_finish	      /* todo_flags_finish */
};

/* The pass class for sink_postinc.  */

class m68k_pass_sink_postinc : public rtl_opt_pass
{
public:
  m68k_pass_sink_postinc (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_sink_postinc, ctxt)
  {}

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_autoinc;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_sink_postinc (func);
  }

}; /* class m68k_pass_sink_postinc */

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

/* =======================================================================
   RTL pass: m68k_pass_opt_autoinc

   Pre-register-allocation auto-increment optimization.  This pass runs
   after combine and scheduling (Phase 7) but before IRA (Phase 8), so the
   register allocator sees POST_INC patterns and can assign address registers
   without relying on the IRA ADDR_REGS promotion hook.

   It handles three patterns that stock pass_inc_dec misses:

   1. Multi-step indexed sequences: multiple sequential memory accesses
      through the same pseudo followed by a single increment.
        (pseudo), 4(pseudo), 8(pseudo), addq #12,pseudo
      → (pseudo)+, (pseudo)+, (pseudo)+

   2. Cross-BB post-increment: memory access in predecessor BB + increment
      at top of successor BB, register dead on other edges.

   3. Increment repositioning: increment before negative-offset accesses
      → move increment after, adjust offsets to positive, enabling POST_INC.

   All three patterns exist on pseudos pre-RA.  Moving them here gives IRA
   better information (sees POST_INC, naturally allocates address registers).

   The post-RA normalize_autoinc pass retains LRA decomposition recovery
   (try_merge_postinc) which genuinely requires post-RA.
   ======================================================================= */

/* Validate an insn pre-RA: must be recognized and satisfy at least one
   alternative's constraints in non-strict mode.  */

static bool
validate_insn (rtx_insn *insn)
{
  INSN_CODE (insn) = -1;
  if (recog_memoized (insn) < 0)
    return false;
  extract_insn (insn);
  return constrain_operands (0, get_enabled_alternatives (insn));
}

/* Try to convert a memory access and subsequent offset accesses to POST_INC
   on pseudos (pre-RA version).

   Same logic as try_convert_to_postinc but:
   - No hard-reg range check (works on any pseudo)
   - Uses strict=0 for constraint validation
   - Handles the case where no add insn exists by checking live_out

   Returns true if any transformation was made.  */

static bool
try_convert_to_postinc (basic_block bb, rtx_insn *first_insn,
			       rtx mem, int is_dest)
{
  int regno;
  if (!mem_reg_p (mem, &regno))
    return false;

  /* POST_INC modifies the address register.  We cannot use POST_INC if the
     other operand of the first instruction is the same register.  */
  rtx first_set = single_set (first_insn);
  if (first_set)
    {
      rtx other_op = is_dest ? SET_SRC (first_set) : SET_DEST (first_set);
      if (REG_P (other_op) && (int) REGNO (other_op) == regno)
	return false;
      if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), other_op))
	return false;
    }

  machine_mode mode = GET_MODE (mem);
  int size = GET_MODE_SIZE (mode);

  /* Collect instructions that need offset adjustment.  */
  auto_vec<rtx_insn *> fixup_insns;
  rtx_insn *add_insn = nullptr;
  HOST_WIDE_INT expected_offset = size;

  for (rtx_insn *insn = next_nonnote_nondebug_insn_bb (first_insn);
       insn;
       insn = next_nonnote_nondebug_insn_bb (insn))
    {
      rtx set = single_set (insn);
      if (!set)
	break;

      rtx dest = SET_DEST (set);
      rtx src = SET_SRC (set);

      /* Check for LEA/ADD that increments our register.  */
      int inc_regno;
      HOST_WIDE_INT incr;
      if (m68k_is_reg_increment (insn, &inc_regno, &incr) && inc_regno == regno)
	{
	  if (incr >= size)
	    {
	      add_insn = insn;
	      break;
	    }
	  return false;
	}

      /* Check if register is used in BOTH src and dest.  */
      bool src_uses_reg = reg_mentioned_p (gen_rtx_REG (Pmode, regno), src);
      bool dest_uses_reg = reg_mentioned_p (gen_rtx_REG (Pmode, regno), dest);
      if (src_uses_reg && dest_uses_reg)
	return false;

      /* Check source operand.  */
      int mem_regno;
      HOST_WIDE_INT offset;
      if (MEM_P (src))
	{
	  if (m68k_mem_reg_offset_p (src, &mem_regno, &offset)
	      && mem_regno == regno)
	    {
	      if (offset != expected_offset)
		return false;
	      fixup_insns.safe_push (insn);
	      expected_offset += size;
	      continue;
	    }
	  else if (mem_reg_p (src, &mem_regno) && mem_regno == regno)
	    return false;
	}

      /* Check destination operand.  */
      if (MEM_P (dest))
	{
	  if (m68k_mem_reg_offset_p (dest, &mem_regno, &offset)
	      && mem_regno == regno)
	    {
	      if (offset != expected_offset)
		return false;
	      fixup_insns.safe_push (insn);
	      expected_offset += size;
	      continue;
	    }
	  else if (mem_reg_p (dest, &mem_regno) && mem_regno == regno)
	    return false;
	}

      /* Check for a single nested MEM at the expected offset inside
	 a binary/commutative expression (e.g., add.l d(%pseudo),%dN).
	 Combined insns with two MEMs are split by reorder_incr
	 before this pass, so only single-MEM cases need handling.  */
      if (GET_RTX_CLASS (GET_CODE (src)) == RTX_COMM_ARITH
	  || GET_RTX_CLASS (GET_CODE (src)) == RTX_BIN_ARITH)
	{
	  rtx op0 = XEXP (src, 0);
	  rtx op1 = XEXP (src, 1);
	  int r0 = -1, r1 = -1;
	  HOST_WIDE_INT off0 = 0, off1 = 0;
	  bool m0 = MEM_P (op0)
	    && (mem_reg_p (op0, &r0)
		|| m68k_mem_reg_offset_p (op0, &r0, &off0));
	  bool m1 = MEM_P (op1)
	    && (mem_reg_p (op1, &r1)
		|| m68k_mem_reg_offset_p (op1, &r1, &off1));

	  if (m0 && r0 == regno && off0 == expected_offset && !m1)
	    {
	      fixup_insns.safe_push (insn);
	      expected_offset += size;
	      continue;
	    }
	  else if (m1 && r1 == regno && off1 == expected_offset && !m0)
	    {
	      fixup_insns.safe_push (insn);
	      expected_offset += size;
	      continue;
	    }
	}

      /* If the register is used but not in a recognizable pattern, abort.  */
      if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), PATTERN (insn)))
	return false;
    }

  /* Need at least one fixup instruction.  */
  if (fixup_insns.is_empty ())
    return false;

  /* On 68040, consecutive POST_INC accesses to the same address register
     cause a 1-cycle pipeline interlock per instruction — the address
     register writeback hasn't completed before the next instruction reads
     it.  Offset addressing (base+displacement) avoids the stall.  Skip
     the conversion when we have multiple consecutive memory instructions
     with no intervening work.  Loop autoincrements are not affected — the
     loop body provides enough separation between iterations.
     Note: 68060 does NOT stall here — POST_INC is a zero-stall producer
     on 68060 (MC68060UM §4.2).  Dual-issue is already impossible for
     consecutive memory ops (test 4: at most one data access per pair).  */
  if (TUNE_68040)
    {
      bool all_consecutive = true;
      rtx_insn *prev = first_insn;
      for (rtx_insn *insn : fixup_insns)
	{
	  rtx_insn *next = next_nonnote_nondebug_insn_bb (prev);
	  if (next != insn)
	    {
	      all_consecutive = false;
	      break;
	    }
	  prev = insn;
	}
      if (all_consecutive)
	return false;
    }

  HOST_WIDE_INT add_incr = 0;
  if (add_insn)
    {
      int add_regno;
      if (!m68k_is_reg_increment (add_insn, &add_regno, &add_incr))
	return false;
      if (add_incr < expected_offset)
	return false;
    }
  else
    {
      /* No add instruction — check if register is dead at BB end.  */
      bitmap live_out = df_get_live_out (bb);
      if (bitmap_bit_p (live_out, regno))
	return false;
      add_incr = expected_offset;
    }

  /* Now perform the transformation.  */

  /* 1. Convert first instruction to use POST_INC.
     Use the canonical regno_reg_rtx so that LRA's SET_REGNO in
     lra_final_code_change will update this rtx in place.  */
  rtx reg = regno_reg_rtx[regno];
  rtx postinc_addr = gen_rtx_POST_INC (Pmode, reg);
  rtx postinc_mem = gen_rtx_MEM (mode, postinc_addr);
  MEM_COPY_ATTRIBUTES (postinc_mem, mem);

  /* Find and replace the specific MEM within the insn pattern.
     For top-level MEMs, this replaces SET_SRC or SET_DEST directly.
     For nested MEMs (inside PLUS etc.), it finds the exact MEM rtx.  */
  rtx *mem_ptr = NULL;
  {
    subrtx_ptr_iterator::array_type array;
    FOR_EACH_SUBRTX_PTR (iter, array, &PATTERN (first_insn), NONCONST)
      {
	if (**iter == mem)
	  {
	    mem_ptr = *iter;
	    break;
	  }
      }
  }
  if (!mem_ptr)
    return false;

  *mem_ptr = postinc_mem;

  /* Validate pre-RA: recog + constraints with strict=0.  */
  if (!validate_insn (first_insn))
    {
      *mem_ptr = mem;
      INSN_CODE (first_insn) = -1;
      recog_memoized (first_insn);
      return false;
    }

  add_reg_note (first_insn, REG_INC, reg);
  df_insn_rescan (first_insn);

  /* 2. Fix up subsequent instructions — reduce their offsets.
     Find the MEM at any nesting depth (handles both top-level and
     nested MEMs from split combined insns).  */
  HOST_WIDE_INT current_adj = size;
  for (rtx_insn *insn : fixup_insns)
    {
      /* Find the MEM that references our register.  */
      rtx *mem_loc = NULL;
      rtx set = single_set (insn);
      if (set)
	{
	  /* Try top-level first (common case).  */
	  if (is_dest && MEM_P (SET_DEST (set)))
	    mem_loc = &SET_DEST (set);
	  else if (!is_dest && MEM_P (SET_SRC (set)))
	    mem_loc = &SET_SRC (set);
	  else
	    {
	      /* Search nested — check binary op operands.  */
	      rtx src = SET_SRC (set);
	      if (GET_RTX_CLASS (GET_CODE (src)) == RTX_COMM_ARITH
		  || GET_RTX_CLASS (GET_CODE (src)) == RTX_BIN_ARITH)
		{
		  if (MEM_P (XEXP (src, 0)))
		    mem_loc = &XEXP (src, 0);
		  else if (MEM_P (XEXP (src, 1)))
		    mem_loc = &XEXP (src, 1);
		}
	    }
	}
      if (!mem_loc || !MEM_P (*mem_loc))
	continue;

      rtx old_mem = *mem_loc;
      machine_mode mem_mode = GET_MODE (old_mem);
      int mem_size = GET_MODE_SIZE (mem_mode);

      int mem_regno;
      HOST_WIDE_INT old_offset;
      /* Handle both bare (reg) at offset 0 and (plus reg offset).  */
      if (mem_reg_p (old_mem, &mem_regno))
	old_offset = 0;
      else if (!m68k_mem_reg_offset_p (old_mem, &mem_regno, &old_offset))
	continue;

      HOST_WIDE_INT new_offset = old_offset - current_adj;

      rtx new_addr;
      if (new_offset == 0)
	{
	  new_addr = gen_rtx_POST_INC (Pmode, reg);
	  current_adj += mem_size;
	}
      else
	new_addr = gen_rtx_PLUS (Pmode, reg, GEN_INT (new_offset));

      rtx new_mem = gen_rtx_MEM (mem_mode, new_addr);
      MEM_COPY_ATTRIBUTES (new_mem, old_mem);
      *mem_loc = new_mem;

      if (!validate_insn (insn))
	{
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
	delete_insn (add_insn);
      else if (remaining > 0)
	{
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

/* Check whether REGNO is dead on all successor edges of PRED except
   the edge to BB.  Works on pseudos (pre-RA version).  */

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
   top of this BB into a post-increment load.  Pre-RA version that works
   on pseudos.

   Same pattern as try_cross_bb_postinc but:
   - No hard-reg range check
   - Uses strict=0 for constraint validation  */

static bool
try_cross_bb_postinc (basic_block bb)
{
  bool changed = false;

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
      if (!m68k_is_reg_increment (insn, &regno, &incr))
	break;

      bool is_last = (insn == BB_END (bb));

      /* Increment must be positive.  */
      if (incr <= 0)
	{
	  if (is_last) break;
	  continue;
	}

      /* No prior reads of this register in BB before the increment.  */
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
	 memory access whose mode size equals the increment.  */
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
	    break;

	  rtx dest = SET_DEST (set);
	  rtx src = SET_SRC (set);

	  if (REG_P (dest) && (int) REGNO (dest) == regno)
	    break;

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
	      break;
	    }

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

	  if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), PATTERN (scan)))
	    break;
	}

      if (!load_insn)
	continue;

      /* Verify no other use of the register between load and branch.  */
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

      /* Branch must not use the address register.  */
      if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), PATTERN (branch)))
	continue;

      /* POST_INC destination != source.  */
      rtx set = single_set (load_insn);
      if (!set)
	continue;
      rtx other_op = is_dest ? SET_SRC (set) : SET_DEST (set);
      if (REG_P (other_op) && (int) REGNO (other_op) == regno)
	continue;
      if (reg_mentioned_p (gen_rtx_REG (Pmode, regno), other_op))
	continue;

      /* Build POST_INC and validate pre-RA.
	 Use canonical regno_reg_rtx for LRA's SET_REGNO update.  */
      rtx reg = regno_reg_rtx[regno];
      machine_mode mode = GET_MODE (load_mem);
      rtx postinc_addr = gen_rtx_POST_INC (Pmode, reg);
      rtx postinc_mem = gen_rtx_MEM (mode, postinc_addr);
      MEM_COPY_ATTRIBUTES (postinc_mem, load_mem);

      if (is_dest)
	SET_DEST (set) = postinc_mem;
      else
	SET_SRC (set) = postinc_mem;

      if (!validate_insn (load_insn))
	{
	  if (is_dest)
	    SET_DEST (set) = load_mem;
	  else
	    SET_SRC (set) = load_mem;
	  INSN_CODE (load_insn) = -1;
	  recog_memoized (load_insn);
	  continue;
	}

      add_reg_note (load_insn, REG_INC, reg);
      df_insn_rescan (load_insn);
      delete_insn (insn);
      changed = true;
      break;
    }

  return changed;
}

/* Main function for the opt_autoinc pass.  */

static unsigned int
m68k_opt_autoinc (function *func)
{
  unsigned int changes = 0;

  /* Phase 1: Cross-BB post-increment conversion.  Repeat until stable.
     Note: Sequential access detection and combined-insn splitting run
     in m68k_pass_reorder_incr which is ordered before this pass.  */
  {
    bool made_changes;
    do
      {
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

  /* Phase 2: Increment normalization.  Repeat until stable.  */
  {
    bool made_changes;
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
		if (m68k_is_reg_increment (insn, &regno, &incr))
		  {
		    if (m68k_try_normalize_increment (bb, insn,
						      regno, incr, false))
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
		if (m68k_is_reg_increment (BB_END (bb), &regno, &incr))
		  {
		    if (m68k_try_normalize_increment (bb, BB_END (bb),
						      regno, incr, false))
		      {
			changes++;
			made_changes = true;
			bb_changed = true;
		      }
		  }
	      }

	    if (bb_changed)
	      df_recompute_luids (bb);
	  }
      }
    while (made_changes);
  }

  /* Phase 3: Within-BB multi-step post-increment conversion.  */
  {
    df_analyze ();
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

	    int regno;
	    if (MEM_P (src) && mem_reg_p (src, &regno))
	      {
		if (try_convert_to_postinc (bb, insn, src, 0))
		  {
		    changes++;
		    bb_changed = true;
		  }
	      }
	    /* Also check nested MEMs in compound source expressions.  */
	    else if (GET_RTX_CLASS (GET_CODE (src)) == RTX_COMM_ARITH
		     || GET_RTX_CLASS (GET_CODE (src)) == RTX_BIN_ARITH)
	      {
		rtx op0 = XEXP (src, 0);
		rtx op1 = XEXP (src, 1);
		if (MEM_P (op0) && mem_reg_p (op0, &regno))
		  {
		    if (try_convert_to_postinc (bb, insn, op0, 0))
		      {
			changes++;
			bb_changed = true;
		      }
		  }
		else if (MEM_P (op1) && mem_reg_p (op1, &regno))
		  {
		    if (try_convert_to_postinc (bb, insn, op1, 0))
		      {
			changes++;
			bb_changed = true;
		      }
		  }
	      }

	    if (MEM_P (dest) && mem_reg_p (dest, &regno))
	      {
		if (try_convert_to_postinc (bb, insn, dest, 1))
		  {
		    changes++;
		    bb_changed = true;
		  }
	      }
	  }

	if (bb_changed)
	  df_recompute_luids (bb);
      }
  }

  if (dump_file && changes > 0)
    fprintf (dump_file, "m68k-opt-autoinc: %d changes\n", changes);

  return 0;
}

/* Pass data for m68k_pass_opt_autoinc.  */

const pass_data m68k_pass_data_opt_autoinc =
{
  RTL_PASS,		    /* type */
  "m68k-autoinc",          /* name */
  OPTGROUP_NONE,	    /* optinfo_flags */
  TV_MACH_DEP,		    /* tv_id */
  0,			    /* properties_required */
  0,			    /* properties_provided */
  0,			    /* properties_destroyed */
  0,			    /* todo_flags_start */
  TODO_df_finish	    /* todo_flags_finish */
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


} // anonymous namespace (RTL passes)


/* Factory functions for the passes.  */

gimple_opt_pass *
make_m68k_pass_autoinc_split (gcc::context *ctxt)
{
  return new m68k_pass_autoinc_split (ctxt);
}

rtl_opt_pass *
make_m68k_pass_sink_for_rmw (gcc::context *ctxt)
{
  return new m68k_pass_sink_for_rmw (ctxt);
}

rtl_opt_pass *
make_m68k_pass_sink_postinc (gcc::context *ctxt)
{
  return new m68k_pass_sink_postinc (ctxt);
}

rtl_opt_pass *
make_m68k_pass_normalize_autoinc (gcc::context *ctxt)
{
  return new m68k_pass_normalize_autoinc (ctxt);
}

rtl_opt_pass *
make_m68k_pass_opt_autoinc (gcc::context *ctxt)
{
  return new m68k_pass_opt_autoinc (ctxt);
}

rtl_opt_pass *
make_m68k_pass_avail_copy_elim (gcc::context *ctxt)
{
  return new m68k_pass_avail_copy_elim (ctxt);
}
