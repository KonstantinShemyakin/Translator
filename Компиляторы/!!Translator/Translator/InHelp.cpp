#include "stdafx.h"

#if defined(_MSC_VER)
#define SSCANF(B,F,V)   sscanf_s(B,F,V)
#elif defined(__GNUC__)
#define SSCANF(B,F,V)   sscanf(B,F,V)
#endif

#include "InHelp.h"

TInHelp::TInHelp(int p) :program(p), count(0), type(0), option(0), mode(0), file(NULL), table(NULL)
{
   start = std::chrono::system_clock::now();
}

TInHelp::~TInHelp()
{
   end = std::chrono::system_clock::now();
   int elapsed_seconds = (int)std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
   printf("\ntime: %d.%03ds\n", elapsed_seconds / 1000, elapsed_seconds % 1000);
}

void TInHelp::option_mode() const
{
   printf("\nprint_mode:");
   printf("\n   0x00000001 - print_other,   0x00000002 - print_space,0x00000004 - print_line,  0x00000008 - print_Lexeme,");
   printf("\n   0x00000010 - print_tree,    0x00000020 - erase_code, 0x00000040 - print_code,  0x00000080 - print_operator,");
   printf("\n   0x00000100 - print_rule,    0x00000200 - print_maker,0x00000400 - print_stack, 0x00000800 - print_Code,");
   printf("\n   0x00001000 - print_SNode,   0x00002000 - print_Tree, 0x00004000 - print_source,0x00008000 - print_semantic");
   printf("\n   0x00010000 - select_produce,0x00020000 - trim_unit,  0x00040000 - print_auto,  0x00080000 - TreeTraversal");
   printf("\n   0x00100000 - print_quadro,  0x00200000 - at_once,    0x00400000 - !auto_digit");
   printf("\n");
}

void TInHelp::table_mode() const
{
   printf("\ntable_mode:");
   printf("\n   Grammar     - 0x00000001, Follow      - 0x00000002, Maker      - 0x00000004, Lexeme     - 0x00000008, ");
   printf("\n   First       - 0x00000010, EFF         - 0x00000020, BNF        - 0x00000040, ");
   printf("\n   Formula     - 0x00000100,                           Output     - 0x00000400, C2A        - 0x00000800, Ahead = 0x00000800, ");
   printf("\n   Action      - 0x00001000, Table       - 0x00002000, Cell       - 0x00001000, ");
   printf("\n   State       - 0x00010000, StateCore   - 0x00020000, StateSort  - 0x00040000, GoTo       - 0x00080000, ");
   printf("\n   Association - 0x00100000, Compression - 0x00200000, NoDefType  - 0x00400000, AssignOper - 0x00800000  ");
   printf("\n");
}

void TInHelp::parse_mode() const
{
   printf("\nparse_mode:");
   printf("\n   0 - source");
   printf("\n   1 - scan");
   printf("\n   2 - next");
   printf("\n   3 - control");
   printf("\n   4 - lexeme");
   printf("\n   5 - prior");
   printf("\n   6 - syntax");
   printf("\n   7 - restore");
   printf("\n   8 - Z(),E(),T(),F()");
   printf("\n   9 - write");
   printf("\n   A - lexer");
   printf("\n");
}

void TInHelp::make_mode() const
{
   printf("\nmake_mode:");
   printf("\n   0 - none");
   printf("\n   1 - Tree");
   printf("\n   2 - Code");
   printf("\n   3 - Node");
   printf("\n   4 - Turn");
   printf("\n   5 - Made");
   printf("\n");
}

void TInHelp::build_mode() const
{
   printf("\nbuild_mode:");
   printf("\n   0 - none");
   printf("\n   4 - PROG(LL<Tree,Code>,NL<Tree>)");
   printf("\n   5 - LL1(LL)");
   printf("\n   6 - LR0(LL,LR,NR)");
   printf("\n   7 - LR0_Core(LL,LR,NR)");
   printf("\n   8 - LR1(LL,LR,NR)");
   printf("\n   9 - LR1_Core(LL,LR,NR)");
   printf("\n   A - LALR(LL,LR,NR)");
   printf("\n   B - LALR_Tab(LL,LR,NR)");
   printf("\n   C - LALR_Full(LL,LR,NR)");
   printf("\n   D - LALR_Core(LL,LR,NR)");
   printf("\n   E - YACC(LL<Tree,Code>,LR<Tree,Code>,NR<Tree,Code,Node>)");

   printf("\n");
}

void TInHelp::grammar_mode() const
{
   printf("\ngrammar_mode:");
   printf("\n   0 - LL(Tree,Code,Node,Made)");
   printf("\n   1 - NL(Tree)");
   printf("\n   2 - LR(Tree,Code,Turn)");
   printf("\n   3 - NR(Tree,Code,Node,Made)");
   printf("\n   4 - ETF_LL()");
   printf("\n   5 - ETF_LL(Tree,Code)");
   printf("\n   6 - ETF_LR()");
   printf("\n   7 - ETF_LR(Tree,Code)");
   printf("\n   8 - EXPR_LR()");
   printf("\n   9 - *.*    // Table.*");
   printf("\n   A - *.bif  // ISyntax.y");
   printf("\n   B - *.bnf  // BSyntax.y");
   printf("\n   C - *.yacc // FSyntax.yacc");
   printf("\n   D - *.y    // FSyntax.y");
   printf("\n   E - *.y    // FSyntax.cpp");
   printf("\n   F - *.tab");
   printf("\n");
}

