#undef S0
#undef S1
#undef S2
#undef S3
#undef S4

#define S0 (*data_stack[0])
#define S1 (*data_stack[1])
#define S2 (*data_stack[2])
#define S3 (*data_stack[3])
#define S4 (*data_stack[4])

#undef ACTION
#define ACTION(MODE) ((syntax->option_mode & 0x0000000F) == A_Syntax::mm##MODE)

MAKER_YACC(DefType)
{
   int param = item.MakerParam();
   T_Lexeme_SNode* x;
   switch (param) {
   case 0x01 : x = data_stack[1    ]; break;
   case 0x03 : x = data_stack[1 + 1]; break;
   case 0x05 : x = data_stack[1 + 1]; break;
   case 0x07 : x = data_stack[1 + 2]; break;
   case 0x09 : x = data_stack[1    ]; break;
   case 0x0B : x = data_stack[1 + 1]; break;
   case 0x20 : x = data_stack[1    ]; break;
   case 0x24 : x = data_stack[1 + 1]; break;
   default : 
      x = data_stack[1    ];
      break;
   }
   MakeDefType(x->lexeme, param);
   if (ACTION(Node)) {
      SNode* node = new SNode(x->lexeme,SNode::stType);
      node->option = param;
      S0.node = node;
   } else if (ACTION(Made)) {
      S0.tree = TBaseType::BaseType(x->lexeme, param);
   }
   S0.lexeme = x->lexeme;
   return true;
}

bool make_yacc_ExpressionS(const GSymbol& item, M_Syntax* syntax, T_Lexeme_SNode* data_stack[])
{
   if (ACTION(Node)) {
      SNodeList* list = (SNodeList*)S1.node;
      list->option = item.MakerParam();
      S0.node = list;
   } else if (ACTION(Made)) {
      TNodeExpressions* expr = (TNodeExpressions*)S1.tree;
      expr->part = (T_Part)item.MakerParam();
      S0.tree = expr;
   }
return true;
}

MAKER_YACC(ExpressionSLL)
{
   return make_yacc_ExpressionS(item, syntax, data_stack);
}

MAKER_YACC(ExpressionSLR)
{
   return make_yacc_ExpressionS(item, syntax, data_stack);
}

MAKER_YACC(AddToList)
{
   if (ACTION(Node)) {
      SNodeList* list = NULL;
      if (item.MakerParam() == 0x05) { // LR
         list = (SNodeList*)S1.node;
         list->Add(S3.node);
         S0.node = list;
      } else if (item.MakerParam() == 0x03) { // LR
         list = (SNodeList*)S1.node;
         list->Add(S2.node);
         S0.node = list;
      } else if (item.MakerParam() == 0x02) { // LL
         list = (SNodeList*)S0.node;
         list->Add(S1.node);
      } else if (item.MakerParam() == 0x06) { // LL
         list = (SNodeList*)S0.node;
         list->Add(S1.node);
         S2.node = list;
      } else if (item.MakerParam() == 0x0A) { // LL
         list = (SNodeList*)S0.node;
         list->Add(S1.node);
         S3.node = list;
      }
   } else if (ACTION(Made)) {
      T_NodeList* list = NULL;
      if (item.MakerParam() == 0x05) { // LR
         list = (T_NodeList*)S1.tree;
         list->Add(S3.tree);
         S0.tree = list;
      } else if (item.MakerParam() == 0x03) { // LR
         list = (T_NodeList*)S1.tree;
         list->Add(S2.tree);
         S0.tree = list;
      } else if (item.MakerParam() == 0x02) { // LL
         list = (T_NodeList*)S0.tree;
         list->Add(S1.tree);
      } else if (item.MakerParam() == 0x06) { // LL
         list = (T_NodeList*)S0.tree;
         list->Add(S1.tree);
         S2.tree = list;
      } else if (item.MakerParam() == 0x0A) { // LL
         list = (T_NodeList*)S0.tree;
         list->Add(S1.tree);
         S3.tree = list;
      }
   }
   return true;
}

void tree_syn(int s, int &s1, int &s2, int &s3, int &s4, int &s5) 
{ 
   s1 = s & SYNTREE_MASK; s >>= SYNTREE_SHIFT;
   s2 = s & SYNTREE_MASK; s >>= SYNTREE_SHIFT;
   s3 = s & SYNTREE_MASK; s >>= SYNTREE_SHIFT;
   s4 = s & SYNTREE_MASK; s >>= SYNTREE_SHIFT;
   s5 = s & SYNTREE_MASK;
}

