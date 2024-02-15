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
#define YYLAST   303

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  192
/* YYNRULES -- Number of rules.  */
#define YYNRULES  270
/* YYNRULES -- Number of states.  */
#define YYNSTATES  376

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
      33,    34,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,    49,    50,    51,    52,     2,    53,
      54,    55,    56,    57,    58,     2
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     7,    12,    13,    14,    15,
      16,    23,    24,    25,    26,    34,    36,    38,    40,    44,
      45,    46,    50,    52,    54,    55,    60,    62,    66,    67,
      68,    69,    77,    78,    83,    84,    85,    89,    90,    93,
      94,    95,   101,   103,   105,   106,   107,   112,   113,   114,
     120,   121,   123,   127,   130,   131,   132,   138,   139,   140,
     145,   147,   148,   149,   150,   155,   157,   159,   160,   164,
     166,   168,   170,   171,   176,   177,   178,   179,   185,   186,
     190,   192,   193,   194,   199,   201,   202,   203,   209,   210,
     211,   215,   217,   219,   221,   223,   225,   227,   229,   231,
     233,   235,   237,   240,   241,   244,   245,   246,   247,   255,
     256,   259,   262,   263,   264,   270,   271,   274,   275,   276,
     282,   283,   286,   287,   288,   294,   295,   298,   299,   300,
     306,   307,   310,   311,   312,   318,   319,   322,   323,   324,
     330,   331,   334,   335,   336,   342,   343,   346,   347,   348,
     354,   355,   358,   359,   360,   366,   367,   370,   371,   372,
     378,   379,   380,   383,   384,   385,   389,   390,   394,   395,
     399,   400,   404,   407,   411,   412,   415,   416,   419,   420,
     424,   425,   429,   430,   434,   435,   438,   440,   441,   447,
     448,   449,   452,   454,   458,   459,   462,   463,   464,   470,
     471,   475,   476,   477,   478,   487,   489,   491,   493,   495,
     498,   500,   503,   504,   505,   506,   507,   518,   519,   520,
     530,   531,   532,   540,   541,   546,   549,   552,   554,   555,
     559,   560,   561,   567,   569,   571,   573,   575,   577,   579,
     581,   583,   585,   588,   591,   593,   595,   597,   599,   600,
     604,   605,   606,   609,   611,   613,   615,   616,   620,   621,
     622,   625,   626,   629,   630,   633,   634,   637,   638,   641,
     642
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      60,     0,    -1,   239,    -1,    -1,    -1,    11,    62,    63,
     131,    -1,    -1,    -1,    -1,    -1,    52,    65,    25,    66,
      67,    61,    -1,    -1,    -1,    -1,    51,    69,    49,    70,
      71,    99,    61,    -1,    68,    -1,    64,    -1,    72,    -1,
      20,    73,    74,    -1,    -1,    -1,    76,    73,    74,    -1,
      21,    -1,    56,    -1,    -1,    14,    78,   234,    15,    -1,
      57,    -1,    16,    75,    17,    -1,    -1,    -1,    -1,    50,
      81,    48,    82,    83,    79,    77,    -1,    -1,    20,    92,
      85,    84,    -1,    -1,    -1,    92,    87,    84,    -1,    -1,
      56,    89,    -1,    -1,    -1,    14,    90,    91,    86,    15,
      -1,    88,    -1,   131,    -1,    -1,    -1,    11,    94,    95,
      88,    -1,    -1,    -1,    18,   131,    19,    97,    96,    -1,
      -1,    58,    -1,    18,   131,    19,    -1,    98,    96,    -1,
      -1,    -1,    49,   101,   102,    99,    93,    -1,    -1,    -1,
      11,   104,   105,   131,    -1,   103,    -1,    -1,    -1,    -1,
      25,   108,   109,   106,    -1,   100,    -1,   107,    -1,    -1,
      40,   112,   110,    -1,   110,    -1,    51,    -1,    52,    -1,
      -1,    20,   111,   115,   114,    -1,    -1,    -1,    -1,   113,
     117,   111,   118,   114,    -1,    -1,    40,   120,   107,    -1,
     107,    -1,    -1,    -1,    52,   122,   123,   119,    -1,   243,
      -1,    -1,    -1,    20,   131,   125,   126,   124,    -1,    -1,
      -1,   131,   128,   124,    -1,     3,    -1,     4,    -1,     5,
      -1,     6,    -1,     7,    -1,    11,    -1,     9,    -1,    10,
      -1,     8,    -1,    12,    -1,    13,    -1,   129,   131,    -1,
      -1,   136,   130,    -1,    -1,    -1,    -1,    35,   133,   134,
     247,    22,   135,   136,    -1,    -1,   137,   132,    -1,   141,
     138,    -1,    -1,    -1,    36,   139,   141,   140,   138,    -1,
      -1,   145,   142,    -1,    -1,    -1,    37,   143,   145,   144,
     142,    -1,    -1,   149,   146,    -1,    -1,    -1,    38,   147,
     149,   148,   146,    -1,    -1,   153,   150,    -1,    -1,    -1,
      39,   151,   153,   152,   150,    -1,    -1,   157,   154,    -1,
      -1,    -1,    40,   155,   157,   156,   154,    -1,    -1,   161,
     158,    -1,    -1,    -1,    41,   159,   161,   160,   158,    -1,
      -1,   165,   162,    -1,    -1,    -1,    42,   163,   165,   164,
     162,    -1,    -1,   169,   166,    -1,    -1,    -1,    43,   167,
     169,   168,   166,    -1,    -1,   173,   170,    -1,    -1,    -1,
      44,   171,   173,   172,   170,    -1,    -1,   179,   174,    -1,
      -1,    -1,    45,   175,   179,   176,   174,    -1,    -1,    -1,
      47,   178,    -1,    -1,    -1,    46,   180,   179,    -1,    -1,
      44,   181,   179,    -1,    -1,    47,   182,   179,    -1,    -1,
      55,   183,   179,    -1,   185,   177,    -1,    16,   245,    17,
      -1,    -1,    23,   186,    -1,    -1,    24,   187,    -1,    -1,
      49,   188,   194,    -1,    -1,    48,   189,   196,    -1,    -1,
      54,   190,   184,    -1,    -1,    25,   191,    -1,   184,    -1,
      -1,    18,   247,    19,   193,   192,    -1,    -1,    -1,   195,
     192,    -1,    57,    -1,    16,   249,    17,    -1,    -1,    56,
     198,    -1,    -1,    -1,    14,   199,   234,    15,   200,    -1,
      -1,    29,   202,   231,    -1,    -1,    -1,    -1,    28,    16,
     204,   121,    17,   205,   231,   201,    -1,    21,    -1,   229,
      -1,   230,    -1,    21,    -1,   121,    21,    -1,    17,    -1,
     241,    17,    -1,    -1,    -1,    -1,    -1,    26,    16,   210,
     206,   211,   207,   212,   208,   213,   231,    -1,    -1,    -1,
      30,   215,   231,    27,    16,   216,   121,    17,    21,    -1,
      -1,    -1,    27,   218,    16,   121,    17,   219,   231,    -1,
      -1,    31,    25,   221,    21,    -1,    33,    21,    -1,    32,
      21,    -1,   247,    -1,    -1,    34,   224,    21,    -1,    -1,
      -1,    53,   227,    22,   228,   231,    -1,   203,    -1,   214,
      -1,   217,    -1,   209,    -1,   220,    -1,   222,    -1,   223,
      -1,   225,    -1,   197,    -1,   116,    21,    -1,   241,    21,
      -1,    21,    -1,   229,    -1,   226,    -1,   230,    -1,    -1,
     231,   233,   232,    -1,    -1,    -1,   235,   232,    -1,    21,
      -1,    80,    -1,   229,    -1,    -1,   236,   238,   237,    -1,
      -1,    -1,   240,   237,    -1,    -1,   242,   127,    -1,    -1,
     244,   127,    -1,    -1,   246,   127,    -1,    -1,   248,   127,
      -1,    -1,   250,   127,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    93,    93,    96,    96,    96,    97,   100,   100,   100,
     100,   103,   103,   103,   103,   106,   107,   110,   113,   114,
     117,   117,   120,   121,   122,   122,   125,   126,   129,   129,
     129,   129,   132,   132,   133,   136,   136,   139,   139,   140,
     140,   140,   143,   144,   147,   147,   147,   148,   151,   151,
     152,   155,   156,   159,   162,   162,   162,   165,   165,   165,
     168,   169,   172,   172,   172,   175,   176,   179,   179,   180,
     183,   184,   187,   187,   188,   191,   191,   191,   194,   194,
     195,   198,   198,   198,   199,   202,   202,   202,   203,   206,
     206,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   222,   223,   226,   229,   229,   229,   229,   230,
     233,   236,   239,   239,   239,   240,   243,   246,   246,   246,
     247,   250,   253,   253,   253,   254,   257,   260,   260,   260,
     261,   264,   267,   267,   267,   268,   271,   274,   274,   274,
     275,   278,   281,   281,   281,   282,   285,   288,   288,   288,
     289,   292,   295,   295,   295,   296,   299,   302,   302,   302,
     303,   306,   306,   307,   310,   310,   311,   311,   312,   312,
     313,   313,   314,   317,   320,   320,   321,   321,   322,   322,
     323,   323,   324,   324,   325,   325,   326,   329,   329,   330,
     333,   333,   336,   337,   340,   340,   341,   341,   341,   344,
     344,   345,   348,   348,   348,   351,   352,   353,   356,   357,
     360,   361,   364,   364,   364,   364,   364,   367,   367,   367,
     370,   370,   370,   373,   373,   376,   379,   382,   383,   386,
     389,   389,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   401,   404,   407,   408,   409,   410,   413,   413,
     414,   417,   417,   420,   421,   422,   425,   425,   426,   429,
     429,   432,   432,   435,   435,   438,   438,   441,   441,   444,
     444
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
  "Reserv_Continue", "Reserv_Break", "Reserv_Return", "Priority_Question",
  "Priority_OrOr", "Priority_AndAnd", "Priority_Or", "Priority_XOr",
  "Priority_And", "Priority_Equ", "Priority_Compare", "Priority_Shift",
  "Priority_Term", "Priority_Factor", "Priority_Unary", "Priority_IncDec",
  "Syntax_IdentFunc", "Syntax_IdentArr", "Syntax_DefFunc", "Syntax_DefArr",
  "Syntax_DefVar", "Syntax_Label", "Syntax_Cast", "Syntax_CastUnary",
  "Syntax_EmptyCramp", "Syntax_EmptyBracket", "Syntax_EmptyScrape",
  "$accept", "Program", "DefParInit", "$@1", "$@2", "DefParVar", "$@3",
  "$@4", "$@5", "DefParArr", "$@6", "$@7", "$@8", "DefPar", "DefParItem",
  "DefParList", "DefParams", "$@9", "BodyFunc", "$@10", "DefFunc_",
  "DefFunc", "$@11", "$@12", "$@13", "AInitialList", "$@14", "AInitial",
  "$@15", "Initializer", "$@16", "$@17", "$@18", "AInitItem", "DefAInit",
  "$@19", "$@20", "DRanges", "$@21", "DefArrD1A", "DefArrDA", "DefArr",
  "$@22", "$@23", "DefVarAssign", "$@24", "$@25", "DefVarInit", "DefVar",
  "$@26", "$@27", "DefIAV", "DefItem", "$@28", "DefType", "DefineList",
  "$@29", "Define", "$@30", "$@31", "ConditionDef", "$@32", "Condition",
  "$@33", "$@34", "ExprList", "$@35", "$@36", "Expressions", "$@37",
  "PriorAssign", "AssignList", "Assign", "QuestionList", "$@38", "$@39",
  "$@40", "Question", "OrOr", "OrOr_", "$@41", "$@42", "AndAnd", "AndAnd_",
  "$@43", "$@44", "Or", "Or_", "$@45", "$@46", "XOr", "XOr_", "$@47",
  "$@48", "And", "And_", "$@49", "$@50", "Equ", "Equ_", "$@51", "$@52",
  "Compare", "Compare_", "$@53", "$@54", "Shift", "Shift_", "$@55", "$@56",
  "Term", "Term_", "$@57", "$@58", "Factor", "Factor_", "$@59", "$@60",
  "UnaryIncDec", "$@61", "Unary", "$@62", "$@63", "$@64", "$@65",
  "Primary", "PrimaryExpr", "$@66", "$@67", "$@68", "$@69", "$@70", "$@71",
  "RangesList", "$@72", "Ranges", "$@73", "CallParams", "CompaundStmnt",
  "$@74", "$@75", "$@76", "IfStmnt_", "$@77", "IfStmnt", "$@78", "$@79",
  "ForPrefix", "ForCondition", "ForPosfix", "ForStmnt", "$@80", "$@81",
  "$@82", "$@83", "DoStmnt", "$@84", "$@85", "WhileStmnt", "$@86", "$@87",
  "GoToStmnt", "$@88", "BreakStmnt", "ContinueStmnt", "ReturnVal",
  "ReturnStmnt", "Statement", "$@89", "$@90", "DefineSemi", "ExprSemi",
  "DefExpr", "StmExprList", "$@91", "StmExpr", "$@92", "DefFAV",
  "DefinesList", "$@93", "Defines", "$@94", "ExpressionExpression", "$@95",
  "ExpressionCondition", "$@96", "ExpressionNone", "$@97",
  "ExpressionValue", "$@98", "ExpressionValueList", "$@99", YY_NULL
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
    1797,  1798,  1799,  1800,  1801,  2818,  2819,  2820,  2821,  2822,
    2823,  2824,  2825,  2826,  2827,  2828,  2829,  2830,  3073,  3074,
    3075,  3076,  3077,  3079,  3080,  3081,  3082,  3083,  3084
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    62,    63,    61,    61,    65,    66,    67,
      64,    69,    70,    71,    68,    72,    72,    73,    74,    74,
      76,    75,    77,    77,    78,    77,    79,    79,    81,    82,
      83,    80,    85,    84,    84,    87,    86,    89,    88,    90,
      91,    88,    92,    92,    94,    95,    93,    93,    97,    96,
      96,    98,    98,    99,   101,   102,   100,   104,   105,   103,
     106,   106,   108,   109,   107,   110,   110,   112,   111,   111,
     113,   113,   115,   114,   114,   117,   118,   116,   120,   119,
     119,   122,   123,   121,   121,   125,   126,   124,   124,   128,
     127,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   130,   130,   131,   133,   134,   135,   132,   132,
     136,   137,   139,   140,   138,   138,   141,   143,   144,   142,
     142,   145,   147,   148,   146,   146,   149,   151,   152,   150,
     150,   153,   155,   156,   154,   154,   157,   159,   160,   158,
     158,   161,   163,   164,   162,   162,   165,   167,   168,   166,
     166,   169,   171,   172,   170,   170,   173,   175,   176,   174,
     174,   178,   177,   177,   180,   179,   181,   179,   182,   179,
     183,   179,   179,   184,   186,   185,   187,   185,   188,   185,
     189,   185,   190,   185,   191,   185,   185,   193,   192,   192,
     195,   194,   196,   196,   198,   197,   199,   200,   197,   202,
     201,   201,   204,   205,   203,   206,   206,   206,   207,   207,
     208,   208,   210,   211,   212,   213,   209,   215,   216,   214,
     218,   219,   217,   221,   220,   222,   223,   224,   224,   225,
     227,   228,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   229,   230,   231,   231,   231,   231,   233,   232,
     232,   235,   234,   236,   236,   236,   238,   237,   237,   240,
     239,   242,   241,   244,   243,   246,   245,   248,   247,   250,
     249
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     0,     4,     0,     0,     0,     0,
       6,     0,     0,     0,     7,     1,     1,     1,     3,     0,
       0,     3,     1,     1,     0,     4,     1,     3,     0,     0,
       0,     7,     0,     4,     0,     0,     3,     0,     2,     0,
       0,     5,     1,     1,     0,     0,     4,     0,     0,     5,
       0,     1,     3,     2,     0,     0,     5,     0,     0,     4,
       1,     0,     0,     0,     4,     1,     1,     0,     3,     1,
       1,     1,     0,     4,     0,     0,     0,     5,     0,     3,
       1,     0,     0,     4,     1,     0,     0,     5,     0,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     0,     2,     0,     0,     0,     7,     0,
       2,     2,     0,     0,     5,     0,     2,     0,     0,     5,
       0,     2,     0,     0,     5,     0,     2,     0,     0,     5,
       0,     2,     0,     0,     5,     0,     2,     0,     0,     5,
       0,     2,     0,     0,     5,     0,     2,     0,     0,     5,
       0,     2,     0,     0,     5,     0,     2,     0,     0,     5,
       0,     0,     2,     0,     0,     3,     0,     3,     0,     3,
       0,     3,     2,     3,     0,     2,     0,     2,     0,     3,
       0,     3,     0,     3,     0,     2,     1,     0,     5,     0,
       0,     2,     1,     3,     0,     2,     0,     0,     5,     0,
       3,     0,     0,     0,     8,     1,     1,     1,     1,     2,
       1,     2,     0,     0,     0,     0,    10,     0,     0,     9,
       0,     0,     7,     0,     4,     2,     2,     1,     0,     3,
       0,     0,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     0,     3,
       0,     0,     2,     1,     1,     1,     0,     3,     0,     0,
       2,     0,     2,     0,     2,     0,     2,     0,     2,     0,
       2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
     259,     0,     2,   258,     1,   253,    28,    70,    71,   254,
      75,     0,   255,   256,   260,     0,     0,   242,   258,    29,
      62,    67,    54,    65,    66,    69,    76,   257,    30,    63,
       0,    55,    74,     0,    61,    68,     0,     0,    77,    20,
      26,     0,    57,    60,    64,     0,    51,    50,    47,    72,
       0,     0,    24,    22,    23,    31,    58,   265,   174,   176,
     184,   166,   164,   168,   180,   178,   182,   170,     0,   103,
     109,   115,   120,   125,   130,   135,   140,   145,   150,   155,
     160,   186,   163,     0,    53,    44,    56,    74,    27,    11,
       7,    16,    15,    17,    19,   251,     0,     0,     0,   175,
     177,   185,     0,     0,     0,     0,   190,     0,     0,    52,
      91,    92,    93,    94,    95,    99,    97,    98,    96,   100,
     101,     0,   104,   105,   110,   112,   111,   117,   116,   122,
     121,   127,   126,   132,   131,   137,   136,   142,   141,   147,
     146,   152,   151,   157,   156,   161,   172,     0,    45,    73,
       0,     0,     0,    21,     0,   261,    59,   173,   266,    89,
     167,   165,   169,   269,   192,   181,   179,   189,   183,   171,
     102,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   162,    48,     0,    12,     8,    19,    25,   196,
     244,     0,   220,     0,   217,     0,     0,     0,   267,   230,
     194,   241,   233,   236,   234,   235,   237,   238,   239,   240,
     246,   245,   247,   248,   252,     0,     0,    88,     0,     0,
     267,   191,   267,   113,   118,   123,   128,   133,   138,   143,
     148,   153,   158,    50,    39,    37,    46,    13,     9,    18,
     251,   212,     0,   202,   261,   223,   226,   225,     0,   227,
       0,     0,   195,   261,   243,   262,     0,    90,   193,   270,
       0,     0,   115,   120,   125,   130,   135,   140,   145,   150,
     155,   160,    49,    40,    38,     0,     6,     0,   261,   263,
     263,     0,     0,   229,   268,   231,   249,    85,   187,   107,
     114,   119,   124,   129,   134,   139,   144,   149,   154,   159,
       0,     6,     3,    10,   197,   205,   213,   206,   207,    81,
       0,    84,     0,     0,     0,   224,   261,    86,   189,     0,
       0,    42,    35,    43,    14,     4,   198,   263,    82,   221,
     264,   203,   218,   232,    88,   188,   108,    41,    34,     0,
     208,     0,   214,     0,   261,   261,   263,    87,     0,    36,
       5,   209,   261,    78,    80,    83,   222,   201,     0,    32,
     210,   215,     0,     0,   199,   204,     0,    34,   261,   211,
      79,   261,   219,    33,   216,   200
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   303,   325,   339,    91,   151,   238,   276,    92,
     150,   237,   275,    93,    94,   153,    50,    51,    55,    95,
      41,     9,    15,    28,    33,   349,   367,   320,   338,   321,
     274,   273,   300,   322,    86,   148,   184,    84,   233,    47,
      48,    23,    31,    36,    43,    56,    96,    44,    24,    29,
      34,    25,    26,    30,    10,    38,    87,    11,    16,    32,
     355,   363,   310,   328,   343,   257,   317,   334,   158,   217,
     121,   122,   159,   124,   171,   222,   319,    69,    70,   126,
     172,   262,    71,   128,   173,   263,    72,   130,   174,   264,
      73,   132,   175,   265,    74,   134,   176,   266,    75,   136,
     177,   267,    76,   138,   178,   268,    77,   140,   179,   269,
      78,   142,   180,   270,    79,   144,   181,   271,   146,   182,
      80,   103,   102,   104,   108,    81,    82,    99,   100,   106,
     105,   107,   101,   221,   318,   166,   167,   165,   201,   252,
     240,   326,   365,   371,   202,   280,   345,   306,   342,   361,
     203,   278,   327,   352,   368,   204,   244,   346,   205,   242,
     344,   206,   282,   207,   208,   248,   209,   210,   251,   316,
     211,   212,   213,   214,   253,   154,   155,    13,    14,    18,
       2,     3,   215,   216,   311,   312,    97,    98,   249,   250,
     218,   219
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -310
static const yytype_int16 yypact[] =
{
    -310,    15,  -310,   -11,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,    34,  -310,  -310,  -310,   -12,    -5,  -310,   -11,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
      17,  -310,    39,     1,    50,  -310,     4,    -5,  -310,  -310,
    -310,     0,  -310,  -310,  -310,    99,  -310,    47,    58,  -310,
      53,    16,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,    54,   152,
      37,    41,    42,    40,    44,    45,    43,    38,    62,    46,
      36,  -310,    49,    99,  -310,  -310,  -310,    39,  -310,  -310,
    -310,  -310,  -310,  -310,    77,  -310,    99,    87,    99,  -310,
    -310,  -310,    99,    99,    99,     3,  -310,    85,    99,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,    99,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,    91,  -310,  -310,
      57,    86,    16,  -310,   101,    -3,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,   100,  -310,  -310,
    -310,  -310,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,  -310,  -310,   -10,  -310,  -310,    77,  -310,  -310,
    -310,   103,  -310,   104,  -310,    96,   106,   113,   114,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,   115,    99,   105,   120,    99,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,    47,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,   125,  -310,    61,  -310,  -310,  -310,   121,  -310,
      99,   122,  -310,    -3,  -310,  -310,    99,  -310,  -310,  -310,
     130,   128,    41,    42,    40,    44,    45,    43,    38,    62,
      46,    36,  -310,  -310,  -310,     4,   140,   137,    12,   116,
     116,   139,   146,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
      84,   140,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
     153,  -310,    99,   154,   156,  -310,    61,  -310,   100,    99,
     158,  -310,  -310,  -310,  -310,  -310,  -310,     5,  -310,  -310,
    -310,  -310,  -310,  -310,   105,  -310,  -310,  -310,   149,    99,
    -310,   155,  -310,     7,    61,    61,   116,  -310,    84,  -310,
    -310,  -310,   157,  -310,  -310,  -310,  -310,   148,   161,  -310,
    -310,  -310,   162,   150,  -310,  -310,   159,   149,    61,  -310,
    -310,    61,  -310,  -310,  -310,  -310
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -310,  -310,  -120,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,    30,    -4,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -183,  -310,  -310,  -310,     2,
    -310,  -310,  -310,  -163,  -310,  -310,  -310,   -46,  -310,  -310,
     -87,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -309,  -310,
    -310,   160,   163,  -310,  -310,   102,  -310,  -310,  -310,  -310,
    -310,  -310,  -275,  -310,  -310,  -143,  -310,  -310,  -213,  -310,
    -310,  -310,   -45,  -310,  -310,  -310,  -310,  -127,  -310,   -69,
    -310,  -310,    22,   -68,  -310,  -310,    23,   -67,  -310,  -310,
      24,   -66,  -310,  -310,    26,   -64,  -310,  -310,    27,   -63,
    -310,  -310,    28,   -62,  -310,  -310,    29,   -61,  -310,  -310,
      31,   -58,  -310,  -310,    33,   -57,  -310,  -310,  -310,  -310,
     -95,  -310,  -310,  -310,  -310,   108,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -109,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
      -2,   -60,  -242,   -37,  -310,   -23,  -310,  -310,   201,  -310,
    -310,  -310,  -132,  -310,  -310,  -310,  -310,  -310,  -177,  -310,
    -310,  -310
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -251
static const yytype_int16 yytable[] =
{
      68,    12,   281,   255,   234,   313,   259,   160,   161,   162,
       5,   189,  -250,   169,    52,     4,    12,    39,   190,   163,
      20,    53,    45,   191,   192,   193,   340,   194,   195,   196,
     197,   198,    20,   305,   354,    21,    19,   284,   147,     6,
       7,     8,    20,   260,    22,   261,   235,   353,     7,     8,
     199,   156,   341,   200,   370,    17,    54,   309,    40,    37,
     164,    42,    46,     7,     8,    83,    22,    89,    90,    85,
      88,   358,   123,   109,   333,   189,   170,   125,   129,   127,
     137,   143,   190,   131,   135,   133,   232,   191,   192,   193,
     141,   194,   195,   196,   197,   198,   145,   152,   234,   330,
      57,    57,   356,   357,   157,   139,   185,    58,    59,    60,
     183,   186,     7,     8,   199,    57,   188,   200,   220,   241,
     243,   245,    58,    59,    60,   256,   374,   246,    61,   375,
      62,    63,    64,    65,   247,  -228,   254,   258,    66,    67,
     235,   279,   283,    61,   285,    62,    63,    64,    65,   288,
     289,   302,   304,    66,    67,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   314,   315,   309,   348,
     329,   331,   332,   337,   360,    20,   351,   364,   366,   369,
     372,   324,   187,   239,   373,   359,   236,   272,   301,   149,
      35,   347,   336,   290,   223,   291,   224,   292,   225,   293,
      49,   226,   294,   227,   295,   228,   296,   229,   297,   335,
     230,   287,   298,   231,   299,   168,   286,   277,   308,    27,
     362,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   323,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   307,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   350,     0,     0,     0,     0,     0,
       0,     0,     0,   323
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-310)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      45,     3,   244,   216,    14,   280,   219,   102,   103,   104,
      21,    14,    15,   108,    14,     0,    18,    16,    21,    16,
      25,    21,    18,    26,    27,    28,    21,    30,    31,    32,
      33,    34,    25,    21,   343,    40,    48,   250,    83,    50,
      51,    52,    25,   220,    49,   222,    56,    40,    51,    52,
      53,    96,   327,    56,   363,    21,    56,    52,    57,    20,
      57,    11,    58,    51,    52,    18,    49,    51,    52,    11,
      17,   346,    35,    19,   316,    14,   121,    36,    38,    37,
      42,    45,    21,    39,    41,    40,   181,    26,    27,    28,
      44,    30,    31,    32,    33,    34,    47,    20,    14,   312,
      16,    16,   344,   345,    17,    43,    49,    23,    24,    25,
      19,    25,    51,    52,    53,    16,    15,    56,    18,    16,
      16,    25,    23,    24,    25,    20,   368,    21,    44,   371,
      46,    47,    48,    49,    21,    21,    21,    17,    54,    55,
      56,    16,    21,    44,    22,    46,    47,    48,    49,    19,
      22,    11,    15,    54,    55,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    27,    21,    52,    20,
      17,    17,    16,    15,    17,    25,    21,    29,    17,    17,
      21,   301,   152,   187,   367,   348,   184,   233,   275,    87,
      30,   334,   319,   262,   172,   263,   173,   264,   174,   265,
      37,   175,   266,   176,   267,   177,   268,   178,   269,   318,
     179,   256,   270,   180,   271,   107,   253,   240,   278,    18,
     352,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   300,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   278,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   339,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   348
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    60,   239,   240,     0,    21,    50,    51,    52,    80,
     113,   116,   229,   236,   237,    81,   117,    21,   238,    48,
      25,    40,    49,   100,   107,   110,   111,   237,    82,   108,
     112,   101,   118,    83,   109,   110,   102,    20,   114,    16,
      57,    79,    11,   103,   106,    18,    58,    98,    99,   111,
      75,    76,    14,    21,    56,    77,   104,    16,    23,    24,
      25,    44,    46,    47,    48,    49,    54,    55,   131,   136,
     137,   141,   145,   149,   153,   157,   161,   165,   169,   173,
     179,   184,   185,    18,    96,    11,    93,   115,    17,    51,
      52,    64,    68,    72,    73,    78,   105,   245,   246,   186,
     187,   191,   181,   180,   182,   189,   188,   190,   183,    19,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   129,   130,    35,   132,    36,   138,    37,   142,    38,
     146,    39,   150,    40,   154,    41,   158,    42,   162,    43,
     166,    44,   170,    45,   174,    47,   177,   131,    94,   114,
      69,    65,    20,    74,   234,   235,   131,    17,   127,   131,
     179,   179,   179,    16,    57,   196,   194,   195,   184,   179,
     131,   133,   139,   143,   147,   151,   155,   159,   163,   167,
     171,   175,   178,    19,    95,    49,    25,    73,    15,    14,
      21,    26,    27,    28,    30,    31,    32,    33,    34,    53,
      56,   197,   203,   209,   214,   217,   220,   222,   223,   225,
     226,   229,   230,   231,   232,   241,   242,   128,   249,   250,
      18,   192,   134,   141,   145,   149,   153,   157,   161,   165,
     169,   173,   179,    97,    14,    56,    88,    70,    66,    74,
     199,    16,   218,    16,   215,    25,    21,    21,   224,   247,
     248,   227,   198,   233,    21,   127,    20,   124,    17,   127,
     247,   247,   140,   144,   148,   152,   156,   160,   164,   168,
     172,   176,    96,    90,    89,    71,    67,   234,   210,    16,
     204,   231,   221,    21,   127,    22,   232,   131,    19,    22,
     138,   142,   146,   150,   154,   158,   162,   166,   170,   174,
      91,    99,    11,    61,    15,    21,   206,   229,   230,    52,
     121,   243,   244,   121,    27,    21,   228,   125,   193,   135,
      86,    88,    92,   131,    61,    62,   200,   211,   122,    17,
     127,    17,    16,   231,   126,   192,   136,    15,    87,    63,
      21,   121,   207,   123,   219,   205,   216,   124,    20,    84,
     131,    21,   212,    40,   107,   119,   231,   231,   121,    92,
      17,   208,   241,   120,    29,   201,    17,    85,   213,    17,
     107,   202,    21,    84,   231,   231
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

    { CODE(BegParVarAssign,0); }
    break;

  case 5:

    { MAKE(ParVarAssign,0); }
    break;

  case 7:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 8:

    { SAVE((yyvsp[(3) - (3)])); }
    break;

  case 9:

    { MAKE(DefParVar,0); }
    break;

  case 11:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 12:

    { SAVE((yyvsp[(3) - (3)])); }
    break;

  case 13:

    { MAKE(DefParArr,0); }
    break;

  case 17:

    { TREE(AddToList,0); }
    break;

  case 20:

    { TREE(Define,2); }
    break;

  case 21:

    { TREE(EndParams,0); }
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

    { MAKE(BodyFunc,2); }
    break;

  case 26:

    { TREE(EndParams,2); }
    break;

  case 28:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 29:

    { SAVE((yyvsp[(3) - (3)])); }
    break;

  case 30:

    { MAKE(FuncIdent,0); }
    break;

  case 32:

    { TREE(AddToList,0); }
    break;

  case 35:

    { TREE(AddToList,0); }
    break;

  case 37:

    { CODE(BegInitial,0); }
    break;

  case 38:

    { TREE(NodeListLL,0); }
    break;

  case 39:

    { CODE(BegInitial,1); }
    break;

  case 40:

    { TREE(NodeListLL,0); }
    break;

  case 41:

    { CODE(EndInitial,0); }
    break;

  case 43:

    { CODE(AInitItem,0); }
    break;

  case 44:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 45:

    { CODE(BegAInit,0); }
    break;

  case 46:

    { MAKE(EndAInit,0); }
    break;

  case 48:

    { MAKE(DRange,0); }
    break;

  case 51:

    { MAKE(DefArrD1AEmpty,0); }
    break;

  case 52:

    { MAKE(DRange,0); }
    break;

  case 53:

    { CODE(EndRanges,0); }
    break;

  case 54:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 55:

    { MAKE(DefArray,0); }
    break;

  case 57:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 58:

    { CODE(BegDefVarAssign,0); }
    break;

  case 59:

    { MAKE(DefVarAssign,0); }
    break;

  case 62:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 63:

    { MAKE(DefIdent,0); }
    break;

  case 67:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 68:

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

  case 75:

    { MAKE(Define,0); }
    break;

  case 76:

    { TREE(AddToList,0); }
    break;

  case 77:

    { CODE(EndDefine,0); }
    break;

  case 78:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 79:

    { TREE(RefDef,0); }
    break;

  case 81:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 82:

    { MAKE(Define,0); }
    break;

  case 83:

    { MAKE(PushDef,0); }
    break;

  case 85:

    { TREE(AddToList,0); }
    break;

  case 86:

    { CODE(AddToExpr,0); }
    break;

  case 89:

    { MAKE(ExpressionsLL,0); }
    break;

  case 90:

    { CODE(ExpressionSLL,0); }
    break;

  case 91:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 92:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 93:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 94:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 95:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 96:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 97:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 98:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 99:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 100:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 101:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 102:

    { MAKE(Binary,0); }
    break;

  case 105:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 106:

    { CODE(BegQuestion,0); }
    break;

  case 107:

    { CODE(MidQuestion,0); }
    break;

  case 108:

    { MAKE(Question,0); }
    break;

  case 112:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 113:

    { MAKE(Binary,0); }
    break;

  case 117:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 118:

    { MAKE(Binary,0); }
    break;

  case 122:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 123:

    { MAKE(Binary,0); }
    break;

  case 127:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 128:

    { MAKE(Binary,0); }
    break;

  case 132:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 133:

    { MAKE(Binary,0); }
    break;

  case 137:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 138:

    { MAKE(Binary,0); }
    break;

  case 142:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 143:

    { MAKE(Binary,0); }
    break;

  case 147:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 148:

    { MAKE(Binary,0); }
    break;

  case 152:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 153:

    { MAKE(Binary,0); }
    break;

  case 157:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 158:

    { MAKE(Binary,0); }
    break;

  case 161:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 162:

    { MAKE(IncDec,0); }
    break;

  case 164:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 165:

    { MAKE(Unary,0); }
    break;

  case 166:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 167:

    { MAKE(Unary,0); }
    break;

  case 168:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 169:

    { MAKE(Unary,0); }
    break;

  case 170:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 171:

    { MAKE(Cast,0); }
    break;

  case 173:

    { TREE(Primary,0); }
    break;

  case 174:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 175:

    { MAKE(Number,0); }
    break;

  case 176:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 177:

    { MAKE(Number,0); }
    break;

  case 178:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 180:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 182:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 183:

    { MAKE(Cast,0); }
    break;

  case 184:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 185:

    { MAKE(Ident,0); }
    break;

  case 187:

    { MAKE(IndexLL,0); }
    break;

  case 190:

    { MAKE(BegIndexLL,0); }
    break;

  case 191:

    { MAKE(EndIndex,0); }
    break;

  case 192:

    { MAKE(Params,0); }
    break;

  case 193:

    { MAKE(Params,1); }
    break;

  case 194:

    { MAKE(Compaund,0); }
    break;

  case 195:

    { CODE(EndBlock,0); }
    break;

  case 196:

    { MAKE(Compaund,0); }
    break;

  case 197:

    { CODE(EndBlock,0); }
    break;

  case 198:

    { TREE(AddToList,0); }
    break;

  case 199:

    { CODE(Else,0); }
    break;

  case 200:

    { MAKE(If,1); }
    break;

  case 201:

    { MAKE(If,0); }
    break;

  case 202:

    { CODE(BegIf,0); }
    break;

  case 203:

    { CODE(Then,0); }
    break;

  case 205:

    { TREE(NodeNull,0); }
    break;

  case 208:

    { MAKE(NodeNull,0); }
    break;

  case 210:

    { TREE(NodeNull,0); }
    break;

  case 212:

    { MAKE(BegFor,0); }
    break;

  case 213:

    { CODE(PrefFor,0); }
    break;

  case 214:

    { CODE(ConditionFor,0); }
    break;

  case 215:

    { CODE(PostFor,0); }
    break;

  case 216:

    { MAKE(For,0); }
    break;

  case 217:

    { MAKE(BegDo,0); }
    break;

  case 218:

    { CODE(MidDo,0); }
    break;

  case 219:

    { MAKE(Do,0); }
    break;

  case 220:

    { MAKE(BegWhile,0); }
    break;

  case 221:

    { CODE(MidWhile,0); }
    break;

  case 222:

    { MAKE(While,0); }
    break;

  case 223:

    { SAVE((yyvsp[(2) - (2)])); }
    break;

  case 224:

    { MAKE(GoTo,0); }
    break;

  case 225:

    { MAKE(Break,0); }
    break;

  case 226:

    { MAKE(Continue,0); }
    break;

  case 227:

    { MAKE(Return,1); }
    break;

  case 228:

    { MAKE(Return,0); }
    break;

  case 230:

    { SAVE((yyvsp[(1) - (1)])); }
    break;

  case 231:

    { CODE(Label,0); }
    break;

  case 232:

    { TREE(Label,0); }
    break;

  case 244:

    { TREE(NodeNull,0); }
    break;

  case 248:

    { TREE(AddToList,0); }
    break;

  case 251:

    { MAKE(BegStmExprLL,0); }
    break;

  case 252:

    { CODE(EndBlock,0); }
    break;

  case 253:

    { TREE(NodeNull,0); }
    break;

  case 256:

    { TREE(AddToList,0); }
    break;

  case 259:

    { MAKE(BegStmExprLL,0); }
    break;

  case 260:

    { CODE(EndBlock,0); }
    break;

  case 261:

    { CODE(Part,16); }
    break;

  case 262:

    { TREE(ExpressionSLL,16); }
    break;

  case 263:

    { CODE(Part,241); }
    break;

  case 264:

    { TREE(ExpressionSLL,241); }
    break;

  case 265:

    { CODE(Part,0); }
    break;

  case 266:

    { TREE(ExpressionSLL,0); }
    break;

  case 267:

    { CODE(Part,256); }
    break;

  case 268:

    { TREE(ExpressionSLL,256); }
    break;

  case 269:

    { CODE(Part,512); }
    break;

  case 270:

    { TREE(ExpressionSLL,512); }
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




