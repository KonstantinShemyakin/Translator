// --------------------- Tree ---------------------
MAKER_TREE(SaveLexeme)
{
   T_Lexeme::T_Group group = T_Lexeme::T_Group(item.MakerParam() >> 16);
   int type = item.MakerParam() & 0x0000FFFF;
   T_Lexeme lexeme(group,type);
   syntax->push_lexeme(lexeme);
   return true;
}

MAKER_TREE(Number)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   TNodeNumber *number = new TNodeNumber(lexeme);
   syntax->PushNode(number);
   return true;
}

MAKER_TREE(Ident)
{
   T_Lexeme lexeme;   
   const T_Lexeme& top = syntax->TopLexeme();
   bool change = (!top.Match(T_Lexeme::grIdent));
   if (change) {
      lexeme = syntax->PopLexeme();
   }
   T_Lexeme lexeme_ident = syntax->PopLexeme();
   TNodeVar *var = new TNodeVar(lexeme_ident);
   syntax->PushNode(var);
   if (change)  syntax->push_lexeme(lexeme);
   VARIABLES(var);
   return true;
}

MAKER_TREE(Label)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   T_NodeList *compaund = new T_NodeList();
	TNodeUserLabel* label = new TNodeUserLabel(lexeme);
   TNode *node = syntax->PopNode();
   compaund->Add(label);
   compaund->Add(node);
   syntax->PushNode(compaund);
   return true;
}

MAKER_TREE(Params)
{
   T_Lexeme lexeme = syntax->PopLexeme(); // IdentFunc
   T_NodeList *list;
   if (item.MakerParam()) {
      list = (T_NodeList*)syntax->PopNode(); // (params)
   } else {
      list = new T_NodeList(lexeme); // ()
   }
   TNodeCall *call = new TNodeCall(lexeme,list);
   syntax->PushNode(call);
   VARIABLES(call);
   return true;
}

MAKER_TREE(BegIndexLL)
{
   T_Lexeme lexeme = syntax->PopLexeme(); // IdentArr
   T_NodeList *list = new T_NodeList(lexeme);
   TNodeIndex *index = new TNodeIndex(lexeme,list);
   syntax->PushNode(index);
   return true;
}

MAKER_TREE(BegIndexLR)
{
   T_Lexeme lexeme = syntax->PopLexeme(); // IdentArr
   T_NodeList *list = new T_NodeList(lexeme);
   TNodeIndex *index = new TNodeIndex(lexeme, list);
   TNode *expr = syntax->PopNode();
   list->Add(expr);
   syntax->PushNode(index);
   return true;
}

MAKER_TREE(IndexLL)
{
   TNode *expr = syntax->PopNode();
   TNodeIndex *index = (TNodeIndex*)syntax->TopNode();
   T_NodeList *list = index->Ranges();
   list->Add(expr);
   return true;
}

MAKER_TREE(IndexLR)
{
   TNode *expr = syntax->PopNode();
   TNodeIndex *index = (TNodeIndex*)syntax->TopNode();
   T_NodeList *list = index->Ranges();
   list->Add(expr);
   return true;
}

MAKER_TREE(EndIndex)
{
   TNodeIndex *index = (TNodeIndex*)syntax->TopNode();
   VARIABLES(index);
   return true;
}

MAKER_TREE(Binary)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   TNode *right = syntax->PopNode(), *left = syntax->PopNode();
   TNode *binary;
   if (lexeme.Match(T_Symbol::prOrOr) || lexeme.Match(T_Symbol::prAndAnd)) {
      binary = new TNodeLogical(lexeme, left, right);
   } else {
      binary = new TNodeBinary(lexeme, left, right);
   }
   syntax->PushNode(binary);
   VARIABLES(binary);
   return true;
}

MAKER_TREE(Unary)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   syntax->ChangeUnary(lexeme,true);
   TNode *expr = syntax->PopNode();
   TNodeUnary *unary = new TNodeUnary(lexeme, expr);
   syntax->PushNode(unary);
   VARIABLES(unary);
   return true;
}

MAKER_TREE(IncDec)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   syntax->ChangeUnary(lexeme,false);
   TNode *expr = syntax->PopNode();
   TNodeUnary *unary = new TNodeUnary(lexeme, expr);
   syntax->PushNode(unary);
   VARIABLES(unary);
   return true;
}

