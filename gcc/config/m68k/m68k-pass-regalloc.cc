/* Register allocation RTL pass for Motorola 68k.
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
#include "rtl-iter.h"

namespace {

/* Try to canonicalize a scaled index in a MEM address.
   Looks for (plus (plus A B) C) where one of {A,B} == C, and rewrites
   to (plus base (ashift C 1)).  Returns true if a change was made.  */

static bool
try_canon_mem_addr (rtx mem)
{
  rtx addr = XEXP (mem, 0);
  if (GET_CODE (addr) != PLUS
      || GET_CODE (XEXP (addr, 0)) != PLUS)
    return false;

  rtx inner = XEXP (addr, 0);
  rtx outer_right = XEXP (addr, 1);

  if (!REG_P (outer_right))
    return false;

  rtx base = NULL_RTX;

  /* (plus (plus A B) C) where B == C → base=A, index=C<<1.  */
  if (rtx_equal_p (XEXP (inner, 1), outer_right)
      && REG_P (XEXP (inner, 0)))
    base = XEXP (inner, 0);
  /* (plus (plus A B) C) where A == C → base=B, index=C<<1.  */
  else if (rtx_equal_p (XEXP (inner, 0), outer_right)
	   && REG_P (XEXP (inner, 1)))
    base = XEXP (inner, 1);

  if (!base)
    return false;

  rtx scaled = gen_rtx_ASHIFT (Pmode, outer_right, const1_rtx);
  XEXP (mem, 0) = gen_rtx_PLUS (Pmode, base, scaled);
  return true;
}

static unsigned int
m68k_canon_scaled_index (function *func)
{
  unsigned int changes = 0;
  basic_block bb;

  FOR_EACH_BB_FN (bb, func)
    {
      rtx_insn *insn;
      FOR_BB_INSNS (bb, insn)
	{
	  if (!NONDEBUG_INSN_P (insn))
	    continue;

	  /* Walk all sub-rtx looking for MEMs with scaled index patterns.
	     Save the pattern first for rollback if recog fails.  */
	  rtx saved_pattern = copy_rtx (PATTERN (insn));
	  bool changed = false;
	  subrtx_ptr_iterator::array_type array;
	  FOR_EACH_SUBRTX_PTR (iter, array, &PATTERN (insn), NONCONST)
	    {
	      rtx x = **iter;
	      if (MEM_P (x) && try_canon_mem_addr (x))
		changed = true;
	    }

	  if (changed)
	    {
	      INSN_CODE (insn) = -1;
	      if (recog_memoized (insn) < 0)
		{
		  /* Revert: restore original pattern.  */
		  PATTERN (insn) = saved_pattern;
		  INSN_CODE (insn) = -1;
		  if (dump_file)
		    fprintf (dump_file,
			     "m68k-canon-scaled-index: insn %d: "
			     "recog failed, reverted\n",
			     INSN_UID (insn));
		}
	      else
		{
		  df_insn_rescan (insn);
		  changes++;
		  if (dump_file)
		    fprintf (dump_file,
			     "m68k-canon-scaled-index: insn %d: "
			     "rewrote to ashift form\n",
			     INSN_UID (insn));
		}
	    }
	}
    }

  if (dump_file && changes > 0)
    fprintf (dump_file, "m68k-canon-scaled-index: %d changes\n", changes);

  return 0;
}

/* Pass data for m68k_pass_canon_scaled_index.  */

const pass_data m68k_pass_data_canon_scaled_index =
{
  RTL_PASS,			 /* type */
  "m68k-canon-scaled-index",	 /* name */
  OPTGROUP_NONE,		 /* optinfo_flags */
  TV_MACH_DEP,			 /* tv_id */
  0,				 /* properties_required */
  0,				 /* properties_provided */
  0,				 /* properties_destroyed */
  0,				 /* todo_flags_start */
  0				 /* todo_flags_finish */
};

/* The pass class for canon_scaled_index.  */

class m68k_pass_canon_scaled_index : public rtl_opt_pass
{
public:
  m68k_pass_canon_scaled_index (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_canon_scaled_index, ctxt)
  {}

  bool gate (function *) final override
  {
    return optimize > 0 && (TARGET_68020 || TARGET_COLDFIRE);
  }

  unsigned int execute (function *func) final override
  {
    return m68k_canon_scaled_index (func);
  }

}; /* class m68k_pass_canon_scaled_index */

} /* anonymous namespace */

rtl_opt_pass *
make_m68k_pass_canon_scaled_index (gcc::context *ctxt)
{
  return new m68k_pass_canon_scaled_index (ctxt);
}

/* Break false partial-write live ranges before IRA.

   When a pseudo is defined via a sequence of partial writes (e.g.,
   bfins for the upper 16 bits + strict_low_part move.w for the lower
   16 bits), DF treats each partial write as a read-modify-write.
   If the pseudo is live-in to the BB (e.g., via a loop back-edge),
   it appears live across calls, causing IRA to allocate it to a
   callee-saved register instead of the argument register.

   This pass detects partial write sequences that fully cover all bits
   of a pseudo and inserts a zero-cost (clobber (reg P)) before the
   first partial write to break the false dependency.  */

