#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#define _FILE_OFFSET_BITS 64
#include <sys/stat.h>

#if defined (__cplusplus)
extern "C" {
#endif

#if __GLIBC_PREREQ(2, 33)

#include <stdarg.h>
#include <fcntl.h>

/*
 * those are referenced by the hosts libgnat.a
 */

extern int __xstat64(int __ver, const char *__filename,
      struct stat64 *__stat_buf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern int __lxstat64(int __ver, const char *__filename,
       struct stat64 *__stat_buf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern int __fxstat64(int __ver, int __fildes, struct stat64 *__stat_buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));

__attribute__((__nothrow__))
int stat64(const char *__path, struct stat64 *__statbuf)
{
	return __xstat64(1, __path, __statbuf);
}

__attribute__((__nothrow__))
int lstat64 (const char *__path, struct stat64 *__statbuf)
{
	return __lxstat64(1, __path, __statbuf);
}

__attribute__((__nothrow__))
int fstat64(int __fd, struct stat64 *__statbuf)
{
	return __fxstat64(1, __fd, __statbuf);
}

#undef fcntl
int fcntl64(int fd, int cmd, ...)
{
  va_list ap;
  void *arg;

  va_start (ap, cmd);
  arg = va_arg (ap, void *);
  va_end (ap);

  return fcntl(fd, cmd, arg);
}

#endif /* __GLIBC_PREREQ */

#if defined (__cplusplus)
}
#endif
