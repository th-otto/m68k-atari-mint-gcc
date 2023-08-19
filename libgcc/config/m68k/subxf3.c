/* Software floating-point emulation.
   Return a - b
   Copyright (C) 1997-2022 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   In addition to the permissions in the GNU Lesser General Public
   License, the Free Software Foundation gives you unlimited
   permission to link the compiled version of this file into
   combinations with other programs, and to distribute those
   combinations without any restriction coming from the use of this
   file.  (The Lesser General Public License restrictions do apply in
   other respects; for example, they cover modification of the file,
   and distribution when not linked into a combine executable.)

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include "soft-fp/soft-fp.h"
#ifdef LIBGCC_HAS_XF_MODE
#include "soft-fp/extended.h"

long double
__subxf3 (long double a, long double b)
{
	(void)a;
	__asm__ __volatile__(
		"bchg #7,%0\n\t"
		"jmp %1"
	:
	: "m"(b), "m"(__addxf3)
	: "cc", "memory");
	__builtin_unreachable();
}
ELF_ALIAS(__subxf3)

#endif
