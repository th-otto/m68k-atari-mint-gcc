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

struct ieee754_float_struct
{
#if	__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	unsigned int signexp:9;
	uint32_t     mantissa:23;
#else
	uint32_t mantissa:23;
	unsigned int signexp:9;
#endif
};

union ieee754_float
{
	struct ieee754_float_struct ieee;
	float d;
};


struct test_data
{
	float arg1;
	float arg2;
	char op;
	float expected;
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
	
	TEST(3.0F, 4.0F),
	TEST(3.0F, 3.0F),
	TEST(1.123456789F, 4.0F),
	TEST(1E38F, 4.0F),
	TEST(1E-37F, 4.0F),
	TEST(0.0F, 0.0F),
};


double x, y;
int a;
long double lx, ly;
int b;

int main(void)
{
	int i;
	int errors = 0;
	int warnings = 0;

	/* to link in the comparison functions from softfp, not from libgcc */
	a = x < y;
	b = lx < ly;

	for (i = 0; i < (int)(sizeof(double_tests) / sizeof(double_tests[0])); i++)
	{
		const struct test_data *lt = &double_tests[i];
		volatile union ieee754_float a, b, z, r1;
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
			case '+': r = __addsf3(lt->arg1, lt->arg2); break;
			case '-': r = __subsf3(lt->arg1, lt->arg2); break;
			case '*': r = __mulsf3(lt->arg1, lt->arg2); break;
			case '/': r = __divsf3(lt->arg1, lt->arg2); break;
			case '~': r = __negsf2(lt->arg1); break;
#endif
			default: abort();
		}
		COPY(z, lt->expected);
		COPY(r1, r);
		if (r1.ieee.signexp != z.ieee.signexp ||
			(z.ieee.mantissa != r1.ieee.mantissa))
		{
#define is_binop(op) (op) != '~'
			int warning = r1.ieee.signexp == z.ieee.signexp && (z.ieee.mantissa - r1.ieee.mantissa) <= 1;
			const char *round = warning ? " (rounding)" : "";
			if (is_binop(lt->op))
				printf("BAD %e %c %e%s\n", a.d, lt->op, b.d, round);
			else
				printf("BAD -(%e)%s\n", a.d, round);
			printf("arg1      %.20e 0x%04x, 0x%08x\n",
				a.d,
				a.ieee.signexp,
				a.ieee.mantissa);
			if (is_binop(lt->op))
			printf("arg2      %.20e 0x%04x, 0x%08x\n",
				b.d,
				b.ieee.signexp,
				b.ieee.mantissa);
			printf("expected  %.20e 0x%04x, 0x%08x\n",
				z.d,
				z.ieee.signexp,
				z.ieee.mantissa);
			printf("got       %.20e 0x%04x, 0x%08x\n",
				r1.d,
				r1.ieee.signexp,
				r1.ieee.mantissa);
			if (warning)
				warnings++;
			else
				errors++;
		} else
		{
			if (is_binop(lt->op))
				printf("OK %e %c %e\n", a.d, lt->op, b.d);
			else
				printf("OK -(%e)\n", a.d);
		}
	}

	if (warnings != 0)
	{
		fprintf(stderr, "got %d warnings\n", warnings);
	}
	if (errors != 0)
	{
		fprintf(stderr, "got %d errors\n", errors);
		return 1;
	}
	printf("no errors\n");
	return 0;
}
