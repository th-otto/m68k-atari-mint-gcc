/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2058 of yacc.c  */
#line 93 "parse.y"
long itype; tree ttype; char *strtype; enum tree_code code; flagged_type_tree ftype; 

/* Line 2058 of yacc.c  */
#line 147 "parse.h"
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
