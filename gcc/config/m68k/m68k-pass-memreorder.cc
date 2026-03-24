/* Memory access reordering passes for Motorola 68k.
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
#include "df.h"
#include "memmodel.h"
#include "tm_p.h"
#include "insn-config.h"
#include "regs.h"
#include "emit-rtl.h"
#include "recog.h"
#include "cfgrtl.h"
#include "rtl-iter.h"
#include "context.h"
#include "tree-ssa-alias.h"
#include "tree-cfg.h"
#include "tree-dfa.h"
#include "tree-into-ssa.h"
#include "m68k-util.h"

namespace {

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

  /* Check if B's statement uses def.  FOR_EACH_SSA_USE_OPERAND covers
     all SSA uses including the store RHS value.  */
  ssa_op_iter iter;
  use_operand_p use_p;
  FOR_EACH_SSA_USE_OPERAND (use_p, b.stmt, iter, SSA_OP_USE)
    {
      if (USE_FROM_PTR (use_p) == def)
	return true;
    }

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
      /* For stores whose RHS is also a memory reference (e.g.
	 auth->field = au->field), check if the intervening statement
	 clobbers the source.  Without this, a store to the source
	 can be reordered past the read, reading uninitialized data.  */
      if (moved.store_rhs && gimple_vdef (inter)
	  && TREE_CODE (moved.store_rhs) != SSA_NAME
	  && is_mem_ref_p (moved.store_rhs)
	  && stmt_may_clobber_ref_p (inter, moved.store_rhs))
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

/* Information about a constant-address memory access.  */

struct const_addr_info
{
  gimple *stmt;           /* The statement.  */
  tree mem_ref;           /* The MEM_REF tree.  */
  HOST_WIDE_INT abs_addr; /* Absolute byte address.  */
  HOST_WIDE_INT size;     /* Access size in bytes.  */
  bool is_lhs;            /* True if this is the LHS (store).  */
};

/* Comparison function for sorting by absolute address.  */

static int
compare_const_addr (const void *a, const void *b)
{
  const const_addr_info *ca = (const const_addr_info *) a;
  const const_addr_info *cb = (const const_addr_info *) b;

  if (ca->abs_addr < cb->abs_addr)
    return -1;
  if (ca->abs_addr > cb->abs_addr)
    return 1;
  return 0;
}

/* Normalize constant-address bases in BB.

   When loop unrolling produces MEM_REFs with different INTEGER_CST base
   pointers that access contiguous memory, this rewrites them to share
   a common (lowest) base with increasing offsets.  This enables the RTL
   pipeline to use a single address register for the entire sequence.  */

