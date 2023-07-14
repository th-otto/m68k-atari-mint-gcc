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

struct ieee754_double_struct
{
#if	__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	unsigned int signexp:12;
	uint32_t     mantissa0:20;
	uint32_t     mantissa1:32;
#else
	uint32_t mantissa1:32;
	uint32_t mantissa0:20;
	unsigned int signexp:12;
#endif
};

union ieee754_double
{
	struct ieee754_double_struct ieee;
	double d;
};


struct test_data
{
	double arg1;
	double arg2;
	char op;
	double expected;
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
	
	TEST(3.0, 4.0),
	TEST(3.0, 3.0),
	TEST(1.123456789, 4.0),
	TEST(1E38, 4.0),
	TEST(1E308, 4.0),
	TEST(1E-37, 4.0),
	TEST(1E-307, 4.0),
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
		volatile union ieee754_double a, b, z, r1;
		double r;
		
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
			case '+': r = __adddf3(lt->arg1, lt->arg2); break;
			case '-': r = __subdf3(lt->arg1, lt->arg2); break;
			case '*': r = __muldf3(lt->arg1, lt->arg2); break;
			case '/': r = __divdf3(lt->arg1, lt->arg2); break;
			case '~': r = __negdf2(lt->arg1); break;
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
				printf("BAD %e %c %e\n", a.d, lt->op, b.d);
			else
				printf("BAD -(%e)\n", a.d);
			printf("arg1      %.20e 0x%04x, 0x%08x, 0x%08x\n",
				a.d,
				a.ieee.signexp,
				a.ieee.mantissa0,
				a.ieee.mantissa1);
			if (is_binop(lt->op))
			printf("arg2      %.20e 0x%04x, 0x%08x, 0x%08x\n",
				b.d,
				b.ieee.signexp,
				b.ieee.mantissa0,
				b.ieee.mantissa1);
			printf("expected  %.20e 0x%04x, 0x%08x, 0x%08x\n",
				z.d,
				z.ieee.signexp,
				z.ieee.mantissa0,
				z.ieee.mantissa1);
			printf("got       %.20e 0x%04x, 0x%08x, 0x%08x\n",
				r1.d,
				r1.ieee.signexp,
				r1.ieee.mantissa0,
				r1.ieee.mantissa1);
			errors++;
		} else
		{
			if (is_binop(lt->op))
				printf("OK %e %c %e\n", a.d, lt->op, b.d);
			else
				printf("OK -(%e)\n", a.d);
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
