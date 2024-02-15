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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   540

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  106
/* YYNRULES -- Number of rules.  */
#define YYNRULES  213
/* YYNRULES -- Number of states.  */
#define YYNSTATES  324

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
       0,     0,     3,     5,     9,    12,    15,    17,    20,    24,
      26,    30,    34,    36,    38,    40,    44,    46,    48,    51,
      55,    57,    60,    63,    66,    68,    72,    75,    78,    80,
      84,    86,    89,    92,    94,    98,   101,   103,   107,   109,
     113,   117,   119,   123,   125,   127,   132,   138,   142,   146,
     152,   156,   161,   163,   165,   167,   171,   173,   176,   180,
     184,   187,   189,   193,   196,   198,   201,   205,   207,   209,
     212,   215,   217,   219,   221,   224,   226,   228,   232,   234,
     236,   238,   240,   242,   244,   246,   248,   250,   252,   254,
     256,   258,   260,   262,   264,   266,   268,   270,   272,   274,
     276,   278,   280,   282,   284,   286,   288,   290,   292,   294,
     296,   298,   300,   302,   306,   308,   314,   316,   320,   322,
     326,   328,   332,   334,   338,   340,   344,   346,   350,   352,
     356,   358,   362,   364,   368,   370,   374,   376,   379,   381,
     384,   386,   389,   392,   395,   400,   402,   406,   408,   410,
     413,   416,   419,   421,   423,   427,   430,   432,   435,   439,
     442,   446,   449,   451,   454,   456,   458,   460,   462,   464,
     467,   469,   472,   479,   487,   493,   497,   500,   503,   505,
     508,   511,   517,   520,   522,   526,   528,   531,   533,   535,
     537,   539,   541,   543,   545,   547,   550,   553,   555,   557,
     559,   561,   564,   566,   568,   570,   572,   575,   577,   579,
     581,   583,   585,   587
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      63,     0,    -1,   162,    -1,    59,    61,    18,    -1,    61,
      18,    -1,    59,    61,    -1,    61,    -1,    64,    48,    -1,
      65,    16,   117,    -1,    65,    -1,    64,    48,    93,    -1,
      67,    16,   117,    -1,    67,    -1,    68,    -1,    66,    -1,
      70,    43,    69,    -1,    69,    -1,    44,    -1,    37,    38,
      -1,    37,   159,    38,    -1,    40,    -1,    70,    40,    -1,
      72,    71,    -1,    60,    58,    -1,    58,    -1,    60,    59,
      61,    -1,    60,    61,    -1,    59,    61,    -1,    61,    -1,
      76,    43,   101,    -1,   101,    -1,    75,    76,    -1,    42,
      92,    -1,    42,    -1,   117,    42,    92,    -1,   117,    42,
      -1,    78,    -1,    81,    16,    90,    -1,    81,    -1,    48,
      41,    79,    -1,    43,    76,    44,    -1,    44,    -1,    48,
      16,   117,    -1,    48,    -1,    48,    -1,    75,    48,    39,
      73,    -1,    75,    80,    43,    76,    44,    -1,    75,    80,
      44,    -1,    75,    83,    82,    -1,    75,    84,    43,    76,
      44,    -1,    75,    85,    44,    -1,    74,    48,    39,    73,
      -1,    86,    -1,    90,    -1,   117,    -1,    89,    43,    88,
      -1,    88,    -1,    37,    38,    -1,    37,    89,    38,    -1,
      41,   117,    42,    -1,    92,    91,    -1,    91,    -1,    41,
      42,    92,    -1,    41,    42,    -1,    92,    -1,    48,    93,
      -1,    94,    16,    90,    -1,    94,    -1,    48,    -1,    16,
     117,    -1,    96,    97,    -1,    96,    -1,    95,    -1,    98,
      -1,    18,    99,    -1,   100,    -1,    99,    -1,   102,    43,
     117,    -1,   117,    -1,     8,    -1,     9,    -1,    10,    -1,
      11,    -1,    12,    -1,    16,    -1,    14,    -1,    15,    -1,
      13,    -1,    34,    -1,    35,    -1,    36,    -1,    19,    -1,
      20,    -1,    17,    -1,    21,    -1,    18,    -1,    26,    -1,
      27,    -1,    29,    -1,    28,    -1,    31,    -1,    30,    -1,
      32,    -1,    33,    -1,     3,    -1,     4,    -1,     5,    -1,
       6,    -1,     7,    -1,    23,    -1,    22,    -1,    24,    -1,
      25,    -1,   118,   103,   117,    -1,   118,    -1,   119,   104,
     166,    45,   118,    -1,   119,    -1,   119,   105,   120,    -1,
     120,    -1,   120,   106,   121,    -1,   121,    -1,   121,   107,
     122,    -1,   122,    -1,   122,   108,   123,    -1,   123,    -1,
     123,   109,   124,    -1,   124,    -1,   124,   110,   125,    -1,
     125,    -1,   125,   111,   126,    -1,   126,    -1,   126,   112,
     127,    -1,   127,    -1,   127,   113,   128,    -1,   128,    -1,
     128,   114,   131,    -1,   131,    -1,   133,   116,    -1,   133,
      -1,    59,    61,    -1,    61,    -1,   115,   131,    -1,   113,
     131,    -1,   116,   131,    -1,    39,   130,    40,   131,    -1,
     129,    -1,    39,   165,    40,    -1,    46,    -1,    47,    -1,
      48,   135,    -1,    48,   136,    -1,    61,   132,    -1,    48,
      -1,   132,    -1,    41,   166,    42,    -1,   135,   134,    -1,
     134,    -1,    39,    40,    -1,    39,   167,    40,    -1,    37,
      38,    -1,    37,   159,    38,    -1,    18,    98,    -1,    98,
      -1,    75,   138,    -1,   164,    -1,    44,    -1,   155,    -1,
     156,    -1,    44,    -1,   139,    44,    -1,    40,    -1,   163,
      40,    -1,    49,    39,   140,   141,   142,   157,    -1,    53,
     157,    50,    39,   139,    40,    44,    -1,    50,    39,   139,
      40,   157,    -1,    54,    48,    44,    -1,    56,    44,    -1,
      55,    44,    -1,    44,    -1,   166,    44,    -1,    57,   149,
      -1,    51,    39,   139,    40,   157,    -1,    48,    45,    -1,
     152,    -1,   151,    52,   157,    -1,   151,    -1,   153,   157,
      -1,   144,    -1,   145,    -1,   143,    -1,   146,    -1,   147,
      -1,   148,    -1,   150,    -1,   137,    -1,    77,    44,    -1,
     163,    44,    -1,    44,    -1,   155,    -1,   154,    -1,   156,
      -1,   158,   157,    -1,   157,    -1,   158,    -1,    44,    -1,
      87,    -1,   161,   160,    -1,   160,    -1,   161,    -1,   102,
      -1,   102,    -1,   102,    -1,   102,    -1,   102,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,    99,   100,   101,   102,   105,   108,   109,
     112,   115,   116,   119,   120,   123,   124,   127,   128,   129,
     132,   133,   136,   139,   140,   143,   144,   145,   146,   149,
     150,   153,   156,   157,   158,   159,   162,   165,   166,   169,
     172,   173,   176,   179,   182,   185,   186,   187,   188,   189,
     190,   193,   194,   197,   198,   201,   202,   205,   206,   209,
     212,   213,   216,   217,   218,   221,   224,   225,   228,   231,
     234,   235,   238,   239,   242,   245,   246,   249,   250,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     266,   269,   272,   275,   278,   281,   284,   285,   288,   289,
     290,   291,   294,   295,   298,   299,   302,   303,   304,   307,
     308,   311,   312,   315,   316,   319,   320,   323,   324,   327,
     328,   331,   332,   335,   336,   339,   340,   343,   344,   347,
     348,   351,   352,   355,   356,   359,   360,   363,   364,   367,
     368,   371,   372,   373,   374,   375,   378,   381,   382,   383,
     384,   385,   386,   387,   390,   393,   394,   397,   398,   401,
     402,   405,   406,   409,   410,   413,   414,   415,   418,   419,
     422,   423,   426,   429,   432,   435,   438,   441,   444,   445,
     448,   451,   454,   457,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   473,   476,   479,   480,   481,
     482,   485,   486,   489,   492,   493,   496,   497,   500,   503,
     506,   509,   512,   515
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
  "$accept", "Program", "DefParType", "DefBegParVar", "DefParVar",
  "DefBegParArr", "DefParArr", "DefParItem", "DefParams", "BodyFunc",
  "DefFuncParBody", "DefParBodyFunc", "DefVoidType", "DefType",
  "CommaDefItem", "Define", "DefineBegRanges", "DefineBegArr", "DefineArr",
  "IdentLeftScrape", "DefineVarAssign", "DefVariableAssign", "DefVarComma",
  "DefVarSemicolon", "DefFuncArrVar", "DefFuncDefine", "AInitItem",
  "AInitial", "Initializer", "DefRange", "DefRanges", "DefBegRanges",
  "DefBegArr", "DefArr", "DefVarIdent", "DefVarAssign", "DefVar", "DefIAV",
  "RefDefIAV", "DefItem", "Expressions", "PriorAssign", "PriorQuestion",
  "PriorOrOr", "PriorAndAnd", "PriorOr", "PriorXOr", "PriorAnd",
  "PriorEqu", "PriorCompare", "PriorShift", "PriorTerm", "PriorFactor",
  "PriorUnary", "PriorIncDec", "Assign", "Question", "OrOr", "AndAnd",
  "Or", "XOr", "And", "Equ", "Compare", "Shift", "Term", "Factor",
  "UnaryIncDec", "DefTypeCast", "Unary", "Primary", "PrimaryExpr", "Range",
  "Ranges", "CallParams", "CompaundStmnt", "ConditionVar", "Condition",
  "ForPrefix", "ForCondition", "ForPostfix", "ForStmnt", "DoStmnt",
  "WhileStmnt", "GoToStmnt", "BreakStmnt", "ContinueStmnt", "ReturnValue",
  "ReturnStmnt", "BegIfStmnt", "LabelIdent", "LabelList", "Statement",
  "DefineSemi", "ExprSemi", "DefExpr", "StmExprList", "StmExpr", "DefFAV",
  "DefinesList", "Defines", "ExpressionExpression", "ExpressionCondition",
  "ExpressionNone", "ExpressionValue", "ExpressionValueList", YY_NULL
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
       0,    62,    63,    64,    64,    64,    64,    65,    66,    66,
      67,    68,    68,    69,    69,    70,    70,    71,    71,    71,
      72,    72,    73,    74,    74,    75,    75,    75,    75,    76,
      76,    77,    78,    78,    78,    78,    79,    80,    80,    81,
      82,    82,    83,    84,    85,    86,    86,    86,    86,    86,
      86,    87,    87,    88,    88,    89,    89,    90,    90,    91,
      92,    92,    93,    93,    93,    94,    95,    95,    96,    97,
      98,    98,    99,    99,   100,   101,   101,   102,   102,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     104,   105,   106,   107,   108,   109,   110,   110,   111,   111,
     111,   111,   112,   112,   113,   113,   114,   114,   114,   115,
     115,   116,   116,   117,   117,   118,   118,   119,   119,   120,
     120,   121,   121,   122,   122,   123,   123,   124,   124,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   130,
     130,   131,   131,   131,   131,   131,   132,   133,   133,   133,
     133,   133,   133,   133,   134,   135,   135,   136,   136,   137,
     137,   138,   138,   139,   139,   140,   140,   140,   141,   141,
     142,   142,   143,   144,   145,   146,   147,   148,   149,   149,
     150,   151,   152,   153,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   155,   156,   157,   157,   157,
     157,   158,   158,   159,   160,   160,   161,   161,   162,   163,
     164,   165,   166,   167
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     2,     2,     1,     2,     3,     1,
       3,     3,     1,     1,     1,     3,     1,     1,     2,     3,
       1,     2,     2,     2,     1,     3,     2,     2,     1,     3,
       1,     2,     2,     1,     3,     2,     1,     3,     1,     3,
       3,     1,     3,     1,     1,     4,     5,     3,     3,     5,
       3,     4,     1,     1,     1,     3,     1,     2,     3,     3,
       2,     1,     3,     2,     1,     2,     3,     1,     1,     2,
       2,     1,     1,     1,     2,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     5,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     2,     1,     2,
       1,     2,     2,     2,     4,     1,     3,     1,     1,     2,
       2,     2,     1,     1,     3,     2,     1,     2,     3,     2,
       3,     2,     1,     2,     1,     1,     1,     1,     1,     2,
       1,     2,     6,     7,     5,     3,     2,     2,     1,     2,
       2,     5,     2,     1,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   204,    24,     0,     0,    28,     0,     0,     0,    52,
     205,   207,   208,     2,    27,    23,     0,    26,     1,     0,
      43,     0,    38,     0,     0,     0,   206,    25,     0,     0,
       0,     0,     0,    47,     0,     0,    41,    48,     0,    50,
      20,     0,     6,     0,     9,    14,    12,    13,    16,     0,
       0,    51,   104,   105,   110,   109,   111,   112,     0,   147,
     148,   152,     0,     0,     0,     0,    42,   114,   116,   118,
     120,   122,   124,   126,   128,   130,   132,   134,   145,   136,
     153,   138,    45,    33,    36,    39,     0,     0,    68,     0,
      67,    72,    71,    73,    76,    75,    30,     0,    37,     0,
       0,     5,     4,     7,     0,     0,    21,     0,     0,    17,
      22,     0,   140,   211,    78,     0,     0,     0,     0,   156,
     149,   150,     0,   151,   142,   141,   143,    79,    80,    81,
      82,    83,    87,    85,    86,    84,    88,    89,     0,    91,
      90,     0,     0,    92,     0,    93,     0,    94,     0,    95,
       0,    96,    97,     0,    99,    98,   101,   100,     0,   102,
     103,     0,     0,   106,   107,   108,     0,   137,     0,    61,
      32,    35,    74,     0,    64,    65,     0,    46,     0,     0,
      70,    57,    56,     0,    53,    54,    40,    49,     3,    10,
       8,    11,    15,     0,    18,   197,   152,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,     0,   209,
     194,   189,   187,   188,   190,   191,   192,   193,   185,   183,
       0,   199,   198,   200,   202,   203,     0,     0,   139,     0,
       0,   146,   157,   213,     0,   212,     0,   155,   113,     0,
     117,   119,   121,   123,   125,   127,   129,   131,   133,   135,
       0,    60,    34,    63,    29,    66,    69,    58,     0,   159,
       0,   182,     0,     0,     0,     0,     0,   177,   176,   178,
     180,     0,    31,   195,     0,   186,   201,    19,   196,    77,
     144,   158,   154,     0,    59,    62,    55,   160,   165,     0,
     166,   167,     0,   210,     0,   164,     0,     0,   175,   179,
     184,   115,   168,     0,     0,     0,    68,   162,   163,     0,
       0,     0,   169,   170,     0,     0,   161,   174,   181,     0,
     172,   171,     0,   173
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,    43,    44,    45,    46,    47,    48,    49,   110,
      50,    51,     7,   207,    89,   208,    84,    85,    21,    22,
      37,    23,    24,    25,     9,    10,   182,   183,   184,   169,
     174,   175,    90,    91,    92,   180,    93,    94,    95,    96,
     209,   138,   141,   142,   144,   146,   148,   150,   153,   158,
     161,    63,   166,    64,    65,   114,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,   115,    79,
      80,    81,   119,   120,   121,   210,   308,   294,   289,   304,
     314,   211,   212,   213,   214,   215,   216,   270,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,    11,    12,
      13,   227,   295,   116,   236,   234
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -271
static const yytype_int16 yypact[] =
{
      41,  -271,  -271,   -34,    28,  -271,    29,   -10,    49,  -271,
    -271,  -271,    41,  -271,  -271,  -271,    15,  -271,  -271,    74,
       2,    10,   108,    19,    87,    88,  -271,  -271,    -9,   479,
      -9,    33,     1,  -271,   119,     1,  -271,  -271,     1,  -271,
    -271,    90,   145,   121,   157,  -271,   158,  -271,  -271,    53,
     -12,  -271,  -271,  -271,  -271,  -271,  -271,  -271,   359,  -271,
    -271,    32,   139,   479,   479,   479,  -271,   174,     4,   159,
     164,   170,   176,    18,    78,    94,   125,   114,  -271,  -271,
    -271,   113,  -271,   154,  -271,  -271,   155,   148,   160,    96,
     182,  -271,   183,  -271,  -271,  -271,  -271,   313,  -271,    99,
     101,   185,  -271,   160,   479,   479,  -271,    51,   111,  -271,
    -271,   143,   139,   162,  -271,   175,   177,   369,   479,  -271,
     169,  -271,   479,  -271,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,   479,  -271,
    -271,   479,   479,  -271,   479,  -271,   479,  -271,   479,  -271,
     479,  -271,  -271,   479,  -271,  -271,  -271,  -271,   479,  -271,
    -271,   479,   479,  -271,  -271,  -271,   479,  -271,   479,  -271,
     154,   154,  -271,   399,   154,  -271,     1,  -271,   119,   479,
    -271,  -271,  -271,    -4,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,   189,  -271,  -271,   -15,   161,   179,   180,
     248,   168,   178,   181,   409,    64,   139,     1,   186,   162,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,   171,  -271,
     248,  -271,  -271,  -271,  -271,   248,   191,   190,  -271,   479,
     479,  -271,  -271,   162,   184,   162,   199,  -271,  -271,   202,
     159,   164,   170,   176,    18,    78,    94,   125,   114,  -271,
     211,  -271,   154,   154,  -271,  -271,  -271,  -271,   439,  -271,
     217,  -271,    44,   319,   319,   206,   213,  -271,  -271,  -271,
    -271,   214,   216,  -271,   248,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,   479,  -271,   154,  -271,  -271,  -271,   309,
    -271,  -271,     3,   162,   220,  -271,   221,   223,  -271,  -271,
    -271,  -271,  -271,   222,   468,   172,  -271,  -271,  -271,   248,
     248,   319,  -271,  -271,   248,   225,  -271,  -271,  -271,   227,
    -271,  -271,   224,  -271
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -271,  -271,  -271,  -271,  -271,  -271,  -271,   167,  -271,  -271,
    -271,   239,  -271,     0,   -32,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,   -37,  -271,   -24,  -154,
     -76,   173,  -271,  -271,  -271,  -271,  -270,   188,  -271,   102,
     -57,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,   -71,  -271,  -271,   196,   -27,    -3,  -271,   137,   138,
     135,   136,   133,   140,   128,   127,   129,  -271,  -271,   -50,
     -53,  -271,   194,  -271,  -271,  -271,  -271,  -247,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,    38,    48,  -192,  -271,    97,   294,  -271,
    -271,    11,  -271,  -271,  -130,  -271
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -45
static const yytype_int16 yytable[] =
{
       8,   113,    66,    99,    86,   162,   100,   170,   265,   123,
      98,   239,     8,   124,   125,   126,   251,   296,    29,    87,
     251,   305,   307,   139,   117,   108,   118,    14,   275,    18,
     261,    40,   109,   276,   257,   316,    52,    53,    19,   258,
     140,    30,   303,    31,   151,   152,   -44,    52,    53,    88,
      41,   306,    42,    32,    33,    54,    55,    56,    57,   123,
     233,   235,    35,    36,   319,   113,    54,    55,    56,    57,
     185,   117,    58,   118,   271,    83,    27,   190,   191,    59,
      60,    61,   300,    58,   235,     1,    15,    16,   288,    17,
      59,    60,    61,   106,    62,   252,   107,    20,   251,     2,
       3,     4,     5,     3,   205,   206,   154,   155,   156,   157,
      41,   238,    42,    28,    52,    53,   249,   317,   318,   163,
     164,   165,   320,    16,    34,    17,   159,   160,    52,    53,
      38,   251,    39,    54,    55,    56,    57,    56,    57,   176,
     177,   250,   176,   186,   176,   187,   250,   235,   193,   194,
      58,   101,   256,   123,   255,   195,    97,    59,    60,   196,
     197,   198,   199,   102,   200,   201,   202,   203,   204,   103,
       3,   205,   206,   104,   105,   272,   162,   285,   122,   143,
     280,   145,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   147,    52,    53,   149,   168,    88,   171,   178,   179,
     262,   173,   279,   188,   228,   229,   293,   293,   136,   137,
     118,    54,    55,    56,    57,   230,   266,   231,   263,   264,
     306,   286,   267,   274,   281,   268,   193,   259,    58,   277,
     273,   185,   293,   195,   278,    59,    60,   196,   197,   198,
     199,   282,   200,   201,   202,   203,   204,   283,     3,   205,
     206,    52,    53,   284,   293,   287,   297,   298,   299,   176,
     309,   310,   311,   292,   292,   321,   312,   322,   323,    82,
      54,    55,    56,    57,   192,   172,   189,   167,   254,   240,
     301,   242,   241,   244,   243,   193,   246,    58,   247,   292,
     260,   248,   195,   245,    59,    60,   196,   197,   198,   199,
     290,   200,   201,   202,   203,   204,    26,     3,   205,   206,
     291,   292,    52,    53,   237,   315,    52,    53,     0,     0,
       0,     0,    52,    53,     0,     0,     0,     0,     0,     0,
       0,    54,    55,    56,    57,    54,    55,    56,    57,     0,
       0,    54,    55,    56,    57,     0,     0,     0,    58,     0,
      97,   181,    58,   302,     0,    59,    60,    61,    58,    59,
      60,    61,    52,    53,     0,    59,    60,    61,     3,   205,
     206,     0,    52,    53,    62,     0,     0,     0,     3,   205,
     206,    54,    55,    56,    57,     0,     0,     0,     0,     0,
       0,    54,    55,    56,    57,     0,     0,     0,    58,     0,
       0,     0,    52,    53,     0,    59,    60,    61,    58,   232,
       0,     0,    52,    53,     0,    59,    60,    61,   111,     0,
     112,    54,    55,    56,    57,     0,     0,     0,     0,     0,
      62,    54,    55,    56,    57,     0,     0,     0,    58,     0,
       0,   253,    52,    53,     0,    59,    60,    61,    58,     0,
       0,     0,     0,   269,     0,    59,    60,    61,     0,     0,
      62,    54,    55,    56,    57,     0,     0,     0,     0,     0,
      62,    52,    53,     0,     0,     0,    97,     0,    58,     0,
       0,     0,    52,    53,     0,    59,    60,    61,     0,     0,
      54,    55,    56,    57,     0,     0,     0,     0,     0,     0,
      62,    54,    55,    56,    57,     0,     0,    58,   313,     0,
       0,     0,     0,     0,    59,    60,    61,     0,    58,     0,
       0,     0,     0,     0,     0,    59,    60,    61,     0,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      62
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-271)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    58,    29,    35,    31,    76,    38,    83,   200,    62,
      34,   141,    12,    63,    64,    65,   170,   264,    16,    18,
     174,    18,   292,    19,    39,    37,    41,    61,   220,     0,
      45,    40,    44,   225,    38,   305,     3,     4,    48,    43,
      36,    39,   289,    41,    26,    27,    44,     3,     4,    48,
      59,    48,    61,    43,    44,    22,    23,    24,    25,   112,
     117,   118,    43,    44,   311,   122,    22,    23,    24,    25,
      97,    39,    39,    41,   204,    42,    61,   104,   105,    46,
      47,    48,   274,    39,   141,    44,    58,    59,    44,    61,
      46,    47,    48,    40,    61,   171,    43,    48,   252,    58,
      59,    60,    61,    59,    60,    61,    28,    29,    30,    31,
      59,   138,    61,    39,     3,     4,   166,   309,   310,     5,
       6,     7,   314,    59,    16,    61,    32,    33,     3,     4,
      43,   285,    44,    22,    23,    24,    25,    24,    25,    43,
      44,   168,    43,    44,    43,    44,   173,   204,    37,    38,
      39,    61,   179,   206,   178,    44,    37,    46,    47,    48,
      49,    50,    51,    18,    53,    54,    55,    56,    57,    48,
      59,    60,    61,    16,    16,   207,   247,   253,    39,    20,
     230,    17,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    21,     3,     4,    18,    41,    48,    42,    16,    16,
      39,    41,   229,    18,    61,    43,   263,   264,    34,    35,
      41,    22,    23,    24,    25,    40,    48,    40,    39,    39,
      48,   258,    44,    52,    40,    44,    37,    38,    39,    38,
      44,   258,   289,    44,    44,    46,    47,    48,    49,    50,
      51,    42,    53,    54,    55,    56,    57,    45,    59,    60,
      61,     3,     4,    42,   311,    38,    50,    44,    44,    43,
      40,    40,    39,   263,   264,    40,    44,    40,    44,    30,
      22,    23,    24,    25,   107,    87,   103,    81,   176,   142,
     283,   146,   144,   150,   148,    37,   158,    39,   161,   289,
     193,   162,    44,   153,    46,    47,    48,    49,    50,    51,
     262,    53,    54,    55,    56,    57,    12,    59,    60,    61,
     262,   311,     3,     4,   120,   304,     3,     4,    -1,    -1,
      -1,    -1,     3,     4,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    22,    23,    24,    25,    -1,
      -1,    22,    23,    24,    25,    -1,    -1,    -1,    39,    -1,
      37,    38,    39,    44,    -1,    46,    47,    48,    39,    46,
      47,    48,     3,     4,    -1,    46,    47,    48,    59,    60,
      61,    -1,     3,     4,    61,    -1,    -1,    -1,    59,    60,
      61,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    -1,    -1,    -1,    39,    -1,
      -1,    -1,     3,     4,    -1,    46,    47,    48,    39,    40,
      -1,    -1,     3,     4,    -1,    46,    47,    48,    59,    -1,
      61,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      61,    22,    23,    24,    25,    -1,    -1,    -1,    39,    -1,
      -1,    42,     3,     4,    -1,    46,    47,    48,    39,    -1,
      -1,    -1,    -1,    44,    -1,    46,    47,    48,    -1,    -1,
      61,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      61,     3,     4,    -1,    -1,    -1,    37,    -1,    39,    -1,
      -1,    -1,     3,     4,    -1,    46,    47,    48,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    22,    23,    24,    25,    -1,    -1,    39,    40,    -1,
      -1,    -1,    -1,    -1,    46,    47,    48,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    47,    48,    -1,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,    58,    59,    60,    61,    63,    74,    75,    86,
      87,   160,   161,   162,    61,    58,    59,    61,     0,    48,
      48,    80,    81,    83,    84,    85,   160,    61,    39,    16,
      39,    41,    43,    44,    16,    43,    44,    82,    43,    44,
      40,    59,    61,    64,    65,    66,    67,    68,    69,    70,
      72,    73,     3,     4,    22,    23,    24,    25,    39,    46,
      47,    48,    61,   113,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   131,
     132,   133,    73,    42,    78,    79,   117,    18,    48,    76,
      94,    95,    96,    98,    99,   100,   101,    37,    90,    76,
      76,    61,    18,    48,    16,    16,    40,    43,    37,    44,
      71,    59,    61,   102,   117,   130,   165,    39,    41,   134,
     135,   136,    39,   132,   131,   131,   131,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    34,    35,   103,    19,
      36,   104,   105,    20,   106,    17,   107,    21,   108,    18,
     109,    26,    27,   110,    28,    29,    30,    31,   111,    32,
      33,   112,   113,     5,     6,     7,   114,   116,    41,    91,
      92,    42,    99,    41,    92,    93,    43,    44,    16,    16,
      97,    38,    88,    89,    90,   117,    44,    44,    18,    93,
     117,   117,    69,    37,    38,    44,    48,    49,    50,    51,
      53,    54,    55,    56,    57,    60,    61,    75,    77,   102,
     137,   143,   144,   145,   146,   147,   148,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   163,    61,    43,
      40,    40,    40,   102,   167,   102,   166,   134,   117,   166,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   131,
     117,    91,    92,    42,   101,    90,   117,    38,    43,    38,
     159,    45,    39,    39,    39,   157,    48,    44,    44,    44,
     149,   166,    76,    44,    52,   157,   157,    38,    44,   117,
     131,    40,    42,    45,    42,    92,    88,    38,    44,   140,
     155,   156,    75,   102,   139,   164,   139,    50,    44,    44,
     157,   118,    44,   139,   141,    18,    48,    98,   138,    40,
      40,    39,    44,    40,   142,   163,    98,   157,   157,   139,
     157,    40,    40,    44
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
        case 2:

    { NODE(None,(1),1,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 3:

    { YACC(DefType,11,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 4:

    { YACC(DefType,9,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 5:

    { YACC(DefType,3,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 6:

    { YACC(DefType,1,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 7:

    { NODE(DefVar,(66),1,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 8:

    { NODE(DefVar,(12354),2,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 10:

    { NODE(DefArr,(786498),1,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 11:

    { NODE(DefArr,(12354),2,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 15:

    { YACC(AddToList,5,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 16:

    { NODE(Define,(4096),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 17:

    { NODE(NodeOne,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 18:

    { NODE(NodeOne,(1),1,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 19:

    { NODE(NodeOne,(129),2,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 20:

    { NODE(Define,(0),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 22:

    { NODE(NodeTwo,(8256),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 23:

    { YACC(DefType,36,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 24:

    { YACC(DefType,32,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 25:

    { YACC(DefType,7,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 26:

    { YACC(DefType,5,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 27:

    { YACC(DefType,3,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 28:

    { YACC(DefType,1,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 29:

    { YACC(AddToList,5,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 30:

    { NODE(Define,(4096),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 31:

    { NODE(Define,(524352),1,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 32:

    { NODE(Ranges,(129),1,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 33:

    { NODE(Ranges,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 34:

    { NODE(Ranges,(4288),4,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 35:

    { NODE(Ranges,(64),2,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 37:

    { NODE(DefArr,(12352),2,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 39:

    { NODE(DefArr,(786433),1,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 40:

    { NODE(None,(2),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 42:

    { NODE(DefVar,(12289),1,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 43:

    { NODE(DefVar,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 44:

    { NODE(DefVar,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 45:

    { NODE(DefFunc,(16450),0,(yyval),(yyvsp[(1) - (4)])); }
    break;

  case 46:

    { NODE(Define,(1056832),1,(yyval),(yyvsp[(1) - (5)])); }
    break;

  case 47:

    { NODE(Define,(8256),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 48:

    { NODE(Define,(794688),1,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 49:

    { NODE(Define,(1056832),1,(yyval),(yyvsp[(1) - (5)])); }
    break;

  case 50:

    { NODE(Define,(8256),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 51:

    { NODE(DefFunc,(16450),0,(yyval),(yyvsp[(1) - (4)])); }
    break;

  case 55:

    { NODE(List,(4288),1,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 56:

    { NODE(List,(65),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 57:

    { NODE(List,(1),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 58:

    { NODE(None,(2),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 59:

    { NODE(None,(2),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 60:

    { NODE(Ranges,(8256),3,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 61:

    { NODE(Ranges,(64),2,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 62:

    { NODE(Ranges,(193),1,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 63:

    { NODE(Ranges,(1),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 65:

    { NODE(DefArr,(524289),1,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 66:

    { NODE(DefArr,(12352),2,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 68:

    { NODE(DefVar,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 69:

    { NODE(None,(2),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 70:

    { NODE(DefVar,(8256),2,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 74:

    { NODE(RefDef,(129),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 77:

    { YACC(AddToList,5,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 78:

    { NODE(Expressions,(65),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 113:

    { NODE(Binary,(12354),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 115:

    { NODE(Trio,(1323074),0,(yyval),(yyvsp[(1) - (5)])); }
    break;

  case 117:

    { NODE(Binary,(12354),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 119:

    { NODE(Binary,(12354),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 121:

    { NODE(Binary,(12354),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 123:

    { NODE(Binary,(12354),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 125:

    { NODE(Binary,(12354),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 127:

    { NODE(Binary,(12354),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 129:

    { NODE(Binary,(12354),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 131:

    { NODE(Binary,(12354),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 133:

    { NODE(Binary,(12354),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 135:

    { NODE(Binary,(12354),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 137:

    { NODE(Unary,(66),1,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 139:

    { YACC(DefType,3,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 140:

    { YACC(DefType,1,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 141:

    { NODE(Unary,(129),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 142:

    { NODE(Unary,(129),1,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 143:

    { NODE(Unary,(129),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 144:

    { NODE(Cast,(258),0,(yyval),(yyvsp[(1) - (4)])); }
    break;

  case 146:

    { NODE(Primary,(129),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 147:

    { NODE(Number,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 148:

    { NODE(Number,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 149:

    { NODE(Index,(129),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 150:

    { NODE(Call,(129),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 151:

    { NODE(Cast,(129),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 152:

    { NODE(Var,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 154:

    { NODE(None,(2),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 155:

    { YACC(AddToList,3,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 156:

    { NODE(List,(64),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 157:

    { NODE(List,(1),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 158:

    { NODE(None,(2),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 159:

    { NODE(Statements,(1),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 160:

    { NODE(None,(2),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 161:

    { NODE(RefDef,(129),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 163:

    { NODE(Define,(8256),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 165:

    { NODE(Null,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 168:

    { NODE(Null,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 170:

    { NODE(Null,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 172:

    { NODE(For,(101990593),0,(yyval),(yyvsp[(1) - (6)])); }
    break;

  case 173:

    { NODE(Do,(8513),0,(yyval),(yyvsp[(1) - (7)])); }
    break;

  case 174:

    { NODE(While,(20673),0,(yyval),(yyvsp[(1) - (5)])); }
    break;

  case 175:

    { NODE(GoTo,(2),0,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 176:

    { NODE(Break,(1),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 177:

    { NODE(Continue,(1),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 178:

    { NODE(Return,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 179:

    { NODE(Return,(65),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 180:

    { NODE(None,(2),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 181:

    { NODE(If,(20673),0,(yyval),(yyvsp[(1) - (5)])); }
    break;

  case 182:

    { NODE(Label,(1),0,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 183:

    { NODE(List,(64),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 184:

    { NODE(If,(12354),1,(yyval),(yyvsp[(1) - (3)])); }
    break;

  case 186:

    { YACC(AddToList,3,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 197:

    { NODE(Null,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 201:

    { YACC(AddToList,3,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 202:

    { NODE(Statements,(64),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 204:

    { NODE(Null,(1),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 206:

    { YACC(AddToList,3,(yyval),(yyvsp[(1) - (2)])); }
    break;

  case 207:

    { NODE(Statements,(64),0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 209:

    { YACC(ExpressionSLR,16,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 210:

    { YACC(ExpressionSLR,241,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 211:

    { YACC(ExpressionSLR,0,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 212:

    { YACC(ExpressionSLR,256,(yyval),(yyvsp[(1) - (1)])); }
    break;

  case 213:

    { YACC(ExpressionSLR,512,(yyval),(yyvsp[(1) - (1)])); }
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




