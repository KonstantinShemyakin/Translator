// Parse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TNodes.h"
#include "SNodes.h"
#include "ASyntax.h"

bool SNode::ClearNode(SNode* N)
{
   if (N && (!N->Owner() || (N->Owner() == this))) {
      if (SNodeList *list = dynamic_cast<SNodeList*>(N)) {
         SNodeList::iterator p = list->begin();
         while (p != list->end()) {
            list->ClearNode(*p);
            p = list->erase(p);
         }
      }
      N->clear(); delete N;
      return true; 
   }
   return false;
}

void SNode::clear()   {}

void SNodeList::clear()
{
	iterator p = begin();
   while (p != end()) { 
      ClearNode(*p);
      p = erase(p);
   }
}

void SNode::print(int level, TPrinter& printer) const
{
   PRINTER_FILE_MODE
   const char *t = title();
   print_offset(level, true, file); fprintf(file, "%-15s, type=%s, option=%08X ",t,snode_title(type),option);
   if (level >= 0) {
      if (lexeme.group != lexeme.grNone) {
         TPrinter printer_lexeme(printer, 0x00);
         fprintf(file, "  "); lexeme.print(printer_lexeme, T_Lexeme::print_scan);
      }
   } else {
   	fprintf(file, " pos=%04d, line=%03d, column=%03d, len=%02d", lexeme.pos, lexeme.line, lexeme.column, lexeme.len);
		fprintf(file, ", text=");
   	for (int i = 0; i < lexeme.len; i++) fprintf(file, "%c", T_Lexeme::print_scan->Char(lexeme.pos + i));
   }
}

void SNodeList::print(int level, TPrinter& printer) const
{
   PRINTER_FILE_MODE
   SNode::print(level, printer);
	const_iterator p = begin();
   while (p != end()) { 
      if (*p) (*p)->print(level + 1, printer);
      p++;
   }
}

const T_Lexeme& SNodeList::FirstLexeme() const
{
   if (!Count() || !lexeme.IsNone()) return lexeme;
   return front()->FirstLexeme();
}

TNode* SNode::Create(A_Syntax* syntax)
{ 
   TNode* ret = NULL;
   switch (type) {
   case stNull : {
      ret = new TNodeNull();
      } break;
   case stNumber : {
      ret = new TNodeNumber(lexeme);
      } break;
   case stVar : {
      ret = new TNodeVar(lexeme);
      } break;
   case stGoTo  : {
      ret = new TNodeUserGoTo(lexeme); 
      } break;
   case stBreak  : {
      ret = new TNodeBreakContinue(T_Block::tbBreak,lexeme);
      } break;
   case stContinue  : { 
      ret = new TNodeBreakContinue(T_Block::tbContinue,lexeme);
      } break;
   case stLabel : { 
      ret = new TNodeUserLabel(lexeme);
      } break;
   case stType : {
      ret = TBaseType::BaseType(lexeme,option);
      } break;
   default : 
      break;
   }

   return ret;
}

