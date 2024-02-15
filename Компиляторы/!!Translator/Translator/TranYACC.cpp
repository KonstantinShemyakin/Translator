// TranYACC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parse.h"
#include "ASyntax.h"
#include "TSemantic.h"
#include "Maker.h"
#include "InHelp.h"
#include "Grammar.h"

// --------------------------- PSyntax ---------------------------
#include "PSyntax.h"

#define MAKE_(FUNC,P,M)   {static GSymbol maker(GSymbol::gsMaker,GMakerTable::maker_table.Find(#FUNC),P,0,M);\
                           if (!Maker(maker)) return false; }
#define MAKE(FUNC)         MAKE_(FUNC,0,GSymbol::Tree | GSymbol::Code)
#define MAKE_TREE(FUNC)    MAKE_(FUNC,0,GSymbol::Tree);
#define MAKE_CODE(FUNC)    MAKE_(FUNC,0,GSymbol::Code);
#define PARAM(FUNC,P)      MAKE_(FUNC,P,GSymbol::Tree | GSymbol::Code) 
#define PARAM_TREE(FUNC,P) MAKE_(FUNC,P,GSymbol::Tree) 
#define PARAM_CODE(FUNC,P) MAKE_(FUNC,P,GSymbol::Code) 

namespace LL_TC_PROG {
#include "LL_TC_PROG.h"
#include "LL_TC_PROG.cpp"
}

namespace NL_TC_PROG {
#include "NL_TC_PROG.h"
#include "NL_TC_PROG.cpp"
}

namespace ETF_LL_TC_PROG {
#include "ETF_LL_TC_PROG.h"
#include "ETF_LL_TC_PROG.cpp"
}

// --------------------------- GSyntax ---------------------------
#include "GSyntax.h"

#pragma optimize("", off)
namespace LL_TC_LL1 {
#include "LL_TC_LL1.cpp"
}

namespace LR_UR_LR0 {
#include "LR_UR_LR0.cpp"
}

namespace NR_SN_LALR {
#include "NR_SN_LALR.cpp"
}
#pragma optimize("", on)

#pragma warning( disable : 4065 )
// --------------------------- YSyntax ---------------------------
#include "YSyntax.h"

int yylex (void *yylval, void *param);
void yyerror(const char* mess);

#define yy_lex yylex
#define yy_error yyerror

#include "UndefYACC.cpp"
namespace LL_TC {
#include "LL_TC_YACC.tab.c"
}

#include "UndefYACC.cpp"
namespace LR_TC {
#include "LR_TC_YACC.tab.c"
}

#include "UndefYACC.cpp"
namespace NR_TC {
#include "NR_TC_YACC.tab.c"
}

#include "UndefYACC.cpp"
namespace NR_SN {
#include "NR_SN_YACC.tab.c"
}

#define CHAR_LEX(G,T,S)  case (T_Lexeme::gr##G << 8) | T_Symbol::lx##T : return S;

#define yy_C_lex   yylex
#define yy_C_error yyerror

#include "UndefYACC.cpp"
namespace C_Grammar {
#include "C_Grammar.tab.cpp"
}

#undef ACTION
#define ACTION(MODE) ((make_mode & 0x0000000F) == A_Syntax::mm##MODE)

