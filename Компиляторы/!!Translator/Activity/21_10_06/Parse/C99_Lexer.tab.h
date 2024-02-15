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

#ifndef YY_YY_C99_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_C99_GRAMMAR_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

#undef CONST
#undef VOID

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
      IDENTIFIER     = 0x0600,
      CONSTANT       = 0x0300,
      CONST_DEC      = 0x0301,
      CONST_OCT      = 0x0302,
      CONST_HEX      = 0x0303,
      CONST_CHAR     = 0x0304,
      CONST_NUM      = 0x0400,
      CONST_NUM_1    = 0x0401,
      CONST_NUM_2    = 0x0402,
      CONST_NUM_HEX  = 0x0403,
      CONST_NUM_HEX_1= 0x0404,
      CONST_NUM_HEX_2= 0x0405,
      STRING_LITERAL = 0x0500,
      INC_OP         = 0x0116,
      DEC_OP         = 0x0117,
      LEFT_OP        = 0x011E,
      RIGHT_OP       = 0x011F,
      LE_OP          = 0x011B,
      GE_OP          = 0x011D,
      EQ_OP          = 0x0118,
      NE_OP          = 0x0119,
      ANDAND_OP      = 0x0112,
      OROR_OP        = 0x0111,
      AND_OP         = 0x0110,
      NOT_OP         = 0x0115,
      TILDA_OP       = 0x0114,
      SUB_OP         = 0x0102,
      ADD_OP         = 0x0101,
      MULTI_OP       = 0x0103,
      DIV_OP         = 0x0104,
      MOD_OP         = 0x0105,
      LT_OP          = 0x011A,
      GT_OP          = 0x011C,
      XOR_OP         = 0x0113,
      OR_OP          = 0x010F,
      QUEST_OP       = 0x0128,
      ASSIGN         = 0x010E,
      MUL_ASSIGN     = 0x0108,
      DIV_ASSIGN     = 0x0109,
      MOD_ASSIGN     = 0x010A,
      ADD_ASSIGN     = 0x0106,
      SUB_ASSIGN     = 0x0107,
      LEFT_ASSIGN    = 0x0120,
      RIGHT_ASSIGN   = 0x0121,
      AND_ASSIGN     = 0x010B,
      XOR_ASSIGN     = 0x010D,
      OR_ASSIGN      = 0x010C,
      ELLIPSIS       = 0x0234,
      PTR_OP         = 0x0233,
      POINT_DEF      = 0x022B,
      COMMA          = 0x022C,
      SEMICOLON      = 0x022D,
      LCRAMP         = 0x0222,
      RCRAMP         = 0x0223,
      COLON          = 0x022E,
      LBRACKET       = 0x0224,
      RBRACKET       = 0x0225,
      LSCRAPE        = 0x0226,
      RSCRAPE        = 0x0227,
      TYPEDEF        = 0x0721,
      EXTERN         = 0x071C,
      STATIC         = 0x0719,
      AUTO           = 0x071A,
      REGISTER       = 0x071D,
      CHAR_DEF       = 0x071B,
      SHORT_DEF      = 0x0712,
      INT_DEF        = 0x0713,
      LONG_DEF       = 0x0714,
      SIGNED         = 0x071E,
      UNSIGNED       = 0x0723,
      FLOAT_DEF      = 0x0715,
      DOUBLE_DEF     = 0x0716,
      CONST          = 0x0718,
      VOLATILE       = 0x0724,
      VOID           = 0x0711,
      STRUCT         = 0x0720,
      UNION          = 0x0722,
      ENUM           = 0x070F,
      SIZEOF         = 0x071F,
      CASE           = 0x070B,
      DEFAULT        = 0x0710,
      IF             = 0x0703,
      ELSE           = 0x0704,
      SWITCH         = 0x070A,
      WHILE          = 0x0702,
      DO             = 0x0705,
      FOR            = 0x0701,
      GOTO           = 0x0706,
      CONTINUE       = 0x0707,
      BREAK          = 0x0708,
      RETURN         = 0x0709,
      BOOL_DEF       = 0x0725,
      COMPLEX        = 0x0726,
      IMAGINARY      = 0x0727,
      INLINE         = 0x0728,
      RESTRICT       = 0x0729,
      TYPE_NAME      = 0x0717,
      MOD_GMOD       = 0x0235,
      MOD_GBEGIN     = 0x0236,
      MOD_GEND       = 0x0237,
      MOD_GTOKEN     = 0x0238,
      MOD_GLEFT      = 0x0239,
      MOD_GRIGHT     = 0x023A
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
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

#endif /* !YY_YY_C99_GRAMMAR_TAB_H_INCLUDED  */