TNode* SNodeList::Create(A_Syntax* syntax)
{ 
   TNode* ret = NULL;
   switch (type) {
   case stUnary: {
      if (option) syntax->ChangeUnary(lexeme, false);
      ret = new TNodeUnary(lexeme, Child()->Create(syntax));
      } break;
   case stPrimary: {
      ret = new TNodePrimary(lexeme, Child()->Create(syntax));
      } break;
   case stCast: {
      TNodeType *type = syntax->BaseType(lexeme);
      TNodeCast *cast = new TNodeCast(lexeme, type, Child()->Create(syntax));
      ret = cast;
      } break;
   case stCall: {
      TNodeCall* call = new TNodeCall(lexeme);
      if (Child()) call->SetList((T_NodeList*)Child()->Create(syntax)); // params
      ret = call;
      } break;
   case stIndex: {
      TNodeIndex* index = new TNodeIndex(lexeme);
      if (Child()) index->SetList((T_NodeList*)Child()->Create(syntax)); // ranges
      ret = index;
      } break;
   case stReturn: {
      TNodeReturn* retur = new TNodeReturn(lexeme);
      if (Child())  retur->SetValue(Child()->Create(syntax));
      ret = retur;
      } break;
   case stSwitchCase: {
      } break;
   case stBinary: {
      if (lexeme.Match(T_Symbol::prOrOr) || lexeme.Match(T_Symbol::prAndAnd)) {
         ret = new TNodeLogical(lexeme, Left()->Create(syntax), Right()->Create(syntax));
      } else {
         ret = new TNodeBinary(lexeme, Left()->Create(syntax), Right()->Create(syntax));
      }
      } break;
   case stLogical: {
      ret = new TNodeLogical(lexeme, Left()->Create(syntax), Right()->Create(syntax));
      } break;
   case stWhile: {
      TNodeWhile* statement = new TNodeWhile(lexeme);
      if (Left())  statement->SetCondition(Left()->Create(syntax));
      if (Right()) statement->SetBody(Right()->Create(syntax));
      ret = statement;
      } break;
   case stDo: {
      TNodeDo* statement = new TNodeDo(lexeme);
      if (Left())  statement->SetCondition(Left()->Create(syntax));
      if (Right()) statement->SetBody(Right()->Create(syntax));
      ret = statement;
      } break;
   case stSwitchItem:
      break;
   case stSwitch:
      break;
   case stTrio: {
      ret = new TNodeTrio(lexeme, Left()->Create(syntax), Mid()->Create(syntax), Right()->Create(syntax));
      } break;
   case stDefVar: {
      TNodeDefVar* def = new TNodeDefVar(lexeme);
      if (Left())  def->SetType((TNodeType*)Left()->Create(syntax));
      if (Right()) def->SetAssign(syntax->oper_assign, Right()->Create(syntax));
      ret = def;
      } break;
   case stDefArr: {
      TNodeDefArr* def = new TNodeDefArr(lexeme, (T_NodeList*)Mid()->Create(syntax));
      if (Left())  def->SetType((TNodeType*)Left()->Create(syntax));
      if (Right()) def->SetAssign(Right()->Create(syntax));
      ret = def;
      } break;
   case stDefFunc: {
      TNodeDefFunc* def = new TNodeDefFunc(lexeme);
      if (Left())  def->SetType((TNodeType*)Left()->Create(syntax));
      if (Right()) def->SetParams((TNodeDefine*)Right()->Create(syntax));
      if (Mid())   def->SetBody(Mid()->Create(syntax));
      ret = def;
      } break;
   case stIf: {
      TNodeIf* statement = new TNodeIf(lexeme);
      if (Left())  statement->SetCondition(Left()->Create(syntax));
      if (Mid())   statement->SetThen(Mid()->Create(syntax));
      if (Right()) statement->SetElse(Right()->Create(syntax));
      ret = statement;
      } break;
   case stFor: {
      TNodeFor* statement = new TNodeFor(lexeme);
      if (Left())  statement->SetBeg(Left()->Create(syntax));
      if (Mid())   statement->SetCondition(Mid()->Create(syntax));
      if (Right()) statement->SetEnd(Right()->Create(syntax));
      if (Four())  statement->SetBody(Four()->Create(syntax));
      ret = statement;
      } break;
   case stExpressions :  {
      TNodeExpressions* expr = new TNodeExpressions();
      expr->part = (T_Part)option; 
      ret = expr;
      for (SNode *snode : *this) {
         if (TNode* node = snode->Create(syntax)) expr->Add(node);
      } 
      } break;
   case stStatements  :  {
      TNodeStatements* statement = new TNodeStatements();
      ret = statement;
      for (SNode *snode : *this) {
         if (TNode* node = snode->Create(syntax)) statement->Add(node);
      } 
      } break;
   case stList  :  {
      T_NodeList* list = new T_NodeList();
      ret = list;
      for (SNode *snode : *this) {
         if (TNode* node = snode->Create(syntax)) list->Add(node);
      } 
      } break;
   case stDefine : {
      TNodeType *define_type = NULL;
      TNodeDefine* define = NULL;
      if (!lexeme.IsNone()) {
         define_type = syntax->BaseType(lexeme, option);
         define = new TNodeDefine(define_type, lexeme);
      } else {
         define = new TNodeDefine();
      }
      for (SNode *snode : *this) {
         TNode* node = snode->Create(syntax);
         if (!node) continue;
         define->Add(node);
         if (!define_type) continue;
         if (snode->option & 0x08) { // reference
            define_type = TBaseType::Or(define_type, T_BaseType::btReference);
         }
         if (TNodeDefVar* var = dynamic_cast<TNodeDefVar*>(node)) {
            var->SetType(define_type);
         }
      } 
      ret = define;
      } break;
   default : 
      return ret;
   }

   return ret;
}

