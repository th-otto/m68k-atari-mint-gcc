/* Shared utility functions for m68k RTL passes.
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

#include "m68k-util.h"

/* Check if RTX is a MEM with (plus (reg) (const_int)) address.
   Returns the offset and register number.  */

bool
m68k_mem_reg_offset_p (rtx x, int *pregno, HOST_WIDE_INT *poffset)
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

/* Check if RTX is a MEM with base register + optional constant offset.
   Handles both (mem (reg)) at offset 0 and (mem (plus (reg) (const_int))).  */

bool
m68k_mem_base_offset_p (rtx x, int *pregno, HOST_WIDE_INT *poffset)
{
  if (m68k_mem_reg_offset_p (x, pregno, poffset))
    return true;
  if (MEM_P (x))
    {
      rtx addr = XEXP (x, 0);
      if (REG_P (addr))
	{
	  *pregno = REGNO (addr);
	  *poffset = 0;
	  return true;
	}
    }
  return false;
}

/* Check if INSN is a LEA or ADD that increments a register.
   Returns the register number and increment value.  */

bool
m68k_is_reg_increment (rtx_insn *insn, int *pregno, HOST_WIDE_INT *pincr)
{
  rtx set = single_set (insn);
  if (!set)
    return false;

  rtx dest = SET_DEST (set);
  rtx src = SET_SRC (set);

  if (!REG_P (dest))
    return false;

  /* (set (reg) (plus (reg) (const_int))) where dest == src0.  */
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

bool
m68k_update_mem_offset_inplace (rtx *mem_loc, int regno,
				HOST_WIDE_INT new_offset)
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

  /* Use the canonical regno_reg_rtx so that LRA's SET_REGNO in
     lra_final_code_change will update this rtx in place.  */
  rtx reg = regno_reg_rtx[regno];

  rtx new_addr;
  if (new_offset == 0)
    new_addr = reg;
  else
    new_addr = gen_rtx_PLUS (Pmode, reg, GEN_INT (new_offset));

  machine_mode mem_mode = GET_MODE (old_mem);
  rtx new_mem = gen_rtx_MEM (mem_mode, new_addr);
  MEM_COPY_ATTRIBUTES (new_mem, old_mem);
  *mem_loc = new_mem;
  return true;
}

/* Check if a MEM operand uses the given register with a negative offset.
   Returns the offset if found, or 0 if not.  */

HOST_WIDE_INT
m68k_get_negative_offset (rtx mem, int regno)
{
  if (!MEM_P (mem))
    return 0;

  int mem_regno;
  HOST_WIDE_INT offset;
  if (m68k_mem_reg_offset_p (mem, &mem_regno, &offset)
      && mem_regno == regno && offset < 0)
    return offset;

  return 0;
}

/* For a binary/commutative expression SRC, check if one operand is a MEM
   with REGNO at a negative offset, and the other operand does NOT mention
   REGNO (i.e., an RMW pattern like (plus (mem (plus reg -4)) d0)).
   Returns the negative offset if found, or 0.  */

static HOST_WIDE_INT
m68k_get_nested_negative_offset (rtx src, int regno)
{
  if (GET_RTX_CLASS (GET_CODE (src)) != RTX_COMM_ARITH
      && GET_RTX_CLASS (GET_CODE (src)) != RTX_BIN_ARITH)
    return 0;

  rtx reg = gen_rtx_REG (Pmode, regno);
  rtx op0 = XEXP (src, 0);
  rtx op1 = XEXP (src, 1);

  HOST_WIDE_INT off0 = m68k_get_negative_offset (op0, regno);
  if (off0 < 0 && !reg_mentioned_p (reg, op1))
    return off0;

  HOST_WIDE_INT off1 = m68k_get_negative_offset (op1, regno);
  if (off1 < 0 && !reg_mentioned_p (reg, op0))
    return off1;

  return 0;
}

/* For a binary/commutative expression at *SRC_LOC, find the nested MEM
   operand that uses REGNO and call m68k_update_mem_offset_inplace on it.
   Returns true if the update was made.  */

