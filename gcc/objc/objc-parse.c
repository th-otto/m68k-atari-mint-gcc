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
#line 33 "objc-parse.y"

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

#include "objc-act.h"

/* Since parsers are distinct for each language, put the language string
   definition here.  */
char *language_string = "GNU Obj-C";

/* Like YYERROR but do call yyerror.  */
#define YYERROR1 { yyerror ("syntax error"); YYERROR; }

/* Cause the `yydebug' variable to be defined.  */
#define YYDEBUG 1

/* Line 371 of yacc.c  */
#line 98 "objc-parse.c"

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
   by #include "objc-parse.h".  */
#ifndef YY_YY_OBJC_PARSE_H_INCLUDED
# define YY_YY_OBJC_PARSE_H_INCLUDED
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
#line 65 "objc-parse.y"
long itype; tree ttype; enum tree_code code;
	char *filename; int lineno; int ends_in_label; 

/* Line 387 of yacc.c  */
#line 206 "objc-parse.c"
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

#endif /* !YY_YY_OBJC_PARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */
/* Line 390 of yacc.c  */
#line 193 "objc-parse.y"

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

/* Objective-C specific information */

tree objc_interface_context;
tree objc_implementation_context;
tree objc_method_context;
tree objc_ivar_chain;
tree objc_ivar_context;
enum tree_code objc_inherit_code;
int objc_receiver_context;
int objc_public_flag;


/* Tell yyparse how to print a token's value, if yydebug is set.  */

#define YYPRINT(FILE,YYCHAR,YYLVAL) yyprint(FILE,YYCHAR,YYLVAL)
extern void yyprint			PROTO ((FILE *, int, YYSTYPE));

