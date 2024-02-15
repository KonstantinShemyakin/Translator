// TranSyntax.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parse.h"
#include "ASyntax.h"
#include "Syntax.h"
#include "CSyntax.h"
#include "TSyntax.h"
#include "DSyntax.h"
#include "MSyntax.h"
#include "TSemantic.h"
#include "Grammar.h"
#include "InHelp.h"

// --------------------------- main ---------------------------

char* get_file_name(const char*file, const char* ext);

enum TYPE_SYNTAX { NONE, SYNTAX, TSYNTAX, CSYNTAX, MSYNTAX_T, MSYNTAX_C, DSYNTAX };

bool test(int type, int option, const char *file)
{
   int syntax_type = type, option_mode = 0;
   if (!OPTION_EMPTY(type, Phase)) {
      syntax_type = OPTION_AREA(type,Method);
   }

   T_SourceFile source;
   TPrinter printer;

	TSemantic semantic(NULL);
   TGrammar  table;
   TBaseType base_type;

	TScanArray scan(&source);
	T_Syntax   tparse(&scan);
	CSyntax   c_parse(&scan);
	TSyntax   t_parse(&scan);
   DSyntax   d_parse(&scan);
   MSyntax   m_parse(&scan,&table);
   A_Syntax* parse = NULL;

   switch (syntax_type) {
   case SYNTAX : 
      parse = &tparse;
      option_mode = OPTION_METHOD(OnePhase, , 0, , , 0, SYNTAX, A_Syntax::mmNone);
      break;
   case TSYNTAX : 
      parse = &t_parse;
      option_mode = OPTION_METHOD(ThreePhase, ,0 , CodeGenerate, BlockTable, 0, TSYNTAX, A_Syntax::mmTree);
      break;
   case DSYNTAX:
      parse = &d_parse;
      option_mode = OPTION_METHOD(ThreePhase, ,0 , CodeGenerate, BlockTable, 0, DSYNTAX, A_Syntax::mmTree);
      break;
   case CSYNTAX :
      parse = &c_parse;
      c_parse.set_semantic(&semantic);
      option_mode = OPTION_METHOD(OnePhase, ,0 , CodeGenerate, BlockTable, 0, CSYNTAX, A_Syntax::mmCode);
      break;
   case MSYNTAX_T : 
   case MSYNTAX_C : 
      parse = &m_parse;
      m_parse.set_semantic(&semantic);
      if (syntax_type == MSYNTAX_T) {
         if (option & T_OptionMode::omQuadruple) {
            option_mode = OPTION_METHOD(ThreePhase, ,0 , QuadGenerate, BlockTable, 0, MSYNTAX_T, A_Syntax::mmTree);
         } else {
            option_mode = OPTION_METHOD(ThreePhase, ,0 , CodeGenerate, BlockTable, 0, MSYNTAX_T, A_Syntax::mmTree);
         }
      } else {
         option_mode = OPTION_METHOD(OnePhase, ,0 , CodeGenerate, BlockTable, 0, MSYNTAX_C, A_Syntax::mmCode);
      }
      table.makers = &GMakerTable::maker_table;
      break;
   default : 
      parse = &tparse;
      option_mode = OPTION_METHOD(ThreePhase, ,0 , CodeGenerate, BlockTable, 0, TSYNTAX, A_Syntax::mmTree);
      break;
   }

   if (!OPTION_EMPTY(type, Phase)) {
      parse->set_make_mode(type);
   } else {
      parse->set_make_mode(option_mode);
   }

	parse->option = option;
	parse->line_is_space = true;
   semantic.syntax = parse;
   if (!parse->Source(source,file)) return false;

// 0x0001 - other,      0x0002 - space,      0x0004 - line,       0x0008 - eof, 
// 0x0010 - print_tree, 0x0020 - erase_code, 0x0040 - print_code, 0x0080 - print_operator, 
// 0x0100 - print_rule, 0x0200 - print_maker,0x0400 - print_stack,0x0800 - print_Code 
	
   TData      data(&table, parse, &semantic); data.makers = &GMakerTable::maker_table;
   data.file = file;

   bool gut = semantic.Translate();

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
   TInHelp in_help(TInHelp::Syntax);
//   in_help.file = "Class_02_ERROR.c";
   in_help.file = "text.cpp";
   in_help.option = 0x0810;
//   in_help.option |= T_OptionMode::omAtOnce;
//   in_help.option |= T_OptionMode::omPrintSyntax;
//   in_help.option |= T_OptionMode::omPrintSemantic;
//   in_help.option |= T_OptionMode::omSyntaxOnly;

//   in_help.option |= T_OptionMode::omQuadruple;
//   TranSyntax.exe 2 0830 Example_09.cpp
//   in_help.file = "test_L.cpp";
//   in_help.type = CSYNTAX;
//   in_help.type = TSYNTAX;
   in_help.type = MSYNTAX_C;
//   in_help.type = OPTION_METHOD(OnePhase  , , 0, CodeGenerate, BlockTable, 0, CSYNTAX, A_Syntax::M_Mode::mmCode);
//   in_help.type = OPTION_METHOD(OnePhase  , , 0, CodeGenerate, BlockTable, 0, MSYNTAX_C, A_Syntax::M_Mode::mmCode);
   in_help.type = OPTION_METHOD(ThreePhase, , 0, CodeGenerate, TreeSearch, 0, MSYNTAX_T, A_Syntax::M_Mode::mmTree);
//   in_help.type = OPTION_METHOD(ThreePhase, , 0, CodeGenerate, TreeSearch, 0, DSYNTAX, A_Syntax::M_Mode::mmTree);
//   in_help.type = OPTION_METHOD(TwoPhase, , TGrammar::sgLL, CodeGenerate, TreeSearch, 0, DSYNTAX, A_Syntax::M_Mode::mmTree);
//   in_help.type = OPTION_METHOD(TwoPhase, , TGrammar::sgLL, CodeGenerate, BlockTable, 0, DSYNTAX, A_Syntax::M_Mode::mmTree);
   in_help.file = "test.cpp";
//   TranSyntax.exe 3 0820 test.cpp
   in_help.type = 3;
   in_help.option = 0x0830;

   if (!in_help.input(argc,argv)) return 0;
   test(in_help.type, in_help.option, in_help.file);

	return 0;
}