static T_Lexeme_SNode lexeme_node;
bool make_yacc_LL_SN(const GSymbol& item, M_Syntax* syntax, T_Lexeme_SNode* data_stack[])
{
   bool print_maker = ((syntax->option & 0x0200) != 0);
   SNode::S_Type type = (SNode::S_Type)item.maker;
   int param = item. MakerParam();
   int s1, s2, s3, s4, s5;
   tree_syn(item.point, s1, s2, s3, s4, s5);
   T_Lexeme_SNode *y1 = &lexeme_node, *y2 = &lexeme_node, *y3 = &lexeme_node, *y4 = &lexeme_node, *y5 = &lexeme_node;
   if (s1) y1 = data_stack[s1];
   if (s2) y2 = data_stack[s2];
   if (s3) y3 = data_stack[s3];
   if (s4) y4 = data_stack[s4];
   if (s5) y5 = data_stack[s5];
   T_Lexeme_SNode *lexeme = &S1;

   SNode* ret = NULL;
   switch (type) {
   case SNode::stNone  :  {
      if (param == 0) { // Copy
         ret = y1->node;
         if (s2) { y2->node = ret; }
      } else if (param == 1) {
         ret = y1->node;
         syntax->Tree(ret);
      } else if (param == 2) { // lexeme
         y1->lexeme = lexeme->lexeme;
      }
      } break;
   case SNode::stLabel : {
      SNode* label = new SNode(lexeme->lexeme,type);
      SNodeList* list = new SNodeList(lexeme_node.lexeme,SNode::stList);
      list->Add(label);
      list->Add(S1.node);
      ret = list;
      } break;
   case SNode::stGoTo :
   case SNode::stBreak :
   case SNode::stContinue : {
      ret = new SNode(lexeme->lexeme, type);
      if (lexeme->lexeme.IsNone()) ret->SetLexeme(syntax->last_key_word);
      } break;
   case SNode::stNull:
   case SNode::stNumber  :
   case SNode::stVar   : {
      ret = new SNode(lexeme->lexeme,type);
      } break;
   case SNode::stRefDef  : {
      y1->node->option = 0x08; // reference
      ret = y1->node;
      } break;
   case SNode::stCast  : {
      ret = new SNodeList(lexeme->lexeme,type,y1->node);
      } break;
   case SNode::stReturn: {
      ret = new SNodeList(lexeme->lexeme, type, y1->node);
      if (lexeme->lexeme.IsNone()) ret->SetLexeme(syntax->last_key_word);
      ret->option = param;
      } break;
   case SNode::stNodeOne :
   case SNode::stPrimary  : 
   case SNode::stCall  : 
   case SNode::stIndex  : { 
      ret = new SNodeList(lexeme->lexeme,type,y1->node);
      ret->option = param;
      } break;
   case SNode::stUnary  : {
      ret = new SNodeList(lexeme->lexeme,type,y1->node);
      ret->option = param;
      if (param == 1) {
         S0.node = ret;
      }
      } break;
   case SNode::stDo :
   case SNode::stWhile :
   case SNode::stNodeTwo : {
      if (param == 0) {
         ret = new SNodeList(lexeme->lexeme,type,y1->node,y2->node);
         S0.node = ret;
      } else if (param == 1) {
      }
      } break; 
   case SNode::stLogical : 
   case SNode::stBinary  : {
      ret = new SNodeList(lexeme->lexeme,type,y1->node,y2->node);
      if (s3) { y3->node = ret; }
      S0.node = ret;
      } break;
   case SNode::stTrio  : { // Question
      if (param == 0) {
         ret = new SNodeList(lexeme->lexeme,type,S0.node,S1.node,NULL);
         S0.node = ret;
      } else if (param == 1) {
         SNodeList *question = (SNodeList*)S0.node;
         question->SetRight(S1.node);
      }
      } break;
   case SNode::stFor  : {
      if (param == 0) { // prefix
         ret = new SNodeList(lexeme_node.lexeme,type,S1.node,NULL,NULL,NULL);
      } else if (param == 1) { // condition
         SNodeList* four = (SNodeList*)S0.node;
         four->SetMid(S1.node);
      } else if (param == 2) { // postfix
         SNodeList* four = (SNodeList*)S0.node;
         four->SetRight(S1.node);
      } else if (param == 3) { // body
         SNodeList* four = (SNodeList*)S0.node;
         four->SetFour(S1.node);
      }
      } break;
   case SNode::stRanges : {
      SNodeList* list;
      if (param == 2) { // create
         list = new SNodeList(lexeme->lexeme,SNode::stList);
         list->Add(y1->node);
      } else if (param == 3) { // add
         list = (SNodeList*)y2->node;
         list->Add(y3->node);
      } else if (param == 4) { // insert
         list = (SNodeList*)y2->node;
         list->Insert(0, y3->node);
      } else if (param == 1) { // ins(Null)
         list = (SNodeList*)y2->node;
         list->Insert(0, new SNode(lexeme_node.lexeme,SNode::stNull));
      } else { // Null
         list = new SNodeList(lexeme->lexeme,SNode::stList);
         list->Add(new SNode(lexeme_node.lexeme,SNode::stNull));
      }
      ret = list;
      } break;
   case SNode::stDefArr  : // (Lexeme,Type,Range,Assign), (,l,m,r)
   case SNode::stDefVar  : {
      if (param == 2) {
         SNodeList* def = (SNodeList*)y2->node; def->SetRight(y1->node); // (,Node,Assign)
         ret = def;
      } else {
         ret = new SNodeList(lexeme->lexeme,type,y1->node,y3->node,y2->node); // (Lexeme,Type,Range,Assign)
         S0.node = ret;
      }
      } break;
   case SNode::stDefFunc : {
      if (param == 0) { // Type
         SNode* type_node = new SNode(lexeme->lexeme,SNode::stType);
         SNodeList* func = new SNodeList(lexeme_node.lexeme,type,type_node,NULL,NULL);
         S0.node = func;
      } else if (param == 1) { // Ident
         SNodeList* func = (SNodeList*)S0.node;
         func->SetLexeme(lexeme->lexeme);
      } else if (param == 2) { // Params
         SNodeList* func = (SNodeList*)S0.node;
         func->SetRight(S1.node);
      } else if (param == 3) { // Body
         SNodeList* func = (SNodeList*)S0.node;
         func->SetMid(S1.node);
      }
      } break;
   case SNode::stDefine : {
      SNodeList* list = NULL;
      list = new SNodeList(lexeme->lexeme,type);
      if (param == 1) { // DefParams
         list->SetLexeme(T_Lexeme());
         list->Add(S1.node);
      }
      if (s1) { y1->node = list; }
      if (s2) { y2->node = list; }
      ret = list;
      } break;
   case SNode::stIf : {
      if (param == 0) { // condition
         ret = new SNodeList(lexeme->lexeme,type,y1->node,NULL,NULL);
      } else if (param == 1) { // then
         SNodeList* beg_if = (SNodeList*)S0.node;
         beg_if->SetMid(y1->node);
         ret = beg_if;
      } else { // else
         SNodeList* beg_if = (SNodeList*)S0.node;
         beg_if->SetRight(y1->node);
         ret = beg_if;
      }
      } break;
   case SNode::stList  : 
   case SNode::stExpressions :  
   case SNode::stStatements  : {
      SNodeList* list;
      list = new SNodeList(lexeme->lexeme,type);
      if (param == 1) {
         list->Add(S1.node);
         if ((type == SNode::stExpressions) && list->Lexeme().IsNone()) list->SetLexeme(S1.node->FirstLexeme());
      }
      if (s1) { y1->node = list; }
      if (s2) { y2->node = list; }
      ret = list;
      } break;
   default : 
      ret = NULL;
      break;
   }
   if (ret && !S0.node) {
      S0.node = ret;
   }
   return true;
}

