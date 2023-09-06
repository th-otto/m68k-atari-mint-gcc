/* Definitions of target machine for GNU compiler.
   Atari ST TOS/MiNT.
   Copyright (C) 1994, 1995, 2007, 2008, 2009, 2010, 2011
   Free Software Foundation, Inc.

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

/* Here are four prefixes that are used by asm_fprintf to
   facilitate customization for alternate assembler syntaxes.
   Machines with no likelihood of an alternate syntax need not
   define these and need not use asm_fprintf.  */

/* The prefix for register names.  Note that REGISTER_NAMES
   is supposed to include this prefix. Also note that this is NOT an
   fprintf format string, it is a literal string */

#undef REGISTER_PREFIX
#define REGISTER_PREFIX "%"

/* The prefix for local (compiler generated) labels.
   These labels will not appear in the symbol table.  */

#undef LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX "."

#undef ASM_COMMENT_START
#define ASM_COMMENT_START "|"

#undef TARGET_LIBC_HAS_FUNCTION
#define TARGET_LIBC_HAS_FUNCTION no_c99_libc_has_function

#undef WCHAR_TYPE
#define WCHAR_TYPE "short unsigned int"

#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE SHORT_TYPE_SIZE

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()		\
  do						\
    {						\
      builtin_define ("__MINT__");		\
      builtin_define_std ("atarist");		\
      builtin_assert ("machine=atari");		\
      builtin_assert ("system=mint");		\
    }						\
  while (0)

/* The following defines are nonstandard
   and are kept only for compatibility
   with older versions of GCC for MiNT.  */

#undef CPP_SPEC
#define CPP_SPEC			\
  "%{m68000|mcpu=68000:-D__M68000__} "		\
  "%{m68020|mcpu=68020:-D__M68020__} "		\
  "%{m68030|mcpu=68030:-D__M68020__} "		\
  "%{m68040|mcpu=68040:-D__M68020__} "		\
  "%{m68060|mcpu=68060:-D__M68020__} "		\
  "%{m68020-40|mcpu=68020-40:-D__M68020__} "		\
  "%{m68020-60|mcpu=68020-60:-D__M68020__} "		\
  "%{!m680*:%{!mc680*:%{!mcpu=680*:-D__M68000__}}} "	\
  "%{mshort:-D__MSHORT__}"

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC	"%{pg|p|profile:gcrt0.o%s;:crt0.o%s} crtbegin.o%s"
 
#undef  ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s"

#undef  LIB_SPEC
#define LIB_SPEC	"-lc"

/* Every structure or union's size must be a multiple of 2 bytes.  */
#define STRUCTURE_SIZE_BOUNDARY 16

/* The -g option generates stabs debug information.  */
#define DBX_DEBUGGING_INFO 1

/* Do not break .stabs pseudos into continuations.  */
#define DBX_CONTIN_LENGTH 0

/* This is the char to use for continuation (in case we need to turn
   continuation back on).  */
#define DBX_CONTIN_CHAR '?'

/* This is the assembler directive to equate two values.  */
#undef SET_ASM_OP
#define SET_ASM_OP		"\t.set\t"

/* This is how we tell the assembler that a symbol is weak.  */
#undef ASM_WEAKEN_LABEL
#define ASM_WEAKEN_LABEL(FILE,NAME) \
  do { fputs ("\t.weak\t", FILE); assemble_name (FILE, NAME); \
       fputc ('\n', FILE); } while (0)

/* Don't default to pcc-struct-return, because gcc is the only compiler, and
   we want to retain compatibility with older gcc versions.  */
#define DEFAULT_PCC_STRUCT_RETURN 0

/* Finalize the trampoline by flushing the insn cache.  */

#undef FINALIZE_TRAMPOLINE
#define FINALIZE_TRAMPOLINE(TRAMP)					\
  if (TARGET_68020 || TARGET_COLDFIRE) \
    maybe_emit_call_builtin___clear_cache ((TRAMP),			\
					 plus_constant (Pmode,		\
							(TRAMP),	\
							TRAMPOLINE_SIZE))

/* Clear the instruction cache from `beg' to `end'.  This makes an
   inline system call to Ssystem(S_FLUSHCACHE).  The arguments are as
   follows:

	Ssystem(S_FLUSHCACHE, addr, len)

   addr	  - the start address for the flush
   len    - the number of bytes to flush

   The kernel will push the instruction cache
	    */

#define CLEAR_INSN_CACHE(BEG, END)					\
{									\
  register unsigned long _beg __asm ("%d0") = (unsigned long) (BEG);	\
  unsigned long _end = (unsigned long) (END);				\
  register unsigned long _len __asm ("%d1") = (_end - _beg);	\
  __asm __volatile							\
    ("move%.l %1,-(%%sp)\n\t"	/* len */			\
     "move%.l %0,-(%%sp)\n\t"	/* beg */			\
     "move%.w #22,-(%%sp)\n\t"	/* S_FLUSHCACHE */			\
     "move%.w #340,-(%%sp)\n\t"	/* system call nr */			\
     "trap #1\n\t"								\
     "lea 12(%%sp),%%sp" /* correct stack */ \
     : /* no outputs */							\
     : "r" (_beg), "r" (_len)						\
     : "%d2", "%a0", "%a1", "%a2", "cc", "memory");						\
}

/* By default, the vtable entries are void pointers, the so the alignment
   is the same as pointer alignment.  The value of this macro specifies
   the alignment of the vtable entry in bits.  It should be defined only
   when special alignment is necessary.

   MiNT: The default value of 32 is too much and unsupported by a.out-mintprg.
*/
#define TARGET_VTABLE_ENTRY_ALIGN 16

