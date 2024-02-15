// Translator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parse.h"
#include "GrammarCFG.h"
#include "Grammar.h"
#include "GBuilder.h"
#include "InHelp.h"

#define RULES

#ifdef RULES
#include "GSyntax.h"
#include "MSyntax.h"
#include "PSyntax.h"
#include "FSyntax.h"
#include "TSemantic.h"
#endif

#include "GrammarStock.h"

T_Stock stock = T_Stock::msNone, stock_grammar = T_Stock::msNone, stock_media = T_Stock::msNone, stock_make = T_Stock::msNone;

// --------------------------- main ---------------------------

#include "Maker.h"
#include "SNodes.h"

#pragma optimize("", off)
#define FORMULA_MACRO_DEFINE
#include "RuleMacro.h"

static void build_formulas(TGrammar &table, TRuleNames &names) 
{

   GFormulaTable& formulas = table.formulas;

#if defined(DEFINE_GRAMMAR_ETF_LL)

   stock_grammar = T_Stock::msETF_LL;

#elif defined(DEFINE_GRAMMAR_EXPR_LR)

   stock_grammar = T_Stock::msEXPR_LR;

#elif defined(DEFINE_GRAMMAR_ETF_LR)

   stock_grammar = T_Stock::msETF_LR;

#elif defined(DEFINE_GRAMMAR_EEE_LR)

   stock_grammar = T_Stock::msEEE;

#elif defined(DEFINE_GRAMMAR_EbEpE)

   stock_grammar = T_Stock::msEbEpE;

#elif defined(DEFINE_GRAMMAR_LL)
   stock_grammar = T_Stock::msLL; table.prefix = "LL_";
#elif defined(DEFINE_GRAMMAR_NL)
   stock_grammar = T_Stock::msNL; table.prefix = "NL_";
#elif defined(DEFINE_GRAMMAR_LR)
   stock_grammar = T_Stock::msLR; table.prefix = "LR_";
#elif defined(DEFINE_GRAMMAR_NR)
   stock_grammar = T_Stock::msNR; table.prefix = "NR_";
#endif
   stock_media = T_Stock::msMFormula;

}
#pragma optimize("", on)