static bool
normalize_constant_address_bases (basic_block bb)
{
  auto_vec<const_addr_info> accesses;

  /* Collect constant-address memory accesses.  */
  for (gimple_stmt_iterator gsi = gsi_start_bb (bb);
       !gsi_end_p (gsi); gsi_next (&gsi))
    {
      gimple *stmt = gsi_stmt (gsi);

      if (!gimple_assign_single_p (stmt))
	continue;

      if (gimple_has_volatile_ops (stmt))
	continue;

      tree lhs = gimple_assign_lhs (stmt);
      tree rhs = gimple_assign_rhs1 (stmt);
      tree mem_ref = NULL_TREE;
      bool is_lhs = false;

      if (TREE_CODE (lhs) == MEM_REF)
	{
	  mem_ref = lhs;
	  is_lhs = true;
	}
      else if (TREE_CODE (rhs) == MEM_REF)
	{
	  mem_ref = rhs;
	  is_lhs = false;
	}
      else
	continue;

      /* The MEM_REF must have an INTEGER_CST pointer (constant address).  */
      tree ptr = TREE_OPERAND (mem_ref, 0);
      tree mem_offset = TREE_OPERAND (mem_ref, 1);

      if (TREE_CODE (ptr) != INTEGER_CST || TREE_CODE (mem_offset) != INTEGER_CST)
	continue;

      /* Resolve full address including any outer COMPONENT_REF etc.  */
      poly_int64 bit_offset, bit_size, bit_max_size;
      bool reverse;
      tree base = get_ref_base_and_extent (mem_ref, &bit_offset, &bit_size,
					   &bit_max_size, &reverse);

      if (!bit_offset.is_constant () || !bit_size.is_constant ())
	continue;
      if (!known_eq (bit_size, bit_max_size))
	continue;

      /* For a plain MEM_REF[int_cst, offset], base should be the MEM_REF
	 itself and bit_offset should be 0 (the offset is in operand 1).
	 Compute the absolute address.  */
      HOST_WIDE_INT abs_addr = tree_to_shwi (ptr) + tree_to_shwi (mem_offset)
			       + bit_offset.to_constant () / BITS_PER_UNIT;
      HOST_WIDE_INT size = bit_size.to_constant () / BITS_PER_UNIT;

      if (size <= 0)
	continue;

      const_addr_info info;
      info.stmt = stmt;
      info.mem_ref = mem_ref;
      info.abs_addr = abs_addr;
      info.size = size;
      info.is_lhs = is_lhs;
      accesses.safe_push (info);
    }

  if (accesses.length () < 2)
    return false;

  /* Sort by absolute address.  */
  accesses.qsort (compare_const_addr);

  bool changed = false;
  unsigned n = accesses.length ();

  /* Partition into contiguous runs and normalize each.  */
  unsigned run_start = 0;
  while (run_start < n)
    {
      unsigned run_end = run_start + 1;
      while (run_end < n
	     && accesses[run_end].abs_addr
		== accesses[run_end - 1].abs_addr
		   + accesses[run_end - 1].size)
	run_end++;

      unsigned run_len = run_end - run_start;
      if (run_len >= 2)
	{
	  HOST_WIDE_INT canonical_base = accesses[run_start].abs_addr;

	  for (unsigned i = run_start; i < run_end; i++)
	    {
	      HOST_WIDE_INT new_offset = accesses[i].abs_addr - canonical_base;
	      tree mem_ref = accesses[i].mem_ref;
	      tree old_ptr = TREE_OPERAND (mem_ref, 0);
	      tree old_off = TREE_OPERAND (mem_ref, 1);

	      /* Skip if already normalized.  */
	      if (tree_to_shwi (old_ptr) == canonical_base
		  && tree_to_shwi (old_off) == new_offset)
		continue;

	      /* Build new MEM_REF with canonical base and new offset.  */
	      tree ptr_type = TREE_TYPE (old_ptr);
	      tree off_type = TREE_TYPE (old_off);
	      tree new_ptr = build_int_cst (ptr_type, canonical_base);
	      tree new_off = build_int_cst (off_type, new_offset);
	      tree mem_type = TREE_TYPE (mem_ref);
	      tree new_mem = build2 (MEM_REF, mem_type, new_ptr, new_off);

	      /* Preserve alignment info.  */
	      if (TREE_THIS_VOLATILE (mem_ref))
		TREE_THIS_VOLATILE (new_mem) = 1;

	      if (accesses[i].is_lhs)
		gimple_assign_set_lhs (accesses[i].stmt, new_mem);
	      else
		gimple_assign_set_rhs1 (accesses[i].stmt, new_mem);

	      update_stmt (accesses[i].stmt);
	      changed = true;

	      if (dump_file && (dump_flags & TDF_DETAILS))
		{
		  fprintf (dump_file,
			   "m68k: Normalized const-addr base to %ld+%ld: ",
			   (long) canonical_base, (long) new_offset);
		  print_gimple_stmt (dump_file, accesses[i].stmt, 0,
				     TDF_SLIM);
		}
	    }
	}

      run_start = run_end;
    }

  return changed;
}

/* Main function for the reorder_mem pass.  */

static unsigned int
m68k_reorder_mem (function *fun)
{
  bool changed = false;
  basic_block bb;

  FOR_EACH_BB_FN (bb, fun)
    {
      /* Normalize constant-address bases first so contiguous accesses
	 to absolute addresses share a common base pointer.  */
      if (normalize_constant_address_bases (bb))
	changed = true;

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
    return optimize > 0 && flag_m68k_reorder_mem;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_reorder_mem (func);
  }

}; /* class m68k_pass_reorder_mem */

} /* anonymous namespace for GIMPLE passes */

/* Factory function for m68k_pass_reorder_mem.  */

gimple_opt_pass *
make_m68k_pass_reorder_mem (gcc::context *ctxt)
{
  return new m68k_pass_reorder_mem (ctxt);
}