static bool
m68k_update_nested_mem_offset_inplace (rtx *src_loc, int regno,
				       HOST_WIDE_INT new_offset)
{
  rtx src = *src_loc;
  if (GET_RTX_CLASS (GET_CODE (src)) != RTX_COMM_ARITH
      && GET_RTX_CLASS (GET_CODE (src)) != RTX_BIN_ARITH)
    return false;

  if (MEM_P (XEXP (src, 0)))
    {
      int mem_regno;
      HOST_WIDE_INT offset;
      if (m68k_mem_reg_offset_p (XEXP (src, 0), &mem_regno, &offset)
	  && mem_regno == regno)
	return m68k_update_mem_offset_inplace (&XEXP (src, 0), regno,
					       new_offset);
    }
  if (MEM_P (XEXP (src, 1)))
    {
      int mem_regno;
      HOST_WIDE_INT offset;
      if (m68k_mem_reg_offset_p (XEXP (src, 1), &mem_regno, &offset)
	  && mem_regno == regno)
	return m68k_update_mem_offset_inplace (&XEXP (src, 1), regno,
					       new_offset);
    }
  return false;
}

/* Try to normalize increment position: move an increment instruction past
   following negative-offset memory accesses, adjusting offsets to positive.

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

   If REQUIRE_ADDR_REG is true, restricts to hard address registers
   (a0-a7 = regs 8-15).  Returns true if the transformation was made.  */

bool
m68k_try_normalize_increment (basic_block bb, rtx_insn *add_insn,
			      int regno, HOST_WIDE_INT incr,
			      bool require_addr_reg)
{
  /* Optionally restrict to address registers (a0-a7 = regs 8-15).  */
  if (require_addr_reg && (regno < 8 || regno > 15))
    return false;

  /* Only handle positive increments.  */
  if (incr <= 0)
    return false;

  /* Collect instructions with negative offsets that need adjustment.  */
  struct insn_to_fix {
    rtx_insn *insn;
    HOST_WIDE_INT src_offset;   /* 0 if src doesn't need fixing */
    HOST_WIDE_INT dest_offset;  /* 0 if dest doesn't need fixing */
    bool src_is_nested;         /* true if src MEM is nested in binary op */
  };
  auto_vec<insn_to_fix> fixups;
  rtx_insn *last_fixup_insn = nullptr;

  rtx reg = gen_rtx_REG (Pmode, regno);

  for (rtx_insn *insn = next_nonnote_nondebug_insn_bb (add_insn);
       insn;
       insn = next_nonnote_nondebug_insn_bb (insn))
    {
      rtx set = single_set (insn);
      if (!set)
	break;

      rtx src = SET_SRC (set);
      rtx dest = SET_DEST (set);

      HOST_WIDE_INT src_neg = m68k_get_negative_offset (src, regno);
      HOST_WIDE_INT dest_neg = m68k_get_negative_offset (dest, regno);

      /* For RMW patterns like (set (mem -4(reg)) (plus (mem -4(reg)) d0)),
	 the src is a binary op with a nested MEM.  Check for this if the
	 direct check didn't find a negative offset in src.  */
      bool src_is_nested = false;
      if (src_neg == 0 && reg_mentioned_p (reg, src))
	{
	  HOST_WIDE_INT nested = m68k_get_nested_negative_offset (src, regno);
	  if (nested < 0)
	    {
	      src_neg = nested;
	      src_is_nested = true;
	    }
	}

      if (src_neg < 0 || dest_neg < 0)
	{
	  /* If the register is mentioned but we didn't find a negative
	     offset (direct or nested), there's a pattern we can't handle.  */
	  bool src_uses_reg = reg_mentioned_p (reg, src);
	  bool dest_uses_reg = reg_mentioned_p (reg, dest);
	  if (src_uses_reg && src_neg == 0)
	    break;
	  if (dest_uses_reg && dest_neg == 0)
	    break;

	  insn_to_fix fix;
	  fix.insn = insn;
	  fix.src_offset = src_neg;
	  fix.dest_offset = dest_neg;
	  fix.src_is_nested = src_is_nested;
	  fixups.safe_push (fix);
	  last_fixup_insn = insn;
	  continue;
	}

      /* If the register is modified by another instruction, stop.  */
      if (reg_set_p (reg, insn))
	break;

      /* If the register is used in some other way, stop.  */
      if (reg_mentioned_p (reg, PATTERN (insn)))
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
	  if (fix.src_is_nested)
	    m68k_update_nested_mem_offset_inplace (&SET_SRC (set), regno,
						   new_offset);
	  else
	    m68k_update_mem_offset_inplace (&SET_SRC (set), regno, new_offset);
	}
      if (fix.dest_offset < 0)
	{
	  HOST_WIDE_INT new_offset = fix.dest_offset + incr;
	  m68k_update_mem_offset_inplace (&SET_DEST (set), regno, new_offset);
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
