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

/* Given a scale operation, extract the ashift amount and the pre-scaled
   operand.  Returns the ashift amount (1, 2, or 3) and sets *unscaled
   to the pre-scaled operand, or returns 0 on failure.

   Recognized patterns (in any integer mode):
     (plus Y Y)              → scale 2  (ashift 1)
     (ashift Y const_1)      → scale 2  (ashift 1)
     (ashift Y const_2)      → scale 4  (ashift 2)
     (ashift Y const_3)      → scale 8  (ashift 3)
     (mult Y const_2)        → scale 2  (ashift 1)
     (mult Y const_4)        → scale 4  (ashift 2)
     (mult Y const_8)        → scale 8  (ashift 3)  */

static int
scale_shift_amount (rtx src, rtx *unscaled)
{
  enum rtx_code code = GET_CODE (src);

  if (code == PLUS
      && REG_P (XEXP (src, 0))
      && rtx_equal_p (XEXP (src, 0), XEXP (src, 1)))
    {
      *unscaled = XEXP (src, 0);
      return 1;
    }

  if (code == ASHIFT
      && (REG_P (XEXP (src, 0)) || GET_CODE (XEXP (src, 0)) == SUBREG)
      && CONST_INT_P (XEXP (src, 1)))
    {
      int shift = INTVAL (XEXP (src, 1));
      if (shift >= 1 && shift <= 3)
	{
	  *unscaled = XEXP (src, 0);
	  return shift;
	}
    }

  if (code == MULT
      && (REG_P (XEXP (src, 0)) || GET_CODE (XEXP (src, 0)) == SUBREG)
      && CONST_INT_P (XEXP (src, 1)))
    {
      HOST_WIDE_INT val = INTVAL (XEXP (src, 1));
      if (val == 2) { *unscaled = XEXP (src, 0); return 1; }
      if (val == 4) { *unscaled = XEXP (src, 0); return 2; }
      if (val == 8) { *unscaled = XEXP (src, 0); return 3; }
    }

  return 0;
}

/* Try to fold a separate HI-mode scale operation into a MEM's address
   as a 68020+ scaled index.

   Pattern: MEM address contains (sign_extend:SI (reg:HI X)) where X's
   defining insn computes X = scale(Y).  Rewrite to use
   (ashift:SI (sign_extend:SI Y) shift) in the address, producing
   a (%base,%Yn.w*SCALE) addressing mode.

   Only valid on 68020+ (not ColdFire) where .w scaled index is supported.
   Returns true if a change was made.  */

static bool
try_fold_hi_scale_to_mem (rtx mem)
{
  if (TARGET_COLDFIRE)
    return false;

  rtx addr = XEXP (mem, 0);
  if (GET_CODE (addr) != PLUS)
    return false;

  /* Find the (sign_extend:SI (reg:HI X)) operand — could be either side.  */
  rtx sext = NULL_RTX;
  rtx *sext_loc = NULL;

  for (int i = 0; i < 2; i++)
    {
      rtx op = XEXP (addr, i);
      if (GET_CODE (op) == SIGN_EXTEND
	  && GET_MODE (op) == SImode
	  && GET_MODE (XEXP (op, 0)) == HImode
	  && REG_P (XEXP (op, 0)))
	{
	  sext = op;
	  sext_loc = &XEXP (addr, i);
	  break;
	}
    }

  if (!sext)
    return false;

  rtx hi_reg = XEXP (sext, 0);
  if (HARD_REGISTER_P (hi_reg))
    return false;

  unsigned int regno = REGNO (hi_reg);

  /* Find the single reaching definition of the HI register.  */
  df_ref def = DF_REG_DEF_CHAIN (regno);
  if (!def || DF_REG_DEF_COUNT (regno) != 1)
    return false;

  rtx_insn *def_insn = DF_REF_INSN (def);
  rtx def_set = single_set (def_insn);
  if (!def_set || !rtx_equal_p (SET_DEST (def_set), hi_reg))
    return false;

  rtx src = SET_SRC (def_set);
  if (GET_MODE (src) != HImode)
    return false;

  rtx unscaled = NULL_RTX;
  int shift = scale_shift_amount (src, &unscaled);
  if (shift == 0)
    return false;

  /* Note: scale 8 / ColdFire guard is not needed here because the
     function already returns false for TARGET_COLDFIRE at the top.  */

  /* Build (ashift:SI (sign_extend:SI unscaled) shift).
     Must copy_rtx to avoid sharing with the defining insn.  */
  rtx new_sext = gen_rtx_SIGN_EXTEND (SImode, copy_rtx (unscaled));
  rtx scaled = gen_rtx_ASHIFT (SImode, new_sext, GEN_INT (shift));
  *sext_loc = scaled;
  return true;
}

