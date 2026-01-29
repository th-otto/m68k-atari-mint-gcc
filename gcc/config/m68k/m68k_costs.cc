/* M68k RTX cost functions.
   Copyright (C) 2024 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 3, or (at your option) any later
   version.

   GCC is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

/* This file implements unified RTX cost functions for M68K.
   Consolidates cost calculations for 68000/010, 68020, 68030, and 68040+
   into a single implementation with per-CPU cost tables.

   Speed optimization: cycle-based costs from CPU documentation
   Size optimization: extension word overhead in bytes  */

#define IN_TARGET_CODE 1

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "cfghooks.h"
#include "tree.h"
#include "rtl.h"
#include "tm_p.h"

/* CPU type for cost table selection */
enum m68k_cpu_cost_type {
  M68K_CPU_68000,
  M68K_CPU_68020,
  M68K_CPU_68040
};


/* Memory addressing mode indices */
enum {
  MEM_REG,       /* (An) or (An)+ - same cost */
  MEM_PRE_DEC,   /* -(An) */
  MEM_DISP,      /* d(An) */
  MEM_INDEX,     /* d(An,Xn) */
  MEM_ABS,       /* abs */
  MEM_DEFAULT    /* complex/unknown */
};

/* Cost table structure - unified for all CPUs */
struct m68k_cost_table {
  /* CPU type - used only for selecting what to look up */
  enum m68k_cpu_cost_type cpu;
  int cost_scale;

  /* CALL costs: [reg, disp, abs, fallback] */
  int8_t call[4];

  /* CONST_INT costs: [moveq, word, long] */
  int8_t const_int[3];

  /* Synthetic constant costs: [word, long] (moveq+op) */
  int8_t const_synth[2];
  bool const_use_synth;       /* use synthetic constants? */
  bool const_fallthrough;     /* return false for CONST? */

  /* Register costs: [opno0, opno1] */
  int8_t reg_cost[2];

  /* SUBREG/STRICT_LOW_PART cost */
  int8_t subreg_cost;

  /* MEM costs: [mode][opno] */
  int8_t mem[6][2];
  int8_t dreg_penalty;        /* penalty for Dn as address base */
  int8_t mem_long_add;        /* extra cost for long mode */
  int8_t mem_predec_src_add;  /* extra for PRE_DEC as source */

  /* Extensions: [sign, zero_word, zero_long, truncate] */
  int8_t extend[4];
  int8_t extend_op_add;       /* added to operand cost for extend */
  bool extend_recurse;        /* recurse into operand? */

  /* NOT/NEG costs: [word, long] for register, [word, long] add for mem */
  int8_t not_neg_reg[2];
  int8_t not_neg_mem_add[2];

  /* Division: [word, long] */
  int16_t div[2];
  int8_t div_size_divisor;    /* divisor for -Os (1 or 3) */

  /* Multiply: [word, long] base cost */
  int16_t mult[2];
  int8_t mult_const_base;     /* base for known-bits calculation */
  int8_t mult_per_bit;        /* cost per bit in multiplier */
  int8_t mult_per_bit_div;    /* divisor for per-bit (68040: 2, others: 1) */
  int8_t mult_size_divisor;   /* divisor for -Os */

  /* Shifts: base costs [word, long] */
  int8_t shift_base[2];
  int8_t shift_per_count;     /* cost per shift count (68000: 2, others: 0) */
  int8_t shift_var_add;       /* extra for variable shift */
  int8_t shift_mem;           /* memory operand shift */
  int8_t shift_large_add;     /* extra for shift > 8 */
  int8_t shift_speed_divisor; /* divisor for -Os */

  /* PLUS/MINUS costs */
  struct {
    int8_t reg_reg[2];        /* [word, long] reg + reg */
    int8_t reg_const[2];      /* [word, long] reg + quick const */
    int8_t reg_const_large[2];/* [word, long] reg + large const */
    int8_t lea_indexed;       /* lea n(ax,dy),az */
    int8_t lea_disp;          /* lea n(ax),ay */
    int8_t sym_add;           /* symbol reference add */
    int8_t op_add[2];         /* [word, long] final operation add */
    int8_t base_cost;         /* 68020+ base cost */
    int8_t lea_penalty;       /* penalty for indexed LEA in complex expr (68040) */
  } plus;

  /* AND/IOR/XOR costs */
  struct {
    int8_t reg_const[2];      /* [word, long] reg op const (AND special) */
    int8_t reg_const_other[2];/* [word, long] for IOR/XOR */
    int8_t mem_const_add[2];  /* [word, long] add for mem op const */
    int8_t reg_op_ea[2];      /* [word, long] reg = reg op ea */
    int8_t ea_op_reg[2];      /* [word, long] ea = ea op reg */
    int8_t op_add[2];         /* [word, long] general op add */
    int8_t xor_word_add;      /* extra for XOR in word mode */
    int8_t base_cost;         /* 68020+ style: base cost (0 = use patterns) */
  } logic;

  /* COMPARE costs */
  struct {
    int8_t reg_imm[2];        /* [word, long] cmp #imm,Dn */
    int8_t mem_imm_add[2];    /* [word, long] add for cmp #imm,ea */
    int8_t reg_ea_add[2];     /* [word, long] cmp ea,Dn add */
    int8_t ea_reg_add[2];     /* [word, long] cmp Dn,ea add */
    int8_t op_add[2];         /* [word, long] general add */
  } compare;