#define CHILD(R) SNode *child = (Count() > R) ? (*this)[R] : NULL;
#define LEFT(R)  SNode *left  = (Count() > R) ? (*this)[R] : NULL;
#define MID(R)   SNode *mid   = (Count() > R) ? (*this)[R] : NULL;
#define RIGHT(R) SNode *right = (Count() > R) ? (*this)[R] : NULL;
#define FOUR(R)  SNode *four  = (Count() > R) ? (*this)[R] : NULL;

TNode* SNodeList::Make(A_Syntax* syntax)
{
   TNode* ret = NULL;
   switch (type) {
   case stNull : {
      ret = new TNodeNull();
      } break;
   case stNumber : {
      ret = new TNodeNumber(lexeme);
      } break;
   case stVar : {
      ret = new TNodeVar(lexeme);
      } break;
   case stGoTo  : {
      ret = new TNodeUserGoTo(lexeme); 
      } break;
   case stBreak  : {
      ret = new TNodeBreakContinue(T_Block::tbBreak,lexeme);
      } break;
   case stContinue  : { 
      ret = new TNodeBreakContinue(T_Block::tbContinue,lexeme);
      } break;
   case stLabel : { 
      ret = new TNodeUserLabel(lexeme);
      } break;
   case stType : {
      ret = TBaseType::BaseType(lexeme,option);
      } break;
   case stUnary : {
      CHILD(0)
      if (option) syntax->ChangeUnary(lexeme,false);
      ret = new TNodeUnary(lexeme, child->Make(syntax));
      } break;
   case stIncDec : {
      CHILD(0)
      syntax->ChangeUnary(lexeme,false);
      ret = new TNodeUnary(lexeme, child->Make(syntax));
      } break;
   case stPrimary : {
      CHILD(0)
      ret = new TNodePrimary(lexeme, child->Make(syntax));
      } break;
   case stCast  : {
      CHILD(0)
      TNodeType *type = syntax->BaseType(lexeme);
      TNodeCast *cast = new TNodeCast(lexeme, type, child->Make(syntax));
      ret = cast;
      } break;
   case stCall  : {
      CHILD(0)
      TNodeCall* call = new TNodeCall(lexeme);
      if (child) call->SetList((T_NodeList*)child->Make(syntax)); // params
      ret = call;
      } break;
   case stIndex  : {
      CHILD(0)
      TNodeIndex* index = new TNodeIndex(lexeme);
      if (child) index->SetList((T_NodeList*)child->Make(syntax)); // ranges
      ret = index;
      } break;
   case stReturn : {
      CHILD(0)
      TNodeReturn* retur = new TNodeReturn(lexeme);
      if (child)  retur->SetValue(child->Make(syntax));
      ret = retur;
      } break;
   case stBinary  : {
      LEFT(0) RIGHT(1)
      if (lexeme.Match(T_Symbol::prOrOr) || lexeme.Match(T_Symbol::prAndAnd)) {
         ret = new TNodeLogical(lexeme,left->Make(syntax),right->Make(syntax));
      } else {
         ret = new TNodeBinary(lexeme,left->Make(syntax),right->Make(syntax));
      }
      } break;
   case stLogical  : {
      LEFT(0) RIGHT(1)
      ret = new TNodeLogical(lexeme,left->Make(syntax),right->Make(syntax));
      } break;
   case stWhile  : {
      LEFT(0) RIGHT(1)
      TNodeWhile* statement = new TNodeWhile(lexeme);
      if (left)  statement->SetCondition(left->Make(syntax));
      if (right) statement->SetBody(right->Make(syntax));
      ret = statement;
      } break;
   case stDo  : {
      LEFT(0) RIGHT(1)
      TNodeDo* statement = new TNodeDo(lexeme);
      if (left)  statement->SetCondition(left->Make(syntax));
      if (right) statement->SetBody(right->Make(syntax));
      ret = statement;
      } break;
   case stSwitchItem : 
      break;
   case stSwitch : 
      break;
   case stTrio  : {
      LEFT(0) MID(1) RIGHT(2)
      ret = new TNodeTrio(lexeme,left->Make(syntax),mid->Make(syntax),right->Make(syntax)); 
      } break;
   case stDefVar  : {
      LEFT(0) RIGHT(1)
      TNodeDefVar* def = new TNodeDefVar(lexeme);
      if (left) {
         TNode* node = left->Make(syntax);
         TNodeType *param_type = dynamic_cast<TNodeType*>(node);
         if (param_type) {
            def->SetType(param_type);
            if (right) def->SetAssign(right->Make(syntax));
         } else {
            def->SetAssign(syntax->oper_assign,node);
         }
      }
      ret = def;
      } break;
   case stDefArr  : {
      LEFT(0) MID(2) RIGHT(1)
      if (!left) break;
      TNode *node = left->Make(syntax), *assign = NULL;
      TNodeType *param_type = dynamic_cast<TNodeType*>(node);
      T_NodeList* ranges = NULL;
      if (!param_type) {
         ranges = (T_NodeList*)node;
         if (right) assign = right->Make(syntax); 
      } else {
         ranges = (T_NodeList*)right->Make(syntax);
         if (mid) assign = mid->Make(syntax); 
      }
      TNodeDefArr* def = new TNodeDefArr(lexeme,ranges);
      if (param_type) def->SetType(param_type);
      if (assign) def->SetAssign(assign);
      ret = def;
      } break;
   case stDefFunc : { 
      LEFT(0) MID(2) RIGHT(1)
      TNodeDefFunc* def = new TNodeDefFunc(lexeme);
      if (left)  def->SetType((TNodeType*)left->Make(syntax));
      if (right) def->SetParams((TNodeDefine*)right->Make(syntax));
      if (mid && (mid->type != stNull))   def->SetBody(mid->Make(syntax));
      ret = def;
      } break;
   case stIf : {
      LEFT(0) MID(1) RIGHT(2)
      TNodeIf* statement = new TNodeIf(lexeme);
      if (left)  statement->SetCondition(left->Make(syntax));
      if (mid)   statement->SetThen(mid->Make(syntax));
      if (right) statement->SetElse(right->Make(syntax));
      ret = statement;
      } break;
   case stFor : {
      LEFT(0) MID(1) RIGHT(2) FOUR(3)
      TNodeFor* statement = new TNodeFor(lexeme);
      if (left )  statement->SetBeg(left->Make(syntax));
      if (mid  )  statement->SetCondition(mid->Make(syntax));
      if (right)  statement->SetEnd(right->Make(syntax));
      if (four )  statement->SetBody(four->Make(syntax));
      ret = statement;
      } break;
   case stExpressions :  {
      TNodeExpressions* expr = new TNodeExpressions();
      expr->part = (T_Part)option; 
      for (SNode *snode : *this) {
         if (TNode* node = snode->Make(syntax)) expr->Add(node);
      } 
      ret = expr;
      } break;
   case stStatements  :  {
      T_NodeList* list = new TNodeStatements(); 
      for (SNode *snode : *this) {
         if (TNode* node = snode->Make(syntax)) list->Add(node);
      } 
      ret = list;
      } break;
   case stRanges : 
   case stList  :  {
      T_NodeList* list = new T_NodeList(); 
      for (SNode *snode : *this) {
         if (TNode* node = snode->Make(syntax)) list->Add(node);
      } 
      ret = list;
      } break;
   case stDefine : {
      TNodeType *define_type = NULL;
      TNodeDefine* define =  NULL;
      for (SNode *snode : *this) {
         if (!define) {
            if (snode->type == stType) {
               define_type = syntax->BaseType(snode->Lexeme(), option);
            }
            define =  new TNodeDefine(define_type, snode->Lexeme());
            if (define_type) continue;
         }
         TNode* node = snode->Make(syntax);
         if (!node) continue;
         TNodeDefVar* var = dynamic_cast<TNodeDefVar*>(node);
         if (var && define_type) {
            TNodeType *var_type = define_type;
            if (snode->option & 0x08) { // reference
               var_type = TBaseType::Or(var_type, T_BaseType::btReference);
            }
            var->SetType(var_type);
         }
         define->Add(node);
      } 
      ret = define;
      } break;
   default : 
      return ret;
   }
 
   return ret;
}

