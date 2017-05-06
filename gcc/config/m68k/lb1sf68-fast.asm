/* libgcc routines for 68000 w/o floating-point hardware.
   Copyright (C) 1994, 1996, 1997, 1998, 2008, 2009 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#ifdef  L_mulsi3
	.text
	FUNC(__mulsi3)
	.globl	SYM (__mulsi3)
SYM (__mulsi3):
	movel   d0, a0          | d0a0 = x0:x1
	movel   d1, a1		| d1a1 = y0:y1
	swap	d0              | d0   = x1:x0 
	muluw   d1, d0          | d0 = y1*x0 
	swap	d1		| d1 = y1:y0
	movel   a0, d2		| d2 = x0:x1
	muluw   d2, d1          | d1 = x1*y0	
#ifndef __mcoldfire__
	addw	d1, d0
#else
	addl	d1, d0
#endif
	swap	d0
	clrw	d0
	movel	a1,d1		| d1 = y0:y1
	muluw	d2, d1		| d1 = x1*y1

	addl	d1, d0

	rts
#endif /* L_mulsi3 */

#ifdef  L_udivsi3
	.text
	FUNC(__udivsi3)
	.globl	SYM (__udivsi3)
SYM (__udivsi3):
#ifndef __mcoldfire__
	movel	d0, a0

	cmpl	IMM (0x10000), d1 /* divisor >= 2 ^ 16 ?   */
	jcc	L3		/* then try next algorithm */
	movel	d0, d2
	clrw	d2
	swap	d2
	divu	d1, d2          /* high quotient in lower word */
	movew	d2, d0		/* save high quotient */
	swap	d0
	movew	a0, d2		/* get low dividend + high rest */
	divu	d1, d2		/* low quotient */
	movew	d2, d0
	jra	L6

L3:	movel	d1, d2		/* use d2 as divisor backup */
L4:	lsrl	IMM (1), d1	/* shift divisor */
	lsrl	IMM (1), d0	/* shift dividend */
	cmpl	IMM (0x10000), d1 /* still divisor >= 2 ^ 16 ?  */
	jcc	L4
	divu	d1, d0		/* now we have 16-bit divisor */
	andl	IMM (0xffff), d0 /* mask out divisor, ignore remainder */

/* Multiply the 16-bit tentative quotient with the 32-bit divisor.  Because of
   the operand ranges, this might give a 33-bit product.  If this product is
   greater than the dividend, the tentative quotient was too large. */
	movel	d2, d1
	mulu	d0, d1		/* low part, 32 bits */
	swap	d2
	mulu	d0, d2		/* high part, at most 17 bits */
	swap	d2		/* align high part with low part */
	tstw	d2		/* high part 17 bits? */
	jne	L5		/* if 17 bits, quotient was too large */
	addl	d2, d1		/* add parts */
	jcs	L5		/* if sum is 33 bits, quotient was too large */
	cmpl	a0, d1		/* compare the sum with the dividend */
	jls	L6		/* if sum > dividend, quotient was too large */
L5:	subql	IMM (1), d0	/* adjust quotient */

L6:	rts

#else /* __mcoldfire__ */

/* ColdFire implementation of non-restoring division algorithm from
   Hennessy & Patterson, Appendix A. */
	moveml	d3-d4,sp@
	clrl	d2		| clear p
	moveq	IMM (31),d4
L1:	addl	d0,d0		| shift reg pair (p,a) one bit left
	addxl	d2,d2
	movl	d2,d3		| subtract b from p, store in tmp.
	subl	d1,d3
	jcs	L2		| if no carry,
	bset	IMM (0),d0	| set the low order bit of a to 1,
	movl	d3,d2		| and store tmp in p.
L2:	subql	IMM (1),d4
	jcc	L1
	moveml	sp@,d3-d4	| restore data registers
	rts
#endif /* __mcoldfire__ */

#endif /* L_udivsi3 */

#ifdef  L_divsi3
	.text
	FUNC(__divsi3)
	.globl	SYM (__divsi3)
SYM (__divsi3):
	moveq	IMM (1), d2	/* sign of result stored in d2 (=1 or =-1) */
	tstl	d1
	jpl	L1
	negl	d1
#ifndef __mcoldfire__
	negw	d2		/* change sign because divisor <0  */
#else
	negl	d2		/* change sign because divisor <0  */
#endif
L1:	tstl	d0		/* d0 = dividend */
	jpl	L2
	negl	d0
#ifndef __mcoldfire__
	negw	d2
#else
	negl	d2
#endif

L2:	movew	d2,a1		/* Called function MUST NOT clobber a1 */
	PICCALL	SYM (__udivsi3)	/* divide abs(dividend) by abs(divisor) */

	movew	a1,d2
	jpl	L3
	negl	d0

L3:	rts
#endif /* L_divsi3 */

#ifdef  L_umodsi3
	.text
	FUNC(__umodsi3)
	.globl	SYM (__umodsi3)
SYM (__umodsi3):
	movel	d0, d2
	movel	d1, a1		/* a1 MUST NOT be clobbered by calls*/
	PICCALL	SYM (__udivsi3)
	movel	a1, d1		/* d1 = divisor */
#ifndef __mcoldfire__
	PICCALL	SYM (__mulsi3)	/* d0 = (a/b)*b */
#else
	mulsl	d1,d0
#endif
	movel	d2, d1		/* d1 = dividend */
	subl	d0, d1		/* d1 = a - (a/b)*b */
	movel	d1, d0
	rts
#endif /* L_umodsi3 */

#ifdef  L_modsi3
	.text
	FUNC(__modsi3)
	.globl	SYM (__modsi3)
SYM (__modsi3):
	movel	d0, sp@-
	movel	d1, sp@-
	PICCALL	SYM (__divsi3)
	movel	sp@+, d1	/* d1 = divisor */
#ifndef __mcoldfire__
	PICCALL	SYM (__mulsi3)	/* d0 = (a/b)*b */
#else
	mulsl	d1,d0
#endif
	movel	sp@+, d1	/* d1 = dividend */
	subl	d0, d1		/* d1 = a - (a/b)*b */
	movel	d1, d0
	rts
#endif /* L_modsi3 */


#ifdef  L_float

|=============================================================================
|=============================================================================
|                         single precision routines
|=============================================================================
|=============================================================================