bool test()
{
   bool source_file = false;
#define TEXT_SOURCE_
#ifdef TEXT_SOURCE
//	T_Source source("i1 = i1[4] +=  1*(-(i12) + -i+3)*4+5*f(0.5-4.4)/(1.1 < i2++), ((i12)-- + -i+3)");
//	T_Source source("int i, j=i=12, arr[3];\n i = 5; j-=i++; arr[0]=2; arr[1]=arr[0]++; arr[2]=arr[0]+arr[1];");
//	T_Source source("int i,j,k=1; double i=j=k, f() { for(;;); } ;");
//	T_Source source("int a[]={10,11,12}; int b[2]={20,a[1]};");
//	T_Source source("int a[]={10,11,12}; int i=0, j; a[++i];");
//	T_Source source("int i,j=+--++i;"); // = 12 + 5 * 6, j = +i++; void f() { for (int i=0; i<4;i++) { int j; f(); break; continue; } }");
//	T_Source source("void f(int i) { i++; }; void main() { f(5.0); }");
//	T_Source source("static const int A[][3] = {{1,2,3},{4,5,6}}; int a[], i, b[7][8];");//int  g = 99; void u(); void f005() { int a[5]; a[1] = 1.2; }; int f() { return 12; }; void main005() { f005(); int i; i = g + 13; }");
//	T_Source source("int g = 99; void u(); void f() { int a[5]; a[1] = 1.2; }; int f() {}; void main() { f(); int i; i = g + 13; }");
//	T_Source source("int k; void f(int i, int j, int t) { if (!j) i++; else i--; int q,r,w,z; }; void main() { f(5,1,6); int w; }");
//	T_Source source("void f() { return; return 12; } int r() { return; return 1.2; }");
// T_Source source("void f() { if (12) 13; else 14; for(;;); for (int i=0; i<4; i++) {} }");
//	T_Source source("int  a[1], d[][3], c[11][22][33];");
//	T_Source source("void f() { int i=0,j=j; i=12; for(;j=i;1,2,3){} j+=i=i++; }");
//	T_Source source("void r() { return; } void f() { int i=0,j=i; L1:i=12; { int k; goto L15; L15: goto L2; } {{ int jjj; L2: ; }} }");
//	T_Source source("int i=(123 || 321,int((const int)12.2));");
//	T_Source source("void f() { int i; L1: L2: int g; goto L2; L3: L4:; }");
//	T_Source source("void r(int i, int j) { 1;2;3; 4,5,6; f(7,8); if (9,10) 11; else 12; for (21,22;23,24;25,26) {} }");
//	T_Source source("void f(int i, int j) { f(i=7-6,8+9); i=7-6; }");
// T_Source source("int a=33,b=33; int f(int i, int j) { int q,w,e,r; if (i) return 2.1; else { j = 13; return j; } } void f() {int aa=a,k,m; } ");
// T_Source source("void f008() { for (int i=0; i<4; i++) {} }"); // if (12) 13; else 14; for(;;); 
//	T_Source source("int j=5, a[3][4]; int i = a[2][3]; ");
//	T_Source source("int f(int a[3][4]=22, double b[][44]){int i=a[55][66]+b[77][88]+f(99,12.21); return i; };"); // int i = a[11,12 || 21,13][31,32,33 && 44]; ");
//	T_Source source("void i() { int i = (int(12 || 21,33,44)); for(4;7;9)11; do ; while(i>23); };");
//	T_Source source("void i() { int i = 11 || 12; 11 ? 12 || 21 : 22; };");
//	T_Source source("int i = (4 || 5) ? 6.3 : (7 && 8); ");
//	T_Source source("void f() { if ((11 || 1.2) && (13 || !21) && !(22 || 23)) 31; else 32; }");
// T_Source source("void f() { int i=12; i++; int &j = i; goto label; break; continue; return; return 123; {} { i = 24; } }");
// T_Source source("void f() { if (!(11 || 12)) 2+1; else 3-1; }");
// T_Source source("void f() { int i = (11 || 12); while (int j = 13) i++; }");
//	T_Source source("void f() { for (int i;33;i++) { continue; i--; break; i++; } }");
//	T_Source source("static const int A[][3] = {{1,2,3},{4,5,6}}; int a[], i, b[7][8]; void f() { } void F() { f(); } void main() { f(); F(); a[2,1] = 12; i = 33; i = i; } "); 
//	T_Source source("int a[] = { 11, 12.21,-55 }, b[2][3] = {{ 21, 22 }, { 31, 32 }};");
//	T_Source source("int a[1][1][1][1] = { 1111 };");
//	T_Source source("int a[] = { 21, 22 || 23 }, i = 12;");
// T_Source source("int i, k, t; void f() { for(;int k=87;); }"); //void f() { int i, a[5]; if (33); if(45) 57; else {} }
//	T_Source source("static const int A[][3] = {{1,2,3},{4,5,6}};");
//	T_Source source("int A[][3] = {1,2,3,4,5,6};");
//	T_Source source("int A[][3] = {{31,32},{43}};");
// T_Source source("void f() { if (111) -22; else 33; for (111;0;222)333; if (55) 66; }");
// T_Source source("void f(); void f() { for (;;222,333); } void v(int k=23, int m[]) { int i = 12; i+= 27; } void f(); ");
//	T_Source source("int a = 2, b = 3 + 6, c = a + b, A[a][b];");
//	T_Source source("i = (5 ? 6 : 7); ");//i = a[1][2] + f(6,7,8);");
// T_Source source("int i = (-double(5)+6.6)*(float)(8- -7); void f() { i++; }");
// T_Source source("int i = -7, d[3][4]; void f(int j) { i++; j--; d[3][2] = 32; }");
//	T_Source source("a[1]+b[22][33]+i-f()*ff(44)");
//	T_Source source("int i; double j; long k; i = (5); j = i + 5"); 
//	T_Source source("int static i[3] = {3,4,5} ,j=6,k[][4]={1,2,3,{4,5}{6,7,8}}; double d;"); // k = 5; d = j + k;");
//	T_Source source("int a[][2] = {{1,2},{3,(const int)4.5}}; double aa[2][1] = {23}; {} {int j; j++;}");
//	T_Source source("int A[3],AA[2][1]; void f() { int i = A[2] + AA[1][1]; }");
//	T_Source source("void f(int i, const double &d = 12.3) { {} i = 2; { d=2;i+=3;};} ");
//	T_Source source("- + --i++ + 5");//i = a[1][2] + f(6,7,8);");
//	T_Source source("void f(int i =23, int a[][2], int& b[][2] = a) { int a[][2]={{1,2},{3,4}}, &i = a[1,7][1]; }");
// T_Source source("int b[1][2]; void f(int a[][2] = b);");
// T_Source source("a[f(),-3];g(-1,+2);b[1][33],+2,(int)3,int(4),5;return;return 6;for(;;);while(7);do{}while(8);break;continue;goto l;"); //5+6*7;{;(8);}{};"); // id*id()+id[10]");
// T_Source source("if(1)i;else k; if(4)l; if(21) if(22) m; else n;");
// T_Source source("int a[][2][3], i[33] = {}, b[] = {1,2,3}, c[3][4] = {{1,2,3},2,{1,2}},i");
// T_Source source("int b[][2] = {{5,8},{1,3}};");
// T_Source source("void f(){ break; continue; goto l; return; return 99; if(77); if(55)66;else; }");
// T_Source source("int k(int i, int a[]=b); int a=8,j; void f(); int g(){do 23; while(32); while(45)54;}");
// T_Source source("3;continue; {4;break; goto l1; }{ return; } return 66;");//&&8,4,5,(55-3||3),-(int)(7*97,1.2);");
// T_Source source("int b[33], i = b[5]; int a[3][2]; void f(int i); void F(int i, int b[33]) { f(22); i = b[5]; }");
// T_Source source("void f(int i, double a[] = b, int c[][1], int d[1][2]); void F(int j = 12) { do; while(3); 5 + 6, 7 - 8; int i; i = 13; }"); // a[13] + A[14][15], i += +5 - f() + + F(1,2), 7+8*9/(3-4)");
// T_Source source("int  i=10, j, arr[3];void ffff() { i = 5; j-=i++; arr[0]=2; arr[1]=arr[0]++; arr[2]=arr[0]+arr[1];}");
// T_Source source("4+5+6*7*8");
   T_Source source("int a, b[] = {1,2,3}, B[a = 3] = {3,2,1}; static void f_s(int p = 33, int a[] = b) { static const int i = 12, k; int &j = i, &m; }");

// T_Source source(")i(+*()j+*)kl)(");

#else
	T_SourceFile source;
	if (!source.Open("text.cpp")) return false;
   source_file = true;
#endif
	
	print_source(source);
	source.Reset();

	TScanArray my_scan(&source);
//	T_Scan my_scan(&source);

#ifdef RULES
   TRuleNames names;
   TGrammar   table;
	GSyntax   parse(&my_scan,&table);
//	P_Syntax  parse(&my_scan,&table);
//	RSyntax   parse(&my_scan,&table);
   parse.syntax_mode = parse.smParseLR0;
   table.option = TGrammar::POption::opAssociation;
   int ret = false;
   build_formulas(table, names);
   if (stock_grammar != T_Stock::msNone) {
      ret = build_grammar(table, stock_grammar | ((stock_media != T_Stock::msNone) ? stock_media : T_Stock::msMFormula), 0x02);
   }
   if (!ret) { return false; }

	TSemantic semantic(&parse);
   TData     data(&table, &parse, &semantic); parse.data = &data;
             data.LLTable = &table.Mtable; data.LRTable = &table.LRtable; data.formulas = &table.formulas;
             parse.syntax_lexeme = T_SyntaxLexeme(table.type | T_SyntaxLexeme::slPriorAssign | T_SyntaxLexeme::mtTurn);
   parse.set_semantic(&semantic);
   parse.set_make_mode(parse.mmTree);
#endif
   parse.option = 0;
	parse.option |= 0x0008; // lexeme
//   parse.option |= 0x0010; // print_tree
   parse.option |= 0x0020; // erase_code
//   parse.option |= 0x40; // print_code
   parse.option |= 0x0100; // print_rule
   parse.option |= 0x0200; // print_maker
   parse.option |= 0x0400; // print_stack
   parse.option |= 0x1000; // print_SNode
   parse.option = 0x0820;
	parse.line_is_space = true;
	
	source.Reset();
//	scan_source(scan);
/* */
	parse.Reset();
#if defined(TSYNTAX) || defined(CSYNTAX) || defined(MSYNTAX) || defined(RULES)
   T_Lexeme::print_scan = &my_scan;
   TBaseType base_type;
   TPrinter printer;
   bool gut = semantic.Translate();
   if (gut) {
//   	parse.FuncTable.print();
      if (parse.option & T_OptionMode::omPrintSemantic) semantic.print_tree("Semantic ");
      if ((parse.option & T_OptionMode::omPrintSNode) && parse.tree) { // print_SNode
         parse.tree->print(0x00, printer);
      }
   	semantic.semantic->print(printer);
   	semantic.semantic->print(printer);
      printer.print_mode = T_OptionMode::omPrintCodes;
   	semantic.CodeTable.print(printer);
   	semantic.syntax->ErrorTable.print();
      semantic.UserLabelTable.print(printer);
      semantic.UserGoToTable.print(printer);
//    semantic.GarbageTable.print(printer);
      }
//   parse.clear(parse.Program());
#else
   bool gut = parse.Translate();
   if (gut) {
      semantic.print();
      }
#endif
   if (parse.option & T_OptionMode::omPrintLexeme) { // Lexeme
      while (parse.CountLexemes()) {
         T_Lexeme lexeme = parse.PopLexeme();
   		lexeme.print(&parse.Scan());
      }
   }
   if (parse.option & T_OptionMode::omPrintSNode) { // print_SNode
      while (parse.CountSNodes()) {
         SNode* node = parse.SPop();
         node->print(0x00, printer);
      }
   }
   parse.print_store(printer);
   if (gut) {
      printf("\ntrue\n");
   } else {
		printf("\nfalse\n");
   }
   parse.forward.print(&my_scan);
   if (source_file) fclose(source.file);

	return true;
}

