#include "stdafx.h"
#include "maker.h"
#include "TSemantic.h"

// --------------------------- GMaker ---------------------------
GMakerTable GMakerTable::maker_table;

GMaker::GMaker(const char* t, GMakerTable* table) 
   :make_tree(NULL), make_code(NULL), make_yacc(NULL), title(t), used(0)
{
   int index = table->Find(t);
   if (index >= 0) {
   } else {
      table->Add(*this);
   }
}

GMaker::GMaker(bool (*f)(const GSymbol&, M_Syntax*), const char* t, GMakerTable* table) 
   :make_tree(f), make_code(NULL), make_yacc(NULL), title(t), used(0) 
{
   int index = table->Find(t);
   if (index >= 0) {
      GMaker* maker = (*table)[index];
      maker->make_tree = f;
   } else {
      table->Add(*this);
   }
}

GMaker::GMaker(bool (*f)(const GSymbol&, MC_Syntax*, TSemantic*), const char* t, GMakerTable* table)
   :make_tree(NULL), make_code(f), make_yacc(NULL), title(t), used(0)
{
   int index = table->Find(t);
   if (index >= 0) {
      GMaker* maker = (*table)[index];
      maker->make_code = f;
   } else {
      table->Add(*this);
   }
}

GMaker::GMaker(bool (*f)(const GSymbol&, M_Syntax*, T_Lexeme_SNode*[]), const char* t, GMakerTable* table) 
   :make_tree(NULL), make_code(NULL), make_yacc(f), title(t), used(0)
{
   int index = table->Find(t);
   if (index >= 0) {
      GMaker* maker = (*table)[index];
      maker->make_yacc = f;
   } else {
      table->Add(*this);
   }
}

void GMaker::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   if (!(print_mode & T_PrintMode::pmMakerCompact)) {
   	fprintf(file,"\n%-25s:", title);
      if (make_tree) fprintf(file," tree"); else fprintf(file,"     ");
      if (make_code) fprintf(file," code"); else fprintf(file,"     ");
      if (make_yacc) fprintf(file," yacc"); else fprintf(file,"     ");
      fprintf(file, " %d", used);
   } else {
   	fprintf(file,"%s", title);
   }
}

GMakerTable::~GMakerTable()
{
   Clear();
}

void GMakerTable::Clear()
{
   indexs.clear();
   clear();
}

void GMakerTable::Add(GMaker& m) 
{ 
   const std::pair<const Key, int> item(Key(m.title),count());
   push_back(&m);
   indexs.insert(item); 
}
int  GMakerTable::Find(const char* k) const
{
   TMakerIndex::const_iterator ip = indexs.find(k); 
   if (ip != indexs.end()) {
      const std::pair<const Key, int> &item = (*ip);
      return item.second;
   } else {
      return -1;
   }
}

void GMakerTable::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   fprintf(file,"\n--- MakerTable --- <%d> ---\n", count());
   if (print_mode == T_PrintMode::pmMakerNone) return;
   for (const GMaker* maker : *this) {
      maker->print(printer);
   } 
}

const char* maker_title(int maker)
{
   if ((maker < 0) || (maker >= GMakerTable::maker_table.count())) return "unknown_maker";
   return GMakerTable::maker_table[maker]->title;
}

// --------------------------- TStackRule ---------------------------
bool TStackRuleItem::Piston(const TStackRuleItem& source, int mode) // (lexeme, node, tree) ==>> 
{
   if (sym.IsMaker() || (mode & 0x01) && sym.IsNone() || (mode & 0x02) && sym.IsProduce()) {
      if (source.lexeme_node.node) { lexeme_node.node = source.lexeme_node.node; }
      if (source.lexeme_node.tree) { lexeme_node.tree = source.lexeme_node.tree; }
      if (lexeme_node.lexeme.IsNone()) lexeme_node.lexeme = source.lexeme_node.lexeme;
      return true;
   }
   return false;
}

void TStackRuleItem::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   sym.print(printer);
//   lexeme_node.lexeme;
   if (lexeme_node.node) lexeme_node.node->print(0, printer);
   if (lexeme_node.tree) lexeme_node.tree->TNode::print(0, printer);
   if (lexeme_node.unit) lexeme_node.unit->print(printer, 0);
}

