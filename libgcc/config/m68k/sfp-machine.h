#define _FP_W_TYPE_SIZE		32
#define _FP_W_TYPE		unsigned long
#define _FP_WS_TYPE		signed long
#define _FP_I_TYPE		long

/* The type of the result of a floating point comparison.  This must
   match `__libgcc_cmp_return__' in GCC for the target.  */
typedef int __gcc_CMPtype __attribute__ ((mode (__libgcc_cmp_return__)));
#define CMPtype __gcc_CMPtype

#if 0 /* does not work, because all inputs/outputs must be in data registers */

#define __FP_FRAC_ADD_4(r3,r2,r1,r0,x3,x2,x1,x0,y3,y2,y1,y0)	\
  __asm__ ("addl %11,%3\n\t"				\
	   "addxl %9,%2\n\t"				\
	   "addxl %7,%1\n\t"				\
	   "addxl %5,%0"				\
	   : "=d" ((USItype) (r3)),				\
	     "=&d" ((USItype) (r2)),				\
	     "=&d" ((USItype) (r1)),				\
	     "=&d" ((USItype) (r0))				\
	   : "%0" ((USItype) (x3)),				\
	     "g" ((USItype) (y3)),				\
	     "%1" ((USItype) (x2)),				\
	     "g" ((USItype) (y2)),				\
	     "%2" ((USItype) (x1)),				\
	     "g" ((USItype) (y1)),				\
	     "%3" ((USItype) (x0)),				\
	     "g" ((USItype) (y0)))
#define __FP_FRAC_ADD_3(r2,r1,r0,x2,x1,x0,y2,y1,y0)		\
  __asm__ ("addl %8,%2\n\t"				\
	   "addxl %6,%1\n\t"				\
	   "addxl %4,%0"				\
	   : "=d" ((USItype) (r2)),				\
	     "=&d" ((USItype) (r1)),				\
	     "=&d" ((USItype) (r0))				\
	   : "%0" ((USItype) (x2)),				\
	     "g" ((USItype) (y2)),				\
	     "%1" ((USItype) (x1)),				\
	     "g" ((USItype) (y1)),				\
	     "%2" ((USItype) (x0)),				\
	     "g" ((USItype) (y0)))
#define __FP_FRAC_SUB_4(r3,r2,r1,r0,x3,x2,x1,x0,y3,y2,y1,y0)	\
  __asm__ ("subl %11,%3\n\t"				\
	   "subxl %9,%2\n\t"				\
	   "subxl %7,%1\n\t"				\
	   "subxl %5,%0"				\
	   : "=d" ((USItype) (r3)),				\
	     "=&d" ((USItype) (r2)),				\
	     "=&d" ((USItype) (r1)),				\
	     "=&d" ((USItype) (r0))				\
	   : "0" ((USItype) (x3)),				\
	     "g" ((USItype) (y3)),				\
	     "1" ((USItype) (x2)),				\
	     "g" ((USItype) (y2)),				\
	     "2" ((USItype) (x1)),				\
	     "g" ((USItype) (y1)),				\
	     "3" ((USItype) (x0)),				\
	     "g" ((USItype) (y0)))
#define __FP_FRAC_SUB_3(r2,r1,r0,x2,x1,x0,y2,y1,y0)		\
  __asm__ ("subl %8,%2\n\t"				\
	   "subxl %6,%1\n\t"				\
	   "subxl %4,%0"				\
	   : "=d" ((USItype) (r2)),				\
	     "=&d" ((USItype) (r1)),				\
	     "=&d" ((USItype) (r0))				\
	   : "0" ((USItype) (x2)),				\
	     "g" ((USItype) (y2)),				\
	     "1" ((USItype) (x1)),				\
	     "g" ((USItype) (y1)),				\
	     "2" ((USItype) (x0)),				\
	     "g" ((USItype) (y0)))
#endif
#define __FP_FRAC_ADDI_4(x3,x2,x1,x0,i)				\
  do { \
    long zero; \
  	__asm__ ("moveq #0,%4\n\t" \
       "addl %5,%3\n\t"				\
	   "addxl %4,%2\n\t"				\
	   "addxl %4,%1\n\t"				\
	   "addxl %4,%0"				\
	   : "+d" ((USItype) (x3)),				\
	     "+&d" ((USItype) (x2)),				\
	     "+&d" ((USItype) (x1)),				\
	     "+&d" ((USItype) (x0)),				\
	     "=d"(zero) \
	   : "g" ((USItype) (i))); \
	} while(0)