/* Line 390 of yacc.c  */
#line 273 "objc-parse.c"

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
#define YYLAST   3649

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  228
/* YYNRULES -- Number of rules.  */
#define YYNRULES  568
/* YYNRULES -- Number of states.  */
#define YYNSTATES  955

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
      19,    21,    27,    30,    34,    39,    44,    47,    50,    53,
      56,    58,    59,    60,    68,    73,    74,    75,    83,    88,
      89,    90,    97,   101,   103,   105,   107,   109,   111,   113,
     115,   117,   119,   121,   123,   125,   126,   128,   130,   134,
     136,   139,   142,   145,   148,   151,   156,   159,   164,   167,
     170,   172,   174,   176,   181,   182,   190,   192,   196,   200,
     204,   208,   212,   216,   220,   224,   228,   232,   236,   240,
     241,   246,   247,   252,   253,   254,   262,   263,   269,   273,
     277,   279,   281,   283,   287,   291,   292,   297,   302,   307,
     311,   315,   318,   321,   323,   325,   327,   329,   331,   333,
     336,   338,   341,   342,   344,   347,   351,   353,   355,   358,
     361,   366,   371,   374,   377,   381,   383,   385,   388,   391,
     392,   393,   398,   403,   407,   411,   414,   417,   420,   423,
     427,   428,   431,   434,   437,   440,   444,   445,   448,   451,
     453,   455,   458,   461,   463,   465,   468,   471,   474,   478,
     479,   482,   484,   486,   488,   491,   494,   496,   501,   506,
     508,   510,   512,   514,   518,   520,   524,   525,   530,   531,
     538,   542,   543,   550,   554,   555,   557,   559,   562,   569,
     571,   575,   576,   578,   583,   590,   595,   597,   599,   601,
     603,   605,   606,   611,   613,   614,   617,   619,   623,   627,
     630,   631,   636,   638,   639,   644,   646,   648,   650,   653,
     656,   657,   658,   664,   665,   666,   672,   674,   676,   680,
     684,   689,   693,   697,   701,   703,   705,   709,   714,   718,
     722,   726,   728,   732,   736,   740,   745,   749,   753,   755,
     757,   760,   762,   765,   767,   770,   771,   779,   785,   788,
     789,   797,   803,   806,   807,   816,   817,   825,   828,   829,
     831,   832,   834,   836,   839,   840,   844,   847,   852,   856,
     858,   862,   864,   866,   869,   871,   875,   880,   887,   893,
     895,   899,   901,   903,   907,   910,   913,   914,   916,   918,
     921,   922,   925,   929,   933,   936,   940,   945,   949,   952,
     956,   959,   963,   965,   967,   970,   973,   974,   976,   979,
     980,   981,   983,   985,   988,   992,   994,   997,   999,  1002,
    1009,  1015,  1021,  1024,  1027,  1032,  1033,  1038,  1039,  1040,
    1044,  1049,  1053,  1055,  1057,  1059,  1061,  1064,  1065,  1070,
    1072,  1076,  1077,  1078,  1086,  1092,  1095,  1096,  1097,  1098,
    1111,  1112,  1119,  1122,  1125,  1128,  1132,  1139,  1148,  1159,
    1172,  1176,  1181,  1183,  1185,  1186,  1193,  1197,  1203,  1206,
    1210,  1211,  1213,  1214,  1216,  1217,  1219,  1221,  1225,  1230,
    1232,  1236,  1237,  1240,  1243,  1244,  1249,  1252,  1253,  1255,
    1257,  1261,  1263,  1267,  1272,  1277,  1282,  1287,  1292,  1293,
    1296,  1298,  1301,  1303,  1307,  1309,  1313,  1315,  1317,  1319,
    1321,  1323,  1325,  1327,  1329,  1333,  1337,  1342,  1343,  1344,
    1355,  1356,  1363,  1364,  1365,  1378,  1379,  1388,  1389,  1396,
    1399,  1400,  1409,  1414,  1415,  1425,  1431,  1432,  1439,  1440,
    1442,  1446,  1450,  1452,  1454,  1456,  1458,  1459,  1463,  1466,
    1470,  1474,  1476,  1477,  1479,  1483,  1485,  1489,  1492,  1493,
    1494,  1495,  1503,  1504,  1505,  1506,  1514,  1515,  1516,  1519,
    1521,  1523,  1526,  1527,  1531,  1533,  1535,  1536,  1537,  1543,
    1544,  1545,  1551,  1556,  1558,  1564,  1567,  1568,  1571,  1572,
    1574,  1576,  1578,  1581,  1584,  1589,  1592,  1595,  1597,  1601,
    1604,  1607,  1610,  1611,  1614,  1615,  1619,  1621,  1623,  1626,
    1628,  1630,  1632,  1634,  1636,  1638,  1640,  1642,  1644,  1646,
    1648,  1650,  1652,  1654,  1656,  1658,  1660,  1662,  1664,  1666,
    1668,  1670,  1672,  1674,  1676,  1683,  1687,  1693,  1696,  1698,
    1700,  1702,  1705,  1707,  1711,  1714,  1716,  1718,  1719,  1720,
    1727,  1729,  1731,  1733,  1736,  1739,  1741,  1746,  1751
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      85,     0,    -1,    -1,    86,    -1,    -1,    87,    89,    -1,
      -1,    86,    88,    89,    -1,    91,    -1,    90,    -1,   243,
      -1,    27,    58,   100,    76,    77,    -1,   242,    89,    -1,
     124,   138,    77,    -1,   131,   124,   138,    77,    -1,   127,
     124,   137,    77,    -1,   131,    77,    -1,   127,    77,    -1,
       1,    77,    -1,     1,    78,    -1,    77,    -1,    -1,    -1,
     127,   124,   166,    92,   118,    93,   200,    -1,   127,   124,
     166,     1,    -1,    -1,    -1,   131,   124,   169,    94,   118,
      95,   200,    -1,   131,   124,   169,     1,    -1,    -1,    -1,
     124,   169,    96,   118,    97,   200,    -1,   124,   169,     1,
      -1,     3,    -1,     4,    -1,    72,    -1,    67,    -1,    43,
      -1,    49,    -1,    48,    -1,    54,    -1,    53,    -1,    79,
      -1,    80,    -1,   102,    -1,    -1,   102,    -1,   108,    -1,
     102,    81,   108,    -1,   114,    -1,    50,   106,    -1,   242,
     106,    -1,    99,   106,    -1,    40,    98,    -1,   104,   103,
      -1,   104,    58,   187,    76,    -1,   105,   103,    -1,   105,
      58,   187,    76,    -1,    33,   106,    -1,    34,   106,    -1,
      11,    -1,    29,    -1,   103,    -1,    58,   187,    76,   106,
      -1,    -1,    58,   187,    76,    82,   107,   152,    78,    -1,
     106,    -1,   108,    48,   108,    -1,   108,    49,   108,    -1,
     108,    50,   108,    -1,   108,    51,   108,    -1,   108,    52,
     108,    -1,   108,    47,   108,    -1,   108,    46,   108,    -1,
     108,    45,   108,    -1,   108,    44,   108,    -1,   108,    43,
     108,    -1,   108,    41,   108,    -1,   108,    42,   108,    -1,
      -1,   108,    40,   109,   108,    -1,    -1,   108,    39,   110,
     108,    -1,    -1,    -1,   108,    37,   111,   100,    38,   112,
     108,    -1,    -1,   108,    37,   113,    38,   108,    -1,   108,
      35,   108,    -1,   108,    36,   108,    -1,     3,    -1,     8,
      -1,   116,    -1,    58,   100,    76,    -1,    58,     1,    76,
      -1,    -1,    58,   115,   202,    76,    -1,   114,    58,   101,
      76,    -1,   114,    59,   100,    83,    -1,   114,    57,    98,
      -1,   114,    60,    98,    -1,   114,    54,    -1,   114,    53,
      -1,   303,    -1,   309,    -1,   310,    -1,   311,    -1,   117,
      -1,     9,    -1,   116,     9,    -1,    75,    -1,   117,    75,
      -1,    -1,   120,    -1,   120,    10,    -1,   207,   208,   121,
      -1,   119,    -1,   195,    -1,   120,   119,    -1,   119,   195,
      -1,   129,   124,   137,    77,    -1,   132,   124,   138,    77,
      -1,   129,    77,    -1,   132,    77,    -1,   207,   208,   126,
      -1,   122,    -1,   195,    -1,   123,   122,    -1,   122,   195,
      -1,    -1,    -1,   127,   124,   137,    77,    -1,   131,   124,
     138,    77,    -1,   127,   124,   160,    -1,   131,   124,   163,
      -1,   127,    77,    -1,   131,    77,    -1,   242,   126,    -1,
     135,   128,    -1,   131,   135,   128,    -1,    -1,   128,   136,
      -1,   128,     5,    -1,   128,   145,    -1,   135,   130,    -1,
     132,   135,   130,    -1,    -1,   130,   136,    -1,   130,     5,
      -1,   132,    -1,   145,    -1,   131,   132,    -1,   131,   145,
      -1,     7,    -1,     5,    -1,   132,     7,    -1,   132,     5,
      -1,   135,   134,    -1,   189,   135,   134,    -1,    -1,   134,
     136,    -1,     6,    -1,   173,    -1,     4,    -1,    67,   259,
      -1,    72,   259,    -1,   260,    -1,    28,    58,   100,    76,
      -1,    28,    58,   187,    76,    -1,     6,    -1,     7,    -1,
     173,    -1,   140,    -1,   137,    81,   140,    -1,   142,    -1,
     138,    81,   140,    -1,    -1,    27,    58,   116,    76,    -1,
      -1,   166,   139,   144,    35,   141,   150,    -1,   166,   139,
     144,    -1,    -1,   169,   139,   144,    35,   143,   150,    -1,
     169,   139,   144,    -1,    -1,   145,    -1,   146,    -1,   145,
     146,    -1,    30,    58,    58,   147,    76,    76,    -1,   148,
      -1,   147,    81,   148,    -1,    -1,   149,    -1,   149,    58,
       3,    76,    -1,   149,    58,     3,    81,   102,    76,    -1,
     149,    58,   101,    76,    -1,    98,    -1,     5,    -1,     6,
      -1,     7,    -1,   108,    -1,    -1,    82,   151,   152,    78,
      -1,     1,    -1,    -1,   153,   178,    -1,   154,    -1,   153,
      81,   154,    -1,   158,    35,   156,    -1,   159,   156,    -1,
      -1,    98,    38,   155,   156,    -1,   156,    -1,    -1,    82,
     157,   152,    78,    -1,   108,    -1,     1,    -1,   159,    -1,
     158,   159,    -1,    57,    98,    -1,    -1,    -1,   166,   161,
     118,   162,   202,    -1,    -1,    -1,   169,   164,   118,   165,
     202,    -1,   167,    -1,   169,    -1,    58,   167,    76,    -1,
     167,    58,   237,    -1,   167,    59,   100,    83,    -1,   167,
      59,    83,    -1,    50,   190,   167,    -1,   145,   125,   167,
      -1,     4,    -1,    72,    -1,   168,    58,   237,    -1,   168,
      59,   100,    83,    -1,   168,    59,    83,    -1,    50,   190,
     168,    -1,   145,   125,   168,    -1,     4,    -1,   169,    58,
     237,    -1,    58,   169,    76,    -1,    50,   190,   169,    -1,
     169,    59,   100,    83,    -1,   169,    59,    83,    -1,   145,
     125,   169,    -1,     3,    -1,    13,    -1,    13,   145,    -1,
      14,    -1,    14,   145,    -1,    12,    -1,    12,   145,    -1,
      -1,   170,    98,    82,   174,   180,    78,   144,    -1,   170,
      82,   180,    78,   144,    -1,   170,    98,    -1,    -1,   171,
      98,    82,   175,   180,    78,   144,    -1,   171,    82,   180,
      78,   144,    -1,   171,    98,    -1,    -1,   172,    98,    82,
     176,   185,   179,    78,   144,    -1,    -1,   172,    82,   177,
     185,   179,    78,   144,    -1,   172,    98,    -1,    -1,    81,
      -1,    -1,    81,    -1,   181,    -1,   181,   182,    -1,    -1,
     181,   182,    77,    -1,   181,    77,    -1,    65,    58,    67,
      76,    -1,   133,   124,   183,    -1,   133,    -1,   189,   124,
     183,    -1,   189,    -1,     1,    -1,   242,   182,    -1,   184,
      -1,   183,    81,   184,    -1,   207,   208,   166,   144,    -1,
     207,   208,   166,    38,   108,   144,    -1,   207,   208,    38,
     108,   144,    -1,   186,    -1,   185,    81,   186,    -1,     1,
      -1,    98,    -1,    98,    35,   108,    -1,   133,   188,    -1,
     189,   188,    -1,    -1,   191,    -1,     7,    -1,   189,     7,
      -1,    -1,   190,     7,    -1,    58,   191,    76,    -1,    50,
     190,   191,    -1,    50,   190,    -1,   191,    58,   230,    -1,
     191,    59,   100,    83,    -1,   191,    59,    83,    -1,    58,
     230,    -1,    59,   100,    83,    -1,    59,    83,    -1,   145,
     125,   191,    -1,   193,    -1,   210,    -1,   193,   210,    -1,
     193,   195,    -1,    -1,   192,    -1,     1,    77,    -1,    -1,
      -1,   198,    -1,   199,    -1,   198,   199,    -1,    32,   241,
      77,    -1,   202,    -1,     1,   202,    -1,    82,    -1,   201,
      78,    -1,   201,   196,   197,   123,   194,    78,    -1,   201,
     196,   197,     1,    78,    -1,   201,   196,   197,   192,    78,
      -1,   204,   209,    -1,   204,     1,    -1,    15,    58,   100,
      76,    -1,    -1,    18,   206,   209,    17,    -1,    -1,    -1,
     207,   208,   212,    -1,   207,   208,   223,   209,    -1,   207,
     208,   211,    -1,   212,    -1,   223,    -1,   202,    -1,   220,
      -1,   100,    77,    -1,    -1,   203,    16,   213,   209,    -1,
     203,    -1,   203,    16,     1,    -1,    -1,    -1,    17,   214,
      58,   100,    76,   215,   209,    -1,   205,    58,   100,    76,
      77,    -1,   205,     1,    -1,    -1,    -1,    -1,    19,    58,
     225,    77,   216,   225,    77,   217,   225,    76,   218,   209,
      -1,    -1,    20,    58,   100,    76,   219,   209,    -1,    23,
      77,    -1,    24,    77,    -1,    25,    77,    -1,    25,   100,
      77,    -1,    27,   224,    58,   100,    76,    77,    -1,    27,
     224,    58,   100,    38,   226,    76,    77,    -1,    27,   224,
      58,   100,    38,   226,    38,   226,    76,    77,    -1,    27,
     224,    58,   100,    38,   226,    38,   226,    38,   229,    76,
      77,    -1,    26,    98,    77,    -1,    26,    50,   100,    77,
      -1,    77,    -1,   221,    -1,    -1,    19,    58,   114,    76,
     222,   209,    -1,    21,   108,    38,    -1,    21,   108,    10,
     108,    38,    -1,    22,    38,    -1,    98,    38,   144,    -1,
      -1,     7,    -1,    -1,   100,    -1,    -1,   227,    -1,   228,
      -1,   227,    81,   228,    -1,     9,    58,   100,    76,    -1,
     116,    -1,   229,    81,   116,    -1,    -1,   231,   232,    -1,
     234,    76,    -1,    -1,   235,    77,   233,   232,    -1,     1,
      76,    -1,    -1,    10,    -1,   235,    -1,   235,    81,    10,
      -1,   236,    -1,   235,    81,   236,    -1,   127,   124,   168,
     144,    -1,   127,   124,   169,   144,    -1,   127,   124,   188,
     144,    -1,   131,   124,   169,   144,    -1,   131,   124,   188,
     144,    -1,    -1,   238,   239,    -1,   232,    -1,   240,    76,
      -1,     3,    -1,   240,    81,     3,    -1,    98,    -1,   241,
      81,    98,    -1,    31,    -1,   247,    -1,   245,    -1,   246,
      -1,   257,    -1,   267,    -1,    63,    -1,    98,    -1,   244,
      81,    98,    -1,    73,   244,    77,    -1,    74,    98,    98,
      77,    -1,    -1,    -1,    61,    98,   259,    82,   248,   261,
      78,   249,   274,    63,    -1,    -1,    61,    98,   259,   250,
     274,    63,    -1,    -1,    -1,    61,    98,    38,    98,   259,
      82,   251,   261,    78,   252,   274,    63,    -1,    -1,    61,
      98,    38,    98,   259,   253,   274,    63,    -1,    -1,    62,
      98,    82,   254,   261,    78,    -1,    62,    98,    -1,    -1,
      62,    98,    38,    98,    82,   255,   261,    78,    -1,    62,
      98,    38,    98,    -1,    -1,    61,    98,    58,    98,    76,
     259,   256,   274,    63,    -1,    62,    98,    58,    98,    76,
      -1,    -1,    71,    98,   259,   258,   274,    63,    -1,    -1,
     260,    -1,    45,   244,    45,    -1,   261,   262,   263,    -1,
     263,    -1,    69,    -1,    70,    -1,    68,    -1,    -1,   263,
     264,    77,    -1,   263,    77,    -1,   133,   124,   265,    -1,
     189,   124,   265,    -1,     1,    -1,    -1,   266,    -1,   265,
      81,   266,    -1,   166,    -1,   166,    38,   108,    -1,    38,
     108,    -1,    -1,    -1,    -1,    48,   268,   284,   269,   285,
     270,   200,    -1,    -1,    -1,    -1,    49,   271,   284,   272,
     285,   273,   200,    -1,    -1,    -1,   275,   276,    -1,   279,
      -1,    90,    -1,   276,   279,    -1,    -1,   276,   277,    90,
      -1,    77,    -1,     1,    -1,    -1,    -1,    48,   280,   284,
     281,   278,    -1,    -1,    -1,    49,   282,   284,   283,   278,
      -1,    58,   187,    76,   293,    -1,   293,    -1,    58,   187,
      76,   294,   291,    -1,   294,   291,    -1,    -1,    77,   286,
      -1,    -1,   287,    -1,   288,    -1,   195,    -1,   287,   288,
      -1,   288,   195,    -1,   127,   124,   289,    77,    -1,   127,
      77,    -1,   131,    77,    -1,   290,    -1,   289,    81,   290,
      -1,   168,   144,    -1,   169,   144,    -1,   188,   144,    -1,
      -1,    81,    10,    -1,    -1,    81,   292,   234,    -1,   295,
      -1,   297,    -1,   294,   297,    -1,     3,    -1,     4,    -1,
      72,    -1,   296,    -1,    12,    -1,    13,    -1,    14,    -1,
      15,    -1,    16,    -1,    17,    -1,    18,    -1,    19,    -1,
      20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,
      25,    -1,    26,    -1,    27,    -1,    11,    -1,    28,    -1,
      29,    -1,     6,    -1,     7,    -1,   295,    38,    58,   187,
      76,    98,    -1,   295,    38,    98,    -1,    38,    58,   187,
      76,    98,    -1,    38,    98,    -1,   295,    -1,   299,    -1,
     301,    -1,   299,   301,    -1,   102,    -1,   295,    38,   300,
      -1,    38,   300,    -1,   100,    -1,    67,    -1,    -1,    -1,
      59,   304,   302,   305,   298,    83,    -1,   295,    -1,   307,
      -1,   308,    -1,   307,   308,    -1,   295,    38,    -1,    38,
      -1,    64,    58,   306,    76,    -1,    71,    58,    98,    76,
      -1,    66,    58,   187,    76,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   234,   234,   238,   253,   253,   254,   254,   258,   259,
     260,   261,   269,   274,   284,   289,   294,   296,   298,   299,
     300,   307,   312,   306,   319,   325,   330,   324,   337,   343,
     348,   342,   355,   363,   364,   365,   366,   369,   371,   373,
     375,   377,   379,   381,   385,   391,   392,   396,   398,   403,
     404,   407,   410,   414,   442,   448,   451,   454,   457,   459,
     464,   468,   472,   473,   477,   476,   508,   509,   511,   513,
     515,   517,   519,   521,   523,   525,   527,   529,   531,   534,
     533,   540,   539,   546,   549,   545,   555,   554,   564,   572,
     584,   743,   744,   746,   752,   755,   754,   791,   793,   795,
     807,   821,   823,   825,   827,   829,   831,   833,   839,   840,
     847,   848,   852,   854,   855,   866,   871,   872,   873,   874,
     882,   887,   892,   895,   904,   909,   910,   911,   912,   920,
     931,   935,   940,   945,   950,   955,   957,   959,   969,   971,
     976,   977,   979,   984,   989,   991,   997,   998,  1000,  1013,
    1015,  1017,  1019,  1024,  1027,  1029,  1032,  1046,  1048,  1053,
    1054,  1062,  1063,  1064,  1068,  1070,  1075,  1077,  1079,  1085,
    1086,  1087,  1091,  1092,  1096,  1097,  1102,  1103,  1111,  1110,
    1118,  1127,  1126,  1135,  1144,  1145,  1150,  1152,  1157,  1162,
    1164,  1170,  1171,  1173,  1175,  1177,  1185,  1186,  1187,  1188,
    1194,  1196,  1195,  1208,  1215,  1217,  1221,  1222,  1228,  1229,
    1231,  1230,  1233,  1238,  1237,  1241,  1243,  1247,  1248,  1252,
    1261,  1270,  1260,  1284,  1293,  1283,  1309,  1310,  1316,  1318,
    1323,  1325,  1327,  1334,  1336,  1337,  1346,  1351,  1353,  1355,
    1362,  1364,  1371,  1376,  1378,  1380,  1382,  1389,  1391,  1395,
    1397,  1402,  1404,  1409,  1411,  1417,  1416,  1422,  1426,  1429,
    1428,  1432,  1436,  1439,  1438,  1445,  1444,  1450,  1454,  1456,
    1459,  1461,  1467,  1469,  1475,  1476,  1478,  1482,  1507,  1513,
    1518,  1524,  1529,  1531,  1537,  1538,  1543,  1546,  1550,  1561,
    1562,  1567,  1573,  1575,  1580,  1582,  1588,  1589,  1593,  1595,
    1601,  1602,  1607,  1610,  1612,  1614,  1616,  1618,  1620,  1622,
    1624,  1628,  1637,  1645,  1646,  1648,  1652,  1654,  1657,  1661,
    1673,  1675,  1681,  1682,  1686,  1700,  1702,  1705,  1707,  1709,
    1717,  1725,  1737,  1741,  1745,  1760,  1759,  1772,  1776,  1780,
    1785,  1790,  1795,  1797,  1803,  1805,  1806,  1824,  1823,  1831,
    1843,  1846,  1856,  1845,  1866,  1874,  1879,  1891,  1894,  1877,
    1921,  1920,  1934,  1939,  1944,  1948,  1952,  1963,  1970,  1977,
    1984,  1995,  2001,  2005,  2011,  2010,  2066,  2097,  2128,  2143,
    2159,  2161,  2167,  2168,  2174,  2175,  2179,  2180,  2185,  2190,
    2192,  2199,  2199,  2209,  2211,  2210,  2220,  2227,  2228,  2238,
    2240,  2245,  2247,  2254,  2263,  2272,  2281,  2291,  2306,  2306,
    2316,  2317,  2327,  2329,  2335,  2337,  2342,  2350,  2351,  2352,
    2353,  2354,  2355,  2370,  2372,  2377,  2383,  2390,  2396,  2389,
    2407,  2406,  2420,  2426,  2419,  2437,  2436,  2450,  2449,  2461,
    2470,  2469,  2481,  2490,  2489,  2502,  2513,  2512,  2528,  2531,
    2535,  2545,  2546,  2550,  2551,  2552,  2557,  2560,  2561,  2579,
    2585,  2591,  2597,  2598,  2599,  2603,  2610,  2616,  2627,  2635,
    2642,  2626,  2652,  2660,  2667,  2651,  2681,  2683,  2683,  2687,
    2688,  2689,  2690,  2690,  2694,  2695,  2700,  2706,  2699,  2714,
    2720,  2713,  2729,  2734,  2739,  2744,  2753,  2755,  2761,  2763,
    2767,  2768,  2769,  2770,  2774,  2779,  2781,  2786,  2788,  2796,
    2801,  2806,  2815,  2818,  2824,  2823,  2836,  2840,  2842,  2849,
    2850,  2851,  2852,  2856,  2857,  2858,  2859,  2860,  2861,  2862,
    2863,  2864,  2865,  2866,  2867,  2868,  2869,  2870,  2871,  2872,
    2873,  2874,  2875,  2875,  2879,  2884,  2889,  2894,  2901,  2902,
    2906,  2907,  2915,  2927,  2931,  2938,  2939,  2947,  2949,  2946,
    2957,  2958,  2962,  2963,  2970,  2974,  2981,  2988,  2997
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
  "$@13", "$@14", "primary", "@15", "string", "objc_string",
  "old_style_parm_decls", "lineno_datadecl", "datadecls", "datadecl",
  "lineno_decl", "decls", "setspecs", "setattrs", "decl",
  "typed_declspecs", "reserved_declspecs",
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
  "identifiers", "identifiers_or_typenames", "extension", "objcdef",
  "identifier_list", "classdecl", "aliasdecl", "classdef", "$@41", "$@42",
  "$@43", "$@44", "$@45", "$@46", "$@47", "$@48", "$@49", "protocoldef",
  "$@50", "protocolrefs", "non_empty_protocolrefs", "ivar_decl_list",
  "visibility_spec", "ivar_decls", "ivar_decl", "ivars", "ivar_declarator",
  "methoddef", "$@51", "$@52", "$@53", "$@54", "$@55", "$@56",
  "methodprotolist", "@57", "methodprotolist2", "@58", "semi_or_error",
  "methodproto", "$@59", "$@60", "$@61", "$@62", "methoddecl",
  "optarglist", "myxdecls", "mydecls", "mydecl", "myparms", "myparm",
  "optparmlist", "$@63", "unaryselector", "keywordselector", "selector",
  "reservedwords", "keyworddecl", "messageargs", "keywordarglist",
  "keywordexpr", "keywordarg", "receiver", "objcmessageexpr", "$@64",
  "$@65", "selectorarg", "keywordnamelist", "keywordname",
  "objcselectorexpr", "objcprotocolexpr", "objcencodeexpr", YY_NULL
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
static const yytype_uint16 yyr1[] =
{
       0,    84,    85,    85,    87,    86,    88,    86,    89,    89,
      89,    89,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    92,    93,    91,    91,    94,    95,    91,    91,    96,
      97,    91,    91,    98,    98,    98,    98,    99,    99,    99,
      99,    99,    99,    99,   100,   101,   101,   102,   102,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     104,   105,   106,   106,   107,   106,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   109,
     108,   110,   108,   111,   112,   108,   113,   108,   108,   108,
     114,   114,   114,   114,   114,   115,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   116,   116,
     117,   117,   118,   118,   118,   119,   120,   120,   120,   120,
     121,   121,   121,   121,   122,   123,   123,   123,   123,   124,
     125,   126,   126,   126,   126,   126,   126,   126,   127,   127,
     128,   128,   128,   128,   129,   129,   130,   130,   130,   131,
     131,   131,   131,   132,   132,   132,   132,   133,   133,   134,
     134,   135,   135,   135,   135,   135,   135,   135,   135,   136,
     136,   136,   137,   137,   138,   138,   139,   139,   141,   140,
     140,   143,   142,   142,   144,   144,   145,   145,   146,   147,
     147,   148,   148,   148,   148,   148,   149,   149,   149,   149,
     150,   151,   150,   150,   152,   152,   153,   153,   154,   154,
     155,   154,   154,   157,   156,   156,   156,   158,   158,   159,
     161,   162,   160,   164,   165,   163,   166,   166,   167,   167,
     167,   167,   167,   167,   167,   167,   168,   168,   168,   168,
     168,   168,   169,   169,   169,   169,   169,   169,   169,   170,
     170,   171,   171,   172,   172,   174,   173,   173,   173,   175,
     173,   173,   173,   176,   173,   177,   173,   173,   178,   178,
     179,   179,   180,   180,   181,   181,   181,   181,   182,   182,
     182,   182,   182,   182,   183,   183,   184,   184,   184,   185,
     185,   185,   186,   186,   187,   187,   188,   188,   189,   189,
     190,   190,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   192,   193,   193,   193,   194,   194,   195,   196,
     197,   197,   198,   198,   199,   200,   200,   201,   202,   202,
     202,   202,   203,   203,   204,   206,   205,   207,   208,   209,
     209,   210,   211,   211,   212,   212,   212,   213,   212,   212,
     212,   214,   215,   212,   212,   212,   216,   217,   218,   212,
     219,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   220,   222,   221,   223,   223,   223,   223,
     224,   224,   225,   225,   226,   226,   227,   227,   228,   229,
     229,   231,   230,   232,   233,   232,   232,   234,   234,   234,
     234,   235,   235,   236,   236,   236,   236,   236,   238,   237,
     239,   239,   240,   240,   241,   241,   242,   243,   243,   243,
     243,   243,   243,   244,   244,   245,   246,   248,   249,   247,
     250,   247,   251,   252,   247,   253,   247,   254,   247,   247,
     255,   247,   247,   256,   247,   247,   258,   257,   259,   259,
     260,   261,   261,   262,   262,   262,   263,   263,   263,   264,
     264,   264,   265,   265,   265,   266,   266,   266,   268,   269,
     270,   267,   271,   272,   273,   267,   274,   275,   274,   276,
     276,   276,   277,   276,   278,   278,   280,   281,   279,   282,
     283,   279,   284,   284,   284,   284,   285,   285,   286,   286,
     287,   287,   287,   287,   288,   288,   288,   289,   289,   290,
     290,   290,   291,   291,   292,   291,   293,   294,   294,   295,
     295,   295,   295,   296,   296,   296,   296,   296,   296,   296,
     296,   296,   296,   296,   296,   296,   296,   296,   296,   296,
     296,   296,   296,   296,   297,   297,   297,   297,   298,   298,
     299,   299,   300,   301,   301,   302,   302,   304,   305,   303,
     306,   306,   307,   307,   308,   308,   309,   310,   311
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     0,     2,     0,     3,     1,     1,
       1,     5,     2,     3,     4,     4,     2,     2,     2,     2,
       1,     0,     0,     7,     4,     0,     0,     7,     4,     0,
       0,     6,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     3,     1,
       2,     2,     2,     2,     2,     4,     2,     4,     2,     2,
       1,     1,     1,     4,     0,     7,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     0,     7,     0,     5,     3,     3,
       1,     1,     1,     3,     3,     0,     4,     4,     4,     3,
       3,     2,     2,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     0,     1,     2,     3,     1,     1,     2,     2,
       4,     4,     2,     2,     3,     1,     1,     2,     2,     0,
       0,     4,     4,     3,     3,     2,     2,     2,     2,     3,
       0,     2,     2,     2,     2,     3,     0,     2,     2,     1,
       1,     2,     2,     1,     1,     2,     2,     2,     3,     0,
       2,     1,     1,     1,     2,     2,     1,     4,     4,     1,
       1,     1,     1,     3,     1,     3,     0,     4,     0,     6,
       3,     0,     6,     3,     0,     1,     1,     2,     6,     1,
       3,     0,     1,     4,     6,     4,     1,     1,     1,     1,
       1,     0,     4,     1,     0,     2,     1,     3,     3,     2,
       0,     4,     1,     0,     4,     1,     1,     1,     2,     2,
       0,     0,     5,     0,     0,     5,     1,     1,     3,     3,
       4,     3,     3,     3,     1,     1,     3,     4,     3,     3,
       3,     1,     3,     3,     3,     4,     3,     3,     1,     1,
       2,     1,     2,     1,     2,     0,     7,     5,     2,     0,
       7,     5,     2,     0,     8,     0,     7,     2,     0,     1,
       0,     1,     1,     2,     0,     3,     2,     4,     3,     1,
       3,     1,     1,     2,     1,     3,     4,     6,     5,     1,
       3,     1,     1,     3,     2,     2,     0,     1,     1,     2,
       0,     2,     3,     3,     2,     3,     4,     3,     2,     3,
       2,     3,     1,     1,     2,     2,     0,     1,     2,     0,
       0,     1,     1,     2,     3,     1,     2,     1,     2,     6,
       5,     5,     2,     2,     4,     0,     4,     0,     0,     3,
       4,     3,     1,     1,     1,     1,     2,     0,     4,     1,
       3,     0,     0,     7,     5,     2,     0,     0,     0,    12,
       0,     6,     2,     2,     2,     3,     6,     8,    10,    12,
       3,     4,     1,     1,     0,     6,     3,     5,     2,     3,
       0,     1,     0,     1,     0,     1,     1,     3,     4,     1,
       3,     0,     2,     2,     0,     4,     2,     0,     1,     1,
       3,     1,     3,     4,     4,     4,     4,     4,     0,     2,
       1,     2,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     4,     0,     0,    10,
       0,     6,     0,     0,    12,     0,     8,     0,     6,     2,
       0,     8,     4,     0,     9,     5,     0,     6,     0,     1,
       3,     3,     1,     1,     1,     1,     0,     3,     2,     3,
       3,     1,     0,     1,     3,     1,     3,     2,     0,     0,
       0,     7,     0,     0,     0,     7,     0,     0,     2,     1,
       1,     2,     0,     3,     1,     1,     0,     0,     5,     0,
       0,     5,     4,     1,     5,     2,     0,     2,     0,     1,
       1,     1,     2,     2,     4,     2,     2,     1,     3,     2,
       2,     2,     0,     2,     0,     3,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     3,     5,     2,     1,     1,
       1,     2,     1,     3,     2,     1,     1,     0,     0,     6,
       1,     1,     1,     2,     2,     1,     4,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     6,     0,     1,     0,     0,   163,   154,   161,
     153,   253,   249,   251,     0,     0,     0,   416,     0,   468,
     472,     0,     0,   422,   448,     0,   448,     0,     0,    20,
       5,     9,     8,     0,   129,   129,   149,   140,   150,   186,
       0,     0,     0,   162,     0,    10,   418,   419,   417,   420,
     166,   421,     7,    18,    19,   254,   250,   252,     0,     0,
       0,    33,    34,    36,    35,   423,     0,     0,     0,   448,
     439,   164,   449,   448,   165,     0,     0,   248,   300,     0,
       0,   174,   130,     0,    17,     0,    16,     0,   151,   140,
     152,   156,   155,   138,   187,   274,   258,   274,   262,   265,
     267,    12,    90,    91,   108,    60,    61,     0,     0,     0,
      37,    39,    38,     0,    41,    40,     0,   557,     0,     0,
       0,   110,    42,    43,     0,     0,    44,    62,     0,     0,
      66,    47,    49,    92,   107,     0,   103,   104,   105,   106,
     298,     0,   296,   159,     0,   296,   191,   450,     0,   519,
     520,   542,   543,   539,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     540,   541,     0,     0,   521,   469,   493,   512,   516,   522,
     517,   473,     0,     0,   430,     0,     0,   437,   446,   425,
       0,     0,     0,    13,     0,     0,    32,     0,   408,     0,
       0,   184,   234,   300,     0,   235,     0,   172,   130,     0,
     226,   227,     0,     0,   139,   142,   169,   170,   141,   143,
     171,     0,     0,     0,   255,     0,   259,     0,   263,    58,
      59,    53,    50,     0,     0,     0,     0,     0,     0,     0,
       0,    52,     0,     0,     0,    54,     0,    56,     0,     0,
      83,    81,    79,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   101,     0,    45,     0,
       0,   109,   111,    51,   167,   300,   391,     0,   130,   294,
     297,   157,   168,   299,   159,   295,   197,   198,   199,   196,
       0,   189,   192,   424,     0,   547,     0,   496,   514,   495,
       0,   518,     0,   496,   448,     0,   427,   477,   442,     0,
     456,   477,   426,   301,   244,   243,   175,   176,   247,     0,
     242,     0,   246,     0,     0,    30,     0,   337,   117,   338,
     183,   185,     0,     0,    15,     0,     0,    24,     0,   184,
     408,     0,    14,    28,     0,     0,   184,   282,   276,   129,
     273,   129,     0,   274,   184,   274,   291,   292,   270,   289,
       0,    94,    93,   327,   319,     0,     0,   556,   555,   558,
     565,   560,     0,   561,   562,     0,     0,    11,    48,     0,
       0,    88,    89,     0,     0,     0,     0,    77,    78,    76,
      75,    74,    73,    72,    67,    68,    69,    70,    71,    99,
       0,    46,     0,   100,   304,     0,   308,     0,   310,     0,
       0,   391,     0,   160,   158,     0,   191,    45,     0,     0,
       0,   470,   513,   397,     0,   545,   474,   435,   448,   456,
       0,     0,   440,   445,     0,     0,     0,     0,     0,   412,
     398,   129,   129,   410,     0,   399,   401,   409,     0,   245,
     318,     0,   119,   114,   118,     0,   181,   232,   228,   173,
     233,    22,   180,   229,   231,     0,    26,     0,   257,   337,
     275,   337,   283,     0,   261,     0,     0,   271,     0,   270,
     328,   320,    96,    64,    63,     0,   564,   566,     0,   563,
     568,   567,    55,    57,     0,     0,    82,    80,    97,    98,
     303,   302,   392,   309,   311,   305,   307,     0,   188,   190,
      90,     0,     0,   492,   512,   129,     0,   501,   497,   499,
       0,     0,   515,   399,     0,     0,   432,   477,   443,     0,
     431,   486,   489,   480,     0,   129,   129,   482,   479,   456,
     455,   453,   454,   438,   456,   461,   458,   129,   129,     0,
     447,   177,   396,   296,   296,   393,   394,     0,   411,     0,
       0,    31,   325,   115,   129,   129,   146,     0,     0,   178,
     230,     0,   277,   278,   284,   338,   280,   184,   184,   293,
     290,   184,     0,     0,     0,   321,   322,     0,     0,   548,
       0,   549,   550,    84,    87,   306,   193,     0,   195,   546,
     494,   505,   296,   506,   502,   503,   471,     0,   475,   456,
       0,   477,   428,     0,     0,   176,     0,     0,     0,   481,
       0,     0,   462,   462,   457,   241,   300,   391,   130,   184,
     184,   184,   300,   130,   184,   184,     0,   400,   402,   413,
     326,   122,     0,   123,     0,   146,   144,   203,   201,   200,
     182,    23,     0,    27,   337,     0,   256,   260,   266,   184,
     414,     0,     0,     0,   337,     0,     0,   126,   338,   313,
     323,   216,    90,     0,   213,     0,   215,     0,   268,   206,
     212,     0,     0,   552,   554,     0,   559,     0,   551,     0,
       0,   184,   184,   184,     0,   507,   544,     0,   436,     0,
     477,   487,   490,   483,   441,     0,   465,   459,   463,   460,
     304,     0,   408,     0,   403,   404,   405,   304,     0,   406,
     407,   395,     0,     0,   145,   148,   147,     0,   179,   285,
       0,   184,   264,   324,     0,   330,   128,   127,   317,     0,
     331,   315,   338,   314,     0,   219,     0,   210,    65,     0,
     205,     0,   218,   209,   553,    85,   194,   509,   510,   511,
     504,   296,   433,   444,     0,     0,     0,   467,     0,     0,
     239,   240,   236,   238,     0,   120,   121,     0,   184,     0,
     286,   415,   329,     0,   163,     0,   351,   335,     0,     0,
       0,     0,     0,     0,     0,     0,   380,   448,   448,   372,
       0,     0,   124,   129,   129,   344,   349,     0,     0,   341,
     342,   345,   373,   343,     0,     0,     0,   207,   208,   508,
     477,   429,   485,   484,   488,   491,   466,   464,   237,   202,
     288,   184,     0,     0,   337,   382,     0,     0,   378,   362,
     363,   364,     0,     0,     0,   381,     0,   184,   346,   135,
       0,   136,     0,     0,   333,   338,   332,   355,     0,   137,
     214,   211,     0,   287,     0,     0,     0,   383,    49,     0,
       0,     0,   376,   365,     0,   370,     0,   379,     0,   133,
     220,     0,   134,   223,   350,   337,     0,     0,   434,   334,
       0,   336,   374,   356,   360,     0,   371,     0,   131,     0,
     132,     0,   348,   339,   337,     0,   352,   337,   382,   337,
     377,   384,     0,   221,   224,   340,   354,   337,   375,     0,
     361,     0,     0,   385,   386,   366,     0,     0,   353,   357,
       0,   384,     0,     0,   222,   225,   382,     0,     0,   367,
     387,     0,   388,     0,     0,   358,   389,     0,   368,   337,
       0,     0,   359,   369,   390
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,     5,    30,    31,    32,   338,   568,
     344,   571,   200,   451,   675,   124,   234,   400,   126,   127,
     128,   129,   130,   587,   131,   386,   385,   383,   689,   384,
     132,   235,   133,   134,   325,   326,   327,   563,   663,   664,
      33,   195,   802,   441,    93,   564,   646,   442,    36,   142,
     281,    37,   218,   206,    80,   201,   207,   652,    81,   567,
     330,   331,    39,   290,   291,   292,   650,   727,   677,   678,
     679,   816,   680,   746,   681,   682,   879,   899,   926,   882,
     901,   927,   317,   210,   691,   211,    40,    41,    42,    43,
     353,   355,   360,   227,   750,   478,   222,   223,   350,   573,
     574,   358,   359,   144,   693,   145,   191,   280,   665,   666,
     739,   328,   481,   584,   585,   586,   561,   364,   562,   806,
     807,   808,   834,   855,   455,   856,   669,   809,   810,   885,
     833,   917,   908,   936,   949,   909,   811,   812,   907,   813,
     846,   869,   922,   923,   924,   947,   406,   407,   443,   636,
     444,   445,   446,   320,   321,   447,   448,   661,   135,    45,
      66,    46,    47,    48,   429,   700,   307,   609,   820,   527,
     310,   539,   611,    49,   311,    71,    50,   434,   544,   435,
     549,   707,   708,    51,    67,   297,   521,    68,   303,   525,
     430,   431,   537,   618,   824,   538,   613,   765,   614,   766,
     175,   421,   518,   519,   520,   694,   695,   299,   423,   176,
     177,   178,   179,   180,   590,   591,   684,   592,   369,   136,
     237,   485,   372,   373,   374,   137,   138,   139
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -811
static const yytype_int16 yypact[] =
{
      95,   100,   166,  3067,  -811,  3067,    33,  -811,  -811,  -811,
    -811,    94,    94,    94,   111,   114,   141,  -811,   437,  -811,
    -811,   437,   437,  -811,   163,   437,   163,   437,   437,  -811,
    -811,  -811,  -811,   350,   159,  1892,   410,  -811,    94,  -811,
     228,   234,   250,  -811,  3067,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,    94,    94,    94,  2747,  2591,
     147,  -811,  -811,  -811,  -811,  -811,    56,  3335,  3335,   107,
      50,  -811,  -811,   163,  -811,   195,   437,  -811,  -811,   350,
     209,  -811,    94,   862,  -811,   684,  -811,   350,   410,  -811,
      94,  -811,  -811,   831,  -811,   179,   168,   179,   177,  -811,
     239,  -811,  -811,  -811,  -811,  -811,  -811,  2747,  2747,   437,
    -811,  -811,  -811,  2747,  -811,  -811,  1355,  -811,   244,   247,
     281,  -811,  -811,  -811,  2747,   280,   295,  -811,  2799,  2851,
    -811,  3597,  1038,   353,   307,  2747,  -811,  -811,  -811,  -811,
    -811,   326,   290,  -811,   331,  3455,   440,  -811,   437,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,   421,   881,  -811,  -811,  -811,  2476,   380,  -811,
    -811,  -811,   437,   437,   356,   437,   437,  -811,  -811,  -811,
     358,   606,   170,  -811,   684,   350,  -811,   393,  -811,  1941,
     108,    94,  -811,  -811,   684,  -811,   211,  -811,    94,  1799,
      88,   328,   217,  1764,   831,  -811,  -811,  -811,  -811,    94,
    -811,   400,   383,  2989,  -811,   396,  -811,   203,  -811,  -811,
    -811,  -811,  -811,   409,   413,   412,   420,  2643,  3363,   881,
     437,  -811,   428,  2747,  1355,  -811,  1355,  -811,  2747,  2747,
     460,  -811,  -811,  2747,  2747,  2747,  2747,  2747,  2747,  2747,
    2747,  2747,  2747,  2747,  2747,  -811,  -811,   437,  2747,  2747,
     437,  -811,  -811,  -811,  -811,  -811,   290,  2006,    94,  -811,
     422,   745,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
     117,  -811,   445,  -811,   881,  -811,   432,   436,   513,  -811,
     380,  -811,   548,   436,   163,   454,  -811,   470,   457,   465,
    -811,   470,  -811,  -811,   328,  -811,  -811,   516,   328,   541,
    -811,  1606,  -811,   475,   476,  -811,  1846,    80,  -811,  -811,
     526,    94,   300,   220,  -811,   684,   684,  -811,   108,    94,
    -811,  2065,  -811,  -811,   108,   497,    94,  -811,  -811,   414,
     490,  3107,   661,   179,    94,   179,  -811,   538,   494,  -811,
     203,  -811,  -811,  -811,   506,   514,  2396,  -811,  -811,  -811,
    -811,   551,   517,  3363,  -811,   525,   527,  -811,  3597,   531,
     536,  3597,  3597,  2747,   558,  2747,  2747,  3041,  1982,  3113,
    1769,  1481,   697,   697,   426,   426,  -811,  -811,  -811,  -811,
     543,   295,   542,  -811,   215,   285,  -811,  3211,  -811,   549,
     290,  -811,  2124,  -811,   745,   545,   440,  2903,   550,  3399,
    1881,  -811,  -811,  1467,   881,  -811,  -811,   532,   163,  -811,
     568,  3142,  -811,  -811,   487,  2959,   571,    83,   559,  -811,
    -811,  -811,  3503,  -811,   564,   237,  -811,  -811,   208,  -811,
    -811,    82,  -811,  -811,  -811,  3037,  -811,    88,  -811,  -811,
      88,  -811,   608,  -811,  -811,   562,  -811,   565,  -811,  -811,
    -811,  -811,  -811,   573,  -811,   576,  2747,   437,   579,   494,
    -811,   627,  -811,  -811,  -811,  3427,  -811,  -811,   551,  -811,
    -811,  -811,  -811,  -811,   622,  2747,  1330,  2565,  -811,  -811,
     422,  -811,  -811,  -811,   422,  -811,  -811,   580,  -811,  -811,
     252,   590,   437,  -811,  2476,   592,  2524,  -811,  -811,  3503,
    1926,    82,  -811,   596,   609,    82,  -811,   470,  -811,   602,
    -811,  -811,  -811,  -811,   350,   159,  1892,   311,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  3522,   601,
    -811,  -811,  -811,  1070,   305,  -811,  -811,  3474,  -811,   679,
     412,  -811,  -811,  -811,   607,  3268,  -811,  1654,    82,  -811,
    -811,    82,  -811,   614,  -811,  -811,   614,    94,    94,  3597,
    -811,    94,   612,   437,  1035,   627,  -811,  1435,  2747,   659,
     615,  3427,  -811,  -811,  1408,  -811,  -811,  2747,  -811,  -811,
    -811,  -811,  1070,  -811,  -811,  -811,  -811,   437,  -811,  -811,
     644,   470,  -811,  3335,  3335,    69,   684,   350,  3192,  -811,
     635,  2985,   452,   452,  -811,  -811,  -811,   305,    94,   124,
     126,    94,  -811,    94,   126,    94,  3211,  -811,  -811,  -811,
    -811,  -811,   684,  -811,   350,  -811,  1011,  -811,  -811,  3597,
    -811,  -811,  1654,  -811,  -811,   544,  -811,  -811,  -811,    94,
    -811,   294,   423,   955,   630,   631,  1115,  -811,  -811,  -811,
    -811,  -811,   677,   437,  -811,   683,  3597,   657,   673,  -811,
    -811,    72,  1595,   295,  -811,  2747,  -811,   659,  -811,  2747,
     270,   124,   126,    94,   304,  -811,  -811,   642,  -811,   692,
     470,  -811,  -811,  -811,  -811,  2747,   702,   680,  -811,   680,
     723,  1070,  -811,  2183,  -811,  -811,  -811,   588,   305,  -811,
    -811,  -811,   351,   382,  1011,  -811,  -811,  1435,  -811,  -811,
    2747,   185,  -811,  -811,   437,  -811,  -811,  -811,  -811,   682,
    -811,  -811,  -811,  -811,  2264,  -811,  1435,  -811,  -811,  1515,
    -811,  1708,  -811,  -811,  -811,  1408,  -811,  -811,  -811,  -811,
    -811,  1070,  -811,  -811,   699,    78,    78,  3597,  2747,   452,
     520,   520,  -811,  -811,   688,  -811,  -811,   687,  3279,  2747,
    -811,  -811,  -811,  2344,   734,   718,  -811,  -811,   721,   728,
    2747,   750,   715,   719,  2695,   364,   790,   151,   223,  -811,
     760,   724,  -811,   727,  3240,  -811,   789,  1195,    81,  -811,
    -811,  -811,  -811,  -811,  2513,   730,  1708,  -811,  -811,  -811,
     470,  -811,  -811,  -811,  -811,  -811,  3597,  -811,  -811,  -811,
    -811,  3279,  2747,   748,  -811,  2747,  2747,  3561,  -811,  -811,
    -811,  -811,   732,  2747,   735,  -811,   753,    94,  -811,  -811,
     684,  -811,   350,  1275,  -811,  -811,  -811,  -811,  2747,  -811,
    -811,  -811,   752,  -811,   740,  2747,   804,  -811,   859,   755,
     749,  2747,  -811,  -811,   757,  -811,  2747,  -811,   387,  -811,
     200,   389,  -811,   796,  -811,  -811,  2344,   751,  -811,  -811,
     754,  -811,  -811,  -811,  -811,  3579,  -811,    49,  -811,   108,
    -811,   108,  -811,  -811,  -811,   764,  -811,  -811,  2747,  -811,
    -811,   820,   765,  -811,  -811,  -811,  -811,  -811,  -811,   769,
    -811,   791,    64,   766,  -811,  -811,   412,   412,  -811,  -811,
    2747,   820,   771,   820,  -811,  -811,  2747,   781,    68,  -811,
    -811,   783,  -811,   541,   787,  -811,   353,   271,  -811,  -811,
     793,   541,  -811,  -811,   353
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -811,  -811,  -811,  -811,  -811,    79,  -375,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,   -15,  -811,   -58,   443,  -231,   458,
    -811,  -811,   -75,  -811,   135,  -811,  -811,  -811,  -811,  -811,
      44,  -811,  -299,  -811,  -302,   553,  -811,  -811,   218,  -811,
     -20,  -161,    84,    -1,   794,  -811,   251,    19,    10,  -164,
     616,    18,  -237,  -584,   -82,  -201,  -140,  -811,  -811,  -811,
     160,     6,    48,  -811,   483,  -811,   249,  -811,  -585,  -811,
     153,  -811,  -602,  -811,  -811,   224,  -811,  -811,  -811,  -811,
    -811,  -811,   -51,  -115,  -477,   -17,  -811,  -811,  -811,   -41,
    -811,  -811,  -811,  -811,  -811,   425,   -42,  -811,   554,   439,
     254,   555,   434,     3,   -70,  -150,  -157,  -141,   258,  -811,
    -811,  -260,  -811,  -811,  -811,   338,   128,  -811,  -195,  -811,
    -811,  -811,  -811,  -135,  -518,  -691,   261,  -811,    38,  -811,
    -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,    42,
    -811,  -810,     0,  -811,    -3,  -811,   521,  -811,  -356,  -811,
     510,   518,   379,  -292,  -811,  -811,  -811,  -811,    25,  -811,
     910,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -811,  -811,  -811,  -811,  -811,    -5,     5,  -358,  -811,   398,
    -811,   317,   176,  -811,  -811,  -811,  -811,  -811,  -811,  -811,
    -288,  -811,  -811,  -811,   180,   415,  -811,  -811,  -811,  -811,
     -33,   646,  -811,  -811,   431,  -811,   186,   441,  -811,   535,
     546,   -80,  -811,  -110,  -811,  -811,   272,   399,  -811,  -811,
    -811,  -811,  -811,  -811,   598,  -811,  -811,  -811
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -501
static const yytype_int16 yytable[] =
{
     125,   141,    34,    65,    34,   212,    69,    70,   339,    38,
      73,    38,    65,    76,    85,    87,    83,    55,    56,    57,
     437,    74,    35,   436,    35,    96,    98,   100,    44,    72,
      44,    72,   229,   230,   209,   181,   461,   401,   232,    82,
     365,    90,   466,    34,   413,    88,   332,   336,   463,   241,
      38,   502,   220,    89,   316,   225,   533,   655,   722,   349,
     273,   190,   192,    35,   184,   329,   452,   301,   188,    44,
     213,   529,   279,   351,    72,   285,   629,   143,    72,   822,
     753,  -113,   857,   560,    52,    82,    94,   911,   185,   333,
     453,   208,   271,    82,   231,    -2,   197,   300,   919,   219,
       4,   147,   931,    94,    94,    94,   943,   751,   186,   324,
      53,    54,  -337,  -337,  -337,  -337,   339,   410,   404,   236,
    -337,  -337,  -337,   101,    16,   912,   941,   198,   199,   673,
      94,   289,   187,   293,   143,   405,  -337,   148,    94,   858,
     932,   323,   777,   866,   944,   182,   340,   341,   278,   818,
     744,   278,    18,  -337,    16,   823,    16,   295,   371,   551,
     517,   815,  -113,   284,   363,   183,    -3,   304,   305,    58,
     308,   309,    59,   220,   314,  -337,   296,   413,   318,   368,
    -337,   620,   712,   713,   198,   199,   401,   192,   349,   -36,
    -112,   143,   329,   415,   902,   459,    18,    82,   416,    60,
     208,    82,   351,   329,   356,   146,    61,    62,    18,   329,
     208,   402,   357,   915,   861,    16,   918,   457,   920,   409,
     219,   460,   313,   779,   783,   376,   928,   197,   198,   199,
    -176,    61,    62,   770,   771,  -176,    84,    61,    62,   610,
     220,   143,   375,   703,   221,    16,   315,   379,   352,   380,
     224,   697,   399,    61,    62,   403,    94,   143,   952,   226,
     605,   -35,   143,   500,   143,   275,   878,    94,    18,   504,
      63,   547,   189,   276,   277,    64,   148,  -176,   340,   341,
     721,  -176,   278,   465,   558,   548,   193,   425,   334,   559,
     194,   484,   335,   488,   342,    63,   458,   418,   194,   427,
      64,    63,   238,    77,   202,   239,    64,   313,    77,    72,
      95,   473,   143,   475,   556,   314,    97,    63,   557,   318,
      16,   228,    64,   699,   667,   494,    94,    38,   596,   469,
      16,   471,    99,   597,   575,    16,   575,   886,   208,   240,
     275,   208,   208,   411,   412,   357,   756,   950,   276,   277,
     203,   243,   951,    77,   507,   632,   242,   683,   204,   531,
     532,   501,   271,   627,   277,   640,   690,    61,    62,   284,
     143,   733,   205,   220,  -478,   734,   243,   352,   378,    94,
      16,   760,   272,   381,   382,   761,   198,   199,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
      78,   289,   274,   736,   301,   589,   741,   282,    79,   726,
     278,   534,   764,    38,   843,    91,   278,    92,   302,   515,
     772,   553,   554,   528,    61,    62,    38,   524,   775,    38,
     535,    63,   335,    72,   300,   312,    64,    38,   306,   516,
      61,    62,   143,    61,    62,   286,   287,   288,    90,   668,
     536,   319,    88,   143,   683,    77,   202,   547,   345,   776,
      89,   346,   357,   194,   898,   565,   900,   711,   335,   710,
     194,   548,   718,   566,   354,   717,   262,   263,   264,   294,
     411,   412,    16,   631,   635,   361,   405,   726,    63,   362,
     705,  -279,  -279,    64,   363,   602,   366,   599,   -86,   462,
     450,   735,   203,   417,    63,   377,   468,    63,   419,    64,
     204,   687,    64,   420,   474,   616,   617,   615,   515,   575,
     496,   497,    90,   422,   205,    38,    88,   622,   623,   668,
     428,   742,   862,  -476,    89,   212,   630,   634,   516,   432,
      82,   433,    90,   197,   642,   644,    88,    77,   202,   805,
     104,    61,    62,   450,    89,   540,   541,   542,   449,   628,
     633,   456,   723,    38,   467,   543,   284,   470,   660,   500,
     504,   706,   706,   476,    16,   477,   500,   504,   712,   713,
     701,   702,   730,   645,   480,   692,   245,   247,   805,   486,
     482,    77,   696,   487,   203,   313,   495,   913,   534,   914,
     615,   490,   204,   491,   731,   220,   424,   492,   628,    77,
     192,   579,   493,   313,   526,    63,   205,   535,    16,   498,
      64,   508,   208,    82,    38,   499,   512,   615,   208,   208,
     594,   530,   503,   633,   550,   552,    16,   536,   632,   143,
     555,   572,    38,   569,   946,   570,   627,   277,   208,   606,
      82,   577,   954,   608,   578,   774,    78,   581,   745,   583,
     593,   208,   347,   595,    79,     7,   598,     9,   140,   601,
     540,   541,   542,    11,    12,    13,    94,   557,   624,   339,
     612,    94,   639,   220,   641,   607,   801,    77,   202,    15,
     659,   805,    17,   314,   318,   654,   651,   685,   686,   653,
     314,   318,   649,   540,   541,   542,    18,   698,  -316,   740,
     540,   541,   542,   704,    16,   -33,   628,   628,   706,   781,
     762,   747,   676,   633,   633,   801,    77,   625,    24,   800,
     313,   934,   935,    26,   203,   748,   842,   656,   657,   273,
     768,   658,   204,   803,   692,   260,   261,   262,   263,   264,
      38,   216,   217,    16,   749,   763,   205,    11,    12,    13,
     782,   769,   821,   804,   329,   829,   329,   628,   800,   814,
     881,   828,   -34,   626,   864,   208,   832,   867,   870,   835,
     844,   627,   277,   850,   852,   874,   836,   649,   838,   714,
     715,   716,   839,    74,   719,   720,   840,   845,   847,   880,
     887,   848,    72,    72,   849,   853,   865,   890,   860,   873,
      90,   876,   875,   803,    88,   888,   889,   676,   897,   732,
      38,   891,    89,   197,   755,   894,  -176,   905,   801,   921,
     906,  -176,   893,   804,   896,   883,   215,   216,   217,   814,
     767,   916,   925,    11,    12,    13,   929,   933,   939,   930,
     867,   757,   758,   759,   198,   199,   208,   942,    82,   945,
     511,    16,   676,   196,   948,   778,   -29,   -29,   -29,   -29,
     953,   800,   937,  -176,   -29,   -29,   -29,  -176,   867,   868,
     454,   676,   737,   214,   676,     7,   676,     9,   140,   197,
     -29,   780,  -176,    11,    12,    13,   724,  -176,   859,   509,
     414,   728,   817,   826,   582,   752,   472,   -29,   729,    15,
     576,   580,   265,   266,   831,   479,   267,   268,   269,   270,
     198,   199,   738,   670,   903,   837,    18,   743,   904,   -29,
     940,   938,   505,   522,   -29,   892,   638,    75,   830,  -176,
     709,   523,   621,  -176,   -29,   827,   825,   819,    24,   426,
     604,   676,   619,    26,   513,   600,   324,   754,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,   514,  -125,  -125,  -125,  -125,
    -125,   489,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,  -125,  -125,     0,  -125,  -125,
     688,   863,     0,     0,     0,  -125,     0,     0,  -125,     0,
    -125,     0,     0,  -125,  -125,  -125,   895,   877,  -125,  -125,
       0,     0,     0,  -125,  -125,     0,   725,   216,   217,  -125,
       0,  -125,  -125,    11,    12,    13,  -125,  -125,     0,     0,
    -125,     0,  -125,  -125,  -125,  -125,   662,  -125,  -337,  -337,
    -337,  -337,  -337,  -337,  -337,     0,  -337,  -337,  -337,  -337,
    -337,     0,  -337,  -337,  -337,  -337,  -337,  -337,  -337,  -337,
    -337,  -337,  -337,  -337,  -337,  -337,  -337,     0,  -337,  -337,
       0,     0,     0,    77,   625,  -337,     0,     0,  -337,     0,
    -337,     0,     0,  -337,  -337,  -337,     0,     0,  -337,  -337,
       0,   265,   266,  -337,  -337,   267,   268,   269,   270,  -337,
      16,  -337,  -337,     0,     0,     0,  -337,  -337,     0,     0,
    -337,     0,  -337,     0,  -337,  -337,   324,  -337,  -337,  -337,
     626,     0,     0,  -337,  -337,     0,  -337,     0,   627,   277,
    -337,     0,  -337,  -337,  -337,  -337,  -337,  -337,  -337,  -337,
    -337,  -337,  -337,     0,  -337,     0,  -337,     0,  -337,  -337,
       0,     0,     0,     0,     0,  -337,     0,     0,  -337,     0,
       0,     0,     0,  -337,  -337,  -337,     0,     0,  -337,  -337,
       0,     0,     0,  -337,  -337,     0,     0,     0,     0,  -337,
       0,  -337,  -337,     0,     0,     0,  -337,  -337,     0,     0,
    -337,     0,  -337,  -312,  -337,  -337,   854,  -337,  -337,  -337,
       0,     0,     0,  -337,  -337,     0,  -337,     0,     0,     0,
    -337,     0,  -337,  -337,  -337,  -337,  -337,  -337,  -337,  -337,
    -337,  -337,  -337,     0,  -337,     0,  -337,     0,  -337,  -337,
       0,     0,     0,     0,     0,  -337,     0,     0,  -337,     0,
       0,     0,     0,  -337,  -337,  -337,     0,     0,  -337,  -337,
       0,     0,     0,  -337,  -337,     0,     0,     0,     0,  -337,
       0,  -337,  -337,     0,     0,     0,  -337,  -337,     0,     0,
    -337,     0,  -337,     0,  -337,  -337,   884,  -337,  -347,  -347,
       0,     0,     0,  -347,  -347,     0,  -347,     0,     0,     0,
    -347,     0,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,     0,  -347,     0,  -347,     0,  -347,  -347,
       0,     0,     0,     0,     0,  -347,     0,     0,  -347,     0,
       0,     0,     0,  -347,  -347,  -347,     0,     0,  -347,  -347,
       0,     0,     0,  -347,  -347,     0,     0,     0,     0,  -347,
       0,  -347,  -347,     0,     0,     0,  -347,  -347,     0,     0,
    -347,     0,  -347,     0,  -347,  -347,   233,  -347,   102,     7,
       0,     9,   140,   103,   104,     0,   105,    11,    12,    13,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,    15,   106,     0,    17,     0,   107,   108,
       0,     0,     0,     0,     0,   109,     0,     0,   110,     0,
      18,     0,     0,   111,   112,   113,     0,     0,   114,   115,
       0,     0,     0,   116,   117,     0,     0,     0,     0,   118,
       0,   119,    24,     0,     0,     0,   120,    26,     0,     0,
     121,     0,     0,     0,   122,   123,   671,   -95,   672,    62,
       0,     0,     0,   103,   104,   250,   105,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,     0,     0,     0,   106,     0,    17,     0,   107,   108,
       0,     7,     8,     9,    10,   109,     0,   440,   110,    11,
      12,    13,     0,   111,   112,   113,     0,     0,   114,   115,
       0,     0,   673,   116,   117,    15,     0,    16,     0,   118,
       0,   119,    63,     0,     0,     0,   120,    64,     0,     0,
     121,     0,    18,  -204,   122,   123,   671,   674,   672,    62,
       0,     0,     0,   103,   104,     0,   105,   258,   259,   260,
     261,   262,   263,   264,    24,     0,     0,     0,     0,    26,
       0,     0,     0,     0,   106,     0,    17,     0,   107,   108,
       0,     0,     0,     0,     0,   109,     0,     0,   110,     0,
       0,     0,     0,   111,   112,   113,     0,     0,   114,   115,
       0,     0,   673,   116,   117,     0,     0,     0,     0,   118,
       0,   119,    63,     0,     0,     0,   120,    64,     0,     0,
     121,     0,     0,  -269,   122,   123,   671,   674,   102,     0,
       0,     0,     0,   103,   104,     0,   105,   438,     0,   439,
       7,     8,     9,    10,     0,     0,   440,     0,    11,    12,
      13,     0,     0,     0,   106,     0,    17,     0,   107,   108,
    -217,     0,     0,     0,    15,   109,    16,     0,   110,     0,
       0,     0,     0,   111,   112,   113,     0,     0,   114,   115,
       0,    18,  -217,   116,   117,   647,     0,   102,     0,   118,
       0,   119,   103,   104,     0,   105,   120,     0,     0,     0,
     121,     0,     0,    24,   122,   123,     0,   674,    26,     0,
       0,     0,  -397,   106,     0,    17,     0,   107,   108,     0,
       0,     0,     0,     0,   109,     0,     0,   110,     0,     0,
       0,     0,   111,   112,   113,     0,     0,   114,   115,   671,
       0,   102,   116,   117,     0,     0,   103,   104,   118,   105,
     119,     0,     0,     0,     0,   120,     0,     0,     0,   121,
       0,     0,     0,   122,   123,     0,   648,   106,     0,    17,
       0,   107,   108,     0,     0,     0,     0,     0,   109,     0,
       0,   110,     0,     0,     0,     0,   111,   112,   113,     0,
       0,   114,   115,     0,     0,   343,   116,   117,   -25,   -25,
     -25,   -25,   118,     0,   119,     0,   -25,   -25,   -25,   120,
       0,     0,     0,   121,     0,     0,     0,   122,   123,     0,
     674,   197,   -25,     0,  -176,     0,     0,     0,     0,  -176,
     337,     0,     0,   -21,   -21,   -21,   -21,     0,     0,   -25,
       0,   -21,   -21,   -21,   257,   258,   259,   260,   261,   262,
     263,   264,   198,   199,     0,     0,   197,   -21,     0,  -176,
       0,   -25,     0,     0,  -176,     0,   -25,     0,     0,     0,
       0,  -176,     0,     0,   -21,  -176,   -25,   324,     0,     0,
    -116,  -116,  -116,  -116,     0,     0,  -116,     0,  -116,  -116,
    -116,     0,     0,     0,     0,     0,   -21,     0,     0,     0,
       0,   -21,     0,     0,  -116,     0,  -176,     0,     0,     0,
    -176,   -21,   324,     0,     0,     7,     8,     9,    10,     0,
       0,  -116,     0,    11,    12,    13,     7,     8,     9,    10,
       0,     0,     0,     0,    11,    12,    13,     0,     0,    15,
       0,    16,     0,  -116,     0,     0,     0,     0,  -116,     0,
      15,     0,    16,     0,     0,     0,    18,   324,  -116,     0,
    -500,  -500,  -500,  -500,     0,     0,     0,    18,  -500,  -500,
    -500,     0,     0,     0,   102,     0,     0,     0,    24,   103,
     104,     0,   105,    26,  -500,     0,  -500,     0,     0,    24,
       0,     0,     0,  -498,    26,     0,     0,     0,     0,    86,
     106,  -500,    17,     0,   107,   108,     0,     0,     0,     0,
       0,   109,     0,     0,   110,     0,     0,     0,     0,   111,
     112,   113,     0,  -500,   114,   115,     0,     0,  -500,   116,
     117,     0,     0,     0,     0,   118,     0,   119,  -500,   102,
       0,     0,   120,     0,   103,   104,   121,   105,     0,     0,
     122,   123,     0,     0,   322,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   106,     0,    17,     0,   107,
     108,     0,     0,     0,     0,     0,   109,     0,     0,   110,
       0,     0,     0,     0,   111,   112,   113,     0,     0,   114,
     115,     0,     0,     0,   116,   117,     0,     0,   102,     0,
     118,     0,   119,   103,   104,     0,   105,   120,     0,     0,
       0,   121,     0,     0,     0,   122,   123,     0,     0,   408,
       0,     0,     0,     0,   106,     0,    17,     0,   107,   108,
       0,     0,     0,     0,     0,   109,     0,     0,   110,     0,
       0,     0,     0,   111,   112,   113,     0,     0,   114,   115,
       0,     0,     0,   116,   117,     0,     0,   102,     0,   118,
       0,   119,   103,   104,     0,   105,   120,     0,     0,     0,
     121,     0,     0,     0,   122,   123,     0,     0,   464,     0,
       0,     0,     0,   106,     0,    17,     0,   107,   108,     0,
       0,     0,     0,     0,   109,     0,     0,   110,     0,     0,
       0,     0,   111,   112,   113,     0,     0,   114,   115,     0,
       0,     0,   116,   117,     0,     0,   102,     0,   118,     0,
     119,   103,   104,     0,   105,   120,     0,     0,     0,   121,
       0,     0,     0,   122,   123,     0,     0,   506,     0,     0,
       0,     0,   106,     0,    17,     0,   107,   108,     0,     0,
       0,     0,     0,   109,     0,     0,   110,     0,     0,     0,
       0,   111,   112,   113,     0,     0,   114,   115,     0,     0,
       0,   116,   117,     0,     0,     0,     0,   118,     0,   119,
       0,     0,     0,     0,   120,     0,     0,     0,   121,     0,
       0,     0,   122,   123,     0,     0,   773,   672,   784,     8,
       9,    10,   103,   104,     0,   105,    11,    12,    13,   785,
       0,   786,   787,   788,   789,   790,   791,   792,   793,   794,
     795,   796,    15,   106,    16,    17,     0,   107,   108,     0,
       0,     0,     0,     0,   109,     0,     0,   110,     0,    18,
       0,     0,   111,   112,   113,     0,     0,   114,   115,     0,
       0,     0,   116,   117,     0,     0,     0,     0,   118,     0,
     119,   797,     0,     0,     0,   120,   798,     0,     0,   121,
       0,   799,     0,   122,   123,     0,   363,   672,    62,     0,
       0,     0,   103,   104,     0,   105,     0,     0,     0,   785,
       0,   786,   787,   788,   789,   790,   791,   792,   793,   794,
     795,   796,     0,   106,     0,    17,     0,   107,   108,     0,
       0,     0,     0,     0,   109,     0,     0,   110,     0,     0,
       0,     0,   111,   112,   113,     0,     0,   114,   115,   102,
       0,     0,   116,   117,   103,   104,     0,   105,   118,     0,
     119,    63,     0,     0,     0,   120,    64,     0,     0,   121,
       0,   799,     0,   122,   123,   106,   363,    17,     0,   107,
     108,     0,     0,     0,     0,     0,   109,     0,     0,   110,
       0,     0,     0,     0,   111,   112,   113,     0,     0,   114,
     115,     0,     0,     0,   116,   117,     0,     0,     0,     0,
     118,     0,   119,     0,     0,     0,     0,   120,     0,     0,
       0,   121,     0,     0,     0,   122,   123,     0,   483,   149,
     150,     0,   151,   152,     0,     0,     0,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,     0,     0,     0,     0,
       0,     0,     0,     0,   172,     0,   102,     7,     8,     9,
      10,   103,   104,     0,   105,    11,    12,    13,     7,     8,
       9,    10,     0,     0,     0,     0,    11,    12,    13,     0,
       0,    15,   106,    16,    17,     0,   107,   108,   174,     0,
       0,     0,    15,   109,    16,     0,   110,   298,    18,     0,
       0,   111,   112,   113,     0,     0,   114,   115,     0,    18,
       0,   116,   117,     0,     0,     0,     0,   118,     0,   119,
      24,     0,     0,     0,   120,    26,     0,     0,   121,     0,
       0,    24,   122,   123,   102,     7,    26,     9,   140,   103,
     104,   603,   105,    11,    12,    13,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,     0,    15,
     106,     0,    17,     0,   107,   108,     0,     0,     0,     0,
       0,   109,     0,     0,   110,     0,    18,     0,     0,   111,
     112,   113,     0,     0,   114,   115,   102,     0,     0,   116,
     117,   103,   104,     0,   105,   118,     0,   119,    24,     0,
       0,     0,   120,    26,     0,     0,   121,     0,     0,     0,
     122,   123,   106,     0,    17,     0,   107,   108,     0,     0,
       0,     0,     0,   109,     0,     0,   110,     0,     0,     0,
       0,   111,   112,   113,     0,     0,   114,   115,   102,     0,
       0,   116,   117,   103,   104,     0,   105,   118,     0,   119,
     367,     0,     0,     0,   120,     0,     0,     0,   121,     0,
       0,     0,   122,   123,   106,     0,    17,     0,   107,   108,
       0,     0,     0,     0,     0,   109,     0,     0,   110,     0,
       0,     0,     0,   111,   112,   113,     0,     0,   114,   115,
     102,     0,     0,   116,   117,   103,   104,     0,   105,   118,
       0,   119,     0,     0,     0,     0,   120,     0,     0,     0,
     121,     0,   841,     0,   122,   123,   106,     0,    17,     0,
     107,   108,     0,     0,     0,     0,     0,   109,     0,     0,
     110,     0,     0,     0,     0,   111,   112,   113,     0,     0,
     114,   115,   102,     0,     0,   116,   117,   103,   104,     0,
     105,   118,     0,   119,     0,     0,     0,     0,   120,     0,
       0,     0,   121,     0,     0,     0,   122,   123,   106,     0,
      17,     0,   107,   108,     0,     0,     0,     0,     0,   109,
       0,     0,   110,     0,     0,     0,     0,   111,   112,   113,
       0,     0,   114,   115,   102,     0,     0,   244,   117,   103,
     104,     0,   105,   118,     0,   119,     0,     0,     0,     0,
     120,     0,     0,     0,   121,     0,     0,     0,   122,   123,
     106,     0,    17,     0,   107,   108,     0,     0,     0,     0,
       0,   109,     0,     0,   110,     0,     0,     0,     0,   111,
     112,   113,     0,     0,   114,   115,   510,     0,     0,   246,
     117,   103,   104,     0,   105,   118,     0,   119,     0,     0,
       0,     0,   120,     0,     0,     0,   121,     0,     0,     0,
     122,   123,   106,     0,    17,     0,   107,   108,     0,     0,
       0,     0,     0,   109,     0,     0,   110,     0,     0,     0,
       0,   111,   112,   113,     0,     0,   114,   115,     0,     0,
     545,   116,   117,     7,     0,     9,   140,   118,     0,   119,
       0,    11,    12,    13,   120,     0,     0,     0,   121,     0,
       0,     0,   122,   123,     0,     0,   545,    15,     0,     7,
     347,     9,   140,     7,     0,     9,   140,    11,    12,    13,
       0,    11,    12,    13,    18,     0,     0,     0,     0,     0,
       0,     0,     0,    15,     0,     0,     0,    15,     0,     0,
      17,     0,     0,     0,     0,     0,    24,  -452,  -452,  -452,
      18,    26,     0,     0,    18,     0,   546,  -452,     0,     0,
       0,     7,     8,     9,    10,     0,     0,     0,     0,    11,
      12,    13,    24,  -451,  -451,  -451,    24,    26,     0,     0,
       0,    26,   546,  -451,     0,    15,   348,  -272,     6,     0,
    -129,     7,     8,     9,    10,     0,     0,     0,     0,    11,
      12,    13,    18,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,    14,    15,     0,    16,    17,     0,
       0,     0,     0,     0,    24,     0,     0,     0,     0,    26,
       0,     7,    18,     9,   283,    19,    20,  -129,     0,    11,
      12,    13,     0,     0,     0,  -129,     0,     0,    21,    22,
      23,     0,     0,     0,    24,    15,     0,     0,    25,    26,
      27,    28,     0,     6,    29,  -129,     7,     8,     9,    10,
       0,     0,    18,     0,    11,    12,    13,   256,   257,   258,
     259,   260,   261,   262,   263,   264,     0,     0,     0,     0,
      15,     0,    16,     0,    24,     0,     0,     0,     0,    26,
       0,     0,     0,     0,  -281,  -281,     0,    18,     0,     0,
     531,   532,  -129,     6,     0,  -129,     7,     8,     9,    10,
    -129,     0,     0,     0,    11,    12,    13,     0,     0,    24,
       0,     0,   438,     0,    26,     7,     8,     9,    10,    29,
      15,   440,    16,    11,    12,    13,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,     0,    15,
       0,    16,  -129,     0,     7,     8,     9,    10,     0,     0,
    -129,     0,    11,    12,    13,     0,    18,     0,     0,    24,
       0,     0,     0,     0,    26,     0,     0,     0,    15,    29,
      16,     0,     7,    91,     9,    92,     0,     0,    24,     0,
      11,    12,    13,    26,     0,    18,     0,  -397,     0,     0,
       0,     0,     0,     0,     0,     0,    15,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,    16,
       0,     0,    26,    18,   248,   249,   250,   851,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,     0,     0,     0,    24,     0,     0,   149,   150,
      26,   151,   152,     0,     0,   643,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,     0,   149,   150,     0,   151,
     152,     0,     0,   172,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   173,     0,     0,     0,     0,     0,     0,
       0,   370,   149,   150,     0,   151,   152,   174,     0,     0,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,     0,
     149,   150,     0,   151,   152,   174,     0,   172,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,     0,     0,     7,
       0,     9,   283,     0,     0,   588,     0,    11,    12,    13,
       0,   174,     0,     0,     0,     0,     0,     0,     7,     8,
       9,    10,     0,    15,   637,    16,    11,    12,    13,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   174,
      18,     0,    15,     0,    16,   275,     0,     7,     8,     9,
      10,     0,     0,   276,   277,    11,    12,    13,     0,    18,
       0,     0,    24,     0,     0,     0,     7,    26,     9,   283,
       0,    15,     0,    16,    11,    12,    13,     0,     0,     0,
       0,    24,     0,     0,     0,     0,    26,     0,    18,     0,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,     0,     0,
      24,   871,     0,     0,     0,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    24,
       0,     0,     0,     0,    26,     0,   248,   249,   250,   872,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   248,   249,   250,   910,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   248,   249,   250,     0,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-811)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      58,    59,     3,    18,     5,    87,    21,    22,   209,     3,
      25,     5,    27,    28,    34,    35,    33,    11,    12,    13,
     319,    26,     3,   311,     5,    40,    41,    42,     3,    24,
       5,    26,   107,   108,    85,    68,   338,   268,   113,    33,
     235,    35,   344,    44,   281,    35,   203,   208,   340,   124,
      44,   407,    93,    35,   194,    97,   431,   575,   642,   223,
     135,    76,    79,    44,    69,   200,   326,   177,    73,    44,
      87,   429,   142,   223,    69,   145,   553,    59,    73,     1,
     682,     1,     1,     1,     5,    79,    38,    38,    38,   204,
      10,    85,     9,    87,   109,     0,    27,   177,   908,    93,
       0,    45,    38,    55,    56,    57,    38,    35,    58,     1,
      77,    78,     4,     5,     6,     7,   317,   278,   275,   116,
      12,    13,    14,    44,    30,    76,   936,    58,    59,    57,
      82,   146,    82,   148,   116,   276,    28,    81,    90,    58,
      76,   199,   727,   834,    76,    38,    58,    59,   142,   751,
     668,   145,    45,    45,    30,    77,    30,   172,   238,    76,
     420,   746,    82,   145,    82,    58,     0,   182,   183,    58,
     185,   186,    58,   214,   191,    67,   173,   414,   195,   237,
      72,   539,    58,    59,    58,    59,   417,   204,   352,    38,
      82,   173,   327,    76,   885,   335,    45,   191,    81,    58,
     194,   195,   352,   338,     1,    58,     3,     4,    45,   344,
     204,   269,   227,   904,   816,    30,   907,   332,   909,   277,
     214,   336,     7,    38,   742,   240,   917,    27,    58,    59,
      30,     3,     4,   710,   711,    35,    77,     3,     4,   527,
     281,   223,   239,   618,    65,    30,    76,   244,   223,   246,
      82,   609,   267,     3,     4,   270,   208,   239,   949,    82,
     520,    38,   244,   404,   246,    50,   850,   219,    45,   410,
      67,   435,    77,    58,    59,    72,    81,    77,    58,    59,
     636,    81,   276,   341,    76,   435,    77,   302,    77,    81,
      81,   366,    81,   373,    77,    67,    76,   294,    81,   304,
      72,    67,    58,     3,     4,    58,    72,     7,     3,   304,
      82,   353,   294,   355,    77,   332,    82,    67,    81,   336,
      30,    82,    72,   611,   584,   383,   278,   321,    76,   349,
      30,   351,    82,    81,   469,    30,   471,   855,   332,    58,
      50,   335,   336,    58,    59,   360,    76,    76,    58,    59,
      50,    81,    81,     3,   412,    50,    76,   588,    58,    48,
      49,    76,     9,    58,    59,   560,   597,     3,     4,   351,
     352,    77,    72,   414,    63,    81,    81,   352,   243,   331,
      30,    77,    75,   248,   249,    81,    58,    59,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
      50,   416,    76,   663,   514,   485,   666,    76,    58,   646,
     404,   431,   700,   407,    50,     5,   410,     7,    38,   420,
     712,   441,   442,   428,     3,     4,   420,   424,    77,   423,
     431,    67,    81,   428,   514,    77,    72,   431,    82,   420,
       3,     4,   424,     3,     4,     5,     6,     7,   442,   584,
     431,    58,   442,   435,   685,     3,     4,   621,    58,    77,
     442,    78,   477,    81,    77,   455,    77,   628,    81,   626,
      81,   621,   633,   455,    78,   632,    50,    51,    52,    58,
      58,    59,    30,   553,   554,    76,   627,   724,    67,    76,
      38,    77,    78,    72,    82,   515,    76,   512,    38,   339,
      77,    78,    50,    58,    67,    77,   346,    67,    76,    72,
      58,   591,    72,    77,   354,   535,   536,   534,   519,   654,
     385,   386,   516,    10,    72,   519,   516,   547,   548,   664,
      76,   666,   820,    63,   516,   617,   553,   554,   519,    82,
     534,    76,   536,    27,   564,   565,   536,     3,     4,   744,
       9,     3,     4,    77,   536,    68,    69,    70,    83,   553,
     554,    35,   644,   557,    67,    78,   548,    77,   583,   710,
     711,   622,   623,    35,    30,    81,   717,   718,    58,    59,
     613,   614,    38,   565,    78,   602,   128,   129,   783,    38,
      76,     3,   607,    76,    50,     7,    38,   899,   618,   901,
     617,    76,    58,    76,   655,   646,    58,    76,   602,     3,
     627,   476,    76,     7,    82,    67,    72,   618,    30,    76,
      72,    76,   616,   617,   618,    83,    76,   644,   622,   623,
     495,    63,    83,   627,    63,    76,    30,   618,    50,   621,
      76,    76,   636,    35,   943,    83,    58,    59,   642,   521,
     644,    78,   951,   525,    78,   713,    50,    78,   673,    32,
      38,   655,     1,    83,    58,     4,    76,     6,     7,    77,
      68,    69,    70,    12,    13,    14,   628,    81,    77,   880,
      78,   633,     3,   724,    77,    76,   744,     3,     4,    28,
      78,   886,    31,   710,   711,    81,   568,    38,    83,   571,
     717,   718,   567,    68,    69,    70,    45,    63,    78,    78,
      68,    69,    70,    78,    30,    38,   710,   711,   769,   734,
      78,    38,   587,   717,   718,   783,     3,     4,    67,   744,
       7,   926,   927,    72,    50,    78,   794,   577,   578,   814,
      38,   581,    58,   744,   761,    48,    49,    50,    51,    52,
     744,     6,     7,    30,    81,    63,    72,    12,    13,    14,
      78,    81,    63,   744,   899,    78,   901,   761,   783,   744,
     852,    83,    38,    50,   832,   769,    58,   835,   836,    58,
     795,    58,    59,   803,   804,   843,    58,   652,    38,   629,
     630,   631,    77,   798,   634,   635,    77,     7,    38,   850,
     858,    77,   797,   798,    77,    16,    58,   865,    78,    77,
     804,    58,    77,   814,   804,    63,    76,   682,   876,   659,
     814,    17,   804,    27,   689,    76,    30,    76,   886,     9,
      76,    35,    77,   814,    77,   852,     5,     6,     7,   814,
     705,    77,    77,    12,    13,    14,    77,    81,    77,    58,
     908,   691,   692,   693,    58,    59,   850,    76,   852,    76,
     417,    30,   727,     1,    77,   730,     4,     5,     6,     7,
      77,   886,   930,    77,    12,    13,    14,    81,   936,   835,
     327,   746,   664,    89,   749,     4,   751,     6,     7,    27,
      28,   731,    30,    12,    13,    14,   645,    35,   814,   416,
     284,   652,   749,   768,   479,   681,   352,    45,   654,    28,
     471,   477,    53,    54,   779,   360,    57,    58,    59,    60,
      58,    59,   664,   585,   886,   790,    45,   666,   886,    67,
     933,   931,   411,   423,    72,    76,   557,    27,   778,    77,
     623,   423,   544,    81,    82,   769,   766,   761,    67,   303,
     519,   816,   537,    72,   419,   514,     1,   685,     3,     4,
       5,     6,     7,     8,     9,   419,    11,    12,    13,    14,
      15,   373,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    34,
     591,   831,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      45,    -1,    -1,    48,    49,    50,   871,   847,    53,    54,
      -1,    -1,    -1,    58,    59,    -1,     5,     6,     7,    64,
      -1,    66,    67,    12,    13,    14,    71,    72,    -1,    -1,
      75,    -1,    77,    78,    79,    80,     1,    82,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    34,
      -1,    -1,    -1,     3,     4,    40,    -1,    -1,    43,    -1,
      45,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,    53,    54,    58,    59,    57,    58,    59,    60,    64,
      30,    66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      75,    -1,    77,    -1,    79,    80,     1,    82,     3,     4,
      50,    -1,    -1,     8,     9,    -1,    11,    -1,    58,    59,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    29,    -1,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,    -1,    -1,    58,    59,    -1,    -1,    -1,    -1,    64,
      -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      75,    -1,    77,    78,    79,    80,     1,    82,     3,     4,
      -1,    -1,    -1,     8,     9,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    29,    -1,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,    -1,    -1,    58,    59,    -1,    -1,    -1,    -1,    64,
      -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      75,    -1,    77,    -1,    79,    80,     1,    82,     3,     4,
      -1,    -1,    -1,     8,     9,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    29,    -1,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,    -1,    -1,    58,    59,    -1,    -1,    -1,    -1,    64,
      -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      75,    -1,    77,    -1,    79,    80,     1,    82,     3,     4,
      -1,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    28,    29,    -1,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      45,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,    -1,    -1,    58,    59,    -1,    -1,    -1,    -1,    64,
      -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      75,    -1,    -1,    -1,    79,    80,     1,    82,     3,     4,
      -1,    -1,    -1,     8,     9,    37,    11,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    34,
      -1,     4,     5,     6,     7,    40,    -1,    10,    43,    12,
      13,    14,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,    -1,    57,    58,    59,    28,    -1,    30,    -1,    64,
      -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      75,    -1,    45,    78,    79,    80,     1,    82,     3,     4,
      -1,    -1,    -1,     8,     9,    -1,    11,    46,    47,    48,
      49,    50,    51,    52,    67,    -1,    -1,    -1,    -1,    72,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,    -1,    57,    58,    59,    -1,    -1,    -1,    -1,    64,
      -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      75,    -1,    -1,    78,    79,    80,     1,    82,     3,    -1,
      -1,    -1,    -1,     8,     9,    -1,    11,     1,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    10,    -1,    12,    13,
      14,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    34,
      35,    -1,    -1,    -1,    28,    40,    30,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,    45,    57,    58,    59,     1,    -1,     3,    -1,    64,
      -1,    66,     8,     9,    -1,    11,    71,    -1,    -1,    -1,
      75,    -1,    -1,    67,    79,    80,    -1,    82,    72,    -1,
      -1,    -1,    76,    29,    -1,    31,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,     1,
      -1,     3,    58,    59,    -1,    -1,     8,     9,    64,    11,
      66,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    -1,    82,    29,    -1,    31,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    53,    54,    -1,    -1,     1,    58,    59,     4,     5,
       6,     7,    64,    -1,    66,    -1,    12,    13,    14,    71,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    -1,
      82,    27,    28,    -1,    30,    -1,    -1,    -1,    -1,    35,
       1,    -1,    -1,     4,     5,     6,     7,    -1,    -1,    45,
      -1,    12,    13,    14,    45,    46,    47,    48,    49,    50,
      51,    52,    58,    59,    -1,    -1,    27,    28,    -1,    30,
      -1,    67,    -1,    -1,    35,    -1,    72,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    45,    81,    82,     1,    -1,    -1,
       4,     5,     6,     7,    -1,    -1,    10,    -1,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    72,    -1,    -1,    28,    -1,    77,    -1,    -1,    -1,
      81,    82,     1,    -1,    -1,     4,     5,     6,     7,    -1,
      -1,    45,    -1,    12,    13,    14,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    12,    13,    14,    -1,    -1,    28,
      -1,    30,    -1,    67,    -1,    -1,    -1,    -1,    72,    -1,
      28,    -1,    30,    -1,    -1,    -1,    45,     1,    82,    -1,
       4,     5,     6,     7,    -1,    -1,    -1,    45,    12,    13,
      14,    -1,    -1,    -1,     3,    -1,    -1,    -1,    67,     8,
       9,    -1,    11,    72,    28,    -1,    30,    -1,    -1,    67,
      -1,    -1,    -1,    82,    72,    -1,    -1,    -1,    -1,    77,
      29,    45,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,
      49,    50,    -1,    67,    53,    54,    -1,    -1,    72,    58,
      59,    -1,    -1,    -1,    -1,    64,    -1,    66,    82,     3,
      -1,    -1,    71,    -1,     8,     9,    75,    11,    -1,    -1,
      79,    80,    -1,    -1,    83,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    29,    -1,    31,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,
      54,    -1,    -1,    -1,    58,    59,    -1,    -1,     3,    -1,
      64,    -1,    66,     8,     9,    -1,    11,    71,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    79,    80,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
      -1,    -1,    -1,    58,    59,    -1,    -1,     3,    -1,    64,
      -1,    66,     8,     9,    -1,    11,    71,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    79,    80,    -1,    -1,    83,    -1,
      -1,    -1,    -1,    29,    -1,    31,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,    -1,
      -1,    -1,    58,    59,    -1,    -1,     3,    -1,    64,    -1,
      66,     8,     9,    -1,    11,    71,    -1,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    29,    -1,    31,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    -1,    53,    54,    -1,    -1,
      -1,    58,    59,    -1,    -1,    -1,    -1,    64,    -1,    66,
      -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    79,    80,    -1,    -1,    83,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    45,
      -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,    -1,
      -1,    -1,    58,    59,    -1,    -1,    -1,    -1,    64,    -1,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    77,    -1,    79,    80,    -1,    82,     3,     4,    -1,
      -1,    -1,     8,     9,    -1,    11,    -1,    -1,    -1,    15,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    29,    -1,    31,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,     3,
      -1,    -1,    58,    59,     8,     9,    -1,    11,    64,    -1,
      66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    77,    -1,    79,    80,    29,    82,    31,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,
      54,    -1,    -1,    -1,    58,    59,    -1,    -1,    -1,    -1,
      64,    -1,    66,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    79,    80,    -1,    82,     3,
       4,    -1,     6,     7,    -1,    -1,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    12,    13,    14,    -1,
      -1,    28,    29,    30,    31,    -1,    33,    34,    72,    -1,
      -1,    -1,    28,    40,    30,    -1,    43,    81,    45,    -1,
      -1,    48,    49,    50,    -1,    -1,    53,    54,    -1,    45,
      -1,    58,    59,    -1,    -1,    -1,    -1,    64,    -1,    66,
      67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,    -1,
      -1,    67,    79,    80,     3,     4,    72,     6,     7,     8,
       9,    77,    11,    12,    13,    14,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    28,
      29,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,    -1,    45,    -1,    -1,    48,
      49,    50,    -1,    -1,    53,    54,     3,    -1,    -1,    58,
      59,     8,     9,    -1,    11,    64,    -1,    66,    67,    -1,
      -1,    -1,    71,    72,    -1,    -1,    75,    -1,    -1,    -1,
      79,    80,    29,    -1,    31,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    -1,    53,    54,     3,    -1,
      -1,    58,    59,     8,     9,    -1,    11,    64,    -1,    66,
      67,    -1,    -1,    -1,    71,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    79,    80,    29,    -1,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    -1,    53,    54,
       3,    -1,    -1,    58,    59,     8,     9,    -1,    11,    64,
      -1,    66,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,
      75,    -1,    77,    -1,    79,    80,    29,    -1,    31,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,
      53,    54,     3,    -1,    -1,    58,    59,     8,     9,    -1,
      11,    64,    -1,    66,    -1,    -1,    -1,    -1,    71,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    79,    80,    29,    -1,
      31,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    -1,    53,    54,     3,    -1,    -1,    58,    59,     8,
       9,    -1,    11,    64,    -1,    66,    -1,    -1,    -1,    -1,
      71,    -1,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,
      29,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,
      49,    50,    -1,    -1,    53,    54,     3,    -1,    -1,    58,
      59,     8,     9,    -1,    11,    64,    -1,    66,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      79,    80,    29,    -1,    31,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    -1,    53,    54,    -1,    -1,
       1,    58,    59,     4,    -1,     6,     7,    64,    -1,    66,
      -1,    12,    13,    14,    71,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    79,    80,    -1,    -1,     1,    28,    -1,     4,
       1,     6,     7,     4,    -1,     6,     7,    12,    13,    14,
      -1,    12,    13,    14,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    28,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      45,    72,    -1,    -1,    45,    -1,    77,    78,    -1,    -1,
      -1,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    12,
      13,    14,    67,    68,    69,    70,    67,    72,    -1,    -1,
      -1,    72,    77,    78,    -1,    28,    77,    78,     1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    12,
      13,    14,    45,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    27,    28,    -1,    30,    31,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    72,
      -1,     4,    45,     6,     7,    48,    49,    50,    -1,    12,
      13,    14,    -1,    -1,    -1,    58,    -1,    -1,    61,    62,
      63,    -1,    -1,    -1,    67,    28,    -1,    -1,    71,    72,
      73,    74,    -1,     1,    77,     3,     4,     5,     6,     7,
      -1,    -1,    45,    -1,    12,    13,    14,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      28,    -1,    30,    -1,    67,    -1,    -1,    -1,    -1,    72,
      -1,    -1,    -1,    -1,    77,    78,    -1,    45,    -1,    -1,
      48,    49,    50,     1,    -1,     3,     4,     5,     6,     7,
      58,    -1,    -1,    -1,    12,    13,    14,    -1,    -1,    67,
      -1,    -1,     1,    -1,    72,     4,     5,     6,     7,    77,
      28,    10,    30,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    28,
      -1,    30,    50,    -1,     4,     5,     6,     7,    -1,    -1,
      58,    -1,    12,    13,    14,    -1,    45,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    28,    77,
      30,    -1,     4,     5,     6,     7,    -1,    -1,    67,    -1,
      12,    13,    14,    72,    -1,    45,    -1,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    30,
      -1,    -1,    72,    45,    35,    36,    37,    77,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    67,    -1,    -1,     3,     4,
      72,     6,     7,    -1,    -1,    77,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,     3,     4,    -1,     6,
       7,    -1,    -1,    38,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,     3,     4,    -1,     6,     7,    72,    -1,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
       3,     4,    -1,     6,     7,    72,    -1,    38,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,     4,
      -1,     6,     7,    -1,    -1,    38,    -1,    12,    13,    14,
      -1,    72,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,
       6,     7,    -1,    28,    10,    30,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      45,    -1,    28,    -1,    30,    50,    -1,     4,     5,     6,
       7,    -1,    -1,    58,    59,    12,    13,    14,    -1,    45,
      -1,    -1,    67,    -1,    -1,    -1,     4,    72,     6,     7,
      -1,    28,    -1,    30,    12,    13,    14,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    -1,    72,    -1,    45,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      67,    10,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    72,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    85,    86,    87,     0,    88,     1,     4,     5,     6,
       7,    12,    13,    14,    27,    28,    30,    31,    45,    48,
      49,    61,    62,    63,    67,    71,    72,    73,    74,    77,
      89,    90,    91,   124,   127,   131,   132,   135,   145,   146,
     170,   171,   172,   173,   242,   243,   245,   246,   247,   257,
     260,   267,    89,    77,    78,   145,   145,   145,    58,    58,
      58,     3,     4,    67,    72,    98,   244,   268,   271,    98,
      98,   259,   260,    98,   259,   244,    98,     3,    50,    58,
     138,   142,   145,   169,    77,   124,    77,   124,   132,   135,
     145,     5,     7,   128,   146,    82,    98,    82,    98,    82,
      98,    89,     3,     8,     9,    11,    29,    33,    34,    40,
      43,    48,    49,    50,    53,    54,    58,    59,    64,    66,
      71,    75,    79,    80,    99,   100,   102,   103,   104,   105,
     106,   108,   114,   116,   117,   242,   303,   309,   310,   311,
       7,   100,   133,   135,   187,   189,    58,    45,    81,     3,
       4,     6,     7,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    38,    58,    72,   284,   293,   294,   295,   296,
     297,   284,    38,    58,   259,    38,    58,    82,   259,    77,
      98,   190,   169,    77,    81,   125,     1,    27,    58,    59,
      96,   139,     4,    50,    58,    72,   137,   140,   145,   166,
     167,   169,   138,   169,   128,     5,     6,     7,   136,   145,
     173,    65,   180,   181,    82,   180,    82,   177,    82,   106,
     106,    98,   106,     1,   100,   115,   187,   304,    58,    58,
      58,   106,    76,    81,    58,   103,    58,   103,    35,    36,
      37,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    57,    58,    59,
      60,     9,    75,   106,    76,    50,    58,    59,   145,   188,
     191,   134,    76,     7,   135,   188,     5,     6,     7,    98,
     147,   148,   149,    98,    58,    98,   187,   269,    81,   291,
     295,   297,    38,   272,    98,    98,    82,   250,    98,    98,
     254,   258,    77,     7,   169,    76,   140,   166,   169,    58,
     237,   238,    83,   100,     1,   118,   119,   120,   195,   207,
     144,   145,   190,   167,    77,    81,   125,     1,    92,   139,
      58,    59,    77,     1,    94,    58,    78,     1,    77,   133,
     182,   189,   242,   174,    78,   175,     1,    98,   185,   186,
     176,    76,    76,    82,   201,   202,    76,    67,   100,   302,
      38,   295,   306,   307,   308,   187,    98,    77,   108,   187,
     187,   108,   108,   111,   113,   110,   109,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,    98,
     101,   102,   100,    98,   190,   191,   230,   231,    83,   100,
     125,    58,    59,   136,   134,    76,    81,    58,   187,    76,
      77,   285,    10,   292,    58,    98,   285,   259,    76,   248,
     274,   275,    82,    76,   261,   263,   274,   116,     1,     3,
      10,   127,   131,   232,   234,   235,   236,   239,   240,    83,
      77,    97,   195,    10,   119,   208,    35,   167,    76,   140,
     167,   118,   144,   237,    83,   100,   118,    67,   144,   124,
      77,   124,   182,   180,   144,   180,    35,    81,   179,   185,
      78,   196,    76,    82,   106,   305,    38,    76,   295,   308,
      76,    76,    76,    76,   100,    38,   108,   108,    76,    83,
     191,    76,   232,    83,   191,   230,    83,   100,    76,   148,
       3,   101,    76,   293,   294,   127,   131,   195,   286,   287,
     288,   270,   234,   235,   187,   273,    82,   253,   259,   261,
      63,    48,    49,    90,   124,   127,   131,   276,   279,   255,
      68,    69,    70,    78,   262,     1,    77,   133,   189,   264,
      63,    76,    76,   124,   124,    76,    77,    81,    76,    81,
       1,   200,   202,   121,   129,   132,   135,   143,    93,    35,
      83,    95,    76,   183,   184,   207,   183,    78,    78,   108,
     186,    78,   179,    32,   197,   198,   199,   107,    38,   295,
     298,   299,   301,    38,   108,    83,    76,    81,    76,    98,
     291,    77,   124,    77,   288,   195,   200,    76,   200,   251,
     274,   256,    78,   280,   282,   169,   124,   124,   277,   279,
     261,   263,   124,   124,    77,     4,    50,    58,   145,   168,
     169,   188,    50,   145,   169,   188,   233,    10,   236,     3,
     202,    77,   124,    77,   124,   135,   130,     1,    82,   108,
     150,   200,   141,   200,    81,   208,   144,   144,   144,    78,
      98,   241,     1,   122,   123,   192,   193,   195,   207,   210,
     199,     1,     3,    57,    82,    98,   108,   152,   153,   154,
     156,   158,   159,   102,   300,    38,    83,   295,   301,   112,
     102,   168,   169,   188,   289,   290,    98,   261,    63,   274,
     249,   284,   284,    90,    78,    38,   166,   265,   266,   265,
     190,   125,    58,    59,   144,   144,   144,   190,   125,   144,
     144,   232,   137,   138,   130,     5,   136,   151,   150,   184,
      38,   166,   144,    77,    81,    78,   195,   122,   192,   194,
      78,   195,   207,   210,   208,    98,   157,    38,    78,    81,
     178,    35,   159,   156,   300,   108,    76,   144,   144,   144,
      77,    81,    78,    63,   274,   281,   283,   108,    38,    81,
     168,   168,   237,    83,   100,    77,    77,   152,   108,    38,
     144,    98,    78,   208,     4,    15,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    67,    72,    77,
      98,   100,   126,   127,   131,   202,   203,   204,   205,   211,
     212,   220,   221,   223,   242,   152,   155,   154,   156,   290,
     252,    63,     1,    77,   278,   278,   108,   266,    83,    78,
     144,   108,    58,   214,   206,    58,    58,   108,    38,    77,
      77,    77,   100,    50,    98,     7,   224,    38,    77,    77,
     124,    77,   124,    16,     1,   207,   209,     1,    58,   126,
      78,   156,   274,   144,   100,    58,   209,   100,   114,   225,
     100,    10,    38,    77,   100,    77,    58,   144,   137,   160,
     166,   138,   163,   169,     1,   213,   208,   100,    63,    76,
     100,    17,    76,    77,    76,   108,    77,   100,    77,   161,
      77,   164,   209,   212,   223,    76,    76,   222,   216,   219,
      38,    38,    76,   118,   118,   209,    77,   215,   209,   225,
     209,     9,   226,   227,   228,    77,   162,   165,   209,    77,
      58,    38,    76,    81,   202,   202,   217,   100,   226,    77,
     228,   225,    76,    38,    76,    76,   116,   229,    77,   218,
      76,    81,   209,    77,   116
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
#line 234 "objc-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids an empty source file");
		  finish_file ();
		}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 239 "objc-parse.y"
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
#line 253 "objc-parse.y"
    {(yyval.ttype) = NULL_TREE; }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 254 "objc-parse.y"
    {(yyval.ttype) = NULL_TREE; }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 262 "objc-parse.y"
    { STRIP_NOPS ((yyvsp[(3) - (5)].ttype));
		  if ((TREE_CODE ((yyvsp[(3) - (5)].ttype)) == ADDR_EXPR
		       && TREE_CODE (TREE_OPERAND ((yyvsp[(3) - (5)].ttype), 0)) == STRING_CST)
		      || TREE_CODE ((yyvsp[(3) - (5)].ttype)) == STRING_CST)
		    assemble_asm ((yyvsp[(3) - (5)].ttype));
		  else
		    error ("argument of `asm' is not a constant string"); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 270 "objc-parse.y"
    { pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 275 "objc-parse.y"
    { if (pedantic)
		    error ("ANSI C forbids data definition with no type or storage class");
		  else if (!flag_traditional)
		    warning ("data definition has no type or storage class"); 

		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(1) - (3)].itype)); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 285 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 290 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype));  }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 295 "objc-parse.y"
    { pedwarn ("empty declaration"); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 297 "objc-parse.y"
    { shadow_tag ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 301 "objc-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C does not allow extra `;' outside of a function"); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 307 "objc-parse.y"
    { if (! start_function (current_declspecs, (yyvsp[(3) - (3)].ttype),
					prefix_attributes, NULL_TREE, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 312 "objc-parse.y"
    { store_parm_decls (); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 314 "objc-parse.y"
    { finish_function (0); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (7)].itype)); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 320 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 325 "objc-parse.y"
    { if (! start_function (current_declspecs, (yyvsp[(3) - (3)].ttype),
					prefix_attributes, NULL_TREE, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 330 "objc-parse.y"
    { store_parm_decls (); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 332 "objc-parse.y"
    { finish_function (0); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (7)].itype)); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 338 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 343 "objc-parse.y"
    { if (! start_function (NULL_TREE, (yyvsp[(2) - (2)].ttype),
					prefix_attributes, NULL_TREE, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 348 "objc-parse.y"
    { store_parm_decls (); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 350 "objc-parse.y"
    { finish_function (0); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(1) - (6)].itype)); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 356 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(1) - (3)].itype)); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 370 "objc-parse.y"
    { (yyval.code) = ADDR_EXPR; }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 372 "objc-parse.y"
    { (yyval.code) = NEGATE_EXPR; }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 374 "objc-parse.y"
    { (yyval.code) = CONVERT_EXPR; }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 376 "objc-parse.y"
    { (yyval.code) = PREINCREMENT_EXPR; }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 378 "objc-parse.y"
    { (yyval.code) = PREDECREMENT_EXPR; }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 380 "objc-parse.y"
    { (yyval.code) = BIT_NOT_EXPR; }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 382 "objc-parse.y"
    { (yyval.code) = TRUTH_NOT_EXPR; }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 386 "objc-parse.y"
    { (yyval.ttype) = build_compound_expr ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 391 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 397 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ttype)); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 399 "objc-parse.y"
    { chainon ((yyvsp[(1) - (3)].ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (3)].ttype))); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 405 "objc-parse.y"
    { (yyval.ttype) = build_indirect_ref ((yyvsp[(2) - (2)].ttype), "unary *"); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 408 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 411 "objc-parse.y"
    { (yyval.ttype) = build_unary_op ((yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].ttype), 0);
		  overflow_warning ((yyval.ttype)); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 415 "objc-parse.y"
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

  case 54:
/* Line 1792 of yacc.c  */
#line 443 "objc-parse.y"
    { skip_evaluation--;
		  if (TREE_CODE ((yyvsp[(2) - (2)].ttype)) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (TREE_OPERAND ((yyvsp[(2) - (2)].ttype), 1)))
		    error ("`sizeof' applied to a bit-field");
		  (yyval.ttype) = c_sizeof (TREE_TYPE ((yyvsp[(2) - (2)].ttype))); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 449 "objc-parse.y"
    { skip_evaluation--;
		  (yyval.ttype) = c_sizeof (groktypename ((yyvsp[(3) - (4)].ttype))); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 452 "objc-parse.y"
    { skip_evaluation--;
		  (yyval.ttype) = c_alignof_expr ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 455 "objc-parse.y"
    { skip_evaluation--;
		  (yyval.ttype) = c_alignof (groktypename ((yyvsp[(3) - (4)].ttype))); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 458 "objc-parse.y"
    { (yyval.ttype) = build_unary_op (REALPART_EXPR, (yyvsp[(2) - (2)].ttype), 0); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 460 "objc-parse.y"
    { (yyval.ttype) = build_unary_op (IMAGPART_EXPR, (yyvsp[(2) - (2)].ttype), 0); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 464 "objc-parse.y"
    { skip_evaluation++; }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 468 "objc-parse.y"
    { skip_evaluation++; }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 474 "objc-parse.y"
    { tree type = groktypename ((yyvsp[(2) - (4)].ttype));
		  (yyval.ttype) = build_c_cast (type, (yyvsp[(4) - (4)].ttype)); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 477 "objc-parse.y"
    { start_init (NULL_TREE, NULL, 0);
		  (yyvsp[(2) - (4)].ttype) = groktypename ((yyvsp[(2) - (4)].ttype));
		  really_start_incremental_init ((yyvsp[(2) - (4)].ttype)); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 481 "objc-parse.y"
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

  case 67:
/* Line 1792 of yacc.c  */
#line 510 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 512 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 514 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 516 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 518 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 520 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 522 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 524 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 526 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 528 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 530 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 532 "objc-parse.y"
    { (yyval.ttype) = parser_build_binary_op ((yyvsp[(2) - (3)].code), (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 534 "objc-parse.y"
    { (yyvsp[(1) - (2)].ttype) = truthvalue_conversion (default_conversion ((yyvsp[(1) - (2)].ttype)));
		  skip_evaluation += (yyvsp[(1) - (2)].ttype) == boolean_false_node; }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 537 "objc-parse.y"
    { skip_evaluation -= (yyvsp[(1) - (4)].ttype) == boolean_false_node;
		  (yyval.ttype) = parser_build_binary_op (TRUTH_ANDIF_EXPR, (yyvsp[(1) - (4)].ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 540 "objc-parse.y"
    { (yyvsp[(1) - (2)].ttype) = truthvalue_conversion (default_conversion ((yyvsp[(1) - (2)].ttype)));
		  skip_evaluation += (yyvsp[(1) - (2)].ttype) == boolean_true_node; }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 543 "objc-parse.y"
    { skip_evaluation -= (yyvsp[(1) - (4)].ttype) == boolean_true_node;
		  (yyval.ttype) = parser_build_binary_op (TRUTH_ORIF_EXPR, (yyvsp[(1) - (4)].ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 546 "objc-parse.y"
    { (yyvsp[(1) - (2)].ttype) = truthvalue_conversion (default_conversion ((yyvsp[(1) - (2)].ttype)));
		  skip_evaluation += (yyvsp[(1) - (2)].ttype) == boolean_false_node; }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 549 "objc-parse.y"
    { skip_evaluation += (((yyvsp[(1) - (5)].ttype) == boolean_true_node)
				      - ((yyvsp[(1) - (5)].ttype) == boolean_false_node)); }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 552 "objc-parse.y"
    { skip_evaluation -= (yyvsp[(1) - (7)].ttype) == boolean_true_node;
		  (yyval.ttype) = build_conditional_expr ((yyvsp[(1) - (7)].ttype), (yyvsp[(4) - (7)].ttype), (yyvsp[(7) - (7)].ttype)); }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 555 "objc-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids omitting the middle term of a ?: expression");
		  /* Make sure first operand is calculated only once.  */
		  (yyvsp[(2) - (2)].ttype) = save_expr ((yyvsp[(1) - (2)].ttype));
		  (yyvsp[(1) - (2)].ttype) = truthvalue_conversion (default_conversion ((yyvsp[(2) - (2)].ttype)));
		  skip_evaluation += (yyvsp[(1) - (2)].ttype) == boolean_true_node; }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 562 "objc-parse.y"
    { skip_evaluation -= (yyvsp[(1) - (5)].ttype) == boolean_true_node;
		  (yyval.ttype) = build_conditional_expr ((yyvsp[(1) - (5)].ttype), (yyvsp[(2) - (5)].ttype), (yyvsp[(5) - (5)].ttype)); }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 565 "objc-parse.y"
    { char class;
		  (yyval.ttype) = build_modify_expr ((yyvsp[(1) - (3)].ttype), NOP_EXPR, (yyvsp[(3) - (3)].ttype));
		  class = TREE_CODE_CLASS (TREE_CODE ((yyval.ttype)));
		  if (class == 'e' || class == '1'
		      || class == '2' || class == '<')
		    C_SET_EXP_ORIGINAL_CODE ((yyval.ttype), MODIFY_EXPR);
		}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 573 "objc-parse.y"
    { char class;
		  (yyval.ttype) = build_modify_expr ((yyvsp[(1) - (3)].ttype), (yyvsp[(2) - (3)].code), (yyvsp[(3) - (3)].ttype));
		  /* This inhibits warnings in truthvalue_conversion.  */
		  class = TREE_CODE_CLASS (TREE_CODE ((yyval.ttype)));
		  if (class == 'e' || class == '1'
		      || class == '2' || class == '<')
		    C_SET_EXP_ORIGINAL_CODE ((yyval.ttype), ERROR_MARK);
		}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 585 "objc-parse.y"
    {
		  (yyval.ttype) = lastiddecl;
		  if (!(yyval.ttype) || (yyval.ttype) == error_mark_node)
		    {
		      if (yychar == YYEMPTY)
			yychar = YYLEX;
		      if (yychar == '(')
			{
			  tree decl;

			  if (objc_receiver_context
			      && ! (objc_receiver_context
				    && strcmp (IDENTIFIER_POINTER ((yyvsp[(1) - (1)].ttype)), "super")))
			    /* we have a message to super */
			    (yyval.ttype) = get_super_receiver ();
			  else if (objc_method_context
				   && (decl = is_ivar (objc_ivar_chain, (yyvsp[(1) - (1)].ttype))))
			    {
			      if (is_private (decl))
				(yyval.ttype) = error_mark_node;
			      else
				(yyval.ttype) = build_ivar_reference ((yyvsp[(1) - (1)].ttype));
			    }
			  else
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
			  tree decl;

		          if (objc_receiver_context
			      && ! strcmp (IDENTIFIER_POINTER ((yyvsp[(1) - (1)].ttype)), "super"))
			    /* we have a message to super */
			    (yyval.ttype) = get_super_receiver ();
			  else if (objc_method_context
				   && (decl = is_ivar (objc_ivar_chain, (yyvsp[(1) - (1)].ttype))))
			    {
			      if (is_private (decl))
				(yyval.ttype) = error_mark_node;
			      else
				(yyval.ttype) = build_ivar_reference ((yyvsp[(1) - (1)].ttype));
			    }
			  else
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
			  if (objc_method_context
			      && is_ivar (objc_ivar_chain, (yyvsp[(1) - (1)].ttype)))
			    error ("Instance variable `%s' implicitly declared as function",
				   IDENTIFIER_POINTER (DECL_NAME ((yyval.ttype))));
			  else
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
		      /* we have a definition - still check if iVariable */

		      if (!objc_receiver_context
			  || (objc_receiver_context
			      && strcmp (IDENTIFIER_POINTER ((yyvsp[(1) - (1)].ttype)), "super")))
                        {
			  tree decl;

			  if (objc_method_context
			      && (decl = is_ivar (objc_ivar_chain, (yyvsp[(1) - (1)].ttype))))
                            {
                              if (IDENTIFIER_LOCAL_VALUE ((yyvsp[(1) - (1)].ttype)))
                                warning ("local declaration of `%s' hides instance variable",
	                                 IDENTIFIER_POINTER ((yyvsp[(1) - (1)].ttype)));
                              else
 				{
 				  if (is_private (decl))
 				    (yyval.ttype) = error_mark_node;
 				  else
 				    (yyval.ttype) = build_ivar_reference ((yyvsp[(1) - (1)].ttype));
 				}
                            }
			}
                      else /* we have a message to super */
		        (yyval.ttype) = get_super_receiver ();
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

  case 92:
/* Line 1792 of yacc.c  */
#line 745 "objc-parse.y"
    { (yyval.ttype) = combine_strings ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 747 "objc-parse.y"
    { char class = TREE_CODE_CLASS (TREE_CODE ((yyvsp[(2) - (3)].ttype)));
		  if (class == 'e' || class == '1'
		      || class == '2' || class == '<')
		    C_SET_EXP_ORIGINAL_CODE ((yyvsp[(2) - (3)].ttype), ERROR_MARK);
		  (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 753 "objc-parse.y"
    { (yyval.ttype) = error_mark_node; }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 755 "objc-parse.y"
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

  case 96:
/* Line 1792 of yacc.c  */
#line 769 "objc-parse.y"
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

  case 97:
/* Line 1792 of yacc.c  */
#line 792 "objc-parse.y"
    { (yyval.ttype) = build_function_call ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 794 "objc-parse.y"
    { (yyval.ttype) = build_array_ref ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 796 "objc-parse.y"
    {
                  if (doing_objc_thang)
                    {
		      if (is_public ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)))
			(yyval.ttype) = build_component_ref ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		      else
			(yyval.ttype) = error_mark_node;
		    }
                  else
		    (yyval.ttype) = build_component_ref ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 808 "objc-parse.y"
    {
                  tree expr = build_indirect_ref ((yyvsp[(1) - (3)].ttype), "->");

                  if (doing_objc_thang)
                    {
		      if (is_public (expr, (yyvsp[(3) - (3)].ttype)))
			(yyval.ttype) = build_component_ref (expr, (yyvsp[(3) - (3)].ttype));
		      else
			(yyval.ttype) = error_mark_node;
		    }
                  else
                    (yyval.ttype) = build_component_ref (expr, (yyvsp[(3) - (3)].ttype));
		}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 822 "objc-parse.y"
    { (yyval.ttype) = build_unary_op (POSTINCREMENT_EXPR, (yyvsp[(1) - (2)].ttype), 0); }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 824 "objc-parse.y"
    { (yyval.ttype) = build_unary_op (POSTDECREMENT_EXPR, (yyvsp[(1) - (2)].ttype), 0); }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 826 "objc-parse.y"
    { (yyval.ttype) = build_message_expr ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 828 "objc-parse.y"
    { (yyval.ttype) = build_selector_expr ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 830 "objc-parse.y"
    { (yyval.ttype) = build_protocol_expr ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 832 "objc-parse.y"
    { (yyval.ttype) = build_encode_expr ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 834 "objc-parse.y"
    { (yyval.ttype) = build_objc_string_object ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 841 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 849 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 857 "objc-parse.y"
    { c_mark_varargs ();
		  if (pedantic)
		    pedwarn ("ANSI C does not permit use of `varargs.h'"); }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 867 "objc-parse.y"
    { }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 883 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 888 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);	
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 893 "objc-parse.y"
    { shadow_tag_warned ((yyvsp[(1) - (2)].ttype), 1);
		  pedwarn ("empty declaration"); }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 896 "objc-parse.y"
    { pedwarn ("empty declaration"); }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 905 "objc-parse.y"
    { }
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 920 "objc-parse.y"
    { (yyval.itype) = suspend_momentary ();
		  pending_xref_error ();
		  declspec_stack = tree_cons (prefix_attributes,
					      current_declspecs,
					      declspec_stack);
		  split_specs_attrs ((yyvsp[(0) - (0)].ttype),
				     &current_declspecs, &prefix_attributes); }
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 931 "objc-parse.y"
    { prefix_attributes = chainon (prefix_attributes, (yyvsp[(0) - (0)].ttype)); }
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 936 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 941 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 946 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (3)].itype)); }
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 951 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (3)].itype)); }
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 956 "objc-parse.y"
    { shadow_tag ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 958 "objc-parse.y"
    { pedwarn ("empty declaration"); }
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 960 "objc-parse.y"
    { pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 970 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 972 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(3) - (3)].ttype), tree_cons (NULL_TREE, (yyvsp[(2) - (3)].ttype), (yyvsp[(1) - (3)].ttype))); }
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 976 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 978 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 980 "objc-parse.y"
    { if (extra_warnings)
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyvsp[(2) - (2)].ttype)));
		  (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 985 "objc-parse.y"
    { (yyval.ttype) = tree_cons ((yyvsp[(2) - (2)].ttype), NULL_TREE, (yyvsp[(1) - (2)].ttype)); }
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 990 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 992 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(3) - (3)].ttype), tree_cons (NULL_TREE, (yyvsp[(2) - (3)].ttype), (yyvsp[(1) - (3)].ttype))); }
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 997 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 999 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1001 "objc-parse.y"
    { if (extra_warnings)
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyvsp[(2) - (2)].ttype)));
		  (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1014 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1016 "objc-parse.y"
    { (yyval.ttype) = tree_cons ((yyvsp[(1) - (1)].ttype), NULL_TREE, NULL_TREE); }
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1018 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1020 "objc-parse.y"
    { (yyval.ttype) = tree_cons ((yyvsp[(2) - (2)].ttype), NULL_TREE, (yyvsp[(1) - (2)].ttype)); }
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1025 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (1)].ttype), NULL_TREE);
		  TREE_STATIC ((yyval.ttype)) = 1; }
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1028 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (1)].ttype), NULL_TREE); }
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1030 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype));
		  TREE_STATIC ((yyval.ttype)) = 1; }
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1033 "objc-parse.y"
    { if (extra_warnings && TREE_STATIC ((yyvsp[(1) - (2)].ttype)))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyvsp[(2) - (2)].ttype)));
		  (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype));
		  TREE_STATIC ((yyval.ttype)) = TREE_STATIC ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1047 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1049 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(3) - (3)].ttype), tree_cons (NULL_TREE, (yyvsp[(2) - (3)].ttype), (yyvsp[(1) - (3)].ttype))); }
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1053 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1055 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1065 "objc-parse.y"
    { /* For a typedef name, record the meaning, not the name.
		     In case of `foo foo, bar;'.  */
		  (yyval.ttype) = lookup_name ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1069 "objc-parse.y"
    { (yyval.ttype) = get_static_reference ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1071 "objc-parse.y"
    { (yyval.ttype) = get_object_reference ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1076 "objc-parse.y"
    { (yyval.ttype) = get_object_reference ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1078 "objc-parse.y"
    { (yyval.ttype) = TREE_TYPE ((yyvsp[(3) - (4)].ttype)); }
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1080 "objc-parse.y"
    { (yyval.ttype) = groktypename ((yyvsp[(3) - (4)].ttype)); }
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1102 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1104 "objc-parse.y"
    { if (TREE_CHAIN ((yyvsp[(3) - (4)].ttype))) (yyvsp[(3) - (4)].ttype) = combine_strings ((yyvsp[(3) - (4)].ttype));
		  (yyval.ttype) = (yyvsp[(3) - (4)].ttype);
		}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1111 "objc-parse.y"
    { (yyval.ttype) = start_decl ((yyvsp[(1) - (4)].ttype), current_declspecs, 1,
					  (yyvsp[(3) - (4)].ttype), prefix_attributes);
		  start_init ((yyval.ttype), (yyvsp[(2) - (4)].ttype), global_bindings_p ()); }
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1116 "objc-parse.y"
    { finish_init ();
		  finish_decl ((yyvsp[(5) - (6)].ttype), (yyvsp[(6) - (6)].ttype), (yyvsp[(2) - (6)].ttype)); }
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1119 "objc-parse.y"
    { tree d = start_decl ((yyvsp[(1) - (3)].ttype), current_declspecs, 0,
				       (yyvsp[(3) - (3)].ttype), prefix_attributes);
		  finish_decl (d, NULL_TREE, (yyvsp[(2) - (3)].ttype)); 
                }
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1127 "objc-parse.y"
    { (yyval.ttype) = start_decl ((yyvsp[(1) - (4)].ttype), current_declspecs, 1,
					  (yyvsp[(3) - (4)].ttype), prefix_attributes);
		  start_init ((yyval.ttype), (yyvsp[(2) - (4)].ttype), global_bindings_p ()); }
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1132 "objc-parse.y"
    { finish_init ();
		  decl_attributes ((yyvsp[(5) - (6)].ttype), (yyvsp[(3) - (6)].ttype), prefix_attributes);
		  finish_decl ((yyvsp[(5) - (6)].ttype), (yyvsp[(6) - (6)].ttype), (yyvsp[(2) - (6)].ttype)); }
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1136 "objc-parse.y"
    { tree d = start_decl ((yyvsp[(1) - (3)].ttype), current_declspecs, 0,
				       (yyvsp[(3) - (3)].ttype), prefix_attributes);
		  finish_decl (d, NULL_TREE, (yyvsp[(2) - (3)].ttype)); }
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1144 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1146 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1151 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1153 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1158 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(4) - (6)].ttype); }
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1163 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1165 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1170 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1172 "objc-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (1)].ttype), NULL_TREE); }
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1174 "objc-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (4)].ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (4)].ttype))); }
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1176 "objc-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (6)].ttype), tree_cons (NULL_TREE, (yyvsp[(3) - (6)].ttype), (yyvsp[(5) - (6)].ttype))); }
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1178 "objc-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1196 "objc-parse.y"
    { really_start_incremental_init (NULL_TREE);
		  /* Note that the call to clear_momentary
		     is in process_init_element.  */
		  push_momentary (); }
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1201 "objc-parse.y"
    { (yyval.ttype) = pop_init_level (0);
		  if ((yyval.ttype) == error_mark_node
		      && ! (yychar == STRING || yychar == CONSTANT))
		    pop_momentary ();
		  else
		    pop_momentary_nofree (); }
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1209 "objc-parse.y"
    { (yyval.ttype) = error_mark_node; }
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1215 "objc-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids empty initializer braces"); }
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1231 "objc-parse.y"
    { set_init_label ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1238 "objc-parse.y"
    { push_init_level (0); }
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1240 "objc-parse.y"
    { process_init_element (pop_init_level (0)); }
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1242 "objc-parse.y"
    { process_init_element ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1253 "objc-parse.y"
    { set_init_label ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1261 "objc-parse.y"
    { push_c_function_context ();
		  if (! start_function (current_declspecs, (yyvsp[(1) - (1)].ttype),
					prefix_attributes, NULL_TREE, 1))
		    {
		      pop_c_function_context ();
		      YYERROR1;
		    }
		  reinit_parse_for_function (); }
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1270 "objc-parse.y"
    { store_parm_decls (); }
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1278 "objc-parse.y"
    { finish_function (1);
		  pop_c_function_context (); }
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1284 "objc-parse.y"
    { push_c_function_context ();
		  if (! start_function (current_declspecs, (yyvsp[(1) - (1)].ttype),
					prefix_attributes, NULL_TREE, 1))
		    {
		      pop_c_function_context ();
		      YYERROR1;
		    }
		  reinit_parse_for_function (); }
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1293 "objc-parse.y"
    { store_parm_decls (); }
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1301 "objc-parse.y"
    { finish_function (1);
		  pop_c_function_context (); }
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1317 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1319 "objc-parse.y"
    { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype), NULL_TREE); }
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 1324 "objc-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1326 "objc-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (3)].ttype), NULL_TREE); }
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1328 "objc-parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1335 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1347 "objc-parse.y"
    { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype), NULL_TREE); }
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1352 "objc-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 1354 "objc-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (3)].ttype), NULL_TREE); }
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 1356 "objc-parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 1363 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 1372 "objc-parse.y"
    { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype), NULL_TREE); }
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 1377 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1379 "objc-parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1381 "objc-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 1383 "objc-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (3)].ttype), NULL_TREE); }
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 1390 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 1396 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 1398 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 1403 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 1405 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 1410 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 1412 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 255:
/* Line 1792 of yacc.c  */
#line 1417 "objc-parse.y"
    { (yyval.ttype) = start_struct (RECORD_TYPE, (yyvsp[(2) - (3)].ttype));
		  /* Start scope of tag before parsing components.  */
		}
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 1421 "objc-parse.y"
    { (yyval.ttype) = finish_struct ((yyvsp[(4) - (7)].ttype), (yyvsp[(5) - (7)].ttype), chainon ((yyvsp[(1) - (7)].ttype), (yyvsp[(7) - (7)].ttype))); }
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 1423 "objc-parse.y"
    { (yyval.ttype) = finish_struct (start_struct (RECORD_TYPE, NULL_TREE),
				      (yyvsp[(3) - (5)].ttype), chainon ((yyvsp[(1) - (5)].ttype), (yyvsp[(5) - (5)].ttype)));
		}
    break;

  case 258:
