#include "stdafx.h"

#include "TSemantic.h"
#include "RSyntax.h"
#include "SNodes.h"
#include "Maker.h"

#undef ACTION
#define ACTION(MODE) ((semantic->syntax->option_mode & 0x0000000F) == A_Syntax::mm##MODE)

#undef SEMANTIC_MODE
#define SEMANTIC_MODE(P1,P2) SemanticMode(A_Syntax::mm##P1, A_Syntax::mm##P2)

// --------------------------- TSemantic---------------------------

TOperTable& OperTable() 
{ 
   static TOperTable *table = NULL; if (!table) table = new TOperTable(); return *table; 
}

TSemantic::TSemantic(A_Syntax *s) : syntax(s), ExecStack(), function(NULL), semantic(NULL), type_node(NULL),
   FuncTable(this), CodeTable(this),
   UserLabelTable(this), UserGoToTable(this), level(0), print_mode(0), block_number(0),
   AddInt(0), MultiInt(0), code_count(0), quad_count(0), mode(T_Mode::tmNone)
{
   OperTable();
   MakeOperTable();
}

TSemantic::~TSemantic()
{
   if (semantic) delete semantic;
}

TNodeDefVar* TSemantic::FindIdent(const T_Lexeme &l) const
{
   return semantic->FindIdent(l);
}

int TSemantic::AddDefFunc(TNodeDefFunc* func)
{
   TFinder finder(TFinder::mfNone);
   const TFuncProfile *profile = func->profile;
   int already_index = 0;
   bool body = func->Body() != NULL, already_body = false, already_func = false;
   TNodeDefFunc* already;
   while (already = FuncTable.find(*profile, finder)) {
      already_func = true; already_index = finder.index;
      if (already->Body()) { already_body = true; break; }
      finder.index++;
   }
   if (body && already_body) {
      AddError(func,erDuplicateBody);
      FuncTable.Add(func);
   } else if (body && already_index) {
      FuncTable[already_index].func = func;
   } else if (!already_index) {
      FuncTable.Add(func);
   }
   return 0;
}

bool TSemantic::VerifyFunc()
{
   bool ret = true;
   for (int i = 0; i < (int)FuncTable.size(); i++) {
      TNodeDefFunc* func = FuncTable[i].func;
      if (!func->Body()) {
         TFinder finder(TFinder::mfNone);
         bool already_body = false;
         TNodeDefFunc* already;
         while (already = FuncTable.find(*func->profile, finder)) {
            if (already->Body()) { already_body = true; break; }
            finder.index++;
         }
         if (!already_body) {
            AddError(func,erUnknownBody);
            ret = false;
         }
      }
   }
   return ret;
}

bool TSemantic::SemanticMode(A_Syntax::M_Mode area, A_Syntax::M_Mode mode) const
{
   return syntax->SemanticMode(area, mode);
}

const char* main_title[16] = { "None", "Tree", "Code", "Node", "Turn", "Made", "Call", "", "", "", "", "", "C_Syntax", "C99_Syntax","","" };
const char* lexer_title[16] = { "Mine", "FLex" };
const char* semantic_title[16] = { "None", "BlockTable", "TreeSearch", "TreeStack", "RuleStack" };
const char* generate_title[16] = { "None", "Code", "Quad" };
const char* grammar_title[16] = { "LL", "NL", "LR", "NR", // grammars
                                  "ETF_LL", "ETF_LLMake", "ETF_LR", "ETF_LRMake", "EXPR_LR", // examples
                                  "Table", "BIF", "BNF", "YACC", "Y", "Parser", // parsers
                                  "File" // reader
                                };
const char* phase_title[16] = { "None", "One", "Two", "Three" };
void TSemantic::print_semantic_mode()
{
   int om = syntax->option_mode;
   printf("option_mode: "
      "Phase=%s, "
      "Grammar=%s, "
      "Generate=%s, " 
      "Semantic=%s, "
      "Lexer=%s, "
      "Method=%1X, "
      "Main=%s"
      "\n",
      phase_title[(om >> (A_Syntax::mmPhase * 4)) & 0x0f],
      grammar_title[(om >> (A_Syntax::mmGrammar * 4)) & 0x0f],
      generate_title[(om >> (A_Syntax::mmGenerate * 4)) & 0x0f],
      semantic_title[(om >> (A_Syntax::mmSemantic * 4)) & 0x0f],
      lexer_title[(om >> (A_Syntax::mmLexer * 4)) & 0x0f],
      (om >> (A_Syntax::mmMethod * 4)) & 0x0f,
      main_title[(om >> (A_Syntax::mmMain * 4)) & 0x0f]
   );
}

bool TSemantic::Search(TFinder& finder)
{
   finder.semantic = this;
   return semantic->Search(finder);
}

TCodeTable& TSemantic::Code()
{
   if (function == NULL) return CodeTable; else return *FuncTable[function->number].code;
}

void TSemantic::AddCode(TNode* code, int counter)
{
   Code().Add(code,counter); code_count++;
   if (!(syntax->option & T_OptionMode::omPrintCode) || !code) return;
   if (dynamic_cast<TNodeCommand*>(code) || dynamic_cast<TNodeLabel*>(code) || dynamic_cast<TNodeGoTo*>(code)) { 
      code->print(0, printer); 
   } else {
      code->TNode::print(0, printer); 
   }
   int ip;
   if (counter < 0) ip = (int)Code().size() - 1; else ip = counter;
   printf(" -->> %05d\n", ip);
}

void TSemantic::WriteCode(TPrinter& printer)
{
   PRINTER_FILE_MODE
   for (TFuncTableItem& item : FuncTable) {
      item.func->TNode::print(-1, printer); printer.eol();
      item.code->write(printer);
      printer.eol();
   }
   CodeTable.write(printer);
   WriteConst(printer);
}

void TSemantic::AddError(TNode* node, T_Error error)
{
   syntax->ErrorTable.Add(error,node->FirstLexeme());
   if ((node->error_code == T_Error::erNone) && !SEMANTIC_MODE(Phase, TwoPhase)) {
      node->SetError(error);
   }
}

void TSemantic::impossible(TNode* node, int mode)
{
   if (ExecStack.CheckExec()) {
      if (node) {
         AddError(node, T_Error::erImpossible);
         if (node->Lexeme().pos == 0) {
            int i = 12;
         }
      } else {
         syntax->ErrorTable.Add(T_Error::erImpossible, (mode & 0x01) ? syntax->lex : syntax->forward);
      }
   }
}

#define TCI TCastItem

