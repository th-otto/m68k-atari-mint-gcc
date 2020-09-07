/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 56 "c-parse.y"

#include "config.h"
#include "system.h"
#include <setjmp.h>

#include "tree.h"
#include "input.h"
#include "c-lex.h"
#include "c-tree.h"
#include "flags.h"
#include "output.h"
#include "toplev.h"

#ifdef MULTIBYTE_CHARS
#include <locale.h>
#endif


/* Since parsers are distinct for each language, put the language string
   definition here.  */
char *language_string = "GNU C";

/* Like YYERROR but do call yyerror.  */
#define YYERROR1 { yyerror ("syntax error"); YYERROR; }

/* Cause the `yydebug' variable to be defined.  */
#define YYDEBUG 1

/* Line 371 of yacc.c  */
#line 97 "c-parse.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "c-parse.h".  */
#ifndef YY_YY_C_PARSE_H_INCLUDED
# define YY_YY_C_PARSE_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     TYPENAME = 259,
     SCSPEC = 260,
     TYPESPEC = 261,
     TYPE_QUAL = 262,
     CONSTANT = 263,
     STRING = 264,
     ELLIPSIS = 265,
     SIZEOF = 266,
     ENUM = 267,
     STRUCT = 268,
     UNION = 269,
     IF = 270,
     ELSE = 271,
     WHILE = 272,
     DO = 273,
     FOR = 274,
     SWITCH = 275,
     CASE = 276,
     DEFAULT = 277,
     BREAK = 278,
     CONTINUE = 279,
     RETURN_KEYWORD = 280,
     GOTO = 281,
     ASM_KEYWORD = 282,
     TYPEOF = 283,
     ALIGNOF = 284,
     ATTRIBUTE = 285,
     EXTENSION = 286,
     LABEL = 287,
     REALPART = 288,
     IMAGPART = 289,
     ASSIGN = 290,
     OROR = 291,
     ANDAND = 292,
     EQCOMPARE = 293,
     ARITHCOMPARE = 294,
     RSHIFT = 295,
     LSHIFT = 296,
     MINUSMINUS = 297,
     PLUSPLUS = 298,
     UNARY = 299,
     HYPERUNARY = 300,
     POINTSAT = 301,
     INTERFACE = 302,
     IMPLEMENTATION = 303,
     END = 304,
     SELECTOR = 305,
     DEFS = 306,
     ENCODE = 307,
     CLASSNAME = 308,
     PUBLIC = 309,
     PRIVATE = 310,
     PROTECTED = 311,
     PROTOCOL = 312,
     OBJECTNAME = 313,
     CLASS = 314,
     ALIAS = 315,
     OBJC_STRING = 316
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 87 "c-parse.y"
long itype; tree ttype; enum tree_code code;
	char *filename; int lineno; int ends_in_label; 

/* Line 387 of yacc.c  */
#line 205 "c-parse.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_C_PARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */
/* Line 390 of yacc.c  */
#line 204 "c-parse.y"

/* Number of statements (loosely speaking) and compound statements 
   seen so far.  */
static int stmt_count;
static int compstmt_count;
  
/* Input file and line number of the end of the body of last simple_if;
   used by the stmt-rule immediately after simple_if returns.  */
static char *if_stmt_file;
static int if_stmt_line;

/* List of types and structure classes of the current declaration.  */
static tree current_declspecs = NULL_TREE;
static tree prefix_attributes = NULL_TREE;

/* Stack of saved values of current_declspecs and prefix_attributes.  */
static tree declspec_stack;

/* 1 if we explained undeclared var errors.  */
static int undeclared_variable_notice;


/* Tell yyparse how to print a token's value, if yydebug is set.  */

#define YYPRINT(FILE,YYCHAR,YYLVAL) yyprint(FILE,YYCHAR,YYLVAL)
extern void yyprint			PROTO ((FILE *, int, YYSTYPE));

