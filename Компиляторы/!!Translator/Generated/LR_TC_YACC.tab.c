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
     Oper_AddAssign = 262,
     Oper_SubAssign = 263,
     Oper_MultiAssign = 264,
     Oper_DivAssign = 265,
     Oper_ModAssign = 266,
     Oper_AndAssign = 267,
     Oper_OrAssign = 268,
     Oper_XOrAssign = 269,
     Oper_Assign = 270,
     Oper_LShiftAssign = 288,
     Oper_RShiftAssign = 289,
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
     Reserv_Switch = 1802,
     Priority_Question = 2818,
     Priority_OrOr = 2819,
     Priority_AndAnd = 2820,
     Priority_Or = 2821,
     Priority_XOr = 2822,
     Priority_And = 2823,
     Priority_Equ = 2824,
     Priority_Compare = 2825,
     Priority_Shift = 2826,
     Priority_Term = 2827,
     Priority_Factor = 2828,
     Priority_Unary = 2829,
     Priority_IncDec = 2830,
     Syntax_IdentFunc = 3073,
     Syntax_IdentArr = 3074,
     Syntax_DefFunc = 3075,
     Syntax_DefArr = 3076,
     Syntax_DefVar = 3077,
     Syntax_Label = 3079,
     Syntax_Cast = 3080,
     Syntax_CastUnary = 3081,
     Syntax_EmptyCramp = 3082,
     Syntax_EmptyBracket = 3083,
     Syntax_EmptyScrape = 3084
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
#define YYLAST   321

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  135
/* YYNRULES -- Number of rules.  */
#define YYNRULES  216
/* YYNRULES -- Number of states.  */
#define YYNSTATES  308

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   3085

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
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    12,    13,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    14,    15,    16,    17,
      18,    19,     2,     2,     2,     2,    20,    21,    22,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    23,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    24,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    25,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,    50,    51,    52,    53,     2,    54,
      55,    56,    57,    58,    59,     2
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    10,    11,    17,    19,
      20,    21,    26,    27,    28,    34,    36,    37,    41,    42,
      46,    50,    52,    54,    56,    57,    58,    64,    66,    67,
      72,    73,    74,    75,    83,    85,    87,    91,    93,    94,
      97,    98,    99,   105,   109,   112,   114,   115,   119,   121,
     123,   124,   125,   130,   131,   132,   138,   140,   141,   144,
     145,   146,   151,   154,   156,   158,   160,   161,   165,   167,
     169,   171,   173,   177,   179,   180,   184,   185,   190,   192,
     194,   196,   198,   200,   202,   204,   206,   208,   210,   212,
     214,   218,   220,   221,   222,   223,   232,   234,   235,   240,
     241,   246,   247,   252,   253,   258,   259,   264,   265,   270,
     271,   276,   277,   282,   283,   288,   289,   294,   296,   297,
     301,   303,   304,   308,   309,   313,   314,   318,   319,   323,
     325,   329,   330,   333,   334,   337,   338,   342,   343,   347,
     348,   352,   353,   356,   358,   362,   365,   367,   369,   373,
     374,   377,   378,   383,   384,   388,   390,   391,   392,   397,
     399,   401,   403,   405,   407,   410,   412,   415,   416,   417,
     418,   419,   430,   432,   435,   438,   439,   440,   448,   449,
     454,   456,   457,   458,   464,   465,   474,   475,   482,   484,
     488,   489,   494,   497,   500,   502,   504,   507,   510,   512,
     514,   516,   518,   521,   523,   525,   527,   529,   531,   534,
     536,   537,   540,   542,   544,   546,   548
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      61,     0,    -1,   188,    -1,    -1,    25,    63,    -1,    -1,
      -1,    62,    11,    65,    66,   119,    -1,    62,    -1,    -1,
      -1,    50,    68,    69,    94,    -1,    -1,    -1,    67,    11,
      71,    72,   119,    -1,    67,    -1,    -1,    52,    74,    70,
      -1,    -1,    53,    75,    64,    -1,    76,    20,    73,    -1,
      73,    -1,    21,    -1,    57,    -1,    -1,    -1,    14,    78,
      79,   185,    15,    -1,    58,    -1,    -1,    16,    81,    76,
      17,    -1,    -1,    -1,    -1,    51,    83,    49,    84,    85,
      80,    77,    -1,    88,    -1,   119,    -1,    87,    20,    86,
      -1,    86,    -1,    -1,    57,    89,    -1,    -1,    -1,    14,
      90,    91,    87,    15,    -1,    18,   119,    19,    -1,    93,
      92,    -1,    92,    -1,    -1,    59,    95,    93,    -1,    59,
      -1,    93,    -1,    -1,    -1,    50,    97,    98,    94,    -1,
      -1,    -1,    96,    11,   100,   101,    88,    -1,    96,    -1,
      -1,    25,   103,    -1,    -1,    -1,    11,   105,   106,   119,
      -1,   102,   104,    -1,   102,    -1,    99,    -1,   107,    -1,
      -1,    41,   110,   108,    -1,   109,    -1,   108,    -1,    52,
      -1,    53,    -1,   113,    20,   111,    -1,   111,    -1,    -1,
     112,   115,   113,    -1,    -1,   116,    20,   119,   117,    -1,
     119,    -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,
       7,    -1,    11,    -1,     9,    -1,    10,    -1,     8,    -1,
      12,    -1,    13,    -1,   120,   118,   119,    -1,   120,    -1,
      -1,    -1,    -1,   124,    36,   121,   122,   193,    22,   123,
     120,    -1,   124,    -1,    -1,   124,    37,   125,   124,    -1,
      -1,   124,    38,   126,   124,    -1,    -1,   124,    39,   127,
     124,    -1,    -1,   124,    40,   128,   124,    -1,    -1,   124,
      41,   129,   124,    -1,    -1,   124,    42,   130,   124,    -1,
      -1,   124,    43,   131,   124,    -1,    -1,   124,    44,   132,
     124,    -1,    -1,   124,    45,   133,   124,    -1,    -1,   124,
      46,   134,   124,    -1,   137,    -1,    -1,   143,    48,   136,
      -1,   143,    -1,    -1,    47,   138,   137,    -1,    -1,    45,
     139,   137,    -1,    -1,    48,   140,   137,    -1,    -1,    56,
     141,   137,    -1,   135,    -1,    16,   192,    17,    -1,    -1,
      23,   144,    -1,    -1,    24,   145,    -1,    -1,    50,   146,
     151,    -1,    -1,    49,   147,   152,    -1,    -1,    55,   148,
     142,    -1,    -1,    25,   149,    -1,   142,    -1,    18,   193,
      19,    -1,   151,   150,    -1,   150,    -1,    58,    -1,    16,
     194,    17,    -1,    -1,    57,   154,    -1,    -1,    14,   155,
     185,    15,    -1,    -1,    41,   157,   104,    -1,   104,    -1,
      -1,    -1,    53,   159,   160,   156,    -1,   191,    -1,    21,
      -1,   181,    -1,   182,    -1,    21,    -1,   158,    21,    -1,
      17,    -1,   190,    17,    -1,    -1,    -1,    -1,    -1,    26,
      16,   165,   161,   166,   162,   167,   163,   168,   183,    -1,
      21,    -1,   193,    21,    -1,    34,   169,    -1,    -1,    -1,
      28,    16,   172,   158,    17,   173,   183,    -1,    -1,   171,
      29,   175,   183,    -1,   171,    -1,    -1,    -1,    54,   176,
      22,   177,   183,    -1,    -1,    30,   178,   183,    27,    16,
     158,    17,    21,    -1,    -1,    27,   179,    16,   158,    17,
     183,    -1,   164,    -1,    35,    16,    17,    -1,    -1,    31,
      25,   180,    21,    -1,    33,    21,    -1,    32,    21,    -1,
     170,    -1,   153,    -1,   114,    21,    -1,   190,    21,    -1,
      21,    -1,   181,    -1,   174,    -1,   182,    -1,   184,   183,
      -1,   183,    -1,   184,    -1,    21,    -1,    82,    -1,   181,
      -1,   187,   186,    -1,   186,    -1,    -1,   189,   187,    -1,
     116,    -1,   116,    -1,   116,    -1,   116,    -1,   116,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    94,    94,    97,    97,   100,   100,   100,   101,   104,
     104,   104,   107,   107,   107,   108,   111,   111,   112,   112,
     115,   116,   119,   120,   121,   121,   121,   124,   125,   125,
     128,   128,   128,   128,   131,   132,   135,   136,   139,   139,
     140,   140,   140,   143,   146,   147,   150,   150,   151,   152,
     155,   155,   155,   158,   158,   158,   159,   162,   162,   165,
     165,   165,   168,   169,   172,   173,   176,   176,   179,   180,
     183,   184,   187,   188,   191,   191,   194,   194,   195,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     211,   212,   215,   215,   215,   215,   216,   219,   219,   220,
     220,   221,   221,   222,   222,   223,   223,   224,   224,   225,
     225,   226,   226,   227,   227,   228,   228,   229,   232,   232,
     233,   236,   236,   237,   237,   238,   238,   239,   239,   240,
     243,   246,   246,   247,   247,   248,   248,   249,   249,   250,
     250,   251,   251,   252,   255,   258,   259,   262,   263,   266,
     266,   267,   267,   270,   270,   271,   274,   274,   274,   275,
     278,   279,   280,   283,   284,   287,   288,   291,   291,   291,
     291,   291,   294,   295,   298,   301,   301,   301,   304,   304,
     305,   306,   306,   306,   307,   307,   308,   308,   309,   310,
     311,   311,   312,   313,   314,   315,   318,   321,   324,   325,
     326,   327,   330,   331,   334,   337,   338,   339,   342,   343,
     346,   346,   349,   352,   355,   358,   361
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Oper_AddAssign", "Oper_SubAssign",
  "Oper_MultiAssign", "Oper_DivAssign", "Oper_ModAssign", "Oper_AndAssign",
  "Oper_OrAssign", "Oper_XOrAssign", "Oper_Assign", "Oper_LShiftAssign",
  "Oper_RShiftAssign", "Separator_LeftCramp", "Separator_RightCramp",
  "Separator_LeftBracket", "Separator_RightBracket",
  "Separator_LeftScrape", "Separator_RightScrape", "Separator_Comma",
  "Separator_Semicolon", "Separator_Colon", "Integer_lexeme",
  "Number_lexeme", "Ident_lexeme", "Reserv_For", "Reserv_While",
  "Reserv_If", "Reserv_Else", "Reserv_Do", "Reserv_GoTo",
  "Reserv_Continue", "Reserv_Break", "Reserv_Return", "Reserv_Switch",
  "Priority_Question", "Priority_OrOr", "Priority_AndAnd", "Priority_Or",
  "Priority_XOr", "Priority_And", "Priority_Equ", "Priority_Compare",
  "Priority_Shift", "Priority_Term", "Priority_Factor", "Priority_Unary",
  "Priority_IncDec", "Syntax_IdentFunc", "Syntax_IdentArr",
  "Syntax_DefFunc", "Syntax_DefArr", "Syntax_DefVar", "Syntax_Label",
  "Syntax_Cast", "Syntax_CastUnary", "Syntax_EmptyCramp",
  "Syntax_EmptyBracket", "Syntax_EmptyScrape", "$accept", "Program",
  "DefBegParVar", "$@1", "DefParVar", "$@2", "$@3", "DefBegParArr", "$@4",
  "$@5", "DefParArr", "$@6", "$@7", "DefParItem", "$@8", "$@9",
  "DefParams", "BodyFunc", "$@10", "$@11", "DefFunc_", "$@12", "DefFunc",
  "$@13", "$@14", "$@15", "AInitItem", "AInitial", "Initializer", "$@16",
  "$@17", "$@18", "DefRanges_", "DefRanges", "DefBegRanges", "$@19",
  "DefBegArr", "$@20", "$@21", "DefArr", "$@22", "$@23", "DefVarIdent",
  "$@24", "DefVarAssign", "$@25", "$@26", "DefVar", "DefIAV", "RefDefIAV",
  "$@27", "DefItem", "DefType", "DefineComma", "Define", "$@28",
  "Expressions", "$@29", "PriorAssign", "Assign", "Question", "$@30",
  "$@31", "$@32", "Binary", "$@33", "$@34", "$@35", "$@36", "$@37", "$@38",
  "$@39", "$@40", "$@41", "$@42", "UnaryIncDec", "$@43", "Unary", "$@44",
  "$@45", "$@46", "$@47", "Primary", "PrimaryExpr", "$@48", "$@49", "$@50",
  "$@51", "$@52", "$@53", "Range", "Ranges", "CallParams", "CompaundStmnt",
  "$@54", "$@55", "Condition_V", "$@56", "Condition", "$@57", "$@58",
  "For_Prefix", "For_Condition", "For_Postfix", "ForStmnt", "$@59", "$@60",
  "$@61", "$@62", "ReturnValue", "ReturnStmnt", "BegIfStmnt", "$@63",
  "$@64", "Statement", "$@65", "$@66", "$@67", "$@68", "$@69", "$@70",
  "DefineSemi", "ExprSemi", "DefExpr", "StmExprList", "StmExpr", "DefFAV",
  "DefinesList", "Defines", "$@71", "ExpressionExpression",
  "ExpressionCondition", "ExpressionNone", "ExpressionValue",
  "ExpressionValueList", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,  3085,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   288,   289,   546,   547,   548,   549,   550,   551,
     556,   557,   558,   768,  1024,  1536,  1793,  1794,  1795,  1796,
    1797,  1798,  1799,  1800,  1801,  1802,  2818,  2819,  2820,  2821,
    2822,  2823,  2824,  2825,  2826,  2827,  2828,  2829,  2830,  3073,
    3074,  3075,  3076,  3077,  3079,  3080,  3081,  3082,  3083,  3084
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    63,    62,    65,    66,    64,    64,    68,
      69,    67,    71,    72,    70,    70,    74,    73,    75,    73,
      76,    76,    77,    77,    78,    79,    77,    80,    81,    80,
      83,    84,    85,    82,    86,    86,    87,    87,    89,    88,
      90,    91,    88,    92,    93,    93,    95,    94,    94,    94,
      97,    98,    96,   100,   101,    99,    99,   103,   102,   105,
     106,   104,   107,   107,   108,   108,   110,   109,   111,   111,
     112,   112,   113,   113,   115,   114,   117,   116,   116,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     119,   119,   121,   122,   123,   120,   120,   125,   124,   126,
     124,   127,   124,   128,   124,   129,   124,   130,   124,   131,
     124,   132,   124,   133,   124,   134,   124,   124,   136,   135,
     135,   138,   137,   139,   137,   140,   137,   141,   137,   137,
     142,   144,   143,   145,   143,   146,   143,   147,   143,   148,
     143,   149,   143,   143,   150,   151,   151,   152,   152,   154,
     153,   155,   153,   157,   156,   156,   159,   160,   158,   158,
     161,   161,   161,   162,   162,   163,   163,   165,   166,   167,
     168,   164,   169,   169,   170,   172,   173,   171,   175,   174,
     174,   176,   177,   174,   178,   174,   179,   174,   174,   174,
     180,   174,   174,   174,   174,   174,   181,   182,   183,   183,
     183,   183,   184,   184,   185,   186,   186,   186,   187,   187,
     189,   188,   190,   191,   192,   193,   194
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     0,     0,     5,     1,     0,
       0,     4,     0,     0,     5,     1,     0,     3,     0,     3,
       3,     1,     1,     1,     0,     0,     5,     1,     0,     4,
       0,     0,     0,     7,     1,     1,     3,     1,     0,     2,
       0,     0,     5,     3,     2,     1,     0,     3,     1,     1,
       0,     0,     4,     0,     0,     5,     1,     0,     2,     0,
       0,     4,     2,     1,     1,     1,     0,     3,     1,     1,
       1,     1,     3,     1,     0,     3,     0,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     0,     0,     8,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     0,     3,
       1,     0,     3,     0,     3,     0,     3,     0,     3,     1,
       3,     0,     2,     0,     2,     0,     3,     0,     3,     0,
       3,     0,     2,     1,     3,     2,     1,     1,     3,     0,
       2,     0,     4,     0,     3,     1,     0,     0,     4,     1,
       1,     1,     1,     1,     2,     1,     2,     0,     0,     0,
       0,    10,     1,     2,     2,     0,     0,     7,     0,     4,
       1,     0,     0,     5,     0,     8,     0,     6,     1,     3,
       0,     4,     2,     2,     1,     1,     2,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     2,     1,
       0,     2,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     210,     0,     2,     0,     1,   205,    30,    70,    71,   206,
      74,     0,   207,   209,   211,     0,     0,   196,   208,    31,
      57,    66,    50,    56,    64,    63,    65,    69,    68,    73,
      75,    32,    58,     0,    51,    53,    59,    62,     0,     0,
      67,     0,    54,    60,    72,    28,    27,     0,     0,    48,
      45,    49,    52,     0,     0,     0,    24,    22,    23,    33,
       0,   131,   133,   141,   123,   121,   125,   137,   135,   139,
     127,     0,    91,    96,   129,   117,   143,   120,     0,    44,
      40,    38,    55,    61,    16,    18,    21,     0,    25,   214,
      78,     0,   132,   134,   142,     0,     0,     0,     0,     0,
       0,     0,    43,    79,    80,    81,    82,    83,    87,    85,
      86,    84,    88,    89,     0,    92,    97,    99,   101,   103,
     105,   107,   109,   111,   113,   115,   118,    47,    41,    39,
       0,     0,    29,     0,     0,     0,   130,   124,   122,   126,
       0,   147,   138,     0,   146,   136,   140,   128,    90,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     119,     0,     9,    15,    17,     3,     8,    19,    20,   151,
     198,     0,   186,     0,   184,     0,     0,     0,     0,     0,
     181,   149,   212,   195,   188,   194,   180,   200,   199,   201,
     203,   204,     0,     0,    76,   216,     0,   215,     0,   145,
       0,    98,   100,   102,   104,   106,   108,   110,   112,   114,
     116,    37,     0,    34,    35,    10,    12,     4,     5,     0,
     167,     0,   175,     0,   190,   193,   192,   172,   174,     0,
       0,     0,   150,   178,   202,    26,   197,    77,   148,   144,
       0,    42,     0,     0,    13,     6,     0,     0,     0,     0,
       0,     0,   173,   189,   182,     0,    94,    36,    11,     0,
       0,   152,   160,   168,   161,   162,   156,   213,     0,   159,
       0,     0,   191,     0,   179,     0,    14,     7,     0,   157,
       0,   176,     0,   183,    95,   163,     0,   169,     0,   187,
       0,     0,   164,     0,   153,   155,   158,   177,     0,   165,
     170,     0,     0,   185,     0,   166,   154,   171
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   166,   217,   167,   245,   260,   163,   215,   243,
     164,   244,   259,    86,   130,   131,    87,    59,    88,   134,
      47,    55,     9,    15,    31,    39,   211,   212,   213,   129,
     128,   161,    50,    51,    52,    78,    23,    34,    41,    24,
      42,    53,    25,    32,    37,    43,    54,    26,    27,    28,
      33,    29,    10,    30,    11,    16,   182,   237,   114,    90,
      72,   149,   200,   275,    73,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,    74,   160,    75,    96,    95,
      97,   101,    76,    77,    92,    93,    99,    98,   100,    94,
     144,   145,   142,   183,   232,   219,   296,   302,   268,   279,
     288,   263,   287,   300,   184,   247,   278,   293,   304,   228,
     185,   186,   249,   290,   187,   255,   231,   273,   223,   221,
     251,   188,   189,   190,   191,   192,    13,    14,     2,     3,
     193,   269,    91,   198,   196
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -252
static const yytype_int16 yypact[] =
{
    -252,    33,  -252,    35,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,    21,  -252,  -252,    35,    16,    25,  -252,  -252,  -252,
    -252,  -252,  -252,    63,  -252,    68,  -252,  -252,  -252,  -252,
      74,  -252,  -252,     4,  -252,  -252,  -252,  -252,    25,    11,
    -252,     2,  -252,  -252,  -252,  -252,  -252,    -8,   216,    96,
    -252,    99,  -252,    -5,   216,     5,  -252,  -252,  -252,  -252,
     216,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,   104,   270,   248,  -252,  -252,  -252,    76,    99,  -252,
    -252,  -252,  -252,  -252,  -252,  -252,  -252,    14,  -252,   111,
    -252,   126,  -252,  -252,  -252,   216,   216,   216,    12,   130,
     135,   216,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,  -252,  -252,  -252,   216,  -252,  -252,  -252,  -252,  -252,
    -252,  -252,  -252,  -252,  -252,  -252,  -252,    99,  -252,  -252,
     105,   136,  -252,     5,    -9,   216,  -252,  -252,  -252,  -252,
     216,  -252,  -252,   216,  -252,   130,  -252,  -252,  -252,  -252,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
    -252,    48,  -252,   149,  -252,  -252,   152,  -252,  -252,  -252,
    -252,   151,  -252,   153,  -252,   143,   155,   156,   150,   154,
    -252,  -252,   111,  -252,  -252,  -252,   159,  -252,  -252,  -252,
    -252,    -9,   157,   163,  -252,   111,   174,   111,   173,  -252,
     216,   267,   275,    66,    94,   137,    83,    55,    45,   147,
    -252,  -252,    40,  -252,  -252,  -252,  -252,  -252,  -252,    -9,
    -252,   178,  -252,    -9,  -252,  -252,  -252,  -252,  -252,   180,
     185,   181,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
     182,  -252,    48,     2,  -252,  -252,   193,    97,   162,   162,
     189,   201,  -252,  -252,  -252,    -9,  -252,  -252,  -252,   216,
     216,  -252,  -252,  -252,  -252,  -252,  -252,   111,   207,  -252,
     208,   210,  -252,    -9,  -252,   216,  -252,  -252,   109,  -252,
      -9,  -252,   162,  -252,  -252,  -252,   209,  -252,    42,  -252,
      -9,   214,  -252,   204,  -252,  -252,  -252,  -252,   212,  -252,
    -252,   217,    68,  -252,    -9,  -252,  -252,  -252
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,  -252,  -252,   102,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,  -252,  -252,  -252,  -252,  -252,    -6,  -252,   184,  -252,
    -252,  -252,   -47,   160,    -1,  -252,  -252,  -252,  -252,  -252,
    -252,  -252,  -252,  -252,  -251,  -252,  -252,  -252,   213,  -252,
    -252,   205,  -252,  -252,  -252,  -252,   -59,  -252,  -252,   -46,
     -30,  -252,  -252,  -252,   145,  -252,  -252,  -252,  -252,  -252,
    -252,  -252,  -252,  -252,  -252,  -252,  -252,   -19,  -252,  -252,
    -252,  -252,   148,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
     110,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -219,  -252,
    -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,    -3,     0,  -188,  -252,    31,   242,  -252,  -252,  -252,
     -36,  -252,  -252,  -168,  -252
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -47
static const yytype_int16 yytable[] =
{
      12,    89,    71,   234,    79,   169,    56,    60,    83,    80,
     229,    12,   170,    57,    61,    62,    63,   171,   172,   173,
      48,   174,   175,   176,   177,   178,   179,    45,   140,    20,
     270,   132,   240,     4,   133,   250,    64,   295,    65,    66,
      67,    68,    17,     7,     8,   180,    69,    70,   181,    58,
      20,   306,    81,    36,    22,   241,     5,    84,    85,   286,
     242,    49,    80,   291,    60,    19,    21,   274,   148,    46,
     141,    61,    62,    63,    35,    22,   137,   138,   139,    36,
      79,   195,   147,   294,   197,   283,     6,     7,     8,   194,
     124,   125,   289,    64,    38,    65,    66,    67,    68,   123,
     124,   125,   297,    69,    70,    81,   119,   120,   121,   122,
     123,   124,   125,    60,   -46,   214,   307,    48,   262,   197,
      61,    62,    63,   102,   126,    60,   122,   123,   124,   125,
     285,   135,    61,    62,    63,   120,   121,   122,   123,   124,
     125,   197,    64,   136,    65,    66,    67,    68,   143,     7,
       8,    60,    69,    70,    64,   162,    65,    66,    67,    68,
     216,   165,   266,   218,    69,    70,    60,   220,   224,   222,
     230,   227,   235,    61,    62,    63,   225,   226,    60,   121,
     122,   123,   124,   125,   236,    61,    62,    63,   233,   267,
     267,   238,   239,   125,   248,    64,   214,    65,    66,    67,
      68,   252,   253,   254,   256,    69,    70,    64,   261,    65,
      66,    67,    68,   276,   277,   266,   271,    69,    70,   267,
      60,   299,   272,   267,   280,   281,   282,    61,    62,    63,
     292,   298,    60,   303,   305,   168,   257,    82,   127,    61,
      62,    63,   258,    44,   264,   284,    40,   265,   146,    64,
     246,    65,    66,    67,    68,   199,    18,   301,     0,    69,
      70,    64,     0,    65,    66,    67,    68,     0,     0,     0,
       0,    69,    70,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   118,   119,   120,   121,   122,   123,
     124,   125
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-252)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       3,    60,    48,   191,    51,    14,    14,    16,    54,    14,
     178,    14,    21,    21,    23,    24,    25,    26,    27,    28,
      18,    30,    31,    32,    33,    34,    35,    16,    16,    25,
     249,    17,   200,     0,    20,   223,    45,   288,    47,    48,
      49,    50,    21,    52,    53,    54,    55,    56,    57,    57,
      25,   302,    57,    11,    50,    15,    21,    52,    53,   278,
      20,    59,    14,   282,    16,    49,    41,   255,   114,    58,
      58,    23,    24,    25,    11,    50,    95,    96,    97,    11,
     127,   140,   101,    41,   143,   273,    51,    52,    53,   135,
      45,    46,   280,    45,    20,    47,    48,    49,    50,    44,
      45,    46,   290,    55,    56,    57,    40,    41,    42,    43,
      44,    45,    46,    16,    18,   161,   304,    18,    21,   178,
      23,    24,    25,    19,    48,    16,    43,    44,    45,    46,
      21,    20,    23,    24,    25,    41,    42,    43,    44,    45,
      46,   200,    45,    17,    47,    48,    49,    50,    18,    52,
      53,    16,    55,    56,    45,    50,    47,    48,    49,    50,
      11,    25,    53,    11,    55,    56,    16,    16,    25,    16,
      16,    21,    15,    23,    24,    25,    21,    21,    16,    42,
      43,    44,    45,    46,    21,    23,    24,    25,    29,   248,
     249,    17,    19,    46,    16,    45,   242,    47,    48,    49,
      50,    21,    17,    22,    22,    55,    56,    45,    15,    47,
      48,    49,    50,   259,   260,    53,    27,    55,    56,   278,
      16,    17,    21,   282,    17,    17,    16,    23,    24,    25,
      21,    17,    16,    21,    17,   133,   242,    53,    78,    23,
      24,    25,   243,    38,   247,   275,    33,   247,   100,    45,
     219,    47,    48,    49,    50,   145,    14,   293,    -1,    55,
      56,    45,    -1,    47,    48,    49,    50,    -1,    -1,    -1,
      -1,    55,    56,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    39,    40,    41,    42,    43,    44,
      45,    46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    61,   188,   189,     0,    21,    51,    52,    53,    82,
     112,   114,   181,   186,   187,    83,   115,    21,   186,    49,
      25,    41,    50,    96,    99,   102,   107,   108,   109,   111,
     113,    84,   103,   110,    97,    11,    11,   104,    20,    85,
     108,    98,   100,   105,   111,    16,    58,    80,    18,    59,
      92,    93,    94,   101,   106,    81,    14,    21,    57,    77,
      16,    23,    24,    25,    45,    47,    48,    49,    50,    55,
      56,   119,   120,   124,   135,   137,   142,   143,    95,    92,
      14,    57,    88,   119,    52,    53,    73,    76,    78,   116,
     119,   192,   144,   145,   149,   139,   138,   140,   147,   146,
     148,   141,    19,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   118,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    48,    93,    90,    89,
      74,    75,    17,    20,    79,    20,    17,   137,   137,   137,
      16,    58,   152,    18,   150,   151,   142,   137,   119,   121,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     136,    91,    50,    67,    70,    25,    62,    64,    73,    14,
      21,    26,    27,    28,    30,    31,    32,    33,    34,    35,
      54,    57,   116,   153,   164,   170,   171,   174,   181,   182,
     183,   184,   185,   190,   119,   116,   194,   116,   193,   150,
     122,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,    86,    87,    88,   119,    68,    11,    63,    11,   155,
      16,   179,    16,   178,    25,    21,    21,    21,   169,   193,
      16,   176,   154,    29,   183,    15,    21,   117,    17,    19,
     193,    15,    20,    69,    71,    65,   185,   165,    16,   172,
     183,   180,    21,    17,    22,   175,    22,    86,    94,    72,
      66,    15,    21,   161,   181,   182,    53,   116,   158,   191,
     158,    27,    21,   177,   183,   123,   119,   119,   166,   159,
      17,    17,    16,   183,   120,    21,   158,   162,   160,   183,
     173,   158,    21,   167,    41,   104,   156,   183,    17,    17,
     163,   190,   157,    21,   168,    17,   104,   183
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

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 4:

    { MAKE(DefParVar,0); }
    break;

  case 5:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 6:

    { CODE(BegParVarAssign,0); }
    break;

  case 7:

    { MAKE(ParVarAssign,0); }
    break;

  case 9:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 10:

    { MAKE(DefParArr,0); }
    break;

  case 12:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 13:

    { CODE(BegParVarAssign,0); }
    break;

  case 14:

    { MAKE(ParVarAssign,0); }
    break;

  case 16:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 18:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 20:

    { TREE(AddToList,0); }
    break;

  case 21:

    { TREE(AddToList,0); }
    break;

  case 22:

    { MAKE(BodyFunc,0); }
    break;

  case 23:

    { MAKE(BodyFunc,1); }
    break;

  case 24:

    { CODE(EndParams,0); }
    break;

  case 25:

    { MAKE(BegStmExprLR,0); }
    break;

  case 26:

    { MAKE(BodyFunc,2); }
    break;

  case 27:

    { TREE(EndParams,2); }
    break;

  case 28:

    { TREE(Define,2); }
    break;

  case 29:

    { TREE(EndParams,0); }
    break;

  case 30:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 31:

    { SAVE((yyvsp[(3) - (3)])); }
    break;

  case 32:

    { MAKE(FuncIdent,0); }
    break;

  case 35:

    { CODE(AInitItem,0); }
    break;

  case 36:

    { TREE(AddToList,0); }
    break;

  case 37:

    { TREE(AddToList,0); }
    break;

  case 38:

    { CODE(BegInitial,0); }
    break;

  case 39:

    { TREE(NodeListLR,0); }
    break;

  case 40:

    { CODE(BegInitial,1); }
    break;

  case 41:

    { TREE(NodeListLR,0); }
    break;

  case 42:

    { CODE(EndInitial,0); }
    break;

  case 44:

    { MAKE(DRange,0); }
    break;

  case 45:

    { MAKE(DRange,0); }
    break;

  case 46:

    { MAKE(DefArrD1AEmpty,0); }
    break;

  case 48:

    { MAKE(DefArrD1AEmpty,0); }
    break;

  case 50:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 51:

    { MAKE(DefArray,0); }
    break;

  case 52:

    { CODE(EndRanges,0); }
    break;

  case 53:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 54:

    { CODE(BegAInit,0); }
    break;

  case 55:

    { MAKE(EndAInit,0); }
    break;

  case 57:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 58:

    { MAKE(DefIdent,0); }
    break;

  case 59:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 60:

    { CODE(BegDefVarAssign,0); }
    break;

  case 61:

    { MAKE(DefVarAssign,0); }
    break;

  case 66:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 67:

    { TREE(RefDef,0); }
    break;

  case 70:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 71:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 72:

    { TREE(AddToList,0); }
    break;

  case 73:

    { TREE(AddToList,0); }
    break;

  case 74:

    { MAKE(Define,0); }
    break;

  case 75:

    { CODE(EndDefine,0); }
    break;

  case 76:

    { TREE(AddToList,0); }
    break;

  case 77:

    { CODE(AddToExpr,0); }
    break;

  case 78:

    { MAKE(ExpressionsLR,0); }
    break;

  case 79:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 80:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 81:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 82:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 83:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 84:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 85:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 86:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 87:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 88:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 89:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 90:

    { MAKE(Binary,0); }
    break;

  case 92:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 93:

    { CODE(BegQuestion,0); }
    break;

  case 94:

    { CODE(MidQuestion,0); }
    break;

  case 95:

    { MAKE(Question,0); }
    break;

  case 97:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 98:

    { MAKE(Binary,0); }
    break;

  case 99:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 100:

    { MAKE(Binary,0); }
    break;

  case 101:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 102:

    { MAKE(Binary,0); }
    break;

  case 103:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 104:

    { MAKE(Binary,0); }
    break;

  case 105:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 106:

    { MAKE(Binary,0); }
    break;

  case 107:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 108:

    { MAKE(Binary,0); }
    break;

  case 109:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 110:

    { MAKE(Binary,0); }
    break;

  case 111:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 112:

    { MAKE(Binary,0); }
    break;

  case 113:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 114:

    { MAKE(Binary,0); }
    break;

  case 115:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 116:

    { MAKE(Binary,0); }
    break;

  case 118:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 119:

    { MAKE(IncDec,0); }
    break;

  case 121:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 122:

    { MAKE(Unary,0); }
    break;

  case 123:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 124:

    { MAKE(Unary,0); }
    break;

  case 125:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 126:

    { MAKE(Unary,0); }
    break;

  case 127:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 128:

    { MAKE(Cast,0); }
    break;

  case 130:

    { TREE(Primary,0); }
    break;

  case 131:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 132:

    { MAKE(Number,0); }
    break;

  case 133:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 134:

    { MAKE(Number,0); }
    break;

  case 135:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 136:

    { MAKE(EndIndex,0); }
    break;

  case 137:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 139:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 140:

    { MAKE(Cast,0); }
    break;

  case 141:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 142:

    { MAKE(Ident,0); }
    break;

  case 145:

    { MAKE(IndexLR,0); }
    break;

  case 146:

    { MAKE(BegIndexLR,0); }
    break;

  case 147:

    { MAKE(Params,0); }
    break;

  case 148:

    { MAKE(Params,1); }
    break;

  case 149:

    { MAKE(Compaund,0); }
    break;

  case 150:

    { CODE(EndBlock,0); }
    break;

  case 151:

    { MAKE(Compaund,0); }
    break;

  case 153:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 154:

    { TREE(RefDef,0); }
    break;

  case 156:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 157:

    { MAKE(Define,0); }
    break;

  case 158:

    { MAKE(PushDef,0); }
    break;

  case 160:

    { TREE(NodeNull,0); }
    break;

  case 163:

    { MAKE(NodeNull,0); }
    break;

  case 165:

    { TREE(NodeNull,0); }
    break;

  case 167:

    { MAKE(BegFor,0); }
    break;

  case 168:

    { CODE(PrefFor,0); }
    break;

  case 169:

    { CODE(ConditionFor,0); }
    break;

  case 170:

    { CODE(PostFor,0); }
    break;

  case 171:

    { MAKE(For,0); }
    break;

  case 172:

    { MAKE(Return,0); }
    break;

  case 173:

    { MAKE(Return,1); }
    break;

  case 175:

    { CODE(BegIf,0); }
    break;

  case 176:

    { CODE(Then,0); }
    break;

  case 178:

    { CODE(Else,0); }
    break;

  case 179:

    { MAKE(If,1); }
    break;

  case 180:

    { MAKE(If,0); }
    break;

  case 181:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 182:

    { CODE(Label,0); }
    break;

  case 183:

    { TREE(Label,0); }
    break;

  case 184:

    { MAKE(BegDo,0); }
    break;

  case 185:

    { MAKE(Do,0); }
    break;

  case 186:

    { MAKE(BegWhile,0); }
    break;

  case 190:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 191:

    { MAKE(GoTo,0); }
    break;

  case 192:

    { MAKE(Break,0); }
    break;

  case 193:

    { MAKE(Continue,0); }
    break;

  case 198:

    { TREE(NodeNull,0); }
    break;

  case 202:

    { TREE(AddToList,0); }
    break;

  case 203:

    { TREE(AddToList,0); }
    break;

  case 204:

    { CODE(EndBlock,0); }
    break;

  case 205:

    { TREE(NodeNull,0); }
    break;

  case 208:

    { TREE(AddToList,0); }
    break;

  case 209:

    { TREE(BegStmExprLR,1); }
    break;

  case 210:

    { CODE(BegStmExprLR,0); }
    break;

  case 211:

    { CODE(EndBlock,0); }
    break;

  case 212:

    { MAKE(ExpressionSLR,16); }
    break;

  case 213:

    { MAKE(ExpressionSLR,241); }
    break;

  case 214:

    { MAKE(ExpressionSLR,0); }
    break;

  case 215:

    { MAKE(ExpressionSLR,256); }
    break;

  case 216:

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




