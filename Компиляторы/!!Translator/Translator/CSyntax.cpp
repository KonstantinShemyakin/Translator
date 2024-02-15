
#include "stdafx.h"
#include "CSyntax.h"
#include "TSemantic.h"

// --------------------------- CSyntax ---------------------------

void CSyntax::clear(TNode* node)
{
   if (node) { node->clear(); } 
}

bool CSyntax::Assign()
{
   if (!Question()) return false;
	if (Match(T_Symbol::prAssign)) {
      T_Lexeme lexeme = forward;
	   if (!Assign()) return false;
      if (!BinaryOper(lexeme)) return false;
	}
   return true;
}

bool CSyntax::Question()
{
   if (!Binary(T_Symbol::prOrOr)) return false;
	if (Match(T_Symbol::prQuestion)) {
      if (!MakeLogic()) return false;
      TExprStackItem logic = TipTop(); 
      AddCode(logic.true_label);
	   if (!Question()) return false;
      TNodeLabel *label_end = new TNodeLabel(semantic);
      TNodeGoTo* go_then = new TNodeGoTo(T_GoTo::tgGoTo,label_end);
      AddCode(go_then);
		if (!MatchMust(T_Symbol::lxColon)) return false;
      AddCode(logic.false_label);
	   if (!Question()) return false;
      MakeValue();
      TExprStackItem right = TipTop(); 
      MakeValue();
      TExprStackItem left  = TipTop(); 
      T_BaseType result = CastableBetween(left.type,right.type);
	   if (result == btUnknown) { return error(erUnknownCast); }
      GenCastable(right.type,result,right.made);
      GenCastable(left .type,result,left .made);
      AddCode(label_end);
      Push(result);
	}
   return true;
}

bool CSyntax::Unary()
{
	if (Match(T_Symbol::prUnary) || Match(T_Symbol::prTerm) || Match(T_Symbol::prIncDec)) {
      T_Lexeme lexeme = forward;
      ChangeUnary(lexeme,true);
      if (!Unary()) return false;
      TExprStackItem& operand = Top();
      if ((operand.type == btLogical) && lexeme.Match(T_Symbol::lxNot)) {
         TNodeLabel *label = operand.true_label; operand.true_label = operand.false_label; operand.false_label = label;
      } else {
         if (!UnaryOper(lexeme)) return false;
      }
	   return true;
	}
   T_ScanStore store; Store(store);
   if (Match(T_Symbol::lxLeftBracket)) {
   	int detail = Match(T_Lexeme::W_Type::rwConst) ? 0x02 : 0x00;
      if (Match(T_Lexeme::W_Type::rwDefine)) {
         T_Lexeme lexeme = forward;
         if (Match(T_Symbol::lxRightBracket)) {
            if (!Unary()) return false;
            MakeValue();
            const TNodeType *type = TBaseType::BaseType(lexeme,detail);
            if (!GenCastable(Top().type,type->BaseType(),Top().made)) return error(erUnknownCast);
            Top().type = type->BaseType();
	         return true;
         }
      } else {
         if (detail) return error_true(erUnknownCast);
      } 
	}
   Restore(store);
   bool ret = Primary(); if (!ret) return false;
	while (Match(T_Symbol::prIncDec)) {
      T_Lexeme lexeme = forward;
      ChangeUnary(lexeme,false);
      if (!UnaryOper(lexeme)) return false;
   }
   return true;
}

bool CSyntax::Index(const T_Lexeme &lexeme)
{
   TNodeDefVar* def = semantic->FindIdent(lexeme);
   int  count = 0;
   while (Match(T_Symbol::lxLeftScrape)) {
   	if (!Expressions(psValue)) return false;
      Pop(); // cast -> const int
      count++;
      if (!MatchMust(T_Symbol::lxRightScrape)) return false;
   }
   if (def) {
      TNodeDefArr *def_arr = dynamic_cast<TNodeDefArr*> (def);
      if (def_arr && (count == def_arr->ranges.count())) {
         semantic->GenCommand(T_Command::command_PushArr,def_arr->offset,def_arr->alloc,def_arr->BaseType()); 
         Push(def_arr->BaseType());
      } else {
         return error(erInvalidType,lexeme);
      }
   } else {
      return error(erUnknownIdent,lexeme);
   }
   return true;
}

