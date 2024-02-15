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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         yy_parse
#define yylex           yy_lex
#define yyerror         yy_error
#define yylval          yy_lval
#define yychar          yy_char
#define yydebug         yy_debug
#define yynerrs         yy_nerrs

/* Copy the first part of user declarations.  */



enum class T_Maker { DefType, ExpressionSLL, ExpressionSLR, AddToList, MakerSNode, SaveLexeme, Number, Ident, 
                     Label, Params, BegIndexLL, BegIndexLR, IndexLL, IndexLR, EndIndex, Binary, 
                     Unary, IncDec, Primary, Cast, Question, ExpressionsLL, ExpressionsLR, DefParVar, 
                     DefParArr, ParVarAssign, EndParams, FuncIdent, BodyFunc, EndAInit, DefArray, DRange, 
                     DefArrD1AEmpty, DefIdent, DefVarAssign, PushDef, RefDef, Define, BegDo, Do, 
                     BegWhile, While, BegFor, For, If, GoTo, Break, Continue, 
                     Return, BegStmExprLL, BegStmExprLR, Compaund, NodeNull, NodeListLL, NodeListLR, EndBlock, 
                     Part, PopType, AddToExpr, BegQuestion, MidQuestion, MidDo, MidWhile, BegIf, 
                     Then, Else, PrefFor, ConditionFor, PostFor, EndDefine, EndRanges, BegAInit, 
                     AInitItem, BegInitial, EndInitial, BegDefVarAssign, BegParVarAssign, MakerTurn, SimpleLexeme, LexTypeName, 
                     Expressions
};


enum class S_Node  { None, Node, Unary, Binary, Logical, Trio, Number, Primary, 
                     Type, Cast, IncDec, Expressions, Compaund, Statements, DefVar, DefArr, 
                     DefFunc, Define, Var, Call, Index, For, While, Do, 
                     Label, GoTo, Break, Continue, Return, If, SwitchCase, SwitchItem, 
                     Switch, List, Ranges, Null, NodeOne, NodeTwo, RefDef, Lexeme, 
                     Param, Formula, Produce, Maker, Tokens, Enums, Item
};