static void test_yacc(int type, int option, YSyntax& parse, TGrammar& table)
{
   A_Syntax::M_Mode make_mode = A_Syntax::M_Mode(OPTION_AREA(type, Main));
   A_Syntax::T_SyntaxMode syntax_mode = A_Syntax::T_SyntaxMode(OPTION_AREA(type, Method));
   int def_rule_mode = (OPTION_AREA(type, Grammar)); // 0 - LL, 1 - NL, 2 - LR, 3 - NR
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0;

   if (def_rule_mode == 0x00) {
      table.type = T_Grammar::gtLL; table.prefix = "LL_";
      parse.syntax_lexeme = T_SyntaxLexeme(table.type | T_SyntaxLexeme::slPrior | T_SyntaxLexeme::slSyntax);
      if ((ACTION(Tree)) || (ACTION(Code))) {
         parse.yy_parse = LL_TC::yy_parse;
         if (print_rule) { 
            LL_TC::yy_debug = 1; 
         }
      }
   } else if (def_rule_mode == 0x02) {
      table.type = T_Grammar::gtLR; table.prefix = "LR_";
      parse.syntax_lexeme = T_SyntaxLexeme(table.type | T_SyntaxLexeme::slPrior | T_SyntaxLexeme::slSyntax);
      if ((ACTION(Tree)) || (ACTION(Code))) {
         parse.yy_parse = LR_TC::yy_parse;
         if (print_rule) { 
            LR_TC::yy_debug = 1; 
         }
      }
   } else if (def_rule_mode == 0x03) {
      table.type = T_Grammar::gtLR; table.prefix = "NR_";
      parse.syntax_lexeme = T_SyntaxLexeme(table.type);
      if (ACTION(Tree) || ACTION(Code)) {
         parse.yy_parse = NR_TC::yy_parse;
         if (print_rule) { 
            NR_TC::yy_debug = 1; 
         }
      } else if (ACTION(Node) || ACTION(Made)) {
         parse.yy_parse = NR_SN::yy_parse;
         if (print_rule) { 
            NR_SN::yy_debug = 1; 
         }
      } else if (ACTION(None)) {
         parse.yy_parse = NR_TC::yy_parse;
         if (print_rule) { 
            NR_TC::yy_debug = 1; 
         }
      }
   } else if (def_rule_mode == 0x0C) {
      table.type = T_Grammar::gtLR; table.prefix = "C_";
      parse.syntax_lexeme = T_SyntaxLexeme(table.type | T_SyntaxLexeme::slNoDefType);
      if (ACTION(Tree)) {
         parse.yy_parse = C_Grammar::yy_C_parse;
         if (print_rule) { 
            C_Grammar::yy_C_debug = 1; 
         }
      }
   }
}

char* get_file_name(const char*file, const char* ext);