  /* SET costs */
  int8_t clr_penalty[2];      /* [word, long] 68000 CLR read-before-write */
  int8_t clr_predec_add;      /* extra for CLR -(An) */
  int8_t set_adjust;          /* adjustment after SET (-2 for 68020) */

  /* Bit field extract: [normal, single-bit] */
  int8_t extract[2];
  bool extract_supported;     /* return false if not supported? */

  /* Miscellaneous */
  int8_t if_then_else;
  int8_t fp_op;
  int8_t addr_ref[2];         /* [word, long] SYMBOL_REF, LABEL_REF */
  int8_t const_double[2];     /* [<=4 bytes, >4 bytes] */
  int8_t const_sym_off[2];    /* [word, long] CONST(symbol+offset) */
  int8_t const_other;
  int8_t pre_dec[2];          /* standalone PRE_DEC [opno] */
  int8_t cmp[3];              /* 68020+ compare: [reg_zero, reg_const, base] */
  int8_t alu_adj[2];          /* ALU adjustments: [reg_both, reg_one] */
  int8_t buscycle_cost;       /* minimum cost unit */
};

/* Cost table for 68000/68010 */
static const struct m68k_cost_table m68k_cost_68000 = {
  /* cpu */
  M68K_CPU_68000,
  /* cost_scale */
  4,

  /* call: [reg, disp, abs, fallback] */
  { 16, 18, 20, 22 },

  /* const_int: [moveq, word, long] */
  { 4, 8, 12 },

  /* const_synth: [word, long] */
  { 8, 10 },
  /* const_use_synth */ true,
  /* const_fallthrough */ true,

  /* reg_cost: [opno0, opno1] - 68000: source=0, dest=cost */
  { 0, 4 },

  /* subreg_cost - not used on 68000 (recurses) */
  0,

  /* mem[mode][opno] - 68000 timing rounded to bus cycles (4)
     -(An) costs 6 cycles (2 for decrement + 4 for access), rounded to 8 */
  {
    /* MEM_REG/(An)+ */ { 4, 4 },
    /* MEM_PRE_DEC */   { 8, 8 },
    /* MEM_DISP */      { 8, 8 },
    /* MEM_INDEX */     { 12, 12 },
    /* MEM_ABS */       { 12, 12 },
    /* MEM_DEFAULT */   { 8, 8 }
  },
  /* dreg_penalty */ 0,
  /* mem_long_add */ 4,
  /* mem_predec_src_add */ 0,

  /* extend: [sign, zero_word, zero_long, truncate] */
  { 8, 8, 8, 0 },
  /* extend_op_add */ 8,
  /* extend_recurse */ true,

  /* not_neg_reg: [word, long] */
  { 4, 6 },
  /* not_neg_mem_add: [word, long] */
  { 8, 12 },

  /* div: [word, long] */
  { 136, 410 },
  /* div_size_divisor */ 3,

  /* mult: [word, long] */
  { 50, 150 },
  /* mult_const_base */ 38,
  /* mult_per_bit */ 2,
  /* mult_per_bit_div */ 1,
  /* mult_size_divisor */ 3,

  /* shift_base: [word, long] */
  { 6, 8 },
  /* shift_per_count */ 2,
  /* shift_var_add */ 16,
  /* shift_mem */ 8,
  /* shift_large_add */ 0,
  /* shift_speed_divisor */ 3,

  /* plus costs */
  {
    /* reg_reg */ { 4, 8 },
    /* reg_const */ { 4, 8 },
    /* reg_const_large */ { 8, 16 },
    /* lea_indexed */ 12,
    /* lea_disp */ 8,
    /* sym_add */ 16,
    /* op_add */ { 4, 6 },
    /* base_cost */ 0,
    /* lea_penalty */ 0
  },

  /* logic costs (AND/IOR/XOR) */
  {
    /* reg_const: AND uses 14 for long, IOR/XOR use 16 */ { 8, 14 },
    /* reg_const_other */ { 8, 16 },
    /* mem_const_add */ { 12, 20 },
    /* reg_op_ea */ { 6, 4 },   /* word: 6 (XOR:8), long: 4 */
    /* ea_op_reg */ { 8, 12 },
    /* op_add */ { 6, 4 },      /* word: XOR=8, others=6; long: 4 */
    /* xor_word_add */ 2,
    /* base_cost */ 0           /* use pattern-specific costs */
  },

  /* compare costs */
  {
    /* reg_imm */ { 8, 14 },
    /* mem_imm_add */ { 12, 20 },
    /* reg_ea_add */ { 4, 6 },
    /* ea_reg_add */ { 8, 12 },
    /* op_add */ { 4, 6 }
  },

  /* clr_penalty */ { 4, 8 },
  /* clr_predec_add */ 2,
  /* set_adjust */ 0,

  /* extract: [normal, single-bit] */
  { 0, 2 },
  /* extract_supported */ false,

  /* if_then_else */ 10,
  /* fp_op */ 0,
  /* addr_ref */ { 12, 12 },
  /* const_double */ { 8, 12 },
  /* const_sym_off */ { 12, 12 },
  /* const_other */ 0,
  /* pre_dec */ { 2, 2 },
  /* cmp */ { 0, 8, 4 },
  /* alu_adj */ { 0, 0 },
  /* buscycle_cost */ 4
};