void test_formulas(int mode)
{
#ifdef RULES
   TGrammar table;
   TRuleNames names;
   int ret = false;
   build_formulas(table, names);
   if (stock_grammar != T_Stock::msNone) {
      ret = grammar_build(table, stock_grammar | ((stock_media != T_Stock::msNone) ? stock_media : T_Stock::msMFormula), !mode ? 0x02 : 0x00);
   }
   if (ret) {
      switch (mode) {
      case 0x00: {
         TPrinter printer_lex;
         table.lexemes.print(printer_lex);
         table.Used();
         break;
      }
      case 0x01: {
         table.Used();
         int filter = 0;
         table.filter_makers(filter);
         table.make_FIRST_ks(2);
         break;
      }
      default:
         break;
      }
   }
//   table.MACRO("rule_def.txt",T_PrintMode::pmMacroMode);
//   table.print(NULL,0x01);
#endif
   return;
}

bool gif_to_sql_bnf(TInHelp& in_help);
void make_sql_bnf(TInHelp& in_help);

extern bool grammar_reception(TInHelp& in_help, TGrammar& table, const T_WordTable* word_table = &T_KeyWordTable::key_word_table);

void test_grammar(int k, const char* file_table)
{
   TGrammar        table; table.option = 0;
   table.makers = &GMakerTable::maker_table;
   TGrammarBuilder my_builder(&table);
   table.builder = &my_builder;

   if (!table.read(file_table, 0x00)) return;
   TPrinter printer;
   table.print(printer);
   table.root = table.formulas.front();
   table.make_lexemes();

   //   int filter = 0;
   //   table.filter_makers(filter);

   table.change_group();
   table.Used();

   //   table.make_FIRSTs();
   //   table.FIRSTs.print("FIRSTs", "", 0x0702);
   //   table.make_FOLLOWs();
   //   table.FOLLOWs.print("FOLLOWs", "", 0x0702);
   table.make_FIRST_ks(k);
   //   table.FIRSTs.print("FIRST_ks", "", 0x0702);
   //   table.make_EFF_ks(k);
   //   table.make_FOLLOW_ks(k);
   //   table.FOLLOWs.print("FOLLOW_ks", "", 0x0702);
   /*
      my_builder.make_LRkTable(k);
      //   my_builder.make_LR1Table();
      if (my_builder.LRtable.duplicate) printf("\nDuplicate: %d\n", my_builder.LRtable.duplicate);
      if (my_builder.Mtable.warning) printf("\nWarning: %d\n", my_builder.Mtable.warning);

      int option_state = 0x0C00; // compact, !sort
      my_builder.Stable.print("ETF_LR_Stable.txt", option_state);
      my_builder.GOTOtable.print("ETF_LR_GOTO.txt", 0x0201);
      my_builder.LRtable.print("ETF_LR_Action.txt", 0x0201);

      table.write_LR("ETF_LR.tab", 0x01);
   */
//   my_builder.make_LLkTable(k);
   TPrinter printer_table("NL_Cell.txt", 0x0201);
   my_builder.Mtable.print(printer_table);
   TPrinter writer_LL("NL.tab", T_PrintMode::pmWriteSimple);
   table.write_LL(writer_LL);
   return;
}
void token_C99();

