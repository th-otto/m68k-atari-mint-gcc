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
#line 29 "parse.y"

/* Cause the `yydebug' variable to be defined.  */
#define YYDEBUG 1

#include "config.h"

#include "system.h"

#include "tree.h"
#include "input.h"
#include "flags.h"
#include "lex.h"
#include "cp-tree.h"
#include "output.h"
#include "except.h"
#include "toplev.h"

/* Since parsers are distinct for each language, put the language string
   definition here.  (fnf) */
char *language_string = "GNU C++";

extern tree void_list_node;
extern struct obstack permanent_obstack;

extern int end_of_file;

/* Like YYERROR but do call yyerror.  */
#define YYERROR1 { yyerror ("syntax error"); YYERROR; }

#define OP0(NODE) (TREE_OPERAND (NODE, 0))
#define OP1(NODE) (TREE_OPERAND (NODE, 1))

/* Contains the statement keyword (if/while/do) to include in an
   error message if the user supplies an empty conditional expression.  */
static const char *cond_stmt_keyword;

static tree empty_parms PROTO((void));
static int parse_decl PROTO((tree, tree, tree, int, tree *));

/* Nonzero if we have an `extern "C"' acting as an extern specifier.  */
int have_extern_spec;
int used_extern_spec;

/* Cons up an empty parameter list.  */
#ifdef __GNUC__
__inline
#endif
static tree
empty_parms ()
{
  tree parms;

  if (strict_prototype
      || current_class_type != NULL)
    parms = void_list_node;
  else
    parms = NULL_TREE;
  return parms;
}


/* Line 371 of yacc.c  */
#line 130 "parse.c"

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
   by #include "parse.h".  */
#ifndef YY_YY_PARSE_H_INCLUDED
# define YY_YY_PARSE_H_INCLUDED
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
     TYPENAME_ID = 259,
     SELFNAME = 260,
     PFUNCNAME = 261,
     SCSPEC = 262,
     TYPESPEC = 263,
     CV_QUALIFIER = 264,
     CONSTANT = 265,
     STRING = 266,
     ELLIPSIS = 267,
     SIZEOF = 268,
     ENUM = 269,
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
     SIGOF = 285,
     ATTRIBUTE = 286,
     EXTENSION = 287,
     LABEL = 288,
     REALPART = 289,
     IMAGPART = 290,
     AGGR = 291,
     VISSPEC = 292,
     DELETE = 293,
     NEW = 294,
     THIS = 295,
     OPERATOR = 296,
     CXX_TRUE = 297,
     CXX_FALSE = 298,
     NAMESPACE = 299,
     TYPENAME_KEYWORD = 300,
     USING = 301,
     LEFT_RIGHT = 302,
     TEMPLATE = 303,
     TYPEID = 304,
     DYNAMIC_CAST = 305,
     STATIC_CAST = 306,
     REINTERPRET_CAST = 307,
     CONST_CAST = 308,
     SCOPE = 309,
     EMPTY = 310,
     NSNAME = 311,
     PTYPENAME = 312,
     THROW = 313,
     ASSIGN = 314,
     OROR = 315,
     ANDAND = 316,
     MIN_MAX = 317,
     EQCOMPARE = 318,
     ARITHCOMPARE = 319,
     RSHIFT = 320,
     LSHIFT = 321,
     DOT_STAR = 322,
     POINTSAT_STAR = 323,
     MINUSMINUS = 324,
     PLUSPLUS = 325,
     UNARY = 326,
     HYPERUNARY = 327,
     PAREN_STAR_PAREN = 328,
     POINTSAT = 329,
     CATCH = 330,
     TRY = 331,
     PRE_PARSED_FUNCTION_DECL = 332,
     EXTERN_LANG_STRING = 333,
     ALL = 334,
     PRE_PARSED_CLASS_DECL = 335,
     DEFARG = 336,
     DEFARG_MARKER = 337,
     TYPENAME_DEFN = 338,
     IDENTIFIER_DEFN = 339,
     PTYPENAME_DEFN = 340,
     END_OF_LINE = 341,
     END_OF_SAVED_INPUT = 342
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 93 "parse.y"
long itype; tree ttype; char *strtype; enum tree_code code; flagged_type_tree ftype; 

/* Line 387 of yacc.c  */
#line 263 "parse.c"
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

#endif /* !YY_YY_PARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */
/* Line 390 of yacc.c  */
#line 287 "parse.y"

/* List of types and structure classes of the current declaration.  */
static tree current_declspecs;

/* List of prefix attributes in effect.
   Prefix attributes are parsed by the reserved_declspecs and declmods
   rules.  They create a list that contains *both* declspecs and attrs.  */
/* ??? It is not clear yet that all cases where an attribute can now appear in
   a declspec list have been updated.  */
static tree prefix_attributes;

/* When defining an aggregate, this is the kind of the most recent one
   being defined.  (For example, this might be class_type_node.)  */
static tree current_aggr;

/* When defining an enumeration, this is the type of the enumeration.  */
static tree current_enum_type;

/* Tell yyparse how to print a token's value, if yydebug is set.  */

#define YYPRINT(FILE,YYCHAR,YYLVAL) yyprint(FILE,YYCHAR,YYLVAL)
extern void yyprint			PROTO((FILE *, int, YYSTYPE));
extern tree combine_strings		PROTO((tree));

static int
parse_decl(declarator, specs_attrs, attributes, initialized, decl)
  tree declarator;
  tree specs_attrs;
  tree attributes;
  int initialized;
  tree* decl;
{
  int  sm;

  split_specs_attrs (specs_attrs, &current_declspecs, &prefix_attributes);
  if (current_declspecs
      && TREE_CODE (current_declspecs) != TREE_LIST)
    current_declspecs = build_decl_list (NULL_TREE, current_declspecs);
  if (have_extern_spec && !used_extern_spec)
    {
      current_declspecs = decl_tree_cons (NULL_TREE, 
					  get_identifier ("extern"), 
					  current_declspecs);
      used_extern_spec = 1;
    }
  sm = suspend_momentary ();
  *decl = start_decl (declarator, current_declspecs, initialized,
		      attributes, prefix_attributes);
  return sm;
}

/* Line 390 of yacc.c  */
#line 343 "parse.c"

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
#define YYLAST   12569

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  112
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  289
/* YYNRULES -- Number of rules.  */
#define YYNRULES  881
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1667

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   342

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   110,     2,     2,     2,    82,    70,     2,
      92,   108,    80,    78,    59,    79,    91,    81,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,    60,
      73,    63,    74,    65,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    93,     2,   111,    69,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,    68,   109,    85,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    61,    64,    66,    67,    71,    72,    75,
      76,    77,    83,    84,    86,    87,    88,    89,    90,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     7,    10,    13,    15,    16,
      17,    18,    20,    22,    23,    26,    29,    31,    33,    39,
      44,    50,    55,    56,    63,    64,    70,    72,    75,    77,
      80,    81,    88,    91,    95,    99,   103,   107,   112,   113,
     119,   122,   126,   128,   130,   133,   136,   138,   141,   142,
     148,   152,   154,   158,   160,   161,   164,   167,   171,   173,
     177,   179,   183,   185,   189,   192,   195,   198,   200,   202,
     208,   213,   216,   219,   223,   227,   230,   233,   237,   241,
     244,   247,   250,   253,   256,   258,   260,   262,   263,   265,
     268,   269,   271,   276,   280,   284,   285,   294,   300,   301,
     311,   318,   319,   328,   334,   335,   345,   352,   355,   358,
     360,   363,   365,   372,   377,   384,   389,   392,   394,   397,
     400,   402,   405,   407,   410,   413,   418,   421,   425,   426,
     427,   429,   433,   436,   440,   442,   447,   450,   455,   458,
     463,   466,   468,   470,   472,   474,   476,   478,   480,   482,
     484,   486,   488,   489,   496,   497,   504,   505,   511,   512,
     518,   519,   527,   528,   536,   537,   544,   545,   552,   553,
     554,   560,   566,   568,   570,   576,   582,   583,   585,   587,
     588,   590,   592,   596,   598,   600,   602,   604,   606,   608,
     610,   612,   614,   616,   618,   622,   624,   628,   629,   631,
     633,   634,   642,   644,   646,   650,   655,   659,   660,   664,
     666,   670,   674,   678,   682,   684,   686,   688,   691,   694,
     697,   700,   703,   706,   709,   714,   717,   722,   725,   729,
     733,   738,   744,   751,   758,   766,   769,   774,   780,   783,
     786,   788,   789,   794,   799,   803,   805,   809,   812,   816,
     821,   823,   826,   832,   834,   838,   842,   846,   850,   854,
     858,   862,   866,   870,   874,   878,   882,   886,   890,   894,
     898,   902,   906,   910,   916,   920,   924,   926,   929,   933,
     937,   939,   941,   943,   945,   947,   948,   954,   960,   966,
     972,   978,   980,   982,   984,   986,   989,   991,   994,   997,
    1001,  1006,  1011,  1013,  1015,  1017,  1021,  1023,  1025,  1027,
    1029,  1033,  1037,  1041,  1042,  1047,  1052,  1055,  1060,  1063,
    1068,  1071,  1074,  1076,  1081,  1083,  1091,  1099,  1107,  1115,
    1120,  1125,  1128,  1131,  1134,  1136,  1141,  1144,  1147,  1153,
    1157,  1160,  1163,  1169,  1173,  1179,  1183,  1188,  1195,  1198,
    1200,  1203,  1205,  1208,  1210,  1212,  1214,  1217,  1218,  1221,
    1224,  1228,  1232,  1236,  1239,  1242,  1245,  1247,  1249,  1251,
    1254,  1257,  1260,  1263,  1265,  1267,  1269,  1271,  1274,  1277,
    1281,  1285,  1289,  1294,  1296,  1299,  1302,  1305,  1307,  1309,
    1311,  1314,  1317,  1320,  1322,  1324,  1327,  1330,  1334,  1336,
    1339,  1341,  1343,  1345,  1350,  1355,  1360,  1365,  1367,  1369,
    1371,  1373,  1377,  1379,  1383,  1385,  1389,  1390,  1395,  1396,
    1403,  1407,  1408,  1413,  1415,  1419,  1423,  1424,  1429,  1433,
    1434,  1436,  1438,  1441,  1448,  1450,  1454,  1455,  1457,  1462,
    1469,  1474,  1476,  1478,  1480,  1482,  1484,  1488,  1489,  1492,
    1494,  1497,  1501,  1506,  1508,  1510,  1514,  1519,  1523,  1529,
    1531,  1536,  1540,  1544,  1545,  1549,  1553,  1557,  1558,  1561,
    1564,  1565,  1573,  1578,  1579,  1586,  1590,  1593,  1596,  1599,
    1600,  1601,  1602,  1613,  1615,  1616,  1618,  1619,  1621,  1623,
    1626,  1629,  1632,  1635,  1638,  1641,  1644,  1647,  1650,  1654,
    1659,  1663,  1666,  1670,  1672,  1673,  1677,  1680,  1683,  1685,
    1687,  1688,  1691,  1695,  1697,  1702,  1704,  1708,  1710,  1712,
    1717,  1722,  1725,  1728,  1732,  1736,  1737,  1739,  1743,  1746,
    1749,  1751,  1754,  1757,  1760,  1763,  1766,  1769,  1772,  1774,
    1777,  1780,  1784,  1787,  1790,  1795,  1800,  1803,  1805,  1811,
    1816,  1818,  1819,  1821,  1825,  1826,  1828,  1832,  1834,  1836,
    1838,  1840,  1845,  1850,  1855,  1860,  1865,  1869,  1874,  1879,
    1884,  1889,  1893,  1895,  1899,  1901,  1905,  1908,  1910,  1918,
    1919,  1922,  1924,  1927,  1928,  1931,  1936,  1941,  1944,  1949,
    1951,  1954,  1958,  1962,  1965,  1968,  1972,  1974,  1979,  1984,
    1988,  1992,  1995,  1997,  1999,  2002,  2004,  2006,  2009,  2012,
    2014,  2017,  2021,  2025,  2028,  2031,  2035,  2037,  2041,  2045,
    2048,  2051,  2055,  2057,  2062,  2066,  2071,  2075,  2077,  2080,
    2083,  2086,  2089,  2092,  2094,  2097,  2102,  2107,  2110,  2112,
    2114,  2116,  2118,  2121,  2126,  2129,  2132,  2135,  2138,  2140,
    2143,  2146,  2149,  2152,  2156,  2158,  2161,  2165,  2170,  2173,
    2176,  2179,  2182,  2185,  2188,  2193,  2196,  2198,  2201,  2204,
    2208,  2210,  2214,  2217,  2221,  2224,  2227,  2231,  2233,  2237,
    2242,  2244,  2247,  2251,  2254,  2257,  2259,  2263,  2266,  2269,
    2271,  2274,  2278,  2280,  2284,  2286,  2293,  2298,  2303,  2307,
    2313,  2317,  2321,  2325,  2328,  2330,  2332,  2335,  2338,  2341,
    2342,  2344,  2346,  2349,  2353,  2355,  2358,  2359,  2363,  2364,
    2365,  2371,  2373,  2374,  2377,  2379,  2381,  2383,  2386,  2387,
    2392,  2394,  2395,  2396,  2402,  2403,  2404,  2412,  2413,  2414,
    2415,  2416,  2429,  2430,  2431,  2439,  2440,  2446,  2447,  2455,
    2456,  2461,  2464,  2467,  2470,  2474,  2481,  2490,  2501,  2514,
    2519,  2523,  2526,  2529,  2531,  2533,  2535,  2537,  2539,  2540,
    2541,  2548,  2549,  2550,  2556,  2558,  2561,  2562,  2563,  2569,
    2571,  2573,  2577,  2581,  2584,  2587,  2590,  2593,  2596,  2598,
    2601,  2602,  2604,  2605,  2607,  2609,  2610,  2612,  2614,  2618,
    2623,  2625,  2629,  2630,  2632,  2634,  2636,  2639,  2642,  2645,
    2647,  2650,  2653,  2654,  2658,  2660,  2662,  2664,  2667,  2670,
    2673,  2678,  2681,  2684,  2687,  2690,  2693,  2696,  2698,  2701,
    2703,  2706,  2708,  2710,  2711,  2712,  2714,  2715,  2720,  2723,
    2725,  2727,  2731,  2732,  2736,  2740,  2744,  2746,  2749,  2752,
    2755,  2758,  2761,  2764,  2767,  2770,  2773,  2776,  2779,  2782,
    2785,  2788,  2791,  2794,  2797,  2800,  2803,  2806,  2809,  2812,
    2815,  2819,  2822,  2825,  2828,  2831,  2835,  2838,  2841,  2846,
    2851,  2855
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     113,     0,    -1,    -1,   114,    -1,    -1,   115,   121,    -1,
     114,   121,    -1,   114,    -1,    -1,    -1,    -1,    32,    -1,
      27,    -1,    -1,   122,   123,    -1,   149,   148,    -1,   145,
      -1,   142,    -1,   120,    92,   220,   108,    60,    -1,   134,
      58,   116,   109,    -1,   134,   117,   149,   118,   148,    -1,
     134,   117,   145,   118,    -1,    -1,    44,   164,    58,   124,
     116,   109,    -1,    -1,    44,    58,   125,   116,   109,    -1,
     126,    -1,   128,    60,    -1,   130,    -1,   119,   123,    -1,
      -1,    44,   164,    63,   127,   133,    60,    -1,    46,   314,
      -1,    46,   328,   314,    -1,    46,   328,   210,    -1,    46,
     132,   164,    -1,    46,   328,   164,    -1,    46,   328,   132,
     164,    -1,    -1,    46,    44,   131,   133,    60,    -1,    56,
      54,    -1,   132,    56,    54,    -1,   210,    -1,   314,    -1,
     328,   314,    -1,   328,   210,    -1,    98,    -1,   134,    98,
      -1,    -1,    48,    73,   136,   137,    74,    -1,    48,    73,
      74,    -1,   141,    -1,   137,    59,   141,    -1,   164,    -1,
      -1,   270,   138,    -1,    45,   138,    -1,   135,   270,   138,
      -1,   139,    -1,   139,    63,   226,    -1,   392,    -1,   392,
      63,   205,    -1,   140,    -1,   140,    63,   185,    -1,   135,
     143,    -1,   135,     1,    -1,   149,   148,    -1,   144,    -1,
     142,    -1,   134,   117,   149,   118,   148,    -1,   134,   117,
     144,   118,    -1,   119,   143,    -1,   237,    60,    -1,   230,
     236,    60,    -1,   227,   235,    60,    -1,   262,    60,    -1,
     237,    60,    -1,   230,   236,    60,    -1,   227,   235,    60,
      -1,   230,    60,    -1,   167,    60,    -1,   227,    60,    -1,
       1,    60,    -1,     1,   109,    -1,    60,    -1,   221,    -1,
     160,    -1,    -1,   159,    -1,   159,    60,    -1,    -1,   107,
      -1,   155,   147,   146,   339,    -1,   155,   147,   363,    -1,
     155,   147,     1,    -1,    -1,   319,     5,    92,   151,   383,
     108,   299,   395,    -1,   319,     5,    47,   299,   395,    -1,
      -1,   328,   319,     5,    92,   152,   383,   108,   299,   395,
      -1,   328,   319,     5,    47,   299,   395,    -1,    -1,   319,
     180,    92,   153,   383,   108,   299,   395,    -1,   319,   180,
      47,   299,   395,    -1,    -1,   328,   319,   180,    92,   154,
     383,   108,   299,   395,    -1,   328,   319,   180,    47,   299,
     395,    -1,   227,   224,    -1,   230,   311,    -1,   311,    -1,
     230,   150,    -1,   150,    -1,     5,    92,   383,   108,   299,
     395,    -1,     5,    47,   299,   395,    -1,   180,    92,   383,
     108,   299,   395,    -1,   180,    47,   299,   395,    -1,   230,
     156,    -1,   156,    -1,   227,   224,    -1,   230,   311,    -1,
     311,    -1,   230,   150,    -1,   150,    -1,    25,     3,    -1,
     158,   254,    -1,   158,    92,   197,   108,    -1,   158,    47,
      -1,    62,   161,   162,    -1,    -1,    -1,   163,    -1,   162,
      59,   163,    -1,   162,     1,    -1,    92,   197,   108,    -1,
      47,    -1,   165,    92,   197,   108,    -1,   165,    47,    -1,
     307,    92,   197,   108,    -1,   307,    47,    -1,   321,    92,
     197,   108,    -1,   321,    47,    -1,     3,    -1,     4,    -1,
       5,    -1,    57,    -1,    56,    -1,     3,    -1,    57,    -1,
      56,    -1,   104,    -1,   103,    -1,   105,    -1,    -1,    48,
     176,   233,    60,   168,   177,    -1,    -1,    48,   176,   227,
     224,   169,   177,    -1,    -1,    48,   176,   311,   170,   177,
      -1,    -1,    48,   176,   150,   171,   177,    -1,    -1,     7,
      48,   176,   233,    60,   172,   177,    -1,    -1,     7,    48,
     176,   227,   224,   173,   177,    -1,    -1,     7,    48,   176,
     311,   174,   177,    -1,    -1,     7,    48,   176,   150,   175,
     177,    -1,    -1,    -1,    57,    73,   183,   182,   181,    -1,
       4,    73,   183,   182,   181,    -1,   180,    -1,   178,    -1,
     164,    73,   183,    74,   181,    -1,     5,    73,   183,   182,
     181,    -1,    -1,    74,    -1,    76,    -1,    -1,   184,    -1,
     185,    -1,   184,    59,   185,    -1,   226,    -1,    57,    -1,
     205,    -1,    79,    -1,    78,    -1,    87,    -1,    86,    -1,
     110,    -1,   196,    -1,   205,    -1,    47,    -1,    92,   187,
     108,    -1,    47,    -1,    92,   191,   108,    -1,    -1,   191,
      -1,     1,    -1,    -1,   373,   224,   238,   247,    63,   192,
     255,    -1,   187,    -1,   109,    -1,   336,   334,   109,    -1,
     336,   334,     1,   109,    -1,   336,     1,   109,    -1,    -1,
      58,   195,   193,    -1,   348,    -1,   205,    59,   205,    -1,
     205,    59,     1,    -1,   196,    59,   205,    -1,   196,    59,
       1,    -1,   205,    -1,   196,    -1,   215,    -1,   119,   204,
      -1,    80,   204,    -1,    70,   204,    -1,    85,   204,    -1,
     186,   204,    -1,    67,   164,    -1,    13,   198,    -1,    13,
      92,   226,   108,    -1,    29,   198,    -1,    29,    92,   226,
     108,    -1,   217,   298,    -1,   217,   298,   202,    -1,   217,
     201,   298,    -1,   217,   201,   298,   202,    -1,   217,    92,
     200,   226,   199,    -1,   217,    92,   200,   226,   199,   202,
      -1,   217,   201,    92,   200,   226,   199,    -1,   217,   201,
      92,   200,   226,   199,   202,    -1,   218,   204,    -1,   218,
      93,   111,   204,    -1,   218,    93,   187,   111,   204,    -1,
      34,   204,    -1,    35,   204,    -1,   108,    -1,    -1,    92,
     200,   197,   108,    -1,    58,   200,   197,   109,    -1,    92,
     197,   108,    -1,    47,    -1,    92,   233,   108,    -1,    63,
     255,    -1,    92,   226,   108,    -1,   203,    92,   226,   108,
      -1,   198,    -1,   203,   198,    -1,   203,    58,   256,   268,
     109,    -1,   204,    -1,   205,    84,   205,    -1,   205,    83,
     205,    -1,   205,    78,   205,    -1,   205,    79,   205,    -1,
     205,    80,   205,    -1,   205,    81,   205,    -1,   205,    82,
     205,    -1,   205,    77,   205,    -1,   205,    76,   205,    -1,
     205,    75,   205,    -1,   205,    73,   205,    -1,   205,    74,
     205,    -1,   205,    72,   205,    -1,   205,    71,   205,    -1,
     205,    70,   205,    -1,   205,    68,   205,    -1,   205,    69,
     205,    -1,   205,    67,   205,    -1,   205,    66,   205,    -1,
     205,    65,   378,    62,   205,    -1,   205,    63,   205,    -1,
     205,    64,   205,    -1,    61,    -1,    61,   205,    -1,    85,
     393,   164,    -1,    85,   393,   178,    -1,   208,    -1,   400,
      -1,     3,    -1,    57,    -1,    56,    -1,    -1,     6,    73,
     207,   183,   182,    -1,   400,    73,   207,   183,   182,    -1,
      48,   164,    73,   183,   182,    -1,    48,     6,    73,   183,
     182,    -1,    48,   400,    73,   183,   182,    -1,   206,    -1,
       4,    -1,     5,    -1,   212,    -1,   248,   212,    -1,   206,
      -1,    80,   211,    -1,    70,   211,    -1,    92,   211,   108,
      -1,     3,    73,   183,   182,    -1,    56,    73,   184,   182,
      -1,   313,    -1,   206,    -1,   213,    -1,    92,   211,   108,
      -1,   206,    -1,    10,    -1,   219,    -1,   220,    -1,    92,
     187,   108,    -1,    92,   211,   108,    -1,    92,     1,   108,
      -1,    -1,    92,   216,   340,   108,    -1,   206,    92,   197,
     108,    -1,   206,    47,    -1,   215,    92,   197,   108,    -1,
     215,    47,    -1,   215,    93,   187,   111,    -1,   215,    87,
      -1,   215,    86,    -1,    40,    -1,     9,    92,   197,   108,
      -1,   317,    -1,    50,    73,   226,    74,    92,   187,   108,
      -1,    51,    73,   226,    74,    92,   187,   108,    -1,    52,
      73,   226,    74,    92,   187,   108,    -1,    53,    73,   226,
      74,    92,   187,   108,    -1,    49,    92,   187,   108,    -1,
      49,    92,   226,   108,    -1,   328,     3,    -1,   328,   208,
      -1,   328,   400,    -1,   316,    -1,   316,    92,   197,   108,
      -1,   316,    47,    -1,   222,   209,    -1,   222,   209,    92,
     197,   108,    -1,   222,   209,    47,    -1,   222,   210,    -1,
     222,   316,    -1,   222,   210,    92,   197,   108,    -1,   222,
     210,    47,    -1,   222,   316,    92,   197,   108,    -1,   222,
     316,    47,    -1,   222,    85,     8,    47,    -1,   222,     8,
      54,    85,     8,    47,    -1,   222,     1,    -1,    39,    -1,
     328,    39,    -1,    38,    -1,   328,   218,    -1,    42,    -1,
      43,    -1,    11,    -1,   220,    11,    -1,    -1,   215,    91,
      -1,   215,    94,    -1,   233,   235,    60,    -1,   227,   235,
      60,    -1,   230,   236,    60,    -1,   227,    60,    -1,   230,
      60,    -1,   119,   223,    -1,   305,    -1,   311,    -1,    47,
      -1,   225,    47,    -1,   231,   332,    -1,   300,   332,    -1,
     233,   332,    -1,   231,    -1,   300,    -1,   231,    -1,   228,
      -1,   230,   233,    -1,   233,   229,    -1,   233,   232,   229,
      -1,   230,   233,   229,    -1,   230,   233,   232,    -1,   230,
     233,   232,   229,    -1,     7,    -1,   229,   234,    -1,   229,
       7,    -1,   229,   248,    -1,   248,    -1,   300,    -1,     7,
      -1,   230,     9,    -1,   230,     7,    -1,   230,   248,    -1,
     248,    -1,   233,    -1,   300,   233,    -1,   233,   232,    -1,
     300,   233,   232,    -1,   234,    -1,   232,   234,    -1,   262,
      -1,     8,    -1,   308,    -1,    28,    92,   187,   108,    -1,
      28,    92,   226,   108,    -1,    30,    92,   187,   108,    -1,
      30,    92,   226,   108,    -1,     8,    -1,     9,    -1,   262,
      -1,   243,    -1,   235,    59,   239,    -1,   244,    -1,   236,
      59,   239,    -1,   245,    -1,   237,    59,   239,    -1,    -1,
     120,    92,   220,   108,    -1,    -1,   224,   238,   247,    63,
     240,   255,    -1,   224,   238,   247,    -1,    -1,   247,    63,
     242,   255,    -1,   247,    -1,   224,   238,   241,    -1,   311,
     238,   241,    -1,    -1,   311,   238,   246,   241,    -1,   150,
     238,   247,    -1,    -1,   248,    -1,   249,    -1,   248,   249,
      -1,    31,    92,    92,   250,   108,   108,    -1,   251,    -1,
     250,    59,   251,    -1,    -1,   252,    -1,   252,    92,     3,
     108,    -1,   252,    92,     3,    59,   197,   108,    -1,   252,
      92,   197,   108,    -1,   164,    -1,     7,    -1,     8,    -1,
       9,    -1,   164,    -1,   253,    59,   164,    -1,    -1,    63,
     255,    -1,   205,    -1,    58,   109,    -1,    58,   256,   109,
      -1,    58,   256,    59,   109,    -1,     1,    -1,   255,    -1,
     256,    59,   255,    -1,    93,   205,   111,   255,    -1,   164,
      62,   255,    -1,   256,    59,   164,    62,   255,    -1,    97,
      -1,   257,   147,   146,   339,    -1,   257,   147,   363,    -1,
     257,   147,     1,    -1,    -1,   259,   258,   148,    -1,   102,
     205,   107,    -1,   102,     1,   107,    -1,    -1,   261,   260,
      -1,   261,     1,    -1,    -1,    14,   164,    58,   263,   296,
     269,   109,    -1,    14,   164,    58,   109,    -1,    -1,    14,
      58,   264,   296,   269,   109,    -1,    14,    58,   109,    -1,
      14,   164,    -1,    14,   326,    -1,    45,   321,    -1,    -1,
      -1,    -1,   277,    58,   265,   283,   109,   247,   266,   261,
     267,   259,    -1,   277,    -1,    -1,    59,    -1,    -1,    59,
      -1,    36,    -1,   270,     7,    -1,   270,     8,    -1,   270,
       9,    -1,   270,    36,    -1,   270,   248,    -1,   270,   164,
      -1,   270,   166,    -1,   271,    58,    -1,   271,    62,    -1,
     270,   319,   164,    -1,   270,   328,   319,   164,    -1,   270,
     328,   164,    -1,   270,   179,    -1,   270,   319,   179,    -1,
     271,    -1,    -1,   272,   275,   278,    -1,   273,   278,    -1,
     270,    58,    -1,   276,    -1,   274,    -1,    -1,    62,   393,
      -1,    62,   393,   279,    -1,   280,    -1,   279,    59,   393,
     280,    -1,   281,    -1,   282,   393,   281,    -1,   321,    -1,
     307,    -1,    30,    92,   187,   108,    -1,    30,    92,   226,
     108,    -1,    37,   393,    -1,     7,   393,    -1,   282,    37,
     393,    -1,   282,     7,   393,    -1,    -1,   285,    -1,   283,
     284,   285,    -1,   283,   284,    -1,    37,    62,    -1,   286,
      -1,   285,   286,    -1,   287,    60,    -1,   287,   109,    -1,
     157,    62,    -1,   157,    96,    -1,   157,    25,    -1,   157,
      58,    -1,    60,    -1,   119,   286,    -1,   135,   286,    -1,
     135,   227,    60,    -1,   227,   288,    -1,   230,   289,    -1,
     311,   238,   247,   254,    -1,   150,   238,   247,   254,    -1,
      62,   205,    -1,     1,    -1,   230,   156,   238,   247,   254,
      -1,   156,   238,   247,   254,    -1,   128,    -1,    -1,   290,
      -1,   288,    59,   291,    -1,    -1,   293,    -1,   289,    59,
     295,    -1,   292,    -1,   293,    -1,   294,    -1,   295,    -1,
     305,   238,   247,   254,    -1,     4,    62,   205,   247,    -1,
     311,   238,   247,   254,    -1,   150,   238,   247,   254,    -1,
       3,    62,   205,   247,    -1,    62,   205,   247,    -1,   305,
     238,   247,   254,    -1,     4,    62,   205,   247,    -1,   311,
     238,   247,   254,    -1,     3,    62,   205,   247,    -1,    62,
     205,   247,    -1,   297,    -1,   296,    59,   297,    -1,   164,
      -1,   164,    63,   205,    -1,   373,   329,    -1,   373,    -1,
      92,   200,   226,   199,    93,   187,   111,    -1,    -1,   299,
       9,    -1,     9,    -1,   300,     9,    -1,    -1,   301,   187,
      -1,   301,    92,   197,   108,    -1,   301,    92,   383,   108,
      -1,   301,    47,    -1,   301,    92,     1,   108,    -1,   305,
      -1,   248,   305,    -1,    80,   300,   304,    -1,    70,   300,
     304,    -1,    80,   304,    -1,    70,   304,    -1,   327,   299,
     304,    -1,   306,    -1,   306,   303,   299,   395,    -1,   306,
      93,   302,   111,    -1,   306,    93,   111,    -1,    92,   304,
     108,    -1,   319,   318,    -1,   318,    -1,   318,    -1,   328,
     318,    -1,   307,    -1,   309,    -1,   328,   309,    -1,   319,
     318,    -1,   311,    -1,   248,   311,    -1,    80,   300,   310,
      -1,    70,   300,   310,    -1,    80,   310,    -1,    70,   310,
      -1,   327,   299,   310,    -1,   214,    -1,    80,   300,   310,
      -1,    70,   300,   310,    -1,    80,   312,    -1,    70,   312,
      -1,   327,   299,   310,    -1,   313,    -1,   214,   303,   299,
     395,    -1,    92,   312,   108,    -1,   214,    93,   302,   111,
      -1,   214,    93,   111,    -1,   315,    -1,   319,   213,    -1,
     319,   210,    -1,   319,   209,    -1,   319,   206,    -1,   319,
     209,    -1,   315,    -1,   328,   315,    -1,   233,    92,   197,
     108,    -1,   233,    92,   211,   108,    -1,   233,   225,    -1,
       4,    -1,     5,    -1,   178,    -1,   320,    -1,   319,   320,
      -1,   319,    48,   325,    54,    -1,     4,    54,    -1,     5,
      54,    -1,    56,    54,    -1,   178,    54,    -1,   322,    -1,
     328,   322,    -1,   323,   164,    -1,   323,   178,    -1,   323,
     325,    -1,   323,    48,   325,    -1,   324,    -1,   323,   324,
      -1,   323,   325,    54,    -1,   323,    48,   325,    54,    -1,
       4,    54,    -1,     5,    54,    -1,   178,    54,    -1,    57,
      54,    -1,     3,    54,    -1,    56,    54,    -1,   164,    73,
     183,   182,    -1,   328,   318,    -1,   309,    -1,   328,   309,
      -1,   319,    80,    -1,   328,   319,    80,    -1,    54,    -1,
      80,   299,   329,    -1,    80,   299,    -1,    70,   299,   329,
      -1,    70,   299,    -1,   327,   299,    -1,   327,   299,   329,
      -1,   330,    -1,    93,   187,   111,    -1,   330,    93,   302,
     111,    -1,   332,    -1,   248,   332,    -1,    80,   300,   331,
      -1,    80,   331,    -1,    80,   300,    -1,    80,    -1,    70,
     300,   331,    -1,    70,   331,    -1,    70,   300,    -1,    70,
      -1,   327,   299,    -1,   327,   299,   331,    -1,   333,    -1,
      92,   331,   108,    -1,    90,    -1,   333,    92,   383,   108,
     299,   395,    -1,   333,    47,   299,   395,    -1,   333,    93,
     302,   111,    -1,   333,    93,   111,    -1,    92,   384,   108,
     299,   395,    -1,   203,   299,   395,    -1,   225,   299,   395,
      -1,    93,   302,   111,    -1,    93,   111,    -1,   347,    -1,
     335,    -1,   334,   347,    -1,   334,   335,    -1,     1,    60,
      -1,    -1,   337,    -1,   338,    -1,   337,   338,    -1,    33,
     253,    60,    -1,   340,    -1,     1,   340,    -1,    -1,    58,
     341,   193,    -1,    -1,    -1,    15,   343,   189,   344,   345,
      -1,   340,    -1,    -1,   346,   348,    -1,   340,    -1,   348,
      -1,   223,    -1,   187,    60,    -1,    -1,   342,    16,   349,
     345,    -1,   342,    -1,    -1,    -1,    17,   350,   189,   351,
     194,    -1,    -1,    -1,    18,   352,   345,    17,   353,   188,
      60,    -1,    -1,    -1,    -1,    -1,    19,   354,    92,   376,
     355,   190,    60,   356,   378,   108,   357,   194,    -1,    -1,
      -1,    20,   358,    92,   191,   108,   359,   345,    -1,    -1,
      21,   205,    62,   360,   347,    -1,    -1,    21,   205,    12,
     205,    62,   361,   347,    -1,    -1,    22,    62,   362,   347,
      -1,    23,    60,    -1,    24,    60,    -1,    25,    60,    -1,
      25,   187,    60,    -1,   120,   377,    92,   220,   108,    60,
      -1,   120,   377,    92,   220,    62,   379,   108,    60,    -1,
     120,   377,    92,   220,    62,   379,    62,   379,   108,    60,
      -1,   120,   377,    92,   220,    62,   379,    62,   379,    62,
     382,   108,    60,    -1,    26,    80,   187,    60,    -1,    26,
     164,    60,    -1,   375,   347,    -1,   375,   109,    -1,    60,
      -1,   366,    -1,   130,    -1,   129,    -1,   126,    -1,    -1,
      -1,    96,   364,   146,   340,   365,   369,    -1,    -1,    -1,
      96,   367,   340,   368,   369,    -1,   370,    -1,   369,   370,
      -1,    -1,    -1,    95,   371,   374,   372,   340,    -1,   231,
      -1,   300,    -1,    92,    12,   108,    -1,    92,   392,   108,
      -1,     3,    62,    -1,    57,    62,    -1,     4,    62,    -1,
       5,    62,    -1,   378,    60,    -1,   223,    -1,    58,   193,
      -1,    -1,     9,    -1,    -1,   187,    -1,     1,    -1,    -1,
     380,    -1,   381,    -1,   380,    59,   381,    -1,    11,    92,
     187,   108,    -1,    11,    -1,   382,    59,    11,    -1,    -1,
     384,    -1,   226,    -1,   388,    -1,   389,    12,    -1,   388,
      12,    -1,   226,    12,    -1,    12,    -1,   388,    62,    -1,
     226,    62,    -1,    -1,    63,   386,   387,    -1,   101,    -1,
     255,    -1,   390,    -1,   392,   385,    -1,   389,   391,    -1,
     389,   394,    -1,   389,   394,    63,   255,    -1,   388,    59,
      -1,   226,    59,    -1,   228,   224,    -1,   231,   224,    -1,
     233,   224,    -1,   228,   332,    -1,   228,    -1,   230,   311,
      -1,   392,    -1,   392,   385,    -1,   390,    -1,   226,    -1,
      -1,    -1,   311,    -1,    -1,    61,    92,   397,   108,    -1,
      61,    47,    -1,   226,    -1,   396,    -1,   397,    59,   396,
      -1,    -1,    80,   299,   398,    -1,    70,   299,   398,    -1,
     327,   299,   398,    -1,    41,    -1,   399,    80,    -1,   399,
      81,    -1,   399,    82,    -1,   399,    78,    -1,   399,    79,
      -1,   399,    70,    -1,   399,    68,    -1,   399,    69,    -1,
     399,    85,    -1,   399,    59,    -1,   399,    75,    -1,   399,
      73,    -1,   399,    74,    -1,   399,    72,    -1,   399,    64,
      -1,   399,    63,    -1,   399,    77,    -1,   399,    76,    -1,
     399,    87,    -1,   399,    86,    -1,   399,    67,    -1,   399,
      66,    -1,   399,   110,    -1,   399,    65,    62,    -1,   399,
      71,    -1,   399,    94,    -1,   399,    84,    -1,   399,    47,
      -1,   399,    93,   111,    -1,   399,    39,    -1,   399,    38,
      -1,   399,    39,    93,   111,    -1,   399,    38,    93,   111,
      -1,   399,   373,   398,    -1,   399,     1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   340,   340,   342,   351,   351,   354,   359,   360,   364,
     369,   373,   379,   383,   383,   390,   392,   394,   396,   399,
     401,   404,   408,   407,   412,   411,   415,   416,   418,   419,
     425,   424,   436,   438,   440,   445,   447,   449,   455,   454,
     469,   475,   484,   485,   486,   488,   493,   495,   503,   502,
     506,   512,   514,   519,   522,   525,   527,   532,   544,   546,
     548,   550,   552,   554,   568,   570,   575,   577,   579,   581,
     584,   587,   592,   593,   595,   597,   603,   604,   606,   608,
     610,   611,   618,   619,   620,   624,   626,   630,   632,   633,
     636,   638,   642,   644,   650,   656,   655,   659,   664,   663,
     667,   672,   671,   675,   680,   679,   683,   690,   693,   696,
     699,   702,   708,   710,   712,   714,   721,   732,   735,   740,
     745,   748,   753,   759,   768,   770,   772,   777,   791,   811,
     812,   814,   815,   819,   825,   831,   833,   835,   837,   839,
     842,   848,   849,   850,   851,   852,   856,   857,   858,   862,
     863,   864,   869,   868,   873,   872,   877,   876,   880,   879,
     883,   882,   888,   886,   892,   891,   895,   894,   900,   903,
     910,   913,   916,   920,   921,   926,   932,   941,   942,   952,
     953,   957,   959,   964,   966,   968,   972,   974,   976,   978,
     980,   985,   987,   991,   995,  1000,  1004,  1010,  1011,  1012,
    1018,  1017,  1042,  1046,  1047,  1048,  1049,  1054,  1053,  1057,
    1062,  1065,  1068,  1070,  1075,  1077,  1081,  1084,  1087,  1089,
    1091,  1093,  1096,  1100,  1102,  1105,  1107,  1113,  1116,  1119,
    1122,  1134,  1139,  1143,  1147,  1152,  1154,  1158,  1162,  1164,
    1174,  1178,  1181,  1183,  1189,  1191,  1193,  1201,  1215,  1219,
    1226,  1227,  1229,  1243,  1245,  1247,  1249,  1251,  1253,  1255,
    1257,  1259,  1261,  1263,  1265,  1267,  1269,  1271,  1273,  1275,
    1277,  1279,  1281,  1283,  1285,  1289,  1291,  1293,  1311,  1313,
    1315,  1316,  1317,  1318,  1319,  1323,  1335,  1337,  1342,  1344,
    1346,  1352,  1353,  1354,  1358,  1359,  1368,  1369,  1371,  1373,
    1378,  1380,  1385,  1388,  1389,  1390,  1395,  1402,  1403,  1404,
    1418,  1420,  1423,  1426,  1425,  1441,  1443,  1445,  1447,  1449,
    1451,  1453,  1456,  1458,  1475,  1476,  1480,  1484,  1488,  1492,
    1494,  1498,  1500,  1502,  1510,  1512,  1514,  1516,  1520,  1522,
    1524,  1526,  1531,  1533,  1535,  1537,  1540,  1542,  1544,  1589,
    1591,  1596,  1598,  1603,  1605,  1611,  1612,  1618,  1630,  1632,
    1640,  1646,  1651,  1653,  1658,  1660,  1668,  1669,  1674,  1677,
    1684,  1687,  1690,  1694,  1697,  1708,  1709,  1713,  1716,  1719,
    1722,  1725,  1728,  1735,  1740,  1742,  1747,  1749,  1768,  1770,
    1772,  1775,  1781,  1783,  1794,  1797,  1800,  1803,  1809,  1811,
    1820,  1821,  1823,  1825,  1828,  1831,  1846,  1866,  1868,  1870,
    1874,  1875,  1880,  1881,  1886,  1887,  1893,  1894,  1900,  1899,
    1905,  1919,  1918,  1927,  1934,  1938,  1944,  1943,  1949,  1959,
    1960,  1965,  1967,  1972,  1977,  1979,  1985,  1986,  1988,  1990,
    1992,  2000,  2001,  2002,  2003,  2008,  2010,  2015,  2017,  2024,
    2025,  2028,  2031,  2034,  2041,  2043,  2046,  2048,  2050,  2055,
    2061,  2068,  2075,  2079,  2081,  2087,  2089,  2093,  2094,  2096,
    2102,  2101,  2112,  2117,  2116,  2127,  2131,  2134,  2137,  2144,
    2146,  2157,  2143,  2166,  2188,  2190,  2193,  2195,  2201,  2202,
    2204,  2206,  2208,  2210,  2215,  2223,  2225,  2227,  2232,  2238,
    2244,  2250,  2256,  2267,  2273,  2272,  2283,  2312,  2322,  2327,
    2331,  2333,  2335,  2340,  2341,  2346,  2350,  2357,  2359,  2360,
    2381,  2405,  2406,  2410,  2421,  2435,  2436,  2437,  2438,  2442,
    2457,  2461,  2468,  2469,  2474,  2476,  2478,  2480,  2482,  2484,
    2487,  2497,  2508,  2529,  2535,  2538,  2541,  2543,  2554,  2559,
    2562,  2569,  2570,  2577,  2589,  2590,  2597,  2608,  2609,  2613,
    2614,  2618,  2624,  2633,  2639,  2645,  2651,  2660,  2663,  2669,
    2672,  2675,  2685,  2686,  2691,  2693,  2699,  2702,  2708,  2720,
    2722,  2727,  2730,  2740,  2744,  2750,  2752,  2754,  2756,  2763,
    2764,  2774,  2776,  2778,  2780,  2782,  2786,  2790,  2792,  2794,
    2796,  2798,  2802,  2806,  2816,  2827,  2828,  2829,  2834,  2842,
    2843,  2852,  2854,  2856,  2858,  2860,  2864,  2868,  2870,  2872,
    2874,  2876,  2880,  2884,  2886,  2888,  2890,  2892,  2894,  2902,
    2905,  2911,  2914,  2920,  2921,  2926,  2928,  2930,  2934,  2935,
    2936,  2940,  2941,  2943,  2950,  2960,  2966,  2972,  2987,  2988,
    2993,  3006,  3008,  3010,  3015,  3020,  3033,  3035,  3040,  3052,
    3058,  3060,  3061,  3062,  3071,  3076,  3084,  3085,  3090,  3092,
    3099,  3105,  3107,  3109,  3111,  3113,  3117,  3121,  3126,  3128,
    3133,  3134,  3144,  3146,  3148,  3150,  3152,  3154,  3156,  3158,
    3160,  3164,  3168,  3173,  3176,  3177,  3179,  3181,  3183,  3185,
    3187,  3189,  3191,  3193,  3202,  3203,  3204,  3205,  3209,  3214,
    3216,  3222,  3223,  3227,  3241,  3243,  3248,  3247,  3255,  3260,
    3254,  3266,  3267,  3267,  3273,  3275,  3279,  3281,  3284,  3283,
    3290,  3293,  3298,  3292,  3302,  3304,  3301,  3311,  3313,  3315,
    3317,  3310,  3321,  3323,  3320,  3327,  3326,  3330,  3329,  3333,
    3332,  3335,  3337,  3339,  3341,  3343,  3349,  3355,  3358,  3361,
    3367,  3369,  3371,  3375,  3377,  3378,  3379,  3381,  3386,  3392,
    3385,  3405,  3407,  3404,  3413,  3414,  3419,  3421,  3418,  3427,
    3428,  3432,  3448,  3455,  3462,  3464,  3466,  3471,  3473,  3474,
    3484,  3486,  3492,  3493,  3494,  3502,  3503,  3507,  3508,  3513,
    3518,  3520,  3532,  3535,  3536,  3544,  3546,  3549,  3551,  3554,
    3556,  3566,  3582,  3581,  3588,  3589,  3594,  3597,  3600,  3603,
    3605,  3610,  3611,  3621,  3625,  3628,  3632,  3636,  3640,  3647,
    3650,  3656,  3657,  3661,  3666,  3671,  3683,  3685,  3687,  3692,
    3697,  3698,  3706,  3708,  3710,  3712,  3719,  3724,  3726,  3728,
    3730,  3732,  3734,  3736,  3738,  3740,  3742,  3744,  3746,  3748,
    3750,  3752,  3754,  3756,  3758,  3760,  3762,  3764,  3766,  3768,
    3770,  3772,  3774,  3776,  3778,  3780,  3782,  3784,  3786,  3788,
    3791,  3793
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "TYPENAME_ID", "SELFNAME",
  "PFUNCNAME", "SCSPEC", "TYPESPEC", "CV_QUALIFIER", "CONSTANT", "STRING",
  "ELLIPSIS", "SIZEOF", "ENUM", "IF", "ELSE", "WHILE", "DO", "FOR",
  "SWITCH", "CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN_KEYWORD",
  "GOTO", "ASM_KEYWORD", "TYPEOF", "ALIGNOF", "SIGOF", "ATTRIBUTE",
  "EXTENSION", "LABEL", "REALPART", "IMAGPART", "AGGR", "VISSPEC",
  "DELETE", "NEW", "THIS", "OPERATOR", "CXX_TRUE", "CXX_FALSE",
  "NAMESPACE", "TYPENAME_KEYWORD", "USING", "LEFT_RIGHT", "TEMPLATE",
  "TYPEID", "DYNAMIC_CAST", "STATIC_CAST", "REINTERPRET_CAST",
  "CONST_CAST", "SCOPE", "EMPTY", "NSNAME", "PTYPENAME", "'{'", "','",
  "';'", "THROW", "':'", "'='", "ASSIGN", "'?'", "OROR", "ANDAND", "'|'",
  "'^'", "'&'", "MIN_MAX", "EQCOMPARE", "'<'", "'>'", "ARITHCOMPARE",
  "RSHIFT", "LSHIFT", "'+'", "'-'", "'*'", "'/'", "'%'", "DOT_STAR",
  "POINTSAT_STAR", "'~'", "MINUSMINUS", "PLUSPLUS", "UNARY", "HYPERUNARY",
  "PAREN_STAR_PAREN", "'.'", "'('", "'['", "POINTSAT", "CATCH", "TRY",
  "PRE_PARSED_FUNCTION_DECL", "EXTERN_LANG_STRING", "ALL",
  "PRE_PARSED_CLASS_DECL", "DEFARG", "DEFARG_MARKER", "TYPENAME_DEFN",
  "IDENTIFIER_DEFN", "PTYPENAME_DEFN", "END_OF_LINE", "END_OF_SAVED_INPUT",
  "')'", "'}'", "'!'", "']'", "$accept", "program", "extdefs", "@1",
  "extdefs_opt", ".hush_warning", ".warning_ok", "extension",
  "asm_keyword", "lang_extdef", "$@2", "extdef", "$@3", "$@4",
  "namespace_alias", "$@5", "using_decl", "namespace_using_decl",
  "using_directive", "$@6", "namespace_qualifier", "any_id",
  "extern_lang_string", "template_header", "$@7", "template_parm_list",
  "maybe_identifier", "template_type_parm", "template_template_parm",
  "template_parm", "template_def", "template_extdef", "template_datadef",
  "datadef", "ctor_initializer_opt", "maybe_return_init",
  "eat_saved_input", "fndef", "constructor_declarator", "@8", "@9", "@10",
  "@11", "fn.def1", "component_constructor_declarator", "fn.def2",
  "return_id", "return_init", "base_init", ".set_base_init",
  "member_init_list", "member_init", "identifier", "notype_identifier",
  "identifier_defn", "explicit_instantiation", "$@12", "$@13", "$@14",
  "$@15", "$@16", "$@17", "$@18", "$@19", "begin_explicit_instantiation",
  "end_explicit_instantiation", "template_type", "apparent_template_type",
  "self_template_type", ".finish_template_type", "template_close_bracket",
  "template_arg_list_opt", "template_arg_list", "template_arg", "unop",
  "expr", "paren_expr_or_null", "paren_cond_or_null", "xcond", "condition",
  "@20", "compstmtend", "already_scoped_stmt", "@21",
  "nontrivial_exprlist", "nonnull_exprlist", "unary_expr",
  ".finish_new_placement", ".begin_new_placement", "new_placement",
  "new_initializer", "regcast_or_absdcl", "cast_expr", "expr_no_commas",
  "notype_unqualified_id", "do_id", "template_id", "object_template_id",
  "unqualified_id", "expr_or_declarator_intern", "expr_or_declarator",
  "notype_template_declarator", "direct_notype_declarator", "primary",
  "@22", "new", "delete", "boolean.literal", "string", "nodecls", "object",
  "decl", "declarator", "fcast_or_absdcl", "type_id", "typed_declspecs",
  "typed_declspecs1", "reserved_declspecs", "declmods", "typed_typespecs",
  "reserved_typespecquals", "typespec", "typespecqual_reserved",
  "initdecls", "notype_initdecls", "nomods_initdecls", "maybeasm",
  "initdcl", "@23", "initdcl0_innards", "@24", "initdcl0",
  "notype_initdcl0", "nomods_initdcl0", "$@25", "maybe_attribute",
  "attributes", "attribute", "attribute_list", "attrib", "any_word",
  "identifiers_or_typenames", "maybe_init", "init", "initlist",
  "fn.defpen", "pending_inline", "pending_inlines", "defarg_again",
  "pending_defargs", "structsp", "@26", "@27", "$@28", "@29", "$@30",
  "maybecomma", "maybecomma_warn", "aggr",
  "named_class_head_sans_basetype", "named_class_head_sans_basetype_defn",
  "named_complex_class_head_sans_basetype", "named_class_head", "@31",
  "unnamed_class_head", "class_head", "maybe_base_class_list",
  "base_class_list", "base_class", "base_class.1",
  "base_class_access_list", "opt.component_decl_list", "access_specifier",
  "component_decl_list", "component_decl", "component_decl_1",
  "components", "notype_components", "component_declarator0",
  "component_declarator", "after_type_component_declarator0",
  "notype_component_declarator0", "after_type_component_declarator",
  "notype_component_declarator", "enumlist", "enumerator", "new_type_id",
  "cv_qualifiers", "nonempty_cv_qualifiers", "suspend_mom",
  "nonmomentary_expr", "maybe_parmlist", "after_type_declarator_intern",
  "after_type_declarator", "direct_after_type_declarator",
  "nonnested_type", "complete_type_name", "nested_type",
  "notype_declarator_intern", "notype_declarator",
  "complex_notype_declarator", "complex_direct_notype_declarator",
  "qualified_id", "notype_qualified_id", "overqualified_id",
  "functional_cast", "type_name", "nested_name_specifier",
  "nested_name_specifier_1", "typename_sub", "typename_sub0",
  "typename_sub1", "typename_sub2", "explicit_template_type",
  "complex_type_name", "ptr_to_mem", "global_scope", "new_declarator",
  "direct_new_declarator", "absdcl_intern", "absdcl",
  "direct_abstract_declarator", "stmts", "errstmt", "maybe_label_decls",
  "label_decls", "label_decl", "compstmt_or_error", "compstmt", "@32",
  "simple_if", "@33", "$@34", "implicitly_scoped_stmt", "@35", "stmt",
  "simple_stmt", "$@36", "@37", "$@38", "@39", "$@40", "@41", "$@42",
  "$@43", "$@44", "$@45", "@46", "$@47", "$@48", "$@49",
  "function_try_block", "$@50", "$@51", "try_block", "@52", "$@53",
  "handler_seq", "handler", "@54", "$@55", "type_specifier_seq",
  "handler_args", "label_colon", "for.init.statement",
  "maybe_cv_qualifier", "xexpr", "asm_operands", "nonnull_asm_operands",
  "asm_operand", "asm_clobbers", "parmlist", "complex_parmlist", "defarg",
  "$@56", "defarg1", "parms", "parms_comma", "named_parm", "full_parm",
  "parm", "see_typename", "bad_parm", "exception_specification_opt",
  "ansi_raise_identifier", "ansi_raise_identifiers",
  "conversion_declarator", "operator", "operator_name", YY_NULL
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   123,    44,
      59,   313,    58,    61,   314,    63,   315,   316,   124,    94,
      38,   317,   318,    60,    62,   319,   320,   321,    43,    45,
      42,    47,    37,   322,   323,   126,   324,   325,   326,   327,
     328,    46,    40,    91,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,    41,   125,
      33,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   112,   113,   113,   115,   114,   114,   116,   116,   117,
     118,   119,   120,   122,   121,   123,   123,   123,   123,   123,
     123,   123,   124,   123,   125,   123,   123,   123,   123,   123,
     127,   126,   128,   128,   128,   129,   129,   129,   131,   130,
     132,   132,   133,   133,   133,   133,   134,   134,   136,   135,
     135,   137,   137,   138,   138,   139,   139,   140,   141,   141,
     141,   141,   141,   141,   142,   142,   143,   143,   143,   143,
     143,   143,   144,   144,   144,   144,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   146,   146,   147,   147,   147,
     148,   148,   149,   149,   149,   151,   150,   150,   152,   150,
     150,   153,   150,   150,   154,   150,   150,   155,   155,   155,
     155,   155,   156,   156,   156,   156,   157,   157,   157,   157,
     157,   157,   157,   158,   159,   159,   159,   160,   161,   162,
     162,   162,   162,   163,   163,   163,   163,   163,   163,   163,
     163,   164,   164,   164,   164,   164,   165,   165,   165,   166,
     166,   166,   168,   167,   169,   167,   170,   167,   171,   167,
     172,   167,   173,   167,   174,   167,   175,   167,   176,   177,
     178,   178,   178,   179,   179,   180,   181,   182,   182,   183,
     183,   184,   184,   185,   185,   185,   186,   186,   186,   186,
     186,   187,   187,   188,   188,   189,   189,   190,   190,   190,
     192,   191,   191,   193,   193,   193,   193,   195,   194,   194,
     196,   196,   196,   196,   197,   197,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     199,   200,   201,   201,   202,   202,   202,   202,   203,   203,
     204,   204,   204,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   206,   206,
     206,   206,   206,   206,   206,   207,   208,   208,   209,   209,
     209,   210,   210,   210,   211,   211,   212,   212,   212,   212,
     213,   213,   214,   214,   214,   214,   215,   215,   215,   215,
     215,   215,   215,   216,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   217,
     217,   218,   218,   219,   219,   220,   220,   221,   222,   222,
     223,   223,   223,   223,   223,   223,   224,   224,   225,   225,
     226,   226,   226,   226,   226,   227,   227,   228,   228,   228,
     228,   228,   228,   229,   229,   229,   229,   229,   230,   230,
     230,   230,   230,   230,   231,   231,   231,   231,   232,   232,
     233,   233,   233,   233,   233,   233,   233,   234,   234,   234,
     235,   235,   236,   236,   237,   237,   238,   238,   240,   239,
     239,   242,   241,   241,   243,   244,   246,   245,   245,   247,
     247,   248,   248,   249,   250,   250,   251,   251,   251,   251,
     251,   252,   252,   252,   252,   253,   253,   254,   254,   255,
     255,   255,   255,   255,   256,   256,   256,   256,   256,   257,
     258,   258,   258,   259,   259,   260,   260,   261,   261,   261,
     263,   262,   262,   264,   262,   262,   262,   262,   262,   265,
     266,   267,   262,   262,   268,   268,   269,   269,   270,   270,
     270,   270,   270,   270,   271,   272,   272,   272,   273,   273,
     273,   273,   273,   274,   275,   274,   274,   276,   277,   277,
     278,   278,   278,   279,   279,   280,   280,   281,   281,   281,
     281,   282,   282,   282,   282,   283,   283,   283,   283,   284,
     285,   285,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   288,   288,   288,   289,   289,   289,   290,   290,   291,
     291,   292,   292,   293,   293,   293,   293,   294,   294,   295,
     295,   295,   296,   296,   297,   297,   298,   298,   298,   299,
     299,   300,   300,   301,   302,   303,   303,   303,   303,   304,
     304,   305,   305,   305,   305,   305,   305,   306,   306,   306,
     306,   306,   306,   307,   307,   308,   308,   308,   309,   310,
     310,   311,   311,   311,   311,   311,   311,   312,   312,   312,
     312,   312,   312,   313,   313,   313,   313,   313,   313,   314,
     314,   315,   315,   316,   316,   317,   317,   317,   318,   318,
     318,   319,   319,   319,   320,   320,   320,   320,   321,   321,
     322,   322,   322,   322,   323,   323,   323,   323,   324,   324,
     324,   324,   324,   324,   325,   326,   326,   326,   327,   327,
     328,   329,   329,   329,   329,   329,   329,   329,   330,   330,
     331,   331,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   334,   334,   334,   334,   335,   336,
     336,   337,   337,   338,   339,   339,   341,   340,   343,   344,
     342,   345,   346,   345,   347,   347,   348,   348,   349,   348,
     348,   350,   351,   348,   352,   353,   348,   354,   355,   356,
     357,   348,   358,   359,   348,   360,   348,   361,   348,   362,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   364,   365,
     363,   367,   368,   366,   369,   369,   371,   372,   370,   373,
     373,   374,   374,   375,   375,   375,   375,   376,   376,   376,
     377,   377,   378,   378,   378,   379,   379,   380,   380,   381,
     382,   382,   383,   383,   383,   384,   384,   384,   384,   384,
     384,   384,   386,   385,   387,   387,   388,   388,   388,   388,
     388,   389,   389,   390,   390,   390,   390,   390,   390,   391,
     391,   392,   392,   393,   394,   394,   395,   395,   395,   396,
     397,   397,   398,   398,   398,   398,   399,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
     400,   400
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     0,     2,     2,     1,     0,     0,
       0,     1,     1,     0,     2,     2,     1,     1,     5,     4,
       5,     4,     0,     6,     0,     5,     1,     2,     1,     2,
       0,     6,     2,     3,     3,     3,     3,     4,     0,     5,
       2,     3,     1,     1,     2,     2,     1,     2,     0,     5,
       3,     1,     3,     1,     0,     2,     2,     3,     1,     3,
       1,     3,     1,     3,     2,     2,     2,     1,     1,     5,
       4,     2,     2,     3,     3,     2,     2,     3,     3,     2,
       2,     2,     2,     2,     1,     1,     1,     0,     1,     2,
       0,     1,     4,     3,     3,     0,     8,     5,     0,     9,
       6,     0,     8,     5,     0,     9,     6,     2,     2,     1,
       2,     1,     6,     4,     6,     4,     2,     1,     2,     2,
       1,     2,     1,     2,     2,     4,     2,     3,     0,     0,
       1,     3,     2,     3,     1,     4,     2,     4,     2,     4,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     6,     0,     5,     0,     5,
       0,     7,     0,     7,     0,     6,     0,     6,     0,     0,
       5,     5,     1,     1,     5,     5,     0,     1,     1,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     0,     1,     1,
       0,     7,     1,     1,     3,     4,     3,     0,     3,     1,
       3,     3,     3,     3,     1,     1,     1,     2,     2,     2,
       2,     2,     2,     2,     4,     2,     4,     2,     3,     3,
       4,     5,     6,     6,     7,     2,     4,     5,     2,     2,
       1,     0,     4,     4,     3,     1,     3,     2,     3,     4,
       1,     2,     5,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     3,     3,     1,     2,     3,     3,
       1,     1,     1,     1,     1,     0,     5,     5,     5,     5,
       5,     1,     1,     1,     1,     2,     1,     2,     2,     3,
       4,     4,     1,     1,     1,     3,     1,     1,     1,     1,
       3,     3,     3,     0,     4,     4,     2,     4,     2,     4,
       2,     2,     1,     4,     1,     7,     7,     7,     7,     4,
       4,     2,     2,     2,     1,     4,     2,     2,     5,     3,
       2,     2,     5,     3,     5,     3,     4,     6,     2,     1,
       2,     1,     2,     1,     1,     1,     2,     0,     2,     2,
       3,     3,     3,     2,     2,     2,     1,     1,     1,     2,
       2,     2,     2,     1,     1,     1,     1,     2,     2,     3,
       3,     3,     4,     1,     2,     2,     2,     1,     1,     1,
       2,     2,     2,     1,     1,     2,     2,     3,     1,     2,
       1,     1,     1,     4,     4,     4,     4,     1,     1,     1,
       1,     3,     1,     3,     1,     3,     0,     4,     0,     6,
       3,     0,     4,     1,     3,     3,     0,     4,     3,     0,
       1,     1,     2,     6,     1,     3,     0,     1,     4,     6,
       4,     1,     1,     1,     1,     1,     3,     0,     2,     1,
       2,     3,     4,     1,     1,     3,     4,     3,     5,     1,
       4,     3,     3,     0,     3,     3,     3,     0,     2,     2,
       0,     7,     4,     0,     6,     3,     2,     2,     2,     0,
       0,     0,    10,     1,     0,     1,     0,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     3,     4,
       3,     2,     3,     1,     0,     3,     2,     2,     1,     1,
       0,     2,     3,     1,     4,     1,     3,     1,     1,     4,
       4,     2,     2,     3,     3,     0,     1,     3,     2,     2,
       1,     2,     2,     2,     2,     2,     2,     2,     1,     2,
       2,     3,     2,     2,     4,     4,     2,     1,     5,     4,
       1,     0,     1,     3,     0,     1,     3,     1,     1,     1,
       1,     4,     4,     4,     4,     4,     3,     4,     4,     4,
       4,     3,     1,     3,     1,     3,     2,     1,     7,     0,
       2,     1,     2,     0,     2,     4,     4,     2,     4,     1,
       2,     3,     3,     2,     2,     3,     1,     4,     4,     3,
       3,     2,     1,     1,     2,     1,     1,     2,     2,     1,
       2,     3,     3,     2,     2,     3,     1,     3,     3,     2,
       2,     3,     1,     4,     3,     4,     3,     1,     2,     2,
       2,     2,     2,     1,     2,     4,     4,     2,     1,     1,
       1,     1,     2,     4,     2,     2,     2,     2,     1,     2,
       2,     2,     2,     3,     1,     2,     3,     4,     2,     2,
       2,     2,     2,     2,     4,     2,     1,     2,     2,     3,
       1,     3,     2,     3,     2,     2,     3,     1,     3,     4,
       1,     2,     3,     2,     2,     1,     3,     2,     2,     1,
       2,     3,     1,     3,     1,     6,     4,     4,     3,     5,
       3,     3,     3,     2,     1,     1,     2,     2,     2,     0,
       1,     1,     2,     3,     1,     2,     0,     3,     0,     0,
       5,     1,     0,     2,     1,     1,     1,     2,     0,     4,
       1,     0,     0,     5,     0,     0,     7,     0,     0,     0,
       0,    12,     0,     0,     7,     0,     5,     0,     7,     0,
       4,     2,     2,     2,     3,     6,     8,    10,    12,     4,
       3,     2,     2,     1,     1,     1,     1,     1,     0,     0,
       6,     0,     0,     5,     1,     2,     0,     0,     5,     1,
       1,     3,     3,     2,     2,     2,     2,     2,     1,     2,
       0,     1,     0,     1,     1,     0,     1,     1,     3,     4,
       1,     3,     0,     1,     1,     1,     2,     2,     2,     1,
       2,     2,     0,     3,     1,     1,     1,     2,     2,     2,
       4,     2,     2,     2,     2,     2,     2,     1,     2,     1,
       2,     1,     1,     0,     0,     1,     0,     4,     2,     1,
       1,     3,     0,     3,     3,     3,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     2,     2,     2,     2,     3,     2,     2,     4,     4,
       3,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,    13,    13,     1,     6,     0,     5,     0,   282,
     638,   639,     0,   389,   401,   581,     0,    12,     0,     0,
       0,    11,   488,   846,     0,     0,     0,   168,   670,   284,
     283,    84,     0,     0,   833,     0,    46,     0,     0,    14,
      26,     0,    28,     9,     0,    17,    16,    90,   111,    87,
       0,   640,   172,   303,   280,   304,   616,     0,   376,     0,
     375,   394,     0,   414,   393,   431,   400,     0,   503,   504,
     510,   509,   508,   483,   388,   605,   402,   606,   109,   302,
     627,   603,     0,   641,   579,     0,     0,   281,    82,    83,
     179,   644,   179,   645,   179,   285,   168,   141,   142,   143,
     145,   144,   473,   476,     0,   666,     0,   477,     0,     0,
       0,     0,   142,   143,   145,   144,    24,     0,     0,     0,
       0,     0,     0,     0,   478,   648,     0,   654,     0,     0,
       0,    38,     0,     0,    32,     0,     0,    48,     0,   646,
       0,   179,     0,     0,   614,   609,     0,     0,     0,   613,
       0,     0,     0,     0,   303,     0,   294,   583,     0,     0,
     302,   579,    29,     0,    27,     4,    47,     0,    65,   389,
       0,     0,     9,    68,    64,    67,    90,     0,     0,     0,
     400,    91,    15,     0,   429,     0,     0,   447,    88,    80,
     647,   583,     0,   579,    81,     0,     0,     0,   107,     0,
     410,   366,   596,   367,   602,     0,   579,   391,   390,    79,
     110,   377,     0,   412,   392,   108,   383,   407,   408,   378,
     396,   398,   387,   409,     0,    76,   432,   489,   490,   491,
     492,   507,   150,   149,   151,   494,   495,   173,   501,   493,
       0,     0,   496,   497,   510,   833,   506,   479,   582,   395,
       0,   426,   639,     0,   668,   172,   631,   632,   628,   608,
     642,     0,   607,   604,     0,   881,   877,   876,   874,   856,
     862,   861,     0,   868,   867,   853,   854,   852,   871,   860,
     858,   859,   857,   864,   863,   850,   851,   847,   848,   849,
     873,   855,   866,   865,     0,   872,   869,   779,   394,   780,
     842,   285,   282,   581,   307,   355,     0,     0,     0,     0,
     351,   349,   322,   353,   354,     0,     0,     0,     0,     0,
     284,   283,   276,     0,     0,   187,   186,     0,     0,   189,
     188,     0,   190,     0,     0,   180,   181,     0,   250,     0,
     253,   185,   306,   216,     0,     0,   308,   309,     0,   183,
     373,   394,   374,   633,   334,   324,     0,     0,     0,     0,
     179,     0,   475,     0,   470,     0,   667,   665,     0,   191,
     192,     0,     0,     0,   436,     4,    22,    30,   662,   658,
     659,   663,   661,   660,   141,   142,   143,     0,   145,   144,
     650,   651,   655,   652,   649,     0,   292,   293,   291,   630,
     629,    34,    33,    50,     0,   158,     0,     0,   394,   156,
       0,     0,   610,   612,     0,   611,   142,   143,   278,   279,
     298,     0,   620,   297,     0,   619,     0,   305,   284,   283,
       0,     0,     0,   296,   295,   624,     0,     0,    13,     0,
     168,    10,    10,    71,     0,    66,     0,     0,    72,    75,
       0,   428,   430,   123,    94,   128,   768,     0,    86,    85,
      93,   126,     0,     0,   124,    89,   626,     0,     0,   587,
       0,   836,     0,     0,   594,   589,     0,   593,     0,     0,
       0,     0,     0,   579,   429,     0,    78,   583,   579,   601,
       0,   380,   381,     0,    77,   429,   385,   384,   386,   379,
     399,   416,   415,   179,   498,   502,   500,     0,   505,   511,
       0,   397,   429,   579,    95,     0,     0,     0,     0,   579,
     101,   580,   615,   639,   669,   172,     0,     0,   870,   875,
     396,   579,   579,     0,   579,   880,   179,     0,     0,     0,
     223,     0,     0,   225,   238,   239,     0,     0,     0,     0,
       0,   277,   222,   219,   218,   220,     0,     0,     0,     0,
       0,   306,     0,     0,     0,   217,   177,   178,   300,     0,
     221,     0,     0,   251,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   316,     0,   318,   321,
     320,   358,     0,     0,   359,   241,   241,     0,   227,   577,
       0,   235,   356,   348,     0,     0,   833,   337,   340,   341,
       0,     0,   368,   689,   685,   694,     0,   583,   579,   579,
     579,   370,   692,     0,   637,   372,     0,     0,   371,   336,
       0,   331,   350,   332,   352,   634,     0,   333,   176,   176,
       0,   166,     0,   394,   164,   574,   486,   572,   472,     0,
       0,   403,     0,     0,   404,   405,   406,   442,   443,   444,
     441,     0,   434,   437,     0,     4,     0,   653,   179,   656,
       0,    42,    43,     0,    54,     0,     0,    58,    62,    51,
     832,   827,     0,   373,   394,    54,   374,   831,    60,   169,
     154,   152,   169,   301,   176,   618,   617,   305,     0,   621,
       0,    19,    21,    90,    10,    10,    74,    73,     0,   129,
     357,     0,   716,    92,   714,   453,     0,   449,   448,   215,
       0,   214,   584,   625,     0,   809,     0,   804,   394,     0,
     803,   805,   834,   816,     0,     0,   623,   590,   592,   591,
       0,     0,     0,     0,     0,     0,   579,   600,     0,   424,
     423,   411,   599,     0,   836,   595,   382,   413,   425,   429,
       0,   499,   638,   639,   833,     0,   833,   640,   512,   513,
     515,   833,   518,   517,     0,   547,   639,     0,   538,     0,
       0,   550,     0,   122,   117,     0,   172,   551,   554,     0,
       0,   530,     0,   120,   427,   836,   802,   179,   179,   643,
     179,   836,   802,   579,    98,   579,   104,   879,   878,   842,
     842,   842,     0,     0,     0,     0,   637,     0,     0,     0,
       0,   394,     0,     0,     0,   312,     0,   310,   311,     0,
     248,   182,   282,   638,   639,   284,   283,     0,     0,   454,
     484,     0,   274,   275,   794,   793,     0,   272,   271,   269,
     270,   268,   267,   266,   264,   265,   263,   262,   261,   256,
     257,   258,   259,   260,   255,   254,     0,     0,     0,     0,
       0,   241,   229,   245,     0,     0,   228,   579,   579,     0,
     579,   576,   677,     0,     0,     0,     0,     0,   339,     0,
     343,     0,   345,     0,     0,   688,   687,   680,   684,   683,
     832,   393,     0,     0,   703,     0,     0,   836,   369,   836,
     690,   579,   802,   583,   689,   685,     0,     0,   579,     0,
     393,     0,     0,     0,     0,   171,   175,   286,   169,   162,
     160,   169,     0,   487,     0,   486,   213,   212,   211,   210,
     436,     0,     0,    25,     0,     0,   657,     0,    39,    45,
      44,    56,    53,    54,     0,    49,     0,     0,   689,   685,
       0,   823,   579,   826,   828,     0,   824,   825,    55,   494,
       0,   159,   169,   169,   157,   170,   299,    18,    20,    70,
      90,   417,   146,   134,   148,   147,     0,   127,   130,     0,
       0,     0,     0,   715,   709,   450,     0,   125,   588,   585,
     808,   822,   811,     0,   586,   807,   821,   810,   806,   835,
     818,   829,   819,   812,   817,   838,     0,     0,     0,     0,
     421,   598,   597,   420,   176,   522,     0,   521,   833,   833,
     833,     0,   579,   802,   546,   539,   551,   540,   429,   429,
     536,   537,   534,   535,   579,   802,   282,   638,     0,   416,
     118,   542,   552,   557,   558,   416,   416,     0,     0,   416,
     116,   543,   555,   416,     0,   429,     0,   531,   532,   533,
     429,    97,     0,     0,     0,     0,   103,     0,   836,   802,
     836,   802,   844,   843,   845,   287,   323,   224,   226,   329,
     330,     0,     0,     0,     0,   311,   314,     0,     0,     0,
       0,   249,     0,   315,   317,   319,     0,     0,     0,     0,
     230,   247,     0,     0,   674,   672,     0,   675,   583,   236,
       0,     0,   179,   346,     0,     0,     0,   681,   686,   682,
     693,   579,   702,   700,   701,   691,   836,     0,   698,     0,
       0,   635,   636,   689,   685,     0,     0,   335,   167,   169,
     169,   165,   575,   573,   474,     0,   435,   433,   282,     0,
      23,    31,   664,    57,    52,    59,    63,     0,   688,   684,
     689,   685,     0,   393,   603,     0,   579,   690,    61,   155,
     153,    69,     0,     0,   136,     0,   138,     0,   140,     0,
     769,     0,   203,   717,     0,   710,   711,     0,   451,   689,
     685,     0,   306,     0,   633,   830,     0,     0,   839,   840,
       0,     0,     0,     0,     0,     0,   418,   174,     0,     0,
       0,   524,   523,   516,   836,     0,   541,   447,   447,   836,
       0,     0,     0,   429,   429,     0,   429,   429,     0,   429,
       0,   529,   480,     0,   447,   579,   289,   288,   290,   579,
     100,     0,   106,     0,     0,     0,     0,     0,     0,   457,
       0,   455,   252,   273,   243,   242,   240,   231,     0,   244,
     246,   673,   671,   678,   676,     0,   237,     0,     0,   338,
     342,   344,   836,   696,   579,   697,   163,   161,   471,     0,
     438,   440,     0,   688,   684,   689,   685,     0,   579,   608,
     690,   133,   131,     0,     0,     0,     0,   445,     0,     0,
     282,   638,   639,   718,   731,   734,   737,   742,     0,     0,
       0,     0,     0,     0,     0,     0,   283,   763,   771,     0,
     790,   767,   766,   765,     0,   726,     0,     0,   394,     0,
     705,   724,   730,   704,   725,   764,     0,   712,   452,     0,
     636,   820,   814,   815,   813,     0,   837,   422,     0,   519,
     520,   514,   113,   579,   545,   549,   115,   579,   429,   429,
     566,   447,   282,   638,     0,   553,   559,   560,   416,   416,
     447,   447,     0,   447,   556,   467,   544,   836,   836,   579,
     579,     0,     0,     0,     0,   456,     0,     0,   232,   233,
     679,   347,   288,   699,   836,     0,   688,   684,     0,   690,
     135,   137,   139,   776,   770,   774,     0,   713,   708,   206,
     783,   785,   786,     0,     0,   722,     0,     0,     0,   749,
     751,   752,   753,     0,     0,     0,     0,     0,     0,     0,
     784,     0,   365,   791,     0,   727,   363,   416,     0,   364,
       0,   416,     0,     0,     0,   204,   707,   706,   728,   762,
     761,   311,   841,   419,   836,   836,   565,   562,   564,     0,
       0,   429,   429,   429,   561,   563,   548,     0,    96,   102,
     836,   836,   325,   326,   327,   328,   458,     0,   234,   695,
     439,   689,   685,     0,     0,     0,   775,   446,   195,     0,
     719,   732,   721,     0,     0,     0,     0,     0,   745,     0,
     754,     0,   760,    40,   145,    35,   145,     0,    36,   772,
       0,   361,   362,     0,     0,     0,   360,   205,   722,   112,
     114,   429,   429,   571,   447,   447,   469,     0,   468,   463,
      99,   105,   578,   393,     0,   777,   202,     0,   394,     0,
     722,     0,   735,   723,   709,   788,   738,     0,     0,     0,
       0,   750,   759,    41,    37,     0,     0,   729,   570,   568,
     567,   569,     0,     0,   482,     0,     0,     0,   196,   416,
     720,   207,   733,   209,     0,   789,     0,   787,   743,   747,
     746,   773,   795,     0,   466,   465,   459,    87,    90,   781,
     782,   778,   429,   709,   193,     0,     0,   199,     0,   198,
     722,     0,     0,     0,   796,   797,   755,     0,   464,     0,
     208,     0,   736,   739,   744,   748,     0,   795,     0,     0,
     462,     0,   461,   200,   194,     0,     0,     0,   756,   798,
     460,     0,     0,   799,     0,     0,   201,   740,   800,     0,
     757,     0,     0,     0,   741,   801,   758
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   438,     3,   439,   167,   712,   333,   183,     5,
       6,    39,   675,   375,  1341,   676,   791,  1342,  1343,   395,
    1448,   680,    43,   792,   404,   686,   961,   687,   688,   689,
      45,   174,   175,    46,   457,   186,   182,    47,    48,   806,
    1089,   812,  1091,    49,   794,   795,   187,   188,   458,   719,
     997,   998,   655,   999,   236,    50,   983,   982,   702,   699,
    1160,  1159,   941,   938,   138,   981,    51,   238,    52,   935,
     568,   334,   335,   336,   337,  1344,  1616,  1510,  1618,  1557,
    1651,  1203,  1592,  1613,   369,   927,   338,  1277,   879,   607,
     886,   339,   340,   370,   342,   360,    54,   257,   681,   420,
     156,    55,    56,   343,   563,   344,   345,   346,   347,   459,
     348,  1345,   501,   629,   349,  1346,    58,   219,   692,   350,
     220,   541,   221,   199,   212,    62,   484,   502,  1368,   759,
    1225,   200,   213,    63,   512,   760,    64,    65,   671,   672,
     673,  1318,   464,   849,   850,  1607,  1608,  1584,  1548,  1487,
      66,   659,   363,   510,  1395,  1549,  1110,   944,    67,    68,
      69,    70,    71,   244,    72,    73,   246,   778,   779,   780,
     781,   799,  1076,   800,   801,   802,  1061,  1071,  1062,  1385,
    1063,  1064,  1386,  1387,   656,   657,   608,   917,   352,   467,
     468,   193,   482,   475,   202,    75,    76,    77,   144,   145,
     159,    79,   134,   353,   354,   355,    81,   356,    83,   783,
     125,   126,   127,   517,   107,    84,   357,   891,   892,   912,
     907,   632,  1349,  1350,  1204,  1205,  1206,   723,  1351,  1004,
    1352,  1433,  1560,  1513,  1514,  1353,  1354,  1538,  1434,  1561,
    1435,  1594,  1436,  1596,  1645,  1661,  1437,  1620,  1570,  1621,
    1519,   460,   720,  1316,  1355,  1451,  1575,  1424,  1425,  1505,
    1587,  1559,  1555,  1356,  1566,  1454,   856,  1623,  1624,  1625,
    1659,   739,   913,  1024,  1217,  1364,   741,   742,   743,  1020,
     744,   150,  1022,   746,  1219,  1220,   535,    86,    87
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1444
static const yytype_int16 yypact[] =
{
      97,   131,   231, -1444, -1444, -1444,  6086, -1444,    49,    38,
      52,   232,   176,   237, -1444, -1444,  1423, -1444,   219,   293,
     301, -1444, -1444, -1444,  1648,  1230,   430,   280, -1444,   236,
     333, -1444,  3476,  3476, -1444,  1540, -1444,  6086,   305, -1444,
   -1444,   359, -1444,    50,  6214, -1444, -1444,   388,   603,   437,
     406,   468, -1444, -1444, -1444, -1444,   365,  2016, -1444,  7389,
   -1444,  2134,   321, -1444,   503, -1444, -1444,  1389,    85, -1444,
     490, -1444, -1444,   506,  4769, -1444, -1444, -1444,  1093, -1444,
   -1444, -1444,  2245, -1444, -1444,   831,  4682,   497, -1444, -1444,
   11071, -1444, 11071, -1444, 11071, -1444, -1444, -1444,    52,   232,
     528,   333,   475,   534,   468, -1444,  1009, -1444,   831, 11156,
   11156,   513, -1444, -1444, -1444, -1444, -1444,   221,   544,   253,
     444,   559,   478,   577, -1444, -1444,  1292, -1444,  1270,    52,
     232, -1444,   528,   333, -1444,   584,   277,   572, 12193, -1444,
   11071, 11071,  1689,  3602, -1444, -1444,  2936,   932,  3602, -1444,
    1878,  4133,  4133,  1540,   557,   563, -1444,   596,   793,   568,
     611, -1444, -1444,   716, -1444,   626, -1444,  7874, -1444, -1444,
     280,  6901,   639, -1444, -1444, -1444,   388,  5433, 12251,   363,
     684, -1444, -1444,   679,   503,   744,   111,   154,   719, -1444,
   -1444,   672,   447, -1444, -1444,  4588,  4588,  3756,  1093,   608,
   -1444, -1444,   436, -1444, -1444,  3403, -1444, -1444, -1444, -1444,
   -1444,  2134,   761, -1444,   503,  1093, -1444, -1444, -1444,  2604,
    2134, -1444,   503, -1444,  5433, -1444, -1444, -1444, -1444, -1444,
   -1444, -1444, -1444, -1444, -1444,   720, -1444,   468, -1444,   503,
    1707,  1992, -1444, -1444,   490, -1444, -1444, -1444, -1444,  1026,
     831, -1444,   677,  1375, -1444,   465, -1444, -1444, -1444, -1444,
   -1444,  4798, -1444, -1444,   319, -1444,   702,   712, -1444, -1444,
   -1444, -1444,   741, -1444, -1444, -1444, -1444, -1444, -1444, -1444,
   -1444, -1444, -1444, -1444, -1444, -1444, -1444, -1444, -1444, -1444,
   -1444, -1444, -1444, -1444,   697, -1444, -1444, -1444,  1026,  4769,
    1223, -1444, -1444,   726, -1444, -1444, 11757, 11842, 11927, 11927,
   -1444, -1444, -1444, -1444, -1444,   733,   769,   774,   781,   791,
     528,   880, 11241,  1995, 11927, -1444, -1444, 11927, 11927, -1444,
   -1444,  8782, -1444, 11927,   562,   810, -1444, 11927, -1444, 11326,
   -1444, 12470,   508,   900,  1871, 11411, -1444,   872,  2257, -1444,
    2603,  2463,   445, -1444,   531, -1444,   654,  2864,   562,   562,
   11071, 12193, -1444,  1995,   777,  1995, -1444, -1444,   803,   842,
   12403,   813,   817,   821,   756,   626, -1444, -1444, -1444, -1444,
   -1444, -1444, -1444, -1444,   544,   253,   444,  1995,   559,   478,
     860,   577, -1444,   895, -1444,  2447,    52,   232, -1444, -1444,
   -1444, -1444, -1444, -1444,  7496, -1444,  5433,  8429,  2592, -1444,
     545,   562, -1444, -1444,   650, -1444,   879,   890, -1444, -1444,
   -1444,  3602, -1444, -1444,  3602, -1444,   859, -1444, -1444, -1444,
     793,   793,   793, -1444, -1444, -1444,  4798,    72,   867,   875,
   -1444, -1444, -1444, -1444, 12193, -1444,   940,   957, -1444, -1444,
     716, -1444,   503, -1444, -1444, -1444, -1444,    94, -1444, -1444,
   -1444, -1444,  9329, 11241, -1444, -1444, -1444, 11241,   886, -1444,
    5340,    93,  5534,  4987, -1444, -1444,  4987, -1444,  5097,  5097,
    3756,  6418,   893, -1444,   503,  5433, -1444,   894, -1444, -1444,
    5106,  2604,  2134,  5433, -1444,   503, -1444, -1444,   503,  2604,
   -1444,   981, -1444, 11071,   720, -1444, -1444,  1707, -1444,  2455,
    4856,  1026,   503, -1444, -1444,   937,   953,   975,   973, -1444,
   -1444, -1444, -1444,   936, -1444,   561,   927,   939, -1444, -1444,
    1026, -1444, -1444,   710, -1444, -1444, 11071, 11241,   726,  8782,
   -1444,   581,  8782, -1444, -1444, -1444, 11156,  5069,  5069,  5069,
    5069, 12448, -1444, -1444, -1444, -1444,   944, 11502, 11502,  8782,
     959,   303,   961,  1014,   966, -1444, -1444, -1444, -1444, 11071,
   -1444,  8872,  8782, -1444, 11241, 11241,  9419, 11241, 11241, 11241,
   11241, 11241, 11241, 11241, 11241, 11241, 11241, 11241, 11241, 11241,
   11241, 11241, 11241, 11241, 11241, 11241, -1444, 11241, -1444, -1444,
   -1444, -1444, 11241, 11241, -1444, -1444, -1444,  3019,   456,   852,
    9954, -1444, -1444, -1444,  1028,  1375,  1078,   600,   605,   653,
    1075,   932, -1444,  3949,  3949, -1444,  6321,   977,  1002,  1054,
   -1444, -1444,   525,  6572,  1971, -1444,  1210,   831, -1444, -1444,
   11241, -1444, -1444, -1444, -1444, -1444,    84,   497, -1444, -1444,
     562, -1444,  5433,  2730, -1444,  1042,  1043, -1444, -1444,  1995,
     860, -1444,  9689,  9779, -1444, -1444, -1444, -1444, -1444, -1444,
   -1444,    54, -1444,  1020,   997,   626,  2447,  1063, 11071, -1444,
    1059, -1444, -1444,   277,  1987,  1085,   146,  1062,  1064, -1444,
   -1444,  2189, 12251,  2189,  4421,  1389,  3407, -1444,  1065, -1444,
   -1444, -1444, -1444, -1444, -1444, -1444, -1444,  1022,  1031, -1444,
    1080, -1444, -1444,   388, -1444, -1444, -1444, -1444,    79,   464,
    1074,  1014, -1444, -1444, -1444, -1444,  8689, 12448, -1444,   842,
    1034, 12403, -1444, -1444,  1036, -1444,  1040,   151,  5246,  1049,
   -1444,   116, 12017,  1084,  1088,   657, -1444, -1444, -1444, -1444,
    4987,  4987,  5792,  5792,  6418,  1210, -1444, -1444,  5106, -1444,
    1098, -1444, -1444,  1027,    93, -1444,  2604, -1444, -1444,   503,
    1091, -1444,   253,   444, -1444,  1082, -1444,   577,  1107, -1444,
   -1444,   108, -1444, -1444,  2132, -1444,  1030,   811, -1444, 11241,
    7645, -1444,  7645,   163,   163,   324,   682,  2303, 12075,    55,
    4967, -1444,    59,   163, -1444,    93,  7509, 11071, 11071, -1444,
   11071,    93,  7509, -1444, -1444, -1444, -1444, -1444, -1444,  1852,
    1852,  1852,   562,  1060,  1079, 10726,  1054,  1086,  1092,  1096,
    1108,  2844,  1109,  1110,  1112, -1444,  1099, -1444, -1444,  1101,
   -1444, -1444,  1105,    67,   451,   171,   583, 11241,  1126, -1444,
    1111,  1102, 12448, 12448, -1444, -1444,  1128,  8070,  6671,  9978,
   12485,  4038,  3825,  4070,  2753,  2753,  2753,  2620,  2620,   673,
     673,   361,   361,   361, -1444, -1444,  1103,  1115,  1081, 11241,
   11156, -1444,   456, -1444,  9329, 11241, -1444, -1444, -1444, 11241,
   -1444, -1444,  1100, 11927,  1090,  1121,  1123,  1172, -1444, 11241,
   -1444, 11241, -1444, 11241,  1884,  6424, -1444, -1444,  6424, -1444,
     134,  1884,  1122,  1135, -1444,  1118,  5069,    93, -1444,    93,
    6644, -1444,  7509,  1133, 10544, 10544,  8503,  1137, 11326,  1141,
    3279,  3509,  2864,  1511,  1142, -1444, -1444, -1444, -1444, -1444,
   -1444, -1444, 11241,  1995,  1144,  1043, -1444, 12448, -1444, 12448,
     756,  1143, 11587, -1444,  1146,  1197, -1444,   562, -1444, -1444,
   -1444, -1444, -1444,  2819,  7496, -1444,  5069, 11071,  1735,  1735,
    7981, -1444, -1444, -1444, -1444,  3403, -1444, -1444, -1444,   985,
   11241, -1444, -1444, -1444, -1444, -1444, -1444, -1444, -1444, -1444,
     388, -1444,   544, -1444,   559,   478, 11241,  1200, -1444,   693,
     705,   763,  1014, -1444,    48, -1444,    30, -1444, -1444, -1444,
   -1444, -1444, -1444, 10453, -1444, -1444, -1444, -1444, -1444, -1444,
   -1444,  1088,  1199, -1444, -1444, -1444,  5069,  2535,  2535,  3065,
   -1444, -1444, -1444,  1206, -1444, -1444, 11156, -1444, -1444, -1444,
   -1444,   965, -1444,  7509, 12448, -1444,  1398, -1444,   503,   503,
   -1444, -1444, -1444, -1444, -1444,  7509,   809,   779, 11241,   981,
   -1444,  1212, -1444, -1444, -1444,   239,   246,  2245,   932,   533,
     163,  1213, -1444,   655,  1216,   503,  5474, -1444, -1444, -1444,
     503, -1444,  1175,   562,   562,   562, -1444,  1177,    93,  7509,
      93,  7509, -1444, -1444, -1444, -1444, -1444, -1444, -1444, -1444,
   -1444,  1207,  1208,  1214,  1215,  1022, -1444, 12336,  9329,  8965,
    1180, -1444, 11241, -1444, -1444, -1444,  1182,  1184,  1194,  5069,
   -1444, -1444,  1203,   355,   385,   385,  1201,   385, -1444, -1444,
   11927,  1300, 11071, -1444,  1222,  1226,  1227, -1444, -1444, -1444,
   -1444, -1444, -1444, -1444, -1444, -1444,    93,  1229, -1444,  1204,
    3279, -1444, -1444,  2323,  2323,  8166,  3877, -1444, -1444, -1444,
   -1444, -1444, 12448, -1444, -1444,  1233, -1444, -1444,    68,  1231,
   -1444, -1444, -1444, -1444, -1444, -1444, -1444,  4234,  2675,  2675,
    3799,  3799,  7981,  4542,   248,  3403, -1444,  4325, 12470, -1444,
   -1444, -1444,  1236,   464, -1444, 11241, -1444, 11241, -1444, 11241,
   -1444,  1995, -1444, -1444,  8267,  1298, -1444,  9055, -1444, 10635,
   10635,  8596,   514,  1245,   518, -1444,  9329,  9145, -1444, -1444,
     181,  3125,  3125,  1168,  1168,  9329, -1444, -1444,  1247,  1253,
    2455, -1444, -1444, -1444,    93,  1256, -1444,  1291,  1291,    93,
    1259, 11241, 11241,  6456,   503,  3262,   503,   503,  1580,   503,
    3665, -1444, -1444,  5730,  1291, -1444, -1444,  1316, -1444, -1444,
   -1444,  1269, -1444,  1274, 11241, 11241, 11241, 11241,  9329, -1444,
    1327, -1444, -1444, 12448, -1444, -1444, -1444,   649,  1194, -1444,
   -1444, -1444, -1444, -1444, -1444,  1279, -1444,  1344,   562, -1444,
   -1444, -1444,    93, -1444, -1444, -1444, -1444, -1444, -1444, 11241,
   -1444, -1444,  4542,  2675,  2675,  4484,  4484,  8361, -1444,   601,
    4325, -1444, -1444,  1287,  1297,  1301,  1311, -1444,   996,   234,
    1346,   841,   851, -1444, -1444, -1444, -1444, -1444, 11241,  1349,
    1352,  1353, 10811,   360,  1995,   258,   819, -1444, -1444, 10901,
    1405, -1444, -1444, -1444,  1359, -1444,  6304, 12135, 12306,  7114,
   -1444, -1444,  1406, -1444, -1444, -1444, 10063, -1444, -1444,  1313,
     919, -1444, -1444, -1444, -1444,  5069, -1444, -1444,  9329, -1444,
   -1444, -1444, -1444, -1444, -1444, -1444, -1444, -1444,  6456,  6456,
   -1444,  1291,   853,   889, 11241, -1444, -1444, -1444,   981,   981,
    1291,  1291,   936,  1291, -1444, -1444, -1444,    93,    93, -1444,
   -1444,  1315,  1330,  1334,  1341, -1444,  9329, 11241, -1444,   649,
   -1444, -1444, -1444, -1444,    93,  1345,  6798,  6798,  1210,  7012,
   -1444, -1444, -1444, -1444,  1311, -1444,  1995, -1444, -1444, -1444,
   -1444, -1444, -1444,   780,   780,  1014,  1332,  1343,  5161, -1444,
   -1444, -1444, -1444,  1397, 11241,  1401,  1399,  1411,  2177,  2263,
   -1444,  1014, -1444, -1444,  1377, -1444, -1444,   981,  1004, -1444,
    1037,   981, 10986,  1039,   261, -1444, -1444, -1444, -1444, -1444,
   -1444,   640, -1444, -1444,    93,    93, -1444, -1444, -1444, 11241,
   11241,  6456,   503,   503, -1444, -1444, -1444,  5939, -1444, -1444,
      93,    93, -1444, -1444, -1444, -1444, -1444,  1356, -1444, -1444,
   -1444,  7238,  7238,  6792,  2024,  1381, -1444, -1444, -1444, 11156,
   -1444, -1444, -1444,  1465, 10359,  5632, 11156, 11241, -1444, 10171,
   -1444,  1424, -1444, -1444,  1431, -1444,  1411,  2177, -1444, -1444,
     716, -1444, -1444, 11672, 11672,  9239, -1444, -1444,  1014, -1444,
   -1444,  6456,  6456, -1444,  1291,  1291, -1444,  9869, -1444, -1444,
   -1444, -1444, -1444,  2024,  7783, -1444, -1444,  1379,   401,  5433,
    1014, 10265, -1444, -1444,    48, -1444, -1444,  1428,  1383, 12426,
   10171, -1444, -1444, -1444, -1444,  1311,    74, -1444, -1444, -1444,
   -1444, -1444,  1382, 12358,  1403,  1387,  1388,  1014, -1444,   981,
   -1444, -1444, -1444, -1444,   783, -1444,  9509, -1444, -1444, -1444,
   -1444,  1311,  1491,  1445, -1444, -1444, -1444,   437,   388, -1444,
   -1444, -1444,   503,    48, -1444, 11241,  1447, -1444,  1451, -1444,
    1014, 10171,  1425,    75,  1459, -1444, -1444,   123, -1444,  1456,
   -1444,  1412, -1444, -1444, -1444, -1444, 11241,  1491,  1462,  1491,
   -1444,    94, -1444, -1444, -1444,  9599,  1416,   149, -1444, -1444,
   -1444,  9329,  1418, -1444,  1519,  1477, -1444, -1444, -1444,   320,
   -1444, 10265,  1528,  1481, -1444, -1444, -1444
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1444, -1444,  1542, -1444,  -330,  1378,  -387,    61,     9,  1544,
   -1444,  1520, -1444, -1444,   222, -1444,   255, -1444,   494, -1444,
     107,   882,    33,    21, -1444, -1444,  -626, -1444, -1444,   598,
      35,  1392,  1116,  1402,  -704,   -42,  -168,   -18,   -22, -1444,
   -1444, -1444, -1444, -1444,   768, -1444, -1444, -1444, -1444, -1444,
   -1444,   381,  1076, -1444, -1444, -1444, -1444, -1444, -1444, -1444,
   -1444, -1444, -1444, -1444,  1490,  -683,  7337,  1337,   104,  -605,
    -143,   -85,  1448,  -535, -1444,   722, -1444,   158, -1444, -1422,
   -1444, -1128,   -68, -1444,  2640,  1246,  -243,   317,  -566, -1444,
    -850,  6925,  1508,  1993,  5137,  1302,  -335,   -86,  -100,  1581,
    -107,   -16,   629, -1444, -1444, -1444,  -336, -1444,  -162, -1444,
   -1444, -1280,   -10,  -346,  2238,    70,  2662,  -172,    17,   233,
    -207,    -6,   -78,  -171,  -166,    -1,    45,    23, -1444,  -274,
   -1444, -1444, -1444, -1444, -1444,    -7,  1466,     8, -1444,   648,
   -1444, -1444, -1137,  -388,   876, -1444, -1444, -1444, -1444, -1444,
     -20, -1444, -1444, -1444, -1444, -1444, -1444,   656,  -379, -1444,
   -1444, -1444, -1444, -1444, -1444, -1444,  1360, -1444,   376,   566,
   -1444, -1444, -1444,   532,  -730, -1444, -1444, -1444, -1444, -1444,
   -1444,   814, -1444,   371,   954,   680,  1017,  1853,   165,    22,
    -467,  1427,  3048,   669, -1444,  -492, -1444,     2,   126,   206,
    -149,   738,  -108,  5715,  1278, -1444,  6561,  2946,  1567,   -14,
    -118, -1444,  1501,   -74, -1444,  6080,  3911,  -197, -1444,  2742,
    1514, -1444, -1444,   286, -1444, -1444,   434,     0,    13, -1444,
   -1444, -1444, -1444, -1262, -1444, -1274, -1443, -1444, -1444, -1444,
   -1444, -1444, -1444, -1444, -1444, -1444, -1444, -1444, -1444, -1444,
   -1444,    16, -1444, -1444, -1444, -1444, -1444,    65, -1367, -1444,
   -1444,   -53, -1444, -1444, -1444, -1444, -1442,    19, -1444,     6,
   -1444,  -686,  -440,   625, -1444, -1444, -1444, -1444,  -391, -1444,
    -390,  -195, -1444,  2295,   292, -1444,   153, -1444,  -224
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -833
static const yytype_int16 yytable[] =
{
      61,   437,   422,   425,   492,   634,   446,   358,   445,   359,
     394,   124,   447,   697,   698,    38,  1002,   782,   105,   984,
     763,   644,   643,    59,   180,   695,   176,    44,   402,   518,
     740,    61,  1120,   300,   841,   400,   401,   210,    61,   491,
     880,   223,   511,   179,   936,   674,    38,   198,   499,   399,
     509,   434,   393,   211,    59,   713,   411,  1506,    44,  1452,
    1045,   178,  1047,   540,   543,    44,   258,    37,   249,   978,
    1077,  1563,   226,  1567,   728,  1467,    57,   172,   192,   173,
     298,  1201,  1470,   612,   351,   612,   351,   262,   351,  1207,
     612,   530,  1074,   184,  1568,   721,   573,    -2,    37,   985,
    1374,  1375,   521,   351,   351,   171,    91,    57,   165,    88,
     366,    90,   454,   950,   177,  1039,   405,  1396,  1593,  1078,
    1082,    91,   310,   251,  1640,    92,  1087,  1299,  1015,  -142,
     258,     4,   408,   647,   351,   351,  1602,  1637,    28,  1208,
      92,   497,   500,   242,   530,  1040,  1010,   243,   166,   442,
     226,   180,   722,   176,   745,   407,   210,  1202,    89,   149,
     915,    61,   951,  1010,  1075,    61,   226,   198,  1079,  -357,
     179,    74,   211,   455,  1619,  1016,  1300,   451,  1017,   192,
     710,  -357,  1603,  1638,    59,   455,   255,   991,   178,   258,
      17,   223,    44,  1011,  -416,   826,  1012,   143,   148,   223,
     223,   461,    74,  1652,   172,   964,   173,   456,   406,    74,
    1011,  1654,    78,  1012,  -832,   648,   649,   462,  1593,   456,
     965,   768,   226,  -416,   192,   139,  -416,  1000,    40,   223,
     226,    -3,   171,  -145,  1506,  1565,  1147,    57,   804,    60,
    1365,   177,   840,    78,  1478,  1571,   463,   226,   618,    95,
      78,   299,   262,  1484,  1485,  1158,  1486,  1655,  1161,    40,
     495,    41,   617,   203,  -366,   215,    17,   703,   704,   413,
      60,  -367,  -416,    17,   415,   650,  1577,    60,   223,   376,
     302,   396,   397,    12,   377,    96,    93,   682,   718,  1366,
     139,   609,    41,   249,  1428,  -602,  1600,  -366,  1590,  1189,
    1190,  -366,   131,    74,  -367,    94,   963,   379,  -367,   140,
     644,   109,    28,   677,  1447,  1119,   421,   424,    23,   297,
     766,  1428,   149,    10,   523,   351,    92,   989,   990,   422,
     425,   223,    74,   320,    30,  -366,    74,  1173,   298,   651,
    -602,  -602,  -367,  1429,   409,   954,   249,  1635,   412,  1050,
     596,   697,  1021,   137,   351,   653,  -602,  1235,  1634,   262,
     473,   476,    34,    97,   112,   113,   740,   365,   525,  1240,
    1537,    60,   740,    78,   434,   132,   133,    78,   407,  1662,
     224,   225,  1051,   203,   215,   110,  1052,   522,   223,   129,
     130,   518,   634,   111,   521,   597,   700,   163,   694,   524,
      60,   211,   622,  1261,    60,  1263,   141,  1580,  1581,   217,
     218,  -296,  -583,   497,   500,    16,   114,   115,   770,   164,
    1053,   497,   224,   448,   180,   685,   715,  1408,  1663,  1227,
     203,   652,  1176,   500,   129,   130,  1595,    22,    61,    28,
    1444,   132,   133,   179,   594,   595,    25,   825,   622,    10,
      11,   822,   500,    14,   248,   887,  1149,  -583,   191,    16,
     226,   178,   185,  1280,   738,   888,   189,   992,   772,   773,
     724,   223,   223,    18,   131,    19,  1296,  1297,   889,   223,
     226,    22,   740,  -583,    28,  1630,   132,   133,   793,   226,
      25,   223,   622,   825,   469,   181,  1121,   351,   380,    28,
      42,   132,   133,   883,    61,    93,   226,   937,   761,   299,
     223,   993,   519,  -143,   177,   623,   767,    94,    28,   884,
     994,   995,   190,  1077,    94,   624,    74,   798,  -583,   487,
     351,    42,   382,   351,    20,   625,   351,   626,   627,   470,
     351,   831,   831,   831,   831,   988,   769,   705,   885,   782,
     706,   141,   245,   351,   609,   596,   996,   520,  -121,  1498,
      17,  -303,   709,   351,   247,  -627,   351,   654,   682,   696,
     301,   790,   921,   697,   698,   960,   839,   297,   639,  1035,
     797,  1037,   139,   959,   362,   695,  1041,   302,   396,   397,
      12,  -121,   364,   957,    60,  -121,   644,   643,   378,   413,
     597,   298,   415,   740,   569,   374,  -303,  -303,   815,    74,
    -627,  -627,   203,   381,   796,   740,   522,   922,   923,   566,
     694,   567,  -296,   640,   530,    23,  -627,   738,   622,  -121,
      17,   383,   253,   223,  -416,   696,   566,   693,   567,   262,
     320,    30,   939,   750,   751,  -144,   403,   898,  -601,   740,
      78,   740,   900,   816,   129,   130,   141,   302,    10,    11,
      12,  1285,  -416,  -416,   157,  -296,   394,   485,   486,    34,
     124,   427,   351,   825,   223,    74,   435,    60,   412,  1095,
    -119,   971,    17,   976,   977,   573,   211,  -305,   497,   191,
     249,   203,   899,  -601,  -601,    23,   883,   901,   365,   203,
     902,  1000,   253,   693,  1025,  1001,   132,   133,   647,  -601,
     320,    30,   884,  -119,   129,   130,   803,  -119,   223,  -622,
    1269,  1271,  1083,  1084,   513,  1085,   201,   305,   977,  1054,
     524,    93,  -305,  -305,  1003,    -8,   694,   166,   782,    34,
    1194,   885,  1407,    60,   449,   903,   223,   453,  -299,  1026,
      94,  -119,  1196,   591,   592,   593,   594,   595,   365,    97,
     112,   113,  1033,   667,   668,   669,   132,   133,   793,   514,
     793,   450,   299,   160,  1055,  1059,  1069,   826,   793,   465,
     157,   157,   157,   466,    61,  1195,    61,  1060,   905,   908,
     254,   696,   211,   503,    61,   526,   302,  1197,   696,    12,
     694,   351,   351,   528,   351,   527,   694,   798,   529,   798,
    1198,   223,   114,   115,  1172,   129,   130,   798,   537,  1271,
     493,   494,  1191,   434,    20,   546,   157,  1508,  1361,  1363,
    1614,   368,   372,    91,    23,    10,    11,  1367,  1048,  1049,
     297,  1242,   547,  1230,  1231,  1232,   201,   548,  1080,   428,
     429,   790,    92,   790,   549,  1199,   129,   130,   203,   693,
     797,   790,  1046,   430,   550,    28,   693,   132,   133,   569,
     797,  1241,  1509,   431,   351,  1615,   705,   706,    34,  1123,
    1405,  1450,    90,   612,   709,   432,   658,   132,   133,   160,
     160,   160,   141,   201,   796,    91,   796,   203,   974,   203,
     203,   662,   796,  1431,   796,    93,    28,   696,   132,   133,
     831,   661,   226,  1432,    92,  1479,   694,  1027,  1028,   226,
     738,   664,   887,  1641,    94,   665,    90,  1281,  1282,   666,
    1284,  -305,   888,   678,   262,   160,   129,   130,   226,  -184,
    1256,  1257,  1258,    91,   203,   889,  -305,   598,  1019,   679,
    -305,  1480,    92,   141,  -184,    74,  -184,    74,   694,   258,
     831,   351,    92,    94,   694,    74,  -305,   707,   118,   772,
     773,   696,  1092,  1093,  1094,   693,    -7,   696,  -305,  -305,
    1473,  -305,  -305,   813,   711,   685,   599,   600,   132,   133,
      93,   601,   602,   603,   604,   775,   803,   733,   803,   485,
     716,   757,   826,  1066,  1073,   762,   803,   738,    17,    94,
     807,  -305,  -305,    10,    11,  1200,   493,   717,  1496,    28,
     831,   121,   122,    60,  1059,    60,   808,  -305,   814,   809,
     351,   422,   425,    60,   217,   218,  1060,   694,   817,   693,
      16,  1237,  1238,   434,   -53,   693,   810,  1288,   -53,   694,
     818,   258,   835,   560,   793,  1426,  1427,   365,   503,   -53,
     422,   425,    22,   485,  1531,   132,   133,   837,  1252,   838,
      61,    25,   722,  1254,   840,   201,   434,  1042,   302,   129,
     130,    12,   895,   694,    93,   694,   897,   696,   914,   905,
     908,   696,   103,   798,   916,   149,   493,  1532,   485,  1536,
     117,   918,   943,    94,  1244,   942,   953,   157,   157,   157,
    1246,  1247,   952,   831,  1244,  1249,    23,   956,  1247,   958,
      17,    22,  1043,   253,  -416,   966,   351,   967,   980,   696,
    -299,   320,    30,  1178,  1179,   696,   455,   790,  1031,   986,
     987,   747,  1007,   235,  1008,  1412,   797,  -831,  1009,   694,
     747,  1023,  -416,  -416,   201,   693,  -416,  1014,   226,   693,
      34,  1030,   201,   697,  1586,  1034,  1038,  -141,  1096,   258,
    1109,   255,    10,    11,  1036,  1458,   694,  1463,   696,  1001,
     796,  1460,  1101,  1102,  1103,   226,  1104,  1097,  1108,   732,
    1112,   226,  1115,  1128,  1098,   434,  1132,   693,  1348,    20,
    1099,  1130,   390,   693,  1100,   738,  1131,  1105,   696,  1106,
    1111,  1113,   826,  1340,    10,    11,   160,   160,   160,  1133,
     696,  1347,    28,  1114,   132,   133,   418,   129,   130,  1142,
    1140,   793,   226,   118,   119,   120,  1380,  1381,  1221,  1390,
    1391,    74,  1393,  1141,  1148,  1151,   693,    61,  1222,  1152,
    1157,  1167,  1066,  1164,   696,  1170,   696,  1171,   365,  1193,
    1223,   560,  1216,  1656,   560,  1339,   132,   133,   828,  1226,
     798,  1245,  1250,   118,   119,   120,   693,    28,  1251,   132,
     133,   560,   803,  1255,    28,  1259,   121,   122,   693,  1272,
     254,  1274,  1275,   531,   560,   384,   385,   386,   855,  1264,
    1265,   694,  1276,   532,   413,   415,  1266,  1267,  1287,    60,
     226,  1279,  1283,   522,   790,  1295,   504,   506,   905,   908,
     696,   201,   693,   797,   693,   878,   121,   122,   223,   516,
    1289,  1201,   894,  1348,  1290,  1291,  1457,  1294,  1457,  1301,
     387,   211,  1298,  1348,  1311,  1303,  1304,   696,   388,   389,
    1348,   530,   525,  1360,   462,  1369,  1347,   796,  1340,   831,
     201,  1370,   201,   201,  1373,  1340,  1347,  1377,  1576,    74,
    -664,  1476,  1477,  1347,  1303,  1304,   696,  1399,    97,   112,
     113,   515,  1400,   412,   422,   425,  1027,  1028,   693,  1406,
    1410,  1411,    97,    98,    99,  1420,   227,   228,   229,   552,
    1339,  1056,  1057,    11,    12,  1421,  1423,   201,  1430,  1422,
    1339,  1439,  1440,  1441,  1453,   693,    23,  1339,    74,  1455,
      20,  1471,  1468,  1492,  1515,   230,    97,    98,    99,   705,
     706,   114,   115,  1482,  1483,  1516,   709,    60,  1493,    23,
    1628,   660,  1494,    28,   693,   100,   101,   231,  1512,  1495,
     670,  1389,    28,  1500,    29,    30,  1389,  1520,  1236,   803,
    1058,  1522,   377,   660,  1529,  1523,  1065,  1552,   195,  1530,
    1416,  1417,   696,  1554,  1543,  1544,  1545,    28,   196,   100,
     101,   102,  1562,    34,  1572,  1573,    60,  1588,  1597,  1604,
     197,  1598,   232,   233,   234,  1609,  1610,   694,   142,   142,
    1606,   158,  1622,  1558,    74,  1626,   495,  1632,  1348,  1348,
    1558,  1633,   226,  1348,    74,    10,    11,  1636,  1639,  1643,
    1644,    74,  1648,  1340,  1653,   214,  1657,   222,  1340,   351,
    1658,  1347,  1347,   239,  1578,  1579,  1347,  1660,   223,  1665,
     693,  1666,     2,     9,   129,   130,    12,     7,   694,  1589,
     444,  1512,   203,  1461,   203,  1348,  1527,   162,   955,   365,
     714,   226,  1174,   443,  1348,  1627,  1070,   132,   133,   441,
    1340,    20,    60,  1512,  1312,  1339,  1339,   505,  1347,  1340,
    1339,    23,    60,   771,   129,  1392,   361,  1347,   410,    60,
    1558,   524,  1511,  1664,    28,  1409,    29,    30,  1166,   157,
    1611,  1165,  1006,   536,   508,  1629,  1371,  1233,  1253,   142,
     151,  1126,  1072,   945,   142,  1348,   155,   158,   158,   158,
     152,  1394,  1339,  1163,   882,    34,   619,   392,   365,   488,
    1340,  1339,   153,  1512,  1612,  1466,   132,   133,  1347,  1357,
    1601,  1650,   157,  1642,   214,  1649,  1215,   848,   560,   260,
     452,    97,   112,   113,   724,  1348,  1647,  1472,     0,     0,
     524,   472,   472,   481,     0,     0,  1416,  1417,   696,     0,
    1340,     0,     0,   260,   299,     0,     0,   222,  1347,    74,
      74,   299,  1339,     0,    74,   498,   222,     0,     0,     0,
       0,   896,     9,   129,   130,    12,     0,     0,   750,   751,
       0,     0,   260,     0,   114,   115,   116,     0,   160,   730,
      97,    98,    99,   260,     0,  1065,   736,     0,     0,   696,
      20,     0,  1339,     0,     0,     0,    74,   142,     0,     0,
      23,     0,     0,   423,   426,    74,   693,     0,     9,    10,
      11,    12,   297,    28,    15,    29,    30,    60,    60,   297,
       0,   160,    60,     0,     0,   365,     0,     0,  1228,    32,
     962,   299,     0,   100,   101,   203,    20,     0,     0,    33,
       0,   979,   260,     0,    34,     0,    23,     0,   155,     0,
       0,    35,   622,   823,     0,     0,    74,   693,     0,    28,
       0,    29,    30,     0,    60,     0,     0,   158,     0,     0,
       0,     0,   848,    60,     0,   968,     0,   260,     0,   157,
     157,   157,     0,     0,     0,   969,   544,   545,     0,     0,
      34,     0,     0,     0,     0,   625,    74,   970,   627,   297,
       0,   260,   553,     0,     0,   554,   555,     0,   157,   157,
     157,   565,     0,   876,     0,   570,   747,     0,   877,     0,
       0,     0,   747,   611,    60,     0,   129,   130,     0,     0,
       0,   521,     0,     0,   631,   635,   638,     0,     0,     0,
       0,     0,     0,   214,   222,    10,    11,     0,     0,    14,
      15,    97,   416,   417,     0,    16,   934,   142,   129,   130,
     142,     0,     0,   747,    60,     0,   158,   158,   158,    18,
       0,    19,   142,     0,     0,     0,    28,    22,   132,   133,
       0,     0,   562,     0,  1388,    20,    25,     0,   160,   160,
     160,     0,   531,   260,     0,    28,     0,   132,   133,   605,
       0,   622,   532,   560,   114,   101,     0,   261,    28,   472,
     132,   133,   472,     0,   481,   481,   481,   160,   160,   160,
     452,     0,     0,     0,   623,     0,   472,   498,   222,     0,
       0,   452,     0,   606,   624,   498,     0,     0,     0,     0,
       0,   747,     0,     0,   625,     0,   626,   627,   452,     0,
    -579,   260,     0,  -579,     0,     0,  1401,  1402,  1403,  1404,
     384,   385,   386,     0,     0,    97,    98,    99,    97,   112,
     113,     0,     0,     0,     0,   158,     0,     0,   158,     0,
       0,     0,   423,   708,   436,   201,     0,   201,   918,     9,
      10,    11,    12,   158,   158,   158,   670,     0,    10,    11,
    -579,     0,  -579,  -579,  -579,     0,     0,     0,   158,   962,
       0,    28,     0,   388,   389,  -579,   471,  -579,   100,   101,
       0,   114,   115,     0,  1443,    20,     0,    23,     0,   490,
     423,   426,     0,  -579,  -579,   553,   554,     0,     0,     0,
      28,   622,    29,    30,   260,     0,   194,     0,    28,  -579,
     132,   133,     0,   341,     0,   341,   195,   341,     0,   904,
     904,   157,   911,     0,  1501,     0,   196,     0,     0,   930,
     260,    34,     0,     0,  1502,     0,     0,     0,   197,     0,
       0,     0,     0,     0,   625,     0,  1503,   627,     0,   222,
     562,     0,     0,   562,     0,  1116,  1117,     0,     0,  1497,
       0,  1122,     0,   341,   341,   118,   772,   773,     0,   423,
     836,   216,   217,   218,     0,  1134,     0,  1135,    16,  1136,
       0,     0,     0,   562,     0,     0,     0,     0,   214,     0,
     222,   239,   157,   157,   157,    20,  1521,     0,     0,     0,
      22,     0,     0,   747,     0,     0,     0,     0,     0,    25,
      97,   112,   113,     0,     0,  1270,     0,   260,   121,   122,
       0,     0,     9,    10,    11,    12,     0,     0,  1169,     0,
     160,     0,     0,   260,   222,   973,     0,   631,   635,     0,
     638,     0,     0,     0,   929,     0,   472,   472,   481,   481,
     481,     0,   747,     0,   472,     0,     0,     0,   201,     0,
      23,  1556,   498,  1524,   115,   452,   622,   855,  1556,     0,
       0,     0,  1192,    28,     0,    29,    30,     0,     9,    10,
     252,    12,   635,     0,     0,     0,     0,   560,   613,   968,
     302,   396,   397,    12,   214,   614,    97,   112,   113,   969,
       0,   160,   160,   160,    34,     0,     0,  1317,     0,   625,
       0,   970,   627,  1270,     0,     0,    23,     0,     0,     0,
       0,   158,     0,   253,     0,     0,     0,     0,    23,     0,
       0,    29,    30,     0,     0,   615,  1056,  1057,    11,    12,
       0,    28,     0,   320,    30,   551,     0,     0,  1556,  1526,
     115,     0,   260,     0,     0,   254,   302,   129,   130,    12,
      34,     0,    15,     0,   423,   708,   758,  1631,     0,     0,
       0,   764,   616,     0,    23,   635,     0,   371,   373,     0,
       0,     0,     0,   341,    20,     0,     0,    28,  1646,    29,
      30,     0,     0,     0,    23,  1058,   805,   855,     0,     0,
     622,   904,   811,   195,   904,     0,     0,    28,     0,   320,
      30,     0,     0,   196,   819,   820,   904,   821,    34,     0,
    1150,  1150,   930,  1153,     0,   197,     0,     0,     0,     0,
       0,  1129,     0,  1154,     0,     0,   929,     0,    34,  1445,
    1446,     0,     0,   625,     0,  1155,   627,     0,  1137,     0,
       0,     0,     0,     0,     0,  1137,     0,     0,     0,   239,
       0,     0,   553,   554,  1177,  1177,  1183,     0,     0,     0,
       0,  1313,     0,  1314,  1137,  1315,     0,     0,     0,     0,
     302,   396,   397,    12,     0,   727,   731,     0,   118,   772,
     773,     0,   774,   731,     0,     0,     0,   129,   130,     0,
       0,   217,   218,     0,     0,     0,     0,    16,     0,  1183,
       0,     0,   919,   920,     0,   775,     0,   919,    23,     0,
       0,     0,   776,  1224,  1224,  1224,   341,     0,   260,    22,
     260,    28,  1507,   320,    30,     0,   423,   836,    25,    28,
     622,   121,   122,     0,   452,   452,     0,    28,     0,   132,
     133,     0,     0,     0,  1525,  1528,     0,     0,     0,   341,
     731,     0,    34,   623,     0,     0,     0,     0,     0,    10,
      11,   452,   260,   624,   248,  1415,   452,     0,     0,     0,
       0,   155,     0,   625,     0,   633,   627,     0,     0,     0,
       0,     0,   341,     0,   727,     0,    20,   852,   853,   564,
     857,   858,   859,   860,   861,   862,   863,   864,   865,   866,
     867,   868,   869,   870,   871,   872,   873,   874,   875,    28,
     731,   132,   133,     0,  1213,   731,     0,     0,     0,   216,
     217,   218,     0,  1574,     0,  1221,    16,   129,   130,  1029,
       0,   496,   217,   218,     0,  1222,     0,     0,    16,  1150,
    1150,   930,     0,    20,     0,     0,   731,  1223,    22,     0,
       0,     0,     0,   731,   260,    20,     0,    25,  1286,     0,
      22,     0,   690,     0,  1177,  1177,  1302,  1302,  1183,    25,
     622,     0,   701,  1177,     0,   947,   949,    28,     0,   132,
     133,     0,     0,     0,  1137,     0,  1088,     0,  1090,     0,
       0,   341,     0,   623,     0,  1302,  1302,  1183,     9,    10,
      11,    12,     0,   624,   248,     0,     0,  1224,  1224,  1224,
       0,  1137,     0,   625,     0,   626,   627,  1137,   589,   590,
     591,   592,   593,   594,   595,     0,    20,     0,   737,   452,
     452,     0,   452,   452,     0,   452,    23,   553,   554,   727,
       0,     0,   622,   260,     0,     0,     0,     0,     0,    28,
       0,    29,    30,     0,     0,   423,   708,   216,   217,   218,
    1124,  1125,     0,  1127,    16,   968,     0,     0,     0,     0,
       0,     0,   260,     0,     0,   969,     0,     0,     0,     0,
      34,    20,   423,   426,     0,   625,    22,   970,   627,  1177,
    1177,  1302,  1302,  1183,  1146,    25,  1177,   824,     0,     0,
     827,     0,  1044,     0,   829,   830,   832,   833,   834,     0,
     940,   423,  1359,     0,     0,     0,     0,   564,     0,     0,
     341,   341,     0,   341,     0,     0,     0,     0,     0,     0,
     851,     0,     0,   214,   222,   260,  1137,     0,   731,     0,
       0,     0,    97,   112,   113,  1187,   227,   228,   229,   587,
     588,   589,   590,   591,   592,   593,   594,   595,     0,     0,
    1107,     0,     0,     0,   452,   452,     0,   565,   129,   130,
      20,     0,   217,   218,     0,   230,     0,     0,    16,     0,
       0,     0,     0,     0,   910,     0,     0,   641,    10,    11,
      12,   910,   731,   731,     0,   114,   115,   727,   731,     0,
      22,     0,  1504,  1504,     0,  1504,     0,   423,   708,    25,
       0,   622,   731,     0,   731,  1234,   731,     0,    28,     0,
     132,   133,   310,   642,     0,    23,     0,  1239,     0,     0,
       0,     0,     0,     0,   623,     0,     0,     0,    28,     0,
     132,   133,     0,     0,   624,     0,     0,     0,   481,     0,
       0,     0,     0,     0,   625,  1162,   626,   627,     0,     9,
     129,   130,    12,     0,     0,   731,     0,   452,   452,   452,
       0,     0,    82,     0,     0,     0,     0,     0,     0,     0,
     341,     0,   106,     0,     0,     0,     0,  1504,  1504,  1553,
       0,     0,   135,  1188,     0,     0,     0,    23,   146,   146,
     690,   146,     0,    82,   253,   260,     0,     0,     0,   731,
      82,     0,    29,    30,  1292,     0,     0,     0,     0,   481,
     481,   481,     0,   205,     0,    82,   731,   452,   452,     0,
       0,     0,     0,   240,     0,     0,   254,     0,  1137,     0,
     106,    34,     0,    10,    11,     0,     0,    14,    15,     0,
       0,   264,   106,    16,     0,     0,     0,     0,     0,  1310,
       0,   553,   554,  1213,   737,     0,     0,    18,     0,    19,
     737,  1243,     0,     0,   106,    22,     0,     0,     0,  1032,
       0,     0,     0,     0,    25,     0,   691,  1137,     0,    10,
      11,     0,     0,    28,   521,   132,   133,     0,   452,     0,
       0,     0,   135,     0,    82,     0,     0,     0,   146,   146,
       0,     0,     0,   414,   146,     0,    20,   146,   146,   146,
    1081,   727,   727,   729,     0,  1273,  1086,     0,  1397,     0,
     729,   881,  1398,    82,     0,   423,  1359,    82,  1118,    28,
       0,   132,   133,   205,    82,   341,     0,     0,     0,    10,
      11,     0,   691,     0,    15,  1221,     0,     0,     0,     0,
       0,   205,   205,   205,     0,  1222,     0,  1414,     0,     0,
       0,     0,     0,     0,   851,     0,    20,  1223,     0,     0,
     737,  1419,     0,     0,   910,     0,     0,     0,     0,     0,
     205,     0,     0,     0,     0,     0,     0,   729,     0,    28,
       0,   132,   133,     0,     0,     0,     0,   507,   731,     0,
     731,     0,   731,     0,     0,  1221,   106,     0,     0,     0,
     727,     0,   690,     0,  1175,  1222,     0,   146,   910,   727,
     727,     0,  1143,     0,  1144,     0,     0,  1223,   727,     0,
       0,     0,     0,     0,     0,     0,  1474,     0,     0,     0,
    1475,     0,     0,     0,  1378,  1379,     0,   729,     0,     0,
       0,     0,   729,   474,   477,   106,   533,     0,     0,     0,
       0,   910,  1490,  1491,     0,     0,     0,     0,     0,     0,
       0,   727,     0,     0,  1218,  1382,  1383,    11,    12,     0,
       0,     0,     0,   729,  1229,     0,     0,     0,     0,     0,
     729,   737,   302,   129,   130,    12,     0,     0,   691,     0,
     106,     0,   731,   737,   620,   691,   533,   533,   636,     0,
       0,     0,     0,    23,     0,     0,     0,    82,     0,     0,
      20,     0,     0,     0,     0,     0,    28,     0,    29,    30,
      23,  1438,     0,     0,  1384,     0,   622,   737,     0,   737,
       0,     0,   195,    28,     0,   320,    30,     0,     0,     0,
       0,   135,   196,     0,     0,     0,     0,    34,     0,  1153,
     106,     0,   205,   106,   197,     0,     0,  1278,     0,  1154,
       0,   727,     0,     0,    34,   906,   909,   146,     0,   625,
     146,  1155,   627,     0,     0,     0,     0,  1481,     0,     0,
       0,     0,   146,  1260,     0,  1262,     0,     0,     0,     0,
      82,     0,     0,   910,     0,     0,     0,     0,     0,   727,
       0,     0,     0,     0,   691,     0,     9,    10,    11,    12,
    -388,    10,    11,  -388,  -388,    14,   248,     0,   205,   205,
     910,    16,   205,     0,   205,   205,   205,   755,     0,     0,
       0,   205,     0,     0,     0,    18,   205,    19,  -388,   205,
       0,  1293,     0,    22,    23,     0,     0,     0,  -388,   910,
       0,   253,    25,     0,   622,   731,    82,     0,     0,    29,
      30,    28,     0,   132,   133,   729,     0,     0,   691,     0,
       0,     0,  1541,  1542,   691,     0,     0,   623,     0,     9,
     129,   130,    12,   254,     0,    15,     0,   624,    34,     0,
       0,     0,  -388,   106,   106,   106,   106,   625,     0,   626,
     627,     0,     0,     0,     0,     0,     0,    20,     0,     0,
    1569,     0,   302,    10,    11,    12,     0,    23,     0,   729,
     729,   748,     0,     0,   749,   729,   474,   477,     0,  1372,
      28,     0,    29,    30,  1376,     0,     0,     0,   765,   729,
    1583,   729,     0,   729,     0,   910,    32,     0,     0,     0,
      23,     0,     0,   106,     0,   533,    33,   253,     0,     0,
       0,    34,     0,     0,     0,   320,    30,   620,    35,   533,
     533,     0,   636,     0,     0,     0,     0,     0,     0,   931,
       0,     0,     0,   933,   691,     0,     0,  1413,   691,   254,
       0,     0,   729,     0,    34,     0,     0,     0,   205,     0,
       0,     0,     0,  1218,     0,     9,   129,   130,    12,     0,
       0,   248,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   135,     0,     0,     0,   691,     0,     0,   135,
       0,     0,   691,    20,     0,     0,   729,   205,   975,   205,
     205,   240,   636,    23,   727,     0,     0,  1138,     0,     0,
    1139,     0,     0,   729,     0,     0,    28,     0,    29,    30,
       0,     0,  1145,     0,     0,     0,   906,   909,  1382,   129,
     130,    12,    32,     0,     0,   691,     0,     0,     0,     0,
       0,     0,    33,     0,   205,     0,     0,    34,   975,     0,
       0,     0,  1488,  1489,    35,     0,   205,   205,   755,   755,
     755,     0,     0,     0,   205,   691,    23,     0,     0,  1499,
     906,   909,     0,     0,     0,     0,     0,   691,     0,    28,
       0,    29,    30,     0,     0,     0,     0,  1384,     0,     0,
       0,     0,     0,   135,     0,    32,    82,     0,    82,     0,
       0,   910,     0,  1067,    82,    33,    82,     0,     0,     0,
      34,   691,   106,   691,     0,     0,     0,    35,   106,     9,
      10,    11,    12,     0,     0,   533,   533,   533,     0,  1539,
    1540,     0,     0,   564,     0,     0,     0,   533,     0,     0,
       0,     0,     0,     0,     0,  1550,  1551,    20,     0,     0,
       0,     0,   690,     0,     0,     0,     0,    23,   748,   749,
     474,   477,     9,    10,    11,    12,   765,     0,    15,     0,
      28,     0,    29,    30,     0,     0,     0,   691,     0,     0,
       0,     0,     0,     0,     0,     0,   478,     0,     0,     0,
      20,     0,     0,     0,     0,   729,   479,   729,     0,   729,
      23,    34,     0,     0,   691,     0,   622,     0,   480,     0,
     533,   533,     0,    28,   533,    29,    30,   533,     0,     0,
       0,     0,   106,     0,     0,     0,   533,     0,   106,  1180,
     931,   931,   931,   691,     0,     0,   533,     0,  1156,  1181,
     302,    10,    11,    12,    34,     0,     0,     0,     0,   625,
       0,  1182,   627,     0,     0,   906,   909,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     106,     0,   106,     0,   205,   205,  1185,    85,    23,     0,
    1138,  1139,   906,   909,     0,   253,     0,   108,     0,  1145,
       0,     0,     0,   320,    30,     0,   128,   136,     0,   729,
       0,     0,     0,   147,   147,     0,   147,     0,    85,     0,
       0,   906,   909,   129,   130,    85,     0,   524,    15,  1185,
       0,     0,    34,     0,     0,     0,     0,     0,   147,   691,
      85,     0,   106,   755,   755,   755,     0,     0,   241,     0,
      20,     0,     0,     0,     0,   250,     0,     0,     0,   106,
       0,     0,  1067,     0,     0,     0,   622,   250,     0,     0,
       0,   106,     0,    28,     0,   132,   133,     0,     0,     0,
       0,     0,     0,     0,  1248,     0,   474,   477,     0,   623,
       0,     0,    82,     0,     0,     0,     0,     0,     0,   624,
       0,     0,     0,     0,     0,   106,     0,   106,     0,   625,
       0,   626,   627,     0,     0,  1138,  1139,   906,   909,    85,
       0,     0,  1145,   147,   147,     0,     0,     0,     0,   147,
       0,     0,   147,   147,   147,   106,     0,     0,     0,     0,
     533,   533,     0,   533,     0,   748,   749,   765,    85,     0,
       0,     0,    85,     0,     0,     0,     0,     0,   147,    85,
       0,     0,     0,     0,     0,     0,   533,     0,     0,   533,
     533,   636,   729,     0,     0,     0,   147,   147,   147,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   592,
     593,   594,   595,   205,   205,   205,   205,   205,  1185,   755,
       0,     0,     0,   205,     0,   147,     9,   129,   130,    12,
       0,     0,    15,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   595,  1185,  1185,  1185,  1138,  1139,
       0,  1145,     0,     0,    20,   691,     0,   755,   755,   755,
     755,     0,   147,     0,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,     0,    29,
      30,   205,     0,     0,     0,     0,   146,     0,     0,    82,
       0,     0,     0,   151,     0,     0,     0,     0,     0,     0,
     250,   147,     0,   152,     0,     0,   691,     0,    34,     0,
       0,     0,     0,     0,     0,   153,   748,   749,   474,   477,
       0,     0,     0,     0,     0,   765,     0,     9,    10,    11,
      12,     0,     0,   906,   909,     0,     0,     0,   755,   205,
     205,   755,   755,  1418,     0,   250,   205,   474,   477,   621,
       0,   147,   147,   637,     0,    20,     0,     0,   646,   474,
     477,     0,    85,     0,     0,    23,     0,     0,     0,     0,
       0,   622,     0,     0,     0,     0,     0,     0,    28,     0,
      29,    30,   205,   975,   205,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   968,     0,   683,     0,     0,     0,
       0,   106,     0,     0,   969,   250,     0,   147,   250,    34,
       0,     0,     0,     0,   625,     0,   970,   627,     9,    10,
      11,    12,   147,     0,   521,   147,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   147,     0,     0,
       0,   748,   749,   474,   477,    85,    20,     0,   765,     0,
       0,     0,   755,   755,     0,   755,    23,     0,     0,     0,
       0,     0,   622,     0,     0,     0,     0,     0,     0,    28,
       0,    29,    30,   147,   147,     0,     0,   147,     0,   147,
     147,   147,   147,     0,     0,   968,   147,     0,     0,     0,
       0,   147,     0,     0,   147,   969,     0,     0,  1185,     0,
      34,     0,     0,     0,     0,   625,     0,   970,   627,     0,
     784,    85,     0,     0,     9,    10,    11,    12,   216,   217,
     218,     0,     0,     0,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   755,   755,  1418,
     755,     0,    20,     0,     0,     0,     0,    22,   250,   250,
     250,   250,    23,     0,   748,   749,    25,   765,   622,     0,
       0,     0,     0,     0,     0,    28,     0,    29,    30,  1185,
    1185,  1185,     0,     0,     0,     0,     0,   302,    10,    11,
      12,   968,     0,    15,     0,     0,     0,     0,     0,   755,
     106,   969,     0,     0,     0,   205,    34,     0,     0,     0,
       0,   625,     0,   970,   627,    20,     0,     0,   250,     0,
     147,     0,     0,     0,     0,    23,     0,     0,     0,     0,
       0,   622,     0,     0,   147,   147,     0,   637,    28,     0,
     320,    30,     0,     0,   932,   302,    10,    11,    12,   474,
     477,     0,     0,     0,  1305,     0,     0,   646,     0,     0,
       0,     0,     0,   147,  1306,     0,     0,     0,     0,    34,
       0,     0,     0,    20,   625,     0,  1307,   627,     0,     0,
       0,   474,   477,    23,     0,     0,     0,   683,     0,   622,
       0,     9,    10,    11,    12,   128,    28,    15,   320,    30,
       0,     0,   147,   637,   147,   147,   241,   637,     0,     0,
       0,     0,  1305,     0,     0,     0,     0,     0,     0,    20,
       0,     0,  1306,     0,     0,     0,     0,    34,     0,    23,
     784,     0,   625,     0,  1307,   627,     0,     0,     0,     0,
       0,     0,    28,     0,    29,    30,     0,     0,     0,   147,
       0,     0,     0,   637,     0,     0,     0,     0,   195,     0,
       0,   147,   147,   147,   147,   147,     0,     0,   196,   147,
       0,     0,     0,    34,     0,     0,     0,     0,     0,     0,
     197,     0,     0,   265,     0,     0,    10,    11,     0,     0,
      14,    15,     0,     0,     0,     0,    16,     0,   136,     0,
       0,    85,     0,    85,     0,     0,     0,     0,  1068,    85,
      18,    85,    19,     0,     0,     0,     0,   250,    22,     0,
     266,   267,     0,   250,     0,     0,     0,    25,     0,   268,
     147,   147,   147,     0,     0,     0,    28,     0,   132,   133,
       0,   269,   147,     0,     0,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,     0,   290,   291,   292,   293,
       0,     0,     0,    10,    11,   294,   295,    14,   248,     0,
       0,     0,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,   296,     0,     0,     0,     0,    18,     0,    19,
       0,     9,   129,   130,    12,    22,     0,   521,     0,     0,
       0,     0,     0,     0,    25,   147,   147,     0,     0,   147,
       0,     0,   147,    28,     0,   132,   133,   250,     0,    20,
       0,   147,     0,   250,     0,   932,   932,   932,     0,    23,
       0,   147,     0,   646,     0,     0,     0,     0,     0,     0,
       0,     0,    28,     0,    29,    30,     0,   785,     0,     9,
      10,   786,    12,   169,    14,    15,     0,     0,    32,     0,
      16,     0,     0,     0,     0,   250,     0,   250,    33,   147,
     147,   637,     0,    34,    18,     0,    19,    20,    21,     0,
      35,     0,    22,  -525,     0,     0,     0,    23,     0,     0,
       0,    25,   787,     0,   170,     0,     0,     0,     0,     0,
      28,     0,    29,    30,     0,     0,   788,     0,   789,     0,
       0,     0,     0,     0,   932,     0,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    33,   250,   147,   147,
     147,    34,     0,     0,     0,     0,     0,     0,    35,     0,
       0,     0,   784,     0,   250,     0,     0,  1068,     0,     0,
       0,     0,     0,     0,     0,  -525,   250,     0,   785,     0,
       9,    10,   786,    12,   169,    14,    15,     0,     0,     0,
       0,    16,     0,     0,     0,     0,     0,    85,     0,     0,
       9,    10,    11,    12,     0,    18,   248,    19,    20,    21,
     250,     0,   250,    22,  -526,     0,     0,     0,    23,     0,
       0,     0,    25,   787,     0,   170,     0,     0,    20,     0,
       0,    28,     0,    29,    30,     0,     0,   788,    23,   789,
     250,     0,     0,     0,     0,   147,   147,    32,   147,     0,
       0,    28,     0,    29,    30,     0,     0,    33,     0,     0,
       0,     0,    34,     0,     0,     0,     0,   195,     0,    35,
       0,   147,     0,     0,   147,   147,   637,   196,     0,     0,
       0,     0,    34,    10,    11,     0,  -526,    14,    15,   197,
       0,     0,     0,    16,     0,     0,     0,     0,   147,   147,
     147,   147,   147,   637,   147,     0,     0,    18,   147,    19,
       9,    10,    11,    12,   784,    22,    15,     0,     0,     9,
      10,    11,    12,     0,    25,   521,     0,     0,     0,     0,
     932,   932,   932,    28,     0,   132,   133,     0,    20,     0,
       0,     0,   147,   147,   147,   147,     0,    20,    23,     0,
       0,   784,     0,    53,     0,     0,     0,    23,     0,     0,
       0,    28,     0,    29,    30,     0,   147,     0,     0,     0,
      28,   147,    29,    30,    85,     0,     0,   478,     0,    53,
      53,     0,   154,  1517,    53,     0,   195,   479,     0,     0,
       0,    53,    34,     0,     0,     0,   196,     0,     0,   480,
       0,    34,     0,     0,    53,     0,    53,     0,   197,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147,   147,   147,   147,   147,   637,   256,
       0,   147,     0,  1518,   574,   575,   576,   577,   578,   579,
     580,   581,   582,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,  1449,     0,     0,     9,
      10,    11,    12,   216,   217,   218,     0,   147,   637,   147,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   398,   398,     0,    53,   250,    20,     0,    53,
      53,     0,    22,   256,     0,    53,     0,    23,   154,   154,
     154,    25,     0,   622,     0,   433,     0,     0,     0,     0,
      28,     0,    29,    30,    53,     0,     0,     0,    53,     0,
       0,     0,     0,     0,    53,    53,   968,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   969,   147,   147,     0,
     147,    34,    53,    53,   154,     0,   625,     0,  1013,   627,
       0,   734,   256,   302,    10,    11,    12,   169,    14,   303,
     304,   305,   735,   306,    16,     0,     0,     0,     0,     0,
       0,    53,     0,     0,     0,     0,     0,     0,    18,   307,
      19,    20,    21,   932,   308,   309,    22,     0,   310,   311,
     312,    23,   313,   314,     0,    25,     0,     0,     0,   315,
     316,   317,   318,   319,    28,     0,   320,    30,    53,     0,
       0,   322,     0,     0,     0,     0,     0,   323,     0,     0,
     324,     0,   147,   147,   637,   147,     0,     0,   325,   326,
     327,     0,     0,     0,     0,   328,   329,   330,     0,     0,
       0,     0,   331,     0,     0,     0,     9,    10,    11,    12,
       0,     0,     0,     0,   932,   932,   932,     0,  -802,     0,
     332,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   147,   250,     0,     0,   561,     0,
     147,     0,     0,     0,    23,   785,     0,     9,    10,   786,
      12,   169,    14,    15,     0,   398,     0,    28,    16,    29,
      30,     0,     0,   256,     0,     0,     0,     0,    53,     0,
       0,     0,    18,   195,    19,    20,    21,     0,     0,     0,
      22,  -528,     0,   196,     0,    23,     0,     0,    34,    25,
     787,     0,   170,     0,     0,   197,     0,     0,    28,     0,
      29,    30,   398,     0,   788,     0,   789,     9,    10,    11,
      12,     0,     0,    53,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,    53,    34,
       0,    53,     0,     0,     0,    20,    35,   433,   433,   433,
       0,     0,     0,    53,     0,    23,     0,     0,     0,     0,
       0,    53,     0,  -528,     0,     0,     0,     0,    28,     0,
      29,    30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   195,     0,     0,     0,     0,    53,
      53,     0,     0,    53,   196,   154,   154,   154,   433,    34,
       0,     0,    53,     0,     0,     0,   197,    53,     0,     0,
      53,     0,     0,   854,     0,   302,    10,    11,    12,   169,
      14,   303,   304,   305,     0,   306,    16,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,   307,    19,    20,    21,     0,   308,   309,    22,     0,
     310,   311,   312,    23,   313,   314,   561,    25,     0,   561,
       0,   315,   316,   317,   318,   319,    28,     0,   320,    30,
    1564,     0,  -792,   322,   561,   561,   561,     0,     0,   323,
       0,     0,   324,     0,     0,     0,     0,     0,     0,   561,
     325,   326,   327,     0,     0,     0,     0,   328,   329,   330,
       0,    80,     0,     0,   331,     0,     0,     0,     0,     0,
       0,   785,     0,     9,    10,   786,    12,   169,    14,    15,
       0,     0,   332,     0,    16,     0,     0,    80,    80,     0,
      80,     0,    80,     0,     0,     0,     0,   256,    18,    80,
      19,    20,    21,     0,     0,     0,    22,  -527,     0,     0,
     561,    23,    80,     0,    80,    25,   787,     0,   170,     0,
       0,     0,     0,     0,    28,     0,    29,    30,     0,    53,
     788,     0,   789,     0,     0,   302,    10,    11,    12,     0,
      32,    15,     0,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,   398,     0,    34,     0,     0,     0,     0,
     398,     0,    35,    20,     0,     0,     0,     0,    53,    53,
      53,    53,     0,    23,     0,     0,     0,     0,     0,  -527,
       0,     0,     0,     0,     0,     0,    28,     0,   320,    30,
       0,     0,     0,    80,     0,     0,     0,    80,    80,     0,
       0,     0,   752,    80,     0,     0,    80,    80,    80,     0,
       0,     0,   753,     0,     0,    53,     0,    34,     0,    53,
       0,     0,    80,     0,   754,     0,    80,    53,    53,   433,
     433,   433,    80,    80,     0,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      80,    80,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    53,     0,    53,
       0,     0,     0,     0,    53,    53,     0,    53,     0,    80,
    1546,     0,  -481,  -481,  -481,  -481,  -481,  -481,  -481,     0,
       0,  -481,     0,  -481,     0,     0,     0,     0,     0,     0,
       0,     0,   561,     0,  -481,     0,  -481,     0,     0,     0,
    -481,     0,     0,     0,     0,  -481,    80,     0,     0,     0,
    -481,     0,     0,     0,  -481,     0,  -481,     0,     0,     0,
       0,     0,     0,  -481,     0,  -481,  -481,  -481,  -481,  -481,
       0,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,     0,     0,  -481,
    -481,  -481,  -481,  -481,     0,  -481,  -481,     0,     0,     0,
       0,  1547,     0,     0,     0,     0,  -481,  -481,  -481,     0,
    -481,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   561,   561,   561,     0,     0,     0,   433,   256,     0,
       0,     0,   645,     0,     0,     0,    80,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     9,
      10,    11,    12,    13,    14,    15,     0,     0,     0,     0,
      16,     0,     0,     0,     0,    53,    53,   154,     0,     0,
       0,     0,   256,    17,    18,   161,    19,    20,    21,     0,
       0,    80,    22,     0,     0,     0,     0,    23,     0,     0,
      24,    25,    26,     0,    27,     0,    80,   206,     0,    80,
      28,     0,    29,    30,     0,     0,    31,     0,     0,     0,
    1212,    80,     0,     0,     0,     0,    32,     0,     0,    80,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,    34,     0,     0,     0,     0,     0,     0,    35,     0,
       0,     0,     0,    53,    36,     0,     0,    80,    80,     0,
       0,    80,     0,    80,    80,    80,     0,     0,     0,     0,
      80,     0,     0,     0,   256,    80,     0,     0,    80,     0,
       0,     0,     0,    53,     0,   168,     0,     9,    10,    11,
      12,   169,    14,    15,     0,    80,     0,     0,    16,     0,
       0,   161,   161,   161,     0,     0,     0,     0,     0,     0,
       0,     0,    18,     0,    19,    20,    21,     0,     0,     0,
      22,     0,     0,     0,     0,    23,     0,   206,     0,    25,
       0,     0,   170,     0,     0,     0,     0,     0,    28,     0,
      29,    30,     0,     0,     0,   206,   206,   483,     0,     0,
       0,     0,     0,     0,    32,     0,     0,   433,     0,     0,
     433,   433,   433,   256,    33,     0,     0,     0,     0,    34,
       0,     0,     0,     0,   206,     0,    35,     9,    10,    11,
      12,     0,    36,     0,    53,    53,    53,   154,   154,   154,
     433,     0,   256,     0,    53,    10,    11,     0,   169,    14,
      15,     0,     0,   735,     0,    16,   645,     0,     0,     0,
       0,     0,     0,     0,     0,    23,  1212,  1212,  1212,    18,
       0,    19,    20,     0,     0,     0,     0,    22,    28,     0,
      29,    30,     0,     0,  1456,     0,    25,    80,   622,     0,
       0,     0,     0,     0,   195,    28,     0,   132,   133,     0,
     534,     0,    53,     0,   196,     0,     0,    53,     0,    34,
      53,   623,     0,     0,     0,     0,   197,     0,     0,     0,
       0,   624,     0,     0,     0,     0,    80,    80,    80,    80,
       0,   625,     0,   626,   627,     0,     0,     0,     0,     0,
       0,   302,    10,    11,    12,     0,     0,     0,   129,   130,
     630,   630,   630,   248,     0,     0,     0,     0,     0,   433,
      53,    53,   433,   433,   433,     0,     0,    53,     0,    20,
       0,     0,     0,    80,     0,    20,     0,    80,     0,    23,
       0,     0,     0,     0,     0,    80,    80,     0,     0,     0,
       0,   622,    28,    80,   320,    30,     0,     0,    28,     0,
     132,   133,     0,    53,    53,    53,   206,    20,   752,     0,
       0,     0,     0,     0,   623,     0,     0,     0,   753,     0,
       0,     0,     0,    34,   624,    80,     0,    80,     0,     0,
     754,     0,    80,    80,   625,    80,   626,   627,     0,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   206,   206,     0,     0,   206,     0,   483,   483,
     483,   756,     0,     0,     0,   206,     0,     0,     0,     0,
     206,     0,     0,   206,     0,   302,    10,    11,    12,   169,
      14,   303,   304,   305,   735,   306,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1212,
      18,   307,    19,    20,    21,     0,   308,   309,    22,     0,
     310,   311,   312,    23,   313,   314,     0,    25,   204,   622,
       0,   315,   316,   317,   318,   319,    28,     0,   320,    30,
       0,     0,     0,   322,     0,     0,     0,     0,     0,   323,
       0,     0,   924,   259,     0,     0,   263,   645,   129,   130,
     325,   326,   925,   521,     0,     0,     0,   328,   329,   330,
       0,     0,   625,     0,   926,   627,     0,   259,     0,   367,
    1212,  1212,  1212,     0,     0,    20,     0,     0,     0,     0,
       0,     0,   332,    80,    80,    80,     0,     0,     0,   890,
       0,   622,     0,     0,     0,     0,    53,     0,    28,     0,
     132,   133,     0,   630,   630,     0,   630,     0,     0,     0,
       0,     0,     0,   630,   623,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   624,     0,     0,     0,  1214,     0,
       0,     0,   206,     0,   625,     0,   626,   627,   204,   579,
     580,   581,   582,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   204,   204,   204,     0,
       0,    80,     0,     0,     0,     0,   489,     0,     0,     0,
       0,   972,     0,   972,   972,     0,   630,     0,     0,     0,
       0,     0,     0,     0,     0,   204,     0,     0,     0,     0,
       0,    80,     0,     0,     0,     0,    10,    11,     0,   169,
      14,    15,    10,    11,   735,     0,    16,   248,     0,     0,
       0,   263,     0,     0,     0,     0,     0,     0,   972,     0,
      18,     0,    19,    20,     0,   259,     0,     0,    22,    20,
     206,   206,   756,   756,   756,     0,     0,    25,   206,   622,
       0,     0,     0,     0,     0,   622,    28,     0,   132,   133,
       0,     0,    28,     0,   132,   133,     0,     0,     0,     0,
       0,     0,  1501,     0,     0,     0,     0,     0,  1501,     0,
       0,     0,  1502,     0,     0,     0,     0,   206,  1502,     0,
       0,     0,   625,     0,  1503,   627,     0,     0,   625,     0,
    1503,   627,    80,    80,    80,    80,    80,    80,     0,   534,
     534,   534,    80,     0,     9,    10,    11,    12,   169,    14,
      15,   630,     0,     0,     0,    16,     0,   259,   263,     0,
       0,     0,     0,     0,  1214,  1214,  1214,     0,     0,    18,
       0,    19,    20,    21,     0,     0,     0,    22,     0,     0,
       0,     0,    23,     0,     0,     0,    25,     0,     0,   170,
       0,     0,     0,     0,     0,    28,     0,    29,    30,     0,
      80,     0,     0,     0,     0,    80,     0,   204,    80,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,   630,   630,    34,     0,   630,     0,
       0,   630,     0,    35,     0,     0,     0,     0,     0,    36,
     630,     0,     0,     0,   630,   630,   630,     0,     0,     0,
     630,     0,     0,     0,     0,     0,    10,    11,    80,    80,
       0,   521,     0,     0,     0,    80,     0,     0,     0,     0,
       0,     0,     0,   204,   204,     0,     0,   204,     0,   204,
     204,   204,   204,    20,     0,     0,   204,     0,   972,   972,
    1186,   204,     0,     0,   204,     0,     0,     0,     0,   622,
       0,    80,    80,    80,     0,     0,    28,     0,   132,   133,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1501,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1502,  1186,     0,     0,     0,     0,     0,     0,
       0,     0,   625,     0,  1503,   627,     0,   756,   756,   756,
       0,     0,     0,     0,     0,  1464,     0,  1320,  1321,  1322,
      12,   169,    14,   303,   304,   305,   206,   306,    16,  1323,
       0,  1324,  1325,  1326,  1327,  1328,  1329,  1330,  1331,  1332,
    1333,    17,    18,   307,    19,    20,    21,     0,   308,   309,
      22,     0,   310,   311,   312,    23,   313,   314,  1334,    25,
    1335,     0,     0,   315,   316,   317,   318,   319,    28,     0,
     320,  1336,   722,     0,  1337,   322,     0,  1214,     0,     0,
       0,   323,     0,     0,   324,     0,     0,     0,     0,     0,
       0,     0,   325,   326,   327,     0,     0,   259,   263,   328,
     329,   330,     0,     0,   890,   890,   331,   890,     0,     0,
    1338,     0,     0,   204,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1465,   332,     0,     0,     0,     0,     0,
     630,     0,     0,   630,   630,   630,     0,     0,     0,     0,
       0,     0,    10,    11,     0,     0,     0,    15,  1214,  1214,
    1214,     0,   204,     0,   204,   204,     0,   972,   972,   972,
    1186,  1186,  1186,  1308,     0,     0,     0,   972,     0,    20,
       0,     0,     0,     0,    80,   628,   628,   628,     0,     0,
       0,     0,     0,     0,     0,   622,     0,     0,     0,  1186,
    1186,  1186,    28,     0,   132,   133,     0,     0,     0,   204,
       0,   756,   756,   756,   756,     0,     0,     0,  1501,     0,
       0,   204,   204,   204,   204,   204,   489,     0,  1502,   204,
       0,     0,     0,     0,     0,   206,     0,     0,   625,     0,
    1503,   627,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   263,     0,     0,     0,     0,
       0,     0,     0,   104,     0,     0,     0,     0,   204,     0,
       0,     0,   123,   104,     0,     0,     0,     0,     0,   104,
     104,     0,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1308,   972,   972,  1308,  1308,  1308,     0,     0,
     972,     0,     9,    10,    11,    12,   207,    14,   208,     0,
       0,     0,     0,    16,   237,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,     0,    19,
      20,     0,     0,     0,     0,    22,   206,     0,   206,     0,
      23,     0,     0,     0,    25,     0,     0,     0,     0,     0,
       0,     0,     0,    28,     0,    29,    30,     0,     0,   209,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
       0,     0,     0,   391,     0,   123,     0,     0,     0,    33,
       0,     0,   104,   104,    34,     0,     0,     0,     0,   104,
     104,    35,     0,   104,   104,   104,     0,   419,   104,   104,
     104,     0,   259,   263,   259,     0,  1308,  1308,     0,  1308,
      10,    11,     0,   169,    14,    15,     0,     0,     0,     0,
      16,     0,     0,    10,    11,     0,   169,    14,    15,     0,
       0,   735,     0,    16,    18,     0,    19,    20,     0,   204,
     204,  1184,    22,     0,     0,     0,   259,    18,     0,    19,
      20,   684,   483,     0,   170,    22,     0,     0,   628,   628,
      28,   628,   132,   133,    25,     0,     0,     0,   928,     0,
       0,     0,     0,    28,     0,   132,   133,     0,     0,     0,
       0,     0,     0,     0,  1184,     0,     0,   237,   104,     0,
       0,  1308,  1308,  1308,  1308,     0,     0,     0,   204,   204,
     204,     0,     0,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,     0,     0,     0,     0,   204,     0,     0,
       0,     0,     0,   483,   483,   483,   628,     0,   628,   628,
       0,   628,     0,     0,     0,     0,     0,     0,   489,     0,
       0,     0,     0,  1308,     0,     0,     0,   104,     0,   206,
       0,     0,     0,     0,     0,     0,   785,     0,     9,    10,
     786,    12,   169,    14,    15,     0,     0,     0,     0,    16,
       0,     0,     0,   628,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,    19,    20,    21,     0,     0,
       0,    22,     0,     0,     0,   104,    23,   104,   104,     0,
      25,   787,     0,   170,     0,     0,     0,     0,     0,    28,
       0,    29,    30,     0,     0,   788,     0,   789,     0,     0,
       0,     0,     0,     0,     0,    32,     0,   259,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
      34,     0,   104,     0,     0,     0,     0,    35,   204,   204,
     204,   204,   204,  1184,   204,     0,  1309,     0,   204,     0,
       0,   104,     0,     0,     0,     0,   628,     0,   104,     0,
       0,   104,     0,     0,     0,     0,     0,     0,     0,     0,
    1184,  1184,  1184,   104,     0,     0,     0,     0,     0,     0,
       0,     0,   204,   204,   204,   204,     0,    10,    11,     0,
     169,    14,    15,     0,     0,  1585,     0,    16,     0,     0,
       0,     0,     0,     0,     0,     0,   204,     0,     0,     0,
       0,    18,     0,    19,    20,     0,     0,     0,     0,    22,
       0,     0,     0,     0,     0,     0,     0,     0,    25,   628,
     628,     0,     0,   628,     0,     0,   628,    28,     0,   132,
     133,     0,     0,     0,   104,   628,   777,     0,     0,   928,
     928,   928,     0,     0,     0,   628,     0,     0,     0,     0,
       0,     0,     0,   204,   204,   204,   204,   204,  1184,     0,
     104,   204,     0,     0,     0,     8,     0,     9,    10,    11,
      12,    13,    14,    15,     0,     0,     0,     0,    16,     0,
       0,     0,     0,   628,   628,   628,     0,     0,     0,     0,
       0,     0,    18,     0,    19,    20,     0,   204,     0,   204,
      22,     0,     0,     0,     0,    23,     0,     0,     0,    25,
       0,     0,   440,     0,     0,     0,     0,     0,    28,     0,
      29,    30,     0,     0,    31,     0,     0,     0,   928,     0,
       0,     0,     0,     0,    32,     0,   104,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,   104,   104,    34,
     104,   104,     0,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   204,   204,  1309,
     204,     0,     0,     0,     9,    10,    11,    12,   169,    14,
      15,     0,     0,   735,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
       0,    19,    20,   104,     0,     0,     0,    22,     0,     0,
     104,   123,    23,  1184,     0,     0,    25,     0,   622,     0,
       0,     0,   237,     0,     0,    28,     0,    29,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1180,     0,     0,     0,     0,   777,     0,     0,     0,
       0,  1181,   204,   204,  1184,   204,    34,     0,     0,     0,
       0,   625,     0,  1182,   627,   628,     0,     0,   628,   628,
     628,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1184,  1184,  1184,     0,     0,     0,
       0,     0,   628,   628,   628,   628,   628,   628,   628,     0,
       0,     0,   628,     0,   204,     0,     0,     0,     0,     0,
     204,   777,     0,     0,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   928,   928,   928,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   595,     0,   104,   104,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   104,   302,
      10,    11,    12,   169,    14,    15,     0,     0,   735,     0,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,     0,    19,    20,     0,     0,
       0,     0,    22,     0,     0,     0,     0,    23,     0,     0,
       0,    25,     0,   622,     0,     0,     0,     0,     0,     0,
      28,     0,   320,    30,     0,     0,     0,   628,   628,   628,
     628,   628,   628,     0,     0,   628,  1153,     0,     0,     0,
       0,   104,   104,     0,     0,   104,  1154,     0,   104,     0,
       0,    34,     0,     0,     0,     0,   625,   104,  1155,   627,
       0,     0,     0,     0,     0,     0,     0,   104,  1319,     0,
    1320,  1321,  1322,    12,   169,    14,   303,   304,   305,     0,
     306,    16,  1323,     0,  1324,  1325,  1326,  1327,  1328,  1329,
    1330,  1331,  1332,  1333,    17,    18,   307,    19,    20,    21,
       0,   308,   309,    22,     0,   310,   311,   312,    23,   313,
     314,  1334,    25,  1335,     0,     0,   315,   316,   317,   318,
     319,    28,     0,   320,  1336,   722,     0,  1337,   322,     0,
       0,     0,     0,     0,   323,     0,     0,   324,     0,     0,
       0,   628,   628,     0,   628,   325,   326,   327,     0,     0,
       0,     0,   328,   329,   330,     0,     0,     0,     0,   331,
       0,     0,     0,  1338,   302,    10,    11,    12,   169,    14,
      15,     0,     0,   735,     0,    16,     0,   332,   777,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
       0,    19,    20,     0,     0,     0,     0,    22,     0,     0,
       0,     0,    23,     0,     0,   104,    25,     0,   622,     0,
       0,     0,     0,     0,     0,    28,     0,   320,    30,     0,
       0,     0,     0,     0,     0,     0,   628,   628,   628,   628,
       0,  1305,     0,    10,    11,     0,   207,    14,   208,     0,
       0,  1306,     0,    16,     0,     0,    34,     0,     0,     0,
       0,   625,     0,  1307,   627,     0,     0,    18,     0,    19,
      20,   104,   104,     0,   104,    22,     0,     0,     0,     0,
       0,     0,     0,     0,    25,     0,     0,     0,   628,     0,
       0,     0,     0,    28,     0,   132,   133,   104,     0,     0,
     104,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   556,     0,   302,    10,    11,    12,
     169,    14,   303,   304,   305,   735,   306,    16,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     777,    18,   307,    19,    20,    21,     0,   308,   309,    22,
       0,   310,   311,   312,    23,   313,   314,     0,    25,     0,
     622,     0,   315,   316,   317,   318,   319,    28,     0,   320,
      30,  -313,     0,     0,   322,     0,     0,   777,     0,     0,
     323,     0,     0,   924,     0,     0,     0,     0,     0,     0,
       0,   325,   326,   925,     0,   104,     0,   104,   328,   329,
     330,     0,     0,   625,     0,   926,   627,   556,     0,     9,
      10,    11,    12,   169,    14,   303,   304,   305,   735,   306,
      16,     0,     0,   332,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,   307,    19,    20,    21,     0,
     308,   309,    22,     0,   310,   311,   312,    23,   313,   314,
       0,    25,     0,   622,     0,   315,   316,   317,   318,   319,
      28,     0,    29,    30,  -313,     0,     0,   322,     0,     0,
       0,     0,     0,   323,     0,     0,  1209,     0,     0,     0,
       0,     0,     0,     0,   325,   326,  1210,     0,     0,     0,
       0,   328,   329,   330,     0,     0,   625,     0,  1211,   627,
     725,     0,   842,   843,   844,    12,     0,    14,   538,   304,
     305,     0,   306,    16,     0,     0,   332,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,   307,    19,
       0,    21,     0,   308,   309,    22,     0,   310,   311,   312,
      23,   313,   314,     0,    25,     0,     0,     0,   315,   316,
     317,   318,   319,    28,     0,   845,   846,   726,     0,     0,
     322,     0,     0,     0,     0,     0,   323,     0,     0,   324,
       0,     0,     0,     0,     0,     0,     0,   325,   326,   327,
       0,     0,     0,     0,   328,   329,   330,     0,     0,     0,
       0,   331,   847,   556,     0,   302,    10,    11,    12,     0,
      14,   303,   304,   305,     0,   306,    16,     0,  1005,   332,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,   307,    19,    20,    21,     0,   308,   309,    22,     0,
     310,   311,   312,    23,   313,   314,     0,    25,     0,     0,
       0,   315,   316,   317,   318,   319,    28,     0,   320,    30,
    -313,     0,     0,   322,     0,     0,     0,     0,     0,   323,
       0,     0,   557,     0,     0,     0,     0,     0,     0,     0,
     325,   326,   558,     0,     0,     0,     0,   328,   329,   330,
       0,     0,     0,   725,   559,   842,   843,   844,    12,     0,
      14,   538,   304,   305,     0,   306,    16,     0,     0,     0,
       0,     0,   332,     0,     0,     0,     0,     0,     0,     0,
      18,   307,    19,     0,    21,     0,   308,   309,    22,     0,
     310,   311,   312,    23,   313,   314,     0,    25,     0,     0,
       0,   315,   316,   317,   318,   319,    28,     0,   845,   846,
     726,     0,     0,   322,     0,     0,     0,     0,     0,   323,
       0,     0,   324,     0,     0,     0,     0,     0,     0,     0,
     325,   326,   327,     0,     0,     0,     0,   328,   329,   330,
       0,     0,     0,     0,   331,   847,   725,     0,   842,   843,
     844,    12,     0,    14,   538,   304,   305,     0,   306,    16,
       0,     0,   332,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,   307,    19,     0,    21,     0,   308,
     309,    22,     0,   310,   311,   312,    23,   313,   314,     0,
      25,     0,     0,     0,   315,   316,   317,   318,   319,    28,
       0,   845,   846,   726,     0,     0,   322,     0,     0,     0,
       0,     0,   323,     0,     0,   324,     0,     0,     0,     0,
       0,     0,     0,   325,   326,   327,     0,     0,     0,     0,
     328,   329,   330,     0,     0,     0,   725,   331,   842,   843,
     844,    12,     0,    14,   538,   304,   305,     0,   306,    16,
       0,     0,     0,     0,  -485,   332,     0,     0,     0,     0,
       0,     0,     0,    18,   307,    19,     0,    21,     0,   308,
     309,    22,     0,   310,   311,   312,    23,   313,   314,     0,
      25,     0,     0,     0,   315,   316,   317,   318,   319,    28,
       0,   845,   846,   726,     0,     0,   322,     0,     0,     0,
       0,     0,   323,     0,     0,   324,     0,     0,     0,     0,
       0,     0,     0,   325,   326,   327,     0,     0,     0,     0,
     328,   329,   330,     0,     0,     0,   725,   331,   302,    10,
      11,    12,     0,    14,   538,   304,   305,     0,   306,    16,
       0,     0,     0,     0,  1358,   332,     0,     0,     0,     0,
       0,     0,     0,    18,   307,    19,     0,    21,     0,   308,
     309,    22,     0,   310,   311,   312,    23,   313,   314,     0,
      25,     0,     0,     0,   315,   316,   317,   318,   319,    28,
       0,   320,    30,   726,     0,     0,   322,     0,     0,     0,
       0,     0,   323,     0,     0,   324,     0,     0,     0,     0,
       0,     0,     0,   325,   326,   327,     0,     0,     0,     0,
     328,   329,   330,     0,     0,     0,     0,   331,     0,     0,
     556,     0,     9,    10,    11,    12,  1362,    14,   303,   304,
     305,     0,   306,    16,     0,   332,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,   307,    19,
      20,    21,     0,   308,   309,    22,     0,   310,   311,   312,
      23,   313,   314,     0,    25,     0,     0,     0,   315,   316,
     317,   318,   319,    28,     0,    29,    30,  -313,     0,     0,
     322,     0,     0,     0,     0,     0,   323,     0,     0,  1533,
       0,     0,     0,     0,     0,     0,     0,   325,   326,  1534,
       0,     0,     0,     0,   328,   329,   330,     0,     0,     0,
     725,  1535,   302,    10,    11,    12,     0,    14,   538,   304,
     305,     0,   306,    16,     0,     0,     0,     0,     0,   332,
       0,     0,     0,     0,     0,     0,     0,    18,   307,    19,
       0,    21,     0,   308,   309,    22,     0,   310,   311,   312,
      23,   313,   314,     0,    25,     0,     0,     0,   315,   316,
     317,   318,   319,    28,     0,   320,    30,   726,     0,     0,
     322,     0,     0,     0,     0,     0,   323,     0,     0,   324,
       0,     0,     0,     0,     0,     0,     0,   325,   326,   327,
       0,     0,     0,     0,   328,   329,   330,     0,     0,     0,
     854,   331,   302,    10,    11,    12,     0,    14,   538,   304,
     305,     0,   306,    16,     0,     0,     0,     0,     0,   332,
       0,     0,     0,     0,     0,     0,     0,    18,   307,    19,
       0,    21,     0,   308,   309,    22,     0,   310,   311,   312,
      23,   313,   314,     0,    25,     0,     0,     0,   315,   316,
     317,   318,   319,    28,     0,   320,    30,     0,     0,     0,
     322,  -792,     0,     0,     0,     0,   323,     0,     0,   324,
       0,     0,     0,     0,     0,     0,     0,   325,   326,   327,
       0,     0,     0,     0,   328,   329,   330,     0,     0,     0,
    1617,   331,   302,    10,    11,    12,     0,    14,   303,   304,
     305,     0,   306,    16,     0,     0,     0,     0,     0,   332,
       0,     0,     0,     0,     0,     0,     0,    18,   307,    19,
       0,    21,     0,   308,   309,    22,     0,   310,   311,   312,
      23,   313,   314,     0,    25,     0,     0,     0,   315,   316,
     317,   318,   319,    28,     0,   320,    30,     0,     0,  -197,
     322,     0,     0,     0,     0,     0,   323,     0,     0,   324,
       0,     0,     0,     0,     0,     0,     0,   325,   326,   327,
       0,     0,     0,     0,   328,   329,   330,     0,     0,     0,
     854,   331,   302,    10,    11,    12,     0,    14,   538,   304,
     305,     0,   306,    16,     0,     0,     0,     0,     0,   332,
       0,     0,     0,     0,     0,     0,     0,    18,   307,    19,
       0,    21,     0,   308,   309,    22,     0,   310,   311,   312,
      23,   313,   314,     0,    25,     0,     0,     0,   315,   316,
     317,   318,   319,    28,     0,   320,    30,     0,     0,     0,
     322,     0,     0,     0,     0,     0,   323,     0,     0,   324,
       0,     0,     0,     0,     0,     0,     0,   325,   326,   327,
       0,     0,     0,     0,   328,   329,   330,     0,     0,     0,
     946,   331,   302,    10,    11,    12,     0,    14,   538,   304,
     305,     0,   306,    16,     0,     0,     0,  -792,     0,   332,
       0,     0,     0,     0,     0,     0,     0,    18,   307,    19,
       0,    21,     0,   308,   309,    22,     0,   310,   311,   312,
      23,   313,   314,     0,    25,     0,     0,     0,   315,   316,
     317,   318,   319,    28,     0,   320,    30,     0,     0,     0,
     322,     0,     0,     0,     0,     0,   323,     0,     0,   324,
       0,     0,     0,     0,     0,     0,     0,   325,   326,   327,
       0,     0,     0,     0,   328,   329,   330,     0,     0,     0,
     948,   331,   302,    10,    11,    12,     0,    14,   538,   304,
     305,     0,   306,    16,     0,     0,     0,     0,     0,   332,
       0,     0,     0,     0,     0,     0,     0,    18,   307,    19,
       0,    21,     0,   308,   309,    22,     0,   310,   311,   312,
      23,   313,   314,     0,    25,     0,     0,     0,   315,   316,
     317,   318,   319,    28,     0,   320,    30,     0,     0,     0,
     322,     0,     0,     0,     0,     0,   323,     0,     0,   324,
       0,     0,     0,     0,     0,     0,     0,   325,   326,   327,
       0,     0,     0,     0,   328,   329,   330,     0,     0,     0,
    1582,   331,   302,    10,    11,    12,     0,    14,   538,   304,
     305,     0,   306,    16,     0,     0,     0,     0,     0,   332,
       0,     0,     0,     0,     0,     0,     0,    18,   307,    19,
       0,    21,     0,   308,   309,    22,     0,   310,   311,   312,
      23,   313,   314,     0,    25,     0,     0,     0,   315,   316,
     317,   318,   319,    28,     0,   320,    30,     0,     0,     0,
     322,     0,     0,     0,     0,     0,   323,     0,     0,   324,
       0,     0,     0,     0,     0,     0,     0,   325,   326,   327,
       0,     0,     0,     0,   328,   329,   330,   302,    10,    11,
      12,   331,    14,   538,   304,   305,     0,   306,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   332,
       0,     0,    18,   307,    19,     0,    21,     0,   308,   309,
      22,     0,   310,   311,   312,    23,   313,   314,     0,    25,
       0,     0,     0,   315,   316,   317,   318,   319,    28,     0,
     320,    30,     0,     0,     0,   322,     0,     0,     0,     0,
       0,   323,     0,     0,   324,     0,     0,     0,     0,     0,
       0,     0,   325,   326,   327,     0,     0,     0,     0,   328,
     329,   330,     0,     0,     0,     0,   331,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   592,
     593,   594,   595,     0,   332,   893,  1320,  1321,  1322,    12,
     169,    14,   303,   304,   305,     0,   306,    16,  1323,     0,
    1324,  1325,  1326,  1327,  1328,  1329,  1330,  1331,  1332,  1333,
      17,    18,   307,    19,    20,    21,     0,   308,   309,    22,
       0,   310,   311,   312,    23,   313,   314,  1334,    25,  1335,
       0,     0,   315,   316,   317,   318,   319,    28,     0,   320,
    1336,   722,     0,  1337,   322,     0,     0,     0,     0,     0,
     323,     0,     0,   324,     0,     0,     0,     0,     0,     0,
       0,   325,   326,   327,     0,     0,     0,     0,   328,   329,
     330,     0,     0,     0,     0,   331,     0,     0,     0,  1338,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1469,   332,  1320,  1321,  1322,    12,   169,    14,
     303,   304,   305,     0,   306,    16,  1323,     0,  1324,  1325,
    1326,  1327,  1328,  1329,  1330,  1331,  1332,  1333,    17,    18,
     307,    19,    20,    21,     0,   308,   309,    22,     0,   310,
     311,   312,    23,   313,   314,  1334,    25,  1335,     0,     0,
     315,   316,   317,   318,   319,    28,     0,   320,  1336,   722,
       0,  1337,   322,     0,     0,     0,     0,     0,   323,     0,
       0,   324,     0,     0,     0,     0,     0,     0,     0,   325,
     326,   327,     0,     0,     0,     0,   328,   329,   330,     0,
       0,     0,     0,   331,     0,     0,     0,  1338,  1320,  1321,
    1322,    12,   169,    14,   303,   304,   305,     0,   306,    16,
    1323,   332,  1324,  1325,  1326,  1327,  1328,  1329,  1330,  1331,
    1332,  1333,    17,    18,   307,    19,    20,    21,     0,   308,
     309,    22,     0,   310,   311,   312,    23,   313,   314,  1334,
      25,  1335,     0,     0,   315,   316,   317,   318,   319,    28,
       0,   320,  1336,  1591,     0,  1337,   322,     0,     0,     0,
       0,     0,   323,     0,     0,   324,     0,     0,     0,     0,
       0,     0,     0,   325,   326,   327,     0,     0,     0,     0,
     328,   329,   330,     0,     0,     0,     0,   331,     0,     0,
       0,  1338,  1320,  1321,  1322,    12,   169,    14,   303,   304,
     305,     0,   306,    16,  1323,   332,  1324,  1325,  1326,  1327,
    1328,  1329,  1330,  1331,  1332,  1333,    17,    18,   307,    19,
      20,    21,     0,   308,   309,    22,     0,   310,   311,   312,
      23,   313,   314,  1334,    25,  1335,     0,     0,   315,   316,
     317,   318,   319,    28,     0,   320,  1336,     0,     0,  1337,
     322,     0,     0,     0,     0,     0,   323,     0,     0,   324,
       0,     0,     0,     0,     0,     0,     0,   325,   326,   327,
       0,     0,     0,     0,   328,   329,   330,     0,     0,     0,
       0,   331,     0,     0,     0,  1338,     9,    10,    11,    12,
     169,    14,   303,   304,   305,   735,   306,    16,     0,   332,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,   307,    19,    20,    21,     0,   308,   309,    22,
       0,   310,   311,   312,    23,   313,   314,     0,    25,     0,
     622,     0,   315,   316,   317,   318,   319,    28,     0,    29,
      30,     0,     0,     0,   322,     0,     0,     0,     0,     0,
     323,     0,     0,  1209,     0,     0,     0,     0,     0,     0,
       0,   325,   326,  1210,     0,     0,     0,     0,   328,   329,
     330,     0,     0,   625,     0,  1211,   627,   302,    10,    11,
      12,     0,    14,   303,   304,   305,     0,   306,    16,     0,
       0,     0,     0,   332,     0,     0,     0,     0,     0,     0,
       0,     0,    18,   307,    19,    20,    21,     0,   308,   309,
      22,     0,   310,   311,   312,    23,   313,   314,     0,    25,
       0,   622,     0,   315,   316,   317,   318,   319,    28,     0,
     320,    30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   323,     0,     0,   924,     0,     0,     0,     0,     0,
       0,     0,   325,   326,   925,     0,     0,     0,     0,   328,
     329,   330,     0,     0,   625,     0,   926,   627,     9,    10,
      11,    12,     0,    14,   303,   304,   305,     0,   306,    16,
       0,     0,     0,     0,   332,     0,     0,     0,     0,     0,
       0,     0,     0,    18,   307,    19,    20,    21,     0,   308,
     309,    22,     0,   310,   311,   312,    23,   313,   314,     0,
      25,     0,   622,     0,   315,   316,   317,   318,   319,    28,
       0,    29,    30,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   323,     0,     0,  1209,     0,     0,     0,     0,
       0,     0,     0,   325,   326,  1210,     0,     0,     0,     0,
     328,   329,   330,     0,     0,   625,     0,  1211,   627,   302,
      10,    11,    12,     0,    14,   538,   304,   305,     0,   306,
      16,     0,     0,     0,     0,   332,     0,     0,     0,     0,
       0,     0,     0,     0,    18,   307,    19,    20,    21,     0,
     308,   309,    22,     0,   310,   311,   312,    23,   313,   314,
       0,    25,     0,     0,     0,   315,   316,   317,   318,   319,
      28,     0,   320,    30,     0,     0,     0,   322,     0,     0,
       0,     0,     0,   323,     0,     0,   557,     0,     0,     0,
       0,     0,     0,     0,   325,   326,   558,     0,     0,     0,
       0,   328,   329,   330,   302,    10,    11,    12,   559,    14,
     538,   304,   305,     0,   306,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   332,     0,     0,    18,
     307,    19,     0,    21,     0,   308,   309,    22,     0,   310,
     311,   312,    23,   313,   314,     0,    25,     0,     0,     0,
     315,   316,   317,   318,   319,    28,     0,   320,    30,     0,
       0,  1442,   322,     0,     0,     0,     0,     0,   323,     0,
       0,   324,     0,     0,     0,     0,     0,     0,     0,   325,
     326,   327,     0,     0,     0,     0,   328,   329,   330,     0,
       0,     0,     0,   331,   302,    10,    11,    12,   169,    14,
     303,   304,   305,     0,   306,    16,     0,     0,     0,     0,
       0,   332,     0,     0,     0,     0,     0,     0,     0,    18,
     307,    19,    20,    21,     0,   308,   309,    22,     0,   310,
     311,   312,    23,   313,   314,     0,    25,     0,     0,     0,
     315,   316,   317,   318,   319,    28,     0,   320,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   323,     0,
       0,   324,     0,     0,     0,     0,     0,     0,     0,   325,
     326,   327,     0,     0,     0,     0,   328,   329,   330,     9,
      10,    11,    12,   331,    14,   538,   304,   305,     0,   306,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   332,     0,     0,    18,   307,    19,    20,    21,     0,
     308,   309,    22,     0,   310,   311,   312,    23,   313,   314,
       0,    25,     0,     0,     0,   315,   316,   317,   318,   319,
      28,     0,    29,    30,     0,     0,     0,   322,     0,     0,
       0,     0,     0,   323,     0,     0,  1533,     0,     0,     0,
       0,     0,     0,     0,   325,   326,  1534,     0,     0,     0,
       0,   328,   329,   330,   302,    10,    11,    12,  1535,    14,
     303,   304,   305,     0,   306,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   332,     0,     0,    18,
     307,    19,     0,    21,     0,   308,   309,    22,     0,   310,
     311,   312,    23,   313,   314,     0,    25,     0,     0,     0,
     315,   316,   317,   318,   319,    28,     0,   320,   321,     0,
       0,     0,   322,     0,     0,     0,     0,     0,   323,     0,
       0,   324,     0,     0,     0,     0,     0,     0,     0,   325,
     326,   327,     0,     0,     0,     0,   328,   329,   330,   302,
      10,    11,    12,   331,    14,   303,   304,   305,     0,   306,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   332,     0,     0,    18,   307,    19,     0,    21,     0,
     308,   309,    22,     0,   310,   311,   312,    23,   313,   314,
       0,    25,     0,     0,     0,   315,   316,   317,   318,   319,
      28,     0,   320,    30,     0,     0,     0,   322,     0,     0,
       0,     0,     0,   323,     0,     0,   324,     0,     0,     0,
       0,     0,     0,     0,   325,   326,   327,     0,     0,     0,
       0,   328,   329,   330,   302,    10,    11,    12,   331,    14,
     538,   304,   305,     0,   306,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   332,     0,     0,    18,
     307,    19,     0,    21,     0,   308,   309,    22,     0,   310,
     311,   312,    23,   313,   314,     0,    25,     0,     0,     0,
     315,   316,   317,   318,   319,    28,     0,   320,    30,     0,
       0,     0,   322,     0,     0,     0,     0,     0,   323,     0,
       0,   324,     0,     0,     0,     0,     0,     0,     0,   325,
     326,   327,     0,     0,     0,     0,   328,   329,   330,   302,
      10,    11,    12,   331,    14,   538,   304,   305,     0,   306,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   332,     0,     0,    18,   307,    19,     0,    21,     0,
     308,   309,    22,     0,   310,   311,   312,    23,   313,   314,
       0,    25,     0,     0,     0,   315,   316,   317,   318,   319,
      28,     0,   320,    30,   571,     0,     0,     0,     0,     0,
       0,     0,     0,   323,     0,     0,   324,     0,     0,     0,
       0,     0,     0,     0,   325,   326,   327,     0,     0,     0,
       0,   328,   329,   330,   302,    10,    11,    12,   572,    14,
     538,   304,   305,     0,   306,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   332,     0,     0,    18,
     307,    19,     0,    21,     0,   308,   309,    22,     0,   310,
     311,   312,    23,   313,   314,     0,    25,     0,     0,     0,
     315,   316,   317,   318,   319,    28,     0,   320,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   323,     0,
       0,   324,     0,     0,     0,     0,     0,     0,     0,   325,
     326,   327,     0,     0,     0,     0,   328,   329,   330,     0,
       0,     0,     0,   331,   610,   302,    10,    11,    12,     0,
      14,   538,   304,   305,     0,   306,    16,     0,     0,     0,
       0,   332,     0,     0,     0,     0,     0,     0,     0,     0,
      18,   307,    19,    20,    21,     0,   308,   309,    22,     0,
     310,   311,   312,    23,   313,   314,     0,    25,     0,     0,
       0,   315,   316,   317,   318,   319,    28,     0,   320,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   323,
       0,     0,   557,     0,     0,     0,     0,     0,     0,     0,
     325,   326,   558,     0,     0,     0,     0,   328,   329,   330,
    1168,    10,    11,    12,   559,    14,   538,   304,   305,     0,
     306,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   332,     0,     0,    18,   307,    19,     0,    21,
       0,   308,   309,    22,     0,   310,   311,   312,    23,   313,
     314,     0,    25,     0,     0,     0,   315,   316,   317,   318,
     319,    28,     0,   320,    30,     0,     0,     0,   322,     0,
       0,     0,     0,     0,   323,     0,     0,   324,     0,     0,
       0,     0,     0,     0,     0,   325,   326,   327,     0,     0,
       0,     0,   328,   329,   330,     9,    10,    11,    12,   331,
      14,   303,   304,   305,     0,   306,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   332,     0,     0,
      18,   307,    19,    20,    21,     0,   308,   309,    22,     0,
     310,   311,   312,    23,   313,   314,     0,    25,     0,     0,
       0,   315,   316,   317,   318,   319,    28,     0,    29,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   323,
       0,     0,  1533,     0,     0,     0,     0,     0,     0,     0,
     325,   326,  1534,     0,     0,     0,     0,   328,   329,   330,
     302,    10,    11,    12,  1535,    14,   538,   304,   305,     0,
     306,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   332,     0,     0,    18,   307,    19,     0,    21,
       0,   308,   309,    22,     0,   310,   311,   312,    23,   313,
     314,     0,    25,     0,     0,     0,   315,   316,   317,   318,
     319,    28,     0,   320,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   323,     0,     0,   324,     0,     0,
       0,     0,     0,     0,     0,   325,   326,   327,     0,     0,
       0,     0,   328,   329,   330,   302,    10,    11,    12,   539,
      14,   538,   304,   305,     0,   306,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   332,     0,     0,
      18,   307,    19,     0,    21,     0,   308,   309,    22,     0,
     310,   311,   312,    23,   313,   314,     0,    25,     0,     0,
       0,   315,   316,   317,   318,   319,    28,     0,   320,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   323,
       0,     0,   324,     0,     0,     0,     0,     0,     0,     0,
     325,   326,   327,     0,     0,     0,     0,   328,   329,   330,
     302,    10,    11,    12,   542,    14,   538,   304,   305,     0,
     306,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   332,     0,     0,    18,   307,    19,     0,    21,
       0,   308,   309,    22,     0,   310,   311,   312,    23,   313,
     314,     0,    25,     0,     0,     0,   315,   316,   317,   318,
     319,    28,     0,   320,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   323,     0,     0,   324,     0,     0,
       0,     0,     0,     0,     0,   325,   326,   327,     0,     0,
       0,     0,   328,   329,   330,     0,     0,     0,     0,   331,
       9,    10,    11,    12,   169,    14,    15,     0,     0,  1018,
       0,    16,     0,     0,     0,     0,     0,   332,     0,     0,
       0,     0,     0,     0,     0,    18,     0,    19,    20,     0,
       0,     0,     0,    22,     0,     0,     0,     0,    23,     0,
       0,     0,    25,     0,     0,     0,     0,     0,     0,     0,
       0,    28,     0,    29,    30,     0,     0,     0,  1056,    10,
     786,    12,   207,    14,   208,     0,     0,    32,     0,    16,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,    34,    18,     0,    19,    20,     0,     0,    35,
       0,    22,     0,     0,     0,     0,    23,     0,     0,     0,
      25,     0,     0,     0,     0,     0,     0,     0,     0,    28,
       0,    29,    30,     0,     0,     0,     0,  1058,     9,    10,
      11,    12,   207,    14,   208,    32,     0,     0,     0,    16,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
      34,     0,     0,    18,     0,    19,    20,    35,     0,     0,
       0,    22,     0,     0,     0,     0,    23,     0,     0,     0,
      25,     0,     0,     0,     0,     0,     0,     0,     0,    28,
       0,    29,    30,     0,     0,  1459,     9,    10,    11,    12,
     169,    14,    15,     0,     0,    32,     0,    16,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
      34,    18,     0,    19,    20,     0,     0,    35,     0,    22,
       0,     0,     0,     0,    23,     0,     0,     0,    25,     0,
       0,     0,     0,     0,     0,     0,     0,    28,     0,    29,
      30,     0,     0,     0,     9,    10,    11,    12,   207,    14,
     208,     0,     0,    32,     0,    16,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,    34,    18,
       0,    19,    20,     0,     0,    35,     0,    22,     0,     0,
       0,     0,    23,     0,     0,     0,    25,     0,     0,     0,
       0,     0,     0,     0,     0,    28,     0,    29,    30,     9,
      10,    11,    12,   216,   217,   218,     0,     0,     0,     0,
      16,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,    34,    20,     0,     0,
       0,     0,    22,    35,     0,     0,     0,    23,     0,     0,
       0,    25,     0,   622,     0,     0,     0,     0,     0,     0,
      28,     0,    29,    30,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   195,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   196,     0,     0,     0,
       0,    34,     0,     0,     0,     0,     0,     0,  1462,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   574,   575,   576,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   592,
     593,   594,   595,     0,     0,     0,     0,  1268,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   663,     0,     0,  1605,   574,   575,   576,   577,
     578,   579,   580,   581,   582,   583,   584,   585,   586,   587,
     588,   589,   590,   591,   592,   593,   594,   595,  1599,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   574,   575,   576,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   592,
     593,   594,   595,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,     0,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   581,   582,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   592,   593,   594,   595
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1444)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       6,   163,   151,   152,   211,   351,   177,    92,   176,    94,
     128,    25,   178,   404,   404,     6,   720,   509,    16,   702,
     487,   357,   357,     6,    44,   404,    44,     6,   136,   253,
     470,    37,   882,    86,   569,   135,   136,    59,    44,   211,
     606,    61,   249,    44,   649,   375,    37,    57,   220,   135,
     245,   158,   126,    59,    37,   442,   141,  1424,    37,  1339,
     790,    44,   792,   306,   307,    44,    82,     6,    74,   695,
     800,  1514,    64,  1515,   462,  1349,     6,    44,    56,    44,
      86,    33,  1356,    11,    90,    11,    92,    85,    94,    59,
      11,   298,    37,    48,  1516,     1,   339,     0,    37,   704,
    1237,  1238,     9,   109,   110,    44,    54,    37,    58,    60,
     108,    73,     1,    59,    44,     7,   138,  1254,  1561,    60,
     806,    54,    38,    78,     1,    73,   812,    59,    12,    62,
     146,     0,   138,   357,   140,   141,    62,    62,    54,   109,
      73,   219,   220,    58,   351,    37,    12,    62,    98,   167,
     142,   171,    58,   171,    61,   138,   178,   109,   109,    33,
     627,   167,   108,    12,   109,   171,   158,   177,   109,    58,
     171,     6,   178,    62,  1596,    59,   108,   184,    62,   157,
     108,    58,   108,   108,   167,    62,    82,   108,   171,   205,
      27,   211,   171,    59,    31,   541,    62,    32,    33,   219,
     220,    47,    37,  1645,   171,    59,   171,    96,   138,    44,
      59,    62,     6,    62,    63,   358,   359,    63,  1661,    96,
      74,   495,   214,    60,   202,    54,    63,   719,     6,   249,
     222,     0,   171,    62,  1601,  1515,   922,   167,   512,     6,
      59,   171,   108,    37,  1381,  1519,    92,   239,   348,    73,
      44,    86,   250,  1390,  1391,   938,  1393,   108,   941,    37,
     215,     6,   348,    57,    25,    59,    27,   410,   411,   143,
      37,    25,   109,    27,   148,   360,  1538,    44,   298,    58,
       3,     4,     5,     6,    63,    48,    54,   395,   450,   108,
      54,   344,    37,   299,    60,    47,  1570,    58,  1560,   982,
     983,    62,    44,   138,    58,    73,   685,    54,    62,    73,
     646,    92,    54,   387,    56,   881,   151,   152,    41,    86,
     492,    60,   196,     4,     5,   331,    73,   714,   715,   478,
     479,   351,   167,    56,    57,    96,   171,   963,   344,   361,
      92,    93,    96,   109,   138,   675,   352,  1621,   142,    25,
      47,   742,   742,    73,   360,   361,   108,  1043,  1620,   357,
     195,   196,    85,     3,     4,     5,   806,    48,   264,  1055,
     109,   138,   812,   167,   481,    56,    57,   171,   361,    59,
      59,    60,    58,   177,   178,    92,    62,   261,   408,     4,
       5,   615,   738,    92,     9,    92,   406,    92,   404,    80,
     167,   407,    47,  1089,   171,  1091,    73,  1544,  1545,     8,
       9,   108,    47,   491,   492,    14,    56,    57,   503,    60,
      96,   499,    59,    60,   444,   404,   444,  1277,   108,  1034,
     224,   361,   967,   511,     4,     5,  1564,    36,   444,    54,
      80,    56,    57,   444,    83,    84,    45,    92,    47,     4,
       5,   536,   530,     8,     9,    70,   923,    92,    93,    14,
     452,   444,    25,   108,   470,    80,    60,     3,     4,     5,
     457,   491,   492,    28,    44,    30,  1159,  1160,    93,   499,
     472,    36,   922,    47,    54,  1613,    56,    57,   510,   481,
      45,   511,    47,    92,    47,   107,   884,   503,    54,    54,
       6,    56,    57,    47,   510,    54,   498,   650,   485,   344,
     530,    47,    47,    62,   444,    70,   493,    73,    54,    63,
      56,    57,    54,  1253,    73,    80,   361,   510,    92,    93,
     536,    37,    54,   539,    31,    90,   542,    92,    93,    92,
     546,   547,   548,   549,   550,   713,   501,   421,    92,  1041,
     424,    73,    62,   559,   607,    47,    92,    92,    25,  1409,
      27,    47,   436,   569,    58,    47,   572,   361,   676,   404,
      73,   510,    47,   964,   964,   683,   563,   344,    47,   774,
     510,   776,    54,   683,   109,   964,   781,     3,     4,     5,
       6,    58,    58,   678,   361,    62,   932,   932,    54,   473,
      92,   607,   476,  1043,    59,    92,    92,    93,    47,   444,
      92,    93,   406,    54,   510,  1055,   490,    92,    93,    74,
     626,    76,   108,    92,   831,    41,   108,   633,    47,    96,
      27,    54,    48,   653,    31,   470,    74,   404,    76,   637,
      56,    57,   652,   478,   479,    62,    74,    47,    47,  1089,
     444,  1091,    47,    92,     4,     5,    73,     3,     4,     5,
       6,  1128,    59,    60,    35,   108,   784,    59,    60,    85,
     684,   108,   678,    92,   694,   510,   108,   444,   472,   822,
      25,   691,    27,   693,   694,   928,   692,    47,   766,    93,
     696,   485,    92,    92,    93,    41,    47,    92,    48,   493,
      47,  1193,    48,   470,    47,   719,    56,    57,   932,   108,
      56,    57,    63,    58,     4,     5,   510,    62,   738,   108,
    1108,  1109,   807,   808,    47,   810,    57,    11,   738,    47,
      80,    54,    92,    93,   721,   109,   742,    98,  1230,    85,
      47,    92,    93,   510,    60,    92,   766,     3,   108,    92,
      73,    96,    47,    80,    81,    82,    83,    84,    48,     3,
       4,     5,   769,     7,     8,     9,    56,    57,   790,    92,
     792,    92,   607,    35,    92,   797,   798,  1123,   800,    60,
     151,   152,   153,   111,   790,    92,   792,   797,   623,   624,
      80,   626,   798,    73,   800,    93,     3,    92,   633,     6,
     806,   807,   808,    62,   810,    93,   812,   790,   111,   792,
      47,   831,    56,    57,   957,     4,     5,   800,    92,  1207,
      59,    60,   990,   930,    31,    92,   197,    47,  1216,  1217,
      47,   109,   110,    54,    41,     4,     5,  1225,   793,   794,
     607,    62,    73,  1038,  1039,  1040,   177,    73,   803,    56,
      57,   790,    73,   792,    73,    92,     4,     5,   652,   626,
     790,   800,   792,    70,    73,    54,   633,    56,    57,    59,
     800,    62,    92,    80,   880,    92,   750,   751,    85,   885,
    1268,    62,    73,    11,   758,    92,   109,    56,    57,   151,
     152,   153,    73,   224,   790,    54,   792,   691,   692,   693,
     694,    59,   798,    62,   800,    54,    54,   742,    56,    57,
     916,   108,   904,    62,    73,    62,   922,   752,   753,   911,
     926,   108,    70,  1627,    73,   108,    73,  1124,  1125,   108,
    1127,    12,    80,    73,   932,   197,     4,     5,   930,    59,
    1083,  1084,  1085,    54,   738,    93,    27,    47,   742,    54,
      31,    62,    73,    73,    74,   790,    76,   792,   964,   975,
     966,   967,    73,    73,   970,   800,    47,   108,     3,     4,
       5,   806,   819,   820,   821,   742,   109,   812,    59,    60,
    1368,    62,    63,    47,   109,   964,    86,    87,    56,    57,
      54,    91,    92,    93,    94,    30,   790,   111,   792,    59,
      60,   108,  1348,   797,   798,   111,   800,  1013,    27,    73,
      73,    92,    93,     4,     5,  1002,    59,    60,  1406,    54,
    1026,    56,    57,   790,  1046,   792,    73,   108,    92,    54,
    1036,  1180,  1181,   800,     8,     9,  1046,  1043,   111,   806,
      14,  1048,  1049,  1150,    59,   812,    73,  1132,    63,  1055,
     111,  1067,   108,   331,  1076,    59,    60,    48,    73,    74,
    1209,  1210,    36,    59,    60,    56,    57,   108,  1075,   108,
    1076,    45,    58,  1080,   108,   406,  1183,    47,     3,     4,
       5,     6,    54,  1089,    54,  1091,     8,   922,   111,   924,
     925,   926,    16,  1076,    92,   969,    59,    60,    59,    60,
      24,    47,    59,    73,  1059,    63,   109,   478,   479,   480,
    1065,  1066,    92,  1119,  1069,  1070,    41,    54,  1073,    60,
      27,    36,    92,    48,    31,    63,  1132,    63,    63,   964,
     108,    56,    57,   968,   969,   970,    62,  1076,   111,   108,
      60,   472,   108,    67,   108,  1288,  1076,    63,   108,  1155,
     481,    63,    59,    60,   485,   922,    63,   108,  1150,   926,
      85,    63,   493,  1554,  1554,    74,    59,    62,   108,  1185,
      59,  1067,     4,     5,    92,  1346,  1182,  1348,  1013,  1193,
    1076,  1347,    74,    74,    74,  1177,    74,   108,    62,   467,
      62,  1183,   111,    93,   108,  1302,    73,   964,  1204,    31,
     108,   111,   126,   970,   108,  1211,    85,   108,  1043,   108,
     108,   108,  1558,  1204,     4,     5,   478,   479,   480,    47,
    1055,  1204,    54,   108,    56,    57,   150,     4,     5,   111,
     108,  1253,  1224,     3,     4,     5,  1243,  1244,    70,  1246,
    1247,  1076,  1249,   108,   111,   108,  1013,  1253,    80,   108,
     108,   108,  1046,   109,  1089,   109,  1091,    60,    48,    59,
      92,   539,    63,  1651,   542,  1204,    56,    57,   546,    63,
    1253,    59,    59,     3,     4,     5,  1043,    54,    62,    56,
      57,   559,  1076,   108,    54,   108,    56,    57,  1055,   109,
      80,   109,   108,    70,   572,     3,     4,     5,   576,    92,
      92,  1307,   108,    80,  1178,  1179,    92,    92,     8,  1076,
    1302,   108,   111,  1187,  1253,   111,   240,   241,  1153,  1154,
    1155,   652,  1089,  1253,  1091,   603,    56,    57,  1348,   253,
     108,    33,   610,  1339,   108,   108,  1346,   108,  1348,   108,
      48,  1347,   109,  1349,   108,  1180,  1181,  1182,    56,    57,
    1356,  1558,  1248,   108,    63,   108,  1339,  1253,  1349,  1365,
     691,   108,   693,   694,   108,  1356,  1349,   108,  1530,  1204,
      54,  1378,  1379,  1356,  1209,  1210,  1211,   108,     3,     4,
       5,     6,   108,  1177,  1533,  1534,  1221,  1222,  1155,    62,
     111,    47,     3,     4,     5,   108,     7,     8,     9,   323,
    1339,     3,     4,     5,     6,   108,    95,   738,    62,   108,
    1349,    62,    60,    60,     9,  1182,    41,  1356,  1253,    60,
      31,   108,    16,   108,    92,    36,     3,     4,     5,  1303,
    1304,    56,    57,  1388,  1389,    92,  1310,  1204,   108,    41,
    1608,   365,   108,    54,  1211,    56,    57,    58,  1435,   108,
     374,  1245,    54,   108,    56,    57,  1250,    60,    60,  1253,
      62,    60,    63,   387,  1451,    54,   797,   111,    70,    92,
    1305,  1306,  1307,    92,  1481,  1482,  1483,    54,    80,    56,
      57,    58,    17,    85,    60,    54,  1253,   108,    60,   107,
      92,   108,   103,   104,   105,   108,   108,  1503,    32,    33,
      97,    35,    11,  1509,  1339,    60,  1461,    60,  1514,  1515,
    1516,    60,  1504,  1519,  1349,     4,     5,    92,    59,    63,
     108,  1356,    60,  1514,   108,    59,   108,    61,  1519,  1535,
      11,  1514,  1515,    67,  1541,  1542,  1519,    60,  1558,    11,
    1307,    60,     0,     3,     4,     5,     6,     3,  1554,  1559,
     172,  1538,  1346,  1347,  1348,  1561,  1449,    37,   676,    48,
     444,  1553,   964,   171,  1570,  1607,   798,    56,    57,   167,
    1561,    31,  1339,  1560,  1193,  1514,  1515,   240,  1561,  1570,
    1519,    41,  1349,   507,     4,     5,    96,  1570,   140,  1356,
    1596,    80,  1434,  1661,    54,  1278,    56,    57,   950,   970,
    1587,   945,   726,   301,   244,  1612,  1230,  1041,  1076,   143,
      70,   889,   798,   659,   148,  1621,    35,   151,   152,   153,
      80,  1250,  1561,   943,   607,    85,   348,   126,    48,   202,
    1621,  1570,    92,  1620,  1589,  1349,    56,    57,  1621,  1205,
    1575,  1641,  1013,  1627,   178,  1639,  1021,   571,   926,    82,
     184,     3,     4,     5,  1641,  1661,  1637,  1365,    -1,    -1,
      80,   195,   196,   197,    -1,    -1,  1501,  1502,  1503,    -1,
    1661,    -1,    -1,   106,  1509,    -1,    -1,   211,  1661,  1514,
    1515,  1516,  1621,    -1,  1519,   219,   220,    -1,    -1,    -1,
      -1,   615,     3,     4,     5,     6,    -1,    -1,  1533,  1534,
      -1,    -1,   135,    -1,    56,    57,    58,    -1,   970,   463,
       3,     4,     5,   146,    -1,  1046,   470,    -1,    -1,  1554,
      31,    -1,  1661,    -1,    -1,    -1,  1561,   261,    -1,    -1,
      41,    -1,    -1,   152,   153,  1570,  1503,    -1,     3,     4,
       5,     6,  1509,    54,     9,    56,    57,  1514,  1515,  1516,
      -1,  1013,  1519,    -1,    -1,    48,    -1,    -1,  1036,    70,
     684,  1596,    -1,    56,    57,  1559,    31,    -1,    -1,    80,
      -1,   695,   205,    -1,    85,    -1,    41,    -1,   197,    -1,
      -1,    92,    47,   537,    -1,    -1,  1621,  1554,    -1,    54,
      -1,    56,    57,    -1,  1561,    -1,    -1,   331,    -1,    -1,
      -1,    -1,   726,  1570,    -1,    70,    -1,   240,    -1,  1180,
    1181,  1182,    -1,    -1,    -1,    80,   308,   309,    -1,    -1,
      85,    -1,    -1,    -1,    -1,    90,  1661,    92,    93,  1596,
      -1,   264,   324,    -1,    -1,   327,   328,    -1,  1209,  1210,
    1211,   333,    -1,   597,    -1,   337,  1177,    -1,   602,    -1,
      -1,    -1,  1183,   345,  1621,    -1,     4,     5,    -1,    -1,
      -1,     9,    -1,    -1,   350,   351,   352,    -1,    -1,    -1,
      -1,    -1,    -1,   407,   408,     4,     5,    -1,    -1,     8,
       9,     3,     4,     5,    -1,    14,   640,   421,     4,     5,
     424,    -1,    -1,  1224,  1661,    -1,   430,   431,   432,    28,
      -1,    30,   436,    -1,    -1,    -1,    54,    36,    56,    57,
      -1,    -1,   331,    -1,  1245,    31,    45,    -1,  1180,  1181,
    1182,    -1,    70,   356,    -1,    54,    -1,    56,    57,    58,
      -1,    47,    80,  1211,    56,    57,    -1,    84,    54,   473,
      56,    57,   476,    -1,   478,   479,   480,  1209,  1210,  1211,
     484,    -1,    -1,    -1,    70,    -1,   490,   491,   492,    -1,
      -1,   495,    -1,    92,    80,   499,    -1,    -1,    -1,    -1,
      -1,  1302,    -1,    -1,    90,    -1,    92,    93,   512,    -1,
       9,   414,    -1,    12,    -1,    -1,  1264,  1265,  1266,  1267,
       3,     4,     5,    -1,    -1,     3,     4,     5,     3,     4,
       5,    -1,    -1,    -1,    -1,   539,    -1,    -1,   542,    -1,
      -1,    -1,   431,   432,   161,  1346,    -1,  1348,    47,     3,
       4,     5,     6,   557,   558,   559,   950,    -1,     4,     5,
      59,    -1,    61,    62,    63,    -1,    -1,    -1,   572,   963,
      -1,    54,    -1,    56,    57,    74,   193,    76,    56,    57,
      -1,    56,    57,    -1,  1332,    31,    -1,    41,    -1,   206,
     479,   480,    -1,    92,    93,   557,   558,    -1,    -1,    -1,
      54,    47,    56,    57,   507,    -1,    60,    -1,    54,   108,
      56,    57,    -1,    90,    -1,    92,    70,    94,    -1,   623,
     624,  1462,   626,    -1,    70,    -1,    80,    -1,    -1,   633,
     533,    85,    -1,    -1,    80,    -1,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    90,    -1,    92,    93,    -1,   653,
     539,    -1,    -1,   542,    -1,   879,   880,    -1,    -1,  1407,
      -1,   885,    -1,   140,   141,     3,     4,     5,    -1,   558,
     559,     7,     8,     9,    -1,   899,    -1,   901,    14,   903,
      -1,    -1,    -1,   572,    -1,    -1,    -1,    -1,   692,    -1,
     694,   695,  1533,  1534,  1535,    31,  1444,    -1,    -1,    -1,
      36,    -1,    -1,  1504,    -1,    -1,    -1,    -1,    -1,    45,
       3,     4,     5,    -1,    -1,  1109,    -1,   620,    56,    57,
      -1,    -1,     3,     4,     5,     6,    -1,    -1,   952,    -1,
    1462,    -1,    -1,   636,   738,   691,    -1,   693,   694,    -1,
     696,    -1,    -1,    -1,   633,    -1,   750,   751,   752,   753,
     754,    -1,  1553,    -1,   758,    -1,    -1,    -1,  1559,    -1,
      41,  1509,   766,    56,    57,   769,    47,  1515,  1516,    -1,
      -1,    -1,   996,    54,    -1,    56,    57,    -1,     3,     4,
       5,     6,   738,    -1,    -1,    -1,    -1,  1535,     1,    70,
       3,     4,     5,     6,   798,     8,     3,     4,     5,    80,
      -1,  1533,  1534,  1535,    85,    -1,    -1,  1201,    -1,    90,
      -1,    92,    93,  1207,    -1,    -1,    41,    -1,    -1,    -1,
      -1,   825,    -1,    48,    -1,    -1,    -1,    -1,    41,    -1,
      -1,    56,    57,    -1,    -1,    48,     3,     4,     5,     6,
      -1,    54,    -1,    56,    57,   322,    -1,    -1,  1596,    56,
      57,    -1,   755,    -1,    -1,    80,     3,     4,     5,     6,
      85,    -1,     9,    -1,   753,   754,   483,  1615,    -1,    -1,
      -1,   488,    85,    -1,    41,   831,    -1,   109,   110,    -1,
      -1,    -1,    -1,   360,    31,    -1,    -1,    54,  1636,    56,
      57,    -1,    -1,    -1,    41,    62,   513,  1645,    -1,    -1,
      47,   905,   519,    70,   908,    -1,    -1,    54,    -1,    56,
      57,    -1,    -1,    80,   531,   532,   920,   534,    85,    -1,
     924,   925,   926,    70,    -1,    92,    -1,    -1,    -1,    -1,
      -1,   893,    -1,    80,    -1,    -1,   825,    -1,    85,  1333,
    1334,    -1,    -1,    90,    -1,    92,    93,    -1,   904,    -1,
      -1,    -1,    -1,    -1,    -1,   911,    -1,    -1,    -1,   963,
      -1,    -1,   924,   925,   968,   969,   970,    -1,    -1,    -1,
      -1,  1195,    -1,  1197,   930,  1199,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    -1,   462,   463,    -1,     3,     4,
       5,    -1,     7,   470,    -1,    -1,    -1,     4,     5,    -1,
      -1,     8,     9,    -1,    -1,    -1,    -1,    14,    -1,  1013,
      -1,    -1,   629,   630,    -1,    30,    -1,   634,    41,    -1,
      -1,    -1,    37,  1027,  1028,  1029,   503,    -1,   931,    36,
     933,    54,  1426,    56,    57,    -1,   925,   926,    45,    54,
      47,    56,    57,    -1,  1048,  1049,    -1,    54,    -1,    56,
      57,    -1,    -1,    -1,  1448,  1449,    -1,    -1,    -1,   536,
     537,    -1,    85,    70,    -1,    -1,    -1,    -1,    -1,     4,
       5,  1075,   975,    80,     9,  1299,  1080,    -1,    -1,    -1,
      -1,   970,    -1,    90,    -1,    92,    93,    -1,    -1,    -1,
      -1,    -1,   569,    -1,   571,    -1,    31,   574,   575,   331,
     577,   578,   579,   580,   581,   582,   583,   584,   585,   586,
     587,   588,   589,   590,   591,   592,   593,   594,   595,    54,
     597,    56,    57,    -1,  1013,   602,    -1,    -1,    -1,     7,
       8,     9,    -1,  1527,    -1,    70,    14,     4,     5,   756,
      -1,     7,     8,     9,    -1,    80,    -1,    -1,    14,  1153,
    1154,  1155,    -1,    31,    -1,    -1,   633,    92,    36,    -1,
      -1,    -1,    -1,   640,  1067,    31,    -1,    45,  1130,    -1,
      36,    -1,   404,    -1,  1178,  1179,  1180,  1181,  1182,    45,
      47,    -1,    60,  1187,    -1,   662,   663,    54,    -1,    56,
      57,    -1,    -1,    -1,  1150,    -1,   813,    -1,   815,    -1,
      -1,   678,    -1,    70,    -1,  1209,  1210,  1211,     3,     4,
       5,     6,    -1,    80,     9,    -1,    -1,  1221,  1222,  1223,
      -1,  1177,    -1,    90,    -1,    92,    93,  1183,    78,    79,
      80,    81,    82,    83,    84,    -1,    31,    -1,   470,  1243,
    1244,    -1,  1246,  1247,    -1,  1249,    41,  1209,  1210,   726,
      -1,    -1,    47,  1156,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    56,    57,    -1,    -1,  1154,  1155,     7,     8,     9,
     887,   888,    -1,   890,    14,    70,    -1,    -1,    -1,    -1,
      -1,    -1,  1185,    -1,    -1,    80,    -1,    -1,    -1,    -1,
      85,    31,  1181,  1182,    -1,    90,    36,    92,    93,  1303,
    1304,  1305,  1306,  1307,   921,    45,  1310,   539,    -1,    -1,
     542,    -1,   789,    -1,   546,   547,   548,   549,   550,    -1,
      60,  1210,  1211,    -1,    -1,    -1,    -1,   559,    -1,    -1,
     807,   808,    -1,   810,    -1,    -1,    -1,    -1,    -1,    -1,
     572,    -1,    -1,  1347,  1348,  1248,  1302,    -1,   825,    -1,
      -1,    -1,     3,     4,     5,   972,     7,     8,     9,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    -1,    -1,
     847,    -1,    -1,    -1,  1378,  1379,    -1,  1339,     4,     5,
      31,    -1,     8,     9,    -1,    36,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,   626,    -1,    -1,     3,     4,     5,
       6,   633,   879,   880,    -1,    56,    57,   884,   885,    -1,
      36,    -1,  1416,  1417,    -1,  1419,    -1,  1306,  1307,    45,
      -1,    47,   899,    -1,   901,  1042,   903,    -1,    54,    -1,
      56,    57,    38,    39,    -1,    41,    -1,  1054,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    54,    -1,
      56,    57,    -1,    -1,    80,    -1,    -1,    -1,  1462,    -1,
      -1,    -1,    -1,    -1,    90,   942,    92,    93,    -1,     3,
       4,     5,     6,    -1,    -1,   952,    -1,  1481,  1482,  1483,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     967,    -1,    16,    -1,    -1,    -1,    -1,  1501,  1502,  1503,
      -1,    -1,    26,   980,    -1,    -1,    -1,    41,    32,    33,
     742,    35,    -1,    37,    48,  1418,    -1,    -1,    -1,   996,
      44,    -1,    56,    57,  1141,    -1,    -1,    -1,    -1,  1533,
    1534,  1535,    -1,    57,    -1,    59,  1013,  1541,  1542,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    80,    -1,  1504,    -1,
      74,    85,    -1,     4,     5,    -1,    -1,     8,     9,    -1,
      -1,    85,    86,    14,    -1,    -1,    -1,    -1,    -1,  1186,
      -1,  1533,  1534,  1462,   806,    -1,    -1,    28,    -1,    30,
     812,  1058,    -1,    -1,   108,    36,    -1,    -1,    -1,   764,
      -1,    -1,    -1,    -1,    45,    -1,   404,  1553,    -1,     4,
       5,    -1,    -1,    54,     9,    56,    57,    -1,  1612,    -1,
      -1,    -1,   136,    -1,   138,    -1,    -1,    -1,   142,   143,
      -1,    -1,    -1,   147,   148,    -1,    31,   151,   152,   153,
     805,  1108,  1109,   463,    -1,  1112,   811,    -1,  1255,    -1,
     470,    92,  1259,   167,    -1,  1534,  1535,   171,   880,    54,
      -1,    56,    57,   177,   178,  1132,    -1,    -1,    -1,     4,
       5,    -1,   470,    -1,     9,    70,    -1,    -1,    -1,    -1,
      -1,   195,   196,   197,    -1,    80,    -1,  1294,    -1,    -1,
      -1,    -1,    -1,    -1,   916,    -1,    31,    92,    -1,    -1,
     922,  1308,    -1,    -1,   926,    -1,    -1,    -1,    -1,    -1,
     224,    -1,    -1,    -1,    -1,    -1,    -1,   537,    -1,    54,
      -1,    56,    57,    -1,    -1,    -1,    -1,   241,  1195,    -1,
    1197,    -1,  1199,    -1,    -1,    70,   250,    -1,    -1,    -1,
    1207,    -1,   964,    -1,   966,    80,    -1,   261,   970,  1216,
    1217,    -1,   917,    -1,   919,    -1,    -1,    92,  1225,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1373,    -1,    -1,    -1,
    1377,    -1,    -1,    -1,  1241,  1242,    -1,   597,    -1,    -1,
      -1,    -1,   602,   195,   196,   299,   300,    -1,    -1,    -1,
      -1,  1013,  1399,  1400,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1268,    -1,    -1,  1026,     3,     4,     5,     6,    -1,
      -1,    -1,    -1,   633,  1036,    -1,    -1,    -1,    -1,    -1,
     640,  1043,     3,     4,     5,     6,    -1,    -1,   626,    -1,
     344,    -1,  1299,  1055,   348,   633,   350,   351,   352,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    -1,   361,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    54,    -1,    56,    57,
      41,  1328,    -1,    -1,    62,    -1,    47,  1089,    -1,  1091,
      -1,    -1,    70,    54,    -1,    56,    57,    -1,    -1,    -1,
      -1,   395,    80,    -1,    -1,    -1,    -1,    85,    -1,    70,
     404,    -1,   406,   407,    92,    -1,    -1,  1119,    -1,    80,
      -1,  1368,    -1,    -1,    85,   623,   624,   421,    -1,    90,
     424,    92,    93,    -1,    -1,    -1,    -1,  1384,    -1,    -1,
      -1,    -1,   436,  1088,    -1,  1090,    -1,    -1,    -1,    -1,
     444,    -1,    -1,  1155,    -1,    -1,    -1,    -1,    -1,  1406,
      -1,    -1,    -1,    -1,   742,    -1,     3,     4,     5,     6,
       3,     4,     5,     6,     7,     8,     9,    -1,   472,   473,
    1182,    14,   476,    -1,   478,   479,   480,   481,    -1,    -1,
      -1,   485,    -1,    -1,    -1,    28,   490,    30,    31,   493,
      -1,  1146,    -1,    36,    41,    -1,    -1,    -1,    41,  1211,
      -1,    48,    45,    -1,    47,  1462,   510,    -1,    -1,    56,
      57,    54,    -1,    56,    57,   825,    -1,    -1,   806,    -1,
      -1,    -1,  1479,  1480,   812,    -1,    -1,    70,    -1,     3,
       4,     5,     6,    80,    -1,     9,    -1,    80,    85,    -1,
      -1,    -1,    85,   547,   548,   549,   550,    90,    -1,    92,
      93,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
    1517,    -1,     3,     4,     5,     6,    -1,    41,    -1,   879,
     880,   473,    -1,    -1,   476,   885,   478,   479,    -1,  1234,
      54,    -1,    56,    57,  1239,    -1,    -1,    -1,   490,   899,
    1547,   901,    -1,   903,    -1,  1307,    70,    -1,    -1,    -1,
      41,    -1,    -1,   607,    -1,   609,    80,    48,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    56,    57,   621,    92,   623,
     624,    -1,   626,    -1,    -1,    -1,    -1,    -1,    -1,   633,
      -1,    -1,    -1,   637,   922,    -1,    -1,  1292,   926,    80,
      -1,    -1,   952,    -1,    85,    -1,    -1,    -1,   652,    -1,
      -1,    -1,    -1,  1365,    -1,     3,     4,     5,     6,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   676,    -1,    -1,    -1,   964,    -1,    -1,   683,
      -1,    -1,   970,    31,    -1,    -1,   996,   691,   692,   693,
     694,   695,   696,    41,  1651,    -1,    -1,   905,    -1,    -1,
     908,    -1,    -1,  1013,    -1,    -1,    54,    -1,    56,    57,
      -1,    -1,   920,    -1,    -1,    -1,   924,   925,     3,     4,
       5,     6,    70,    -1,    -1,  1013,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,   738,    -1,    -1,    85,   742,    -1,
      -1,    -1,  1397,  1398,    92,    -1,   750,   751,   752,   753,
     754,    -1,    -1,    -1,   758,  1043,    41,    -1,    -1,  1414,
     968,   969,    -1,    -1,    -1,    -1,    -1,  1055,    -1,    54,
      -1,    56,    57,    -1,    -1,    -1,    -1,    62,    -1,    -1,
      -1,    -1,    -1,   787,    -1,    70,   790,    -1,   792,    -1,
      -1,  1503,    -1,   797,   798,    80,   800,    -1,    -1,    -1,
      85,  1089,   806,  1091,    -1,    -1,    -1,    92,   812,     3,
       4,     5,     6,    -1,    -1,   819,   820,   821,    -1,  1474,
    1475,    -1,    -1,  1535,    -1,    -1,    -1,   831,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1490,  1491,    31,    -1,    -1,
      -1,    -1,  1554,    -1,    -1,    -1,    -1,    41,   750,   751,
     752,   753,     3,     4,     5,     6,   758,    -1,     9,    -1,
      54,    -1,    56,    57,    -1,    -1,    -1,  1155,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,  1195,    80,  1197,    -1,  1199,
      41,    85,    -1,    -1,  1182,    -1,    47,    -1,    92,    -1,
     904,   905,    -1,    54,   908,    56,    57,   911,    -1,    -1,
      -1,    -1,   916,    -1,    -1,    -1,   920,    -1,   922,    70,
     924,   925,   926,  1211,    -1,    -1,   930,    -1,   932,    80,
       3,     4,     5,     6,    85,    -1,    -1,    -1,    -1,    90,
      -1,    92,    93,    -1,    -1,  1153,  1154,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
     964,    -1,   966,    -1,   968,   969,   970,     6,    41,    -1,
    1178,  1179,  1180,  1181,    -1,    48,    -1,    16,    -1,  1187,
      -1,    -1,    -1,    56,    57,    -1,    25,    26,    -1,  1299,
      -1,    -1,    -1,    32,    33,    -1,    35,    -1,    37,    -1,
      -1,  1209,  1210,     4,     5,    44,    -1,    80,     9,  1013,
      -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    57,  1307,
      59,    -1,  1026,  1027,  1028,  1029,    -1,    -1,    67,    -1,
      31,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,  1043,
      -1,    -1,  1046,    -1,    -1,    -1,    47,    86,    -1,    -1,
      -1,  1055,    -1,    54,    -1,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1068,    -1,   968,   969,    -1,    70,
      -1,    -1,  1076,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    -1,    -1,  1089,    -1,  1091,    -1,    90,
      -1,    92,    93,    -1,    -1,  1303,  1304,  1305,  1306,   138,
      -1,    -1,  1310,   142,   143,    -1,    -1,    -1,    -1,   148,
      -1,    -1,   151,   152,   153,  1119,    -1,    -1,    -1,    -1,
    1124,  1125,    -1,  1127,    -1,  1027,  1028,  1029,   167,    -1,
      -1,    -1,   171,    -1,    -1,    -1,    -1,    -1,   177,   178,
      -1,    -1,    -1,    -1,    -1,    -1,  1150,    -1,    -1,  1153,
    1154,  1155,  1462,    -1,    -1,    -1,   195,   196,   197,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,  1177,  1178,  1179,  1180,  1181,  1182,  1183,
      -1,    -1,    -1,  1187,    -1,   224,     3,     4,     5,     6,
      -1,    -1,     9,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,  1209,  1210,  1211,  1416,  1417,
      -1,  1419,    -1,    -1,    31,  1503,    -1,  1221,  1222,  1223,
    1224,    -1,   261,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    56,
      57,  1245,    -1,    -1,    -1,    -1,  1250,    -1,    -1,  1253,
      -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
     299,   300,    -1,    80,    -1,    -1,  1554,    -1,    85,    -1,
      -1,    -1,    -1,    -1,    -1,    92,  1178,  1179,  1180,  1181,
      -1,    -1,    -1,    -1,    -1,  1187,    -1,     3,     4,     5,
       6,    -1,    -1,  1501,  1502,    -1,    -1,    -1,  1302,  1303,
    1304,  1305,  1306,  1307,    -1,   344,  1310,  1209,  1210,   348,
      -1,   350,   351,   352,    -1,    31,    -1,    -1,   357,  1221,
    1222,    -1,   361,    -1,    -1,    41,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      56,    57,  1346,  1347,  1348,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,   395,    -1,    -1,    -1,
      -1,  1365,    -1,    -1,    80,   404,    -1,   406,   407,    85,
      -1,    -1,    -1,    -1,    90,    -1,    92,    93,     3,     4,
       5,     6,   421,    -1,     9,   424,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   436,    -1,    -1,
      -1,  1303,  1304,  1305,  1306,   444,    31,    -1,  1310,    -1,
      -1,    -1,  1416,  1417,    -1,  1419,    41,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    56,    57,   472,   473,    -1,    -1,   476,    -1,   478,
     479,   480,   481,    -1,    -1,    70,   485,    -1,    -1,    -1,
      -1,   490,    -1,    -1,   493,    80,    -1,    -1,  1462,    -1,
      85,    -1,    -1,    -1,    -1,    90,    -1,    92,    93,    -1,
     509,   510,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    -1,    -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1501,  1502,  1503,
    1504,    -1,    31,    -1,    -1,    -1,    -1,    36,   547,   548,
     549,   550,    41,    -1,  1416,  1417,    45,  1419,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    56,    57,  1533,
    1534,  1535,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    70,    -1,     9,    -1,    -1,    -1,    -1,    -1,  1553,
    1554,    80,    -1,    -1,    -1,  1559,    85,    -1,    -1,    -1,
      -1,    90,    -1,    92,    93,    31,    -1,    -1,   607,    -1,
     609,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,   623,   624,    -1,   626,    54,    -1,
      56,    57,    -1,    -1,   633,     3,     4,     5,     6,  1501,
    1502,    -1,    -1,    -1,    70,    -1,    -1,   646,    -1,    -1,
      -1,    -1,    -1,   652,    80,    -1,    -1,    -1,    -1,    85,
      -1,    -1,    -1,    31,    90,    -1,    92,    93,    -1,    -1,
      -1,  1533,  1534,    41,    -1,    -1,    -1,   676,    -1,    47,
      -1,     3,     4,     5,     6,   684,    54,     9,    56,    57,
      -1,    -1,   691,   692,   693,   694,   695,   696,    -1,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    85,    -1,    41,
     719,    -1,    90,    -1,    92,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    56,    57,    -1,    -1,    -1,   738,
      -1,    -1,    -1,   742,    -1,    -1,    -1,    -1,    70,    -1,
      -1,   750,   751,   752,   753,   754,    -1,    -1,    80,   758,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    -1,     1,    -1,    -1,     4,     5,    -1,    -1,
       8,     9,    -1,    -1,    -1,    -1,    14,    -1,   787,    -1,
      -1,   790,    -1,   792,    -1,    -1,    -1,    -1,   797,   798,
      28,   800,    30,    -1,    -1,    -1,    -1,   806,    36,    -1,
      38,    39,    -1,   812,    -1,    -1,    -1,    45,    -1,    47,
     819,   820,   821,    -1,    -1,    -1,    54,    -1,    56,    57,
      -1,    59,   831,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    84,    85,    86,    87,
      -1,    -1,    -1,     4,     5,    93,    94,     8,     9,    -1,
      -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    -1,    -1,    28,    -1,    30,
      -1,     3,     4,     5,     6,    36,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    45,   904,   905,    -1,    -1,   908,
      -1,    -1,   911,    54,    -1,    56,    57,   916,    -1,    31,
      -1,   920,    -1,   922,    -1,   924,   925,   926,    -1,    41,
      -1,   930,    -1,   932,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    56,    57,    -1,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    70,    -1,
      14,    -1,    -1,    -1,    -1,   964,    -1,   966,    80,   968,
     969,   970,    -1,    85,    28,    -1,    30,    31,    32,    -1,
      92,    -1,    36,    37,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    56,    57,    -1,    -1,    60,    -1,    62,    -1,
      -1,    -1,    -1,    -1,  1013,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,  1026,  1027,  1028,
    1029,    85,    -1,    -1,    -1,    -1,    -1,    -1,    92,    -1,
      -1,    -1,  1041,    -1,  1043,    -1,    -1,  1046,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   109,  1055,    -1,     1,    -1,
       3,     4,     5,     6,     7,     8,     9,    -1,    -1,    -1,
      -1,    14,    -1,    -1,    -1,    -1,    -1,  1076,    -1,    -1,
       3,     4,     5,     6,    -1,    28,     9,    30,    31,    32,
    1089,    -1,  1091,    36,    37,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    45,    46,    -1,    48,    -1,    -1,    31,    -1,
      -1,    54,    -1,    56,    57,    -1,    -1,    60,    41,    62,
    1119,    -1,    -1,    -1,    -1,  1124,  1125,    70,  1127,    -1,
      -1,    54,    -1,    56,    57,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    85,    -1,    -1,    -1,    -1,    70,    -1,    92,
      -1,  1150,    -1,    -1,  1153,  1154,  1155,    80,    -1,    -1,
      -1,    -1,    85,     4,     5,    -1,   109,     8,     9,    92,
      -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,  1177,  1178,
    1179,  1180,  1181,  1182,  1183,    -1,    -1,    28,  1187,    30,
       3,     4,     5,     6,  1193,    36,     9,    -1,    -1,     3,
       4,     5,     6,    -1,    45,     9,    -1,    -1,    -1,    -1,
    1209,  1210,  1211,    54,    -1,    56,    57,    -1,    31,    -1,
      -1,    -1,  1221,  1222,  1223,  1224,    -1,    31,    41,    -1,
      -1,  1230,    -1,     6,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    54,    -1,    56,    57,    -1,  1245,    -1,    -1,    -1,
      54,  1250,    56,    57,  1253,    -1,    -1,    70,    -1,    32,
      33,    -1,    35,    12,    37,    -1,    70,    80,    -1,    -1,
      -1,    44,    85,    -1,    -1,    -1,    80,    -1,    -1,    92,
      -1,    85,    -1,    -1,    57,    -1,    59,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1302,  1303,  1304,  1305,  1306,  1307,    82,
      -1,  1310,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,  1335,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    -1,  1346,  1347,  1348,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   135,   136,    -1,   138,  1365,    31,    -1,   142,
     143,    -1,    36,   146,    -1,   148,    -1,    41,   151,   152,
     153,    45,    -1,    47,    -1,   158,    -1,    -1,    -1,    -1,
      54,    -1,    56,    57,   167,    -1,    -1,    -1,   171,    -1,
      -1,    -1,    -1,    -1,   177,   178,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,  1416,  1417,    -1,
    1419,    85,   195,   196,   197,    -1,    90,    -1,    92,    93,
      -1,     1,   205,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      -1,   224,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,  1462,    34,    35,    36,    -1,    38,    39,
      40,    41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,
      50,    51,    52,    53,    54,    -1,    56,    57,   261,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      70,    -1,  1501,  1502,  1503,  1504,    -1,    -1,    78,    79,
      80,    -1,    -1,    -1,    -1,    85,    86,    87,    -1,    -1,
      -1,    -1,    92,    -1,    -1,    -1,     3,     4,     5,     6,
      -1,    -1,    -1,    -1,  1533,  1534,  1535,    -1,   108,    -1,
     110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1553,  1554,    -1,    -1,   331,    -1,
    1559,    -1,    -1,    -1,    41,     1,    -1,     3,     4,     5,
       6,     7,     8,     9,    -1,   348,    -1,    54,    14,    56,
      57,    -1,    -1,   356,    -1,    -1,    -1,    -1,   361,    -1,
      -1,    -1,    28,    70,    30,    31,    32,    -1,    -1,    -1,
      36,    37,    -1,    80,    -1,    41,    -1,    -1,    85,    45,
      46,    -1,    48,    -1,    -1,    92,    -1,    -1,    54,    -1,
      56,    57,   395,    -1,    60,    -1,    62,     3,     4,     5,
       6,    -1,    -1,   406,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,   421,    85,
      -1,   424,    -1,    -1,    -1,    31,    92,   430,   431,   432,
      -1,    -1,    -1,   436,    -1,    41,    -1,    -1,    -1,    -1,
      -1,   444,    -1,   109,    -1,    -1,    -1,    -1,    54,    -1,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,   472,
     473,    -1,    -1,   476,    80,   478,   479,   480,   481,    85,
      -1,    -1,   485,    -1,    -1,    -1,    92,   490,    -1,    -1,
     493,    -1,    -1,     1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    13,    14,   510,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,   539,    45,    -1,   542,
      -1,    49,    50,    51,    52,    53,    54,    -1,    56,    57,
      58,    -1,    60,    61,   557,   558,   559,    -1,    -1,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,   572,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,
      -1,     6,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      -1,    -1,   110,    -1,    14,    -1,    -1,    32,    33,    -1,
      35,    -1,    37,    -1,    -1,    -1,    -1,   620,    28,    44,
      30,    31,    32,    -1,    -1,    -1,    36,    37,    -1,    -1,
     633,    41,    57,    -1,    59,    45,    46,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    57,    -1,   652,
      60,    -1,    62,    -1,    -1,     3,     4,     5,     6,    -1,
      70,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    -1,   676,    -1,    85,    -1,    -1,    -1,    -1,
     683,    -1,    92,    31,    -1,    -1,    -1,    -1,   691,   692,
     693,   694,    -1,    41,    -1,    -1,    -1,    -1,    -1,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    56,    57,
      -1,    -1,    -1,   138,    -1,    -1,    -1,   142,   143,    -1,
      -1,    -1,    70,   148,    -1,    -1,   151,   152,   153,    -1,
      -1,    -1,    80,    -1,    -1,   738,    -1,    85,    -1,   742,
      -1,    -1,   167,    -1,    92,    -1,   171,   750,   751,   752,
     753,   754,   177,   178,    -1,   758,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     195,   196,   197,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   790,    -1,   792,
      -1,    -1,    -1,    -1,   797,   798,    -1,   800,    -1,   224,
       1,    -1,     3,     4,     5,     6,     7,     8,     9,    -1,
      -1,    12,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   825,    -1,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    36,   261,    -1,    -1,    -1,
      41,    -1,    -1,    -1,    45,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    -1,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    -1,    -1,    90,
      91,    92,    93,    94,    -1,    96,    97,    -1,    -1,    -1,
      -1,   102,    -1,    -1,    -1,    -1,   107,   108,   109,    -1,
     111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   924,   925,   926,    -1,    -1,    -1,   930,   931,    -1,
      -1,    -1,   357,    -1,    -1,    -1,   361,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      14,    -1,    -1,    -1,    -1,   968,   969,   970,    -1,    -1,
      -1,    -1,   975,    27,    28,    35,    30,    31,    32,    -1,
      -1,   406,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      44,    45,    46,    -1,    48,    -1,   421,    57,    -1,   424,
      54,    -1,    56,    57,    -1,    -1,    60,    -1,    -1,    -1,
    1013,   436,    -1,    -1,    -1,    -1,    70,    -1,    -1,   444,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    92,    -1,
      -1,    -1,    -1,  1046,    98,    -1,    -1,   472,   473,    -1,
      -1,   476,    -1,   478,   479,   480,    -1,    -1,    -1,    -1,
     485,    -1,    -1,    -1,  1067,   490,    -1,    -1,   493,    -1,
      -1,    -1,    -1,  1076,    -1,     1,    -1,     3,     4,     5,
       6,     7,     8,     9,    -1,   510,    -1,    -1,    14,    -1,
      -1,   151,   152,   153,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    31,    32,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    41,    -1,   177,    -1,    45,
      -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      56,    57,    -1,    -1,    -1,   195,   196,   197,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,  1150,    -1,    -1,
    1153,  1154,  1155,  1156,    80,    -1,    -1,    -1,    -1,    85,
      -1,    -1,    -1,    -1,   224,    -1,    92,     3,     4,     5,
       6,    -1,    98,    -1,  1177,  1178,  1179,  1180,  1181,  1182,
    1183,    -1,  1185,    -1,  1187,     4,     5,    -1,     7,     8,
       9,    -1,    -1,    12,    -1,    14,   621,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,  1209,  1210,  1211,    28,
      -1,    30,    31,    -1,    -1,    -1,    -1,    36,    54,    -1,
      56,    57,    -1,    -1,    60,    -1,    45,   652,    47,    -1,
      -1,    -1,    -1,    -1,    70,    54,    -1,    56,    57,    -1,
     300,    -1,  1245,    -1,    80,    -1,    -1,  1250,    -1,    85,
    1253,    70,    -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    80,    -1,    -1,    -1,    -1,   691,   692,   693,   694,
      -1,    90,    -1,    92,    93,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    -1,    -1,    -1,     4,     5,
     350,   351,   352,     9,    -1,    -1,    -1,    -1,    -1,  1302,
    1303,  1304,  1305,  1306,  1307,    -1,    -1,  1310,    -1,    31,
      -1,    -1,    -1,   738,    -1,    31,    -1,   742,    -1,    41,
      -1,    -1,    -1,    -1,    -1,   750,   751,    -1,    -1,    -1,
      -1,    47,    54,   758,    56,    57,    -1,    -1,    54,    -1,
      56,    57,    -1,  1346,  1347,  1348,   406,    31,    70,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    85,    80,   790,    -1,   792,    -1,    -1,
      92,    -1,   797,   798,    90,   800,    92,    93,    -1,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   472,   473,    -1,    -1,   476,    -1,   478,   479,
     480,   481,    -1,    -1,    -1,   485,    -1,    -1,    -1,    -1,
     490,    -1,    -1,   493,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1462,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    -1,    45,    57,    47,
      -1,    49,    50,    51,    52,    53,    54,    -1,    56,    57,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    70,    82,    -1,    -1,    85,   932,     4,     5,
      78,    79,    80,     9,    -1,    -1,    -1,    85,    86,    87,
      -1,    -1,    90,    -1,    92,    93,    -1,   106,    -1,   108,
    1533,  1534,  1535,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,   110,   968,   969,   970,    -1,    -1,    -1,   609,
      -1,    47,    -1,    -1,    -1,    -1,  1559,    -1,    54,    -1,
      56,    57,    -1,   623,   624,    -1,   626,    -1,    -1,    -1,
      -1,    -1,    -1,   633,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,  1013,    -1,
      -1,    -1,   652,    -1,    90,    -1,    92,    93,   177,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,   195,   196,   197,    -1,
      -1,  1046,    -1,    -1,    -1,    -1,   205,    -1,    -1,    -1,
      -1,   691,    -1,   693,   694,    -1,   696,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   224,    -1,    -1,    -1,    -1,
      -1,  1076,    -1,    -1,    -1,    -1,     4,     5,    -1,     7,
       8,     9,     4,     5,    12,    -1,    14,     9,    -1,    -1,
      -1,   250,    -1,    -1,    -1,    -1,    -1,    -1,   738,    -1,
      28,    -1,    30,    31,    -1,   264,    -1,    -1,    36,    31,
     750,   751,   752,   753,   754,    -1,    -1,    45,   758,    47,
      -1,    -1,    -1,    -1,    -1,    47,    54,    -1,    56,    57,
      -1,    -1,    54,    -1,    56,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,   797,    80,    -1,
      -1,    -1,    90,    -1,    92,    93,    -1,    -1,    90,    -1,
      92,    93,  1177,  1178,  1179,  1180,  1181,  1182,    -1,   819,
     820,   821,  1187,    -1,     3,     4,     5,     6,     7,     8,
       9,   831,    -1,    -1,    -1,    14,    -1,   356,   357,    -1,
      -1,    -1,    -1,    -1,  1209,  1210,  1211,    -1,    -1,    28,
      -1,    30,    31,    32,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    56,    57,    -1,
    1245,    -1,    -1,    -1,    -1,  1250,    -1,   406,  1253,    -1,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    -1,   904,   905,    85,    -1,   908,    -1,
      -1,   911,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,
     920,    -1,    -1,    -1,   924,   925,   926,    -1,    -1,    -1,
     930,    -1,    -1,    -1,    -1,    -1,     4,     5,  1303,  1304,
      -1,     9,    -1,    -1,    -1,  1310,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   472,   473,    -1,    -1,   476,    -1,   478,
     479,   480,   481,    31,    -1,    -1,   485,    -1,   968,   969,
     970,   490,    -1,    -1,   493,    -1,    -1,    -1,    -1,    47,
      -1,  1346,  1347,  1348,    -1,    -1,    54,    -1,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,  1013,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    -1,    92,    93,    -1,  1027,  1028,  1029,
      -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,  1046,    13,    14,    15,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    -1,
      56,    57,    58,    -1,    60,    61,    -1,  1462,    -1,    -1,
      -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    79,    80,    -1,    -1,   636,   637,    85,
      86,    87,    -1,    -1,  1124,  1125,    92,  1127,    -1,    -1,
      96,    -1,    -1,   652,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   109,   110,    -1,    -1,    -1,    -1,    -1,
    1150,    -1,    -1,  1153,  1154,  1155,    -1,    -1,    -1,    -1,
      -1,    -1,     4,     5,    -1,    -1,    -1,     9,  1533,  1534,
    1535,    -1,   691,    -1,   693,   694,    -1,  1177,  1178,  1179,
    1180,  1181,  1182,  1183,    -1,    -1,    -1,  1187,    -1,    31,
      -1,    -1,    -1,    -1,  1559,   350,   351,   352,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,  1209,
    1210,  1211,    54,    -1,    56,    57,    -1,    -1,    -1,   738,
      -1,  1221,  1222,  1223,  1224,    -1,    -1,    -1,    70,    -1,
      -1,   750,   751,   752,   753,   754,   755,    -1,    80,   758,
      -1,    -1,    -1,    -1,    -1,  1245,    -1,    -1,    90,    -1,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   784,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,   797,    -1,
      -1,    -1,    25,    26,    -1,    -1,    -1,    -1,    -1,    32,
      33,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1302,  1303,  1304,  1305,  1306,  1307,    -1,    -1,
    1310,    -1,     3,     4,     5,     6,     7,     8,     9,    -1,
      -1,    -1,    -1,    14,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    -1,    -1,    -1,    -1,    36,  1346,    -1,  1348,    -1,
      41,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    -1,    56,    57,    -1,    -1,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      -1,    -1,    -1,   126,    -1,   128,    -1,    -1,    -1,    80,
      -1,    -1,   135,   136,    85,    -1,    -1,    -1,    -1,   142,
     143,    92,    -1,   146,   147,   148,    -1,   150,   151,   152,
     153,    -1,   931,   932,   933,    -1,  1416,  1417,    -1,  1419,
       4,     5,    -1,     7,     8,     9,    -1,    -1,    -1,    -1,
      14,    -1,    -1,     4,     5,    -1,     7,     8,     9,    -1,
      -1,    12,    -1,    14,    28,    -1,    30,    31,    -1,   968,
     969,   970,    36,    -1,    -1,    -1,   975,    28,    -1,    30,
      31,    45,  1462,    -1,    48,    36,    -1,    -1,   623,   624,
      54,   626,    56,    57,    45,    -1,    -1,    -1,   633,    -1,
      -1,    -1,    -1,    54,    -1,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1013,    -1,    -1,   240,   241,    -1,
      -1,  1501,  1502,  1503,  1504,    -1,    -1,    -1,  1027,  1028,
    1029,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   261,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1046,    -1,    -1,
      -1,    -1,    -1,  1533,  1534,  1535,   691,    -1,   693,   694,
      -1,   696,    -1,    -1,    -1,    -1,    -1,    -1,  1067,    -1,
      -1,    -1,    -1,  1553,    -1,    -1,    -1,   300,    -1,  1559,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,    14,
      -1,    -1,    -1,   738,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    31,    32,    -1,    -1,
      -1,    36,    -1,    -1,    -1,   348,    41,   350,   351,    -1,
      45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    56,    57,    -1,    -1,    60,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,  1156,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,
      85,    -1,   395,    -1,    -1,    -1,    -1,    92,  1177,  1178,
    1179,  1180,  1181,  1182,  1183,    -1,  1185,    -1,  1187,    -1,
      -1,   414,    -1,    -1,    -1,    -1,   831,    -1,   421,    -1,
      -1,   424,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1209,  1210,  1211,   436,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1221,  1222,  1223,  1224,    -1,     4,     5,    -1,
       7,     8,     9,    -1,    -1,    12,    -1,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1245,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,   904,
     905,    -1,    -1,   908,    -1,    -1,   911,    54,    -1,    56,
      57,    -1,    -1,    -1,   507,   920,   509,    -1,    -1,   924,
     925,   926,    -1,    -1,    -1,   930,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1302,  1303,  1304,  1305,  1306,  1307,    -1,
     533,  1310,    -1,    -1,    -1,     1,    -1,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    -1,   968,   969,   970,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    31,    -1,  1346,    -1,  1348,
      36,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    45,
      -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      56,    57,    -1,    -1,    60,    -1,    -1,    -1,  1013,    -1,
      -1,    -1,    -1,    -1,    70,    -1,   609,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,   620,   621,    85,
     623,   624,    -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1416,  1417,  1418,
    1419,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    -1,    -1,    12,    -1,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,   676,    -1,    -1,    -1,    36,    -1,    -1,
     683,   684,    41,  1462,    -1,    -1,    45,    -1,    47,    -1,
      -1,    -1,   695,    -1,    -1,    54,    -1,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    -1,    -1,    -1,   719,    -1,    -1,    -1,
      -1,    80,  1501,  1502,  1503,  1504,    85,    -1,    -1,    -1,
      -1,    90,    -1,    92,    93,  1150,    -1,    -1,  1153,  1154,
    1155,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1533,  1534,  1535,    -1,    -1,    -1,
      -1,    -1,  1177,  1178,  1179,  1180,  1181,  1182,  1183,    -1,
      -1,    -1,  1187,    -1,  1553,    -1,    -1,    -1,    -1,    -1,
    1559,   784,    -1,    -1,   787,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1209,  1210,  1211,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    -1,   819,   820,   821,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   831,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    12,    -1,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    45,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    56,    57,    -1,    -1,    -1,  1302,  1303,  1304,
    1305,  1306,  1307,    -1,    -1,  1310,    70,    -1,    -1,    -1,
      -1,   904,   905,    -1,    -1,   908,    80,    -1,   911,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    90,   920,    92,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   930,     1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      13,    14,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    -1,    56,    57,    58,    -1,    60,    61,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,
      -1,  1416,  1417,    -1,  1419,    78,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    87,    -1,    -1,    -1,    -1,    92,
      -1,    -1,    -1,    96,     3,     4,     5,     6,     7,     8,
       9,    -1,    -1,    12,    -1,    14,    -1,   110,  1041,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    41,    -1,    -1,  1068,    45,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1501,  1502,  1503,  1504,
      -1,    70,    -1,     4,     5,    -1,     7,     8,     9,    -1,
      -1,    80,    -1,    14,    -1,    -1,    85,    -1,    -1,    -1,
      -1,    90,    -1,    92,    93,    -1,    -1,    28,    -1,    30,
      31,  1124,  1125,    -1,  1127,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,  1553,    -1,
      -1,    -1,    -1,    54,    -1,    56,    57,  1150,    -1,    -1,
    1153,  1154,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1193,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      -1,    38,    39,    40,    41,    42,    43,    -1,    45,    -1,
      47,    -1,    49,    50,    51,    52,    53,    54,    -1,    56,
      57,    58,    -1,    -1,    61,    -1,    -1,  1230,    -1,    -1,
      67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    79,    80,    -1,  1248,    -1,  1250,    85,    86,
      87,    -1,    -1,    90,    -1,    92,    93,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    -1,    38,    39,    40,    41,    42,    43,
      -1,    45,    -1,    47,    -1,    49,    50,    51,    52,    53,
      54,    -1,    56,    57,    58,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    87,    -1,    -1,    90,    -1,    92,    93,
       1,    -1,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    -1,    13,    14,    -1,    -1,   110,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      -1,    32,    -1,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    58,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,
      -1,    92,    93,     1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    -1,    13,    14,    -1,   109,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    -1,    45,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    54,    -1,    56,    57,
      58,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,
      -1,    -1,    -1,     1,    92,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    -1,    13,    14,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    29,    30,    -1,    32,    -1,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    -1,    45,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    54,    -1,    56,    57,
      58,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,
      -1,    -1,    -1,    -1,    92,    93,     1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    10,    11,    -1,    13,    14,
      -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    -1,    32,    -1,    34,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    -1,
      45,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      -1,    56,    57,    58,    -1,    -1,    61,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    87,    -1,    -1,    -1,     1,    92,     3,     4,
       5,     6,    -1,     8,     9,    10,    11,    -1,    13,    14,
      -1,    -1,    -1,    -1,   109,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    -1,    32,    -1,    34,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    -1,
      45,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      -1,    56,    57,    58,    -1,    -1,    61,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    87,    -1,    -1,    -1,     1,    92,     3,     4,
       5,     6,    -1,     8,     9,    10,    11,    -1,    13,    14,
      -1,    -1,    -1,    -1,   109,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    -1,    32,    -1,    34,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    -1,
      45,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      -1,    56,    57,    58,    -1,    -1,    61,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    87,    -1,    -1,    -1,    -1,    92,    -1,    -1,
       1,    -1,     3,     4,     5,     6,   101,     8,     9,    10,
      11,    -1,    13,    14,    -1,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    58,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,
       1,    92,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      -1,    32,    -1,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    58,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,
       1,    92,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      -1,    32,    -1,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,
       1,    92,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      -1,    32,    -1,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,
       1,    92,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      -1,    32,    -1,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,
       1,    92,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    -1,    13,    14,    -1,    -1,    -1,   108,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      -1,    32,    -1,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,
       1,    92,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      -1,    32,    -1,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,
       1,    92,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      -1,    32,    -1,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,     3,     4,     5,
       6,    92,     8,     9,    10,    11,    -1,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    28,    29,    30,    -1,    32,    -1,    34,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    -1,    45,
      -1,    -1,    -1,    49,    50,    51,    52,    53,    54,    -1,
      56,    57,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    87,    -1,    -1,    -1,    -1,    92,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,   110,   111,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    13,    14,    15,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    -1,    56,
      57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,
      87,    -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,    96,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,   110,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    13,    14,    15,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    -1,    56,    57,    58,
      -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    -1,    96,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,    14,
      15,   110,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      -1,    56,    57,    58,    -1,    60,    61,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    87,    -1,    -1,    -1,    -1,    92,    -1,    -1,
      -1,    96,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    13,    14,    15,   110,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    96,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      -1,    38,    39,    40,    41,    42,    43,    -1,    45,    -1,
      47,    -1,    49,    50,    51,    52,    53,    54,    -1,    56,
      57,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,
      87,    -1,    -1,    90,    -1,    92,    93,     3,     4,     5,
       6,    -1,     8,     9,    10,    11,    -1,    13,    14,    -1,
      -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    -1,    45,
      -1,    47,    -1,    49,    50,    51,    52,    53,    54,    -1,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    87,    -1,    -1,    90,    -1,    92,    93,     3,     4,
       5,     6,    -1,     8,     9,    10,    11,    -1,    13,    14,
      -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    -1,
      45,    -1,    47,    -1,    49,    50,    51,    52,    53,    54,
      -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    87,    -1,    -1,    90,    -1,    92,    93,     3,
       4,     5,     6,    -1,     8,     9,    10,    11,    -1,    13,
      14,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    -1,    38,    39,    40,    41,    42,    43,
      -1,    45,    -1,    -1,    -1,    49,    50,    51,    52,    53,
      54,    -1,    56,    57,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    87,     3,     4,     5,     6,    92,     8,
       9,    10,    11,    -1,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    28,
      29,    30,    -1,    32,    -1,    34,    35,    36,    -1,    38,
      39,    40,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    -1,    56,    57,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,    -1,
      -1,    -1,    -1,    92,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    13,    14,    -1,    -1,    -1,    -1,
      -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    -1,    38,
      39,    40,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    -1,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,     3,
       4,     5,     6,    92,     8,     9,    10,    11,    -1,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   110,    -1,    -1,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    -1,    38,    39,    40,    41,    42,    43,
      -1,    45,    -1,    -1,    -1,    49,    50,    51,    52,    53,
      54,    -1,    56,    57,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    87,     3,     4,     5,     6,    92,     8,
       9,    10,    11,    -1,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    28,
      29,    30,    -1,    32,    -1,    34,    35,    36,    -1,    38,
      39,    40,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    -1,    56,    57,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,     3,
       4,     5,     6,    92,     8,     9,    10,    11,    -1,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   110,    -1,    -1,    28,    29,    30,    -1,    32,    -1,
      34,    35,    36,    -1,    38,    39,    40,    41,    42,    43,
      -1,    45,    -1,    -1,    -1,    49,    50,    51,    52,    53,
      54,    -1,    56,    57,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    87,     3,     4,     5,     6,    92,     8,
       9,    10,    11,    -1,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    28,
      29,    30,    -1,    32,    -1,    34,    35,    36,    -1,    38,
      39,    40,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    -1,    56,    57,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,     3,
       4,     5,     6,    92,     8,     9,    10,    11,    -1,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   110,    -1,    -1,    28,    29,    30,    -1,    32,    -1,
      34,    35,    36,    -1,    38,    39,    40,    41,    42,    43,
      -1,    45,    -1,    -1,    -1,    49,    50,    51,    52,    53,
      54,    -1,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    87,     3,     4,     5,     6,    92,     8,
       9,    10,    11,    -1,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    28,
      29,    30,    -1,    32,    -1,    34,    35,    36,    -1,    38,
      39,    40,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    -1,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,    -1,
      -1,    -1,    -1,    92,    93,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    -1,    13,    14,    -1,    -1,    -1,
      -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    -1,    45,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    54,    -1,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,
       3,     4,     5,     6,    92,     8,     9,    10,    11,    -1,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    28,    29,    30,    -1,    32,
      -1,    34,    35,    36,    -1,    38,    39,    40,    41,    42,
      43,    -1,    45,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    54,    -1,    56,    57,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    87,     3,     4,     5,     6,    92,
       8,     9,    10,    11,    -1,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    -1,    45,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    54,    -1,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,
       3,     4,     5,     6,    92,     8,     9,    10,    11,    -1,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    28,    29,    30,    -1,    32,
      -1,    34,    35,    36,    -1,    38,    39,    40,    41,    42,
      43,    -1,    45,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    54,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    87,     3,     4,     5,     6,    92,
       8,     9,    10,    11,    -1,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,
      28,    29,    30,    -1,    32,    -1,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    -1,    45,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    54,    -1,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,
       3,     4,     5,     6,    92,     8,     9,    10,    11,    -1,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,    28,    29,    30,    -1,    32,
      -1,    34,    35,    36,    -1,    38,    39,    40,    41,    42,
      43,    -1,    45,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    54,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    87,    -1,    -1,    -1,    -1,    92,
       3,     4,     5,     6,     7,     8,     9,    -1,    -1,    12,
      -1,    14,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    56,    57,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    -1,    -1,    70,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    85,    28,    -1,    30,    31,    -1,    -1,    92,
      -1,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    56,    57,    -1,    -1,    -1,    -1,    62,     3,     4,
       5,     6,     7,     8,     9,    70,    -1,    -1,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,
      85,    -1,    -1,    28,    -1,    30,    31,    92,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    56,    57,    -1,    -1,    60,     3,     4,     5,     6,
       7,     8,     9,    -1,    -1,    70,    -1,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,
      85,    28,    -1,    30,    31,    -1,    -1,    92,    -1,    36,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    56,
      57,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    -1,    -1,    70,    -1,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    85,    28,
      -1,    30,    31,    -1,    -1,    92,    -1,    36,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    56,    57,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      14,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    -1,    -1,    -1,    85,    31,    -1,    -1,
      -1,    -1,    36,    92,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    45,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    92,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,   111,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    -1,   107,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   113,   114,   115,     0,   121,   122,   121,     1,     3,
       4,     5,     6,     7,     8,     9,    14,    27,    28,    30,
      31,    32,    36,    41,    44,    45,    46,    48,    54,    56,
      57,    60,    70,    80,    85,    92,    98,   119,   120,   123,
     126,   128,   130,   134,   135,   142,   145,   149,   150,   155,
     167,   178,   180,   206,   208,   213,   214,   227,   228,   230,
     231,   233,   237,   245,   248,   249,   262,   270,   271,   272,
     273,   274,   276,   277,   300,   307,   308,   309,   311,   313,
     315,   318,   319,   320,   327,   328,   399,   400,    60,   109,
      73,    54,    73,    54,    73,    73,    48,     3,     4,     5,
      56,    57,    58,   164,   178,   309,   319,   326,   328,    92,
      92,    92,     4,     5,    56,    57,    58,   164,     3,     4,
       5,    56,    57,   178,   321,   322,   323,   324,   328,     4,
       5,    44,    56,    57,   314,   319,   328,    73,   176,    54,
      73,    73,   248,   300,   310,   311,   319,   328,   300,   310,
     393,    70,    80,    92,   206,   211,   212,   214,   248,   312,
     313,   327,   123,    92,    60,    58,    98,   117,     1,     7,
      48,   119,   134,   142,   143,   144,   149,   227,   230,   237,
     262,   107,   148,   120,   238,    25,   147,   158,   159,    60,
      54,    93,   301,   303,    60,    70,    80,    92,   224,   235,
     243,   305,   306,   311,   318,   319,   327,     7,     9,    60,
     150,   233,   236,   244,   248,   311,     7,     8,     9,   229,
     232,   234,   248,   262,    59,    60,   249,     7,     8,     9,
      36,    58,   103,   104,   105,   164,   166,   178,   179,   248,
     319,   328,    58,    62,   275,    62,   278,    58,     9,   233,
     328,   238,     5,    48,    80,   180,   206,   209,   213,   318,
     320,   299,   309,   318,   319,     1,    38,    39,    47,    59,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      84,    85,    86,    87,    93,    94,   110,   231,   233,   300,
     373,    73,     3,     9,    10,    11,    13,    29,    34,    35,
      38,    39,    40,    42,    43,    49,    50,    51,    52,    53,
      56,    57,    61,    67,    70,    78,    79,    80,    85,    86,
      87,    92,   110,   119,   183,   184,   185,   186,   198,   203,
     204,   205,   206,   215,   217,   218,   219,   220,   222,   226,
     231,   233,   300,   315,   316,   317,   319,   328,   183,   183,
     207,   176,   109,   264,    58,    48,   309,   318,   187,   196,
     205,   226,   187,   226,    92,   125,    58,    63,    54,    54,
      54,    54,    54,    54,     3,     4,     5,    48,    56,    57,
     164,   178,   324,   325,   322,   131,     4,     5,   206,   209,
     210,   210,   314,    74,   136,   150,   227,   230,   233,   311,
     184,   183,   311,   310,   319,   310,     4,     5,   164,   178,
     211,   300,   312,   211,   300,   312,   211,   108,    56,    57,
      70,    80,    92,   206,   212,   108,   299,   220,   114,   116,
      48,   145,   149,   143,   117,   148,   235,   236,    60,    60,
      92,   247,   248,     3,     1,    62,    96,   146,   160,   221,
     363,    47,    63,    92,   254,    60,   111,   301,   302,    47,
      92,   299,   248,   300,   304,   305,   300,   304,    70,    80,
      92,   248,   304,   327,   238,    59,    60,    93,   303,   318,
     299,   229,   232,    59,    60,   238,     7,   234,   248,   229,
     234,   224,   239,    73,   164,   179,   164,   319,   278,   393,
     265,   232,   246,    47,    92,     6,   164,   325,   400,    47,
      92,     9,   310,     5,    80,   180,    93,    93,    62,   111,
     232,    70,    80,   319,   327,   398,   207,    92,     9,    92,
     198,   233,    92,   198,   204,   204,    92,    73,    73,    73,
      73,   205,   164,   204,   204,   204,     1,    70,    80,    92,
     187,   206,   211,   216,   226,   204,    74,    76,   182,    59,
     204,    58,    92,   198,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    47,    92,    47,    86,
      87,    91,    92,    93,    94,    58,    92,   201,   298,   373,
      93,   204,    11,     1,     8,    48,    85,   209,   210,   316,
     319,   328,    47,    70,    80,    90,    92,    93,   203,   225,
     327,   332,   333,    92,   225,   332,   319,   328,   332,    47,
      92,     3,    39,   208,   218,   315,   328,   400,   182,   182,
     183,   150,   227,   233,   311,   164,   296,   297,   109,   263,
     164,   108,    59,    59,   108,   108,   108,     7,     8,     9,
     164,   250,   251,   252,   116,   124,   127,   325,    73,    54,
     133,   210,   314,   328,    45,   135,   137,   139,   140,   141,
     226,   228,   230,   231,   233,   270,   300,   390,   392,   171,
     224,    60,   170,   182,   182,   310,   310,   108,   211,   310,
     108,   109,   118,   118,   144,   149,    60,    60,   220,   161,
     364,     1,    58,   339,   340,     1,    58,   205,   255,   196,
     197,   205,   187,   111,     1,    12,   197,   226,   233,   383,
     384,   388,   389,   390,   392,    61,   395,   305,   304,   304,
     300,   300,    70,    80,    92,   319,   327,   108,   299,   241,
     247,   239,   111,   302,   299,   304,   229,   239,   241,   238,
     183,   164,     4,     5,     7,    30,    37,   178,   279,   280,
     281,   282,   307,   321,   328,     1,     5,    46,    60,    62,
     119,   128,   135,   150,   156,   157,   180,   227,   230,   283,
     285,   286,   287,   311,   241,   299,   151,    73,    73,    54,
      73,   299,   153,    47,    92,    47,    92,   111,   111,   299,
     299,   299,   183,   197,   226,    92,   225,   226,   187,   226,
     226,   233,   226,   226,   226,   108,   211,   108,   108,   340,
     108,   185,     3,     4,     5,    56,    57,    93,   164,   255,
     256,   226,   205,   205,     1,   187,   378,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   197,   197,   187,   200,
     200,    92,   298,    47,    63,    92,   202,    70,    80,    93,
     327,   329,   330,   111,   187,    54,   164,     8,    47,    92,
      47,    92,    47,    92,   248,   300,   331,   332,   300,   331,
     226,   248,   331,   384,   111,   302,    92,   299,    47,   299,
     299,    47,    92,    93,    70,    80,    92,   197,   203,   211,
     248,   319,   328,   319,   197,   181,   181,   182,   175,   224,
      60,   174,    63,    59,   269,   296,     1,   205,     1,   205,
      59,   108,    92,   109,   116,   133,    54,   183,    60,   210,
     314,   138,   164,   270,    59,    74,    63,    63,    70,    80,
      92,   224,   327,   332,   311,   319,   224,   224,   138,   164,
      63,   177,   169,   168,   177,   181,   108,    60,   148,   118,
     118,   108,     3,    47,    56,    57,    92,   162,   163,   165,
     307,   321,   146,   340,   341,   109,   256,   108,   108,   108,
      12,    59,    62,    92,   108,    12,    59,    62,    12,   311,
     391,   392,   394,    63,   385,    47,    92,   300,   300,   299,
      63,   111,   395,   247,    74,   393,    92,   393,    59,     7,
      37,   393,    47,    92,   205,   286,   227,   286,   238,   238,
      25,    58,    62,    96,    47,    92,     3,     4,    62,   150,
     224,   288,   290,   292,   293,   305,   311,   319,   328,   150,
     156,   289,   293,   311,    37,   109,   284,   286,    60,   109,
     238,   395,   383,   183,   183,   183,   395,   383,   299,   152,
     299,   154,   398,   398,   398,   182,   108,   108,   108,   108,
     108,    74,    74,    74,    74,   108,   108,   205,    62,    59,
     268,   108,    62,   108,   108,   111,   197,   197,   226,   200,
     202,   255,   197,   233,   299,   299,   187,   299,    93,   204,
     111,    85,    73,    47,   197,   197,   197,   332,   331,   331,
     108,   108,   111,   395,   395,   331,   299,   383,   111,   302,
     248,   108,   108,    70,    80,    92,   319,   108,   177,   173,
     172,   177,   205,   297,   109,   269,   251,   108,     3,   197,
     109,    60,   182,   138,   141,   226,   185,   248,   300,   300,
      70,    80,    92,   248,   318,   319,   327,   299,   205,   177,
     177,   148,   197,    59,    47,    92,    47,    92,    47,    92,
     340,    33,   109,   193,   336,   337,   338,    59,   109,    70,
      80,    92,   206,   211,   315,   385,    63,   386,   226,   396,
     397,    70,    80,    92,   248,   242,    63,   181,   187,   226,
     393,   393,   393,   281,   299,   383,    60,   247,   247,   299,
     383,    62,    62,   205,   238,    59,   238,   238,   319,   238,
      59,    62,   247,   285,   247,   108,   182,   182,   182,   108,
     395,   383,   395,   383,    92,    92,    92,    92,   111,   255,
     164,   255,   109,   205,   109,   108,   108,   199,   226,   108,
     108,   329,   329,   111,   329,   302,   204,     8,   183,   108,
     108,   108,   299,   395,   108,   111,   177,   177,   109,    59,
     108,   108,   248,   300,   300,    70,    80,    92,   327,   318,
     299,   108,   163,   197,   197,   197,   365,   164,   253,     1,
       3,     4,     5,    15,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    44,    46,    57,    60,    96,   119,
     120,   126,   129,   130,   187,   223,   227,   230,   233,   334,
     335,   340,   342,   347,   348,   366,   375,   338,   109,   211,
     108,   255,   101,   255,   387,    59,   108,   255,   240,   108,
     108,   280,   395,   108,   254,   254,   395,   108,   205,   205,
     247,   247,     3,     4,    62,   291,   294,   295,   305,   311,
     247,   247,     5,   247,   295,   266,   254,   299,   299,   108,
     108,   187,   187,   187,   187,   255,    62,    93,   202,   199,
     111,    47,   182,   395,   299,   197,   300,   300,   319,   299,
     108,   108,   108,    95,   369,   370,    59,    60,    60,   109,
      62,    62,    62,   343,   350,   352,   354,   358,   205,    62,
      60,    60,    60,   187,    80,   164,   164,    56,   132,   328,
      62,   367,   223,     9,   377,    60,    60,   224,   235,    60,
     236,   311,    92,   235,     1,   109,   335,   347,    16,   109,
     347,   108,   396,   255,   299,   299,   247,   247,   254,    62,
      62,   205,   238,   238,   254,   254,   254,   261,   395,   395,
     299,   299,   108,   108,   108,   108,   255,   187,   202,   395,
     108,    70,    80,    92,   248,   371,   370,   164,    47,    92,
     189,   189,   340,   345,   346,    92,    92,    12,    62,   362,
      60,   187,    60,    54,    56,   164,    56,   132,   164,   340,
      92,    60,    60,    70,    80,    92,    60,   109,   349,   395,
     395,   205,   205,   247,   247,   247,     1,   102,   260,   267,
     395,   395,   111,   248,    92,   374,   187,   191,   233,   373,
     344,   351,    17,   348,    58,   223,   376,   378,   191,   205,
     360,   347,    60,    54,   164,   368,   220,   345,   247,   247,
     254,   254,     1,   205,   259,    12,   392,   372,   108,   224,
     345,    58,   194,   348,   353,   193,   355,    60,   108,    62,
     347,   369,    62,   108,   107,   107,    97,   257,   258,   108,
     108,   340,   238,   195,    47,    92,   188,     1,   190,   191,
     359,   361,    11,   379,   380,   381,    60,   147,   148,   247,
     193,   187,    60,    60,   345,   347,    92,    62,   108,    59,
       1,   146,   363,    63,   108,   356,   187,   379,    60,   381,
     339,   192,   378,   108,    62,   108,   255,   108,    11,   382,
      60,   357,    59,   108,   194,    11,    60
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
        case 3:
/* Line 1792 of yacc.c  */
#line 343 "parse.y"
    { finish_translation_unit (); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 351 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 353 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 355 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 364 "parse.y"
    { have_extern_spec = 1;
		  used_extern_spec = 0;
		  (yyval.ttype) = NULL_TREE; }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 369 "parse.y"
    { have_extern_spec = 0; }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 374 "parse.y"
    { (yyval.itype) = pedantic;
		  pedantic = 0; }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 383 "parse.y"
    { if (pending_lang_change) do_pending_lang_change(); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 385 "parse.y"
    { if (! toplevel_bindings_p () && ! pseudo_global_level_p())
		  pop_everything (); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 391 "parse.y"
    { if (pending_inlines) do_pending_inlines (); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 393 "parse.y"
    { if (pending_inlines) do_pending_inlines (); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 395 "parse.y"
    { if (pending_inlines) do_pending_inlines (); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 397 "parse.y"
    { if (TREE_CHAIN ((yyvsp[(3) - (5)].ttype))) (yyvsp[(3) - (5)].ttype) = combine_strings ((yyvsp[(3) - (5)].ttype));
		  assemble_asm ((yyvsp[(3) - (5)].ttype)); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 400 "parse.y"
    { pop_lang_context (); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 402 "parse.y"
    { if (pending_inlines) do_pending_inlines ();
		  pop_lang_context (); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 405 "parse.y"
    { if (pending_inlines) do_pending_inlines ();
		  pop_lang_context (); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 408 "parse.y"
    { push_namespace ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 410 "parse.y"
    { pop_namespace (); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 412 "parse.y"
    { push_namespace (NULL_TREE); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 414 "parse.y"
    { pop_namespace (); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 417 "parse.y"
    { do_toplevel_using_decl ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 420 "parse.y"
    { pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 425 "parse.y"
    { begin_only_namespace_names (); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 427 "parse.y"
    {
		  end_only_namespace_names ();
		  if (lastiddecl)
		    (yyvsp[(5) - (6)].ttype) = lastiddecl;
		  do_namespace_alias ((yyvsp[(2) - (6)].ttype), (yyvsp[(5) - (6)].ttype));
		}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 437 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 439 "parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 441 "parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 446 "parse.y"
    { (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 448 "parse.y"
    { (yyval.ttype) = build_parse_node (SCOPE_REF, global_namespace, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 450 "parse.y"
    { (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(3) - (4)].ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 455 "parse.y"
    { begin_only_namespace_names (); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 457 "parse.y"
    {
		  end_only_namespace_names ();
		  /* If no declaration was found, the using-directive is
		     invalid. Since that was not reported, we need the
		     identifier for the error message. */
		  if (TREE_CODE ((yyvsp[(4) - (5)].ttype)) == IDENTIFIER_NODE && lastiddecl)
		    (yyvsp[(4) - (5)].ttype) = lastiddecl;
		  do_using_directive ((yyvsp[(4) - (5)].ttype));
		}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 470 "parse.y"
    {
		  if (TREE_CODE ((yyval.ttype)) == IDENTIFIER_NODE)
		    (yyval.ttype) = lastiddecl;
		  got_scope = (yyval.ttype);
		}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 476 "parse.y"
    {
		  (yyval.ttype) = (yyvsp[(2) - (3)].ttype);
		  if (TREE_CODE ((yyval.ttype)) == IDENTIFIER_NODE)
		    (yyval.ttype) = lastiddecl;
		  got_scope = (yyval.ttype);
		}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 487 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 489 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 494 "parse.y"
    { push_lang_context ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 496 "parse.y"
    { if (current_lang_name != (yyvsp[(2) - (2)].ttype))
		    cp_error ("use of linkage spec `%D' is different from previous spec `%D'", (yyvsp[(2) - (2)].ttype), current_lang_name);
		  pop_lang_context (); push_lang_context ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 503 "parse.y"
    { begin_template_parm_list (); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 505 "parse.y"
    { (yyval.ttype) = end_template_parm_list ((yyvsp[(4) - (5)].ttype)); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 507 "parse.y"
    { begin_specialization(); 
		  (yyval.ttype) = NULL_TREE; }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 513 "parse.y"
    { (yyval.ttype) = process_template_parm (NULL_TREE, (yyvsp[(1) - (1)].ttype)); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 515 "parse.y"
    { (yyval.ttype) = process_template_parm ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 520 "parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 522 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 526 "parse.y"
    { (yyval.ttype) = finish_template_type_parm ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 528 "parse.y"
    { (yyval.ttype) = finish_template_type_parm (class_type_node, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 533 "parse.y"
    { (yyval.ttype) = finish_template_template_parm ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 545 "parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ttype)); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 547 "parse.y"
    { (yyval.ttype) = build_tree_list (groktypename ((yyvsp[(3) - (3)].ftype).t), (yyvsp[(1) - (3)].ttype)); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 549 "parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ftype).t); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 551 "parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(3) - (3)].ttype), (yyvsp[(1) - (3)].ftype).t); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 553 "parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ttype)); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 555 "parse.y"
    {
		  if (TREE_CODE ((yyvsp[(3) - (3)].ttype)) != TEMPLATE_DECL
		      && TREE_CODE ((yyvsp[(3) - (3)].ttype)) != TEMPLATE_TEMPLATE_PARM
		      && TREE_CODE ((yyvsp[(3) - (3)].ttype)) != TYPE_DECL)
		    {
		      error ("invalid default template argument");
		      (yyvsp[(3) - (3)].ttype) = error_mark_node;
		    }
		  (yyval.ttype) = build_tree_list ((yyvsp[(3) - (3)].ttype), (yyvsp[(1) - (3)].ttype));
		}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 569 "parse.y"
    { finish_template_decl ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 571 "parse.y"
    { finish_template_decl ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 576 "parse.y"
    { if (pending_inlines) do_pending_inlines (); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 578 "parse.y"
    { if (pending_inlines) do_pending_inlines (); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 580 "parse.y"
    { if (pending_inlines) do_pending_inlines (); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 582 "parse.y"
    { if (pending_inlines) do_pending_inlines ();
		  pop_lang_context (); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 585 "parse.y"
    { if (pending_inlines) do_pending_inlines ();
		  pop_lang_context (); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 588 "parse.y"
    { pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 594 "parse.y"
    {}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 596 "parse.y"
    { note_list_got_semicolon ((yyvsp[(1) - (3)].ftype).t); }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 598 "parse.y"
    { maybe_process_partial_specialization ((yyvsp[(1) - (2)].ftype).t);
		  note_got_semicolon ((yyvsp[(1) - (2)].ftype).t); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 605 "parse.y"
    {}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 607 "parse.y"
    { note_list_got_semicolon ((yyvsp[(1) - (3)].ftype).t); }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 609 "parse.y"
    { pedwarn ("empty declaration"); }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 612 "parse.y"
    {
		  tree t, attrs;
		  split_specs_attrs ((yyvsp[(1) - (2)].ftype).t, &t, &attrs);
		  shadow_tag (t);
		  note_list_got_semicolon ((yyvsp[(1) - (2)].ftype).t);
		}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 625 "parse.y"
    { (yyval.itype) = 0; }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 627 "parse.y"
    { (yyval.itype) = 1; }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 643 "parse.y"
    { finish_function (lineno, (int)(yyvsp[(3) - (4)].itype), 0); }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 645 "parse.y"
    { 
		  int nested = (hack_decl_function_context
				(current_function_decl) != NULL_TREE);
		  finish_function (lineno, (int)(yyvsp[(3) - (3)].itype), nested); 
		}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 651 "parse.y"
    { }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 656 "parse.y"
    { (yyval.ttype) = begin_constructor_declarator ((yyvsp[(1) - (3)].ttype), (yyvsp[(2) - (3)].ttype)); }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 658 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyvsp[(4) - (8)].ttype), (yyvsp[(5) - (8)].ttype), (yyvsp[(7) - (8)].ttype), (yyvsp[(8) - (8)].ttype)); }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 660 "parse.y"
    { (yyval.ttype) = begin_constructor_declarator ((yyvsp[(1) - (5)].ttype), (yyvsp[(2) - (5)].ttype)); 
		  (yyval.ttype) = make_call_declarator ((yyval.ttype), empty_parms (), (yyvsp[(4) - (5)].ttype), (yyvsp[(5) - (5)].ttype));
		}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 664 "parse.y"
    { (yyval.ttype) = begin_constructor_declarator ((yyvsp[(2) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 666 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyvsp[(5) - (9)].ttype), (yyvsp[(6) - (9)].ttype), (yyvsp[(8) - (9)].ttype), (yyvsp[(9) - (9)].ttype)); }
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 668 "parse.y"
    { (yyval.ttype) = begin_constructor_declarator ((yyvsp[(2) - (6)].ttype), (yyvsp[(3) - (6)].ttype));
		  (yyval.ttype) = make_call_declarator ((yyval.ttype), empty_parms (), (yyvsp[(5) - (6)].ttype), (yyvsp[(6) - (6)].ttype));
		}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 672 "parse.y"
    { (yyval.ttype) = begin_constructor_declarator ((yyvsp[(1) - (3)].ttype), (yyvsp[(2) - (3)].ttype)); }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 674 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyvsp[(4) - (8)].ttype), (yyvsp[(5) - (8)].ttype), (yyvsp[(7) - (8)].ttype), (yyvsp[(8) - (8)].ttype)); }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 676 "parse.y"
    { (yyval.ttype) = begin_constructor_declarator ((yyvsp[(1) - (5)].ttype), (yyvsp[(2) - (5)].ttype));
		  (yyval.ttype) = make_call_declarator ((yyval.ttype), empty_parms (), (yyvsp[(4) - (5)].ttype), (yyvsp[(5) - (5)].ttype));
		}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 680 "parse.y"
    { (yyval.ttype) = begin_constructor_declarator ((yyvsp[(2) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 682 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyvsp[(5) - (9)].ttype), (yyvsp[(6) - (9)].ttype), (yyvsp[(8) - (9)].ttype), (yyvsp[(9) - (9)].ttype)); }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 684 "parse.y"
    { (yyval.ttype) = begin_constructor_declarator ((yyvsp[(2) - (6)].ttype), (yyvsp[(3) - (6)].ttype)); 
		  (yyval.ttype) = make_call_declarator ((yyval.ttype), empty_parms (), (yyvsp[(5) - (6)].ttype), (yyvsp[(6) - (6)].ttype));
		}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 691 "parse.y"
    { if (!begin_function_definition ((yyvsp[(1) - (2)].ftype).t, (yyvsp[(2) - (2)].ttype)))
		    YYERROR1; }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 694 "parse.y"
    { if (!begin_function_definition ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)))
		    YYERROR1; }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 697 "parse.y"
    { if (!begin_function_definition (NULL_TREE, (yyvsp[(1) - (1)].ttype)))
		    YYERROR1; }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 700 "parse.y"
    { if (!begin_function_definition ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)))
		    YYERROR1; }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 703 "parse.y"
    { if (!begin_function_definition (NULL_TREE, (yyvsp[(1) - (1)].ttype)))
		    YYERROR1; }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 709 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyvsp[(1) - (6)].ttype), (yyvsp[(3) - (6)].ttype), (yyvsp[(5) - (6)].ttype), (yyvsp[(6) - (6)].ttype)); }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 711 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyvsp[(1) - (4)].ttype), empty_parms (), (yyvsp[(3) - (4)].ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 713 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyvsp[(1) - (6)].ttype), (yyvsp[(3) - (6)].ttype), (yyvsp[(5) - (6)].ttype), (yyvsp[(6) - (6)].ttype)); }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 715 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyvsp[(1) - (4)].ttype), empty_parms (), (yyvsp[(3) - (4)].ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 722 "parse.y"
    { tree specs, attrs;
		  split_specs_attrs ((yyvsp[(1) - (2)].ttype), &specs, &attrs);
		  attrs = build_tree_list (attrs, NULL_TREE);
		  (yyval.ttype) = start_method (specs, (yyvsp[(2) - (2)].ttype), attrs);
		 rest_of_mdef:
		  if (! (yyval.ttype))
		    YYERROR1;
		  if (yychar == YYEMPTY)
		    yychar = YYLEX;
		  reinit_parse_for_method (yychar, (yyval.ttype)); }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 733 "parse.y"
    { (yyval.ttype) = start_method (NULL_TREE, (yyvsp[(1) - (1)].ttype), NULL_TREE); 
		  goto rest_of_mdef; }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 736 "parse.y"
    { tree specs, attrs;
		  split_specs_attrs ((yyvsp[(1) - (2)].ftype).t, &specs, &attrs);
		  attrs = build_tree_list (attrs, NULL_TREE);
		  (yyval.ttype) = start_method (specs, (yyvsp[(2) - (2)].ttype), attrs); goto rest_of_mdef; }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 741 "parse.y"
    { tree specs, attrs;
		  split_specs_attrs ((yyvsp[(1) - (2)].ttype), &specs, &attrs);
		  attrs = build_tree_list (attrs, NULL_TREE);
		  (yyval.ttype) = start_method (specs, (yyvsp[(2) - (2)].ttype), attrs); goto rest_of_mdef; }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 746 "parse.y"
    { (yyval.ttype) = start_method (NULL_TREE, (yyval.ttype), NULL_TREE); 
		  goto rest_of_mdef; }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 749 "parse.y"
    { tree specs, attrs;
		  split_specs_attrs ((yyvsp[(1) - (2)].ttype), &specs, &attrs);
		  attrs = build_tree_list (attrs, NULL_TREE);
		  (yyval.ttype) = start_method (specs, (yyvsp[(2) - (2)].ttype), attrs); goto rest_of_mdef; }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 754 "parse.y"
    { (yyval.ttype) = start_method (NULL_TREE, (yyval.ttype), NULL_TREE); 
		  goto rest_of_mdef; }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 760 "parse.y"
    {
		  if (! current_function_parms_stored)
		    store_parm_decls ();
		  (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 769 "parse.y"
    { store_return_init ((yyval.ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 771 "parse.y"
    { store_return_init ((yyval.ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 773 "parse.y"
    { store_return_init ((yyval.ttype), NULL_TREE); }
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 778 "parse.y"
    {
		  if ((yyvsp[(3) - (3)].itype) == 0)
		    error ("no base initializers given following ':'");
		  setup_vtbl_ptr ();
		  /* Always keep the BLOCK node associated with the outermost
		     pair of curley braces of a function.  These are needed
		     for correct operation of dwarfout.c.  */
		  keep_next_level ();
		}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 791 "parse.y"
    {
		  if (! current_function_parms_stored)
		    store_parm_decls ();

		  if (DECL_CONSTRUCTOR_P (current_function_decl))
		    {
		      /* Make a contour for the initializer list.  */
		      pushlevel (0);
		      clear_last_expr ();
		      expand_start_bindings (0);
		    }
		  else if (current_class_type == NULL_TREE)
		    error ("base initializers not allowed for non-member functions");
		  else if (! DECL_CONSTRUCTOR_P (current_function_decl))
		    error ("only constructors take base initializers");
		}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 811 "parse.y"
    { (yyval.itype) = 0; }
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 813 "parse.y"
    { (yyval.itype) = 1; }
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 820 "parse.y"
    {
		  if (current_class_name)
		    pedwarn ("anachronistic old style base class initializer");
		  expand_member_init (current_class_ref, NULL_TREE, (yyvsp[(2) - (3)].ttype));
		}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 826 "parse.y"
    {
		  if (current_class_name)
		    pedwarn ("anachronistic old style base class initializer");
		  expand_member_init (current_class_ref, NULL_TREE, void_type_node);
		}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 832 "parse.y"
    { expand_member_init (current_class_ref, (yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 834 "parse.y"
    { expand_member_init (current_class_ref, (yyvsp[(1) - (2)].ttype), void_type_node); }
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 836 "parse.y"
    { expand_member_init (current_class_ref, (yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 838 "parse.y"
    { expand_member_init (current_class_ref, (yyvsp[(1) - (2)].ttype), void_type_node); }
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 840 "parse.y"
    { expand_member_init (current_class_ref, TYPE_MAIN_DECL ((yyvsp[(1) - (4)].ttype)),
				      (yyvsp[(3) - (4)].ttype)); }
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 843 "parse.y"
    { expand_member_init (current_class_ref, TYPE_MAIN_DECL ((yyvsp[(1) - (2)].ttype)),
				      void_type_node); }
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 869 "parse.y"
    { do_type_instantiation ((yyvsp[(3) - (4)].ftype).t, NULL_TREE);
		  yyungetc (';', 1); }
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 873 "parse.y"
    { tree specs = strip_attrs ((yyvsp[(3) - (4)].ftype).t);
		  do_decl_instantiation (specs, (yyvsp[(4) - (4)].ttype), NULL_TREE); }
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 877 "parse.y"
    { do_decl_instantiation (NULL_TREE, (yyvsp[(3) - (3)].ttype), NULL_TREE); }
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 880 "parse.y"
    { do_decl_instantiation (NULL_TREE, (yyvsp[(3) - (3)].ttype), NULL_TREE); }
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 883 "parse.y"
    { do_type_instantiation ((yyvsp[(4) - (5)].ftype).t, (yyvsp[(1) - (5)].ttype));
		  yyungetc (';', 1); }
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 888 "parse.y"
    { tree specs = strip_attrs ((yyvsp[(4) - (5)].ftype).t);
		  do_decl_instantiation (specs, (yyvsp[(5) - (5)].ttype), (yyvsp[(1) - (5)].ttype)); }
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 892 "parse.y"
    { do_decl_instantiation (NULL_TREE, (yyvsp[(4) - (4)].ttype), (yyvsp[(1) - (4)].ttype)); }
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 895 "parse.y"
    { do_decl_instantiation (NULL_TREE, (yyvsp[(4) - (4)].ttype), (yyvsp[(1) - (4)].ttype)); }
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 900 "parse.y"
    { begin_explicit_instantiation(); }
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 903 "parse.y"
    { end_explicit_instantiation(); }
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 912 "parse.y"
    { (yyval.ttype) = (yyvsp[(5) - (5)].ttype); }
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 915 "parse.y"
    { (yyval.ttype) = (yyvsp[(5) - (5)].ttype); }
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 923 "parse.y"
    { (yyval.ttype) = (yyvsp[(5) - (5)].ttype); }
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 928 "parse.y"
    { (yyval.ttype) = (yyvsp[(5) - (5)].ttype); }
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 932 "parse.y"
    { 
		  if (yychar == YYEMPTY)
		    yychar = YYLEX;

		  (yyval.ttype) = finish_template_type ((yyvsp[(-3) - (0)].ttype), (yyvsp[(-1) - (0)].ttype), 
					     yychar == SCOPE);
		}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 943 "parse.y"
    {
		  /* Handle `Class<Class<Type>>' without space in the `>>' */
		  pedwarn ("`>>' should be `> >' in template class name");
		  yyungetc ('>', 1);
		}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 952 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 958 "parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyval.ttype)); }
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 960 "parse.y"
    { (yyval.ttype) = chainon ((yyval.ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (3)].ttype))); }
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 965 "parse.y"
    { (yyval.ttype) = groktypename ((yyvsp[(1) - (1)].ftype).t); }
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 967 "parse.y"
    { (yyval.ttype) = lastiddecl; }
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 973 "parse.y"
    { (yyval.code) = NEGATE_EXPR; }
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 975 "parse.y"
    { (yyval.code) = CONVERT_EXPR; }
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 977 "parse.y"
    { (yyval.code) = PREINCREMENT_EXPR; }
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 979 "parse.y"
    { (yyval.code) = PREDECREMENT_EXPR; }
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 981 "parse.y"
    { (yyval.code) = TRUTH_NOT_EXPR; }
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 986 "parse.y"
    { (yyval.ttype) = build_x_compound_expr ((yyval.ttype)); }
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 992 "parse.y"
    { error ("ANSI C++ forbids an empty condition for `%s'",
			 cond_stmt_keyword);
		  (yyval.ttype) = integer_zero_node; }
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 996 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1001 "parse.y"
    { error ("ANSI C++ forbids an empty condition for `%s'",
			 cond_stmt_keyword);
		  (yyval.ttype) = integer_zero_node; }
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1005 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1010 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1013 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1018 "parse.y"
    { {
		  tree d;
		  for (d = getdecls (); d; d = TREE_CHAIN (d))
		    if (TREE_CODE (d) == TYPE_DECL) {
		      tree s = TREE_TYPE (d);
		      if (TREE_CODE (s) == RECORD_TYPE)
			cp_error ("definition of class `%T' in condition", s);
		      else if (TREE_CODE (s) == ENUMERAL_TYPE)
			cp_error ("definition of enum `%T' in condition", s);
		    }
		  }
		  current_declspecs = (yyvsp[(1) - (5)].ftype).t;
		  (yyvsp[(5) - (5)].itype) = suspend_momentary ();
		  (yyval.ttype) = start_decl ((yyvsp[(2) - (5)].ttype), current_declspecs, 1,
					  (yyvsp[(4) - (5)].ttype), /*prefix_attributes*/ NULL_TREE);
		}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1035 "parse.y"
    { 
		  cp_finish_decl ((yyvsp[(6) - (7)].ttype), (yyvsp[(7) - (7)].ttype), (yyvsp[(4) - (7)].ttype), 1, LOOKUP_ONLYCONVERTING);
		  resume_momentary ((yyvsp[(5) - (7)].itype));
		  (yyval.ttype) = convert_from_reference ((yyvsp[(6) - (7)].ttype)); 
		  if (TREE_CODE (TREE_TYPE ((yyval.ttype))) == ARRAY_TYPE)
		    cp_error ("definition of array `%#D' in condition", (yyval.ttype)); 
		}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1054 "parse.y"
    { (yyval.ttype) = begin_compound_stmt (1); }
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1056 "parse.y"
    { finish_compound_stmt (1, (yyvsp[(2) - (3)].ttype)); }
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1063 "parse.y"
    { (yyval.ttype) = expr_tree_cons (NULL_TREE, (yyval.ttype), 
		                  build_expr_list (NULL_TREE, (yyvsp[(3) - (3)].ttype))); }
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1066 "parse.y"
    { (yyval.ttype) = expr_tree_cons (NULL_TREE, (yyval.ttype), 
		                  build_expr_list (NULL_TREE, error_mark_node)); }
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1069 "parse.y"
    { chainon ((yyval.ttype), build_expr_list (NULL_TREE, (yyvsp[(3) - (3)].ttype))); }
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1071 "parse.y"
    { chainon ((yyval.ttype), build_expr_list (NULL_TREE, error_mark_node)); }
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1076 "parse.y"
    { (yyval.ttype) = build_expr_list (NULL_TREE, (yyval.ttype)); }
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1082 "parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1085 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1088 "parse.y"
    { (yyval.ttype) = build_x_indirect_ref ((yyvsp[(2) - (2)].ttype), "unary *"); }
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1090 "parse.y"
    { (yyval.ttype) = build_x_unary_op (ADDR_EXPR, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1092 "parse.y"
    { (yyval.ttype) = build_x_unary_op (BIT_NOT_EXPR, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1094 "parse.y"
    { (yyval.ttype) = finish_unary_op_expr ((yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1097 "parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C++ forbids `&&'");
  		  (yyval.ttype) = finish_label_address_expr ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1101 "parse.y"
    { (yyval.ttype) = expr_sizeof ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1103 "parse.y"
    { (yyval.ttype) = c_sizeof (groktypename ((yyvsp[(3) - (4)].ftype).t));
		  check_for_new_type ("sizeof", (yyvsp[(3) - (4)].ftype)); }
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1106 "parse.y"
    { (yyval.ttype) = grok_alignof ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1108 "parse.y"
    { (yyval.ttype) = c_alignof (groktypename ((yyvsp[(3) - (4)].ftype).t)); 
		  check_for_new_type ("alignof", (yyvsp[(3) - (4)].ftype)); }
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1114 "parse.y"
    { (yyval.ttype) = build_new (NULL_TREE, (yyvsp[(2) - (2)].ftype).t, NULL_TREE, (yyvsp[(1) - (2)].itype)); 
		  check_for_new_type ("new", (yyvsp[(2) - (2)].ftype)); }
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1117 "parse.y"
    { (yyval.ttype) = build_new (NULL_TREE, (yyvsp[(2) - (3)].ftype).t, (yyvsp[(3) - (3)].ttype), (yyvsp[(1) - (3)].itype)); 
		  check_for_new_type ("new", (yyvsp[(2) - (3)].ftype)); }
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1120 "parse.y"
    { (yyval.ttype) = build_new ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ftype).t, NULL_TREE, (yyvsp[(1) - (3)].itype)); 
		  check_for_new_type ("new", (yyvsp[(3) - (3)].ftype)); }
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 1123 "parse.y"
    { (yyval.ttype) = build_new ((yyvsp[(2) - (4)].ttype), (yyvsp[(3) - (4)].ftype).t, (yyvsp[(4) - (4)].ttype), (yyvsp[(1) - (4)].itype)); 
		  check_for_new_type ("new", (yyvsp[(3) - (4)].ftype)); }
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1136 "parse.y"
    { (yyval.ttype) = build_new (NULL_TREE, groktypename((yyvsp[(4) - (5)].ftype).t),
				  NULL_TREE, (yyvsp[(1) - (5)].itype)); 
		  check_for_new_type ("new", (yyvsp[(4) - (5)].ftype)); }
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1141 "parse.y"
    { (yyval.ttype) = build_new (NULL_TREE, groktypename((yyvsp[(4) - (6)].ftype).t), (yyvsp[(6) - (6)].ttype), (yyvsp[(1) - (6)].itype)); 
		  check_for_new_type ("new", (yyvsp[(4) - (6)].ftype)); }
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1145 "parse.y"
    { (yyval.ttype) = build_new ((yyvsp[(2) - (6)].ttype), groktypename((yyvsp[(5) - (6)].ftype).t), NULL_TREE, (yyvsp[(1) - (6)].itype)); 
		  check_for_new_type ("new", (yyvsp[(5) - (6)].ftype)); }
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1149 "parse.y"
    { (yyval.ttype) = build_new ((yyvsp[(2) - (7)].ttype), groktypename((yyvsp[(5) - (7)].ftype).t), (yyvsp[(7) - (7)].ttype), (yyvsp[(1) - (7)].itype)); 
		  check_for_new_type ("new", (yyvsp[(5) - (7)].ftype)); }
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1153 "parse.y"
    { (yyval.ttype) = delete_sanity ((yyvsp[(2) - (2)].ttype), NULL_TREE, 0, (yyvsp[(1) - (2)].itype)); }
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1155 "parse.y"
    { (yyval.ttype) = delete_sanity ((yyvsp[(4) - (4)].ttype), NULL_TREE, 1, (yyvsp[(1) - (4)].itype));
		  if (yychar == YYEMPTY)
		    yychar = YYLEX; }
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1159 "parse.y"
    { (yyval.ttype) = delete_sanity ((yyvsp[(5) - (5)].ttype), (yyvsp[(3) - (5)].ttype), 2, (yyvsp[(1) - (5)].itype));
		  if (yychar == YYEMPTY)
		    yychar = YYLEX; }
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 1163 "parse.y"
    { (yyval.ttype) = build_x_unary_op (REALPART_EXPR, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 1165 "parse.y"
    { (yyval.ttype) = build_x_unary_op (IMAGPART_EXPR, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 1175 "parse.y"
    { finish_new_placement (NULL_TREE, (yyvsp[(-1) - (1)].itype)); }
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 1178 "parse.y"
    { (yyval.itype) = begin_new_placement (); }
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 1182 "parse.y"
    { (yyval.ttype) = finish_new_placement ((yyvsp[(3) - (4)].ttype), (yyvsp[(2) - (4)].itype)); }
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 1184 "parse.y"
    { cp_pedwarn ("old style placement syntax, use () instead");
		  (yyval.ttype) = finish_new_placement ((yyvsp[(3) - (4)].ttype), (yyvsp[(2) - (4)].itype)); }
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1190 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1192 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 1194 "parse.y"
    {
		  cp_error ("`%T' is not a valid expression", (yyvsp[(2) - (3)].ftype).t);
		  (yyval.ttype) = error_mark_node;
		}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 1202 "parse.y"
    {
		  if (pedantic)
		    pedwarn ("ANSI C++ forbids initialization of new expression with `='");
		  if (TREE_CODE ((yyvsp[(2) - (2)].ttype)) != TREE_LIST
		      && TREE_CODE ((yyvsp[(2) - (2)].ttype)) != CONSTRUCTOR)
		    (yyval.ttype) = build_expr_list (NULL_TREE, (yyvsp[(2) - (2)].ttype));
		  else
		    (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 1216 "parse.y"
    { (yyvsp[(2) - (3)].ftype).t = finish_parmlist (build_tree_list (NULL_TREE, (yyvsp[(2) - (3)].ftype).t), 0);
		  (yyval.ttype) = make_call_declarator (NULL_TREE, (yyvsp[(2) - (3)].ftype).t, NULL_TREE, NULL_TREE);
		  check_for_new_type ("cast", (yyvsp[(2) - (3)].ftype)); }
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 1220 "parse.y"
    { (yyvsp[(3) - (4)].ftype).t = finish_parmlist (build_tree_list (NULL_TREE, (yyvsp[(3) - (4)].ftype).t), 0); 
		  (yyval.ttype) = make_call_declarator ((yyval.ttype), (yyvsp[(3) - (4)].ftype).t, NULL_TREE, NULL_TREE);
		  check_for_new_type ("cast", (yyvsp[(3) - (4)].ftype)); }
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 1228 "parse.y"
    { (yyval.ttype) = reparse_absdcl_as_casts ((yyval.ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 1230 "parse.y"
    { 
		  tree init = build_nt (CONSTRUCTOR, NULL_TREE,
					nreverse ((yyvsp[(3) - (5)].ttype))); 
		  if (pedantic)
		    pedwarn ("ANSI C++ forbids constructor-expressions");
		  /* Indicate that this was a GNU C constructor expression.  */
		  TREE_HAS_CONSTRUCTOR (init) = 1;

		  (yyval.ttype) = reparse_absdcl_as_casts ((yyval.ttype), init);
		}
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 1246 "parse.y"
    { (yyval.ttype) = build_x_binary_op (MEMBER_REF, (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 255:
/* Line 1792 of yacc.c  */
#line 1248 "parse.y"
    { (yyval.ttype) = build_m_component_ref ((yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 1250 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 1252 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 258:
/* Line 1792 of yacc.c  */
#line 1254 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 1256 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 260:
/* Line 1792 of yacc.c  */
#line 1258 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 1260 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 1262 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 1264 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 1266 "parse.y"
    { (yyval.ttype) = build_x_binary_op (LT_EXPR, (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 1268 "parse.y"
    { (yyval.ttype) = build_x_binary_op (GT_EXPR, (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 1270 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 1272 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 1274 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 269:
/* Line 1792 of yacc.c  */
#line 1276 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 270:
/* Line 1792 of yacc.c  */
#line 1278 "parse.y"
    { (yyval.ttype) = build_x_binary_op ((yyvsp[(2) - (3)].code), (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 1280 "parse.y"
    { (yyval.ttype) = build_x_binary_op (TRUTH_ANDIF_EXPR, (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 272:
/* Line 1792 of yacc.c  */
#line 1282 "parse.y"
    { (yyval.ttype) = build_x_binary_op (TRUTH_ORIF_EXPR, (yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 273:
/* Line 1792 of yacc.c  */
#line 1284 "parse.y"
    { (yyval.ttype) = build_x_conditional_expr ((yyval.ttype), (yyvsp[(3) - (5)].ttype), (yyvsp[(5) - (5)].ttype)); }
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 1286 "parse.y"
    { (yyval.ttype) = build_x_modify_expr ((yyval.ttype), NOP_EXPR, (yyvsp[(3) - (3)].ttype));
		  if ((yyval.ttype) != error_mark_node)
                    C_SET_EXP_ORIGINAL_CODE ((yyval.ttype), MODIFY_EXPR); }
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 1290 "parse.y"
    { (yyval.ttype) = build_x_modify_expr ((yyval.ttype), (yyvsp[(2) - (3)].code), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 1292 "parse.y"
    { (yyval.ttype) = build_throw (NULL_TREE); }
    break;

  case 277:
/* Line 1792 of yacc.c  */
#line 1294 "parse.y"
    { (yyval.ttype) = build_throw ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 278:
/* Line 1792 of yacc.c  */
#line 1312 "parse.y"
    { (yyval.ttype) = build_parse_node (BIT_NOT_EXPR, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 1314 "parse.y"
    { (yyval.ttype) = build_parse_node (BIT_NOT_EXPR, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 285:
/* Line 1792 of yacc.c  */
#line 1323 "parse.y"
    {
		  /* If lastiddecl is a TREE_LIST, it's a baselink, which
		     means that we're in an expression like S::f<int>, so
		     don't do_identifier; we only do that for unqualified
		     identifiers.  */
		  if (lastiddecl && TREE_CODE (lastiddecl) != TREE_LIST)
		    (yyval.ttype) = do_identifier ((yyvsp[(-1) - (0)].ttype), 1, NULL_TREE);
		  else
		    (yyval.ttype) = (yyvsp[(-1) - (0)].ttype);
		}
    break;

  case 286:
/* Line 1792 of yacc.c  */
#line 1336 "parse.y"
    { (yyval.ttype) = lookup_template_function ((yyvsp[(3) - (5)].ttype), (yyvsp[(4) - (5)].ttype)); }
    break;

  case 287:
/* Line 1792 of yacc.c  */
#line 1338 "parse.y"
    { (yyval.ttype) = lookup_template_function ((yyvsp[(3) - (5)].ttype), (yyvsp[(4) - (5)].ttype)); }
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 1343 "parse.y"
    { (yyval.ttype) = lookup_template_function ((yyvsp[(2) - (5)].ttype), (yyvsp[(4) - (5)].ttype)); }
    break;

  case 289:
/* Line 1792 of yacc.c  */
#line 1345 "parse.y"
    { (yyval.ttype) = lookup_template_function ((yyvsp[(2) - (5)].ttype), (yyvsp[(4) - (5)].ttype)); }
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 1348 "parse.y"
    { (yyval.ttype) = lookup_template_function ((yyvsp[(2) - (5)].ttype), (yyvsp[(4) - (5)].ttype)); }
    break;

  case 295:
/* Line 1792 of yacc.c  */
#line 1360 "parse.y"
    {
		  /* Provide support for '(' attributes '*' declarator ')'
		     etc */
		  (yyval.ttype) = decl_tree_cons ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype), NULL_TREE);
		}
    break;

  case 297:
/* Line 1792 of yacc.c  */
#line 1370 "parse.y"
    { (yyval.ttype) = build_parse_node (INDIRECT_REF, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 298:
/* Line 1792 of yacc.c  */
#line 1372 "parse.y"
    { (yyval.ttype) = build_parse_node (ADDR_EXPR, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 299:
/* Line 1792 of yacc.c  */
#line 1374 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 300:
/* Line 1792 of yacc.c  */
#line 1379 "parse.y"
    { (yyval.ttype) = lookup_template_function ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 301:
/* Line 1792 of yacc.c  */
#line 1381 "parse.y"
    { (yyval.ttype) = lookup_template_function ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 305:
/* Line 1792 of yacc.c  */
#line 1391 "parse.y"
    { (yyval.ttype) = finish_decl_parsing ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 306:
/* Line 1792 of yacc.c  */
#line 1396 "parse.y"
    {
		  if (TREE_CODE ((yyvsp[(1) - (1)].ttype)) == BIT_NOT_EXPR)
		    (yyval.ttype) = build_x_unary_op (BIT_NOT_EXPR, TREE_OPERAND ((yyvsp[(1) - (1)].ttype), 0));
		  else 
		    (yyval.ttype) = finish_id_expr ((yyvsp[(1) - (1)].ttype));
		}
    break;

  case 309:
/* Line 1792 of yacc.c  */
#line 1405 "parse.y"
    {
		  if (processing_template_decl)
		    push_obstacks (&permanent_obstack, &permanent_obstack);
		  (yyval.ttype) = combine_strings ((yyval.ttype));
		  /* combine_strings doesn't set up TYPE_MAIN_VARIANT of
		     a const array the way we want, so fix it.  */
		  if (flag_const_strings)
		    TREE_TYPE ((yyval.ttype)) = build_cplus_array_type
		      (TREE_TYPE (TREE_TYPE ((yyval.ttype))),
		       TYPE_DOMAIN (TREE_TYPE ((yyval.ttype))));
		  if (processing_template_decl)
		    pop_obstacks ();
		}
    break;

  case 310:
/* Line 1792 of yacc.c  */
#line 1419 "parse.y"
    { (yyval.ttype) = finish_parenthesized_expr ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 311:
/* Line 1792 of yacc.c  */
#line 1421 "parse.y"
    { (yyvsp[(2) - (3)].ttype) = reparse_decl_as_expr (NULL_TREE, (yyvsp[(2) - (3)].ttype));
		  (yyval.ttype) = finish_parenthesized_expr ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 1424 "parse.y"
    { (yyval.ttype) = error_mark_node; }
    break;

  case 313:
/* Line 1792 of yacc.c  */
#line 1426 "parse.y"
    { tree scope = current_scope ();
		  if (!scope || TREE_CODE (scope) != FUNCTION_DECL)
		    {
		      error ("braced-group within expression allowed only inside a function");
		      YYERROR;
		    }
		  if (pedantic)
		    pedwarn ("ANSI C++ forbids braced-groups within expressions");  
		  (yyval.ttype) = begin_stmt_expr (); 
		}
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 1437 "parse.y"
    { (yyval.ttype) = finish_stmt_expr ((yyvsp[(2) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 315:
/* Line 1792 of yacc.c  */
#line 1442 "parse.y"
    { (yyval.ttype) = finish_call_expr ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype), 1); }
    break;

  case 316:
/* Line 1792 of yacc.c  */
#line 1444 "parse.y"
    { (yyval.ttype) = finish_call_expr ((yyvsp[(1) - (2)].ttype), NULL_TREE, 1); }
    break;

  case 317:
/* Line 1792 of yacc.c  */
#line 1446 "parse.y"
    { (yyval.ttype) = finish_call_expr ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype), 0); }
    break;

  case 318:
/* Line 1792 of yacc.c  */
#line 1448 "parse.y"
    { (yyval.ttype) = finish_call_expr ((yyvsp[(1) - (2)].ttype), NULL_TREE, 0); }
    break;

  case 319:
/* Line 1792 of yacc.c  */
#line 1450 "parse.y"
    { (yyval.ttype) = grok_array_decl ((yyval.ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 320:
/* Line 1792 of yacc.c  */
#line 1452 "parse.y"
    { (yyval.ttype) = finish_increment_expr ((yyvsp[(1) - (2)].ttype), POSTINCREMENT_EXPR); }
    break;

  case 321:
/* Line 1792 of yacc.c  */
#line 1454 "parse.y"
    { (yyval.ttype) = finish_increment_expr ((yyvsp[(1) - (2)].ttype), POSTDECREMENT_EXPR); }
    break;

  case 322:
/* Line 1792 of yacc.c  */
#line 1457 "parse.y"
    { (yyval.ttype) = finish_this_expr (); }
    break;

  case 323:
/* Line 1792 of yacc.c  */
#line 1459 "parse.y"
    {
		  /* This is a C cast in C++'s `functional' notation
		     using the "implicit int" extension so that:
		     `const (3)' is equivalent to `const int (3)'.  */
		  tree type;

		  if ((yyvsp[(3) - (4)].ttype) == error_mark_node)
		    {
		      (yyval.ttype) = error_mark_node;
		      break;
		    }

		  type = cp_build_qualified_type (integer_type_node,
						  cp_type_qual_from_rid ((yyvsp[(1) - (4)].ttype)));
		  (yyval.ttype) = build_c_cast (type, build_compound_expr ((yyvsp[(3) - (4)].ttype)));
		}
    break;

  case 325:
/* Line 1792 of yacc.c  */
#line 1477 "parse.y"
    { tree type = groktypename ((yyvsp[(3) - (7)].ftype).t);
		  check_for_new_type ("dynamic_cast", (yyvsp[(3) - (7)].ftype));
		  (yyval.ttype) = build_dynamic_cast (type, (yyvsp[(6) - (7)].ttype)); }
    break;

  case 326:
/* Line 1792 of yacc.c  */
#line 1481 "parse.y"
    { tree type = groktypename ((yyvsp[(3) - (7)].ftype).t);
		  check_for_new_type ("static_cast", (yyvsp[(3) - (7)].ftype));
		  (yyval.ttype) = build_static_cast (type, (yyvsp[(6) - (7)].ttype)); }
    break;

  case 327:
/* Line 1792 of yacc.c  */
#line 1485 "parse.y"
    { tree type = groktypename ((yyvsp[(3) - (7)].ftype).t);
		  check_for_new_type ("reinterpret_cast", (yyvsp[(3) - (7)].ftype));
		  (yyval.ttype) = build_reinterpret_cast (type, (yyvsp[(6) - (7)].ttype)); }
    break;

  case 328:
/* Line 1792 of yacc.c  */
#line 1489 "parse.y"
    { tree type = groktypename ((yyvsp[(3) - (7)].ftype).t);
		  check_for_new_type ("const_cast", (yyvsp[(3) - (7)].ftype));
		  (yyval.ttype) = build_const_cast (type, (yyvsp[(6) - (7)].ttype)); }
    break;

  case 329:
/* Line 1792 of yacc.c  */
#line 1493 "parse.y"
    { (yyval.ttype) = build_x_typeid ((yyvsp[(3) - (4)].ttype)); }
    break;

  case 330:
/* Line 1792 of yacc.c  */
#line 1495 "parse.y"
    { tree type = groktypename ((yyvsp[(3) - (4)].ftype).t);
		  check_for_new_type ("typeid", (yyvsp[(3) - (4)].ftype));
		  (yyval.ttype) = get_typeid (TYPE_MAIN_VARIANT (type)); }
    break;

  case 331:
/* Line 1792 of yacc.c  */
#line 1499 "parse.y"
    { (yyval.ttype) = do_scoped_id ((yyvsp[(2) - (2)].ttype), 1); }
    break;

  case 332:
/* Line 1792 of yacc.c  */
#line 1501 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 333:
/* Line 1792 of yacc.c  */
#line 1503 "parse.y"
    {
		  got_scope = NULL_TREE;
		  if (TREE_CODE ((yyvsp[(2) - (2)].ttype)) == IDENTIFIER_NODE)
		    (yyval.ttype) = do_scoped_id ((yyvsp[(2) - (2)].ttype), 1);
		  else
		    (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		}
    break;

  case 334:
/* Line 1792 of yacc.c  */
#line 1511 "parse.y"
    { (yyval.ttype) = build_offset_ref (OP0 ((yyval.ttype)), OP1 ((yyval.ttype))); }
    break;

  case 335:
/* Line 1792 of yacc.c  */
#line 1513 "parse.y"
    { (yyval.ttype) = finish_qualified_call_expr ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 336:
/* Line 1792 of yacc.c  */
#line 1515 "parse.y"
    { (yyval.ttype) = finish_qualified_call_expr ((yyvsp[(1) - (2)].ttype), NULL_TREE); }
    break;

  case 337:
/* Line 1792 of yacc.c  */
#line 1517 "parse.y"
    { 
		  (yyval.ttype) = build_x_component_ref ((yyval.ttype), (yyvsp[(2) - (2)].ttype), NULL_TREE, 1); 
		}
    break;

  case 338:
/* Line 1792 of yacc.c  */
#line 1521 "parse.y"
    { (yyval.ttype) = finish_object_call_expr ((yyvsp[(2) - (5)].ttype), (yyvsp[(1) - (5)].ttype), (yyvsp[(4) - (5)].ttype)); }
    break;

  case 339:
/* Line 1792 of yacc.c  */
#line 1523 "parse.y"
    { (yyval.ttype) = finish_object_call_expr ((yyvsp[(2) - (3)].ttype), (yyvsp[(1) - (3)].ttype), NULL_TREE); }
    break;

  case 340:
/* Line 1792 of yacc.c  */
#line 1525 "parse.y"
    { (yyval.ttype) = build_x_component_ref ((yyval.ttype), (yyvsp[(2) - (2)].ttype), NULL_TREE, 1); }
    break;

  case 341:
/* Line 1792 of yacc.c  */
#line 1527 "parse.y"
    { if (processing_template_decl)
		    (yyval.ttype) = build_min_nt (COMPONENT_REF, (yyvsp[(1) - (2)].ttype), copy_to_permanent ((yyvsp[(2) - (2)].ttype)));
		  else
		    (yyval.ttype) = build_object_ref ((yyval.ttype), OP0 ((yyvsp[(2) - (2)].ttype)), OP1 ((yyvsp[(2) - (2)].ttype))); }
    break;

  case 342:
/* Line 1792 of yacc.c  */
#line 1532 "parse.y"
    { (yyval.ttype) = finish_object_call_expr ((yyvsp[(2) - (5)].ttype), (yyvsp[(1) - (5)].ttype), (yyvsp[(4) - (5)].ttype)); }
    break;

  case 343:
/* Line 1792 of yacc.c  */
#line 1534 "parse.y"
    { (yyval.ttype) = finish_object_call_expr ((yyvsp[(2) - (3)].ttype), (yyvsp[(1) - (3)].ttype), NULL_TREE); }
    break;

  case 344:
/* Line 1792 of yacc.c  */
#line 1536 "parse.y"
    { (yyval.ttype) = finish_qualified_object_call_expr ((yyvsp[(2) - (5)].ttype), (yyvsp[(1) - (5)].ttype), (yyvsp[(4) - (5)].ttype)); }
    break;

  case 345:
/* Line 1792 of yacc.c  */
#line 1538 "parse.y"
    { (yyval.ttype) = finish_qualified_object_call_expr ((yyvsp[(2) - (3)].ttype), (yyvsp[(1) - (3)].ttype), NULL_TREE); }
    break;

  case 346:
/* Line 1792 of yacc.c  */
#line 1541 "parse.y"
    { (yyval.ttype) = finish_pseudo_destructor_call_expr ((yyvsp[(1) - (4)].ttype), NULL_TREE, (yyvsp[(3) - (4)].ttype)); }
    break;

  case 347:
/* Line 1792 of yacc.c  */
#line 1543 "parse.y"
    { (yyval.ttype) = finish_pseudo_destructor_call_expr ((yyvsp[(1) - (6)].ttype), (yyvsp[(2) - (6)].ttype), (yyvsp[(5) - (6)].ttype)); }
    break;

  case 348:
/* Line 1792 of yacc.c  */
#line 1545 "parse.y"
    {
		  (yyval.ttype) = error_mark_node;
		}
    break;

  case 349:
/* Line 1792 of yacc.c  */
#line 1590 "parse.y"
    { (yyval.itype) = 0; }
    break;

  case 350:
/* Line 1792 of yacc.c  */
#line 1592 "parse.y"
    { got_scope = NULL_TREE; (yyval.itype) = 1; }
    break;

  case 351:
/* Line 1792 of yacc.c  */
#line 1597 "parse.y"
    { (yyval.itype) = 0; }
    break;

  case 352:
/* Line 1792 of yacc.c  */
#line 1599 "parse.y"
    { got_scope = NULL_TREE; (yyval.itype) = 1; }
    break;

  case 353:
/* Line 1792 of yacc.c  */
#line 1604 "parse.y"
    { (yyval.ttype) = boolean_true_node; }
    break;

  case 354:
/* Line 1792 of yacc.c  */
#line 1606 "parse.y"
    { (yyval.ttype) = boolean_false_node; }
    break;

  case 356:
/* Line 1792 of yacc.c  */
#line 1613 "parse.y"
    { (yyval.ttype) = chainon ((yyval.ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 357:
/* Line 1792 of yacc.c  */
#line 1618 "parse.y"
    {
		  if (! current_function_parms_stored)
		    store_parm_decls ();
		  setup_vtbl_ptr ();
		  /* Always keep the BLOCK node associated with the outermost
		     pair of curley braces of a function.  These are needed
		     for correct operation of dwarfout.c.  */
		  keep_next_level ();
		}
    break;

  case 358:
/* Line 1792 of yacc.c  */
#line 1631 "parse.y"
    { got_object = TREE_TYPE ((yyval.ttype)); }
    break;

  case 359:
/* Line 1792 of yacc.c  */
#line 1633 "parse.y"
    {
		  (yyval.ttype) = build_x_arrow ((yyval.ttype)); 
		  got_object = TREE_TYPE ((yyval.ttype));
		}
    break;

  case 360:
/* Line 1792 of yacc.c  */
#line 1641 "parse.y"
    {
		  resume_momentary ((yyvsp[(2) - (3)].itype));
		  if ((yyvsp[(1) - (3)].ftype).t && IS_AGGR_TYPE_CODE (TREE_CODE ((yyvsp[(1) - (3)].ftype).t)))
		    note_got_semicolon ((yyvsp[(1) - (3)].ftype).t);
		}
    break;

  case 361:
/* Line 1792 of yacc.c  */
#line 1647 "parse.y"
    {
		  resume_momentary ((yyvsp[(2) - (3)].itype));
		  note_list_got_semicolon ((yyvsp[(1) - (3)].ftype).t);
		}
    break;

  case 362:
/* Line 1792 of yacc.c  */
#line 1652 "parse.y"
    { resume_momentary ((yyvsp[(2) - (3)].itype)); }
    break;

  case 363:
/* Line 1792 of yacc.c  */
#line 1654 "parse.y"
    {
		  shadow_tag ((yyvsp[(1) - (2)].ftype).t);
		  note_list_got_semicolon ((yyvsp[(1) - (2)].ftype).t);
		}
    break;

  case 364:
/* Line 1792 of yacc.c  */
#line 1659 "parse.y"
    { warning ("empty declaration"); }
    break;

  case 365:
/* Line 1792 of yacc.c  */
#line 1661 "parse.y"
    { pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 368:
/* Line 1792 of yacc.c  */
#line 1675 "parse.y"
    { (yyval.ttype) = make_call_declarator (NULL_TREE, empty_parms (),
					     NULL_TREE, NULL_TREE); }
    break;

  case 369:
/* Line 1792 of yacc.c  */
#line 1678 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyval.ttype), empty_parms (), NULL_TREE,
					     NULL_TREE); }
    break;

  case 370:
/* Line 1792 of yacc.c  */
#line 1685 "parse.y"
    { (yyval.ftype).t = build_decl_list ((yyvsp[(1) - (2)].ftype).t, (yyvsp[(2) - (2)].ttype)); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag; }
    break;

  case 371:
/* Line 1792 of yacc.c  */
#line 1688 "parse.y"
    { (yyval.ftype).t = build_decl_list ((yyvsp[(1) - (2)].ftype).t, (yyvsp[(2) - (2)].ttype)); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag; }
    break;

  case 372:
/* Line 1792 of yacc.c  */
#line 1691 "parse.y"
    { (yyval.ftype).t = build_decl_list (build_decl_list (NULL_TREE, (yyvsp[(1) - (2)].ftype).t),
					  (yyvsp[(2) - (2)].ttype)); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag; }
    break;

  case 373:
/* Line 1792 of yacc.c  */
#line 1695 "parse.y"
    { (yyval.ftype).t = build_decl_list ((yyvsp[(1) - (1)].ftype).t, NULL_TREE);
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (1)].ftype).new_type_flag;  }
    break;

  case 374:
/* Line 1792 of yacc.c  */
#line 1698 "parse.y"
    { (yyval.ftype).t = build_decl_list ((yyvsp[(1) - (1)].ftype).t, NULL_TREE); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (1)].ftype).new_type_flag; }
    break;

  case 377:
/* Line 1792 of yacc.c  */
#line 1714 "parse.y"
    { (yyval.ftype).t = decl_tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ftype).t, (yyvsp[(1) - (2)].ttype)); 
		  (yyval.ftype).new_type_flag = (yyvsp[(2) - (2)].ftype).new_type_flag; }
    break;

  case 378:
/* Line 1792 of yacc.c  */
#line 1717 "parse.y"
    { (yyval.ftype).t = decl_tree_cons (NULL_TREE, (yyvsp[(1) - (2)].ftype).t, (yyvsp[(2) - (2)].ttype)); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag; }
    break;

  case 379:
/* Line 1792 of yacc.c  */
#line 1720 "parse.y"
    { (yyval.ftype).t = decl_tree_cons (NULL_TREE, (yyvsp[(1) - (3)].ftype).t, chainon ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype))); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (3)].ftype).new_type_flag; }
    break;

  case 380:
/* Line 1792 of yacc.c  */
#line 1723 "parse.y"
    { (yyval.ftype).t = decl_tree_cons (NULL_TREE, (yyvsp[(2) - (3)].ftype).t, chainon ((yyvsp[(3) - (3)].ttype), (yyvsp[(1) - (3)].ttype))); 
		  (yyval.ftype).new_type_flag = (yyvsp[(2) - (3)].ftype).new_type_flag; }
    break;

  case 381:
/* Line 1792 of yacc.c  */
#line 1726 "parse.y"
    { (yyval.ftype).t = decl_tree_cons (NULL_TREE, (yyvsp[(2) - (3)].ftype).t, chainon ((yyvsp[(3) - (3)].ttype), (yyvsp[(1) - (3)].ttype))); 
		  (yyval.ftype).new_type_flag = (yyvsp[(2) - (3)].ftype).new_type_flag; }
    break;

  case 382:
/* Line 1792 of yacc.c  */
#line 1729 "parse.y"
    { (yyval.ftype).t = decl_tree_cons (NULL_TREE, (yyvsp[(2) - (4)].ftype).t,
					 chainon ((yyvsp[(3) - (4)].ttype), chainon ((yyvsp[(4) - (4)].ttype), (yyvsp[(1) - (4)].ttype)))); 
		  (yyval.ftype).new_type_flag = (yyvsp[(2) - (4)].ftype).new_type_flag; }
    break;

  case 383:
/* Line 1792 of yacc.c  */
#line 1736 "parse.y"
    { if (extra_warnings)
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyval.ttype)));
		  (yyval.ttype) = build_decl_list (NULL_TREE, (yyval.ttype)); }
    break;

  case 384:
/* Line 1792 of yacc.c  */
#line 1741 "parse.y"
    { (yyval.ttype) = decl_tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ftype).t, (yyval.ttype)); }
    break;

  case 385:
/* Line 1792 of yacc.c  */
#line 1743 "parse.y"
    { if (extra_warnings)
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyvsp[(2) - (2)].ttype)));
		  (yyval.ttype) = decl_tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyval.ttype)); }
    break;

  case 386:
/* Line 1792 of yacc.c  */
#line 1748 "parse.y"
    { (yyval.ttype) = decl_tree_cons ((yyvsp[(2) - (2)].ttype), NULL_TREE, (yyvsp[(1) - (2)].ttype)); }
    break;

  case 387:
/* Line 1792 of yacc.c  */
#line 1750 "parse.y"
    { (yyval.ttype) = decl_tree_cons ((yyvsp[(1) - (1)].ttype), NULL_TREE, NULL_TREE); }
    break;

  case 388:
/* Line 1792 of yacc.c  */
#line 1769 "parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ftype).t; TREE_STATIC ((yyval.ttype)) = 1; }
    break;

  case 389:
/* Line 1792 of yacc.c  */
#line 1771 "parse.y"
    { (yyval.ttype) = hash_tree_cons (NULL_TREE, (yyval.ttype), NULL_TREE); }
    break;

  case 390:
/* Line 1792 of yacc.c  */
#line 1773 "parse.y"
    { (yyval.ttype) = hash_tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyval.ttype));
		  TREE_STATIC ((yyval.ttype)) = 1; }
    break;

  case 391:
/* Line 1792 of yacc.c  */
#line 1776 "parse.y"
    { if (extra_warnings && TREE_STATIC ((yyval.ttype)))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyvsp[(2) - (2)].ttype)));
		  (yyval.ttype) = hash_tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyval.ttype));
		  TREE_STATIC ((yyval.ttype)) = TREE_STATIC ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 392:
/* Line 1792 of yacc.c  */
#line 1782 "parse.y"
    { (yyval.ttype) = hash_tree_cons ((yyvsp[(2) - (2)].ttype), NULL_TREE, (yyvsp[(1) - (2)].ttype)); }
    break;

  case 393:
/* Line 1792 of yacc.c  */
#line 1784 "parse.y"
    { (yyval.ttype) = hash_tree_cons ((yyvsp[(1) - (1)].ttype), NULL_TREE, NULL_TREE); }
    break;

  case 394:
/* Line 1792 of yacc.c  */
#line 1795 "parse.y"
    { (yyval.ftype).t = build_decl_list (NULL_TREE, (yyvsp[(1) - (1)].ftype).t); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (1)].ftype).new_type_flag; }
    break;

  case 395:
/* Line 1792 of yacc.c  */
#line 1798 "parse.y"
    { (yyval.ftype).t = decl_tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ftype).t, (yyvsp[(1) - (2)].ftype).t); 
		  (yyval.ftype).new_type_flag = (yyvsp[(2) - (2)].ftype).new_type_flag; }
    break;

  case 396:
/* Line 1792 of yacc.c  */
#line 1801 "parse.y"
    { (yyval.ftype).t = decl_tree_cons (NULL_TREE, (yyvsp[(1) - (2)].ftype).t, (yyvsp[(2) - (2)].ttype)); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag; }
    break;

  case 397:
/* Line 1792 of yacc.c  */
#line 1804 "parse.y"
    { (yyval.ftype).t = decl_tree_cons (NULL_TREE, (yyvsp[(2) - (3)].ftype).t, chainon ((yyvsp[(3) - (3)].ttype), (yyvsp[(1) - (3)].ftype).t)); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (3)].ftype).new_type_flag; }
    break;

  case 398:
/* Line 1792 of yacc.c  */
#line 1810 "parse.y"
    { (yyval.ttype) = build_decl_list (NULL_TREE, (yyvsp[(1) - (1)].ftype).t); }
    break;

  case 399:
/* Line 1792 of yacc.c  */
#line 1812 "parse.y"
    { (yyval.ttype) = decl_tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ftype).t, (yyvsp[(1) - (2)].ttype)); }
    break;

  case 401:
/* Line 1792 of yacc.c  */
#line 1822 "parse.y"
    { (yyval.ftype).t = (yyvsp[(1) - (1)].ttype); (yyval.ftype).new_type_flag = 0; }
    break;

  case 402:
/* Line 1792 of yacc.c  */
#line 1824 "parse.y"
    { (yyval.ftype).t = (yyvsp[(1) - (1)].ttype); (yyval.ftype).new_type_flag = 0; }
    break;

  case 403:
/* Line 1792 of yacc.c  */
#line 1826 "parse.y"
    { (yyval.ftype).t = finish_typeof ((yyvsp[(3) - (4)].ttype));
		  (yyval.ftype).new_type_flag = 0; }
    break;

  case 404:
/* Line 1792 of yacc.c  */
#line 1829 "parse.y"
    { (yyval.ftype).t = groktypename ((yyvsp[(3) - (4)].ftype).t);
		  (yyval.ftype).new_type_flag = 0; }
    break;

  case 405:
/* Line 1792 of yacc.c  */
#line 1832 "parse.y"
    { tree type = TREE_TYPE ((yyvsp[(3) - (4)].ttype));

                  (yyval.ftype).new_type_flag = 0;
		  if (IS_AGGR_TYPE (type))
		    {
		      sorry ("sigof type specifier");
		      (yyval.ftype).t = type;
		    }
		  else
		    {
		      error ("`sigof' applied to non-aggregate expression");
		      (yyval.ftype).t = error_mark_node;
		    }
		}
    break;

  case 406:
/* Line 1792 of yacc.c  */
#line 1847 "parse.y"
    { tree type = groktypename ((yyvsp[(3) - (4)].ftype).t);

                  (yyval.ftype).new_type_flag = 0;
		  if (IS_AGGR_TYPE (type))
		    {
		      sorry ("sigof type specifier");
		      (yyval.ftype).t = type;
		    }
		  else
		    {
		      error("`sigof' applied to non-aggregate type");
		      (yyval.ftype).t = error_mark_node;
		    }
		}
    break;

  case 407:
/* Line 1792 of yacc.c  */
#line 1867 "parse.y"
    { (yyval.ftype).t = (yyvsp[(1) - (1)].ttype); (yyval.ftype).new_type_flag = 0; }
    break;

  case 408:
/* Line 1792 of yacc.c  */
#line 1869 "parse.y"
    { (yyval.ftype).t = (yyvsp[(1) - (1)].ttype); (yyval.ftype).new_type_flag = 0; }
    break;

  case 411:
/* Line 1792 of yacc.c  */
#line 1876 "parse.y"
    { check_multiple_declarators (); }
    break;

  case 413:
/* Line 1792 of yacc.c  */
#line 1882 "parse.y"
    { check_multiple_declarators (); }
    break;

  case 415:
/* Line 1792 of yacc.c  */
#line 1888 "parse.y"
    { check_multiple_declarators (); }
    break;

  case 416:
/* Line 1792 of yacc.c  */
#line 1893 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 417:
/* Line 1792 of yacc.c  */
#line 1895 "parse.y"
    { if (TREE_CHAIN ((yyvsp[(3) - (4)].ttype))) (yyvsp[(3) - (4)].ttype) = combine_strings ((yyvsp[(3) - (4)].ttype)); (yyval.ttype) = (yyvsp[(3) - (4)].ttype); }
    break;

  case 418:
/* Line 1792 of yacc.c  */
#line 1900 "parse.y"
    { (yyval.ttype) = start_decl ((yyvsp[(1) - (4)].ttype), current_declspecs, 1,
					  (yyvsp[(3) - (4)].ttype), prefix_attributes); }
    break;

  case 419:
/* Line 1792 of yacc.c  */
#line 1904 "parse.y"
    { cp_finish_decl ((yyvsp[(5) - (6)].ttype), (yyvsp[(6) - (6)].ttype), (yyvsp[(2) - (6)].ttype), 1, LOOKUP_ONLYCONVERTING); }
    break;

  case 420:
/* Line 1792 of yacc.c  */
#line 1906 "parse.y"
    { (yyval.ttype) = start_decl ((yyvsp[(1) - (3)].ttype), current_declspecs, 0,
					  (yyvsp[(3) - (3)].ttype), prefix_attributes);
		  cp_finish_decl ((yyval.ttype), NULL_TREE, (yyvsp[(2) - (3)].ttype), 1, 0); }
    break;

  case 421:
/* Line 1792 of yacc.c  */
#line 1919 "parse.y"
    { (yyvsp[(2) - (2)].itype) = parse_decl ((yyvsp[(-1) - (2)].ttype), (yyvsp[(-2) - (2)].ttype), 
					   (yyvsp[(1) - (2)].ttype), 1, &(yyval.ttype)); }
    break;

  case 422:
/* Line 1792 of yacc.c  */
#line 1924 "parse.y"
    { cp_finish_decl ((yyvsp[(3) - (4)].ttype), (yyvsp[(4) - (4)].ttype), (yyvsp[(0) - (4)].ttype), 1,
				  LOOKUP_ONLYCONVERTING);
		  (yyval.itype) = (yyvsp[(2) - (4)].itype); }
    break;

  case 423:
/* Line 1792 of yacc.c  */
#line 1928 "parse.y"
    { tree d;
		  (yyval.itype) = parse_decl ((yyvsp[(-1) - (1)].ttype), (yyvsp[(-2) - (1)].ttype), (yyvsp[(1) - (1)].ttype), 0, &d);
		  cp_finish_decl (d, NULL_TREE, (yyvsp[(0) - (1)].ttype), 1, 0); }
    break;

  case 424:
/* Line 1792 of yacc.c  */
#line 1935 "parse.y"
    { (yyval.itype) = (yyvsp[(3) - (3)].itype); }
    break;

  case 425:
/* Line 1792 of yacc.c  */
#line 1939 "parse.y"
    { (yyval.itype) = (yyvsp[(3) - (3)].itype); }
    break;

  case 426:
/* Line 1792 of yacc.c  */
#line 1944 "parse.y"
    { /* Set things up as initdcl0_innards expects.  */
	      (yyvsp[(2) - (2)].ttype) = (yyvsp[(1) - (2)].ttype); 
              (yyvsp[(1) - (2)].ttype) = NULL_TREE; }
    break;

  case 427:
/* Line 1792 of yacc.c  */
#line 1948 "parse.y"
    {}
    break;

  case 428:
/* Line 1792 of yacc.c  */
#line 1950 "parse.y"
    { tree d;
		  parse_decl((yyvsp[(1) - (3)].ttype), NULL_TREE, (yyvsp[(3) - (3)].ttype), 0, &d);
		  cp_finish_decl (d, NULL_TREE, (yyvsp[(2) - (3)].ttype), 1, 0); }
    break;

  case 429:
/* Line 1792 of yacc.c  */
#line 1959 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 430:
/* Line 1792 of yacc.c  */
#line 1961 "parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 431:
/* Line 1792 of yacc.c  */
#line 1966 "parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 432:
/* Line 1792 of yacc.c  */
#line 1968 "parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 433:
/* Line 1792 of yacc.c  */
#line 1973 "parse.y"
    { (yyval.ttype) = (yyvsp[(4) - (6)].ttype); }
    break;

  case 434:
/* Line 1792 of yacc.c  */
#line 1978 "parse.y"
    { (yyval.ttype) = (yyvsp[(1) - (1)].ttype); }
    break;

  case 435:
/* Line 1792 of yacc.c  */
#line 1980 "parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 436:
/* Line 1792 of yacc.c  */
#line 1985 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 437:
/* Line 1792 of yacc.c  */
#line 1987 "parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (1)].ttype), NULL_TREE); }
    break;

  case 438:
/* Line 1792 of yacc.c  */
#line 1989 "parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (4)].ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (4)].ttype))); }
    break;

  case 439:
/* Line 1792 of yacc.c  */
#line 1991 "parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (6)].ttype), tree_cons (NULL_TREE, (yyvsp[(3) - (6)].ttype), (yyvsp[(5) - (6)].ttype))); }
    break;

  case 440:
/* Line 1792 of yacc.c  */
#line 1993 "parse.y"
    { (yyval.ttype) = build_tree_list ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 445:
/* Line 1792 of yacc.c  */
#line 2009 "parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ttype)); }
    break;

  case 446:
/* Line 1792 of yacc.c  */
#line 2011 "parse.y"
    { (yyval.ttype) = chainon ((yyvsp[(1) - (3)].ttype), build_tree_list (NULL_TREE, (yyvsp[(3) - (3)].ttype))); }
    break;

  case 447:
/* Line 1792 of yacc.c  */
#line 2016 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 448:
/* Line 1792 of yacc.c  */
#line 2018 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 450:
/* Line 1792 of yacc.c  */
#line 2026 "parse.y"
    { (yyval.ttype) = build_nt (CONSTRUCTOR, NULL_TREE, NULL_TREE);
		  TREE_HAS_CONSTRUCTOR ((yyval.ttype)) = 1; }
    break;

  case 451:
/* Line 1792 of yacc.c  */
#line 2029 "parse.y"
    { (yyval.ttype) = build_nt (CONSTRUCTOR, NULL_TREE, nreverse ((yyvsp[(2) - (3)].ttype)));
		  TREE_HAS_CONSTRUCTOR ((yyval.ttype)) = 1; }
    break;

  case 452:
/* Line 1792 of yacc.c  */
#line 2032 "parse.y"
    { (yyval.ttype) = build_nt (CONSTRUCTOR, NULL_TREE, nreverse ((yyvsp[(2) - (4)].ttype)));
		  TREE_HAS_CONSTRUCTOR ((yyval.ttype)) = 1; }
    break;

  case 453:
/* Line 1792 of yacc.c  */
#line 2035 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 454:
/* Line 1792 of yacc.c  */
#line 2042 "parse.y"
    { (yyval.ttype) = build_tree_list (NULL_TREE, (yyval.ttype)); }
    break;

  case 455:
/* Line 1792 of yacc.c  */
#line 2044 "parse.y"
    { (yyval.ttype) = expr_tree_cons (NULL_TREE, (yyvsp[(3) - (3)].ttype), (yyval.ttype)); }
    break;

  case 456:
/* Line 1792 of yacc.c  */
#line 2047 "parse.y"
    { (yyval.ttype) = build_expr_list ((yyvsp[(2) - (4)].ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 457:
/* Line 1792 of yacc.c  */
#line 2049 "parse.y"
    { (yyval.ttype) = build_expr_list ((yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 458:
/* Line 1792 of yacc.c  */
#line 2051 "parse.y"
    { (yyval.ttype) = expr_tree_cons ((yyvsp[(3) - (5)].ttype), (yyvsp[(5) - (5)].ttype), (yyval.ttype)); }
    break;

  case 459:
/* Line 1792 of yacc.c  */
#line 2056 "parse.y"
    { start_function (NULL_TREE, TREE_VALUE ((yyvsp[(1) - (1)].ttype)),
				  NULL_TREE, 2);
		  reinit_parse_for_function (); }
    break;

  case 460:
/* Line 1792 of yacc.c  */
#line 2062 "parse.y"
    {
		  int nested = (hack_decl_function_context
				(current_function_decl) != NULL_TREE);
		  finish_function (lineno, (int)(yyvsp[(3) - (4)].itype) | 2, nested);
		  process_next_inline ((yyvsp[(1) - (4)].ttype));
		}
    break;

  case 461:
/* Line 1792 of yacc.c  */
#line 2069 "parse.y"
    { 
		  int nested = (hack_decl_function_context
				(current_function_decl) != NULL_TREE);
		  finish_function (lineno, (int)(yyvsp[(3) - (3)].itype) | 2, nested); 
                  process_next_inline ((yyvsp[(1) - (3)].ttype));
		}
    break;

  case 462:
/* Line 1792 of yacc.c  */
#line 2076 "parse.y"
    { process_next_inline ((yyvsp[(1) - (3)].ttype)); }
    break;

  case 465:
/* Line 1792 of yacc.c  */
#line 2088 "parse.y"
    { replace_defarg ((yyvsp[(1) - (3)].ttype), (yyvsp[(2) - (3)].ttype)); }
    break;

  case 466:
/* Line 1792 of yacc.c  */
#line 2090 "parse.y"
    { replace_defarg ((yyvsp[(1) - (3)].ttype), error_mark_node); }
    break;

  case 468:
/* Line 1792 of yacc.c  */
#line 2095 "parse.y"
    { do_pending_defargs (); }
    break;

  case 469:
/* Line 1792 of yacc.c  */
#line 2097 "parse.y"
    { do_pending_defargs (); }
    break;

  case 470:
/* Line 1792 of yacc.c  */
#line 2102 "parse.y"
    { (yyvsp[(3) - (3)].itype) = suspend_momentary ();
		  (yyval.ttype) = current_enum_type;
		  current_enum_type = start_enum ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 471:
/* Line 1792 of yacc.c  */
#line 2106 "parse.y"
    { TYPE_VALUES (current_enum_type) = (yyvsp[(5) - (7)].ttype);
		  (yyval.ftype).t = finish_enum (current_enum_type);
		  (yyval.ftype).new_type_flag = 1;
		  current_enum_type = (yyvsp[(4) - (7)].ttype);
		  resume_momentary ((int) (yyvsp[(3) - (7)].itype));
		  check_for_missing_semicolon ((yyval.ftype).t); }
    break;

  case 472:
/* Line 1792 of yacc.c  */
#line 2113 "parse.y"
    { (yyval.ftype).t = finish_enum (start_enum ((yyvsp[(2) - (4)].ttype)));
		  (yyval.ftype).new_type_flag = 1;
		  check_for_missing_semicolon ((yyval.ftype).t); }
    break;

  case 473:
/* Line 1792 of yacc.c  */
#line 2117 "parse.y"
    { (yyvsp[(2) - (2)].itype) = suspend_momentary ();
		  (yyval.ttype) = current_enum_type;
		  current_enum_type = start_enum (make_anon_name ()); }
    break;

  case 474:
/* Line 1792 of yacc.c  */
#line 2121 "parse.y"
    { TYPE_VALUES (current_enum_type) = (yyvsp[(4) - (6)].ttype);
		  (yyval.ftype).t = finish_enum (current_enum_type);
		  (yyval.ftype).new_type_flag = 1;
		  current_enum_type = (yyvsp[(3) - (6)].ttype);
		  resume_momentary ((int) (yyvsp[(1) - (6)].itype));
		  check_for_missing_semicolon ((yyval.ftype).t); }
    break;

  case 475:
/* Line 1792 of yacc.c  */
#line 2128 "parse.y"
    { (yyval.ftype).t = finish_enum (start_enum (make_anon_name()));
		  (yyval.ftype).new_type_flag = 1;
		  check_for_missing_semicolon ((yyval.ftype).t); }
    break;

  case 476:
/* Line 1792 of yacc.c  */
#line 2132 "parse.y"
    { (yyval.ftype).t = xref_tag (enum_type_node, (yyvsp[(2) - (2)].ttype), 1); 
		  (yyval.ftype).new_type_flag = 0; }
    break;

  case 477:
/* Line 1792 of yacc.c  */
#line 2135 "parse.y"
    { (yyval.ftype).t = xref_tag (enum_type_node, (yyvsp[(2) - (2)].ttype), 1); 
		  (yyval.ftype).new_type_flag = 0; }
    break;

  case 478:
/* Line 1792 of yacc.c  */
#line 2138 "parse.y"
    { (yyval.ftype).t = (yyvsp[(2) - (2)].ttype);
		  (yyval.ftype).new_type_flag = 0; 
		  if (!processing_template_decl)
		    cp_pedwarn ("using `typename' outside of template"); }
    break;

  case 479:
/* Line 1792 of yacc.c  */
#line 2144 "parse.y"
    { (yyvsp[(1) - (2)].ftype).t = begin_class_definition ((yyvsp[(1) - (2)].ftype).t); }
    break;

  case 480:
/* Line 1792 of yacc.c  */
#line 2146 "parse.y"
    { 
		  int semi;

		  if (yychar == YYEMPTY)
		    yychar = YYLEX;
		  semi = yychar == ';';

		  (yyval.ttype) = finish_class_definition ((yyvsp[(1) - (6)].ftype).t, (yyvsp[(6) - (6)].ttype), semi,
						       (yyvsp[(1) - (6)].ftype).new_type_flag); 
		}
    break;

  case 481:
/* Line 1792 of yacc.c  */
#line 2157 "parse.y"
    {
		  begin_inline_definitions ();
		}
    break;

  case 482:
/* Line 1792 of yacc.c  */
#line 2161 "parse.y"
    {
		  finish_inline_definitions ();
		  (yyval.ftype).t = (yyvsp[(7) - (10)].ttype);
		  (yyval.ftype).new_type_flag = 1; 
		}
    break;

  case 483:
/* Line 1792 of yacc.c  */
#line 2167 "parse.y"
    {
		  if ((yyvsp[(1) - (1)].ftype).new_type_flag)
		    pop_scope (CP_DECL_CONTEXT (TYPE_MAIN_DECL ((yyvsp[(1) - (1)].ftype).t)));
		  (yyval.ftype).new_type_flag = 0;
		  if (TYPE_BINFO ((yyvsp[(1) - (1)].ftype).t) == NULL_TREE)
		    {
		      cp_error ("%T is not a class type", (yyvsp[(1) - (1)].ftype).t);
		      (yyval.ftype).t = error_mark_node;
		    } 
		  else
		    {
		      (yyval.ftype).t = (yyvsp[(1) - (1)].ftype).t;
		      /* struct B: public A; is not accepted by the WP grammar.  */
		      if (TYPE_BINFO_BASETYPES ((yyval.ftype).t) && !TYPE_SIZE ((yyval.ftype).t)
			  && ! TYPE_BEING_DEFINED ((yyval.ftype).t))
			cp_error ("base clause without member specification for `%#T'",
				  (yyval.ftype).t);
		    }
		}
    break;

  case 487:
/* Line 1792 of yacc.c  */
#line 2196 "parse.y"
    { if (pedantic && !in_system_header)
		    pedwarn ("comma at end of enumerator list"); }
    break;

  case 489:
/* Line 1792 of yacc.c  */
#line 2203 "parse.y"
    { error ("storage class specifier `%s' not allowed after struct or class", IDENTIFIER_POINTER ((yyvsp[(2) - (2)].ttype))); }
    break;

  case 490:
/* Line 1792 of yacc.c  */
#line 2205 "parse.y"
    { error ("type specifier `%s' not allowed after struct or class", IDENTIFIER_POINTER ((yyvsp[(2) - (2)].ttype))); }
    break;

  case 491:
/* Line 1792 of yacc.c  */
#line 2207 "parse.y"
    { error ("type qualifier `%s' not allowed after struct or class", IDENTIFIER_POINTER ((yyvsp[(2) - (2)].ttype))); }
    break;

  case 492:
/* Line 1792 of yacc.c  */
#line 2209 "parse.y"
    { error ("no body nor ';' separates two class, struct or union declarations"); }
    break;

  case 493:
/* Line 1792 of yacc.c  */
#line 2211 "parse.y"
    { (yyval.ttype) = build_decl_list ((yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ttype)); }
    break;

  case 494:
/* Line 1792 of yacc.c  */
#line 2216 "parse.y"
    { 
		  current_aggr = (yyvsp[(1) - (2)].ttype); 
		  (yyval.ttype) = (yyvsp[(2) - (2)].ttype); 
		}
    break;

  case 495:
/* Line 1792 of yacc.c  */
#line 2224 "parse.y"
    { current_aggr = (yyval.ttype); (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 496:
/* Line 1792 of yacc.c  */
#line 2226 "parse.y"
    { yyungetc ('{', 1); }
    break;

  case 497:
/* Line 1792 of yacc.c  */
#line 2228 "parse.y"
    { yyungetc (':', 1); }
    break;

  case 498:
/* Line 1792 of yacc.c  */
#line 2233 "parse.y"
    {
		  current_aggr = (yyvsp[(1) - (3)].ttype);
		  (yyval.ftype).t = handle_class_head ((yyvsp[(1) - (3)].ttype), (yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		  (yyval.ftype).new_type_flag = 1;
		}
    break;

  case 499:
/* Line 1792 of yacc.c  */
#line 2239 "parse.y"
    {
		  current_aggr = (yyvsp[(1) - (4)].ttype);
		  (yyval.ftype).t = handle_class_head ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype), (yyvsp[(4) - (4)].ttype));
		  (yyval.ftype).new_type_flag = 1;
		}
    break;

  case 500:
/* Line 1792 of yacc.c  */
#line 2245 "parse.y"
    {
		  current_aggr = (yyvsp[(1) - (3)].ttype);
		  (yyval.ftype).t = handle_class_head ((yyvsp[(1) - (3)].ttype), NULL_TREE, (yyvsp[(3) - (3)].ttype));
		  (yyval.ftype).new_type_flag = 1;
		}
    break;

  case 501:
/* Line 1792 of yacc.c  */
#line 2251 "parse.y"
    { 
		  current_aggr = (yyvsp[(1) - (2)].ttype); 
		  (yyval.ftype).t = (yyvsp[(2) - (2)].ttype);
		  (yyval.ftype).new_type_flag = 0;
		}
    break;

  case 502:
/* Line 1792 of yacc.c  */
#line 2257 "parse.y"
    { 
		  current_aggr = (yyvsp[(1) - (3)].ttype); 
		  (yyval.ftype).t = (yyvsp[(3) - (3)].ttype);
		  if (CP_DECL_CONTEXT ((yyval.ftype).t))
		    push_scope (CP_DECL_CONTEXT ((yyval.ftype).t));
		  (yyval.ftype).new_type_flag = 1;
		}
    break;

  case 503:
/* Line 1792 of yacc.c  */
#line 2268 "parse.y"
    { 
		  (yyval.ftype).t = xref_tag (current_aggr, (yyvsp[(1) - (1)].ttype), 1); 
		  (yyval.ftype).new_type_flag = 0;
		}
    break;

  case 504:
/* Line 1792 of yacc.c  */
#line 2273 "parse.y"
    { (yyval.ttype) = xref_tag (current_aggr, (yyvsp[(1) - (1)].ttype), 0); }
    break;

  case 505:
/* Line 1792 of yacc.c  */
#line 2277 "parse.y"
    { 
		  (yyval.ftype).t = (yyvsp[(2) - (3)].ttype);
		  (yyval.ftype).new_type_flag = 0;
		  if ((yyvsp[(3) - (3)].ttype))
                    xref_basetypes (current_aggr, (yyvsp[(1) - (3)].ttype), (yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); 
		}
    break;

  case 506:
/* Line 1792 of yacc.c  */
#line 2285 "parse.y"
    { 
		  if ((yyvsp[(1) - (2)].ftype).t != error_mark_node)
		    {
		      (yyval.ftype).t = TREE_TYPE ((yyvsp[(1) - (2)].ftype).t);
		      (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag;
		      if (current_aggr == union_type_node
			  && TREE_CODE ((yyval.ftype).t) != UNION_TYPE)
			cp_pedwarn ("`union' tag used in declaring `%#T'", 
				    (yyval.ftype).t);
		      else if (TREE_CODE ((yyval.ftype).t) == UNION_TYPE
			       && current_aggr != union_type_node)
			cp_pedwarn ("non-`union' tag used in declaring `%#T'", (yyval.ftype));
		      else if (TREE_CODE ((yyval.ftype).t) == RECORD_TYPE)
			/* We might be specializing a template with a different
			   class-key; deal.  */
			CLASSTYPE_DECLARED_CLASS ((yyval.ftype).t) 
			  = (current_aggr == class_type_node);
		      if ((yyvsp[(2) - (2)].ttype))
			{
			  maybe_process_partial_specialization ((yyval.ftype).t);
			  xref_basetypes (current_aggr, (yyvsp[(1) - (2)].ftype).t, (yyval.ftype).t, (yyvsp[(2) - (2)].ttype)); 
			}
		    }
		}
    break;

  case 507:
/* Line 1792 of yacc.c  */
#line 2313 "parse.y"
    { (yyval.ttype) = xref_tag ((yyval.ttype), make_anon_name (), 0);
		  yyungetc ('{', 1); }
    break;

  case 508:
/* Line 1792 of yacc.c  */
#line 2323 "parse.y"
    {
		  (yyval.ftype).t = (yyvsp[(1) - (1)].ttype);
		  (yyval.ftype).new_type_flag = 0;
		}
    break;

  case 510:
/* Line 1792 of yacc.c  */
#line 2332 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 511:
/* Line 1792 of yacc.c  */
#line 2334 "parse.y"
    { yyungetc(':', 1); (yyval.ttype) = NULL_TREE; }
    break;

  case 512:
/* Line 1792 of yacc.c  */
#line 2336 "parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 514:
/* Line 1792 of yacc.c  */
#line 2342 "parse.y"
    { (yyval.ttype) = chainon ((yyval.ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 515:
/* Line 1792 of yacc.c  */
#line 2347 "parse.y"
    { (yyval.ttype) = finish_base_specifier (access_default_node, (yyvsp[(1) - (1)].ttype),
					      current_aggr 
					      == signature_type_node); }
    break;

  case 516:
/* Line 1792 of yacc.c  */
#line 2351 "parse.y"
    { (yyval.ttype) = finish_base_specifier ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype), 
					      current_aggr 
					      == signature_type_node); }
    break;

  case 517:
/* Line 1792 of yacc.c  */
#line 2358 "parse.y"
    { if ((yyval.ttype) != error_mark_node) (yyval.ttype) = TYPE_MAIN_DECL ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 519:
/* Line 1792 of yacc.c  */
#line 2361 "parse.y"
    {
		  if (current_aggr == signature_type_node)
		    {
		      if (IS_AGGR_TYPE (TREE_TYPE ((yyvsp[(3) - (4)].ttype))))
			{
			  sorry ("`sigof' as base signature specifier");
			  (yyval.ttype) = TREE_TYPE ((yyvsp[(3) - (4)].ttype));
			}
		      else
			{
			  error ("`sigof' applied to non-aggregate expression");
			  (yyval.ttype) = error_mark_node;
			}
		    }
		  else
		    {
		      error ("`sigof' in struct or class declaration");
		      (yyval.ttype) = error_mark_node;
		    }
		}
    break;

  case 520:
/* Line 1792 of yacc.c  */
#line 2382 "parse.y"
    {
		  if (current_aggr == signature_type_node)
		    {
		      if (IS_AGGR_TYPE (groktypename ((yyvsp[(3) - (4)].ftype).t)))
			{
			  sorry ("`sigof' as base signature specifier");
			  (yyval.ttype) = groktypename ((yyvsp[(3) - (4)].ftype).t);
			}
		      else
			{
			  error ("`sigof' applied to non-aggregate expression");
			  (yyval.ttype) = error_mark_node;
			}
		    }
		  else
		    {
		      error ("`sigof' in struct or class declaration");
		      (yyval.ttype) = error_mark_node;
		    }
		}
    break;

  case 522:
/* Line 1792 of yacc.c  */
#line 2407 "parse.y"
    { if ((yyvsp[(1) - (2)].ttype) != ridpointers[(int)RID_VIRTUAL])
		    cp_error ("`%D' access", (yyvsp[(1) - (2)].ttype));
		  (yyval.ttype) = access_default_virtual_node; }
    break;

  case 523:
/* Line 1792 of yacc.c  */
#line 2411 "parse.y"
    {
		  if ((yyvsp[(1) - (3)].ttype) != access_default_virtual_node)
		    error ("multiple access specifiers");
		  else if ((yyvsp[(2) - (3)].ttype) == access_public_node)
		    (yyval.ttype) = access_public_virtual_node;
		  else if ((yyvsp[(2) - (3)].ttype) == access_protected_node)
		    (yyval.ttype) = access_protected_virtual_node;
		  else /* $2 == access_private_node */
		    (yyval.ttype) = access_private_virtual_node;
		}
    break;

  case 524:
/* Line 1792 of yacc.c  */
#line 2422 "parse.y"
    { if ((yyvsp[(2) - (3)].ttype) != ridpointers[(int)RID_VIRTUAL])
		    cp_error ("`%D' access", (yyvsp[(2) - (3)].ttype));
		  else if ((yyval.ttype) == access_public_node)
		    (yyval.ttype) = access_public_virtual_node;
		  else if ((yyval.ttype) == access_protected_node)
		    (yyval.ttype) = access_protected_virtual_node;
		  else if ((yyval.ttype) == access_private_node)
		    (yyval.ttype) = access_private_virtual_node;
		  else
		    error ("multiple `virtual' specifiers");
		}
    break;

  case 529:
/* Line 1792 of yacc.c  */
#line 2443 "parse.y"
    {
		  if (current_aggr == signature_type_node)
		    {
		      error ("access specifier not allowed in signature");
		      (yyvsp[(1) - (2)].ttype) = access_public_node;
		    }

		  current_access_specifier = (yyvsp[(1) - (2)].ttype);
                }
    break;

  case 530:
/* Line 1792 of yacc.c  */
#line 2458 "parse.y"
    { 
		  finish_member_declaration ((yyvsp[(1) - (1)].ttype));
		}
    break;

  case 531:
/* Line 1792 of yacc.c  */
#line 2462 "parse.y"
    { 
		  finish_member_declaration ((yyvsp[(2) - (2)].ttype));
		}
    break;

  case 533:
/* Line 1792 of yacc.c  */
#line 2470 "parse.y"
    { error ("missing ';' before right brace");
		  yyungetc ('}', 0); }
    break;

  case 534:
/* Line 1792 of yacc.c  */
#line 2475 "parse.y"
    { (yyval.ttype) = finish_method ((yyval.ttype)); }
    break;

  case 535:
/* Line 1792 of yacc.c  */
#line 2477 "parse.y"
    { (yyval.ttype) = finish_method ((yyval.ttype)); }
    break;

  case 536:
/* Line 1792 of yacc.c  */
#line 2479 "parse.y"
    { (yyval.ttype) = finish_method ((yyval.ttype)); }
    break;

  case 537:
/* Line 1792 of yacc.c  */
#line 2481 "parse.y"
    { (yyval.ttype) = finish_method ((yyval.ttype)); }
    break;

  case 538:
/* Line 1792 of yacc.c  */
#line 2483 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 539:
/* Line 1792 of yacc.c  */
#line 2485 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  pedantic = (yyvsp[(1) - (2)].itype); }
    break;

  case 540:
/* Line 1792 of yacc.c  */
#line 2488 "parse.y"
    {  
		  if ((yyvsp[(2) - (2)].ttype))
		    (yyval.ttype) = finish_member_template_decl ((yyvsp[(2) - (2)].ttype));
		  else
		    /* The component was already processed.  */
		    (yyval.ttype) = NULL_TREE;

		  finish_template_decl ((yyvsp[(1) - (2)].ttype));
		}
    break;

  case 541:
/* Line 1792 of yacc.c  */
#line 2498 "parse.y"
    { 
		  (yyval.ttype) = finish_member_class_template ((yyvsp[(2) - (3)].ftype).t); 
		  finish_template_decl ((yyvsp[(1) - (3)].ttype));
		}
    break;

  case 542:
/* Line 1792 of yacc.c  */
#line 2509 "parse.y"
    {
		  /* Most of the productions for component_decl only
		     allow the creation of one new member, so we call
		     finish_member_declaration in component_decl_list.
		     For this rule and the next, however, there can be
		     more than one member, e.g.:

		       int i, j;

		     and we need the first member to be fully
		     registered before the second is processed.
		     Therefore, the rules for components take care of
		     this processing.  To avoid registering the
		     components more than once, we send NULL_TREE up
		     here; that lets finish_member_declaration know
		     that there is nothing to do.  */
		  if (!(yyvsp[(2) - (2)].itype))
		    grok_x_components ((yyvsp[(1) - (2)].ftype).t);
		  (yyval.ttype) = NULL_TREE;
		}
    break;

  case 543:
/* Line 1792 of yacc.c  */
#line 2530 "parse.y"
    { 
		  if (!(yyvsp[(2) - (2)].itype))
		    grok_x_components ((yyvsp[(1) - (2)].ttype));
		  (yyval.ttype) = NULL_TREE; 
		}
    break;

  case 544:
/* Line 1792 of yacc.c  */
#line 2536 "parse.y"
    { (yyval.ttype) = grokfield ((yyval.ttype), NULL_TREE, (yyvsp[(4) - (4)].ttype), (yyvsp[(2) - (4)].ttype),
				  build_tree_list ((yyvsp[(3) - (4)].ttype), NULL_TREE)); }
    break;

  case 545:
/* Line 1792 of yacc.c  */
#line 2539 "parse.y"
    { (yyval.ttype) = grokfield ((yyval.ttype), NULL_TREE, (yyvsp[(4) - (4)].ttype), (yyvsp[(2) - (4)].ttype),
				  build_tree_list ((yyvsp[(3) - (4)].ttype), NULL_TREE)); }
    break;

  case 546:
/* Line 1792 of yacc.c  */
#line 2542 "parse.y"
    { (yyval.ttype) = grokbitfield (NULL_TREE, NULL_TREE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 547:
/* Line 1792 of yacc.c  */
#line 2544 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 548:
/* Line 1792 of yacc.c  */
#line 2555 "parse.y"
    { tree specs, attrs;
		  split_specs_attrs ((yyvsp[(1) - (5)].ttype), &specs, &attrs);
		  (yyval.ttype) = grokfield ((yyvsp[(2) - (5)].ttype), specs, (yyvsp[(5) - (5)].ttype), (yyvsp[(3) - (5)].ttype),
				  build_tree_list ((yyvsp[(4) - (5)].ttype), attrs)); }
    break;

  case 549:
/* Line 1792 of yacc.c  */
#line 2560 "parse.y"
    { (yyval.ttype) = grokfield ((yyval.ttype), NULL_TREE, (yyvsp[(4) - (4)].ttype), (yyvsp[(2) - (4)].ttype),
				  build_tree_list ((yyvsp[(3) - (4)].ttype), NULL_TREE)); }
    break;

  case 550:
/* Line 1792 of yacc.c  */
#line 2563 "parse.y"
    { (yyval.ttype) = do_class_using_decl ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 551:
/* Line 1792 of yacc.c  */
#line 2569 "parse.y"
    { (yyval.itype) = 0; }
    break;

  case 552:
/* Line 1792 of yacc.c  */
#line 2571 "parse.y"
    { 
		  if (PROCESSING_REAL_TEMPLATE_DECL_P ())
		    (yyvsp[(1) - (1)].ttype) = finish_member_template_decl ((yyvsp[(1) - (1)].ttype));
		  finish_member_declaration ((yyvsp[(1) - (1)].ttype)); 
		  (yyval.itype) = 1;
		}
    break;

  case 553:
/* Line 1792 of yacc.c  */
#line 2578 "parse.y"
    { 
		  check_multiple_declarators ();
		  if (PROCESSING_REAL_TEMPLATE_DECL_P ())
		    (yyvsp[(3) - (3)].ttype) = finish_member_template_decl ((yyvsp[(3) - (3)].ttype));
		  finish_member_declaration ((yyvsp[(3) - (3)].ttype));
		  (yyval.itype) = 2;
		}
    break;

  case 554:
/* Line 1792 of yacc.c  */
#line 2589 "parse.y"
    { (yyval.itype) = 0; }
    break;

  case 555:
/* Line 1792 of yacc.c  */
#line 2591 "parse.y"
    { 
		  if (PROCESSING_REAL_TEMPLATE_DECL_P ())
		    (yyvsp[(1) - (1)].ttype) = finish_member_template_decl ((yyvsp[(1) - (1)].ttype));
		  finish_member_declaration ((yyvsp[(1) - (1)].ttype));
		  (yyval.itype) = 1;
		}
    break;

  case 556:
/* Line 1792 of yacc.c  */
#line 2598 "parse.y"
    { 
		  check_multiple_declarators ();
		  if (PROCESSING_REAL_TEMPLATE_DECL_P ())
		    (yyvsp[(3) - (3)].ttype) = finish_member_template_decl ((yyvsp[(3) - (3)].ttype));
		  finish_member_declaration ((yyvsp[(3) - (3)].ttype)); 
		  (yyval.itype) = 2;
		}
    break;

  case 561:
/* Line 1792 of yacc.c  */
#line 2619 "parse.y"
    { split_specs_attrs ((yyvsp[(0) - (4)].ttype), &current_declspecs,
				     &prefix_attributes);
		  (yyvsp[(0) - (4)].ttype) = current_declspecs;
		  (yyval.ttype) = grokfield ((yyval.ttype), current_declspecs, (yyvsp[(4) - (4)].ttype), (yyvsp[(2) - (4)].ttype),
				  build_tree_list ((yyvsp[(3) - (4)].ttype), prefix_attributes)); }
    break;

  case 562:
/* Line 1792 of yacc.c  */
#line 2625 "parse.y"
    { split_specs_attrs ((yyvsp[(0) - (4)].ttype), &current_declspecs,
				     &prefix_attributes);
		  (yyvsp[(0) - (4)].ttype) = current_declspecs;
		  (yyval.ttype) = grokbitfield ((yyval.ttype), current_declspecs, (yyvsp[(3) - (4)].ttype));
		  cplus_decl_attributes ((yyval.ttype), (yyvsp[(4) - (4)].ttype), prefix_attributes); }
    break;

  case 563:
/* Line 1792 of yacc.c  */
#line 2634 "parse.y"
    { split_specs_attrs ((yyvsp[(0) - (4)].ttype), &current_declspecs,
				     &prefix_attributes);
		  (yyvsp[(0) - (4)].ttype) = current_declspecs;
		  (yyval.ttype) = grokfield ((yyval.ttype), current_declspecs, (yyvsp[(4) - (4)].ttype), (yyvsp[(2) - (4)].ttype),
				  build_tree_list ((yyvsp[(3) - (4)].ttype), prefix_attributes)); }
    break;

  case 564:
/* Line 1792 of yacc.c  */
#line 2640 "parse.y"
    { split_specs_attrs ((yyvsp[(0) - (4)].ttype), &current_declspecs,
				     &prefix_attributes);
		  (yyvsp[(0) - (4)].ttype) = current_declspecs;
		  (yyval.ttype) = grokfield ((yyval.ttype), current_declspecs, (yyvsp[(4) - (4)].ttype), (yyvsp[(2) - (4)].ttype),
				  build_tree_list ((yyvsp[(3) - (4)].ttype), prefix_attributes)); }
    break;

  case 565:
/* Line 1792 of yacc.c  */
#line 2646 "parse.y"
    { split_specs_attrs ((yyvsp[(0) - (4)].ttype), &current_declspecs,
				     &prefix_attributes);
		  (yyvsp[(0) - (4)].ttype) = current_declspecs;
		  (yyval.ttype) = grokbitfield ((yyval.ttype), current_declspecs, (yyvsp[(3) - (4)].ttype));
		  cplus_decl_attributes ((yyval.ttype), (yyvsp[(4) - (4)].ttype), prefix_attributes); }
    break;

  case 566:
/* Line 1792 of yacc.c  */
#line 2652 "parse.y"
    { split_specs_attrs ((yyvsp[(0) - (3)].ttype), &current_declspecs,
				     &prefix_attributes);
		  (yyvsp[(0) - (3)].ttype) = current_declspecs;
		  (yyval.ttype) = grokbitfield (NULL_TREE, current_declspecs, (yyvsp[(2) - (3)].ttype));
		  cplus_decl_attributes ((yyval.ttype), (yyvsp[(3) - (3)].ttype), prefix_attributes); }
    break;

  case 567:
/* Line 1792 of yacc.c  */
#line 2661 "parse.y"
    { (yyval.ttype) = grokfield ((yyval.ttype), current_declspecs, (yyvsp[(4) - (4)].ttype), (yyvsp[(2) - (4)].ttype),
				  build_tree_list ((yyvsp[(3) - (4)].ttype), prefix_attributes)); }
    break;

  case 568:
/* Line 1792 of yacc.c  */
#line 2664 "parse.y"
    { (yyval.ttype) = grokbitfield ((yyval.ttype), current_declspecs, (yyvsp[(3) - (4)].ttype));
		  cplus_decl_attributes ((yyval.ttype), (yyvsp[(4) - (4)].ttype), prefix_attributes); }
    break;

  case 569:
/* Line 1792 of yacc.c  */
#line 2670 "parse.y"
    { (yyval.ttype) = grokfield ((yyval.ttype), current_declspecs, (yyvsp[(4) - (4)].ttype), (yyvsp[(2) - (4)].ttype),
				  build_tree_list ((yyvsp[(3) - (4)].ttype), prefix_attributes)); }
    break;

  case 570:
/* Line 1792 of yacc.c  */
#line 2673 "parse.y"
    { (yyval.ttype) = grokbitfield ((yyval.ttype), current_declspecs, (yyvsp[(3) - (4)].ttype));
		  cplus_decl_attributes ((yyval.ttype), (yyvsp[(4) - (4)].ttype), prefix_attributes); }
    break;

  case 571:
/* Line 1792 of yacc.c  */
#line 2676 "parse.y"
    { (yyval.ttype) = grokbitfield (NULL_TREE, current_declspecs, (yyvsp[(2) - (3)].ttype));
		  cplus_decl_attributes ((yyval.ttype), (yyvsp[(3) - (3)].ttype), prefix_attributes); }
    break;

  case 573:
/* Line 1792 of yacc.c  */
#line 2687 "parse.y"
    { TREE_CHAIN ((yyvsp[(3) - (3)].ttype)) = (yyval.ttype); (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 574:
/* Line 1792 of yacc.c  */
#line 2692 "parse.y"
    { (yyval.ttype) = build_enumerator ((yyval.ttype), NULL_TREE, current_enum_type); }
    break;

  case 575:
/* Line 1792 of yacc.c  */
#line 2694 "parse.y"
    { (yyval.ttype) = build_enumerator ((yyval.ttype), (yyvsp[(3) - (3)].ttype), current_enum_type); }
    break;

  case 576:
/* Line 1792 of yacc.c  */
#line 2700 "parse.y"
    { (yyval.ftype).t = build_decl_list ((yyvsp[(1) - (2)].ftype).t, (yyvsp[(2) - (2)].ttype)); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag; }
    break;

  case 577:
/* Line 1792 of yacc.c  */
#line 2703 "parse.y"
    { (yyval.ftype).t = build_decl_list ((yyvsp[(1) - (1)].ftype).t, NULL_TREE); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (1)].ftype).new_type_flag; }
    break;

  case 578:
/* Line 1792 of yacc.c  */
#line 2710 "parse.y"
    {
		  if (pedantic)
		    pedwarn ("ANSI C++ forbids array dimensions with parenthesized type in new");
		  (yyval.ftype).t = build_parse_node (ARRAY_REF, TREE_VALUE ((yyvsp[(3) - (7)].ftype).t), (yyvsp[(6) - (7)].ttype));
		  (yyval.ftype).t = build_decl_list (TREE_PURPOSE ((yyvsp[(3) - (7)].ftype).t), (yyval.ftype).t);
		  (yyval.ftype).new_type_flag = (yyvsp[(3) - (7)].ftype).new_type_flag;
		}
    break;

  case 579:
/* Line 1792 of yacc.c  */
#line 2721 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 580:
/* Line 1792 of yacc.c  */
#line 2723 "parse.y"
    { (yyval.ttype) = decl_tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyval.ttype)); }
    break;

  case 581:
/* Line 1792 of yacc.c  */
#line 2728 "parse.y"
    { (yyval.ftype).t = hash_tree_cons (NULL_TREE, (yyvsp[(1) - (1)].ttype), NULL_TREE);
		  (yyval.ftype).new_type_flag = 0; }
    break;

  case 582:
/* Line 1792 of yacc.c  */
#line 2731 "parse.y"
    { (yyval.ftype).t = hash_tree_cons (NULL_TREE, (yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ftype).t); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag; }
    break;

  case 583:
/* Line 1792 of yacc.c  */
#line 2740 "parse.y"
    { (yyval.itype) = suspend_momentary (); }
    break;

  case 584:
/* Line 1792 of yacc.c  */
#line 2745 "parse.y"
    { resume_momentary ((int) (yyvsp[(1) - (2)].itype)); (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 585:
/* Line 1792 of yacc.c  */
#line 2751 "parse.y"
    { resume_momentary ((int) (yyvsp[(1) - (4)].itype)); (yyval.ttype) = (yyvsp[(3) - (4)].ttype); }
    break;

  case 586:
/* Line 1792 of yacc.c  */
#line 2753 "parse.y"
    { resume_momentary ((int) (yyvsp[(1) - (4)].itype)); (yyval.ttype) = (yyvsp[(3) - (4)].ttype); }
    break;

  case 587:
/* Line 1792 of yacc.c  */
#line 2755 "parse.y"
    { resume_momentary ((int) (yyvsp[(1) - (2)].itype)); (yyval.ttype) = empty_parms (); }
    break;

  case 588:
/* Line 1792 of yacc.c  */
#line 2757 "parse.y"
    { resume_momentary ((int) (yyvsp[(1) - (4)].itype)); (yyval.ttype) = NULL_TREE; }
    break;

  case 590:
/* Line 1792 of yacc.c  */
#line 2765 "parse.y"
    {
		  /* Provide support for '(' attributes '*' declarator ')'
		     etc */
		  (yyval.ttype) = decl_tree_cons ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype), NULL_TREE);
		}
    break;

  case 591:
/* Line 1792 of yacc.c  */
#line 2775 "parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ftype).t, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 592:
/* Line 1792 of yacc.c  */
#line 2777 "parse.y"
    { (yyval.ttype) = make_reference_declarator ((yyvsp[(2) - (3)].ftype).t, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 593:
/* Line 1792 of yacc.c  */
#line 2779 "parse.y"
    { (yyval.ttype) = make_pointer_declarator (NULL_TREE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 594:
/* Line 1792 of yacc.c  */
#line 2781 "parse.y"
    { (yyval.ttype) = make_reference_declarator (NULL_TREE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 595:
/* Line 1792 of yacc.c  */
#line 2783 "parse.y"
    { tree arg = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(1) - (3)].ttype), arg);
		}
    break;

  case 597:
/* Line 1792 of yacc.c  */
#line 2791 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyval.ttype), (yyvsp[(2) - (4)].ttype), (yyvsp[(3) - (4)].ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 598:
/* Line 1792 of yacc.c  */
#line 2793 "parse.y"
    { (yyval.ttype) = build_parse_node (ARRAY_REF, (yyval.ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 599:
/* Line 1792 of yacc.c  */
#line 2795 "parse.y"
    { (yyval.ttype) = build_parse_node (ARRAY_REF, (yyval.ttype), NULL_TREE); }
    break;

  case 600:
/* Line 1792 of yacc.c  */
#line 2797 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 601:
/* Line 1792 of yacc.c  */
#line 2799 "parse.y"
    { push_nested_class ((yyvsp[(1) - (2)].ttype), 3);
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyval.ttype), (yyvsp[(2) - (2)].ttype));
		  TREE_COMPLEXITY ((yyval.ttype)) = current_class_depth; }
    break;

  case 603:
/* Line 1792 of yacc.c  */
#line 2807 "parse.y"
    {
		  if (TREE_CODE ((yyvsp[(1) - (1)].ttype)) == IDENTIFIER_NODE)
		    {
		      (yyval.ttype) = lookup_name ((yyvsp[(1) - (1)].ttype), 1);
		      maybe_note_name_used_in_class ((yyvsp[(1) - (1)].ttype), (yyval.ttype));
		    }
		  else
		    (yyval.ttype) = (yyvsp[(1) - (1)].ttype);
		}
    break;

  case 604:
/* Line 1792 of yacc.c  */
#line 2817 "parse.y"
    {
		  if (TREE_CODE ((yyvsp[(2) - (2)].ttype)) == IDENTIFIER_NODE)
		    (yyval.ttype) = IDENTIFIER_GLOBAL_VALUE ((yyvsp[(2) - (2)].ttype));
		  else
		    (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  got_scope = NULL_TREE;
		}
    break;

  case 607:
/* Line 1792 of yacc.c  */
#line 2830 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 608:
/* Line 1792 of yacc.c  */
#line 2835 "parse.y"
    { (yyval.ttype) = get_type_decl ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 610:
/* Line 1792 of yacc.c  */
#line 2844 "parse.y"
    {
		  /* Provide support for '(' attributes '*' declarator ')'
		     etc */
		  (yyval.ttype) = decl_tree_cons ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype), NULL_TREE);
		}
    break;

  case 611:
/* Line 1792 of yacc.c  */
#line 2853 "parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ftype).t, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 612:
/* Line 1792 of yacc.c  */
#line 2855 "parse.y"
    { (yyval.ttype) = make_reference_declarator ((yyvsp[(2) - (3)].ftype).t, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 613:
/* Line 1792 of yacc.c  */
#line 2857 "parse.y"
    { (yyval.ttype) = make_pointer_declarator (NULL_TREE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 614:
/* Line 1792 of yacc.c  */
#line 2859 "parse.y"
    { (yyval.ttype) = make_reference_declarator (NULL_TREE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 615:
/* Line 1792 of yacc.c  */
#line 2861 "parse.y"
    { tree arg = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(1) - (3)].ttype), arg);
		}
    break;

  case 617:
/* Line 1792 of yacc.c  */
#line 2869 "parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ftype).t, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 618:
/* Line 1792 of yacc.c  */
#line 2871 "parse.y"
    { (yyval.ttype) = make_reference_declarator ((yyvsp[(2) - (3)].ftype).t, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 619:
/* Line 1792 of yacc.c  */
#line 2873 "parse.y"
    { (yyval.ttype) = make_pointer_declarator (NULL_TREE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 620:
/* Line 1792 of yacc.c  */
#line 2875 "parse.y"
    { (yyval.ttype) = make_reference_declarator (NULL_TREE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 621:
/* Line 1792 of yacc.c  */
#line 2877 "parse.y"
    { tree arg = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(1) - (3)].ttype), arg);
		}
    break;

  case 623:
/* Line 1792 of yacc.c  */
#line 2885 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyval.ttype), (yyvsp[(2) - (4)].ttype), (yyvsp[(3) - (4)].ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 624:
/* Line 1792 of yacc.c  */
#line 2887 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 625:
/* Line 1792 of yacc.c  */
#line 2889 "parse.y"
    { (yyval.ttype) = build_parse_node (ARRAY_REF, (yyval.ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 626:
/* Line 1792 of yacc.c  */
#line 2891 "parse.y"
    { (yyval.ttype) = build_parse_node (ARRAY_REF, (yyval.ttype), NULL_TREE); }
    break;

  case 627:
/* Line 1792 of yacc.c  */
#line 2893 "parse.y"
    { enter_scope_of ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 628:
/* Line 1792 of yacc.c  */
#line 2895 "parse.y"
    { got_scope = NULL_TREE;
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype));
		  enter_scope_of ((yyval.ttype));
		}
    break;

  case 629:
/* Line 1792 of yacc.c  */
#line 2903 "parse.y"
    { got_scope = NULL_TREE;
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyval.ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 630:
/* Line 1792 of yacc.c  */
#line 2906 "parse.y"
    { got_scope = NULL_TREE;
 		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 631:
/* Line 1792 of yacc.c  */
#line 2912 "parse.y"
    { got_scope = NULL_TREE;
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyval.ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 632:
/* Line 1792 of yacc.c  */
#line 2915 "parse.y"
    { got_scope = NULL_TREE;
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 634:
/* Line 1792 of yacc.c  */
#line 2922 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 635:
/* Line 1792 of yacc.c  */
#line 2927 "parse.y"
    { (yyval.ttype) = build_functional_cast ((yyvsp[(1) - (4)].ftype).t, (yyvsp[(3) - (4)].ttype)); }
    break;

  case 636:
/* Line 1792 of yacc.c  */
#line 2929 "parse.y"
    { (yyval.ttype) = reparse_decl_as_expr ((yyvsp[(1) - (4)].ftype).t, (yyvsp[(3) - (4)].ttype)); }
    break;

  case 637:
/* Line 1792 of yacc.c  */
#line 2931 "parse.y"
    { (yyval.ttype) = reparse_absdcl_as_expr ((yyvsp[(1) - (2)].ftype).t, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 642:
/* Line 1792 of yacc.c  */
#line 2942 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 643:
/* Line 1792 of yacc.c  */
#line 2944 "parse.y"
    { got_scope = (yyval.ttype) = make_typename_type ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 644:
/* Line 1792 of yacc.c  */
#line 2951 "parse.y"
    {
		  if (TREE_CODE ((yyvsp[(1) - (2)].ttype)) == IDENTIFIER_NODE)
		    {
		      (yyval.ttype) = lastiddecl;
		      maybe_note_name_used_in_class ((yyvsp[(1) - (2)].ttype), (yyval.ttype));
		    }
		  got_scope = (yyval.ttype) =
		    complete_type (TYPE_MAIN_VARIANT (TREE_TYPE ((yyval.ttype))));
		}
    break;

  case 645:
/* Line 1792 of yacc.c  */
#line 2961 "parse.y"
    {
		  if (TREE_CODE ((yyvsp[(1) - (2)].ttype)) == IDENTIFIER_NODE)
		    (yyval.ttype) = lastiddecl;
		  got_scope = (yyval.ttype) = TREE_TYPE ((yyval.ttype));
		}
    break;

  case 646:
/* Line 1792 of yacc.c  */
#line 2967 "parse.y"
    {
		  if (TREE_CODE ((yyval.ttype)) == IDENTIFIER_NODE)
		    (yyval.ttype) = lastiddecl;
		  got_scope = (yyval.ttype);
		}
    break;

  case 647:
/* Line 1792 of yacc.c  */
#line 2973 "parse.y"
    { got_scope = (yyval.ttype) = complete_type (TREE_TYPE ((yyvsp[(1) - (2)].ttype))); }
    break;

  case 649:
/* Line 1792 of yacc.c  */
#line 2989 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 650:
/* Line 1792 of yacc.c  */
#line 2994 "parse.y"
    {
		  if (TREE_CODE_CLASS (TREE_CODE ((yyvsp[(1) - (2)].ttype))) == 't')
		    (yyval.ttype) = make_typename_type ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype));
		  else if (TREE_CODE ((yyvsp[(2) - (2)].ttype)) == IDENTIFIER_NODE)
		    cp_error ("`%T' is not a class or namespace", (yyvsp[(2) - (2)].ttype));
		  else
		    {
		      (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		      if (TREE_CODE ((yyval.ttype)) == TYPE_DECL)
			(yyval.ttype) = TREE_TYPE ((yyval.ttype));
		    }
		}
    break;

  case 651:
/* Line 1792 of yacc.c  */
#line 3007 "parse.y"
    { (yyval.ttype) = TREE_TYPE ((yyvsp[(2) - (2)].ttype)); }
    break;

  case 652:
/* Line 1792 of yacc.c  */
#line 3009 "parse.y"
    { (yyval.ttype) = make_typename_type ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype)); }
    break;

  case 653:
/* Line 1792 of yacc.c  */
#line 3011 "parse.y"
    { (yyval.ttype) = make_typename_type ((yyvsp[(1) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 654:
/* Line 1792 of yacc.c  */
#line 3016 "parse.y"
    {
		  if (TREE_CODE ((yyvsp[(1) - (1)].ttype)) == IDENTIFIER_NODE)
		    cp_error ("`%T' is not a class or namespace", (yyvsp[(1) - (1)].ttype));
		}
    break;

  case 655:
/* Line 1792 of yacc.c  */
#line 3021 "parse.y"
    {
		  if (TREE_CODE_CLASS (TREE_CODE ((yyvsp[(1) - (2)].ttype))) == 't')
		    (yyval.ttype) = make_typename_type ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype));
		  else if (TREE_CODE ((yyvsp[(2) - (2)].ttype)) == IDENTIFIER_NODE)
		    cp_error ("`%T' is not a class or namespace", (yyvsp[(2) - (2)].ttype));
		  else
		    {
		      (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		      if (TREE_CODE ((yyval.ttype)) == TYPE_DECL)
			(yyval.ttype) = TREE_TYPE ((yyval.ttype));
		    }
		}
    break;

  case 656:
/* Line 1792 of yacc.c  */
#line 3034 "parse.y"
    { got_scope = (yyval.ttype) = make_typename_type ((yyvsp[(1) - (3)].ttype), (yyvsp[(2) - (3)].ttype)); }
    break;

  case 657:
/* Line 1792 of yacc.c  */
#line 3036 "parse.y"
    { got_scope = (yyval.ttype) = make_typename_type ((yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 658:
/* Line 1792 of yacc.c  */
#line 3041 "parse.y"
    {
		  if (TREE_CODE ((yyvsp[(1) - (2)].ttype)) != IDENTIFIER_NODE)
		    (yyvsp[(1) - (2)].ttype) = lastiddecl;

		  /* Retrieve the type for the identifier, which might involve
		     some computation. */
		  got_scope = (yyval.ttype) = complete_type (IDENTIFIER_TYPE_VALUE ((yyvsp[(1) - (2)].ttype)));

		  if ((yyval.ttype) == error_mark_node)
		    cp_error ("`%T' is not a class or namespace", (yyvsp[(1) - (2)].ttype));
		}
    break;

  case 659:
/* Line 1792 of yacc.c  */
#line 3053 "parse.y"
    {
		  if (TREE_CODE ((yyvsp[(1) - (2)].ttype)) != IDENTIFIER_NODE)
		    (yyval.ttype) = lastiddecl;
		  got_scope = (yyval.ttype) = complete_type (TREE_TYPE ((yyval.ttype)));
		}
    break;

  case 660:
/* Line 1792 of yacc.c  */
#line 3059 "parse.y"
    { got_scope = (yyval.ttype) = complete_type (TREE_TYPE ((yyval.ttype))); }
    break;

  case 663:
/* Line 1792 of yacc.c  */
#line 3063 "parse.y"
    {
		  if (TREE_CODE ((yyval.ttype)) == IDENTIFIER_NODE)
		    (yyval.ttype) = lastiddecl;
		  got_scope = (yyval.ttype);
		}
    break;

  case 664:
/* Line 1792 of yacc.c  */
#line 3072 "parse.y"
    { (yyval.ttype) = build_min_nt (TEMPLATE_ID_EXPR, (yyvsp[(1) - (4)].ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 665:
/* Line 1792 of yacc.c  */
#line 3077 "parse.y"
    {
		  if (TREE_CODE ((yyvsp[(2) - (2)].ttype)) == IDENTIFIER_NODE)
		    (yyval.ttype) = IDENTIFIER_GLOBAL_VALUE ((yyvsp[(2) - (2)].ttype));
		  else
		    (yyval.ttype) = (yyvsp[(2) - (2)].ttype);
		  got_scope = NULL_TREE;
		}
    break;

  case 667:
/* Line 1792 of yacc.c  */
#line 3086 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (2)].ttype); }
    break;

  case 668:
/* Line 1792 of yacc.c  */
#line 3091 "parse.y"
    { got_scope = NULL_TREE; }
    break;

  case 669:
/* Line 1792 of yacc.c  */
#line 3093 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); got_scope = NULL_TREE; }
    break;

  case 670:
/* Line 1792 of yacc.c  */
#line 3100 "parse.y"
    { got_scope = void_type_node; }
    break;

  case 671:
/* Line 1792 of yacc.c  */
#line 3106 "parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 672:
/* Line 1792 of yacc.c  */
#line 3108 "parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (2)].ttype), NULL_TREE); }
    break;

  case 673:
/* Line 1792 of yacc.c  */
#line 3110 "parse.y"
    { (yyval.ttype) = make_reference_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 674:
/* Line 1792 of yacc.c  */
#line 3112 "parse.y"
    { (yyval.ttype) = make_reference_declarator ((yyvsp[(2) - (2)].ttype), NULL_TREE); }
    break;

  case 675:
/* Line 1792 of yacc.c  */
#line 3114 "parse.y"
    { tree arg = make_pointer_declarator ((yyvsp[(2) - (2)].ttype), NULL_TREE);
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(1) - (2)].ttype), arg);
		}
    break;

  case 676:
/* Line 1792 of yacc.c  */
#line 3118 "parse.y"
    { tree arg = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(1) - (3)].ttype), arg);
		}
    break;

  case 678:
/* Line 1792 of yacc.c  */
#line 3127 "parse.y"
    { (yyval.ttype) = build_parse_node (ARRAY_REF, NULL_TREE, (yyvsp[(2) - (3)].ttype)); }
    break;

  case 679:
/* Line 1792 of yacc.c  */
#line 3129 "parse.y"
    { (yyval.ttype) = build_parse_node (ARRAY_REF, (yyval.ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 681:
/* Line 1792 of yacc.c  */
#line 3135 "parse.y"
    {
		  /* Provide support for '(' attributes '*' declarator ')'
		     etc */
		  (yyval.ttype) = decl_tree_cons ((yyvsp[(1) - (2)].ttype), (yyvsp[(2) - (2)].ttype), NULL_TREE);
		}
    break;

  case 682:
/* Line 1792 of yacc.c  */
#line 3145 "parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ftype).t, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 683:
/* Line 1792 of yacc.c  */
#line 3147 "parse.y"
    { (yyval.ttype) = make_pointer_declarator (NULL_TREE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 684:
/* Line 1792 of yacc.c  */
#line 3149 "parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (2)].ftype).t, NULL_TREE); }
    break;

  case 685:
/* Line 1792 of yacc.c  */
#line 3151 "parse.y"
    { (yyval.ttype) = make_pointer_declarator (NULL_TREE, NULL_TREE); }
    break;

  case 686:
/* Line 1792 of yacc.c  */
#line 3153 "parse.y"
    { (yyval.ttype) = make_reference_declarator ((yyvsp[(2) - (3)].ftype).t, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 687:
/* Line 1792 of yacc.c  */
#line 3155 "parse.y"
    { (yyval.ttype) = make_reference_declarator (NULL_TREE, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 688:
/* Line 1792 of yacc.c  */
#line 3157 "parse.y"
    { (yyval.ttype) = make_reference_declarator ((yyvsp[(2) - (2)].ftype).t, NULL_TREE); }
    break;

  case 689:
/* Line 1792 of yacc.c  */
#line 3159 "parse.y"
    { (yyval.ttype) = make_reference_declarator (NULL_TREE, NULL_TREE); }
    break;

  case 690:
/* Line 1792 of yacc.c  */
#line 3161 "parse.y"
    { tree arg = make_pointer_declarator ((yyvsp[(2) - (2)].ttype), NULL_TREE);
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(1) - (2)].ttype), arg);
		}
    break;

  case 691:
/* Line 1792 of yacc.c  */
#line 3165 "parse.y"
    { tree arg = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(1) - (3)].ttype), arg);
		}
    break;

  case 693:
/* Line 1792 of yacc.c  */
#line 3174 "parse.y"
    { (yyval.ttype) = (yyvsp[(2) - (3)].ttype); }
    break;

  case 695:
/* Line 1792 of yacc.c  */
#line 3178 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyval.ttype), (yyvsp[(3) - (6)].ttype), (yyvsp[(5) - (6)].ttype), (yyvsp[(6) - (6)].ttype)); }
    break;

  case 696:
/* Line 1792 of yacc.c  */
#line 3180 "parse.y"
    { (yyval.ttype) = make_call_declarator ((yyval.ttype), empty_parms (), (yyvsp[(3) - (4)].ttype), (yyvsp[(4) - (4)].ttype)); }
    break;

  case 697:
/* Line 1792 of yacc.c  */
#line 3182 "parse.y"
    { (yyval.ttype) = build_parse_node (ARRAY_REF, (yyval.ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 698:
/* Line 1792 of yacc.c  */
#line 3184 "parse.y"
    { (yyval.ttype) = build_parse_node (ARRAY_REF, (yyval.ttype), NULL_TREE); }
    break;

  case 699:
/* Line 1792 of yacc.c  */
#line 3186 "parse.y"
    { (yyval.ttype) = make_call_declarator (NULL_TREE, (yyvsp[(2) - (5)].ttype), (yyvsp[(4) - (5)].ttype), (yyvsp[(5) - (5)].ttype)); }
    break;

  case 700:
/* Line 1792 of yacc.c  */
#line 3188 "parse.y"
    { set_quals_and_spec ((yyval.ttype), (yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 701:
/* Line 1792 of yacc.c  */
#line 3190 "parse.y"
    { set_quals_and_spec ((yyval.ttype), (yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 702:
/* Line 1792 of yacc.c  */
#line 3192 "parse.y"
    { (yyval.ttype) = build_parse_node (ARRAY_REF, NULL_TREE, (yyvsp[(2) - (3)].ttype)); }
    break;

  case 703:
/* Line 1792 of yacc.c  */
#line 3194 "parse.y"
    { (yyval.ttype) = build_parse_node (ARRAY_REF, NULL_TREE, NULL_TREE); }
    break;

  case 710:
/* Line 1792 of yacc.c  */
#line 3217 "parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C++ forbids label declarations"); }
    break;

  case 713:
/* Line 1792 of yacc.c  */
#line 3228 "parse.y"
    { tree link;
		  for (link = (yyvsp[(2) - (3)].ttype); link; link = TREE_CHAIN (link))
		    {
		      tree label = shadow_label (TREE_VALUE (link));
		      C_DECLARED_LABEL_FLAG (label) = 1;
		      declare_nonlocal_label (label);
		    }
		}
    break;

  case 714:
/* Line 1792 of yacc.c  */
#line 3242 "parse.y"
    {}
    break;

  case 716:
/* Line 1792 of yacc.c  */
#line 3248 "parse.y"
    { (yyval.ttype) = begin_compound_stmt (0); }
    break;

  case 717:
/* Line 1792 of yacc.c  */
#line 3250 "parse.y"
    { (yyval.ttype) = finish_compound_stmt (0, (yyvsp[(2) - (3)].ttype)); }
    break;

  case 718:
/* Line 1792 of yacc.c  */
#line 3255 "parse.y"
    {
		  (yyval.ttype) = begin_if_stmt ();
		  cond_stmt_keyword = "if";
		}
    break;

  case 719:
/* Line 1792 of yacc.c  */
#line 3260 "parse.y"
    { finish_if_stmt_cond ((yyvsp[(3) - (3)].ttype), (yyvsp[(2) - (3)].ttype)); }
    break;

  case 720:
/* Line 1792 of yacc.c  */
#line 3262 "parse.y"
    { (yyval.ttype) = finish_then_clause ((yyvsp[(2) - (5)].ttype)); }
    break;

  case 722:
/* Line 1792 of yacc.c  */
#line 3267 "parse.y"
    { (yyval.ttype) = begin_compound_stmt (0); }
    break;

  case 723:
/* Line 1792 of yacc.c  */
#line 3269 "parse.y"
    { (yyval.ttype) = finish_compound_stmt (0, (yyvsp[(1) - (2)].ttype)); }
    break;

  case 724:
/* Line 1792 of yacc.c  */
#line 3274 "parse.y"
    {}
    break;

  case 726:
/* Line 1792 of yacc.c  */
#line 3280 "parse.y"
    { finish_stmt (); }
    break;

  case 727:
/* Line 1792 of yacc.c  */
#line 3282 "parse.y"
    { finish_expr_stmt ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 728:
/* Line 1792 of yacc.c  */
#line 3284 "parse.y"
    { begin_else_clause (); }
    break;

  case 729:
/* Line 1792 of yacc.c  */
#line 3286 "parse.y"
    { 
		  finish_else_clause ((yyvsp[(1) - (4)].ttype)); 
		  finish_if_stmt ();
		}
    break;

  case 730:
/* Line 1792 of yacc.c  */
#line 3291 "parse.y"
    { finish_if_stmt (); }
    break;

  case 731:
/* Line 1792 of yacc.c  */
#line 3293 "parse.y"
    {
		  (yyval.ttype) = begin_while_stmt ();
		  cond_stmt_keyword = "while";
		}
    break;

  case 732:
/* Line 1792 of yacc.c  */
#line 3298 "parse.y"
    { finish_while_stmt_cond ((yyvsp[(3) - (3)].ttype), (yyvsp[(2) - (3)].ttype)); }
    break;

  case 733:
/* Line 1792 of yacc.c  */
#line 3300 "parse.y"
    { finish_while_stmt ((yyvsp[(2) - (5)].ttype)); }
    break;

  case 734:
/* Line 1792 of yacc.c  */
#line 3302 "parse.y"
    { (yyval.ttype) = begin_do_stmt (); }
    break;

  case 735:
/* Line 1792 of yacc.c  */
#line 3304 "parse.y"
    {
		  finish_do_body ((yyvsp[(2) - (4)].ttype));
		  cond_stmt_keyword = "do";
		}
    break;

  case 736:
/* Line 1792 of yacc.c  */
#line 3309 "parse.y"
    { finish_do_stmt ((yyvsp[(6) - (7)].ttype), (yyvsp[(2) - (7)].ttype)); }
    break;

  case 737:
/* Line 1792 of yacc.c  */
#line 3311 "parse.y"
    { (yyval.ttype) = begin_for_stmt (); }
    break;

  case 738:
/* Line 1792 of yacc.c  */
#line 3313 "parse.y"
    { finish_for_init_stmt ((yyvsp[(2) - (4)].ttype)); }
    break;

  case 739:
/* Line 1792 of yacc.c  */
#line 3315 "parse.y"
    { finish_for_cond ((yyvsp[(6) - (7)].ttype), (yyvsp[(2) - (7)].ttype)); }
    break;

  case 740:
/* Line 1792 of yacc.c  */
#line 3317 "parse.y"
    { finish_for_expr ((yyvsp[(9) - (10)].ttype), (yyvsp[(2) - (10)].ttype)); }
    break;

  case 741:
/* Line 1792 of yacc.c  */
#line 3319 "parse.y"
    { finish_for_stmt ((yyvsp[(9) - (12)].ttype), (yyvsp[(2) - (12)].ttype)); }
    break;

  case 742:
/* Line 1792 of yacc.c  */
#line 3321 "parse.y"
    { begin_switch_stmt (); }
    break;

  case 743:
/* Line 1792 of yacc.c  */
#line 3323 "parse.y"
    { (yyval.ttype) = finish_switch_cond ((yyvsp[(4) - (5)].ttype)); }
    break;

  case 744:
/* Line 1792 of yacc.c  */
#line 3325 "parse.y"
    { finish_switch_stmt ((yyvsp[(4) - (7)].ttype), (yyvsp[(6) - (7)].ttype)); }
    break;

  case 745:
/* Line 1792 of yacc.c  */
#line 3327 "parse.y"
    { finish_case_label ((yyvsp[(2) - (3)].ttype), NULL_TREE); }
    break;

  case 747:
/* Line 1792 of yacc.c  */
#line 3330 "parse.y"
    { finish_case_label ((yyvsp[(2) - (5)].ttype), (yyvsp[(4) - (5)].ttype)); }
    break;

  case 749:
/* Line 1792 of yacc.c  */
#line 3333 "parse.y"
    { finish_case_label (NULL_TREE, NULL_TREE); }
    break;

  case 751:
/* Line 1792 of yacc.c  */
#line 3336 "parse.y"
    { finish_break_stmt (); }
    break;

  case 752:
/* Line 1792 of yacc.c  */
#line 3338 "parse.y"
    { finish_continue_stmt (); }
    break;

  case 753:
/* Line 1792 of yacc.c  */
#line 3340 "parse.y"
    { finish_return_stmt (NULL_TREE); }
    break;

  case 754:
/* Line 1792 of yacc.c  */
#line 3342 "parse.y"
    { finish_return_stmt ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 755:
/* Line 1792 of yacc.c  */
#line 3344 "parse.y"
    { 
		  finish_asm_stmt ((yyvsp[(2) - (6)].ttype), (yyvsp[(4) - (6)].ttype), NULL_TREE, NULL_TREE,
				   NULL_TREE); 
		}
    break;

  case 756:
/* Line 1792 of yacc.c  */
#line 3350 "parse.y"
    { 
		  finish_asm_stmt ((yyvsp[(2) - (8)].ttype), (yyvsp[(4) - (8)].ttype), (yyvsp[(6) - (8)].ttype), NULL_TREE,
				   NULL_TREE); 
		}
    break;

  case 757:
/* Line 1792 of yacc.c  */
#line 3356 "parse.y"
    { finish_asm_stmt ((yyvsp[(2) - (10)].ttype), (yyvsp[(4) - (10)].ttype), (yyvsp[(6) - (10)].ttype), (yyvsp[(8) - (10)].ttype), NULL_TREE); }
    break;

  case 758:
/* Line 1792 of yacc.c  */
#line 3360 "parse.y"
    { finish_asm_stmt ((yyvsp[(2) - (12)].ttype), (yyvsp[(4) - (12)].ttype), (yyvsp[(6) - (12)].ttype), (yyvsp[(8) - (12)].ttype), (yyvsp[(10) - (12)].ttype)); }
    break;

  case 759:
/* Line 1792 of yacc.c  */
#line 3362 "parse.y"
    { 
		  if (pedantic)
		    pedwarn ("ANSI C++ forbids computed gotos");
		  finish_goto_stmt ((yyvsp[(3) - (4)].ttype));
		}
    break;

  case 760:
/* Line 1792 of yacc.c  */
#line 3368 "parse.y"
    { finish_goto_stmt ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 761:
/* Line 1792 of yacc.c  */
#line 3370 "parse.y"
    { finish_stmt (); }
    break;

  case 762:
/* Line 1792 of yacc.c  */
#line 3372 "parse.y"
    { error ("label must be followed by statement");
		  yyungetc ('}', 0);
		  finish_stmt (); }
    break;

  case 763:
/* Line 1792 of yacc.c  */
#line 3376 "parse.y"
    { finish_stmt (); }
    break;

  case 766:
/* Line 1792 of yacc.c  */
#line 3380 "parse.y"
    { do_local_using_decl ((yyvsp[(1) - (1)].ttype)); }
    break;

  case 768:
/* Line 1792 of yacc.c  */
#line 3386 "parse.y"
    {
		  if (! current_function_parms_stored)
		    store_parm_decls ();
		  expand_start_early_try_stmts ();
		}
    break;

  case 769:
/* Line 1792 of yacc.c  */
#line 3392 "parse.y"
    { 
		  end_protect_partials ();
                  expand_start_all_catch (); 
                }
    break;

  case 770:
/* Line 1792 of yacc.c  */
#line 3397 "parse.y"
    {
		  expand_end_all_catch ();
		  (yyval.itype) = (yyvsp[(3) - (6)].itype);
		}
    break;

  case 771:
/* Line 1792 of yacc.c  */
#line 3405 "parse.y"
    { (yyval.ttype) = begin_try_block (); }
    break;

  case 772:
/* Line 1792 of yacc.c  */
#line 3407 "parse.y"
    { finish_try_block ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 773:
/* Line 1792 of yacc.c  */
#line 3409 "parse.y"
    { finish_handler_sequence ((yyvsp[(2) - (5)].ttype)); }
    break;

  case 776:
/* Line 1792 of yacc.c  */
#line 3419 "parse.y"
    { (yyval.ttype) = begin_handler(); }
    break;

  case 777:
/* Line 1792 of yacc.c  */
#line 3421 "parse.y"
    { finish_handler_parms ((yyvsp[(2) - (3)].ttype)); }
    break;

  case 778:
/* Line 1792 of yacc.c  */
#line 3423 "parse.y"
    { finish_handler ((yyvsp[(2) - (5)].ttype)); }
    break;

  case 781:
/* Line 1792 of yacc.c  */
#line 3433 "parse.y"
    { expand_start_catch_block (NULL_TREE, NULL_TREE); }
    break;

  case 782:
/* Line 1792 of yacc.c  */
#line 3449 "parse.y"
    { check_for_new_type ("inside exception declarations", (yyvsp[(2) - (3)].ftype));
		  expand_start_catch_block (TREE_PURPOSE ((yyvsp[(2) - (3)].ftype).t),
					    TREE_VALUE ((yyvsp[(2) - (3)].ftype).t)); }
    break;

  case 783:
/* Line 1792 of yacc.c  */
#line 3456 "parse.y"
    { tree label;
		do_label:
		  label = define_label (input_filename, lineno, (yyvsp[(1) - (2)].ttype));
		  if (label && ! minimal_parse_mode)
		    expand_label (label);
		}
    break;

  case 784:
/* Line 1792 of yacc.c  */
#line 3463 "parse.y"
    { goto do_label; }
    break;

  case 785:
/* Line 1792 of yacc.c  */
#line 3465 "parse.y"
    { goto do_label; }
    break;

  case 786:
/* Line 1792 of yacc.c  */
#line 3467 "parse.y"
    { goto do_label; }
    break;

  case 787:
/* Line 1792 of yacc.c  */
#line 3472 "parse.y"
    { if ((yyvsp[(1) - (2)].ttype)) cplus_expand_expr_stmt ((yyvsp[(1) - (2)].ttype)); }
    break;

  case 789:
/* Line 1792 of yacc.c  */
#line 3475 "parse.y"
    { if (pedantic)
		    pedwarn ("ANSI C++ forbids compound statements inside for initializations");
		}
    break;

  case 790:
/* Line 1792 of yacc.c  */
#line 3484 "parse.y"
    { emit_line_note (input_filename, lineno);
		  (yyval.ttype) = NULL_TREE; }
    break;

  case 791:
/* Line 1792 of yacc.c  */
#line 3487 "parse.y"
    { emit_line_note (input_filename, lineno); }
    break;

  case 792:
/* Line 1792 of yacc.c  */
#line 3492 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 794:
/* Line 1792 of yacc.c  */
#line 3495 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 795:
/* Line 1792 of yacc.c  */
#line 3502 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 798:
/* Line 1792 of yacc.c  */
#line 3509 "parse.y"
    { (yyval.ttype) = chainon ((yyval.ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 799:
/* Line 1792 of yacc.c  */
#line 3514 "parse.y"
    { (yyval.ttype) = build_tree_list ((yyval.ttype), (yyvsp[(3) - (4)].ttype)); }
    break;

  case 800:
/* Line 1792 of yacc.c  */
#line 3519 "parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyval.ttype), NULL_TREE); }
    break;

  case 801:
/* Line 1792 of yacc.c  */
#line 3521 "parse.y"
    { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[(3) - (3)].ttype), (yyval.ttype)); }
    break;

  case 802:
/* Line 1792 of yacc.c  */
#line 3532 "parse.y"
    {
		  (yyval.ttype) = empty_parms();
		}
    break;

  case 804:
/* Line 1792 of yacc.c  */
#line 3537 "parse.y"
    { (yyval.ttype) = finish_parmlist (build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ftype).t), 0);
		  check_for_new_type ("inside parameter list", (yyvsp[(1) - (1)].ftype)); }
    break;

  case 805:
/* Line 1792 of yacc.c  */
#line 3545 "parse.y"
    { (yyval.ttype) = finish_parmlist ((yyval.ttype), 0); }
    break;

  case 806:
/* Line 1792 of yacc.c  */
#line 3547 "parse.y"
    { (yyval.ttype) = finish_parmlist ((yyvsp[(1) - (2)].ttype), 1); }
    break;

  case 807:
/* Line 1792 of yacc.c  */
#line 3550 "parse.y"
    { (yyval.ttype) = finish_parmlist ((yyvsp[(1) - (2)].ttype), 1); }
    break;

  case 808:
/* Line 1792 of yacc.c  */
#line 3552 "parse.y"
    { (yyval.ttype) = finish_parmlist (build_tree_list (NULL_TREE,
							 (yyvsp[(1) - (2)].ftype).t), 1); }
    break;

  case 809:
/* Line 1792 of yacc.c  */
#line 3555 "parse.y"
    { (yyval.ttype) = finish_parmlist (NULL_TREE, 1); }
    break;

  case 810:
/* Line 1792 of yacc.c  */
#line 3557 "parse.y"
    {
		  /* This helps us recover from really nasty
		     parse errors, for example, a missing right
		     parenthesis.  */
		  yyerror ("possibly missing ')'");
		  (yyval.ttype) = finish_parmlist ((yyvsp[(1) - (2)].ttype), 0);
		  yyungetc (':', 0);
		  yychar = ')';
		}
    break;

  case 811:
/* Line 1792 of yacc.c  */
#line 3567 "parse.y"
    {
		  /* This helps us recover from really nasty
		     parse errors, for example, a missing right
		     parenthesis.  */
		  yyerror ("possibly missing ')'");
		  (yyval.ttype) = finish_parmlist (build_tree_list (NULL_TREE,
							 (yyvsp[(1) - (2)].ftype).t), 0); 
		  yyungetc (':', 0);
		  yychar = ')';
		}
    break;

  case 812:
/* Line 1792 of yacc.c  */
#line 3582 "parse.y"
    { maybe_snarf_defarg (); }
    break;

  case 813:
/* Line 1792 of yacc.c  */
#line 3584 "parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (3)].ttype); }
    break;

  case 816:
/* Line 1792 of yacc.c  */
#line 3595 "parse.y"
    { check_for_new_type ("in a parameter list", (yyvsp[(1) - (1)].ftype));
		  (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ftype).t); }
    break;

  case 817:
/* Line 1792 of yacc.c  */
#line 3598 "parse.y"
    { check_for_new_type ("in a parameter list", (yyvsp[(1) - (2)].ftype));
		  (yyval.ttype) = build_tree_list ((yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ftype).t); }
    break;

  case 818:
/* Line 1792 of yacc.c  */
#line 3601 "parse.y"
    { check_for_new_type ("in a parameter list", (yyvsp[(2) - (2)].ftype));
		  (yyval.ttype) = chainon ((yyval.ttype), (yyvsp[(2) - (2)].ftype).t); }
    break;

  case 819:
/* Line 1792 of yacc.c  */
#line 3604 "parse.y"
    { (yyval.ttype) = chainon ((yyval.ttype), build_tree_list (NULL_TREE, (yyvsp[(2) - (2)].ttype))); }
    break;

  case 820:
/* Line 1792 of yacc.c  */
#line 3606 "parse.y"
    { (yyval.ttype) = chainon ((yyval.ttype), build_tree_list ((yyvsp[(4) - (4)].ttype), (yyvsp[(2) - (4)].ttype))); }
    break;

  case 822:
/* Line 1792 of yacc.c  */
#line 3612 "parse.y"
    { check_for_new_type ("in a parameter list", (yyvsp[(1) - (2)].ftype));
		  (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[(1) - (2)].ftype).t); }
    break;

  case 823:
/* Line 1792 of yacc.c  */
#line 3622 "parse.y"
    { tree specs = strip_attrs ((yyvsp[(1) - (2)].ftype).t);
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag;
		  (yyval.ftype).t = build_tree_list (specs, (yyvsp[(2) - (2)].ttype)); }
    break;

  case 824:
/* Line 1792 of yacc.c  */
#line 3626 "parse.y"
    { (yyval.ftype).t = build_tree_list ((yyvsp[(1) - (2)].ftype).t, (yyvsp[(2) - (2)].ttype)); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag; }
    break;

  case 825:
/* Line 1792 of yacc.c  */
#line 3629 "parse.y"
    { (yyval.ftype).t = build_tree_list (build_decl_list (NULL_TREE, (yyvsp[(1) - (2)].ftype).t),
					  (yyvsp[(2) - (2)].ttype)); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag; }
    break;

  case 826:
/* Line 1792 of yacc.c  */
#line 3633 "parse.y"
    { tree specs = strip_attrs ((yyvsp[(1) - (2)].ftype).t);
		  (yyval.ftype).t = build_tree_list (specs, (yyvsp[(2) - (2)].ttype));
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag; }
    break;

  case 827:
/* Line 1792 of yacc.c  */
#line 3637 "parse.y"
    { tree specs = strip_attrs ((yyvsp[(1) - (1)].ftype).t);
		  (yyval.ftype).t = build_tree_list (specs, NULL_TREE); 
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (1)].ftype).new_type_flag; }
    break;

  case 828:
/* Line 1792 of yacc.c  */
#line 3641 "parse.y"
    { tree specs = strip_attrs ((yyvsp[(1) - (2)].ttype));
		  (yyval.ftype).t = build_tree_list (specs, (yyvsp[(2) - (2)].ttype)); 
		  (yyval.ftype).new_type_flag = 0; }
    break;

  case 829:
/* Line 1792 of yacc.c  */
#line 3648 "parse.y"
    { (yyval.ftype).t = build_tree_list (NULL_TREE, (yyvsp[(1) - (1)].ftype).t);
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (1)].ftype).new_type_flag;  }
    break;

  case 830:
/* Line 1792 of yacc.c  */
#line 3651 "parse.y"
    { (yyval.ftype).t = build_tree_list ((yyvsp[(2) - (2)].ttype), (yyvsp[(1) - (2)].ftype).t);
		  (yyval.ftype).new_type_flag = (yyvsp[(1) - (2)].ftype).new_type_flag;  }
    break;

  case 833:
/* Line 1792 of yacc.c  */
#line 3662 "parse.y"
    { see_typename (); }
    break;

  case 834:
/* Line 1792 of yacc.c  */
#line 3667 "parse.y"
    {
		  error ("type specifier omitted for parameter");
		  (yyval.ttype) = build_tree_list (integer_type_node, NULL_TREE);
		}
    break;

  case 835:
/* Line 1792 of yacc.c  */
#line 3672 "parse.y"
    {
		  error ("type specifier omitted for parameter");
		  if (TREE_CODE ((yyval.ttype)) == SCOPE_REF
		      && (TREE_CODE (TREE_OPERAND ((yyval.ttype), 0)) == TEMPLATE_TYPE_PARM
			  || TREE_CODE (TREE_OPERAND ((yyval.ttype), 0)) == TEMPLATE_TEMPLATE_PARM))
		    cp_error ("  perhaps you want `typename %E' to make it a type", (yyval.ttype));
		  (yyval.ttype) = build_tree_list (integer_type_node, (yyval.ttype));
		}
    break;

  case 836:
/* Line 1792 of yacc.c  */
#line 3684 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 837:
/* Line 1792 of yacc.c  */
#line 3686 "parse.y"
    { (yyval.ttype) = (yyvsp[(3) - (4)].ttype); }
    break;

  case 838:
/* Line 1792 of yacc.c  */
#line 3688 "parse.y"
    { (yyval.ttype) = build_decl_list (NULL_TREE, NULL_TREE); }
    break;

  case 839:
/* Line 1792 of yacc.c  */
#line 3693 "parse.y"
    { (yyval.ttype) = build_decl_list (NULL_TREE, groktypename((yyvsp[(1) - (1)].ftype).t)); }
    break;

  case 841:
/* Line 1792 of yacc.c  */
#line 3699 "parse.y"
    {
		  TREE_CHAIN ((yyvsp[(3) - (3)].ttype)) = (yyval.ttype);
		  (yyval.ttype) = (yyvsp[(3) - (3)].ttype);
		}
    break;

  case 842:
/* Line 1792 of yacc.c  */
#line 3707 "parse.y"
    { (yyval.ttype) = NULL_TREE; }
    break;

  case 843:
/* Line 1792 of yacc.c  */
#line 3709 "parse.y"
    { (yyval.ttype) = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 844:
/* Line 1792 of yacc.c  */
#line 3711 "parse.y"
    { (yyval.ttype) = make_reference_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype)); }
    break;

  case 845:
/* Line 1792 of yacc.c  */
#line 3713 "parse.y"
    { tree arg = make_pointer_declarator ((yyvsp[(2) - (3)].ttype), (yyvsp[(3) - (3)].ttype));
		  (yyval.ttype) = build_parse_node (SCOPE_REF, (yyvsp[(1) - (3)].ttype), arg);
		}
    break;

  case 846:
/* Line 1792 of yacc.c  */
#line 3720 "parse.y"
    { got_scope = NULL_TREE; }
    break;

  case 847:
/* Line 1792 of yacc.c  */
#line 3725 "parse.y"
    { (yyval.ttype) = ansi_opname[MULT_EXPR]; }
    break;

  case 848:
/* Line 1792 of yacc.c  */
#line 3727 "parse.y"
    { (yyval.ttype) = ansi_opname[TRUNC_DIV_EXPR]; }
    break;

  case 849:
/* Line 1792 of yacc.c  */
#line 3729 "parse.y"
    { (yyval.ttype) = ansi_opname[TRUNC_MOD_EXPR]; }
    break;

  case 850:
/* Line 1792 of yacc.c  */
#line 3731 "parse.y"
    { (yyval.ttype) = ansi_opname[PLUS_EXPR]; }
    break;

  case 851:
/* Line 1792 of yacc.c  */
#line 3733 "parse.y"
    { (yyval.ttype) = ansi_opname[MINUS_EXPR]; }
    break;

  case 852:
/* Line 1792 of yacc.c  */
#line 3735 "parse.y"
    { (yyval.ttype) = ansi_opname[BIT_AND_EXPR]; }
    break;

  case 853:
/* Line 1792 of yacc.c  */
#line 3737 "parse.y"
    { (yyval.ttype) = ansi_opname[BIT_IOR_EXPR]; }
    break;

  case 854:
/* Line 1792 of yacc.c  */
#line 3739 "parse.y"
    { (yyval.ttype) = ansi_opname[BIT_XOR_EXPR]; }
    break;

  case 855:
/* Line 1792 of yacc.c  */
#line 3741 "parse.y"
    { (yyval.ttype) = ansi_opname[BIT_NOT_EXPR]; }
    break;

  case 856:
/* Line 1792 of yacc.c  */
#line 3743 "parse.y"
    { (yyval.ttype) = ansi_opname[COMPOUND_EXPR]; }
    break;

  case 857:
/* Line 1792 of yacc.c  */
#line 3745 "parse.y"
    { (yyval.ttype) = ansi_opname[(yyvsp[(2) - (2)].code)]; }
    break;

  case 858:
/* Line 1792 of yacc.c  */
#line 3747 "parse.y"
    { (yyval.ttype) = ansi_opname[LT_EXPR]; }
    break;

  case 859:
/* Line 1792 of yacc.c  */
#line 3749 "parse.y"
    { (yyval.ttype) = ansi_opname[GT_EXPR]; }
    break;

  case 860:
/* Line 1792 of yacc.c  */
#line 3751 "parse.y"
    { (yyval.ttype) = ansi_opname[(yyvsp[(2) - (2)].code)]; }
    break;

  case 861:
/* Line 1792 of yacc.c  */
#line 3753 "parse.y"
    { (yyval.ttype) = ansi_assopname[(yyvsp[(2) - (2)].code)]; }
    break;

  case 862:
/* Line 1792 of yacc.c  */
#line 3755 "parse.y"
    { (yyval.ttype) = ansi_opname [MODIFY_EXPR]; }
    break;

  case 863:
/* Line 1792 of yacc.c  */
#line 3757 "parse.y"
    { (yyval.ttype) = ansi_opname[(yyvsp[(2) - (2)].code)]; }
    break;

  case 864:
/* Line 1792 of yacc.c  */
#line 3759 "parse.y"
    { (yyval.ttype) = ansi_opname[(yyvsp[(2) - (2)].code)]; }
    break;

  case 865:
/* Line 1792 of yacc.c  */
#line 3761 "parse.y"
    { (yyval.ttype) = ansi_opname[POSTINCREMENT_EXPR]; }
    break;

  case 866:
/* Line 1792 of yacc.c  */
#line 3763 "parse.y"
    { (yyval.ttype) = ansi_opname[PREDECREMENT_EXPR]; }
    break;

  case 867:
/* Line 1792 of yacc.c  */
#line 3765 "parse.y"
    { (yyval.ttype) = ansi_opname[TRUTH_ANDIF_EXPR]; }
    break;

  case 868:
/* Line 1792 of yacc.c  */
#line 3767 "parse.y"
    { (yyval.ttype) = ansi_opname[TRUTH_ORIF_EXPR]; }
    break;

  case 869:
/* Line 1792 of yacc.c  */
#line 3769 "parse.y"
    { (yyval.ttype) = ansi_opname[TRUTH_NOT_EXPR]; }
    break;

  case 870:
/* Line 1792 of yacc.c  */
#line 3771 "parse.y"
    { (yyval.ttype) = ansi_opname[COND_EXPR]; }
    break;

  case 871:
/* Line 1792 of yacc.c  */
#line 3773 "parse.y"
    { (yyval.ttype) = ansi_opname[(yyvsp[(2) - (2)].code)]; }
    break;

  case 872:
/* Line 1792 of yacc.c  */
#line 3775 "parse.y"
    { (yyval.ttype) = ansi_opname[COMPONENT_REF]; }
    break;

  case 873:
/* Line 1792 of yacc.c  */
#line 3777 "parse.y"
    { (yyval.ttype) = ansi_opname[MEMBER_REF]; }
    break;

  case 874:
/* Line 1792 of yacc.c  */
#line 3779 "parse.y"
    { (yyval.ttype) = ansi_opname[CALL_EXPR]; }
    break;

  case 875:
/* Line 1792 of yacc.c  */
#line 3781 "parse.y"
    { (yyval.ttype) = ansi_opname[ARRAY_REF]; }
    break;

  case 876:
/* Line 1792 of yacc.c  */
#line 3783 "parse.y"
    { (yyval.ttype) = ansi_opname[NEW_EXPR]; }
    break;

  case 877:
/* Line 1792 of yacc.c  */
#line 3785 "parse.y"
    { (yyval.ttype) = ansi_opname[DELETE_EXPR]; }
    break;

  case 878:
/* Line 1792 of yacc.c  */
#line 3787 "parse.y"
    { (yyval.ttype) = ansi_opname[VEC_NEW_EXPR]; }
    break;

  case 879:
/* Line 1792 of yacc.c  */
#line 3789 "parse.y"
    { (yyval.ttype) = ansi_opname[VEC_DELETE_EXPR]; }
    break;

  case 880:
/* Line 1792 of yacc.c  */
#line 3792 "parse.y"
    { (yyval.ttype) = grokoptypename ((yyvsp[(2) - (3)].ftype).t, (yyvsp[(3) - (3)].ttype)); }
    break;

  case 881:
/* Line 1792 of yacc.c  */
#line 3794 "parse.y"
    { (yyval.ttype) = ansi_opname[ERROR_MARK]; }
    break;


/* Line 1792 of yacc.c  */
#line 10553 "parse.c"
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
#line 3797 "parse.y"


#ifdef SPEW_DEBUG
const char *
debug_yytranslate (value)
    int value;
{
  return yytname[YYTRANSLATE (value)];
}

#endif
