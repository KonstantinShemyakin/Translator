// --------------------- Codes ---------------------

MAKER_CODE(SaveLexeme)
{
   T_Lexeme::T_Group group = T_Lexeme::T_Group(item.MakerParam() >> 16);
   int type = item.MakerParam() & 0x0000FFFF;
   T_Lexeme lexeme(group,type);
   syntax->push_lexeme(lexeme);
   return true;
}

MAKER_CODE(Compaund)
{
   TNodeStatements *statements = new TNodeStatements();
   semantic->BlockBegin(statements);
   semantic->ExecStack.Push();
   return true;
}

MAKER_CODE(BegStmExprLL)
{
   TNodeStatements *statements = new TNodeStatements();
   semantic->BlockBegin(statements);
   semantic->ExecStack.Push();
   return true;
}

MAKER_CODE(BegStmExprLR)
{
   TNodeStatements *statements = new TNodeStatements();
   semantic->BlockBegin(statements);
   semantic->ExecStack.Push();
   return true;
}

MAKER_CODE(EndBlock)
{
   semantic->BlockEnd(NULL,true);
   semantic->ExecStack.Down();
   return true;
}

MAKER_CODE(Part)
{
   T_Part param = (T_Part)item.MakerParam();
   TExprStackItem part(param);
   syntax->Push(part);
   return true;
}

MAKER_CODE(PopType)
{
   syntax->Pop();
   return true;
}

MAKER_CODE(ExpressionsLL)
{
// stack: part, assign
   TExprStackItem assign = syntax->TipTop();
   assign.param = 1;
// stack: part
   TExprStackItem part = syntax->TipTop();
   assign.part = part.part;
   syntax->PushWithoutMade(assign);
   return true;
}

MAKER_CODE(ExpressionsLR)
{
   // stack: assign
   syntax->Top().param = 1;
   return true;
}

MAKER_CODE(AddToExpr)
{
// stack: expr..., assign
   TExprStackItem assign = syntax->TipTop();
   assign.param = syntax->Top().param + 1;
   assign.part = syntax->Top().part;
   syntax->PushWithoutMade(assign);
   return true;
}

bool make_code_ExpressionS(const GSymbol& item, MC_Syntax* syntax, TSemantic* semantic, T_Part part)
{
   int count = syntax->Top().param;
   bool pop = false;
   if (!(part & T_Part::psValueList)) {
      TExprStackItem last_expr = syntax->Top();
      for (int i = count - 1; i >= 0; i-- ) {
   	   TExprStackItem& expr = syntax->Top(); 
         bool last = (i == (count - 1)), condition = last && (part & psIfGoTo), value = (part & psValueList) || last && (part & psValue);
         if (!last) { // !last
            if (expr.type == btLogical) {
               syntax->AddCode(expr.false_label,expr.made++); syntax->AddCode(expr.true_label,expr.made++);
            } else if (expr.value()) {
               semantic->GenPop(1,expr.made++);
            }
            syntax->Pop(); // expr
         } else if (part != psNone) { // last && !primary
            pop = !value && !condition;
            if ((part & psIfGoTo)) { 
               if (!syntax->MakeLogic()) return false;
            } else if (part & psValue) {
               syntax->MakeValue();
               if (!syntax->Top().value()) return false;
            } else {
               if (syntax->Top().value()) {
                  semantic->GenPop(1,syntax->Top().made++);
                  syntax->Top().type = btVoid;
               }
            }
            last_expr = syntax->TipTop();
         } else { // last && primary
            syntax->Pop(); // expr
         }
      }
      if (!pop) syntax->Push(last_expr);
   }
   return true;
}
MAKER_CODE(ExpressionSLL)
{
   T_Part part = syntax->Top().part;
   return make_code_ExpressionS(item, syntax, semantic, part);
}
MAKER_CODE(ExpressionSLR)
{
   T_Part part = (T_Part)item.MakerParam();
   return make_code_ExpressionS(item, syntax, semantic, part);
}

MAKER_CODE(BegQuestion)
{
   T_Lexeme lexeme = syntax->PopLexeme();
// stack: logic
   if (!syntax->MakeLogic()) return false;
   TExprStackItem& logic = syntax->Top();
   syntax->AddCode(logic.true_label);
   return true;
}

