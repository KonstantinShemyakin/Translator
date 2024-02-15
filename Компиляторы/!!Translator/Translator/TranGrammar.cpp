// TranGrammar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parse.h"
#include "GSyntax.h"
#include "MSyntax.h"
#include "TSemantic.h"
#include "InHelp.h"
#include "CGrammar.h"
#include "Grammar.h"

#include "C99_Lexer.h"

// --------------------------- C_Grammar_Syntax ---------------------------

class C_GrammarGSyntax : public GSyntax, public C_Grammar_Syntax
{
public:
   C_GrammarGSyntax(T_Scan *s, TGrammar* g) :GSyntax(s,g), C_Grammar_Syntax(this) {}
   virtual bool Translate();
   virtual bool Command(int command) { return C_Grammar_Syntax::Command(command); }
	virtual T_Lexeme::T_Group Lexeme(T_Lexeme &l);
   virtual bool VerifyAction(const GSymbol& sym) { return VerifyLR0(sym); }
};

bool C_GrammarGSyntax::Translate()
{
   blocks.Push(C_GrammarIdentTable::T_Block::Global); 
   bool ret = GSyntax::Translate();
   blocks.Pop();
   return ret;
}

T_Lexeme::T_Group C_GrammarGSyntax::Lexeme(T_Lexeme &l)
{
   A_Syntax::Lexeme(current_lexeme);
   UpdateLexeme(current_lexeme);
   l = current_lexeme;

   return l.group;
}

#undef ACTION 
#define ACTION(MODE) (make_mode == A_Syntax::M_Mode::mm##MODE)

bool test(int type, int option, const char *file, const char *table_file)
{
   const int C_syntax = GSyntax::M_Mode::mmC_Syntax, C99_syntax = GSyntax::M_Mode::mmC99_Syntax;
   int make_mode, scan_type;
   int option_mode = 0;
   if (!OPTION_EMPTY(type, Phase)) {
      make_mode = A_Syntax::M_Mode(OPTION_AREA(type, Main));
      scan_type = OPTION_AREA(type, Lexer);
   } else {
      make_mode = A_Syntax::M_Mode(type & 0x0F);
      scan_type = (type & 0xF0) >> 4;
   }
   if ((make_mode < 0) || (make_mode > C99_syntax)) {
      printf("\nmode error : %d", make_mode);
      return false;
   }
	T_SourceFile source;
   TGrammar     table;

	TScanArray  scan(&source);
   T_FlexLexer lexer(&source);

	GSyntax          parse_g(&scan,&table);
	C_GrammarGSyntax parse_C(&scan,&table);
	GSyntax*         parse;

   if ((make_mode == C_syntax) || (make_mode == C99_syntax)) { // C_Grammar
      parse = &parse_C;
   } else {
      parse = &parse_g;
   }
   parse->option = option;
	parse->line_is_space = true;
	
   if (scan_type) {
      if (!lexer.Open()) return false;
      parse->Scan(&lexer);
   }
   if (!parse->Source(source, file)) return false;

	TSemantic  semantic(parse);

   TData      data(&table, parse, &semantic); data.makers = &GMakerTable::maker_table;
              data.file = file;

   int table_type;
   A_Syntax::T_SyntaxMode syntax_type;
   if (!table.read(table_file,table_type,0x00)) return false;
 
   TPrinter printer;
   if (table_type & T_Grammar::gtLL) {
      table.Mtable.print(printer);
      syntax_type = A_Syntax::smParseLL1;
   } else if (table_type & T_Grammar::gtLR) {
      table.LRtable.print(printer);
      syntax_type = A_Syntax::smParseLR0;
   }
   table.print(printer);

   T_Grammar grammar_type = table.type;
   bool yes_C = false;
   if ((make_mode == C_syntax) || (make_mode == C99_syntax)) { // C_Grammar
      table.type = T_SyntaxLexeme(table.type | T_SyntaxLexeme::slNoSave); // !SaveLexeme
      parse_C.Mask((make_mode == C_syntax) ? A_Symbol::mmC : A_Symbol::mmC_99);
      make_mode = GSyntax::M_Mode::mmTree; yes_C = true;
   }
   if (ACTION(Tree) && !(grammar_type & T_Grammar::mtTree) ||
       ACTION(Code) && !(grammar_type & T_Grammar::mtCode) ||
       ACTION(Call) && !(grammar_type & T_Grammar::mtCall) ||
      (ACTION(Node) || ACTION(Made)) && !(grammar_type & T_Grammar::mtSNode)
      ) {
      make_mode = M_Syntax::mmNone;
   }
   type = (type & ~0x0000000F) | make_mode;
   parse->set_semantic(&semantic);
   parse->syntax_mode = syntax_type;
   parse->syntax_lexeme = table.type;
   parse->look_ahead = table.look_ahead;

   if (!OPTION_EMPTY(type, Phase)) {
      parse->set_make_mode(type);
   } else {
      if (yes_C) {
         option_mode = OPTION_METHOD(ThreePhase, , 0, CodeGenerate, , scan_type, 0, make_mode);
      } else {
         if (option & T_OptionMode::omQuadruple) {
            option_mode = OPTION_METHOD(ThreePhase, , 0, QuadGenerate, BlockTable, scan_type, 0, make_mode);
         } else {
            option_mode = OPTION_METHOD(ThreePhase, , 0, CodeGenerate, BlockTable, scan_type, 0, make_mode);
         }
      }
      parse->set_make_mode(option_mode);
   }

   bool gut = semantic.Translate();

   if (parse->option & T_OptionMode::omTrimUnit) {
      parse->unit.trim();
   }

   semantic.Result(file);

   parse->print_store(printer);

	if (gut) { 
		printf("\ntrue\n");
   } else {
		printf("\nfalse\n");
   }
	parse->Cur().print(&scan);

	return true;
}