void TStackRule::lexeme_piston(int item_step, const T_Lexeme& lexeme)
{
   int maker = item_step - 1;
   while ((maker >= 0) && !stack_item(filled() - item_step + maker).sym.IsMaker()) {
      maker--;
   }
   stack_item(filled() - item_step + maker).lexeme_node.lexeme = lexeme;
}

void TStackRule::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   printer.eol();
   int index = (int)size() - 1;
   for (const_reverse_iterator r = rbegin(); r < rend(); r++, index--) {
      fprintf(file, "*%05d* ", index);
      r->print(printer);
      fprintf(file,"\n");
   }
}

// --------------------------- M_Syntax ---------------------------
M_Syntax::M_Syntax(T_Scan *s) :A_Syntax(s), trunc_node(0), trunc_snode(0), trunc_lexeme(0), tree(NULL) { makers = &GMakerTable::maker_table;}

M_Syntax::~M_Syntax()
{
}

void M_Syntax::ClearProgram() 
{
   if (program) {
      program->clear();
      GarbageCollectorAdd(program, 0x01);
      program = NULL;
   }
   if (tree) {
      tree->clear();
      delete tree;
      tree = NULL;
   }
   if (Auto()) {
      Auto()->clear();
   }
}

void M_Syntax::push_lexeme(const T_Lexeme& lexeme)
{ 
   if (!ACTION(Tree) && !ACTION(Code) && !ACTION(Turn) && !ACTION(Call)) return;
   bool print_lexeme = (option & T_OptionMode::omPrintOther) != 0, print_stack = (option & T_OptionMode::omPrintStack) != 0;
   if (print_lexeme && print_stack) {
      printf("l<%d ",CountLexemes() + 1); lexeme.print(&Scan());
   }
   lexemes.push(lexeme); 
}

void M_Syntax::PushLexeme(const T_Lexeme& lexeme) 
{ 
   if (((lexeme.group == T_Lexeme::T_Group::grPriority) || (lexeme.group == T_Lexeme::T_Group::grIdent) || 
        (lexeme.group == T_Lexeme::T_Group::grInteger)  || (lexeme.group == T_Lexeme::T_Group::grNumber) ||
        (lexeme.group == T_Lexeme::T_Group::grReserv)   && ((lexeme.type == T_Lexeme::W_Type::rwDefine) || (lexeme.type == T_Lexeme::W_Type::rwVoid)))) {
      push_lexeme(forward);
   } else if (lexeme.group == T_Lexeme::T_Group::grOper) {
      push_lexeme(forward);
   } else if ((lexeme.group == T_Lexeme::T_Group::grSyntax) && 
             !((lexeme.type == T_Lexeme::sxEmptyBracket) || (lexeme.type == T_Lexeme::sxEmptyCramp) || (lexeme.type == T_Lexeme::sxEmptyScrape))) {
      push_lexeme(lexeme);
   }
}

T_Lexeme M_Syntax::PopLexeme()
{ 
   T_Lexeme lexeme = lexemes.top(); lexemes.pop(); 
   bool print_lexeme = (option & T_OptionMode::omPrintOther) != 0, print_stack = (option & T_OptionMode::omPrintStack) != 0;
   if (print_lexeme && print_stack) {
      printf("l>%d ",CountLexemes() + 1); lexeme.print(&Scan()); 
   }
   return lexeme; 
}

void M_Syntax::print_stack(bool all)
{ 
   int count = CountNodes();
   if ((count > 1) || all) {
      TPrinter printer;
      printf("\n--- Stack ----\n");
      for (TStackRule::const_reverse_iterator r = tree_stack.rbegin(); r < tree_stack.rend(); r++) {
         r->lexeme_node.tree->print(0, printer);
      }
   }
}
void M_Syntax::Accept(const TStackRuleItem& item)
{
   if (item.lexeme_node.node) Tree(item.lexeme_node.node);
   if (item.lexeme_node.tree) Program(item.lexeme_node.tree);
}
void M_Syntax::Accept()
{
   if (!Empty()) {
      TNode* node = TopNode(); Program(node);
      SNode* snode = &STop(); Tree(snode);
   }
}

void M_Syntax::Store(T_ScanStore& store)
{
   A_Syntax::Store(store);
   store.store_lexeme = CountLexemes();
   store.store_tree = CountNodes();
   store.store_node = CountSNodes();
}
bool M_Syntax::Restore(const T_ScanStore& store)
{
   TruncLexemes(store.store_lexeme);
   TruncNodes(store.store_tree);
   TruncSNodes(store.store_node);
   return A_Syntax::Restore(store);
}
void M_Syntax::print_store(TPrinter& printer) const
{
   A_Syntax::print_store(printer);
   fprintf(printer.file, "trunc_node=%d, trunc_lexeme=%d, trunc_snode=%d\n", trunc_node, trunc_lexeme, trunc_snode);
}