MAKER_CODE(MidQuestion)
{
// stack: logic, left
   TExprStackItem  left  = syntax->TipTop(); 
// stack: logic
   TExprStackItem& logic = syntax->Top(); 
   TNodeLabel *label_end = new TNodeLabel(semantic);
   logic.true_label = label_end;
   TNodeGoTo* go_then = new TNodeGoTo(T_GoTo::tgGoTo,label_end);
   syntax->AddCode(go_then);
   syntax->AddCode(logic.false_label);
   syntax->PushWithoutMade(left); // made == old, before (goto, label)
// stack: logic, left
   return true;
}

MAKER_CODE(Question)
{
// stack: logic, left, righ
   syntax->MakeValue();
   TExprStackItem right = syntax->TipTop(); 
// stack: logic, left
   syntax->MakeValue();
   TExprStackItem left  = syntax->TipTop(); 
// stack: logic
   TExprStackItem logic = syntax->TipTop(); 
// stack: 
   TNodeLabel *label_end = logic.true_label;
   T_BaseType result = CastableBetween(left.type,right.type);
	if (result == btUnknown) { return syntax->error(erUnknownCast); }
   syntax->GenCastable(right.type,result,right.made);
   syntax->GenCastable(left .type,result,left .made);
   syntax->AddCode(label_end);
   syntax->Push(result); // +made
// stack: result
   return true;
}

MAKER_CODE(Binary)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   if (lexeme.Match(T_Symbol::prOrOr) || lexeme.Match(T_Symbol::prAndAnd)) {
      if (!syntax->BinaryLogic(lexeme)) return false;
   } else {
      if (!syntax->BinaryOper(lexeme)) return false;
   }
   return true;
}

MAKER_CODE(Number)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   semantic->GenNumber(lexeme); 
   T_BaseType base_type = (lexeme.group == lexeme.grInteger) ? btCInt : ((lexeme.group == lexeme.grNumber) ? btCDouble : btUnknown);
   syntax->Push(TExprStackItem(base_type, lexeme));
   return true;
}

MAKER_CODE(Ident)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   TNodeDefVar *def_var = semantic->FindIdent(lexeme); 
   if (!def_var) { return syntax->error(erUnknownIdent,lexeme); }
   if (def_var->uninitialized) { return syntax->error(erUninitialized,lexeme); }
   semantic->GenCommand(T_Command::command_PushVar,def_var->offset,def_var->alloc,def_var->BaseType()); 
   syntax->Push(def_var->BaseType());
   return true;
}

MAKER_CODE(BegIndexLL)
{
   TExprStackItem pseudo_range; pseudo_range.param = -1;
   syntax->Push(pseudo_range);
   return true;
}

MAKER_CODE(BegIndexLR)
{
   syntax->Top().param = 1;
// stack: range_1
   return true;
}

MAKER_CODE(IndexLL)
{
   TExprStackItem range = syntax->TipTop();
   TExprStackItem prev_range = syntax->TipTop();
   if (prev_range.param > -1) {
      range.param = prev_range.param + 1;
      syntax->PushWithoutMade(prev_range);
   } else {
      range.param = 1;
   } 
   syntax->PushWithoutMade(range);
   return true;
}

MAKER_CODE(IndexLR)
{
   TExprStackItem range = syntax->TipTop();
   range.param = syntax->Top().param + 1;
   syntax->PushWithoutMade(range);
   return true;
}

MAKER_CODE(EndIndex)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   TNodeDefVar* def = semantic->FindIdent(lexeme);
   if (def) {
      TNodeDefArr *def_arr = dynamic_cast<TNodeDefArr*> (def);
      if (def_arr) {
         int count = syntax->Top().param;
         if (count == def_arr->ranges.size()) {
            for (int i = 0; i < count; i++) {
               TExprStackItem range = syntax->TipTop();  // cast -> const int
            }
            semantic->GenCommand(T_Command::command_PushArr,def_arr->offset,def_arr->alloc,def_arr->BaseType()); 
            syntax->Push(def_arr->BaseType());
         } else {
            return syntax->error(erInvalidType,lexeme);
         }
      } else {
         return syntax->error(erInvalidType,lexeme);
      }
   } else {
      return syntax->error(erUnknownIdent,lexeme);
   }
   return true;
}