/* Cost table for 68020/68030 */
static const struct m68k_cost_table m68k_cost_68020 = {
  /* cpu */
  M68K_CPU_68020,
  /* cost_scale */
  1,

  /* call: [reg, disp, abs, fallback] */
  { 7, 9, 7, 13 },

  /* const_int: [moveq, word, long] */
  { 1, 2, 4 },

  /* const_synth: [word, long] - not used */
  { 2, 4 },
  /* const_use_synth */ false,
  /* const_fallthrough */ false,

  /* reg_cost: [opno0, opno1] - same for both */
  { 2, 2 },

  /* subreg_cost */
  2,

  /* mem[mode][opno] */
  {
    /* MEM_REG/(An)+ */ { 4, 5 },
    /* MEM_PRE_DEC */   { 5, 6 },
    /* MEM_DISP */      { 5, 7 },
    /* MEM_INDEX */     { 10, 12 },
    /* MEM_ABS */       { 9, 10 },
    /* MEM_DEFAULT */   { 13, 15 }
  },
  /* dreg_penalty */ 5,
  /* mem_long_add */ 0,
  /* mem_predec_src_add */ 0,

  /* extend: [sign, zero_word, zero_long, truncate] */
  { 4, 2, 4, 0 },
  /* extend_op_add */ 0,
  /* extend_recurse */ false,

  /* not_neg_reg: [word, long] */
  { 2, 2 },
  /* not_neg_mem_add: [word, long] */
  { 0, 0 },

  /* div: [word, long] */
  { 56, 90 },
  /* div_size_divisor */ 3,

  /* mult: [word, long] */
  { 28, 44 },
  /* mult_const_base */ 12,
  /* mult_per_bit */ 1,
  /* mult_per_bit_div */ 1,
  /* mult_size_divisor */ 3,

  /* shift_base: [word, long] */
  { 4, 4 },
  /* shift_per_count */ 0,
  /* shift_var_add */ 2,
  /* shift_mem */ 6,
  /* shift_large_add */ 6,
  /* shift_speed_divisor */ 1,

  /* plus costs */
  {
    /* reg_reg */ { 2, 2 },
    /* reg_const */ { 2, 2 },
    /* reg_const_large */ { 2, 2 },
    /* lea_indexed */ 0,
    /* lea_disp */ 0,
    /* sym_add */ 0,
    /* op_add */ { 0, 0 },
    /* base_cost */ 2,
    /* lea_penalty */ 0
  },

  /* logic costs (AND/IOR/XOR) */
  {
    /* reg_const */ { 2, 2 },
    /* reg_const_other */ { 2, 2 },
    /* mem_const_add */ { 0, 0 },
    /* reg_op_ea */ { 0, 0 },
    /* ea_op_reg */ { 0, 0 },
    /* op_add */ { 0, 0 },
    /* xor_word_add */ 0,
    /* base_cost */ 2           /* use general base_cost + alu_adj */
  },

  /* compare costs */
  {
    /* reg_imm */ { 1, 1 },
    /* mem_imm_add */ { 0, 0 },
    /* reg_ea_add */ { 2, 2 },
    /* ea_reg_add */ { 2, 2 },
    /* op_add */ { 2, 2 }
  },

  /* clr_penalty */ { 0, 0 },
  /* clr_predec_add */ 0,
  /* set_adjust */ -2,

  /* extract: [normal, single-bit] */
  { 10, 2 },
  /* extract_supported */ true,

  /* if_then_else */ 7,
  /* fp_op */ 3,
  /* addr_ref */ { 3, 5 },
  /* const_double */ { 4, 8 },
  /* const_sym_off */ { 4, 5 },
  /* const_other */ 7,
  /* pre_dec */ { 2, 0 },
  /* cmp */ { 0, 1, 2 },
  /* alu_adj */ { 4, 2 },
  /* buscycle_cost */ 2
};

/* Cost table for 68040 (also used for 68060 and ColdFire) */
static const struct m68k_cost_table m68k_cost_68040 = {
  /* cpu */
  M68K_CPU_68040,
  /* cost_scale */
  1,

  /* call: [reg, disp, abs, fallback] */
  { 6, 8, 6, 12 },

  /* const_int: [moveq, word, long] */
  { 0, 0, 0 },

  /* const_synth: [word, long] - not used */
  { 0, 0 },
  /* const_use_synth */ false,
  /* const_fallthrough */ false,

  /* reg_cost: [opno0, opno1] - same for both */
  { 2, 2 },

  /* subreg_cost */
  0,

  /* mem[mode][opno] */
  {
    /* MEM_REG/(An)+ */ { 2, 3 },
    /* MEM_PRE_DEC */   { 3, 3 },
    /* MEM_DISP */      { 4, 5 },
    /* MEM_INDEX */     { 7, 9 },
    /* MEM_ABS */       { 6, 7 },
    /* MEM_DEFAULT */   { 10, 12 }
  },
  /* dreg_penalty */ 4,
  /* mem_long_add */ 0,
  /* mem_predec_src_add */ 0,

  /* extend: [sign, zero_word, zero_long, truncate] */
  { 1, 1, 1, 0 },
  /* extend_op_add */ 0,
  /* extend_recurse */ false,

  /* not_neg_reg: [word, long] */
  { 1, 1 },
  /* not_neg_mem_add: [word, long] */
  { 0, 0 },

  /* div: [word, long] */
  { 27, 44 },
  /* div_size_divisor */ 3,

  /* mult: [word, long] */
  { 16, 20 },
  /* mult_const_base */ 4,
  /* mult_per_bit */ 1,
  /* mult_per_bit_div */ 2,
  /* mult_size_divisor */ 3,

  /* shift_base: [word, long] */
  { 2, 2 },
  /* shift_per_count */ 0,
  /* shift_var_add */ 1,
  /* shift_mem */ 4,
  /* shift_large_add */ 4,
  /* shift_speed_divisor */ 1,

  /* plus costs */
  {
    /* reg_reg */ { 2, 2 },
    /* reg_const */ { 2, 2 },
    /* reg_const_large */ { 2, 2 },
    /* lea_indexed */ 0,
    /* lea_disp */ 0,
    /* sym_add */ 0,
    /* op_add */ { 0, 0 },
    /* base_cost */ 2,
    /* lea_penalty */ 3         /* 68040 LEA penalty for indexed in complex expr */
  },

  /* logic costs (AND/IOR/XOR) */
  {
    /* reg_const */ { 2, 2 },
    /* reg_const_other */ { 2, 2 },
    /* mem_const_add */ { 0, 0 },
    /* reg_op_ea */ { 0, 0 },
    /* ea_op_reg */ { 0, 0 },
    /* op_add */ { 0, 0 },
    /* xor_word_add */ 0,
    /* base_cost */ 2           /* use general base_cost + alu_adj */
  },

  /* compare costs */
  {
    /* reg_imm */ { 1, 1 },
    /* mem_imm_add */ { 0, 0 },
    /* reg_ea_add */ { 2, 2 },
    /* ea_reg_add */ { 2, 2 },
    /* op_add */ { 2, 2 }
  },

  /* clr_penalty */ { 0, 0 },
  /* clr_predec_add */ 0,
  /* set_adjust */ 0,

  /* extract: [normal, single-bit] */
  { 4, 2 },
  /* extract_supported */ true,

  /* if_then_else */ 3,
  /* fp_op */ 2,
  /* addr_ref */ { 1, 1 },
  /* const_double */ { 1, 2 },
  /* const_sym_off */ { 3, 4 },
  /* const_other */ 5,
  /* pre_dec */ { 0, 0 },
  /* cmp */ { 0, 1, 2 },
  /* alu_adj */ { 0, 0 },
  /* buscycle_cost */ 1
};

