/*
 * When compiling for elf without a USER_LABEL_PREFIX,
 * still provide alias for internal functions when user code is compiled
 * with -fleading-underscore
 */
#define _ 2 /* __USER_LABEL_PREFIX__ may be defined to this */
#if defined(__ELF__) && (__USER_LABEL_PREFIX__ + 0) != 2
#ifdef __ASSEMBLER__
#define ELF_ALIAS(x) .globl _ ## x; _ ## x:
#else
#define ELF_ALIAS(f) typeof(f) _ ## f __attribute__((alias(#f)));
#pragma GCC diagnostic ignored "-Wmissing-attributes"
#endif
#else
#define ELF_ALIAS(f)
#endif
#undef _