// --------------------------- MC_Syntax ---------------------------
bool MC_Syntax::Match(T_Lexeme::T_Syntax type)
{
   T_Lexeme lexeme(T_Lexeme::T_Group::grSyntax,type);
   return MatchLexeme(lexeme);
}
bool MC_Syntax::Match(T_Lexeme::T_Group g)
{
   T_Lexeme lexeme(g,0);
   return MatchLexeme(lexeme);
}
bool MC_Syntax::Match(T_Lexeme::T_Group g, T_Symbol::T_Type type)
{
   T_Lexeme lexeme(g,type);
   return MatchLexeme(lexeme);
}
bool MC_Syntax::Match(A_Symbol::T_Priority priority)
{
   T_Lexeme lexeme(T_Lexeme::T_Group::grPriority,priority);
   return MatchLexeme(lexeme);
}
bool MC_Syntax::Match(T_Lexeme::W_Type keyword)
{
   T_Lexeme lexeme(T_Lexeme::T_Group::grReserv,keyword);
   return MatchLexeme(lexeme);
}

void MC_Syntax::Store(T_ScanStore& store)
{
   M_Syntax::Store(store);
   store.store_type = CountTypes();
}
bool MC_Syntax::Restore(const T_ScanStore& store)
{
   TruncTypes(store.store_type);
   return M_Syntax::Restore(store);
}
void MC_Syntax::print_store(TPrinter& printer) const
{
   M_Syntax::print_store(printer);
   fprintf(printer.file, "trunc_type=%d\n", trunc_type);
}

bool MC_Syntax::Maker(const GSymbol& sym)
{
   int ret = 0;
   if (ACTION(None)) return (ret >= 0);
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = ((option & T_OptionMode::omPrintMaker) != 0), print_stack = (option & T_OptionMode::omPrintStack) != 0; 
   int nodes_before=0, lexemes_before=0, types_before=0, turn_before=CountSNodes();
   Counts(nodes_before, lexemes_before, types_before); 
   int execs_before = 0, blocks_before = 0, idents_before = 0;
   if (semantic) semantic->Count(execs_before, blocks_before, idents_before);
   GSymbol maker(sym);
   if (maker.maker >= 0) {
      int index = sym.IsMakerTurn() ? (*makers).maker_turn : (sym.IsMakerCall() ? (*makers).maker_call : maker.maker);
      const GMaker& maker_body = *(*makers)[index];
      ret = -2;
      if (ACTION(Tree) && sym.IsMakerTree() ||
          ACTION(Turn) && sym.IsMakerTurn() ||
          ACTION(Call) && sym.IsMakerCall()
         ) {
         if (!maker_body.make_tree || !maker_body.make_tree(sym,this)) {
            ret = -1; 
         } else {
            ret = 1; 
         }
      }
      if (ACTION(Code) && sym.IsMakerCode()) {
         if (!maker_body.make_code || !maker_body.make_code(sym,this,semantic)) {
            ret = -1;
         } else {
            ret = 1; 
         }
      }
      if ((ret > -2) && print_maker) {
         static char buffer[20] = {};
         SPRINTF(buffer,"%d",maker.param);
         if (ACTION(Turn)) {
            printf("Turner[%s,%s",turn_title((SNode::T_Turn)sym.maker),snode_title((SNode::S_Type)sym.point)); printf(",%s]",buffer); 
         } else {
            TPrinter printer(T_PrintMode::pmMakerCompact);
            printf("Maker["); maker_body.print(printer); printf(",%s]",buffer);
         }
      }
   } else {
      if (print_maker) printf("unknown_maker");
      ret = -1; 
   }
   if ((ret > -2) && print_maker) {
      printf(", ret=%d", ret);
      int nodes_after=0, lexemes_after=0, types_after=0, turn_after=CountSNodes(); 
      Counts(nodes_after, lexemes_after, types_after); 
      int execs_after  = 0, blocks_after = 0, idents_after = 0;
      if (semantic) semantic->Count(execs_after, blocks_after, idents_after);
      printf(" n=[%d,%d],l=[%d,%d],t=[%d,%d],e=[%d,%d],b=[%d,%d],i=[%d,%d],s=[%d,%d]", 
               nodes_before, nodes_after, lexemes_before, lexemes_after, types_before , types_after , 
               execs_before, execs_after, blocks_before , blocks_after , idents_before, idents_after, turn_before, turn_after);
      printf("\n");
   }
   if (ret == -2) ret = 0;
   return (ret >= 0);
}