/* Get the appropriate cost table for the current CPU */
static inline const struct m68k_cost_table *
get_cost_table (void)
{
  if (TUNE_68000_10)
    return &m68k_cost_68000;
  else if (m68k_tune == u68020 || m68k_tune == u68030)
    return &m68k_cost_68020;
  else
    return &m68k_cost_68040;
}

/* Calculate memory addressing cost for speed optimization */
static int
mem_cost_speed (rtx addr, const struct m68k_cost_table *costs, int opno)
{
  int code = GET_CODE (addr);
  int total;

  switch (code)
    {
    case REG:
      total = costs->mem[MEM_REG][opno];
      /* Data register as address base penalty (68020+) */
      if (costs->dreg_penalty && REGNO (addr) < 8)
	total += costs->dreg_penalty;
      return total;

    case POST_INC:
      return costs->mem[MEM_REG][opno];  /* POST_INC same as REG */

    case PRE_DEC:
      return costs->mem[MEM_PRE_DEC][opno];

    case SYMBOL_REF:
    case LABEL_REF:
      return costs->mem[MEM_ABS][opno];

    case PLUS:
      {
	rtx base = XEXP (addr, 0);
	rtx offset = XEXP (addr, 1);

	if (REG_P (base))
	  {
	    if (CONST_INT_P (offset) || SYMBOL_REF_P (offset))
	      {
		total = costs->mem[MEM_DISP][opno];
		/* Data register as address base penalty (68020+) */
		if (costs->dreg_penalty && REGNO (base) < 8)
		  total += costs->dreg_penalty;
		return total;
	      }
	    if (REG_P (offset))
	      return costs->mem[MEM_INDEX][opno];
	  }
	/* Check for (PLUS (PLUS reg reg) const) - indexed with displacement */
	if (GET_CODE (base) == PLUS)
	  return costs->mem[MEM_INDEX][opno];
      }
      break;

    case CONST_INT:
      return costs->mem[MEM_ABS][opno];

    default:
      break;
    }

  return costs->mem[MEM_DEFAULT][opno];
}

/* Forward declaration for recursive calls.  */
bool m68k_rtx_costs_impl (rtx, machine_mode, int, int, int *, bool);

/* Calculate raw multiply cost (before size divisor adjustment).
   Returns true if cost was calculated, false otherwise.
   Sets *is_shift to true if power-of-2 multiplication was converted to shift.
   The caller applies mult_size_divisor for -Os only when !*is_shift.  */