MAKER_CODE(Params)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   TFuncProfile profile(lexeme); // IdentFunc
   std::vector<TExprStackItem> items;
   int count = 0;
   if (item.MakerParam()) {  // (params)
      count = syntax->Top().param;
      for (int i = 0; i < count; i++) {
   	   TExprStackItem expr = syntax->TipTop();
         T_BaseType param_type = expr.type;
         profile.Add(param_type);
         items.push_back(expr); 
      }
   }
   TFinder finder(*semantic, TFinder::mfNone);
   TNodeDefFunc* func = semantic->FuncTable.Find(profile, finder);
   if (func) {
      if (item.MakerParam()) {  // (params)
         for (int i = count - 1; i >= 0; i--) {
      	   TExprStackItem& expr = items[count - 1 - i];
            semantic->GenCastable(profile[i], (*func->profile)[i], expr.made);
         }
      }
      profile.result = func->profile->result;
		int number = func->number;
      semantic->GenCommand(T_Command::command_Call,number,0,profile.result); 
      syntax->Push(profile.result);
      return true;
   } else {
      return syntax->error(erUnknownFunc,lexeme);
   }
   return true;
}

MAKER_CODE(Unary)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   syntax->ChangeUnary(lexeme,true);
   TExprStackItem& operand = syntax->Top();
   if ((operand.type == btLogical) && lexeme.Match(T_Symbol::lxNot)) {
      TNodeLabel *label = operand.true_label; operand.true_label = operand.false_label; operand.false_label = label;
   } else {
      if (!syntax->UnaryOper(lexeme)) return false;
   }
   return true;
}

MAKER_CODE(IncDec)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   syntax->ChangeUnary(lexeme,false);
   if (!syntax->UnaryOper(lexeme)) return false;
   return true;
}

MAKER_CODE(Cast)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   syntax->MakeValue();
   const TNodeType *type = TBaseType::BaseType(lexeme,0); // !owner - clear
   if (!syntax->GenCastable(syntax->Top().type,type->BaseType())) return syntax->error(erUnknownCast);
   syntax->Top().type = type->BaseType();
   return true;
}

MAKER_CODE(NodeNull)
{
   syntax->Push(T_BaseType::btVoid);
   return true;
}

MAKER_CODE(Return)
{
   bool value = false;
   if (item.MakerParam() != 0x00) {
      value = true;
   }
   syntax->GenReturn(value);
   return true;
}

MAKER_CODE(Continue)
{
   return syntax->GenBreakContinue(T_Block::tbContinue,syntax->forward);
}

MAKER_CODE(Break)
{
   return syntax->GenBreakContinue(T_Block::tbBreak,syntax->forward);
}

MAKER_CODE(GoTo)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   syntax->GenGoTo(lexeme); // ident
   return true;
}

MAKER_CODE(Label)
{
   T_Lexeme lexeme = syntax->PopLexeme();
	TNodeUserLabel* label = new TNodeUserLabel(lexeme);
   semantic->MakeGoToLabel(label);
   semantic->UserLabelTable.Add(label);
   semantic->ExecStack.Label();
   syntax->AddCode(label);
   return true;
}

// block_labels -> (_one_, do); (_break_, end); (_continue_, while); 
MAKER_CODE(BegDo)
{
   TNodeDo *cycle = new TNodeDo();
   semantic->BlockBegin(cycle);
   TBlock& block_labels = *semantic->Block();

   TNodeLabel *label_do = new TNodeLabel(semantic), *label_while = new TNodeLabel(semantic), *label_end = new TNodeLabel(semantic);
   syntax->AddCode(label_do);
   semantic->ExecStack.Push();
   block_labels.break_label = label_end; block_labels.continue_label = label_while;
   block_labels.one_label = label_do;
   return true;
}

MAKER_CODE(MidDo)
{
   TBlock& block_labels = *semantic->Block();
   TNodeLabel *&label_while = block_labels.continue_label;
   semantic->ExecStack.Down();

   syntax->AddCode(label_while);
   return true;
}