/* Try to combine a double-scaled index in a MEM address.

   Looks for (mult:SI reg SCALE) or (ashift:SI reg SHIFT) in a MEM address
   where reg's def chain is zero_extend:SI(HI_val) and HI_val's def is
   another scale operation.  Combines both scales into a single larger scale
   applied to the pre-scaled value.

   Example (from narrow_index_mult):
     r74:HI = r53:HI + r53:HI          ;; *2
     r75:SI = zero_extend(r74:HI)       ;; extend doubled value
     mem[mult(r75, 2) + ext_table]      ;; *2 in address = *4 total
   Becomes:
     r_new:SI = zero_extend(r53:HI)     ;; extend pre-scaled value
     mem[mult(r_new, 4) + ext_table]    ;; combined *4

   The original scale and zero_extend insns become dead for DCE.
   Only valid on 68020+ or ColdFire with scaled index support.
   Returns true if a change was made.  */

static bool
try_combine_mem_scale (rtx_insn *insn)
{
  if (!TARGET_68020 && !TARGET_COLDFIRE)
    return false;

  subrtx_ptr_iterator::array_type array;
  FOR_EACH_SUBRTX_PTR (iter, array, &PATTERN (insn), NONCONST)
    {
      rtx x = **iter;
      if (!MEM_P (x))
	continue;

      rtx addr = XEXP (x, 0);
      if (GET_CODE (addr) != PLUS)
	continue;

      /* Check each side of the PLUS for a scaled index.  */
      for (int side = 0; side < 2; side++)
	{
	  rtx scale_node = XEXP (addr, side);
	  if (GET_MODE (scale_node) != SImode)
	    continue;

	  /* Reuse scale_shift_amount to decode the outer scale.  */
	  rtx index_reg = NULL_RTX;
	  int outer_shift = scale_shift_amount (scale_node, &index_reg);
	  if (outer_shift == 0)
	    continue;

	  if (!REG_P (index_reg) || HARD_REGISTER_P (index_reg))
	    continue;

	  unsigned int regno = REGNO (index_reg);

	  /* Single reaching definition.  */
	  df_ref def = DF_REG_DEF_CHAIN (regno);
	  if (!def || DF_REG_DEF_COUNT (regno) != 1)
	    continue;

	  rtx_insn *def_insn = DF_REF_INSN (def);
	  rtx def_set = single_set (def_insn);
	  if (!def_set || !rtx_equal_p (SET_DEST (def_set), index_reg))
	    continue;

	  rtx def_src = SET_SRC (def_set);

	  /* Must be (zero_extend:SI (reg:HI)).  */
	  if (GET_CODE (def_src) != ZERO_EXTEND
	      || GET_MODE (def_src) != SImode
	      || GET_MODE (XEXP (def_src, 0)) != HImode
	      || !REG_P (XEXP (def_src, 0)))
	    continue;

	  rtx hi_reg = XEXP (def_src, 0);
	  if (HARD_REGISTER_P (hi_reg))
	    continue;

	  unsigned int hi_regno = REGNO (hi_reg);

	  /* Single definition of the HI register.  */
	  df_ref hi_def = DF_REG_DEF_CHAIN (hi_regno);
	  if (!hi_def || DF_REG_DEF_COUNT (hi_regno) != 1)
	    continue;

	  rtx_insn *hi_def_insn = DF_REF_INSN (hi_def);
	  rtx hi_def_set = single_set (hi_def_insn);
	  if (!hi_def_set || !rtx_equal_p (SET_DEST (hi_def_set), hi_reg))
	    continue;

	  rtx hi_src = SET_SRC (hi_def_set);
	  if (GET_MODE (hi_src) != HImode)
	    continue;

	  rtx unscaled = NULL_RTX;
	  int inner_shift = scale_shift_amount (hi_src, &unscaled);
	  if (inner_shift == 0)
	    continue;

	  int combined_shift = outer_shift + inner_shift;
	  if (combined_shift > 3)
	    continue;  /* Combined scale > 8 not supported.  */

	  if (!REG_P (unscaled))
	    continue;

	  /* Emit r_new:SI = zero_extend:SI(unscaled:HI) before insn.
	     Use the original REG rtx (not copy_rtx) so IRA can track it.  */
	  rtx new_pseudo = gen_reg_rtx (SImode);
	  rtx new_zext = gen_rtx_SET (new_pseudo,
				      gen_rtx_ZERO_EXTEND (SImode, unscaled));
	  rtx_insn *new_insn = emit_insn_before (new_zext, insn);

	  /* Replace the scaled index with combined scale.  */
	  rtx saved_scale = XEXP (addr, side);
	  HOST_WIDE_INT combined_scale = HOST_WIDE_INT_1 << combined_shift;
	  XEXP (addr, side) = gen_rtx_MULT (SImode, new_pseudo,
					     GEN_INT (combined_scale));

	  INSN_CODE (insn) = -1;
	  if (recog_memoized (insn) >= 0)
	    {
	      df_insn_rescan (new_insn);
	      df_insn_rescan (insn);
	      return true;
	    }

	  /* Revert on recog failure.  */
	  XEXP (addr, side) = saved_scale;
	  INSN_CODE (insn) = -1;
	  delete_insn (new_insn);
	}
    }

  return false;
}

