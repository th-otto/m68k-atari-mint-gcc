/* Software floating-point emulation.
   Definitions for IEEE Quad Precision.
   Copyright (C) 1997-2022 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   In addition to the permissions in the GNU Lesser General Public
   License, the Free Software Foundation gives you unlimited
   permission to link the compiled version of this file into
   combinations with other programs, and to distribute those
   combinations without any restriction coming from the use of this
   file.  (The Lesser General Public License restrictions do apply in
   other respects; for example, they cover modification of the file,
   and distribution when not linked into a combine executable.)

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#ifndef SOFT_FP_QUAD_H
#define SOFT_FP_QUAD_H	1

#if _FP_W_TYPE_SIZE < 32
# error "Here's a nickel, kid. Go buy yourself a real computer."
#endif

#if _FP_W_TYPE_SIZE < 64
# define _FP_FRACTBITS_Q	(4*_FP_W_TYPE_SIZE)
# define _FP_FRACTBITS_DW_Q	(8*_FP_W_TYPE_SIZE)
#else
# define _FP_FRACTBITS_Q		(2*_FP_W_TYPE_SIZE)
# define _FP_FRACTBITS_DW_Q	(4*_FP_W_TYPE_SIZE)
#endif

#define _FP_FRACBITS_Q		113
#define _FP_FRACXBITS_Q		(_FP_FRACTBITS_Q - _FP_FRACBITS_Q)
#define _FP_WFRACBITS_Q		(_FP_WORKBITS + _FP_FRACBITS_Q)
#define _FP_WFRACXBITS_Q	(_FP_FRACTBITS_Q - _FP_WFRACBITS_Q)
#define _FP_EXPBITS_Q		15
#define _FP_EXPBIAS_Q		16383
#define _FP_EXPMAX_Q		32767

#define _FP_QNANBIT_Q		\
	((_FP_W_TYPE) 1 << (_FP_FRACBITS_Q-2) % _FP_W_TYPE_SIZE)
#define _FP_QNANBIT_SH_Q		\
	((_FP_W_TYPE) 1 << (_FP_FRACBITS_Q-2+_FP_WORKBITS) % _FP_W_TYPE_SIZE)
#define _FP_IMPLBIT_Q		\
	((_FP_W_TYPE) 1 << (_FP_FRACBITS_Q-1) % _FP_W_TYPE_SIZE)
#define _FP_IMPLBIT_SH_Q		\
	((_FP_W_TYPE) 1 << (_FP_FRACBITS_Q-1+_FP_WORKBITS) % _FP_W_TYPE_SIZE)
#define _FP_OVERFLOW_Q		\
	((_FP_W_TYPE) 1 << (_FP_WFRACBITS_Q % _FP_W_TYPE_SIZE))

#define _FP_WFRACBITS_DW_Q	(2 * _FP_WFRACBITS_Q)
#define _FP_WFRACXBITS_DW_Q	(_FP_FRACTBITS_DW_Q - _FP_WFRACBITS_DW_Q)
#define _FP_HIGHBIT_DW_Q	\
  ((_FP_W_TYPE) 1 << (_FP_WFRACBITS_DW_Q - 1) % _FP_W_TYPE_SIZE)

#ifndef TFtype
typedef float TFtype __attribute__ ((mode (TF)));
#endif

#if _FP_W_TYPE_SIZE < 64

union _FP_UNION_Q
{
  TFtype flt;
  struct _FP_STRUCT_LAYOUT
  {
# if __BYTE_ORDER == __BIG_ENDIAN
    unsigned sign : 1;
    unsigned exp : _FP_EXPBITS_Q;
    unsigned long frac3 : _FP_FRACBITS_Q - (_FP_IMPLBIT_Q != 0)-(_FP_W_TYPE_SIZE * 3);
    unsigned long frac2 : _FP_W_TYPE_SIZE;
    unsigned long frac1 : _FP_W_TYPE_SIZE;
    unsigned long frac0 : _FP_W_TYPE_SIZE;
# else
    unsigned long frac0 : _FP_W_TYPE_SIZE;
    unsigned long frac1 : _FP_W_TYPE_SIZE;
    unsigned long frac2 : _FP_W_TYPE_SIZE;
    unsigned long frac3 : _FP_FRACBITS_Q - (_FP_IMPLBIT_Q != 0)-(_FP_W_TYPE_SIZE * 3);
    unsigned exp : _FP_EXPBITS_Q;
    unsigned sign : 1;
# endif /* not bigendian */
  } bits;
};