| A single precision floating point number (float) has the format:
|
| struct _float {
|  unsigned int sign      : 1;  /* sign bit */ 
|  unsigned int exponent  : 8;  /* exponent, shifted by 126 */
|  unsigned int fraction  : 23; /* fraction */
| } float;
| 
| Thus sizeof(float) = 4 (32 bits). 
|
| All the routines are callable from C programs, and return the result 
| in the single register d0. They also preserve all registers except 
| d0-d1 and a0-a1.

|=============================================================================
|                              __subsf3
|=============================================================================

| float __subsf3(float, float);
	FUNC(__subsf3)
SYM (__subsf3):
	negl	d1       	| change sign of second operand
				| and fall through
|=============================================================================
|                              __addsf3
|=============================================================================

| float __addsf3(float, float);
	FUNC(__addsf3)
SYM (__addsf3):
#ifndef __mcoldfire__
	link	a6,IMM (0)	| everything will be done in registers
	moveml	d2-d7/a2-a5,sp@-	| save all data registers but d0-d1
#else
	link	a6,IMM (-40)
	moveml	d2-d7/a2-a5,sp@
#endif
	movel	d0,a2		| store first operand
	movel	d1,a3		| store second operand
	movel	d0,a0		| get d0's sign bit '
	addl	d0,d0		| check and clear sign bit of a
	beq	Laddsf$b	| if zero return second operand
	movel	d1,a1		| save b's sign bit '
	addl	d1,d1		| get rid of sign bit
	beq	Laddsf$a	| if zero return first operand

| Get the exponents and check for denormalized and/or infinity.

	movel	IMM (0x00ffffff),d4	| mask to get fraction
	movel	IMM (0x01000000),d5	| mask to put hidden bit back

	movel	d0,d6		| save a to get exponent
	andl	d4,d0		| get fraction in d0
	notl 	d4		| make d4 into a mask for the exponent
	andl	d4,d6		| get exponent in d6
	beq	Laddsf$a$den	| branch if a is denormalized
	cmpl	d4,d6		| check for INFINITY or NaN
	beq	Laddsf$nf
	swap	d6		| put exponent into first word
	orl	d5,d0		| and put hidden bit back
Laddsf$1:
| Now we have a's exponent in d6 (second byte) and the mantissa in d0. '
	movel	d1,d7		| get exponent in d7
	andl	d4,d7		| 
	beq	Laddsf$b$den	| branch if b is denormalized
	cmpl	d4,d7		| check for INFINITY or NaN
	beq	Laddsf$nf
	swap	d7		| put exponent into first word
	notl 	d4		| make d4 into a mask for the fraction
	andl	d4,d1		| get fraction in d1
	orl	d5,d1		| and put hidden bit back
Laddsf$2:
| Now we have b's exponent in d7 (second byte) and the mantissa in d1. '

| Note that the hidden bit corresponds to bit #FLT_MANT_DIG-1, and we 
| shifted right once, so bit #FLT_MANT_DIG is set (so we have one extra
| bit).

	movel	d1,d2		| move b to d2, since we want to use
				| two registers to do the sum
	movel	IMM (0),d1	| and clear the new ones
	movel	d1,d3		|

| Here we shift the numbers in registers d0 and d1 so the exponents are the
| same, and put the largest exponent in d6. Note that we are using two
| registers for each number (see the discussion by D. Knuth in "Seminumerical 
| Algorithms").
#ifndef __mcoldfire__
	cmpw	d6,d7		| compare exponents
#else
	cmpl	d6,d7		| compare exponents
#endif
	beq	Laddsf$3	| if equal don't shift '
	bhi	5f		| branch if second exponent largest
1:
	subl	d6,d7		| keep the largest exponent
	negl	d7
#ifndef __mcoldfire__
	lsrw	IMM (8),d7	| put difference in lower byte
#else
	lsrl	IMM (8),d7	| put difference in lower byte
#endif
| if difference is too large we don't shift (actually, we can just exit) '
#ifndef __mcoldfire__
	cmpw	IMM (FLT_MANT_DIG+2),d7		
#else
	cmpl	IMM (FLT_MANT_DIG+2),d7		
#endif
	bge	Laddsf$b$small
#ifndef __mcoldfire__
	cmpw	IMM (16),d7	| if difference >= 16 swap
#else
	cmpl	IMM (16),d7	| if difference >= 16 swap
#endif
	bge	4f
2:
#ifndef __mcoldfire__
	subw	IMM (1),d7
#else
	subql	IMM (1), d7
#endif
3:
#ifndef __mcoldfire__
	lsrl	IMM (1),d2	| shift right second operand
	roxrl	IMM (1),d3
	dbra	d7,3b
#else
	lsrl	IMM (1),d3
	btst	IMM (0),d2
	beq	10f
	bset	IMM (31),d3
10:	lsrl	IMM (1),d2
	subql	IMM (1), d7
	bpl	3b
#endif
	bra	Laddsf$3
4:
	movew	d2,d3
	swap	d3
	movew	d3,d2
	swap	d2
#ifndef __mcoldfire__
	subw	IMM (16),d7
#else
	subl	IMM (16),d7
#endif
	bne	2b		| if still more bits, go back to normal case
	bra	Laddsf$3
5:
#ifndef __mcoldfire__
	exg	d6,d7		| exchange the exponents
#else
	eorl	d6,d7
	eorl	d7,d6
	eorl	d6,d7
#endif
	subl	d6,d7		| keep the largest exponent
	negl	d7		|
#ifndef __mcoldfire__
	lsrw	IMM (8),d7	| put difference in lower byte
#else
	lsrl	IMM (8),d7	| put difference in lower byte
#endif
| if difference is too large we don't shift (and exit!) '
#ifndef __mcoldfire__
	cmpw	IMM (FLT_MANT_DIG+2),d7		
#else
	cmpl	IMM (FLT_MANT_DIG+2),d7		
#endif
	bge	Laddsf$a$small
#ifndef __mcoldfire__
	cmpw	IMM (16),d7	| if difference >= 16 swap
#else
	cmpl	IMM (16),d7	| if difference >= 16 swap
#endif
	bge	8f
6:
#ifndef __mcoldfire__
	subw	IMM (1),d7
#else
	subl	IMM (1),d7
#endif
7:
#ifndef __mcoldfire__
	lsrl	IMM (1),d0	| shift right first operand
	roxrl	IMM (1),d1
	dbra	d7,7b
#else
	lsrl	IMM (1),d1
	btst	IMM (0),d0
	beq	10f
	bset	IMM (31),d1
10:	lsrl	IMM (1),d0
	subql	IMM (1),d7
	bpl	7b
#endif
	bra	Laddsf$3
8:
	movew	d0,d1
	swap	d1
	movew	d1,d0
	swap	d0
#ifndef __mcoldfire__
	subw	IMM (16),d7
#else
	subl	IMM (16),d7
#endif
	bne	6b		| if still more bits, go back to normal case
				| otherwise we fall through

| Now we have a in d0-d1, b in d2-d3, and the largest exponent in d6 (the
| signs are stored in a0 and a1).

Laddsf$3:
| Here we have to decide whether to add or subtract the numbers
#ifndef __mcoldfire__
	exg	d6,a0		| get signs back
	exg	d7,a1		| and save the exponents
#else
	movel	d6,d4
	movel	a0,d6
	movel	d4,a0
	movel	d7,d4
	movel	a1,d7
	movel	d4,a1
#endif
	eorl	d6,d7		| combine sign bits
	bmi	Lsubsf$0	| if negative a and b have opposite 
				| sign so we actually subtract the
				| numbers

| Here we have both positive or both negative
#ifndef __mcoldfire__
	exg	d6,a0		| now we have the exponent in d6
#else
	movel	d6,d4
	movel	a0,d6
	movel	d4,a0
#endif
	movel	a0,d7		| and sign in d7
	andl	IMM (0x80000000),d7
| Here we do the addition.
	addl	d3,d1
	addxl	d2,d0
| Note: now we have d2, d3, d4 and d5 to play with! 

| Put the exponent, in the first byte, in d2, to use the "standard" rounding
| routines:
	movel	d6,d2
#ifndef __mcoldfire__
	lsrw	IMM (8),d2
#else
	lsrl	IMM (8),d2
#endif

| Before rounding normalize so bit #FLT_MANT_DIG is set (we will consider
| the case of denormalized numbers in the rounding routine itself).
| As in the addition (not in the subtraction!) we could have set 
| one more bit we check this:
	btst	IMM (FLT_MANT_DIG+1),d0	
	beq	1f