enum T_Run {
   trNone,
   trMake_Y,
   trTableBuilder,
   trLeftRecursion,
   trTest = 0x1000,
   trToken_C99,
   trSQL_BNF,
   trFormulas,
   trGrammar,
   trGifToBnf,
   trGroupMaker
};

void table_builder(TInHelp& in_help, T_Run run)
{
   int type = in_help.type; int& option = in_help.option; const char *file = in_help.file; const char *table_file = in_help.table;
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

   if (run == T_Run::trLeftRecursion) {
      table.filter_makers(make_mode, 0x00);
      table.delete_LeftRecursion();
   }
   if (run == T_Run::trTableBuilder) {
      table.Make(type, file);
   }
   table.Print(type, file);

}

void make_y(const TInHelp& in_help)
{
}

void group_maker(TInHelp& in_help)
{
   /*
   TableBuilder 0x020A48 0x00002141 ..\Table\IGrammarBIF.tab ..\Grammar\IGrammar.bif
   */
   if (in_help.count < 2) {
      in_help.table = "..\\Grammar\\IGrammar.bif";
      in_help.file = "..\\Table\\IGrammarBIF.tab";
      in_help.type = 0x0200F0;
      in_help.option = 0x00002141;
   }
   
   TPrinter printer;
   int look_ahead = (in_help.type & 0x000F0000) >> 16;
   if (look_ahead > 1) {
   	in_help.option |= TGrammar::POption::opNoPriorAssign;
   }
   
   TGrammar table;
   TNameTable names; table.names = &names;
   if (!grammar_reception(in_help, table)) return;
   T_Lexeme::word_table = &T_KeyWordTable::key_word_table;
   T_Lexeme::print_scan = NULL;

   table.print(printer);
   {
      char *file_formula = get_file_name(in_help.file, "formula");
      TPrinter printer(file_formula, T_PrintMode::pmProduceHead | T_PrintMode::pmPrintItem);
      table.print(printer);
      free(file_formula);
   }

   A_Syntax::M_Mode make_mode = A_Syntax::M_Mode((in_help.type & 0x0F0) >> 4);
   table.filter_makers(make_mode, 0x00);
   table.print(printer);
   {
      char *file_formula = get_file_name(in_help.file, "formula.filter");
      TPrinter printer(file_formula, T_PrintMode::pmProduceHead | T_PrintMode::pmPrintItem);
      table.print(printer);
      free(file_formula);
   }

   table.make_makers_head(false);
   table.print(printer);
   {
      char *file_formula = get_file_name(in_help.file, "formula.head");
      TPrinter printer(file_formula, T_PrintMode::pmProduceHead | T_PrintMode::pmPrintItem);
      table.print(printer);
      free(file_formula);
   }

   table.make_head_makers(true);
   table.print(printer);
   table.Used();
   table.print(printer);
   {
      char *file_formula = get_file_name(in_help.file, "formula.maker");
      TPrinter printer(file_formula, T_PrintMode::pmProduceHead | T_PrintMode::pmPrintItem);
      table.print(printer);
      free(file_formula);
   }

   table.make_makers_head(true);
   table.print(printer);
   {
      char *file_formula = get_file_name(in_help.file, "formula.group");
      TPrinter printer(file_formula, T_PrintMode::pmProduceHead | T_PrintMode::pmPrintItem);
      table.print(printer);
      free(file_formula);
   }

   table.make_head_makers(true);
   table.print(printer);
   table.Used();
   table.ClearVectors();
   table.print(printer);
   {
      char *file_formula = get_file_name(in_help.file, "formula.reveal");
      TPrinter printer(file_formula, T_PrintMode::pmProduceHead | T_PrintMode::pmPrintItem);
      table.print(printer);
      free(file_formula);
   }

}

