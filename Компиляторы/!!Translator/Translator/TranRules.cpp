// TranRules.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parse.h"
#include "ASyntax.h"
#include "RSyntax.h"
#include "TSemantic.h"
#include "Maker.h"
#include "InHelp.h"
#include "GrammarStock.h"
#include "Grammar.h"

// --------------------------- main ---------------------------

/*
   mode  { 0x00XX - formula + LL, 0x01XX - formula + NL }
   make  { mmNone = 0x0000, mmTree = 0x0010, mmCode = 0x0020, mmNode = 0x0030, mmTurn = 0x0040, mmMade = 0x0050 };  
*/

char* get_file_name(const char*file, const char* ext);

bool test(int type, int option, const char *file, const char *table_file)
{
   A_Syntax::M_Mode make_mode;
   A_Syntax::T_SyntaxMode syntax_mode;
   TGrammar::T_SourceGrammar def_rule_mode; // 000 - LL(F), 100 - NL(F)
   int option_mode = 0;
   if (!OPTION_EMPTY(type, Phase)) {
      make_mode = A_Syntax::M_Mode(OPTION_AREA(type, Main));
      syntax_mode = A_Syntax::T_SyntaxMode(OPTION_AREA(type, Method));
      def_rule_mode = TGrammar::T_SourceGrammar(OPTION_AREA(type, Grammar));
      option_mode = type;
   } else {
      make_mode = A_Syntax::M_Mode((type & 0x0F0) >> 4);
      syntax_mode = A_Syntax::T_SyntaxMode(type & 0x00F);
      def_rule_mode = TGrammar::T_SourceGrammar((type & 0xF00) >> 8);
      if (option & T_OptionMode::omQuadruple) {
         option_mode = OPTION_METHOD(ThreePhase, , def_rule_mode, QuadGenerate, BlockTable, 0, syntax_mode, make_mode);
      } else {
         option_mode = OPTION_METHOD(ThreePhase, , def_rule_mode, CodeGenerate, BlockTable, 0, syntax_mode, make_mode);
      }

   }

   T_SourceFile source;
   TGrammar   table;

	TScanArray scan(&source);
	RSyntax    parse(&scan,&table);

	parse.option = option;
	parse.line_is_space = true;
   if (!parse.Source(source,file)) return false;

   TSemantic  semantic(&parse);

   TData      data(&table, &parse, &semantic); data.makers = &GMakerTable::maker_table;
              data.file = file;

   bool ret;
   if (def_rule_mode == TGrammar::sgGrammar) {
      int table_type;
      ret = table.read(table_file,table_type,0x00);
   } else {
      ret = build_grammar(table, option_mode, 0x00);
      if (def_rule_mode == 0x01) { // NL
         parse.syntax_lexeme = T_SyntaxLexeme::slNone;
      }
   }
   if (!ret || (table.type & T_Grammar::gtLR)) return false;
   TPrinter printer;
   table.print(printer);
   parse.set_semantic(&semantic);
   parse.set_syntax_mode(syntax_mode);

   if ((syntax_mode == A_Syntax::smParseStackRule) && (option & T_OptionMode::omSelectProduce)) { // select_produce
      table.make_lexemes();
      table.make_FIRSTs();
      table.make_FIRSTsP();
   }

   parse.set_make_mode(option_mode);

   bool gut = semantic.Translate();

   semantic.Result(file);

   parse.print_store(printer);
	if (gut)  
		printf("\ntrue\n");
   else
		printf("\nfalse\n");
	parse.Cur().print(&scan);

	return true;
}

int main(int argc, const char* argv[])
{
   TInHelp in_help(TInHelp::Rules);
   in_help.type = 0x011;
   in_help.file = "text.cpp";
   in_help.option = 0x0820;
//   in_help.option = 0x1831;
   in_help.option = 0x8830;

//   TranRules.exe 031 1830 text.cpp
   in_help.type = 0x031;
   in_help.option = 0x0810;
//   in_help.option |= T_OptionMode::omPrintSyntax | T_OptionMode::omPrintSemantic;
//   TranRules.exe 1031 1830 text.cpp
   in_help.type = OPTION_METHOD(ThreePhase, , TGrammar::sgLL, CodeGenerate, BlockTable, 0, A_Syntax::smParseStackRule, A_Syntax::M_Mode::mmTree);
   in_help.type = OPTION_METHOD(TwoPhase, , TGrammar::sgLL, CodeGenerate, BlockTable, 0, A_Syntax::smParseStackRule, A_Syntax::M_Mode::mmMade);
   in_help.type = OPTION_METHOD(TwoPhase, , TGrammar::sgGrammar, CodeGenerate, BlockTable, 0, A_Syntax::smParseStackRule, A_Syntax::M_Mode::mmMade);
   in_help.table = "..\\Table\\LL_SN_LL1_Block.tab";
//   in_help.type = OPTION_METHOD(TwoPhase, , TGrammar::sgLL, CodeGenerate, TreeSearch, 0, A_Syntax::smParseStackRule, A_Syntax::M_Mode::mmCall);
   in_help.option |= T_OptionMode::omPrintRule ;
   in_help.option |= T_OptionMode::omPrintLexeme;
   in_help.option |= T_OptionMode::omPrintMaker;
   in_help.file = "test.cpp";
   in_help.type = 0x0011; in_help.option = 0x0830;
//   TranRules.exe    0x30F12016 0x00000830 test.cpp d_LX_.tab
   in_help.type = 0x30F12016; in_help.option = 0x00000830;
   in_help.table = "d_LX_.tab";

   if (!in_help.input(argc,argv)) return 0;
   test(in_help.type, in_help.option, in_help.file, in_help.table);

	return 0;
}