MAKER_CODE(Do)
{
   TBlock& block_labels = *semantic->Block();
   TNodeLabel *&label_end = block_labels.break_label;
   TNodeLabel *&label_do = block_labels.one_label;
   TExprStackItem logic = syntax->TipTop();
   semantic->Reference(logic.true_label,label_do);
   semantic->Reference(logic.false_label,label_end);

   syntax->AddCode(label_end);
   semantic->BlockEnd(NULL,true);
   return true;
}

// block_labels -> (_break_, end); (_continue_, while); 
MAKER_CODE(BegWhile)
{
   TNodeWhile *cycle = new TNodeWhile();
   semantic->BlockBegin(cycle);
   TNodeLabel *label_while = new TNodeLabel(semantic);
   syntax->AddCode(label_while);
   TBlock& block_labels = *semantic->Block();
   block_labels.continue_label = label_while;
   return true;
}

MAKER_CODE(MidWhile)
{
   TExprStackItem logic = syntax->TipTop(); 
   TNodeLabel *label_body = logic.true_label, *label_end = logic.false_label;
   TBlock& block_labels = *semantic->Block();

   semantic->ExecStack.Push();
   block_labels.break_label = label_end;
   syntax->AddCode(label_body);
   return true;
}

MAKER_CODE(While)
{
   TBlock& block_labels = *semantic->Block();
   TNodeLabel *&label_end   = block_labels.break_label;
   TNodeLabel *&label_while = block_labels.continue_label;
   semantic->ExecStack.Pop();
   
   TNodeGoTo* go_cycle = new TNodeGoTo(T_GoTo::tgGoTo,label_while);
   syntax->AddCode(go_cycle);
   syntax->AddCode(label_end);
   semantic->BlockEnd(NULL,true);
   return true;
}

// block_labels -> (_one_, end); (_two_, false); 
MAKER_CODE(BegIf)
{
   TNodeIf *statement = new TNodeIf();
   semantic->BlockBegin(statement);
   return true;
}

MAKER_CODE(Then)
{
// stack: logic(true_label,false_label)
   TExprStackItem logic = syntax->TipTop();

   TNodeIf* block = dynamic_cast<TNodeIf*>(semantic->Block());
   block->trunc = block->size;
   semantic->ExecStack.Push();
   syntax->AddCode(logic.true_label);
   block->two_label = logic.false_label;
// stack:
   return true;
}

MAKER_CODE(Else)
{
// stack:
   TNodeIf* block = dynamic_cast<TNodeIf*>(semantic->Block());
   semantic->BlockTrunc(block->trunc);

   block->then_exec = semantic->ExecStack.Pop();
   semantic->ExecStack.Push();

   TNodeLabel *label_end = new TNodeLabel(semantic);
   TNodeGoTo* go_then = new TNodeGoTo(T_GoTo::tgGoTo,label_end);
   syntax->AddCode(go_then);
   syntax->AddCode(block->two_label);
   block->one_label = label_end;
   return true;
}

MAKER_CODE(If)
{
// stack:
   TNodeIf* block = dynamic_cast<TNodeIf*>(semantic->Block());
   TNodeLabel *label_end = NULL;
   int then_exec, else_exec = 0;
   if (item.MakerParam() == 0x00) { // !else

      then_exec = semantic->ExecStack.Pop();
      label_end = new TNodeLabel(semantic);
      TNodeGoTo* go_then = new TNodeGoTo(T_GoTo::tgGoTo,label_end);
      syntax->AddCode(go_then);
      syntax->AddCode(block->two_label);
   } else {
      label_end = block->one_label;
      then_exec = block->then_exec;
      else_exec = semantic->ExecStack.Pop();
   }
   semantic->ExecStack.Up(then_exec & else_exec);

   syntax->AddCode(label_end);
   semantic->BlockEnd(NULL,true);
   return true;
}

// block_labels -> (_one_, body); (_two_, condition); (_break_, end); (_continue_);
MAKER_CODE(BegFor)
{
   TNodeFor *cycle = new TNodeFor();
   semantic->BlockBegin(cycle);
   return true;
}

MAKER_CODE(PrefFor)
{
   TNodeLabel *label_condition = new TNodeLabel(semantic);

   syntax->AddCode(label_condition);
   TBlock& block_labels = *semantic->Block();
   block_labels.two_label = label_condition;
   return true;
}

