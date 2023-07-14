|=============================================================================
|                              __addxf3
|=============================================================================

| long double __addxf3(long double, long double);
	FUNC(__addxf3)
SYM (__addxf3):
	link	a6,IMM (-40)	| everything will be done in registers
	moveml	d2-d7/a2-a5,sp@	| save all data registers and a2-a5 (but d0-d1)
	moveml	a6@(8),d0-d1/a4	| get first operand into d0-d1/a4
	clrw	d0
	moveml	a6@(20),d2-d3/a5 | and second operand into d2-d3/a5
	clrw	d2

	movel	d0,d7		| get d0's sign bit in d7
	bclr	IMM(31),d0
	movel	a4,d4
	orl		d0,d4
	orl		d1,d4
	beq	Laddxf$b	| if zero return second operand

	movel	d2,d6		| save sign in d6
	bclr	IMM(31),d2
	movel	a5,d4
	orl		d2,d4
	orl		d3,d4
	beq	Laddxf$a	| if zero return first operand

	andl	IMM (0x80000000),d7 | isolate a's sign bit
    swap	d6		| and also b's sign bit
#ifndef __mcoldfire__
	andw	IMM (0x8000),d6	|
	orw	d6,d7		| and combine them into d7, so that a's sign
				| bit is in the high word and b's is in the
				| low word, so d6 is free to be used
#else
	andl	IMM (0x8000),d6
	orl	d6,d7
#endif
	movel	d7,a0		| now save d7 into a0, so d7 is free to
                		| be used also

| Get the exponents and check for denormalized and/or infinity.

	movel	IMM (0x7fffffff),d6 | mask for the fraction
	movel	IMM (0x80000000),d7 | mask to put hidden bit back

	andl	d6,d1		| get fraction in d1
	movel	d0,d4		|
	swap	d4			| get exponent in d4
	beq	Laddxf$a$den	| branch if a is denormalized
#ifndef __mcoldfire__
	cmpw	IMM(X_MAX_EXP),d4		| check for INFINITY or NaN
#else
	cmpl	IMM(X_MAX_EXP),d4		| check for INFINITY or NaN
#endif
	beq	Laddxf$nf       |
	orl	d7,d1		| and put hidden bit back
Laddxf$1:
	movel	d1,d0
	movel	a4,d1
| Now we have a's exponent in d4 and fraction in d0-d1

	andl	d6,d3		| get fraction in d3
	movel	d2,d5
	swap	d5		| get exponent in d5
	beq	Laddxf$b$den	| branch if b is denormalized
#ifndef __mcoldfire__
	cmpw	IMM(X_MAX_EXP),d5		| check for INFINITY or NaN
#else
	cmpl	IMM(X_MAX_EXP),d5		| check for INFINITY or NaN
#endif
	beq	Laddxf$nf
	orl	d7,d3		| and put hidden bit back
Laddxf$2:

	movel	d3,d2
	movel	a5,d3
| Now we have b's exponent in d5 and fraction in d2-d3.

| The situation now is as follows: the signs are combined in a0, the
| numbers are in d0-d1 (a) and d2-d3 (b), and the exponents in d4 (a)
| and d5 (b). To do the rounding correctly we need to keep all the
| bits until the end, so we need to use d0-d1-d2-d3 for the first number
| and d4-d5-d6-d7 for the second. To do this we store (temporarily) the
| exponents in a2-a3.

	movel	d4,a2		| save the exponents
	movel	d5,a3		|

	movel	IMM (0),d7	| and move the numbers around
	movel	d7,d6		|
	movel	d3,d5		|
	movel	d2,d4		|
	movel	d7,d3		|
	movel	d7,d2		|

| Here we shift the numbers until the exponents are the same, and put
| the largest exponent in a2.
#ifndef __mcoldfire__
	exg	d4,a2		| get exponents back
	exg	d5,a3		|
	cmpw	d4,d5		| compare the exponents
#else
	movel	d4,a4		| get exponents back
	movel	a2,d4
	movel	a4,a2
	movel	d5,a4
	movel	a3,d5
	movel	a4,a3
	cmpl	d4,d5		| compare the exponents
