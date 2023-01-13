#if defined(__LINUX_GLIBC_WRAP_H)

/* ugly hack to get __libc_start_main versioned */

#if __GLIBC_PREREQ(2, 34)

#define STR_(s) #s
#define STR(s)  STR_(s)
#include <stdio.h>
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

#pragma GCC diagnostic ignored "-Wnonnull-compare"

/* dito for dladdr */
int dladdr (const void *address, Dl_info *info)
{
	typeof(dladdr) *real_dladdr;
	if ((*(void**)&real_dladdr = dlsym(RTLD_NEXT, STR(dladdr))) != 0)
		return real_dladdr(address, info);
	if (info != 0)
	{
		info->dli_fname = 0;
		info->dli_fbase = 0;
		info->dli_sname = 0;
		info->dli_saddr = 0;
	}
	return 0;
}

#ifdef __cplusplus
}
#endif
#undef STR
#undef STR_
#endif
#endif