bool MC_Syntax::MakerSyntaxNode(const GSymbol& sym, T_Lexeme_SNode* data_stack[], int maker_index)
{
   TPrinter printer;
   PRINTER_FILE_MODE

   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = ((option & T_OptionMode::omPrintMaker) != 0); 
   GSymbol maker(sym);
   int index = (maker_index >= 0) ? GMakerTable::maker_table.maker_node : maker.maker;
   if (index >= 0) {
      const GMaker& maker_body = *(*makers)[index];
      ret = -2;
      if ((ACTION(Node) || ACTION(Made)) && (sym.IsMakerYACC() || sym.IsMakerNode())) {
         if (!maker_body.make_yacc || !maker_body.make_yacc(sym,this, data_stack)) {
            ret = -1;
         } else {
            ret = 1; 
         }
      }
   } else {
      ret = -1; 
   }
   if ((ret > -2) && (print_rule || print_maker)) {
      maker.print(printer); printf(", ret=%d", ret);
      printf("\n");
   }
   return (ret >= 0);
}

// ------------------------- C_Syntax -------------------------
bool C_Syntax::GenCastable(T_BaseType from, T_BaseType to, int& made)
{
   return semantic->GenCastable(from, to, made);
}
void C_Syntax::AddCode(TNode* code, int counter) { semantic->AddCode(code, counter); }
void C_Syntax::InsCode(TNode* code, int counter) { semantic->AddCode(code, counter); }
int  C_Syntax::made() { return (int)semantic->Code().size(); }
TNode* C_Syntax::GetCommand(int counter) { return semantic->GetCommand(counter); }

bool C_Syntax::UnaryOper(const T_Lexeme &lexeme)
{
   MakeValue();
   TExprStackItem operand = TipTop();
   const TOperProfile* profile = semantic->Oper(lexeme, operand.type);
   if (profile) {
      TExprStackItem result(profile->result, lexeme);
      GenCastable(operand.type, (*profile)[0]);
      semantic->GenCommand(T_Command::command_Oper, profile->oper, 0, result.type);
      Push(result);
      return true;
   } else {
      Push(btUnknown);
      return error_code(erUnknownOper);
   }
}

bool C_Syntax::BinaryOper(const T_Lexeme &lexeme)
{
   MakeValue();
   TExprStackItem right = TipTop();
   MakeValue();
   TExprStackItem left = TipTop();

   const TOperProfile* profile = semantic->Oper(lexeme, left.type, right.type);
   if (profile) {
      TExprStackItem result(profile->result, lexeme);
      GenCastable(right.type, (*profile)[1], right.made);
      GenCastable(left.type, (*profile)[0], left.made);
      //printf("\nleft = (%s->%s), right = (%s->%s)", TBaseType::Title(left.type), TBaseType::Title((*profile)[0]), TBaseType::Title(right.type), TBaseType::Title((*profile)[1])); 
      semantic->GenCommand(T_Command::command_Oper, profile->oper, 0, result.type);
      Push(result);
      return true;
   } else {
      Push(btUnknown);
      return error_code(erUnknownOper);
   }
}

bool C_Syntax::BinaryLogic(const T_Lexeme &lexeme)
{
   bool oper_or = lexeme.Match(T_Symbol::lxOrOr);
   if (!MakeLogic()) return false;
   TExprStackItem right = TipTop();
   if (!MakeLogic()) return false;
   TExprStackItem left = TipTop();
   if (oper_or) {
      semantic->Reference(left.true_label, right.true_label);
      InsCode(left.false_label, left.made);
   } else {
      semantic->Reference(left.false_label, right.false_label);
      InsCode(left.true_label, left.made);
   }
   Push(right);
   return true;
}