/* Try to fold a separate scale operation into a PLUS expression that
   computes an address (for LEA or pointer arithmetic).

   Pattern: insn has (set dest (plus base reg)) where reg's single
   defining insn is a scale operation (ashift/plus-self/mult by 2/4/8).
   Fold to (set dest (plus base (ashift orig shift))), which
   m68k_legitimate_address_p recognizes as a scaled index address.

   Only valid on 68020+ which supports scaled index addressing.
   Returns true if a change was made.  */

static bool
try_fold_scale_to_plus (rtx_insn *insn)
{
  if (!TARGET_68020)
    return false;

  rtx set = single_set (insn);
  if (!set)
    return false;

  rtx dest = SET_DEST (set);
  rtx src = SET_SRC (set);

  /* Match (set dest (plus A B)) in SImode.  */
  if (GET_CODE (src) != PLUS || GET_MODE (src) != SImode)
    return false;

  /* Dest must be a register (address or data).  */
  if (!REG_P (dest))
    return false;

  /* Try each operand of the PLUS as the potential scaled register.  */
  for (int i = 0; i < 2; i++)
    {
      rtx scaled_op = XEXP (src, i);
      rtx base_op = XEXP (src, 1 - i);

      if (!REG_P (scaled_op) || HARD_REGISTER_P (scaled_op))
	continue;

      unsigned int regno = REGNO (scaled_op);

      /* Need a single reaching definition.  */
      df_ref def = DF_REG_DEF_CHAIN (regno);
      if (!def || DF_REG_DEF_COUNT (regno) != 1)
	continue;

      rtx_insn *def_insn = DF_REF_INSN (def);
      if (!NONDEBUG_INSN_P (def_insn))
	continue;

      /* Both insns must be in the same basic block.  */
      if (BLOCK_FOR_INSN (def_insn) != BLOCK_FOR_INSN (insn))
	continue;

      rtx def_set = single_set (def_insn);
      if (!def_set || !rtx_equal_p (SET_DEST (def_set), scaled_op))
	continue;

      rtx def_src = SET_SRC (def_set);

      /* Accept both SI-mode and HI-mode scale operations.
	 HI-mode scales produce .w index; SI-mode produce .l index.  */
      if (GET_MODE (def_src) != SImode && GET_MODE (def_src) != HImode)
	continue;

      rtx unscaled = NULL_RTX;
      int shift = scale_shift_amount (def_src, &unscaled);
      if (shift == 0)
	continue;

      /* Scale 8 (shift=3) requires specific CPU support.  */
      if (shift == 3 && TARGET_COLDFIRE && !TARGET_COLDFIRE_FPU)
	continue;

      /* The unscaled operand must be a REG or SUBREG for the addressing
	 mode to work.  */
      if (!REG_P (unscaled) && GET_CODE (unscaled) != SUBREG)
	continue;

      /* Only fold when the scaled register has exactly one use (this insn).
	 Otherwise the defining shift insn can't be eliminated.  */
      if (DF_REG_USE_COUNT (regno) != 1)
	continue;

      /* The fold produces a LEA (address register destination).  On 68030,
	 cmpa.l costs 4 cycles vs cmp.l's 2, so folding is harmful when
	 the result is used in a loop comparison.  On 68040, lea costs
	 4 cycles vs lsl+add's 3, so the fold is also undesirable.
	 On 68060, cmpa.l = cmp.l = 1 cycle and lea = 1 cycle vs
	 lsl+add = 2 cycles, so the fold is always beneficial.
	 Skip if dest is used in any jump/compare insn, except on 68060.
	 (m68k uses cbranchsi4 which is a jump_insn with if_then_else,
	 not a separate COMPARE.)  */
      {
	unsigned int dest_regno = REGNO (dest);
	bool used_in_compare = false;
	df_ref use;
	for (use = DF_REG_USE_CHAIN (dest_regno); use;
	     use = DF_REF_NEXT_REG (use))
	  {
	    rtx_insn *use_insn = DF_REF_INSN (use);
	    if (JUMP_P (use_insn) && !TUNE_68060)
	      {
		used_in_compare = true;
		break;
	      }
	  }
	if (used_in_compare)
	  continue;
      }

      /* Build a new PLUS with the scale folded in:
	 (plus base (ashift (maybe_extend unscaled) shift)).
	 Use validate_change to properly notify GCC's infrastructure.
	 Must copy_rtx to avoid sharing with the defining insn.  */
      rtx new_idx = copy_rtx (unscaled);
      if (GET_MODE (def_src) == HImode)
	new_idx = gen_rtx_SIGN_EXTEND (SImode, new_idx);
      rtx new_scaled = gen_rtx_ASHIFT (SImode, new_idx, GEN_INT (shift));
      rtx new_src = gen_rtx_PLUS (SImode, base_op, new_scaled);
      validate_unshare_change (insn, &SET_SRC (set), new_src, true);
      if (!apply_change_group ())
	continue;
      /* Successful — recog and constraints validated by apply_change_group.  */
      df_insn_rescan (insn);
      return true;
    }

  return false;
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

	  /* Try folding a scale operation into a PLUS (address computation).
	     This uses validate_change internally and handles its own rollback,
	     so count it separately from the MEM-based folds below.  */
	  if (try_fold_scale_to_plus (insn))
	    {
	      changes++;
	      if (dump_file)
		{
		  fprintf (dump_file,
			   "m68k-canon-scaled-index: insn %d: "
			   "folded scale into address computation\n",
			   INSN_UID (insn));
		  print_rtl_single (dump_file, insn);
		}
	      continue;
	    }

	  /* Try combining double-scaled indices in MEMs.  This handles its
	     own recog validation and insn emission/cleanup.  */
	  if (try_combine_mem_scale (insn))
	    {
	      changes++;
	      if (dump_file)
		{
		  fprintf (dump_file,
			   "m68k-canon-scaled-index: insn %d: "
			   "combined double-scaled MEM index\n",
			   INSN_UID (insn));
		  print_rtl_single (dump_file, insn);
		}
	      continue;
	    }

	  /* Walk all sub-rtx looking for MEMs with scaled index patterns.
	     Defer the copy_rtx snapshot until a fold actually fires.  */
	  rtx saved_pattern = NULL_RTX;
	  bool changed = false;
	  subrtx_ptr_iterator::array_type array;
	  FOR_EACH_SUBRTX_PTR (iter, array, &PATTERN (insn), NONCONST)
	    {
	      rtx x = **iter;
	      if (MEM_P (x))
		{
		  if (!saved_pattern)
		    saved_pattern = copy_rtx (PATTERN (insn));
		  if (try_canon_mem_addr (x)
		      || try_fold_hi_scale_to_mem (x))
		    changed = true;
		}
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
		    {
		      fprintf (dump_file,
			       "m68k-canon-scaled-index: insn %d: "
			       "rewrote to ashift form\n",
			       INSN_UID (insn));
		      print_rtl_single (dump_file, insn);
		    }
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

