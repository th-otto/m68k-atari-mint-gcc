/* "main" for the compiler driver.
   Copyright (C) 1987-2017 Free Software Foundation, Inc.

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

/* This source file contains "main" for the compiler driver.
   All of the real work is done within gcc.c; we implement "main"
   in here for the "gcc" binary so that gcc.o can be used in
   libgccjit.so.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "xregex.h"
#include "obstack.h"
#include "intl.h"
#include "prefix.h"
#include "gcc.h"

/* Implement the top-level "main" within the driver in terms of
   driver::main (implemented in gcc.c).  */

extern int main (int, char **);

#if defined(__LINUX_GLIBC_WRAP_H)

/* ugly hack to get __libc_start_main versioned */

#if __GLIBC_PREREQ(2, 34)

#define STR_(s) #s
#define STR(s)  STR_(s)
#include <dlfcn.h>

#ifdef __UCLIBC__
#define __libc_start_main       __uClibc_main
#endif

#ifdef __cplusplus
extern "C" {
#endif
int __libc_start_main(
        int (*main)(int,char**,char**), int ac, char **av,
        int (*init)(void), void (*fini)(void),
        void (*rtld_fini)(void), void *stack_end);
int __libc_start_main(
        int (*main)(int,char**,char**), int ac, char **av,
        int (*init)(void), void (*fini)(void),
        void (*rtld_fini)(void), void *stack_end)
{
	typeof(__libc_start_main) *real_lsm;
	if ((*(void**)&real_lsm = dlsym(RTLD_NEXT, STR(__libc_start_main))) != 0)
		return real_lsm(main, ac, av, init, fini, rtld_fini, stack_end);
	fputs("BUG: dlsym error\n", stderr);
	return 1;
}
#ifdef __cplusplus
}
#endif
#undef STR
#undef STR_
#endif
#endif

int
main (int argc, char **argv)
{
  driver d (false, /* can_finalize */
	    false); /* debug */

  return d.main (argc, argv);
}
