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

#ifndef YY_YY_CXXPARSER_TAB_H_INCLUDED
# define YY_YY_CXXPARSER_TAB_H_INCLUDED
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
     ARROW = 258,
     ARROW_STAR = 259,
     DEC = 260,
     EQ = 261,
     GE = 262,
     INC = 263,
     LE = 264,
     LOG_AND = 265,
     LOG_OR = 266,
     NE = 267,
     SHL = 268,
     SHR = 269,
     ASS_ADD = 270,
     ASS_AND = 271,
     ASS_DIV = 272,
     ASS_MOD = 273,
     ASS_MUL = 274,
     ASS_OR = 275,
     ASS_SHL = 276,
     ASS_SHR = 277,
     ASS_SUB = 278,
     ASS_XOR = 279,
     DOT_STAR = 280,
     ELLIPSIS = 281,
     SCOPE = 282,
     PRIVATE = 283,
     PROTECTED = 284,
     PUBLIC = 285,
     BOOL = 286,
     CHAR = 287,
     DOUBLE = 288,
     FLOAT = 289,
     INT = 290,
     LONG = 291,
     SHORT = 292,
     SIGNED = 293,
     UNSIGNED = 294,
     VOID = 295,
     WCHAR_T = 296,
     CLASS = 297,
     ENUM = 298,
     NAMESPACE = 299,
     STRUCT = 300,
     TYPENAME = 301,
     UNION = 302,
     CONST = 303,
     VOLATILE = 304,
     AUTO = 305,
     EXPLICIT = 306,
     EXPORT = 307,
     EXTERN = 308,
     FRIEND = 309,
     INLINE = 310,
     MUTABLE = 311,
     REGISTER = 312,
     STATIC = 313,
     TEMPLATE = 314,
     TYPEDEF = 315,
     USING = 316,
     VIRTUAL = 317,
     ASM = 318,
     BREAK = 319,
     CASE = 320,
     CATCH = 321,
     CONST_CAST = 322,
     CONTINUE = 323,
     DEFAULT = 324,
     DELETE = 325,
     DO = 326,
     DYNAMIC_CAST = 327,
     ELSE = 328,
     FALSE = 329,
     FOR = 330,
     GOTO = 331,
     IF = 332,
     NEW = 333,
     OPERATOR = 334,
     REINTERPRET_CAST = 335,
     RETURN = 336,
     SIZEOF = 337,
     STATIC_CAST = 338,
     SWITCH = 339,
     THIS = 340,
     THROW = 341,
     TRUE = 342,
     TRY = 343,
     TYPEID = 344,
     WHILE = 345,
     CharacterLiteral = 346,
     FloatingLiteral = 347,
     Identifier = 348,
     IntegerLiteral = 349,
     NumberLiteral = 350,
     StringLiteral = 351,
     SHIFT_THERE = 352,
     REDUCE_HERE_MOSTLY = 353
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

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

#endif /* !YY_YY_CXXPARSER_TAB_H_INCLUDED  */