bool CSyntax::Call(const T_Lexeme &lexeme)
{
   bool ret = true;
   TFuncProfile profile(lexeme);
   std::vector<int> mades;
	if (!Match(T_Symbol::lxRightBracket)) {
	   do {
			if (!Assign()) { return false; }
         MakeValue();
         TExprStackItem& param = Top();
         if ((param.type == btUnknown) || (param.type == btVoid)) {
            return error(erUnknownParam);
         }
         profile.Add(param.type); Top(); mades.push_back(made());
		} while (Match(T_Symbol::lxComma));
	   if (!MatchMust(T_Symbol::lxRightBracket)) { return false; }
	}
   TFinder finder(*semantic, TFinder::mfNone);
   TNodeDefFunc* func = semantic->FuncTable.Find(profile, finder);
   if (func) {
      profile.result = func->profile->result;
      for (int i = (int)mades.size() - 1; i >= 0; i--) {
         semantic->GenCastable(profile[i], (*func->profile)[i], mades[i]);
      }
		int number = func->number;
      semantic->GenCommand(T_Command::command_Call,number,0,profile.result); 
      Push(profile.result);
   } else {
      ret = error(erUnknownFunc,lexeme);
   }
   return ret;
}

bool CSyntax::Primary()
{
   if (Match(T_Lexeme::grIdent)) {
      T_Lexeme lexeme = forward;
		if (Match(T_Symbol::lxLeftBracket)) {
         bool ret = Call(lexeme);
			return ret;
		}
		if (MatchSpot(T_Symbol::lxLeftScrape)) {
         bool ret = Index(lexeme);
			return ret;
		}
      TNodeDefVar *def_var = semantic->FindIdent(lexeme); 
      if (!def_var) { return error(erUnknownIdent,lexeme); }
      if (def_var->uninitialized) { return error(erUninitialized,lexeme); }
      semantic->GenCommand(T_Command::command_PushVar,def_var->offset,def_var->alloc,def_var->BaseType()); 
      Push(def_var->BaseType());
   	return true;
   	}
   if (Match(T_Lexeme::grInteger) || Match(T_Lexeme::grNumber)) {
      T_Lexeme lexeme = forward;
      semantic->GenNumber(lexeme); 
      T_BaseType base_type = (lexeme.group == lexeme.grInteger) ? btCInt : ((lexeme.group == lexeme.grNumber) ? btCDouble : btUnknown);
      Push(TExprStackItem(base_type, lexeme));
		return true;
   }
   if (Match(T_Symbol::lxLeftBracket)) {
      if (!Expressions() || !Match(T_Symbol::lxRightBracket)) return false;
		return true;
      }
   if (Match(T_Lexeme::W_Type::rwDefine)) {
      T_Lexeme lexeme = forward;
	   if (!MatchMust(T_Symbol::lxLeftBracket) || !Expressions(psValue) || !MatchMust(T_Symbol::lxRightBracket)) return false;
      const TNodeType *type = TBaseType::BaseType(lexeme,0);
      if (!GenCastable(Top().type,type->BaseType(),Top().made)) return error(erUnknownCast,lexeme);
      Top().type = type->BaseType();
		return true;
   }
   return error(erPrimary);
}

bool CSyntax::Binary(T_Symbol::T_Priority priority)
{
   if ((priority + 1) < T_Symbol::prUnary) {
      if (!Binary(T_Symbol::T_Priority(priority + 1))) return false;
   } else {
      if (!Unary()) return false;
   }
   while (Match(priority)) {
      T_Lexeme lexeme = forward;
      if ((priority + 1) < T_Symbol::prUnary) {
         if (!Binary(T_Symbol::T_Priority(priority + 1))) return false;
      } else {
         if (!Unary()) return false;
      }
      if ((priority == T_Symbol::prOrOr ) || (priority == T_Symbol::prAndAnd)) {
         if (!BinaryLogic(lexeme)) return false;
      } else {
         if (!BinaryOper(lexeme)) return false;
      }
   }
   return true;
}