bool C_Syntax::MakeLogic()
{
   TExprStackItem& operand = Top();
   if (operand.type != btLogical) {
      if (!GenCastable(operand.type, T_BaseType::btCInt, operand.made)) {
         return error_code(erUnknownCast);
      }
      operand.true_label = new TNodeLabel(semantic); operand.false_label = new TNodeLabel(semantic);
      TNodeGoTo* go_true = new TNodeGoTo(T_GoTo::tgIf, operand.true_label);
      TNodeGoTo* go_false = new TNodeGoTo(T_GoTo::tgGoTo, operand.false_label);
      AddCode(go_true, operand.made); operand.made++;
      AddCode(go_false, operand.made); operand.made++;
      operand.type = btLogical;
   }
   return true;
}

void C_Syntax::MakeValue()
{
   TExprStackItem& operand = Top();
   if (operand.type == btLogical) {
      semantic->MakeValue(operand.true_label, operand.false_label, operand.made);
      operand.type = btCInt;
   }
}

void C_Syntax::GenReturn(bool value)
{
   TNodeDefFunc* func = dynamic_cast<TNodeDefFunc*>(semantic->Block(T_Block::tbFunc));
   T_BaseType base_type = func ? func->BaseType() : T_BaseType::btVoid;
   semantic->ExecStack.Return();
   T_BaseType return_type = T_BaseType::btVoid;
   if (value) {
      return_type = PopType();
      if (!semantic->GenCastable(return_type, base_type)) {
         error_code(erUnknownCast);
      }
   } else {
      if ((base_type != T_BaseType::btVoid) && (base_type != T_BaseType::btUnknown)) {
         error_code(erNoValue);
      }
   }
   semantic->GenCommand(T_Command::command_Return, 0, base_type);
}

bool C_Syntax::GenBreakContinue(T_Block rate, const T_Lexeme &lexeme)
{
   TNodeBreakContinue *statement = new TNodeBreakContinue(rate, lexeme);
   semantic->FindLabel(*statement);
   if (statement->del_count) semantic->GenPop(statement->del_count);
   semantic->AddCode(statement);
   return true;
}

void C_Syntax::GenGoTo(const T_Lexeme &lexeme)
{
   TNodeUserGoTo *statement = new TNodeUserGoTo(lexeme);
   semantic->MakeGoToLabel(statement);
   semantic->UserGoToTable.Add(statement);
   semantic->GenPop(-1);
   semantic->AddCode(statement);
   semantic->ExecStack.GoTo();
}

// --------------------------- MAKER_TREE_CODE_YACC ---------------------------
void MakeDefType(T_Lexeme& l, int def)
{
   def <<= 16; // GRAMMAR_NLL ||  GRAMMAR_NLR
   if (l.group == T_Lexeme::T_Group::grReserv) {
      l.value = def | l.type;
      l.group = T_Lexeme::T_Group::grSyntax; l.type = T_Lexeme::T_Syntax::sxDefType;
   }
   else if ((l.group == T_Lexeme::T_Group::grSyntax) && (l.type == T_Lexeme::T_Syntax::sxDefType)) {
      l.value |= def;
   }
}

#define MAKER_TREE(FUNC) \
bool make_tree_##FUNC(const GSymbol& item, M_Syntax* syntax);\
static GMaker maker_tree_##FUNC(make_tree_##FUNC,#FUNC, &GMakerTable::maker_table);\
bool make_tree_##FUNC(const GSymbol& item, M_Syntax* syntax)                   

#define MAKER_CODE(FUNC) \
bool make_code_##FUNC(const GSymbol& item, MC_Syntax* syntax, TSemantic* semantic);\
static GMaker maker_code_##FUNC(make_code_##FUNC,#FUNC, &GMakerTable::maker_table);\
bool make_code_##FUNC(const GSymbol& item, MC_Syntax* syntax, TSemantic* semantic)                   

#define MAKER_YACC(FUNC) \
bool make_yacc_##FUNC(const GSymbol& item, M_Syntax* syntax, T_Lexeme_SNode* data_stack[]);\
static GMaker maker_yacc_##FUNC(make_yacc_##FUNC,#FUNC, &GMakerTable::maker_table);\
bool make_yacc_##FUNC(const GSymbol& item, M_Syntax* syntax, T_Lexeme_SNode* data_stack[])                   

#define VARIABLES(NODE) if (NODE && (SYNTAX_MODE(Phase, TwoPhase))) NODE->Variables(*(syntax->data->semantic), 0x00);