const TCastItem CastableTable[24][24] = {
//                 Void         Short          Int          Long           Float        Double        CVoid         CShort         CInt          CLong        CFloat       CDouble         RVoid        RShort         RInt          RLong        RFloat       RDouble       CRVoid         CRShort        CRInt        CRLong        CRFloat      CRDouble 
/*Void    */{TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*Void    */
/*Short   */{TCI( -1,_______),TCI(  0,_______),TCI(  1,S___I__),TCI(  2,S___L__),TCI(  3,S___F__),TCI(  4,S___D__),TCI( -1,_______),TCI(  0,S___SC_),TCI(  1,S___IC_),TCI(  2,S___LC_),TCI(  3,S___FC_),TCI(  4,S___DC_),TCI( -1,_______),TCI(  0,S___SR_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,S___SCR),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*Short   */
/*Int     */{TCI( -1,_______),TCI( 10,I___S__),TCI(  0,_______),TCI(  1,I___L__),TCI(  2,I___F__),TCI(  3,I___D__),TCI( -1,_______),TCI( 10,I___SC_),TCI(  0,I___IC_),TCI(  1,I___LC_),TCI(  2,I___FC_),TCI(  3,I___DC_),TCI( -1,_______),TCI( -1,_______),TCI(  0,I___IR_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,I___ICR),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*Int     */
/*Long    */{TCI( -1,_______),TCI( 20,L___S__),TCI( 10,L___I__),TCI(  0,_______),TCI(  1,L___F__),TCI(  2,L___D__),TCI( -1,_______),TCI( 20,L___SC_),TCI( 10,L___IC_),TCI(  0,L___LC_),TCI(  1,L___FC_),TCI(  2,L___DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,L___LR_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,L___LCR),TCI( -1,_______),TCI( -1,_______)},/*Long    */
/*Float   */{TCI( -1,_______),TCI(100,F___S__),TCI(100,F___I__),TCI(100,F___L__),TCI(  0,_______),TCI(  1,F___D__),TCI( -1,_______),TCI(100,F___SC_),TCI(100,F___IC_),TCI(100,F___LC_),TCI(  0,F___FC_),TCI(  1,F___DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,F___FR_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,F___FCR),TCI( -1,_______)},/*Float   */
/*Double  */{TCI( -1,_______),TCI(200,D___S__),TCI(200,D___I__),TCI(200,D___L__),TCI( 10,D___F__),TCI(  0,_______),TCI( -1,_______),TCI(200,D___SC_),TCI(200,D___IC_),TCI(200,D___LC_),TCI( 10,D___FC_),TCI(  0,D___DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,D___DR_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,D___DCR)},/*Double  */
/*CVoid   */{TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*CVoid   */
/*CShort  */{TCI( -1,_______),TCI(  0,SC__S__),TCI(  1,SC__I__),TCI(  2,SC__L__),TCI(  3,SC__F__),TCI(  4,SC__D__),TCI( -1,_______),TCI(  0,_______),TCI(  1,SC__IC_),TCI(  2,SC__LC_),TCI(  3,SC__FC_),TCI(  4,SC__DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*CShort  */
/*CInt    */{TCI( -1,_______),TCI( 10,IC__S__),TCI(  0,IC__I__),TCI(  1,IC__L__),TCI(  2,IC__F__),TCI(  3,IC__D__),TCI( -1,_______),TCI( 10,IC__SC_),TCI(  0,_______),TCI(  1,IC__LC_),TCI(  2,IC__FC_),TCI(  3,IC__DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*CInt    */
/*CLong   */{TCI( -1,_______),TCI( 20,LC__S__),TCI( 10,LC__I__),TCI(  0,LC__L__),TCI(  1,LC__F__),TCI(  2,LC__D__),TCI( -1,_______),TCI( 20,LC__SC_),TCI( 10,LC__IC_),TCI(  0,_______),TCI(  1,LC__FC_),TCI(  2,LC__DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*CLong   */
/*CFloat  */{TCI( -1,_______),TCI(100,FC__S__),TCI(100,FC__I__),TCI(100,FC__L__),TCI(  0,FC__F__),TCI(  1,FC__D__),TCI( -1,_______),TCI(100,FC__SC_),TCI(100,FC__IC_),TCI(100,FC__LC_),TCI(  0,_______),TCI(  1,FC__DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*CFloat  */
/*CDouble */{TCI( -1,_______),TCI(200,DC__S__),TCI(200,DC__I__),TCI(200,DC__L__),TCI( 10,DC__F__),TCI(  0,DC__D__),TCI( -1,_______),TCI(200,DC__SC_),TCI(200,DC__IC_),TCI(200,DC__LC_),TCI( 10,DC__FC_),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*CDouble */
/*RVoid   */{TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*RVoid   */
/*RShort  */{TCI( -1,_______),TCI(  0,SR__S__),TCI(  1,SR__I__),TCI(  2,SR__L__),TCI(  3,SR__F__),TCI(  4,SR__D__),TCI( -1,_______),TCI(  0,SR__SC_),TCI(  1,SR__IC_),TCI(  2,SR__LC_),TCI(  3,SR__FC_),TCI(  4,SR__DC_),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*RShort  */
/*RInt    */{TCI( -1,_______),TCI( 10,IR__S__),TCI(  0,IR__I__),TCI(  1,IR__L__),TCI(  2,IR__F__),TCI(  3,IR__D__),TCI( -1,_______),TCI( 10,IR__SC_),TCI(  0,IR__IC_),TCI(  1,IR__LC_),TCI(  2,IR__FC_),TCI(  3,IR__DC_),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*RInt    */
/*RLong   */{TCI( -1,_______),TCI( 20,LR__S__),TCI( 10,LR__I__),TCI(  0,LR__L__),TCI(  1,LR__F__),TCI(  2,LR__D__),TCI( -1,_______),TCI( 20,LR__SC_),TCI( 10,LR__IC_),TCI(  0,LR__LC_),TCI(  1,LR__FC_),TCI(  2,LR__DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______)},/*RLong   */
/*RFloat  */{TCI( -1,_______),TCI(100,FR__S__),TCI(100,FR__I__),TCI(100,FR__L__),TCI(  0,FR__F__),TCI(  1,FR__D__),TCI( -1,_______),TCI(100,FR__SC_),TCI(100,FR__IC_),TCI(100,FR__LC_),TCI(  0,FR__FC_),TCI(  1,FR__DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______)},/*RFloat  */
/*RDouble */{TCI( -1,_______),TCI(200,DR__S__),TCI(200,DR__I__),TCI(200,DR__L__),TCI( 10,DR__F__),TCI(  0,DR__D__),TCI( -1,_______),TCI(200,DR__SC_),TCI(200,DR__IC_),TCI(200,DR__LC_),TCI( 10,DR__FC_),TCI(  0,DR__DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______)},/*RDouble */
/*CRVoid  */{TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*CRVoid  */
/*CRShort */{TCI( -1,_______),TCI(  0,SCR_S__),TCI(  1,SCR_I__),TCI(  2,SCR_L__),TCI(  3,SCR_F__),TCI(  4,SCR_D__),TCI( -1,_______),TCI(  0,SCR_SC_),TCI(  1,SCR_IC_),TCI(  2,SCR_LC_),TCI(  3,SCR_FC_),TCI(  4,SCR_DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*CRShort */
/*CRInt   */{TCI( -1,_______),TCI( 10,ICR_S__),TCI(  0,ICR_I__),TCI(  1,ICR_L__),TCI(  2,ICR_F__),TCI(  3,ICR_D__),TCI( -1,_______),TCI( 10,ICR_SC_),TCI(  0,ICR_IC_),TCI(  1,ICR_LC_),TCI(  2,ICR_FC_),TCI(  3,ICR_DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______)},/*CRInt   */
/*CRLong  */{TCI( -1,_______),TCI( 20,LCR_S__),TCI( 10,LCR_I__),TCI(  0,LCR_L__),TCI(  1,LCR_F__),TCI(  2,LCR_D__),TCI( -1,_______),TCI( 20,LCR_SC_),TCI( 10,LCR_IC_),TCI(  0,LCR_LC_),TCI(  1,LCR_FC_),TCI(  2,LCR_DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______),TCI( -1,_______)},/*CRLong  */
/*CRFloat */{TCI( -1,_______),TCI(100,FCR_S__),TCI(100,FCR_I__),TCI(100,FCR_L__),TCI(  0,FCR_F__),TCI(  1,FCR_D__),TCI( -1,_______),TCI(100,FCR_SC_),TCI(100,FCR_IC_),TCI(100,FCR_LC_),TCI(  0,FCR_FC_),TCI(  1,FCR_DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______),TCI( -1,_______)},/*CRFloat */
/*CRDouble*/{TCI( -1,_______),TCI(200,DCR_S__),TCI(200,DCR_I__),TCI(200,DCR_L__),TCI( 10,DCR_F__),TCI(  0,DCR_D__),TCI( -1,_______),TCI(200,DCR_SC_),TCI(200,DCR_IC_),TCI(200,DCR_LC_),TCI( 10,DCR_FC_),TCI(  0,DCR_DC_),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI( -1,_______),TCI(  0,_______)},/*CRDouble*/
};

const TCastItem& Castable(T_BaseType from, T_BaseType to) 
{
   if ((from == btUnknown) || (to == btUnknown))  return CastableTable[0][1];
   from = TBaseType::Tilda(from,btStatic); to = TBaseType::Tilda(to,btStatic);
   return CastableTable[TBaseType::Index(from)][TBaseType::Index(to)];
}

T_BaseType CastableBetween(T_BaseType one, T_BaseType two)
{
   T_BaseType ret = btUnknown;
   const TCastItem &cast_one_two = Castable(one,two);
   const TCastItem &cast_two_one = Castable(two,one);
	if ((cast_one_two.weight >= 0) && (cast_two_one.weight >= 0)) {
      ret = (cast_one_two.weight >= cast_two_one.weight) ? one : two;
   } else if (cast_one_two.weight >= 0) {
      ret = one;
   } else if (cast_two_one.weight >= 0) {
      ret = two;
   }
   return ret;
}

const TOperProfile* TOperTable::Oper(T_Symbol::T_Type oper, T_BaseType left, T_BaseType right) const
{
   const T_Symbol& symbol = symbol_table().Symbol(oper);
   if (!symbol.oper_count) return NULL;
	T_Profile join; join.Add(left); if (right != btUnknown) join.Add(right);
   int weight_gut = 1000000;
	const TOperProfile *profile_gut = NULL;
   for (int i = 0; i < symbol.oper_count; i++) {
      const TOperProfile& profile = (*this)[symbol.oper_index + i];
		int weight = profile.Match(join);
		if (weight < 0) continue;
		if (weight < weight_gut) {
			weight_gut = weight; profile_gut = &profile;
		}
		if (weight == 0) break;
   }
   return profile_gut;
}

void TOperTable::Clear()
{
   iterator ip = begin();
   while (ip != end()) {
      ip = erase(ip);
   }
   delete this;
}

int  T_Profile::Match(const T_Profile &join) const
{
	int weight = 0;
	if (size() != join.size()) return -1;
   for (int i = 0; i < (int)size(); i++) {
		const TCastItem &cast = Castable(join[i],(*this)[i]);
		if (cast.weight == -1) return -1;
		weight += cast.weight;
	}
	return weight;
}

bool T_Profile::match(const T_Profile &join) const
{
	if (size() != join.size()) return false;
   for (int i = 0; i < (int)size(); i++) {
		if (join[i] != (*this)[i]) return false;
	}
	return true;
}

int  T_Profile::Cast(const T_Profile &join, TCastables &castables) const
{
   castables.clear();
	int weight = 0;
	if (size() != join.size()) return -1;
   for (int i = 0; i < (int)size(); i++) {
		const TCastItem &cast = Castable(join[i],(*this)[i]);
		if (cast.weight == -1) return -1;
      castables.push_back(cast.cast);
		if (cast.cast != T_CastType::None) weight++;
	}
	return weight;
}

T_CastType TSemantic::GetCastable(T_BaseType from, T_BaseType to)
{
   const TCastItem &cast = Castable(from,to);
	if (cast.weight >= 0) {
      return cast.cast;
   }
   return T_CastType::Illegal;
}

bool TSemantic::GenCastable(TNode* &node, T_BaseType type, int mode) // 0x01 - code, 0x02 - const
{
   T_BaseType from_type = node->BaseType();
   if (mode & 0x02) { // initialization
      from_type = TBaseType::Tilda(from_type,T_BaseType::btConst);
   }
   const TCastItem &cast = Castable(from_type,type);
	if (cast.weight >= 0) {
      if (cast.cast != T_CastType::None) {
         TNodeCast* cast_node = new TNodeCast();
         cast_node->cast = cast.cast; cast_node->base_type = type;
         cast_node->SetOwner(node->Owner()); node->SetOwner();
         cast_node->SetRight(node); node = cast_node;
      }
      return true;
   }
   return false;
}

bool TSemantic::GenCastable(T_BaseType from, T_BaseType to, int& made)
{ 
   const TCastItem &cast = Castable(from,to);
	if (cast.weight >= 0) {
      if (cast.cast != T_CastType::None) {
         TNodeCommand* command = new TNodeCommand(T_Command::command_Cast,cast.cast,0,to);
         AddCode(command,made++);
      }
      return true;
   }
   return false;
}

void TSemantic::GenCommand(T_Command command, int param, int mode, T_BaseType type, int made)
{
   if ((command == T_Command::command_Pop) && (param < 0)) {
      int i = 12; i++;
   }
   AddCode(new TNodeCommand(command,param,mode,type), made);
}

void TSemantic::GenNumber(const T_Lexeme &lexeme)
{
   T_BaseType base_type = (lexeme.group == lexeme.grInteger) ? btCInt : ((lexeme.group == lexeme.grNumber) ? btCDouble : btUnknown);
   if (lexeme.group == lexeme.grInteger)
      GenCommand(T_Command::command_PushInt, syntax->Integer(lexeme), base_type);
   else
      GenCommand(T_Command::command_PushNum, lexeme.value/*syntax->Scan().Number(lexeme)*/, base_type);
}

TNode* TSemantic::GetCommand(int counter)
{
   return Code()[counter];
}

bool TSemantic::MakeLogical(TNode* &node, TNodeLabel* &true_label, TNodeLabel* &false_label)
{
   bool ret = true;
	TNodeLogical* logical = node->Logical();
   if (!logical) {
	   if (!GenCastable(node, T_BaseType::btCInt)) {
         AddError(node,erUnknownCast);
         ret = false;
	   }
      true_label = new TNodeLabel(this); false_label = new TNodeLabel(this);
      TNodeGoTo* go_true  = new TNodeGoTo(T_GoTo::tgIf  ,true_label );
      TNodeGoTo* go_false = new TNodeGoTo(T_GoTo::tgGoTo,false_label);
      node->InsertAfter(go_true); node->InsertAfter(go_false);
	} else {
		true_label = logical->true_label; false_label = logical->false_label;
      logical->logical = 1;
   }
   return ret;
}

void TSemantic::MakeValue(TNodeLabel* true_label, TNodeLabel* false_label, int &made)
{
   AddCode(true_label,made); if (made >= 0) made++;
   AddCode(new TNodeCommand(T_Command::command_PushInt,1,0,btCInt),made); if (made >= 0) made++; 
   TNodeLabel* label_end = new TNodeLabel(this);
   TNodeGoTo* go_end = new TNodeGoTo(T_GoTo::tgGoTo,label_end);
   AddCode(go_end,made); if (made >= 0) made++;
   AddCode(false_label,made); if (made >= 0) made++;
   AddCode(new TNodeCommand(T_Command::command_PushInt,0,0,btCInt),made); if (made >= 0) made++; 
   AddCode(label_end,made); if (made >= 0) made++;
}

const TOperProfile* TSemantic::Oper(const T_Lexeme &lexeme, T_BaseType left, T_BaseType right) const
{
   T_Symbol::T_Type oper;
   if (lexeme.group == T_Lexeme::grPriority) {
      const T_Symbol& symbol = symbol_table().Symbol(lexeme.value);
      oper = T_Symbol::T_Type(symbol.type);
   } else {
      oper = T_Symbol::T_Type(lexeme.type);
   }
   return OperTable().Oper(oper, left, right);
}

void TSemantic::MakeBinaryOper(const char* oper, T_BaseType result, T_BaseType left, T_BaseType right)
{
   const T_Symbol* symbol = symbol_table().Symbol(oper);
   if (!symbol) return;
   MakeBinaryOper(symbol->type,result,left,right);
}
void TSemantic::MakeBinaryOper(T_Symbol::T_Type oper, T_BaseType result, T_BaseType left, T_BaseType right)
{
   int index = OperTable().count();
   TOperProfile profile(oper, result, left, right);
   OperTable().push_back(profile);
   symbol_table().Symbol(oper).MakeOper(index);
}
void TSemantic::MakeUnaryOper(T_Symbol::T_Type oper, T_BaseType result, T_BaseType param)
{
   int index = OperTable().count();
   TOperProfile profile(oper, result, param);
   OperTable().push_back(profile);
   symbol_table().Symbol(oper).MakeOper(index);
}

//#define MAKE_BINARY(OPER, RESULT, LEFT, RIGHT) MakeBinaryOper(T_Symbol::lx##OPER, T_BaseType::bt##RESULT, T_BaseType::bt##LEFT, T_BaseType::bt##RIGHT);
#define MAKE_BINARY(OPER, RESULT, LEFT, RIGHT) \
   MakeUnaryOper(T_Symbol::lx##OPER, T_BaseType::bt##RESULT, T_BaseType::bt##LEFT); \
   OperTable().back().Add(T_BaseType::bt##RIGHT);
#define MAKE_UNARY(OPER, RESULT, PARAM) MakeUnaryOper(T_Symbol::lx##OPER, T_BaseType::bt##RESULT, T_BaseType::bt##PARAM);

void TSemantic::MakeOperTable()
{
//   static bool make = false; if (make) return; make = true;
   AddInt = OperTable().count(); 
   MAKE_BINARY(Add          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Add          ,CDouble,CDouble,CDouble)
   MAKE_BINARY(Sub          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Sub          ,CDouble,CDouble,CDouble)
   MultiInt = OperTable().count();
   MAKE_BINARY(Multi        ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Multi        ,CDouble,CDouble,CDouble)
   MAKE_BINARY(Div          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Div          ,CDouble,CDouble,CDouble)
   MAKE_BINARY(Mod          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Or           ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(And          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(OrOr         ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(AndAnd       ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(XOr          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Equ          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Equ          ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(NotEqu       ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(NotEqu       ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(LT           ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(LT           ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(LE           ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(LE           ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(GT           ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(GT           ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(GE           ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(GE           ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(LShift       ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(RShift       ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(LShiftAssign ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(RShiftAssign ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(ModAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(AndAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(OrAssign     ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(XOrAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(Assign       ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(Assign       ,CDouble,RDouble,CDouble)
   MAKE_BINARY(AddAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(AddAssign    ,CDouble,RDouble,CDouble)
   MAKE_BINARY(SubAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(SubAssign    ,CDouble,RDouble,CDouble)
   MAKE_BINARY(MultiAssign  ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(MultiAssign  ,CDouble,RDouble,CDouble)
   MAKE_BINARY(DivAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(DivAssign    ,CDouble,RDouble,CDouble)
   MAKE_UNARY (UnaryAdd     ,CInt   ,CInt   )
   MAKE_UNARY (UnaryAdd     ,CDouble,CDouble)
   MAKE_UNARY (UnarySub     ,CInt   ,CInt   )
   MAKE_UNARY (UnarySub     ,CDouble,CDouble)
   MAKE_UNARY (Not          ,CInt   ,CInt   )
   MAKE_UNARY (Not          ,CInt   ,CDouble)
   MAKE_UNARY (Tilda        ,CInt   ,CInt   )
   MAKE_UNARY (PlusPlus     ,RInt   ,RInt   )
   MAKE_UNARY (PlusPlus     ,RDouble,RDouble)
   MAKE_UNARY (MinusMinus   ,RInt   ,RInt   )
   MAKE_UNARY (MinusMinus   ,RDouble,RDouble)
   MAKE_UNARY (PostInc      ,CInt   ,RInt   )
   MAKE_UNARY (PostInc      ,CDouble,RDouble)
   MAKE_UNARY (PostDec      ,CInt   ,RInt   )
   MAKE_UNARY (PostDec      ,CDouble,RDouble)
}

bool TSemantic::Translate()
{
   A_Syntax::mmMain; 
   A_Syntax::mmLexer; 

   T_Mode mode = T_Mode::tmNone;
   if (SEMANTIC_MODE(Phase, ThreePhase)) {
      if (SEMANTIC_MODE(Semantic, BlockTable)) {
         semantic = new BlockSemantic(this);
         mode = T_Mode::tmBlock;
      } else if (SEMANTIC_MODE(Semantic, TreeSearch)) {
         semantic = new TreeSemantic(this);
         mode = T_Mode::tmTree;
      } else {

      }
   } else if (SEMANTIC_MODE(Phase, TwoPhase)) {
      if (SEMANTIC_MODE(Semantic, BlockTable)) {
         semantic = new BlockSemantic(this);
         mode = T_Mode::tmBlock;
      } else if (SEMANTIC_MODE(Semantic, TreeStack)) {
         if (M_Syntax *m_syntax = dynamic_cast<M_Syntax*> (syntax)) {
            TStackRule* stack = &m_syntax->tree_stack;
            semantic = new StackSemantic(this, stack);
            mode = T_Mode::tmStack;
         }
      } else if (SEMANTIC_MODE(Semantic, RuleStack)) {
         if (S_Syntax *g_syntax = dynamic_cast<S_Syntax*> (syntax)) {
            TStackRule* stack = &g_syntax->rule_stack;
            semantic = new StackSemantic(this, stack);
            mode = T_Mode::tmStack;
         }
      } else if (SEMANTIC_MODE(Semantic, TreeSearch)) {
         semantic = new TreeSemantic(this);
         mode = T_Mode::tmTree;
      } else {

      }
   } else if (SEMANTIC_MODE(Phase, OnePhase)) {
      if (SEMANTIC_MODE(Semantic, BlockTable)) {
         semantic = new BlockSemantic(this);
         mode = T_Mode::tmBlock;
      } else {

      }
   } else {
   }

   if (SEMANTIC_MODE(Generate, QuadGenerate)) mode = (T_Mode)(mode | T_Mode::tmQuad);
   Mode(mode);

   print_semantic_mode();
   if (!syntax->Translate()) {
      return false;
   }
   TNode* program = syntax->Program();
   if (!program) {
      if (SNode* root = syntax->Tree()) {
         if (SEMANTIC_MODE(Main, Node)) program = root->Create(syntax);
         if (SEMANTIC_MODE(Main, Turn)) program = root->Make(syntax);
         syntax->Program(program);
      }
   }
   if (!program) {
      if (SEMANTIC_MODE(Main, Tree)) {
         program = syntax->Node();
         syntax->Program(program);
      }
   }
   if (syntax->option & T_OptionMode::omSyntaxOnly) return true;
   if (syntax->option & T_OptionMode::omPrintSyntax) {
      print_tree("Syntax ");
   }
   A_Syntax::mmSemantic;
   A_Syntax::mmGenerate;
   if (program) {
      if (SEMANTIC_MODE(Phase, ThreePhase)) {
         program->Variables(*this, T_Step::tsAll);
         program->Verify(*this, 0);
      } else {
      }
      VerifyFunc();
      program->Codes(*this, T_VerifyMode::mvNone);
      if (!IsQuad()) {
         if (syntax->option & T_OptionMode::omEraseCode) CodeTable.Erase();
         CodeTable.Labels();
      }
   } else if (!SEMANTIC_MODE(Generate, None)) {
      VerifyFunc();
      if (syntax->option & T_OptionMode::omEraseCode) CodeTable.Erase(true);
      CodeTable.Gotos();
      CodeTable.Labels(true);
   }
   if (syntax->option & T_OptionMode::omPrintSemantic) {
      print_tree("Semantic ");
   }
   syntax->print_stack();
   return true;
}

void TSemantic::print_tree(const char* title)
{
   printf("\n--- %sTree ----\n",title);
   TNode* program = syntax->Program();  
   if (program) {
      program->print(0, printer);
   }
}

char* get_file_name(const char*file, const char* ext);

void TSemantic::Result(const char* file)
{
// parse.FuncTable.print();
   if (!semantic) return;
   semantic->print(printer);
   if (syntax->ErrorTable.size()) syntax->ErrorTable.print();
   if (UserLabelTable.size()) UserLabelTable.print(printer);
   if (UserGoToTable.size()) UserGoToTable.print(printer);
// GarbageTable.print();
// parse.clear(parse.Program());
   if ((syntax->option & T_OptionMode::omPrintCodes) && code_count) {
      char *file_code  = get_file_name(file,"code");
      TPrinter printer(file_code, 0x00);
      WriteCode(printer);
      free(file_code);
   }
   if ((syntax->option & T_OptionMode::omPrintCodes) && quad_count) {
      char *file_quad = get_file_name(file, "quad");
      TPrinter printer(file_quad, 0x00);
      WriteQuad(printer);
      free(file_quad);
   }
   if (syntax->option & T_OptionMode::omPrintTree) {
      TNode* program = syntax->Program();  
      if (program) {
         char *file_tree  = get_file_name(file,"tree");
         TPrinter printer(file_tree, 0x00);
         program->print(0, printer);
         free(file_tree);
      }
   }
   if (syntax->option & T_OptionMode::omPrintSNode) { // print_SNode
      SNode* tree = syntax->Tree();
      if (tree) {
         char *file_node  = get_file_name(file,"node");
         TPrinter printer(file_node, 0x00);
         tree->print(0, printer);
         free(file_node);
      }
   }
   if (syntax->option & T_OptionMode::omPrintTree) {
      TSyntaxTree* unit = syntax->Auto();
      if (unit && unit->root) {
         char *file_unit = get_file_name(file, "auto");
         TPrinter printer(file_unit, (syntax->option & T_OptionMode::omAutoNoDigit) ? T_OptionMode::omAutoNoDigit : T_OptionMode::omNone);
         unit->print(printer);
         free(file_unit);
      }
   }

   syntax->ClearProgram();
   CodeTable.Clear();
   FuncTable.Clear();
   OperTable().Clear();
   GMakerTable::maker_table.Clear();
   TBaseType::Clear();
   GarbageCollectorClear();
}

void TSemantic::Count(int& execs, int& blocks, int& idents) const 
{
   execs = (int)ExecStack.size(); semantic->Count(blocks,idents);
}

// --------------------------- Tables ---------------------------
void TFuncTable::Add(TNodeDefFunc* func)
{
   TFuncTableItem item(func, NULL); 
   if (semantic->IsQuad()) item.quad = new TQuadTable(); else item.code = new TCodeTable(semantic);
   push_back(item);
	func->number = (int)size() - 1;
   if (ACTION(Code)) {
      func->SetOwner(this);
   }
}

int  TFinder::Match(const TFuncProfile &profile, const TFuncProfile &join)
{
   if (!semantic->Compare(profile.ident, join.ident)) return -1;
   int cur_weight = profile.Match(join);
   if (cur_weight < 0) return -1;
   if (cur_weight < weight) {
      weight = cur_weight; return 1;
   }
   return 0;
}

TNodeDefFunc* TFuncTable::Find(const TFuncProfile &profile, TFinder& finder) const
{
   finder.weight = 1000000;
	TNodeDefFunc *function_gut = NULL;
   for (const TFuncTableItem& item : (*this)) {
      TNodeDefFunc* func = item.func;
		if (finder.Match(*func->profile, profile) < 1) continue;
		function_gut = func;
		if (finder.weight == 0) break;
   }
   return function_gut;
}

TNodeDefFunc* TSemantic::FindFunc(const TFuncProfile &profile, TFinder& finder) const
{
   if (IsBlock()) return FuncTable.Find(profile, finder);

   T_NodeList* global_block = NULL;
   TNodeDefFunc *function_this = NULL;
   if (IsTree()) {
      global_block = dynamic_cast<T_NodeList*> (syntax->Program()->root());
   } else if (IsStack()) {
      TStackRule* stack = NULL;
      M_Syntax *m_syntax = dynamic_cast<M_Syntax*> (syntax);
      if (m_syntax && m_syntax->CountNodes()) {
         stack = &m_syntax->tree_stack;
      } else if (S_Syntax *g_syntax = dynamic_cast<S_Syntax*> (syntax)) {
         stack = &g_syntax->rule_stack;
      }
      if (!stack) return NULL;
      for (int index = 0; index < stack->filled(); index++) {
         TStackRuleItem& stack_item = stack->stack_item(index);
         if (!global_block) {
            global_block = dynamic_cast<T_NodeList*> (stack_item.lexeme_node.tree);
         }
         if (!function_this) {
            function_this = dynamic_cast<TNodeDefFunc*> (stack_item.lexeme_node.tree);
         }
         if (function_this && global_block) break;
      }
   }
   finder.weight = 1000000;
	TNodeDefFunc *function_gut = NULL;
   if (!global_block) return function_gut;
   for (TNode* node : *global_block) {
      TNodeDefFunc* func = dynamic_cast<TNodeDefFunc*>(node);
      if (!func) {
         TNodeDefine *def = dynamic_cast<TNodeDefine*>(node);
         if (def && (def->Count() == 1)) {
            func = dynamic_cast<TNodeDefFunc*>(def->front());
         }
      }
      if (!func || !func->profile) continue;
      if (finder.Match(*func->profile, profile) > 0) {
         function_gut = func;
         if (finder.weight == 0) break;
      }
   }
   if (function_this && function_this->profile) {
      if (finder.Match(*function_this->profile, profile) > 0) {
         function_gut = function_this;
      }
   }
   return function_gut;
}

TNodeDefFunc* TFuncTable::find(const TFuncProfile &profile, TFinder& finder) const
{
   for (; finder.index < (int)size(); finder.index++) {
      TNodeDefFunc* func = (*this)[finder.index].func;
      if (!semantic->Compare(func->Lexeme(),profile.ident)) continue;
		if (func->profile->match(profile)) return func;
   }
   return NULL;
}

TFuncTable::~TFuncTable()
{
   Clear();
}
void TFuncTable::Clear()
{

   if (ACTION(Node)) {
      iterator ip = begin();
      while (ip != end()) { 
         TNodeDefFunc* func = (*ip).func;
         ClearNode(func);
         TQuadTable* quad = (*ip).quad;
         if (quad) delete quad;
         ip = erase(ip); 
      }
   }
}

void TFuncTable::Codes()
{
   for (TFuncTableItem& item : (*this)) { item.func->Codes(*semantic, T_VerifyMode::mvNone); }
}

void TFuncTable::print(TPrinter& printer)
{
  printf("\n--- FuncTable ----\n");
   for (const TFuncTableItem& item : (*this)) { item.func->print(0, printer); }
}

void TLabelTable::print(TPrinter& printer)
{
   printf("\n--- LabelTable ---- %d ----\n",(int)size());
   for (const TNodeLabel* label : (*this)) { label->print(0, printer); }
}

bool T_UserGoToLabel::Compare(const T_UserGoToLabel &join) const
{
// this - label, join - goto
   int count_label = (int)size(), count_goto = (int)join.size(), count = MIN(count_label,count_goto);
   for (int i = 0; i < count; i++) {
      if (((*this)[i].block != join[i].block) || ((*this)[i].offset > join[i].offset)) return false;
   }
   for (int i = count + 1; i < count_label; i++) {
      if ((*this)[i].offset) return false;
   }
   return true;
}

void T_UserGoToLabel::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   for (const T_UserGoToItem& item : *this) {
      fprintf(file, " (%d,%d)", item.block, item.offset);
   }
}

void TUserLabelTable::Add(TNodeUserLabel* label)
{
   TNodeUserLabel* old_label = Find(label->Lexeme());
   if (old_label) {
      semantic->AddError(label,erDuplicateLabel);
   } else {
      push_back(label);
   }
}

TNodeUserLabel* TUserLabelTable::Find(const T_Lexeme& ident)
{
   for (TNodeUserLabel* label : (*this)) {
      if (semantic->Compare(label->Lexeme(),ident)) return label;
   }
   return NULL;
}

bool TUserLabelTable::Find(TNodeUserGoTo* go_to)
{
   TNodeUserLabel* label = semantic->UserLabelTable.Find(go_to->Lexeme());
   if (label) {
      if (!label->Compare(*go_to)) {
         semantic->AddError(go_to,erErrorLabel);
      }
      go_to->SetLabel(label);
      return true;
   }
   return false;
}

void TUserLabelTable::Verify()
{
   for (TNodeUserLabel* label : (*this)) {
      if (!label->go_to) {
         semantic->AddError(label,erUnusedLabel);
      }
   }
}

void TUserLabelTable::print(TPrinter& printer)
{
   printf("\n--- UserLabelTable ---- %d ----\n",(int)size());
   for (const TNodeUserLabel* label : (*this)) { label->print(0, printer); }
}

void TUserGoToTable::Add(TNodeUserGoTo* go_to)
{
   if (!semantic->UserLabelTable.Find(go_to)) {
      push_back(go_to);
   }
}

void TUserGoToTable::Verify()
{
   for (TNodeUserGoTo* go_to : (*this)) {
      if (!semantic->UserLabelTable.Find(go_to)) {
         semantic->AddError(go_to,erUnknownLabel);
      }
   }
}

void TUserGoToTable::print(TPrinter& printer)
{
   printf("\n--- UserGoToTable ---- %d ----\n",(int)size());
   for (const TNodeUserGoTo* go_to : (*this)) { go_to->print(0, printer); }
}

// ------------------------- TCodeTable -------------------------
TCodeTable::~TCodeTable()
{
   Clear();
}

void TCodeTable::Clear()
{
   iterator ip = begin();
   while (ip != end())
   {
      TNodeDefFunc* def_func = dynamic_cast<TNodeDefFunc*>((*ip));
      if (!def_func) {
         GarbageCollectorAdd(*ip,0x01);
      }
      ip = erase(ip);
   }
}

void TCodeTable::Add(TNode* code, int counter)
{
   if (!code || !counter) {
      int i = 12; i++;
   }
   if (counter < 0)
      push_back(code);
   else
      insert(begin() + counter,code);
}

void TCodeTable::Erase(bool del)
{
   bool yes_erase = true;
   while(yes_erase) {
      yes_erase = false;
		iterator ip = begin();
      while (ip != end()) { 
         TNodeLabel* label = dynamic_cast<TNodeLabel*>(*ip);
         if (label && !label->go_to) {
            GarbageCollectorAdd(*ip, del);
            ip = erase(ip); yes_erase = true; 
            continue;
         }
         if (label && (ip > (begin() + 1))) { // go_if l1; go_to l2; label l1; -> go_else l2; label l1;
            TNodeGoTo* go_one = dynamic_cast<TNodeGoTo*>(*(ip - 2));
            TNodeGoTo* go_two = dynamic_cast<TNodeGoTo*>(*(ip - 1));
            if (go_one && (go_one-> GetLabel() == label) && go_two && (go_two->type == T_GoTo::tgGoTo)) {
               go_two->type = (go_one->type == T_GoTo::tgIf) ? T_GoTo::tgElse : T_GoTo::tgIf;
               go_one->SetLabel(NULL);
               yes_erase = true; 
               continue;
            }
         }
         if (label && (ip < (end() - 1))) {
            TNodeLabel* label_after = dynamic_cast<TNodeLabel*>(*(ip + 1)); // label l1; label l2; - l2 -> l1
            if (label_after) {
               semantic->Reference(label_after,label);
               ip++; 
               yes_erase = true; 
               continue;
            }
            TNodeGoTo* go_after = dynamic_cast<TNodeGoTo*>(*(ip + 1)); // label l1; go_to l2; - l1 -> l2
            if (go_after && (go_after->type == T_GoTo::tgGoTo) && (go_after->GetLabel() != label)) {
               semantic->Reference(label,go_after->GetLabel());
               ip++; 
               yes_erase = true; 
               continue;
            }
         }
         TNodeGoTo* go_to = dynamic_cast<TNodeGoTo*>((*ip));
         if (go_to && !go_to->GetLabel()) {
            GarbageCollectorAdd(*ip, del);
            ip = erase(ip); yes_erase = true; 
            continue;
         }
         if (go_to && ((ip + 1) != end())) { // go_xx l1; label l1; ->
            TNodeLabel* label = dynamic_cast<TNodeLabel*>(*(ip + 1));
            if (label && (go_to->GetLabel() == label)) {
               go_to->SetLabel(NULL);
               if (go_to->type == tgGoTo) { // go_to l1; label l1; -> label l1;
                  GarbageCollectorAdd(*ip, del);
                  ip = erase(ip); 
               } else { // go_<if,else> l1; label l1; -> pop; label l1;
                  TNodeCommand* command = new TNodeCommand(T_Command::command_Pop,1,0,btVoid);
                  GarbageCollectorAdd(*ip, del);
                  (*ip) = command;
               }
               yes_erase = true; 
               continue;
            } 
         }
         TNodeCommand* command_prev = NULL;
         if (ip != begin()) {
            command_prev = dynamic_cast<TNodeCommand*>(*(ip - 1));
         }
         if (go_to && ((go_to->type == T_GoTo::tgIf) || (go_to->type == T_GoTo::tgElse)) && command_prev) {
            if (command_prev->command == T_Command::command_PushInt) {
               int value = command_prev->param;
               command_prev->command = T_Command::command_None;
               if (value && (go_to->type == T_GoTo::tgIf) || !value && (go_to->type == T_GoTo::tgElse)) {
                  go_to->type = T_GoTo::tgGoTo;
               } else {
                  go_to->SetLabel(NULL);
                  GarbageCollectorAdd(*ip, del);
                  ip = erase(ip); 
               } 
               yes_erase = true; 
               continue;
            }
         }
         bool yes_return = false;
         TNodeCommand* command = dynamic_cast<TNodeCommand*>((*ip));
         if (command) {
            if (command->command == T_Command::command_Pop) {
               if ((command->param == -1) && ((ip + 1) != end())) {
                  int del_count = 0;
                  if (TNodeUserGoTo* go_to = dynamic_cast<TNodeUserGoTo*>(*(ip + 1))) {
                     if (TNodeUserLabel *label = (TNodeUserLabel*)go_to->GetLabel()) {
                        del_count = go_to->back().offset - label->back().offset;
                     }
                  }
                  command->param = del_count;
               } else if ((command->param == 1) && command_prev && (command_prev->command == T_Command::command_Oper) && (command_prev->base_type != btVoid)) {
                  command_prev->mode = 1; command_prev->base_type = btVoid;
                  command->param = 0;
               }
               if (!command->param) {
                  command->command = T_Command::command_None;
               }
            }
            if (command->command == T_Command::command_None) {
               GarbageCollectorAdd(*ip, del);
               ip = erase(ip); yes_erase = true; 
               continue;
            }
            if ((command->command == T_Command::command_Pop) && (command->param == 1) && command_prev) {
               if ((command_prev->command == T_Command::command_PushInt) || (command_prev->command == T_Command::command_PushNum)) {
                  command_prev->command = command->command = T_Command::command_None; yes_erase = true; 
                  continue;
               }
            }
            yes_return = (command->command == T_Command::command_Return);
         }
         ip++; 
         if (go_to && (go_to->type == tgGoTo) || yes_return) {
            while ((ip != end()) && (!(label   = dynamic_cast<TNodeLabel*>(*ip))   || !label->go_to) &&
                                    (!(command = dynamic_cast<TNodeCommand*>(*ip)) || (command->command != T_Command::command_Exit)) &&
                                    !(dynamic_cast<TNodeDefFunc*>(*ip))) {
               TNodeGoTo* go_to = dynamic_cast<TNodeGoTo*>(*ip);
               if (go_to) go_to->SetLabel(NULL);
               GarbageCollectorAdd(*ip, del);
               ip = erase(ip); yes_erase = true;
            }
         }
      }
   }
}

void TCodeTable::Gotos()
{
   int count = (int)size();
   for (int ip = 1; ip < count; ip++) {
      TNodeCommand* command = dynamic_cast<TNodeCommand*>((*this)[ip - 1]);
      if (command && (command->command == T_Command::command_Pop) && (command->param == -1)) {
         int del_count = 0;
         if (TNodeUserGoTo* go_to = dynamic_cast<TNodeUserGoTo*>((*this)[ip])) {
            if (TNodeUserLabel *label = (TNodeUserLabel*)go_to->GetLabel()) {
               del_count = go_to->back().offset - label->back().offset;
            }
         }
         command->param = del_count;
      }
   }
}

void TCodeTable::Labels(bool del)
{
   int count = (int)size();
   for (int ip = 0; ip < count; ip++) {
      TNodeLabel* label = dynamic_cast<TNodeLabel*>((*this)[ip]);
      if (label) {
         label->command = ip;
         TNodeCommand* command = new TNodeCommand(T_Command::command_Label,ip,label->go_to,btVoid);
         GarbageCollectorAdd((*this)[ip], del);
         (*this)[ip] = command;
      }
   }
   for (int ip = 0; ip < count; ip++) {
      TNodeGoTo* go_to = dynamic_cast<TNodeGoTo*>((*this)[ip]);
      if (go_to) {
         TNodeLabel* label = go_to->GetLabel();
         if (label) {
            TNodeCommand* command = new TNodeCommand(T_Command::command_GoTo,label->command,go_to->type,btUnknown);
            GarbageCollectorAdd((*this)[ip], del);
            (*this)[ip] = command;
      	} else {
            semantic->AddError(go_to,erUnknownLabel);
         }
      }
   }
}

void TCodeTable::write(TWriter& printer) const
{
   const_iterator p = begin();
   int ip = 0;
   while (p != end()) {
      if (TNodeCommand *command = dynamic_cast<TNodeCommand*>((*p))) {
         command->write(printer);
         //         fprintf(file," -->> %05d", ip);
      } else {
         if (*p) (*p)->TNode::write(printer);
      }
      p++; ip++;
      printer.eol();
   }
}

void TCodeTable::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   printf("\n--- CodeTable ---- %d ----\n",(int)size());
   if ((print_mode & T_OptionMode::omPrintCodes) == 0) return;
	const_iterator p = begin(); 
   int ip = 0;
   while (p != end()) { 
      if (TNodeCommand *command = dynamic_cast<TNodeCommand*>((*p))) {
         command->print(0, printer);
         printf(" -->> %05d", ip);
      } else {
         (*p)->TNode::print(-1, printer); 
      }
      p++; ip++;
   }
}

// ------------------------- TQuadruple -------------------------

const char* title_cast_type(T_CastType cast);
const char* title_command_mode_goto(int mode);

void TQuadruple::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   const TSemantic* semantic = printer.semantic;
   fprintf(file, "%-10s", quadruple_title(quad));
   if (quad == TQuadruple::T_Quad::qtNone) return;
   fprintf(file, " "); value_number.write(printer);
   fprintf(file, " "); arg_one.write(printer);
   fprintf(file, " "); arg_two.write(printer);
   fprintf(file, " "); result.write(printer);
   if ((quad == TQuadruple::T_Quad::qtUnary) || (quad == TQuadruple::T_Quad::qtBinary)) {
      fprintf(file, ", oper  = %-14s", lexeme_type_title((T_Symbol::T_Type)oper));
      if (node) fprintf(file, ", type = %-10s", TBaseType::Title(node->BaseType()));
   } else if (quad == TQuadruple::T_Quad::qtCast) {
      fprintf(file, ", cast  = %-14s", title_cast_type((T_CastType)oper));
      if (node) fprintf(file, ", type = %-10s", TBaseType::Title(node->BaseType()));
   } else if (quad == TQuadruple::T_Quad::qtIndex) {
      fprintf(file, ",                       ");
      if (node) fprintf(file, ", type = %-10s", TBaseType::Title(node->BaseType()));
   } else if (quad == TQuadruple::T_Quad::qtCall)
      fprintf(file, ", func  = %-14s", (oper >= 0) ? semantic->FuncTable[oper].func->Lexeme().Text() : "unknown");
   else if (quad == TQuadruple::T_Quad::qtGoto)
      fprintf(file, ", goto  = %-14s", title_command_mode_goto(oper));
   else if (quad == TQuadruple::T_Quad::qtLabel) {
      TNodeUserLabel* label = dynamic_cast<TNodeUserLabel*> (node);
      if (label) {
         fprintf(file, ", label = %-14s", label->Lexeme().Text());
      }
   }
}

TQuadTable& TSemantic::Quad()
{
   if (function == NULL) return QuadTable; else return *FuncTable[function->number].quad;
}

TQuadTable::TQuadTable()
{
   for (int &item : value_numbar_maker) {
      item = 0;
   }
}

void TQuadTable::Add(TQuadruple* quad, int counter) 
{ 
   if (counter == 0) {
      push_back(quad);
   } else if (counter < 0) {
      insert(end() + counter, quad);
   } else {
      insert(begin() + counter, quad);
   }
}

void TQuadTable::AddLabel(TQuadruple* quad, int counter)
{
   int label = quad->value_number.number;
   if ((int)label_quad.size() < label + 1) {
      label_quad.resize(label + 1, -1);
   }
   label_quad[label] = counter;
}

void TQuadTable::ValueNumber(TAddress& value_number)
{
   switch (value_number.alloc) {
   case taGlobal:
   case taLocal:
   case taParam:
   case taOper:
   case taLabel:
      value_number.number = value_numbar_maker[value_number.alloc]++;
      break;
   default:
      break;
   }

}

void TQuadTable::Reset()
{
   value_numbar_maker[T_Alloc::taLocal  ] = 0;
   value_numbar_maker[T_Alloc::taParam  ] = 0;
   value_numbar_maker[T_Alloc::taOper   ] = 0;
   value_numbar_maker[T_Alloc::taLabel  ] = 0;
   value_numbar_maker[T_Alloc::taCommand] = 0;
}

bool TQuadTable::Verify()
{
   int current = 0;
   int change_count = 0;
   while (int ret = GoToGoToLabel(current) >= 0) {
      if (ret == 1) { change_count++; }
   }
   current = 0;
   while (int ret = GoToLabel(current) >= 0) {
      if (ret == 1) { change_count++; }
   }
   current = 0;
   while (int ret = LabelGoTo(current) >= 0) {
      if (ret == 1) { change_count++; }
   }
   current = 0;
   while (int ret = Label(current) >= 0) {
      if (ret == 1) { change_count++; }
   }
   return true;
}

int  TQuadTable::Label(int& current)
{
   if (current > Count() - 1) { return -1; }
   TQuadruple& one = *(*this)[current];
   if (one.quad != TQuadruple::qtLabel) { current++; return 0; }
   TNodeLabel* label = dynamic_cast<TNodeLabel*> (one.node);
   if (label) {
      if (!label->go_to) {
         one.quad = TQuadruple::qtNone;
      }
   }
   current += 1; return 1;
}

int  TQuadTable::LabelGoTo(int& current)
{
   if (current > Count() - 2) { return -1; }
   TQuadruple& one = *(*this)[current + 1];
   TQuadruple& two = *(*this)[current];
   if ((one.quad != TQuadruple::qtGoto) || (one.oper != T_GoTo::tgGoTo)) { current++; return 0; }
   if (two.quad != TQuadruple::qtLabel) { current++; return 0; }
   if (!(one.arg_one == two.value_number)) { current += 2; return 0; }
   one.quad = TQuadruple::qtNone;
   TNodeLabel* label = dynamic_cast<TNodeLabel*> (two.node);
   if (label) {
      if (!--label->go_to) {
         two.quad = TQuadruple::qtNone;
      }
   }
   current += 2; return 1;
}

int  TQuadTable::GoToLabel(int& current)
{
   if (current > Count() - 2) { return -1; }
   TQuadruple& one = *(*this)[current];
   TQuadruple& two = *(*this)[current + 1];
   if ((one.quad != TQuadruple::qtGoto) || (one.oper != T_GoTo::tgGoTo)) { current++; return 0; }
   if (two.quad != TQuadruple::qtLabel) { current++; return 0; }
   if (!(one.arg_one == two.value_number)) { current += 2; return 0; }
   one.quad = TQuadruple::qtNone;
   TNodeLabel* label = dynamic_cast<TNodeLabel*> (two.node);
   if (label) {
      if (!--label->go_to) {
         two.quad = TQuadruple::qtNone;
      }
   }
   current += 2; return 1;
}

int  TQuadTable::GoToGoToLabel(int& current)
{
   if (current > Count() - 3) { return -1; }
   TQuadruple& one   = *(*this)[current];
   TQuadruple& two   = *(*this)[current + 1];
   TQuadruple& three = *(*this)[current + 2];
   if ((one.quad != TQuadruple::qtGoto) || (one.oper != T_GoTo::tgIf)) { current++; return 0; }
   if (two.quad != TQuadruple::qtGoto) { current += 2; return 0; }
   if (two.oper != T_GoTo::tgGoTo) { current++; return 0; }
   if (three.quad != TQuadruple::qtLabel) { current++; return 0; }
   if (!(one.arg_one == three.value_number)) { current += 3; return 0; }
   one.oper = T_GoTo::tgElse; one.arg_one = two.arg_one;
   three.quad = two.quad = TQuadruple::qtNone;
   TNodeLabel* label = dynamic_cast<TNodeLabel*> (three.node);
   if (label) {
      label->go_to--;
   }
   current += 3; return 1;
}

void TQuadTable::write(TWriter& printer) const
{
   const_iterator p = begin();
   for (const TQuadruple* quad : (*this)) {
      quad->write(printer);
      printer.eol();
   }
}

void TQuadTable::write_label(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   for (int l = 0; l < (int)label_quad.size(); l++) {
      int quad_label = label_quad[l];
      if (quad_label >= 0) {
         const TQuadruple* quadruple_label = (const TQuadruple*)((*this)[quad_label]);
         quadruple_label->value_number.write(printer);
         TNodeLabel* label = dynamic_cast<TNodeLabel*> (quadruple_label->node);
         fprintf(file, " refer = %5d", label->go_to);
      }
      fprintf(file, " %5d\n", quad_label);
   }
}

void TSemantic::WriteQuad(TPrinter& printer)
{
   PRINTER_FILE_MODE
   printer.semantic = this;
   for (TFuncTableItem& item : FuncTable) {
      item.quad->Verify();
      item.func->TNode::print(-1, printer); printer.eol();
      item.quad->write(printer);
      printer.eol();
      item.quad->write_label(printer);
      printer.eol();
   }
   QuadTable.Verify();
   QuadTable.write(printer);
   if (!QuadTable.label_quad.empty()) {
      printer.eol();
   }
   QuadTable.write_label(printer);
   WriteConst(printer);
}

void TSemantic::AddQuad(TQuadruple* quad, int counter) 
{ 
   int size = (int)Quad().size();
   if (counter < 0) {
      size += counter;
   } else if (counter > 0) {
      size = counter;
   }
   if ((quad->quad == TQuadruple::T_Quad::qtUnary) || (quad->quad == TQuadruple::T_Quad::qtBinary) || (quad->quad == TQuadruple::T_Quad::qtCast) || 
       (quad->quad == TQuadruple::T_Quad::qtSet)   || (quad->quad == TQuadruple::T_Quad::qtIndex)) {
      quad->value_number.number = size; 
      quad->value_number.alloc = T_Alloc::taOper;
   } else if ((quad->quad == TQuadruple::qtGoto) || (quad->quad == TQuadruple::qtReturn) || (quad->quad == TQuadruple::qtParam) || (quad->quad == TQuadruple::qtCall)){
      quad->value_number.number = size;
      quad->value_number.alloc = T_Alloc::taCommand;
   } 
   Quad().Add(quad, counter); quad_count++; 
   if (quad->quad == TQuadruple::qtLabel) {
      Quad().AddLabel(quad, size);
   }
}

void TSemantic::WriteConst(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   TAddress address;
   printer.eol();
   address.alloc = T_Alloc::taInteger;
   for (const int& item : syntax->Scan().integers) {
      address.write(printer);
      fprintf(file, " %d\n", item);
      address.number++;
   }
   printer.eol();
   address.alloc = T_Alloc::taNumber; address.number = 0;
   for (const double& item : syntax->Scan().numbers) {
      address.write(printer);
      fprintf(file, " %f\n", item);
      address.number++;
   }
}

void TAddress::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   if (alloc != T_Alloc::taNone) {
      fprintf(file, "%-10s %5d", title_alloc(alloc), number);
   } else {
      fprintf(file, "                ");
   }
}

static const char* quadruple_type[] = {
   "None", "Const", "Binary", "Unary", "Cast", "Set", "Goto", "If", "Param", "Call", "Return", "Index", "Range", "Variable", "Array", "Referense", "Pointer", "Refer", "Label"
};

const char* quadruple_title(TQuadruple::T_Quad quad) { return quadruple_type[quad]; }

// ------------------------- TGarbage -------------------------
TGarbageTable GarbageCollector;

void GarbageCollectorAdd(TNode* node, int mode_del)
{
   GarbageCollector.Add(node, mode_del);
}
void GarbageCollectorClear()
{
   GarbageCollector.Clear();
}

TGarbageTable::~TGarbageTable()
{
   Clear();
}

void TGarbageTable::Add(TNode* node, int mode_del)
{ 
   if (!(mode_del & 0x01)) {
      if (dynamic_cast<TNodeGoTo*>(node)) {
         if (!dynamic_cast<TNodeUserGoTo*>(node) && !dynamic_cast<TNodeBreakContinue*>(node)) {
            mode_del |= 0x01;
         }
      } else if (dynamic_cast<TNodeLabel*>(node)) {
         if (!dynamic_cast<TNodeUserLabel*>(node)) {
            mode_del |= 0x01;
         }
      } else if (dynamic_cast<TNodeCommand*>(node)) {
         mode_del |= 0x01;
      }
   }
   if ((mode_del & 0x01) || !node->Owner()) {
      std::set<TNode*> ::iterator ip = find(node);
      if (ip != end()) {
         return;
      }
      node->SetOwner();
      insert(node);
   }
}

void TGarbageTable::Clear()
{
   iterator ip = begin();
   while (ip != end()) {
      delete *ip; ip = erase(ip);
   }
}

void TGarbageTable::print(TPrinter& printer)
{
	printf("\n--- GarbageTable ---- %d ----\n",(int)size());
   for (const TNode* node : (*this)) { node->print(0, printer); }
}