/* If we have a definition of INCOMING_RETURN_ADDR_RTX, assume that
   the rest of the DWARF 2 frame unwind support is also provided.
   
   All configurations that don't use elf must be explicit about not using
   dwarf unwind information.

   MiNT: DWARF 2 frame unwind is not supported by a.out-mint.
*/
#define DWARF2_UNWIND_INFO 0

/* config/m68k.md has an explicit reference to the program counter,
   prefix this by the register prefix.  */

#define ASM_RETURN_CASE_JUMP				\
  do {							\
    if (TARGET_COLDFIRE)				\
      {							\
	if (ADDRESS_REG_P (operands[0]))		\
	  return "jmp %%pc@(2,%0:l)";			\
	else if (TARGET_LONG_JUMP_TABLE_OFFSETS)	\
	  return "jmp %%pc@(2,%0:l)";			\
	else						\
	  return "ext%.l %0\n\tjmp %%pc@(2,%0:l)";	\
      }							\
    else if (TARGET_LONG_JUMP_TABLE_OFFSETS)		\
      return "jmp %%pc@(2,%0:l)";			\
    else						\
      return "jmp %%pc@(2,%0:w)";			\
  } while (0)

/* The ADDR_DIFF_VEC must exactly follow the previous instruction.  */

#undef ADDR_VEC_ALIGN
#define ADDR_VEC_ALIGN(ADDR_VEC) 0

/* If defined, a C expression whose value is a string containing the
   assembler operation to identify the following data as uninitialized global
   data.  */

#ifdef USING_ELFOS_H
#define BSS_SECTION_ASM_OP "\t.section\t.bss"

#define TARGET_HAVE_NAMED_SECTIONS true

/* Currently, JUMP_TABLES_IN_TEXT_SECTION must be defined in order to
   keep switch tables in the text section.  */
   
#define JUMP_TABLES_IN_TEXT_SECTION 1

#define EH_TABLES_CAN_BE_READ_ONLY 1

/*
 * our object format is elf, but not our executable format
 */
#undef HAVE_INITFINI_ARRAY_SUPPORT
#define HAVE_INITFINI_ARRAY_SUPPORT 0

#undef OBJECT_FORMAT_ELF 
#undef INIT_SECTION_ASM_OP
#undef FINI_SECTION_ASM_OP

#else
#define BSS_SECTION_ASM_OP "\t.bss"

#define TARGET_HAVE_NAMED_SECTIONS false
#endif

/* A C statement (sans semicolon) to output to the stdio stream
   FILE the assembler definition of uninitialized global DECL named
   NAME whose size is SIZE bytes and alignment is ALIGN bytes.
   Try to use asm_output_aligned_bss to implement this macro.  */

#define ASM_OUTPUT_ALIGNED_BSS(FILE, DECL, NAME, SIZE, ALIGN) \
  asm_output_aligned_bss (FILE, DECL, NAME, SIZE, ALIGN)

/* Disable -fpic and -fPIC since bsr.l _label@PLTPC
   is unsupported by the assembler.  */

#undef  SUBTARGET_OVERRIDE_OPTIONS
#define SUBTARGET_OVERRIDE_OPTIONS					\
do {									\
  if (flag_pic && !TARGET_PCREL)					\
      error ("-f%s is not supported on this target",			\
	       (flag_pic > 1) ? "PIC" : "pic");				\
} while (0)


/* Workaround for GCC bug #35067 about multiple thunks.  */

#undef MAKE_DECL_ONE_ONLY
#define MAKE_DECL_ONE_ONLY(DECL) (DECL_WEAK (DECL) = 1)

/* Avoid requiring -static with -fmudflap like in config/bfin/uclinux.h */
#define MFWRAP_SPEC " %{fmudflap|fmudflapth: \
 --wrap=malloc --wrap=free --wrap=calloc --wrap=realloc\
 --wrap=mmap --wrap=munmap --wrap=alloca\
 %{fmudflapth: --wrap=pthread_create\
}} %{fmudflap|fmudflapth: --wrap=main}"

/* Install the __sync libcalls.  */
#undef TARGET_INIT_LIBFUNCS
#define TARGET_INIT_LIBFUNCS  m68k_init_libfuncs

#ifdef USING_ELFOS_H
/*
 * Definitions for crtstuff.c.
 * Only for elf; others use libgcc2.c instead
 */
#define CTOR_LIST_BEGIN \
STATIC func_ptr __CTOR_LIST__[1] \
  __attribute__ ((__used__, section(".ctors"), aligned(__alignof__(func_ptr)))) \
  = { (func_ptr) (-1) }; \
  /* STATIC ELF_ALIAS(__CTOR_LIST__) */

#define DTOR_LIST_BEGIN \
STATIC func_ptr __DTOR_LIST__[1] \
  __attribute__ ((__used__, section(".dtors"), aligned(__alignof__(func_ptr)))) \
  = { (func_ptr) (-1) }; \
  /* STATIC ELF_ALIAS(__DTOR_LIST__) */

#define CTOR_LIST_END \
STATIC func_ptr __CTOR_END__[1] \
  __attribute__((__used__)) \
  __attribute__((section(".ctors"), aligned(__alignof__(func_ptr)))) \
  = { (func_ptr) 0 }; \
  /* STATIC ELF_ALIAS(__CTOR_END__) */

#define DTOR_LIST_END \
STATIC func_ptr __DTOR_END__[1] \
  __attribute__((__used__)) \
  __attribute__((section(".dtors"), aligned(__alignof__(func_ptr)))) \
  = { (func_ptr) 0 }; \
  /* STATIC ELF_ALIAS(__DTOR_END__) */

#endif