bool make_yacc_LL_MD(const GSymbol& item, M_Syntax* syntax, T_Lexeme_SNode* data_stack[])
{
   SNode::S_Type type = (SNode::S_Type)item.maker;
   int param = item.MakerParam();
   int s1, s2, s3, s4, s5;
   tree_syn(item.point, s1, s2, s3, s4, s5);
   T_Lexeme_SNode *y1 = &lexeme_node, *y2 = &lexeme_node, *y3 = &lexeme_node, *y4 = &lexeme_node, *y5 = &lexeme_node;
   if (s1) y1 = data_stack[s1];
   if (s2) y2 = data_stack[s2];
   if (s3) y3 = data_stack[s3];
   if (s4) y4 = data_stack[s4];
   if (s5) y5 = data_stack[s5];
   T_Lexeme_SNode *lexeme = &S1;

   TNode* ret = NULL;
   switch (type) {
   case SNode::stNone: {
      if (param == 0) { // Copy
         ret = y1->tree;
         if (s2) { y2->tree = ret; }
      } else if (param == 1) {
         ret = y1->tree;
         syntax->Program(ret);
      } else if (param == 2) { // lexeme
         y1->lexeme = lexeme->lexeme;
      }
      } break;
   case SNode::stNull: {
      ret = new TNodeNull();
      } break;
   case SNode::stNumber: {
      ret = new TNodeNumber(lexeme->lexeme);
      } break;
   case SNode::stVar: {
      ret = new TNodeVar(lexeme->lexeme);
      } break;
   case SNode::stGoTo: {
      ret = new TNodeUserGoTo(lexeme->lexeme);
      if (lexeme->lexeme.IsNone()) ret->SetLexeme(syntax->last_key_word);
      } break;
   case SNode::stBreak: {
      ret = new TNodeBreakContinue(T_Block::tbBreak, lexeme->lexeme);
      if (lexeme->lexeme.IsNone()) ret->SetLexeme(syntax->last_key_word);
      } break;
   case SNode::stContinue: {
      ret = new TNodeBreakContinue(T_Block::tbContinue, lexeme->lexeme);
      if (lexeme->lexeme.IsNone()) ret->SetLexeme(syntax->last_key_word);
      } break;
   case SNode::stLabel: {
      TNodeUserLabel* label = new TNodeUserLabel(lexeme->lexeme);
      T_NodeList* list = new T_NodeList(lexeme_node.lexeme);
      list->Add(label);
      list->Add(S1.tree);
      ret = list;
      } break;
   case SNode::stRefDef: {
      TNodeDefVar *var = (TNodeDefVar*)y1->tree; // var || arr
      TNodeType* type = var->Type();
      if (type) {
         type = TBaseType::Or(type, T_BaseType::btReference);
         var->SetType(type);
      }
      var->referenced = true;
      ret = var;
      } break;
   case SNode::stCast: {
      TNodeType *type = syntax->BaseType(lexeme->lexeme);
      TNodeCast *cast = new TNodeCast(lexeme->lexeme, type, y1->tree);
      ret = cast;
      } break;
   case SNode::stPrimary: {
      ret = new TNodePrimary(lexeme->lexeme, y1->tree);
      } break;
   case SNode::stCall: {
      TNodeCall* call = new TNodeCall(lexeme->lexeme);
      if (y1->tree) call->SetList((T_NodeList*)y1->tree); // params
      ret = call;
      } break;
   case SNode::stIndex: {
      TNodeIndex* index = new TNodeIndex(lexeme->lexeme);
      if (y1->tree) index->SetList((T_NodeList*)y1->tree); // ranges
      ret = index;
      } break;
   case SNode::stReturn: {
      TNodeReturn* retur = new TNodeReturn(lexeme->lexeme);
      if (lexeme->lexeme.IsNone()) retur->SetLexeme(syntax->last_key_word);
      if (y1->tree) retur->SetValue(y1->tree);
      ret = retur;
      } break;
   case SNode::stUnary: {
      if (param) syntax->ChangeUnary(lexeme->lexeme, false);
      ret = new TNodeUnary(lexeme->lexeme, y1->tree);
      if (param) S0.tree = ret;
      } break;
   case SNode::stLogical:
   case SNode::stBinary: {
      if (lexeme->lexeme.Match(T_Symbol::prOrOr) || lexeme->lexeme.Match(T_Symbol::prAndAnd)) {
         ret = new TNodeLogical(lexeme->lexeme, y1->tree, y2->tree);
      } else {
         ret = new TNodeBinary(lexeme->lexeme, y1->tree, y2->tree);
      }
      if (s3) { y3->tree = ret; }
      S0.tree = ret;
      } break;
   case SNode::stWhile: {
      TNodeWhile* statement = new TNodeWhile(lexeme->lexeme);
      if (y1->tree) statement->SetCondition(y1->tree);
      if (y2->tree) statement->SetBody(y2->tree);
      ret = statement;
      S0.tree = ret;
      } break;
   case SNode::stDo: {
      TNodeDo* statement = new TNodeDo(lexeme->lexeme);
      if (y1->tree) statement->SetCondition(y1->tree);
      if (y2->tree) statement->SetBody(y2->tree);
      ret = statement;
      S0.tree = ret;
      } break;
   case SNode::stTrio: { // Question
      if (param == 0) {
         ret = new TNodeTrio(lexeme->lexeme, S0.tree, S1.tree, NULL);
         S0.tree = ret;
      } else if (param == 1) {
         TNodeTrio *question = (TNodeTrio*)S0.tree;
         question->SetRight(S1.tree);
      }
      } break;
   case SNode::stFor: {
      if (param == 0) { // prefix
         TNodeFor* statement = new TNodeFor(lexeme_node.lexeme);
         statement->SetBeg(S1.tree);
         ret = statement;
      } else if (param == 1) { // condition
         TNodeFor* statement = (TNodeFor*)S0.tree;
         statement->SetCondition(S1.tree);
      } else if (param == 2) { // postfix
         TNodeFor* statement = (TNodeFor*)S0.tree;
         statement->SetEnd(S1.tree);
      } else if (param == 3) { // body
         TNodeFor* statement = (TNodeFor*)S0.tree;
         statement->SetBody(S1.tree);
      }
      } break;
   case SNode::stIf: {
      if (param == 0) { // condition
         TNodeIf* statement = new TNodeIf(lexeme->lexeme);
         statement->SetCondition(y1->tree);
         ret = statement;
      } else if (param == 1) { // then
         TNodeIf* statement = (TNodeIf*)S0.tree;
         statement->SetThen(y1->tree);
      } else { // else
         TNodeIf* statement = (TNodeIf*)S0.tree;
         statement->SetElse(y1->tree);
      }
      } break;
   case SNode::stRanges: {
      T_NodeList* list;
      if (param == 2) { // create
         list = new T_NodeList(lexeme->lexeme);
         list->Add(y1->tree);
      } else if (param == 3) { // add
         list = (T_NodeList*)y2->tree;
         list->Add(y3->tree);
      } else if (param == 4) { // insert
         list = (T_NodeList*)y2->node;
         list->Insert(0, y3->tree);
      } else if (param == 1) { // ins(Null)
         list = (T_NodeList*)y2->tree;
         list->Insert(0, new TNodeNull());
      } else { // Null
         list = new T_NodeList(lexeme->lexeme);
         list->Add(new TNodeNull());
      }
      ret = list;
      } break;
   case SNode::stDefVar: {
      TNodeDefVar* def = new TNodeDefVar(lexeme->lexeme); // (Lexeme,Type,,Assign)
      if (y1->tree) def->SetType((TNodeType*)y1->tree);
      if (y2->tree) def->SetAssign(syntax->oper_assign, y2->tree);
      ret = def;
      S0.tree = ret;
      } break;
   case SNode::stDefArr: {
      if (param == 2) {
         TNodeDefArr* def = (TNodeDefArr*)y2->tree; // (,Node,Assign) 
         def->SetAssign(y1->tree);
         ret = def;
      } else {
         TNodeDefArr* def = new TNodeDefArr(lexeme->lexeme, (T_NodeList*)y3->tree); // (Lexeme,Type,Range,Assign)
         if (y1->tree) def->SetType((TNodeType*)y1->tree);
         if (y2->tree) def->SetAssign(y2->tree);
         ret = def;
         S0.tree = ret;
      }
      } break;
   case SNode::stDefFunc: {
      if (param == 0) { // Type
         TNodeType *type_node = syntax->BaseType(lexeme->lexeme);
         TNodeDefFunc* func = new TNodeDefFunc(type_node, lexeme_node.lexeme, NULL, NULL);
         S0.tree = func;
      } else if (param == 1) { // Ident
         TNodeDefFunc* func = (TNodeDefFunc*)S0.tree;
         func->SetLexeme(lexeme->lexeme);
      } else if (param == 2) { // Params
         TNodeDefFunc* func = (TNodeDefFunc*)S0.tree;
         func->SetParams((TNodeDefine*)S1.tree);
      } else if (param == 3) { // Body
         TNodeDefFunc* func = (TNodeDefFunc*)S0.tree;
         func->SetBody(S1.tree);
      }
      } break;
   case SNode::stDefine: {
      TNodeType *type_node = NULL;
      if (!param) { // DefParams
         type_node = syntax->BaseType(lexeme->lexeme);
      }
      TNodeDefine* define = new TNodeDefine(type_node, lexeme->lexeme);
      if (param == 1) { // DefParams
         if (s1) define->Add(y1->tree);
      }
      if (s1) { y1->tree = define; }
      if (s2) { y2->tree = define; }
      ret = define;
      } break;
   case SNode::stList: {
      T_NodeList* list;
      list = new T_NodeList(lexeme->lexeme);
      if (param == 1) {
         list->Add(S1.tree);
      }
      if (s1) { y1->tree = list; }
      if (s2) { y2->tree = list; }
      ret = list;
      } break;
   case SNode::stExpressions: {
      T_NodeList* list;
      list = new TNodeExpressions(lexeme->lexeme);
      if (param == 1) {
         list->Add(S1.tree);
         list->SetLexeme(S1.tree->FirstLexeme());
      }
      if (s1) { y1->tree = list; }
      if (s2) { y2->tree = list; }
      ret = list;
      } break;
   case SNode::stStatements: {
      T_NodeList* list;
      list = new TNodeStatements();
      if (param == 1) {
         list->Add(S1.tree);
      }
      if (s1) { y1->tree = list; }
      if (s2) { y2->tree = list; }
      ret = list;
      } break;
   default:
      ret = NULL;
      break;
   }
   if (ret && !S0.tree) {
      S0.tree = ret;
   }
   return true;
}