MAKER_TREE(Primary) // Tree only
{
   T_Lexeme lexeme;
   TNode *expr = syntax->PopNode();
   TNodePrimary *primary = new TNodePrimary(lexeme, expr);
   syntax->PushNode(primary);
   VARIABLES(primary);
   return true;
}

MAKER_TREE(Cast)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   TNode *expr = syntax->PopNode();
   TNodeType *type = syntax->BaseType(lexeme);
   TNodeCast *cast = new TNodeCast(lexeme, type, expr);
   syntax->PushNode(cast);
   VARIABLES(cast);
   return true;
}

MAKER_TREE(Question)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   TNode *right = syntax->PopNode(), *left = syntax->PopNode(), *expr = syntax->PopNode();
   TNodeTrio *question = new TNodeTrio(lexeme, expr, left, right);
   syntax->PushNode(question);
   VARIABLES(question);
   return true;
}

MAKER_TREE(ExpressionsLL)
{
// stack: assign
   T_Lexeme lexeme;
   TNodeExpressions *expression = new TNodeExpressions(lexeme);
   TNode *expr = syntax->PopNode(); // assign
   expression->Add(expr);
   syntax->PushNode(expression);
// stack: expression
   return true;
}

MAKER_TREE(ExpressionsLR)
{
   // stack: assign
   T_Lexeme lexeme;
   TNodeExpressions *expression = new TNodeExpressions(lexeme);
   TNode *expr = syntax->PopNode(); // assign
   expression->Add(expr);
   syntax->PushNode(expression);
   // stack: expression
   return true;
}

MAKER_TREE(ExpressionSLL)
{
// stack: expression
   TNodeExpressions *expression = (TNodeExpressions*)syntax->TopNode();
   expression->part = T_Part(item.MakerParam());
   return true;
}

MAKER_TREE(ExpressionSLR)
{
   // stack: expression
   TNodeExpressions *expression = (TNodeExpressions*)syntax->TopNode();
   expression->part = T_Part(item.MakerParam());
   return true;
}

MAKER_TREE(DefParVar)
{
   T_Lexeme ident_lexeme = syntax->PopLexeme();
   T_Lexeme type_lexeme = syntax->PopLexeme();
   TNodeType *type = syntax->BaseType(type_lexeme);
   TNodeDefVar *param = new TNodeDefVar(type,ident_lexeme);
   syntax->PushNode(param);
   return true;
}

MAKER_TREE(DefParArr)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   T_Lexeme l = syntax->PopLexeme();
   TNodeType *type = syntax->BaseType(l);
   T_NodeList *list_range = new T_NodeList();
   TNodeDefArr *param = new TNodeDefArr(type,lexeme,list_range);
   syntax->PushNode(param);
   return true;
}

MAKER_TREE(ParVarAssign)
{
   T_Lexeme lexeme_assign = syntax->PopLexeme();
   TNode *assign = syntax->PopNode();
   TNodeDefVar *param = (TNodeDefVar*)syntax->TopNode();
   param->SetAssign(assign);
   return true;
}

MAKER_TREE(EndParams)
{
   TNodeDefine *params;
   if (item.MakerParam() <= 1) {
      params = (TNodeDefine*)syntax->PopNode();
   }
   TNodeDefFunc *func = (TNodeDefFunc*)syntax->TopNode();
   if (!func) return false;
   if (item.MakerParam() <= 1) {
      func->SetParams(params);
   }
   VARIABLES(func);
   return true;
}

MAKER_TREE(FuncIdent)
{
// lexemes: type, ident
   T_Lexeme lexeme_ident = syntax->PopLexeme();
   T_Lexeme lexeme_type = syntax->PopLexeme();
   TNodeType *type = syntax->BaseType(lexeme_type);
   TNodeDefFunc *func = new TNodeDefFunc(type,lexeme_ident,NULL,NULL);
   syntax->PushNode(func);
   return true;
}

MAKER_TREE(BodyFunc)
{
   if (item.MakerParam()) {
      TNode *body;
      if (item.MakerParam() == 0x02) {
         body = syntax->PopNode();
      } else {
         body = new TNodeStatements();
      }
      TNodeDefFunc *func = (TNodeDefFunc*)syntax->TopNode();
      func->SetBody(body);
   }
   return true;
}