int run(TInHelp& in_help)
{
   int ret = 0;
   switch (in_help.mode)
   {
   case T_Run::trNone:
      break;
   case T_Run::trMake_Y:
      make_y(in_help);
      break;
   case T_Run::trTableBuilder:
   case T_Run::trLeftRecursion:
      table_builder(in_help, (T_Run)in_help.mode);
      break;
   case T_Run::trTest:
      test();
      break;
   case T_Run::trToken_C99:
      token_C99();
      break;
   case T_Run::trSQL_BNF:
      make_sql_bnf(in_help);
      break;
   case T_Run::trFormulas:
      in_help.type = 0x00;
      test_formulas(in_help.type);
      break;
   case T_Run::trGrammar:
      test_grammar(in_help.type, in_help.file);
      break;
   case T_Run::trGifToBnf:
      ret = gif_to_sql_bnf(in_help);
      break;
   case T_Run::trGroupMaker:
      group_maker(in_help);
      break;
   default:
      break;
   }
   printf("\n");
   return ret;
}

int main(int argc, const char* argv[])
{
   TInHelp in_help(TInHelp::Translate);
//   test_grammar(2);
   in_help.mode = T_Run::trSQL_BNF;
   in_help.mode = T_Run::trGifToBnf;

//   ..\Release\Translator.exe 0x1005 0x00000000 0x00000000 ..\SQL\SQL_.txt ..\SQL\bif_to_bnf.tab
   in_help.file = "..\\SQL\\SQL_.txt";
   in_help.table = "..\\SQL\\bif_to_bnf.tab";

   in_help.mode = T_Run::trGroupMaker;
   in_help.mode = T_Run::trFormulas;

   if (!in_help.input(argc,argv)) return 0;
   int ret = run(in_help);

   return ret;
}

