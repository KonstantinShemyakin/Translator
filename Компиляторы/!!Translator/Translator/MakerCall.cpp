#define ENTRY_TREE(N) { if (TNode* node = syntax->Program()) { node->SetCurrentChild(N); } syntax->Program(N); }
//#define ENTRY_TREE(N) { printf("\nE*E*E "); if (TNode* node = syntax->Program()) { printf(" %s->",node->title()); node->SetCurrentChild(N); } printf(" %s\n",N->title()); syntax->Program(N); }
#undef  CURRENT_CHILD
#define CURRENT_CHILD(C) if (!syntax->Program()->SetCurrentChild(C)) return false;
//#define CURRENT_CHILD(C) { printf("\nC*C*C %s(%d) + %s\n",syntax->Program()->title(),syntax->Program()->current_child,C->title()); if (!syntax->Program()->SetCurrentChild(C)) return false; }
#define CURRENT_CHANGE(C) if (syntax->Program()->ChangeCurrentChild(C)) syntax->Program(C); else return false;
#define NODE_TREE syntax->Program()
#define LEAVE_TREE { TNode* node = syntax->Program(); if (node && node->Owner()) syntax->Program(node->Owner()); }
//#define LEAVE_TREE { TNode* node = syntax->Program(); if (node && node->Owner()) { printf("\nL*L*L %s<-%s\n",node->Owner()->title(),node->title()); syntax->Program(node->Owner());} }

#define STEP_IF(STEP)   if (step & T_Step::ts##STEP) {
#define STEP_ELSE(STEP) } if (step & T_Step::ts##STEP) {
#define STEP_END        }