MAKER_TREE(EndAInit)
{
   T_Lexeme lexeme_assign = syntax->PopLexeme();
   T_NodeList *list_init = dynamic_cast<T_NodeList*> (syntax->PopNode());
   if (!list_init) return false;
   TNodeDefArr *arr = (TNodeDefArr*)syntax->TopNode();
   arr->SetAssign(list_init);
   return true;
}

MAKER_TREE(DefArray)
{
   TNodeDefine *def = (TNodeDefine*)syntax->TopNode(); // top
   TNodeType *type_arr = def->Type();
   T_Lexeme lexeme = syntax->PopLexeme();
   T_NodeList *list_range = new T_NodeList();
   TNodeDefArr *arr = new TNodeDefArr(type_arr,lexeme,list_range);
   syntax->PushNode(arr);
   VARIABLES(arr);
   return true;
}

MAKER_TREE(DRange)
{
   TNode* expr = syntax->PopNode();
   TNodeDefArr *arr = (TNodeDefArr*)syntax->TopNode(); // top
   T_NodeList* range = arr->Range();
   range->Add(expr);
   return true;
}

MAKER_TREE(DefArrD1AEmpty)
{
   syntax->PushNode(new TNodeNull());
   return make_tree_DRange(item, syntax);
}

MAKER_TREE(DefIdent)
{
   TNodeDefine *def = (TNodeDefine*)syntax->TopNode(); // top
   TNodeType *type_ident = def->Type();
   T_Lexeme lexeme = syntax->PopLexeme();
   TNodeDefVar *var = new TNodeDefVar(type_ident,lexeme);
   syntax->PushNode(var);
   if (!lexeme.Match(T_Lexeme::grIdent)) {
      static int i_i = 0; i_i++;
   }
   return true;
}

MAKER_TREE(DefVarAssign)
{
   T_Lexeme lexeme_assign = syntax->PopLexeme();
   TNode* expr = syntax->PopNode();
   TNodeDefVar *var = (TNodeDefVar*)syntax->TopNode();
   var->SetAssign(lexeme_assign,expr);
   return true;
}

MAKER_TREE(PushDef) // Condition
{
// stack: define, def_var
   TNodeDefVar *def_var = (TNodeDefVar*)syntax->PopNode();
   T_NodeList *list = new T_NodeList();
   list->Add(def_var);
   T_Lexeme my_ident = def_var->Lexeme();
	TNodeVar *push_var = new TNodeVar(my_ident);
   list->Add(push_var);
   TNodeDefine *define = (TNodeDefine*)syntax->TopNode();
   define->Add(list);
// stack: define
   return true;
}

MAKER_TREE(RefDef)
{
   T_Lexeme lexeme_ref = syntax->PopLexeme();
   TNodeDefVar *var = (TNodeDefVar*)syntax->TopNode(); // var || arr
   TNodeType* type = var->Type();
   type = TBaseType::Or(type, T_BaseType::btReference);
   var->SetType(type);
   return true;
}

MAKER_TREE(DefType)
{
   int type = item.MakerParam();
   if (type & 0x08) syntax->PopLexeme(); // &
   T_Lexeme& l = syntax->TopLexeme();
   MakeDefType(l, type);
   return true;
}

MAKER_TREE(Define)
{
   if (item.MakerParam() == 0x02) { // DefParams
      TNodeDefine *define = new TNodeDefine();
      syntax->PushNode(define);
      return true;
   }
   T_Lexeme lexeme_type, lexeme_ident;
   bool close = !(syntax->syntax_lexeme & T_Grammar::slSyntax) && !item.MakerParam(); // NR
   if (close) {
      lexeme_ident = syntax->PopLexeme();
      lexeme_type  = syntax->PopLexeme();
      syntax->push_lexeme(lexeme_ident);
   } else {
      lexeme_type = syntax->PopLexeme();
   }
   TNodeType *type = syntax->BaseType(lexeme_type);
   TNodeDefine *define = new TNodeDefine(type, lexeme_type);
   syntax->PushNode(define);
   return true;
}

MAKER_TREE(BegDo)
{
   TNodeDo *cycle = new TNodeDo(syntax->forward);
   syntax->PushNode(cycle);
   VARIABLES(cycle);
   return true;
}

MAKER_TREE(Do)
{
   TNode* condition = syntax->PopNode();
   TNode* body = syntax->PopNode();
   TNodeDo *cycle = (TNodeDo*)syntax->TopNode();
   cycle->SetCondition(condition);
   cycle->SetBody(body);
   return true;
}