/* =======================================================================
   RTL pass: m68k_pass_reorder_incr

   Pre-RA increment normalization.  Moves pointer increment instructions
   past negative-offset memory accesses, adjusting offsets to be positive.

   Problem: IVOPTS places pointer increments in the middle of an access
   sequence, causing some accesses to use negative offsets:

     move.w (%a0),(%a1)
     move.w 2(%a0),2(%a1)
     move.w 4(%a0),4(%a1)
     addq.l #8,%a0            ; increment in middle
     addq.l #8,%a1
     move.w -2(%a0),-2(%a1)   ; negative offset = original offset 6

   After normalization:

     move.w (%a0),(%a1)
     move.w 2(%a0),2(%a1)
     move.w 4(%a0),4(%a1)
     move.w 6(%a0),6(%a1)     ; -2 + 8 = 6
     addq.l #8,%a0            ; moved to end
     addq.l #8,%a1

   This enables the downstream auto-increment pass to convert the
   sequential pattern to POST_INC addressing.

   Runs after scheduling (where the patterns form), before IRA.
   ======================================================================= */

/* Record of a MEM found during BB scanning.  */

struct seq_mem_ref {
  rtx_insn *insn;       /* Containing insn.  */
  rtx *mem_loc;          /* Pointer to the MEM rtx within the insn pattern.  */
  HOST_WIDE_INT offset;  /* Offset from base register.  */
  machine_mode mode;     /* Access mode (SImode, HImode, etc.).  */
};

/* Process a group of sequential MEMs from the same base register.
   REFS must be sorted by offset with fixed stride.
   Inserts lea + rewrites + addq for POST_INC conversion.  */

static bool
process_sequential_refs (auto_vec<seq_mem_ref> &refs, int base_regno)
{
  int n = refs.length ();
  if (n < 2)
    return false;

  HOST_WIDE_INT first_offset = refs[0].offset;
  HOST_WIDE_INT stride = GET_MODE_SIZE (refs[0].mode);

  /* Verify sequential ascending offsets and uniform stride.  */
  for (int i = 1; i < n; i++)
    {
      if (refs[i].offset != first_offset + i * stride)
	return false;
      if (GET_MODE_SIZE (refs[i].mode) != stride)
	return false;
    }

  /* Thresholds.  */
  if (first_offset == 0 && n < 3)
    return false;
  if (first_offset != 0 && n < 2)
    return false;

  HOST_WIDE_INT total = n * stride;

  if (dump_file)
    fprintf (dump_file, "  Sequential run: %d MEMs at %s+%ld, "
	     "stride %ld, total %ld\n",
	     n, reg_names[base_regno], (long) first_offset,
	     (long) stride, (long) total);

  /* Create pseudo pointer and lea.  */
  rtx pseudo = gen_reg_rtx (Pmode);
  rtx base_reg = gen_rtx_REG (Pmode, base_regno);
  rtx lea_src = (first_offset != 0)
    ? gen_rtx_PLUS (Pmode, base_reg, GEN_INT (first_offset))
    : base_reg;

  rtx_insn *lea_insn = emit_insn_before (gen_rtx_SET (pseudo, lea_src),
					  refs[0].insn);
  INSN_CODE (lea_insn) = -1;
  if (recog_memoized (lea_insn) < 0)
    {
      delete_insn (lea_insn);
      return false;
    }

  /* Track old MEMs for revert on failure.  */
  auto_vec<rtx> old_mems;
  for (int i = 0; i < n; i++)
    old_mems.safe_push (*refs[i].mem_loc);

  /* Rewrite each MEM address.  Multiple MEMs per insn are handled
     naturally since each ref has its own mem_loc pointer.  */
  rtx_insn *prev_insn = NULL;
  for (int i = 0; i < n; i++)
    {
      HOST_WIDE_INT new_offset = refs[i].offset - first_offset;
      rtx new_addr = (new_offset == 0)
	? pseudo
	: gen_rtx_PLUS (Pmode, pseudo, GEN_INT (new_offset));

      *refs[i].mem_loc = replace_equiv_address_nv (*refs[i].mem_loc,
						   new_addr);

      /* Validate the insn after all its MEMs for this insn are rewritten.
	 (An insn may have multiple refs — validate once after all are done.)  */
      if (refs[i].insn != prev_insn)
	{
	  if (prev_insn)
	    {
	      INSN_CODE (prev_insn) = -1;
	      if (recog_memoized (prev_insn) < 0)
		goto revert;
	      df_insn_rescan (prev_insn);
	    }
	  prev_insn = refs[i].insn;
	}
    }
  /* Validate the last insn.  */
  if (prev_insn)
    {
      INSN_CODE (prev_insn) = -1;
      if (recog_memoized (prev_insn) < 0)
	goto revert;
      df_insn_rescan (prev_insn);
    }

  /* Insert increment after the last insn.  */
  {
    rtx_insn *last_insn = refs[n - 1].insn;
    rtx_insn *incr_insn = emit_insn_after (
      gen_rtx_SET (pseudo, gen_rtx_PLUS (Pmode, pseudo, GEN_INT (total))),
      last_insn);
    INSN_CODE (incr_insn) = -1;
    if (recog_memoized (incr_insn) < 0)
      delete_insn (incr_insn);
  }

  return true;

 revert:
  for (int i = 0; i < n; i++)
    {
      *refs[i].mem_loc = old_mems[i];
      INSN_CODE (refs[i].insn) = -1;
      recog_memoized (refs[i].insn);
    }
  delete_insn (lea_insn);
  return false;
}