/* Line 1792 of yacc.c  */
#line 1427 "objc-parse.y"
    { (yyval.ttype) = xref_tag (RECORD_TYPE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 1429 "objc-parse.y"
    { (yyval.ttype) = start_struct (UNION_TYPE, (yyvsp[(2) - (3)].ttype)); }
    break;

  case 260:
/* Line 1792 of yacc.c  */
#line 1431 "objc-parse.y"
    { (yyval.ttype) = finish_struct ((yyvsp[(4) - (7)].ttype), (yyvsp[(5) - (7)].ttype), chainon ((yyvsp[(1) - (7)].ttype), (yyvsp[(7) - (7)].ttype))); }
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 1433 "objc-parse.y"
    { (yyval.ttype) = finish_struct (start_struct (UNION_TYPE, NULL_TREE),
				      (yyvsp[(3) - (5)].ttype), chainon ((yyvsp[(1) - (5)].ttype), (yyvsp[(5) - (5)].ttype)));
		}
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 1437 "objc-parse.y"
    { (yyval.ttype) = xref_tag (UNION_TYPE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 1439 "objc-parse.y"
    { (yyvsp[(3) - (3)].itype) = suspend_momentary ();
		  (yyval.ttype) = start_enum ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 1442 "objc-parse.y"
    { (yyval.ttype)= finish_enum ((yyvsp[(4) - (8)].ttype), nreverse ((yyvsp[(5) - (8)].ttype)), chainon ((yyvsp[(1) - (8)].ttype), (yyvsp[(8) - (8)].ttype)));
		  resume_momentary ((yyvsp[(3) - (8)].itype)); }
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 1445 "objc-parse.y"
    { (yyvsp[(2) - (2)].itype) = suspend_momentary ();
		  (yyval.ttype) = start_enum (NULL_TREE); }
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 1448 "objc-parse.y"
    { (yyval.ttype)= finish_enum ((yyvsp[(3) - (7)].ttype), nreverse ((yyvsp[(4) - (7)].ttype)), chainon ((yyvsp[(1) - (7)].ttype), (yyvsp[(7) - (7)].ttype)));
		  resume_momentary ((yyvsp[(2) - (7)].itype)); }
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 1451 "objc-parse.y"
    { (yyval.ttype) = xref_tag (ENUMERAL_TYPE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 1462 "objc-parse.y"
    { if (pedantic && ! flag_isoc9x)
		    pedwarn ("comma at end of enumerator list"); }
    break;

  case 272:
/* Line 1792 of yacc.c  */
#line 1468 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 273:
/* Line 1792 of yacc.c  */
#line 1470 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype));
		  pedwarn ("no semicolon at end of struct or union"); }
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 1475 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 1477 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), (yyvsp[(2) - (3)].ttype)); }
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 1479 "objc-parse.y"
    { if (pedantic)
		    pedwarn ("extra semicolon in struct or union specified"); }
    break;

  case 277:
/* Line 1792 of yacc.c  */
#line 1483 "objc-parse.y"
    {
		  tree interface = lookup_interface ((yyvsp[(3) - (4)].ttype));

		  if (interface)
		    (yyval.ttype) = get_class_ivars (interface);
		  else
		    {
		      error ("Cannot find interface declaration for `%s'",
			     IDENTIFIER_POINTER ((yyvsp[(3) - (4)].ttype)));
		      (yyval.ttype) = NULL_TREE;
		    }
		}
    break;

  case 278:
/* Line 1792 of yacc.c  */
#line 1508 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype);
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (3)].itype)); }
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 1514 "objc-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids member declarations with no members");
		  shadow_tag((yyvsp[(1) - (1)].ttype));
		  (yyval.ttype) = NULL_TREE; }
    break;

  case 280:
/* Line 1792 of yacc.c  */
#line 1519 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype);
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (3)].itype)); }
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 1525 "objc-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids member declarations with no members");
		  shadow_tag((yyvsp[(1) - (1)].ttype));
		  (yyval.ttype) = NULL_TREE; }
    break;

  case 282:
/* Line 1792 of yacc.c  */
#line 1530 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 283:
/* Line 1792 of yacc.c  */
#line 1532 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 285:
/* Line 1792 of yacc.c  */
#line 1539 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 286:
/* Line 1792 of yacc.c  */
#line 1544 "objc-parse.y"
    { (yyval.ttype) = grokfield ((yyvsp[(1) - (4)].filename), (yyvsp[(2) - (4)].lineno), (yyvsp[(3) - (4)].ttype), current_declspecs, NULL_TREE);
		  decl_attributes ((yyval.ttype), (yyvsp[(4) - (4)].ttype), prefix_attributes); }
    break;

  case 287:
/* Line 1792 of yacc.c  */
#line 1548 "objc-parse.y"
    { (yyval.ttype) = grokfield ((yyvsp[(1) - (6)].filename), (yyvsp[(2) - (6)].lineno), (yyvsp[(3) - (6)].ttype), current_declspecs, (yyvsp[(5) - (6)].ttype));
		  decl_attributes ((yyval.ttype), (yyvsp[(6) - (6)].ttype), prefix_attributes); }
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 1551 "objc-parse.y"
    { (yyval.ttype) = grokfield ((yyvsp[(1) - (5)].filename), (yyvsp[(2) - (5)].lineno), NULL_TREE, current_declspecs, (yyvsp[(4) - (5)].ttype));
		  decl_attributes ((yyval.ttype), (yyvsp[(5) - (5)].ttype), prefix_attributes); }
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 1563 "objc-parse.y"
    { if ((yyvsp[(1) - (3)].ttype) == error_mark_node)
		    (yyval.ttype) = (yyvsp[(1) - (3)].ttype);
		  else
		    (yyval.ttype) = chainon ((yyvsp[(3) - (3)].ttype), (yyvsp[(1) - (3)].ttype)); }
    break;

  case 291:
/* Line 1792 of yacc.c  */
#line 1568 "objc-parse.y"
    { (yyval.ttype) = error_mark_node; }
    break;

  case 292:
/* Line 1792 of yacc.c  */
#line 1574 "objc-parse.y"
    { (yyval.ttype) = build_enumerator ((yyvsp[(1) - (1)].ttype), NULL_TREE); }
    break;

  case 293:
/* Line 1792 of yacc.c  */
#line 1576 "objc-parse.y"
    { (yyval.ttype) = build_enumerator ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 294:
/* Line 1792 of yacc.c  */
#line 1581 "objc-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 295:
/* Line 1792 of yacc.c  */
#line 1583 "objc-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 296:
/* Line 1792 of yacc.c  */
#line 1588 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 298:
/* Line 1792 of yacc.c  */
#line 1594 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(1) - (1)].ttype), NULL_TREE); }
    break;

  case 299:
/* Line 1792 of yacc.c  */
#line 1596 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 300:
/* Line 1792 of yacc.c  */
#line 1601 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 301:
/* Line 1792 of yacc.c  */
#line 1603 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 302:
/* Line 1792 of yacc.c  */
#line 1608 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 303:
/* Line 1792 of yacc.c  */
#line 1611 "objc-parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 304:
/* Line 1792 of yacc.c  */
#line 1613 "objc-parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (2)].ttype), NULL_TREE); }
    break;

  case 305:
/* Line 1792 of yacc.c  */
#line 1615 "objc-parse.y"
    { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype), NULL_TREE); }
    break;

  case 306:
/* Line 1792 of yacc.c  */
#line 1617 "objc-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 307:
/* Line 1792 of yacc.c  */
#line 1619 "objc-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[(1) - (3)].ttype), NULL_TREE); }
    break;

  case 308:
/* Line 1792 of yacc.c  */
#line 1621 "objc-parse.y"
    { (yyval.ttype) = build_nt (CALL_EXPR, NULL_TREE, (yyvsp[(2) - (2)].ttype), NULL_TREE); }
    break;

  case 309:
/* Line 1792 of yacc.c  */
#line 1623 "objc-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, NULL_TREE, (yyvsp[(2) - (3)].ttype)); }
    break;

  case 310:
/* Line 1792 of yacc.c  */
#line 1625 "objc-parse.y"
    { (yyval.ttype) = build_nt (ARRAY_REF, NULL_TREE, NULL_TREE); }
    break;

  case 311:
/* Line 1792 of yacc.c  */
#line 1629 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 1638 "objc-parse.y"
    {
		  if (pedantic && (yyvsp[(1) - (1)].ends_in_label))
		    pedwarn ("ANSI C forbids label at end of compound statement");
		}
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 1647 "objc-parse.y"
    { (yyval.ends_in_label) = (yyvsp[(2) - (2)].ends_in_label); }
    break;

  case 315:
/* Line 1792 of yacc.c  */
#line 1649 "objc-parse.y"
    { (yyval.ends_in_label) = 0; }
    break;

  case 319:
/* Line 1792 of yacc.c  */
#line 1661 "objc-parse.y"
    { emit_line_note (input_filename, lineno);
		  pushlevel (0);
		  clear_last_expr ();
		  push_momentary ();
		  expand_start_bindings (0);
		  if (objc_method_context)
		    add_objc_decls ();
		}
    break;

  case 321:
/* Line 1792 of yacc.c  */
#line 1676 "objc-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids label declarations"); }
    break;

  case 324:
/* Line 1792 of yacc.c  */
#line 1687 "objc-parse.y"
    { tree link;
		  for (link = (yyvsp[(2) - (3)].ttype); link; link = TREE_CHAIN (link))
		    {
		      tree label = shadow_label (TREE_VALUE (link));
		      C_DECLARED_LABEL_FLAG (label) = 1;
		      declare_nonlocal_label (label);
		    }
		}
    break;

  case 325:
/* Line 1792 of yacc.c  */
#line 1701 "objc-parse.y"
    {}
    break;

  case 327:
/* Line 1792 of yacc.c  */
#line 1705 "objc-parse.y"
    { compstmt_count++; }
    break;

  case 328:
/* Line 1792 of yacc.c  */
#line 1708 "objc-parse.y"
    { (yyval.ttype) = convert (void_type_node, integer_zero_node); }
    break;

  case 329:
/* Line 1792 of yacc.c  */
#line 1710 "objc-parse.y"
    { emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), 1, 0);
		  (yyval.ttype) = poplevel (1, 1, 0);
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
    break;

  case 330:
/* Line 1792 of yacc.c  */
#line 1718 "objc-parse.y"
    { emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), kept_level_p (), 0);
		  (yyval.ttype) = poplevel (kept_level_p (), 0, 0);
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
    break;

  case 331:
/* Line 1792 of yacc.c  */
#line 1726 "objc-parse.y"
    { emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), kept_level_p (), 0);
		  (yyval.ttype) = poplevel (kept_level_p (), 0, 0);
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
    break;

  case 334:
/* Line 1792 of yacc.c  */
#line 1746 "objc-parse.y"
    { emit_line_note ((yyvsp[(-1) - (4)].filename), (yyvsp[(0) - (4)].lineno));
		  c_expand_start_cond (truthvalue_conversion ((yyvsp[(3) - (4)].ttype)), 0, 
				       compstmt_count);
		  (yyval.itype) = stmt_count;
		  if_stmt_file = (yyvsp[(-1) - (4)].filename);
		  if_stmt_line = (yyvsp[(0) - (4)].lineno);
		  position_after_white_space (); }
    break;

  case 335:
/* Line 1792 of yacc.c  */
#line 1760 "objc-parse.y"
    { stmt_count++;
		  compstmt_count++;
		  emit_line_note ((yyvsp[(-1) - (1)].filename), (yyvsp[(0) - (1)].lineno));
		  /* See comment in `while' alternative, above.  */
		  emit_nop ();
		  expand_start_loop_continue_elsewhere (1);
		  position_after_white_space (); }
    break;

  case 336:
/* Line 1792 of yacc.c  */
#line 1768 "objc-parse.y"
    { expand_loop_continue_here (); }
    break;

  case 337:
/* Line 1792 of yacc.c  */
#line 1772 "objc-parse.y"
    { (yyval.filename) = input_filename; }
    break;

  case 338:
/* Line 1792 of yacc.c  */
#line 1776 "objc-parse.y"
    { (yyval.lineno) = lineno; }
    break;

  case 339:
/* Line 1792 of yacc.c  */
#line 1781 "objc-parse.y"
    { }
    break;

  case 340:
/* Line 1792 of yacc.c  */
#line 1786 "objc-parse.y"
    { }
    break;

  case 341:
/* Line 1792 of yacc.c  */
#line 1791 "objc-parse.y"
    { (yyval.ends_in_label) = (yyvsp[(3) - (3)].ends_in_label); }
    break;

  case 342:
/* Line 1792 of yacc.c  */
#line 1796 "objc-parse.y"
    { (yyval.ends_in_label) = 0; }
    break;

  case 343:
/* Line 1792 of yacc.c  */
#line 1798 "objc-parse.y"
    { (yyval.ends_in_label) = 1; }
    break;

  case 344:
/* Line 1792 of yacc.c  */
#line 1804 "objc-parse.y"
    { stmt_count++; }
    break;

  case 346:
/* Line 1792 of yacc.c  */
#line 1807 "objc-parse.y"
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

  case 347:
/* Line 1792 of yacc.c  */
#line 1824 "objc-parse.y"
    { c_expand_start_else ();
		  (yyvsp[(1) - (2)].itype) = stmt_count;
		  position_after_white_space (); }
    break;

  case 348:
/* Line 1792 of yacc.c  */
#line 1828 "objc-parse.y"
    { c_expand_end_cond ();
		  if (extra_warnings && stmt_count == (yyvsp[(1) - (4)].itype))
		    warning ("empty body in an else-statement"); }
    break;

  case 349:
/* Line 1792 of yacc.c  */
#line 1832 "objc-parse.y"
    { c_expand_end_cond ();
		  /* This warning is here instead of in simple_if, because we
		     do not want a warning if an empty if is followed by an
		     else statement.  Increment stmt_count so we don't
		     give a second error if this is a nested `if'.  */
		  if (extra_warnings && stmt_count++ == (yyvsp[(1) - (1)].itype))
		    warning_with_file_and_line (if_stmt_file, if_stmt_line,
						"empty body in an if-statement"); }
    break;

  case 350:
/* Line 1792 of yacc.c  */
#line 1844 "objc-parse.y"
    { c_expand_end_cond (); }
    break;

  case 351:
/* Line 1792 of yacc.c  */
#line 1846 "objc-parse.y"
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

  case 352:
/* Line 1792 of yacc.c  */
#line 1856 "objc-parse.y"
    { /* Don't start the loop till we have succeeded
		     in parsing the end test.  This is to make sure
		     that we end every loop we start.  */
		  expand_start_loop (1);
		  emit_line_note (input_filename, lineno);
		  expand_exit_loop_if_false (NULL_PTR,
					     truthvalue_conversion ((yyvsp[(4) - (5)].ttype)));
		  position_after_white_space (); }
    break;

  case 353:
/* Line 1792 of yacc.c  */
#line 1865 "objc-parse.y"
    { expand_end_loop (); }
    break;

  case 354:
/* Line 1792 of yacc.c  */
#line 1868 "objc-parse.y"
    { emit_line_note (input_filename, lineno);
		  expand_exit_loop_if_false (NULL_PTR,
					     truthvalue_conversion ((yyvsp[(3) - (5)].ttype)));
		  expand_end_loop ();
		  clear_momentary (); }
    break;

  case 355:
/* Line 1792 of yacc.c  */
#line 1875 "objc-parse.y"
    { expand_end_loop ();
		  clear_momentary (); }
    break;

  case 356:
/* Line 1792 of yacc.c  */
#line 1879 "objc-parse.y"
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

  case 357:
/* Line 1792 of yacc.c  */
#line 1891 "objc-parse.y"
    { (yyvsp[(7) - (7)].lineno) = lineno;
		  (yyval.filename) = input_filename; }
    break;

  case 358:
/* Line 1792 of yacc.c  */
#line 1894 "objc-parse.y"
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

  case 359:
/* Line 1792 of yacc.c  */
#line 1910 "objc-parse.y"
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

  case 360:
/* Line 1792 of yacc.c  */
#line 1921 "objc-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (4)].filename), (yyvsp[(0) - (4)].lineno));
		  c_expand_start_case ((yyvsp[(3) - (4)].ttype));
		  /* Don't let the tree nodes for $3 be discarded by
		     clear_momentary during the parsing of the next stmt.  */
		  push_momentary ();
		  position_after_white_space (); }
    break;

  case 361:
/* Line 1792 of yacc.c  */
#line 1929 "objc-parse.y"
    { expand_end_case ((yyvsp[(3) - (6)].ttype));
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
    break;

  case 362:
/* Line 1792 of yacc.c  */
#line 1935 "objc-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (2)].filename), (yyvsp[(0) - (2)].lineno));
		  if ( ! expand_exit_something ())
		    error ("break statement not within loop or switch"); }
    break;

  case 363:
/* Line 1792 of yacc.c  */
#line 1940 "objc-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (2)].filename), (yyvsp[(0) - (2)].lineno));
		  if (! expand_continue_loop (NULL_PTR))
		    error ("continue statement not within a loop"); }
    break;

  case 364:
/* Line 1792 of yacc.c  */
#line 1945 "objc-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (2)].filename), (yyvsp[(0) - (2)].lineno));
		  c_expand_return (NULL_TREE); }
    break;

  case 365:
/* Line 1792 of yacc.c  */
#line 1949 "objc-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (3)].filename), (yyvsp[(0) - (3)].lineno));
		  c_expand_return ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 366:
/* Line 1792 of yacc.c  */
#line 1953 "objc-parse.y"
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

  case 367:
/* Line 1792 of yacc.c  */
#line 1964 "objc-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (8)].filename), (yyvsp[(0) - (8)].lineno));
		  c_expand_asm_operands ((yyvsp[(4) - (8)].ttype), (yyvsp[(6) - (8)].ttype), NULL_TREE, NULL_TREE,
					 (yyvsp[(2) - (8)].ttype) == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
    break;

  case 368:
/* Line 1792 of yacc.c  */
#line 1971 "objc-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (10)].filename), (yyvsp[(0) - (10)].lineno));
		  c_expand_asm_operands ((yyvsp[(4) - (10)].ttype), (yyvsp[(6) - (10)].ttype), (yyvsp[(8) - (10)].ttype), NULL_TREE,
					 (yyvsp[(2) - (10)].ttype) == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
    break;

  case 369:
/* Line 1792 of yacc.c  */
#line 1979 "objc-parse.y"
    { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (12)].filename), (yyvsp[(0) - (12)].lineno));
		  c_expand_asm_operands ((yyvsp[(4) - (12)].ttype), (yyvsp[(6) - (12)].ttype), (yyvsp[(8) - (12)].ttype), (yyvsp[(10) - (12)].ttype),
					 (yyvsp[(2) - (12)].ttype) == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
    break;

  case 370:
/* Line 1792 of yacc.c  */
#line 1985 "objc-parse.y"
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

  case 371:
/* Line 1792 of yacc.c  */
#line 1996 "objc-parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C forbids `goto *expr;'");
		  stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (4)].filename), (yyvsp[(0) - (4)].lineno));
		  expand_computed_goto (convert (ptr_type_node, (yyvsp[(3) - (4)].ttype))); }
    break;

  case 374:
/* Line 1792 of yacc.c  */
#line 2011 "objc-parse.y"
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

  case 375:
/* Line 1792 of yacc.c  */
#line 2032 "objc-parse.y"
    {
	    if ((yyvsp[(5) - (6)].itype))
	      iterator_for_loop_end ((yyvsp[(3) - (6)].ttype));
	  }
    break;

  case 376:
/* Line 1792 of yacc.c  */
#line 2067 "objc-parse.y"
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

  case 377:
/* Line 1792 of yacc.c  */
#line 2098 "objc-parse.y"
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

  case 378:
/* Line 1792 of yacc.c  */
#line 2129 "objc-parse.y"
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

  case 379:
/* Line 1792 of yacc.c  */
#line 2144 "objc-parse.y"
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

  case 380:
/* Line 1792 of yacc.c  */
#line 2159 "objc-parse.y"
    { emit_line_note (input_filename, lineno);
		  (yyval.ttype) = NULL_TREE; }
    break;

  case 381:
/* Line 1792 of yacc.c  */
#line 2162 "objc-parse.y"
    { emit_line_note (input_filename, lineno); }
    break;

  case 382:
/* Line 1792 of yacc.c  */
#line 2167 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 384:
/* Line 1792 of yacc.c  */
#line 2174 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 387:
/* Line 1792 of yacc.c  */
#line 2181 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 388:
/* Line 1792 of yacc.c  */
#line 2186 "objc-parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 389:
/* Line 1792 of yacc.c  */
#line 2191 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, combine_strings ((yyvsp[(1) - (1)].ttype)), NULL_TREE); }
    break;

  case 390:
/* Line 1792 of yacc.c  */
#line 2193 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, combine_strings ((yyvsp[(3) - (3)].ttype)), (yyvsp[(1) - (3)].ttype)); }
    break;

  case 391:
/* Line 1792 of yacc.c  */
#line 2199 "objc-parse.y"
    { pushlevel (0);
		  clear_parm_order ();
		  declare_parm_level (0); }
    break;

  case 392:
/* Line 1792 of yacc.c  */
#line 2203 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  parmlist_tags_warning ();
		  poplevel (0, 0, 0); }
    break;

  case 394:
/* Line 1792 of yacc.c  */
#line 2211 "objc-parse.y"
    { tree parm;
		  if (pedantic)
		    pedwarn ("ANSI C forbids forward parameter declarations");
		  /* Mark the forward decls as such.  */
		  for (parm = getdecls (); parm; parm = TREE_CHAIN (parm))
		    TREE_ASM_WRITTEN (parm) = 1;
		  clear_parm_order (); }
    break;

  case 395:
/* Line 1792 of yacc.c  */
#line 2219 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(4) - (4)].ttype); }
    break;

  case 396:
/* Line 1792 of yacc.c  */
#line 2221 "objc-parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, NULL_TREE, NULL_TREE); }
    break;

  case 397:
/* Line 1792 of yacc.c  */
#line 2227 "objc-parse.y"
    { (yyval.ttype) = get_parm_info (0); }
    break;

  case 398:
/* Line 1792 of yacc.c  */
#line 2229 "objc-parse.y"
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

  case 399:
/* Line 1792 of yacc.c  */
#line 2239 "objc-parse.y"
    { (yyval.ttype) = get_parm_info (1); }
    break;

  case 400:
/* Line 1792 of yacc.c  */
#line 2241 "objc-parse.y"
    { (yyval.ttype) = get_parm_info (0); }
    break;

  case 401:
/* Line 1792 of yacc.c  */
#line 2246 "objc-parse.y"
    { push_parm_decl ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 402:
/* Line 1792 of yacc.c  */
#line 2248 "objc-parse.y"
    { push_parm_decl ((yyvsp[(3) - (3)].ttype)); }
    break;

  case 403:
/* Line 1792 of yacc.c  */
#line 2255 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(3) - (4)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(4) - (4)].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 404:
/* Line 1792 of yacc.c  */
#line 2264 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(3) - (4)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(4) - (4)].ttype))); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 405:
/* Line 1792 of yacc.c  */
#line 2273 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(3) - (4)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(4) - (4)].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 406:
/* Line 1792 of yacc.c  */
#line 2282 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(3) - (4)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(4) - (4)].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype));  }
    break;

  case 407:
/* Line 1792 of yacc.c  */
#line 2292 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(3) - (4)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(4) - (4)].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype));  }
    break;

  case 408:
/* Line 1792 of yacc.c  */
#line 2306 "objc-parse.y"
    { pushlevel (0);
		  clear_parm_order ();
		  declare_parm_level (1); }
    break;

  case 409:
/* Line 1792 of yacc.c  */
#line 2310 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  parmlist_tags_warning ();
		  poplevel (0, 0, 0); }
    break;

  case 411:
/* Line 1792 of yacc.c  */
#line 2318 "objc-parse.y"
    { tree t;
		  for (t = (yyvsp[(1) - (2)].ttype); t; t = TREE_CHAIN (t))
		    if (TREE_VALUE (t) == NULL_TREE)
		      error ("`...' in old-style identifier list");
		  (yyval.ttype) = tree_cons (NULL_TREE, NULL_TREE, (yyvsp[(1) - (2)].ttype)); }
    break;

  case 412:
/* Line 1792 of yacc.c  */
#line 2328 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ttype)); }
    break;

  case 413:
/* Line 1792 of yacc.c  */
#line 2330 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (3)].ttype))); }
    break;

  case 414:
/* Line 1792 of yacc.c  */
#line 2336 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ttype)); }
    break;

  case 415:
/* Line 1792 of yacc.c  */
#line 2338 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (3)].ttype))); }
    break;

  case 416:
/* Line 1792 of yacc.c  */
#line 2343 "objc-parse.y"
    { (yyval.itype) = pedantic;
		  pedantic = 0; }
    break;

  case 422:
/* Line 1792 of yacc.c  */
#line 2356 "objc-parse.y"
    {
		  if (objc_implementation_context)
                    {
		      finish_class (objc_implementation_context);
		      objc_ivar_chain = NULL_TREE;
		      objc_implementation_context = NULL_TREE;
		    }
		  else
		    warning ("`@end' must appear in an implementation context");
		}
    break;

  case 423:
/* Line 1792 of yacc.c  */
#line 2371 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ttype)); }
    break;

  case 424:
/* Line 1792 of yacc.c  */
#line 2373 "objc-parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (3)].ttype))); }
    break;

  case 425:
/* Line 1792 of yacc.c  */
#line 2378 "objc-parse.y"
    {
		  objc_declare_class ((yyvsp[(2) - (3)].ttype));
		}
    break;

  case 426:
/* Line 1792 of yacc.c  */
#line 2384 "objc-parse.y"
    {
		  objc_declare_alias ((yyvsp[(2) - (4)].ttype), (yyvsp[(3) - (4)].ttype));
		}
    break;

  case 427:
/* Line 1792 of yacc.c  */
#line 2390 "objc-parse.y"
    {
		  objc_interface_context = objc_ivar_context
		    = start_class (CLASS_INTERFACE_TYPE, (yyvsp[(2) - (4)].ttype), NULL_TREE, (yyvsp[(3) - (4)].ttype));
                  objc_public_flag = 0;
		}
    break;

  case 428:
/* Line 1792 of yacc.c  */
#line 2396 "objc-parse.y"
    {
                  continue_class (objc_interface_context);
		}
    break;

  case 429:
/* Line 1792 of yacc.c  */
#line 2401 "objc-parse.y"
    {
		  finish_class (objc_interface_context);
		  objc_interface_context = NULL_TREE;
		}
    break;

  case 430:
/* Line 1792 of yacc.c  */
#line 2407 "objc-parse.y"
    {
		  objc_interface_context
		    = start_class (CLASS_INTERFACE_TYPE, (yyvsp[(2) - (3)].ttype), NULL_TREE, (yyvsp[(3) - (3)].ttype));
                  continue_class (objc_interface_context);
		}
    break;

  case 431:
/* Line 1792 of yacc.c  */
#line 2414 "objc-parse.y"
    {
		  finish_class (objc_interface_context);
		  objc_interface_context = NULL_TREE;
		}
    break;

  case 432:
/* Line 1792 of yacc.c  */
#line 2420 "objc-parse.y"
    {
		  objc_interface_context = objc_ivar_context
		    = start_class (CLASS_INTERFACE_TYPE, (yyvsp[(2) - (6)].ttype), (yyvsp[(4) - (6)].ttype), (yyvsp[(5) - (6)].ttype));
                  objc_public_flag = 0;
		}
    break;

  case 433:
/* Line 1792 of yacc.c  */
#line 2426 "objc-parse.y"
    {
                  continue_class (objc_interface_context);
		}
    break;

  case 434:
/* Line 1792 of yacc.c  */
#line 2431 "objc-parse.y"
    {
		  finish_class (objc_interface_context);
		  objc_interface_context = NULL_TREE;
		}
    break;

  case 435:
/* Line 1792 of yacc.c  */
#line 2437 "objc-parse.y"
    {
		  objc_interface_context
		    = start_class (CLASS_INTERFACE_TYPE, (yyvsp[(2) - (5)].ttype), (yyvsp[(4) - (5)].ttype), (yyvsp[(5) - (5)].ttype));
                  continue_class (objc_interface_context);
		}
    break;

  case 436:
/* Line 1792 of yacc.c  */
#line 2444 "objc-parse.y"
    {
		  finish_class (objc_interface_context);
		  objc_interface_context = NULL_TREE;
		}
    break;

  case 437:
/* Line 1792 of yacc.c  */
#line 2450 "objc-parse.y"
    {
		  objc_implementation_context = objc_ivar_context
		    = start_class (CLASS_IMPLEMENTATION_TYPE, (yyvsp[(2) - (3)].ttype), NULL_TREE, NULL_TREE);
                  objc_public_flag = 0;
		}
    break;

  case 438:
/* Line 1792 of yacc.c  */
#line 2456 "objc-parse.y"
    {
                  objc_ivar_chain
		    = continue_class (objc_implementation_context);
		}
    break;

  case 439:
/* Line 1792 of yacc.c  */
#line 2462 "objc-parse.y"
    {
		  objc_implementation_context
		    = start_class (CLASS_IMPLEMENTATION_TYPE, (yyvsp[(2) - (2)].ttype), NULL_TREE, NULL_TREE);
                  objc_ivar_chain
		    = continue_class (objc_implementation_context);
		}
    break;

  case 440:
/* Line 1792 of yacc.c  */
#line 2470 "objc-parse.y"
    {
		  objc_implementation_context = objc_ivar_context
		    = start_class (CLASS_IMPLEMENTATION_TYPE, (yyvsp[(2) - (5)].ttype), (yyvsp[(4) - (5)].ttype), NULL_TREE);
                  objc_public_flag = 0;
		}
    break;

  case 441:
/* Line 1792 of yacc.c  */
#line 2476 "objc-parse.y"
    {
                  objc_ivar_chain
		    = continue_class (objc_implementation_context);
		}
    break;

  case 442:
/* Line 1792 of yacc.c  */
#line 2482 "objc-parse.y"
    {
		  objc_implementation_context
		    = start_class (CLASS_IMPLEMENTATION_TYPE, (yyvsp[(2) - (4)].ttype), (yyvsp[(4) - (4)].ttype), NULL_TREE);
                  objc_ivar_chain
		    = continue_class (objc_implementation_context);
		}
    break;

  case 443:
/* Line 1792 of yacc.c  */
#line 2490 "objc-parse.y"
    {
		  objc_interface_context
		    = start_class (CATEGORY_INTERFACE_TYPE, (yyvsp[(2) - (6)].ttype), (yyvsp[(4) - (6)].ttype), (yyvsp[(6) - (6)].ttype));
                  continue_class (objc_interface_context);
		}
    break;

  case 444:
/* Line 1792 of yacc.c  */
#line 2497 "objc-parse.y"
    {
		  finish_class (objc_interface_context);
		  objc_interface_context = NULL_TREE;
		}
    break;

  case 445:
/* Line 1792 of yacc.c  */
#line 2503 "objc-parse.y"
    {
		  objc_implementation_context
		    = start_class (CATEGORY_IMPLEMENTATION_TYPE, (yyvsp[(2) - (5)].ttype), (yyvsp[(4) - (5)].ttype), NULL_TREE);
                  objc_ivar_chain
		    = continue_class (objc_implementation_context);
		}
    break;

  case 446:
/* Line 1792 of yacc.c  */
#line 2513 "objc-parse.y"
    {
		  remember_protocol_qualifiers ();
		  objc_interface_context
		    = start_protocol(PROTOCOL_INTERFACE_TYPE, (yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		}
    break;

  case 447:
/* Line 1792 of yacc.c  */
#line 2519 "objc-parse.y"
    {
		  forget_protocol_qualifiers();
		  finish_protocol(objc_interface_context);
		  objc_interface_context = NULL_TREE;
		}
    break;

  case 448:
/* Line 1792 of yacc.c  */
#line 2528 "objc-parse.y"
    {
		  (yyval.ttype) = NULL_TREE;
		}
    break;

  case 450:
/* Line 1792 of yacc.c  */
#line 2536 "objc-parse.y"
    {
		  if ((yyvsp[(1) - (3)].code) == LT_EXPR && (yyvsp[(3) - (3)].code) == GT_EXPR)
		    (yyval.ttype) = (yyvsp[(2) - (3)].ttype);
		  else
		    YYERROR1;
		}
    break;

  case 453:
/* Line 1792 of yacc.c  */
#line 2550 "objc-parse.y"
    { objc_public_flag = 2; }
    break;

  case 454:
/* Line 1792 of yacc.c  */
#line 2551 "objc-parse.y"
    { objc_public_flag = 0; }
    break;

  case 455:
/* Line 1792 of yacc.c  */
#line 2552 "objc-parse.y"
    { objc_public_flag = 1; }
    break;

  case 456:
/* Line 1792 of yacc.c  */
#line 2557 "objc-parse.y"
    {
                  (yyval.ttype) = NULL_TREE;
                }
    break;

  case 458:
/* Line 1792 of yacc.c  */
#line 2562 "objc-parse.y"
    {
                  if (pedantic)
		    pedwarn ("extra semicolon in struct or union specified");
                }
    break;

  case 459:
/* Line 1792 of yacc.c  */
#line 2580 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype);
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (3)].itype)); }
    break;

  case 460:
/* Line 1792 of yacc.c  */
#line 2586 "objc-parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype);
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (3)].itype)); }
    break;

  case 461:
/* Line 1792 of yacc.c  */
#line 2592 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 462:
/* Line 1792 of yacc.c  */
#line 2597 "objc-parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 465:
/* Line 1792 of yacc.c  */
#line 2604 "objc-parse.y"
    {
		  (yyval.ttype) = add_instance_variable (objc_ivar_context,
					      objc_public_flag,
					      (yyvsp[(1) - (1)].ttype), current_declspecs,
					      NULL_TREE);
                }
    break;

  case 466:
/* Line 1792 of yacc.c  */
#line 2611 "objc-parse.y"
    {
		  (yyval.ttype) = add_instance_variable (objc_ivar_context,
					      objc_public_flag,
					      (yyvsp[(1) - (3)].ttype), current_declspecs, (yyvsp[(3) - (3)].ttype));
                }
    break;

  case 467:
/* Line 1792 of yacc.c  */
#line 2617 "objc-parse.y"
    {
		  (yyval.ttype) = add_instance_variable (objc_ivar_context,
					      objc_public_flag,
					      NULL_TREE,
					      current_declspecs, (yyvsp[(2) - (2)].ttype));
                }
    break;

  case 468:
/* Line 1792 of yacc.c  */
#line 2627 "objc-parse.y"
    {
		  remember_protocol_qualifiers ();
		  if (objc_implementation_context)
		    objc_inherit_code = CLASS_METHOD_DECL;
                  else
		    fatal ("method definition not in class context");
		}
    break;

  case 469:
/* Line 1792 of yacc.c  */
#line 2635 "objc-parse.y"
    {
		  forget_protocol_qualifiers ();
		  add_class_method (objc_implementation_context, (yyvsp[(3) - (3)].ttype));
		  start_method_def ((yyvsp[(3) - (3)].ttype));
		  objc_method_context = (yyvsp[(3) - (3)].ttype);
		}
    break;

  case 470:
/* Line 1792 of yacc.c  */
#line 2642 "objc-parse.y"
    {
		  continue_method_def ();
		}
    break;

  case 471:
/* Line 1792 of yacc.c  */
#line 2646 "objc-parse.y"
    {
		  finish_method_def ();
		  objc_method_context = NULL_TREE;
		}
    break;

  case 472:
/* Line 1792 of yacc.c  */
#line 2652 "objc-parse.y"
    {
		  remember_protocol_qualifiers ();
		  if (objc_implementation_context)
		    objc_inherit_code = INSTANCE_METHOD_DECL;
                  else
		    fatal ("method definition not in class context");
		}
    break;

  case 473:
/* Line 1792 of yacc.c  */
#line 2660 "objc-parse.y"
    {
		  forget_protocol_qualifiers ();
		  add_instance_method (objc_implementation_context, (yyvsp[(3) - (3)].ttype));
		  start_method_def ((yyvsp[(3) - (3)].ttype));
		  objc_method_context = (yyvsp[(3) - (3)].ttype);
		}
    break;

  case 474:
/* Line 1792 of yacc.c  */
#line 2667 "objc-parse.y"
    {
		  continue_method_def ();
		}
    break;

  case 475:
/* Line 1792 of yacc.c  */
#line 2671 "objc-parse.y"
    {
		  finish_method_def ();
		  objc_method_context = NULL_TREE;
		}
    break;

  case 477:
/* Line 1792 of yacc.c  */
#line 2683 "objc-parse.y"
    {(yyval.ttype) = NULL_TREE; }
    break;

  case 482:
/* Line 1792 of yacc.c  */
#line 2690 "objc-parse.y"
    {(yyval.ttype) = NULL_TREE; }
    break;

  case 486:
/* Line 1792 of yacc.c  */
#line 2700 "objc-parse.y"
    {
		  /* Remember protocol qualifiers in prototypes.  */
		  remember_protocol_qualifiers ();
		  objc_inherit_code = CLASS_METHOD_DECL;
		}
    break;

  case 487:
/* Line 1792 of yacc.c  */
#line 2706 "objc-parse.y"
    {
		  /* Forget protocol qualifiers here.  */
		  forget_protocol_qualifiers ();
		  add_class_method (objc_interface_context, (yyvsp[(3) - (3)].ttype));
		}
    break;

  case 489:
/* Line 1792 of yacc.c  */
#line 2714 "objc-parse.y"
    {
		  /* Remember protocol qualifiers in prototypes.  */
		  remember_protocol_qualifiers ();
		  objc_inherit_code = INSTANCE_METHOD_DECL;
		}
    break;

  case 490:
/* Line 1792 of yacc.c  */
#line 2720 "objc-parse.y"
    {
		  /* Forget protocol qualifiers here.  */
		  forget_protocol_qualifiers ();
		  add_instance_method (objc_interface_context, (yyvsp[(3) - (3)].ttype));
		}
    break;

  case 492:
/* Line 1792 of yacc.c  */
#line 2730 "objc-parse.y"
    {
		  (yyval.ttype) = build_method_decl (objc_inherit_code, (yyvsp[(2) - (4)].ttype), (yyvsp[(4) - (4)].ttype), NULL_TREE);
		}
    break;

  case 493:
/* Line 1792 of yacc.c  */
#line 2735 "objc-parse.y"
    {
		  (yyval.ttype) = build_method_decl (objc_inherit_code, NULL_TREE, (yyvsp[(1) - (1)].ttype), NULL_TREE);
		}
    break;

  case 494:
/* Line 1792 of yacc.c  */
#line 2740 "objc-parse.y"
    {
		  (yyval.ttype) = build_method_decl (objc_inherit_code, (yyvsp[(2) - (5)].ttype), (yyvsp[(4) - (5)].ttype), (yyvsp[(5) - (5)].ttype));
		}
    break;

  case 495:
/* Line 1792 of yacc.c  */
#line 2745 "objc-parse.y"
    {
		  (yyval.ttype) = build_method_decl (objc_inherit_code, NULL_TREE, (yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype));
		}
    break;

  case 504:
/* Line 1792 of yacc.c  */
#line 2775 "objc-parse.y"
    { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[(2) - (4)].itype)); }
    break;

  case 505:
/* Line 1792 of yacc.c  */
#line 2780 "objc-parse.y"
    { shadow_tag ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 506:
/* Line 1792 of yacc.c  */
#line 2782 "objc-parse.y"
    { pedwarn ("empty declaration"); }
    break;

  case 507:
/* Line 1792 of yacc.c  */
#line 2787 "objc-parse.y"
    { push_parm_decl ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 508:
/* Line 1792 of yacc.c  */
#line 2789 "objc-parse.y"
    { push_parm_decl ((yyvsp[(3) - (3)].ttype)); }
    break;

  case 509:
/* Line 1792 of yacc.c  */
#line 2797 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(1) - (2)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(2) - (2)].ttype))); }
    break;

  case 510:
/* Line 1792 of yacc.c  */
#line 2802 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(1) - (2)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(2) - (2)].ttype))); }
    break;

  case 511:
/* Line 1792 of yacc.c  */
#line 2807 "objc-parse.y"
    { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[(1) - (2)].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[(2) - (2)].ttype))); }
    break;

  case 512:
/* Line 1792 of yacc.c  */
#line 2815 "objc-parse.y"
    {
	    	  (yyval.ttype) = NULL_TREE;
		}
    break;

  case 513:
/* Line 1792 of yacc.c  */
#line 2819 "objc-parse.y"
    {
		  /* oh what a kludge! */
		  (yyval.ttype) = (tree)1;
		}
    break;

  case 514:
/* Line 1792 of yacc.c  */
#line 2824 "objc-parse.y"
    {
		  pushlevel (0);
		}
    break;

  case 515:
/* Line 1792 of yacc.c  */
#line 2828 "objc-parse.y"
    {
	  	  /* returns a tree list node generated by get_parm_info */
		  (yyval.ttype) = (yyvsp[(3) - (3)].ttype);
		  poplevel (0, 0, 0);
		}
    break;

  case 518:
/* Line 1792 of yacc.c  */
#line 2843 "objc-parse.y"
    {
		  (yyval.ttype) = chainon ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype));
		}
    break;

  case 523:
/* Line 1792 of yacc.c  */
#line 2856 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 524:
/* Line 1792 of yacc.c  */
#line 2857 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 525:
/* Line 1792 of yacc.c  */
#line 2858 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 526:
/* Line 1792 of yacc.c  */
#line 2859 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 527:
/* Line 1792 of yacc.c  */
#line 2860 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 528:
/* Line 1792 of yacc.c  */
#line 2861 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 529:
/* Line 1792 of yacc.c  */
#line 2862 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 530:
/* Line 1792 of yacc.c  */
#line 2863 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 531:
/* Line 1792 of yacc.c  */
#line 2864 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 532:
/* Line 1792 of yacc.c  */
#line 2865 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 533:
/* Line 1792 of yacc.c  */
#line 2866 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 534:
/* Line 1792 of yacc.c  */
#line 2867 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 535:
/* Line 1792 of yacc.c  */
#line 2868 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 536:
/* Line 1792 of yacc.c  */
#line 2869 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 537:
/* Line 1792 of yacc.c  */
#line 2870 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 538:
/* Line 1792 of yacc.c  */
#line 2871 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 539:
/* Line 1792 of yacc.c  */
#line 2872 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 540:
/* Line 1792 of yacc.c  */
#line 2873 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 541:
/* Line 1792 of yacc.c  */
#line 2874 "objc-parse.y"
    { (yyval.ttype) = get_identifier (token_buffer); }
    break;

  case 544:
/* Line 1792 of yacc.c  */
#line 2880 "objc-parse.y"
    {
		  (yyval.ttype) = build_keyword_decl ((yyvsp[(1) - (6)].ttype), (yyvsp[(4) - (6)].ttype), (yyvsp[(6) - (6)].ttype));
		}
    break;

  case 545:
/* Line 1792 of yacc.c  */
#line 2885 "objc-parse.y"
    {
		  (yyval.ttype) = build_keyword_decl ((yyvsp[(1) - (3)].ttype), NULL_TREE, (yyvsp[(3) - (3)].ttype));
		}
    break;

  case 546:
/* Line 1792 of yacc.c  */
#line 2890 "objc-parse.y"
    {
		  (yyval.ttype) = build_keyword_decl (NULL_TREE, (yyvsp[(3) - (5)].ttype), (yyvsp[(5) - (5)].ttype));
		}
    break;

  case 547:
/* Line 1792 of yacc.c  */
#line 2895 "objc-parse.y"
    {
		  (yyval.ttype) = build_keyword_decl (NULL_TREE, NULL_TREE, (yyvsp[(2) - (2)].ttype));
		}
    break;

  case 551:
/* Line 1792 of yacc.c  */
#line 2908 "objc-parse.y"
    {
		  (yyval.ttype) = chainon ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype));
		}
    break;

  case 552:
/* Line 1792 of yacc.c  */
#line 2916 "objc-parse.y"
    {
		  if (TREE_CHAIN ((yyvsp[(1) - (1)].ttype)) == NULL_TREE)
		    /* just return the expr., remove a level of indirection */
		    (yyval.ttype) = TREE_VALUE ((yyvsp[(1) - (1)].ttype));
                  else
		    /* we have a comma expr., we will collapse later */
		    (yyval.ttype) = (yyvsp[(1) - (1)].ttype);
		}
    break;

  case 553:
/* Line 1792 of yacc.c  */
#line 2928 "objc-parse.y"
    {
		  (yyval.ttype) = build_tree_list ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		}
    break;

  case 554:
/* Line 1792 of yacc.c  */
#line 2932 "objc-parse.y"
    {
		  (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(2) - (2)].ttype));
		}
    break;

  case 556:
/* Line 1792 of yacc.c  */
#line 2940 "objc-parse.y"
    {
		  (yyval.ttype) = get_class_reference ((yyvsp[(1) - (1)].ttype));
		}
    break;

  case 557:
/* Line 1792 of yacc.c  */
#line 2947 "objc-parse.y"
    { objc_receiver_context = 1; }
    break;

  case 558:
/* Line 1792 of yacc.c  */
#line 2949 "objc-parse.y"
    { objc_receiver_context = 0; }
    break;

  case 559:
/* Line 1792 of yacc.c  */
#line 2951 "objc-parse.y"
    {
		  (yyval.ttype) = build_tree_list ((yyvsp[(3) - (6)].ttype), (yyvsp[(5) - (6)].ttype));
		}
    break;

  case 563:
/* Line 1792 of yacc.c  */
#line 2964 "objc-parse.y"
    {
		  (yyval.ttype) = chainon ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype));
		}
    break;

  case 564:
/* Line 1792 of yacc.c  */
#line 2971 "objc-parse.y"
    {
		  (yyval.ttype) = build_tree_list ((yyvsp[(1) - (2)].ttype), NULL_TREE);
		}
    break;

  case 565:
/* Line 1792 of yacc.c  */
#line 2975 "objc-parse.y"
    {
		  (yyval.ttype) = build_tree_list (NULL_TREE, NULL_TREE);
		}
    break;

  case 566:
/* Line 1792 of yacc.c  */
#line 2982 "objc-parse.y"
    {
		  (yyval.ttype) = (yyvsp[(3) - (4)].ttype);
		}
    break;

  case 567:
/* Line 1792 of yacc.c  */
#line 2989 "objc-parse.y"
    {
		  (yyval.ttype) = (yyvsp[(3) - (4)].ttype);
		}
    break;

  case 568:
/* Line 1792 of yacc.c  */
#line 2998 "objc-parse.y"
    {
		  (yyval.ttype) = groktypename ((yyvsp[(3) - (4)].ttype));
		}
    break;


/* Line 1792 of yacc.c  */
#line 6679 "objc-parse.c"
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
#line 3003 "objc-parse.y"

