// TableBuilder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parse.h"
#include "GSyntax.h"
#include "FSyntax.h"
#include "InHelp.h"

#include "Maker.h"
#include "GrammarStock.h"
#include "Grammar.h"

char* get_file_name(const char*file, const char* ext);

// --------------------------- GSyntax ---------------------------

extern bool grammar_reception(TInHelp& in_help, TGrammar& table, const T_WordTable* word_table = &T_KeyWordTable::key_word_table);

void test(TInHelp& in_help)
{
   int type = in_help.type; int& option = in_help.option; const char *file = in_help.file;
   A_Syntax::M_Mode make_mode = A_Syntax::M_Mode((type & 0x0F0) >> 4);
   A_Syntax::T_SyntaxMode syntax_mode = A_Syntax::T_SyntaxMode(type & 0x00F);
   int look_ahead = (type & 0x000F0000) >> 16;

   if ((syntax_mode == A_Syntax::T_SyntaxMode::smParseYACC) || (look_ahead > 1)) {
      option |= TGrammar::POption::opNoPriorAssign;
   }

   TGrammar table;
   TNameTable names; table.names = &names;
   if (!grammar_reception(in_help, table)) return;

   T_Lexeme::word_table = &T_KeyWordTable::key_word_table;
   T_Lexeme::print_scan = NULL;

   if (!table.empty()) {
      table.Make(type, file);
      table.Print(type, file);
   }
}

