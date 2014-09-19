/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_YYPARSER_HPP_INCLUDED
# define YY_YY_YYPARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
     IFX = 258,
     TOK_ELSE = 259,
     THISX = 260,
     TOK_DOT = 261,
     TOK_LBRACKET = 262,
     TOK_UNKNOWN = 263,
     TOK_EOF = 264,
     TOK_EOL = 265,
     TOK_SPACE = 266,
     TOK_COMMENT = 267,
     TOK_IDENTIFIER = 268,
     TOK_STRING = 269,
     TOK_CHAR = 270,
     TOK_UNS32 = 271,
     TOK_UNS64 = 272,
     TOK_FLOAT32 = 273,
     TOK_FLOAT64 = 274,
     TOK_DIV = 275,
     TOK_DIVASS = 276,
     TOK_DOTDOT = 277,
     TOK_DOTDOTDOT = 278,
     TOK_AND = 279,
     TOK_ANDASS = 280,
     TOK_ANDAND = 281,
     TOK_OR = 282,
     TOK_ORASS = 283,
     TOK_OROR = 284,
     TOK_MINUS = 285,
     TOK_MINUSASS = 286,
     TOK_MINUSMINUS = 287,
     TOK_PLUS = 288,
     TOK_PLUSASS = 289,
     TOK_PLUSPLUS = 290,
     TOK_LT = 291,
     TOK_LE = 292,
     TOK_SHL = 293,
     TOK_SHLASS = 294,
     TOK_LG = 295,
     TOK_LEG = 296,
     TOK_GT = 297,
     TOK_GE = 298,
     TOK_SHRASS = 299,
     TOK_USHRASS = 300,
     TOK_SHR = 301,
     TOK_USHR = 302,
     TOK_NOT = 303,
     TOK_NOTEQUAL = 304,
     TOK_UE = 305,
     TOK_UNORD = 306,
     TOK_UGE = 307,
     TOK_UG = 308,
     TOK_ULE = 309,
     TOK_UL = 310,
     TOK_LPAREN = 311,
     TOK_RPAREN = 312,
     TOK_RBRACKET = 313,
     TOK_LCURLY = 314,
     TOK_RCURLY = 315,
     TOK_QUESTION = 316,
     TOK_COMMA = 317,
     TOK_SEMICOLON = 318,
     TOK_COLON = 319,
     TOK_COLONCOLON = 320,
     TOK_DOLLAR = 321,
     TOK_ASSIGN = 322,
     TOK_EQUAL = 323,
     TOK_MUL = 324,
     TOK_MULASS = 325,
     TOK_MOD = 326,
     TOK_MODASS = 327,
     TOK_XOR = 328,
     TOK_XORASS = 329,
     TOK_CAT = 330,
     TOK_CATASS = 331,
     TOK_BASE = 332,
     TOK_BREAK = 333,
     TOK_CASE = 334,
     TOK_CATCH = 335,
     TOK_CONST = 336,
     TOK_CONTINUE = 337,
     TOK_DEFAULT = 338,
     TOK_DELEGATE = 339,
     TOK_DELETE = 340,
     TOK_DO = 341,
     TOK_ENUM = 342,
     TOK_EXTENDS = 343,
     TOK_FALSE = 344,
     TOK_FOR = 345,
     TOK_FOREACH = 346,
     TOK_FUNCTION = 347,
     TOK_IF = 348,
     TOK_IN = 349,
     TOK_INT = 350,
     TOK_LOCAL = 351,
     TOK_METAFUNCTION = 352,
     TOK_NAMESPACE = 353,
     TOK_NEW = 354,
     TOK_NULL = 355,
     TOK_RESUME = 356,
     TOK_RETURN = 357,
     TOK_SWITCH = 358,
     TOK_THIS = 359,
     TOK_THROW = 360,
     TOK_TRUE = 361,
     TOK_TRY = 362,
     TOK_VAR = 363,
     TOK_WHILE = 364,
     TOK_YIELD = 365,
     STOK_FILE = 366,
     STOK_LINE = 367,
     STOK_DATE = 368,
     STOK_TIME = 369,
     STOK_TIMESTAMP = 370,
     STOK_VENDOR = 371,
     STOK_VERSION = 372
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 34 "yyparser.y"

    acToken token;
    NodeAST* node;
    BlockAST* block;
    GetVarAST* getvar;
    FunctionAST* func;
    StringList* arglist;
    NodeASTList* nodelist;


/* Line 2053 of yacc.c  */
#line 185 "yyparser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


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

#endif /* !YY_YY_YYPARSER_HPP_INCLUDED  */