namespace {

/* Return the 32-bit bitmask of bits written by SET_DEST for pseudo REGNO,
   or 0 if this is not a partial write to REGNO.  Returns -1 (all bits)
   if this is a full write to REGNO (meaning old value IS live).  */

static unsigned int
partial_write_mask (rtx set, unsigned int regno)
{
  rtx dest = SET_DEST (set);

  /* (set (zero_extract:SI (reg P) (const_int W) (const_int O)) ...) */
  if (GET_CODE (dest) == ZERO_EXTRACT)
    {
      rtx reg = XEXP (dest, 0);
      rtx width_rtx = XEXP (dest, 1);
      rtx offset_rtx = XEXP (dest, 2);
      if (REG_P (reg)
	  && REGNO (reg) == regno
	  && CONST_INT_P (width_rtx)
	  && CONST_INT_P (offset_rtx))
	{
	  int w = INTVAL (width_rtx);
	  int o = INTVAL (offset_rtx);
	  if (w > 0 && w <= 32 && o >= 0 && o + w <= 32)
	    return ((1u << w) - 1) << (32 - o - w);
	}
      return 0;
    }

  /* (set (strict_low_part (subreg:HI (reg:SI P) 2)) ...)
     (set (strict_low_part (subreg:QI (reg:SI P) 3)) ...) */
  if (GET_CODE (dest) == STRICT_LOW_PART)
    {
      rtx sub = XEXP (dest, 0);
      if (GET_CODE (sub) == SUBREG)
	{
	  rtx reg = SUBREG_REG (sub);
	  if (REG_P (reg) && REGNO (reg) == regno)
	    {
	      machine_mode mode = GET_MODE (sub);
	      if (mode == HImode)
		return 0x0000FFFFu;
	      if (mode == QImode)
		return 0x000000FFu;
	    }
	}
      return 0;
    }

  /* Full (set (reg:SI P) ...) — stops the scan.  Cannot prove partial
     writes alone cover all bits before this full definition.  */
  if (REG_P (dest) && REGNO (dest) == regno
      && GET_MODE (dest) == SImode)
    return 0xFFFFFFFFu;

  return 0;
}

/* Return true if INSN reads pseudo REGNO (not as part of a partial write
   destination).  */

static bool
insn_reads_pseudo (rtx_insn *insn, unsigned int regno)
{
  df_ref use;
  FOR_EACH_INSN_USE (use, insn)
    if (DF_REF_REGNO (use) == regno)
      return true;
  return false;
}

static unsigned int
m68k_break_false_dep (function *func)
{
  unsigned int changes = 0;

  df_analyze ();

  basic_block bb;
  FOR_EACH_BB_FN (bb, func)
    {
      bitmap live_in = df_get_live_in (bb);

      rtx_insn *insn;
      FOR_BB_INSNS (bb, insn)
	{
	  if (!NONDEBUG_INSN_P (insn))
	    continue;

	  rtx set = single_set (insn);
	  if (!set)
	    continue;

	  rtx dest = SET_DEST (set);

	  /* Look for a partial write to a pseudo that is live-in.  */
	  unsigned int regno = 0;
	  if (GET_CODE (dest) == ZERO_EXTRACT && REG_P (XEXP (dest, 0)))
	    regno = REGNO (XEXP (dest, 0));
	  else if (GET_CODE (dest) == STRICT_LOW_PART
		   && GET_CODE (XEXP (dest, 0)) == SUBREG
		   && REG_P (SUBREG_REG (XEXP (dest, 0))))
	    regno = REGNO (SUBREG_REG (XEXP (dest, 0)));
	  else
	    continue;

	  if (regno < FIRST_PSEUDO_REGISTER)
	    continue;
	  if (!bitmap_bit_p (live_in, regno))
	    continue;

	  /* Found a partial write to a live-in pseudo.  Scan forward
	     to see if partial writes fully cover all 32 bits before
	     any read of the old value.  */
	  unsigned int coverage = 0;
	  rtx_insn *first_partial = insn;
	  bool fully_covered = false;
	  rtx_insn *scan;

	  for (scan = insn; scan && scan != NEXT_INSN (BB_END (bb));
	       scan = NEXT_INSN (scan))
	    {
	      if (!NONDEBUG_INSN_P (scan))
		continue;

	      rtx scan_set = single_set (scan);
	      if (!scan_set)
		{
		  /* Complex insn — check if it reads the pseudo.  */
		  if (insn_reads_pseudo (scan, regno))
		    break;
		  continue;
		}

	      unsigned int mask = partial_write_mask (scan_set, regno);
	      if (mask == 0xFFFFFFFFu)
		/* Full write — the old value IS used up to here.  */
		break;

	      if (mask != 0)
		{
		  coverage |= mask;
		  if (coverage == 0xFFFFFFFFu)
		    {
		      fully_covered = true;
		      break;
		    }
		  /* The partial write itself "reads" the pseudo in DF
		     (read-modify-write), but that is the false dependency
		     we are trying to break.  Only check for real reads
		     in the source operand.  */
		  if (reg_mentioned_p (regno_reg_rtx[regno],
				       SET_SRC (scan_set)))
		    break;
		  continue;
		}

	      /* Not a partial write to our pseudo — check if it reads it.  */
	      if (insn_reads_pseudo (scan, regno))
		break;
	    }

	  if (!fully_covered)
	    continue;

	  /* Insert clobber before the first partial write.  */
	  rtx clobber = gen_rtx_CLOBBER (VOIDmode,
					 gen_rtx_REG (SImode, regno));
	  rtx_insn *clobber_insn = emit_insn_before (clobber, first_partial);
	  df_insn_rescan (clobber_insn);
	  changes++;

	  if (dump_file)
	    fprintf (dump_file,
		     "m68k-break-false-dep: BB %d: inserted clobber for "
		     "pseudo %d before insn %d (coverage 0x%08x)\n",
		     bb->index, regno, INSN_UID (first_partial), coverage);

	  /* Skip past the covered region so the outer loop doesn't
	     re-examine the same partial writes.  */
	  insn = scan;
	}
    }

  if (dump_file && changes > 0)
    fprintf (dump_file, "m68k-break-false-dep: %d clobbers inserted\n",
	     changes);

  return 0;
}

/* Remove standalone (clobber (reg pseudo)) insns that were inserted
   by break_false_dep.  These served their purpose in breaking false live
   ranges for IRA, but must be removed before postreload since LRA does
   not allocate hard registers for standalone clobbers.  */

static unsigned int
m68k_break_false_dep_cleanup (function *func)
{
  unsigned int changes = 0;
  basic_block bb;

  FOR_EACH_BB_FN (bb, func)
    {
      rtx_insn *insn;
      FOR_BB_INSNS (bb, insn)
	{
	  if (!INSN_P (insn))
	    continue;
	  rtx pat = PATTERN (insn);
	  if (GET_CODE (pat) == CLOBBER
	      && REG_P (XEXP (pat, 0))
	      && !HARD_REGISTER_P (XEXP (pat, 0)))
	    {
	      if (dump_file)
		fprintf (dump_file,
			 "m68k-break-false-dep-cleanup: deleting clobber "
			 "insn %d (pseudo %d)\n",
			 INSN_UID (insn), REGNO (XEXP (pat, 0)));
	      set_insn_deleted (insn);
	      changes++;
	    }
	}
    }

  if (dump_file && changes > 0)
    fprintf (dump_file,
	     "m68k-break-false-dep-cleanup: %d clobbers deleted\n", changes);

  return 0;
}

const pass_data m68k_pass_data_break_false_dep =
{
  RTL_PASS,			 /* type */
  "m68k-break-false-dep",	 /* name */
  OPTGROUP_NONE,		 /* optinfo_flags */
  TV_MACH_DEP,			 /* tv_id */
  0,				 /* properties_required */
  0,				 /* properties_provided */
  0,				 /* properties_destroyed */
  0,				 /* todo_flags_start */
  TODO_df_finish		 /* todo_flags_finish */
};

class m68k_pass_break_false_dep : public rtl_opt_pass
{
public:
  m68k_pass_break_false_dep (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_break_false_dep, ctxt)
  {}

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_break_false_dep;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_break_false_dep (func);
  }

}; /* class m68k_pass_break_false_dep */