/* Line 390 of yacc.c  */
#line 261 "c-parse.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2490

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  158
/* YYNRULES -- Number of rules.  */
#define YYNRULES  405
/* YYNRULES -- Number of states.  */
#define YYNSTATES  692

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   316

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,     2,     2,     2,    52,    43,     2,
      58,    76,    50,    48,    81,    49,    57,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    38,    77,
       2,    35,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    83,    42,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    82,    41,    78,    79,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      36,    39,    40,    44,    45,    46,    47,    53,    54,    55,
      56,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     7,    10,    11,    15,    17,
      19,    25,    28,    32,    37,    42,    45,    48,    51,    54,
      56,    57,    58,    66,    71,    72,    73,    81,    86,    87,
      88,    95,    99,   101,   103,   105,   107,   109,   111,   113,
     115,   117,   119,   120,   122,   124,   128,   130,   133,   136,
     139,   142,   145,   150,   153,   158,   161,   164,   166,   168,
     170,   175,   176,   184,   186,   190,   194,   198,   202,   206,
     210,   214,   218,   222,   226,   230,   234,   235,   240,   241,
     246,   247,   248,   256,   257,   263,   267,   271,   273,   275,
     277,   281,   285,   286,   291,   296,   301,   305,   309,   312,
     315,   317,   320,   321,   323,   326,   330,   332,   334,   337,
     340,   345,   350,   353,   356,   360,   362,   364,   367,   370,
     371,   372,   377,   382,   386,   390,   393,   396,   399,   402,
     406,   407,   410,   413,   416,   419,   423,   424,   427,   430,
     432,   434,   437,   440,   442,   444,   447,   450,   453,   457,
     458,   461,   463,   465,   467,   472,   477,   479,   481,   483,
     485,   489,   491,   495,   496,   501,   502,   509,   513,   514,
     521,   525,   526,   528,   530,   533,   540,   542,   546,   547,
     549,   554,   561,   566,   568,   570,   572,   574,   576,   577,
     582,   584,   585,   588,   590,   594,   598,   601,   602,   607,
     609,   610,   615,   617,   619,   621,   624,   627,   633,   637,
     638,   639,   645,   646,   647,   653,   655,   657,   661,   665,
     670,   674,   678,   682,   684,   688,   693,   698,   702,   706,
     710,   712,   716,   720,   724,   729,   734,   738,   742,   744,
     746,   749,   751,   754,   756,   759,   760,   768,   774,   777,
     778,   786,   792,   795,   796,   805,   806,   814,   817,   818,
     820,   821,   823,   825,   828,   829,   833,   836,   840,   842,
     846,   848,   850,   853,   855,   859,   864,   871,   877,   879,
     883,   885,   887,   891,   894,   897,   898,   900,   902,   905,
     906,   909,   913,   917,   920,   924,   929,   933,   936,   940,
     943,   947,   949,   951,   954,   957,   958,   960,   963,   964,
     965,   967,   969,   972,   976,   978,   981,   983,   986,   993,
     999,  1005,  1008,  1011,  1016,  1017,  1022,  1023,  1024,  1028,
    1033,  1037,  1039,  1041,  1043,  1045,  1048,  1049,  1054,  1056,
    1060,  1061,  1062,  1070,  1076,  1079,  1080,  1081,  1082,  1095,
    1096,  1103,  1106,  1109,  1112,  1116,  1123,  1132,  1143,  1156,
    1160,  1165,  1167,  1169,  1170,  1177,  1181,  1187,  1190,  1194,
    1195,  1197,  1198,  1200,  1201,  1203,  1205,  1209,  1214,  1216,
    1220,  1221,  1224,  1227,  1228,  1233,  1236,  1237,  1239,  1241,
    1245,  1247,  1251,  1256,  1261,  1266,  1271,  1276,  1277,  1280,
    1282,  1285,  1287,  1291,  1293,  1297
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      85,     0,    -1,    -1,    86,    -1,    -1,    87,    89,    -1,
      -1,    86,    88,    89,    -1,    91,    -1,    90,    -1,    27,
      58,   100,    76,    77,    -1,   241,    89,    -1,   123,   137,
      77,    -1,   130,   123,   137,    77,    -1,   126,   123,   136,
      77,    -1,   130,    77,    -1,   126,    77,    -1,     1,    77,
      -1,     1,    78,    -1,    77,    -1,    -1,    -1,   126,   123,
     165,    92,   117,    93,   199,    -1,   126,   123,   165,     1,
      -1,    -1,    -1,   130,   123,   168,    94,   117,    95,   199,
      -1,   130,   123,   168,     1,    -1,    -1,    -1,   123,   168,
      96,   117,    97,   199,    -1,   123,   168,     1,    -1,     3,
      -1,     4,    -1,    43,    -1,    49,    -1,    48,    -1,    54,
      -1,    53,    -1,    79,    -1,    80,    -1,   102,    -1,    -1,
     102,    -1,   108,    -1,   102,    81,   108,    -1,   114,    -1,
      50,   106,    -1,   241,   106,    -1,    99,   106,    -1,    40,
      98,    -1,   104,   103,    -1,   104,    58,   186,    76,    -1,
     105,   103,    -1,   105,    58,   186,    76,    -1,    33,   106,
      -1,    34,   106,    -1,    11,    -1,    29,    -1,   103,    -1,
      58,   186,    76,   106,    -1,    -1,    58,   186,    76,    82,
     107,   151,    78,    -1,   106,    -1,   108,    48,   108,    -1,
     108,    49,   108,    -1,   108,    50,   108,    -1,   108,    51,
     108,    -1,   108,    52,   108,    -1,   108,    47,   108,    -1,
     108,    46,   108,    -1,   108,    45,   108,    -1,   108,    44,
     108,    -1,   108,    43,   108,    -1,   108,    41,   108,    -1,
     108,    42,   108,    -1,    -1,   108,    40,   109,   108,    -1,
      -1,   108,    39,   110,   108,    -1,    -1,    -1,   108,    37,
     111,   100,    38,   112,   108,    -1,    -1,   108,    37,   113,
      38,   108,    -1,   108,    35,   108,    -1,   108,    36,   108,
      -1,     3,    -1,     8,    -1,   116,    -1,    58,   100,    76,
      -1,    58,     1,    76,    -1,    -1,    58,   115,   201,    76,
      -1,   114,    58,   101,    76,    -1,   114,    59,   100,    83,
      -1,   114,    57,    98,    -1,   114,    60,    98,    -1,   114,
      54,    -1,   114,    53,    -1,     9,    -1,   116,     9,    -1,
      -1,   119,    -1,   119,    10,    -1,   206,   207,   120,    -1,
     118,    -1,   194,    -1,   119,   118,    -1,   118,   194,    -1,
     128,   123,   136,    77,    -1,   131,   123,   137,    77,    -1,
     128,    77,    -1,   131,    77,    -1,   206,   207,   125,    -1,
     121,    -1,   194,    -1,   122,   121,    -1,   121,   194,    -1,
      -1,    -1,   126,   123,   136,    77,    -1,   130,   123,   137,
      77,    -1,   126,   123,   159,    -1,   130,   123,   162,    -1,
     126,    77,    -1,   130,    77,    -1,   241,   125,    -1,   134,
     127,    -1,   130,   134,   127,    -1,    -1,   127,   135,    -1,
     127,     5,    -1,   127,   144,    -1,   134,   129,    -1,   131,
     134,   129,    -1,    -1,   129,   135,    -1,   129,     5,    -1,
     131,    -1,   144,    -1,   130,   131,    -1,   130,   144,    -1,
       7,    -1,     5,    -1,   131,     7,    -1,   131,     5,    -1,
     134,   133,    -1,   188,   134,   133,    -1,    -1,   133,   135,
      -1,     6,    -1,   172,    -1,     4,    -1,    28,    58,   100,
      76,    -1,    28,    58,   186,    76,    -1,     6,    -1,     7,
      -1,   172,    -1,   139,    -1,   136,    81,   139,    -1,   141,
      -1,   137,    81,   139,    -1,    -1,    27,    58,   116,    76,
      -1,    -1,   165,   138,   143,    35,   140,   149,    -1,   165,
     138,   143,    -1,    -1,   168,   138,   143,    35,   142,   149,
      -1,   168,   138,   143,    -1,    -1,   144,    -1,   145,    -1,
     144,   145,    -1,    30,    58,    58,   146,    76,    76,    -1,
     147,    -1,   146,    81,   147,    -1,    -1,   148,    -1,   148,
      58,     3,    76,    -1,   148,    58,     3,    81,   102,    76,
      -1,   148,    58,   101,    76,    -1,    98,    -1,     5,    -1,
       6,    -1,     7,    -1,   108,    -1,    -1,    82,   150,   151,
      78,    -1,     1,    -1,    -1,   152,   177,    -1,   153,    -1,
     152,    81,   153,    -1,   157,    35,   155,    -1,   158,   155,
      -1,    -1,    98,    38,   154,   155,    -1,   155,    -1,    -1,
      82,   156,   151,    78,    -1,   108,    -1,     1,    -1,   158,
      -1,   157,   158,    -1,    57,    98,    -1,    59,   108,    10,
     108,    83,    -1,    59,   108,    83,    -1,    -1,    -1,   165,
     160,   117,   161,   201,    -1,    -1,    -1,   168,   163,   117,
     164,   201,    -1,   166,    -1,   168,    -1,    58,   166,    76,
      -1,   166,    58,   236,    -1,   166,    59,   100,    83,    -1,
     166,    59,    83,    -1,    50,   189,   166,    -1,   144,   124,
     166,    -1,     4,    -1,   167,    58,   236,    -1,   167,    59,
      50,    83,    -1,   167,    59,   100,    83,    -1,   167,    59,
      83,    -1,    50,   189,   167,    -1,   144,   124,   167,    -1,
       4,    -1,   168,    58,   236,    -1,    58,   168,    76,    -1,
      50,   189,   168,    -1,   168,    59,    50,    83,    -1,   168,
      59,   100,    83,    -1,   168,    59,    83,    -1,   144,   124,
     168,    -1,     3,    -1,    13,    -1,    13,   144,    -1,    14,
      -1,    14,   144,    -1,    12,    -1,    12,   144,    -1,    -1,
     169,    98,    82,   173,   179,    78,   143,    -1,   169,    82,
     179,    78,   143,    -1,   169,    98,    -1,    -1,   170,    98,
      82,   174,   179,    78,   143,    -1,   170,    82,   179,    78,
     143,    -1,   170,    98,    -1,    -1,   171,    98,    82,   175,
     184,   178,    78,   143,    -1,    -1,   171,    82,   176,   184,
     178,    78,   143,    -1,   171,    98,    -1,    -1,    81,    -1,
      -1,    81,    -1,   180,    -1,   180,   181,    -1,    -1,   180,
     181,    77,    -1,   180,    77,    -1,   132,   123,   182,    -1,
     132,    -1,   188,   123,   182,    -1,   188,    -1,     1,    -1,
     241,   181,    -1,   183,    -1,   182,    81,   183,    -1,   206,
     207,   165,   143,    -1,   206,   207,   165,    38,   108,   143,
      -1,   206,   207,    38,   108,   143,    -1,   185,    -1,   184,
      81,   185,    -1,     1,    -1,    98,    -1,    98,    35,   108,
      -1,   132,   187,    -1,   188,   187,    -1,    -1,   190,    -1,
       7,    -1,   188,     7,    -1,    -1,   189,     7,    -1,    58,
     190,    76,    -1,    50,   189,   190,    -1,    50,   189,    -1,
     190,    58,   229,    -1,   190,    59,   100,    83,    -1,   190,
      59,    83,    -1,    58,   229,    -1,    59,   100,    83,    -1,
      59,    83,    -1,   144,   124,   190,    -1,   192,    -1,   209,
      -1,   192,   209,    -1,   192,   194,    -1,    -1,   191,    -1,
       1,    77,    -1,    -1,    -1,   197,    -1,   198,    -1,   197,
     198,    -1,    32,   240,    77,    -1,   201,    -1,     1,   201,
      -1,    82,    -1,   200,    78,    -1,   200,   195,   196,   122,
     193,    78,    -1,   200,   195,   196,     1,    78,    -1,   200,
     195,   196,   191,    78,    -1,   203,   208,    -1,   203,     1,
      -1,    15,    58,   100,    76,    -1,    -1,    18,   205,   208,
      17,    -1,    -1,    -1,   206,   207,   211,    -1,   206,   207,
     222,   208,    -1,   206,   207,   210,    -1,   211,    -1,   222,
      -1,   201,    -1,   219,    -1,   100,    77,    -1,    -1,   202,
      16,   212,   208,    -1,   202,    -1,   202,    16,     1,    -1,
      -1,    -1,    17,   213,    58,   100,    76,   214,   208,    -1,
     204,    58,   100,    76,    77,    -1,   204,     1,    -1,    -1,
      -1,    -1,    19,    58,   224,    77,   215,   224,    77,   216,
     224,    76,   217,   208,    -1,    -1,    20,    58,   100,    76,
     218,   208,    -1,    23,    77,    -1,    24,    77,    -1,    25,
      77,    -1,    25,   100,    77,    -1,    27,   223,    58,   100,
      76,    77,    -1,    27,   223,    58,   100,    38,   225,    76,
      77,    -1,    27,   223,    58,   100,    38,   225,    38,   225,
      76,    77,    -1,    27,   223,    58,   100,    38,   225,    38,
     225,    38,   228,    76,    77,    -1,    26,    98,    77,    -1,
      26,    50,   100,    77,    -1,    77,    -1,   220,    -1,    -1,
      19,    58,   114,    76,   221,   208,    -1,    21,   108,    38,
      -1,    21,   108,    10,   108,    38,    -1,    22,    38,    -1,
      98,    38,   143,    -1,    -1,     7,    -1,    -1,   100,    -1,
      -1,   226,    -1,   227,    -1,   226,    81,   227,    -1,     9,
      58,   100,    76,    -1,   116,    -1,   228,    81,   116,    -1,
      -1,   230,   231,    -1,   233,    76,    -1,    -1,   234,    77,
     232,   231,    -1,     1,    76,    -1,    -1,    10,    -1,   234,
      -1,   234,    81,    10,    -1,   235,    -1,   234,    81,   235,
      -1,   126,   123,   167,   143,    -1,   126,   123,   168,   143,
      -1,   126,   123,   187,   143,    -1,   130,   123,   168,   143,
      -1,   130,   123,   187,   143,    -1,    -1,   237,   238,    -1,
     231,    -1,   239,    76,    -1,     3,    -1,   239,    81,     3,
      -1,    98,    -1,   240,    81,    98,    -1,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   234,   234,   238,   253,   253,   254,   254,   258,   259,
     260,   268,   273,   283,   288,   293,   295,   297,   298,   299,
     306,   311,   305,   318,   324,   329,   323,   336,   342,   347,
     341,   354,   362,   363,   366,   368,   370,   372,   374,   376,
     378,   382,   388,   389,   393,   395,   400,   401,   404,   407,
     411,   439,   445,   448,   451,   454,   456,   461,   465,   469,
     470,   474,   473,   505,   506,   508,   510,   512,   514,   516,
     518,   520,   522,   524,   526,   528,   531,   530,   537,   536,
     543,   546,   542,   552,   551,   561,   569,   581,   679,   680,
     682,   688,   691,   690,   727,   729,   731,   735,   741,   743,
     749,   750,   755,   757,   758,   769,   774,   775,   776,   777,
     785,   790,   795,   798,   807,   812,   813,   814,   815,   823,
     834,   838,   843,   848,   853,   858,   860,   862,   872,   874,
     879,   880,   882,   887,   892,   894,   900,   901,   903,   916,
     918,   920,   922,   927,   930,   932,   935,   949,   951,   956,
     957,   965,   966,   967,   971,   973,   979,   980,   981,   985,
     986,   990,   991,   996,   997,  1005,  1004,  1012,  1021,  1020,
    1029,  1038,  1039,  1044,  1046,  1051,  1056,  1058,  1064,  1065,
    1067,  1069,  1071,  1079,  1080,  1081,  1082,  1088,  1090,  1089,
    1102,  1109,  1111,  1115,  1116,  1122,  1123,  1125,  1124,  1127,
    1132,  1131,  1135,  1137,  1141,  1142,  1146,  1151,  1153,  1159,
    1168,  1158,  1182,  1191,  1181,  1207,  1208,  1214,  1216,  1221,
    1223,  1225,  1232,  1234,  1243,  1248,  1253,  1255,  1257,  1264,
    1266,  1273,  1278,  1280,  1282,  1287,  1289,  1296,  1298,  1302,
    1304,  1309,  1311,  1316,  1318,  1324,  1323,  1329,  1333,  1336,
    1335,  1339,  1343,  1346,  1345,  1352,  1351,  1357,  1361,  1363,
    1366,  1368,  1374,  1376,  1382,  1383,  1385,  1400,  1406,  1411,
    1417,  1422,  1424,  1430,  1431,  1436,  1439,  1443,  1454,  1455,
    1460,  1466,  1468,  1473,  1475,  1481,  1482,  1486,  1488,  1494,
    1495,  1500,  1503,  1505,  1507,  1509,  1511,  1513,  1515,  1517,
    1521,  1530,  1538,  1539,  1541,  1545,  1547,  1550,  1554,  1564,
    1566,  1572,  1573,  1577,  1591,  1593,  1596,  1598,  1600,  1608,
    1616,  1628,  1632,  1636,  1651,  1650,  1663,  1667,  1671,  1676,
    1681,  1686,  1688,  1694,  1696,  1697,  1715,  1714,  1722,  1734,
    1737,  1747,  1736,  1757,  1765,  1770,  1782,  1785,  1768,  1812,
    1811,  1825,  1830,  1835,  1839,  1843,  1854,  1861,  1868,  1875,
    1886,  1892,  1896,  1902,  1901,  1957,  1988,  2019,  2034,  2050,
    2052,  2058,  2059,  2065,  2066,  2070,  2071,  2076,  2081,  2083,
    2090,  2090,  2100,  2102,  2101,  2111,  2118,  2119,  2129,  2131,
    2136,  2138,  2145,  2154,  2163,  2172,  2182,  2197,  2197,  2207,
    2208,  2218,  2220,  2226,  2228,  2233
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "TYPENAME", "SCSPEC",
  "TYPESPEC", "TYPE_QUAL", "CONSTANT", "STRING", "ELLIPSIS", "SIZEOF",
  "ENUM", "STRUCT", "UNION", "IF", "ELSE", "WHILE", "DO", "FOR", "SWITCH",
  "CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN_KEYWORD", "GOTO",
  "ASM_KEYWORD", "TYPEOF", "ALIGNOF", "ATTRIBUTE", "EXTENSION", "LABEL",
  "REALPART", "IMAGPART", "'='", "ASSIGN", "'?'", "':'", "OROR", "ANDAND",
  "'|'", "'^'", "'&'", "EQCOMPARE", "ARITHCOMPARE", "RSHIFT", "LSHIFT",
  "'+'", "'-'", "'*'", "'/'", "'%'", "MINUSMINUS", "PLUSPLUS", "UNARY",
  "HYPERUNARY", "'.'", "'('", "'['", "POINTSAT", "INTERFACE",
  "IMPLEMENTATION", "END", "SELECTOR", "DEFS", "ENCODE", "CLASSNAME",
  "PUBLIC", "PRIVATE", "PROTECTED", "PROTOCOL", "OBJECTNAME", "CLASS",
  "ALIAS", "OBJC_STRING", "')'", "';'", "'}'", "'~'", "'!'", "','", "'{'",
  "']'", "$accept", "program", "extdefs", "@1", "@2", "extdef", "datadef",
  "fndef", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "identifier", "unop",
  "expr", "exprlist", "nonnull_exprlist", "unary_expr", "sizeof",
  "alignof", "cast_expr", "$@9", "expr_no_commas", "$@10", "$@11", "$@12",
  "$@13", "$@14", "primary", "@15", "string", "old_style_parm_decls",
  "lineno_datadecl", "datadecls", "datadecl", "lineno_decl", "decls",
  "setspecs", "setattrs", "decl", "typed_declspecs", "reserved_declspecs",
  "typed_declspecs_no_prefix_attr", "reserved_declspecs_no_prefix_attr",
  "declmods", "declmods_no_prefix_attr", "typed_typespecs",
  "reserved_typespecquals", "typespec", "typespecqual_reserved",
  "initdecls", "notype_initdecls", "maybeasm", "initdcl", "@16",
  "notype_initdcl", "@17", "maybe_attribute", "attributes", "attribute",
  "attribute_list", "attrib", "any_word", "init", "$@18",
  "initlist_maybe_comma", "initlist1", "initelt", "$@19", "initval",
  "$@20", "designator_list", "designator", "nested_function", "$@21",
  "$@22", "notype_nested_function", "$@23", "$@24", "declarator",
  "after_type_declarator", "parm_declarator", "notype_declarator",
  "struct_head", "union_head", "enum_head", "structsp", "@25", "@26",
  "@27", "@28", "maybecomma", "maybecomma_warn", "component_decl_list",
  "component_decl_list2", "component_decl", "components",
  "component_declarator", "enumlist", "enumerator", "typename", "absdcl",
  "nonempty_type_quals", "type_quals", "absdcl1", "stmts",
  "lineno_stmt_or_labels", "xstmts", "errstmt", "pushlevel",
  "maybe_label_decls", "label_decls", "label_decl", "compstmt_or_error",
  "compstmt_start", "compstmt", "simple_if", "if_prefix", "do_stmt_start",
  "$@29", "save_filename", "save_lineno", "lineno_labeled_stmt",
  "lineno_stmt_or_label", "stmt_or_label", "stmt", "$@30", "$@31", "$@32",
  "$@33", "@34", "$@35", "$@36", "all_iter_stmt", "all_iter_stmt_simple",
  "@37", "label", "maybe_type_qual", "xexpr", "asm_operands",
  "nonnull_asm_operands", "asm_operand", "asm_clobbers", "parmlist",
  "$@38", "parmlist_1", "$@39", "parmlist_2", "parms", "parm",
  "parmlist_or_identifiers", "$@40", "parmlist_or_identifiers_1",
  "identifiers", "identifiers_or_typenames", "extension", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,    61,   290,    63,    58,   291,
     292,   124,    94,    38,   293,   294,   295,   296,    43,    45,
      42,    47,    37,   297,   298,   299,   300,    46,    40,    91,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,    41,    59,   125,   126,
      33,    44,   123,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    85,    87,    86,    88,    86,    89,    89,
      89,    89,    90,    90,    90,    90,    90,    90,    90,    90,
      92,    93,    91,    91,    94,    95,    91,    91,    96,    97,
      91,    91,    98,    98,    99,    99,    99,    99,    99,    99,
      99,   100,   101,   101,   102,   102,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   104,   105,   106,
     106,   107,   106,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   109,   108,   110,   108,
     111,   112,   108,   113,   108,   108,   108,   114,   114,   114,
     114,   114,   115,   114,   114,   114,   114,   114,   114,   114,
     116,   116,   117,   117,   117,   118,   119,   119,   119,   119,
     120,   120,   120,   120,   121,   122,   122,   122,   122,   123,
     124,   125,   125,   125,   125,   125,   125,   125,   126,   126,
     127,   127,   127,   127,   128,   128,   129,   129,   129,   130,
     130,   130,   130,   131,   131,   131,   131,   132,   132,   133,
     133,   134,   134,   134,   134,   134,   135,   135,   135,   136,
     136,   137,   137,   138,   138,   140,   139,   139,   142,   141,
     141,   143,   143,   144,   144,   145,   146,   146,   147,   147,
     147,   147,   147,   148,   148,   148,   148,   149,   150,   149,
     149,   151,   151,   152,   152,   153,   153,   154,   153,   153,
     156,   155,   155,   155,   157,   157,   158,   158,   158,   160,
     161,   159,   163,   164,   162,   165,   165,   166,   166,   166,
     166,   166,   166,   166,   167,   167,   167,   167,   167,   167,
     167,   168,   168,   168,   168,   168,   168,   168,   168,   169,
     169,   170,   170,   171,   171,   173,   172,   172,   172,   174,
     172,   172,   172,   175,   172,   176,   172,   172,   177,   177,
     178,   178,   179,   179,   180,   180,   180,   181,   181,   181,
     181,   181,   181,   182,   182,   183,   183,   183,   184,   184,
     184,   185,   185,   186,   186,   187,   187,   188,   188,   189,
     189,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   191,   192,   192,   192,   193,   193,   194,   195,   196,
     196,   197,   197,   198,   199,   199,   200,   201,   201,   201,
     201,   202,   202,   203,   205,   204,   206,   207,   208,   208,
     209,   210,   210,   211,   211,   211,   212,   211,   211,   211,
     213,   214,   211,   211,   211,   215,   216,   217,   211,   218,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   219,   221,   220,   222,   222,   222,   222,   223,
     223,   224,   224,   225,   225,   226,   226,   227,   228,   228,
     230,   229,   231,   232,   231,   231,   233,   233,   233,   233,
     234,   234,   235,   235,   235,   235,   235,   237,   236,   238,
     238,   239,   239,   240,   240,   241
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     0,     2,     0,     3,     1,     1,
       5,     2,     3,     4,     4,     2,     2,     2,     2,     1,
       0,     0,     7,     4,     0,     0,     7,     4,     0,     0,
       6,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     3,     1,     2,     2,     2,
       2,     2,     4,     2,     4,     2,     2,     1,     1,     1,
       4,     0,     7,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     0,     7,     0,     5,     3,     3,     1,     1,     1,
       3,     3,     0,     4,     4,     4,     3,     3,     2,     2,
       1,     2,     0,     1,     2,     3,     1,     1,     2,     2,
       4,     4,     2,     2,     3,     1,     1,     2,     2,     0,
       0,     4,     4,     3,     3,     2,     2,     2,     2,     3,
       0,     2,     2,     2,     2,     3,     0,     2,     2,     1,
       1,     2,     2,     1,     1,     2,     2,     2,     3,     0,
       2,     1,     1,     1,     4,     4,     1,     1,     1,     1,
       3,     1,     3,     0,     4,     0,     6,     3,     0,     6,
       3,     0,     1,     1,     2,     6,     1,     3,     0,     1,
       4,     6,     4,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     2,     1,     3,     3,     2,     0,     4,     1,
       0,     4,     1,     1,     1,     2,     2,     5,     3,     0,
       0,     5,     0,     0,     5,     1,     1,     3,     3,     4,
       3,     3,     3,     1,     3,     4,     4,     3,     3,     3,
       1,     3,     3,     3,     4,     4,     3,     3,     1,     1,
       2,     1,     2,     1,     2,     0,     7,     5,     2,     0,
       7,     5,     2,     0,     8,     0,     7,     2,     0,     1,
       0,     1,     1,     2,     0,     3,     2,     3,     1,     3,
       1,     1,     2,     1,     3,     4,     6,     5,     1,     3,
       1,     1,     3,     2,     2,     0,     1,     1,     2,     0,
       2,     3,     3,     2,     3,     4,     3,     2,     3,     2,
       3,     1,     1,     2,     2,     0,     1,     2,     0,     0,
       1,     1,     2,     3,     1,     2,     1,     2,     6,     5,
       5,     2,     2,     4,     0,     4,     0,     0,     3,     4,
       3,     1,     1,     1,     1,     2,     0,     4,     1,     3,
       0,     0,     7,     5,     2,     0,     0,     0,    12,     0,
       6,     2,     2,     2,     3,     6,     8,    10,    12,     3,
       4,     1,     1,     0,     6,     3,     5,     2,     3,     0,
       1,     0,     1,     0,     1,     1,     3,     4,     1,     3,
       0,     2,     2,     0,     4,     2,     0,     1,     1,     3,
       1,     3,     4,     4,     4,     4,     4,     0,     2,     1,
       2,     1,     3,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     6,     0,     1,     0,     0,   153,   144,   151,
     143,   243,   239,   241,     0,     0,     0,   405,    19,     5,
       9,     8,     0,   119,   119,   139,   130,   140,   173,     0,
       0,     0,   152,     0,     7,    17,    18,   244,   240,   242,
       0,     0,     0,   238,   289,     0,     0,   161,   120,     0,
      16,     0,    15,     0,   141,   130,   142,   146,   145,   128,
     174,    32,    33,   264,   248,   264,   252,   255,   257,    11,
      87,    88,   100,    57,    58,     0,     0,     0,    34,    36,
      35,     0,    38,    37,     0,    39,    40,     0,     0,    41,
      59,     0,     0,    63,    44,    46,    89,     0,   287,     0,
     285,   149,     0,   285,   178,     0,     0,    12,     0,     0,
      31,     0,   397,     0,     0,   171,   223,   289,     0,     0,
     159,   120,     0,   215,   216,     0,     0,   129,   132,   156,
     157,   131,   133,   158,     0,     0,   245,     0,   249,     0,
     253,    55,    56,    50,    47,     0,     0,     0,     0,    49,
       0,     0,     0,    51,     0,    53,     0,     0,    80,    78,
      76,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,    98,     0,    42,     0,     0,   101,
      48,   154,   289,   380,     0,   120,   283,   286,   147,   155,
     288,   149,   284,   184,   185,   186,   183,     0,   176,   179,
     290,   233,   232,   162,   163,   237,     0,   231,     0,     0,
     236,     0,     0,    29,     0,   326,   107,   327,   170,   172,
       0,     0,    14,     0,     0,    23,     0,   171,   397,     0,
      13,    27,     0,   171,   271,   266,   119,   263,   119,     0,
     264,   171,   264,   280,   281,   260,   278,     0,    91,    90,
     316,   308,     0,     0,    10,    45,     0,     0,    85,    86,
       0,     0,     0,     0,    74,    75,    73,    72,    71,    70,
      69,    64,    65,    66,    67,    68,    96,     0,    43,     0,
      97,   293,     0,   297,     0,   299,     0,     0,   380,     0,
     150,   148,     0,   178,    42,     0,     0,   401,   387,   119,
     119,   399,     0,   388,   390,   398,     0,   234,   235,   307,
       0,   109,   104,   108,     0,   168,   221,   217,   160,   222,
      21,   167,   218,   220,     0,    25,   247,   326,   265,   326,
     272,     0,   251,     0,     0,   261,     0,   260,   317,   309,
      93,    61,    60,    52,    54,     0,     0,    79,    77,    94,
      95,   292,   291,   381,   298,   300,   294,   296,     0,   175,
     177,    87,     0,   164,   385,   285,   285,   382,   383,     0,
     400,     0,     0,    30,   314,   105,   119,   119,   136,     0,
       0,   165,   219,     0,   267,   273,   327,   269,   171,   171,
     282,   279,   171,     0,     0,     0,   310,   311,     0,    81,
      84,   295,   180,     0,   182,   230,   289,   380,   120,   171,
     171,   171,   289,   120,   171,   171,     0,   389,   391,   402,
     315,   112,     0,   113,     0,   136,   134,   190,   188,   187,
     169,    22,     0,    26,   326,     0,   246,   250,   256,   171,
     403,     0,     0,     0,   326,     0,     0,   116,   327,   302,
     312,   203,    87,     0,     0,   200,     0,   202,     0,   258,
     193,   199,     0,     0,     0,     0,   293,     0,   397,     0,
     392,   393,   394,   293,     0,   395,   396,   384,     0,     0,
     163,   135,   138,   137,     0,   166,   274,     0,   171,   254,
     313,     0,   319,   118,   117,   306,     0,   320,   304,   327,
     303,     0,   206,     0,     0,   197,    62,     0,   192,     0,
     205,   196,    82,   181,   228,   229,   224,     0,   227,     0,
     110,   111,     0,   171,     0,   275,   404,   318,     0,   153,
       0,   340,   324,     0,     0,     0,     0,     0,     0,     0,
       0,   369,   361,     0,     0,   114,   119,   119,   333,   338,
       0,     0,   330,   331,   334,   362,   332,     0,     0,   208,
       0,     0,   194,   195,   225,   226,   189,   277,   171,     0,
       0,   326,   371,     0,     0,   367,   351,   352,   353,     0,
       0,     0,   370,     0,   171,   335,   125,     0,   126,     0,
       0,   322,   327,   321,   344,     0,   127,     0,   201,   198,
     276,     0,     0,     0,   372,    46,     0,     0,     0,   365,
     354,     0,   359,     0,   368,     0,   123,   209,     0,   124,
     212,   339,   326,     0,     0,   207,   323,     0,   325,   363,
     345,   349,     0,   360,     0,   121,     0,   122,     0,   337,
     328,   326,     0,   341,   326,   371,   326,   366,   373,     0,
     210,   213,   329,   343,   326,   364,     0,   350,     0,     0,
     374,   375,   355,     0,     0,   342,   346,     0,   373,     0,
       0,   211,   214,   371,     0,     0,   356,   376,     0,   377,
       0,     0,   347,   378,     0,   357,   326,     0,     0,   348,
     358,   379
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,     5,    19,    20,    21,   226,   380,
     232,   383,   114,   310,   456,    87,   146,   277,    89,    90,
      91,    92,    93,   398,    94,   263,   262,   260,   464,   261,
      95,   147,    96,   213,   214,   215,   375,   443,   444,    22,
     109,   545,   299,    59,   376,   426,   300,    25,   100,   188,
      26,   131,   119,    46,   115,   120,   432,    47,   379,   218,
     219,    28,   197,   198,   199,   430,   484,   458,   459,   460,
     561,   461,   504,   462,   463,   616,   636,   663,   619,   638,
     664,   204,   123,   409,   124,    29,    30,    31,    32,   240,
     242,   247,   139,   508,   336,   134,   135,   237,   384,   385,
     245,   246,   102,   186,   103,   105,   187,   445,   446,   496,
     216,   339,   395,   396,   397,   373,   251,   374,   549,   550,
     551,   571,   592,   314,   593,   449,   552,   553,   622,   570,
     654,   645,   673,   686,   646,   554,   555,   644,   556,   583,
     606,   659,   660,   661,   684,   283,   284,   301,   416,   302,
     303,   304,   207,   208,   305,   306,   441,    97
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -571
static const yytype_int16 yypact[] =
{
      79,    90,   121,  2328,  -571,  2328,   252,  -571,  -571,  -571,
    -571,   136,   136,   136,   154,   164,   176,  -571,  -571,  -571,
    -571,  -571,   382,   117,  1173,   101,  -571,   136,  -571,    51,
      63,    66,  -571,  2328,  -571,  -571,  -571,   136,   136,   136,
    2154,  2088,   184,  -571,  -571,   382,   107,  -571,   136,  1346,
    -571,   376,  -571,   382,   101,  -571,   136,  -571,  -571,   687,
    -571,  -571,  -571,  -571,    96,  -571,   118,  -571,   145,  -571,
    -571,  -571,  -571,  -571,  -571,  2154,  2154,   357,  -571,  -571,
    -571,  2154,  -571,  -571,  1109,  -571,  -571,  2154,   168,   178,
    -571,  2206,  2239,  -571,  2438,   468,   263,  2154,  -571,   219,
     232,  -571,   229,  1722,   589,   324,   216,  -571,   376,   382,
    -571,   254,  -571,  1448,   312,   136,  -571,  -571,   376,   120,
    -571,   136,  1441,   383,   385,   199,  1408,   687,  -571,  -571,
    -571,  -571,   136,  -571,   261,  1027,  -571,   270,  -571,   283,
    -571,  -571,  -571,  -571,  -571,   279,   290,   302,   317,  -571,
     318,  2154,  1109,  -571,  1109,  -571,  2154,  2154,   359,  -571,
    -571,  2154,  2154,  2154,  2154,  2154,  2154,  2154,  2154,  2154,
    2154,  2154,  2154,  -571,  -571,   357,  2154,  2154,   357,  -571,
    -571,  -571,  -571,   232,  1501,   136,  -571,   391,   504,  -571,
    -571,  -571,  -571,  -571,  -571,  -571,  -571,    13,  -571,   341,
    -571,   385,  -571,  -571,   404,   385,   415,  -571,  1563,  1554,
    -571,   350,   361,  -571,   397,    61,  -571,  -571,   411,   136,
     465,   235,  -571,   376,   376,  -571,   312,   136,  -571,  1607,
    -571,  -571,   312,   136,  -571,  -571,   386,   375,   358,   470,
    -571,   136,  -571,  -571,   419,   381,  -571,   283,  -571,  -571,
    -571,   392,   402,  1979,  -571,  2438,   431,   433,  2438,  2438,
    2154,   447,  2154,  2154,  2061,   919,   896,   759,   839,   550,
     550,   368,   368,  -571,  -571,  -571,  -571,   437,   178,   390,
    -571,   398,   262,  -571,  1616,  -571,   408,   232,  -571,  1660,
    -571,   504,   459,   589,  2272,    49,   473,  -571,  -571,  -571,
    1879,  -571,   478,   202,  -571,  -571,    46,  -571,  -571,  -571,
      32,  -571,  -571,  -571,   717,  -571,   383,  -571,  -571,   383,
    -571,   469,  -571,  -571,   477,  -571,  -571,  -571,  -571,  -571,
    -571,   485,  -571,   487,  2154,   357,   488,   381,  -571,   455,
    -571,  -571,  -571,  -571,  -571,   529,  2154,  1870,  1950,  -571,
    -571,   391,  -571,  -571,  -571,   391,  -571,  -571,   486,  -571,
    -571,   110,   495,  -571,  -571,   205,   238,  -571,  -571,  1798,
    -571,   569,   302,  -571,  -571,  -571,   497,   409,  -571,  1283,
      32,  -571,  -571,    32,   494,  -571,  -571,   494,   136,   136,
    2438,  -571,   136,   498,   357,   735,   455,  -571,   871,  -571,
    1790,  -571,  -571,  2154,  -571,  -571,  -571,   238,   136,   124,
     160,   136,  -571,   136,   160,   136,  1616,  -571,  -571,  -571,
    -571,  -571,   376,  -571,   382,  -571,   329,  -571,  -571,  2438,
    -571,  -571,  1283,  -571,  -571,   195,  -571,  -571,  -571,   136,
    -571,   225,   403,   655,   500,   501,   815,  -571,  -571,  -571,
    -571,  -571,   548,   357,  2154,  -571,   549,  2438,   526,   525,
    -571,  -571,   169,  1224,  2154,   111,   165,   205,  -571,  1713,
    -571,  -571,  -571,   207,   238,  -571,  -571,  -571,   269,   276,
      33,   329,  -571,  -571,   871,  -571,  -571,  2154,   143,  -571,
    -571,   357,  -571,  -571,  -571,  -571,   547,  -571,  -571,  -571,
    -571,  1847,  -571,  2352,   871,  -571,  -571,  1165,  -571,  1337,
    -571,  -571,  1790,  -571,   435,   435,  -571,  1766,  -571,   543,
    -571,  -571,   551,  2397,  2154,  -571,  -571,  -571,  1927,   590,
     573,  -571,  -571,   574,   576,  2154,   597,   577,   578,  2121,
      60,   650,  -571,   633,   610,  -571,   613,  1668,  -571,   675,
     971,    58,  -571,  -571,  -571,  -571,  -571,  2035,  2154,  -571,
     618,  1337,  -571,  -571,  -571,  -571,  -571,  -571,  2397,  2154,
     639,  -571,  2154,  2154,   601,  -571,  -571,  -571,  -571,   625,
    2154,   629,  -571,   649,   136,  -571,  -571,   376,  -571,   382,
    1053,  -571,  -571,  -571,  -571,  2154,  -571,  2371,  -571,  -571,
    -571,   635,  2154,   695,  -571,   531,   641,   640,  2154,  -571,
    -571,   642,  -571,  2154,  -571,   286,  -571,    53,   310,  -571,
     744,  -571,  -571,  1927,   644,  -571,  -571,   651,  -571,  -571,
    -571,  -571,  2420,  -571,    39,  -571,   312,  -571,   312,  -571,
    -571,  -571,   648,  -571,  -571,  2154,  -571,  -571,   719,   674,
    -571,  -571,  -571,  -571,  -571,  -571,   690,  -571,   712,    43,
     691,  -571,  -571,   302,   302,  -571,  -571,  2154,   719,   696,
     719,  -571,  -571,  2154,   700,    48,  -571,  -571,   701,  -571,
     415,   703,  -571,   263,   135,  -571,  -571,   704,   415,  -571,
    -571,   263
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -571,  -571,  -571,  -571,  -571,    67,  -571,  -571,  -571,  -571,
    -571,  -571,  -571,  -571,   -26,  -571,   -40,   493,  -155,   428,
    -571,  -571,    20,  -571,   452,  -571,  -571,  -571,  -571,  -571,
     210,  -571,  -188,  -183,   575,  -571,  -571,   347,  -571,     0,
     -80,   237,     4,   737,  -571,   370,     7,   -11,   -83,   605,
       1,  -149,  -391,   -51,  -111,   -76,  -571,  -571,  -571,   142,
      23,   137,  -571,   506,  -571,   365,  -571,  -364,  -571,   293,
    -571,  -410,  -571,  -571,   339,  -571,  -571,  -571,  -571,  -571,
    -571,   -45,   -53,    92,    -7,  -571,  -571,  -571,   -30,  -571,
    -571,  -571,  -571,  -571,   476,   -35,  -571,   581,   499,   388,
     580,   508,    25,   -95,   -78,   -98,  -122,   401,  -571,  -571,
    -192,  -571,  -571,  -571,   451,  -102,  -571,  -120,  -571,  -571,
    -571,  -571,   -97,  -336,  -484,   405,  -571,   206,  -571,  -571,
    -571,  -571,  -571,  -571,  -571,  -571,  -571,  -571,   230,  -571,
    -570,   186,  -571,   182,  -571,   568,  -571,  -236,  -571,  -571,
    -571,   490,  -208,  -571,  -571,  -571,  -571,    11
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -387
static const yytype_int16 yytable[] =
{
      88,    99,   125,    64,    66,    68,   122,    23,   192,    23,
      24,   227,    24,    54,    33,    49,    33,   217,   295,   220,
     322,   278,   311,    51,    53,    55,    27,   252,    27,   133,
     137,   478,   203,   372,    37,    38,    39,    23,   106,   290,
      24,   224,   101,   320,    33,    48,   126,    56,   353,   325,
     435,   143,   236,   511,    61,    62,    27,   238,   179,   594,
     111,   282,  -103,    61,    62,   221,    61,    62,    48,    61,
      62,   312,    34,   211,   121,   656,    48,   648,   196,    -2,
     111,   668,   132,  -163,   281,   101,   680,   603,  -163,   292,
       4,   112,   113,   227,   293,   141,   142,   133,   201,   563,
      69,   144,   205,   678,   191,   287,    57,   149,    58,   148,
     580,   106,   501,   244,   250,   649,   595,   180,   217,   669,
     522,    -3,   370,   185,   681,   363,   185,   371,    48,   217,
    -163,   121,    48,    63,  -163,   217,   101,   279,   639,   278,
     560,   121,   290,  -103,   286,    65,   239,   318,    67,   276,
     132,   599,   280,   101,    16,   101,   236,   652,   133,   351,
     655,   238,   657,   528,    60,   355,    16,   316,    43,   405,
     665,   319,   200,    16,    60,    60,    60,   256,   136,   257,
     477,   524,   468,   469,   107,    60,   402,   513,   108,   324,
      16,   403,   151,    60,    50,    16,   615,   222,    43,   116,
     138,   223,   689,   447,   509,   331,   185,   333,    43,   405,
      43,   687,    40,   201,   200,   406,   688,   205,   112,   113,
     345,   244,    41,   407,   184,    16,   453,   140,   454,   144,
     386,    27,   386,   487,    42,    16,   327,    16,   329,   191,
     101,    43,   104,   121,   150,   117,   121,   121,   465,   358,
     239,   493,   420,   118,   498,   406,   623,   412,    60,   151,
     516,   133,    16,   407,   184,   407,   184,   196,    16,    60,
     411,   415,   179,   342,   112,   113,   230,   483,   431,   368,
     108,   433,   182,   369,   243,   282,    61,    62,   412,    54,
     183,   184,   202,   228,   229,   181,   407,   184,   448,   365,
     366,    55,   490,   377,   185,   189,   491,    27,   466,   244,
     185,   317,   206,   212,   473,   378,  -326,  -326,  -326,  -326,
     288,   289,    60,    56,  -326,  -326,  -326,    43,   467,    35,
      36,   200,   483,   474,   482,   129,   130,   386,   352,   233,
    -326,    11,    12,    13,   351,   355,   520,   448,   241,   499,
     223,   351,   355,   521,    16,   248,    60,   108,   410,   414,
      61,    62,     7,   635,     9,   190,   249,   223,   440,   321,
      11,    12,    13,   479,    44,   326,   422,   424,   425,    43,
     116,   548,    45,   332,   250,    43,    15,   637,   408,   413,
     488,   108,    27,   253,  -102,   254,   133,   -83,   212,   294,
     106,  -106,  -106,  -106,  -106,   200,    16,  -106,   548,  -106,
    -106,  -106,    16,     7,    57,     9,    58,   480,   170,   171,
     172,    11,    12,    13,    72,  -106,   117,   502,    16,   519,
     413,   111,    44,   308,   118,  -270,  -270,    15,   309,    27,
      45,   228,   229,   112,   113,   121,   315,    48,   182,   288,
     289,   133,   328,   650,   334,   651,   183,   184,   121,   201,
     205,   544,   335,  -268,  -268,   526,   201,   205,    43,   116,
     338,   234,   200,   350,     7,   543,     9,    98,   340,  -106,
     309,   492,    11,    12,    13,   346,   423,   394,   544,   408,
     408,   354,   683,   468,   469,    16,   413,   413,    15,   579,
     691,    17,   543,   548,   381,   546,   227,   343,   547,   344,
     129,   130,   557,   349,   581,   117,    11,    12,    13,   153,
     155,   173,   174,   118,    27,   175,   176,   177,   178,   601,
     436,   437,   604,   607,   438,   359,    54,   144,   618,   217,
     611,   217,   617,   671,   672,    60,   587,   589,    55,   364,
      60,   470,   471,   472,   367,   624,   475,   476,   514,   515,
     382,   546,   627,   388,   547,   389,   392,   399,   557,   401,
      56,   404,   419,   634,   421,   434,   439,   180,  -305,   497,
      27,   489,   620,   544,   173,   174,   -32,   505,   175,   176,
     177,   178,    61,    62,   193,   194,   195,   543,   168,   169,
     170,   171,   172,   255,   506,   604,   507,   629,   258,   259,
     121,   608,    48,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   527,   565,   674,   -33,   566,
     525,   569,   572,   604,   573,   575,   156,   157,   158,   609,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   576,   577,   212,   582,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,   567,  -115,  -115,  -115,  -115,
    -115,   584,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,   585,  -115,  -115,
     586,   590,   128,   129,   130,  -115,   598,   602,  -115,    11,
      12,    13,   610,  -115,  -115,  -115,   612,   613,  -115,  -115,
     600,   626,   628,  -115,   347,   348,   631,    16,   630,   633,
     642,     7,     8,     9,    10,   653,   614,   643,   658,    11,
      12,    13,  -115,  -115,  -115,  -115,   442,  -115,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,    15,  -326,  -326,  -326,  -326,
    -326,   662,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,   666,  -326,  -326,
     667,   111,   670,   676,  -163,  -326,   679,   682,  -326,  -163,
     685,   690,   605,  -326,  -326,  -326,   390,   362,  -326,  -326,
     313,   494,   127,  -326,   596,   481,   291,   485,   400,   360,
     562,   510,   112,   113,   165,   166,   167,   168,   169,   170,
     171,   172,  -326,   393,  -326,  -326,   212,  -326,  -326,  -326,
     330,  -163,   486,  -326,  -326,  -163,  -326,   337,   387,   640,
    -326,   429,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,   391,  -326,   495,  -326,   450,  -326,  -326,
     457,   500,   677,   641,   675,  -326,   356,     0,  -326,   418,
       0,     0,     0,  -326,  -326,  -326,     0,     0,  -326,  -326,
       0,     0,   451,  -326,   452,    62,     0,     0,     0,    71,
      72,     0,    73,     0,   429,   166,   167,   168,   169,   170,
     171,   172,  -326,  -301,  -326,  -326,     0,  -326,     0,     0,
      74,     0,    17,     0,    75,    76,   503,     0,     0,     0,
       0,    77,     0,     0,    78,   457,   512,     0,     0,    79,
      80,    81,     0,     0,    82,    83,     0,     0,   453,    84,
     454,     0,     0,     0,     0,     0,   457,     0,     0,   523,
     164,   165,   166,   167,   168,   169,   170,   171,   172,  -191,
      85,    86,     0,   455,     0,     0,   457,     0,     0,   457,
       0,   457,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   591,     0,  -326,  -326,   568,     0,     0,  -326,
    -326,     0,  -326,     0,     0,     0,  -326,   574,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,     0,
    -326,     0,  -326,     0,  -326,  -326,     0,     0,     0,     0,
     597,  -326,     0,   457,  -326,     0,     0,     0,     0,  -326,
    -326,  -326,     0,     0,  -326,  -326,     0,     0,   234,  -326,
       0,     7,     0,     9,    98,     0,     0,     0,     0,    11,
      12,    13,     0,     0,     0,     0,     0,     0,  -326,     0,
    -326,  -326,     0,  -326,   621,    15,  -336,  -336,    17,     0,
     632,  -336,  -336,     0,  -336,     0,     0,     0,  -336,     0,
    -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,     0,  -336,     0,  -336,     0,  -336,  -336,     0,     0,
       0,     0,     0,  -336,     0,     0,  -336,     0,     0,     0,
       0,  -336,  -336,  -336,   235,  -262,  -336,  -336,     0,     0,
     145,  -336,    70,     7,     0,     9,    98,    71,    72,     0,
      73,    11,    12,    13,     0,     0,     0,     0,     0,     0,
    -336,     0,  -336,  -336,     0,  -336,     0,    15,    74,     0,
      17,     0,    75,    76,     0,     0,     0,     0,     0,    77,
       0,     0,    78,     0,     0,     0,     0,    79,    80,    81,
       0,     0,    82,    83,     0,     0,   451,    84,   452,    62,
       0,     0,     0,    71,    72,     0,    73,     7,     8,     9,
      10,     0,     0,     0,     0,    11,    12,    13,    85,    86,
       0,   -92,     0,     0,    74,     0,    17,     0,    75,    76,
       0,    15,     0,    16,     0,    77,     0,     0,    78,     0,
       0,     0,     0,    79,    80,    81,     0,     0,    82,    83,
       0,     0,   453,    84,   454,   451,     0,    70,     0,     0,
       0,     0,    71,    72,     0,    73,     0,     0,     0,     0,
       0,     0,     0,  -259,    85,    86,     0,   455,     0,     0,
      52,     0,     0,    74,     0,    17,     0,    75,    76,  -204,
       0,     0,     0,     0,    77,     0,     0,    78,     0,     0,
       0,     0,    79,    80,    81,     0,     0,    82,    83,     0,
       0,  -204,    84,  -204,   427,     0,    70,     0,     0,     0,
       0,    71,    72,     0,    73,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,     0,   455,     0,     0,     0,
       0,     0,    74,     0,    17,     0,    75,    76,     0,     0,
       0,     0,     0,    77,     0,     0,    78,     0,     0,     0,
       0,    79,    80,    81,     0,     0,    82,    83,   451,     0,
      70,    84,     0,     0,     0,    71,    72,   110,    73,     0,
     -28,   -28,   -28,   -28,     0,     0,     0,     0,   -28,   -28,
     -28,     0,    85,    86,     0,   428,    74,     0,    17,     0,
      75,    76,     0,   111,   -28,     0,  -163,    77,     0,     0,
      78,  -163,     0,     0,     0,    79,    80,    81,     0,     0,
      82,    83,     0,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   113,     0,     0,     0,   231,
       0,     0,   -24,   -24,   -24,   -24,    85,    86,     0,   455,
     -24,   -24,   -24,  -163,     0,     0,     0,  -163,   -28,     0,
       0,     0,     0,     0,     0,   111,   -24,     0,  -163,     0,
       0,     0,   225,  -163,     0,   -20,   -20,   -20,   -20,     0,
       0,    70,     0,   -20,   -20,   -20,    71,    72,     0,    73,
       0,     0,     0,     0,     0,     0,   112,   113,   111,   -20,
       0,  -163,     0,     0,     0,     0,  -163,    74,     0,    17,
       0,    75,    76,     0,     0,  -163,     0,     0,    77,  -163,
     -24,    78,     0,     0,     0,     0,    79,    80,   209,     0,
       0,    82,    83,     0,    70,     0,    84,     0,     0,    71,
      72,     0,    73,     0,     0,     0,     0,     0,  -163,     0,
       0,     0,  -163,   -20,     0,     0,     0,    85,    86,     0,
      74,   210,    17,     0,    75,    76,     0,     0,     0,     0,
       0,    77,     0,     0,    78,     0,     0,     0,     0,    79,
      80,    81,     0,     0,    82,    83,     0,    70,     0,    84,
       0,     0,    71,    72,   296,    73,   297,     7,     8,     9,
      10,     0,     0,   298,     0,    11,    12,    13,     0,     0,
      85,    86,     0,    74,   285,    17,     0,    75,    76,     0,
       0,    15,     0,    16,    77,     0,     0,    78,     0,     0,
       0,     0,    79,    80,    81,     0,     0,    82,    83,     0,
      70,     0,    84,     0,     0,    71,    72,   296,    73,     0,
       7,     8,     9,    10,     0,     0,   298,     0,    11,    12,
      13,     0,     0,    85,    86,     0,    74,   307,    17,  -386,
      75,    76,     0,     0,    15,     0,    16,    77,     0,     0,
      78,     0,     0,     0,     0,    79,    80,    81,     0,     0,
      82,    83,     0,    70,     0,    84,     0,     0,    71,    72,
       0,    73,     7,     8,     9,    10,     0,     0,     0,     0,
      11,    12,    13,     0,     0,     0,    85,    86,     0,    74,
     323,    17,  -386,    75,    76,     0,    15,     0,    16,     0,
      77,     0,     0,    78,     0,     0,     0,     0,    79,    80,
      81,     0,     0,    82,    83,     0,    70,     0,    84,     0,
       0,    71,    72,     0,    73,     0,     7,     0,     9,   190,
       0,     0,     0,     0,    11,    12,    13,     0,     0,    85,
      86,     0,    74,   357,    17,   588,    75,    76,     0,     0,
      15,     0,    16,    77,     0,     0,    78,     0,     0,     0,
       0,    79,    80,   517,     0,     0,    82,    83,     0,    70,
       0,    84,   182,     0,    71,    72,     0,    73,     0,     0,
     183,   184,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    85,    86,     0,    74,   518,    17,     0,    75,
      76,     0,     7,     8,     9,    10,    77,     0,   417,    78,
      11,    12,    13,     0,    79,    80,    81,     0,     0,    82,
      83,     0,     0,     0,    84,     0,    15,   158,    16,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,    85,    86,     0,     0,   564,
     452,   529,     8,     9,    10,    71,    72,     0,    73,    11,
      12,    13,   530,     0,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,    15,    74,    16,    17,     0,
      75,    76,     0,     7,     8,     9,    10,    77,     0,     0,
      78,    11,    12,    13,     0,    79,    80,    81,     0,     0,
      82,    83,     0,     0,     0,    84,     0,    15,     0,    16,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,   542,     0,    85,    86,     0,   250,
     452,    62,     0,     0,     0,    71,    72,     0,    73,     0,
       0,     0,   530,     0,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,     0,    74,     0,    17,     0,
      75,    76,     0,     0,     0,     0,     0,    77,     0,     0,
      78,     0,     0,     0,     0,    79,    80,    81,     0,     0,
      82,    83,    70,     0,     0,    84,     0,    71,    72,     0,
      73,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,   542,     0,    85,    86,    74,   250,
      17,     0,    75,    76,     0,     0,     0,     0,     0,    77,
       0,     0,    78,     0,     0,     0,     0,    79,    80,    81,
       0,     0,    82,    83,     0,     0,     0,    84,    70,     7,
       8,     9,    10,    71,    72,     0,    73,    11,    12,    13,
       0,     0,     0,     0,     0,     0,     0,     0,    85,    86,
       0,   341,     0,    15,    74,    16,    17,     0,    75,    76,
       0,     0,     0,     0,     0,    77,     0,     0,    78,     0,
       0,     0,     0,    79,    80,    81,     0,     0,    82,    83,
       0,    70,     7,    84,     9,    98,    71,    72,     0,    73,
      11,    12,    13,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,    85,    86,    15,    74,     0,    17,
       0,    75,    76,     0,    70,     0,     0,     0,    77,    71,
      72,    78,    73,     0,     0,     0,    79,    80,    81,     0,
       0,    82,    83,     0,     0,     0,    84,     0,     0,     0,
      74,     0,    17,     0,    75,    76,     0,    70,     0,     0,
       0,    77,    71,    72,    78,    73,     0,    85,    86,    79,
      80,    81,     0,     0,    82,    83,     0,     0,     0,    84,
       0,     0,     0,    74,     0,    17,     0,    75,    76,     0,
       0,     0,     0,     0,    77,     0,     0,    78,   578,     0,
      85,    86,    79,    80,    81,     0,     0,    82,    83,    70,
       0,     0,    84,     0,    71,    72,     0,    73,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    74,     0,    17,     0,    75,
      76,     0,    70,     0,     0,     0,    77,    71,    72,    78,
      73,     0,     0,     0,    79,    80,    81,     0,     0,    82,
      83,     0,     0,     0,   152,     0,     0,     0,    74,     0,
      17,     0,    75,    76,     0,   361,     0,     0,     0,    77,
      71,    72,    78,    73,     0,    85,    86,    79,    80,    81,
       0,     0,    82,    83,     0,     0,     0,   154,     0,     0,
       0,    74,     0,    17,     0,    75,    76,     0,     0,     0,
       0,     0,    77,     0,     0,    78,     0,     0,    85,    86,
      79,    80,    81,     0,     0,    82,    83,     0,     0,     6,
      84,  -119,     7,     8,     9,    10,     0,     0,     0,     0,
      11,    12,    13,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,     0,     0,    14,    15,     0,    16,    17,
       0,     0,   558,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -119,     0,
       0,     0,     0,     0,     0,     0,  -119,   156,   157,   158,
       0,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,    18,   156,   157,   158,     0,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,     0,     0,    16,     0,     0,
       0,     0,   156,   157,   158,   559,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
       0,     0,     0,     0,   625,   156,   157,   158,   647,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   156,   157,   158,     0,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-571)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      40,    41,    53,    29,    30,    31,    51,     3,   103,     5,
       3,   122,     5,    24,     3,    22,     5,   114,   206,   117,
     228,   176,   214,    23,    24,    24,     3,   147,     5,    59,
      65,   422,   108,     1,    11,    12,    13,    33,    45,   188,
      33,   121,    41,   226,    33,    22,    53,    24,   284,   232,
     386,    77,   135,   463,     3,     4,    33,   135,     9,     1,
      27,   183,     1,     3,     4,   118,     3,     4,    45,     3,
       4,    10,     5,   113,    51,   645,    53,    38,   104,     0,
      27,    38,    59,    30,   182,    84,    38,   571,    35,    76,
       0,    58,    59,   204,    81,    75,    76,   127,   105,   509,
      33,    81,   109,   673,   103,   185,     5,    87,     7,    84,
      50,   118,   448,   139,    82,    76,    58,    97,   215,    76,
     484,     0,    76,   100,    76,    76,   103,    81,   105,   226,
      77,   108,   109,    82,    81,   232,   135,   177,   622,   294,
     504,   118,   291,    82,   184,    82,   135,   223,    82,   175,
     127,   561,   178,   152,    30,   154,   239,   641,   188,   281,
     644,   239,   646,   499,    27,   287,    30,   220,     3,     4,
     654,   224,     7,    30,    37,    38,    39,   152,    82,   154,
     416,    38,    58,    59,    77,    48,    76,    76,    81,   229,
      30,    81,    81,    56,    77,    30,   587,    77,     3,     4,
      82,    81,   686,   395,    35,   240,   183,   242,     3,     4,
       3,    76,    58,   220,     7,    50,    81,   224,    58,    59,
     260,   247,    58,    58,    59,    30,    57,    82,    59,   209,
     327,   208,   329,    38,    58,    30,   236,    30,   238,   238,
     239,     3,    58,   220,    76,    50,   223,   224,   403,   289,
     239,   443,   372,    58,   446,    50,   592,    50,   121,    81,
     468,   291,    30,    58,    59,    58,    59,   293,    30,   132,
     365,   366,     9,   253,    58,    59,    77,   426,   380,    77,
      81,   383,    50,    81,     1,   407,     3,     4,    50,   300,
      58,    59,    76,    58,    59,    76,    58,    59,   395,   299,
     300,   300,    77,   314,   281,    76,    81,   284,   406,   335,
     287,    76,    58,     1,   412,   314,     4,     5,     6,     7,
      58,    59,   185,   300,    12,    13,    14,     3,   408,    77,
      78,     7,   481,   413,     5,     6,     7,   434,    76,    78,
      28,    12,    13,    14,   466,   467,    77,   444,    78,   446,
      81,   473,   474,    77,    30,    76,   219,    81,   365,   366,
       3,     4,     4,    77,     6,     7,    76,    81,   394,   227,
      12,    13,    14,   424,    50,   233,   376,   377,   377,     3,
       4,   501,    58,   241,    82,     3,    28,    77,   365,   366,
     435,    81,   369,    76,    82,    77,   426,    38,     1,    58,
     407,     4,     5,     6,     7,     7,    30,    10,   528,    12,
      13,    14,    30,     4,     5,     6,     7,   424,    50,    51,
      52,    12,    13,    14,     9,    28,    50,   453,    30,   469,
     407,    27,    50,    83,    58,    77,    78,    28,    77,   416,
      58,    58,    59,    58,    59,   422,    35,   424,    50,    58,
      59,   481,    77,   636,    35,   638,    58,    59,   435,   466,
     467,   501,    81,    77,    78,   491,   473,   474,     3,     4,
      78,     1,     7,    83,     4,   501,     6,     7,    76,    82,
      77,    78,    12,    13,    14,    38,    77,    32,   528,   466,
     467,    83,   680,    58,    59,    30,   473,   474,    28,   539,
     688,    31,   528,   623,    35,   501,   617,    76,   501,    76,
       6,     7,   501,    76,   540,    50,    12,    13,    14,    91,
      92,    53,    54,    58,   501,    57,    58,    59,    60,   569,
     388,   389,   572,   573,   392,    76,   547,   517,   589,   636,
     580,   638,   587,   663,   664,   408,   546,   547,   547,    76,
     413,   409,   410,   411,    76,   595,   414,   415,   466,   467,
      83,   557,   602,    78,   557,    78,    78,    38,   557,    83,
     547,    76,     3,   613,    77,    81,    78,   557,    78,    78,
     557,   439,   589,   623,    53,    54,    38,    38,    57,    58,
      59,    60,     3,     4,     5,     6,     7,   623,    48,    49,
      50,    51,    52,   151,    78,   645,    81,    76,   156,   157,
     587,    10,   589,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,    78,    83,   667,    38,    78,
     488,    58,    58,   673,    58,    38,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    77,    77,     1,     7,     3,     4,
       5,     6,     7,     8,     9,   523,    11,    12,    13,    14,
      15,    38,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    77,    33,    34,
      77,    16,     5,     6,     7,    40,    78,    58,    43,    12,
      13,    14,    77,    48,    49,    50,    77,    58,    53,    54,
     568,    76,    17,    58,   262,   263,    76,    30,    77,    77,
      76,     4,     5,     6,     7,    77,   584,    76,     9,    12,
      13,    14,    77,    78,    79,    80,     1,    82,     3,     4,
       5,     6,     7,     8,     9,    28,    11,    12,    13,    14,
      15,    77,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    77,    33,    34,
      58,    27,    81,    77,    30,    40,    76,    76,    43,    35,
      77,    77,   572,    48,    49,    50,   334,   294,    53,    54,
     215,   444,    55,    58,   557,   425,   191,   432,   346,   293,
     507,   462,    58,    59,    45,    46,    47,    48,    49,    50,
      51,    52,    77,   337,    79,    80,     1,    82,     3,     4,
     239,    77,   434,     8,     9,    81,    11,   247,   329,   623,
      15,   379,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,   335,    29,   444,    31,   396,    33,    34,
     398,   446,   670,   623,   668,    40,   288,    -1,    43,   369,
      -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,    -1,     1,    58,     3,     4,    -1,    -1,    -1,     8,
       9,    -1,    11,    -1,   432,    46,    47,    48,    49,    50,
      51,    52,    77,    78,    79,    80,    -1,    82,    -1,    -1,
      29,    -1,    31,    -1,    33,    34,   454,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,   463,   464,    -1,    -1,    48,
      49,    50,    -1,    -1,    53,    54,    -1,    -1,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,   484,    -1,    -1,   487,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    78,
      79,    80,    -1,    82,    -1,    -1,   504,    -1,    -1,   507,
      -1,   509,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,     1,    -1,     3,     4,   524,    -1,    -1,     8,
       9,    -1,    11,    -1,    -1,    -1,    15,   535,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      29,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
     558,    40,    -1,   561,    43,    -1,    -1,    -1,    -1,    48,
      49,    50,    -1,    -1,    53,    54,    -1,    -1,     1,    58,
      -1,     4,    -1,     6,     7,    -1,    -1,    -1,    -1,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      79,    80,    -1,    82,     1,    28,     3,     4,    31,    -1,
     608,     8,     9,    -1,    11,    -1,    -1,    -1,    15,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    29,    -1,    31,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    48,    49,    50,    77,    78,    53,    54,    -1,    -1,
       1,    58,     3,     4,    -1,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    79,    80,    -1,    82,    -1,    28,    29,    -1,
      31,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    -1,    53,    54,    -1,    -1,     1,    58,     3,     4,
      -1,    -1,    -1,     8,     9,    -1,    11,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    12,    13,    14,    79,    80,
      -1,    82,    -1,    -1,    29,    -1,    31,    -1,    33,    34,
      -1,    28,    -1,    30,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,    -1,    57,    58,    59,     1,    -1,     3,    -1,    -1,
      -1,    -1,     8,     9,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    79,    80,    -1,    82,    -1,    -1,
      77,    -1,    -1,    29,    -1,    31,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,    -1,
      -1,    57,    58,    59,     1,    -1,     3,    -1,    -1,    -1,
      -1,     8,     9,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    80,    -1,    82,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    31,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    -1,    53,    54,     1,    -1,
       3,    58,    -1,    -1,    -1,     8,     9,     1,    11,    -1,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    12,    13,
      14,    -1,    79,    80,    -1,    82,    29,    -1,    31,    -1,
      33,    34,    -1,    27,    28,    -1,    30,    40,    -1,    -1,
      43,    35,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,
      53,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    -1,    -1,    -1,     1,
      -1,    -1,     4,     5,     6,     7,    79,    80,    -1,    82,
      12,    13,    14,    77,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    -1,    30,    -1,
      -1,    -1,     1,    35,    -1,     4,     5,     6,     7,    -1,
      -1,     3,    -1,    12,    13,    14,     8,     9,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    27,    28,
      -1,    30,    -1,    -1,    -1,    -1,    35,    29,    -1,    31,
      -1,    33,    34,    -1,    -1,    77,    -1,    -1,    40,    81,
      82,    43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    53,    54,    -1,     3,    -1,    58,    -1,    -1,     8,
       9,    -1,    11,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    79,    80,    -1,
      29,    83,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,
      49,    50,    -1,    -1,    53,    54,    -1,     3,    -1,    58,
      -1,    -1,     8,     9,     1,    11,     3,     4,     5,     6,
       7,    -1,    -1,    10,    -1,    12,    13,    14,    -1,    -1,
      79,    80,    -1,    29,    83,    31,    -1,    33,    34,    -1,
      -1,    28,    -1,    30,    40,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,    -1,
       3,    -1,    58,    -1,    -1,     8,     9,     1,    11,    -1,
       4,     5,     6,     7,    -1,    -1,    10,    -1,    12,    13,
      14,    -1,    -1,    79,    80,    -1,    29,    83,    31,    76,
      33,    34,    -1,    -1,    28,    -1,    30,    40,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,
      53,    54,    -1,     3,    -1,    58,    -1,    -1,     8,     9,
      -1,    11,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      12,    13,    14,    -1,    -1,    -1,    79,    80,    -1,    29,
      83,    31,    76,    33,    34,    -1,    28,    -1,    30,    -1,
      40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,
      50,    -1,    -1,    53,    54,    -1,     3,    -1,    58,    -1,
      -1,     8,     9,    -1,    11,    -1,     4,    -1,     6,     7,
      -1,    -1,    -1,    -1,    12,    13,    14,    -1,    -1,    79,
      80,    -1,    29,    83,    31,    77,    33,    34,    -1,    -1,
      28,    -1,    30,    40,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    -1,    53,    54,    -1,     3,
      -1,    58,    50,    -1,     8,     9,    -1,    11,    -1,    -1,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,    -1,    29,    83,    31,    -1,    33,
      34,    -1,     4,     5,     6,     7,    40,    -1,    10,    43,
      12,    13,    14,    -1,    48,    49,    50,    -1,    -1,    53,
      54,    -1,    -1,    -1,    58,    -1,    28,    37,    30,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    -1,    79,    80,    -1,    -1,    83,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    34,    -1,     4,     5,     6,     7,    40,    -1,    -1,
      43,    12,    13,    14,    -1,    48,    49,    50,    -1,    -1,
      53,    54,    -1,    -1,    -1,    58,    -1,    28,    -1,    30,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    77,    -1,    79,    80,    -1,    82,
       3,     4,    -1,    -1,    -1,     8,     9,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    29,    -1,    31,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,
      53,    54,     3,    -1,    -1,    58,    -1,     8,     9,    -1,
      11,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    77,    -1,    79,    80,    29,    82,
      31,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    -1,    53,    54,    -1,    -1,    -1,    58,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,
      -1,    82,    -1,    28,    29,    30,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,     3,     4,    58,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    79,    80,    28,    29,    -1,    31,
      -1,    33,    34,    -1,     3,    -1,    -1,    -1,    40,     8,
       9,    43,    11,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    53,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      29,    -1,    31,    -1,    33,    34,    -1,     3,    -1,    -1,
      -1,    40,     8,     9,    43,    11,    -1,    79,    80,    48,
      49,    50,    -1,    -1,    53,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    29,    -1,    31,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    77,    -1,
      79,    80,    48,    49,    50,    -1,    -1,    53,    54,     3,
      -1,    -1,    58,    -1,     8,     9,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    80,    29,    -1,    31,    -1,    33,
      34,    -1,     3,    -1,    -1,    -1,    40,     8,     9,    43,
      11,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,
      54,    -1,    -1,    -1,    58,    -1,    -1,    -1,    29,    -1,
      31,    -1,    33,    34,    -1,     3,    -1,    -1,    -1,    40,
       8,     9,    43,    11,    -1,    79,    80,    48,    49,    50,
      -1,    -1,    53,    54,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    29,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    43,    -1,    -1,    79,    80,
      48,    49,    50,    -1,    -1,    53,    54,    -1,    -1,     1,
      58,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    80,    -1,    -1,    27,    28,    -1,    30,    31,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    35,    36,    37,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    77,    35,    36,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    35,    36,    37,    83,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    83,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    35,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    85,    86,    87,     0,    88,     1,     4,     5,     6,
       7,    12,    13,    14,    27,    28,    30,    31,    77,    89,
      90,    91,   123,   126,   130,   131,   134,   144,   145,   169,
     170,   171,   172,   241,    89,    77,    78,   144,   144,   144,
      58,    58,    58,     3,    50,    58,   137,   141,   144,   168,
      77,   123,    77,   123,   131,   134,   144,     5,     7,   127,
     145,     3,     4,    82,    98,    82,    98,    82,    98,    89,
       3,     8,     9,    11,    29,    33,    34,    40,    43,    48,
      49,    50,    53,    54,    58,    79,    80,    99,   100,   102,
     103,   104,   105,   106,   108,   114,   116,   241,     7,   100,
     132,   134,   186,   188,    58,   189,   168,    77,    81,   124,
       1,    27,    58,    59,    96,   138,     4,    50,    58,   136,
     139,   144,   165,   166,   168,   137,   168,   127,     5,     6,
       7,   135,   144,   172,   179,   180,    82,   179,    82,   176,
      82,   106,   106,    98,   106,     1,   100,   115,   186,   106,
      76,    81,    58,   103,    58,   103,    35,    36,    37,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    57,    58,    59,    60,     9,
     106,    76,    50,    58,    59,   144,   187,   190,   133,    76,
       7,   134,   187,     5,     6,     7,    98,   146,   147,   148,
       7,   168,    76,   139,   165,   168,    58,   236,   237,    50,
      83,   100,     1,   117,   118,   119,   194,   206,   143,   144,
     189,   166,    77,    81,   124,     1,    92,   138,    58,    59,
      77,     1,    94,    78,     1,    77,   132,   181,   188,   241,
     173,    78,   174,     1,    98,   184,   185,   175,    76,    76,
      82,   200,   201,    76,    77,   108,   186,   186,   108,   108,
     111,   113,   110,   109,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,    98,   101,   102,   100,
      98,   189,   190,   229,   230,    83,   100,   124,    58,    59,
     135,   133,    76,    81,    58,   116,     1,     3,    10,   126,
     130,   231,   233,   234,   235,   238,   239,    83,    83,    77,
      97,   194,    10,   118,   207,    35,   166,    76,   139,   166,
     117,   143,   236,    83,   100,   117,   143,   123,    77,   123,
     181,   179,   143,   179,    35,    81,   178,   184,    78,   195,
      76,    82,   106,    76,    76,   100,    38,   108,   108,    76,
      83,   190,    76,   231,    83,   190,   229,    83,   100,    76,
     147,     3,   101,    76,    76,   123,   123,    76,    77,    81,
      76,    81,     1,   199,   201,   120,   128,   131,   134,   142,
      93,    35,    83,    95,   182,   183,   206,   182,    78,    78,
     108,   185,    78,   178,    32,   196,   197,   198,   107,    38,
     108,    83,    76,    81,    76,     4,    50,    58,   144,   167,
     168,   187,    50,   144,   168,   187,   232,    10,   235,     3,
     201,    77,   123,    77,   123,   134,   129,     1,    82,   108,
     149,   199,   140,   199,    81,   207,   143,   143,   143,    78,
      98,   240,     1,   121,   122,   191,   192,   194,   206,   209,
     198,     1,     3,    57,    59,    82,    98,   108,   151,   152,
     153,   155,   157,   158,   112,   102,   189,   124,    58,    59,
     143,   143,   143,   189,   124,   143,   143,   231,   136,   137,
     168,   129,     5,   135,   150,   149,   183,    38,   165,   143,
      77,    81,    78,   194,   121,   191,   193,    78,   194,   206,
     209,   207,    98,   108,   156,    38,    78,    81,   177,    35,
     158,   155,   108,    76,   167,   167,   236,    50,    83,   100,
      77,    77,   151,   108,    38,   143,    98,    78,   207,     4,
      15,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    77,    98,   100,   125,   126,   130,   201,   202,
     203,   204,   210,   211,   219,   220,   222,   241,    10,    83,
     151,   154,   153,   155,    83,    83,    78,   143,   108,    58,
     213,   205,    58,    58,   108,    38,    77,    77,    77,   100,
      50,    98,     7,   223,    38,    77,    77,   123,    77,   123,
      16,     1,   206,   208,     1,    58,   125,   108,    78,   155,
     143,   100,    58,   208,   100,   114,   224,   100,    10,    38,
      77,   100,    77,    58,   143,   136,   159,   165,   137,   162,
     168,     1,   212,   207,   100,    83,    76,   100,    17,    76,
      77,    76,   108,    77,   100,    77,   160,    77,   163,   208,
     211,   222,    76,    76,   221,   215,   218,    38,    38,    76,
     117,   117,   208,    77,   214,   208,   224,   208,     9,   225,
     226,   227,    77,   161,   164,   208,    77,    58,    38,    76,
      81,   201,   201,   216,   100,   225,    77,   227,   224,    76,
      38,    76,    76,   116,   228,    77,   217,    76,    81,   208,
      77,   116
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = (yytype_int16)yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T)(yyssp - yyss + 1);

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 234 "c-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids an empty source file");
		  finish_file ();
		}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 239 "c-parse.y"
    {
		  /* In case there were missing closebraces,
		     get us back to the global binding level.  */
		  while (! global_bindings_p ())
		    poplevel (0, 0, 0);
		  finish_file ();
		}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 253 "c-parse.y"
    {(yyval.ttype) = NULL_TREE; }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 254 "c-parse.y"
    {(yyval.ttype) = NULL_TREE; }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 261 "c-parse.y"
    { STRIP_NOPS ((yyvsp[(3) - (5)].ttype));
		  if ((TREE_CODE ((yyvsp[(3) - (5)].ttype)) == ADDR_EXPR
		       && TREE_CODE (TREE_OPERAND ((yyvsp[(3) - (5)].ttype), 0)) == STRING_CST)
		      || TREE_CODE ((yyvsp[(3) - (5)].ttype)) == STRING_CST)
		    assemble_asm ((yyvsp[(3) - (5)].ttype));
		  else
		    error ("argument of `asm' is not a constant string"); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 269 "c-parse.y"
    { pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 274 "c-parse.y"
    { if (pedantic)
		    error ("ANSI C forbids data definition with no type or storage class");
		  else if (!flag_traditional)
		    warning ("data definition has no type or storage class"); 

		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(1) - (3)].itype)); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 284 "c-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 289 "c-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype));  }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 294 "c-parse.y"
    { pedwarn ("empty declaration"); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 296 "c-parse.y"
    { shadow_tag ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 300 "c-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C does not allow extra `;' outside of a function"); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 306 "c-parse.y"
    { if (! start_function (current_declspecs, (yyvsp[(3) - (3)].ttype),
					prefix_attributes, NULL_TREE, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 311 "c-parse.y"
    { store_parm_decls (); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 313 "c-parse.y"
    { finish_function (0); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (7)].itype)); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 319 "c-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 324 "c-parse.y"
    { if (! start_function (current_declspecs, (yyvsp[(3) - (3)].ttype),
					prefix_attributes, NULL_TREE, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 329 "c-parse.y"
    { store_parm_decls (); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 331 "c-parse.y"
    { finish_function (0); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (7)].itype)); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 337 "c-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 342 "c-parse.y"
    { if (! start_function (NULL_TREE, (yyvsp[(2) - (2)].ttype),
					prefix_attributes, NULL_TREE, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 347 "c-parse.y"
    { store_parm_decls (); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 349 "c-parse.y"
    { finish_function (0); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(1) - (6)].itype)); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 355 "c-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(1) - (3)].itype)); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 367 "c-parse.y"
    { (yyval.code) = ADDR_EXPR; }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 369 "c-parse.y"
    { (yyval.code) = NEGATE_EXPR; }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 371 "c-parse.y"
    { (yyval.code) = CONVERT_EXPR; }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 373 "c-parse.y"
    { (yyval.code) = PREINCREMENT_EXPR; }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 375 "c-parse.y"
    { (yyval.code) = PREDECREMENT_EXPR; }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 377 "c-parse.y"
    { (yyval.code) = BIT_NOT_EXPR; }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 379 "c-parse.y"
    { (yyval.code) = TRUTH_NOT_EXPR; }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 383 "c-parse.y"
    { (yyval.ttype) = build_compound_expr ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 388 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 394 "c-parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ttype)); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 396 "c-parse.y"
    { chainon ((yyvsp[(1) - (3)].ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (3)].ttype))); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 402 "c-parse.y"
    { (yyval.ttype) = build_indirect_ref ((yyvsp[(2) - (2)].ttype), "unary *"); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 405 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 408 "c-parse.y"
    { (yyval.ttype) = build_unary_op ((yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].ttype), 0);
		  overflow_warning ((yyval.ttype)); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 412 "c-parse.y"
    { tree label = lookup_label ((yyvsp[(2) - (2)].ttype));
		  if (pedantic)
		    pedwarn ("ANSI C forbids `&&'");
		  if (label == 0)
		    (yyval.ttype) = null_pointer_node;
		  else
		    {
		      TREE_USED (label) = 1;
		      (yyval.ttype) = build1 (ADDR_EXPR, ptr_type_node, label);
		      TREE_CONSTANT ((yyval.ttype)) = 1;
		    }
		}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 440 "c-parse.y"
    { skip_evaluation--;
		  if (TREE_CODE ((yyvsp[(2) - (2)].ttype)) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (TREE_OPERAND ((yyvsp[(2) - (2)].ttype), 1)))
		    error ("`sizeof' applied to a bit-field");
		  (yyval.ttype) = c_sizeof (TREE_TYPE ((yyvsp[(2) - (2)].ttype))); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 446 "c-parse.y"
    { skip_evaluation--;
		  (yyval.ttype) = c_sizeof (groktypename ((yyvsp[(3) - (4)].ttype))); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 449 "c-parse.y"
    { skip_evaluation--;
		  (yyval.ttype) = c_alignof_expr ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 452 "c-parse.y"
    { skip_evaluation--;
		  (yyval.ttype) = c_alignof (groktypename ((yyvsp[(3) - (4)].ttype))); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 455 "c-parse.y"
    { (yyval.ttype) = build_unary_op (REALPART_EXPR, (yyvsp[(2) - (2)].ttype), 0); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 457 "c-parse.y"
    { (yyval.ttype) = build_unary_op (IMAGPART_EXPR, (yyvsp[(2) - (2)].ttype), 0); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 461 "c-parse.y"
    { skip_evaluation++; }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 465 "c-parse.y"
    { skip_evaluation++; }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 471 "c-parse.y"
    { tree type = groktypename ((yyvsp[(2) - (4)].ttype));
		  (yyval.ttype) = build_c_cast (type, (yyvsp[(4) - (4)].ttype)); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 474 "c-parse.y"
    { start_init (NULL_TREE, NULL, 0);
		  (yyvsp[(2) - (4)].ttype) = groktypename ((yyvsp[(2) - (4)].ttype));
		  really_start_incremental_init ((yyvsp[(2) - (4)].ttype)); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 478 "c-parse.y"
    { char *name;
		  tree result = pop_init_level (0);
		  tree type = (yyvsp[(2) - (7)].ttype);
		  finish_init ();

		  if (pedantic && ! flag_isoc9x)
		    pedwarn ("ANSI C forbids constructor expressions");
		  if (TYPE_NAME (type) != 0)
		    {
		      if (TREE_CODE (TYPE_NAME (type)) == IDENTIFIER_NODE)
			name = IDENTIFIER_POINTER (TYPE_NAME (type));
		      else
			name = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (type)));
		    }
		  else
		    name = "";
		  (yyval.ttype) = result;
		  if (TREE_CODE (type) == ARRAY_TYPE && TYPE_SIZE (type) == 0)
		    {
		      int failure = complete_array_type (type, (yyval.ttype), 1);
		      if (failure)
			abort ();
		    }
		}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 507 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 509 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 511 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 513 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 515 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 517 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 519 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 521 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 523 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 525 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 527 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 529 "c-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 531 "c-parse.y"
    { (yyvsp[(1) - (2)].ttype) = truthvalue_conversion (default_conversion ((yyvsp[(1) - (2)].ttype)));
		  skip_evaluation += (yyvsp[(1) - (2)].ttype) == boolean_false_node; }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 534 "c-parse.y"
    { skip_evaluation -= (yyvsp[(1) - (4)].ttype) == boolean_false_node;
		  (yyval.ttype) = parser_build_binary_op (TRUTH_ANDIF_EXPR, (yyvsp[(1) - (4)].ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 537 "c-parse.y"
    { (yyvsp[(1) - (2)].ttype) = truthvalue_conversion (default_conversion ((yyvsp[(1) - (2)].ttype)));
		  skip_evaluation += (yyvsp[(1) - (2)].ttype) == boolean_true_node; }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 540 "c-parse.y"
    { skip_evaluation -= (yyvsp[(1) - (4)].ttype) == boolean_true_node;
		  (yyval.ttype) = parser_build_binary_op (TRUTH_ORIF_EXPR, (yyvsp[(1) - (4)].ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 543 "c-parse.y"
    { (yyvsp[(1) - (2)].ttype) = truthvalue_conversion (default_conversion ((yyvsp[(1) - (2)].ttype)));
		  skip_evaluation += (yyvsp[(1) - (2)].ttype) == boolean_false_node; }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 546 "c-parse.y"
    { skip_evaluation += (((yyvsp[(1) - (5)].ttype) == boolean_true_node)
				      - ((yyvsp[(1) - (5)].ttype) == boolean_false_node)); }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 549 "c-parse.y"
    { skip_evaluation -= (yyvsp[(1) - (7)].ttype) == boolean_true_node;
		  (yyval.ttype) = build_conditional_expr ((yyvsp[(1) - (7)].ttype), (yyvsp[(4) - (7)].ttype), (yyvsp[(7) - (7)].ttype)); }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 552 "c-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids omitting the middle term of a ?: expression");
		  /* Make sure first operand is calculated only once.  */
		  (yyvsp[(2) - (2)].ttype) = save_expr ((yyvsp[(1) - (2)].ttype));
		  (yyvsp[(1) - (2)].ttype) = truthvalue_conversion (default_conversion ((yyvsp[(2) - (2)].ttype)));
		  skip_evaluation += (yyvsp[(1) - (2)].ttype) == boolean_true_node; }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 559 "c-parse.y"
    { skip_evaluation -= (yyvsp[(1) - (5)].ttype) == boolean_true_node;
		  (yyval.ttype) = build_conditional_expr ((yyvsp[(1) - (5)].ttype), (yyvsp[(2) - (5)].ttype), (yyvsp[(5) - (5)].ttype)); }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 562 "c-parse.y"
    { char class;
		  (yyval.ttype) = build_modify_expr ((yyvsp[(1) - (3)].ttype), NOP_EXPR, (yyvsp[(3) - (3)].ttype));
		  class = TREE_CODE_CLASS (TREE_CODE ((yyval.ttype)));
		  if (class == 'e' || class == '1'
		      || class == '2' || class == '<')
		    C_SET_EXP_ORIGINAL_CODE ((yyval.ttype), MODIFY_EXPR);
		}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 570 "c-parse.y"
    { char class;
		  (yyval.ttype) = build_modify_expr ((yyvsp[(1) - (3)].ttype), (yyvsp[(2) - (3)].code), (yyvsp[(3) - (3)].ttype));
		  /* This inhibits warnings in truthvalue_conversion.  */
		  class = TREE_CODE_CLASS (TREE_CODE ((yyval.ttype)));
		  if (class == 'e' || class == '1'
		      || class == '2' || class == '<')
		    C_SET_EXP_ORIGINAL_CODE ((yyval.ttype), ERROR_MARK);
		}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 582 "c-parse.y"
    {
		  (yyval.ttype) = lastiddecl;
		  if (!(yyval.ttype) || (yyval.ttype) == error_mark_node)
		    {
		      if (yychar == YYEMPTY)
			yychar = YYLEX;
		      if (yychar == '(')
			{
			    {
			      /* Ordinary implicit function declaration.  */
			      (yyval.ttype) = implicitly_declare ((yyvsp[(1) - (1)].ttype));
			      assemble_external ((yyval.ttype));
			      TREE_USED ((yyval.ttype)) = 1;
			    }
			}
		      else if (current_function_decl == 0)
			{
			  error ("`%s' undeclared here (not in a function)",
				 IDENTIFIER_POINTER ((yyvsp[(1) - (1)].ttype)));
			  (yyval.ttype) = error_mark_node;
			}
		      else
			{
			    {
			      if (IDENTIFIER_GLOBAL_VALUE ((yyvsp[(1) - (1)].ttype)) != error_mark_node
				  || IDENTIFIER_ERROR_LOCUS ((yyvsp[(1) - (1)].ttype)) != current_function_decl)
				{
				  error ("`%s' undeclared (first use in this function)",
					 IDENTIFIER_POINTER ((yyvsp[(1) - (1)].ttype)));

				  if (! undeclared_variable_notice)
				    {
				      error ("(Each undeclared identifier is reported only once");
				      error ("for each function it appears in.)");
				      undeclared_variable_notice = 1;
				    }
				}
			      (yyval.ttype) = error_mark_node;
			      /* Prevent repeated error messages.  */
			      IDENTIFIER_GLOBAL_VALUE ((yyvsp[(1) - (1)].ttype)) = error_mark_node;
			      IDENTIFIER_ERROR_LOCUS ((yyvsp[(1) - (1)].ttype)) = current_function_decl;
			    }
			}
		    }
		  else if (TREE_TYPE ((yyval.ttype)) == error_mark_node)
		    (yyval.ttype) = error_mark_node;
		  else if (C_DECL_ANTICIPATED ((yyval.ttype)))
		    {
		      /* The first time we see a build-in function used,
			 if it has not been declared.  */
		      C_DECL_ANTICIPATED ((yyval.ttype)) = 0;
		      if (yychar == YYEMPTY)
			yychar = YYLEX;
		      if (yychar == '(')
			{
			  /* Omit the implicit declaration we
			     would ordinarily do, so we don't lose
			     the actual built in type.
			     But print a diagnostic for the mismatch.  */
			    if (TREE_CODE ((yyval.ttype)) != FUNCTION_DECL)
			      error ("`%s' implicitly declared as function",
				     IDENTIFIER_POINTER (DECL_NAME ((yyval.ttype))));
			  else if ((TYPE_MODE (TREE_TYPE (TREE_TYPE ((yyval.ttype))))
				    != TYPE_MODE (integer_type_node))
				   && (TREE_TYPE (TREE_TYPE ((yyval.ttype)))
				       != void_type_node))
			    pedwarn ("type mismatch in implicit declaration for built-in function `%s'",
				     IDENTIFIER_POINTER (DECL_NAME ((yyval.ttype))));
			  /* If it really returns void, change that to int.  */
			  if (TREE_TYPE (TREE_TYPE ((yyval.ttype))) == void_type_node)
			    TREE_TYPE ((yyval.ttype))
			      = build_function_type (integer_type_node,
						     TYPE_ARG_TYPES (TREE_TYPE ((yyval.ttype))));
			}
		      else
			pedwarn ("built-in function `%s' used without declaration",
				 IDENTIFIER_POINTER (DECL_NAME ((yyval.ttype))));

		      /* Do what we would ordinarily do when a fn is used.  */
		      assemble_external ((yyval.ttype));
		      TREE_USED ((yyval.ttype)) = 1;
		    }
		  else
		    {
		      assemble_external ((yyval.ttype));
		      TREE_USED ((yyval.ttype)) = 1;
		    }

		  if (TREE_CODE ((yyval.ttype)) == CONST_DECL)
		    {
		      (yyval.ttype) = DECL_INITIAL ((yyval.ttype));
		      /* This is to prevent an enum whose value is 0
			 from being considered a null pointer constant.  */
		      (yyval.ttype) = build1 (NOP_EXPR, TREE_TYPE ((yyval.ttype)), (yyval.ttype));
		      TREE_CONSTANT ((yyval.ttype)) = 1;
		    }
		}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 681 "c-parse.y"
    { (yyval.ttype) = combine_strings ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 683 "c-parse.y"
    { char class = TREE_CODE_CLASS (TREE_CODE ((yyvsp[(2) - (3)].ttype)));
		  if (class == 'e' || class == '1'
		      || class == '2' || class == '<')
		    C_SET_EXP_ORIGINAL_CODE ((yyvsp[(2) - (3)].ttype), ERROR_MARK);
		  (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 689 "c-parse.y"
    { (yyval.ttype) = error_mark_node; }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 691 "c-parse.y"
    { if (current_function_decl == 0)
		    {
		      error ("braced-group within expression allowed only inside a function");
		      YYERROR;
		    }
		  /* We must force a BLOCK for this level
		     so that, if it is not expanded later,
		     there is a way to turn off the entire subtree of blocks
		     that are contained in it.  */
		  keep_next_level ();
		  push_iterator_stack ();
		  push_label_level ();
		  (yyval.ttype) = expand_start_stmt_expr (); }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 705 "c-parse.y"
    { tree rtl_exp;
		  if (pedantic)
		    pedwarn ("ANSI C forbids braced-groups within expressions");
		  pop_iterator_stack ();
		  pop_label_level ();
		  rtl_exp = expand_end_stmt_expr ((yyvsp[(2) - (4)].ttype));
		  /* The statements have side effects, so the group does.  */
		  TREE_SIDE_EFFECTS (rtl_exp) = 1;

		  if (TREE_CODE ((yyvsp[(3) - (4)].ttype)) == BLOCK)
		    {
		      /* Make a BIND_EXPR for the BLOCK already made.  */
		      (yyval.ttype) = build (BIND_EXPR, TREE_TYPE (rtl_exp),
				  NULL_TREE, rtl_exp, (yyvsp[(3) - (4)].ttype));
		      /* Remove the block from the tree at this point.
			 It gets put back at the proper place
			 when the BIND_EXPR is expanded.  */
		      delete_block ((yyvsp[(3) - (4)].ttype));
		    }
		  else
		    (yyval.ttype) = (yyvsp[(3) - (4)].ttype);
		}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 728 "c-parse.y"
    { (yyval.ttype) = build_function_call ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 730 "c-parse.y"
    { (yyval.ttype) = build_array_ref ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 732 "c-parse.y"
    {
		    (yyval.ttype) = build_component_ref ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 736 "c-parse.y"
    {
                  tree expr = build_indirect_ref ((yyvsp[(1) - (3)].ttype), "->");

                    (yyval.ttype) = build_component_ref (expr, (yyvsp[(3) - (3)].ttype));
		}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 742 "c-parse.y"
    { (yyval.ttype) = build_unary_op (POSTINCREMENT_EXPR, (yyvsp[(1) - (2)].ttype), 0); }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 744 "c-parse.y"
    { (yyval.ttype) = build_unary_op (POSTDECREMENT_EXPR, (yyvsp[(1) - (2)].ttype), 0); }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 751 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 760 "c-parse.y"
    { c_mark_varargs ();
		  if (pedantic)
		    pedwarn ("ANSI C does not permit use of `varargs.h'"); }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 770 "c-parse.y"
    { }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 786 "c-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 791 "c-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);	
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 796 "c-parse.y"
    { shadow_tag_warned ((yyvsp[(1) - (2)].ttype), 1);
		  pedwarn ("empty declaration"); }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 799 "c-parse.y"
    { pedwarn ("empty declaration"); }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 808 "c-parse.y"
    { }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 823 "c-parse.y"
    { (yyval.itype) = suspend_momentary ();
		  pending_xref_error ();
		  declspec_stack = tree_cons (prefix_attributes,
					      current_declspecs,
					      declspec_stack);
		  split_specs_attrs ((yyvsp[(0) - (0)].ttype),
				     &current_declspecs, &prefix_attributes); }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 834 "c-parse.y"
    { prefix_attributes = chainon (prefix_attributes, (yyvsp[(0) - (0)].ttype)); }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 839 "c-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 844 "c-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 849 "c-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (3)].itype)); }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 854 "c-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (3)].itype)); }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 859 "c-parse.y"
    { shadow_tag ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 861 "c-parse.y"
    { pedwarn ("empty declaration"); }
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 863 "c-parse.y"
    { pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 873 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 875 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(3) - (3)].ttype), tree_cons (NULL_TREE, (yyvsp[(2) - (3)].ttype), (yyvsp[(1) - (3)].ttype))); }
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 879 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 881 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 883 "c-parse.y"
    { if (extra_warnings)
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyvsp[(2) - (2)].ttype)));
		  (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 888 "c-parse.y"
    { (yyval.ttype) = tree_cons ((yyvsp[(2) - (2)].ttype), NULL_TREE, (yyvsp[(1) - (2)].ttype)); }
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 893 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 895 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(3) - (3)].ttype), tree_cons (NULL_TREE, (yyvsp[(2) - (3)].ttype), (yyvsp[(1) - (3)].ttype))); }
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 900 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 902 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 904 "c-parse.y"
    { if (extra_warnings)
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyvsp[(2) - (2)].ttype)));
		  (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 917 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 919 "c-parse.y"
    { (yyval.ttype) = tree_cons ((yyvsp[(1) - (1)].ttype), NULL_TREE, NULL_TREE); }
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 921 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 923 "c-parse.y"
    { (yyval.ttype) = tree_cons ((yyvsp[(2) - (2)].ttype), NULL_TREE, (yyvsp[(1) - (2)].ttype)); }
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 928 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (1)].ttype), NULL_TREE);
		  TREE_STATIC ((yyval.ttype)) = 1; }
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 931 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (1)].ttype), NULL_TREE); }
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 933 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype));
		  TREE_STATIC ((yyval.ttype)) = 1; }
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 936 "c-parse.y"
    { if (extra_warnings && TREE_STATIC ((yyvsp[(1) - (2)].ttype)))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyvsp[(2) - (2)].ttype)));
		  (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype));
		  TREE_STATIC ((yyval.ttype)) = TREE_STATIC ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 950 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 952 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(3) - (3)].ttype), tree_cons (NULL_TREE, (yyvsp[(2) - (3)].ttype), (yyvsp[(1) - (3)].ttype))); }
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 956 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 958 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 968 "c-parse.y"
    { /* For a typedef name, record the meaning, not the name.
		     In case of `foo foo, bar;'.  */
		  (yyval.ttype) = lookup_name ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 972 "c-parse.y"
    { (yyval.ttype) = TREE_TYPE ((yyvsp[(3) - (4)].ttype)); }
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 974 "c-parse.y"
    { (yyval.ttype) = groktypename ((yyvsp[(3) - (4)].ttype)); }
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 996 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 998 "c-parse.y"
    { if (TREE_CHAIN ((yyvsp[(3) - (4)].ttype))) (yyvsp[(3) - (4)].ttype) = combine_strings ((yyvsp[(3) - (4)].ttype));
		  (yyval.ttype) = (yyvsp[(3) - (4)].ttype);
		}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1005 "c-parse.y"
    { (yyval.ttype) = start_decl ((yyvsp[(1) - (4)].ttype), current_declspecs, 1,
					  (yyvsp[(3) - (4)].ttype), prefix_attributes);
		  start_init ((yyval.ttype), (yyvsp[(2) - (4)].ttype), global_bindings_p ()); }
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1010 "c-parse.y"
    { finish_init ();
		  finish_decl ((yyvsp[(5) - (6)].ttype), (yyvsp[(6) - (6)].ttype), (yyvsp[(2) - (6)].ttype)); }
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1013 "c-parse.y"
    { tree d = start_decl ((yyvsp[(1) - (3)].ttype), current_declspecs, 0,
				       (yyvsp[(3) - (3)].ttype), prefix_attributes);
		  finish_decl (d, NULL_TREE, (yyvsp[(2) - (3)].ttype)); 
                }
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1021 "c-parse.y"
    { (yyval.ttype) = start_decl ((yyvsp[(1) - (4)].ttype), current_declspecs, 1,
					  (yyvsp[(3) - (4)].ttype), prefix_attributes);
		  start_init ((yyval.ttype), (yyvsp[(2) - (4)].ttype), global_bindings_p ()); }
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1026 "c-parse.y"
    { finish_init ();
		  decl_attributes ((yyvsp[(5) - (6)].ttype), (yyvsp[(3) - (6)].ttype), prefix_attributes);
		  finish_decl ((yyvsp[(5) - (6)].ttype), (yyvsp[(6) - (6)].ttype), (yyvsp[(2) - (6)].ttype)); }
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1030 "c-parse.y"
    { tree d = start_decl ((yyvsp[(1) - (3)].ttype), current_declspecs, 0,
				       (yyvsp[(3) - (3)].ttype), prefix_attributes);
		  finish_decl (d, NULL_TREE, (yyvsp[(2) - (3)].ttype)); }
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1038 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1040 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1045 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1047 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1052 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(4) - (6)].ttype); }
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1057 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1059 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1064 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1066 "c-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (1)].ttype), NULL_TREE); }
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1068 "c-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (4)].ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (4)].ttype))); }
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1070 "c-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (6)].ttype), tree_cons (NULL_TREE, (yyvsp[(3) - (6)].ttype), (yyvsp[(5) - (6)].ttype))); }
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1072 "c-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1090 "c-parse.y"
    { really_start_incremental_init (NULL_TREE);
		  /* Note that the call to clear_momentary
		     is in process_init_element.  */
		  push_momentary (); }
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1095 "c-parse.y"
    { (yyval.ttype) = pop_init_level (0);
		  if ((yyval.ttype) == error_mark_node
		      && ! (yychar == STRING || yychar == CONSTANT))
		    pop_momentary ();
		  else
		    pop_momentary_nofree (); }
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1103 "c-parse.y"
    { (yyval.ttype) = error_mark_node; }
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1109 "c-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids empty initializer braces"); }
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1125 "c-parse.y"
    { set_init_label ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1132 "c-parse.y"
    { push_init_level (0); }
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1134 "c-parse.y"
    { process_init_element (pop_init_level (0)); }
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1136 "c-parse.y"
    { process_init_element ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1147 "c-parse.y"
    { set_init_label ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1152 "c-parse.y"
    { set_init_index ((yyvsp[(2) - (5)].ttype), (yyvsp[(4) - (5)].ttype)); }
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1154 "c-parse.y"
    { set_init_index ((yyvsp[(2) - (3)].ttype), NULL_TREE); }
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1159 "c-parse.y"
    { push_c_function_context ();
		  if (! start_function (current_declspecs, (yyvsp[(1) - (1)].ttype),
					prefix_attributes, NULL_TREE, 1))
		    {
		      pop_c_function_context ();
		      YYERROR1;
		    }
		  reinit_parse_for_function (); }
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1168 "c-parse.y"
    { store_parm_decls (); }
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1176 "c-parse.y"
    { finish_function (1);
		  pop_c_function_context (); }
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1182 "c-parse.y"
    { push_c_function_context ();
		  if (! start_function (current_declspecs, (yyvsp[(1) - (1)].ttype),
					prefix_attributes, NULL_TREE, 1))
		    {
		      pop_c_function_context ();
		      YYERROR1;
		    }
		  reinit_parse_for_function (); }
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1191 "c-parse.y"
    { store_parm_decls (); }
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1199 "c-parse.y"
    { finish_function (1);
		  pop_c_function_context (); }
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1215 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1217 "c-parse.y"
    { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype), NULL_TREE); }
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1222 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1224 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (3)].ttype), NULL_TREE); }
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1226 "c-parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1233 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1244 "c-parse.y"
    { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype), NULL_TREE); }
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1249 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (4)].ttype), NULL_TREE);
		  if (! flag_isoc9x)
		    error ("`[*]' in parameter declaration only allowed in ISO C 9x");
		}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1254 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1256 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (3)].ttype), NULL_TREE); }
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1258 "c-parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1265 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1274 "c-parse.y"
    { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype), NULL_TREE); }
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1279 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1281 "c-parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1283 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (4)].ttype), NULL_TREE);
		  if (! flag_isoc9x)
		    error ("`[*]' in parameter declaration only allowed in ISO C 9x");
		}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1288 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1290 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (3)].ttype), NULL_TREE); }
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1297 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 1303 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 1305 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 1310 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 1312 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 1317 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1319 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1324 "c-parse.y"
    { (yyval.ttype) = start_struct (RECORD_TYPE, (yyvsp[(2) - (3)].ttype));
		  /* Start scope of tag before parsing components.  */
		}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 1328 "c-parse.y"
    { (yyval.ttype) = finish_struct ((yyvsp[(4) - (7)].ttype), (yyvsp[(5) - (7)].ttype), chainon ((yyvsp[(1) - (7)].ttype), (yyvsp[(7) - (7)].ttype))); }
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 1330 "c-parse.y"
    { (yyval.ttype) = finish_struct (start_struct (RECORD_TYPE, NULL_TREE),
				      (yyvsp[(3) - (5)].ttype), chainon ((yyvsp[(1) - (5)].ttype), (yyvsp[(5) - (5)].ttype)));
		}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 1334 "c-parse.y"
    { (yyval.ttype) = xref_tag (RECORD_TYPE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 1336 "c-parse.y"
    { (yyval.ttype) = start_struct (UNION_TYPE, (yyvsp[(2) - (3)].ttype)); }
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 1338 "c-parse.y"
    { (yyval.ttype) = finish_struct ((yyvsp[(4) - (7)].ttype), (yyvsp[(5) - (7)].ttype), chainon ((yyvsp[(1) - (7)].ttype), (yyvsp[(7) - (7)].ttype))); }
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 1340 "c-parse.y"
    { (yyval.ttype) = finish_struct (start_struct (UNION_TYPE, NULL_TREE),
				      (yyvsp[(3) - (5)].ttype), chainon ((yyvsp[(1) - (5)].ttype), (yyvsp[(5) - (5)].ttype)));
		}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 1344 "c-parse.y"
    { (yyval.ttype) = xref_tag (UNION_TYPE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 1346 "c-parse.y"
    { (yyvsp[(3) - (3)].itype) = suspend_momentary ();
		  (yyval.ttype) = start_enum ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 1349 "c-parse.y"
    { (yyval.ttype)= finish_enum ((yyvsp[(4) - (8)].ttype), nreverse ((yyvsp[(5) - (8)].ttype)), chainon ((yyvsp[(1) - (8)].ttype), (yyvsp[(8) - (8)].ttype)));
		  resume_momentary ((yyvsp[(3) - (8)].itype)); }
    break;

  case 255:
/* Line 1792 of yacc.c  */
#line 1352 "c-parse.y"
    { (yyvsp[(2) - (2)].itype) = suspend_momentary ();
		  (yyval.ttype) = start_enum (NULL_TREE); }
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 1355 "c-parse.y"
    { (yyval.ttype)= finish_enum ((yyvsp[(3) - (7)].ttype), nreverse ((yyvsp[(4) - (7)].ttype)), chainon ((yyvsp[(1) - (7)].ttype), (yyvsp[(7) - (7)].ttype)));
		  resume_momentary ((yyvsp[(2) - (7)].itype)); }
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 1358 "c-parse.y"
    { (yyval.ttype) = xref_tag (ENUMERAL_TYPE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 1369 "c-parse.y"
    { if (pedantic && ! flag_isoc9x)
		    pedwarn ("comma at end of enumerator list"); }
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 1375 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 1377 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype));
		  pedwarn ("no semicolon at end of struct or union"); }
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 1382 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 1384 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), (yyvsp[(2) - (3)].ttype)); }
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 1386 "c-parse.y"
    { if (pedantic)
		    pedwarn ("extra semicolon in struct or union specified"); }
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 1401 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype);
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (3)].itype)); }
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 1407 "c-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids member declarations with no members");
		  shadow_tag((yyvsp[(1) - (1)].ttype));
		  (yyval.ttype) = NULL_TREE; }
    break;

  case 269:
/* Line 1792 of yacc.c  */
#line 1412 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype);
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (3)].itype)); }
    break;

  case 270:
/* Line 1792 of yacc.c  */
#line 1418 "c-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids member declarations with no members");
		  shadow_tag((yyvsp[(1) - (1)].ttype));
		  (yyval.ttype) = NULL_TREE; }
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 1423 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 272:
/* Line 1792 of yacc.c  */
#line 1425 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 1432 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 1437 "c-parse.y"
    { (yyval.ttype) = grokfield ((yyvsp[(1) - (4)].filename), (yyvsp[(2) - (4)].lineno), (yyvsp[(3) - (4)].ttype), current_declspecs, NULL_TREE);
		  decl_attributes ((yyval.ttype), (yyvsp[(4) - (4)].ttype), prefix_attributes); }
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 1441 "c-parse.y"
    { (yyval.ttype) = grokfield ((yyvsp[(1) - (6)].filename), (yyvsp[(2) - (6)].lineno), (yyvsp[(3) - (6)].ttype), current_declspecs, (yyvsp[(5) - (6)].ttype));
		  decl_attributes ((yyval.ttype), (yyvsp[(6) - (6)].ttype), prefix_attributes); }
    break;

  case 277:
/* Line 1792 of yacc.c  */
#line 1444 "c-parse.y"
    { (yyval.ttype) = grokfield ((yyvsp[(1) - (5)].filename), (yyvsp[(2) - (5)].lineno), NULL_TREE, current_declspecs, (yyvsp[(4) - (5)].ttype));
		  decl_attributes ((yyval.ttype), (yyvsp[(5) - (5)].ttype), prefix_attributes); }
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 1456 "c-parse.y"
    { if ((yyvsp[(1) - (3)].ttype) == error_mark_node)
		    (yyval.ttype) = (yyvsp[(1) - (3)].ttype);
		  else
		    (yyval.ttype) = chainon ((yyvsp[(3) - (3)].ttype), (yyvsp[(1) - (3)].ttype)); }
    break;

  case 280:
/* Line 1792 of yacc.c  */
#line 1461 "c-parse.y"
    { (yyval.ttype) = error_mark_node; }
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 1467 "c-parse.y"
    { (yyval.ttype) = build_enumerator ((yyvsp[(1) - (1)].ttype), NULL_TREE); }
    break;

  case 282:
/* Line 1792 of yacc.c  */
#line 1469 "c-parse.y"
    { (yyval.ttype) = build_enumerator ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 283:
/* Line 1792 of yacc.c  */
#line 1474 "c-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 284:
/* Line 1792 of yacc.c  */
#line 1476 "c-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 285:
/* Line 1792 of yacc.c  */
#line 1481 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 287:
/* Line 1792 of yacc.c  */
#line 1487 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (1)].ttype), NULL_TREE); }
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 1489 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 289:
/* Line 1792 of yacc.c  */
#line 1494 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 1496 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 291:
/* Line 1792 of yacc.c  */
#line 1501 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 292:
/* Line 1792 of yacc.c  */
#line 1504 "c-parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 293:
/* Line 1792 of yacc.c  */
#line 1506 "c-parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (2)].ttype), NULL_TREE); }
    break;

  case 294:
/* Line 1792 of yacc.c  */
#line 1508 "c-parse.y"
    { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype), NULL_TREE); }
    break;

  case 295:
/* Line 1792 of yacc.c  */
#line 1510 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 296:
/* Line 1792 of yacc.c  */
#line 1512 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (3)].ttype), NULL_TREE); }
    break;

  case 297:
/* Line 1792 of yacc.c  */
#line 1514 "c-parse.y"
    { (yyval.ttype) = build_nt (CALL_EXPR, NULL_TREE, (yyvsp[(2) - (2)].ttype), NULL_TREE); }
    break;

  case 298:
/* Line 1792 of yacc.c  */
#line 1516 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, NULL_TREE, (yyvsp[(2) - (3)].ttype)); }
    break;

  case 299:
/* Line 1792 of yacc.c  */
#line 1518 "c-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, NULL_TREE, NULL_TREE); }
    break;

  case 300:
/* Line 1792 of yacc.c  */
#line 1522 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 301:
/* Line 1792 of yacc.c  */
#line 1531 "c-parse.y"
    {
		  if (pedantic && (yyvsp[(1) - (1)].ends_in_label))
		    pedwarn ("ANSI C forbids label at end of compound statement");
		}
    break;

  case 303:
/* Line 1792 of yacc.c  */
#line 1540 "c-parse.y"
    { (yyval.ends_in_label) = (yyvsp[(2) - (2)].ends_in_label); }
    break;

  case 304:
/* Line 1792 of yacc.c  */
#line 1542 "c-parse.y"
    { (yyval.ends_in_label) = 0; }
    break;

  case 308:
/* Line 1792 of yacc.c  */
#line 1554 "c-parse.y"
    { emit_line_note (input_filename, lineno);
		  pushlevel (0);
		  clear_last_expr ();
		  push_momentary ();
		  expand_start_bindings (0);
		}
    break;

  case 310:
/* Line 1792 of yacc.c  */
#line 1567 "c-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids label declarations"); }
    break;

  case 313:
/* Line 1792 of yacc.c  */
#line 1578 "c-parse.y"
    { tree link;
		  for (link = (yyvsp[(2) - (3)].ttype); link; link = TREE_CHAIN (link))
		    {
		      tree label = shadow_label (TREE_VALUE (link));
		      C_DECLARED_LABEL_FLAG (label) = 1;
		      declare_nonlocal_label (label);
		    }
		}
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 1592 "c-parse.y"
    {}
    break;

  case 316:
/* Line 1792 of yacc.c  */
#line 1596 "c-parse.y"
    { compstmt_count++; }
    break;

  case 317:
/* Line 1792 of yacc.c  */
#line 1599 "c-parse.y"
    { (yyval.ttype) = convert (void_type_node, integer_zero_node); }
    break;

  case 318:
/* Line 1792 of yacc.c  */
#line 1601 "c-parse.y"
    { emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), 1, 0);
		  (yyval.ttype) = poplevel (1, 1, 0);
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
    break;

  case 319:
/* Line 1792 of yacc.c  */
#line 1609 "c-parse.y"
    { emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), kept_level_p (), 0);
		  (yyval.ttype) = poplevel (kept_level_p (), 0, 0);
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
    break;

  case 320:
/* Line 1792 of yacc.c  */
#line 1617 "c-parse.y"
    { emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), kept_level_p (), 0);
		  (yyval.ttype) = poplevel (kept_level_p (), 0, 0);
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
    break;

  case 323:
/* Line 1792 of yacc.c  */
#line 1637 "c-parse.y"
    { emit_line_note ((yyvsp[(-1) - (4)].filename), (yyvsp[(0) - (4)].lineno));
		  c_expand_start_cond (truthvalue_conversion ((yyvsp[(3) - (4)].ttype)), 0, 
				       compstmt_count);
		  (yyval.itype) = stmt_count;
		  if_stmt_file = (yyvsp[(-1) - (4)].filename);
		  if_stmt_line = (yyvsp[(0) - (4)].lineno);
		  position_after_white_space (); }
    break;

  case 324:
/* Line 1792 of yacc.c  */
#line 1651 "c-parse.y"
    { stmt_count++;
		  compstmt_count++;
		  emit_line_note ((yyvsp[(-1) - (1)].filename), (yyvsp[(0) - (1)].lineno));
		  /* See comment in `while' alternative, above.  */
		  emit_nop ();
		  expand_start_loop_continue_elsewhere (1);
		  position_after_white_space (); }
    break;

  case 325:
/* Line 1792 of yacc.c  */
#line 1659 "c-parse.y"
    { expand_loop_continue_here (); }
    break;

  case 326:
/* Line 1792 of yacc.c  */
#line 1663 "c-parse.y"
    { (yyval.filename) = input_filename; }
    break;

  case 327:
/* Line 1792 of yacc.c  */
#line 1667 "c-parse.y"
    { (yyval.lineno) = lineno; }
    break;

  case 328:
/* Line 1792 of yacc.c  */
#line 1672 "c-parse.y"
    { }
    break;

  case 329:
/* Line 1792 of yacc.c  */
#line 1677 "c-parse.y"
    { }
    break;

  case 330:
/* Line 1792 of yacc.c  */
#line 1682 "c-parse.y"
    { (yyval.ends_in_label) = (yyvsp[(3) - (3)].ends_in_label); }
    break;

  case 331:
/* Line 1792 of yacc.c  */
#line 1687 "c-parse.y"
    { (yyval.ends_in_label) = 0; }
    break;

  case 332:
/* Line 1792 of yacc.c  */
#line 1689 "c-parse.y"
    { (yyval.ends_in_label) = 1; }
    break;

  case 333:
/* Line 1792 of yacc.c  */
#line 1695 "c-parse.y"
    { stmt_count++; }
    break;

  case 335:
/* Line 1792 of yacc.c  */
#line 1698 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (2)].filename), (yyvsp[(0) - (2)].lineno));
/* It appears that this should not be done--that a non-lvalue array
   shouldn't get an error if the value isn't used.
   Section 3.2.2.1 says that an array lvalue gets converted to a pointer
   if it appears as a top-level expression,
   but says nothing about non-lvalue arrays.  */
#if 0
		  /* Call default_conversion to get an error
		     on referring to a register array if pedantic.  */
		  if (TREE_CODE (TREE_TYPE ((yyvsp[(1) - (2)].ttype))) == ARRAY_TYPE
		      || TREE_CODE (TREE_TYPE ((yyvsp[(1) - (2)].ttype))) == FUNCTION_TYPE)
		    (yyvsp[(1) - (2)].ttype) = default_conversion ((yyvsp[(1) - (2)].ttype));
#endif
		  iterator_expand ((yyvsp[(1) - (2)].ttype));
		  clear_momentary (); }
    break;

  case 336:
/* Line 1792 of yacc.c  */
#line 1715 "c-parse.y"
    { c_expand_start_else ();
		  (yyvsp[(1) - (2)].itype) = stmt_count;
		  position_after_white_space (); }
    break;

  case 337:
/* Line 1792 of yacc.c  */
#line 1719 "c-parse.y"
    { c_expand_end_cond ();
		  if (extra_warnings && stmt_count == (yyvsp[(1) - (4)].itype))
		    warning ("empty body in an else-statement"); }
    break;

  case 338:
/* Line 1792 of yacc.c  */
#line 1723 "c-parse.y"
    { c_expand_end_cond ();
		  /* This warning is here instead of in simple_if, because we
		     do not want a warning if an empty if is followed by an
		     else statement.  Increment stmt_count so we don't
		     give a second error if this is a nested `if'.  */
		  if (extra_warnings && stmt_count++ == (yyvsp[(1) - (1)].itype))
		    warning_with_file_and_line (if_stmt_file, if_stmt_line,
						"empty body in an if-statement"); }
    break;

  case 339:
/* Line 1792 of yacc.c  */
#line 1735 "c-parse.y"
    { c_expand_end_cond (); }
    break;

  case 340:
/* Line 1792 of yacc.c  */
#line 1737 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (1)].filename), (yyvsp[(0) - (1)].lineno));
		  /* The emit_nop used to come before emit_line_note,
		     but that made the nop seem like part of the preceding line.
		     And that was confusing when the preceding line was
		     inside of an if statement and was not really executed.
		     I think it ought to work to put the nop after the line number.
		     We will see.  --rms, July 15, 1991.  */
		  emit_nop (); }
    break;

  case 341:
/* Line 1792 of yacc.c  */
#line 1747 "c-parse.y"
    { /* Don't start the loop till we have succeeded
		     in parsing the end test.  This is to make sure
		     that we end every loop we start.  */
		  expand_start_loop (1);
		  emit_line_note (input_filename, lineno);
		  expand_exit_loop_if_false (NULL_PTR,
					     truthvalue_conversion ((yyvsp[(4) - (5)].ttype)));
		  position_after_white_space (); }
    break;

  case 342:
/* Line 1792 of yacc.c  */
#line 1756 "c-parse.y"
    { expand_end_loop (); }
    break;

  case 343:
/* Line 1792 of yacc.c  */
#line 1759 "c-parse.y"
    { emit_line_note (input_filename, lineno);
		  expand_exit_loop_if_false (NULL_PTR,
					     truthvalue_conversion ((yyvsp[(3) - (5)].ttype)));
		  expand_end_loop ();
		  clear_momentary (); }
    break;

  case 344:
/* Line 1792 of yacc.c  */
#line 1766 "c-parse.y"
    { expand_end_loop ();
		  clear_momentary (); }
    break;

  case 345:
/* Line 1792 of yacc.c  */
#line 1770 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (4)].filename), (yyvsp[(0) - (4)].lineno));
		  /* See comment in `while' alternative, above.  */
		  emit_nop ();
		  if ((yyvsp[(3) - (4)].ttype)) c_expand_expr_stmt ((yyvsp[(3) - (4)].ttype));
		  /* Next step is to call expand_start_loop_continue_elsewhere,
		     but wait till after we parse the entire for (...).
		     Otherwise, invalid input might cause us to call that
		     fn without calling expand_end_loop.  */
		}
    break;

  case 346:
/* Line 1792 of yacc.c  */
#line 1782 "c-parse.y"
    { (yyvsp[(7) - (7)].lineno) = lineno;
		  (yyval.filename) = input_filename; }
    break;

  case 347:
/* Line 1792 of yacc.c  */
#line 1785 "c-parse.y"
    { 
		  /* Start the loop.  Doing this after parsing
		     all the expressions ensures we will end the loop.  */
		  expand_start_loop_continue_elsewhere (1);
		  /* Emit the end-test, with a line number.  */
		  emit_line_note ((yyvsp[(8) - (10)].filename), (yyvsp[(7) - (10)].lineno));
		  if ((yyvsp[(6) - (10)].ttype))
		    expand_exit_loop_if_false (NULL_PTR,
					       truthvalue_conversion ((yyvsp[(6) - (10)].ttype)));
		  /* Don't let the tree nodes for $9 be discarded by
		     clear_momentary during the parsing of the next stmt.  */
		  push_momentary ();
		  (yyvsp[(7) - (10)].lineno) = lineno;
		  (yyvsp[(8) - (10)].filename) = input_filename;
		  position_after_white_space (); }
    break;

  case 348:
/* Line 1792 of yacc.c  */
#line 1801 "c-parse.y"
    { /* Emit the increment expression, with a line number.  */
		  emit_line_note ((yyvsp[(8) - (12)].filename), (yyvsp[(7) - (12)].lineno));
		  expand_loop_continue_here ();
		  if ((yyvsp[(9) - (12)].ttype))
		    c_expand_expr_stmt ((yyvsp[(9) - (12)].ttype));
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary ();
		  expand_end_loop (); }
    break;

  case 349:
/* Line 1792 of yacc.c  */
#line 1812 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (4)].filename), (yyvsp[(0) - (4)].lineno));
		  c_expand_start_case ((yyvsp[(3) - (4)].ttype));
		  /* Don't let the tree nodes for $3 be discarded by
		     clear_momentary during the parsing of the next stmt.  */
		  push_momentary ();
		  position_after_white_space (); }
    break;

  case 350:
/* Line 1792 of yacc.c  */
#line 1820 "c-parse.y"
    { expand_end_case ((yyvsp[(3) - (6)].ttype));
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
    break;

  case 351:
/* Line 1792 of yacc.c  */
#line 1826 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (2)].filename), (yyvsp[(0) - (2)].lineno));
		  if ( ! expand_exit_something ())
		    error ("break statement not within loop or switch"); }
    break;

  case 352:
/* Line 1792 of yacc.c  */
#line 1831 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (2)].filename), (yyvsp[(0) - (2)].lineno));
		  if (! expand_continue_loop (NULL_PTR))
		    error ("continue statement not within a loop"); }
    break;

  case 353:
/* Line 1792 of yacc.c  */
#line 1836 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (2)].filename), (yyvsp[(0) - (2)].lineno));
		  c_expand_return (NULL_TREE); }
    break;

  case 354:
/* Line 1792 of yacc.c  */
#line 1840 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (3)].filename), (yyvsp[(0) - (3)].lineno));
		  c_expand_return ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 355:
/* Line 1792 of yacc.c  */
#line 1844 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (6)].filename), (yyvsp[(0) - (6)].lineno));
		  STRIP_NOPS ((yyvsp[(4) - (6)].ttype));
		  if ((TREE_CODE ((yyvsp[(4) - (6)].ttype)) == ADDR_EXPR
		       && TREE_CODE (TREE_OPERAND ((yyvsp[(4) - (6)].ttype), 0)) == STRING_CST)
		      || TREE_CODE ((yyvsp[(4) - (6)].ttype)) == STRING_CST)
		    expand_asm ((yyvsp[(4) - (6)].ttype));
		  else
		    error ("argument of `asm' is not a constant string"); }
    break;

  case 356:
/* Line 1792 of yacc.c  */
#line 1855 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (8)].filename), (yyvsp[(0) - (8)].lineno));
		  c_expand_asm_operands ((yyvsp[(4) - (8)].ttype), (yyvsp[(6) - (8)].ttype), NULL_TREE, NULL_TREE,
					 (yyvsp[(2) - (8)].ttype) == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
    break;

  case 357:
/* Line 1792 of yacc.c  */
#line 1862 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (10)].filename), (yyvsp[(0) - (10)].lineno));
		  c_expand_asm_operands ((yyvsp[(4) - (10)].ttype), (yyvsp[(6) - (10)].ttype), (yyvsp[(8) - (10)].ttype), NULL_TREE,
					 (yyvsp[(2) - (10)].ttype) == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
    break;

  case 358:
/* Line 1792 of yacc.c  */
#line 1870 "c-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (12)].filename), (yyvsp[(0) - (12)].lineno));
		  c_expand_asm_operands ((yyvsp[(4) - (12)].ttype), (yyvsp[(6) - (12)].ttype), (yyvsp[(8) - (12)].ttype), (yyvsp[(10) - (12)].ttype),
					 (yyvsp[(2) - (12)].ttype) == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
    break;

  case 359:
/* Line 1792 of yacc.c  */
#line 1876 "c-parse.y"
    { tree decl;
		  stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (3)].filename), (yyvsp[(0) - (3)].lineno));
		  decl = lookup_label ((yyvsp[(2) - (3)].ttype));
		  if (decl != 0)
		    {
		      TREE_USED (decl) = 1;
		      expand_goto (decl);
		    }
		}
    break;

  case 360:
/* Line 1792 of yacc.c  */
#line 1887 "c-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids `goto *expr;'");
		  stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (4)].filename), (yyvsp[(0) - (4)].lineno));
		  expand_computed_goto (convert (ptr_type_node, (yyvsp[(3) - (4)].ttype))); }
    break;

  case 363:
/* Line 1792 of yacc.c  */
#line 1902 "c-parse.y"
    {
	    /* The value returned by this action is  */
	    /*      1 if everything is OK */ 
	    /*      0 in case of error or already bound iterator */

	    (yyval.itype) = 0;
	    if (TREE_CODE ((yyvsp[(3) - (4)].ttype)) != VAR_DECL)
	      error ("invalid `for (ITERATOR)' syntax");
	    else if (! ITERATOR_P ((yyvsp[(3) - (4)].ttype)))
	      error ("`%s' is not an iterator",
		     IDENTIFIER_POINTER (DECL_NAME ((yyvsp[(3) - (4)].ttype))));
	    else if (ITERATOR_BOUND_P ((yyvsp[(3) - (4)].ttype)))
	      error ("`for (%s)' inside expansion of same iterator",
		     IDENTIFIER_POINTER (DECL_NAME ((yyvsp[(3) - (4)].ttype))));
	    else
	      {
		(yyval.itype) = 1;
		iterator_for_loop_start ((yyvsp[(3) - (4)].ttype));
	      }
	  }
    break;

  case 364:
/* Line 1792 of yacc.c  */
#line 1923 "c-parse.y"
    {
	    if ((yyvsp[(5) - (6)].itype))
	      iterator_for_loop_end ((yyvsp[(3) - (6)].ttype));
	  }
    break;

  case 365:
/* Line 1792 of yacc.c  */
#line 1958 "c-parse.y"
    { register tree value = check_case_value ((yyvsp[(2) - (3)].ttype));
		  register tree label
		    = build_decl (LABEL_DECL, NULL_TREE, NULL_TREE);

		  stmt_count++;

		  if (value != error_mark_node)
		    {
		      tree duplicate;
		      int success;

		      if (pedantic && ! INTEGRAL_TYPE_P (TREE_TYPE (value)))
			pedwarn ("label must have integral type in ANSI C");

		      success = pushcase (value, convert_and_check,
					  label, &duplicate);

		      if (success == 1)
			error ("case label not within a switch statement");
		      else if (success == 2)
			{
			  error ("duplicate case value");
			  error_with_decl (duplicate, "this is the first entry for that value");
			}
		      else if (success == 3)
			warning ("case value out of range");
		      else if (success == 5)
			error ("case label within scope of cleanup or variable array");
		    }
		  position_after_white_space (); }
    break;

  case 366:
/* Line 1792 of yacc.c  */
#line 1989 "c-parse.y"
    { register tree value1 = check_case_value ((yyvsp[(2) - (5)].ttype));
		  register tree value2 = check_case_value ((yyvsp[(4) - (5)].ttype));
		  register tree label
		    = build_decl (LABEL_DECL, NULL_TREE, NULL_TREE);

		  if (pedantic)
		    pedwarn ("ANSI C forbids case ranges");
		  stmt_count++;

		  if (value1 != error_mark_node && value2 != error_mark_node)
		    {
		      tree duplicate;
		      int success = pushcase_range (value1, value2,
						    convert_and_check, label,
						    &duplicate);
		      if (success == 1)
			error ("case label not within a switch statement");
		      else if (success == 2)
			{
			  error ("duplicate case value");
			  error_with_decl (duplicate, "this is the first entry for that value");
			}
		      else if (success == 3)
			warning ("case value out of range");
		      else if (success == 4)
			warning ("empty case range");
		      else if (success == 5)
			error ("case label within scope of cleanup or variable array");
		    }
		  position_after_white_space (); }
    break;

  case 367:
/* Line 1792 of yacc.c  */
#line 2020 "c-parse.y"
    {
		  tree duplicate;
		  register tree label
		    = build_decl (LABEL_DECL, NULL_TREE, NULL_TREE);
		  int success = pushcase (NULL_TREE, 0, label, &duplicate);
		  stmt_count++;
		  if (success == 1)
		    error ("default label not within a switch statement");
		  else if (success == 2)
		    {
		      error ("multiple default labels in one switch");
		      error_with_decl (duplicate, "this is the first default label");
		    }
		  position_after_white_space (); }
    break;

  case 368:
/* Line 1792 of yacc.c  */
#line 2035 "c-parse.y"
    { tree label = define_label (input_filename, lineno, (yyvsp[(1) - (3)].ttype));
		  stmt_count++;
		  emit_nop ();
		  if (label)
		    {
		      expand_label (label);
		      decl_attributes (label, (yyvsp[(3) - (3)].ttype), NULL_TREE);
		    }
		  position_after_white_space (); }
    break;

  case 369:
/* Line 1792 of yacc.c  */
#line 2050 "c-parse.y"
    { emit_line_note (input_filename, lineno);
		  (yyval.ttype) = NULL_TREE; }
    break;

  case 370:
/* Line 1792 of yacc.c  */
#line 2053 "c-parse.y"
    { emit_line_note (input_filename, lineno); }
    break;

  case 371:
/* Line 1792 of yacc.c  */
#line 2058 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 373:
/* Line 1792 of yacc.c  */
#line 2065 "c-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 376:
/* Line 1792 of yacc.c  */
#line 2072 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 377:
/* Line 1792 of yacc.c  */
#line 2077 "c-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 378:
/* Line 1792 of yacc.c  */
#line 2082 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, combine_strings ((yyvsp[(1) - (1)].ttype)), NULL_TREE); }
    break;

  case 379:
/* Line 1792 of yacc.c  */
#line 2084 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, combine_strings ((yyvsp[(3) - (3)].ttype)), (yyvsp[(1) - (3)].ttype)); }
    break;

  case 380:
/* Line 1792 of yacc.c  */
#line 2090 "c-parse.y"
    { pushlevel (0);
		  clear_parm_order ();
		  declare_parm_level (0); }
    break;

  case 381:
/* Line 1792 of yacc.c  */
#line 2094 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  parmlist_tags_warning ();
		  poplevel (0, 0, 0); }
    break;

  case 383:
/* Line 1792 of yacc.c  */
#line 2102 "c-parse.y"
    { tree parm;
		  if (pedantic)
		    pedwarn ("ANSI C forbids forward parameter declarations");
		  /* Mark the forward decls as such.  */
		  for (parm = getdecls (); parm; parm = TREE_CHAIN (parm))
		    TREE_ASM_WRITTEN (parm) = 1;
		  clear_parm_order (); }
    break;

  case 384:
/* Line 1792 of yacc.c  */
#line 2110 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(4) - (4)].ttype); }
    break;

  case 385:
/* Line 1792 of yacc.c  */
#line 2112 "c-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, NULL_TREE, NULL_TREE); }
    break;

  case 386:
/* Line 1792 of yacc.c  */
#line 2118 "c-parse.y"
    { (yyval.ttype) = get_parm_info (0); }
    break;

  case 387:
/* Line 1792 of yacc.c  */
#line 2120 "c-parse.y"
    { (yyval.ttype) = get_parm_info (0);
		  /* Gcc used to allow this as an extension.  However, it does
		     not work for all targets, and thus has been disabled.
		     Also, since func (...) and func () are indistinguishable,
		     it caused problems with the code in expand_builtin which
		     tries to verify that BUILT_IN_NEXT_ARG is being used
		     correctly.  */
		  error ("ANSI C requires a named argument before `...'");
		}
    break;

  case 388:
/* Line 1792 of yacc.c  */
#line 2130 "c-parse.y"
    { (yyval.ttype) = get_parm_info (1); }
    break;

  case 389:
/* Line 1792 of yacc.c  */
#line 2132 "c-parse.y"
    { (yyval.ttype) = get_parm_info (0); }
    break;

  case 390:
/* Line 1792 of yacc.c  */
#line 2137 "c-parse.y"
    { push_parm_decl ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 391:
/* Line 1792 of yacc.c  */
#line 2139 "c-parse.y"
    { push_parm_decl ((yyvsp[(3) - (3)].ttype)); }
    break;

  case 392:
/* Line 1792 of yacc.c  */
#line 2146 "c-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(3) - (4)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(4) - (4)].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 393:
/* Line 1792 of yacc.c  */
#line 2155 "c-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(3) - (4)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(4) - (4)].ttype))); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 394:
/* Line 1792 of yacc.c  */
#line 2164 "c-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(3) - (4)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(4) - (4)].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 395:
/* Line 1792 of yacc.c  */
#line 2173 "c-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(3) - (4)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(4) - (4)].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype));  }
    break;

  case 396:
/* Line 1792 of yacc.c  */
#line 2183 "c-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(3) - (4)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(4) - (4)].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype));  }
    break;

  case 397:
/* Line 1792 of yacc.c  */
#line 2197 "c-parse.y"
    { pushlevel (0);
		  clear_parm_order ();
		  declare_parm_level (1); }
    break;

  case 398:
/* Line 1792 of yacc.c  */
#line 2201 "c-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  parmlist_tags_warning ();
		  poplevel (0, 0, 0); }
    break;

  case 400:
/* Line 1792 of yacc.c  */
#line 2209 "c-parse.y"
    { tree t;
		  for (t = (yyvsp[(1) - (2)].ttype); t; t = TREE_CHAIN (t))
		    if (TREE_VALUE (t) == NULL_TREE)
		      error ("`...' in old-style identifier list");
		  (yyval.ttype) = tree_cons (NULL_TREE, NULL_TREE, (yyvsp[(1) - (2)].ttype)); }
    break;

  case 401:
/* Line 1792 of yacc.c  */
#line 2219 "c-parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ttype)); }
    break;

  case 402:
/* Line 1792 of yacc.c  */
#line 2221 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (3)].ttype))); }
    break;

  case 403:
/* Line 1792 of yacc.c  */
#line 2227 "c-parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ttype)); }
    break;

  case 404:
/* Line 1792 of yacc.c  */
#line 2229 "c-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (3)].ttype))); }
    break;

  case 405:
/* Line 1792 of yacc.c  */
#line 2234 "c-parse.y"
    { (yyval.itype) = pedantic;
		  pedantic = 0; }
    break;


/* Line 1792 of yacc.c  */
#line 5212 "c-parse.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 2238 "c-parse.y"