int main(int argc, const char* argv[])
{
   TInHelp in_help(TInHelp::Grammar);
   in_help.type = 0x007; // 0x010 + M_Syntax::mmCode; M_Syntax::mmTurn + 2; // GSyntax::M_Mode::mmTurn + 1;
   //   in_help.table = "NR_SN_LR1.tab"; 
   in_help.table = "NR_LR0.tab";
//   in_help.table = "LL_TC_LLk.tab";
//   in_help.table = "ETF_LR_LR0.tab";
//   in_help.table = "ETF_LL_LL1.tab";
//   in_help.table = "ETF_LL_LR0.tab";
//   in_help.table = "C_Grammar.tab";
   in_help.option = 0x0830;

//   in_help.file = "..\\TranBuilder\\FSyntax.y";
   in_help.file = "text.cpp";
//   in_help.file = "text_c.cpp";
//   in_help.option = 0x5FF8;

//   TranGrammar 6 000820 text.cpp NR_LR0_Auto.tab
   in_help.file = "text.cpp";
   in_help.type = 0;
   in_help.option = 0x0000;
   in_help.option |= T_OptionMode::omPrintTree;
   in_help.option |= T_OptionMode::omAutoTree;
   in_help.table = "NR_LR0_Auto.tab";

//   TranGrammar.exe 3 1830 text.cpp ..\Table\LL_SN_LL2.tab
//   TranGrammar.exe 3 1830 text.cpp ..\Table\LL_SN_LL1.tab
   in_help.type = 0x0011;
   in_help.file = "text.cpp";
   in_help.option = 0x00000830;
//   in_help.option |= T_OptionMode::omTreeTraversal;
   in_help.table = "..\\Table\\LR_TC_LR0.tab";

//   TranGrammar.exe 15 1830 text.cpp ..\Table\NR_SN_LR1.tab

//   TranGrammar.exe 11 0830 text.cpp ..\Table\LR_TC_LR0.tab

//   TranGrammar.exe 1 4FF8 Example_02.cpp Example\02_ETF_LL_TC_LL1.tab
   in_help.type = 0x0001;
   in_help.file = "Example_02.cpp";
   in_help.option = 0x00004FF8;
   in_help.table = "02_ETF_LL_TC_LL1.tab";
//   TranGrammar.exe 5 1830 text.cpp ..\Table\LL_SN_LL1.tab
   in_help.type = 0x0001;
   in_help.file = "text.cpp";
   in_help.option = 0x00001830;
//   in_help.option |= T_OptionMode::omPrintRule | T_OptionMode::omPrintStack;
   in_help.option |= T_OptionMode::omPrintMaker;
   in_help.option |= T_OptionMode::omAtOnce;
   in_help.table = "..\\Table\\LL_TC_LR1.tab";
//   TranGrammar.exe 15 1830 text.cpp ..\Table\NR_SN_LR1.tab
//   TranGrammar.exe 1 0838 text.cpp ..\Grammar\BIF_TC.tab
   in_help.table = "..\\Grammar\\BIF_TC.tab";
   in_help.file = "text.cpp";
   in_help.option = 0x0000838;
//   TranGrammar.exe 1 0830 text.cpp ..\Grammar\BIF_TC.bif
//   TranGrammar.exe 1 1830 text.cpp ..\Table\LL_TC_LL1.tab
   in_help.table = "..\\Table\\LL_SN_LL1.tab";
   in_help.type = 0x0003;
   in_help.file = "text.cpp";
   in_help.option = 0x00001830;
//   TranGrammar.exe 1 40820 text.cpp LXk\LR_TC_SLRk.tab
//   TranGrammar.exe 1 4493F text.cpp LXk\LR_TC_LARL2.tab
//   TranGrammar.exe 1 41830 text.cpp ..\Table\LL_TC_LL1.tab
   in_help.table = "..\\Table\\LL_SN_LL1.tab";
   in_help.table = "..\\Release\\LXk\\LR_UR_LARLk.tab";
   in_help.type = 0x0004;
   in_help.file = "text.cpp";
   in_help.option = 0x00061830;
//   TranGrammar.exe 1 0B28 text.cpp  ..\Table\LL_TC_LL1.tab
   in_help.table = "..\\Table\\LR_TC_LR1.tab";
   in_help.type = 0x0001;
   in_help.option = 0x00B28;
//   TranGrammar.exe 0 0938 text.cpp ..\Grammar\LX\_LX_.tab
   in_help.table = "..\\Grammar\\LX\\_LX_.tab";
//   TranGrammar.exe 4 0820 text.cpp ..\Table\LR_Left_UR_LL1.tab
   in_help.table = "..\\Table\\LR_Left_UR_LL1.tab";
   in_help.type = 0x0004;
   in_help.option = 0x00820;
//   TranGrammar 1 0820 text.cpp ..\Table\NR_Left_TC_LL1.tab
   in_help.table = "..\\Table\\NR_Left_TC_LL1.tab";
   in_help.type = 0x0001;
   in_help.option = 0x00B28;
//   TranGrammar.exe 6 0308 test_c.cpp ..\Table\C_Grammar_Left_LRk.tab
//   TranGrammar.exe 6 0008 text_c.cpp ..\Table\C_Grammar.tab
   in_help.table = "..\\Table\\C_Grammar.tab";
   in_help.type = 0x0006;
   in_help.option = 0x00308;
//   in_help.file = "text_c.cpp";
//   TranGrammar.exe 11 0838 text.cpp ..\Table\NR_TC_LR1.tab
   in_help.type = 0x0001;
   in_help.option = 0x00830;
   in_help.option |= omPrintMaker;
   in_help.table = "..\\Table\\NR_TC_LR1.tab";
   in_help.file = "test_L.cpp";
//   TranGrammar.exe 3 1B30 text.cpp ..\Table\NR_SN_LR1.tab
//   TranGrammar.exe 15 1830 text.cpp ..\Table\NR_SN_LR1.tab
   in_help.type = 0x0000;
   in_help.option = 0x00830;
//   in_help.option |= omPrintMaker;
   in_help.table = "..\\Table\\NR_SN_LR1.tab";
   in_help.file = "text.cpp";
//   TranGrammar.exe 0 00444008 Test_Define.cpp Table\ETF_Define.tab
   in_help.type = 0x0000;
   in_help.option = 0x4008;
   in_help.option |= omAutoTree | omAutoNoDigit | omPrintTree;
   in_help.table = "ETF_Define.tab";
   in_help.file = "Test_Define.cpp";
//   TranGrammar.exe 1 0800 stack.cpp Table\LR_TC_LR0.tab
   in_help.table = "..\\Table\\LR_TC_LR0.tab";
   in_help.file = "stack.cpp";
   in_help.type = 0x0001;
   in_help.option = 0x0800;
   in_help.option |= omPrintMaker;
   in_help.option |= T_OptionMode::omPrintSyntax | T_OptionMode::omPrintSemantic;
//   TranGrammar.exe D 0000 text_c.cpp ..\Table\C99_Grammar.tab
   in_help.table = "..\\Table\\C99_Grammar_.tab";
   in_help.file = "test.cpp";
   in_help.type = 0x000D;
   in_help.option = 0x0108;
//TranGrammar.exe  0x20011015 0x00000830 text.cpp ..\Table\LL_SN_LL1_Block.tab
   in_help.table = "..\\Table\\LL_SN_LL1_Block.tab";
   in_help.file = "text.cpp";
   in_help.type = 0x20011015;
   in_help.option = 0x00000830;
//TranGrammar.exe 1 0820 text.cpp ..\Table\LL_TC_LL1.tab
   in_help.table = "..\\Table\\LL_TC_LL1.tab";
   in_help.type = 1;
   in_help.option = 0x00000820;

   if (!in_help.input(argc,argv)) return 0;
   test(in_help.type, in_help.option, in_help.file, in_help.table);

	return 0;
}
