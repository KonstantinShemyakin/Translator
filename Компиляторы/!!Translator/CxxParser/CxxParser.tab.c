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


#include "CxxParsing.hxx"
using namespace std;



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
   by #include "CxxParser.tab.h".  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5060

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  129
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  211
/* YYNRULES -- Number of rules.  */
#define YYNRULES  561
/* YYNRULES -- Number of states.  */
#define YYNSTATES  899

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   353

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    12,    26,   128,    29,     7,     9,    25,
      21,    22,     5,     3,    31,     4,    24,     6,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    16,    30,
      13,    15,    14,    23,    28,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    17,    27,    18,     8,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    19,    10,    20,    11,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    15,    20,    24,    26,
      28,    30,    33,    36,    38,    41,    43,    46,    49,    52,
      54,    56,    59,    61,    64,    67,    69,    72,    74,    76,
      78,    80,    83,    88,    91,    94,    96,    99,   101,   104,
     106,   108,   110,   112,   114,   116,   118,   120,   122,   124,
     126,   128,   130,   132,   136,   139,   142,   146,   147,   149,
     154,   163,   171,   177,   182,   186,   190,   194,   198,   201,
     204,   212,   220,   228,   236,   239,   240,   242,   244,   248,
     250,   253,   256,   259,   263,   266,   269,   272,   275,   278,
     280,   283,   285,   288,   291,   295,   300,   303,   308,   311,
     314,   317,   320,   322,   326,   331,   332,   336,   338,   341,
     343,   347,   351,   353,   357,   361,   365,   367,   371,   375,
     377,   381,   385,   387,   391,   395,   399,   403,   405,   409,
     413,   415,   419,   421,   425,   427,   431,   433,   437,   439,
     443,   445,   451,   453,   457,   461,   463,   465,   467,   469,
     471,   473,   475,   477,   479,   481,   483,   485,   486,   488,
     490,   494,   496,   498,   502,   506,   510,   512,   516,   520,
     522,   526,   528,   532,   534,   538,   540,   544,   546,   550,
     552,   558,   560,   564,   566,   568,   572,   574,   578,   581,
     583,   587,   590,   592,   594,   596,   598,   600,   602,   604,
     606,   610,   615,   619,   623,   631,   632,   635,   642,   648,
     656,   662,   663,   665,   667,   673,   681,   690,   692,   695,
     698,   702,   706,   708,   713,   723,   724,   728,   736,   739,
     741,   745,   748,   750,   752,   754,   756,   758,   760,   762,
     765,   767,   769,   771,   773,   775,   777,   780,   782,   785,
     788,   791,   793,   796,   799,   801,   804,   806,   808,   811,
     813,   816,   818,   821,   823,   825,   828,   830,   833,   835,
     838,   842,   845,   847,   849,   851,   853,   855,   857,   859,
     862,   864,   866,   868,   870,   872,   874,   876,   878,   880,
     882,   884,   886,   888,   890,   893,   895,   897,   899,   901,
     903,   905,   907,   909,   911,   913,   915,   917,   919,   921,
     923,   926,   929,   933,   936,   939,   943,   948,   950,   954,
     956,   960,   961,   965,   967,   971,   974,   976,   980,   982,
     986,   989,   995,   999,  1004,  1009,  1015,  1019,  1023,  1027,
    1031,  1033,  1035,  1038,  1040,  1043,  1045,  1047,  1050,  1052,
    1055,  1056,  1059,  1060,  1063,  1065,  1067,  1070,  1073,  1074,
    1077,  1079,  1080,  1082,  1085,  1089,  1094,  1097,  1101,  1105,
    1106,  1108,  1111,  1113,  1117,  1119,  1123,  1125,  1128,  1132,
    1134,  1138,  1140,  1142,  1144,  1147,  1149,  1151,  1155,  1158,
    1160,  1163,  1167,  1169,  1171,  1174,  1177,  1180,  1183,  1186,
    1189,  1191,  1195,  1199,  1202,  1204,  1206,  1208,  1212,  1217,
    1220,  1227,  1236,  1238,  1242,  1245,  1247,  1251,  1254,  1256,
    1259,  1264,  1270,  1275,  1279,  1282,  1284,  1286,  1288,  1292,
    1301,  1302,  1306,  1314,  1317,  1319,  1323,  1326,  1328,  1330,
    1332,  1334,  1336,  1338,  1341,  1344,  1347,  1350,  1354,  1358,
    1362,  1364,  1366,  1369,  1373,  1376,  1378,  1384,  1386,  1390,
    1392,  1396,  1398,  1401,  1404,  1406,  1408,  1410,  1413,  1416,
    1419,  1420,  1422,  1425,  1430,  1432,  1435,  1438,  1443,  1448,
    1450,  1453,  1455,  1457,  1459,  1461,  1463,  1465,  1467,  1469,
    1471,  1473,  1475,  1477,  1479,  1481,  1483,  1485,  1487,  1489,
    1491,  1493,  1495,  1497,  1499,  1501,  1503,  1505,  1507,  1509,
    1511,  1513,  1515,  1517,  1519,  1521,  1523,  1525,  1527,  1529,
    1532,  1535,  1538,  1541,  1546,  1548,  1552,  1554,  1558,  1560,
    1564,  1566,  1569,  1571,  1573,  1576,  1580,  1586,  1589,  1591,
    1595,  1597,  1602,  1606,  1608,  1611,  1617,  1619,  1621,  1624,
    1626,  1629,  1633,  1638,  1640,  1644,  1646,  1647,  1648,  1649,
    1650,  1651
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     150,     0,    -1,   122,    -1,   130,    -1,   131,    -1,   131,
     133,     3,   322,    14,    -1,   131,   133,     3,    14,    -1,
     131,   133,     4,    -1,   321,    -1,    13,    -1,    56,    -1,
      88,   134,    -1,   132,    56,    -1,   132,    -1,   135,   136,
      -1,   136,    -1,   134,   136,    -1,    11,   132,    -1,    88,
     138,    -1,   305,    -1,   313,    -1,    88,   139,    -1,   139,
      -1,   135,   138,    -1,   135,   140,    -1,   140,    -1,   134,
     140,    -1,   137,    -1,   141,    -1,   138,    -1,   233,    -1,
     143,   233,    -1,   143,    56,    11,   143,    -1,    11,   143,
      -1,    88,   144,    -1,   144,    -1,   135,   145,    -1,   145,
      -1,   134,   146,    -1,   125,    -1,   123,    -1,   120,    -1,
     121,    -1,   147,    -1,   149,    -1,   103,    -1,   116,    -1,
     209,    -1,   148,    -1,   114,    -1,   223,    -1,   152,    -1,
     264,    -1,    17,   180,    18,    -1,    88,   264,    -1,   267,
      30,    -1,   153,   267,    30,    -1,    -1,   151,    -1,   155,
     264,   154,     4,    -1,   155,   264,   154,     3,   153,   335,
      19,     1,    -1,   155,   264,   154,     3,   153,   335,     1,
      -1,   155,   264,   154,     3,     1,    -1,   155,    17,   180,
      18,    -1,   155,    24,   142,    -1,   155,    24,   146,    -1,
     155,    32,   142,    -1,   155,    32,   146,    -1,   155,    37,
      -1,   155,    34,    -1,   101,    13,   260,    14,    21,   181,
      22,    -1,   112,    13,   260,    14,    21,   181,    22,    -1,
     109,    13,   260,    14,    21,   181,    22,    -1,    96,    13,
     260,    14,    21,   181,    22,    -1,   118,   265,    -1,    -1,
     157,    -1,   178,    -1,   157,    31,   178,    -1,   155,    -1,
      37,   165,    -1,    34,   165,    -1,   255,   165,    -1,   224,
     253,   165,    -1,     3,   165,    -1,     4,   165,    -1,    12,
     165,    -1,    11,   165,    -1,   111,   158,    -1,   160,    -1,
     134,   160,    -1,   159,    -1,   134,   159,    -1,    99,   165,
      -1,   107,   161,   164,    -1,   107,   265,   161,   164,    -1,
     107,   265,    -1,   107,   265,   265,   164,    -1,   230,   257,
      -1,   230,   162,    -1,   230,   161,    -1,   255,   162,    -1,
     163,    -1,    17,   181,    18,    -1,   163,    17,   182,    18,
      -1,    -1,    21,   156,    22,    -1,   158,    -1,   152,   165,
      -1,   165,    -1,   166,    54,   165,    -1,   166,    33,   165,
      -1,   166,    -1,   167,   253,   166,    -1,   167,     6,   166,
      -1,   167,     7,   166,    -1,   167,    -1,   168,     3,   167,
      -1,   168,     4,   167,    -1,   168,    -1,   169,    42,   168,
      -1,   169,    43,   168,    -1,   169,    -1,   170,    13,   169,
      -1,   170,    14,   169,    -1,   170,    38,   169,    -1,   170,
      36,   169,    -1,   170,    -1,   171,    35,   170,    -1,   171,
      41,   170,    -1,   171,    -1,   172,     9,   171,    -1,   172,
      -1,   173,     8,   172,    -1,   173,    -1,   174,    10,   173,
      -1,   174,    -1,   175,    39,   174,    -1,   175,    -1,   176,
      40,   175,    -1,   176,    -1,   176,    23,   181,    16,   178,
      -1,   177,    -1,   176,   179,   178,    -1,   176,    15,   282,
      -1,   329,    -1,    15,    -1,    44,    -1,    45,    -1,    46,
      -1,    47,    -1,    48,    -1,    49,    -1,    50,    -1,    51,
      -1,    52,    -1,    53,    -1,    -1,   181,    -1,   178,    -1,
     157,    31,   178,    -1,   177,    -1,   169,    -1,   183,    13,
     169,    -1,   183,    38,   169,    -1,   183,    36,   169,    -1,
     183,    -1,   184,    35,   183,    -1,   184,    41,   183,    -1,
     184,    -1,   185,     9,   184,    -1,   185,    -1,   186,     8,
     185,    -1,   186,    -1,   187,    10,   186,    -1,   187,    -1,
     188,    39,   187,    -1,   188,    -1,   189,    40,   188,    -1,
     189,    -1,   189,    23,   192,    16,   191,    -1,   190,    -1,
     189,   179,   191,    -1,   330,    -1,   191,    -1,   193,    31,
     191,    -1,   191,    -1,   193,    31,   191,    -1,   337,   195,
      -1,   196,    -1,   333,     3,   195,    -1,   333,     4,    -1,
     197,    -1,   199,    -1,   207,    -1,   325,    -1,   198,    -1,
     201,    -1,   204,    -1,   206,    -1,   130,    16,   194,    -1,
      94,   182,    16,   194,    -1,    98,    16,   194,    -1,    19,
     200,    20,    -1,    19,   200,   194,   128,   334,     1,    20,
      -1,    -1,   200,   194,    -1,   200,   194,   128,   334,     1,
      30,    -1,   106,    21,   203,    22,   194,    -1,   106,    21,
     203,    22,   194,   102,   194,    -1,   113,    21,   203,    22,
     194,    -1,    -1,   203,    -1,   267,    -1,   119,    21,   203,
      22,   194,    -1,   100,   194,   119,    21,   181,    22,    30,
      -1,   104,    21,   205,   202,    30,   180,    22,   194,    -1,
     216,    -1,    93,    30,    -1,    97,    30,    -1,   110,   180,
      30,    -1,   105,   131,    30,    -1,   214,    -1,    19,   336,
     209,    20,    -1,    19,   336,   209,   339,   210,   128,   334,
       1,    20,    -1,    -1,   209,   339,   210,    -1,   209,   339,
     210,   128,   334,     1,    30,    -1,   338,   211,    -1,   212,
      -1,   333,     3,   211,    -1,   333,     4,    -1,   214,    -1,
     274,    -1,   315,    -1,   324,    -1,   213,    -1,   250,    -1,
     245,    -1,    88,   213,    -1,   216,    -1,   215,    -1,   249,
      -1,   246,    -1,   247,    -1,   248,    -1,    88,   215,    -1,
      30,    -1,   252,    30,    -1,   251,    30,    -1,   227,   216,
      -1,   233,    -1,   217,   233,    -1,   217,   226,    -1,   217,
      -1,    88,   218,    -1,   137,    -1,   231,    -1,   219,   226,
      -1,   219,    -1,   219,   217,    -1,   220,    -1,   221,   220,
      -1,   141,    -1,   221,    -1,   221,   141,    -1,   218,    -1,
     218,   222,    -1,   222,    -1,   221,    56,    -1,   218,   221,
      56,    -1,   218,    56,    -1,   228,    -1,   229,    -1,    83,
      -1,    89,    -1,   259,    -1,   225,    -1,   225,    -1,    88,
     227,    -1,    86,    -1,    87,    -1,    85,    -1,    82,    -1,
      79,    -1,    80,    -1,    84,    -1,    91,    -1,   232,    -1,
     231,    -1,   259,    -1,   290,    -1,   236,    -1,   234,    -1,
      88,   231,    -1,   137,    -1,   233,    -1,    61,    -1,    70,
      -1,    60,    -1,    66,    -1,    64,    -1,    65,    -1,    67,
      -1,    68,    -1,    63,    -1,    62,    -1,    69,    -1,   287,
      -1,   235,    -1,    75,   137,    -1,    72,   137,    -1,    72,
     137,   237,    -1,    72,   237,    -1,    19,   238,    -1,    19,
     242,   238,    -1,    19,   242,    31,   239,    -1,    20,    -1,
     334,     1,    20,    -1,    20,    -1,   334,     1,    20,    -1,
      -1,   334,     1,    31,    -1,   240,    -1,   242,    31,   240,
      -1,   241,   243,    -1,   244,    -1,   244,    15,   182,    -1,
     131,    -1,    73,   137,   208,    -1,    73,   208,    -1,    73,
     137,    15,   137,    30,    -1,    90,   142,    30,    -1,    90,
      75,   142,    30,    -1,    90,    73,   137,    30,    -1,    92,
      21,   147,    22,    30,    -1,    82,   147,   210,    -1,    82,
     147,   208,    -1,   178,    31,   252,    -1,   251,    31,   252,
      -1,   178,    -1,     5,    -1,   253,   259,    -1,   253,    -1,
     135,   254,    -1,     9,    -1,   254,    -1,   134,   254,    -1,
     255,    -1,   255,   256,    -1,    -1,   255,   257,    -1,    -1,
     258,   259,    -1,    77,    -1,    78,    -1,   230,   261,    -1,
     230,   260,    -1,    -1,   255,   261,    -1,   263,    -1,    -1,
     263,    -1,   262,   264,    -1,   262,    17,    18,    -1,   262,
      17,   182,    18,    -1,   265,   258,    -1,   265,   258,   331,
      -1,    21,   266,    22,    -1,    -1,   267,    -1,   267,    55,
      -1,   271,    -1,   267,    31,   271,    -1,   256,    -1,   167,
     253,   257,    -1,   268,    -1,   172,     9,    -1,   172,     9,
     268,    -1,   269,    -1,   269,    15,   178,    -1,    55,    -1,
     178,    -1,   270,    -1,   227,   271,    -1,   191,    -1,   273,
      -1,   273,    15,   191,    -1,   227,   272,    -1,   268,    -1,
     185,     9,    -1,   185,     9,   268,    -1,   276,    -1,   275,
      -1,   178,   278,    -1,   178,   280,    -1,   227,   275,    -1,
     277,   278,    -1,   277,   280,    -1,   227,   276,    -1,   301,
      -1,   277,    31,   178,    -1,   117,   279,   326,    -1,   307,
     280,    -1,   199,    -1,   178,    -1,   282,    -1,    19,   283,
      20,    -1,    19,   283,    31,    20,    -1,    19,    20,    -1,
      19,   284,   128,   334,     1,    20,    -1,    19,   283,    31,
     284,   128,   334,     1,    20,    -1,   284,    -1,   283,    31,
     284,    -1,   337,   285,    -1,   281,    -1,   333,     3,   285,
      -1,   333,     4,    -1,    16,    -1,   289,   137,    -1,   289,
     137,   286,     1,    -1,   289,   137,   286,   302,    19,    -1,
     289,    16,   302,    19,    -1,   289,   137,    19,    -1,   289,
      19,    -1,    71,    -1,    74,    -1,    76,    -1,   288,   291,
      20,    -1,   288,   291,   339,   292,   128,   334,     1,    20,
      -1,    -1,   291,   339,   292,    -1,   291,   339,   292,   128,
     334,     1,    30,    -1,   337,   293,    -1,   294,    -1,   333,
       3,   293,    -1,   333,     4,    -1,   298,    -1,   295,    -1,
     274,    -1,   247,    -1,   315,    -1,    30,    -1,   178,    30,
      -1,   277,    30,    -1,   296,    30,    -1,   227,   295,    -1,
     178,    31,   297,    -1,   277,    31,   301,    -1,   296,    31,
     297,    -1,   178,    -1,   301,    -1,   304,    16,    -1,   178,
      16,   300,    -1,    16,   300,    -1,   176,    -1,   176,    23,
     300,    16,   300,    -1,   299,    -1,   299,    15,   281,    -1,
     303,    -1,   302,    31,   303,    -1,   137,    -1,   304,   303,
      -1,    91,   303,    -1,    57,    -1,    58,    -1,    59,    -1,
     108,   306,    -1,   230,   257,    -1,   230,   306,    -1,    -1,
     308,    -1,    16,   309,    -1,    16,   309,   334,     1,    -1,
     311,    -1,   310,   311,    -1,   309,    31,    -1,   309,   334,
       1,    31,    -1,   312,    21,   156,    22,    -1,   137,    -1,
     108,   314,    -1,   107,    -1,    99,    -1,     3,    -1,     4,
      -1,     5,    -1,     6,    -1,     7,    -1,     8,    -1,     9,
      -1,    10,    -1,    11,    -1,    12,    -1,    15,    -1,    13,
      -1,    14,    -1,    44,    -1,    52,    -1,    48,    -1,    46,
      -1,    47,    -1,    53,    -1,    45,    -1,    49,    -1,    42,
      -1,    43,    -1,    51,    -1,    50,    -1,    35,    -1,    41,
      -1,    38,    -1,    36,    -1,    39,    -1,    40,    -1,    37,
      -1,    34,    -1,    31,    -1,    33,    -1,    32,    -1,    21,
      22,    -1,    17,    18,    -1,   316,   212,    -1,    81,   315,
      -1,    88,    13,   317,    14,    -1,   318,    -1,   317,    31,
     318,    -1,   319,    -1,   319,    15,   260,    -1,   320,    -1,
     320,    15,   131,    -1,   272,    -1,   334,     1,    -1,    71,
      -1,    75,    -1,   316,    71,    -1,   316,    71,   131,    -1,
      88,   131,    13,   322,    14,    -1,    88,   321,    -1,   323,
      -1,   322,    31,   323,    -1,   272,    -1,    88,    13,    14,
     212,    -1,   117,   199,   326,    -1,   327,    -1,   327,   326,
      -1,    95,    21,   328,    22,   199,    -1,   271,    -1,   115,
      -1,   115,   178,    -1,   115,    -1,   115,   191,    -1,   115,
      21,    22,    -1,   115,    21,   332,    22,    -1,   260,    -1,
     332,    31,   260,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   304,   304,   305,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   326,   327,   328,   329,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   348,   349,   350,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   376,
     379,   380,   381,   382,   383,   384,   385,   390,   422,   423,
     424,   428,   434,   435,   436,   443,   444,   445,   446,   448,
     449,   451,   453,   455,   459,   461,   462,   464,   465,   466,
     467,   468,   469,   470,   471,   474,   475,   476,   477,   479,
     480,   481,   482,   487,   489,   490,   491,   492,   493,   495,
     496,   497,   498,   502,   504,   505,   506,   508,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   525,   526,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   567,   568,   569,   570,   571,   571,   571,   571,
     571,   571,   571,   571,   571,   571,   571,   576,   577,   578,
     579,   580,   584,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   594,   596,   597,   599,   600,   602,   603,   605,
     606,   608,   609,   611,   612,   613,   615,   616,   623,   624,
     625,   626,   627,   629,   630,   631,   632,   633,   634,   635,
     636,   637,   638,   640,   641,   642,   643,   644,   648,   649,
     650,   651,   652,   653,   656,   657,   658,   660,   662,   663,
     664,   665,   666,   671,   672,   674,   675,   676,   677,   678,
     679,   680,   681,   682,   683,   685,   686,   687,   688,   689,
     690,   691,   692,   693,   694,   695,   696,   697,   698,   699,
     700,   715,   716,   717,   718,   719,   720,   721,   722,   723,
     724,   725,   726,   727,   728,   729,   730,   731,   732,   733,
     734,   735,   737,   738,   739,   740,   741,   743,   745,   746,
     748,   748,   748,   749,   750,   752,   753,   754,   756,   757,
     758,   760,   761,   762,   763,   764,   765,   766,   766,   766,
     766,   766,   766,   766,   766,   766,   766,   766,   777,   778,
     779,   781,   782,   783,   784,   785,   786,   787,   788,   789,
     790,   791,   792,   793,   794,   795,   796,   797,   798,   800,
     801,   802,   804,   805,   807,   808,   809,   810,   816,   817,
     818,   825,   826,   827,   828,   829,   830,   831,   832,   833,
     835,   836,   838,   839,   840,   840,   843,   844,   847,   848,
     849,   850,   851,   852,   853,   854,   857,   858,   859,   861,
     862,   863,   864,   865,   872,   873,   874,   875,   876,   877,
     878,   879,   880,   881,   882,   886,   887,   888,   890,   891,
     892,   893,   899,   900,   901,   902,   903,   904,   905,   906,
     907,   908,   909,   910,   911,   918,   919,   920,   921,   922,
     923,   924,   926,   927,   928,   929,   930,   931,   946,   947,
     948,   949,   950,   951,   952,   953,   953,   953,   954,   955,
     957,   958,   959,   961,   962,   963,   964,   965,   966,   967,
     970,   971,   978,   979,   980,   981,   982,   983,   984,   985,
     986,   989,   990,   991,   992,   993,   995,   996,   997,  1003,
    1004,  1005,  1006,  1007,  1008,  1008,  1008,  1013,  1014,  1015,
    1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,  1032,
    1037,  1047,  1048,  1053,  1054,  1055,  1056,  1057,  1058,  1059,
    1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,  1068,  1069,
    1070,  1071,  1072,  1073,  1074,  1075,  1076,  1077,  1078,  1079,
    1080,  1081,  1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,
    1090,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,  1103,
    1104,  1105,  1106,  1108,  1110,  1111,  1112,  1113,  1117,  1118,
    1119,  1129,  1134,  1136,  1137,  1138,  1139,  1141,  1142,  1143,
    1144,  1145,  1146,  1147,  1148,  1153,  1154,  1155,  1156,  1157,
    1158,  1159
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'",
  "'&'", "'|'", "'~'", "'!'", "'<'", "'>'", "'='", "':'", "'['", "']'",
  "'{'", "'}'", "'('", "')'", "'?'", "'.'", "'\\''", "'\"'", "'\\\\'",
  "'@'", "'$'", "';'", "','", "ARROW", "ARROW_STAR", "DEC", "EQ", "GE",
  "INC", "LE", "LOG_AND", "LOG_OR", "NE", "SHL", "SHR", "ASS_ADD",
  "ASS_AND", "ASS_DIV", "ASS_MOD", "ASS_MUL", "ASS_OR", "ASS_SHL",
  "ASS_SHR", "ASS_SUB", "ASS_XOR", "DOT_STAR", "ELLIPSIS", "SCOPE",
  "PRIVATE", "PROTECTED", "PUBLIC", "BOOL", "CHAR", "DOUBLE", "FLOAT",
  "INT", "LONG", "SHORT", "SIGNED", "UNSIGNED", "VOID", "WCHAR_T", "CLASS",
  "ENUM", "NAMESPACE", "STRUCT", "TYPENAME", "UNION", "CONST", "VOLATILE",
  "AUTO", "EXPLICIT", "EXPORT", "EXTERN", "FRIEND", "INLINE", "MUTABLE",
  "REGISTER", "STATIC", "TEMPLATE", "TYPEDEF", "USING", "VIRTUAL", "ASM",
  "BREAK", "CASE", "CATCH", "CONST_CAST", "CONTINUE", "DEFAULT", "DELETE",
  "DO", "DYNAMIC_CAST", "ELSE", "FALSE", "FOR", "GOTO", "IF", "NEW",
  "OPERATOR", "REINTERPRET_CAST", "RETURN", "SIZEOF", "STATIC_CAST",
  "SWITCH", "THIS", "THROW", "TRUE", "TRY", "TYPEID", "WHILE",
  "CharacterLiteral", "FloatingLiteral", "Identifier", "IntegerLiteral",
  "NumberLiteral", "StringLiteral", "SHIFT_THERE", "REDUCE_HERE_MOSTLY",
  "'#'", "$accept", "identifier_word", "identifier", "id", "template_test",
  "global_scope", "id_scope", "nested_id", "scoped_id", "destructor_id",
  "special_function_id", "nested_special_function_id",
  "scoped_special_function_id", "declarator_id", "built_in_type_id",
  "pseudo_destructor_id", "nested_pseudo_destructor_id",
  "scoped_pseudo_destructor_id", "string", "literal", "boolean_literal",
  "translation_unit", "primary_expression", "abstract_expression",
  "type1_parameters", "mark_type1", "postfix_expression",
  "expression_list.opt", "expression_list", "unary_expression",
  "delete_expression", "new_expression", "new_type_id", "new_declarator",
  "direct_new_declarator", "new_initializer.opt", "cast_expression",
  "pm_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression.opt", "expression", "constant_expression",
  "templated_relational_expression", "templated_equality_expression",
  "templated_and_expression", "templated_exclusive_or_expression",
  "templated_inclusive_or_expression", "templated_logical_and_expression",
  "templated_logical_or_expression", "templated_conditional_expression",
  "templated_assignment_expression", "templated_expression",
  "templated_expression_list", "looping_statement", "looped_statement",
  "statement", "control_statement", "labeled_statement",
  "compound_statement", "statement_seq.opt", "selection_statement",
  "condition.opt", "condition", "iteration_statement",
  "for_init_statement", "jump_statement", "declaration_statement",
  "compound_declaration", "declaration_seq.opt", "looping_declaration",
  "looped_declaration", "declaration", "specialised_declaration",
  "block_declaration", "specialised_block_declaration",
  "simple_declaration", "suffix_built_in_decl_specifier.raw",
  "suffix_built_in_decl_specifier", "suffix_named_decl_specifier",
  "suffix_named_decl_specifier.bi", "suffix_named_decl_specifiers",
  "suffix_named_decl_specifiers.sf", "suffix_decl_specified_ids",
  "suffix_decl_specified_scope", "decl_specifier_affix",
  "decl_specifier_suffix", "decl_specifier_prefix",
  "storage_class_specifier", "function_specifier", "type_specifier",
  "elaborate_type_specifier", "simple_type_specifier",
  "built_in_type_specifier", "elaborated_type_specifier",
  "elaborated_enum_specifier", "enum_specifier", "enumerator_clause",
  "enumerator_list_ecarb", "enumerator_definition_ecarb",
  "enumerator_definition_filler", "enumerator_list_head",
  "enumerator_list", "enumerator_definition", "enumerator",
  "namespace_definition", "namespace_alias_definition",
  "using_declaration", "using_directive", "asm_definition",
  "linkage_specification", "init_declarations", "init_declaration",
  "star_ptr_operator", "nested_ptr_operator", "ptr_operator",
  "ptr_operator_seq", "ptr_operator_seq.opt", "cv_qualifier_seq.opt",
  "cv_qualifier", "type_id", "abstract_declarator.opt",
  "direct_abstract_declarator.opt", "direct_abstract_declarator",
  "parenthesis_clause", "parameters_clause",
  "parameter_declaration_clause", "parameter_declaration_list",
  "abstract_pointer_declaration", "abstract_parameter_declaration",
  "special_parameter_declaration", "parameter_declaration",
  "templated_parameter_declaration", "templated_abstract_declaration",
  "function_definition", "func_definition", "ctor_definition",
  "constructor_head", "function_try_block", "function_block",
  "function_body", "initializer_clause", "braced_initializer",
  "initializer_list", "looping_initializer_clause",
  "looped_initializer_clause", "colon_mark", "elaborated_class_specifier",
  "class_specifier_head", "class_key", "class_specifier",
  "member_specification.opt", "looping_member_declaration",
  "looped_member_declaration", "member_declaration",
  "simple_member_declaration", "member_init_declarations",
  "member_init_declaration", "accessibility_specifier",
  "bit_field_declaration", "bit_field_width", "bit_field_init_declaration",
  "base_specifier_list", "base_specifier", "access_specifier",
  "conversion_function_id", "conversion_type_id", "ctor_initializer.opt",
  "ctor_initializer", "mem_initializer_list", "mem_initializer_list_head",
  "mem_initializer", "mem_initializer_id", "operator_function_id",
  "operator", "template_declaration", "template_parameter_clause",
  "template_parameter_list", "template_parameter", "simple_type_parameter",
  "templated_type_parameter", "template_id", "template_argument_list",
  "template_argument", "explicit_specialization", "try_block",
  "handler_seq", "handler", "exception_declaration", "throw_expression",
  "templated_throw_expression", "exception_specification", "type_id_list",
  "advance_search", "bang", "mark", "nest", "start_search",
  "start_search1", "util", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    43,    45,    42,    47,    37,    94,    38,
     124,   126,    33,    60,    62,    61,    58,    91,    93,   123,
     125,    40,    41,    63,    46,    39,    34,    92,    64,    36,
      59,    44,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,    35
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   129,   130,   131,   132,   132,   132,   132,   132,   133,
     134,   134,   135,   136,   136,   137,   137,   138,   138,   139,
     139,   139,   140,   140,   140,   141,   141,   142,   142,   142,
     143,   143,   144,   144,   144,   145,   145,   146,   146,   147,
     148,   148,   148,   148,   148,   149,   149,   150,   151,   151,
     151,   151,   152,   152,   152,   153,   153,   154,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   156,   156,   157,   157,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   159,   160,   160,   160,   160,   161,   161,
     161,   162,   162,   163,   163,   164,   164,   165,   165,   166,
     166,   166,   167,   167,   167,   167,   168,   168,   168,   169,
     169,   169,   170,   170,   170,   170,   170,   171,   171,   171,
     172,   172,   173,   173,   174,   174,   175,   175,   176,   176,
     177,   177,   178,   178,   178,   178,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   180,   180,   181,
     181,   182,   183,   183,   183,   183,   184,   184,   184,   185,
     185,   186,   186,   187,   187,   188,   188,   189,   189,   190,
     190,   191,   191,   191,   192,   192,   193,   193,   194,   195,
     195,   195,   196,   196,   196,   196,   197,   197,   197,   197,
     198,   198,   198,   199,   199,   200,   200,   200,   201,   201,
     201,   202,   202,   203,   204,   204,   204,   205,   206,   206,
     206,   206,   207,   208,   208,   209,   209,   209,   210,   211,
     211,   211,   212,   212,   212,   212,   212,   213,   213,   213,
     214,   214,   215,   215,   215,   215,   215,   216,   216,   216,
     216,   217,   217,   217,   218,   218,   219,   219,   219,   220,
     220,   221,   221,   222,   222,   222,   223,   223,   223,   224,
     224,   224,   225,   225,   225,   225,   225,   226,   227,   227,
     228,   228,   228,   228,   228,   229,   229,   229,   230,   230,
     230,   231,   231,   231,   231,   232,   232,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   234,   234,
     234,   235,   236,   236,   237,   237,   237,   238,   238,   239,
     239,   240,   240,   241,   241,   242,   243,   243,   244,   245,
     245,   246,   247,   247,   248,   249,   250,   250,   251,   251,
     252,   253,   253,   254,   254,   255,   255,   255,   256,   256,
     257,   257,   258,   258,   259,   259,   260,   260,   261,   261,
     261,   262,   262,   263,   263,   263,   264,   264,   265,   266,
     266,   266,   267,   267,   268,   268,   269,   269,   269,   270,
     270,   270,   271,   271,   271,   272,   272,   272,   272,   273,
     273,   273,   274,   274,   275,   275,   275,   276,   276,   276,
     277,   277,   278,   279,   280,   281,   281,   282,   282,   282,
     282,   282,   283,   283,   284,   285,   285,   285,   286,   287,
     287,   288,   288,   288,   288,   289,   289,   289,   290,   290,
     291,   291,   291,   292,   293,   293,   293,   294,   294,   294,
     294,   294,   295,   295,   295,   295,   295,   296,   296,   296,
     297,   297,   298,   299,   299,   300,   300,   301,   301,   302,
     302,   303,   303,   303,   304,   304,   304,   305,   306,   306,
     307,   307,   308,   308,   309,   309,   310,   310,   311,   312,
     313,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   315,   315,   316,   317,   317,   318,   318,   318,   318,
     318,   318,   319,   319,   320,   320,   321,   321,   322,   322,
     323,   324,   325,   326,   326,   327,   328,   329,   329,   330,
     330,   331,   331,   332,   332,   333,   334,   335,   336,   337,
     338,   339
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     5,     4,     3,     1,     1,
       1,     2,     2,     1,     2,     1,     2,     2,     2,     1,
       1,     2,     1,     2,     2,     1,     2,     1,     1,     1,
       1,     2,     4,     2,     2,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     2,     3,     0,     1,     4,
       8,     7,     5,     4,     3,     3,     3,     3,     2,     2,
       7,     7,     7,     7,     2,     0,     1,     1,     3,     1,
       2,     2,     2,     3,     2,     2,     2,     2,     2,     1,
       2,     1,     2,     2,     3,     4,     2,     4,     2,     2,
       2,     2,     1,     3,     4,     0,     3,     1,     2,     1,
       3,     3,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     5,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       3,     1,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     1,     1,     3,     1,     3,     2,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     3,     7,     0,     2,     6,     5,     7,
       5,     0,     1,     1,     5,     7,     8,     1,     2,     2,
       3,     3,     1,     4,     9,     0,     3,     7,     2,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     2,
       2,     1,     2,     2,     1,     2,     1,     1,     2,     1,
       2,     1,     2,     1,     1,     2,     1,     2,     1,     2,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     2,     2,     3,     4,     1,     3,     1,
       3,     0,     3,     1,     3,     2,     1,     3,     1,     3,
       2,     5,     3,     4,     4,     5,     3,     3,     3,     3,
       1,     1,     2,     1,     2,     1,     1,     2,     1,     2,
       0,     2,     0,     2,     1,     1,     2,     2,     0,     2,
       1,     0,     1,     2,     3,     4,     2,     3,     3,     0,
       1,     2,     1,     3,     1,     3,     1,     2,     3,     1,
       3,     1,     1,     1,     2,     1,     1,     3,     2,     1,
       2,     3,     1,     1,     2,     2,     2,     2,     2,     2,
       1,     3,     3,     2,     1,     1,     1,     3,     4,     2,
       6,     8,     1,     3,     2,     1,     3,     2,     1,     2,
       4,     5,     4,     3,     2,     1,     1,     1,     3,     8,
       0,     3,     7,     2,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     3,     3,     3,
       1,     1,     2,     3,     2,     1,     5,     1,     3,     1,
       3,     1,     2,     2,     1,     1,     1,     2,     2,     2,
       0,     1,     2,     4,     1,     2,     2,     4,     4,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     4,     1,     3,     1,     3,     1,     3,
       1,     2,     1,     1,     2,     3,     5,     2,     1,     3,
       1,     4,     3,     1,     2,     5,     1,     1,     2,     1,
       2,     3,     4,     1,     3,     1,     0,     0,     0,     0,
       0,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
     225,     0,   561,     1,   560,   226,     0,   556,   555,     0,
       0,   341,   345,     0,     0,     0,   157,   369,   247,     0,
       0,    10,   299,   297,   306,   305,   301,   302,   300,   303,
     304,   307,   298,   425,     0,     0,   426,     0,   427,   354,
     355,   284,   285,     0,   283,   274,   286,   282,   280,   281,
       0,   275,     0,   287,     0,     0,     0,     0,    45,     0,
       0,     0,     0,     0,    49,   547,    46,     0,    41,    42,
       2,    40,    39,     3,     4,    13,     0,     0,    15,   256,
      22,    25,   263,    43,    48,    44,    58,    51,    79,   107,
      91,    89,   109,   112,   116,   119,   122,   127,   130,   132,
     134,   136,   138,   140,   142,   340,   228,   229,   236,   232,
     241,   240,   254,   266,   259,   261,   264,   268,    50,     0,
     278,     0,   272,   273,   257,   251,   293,   309,   292,   238,
     243,   244,   245,   242,   237,     0,     0,   343,   346,     0,
     276,    52,   352,   233,   393,   392,     0,   308,   430,     0,
     291,   457,   400,    19,    20,   234,     0,     8,   235,   145,
       0,     0,     0,    84,    85,    87,    86,   455,   454,     0,
     159,     0,   158,   381,   283,     0,   116,   132,   382,     0,
     348,   374,     0,   370,   376,   379,   383,   372,    81,    80,
     321,     0,     0,     0,   311,   313,   558,     0,   330,   310,
       0,   522,   560,   556,     0,     0,    11,    21,   239,   246,
     255,   279,   294,    54,   537,     0,     0,     0,     0,     0,
       0,    27,    29,    28,     0,     0,     0,    93,     0,     0,
     295,   105,   350,   289,   288,   296,   290,    96,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   494,   495,
     493,     0,     0,   516,   518,   517,   515,   508,   511,   514,
     510,   512,   513,   509,   504,   505,   496,   502,   499,   500,
     498,   503,   507,   506,   497,   501,   482,   481,   350,   467,
     480,     0,    51,    88,     0,   548,    74,     9,     0,    12,
       0,    16,    26,    92,    90,   347,     0,    14,    23,    24,
     344,   108,   157,     0,     0,    69,    68,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   146,     0,     0,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
       0,     0,   205,     0,   470,   404,   394,   395,   277,   253,
     252,    10,     0,   264,   267,   260,   258,    10,   265,   262,
       0,   250,   396,   399,   249,     0,   248,   342,    82,   366,
       0,   397,   398,   561,     0,   424,   419,     0,   521,     0,
     231,     0,     0,     0,     0,    53,     0,   350,   377,   384,
     349,   368,     0,   371,     0,   317,   314,   323,     0,   556,
       0,     0,   312,   225,     0,   329,   556,   337,   336,     0,
     425,   533,     0,   549,   162,   166,   169,   171,   173,   175,
     177,   179,   181,   385,     0,   389,   530,   386,     0,     0,
     524,   526,   528,   183,     0,     0,    17,     0,     0,    18,
     332,     0,   358,     0,     0,    75,    94,     0,     0,     0,
     100,    99,   102,   350,    98,   105,   105,   520,   519,   350,
     468,   469,     0,     0,     0,     7,     0,     0,     0,     0,
       0,    64,     0,    35,    37,    65,    30,    66,    67,     0,
     111,   110,   114,   115,   113,   117,   118,   120,   121,   123,
     124,   126,   125,   128,   129,   131,   133,   135,   137,   559,
     144,     0,   139,   143,   453,   559,   340,   338,     0,     0,
       0,   471,    10,    83,   339,     0,   353,   367,   401,   428,
     559,   464,   465,   466,     0,   461,     0,   459,     0,   418,
     423,     0,   405,   458,   406,   230,   227,     0,   160,   350,
     375,   378,   373,   380,   328,   325,   326,   321,   315,     0,
       0,   561,     0,   541,   171,   550,     0,     0,     0,     0,
       0,   390,     0,     0,     0,   146,     0,     0,     0,   388,
       0,   534,   523,   556,     0,     0,   531,   540,     0,   538,
     334,   333,     0,   358,   357,   356,     0,   360,     0,     0,
       0,    76,    77,     0,     0,     0,     0,     0,   101,   351,
      95,    97,     0,     0,     6,     0,    63,    33,    34,     0,
       0,     0,    38,     0,    36,     0,    31,     0,    59,   409,
       0,   412,     0,     0,   203,   206,     0,   479,   472,     0,
     474,     0,     0,   402,   543,   403,     0,   431,     0,   463,
     422,     0,   462,   420,     0,     0,     0,   319,   316,   324,
       0,     0,   318,   322,   223,   560,   331,     0,   163,   165,
     164,   167,   168,   170,   391,   172,   174,   176,   184,     0,
       0,   178,   182,   387,   535,   525,   527,   529,   536,     0,
     335,   359,     0,   363,     0,     0,   106,     0,   103,   140,
     161,     0,     0,     0,     5,     0,     0,     0,    62,   557,
       0,   407,   559,   556,   415,   414,     0,   141,   556,     0,
       0,     0,     0,     0,     0,   559,     0,     0,     0,   157,
       0,     0,     0,     3,   340,   188,   189,   192,   196,   193,
     197,   198,   199,   194,   222,     0,   195,     0,   476,     0,
     475,    75,     0,   544,   551,   553,     0,   556,   442,     0,
       0,     0,   440,   439,     0,   433,   434,   438,     0,   437,
       0,   441,     0,   460,   421,   456,   327,     0,   226,     0,
       0,   539,   364,     0,     0,     0,    78,   104,     0,     0,
       0,    32,     0,     0,    55,   408,   413,     0,     0,   417,
       0,     0,     0,   218,     0,   219,   559,     0,     0,     0,
       0,     0,     0,     0,     0,   559,     0,   191,   473,     0,
     546,     0,   552,     0,     0,   443,     0,   446,   444,     0,
     445,     0,   452,     0,   436,   320,   556,   180,   185,   365,
      73,    70,    72,    71,    56,    61,     0,   556,     0,   416,
       0,   559,   202,     0,   211,   217,   221,     0,   213,   220,
       0,   542,     0,   200,   190,   477,   478,     0,   554,     0,
     450,   447,   451,   401,   448,   449,   435,     0,    60,     0,
     410,   204,   207,   201,     0,     0,   212,   559,   559,   559,
     545,   429,   432,     0,     0,     0,   157,   208,   210,   214,
     224,   411,     0,     0,   559,   215,   559,   209,   216
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    73,    74,    75,   288,    76,    77,    78,    79,   222,
      80,    81,    82,   224,   472,   473,   474,   612,    83,    84,
      85,     1,    86,    87,   699,   479,    88,   590,   169,    89,
      90,    91,   231,   451,   452,   446,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   170,
     340,   171,   172,   691,   415,   416,   554,   418,   419,   420,
     421,   422,   423,   669,   670,   625,   725,   726,   727,   728,
     345,   505,   730,   875,   847,   731,   844,   732,   733,   198,
       2,     5,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   349,   179,   122,
     123,   442,   124,   234,   125,   126,   127,   128,   195,   396,
     648,   397,   398,   399,   545,   546,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   181,   599,   369,
     140,   443,   585,   586,   587,   141,   142,   182,   848,   184,
     185,   186,   187,   426,   427,   143,   144,   145,   146,   346,
     509,   347,   704,   534,   620,   621,   705,   531,   147,   148,
     149,   150,   373,   637,   755,   756,   757,   758,   861,   759,
     151,   168,   152,   526,   527,   528,   153,   279,   510,   511,
     628,   629,   630,   631,   154,   280,   155,   156,   429,   430,
     431,   432,   157,   578,   579,   158,   736,   633,   634,   811,
     159,   433,   517,   746,   160,   434,   783,   403,   626,     6,
       4
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -675
static const yytype_int16 yypact[] =
{
    -675,   104,   149,  -675,  -675,    23,  1881,  -675,  -675,  4095,
    4095,  -675,  -675,  4095,  4095,  4095,  3726,  2619,  -675,  4095,
    4095,  -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,
    -675,  -675,  -675,  -675,   277,   295,  -675,    38,  -675,  -675,
    -675,  -675,  -675,   282,    68,  -675,  -675,  -675,  -675,  -675,
    4365,  -675,   554,  -675,   209,   292,  4095,   310,  -675,  4655,
    4218,   312,  4095,   340,  -675,  3726,  -675,   260,  -675,  -675,
    -675,  -675,  -675,  -675,   396,   367,   452,    69,  -675,  -675,
    -675,  -675,  -675,  -675,  -675,  -675,  -675,  4297,   502,  -675,
    -675,  -675,  -675,    94,   525,   503,   534,   664,   130,   417,
     435,   439,   419,  1399,  -675,   102,  -675,  -675,  -675,  -675,
    -675,  -675,  1966,   755,  1966,  -675,   998,  -675,  -675,   455,
    -675,  2373,  -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,
    -675,  -675,  -675,  -675,  -675,   556,   441,   511,  -675,  4095,
    -675,  -675,  -675,  -675,  -675,  -675,   284,  -675,  -675,    87,
    -675,   458,  -675,  -675,  -675,  -675,  2250,  -675,  -675,  -675,
     589,   477,  4684,  -675,  -675,  -675,  -675,   115,  -675,   489,
     491,   468,  -675,  -675,  -675,  4586,   525,   526,  -675,  2619,
    4095,  -675,   516,    89,  -675,   528,  -675,  -675,  -675,  -675,
      81,    38,   -23,   -23,   537,  -675,  -675,   377,  -675,  -675,
     532,  -675,   539,  2742,  4748,   550,  -675,  -675,  -675,  -675,
    -675,  -675,  -675,  -675,  -675,   -23,    38,   425,   425,   -17,
     236,  -675,  -675,  -675,   549,    68,  4909,  -675,  4909,   585,
    -675,   560,  1494,  -675,  -675,  -675,  -675,  4655,  -675,  -675,
    -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,
    -675,   565,   593,  -675,  -675,  -675,  -675,  -675,  -675,  -675,
    -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,
    -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,  4267,  -675,
    -675,  4909,  -675,  -675,  4909,  -675,  -675,  -675,   591,  -675,
     -17,  -675,  -675,  -675,  -675,  -675,   236,  -675,  -675,  -675,
    -675,  -675,  3726,   891,   891,  -675,  -675,  -675,  4095,  4095,
    4095,  4095,  3357,  4095,  4095,  4095,  4095,  4095,  4095,  4095,
    4095,  4095,  4095,  4095,  4095,  4095,  4095,   599,  3726,  4095,
    -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,  -675,
    3726,  4095,  -675,  3726,   615,  -675,  -675,  -675,  -675,  -675,
    -675,   620,  1070,  1097,  -675,  1966,  -675,   634,  -675,  -675,
    3357,  -675,  -675,  -675,  -675,  3726,  -675,  -675,  -675,   387,
    3726,  -675,  -675,   616,   433,  -675,   196,  3480,  -675,  1881,
    -675,   628,  4938,  4095,  3726,  -675,  4860,  3357,  4095,  -675,
    -675,  -675,  2619,  -675,  3726,  -675,  -675,  -675,   523,   300,
     662,   -23,  -675,  -675,    38,  -675,  3111,  -675,  -675,  2250,
     276,    38,  4445,  3849,   534,   262,   306,   674,   681,   684,
     656,  1753,  -675,  -675,  3234,  -675,  -675,   686,   626,   254,
    -675,   691,   693,  -675,   708,  3234,  -675,   683,   685,  -675,
    -675,   692,  1419,   702,   705,  3726,  -675,  3726,   147,   147,
    -675,  -675,   704,   395,  -675,   560,   560,  -675,  -675,   405,
    -675,  -675,   709,   710,  2865,  -675,   707,  1560,   891,   963,
    1245,  -675,  1860,  -675,  -675,  -675,  -675,  -675,  -675,   595,
    -675,  -675,    94,    94,    94,   525,   525,   503,   503,   534,
     534,   534,   534,   664,   664,   130,   417,   435,   439,   717,
    -675,   711,   419,  -675,  -675,   718,  -675,  -675,    38,   627,
     714,  -675,   723,  -675,  -675,   727,  -675,  -675,  -675,  -675,
    -675,  -675,  -675,  -675,   433,  -675,   278,  -675,   433,  -675,
    -675,   453,  -675,  -675,  -675,  -675,  -675,   728,   719,  4095,
    -675,  -675,  -675,  -675,  -675,  -675,   738,   161,  -675,   753,
     325,   735,   729,  -675,   748,  -675,  4095,  4095,  4095,  4095,
    4095,  4095,  4095,  4095,  4095,  -675,  3849,  4095,  3849,  -675,
    3849,   523,  -675,  3111,  4909,   523,  -675,  -675,   257,  -675,
    -675,  -675,   730,    91,  -675,  -675,   449,   478,   740,   741,
     742,   736,  -675,   750,  4095,   367,   147,   147,  -675,  -675,
    -675,  -675,   749,   754,  -675,   264,  -675,  1258,  -675,  1258,
     963,  1320,  -675,  1245,  -675,   758,  -675,  2004,  -675,  -675,
     330,   646,  2127,  3726,  -675,   648,  1635,  -675,    86,    38,
    -675,   756,   757,  -675,   627,  -675,  4719,   651,  1758,  -675,
    -675,   433,  -675,  -675,   311,  4095,  4095,  -675,  -675,  -675,
     779,   766,  -675,  -675,  -675,  -675,  -675,  4095,   534,   534,
     534,   262,   262,   306,  -675,   748,   681,   684,   764,   771,
     773,   656,  -675,  -675,  -675,  -675,  -675,  -675,  -675,  3234,
    -675,  -675,  3972,  -675,  3726,  3726,  -675,  3726,  -675,   271,
    -675,   770,  3726,  3726,  -675,  1320,  1523,  1258,  -675,  2619,
     578,  -675,   782,  -675,  -675,  -675,   609,  -675,  -675,    38,
    4514,   776,  4095,   784,   800,  -675,   797,   523,   799,  3726,
     807,   714,   813,   819,   805,  -675,  -675,  -675,  -675,  -675,
    -675,  -675,  -675,  -675,  -675,  2988,  -675,   631,  -675,   838,
    -675,  3726,  2619,  -675,  -675,  -675,    47,  -675,  -675,   715,
     123,  2496,  -675,  -675,   444,  -675,  -675,  -675,   613,  -675,
     829,  -675,   644,  -675,  -675,  -675,  -675,   415,   712,  3849,
    3849,  -675,  -675,   828,   825,   826,  -675,  -675,   830,   831,
    1523,  1258,   621,    88,  -675,  -675,   722,   850,  2127,  -675,
     853,   841,  4811,  -675,   844,  -675,  -675,   743,  2988,   834,
    2619,   836,  2619,   627,  2619,  -675,  1635,  -675,   839,   845,
    -675,   847,  -675,  4909,   871,  -675,  3603,  -675,  -675,  3603,
    -675,  3603,  -675,  1758,  -675,  -675,  -675,  -675,   843,  -675,
    -675,  -675,  -675,  -675,  -675,  -675,   877,  -675,   860,  -675,
     177,  -675,  -675,   861,  2619,  -675,  -675,   863,   856,  -675,
     869,  -675,   870,  -675,  -675,  -675,  -675,   714,  -675,   186,
     878,  -675,  -675,   878,  -675,  -675,  -675,   892,  -675,   894,
    -675,  -675,  -675,  -675,  3726,   868,  -675,  -675,  -675,  -675,
    -675,  -675,  -675,   318,   879,   881,  3726,   803,  -675,  -675,
    -675,  -675,   876,   885,  -675,  -675,  -675,  -675,  -675
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -675,  -588,   -46,   -26,  -675,   706,   824,     7,    76,   -40,
      20,   -32,   -31,  -163,  -435,  -412,  -430,   362,    -8,  -675,
    -675,  -675,  -675,   846,  -675,  -675,  -675,   160,  -429,   851,
     833,   840,   230,   459,  -675,   219,   245,   204,     5,   364,
     687,   365,  -242,    -3,   590,   588,   592,     8,  -548,    -6,
     497,  -285,  -277,  -516,   132,  -498,  -175,   356,   361,   353,
    -675,  -675,  -325,  -675,  -675,  -674,   120,  -675,  -675,  -675,
    -596,  -675,  -675,  -675,  -518,  -675,  -675,  -675,  -675,   165,
     524,  -187,   551,  -127,    10,  -573,   -41,  -116,   814,   -43,
    -675,   -90,   816,   818,  -675,  -675,   -81,   822,    73,  -675,
    -675,     2,   713,  -675,   903,  -675,  -675,  -675,   739,   545,
    -675,   399,  -675,  -675,  -675,  -675,  -675,  -675,  -581,  -675,
    -675,  -675,  -675,  -268,   -67,   -28,   -11,   768,  -185,  -675,
     268,  -189,   366,  -675,  -675,   -38,     9,  -675,   -14,   -89,
    -675,  -675,  -160,  -400,  -675,  -572,  -113,  -111,  -595,  -133,
    -675,  -128,   587,   638,  -675,   265,   178,  -675,  -675,  -675,
    -675,  -675,  -675,  -675,   145,  -675,   218,  -675,   150,  -675,
    -675,  -316,  -318,   445,  -451,  -566,  -675,   697,  -675,  -675,
    -675,  -675,   341,  -675,  -675,  -675,   -42,  -183,  -675,   404,
    -675,  -675,   682,   517,   301,  -675,  -675,  -592,  -675,  -675,
    -675,  -675,  -675,  -675,  -536,    -5,  -675,  -675,  -465,  -675,
    -315
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -557
static const yytype_int16 yytable[] =
{
     105,   201,   161,   183,   205,   361,   180,   210,   362,   209,
     363,   178,   213,   371,   177,   408,   591,   466,   372,   389,
     428,   223,   176,   167,   569,   504,   359,   312,   417,   378,
     729,   348,   607,   348,   622,   577,   202,   298,   723,   444,
     614,   797,   743,   754,   292,   299,   690,   454,   295,   300,
     307,   501,   360,   734,   438,   638,   608,   752,   520,   285,
     208,   232,   278,   663,   577,   401,   753,   537,   237,   812,
     207,   290,   760,   639,    11,   507,   286,   642,   813,   121,
     215,   495,  -556,   291,   297,   358,   706,  -556,   555,   835,
     737,    60,   462,   460,    21,   463,    11,   514,   690,    70,
      12,   395,   762,   374,     3,    70,   375,   836,  -361,   387,
     194,   197,  -361,   199,   425,   105,   205,   738,   341,   210,
     392,   342,   842,   211,   213,   803,   191,   308,   221,   205,
     766,   853,   210,   343,   690,   230,   230,   213,   383,   341,
     471,   477,   342,    21,   393,   205,   495,    21,   309,   -47,
     105,     7,    11,   815,   816,   329,   754,   296,   205,   663,
      70,   210,  -556,   209,   690,   321,   773,   873,   180,   180,
     593,   322,   205,   178,   607,   191,   177,    60,   439,   191,
     298,   647,   207,   205,   176,   400,   223,   292,   299,   436,
     763,    70,   180,    72,   121,   207,   794,   871,   608,   291,
     297,   608,   540,   887,   888,   889,   881,   872,   176,    70,
     729,   851,   529,    70,   208,   530,   882,   441,   723,   344,
     897,   453,   898,   428,   207,   376,   291,   297,   754,   121,
     225,   417,   542,   734,   232,   401,   655,   622,   207,   232,
     344,   668,   752,   672,   205,   673,   456,   215,   211,   417,
     205,   753,   706,   584,   163,   164,   439,   760,   165,   166,
     417,   880,   781,   359,   188,   189,   614,   459,   572,    70,
     737,   678,   223,   223,   348,   556,   424,   211,   694,   577,
     278,    17,   553,   608,   850,   573,   852,   762,   679,   417,
    -532,  -532,   437,   221,   328,   679,   190,   640,   557,   541,
     558,   227,   230,   342,   230,   226,   205,  -532,   230,   641,
     207,   329,   591,   230,   196,   370,   207,   425,   485,   486,
     395,   496,   358,   228,   296,   281,   876,   236,   236,   765,
     764,   547,   301,    21,   503,   425,   205,   506,   890,   210,
     205,   559,   641,   210,    60,   652,   425,   560,   536,   167,
     701,    21,   544,   284,   230,   205,   653,   230,    70,   506,
     230,   702,   405,    43,   518,   191,   205,   407,   608,   210,
     200,   532,   207,   105,   213,   425,   539,   180,   538,   221,
     221,   180,   635,   191,   368,   676,   178,   665,   543,   177,
     428,   167,   404,   176,   549,   180,   196,   176,   417,    70,
      11,   344,   207,   105,    12,   367,   207,   774,   775,   287,
      11,   176,   447,   180,    12,   778,   779,    70,   312,   312,
     295,   300,   205,   289,   180,   368,   323,   595,   439,   176,
     298,   583,   207,   595,   801,   825,   215,   292,   299,   592,
     176,   436,   453,   324,   827,   828,   653,   745,   459,   325,
     525,    21,   121,   180,   643,   291,   297,    11,   326,   211,
      11,    21,   450,   342,    39,    40,   682,   455,   768,   176,
      17,   366,   664,   377,   818,   819,   291,   297,   381,   424,
     552,    21,   121,   191,   425,   211,   385,   199,   207,    21,
     521,   522,   523,   191,   236,  -362,   236,   424,   862,  -362,
     236,   864,   515,   862,   417,   236,   313,   314,   424,    21,
     521,   522,   523,   218,   482,   483,   484,    70,   230,   302,
     384,   191,   -77,    17,   524,   674,   303,    70,   539,   677,
      11,   310,   311,    60,   304,   388,   305,   424,   391,   306,
     290,   191,   650,   394,   524,   406,   236,    70,   683,   236,
     180,    56,   236,   480,   481,    70,   190,   595,   196,    59,
      60,   344,   180,   435,   205,   215,   176,   205,   295,   300,
     595,   595,   583,   439,    70,    70,   315,   316,   176,   440,
     367,   445,   810,   457,   627,   595,   364,   365,    39,    40,
     425,   484,   379,   380,   464,   465,   761,   885,   617,   618,
     525,   893,   689,   700,   525,   513,   180,   525,   784,   392,
      21,   178,   788,   789,   177,   458,   532,   707,   499,   361,
     724,   371,   176,   739,   858,  -271,   372,   216,   367,   217,
     207,   508,   750,   207,   806,   807,   519,   516,   362,  -269,
     363,    21,   218,   820,   821,    70,   424,   823,   824,   205,
     230,   834,   392,   167,   689,   367,    33,    34,   536,    36,
      37,    38,    60,   550,   205,   475,   478,   210,   180,   209,
     595,   799,   213,   229,   600,   601,    70,   317,   318,   487,
     488,   776,   845,   561,   176,   782,   493,   494,   180,   562,
     689,   661,   662,   178,   563,   564,   177,   571,   787,   735,
     319,   570,   320,   790,   176,   627,   574,    70,   575,   576,
     236,   751,   230,   580,   582,   581,   588,   525,   223,   589,
     689,   594,   632,   602,   603,   606,   215,   623,  -270,   724,
     207,   180,   214,   342,   205,   592,   178,   619,   624,   177,
     192,   192,   814,   192,   645,   750,   205,   176,   636,   210,
     -78,   209,   424,   646,   651,   654,   206,   657,   219,   656,
     680,   684,   685,   212,   686,   192,   192,   687,   688,   697,
     692,    21,   233,   233,   703,   693,   708,   741,   742,   747,
     767,   761,   532,   211,   368,   791,   652,   769,   777,   180,
     217,   180,   724,   180,   178,  -186,   178,   177,   178,   177,
     724,   177,   785,   218,   770,   176,   793,   176,   735,   176,
     860,   351,   207,   863,   795,   860,   796,   750,   798,   219,
     800,   867,   219,    60,   751,   221,    33,    34,   802,    36,
      37,    38,   869,   180,   804,   805,   343,    70,   178,   808,
     826,   177,   236,   352,   214,   822,   829,   830,   831,   176,
     837,   838,   832,   833,   840,   192,   404,   214,   193,   193,
     841,   193,   843,    60,   846,   211,   849,   856,   206,   857,
     855,   735,   859,   214,  -187,   212,   220,    70,   868,   735,
     870,   206,   874,   193,   193,   877,   214,   392,   212,   230,
     414,   878,   879,   883,   341,   884,   751,   206,   886,   891,
     214,   809,   467,   892,   236,   894,   895,   896,   282,   293,
     206,   214,   598,   283,   498,   497,   294,   212,   568,   666,
     671,   502,   192,   219,   206,   667,   854,   551,   355,   353,
     535,   354,   192,   402,   192,   206,   356,   220,   448,   233,
     220,   233,   212,   192,   548,   233,   649,    21,   390,   681,
     233,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,   235,   235,   533,   500,   839,   786,   866,   817,
     740,   865,   214,   193,   609,   461,   644,   675,   214,   468,
     771,   605,     0,     0,   448,     0,     0,   192,     0,     0,
     192,   233,     0,     0,   233,     0,     0,   233,     0,    60,
       0,     0,     0,     0,   489,   490,   491,   492,     0,   469,
     469,     0,     0,    70,     0,   350,   193,   193,     0,    21,
       0,     0,     0,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,   214,     0,     0,     0,     0,     0,
     193,   220,     0,   220,   220,     0,     0,     0,     0,     0,
     193,   610,   193,     0,   357,     0,   449,     0,   206,   219,
       0,   193,     0,     0,   214,   212,     0,     0,   214,    33,
      34,    60,    36,    37,    38,     0,     0,     0,     0,     0,
     192,   236,     0,   214,     0,    70,   352,     0,   206,     0,
       0,     0,   206,   414,   214,   212,     0,     0,     0,   212,
     414,     0,   449,     0,     0,   193,    60,     0,   193,     0,
     192,   414,     0,     0,     0,     0,     0,   192,   206,     0,
      70,     0,   414,     0,     0,   212,    21,   470,   470,   235,
       0,   235,     0,     0,     0,   235,     0,     0,     0,     0,
     235,    33,    34,     0,    36,    37,    38,     0,   448,     0,
     214,   414,     0,   512,     0,   233,     0,     0,   352,   596,
       0,     0,     0,     0,     0,   596,     0,     0,    33,    34,
       0,    36,    37,    38,   206,   611,     0,   220,    60,     0,
       0,   235,     0,     0,   235,   352,     0,   235,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,   193,     0,
       0,     0,     0,     0,     0,    60,   476,   476,     0,     0,
       0,     0,     0,     0,   192,     0,     0,     0,     0,    70,
       0,     0,     0,     0,     0,     0,     0,     0,   193,     0,
     192,     0,     0,     0,   192,   193,     0,   192,     0,     0,
       0,     0,     0,   658,   659,   660,   414,   414,   414,   414,
     414,   414,     0,   414,   414,   414,   467,   414,   350,     0,
     414,     0,     0,     0,     0,     0,   449,     0,     0,     0,
       0,     0,   449,   449,     0,     0,     0,   597,     0,     0,
     192,     0,     0,   597,     0,     0,     0,   233,     0,   596,
       0,     0,   214,   470,   470,   214,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,   206,   611,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     0,
       0,   609,   193,   613,     0,   192,     0,     0,     0,     0,
       0,     0,   192,     0,   414,   235,     0,   192,   193,   233,
       0,     0,   193,    60,     0,   193,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   414,    70,     0,     0,
     476,   476,   476,   476,     0,   616,    21,   214,     0,     0,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,   214,     0,     0,     0,     0,     0,   193,     0,
       0,   206,     0,     0,     0,     0,     0,   597,   695,     0,
       0,     0,     0,     0,   327,   192,   206,     0,     0,     0,
     597,   597,   328,   212,    11,     0,     0,     0,    12,     0,
       0,     0,     0,     0,     0,   696,  -361,     0,     0,   329,
    -361,     0,    70,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   193,     0,   219,   414,   414,     0,     0,
     193,     0,   214,     0,     0,   193,     0,     0,     0,     0,
       0,     0,     0,     0,   214,    21,     0,   235,     0,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,     0,    36,    37,    38,    39,    40,   206,    11,
       0,     0,     0,    12,     0,   212,     0,   229,     0,     0,
     616,   447,   476,   476,   476,     0,   476,     0,     0,   192,
     696,     0,     0,     0,     0,     0,   233,     0,     0,     0,
       0,     0,     0,   193,   609,     0,     0,     0,     0,   235,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
      21,     0,     0,     0,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,     0,    36,    37,
      38,    39,    40,   220,     0,     0,     0,     0,     0,     0,
       0,     0,   229,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     0,     0,     0,     0,   476,   476,
     476,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   780,     0,     0,     0,     0,    70,     0,     0,     0,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,     0,     0,     0,     0,     8,   193,     9,    10,
      11,     0,     0,     0,    12,    70,    13,    14,   401,     0,
       0,     0,    16,     0,   342,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     0,    18,     0,     0,     0,    19,
       0,     0,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,   476,   616,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,   709,    36,
      37,    38,    39,    40,    41,    42,   235,   174,    45,    46,
      47,    48,    49,   710,    51,    52,    53,    54,   711,   712,
       0,    55,   713,   714,    56,   715,    57,     0,    58,   716,
     717,   718,    59,    60,    61,   719,    62,    63,   720,    64,
      65,    66,   721,    67,   722,    68,    69,    70,    71,     8,
      72,     9,    10,    11,     0,     0,     0,    12,   565,    13,
      14,     0,     0,     0,    15,    16,   566,     0,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     0,   748,     0,
       0,     0,    19,   567,     0,    20,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,     0,     0,     0,
       0,     0,     0,     0,    21,   521,   522,   523,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     0,    36,    37,    38,    39,    40,    41,    42,    43,
     174,    45,    46,    47,    48,    49,   412,    51,   749,    53,
       0,     0,     0,     0,    55,     0,     0,    56,     0,    57,
       0,    58,     0,     0,     0,    59,    60,    61,     0,    62,
      63,     0,    64,    65,    66,     0,    67,     0,    68,    69,
      70,    71,     8,    72,     9,    10,    11,     0,     0,     0,
      12,     0,    13,    14,     0,     0,     0,    15,    16,     0,
       0,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,     0,    19,   615,     0,    20,     0,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,     0,     0,     0,     0,     0,    21,     0,     0,
       0,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,     0,     0,     0,    55,     0,     0,
      56,     0,    57,     0,    58,     0,     0,     0,    59,    60,
      61,     0,    62,    63,     0,    64,    65,    66,     0,    67,
       0,    68,    69,    70,    71,   698,    72,     9,    10,    11,
       0,     0,     0,    12,     0,    13,    14,     0,     0,     0,
       0,    16,     0,     0,     0,    17,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     0,    19,     0,
       0,    20,     0,    39,    40,    41,    42,     0,   174,    45,
      46,    47,    48,    49,     0,    51,     0,    53,     0,   173,
      21,     0,     0,     0,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,     0,    36,    37,
      38,    39,    40,    41,    42,     0,   174,    45,    46,    47,
      48,    49,   175,    51,     0,    53,     0,     0,     0,     0,
      55,     0,     0,    56,     0,    57,     0,    58,     0,     0,
       0,    59,    60,    61,     0,    62,    63,     0,    64,    65,
      66,     0,    67,     0,    68,    69,    70,    71,     8,    72,
       9,    10,    11,     0,     0,     0,    12,     0,    13,    14,
       0,     0,     0,     0,    16,     0,   499,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     0,     0,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       0,    36,    37,    38,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   162,     0,     0,     0,     0,
       0,     0,     0,    55,     0,     0,    56,     0,    57,     0,
      58,     0,     0,     0,    59,    60,    61,     0,    62,    63,
       0,    64,    65,    66,     0,    67,     0,    68,    69,    70,
      71,     0,    72,     9,    10,    11,     0,     0,     0,    12,
       0,    13,    14,     0,     0,     0,    15,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,     0,     0,    19,     0,     0,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,     0,     0,     0,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,     0,     0,     0,    55,     0,     0,    56,
       0,    57,     0,    58,     0,     0,     0,    59,    60,    61,
       0,    62,    63,     0,    64,    65,    66,     0,    67,     0,
      68,    69,    70,    71,     0,    72,     9,    10,    11,     0,
       0,     0,    12,     0,    13,    14,     0,     0,     0,    15,
      16,     0,     0,     0,    17,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,     0,     0,    19,     0,     0,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
       0,     0,     0,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,     0,    36,    37,    38,
      39,    40,    41,    42,     0,   174,    45,    46,    47,    48,
      49,   175,    51,     0,    53,     0,     0,     0,     0,    55,
       0,     0,    56,     0,    57,     0,    58,     0,     0,     0,
      59,    60,    61,     0,    62,    63,     0,    64,    65,    66,
       0,    67,     0,    68,    69,    70,    71,     0,    72,     9,
      10,    11,     0,     0,     0,    12,     0,    13,    14,     0,
       0,     0,    15,    16,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     0,   748,     0,     0,     0,
      19,     0,     0,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,     0,     0,     0,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,     0,
      36,    37,    38,    39,    40,    41,    42,     0,   174,    45,
      46,    47,    48,    49,   175,    51,     0,    53,     0,     0,
       0,     0,    55,     0,     0,    56,     0,    57,     0,    58,
       0,     0,     0,    59,    60,    61,     0,    62,    63,     0,
      64,    65,    66,     0,    67,     0,    68,    69,    70,    71,
       0,    72,     9,    10,    11,     0,     0,     0,    12,     0,
      13,    14,     0,     0,     0,     0,    16,     0,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,    21,     0,     0,     0,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,     0,    36,    37,    38,    39,    40,    41,    42,
       0,   174,    45,    46,    47,    48,    49,   175,    51,     0,
      53,     0,     0,     0,     0,    55,     0,     0,    56,     0,
      57,     0,    58,     0,     0,     0,    59,    60,    61,     0,
      62,    63,     0,    64,    65,    66,     0,    67,     0,    68,
      69,    70,    71,     0,    72,     9,    10,    11,     0,     0,
       0,    12,     0,    13,    14,     0,   409,     0,     0,    16,
       0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,     0,     0,    20,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,     0,
       0,     0,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,   410,    34,     0,    36,   411,    38,    39,
      40,    41,    42,     0,   174,    45,    46,    47,    48,    49,
     412,    51,     0,    53,     0,     0,     0,     0,    55,     0,
       0,    56,     0,    57,     0,    58,     0,     0,     0,    59,
      60,    61,     0,    62,    63,     0,    64,   413,    66,     0,
      67,     0,    68,    69,    70,    71,     0,    72,     9,    10,
      11,     0,     0,     0,    12,     0,    13,    14,     0,   604,
       0,     0,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
       0,     0,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,     0,    36,
      37,    38,    39,    40,    41,    42,     0,   174,    45,    46,
      47,    48,    49,   175,    51,     0,    53,     0,     0,     0,
       0,    55,     0,     0,    56,     0,    57,     0,    58,     0,
       0,     0,    59,    60,    61,     0,    62,    63,     0,    64,
     413,    66,     0,    67,     0,    68,    69,    70,    71,     0,
      72,     9,    10,    11,     0,     0,     0,    12,     0,    13,
      14,     0,     0,     0,     0,    16,     0,     0,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     0,    18,     0,
       0,     0,    19,     0,     0,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,     0,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     0,    36,    37,    38,    39,    40,    41,    42,     0,
     174,    45,    46,    47,    48,    49,   175,    51,     0,    53,
       0,     0,     0,     0,    55,     0,     0,    56,     0,    57,
       0,    58,     0,     0,     0,    59,    60,    61,     0,    62,
      63,     0,    64,    65,    66,     0,    67,     0,    68,    69,
      70,    71,     0,    72,     9,    10,    11,     0,     0,     0,
      12,     0,    13,    14,     0,     0,     0,     0,    16,     0,
       0,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,     0,     0,    20,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,     0,     0,
       0,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,   410,    34,     0,    36,   411,    38,    39,    40,
      41,    42,     0,   174,    45,    46,    47,    48,    49,   412,
      51,     0,    53,     0,     0,     0,     0,    55,     0,     0,
      56,     0,    57,     0,    58,     0,     0,     0,    59,    60,
      61,     0,    62,    63,     0,    64,   413,    66,     0,    67,
       0,    68,    69,    70,    71,     0,    72,     9,    10,    11,
       0,     0,     0,    12,     0,    13,    14,     0,     0,     0,
       0,    16,     0,     0,     0,    17,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,     0,
       0,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,     0,     0,     0,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,     0,    36,    37,
      38,    39,    40,    41,    42,     0,   174,    45,    46,    47,
      48,    49,   175,    51,     0,    53,     0,     0,     0,     0,
      55,     0,     0,    56,     0,    57,     0,    58,     0,     0,
       0,    59,    60,    61,     0,    62,    63,     0,    64,   413,
      66,     0,    67,     0,    68,    69,    70,    71,     0,    72,
       9,    10,    11,     0,     0,     0,    12,     0,    13,    14,
       0,     0,     0,     0,    16,     0,     0,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     0,     0,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       0,    36,    37,    38,    39,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   162,     0,     0,     0,     0,
       0,     0,     0,    55,     0,     0,    56,     0,    57,     0,
      58,     0,     0,     0,    59,    60,    61,     0,    62,    63,
       0,    64,     0,    66,     0,    67,     0,    68,    69,    70,
      71,     0,    72,     9,    10,    11,     0,     0,     0,    12,
       0,    13,    14,     0,     0,     0,     0,    16,     0,   499,
       0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    19,     0,     0,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,     0,     0,     0,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,     0,    36,    37,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   162,     0,
       0,     0,     0,     0,     0,     0,    55,     0,     0,    56,
       0,    57,     0,    58,     0,     0,     0,    59,    60,    61,
       0,    62,    63,     0,    64,    65,    66,     0,    67,     0,
      68,    69,    70,    71,     0,    72,     9,    10,    11,     0,
       0,     0,    12,     0,    13,    14,     0,     0,     0,    15,
      16,     0,     0,     0,    17,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,     0,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
       0,     0,     0,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,     0,    36,    37,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   162,     0,     0,     0,     0,     0,     0,     0,    55,
       0,     0,    56,     0,    57,     0,    58,     0,     0,     0,
      59,    60,    61,     0,    62,    63,     0,    64,    65,    66,
       0,    67,     0,    68,    69,    70,    71,     0,    72,     9,
      10,    11,     0,     0,     0,    12,     0,    13,    14,     0,
       0,     0,     0,    16,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,     0,     0,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,     0,     0,     0,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,     0,
      36,    37,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   162,     0,     0,     0,     0,     0,
       0,     0,    55,     0,     0,    56,     0,    57,     0,    58,
       0,     0,     0,    59,    60,    61,     0,    62,    63,     0,
      64,    65,    66,     0,    67,     0,    68,    69,    70,    71,
       0,    72,     9,    10,    11,     0,     0,     0,    12,     0,
      13,    14,     0,     0,     0,     0,    16,     0,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,     0,     0,     0,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,     0,    36,    37,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   162,     0,     0,
       0,     0,     0,     0,     0,    55,     0,     0,    56,     0,
      57,     0,    58,     0,     0,     0,    59,    60,    61,     0,
      62,    63,     0,    64,   413,    66,     0,    67,     0,    68,
      69,    70,    71,     0,    72,     9,    10,    11,     0,     0,
       0,    12,     0,    13,    14,     0,     0,     0,     0,    16,
     772,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,     0,     0,    20,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,     0,
       0,     0,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,     0,    36,    37,    38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     162,     0,     0,     0,     0,     0,     0,     0,    55,     0,
       0,    56,     0,    57,     0,    58,     0,     0,     0,    59,
      60,    61,     0,    62,    63,     0,    64,     0,    66,     0,
      67,     0,    68,    69,    70,    71,     0,    72,     9,    10,
      11,     0,     0,     0,    12,     0,    13,    14,     0,     0,
       0,     0,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
       0,     0,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,     0,    36,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   162,     0,     0,     0,     0,     0,     0,
       0,    55,     0,     0,    56,     0,    57,     0,    58,     0,
       0,     0,    59,    60,    61,     0,    62,    63,     0,    64,
       0,    66,     0,    67,     0,    68,    69,    70,    71,     0,
      72,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,     0,   251,     0,     0,     0,   252,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,    11,     0,    21,     0,    12,     0,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     0,    36,    37,    38,    39,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   229,     0,    13,    14,
       0,     0,     0,     0,     0,     0,     0,   276,    17,     0,
       0,     0,     0,    21,     0,   277,     0,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      70,    36,    37,    38,    39,    40,     0,     0,     0,     0,
       0,     0,     0,    21,     0,   229,     0,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       0,    36,    37,    38,     0,     0,     0,     0,   203,     0,
       0,     0,     0,     0,     0,   162,    17,     0,     0,    70,
       0,     0,     0,    55,     0,     0,    56,     0,    57,     0,
      58,     0,     0,     0,    59,    60,    61,     0,    62,    63,
       0,    64,     0,    66,     0,    67,     0,    68,    69,    70,
      71,    21,    72,     0,     0,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,     0,    44,    45,    46,
      47,    48,    49,   204,    51,    52,    53,    54,   406,     0,
       0,     0,     0,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,     0,    36,
      37,    38,    39,    40,    41,    42,     0,   174,    45,    46,
      47,    48,    49,   386,    51,    17,    53,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,     0,     0,
      21,     0,     0,     0,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,   709,    36,    37,
      38,    39,    40,    41,    42,     0,   174,    45,    46,    47,
      48,    49,   792,    51,    52,    53,    54,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    70,     0,     0,     0,
       0,     0,    21,     0,     0,     0,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,     0,
      36,    37,    38,    39,    40,    41,    42,     0,   174,    45,
      46,    47,    48,    49,   386,    51,    17,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,    70,     0,
       0,    21,     0,     0,     0,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,     0,    36,
      37,    38,    39,    40,     0,     0,     0,     0,     0,     0,
      21,   744,     0,   229,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,     0,    36,    37,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   382,     0,     0,    21,     0,    70,     0,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    60,    36,    37,    38,    39,    40,     0,     0,
       0,     0,     0,     0,    21,     0,    70,   229,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,     0,
      44,    45,    46,    47,    48,    49,   204,    51,    52,    53,
      54,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,     0,     0,
      70,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,   709,    36,    37,    38,    39,    40,
      41,    42,     0,   174,    45,    46,    47,    48,    49,   792,
      51,    52,    53,    54,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,     0,     0,    60,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    70,    36,    37,    38,    39,    40,    41,
      42,     0,   174,    45,    46,    47,    48,    49,   386,    51,
       0,    53,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,     0,     0,    60,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    70,    36,    37,    38,    39,    40,     0,     0,
       0,     0,     0,     0,    21,     0,     0,   229,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     0,    36,    37,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   382,     0,     0,     0,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-675)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       6,    43,     7,    17,    50,   121,    17,    50,   121,    50,
     121,    17,    50,   146,    17,   202,   445,   302,   146,   179,
     203,    52,    17,    15,   424,   341,   116,    94,   203,   156,
     626,   112,   467,   114,   499,   435,    44,    77,   626,   228,
     470,   715,   634,   638,    76,    77,   594,   232,    76,    77,
      88,   328,   119,   626,   217,   520,   468,   638,   373,    65,
      50,    59,    60,   561,   464,    88,   638,   383,    59,    22,
      50,    88,   638,   524,     5,   343,    67,   528,    31,     6,
      11,   323,     1,    76,    77,   116,   622,     1,   413,     1,
     626,   108,   281,   278,    56,   284,     5,   365,   646,   122,
       9,    20,   638,    16,     0,   122,    19,    19,    17,   176,
      34,    35,    21,    37,   203,   121,   162,    31,    16,   162,
      31,    19,   796,    50,   162,   721,    88,    33,    52,   175,
     646,   805,   175,    31,   682,    59,    60,   175,    23,    16,
     303,   304,    19,    56,    55,   191,   388,    56,    54,     0,
     156,   128,     5,    30,    31,    40,   751,    88,   204,   657,
     122,   204,     1,   204,   712,    35,   682,   841,   179,   180,
     447,    41,   218,   179,   609,    88,   179,   108,   218,    88,
     220,    20,   162,   229,   179,   190,   217,   219,   220,   215,
     641,   122,   203,   125,   121,   175,   712,    20,   610,   192,
     193,   613,   387,   877,   878,   879,    20,    30,   203,   122,
     806,   803,    16,   122,   204,    19,    30,   225,   806,   117,
     894,   232,   896,   406,   204,   149,   219,   220,   823,   156,
      21,   406,   392,   806,   232,    88,   551,   702,   218,   237,
     117,   566,   823,   568,   290,   570,   237,    11,   175,   424,
     296,   823,   788,   442,     9,    10,   296,   823,    13,    14,
     435,   857,   697,   353,    19,    20,   696,   278,    14,   122,
     806,    14,   303,   304,   355,    13,   203,   204,    14,   679,
     278,    21,   409,   695,   802,    31,   804,   823,    31,   464,
      14,    15,   216,   217,    23,    31,    19,    19,    36,   388,
      38,    56,   226,    19,   228,    13,   352,    31,   232,    31,
     290,    40,   741,   237,    19,    31,   296,   406,   313,   314,
      20,   324,   353,    13,    88,    13,   844,    59,    60,   645,
      19,    31,    87,    56,   340,   424,   382,   343,    20,   382,
     386,    35,    31,   386,   108,    20,   435,    41,    30,   341,
      20,    56,   398,    13,   278,   401,    31,   281,   122,   365,
     284,    31,   197,    81,   370,    88,   412,   202,   780,   412,
      88,   377,   352,   379,   412,   464,   387,   388,   384,   303,
     304,   392,   510,    88,   139,   574,   392,   562,   394,   392,
     573,   383,    15,   388,   399,   406,    19,   392,   573,   122,
       5,   117,   382,   409,     9,   137,   386,   684,   685,    13,
       5,   406,    17,   424,     9,   692,   693,   122,   485,   486,
     448,   449,   468,    56,   435,   180,     9,   453,   468,   424,
     470,   442,   412,   459,   719,    20,    11,   469,   470,   445,
     435,   467,   453,     8,   769,   770,    31,   636,   459,    10,
     374,    56,   379,   464,     1,   448,   449,     5,    39,   386,
       5,    56,   232,    19,    77,    78,    17,   237,   655,   464,
      21,    30,   561,    15,    30,    31,   469,   470,     1,   406,
     404,    56,   409,    88,   573,   412,    18,   411,   468,    56,
      57,    58,    59,    88,   226,    17,   228,   424,   816,    21,
     232,   819,   115,   821,   679,   237,     3,     4,   435,    56,
      57,    58,    59,    88,   310,   311,   312,   122,   442,    17,
      31,    88,    31,    21,    91,   571,    24,   122,   539,   575,
       5,     6,     7,   108,    32,     9,    34,   464,    22,    37,
      88,    88,   547,    15,    91,    13,   278,   122,   586,   281,
     561,    99,   284,   308,   309,   122,    19,   583,    19,   107,
     108,   117,   573,    13,   610,    11,   561,   613,   596,   597,
     596,   597,   583,   613,   122,   122,    42,    43,   573,    30,
     312,    21,   742,    18,   508,   611,    30,    31,    77,    78,
     679,   387,     3,     4,     3,     4,   638,   874,     3,     4,
     524,   886,   594,   617,   528,   360,   617,   531,    30,    31,
      56,   617,     3,     4,   617,    22,   622,   623,    19,   735,
     626,   754,   617,   628,   813,     5,   754,    73,   360,    75,
     610,    16,   638,   613,     3,     4,    20,   369,   751,     5,
     751,    56,    88,    30,    31,   122,   573,     3,     4,   695,
     574,    30,    31,   645,   646,   387,    71,    72,    30,    74,
      75,    76,   108,     1,   710,   303,   304,   710,   679,   710,
     696,   717,   710,    88,   455,   456,   122,    13,    14,   315,
     316,   687,   798,     9,   679,   699,   321,   322,   699,     8,
     682,   559,   560,   699,    10,    39,   699,    71,   703,   626,
      36,    15,    38,   708,   699,   629,    15,   122,    15,     1,
     442,   638,   636,    30,    22,    30,    14,   641,   749,    14,
     712,    17,    95,    14,    14,    18,    11,    16,     5,   735,
     710,   742,    50,    19,   780,   741,   742,    20,    20,   742,
      34,    35,   747,    37,    16,   751,   792,   742,    21,   792,
      31,   792,   679,    15,     1,    20,    50,     9,    52,    30,
      30,    21,    21,    50,    22,    59,    60,    31,    18,    11,
      21,    56,    59,    60,   128,    21,   128,    21,    21,   128,
       1,   823,   788,   710,   539,   709,    20,    16,    18,   800,
      75,   802,   798,   804,   800,    31,   802,   800,   804,   802,
     806,   804,    20,    88,    31,   800,    30,   802,   735,   804,
     816,    56,   792,   819,    30,   821,    16,   823,    21,   113,
      21,   826,   116,   108,   751,   749,    71,    72,    21,    74,
      75,    76,   837,   844,    21,    16,    31,   122,   844,     1,
     128,   844,   574,    88,   162,    16,    18,    22,    22,   844,
     128,     1,    22,    22,     1,   149,    15,   175,    34,    35,
      16,    37,   119,   108,    30,   792,    30,    22,   162,    22,
      31,   798,     1,   191,    31,   162,    52,   122,     1,   806,
      20,   175,    21,    59,    60,    22,   204,    31,   175,   813,
     203,    22,    22,     1,    16,     1,   823,   191,    30,    20,
     218,   741,    11,    22,   636,   102,    30,    22,    62,    76,
     204,   229,   453,    62,   326,   325,    76,   204,   421,   563,
     567,   329,   216,   217,   218,   564,   806,   403,   114,   113,
     379,   113,   226,   194,   228,   229,   114,   113,   232,   226,
     116,   228,   229,   237,   399,   232,   547,    56,   180,   583,
     237,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    59,    60,   377,   327,   788,   702,   823,   751,
     629,   821,   290,   149,    11,   278,   531,   573,   296,    88,
     679,   464,    -1,    -1,   278,    -1,    -1,   281,    -1,    -1,
     284,   278,    -1,    -1,   281,    -1,    -1,   284,    -1,   108,
      -1,    -1,    -1,    -1,   317,   318,   319,   320,    -1,   303,
     304,    -1,    -1,   122,    -1,   112,   192,   193,    -1,    56,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,   352,    -1,    -1,    -1,    -1,    -1,
     216,   217,    -1,   219,   220,    -1,    -1,    -1,    -1,    -1,
     226,    88,   228,    -1,    56,    -1,   232,    -1,   352,   353,
      -1,   237,    -1,    -1,   382,   352,    -1,    -1,   386,    71,
      72,   108,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
     374,   813,    -1,   401,    -1,   122,    88,    -1,   382,    -1,
      -1,    -1,   386,   406,   412,   382,    -1,    -1,    -1,   386,
     413,    -1,   278,    -1,    -1,   281,   108,    -1,   284,    -1,
     404,   424,    -1,    -1,    -1,    -1,    -1,   411,   412,    -1,
     122,    -1,   435,    -1,    -1,   412,    56,   303,   304,   226,
      -1,   228,    -1,    -1,    -1,   232,    -1,    -1,    -1,    -1,
     237,    71,    72,    -1,    74,    75,    76,    -1,   442,    -1,
     468,   464,    -1,    56,    -1,   442,    -1,    -1,    88,   453,
      -1,    -1,    -1,    -1,    -1,   459,    -1,    -1,    71,    72,
      -1,    74,    75,    76,   468,   469,    -1,   353,   108,    -1,
      -1,   278,    -1,    -1,   281,    88,    -1,   284,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,   374,    -1,
      -1,    -1,    -1,    -1,    -1,   108,   303,   304,    -1,    -1,
      -1,    -1,    -1,    -1,   508,    -1,    -1,    -1,    -1,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   404,    -1,
     524,    -1,    -1,    -1,   528,   411,    -1,   531,    -1,    -1,
      -1,    -1,    -1,   556,   557,   558,   559,   560,   561,   562,
     563,   564,    -1,   566,   567,   568,    11,   570,   355,    -1,
     573,    -1,    -1,    -1,    -1,    -1,   442,    -1,    -1,    -1,
      -1,    -1,   448,   449,    -1,    -1,    -1,   453,    -1,    -1,
     574,    -1,    -1,   459,    -1,    -1,    -1,   574,    -1,   583,
      -1,    -1,   610,   469,   470,   613,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,   610,   611,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    11,   508,    88,    -1,   629,    -1,    -1,    -1,    -1,
      -1,    -1,   636,    -1,   657,   442,    -1,   641,   524,   636,
      -1,    -1,   528,   108,    -1,   531,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   679,   122,    -1,    -1,
     467,   468,   469,   470,    -1,   472,    56,   695,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,   710,    -1,    -1,    -1,    -1,    -1,   574,    -1,
      -1,   695,    -1,    -1,    -1,    -1,    -1,   583,    88,    -1,
      -1,    -1,    -1,    -1,    15,   709,   710,    -1,    -1,    -1,
     596,   597,    23,   710,     5,    -1,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,    -1,   611,    17,    -1,    -1,    40,
      21,    -1,   122,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,   629,    -1,   749,   769,   770,    -1,    -1,
     636,    -1,   780,    -1,    -1,   641,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   792,    56,    -1,   574,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    77,    78,   792,     5,
      -1,    -1,    -1,     9,    -1,   792,    -1,    88,    -1,    -1,
     607,    17,   609,   610,   611,    -1,   613,    -1,    -1,   813,
     696,    -1,    -1,    -1,    -1,    -1,   813,    -1,    -1,    -1,
      -1,    -1,    -1,   709,    11,    -1,    -1,    -1,    -1,   636,
      -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    74,    75,
      76,    77,    78,   749,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,   695,   696,
     697,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,     1,   813,     3,     4,
       5,    -1,    -1,    -1,     9,   122,    11,    12,    88,    -1,
      -1,    -1,    17,    -1,    19,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   122,   780,   781,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   813,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      -1,    96,    97,    98,    99,   100,   101,    -1,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,     1,
     125,     3,     4,     5,    -1,    -1,    -1,     9,    15,    11,
      12,    -1,    -1,    -1,    16,    17,    23,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    34,    40,    -1,    37,    -1,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,
      -1,   103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,
     112,    -1,   114,   115,   116,    -1,   118,    -1,   120,   121,
     122,   123,     1,   125,     3,     4,     5,    -1,    -1,    -1,
       9,    -1,    11,    12,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    34,    56,    -1,    37,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    -1,    -1,    96,    -1,    -1,
      99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,
     109,    -1,   111,   112,    -1,   114,   115,   116,    -1,   118,
      -1,   120,   121,   122,   123,     1,   125,     3,     4,     5,
      -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,    -1,
      -1,    17,    -1,    -1,    -1,    21,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    -1,    34,    -1,
      -1,    37,    -1,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,    86,    87,    -1,    89,    -1,    91,    -1,    55,
      56,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    74,    75,
      76,    77,    78,    79,    80,    -1,    82,    83,    84,    85,
      86,    87,    88,    89,    -1,    91,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,    -1,
      -1,   107,   108,   109,    -1,   111,   112,    -1,   114,   115,
     116,    -1,   118,    -1,   120,   121,   122,   123,     1,   125,
       3,     4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,
      -1,    -1,    -1,    -1,    17,    -1,    19,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,
     103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,
      -1,   114,   115,   116,    -1,   118,    -1,   120,   121,   122,
     123,    -1,   125,     3,     4,     5,    -1,    -1,    -1,     9,
      -1,    11,    12,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    -1,    -1,    -1,    96,    -1,    -1,    99,
      -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,
      -1,   111,   112,    -1,   114,   115,   116,    -1,   118,    -1,
     120,   121,   122,   123,    -1,   125,     3,     4,     5,    -1,
      -1,    -1,     9,    -1,    11,    12,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    74,    75,    76,
      77,    78,    79,    80,    -1,    82,    83,    84,    85,    86,
      87,    88,    89,    -1,    91,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    99,    -1,   101,    -1,   103,    -1,    -1,    -1,
     107,   108,   109,    -1,   111,   112,    -1,   114,   115,   116,
      -1,   118,    -1,   120,   121,   122,   123,    -1,   125,     3,
       4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      74,    75,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    91,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,
      -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,
     114,   115,   116,    -1,   118,    -1,   120,   121,   122,   123,
      -1,   125,     3,     4,     5,    -1,    -1,    -1,     9,    -1,
      11,    12,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    77,    78,    79,    80,
      -1,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      91,    -1,    -1,    -1,    -1,    96,    -1,    -1,    99,    -1,
     101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,    -1,
     111,   112,    -1,   114,   115,   116,    -1,   118,    -1,   120,
     121,   122,   123,    -1,   125,     3,     4,     5,    -1,    -1,
      -1,     9,    -1,    11,    12,    -1,    14,    -1,    -1,    17,
      -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    74,    75,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    91,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,
     108,   109,    -1,   111,   112,    -1,   114,   115,   116,    -1,
     118,    -1,   120,   121,   122,   123,    -1,   125,     3,     4,
       5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,    14,
      -1,    -1,    17,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    78,    79,    80,    -1,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    91,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
     115,   116,    -1,   118,    -1,   120,   121,   122,   123,    -1,
     125,     3,     4,     5,    -1,    -1,    -1,     9,    -1,    11,
      12,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    74,    75,    76,    77,    78,    79,    80,    -1,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    91,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,
      -1,   103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,
     112,    -1,   114,   115,   116,    -1,   118,    -1,   120,   121,
     122,   123,    -1,   125,     3,     4,     5,    -1,    -1,    -1,
       9,    -1,    11,    12,    -1,    -1,    -1,    -1,    17,    -1,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    74,    75,    76,    77,    78,
      79,    80,    -1,    82,    83,    84,    85,    86,    87,    88,
      89,    -1,    91,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,
     109,    -1,   111,   112,    -1,   114,   115,   116,    -1,   118,
      -1,   120,   121,   122,   123,    -1,   125,     3,     4,     5,
      -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,    -1,
      -1,    17,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    74,    75,
      76,    77,    78,    79,    80,    -1,    82,    83,    84,    85,
      86,    87,    88,    89,    -1,    91,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,    -1,
      -1,   107,   108,   109,    -1,   111,   112,    -1,   114,   115,
     116,    -1,   118,    -1,   120,   121,   122,   123,    -1,   125,
       3,     4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,
      -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,
     103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,
      -1,   114,    -1,   116,    -1,   118,    -1,   120,   121,   122,
     123,    -1,   125,     3,     4,     5,    -1,    -1,    -1,     9,
      -1,    11,    12,    -1,    -1,    -1,    -1,    17,    -1,    19,
      -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    99,
      -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,
      -1,   111,   112,    -1,   114,   115,   116,    -1,   118,    -1,
     120,   121,   122,   123,    -1,   125,     3,     4,     5,    -1,
      -1,    -1,     9,    -1,    11,    12,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    99,    -1,   101,    -1,   103,    -1,    -1,    -1,
     107,   108,   109,    -1,   111,   112,    -1,   114,   115,   116,
      -1,   118,    -1,   120,   121,   122,   123,    -1,   125,     3,
       4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,
      -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,
     114,   115,   116,    -1,   118,    -1,   120,   121,   122,   123,
      -1,   125,     3,     4,     5,    -1,    -1,    -1,     9,    -1,
      11,    12,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    99,    -1,
     101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,    -1,
     111,   112,    -1,   114,   115,   116,    -1,   118,    -1,   120,
     121,   122,   123,    -1,   125,     3,     4,     5,    -1,    -1,
      -1,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,    17,
      18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,
     108,   109,    -1,   111,   112,    -1,   114,    -1,   116,    -1,
     118,    -1,   120,   121,   122,   123,    -1,   125,     3,     4,
       5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    17,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
      -1,   116,    -1,   118,    -1,   120,   121,   122,   123,    -1,
     125,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    17,    -1,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,     5,    -1,    56,    -1,     9,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,    21,    -1,
      -1,    -1,    -1,    56,    -1,   107,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
     122,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    88,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    21,    -1,    -1,   122,
      -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,
     103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,
      -1,   114,    -1,   116,    -1,   118,    -1,   120,   121,   122,
     123,    56,   125,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    78,    79,    80,    -1,    82,    83,    84,
      85,    86,    87,    88,    89,    21,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,
      56,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    -1,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      74,    75,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,    86,    87,    88,    89,    21,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,   122,    -1,
      -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    22,    -1,    88,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    -1,    56,    -1,   122,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,   108,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,   122,    88,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
     122,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,   108,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,   122,    74,    75,    76,    77,    78,    79,
      80,    -1,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,   108,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,   122,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    88,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   150,   209,     0,   339,   210,   338,   128,     1,     3,
       4,     5,     9,    11,    12,    16,    17,    21,    30,    34,
      37,    56,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    96,    99,   101,   103,   107,
     108,   109,   111,   112,   114,   115,   116,   118,   120,   121,
     122,   123,   125,   130,   131,   132,   134,   135,   136,   137,
     139,   140,   141,   147,   148,   149,   151,   152,   155,   158,
     159,   160,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   227,   228,   229,   231,   233,   234,   235,   236,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     259,   264,   265,   274,   275,   276,   277,   287,   288,   289,
     290,   299,   301,   305,   313,   315,   316,   321,   324,   329,
     333,   334,    88,   165,   165,   165,   165,   176,   300,   157,
     178,   180,   181,    55,    82,    88,   167,   172,   178,   227,
     255,   256,   266,   267,   268,   269,   270,   271,   165,   165,
      19,    88,   134,   135,   137,   237,    19,   137,   208,   137,
      88,   315,   147,    13,    88,   131,   134,   139,   213,   215,
     218,   227,   231,   264,   321,    11,    73,    75,    88,   134,
     135,   137,   138,   141,   142,    21,    13,   165,    13,    88,
     137,   161,   230,   231,   232,   233,   259,   265,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    17,    21,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    99,   107,   230,   306,
     314,    13,   152,   158,    13,   178,   265,    13,   133,    56,
      88,   136,   140,   159,   160,   254,    88,   136,   138,   140,
     254,   165,    17,    24,    32,    34,    37,   264,    33,    54,
       6,     7,   253,     3,     4,    42,    43,    13,    14,    36,
      38,    35,    41,     9,     8,    10,    39,    15,    23,    40,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
     179,    16,    19,    31,   117,   199,   278,   280,   225,   226,
     233,    56,    88,   221,   222,   217,   226,    56,   141,   220,
     253,   216,   275,   276,    30,    31,    30,   259,   165,   258,
      31,   278,   280,   291,    16,    19,   137,    15,   212,     3,
       4,     1,    88,    23,    31,    18,    88,   253,     9,   271,
     256,    22,    31,    55,    15,    20,   238,   240,   241,   242,
     334,    88,   237,   336,    15,   208,    13,   208,   210,    14,
      71,    75,    88,   115,   169,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   227,   268,   272,   273,   316,   317,
     318,   319,   320,   330,   334,    13,   132,   137,   142,   138,
      30,   147,   230,   260,   260,    21,   164,    17,   134,   135,
     161,   162,   163,   255,   257,   161,   265,    18,    22,   255,
     257,   306,   260,   260,     3,     4,   180,    11,    88,   134,
     135,   142,   143,   144,   145,   146,   233,   142,   146,   154,
     165,   165,   166,   166,   166,   167,   167,   168,   168,   169,
     169,   169,   169,   170,   170,   171,   172,   173,   174,    19,
     282,   181,   175,   178,   300,   200,   178,   252,    16,   279,
     307,   308,    56,   165,   252,   115,   259,   331,   178,    20,
     339,    57,    58,    59,    91,   137,   302,   303,   304,    16,
      19,   286,   178,   281,   282,   211,    30,   300,   178,   255,
     257,   268,   271,   178,   131,   243,   244,    31,   238,   334,
       1,   209,   137,   212,   185,   191,    13,    36,    38,    35,
      41,     9,     8,    10,    39,    15,    23,    40,   179,   272,
      15,    71,    14,    31,    15,    15,     1,   272,   322,   323,
      30,    30,    22,   255,   260,   261,   262,   263,    14,    14,
     156,   157,   178,   181,    17,   132,   134,   135,   162,   257,
     164,   164,    14,    14,    14,   322,    18,   143,   144,    11,
      88,   134,   146,    88,   145,    56,   233,     3,     4,    20,
     283,   284,   337,    16,    20,   194,   337,   137,   309,   310,
     311,   312,    95,   326,   327,   280,    21,   292,   337,   303,
      19,    31,   303,     1,   302,    16,    15,    20,   239,   240,
     334,     1,    20,    31,    20,   339,    30,     9,   169,   169,
     169,   183,   183,   184,   268,   185,   186,   187,   191,   192,
     193,   188,   191,   191,   131,   318,   260,   131,    14,    31,
      30,   261,    17,   264,    21,    21,    22,    31,    18,   176,
     177,   182,    21,    21,    14,    88,   135,    11,     1,   153,
     267,    20,    31,   128,   281,   285,   333,   178,   128,    73,
      88,    93,    94,    97,    98,   100,   104,   105,   106,   110,
     113,   117,   119,   130,   178,   195,   196,   197,   198,   199,
     201,   204,   206,   207,   214,   227,   325,   333,    31,   334,
     311,    21,    21,   326,    22,   260,   332,   128,    30,    90,
     178,   227,   247,   274,   277,   293,   294,   295,   296,   298,
     304,   315,   333,   303,    19,   300,   182,     1,   210,    16,
      31,   323,    18,   182,   181,   181,   178,    18,   181,   181,
      88,   143,   267,   335,    30,    20,   284,   334,     3,     4,
     334,   137,    88,    30,   182,    30,    16,   194,    21,   131,
      21,   180,    21,   199,    21,    16,     3,     4,     1,   156,
     271,   328,    22,    31,   334,    30,    31,   295,    30,    31,
      30,    31,    16,     3,     4,    20,   128,   191,   191,    18,
      22,    22,    22,    22,    30,     1,    19,   128,     1,   285,
       1,    16,   194,   119,   205,   216,    30,   203,   267,    30,
     203,   326,   203,   194,   195,    31,    22,    22,   260,     1,
     178,   297,   301,   178,   301,   297,   293,   334,     1,   334,
      20,    20,    30,   194,    21,   202,   203,    22,    22,    22,
     199,    20,    30,     1,     1,   181,    30,   194,   194,   194,
      20,    20,    22,   180,   102,    30,    22,   194,   194
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

    { (yyval.name) = (yyvsp[(1) - (1)].identifier); }
    break;

  case 4:

    { (yyval.name) = YACC_NAME((yyvsp[(1) - (1)].name)); }
    break;

  case 5:

    { (yyval.name) = YACC_TEMPLATE_NAME((yyvsp[(1) - (5)].name), (yyvsp[(4) - (5)].template_arguments)); }
    break;

  case 6:

    { (yyval.name) = (yyvsp[(1) - (4)].name); ERRMSG("Empty template-argument-list"); }
    break;

  case 7:

    { (yyval.name) = YACC_NAME((yyvsp[(1) - (3)].name)); }
    break;

  case 9:

    { template_test(); }
    break;

  case 10:

    { (yyval.is_template) = IS_DEFAULT; }
    break;

  case 11:

    { (yyval.is_template) = IS_TEMPLATE; }
    break;

  case 12:

    { (yyval.name) = YACC_NESTED_SCOPE((yyvsp[(1) - (2)].name)); }
    break;

  case 14:

    { (yyval.name) = YACC_NESTED_ID((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].name)); }
    break;

  case 16:

    { (yyval.name) = YACC_GLOBAL_ID((yyvsp[(1) - (2)].is_template), (yyvsp[(2) - (2)].name)); }
    break;

  case 17:

    { (yyval.name) = YACC_DESTRUCTOR_ID((yyvsp[(2) - (2)].name)); }
    break;

  case 18:

    { (yyval.name) = YACC_SET_TEMPLATE_ID((yyvsp[(2) - (2)].name)); }
    break;

  case 21:

    { (yyval.name) = YACC_SET_TEMPLATE_ID((yyvsp[(2) - (2)].name)); }
    break;

  case 23:

    { (yyval.name) = YACC_NESTED_ID((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].name)); }
    break;

  case 24:

    { (yyval.name) = YACC_NESTED_ID((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].name)); }
    break;

  case 26:

    { (yyval.name) = YACC_GLOBAL_ID((yyvsp[(1) - (2)].is_template), (yyvsp[(2) - (2)].name)); }
    break;

  case 31:

    { (yyval.built_in_id) = YACC_BUILT_IN_IDS((yyvsp[(1) - (2)].built_in_id), (yyvsp[(2) - (2)].built_in_id)); }
    break;

  case 32:

    { (yyval.name) = YACC_PSEUDO_DESTRUCTOR_ID((yyvsp[(1) - (4)].built_in_id), (yyvsp[(4) - (4)].built_in_id)); }
    break;

  case 33:

    { (yyval.name) = YACC_PSEUDO_DESTRUCTOR_ID(0, (yyvsp[(2) - (2)].built_in_id)); }
    break;

  case 34:

    { (yyval.name) = YACC_SET_TEMPLATE_ID((yyvsp[(2) - (2)].name)); }
    break;

  case 36:

    { (yyval.name) = YACC_NESTED_ID((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].name)); }
    break;

  case 38:

    { (yyval.name) = YACC_GLOBAL_ID((yyvsp[(1) - (2)].is_template), (yyvsp[(2) - (2)].name)); }
    break;

  case 39:

    { (yyval.strings) = (yyvsp[(1) - (1)].string_literal); }
    break;

  case 40:

    { (yyval.expression) = YACC_INTEGER_LITERAL_EXPRESSION((yyvsp[(1) - (1)].integer_literal)); }
    break;

  case 41:

    { (yyval.expression) = YACC_CHARACTER_LITERAL_EXPRESSION((yyvsp[(1) - (1)].character_literal)); }
    break;

  case 42:

    { (yyval.expression) = YACC_FLOATING_LITERAL_EXPRESSION((yyvsp[(1) - (1)].floating_literal)); }
    break;

  case 43:

    { (yyval.expression) = YACC_STRING_LITERAL_EXPRESSION((yyvsp[(1) - (1)].strings)); }
    break;

  case 45:

    { (yyval.expression) = YACC_FALSE_EXPRESSION(); }
    break;

  case 46:

    { (yyval.expression) = YACC_TRUE_EXPRESSION(); }
    break;

  case 47:

    { YACC_RESULT((yyvsp[(1) - (1)].declarations)); }
    break;

  case 49:

    { (yyval.expression) = YACC_THIS_EXPRESSION(); }
    break;

  case 50:

    { (yyval.expression) = (yyvsp[(1) - (1)].name); }
    break;

  case 52:

    { (yyval.expression) = YACC_ABSTRACT_FUNCTION_EXPRESSION((yyvsp[(1) - (1)].parenthesised)); }
    break;

  case 53:

    { (yyval.expression) = YACC_ABSTRACT_ARRAY_EXPRESSION((yyvsp[(2) - (3)].expression)); }
    break;

  case 54:

    { (yyval.expression) = YACC_SET_TEMPLATE_EXPRESSION(YACC_ABSTRACT_FUNCTION_EXPRESSION((yyvsp[(2) - (2)].parenthesised))); }
    break;

  case 55:

    { (yyval.type1_parameters) = YACC_TYPE1_PARAMETERS(0, (yyvsp[(1) - (2)].parameters)); }
    break;

  case 56:

    { (yyval.type1_parameters) = YACC_TYPE1_PARAMETERS((yyvsp[(1) - (3)].type1_parameters), (yyvsp[(2) - (3)].parameters)); }
    break;

  case 57:

    { (yyval.mark) = mark_type1(); }
    break;

  case 59:

    { (yyval.expression) = YACC_CALL_EXPRESSION((yyvsp[(1) - (4)].expression), (yyvsp[(2) - (4)].parenthesised)); }
    break;

  case 60:

    { yyerrok; remark_type1((yyvsp[(6) - (8)].mark)); unmark(); unmark((yyvsp[(5) - (8)].type1_parameters)); (yyval.expression) = YACC_TYPE1_EXPRESSION((yyvsp[(1) - (8)].expression), (yyvsp[(2) - (8)].parenthesised), (yyvsp[(5) - (8)].type1_parameters)); }
    break;

  case 61:

    { yyerrok; remark_type1((yyvsp[(3) - (7)].mark)); unmark(); unmark(); (yyval.expression) = YACC_CALL_EXPRESSION((yyvsp[(1) - (7)].expression), (yyvsp[(2) - (7)].parenthesised)); }
    break;

  case 62:

    { yyerrok; remark_type1((yyvsp[(3) - (5)].mark)); unmark(); (yyval.expression) = YACC_CALL_EXPRESSION((yyvsp[(1) - (5)].expression), (yyvsp[(2) - (5)].parenthesised)); }
    break;

  case 63:

    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression)); }
    break;

  case 64:

    { (yyval.expression) = YACC_DOT_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].name)); }
    break;

  case 65:

    { (yyval.expression) = YACC_DOT_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].name)); }
    break;

  case 66:

    { (yyval.expression) = YACC_ARROW_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].name)); }
    break;

  case 67:

    { (yyval.expression) = YACC_ARROW_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].name)); }
    break;

  case 68:

    { (yyval.expression) = YACC_POST_INCREMENT_EXPRESSION((yyvsp[(1) - (2)].expression)); }
    break;

  case 69:

    { (yyval.expression) = YACC_POST_DECREMENT_EXPRESSION((yyvsp[(1) - (2)].expression)); }
    break;

  case 70:

    { (yyval.expression) = YACC_DYNAMIC_CAST_EXPRESSION((yyvsp[(3) - (7)].expression), (yyvsp[(6) - (7)].expression)); }
    break;

  case 71:

    { (yyval.expression) = YACC_STATIC_CAST_EXPRESSION((yyvsp[(3) - (7)].expression), (yyvsp[(6) - (7)].expression)); }
    break;

  case 72:

    { (yyval.expression) = YACC_REINTERPRET_CAST_EXPRESSION((yyvsp[(3) - (7)].expression), (yyvsp[(6) - (7)].expression)); }
    break;

  case 73:

    { (yyval.expression) = YACC_CONST_CAST_EXPRESSION((yyvsp[(3) - (7)].expression), (yyvsp[(6) - (7)].expression)); }
    break;

  case 74:

    { (yyval.expression) = YACC_TYPEID_EXPRESSION((yyvsp[(2) - (2)].parameters)); }
    break;

  case 75:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, 0); }
    break;

  case 77:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yyvsp[(1) - (1)].expression)); }
    break;

  case 78:

    { (yyval.expressions) = YACC_EXPRESSIONS((yyvsp[(1) - (3)].expressions), (yyvsp[(3) - (3)].expression)); }
    break;

  case 80:

    { (yyval.expression) = YACC_PRE_INCREMENT_EXPRESSION((yyvsp[(2) - (2)].expression)); }
    break;

  case 81:

    { (yyval.expression) = YACC_PRE_DECREMENT_EXPRESSION((yyvsp[(2) - (2)].expression)); }
    break;

  case 82:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yyvsp[(1) - (2)].declarator), (yyvsp[(2) - (2)].expression)); }
    break;

  case 83:

    { (yyval.expression) = YACC_SCOPED_POINTER_EXPRESSION((yyvsp[(1) - (3)].name), (yyvsp[(2) - (3)].pointer_declarator), (yyvsp[(3) - (3)].expression)); }
    break;

  case 84:

    { (yyval.expression) = YACC_PLUS_EXPRESSION((yyvsp[(2) - (2)].expression)); }
    break;

  case 85:

    { (yyval.expression) = YACC_MINUS_EXPRESSION((yyvsp[(2) - (2)].expression)); }
    break;

  case 86:

    { (yyval.expression) = YACC_NOT_EXPRESSION((yyvsp[(2) - (2)].expression)); }
    break;

  case 87:

    { (yyval.expression) = YACC_COMPLEMENT_EXPRESSION((yyvsp[(2) - (2)].expression)); }
    break;

  case 88:

    { (yyval.expression) = YACC_SIZEOF_EXPRESSION((yyvsp[(2) - (2)].expression)); }
    break;

  case 89:

    { (yyval.expression) = (yyvsp[(1) - (1)].new_expression); }
    break;

  case 90:

    { (yyval.expression) = YACC_GLOBAL_EXPRESSION((yyvsp[(1) - (2)].is_template), (yyvsp[(2) - (2)].new_expression)); }
    break;

  case 91:

    { (yyval.expression) = (yyvsp[(1) - (1)].delete_expression); }
    break;

  case 92:

    { (yyval.expression) = YACC_GLOBAL_EXPRESSION((yyvsp[(1) - (2)].is_template), (yyvsp[(2) - (2)].delete_expression)); }
    break;

  case 93:

    { (yyval.delete_expression) = YACC_DELETE_EXPRESSION((yyvsp[(2) - (2)].expression)); }
    break;

  case 94:

    { (yyval.new_expression) = YACC_NEW_TYPE_ID_EXPRESSION(0, (yyvsp[(2) - (3)].expression), (yyvsp[(3) - (3)].expressions)); }
    break;

  case 95:

    { (yyval.new_expression) = YACC_NEW_TYPE_ID_EXPRESSION((yyvsp[(2) - (4)].parameters), (yyvsp[(3) - (4)].expression), (yyvsp[(4) - (4)].expressions)); }
    break;

  case 96:

    { (yyval.new_expression) = YACC_NEW_EXPRESSION((yyvsp[(2) - (2)].parameters), 0, 0); }
    break;

  case 97:

    { (yyval.new_expression) = YACC_NEW_EXPRESSION((yyvsp[(2) - (4)].parameters), (yyvsp[(3) - (4)].parameters), (yyvsp[(4) - (4)].expressions)); }
    break;

  case 98:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].expression)); }
    break;

  case 99:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].expression)); }
    break;

  case 100:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].expression)); }
    break;

  case 101:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yyvsp[(1) - (2)].declarator), (yyvsp[(2) - (2)].expression)); }
    break;

  case 103:

    { (yyval.expression) = YACC_ABSTRACT_ARRAY_EXPRESSION((yyvsp[(2) - (3)].expression)); }
    break;

  case 104:

    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression)); }
    break;

  case 105:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, 0); }
    break;

  case 106:

    { (yyval.expressions) = (yyvsp[(2) - (3)].expressions); }
    break;

  case 108:

    { (yyval.expression) = YACC_CAST_EXPRESSION((yyvsp[(1) - (2)].expression), (yyvsp[(2) - (2)].expression)); }
    break;

  case 110:

    { (yyval.expression) = YACC_DOT_STAR_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 111:

    { (yyval.expression) = YACC_ARROW_STAR_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 113:

    { (yyval.expression) = YACC_MULTIPLY_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].pointer_declarator), (yyvsp[(3) - (3)].expression)); }
    break;

  case 114:

    { (yyval.expression) = YACC_DIVIDE_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 115:

    { (yyval.expression) = YACC_MODULUS_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 117:

    { (yyval.expression) = YACC_ADD_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 118:

    { (yyval.expression) = YACC_SUBTRACT_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 120:

    { (yyval.expression) = YACC_SHIFT_LEFT_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 121:

    { (yyval.expression) = YACC_SHIFT_RIGHT_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 123:

    { (yyval.expression) = YACC_LESS_THAN_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 124:

    { (yyval.expression) = YACC_GREATER_THAN_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 125:

    { (yyval.expression) = YACC_LESS_EQUAL_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 126:

    { (yyval.expression) = YACC_GREATER_EQUAL_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 128:

    { (yyval.expression) = YACC_EQUAL_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 129:

    { (yyval.expression) = YACC_NOT_EQUAL_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 131:

    { (yyval.expression) = YACC_AND_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 133:

    { (yyval.expression) = YACC_EXCLUSIVE_OR_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 135:

    { (yyval.expression) = YACC_INCLUSIVE_OR_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 137:

    { (yyval.expression) = YACC_LOGICAL_AND_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 139:

    { (yyval.expression) = YACC_LOGICAL_OR_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 141:

    { (yyval.expression) = YACC_CONDITIONAL_EXPRESSION((yyvsp[(1) - (5)].expression), (yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].expression)); }
    break;

  case 143:

    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].keyword), (yyvsp[(3) - (3)].expression)); }
    break;

  case 144:

    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].keyword), (yyvsp[(3) - (3)].initializer_clause)); }
    break;

  case 157:

    { (yyval.expression) = YACC_EXPRESSION(0); }
    break;

  case 160:

    { (yyval.expression) = YACC_EXPRESSION(YACC_EXPRESSIONS((yyvsp[(1) - (3)].expressions), (yyvsp[(3) - (3)].expression))); }
    break;

  case 163:

    { (yyval.expression) = YACC_LESS_THAN_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 164:

    { (yyval.expression) = YACC_LESS_EQUAL_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 165:

    { (yyval.expression) = YACC_GREATER_EQUAL_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 167:

    { (yyval.expression) = YACC_EQUAL_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 168:

    { (yyval.expression) = YACC_NOT_EQUAL_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 170:

    { (yyval.expression) = YACC_AND_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 172:

    { (yyval.expression) = YACC_EXCLUSIVE_OR_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 174:

    { (yyval.expression) = YACC_INCLUSIVE_OR_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 176:

    { (yyval.expression) = YACC_LOGICAL_AND_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 178:

    { (yyval.expression) = YACC_LOGICAL_OR_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 180:

    { (yyval.expression) = YACC_CONDITIONAL_EXPRESSION((yyvsp[(1) - (5)].expression), (yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].expression)); }
    break;

  case 182:

    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].keyword), (yyvsp[(3) - (3)].expression)); }
    break;

  case 185:

    { (yyval.expression) = YACC_EXPRESSION(YACC_EXPRESSIONS((yyvsp[(1) - (3)].expressions), (yyvsp[(3) - (3)].expression))); }
    break;

  case 186:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yyvsp[(1) - (1)].expression)); }
    break;

  case 187:

    { (yyval.expressions) = YACC_EXPRESSIONS((yyvsp[(1) - (3)].expressions), (yyvsp[(3) - (3)].expression)); }
    break;

  case 188:

    { (yyval.statement) = YACC_LINED_STATEMENT((yyvsp[(2) - (2)].statement), (yyvsp[(1) - (2)].line)); end_search((yyval.statement)); }
    break;

  case 190:

    { (yyval.statement) = (yyvsp[(3) - (3)].statement); }
    break;

  case 191:

    { (yyval.statement) = 0; }
    break;

  case 195:

    { (yyval.statement) = YACC_TRY_BLOCK_STATEMENT((yyvsp[(1) - (1)].function_body)); }
    break;

  case 200:

    { (yyval.statement) = YACC_LABEL_STATEMENT((yyvsp[(1) - (3)].name), (yyvsp[(3) - (3)].statement)); }
    break;

  case 201:

    { (yyval.statement) = YACC_CASE_STATEMENT((yyvsp[(2) - (4)].expression), (yyvsp[(4) - (4)].statement)); }
    break;

  case 202:

    { (yyval.statement) = YACC_DEFAULT_STATEMENT((yyvsp[(3) - (3)].statement)); }
    break;

  case 203:

    { (yyval.statement) = YACC_COMPOUND_STATEMENT((yyvsp[(2) - (3)].statements)); }
    break;

  case 204:

    { (yyval.statement) = (yyvsp[(2) - (7)].statements); YACC_UNBANG((yyvsp[(5) - (7)].bang), "Bad statement-seq."); }
    break;

  case 205:

    { (yyval.statements) = YACC_STATEMENTS(0, 0); }
    break;

  case 206:

    { (yyval.statements) = YACC_STATEMENTS((yyvsp[(1) - (2)].statements), YACC_COMPILE_STATEMENT((yyvsp[(2) - (2)].statement))); }
    break;

  case 207:

    { (yyval.statements) = (yyvsp[(1) - (6)].statements); YACC_UNBANG((yyvsp[(4) - (6)].bang), "Bad statement."); }
    break;

  case 208:

    { (yyval.statement) = YACC_IF_STATEMENT((yyvsp[(3) - (5)].condition), (yyvsp[(5) - (5)].statement), 0); }
    break;

  case 209:

    { (yyval.statement) = YACC_IF_STATEMENT((yyvsp[(3) - (7)].condition), (yyvsp[(5) - (7)].statement), (yyvsp[(7) - (7)].statement)); }
    break;

  case 210:

    { (yyval.statement) = YACC_SWITCH_STATEMENT((yyvsp[(3) - (5)].condition), (yyvsp[(5) - (5)].statement)); }
    break;

  case 211:

    { (yyval.condition) = YACC_CONDITION(0); }
    break;

  case 213:

    { (yyval.condition) = YACC_CONDITION((yyvsp[(1) - (1)].parameters)); }
    break;

  case 214:

    { (yyval.statement) = YACC_WHILE_STATEMENT((yyvsp[(3) - (5)].condition), (yyvsp[(5) - (5)].statement)); }
    break;

  case 215:

    { (yyval.statement) = YACC_DO_WHILE_STATEMENT((yyvsp[(2) - (7)].statement), (yyvsp[(5) - (7)].expression)); }
    break;

  case 216:

    { (yyval.statement) = YACC_FOR_STATEMENT((yyvsp[(3) - (8)].expression), (yyvsp[(4) - (8)].condition), (yyvsp[(6) - (8)].expression), (yyvsp[(8) - (8)].statement)); }
    break;

  case 218:

    { (yyval.statement) = YACC_BREAK_STATEMENT(); }
    break;

  case 219:

    { (yyval.statement) = YACC_CONTINUE_STATEMENT(); }
    break;

  case 220:

    { (yyval.statement) = YACC_RETURN_STATEMENT((yyvsp[(2) - (3)].expression)); }
    break;

  case 221:

    { (yyval.statement) = YACC_GOTO_STATEMENT((yyvsp[(2) - (3)].name)); }
    break;

  case 222:

    { (yyval.statement) = YACC_DECLARATION_STATEMENT((yyvsp[(1) - (1)].declaration)); }
    break;

  case 223:

    { (yyval.declarations) = (yyvsp[(3) - (4)].declarations); unnest((yyvsp[(2) - (4)].nest)); }
    break;

  case 224:

    { (yyval.declarations) = (yyvsp[(3) - (9)].declarations); unnest((yyvsp[(2) - (9)].nest)); YACC_UNBANG((yyvsp[(7) - (9)].bang), "Bad declaration-seq."); }
    break;

  case 225:

    { (yyval.declarations) = YACC_DECLARATIONS(0, 0); }
    break;

  case 226:

    { (yyval.declarations) = YACC_DECLARATIONS((yyvsp[(1) - (3)].declarations), YACC_COMPILE_DECLARATION((yyvsp[(2) - (3)].utility), (yyvsp[(3) - (3)].declaration))); }
    break;

  case 227:

    { (yyval.declarations) = (yyvsp[(1) - (7)].declarations); YACC_UNBANG((yyvsp[(5) - (7)].bang), "Bad declaration."); }
    break;

  case 228:

    { (yyval.declaration) = YACC_LINED_DECLARATION((yyvsp[(2) - (2)].declaration), (yyvsp[(1) - (2)].line)); end_search((yyval.declaration)); }
    break;

  case 230:

    { (yyval.declaration) = (yyvsp[(3) - (3)].declaration); }
    break;

  case 231:

    { (yyval.declaration) = 0; }
    break;

  case 233:

    { (yyval.declaration) = YACC_SIMPLE_DECLARATION((yyvsp[(1) - (1)].expression)); }
    break;

  case 237:

    { (yyval.declaration) = YACC_LINKAGE_SPECIFICATION((yyvsp[(1) - (1)].name)); }
    break;

  case 238:

    { (yyval.declaration) = YACC_NAMESPACE_DECLARATION((yyvsp[(1) - (1)].name)); }
    break;

  case 239:

    { (yyval.declaration) = YACC_SET_TEMPLATE_DECLARATION((yyvsp[(2) - (2)].declaration)); }
    break;

  case 240:

    { (yyval.declaration) = YACC_SIMPLE_DECLARATION((yyvsp[(1) - (1)].expression)); }
    break;

  case 246:

    { (yyval.declaration) = YACC_SET_TEMPLATE_DECLARATION((yyvsp[(2) - (2)].declaration)); }
    break;

  case 247:

    { (yyval.expression) = YACC_EXPRESSION(0); }
    break;

  case 249:

    { (yyval.expression) = (yyvsp[(1) - (2)].expressions); }
    break;

  case 250:

    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yyvsp[(2) - (2)].expression), (yyvsp[(1) - (2)].decl_specifier_id)); }
    break;

  case 251:

    { (yyval.name) = (yyvsp[(1) - (1)].built_in_id); }
    break;

  case 252:

    { (yyval.name) = YACC_BUILT_IN_NAME((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].built_in_id)); }
    break;

  case 253:

    { (yyval.name) = YACC_DECL_SPECIFIER_NAME((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].decl_specifier_id)); }
    break;

  case 254:

    { (yyval.name) = (yyvsp[(1) - (1)].name); }
    break;

  case 255:

    { (yyval.name) = YACC_SET_TEMPLATE_NAME((yyvsp[(2) - (2)].name)); }
    break;

  case 256:

    { (yyval.name) = (yyvsp[(1) - (1)].name); }
    break;

  case 257:

    { (yyval.name) = (yyvsp[(1) - (1)].name); }
    break;

  case 258:

    { (yyval.name) = YACC_DECL_SPECIFIER_NAME((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].decl_specifier_id)); }
    break;

  case 259:

    { (yyval.name) = YACC_NAME_EXPRESSION((yyvsp[(1) - (1)].name)); }
    break;

  case 260:

    { (yyval.name) = YACC_TYPED_NAME((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].name)); }
    break;

  case 262:

    { (yyval.name) = YACC_TYPED_NAME((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].name)); }
    break;

  case 263:

    { (yyval.name) = YACC_NAME_EXPRESSION((yyvsp[(1) - (1)].name)); }
    break;

  case 265:

    { (yyval.name) = YACC_TYPED_NAME((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].name)); }
    break;

  case 267:

    { (yyval.name) = YACC_TYPED_NAME((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].name)); }
    break;

  case 270:

    { (yyval.name) = YACC_TYPED_NAME((yyvsp[(1) - (3)].name), (yyvsp[(2) - (3)].name)); }
    break;

  case 271:

    { (yyval.name) = YACC_NAME_EXPRESSION((yyvsp[(1) - (2)].name)); }
    break;

  case 276:

    { (yyval.decl_specifier_id) = (yyvsp[(1) - (1)].cv_qualifiers); }
    break;

  case 279:

    { (yyval.decl_specifier_id) = YACC_SET_TEMPLATE_DECL_SPECIFIER((yyvsp[(2) - (2)].decl_specifier_id)); }
    break;

  case 290:

    { (yyval.name) = YACC_CV_DECL_SPECIFIER((yyvsp[(1) - (1)].cv_qualifiers)); }
    break;

  case 294:

    { (yyval.name) = YACC_SET_TEMPLATE_ID((yyvsp[(2) - (2)].name)); }
    break;

  case 296:

    { (yyval.name) = YACC_BUILT_IN_ID_ID((yyvsp[(1) - (1)].built_in_id)); }
    break;

  case 310:

    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yyvsp[(1) - (2)].class_key), (yyvsp[(2) - (2)].name)); }
    break;

  case 311:

    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yyvsp[(1) - (2)].class_key), (yyvsp[(2) - (2)].name)); }
    break;

  case 312:

    { (yyval.name) = YACC_ENUM_SPECIFIER_ID((yyvsp[(2) - (3)].name), (yyvsp[(3) - (3)].enumerators)); }
    break;

  case 313:

    { (yyval.name) = YACC_ENUM_SPECIFIER_ID(0, (yyvsp[(2) - (2)].enumerators)); }
    break;

  case 314:

    { (yyval.enumerators) = YACC_ENUMERATORS(0, 0); }
    break;

  case 315:

    { (yyval.enumerators) = (yyvsp[(2) - (3)].enumerators); }
    break;

  case 316:

    { (yyval.enumerators) = (yyvsp[(2) - (4)].enumerators); }
    break;

  case 317:

    { }
    break;

  case 318:

    { YACC_UNBANG((yyvsp[(1) - (3)].bang), "Bad enumerator-list."); }
    break;

  case 319:

    { }
    break;

  case 320:

    { YACC_UNBANG((yyvsp[(1) - (3)].bang), "Bad enumerator-definition."); }
    break;

  case 322:

    { YACC_UNBANG((yyvsp[(1) - (3)].bang), "Bad enumerator-definition."); }
    break;

  case 323:

    { (yyval.enumerators) = YACC_ENUMERATORS(0, 0); }
    break;

  case 325:

    { (yyval.enumerators) = YACC_ENUMERATORS((yyvsp[(1) - (2)].enumerators), (yyvsp[(2) - (2)].enumerator)); }
    break;

  case 326:

    { (yyval.enumerator) = YACC_ENUMERATOR((yyvsp[(1) - (1)].name), 0); }
    break;

  case 327:

    { (yyval.enumerator) = YACC_ENUMERATOR((yyvsp[(1) - (3)].name), (yyvsp[(3) - (3)].expression)); }
    break;

  case 329:

    { (yyval.name) = YACC_NAMESPACE_DEFINITION((yyvsp[(2) - (3)].name), (yyvsp[(3) - (3)].declarations)); }
    break;

  case 330:

    { (yyval.name) = YACC_NAMESPACE_DEFINITION(0, (yyvsp[(2) - (2)].declarations)); }
    break;

  case 331:

    { (yyval.declaration) = YACC_NAMESPACE_ALIAS_DEFINITION((yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].name)); }
    break;

  case 332:

    { (yyval.declaration) = YACC_USING_DECLARATION(false, (yyvsp[(2) - (3)].name)); }
    break;

  case 333:

    { (yyval.declaration) = YACC_USING_DECLARATION(true, (yyvsp[(3) - (4)].name)); }
    break;

  case 334:

    { (yyval.declaration) = YACC_USING_DIRECTIVE((yyvsp[(3) - (4)].name)); }
    break;

  case 335:

    { (yyval.declaration) = YACC_ASM_DEFINITION((yyvsp[(3) - (5)].strings)); }
    break;

  case 336:

    { (yyval.name) = YACC_LINKAGE_SPECIFIER((yyvsp[(2) - (3)].strings), (yyvsp[(3) - (3)].declaration)); }
    break;

  case 337:

    { (yyval.name) = YACC_LINKAGE_SPECIFIER((yyvsp[(2) - (3)].strings), (yyvsp[(3) - (3)].declarations)); }
    break;

  case 338:

    { (yyval.expressions) = YACC_EXPRESSIONS(YACC_EXPRESSIONS(0, (yyvsp[(1) - (3)].expression)), (yyvsp[(3) - (3)].expression)); }
    break;

  case 339:

    { (yyval.expressions) = YACC_EXPRESSIONS((yyvsp[(1) - (3)].expressions), (yyvsp[(3) - (3)].expression)); }
    break;

  case 341:

    { (yyval.pointer_declarator) = YACC_POINTER_DECLARATOR(); }
    break;

  case 342:

    { (yyval.pointer_declarator) = YACC_CV_DECLARATOR((yyvsp[(1) - (2)].pointer_declarator), (yyvsp[(2) - (2)].cv_qualifiers)); }
    break;

  case 343:

    { (yyval.declarator) = (yyvsp[(1) - (1)].pointer_declarator); }
    break;

  case 344:

    { (yyval.declarator) = YACC_NESTED_DECLARATOR((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].declarator)); }
    break;

  case 345:

    { (yyval.declarator) = YACC_REFERENCE_DECLARATOR(); }
    break;

  case 346:

    { (yyval.declarator) = (yyvsp[(1) - (1)].declarator); }
    break;

  case 347:

    { (yyval.declarator) = YACC_GLOBAL_DECLARATOR((yyvsp[(1) - (2)].is_template), (yyvsp[(2) - (2)].declarator)); }
    break;

  case 348:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yyvsp[(1) - (1)].declarator), YACC_EPSILON()); }
    break;

  case 349:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yyvsp[(1) - (2)].declarator), (yyvsp[(2) - (2)].expression)); }
    break;

  case 350:

    { (yyval.expression) = YACC_EXPRESSION(0); }
    break;

  case 351:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yyvsp[(1) - (2)].declarator), (yyvsp[(2) - (2)].expression)); }
    break;

  case 352:

    { (yyval.cv_qualifiers) = YACC_CV_QUALIFIERS(0, 0); }
    break;

  case 353:

    { (yyval.cv_qualifiers) = YACC_CV_QUALIFIERS((yyvsp[(1) - (2)].cv_qualifiers), (yyvsp[(2) - (2)].cv_qualifiers)); }
    break;

  case 356:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].expression)); }
    break;

  case 357:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].expression)); }
    break;

  case 358:

    { (yyval.expression) = YACC_EPSILON(); }
    break;

  case 359:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yyvsp[(1) - (2)].declarator), (yyvsp[(2) - (2)].expression)); }
    break;

  case 361:

    { (yyval.expression) = YACC_EPSILON(); }
    break;

  case 363:

    { (yyval.expression) = YACC_CALL_EXPRESSION((yyvsp[(1) - (2)].expression), (yyvsp[(2) - (2)].parenthesised)); }
    break;

  case 364:

    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yyvsp[(1) - (3)].expression), 0); }
    break;

  case 365:

    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression)); }
    break;

  case 366:

    { (yyval.parenthesised) = YACC_PARENTHESISED((yyvsp[(1) - (2)].parameters), (yyvsp[(2) - (2)].cv_qualifiers), 0); }
    break;

  case 367:

    { (yyval.parenthesised) = YACC_PARENTHESISED((yyvsp[(1) - (3)].parameters), (yyvsp[(2) - (3)].cv_qualifiers), (yyvsp[(3) - (3)].exception_specification)); }
    break;

  case 368:

    { (yyval.parameters) = (yyvsp[(2) - (3)].parameters); }
    break;

  case 369:

    { (yyval.parameters) = YACC_PARAMETERS(0, 0); }
    break;

  case 371:

    { (yyval.parameters) = YACC_PARAMETERS((yyvsp[(1) - (2)].parameters), YACC_ELLIPSIS_EXPRESSION()); }
    break;

  case 372:

    { (yyval.parameters) = YACC_PARAMETERS(0, (yyvsp[(1) - (1)].parameter)); }
    break;

  case 373:

    { (yyval.parameters) = YACC_PARAMETERS((yyvsp[(1) - (3)].parameters), (yyvsp[(3) - (3)].parameter)); }
    break;

  case 375:

    { (yyval.expression) = YACC_MULTIPLY_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].pointer_declarator), (yyvsp[(3) - (3)].expression)); }
    break;

  case 377:

    { (yyval.expression) = YACC_AND_EXPRESSION((yyvsp[(1) - (2)].expression), YACC_EPSILON()); }
    break;

  case 378:

    { (yyval.expression) = YACC_AND_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 380:

    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].keyword), (yyvsp[(3) - (3)].expression)); }
    break;

  case 381:

    { (yyval.expression) = YACC_ELLIPSIS_EXPRESSION(); }
    break;

  case 382:

    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yyvsp[(1) - (1)].expression)); }
    break;

  case 383:

    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yyvsp[(1) - (1)].expression)); }
    break;

  case 384:

    { (yyval.parameter) = YACC_DECL_SPECIFIER_PARAMETER((yyvsp[(2) - (2)].parameter), (yyvsp[(1) - (2)].decl_specifier_id)); }
    break;

  case 385:

    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yyvsp[(1) - (1)].expression)); }
    break;

  case 386:

    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yyvsp[(1) - (1)].expression)); }
    break;

  case 387:

    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER(YACC_ASSIGNMENT_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].keyword), (yyvsp[(3) - (3)].expression))); }
    break;

  case 388:

    { (yyval.parameter) = YACC_DECL_SPECIFIER_PARAMETER((yyvsp[(2) - (2)].parameter), (yyvsp[(1) - (2)].decl_specifier_id)); }
    break;

  case 390:

    { (yyval.expression) = YACC_AND_EXPRESSION((yyvsp[(1) - (2)].expression), 0); }
    break;

  case 391:

    { (yyval.expression) = YACC_AND_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 394:

    { (yyval.expression) = YACC_FUNCTION_DEFINITION((yyvsp[(1) - (2)].expression), (yyvsp[(2) - (2)].function_body)); }
    break;

  case 395:

    { (yyval.expression) = YACC_FUNCTION_DEFINITION((yyvsp[(1) - (2)].expression), (yyvsp[(2) - (2)].function_body)); }
    break;

  case 396:

    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yyvsp[(2) - (2)].expression), (yyvsp[(1) - (2)].decl_specifier_id)); }
    break;

  case 397:

    { (yyval.expression) = YACC_CTOR_DEFINITION((yyvsp[(1) - (2)].expressions), (yyvsp[(2) - (2)].function_body)); }
    break;

  case 398:

    { (yyval.expression) = YACC_CTOR_DEFINITION((yyvsp[(1) - (2)].expressions), (yyvsp[(2) - (2)].function_body)); }
    break;

  case 399:

    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yyvsp[(2) - (2)].expression), (yyvsp[(1) - (2)].decl_specifier_id)); }
    break;

  case 400:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yyvsp[(1) - (1)].expression)); }
    break;

  case 401:

    { (yyval.expressions) = YACC_EXPRESSIONS((yyvsp[(1) - (3)].expressions), (yyvsp[(3) - (3)].expression)); }
    break;

  case 402:

    { (yyval.function_body) = YACC_TRY_FUNCTION_BLOCK((yyvsp[(2) - (3)].function_body), (yyvsp[(3) - (3)].handlers)); }
    break;

  case 403:

    { (yyval.function_body) = YACC_CTOR_FUNCTION_BLOCK((yyvsp[(2) - (2)].function_body), (yyvsp[(1) - (2)].mem_initializers)); }
    break;

  case 404:

    { (yyval.function_body) = YACC_FUNCTION_BLOCK((yyvsp[(1) - (1)].statement)); }
    break;

  case 405:

    { (yyval.initializer_clause) = YACC_INITIALIZER_EXPRESSION_CLAUSE((yyvsp[(1) - (1)].expression)); }
    break;

  case 407:

    { (yyval.initializer_clause) = YACC_INITIALIZER_LIST_CLAUSE((yyvsp[(2) - (3)].initializer_clauses)); }
    break;

  case 408:

    { (yyval.initializer_clause) = YACC_INITIALIZER_LIST_CLAUSE((yyvsp[(2) - (4)].initializer_clauses)); }
    break;

  case 409:

    { (yyval.initializer_clause) = YACC_INITIALIZER_LIST_CLAUSE(0); }
    break;

  case 410:

    { (yyval.initializer_clause) = 0; YACC_UNBANG((yyvsp[(4) - (6)].bang), "Bad initializer_clause."); }
    break;

  case 411:

    { (yyval.initializer_clause) = (yyvsp[(2) - (8)].initializer_clauses); YACC_UNBANG((yyvsp[(6) - (8)].bang), "Bad initializer_clause."); }
    break;

  case 412:

    { (yyval.initializer_clauses) = YACC_INITIALIZER_CLAUSES(0, (yyvsp[(1) - (1)].initializer_clause)); }
    break;

  case 413:

    { (yyval.initializer_clauses) = YACC_INITIALIZER_CLAUSES((yyvsp[(1) - (3)].initializer_clauses), (yyvsp[(3) - (3)].initializer_clause)); }
    break;

  case 414:

    { (yyval.initializer_clause) = (yyvsp[(2) - (2)].initializer_clause); end_search((yyval.initializer_clause)); }
    break;

  case 416:

    { (yyval.initializer_clause) = (yyvsp[(3) - (3)].initializer_clause); }
    break;

  case 417:

    { (yyval.initializer_clause) = 0; }
    break;

  case 418:

    { (yyval.mark) = mark(); }
    break;

  case 419:

    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yyvsp[(1) - (2)].class_key), (yyvsp[(2) - (2)].name)); }
    break;

  case 420:

    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yyvsp[(1) - (4)].class_key), (yyvsp[(2) - (4)].name)); rewind_colon((yyvsp[(3) - (4)].mark), (yyval.name)); }
    break;

  case 421:

    { unmark((yyvsp[(4) - (5)].base_specifiers)); (yyval._class) = YACC_CLASS_SPECIFIER_ID((yyvsp[(1) - (5)].class_key), (yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].base_specifiers)); }
    break;

  case 422:

    { (yyval._class) = YACC_CLASS_SPECIFIER_ID((yyvsp[(1) - (4)].class_key), 0, (yyvsp[(3) - (4)].base_specifiers)); }
    break;

  case 423:

    { (yyval._class) = YACC_CLASS_SPECIFIER_ID((yyvsp[(1) - (3)].class_key), (yyvsp[(2) - (3)].name), 0); }
    break;

  case 424:

    { (yyval._class) = YACC_CLASS_SPECIFIER_ID((yyvsp[(1) - (2)].class_key), 0, 0); }
    break;

  case 428:

    { (yyval.name) = YACC_CLASS_MEMBERS((yyvsp[(1) - (3)]._class), (yyvsp[(2) - (3)].declarations)); }
    break;

  case 429:

    { (yyval.name) = YACC_CLASS_MEMBERS((yyvsp[(1) - (8)]._class), (yyvsp[(2) - (8)].declarations)); YACC_UNBANG((yyvsp[(6) - (8)].bang), "Bad member_specification.opt."); }
    break;

  case 430:

    { (yyval.declarations) = YACC_MEMBER_DECLARATIONS(0, 0); }
    break;

  case 431:

    { (yyval.declarations) = YACC_MEMBER_DECLARATIONS((yyvsp[(1) - (3)].declarations), YACC_COMPILE_DECLARATION((yyvsp[(2) - (3)].utility), (yyvsp[(3) - (3)].declaration))); }
    break;

  case 432:

    { (yyval.declarations) = (yyvsp[(1) - (7)].declarations); YACC_UNBANG((yyvsp[(5) - (7)].bang), "Bad member-declaration."); }
    break;

  case 433:

    { (yyval.declaration) = YACC_LINED_DECLARATION((yyvsp[(2) - (2)].declaration), (yyvsp[(1) - (2)].line)); end_search((yyval.declaration)); }
    break;

  case 435:

    { (yyval.declaration) = (yyvsp[(3) - (3)].declaration); }
    break;

  case 436:

    { (yyval.declaration) = 0; }
    break;

  case 438:

    { (yyval.declaration) = YACC_SIMPLE_DECLARATION((yyvsp[(1) - (1)].expression)); }
    break;

  case 439:

    { (yyval.declaration) = YACC_SIMPLE_DECLARATION((yyvsp[(1) - (1)].expression)); }
    break;

  case 442:

    { (yyval.expression) = YACC_EXPRESSION(0); }
    break;

  case 444:

    { (yyval.expression) = (yyvsp[(1) - (2)].expressions); }
    break;

  case 445:

    { (yyval.expression) = (yyvsp[(1) - (2)].expressions); }
    break;

  case 446:

    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yyvsp[(2) - (2)].expression), (yyvsp[(1) - (2)].decl_specifier_id)); }
    break;

  case 447:

    { (yyval.expressions) = YACC_EXPRESSIONS(YACC_EXPRESSIONS(0, (yyvsp[(1) - (3)].expression)), (yyvsp[(3) - (3)].expression)); }
    break;

  case 448:

    { (yyval.expressions) = YACC_EXPRESSIONS((yyvsp[(1) - (3)].expressions), (yyvsp[(3) - (3)].expression)); }
    break;

  case 449:

    { (yyval.expressions) = YACC_EXPRESSIONS((yyvsp[(1) - (3)].expressions), (yyvsp[(3) - (3)].expression)); }
    break;

  case 452:

    { (yyval.declaration) = YACC_ACCESSIBILITY_SPECIFIER((yyvsp[(1) - (2)].access_specifier)); }
    break;

  case 453:

    { (yyval.expression) = YACC_BIT_FIELD_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 454:

    { (yyval.expression) = YACC_BIT_FIELD_EXPRESSION(0, (yyvsp[(2) - (2)].expression)); }
    break;

  case 456:

    { (yyval.expression) = YACC_CONDITIONAL_EXPRESSION((yyvsp[(1) - (5)].expression), (yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].expression)); }
    break;

  case 458:

    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].keyword), (yyvsp[(3) - (3)].initializer_clause)); }
    break;

  case 459:

    { (yyval.base_specifiers) = YACC_BASE_SPECIFIERS(0, (yyvsp[(1) - (1)].base_specifier)); }
    break;

  case 460:

    { (yyval.base_specifiers) = YACC_BASE_SPECIFIERS((yyvsp[(1) - (3)].base_specifiers), (yyvsp[(3) - (3)].base_specifier)); }
    break;

  case 461:

    { (yyval.base_specifier) = YACC_BASE_SPECIFIER((yyvsp[(1) - (1)].name)); }
    break;

  case 462:

    { (yyval.base_specifier) = YACC_ACCESS_BASE_SPECIFIER((yyvsp[(2) - (2)].base_specifier), (yyvsp[(1) - (2)].access_specifier)); }
    break;

  case 463:

    { (yyval.base_specifier) = YACC_VIRTUAL_BASE_SPECIFIER((yyvsp[(2) - (2)].base_specifier)); }
    break;

  case 467:

    { (yyval.name) = YACC_CONVERSION_FUNCTION_ID((yyvsp[(2) - (2)].expression)); }
    break;

  case 468:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].expression)); }
    break;

  case 469:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].expression)); }
    break;

  case 470:

    { (yyval.mem_initializers) = YACC_MEM_INITIALIZERS(0, 0); }
    break;

  case 472:

    { (yyval.mem_initializers) = (yyvsp[(2) - (2)].mem_initializers); }
    break;

  case 473:

    { (yyval.mem_initializers) = (yyvsp[(2) - (4)].mem_initializers); YACC_UNBANG((yyvsp[(3) - (4)].bang), "Bad ctor-initializer."); }
    break;

  case 474:

    { (yyval.mem_initializers) = YACC_MEM_INITIALIZERS(0, (yyvsp[(1) - (1)].mem_initializer)); }
    break;

  case 475:

    { (yyval.mem_initializers) = YACC_MEM_INITIALIZERS((yyvsp[(1) - (2)].mem_initializers), (yyvsp[(2) - (2)].mem_initializer)); }
    break;

  case 477:

    { YACC_UNBANG((yyvsp[(2) - (4)].bang), "Bad mem-initializer."); }
    break;

  case 478:

    { (yyval.mem_initializer) = YACC_MEM_INITIALIZER((yyvsp[(1) - (4)].name), (yyvsp[(3) - (4)].expressions)); }
    break;

  case 480:

    { (yyval.name) = YACC_OPERATOR_FUNCTION_ID((yyvsp[(2) - (2)].name)); }
    break;

  case 481:

    { (yyval.name) = YACC_OPERATOR_NEW_ID(); }
    break;

  case 482:

    { (yyval.name) = YACC_OPERATOR_DELETE_ID(); }
    break;

  case 483:

    { (yyval.name) = YACC_OPERATOR_ADD_ID(); }
    break;

  case 484:

    { (yyval.name) = YACC_OPERATOR_SUB_ID(); }
    break;

  case 485:

    { (yyval.name) = YACC_OPERATOR_MUL_ID(); }
    break;

  case 486:

    { (yyval.name) = YACC_OPERATOR_DIV_ID(); }
    break;

  case 487:

    { (yyval.name) = YACC_OPERATOR_MOD_ID(); }
    break;

  case 488:

    { (yyval.name) = YACC_OPERATOR_XOR_ID(); }
    break;

  case 489:

    { (yyval.name) = YACC_OPERATOR_BIT_AND_ID(); }
    break;

  case 490:

    { (yyval.name) = YACC_OPERATOR_BIT_OR_ID(); }
    break;

  case 491:

    { (yyval.name) = YACC_OPERATOR_BIT_NOT_ID(); }
    break;

  case 492:

    { (yyval.name) = YACC_OPERATOR_LOG_NOT_ID(); }
    break;

  case 493:

    { (yyval.name) = YACC_OPERATOR_ASS_ID(); }
    break;

  case 494:

    { (yyval.name) = YACC_OPERATOR_LT_ID(); }
    break;

  case 495:

    { (yyval.name) = YACC_OPERATOR_GT_ID(); }
    break;

  case 496:

    { (yyval.name) = YACC_OPERATOR_ASS_ADD_ID(); }
    break;

  case 497:

    { (yyval.name) = YACC_OPERATOR_ASS_SUB_ID(); }
    break;

  case 498:

    { (yyval.name) = YACC_OPERATOR_ASS_MUL_ID(); }
    break;

  case 499:

    { (yyval.name) = YACC_OPERATOR_ASS_DIV_ID(); }
    break;

  case 500:

    { (yyval.name) = YACC_OPERATOR_ASS_MOD_ID(); }
    break;

  case 501:

    { (yyval.name) = YACC_OPERATOR_ASS_XOR_ID(); }
    break;

  case 502:

    { (yyval.name) = YACC_OPERATOR_ASS_BIT_AND_ID(); }
    break;

  case 503:

    { (yyval.name) = YACC_OPERATOR_ASS_BIT_OR_ID(); }
    break;

  case 504:

    { (yyval.name) = YACC_OPERATOR_SHL_ID(); }
    break;

  case 505:

    { (yyval.name) = YACC_OPERATOR_SHR_ID(); }
    break;

  case 506:

    { (yyval.name) = YACC_OPERATOR_ASS_SHR_ID(); }
    break;

  case 507:

    { (yyval.name) = YACC_OPERATOR_ASS_SHL_ID(); }
    break;

  case 508:

    { (yyval.name) = YACC_OPERATOR_EQ_ID(); }
    break;

  case 509:

    { (yyval.name) = YACC_OPERATOR_NE_ID(); }
    break;

  case 510:

    { (yyval.name) = YACC_OPERATOR_LE_ID(); }
    break;

  case 511:

    { (yyval.name) = YACC_OPERATOR_GE_ID(); }
    break;

  case 512:

    { (yyval.name) = YACC_OPERATOR_LOG_AND_ID(); }
    break;

  case 513:

    { (yyval.name) = YACC_OPERATOR_LOG_OR_ID(); }
    break;

  case 514:

    { (yyval.name) = YACC_OPERATOR_INC_ID(); }
    break;

  case 515:

    { (yyval.name) = YACC_OPERATOR_DEC_ID(); }
    break;

  case 516:

    { (yyval.name) = YACC_OPERATOR_COMMA_ID(); }
    break;

  case 517:

    { (yyval.name) = YACC_OPERATOR_ARROW_STAR_ID(); }
    break;

  case 518:

    { (yyval.name) = YACC_OPERATOR_ARROW_ID(); }
    break;

  case 519:

    { (yyval.name) = YACC_OPERATOR_CALL_ID(); }
    break;

  case 520:

    { (yyval.name) = YACC_OPERATOR_INDEX_ID(); }
    break;

  case 521:

    { (yyval.declaration) = YACC_TEMPLATE_DECLARATION((yyvsp[(1) - (2)].template_parameters), (yyvsp[(2) - (2)].declaration)); }
    break;

  case 522:

    { (yyval.declaration) = YACC_DECL_SPECIFIER_DECLARATION((yyvsp[(2) - (2)].declaration), (yyvsp[(1) - (2)].decl_specifier_id)); }
    break;

  case 523:

    { (yyval.template_parameters) = (yyvsp[(3) - (4)].template_parameters); }
    break;

  case 524:

    { (yyval.template_parameters) = YACC_TEMPLATE_PARAMETERS(0, (yyvsp[(1) - (1)].template_parameter)); }
    break;

  case 525:

    { (yyval.template_parameters) = YACC_TEMPLATE_PARAMETERS((yyvsp[(1) - (3)].template_parameters), (yyvsp[(3) - (3)].template_parameter)); }
    break;

  case 526:

    { (yyval.template_parameter) = YACC_INIT_SIMPLE_TYPE_PARAMETER((yyvsp[(1) - (1)].simple_type_parameter), 0); }
    break;

  case 527:

    { (yyval.template_parameter) = YACC_INIT_SIMPLE_TYPE_PARAMETER((yyvsp[(1) - (3)].simple_type_parameter), (yyvsp[(3) - (3)].expression)); }
    break;

  case 528:

    { (yyval.template_parameter) = YACC_INIT_TEMPLATED_PARAMETER((yyvsp[(1) - (1)].templated_type_parameter), 0); }
    break;

  case 529:

    { (yyval.template_parameter) = YACC_INIT_TEMPLATED_PARAMETER((yyvsp[(1) - (3)].templated_type_parameter), (yyvsp[(3) - (3)].name)); }
    break;

  case 530:

    { (yyval.template_parameter) = YACC_TEMPLATE_PARAMETER((yyvsp[(1) - (1)].parameter)); }
    break;

  case 531:

    { (yyval.template_parameter) = 0; YACC_UNBANG((yyvsp[(1) - (2)].bang), "Bad template-parameter."); }
    break;

  case 532:

    { (yyval.simple_type_parameter) = YACC_CLASS_TYPE_PARAMETER(0); }
    break;

  case 533:

    { (yyval.simple_type_parameter) = YACC_TYPENAME_TYPE_PARAMETER(0); }
    break;

  case 534:

    { (yyval.templated_type_parameter) = YACC_TEMPLATED_TYPE_PARAMETER((yyvsp[(1) - (2)].template_parameters), 0); }
    break;

  case 535:

    { (yyval.templated_type_parameter) = YACC_TEMPLATED_TYPE_PARAMETER((yyvsp[(1) - (3)].template_parameters), (yyvsp[(3) - (3)].name)); }
    break;

  case 536:

    { (yyval.name) = YACC_TEMPLATE_NAME((yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].template_arguments)); }
    break;

  case 537:

    { (yyval.name) = (yyvsp[(2) - (2)].name); }
    break;

  case 538:

    { (yyval.template_arguments) = YACC_TEMPLATE_ARGUMENTS(0, (yyvsp[(1) - (1)].template_argument)); }
    break;

  case 539:

    { (yyval.template_arguments) = YACC_TEMPLATE_ARGUMENTS((yyvsp[(1) - (3)].template_arguments), (yyvsp[(3) - (3)].template_argument)); }
    break;

  case 540:

    { (yyval.template_argument) = YACC_TEMPLATE_ARGUMENT((yyvsp[(1) - (1)].parameter)); }
    break;

  case 541:

    { (yyval.declaration) = YACC_EXPLICIT_SPECIALIZATION((yyvsp[(4) - (4)].declaration)); }
    break;

  case 542:

    { (yyval.function_body) = YACC_TRY_BLOCK((yyvsp[(2) - (3)].statement), (yyvsp[(3) - (3)].handlers)); }
    break;

  case 543:

    { (yyval.handlers) = YACC_HANDLERS(0, (yyvsp[(1) - (1)].handler)); }
    break;

  case 544:

    { (yyval.handlers) = YACC_HANDLERS((yyvsp[(2) - (2)].handlers), (yyvsp[(1) - (2)].handler)); }
    break;

  case 545:

    { (yyval.handler) = YACC_HANDLER((yyvsp[(3) - (5)].exception_declaration), (yyvsp[(5) - (5)].statement)); }
    break;

  case 546:

    { (yyval.exception_declaration) = YACC_EXCEPTION_DECLARATION((yyvsp[(1) - (1)].parameter)); }
    break;

  case 547:

    { (yyval.expression) = YACC_THROW_EXPRESSION(0); }
    break;

  case 548:

    { (yyval.expression) = YACC_THROW_EXPRESSION((yyvsp[(2) - (2)].expression)); }
    break;

  case 549:

    { (yyval.expression) = YACC_THROW_EXPRESSION(0); }
    break;

  case 550:

    { (yyval.expression) = YACC_THROW_EXPRESSION((yyvsp[(2) - (2)].expression)); }
    break;

  case 551:

    { (yyval.exception_specification) = YACC_EXCEPTION_SPECIFICATION(0); }
    break;

  case 552:

    { (yyval.exception_specification) = YACC_EXCEPTION_SPECIFICATION((yyvsp[(3) - (4)].expressions)); }
    break;

  case 553:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yyvsp[(1) - (1)].expression)); }
    break;

  case 554:

    { (yyval.expressions) = YACC_EXPRESSIONS((yyvsp[(1) - (3)].expressions), (yyvsp[(3) - (3)].expression)); }
    break;

  case 555:

    { yyerrok; advance_search(); }
    break;

  case 556:

    { (yyval.bang) = YACC_BANG(); }
    break;

  case 557:

    { (yyval.mark) = mark(); }
    break;

  case 558:

    { (yyval.nest) = nest(); }
    break;

  case 559:

    { (yyval.line) = YACC_LINE(); start_search(false); }
    break;

  case 560:

    { (yyval.line) = YACC_LINE(); start_search(true); }
    break;

  case 561:

    { (yyval.utility) = YACC_UTILITY_MODE(); }
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





#include "CxxParsing.cxx"
/*EndTester*/
