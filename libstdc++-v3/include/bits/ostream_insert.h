// Helpers for ostream inserters -*- C++ -*-

// Copyright (C) 2007-2023 Free Software Foundation, Inc.
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

/** @file bits/ostream_insert.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{ostream}
 */

#ifndef _OSTREAM_INSERT_H
#define _OSTREAM_INSERT_H 1

#pragma GCC system_header

#include <iosfwd>
#include <bits/cxxabi_forced.h>
#include <bits/exception_defines.h>

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /// @cond undocumented

  template<typename _CharT, typename _Traits>
    inline void
    __ostream_write(basic_ostream<_CharT, _Traits>& ___out,
		    const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits>       __ostream_type;      
      typedef typename __ostream_type::ios_base    __ios_base;

      const streamsize __put = ___out.rdbuf()->sputn(__s, __n);
      if (__put != __n)
	___out.setstate(__ios_base::badbit);
    }

  template<typename _CharT, typename _Traits>
    inline void
    __ostream_fill(basic_ostream<_CharT, _Traits>& ___out, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits>       __ostream_type;      
      typedef typename __ostream_type::ios_base    __ios_base;

      const _CharT __c = ___out.fill();
      for (; __n > 0; --__n)
	{
	  const typename _Traits::int_type __put = ___out.rdbuf()->sputc(__c);
	  if (_Traits::eq_int_type(__put, _Traits::eof()))
	    {
	      ___out.setstate(__ios_base::badbit);
	      break;
	    }
	}
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    __ostream_insert(basic_ostream<_CharT, _Traits>& ___out,
		     const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits>       __ostream_type;
      typedef typename __ostream_type::ios_base    __ios_base;

      typename __ostream_type::sentry __cerb(___out);
      if (__cerb)
	{
	  __try
	    {
	      const streamsize __w = ___out.width();
	      if (__w > __n)
		{
		  const bool __left = ((___out.flags()
					& __ios_base::adjustfield)
				       == __ios_base::left);
		  if (!__left)
		    __ostream_fill(___out, __w - __n);
		  if (___out.good())
		    __ostream_write(___out, __s, __n);
		  if (__left && ___out.good())
		    __ostream_fill(___out, __w - __n);
		}
	      else
		__ostream_write(___out, __s, __n);
	      ___out.width(0);
	    }
	  __catch(__cxxabiv1::__forced_unwind&)
	    {
	      ___out._M_setstate(__ios_base::badbit);
	      __throw_exception_again;
	    }
	  __catch(...)
	    { ___out._M_setstate(__ios_base::badbit); }
	}
      return ___out;
    }

  // Inhibit implicit instantiations for required instantiations,
  // which are defined via explicit instantiations elsewhere.
#if _GLIBCXX_EXTERN_TEMPLATE
  extern template ostream& __ostream_insert(ostream&, const char*, streamsize);

#ifdef _GLIBCXX_USE_WCHAR_T
  extern template wostream& __ostream_insert(wostream&, const wchar_t*,
					     streamsize);
#endif
#endif

  /// @endcond

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std

#endif /* _OSTREAM_INSERT_H */
