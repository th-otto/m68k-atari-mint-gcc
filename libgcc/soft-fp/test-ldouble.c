#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
#include <endian.h>
#include <stdint.h>
#include <errno.h>
#include "soft-fp.h"
#include "softfp-protos.h"

struct ieee854_long_double_struct
{
#if	__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	unsigned int signexp:16;
	unsigned int empty:16;
	uint32_t     mantissa0:32;
	uint32_t     mantissa1:32;
#else
	uint32_t mantissa1:32;
	uint32_t mantissa0:32;
	unsigned int signexp:16;
	unsigned int empty:16;
#endif
};

union ieee854_long_double
{
	struct ieee854_long_double_struct ieee;
	long double d;
};

struct test_data
{
	long double arg1;
	long double arg2;
	char op;
	long double expected;
};

static struct test_data const double_tests[] = {
#define OP2(a, op, b) { a, b, #op[0], a op b }
#define OP1(a, op, opc) { a, 0, #opc[0], op(a) }
#define TESTOPS(a, b) \
	OP2(a, +, b), \
	OP2(a, -, b), \
	OP2(a, *, b), \
	OP2(a, /, b), \
	OP1(a, -, ~)
#define TEST(a, b) \
	TESTOPS(a, b), \
	TESTOPS(b, a), \
	TESTOPS(-(a), -(b)), \
	TESTOPS(-(b), -(a))
	
	TEST(3.0L, 4.0L),
	TEST(3.0L, 3.0L),
	TEST(1.123456789L, 4.0L),
	TEST(1E38L, 4.0L),
	TEST(1E308L, 4.0L),
	TEST(1E4000L, 4.0L),
	TEST(1E-37L, 4.0L),
	TEST(1E-307L, 4.0L),
	TEST(1E-4000L, 4.0L),
	TEST(0.0, 0.0),
};


double x, y;
int a;
long double lx, ly;
int b;

int main(void)
{
	int i;
	int errors = 0;

	/* to link in the comparison functions from softfp, not from libgcc */
	a = x < y;
	b = lx < ly;

	for (i = 0; i < (int)(sizeof(double_tests) / sizeof(double_tests[0])); i++)
	{
		const struct test_data *lt = &double_tests[i];
		volatile union ieee854_long_double a, b, z, r1;
		long double r;
		
#define COPY(dst, src) dst.d = src
		
		COPY(a, lt->arg1);
		COPY(b, lt->arg2);
		switch (lt->op)
		{
#if 0
			case '+': r = lt->arg1 + lt->arg2; break;
			case '-': r = lt->arg1 - lt->arg2; break;
			case '*': r = lt->arg1 * lt->arg2; break;
			case '/': r = lt->arg1 / lt->arg2; break;
			case '~': r = -(lt->arg1); break;
#else
			case '+': r = __addxf3(lt->arg1, lt->arg2); break;
			case '-': r = __subxf3(lt->arg1, lt->arg2); break;
			case '*': r = __mulxf3(lt->arg1, lt->arg2); break;
			case '/': r = __divxf3(lt->arg1, lt->arg2); break;
			case '~': r = __negxf2(lt->arg1); break;
#endif
			default: abort();
		}
		COPY(z, lt->expected);
		COPY(r1, r);
		if (r1.ieee.signexp != z.ieee.signexp ||
			r1.ieee.mantissa0 != z.ieee.mantissa0 ||
			r1.ieee.mantissa1 != z.ieee.mantissa1)
		{
#define is_binop(op) (op) != '~'
			if (is_binop(lt->op))
				printf("BAD %Le %c %Le\n", a.d, lt->op, b.d);
			else
				printf("BAD -(%Le)\n", a.d);
			printf("arg1      %.20Le 0x%04x, 0x%08x, 0x%08x\n",
				a.d,
				a.ieee.signexp,
				a.ieee.mantissa0,
				a.ieee.mantissa1);
			if (is_binop(lt->op))
			printf("arg2      %.20Le 0x%04x, 0x%08x, 0x%08x\n",
				b.d,
				b.ieee.signexp,
				b.ieee.mantissa0,
				b.ieee.mantissa1);
			printf("expected  %.20Le 0x%04x, 0x%08x, 0x%08x\n",
				z.d,
				z.ieee.signexp,
				z.ieee.mantissa0,
				z.ieee.mantissa1);
			printf("got       %.20Le 0x%04x, 0x%08x, 0x%08x\n",
				r1.d,
				r1.ieee.signexp,
				r1.ieee.mantissa0,
				r1.ieee.mantissa1);
			errors++;
		} else
		{
			if (is_binop(lt->op))
				printf("OK %Le %c %Le\n", a.d, lt->op, b.d);
			else
				printf("OK -(%Le)\n", a.d);
		}
	}

	if (errors != 0)
	{
		fprintf(stderr, "got %d errors\n", errors);
		return 1;
	}
	printf("no errors\n");
	return 0;
}
