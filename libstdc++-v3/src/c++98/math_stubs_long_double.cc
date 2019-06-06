// Stub definitions for long double math.

// Copyright (C) 2001-2019 Free Software Foundation, Inc.
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

#include <cmath>

// For targets which do not have support for long double versions,
// we use the following crude approximations. We keep saying that we'll do
// better later, but never do.

#define WEAK __attribute__((weak))

extern "C"
{
#ifndef _GLIBCXX_HAVE_FABSL
  long double WEAK
  fabsl(long double x)
  {
    return fabs((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_ACOSL
  long double WEAK
  acosl(long double x)
  {
    return acos((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_ASINL
  long double WEAK
  asinl(long double x)
  {
    return asin((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_ATANL
  long double WEAK
  atanl(long double x)
  {
    return atan ((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_ATAN2L
  long double WEAK
  atan2l(long double x, long double y)
  {
    return atan2((double) x, (double) y);
  }
#endif

#ifndef _GLIBCXX_HAVE_CEILL
  long double WEAK
  ceill(long double x)
  {
    return ceil((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_COSL
  long double WEAK
  cosl(long double x)
  {
    return cos((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_COSHL
  long double WEAK
  coshl(long double x)
  {
    return cosh((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_EXPL
  long double WEAK
  expl(long double x)
  {
    return exp((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_FLOORL
  long double WEAK
  floorl(long double x)
  {
    return floor((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_FMODL
  long double WEAK
  fmodl(long double x, long double y)
  {
    return fmod((double) x, (double) y);
  }
#endif

#ifndef _GLIBCXX_HAVE_FREXPL
  long double WEAK
  frexpl(long double x, int *exp)
  {
    return frexp((double) x, exp);
  }
#endif

#ifndef _GLIBCXX_HAVE_SQRTL
  long double WEAK
  sqrtl(long double x)
  {
    return  sqrt((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_HYPOTL
  long double WEAK
  hypotl(long double x, long double y)
  {
    long double s = fabsl(x) + fabsl(y);
    if (s == 0.0L)
      return s;
    x /= s; y /= s;
    return s * sqrtl(x * x + y * y);
  }
#endif

#ifndef _GLIBCXX_HAVE_LDEXPL
  long double WEAK
  ldexpl(long double x, int exp)
  {
    return ldexp((double) x, exp);
  }
#endif

#ifndef _GLIBCXX_HAVE_LOGL
  long double WEAK
  logl(long double x)
  {
    return log((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_LOG10L
  long double WEAK
  log10l(long double x)
  {
    return log10((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_MODFL
  long double WEAK
  modfl(long double x, long double *iptr)
  {
    double result, temp;

    result = modf((double) x, &temp);
    *iptr = temp;
    return result;
  }
#endif

#ifndef _GLIBCXX_HAVE_POWL
  long double WEAK
  powl(long double x, long double y)
  {
    return pow((double) x, (double) y);
  }
#endif

#ifndef _GLIBCXX_HAVE_SINL
  long double WEAK
  sinl(long double x)
  {
    return sin((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_SINHL
  long double WEAK
  sinhl(long double x)
  {
    return sinh((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_TANL
  long double WEAK
  tanl(long double x)
  {
    return tan((double) x);
  }
#endif

#ifndef _GLIBCXX_HAVE_TANHL
  long double WEAK
  tanhl(long double x)
  {
    return tanh((double) x);
  }
#endif
} // extern "C"
