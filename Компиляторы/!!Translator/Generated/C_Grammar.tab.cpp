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
#define yyparse         yy_C_parse
#define yylex           yy_C_lex
#define yyerror         yy_C_error
#define yylval          yy_C_lval
#define yychar          yy_C_char
#define yydebug         yy_C_debug
#define yynerrs         yy_C_nerrs

/* Copy the first part of user declarations.  */



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
extern int yy_C_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 1536,
     CONSTANT = 768,
     STRING_LITERAL = 1280,
     INC_OP = 278,
     DEC_OP = 279,
     LEFT_OP = 286,
     RIGHT_OP = 287,
     LE_OP = 283,
     GE_OP = 285,
     EQ_OP = 280,
     NE_OP = 281,
     AND_OP = 274,
     OR_OP = 273,
     MUL_ASSIGN = 264,
     DIV_ASSIGN = 265,
     MOD_ASSIGN = 266,
     ADD_ASSIGN = 262,
     SUB_ASSIGN = 263,
     LEFT_ASSIGN = 288,
     RIGHT_ASSIGN = 289,
     AND_ASSIGN = 267,
     XOR_ASSIGN = 269,
     OR_ASSIGN = 268,
     ELLIPSIS = 564,
     PTR_OP = 563,
     TYPEDEF = 1825,
     EXTERN = 1820,
     STATIC = 1817,
     AUTO = 1818,
     REGISTER = 1821,
     CHAR = 1819,
     SHORT = 1810,
     INT = 1811,
     LONG = 1812,
     SIGNED = 1822,
     UNSIGNED = 1827,
     FLOAT = 1813,
     DOUBLE = 1814,
     CONST = 1816,
     VOLATILE = 1828,
     VOID = 1809,
     STRUCT = 1824,
     UNION = 1826,
     ENUM = 1807,
     SIZEOF = 1823,
     CASE = 1803,
     DEFAULT = 1808,
     IF = 1795,
     ELSE = 1796,
     SWITCH = 1802,
     WHILE = 1794,
     DO = 1797,
     FOR = 1793,
     GOTO = 1798,
     CONTINUE = 1799,
     BREAK = 1800,
     RETURN = 1801,
     TYPE_NAME = 1815
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
int yy_C_parse (void *YYPARSE_PARAM);
#else
int yy_C_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yy_C_parse (void);
#else
int yy_C_parse ();
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
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1326

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  214
/* YYNRULES -- Number of states.  */
#define YYNSTATES  352

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   1829

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,     2,     2,     2,    74,    67,     2,
      61,    62,    68,    69,    66,    70,    65,    73,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    80,    82,
      75,    81,    76,    79,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    63,     2,    64,    77,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    83,    78,    84,    71,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,    19,    20,    16,    17,    18,    23,    25,    24,
       2,     2,     2,    15,    14,     2,     2,     2,     6,     7,
      12,    13,     2,    10,     2,    11,     8,     9,    21,    22,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,    26,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       5,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,    53,    50,    51,    54,    56,    57,
      58,    59,    52,    48,     2,     2,     2,    46,    49,    43,
      34,    35,    36,    39,    40,    60,    41,    30,    31,    33,
      29,    32,    37,    47,    44,    28,    45,    38,    42,     2
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    20,
      22,    27,    31,    36,    40,    44,    47,    50,    52,    56,
      58,    61,    64,    67,    70,    75,    77,    79,    81,    83,
      85,    87,    89,    94,    96,   100,   104,   108,   110,   114,
     118,   120,   124,   128,   130,   134,   138,   142,   146,   148,
     152,   156,   158,   162,   164,   168,   170,   174,   176,   180,
     182,   186,   188,   194,   196,   200,   202,   204,   206,   208,
     210,   212,   214,   216,   218,   220,   222,   224,   228,   230,
     233,   237,   239,   242,   244,   247,   249,   252,   254,   258,
     260,   264,   266,   268,   270,   272,   274,   276,   278,   280,
     282,   284,   286,   288,   290,   292,   294,   296,   298,   304,
     309,   312,   314,   316,   318,   321,   325,   328,   330,   333,
     335,   337,   341,   343,   346,   350,   355,   361,   364,   366,
     370,   372,   376,   378,   380,   383,   385,   387,   391,   396,
     400,   405,   410,   414,   416,   419,   422,   426,   428,   431,
     433,   437,   439,   443,   446,   449,   451,   453,   457,   459,
     462,   464,   466,   469,   473,   476,   480,   484,   489,   492,
     496,   500,   505,   507,   511,   516,   518,   522,   524,   526,
     528,   530,   532,   534,   538,   543,   547,   549,   552,   556,
     560,   565,   567,   570,   572,   575,   577,   580,   586,   594,
     600,   606,   614,   621,   629,   633,   636,   639,   642,   646,
     648,   650,   655,   659,   663
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      86,     0,    -1,    87,    -1,   149,    -1,    87,   149,    -1,
       3,    -1,     4,    -1,     5,    -1,    61,   107,    62,    -1,
      88,    -1,    89,    63,   107,    64,    -1,    89,    61,    62,
      -1,    89,    61,    90,    62,    -1,    89,    65,     3,    -1,
      89,    27,     3,    -1,    89,     6,    -1,    89,     7,    -1,
     105,    -1,    90,    66,   105,    -1,    89,    -1,     6,    91,
      -1,     7,    91,    -1,    92,    93,    -1,    47,    91,    -1,
      47,    61,   134,    62,    -1,    67,    -1,    68,    -1,    69,
      -1,    70,    -1,    71,    -1,    72,    -1,    91,    -1,    61,
     134,    62,    93,    -1,    93,    -1,    94,    68,    93,    -1,
      94,    73,    93,    -1,    94,    74,    93,    -1,    94,    -1,
      95,    69,    94,    -1,    95,    70,    94,    -1,    95,    -1,
      96,     8,    95,    -1,    96,     9,    95,    -1,    96,    -1,
      97,    75,    96,    -1,    97,    76,    96,    -1,    97,    10,
      96,    -1,    97,    11,    96,    -1,    97,    -1,    98,    12,
      97,    -1,    98,    13,    97,    -1,    98,    -1,    99,    67,
      98,    -1,    99,    -1,   100,    77,    99,    -1,   100,    -1,
     101,    78,   100,    -1,   101,    -1,   102,    14,   101,    -1,
     102,    -1,   103,    15,   102,    -1,   103,    -1,   103,    79,
     107,    80,   104,    -1,   104,    -1,    91,   106,   105,    -1,
      81,    -1,    16,    -1,    17,    -1,    18,    -1,    19,    -1,
      20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,
      25,    -1,   105,    -1,   107,    66,   105,    -1,   104,    -1,
     110,    82,    -1,   110,   111,    82,    -1,   113,    -1,   113,
     110,    -1,   114,    -1,   114,   110,    -1,   125,    -1,   125,
     110,    -1,   112,    -1,   111,    66,   112,    -1,   126,    -1,
     126,    81,   137,    -1,    28,    -1,    29,    -1,    30,    -1,
      31,    -1,    32,    -1,    43,    -1,    33,    -1,    34,    -1,
      35,    -1,    36,    -1,    39,    -1,    40,    -1,    37,    -1,
      38,    -1,   115,    -1,   122,    -1,    60,    -1,   116,     3,
      83,   117,    84,    -1,   116,    83,   117,    84,    -1,   116,
       3,    -1,    44,    -1,    45,    -1,   118,    -1,   117,   118,
      -1,   119,   120,    82,    -1,   114,   119,    -1,   114,    -1,
     125,   119,    -1,   125,    -1,   121,    -1,   120,    66,   121,
      -1,   126,    -1,    80,   108,    -1,   126,    80,   108,    -1,
      46,    83,   123,    84,    -1,    46,     3,    83,   123,    84,
      -1,    46,     3,    -1,   124,    -1,   123,    66,   124,    -1,
       3,    -1,     3,    81,   108,    -1,    41,    -1,    42,    -1,
     128,   127,    -1,   127,    -1,     3,    -1,    61,   126,    62,
      -1,   127,    63,   108,    64,    -1,   127,    63,    64,    -1,
     127,    61,   130,    62,    -1,   127,    61,   133,    62,    -1,
     127,    61,    62,    -1,    68,    -1,    68,   129,    -1,    68,
     128,    -1,    68,   129,   128,    -1,   125,    -1,   129,   125,
      -1,   131,    -1,   131,    66,    26,    -1,   132,    -1,   131,
      66,   132,    -1,   110,   126,    -1,   110,   135,    -1,   110,
      -1,     3,    -1,   133,    66,     3,    -1,   119,    -1,   119,
     135,    -1,   128,    -1,   136,    -1,   128,   136,    -1,    61,
     135,    62,    -1,    63,    64,    -1,    63,   108,    64,    -1,
     136,    63,    64,    -1,   136,    63,   108,    64,    -1,    61,
      62,    -1,    61,   130,    62,    -1,   136,    61,    62,    -1,
     136,    61,   130,    62,    -1,   105,    -1,    83,   138,    84,
      -1,    83,   138,    66,    84,    -1,   137,    -1,   138,    66,
     137,    -1,   140,    -1,   141,    -1,   145,    -1,   146,    -1,
     147,    -1,   148,    -1,     3,    80,   139,    -1,    48,   108,
      80,   139,    -1,    49,    80,   139,    -1,   142,    -1,    83,
      84,    -1,    83,   144,    84,    -1,    83,   143,    84,    -1,
      83,   143,   144,    84,    -1,   109,    -1,   143,   109,    -1,
     139,    -1,   144,   139,    -1,    82,    -1,   107,    82,    -1,
      50,    61,   107,    62,   139,    -1,    50,    61,   107,    62,
     139,    51,   139,    -1,    52,    61,   107,    62,   139,    -1,
      53,    61,   107,    62,   139,    -1,    54,   139,    53,    61,
     107,    62,    82,    -1,    55,    61,   145,   145,    62,   139,
      -1,    55,    61,   145,   145,   107,    62,   139,    -1,    56,
       3,    82,    -1,    57,    82,    -1,    58,    82,    -1,    59,
      82,    -1,    59,   107,    82,    -1,   150,    -1,   109,    -1,
     110,   126,   143,   141,    -1,   110,   126,   141,    -1,   126,
     143,   141,    -1,   126,   141,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    75,    75,    79,    80,    84,    85,    86,    87,    91,
      92,    93,    94,    95,    96,    97,    98,   102,   103,   107,
     108,   109,   110,   111,   112,   116,   117,   118,   119,   120,
     121,   125,   126,   130,   131,   132,   133,   137,   138,   139,
     143,   144,   145,   149,   150,   151,   152,   153,   157,   158,
     159,   163,   164,   168,   169,   173,   174,   178,   179,   183,
     184,   188,   189,   193,   194,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   212,   213,   217,   221,
     222,   226,   227,   228,   229,   230,   231,   235,   236,   240,
     241,   245,   246,   247,   248,   249,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   268,   269,
     270,   274,   275,   279,   280,   284,   288,   289,   290,   291,
     295,   296,   300,   301,   302,   306,   307,   308,   312,   313,
     317,   318,   322,   323,   327,   328,   332,   333,   334,   335,
     336,   337,   338,   342,   343,   344,   345,   349,   350,   354,
     355,   359,   360,   364,   365,   366,   370,   371,   375,   376,
     380,   381,   382,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   398,   399,   400,   404,   405,   409,   410,   411,
     412,   413,   414,   418,   419,   420,   424,   428,   429,   430,
     431,   435,   436,   440,   441,   445,   446,   450,   451,   452,
     456,   457,   458,   459,   463,   464,   465,   466,   467,   471,
     472,   476,   477,   478,   479
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT",
  "STRING_LITERAL", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP",
  "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "ELLIPSIS", "PTR_OP", "TYPEDEF",
  "EXTERN", "STATIC", "AUTO", "REGISTER", "CHAR", "SHORT", "INT", "LONG",
  "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "CONST", "VOLATILE", "VOID",
  "STRUCT", "UNION", "ENUM", "SIZEOF", "CASE", "DEFAULT", "IF", "ELSE",
  "SWITCH", "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN",
  "TYPE_NAME", "'('", "')'", "'['", "']'", "'.'", "','", "'&'", "'*'",
  "'+'", "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'",
  "'?'", "':'", "'='", "';'", "'{'", "'}'", "$accept", "translation_start",
  "translation_unit", "primary_expression", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "statement", "labeled_statement",
  "compound_statement", "compound_statement_type_name", "declaration_list",
  "statement_list", "expression_statement", "selection_statement",
  "iteration_statement", "jump_statement", "external_declaration",
  "function_definition", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,  1829,  1536,   768,  1280,   278,   279,   286,   287,
     283,   285,   280,   281,   274,   273,   264,   265,   266,   262,
     263,   288,   289,   267,   269,   268,   564,   563,  1825,  1820,
    1817,  1818,  1821,  1819,  1810,  1811,  1812,  1822,  1827,  1813,
    1814,  1816,  1828,  1809,  1824,  1826,  1807,  1823,  1803,  1808,
    1795,  1796,  1802,  1794,  1797,  1793,  1798,  1799,  1800,  1801,
    1815,    40,    41,    91,    93,    46,    44,    38,    42,    43,
      45,   126,    33,    47,    37,    60,    62,    94,   124,    63,
      58,    61,    59,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    88,    88,    88,    88,    89,
      89,    89,    89,    89,    89,    89,    89,    90,    90,    91,
      91,    91,    91,    91,    91,    92,    92,    92,    92,    92,
      92,    93,    93,    94,    94,    94,    94,    95,    95,    95,
      96,    96,    96,    97,    97,    97,    97,    97,    98,    98,
      98,    99,    99,   100,   100,   101,   101,   102,   102,   103,
     103,   104,   104,   105,   105,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   107,   107,   108,   109,
     109,   110,   110,   110,   110,   110,   110,   111,   111,   112,
     112,   113,   113,   113,   113,   113,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   115,   115,
     115,   116,   116,   117,   117,   118,   119,   119,   119,   119,
     120,   120,   121,   121,   121,   122,   122,   122,   123,   123,
     124,   124,   125,   125,   126,   126,   127,   127,   127,   127,
     127,   127,   127,   128,   128,   128,   128,   129,   129,   130,
     130,   131,   131,   132,   132,   132,   133,   133,   134,   134,
     135,   135,   135,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   137,   137,   137,   138,   138,   139,   139,   139,
     139,   139,   139,   140,   140,   140,   141,   142,   142,   142,
     142,   143,   143,   144,   144,   145,   145,   146,   146,   146,
     147,   147,   147,   147,   148,   148,   148,   148,   148,   149,
     149,   150,   150,   150,   150
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     3,     1,
       4,     3,     4,     3,     3,     2,     2,     1,     3,     1,
       2,     2,     2,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     4,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     5,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     2,
       3,     1,     2,     1,     2,     1,     2,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     4,
       2,     1,     1,     1,     2,     3,     2,     1,     2,     1,
       1,     3,     1,     2,     3,     4,     5,     2,     1,     3,
       1,     3,     1,     1,     2,     1,     1,     3,     4,     3,
       4,     4,     3,     1,     2,     2,     3,     1,     2,     1,
       3,     1,     3,     2,     2,     1,     1,     3,     1,     2,
       1,     1,     2,     3,     2,     3,     3,     4,     2,     3,
       3,     4,     1,     3,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     4,     3,     1,     2,     3,     3,
       4,     1,     2,     1,     2,     1,     2,     5,     7,     5,
       5,     7,     6,     7,     3,     2,     2,     2,     3,     1,
       1,     4,     3,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   136,    91,    92,    93,    94,    95,    97,    98,    99,
     100,   103,   104,   101,   102,   132,   133,    96,   111,   112,
       0,   107,     0,   143,     0,     2,   210,     0,    81,    83,
     105,     0,   106,    85,     0,   135,     0,     3,   209,   127,
       0,     0,   147,   145,   144,     1,     4,    79,     0,    87,
      89,    82,    84,   110,     0,    86,     0,   191,     0,   214,
     186,     0,     0,     0,   134,     0,   130,     0,   128,   137,
     148,   146,     0,    80,     0,   212,     0,     0,   117,     0,
     113,     0,   119,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    25,    26,    27,    28,    29,    30,   195,   187,     9,
      19,    31,     0,    33,    37,    40,    43,    48,    51,    53,
      55,    57,    59,    61,    63,    76,     0,   193,   177,   178,
       0,     0,   179,   180,   181,   182,    89,   192,   213,   156,
     142,   155,     0,   149,   151,     0,     5,   139,    31,    78,
       0,     0,     0,     0,   125,    88,     0,   172,    90,   211,
       0,   116,   109,   114,     0,     0,   120,   122,   118,     0,
       0,    20,    21,     0,    23,     0,     0,     0,     0,     0,
       0,     0,     0,   205,   206,   207,     0,     0,   158,     0,
      15,    16,     0,     0,     0,     0,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    65,     0,    22,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   196,
     189,     0,   188,   194,     0,     0,   153,   160,   154,   161,
     140,     0,   141,     0,   138,   126,   131,   129,   175,     0,
     108,   123,     0,   115,     0,   183,     0,     0,   185,     0,
       0,     0,     0,     0,   204,   208,     8,     0,   160,   159,
       0,    14,    11,     0,    17,     0,    13,    64,    34,    35,
      36,    38,    39,    41,    42,    46,    47,    44,    45,    49,
      50,    52,    54,    56,    58,    60,     0,    77,   190,   168,
       0,     0,   164,     0,   162,     0,     0,   150,   152,   157,
       0,   173,   121,   124,    24,   184,     0,     0,     0,     0,
       0,    32,    12,     0,    10,     0,   169,   163,   165,   170,
       0,   166,     0,   174,   176,   197,   199,   200,     0,     0,
       0,    18,    62,   171,   167,     0,     0,   202,     0,   198,
     201,   203
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,   109,   110,   273,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   207,   126,   150,    57,    58,    48,    49,    28,    29,
      30,    31,    79,    80,    81,   165,   166,    32,    67,    68,
      33,    34,    35,    36,    44,   300,   143,   144,   145,   189,
     301,   239,   158,   249,   127,   128,   129,    60,    61,   131,
     132,   133,   134,   135,    37,    38
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -223
static const yytype_int16 yypact[] =
{
     928,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
       9,  -223,    55,    -2,    48,   928,  -223,    50,  1238,  1238,
    -223,    16,  -223,  1238,  1040,    92,    13,  -223,  -223,   -63,
      66,    21,  -223,  -223,    -2,  -223,  -223,  -223,   -14,  -223,
    1007,  -223,  -223,    19,  1266,  -223,   278,  -223,    50,  -223,
    -223,  1040,   972,   660,    92,    66,    -3,   -42,  -223,  -223,
    -223,  -223,    55,  -223,   536,  -223,  1040,  1266,  1266,  1068,
    -223,    54,  1266,    49,  -223,  -223,   780,   780,   813,   839,
      53,    86,    89,   118,   504,   145,   209,   138,   163,   563,
     648,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
     187,   276,   839,  -223,   -24,   155,   218,    61,   217,   179,
     174,   175,   202,     8,  -223,  -223,    -5,  -223,  -223,  -223,
     337,   396,  -223,  -223,  -223,  -223,   177,  -223,  -223,  -223,
    -223,    23,   193,   190,  -223,    83,  -223,  -223,  -223,  -223,
     196,   -21,   839,    66,  -223,  -223,   536,  -223,  -223,  -223,
    1096,  -223,  -223,  -223,   839,    32,  -223,   182,  -223,   504,
     839,  -223,  -223,   648,  -223,   183,   504,   839,   839,   839,
     211,   589,   189,  -223,  -223,  -223,    60,    90,    78,   207,
    -223,  -223,   269,   693,   839,   275,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,   839,  -223,   839,
     839,   839,   839,   839,   839,   839,   839,   839,   839,   839,
     839,   839,   839,   839,   839,   839,   839,   839,   839,  -223,
    -223,   434,  -223,  -223,   884,   730,  -223,    64,  -223,   126,
    -223,  1170,  -223,   277,  -223,  -223,  -223,  -223,  -223,   -19,
    -223,  -223,    54,  -223,   839,  -223,   224,   504,  -223,   122,
     124,   130,   226,   589,  -223,  -223,  -223,  1129,   158,  -223,
     839,  -223,  -223,   137,  -223,   134,  -223,  -223,  -223,  -223,
    -223,   -24,   -24,   155,   155,   218,   218,   218,   218,    61,
      61,   217,   179,   174,   175,   202,   -10,  -223,  -223,  -223,
     227,   228,  -223,   215,   126,  1203,   742,  -223,  -223,  -223,
     466,  -223,  -223,  -223,  -223,  -223,   504,   504,   504,   839,
     768,  -223,  -223,   839,  -223,   839,  -223,  -223,  -223,  -223,
     240,  -223,   239,  -223,  -223,   237,  -223,  -223,   139,   504,
     149,  -223,  -223,  -223,  -223,   504,   247,  -223,   504,  -223,
    -223,  -223
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -223,  -223,  -223,  -223,  -223,  -223,   -52,  -223,   -90,    20,
      25,    58,    22,   129,   132,   128,   133,   127,  -223,   -59,
     -53,  -223,   -97,   -57,    18,     0,  -223,   282,  -223,   131,
    -223,  -223,   279,   -72,   -69,  -223,   107,  -223,   298,   235,
      31,   -17,   -30,    -6,  -223,   -61,  -223,   123,  -223,   238,
     -82,  -222,  -129,  -223,   -80,  -223,    67,  -223,    88,   280,
    -173,  -223,  -223,  -223,   387,  -223
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      27,   142,   186,   187,   149,    41,    64,   163,   263,   161,
      50,   148,    39,   168,   180,   304,     1,    43,    26,    53,
      65,   157,   208,   226,   153,    27,     1,   248,    51,    52,
     149,   188,   175,    55,   171,   172,   174,   148,    71,    15,
      16,   136,   154,    26,   209,   153,   304,   310,    45,   210,
     211,   233,    72,     1,    42,   136,   228,     1,     1,   238,
     148,   228,   141,   245,   167,   311,    23,     1,    73,    66,
     325,   216,   217,   187,    22,    70,   187,   229,   152,   137,
     259,   260,   261,    69,   234,    82,   235,   227,   163,   255,
     320,    23,    40,   149,   137,   246,   258,   275,   252,    54,
     148,    59,    77,   157,   188,   149,   269,   251,    82,    82,
      82,    22,   148,    82,   253,    22,    22,    75,    23,   278,
     279,   280,    23,    23,   236,   234,   228,   235,   138,   169,
     296,    82,    47,   176,   164,   237,   218,   219,    76,   267,
     274,   235,   265,   159,   130,   242,    23,   177,   137,   243,
     178,   233,   266,    62,   277,    63,   228,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   297,   149,   315,   303,   179,
     321,   334,   268,   148,   316,    78,   317,   305,   228,   306,
     228,    82,   318,   190,   191,   149,   228,   313,   324,   322,
     228,   346,   148,   323,    82,   228,   181,    64,    78,    78,
      78,   348,   182,    78,   192,   228,   225,    41,   148,   267,
     183,   235,   338,   340,   212,   213,   214,   215,   237,   220,
     221,    78,   281,   282,   141,   167,   335,   336,   337,   283,
     284,   141,   289,   290,   330,   184,   222,   149,   193,   332,
     194,   223,   195,   224,   148,   240,   241,   157,    74,   347,
     244,   268,   254,   257,   262,   349,   342,   141,   351,   270,
     341,   264,   271,   148,   285,   286,   287,   288,   276,   328,
     309,    83,    84,    85,    86,    87,   314,   319,   345,   326,
     327,    78,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   343,   344,    78,   141,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    88,    89,    90,    91,   350,
      92,    93,    94,    95,    96,    97,    98,    99,    21,   100,
      83,    84,    85,    86,    87,   101,   102,   103,   104,   105,
     106,   291,   293,   295,   155,   292,   160,   206,   294,   312,
     107,    56,   108,   151,   308,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    88,    89,    90,    91,   247,    92,
      93,    94,    95,    96,    97,    98,    99,    21,   100,    83,
      84,    85,    86,    87,   101,   102,   103,   104,   105,   106,
     231,   256,    46,     0,     0,     0,     0,     0,     0,   107,
      56,   230,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,    84,    85,
      86,    87,     0,    88,    89,    90,    91,     0,    92,    93,
      94,    95,    96,    97,    98,    99,     0,   100,     0,     0,
       0,     0,     0,   101,   102,   103,   104,   105,   106,   146,
      84,    85,    86,    87,     0,     0,     0,     0,   107,    56,
     232,    88,    89,    90,    91,     0,    92,    93,    94,    95,
      96,    97,    98,    99,     0,   100,     0,     0,     0,     0,
       0,   101,   102,   103,   104,   105,   106,    83,    84,    85,
      86,    87,     0,    88,     0,     0,   107,    56,   298,     0,
       0,     0,     0,     0,     0,     0,     0,   100,     0,     0,
       0,     0,     0,   101,   102,   103,   104,   105,   106,   146,
      84,    85,    86,    87,     0,     0,     0,     0,     0,   156,
     333,    88,    89,    90,    91,     0,    92,    93,    94,    95,
      96,    97,    98,    99,     0,   100,   146,    84,    85,    86,
      87,   101,   102,   103,   104,   105,   106,     0,     0,     0,
       0,     0,     0,    88,     0,     0,   107,    56,     0,     0,
       0,     0,   146,    84,    85,    86,    87,   100,     0,     0,
       0,     0,     0,   101,   102,   103,   104,   105,   106,     0,
      88,     0,     0,     0,     0,     0,     0,     0,     0,   156,
       0,     0,     0,     0,   100,     0,     0,     0,     0,     0,
     101,   102,   103,   104,   105,   106,    88,     0,     0,     0,
       0,     0,     0,     0,     0,   185,     0,     0,     0,     0,
     100,   146,    84,    85,    86,    87,   101,   102,   103,   104,
     105,   106,     0,   146,    84,    85,    86,    87,     0,     0,
       0,   107,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    88,   146,    84,    85,    86,
      87,     0,     0,     0,     0,     0,     0,    88,    21,   100,
       0,     0,     0,     0,     0,   101,   102,   103,   104,   105,
     106,   100,     0,     0,   147,     0,     0,   101,   102,   103,
     104,   105,   106,   146,    84,    85,    86,    87,     0,     0,
      88,     0,     0,     0,     0,   146,    84,    85,    86,    87,
       0,     0,     0,     0,   100,   272,     0,     0,     0,     0,
     101,   102,   103,   104,   105,   106,     0,     0,     0,     0,
       0,   146,    84,    85,    86,    87,     0,    88,     0,     0,
       0,     0,     0,   146,    84,    85,    86,    87,     0,    88,
       0,   100,     0,     0,   302,     0,     0,   101,   102,   103,
     104,   105,   106,   100,     0,     0,   331,     0,     0,   101,
     102,   103,   104,   105,   106,    88,   146,    84,    85,    86,
      87,     0,     0,     0,     0,     0,     0,    88,     0,   100,
     339,     0,     0,     0,     0,   101,   102,   103,   104,   105,
     106,   170,   146,    84,    85,    86,    87,   101,   102,   103,
     104,   105,   106,     0,     0,     0,     0,     0,     0,     0,
      88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,     0,     0,     0,     0,     0,
     101,   102,   103,   104,   105,   106,    88,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     100,     0,     0,     0,     0,     0,   101,   102,   103,   104,
     105,   106,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,   234,   299,   235,     0,     0,
       0,     0,    23,     0,     0,     0,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,   139,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
       0,     0,     0,     0,     0,     0,    23,     0,     0,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,     0,   140,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,     0,    74,     0,
      56,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,     0,     0,     0,     0,     0,
       0,     0,     0,    56,     0,     0,     0,     0,    21,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   162,     0,     0,     0,    21,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,     0,     0,     0,     0,
     250,     0,     0,     0,     0,     0,     0,     0,     0,    21,
     267,   299,   235,     0,     0,     0,   307,    23,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,   329,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-223)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    62,    99,   100,    63,    22,    36,    79,   181,    78,
      27,    63,     3,    82,    94,   237,     3,    23,     0,     3,
      83,    74,   112,    15,    66,    25,     3,   156,    28,    29,
      89,   100,    89,    33,    86,    87,    88,    89,    44,    41,
      42,    58,    84,    25,    68,    66,   268,    66,     0,    73,
      74,   131,    66,     3,    23,    72,    66,     3,     3,   141,
     112,    66,    62,    84,    81,    84,    68,     3,    82,     3,
      80,    10,    11,   170,    61,    44,   173,    82,    81,    61,
     177,   178,   179,    62,    61,    54,    63,    79,   160,   169,
     263,    68,    83,   152,    76,   152,   176,   194,    66,    83,
     152,    34,    83,   156,   173,   164,   188,   164,    77,    78,
      79,    61,   164,    82,    82,    61,    61,    50,    68,   209,
     210,   211,    68,    68,   141,    61,    66,    63,    61,    80,
     227,   100,    82,    80,    80,   141,    75,    76,    50,    61,
     193,    63,    82,    76,    56,    62,    68,    61,   130,    66,
      61,   231,    62,    61,   207,    63,    66,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   228,   235,   257,   235,    61,
     270,   310,   188,   235,    62,    54,    62,    61,    66,    63,
      66,   160,    62,     6,     7,   254,    66,   254,    64,    62,
      66,    62,   254,    66,   173,    66,    61,   237,    77,    78,
      79,    62,     3,    82,    27,    66,    14,   234,   270,    61,
      82,    63,   319,   320,    69,    70,     8,     9,   234,    12,
      13,   100,   212,   213,   234,   252,   316,   317,   318,   214,
     215,   241,   220,   221,   305,    82,    67,   306,    61,   306,
      63,    77,    65,    78,   306,    62,    66,   310,    81,   339,
      64,   267,    80,    80,    53,   345,   325,   267,   348,    62,
     323,    82,     3,   325,   216,   217,   218,   219,     3,    64,
       3,     3,     4,     5,     6,     7,    62,    61,    51,    62,
      62,   160,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    62,    64,   173,   305,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    82,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
       3,     4,     5,     6,     7,    67,    68,    69,    70,    71,
      72,   222,   224,   226,    72,   223,    77,    81,   225,   252,
      82,    83,    84,    65,   241,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,   153,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,     3,
       4,     5,     6,     7,    67,    68,    69,    70,    71,    72,
     130,   173,    25,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,    -1,    47,    48,    49,    50,    -1,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    82,    83,
      84,    47,    48,    49,    50,    -1,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    72,     3,     4,     5,
       6,     7,    -1,    47,    -1,    -1,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    83,
      84,    47,    48,    49,    50,    -1,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    61,     3,     4,     5,     6,
       7,    67,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    82,    83,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,    61,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,
      61,     3,     4,     5,     6,     7,    67,    68,    69,    70,
      71,    72,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    -1,    47,    60,    61,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    61,    -1,    -1,    64,    -1,    -1,    67,    68,    69,
      70,    71,    72,     3,     4,     5,     6,     7,    -1,    -1,
      47,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,    -1,    47,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,    47,
      -1,    61,    -1,    -1,    64,    -1,    -1,    67,    68,    69,
      70,    71,    72,    61,    -1,    -1,    64,    -1,    -1,    67,
      68,    69,    70,    71,    72,    47,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    61,     3,     4,     5,     6,     7,    67,    68,    69,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    47,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    -1,    62,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    81,    -1,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    60,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    -1,    60,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    -1,    -1,    -1,    26,    68,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    62,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    60,    61,    68,    86,    87,   109,   110,   113,   114,
     115,   116,   122,   125,   126,   127,   128,   149,   150,     3,
      83,   126,   125,   128,   129,     0,   149,    82,   111,   112,
     126,   110,   110,     3,    83,   110,    83,   109,   110,   141,
     142,   143,    61,    63,   127,    83,     3,   123,   124,    62,
     125,   128,    66,    82,    81,   141,   143,    83,   114,   117,
     118,   119,   125,     3,     4,     5,     6,     7,    47,    48,
      49,    50,    52,    53,    54,    55,    56,    57,    58,    59,
      61,    67,    68,    69,    70,    71,    72,    82,    84,    88,
      89,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   107,   139,   140,   141,
     143,   144,   145,   146,   147,   148,   126,   109,   141,     3,
      62,   110,   130,   131,   132,   133,     3,    64,    91,   104,
     108,   123,    81,    66,    84,   112,    83,   105,   137,   141,
     117,   119,    84,   118,    80,   120,   121,   126,   119,    80,
      61,    91,    91,    61,    91,   108,    80,    61,    61,    61,
     139,    61,     3,    82,    82,    82,   107,   107,   119,   134,
       6,     7,    27,    61,    63,    65,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    81,   106,    93,    68,
      73,    74,    69,    70,     8,     9,    10,    11,    75,    76,
      12,    13,    67,    77,    78,    14,    15,    79,    66,    82,
      84,   144,    84,   139,    61,    63,   126,   128,   135,   136,
      62,    66,    62,    66,    64,    84,   108,   124,   137,   138,
      84,   108,    66,    82,    80,   139,   134,    80,   139,   107,
     107,   107,    53,   145,    82,    82,    62,    61,   128,   135,
      62,     3,    62,    90,   105,   107,     3,   105,    93,    93,
      93,    94,    94,    95,    95,    96,    96,    96,    96,    97,
      97,    98,    99,   100,   101,   102,   107,   105,    84,    62,
     130,   135,    64,   108,   136,    61,    63,    26,   132,     3,
      66,    84,   121,   108,    62,   139,    62,    62,    62,    61,
     145,    93,    62,    66,    64,    80,    62,    62,    64,    62,
     130,    64,   108,    84,   137,   139,   139,   139,   107,    62,
     107,   105,   104,    62,    64,    51,    62,   139,    62,   139,
      82,   139
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