static bool
mul_cost (rtx x, machine_mode mode, const struct m68k_cost_table *costs,
	  int *total, bool *is_shift)
{
  rtx op0 = XEXP (x, 0);
  rtx op1 = XEXP (x, 1);
  int idx = GET_MODE_SIZE (mode) > 2 ? 1 : 0;

  *is_shift = false;

  if (CONST_INT_P (op1))
    {
      unsigned HOST_WIDE_INT val = INTVAL (op1);
      if ((HOST_WIDE_INT) val < 0)
	val = -val;

      /* Check for power of 2 - can use shift */
      if (val && (val & (val - 1)) == 0)
	{
	  int shift = 0;
	  unsigned HOST_WIDE_INT v = val;
	  while (v > 1)
	    {
	      v >>= 1;
	      shift++;
	    }
	  *total = costs->shift_base[idx] + costs->shift_per_count * shift;
	  *is_shift = true;
	  return true;
	}

      /* Count bits for multiply estimation */
      int bits = __builtin_popcount (val);

      if (costs->cpu == M68K_CPU_68000)
	{
	  /* 68000-style: microcoded multiply with variable timing */
	  if (GET_CODE (op0) == ZERO_EXTEND
	      || GET_CODE (op0) == SIGN_EXTEND)
	    {
	      *total = 0;
	      mode = HImode;
	      idx = 0;
	    }
	  else if (!m68k_rtx_costs_impl (op0, mode, MULT, 0, total, true))
	    return false;

	  if (GET_MODE_SIZE (mode) == 2 && INTVAL (op1) > 0)
	    *total += costs->mult_const_base + costs->mult_per_bit * bits;
	  else
	    *total += costs->mult[idx];
	  return true;
	}

      /* 68020+ with constant multiplier */
      if (REG_P (op0) || GET_CODE (op0) == ZERO_EXTEND)
	{
	  *total = costs->mult_const_base
		   + costs->mult_per_bit * bits / costs->mult_per_bit_div;
	  return true;
	}
    }

  if (costs->cpu == M68K_CPU_68000)
    {
      /* 68000-style: microcoded multiply */
      if (GET_CODE (op0) == ZERO_EXTEND
	  || GET_CODE (op0) == SIGN_EXTEND)
	{
	  *total = 0;
	  mode = HImode;
	  idx = 0;
	}
      else if (!m68k_rtx_costs_impl (op0, mode, MULT, 0, total, true))
	return false;

      *total += costs->mult[idx];
      return true;
    }

  *total = costs->mult[idx];
  return true;
}

/* Unified cost calculation - returns cycle-based costs.
   The 'speed' parameter is used selectively: for 68020+, speed is effectively
   ignored (unified costs).  For 68000/68010, speed affects MULT/DIV/shift
   costs where timing varies significantly with operand values.  */