MAKER_CODE(ConditionFor)
{
// stack: condition
   TExprStackItem logic = syntax->TipTop();
   TBlock& block_labels = *semantic->Block();
   TNodeLabel *label_body, *label_end;
   if (logic.type == btLogical) { // yes condition
      label_body = logic.true_label; label_end = logic.false_label;
   } else {
      label_body = new TNodeLabel(semantic); label_end = new TNodeLabel(semantic);
   }
   block_labels.one_label = label_body;
   block_labels.break_label = label_end;
   TNodeLabel *label_continue = new TNodeLabel(semantic);
   block_labels.continue_label = label_continue;
   syntax->AddCode(label_continue);
// stack: 
   return true;
}

MAKER_CODE(PostFor)
{
// stack: 
   TBlock& block_labels = *semantic->Block();
   TNodeLabel *&label_condition = block_labels.two_label, *&label_body = block_labels.one_label;
   TNodeGoTo* go_cycle = new TNodeGoTo(T_GoTo::tgGoTo,label_condition); 
   syntax->AddCode(go_cycle);

   syntax->AddCode(label_body);
   semantic->ExecStack.Push();
   return true;
}

MAKER_CODE(For)
{
// stack:
   TBlock& block_labels = *semantic->Block();
   TNodeLabel *&label_continue  = block_labels.continue_label;
   TNodeLabel *&label_end       = block_labels.break_label;
   semantic->ExecStack.Pop();
   TNodeGoTo* go_continue = new TNodeGoTo(T_GoTo::tgGoTo,label_continue);
   syntax->AddCode(go_continue);

   syntax->AddCode(label_end);
   semantic->BlockEnd(NULL,true);
   return true;
}

MAKER_CODE(DefType)
{
   int type = item.MakerParam();
   if (type & 0x08) syntax->PopLexeme(); // &
   T_Lexeme& l = syntax->TopLexeme();
   MakeDefType(l, type);
   return true;
}

MAKER_CODE(Define)
{
   T_Lexeme lexeme_type, lexeme_ident;
   if (!(syntax->syntax_lexeme & T_Grammar::slSyntax) && !item.MakerParam()) { // NR
      lexeme_ident = syntax->PopLexeme();
      lexeme_type  = syntax->PopLexeme();
      syntax->push_lexeme(lexeme_ident);
   } else {
      lexeme_type = syntax->PopLexeme();
   }
   TNodeType *type = syntax->BaseType(lexeme_type);
   TExprStackItem def(type);
   syntax->Push(def);
   return true;
}

MAKER_CODE(EndDefine)
{
   TExprStackItem define = syntax->TipTop();
   return true;
}

MAKER_CODE(DefArray)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   bool yes_ref = syntax->CountLexemes() && syntax->TopLexeme().Match(T_Symbol::lxAnd);
   if (yes_ref) 
      syntax->PopLexeme();
   TNodeType *type_arr = (TNodeType*)syntax->Top().node;
   if (yes_ref) {
      type_arr = TBaseType::Or(type_arr, T_BaseType::btReference);
   }
   TNodeDefArr *arr = new TNodeDefArr(type_arr,lexeme,NULL);
   semantic->AddDefVar(arr);
   return true;
}

MAKER_CODE(DRange)
{
   TNodeDefArr *arr = (TNodeDefArr*)semantic->GetDefVar();
   TDefArrRangeItem range;
   TExprStackItem index = syntax->TipTop();
   if ((index.type == btCInt) && (index.lexeme.group == T_Lexeme::grInteger)) {
      range.range = syntax->Integer(index.lexeme);
   	if (range.range < 1) { syntax->error(erRanges); range.range = -2; }
   } else {
      range.range = -2;
      if (!semantic->GenCastable(index.type, btCInt)) {
         return syntax->error(erUnknownCast);
      }
   }
   range.made = syntax->made();
   arr->ranges.push_back(range);
   return true;
}

MAKER_CODE(DefArrD1AEmpty)
{
   TNodeDefArr *arr = (TNodeDefArr*)semantic->GetDefVar();
   TDefArrRangeItem range;
   range.range = -1;
   syntax->AddCode(new TNodeCommand(T_Command::command_PushInt,range.range,0,btCInt));
   range.made = syntax->made();
   arr->ranges.push_back(range);
   return true;
}