bool CSyntax::Expressions(T_Part part) // !param_list
{
   do {
      if (!Assign()) return false;
      const TExprStackItem& result = Top();
      if (MatchSpot(T_Symbol::lxComma)) { // !last
         if (result.type == btLogical) {
            AddCode(result.false_label); AddCode(result.true_label);
         } else if (result.value()) {
            semantic->GenPop(1);
         }
         Pop();
      } else if (part != psNone) { // last && !primary
         if ((part & psIfGoTo)) { 
            if (!MakeLogic()) return false;
         } else if (part & psValue) {
            MakeValue();
            if (!Top().value()) return false;
         } else {
            if (result.value()) {
               semantic->GenPop(1);
            }
            Pop();
         }
      }
   } while (Match(T_Symbol::lxComma));
   return true;
}

#define IMPOSSIBLE  semantic->impossible(NULL);
#define IMPOSSIBLE_MODE(MODE)  semantic->impossible(NULL,MODE);

bool CSyntax::Statement(T_Part part)
{
	if (Match(T_Symbol::lxSemicolon)) return !(part & T_Part::psNoSemicolon);

   if (part & T_Part::psDefine) {
      T_Lexeme l;
      int def = SCDefine(l,0x26); // -1 - error, 0, 0x01 - define, 0x02 - const, 0x04 - static, 0x20 - void
		if (def < 0) return false;
 		if (def) {
         forward = l;
         IMPOSSIBLE_MODE(0x01)
		   return Define(part,def);
		}
	}
   if (part & T_Part::psStatement) {
      T_Lexeme lexeme;
      T_ScanStore store; Store(store);
      if (Match(lexeme,T_Lexeme::grIdent) && Match(T_Symbol::lxColon)) {
			TNodeUserLabel* label = new TNodeUserLabel(lexeme);
         semantic->MakeGoToLabel(label);
         semantic->UserLabelTable.Add(label);
         semantic->ExecStack.Label();
         AddCode(label);
         return Statement(T_Part::psLabel);
      } 
      Restore(store);
      if (Match(T_Lexeme::W_Type::rwFor))      { IMPOSSIBLE return For(); }
      if (Match(T_Lexeme::W_Type::rwWhile))    { IMPOSSIBLE return While(); }
      if (Match(T_Lexeme::W_Type::rwIf))       { IMPOSSIBLE return If(); }
      if (Match(T_Lexeme::W_Type::rwDo))       { IMPOSSIBLE return Do(); }
      if (Match(T_Lexeme::W_Type::rwContinue)) { IMPOSSIBLE return BreakContinue(T_Block::tbContinue); }
      if (Match(T_Lexeme::W_Type::rwBreak))    { IMPOSSIBLE return BreakContinue(T_Block::tbBreak); }
      if (Match(T_Lexeme::W_Type::rwGoTo))     { IMPOSSIBLE return GoTo(); }
      if (Match(T_Lexeme::W_Type::rwReturn))   { IMPOSSIBLE return Return(); }
      if (Match(T_Lexeme::W_Type::rwSwitch))   { IMPOSSIBLE return Switch(); }
	}
   if (part & T_Part::psCompaund) {
      if (Match(T_Symbol::lxLeftCramp)) return Compaund();
	}

   if (part & T_Part::psExpression) {
      IMPOSSIBLE_MODE(0x01)
      return Expressions(part) && ((part & T_Part::psNoSemicolon) || Match(T_Symbol::lxSemicolon));
	}

   return false;
}

bool CSyntax::Compaund()
{
   TNodeStatements *compaund = new TNodeStatements();
   semantic->BlockBegin(compaund);
   while (!Match(T_Symbol::lxRightCramp)) {
      if (!Statement(T_Part::psBody)) return false;
   }
   semantic->BlockEnd(NULL,true);
   return true;
}

