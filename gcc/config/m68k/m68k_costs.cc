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
#include "regs.h"
#include "df.h"
#include "insn-config.h"
#include "recog.h"
#include "tm_p.h"

/* From ira.h — avoid pulling in the full header and its emit-rtl.h
   dependency, which requires many additional includes.  */
extern bool ira_use_lra_p;

/* CPU type for cost table selection */
enum m68k_cpu_cost_type {
  M68K_CPU_68000,
  M68K_CPU_68020,
  M68K_CPU_68040,
  M68K_CPU_68060
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

/* Cost table structure - unified for all CPUs.

   All values are in actual hardware clock cycles for easy editing and
   verification against processor manuals.  The cost_scale field converts
   these cycle counts to GCC's internal cost units via:

       COSTS_N_INSNS(cycles) / cost_scale

   GCC defines COSTS_N_INSNS(1) = 4 as the cost of one fast instruction.
   cost_scale is set to the cycle count of a fast instruction on each CPU,
   so that a fast instruction always maps to COSTS_N_INSNS(1):

       68000:  add.w  =  4 cycles  -> cost_scale = 4  ->  4*4/4 =  4
       68020:  add.l  =  2 cycles  -> cost_scale = 2  ->  2*4/2 =  4
       68040:  add.l  =  1 cycle   -> cost_scale = 1  ->  1*4/1 =  4

   A slow instruction like mulu.w scales the same way:

       68000:  mulu.w = 50 cycles  -> cost_scale = 4  -> 50*4/4 =  50
       68020:  mulu.w = 28 cycles  -> cost_scale = 2  -> 28*4/2 =  56
       68040:  mulu.w = 16 cycles  -> cost_scale = 1  -> 16*4/1 =  64

   So mulu.w costs 12-16 fast instructions depending on CPU — GCC can
   compare this directly against a synth_mult decomposition of adds.

   Correct scaling matters because GCC's optimization passes compare
   target-reported costs against hardcoded COSTS_N_INSNS thresholds.
   For example, if-conversion (ifcvt.cc) uses COSTS_N_INSNS(2) as the
   baseline cost of a compare+branch when deciding whether to replace
   a branch with a conditional move.  With a wrong cost_scale, a simple
   add.l would appear to cost COSTS_N_INSNS(2) instead of COSTS_N_INSNS(1),
   making GCC overly conservative about replacing branches.
 */
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
    int8_t base_cost[2];      /* [word, long] base ALU cost for general fallback */
    int8_t lea_penalty;       /* penalty for indexed LEA in complex expr (68040) */
  } plus;

  /* AND/IOR/XOR costs */
  struct {
    int8_t reg_const[2];      /* [word, long] reg op const (AND special) */
    int8_t reg_const_other[2];/* [word, long] for IOR/XOR */
    int8_t mem_const_add[2];  /* [word, long] add for mem op const */
    int8_t reg_op_ea[2];      /* [word, long] reg = reg op ea */
    int8_t ea_op_reg[2];      /* [word, long] ea = ea op reg */
    int8_t xor_word_add;      /* extra for XOR in word mode */
    int8_t base_cost[2];      /* [word, long] base ALU cost for general fallback */
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
  /* cost_scale: moveq = 4 cycles */
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
  /* shift_speed_divisor */ 2,

  /* plus costs */
  {
    /* reg_reg */ { 4, 8 },
    /* reg_const */ { 4, 8 },
    /* reg_const_large: ALU cost without fiea (fiea added in code) */ { 4, 8 },
    /* lea_indexed */ 12,
    /* lea_disp */ 8,
    /* sym_add */ 16,
    /* base_cost */ { 4, 6 },
    /* lea_penalty */ 0
  },

  /* logic costs (AND/IOR/XOR) */
  {
    /* reg_const: ALU cost without fiea (fiea added in code) */ { 4, 6 },
    /* reg_const_other: IOR/XOR ALU cost without fiea */ { 4, 8 },
    /* mem_const_add: mem op cost without fiea */ { 8, 12 },
    /* reg_op_ea */ { 6, 4 },   /* word: 6 (XOR:8), long: 4 */
    /* ea_op_reg */ { 8, 12 },
    /* xor_word_add */ 2,
    /* base_cost */ { 6, 4 }
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

/* Cost table for 68020/68030.
   Values from MC68030 User's Manual Section 11.6, NCC (No-Cache) column.
   NCC represents stall-exposed timings without instruction cache benefit,
   appropriate for a conservative cost model.  68020 and 68030 have identical
   instruction timing; 68030 adds an on-chip data cache but NCC excludes it. */
static const struct m68k_cost_table m68k_cost_68020 = {
  /* cpu */
  M68K_CPU_68020,
  /* cost_scale: a fast 68020 instruction (add.l Dn,Dn) takes 2 cycles */
  2,

  /* call: [reg, disp, abs, fallback]
     JSR (An): JEA=2 + base=7 = 9; JSR (d16,An): 9; JSR xxx.L: 7 */
  { 9, 9, 7, 13 },

  /* const_int: [moveq, word, long] — UNUSED, see CONST_INT in cost function.
     NCC: MOVEQ = 2; MOVE.W #imm,Dn = 4; MOVE.L #imm,Dn = 6 */
  { 2, 4, 6 },

  /* const_synth: [word, long] - not used */
  { 2, 4 },
  /* const_use_synth */ false,
  /* const_fallthrough */ false,

  /* reg_cost: [opno0, opno1] - same for both */
  { 2, 2 },

  /* subreg_cost */
  2,

  /* mem[mode][opno] - 68030 NCC timings
     MOVE (An),Dn:      fea=3 + base=2 = 5; store: 4
     MOVE (An)+,Dn:     fea=3 + base=2 = 5 (same as (An))
     MOVE -(An),Dn:     fea=4 + base=2 = 6; store: 5
     MOVE (d16,An),Dn:  fea=4 + base=2 = 6; store: 5
     MOVE (d8,An,Xn),Dn: fea=6 + base=2 = 8; store: 7
     MOVE xxx.L,Dn:     fea=5 + base=2 = 7; store: 7
     Index costs kept at 10 to preserve 2x ratio vs simple modes —
     IVOPTS needs this differential to prefer separate pointer IVs
     with post-increment over fewer IVs with indexed addressing. */
  {
    /* MEM_REG/(An)+ */ { 5, 4 },
    /* MEM_PRE_DEC */   { 6, 5 },
    /* MEM_DISP */      { 6, 5 },
    /* MEM_INDEX */     { 10, 10 },
    /* MEM_ABS */       { 7, 7 },
    /* MEM_DEFAULT */   { 13, 15 }
  },
  /* dreg_penalty */ 5,
  /* mem_long_add */ 0,
  /* mem_predec_src_add */ 0,

  /* extend: [sign, zero_word, zero_long, truncate]
     EXT = 4 NCC */
  { 4, 2, 4, 0 },
  /* extend_op_add */ 0,
  /* extend_recurse */ false,

  /* not_neg_reg: [word, long]
     NEG Dn = 2 NCC */
  { 2, 2 },
  /* not_neg_mem_add: [word, long] */
  { 0, 0 },

  /* div: [word, long]
     DIVS.W = 56 NCC; DIVS.L = 90 NCC */
  { 56, 90 },
  /* div_size_divisor */ 3,

  /* mult: [word, long]
     MULS.W = 28 NCC; MULS.L = 44 NCC */
  { 28, 44 },
  /* mult_const_base */ 12,
  /* mult_per_bit */ 1,
  /* mult_per_bit_div */ 1,
  /* mult_size_divisor */ 3,

  /* shift_base: [word, long]
     LSd #imm,Dy = 4 NCC; ASR #imm = 4; ASL #imm = 6 → average 4 */
  { 4, 4 },
  /* shift_per_count */ 0,
  /* shift_var_add: LSd Dx,Dy = 6 vs LSd #,Dy = 4 → +2 */
  /* shift_var_add */ 2,
  /* shift_mem: LSd mem by 1 = 4 NCC */
  /* shift_mem */ 4,
  /* shift_large_add: constant shift count > 8 needs moveq + variable shift.
     LSd #imm(4) → moveq(2) + LSd Dx,Dy(6) = 8 NCC, delta +4 */
  /* shift_large_add */ 4,
  /* shift_speed_divisor */ 1,

  /* plus costs */
  {
    /* reg_reg: ADD Rn,Dn = 2 NCC */ { 2, 2 },
    /* reg_const: ADDQ = 2 NCC */ { 2, 2 },
    /* reg_const_large */ { 2, 2 },
    /* lea_indexed: LEA (d8,An,Xn) = 2 + fea 6 = 8 → 0 (base_cost handles) */
    /* lea_indexed */ 0,
    /* lea_disp */ 0,
    /* sym_add */ 0,
    /* base_cost */ { 2, 2 },
    /* lea_penalty */ 0
  },

  /* logic costs (AND/IOR/XOR)
     ANDI.L #imm,Dn: base=2 + fiea=4 = 6 NCC */
  {
    /* reg_const */ { 2, 2 },
    /* reg_const_other */ { 2, 2 },
    /* mem_const_add */ { 0, 0 },
    /* reg_op_ea */ { 0, 0 },
    /* ea_op_reg */ { 0, 0 },
    /* xor_word_add */ 0,
    /* base_cost */ { 2, 2 }
  },

  /* compare costs
     CMP Rn,Dn = 2 NCC; CMPA = 4 NCC */
  {
    /* reg_imm */ { 1, 1 },
    /* mem_imm_add */ { 0, 0 },
    /* reg_ea_add */ { 2, 2 },
    /* ea_reg_add */ { 2, 2 },
    /* op_add */ { 2, 2 }
  },

  /* clr_penalty: 68030 CLR is a write-only, no read-before-write */ { 0, 0 },
  /* clr_predec_add */ 0,
  /* set_adjust */ -2,

  /* extract: [normal, single-bit]
     BFEXTU Dn = 10 NCC; BTST Dn,Dn = 4 NCC */
  { 10, 4 },
  /* extract_supported */ true,

  /* if_then_else: Bcc taken = 8 NCC */
  /* if_then_else */ 8,
  /* fp_op */ 3,
  /* addr_ref: fea (xxx).W = 4 NCC; fea (xxx).L = 5 NCC */
  /* addr_ref */ { 4, 5 },
  /* const_double */ { 4, 8 },
  /* const_sym_off */ { 4, 5 },
  /* const_other */ 7,
  /* pre_dec */ { 2, 0 },
  /* cmp */ { 0, 1, 2 },
  /* alu_adj */ { 4, 2 },
  /* buscycle_cost */ 2
};

/* Cost table for 68040.
   Values from M68040 User's Manual Section 10.  Each entry is
   <ea> Calculate + Execute clocks, assuming cache hits and aligned accesses.
   The 68040 has a 4-stage integer pipeline: ea-calc → ea-fetch → execute →
   write-back.  Execute times are expressed as NL+M where N = lead time
   (absorbable stalls) and M = base time.  We use N+M as worst case. */
static const struct m68k_cost_table m68k_cost_68040 = {
  /* cpu */
  M68K_CPU_68040,
  /* cost_scale: add.l Dn,Dn = calc 1 + exec 1 = 2;
     but many common ops complete in 1 effective cycle due to pipelining */
  1,

  /* call: [reg, disp, abs, fallback]
     JSR (An): calc=1 + exec=1L+1 ≈ 2; RTS = calc=5 + exec=5
     JSR (d16,An): calc=2 + exec=1L+1 ≈ 3
     JSR xxx: calc=1 + exec=1 ≈ 2 */
  { 5, 6, 5, 10 },

  /* const_int: [moveq, word, long]
     MOVEQ = calc 1 + exec 1 = 2 → 0 scaled */
  { 0, 0, 0 },

  /* const_synth: [word, long] - not used */
  { 0, 0 },
  /* const_use_synth */ false,
  /* const_fallthrough */ false,

  /* reg_cost: [opno0, opno1] - same for both */
  { 2, 2 },

  /* subreg_cost */
  0,

  /* mem[mode][opno] - 68040 pipelined timings (cache hit)
     MOVE (An),Dn:      calc=1, exec=1 = 2
     MOVE (An)+,Dn:     calc=1, exec=1 = 2
     MOVE -(An),Dn:     calc=1, exec=1 = 2
     MOVE (d16,An),Dn:  calc=1, exec=1 = 2; store: calc=2, exec=1L+1 ≈ 3
     MOVE (d8,An,Xn),Dn: calc=3, exec=3 = 6; store: calc=3, exec=3 = 6
     MOVE xxx,Dn:       calc=1, exec=1 = 2; store: calc=1, exec=1 = 2 */
  {
    /* MEM_REG/(An)+ */ { 2, 2 },
    /* MEM_PRE_DEC */   { 2, 2 },
    /* MEM_DISP */      { 2, 3 },
    /* MEM_INDEX */     { 6, 6 },
    /* MEM_ABS */       { 2, 2 },
    /* MEM_DEFAULT */   { 10, 12 }
  },
  /* dreg_penalty */ 4,
  /* mem_long_add */ 0,
  /* mem_predec_src_add */ 0,

  /* extend: [sign, zero_word, zero_long, truncate]
     EXT.W = calc 1 + exec 2 = 3; EXT.L = calc 1 + exec 1 = 2 */
  { 2, 1, 2, 0 },
  /* extend_op_add */ 0,
  /* extend_recurse */ false,

  /* not_neg_reg: [word, long]
     NEG Dn = calc 1 + exec 1 = 2 → 1 scaled */
  { 1, 1 },
  /* not_neg_mem_add: [word, long] */
  { 0, 0 },

  /* div: [word, long]
     DIVS.W: calc=1, exec=23 = 24; DIVS.L: calc=1, exec=43 = 44 */
  { 24, 44 },
  /* div_size_divisor */ 3,

  /* mult: [word, long]
     MULS.W: calc=1, exec=8L+1 ≈ 9; MULS.L: calc=1, exec=8L+5 ≈ 14 */
  { 9, 14 },
  /* mult_const_base */ 4,
  /* mult_per_bit */ 1,
  /* mult_per_bit_div */ 2,
  /* mult_size_divisor */ 3,

  /* shift_base: [word, long]
     ASR/LSR #imm = calc 1 + exec 2 = 3; ASL #imm = calc 1 + exec 3 = 4
     → average 2 for the common case */
  { 2, 2 },
  /* shift_per_count */ 0,
  /* shift_var_add: register count adds +1 */
  /* shift_var_add */ 1,
  /* shift_mem: LSd mem = calc 1 + exec 2 = 3 */
  /* shift_mem */ 3,
  /* shift_large_add */ 4,
  /* shift_speed_divisor */ 1,

  /* plus costs */
  {
    /* reg_reg: ADD Dn,Dn = calc 1 + exec 1 = 2 */ { 2, 2 },
    /* reg_const: ADDQ = calc 1 + exec 1 = 2 */ { 2, 2 },
    /* reg_const_large */ { 2, 2 },
    /* lea_indexed */ 0,
    /* lea_disp */ 0,
    /* sym_add */ 0,
    /* base_cost */ { 2, 2 },
    /* lea_penalty */ 3         /* 68040 LEA penalty for indexed in complex expr */
  },

  /* logic costs (AND/IOR/XOR)
     ANDI Dn = calc 1 + exec 1 = 2 */
  {
    /* reg_const */ { 2, 2 },
    /* reg_const_other */ { 2, 2 },
    /* mem_const_add */ { 0, 0 },
    /* reg_op_ea */ { 0, 0 },
    /* ea_op_reg */ { 0, 0 },
    /* xor_word_add */ 0,
    /* base_cost */ { 2, 2 }
  },

  /* compare costs
     CMP Dn,Dn = calc 1 + exec 1 = 2 */
  {
    /* reg_imm */ { 1, 1 },
    /* mem_imm_add */ { 0, 0 },
    /* reg_ea_add */ { 2, 2 },
    /* ea_reg_add */ { 2, 2 },
    /* op_add */ { 2, 2 }
  },

  /* clr_penalty: 68040 CLR is write-only */ { 0, 0 },
  /* clr_predec_add */ 0,
  /* set_adjust */ 0,

  /* extract: [normal, single-bit]
     BFEXTU Dn = calc 1 + exec 4 = 5 */
  { 5, 2 },
  /* extract_supported */ true,

  /* if_then_else: Bcc taken = calc 2 + exec 2 = 4 */
  /* if_then_else */ 4,
  /* fp_op */ 2,
  /* addr_ref */ { 1, 1 },
  /* const_double */ { 1, 2 },
  /* const_sym_off */ { 3, 4 },
  /* const_other */ 5,
  /* pre_dec */ { 0, 0 },
  /* cmp */ { 0, 1, 2 },
  /* alu_adj */ { 2, 1 },
  /* buscycle_cost */ 1
};

/* Cost table for 68060 (also used for ColdFire).
   Values from MC68060 User's Manual Section 10.  The 68060 is superscalar
   with dual OEPs and branch prediction.  Timings assume single dispatch
   (no superscalar pairing) per the manual's convention.
   ColdFire V4/V4e shares this table: both have pipelined single-cycle ALU,
   fast 2-3 cycle multiply, and single-cycle shifts. */
static const struct m68k_cost_table m68k_cost_68060 = {
  /* cpu */
  M68K_CPU_68060,
  /* cost_scale: ADD Dn,Dn = 1(0/0) → 1 cycle */
  1,

  /* call: [reg, disp, abs, fallback]
     JSR = 3(0/1) unpredicted backward; RTS = 7(1/0)
     predicted: JSR = 1(0/1), so avg ≈ 2 + RTS overhead */
  { 5, 4, 4, 8 },

  /* const_int: [moveq, word, long]
     MOVEQ = 1(0/0); all immediates pipelined → effectively free */
  { 0, 0, 0 },

  /* const_synth: [word, long] - not used */
  { 0, 0 },
  /* const_use_synth */ false,
  /* const_fallthrough */ false,

  /* reg_cost: [opno0, opno1] - same for both */
  { 2, 2 },

  /* subreg_cost */
  0,

  /* mem[mode][opno] - 68060 timings (cache hit, single dispatch)
     Raw timings: all simple modes = 1(1/0) load, 1(0/1) store.
     (bd,An,Xi*SF) adds 1 EA calc cycle.  Memory indirect adds 3(1/0).

     However, superscalar dispatch constraints make indexed addressing
     effectively more expensive: sOEP Test 3 prevents (bd,An,Xi*SF)
     from dispatching to the secondary OEP.  In a loop body, simple
     modes (An)/(An)+/(d16,An) can pair with another instruction via
     sOEP, while indexed modes force pOEP-only — halving throughput.
     Indexed costs are inflated to reflect this real-world penalty and
     to preserve IVOPTS preference for separate pointer IVs with
     post-increment over fewer IVs with indexed addressing. */
  {
    /* MEM_REG/(An)+ */ { 2, 2 },
    /* MEM_PRE_DEC */   { 2, 2 },
    /* MEM_DISP */      { 2, 2 },
    /* MEM_INDEX */     { 5, 6 },  /* superscalar penalty: pOEP-only */
    /* MEM_ABS */       { 2, 2 },
    /* MEM_DEFAULT */   { 7, 8 }   /* memory indirect: +3(1/0) pointer fetch */
  },
  /* dreg_penalty */ 3,
  /* mem_long_add */ 0,
  /* mem_predec_src_add */ 0,

  /* extend: [sign, zero_word, zero_long, truncate]
     EXT = 1(0/0); EXTB.L = 1(0/0) */
  { 1, 1, 1, 0 },
  /* extend_op_add */ 0,
  /* extend_recurse */ false,

  /* not_neg_reg: [word, long]
     NEG = 1(0/0) */
  { 1, 1 },
  /* not_neg_mem_add: [word, long] */
  { 0, 0 },

  /* div: [word, long]
     DIVS.W = ≤22(1/0); DIVS.L = 38(1/0) */
  { 22, 38 },
  /* div_size_divisor */ 3,

  /* mult: [word, long]
     MULS.W = 2(1/0); MULS.L = 2(1/0) */
  { 2, 2 },
  /* mult_const_base */ 2,
  /* mult_per_bit */ 0,       /* constant time, no per-bit component */
  /* mult_per_bit_div */ 1,
  /* mult_size_divisor */ 1,

  /* shift_base: [word, long]
     ASL/ASR/LSL/LSR #imm = 1(0/0) */
  { 1, 1 },
  /* shift_per_count */ 0,    /* count does not affect timing */
  /* shift_var_add */ 0,      /* register count = same cost */
  /* shift_mem: memory shift = 1(1/1) */
  /* shift_mem */ 2,
  /* shift_large_add */ 0,
  /* shift_speed_divisor */ 1,

  /* plus costs */
  {
    /* reg_reg: ADD Dn,Dn = 1(0/0) → 2 scaled */ { 2, 2 },
    /* reg_const: ADDQ = 1(0/0) */ { 2, 2 },
    /* reg_const_large */ { 2, 2 },
    /* lea_indexed */ 0,
    /* lea_disp */ 0,
    /* sym_add */ 0,
    /* base_cost */ { 2, 2 },
    /* lea_penalty */ 0         /* 68060 LEA is pOEP|sOEP, no penalty */
  },

  /* logic costs (AND/IOR/XOR)
     ANDI Dn = 1(0/0) */
  {
    /* reg_const */ { 2, 2 },
    /* reg_const_other */ { 2, 2 },
    /* mem_const_add */ { 0, 0 },
    /* reg_op_ea */ { 0, 0 },
    /* ea_op_reg */ { 0, 0 },
    /* xor_word_add */ 0,
    /* base_cost */ { 2, 2 }
  },

  /* compare costs
     CMP = 1(1/0) */
  {
    /* reg_imm */ { 1, 1 },
    /* mem_imm_add */ { 0, 0 },
    /* reg_ea_add */ { 2, 2 },
    /* ea_reg_add */ { 2, 2 },
    /* op_add */ { 2, 2 }
  },

  /* clr_penalty: CLR is write-only on 68060 */ { 0, 0 },
  /* clr_predec_add */ 0,
  /* set_adjust */ 0,

  /* extract: [normal, single-bit]
     BFEXTU Dn = 6(0/0); BFEXTS Dn = 6(0/0) */
  { 6, 2 },
  /* extract_supported */ true,

  /* if_then_else: Bcc backward taken = 3(0/0) unpredicted;
     predicted correct = 0(0/0).  Use 3 as conservative estimate. */
  /* if_then_else */ 3,
  /* fp_op */ 2,
  /* addr_ref */ { 1, 1 },
  /* const_double */ { 1, 2 },
  /* const_sym_off */ { 2, 3 },
  /* const_other */ 4,
  /* pre_dec */ { 0, 0 },
  /* cmp */ { 0, 1, 2 },
  /* alu_adj */ { 2, 1 },
  /* buscycle_cost */ 1
};

/* Get the appropriate cost table for the current CPU.
   68000/010:            m68k_cost_68000
   68020/030:            m68k_cost_68020 (68030 NCC timings)
   68040:                m68k_cost_68040 (68040 pipelined timings)
   68060/ColdFire/other: m68k_cost_68060 (superscalar timings) */
static inline const struct m68k_cost_table *
get_cost_table (void)
{
  if (TUNE_68000_10)
    return &m68k_cost_68000;
  else if (m68k_tune == u68020 || m68k_tune == u68030)
    return &m68k_cost_68020;
  else if (TUNE_68040)
    return &m68k_cost_68040;
  else
    return &m68k_cost_68060;
}

/* Calculate memory addressing cost for speed optimization.
   Uses m68k_decompose_address to classify the addressing mode, which
   correctly handles SIGN_EXTEND, MULT, and ASHIFT index forms that
   the previous ad-hoc matching missed.  */
static int
mem_cost_speed (rtx addr, machine_mode mode,
		const struct m68k_cost_table *costs, int opno)
{
  struct m68k_address address;
  int total;

  if (!m68k_decompose_address (mode, addr, false, &address))
    return costs->mem[MEM_DEFAULT][opno];

  if (address.code == PRE_DEC)
    return costs->mem[MEM_PRE_DEC][opno];

  if (address.code == POST_INC)
    return costs->mem[MEM_REG][opno];

  if (address.index)
    return costs->mem[MEM_INDEX][opno];

  if (address.base && address.offset)
    {
      total = costs->mem[MEM_DISP][opno];
      if (costs->dreg_penalty && DATA_REGNO_P (REGNO (address.base)))
	total += costs->dreg_penalty;
      return total;
    }

  if (address.base)
    {
      total = costs->mem[MEM_REG][opno];
      if (costs->dreg_penalty && DATA_REGNO_P (REGNO (address.base)))
	total += costs->dreg_penalty;
      return total;
    }

  /* Absolute address or symbolic constant.  */
  return costs->mem[MEM_ABS][opno];
}

/* Forward declaration for recursive calls.  Internal callers must use
   m68k_rtx_costs_unified (raw costs) rather than m68k_rtx_costs_impl
   (which applies COSTS_N_INSNS scaling), to avoid double-scaling.  */
static bool m68k_rtx_costs_unified (rtx, machine_mode, int, int,
				    int *, const struct m68k_cost_table *,
				    bool);

/* Operation context for immediate constant costing.

   On m68k, the cost of using an immediate constant depends on the instruction:
   some have "quick" encodings where the constant is part of the opcode word
   (no extension words needed), while others always require extension words
   with their associated bus cycle overhead (fiea).

   OP_SET:     Move/load context.  MOVEQ encodes -128..127 in the opcode.
	       Other values use synthesis (moveq+not, swap) or MOVE.L #imm.
	       When DEST is MEM, synthesis is unavailable — always MOVL.
   OP_ADD_SUB: Add/subtract context.  ADDQ/SUBQ encode 1..8 in the opcode.
	       Other values need ADDI/SUBI with extension words (fiea).
   OP_COMPARE: Compare context.  CMP #0 uses TST (no extension words).
	       Other values need CMPI with extension words (fiea).
   OP_OTHER:   All other ALU ops (ANDI/ORI/EORI).  No quick form;
	       the immediate always needs extension words (fiea).  */

enum m68k_const_op {
  M68K_CONST_OP_SET,
  M68K_CONST_OP_ADD_SUB,
  M68K_CONST_OP_COMPARE,
  M68K_CONST_OP_OTHER
};

/* Return the raw NCC cost of a CONST_INT immediate in the given operation
   context.  MODE determines the extension word size for fiea costing:
   word (<=2 bytes) = 1 bus cycle, long (>2 bytes) = 2 bus cycles.
   DEST is used for OP_SET to check whether register-only synthesis
   (moveq+not, swap, etc.) is available — MEM destinations force MOVL.  */

static int
m68k_const_cost (HOST_WIDE_INT val, machine_mode mode,
		 enum m68k_const_op op,
		 const struct m68k_cost_table *costs,
		 rtx dest = NULL_RTX)
{
  switch (op)
    {
    case M68K_CONST_OP_SET:
      {
	/* MEM destinations cannot use register-only synthesis (moveq+not,
	   swap, etc.), so the constant must be a full immediate.  */
	int mult;
	switch (m68k_const_method (val, dest))
	  {
	  case MOVQ:
	    mult = 0;
	    break;
	  case MVZ: case MVS:
	  case NOTB: case NOTW: case NEGW: case SWAP:
	    mult = 1;
	    break;
	  case MOVL: default:
	    mult = 2;
	    break;
	  }
	return mult * costs->buscycle_cost;
      }

    case M68K_CONST_OP_ADD_SUB:
      /* ADDQ/SUBQ: 1..8 encoded in opcode, no extension words.  */
      if ((val >= 1 && val <= 8) || (val >= -8 && val <= -1))
	return 0;
      /* Larger values need ADDI/SUBI with extension words.  */
      goto fiea;

    case M68K_CONST_OP_COMPARE:
      /* CMP #0 uses TST: no immediate, no extension words.  */
      if (val == 0)
	return 0;
      /* Non-zero values need CMPI with extension words.  */
      goto fiea;

    case M68K_CONST_OP_OTHER:
    fiea:
      /* Immediate extension word cost (fiea).
	 Word-sized operation: 1 extension word = 1 bus cycle.
	 Long-sized operation: 2 extension words = 2 bus cycles.  */
      return (GET_MODE_SIZE (mode) <= 2 ? 1 : 2) * costs->buscycle_cost;
    }
  gcc_unreachable ();
}

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
      int shift = exact_log2 (val);
      if (shift >= 0)
	{
	  *total = costs->shift_base[idx] + costs->shift_per_count * shift;
	  *is_shift = true;
	  return true;
	}

      /* Count bits for multiply estimation */
      int bits = popcount_hwi (val);

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
	  else if (!m68k_rtx_costs_unified (op0, mode, MULT, 0, total,
					    costs, true))
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

  /* Widening multiply (mulu.w/muls.w): operand is ZERO_EXTEND or
     SIGN_EXTEND, so the hardware uses word multiply timing.
     On 68000, use the word multiply cost directly.
     On 68020+, this path handles the init_expmed probe (no constant
     known), so use the constant-multiply formula with average bit
     count (half the narrower mode width).  */
  if (GET_CODE (op0) == ZERO_EXTEND || GET_CODE (op0) == SIGN_EXTEND)
    {
      if (costs->cpu == M68K_CPU_68000)
	{
	  int narrow_idx
	    = GET_MODE_SIZE (GET_MODE (XEXP (op0, 0))) > 2 ? 1 : 0;
	  *total = costs->mult[narrow_idx];
	}
      else
	{
	  int avg_bits = GET_MODE_BITSIZE (GET_MODE (XEXP (op0, 0))) / 2;
	  *total = costs->mult_const_base
		   + costs->mult_per_bit * avg_bits / costs->mult_per_bit_div;
	}
      return true;
    }

  /* Non-widening, non-constant multiply.  On 68000 the microcoded
     multiply includes EA timing, so recursively cost op0.  On 68020+
     the EA is pipelined separately, so just use the multiply cost.  */
  if (costs->cpu == M68K_CPU_68000)
    {
      if (!m68k_rtx_costs_unified (op0, mode, MULT, 0, total,
				   costs, true))
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
      return m68k_rtx_costs_unified (XEXP (x, 0), mode, code, 0, total, costs, speed);

    case CONST_INT:
      /* Cost of materializing this constant into a register.
	 OP_SET accounts for MOVEQ (cost 0 for -128..127), synthesis
	 (moveq+not/swap), and full immediate load.

	 ALU handlers (PLUS, AND, COMPARE) catch CONST_INT operands
	 inline and call m68k_const_cost with the appropriate op type
	 for fiea costing — they never reach here.  This fallback is
	 only reached from general-case recursions and standalone
	 cost queries (e.g., IRA rematerialization decisions).  */
      *total = m68k_const_cost (INTVAL (x), mode, M68K_CONST_OP_SET, costs);
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
	    if (SYMBOL_REF_P (sym) || LABEL_REF_P (sym))
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
	  if (m68k_rtx_costs_unified (XEXP (x, 0), GET_MODE (XEXP (x, 0)),
				   code, 0, total, costs, speed))
	    {
	      *total += costs->extend_op_add;
	      return true;
	    }
	  return false;
	}
      {
	int ext_cost = GET_MODE_SIZE (mode) > 2
		       ? costs->extend[2] : costs->extend[1];
	/* 68020+: for MEM operands, recurse to include memory access cost.
	   Without this, zero_extend(mem) and zero_extend(reg) get the same
	   flat cost, causing combine to underestimate memory loads.  */
	if (MEM_P (XEXP (x, 0))
	    && m68k_rtx_costs_unified (XEXP (x, 0), GET_MODE (XEXP (x, 0)),
				       code, 0, total, costs, speed))
	  {
	    *total += ext_cost;
	    return true;
	  }
	*total = ext_cost;
	return true;
      }

    case SIGN_EXTEND:
      if (costs->extend_recurse)
	{
	  /* 68000: limited EXT instruction - recurse and add cost */
	  if (m68k_rtx_costs_unified (XEXP (x, 0), GET_MODE (XEXP (x, 0)),
				   code, 0, total, costs, speed))
	    {
	      *total += costs->extend_op_add;
	      return true;
	    }
	  return false;
	}
      /* 68020+: for MEM operands, recurse to include memory access cost. */
      if (MEM_P (XEXP (x, 0))
	  && m68k_rtx_costs_unified (XEXP (x, 0), GET_MODE (XEXP (x, 0)),
				     code, 0, total, costs, speed))
	{
	  *total += costs->extend[0];
	  return true;
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
	if (m68k_rtx_costs_unified (op, mode, code, 0, total, costs, speed))
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
	    if (!m68k_rtx_costs_unified (op, mode, code, 0, total, costs, speed))
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
	*total = mem_cost_speed (addr, mode, costs, opno);
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
	    if (m68k_rtx_costs_unified (src, mode, code, 1, total, costs, speed))
	      return true;
	  }
	else if (m68k_rtx_costs_unified (dst, mode, code, 0, total, costs, speed)
		 && m68k_rtx_costs_unified (src, mode, code, 1, &total2, costs, speed))
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
	    && ADDRESS_REGNO_P (REGNO (op0)))
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
	    && ADDRESS_REGNO_P (REGNO (op0))
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
		    || (ADDRESS_REGNO_P (REGNO (op0))
			&& (unsigned) (val + 32768) < 65535)))
	      *total = costs->plus.reg_const[effective_idx];
	    else
	      {
		*total = costs->plus.reg_const_large[effective_idx]
			 + m68k_const_cost (val, mode,
					    M68K_CONST_OP_ADD_SUB, costs);
	      }
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
	if (!m68k_rtx_costs_unified (op1, mode, code, 1, &total2, costs,
				     speed))
	  break;
	if (m68k_rtx_costs_unified (op0, mode, code, 0, total, costs, speed))
	  {
	    *total += total2 + costs->plus.base_cost[effective_idx];
	    if (REG_P (op0))
	      *total -= REG_P (op1) ? costs->alu_adj[0] : costs->alu_adj[1];
	    /* LEA penalty for indexed addressing in complex expression */
	    if (costs->plus.lea_penalty
		&& GET_CODE (op0) == PLUS
		&& REG_P (XEXP (op0, 1)))
	      *total += costs->plus.lea_penalty;
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

	if (CONST_INT_P (op1))
	  {
	    int const_cost = m68k_const_cost (INTVAL (op1), mode,
					      M68K_CONST_OP_OTHER, costs);
	    if (REG_P (op0))
	      {
		*total = ((code == AND)
			  ? costs->logic.reg_const[idx]
			  : costs->logic.reg_const_other[idx])
			 + const_cost;
		return true;
	      }
	    if (m68k_rtx_costs_unified (op0, mode, code, 0, total, costs,
					speed))
	      {
		*total += costs->logic.mem_const_add[idx] + const_cost;
		return true;
	      }
	  }
	else if (REG_P (op0))
	  {
	    if (m68k_rtx_costs_unified (op1, mode, code, 1, total, costs,
					speed))
	      {
		*total += costs->logic.reg_op_ea[idx] + xor_add;
		return true;
	      }
	  }
	else if (REG_P (op1))
	  {
	    if (m68k_rtx_costs_unified (op0, mode, code, 0, total, costs,
					speed))
	      {
		*total += costs->logic.ea_op_reg[idx];
		return true;
	      }
	  }

	/* General fallback: cost both operands + base ALU cost */
	if (CONST_INT_P (op1))
	  total2 = m68k_const_cost (INTVAL (op1), mode,
				    M68K_CONST_OP_OTHER, costs);
	else if (!m68k_rtx_costs_unified (op1, mode, code, 1, &total2, costs,
					  speed))
	  break;
	if (m68k_rtx_costs_unified (op0, mode, code, 0, total, costs, speed))
	  {
	    *total += total2 + costs->logic.base_cost[idx] + xor_add;
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

	if (REG_P (op0)
	    || (SUBREG_P (op0) && REG_P (SUBREG_REG (op0))))
	  {
	    int shift_cost = costs->shift_base[idx];
	    if (CONST_INT_P (op1))
	      {
		HOST_WIDE_INT count = INTVAL (op1);
		shift_cost += costs->shift_per_count * count;
		/* Shift counts > 8 need a moveq to load the count into
		   a register, since ASd/LSd #imm only supports 1-8.
		   Exception: shift by 16 in SI mode uses the swap
		   instruction (ashrsi_16/lshrsi_16/ashlsi_16 patterns),
		   not moveq + register shift.  */
		if (count > 8 && !(count == 16 && idx == 1))
		  shift_cost += costs->shift_large_add;
	      }
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
	    if (m68k_rtx_costs_unified (op0, mode, code, 0, total, costs, speed))
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
		if (m68k_rtx_costs_unified (op0, mode, code, 0, total, costs, speed))
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
		if (m68k_rtx_costs_unified (op1, mode, code, 1, total, costs, speed))
		  {
		    /* CMP ea,Dn */
		    *total += costs->compare.reg_ea_add[idx];
		    return true;
		  }
	      }
	    else if (REG_P (op1))
	      {
		if (m68k_rtx_costs_unified (op0, mode, code, 0, total, costs, speed))
		  {
		    *total += costs->compare.ea_reg_add[idx];
		    return true;
		  }
	      }

	    if (m68k_rtx_costs_unified (op0, mode, code, 0, total, costs, speed)
		&& m68k_rtx_costs_unified (op1, mode, code, 1, &total2, costs, speed))
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
	    m68k_rtx_costs_unified (op1, mode, code, 1, total, costs, speed);
	    *total += costs->cmp[2];
	    return true;
	  }
	if (m68k_rtx_costs_unified (op0, mode, code, 0, total, costs, speed))
	  {
	    if (CONST_INT_P (op1) && INTVAL (op1) == 0)
	      return true;

	    if (m68k_rtx_costs_unified (op1, mode, code, 1, &total2, costs, speed))
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

/* Return the scaled cost of loading CONST_INT value VAL into DEST.
   Returns costs in the same units as rtx_cost().  */

static int
m68k_const_set_cost (HOST_WIDE_INT val, rtx dest)
{
  const struct m68k_cost_table *costs = get_cost_table ();
  int raw = m68k_const_cost (val, SImode, M68K_CONST_OP_SET, costs, dest);
  return COSTS_N_INSNS (raw) / costs->cost_scale;
}

/* Implement TARGET_INSN_COST.

   The m68k cost table treats rtx_cost values as sub-expression costs:
   - MEM costs are EA-only (e.g. MEM_DISP=8 for d(An), not including the
     base 4-cycle instruction cost)
   - Compound operations (AND, OR, ADD with MEM operands) build up full
     instruction costs additively (e.g. AND(MEM,const) = MEM(8) +
     mem_const_add(12) = 20)

   pattern_cost() only evaluates SET_SRC, so stores like "move.b Dn,d(An)"
   get costed at just COSTS_N_INSNS(1)=4 instead of 12.  We fix both
   stores and loads by using max(src, dst) to capture the dominant EA cost,
   then adding COSTS_N_INSNS(1) as the base instruction cost for plain
   moves (where the source is a simple operand like MEM, REG, or CONST).
   Compound operations already embed the full cost in src_cost.  */

int
m68k_insn_cost_impl (rtx_insn *insn, bool speed)
{
  if (flag_m68k_insn_cost)
    {
      rtx set = single_set (insn);
      if (set)
	{
	  rtx src = SET_SRC (set);
	  rtx dst = SET_DEST (set);
	  machine_mode mode = GET_MODE (dst);
	  /* For CONST_INT sources, use dest-aware costing that accounts
	     for register-only synthesis being unavailable for MEM dests.  */
	  int src_cost;
	  if (CONST_INT_P (src))
	    src_cost = m68k_const_set_cost (INTVAL (src), dst);
	  else
	    src_cost = rtx_cost (src, mode, SET, 1, speed);
	  int dst_cost = rtx_cost (dst, mode, SET, 0, speed);
	  /* For constant-to-memory, the immediate extension words and the
	     memory EA both require bus cycles for instruction word fetches,
	     so their costs are additive rather than overlapping.  */
	  int cost;
	  if (CONST_INT_P (src) && MEM_P (dst) && src_cost > 0)
	    cost = src_cost + dst_cost;
	  else
	    cost = MAX (src_cost, dst_cost);
	  /* For plain move instructions (SET_SRC is MEM, REG, or CONST),
	     rtx_cost returns only the operand/EA cost.  Add COSTS_N_INSNS(1)
	     for the base instruction cycle cost when a MEM is involved,
	     since MEM EA costs don't include the base timing.
	     Compound operations (AND, OR, etc.) already build up full
	     instruction costs additively in their rtx_cost handlers.  */
	  if (OBJECT_P (src) && (MEM_P (src) || MEM_P (dst)))
	    cost += COSTS_N_INSNS (1);
	  /* Compound operation (PLUS, AND, etc.) writing to memory where no
	     source operand matches the destination.  This is NOT a
	     read-modify-write (like add.w #1,(a0)) and cannot be a single
	     m68k instruction.  Reload will insert a register copy, making
	     it 3 instructions: copy src->temp, op temp, store temp->mem.
	     Use additive costs instead of max to reflect the true cost.  */
	  else if (MEM_P (dst) && !OBJECT_P (src))
	    {
	      bool is_rmw = false;
	      if (BINARY_P (src))
		is_rmw = (rtx_equal_p (XEXP (src, 0), dst)
			  || rtx_equal_p (XEXP (src, 1), dst));
	      else if (UNARY_P (src))
		is_rmw = rtx_equal_p (XEXP (src, 0), dst);
	      if (!is_rmw)
		cost = src_cost + dst_cost + COSTS_N_INSNS (2);
	    }
	  return MAX (COSTS_N_INSNS (1), cost);
	}
    }
  return pattern_cost (PATTERN (insn), speed);
}

/* Return cost of address X based on addressing mode complexity.
   Uses m68k_rtx_costs_impl on a synthetic MEM to get addressing mode cost.  */

int
m68k_address_cost_impl (rtx x, machine_mode mode, bool speed)
{
  static class rtx_def mem;
  mem.code = MEM;
  mem.u.fld[0].rt_rtx = x;
  int total = 0;
  m68k_rtx_costs_impl (&mem, mode, SET, 0, &total, speed);
  return total;
}

/* Implement TARGET_REGISTER_MOVE_COST.  */

int
m68k_register_move_cost_impl (reg_class_t from, reg_class_t to)
{
  /* Moves to/from FP registers are expensive.  */
  if ((from == FP_REGS) != (to == FP_REGS))
    return 4;

  /* Penalize moves from data to address registers.  On m68k, moves to
     address registers don't set CC flags, representing a hidden cost
     that the default uniform cost=2 doesn't capture.  */
  if (flag_m68k_ira_promote
      && from == DATA_REGS && to == ADDR_REGS)
    return 3;

  return 2;
}

/* Implement TARGET_MEMORY_MOVE_COST.

   The default (4) makes memory nearly as cheap as a register move (2),
   which causes IRA to prefer spilling over callee-saved registers in
   tight allocation scenarios.  Register move cost 2 corresponds to
   move.l reg,reg = 4 cycles (2 cycles per unit).  Frame spill/reload
   costs:
     move.w d(sp),rN = 12 cycles → cost 6  (one bus access for data)
     move.l d(sp),rN = 16 cycles → cost 8  (two bus accesses on 16-bit bus)

   The long penalty only applies on a 16-bit bus: 68000 always, or
   020+ with -mshort (e.g., Falcon030 with 16-bit external bus).
   On a 32-bit bus (020+ without -mshort), long costs the same as
   word since data is fetched in one bus cycle.  */

int
m68k_memory_move_cost_impl (machine_mode mode, reg_class_t rclass, bool in)
{
  /* FP register spills go through memory and may need a temporary
     integer register, making them significantly more expensive.  */
  if (rclass == FP_REGS)
    return 12;

  /* Long on 16-bit bus: 68000 (always 16-bit) or 020+ with -mshort.  */
  if (GET_MODE_SIZE (mode) > 2
      && (!TARGET_68020 || TARGET_SHORT))
    return 8;

  return 6;
}

/* Implement TARGET_IV_COMPARE_COST for m68k.
   Return the per-iteration cost of the loop exit comparison instruction
   when an IV of the given TYPE is used.  When DOLOOP_P is true, the
   comparison is absorbed into dbra and costs nothing extra.

   On 68000, CMP.L and CMPA.L have the same timing (6 cycles).
   On 68020+, CMPA.L (4 NCC) is more expensive than CMP.L (2 NCC).
   Pointer-typed IVs map to address registers and require CMPA.  */

int
m68k_iv_compare_cost_impl (tree type, bool doloop_p, bool speed)
{
  if (!speed || doloop_p)
    return 0;

  const struct m68k_cost_table *costs = get_cost_table ();

  /* Base CMP.L Rn,Dn cost from the cost table.  */
  int cmp_cycles = costs->compare.reg_ea_add[1];

  /* CMPA penalty: pointer types use address registers, requiring the
     more expensive CMPA instruction on 68020+.  On 68000, CMP and CMPA
     have the same timing so no penalty applies.  */
  if (POINTER_TYPE_P (type) && costs->cpu != M68K_CPU_68000)
    cmp_cycles += 2;

  return COSTS_N_INSNS (cmp_cycles) / costs->cost_scale;
}

/* Implement SECONDARY_RELOAD_CLASS for m68k.  */

enum reg_class
m68k_secondary_reload_class_impl (enum reg_class rclass,
				  machine_mode mode, rtx x)
{
  int regno = true_regnum (x);

  /* If one operand of a movqi is an address register, the other
     operand must be a general register or constant.  Other types
     of operand must be reloaded through a data register.  */
  if (GET_MODE_SIZE (mode) == 1
      && reg_classes_intersect_p (rclass, ADDR_REGS)
      && !(INT_REGNO_P (regno) || CONSTANT_P (x)))
    return DATA_REGS;

  /* PC-relative addresses must be loaded into an address register first.  */
  if (TARGET_PCREL
      && !reg_class_subset_p (rclass, ADDR_REGS)
      && symbolic_operand (x, VOIDmode))
    return ADDR_REGS;

  return NO_REGS;
}

/* Implement TARGET_PREFERRED_RELOAD_CLASS_FOR_USE for m68k.
   Subsumes PREFERRED_RELOAD_CLASS with use-context awareness.

   For comparison operands, prefer data registers:
   - On 68020/030, cmp.l (2 NCC) is cheaper than cmpa.l (4+ NCC)
   - On all CPUs, d0/d1 are caller-saved: a comparison-only value
     stays in a caller-saved data register, avoiding save/restore
     overhead vs being placed in a callee-saved address register  */

reg_class_t
m68k_preferred_reload_class_for_use_impl (rtx x, reg_class_t rclass,
					  int src_use, int dst_use ATTRIBUTE_UNUSED)
{
  /* For comparison operands, prefer data registers.  */
  if ((src_use & REG_USE_COMPARE)
      && reg_class_subset_p (DATA_REGS, rclass))
    return DATA_REGS;

  /* If RCLASS might need a secondary reload, try restricting it to
     a class that doesn't.  */
  enum reg_class secondary_class
    = m68k_secondary_reload_class_impl ((enum reg_class) rclass, GET_MODE (x), x);
  if (secondary_class != NO_REGS
      && reg_class_subset_p (secondary_class, rclass))
    return (reg_class_t) secondary_class;

  /* Prefer to use moveq for in-range constants.  */
  if (GET_CODE (x) == CONST_INT
      && reg_class_subset_p (DATA_REGS, rclass)
      && IN_RANGE (INTVAL (x), -0x80, 0x7f))
    return DATA_REGS;

  if (GET_CODE (x) == CONST_DOUBLE
      && GET_MODE_CLASS (GET_MODE (x)) == MODE_FLOAT)
    {
      if (TARGET_HARD_FLOAT && reg_class_subset_p (FP_REGS, rclass))
	return FP_REGS;

      return NO_REGS;
    }

  return rclass;
}

/* Helper: check if pseudo REGNO appears only in RTX contexts where m68k
   address registers are sufficient.  PARENT_CODE is the RTX code of X's
   parent node (UNKNOWN at top level).

   Address registers handle: move, add, sub, compare, memory address.
   They cannot do: bitwise ops, shifts, multiply, divide, negate,
   sign/zero extend, strict_low_part writes.  */

static bool
regno_addr_safe_context_p (rtx x, unsigned int regno,
			   enum rtx_code parent_code)
{
  if (x == NULL_RTX)
    return true;

  enum rtx_code code = GET_CODE (x);

  /* Found our pseudo -- check if the parent context is addr-safe.  */
  if (code == REG && REGNO (x) == regno)
    {
      switch (parent_code)
	{
	/* Operations that require data registers on m68k.  */
	case AND: case IOR: case XOR: case NOT:
	case ASHIFT: case ASHIFTRT: case LSHIFTRT:
	case ROTATE: case ROTATERT:
	case MULT: case DIV: case MOD: case UDIV: case UMOD:
	case NEG: case ABS:
	case SIGN_EXTEND: case ZERO_EXTEND: case TRUNCATE:
	case STRICT_LOW_PART:
	case UNSPEC: case UNSPEC_VOLATILE:
	  return false;
	default:
	  return true;
	}
    }

  /* Special handling for SET: the destination is addr-safe only if
     the source operation is addr-reg compatible.  */
  if (code == SET)
    {
      rtx dest = SET_DEST (x);
      rtx src = SET_SRC (x);

      if (refers_to_regno_p (regno, dest))
	{
	  rtx d = dest;
	  /* strict_low_part write requires data register.  */
	  if (GET_CODE (d) == STRICT_LOW_PART)
	    {
	      d = XEXP (d, 0);
	      if (GET_CODE (d) == SUBREG)
		d = SUBREG_REG (d);
	      if (REG_P (d) && REGNO (d) == regno)
		return false;
	    }
	  if (GET_CODE (d) == SUBREG)
	    d = SUBREG_REG (d);
	  if (REG_P (d) && REGNO (d) == regno)
	    {
	      /* Pseudo IS the SET destination.  The source operation
		 determines whether this needs a data register.  */
	      switch (GET_CODE (src))
		{
		case AND: case IOR: case XOR: case NOT:
		case ASHIFT: case ASHIFTRT: case LSHIFTRT:
		case ROTATE: case ROTATERT:
		case MULT: case DIV: case MOD: case UDIV: case UMOD:
		case NEG: case ABS:
		case SIGN_EXTEND: case ZERO_EXTEND: case TRUNCATE:
		case UNSPEC: case UNSPEC_VOLATILE:
		  return false;
		default:
		  break;
		}
	    }
	  else
	    {
	      /* Pseudo is nested in dest (e.g., in MEM address).  */
	      if (!regno_addr_safe_context_p (dest, regno, SET))
		return false;
	    }
	}

      return regno_addr_safe_context_p (src, regno, SET);
    }

  /* Recurse into sub-expressions with current code as parent.  */
  const char *fmt = GET_RTX_FORMAT (code);
  for (int i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  if (!regno_addr_safe_context_p (XEXP (x, i), regno, code))
	    return false;
	}
      else if (fmt[i] == 'E')
	{
	  for (int j = XVECLEN (x, i) - 1; j >= 0; j--)
	    if (!regno_addr_safe_context_p (XVECEXP (x, i, j), regno, code))
	      return false;
	}
    }
  return true;
}

/* Return true if pseudo REGNO only participates in operations that
   m68k address registers can handle (move, add, sub, compare,
   memory addressing).  Scans all DEF and USE chain references.  */

static bool
pseudo_only_addr_ops_p (unsigned int regno)
{
  df_ref ref;

  for (ref = DF_REG_DEF_CHAIN (regno); ref; ref = DF_REF_NEXT_REG (ref))
    {
      rtx_insn *insn = DF_REF_INSN (ref);
      if (!insn || !INSN_P (insn))
	continue;
      if (!regno_addr_safe_context_p (PATTERN (insn), regno, UNKNOWN))
	return false;
    }

  for (ref = DF_REG_USE_CHAIN (regno); ref; ref = DF_REF_NEXT_REG (ref))
    {
      rtx_insn *insn = DF_REF_INSN (ref);
      if (!insn || !INSN_P (insn))
	continue;
      if (!regno_addr_safe_context_p (PATTERN (insn), regno, UNKNOWN))
	return false;
    }

  return true;
}

/* Return true if pseudo REGNO is derived from a pointer source.
   Checks if any DEF of REGNO is a simple copy (set reg reg) from
   a REG_POINTER pseudo.  This catches cases where GCC's middle-end
   loses the pointer attribute on a derived value.  */

static bool
pseudo_pointer_derived_p (unsigned int regno)
{
  df_ref ref;

  for (ref = DF_REG_DEF_CHAIN (regno); ref; ref = DF_REF_NEXT_REG (ref))
    {
      rtx_insn *insn = DF_REF_INSN (ref);
      if (!insn || !INSN_P (insn))
	continue;
      rtx pat = PATTERN (insn);
      if (GET_CODE (pat) != SET)
	continue;
      rtx dest = SET_DEST (pat);
      rtx src = SET_SRC (pat);
      /* Check for simple reg-to-reg copy: (set (reg REGNO) (reg SRC)).  */
      if (REG_P (dest) && REGNO (dest) == regno
	  && REG_P (src) && REGNO (src) >= FIRST_PSEUDO_REGISTER
	  && REG_POINTER (src))
	return true;
      /* Also check (set (reg REGNO) (plus (reg SRC) ...)) where SRC
	 is a pointer (pointer arithmetic).  */
      if (REG_P (dest) && REGNO (dest) == regno
	  && GET_CODE (src) == PLUS
	  && REG_P (XEXP (src, 0))
	  && REGNO (XEXP (src, 0)) >= FIRST_PSEUDO_REGISTER
	  && REG_POINTER (XEXP (src, 0)))
	return true;
    }
  return false;
}

/* Helper: Check if REGNO is used as a memory address in INSN.
   Recursively scans the RTX pattern looking for (mem (... regno ...)).  */

static bool
regno_used_as_mem_address_in_rtx (rtx x, unsigned int regno)
{
  if (x == NULL_RTX)
    return false;

  if (MEM_P (x))
    {
      /* Check if regno appears anywhere in the address.  */
      rtx addr = XEXP (x, 0);
      return refers_to_regno_p (regno, addr);
    }

  const char *fmt = GET_RTX_FORMAT (GET_CODE (x));
  for (int i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  if (regno_used_as_mem_address_in_rtx (XEXP (x, i), regno))
	    return true;
	}
      else if (fmt[i] == 'E')
	{
	  for (int j = XVECLEN (x, i) - 1; j >= 0; j--)
	    if (regno_used_as_mem_address_in_rtx (XVECEXP (x, i, j), regno))
	      return true;
	}
    }
  return false;
}