#endif
	beq	Laddxf$3	| if equal don't shift
	bhi	9f		| branch if second exponent is higher

| Here we have a's exponent larger than b's, so we have to shift b. We do
| this by using as counter d2:
1:	movew	d4,d2		| move largest exponent to d2
#ifndef __mcoldfire__
	subw	d5,d2		| and subtract second exponent
	exg	d4,a2		| get back the longs we saved
	exg	d5,a3		|
#else
	subl	d5,d2		| and subtract second exponent
	movel	d4,a4		| get back the longs we saved
	movel	a2,d4
	movel	a4,a2
	movel	d5,a4
	movel	a3,d5
	movel	a4,a3
#endif
| if difference is too large we don't shift (actually, we can just exit)
#ifndef __mcoldfire__
	cmpw	IMM (LDBL_MANT_DIG),d2
#else
	cmpl	IMM (LDBL_MANT_DIG),d2
#endif
	bge	Laddxf$b$small
#ifndef __mcoldfire__
	cmpw	IMM (32),d2	| if difference >= 32, shift by longs
#else
	cmpl	IMM (32),d2	| if difference >= 32, shift by longs
#endif
	bge	5f
2:
#ifndef __mcoldfire__
	cmpw	IMM (16),d2	| if difference >= 16, shift by words
#else
	cmpl	IMM (16),d2	| if difference >= 16, shift by words
#endif
	bge	6f
	bra	3f		| enter dbra loop

4:
#ifndef __mcoldfire__
	lsrl	IMM (1),d4
	roxrl	IMM (1),d5
	roxrl	IMM (1),d6
	roxrl	IMM (1),d7
#else
	lsrl	IMM (1),d7
	btst	IMM (0),d6
	beq	10f
	bset	IMM (31),d7
10:	lsrl	IMM (1),d6
	btst	IMM (0),d5
	beq	11f
	bset	IMM (31),d6
11:	lsrl	IMM (1),d5
	btst	IMM (0),d4
	beq	12f
	bset	IMM (31),d5
12:	lsrl	IMM (1),d4
#endif
3:
#ifndef __mcoldfire__
	dbra	d2,4b
#else
	subql	IMM (1),d2
	bpl	4b
#endif
	movel	IMM (0),d2
	movel	d2,d3
	bra	Laddxf$4
5:
	movel	d6,d7
	movel	d5,d6
	movel	d4,d5
	movel	IMM (0),d4
#ifndef __mcoldfire__
	subw	IMM (32),d2
#else
	subl	IMM (32),d2
#endif
	bra	2b
6:
	movew	d6,d7
	swap	d7
	movew	d5,d6
	swap	d6
	movew	d4,d5
	swap	d5
	movew	IMM (0),d4
	swap	d4
#ifndef __mcoldfire__
	subw	IMM (16),d2
#else
	subl	IMM (16),d2
#endif
	bra	3b

9:
#ifndef __mcoldfire__
	exg	d4,d5
	movew	d4,d6
	subw	d5,d6		| keep d5 (largest exponent) in d4
	exg	d4,a2
	exg	d5,a3
#else
	movel	d5,d6
	movel	d4,d5
	movel	d6,d4
	subl	d5,d6
	movel	d4,a4
	movel	a2,d4
	movel	a4,a2
	movel	d5,a4
	movel	a3,d5
	movel	a4,a3
#endif
| if difference is too large we don't shift (actually, we can just exit)
#ifndef __mcoldfire__
	cmpw	IMM (LDBL_MANT_DIG),d6
#else
	cmpl	IMM (LDBL_MANT_DIG),d6
#endif
	bge	Laddxf$a$small
#ifndef __mcoldfire__
	cmpw	IMM (32),d6	| if difference >= 32, shift by longs
#else
	cmpl	IMM (32),d6	| if difference >= 32, shift by longs
#endif
	bge	5f
2:
#ifndef __mcoldfire__
	cmpw	IMM (16),d6	| if difference >= 16, shift by words
#else
	cmpl	IMM (16),d6	| if difference >= 16, shift by words
#endif
	bge	6f
	bra	3f		| enter dbra loop