#define YYPARSE_PARAM parm
#define YYLEX_PARAM parm
#define YYERROR_VERBOSE
#define YYSTYPE T_Lexeme_SNode



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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yy_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     Oper_Add = 257,
     Oper_Sub = 258,
     Oper_Multi = 259,
     Oper_Div = 260,
     Oper_Mod = 261,
     Oper_AddAssign = 262,
     Oper_SubAssign = 263,
     Oper_MultiAssign = 264,
     Oper_DivAssign = 265,
     Oper_ModAssign = 266,
     Oper_AndAssign = 267,
     Oper_OrAssign = 268,
     Oper_XOrAssign = 269,
     Oper_Assign = 270,
     Oper_Or = 271,
     Oper_And = 272,
     Oper_OrOr = 273,
     Oper_AndAnd = 274,
     Oper_XOr = 275,
     Oper_Tilda = 276,
     Oper_Not = 277,
     Oper_PlusPlus = 278,
     Oper_MinusMinus = 279,
     Oper_Equ = 280,
     Oper_NotEqu = 281,
     Oper_LT = 282,
     Oper_LE = 283,
     Oper_GT = 284,
     Oper_GE = 285,
     Oper_LShift = 286,
     Oper_RShift = 287,
     Oper_LShiftAssign = 288,
     Oper_RShiftAssign = 289,
     Oper_Question = 296,
     Separator_LeftCramp = 546,
     Separator_RightCramp = 547,
     Separator_LeftBracket = 548,
     Separator_RightBracket = 549,
     Separator_LeftScrape = 550,
     Separator_RightScrape = 551,
     Separator_Comma = 556,
     Separator_Semicolon = 557,
     Separator_Colon = 558,
     Integer_lexeme = 768,
     Number_lexeme = 1024,
     Ident_lexeme = 1536,
     Reserv_For = 1793,
     Reserv_While = 1794,
     Reserv_If = 1795,
     Reserv_Else = 1796,
     Reserv_Do = 1797,
     Reserv_GoTo = 1798,
     Reserv_Continue = 1799,
     Reserv_Break = 1800,
     Reserv_Return = 1801,
     Reserv_Void = 1809,
     Reserv_Const = 1816,
     Reserv_Static = 1817,
     Syntax_DefType = 3078
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yy_parse (void *YYPARSE_PARAM);
#else
int yy_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yy_parse (void);
#else
int yy_parse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* Copy the second part of user declarations.  */



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
#define YYLAST   447

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  193
/* YYNRULES -- Number of rules.  */
#define YYNRULES  300
/* YYNRULES -- Number of states.  */
#define YYNSTATES  411

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   3079

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       2,     2,     2,     2,     2,     2,    36,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,    37,    38,    39,    40,
      41,    42,     2,     2,     2,     2,    43,    44,    45,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    47,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    48,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,    50,    51,    52,    53,    54,    55,
      56,    57,     2,     2,     2,     2,     2,     2,     2,    58,
       2,     2,     2,     2,     2,     2,    59,    60,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,     2
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     7,    13,    14,    15,    20,
      21,    25,    26,    29,    30,    34,    35,    36,    42,    44,
      45,    46,    52,    53,    54,    60,    62,    64,    66,    70,
      72,    74,    77,    78,    79,    85,    87,    90,    91,    95,
      96,   100,   101,   104,   105,   110,   111,   115,   116,   120,
     121,   124,   128,   130,   131,   135,   136,   140,   142,   143,
     148,   151,   153,   154,   155,   161,   163,   164,   165,   166,
     173,   177,   179,   180,   181,   182,   183,   184,   185,   195,
     196,   197,   198,   203,   204,   205,   206,   211,   212,   213,
     220,   221,   228,   229,   234,   238,   244,   248,   249,   250,
     257,   259,   261,   263,   267,   269,   270,   274,   275,   276,
     282,   286,   289,   291,   292,   297,   300,   302,   303,   304,
     309,   310,   311,   317,   319,   320,   323,   324,   325,   330,
     333,   335,   337,   339,   340,   344,   346,   348,   349,   354,
     356,   358,   360,   362,   364,   366,   368,   370,   372,   374,
     376,   378,   380,   382,   384,   386,   388,   390,   392,   394,
     396,   398,   400,   402,   404,   406,   408,   410,   412,   414,
     416,   418,   420,   422,   424,   428,   430,   431,   432,   440,
     442,   446,   448,   452,   454,   458,   460,   464,   466,   470,
     472,   476,   478,   482,   484,   488,   490,   494,   496,   500,
     502,   505,   507,   508,   512,   513,   516,   519,   522,   525,
     530,   532,   536,   537,   540,   541,   544,   545,   549,   550,
     554,   555,   559,   560,   563,   565,   569,   572,   574,   577,
     581,   582,   586,   587,   592,   593,   597,   599,   600,   604,
     606,   608,   610,   612,   614,   617,   619,   622,   623,   624,
     625,   626,   637,   638,   647,   648,   655,   656,   661,   664,
     667,   669,   672,   675,   676,   677,   685,   686,   690,   692,
     693,   698,   700,   703,   705,   707,   709,   711,   713,   715,
     717,   719,   722,   725,   727,   729,   731,   733,   736,   738,
     740,   742,   744,   747,   749,   750,   753,   755,   757,   759,
     761
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      63,     0,    -1,   248,    -1,    -1,    -1,    59,    61,    65,
      18,    66,    -1,    -1,    -1,    61,    67,    18,    68,    -1,
      -1,    59,    61,    69,    -1,    -1,    61,    70,    -1,    -1,
      64,    48,    72,    -1,    -1,    -1,    71,    16,    74,    75,
     178,    -1,    71,    -1,    -1,    -1,    64,    48,    77,    78,
     144,    -1,    -1,    -1,    76,    16,    80,    81,   178,    -1,
      76,    -1,    79,    -1,    73,    -1,    83,    43,    82,    -1,
      82,    -1,    44,    -1,    37,    38,    -1,    -1,    -1,    37,
      85,    86,   245,    38,    -1,    40,    -1,    83,    40,    -1,
      -1,    89,    87,    84,    -1,    -1,    60,    58,    91,    -1,
      -1,    58,    92,    -1,    -1,    60,    59,    61,    94,    -1,
      -1,    60,    61,    95,    -1,    -1,    59,    61,    96,    -1,
      -1,    61,    97,    -1,    98,    43,   161,    -1,   161,    -1,
      -1,    93,   100,    98,    -1,    -1,    42,   102,   143,    -1,
      42,    -1,    -1,   178,    42,   103,   143,    -1,   178,    42,
      -1,   101,    -1,    -1,    -1,   108,    16,   106,   107,   138,
      -1,   108,    -1,    -1,    -1,    -1,    48,   109,    41,   110,
     111,   104,    -1,    43,    98,    44,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,   114,   115,   116,    16,
     117,   118,   178,   119,    -1,    -1,    -1,    -1,    48,   121,
     122,   123,    -1,    -1,    -1,    -1,    48,   125,   126,   127,
      -1,    -1,    -1,    93,    48,   129,    39,   130,    88,    -1,
      -1,    93,   105,   131,    43,    98,    44,    -1,    -1,    93,
     105,   132,    44,    -1,    93,   113,   112,    -1,    93,   120,
      43,    98,    44,    -1,    93,   124,    44,    -1,    -1,    -1,
      90,    48,   134,    39,   135,    88,    -1,   128,    -1,   138,
      -1,   178,    -1,   137,    43,   136,    -1,   136,    -1,    -1,
      37,    38,   139,    -1,    -1,    -1,    37,   140,   141,   137,
      38,    -1,    41,   178,    42,    -1,   143,   142,    -1,   142,
      -1,    -1,    41,    42,   145,   143,    -1,    41,    42,    -1,
     143,    -1,    -1,    -1,    48,   147,   148,   144,    -1,    -1,
      -1,   146,    16,   150,   151,   138,    -1,   146,    -1,    -1,
      48,   153,    -1,    -1,    -1,    16,   155,   156,   178,    -1,
     152,   154,    -1,   152,    -1,   149,    -1,   157,    -1,    -1,
      18,   160,   158,    -1,   159,    -1,   158,    -1,    -1,   162,
      43,   178,   163,    -1,   178,    -1,     8,    -1,     9,    -1,
      10,    -1,    11,    -1,    12,    -1,    16,    -1,    14,    -1,
      15,    -1,    13,    -1,    34,    -1,    35,    -1,    36,    -1,
      19,    -1,    20,    -1,    17,    -1,    21,    -1,    18,    -1,
      26,    -1,    27,    -1,    29,    -1,    28,    -1,    31,    -1,
      30,    -1,    32,    -1,    33,    -1,     3,    -1,     4,    -1,
       5,    -1,     6,    -1,     7,    -1,    23,    -1,    22,    -1,
      24,    -1,    25,    -1,   179,   164,   178,    -1,   179,    -1,
      -1,    -1,   182,   165,   180,   253,    45,   181,   179,    -1,
     182,    -1,   182,   166,   183,    -1,   183,    -1,   183,   167,
     184,    -1,   184,    -1,   184,   168,   185,    -1,   185,    -1,
     185,   169,   186,    -1,   186,    -1,   186,   170,   187,    -1,
     187,    -1,   187,   171,   188,    -1,   188,    -1,   188,   172,
     189,    -1,   189,    -1,   189,   173,   190,    -1,   190,    -1,
     190,   174,   191,    -1,   191,    -1,   191,   175,   196,    -1,
     196,    -1,   198,   177,    -1,   198,    -1,    -1,    59,    61,
     194,    -1,    -1,    61,   195,    -1,   176,   196,    -1,   174,
     196,    -1,   177,   196,    -1,    39,   193,    40,   196,    -1,
     192,    -1,    39,   252,    40,    -1,    -1,    46,   199,    -1,
      -1,    47,   200,    -1,    -1,    48,   201,   206,    -1,    -1,
      48,   202,   207,    -1,    -1,    61,   203,   197,    -1,    -1,
      48,   204,    -1,   197,    -1,    41,   253,    42,    -1,   206,
     205,    -1,   205,    -1,    39,    40,    -1,    39,   254,    40,
      -1,    -1,    37,    38,   209,    -1,    -1,    37,   210,   245,
      38,    -1,    -1,    18,   212,   157,    -1,   157,    -1,    -1,
      93,   214,   211,    -1,   251,    -1,    44,    -1,   241,    -1,
     242,    -1,    44,    -1,   213,    44,    -1,    40,    -1,   250,
      40,    -1,    -1,    -1,    -1,    -1,    49,    39,   219,   215,
     220,   216,   221,   217,   222,   243,    -1,    -1,    53,   224,
     243,    50,    39,   213,    40,    44,    -1,    -1,    50,   226,
      39,   213,    40,   243,    -1,    -1,    54,    48,   228,    44,
      -1,    56,    44,    -1,    55,    44,    -1,    44,    -1,   253,
      44,    -1,    57,   231,    -1,    -1,    -1,    51,    39,   234,
     213,    40,   235,   243,    -1,    -1,    48,   237,    45,    -1,
     236,    -1,    -1,   233,    52,   240,   243,    -1,   233,    -1,
     238,   243,    -1,   223,    -1,   225,    -1,   218,    -1,   227,
      -1,   229,    -1,   230,    -1,   232,    -1,   208,    -1,    99,
      44,    -1,   250,    44,    -1,    44,    -1,   241,    -1,   239,
      -1,   242,    -1,   244,   243,    -1,   243,    -1,   244,    -1,
      44,    -1,   133,    -1,   247,   246,    -1,   246,    -1,    -1,
     249,   247,    -1,   162,    -1,   162,    -1,   162,    -1,   162,
      -1,   162,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,    99,    99,    99,   100,   100,   100,   101,
     101,   102,   102,   105,   105,   108,   108,   108,   109,   112,
     112,   112,   115,   115,   115,   116,   119,   120,   123,   124,
     127,   128,   129,   129,   129,   132,   133,   136,   136,   139,
     139,   140,   140,   143,   143,   144,   144,   145,   145,   146,
     146,   149,   150,   153,   153,   156,   156,   157,   158,   158,
     159,   162,   165,   165,   165,   166,   169,   169,   169,   169,
     172,   173,   176,   176,   176,   176,   176,   176,   176,   179,
     179,   179,   179,   182,   182,   182,   182,   185,   185,   185,
     186,   186,   187,   187,   188,   189,   190,   193,   193,   193,
     194,   197,   198,   201,   202,   205,   205,   206,   206,   206,
     209,   212,   213,   216,   216,   217,   218,   221,   221,   221,
     224,   224,   224,   225,   228,   228,   231,   231,   231,   234,
     235,   238,   239,   242,   242,   245,   246,   249,   249,   250,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   266,   269,   272,   275,   278,   281,   284,   285,   288,
     289,   290,   291,   294,   295,   298,   299,   302,   303,   304,
     307,   308,   311,   312,   315,   316,   319,   319,   319,   320,
     323,   324,   327,   328,   331,   332,   335,   336,   339,   340,
     343,   344,   347,   348,   351,   352,   355,   356,   359,   360,
     363,   364,   367,   367,   368,   368,   371,   372,   373,   374,
     375,   378,   381,   381,   382,   382,   383,   383,   384,   384,
     385,   385,   386,   386,   387,   390,   393,   394,   397,   398,
     401,   401,   402,   402,   405,   405,   406,   409,   409,   410,
     413,   414,   415,   418,   419,   422,   423,   426,   426,   426,
     426,   426,   429,   429,   432,   432,   435,   435,   438,   441,
     444,   445,   448,   451,   451,   451,   454,   454,   457,   460,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   473,   476,   479,   480,   481,   482,   485,   486,   489,
     492,   493,   496,   497,   500,   500,   503,   506,   509,   512,
     515
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Oper_Add", "Oper_Sub", "Oper_Multi",
  "Oper_Div", "Oper_Mod", "Oper_AddAssign", "Oper_SubAssign",
  "Oper_MultiAssign", "Oper_DivAssign", "Oper_ModAssign", "Oper_AndAssign",
  "Oper_OrAssign", "Oper_XOrAssign", "Oper_Assign", "Oper_Or", "Oper_And",
  "Oper_OrOr", "Oper_AndAnd", "Oper_XOr", "Oper_Tilda", "Oper_Not",
  "Oper_PlusPlus", "Oper_MinusMinus", "Oper_Equ", "Oper_NotEqu", "Oper_LT",
  "Oper_LE", "Oper_GT", "Oper_GE", "Oper_LShift", "Oper_RShift",
  "Oper_LShiftAssign", "Oper_RShiftAssign", "Oper_Question",
  "Separator_LeftCramp", "Separator_RightCramp", "Separator_LeftBracket",
  "Separator_RightBracket", "Separator_LeftScrape",
  "Separator_RightScrape", "Separator_Comma", "Separator_Semicolon",
  "Separator_Colon", "Integer_lexeme", "Number_lexeme", "Ident_lexeme",
  "Reserv_For", "Reserv_While", "Reserv_If", "Reserv_Else", "Reserv_Do",
  "Reserv_GoTo", "Reserv_Continue", "Reserv_Break", "Reserv_Return",
  "Reserv_Void", "Reserv_Const", "Reserv_Static", "Syntax_DefType",
  "$accept", "Program", "DefParType", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "DefBegParVar", "$@7", "DefParVar", "$@8", "$@9", "DefBegParArr",
  "$@10", "$@11", "DefParArr", "$@12", "$@13", "DefParItem", "DefParams",
  "BodyFunc", "$@14", "$@15", "DefFuncParBody", "DefParBodyFunc", "$@16",
  "DefVoidType", "$@17", "$@18", "DefType", "$@19", "$@20", "$@21", "$@22",
  "CommaDefItem", "Define", "$@23", "DefineBegRanges", "$@24", "$@25",
  "DefineBegArr", "DefineArr", "$@26", "$@27", "IdentLeftScrape", "$@28",
  "$@29", "$@30", "DefineVarAssign", "DefVariableAssign", "$@31", "$@32",
  "$@33", "$@34", "$@35", "$@36", "DefVarComma", "$@37", "$@38", "$@39",
  "DefVarSemicolon", "$@40", "$@41", "$@42", "DefFuncArrVar", "$@43",
  "$@44", "$@45", "$@46", "DefFuncDefine", "$@47", "$@48", "AInitItem",
  "AInitial", "Initializer", "$@49", "$@50", "$@51", "DefRange",
  "DefRanges", "DefBegRanges", "$@52", "DefBegArr", "$@53", "$@54",
  "DefArr", "$@55", "$@56", "DefVarIdent", "$@57", "DefVarAssign", "$@58",
  "$@59", "DefVar", "DefIAV", "RefDefIAV", "$@60", "DefItem",
  "Expressions", "$@61", "PriorAssign", "PriorQuestion", "PriorOrOr",
  "PriorAndAnd", "PriorOr", "PriorXOr", "PriorAnd", "PriorEqu",
  "PriorCompare", "PriorShift", "PriorTerm", "PriorFactor", "PriorUnary",
  "PriorIncDec", "Assign", "Question", "$@62", "$@63", "OrOr", "AndAnd",
  "Or", "XOr", "And", "Equ", "Compare", "Shift", "Term", "Factor",
  "UnaryIncDec", "DefTypeCast", "$@64", "$@65", "Unary", "Primary",
  "PrimaryExpr", "$@66", "$@67", "$@68", "$@69", "$@70", "$@71", "Range",
  "Ranges", "CallParams", "CompaundStmnt", "$@72", "$@73", "ConditionVar",
  "$@74", "Condition", "$@75", "ForPrefix", "ForCondition", "ForPostfix",
  "ForStmnt", "$@76", "$@77", "$@78", "$@79", "DoStmnt", "$@80",
  "WhileStmnt", "$@81", "GoToStmnt", "$@82", "BreakStmnt", "ContinueStmnt",
  "ReturnValue", "ReturnStmnt", "BegIfStmnt", "$@83", "$@84", "LabelIdent",
  "$@85", "LabelList", "Statement", "$@86", "DefineSemi", "ExprSemi",
  "DefExpr", "StmExprList", "StmExpr", "DefFAV", "DefinesList", "Defines",
  "$@87", "ExpressionExpression", "ExpressionCondition", "ExpressionNone",
  "ExpressionValue", "ExpressionValueList", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,  3079,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   296,   546,   547,   548,
     549,   550,   551,   556,   557,   558,   768,  1024,  1536,  1793,
    1794,  1795,  1796,  1797,  1798,  1799,  1800,  1801,  1809,  1816,
    1817,  3078
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    65,    66,    64,    67,    68,    64,    69,
      64,    70,    64,    72,    71,    74,    75,    73,    73,    77,
      78,    76,    80,    81,    79,    79,    82,    82,    83,    83,
      84,    84,    85,    86,    84,    87,    87,    89,    88,    91,
      90,    92,    90,    94,    93,    95,    93,    96,    93,    97,
      93,    98,    98,   100,    99,   102,   101,   101,   103,   101,
     101,   104,   106,   107,   105,   105,   109,   110,   111,   108,
     112,   112,   114,   115,   116,   117,   118,   119,   113,   121,
     122,   123,   120,   125,   126,   127,   124,   129,   130,   128,
     131,   128,   132,   128,   128,   128,   128,   134,   135,   133,
     133,   136,   136,   137,   137,   139,   138,   140,   141,   138,
     142,   143,   143,   145,   144,   144,   144,   147,   148,   146,
     150,   151,   149,   149,   153,   152,   155,   156,   154,   157,
     157,   158,   158,   160,   159,   161,   161,   163,   162,   162,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   165,   166,   167,   168,   169,   170,   171,   171,   172,
     172,   172,   172,   173,   173,   174,   174,   175,   175,   175,
     176,   176,   177,   177,   178,   178,   180,   181,   179,   179,
     182,   182,   183,   183,   184,   184,   185,   185,   186,   186,
     187,   187,   188,   188,   189,   189,   190,   190,   191,   191,
     192,   192,   194,   193,   195,   193,   196,   196,   196,   196,
     196,   197,   199,   198,   200,   198,   201,   198,   202,   198,
     203,   198,   204,   198,   198,   205,   206,   206,   207,   207,
     209,   208,   210,   208,   212,   211,   211,   214,   213,   213,
     215,   215,   215,   216,   216,   217,   217,   219,   220,   221,
     222,   218,   224,   223,   226,   225,   228,   227,   229,   230,
     231,   231,   232,   234,   235,   233,   237,   236,   238,   240,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   241,   242,   243,   243,   243,   243,   244,   244,   245,
     246,   246,   247,   247,   249,   248,   250,   251,   252,   253,
     254
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     0,     5,     0,     0,     4,     0,
       3,     0,     2,     0,     3,     0,     0,     5,     1,     0,
       0,     5,     0,     0,     5,     1,     1,     1,     3,     1,
       1,     2,     0,     0,     5,     1,     2,     0,     3,     0,
       3,     0,     2,     0,     4,     0,     3,     0,     3,     0,
       2,     3,     1,     0,     3,     0,     3,     1,     0,     4,
       2,     1,     0,     0,     5,     1,     0,     0,     0,     6,
       3,     1,     0,     0,     0,     0,     0,     0,     9,     0,
       0,     0,     4,     0,     0,     0,     4,     0,     0,     6,
       0,     6,     0,     4,     3,     5,     3,     0,     0,     6,
       1,     1,     1,     3,     1,     0,     3,     0,     0,     5,
       3,     2,     1,     0,     4,     2,     1,     0,     0,     4,
       0,     0,     5,     1,     0,     2,     0,     0,     4,     2,
       1,     1,     1,     0,     3,     1,     1,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     0,     7,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     1,     0,     3,     0,     2,     2,     2,     2,     4,
       1,     3,     0,     2,     0,     2,     0,     3,     0,     3,
       0,     3,     0,     2,     1,     3,     2,     1,     2,     3,
       0,     3,     0,     4,     0,     3,     1,     0,     3,     1,
       1,     1,     1,     1,     2,     1,     2,     0,     0,     0,
       0,    10,     0,     8,     0,     6,     0,     4,     2,     2,
       1,     2,     2,     0,     0,     7,     0,     3,     1,     0,
       4,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     2,     1,     0,     2,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
     294,     0,     2,     0,     1,   290,    41,     0,     0,    49,
       0,     0,   100,   291,   293,   295,    42,    47,    39,     0,
      45,    50,    97,    66,    90,    65,     0,     0,     0,   292,
      48,    40,    43,    46,     0,     0,    73,    80,    84,     0,
       0,     0,    62,     0,    71,    94,     0,    96,    44,    98,
      67,    74,    81,    85,    88,     0,    93,    63,   133,   124,
       0,   123,   131,   130,   132,   136,   135,    52,     0,    37,
      68,     0,    82,    86,    37,     0,     0,     0,   118,   125,
       0,    70,   120,   126,   129,    95,    99,     0,     0,    75,
      89,    91,   107,    64,   134,     0,    51,   121,   127,    35,
       0,     6,     0,    18,    27,    25,    26,    29,     0,     0,
     165,   166,   171,   170,   172,   173,     0,    57,   212,   214,
     222,   220,    61,    69,     0,     0,     0,     0,   175,   179,
     181,   183,   185,   187,   189,   191,   193,   195,   197,   210,
     199,   224,   201,    76,   105,   108,     0,   112,   116,   119,
       0,     0,     3,     0,    12,    13,    15,    22,    36,     0,
      32,    30,    38,     0,   204,   298,   139,     0,     0,     0,
     213,   215,     0,     0,   223,     0,   207,   206,   208,    60,
     140,   141,   142,   143,   144,   148,   146,   147,   145,   149,
     150,     0,   152,   151,   176,     0,   153,     0,   154,     0,
     155,     0,   156,     0,   157,   158,     0,   160,   159,   162,
     161,     0,   163,   164,     0,     0,   167,   168,   169,     0,
     200,     0,   106,     0,   115,     0,     0,   111,   122,   128,
       0,    10,     7,    14,    20,    16,    23,    28,    31,    33,
     202,   205,     0,     0,   211,    56,     0,   227,   217,     0,
     219,     0,   221,     0,   174,     0,   180,   182,   184,   186,
     188,   190,   192,   194,   196,   198,    77,   104,     0,   101,
     102,     0,   110,     4,     8,     0,     0,     0,     0,   203,
     137,   209,   299,     0,   226,   228,   300,     0,    59,     0,
      78,   109,     0,   114,     5,    21,    17,    24,   232,   283,
     222,     0,   254,     0,   252,     0,     0,     0,     0,     0,
      49,    53,     0,   296,   280,   275,   273,   274,   276,   277,
     278,   279,   271,   268,     0,   285,   284,   286,   288,   289,
       0,     0,   138,   225,   229,   177,   103,   230,     0,     0,
     247,     0,   263,     0,   256,   259,   258,   260,   262,     0,
       0,   281,   269,   272,   287,    34,   282,     0,   231,     0,
     267,     0,     0,     0,     0,     0,   261,    54,     0,   178,
     233,   240,   248,   241,   242,   237,   297,     0,   239,     0,
       0,   257,   270,     0,     0,     0,   264,     0,   243,     0,
     249,   234,   124,   236,   238,   255,     0,     0,   244,     0,
       0,   265,     0,   245,   250,     0,   235,   253,     0,   246,
     251
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   102,   230,   294,   153,   274,   231,   154,   103,
     233,   104,   235,   276,   105,   234,   275,   106,   236,   277,
     107,   108,   162,   239,   278,   109,    86,    87,    10,    31,
      16,   311,    48,    33,    30,    21,    60,   312,   350,   122,
     169,   253,   123,    24,    57,    76,    25,    35,    70,    88,
      45,    26,    36,    51,    71,   143,   221,   290,    27,    37,
      52,    72,    28,    38,    53,    73,    12,    39,    74,    40,
      41,    13,    34,    69,   267,   268,   269,   222,   145,   223,
     147,   148,   149,   271,    61,    78,    95,    62,    97,   150,
      63,    79,    84,    98,   151,    64,    65,    66,    77,    67,
     313,   332,   191,   194,   195,   197,   199,   201,   203,   206,
     211,   214,   124,   219,   125,   126,   166,   128,   255,   357,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   167,   279,   241,   140,   141,   142,   170,   171,   172,
     173,   175,   174,   247,   248,   250,   314,   358,   338,   394,
     400,   377,   384,   372,   390,   404,   315,   361,   383,   399,
     408,   316,   343,   317,   341,   318,   365,   319,   320,   348,
     321,   322,   363,   396,   323,   339,   324,   325,   368,   326,
     327,   328,   329,   330,    14,    15,     2,     3,   331,   378,
     168,   283,   287
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -355
static const yytype_int16 yypact[] =
{
    -355,    22,  -355,    -4,  -355,  -355,  -355,   -30,    33,  -355,
      11,    23,  -355,  -355,  -355,    -4,  -355,  -355,  -355,    32,
    -355,  -355,  -355,     4,    62,    92,     2,    68,    85,  -355,
    -355,  -355,  -355,  -355,    89,    77,  -355,  -355,  -355,    97,
      88,    94,  -355,     1,  -355,  -355,     1,  -355,  -355,  -355,
    -355,  -355,  -355,  -355,  -355,     1,  -355,  -355,  -355,    98,
      20,   128,  -355,   130,  -355,  -355,  -355,  -355,    70,  -355,
    -355,   131,  -355,  -355,  -355,    79,   112,   103,  -355,  -355,
       1,  -355,  -355,  -355,  -355,  -355,  -355,   -17,    73,  -355,
    -355,  -355,   114,  -355,  -355,   109,  -355,  -355,  -355,  -355,
      93,   105,   107,   142,  -355,   143,  -355,  -355,    29,   -10,
    -355,  -355,  -355,  -355,  -355,  -355,   267,   119,  -355,  -355,
      60,  -355,  -355,  -355,   386,   386,   386,   129,   154,     5,
     152,   156,   158,   162,    61,    55,    84,   121,    74,  -355,
    -355,  -355,   102,  -355,  -355,  -355,   294,  -355,   133,  -355,
     112,   386,   134,   163,  -355,   144,  -355,  -355,  -355,    43,
     145,  -355,  -355,   123,   147,   148,  -355,   165,   175,   133,
    -355,  -355,   146,   159,  -355,   177,  -355,  -355,  -355,   176,
    -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,   386,  -355,  -355,  -355,   386,  -355,   386,  -355,   386,
    -355,   386,  -355,   386,  -355,  -355,   386,  -355,  -355,  -355,
    -355,   386,  -355,  -355,   386,   386,  -355,  -355,  -355,   386,
    -355,   386,  -355,   300,   179,   151,   386,  -355,  -355,  -355,
     203,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,   386,   386,  -355,   133,   386,  -355,   146,   327,
    -355,   386,  -355,   133,  -355,   386,   152,   156,   158,   162,
      61,    55,    84,   121,    74,  -355,  -355,  -355,    -8,  -355,
    -355,   133,  -355,  -355,  -355,   109,   386,   386,   153,  -355,
    -355,  -355,   148,   182,  -355,  -355,   148,   185,   133,   181,
    -355,  -355,   300,   133,  -355,  -355,  -355,  -355,   189,  -355,
     -13,   190,  -355,   191,  -355,   180,   187,   188,   354,    44,
     147,  -355,   192,   148,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,   183,  -355,   153,  -355,  -355,  -355,  -355,   153,
     195,   201,  -355,  -355,  -355,  -355,  -355,  -355,   153,   202,
    -355,   207,  -355,   153,  -355,  -355,  -355,  -355,  -355,   206,
       1,  -355,  -355,  -355,  -355,  -355,  -355,   386,  -355,   196,
    -355,    14,   219,   219,   205,   208,  -355,   210,   153,  -355,
    -355,  -355,  -355,  -355,  -355,  -355,   148,   211,  -355,   216,
     218,  -355,  -355,   215,     3,   153,  -355,   219,  -355,   220,
    -355,  -355,  -355,  -355,  -355,  -355,   153,   228,  -355,   382,
     212,  -355,   233,  -355,  -355,   232,  -355,  -355,   153,  -355,
    -355
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
     122,  -355,  -355,  -355,  -355,  -355,   209,  -355,  -355,  -355,
    -355,    -3,  -355,  -355,  -355,  -355,   -45,  -355,  -355,  -355,
    -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,  -355,  -355,    -7,  -355,   -68,  -355,  -355,  -355,
    -145,  -164,     7,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,  -355,  -355,  -355,  -332,   217,  -355,  -355,   204,
    -114,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,  -133,  -355,  -355,   157,   -81,   -71,  -355,  -355,
    -355,   100,    90,   101,    87,    99,    95,    82,    96,    81,
    -355,  -355,  -355,  -355,  -110,   132,  -355,  -355,  -355,  -355,
    -355,  -355,  -355,    63,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -354,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,   -53,
     -52,  -318,  -355,   -26,   305,  -355,  -355,  -355,   -78,  -355,
    -355,  -242,  -355
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -267
static const yytype_int16 yytable[] =
{
      11,    68,   165,   227,   215,   245,   353,   127,    93,   379,
      75,   354,    11,   289,   176,   177,   178,   110,   111,    58,
     -72,   391,     4,    99,   192,   364,  -218,   160,  -216,   389,
     291,    17,  -266,   397,   161,   292,   112,   113,   114,   115,
       5,   193,   100,   -87,   101,    43,    44,   -79,   -83,    59,
     382,   392,   393,   116,     6,     7,     8,     9,   371,    22,
     118,   119,   120,    80,    81,   225,   349,   395,   406,   158,
     229,    23,   159,     7,   309,   310,   110,   111,   401,   216,
     217,   218,   228,   207,   208,   209,   210,   204,   205,   288,
     410,    18,    19,    32,    20,   112,   113,   114,   115,  -218,
     227,  -216,   100,    19,   101,    20,   -92,   293,    42,   265,
     254,    46,   116,    80,    85,   117,   212,   213,    50,   118,
     119,   120,    80,    91,   110,   111,   114,   115,    49,    47,
     215,    55,   282,   281,   121,   286,    54,   165,    56,  -117,
     266,   282,   270,   227,    82,   225,    83,    89,   227,    92,
     146,    59,   144,   -11,   152,   155,   110,   111,   156,   157,
     -55,   280,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   179,   196,   198,   226,   112,   113,   114,   115,   200,
     202,   232,    -9,   238,   240,   -19,  -220,   246,   189,   190,
     298,   242,   116,   272,   282,   296,   297,   299,   249,   118,
     119,   300,   301,   302,   303,   243,   304,   305,   306,   307,
     308,   270,     7,   309,   310,   244,   251,   -58,   110,   111,
    -113,   273,   110,   111,   333,   334,   335,   337,   344,   340,
     342,   345,   346,   355,   370,   352,   351,   112,   113,   114,
     115,   112,   113,   114,   115,   356,   362,   360,   376,   376,
     366,   385,   381,    80,   116,   380,   386,   387,   116,   388,
     392,   118,   119,   120,   398,   118,   119,   120,   402,   376,
     110,   111,   409,   376,     7,   309,   310,   407,     7,   309,
     310,   237,   295,    90,    96,   336,   369,   257,   259,   112,
     113,   114,   115,   262,    94,   256,   264,   110,   111,   220,
     258,   261,   260,   110,   111,   367,   116,   252,   373,   374,
     263,   284,   359,   118,   119,   120,   112,   113,   114,   115,
      29,   405,   112,   113,   114,   115,   163,     0,   164,     0,
     110,   111,     0,   116,     0,     0,   224,    92,     0,   116,
     118,   119,   120,     0,     0,     0,   118,   119,   120,   112,
     113,   114,   115,     0,     0,   121,     0,   110,   111,   375,
     375,   121,     0,     0,     0,     0,   116,   285,     0,     0,
       0,     0,     0,   118,   119,   120,   112,   113,   114,   115,
     375,     0,     0,     0,   375,   110,   111,     0,   121,   110,
     111,     0,     0,   116,     0,     0,     0,     0,   347,     0,
     118,   119,   120,     0,   112,   113,   114,   115,   112,   113,
     114,   115,     0,     0,     0,   121,     0,     0,     0,     0,
       0,   116,   403,     0,     0,   116,     0,     0,   118,   119,
     120,     0,   118,   119,   120,     0,     0,     0,     0,     0,
       0,     0,     0,   121,     0,     0,     0,   121
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-355)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       3,    46,   116,   148,   137,   169,   324,    88,    76,   363,
      55,   329,    15,   255,   124,   125,   126,     3,     4,    18,
      16,    18,     0,    40,    19,   343,    39,    37,    41,   383,
      38,    61,    45,   387,    44,    43,    22,    23,    24,    25,
      44,    36,    59,    39,    61,    43,    44,    43,    44,    48,
     368,    48,   384,    39,    58,    59,    60,    61,    44,    48,
      46,    47,    48,    43,    44,   146,   308,   385,   400,    40,
     151,    48,    43,    59,    60,    61,     3,     4,   396,     5,
       6,     7,   150,    28,    29,    30,    31,    26,    27,   253,
     408,    58,    59,    61,    61,    22,    23,    24,    25,    39,
     245,    41,    59,    59,    61,    61,    44,   271,    16,   219,
     191,    43,    39,    43,    44,    42,    32,    33,    41,    46,
      47,    48,    43,    44,     3,     4,    24,    25,    39,    44,
     263,    43,   246,   243,    61,   249,    39,   251,    44,    41,
     221,   255,   223,   288,    16,   226,    16,    16,   293,    37,
      41,    48,    38,    48,    61,    48,     3,     4,    16,    16,
      41,   242,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    42,    20,    17,    41,    22,    23,    24,    25,    21,
      18,    18,    48,    38,    61,    41,    39,    41,    34,    35,
      37,    43,    39,    42,   308,   276,   277,    44,    39,    46,
      47,    48,    49,    50,    51,    40,    53,    54,    55,    56,
      57,   292,    59,    60,    61,    40,    39,    41,     3,     4,
      41,    18,     3,     4,    42,    40,    45,    38,    48,    39,
      39,    44,    44,    38,    38,    52,    44,    22,    23,    24,
      25,    22,    23,    24,    25,    44,    39,    45,   362,   363,
      44,    40,    44,    43,    39,    50,    40,    39,    39,    44,
      48,    46,    47,    48,    44,    46,    47,    48,    40,   383,
       3,     4,    40,   387,    59,    60,    61,    44,    59,    60,
      61,   159,   275,    74,    80,   292,   357,   197,   201,    22,
      23,    24,    25,   211,    77,   195,   215,     3,     4,   142,
     199,   206,   203,     3,     4,   350,    39,   175,   361,   361,
     214,   248,   338,    46,    47,    48,    22,    23,    24,    25,
      15,   399,    22,    23,    24,    25,    59,    -1,    61,    -1,
       3,     4,    -1,    39,    -1,    -1,    42,    37,    -1,    39,
      46,    47,    48,    -1,    -1,    -1,    46,    47,    48,    22,
      23,    24,    25,    -1,    -1,    61,    -1,     3,     4,   362,
     363,    61,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,
      -1,    -1,    -1,    46,    47,    48,    22,    23,    24,    25,
     383,    -1,    -1,    -1,   387,     3,     4,    -1,    61,     3,
       4,    -1,    -1,    39,    -1,    -1,    -1,    -1,    44,    -1,
      46,    47,    48,    -1,    22,    23,    24,    25,    22,    23,
      24,    25,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    39,    40,    -1,    -1,    39,    -1,    -1,    46,    47,
      48,    -1,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    61
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    63,   248,   249,     0,    44,    58,    59,    60,    61,
      90,    93,   128,   133,   246,   247,    92,    61,    58,    59,
      61,    97,    48,    48,   105,   108,   113,   120,   124,   246,
      96,    91,    61,    95,   134,   109,   114,   121,   125,   129,
     131,   132,    16,    43,    44,   112,    43,    44,    94,    39,
      41,   115,   122,   126,    39,    43,    44,   106,    18,    48,
      98,   146,   149,   152,   157,   158,   159,   161,    98,   135,
     110,   116,   123,   127,   130,    98,   107,   160,   147,   153,
      43,    44,    16,    16,   154,    44,    88,    89,   111,    16,
      88,    44,    37,   138,   158,   148,   161,   150,   155,    40,
      59,    61,    64,    71,    73,    76,    79,    82,    83,    87,
       3,     4,    22,    23,    24,    25,    39,    42,    46,    47,
      48,    61,   101,   104,   174,   176,   177,   178,   179,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     196,   197,   198,   117,    38,   140,    41,   142,   143,   144,
     151,   156,    61,    67,    70,    48,    16,    16,    40,    43,
      37,    44,    84,    59,    61,   162,   178,   193,   252,   102,
     199,   200,   201,   202,   204,   203,   196,   196,   196,    42,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    34,
      35,   164,    19,    36,   165,   166,    20,   167,    17,   168,
      21,   169,    18,   170,    26,    27,   171,    28,    29,    30,
      31,   172,    32,    33,   173,   174,     5,     6,     7,   175,
     177,   118,   139,   141,    42,   178,    41,   142,   138,   178,
      65,    69,    18,    72,    77,    74,    80,    82,    38,    85,
      61,   195,    43,    40,    40,   143,    41,   205,   206,    39,
     207,    39,   197,   103,   178,   180,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   196,   178,   136,   137,   138,
     178,   145,    42,    18,    68,    78,    75,    81,    86,   194,
     178,   196,   162,   253,   205,    40,   162,   254,   143,   253,
     119,    38,    43,   143,    66,   144,   178,   178,    37,    44,
      48,    49,    50,    51,    53,    54,    55,    56,    57,    60,
      61,    93,    99,   162,   208,   218,   223,   225,   227,   229,
     230,   232,   233,   236,   238,   239,   241,   242,   243,   244,
     245,   250,   163,    42,    40,    45,   136,    38,   210,   237,
      39,   226,    39,   224,    48,    44,    44,    44,   231,   253,
     100,    44,    52,   243,   243,    38,    44,   181,   209,   245,
      45,   219,    39,   234,   243,   228,    44,    98,   240,   179,
      38,    44,   215,   241,   242,    93,   162,   213,   251,   213,
      50,    44,   243,   220,   214,    40,    40,    39,    44,   213,
     216,    18,    48,   157,   211,   243,   235,   213,    44,   221,
     212,   243,    40,    40,   217,   250,   157,    44,   222,    40,
     243
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
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
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
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
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
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

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

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 4:

    { SAVE((yyvsp[(4) - (4)])); }
    break;

  case 5:

    { MAKE(DefType,11); }
    break;

  case 6:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 7:

    { SAVE((yyvsp[(3) - (3)])); }
    break;

  case 8:

    { MAKE(DefType,9); }
    break;

  case 9:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 10:

    { MAKE(DefType,3); }
    break;

  case 11:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 12:

    { MAKE(DefType,1); }
    break;

  case 13:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 14:

    { MAKE(DefParVar,0); }
    break;

  case 15:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 16:

    { CODE(BegParVarAssign,0); }
    break;

  case 17:

    { MAKE(ParVarAssign,0); }
    break;

  case 19:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 20:

    { MAKE(DefParArr,0); }
    break;

  case 22:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 23:

    { CODE(BegParVarAssign,0); }
    break;

  case 24:

    { MAKE(ParVarAssign,0); }
    break;

  case 28:

    { TREE(AddToList,0); }
    break;

  case 29:

    { TREE(AddToList,0); }
    break;

  case 30:

    { MAKE(BodyFunc,0); }
    break;

  case 31:

    { MAKE(BodyFunc,1); }
    break;

  case 32:

    { CODE(EndParams,0); }
    break;

  case 33:

    { MAKE(BegStmExprLR,0); }
    break;

  case 34:

    { MAKE(BodyFunc,2); }
    break;

  case 35:

    { TREE(EndParams,1); }
    break;

  case 36:

    { TREE(EndParams,0); }
    break;

  case 37:

    { TREE(Define,2); }
    break;

  case 39:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 40:

    { MAKE(DefType,36); }
    break;

  case 41:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 42:

    { MAKE(DefType,32); }
    break;

  case 43:

    { SAVE((yyvsp[(3) - (3)])); }
    break;

  case 44:

    { MAKE(DefType,7); }
    break;

  case 45:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 46:

    { MAKE(DefType,5); }
    break;

  case 47:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 48:

    { MAKE(DefType,3); }
    break;

  case 49:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 50:

    { MAKE(DefType,1); }
    break;

  case 51:

    { TREE(AddToList,0); }
    break;

  case 52:

    { TREE(AddToList,0); }
    break;

  case 53:

    { MAKE(Define,1); }
    break;

  case 54:

    { CODE(EndDefine,0); }
    break;

  case 55:

    { MAKE(DefArrD1AEmpty,0); }
    break;

  case 57:

    { MAKE(DefArrD1AEmpty,0); }
    break;

  case 58:

    { MAKE(DRange,0); }
    break;

  case 60:

    { MAKE(DRange,0); }
    break;

  case 61:

    { CODE(EndRanges,0); }
    break;

  case 62:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 63:

    { CODE(BegAInit,0); }
    break;

  case 64:

    { MAKE(EndAInit,0); }
    break;

  case 66:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 67:

    { MAKE(Define,0); }
    break;

  case 68:

    { MAKE(DefArray,0); }
    break;

  case 70:

    { CODE(EndDefine,0); }
    break;

  case 71:

    { CODE(EndDefine,0); }
    break;

  case 72:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 73:

    { MAKE(Define,0); }
    break;

  case 74:

    { MAKE(DefIdent,0); }
    break;

  case 75:

    { SAVE((yyvsp[(5) - (5)])); }
    break;

  case 76:

    { CODE(BegDefVarAssign,0); }
    break;

  case 77:

    { MAKE(DefVarAssign,0); }
    break;

  case 78:

    { TREE(AddToList,0); }
    break;

  case 79:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 80:

    { MAKE(Define,0); }
    break;

  case 81:

    { MAKE(DefIdent,0); }
    break;

  case 82:

    { TREE(AddToList,0); }
    break;

  case 83:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 84:

    { MAKE(Define,0); }
    break;

  case 85:

    { MAKE(DefIdent,0); }
    break;

  case 86:

    { TREE(AddToList,0); }
    break;

  case 87:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 88:

    { MAKE(FuncIdent,0); }
    break;

  case 90:

    { TREE(AddToList,0); }
    break;

  case 91:

    { CODE(EndDefine,0); }
    break;

  case 92:

    { TREE(AddToList,0); }
    break;

  case 93:

    { CODE(EndDefine,0); }
    break;

  case 95:

    { CODE(EndDefine,0); }
    break;

  case 96:

    { CODE(EndDefine,0); }
    break;

  case 97:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 98:

    { MAKE(FuncIdent,0); }
    break;

  case 102:

    { CODE(AInitItem,0); }
    break;

  case 103:

    { TREE(AddToList,0); }
    break;

  case 104:

    { TREE(AddToList,0); }
    break;

  case 105:

    { CODE(BegInitial,0); }
    break;

  case 106:

    { TREE(NodeListLR,0); }
    break;

  case 107:

    { CODE(BegInitial,1); }
    break;

  case 108:

    { TREE(NodeListLR,0); }
    break;

  case 109:

    { CODE(EndInitial,0); }
    break;

  case 111:

    { MAKE(DRange,0); }
    break;

  case 112:

    { MAKE(DRange,0); }
    break;

  case 113:

    { MAKE(DefArrD1AEmpty,0); }
    break;

  case 115:

    { MAKE(DefArrD1AEmpty,0); }
    break;

  case 117:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 118:

    { MAKE(DefArray,0); }
    break;

  case 119:

    { CODE(EndRanges,0); }
    break;

  case 120:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 121:

    { CODE(BegAInit,0); }
    break;

  case 122:

    { MAKE(EndAInit,0); }
    break;

  case 124:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 125:

    { MAKE(DefIdent,0); }
    break;

  case 126:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 127:

    { CODE(BegDefVarAssign,0); }
    break;

  case 128:

    { MAKE(DefVarAssign,0); }
    break;

  case 133:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 134:

    { TREE(RefDef,0); }
    break;

  case 137:

    { TREE(AddToList,0); }
    break;

  case 138:

    { CODE(AddToExpr,0); }
    break;

  case 139:

    { MAKE(ExpressionsLR,0); }
    break;

  case 140:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 141:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 142:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 143:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 144:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 145:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 146:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 147:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 148:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 149:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 150:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 151:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 152:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 153:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 154:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 155:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 156:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 157:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 158:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 159:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 160:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 161:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 162:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 163:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 164:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 165:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 166:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 167:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 168:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 169:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 170:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 171:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 172:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 173:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 174:

    { MAKE(Binary,0); }
    break;

  case 176:

    { CODE(BegQuestion,0); }
    break;

  case 177:

    { CODE(MidQuestion,0); }
    break;

  case 178:

    { MAKE(Question,0); }
    break;

  case 180:

    { MAKE(Binary,0); }
    break;

  case 182:

    { MAKE(Binary,0); }
    break;

  case 184:

    { MAKE(Binary,0); }
    break;

  case 186:

    { MAKE(Binary,0); }
    break;

  case 188:

    { MAKE(Binary,0); }
    break;

  case 190:

    { MAKE(Binary,0); }
    break;

  case 192:

    { MAKE(Binary,0); }
    break;

  case 194:

    { MAKE(Binary,0); }
    break;

  case 196:

    { MAKE(Binary,0); }
    break;

  case 198:

    { MAKE(Binary,0); }
    break;

  case 200:

    { MAKE(IncDec,0); }
    break;

  case 202:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 203:

    { MAKE(DefType,3); }
    break;

  case 204:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 205:

    { MAKE(DefType,1); }
    break;

  case 206:

    { MAKE(Unary,0); }
    break;

  case 207:

    { MAKE(Unary,0); }
    break;

  case 208:

    { MAKE(Unary,0); }
    break;

  case 209:

    { MAKE(Cast,0); }
    break;

  case 211:

    { TREE(Primary,0); }
    break;

  case 212:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 213:

    { MAKE(Number,0); }
    break;

  case 214:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 215:

    { MAKE(Number,0); }
    break;

  case 216:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 217:

    { MAKE(EndIndex,0); }
    break;

  case 218:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 220:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 221:

    { MAKE(Cast,0); }
    break;

  case 222:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 223:

    { MAKE(Ident,0); }
    break;

  case 226:

    { MAKE(IndexLR,0); }
    break;

  case 227:

    { MAKE(BegIndexLR,0); }
    break;

  case 228:

    { MAKE(Params,0); }
    break;

  case 229:

    { MAKE(Params,1); }
    break;

  case 230:

    { MAKE(Compaund,0); }
    break;

  case 231:

    { CODE(EndBlock,0); }
    break;

  case 232:

    { MAKE(Compaund,0); }
    break;

  case 234:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 235:

    { TREE(RefDef,0); }
    break;

  case 237:

    { MAKE(Define,1); }
    break;

  case 238:

    { MAKE(PushDef,0); }
    break;

  case 240:

    { TREE(NodeNull,0); }
    break;

  case 243:

    { MAKE(NodeNull,0); }
    break;

  case 245:

    { TREE(NodeNull,0); }
    break;

  case 247:

    { MAKE(BegFor,0); }
    break;

  case 248:

    { CODE(PrefFor,0); }
    break;

  case 249:

    { CODE(ConditionFor,0); }
    break;

  case 250:

    { CODE(PostFor,0); }
    break;

  case 251:

    { MAKE(For,0); }
    break;

  case 252:

    { MAKE(BegDo,0); }
    break;

  case 253:

    { MAKE(Do,0); }
    break;

  case 254:

    { MAKE(BegWhile,0); }
    break;

  case 255:

    { MAKE(While,0); }
    break;

  case 256:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 257:

    { MAKE(GoTo,0); }
    break;

  case 258:

    { MAKE(Break,0); }
    break;

  case 259:

    { MAKE(Continue,0); }
    break;

  case 260:

    { MAKE(Return,0); }
    break;

  case 261:

    { MAKE(Return,1); }
    break;

  case 263:

    { CODE(BegIf,0); }
    break;

  case 264:

    { CODE(Then,0); }
    break;

  case 266:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 267:

    { CODE(Label,0); }
    break;

  case 269:

    { CODE(Else,0); }
    break;

  case 270:

    { MAKE(If,1); }
    break;

  case 271:

    { MAKE(If,0); }
    break;

  case 272:

    { TREE(Label,0); }
    break;

  case 283:

    { TREE(NodeNull,0); }
    break;

  case 287:

    { TREE(AddToList,0); }
    break;

  case 288:

    { TREE(AddToList,0); }
    break;

  case 289:

    { CODE(EndBlock,0); }
    break;

  case 290:

    { TREE(NodeNull,0); }
    break;

  case 292:

    { TREE(AddToList,0); }
    break;

  case 293:

    { TREE(BegStmExprLR,1); }
    break;

  case 294:

    { CODE(BegStmExprLR,0); }
    break;

  case 295:

    { CODE(EndBlock,0); }
    break;

  case 296:

    { MAKE(ExpressionSLR,16); }
    break;

  case 297:

    { MAKE(ExpressionSLR,241); }
    break;

  case 298:

    { MAKE(ExpressionSLR,0); }
    break;

  case 299:

    { MAKE(ExpressionSLR,256); }
    break;

  case 300:

    { MAKE(ExpressionSLR,512); }
    break;



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