# define FP_DECL_Q(X)		_FP_DECL (4, X)
# define FP_UNPACK_RAW_Q(X, val)	_FP_UNPACK_RAW_4 (Q, X, (val))
# define FP_UNPACK_RAW_QP(X, val)	_FP_UNPACK_RAW_4_P (Q, X, (val))
# define FP_PACK_RAW_Q(val, X)	_FP_PACK_RAW_4 (Q, (val), X)
# define FP_PACK_RAW_QP(val, X)			\
  do						\
    {						\
      if (!FP_INHIBIT_RESULTS)			\
	_FP_PACK_RAW_4_P (Q, (val), X);		\
    }						\
  while (0)

# define FP_UNPACK_Q(X, val)			\
  do						\
    {						\
      _FP_UNPACK_RAW_4 (Q, X, (val));		\
      _FP_UNPACK_CANONICAL (Q, 4, X);		\
    }						\
  while (0)

# define FP_UNPACK_QP(X, val)			\
  do						\
    {						\
      _FP_UNPACK_RAW_4_P (Q, X, (val));		\
      _FP_UNPACK_CANONICAL (Q, 4, X);		\
    }						\
  while (0)

# define FP_UNPACK_SEMIRAW_Q(X, val)		\
  do						\
    {						\
      _FP_UNPACK_RAW_4 (Q, X, (val));		\
      _FP_UNPACK_SEMIRAW (Q, 4, X);		\
    }						\
  while (0)

# define FP_UNPACK_SEMIRAW_QP(X, val)		\
  do						\
    {						\
      _FP_UNPACK_RAW_4_P (Q, X, (val));		\
      _FP_UNPACK_SEMIRAW (Q, 4, X);		\
    }						\
  while (0)

# define FP_PACK_Q(val, X)			\
  do						\
    {						\
      _FP_PACK_CANONICAL (Q, 4, X);		\
      _FP_PACK_RAW_4 (Q, (val), X);		\
    }						\
  while (0)

# define FP_PACK_QP(val, X)			\
  do						\
    {						\
      _FP_PACK_CANONICAL (Q, 4, X);		\
      if (!FP_INHIBIT_RESULTS)			\
	_FP_PACK_RAW_4_P (Q, (val), X);		\
    }						\
  while (0)

# define FP_PACK_SEMIRAW_Q(val, X)		\
  do						\
    {						\
      _FP_PACK_SEMIRAW (Q, 4, X);		\
      _FP_PACK_RAW_4 (Q, (val), X);		\
    }						\
  while (0)

# define FP_PACK_SEMIRAW_QP(val, X)		\
  do						\
    {						\
      _FP_PACK_SEMIRAW (Q, 4, X);		\
      if (!FP_INHIBIT_RESULTS)			\
	_FP_PACK_RAW_4_P (Q, (val), X);		\
    }						\
  while (0)

# define FP_ISSIGNAN_Q(X)		_FP_ISSIGNAN (Q, 4, X)
# define FP_NEG_Q(R, X)			_FP_NEG (Q, 4, R, X)
# define FP_ADD_Q(R, X, Y)		_FP_ADD (Q, 4, R, X, Y)
# define FP_SUB_Q(R, X, Y)		_FP_SUB (Q, 4, R, X, Y)
# define FP_MUL_Q(R, X, Y)		_FP_MUL (Q, 4, R, X, Y)
# define FP_DIV_Q(R, X, Y)		_FP_DIV (Q, 4, R, X, Y)
# define FP_SQRT_Q(R, X)		_FP_SQRT (Q, 4, R, X)
# define _FP_SQRT_MEAT_Q(R, S, T, X, Q)	_FP_SQRT_MEAT_4 (R, S, T, X, (Q))
# define FP_FMA_Q(R, X, Y, Z)		_FP_FMA (Q, 4, 8, R, X, Y, Z)