void TInHelp::parse_help() const
{
   printf("\nTranParse parse_mode print_mode file");
   parse_mode();
   option_mode();
}

void TInHelp::rules_help() const
{
   printf("\nTranRules FGMP print_mode file table");
   printf("\nGMP:");
   printf("\n   Grammar: 0 - LL(Tree,Code,Node), 1 - NL(Tree), 4 - ETF_LL(), 5 - ETF_LL(Tree,Code)");
   printf("\n   Make   : 0 - none, 1 - Tree, 2 - Code, 3 - Node, 5 - Made");
   printf("\n   Parse  : 0 - none, 1 - ParseStackRule, 2 - ParseStackSymbol, 4 - ParseFormula");
   printf("\n");
   option_mode();
}

void TInHelp::syntax_help() const
{
   printf("\nTranSyntax mode print_mode file");
   printf("\nmode:");
   printf("\n   0 - none, 1 - Syntax, 2 - TSyntax(Tree), 3 - CSyntax(Code), 4 - MSyntax(Tree), 5 - MSyntax(Code)");
   printf("\n");
   option_mode();
}

void TInHelp::yacc_help() const
{
   printf("\nTranYACC GrammarMakeParse print_mode file");
   printf("\n   Grammar: 0 - LL<PROG,YACC>(Tree,Code), 1 - NL<PROG>(Tree), 2 - LR<YACC>(Tree,Code), 3 - NR<YACC>(Tree,Code,Node)");
   printf("\n            C - C_Grammar<YACC>(Tree)");
   printf("\n   Make   : 0 - none, 1 - Tree, 2 - Code, 3 - Node, 5 - Made");
   printf("\n   Parse  : 0 - none, 3 - TAB , 4 - PROG, E - YACC");
   printf("\n");
   option_mode();
}

void TInHelp::grammar_help() const
{
   printf("\nTranGrammar SM print_mode file table");
   printf("\nS - scan_type:");
   printf("\n   0 - Scan, 1 - Flex");
   printf("\nM - make_mode:");
   printf("\n   0 - none, 1 - Tree, 2 - Code, 3 - Node, 4 - Turn, 5 - Made, 6 - Call, C - C_Grammar, D - C99_Grammar");
   printf("\n");
   option_mode();
}

void TInHelp::table_help() const
{
   printf("\nTableBuilder k_scan_grammar_make_build table_mode file table");
   printf("\nk_mode: k - LookAhead");
   printf("\nscan_mode: 0 - MyScan, 1 - FlexLexer");
   grammar_mode();
   make_mode();
   build_mode();
   table_mode();
}

void TInHelp::translator_help() const
{
   printf("\nTranslator case mode table_mode file table");
   printf("\ncase: ");
   printf("\n   Test       - 0x1000");
   printf("\n   Token_C99  - 0x1001");
   printf("\n   SQL_BNF    - 0x1002");
   printf("\n   Formulas   - 0x1003");
   printf("\n   Grammar    - 0x1004");
   printf("\n   GroupMaker - 0x1006");
   printf("\nmode: ");
   table_mode();
}

void TInHelp::help() const
{
   switch (program) {
   case None:      table_mode(); make_mode(); option_mode(); break;
   case Parse:     parse_help();      break;
   case Syntax:    syntax_help();     break;
   case Rules:     rules_help();      break;
   case Table:     table_help();      break;
   case YACC:      yacc_help();       break;
   case Grammar:   grammar_help();    break;
   case Translate: translator_help(); break;
   }
}

int TInHelp::input(int argc, const char* argv[])
{
   
   if (argc <= 1) {
      help();
      return false;
   }
   
   for (int i = 0; i < argc; i++)
   {
       printf("%s\n", argv[i]);
   }
   printf("\n");

   int arg = 1;
   if (argc > arg) {
      SSCANF(argv[arg++],"%x",&type);
   }
   if (program == Translate) {
      mode = type;
      if (argc > arg) {
         SSCANF(argv[arg++], "%x", &type);
      }
   }
   if (argc > arg) {
      SSCANF(argv[arg++],"%x",&option);
   }
   if (argc > arg) {
      file = argv[arg++];
   }
   if (argc > arg) {
      table = argv[arg++];
   }

   count = argc;

   return true;
}

#include "ASyntax.h"

static int options[] = 
{
OPTION_MODE(ThreePhase, , , CodeGenerate, BlockTable, , , Tree),
OPTION_MODE(OnePhase, , , CodeGenerate, BlockTable, , , Code),

};