/* Check if pseudo REGNO is used as a memory address anywhere.  */

static bool
pseudo_used_as_mem_address_p (unsigned int regno)
{
  df_ref ref;

  for (ref = DF_REG_USE_CHAIN (regno); ref; ref = DF_REF_NEXT_REG (ref))
    {
      rtx_insn *insn = DF_REF_INSN (ref);
      if (insn && INSN_P (insn))
	{
	  if (regno_used_as_mem_address_in_rtx (PATTERN (insn), regno))
	    return true;
	}
    }
  return false;
}

/* Implement TARGET_IRA_CHANGE_PSEUDO_ALLOCNO_CLASS.
   Prevent IRA's allocno-class widening from defeating register-class
   preferences determined by cost analysis.

   DATA_REGS case: when costs say DATA_REGS is best but the allocno class
   was widened to GENERAL_REGS, narrow it back.  Otherwise IRA thread
   coalescing can pull the pseudo into an address register, forcing reload
   to insert a copy through a data register.

   ADDR_REGS case: when the pseudo is used as a memory base address, force
   ADDR_REGS.  There is no (Dn) addressing mode on any 68k CPU.  Pseudos
   used only for pointer arithmetic or comparisons can stay in data
   registers to avoid unnecessary callee-save overhead.  */

reg_class_t
m68k_ira_change_pseudo_allocno_class_impl (int regno,
					   reg_class_t allocno_class,
					   reg_class_t best_class)
{
  if (!flag_m68k_ira_promote)
    return allocno_class;

  /* If DATA_REGS is best but the class was widened to GENERAL_REGS,
     narrow it back.  This prevents thread coalescing from pulling
     data-register-preferring pseudos into address registers, which
     would force reload to insert a copy.

     Exception: on CPUs where cmp.l and cmpa.l cost the same (68000,
     68040, 68060), don't narrow pseudos that are direct copies of
     address hard registers.  DATA_REGS preference for these pseudos
     comes only from the comparison-use narrowing in
     preferred_reload_class_for_use, which has no cycle benefit on
     these CPUs.  Narrowing breaks IRA's preference hints from
     function arguments, causing suboptimal address register
     assignment for connected loop-pointer pseudos.  */
  if (best_class == DATA_REGS
      && allocno_class == GENERAL_REGS)
    {
      if (TARGET_68020 && !TARGET_68040)
	return DATA_REGS;

      /* Check if pseudo is a direct copy of an address hard register.  */
      df_ref def_ref = DF_REG_DEF_CHAIN (regno);
      if (def_ref && !DF_REF_NEXT_REG (def_ref))
	{
	  rtx_insn *insn = DF_REF_INSN (def_ref);
	  rtx set = single_set (insn);
	  if (set && REG_P (SET_SRC (set))
	      && HARD_REGISTER_P (SET_SRC (set))
	      && ADDRESS_REGNO_P (REGNO (SET_SRC (set))))
	    return allocno_class;
	}

      return DATA_REGS;
    }

  /* When costs are equal (best_class == GENERAL_REGS) or IRA prefers
     ADDR_REGS (best_class == ADDR_REGS) but the allocno class was
     widened, and the pseudo is pointer-typed AND actually used as a
     memory address base, prefer ADDR_REGS.

     The REG_POINTER check alone is insufficient: many pointer pseudos
     are only used in copies or arithmetic (e.g., saving a base pointer
     for later reuse).  Promoting these fills address registers and
     forces non-pointer pseudos into suboptimal data registers.
     The pseudo_used_as_mem_address_p guard ensures we only promote
     pseudos that genuinely need address registers for memory access.

     We also handle best_class == ADDR_REGS to handle IRA's two-pass
     cost computation: pass 0 may set best to ADDR_REGS (from this
     hook), then pass 1 widens allocno_class back to GENERAL_REGS
     but keeps best as ADDR_REGS.

     ColdFire is excluded from all ADDR_REGS promotion: its ISA
     constraints differ from classic 68k, and forcing ADDR_REGS can
     create unsatisfiable allocation conflicts that cause IRA/LRA to
     loop indefinitely.

     For LRA mode on classic 68k, also promote pointer-derived pseudos
     (e.g., loop induction variables computed from pointer values) that
     only use addr-reg-compatible operations.  This compensates for
     LRA's flat coloring keeping caller-save registers in the
     profitable set.  */
  if (!TARGET_COLDFIRE
      && (best_class == GENERAL_REGS || best_class == ADDR_REGS)
      && allocno_class == GENERAL_REGS
      && ((REG_POINTER (regno_reg_rtx[regno])
	   && pseudo_used_as_mem_address_p (regno))
	  || (ira_use_lra_p
	      && pseudo_pointer_derived_p (regno)
	      && pseudo_only_addr_ops_p (regno))))
    return ADDR_REGS;

  /* Only consider forcing ADDR_REGS if that's the best class.  */
  if (best_class != ADDR_REGS)
    return allocno_class;

  /* If allocno_class is already ADDR_REGS, no change needed.  */
  if (allocno_class == ADDR_REGS)
    return allocno_class;

  /* Check if this pseudo is actually used as a memory address.
     If so, force ADDR_REGS to avoid reload copies.  */
  if (!TARGET_COLDFIRE && pseudo_used_as_mem_address_p (regno))
    return ADDR_REGS;

  /* Pseudo is only used for arithmetic/comparisons - let IRA decide.  */
  return allocno_class;
}
