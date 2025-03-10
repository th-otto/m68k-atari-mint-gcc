/* Copyright (C) 2000-2023 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#include "elf-alias.h"

extern unsigned long __udivmodsi4(unsigned long num, unsigned long den,
								  int modwanted);

long
__udivsi3 (long a, long b)
{
  return __udivmodsi4 (a, b, 0);
}
ELF_ALIAS(__udivsi3)

long
__umodsi3 (long a, long b)
{
  return __udivmodsi4 (a, b, 1);
}
ELF_ALIAS(__umodsi3)
