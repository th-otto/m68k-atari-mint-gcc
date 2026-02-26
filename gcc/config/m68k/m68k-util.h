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

#ifndef GCC_M68K_UTIL_H
#define GCC_M68K_UTIL_H

/* Check if RTX is a MEM with (plus (reg) (const_int)) address.
   Sets *PREGNO and *POFFSET on success.  */
extern bool m68k_mem_reg_offset_p (rtx x, int *pregno,
				   HOST_WIDE_INT *poffset);

/* Check if INSN is a LEA or ADD that increments a register:
   (set (reg) (plus (reg) (const_int))) where dest == src.
   Sets *PREGNO and *PINCR on success.  */
extern bool m68k_is_reg_increment (rtx_insn *insn, int *pregno,
				   HOST_WIDE_INT *pincr);

/* Update a memory operand's offset in place.  The MEM at *MEM_LOC must
   use REGNO with a base+offset address.  Returns true on success.  */
extern bool m68k_update_mem_offset_inplace (rtx *mem_loc, int regno,
					    HOST_WIDE_INT new_offset);

/* Check if a MEM operand uses REGNO with a negative offset.
   Returns the offset if found, or 0 if not.  */
extern HOST_WIDE_INT m68k_get_negative_offset (rtx mem, int regno);

/* Try to normalize increment position: move an increment instruction past
   following negative-offset memory accesses, adjusting offsets to positive.
   If REQUIRE_ADDR_REG is true, only accept hard address registers
   (a0-a7 = regs 8-15); used for post-RA passes.  */
extern bool m68k_try_normalize_increment (basic_block bb, rtx_insn *add_insn,
					  int regno, HOST_WIDE_INT incr,
					  bool require_addr_reg);

#endif /* GCC_M68K_UTIL_H */