# define FP_CMP_Q(r, X, Y, un, ex)	_FP_CMP (Q, 4, (r), X, Y, (un), (ex))
# define FP_CMP_EQ_Q(r, X, Y, ex)	_FP_CMP_EQ (Q, 4, (r), X, Y, (ex))
# define FP_CMP_UNORD_Q(r, X, Y, ex)	_FP_CMP_UNORD (Q, 4, (r), X, Y, (ex))

# define FP_TO_INT_Q(r, X, rsz, rsg)	_FP_TO_INT (Q, 4, (r), X, (rsz), (rsg))
# define FP_TO_INT_ROUND_Q(r, X, rsz, rsg)	\
  _FP_TO_INT_ROUND (Q, 4, (r), X, (rsz), (rsg))
# define FP_FROM_INT_Q(X, r, rs, rt)	_FP_FROM_INT (Q, 4, X, (r), (rs), rt)

# define _FP_FRAC_HIGH_Q(X)	_FP_FRAC_HIGH_4 (X)
# define _FP_FRAC_ZEROHIGH_Q(X)
# define _FP_FRAC_HIGH_RAW_Q(X)	_FP_FRAC_HIGH_4 (X)

# define _FP_FRAC_HIGH_DW_Q(X)	_FP_FRAC_HIGH_8 (X)

#else   /* not _FP_W_TYPE_SIZE < 64 */
union _FP_UNION_Q
{
  TFtype flt /* __attribute__ ((mode (TF))) */ ;
  struct _FP_STRUCT_LAYOUT
  {
    _FP_W_TYPE a, b;
  } longs;
  struct _FP_STRUCT_LAYOUT
  {
# if __BYTE_ORDER == __BIG_ENDIAN
    unsigned sign    : 1;
    unsigned exp     : _FP_EXPBITS_Q;
    _FP_W_TYPE frac1 : _FP_FRACBITS_Q - (_FP_IMPLBIT_Q != 0) - _FP_W_TYPE_SIZE;
    _FP_W_TYPE frac0 : _FP_W_TYPE_SIZE;
# else
    _FP_W_TYPE frac0 : _FP_W_TYPE_SIZE;
    _FP_W_TYPE frac1 : _FP_FRACBITS_Q - (_FP_IMPLBIT_Q != 0) - _FP_W_TYPE_SIZE;
    unsigned exp     : _FP_EXPBITS_Q;
    unsigned sign    : 1;
# endif
  } bits;
};

# define FP_DECL_Q(X)		_FP_DECL (2, X)
# define FP_UNPACK_RAW_Q(X, val)	_FP_UNPACK_RAW_2 (Q, X, (val))
# define FP_UNPACK_RAW_QP(X, val)	_FP_UNPACK_RAW_2_P (Q, X, (val))
# define FP_PACK_RAW_Q(val, X)	_FP_PACK_RAW_2 (Q, (val), X)
# define FP_PACK_RAW_QP(val, X)			\
  do						\
    {						\
      if (!FP_INHIBIT_RESULTS)			\
	_FP_PACK_RAW_2_P (Q, (val), X);		\
    }						\
  while (0)

# define FP_UNPACK_Q(X, val)			\
  do						\
    {						\
      _FP_UNPACK_RAW_2 (Q, X, (val));		\
      _FP_UNPACK_CANONICAL (Q, 2, X);		\
    }						\
  while (0)

# define FP_UNPACK_QP(X, val)			\
  do						\
    {						\
      _FP_UNPACK_RAW_2_P (Q, X, (val));		\
      _FP_UNPACK_CANONICAL (Q, 2, X);		\
    }						\
  while (0)