bool CSyntax::Statements(T_Part part)
{
   TNodeStatements *statements = new TNodeStatements();
   semantic->BlockBegin(statements);
   while (!Match(T_Lexeme::grEof)) {
      if (!Statement(part)) return false;
   }
   semantic->BlockEnd(NULL,true);
   return true;
}

bool CSyntax::Translate()
{
   bool ret = Statements(T_Part::psMain);
   return ret;
}

bool CSyntax::DefineParam(TNodeDefVar* &par)
{
   T_Lexeme lexeme;
   int def = SCDefine(lexeme, 0x02); // -1 - error, 0, 0x01 - define, 0x02 - const, 0x08 - &
	if (def < 0) return false;
   if (!def) return error(erDefine);
   T_Lexeme ident = (Match(T_Lexeme::grIdent) ? forward : empty_ident);
   TNodeType *type = BaseType(lexeme,def); // owner + clear
	if (MatchSpot(T_Symbol::lxLeftScrape)) {
      if (def & 0x08) { return error_true(erDefArr); } // reference ???
      TNodeDefArr *param = new TNodeDefArr(type,ident,NULL);
      int scrape = 0;
   	while (Match(T_Symbol::lxLeftScrape)) {
   	   if (!scrape++ && Match(T_Symbol::lxRightScrape)) continue;
   		if (!Assign()) { clear(param); return false; }
         Pop();
         TDefArrRangeItem item;
         param->ranges.push_back(item);
   	   if (!MatchMust(T_Symbol::lxRightScrape)) { clear(param); return false; }
   	}
      if (Match(T_Symbol::lxAssign)) {
     		if (!Assign()) { clear(param); return false; }
      } else if (param->BaseType() & T_BaseType::btReference) {
         error(erUninitialized);
      }
      par = param;
      return true;
   }
   TNodeDefVar *param = new TNodeDefVar(type,ident);
   if (Match(T_Symbol::lxAssign)) {
  		if (!Assign()) { clear(param); return false; }
   } else if (param->BaseType() & T_BaseType::btReference) {
      error(erUninitialized);
   }
   par = param;
   return true;
}