static bool
m68k_rtx_costs_unified (rtx x, machine_mode mode, int outer_code, int opno,
			int *total, const struct m68k_cost_table *costs,
			bool speed)
{
  int code = GET_CODE (x);
  int total2 = 0;

  switch (code)
    {
    case CALL:
      {
	rtx addr = XEXP (x, 0);
	if (MEM_P (addr))
	  {
	    rtx target = XEXP (addr, 0);
	    if (REG_P (target) || GET_CODE (target) == PC)
	      {
		*total = costs->call[0];
		return true;
	      }
	    if (GET_CODE (target) == PLUS && REG_P (XEXP (target, 0)))
	      {
		*total = costs->call[1];
		return true;
	      }
	    if (SYMBOL_REF_P (target) || CONST_INT_P (target))
	      {
		*total = costs->call[2];
		return true;
	      }
	  }
	*total = costs->call[3];
	return true;
      }

    case NE:
    case EQ:
    case GE:
    case GT:
    case LE:
    case LT:
    case GEU:
    case GTU:
    case LEU:
    case LTU:
      /* Cost the operand being compared */
      return m68k_rtx_costs_impl (XEXP (x, 0), mode, code, 0, total, speed);

    case CONST_INT:
      {
	/* Use m68k_const_method to determine constant load cost.
	   Returns 0, 1, or 2 multiplied by buscycle_cost for consistency
	   across different CPUs.  */
	HOST_WIDE_INT val = INTVAL (x);
	int mult;
	switch (m68k_const_method (val))
	  {
	  case MOVQ:
	    /* Constants between -128 and 127 are cheap due to moveq.  */
	    mult = 0;
	    break;
	  case MVZ:
	  case MVS:
	  case NOTB:
	  case NOTW:
	  case NEGW:
	  case SWAP:
	    /* Constants easily generated by moveq + not.b/not.w/neg.w/swap.  */
	    mult = 1;
	    break;
	  case MOVL:
	  default:
	    mult = 2;
	    break;
	  }
	*total = mult * costs->buscycle_cost;
      }
      return true;

    case CONST_DOUBLE:
      *total = GET_MODE_SIZE (mode) > 4 ? costs->const_double[1]
					: costs->const_double[0];
      return true;

    case CONST:
      {
	rtx inner = XEXP (x, 0);
	if (GET_CODE (inner) == PLUS)
	  {
	    rtx sym = XEXP (inner, 0);
	    if (SYMBOL_REF_P (sym) || GET_CODE (sym) == LABEL_REF)
	      {
		*total = GET_MODE_SIZE (mode) > 2 ? costs->const_sym_off[1]
						  : costs->const_sym_off[0];
		return true;
	      }
	  }
	*total = costs->const_other;
	return !costs->const_fallthrough;
      }

    case SYMBOL_REF:
      *total = GET_MODE_SIZE (mode) > 2 ? costs->addr_ref[1]
					: costs->addr_ref[0];
      return true;

    case LABEL_REF:
      *total = GET_MODE_SIZE (mode) > 2 ? costs->addr_ref[1]
					: costs->addr_ref[0];
      return true;

    case POST_INC:
      *total = 0;
      return true;

    case PRE_DEC:
      *total = costs->pre_dec[opno];
      return true;

    case REG:
    case PC:
      *total = costs->reg_cost[opno != 0];
      return true;

    case SUBREG:
    case STRICT_LOW_PART:
      /* SUBREG is essentially free - just accessing part of a register.
	 Use subreg_cost from table (0 for all CPUs). */
      *total = costs->subreg_cost;
      return true;

    case TRUNCATE:
      /* Truncation is free on all m68k - just use lower bits. */
      *total = costs->extend[3];
      return true;

    case ZERO_EXTEND:
      if (costs->extend_recurse)
	{
	  /* 68000: no MVZ, needs AND instruction - recurse and add cost */
	  if (m68k_rtx_costs_impl (XEXP (x, 0), GET_MODE (XEXP (x, 0)),
				   code, 0, total, speed))
	    {
	      *total += costs->extend_op_add;
	      return true;
	    }
	  return false;
	}
      *total = GET_MODE_SIZE (mode) > 2 ? costs->extend[2] : costs->extend[1];
      return true;

    case SIGN_EXTEND:
      if (costs->extend_recurse)
	{
	  /* 68000: limited EXT instruction - recurse and add cost */
	  if (m68k_rtx_costs_impl (XEXP (x, 0), GET_MODE (XEXP (x, 0)),
				   code, 0, total, speed))
	    {
	      *total += costs->extend_op_add;
	      return true;
	    }
	  return false;
	}
      *total = costs->extend[0];
      return true;

    case ZERO_EXTRACT:
      if (outer_code == COMPARE
	  && CONST_INT_P (XEXP (x, 1))
	  && INTVAL (XEXP (x, 1)) == 1)
	{
	  /* Single-bit test (BTST) - available on all m68k.  */
	  *total = costs->extract[1];
	  return true;
	}
      /* Note: GCC does not generate ZERO_EXTRACT for word-aligned 16-bit
	 extractions.  It uses lshiftrt:SI by 16 instead (matched by
	 lshrsi_16 pattern).  ZERO_EXTRACT is only generated for non-aligned
	 bitfield access which requires 68020+ bitfield instructions.  */
      if (!costs->extract_supported)
	return false;
      *total = costs->extract[0];
      return true;

    case SIGN_EXTRACT:
      if (outer_code == COMPARE
	  && CONST_INT_P (XEXP (x, 1))
	  && INTVAL (XEXP (x, 1)) == 1)
	{
	  *total = costs->extract[1];
	  return true;
	}
      /* Note: GCC does not generate SIGN_EXTRACT for word-aligned 16-bit
	 extractions.  It uses ashiftrt:SI by 16 instead (matched by
	 ashrsi_16 pattern).  SIGN_EXTRACT is only generated for non-aligned
	 bitfield access which requires 68020+ bitfield instructions.  */
      if (!costs->extract_supported)
	return false;
      *total = costs->extract[0];
      return true;

    case NOT:
    case NEG:
      {
	int idx = GET_MODE_SIZE (mode) > 2;
	rtx op = XEXP (x, 0);
	if (REG_P (op))
	  {
	    *total = costs->not_neg_reg[idx];
	    return true;
	  }
	if (m68k_rtx_costs_impl (op, mode, code, 0, total, speed))
	  {
	    *total += costs->not_neg_mem_add[idx];
	    return true;
	  }
	return false;
      }

    case DIV:
    case MOD:
    case UDIV:
    case UMOD:
      {
	int idx = GET_MODE_SIZE (mode) > 2;
	int div_cost = costs->div[idx];

	if (costs->cpu == M68K_CPU_68000)
	  {
	    /* 68000: include operand cost (variable timing) */
	    rtx op = XEXP (x, 0);
	    if (!m68k_rtx_costs_impl (op, mode, code, 0, total, speed))
	      return false;
	  }
	else
	  *total = 0;

	if (!speed && costs->div_size_divisor > 1)
	  div_cost /= costs->div_size_divisor;

	*total += div_cost;
	return true;
      }

    case MEM:
      {
	rtx addr = XEXP (x, 0);
	*total = mem_cost_speed (addr, costs, opno);
	/* Add cost for long mode memory access (68000 16-bit bus) */
	if (costs->mem_long_add && mode != QImode && mode != HImode)
	  *total += costs->mem_long_add;
	/* Add cost for PRE_DEC source operand (68000 timing) */
	if (costs->mem_predec_src_add && opno && GET_CODE (addr) == PRE_DEC)
	  *total += costs->mem_predec_src_add;
	return true;
      }

    case SET:
      {
	rtx dst = XEXP (x, 0);
	rtx src = XEXP (x, 1);
	int idx = GET_MODE_SIZE (mode) > 2 ? 1 : 0;

	if (REG_P (dst))
	  {
	    if (m68k_rtx_costs_impl (src, mode, code, 1, total, speed))
	      return true;
	  }
	else if (m68k_rtx_costs_impl (dst, mode, code, 0, total, speed)
		 && m68k_rtx_costs_impl (src, mode, code, 1, &total2, speed))
	  {
	    *total += total2;

	    /* CLR penalty: read-before-write on memory (68000) */
	    if (costs->clr_penalty[idx]
		&& MEM_P (dst)
		&& CONST_INT_P (src)
		&& INTVAL (src) == 0)
	      {
		*total += costs->clr_penalty[idx];
		if (GET_CODE (XEXP (dst, 0)) == PRE_DEC)
		  *total += costs->clr_predec_add;
	      }

	    /* Set adjustment (68020: -2) */
	    *total += costs->set_adjust;

	    return true;
	  }
      }
      break;

    case PLUS:
    case MINUS:
      {
	rtx op0 = XEXP (x, 0);
	rtx op1 = XEXP (x, 1);
	int idx = GET_MODE_SIZE (mode) > 2;

	/* LEA optimization: lea n(ax,dy),az */
	if (costs->plus.lea_indexed
	    && GET_CODE (op0) == PLUS
	    && CONST_INT_P (op1)
	    && (unsigned) (INTVAL (op1) + 128) < 255
	    && REG_P (XEXP (op0, 0))
	    && REG_P (XEXP (op0, 1)))
	  {
	    *total = costs->plus.lea_indexed;
	    return true;
	  }

	/* lea n(ax),ay - address register with displacement */
	if (costs->plus.lea_disp
	    && REG_P (op0)
	    && REGNO (op0) >= 8
	    && REGNO (op0) < 16)
	  {
	    if (GET_CODE (op1) == CONST
		&& GET_CODE (XEXP (op1, 0)) == UNSPEC)
	      {
		*total = costs->plus.lea_disp;
		return true;
	      }
	    if (CONST_INT_P (op1)
		&& (unsigned) (INTVAL (op1) + 32768) < 65535)
	      {
		*total = costs->plus.lea_disp;
		return true;
	      }
	  }

	/* 68000: Address registers operate on 32 bits internally.
	   Use long costs for addq.w on An to guide IRA to prefer DATA_REGS. */
	int effective_idx = idx;
	if (costs->plus.reg_reg[0] != costs->plus.reg_reg[1]
	    && REG_P (op0)
	    && REGNO (op0) >= 8
	    && REGNO (op0) < 16
	    && GET_MODE_SIZE (mode) < 4)
	  effective_idx = 1;  /* Force long cost */

	/* add reg,reg */
	if (REG_P (op0) && REG_P (op1))
	  {
	    *total = costs->plus.reg_reg[effective_idx];
	    return true;
	  }

	if (CONST_INT_P (op1))
	  {
	    HOST_WIDE_INT val = INTVAL (op1);
	    if (REG_P (op0)
		&& ((val >= -128 && val <= 127)
		    || (REGNO (op0) >= 8
			&& REGNO (op0) < 16
			&& (unsigned) (val + 32768) < 65535)))
	      *total = costs->plus.reg_const[effective_idx];
	    else
	      *total = costs->plus.reg_const_large[effective_idx];
	    return true;
	  }

	if (costs->plus.sym_add
	    && (SYMBOL_REF_P (op1)
		|| (GET_CODE (op1) == CONST
		    && GET_CODE (XEXP (op1, 0)) == PLUS
		    && SYMBOL_REF_P (XEXP (XEXP (op1, 0), 0)))))
	  {
	    *total = costs->plus.sym_add;
	    return true;
	  }

	/* General case: cost both operands and add */
	if (m68k_rtx_costs_impl (op0, mode, code, 0, total, speed)
	    && m68k_rtx_costs_impl (op1, mode, code, 1, &total2, speed))
	  {
	    *total += total2;
	    if (costs->plus.base_cost)
	      {
		/* 68020+ style: base cost with ALU adjustments */
		*total += costs->plus.base_cost;
		if (REG_P (op0))
		  *total -= REG_P (op1) ? costs->alu_adj[0] : costs->alu_adj[1];
		/* LEA penalty for indexed addressing in complex expression */
		if (costs->plus.lea_penalty
		    && GET_CODE (op0) == PLUS
		    && REG_P (XEXP (op0, 1)))
		  *total += costs->plus.lea_penalty;
	      }
	    else
	      {
		/* 68000 style: add operation cost */
		*total += costs->plus.op_add[effective_idx];
	      }
	    return true;
	  }
      }
      break;

    case AND:
    case IOR:
    case XOR:
      {
	rtx op0 = XEXP (x, 0);
	rtx op1 = XEXP (x, 1);
	int idx = GET_MODE_SIZE (mode) > 2 ? 1 : 0;
	int xor_add = (code == XOR && idx == 0) ? costs->logic.xor_word_add : 0;

	/* Pattern-specific mode (base_cost == 0) or general mode */
	if (costs->logic.base_cost == 0)
	  {
	    /* Pattern-specific costs */
	    if (CONST_INT_P (op1))
	      {
		if (REG_P (op0))
		  {
		    *total = (code == AND)
			     ? costs->logic.reg_const[idx]
			     : costs->logic.reg_const_other[idx];
		    return true;
		  }
		if (m68k_rtx_costs_impl (op0, mode, code, 0, total, speed))
		  {
		    *total += costs->logic.mem_const_add[idx];
		    return true;
		  }
	      }
	    else if (REG_P (op0))
	      {
		if (m68k_rtx_costs_impl (op1, mode, code, 1, total, speed))
		  {
		    *total += costs->logic.reg_op_ea[idx] + xor_add;
		    return true;
		  }
	      }
	    else if (REG_P (op1))
	      {
		if (m68k_rtx_costs_impl (op0, mode, code, 0, total, speed))
		  {
		    *total += costs->logic.ea_op_reg[idx];
		    return true;
		  }
	      }

	    /* General fallback for pattern-specific mode */
	    if (m68k_rtx_costs_impl (op0, mode, code, 0, total, speed)
		&& m68k_rtx_costs_impl (op1, mode, code, 1, &total2, speed))
	      {
		*total += total2 + costs->logic.op_add[idx] + xor_add;
		return true;
	      }
	    break;
	  }

	/* General mode with base_cost */
	if (m68k_rtx_costs_impl (op0, mode, code, 0, total, speed)
	    && m68k_rtx_costs_impl (op1, mode, code, 1, &total2, speed))
	  {
	    *total += total2 + costs->logic.base_cost;
	    if (REG_P (op0))
	      *total -= REG_P (op1) ? costs->alu_adj[0] : costs->alu_adj[1];
	    return true;
	  }
      }
      break;

    case ASHIFT:
    case ASHIFTRT:
    case LSHIFTRT:
      {
	rtx op0 = XEXP (x, 0);
	rtx op1 = XEXP (x, 1);
	int idx = GET_MODE_SIZE (mode) > 2 ? 1 : 0;

	if (REG_P (op0))
	  {
	    int shift_cost = costs->shift_base[idx];
	    if (CONST_INT_P (op1))
	      shift_cost += costs->shift_per_count * INTVAL (op1);
	    else
	      shift_cost += costs->shift_var_add;
	    /* Apply speed divisor for -Os (68000 style) */
	    if (costs->shift_speed_divisor > 1 && !speed)
	      shift_cost /= costs->shift_speed_divisor;
	    *total = shift_cost;
	    return true;
	  }

	/* Memory operand */
	if (costs->shift_per_count)
	  {
	    /* No barrel shifter: recurse into operand */
	    if (m68k_rtx_costs_impl (op0, mode, code, 0, total, speed))
	      {
		int shift_cost = costs->shift_mem;
		if (costs->shift_speed_divisor > 1 && !speed)
		  shift_cost /= costs->shift_speed_divisor;
		*total += shift_cost;
		return true;
	      }
	    break;
	  }

	/* Barrel shifter: direct memory shift */
	*total = costs->shift_mem;
	if (CONST_INT_P (op1) && INTVAL (op1) > 8)
	  *total += costs->shift_large_add;
	return true;
      }

    case MULT:
      {
	bool is_shift;
	if (!mul_cost (x, mode, costs, total, &is_shift))
	  break;
	if (!speed && !is_shift && costs->mult_size_divisor > 1)
	  *total /= costs->mult_size_divisor;
	return true;
      }

    case COMPARE:
      {
	rtx op0 = XEXP (x, 0);
	rtx op1 = XEXP (x, 1);
	int idx = GET_MODE_SIZE (mode) > 2 ? 1 : 0;

	/* 68000-style: pattern-specific costs (indicated by mem_imm_add > 0) */
	if (costs->compare.mem_imm_add[0] > 0)
	  {
	    if (CONST_INT_P (op1))
	      {
		if (REG_P (op0))
		  {
		    /* CMPI #imm,Dn */
		    *total = costs->compare.reg_imm[idx];
		    return true;
		  }
		if (m68k_rtx_costs_impl (op0, mode, code, 0, total, speed))
		  {
		    *total += costs->compare.mem_imm_add[idx];
		    return true;
		  }
	      }
	    else if (REG_P (op0) && REG_P (op1))
	      {
		/* CMP Rn,Rn - register to register compare
		   68000: CMP.W = 4 cycles, CMP.L = 6 cycles
		   No memory access, just the compare operation cost.  */
		*total = costs->compare.reg_ea_add[idx];
		return true;
	      }
	    else if (REG_P (op0))
	      {
		if (m68k_rtx_costs_impl (op1, mode, code, 1, total, speed))
		  {
		    /* CMP ea,Dn */
		    *total += costs->compare.reg_ea_add[idx];
		    return true;
		  }
	      }
	    else if (REG_P (op1))
	      {
		if (m68k_rtx_costs_impl (op0, mode, code, 0, total, speed))
		  {
		    *total += costs->compare.ea_reg_add[idx];
		    return true;
		  }
	      }

	    if (m68k_rtx_costs_impl (op0, mode, code, 0, total, speed)
		&& m68k_rtx_costs_impl (op1, mode, code, 1, &total2, speed))
	      {
		*total += total2 + costs->compare.op_add[idx];
		return true;
	      }
	    break;
	  }

	/* 68020+ style: simplified cmp[] based costs */
	if (REG_P (op0))
	  {
	    if (CONST_INT_P (op1))
	      {
		*total = INTVAL (op1) == 0 ? costs->cmp[0]
					   : costs->cmp[1];
		return true;
	      }
	    m68k_rtx_costs_impl (op1, mode, code, 1, total, speed);
	    *total += costs->cmp[2];
	    return true;
	  }
	if (m68k_rtx_costs_impl (op0, mode, code, 0, total, speed))
	  {
	    if (CONST_INT_P (op1) && INTVAL (op1) == 0)
	      return true;

	    if (m68k_rtx_costs_impl (op1, mode, code, 1, &total2, speed))
	      {
		*total += total2 + costs->cmp[2];
		return true;
	      }
	  }
      }
      break;

    case IF_THEN_ELSE:
      *total = costs->if_then_else;
      return true;

    case FLOAT:
    case FLOAT_TRUNCATE:
    case FIX:
      *total = costs->fp_op;
      return true;

    case ASM_OPERANDS:
    case ASM_INPUT:
      return false;

    default:
      break;
    }

  *total = costs->buscycle_cost;
  return true;
}

/* Main entry point for RTX cost calculation.
   Called from m68k_rtx_costs() in m68k.cc

   Uses unified cycle-based costs for both -O2 and -Os.  The 'speed' parameter
   is passed to the cost function for selective use: on 68000/68010, the
   MULT/DIV/shift timing varies significantly with operands, so speed affects
   those costs.  On 68020+, the speed parameter is effectively ignored since
   hardware multiply/divide have predictable timing.  */
bool
m68k_rtx_costs_impl (rtx x, machine_mode mode, int outer_code, int opno,
		     int *total, bool speed)
{
  const struct m68k_cost_table *costs = get_cost_table ();
  bool result = m68k_rtx_costs_unified (x, mode, outer_code, opno,
					total, costs, speed);
  if (result)
    {
        *total = COSTS_N_INSNS (*total) / costs->cost_scale;
    }
  return result;
}