#define _FP_MUL_MEAT_S(R,X,Y)	_FP_MUL_MEAT_1_wide(_FP_WFRACBITS_S,R,X,Y,umul_ppmm)
#define _FP_MUL_MEAT_D(R,X,Y)	_FP_MUL_MEAT_2_wide(_FP_WFRACBITS_D,R,X,Y,umul_ppmm)
#define _FP_MUL_MEAT_E(R,X,Y)	_FP_MUL_MEAT_4_wide(_FP_WFRACBITS_E,R,X,Y,umul_ppmm)
#define _FP_MUL_MEAT_Q(R,X,Y)	_FP_MUL_MEAT_4_wide(_FP_WFRACBITS_Q,R,X,Y,umul_ppmm)

#define _FP_DIV_MEAT_S(R,X,Y)   _FP_DIV_MEAT_1_loop(S,R,X,Y)
#define _FP_DIV_MEAT_D(R,X,Y)   _FP_DIV_MEAT_2_udiv(D,R,X,Y)
#define _FP_DIV_MEAT_E(R,X,Y)   _FP_DIV_MEAT_4_udiv(E,R,X,Y)
#define _FP_DIV_MEAT_Q(R,X,Y)   _FP_DIV_MEAT_4_udiv(Q,R,X,Y)

#define _FP_NANFRAC_H		_FP_QNANBIT_H
#define _FP_NANFRAC_B		_FP_QNANBIT_B
#define _FP_NANFRAC_S		_FP_QNANBIT_S
#define _FP_NANFRAC_D		_FP_QNANBIT_D, 0
/* Even if XFmode is 12byte,  we have to pad it to
   16byte since soft-fp emulation is done in 16byte.  */
#define _FP_NANFRAC_E		_FP_QNANBIT_E, 0, 0, 0
#define _FP_NANFRAC_Q		_FP_QNANBIT_Q, 0, 0, 0

#ifndef _SOFT_FLOAT
#define FP_EX_SHIFT 0

#define _FP_DECL_EX \
  unsigned short _fcw __attribute__ ((unused)) = FP_RND_NEAREST;

#define FP_RND_NEAREST		0
#define FP_RND_ZERO		0x010
#define FP_RND_PINF		0x020
#define FP_RND_MINF		0x030

#define FP_RND_MASK		0x030

#define FP_INIT_ROUNDMODE

#endif

#define _FP_KEEPNANFRACP	1
#define _FP_QNANNEGATEDP 0

#define _FP_NANSIGN_H		0
#define _FP_NANSIGN_B		0
#define _FP_NANSIGN_S		0
#define _FP_NANSIGN_D		0
#define _FP_NANSIGN_E		0
#define _FP_NANSIGN_Q		0

/* Here is something Intel misdesigned: the specs don't define
   the case where we have two NaNs with same mantissas, but
   different sign. Different operations pick up different NaNs.  */
#define _FP_CHOOSENAN(fs, wc, R, X, Y, OP)			\
  do {								\
    if (_FP_FRAC_GT_##wc(X, Y)					\
	|| (_FP_FRAC_EQ_##wc(X,Y) && (OP == '+' || OP == '*')))	\
      {								\
	R##_s = X##_s;						\
	_FP_FRAC_COPY_##wc(R,X);				\
      }								\
    else							\
      {								\
	R##_s = Y##_s;						\
	_FP_FRAC_COPY_##wc(R,Y);				\
      }								\
    R##_c = FP_CLS_NAN;						\
  } while (0)

#ifndef _SOFT_FLOAT
/*
 * these are arbitrary, but we choose
 * the same values as co-processor would use
 */
#define FP_EX_INVALID		0x4000
#define FP_EX_OVERFLOW		0x1000
#define FP_EX_DIVZERO		0x0400
#define FP_EX_UNDERFLOW		0x0800
#define FP_EX_INEXACT		0x0200
#define FP_EX_ALL \
	(FP_EX_INVALID | FP_EX_DENORM | FP_EX_DIVZERO | FP_EX_OVERFLOW \
	 | FP_EX_UNDERFLOW | FP_EX_INEXACT)

void __sfp_handle_exceptions (int);

#define FP_HANDLE_EXCEPTIONS			\
  do {						\
    if (__builtin_expect (_fex, 0))		\
      __sfp_handle_exceptions (_fex);		\
  } while (0)

#define FP_TRAPPING_EXCEPTIONS ((_fcw >> FP_EX_SHIFT) & FP_EX_ALL)

#define FP_ROUNDMODE		(_fcw & FP_RND_MASK)
#endif

#define _FP_TININESS_AFTER_ROUNDING 1

#define	__LITTLE_ENDIAN	1234
#define	__BIG_ENDIAN	4321

#define __BYTE_ORDER __BIG_ENDIAN

/* Define ALIASNAME as a strong alias for NAME.  */
# define strong_alias(name, aliasname) _strong_alias(name, aliasname)
# define _strong_alias(name, aliasname) \
  extern __typeof (name) aliasname __attribute__ ((alias (#name)));