bool CSyntax::Function(TNodeDefFunc *function, int &def)
{
   TFuncProfile &profile = *(function->profile = new TFuncProfile(function->Lexeme()));
   semantic->BlockBegin(function);
   profile.result = function->BaseType();
	if (!Match(T_Symbol::lxRightBracket)) {
      do {
         TNodeDefVar *param = NULL;
         if (!DefineParam(param)) { clear(function); return false; }
         semantic->AddDefVar(param); 
         profile.Add(param->BaseType());
      } while (Match(T_Symbol::lxComma));
      if (!MatchMust(T_Symbol::lxRightBracket)) { clear(function); return false; }
   }
   bool yes_body = Match(T_Symbol::lxLeftCramp);
   if (yes_body) {
      function->SetBody(new TNodeNull());
   }
   semantic->AddDefFunc(function);
   semantic->ExecStack.Push();
   if (yes_body) {
      if (!Compaund()) return false;
      def = -2;
   }
   int exec_mode = semantic->ExecStack.Pop();
   if (def == -2) {
      if (!(exec_mode & T_ExecMode::meRestituer)) {
         if ((TBaseType::Tilda(function->BaseType(),T_BaseType::btStatic) != T_BaseType::btVoid) && (function->BaseType() != T_BaseType::btUnknown)) {
            error(erNoReturn);
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

bool CSyntax::Initializer(TNodeDefArr &arr, int level)
{
   if (!MatchMust(T_Symbol::lxLeftCramp)) return false;
   if (!Match(T_Symbol::lxRightCramp)) {
      do {
         if (MatchSpot(T_Symbol::lxLeftCramp)) {
            if ((level + 1) >= arr.ranges.count()) return error(erInvalidInit);
            if (!Initializer(arr, level + 1)) return false;
         } else {
            if (!arr.ranges.next()) return error(erInvalidInit);
            if (!Assign()) return false;
            MakeValue();
            TExprStackItem operand = TipTop();
      		if (!semantic->GenCastable(operand.type, TBaseType::Const(arr.BaseType()))) {
               return error(erUnknownCast);
   	   	}
            semantic->GenCommand(T_Command::command_PushInt,arr.ranges.offset(),0,btCInt);
            semantic->GenCommand(T_Command::command_InitArr,arr.offset,arr.alloc,arr.BaseType()); 
         }
      } while (Match(T_Symbol::lxComma));
      if (!MatchMust(T_Symbol::lxRightCramp)) return false;
   }
   arr.ranges.jump(level);
   return true;
}

bool CSyntax::Array(TNodeDefArr *arr)
{
   int scrape = 0;
   bool unknown_range = false;
   int first_range_made = 0;
   while (Match(T_Symbol::lxLeftScrape)) {
      TDefArrRangeItem item;
      if (!scrape++ && Match(T_Symbol::lxRightScrape)) {
         item.range = -1;
         arr->ranges.push_back(item);
         AddCode(new TNodeCommand(T_Command::command_PushInt,item.range,0,btCInt));
         first_range_made = made();
         unknown_range = true;
         continue;
      }
   	if (!Assign()) { clear(arr); return false; }
      TExprStackItem range = TipTop();
      if ((range.type == btCInt) && (range.lexeme.group == T_Lexeme::grInteger)) {
         item.range = Integer(range.lexeme);
      	if (item.range < 1) { error(erRanges); item.range = -2; }
      } else {
         item.range = -2;
         if (!semantic->GenCastable(range.type, btCInt)) {
            return error(erUnknownCast);
         }
      }
      arr->ranges.push_back(item);
      if (!MatchMust(T_Symbol::lxRightScrape)) { clear(arr); return false; }
   }
   arr->ranges.calc();
   semantic->AddDefVar(arr);
   int count = scrape;
   semantic->GenCommand(T_Command::command_NewArr,count,arr->alloc,arr->BaseType()); 
   if (Match(T_Symbol::lxAssign)) {
      if (arr->ranges.variable_range()) { clear(arr); return error(erInvalidInit); }
      if (Initializer(*arr,0)) {
         if (unknown_range) {
            arr->ranges[0].range = arr->ranges[0].index;
            if (arr->ranges.count() == 1) arr->ranges[0].range++;
            TNodeCommand* command = (TNodeCommand*)GetCommand(first_range_made - 1);
            command->param = arr->ranges[0].range;
         }
      } else {
         clear(arr);
         return error(erInvalidInit);
      }
   } else if (arr->BaseType() & T_BaseType::btConstReference) {
      error(erUninitialized,arr->Lexeme());
   }
   return true;
}

int CSyntax::DefineItem(const T_Lexeme &lexeme, T_Part part, int detail, TNode* &node) // 0x04 - static, 0x02 - const
{
	if (Match(T_Symbol::lxAnd)) detail |= 0x08; // reference
   if (!Match(T_Lexeme::grIdent)) return error(erNoIdent);
   TNodeType *type = BaseType(lexeme,detail);
   T_Lexeme ident = forward;

   if (Match(T_Symbol::lxLeftBracket)) {
      if (!(part & psDefFunc)) { return error(erDefFunc); }
      TNodeDefFunc *func = new TNodeDefFunc(type,ident,NULL,NULL);
      node = func;
      return -1;
   }
   if (lexeme.Match(T_Lexeme::W_Type::rwVoid)) { return error(erDefVoid); }

	if (MatchSpot(T_Symbol::lxLeftScrape)) {
		if ((detail & 0x08) || (part & T_Part::psOneDef)) { return error(erDefArr); } // reference
      TNodeDefArr *arr = new TNodeDefArr(type, ident, NULL);
      return Array(arr);
   }

   TNodeDefVar *var = new TNodeDefVar(type, ident);
   semantic->AddDefVar(var);
   semantic->GenCommand(T_Command::command_NewVar,var->offset,var->alloc,var->BaseType()); 

   if (Match(T_Symbol::lxAssign)) {
      T_Lexeme lexeme = forward;
      semantic->GenCommand(T_Command::command_PushVar,var->offset,var->alloc,var->BaseType()); 
      var->uninitialized = true;
      Push(TBaseType::Tilda(var->BaseType(),T_BaseType::btConst));
      if (!Assign()) { clear(var); return false; }
      if (!BinaryOper(lexeme)) { clear(var); return false; }
      semantic->GenPop(1);
      Pop();
      var->uninitialized = false;
   } else if (var->BaseType() & T_BaseType::btConstReference) {
      error(erUninitialized,ident);
   }
   if (part & T_Part::psOneDef) { // condition
      semantic->GenCommand(T_Command::command_PushVar,var->offset,var->alloc,var->BaseType()); 
      Push(var->BaseType());
      if (!MakeLogic()) return false;
   }
   return true;
}

bool CSyntax::Define(T_Part part, int constant) // 0x02 - static, 0x01 - const
{
   T_Lexeme lexeme = forward;
   int count = 0, def;
   TNode* node = NULL;
   do {
      def = DefineItem(lexeme, part, constant, node);
      if (!def) return false;
      count++;
      if (part & T_Part::psOneDef) break;
   } while (Match(T_Symbol::lxComma));
   if ((count == 1) && (def == -1)) {
      if (!Function(dynamic_cast<TNodeDefFunc*>(node),def)) return false;
   }
   return (part & T_Part::psNoSemicolon) || Match(T_Symbol::lxSemicolon) || (def == -2);
}

bool CSyntax::For()
{
   TNodeFor *cycle = new TNodeFor();
   semantic->BlockBegin(cycle);
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   if (!Statement(T_Part::psForBeg)) return false;  // prefix

   TNodeLabel *label_condition = new TNodeLabel(semantic), *label_body, *label_end;
   TNodeLabel *label_continue = new TNodeLabel(semantic), *&label_break = label_end;

   AddCode(label_condition);
   int before_condition = made();
   if (!Statement(T_Part::psForExpr)) return false; // condition
   int after_condition = made();
   if (after_condition > before_condition) {        // yes condition
      TExprStackItem logic = TipTop();
      label_body = logic.true_label; label_end = logic.false_label;
   } else {
      label_body = new TNodeLabel(semantic); label_end = new TNodeLabel(semantic);
   }

   AddCode(label_continue);
   if (!Match(T_Symbol::lxRightBracket)) {
      if (!Expressions(psExpression)) return false;  // postfix
      if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   }
   TNodeGoTo* go_cycle = new TNodeGoTo(T_GoTo::tgGoTo,label_condition); 
   AddCode(go_cycle);

   AddCode(label_body);
   semantic->ExecStack.Push();
   cycle->BreakContinueLabel(label_break,label_continue);
   if (!Statement(T_Part::psBody)) return false;    // body
    
   semantic->ExecStack.Pop();
   TNodeGoTo* go_continue = new TNodeGoTo(T_GoTo::tgGoTo,label_continue);
   AddCode(go_continue);

   AddCode(label_end);
   semantic->BlockEnd(NULL,true);
   return true;
}

bool CSyntax::While()
{
   TNodeWhile *cycle = new TNodeWhile();
   semantic->BlockBegin(cycle);
   TNodeLabel *label_while = new TNodeLabel(semantic);
   AddCode(label_while);
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   if (!Statement(T_Part::psCondition)) return false;
   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   TExprStackItem logic = TipTop(); 
   TNodeLabel *label_body = logic.true_label, *label_end = logic.false_label;

   semantic->ExecStack.Push();
   cycle->BreakContinueLabel(label_end,label_while);
   AddCode(label_body);
   if (!Statement(T_Part::psBody)) return false;
    
   semantic->ExecStack.Pop();
   
   TNodeGoTo* go_cycle = new TNodeGoTo(T_GoTo::tgGoTo,label_while);
   AddCode(go_cycle);
   AddCode(label_end);
   semantic->BlockEnd(NULL,true);
   return true;
}

bool CSyntax::Do()
{
   TNodeDo *cycle = new TNodeDo();
   semantic->BlockBegin(cycle);

   TNodeLabel *label_do = new TNodeLabel(semantic), *label_while = new TNodeLabel(semantic), *label_end = new TNodeLabel(semantic);
   AddCode(label_do);
   semantic->ExecStack.Push();
   cycle->BreakContinueLabel(label_end,label_while);
   if (!Statement(T_Part::psBody)) return false;
    
   semantic->ExecStack.Down();

   AddCode(label_while);
   if (!Match(T_Lexeme::W_Type::rwWhile)) return false;
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   if (!Statement(T_Part::psCondition)) return false;
   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   TExprStackItem logic = TipTop(); 
   semantic->Reference(logic.true_label,label_do);
   semantic->Reference(logic.false_label,label_end);

   AddCode(label_end);
   semantic->BlockEnd(NULL,true);
   return MatchMust(T_Symbol::lxSemicolon);
}

bool CSyntax::If()
{
   TNodeIf *statement = new TNodeIf();
   semantic->BlockBegin(statement);

   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   if (!Statement(T_Part::psCondition)) return false;    // condition
   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   TExprStackItem logic = TipTop(); 

   statement->trunc = statement->size;
   semantic->ExecStack.Push();
   AddCode(logic.true_label);
   if (!Statement(T_Part::psBody)) return false;    // then
   semantic->BlockTrunc(statement->trunc);

   int then_exec = semantic->ExecStack.Pop();
   semantic->ExecStack.Push();

   TNodeLabel *label_end = new TNodeLabel(semantic);
   TNodeGoTo* go_then = new TNodeGoTo(T_GoTo::tgGoTo,label_end);
   AddCode(go_then);
   AddCode(logic.false_label);
   if (Match(T_Lexeme::W_Type::rwElse)) {
      if (!Statement(T_Part::psBody)) return false; // else
   }
   int else_exec = semantic->ExecStack.Pop();
   semantic->ExecStack.Up(then_exec & else_exec);

   AddCode(label_end);
   semantic->BlockEnd(NULL,true);
   return true;
}

bool CSyntax::GoTo()
{
   T_Lexeme lexeme = forward; // goto
   if (!Match(T_Lexeme::grIdent)) return error(erNoIdent);
   GenGoTo(forward); // ident
   return MatchMust(T_Symbol::lxSemicolon);
}

bool CSyntax::BreakContinue(T_Block rate)
{
   semantic->ExecStack.GoTo();
   return GenBreakContinue(rate,forward) && MatchMust(T_Symbol::lxSemicolon);
}

bool CSyntax::Return()
{
   bool value = false;
	if (!Match(T_Symbol::lxSemicolon)) {
      if (!Expressions(psValue)) return false;
      MakeValue();
      value = true;
   }
   GenReturn(value);
   return !value || MatchMust(T_Symbol::lxSemicolon);
}

bool CSyntax::Switch()
{
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   if (!Statement(T_Part::psCondition)) return false;
   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   if (!MatchMust(T_Symbol::lxLeftCramp)) return false;
   int case_count = 0, default_count = 0;
   do {
      while (Match(T_Lexeme::W_Type::rwCase) || Match(T_Lexeme::W_Type::rwDefault)) {
         if (forward.Match(T_Lexeme::W_Type::rwCase)) {
            case_count++; 
            if (!Question()) return error(erNoInteger);;
         } else {
            if (default_count++) return false;
         } 
         if (!MatchMust(T_Symbol::lxColon)) return false;
      }
      while (!MatchSpot(T_Lexeme::W_Type::rwCase) && !MatchSpot(T_Lexeme::W_Type::rwDefault) && !MatchSpot(T_Symbol::lxRightCramp)) {
         if (!Statement(T_Part::psCase)) return false;
      }
   } while (!Match(T_Symbol::lxRightCramp));
   if (!case_count || (default_count > 1)) return false;
   return true;
}