#define TOKEN_WORD(C,T)      { int t = T_Lexeme::T_Group::grReserv << 8 | T_Lexeme::W_Type::rw##T;    printf("\n%%token %-20s %5d // %04X",#C,t,t); }
#define TOKEN_OPER(C,T)      { int t = T_Lexeme::T_Group::grOper << 8 | A_Symbol::T_Type::lx##T;      printf("\n%%token %-20s %5d // %04X",#C,t,t); }
#define TOKEN_SEPORATOR(C,T) { int t = T_Lexeme::T_Group::grSeparator << 8 | A_Symbol::T_Type::lx##T; printf("\n%%token %-20s %5d // %04X",#C,t,t); }
#define TOKEN_LEXEME(C,G,T)  { int t = T_Lexeme::T_Group::gr##G << 8 | T;                             printf("\n%%token %-20s %5d // %04X",#C,t,t); }

void token_C99()
{

TOKEN_LEXEME(IDENTIFIER    ,Ident        ,0        )
TOKEN_LEXEME(CONSTANT      ,Integer      ,0        )
TOKEN_LEXEME(STRING_LITERAL,String       ,0        )

TOKEN_OPER(INC_OP        ,PlusPlus    ) 
TOKEN_OPER(DEC_OP        ,MinusMinus  ) 
TOKEN_OPER(LEFT_OP       ,LShift      ) 
TOKEN_OPER(RIGHT_OP      ,RShift      ) 
TOKEN_OPER(LE_OP         ,LE          ) 
TOKEN_OPER(GE_OP         ,GE          ) 
TOKEN_OPER(EQ_OP         ,Equ         ) 
TOKEN_OPER(NE_OP         ,NotEqu      ) 
TOKEN_OPER(AND_OP        ,AndAnd      ) 
TOKEN_OPER(OR_OP         ,OrOr        ) 
TOKEN_OPER(MUL_ASSIGN    ,MultiAssign ) 
TOKEN_OPER(DIV_ASSIGN    ,DivAssign   ) 
TOKEN_OPER(MOD_ASSIGN    ,ModAssign   ) 
TOKEN_OPER(ADD_ASSIGN    ,AddAssign   ) 
TOKEN_OPER(SUB_ASSIGN    ,SubAssign   ) 
TOKEN_OPER(LEFT_ASSIGN   ,LShiftAssign) 
TOKEN_OPER(RIGHT_ASSIGN  ,RShiftAssign) 
TOKEN_OPER(AND_ASSIGN    ,AndAssign   ) 
TOKEN_OPER(XOR_ASSIGN    ,XOrAssign   ) 
TOKEN_OPER(OR_ASSIGN     ,OrAssign    ) 

TOKEN_SEPORATOR(ELLIPSIS ,Ellipsis    )
TOKEN_SEPORATOR(PTR_OP   ,Pointer     )
                                      
TOKEN_WORD(TYPEDEF       ,Typedef     )
TOKEN_WORD(EXTERN        ,Extern      )
TOKEN_WORD(STATIC        ,Static      )
TOKEN_WORD(AUTO          ,Auto        )
TOKEN_WORD(REGISTER      ,Register    )
TOKEN_WORD(CHAR          ,Char        )
TOKEN_WORD(SHORT         ,Short       )
TOKEN_WORD(INT           ,Int         )
TOKEN_WORD(LONG          ,Long        )
TOKEN_WORD(SIGNED        ,Signed      )
TOKEN_WORD(UNSIGNED      ,Unsigned    )
TOKEN_WORD(FLOAT         ,Float       )
TOKEN_WORD(DOUBLE        ,Double      )
TOKEN_WORD(CONST         ,Const       )
TOKEN_WORD(VOLATILE      ,Volatile    )
TOKEN_WORD(VOID          ,Void        )
TOKEN_WORD(STRUCT        ,Struct      )
TOKEN_WORD(UNION         ,Union       )
TOKEN_WORD(ENUM          ,Enum        )
TOKEN_WORD(SIZEOF        ,Sizeof      )
TOKEN_WORD(CASE          ,Case        )
TOKEN_WORD(DEFAULT       ,Default     )
TOKEN_WORD(IF            ,If          )
TOKEN_WORD(ELSE          ,Else        )
TOKEN_WORD(SWITCH        ,Switch      )
TOKEN_WORD(WHILE         ,While       )
TOKEN_WORD(DO            ,Do          )
TOKEN_WORD(FOR           ,For         )
TOKEN_WORD(GOTO          ,GoTo        )
TOKEN_WORD(CONTINUE      ,Continue    )
TOKEN_WORD(BREAK         ,Break       )
TOKEN_WORD(RETURN        ,Return      )
                                      
TOKEN_WORD(TYPE_NAME     ,Define      )

}


