
// Copyright (C) 2014-2017 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#ifndef _GLIBCXX_EXPERIMENTAL_FS_WIN32_H
#define _GLIBCXX_EXPERIMENTAL_FS_WIN32_H 1

#define os_DIR_t _WDIR
#define os_dirent_t _wdirent
#define os_open _wopen
#define os_opendir _wopendir
#define os_closedir _wclosedir
#define os_readdir _wreaddir
#define os_stat _wstat
#define os_stat_t _stat
#define os_chmod _wchmod
#define os_mkdir _wmkdir
#define os_getcwd _wgetcwd
#define os_chdir _wchdir
#define os_utimbuf_t _utimbuf
#define os_utime _wutime
#define os_remove _wremove
#define os_rename _wrename

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

inline int _wtruncate(const wchar_t *fname, _off64_t size) {
  int fd = ::os_open(fname, _O_BINARY|_O_RDWR);
  if (fd == -1) return fd;
  int ret = ::ftruncate64(fd, size), err=0;
  _get_errno(&err);
  _close(fd);
  _set_errno(err);
  return ret;
}

#define os_truncate _wtruncate

#define os_utime _wutime

#define _WS(x) L##x

#endif // _GLIBCXX_EXPERIMENTAL_FS_WIN32_H