#ifndef __mcoldfire__
	lsrl	IMM (1),d0
	roxrl	IMM (1),d1
#else
	lsrl	IMM (1),d1
	btst	IMM (0),d0
	beq	10f
	bset	IMM (31),d1
10:	lsrl	IMM (1),d0
#endif
	addl	IMM (1),d2
1:
	lea	pc@(Laddsf$4),a0 | to return from rounding routine
	PICLEA	SYM (_fpCCR),a1	| check the rounding mode
#ifdef __mcoldfire__
	clrl	d6
#endif
	movew	a1@(6),d6	| rounding mode in d6
	beq	Lround$to$nearest
#ifndef __mcoldfire__
	cmpw	IMM (ROUND_TO_PLUS),d6
#else
	cmpl	IMM (ROUND_TO_PLUS),d6
#endif
	bhi	Lround$to$minus
	blt	Lround$to$zero
	bra	Lround$to$plus
Laddsf$4:
| Put back the exponent, but check for overflow.
#ifndef __mcoldfire__
	cmpw	IMM (0xff),d2
#else
	cmpl	IMM (0xff),d2
#endif
	bhi	1f
	bclr	IMM (FLT_MANT_DIG-1),d0
#ifndef __mcoldfire__
	lslw	IMM (7),d2
#else
	lsll	IMM (7),d2
#endif
	swap	d2
	orl	d2,d0
	bra	Laddsf$ret
1:
	moveq	IMM (ADD),d5
	bra	Lf$overflow

Lsubsf$0:
| We are here if a > 0 and b < 0 (sign bits cleared).
| Here we do the subtraction.
	movel	d6,d7		| put sign in d7
	andl	IMM (0x80000000),d7

	subl	d3,d1		| result in d0-d1
	subxl	d2,d0		|
	beq	Laddsf$ret	| if zero just exit
	bpl	1f		| if positive skip the following
	bchg	IMM (31),d7	| change sign bit in d7
	negl	d1
	negxl	d0
1:
#ifndef __mcoldfire__
	exg	d2,a0		| now we have the exponent in d2
	lsrw	IMM (8),d2	| put it in the first byte
#else
	movel	d2,d4
	movel	a0,d2
	movel	d4,a0
	lsrl	IMM (8),d2	| put it in the first byte
#endif

| Now d0-d1 is positive and the sign bit is in d7.

| Note that we do not have to normalize, since in the subtraction bit
| #FLT_MANT_DIG+1 is never set, and denormalized numbers are handled by
| the rounding routines themselves.
	lea	pc@(Lsubsf$1),a0 | to return from rounding routine
	PICLEA	SYM (_fpCCR),a1	| check the rounding mode
#ifdef __mcoldfire__
	clrl	d6
#endif
	movew	a1@(6),d6	| rounding mode in d6
	beq	Lround$to$nearest
#ifndef __mcoldfire__
	cmpw	IMM (ROUND_TO_PLUS),d6
#else
	cmpl	IMM (ROUND_TO_PLUS),d6
#endif
	bhi	Lround$to$minus
	blt	Lround$to$zero
	bra	Lround$to$plus