bool test(int type, int option, const char *file)
{
   TPrinter printer;

   A_Syntax::M_Mode make_mode;
   A_Syntax::T_SyntaxMode syntax_mode;
   int def_rule_mode; // 0 - LL, 1 - NL, 2 - LR, 3 - NR

   int option_mode;
   if (!OPTION_EMPTY(type, Phase)) {
      make_mode = A_Syntax::M_Mode(OPTION_AREA(type, Main));
      syntax_mode = A_Syntax::T_SyntaxMode(OPTION_AREA(type, Method));
      def_rule_mode = OPTION_AREA(type, Grammar);
      option_mode = type;
   } else {
      make_mode = A_Syntax::M_Mode((type & 0x0F0) >> 4);
      syntax_mode = A_Syntax::T_SyntaxMode(type & 0x00F);
      def_rule_mode = (type & 0xF00) >> 8;
      if (option & T_OptionMode::omQuadruple) {
         option_mode = OPTION_METHOD(ThreePhase, , def_rule_mode, QuadGenerate, BlockTable, 0, syntax_mode, make_mode);
      } else {
         option_mode = OPTION_METHOD(ThreePhase, , def_rule_mode, CodeGenerate, BlockTable, 0, syntax_mode, make_mode);
      }
   }

   T_SourceFile source;

   TGrammar   table;
   TBaseType  base_type;

	TScanArray scan(&source);

	YSyntax             parse_Y(&scan,&table);
   C_GrammarYSyntax    parse_C(&scan,&table);

   GSyntax             parse_G(&scan,&table);

   LL_TC_PROG::PSyntax     parse_LL(&scan,&table);
   NL_TC_PROG::PSyntax     parse_NL(&scan,&table);
   ETF_LL_TC_PROG::PSyntax parse_ETF_LL(&scan,&table);

   MC_Syntax* parse = NULL;
   YSyntax*   parse_YACC = NULL;

   if (syntax_mode == A_Syntax::smParseYACC) { // YACC
      if (def_rule_mode == 0x0C) {
        parse = parse_YACC = &parse_C;
        parse_C.Mask(A_Symbol::mmC);
      } else {
        parse = parse_YACC = &parse_Y;
      }
      test_yacc(option_mode, option, *parse_YACC, table);
   } else if (syntax_mode == A_Syntax::smParseFormula) { // PROG
      if (def_rule_mode == 0x00) {
         parse = &parse_LL;
         table.type = T_Grammar::gtLL; table.prefix = "LL_";
         parse->syntax_lexeme = T_SyntaxLexeme::slSyntax;
      } else if (def_rule_mode == 0x01) {
         parse = &parse_NL;
         table.type = T_Grammar::gtLL; table.prefix = "NL_";
         parse->syntax_lexeme = T_SyntaxLexeme::slNone;
      } else if (def_rule_mode == 0x05) {
         parse = &parse_ETF_LL;
         table.type = T_Grammar::gtLL; table.prefix = "ETF_LL_";
         parse->syntax_lexeme = T_SyntaxLexeme::slNone;
      }
   } else if (syntax_mode == A_Syntax::smParseRule) { // Table
      void (*make_grammar)(TGrammar& grammar) = NULL;
      if (def_rule_mode == 0x00) {
         parse = &parse_G; make_grammar = LL_TC_LL1::make_grammar;
         table.prefix = "LL_";
         syntax_mode = A_Syntax::smParseLL1;
      } else if (def_rule_mode == 0x02) {
         parse = &parse_G; make_grammar = LR_UR_LR0::make_grammar;
         table.prefix = "LR_";
         syntax_mode = A_Syntax::smParseLR0;
      } else if (def_rule_mode == 0x03) {
         parse = &parse_G; make_grammar = NR_SN_LALR::make_grammar;
         table.prefix = "NR_";
         syntax_mode = A_Syntax::smParseLR0;
      }
      if (make_grammar != NULL) {
         make_grammar(table);
         parse->syntax_lexeme = table.type;
         table.Used();
      }
   }
   if (!parse) return false;
	parse->option = option;
	parse->line_is_space = true;
   if (!parse->Source(source,file)) return false;

	TSemantic  semantic(parse);

   TData      data(&table, parse, &semantic); data.makers = &GMakerTable::maker_table;
              data.file = file;

   parse->set_make_mode(option_mode);
   parse->set_semantic(&semantic);
   parse->syntax_mode = syntax_mode;

// 0x0001 - other,      0x0002 - space,      0x0004 - line,       0x0008 - Lexeme, 
// 0x0010 - print_tree, 0x0020 - erase_code, 0x0040 - print_code, 0x0080 - print_operator, 
// 0x0100 - print_rule, 0x0200 - print_maker,0x0400 - print_stack,0x0800 - print_Code,
// 0x1000 - print_SNode

   bool gut = (parse != NULL) && semantic.Translate();

   semantic.Result(file);

   parse->print_store(printer);
	if (gut)  
		printf("\ntrue\n");
   else
		printf("\nfalse\n");
	parse->Cur().print(&scan);

	return true;
}

int main(int argc, const char* argv[])
{
   TInHelp in_help(TInHelp::YACC);
   in_help.type = 0x0C1E; // C_Grammar, Tree, YACC
//   in_help.type = 0x0243; // LL, Code, PROG
//   TranYACC.exe 01E 0838 text.cpp
//   TranYACC.exe 014 0830 text.cpp
   in_help.file = "text.cpp";
   in_help.option = 0x0830;
   in_help.type = 0x0013;
//   TranYACC.exe 243 1830 text.cpp
   in_help.type = 0x0243;
//   in_help.option = 0x1830;
//   in_help.option |= omPrintRule;
   in_help.option |= omPrintMaker;
//TranYACC.exe 35E 0830 text.cpp
   in_help.type = 0x035E;

   if (!in_help.input(argc,argv)) return 0;
   test(in_help.type, in_help.option, in_help.file);

	return 0;
}