MAKER_TREE(BegWhile)
{
   TNodeWhile *cycle = new TNodeWhile(syntax->forward);
   syntax->PushNode(cycle);
   VARIABLES(cycle);
   return true;
}

MAKER_TREE(While)
{
   TNode* body = syntax->PopNode();
   TNode* condition = syntax->PopNode();
   TNodeWhile *cycle = (TNodeWhile*)syntax->TopNode();
   cycle->SetCondition(condition);
   cycle->SetBody(body);
   return true;
}

MAKER_TREE(BegFor)
{
   TNodeFor *cycle = new TNodeFor(syntax->forward);
   syntax->PushNode(cycle);
   VARIABLES(cycle);
   return true;
}

MAKER_TREE(For)
{
   TNode* body = syntax->PopNode(); // body
   TNode* postfix  = syntax->PopNode();// postfix
   TNode* condition = syntax->PopNode(); // condition
   TNode* prefix = syntax->PopNode(); // prefix
   TNodeFor *cycle = (TNodeFor*)syntax->TopNode();
   cycle->SetBeg(prefix);
   cycle->SetCondition(condition);
   cycle->SetEnd(postfix);
   cycle->SetBody(body);
   VARIABLES(cycle);
   return true;
}

MAKER_TREE(If)
{
   T_Lexeme lexeme;
   TNodeIf *statement = new TNodeIf(lexeme);
   if (item.MakerParam() != 0x00) {
      TNode* else_body = syntax->PopNode();
      statement->SetElse(else_body);
   } else {
      statement->SetElse(new TNodeNull()); 
   }
   TNode* then_body = syntax->PopNode();
   statement->SetThen(then_body);
   TNode* condition = syntax->PopNode();
   statement->SetCondition(condition);
   syntax->PushNode(statement);
   VARIABLES(statement);
   return true;
}

MAKER_TREE(GoTo)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   TNodeUserGoTo *statement = new TNodeUserGoTo(lexeme);
   syntax->PushNode(statement);
   VARIABLES(statement);
   return true;
}

MAKER_TREE(Break)
{
   TNodeBreakContinue *statement = new TNodeBreakContinue(T_Block::tbBreak, syntax->forward);
   syntax->PushNode(statement);
   VARIABLES(statement);
   return true;
}

MAKER_TREE(Continue)
{
   TNodeBreakContinue *statement = new TNodeBreakContinue(T_Block::tbContinue, syntax->forward);
   syntax->PushNode(statement);
   VARIABLES(statement);
   return true;
}

MAKER_TREE(Return)
{
   TNodeReturn *statement = new TNodeReturn(syntax->forward);
   if (item.MakerParam() != 0x00) {
      TNode *expr = syntax->PopNode();
      statement->SetValue(expr);
   }
   syntax->PushNode(statement);
   VARIABLES(statement);
   return true;
}

MAKER_TREE(BegStmExprLL)
{
   TNodeStatements *statements = new TNodeStatements();
   syntax->PushNode(statements);
   return true;
}

MAKER_TREE(BegStmExprLR)
{
   TNodeStatements *statements = new TNodeStatements();
   if (item.MakerParam() == 0x01) {
      TNode *node = syntax->PopNode();
      statements->Add(node);
   }
   syntax->PushNode(statements);
   return true;
}

MAKER_TREE(Compaund)
{
   TNodeStatements *statement = new TNodeStatements();
   syntax->PushNode(statement);
   return true;
}

MAKER_TREE(NodeNull)
{
   TNodeNull *null = new TNodeNull();
   syntax->PushNode(null);
   return true;
}

MAKER_TREE(NodeListLL)
{
   T_NodeList *list = new T_NodeList();
   syntax->PushNode(list);
   return true;
}

MAKER_TREE(NodeListLR)
{
   T_NodeList *list = new T_NodeList();
   if (item.MakerParam() != 0x00) {
      list->Add(syntax->PopNode());
   }
   syntax->PushNode(list);
   return true;
}

MAKER_TREE(AddToList)
{
   TNode *node = syntax->PopNode();
   T_NodeList *list = dynamic_cast<T_NodeList*> (syntax->TopNode()); // top
   if (!list) return false;
   list->Add(node);
   return true;
}