bool make_yacc_LL_MK(const GSymbol& item, M_Syntax* syntax, T_Lexeme_SNode* data_stack[])
{
   SNode::S_Type type = (SNode::S_Type)item.maker;
   int param = item.MakerParam();
   int s1, s2, s3, s4, s5;
   tree_syn(item.point, s1, s2, s3, s4, s5);
   T_Lexeme_SNode *y1 = &lexeme_node, *y2 = &lexeme_node, *y3 = &lexeme_node, *y4 = &lexeme_node, *y5 = &lexeme_node;
   if (s1) y1 = data_stack[s1];
   if (s2) y2 = data_stack[s2];
   if (s3) y3 = data_stack[s3];
   if (s4) y4 = data_stack[s4];
   if (s5) y5 = data_stack[s5];
   T_Lexeme_SNode *lexeme = &S1;

   TNode* ret = NULL;
   switch (type) {
   case SNode::stNone: {
      if (param == 0) { // Copy
         ret = y1->tree;
         if (s2) { y2->tree = ret; }
      } else if (param == 1) {
         ret = y1->tree;
         syntax->Program(ret);
      } else if (param == 2) { // lexeme
         y1->lexeme = lexeme->lexeme;
      }
      } break;
   case SNode::stNull: {
      ret = new TNodeNull();
      } break;
   case SNode::stNumber: {
      ret = new TNodeNumber(lexeme->lexeme);
      } break;
   case SNode::stVar: {
      ret = new TNodeVar(lexeme->lexeme);
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stGoTo: {
      ret = new TNodeUserGoTo(lexeme->lexeme);
      if (lexeme->lexeme.IsNone()) ret->SetLexeme(syntax->last_key_word);
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stBreak: {
      ret = new TNodeBreakContinue(T_Block::tbBreak, lexeme->lexeme);
      if (lexeme->lexeme.IsNone()) ret->SetLexeme(syntax->last_key_word);
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stContinue: {
      ret = new TNodeBreakContinue(T_Block::tbContinue, lexeme->lexeme);
      if (lexeme->lexeme.IsNone()) ret->SetLexeme(syntax->last_key_word);
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stLabel: {
      TNodeUserLabel* label = new TNodeUserLabel(lexeme->lexeme);
      ret = label;
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stRefDef: {
      TNodeDefVar *var = (TNodeDefVar*)y1->tree; // var || arr
      TNodeType* type = var->Type();
      if (type) {
         type = TBaseType::Or(type, T_BaseType::btReference);
         var->SetType(type);
      }
      var->referenced = true;
      ret = var;
      } break;
   case SNode::stCast: {
      TNodeType *type = syntax->BaseType(lexeme->lexeme);
      TNodeCast *cast = new TNodeCast(lexeme->lexeme, type, y1->tree);
      ret = cast;
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stPrimary: {
      ret = new TNodePrimary(lexeme->lexeme, y1->tree);
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stCall: {
      TNodeCall* call = new TNodeCall(lexeme->lexeme);
      if (y1->tree) call->SetList((T_NodeList*)y1->tree); // params
      ret = call;
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stIndex: {
      TNodeIndex* index = new TNodeIndex(lexeme->lexeme);
      if (y1->tree) index->SetList((T_NodeList*)y1->tree); // ranges
      ret = index;
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stReturn: {
      TNodeReturn* retur = new TNodeReturn(lexeme->lexeme);
      if (lexeme->lexeme.IsNone()) retur->SetLexeme(syntax->last_key_word);
      if (y1->tree)  retur->SetValue(y1->tree);
      ret = retur;
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stUnary: {
      if (param) syntax->ChangeUnary(lexeme->lexeme, false);
      ret = new TNodeUnary(lexeme->lexeme, y1->tree);
      if (param) S0.tree = ret;
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stLogical:
   case SNode::stBinary: {
      if (lexeme->lexeme.Match(T_Symbol::prOrOr) || lexeme->lexeme.Match(T_Symbol::prAndAnd)) {
         ret = new TNodeLogical(lexeme->lexeme, y1->tree, y2->tree);
      } else {
         ret = new TNodeBinary(lexeme->lexeme, y1->tree, y2->tree);
      }
      if (s3) { y3->tree = ret; }
      S0.tree = ret;
      VARIABLES_STEP(ret, All)
      } break;
   case SNode::stWhile: {
      TNodeWhile* statement;
      if (param == -1) {
         statement = new TNodeWhile(lexeme->lexeme);
         VARIABLES_STEP(statement, Begin)
         ret = statement;
      } else if (param == 0) {
         statement = (TNodeWhile*)S0.tree;
         if (y1->tree) statement->SetCondition(y1->tree);
         VARIABLES_STEP(statement, Condition)
      } else if (param == 1) {
         statement = (TNodeWhile*)S0.tree;
         if (y1->tree) statement->SetBody(y1->tree);
         VARIABLES_STEP(statement, Body)
      } else if (param == -2) {
         statement = (TNodeWhile*)S0.tree;
         VARIABLES_STEP(statement, End)
      }
      } break;
   case SNode::stDo: {
      TNodeDo* statement;
      if (param == -1) {
         statement = new TNodeDo(lexeme->lexeme);
         VARIABLES_STEP(statement, Begin)
         ret = statement;
      }  else if (param == 1) {
         statement = (TNodeDo*)S0.tree;
         if (y1->tree) statement->SetBody(y1->tree);
         VARIABLES_STEP(statement, Body)
      } else if (param == 0) {
         statement = (TNodeDo*)S0.tree;
         if (y1->tree) statement->SetCondition(y1->tree);
         VARIABLES_STEP(statement, Condition)
      } else if (param == -2) {
         statement = (TNodeDo*)S0.tree;
         VARIABLES_STEP(statement, End)
      }
      } break;
   case SNode::stTrio: { // Question
      if (param == 0) {
         ret = new TNodeTrio(lexeme->lexeme, S0.tree, S1.tree, NULL);
         S0.tree = ret;
      } else if (param == 1) {
         TNodeTrio *question = (TNodeTrio*)S0.tree;
         question->SetRight(S1.tree);
         VARIABLES_STEP(question,All);
      }
      } break;
   case SNode::stFor: {
      TNodeFor* statement = NULL;
      if (param == -1) {
         statement = new TNodeFor(lexeme_node.lexeme);
         VARIABLES_STEP(statement, Begin)
         ret = statement;
      } else if (param == 0) { // prefix
         statement = (TNodeFor*)S0.tree;
         statement->SetBeg(S1.tree);
         ret = statement;
      } else if (param == 1) { // condition
         statement = (TNodeFor*)S0.tree;
         statement->SetCondition(S1.tree);
      } else if (param == 2) { // postfix
         statement = (TNodeFor*)S0.tree;
         statement->SetEnd(S1.tree);
         VARIABLES_STEP(statement, ForTitle)
      } else if (param == 3) { // body
         statement = (TNodeFor*)S0.tree;
         statement->SetBody(S1.tree);
         VARIABLES_STEP(statement, Body);
      } else if (param == -2) {
         statement = (TNodeFor*)S0.tree;
         VARIABLES_STEP(statement, End)
      }
      } break;
   case SNode::stIf: {
      if (param == -1) {
         TNodeIf* statement = new TNodeIf(lexeme->lexeme);
         VARIABLES_STEP(statement, Begin)
         ret = statement;
      } else if (param == 0) { // condition
         TNodeIf* statement = (TNodeIf*)S0.tree;
         statement->SetCondition(y1->tree);
         VARIABLES_STEP(statement, Condition)
      } else if (param == 1) { // then
         TNodeIf* statement = (TNodeIf*)S0.tree;
         statement->SetThen(y1->tree);
         VARIABLES_STEP(statement, IfThen)
      } else { // else
         TNodeIf* statement = (TNodeIf*)S0.tree;
         statement->SetElse(y1->tree);
         VARIABLES_STEPS(statement, IfElse, IfLabel, End,)
      }
      } break;
   case SNode::stRanges: {
      T_NodeList* list;
      if (param == 2) { // create
         list = new T_NodeList(lexeme->lexeme);
         list->Add(y1->tree);
      } else if (param == 3) { // add
         list = (T_NodeList*)y2->tree;
         list->Add(y3->tree);
      } else if (param == 4) { // insert
         list = (T_NodeList*)y2->node;
         list->Insert(0, y3->tree);
      } else if (param == 1) { // ins(Null)
         list = (T_NodeList*)y2->tree;
         list->Insert(0, new TNodeNull());
      } else { // Null
         list = new T_NodeList(lexeme->lexeme);
         list->Add(new TNodeNull());
      }
      ret = list;
      } break;
   case SNode::stDefVar: {
      TNodeDefVar* def = new TNodeDefVar(lexeme->lexeme); // (Lexeme,Type,,Assign)
      TNodeType *type_node = NULL;
      if (y1->tree) {
         type_node = (TNodeType*)y1->tree;
      } else {
         type_node = syntax->data->semantic->type_node;
      }
      def->SetType(type_node);
      if (y2->tree) def->SetAssign(syntax->oper_assign, y2->tree, SYNTAX_MODE(Phase, TwoPhase) ? syntax->data->semantic : NULL);
      ret = def;
      S0.tree = ret;
      VARIABLES_STEP(ret,All);
      } break;
   case SNode::stDefArr: {
      if (param == 2) {
         TNodeDefArr* def = (TNodeDefArr*)y2->tree; // (,Node,Assign) 
         def->SetAssign(y1->tree);
         ret = def;
         VARIABLES_STEP(ret,DefArrAssign);
      } else {
         TNodeDefArr* def = new TNodeDefArr(lexeme->lexeme, (T_NodeList*)y3->tree); // (Lexeme,Type,Range,Assign)
         TNodeType *type_node = NULL;
         if (y1->tree) {
            type_node = (TNodeType*)y1->tree;
         } else {
            type_node = syntax->data->semantic->type_node;
         }
         def->SetType(type_node);
         if (y2->tree) def->SetAssign(y2->tree);
         ret = def;
         S0.tree = ret;
         VARIABLES_STEP(ret, Begin);
      }
      } break;
   case SNode::stDefFunc: {
      if (param == 0) { // Type
         TNodeType *type_node = syntax->BaseType(lexeme->lexeme);
         TNodeDefFunc* func = new TNodeDefFunc(type_node, lexeme_node.lexeme, NULL, NULL);
         S0.tree = func;
         VARIABLES_STEP(func,Begin)
      } else if (param == 1) { // Ident
         TNodeDefFunc* func = (TNodeDefFunc*)S0.tree;
         func->SetLexeme(lexeme->lexeme);
      } else if (param == 2) { // Params
         TNodeDefFunc* func = (TNodeDefFunc*)S0.tree;
         func->SetParams((TNodeDefine*)S1.tree);
         VARIABLES_STEP(func, Param)
      } else if (param == 3) { // Body
         TNodeDefFunc* func = (TNodeDefFunc*)S0.tree;
         func->SetBody(S1.tree);
         VARIABLES_STEP(func, Body)
         VARIABLES_STEP(func, End)
         }
      } break;
   case SNode::stDefine: {
      TNodeDefine* define = NULL;
      if (param <= 1) {
         TNodeType *type_node = NULL;
         if (!param) { // Define
            type_node = syntax->BaseType(lexeme->lexeme);
            syntax->data->semantic->type_node = type_node;
         }
         define = new TNodeDefine(type_node, lexeme->lexeme);
         if (param == 1) { // DefParams
            if (s1) define->Add(y1->tree);
         } else {
            if (s1) { y1->tree = define; }
         }
         if (s2) { y2->tree = define; }
      } else { // EndDefine
         define = (TNodeDefine*)S0.tree;
         syntax->data->semantic->type_node = NULL;
         VARIABLES_STEP(define,All);
      }
      ret = define;
      } break;
   case SNode::stList: {
      T_NodeList* list;
      list = new T_NodeList(lexeme->lexeme);
      if (param == 1) {
         list->Add(S1.tree);
      }
      if (s1) { y1->tree = list; }
      if (s2) { y2->tree = list; }
      ret = list;
      } break;
   case SNode::stExpressions: {
      T_NodeList* list;
      list = new TNodeExpressions(lexeme->lexeme);
      if (param == 1) {
         list->Add(S1.tree);
         list->SetLexeme(S1.tree->FirstLexeme());
      }
      if (s1) { y1->tree = list; }
      if (s2) { y2->tree = list; }
      ret = list;
      } break;
   case SNode::stStatements: {
      TNodeStatements* list = NULL;
      if (param >= 0) {
         list = new TNodeStatements();
         if (s1) { y1->tree = list; }
         if (s2) { y2->tree = list; }
         ret = list;
         VARIABLES_STEP(list, Begin)
      } else if (param == -2) {
         list = (TNodeStatements*)S0.tree;
         VARIABLES_STEP(list, End)
      }
      } break;
   default:
      ret = NULL;
      break;
   }
   if (ret && !S0.tree) {
      S0.tree = ret;
   }
   return true;
}

bool make_yacc_LR_SN(const GSymbol& item, M_Syntax* syntax, T_Lexeme_SNode* data_stack[])
{
   SNode::S_Type type = (SNode::S_Type)item.maker;
   int param = item. MakerParam();
   int s1, s2, s3, s4, s5;
   tree_syn(item.point, s1, s2, s3, s4, s5);
   T_Lexeme_SNode *y1 = &lexeme_node, *y2 = &lexeme_node, *y3 = &lexeme_node, *y4 = &lexeme_node, *y5 = &lexeme_node;
   if (s1) { y1 = data_stack[s1]; if (!y1) return false; }
   if (s2) { y2 = data_stack[s2]; if (!y2) return false; }
   if (s3) { y3 = data_stack[s3]; if (!y3) return false; }
   if (s4) { y4 = data_stack[s4]; if (!y4) return false; }
   if (s5) { y5 = data_stack[s5]; if (!y5) return false; }
   T_Lexeme_SNode *lexeme = y1;
   if (!lexeme) { lexeme = &lexeme_node; }

   SNode* ret = NULL;
   switch (type) {
   case SNode::stNone  :  {
      ret = y1->node;
      if (param) syntax->Tree(ret);
      } break;
   case SNode::stNull :
   case SNode::stGoTo :
   case SNode::stLabel :
   case SNode::stBreak :
   case SNode::stContinue :
   case SNode::stNumber  :  
   case SNode::stVar  :  {
      ret = new SNode(lexeme->lexeme,type);
      } break;
   case SNode::stRefDef  : {
      y2->node->option = 0x08; // reference
      ret = y2->node;
      } break;
   case SNode::stCast  : {
      ret = new SNodeList(lexeme->lexeme,type,y2->node);
      } break;
   case SNode::stReturn  : {
      if (!param) {
         ret = new SNodeList(lexeme->lexeme, type, y2->node);
      } else if (param == 1) {
         ret = (SNodeList*)y2->node;
         ret->SetLexeme(lexeme->lexeme);
      }
      } break;
   case SNode::stNodeOne :
   case SNode::stPrimary  : 
   case SNode::stCall  : 
   case SNode::stIndex  : 
   case SNode::stUnary  : {
      ret = new SNodeList(lexeme->lexeme,type,y2->node);
      ret->option = param;
      } break;
   case SNode::stDo :
   case SNode::stWhile :
   case SNode::stNodeTwo :
   case SNode::stLogical : 
   case SNode::stBinary  : {
      ret = new SNodeList(lexeme->lexeme,type,y2->node,y3->node);
      ret->option = param;
      } break;
   case SNode::stTrio  : {
      ret = new SNodeList(lexeme->lexeme,type,y2->node,y3->node,y4->node);
      } break;
   case SNode::stFor  : {
      ret = new SNodeList(lexeme->lexeme,type,y2->node,y3->node,y4->node,y5->node);
      } break;
   case SNode::stRanges : {
      SNodeList* list;
      if (param == 2) { // create
         list = new SNodeList(lexeme->lexeme,SNode::stList);
         list->Add(y2->node);
      } else if (param == 3) { // add
         list = (SNodeList*)y2->node;
         list->Add(y3->node);
      } else if (param == 4) { // insert
         list = (SNodeList*)y2->node;
         list->Insert(0, y3->node);
      } else if (param == 1) { // ins(Null)
         list = (SNodeList*)y2->node;
         list->Insert(0, new SNode(lexeme_node.lexeme,SNode::stNull));
      } else { // Null
         list = new SNodeList(lexeme->lexeme,SNode::stList);
         list->Add(new SNode(lexeme_node.lexeme,SNode::stNull));
      }
      ret = list;
      } break;
   case SNode::stDefArr  : // (Lexeme,Type,Range,Assign), (,l,m,r)
   case SNode::stDefVar  : {
      if (param == 2) {
         SNodeList* def = (SNodeList*)y2->node; def->SetRight(y3->node); // (,Node,Assign)
         ret = def;
      } else {
         ret = new SNodeList(lexeme->lexeme,type,y2->node,y4->node,y3->node); // (Lexeme,Type,Range,Assign)
      }
      } break;
   case SNode::stDefFunc : {
      if (param == 0) {
         SNodeList* func = new SNodeList(lexeme->lexeme, type, y2->node, NULL, NULL);
         SNodeList* par_body = (SNodeList*)y3->node;
         SNode* par = par_body->Left(); SNodeList *body = (SNodeList*)par_body->Right();
         if (body->option == 1) {
            func->SetMid(new SNodeList(lexeme_node.lexeme, SNode::stStatements));
         } else if (body->option == 2) {
            body->Child()->SetOwner(NULL);
            func->SetMid(body->Child());
         }
         par->SetOwner(NULL);
         func->SetRight(par);
//         par_body->clear();
         ret = func;
      }
      } break;
   case SNode::stDefine : { // ((,Type,First,Tail),1)    ((,Type,First),0)
      SNodeList* list = NULL;
      if (param == 1) {
         list = (SNodeList*)y4->node;
         if (list) {
            list->SetLexeme(y2->lexeme);
            list->type = type;
         }
      } 
      if (!list) {
         T_Lexeme *my_lexeme = y2 ? &y2->lexeme : &lexeme->lexeme;
         list = new SNodeList(*my_lexeme,type);
      }
      if (s3 && y3->node) { list->Insert(0,y3->node); }
      if (s2) list->option = y2->node->option;
//      y2->node->clear();
      ret = list;
      } break;
   case SNode::stIf : {
      if (param) {
         SNodeList* beg_if = (SNodeList*)y2->node;
         beg_if->SetRight(y3->node);
         ret = beg_if;
      } else {
         ret = new SNodeList(lexeme->lexeme,type,y2->node,y3->node,y4->node);
      }
      } break;
   case SNode::stList  : 
   case SNode::stExpressions :  
   case SNode::stCompaund  : 
   case SNode::stStatements  : {
      SNodeList* list;
      if (param) {
         list = (SNodeList*)y3->node; // ((,node,list),1) - add
      } else {
         list = new SNodeList(lexeme->lexeme,type); // ((lexeme,node),0) - create + add
      }
      if (s2 && y2->node) { 
         list->Add(y2->node); 
         if ((type == SNode::stExpressions) && list->Lexeme().IsNone()) list->SetLexeme(y2->node->FirstLexeme());
      }
      ret = list;
      } break;
   default : 
      ret = NULL;
      break;
   }
   S0.node = ret;
   return true;
}

bool make_yacc_LR_MD(const GSymbol& item, M_Syntax* syntax, T_Lexeme_SNode* data_stack[])
{
   SNode::S_Type type = (SNode::S_Type)item.maker;
   int param = item.MakerParam();
   int s1, s2, s3, s4, s5;
   tree_syn(item.point, s1, s2, s3, s4, s5);
   T_Lexeme_SNode *y1 = &lexeme_node, *y2 = &lexeme_node, *y3 = &lexeme_node, *y4 = &lexeme_node, *y5 = &lexeme_node;
   if (s1) { y1 = data_stack[s1]; if (!y1) return false; }
   if (s2) { y2 = data_stack[s2]; if (!y2) return false; }
   if (s3) { y3 = data_stack[s3]; if (!y3) return false; }
   if (s4) { y4 = data_stack[s4]; if (!y4) return false; }
   if (s5) { y5 = data_stack[s5]; if (!y5) return false; }
   T_Lexeme_SNode *lexeme = y1;
   if (!lexeme) { lexeme = &lexeme_node; }

   TNode* ret = NULL;
   switch (type) {
   case SNode::stNone: {
      ret = y1->tree;
      if (param) {
         syntax->Program(ret);
      }
      } break;
   case SNode::stNull: {
      ret = new TNodeNull();
      } break;
   case SNode::stNumber: {
      ret = new TNodeNumber(lexeme->lexeme);
      } break;
   case SNode::stVar: {
      ret = new TNodeVar(lexeme->lexeme);
      VARIABLES(ret);
      } break;
   case SNode::stGoTo: {
      ret = new TNodeUserGoTo(lexeme->lexeme);
      } break;
   case SNode::stBreak: {
      ret = new TNodeBreakContinue(T_Block::tbBreak, lexeme->lexeme);
      } break;
   case SNode::stContinue: {
      ret = new TNodeBreakContinue(T_Block::tbContinue, lexeme->lexeme);
      } break;
   case SNode::stLabel: {
      ret = new TNodeUserLabel(lexeme->lexeme);
      } break;
   case SNode::stRefDef: {
      TNodeDefVar *var = (TNodeDefVar*)y2->tree; // var || arr
      TNodeType* type = var->Type();
      if (type) {
         type = TBaseType::Or(type, T_BaseType::btReference);
         var->SetType(type);
      }
      var->referenced = true;
      ret = var;
      } break;
   case SNode::stCast: {
      TNodeType *type = syntax->BaseType(lexeme->lexeme);
      TNodeCast *cast = new TNodeCast(lexeme->lexeme, type, y2->tree);
      ret = cast;
      VARIABLES(ret);
      } break;
   case SNode::stUnary: {
      if (param) syntax->ChangeUnary(lexeme->lexeme, false);
      ret = new TNodeUnary(lexeme->lexeme, y2->tree);
      VARIABLES(ret);
      } break;
   case SNode::stPrimary: {
      ret = new TNodePrimary(lexeme->lexeme, y2->tree);
      VARIABLES(ret);
      } break;
   case SNode::stCall: {
      TNodeCall* call = new TNodeCall(lexeme->lexeme);
      if (y2->tree) call->SetList((T_NodeList*)y2->tree); // params
      ret = call;
      S_Syntax *g_syntax = dynamic_cast<S_Syntax*> (syntax);
      VARIABLES(ret);
      } break;
   case SNode::stIndex: {
      TNodeIndex* index = new TNodeIndex(lexeme->lexeme);
      if (y2->tree) index->SetList((T_NodeList*)y2->tree); // ranges
      ret = index;
      VARIABLES(ret);
      } break;
   case SNode::stReturn: {
      if (!param) {
         TNodeReturn* retur = new TNodeReturn(lexeme->lexeme);
         if (y2->tree)  retur->SetValue(y2->tree);
         ret = retur;
      } else if (param == 1) {
         ret = (TNodeReturn*)y2->tree;
         ret->SetLexeme(lexeme->lexeme);
         VARIABLES(ret);
      }
      } break;
   case SNode::stBinary: {
      if (lexeme->lexeme.Match(T_Symbol::prOrOr) || lexeme->lexeme.Match(T_Symbol::prAndAnd)) {
         ret = new TNodeLogical(lexeme->lexeme, y2->tree, y3->tree);
      } else {
         ret = new TNodeBinary(lexeme->lexeme, y2->tree, y3->tree);
      }
      VARIABLES(ret);
      } break;
   case SNode::stNodeOne: {
      TNode* body = y2->tree;
      if (param == 1) body = new TNodeNull(); // 0 - ; 1 - {} 2 - {...}
      ret = body; // Body
      } break;
   case SNode::stNodeTwo: {
      ret = new TNodeBinary(lexeme->lexeme, y2->tree, y3->tree); // Param_Body
      } break;
   case SNode::stLogical: {
      ret = new TNodeLogical(lexeme->lexeme, y2->tree, y3->tree);
      } break;
   case SNode::stWhile: {
      TNodeWhile* statement = new TNodeWhile(lexeme->lexeme);
      if (y2->tree) statement->SetCondition(y2->tree);
      if (y3->tree) statement->SetBody(y3->tree);
      ret = statement;
      } break;
   case SNode::stDo: {
      TNodeDo* statement = new TNodeDo(lexeme->lexeme);
      if (y2->tree) statement->SetCondition(y2->tree);
      if (y3->tree) statement->SetBody(y3->tree);
      ret = statement;
      } break;
   case SNode::stTrio: {
      ret = new TNodeTrio(lexeme->lexeme, y2->tree, y3->tree, y4->tree);
      VARIABLES(ret);
      } break;
   case SNode::stFor: {
      TNodeFor* statement = new TNodeFor(lexeme->lexeme);
      statement->SetBeg(y2->tree);
      statement->SetCondition(y3->tree);
      statement->SetEnd(y4->tree);
      statement->SetBody(y5->tree);
      ret = statement;
      } break;
   case SNode::stIf: {
      TNodeIf* statement;
      if (param) {
         statement = (TNodeIf*)y2->tree;
         statement->SetElse(y3->tree);
      } else {
         statement = new TNodeIf(lexeme->lexeme);
         statement->SetCondition(y2->tree);
         statement->SetThen(y3->tree);
         statement->SetElse(y4->tree);
      }
      ret = statement;
      } break;
   case SNode::stRanges: {
      T_NodeList* list;
      if (param == 2) { // create
         list = new T_NodeList(lexeme->lexeme);
         list->Add(y2->tree);
      } else if (param == 3) { // add
         list = (T_NodeList*)y2->tree;
         list->Add(y3->tree);
      } else if (param == 4) { // insert
         list = (T_NodeList*)y2->tree;
         list->Insert(0, y3->tree);
      } else if (param == 1) { // ins(Null)
         list = (T_NodeList*)y2->tree;
         list->Insert(0, new TNodeNull());
      } else { // Null
         list = new T_NodeList(lexeme->lexeme);
         list->Add(new TNodeNull());
      }
      ret = list;
      } break;
   case SNode::stDefVar: {
      TNodeDefVar* def;
      if (param == 2) {
         def = (TNodeDefVar*)y2->tree; 
         def->SetAssign(syntax->oper_assign, y3->tree, syntax->data->semantic); // (,Node,Assign)
      } else {
         def = new TNodeDefVar(lexeme->lexeme); // (Lexeme,Type,,Assign)
         if (y2->tree) def->SetType((TNodeType*)y2->tree);
         if (!y2->tree && syntax->data->semantic->IsStack()) {
            S_Syntax *g_syntax = dynamic_cast<S_Syntax*> (syntax);
            int index = g_syntax->filled() - 1;
            for (; index >= 0; index--) {
               TStackRuleItem& stack_item = g_syntax->stack_item(index);
               if (TNodeType* node_type = dynamic_cast<TNodeType*> (stack_item.lexeme_node.tree)) {
                  def->SetType(node_type); break;
               }
               if (TNodeDefVar* def_var = dynamic_cast<TNodeDefVar*> (stack_item.lexeme_node.tree)) {
                  def->SetType(def_var->Type()); break;
               }
            }
         }
         if (y3->tree) def->SetAssign(syntax->oper_assign, y3->tree, syntax->data->semantic);
      }
      ret = def;
      } break;
   case SNode::stDefArr: {
      TNodeDefArr* def;
      if (param == 2) {
         def = (TNodeDefArr*)y2->tree; 
         def->SetAssign(y3->tree); // (,Node,Assign)
      } else {
         def = new TNodeDefArr(lexeme->lexeme, (T_NodeList*)y4->tree); // (Lexeme,Range)
         if (y2->tree) def->SetType((TNodeType*)y2->tree);
         if (!y2->tree && syntax->data->semantic->IsStack()) {
            S_Syntax *g_syntax = dynamic_cast<S_Syntax*> (syntax);
            int index = g_syntax->filled() - 1;
            for (; index >= 0; index--) {
               TStackRuleItem& stack_item = g_syntax->stack_item(index);
               if (TNodeType* node_type = dynamic_cast<TNodeType*> (stack_item.lexeme_node.tree)) {
                  def->SetType(node_type); break;
               }
               if (TNodeDefVar* def_var = dynamic_cast<TNodeDefVar*> (stack_item.lexeme_node.tree)) {
                  def->SetType(def_var->Type()); break;
               }
            }
         }
         if (y3->tree) def->SetAssign(syntax->oper_assign, y3->tree);
      }
      ret = def;
      } break;
   case SNode::stDefFunc: {
      TNodeDefFunc* func = NULL;
      if (param == 1) {
      } else if (param == 2) {
      } else {
         func = new TNodeDefFunc(lexeme->lexeme);
         if (y2->tree)  func->SetType((TNodeType*)y2->tree);
         TNodeBinary* par_body = (TNodeBinary*)y3->tree;
         TNodeDefine* par = (TNodeDefine*)par_body->Left();
         TNode *body = par_body->Right();
         if (body) { body->SetOwner(NULL); func->SetMid(body); }
         par->SetOwner(NULL); func->SetRight(par);
         delete par_body;
         ret = func;
         VARIABLES(ret);
      }
      } break;
   case SNode::stExpressions: {
      TNodeExpressions* list;
      if (param) {
         list = (TNodeExpressions*)y3->tree; // ((,node,list),1) - add
      } else {
         list = new TNodeExpressions(); // ((lexeme,node),0) - create + add
      }
      if (s2 && y2->tree) { 
         list->Add(y2->tree); 
         if (list->Lexeme().IsNone()) list->SetLexeme(y2->tree->FirstLexeme());
      }
      ret = list;
      } break;
   case SNode::stStatements: {
      TNodeStatements* list;
      if (param) {
         list = (TNodeStatements*)y3->tree; // ((,node,list),1) - add
      } else {
         list = new TNodeStatements(); // ((lexeme,node),0) - create + add
      }
      if (s2 && y2->tree) { list->Add(y2->tree); }
      ret = list;
      } break;
   case SNode::stList: {
      T_NodeList* list;
      if (param) {
         list = (T_NodeList*)y3->tree; // ((,node,list),1) - add
      } else {
         list = new T_NodeList(lexeme->lexeme); // ((lexeme,node),0) - create + add
      }
      if (s2 && y2->tree) { list->Add(y2->tree); }
      ret = list;
      } break;
   case SNode::stDefine: { // ((,Type,First,Tail),1)    ((,Type,First),0)
      TNodeDefine* define = NULL;
      if (param == 1) {
         define = (TNodeDefine*)y4->tree;
         if (define) {
            define->SetLexeme(y2->lexeme);
            define->SetType((TNodeType*)y2->tree);
         }
      }
      if (!define) {
         if (s2) {
            TNodeType *define_type = (TNodeType*)y2->tree;
            define = new TNodeDefine(define_type, define_type ? define_type->Lexeme() : lexeme->lexeme);
         } else {
            define = new TNodeDefine(lexeme->lexeme);
         }
      }
      if (s3 && y3->tree) { define->Insert(0, y3->tree); }
      ret = define;
      } break;
   default:
      ret = NULL;
      break;
   }
   S0.tree = ret;
   return true;
}

bool make_yacc_Grammar(const GSymbol& item, M_Syntax* syntax, T_Lexeme_SNode* data_stack[])
{
   SNode::S_Type type = (SNode::S_Type)item.maker;
   int param = item. MakerParam();
   int s1, s2, s3, s4, s5;
   tree_syn(item.point, s1, s2, s3, s4, s5);
   T_Lexeme_SNode *y1 = &lexeme_node, *y2 = &lexeme_node, *y3 = &lexeme_node, *y4 = &lexeme_node, *y5 = &lexeme_node;
   if (s1) y1 = data_stack[s1];
   if (s2) y2 = data_stack[s2];
   if (s3) y3 = data_stack[s3];
   if (s4) y4 = data_stack[s4];
   if (s5) y5 = data_stack[s5];
   T_Lexeme_SNode *lexeme = y1;
   if (!lexeme) { lexeme = &lexeme_node; }

   SNode* ret = NULL;
   switch (type) {
   case SNode::stEnums  : {
      SNodeList* list = NULL;
      if (param == 0) {
         list = new SNodeList(lexeme->lexeme,type);
      } else if (param == 1) {
         list = new SNodeList(lexeme->lexeme,type);
         list->Add(new SNodeList(y2->lexeme,type));
      } else if (param == 2) {
         list = new SNodeList(lexeme->lexeme,type);
         list->Add(y2->node);
      } else if (param == 3) {
         list = (SNodeList*)y2->node;
         list->Add(y3->node);
      } else if (param == 4) {
         list = (SNodeList*)y2->node;
         list->SetLexeme(lexeme->lexeme);
      } else if (param == 5) {
         list = new SNodeList(lexeme->lexeme,type);
         list->Add(y2->node);
      } else if (param == 6) {
         list = (SNodeList*)y2->node;
         list->Add(y3->node);
      }  else if (param == 7) {
         list = (SNodeList*)y2->node;
      }

      ret = list;
      ret->option = param;
      } break;
   case SNode::stTokens : {
      SNodeList* list;
      if (param == 0) {
         list = new SNodeList(lexeme->lexeme,type);
         list->Add(new SNodeList(y2->lexeme,type));
      } else if (param == 1) {
         list = new SNodeList(lexeme->lexeme,type);
         list->Add(y2->node);
      } else if (param == 2) {
         list = (SNodeList*)y2->node;
         list->Add(y3->node);
      }

      ret = list;
      ret->option = param;
      } break;
   case SNode::stFormula  : {
      SNodeList* list;
      if (param == 0) {
         list = new SNodeList(lexeme->lexeme,type);
         list->Add(y2->node);
      } else if (param == 1) {
         list = (SNodeList*)y2->node;
         list->Add(y3->node);
      } else if (param == 2) {
         if (y2->node) {
            SNodeList* formula = list = (SNodeList*)y2->node;
            formula->SetLexeme(lexeme->lexeme);
            if (y3->node) {
               list->Add(new SNodeList(lexeme->lexeme, SNode::stProduce)); // Empty
            }
         } else { // :;
            list = new SNodeList(lexeme->lexeme, type);
            list->Add(new SNodeList(lexeme->lexeme, SNode::stProduce));
         }
/*
      } else if (param == 3) {
         list = new SNodeList(lexeme->lexeme,type);
         list->Add(y2->node);
      } else if (param == 4) {
         list = (SNodeList*)y2->node;
         list->Add(y3->node);
*/
      } else if (param == 5) {
         list = new SNodeList(lexeme->lexeme,type);
         if (y2->node) list->Add(y2->node);
         if (y3->node) list->Add(y3->node);
         list->Add(y4->node);
      } else if (param == 6) { // BNF
         list = new SNodeList(lexeme->lexeme, type);
      } else if (param == 7) { // BNF
         T_Lexeme head_lexeme(y2->node->Lexeme());
         if (!head_lexeme.Match(T_Lexeme::grIdent)) {
            syntax->forward = head_lexeme;
            return false;
         }
         list = new SNodeList(head_lexeme, type);
         list->Add(y2->node);
      }

      ret = list;
      ret->option = param;
      } break;
   case SNode::stProduce  : {
      SNodeList* list;
      if (param == 4) {
         list = new SNodeList(lexeme->lexeme,type);
         if (!s1) list->SetLexeme(syntax->forward);
         if (y2->node) list->Add(y2->node);
      } else if (param == 5) {
         list = (SNodeList*)y2->node;
         list->Add(y3->node);
      } else if (param == 6) { // BNF
         list = new SNodeList(lexeme->lexeme, type);
      } else if (param == 7) { // BNF list(Produce).add(item)
         list = (SNodeList*)y2->node;
         SNode* item;
         if (!y1->node) {
            item = new SNodeList(lexeme->lexeme, SNode::stItem); // <space>
         } else {
            item = y1->node;
         }
         list->Add(item);
      } else if (param == 8) { // BIF create(Produce).add(item)
         list = new SNodeList(T_Lexeme(), type);
         SNode* item;
         if (!y1->node) {
            item = new SNodeList(lexeme->lexeme, SNode::stItem); // <space>
         } else {
            item = y1->node;
         }
         list->Add(item);
      }

      ret = list;
      ret->option = param;
      } break;
   case SNode::stItem: {
      SNodeList* list;
      if (param == 0) {        // Item(Ident)
         list = new SNodeList(lexeme->lexeme,type);
      } else if (param == 1) { // Item(Integer)
         list = new SNodeList(lexeme->lexeme, type);
      } else if (param == 2) { // Item(<Group>)
         list = new SNodeList(lexeme->lexeme, type);
      } else if (param == 3) { // Item(<Group,Type>)
         list = new SNodeList(lexeme->lexeme, type);
         list->Add(new SNodeList(y2->lexeme, type));
      } else if (param == 4) { // Item(|)
         list = new SNodeList(lexeme->lexeme, type);
      } else if (param == 5) { // BIF create(Item).ref(or_list(Formula))
         // bool yes_or = lexeme->lexeme.Match(A_Symbol::lxLeftCramp);     { or_list }
         // bool yes_empty = lexeme->lexeme.Match(A_Symbol::lxLeftScrape); [ or_list ]
         // bool yes_master = lexeme->lexeme.Match(A_Symbol::lxEllipsis);  [ or_list ]...
         list = (SNodeList*)y2->node; // Formula
         list->SetLexeme(lexeme->lexeme);
//      } else if (param == 6) { // BIF create(Item).ref(or_list(Formula)) [ or_list ] /. Maker ./ ...
//         list = (SNodeList*)y2->node; // Formula
//         list->Add(y3->node);  // Maker
//         list->SetLexeme(lexeme->lexeme);
      }
      ret = list;
      if (param != 5) ret->option = param;
      } break;
   case SNode::stMaker  : {
      SNodeList* list;
      if (param == 0 || param == 5 || param == 6) { // MAKE, TURN, CALL
         list = new SNodeList(lexeme->lexeme,type);
         list->Add(new SNodeList(y2->lexeme,type));
         if (y3->node) list->Add(y3->node);
      } else if (param == 1) { // NODE
         list = new SNodeList(lexeme->lexeme,type);
         list->Add(y2->node);
         if (y3->node) list->Add(y3->node);
      } else if (param == 2) { // NODE(body)
         list = new SNodeList(lexeme->lexeme,type);
         if (y1->node) list->Add(y1->node);
         if (y2->node) list->Add(y2->node);
         if (y3->node) list->Add(y3->node);
         if (y4->node) list->Add(y4->node);
         if (y5->node) list->Add(y5->node);
      } else if (param == 3) { // NODE(int_body)
         list = new SNodeList(lexeme->lexeme,type);
         if (y2->lexeme.group) list->Add(new SNodeList(y2->lexeme,type));
      } else if (param == 4) { // NODE(-int_body)
         list = new SNodeList(lexeme->lexeme, type);
      }

      ret = list;
      ret->option = param;
      } break;
   default : 
      ret = NULL;
      break;
   }
   S0.node = ret;
   return true;
}

MAKER_YACC(MakerSNode)
{
   if (syntax->syntax_mode <= A_Syntax::smParseLL1) {
      if (ACTION(Node)) {
         return make_yacc_LL_SN(item, syntax, data_stack);
      } else if (ACTION(Made)) {
         if (SYNTAX_MODE(Phase, TwoPhase)) {
            return make_yacc_LL_MK(item, syntax, data_stack);
         } else {
            return make_yacc_LL_MD(item, syntax, data_stack);
         }
      }
   } else {
      if (item.maker >= SNode::stFormula) {
         return make_yacc_Grammar(item, syntax, data_stack);
      } else {
         if (ACTION(Node)) {
            return make_yacc_LR_SN(item, syntax, data_stack);
         } else if (ACTION(Made)) {
            return make_yacc_LR_MD(item, syntax, data_stack);
         }
      }
   }
   return true;
}


#undef S0
#undef S1
#undef S2
#undef S3
#undef S4