/* Detect sequential memory accesses at ascending offsets from the same
   hard register and synthesize a pointer + increment pattern.  This
   enables downstream opt_autoinc to convert to POST_INC addressing.

   Walks ALL sub-expressions of each insn to find MEMs at any nesting
   depth (stores, loads, arithmetic with MEM operands, combined insns
   with multiple MEMs).  Groups them by base register and offset.

   Thresholds: N >= 3 if first offset is 0, N >= 2 if first offset > 0.  */

static bool
try_sequential_access_to_postinc (basic_block bb)
{
  bool changed = false;

  /* Phase 1: Collect all MEMs with hard-register base + const offset.
     Group by base register.  Use a simple approach: collect for one
     base at a time, process when a different base or non-MEM insn
     is encountered.  */
  auto_vec<seq_mem_ref> refs;
  int current_base = -1;

  rtx_insn *insn;
  FOR_BB_INSNS (bb, insn)
    {
      if (!NONDEBUG_INSN_P (insn))
	continue;

      /* Collect MEMs from this insn for all possible base registers.  */
      auto_vec<seq_mem_ref> insn_refs;
      subrtx_ptr_iterator::array_type array;
      FOR_EACH_SUBRTX_PTR (iter, array, &PATTERN (insn), NONCONST)
	{
	  rtx *loc = *iter;
	  rtx x = *loc;
	  if (!MEM_P (x))
	    continue;

	  rtx addr = XEXP (x, 0);
	  int regno = -1;
	  HOST_WIDE_INT offset = 0;

	  if (REG_P (addr) && REGNO (addr) < FIRST_PSEUDO_REGISTER)
	    {
	      regno = REGNO (addr);
	      offset = 0;
	    }
	  else if (GET_CODE (addr) == PLUS
		   && REG_P (XEXP (addr, 0))
		   && REGNO (XEXP (addr, 0)) < FIRST_PSEUDO_REGISTER
		   && CONST_INT_P (XEXP (addr, 1)))
	    {
	      regno = REGNO (XEXP (addr, 0));
	      offset = INTVAL (XEXP (addr, 1));
	    }

	  if (regno >= 0)
	    {
	      seq_mem_ref ref = { insn, loc, offset, GET_MODE (x) };
	      insn_refs.safe_push (ref);
	    }
	  iter.skip_subrtxes ();
	}

      /* Check if this insn's MEMs extend the current run.  */
      if (insn_refs.is_empty ()
	  || (current_base >= 0
	      && !refs.is_empty ()
	      && insn_refs[0].offset <= refs.last ().offset))
	{
	  /* No MEMs, or non-ascending — process current run.  */
	  if (!refs.is_empty ())
	    {
	      if (process_sequential_refs (refs, current_base))
		changed = true;
	      refs.truncate (0);
	    }
	  if (insn_refs.is_empty ())
	    {
	      current_base = -1;
	      continue;
	    }
	}

      /* Determine base register from this insn's refs.  */
      int insn_base = -1;
      for (unsigned j = 0; j < insn_refs.length (); j++)
	{
	  rtx addr = XEXP (*insn_refs[j].mem_loc, 0);
	  int r = REG_P (addr) ? REGNO (addr) : REGNO (XEXP (addr, 0));
	  if (insn_base < 0)
	    insn_base = r;
	  else if (r != insn_base)
	    { insn_base = -1; break; }
	}

      if (insn_base < 0)
	{
	  if (!refs.is_empty ())
	    {
	      if (process_sequential_refs (refs, current_base))
		changed = true;
	      refs.truncate (0);
	    }
	  current_base = -1;
	  continue;
	}

      /* Start or extend run.  */
      if (current_base != insn_base && !refs.is_empty ())
	{
	  if (process_sequential_refs (refs, current_base))
	    changed = true;
	  refs.truncate (0);
	}
      current_base = insn_base;

      for (unsigned j = 0; j < insn_refs.length (); j++)
	refs.safe_push (insn_refs[j]);

    }

  /* Process remaining run.  */
  if (!refs.is_empty ())
    if (process_sequential_refs (refs, current_base))
      changed = true;

  return changed;
}