MAKER_CODE(EndRanges)
{
   TNodeDefArr *arr = (TNodeDefArr*)semantic->GetDefVar();
   arr->ranges.calc();
   int count = arr->ranges.count();
   semantic->GenCommand(T_Command::command_NewArr,count,arr->alloc,arr->BaseType()); 
   return true;
}

MAKER_CODE(BegAInit)
{
   TNodeDefArr *arr = (TNodeDefArr*)semantic->GetDefVar();
   if (arr->ranges.variable_range()) { return syntax->error(erInvalidInit); }
   return true;
}

MAKER_CODE(AInitItem)
{
   TNodeDefArr *arr = (TNodeDefArr*)semantic->GetDefVar();
   if (!arr->ranges.next()) return syntax->error(erInvalidInit);
   syntax->MakeValue();
   TExprStackItem operand = syntax->TipTop();
   if (!semantic->GenCastable(operand.type, TBaseType::Const(arr->BaseType()))) {
      return syntax->error(erUnknownCast);
   }
   semantic->GenCommand(T_Command::command_PushInt,arr->ranges.offset(),0,btCInt);
   semantic->GenCommand(T_Command::command_InitArr,arr->offset,arr->alloc,arr->BaseType()); 
   return true;
}

MAKER_CODE(BegInitial)
{
   TNodeDefArr *arr = (TNodeDefArr*)semantic->GetDefVar();
   int &level = arr->ranges.level;
   if (item.MakerParam()) { // !empty
      if ((++level) > arr->ranges.count()) return syntax->error(erInvalidInit);
   } else {
      arr->ranges.jump(level);
   }
   return true;
}

MAKER_CODE(EndInitial)
{
   TNodeDefArr *arr = (TNodeDefArr*)semantic->GetDefVar();
   int &level = arr->ranges.level;
   arr->ranges.jump(--level);
   return true;
}

MAKER_CODE(EndAInit)
{
   T_Lexeme lexeme_assign = syntax->PopLexeme();
   TNodeDefArr *arr = (TNodeDefArr*)semantic->GetDefVar();
   if (arr->ranges.unknown_range()) {
      arr->ranges[0].range = arr->ranges[0].index;
      if (arr->ranges.count() == 1) arr->ranges[0].range++;
      TNodeCommand* command = (TNodeCommand*)semantic->GetCommand(arr->ranges[0].made - 1);
      command->param = arr->ranges[0].range;
   }
   return true;
}

MAKER_CODE(DefIdent)
{
   T_Lexeme lexeme = syntax->PopLexeme();
   bool yes_ref = syntax->CountLexemes() && syntax->TopLexeme().Match(T_Symbol::lxAnd);
   if (yes_ref) syntax->PopLexeme();
   TNodeType *type_ident = (TNodeType*)syntax->Top().node;
   if (yes_ref) {
      type_ident = TBaseType::Or(type_ident, T_BaseType::btReference);
   }
   TNodeDefVar *var = new TNodeDefVar(type_ident,lexeme);
   semantic->AddDefVar(var);
   semantic->GenCommand(T_Command::command_NewVar,var->offset,var->alloc,var->BaseType()); 
   return true;
}

MAKER_CODE(BegDefVarAssign)
{
   TNodeDefVar *var = semantic->GetDefVar();
   if (!var) return false;
   semantic->GenCommand(T_Command::command_PushVar,var->offset,var->alloc,var->BaseType()); 
   var->uninitialized = true;
   syntax->Push(TBaseType::Tilda(var->BaseType(),T_BaseType::btConst));   // left
   return true;
}

MAKER_CODE(DefVarAssign)
{
// stack: var, assign
   TNodeDefVar *var = semantic->GetDefVar();
   T_Lexeme lexeme_assign = syntax->PopLexeme();
   if (!syntax->BinaryOper(lexeme_assign)) return false;
   semantic->GenPop(1);
   syntax->Pop();
   var->uninitialized = false;
   return true;
}