bool make_call_01_MK(const GSymbol& item, M_Syntax* syntax)
{
   SNode::S_Type type = (SNode::S_Type)item.node;
   int param = item.MakerParam();
   int step = item.step;
//   printf("\n*** ENTRY_CALL "); if (syntax->Program()) { printf("%s(d=%d,c=%d)", syntax->Program()->title(), syntax->Program()->depth(),syntax->Program()->current_child);  printf("\n"); }
   switch (type) {
   case SNode::stNone: {
      if (param == 0) { // Copy
      }
      else if (param == 1) {
      }
      else if (param == 2) { // lexeme
      }
      } break;
   case SNode::stNull: {
      STEP_IF(Create)
         TNode* null = new TNodeNull();
         CURRENT_CHILD(null);
      STEP_END
      } break;
   case SNode::stNumber: {
      T_Lexeme lexeme = syntax->PopLexeme();
      TNodeNumber *number = new TNodeNumber(lexeme);
      CURRENT_CHILD(number);
      } break;
   case SNode::stVar: {
      T_Lexeme lexeme;
      const T_Lexeme& top = syntax->TopLexeme();
      bool change = (!top.Match(T_Lexeme::grIdent));
      if (change) {
         lexeme = syntax->PopLexeme();
      }
      T_Lexeme lexeme_ident = syntax->PopLexeme();
      TNodeVar *var = new TNodeVar(lexeme_ident);
      if (change)  syntax->push_lexeme(lexeme);
      CURRENT_CHILD(var);
      VARIABLES_STEP(var, All)
      } break;
   case SNode::stGoTo: {
      T_Lexeme lexeme = syntax->PopLexeme();
      if (lexeme.IsNone()) lexeme = syntax->last_key_word;
      TNodeUserGoTo *statement = new TNodeUserGoTo(lexeme);
      CURRENT_CHILD(statement);
      VARIABLES_STEP(statement, All)
      } break;
   case SNode::stBreak: {
      TNodeBreakContinue *statement = new TNodeBreakContinue(T_Block::tbBreak, syntax->forward);
      CURRENT_CHILD(statement);
      VARIABLES_STEP(statement, All)
      } break;
   case SNode::stContinue: {
      TNodeBreakContinue *statement = new TNodeBreakContinue(T_Block::tbContinue, syntax->forward);
      CURRENT_CHILD(statement);
      VARIABLES_STEP(statement, All)
      } break;
   case SNode::stLabel: {
      T_Lexeme lexeme = syntax->PopLexeme();
      TNodeUserLabel* label = new TNodeUserLabel(lexeme);
      CURRENT_CHILD(label);
      VARIABLES_STEP(label, All)
      } break;
   case SNode::stRefDef: {
      TNodeDefVar *var = (TNodeDefVar*)NODE_TREE->GetCurrentChild(); // var || arr
      TNodeType* type = var->Type();
      if (type) {
         type = TBaseType::Or(type, T_BaseType::btReference);
         var->SetType(type);
      }
      var->referenced = true;
      } break;
   case SNode::stCast: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeType *type = syntax->BaseType(lexeme);
         TNodeCast *cast = new TNodeCast(lexeme, type, NULL);
         ENTRY_TREE(cast)
         cast->SetChildIndex(1);
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, All)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stPrimary: {
      T_Lexeme lexeme;// = syntax->PopLexeme();
      TNode *primary = new TNodePrimary(lexeme, NULL);
      CURRENT_CHANGE(primary)
      VARIABLES_STEP(primary, All)
      LEAVE_TREE
      } break;
   case SNode::stCall: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeCall* call = new TNodeCall(lexeme);
         ENTRY_TREE(call)
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, All)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stIndex: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeIndex* index = new TNodeIndex(lexeme);
         ENTRY_TREE(index)
         index->SetChildIndex(1);
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, All)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stReturn: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->last_key_word;
         TNodeReturn* retur = new TNodeReturn(lexeme);
         ENTRY_TREE(retur)
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, All)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stUnary: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         if (param) syntax->ChangeUnary(lexeme, false);
         TNodeUnary* unary = new TNodeUnary(lexeme, NULL);
         ENTRY_TREE(unary)
      STEP_ELSE(UnaryIncDec)
         T_Lexeme lexeme = syntax->PopLexeme();
         syntax->ChangeUnary(lexeme, false);
         TNodeUnary *unary = new TNodeUnary(lexeme, NULL);
         CURRENT_CHANGE(unary)
         VARIABLES_STEP(unary, All)
         LEAVE_TREE
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, All)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stLogical:
   case SNode::stBinary: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNode* binary = NULL;
         if (lexeme.Match(T_Symbol::prOrOr) || lexeme.Match(T_Symbol::prAndAnd)) {
            binary = new TNodeLogical(lexeme, NULL, NULL);
         }  else {
            binary = new TNodeBinary(lexeme, NULL, NULL);
         }
         CURRENT_CHANGE(binary)
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, All)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stWhile: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->last_key_word;
         TNodeWhile* statement = new TNodeWhile(lexeme);
         ENTRY_TREE(statement)
         VARIABLES_STEP(statement, Begin)
      STEP_ELSE(Condition)
         VARIABLES_STEP(NODE_TREE, Condition)
      STEP_ELSE(Body)
         VARIABLES_STEP(NODE_TREE, Body)
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, End)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stDo: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->last_key_word;
         TNodeDo* statement = new TNodeDo(lexeme);
         ENTRY_TREE(statement)
         VARIABLES_STEP(statement, Begin)
      STEP_ELSE(Body)
         VARIABLES_STEP(NODE_TREE, Body)
      STEP_ELSE(Condition)
         VARIABLES_STEP(NODE_TREE, Condition)
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, End)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stTrio: { // Question
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeTrio* trio = new TNodeTrio(lexeme, NULL, NULL, NULL);
         CURRENT_CHANGE(trio)
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, All)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stFor: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->last_key_word;
         TNodeFor* statement = new TNodeFor(lexeme);
         ENTRY_TREE(statement)
         VARIABLES_STEP(statement, Begin)
      STEP_ELSE(ForTitle)
         VARIABLES_STEP(NODE_TREE, ForTitle)
      STEP_ELSE(Body) // body
         VARIABLES_STEP(NODE_TREE, Body);
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, End)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stIf: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->last_key_word;
         TNodeIf* statement = new TNodeIf(lexeme);
         ENTRY_TREE(statement)
         VARIABLES_STEP(statement, Begin)
      STEP_ELSE(Condition) // condition
         VARIABLES_STEP(NODE_TREE, Condition)
      STEP_ELSE(IfThen) // then
         VARIABLES_STEP(NODE_TREE, IfThen)
      STEP_ELSE(IfElse) // else
         VARIABLES_STEPS(NODE_TREE, IfElse, IfLabel, End, )
         LEAVE_TREE
      STEP_END
      } break;
            /*
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
      */
   case SNode::stDefVar: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeDefVar* def = new TNodeDefVar(lexeme); // (Lexeme,Type,,Assign)
         TNodeType *type_node = NULL;
         if (param == 1) {
            T_Lexeme lexeme_type = syntax->PopLexeme();
            type_node = syntax->BaseType(lexeme_type);
         } else {
            type_node = syntax->data->semantic->type_node;
         }
         def->SetType(type_node);
         def->ChangeChildIndex(1);
         ENTRY_TREE(def)
      STEP_ELSE(DefVarAssign)
         TNodeDefVar* var = (TNodeDefVar*)NODE_TREE;
         if (var->Right()) {
            var->Right()->SetOwner();
            T_Lexeme lexeme = syntax->PopLexeme();
            var->SetAssign(lexeme, var->Right(), SYNTAX_MODE(Phase, TwoPhase) ? syntax->data->semantic : NULL);
         }
         VARIABLES_STEP(NODE_TREE, All)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stDefArr: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeDefArr* def = new TNodeDefArr(lexeme, NULL); // (Lexeme,Type,Range,Assign)
         TNodeType *type_node = NULL;
         if (param == 1) {
            T_Lexeme lexeme_type = syntax->PopLexeme();
            type_node = syntax->BaseType(lexeme_type);
         } else {
            type_node = syntax->data->semantic->type_node;
         }
         def->SetType(type_node);
         def->SetChildIndex(2);
         ENTRY_TREE(def)
      STEP_ELSE(DefArrRanges)
         VARIABLES_STEP(NODE_TREE, Begin)
         NODE_TREE->SetChildIndex(1);
      STEP_ELSE(DefArrAssign)
         TNodeDefArr* var = (TNodeDefArr*)NODE_TREE; // (,Node,Assign)
         if (var->Right()) {
            var->Right()->SetOwner();
            T_Lexeme lexeme = syntax->PopLexeme();
            var->SetAssign(var->Right());
         }
         VARIABLES_STEP(NODE_TREE, DefArrAssign)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stDefFunc: {
      STEP_IF(Begin) // Type
      STEP_ELSE(FuncIdent) // Ident
         T_Lexeme lexeme = syntax->PopLexeme();
         T_Lexeme lexeme_type = syntax->PopLexeme();
         TNodeType *type_node = syntax->BaseType(lexeme_type);
         TNodeDefFunc* func = new TNodeDefFunc(type_node, lexeme, NULL, NULL);
         ENTRY_TREE(func)
         VARIABLES_STEP(func, Begin)
      STEP_ELSE(Param) // Params
         if (!param) { NODE_TREE->ChangeChildIndex(1); }
         VARIABLES_STEP(NODE_TREE, Param)
      STEP_ELSE(Body) // Body
         VARIABLES_STEP(NODE_TREE, Body)
      STEP_ELSE(End) // End
         VARIABLES_STEP(NODE_TREE, End)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stDefine: {
      STEP_IF(Begin)
         T_Lexeme lexeme;
         TNodeType *type_node = NULL;
         if (!param) { // Define
            lexeme = syntax->PopLexeme();
            type_node = syntax->BaseType(lexeme);
            syntax->data->semantic->type_node = type_node;
         }
         TNodeDefine* define = new TNodeDefine(type_node, lexeme);
         ENTRY_TREE(define)
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, End)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stList: {
      STEP_IF(Begin)
         T_Lexeme lexeme;
         T_NodeList* list = new T_NodeList(lexeme);
         ENTRY_TREE(list)
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, End)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stExpressions: {
      STEP_IF(Begin)
         T_Lexeme lexeme;
         T_NodeList* list = new TNodeExpressions(lexeme);
         CURRENT_CHANGE(list)
         lexeme = list->back()->Lexeme();
         list->SetLexeme(lexeme);
      STEP_ELSE(End)
         TNodeExpressions* expr = (TNodeExpressions*)NODE_TREE;
         expr->part = (T_Part)item.MakerParam();
         VARIABLES_STEP(NODE_TREE, End)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stStatements: {
      STEP_IF(Begin)
         TNodeStatements* list = new TNodeStatements();
         ENTRY_TREE(list)
         VARIABLES_STEP(list, Begin)
      STEP_ELSE(Body)
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, End)
         LEAVE_TREE
      STEP_END
      } break;
   default:
      break;
   }