4:
#ifndef __mcoldfire__
	lsrl	IMM (1),d0
	roxrl	IMM (1),d1
	roxrl	IMM (1),d2
	roxrl	IMM (1),d3
#else
	lsrl	IMM (1),d3
	btst	IMM (0),d2
	beq	10f
	bset	IMM (31),d3
10:	lsrl	IMM (1),d2
	btst	IMM (0),d1
	beq	11f
	bset	IMM (31),d2
11:	lsrl	IMM (1),d1
	btst	IMM (0),d0
	beq	12f
	bset	IMM (31),d1
12:	lsrl	IMM (1),d0
#endif
3:
#ifndef __mcoldfire__
	dbra	d6,4b
#else
	subql	IMM (1),d6
	bpl	4b
#endif
	movel	IMM (0),d7
	movel	d7,d6
	bra	Laddxf$4
5:
	movel	d2,d3
	movel	d1,d2
	movel	d0,d1
	movel	IMM (0),d0
#ifndef __mcoldfire__
	subw	IMM (32),d6
#else
	subl	IMM (32),d6
#endif
	bra	2b
6:
	movew	d2,d3
	swap	d3
	movew	d1,d2
	swap	d2
	movew	d0,d1
	swap	d1
	movew	IMM (0),d0
	swap	d0
#ifndef __mcoldfire__
	subw	IMM (16),d6
#else
	subl	IMM (16),d6
#endif
	bra	3b
Laddxf$3:
#ifndef __mcoldfire__
	exg	d4,a2
	exg	d5,a3
#else
	movel	d4,a4
	movel	a2,d4
	movel	a4,a2
	movel	d5,a4
	movel	a3,d5
	movel	a4,a3
#endif
Laddxf$4:
| Now we have the numbers in d0--d3 and d4--d7, the exponent in a2, and
| the signs in a0.

| Here we have to decide whether to add or subtract the numbers:
#ifndef __mcoldfire__
	exg	d7,a0		| get the signs
	exg	d6,a3		| a3 is free to be used
#else
	movel	d7,a4
	movel	a0,d7
	movel	a4,a0
	movel	d6,a4
	movel	a3,d6
	movel	a4,a3
#endif
	movel	d7,d6		|
	movew	IMM (0),d7	| get a's sign in d7
	swap	d6              |
	movew	IMM (0),d6	| and b's sign in d6
	eorl	d7,d6		| compare the signs
	bmi	Lsubxf$0	| if the signs are different we have
				| to subtract
#ifndef __mcoldfire__
	exg	d7,a0		| else we add the numbers
	exg	d6,a3		|
#else
	movel	d7,a4
	movel	a0,d7
	movel	a4,a0
	movel	d6,a4
	movel	a3,d6
	movel	a4,a3
#endif
	addl	d7,d3		|
	addxl	d6,d2		|
	addxl	d5,d1		|
	addxl	d4,d0           |

	movel	a2,d4		| return exponent to d4
	movel	a0,d7		|
	andl	IMM (0x80000000),d7 | d7 now has the sign

| Before rounding normalize so bit #LDBL_MANT_DIG is set (we will consider
| the case of denormalized numbers in the rounding routine itself).
| As in the addition (not in the subtraction!) we could have set
| one more bit we check this:
	btst	IMM (LDBL_MANT_DIG-1-32),d0
	beq	1f
#ifndef __mcoldfire__
	lsrl	IMM (1),d0
	roxrl	IMM (1),d1
	roxrl	IMM (1),d2
	roxrl	IMM (1),d3
	addw	IMM (1),d4
#else
	lsrl	IMM (1),d3
	btst	IMM (0),d2
	beq	10f
	bset	IMM (31),d3
10:	lsrl	IMM (1),d2
	btst	IMM (0),d1
	beq	11f
	bset	IMM (31),d2
11:	lsrl	IMM (1),d1
	btst	IMM (0),d0
	beq	12f
	bset	IMM (31),d1
12:	lsrl	IMM (1),d0
	addl	IMM (1),d4
#endif
1:
	PICLEA	SYM (_fpCCR),a0	| check the rounding mode
#ifdef __mcoldfire__
	clrl	d6