#define BLOCK_BEG(NODE) if (NODE && (SYNTAX_MODE(Phase, TwoPhase))) NODE->BlockBegin(*(syntax->data->semantic));
#define BLOCK_END(NODE) if (NODE && (SYNTAX_MODE(Phase, TwoPhase))) NODE->BlockEnd(*(syntax->data->semantic));

#define VARIABLES_STEP(NODE,STEP) if (int my_mode = NODE->Passport(T_Step::ts##STEP)) NODE->Variables(*(syntax->data->semantic), my_mode);
#define VARIABLES_STEPS(NODE,S1,S2,S3,S4) if (int my_mode = NODE->Passport(T_Step::ts##S1 | T_Step::ts##S2 | T_Step::ts##S3 | T_Step::ts##S4)) NODE->Variables(*(syntax->data->semantic), my_mode);

#include "MakerYACC.cpp"
#include "MakerTree.cpp"
#include "MakerCode.cpp"
#include "MakerCall.cpp"

MAKER_TREE(MakerTurn)
{
   T_Lexeme lexeme;
   SNode::T_Turn command = (SNode::T_Turn)item.maker;
   int param = item. MakerParam();

   switch (command) {
   case SNode::ttNone :
      if (!syntax->SEmpty()) {
         SNode* node = syntax->SPop();
         syntax->Tree(node);
      }
      break;
   case SNode::ttPush : 
      if (!syntax->CountLexemes()) return false; lexeme = syntax->PopLexeme();
   case SNode::ttPut : {
      SNode* node = new SNodeList(lexeme,SNode::S_Type(item.point));
      node->option = param;
      syntax->SPush(node);
      } break;
   case SNode::ttAdd  : {
      if (syntax->SEmpty()) return false;
      if (!syntax->CountLexemes()) return false; lexeme = syntax->PopLexeme();
      SNode* node = new SNodeList(lexeme,SNode::S_Type(item.point));
      node->option = param;
      syntax->STop().Add(node);
      } break;
   case SNode::ttMake : {
      if (param < 0) {
         if (!syntax->CountLexemes()) return false; lexeme = syntax->PopLexeme();
      }
      SNodeList* master = new SNodeList(lexeme,SNode::S_Type(item.point));
      master->option = param;
      int count = abs(param);
      while (count--) {
         if (syntax->SEmpty()) return false;
         SNode* node = syntax->SPop();
         master->Insert(0,node);
      }
      syntax->SPush(master);
      } break;
   case SNode::ttDown : {
      if (syntax->SEmpty()) return false;
      SNode* node = syntax->SPop();
      if (syntax->SEmpty()) return false;
      syntax->STop().Add(node);
      } break;
   case SNode::ttUp : {
      if (syntax->SEmpty()) return false;
      SNode* node_1 = syntax->SPop();
      if (syntax->SEmpty()) return false;
      SNode* node_2 = syntax->SPop();
      node_1->Add(node_2);
      syntax->SPush(node_1);
      } break;
   case SNode::ttSwap : {
      if (syntax->SEmpty()) return false;
      SNode* node_1 = syntax->SPop();
      if (syntax->SEmpty()) return false;
      SNode* node_2 = syntax->SPop();
      syntax->SPush(node_1);
      syntax->SPush(node_2);
      } break;
   case SNode::ttCommand : {
      if (item.point == SNode::stLexeme) {
         if (param < 0) {
            while (param++) {
               if (!syntax->CountLexemes()) return false;
               lexeme = syntax->PopLexeme();
            }
         } else  if (param == 1) {
            if (!syntax->CountLexemes()) return false;
            lexeme = syntax->PopLexeme();
            syntax->STop().SetLexeme(lexeme);
         } else {
            return false;
         }
      } else if (item.point == SNode::stParam) {
         if (syntax->SEmpty()) return false;
         syntax->STop().option = param;
      }
      } break;
   }
   return true;
}

MAKER_TREE(LexTypeName)
{
   int command = item.MakerParam();
   return syntax->Command(command);
}

MAKER_YACC(Expressions)
{
   return make_yacc_ExpressionS(item, syntax, data_stack);
}

static int i__node = GMakerTable::maker_table.maker_node = GMakerTable::maker_table.Find("MakerSNode");
static int i__turn = GMakerTable::maker_table.maker_turn = GMakerTable::maker_table.Find("MakerTurn");
static int i__call = GMakerTable::maker_table.maker_call = GMakerTable::maker_table.Find("MakerCall");