const pass_data m68k_pass_data_break_false_dep_cleanup =
{
  RTL_PASS,				   /* type */
  "m68k-break-false-dep-cleanup",	   /* name */
  OPTGROUP_NONE,			   /* optinfo_flags */
  TV_MACH_DEP,				   /* tv_id */
  0,					   /* properties_required */
  0,					   /* properties_provided */
  0,					   /* properties_destroyed */
  0,					   /* todo_flags_start */
  0					   /* todo_flags_finish */
};

class m68k_pass_break_false_dep_cleanup : public rtl_opt_pass
{
public:
  m68k_pass_break_false_dep_cleanup (gcc::context *ctxt)
    : rtl_opt_pass (m68k_pass_data_break_false_dep_cleanup, ctxt)
  {}

  bool gate (function *) final override
  {
    return optimize > 0 && flag_m68k_break_false_dep;
  }

  unsigned int execute (function *func) final override
  {
    return m68k_break_false_dep_cleanup (func);
  }

}; /* class m68k_pass_break_false_dep_cleanup */

} /* anonymous namespace */

rtl_opt_pass *
make_m68k_pass_break_false_dep (gcc::context *ctxt)
{
  return new m68k_pass_break_false_dep (ctxt);
}

rtl_opt_pass *
make_m68k_pass_break_false_dep_cleanup (gcc::context *ctxt)
{
  return new m68k_pass_break_false_dep_cleanup (ctxt);
}