//   printf("\n*** EXIT_CALL "); if (syntax->Program()) { printf("%s(d=%d,c=%d)", syntax->Program()->title(), syntax->Program()->depth(),syntax->Program()->current_child); printf("\n"); }
   return true;
}

#undef  CURRENT_CHILD
//#define CURRENT_CHILD(C) syntax->PushNode(C);
#undef NODE_TREE
#define NODE_TREE syntax->TopNode()
#undef ENTRY_TREE
//#define ENTRY_TREE(N) syntax->PushNode(N);
#define PUSH_NODE(N) syntax->PushNode(N);
#define POP_NODE(T,N) T* N = (T*)syntax->PopNode();
#define TOP_NODE(T,N) T* N = (T*)syntax->TopNode();
#define POP_STACK syntax->PopNode();

bool make_call_02_MK(const GSymbol& item, M_Syntax* syntax)
{
   SNode::S_Type type = (SNode::S_Type)item.node;
   int param = item.MakerParam();
   int step = item.step;
//   printf("\n*** ENTRY_CALL "); if (syntax->Program()) { printf("%s(d=%d,c=%d)", syntax->Program()->title(), syntax->Program()->depth(),syntax->Program()->current_child);  printf("\n"); }
   switch (type) {
   case SNode::stNone: {
      if (param == 0) { // Copy
      }
      else if (param == 1) {
      }
      else if (param == 2) { // lexeme
      }
      } break;
   case SNode::stNull: {
      STEP_IF(Create)
         TNode* null = new TNodeNull();
         PUSH_NODE(null);
      STEP_ELSE(Empty)
         TNode* null = new TNodeNull();
         PUSH_NODE(null);
      STEP_END
      } break;
   case SNode::stNumber: {
      T_Lexeme lexeme = syntax->PopLexeme();
      TNodeNumber *number = new TNodeNumber(lexeme);
      PUSH_NODE(number);
      } break;
   case SNode::stVar: {
      T_Lexeme lexeme;
      const T_Lexeme& top = syntax->TopLexeme();
      bool change = (!top.Match(T_Lexeme::grIdent));
      if (change) {
         lexeme = syntax->PopLexeme();
      }
      T_Lexeme lexeme_ident = syntax->PopLexeme();
      TNodeVar *var = new TNodeVar(lexeme_ident);
      if (change)  syntax->push_lexeme(lexeme);
      PUSH_NODE(var);
      VARIABLES_STEP(var, All)
      } break;
   case SNode::stGoTo: {
      T_Lexeme lexeme = syntax->PopLexeme();
      if (lexeme.IsNone()) lexeme = syntax->last_key_word;
      TNodeUserGoTo *statement = new TNodeUserGoTo(lexeme);
      PUSH_NODE(statement);
      VARIABLES_STEP(statement, All)
      } break;
   case SNode::stBreak: {
      TNodeBreakContinue *statement = new TNodeBreakContinue(T_Block::tbBreak, syntax->forward);
      PUSH_NODE(statement);
      VARIABLES_STEP(statement, All)
      } break;
   case SNode::stContinue: {
      TNodeBreakContinue *statement = new TNodeBreakContinue(T_Block::tbContinue, syntax->forward);
      PUSH_NODE(statement);
      VARIABLES_STEP(statement, All)
      } break;
   case SNode::stLabel: {
      T_Lexeme lexeme = syntax->PopLexeme();
      TNodeUserLabel* label = new TNodeUserLabel(lexeme);
      PUSH_NODE(label);
      VARIABLES_STEP(label, All)
      } break;
   case SNode::stRefDef: {
      TNodeDefVar *var = (TNodeDefVar*)NODE_TREE; // var || arr
      TNodeType* type = var->Type();
      if (type) {
         type = TBaseType::Or(type, T_BaseType::btReference);
         var->SetType(type);
      }
      var->referenced = true;
      } break;
   case SNode::stCast: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeType *type = syntax->BaseType(lexeme);
         TNodeCast *cast = new TNodeCast(lexeme, type, NULL);
         PUSH_NODE(cast)
      STEP_ELSE(End)
         POP_NODE(TNode,expr)
         POP_NODE(TNodeCast,cast)
         cast->SetRight(expr);
         VARIABLES_STEP(NODE_TREE, All)
      STEP_END
      } break;
   case SNode::stPrimary: {
      T_Lexeme lexeme;// = syntax->PopLexeme();
      POP_NODE(TNode,expr)
      TNode *primary = new TNodePrimary(lexeme, expr);
      PUSH_NODE(primary)
      VARIABLES_STEP(primary, All)
      } break;
   case SNode::stCall: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeCall* call = new TNodeCall(lexeme);
         PUSH_NODE(call)
      STEP_ELSE(End)
         POP_NODE(T_NodeList, params)
         TOP_NODE(TNodeCall, call)
         call->SetRight(params);
         VARIABLES_STEP(call, All)
      STEP_END
      } break;
   case SNode::stIndex: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeIndex* index = new TNodeIndex(lexeme);
         PUSH_NODE(index)
      STEP_ELSE(End)
         POP_NODE(T_NodeList, ranges)
         TOP_NODE(TNodeIndex, index)
         index->SetList(ranges);
         VARIABLES_STEP(index, All)
      STEP_END
      } break;
   case SNode::stReturn: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->last_key_word;
         TNodeReturn* retur = new TNodeReturn(lexeme);
         PUSH_NODE(retur)
      STEP_ELSE(End)
         POP_NODE(TNode, value)
         TOP_NODE(TNodeReturn, retur)
         retur->SetValue(value);
         VARIABLES_STEP(retur, All)
      STEP_END
      } break;
   case SNode::stUnary: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         if (param) syntax->ChangeUnary(lexeme, false);
         TNodeUnary* unary = new TNodeUnary(lexeme, NULL);
         PUSH_NODE(unary)
      STEP_ELSE(UnaryIncDec)
         T_Lexeme lexeme = syntax->PopLexeme();
         syntax->ChangeUnary(lexeme, false);
         POP_NODE(TNode, expr)
         TNodeUnary *unary = new TNodeUnary(lexeme, expr);
         PUSH_NODE(unary)
         VARIABLES_STEP(unary, All)
      STEP_ELSE(End)
         POP_NODE(TNode, expr)
         TOP_NODE(TNodeUnary, unary)
         unary->SetChild(expr);
         VARIABLES_STEP(unary, All)
      STEP_END
      } break;
   case SNode::stLogical:
   case SNode::stBinary: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNode* binary = NULL;
         if (lexeme.Match(T_Symbol::prOrOr) || lexeme.Match(T_Symbol::prAndAnd)) {
            binary = new TNodeLogical(lexeme, NULL, NULL);
         }  else {
            binary = new TNodeBinary(lexeme, NULL, NULL);
         }
         CURRENT_CHANGE(binary)
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, All)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stWhile: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->last_key_word;
         TNodeWhile* statement = new TNodeWhile(lexeme);
         PUSH_NODE(statement)
         VARIABLES_STEP(statement, Begin)
      STEP_ELSE(Condition)
         POP_NODE(TNode, condition)
         TOP_NODE(TNodeWhile, statement)
         statement->SetCondition(condition);
         VARIABLES_STEP(statement, Condition)
      STEP_ELSE(Body)
         POP_NODE(TNode, body)
         TOP_NODE(TNodeWhile, statement)
         statement->SetBody(body);
         VARIABLES_STEP(statement, Body)
      STEP_ELSE(End)
         TOP_NODE(TNodeWhile, statement)
         VARIABLES_STEP(statement, End)
      STEP_END
      } break;
   case SNode::stDo: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->last_key_word;
         TNodeDo* statement = new TNodeDo(lexeme);
         PUSH_NODE(statement)
         VARIABLES_STEP(statement, Begin)
      STEP_ELSE(Body)
         POP_NODE(TNode, body)
         TOP_NODE(TNodeDo, statement)
         statement->SetBody(body);
         VARIABLES_STEP(statement, Body)
      STEP_ELSE(Condition)
         POP_NODE(TNode, condition)
         TOP_NODE(TNodeDo, statement)
         statement->SetCondition(condition);
         VARIABLES_STEP(statement, Condition)
      STEP_ELSE(End)
         TOP_NODE(TNodeDo, statement)
         VARIABLES_STEP(statement, End)
      STEP_END
      } break;
   case SNode::stTrio: { // Question
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeTrio* trio = new TNodeTrio(lexeme, NULL, NULL, NULL);
         CURRENT_CHANGE(trio)
      STEP_ELSE(End)
         VARIABLES_STEP(NODE_TREE, All)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stFor: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->last_key_word;
         TNodeFor* statement = new TNodeFor(lexeme);
         PUSH_NODE(statement)
         VARIABLES_STEP(statement, Begin)
      STEP_ELSE(ForTitle)
         POP_NODE(TNode, posfix)
         POP_NODE(TNode, condition)
         POP_NODE(TNode, prefix)
         TOP_NODE(TNodeFor, statement)
         statement->SetBeg(prefix);
         statement->SetCondition(condition);
         statement->SetEnd(posfix);
         VARIABLES_STEP(statement, ForTitle)
      STEP_ELSE(Body) // body
         POP_NODE(TNode, body)
         TOP_NODE(TNodeFor, statement)
         statement->SetBody(body);
         VARIABLES_STEP(statement, Body);
      STEP_ELSE(End)
         TOP_NODE(TNodeFor, statement)
         VARIABLES_STEP(statement, End)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stIf: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->last_key_word;
         TNodeIf* statement = new TNodeIf(lexeme);
         PUSH_NODE(statement)
         VARIABLES_STEP(statement, Begin)
      STEP_ELSE(Condition) // condition
         POP_NODE(TNode, condition)
         TOP_NODE(TNodeIf, statement)
         statement->SetCondition(condition);
         VARIABLES_STEP(statement, Condition)
      STEP_ELSE(IfThen) // then
         POP_NODE(TNode, then_sttmnt)
         TOP_NODE(TNodeIf, statement)
         statement->SetThen(then_sttmnt);
         VARIABLES_STEP(statement, IfThen)
      STEP_ELSE(IfElse) // else
         POP_NODE(TNode, else_sttmnt)
         TOP_NODE(TNodeIf, statement)
         statement->SetElse(else_sttmnt);
         VARIABLES_STEPS(statement, IfElse, IfLabel, End, )
      STEP_END
      } break;
            /*
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
      */
   case SNode::stDefVar: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeDefVar* def = new TNodeDefVar(lexeme); // (Lexeme,Type,,Assign)
         TNodeType *type_node = NULL;
         if (param == 1) {
            T_Lexeme lexeme_type = syntax->PopLexeme();
            type_node = syntax->BaseType(lexeme_type);
         } else {
            type_node = syntax->data->semantic->type_node;
         }
         def->SetType(type_node);
         PUSH_NODE(def)
      STEP_ELSE(DefVarAssign)
         POP_NODE(TNode,value);
         TOP_NODE(TNodeDefVar,var);
         T_Lexeme lexeme = syntax->PopLexeme();
         var->SetAssign(lexeme, value, SYNTAX_MODE(Phase, TwoPhase) ? syntax->data->semantic : NULL);
      STEP_ELSE(End)
         TOP_NODE(TNodeDefVar,var)
         VARIABLES_STEP(var, All)
      STEP_END
      } break;
   case SNode::stDefArr: {
      STEP_IF(Begin)
         T_Lexeme lexeme = syntax->PopLexeme();
         TNodeDefArr* def = new TNodeDefArr(lexeme, NULL); // (Lexeme,Type,Range,Assign)
         TNodeType *type_node = NULL;
         if (param == 1) {
            T_Lexeme lexeme_type = syntax->PopLexeme();
            type_node = syntax->BaseType(lexeme_type);
         } else {
            type_node = syntax->data->semantic->type_node;
         }
         def->SetType(type_node);
         def->SetChildIndex(2);
         PUSH_NODE(def)
      STEP_ELSE(DefArrRanges)
         VARIABLES_STEP(NODE_TREE, Begin)
         NODE_TREE->SetChildIndex(1);
      STEP_ELSE(DefArrAssign)
         TNodeDefArr* var = (TNodeDefArr*)NODE_TREE; // (,Node,Assign)
         if (var->Right()) {
            var->Right()->SetOwner();
            T_Lexeme lexeme = syntax->PopLexeme();
            var->SetAssign(var->Right());
         }
         VARIABLES_STEP(NODE_TREE, DefArrAssign)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stDefFunc: {
      STEP_IF(Begin) // Type
      STEP_ELSE(FuncIdent) // Ident
         T_Lexeme lexeme = syntax->PopLexeme();
         T_Lexeme lexeme_type = syntax->PopLexeme();
         TNodeType *type_node = syntax->BaseType(lexeme_type);
         TNodeDefFunc* func = new TNodeDefFunc(type_node, lexeme, NULL, NULL);
         PUSH_NODE(func)
         VARIABLES_STEP(func, Begin)
      STEP_ELSE(Param) // Params
         if (param) {
            POP_NODE(TNodeDefine, params)
            TOP_NODE(TNodeDefFunc, func)
            func->SetParams(params);
            VARIABLES_STEP(func, Param)
         }
      STEP_ELSE(Body) // Body
         POP_NODE(TNode, body)
         TOP_NODE(TNodeDefFunc, func)
         func->SetBody(body);
         VARIABLES_STEP(func, Body)
      STEP_ELSE(End) // End
         TOP_NODE(TNodeDefFunc,func)
         VARIABLES_STEP(func, End)
      STEP_END
      } break;
   case SNode::stDefine: {
      STEP_IF(Begin)
         T_Lexeme lexeme;
         TNodeType *type_node = NULL;
         if (!param) { // Define
            lexeme = syntax->PopLexeme();
            type_node = syntax->BaseType(lexeme);
            syntax->data->semantic->type_node = type_node;
         }
         TNodeDefine* define = new TNodeDefine(type_node, lexeme);
         PUSH_NODE(define)
      STEP_ELSE(End)
         TOP_NODE(TNodeDefine, define)
         VARIABLES_STEP(define, End)
      STEP_END
      } break;
   case SNode::stList: {
      STEP_IF(Begin)
         T_Lexeme lexeme;
         T_NodeList* list = new T_NodeList(lexeme);
         PUSH_NODE(list)
      STEP_ELSE(Empty)
         T_Lexeme lexeme;
         T_NodeList* list = new T_NodeList(lexeme);
         PUSH_NODE(list)
      STEP_ELSE(Append)
         POP_NODE(TNode, item)
         TOP_NODE(T_NodeList, list)
         list->Add(item);
      STEP_ELSE(End)
         TOP_NODE(T_NodeList, list)
         VARIABLES_STEP(list, End)
      STEP_END
      } break;
   case SNode::stExpressions: {
      STEP_IF(Begin)
         T_Lexeme lexeme;
         T_NodeList* list = new TNodeExpressions(lexeme);
         CURRENT_CHANGE(list)
         lexeme = list->back()->Lexeme();
         list->SetLexeme(lexeme);
      STEP_ELSE(End)
         TNodeExpressions* expr = (TNodeExpressions*)NODE_TREE;
         expr->part = (T_Part)item.MakerParam();
         VARIABLES_STEP(NODE_TREE, End)
         LEAVE_TREE
      STEP_END
      } break;
   case SNode::stStatements: {
      STEP_IF(Begin)
         TNodeStatements* list = new TNodeStatements();
         PUSH_NODE(list)
         VARIABLES_STEP(list, Begin)
      STEP_ELSE(Body)
      STEP_ELSE(End)
         TOP_NODE(T_NodeList, list)
         VARIABLES_STEP(list, End)
      STEP_END
      } break;
   default:
      break;
   }
//   printf("\n*** EXIT_CALL "); if (syntax->Program()) { printf("%s(d=%d,c=%d)", syntax->Program()->title(), syntax->Program()->depth(),syntax->Program()->current_child); printf("\n"); }
   return true;
}

MAKER_TREE(MakerCall)
{
   if (item.MakerCaller() == 0x01) {
      return make_call_01_MK(item, syntax);
   }
   if (item.MakerCaller() == 0x02) {
      return make_call_02_MK(item, syntax);
   }
   return true;
}