#endif
	movew	a0@(6),d6	| rounding mode in d6
	lea	pc@(Laddxf$5),a0 | to return from rounding routine
	beq	Lround$to$nearest
#ifndef __mcoldfire__
	cmpw	IMM (ROUND_TO_PLUS),d6
#else
	cmpl	IMM (ROUND_TO_PLUS),d6
#endif
	bhi	Lround$to$minus
	blt	Lround$to$zero
	bra	Lround$to$plus
Laddxf$5:
| Put back the exponent and check for overflow
	movel	d2,a4
#ifndef __mcoldfire__
	cmpw	IMM (X_MAX_EXP),d4	| is the exponent big?
#else
	cmpl	IMM (X_MAX_EXP),d4	| is the exponent big?
#endif
	bcc	1f
	bset	IMM (31),d0 | put hidden bit back
	swap	d4	| put exponent back into position
| Put back the numbers
	movel	d2,a4
	movel	d0,d1
	movel	d4,d0
	bra	Laddxf$ret
1:
	moveq	IMM (ADD),d5
	bra	Lx$overflow

Lsubxf$0:
| Here we do the subtraction.
#ifndef __mcoldfire__
	exg	d7,a0		| put sign back in a0
	exg	d6,a3		|
#else
	movel	d7,a4
	movel	a0,d7
	movel	a4,a0
	movel	d6,a4
	movel	a3,d6
	movel	a4,a3
#endif
	subl	d7,d3		|
	subxl	d6,d2		|
	subxl	d5,d1		|
	subxl	d4,d0		|
	beq	Laddxf$ret$1	| if zero just exit
	bpl	1f		| if positive skip the following
	movel	a0,d7		|
	bchg	IMM (31),d7	| change sign bit in d7
	movel	d7,a0		|
	negl	d3		|
	negxl	d2		|
	negxl	d1              | and negate result
	negxl	d0              |
1:
	movel	a2,d4		| return exponent to d4
	movel	a0,d7
	andl	IMM (0x80000000),d7 | isolate sign bit

| Before rounding normalize so bit #LDBL_MANT_DIG is set (we will consider
| the case of denormalized numbers in the rounding routine itself).
| As in the addition (not in the subtraction!) we could have set
| one more bit we check this:
	btst	IMM (LDBL_MANT_DIG-1-32),d0
	beq	1f
#ifndef __mcoldfire__
	lsrl	IMM (1),d0
	roxrl	IMM (1),d1
	roxrl	IMM (1),d2
	roxrl	IMM (1),d3
	addw	IMM (1),d4
#else
	lsrl	IMM (1),d3
	btst	IMM (0),d2
	beq	10f
	bset	IMM (31),d3
10:	lsrl	IMM (1),d2
	btst	IMM (0),d1
	beq	11f
	bset	IMM (31),d2
11:	lsrl	IMM (1),d1
	btst	IMM (0),d0
	beq	12f
	bset	IMM (31),d1
12:	lsrl	IMM (1),d0
	addl	IMM (1),d4