static const char* title_snode[] = {
   "None", "Node", "Unary", "Binary", "Logical", "Trio", "Number", "Primary", "Type", "Cast", "IncDec",
   "Expressions", "Compaund", "Statements", "DefVar", "DefArr", "DefFunc", "Define", "Var",
   "Call", "Index", "For", "While", "Do", "Label", "GoTo", "Break", "Continue", "Return", "If", 
   "SwitchCase", "SwitchItem", "Switch", "List", "Ranges", "Null", "NodeOne", "NodeTwo", "RefDef",
   "Lexeme", "Param", "Formula", "Produce", "Maker", "Tokens", "Enums", "Item"
   }; 
static const char* title_turn[] = { "None", "Push", "Put", "Add", "Make", "Down", "Up", "Swap", "Command" };
const char* snode_title(SNode::S_Type t) { return title_snode[t]; }
const char* snode_title(int t) { return snode_title((SNode::S_Type)t); }
const char*  turn_title(SNode::T_Turn t) { return title_turn[t]; }
SNode::S_Type title_snode_maker(const char* t) 
{
   int i = 0;
   for (const char* item : title_snode) {
      if (strcmp(item, t) == 0) return (SNode::S_Type)i;
      i++;
   }
   return SNode::S_Type::stNone;
}
SNode::T_Turn title_tnode_maker(const char* t) 
{
   int i = 0;
   for (const char* item : title_turn) {
      if (strcmp(item, t) == 0) return (SNode::T_Turn)i;
      i++;
   }
   return SNode::T_Turn::ttNone;
}