Lsubsf$1:
| Put back the exponent (we can't have overflow!). '
	bclr	IMM (FLT_MANT_DIG-1),d0
#ifndef __mcoldfire__
	lslw	IMM (7),d2
#else
	lsll	IMM (7),d2
#endif
	swap	d2
	orl	d2,d0
	bra	Laddsf$ret

| If one of the numbers was too small (difference of exponents >= 
| FLT_MANT_DIG+2) we return the other (and now we don't have to '
| check for finiteness or zero).
Laddsf$a$small:
	movel	a3,d0
	PICLEA	SYM (_fpCCR),a0
	movew	IMM (0),a0@
#ifndef __mcoldfire__
	moveml	sp@+,d2-d7/a2-a5	| restore data registers
#else
	moveml	sp@,d2-d7/a2-a5
	lea	a6@(28),a6	
	| XXX if frame pointer is ever removed, stack pointer must
	| be adjusted here.
#endif
	rts		| and return

Laddsf$b$small:
	movel	a2,d0
	PICLEA	SYM (_fpCCR),a0
	movew	IMM (0),a0@
#ifndef __mcoldfire__
	moveml	sp@+,d2-d7/a2-a5	| restore data registers
#else
	moveml	sp@,d2-d7/a2-a5
	lea	a6@(28),a6	
	| XXX if frame pointer is ever removed, stack pointer must
	| be adjusted here.
#endif
	rts		| and return

| If the numbers are denormalized remember to put exponent equal to 1.

Laddsf$a$den:
	movel	d5,d6		| d5 contains 0x01000000
	swap	d6
	bra	Laddsf$1

Laddsf$b$den:
	movel	d5,d7
	swap	d7
	notl 	d4		| make d4 into a mask for the fraction
				| (this was not executed after the jump)
	bra	Laddsf$2

| The rest is mainly code for the different results which can be 
| returned (checking always for +/-INFINITY and NaN).

Laddsf$b:
| Return b (if a is zero).
	movel	a3,d0
	cmpl	IMM (0x80000000),d0	| Check if b is -0
	bne	1f
	movel	a0,d7
	andl	IMM (0x80000000),d7	| Use the sign of a
	clrl	d0
	bra	Laddsf$ret
Laddsf$a:
| Return a (if b is zero).
	movel	a2,d0
1:
	moveq	IMM (ADD),d5
| We have to check for NaN and +/-infty.
	movel	d0,d7
	andl	IMM (0x80000000),d7	| put sign in d7
	bclr	IMM (31),d0		| clear sign
	cmpl	IMM (INFINITY),d0	| check for infty or NaN
	bge	2f
	movel	d0,d0		| check for zero (we do this because we don't '
	bne	Laddsf$ret	| want to return -0 by mistake
	bclr	IMM (31),d7	| if zero be sure to clear sign
	bra	Laddsf$ret	| if everything OK just return
2:
| The value to be returned is either +/-infty or NaN
	andl	IMM (0x007fffff),d0	| check for NaN
	bne	Lf$inop			| if mantissa not zero is NaN
	bra	Lf$infty

Laddsf$ret:
| Normal exit (a and b nonzero, result is not NaN nor +/-infty).
| We have to clear the exception flags (just the exception type).
	PICLEA	SYM (_fpCCR),a0
	movew	IMM (0),a0@
	orl	d7,d0		| put sign bit
#ifndef __mcoldfire__
	moveml	sp@+,d2-d7/a2-a5	| restore data registers
#else
	moveml	sp@,d2-d7/a2-a5
	| XXX if frame pointer is ever removed, stack pointer must
	| be adjusted here.
#endif
	unlk	a6		| and return
	rts

Laddsf$ret$den:
| Return a denormalized number (for addition we don't signal underflow) '
	lsrl	IMM (1),d0	| remember to shift right back once
	bra	Laddsf$ret	| and return

| Note: when adding two floats of the same sign if either one is 
| NaN we return NaN without regard to whether the other is finite or 
| not. When subtracting them (i.e., when adding two numbers of 
| opposite signs) things are more complicated: if both are INFINITY 
| we return NaN, if only one is INFINITY and the other is NaN we return
| NaN, but if it is finite we return INFINITY with the corresponding sign.

Laddsf$nf:
	moveq	IMM (ADD),d5
| This could be faster but it is not worth the effort, since it is not
| executed very often. We sacrifice speed for clarity here.
	movel	a2,d0	| get the numbers back (remember that we
	movel	a3,d1	| did some processing already)
	movel	IMM (INFINITY),d4 | useful constant (INFINITY)
	movel	d0,d2		| save sign bits
	movel	d1,d3
	bclr	IMM (31),d0	| clear sign bits
	bclr	IMM (31),d1
| We know that one of them is either NaN of +/-INFINITY
| Check for NaN (if either one is NaN return NaN)
	cmpl	d4,d0		| check first a (d0)
	bhi	Lf$inop		
	cmpl	d4,d1		| check now b (d1)
	bhi	Lf$inop		
| Now comes the check for +/-INFINITY. We know that both are (maybe not
| finite) numbers, but we have to check if both are infinite whether we
| are adding or subtracting them.
	eorl	d3,d2		| to check sign bits
	bmi	1f
	movel	d0,d7
	andl	IMM (0x80000000),d7	| get (common) sign bit
	bra	Lf$infty
1:
| We know one (or both) are infinite, so we test for equality between the
| two numbers (if they are equal they have to be infinite both, so we
| return NaN).
	cmpl	d1,d0		| are both infinite?
	beq	Lf$inop		| if so return NaN

	movel	d0,d7
	andl	IMM (0x80000000),d7 | get a's sign bit '
	cmpl	d4,d0		| test now for infinity
	beq	Lf$infty	| if a is INFINITY return with this sign
	bchg	IMM (31),d7	| else we know b is INFINITY and has
	bra	Lf$infty	| the opposite sign

|=============================================================================
|                             __mulsf3
|=============================================================================

| float __mulsf3(float, float);
	FUNC(__mulsf3)
SYM (__mulsf3):
#ifndef __mcoldfire__
	link	a6,IMM (0)
	moveml	d2-d7/a2-a5,sp@-
#else
	link	a6,IMM (-40)
	moveml	d2-d7/a2-a5,sp@
#endif
	movel	d0,a2		| store a into a0
	movel	d1,a3		| store b into a1
	movel	d0,d7		| d7 will hold the sign of the product
	eorl	d1,d7		|
	andl	IMM (0x80000000),d7
	movel	IMM (INFINITY),d6	| useful constant (+INFINITY)
	movel	d6,d5			| another (mask for fraction)
	notl	d5			|
	movel	IMM (0x00800000),d4	| this is to put hidden bit back
	bclr	IMM (31),d0		| get rid of a's sign bit '
	movel	d0,d2			|
	beq	Lmulsf$a$0		| branch if a is zero
	bclr	IMM (31),d1		| get rid of b's sign bit '
	movel	d1,d3		|
	beq	Lmulsf$b$0	| branch if b is zero
	cmpl	d6,d0		| is a big?
	bhi	Lmulsf$inop	| if a is NaN return NaN
	beq	Lmulsf$inf	| if a is INFINITY we have to check b
	cmpl	d6,d1		| now compare b with INFINITY
	bhi	Lmulsf$inop	| is b NaN?
	beq	Lmulsf$overflow | is b INFINITY?
| Here we have both numbers finite and nonzero (and with no sign bit).
| Now we get the exponents into d2 and d3.
	andl	d6,d2		| and isolate exponent in d2
	beq	Lmulsf$a$den	| if exponent is zero we have a denormalized
	andl	d5,d0		| and isolate fraction
	orl	d4,d0		| and put hidden bit back
	swap	d2		| I like exponents in the first byte
#ifndef __mcoldfire__
	lsrw	IMM (7),d2	| 
#else
	lsrl	IMM (7),d2	| 
#endif
Lmulsf$1:			| number
	andl	d6,d3		|
	beq	Lmulsf$b$den	|
	andl	d5,d1		|
	orl	d4,d1		|
	swap	d3		|
#ifndef __mcoldfire__
	lsrw	IMM (7),d3	|
#else
	lsrl	IMM (7),d3	|
#endif
Lmulsf$2:			|
#ifndef __mcoldfire__
	addw	d3,d2		| add exponents
	subw	IMM (F_BIAS+1),d2 | and subtract bias (plus one)
#else
	addl	d3,d2		| add exponents
	subl	IMM (F_BIAS+1),d2 | and subtract bias (plus one)
#endif

| We are now ready to do the multiplication. The situation is as follows:
| both a and b have bit FLT_MANT_DIG-1 set (even if they were 
| denormalized to start with!), which means that in the product 
| bit 2*(FLT_MANT_DIG-1) (that is, bit 2*FLT_MANT_DIG-2-32 of the 
| high long) is set. 

| To do the multiplication let us move the number a little bit around ...
	movel	d1,d6		| second operand in d6
	movel	d0,d5		| first operand in d4-d5
	movel	IMM (0),d4
	movel	d4,d1		| the sums will go in d0-d1
	movel	d4,d0

| now bit FLT_MANT_DIG-1 becomes bit 31:
	lsll	IMM (31-FLT_MANT_DIG+1),d6		

| Start the loop (we loop #FLT_MANT_DIG times):
	moveq	IMM (FLT_MANT_DIG-1),d3	
1:	addl	d1,d1		| shift sum 
	addxl	d0,d0
	lsll	IMM (1),d6	| get bit bn
	bcc	2f		| if not set skip sum
	addl	d5,d1		| add a
	addxl	d4,d0
2:
#ifndef __mcoldfire__
	dbf	d3,1b		| loop back
#else
	subql	IMM (1),d3
	bpl	1b
#endif

| Now we have the product in d0-d1, with bit (FLT_MANT_DIG - 1) + FLT_MANT_DIG
| (mod 32) of d0 set. The first thing to do now is to normalize it so bit 
| FLT_MANT_DIG is set (to do the rounding).
#ifndef __mcoldfire__
	rorl	IMM (6),d1
	swap	d1
	movew	d1,d3
	andw	IMM (0x03ff),d3
	andw	IMM (0xfd00),d1
#else
	movel	d1,d3
	lsll	IMM (8),d1
	addl	d1,d1
	addl	d1,d1
	moveq	IMM (22),d5
	lsrl	d5,d3
	orl	d3,d1
	andl	IMM (0xfffffd00),d1
#endif
	lsll	IMM (8),d0
	addl	d0,d0
	addl	d0,d0
#ifndef __mcoldfire__
	orw	d3,d0
#else
	orl	d3,d0
#endif

	moveq	IMM (MULTIPLY),d5
	
	btst	IMM (FLT_MANT_DIG+1),d0
	beq	Lround$exit
#ifndef __mcoldfire__
	lsrl	IMM (1),d0
	roxrl	IMM (1),d1
	addw	IMM (1),d2
#else
	lsrl	IMM (1),d1
	btst	IMM (0),d0
	beq	10f
	bset	IMM (31),d1
10:	lsrl	IMM (1),d0
	addql	IMM (1),d2
#endif
	bra	Lround$exit

Lmulsf$inop:
	moveq	IMM (MULTIPLY),d5
	bra	Lf$inop

Lmulsf$overflow:
	moveq	IMM (MULTIPLY),d5
	bra	Lf$overflow

Lmulsf$inf:
	moveq	IMM (MULTIPLY),d5
| If either is NaN return NaN; else both are (maybe infinite) numbers, so
| return INFINITY with the correct sign (which is in d7).
	cmpl	d6,d1		| is b NaN?
	bhi	Lf$inop		| if so return NaN
	bra	Lf$overflow	| else return +/-INFINITY

| If either number is zero return zero, unless the other is +/-INFINITY, 
| or NaN, in which case we return NaN.
Lmulsf$b$0:
| Here d1 (==b) is zero.
	movel	a2,d1		| get a again to check for non-finiteness
	bra	1f
Lmulsf$a$0:
	movel	a3,d1	| get b again to check for non-finiteness
1:	bclr	IMM (31),d1	| clear sign bit 
	cmpl	IMM (INFINITY),d1 | and check for a large exponent
	bge	Lf$inop		| if b is +/-INFINITY or NaN return NaN
	movel	d7,d0		| else return signed zero
	PICLEA	SYM (_fpCCR),a0	|
	movew	IMM (0),a0@	| 
#ifndef __mcoldfire__
	moveml	sp@+,d2-d7/a2-a5	| 
#else
	moveml	sp@,d2-d7/a2-a5
	| XXX if frame pointer is ever removed, stack pointer must
	| be adjusted here.
#endif
	unlk	a6		| 
	rts			| 

| If a number is denormalized we put an exponent of 1 but do not put the 
| hidden bit back into the fraction; instead we shift left until bit 23
| (the hidden bit) is set, adjusting the exponent accordingly. We do this
| to ensure that the product of the fractions is close to 1.
Lmulsf$a$den:
	movel	IMM (1),d2
	andl	d5,d0
1:	addl	d0,d0		| shift a left (until bit 23 is set)
#ifndef __mcoldfire__
	subw	IMM (1),d2	| and adjust exponent
#else
	subql	IMM (1),d2	| and adjust exponent
#endif
	btst	IMM (FLT_MANT_DIG-1),d0
	bne	Lmulsf$1	|
	bra	1b		| else loop back

Lmulsf$b$den:
	movel	IMM (1),d3
	andl	d5,d1
1:	addl	d1,d1		| shift b left until bit 23 is set
#ifndef __mcoldfire__
	subw	IMM (1),d3	| and adjust exponent
#else
	subql	IMM (1),d3	| and adjust exponent
#endif
	btst	IMM (FLT_MANT_DIG-1),d1
	bne	Lmulsf$2	|
	bra	1b		| else loop back

|=============================================================================
|                             __divsf3
|=============================================================================

| float __divsf3(float, float);
	FUNC(__divsf3)
SYM (__divsf3):
#ifndef __mcoldfire__
	link	a6,IMM (0)
	moveml	d2-d7/a2-a5,sp@-
#else
	link	a6,IMM (-40)
	moveml	d2-d7/a2-a5,sp@
#endif
	movel	d0,d7			| d7 will hold the sign of the result
	eorl	d1,d7			|
	andl	IMM (0x80000000),d7	| 
	movel	IMM (INFINITY),d6	| useful constant (+INFINITY)
	movel	d6,d5			| another (mask for fraction)
	notl	d5			|
	movel	IMM (0x00800000),d4	| this is to put hidden bit back
	bclr	IMM (31),d0		| get rid of a's sign bit '
	movel	d0,d2			|
	beq	Ldivsf$a$0		| branch if a is zero
	bclr	IMM (31),d1		| get rid of b's sign bit '
	movel	d1,d3			|
	beq	Ldivsf$b$0		| branch if b is zero
	cmpl	d6,d0			| is a big?
	bhi	Ldivsf$inop		| if a is NaN return NaN
	beq	Ldivsf$inf		| if a is INFINITY we have to check b
	cmpl	d6,d1			| now compare b with INFINITY 
	bhi	Ldivsf$inop		| if b is NaN return NaN
	beq	Ldivsf$underflow
| Here we have both numbers finite and nonzero (and with no sign bit).
| Now we get the exponents into d2 and d3 and normalize the numbers to
| ensure that the ratio of the fractions is close to 1. We do this by
| making sure that bit #FLT_MANT_DIG-1 (hidden bit) is set.
	andl	d6,d2		| and isolate exponent in d2
	beq	Ldivsf$a$den	| if exponent is zero we have a denormalized
	andl	d5,d0		| and isolate fraction
	orl	d4,d0		| and put hidden bit back
	swap	d2		| I like exponents in the first byte
#ifndef __mcoldfire__
	lsrw	IMM (7),d2	| 
#else
	lsrl	IMM (7),d2	| 
#endif
Ldivsf$1:			| 
	andl	d6,d3		|
	beq	Ldivsf$b$den	|
	andl	d5,d1		|
	orl	d4,d1		|
	swap	d3		|
#ifndef __mcoldfire__
	lsrw	IMM (7),d3	|
#else
	lsrl	IMM (7),d3	|
#endif
Ldivsf$2:			|
#ifndef __mcoldfire__
	subw	d3,d2		| subtract exponents
 	addw	IMM (F_BIAS),d2	| and add bias
#else
	subl	d3,d2		| subtract exponents
 	addl	IMM (F_BIAS),d2	| and add bias
#endif
 
| We are now ready to do the division. We have prepared things in such a way
| that the ratio of the fractions will be less than 2 but greater than 1/2.
| At this point the registers in use are:
| d0	holds a (first operand, bit FLT_MANT_DIG=0, bit FLT_MANT_DIG-1=1)
| d1	holds b (second operand, bit FLT_MANT_DIG=1)
| d2	holds the difference of the exponents, corrected by the bias
| d7	holds the sign of the ratio
| d4, d5, d6 hold some constants
	movel	d7,a0		| d6-d7 will hold the ratio of the fractions
	movel	IMM (0),d6	| 
	movel	d6,d7

	moveq	IMM (FLT_MANT_DIG+1),d3
1:	cmpl	d0,d1		| is a < b?
	bhi	2f		|
	bset	d3,d6		| set a bit in d6
	subl	d1,d0		| if a >= b  a <-- a-b
	beq	3f		| if a is zero, exit
2:	addl	d0,d0		| multiply a by 2
#ifndef __mcoldfire__
	dbra	d3,1b
#else
	subql	IMM (1),d3
	bpl	1b
#endif

| Now we keep going to set the sticky bit ...
	moveq	IMM (FLT_MANT_DIG),d3
1:	cmpl	d0,d1
	ble	2f
	addl	d0,d0
#ifndef __mcoldfire__
	dbra	d3,1b
#else
	subql	IMM(1),d3
	bpl	1b
#endif
	movel	IMM (0),d1
	bra	3f
2:	movel	IMM (0),d1
#ifndef __mcoldfire__
	subw	IMM (FLT_MANT_DIG),d3
	addw	IMM (31),d3
#else
	subl	IMM (FLT_MANT_DIG),d3
	addl	IMM (31),d3
#endif
	bset	d3,d1
3:
	movel	d6,d0		| put the ratio in d0-d1
	movel	a0,d7		| get sign back

| Because of the normalization we did before we are guaranteed that 
| d0 is smaller than 2^26 but larger than 2^24. Thus bit 26 is not set,
| bit 25 could be set, and if it is not set then bit 24 is necessarily set.
	btst	IMM (FLT_MANT_DIG+1),d0		
	beq	1f              | if it is not set, then bit 24 is set
	lsrl	IMM (1),d0	|
#ifndef __mcoldfire__
	addw	IMM (1),d2	|
#else
	addl	IMM (1),d2	|
#endif
1:
| Now round, check for over- and underflow, and exit.
	moveq	IMM (DIVIDE),d5
	bra	Lround$exit

Ldivsf$inop:
	moveq	IMM (DIVIDE),d5
	bra	Lf$inop

Ldivsf$overflow:
	moveq	IMM (DIVIDE),d5
	bra	Lf$overflow

Ldivsf$underflow:
	moveq	IMM (DIVIDE),d5
	bra	Lf$underflow

Ldivsf$a$0:
	moveq	IMM (DIVIDE),d5
| If a is zero check to see whether b is zero also. In that case return
| NaN; then check if b is NaN, and return NaN also in that case. Else
| return a properly signed zero.
	andl	IMM (0x7fffffff),d1	| clear sign bit and test b
	beq	Lf$inop			| if b is also zero return NaN
	cmpl	IMM (INFINITY),d1	| check for NaN
	bhi	Lf$inop			| 
	movel	d7,d0			| else return signed zero
	PICLEA	SYM (_fpCCR),a0		|
	movew	IMM (0),a0@		|
#ifndef __mcoldfire__
	moveml	sp@+,d2-d7/a2-a5		| 
#else
	moveml	sp@,d2-d7/a2-a5		| 
	| XXX if frame pointer is ever removed, stack pointer must
	| be adjusted here.
#endif
	unlk	a6			| 
	rts				| 
	
Ldivsf$b$0:
	moveq	IMM (DIVIDE),d5
| If we got here a is not zero. Check if a is NaN; in that case return NaN,
| else return +/-INFINITY. Remember that a is in d0 with the sign bit 
| cleared already.
	cmpl	IMM (INFINITY),d0	| compare d0 with INFINITY
	bhi	Lf$inop			| if larger it is NaN
	bra	Lf$div$0		| else signal DIVIDE_BY_ZERO

Ldivsf$inf:
	moveq	IMM (DIVIDE),d5
| If a is INFINITY we have to check b
	cmpl	IMM (INFINITY),d1	| compare b with INFINITY 
	bge	Lf$inop			| if b is NaN or INFINITY return NaN
	bra	Lf$overflow		| else return overflow

| If a number is denormalized we put an exponent of 1 but do not put the 
| bit back into the fraction.
Ldivsf$a$den:
	movel	IMM (1),d2
	andl	d5,d0
1:	addl	d0,d0		| shift a left until bit FLT_MANT_DIG-1 is set
#ifndef __mcoldfire__
	subw	IMM (1),d2	| and adjust exponent
#else
	subl	IMM (1),d2	| and adjust exponent
#endif
	btst	IMM (FLT_MANT_DIG-1),d0
	bne	Ldivsf$1
	bra	1b

Ldivsf$b$den:
	movel	IMM (1),d3
	andl	d5,d1
1:	addl	d1,d1		| shift b left until bit FLT_MANT_DIG is set
#ifndef __mcoldfire__
	subw	IMM (1),d3	| and adjust exponent
#else
	subl	IMM (1),d3	| and adjust exponent
#endif
	btst	IMM (FLT_MANT_DIG-1),d1
	bne	Ldivsf$2
	bra	1b

Lround$exit:
| This is a common exit point for __mulsf3 and __divsf3. 

| First check for underlow in the exponent:
#ifndef __mcoldfire__
	cmpw	IMM (-FLT_MANT_DIG-1),d2		
#else
	cmpl	IMM (-FLT_MANT_DIG-1),d2		
#endif
	blt	Lf$underflow	
| It could happen that the exponent is less than 1, in which case the 
| number is denormalized. In this case we shift right and adjust the 
| exponent until it becomes 1 or the fraction is zero (in the latter case 
| we signal underflow and return zero).
	movel	IMM (0),d6	| d6 is used temporarily
#ifndef __mcoldfire__
	cmpw	IMM (1),d2	| if the exponent is less than 1 we 
#else
	cmpl	IMM (1),d2	| if the exponent is less than 1 we 
#endif
	bge	2f		| have to shift right (denormalize)
1:
#ifndef __mcoldfire__
	addw	IMM (1),d2	| adjust the exponent
	lsrl	IMM (1),d0	| shift right once 
	roxrl	IMM (1),d1	|
	roxrl	IMM (1),d6	| d6 collect bits we would lose otherwise
	cmpw	IMM (1),d2	| is the exponent 1 already?
#else
	addql	IMM (1),d2	| adjust the exponent
	lsrl	IMM (1),d6
	btst	IMM (0),d1
	beq	11f
	bset	IMM (31),d6
11:	lsrl	IMM (1),d1
	btst	IMM (0),d0
	beq	10f
	bset	IMM (31),d1
10:	lsrl	IMM (1),d0
	cmpl	IMM (1),d2	| is the exponent 1 already?
#endif
	beq	2f		| if not loop back
	bra	1b              |
	bra	Lf$underflow	| safety check, shouldn't execute '
2:	orl	d6,d1		| this is a trick so we don't lose  '
				| the extra bits which were flushed right
| Now call the rounding routine (which takes care of denormalized numbers):
	lea	pc@(Lround$0),a0 | to return from rounding routine
	PICLEA	SYM (_fpCCR),a1	| check the rounding mode
#ifdef __mcoldfire__
	clrl	d6
#endif
	movew	a1@(6),d6	| rounding mode in d6
	beq	Lround$to$nearest
#ifndef __mcoldfire__
	cmpw	IMM (ROUND_TO_PLUS),d6
#else
	cmpl	IMM (ROUND_TO_PLUS),d6
#endif
	bhi	Lround$to$minus
	blt	Lround$to$zero
	bra	Lround$to$plus
Lround$0:
| Here we have a correctly rounded result (either normalized or denormalized).

| Here we should have either a normalized number or a denormalized one, and
| the exponent is necessarily larger or equal to 1 (so we don't have to  '
| check again for underflow!). We have to check for overflow or for a 
| denormalized number (which also signals underflow).
| Check for overflow (i.e., exponent >= 255).
#ifndef __mcoldfire__
	cmpw	IMM (0x00ff),d2
#else
	cmpl	IMM (0x00ff),d2
#endif
	bge	Lf$overflow
| Now check for a denormalized number (exponent==0).
	movew	d2,d2
	beq	Lf$den
1:
| Put back the exponents and sign and return.
#ifndef __mcoldfire__
	lslw	IMM (7),d2	| exponent back to fourth byte
#else
	lsll	IMM (7),d2	| exponent back to fourth byte
#endif
	bclr	IMM (FLT_MANT_DIG-1),d0
	swap	d0		| and put back exponent
#ifndef __mcoldfire__
	orw	d2,d0		| 
#else
	orl	d2,d0
#endif
	swap	d0		|
	orl	d7,d0		| and sign also

	PICLEA	SYM (_fpCCR),a0
	movew	IMM (0),a0@
#ifndef __mcoldfire__
	moveml	sp@+,d2-d7/a2-a5
#else
	moveml	sp@,d2-d7/a2-a5
	| XXX if frame pointer is ever removed, stack pointer must
	| be adjusted here.
#endif
	unlk	a6
	rts

|=============================================================================
|                             __negsf2
|=============================================================================

| This is trivial and could be shorter if we didn't bother checking for NaN '
| and +/-INFINITY.

| float __negsf2(float);
	FUNC(__negsf2)
SYM (__negsf2):
#ifndef __mcoldfire__
	link	a6,IMM (0)
	moveml	d2-d7/a2-a5,sp@-
#else
	link	a6,IMM (-40)
	moveml	d2-d7/a2-a5,sp@
#endif
	moveq	IMM (NEGATE),d5
	bchg	IMM (31),d0	| negate
	movel	d0,d1		| make a positive copy
	bclr	IMM (31),d1	|
	tstl	d1		| check for zero
	beq	2f		| if zero (either sign) return +zero
	cmpl	IMM (INFINITY),d1 | compare to +INFINITY
	blt	1f		|
	bhi	Lf$inop		| if larger (fraction not zero) is NaN
	movel	d0,d7		| else get sign and return INFINITY
	andl	IMM (0x80000000),d7
	bra	Lf$infty		
1:	PICLEA	SYM (_fpCCR),a0
	movew	IMM (0),a0@
#ifndef __mcoldfire__
	moveml	sp@+,d2-d7/a2-a5
#else
	moveml	sp@,d2-d7/a2-a5
	| XXX if frame pointer is ever removed, stack pointer must
	| be adjusted here.
#endif
	unlk	a6
	rts
2:	bclr	IMM (31),d0
	bra	1b

|=============================================================================
|                             __cmpsf2
|=============================================================================

GREATER =  1
LESS    = -1
EQUAL   =  0

| Last int arg is actually sent in a0!
| int __cmpsf2_internal(float, float, int);
SYM (__cmpsf2_internal):
#ifndef __mcoldfire__
	link	a6,IMM (0)
	moveml	d2-d7/a2-a5,sp@- 	| save registers
#else
	link	a6,IMM (-40)
	moveml	d2-d7/a2-a5,sp@
#endif
	moveq	IMM (COMPARE),d5
| Check if either is NaN, and in that case return garbage and signal
| INVALID_OPERATION. Check also if either is zero, and clear the signs
| if necessary.
	movel	d0,d6
	andl	IMM (0x7fffffff),d0
	beq	Lcmpsf$a$0
	cmpl	IMM (0x7f800000),d0
	bhi	Lcmpf$inop
Lcmpsf$1:
	movel	d1,d7
	andl	IMM (0x7fffffff),d1
	beq	Lcmpsf$b$0
	cmpl	IMM (0x7f800000),d1
	bhi	Lcmpf$inop
Lcmpsf$2:
| Check the signs
	eorl	d6,d7
	bpl	1f
| If the signs are not equal check if a >= 0
	tstl	d6
	bpl	Lcmpsf$a$gt$b	| if (a >= 0 && b < 0) => a > b
	bmi	Lcmpsf$b$gt$a	| if (a < 0 && b >= 0) => a < b
1:
| If the signs are equal check for < 0
	tstl	d6
	bpl	1f
| If both are negative exchange them
#ifndef __mcoldfire__
	exg	d0,d1
#else
	movel	d0,d7
	movel	d1,d0
	movel	d7,d1
#endif
1:
| Now that they are positive we just compare them as longs (does this also
| work for denormalized numbers?).
	cmpl	d0,d1
	bhi	Lcmpsf$b$gt$a	| |b| > |a|
	bne	Lcmpsf$a$gt$b	| |b| < |a|
| If we got here a == b.
	movel	IMM (EQUAL),d0
#ifndef __mcoldfire__
	moveml	sp@+,d2-d7/a2-a5 	| put back the registers
#else
	moveml	sp@,d2-d7/a2-a5
#endif
	unlk	a6
	rts
Lcmpsf$a$gt$b:
	movel	IMM (GREATER),d0
#ifndef __mcoldfire__
	moveml	sp@+,d2-d7/a2-a5 	| put back the registers
#else
	moveml	sp@,d2-d7/a2-a5
	| XXX if frame pointer is ever removed, stack pointer must
	| be adjusted here.
#endif
	unlk	a6
	rts
Lcmpsf$b$gt$a:
	movel	IMM (LESS),d0
#ifndef __mcoldfire__
	moveml	sp@+,d2-d7/a2-a5 	| put back the registers
#else
	moveml	sp@,d2-d7/a2-a5
	| XXX if frame pointer is ever removed, stack pointer must
	| be adjusted here.
#endif
	unlk	a6
	rts

Lcmpsf$a$0:	
	bclr	IMM (31),d6
	bra	Lcmpsf$1
Lcmpsf$b$0:
	bclr	IMM (31),d7
	bra	Lcmpsf$2

Lcmpf$inop:
	movel	a0,d0
	moveq	IMM (INEXACT_RESULT+INVALID_OPERATION),d7
	moveq	IMM (SINGLE_FLOAT),d6
	PICJUMP	$_exception_handler

| int __cmpsf2(float, float);
	FUNC(__cmpsf2)
SYM (__cmpsf2):
	lea	1.w,a0
	bra	SYM (__cmpsf2_internal)

#endif /* L_float */

| gcc expects the routines __eqdf2, __nedf2, __gtdf2, __gedf2,
| __ledf2, __ltdf2 to all return the same value as a direct call to
| __cmpdf2 would.  In this implementation, each of these routines
| simply calls __cmpdf2.  It would be more efficient to give the
| __cmpdf2 routine several names, but separating them out will make it
| easier to write efficient versions of these routines someday.
| If the operands recompare unordered unordered __gtdf2 and __gedf2 return -1.
| The other routines return 1.

| The comments above about __eqdf2, et. al., also apply to __eqsf2,
| et. al., except that the latter call __cmpsf2 rather than __cmpdf2.

#ifdef  L_eqsf2
	.text
	FUNC(__eqsf2)
	.globl	SYM (__eqsf2)
SYM (__eqsf2):
	lea	1.w,a0
	bra	SYM (__cmpsf2_internal)

#endif /* L_eqsf2 */

#ifdef  L_nesf2
	.text
	FUNC(__nesf2)
	.globl	SYM (__nesf2)
SYM (__nesf2):
	lea	1.w,a0
	bra	SYM (__cmpsf2_internal)
#endif /* L_nesf2 */

#ifdef  L_gtsf2
	.text
	FUNC(__gtsf2)
	.globl	SYM (__gtsf2)
SYM (__gtsf2):
	lea	-1.w,a0
	bra	SYM (__cmpsf2_internal)
#endif /* L_gtsf2 */

#ifdef  L_gesf2
	.text
	FUNC(__gesf2)
	.globl	SYM (__gesf2)
SYM (__gesf2):
	lea	-1.w,a0
	bra	SYM (__cmpsf2_internal)
#endif /* L_gesf2 */

#ifdef  L_ltsf2
	.text
	FUNC(__ltsf2)
	.globl	SYM (__ltsf2)
SYM (__ltsf2):
	lea	1.w,a0
	bra	SYM (__cmpsf2_internal)
#endif /* L_ltsf2 */

#ifdef  L_lesf2
	.text
	FUNC(__lesf2)
	.globl	SYM (__lesf2)
SYM (__lesf2):
	lea	1.w,a0
	bra	SYM (__cmpsf2_internal)
#endif /* L_lesf2 */
