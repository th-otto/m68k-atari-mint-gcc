// Stub definitions for float math.

// Copyright (C) 2001-2020 Free Software Foundation, Inc.
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

// For targets which do not have support for float versions,
// we use the following crude approximations. We keep saying that we'll do
// better later, but never do.

#define WEAK __attribute__((weak))

extern "C"
{
#ifndef _GLIBCXX_HAVE_FABSF
  float WEAK
  fabsf(float x)
  {
    return (float) fabs(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_ACOSF
  float WEAK
  acosf(float x)
  {
    return (float) acos(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_ASINF
  float WEAK
  asinf(float x)
  {
    return (float) asin(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_ATANF
  float WEAK
  atanf(float x)
  {
    return (float) atan(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_ATAN2F
  float WEAK
  atan2f(float x, float y)
  {
    return (float) atan2(x, y);
  }
#endif

#ifndef _GLIBCXX_HAVE_CEILF
  float WEAK
  ceilf(float x)
  {
    return (float) ceil(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_COSF
  float WEAK
  cosf(float x)
  {
    return (float) cos(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_COSHF
  float WEAK
  coshf(float x)
  {
    return (float) cosh(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_EXPF
  float WEAK
  expf(float x)
  {
    return (float) exp(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_FLOORF
  float WEAK
  floorf(float x)
  {
    return (float) floor(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_FMODF
  float WEAK
  fmodf(float x, float y)
  {
    return (float) fmod(x, y);
  }
#endif

#ifndef _GLIBCXX_HAVE_FREXPF
  float WEAK
  frexpf(float x, int *exp)
  {
    return (float) frexp(x, exp);
  }
#endif

#ifndef _GLIBCXX_HAVE_SQRTF
  float WEAK
  sqrtf(float x)
  {
    return (float) sqrt(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_HYPOTF
  float WEAK
  hypotf(float x, float y)
  {
    float s = fabsf(x) + fabsf(y);
    if (s == 0.0F)
      return s;
    x /= s; y /= s;
    return s * sqrtf(x * x + y * y);
  }
#endif

#ifndef _GLIBCXX_HAVE_LDEXPF
  float WEAK
  ldexpf(float x, int exp)
  {
    return (float) ldexp(x, exp);
  }
#endif

#ifndef _GLIBCXX_HAVE_LOGF
  float WEAK
  logf(float x)
  {
    return (float) log(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_LOG10F
  float WEAK
  log10f(float x)
  {
    return (float) log10(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_MODFF
  float WEAK
  modff(float x, float *iptr)
  {
    double result, temp;

    result = modf(x, &temp);
    *iptr = (float) temp;
    return (float) result;
  }
#endif

#ifndef _GLIBCXX_HAVE_POWF
  float WEAK
  powf(float x, float y)
  {
    return (float) pow(x, y);
  }
#endif

#ifndef _GLIBCXX_HAVE_SINF
  float WEAK
  sinf(float x)
  {
    return (float) sin(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_SINHF
  float WEAK
  sinhf(float x)
  {
    return (float) sinh(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_TANF
  float WEAK
  tanf(float x)
  {
    return (float) tan(x);
  }
#endif

#ifndef _GLIBCXX_HAVE_TANHF
  float WEAK
  tanhf(float x)
  {
    return (float) tanh(x);
  }
#endif
} // extern "C"