#include "Grammar.h"
// ------------------------- T_SyntaxNode ----------------------
void T_SyntaxNode::clear() {}

void TLexemeNode::clear() {}

void TProduceNode::clear()
{
   iterator p = begin();
   while (p != end()) {
      (*p)->clear();
      delete (*p);
      p = erase(p);
   }
   std::vector<T_SyntaxNode*> ::clear();
}

void TSyntaxTree::clear()
{
   if (root) {
      root->clear();
      delete root;
      root = NULL;
   }
}

T_SyntaxNode* TProduceNode::trim()
{
   if (empty()) return NULL;
   iterator p = begin();
   while (p != end()) {
      T_SyntaxNode* node = (*p)->trim();
      if (node) {
         node->child = (*p)->child;
         node->owner = this;
         delete (*p);
         (*p) = node;
      }
      p++;
   }
   if ((children == 1) && (size() == 1)) return front();
   
   if ((master == 1) && (size() == 2) && (front()->symbol == symbol)) {
      TProduceNode* list = (TProduceNode*)front();
      list->Add(back(), (int)list->size() + 1);
      back() = NULL; front() = NULL;
      return list;
   }
   
   return NULL;
}

void TSyntaxTree::trim()
{
   if (root) root->trim();
}

void TProduceNode::Add(T_SyntaxNode* node, int index)
{ 
   node->child = index;
   node->owner = this;
   push_back(node);
}

void TProduceNode::Insert(T_SyntaxNode* node, int index)
{
   node->child = index;
   node->owner = this;
   insert(begin(), node);
}

const char* T_SyntaxNode::title() const
{
   return symbol_title(symbol.type);
}

const char* TLexemeNode::title() const
{
   return T_SyntaxNode::title();
}

const char* TProduceNode::title() const
{
   return T_SyntaxNode::title();
}

T_SyntaxNode* TSyntaxTree::New(const GSymbol& type)
{
   T_SyntaxNode* ret = NULL;
   if (type.IsProduce()) {
      const GProduce produce = grammar->Produce(type);
      TProduceNode* node = new TProduceNode(type); 
      node->children = produce.Real(0x01); node->master = produce.Master(); // BNF(space == SYMBOL)
      ret = node;
   } else if (type.IsTerminal()) {
      if (type.IsSaved()) ret = new TLexemeNode(type);
   }
   return ret;
}

T_SyntaxNode* TSyntaxTree::New(const T_Lexeme& lexeme)
{
   T_SyntaxNode* ret = NULL;
   ret = new TLexemeNode(lexeme);
   return ret;
}

void TSyntaxTree::print(TPrinter& printer) const
{
   if (root) {
      printer.grammar = grammar;
      root->print(printer, 0);
   }
}

void T_SyntaxNode::print(TPrinter& printer, int level) const
{
   PRINTER_FILE_MODE_GRAMMAR
   print_offset(level, 0x01, file); 
   if (!(print_mode & T_OptionMode::omAutoNoDigit)) fprintf(file,"(%d)",child);
}

void TLexemeNode::print(TPrinter& printer, int level) const
{
   PRINTER_FILE_MODE_GRAMMAR
   T_SyntaxNode::print(printer, level);
   lexeme.print(printer, NULL);
}

void TProduceNode::print(TPrinter& printer, int level) const
{
   PRINTER_FILE_MODE_GRAMMAR
   T_SyntaxNode::print(printer, level);
   symbol.print(printer); 
   if (!(print_mode & T_OptionMode::omAutoNoDigit)) fprintf(file, "(%d,%d)", children, master);
   for (const T_SyntaxNode* node : (*this)) {
      node->print(printer, level + 1);
   }
}