# define FP_UNPACK_SEMIRAW_Q(X, val)		\
  do						\
    {						\
      _FP_UNPACK_RAW_2 (Q, X, (val));		\
      _FP_UNPACK_SEMIRAW (Q, 2, X);		\
    }						\
  while (0)

# define FP_UNPACK_SEMIRAW_QP(X, val)		\
  do						\
    {						\
      _FP_UNPACK_RAW_2_P (Q, X, (val));		\
      _FP_UNPACK_SEMIRAW (Q, 2, X);		\
    }						\
  while (0)

# define FP_PACK_Q(val, X)			\
  do						\
    {						\
      _FP_PACK_CANONICAL (Q, 2, X);		\
      _FP_PACK_RAW_2 (Q, (val), X);		\
    }						\
  while (0)

# define FP_PACK_QP(val, X)			\
  do						\
    {						\
      _FP_PACK_CANONICAL (Q, 2, X);		\
      if (!FP_INHIBIT_RESULTS)			\
	_FP_PACK_RAW_2_P (Q, (val), X);		\
    }						\
  while (0)

# define FP_PACK_SEMIRAW_Q(val, X)		\
  do						\
    {						\
      _FP_PACK_SEMIRAW (Q, 2, X);		\
      _FP_PACK_RAW_2 (Q, (val), X);		\
    }						\
  while (0)

# define FP_PACK_SEMIRAW_QP(val, X)		\
  do						\
    {						\
      _FP_PACK_SEMIRAW (Q, 2, X);		\
      if (!FP_INHIBIT_RESULTS)			\
	_FP_PACK_RAW_2_P (Q, (val), X);		\
    }						\
  while (0)

# define FP_ISSIGNAN_Q(X)		_FP_ISSIGNAN (Q, 2, X)
# define FP_NEG_Q(R, X)			_FP_NEG (Q, 2, R, X)
# define FP_ADD_Q(R, X, Y)		_FP_ADD (Q, 2, R, X, Y)
# define FP_SUB_Q(R, X, Y)		_FP_SUB (Q, 2, R, X, Y)
# define FP_MUL_Q(R, X, Y)		_FP_MUL (Q, 2, R, X, Y)
# define FP_DIV_Q(R, X, Y)		_FP_DIV (Q, 2, R, X, Y)
# define FP_SQRT_Q(R, X)		_FP_SQRT (Q, 2, R, X)
# define _FP_SQRT_MEAT_Q(R, S, T, X, Q)	_FP_SQRT_MEAT_2 (R, S, T, X, (Q))
# define FP_FMA_Q(R, X, Y, Z)		_FP_FMA (Q, 2, 4, R, X, Y, Z)

# define FP_CMP_Q(r, X, Y, un, ex)	_FP_CMP (Q, 2, (r), X, Y, (un), (ex))
# define FP_CMP_EQ_Q(r, X, Y, ex)	_FP_CMP_EQ (Q, 2, (r), X, Y, (ex))
# define FP_CMP_UNORD_Q(r, X, Y, ex)	_FP_CMP_UNORD (Q, 2, (r), X, Y, (ex))

# define FP_TO_INT_Q(r, X, rsz, rsg)	_FP_TO_INT (Q, 2, (r), X, (rsz), (rsg))
# define FP_TO_INT_ROUND_Q(r, X, rsz, rsg)	\
  _FP_TO_INT_ROUND (Q, 2, (r), X, (rsz), (rsg))
# define FP_FROM_INT_Q(X, r, rs, rt)	_FP_FROM_INT (Q, 2, X, (r), (rs), rt)

# define _FP_FRAC_HIGH_Q(X)	_FP_FRAC_HIGH_2 (X)
# define _FP_FRAC_ZEROHIGH_Q(X)
# define _FP_FRAC_HIGH_RAW_Q(X)	_FP_FRAC_HIGH_2 (X)

# define _FP_FRAC_HIGH_DW_Q(X)	_FP_FRAC_HIGH_4 (X)

#endif /* not _FP_W_TYPE_SIZE < 64 */

#endif /* !SOFT_FP_QUAD_H */