namespace {

/* Main function for the reorder_incr pass.  Iterates until stable.  */

static unsigned int
m68k_reorder_incr (function *func)
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
		  if (m68k_try_normalize_increment (bb, insn, regno, incr,
						    false))
		    {
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
		  if (m68k_try_normalize_increment (bb, BB_END (bb),
						    regno, incr, false))
		    {
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

  /* Phase 2: Detect sequential base+offset accesses on hard registers
     and synthesize pointer + increment patterns.  */
  {
    basic_block bb;
    FOR_EACH_BB_FN (bb, func)
      try_sequential_access_to_postinc (bb);
  }

  /* Phase 3: Split combined insns with two MEMs from the same base at
     consecutive offsets into separate load + op insns.  This enables
     opt_autoinc to convert each MEM to POST_INC individually.  */
  {
    basic_block bb;
    FOR_EACH_BB_FN (bb, func)
      {
	rtx_insn *insn, *next;
	for (insn = BB_HEAD (bb); insn != NEXT_INSN (BB_END (bb)); insn = next)
	  {
	    next = NEXT_INSN (insn);
	    if (!NONDEBUG_INSN_P (insn))
	      continue;
	    rtx set = single_set (insn);
	    if (!set)
	      continue;
	    rtx src = SET_SRC (set);
	    if (GET_RTX_CLASS (GET_CODE (src)) != RTX_COMM_ARITH
		&& GET_RTX_CLASS (GET_CODE (src)) != RTX_BIN_ARITH)
	      continue;

	    rtx op0 = XEXP (src, 0);
	    rtx op1 = XEXP (src, 1);
	    if (!MEM_P (op0) || !MEM_P (op1))
	      continue;

	    int r0, r1;
	    HOST_WIDE_INT off0 = 0, off1 = 0;
	    bool m0 = (m68k_mem_reg_offset_p (op0, &r0, &off0)
		       || (REG_P (XEXP (op0, 0)) && (r0 = REGNO (XEXP (op0, 0)), off0 = 0, true)));
	    bool m1 = (m68k_mem_reg_offset_p (op1, &r1, &off1)
		       || (REG_P (XEXP (op1, 0)) && (r1 = REGNO (XEXP (op1, 0)), off1 = 0, true)));

	    if (!m0 || !m1 || r0 != r1)
	      continue;

	    int stride = GET_MODE_SIZE (GET_MODE (op0));
	    if (off1 != off0 + stride)
	      continue;

	    machine_mode mode = GET_MODE (op0);
	    rtx tmp = gen_reg_rtx (mode);
	    rtx_insn *load_insn = emit_insn_before (gen_rtx_SET (tmp, op0), insn);
	    INSN_CODE (load_insn) = -1;
	    if (recog_memoized (load_insn) < 0)
	      {
		delete_insn (load_insn);
		continue;
	      }

	    rtx old_op0 = XEXP (src, 0);
	    XEXP (src, 0) = tmp;
	    INSN_CODE (insn) = -1;
	    if (recog_memoized (insn) < 0)
	      {
		XEXP (src, 0) = old_op0;
		INSN_CODE (insn) = -1;
		recog_memoized (insn);
		delete_insn (load_insn);
		continue;
	      }

	    df_insn_rescan (load_insn);
	    df_insn_rescan (insn);
	  }
      }
  }

  return 0;
}

const pass_data m68k_pass_data_reorder_incr =
{
  RTL_PASS,		  /* type */
  "m68k-reorder-incr",	  /* name */
  OPTGROUP_NONE,	  /* optinfo_flags */
  TV_MACH_DEP,		  /* tv_id */
  0,			  /* properties_required */
  0,			  /* properties_provided */
  0,			  /* properties_destroyed */
  0,			  /* todo_flags_start */
  TODO_df_finish	  /* todo_flags_finish */
};

class m68k_pass_reorder_incr : public rtl_opt_pass
{
public:
  m68k_pass_reorder_incr (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_reorder_incr, ctxt)
  {}

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_autoinc;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_reorder_incr (func);
  }

}; /* class m68k_pass_reorder_incr */

} /* anonymous namespace for RTL passes */

/* Factory function for m68k_pass_reorder_incr.  */

rtl_opt_pass *
make_m68k_pass_reorder_incr (gcc::context *ctxt)
{
  return new m68k_pass_reorder_incr (ctxt);
}