void test_cpp()
{
/*
   int i = 0; do ; while(i);
   int i; i = (int const) 12.3 + (int const(32.4) + 13);
   int aa[3] = {}; int i = aa[3,2,1];
   int i = 0; ++ -- ++ i; 
   i ++;

   int i = 5 + (1,fv(),3); i = int (4.4) + (const int (3.3));
   return 1 == 0;
   int i = 0;
   {
   int i = i + 5;
   }

   int i = 0; i = (int)i+=12; i = int(i=12); i = (int)f()+i+13;

   int i = 12;

   if (int jj = 12) int i = 13 + jj; else int i = 14 - jj;

   switch (i = 14, 12, i) {
      case 1: int m = i;
   }

   switch (int j = 15) {
      case 1: int m = j;
   }

   while (int j = 14) {
      int m = j;
   }
   int a[2] = { 1, 2 };
   for (int i=0, j = 12; int k = a[1]; j = 0, k = i++) {}
   int b[2] = {};
   while (1,2,3);
*/
}

/*
int const &ff();;;;
int aa = 5 + aa;
void ff(int e[] = a) {};
int f() { int i = 0; int j = -- ++ -- i; double d = 0.0, n = !d; int k = !d; return 10;}
void w(int i) {}
void v(const short &s) { w(s); int ii = (const int)s + int(s); } 

int a[3] = { 1, a[2] }, b[2][2] = {{1,2},{}};
static const int A[][3] = {{1,2,3},{4,5,6}};
int b2[3][2] = { {1,2}, {3,4}, {5} };

void g() { int i = 0; goto l1; { l0:i++; l4: int y = 0; y++; goto l4; } for (int i = 0;;) { int j = 0; l1:i=0, 12; goto l0;} }

int j = 12;
void f(const int &i = j) { int k = i; j++; int m = i; }

int i = (1,2,3);

*/