#endif
1:
	lea	pc@(Lsubxf$1),a0 | to return from rounding routine
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
Lsubxf$1:
| Put back the exponent and sign (we don't have overflow).
	bset	IMM (31),d0 | put hidden bit back
	swap	d4	| put exponent back into position
| Put back the numbers
	movel	d2,a4
	movel	d0,d1
	movel	d4,d0
	bra	Laddxf$ret

| If one of the numbers was too small (difference of exponents >=
| LDBL_MANT_DIG) we return the other (and now we don't have to
| check for finiteness or zero).
Laddxf$a$small:
	moveml a6@(20),d0-d1/a4
	bra Laddxf$retnorm

Laddxf$b$small:
	moveml a6@(8),d0-d1/a4
	bra Laddxf$retnorm

Laddxf$a$den:
	movel	d7,d4		| d7 contains 0x00200000
	bra	Laddxf$1

Laddxf$b$den:
	movel	d7,d5           | d7 contains 0x00200000
	notl	d6
	bra	Laddxf$2

Laddxf$b:
| Return b (if a is zero)
	movel	d2,d0
	movel	d3,d1
	movel	a5,d5
	bne	1f			| Check if b is -0
	tstl	d1
	bne	1f			| Check if b is -0
	cmpl	IMM (0x80000000),d0
	bne	1f
	andl	IMM (0x80000000),d7	| Use the sign of a
	clrl	d0
	bra	Laddxf$ret
Laddxf$a:
	moveml	a6@(8),d0-d1/d5
1:
	movel	d5,a4
	moveq	IMM (ADD),d5
| Check for NaN and +/-INFINITY.
	movel	d0,d7         		|
	andl	IMM (0x80000000),d7	|
	andl	IMM (0x7fff0000),d0		|
	cmpl	IMM (0x7fff0000),d0	|
	bge	2f			|
	movel	a4,d4           	| check for zero, since we don't
	orl		d0,d4		| want to return -0 by mistake
	orl		d1,d4
	bne	Laddxf$ret		| want to return -0 by mistake
	bclr	IMM (31),d7		|
	bra	Laddxf$ret		|
2:
	movel	a4,d0	| check for NaN (nonzero fraction)
	orl	d1,d0			|
	bne	Lx$inop         	|
	bra	Lx$infty		|

Laddxf$ret$1:
	movel	d0,a4
	movel	d0,d1

Laddxf$ret:
| Normal exit.
	orl	d7,d0		| put sign bit back
Laddxf$retnorm:
	PICLEA	SYM (_fpCCR),a0
	clrw	a0@
	moveml	d0-d1/a4,a1@
	movel	a1,d0
	moveml	sp@,d2-d7/a2-a5
	| XXX if frame pointer is ever removed, stack pointer must
	| be adjusted here.
	unlk	a6
	rts

Laddxf$ret$den:
| Return a denormalized number.
#ifndef __mcoldfire__
	lsrl	IMM (1),d0	| shift right once more
	roxrl	IMM (1),d1	|
#else
	lsrl	IMM (1),d1
	btst	IMM (0),d0
	beq	10f
	bset	IMM (31),d1
10:	lsrl	IMM (1),d0
#endif
	bra	Laddxf$ret

Laddxf$nf:
	moveq	IMM (ADD),d5
| This could be faster but it is not worth the effort, since it is not
| executed very often. We sacrifice speed for clarity here.
	movel	a6@(8),d0	| get the numbers back (remember that we
	movel	a6@(12),d1	| did some processing already)
	movel	a6@(16),d2	|
	movel	a6@(20),d3	|
	movel	IMM (INFINITY),d4 | useful constant (INFINITY)
	movel	d0,d7		| save sign bits
	movel	d2,d6		|
	bclr	IMM (31),d0	| clear sign bits
	bclr	IMM (31),d2	|
| We know that one of them is either NaN of +/-INFINITY
| Check for NaN (if either one is NaN return NaN)
	cmpl	d4,d0		| check first a (d0)
	bhi	Lx$inop		| if d0 > 0x7ff00000 or equal and
	bne	2f
	tstl	d1		| d1 > 0, a is NaN
	bne	Lx$inop		|
2:	cmpl	d4,d2		| check now b (d1)
	bhi	Lx$inop		|
	bne	3f
	tstl	d3		|
	bne	Lx$inop		|
3:
| Now comes the check for +/-INFINITY. We know that both are (maybe not
| finite) numbers, but we have to check if both are infinite whether we
| are adding or subtracting them.
	eorl	d7,d6		| to check sign bits
	bmi	1f
	andl	IMM (0x80000000),d7 | get (common) sign bit
	bra	Lx$infty
1:
| We know one (or both) are infinite, so we test for equality between the
| two numbers (if they are equal they have to be infinite both, so we
| return NaN).
	cmpl	d2,d0		| are both infinite?
	bne	1f		| if d0 <> d2 they are not equal
	cmpl	d3,d1		| if d0 == d2 test d3 and d1
	beq	Lx$inop		| if equal return NaN
1:
	andl	IMM (0x80000000),d7 | get a's sign bit
	cmpl	d4,d0		| test now for infinity
	beq	Lx$infty	| if a is INFINITY return with this sign
	bchg	IMM (31),d7	| else we know b is INFINITY and has
	bra	Lx$infty	| the opposite sign