int main(int argc, const char* argv[])
{
   TInHelp in_help(TInHelp::Table);
//   in_help.file = "xAxa.tab"; // "FSyntax.tab";
//   in_help.file = "LR_LRk.tab";
//   in_help.file = "..\\Table\\NR_SN_YACC.y"; 

//   in_help.table = "..\\Grammar\\ETF_LR.y";  
//   in_help.file  = "ETF_LR_.tab";
//   in_help.type  = 0x000D08;

//   in_help.option |= TGrammar::opCompression;   // 0x00200000
//   in_help.option |= TGrammar::opNoPriorAssign; // 0x00800000

//   in_help.type = 0x00021E;
//   in_help.type = 0x000407;

//   TableBuilder 02071A 0x108915FF ETF\ETF_LR_TC_LALR2.tab
//   TableBuilder 010E15 0x000911ff DefExpr\DefExpr_LLk.tab DefExpr_LL.y
//   TableBuilder 020E18 0x003931FF BNF.tab ..\Grammar\bnf.y

//   in_help.option |= TGrammar::opTable;       // 0x00002000
//   in_help.type = 0x020E18;
//   in_help.table = "bnf.y";  
//   in_help.file = "BNF.tab";

//   TableBuilder.exe E36 0x00002001 Table\FSyntax.tab Grammar\FSyntax.y
//   in_help.type = 0x000E36;
//   in_help.option = 0x00002001;
//   in_help.table = "FSyntax.y";  
//   in_help.file = "FSyntax.tab";

//   TableBuilder.exe 010015 004931FF LXk\LL_TC_LL1.tab
//   in_help.type = 0x020015;
//   in_help.option = 0x006931FF;
//   in_help.file = "LL_TC_LL2.tab";

//   in_help.type = 0x00031E;
//   in_help.option = 0x00000000;
//   in_help.option |= TGrammar::opGrammar; // | TGrammar::opBNF;
//   in_help.file = "NR_YACC_TC.y";

//   in_help.table = "NR_BNF_TC.bnf";
//   in_help.file = "NR_BNF_TC.tab";
//   in_help.type = 0x000B08;

   in_help.table = "NR_YACC_TC.yacc";
   in_help.file = "NR_YACC_TC.tab";
   in_help.type = 0x000D08;

//   in_help.type = 0x010405;
//   in_help.option = 0x004931FF;
//   in_help.file = "ETF_LLk_.tab";

//   TableBuilder 010219 00091800 ..\Table\LR_TC_LRk_Core.tab
   in_help.file = "LR_TC_LR1_Core.tab";
   in_help.type = 0x000219;
   in_help.option = 0x00091901;

   in_help.table = "Green_E_5_26.bnf";
   in_help.file = "Green_E_5.26_C.tab";
   in_help.type = 0x020B08;
   in_help.option = 0x000B1901;

   in_help.table = "ETF_LL_TC.grammar";
   in_help.file = "ETF_LL_TC_D.tab";
   in_help.type = 0x000D08;
   in_help.option = 0x000B1901;
   
//   ..\Release\TableBuilder.exe 0x040E08 0x000B1801 Core\Green_L_8_7_LRk.tab   ..\Grammar\Green_L_8_7.grammar
//   in_help.table = "Green_L_8_7.grammar";
//   in_help.file = "Green_L_8.7.tab";
//   in_help.type = 0x040E08;
//   in_help.option = 0x000B1801;

//   ..\Release\TableBuilder.exe 0x040D08 0x000B1801 Core\Green_L_8_7_LRk.tab   ..\Grammar\Green_L_8_7.grammar
//   in_help.type = 0x040D08;

//   TableBuilder 218 00391000 ..\Table\LR_TC_LR1.tab 
   in_help.file = "..\\Table\\LR_TC_LR1.tab";
   in_help.type = 0x000218;
   in_help.option = 0x00031100;

//   TableBuilder 010608 104931FF ETF\ETF_LR_LRk.tab
   in_help.file = "ETF_LR_LRk.tab";
   in_help.type = 0x010608;
   in_help.option = 0x104931FF;
//   TableBuilder 015 003931FF ..\Table\LL_TC_LL1.tab 
   in_help.file = "LL_TC_LL1.tab";
   in_help.type = 0x000015;
   in_help.option = 0x00001141;
//   TableBuilder 035 003911FF ..\Table\LL_SN_LL1.tab
   in_help.file = "LL_SN_LL1.tab";
   in_help.type = 0x000016;
   in_help.option = 0x003911FF;
//   TableBuilder 035 003911FF ..\Table\LL_SN_LL1.tab
   in_help.table = "sql.y";
   in_help.file = "sql.tab";
   in_help.type = 0x010D06;
   in_help.option = 0x00193101;
// * * * * * * *
//   TableBuilder 020E18 000910ff ETF_LR_LR2.tab ..\Grammar\ETF_LR.grammar
   in_help.table = "..\\Grammar\\ETF_GG.grammar";
//   in_help.table = "..\\Grammar\\SaSb.y";
   //   in_help.table = "..\\Grammar\\SaSb.y";
   in_help.file = "ETF_GG.tab";
   in_help.type = 0x010E18;
   in_help.option = 0x000918ff;
   in_help.option |= TGrammar::opFiUnattainable; 
//   in_help.option |= TGrammar::opSplitting;
   in_help.option |= TGrammar::opChainRule;
   in_help.option = 0x011979FF;

//   TableBuilder.exe 010E18 0x0009B9FF ETF_TC_Fi.tab ..\Grammar\ETF_LR_TC.grammar
   in_help.option = 0x0009F9FF;
   in_help.table = "..\\Grammar\\ETF_LR_TC.grammar";
//   in_help.file = "SLR_TC_Fi_.tab";
   in_help.file = "ETF_TC_Fi_.tab";
   in_help.type = 0x010E18;
//   in_help.option |= TGrammar::opSplittingAddition;
//   in_help.option |= TGrammar::opChainRule;

//   TableBuilder.exe 0x020D38 0x001931FF ..\Table\BSyntax.tab ..\Grammar\BSyntax.y
   in_help.table = "..\\Grammar\\BNFSyntax.y";
//   in_help.table = "BSyntax.grammar";
   in_help.file = "BSyntax_.tab";
   in_help.type = 0x020D38;
   in_help.option = 0x001931FF;

   in_help.table = "..\\Grammar\\ETF_TC.bif";
   in_help.file = "LL_TC_.y";
   in_help.type = 0x000A08;
   in_help.option = 0x00000101;
/*
//   TableBuilder 0x020E38 0x00013101 ..\Table\IGrammar.tab ..\Grammar\IGrammar.y
   in_help.table = "..\\Grammar\\IGrammar.y";
   in_help.file = "..\\Table\\IGrammar.tab";
   in_help.type = 0x010E38;
   in_help.option = 0x00013101;
*/
//   TableBuilder.exe 0x000A18 0x001910ff ..\Release\ETF\BIF_TC.tab ..\Grammar\BIF_TC.bif
//   TableBuilder.exe 0x000A16 0x0009110f BIF_TC.tab BIF_.grammar
   in_help.table = "..\\Grammar\\BIF_TC.bif";
   in_help.table = "BIF_.grammar";
   in_help.file = "BIF_TC.tab";
   in_help.type = 0x000A16;
   in_help.option = 0x0009110f;
//   TableBuilder 0x000E15 0x00091000 ..\Table\LLy_TC_LL1.tab ..\Grammar\LX\LL.grammar
   in_help.table = "..\\Grammar\\LX\\LL.grammar";
   in_help.file  = "..\\Table\\LLy_TC_LL1.tab";
   in_help.type = 0x000E15;
   in_help.option = 0x00091000;
//   TableBuilder.exe 0x000A16 0x0009110f ..\Table\LL_TC_BIF_LR0.tab ..\Table\LL_BIF.grammar
   in_help.table = "..\\Table\\LL_BIF.grammar";
   in_help.file = "..\\Table\\LL_TC_BIF_LR0.tab";
   in_help.type = 0x000A16;
   in_help.option = 0x0009100F;
//   TableBuilder.exe 0x000200 0x000000C1 ..\Grammar\BIF_.grammar
   in_help.file = "..\\Grammar\\BIF_.grammar";
   in_help.type = 0x000200;
   in_help.option = 0x001000C1;
//   TableBuilder.exe 02021A 0089310F LXk\LR_TC_LALR2.tab
//   TableBuilder.exe 010035 0049313F LXk\LL_SN_LLk.tab
   in_help.file = "..\\Release\\LXk\\LR_UR_LARLk.tab";
//   in_help.file = "..\\Release\\LXk\\LL_TC_LLk.tab";
   in_help.type = 0x01024A;
   in_help.option = 0x0089393F;
   in_help.option |= TGrammar::POption::opNoPriorAssign;
   in_help.option |= TGrammar::POption::opAssociation;
//   TableBuilder 000D15 1081103f Auto\ETF_TC_LL1.tab ..\Grammar\ETF_LL.grammar
   in_help.table = "..\\Grammar\\ETF_LL.grammar";
   in_help.file = "..\\Release\\Auto\\ETF_TC_LL1.tab";
   in_help.type = 0x000E15;
   in_help.option = 0x1081103F;
//   TableBuilder 514 00091000 ..\Table\ETF_LL_TC_PROG.tab
   in_help.file = "..\\Table\\ETF_LL_TC_PROG.tab";
   in_help.type = 0x000514;
   in_help.option = 0x00091200;
   in_help.type = 0x0000;
//   TableBuilder 0x020E38 0x00000041 ..\Auto\BGrammar.tab ..\Grammar\BGrammar.y
   in_help.table = "..\\Grammar\\BGrammar.grammar";
   in_help.file = "..\\Release\\Auto\\BGrammar.tab";
   in_help.type = 0x020B38;
   in_help.option = 0x0001317F;
//   TableBuilder 0x020A38 0x00002041 ..\Table\IGrammarBIF.grammar ..\Grammar\IGrammar.bif
   in_help.table = "..\\Grammar\\IGrammar.bif";
   in_help.file = "..\\Table\\IGrammarBIF.tab";
   in_help.type = 0x020A38;
   in_help.option = 0x00002041;
//   TableBuilder.exe 0x000A15 0x0009114f ..\Table\ETF_TC_BIF_LL1.tab ..\Grammar\ETF_.bif
   in_help.table = "..\\Grammar\\LX\\LL.bif";
//   in_help.table = "..\\Grammar\\ETF_.bif";
   in_help.file = "..\\Table\\ETF_TC_BIF_LL1.tab";
   in_help.type = 0x000A15;
   in_help.option = 0x0009114f;
//   in_help.option |= TGrammar::POption::opSelfParsing;
//   TableBuilder 0x020A48 0x00002141 ..\Table\IGrammarBIF.tab ..\Grammar\IGrammar.bif
   in_help.table = "..\\Grammar\\IGrammar.bif";
   in_help.file = "..\\Table\\IGrammarBIF.tab";
   in_help.type = 0x020A48;
   in_help.option = 0x00002141;

//   TableBuilder.exe 0x000200 0x000000C1 ..\Table\LR_BIF.grammar
   in_help.file = "LL_BIF.grammar";
   in_help.type = 0x000000;
   in_help.option = 0x000000C1;
//   TableBuilder 0x000E30 0x000000C1 ..\Table\IGrammarBNF.grammar ..\Grammar\IGrammar.y
   in_help.table = "..\\Grammar\\IGrammar.bnf";
   in_help.file = "..\\Table\\IGrammarBIF.tab";
   in_help.type = 0x020B30;
   in_help.option = 0x000000C1;
//   TableBuilder 0x000F45 0x00003140 ..\Grammar\LX\LL.bif ..\Table\IGrammarLLk.tab
   in_help.table = "..\\Table\\IGrammarLRk.tab";
   in_help.file = "..\\Grammar\\LX\\LL.bif";
   in_help.type = 0x000915;
   in_help.option = 0x00003140 | TGrammar::POption::opSelfParsing;
//   TableBuilder 0x000915 0x40003140 ..\Grammar\LX\LL.bif ..\Table\IGrammarLRk.tab
//   TableBuilder 0x000915 0x00003140 ..\Grammar\LX\LL.y ..\Table\FGrammar.tab
   in_help.table = "..\\Table\\FGrammar.tab";
   in_help.file = "..\\Grammar\\LX\\LL.y";
   in_help.type = 0x000915;
   in_help.option = 0x00003140;
//   TableBuilder.exe 0x000200 0x000000C1 ..\Grammar\LX\_LX_.grammar
   in_help.file = "..\\Grammar\\LX\\_LX__.grammary";
   in_help.type = 0x000000;
   in_help.option = 0x000000C1;
//   in_help.file = "LX\\_LX_.grammary";

   in_help.table = "..\\Grammar\\ETF_LR_TC.grammar";
   in_help.file = "ETF_LR_TC.tab";
   in_help.type = 0x000D18;
   in_help.option = 0x100911FF;

//   TableBuilder.exe 0x000200 0x00000001 ..\Grammar\LX\_LX_.grammar
   in_help.file = "..\\Grammar\\LX\\_LX_.grammar";
//   in_help.table = "..\\Grammar\\Purple_4_3_1.y";
//   in_help.file = "Purple_4_3_1_.tab";
//   in_help.table = "..\\Grammar\\Green_E_5_11_.y";
//   in_help.file = "Green_E_5_11_.tab";
   in_help.type = 0x010115;
   in_help.option = 0x00001001;
//   TableBuilder 0x010B15 0x00001100 ..\Table\NR_Left_TC_LL1.tab ..\Grammar\LX\NR_Left.bnf
   in_help.file = "..\\Table\\NR_Left_LL1.bnf";
   in_help.table = "..\\Grammar\\LX\\NR_Left.bnf";
   in_help.type = 0x010B15;
   in_help.option = 0x00001100;
//   TableBuilder 33E 00391000 ..\Table\NR_SN_YACC.y
   in_help.file = "..\\Table\\NR_SN_YACC.y";
   in_help.type = 0x00033E;
   in_help.option = 0x00391000;
//   TableBuilder 338 10091101 ..\Table\NR_SN_LR1.tab
   in_help.file = "..\\Table\\NR_SN_LR1.tab";
   in_help.type = 0x000338;
   in_help.option = 0x10091101;
//   TableBuilder.exe E1D 0x00011101 Table\C99_Grammar.tab Grammar\C99_Grammar.y
   in_help.file = "..\\Table\\C99_Grammar.tab";
   in_help.table = "..\\Grammar\\C99_Grammar.y";
   in_help.type = 0x000E1D;
   in_help.option = 0x00091101;
//   TableBuilder.exe 0x20000035 0x1009113F ..\Table\LL_SN_LL1_Block.tab
   in_help.file = "..\\Table\\LL_SN_LL1_Block.tab";
   in_help.type = 0x20000035;
   in_help.option = 0x1009113F;
//   TableBuilder.exe 0x200000F0 0x00000001 d_LX_.grammar
   in_help.table = "d_LX_.g";
   in_help.file = "d_LX_.grammar";
   in_help.type = 0x20000EF0;
   in_help.option = 0x00000001;

//   if (!in_help.input(argc,argv)) return 0;
   test(in_help);

	return 0;
}