MAKER_CODE(PushDef)
{
   TNodeDefVar *var = semantic->GetDefVar();
   semantic->GenCommand(T_Command::command_PushVar,var->offset,var->alloc,var->BaseType()); 
   syntax->Push(var->BaseType());
   if (!syntax->MakeLogic()) return false;
   return true;
}

MAKER_CODE(DefParVar)
{
// lexemes: type, ident
   T_Lexeme lexeme = syntax->PopLexeme();
   T_Lexeme l = syntax->PopLexeme();
   TNodeType *type = syntax->BaseType(l);
   TNodeDefVar *param = new TNodeDefVar(type,lexeme);
   semantic->AddDefVar(param);
   TNodeDefFunc *function = dynamic_cast<TNodeDefFunc*>(semantic->Block(tbFunc));
   TFuncProfile &profile = *function->profile; 
   profile.Add(param->BaseType());
   return true;
}

MAKER_CODE(DefParArr)
{
// lexemes: type, ident
   T_Lexeme lexeme = syntax->PopLexeme();
   T_Lexeme l = syntax->PopLexeme();
   TNodeType *type = syntax->BaseType(l);
   TNodeDefArr *param = new TNodeDefArr(type,lexeme,NULL);
   semantic->AddDefVar(param);
   TNodeDefFunc *function = dynamic_cast<TNodeDefFunc*>(semantic->Block(tbFunc));
   TFuncProfile &profile = *function->profile; 
   profile.Add(param->BaseType());
   return true;
}

MAKER_CODE(BegParVarAssign)
{
   TNodeDefVar *var = semantic->GetDefVar();
   semantic->GenCommand(T_Command::command_PushVar,var->offset,var->alloc,var->BaseType()); 
   var->uninitialized = true;
   syntax->Push(TBaseType::Tilda(var->BaseType(),T_BaseType::btConst));
   return true;
}

MAKER_CODE(ParVarAssign)
{
   T_Lexeme lexeme_assign = syntax->PopLexeme();
   TNodeDefVar *var = semantic->GetDefVar();
   const T_Lexeme &lexeme = lexeme_assign;
   if (!syntax->BinaryOper(lexeme)) return false;
   semantic->GenPop(1);
   syntax->Pop();
   var->uninitialized = false;
   return true;
}

MAKER_CODE(FuncIdent)
{
// lexemes: type, ident
   T_Lexeme lexeme_ident = syntax->PopLexeme();
   T_Lexeme lexeme_type = syntax->PopLexeme();
   TNodeType *type = syntax->BaseType(lexeme_type);
   TNodeDefFunc *function = new TNodeDefFunc(type,lexeme_ident,NULL,NULL);
//   semantic->AddCode(function);
   TFuncProfile &profile = *(function->profile = new TFuncProfile(lexeme_ident));
   semantic->BlockBegin(function);
   profile.result = function->BaseType();
   return true;
}

MAKER_CODE(EndParams)
{
   TNodeDefFunc *function = dynamic_cast<TNodeDefFunc*>(semantic->Block());
   function->SetBody(new TNodeNull());
   semantic->AddDefFunc(function);
   semantic->ExecStack.Push();
   return true;
}

MAKER_CODE(BodyFunc)
{
   TNodeDefFunc *function = dynamic_cast<TNodeDefFunc*>(semantic->Block());
   if (item.MakerParam() < 0x02) {
      if (item.MakerParam() == 0x01) {
         function->SetBody(new TNodeNull());
      }
      semantic->AddDefFunc(function);
   }
   int exec_mode = semantic->ExecStack.Pop();
   semantic->ExecStack.Push();
   if (item.MakerParam() > 0x00) {
      if (!(exec_mode & T_ExecMode::meRestituer)) {
         if ((TBaseType::Tilda(function->BaseType(),T_BaseType::btStatic) != T_BaseType::btVoid) && (function->BaseType() != T_BaseType::btUnknown)) {
            syntax->error(erNoReturn);
         }
      }
   
      semantic->UserGoToTable .Verify();
      semantic->UserLabelTable.Verify();
      semantic->UserGoToTable .clear();
      semantic->UserLabelTable.clear();
   
      semantic->GenCommand(T_Command::command_Exit,function->number,0,T_BaseType::btVoid);
   }
   semantic->BlockEnd(NULL);
   return true;
}
