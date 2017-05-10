
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

#ifndef _GLIBCXX_EXPERIMENTAL_FS_POSIX_H
#define _GLIBCXX_EXPERIMENTAL_FS_POSIX_H 1

#define os_DIR_t DIR
#define os_dirent_t dirent
#define os_open open
#define os_opendir opendir
#define os_closedir closedir
#define os_readdir readdir
#define os_stat stat
#define os_stat_t stat
#define os_chmod chmod
#define os_mkdir mkdir
#define os_getcwd getcwd
#define os_chdir chdir
#define os_utimbuf_t utimbuf
#define os_utime utime
#define os_remove remove
#define os_rename rename
#define os_truncate truncate

#define os_utime utime

#define _WS(x) x

#endif // _GLIBCXX_EXPERIMENTAL_FS_POSIX_H
