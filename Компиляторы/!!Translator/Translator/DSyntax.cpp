// Parse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TNodes.h"
#include "DSyntax.h"
#include "TSemantic.h"

#define PARSE_EXPRESSION(NAME,FUNC,CLEAR) TNode *NAME = FUNC; if (NAME->error()) { CLEAR; return NAME; }

#define MATCH_MUST(SYM) if (!MatchMust(SYM)) { return false; }
#undef  CURRENT_CHILD
#define CURRENT_CHILD(L,C) if (!L->SetCurrentChild(C)) return false;
#define CURRENT_CHANGE(L,C) if (!L->ChangeCurrentChild(C)) return false;
#define CHILD_INDEX(L,I) L->SetChildIndex(I);

#define syntax this
#define VARIABLES_STEP(NODE,STEP) if (NODE && SYNTAX_MODE(Phase, TwoPhase)) NODE->Variables(*(syntax->data->semantic), T_Step::ts##STEP);
#define VARIABLES_STEPS(NODE,S1,S2,S3,S4) if (NODE && SYNTAX_MODE(Phase, TwoPhase)) \
        NODE->Variables(*(syntax->data->semantic), T_Step::ts##S1 | T_Step::ts##S2 | T_Step::ts##S3 | T_Step::ts##S4);

// --------------------------- DSyntax ---------------------------

DSyntax::DSyntax(T_Scan *s) : A_Syntax(s), current_error(NULL) 
{
   option_mode = mmNode;
}

bool DSyntax::Assign(TNode* landlord)
{
   if (!Question(landlord)) return false;
	if (Match(T_Symbol::prAssign)) {
      T_Lexeme lexeme = forward;
      TNodeBinary *assign = new TNodeBinary(lexeme, NULL, NULL);
      CURRENT_CHANGE(landlord,assign)
      if (!Assign(assign)) return false;
      VARIABLES_STEP(assign, All)
   }
   return true;
}

bool DSyntax::Question(TNode* landlord)
{
   if (!Binary(landlord, T_Symbol::prOrOr)) return false;
   if (Match(T_Symbol::prQuestion)) {
      T_Lexeme lexeme = forward;
      TNodeTrio *question = new TNodeTrio(lexeme, NULL, NULL, NULL);
      CURRENT_CHANGE(landlord,question)
      if (!Question(question)) return false;
      if (!Match(T_Symbol::lxColon)) return false;
      if (!Question(question)) return false;
      VARIABLES_STEP(question,All);
   }
   return true;
}

bool DSyntax::Unary(TNode* landlord)
{
	if (Match(T_Symbol::prUnary) || Match(T_Symbol::prTerm) || Match(T_Symbol::prIncDec)) {
      T_Lexeme lexeme = forward;
      ChangeUnary(lexeme,true);
      TNodeUnary *unary = new TNodeUnary(lexeme, NULL);
      CURRENT_CHILD(landlord,unary)
      if (!Unary(unary)) return false;
      VARIABLES_STEP(unary, All)
      return true;
	}
   T_ScanStore store; Store(store);
   if (Match(T_Symbol::lxLeftBracket)) { // ([const] int) unary
   	int detail = Match(T_Lexeme::W_Type::rwConst) ? 0x02 : 0x00;
      if (Match(T_Lexeme::W_Type::rwDefine)) {
         T_Lexeme lexeme = forward;
         if (Match(T_Symbol::lxRightBracket)) {
            TNodeType *type = BaseType(lexeme,detail);
            TNodeCast *cast = new TNodeCast(lexeme, type, NULL);
            CURRENT_CHILD(landlord, cast)
            if (!Unary(cast)) return false;
            VARIABLES_STEP(cast, All)
            return true;
         }
      } else {
         if (detail) return error(erUnknownCast);
      } 
	}
   Restore(store);
   if (!Primary(landlord)) return false;
	while (Match(T_Symbol::prIncDec)) {
      T_Lexeme lexeme = forward;
      ChangeUnary(lexeme,false);
      TNodeUnary *unary = new TNodeUnary(lexeme, NULL);
      CURRENT_CHANGE(landlord,unary)
      VARIABLES_STEP(unary, All)
   }
   return true;
}

bool DSyntax::Primary(TNode* landlord)
{
   if (Match(T_Lexeme::grIdent)) {
      T_Lexeme lexeme = forward;
		if (Match(T_Symbol::lxLeftBracket)) {
         TNodeCall *call = new TNodeCall(lexeme,NULL);
         CURRENT_CHILD(landlord, call)
         if (!Match(T_Symbol::lxRightBracket)) {
            if (!Expressions(call, psValueList)) return false;
			   MATCH_MUST(T_Symbol::lxRightBracket)
			}
         VARIABLES_STEP(call, All)
         return true;
		}
		if (MatchSpot(T_Symbol::lxLeftScrape)) {
         T_NodeList *list = new T_NodeList(forward);
         TNodeIndex *index = new TNodeIndex(lexeme,list);
         CURRENT_CHILD(landlord, index)
         while (Match(T_Symbol::lxLeftScrape)) {
            if (!Expressions(list, psValue)) return false;
			   MATCH_MUST(T_Symbol::lxRightScrape)
			}
         VARIABLES_STEP(index, All)
         return true;
		}
      TNodeVar *var = new TNodeVar(lexeme);
      CURRENT_CHILD(landlord, var)
      VARIABLES_STEP(var, All)
      return true;
	}
   if (Match(T_Lexeme::grInteger) || Match(T_Lexeme::grNumber)) {
      TNodeNumber *expr = new TNodeNumber(forward);
      CURRENT_CHILD(landlord, expr)
      return true;
   }
   if (Match(T_Symbol::lxLeftBracket)) {
      T_Lexeme lexeme = forward;
      TNodePrimary *primary = new TNodePrimary(lexeme, NULL);
      CURRENT_CHILD(landlord, primary)
      if (!Expressions(primary)) return false;
      VARIABLES_STEP(primary, All)
      MATCH_MUST(T_Symbol::lxRightBracket)
		return true;
   }
   if (Match(T_Lexeme::W_Type::rwDefine)) {
      T_Lexeme lexeme = forward;
      MATCH_MUST(T_Symbol::lxLeftBracket)
      TNodeType *type = BaseType(lexeme,0);
      TNodeCast *cast = new TNodeCast(lexeme, type, NULL);
      CURRENT_CHILD(landlord, cast)
      if (!Expressions(cast, psValue)) return false;
      VARIABLES_STEP(cast, All)
      MATCH_MUST(T_Symbol::lxRightBracket)
	   return true;
   }
   return error(erPrimary);
}

bool DSyntax::Binary(TNode* landlord, T_Symbol::T_Priority priority)
{
   if ((priority + 1) < T_Symbol::prUnary) {
      if (!Binary(landlord, T_Symbol::T_Priority(priority + 1))) return false;
   } else {
      if (!Unary(landlord)) return false;
   }
   while (Match(priority)) {
      T_Lexeme lexeme = forward;
      if ((priority) < T_Symbol::prUnary) {
         TNode* binary;
         if ((priority == T_Symbol::prOrOr) || (priority == T_Symbol::prAndAnd)) {
            binary = new TNodeLogical(lexeme, NULL, NULL);
         } else {
            binary = new TNodeBinary(lexeme, NULL, NULL);
         }
         CURRENT_CHANGE(landlord,binary)
         if (!Binary(binary, T_Symbol::T_Priority(priority + 1))) return false;
         VARIABLES_STEP(binary, All)
      } else {
         if (!Unary(landlord)) return false;
      }
   }
   return true;
}

bool DSyntax::Expressions(TNode* landlord, T_Part part)
{
   TNodeExpressions *expression = new TNodeExpressions(forward);
   expression->part = part;
   CURRENT_CHILD(landlord,expression)
   do {
      if (!Assign(expression)) return false;
   } while (Match(T_Symbol::lxComma));
   return true;
}

bool DSyntax::Compaund(TNode* landlord)
{
   TNodeStatements *compaund = new TNodeStatements();
   CURRENT_CHILD(landlord,compaund)
   VARIABLES_STEP(compaund, Begin)
   while (!Match(T_Symbol::lxRightCramp)) {
      if (!Statement(compaund, T_Part::psBody)) return false;
   }
   VARIABLES_STEP(compaund, End)
   return true;
}

bool DSyntax::Statements(T_Part part)
{
   TNodeStatements *statements = new TNodeStatements();
   program = statements;
   VARIABLES_STEP(statements, Begin)
   while (!Match(T_Lexeme::grEof)) {
      if (!Statement(statements, T_Part::psMain)) return false;
   }
   VARIABLES_STEP(statements, End)
   return true;
}

bool DSyntax::Translate()
{
   return Statements(T_Part::psMain);
}

bool DSyntax::Statement(TNode* landlord, T_Part part)
{

	if (Match(T_Symbol::lxSemicolon)) {
      if ((part & T_Part::psNoSemicolon)) return error(erSymbol);
      CURRENT_CHILD(landlord,new TNodeNull())
      return true;
   }
   if (part & T_Part::psDefine) {
      T_Lexeme l;
      int def = SCDefine(l,0x26); // -1 - error, 0, 0x01 - define, 0x02 - const, 0x04 - static, 0x20 - void
		if (def < 0) return error(erDefine);
 		if (def) {
         forward = l;
		   return Define(landlord, part,def);
		}
	}

   if (part & T_Part::psStatement) {
      T_Lexeme lexeme;
      T_ScanStore store; Store(store);
      if (Match(lexeme,T_Lexeme::grIdent) && Match(T_Symbol::lxColon)) {
         if (MatchSpot(T_Symbol::lxRightCramp)) return error(erStatement);
			TNodeUserLabel* label = new TNodeUserLabel(lexeme);
         T_NodeList *compaund = new T_NodeList();
         CURRENT_CHILD(compaund, label)
         CURRENT_CHILD(landlord, compaund)
         VARIABLES_STEP(label, All)
         if (!Statement(compaund, T_Part::psLabel)) return false;
         return true;
      } 
      Restore(store);
      if (Match(T_Lexeme::W_Type::rwIf))       return If(landlord);
      if (Match(T_Lexeme::W_Type::rwFor))      return For(landlord);
      if (Match(T_Lexeme::W_Type::rwWhile))    return While(landlord);
      if (Match(T_Lexeme::W_Type::rwDo))       return Do(landlord);
      if (Match(T_Lexeme::W_Type::rwGoTo))     return GoTo(landlord);
      if (Match(T_Lexeme::W_Type::rwContinue)) return BreakContinue(landlord, T_Block::tbContinue);
      if (Match(T_Lexeme::W_Type::rwBreak))    return BreakContinue(landlord, T_Block::tbBreak);
      if (Match(T_Lexeme::W_Type::rwReturn))   return Return(landlord);
      if (Match(T_Lexeme::W_Type::rwSwitch))   return Switch(landlord);
	}

   if (part & T_Part::psCompaund) {
      if (Match(T_Symbol::lxLeftCramp)) return Compaund(landlord);
	}

   if (part & T_Part::psExpression) {
      if (!Expressions(landlord, part)) return false;  
      if (!(part & T_Part::psNoSemicolon)) {
         MATCH_MUST(T_Symbol::lxSemicolon)
         }
      return true;
	}

   return error(erStatement);
}

bool DSyntax::DefineParam(TNode* landlord)
{
   T_Lexeme lexeme;
   int def = SCDefine(lexeme, 0x0A); // -1 - error, 0, 0x01 - define, 0x02 - const, 0x08 - &
	if (def < 0) return error(erDefine);
   if (!def) return error(erDefine);
   T_Lexeme ident = (Match(T_Lexeme::grIdent) ? forward : empty_ident);
   TNodeType *type = BaseType(lexeme,def);
	if (MatchSpot(T_Symbol::lxLeftScrape)) {
      if (def & 0x08) { return error(erDefArr); } // reference
      T_NodeList *range = new T_NodeList(forward);
      TNodeDefArr *param = new TNodeDefArr(type,ident,range);
      CURRENT_CHILD(landlord, param)
      int scrape = 0;
		while (Match(T_Symbol::lxLeftScrape)) {
		   if (!scrape++ && Match(T_Symbol::lxRightScrape)) {
            range->Add(new TNodeNull());
            continue;
         }
         if (!Assign(range)) return false;
		   MATCH_MUST(T_Symbol::lxRightScrape)
		}
      VARIABLES_STEP(param, Begin);
      if (Match(T_Symbol::lxAssign)) {
         if (!Assign(param)) return false;
      } else if (param->BaseType() & T_BaseType::btReference) {
         error(erUninitialized);
      }
      VARIABLES_STEP(param, DefArrAssign);
      return true;
   }
   TNodeDefVar *param = new TNodeDefVar(type,ident);
   CURRENT_CHILD(landlord, param)
   if (Match(T_Symbol::lxAssign)) {
      if (!Assign(param)) return false;
   } else if (param->BaseType() & T_BaseType::btReference) {
      error(erUninitialized);
   }
   VARIABLES_STEP(param, All)
   return true;
}

bool DSyntax::DefineParams(TNode* landlord)
{
   TNodeDefine *params = new TNodeDefine(forward);
   CURRENT_CHILD(landlord, params)
   do {
      if (!DefineParam(params)) return false;
   } while (Match(T_Symbol::lxComma));
   VARIABLES_STEP(params, All)
   return true;
}

bool DSyntax::InitializerItem(TNode* landlord)
{
   if (MatchSpot(T_Symbol::lxLeftCramp)) return Initializer(landlord);
   return Assign(landlord);
}

bool DSyntax::Initializer(TNode* landlord)
{
   if (!MatchMust(T_Symbol::lxLeftCramp)) return false;
   T_NodeList *list = new T_NodeList(forward);
   CURRENT_CHILD(landlord, list)
   if (Match(T_Symbol::lxRightCramp)) return true;
   do {
      if (!InitializerItem(list)) return false;
   } while (Match(T_Symbol::lxComma));
   MATCH_MUST(T_Symbol::lxRightCramp)
   return true;
}

bool DSyntax::DefineItem(TNode* landlord, const T_Lexeme &lexeme, T_Part part, int detail)
{
	if (Match(T_Symbol::lxAnd)) detail |= 0x08; // reference
   if (!Match(T_Lexeme::grIdent)) return error(erNoIdent);
   TNodeType *type = BaseType(lexeme,detail);
   T_Lexeme ident = forward;

   if (type->Void()) { return error(erDefVoid); }
	if (MatchSpot(T_Symbol::lxLeftScrape)) {
		if ((detail & 0x08) || (part & T_Part::psOneDef)) { return error(erDefArr); }
      T_NodeList *range = new T_NodeList();
      TNodeDefArr *arr = new TNodeDefArr(type, ident, range);
      CURRENT_CHILD(landlord, arr)
      int scrape = 0;
		while (Match(T_Symbol::lxLeftScrape)) {
		   if (!scrape++ && Match(T_Symbol::lxRightScrape)) {
            range->Add(new TNodeNull());
            continue;
         }
         if (!Assign(range)) return false;
		   MATCH_MUST(T_Symbol::lxRightScrape)
		}
      VARIABLES_STEP(arr, Begin);
      if (Match(T_Symbol::lxAssign)) {
         if (!Initializer(arr)) return false;
      } else if (arr->BaseType() & T_BaseType::btConstReference) {
         error(erUninitialized);
      }
      VARIABLES_STEP(arr, DefArrAssign);
      return true;
   }
   TNodeDefVar *var = new TNodeDefVar(type, ident);
   CURRENT_CHILD(landlord, var)
   if (Match(T_Symbol::lxAssign)) {
      T_Lexeme lexeme = forward;
      if (!Assign(var)) return false;
      var->SetAssign(lexeme,var->Right(), SYNTAX_MODE(Phase, TwoPhase) ? syntax->data->semantic : NULL);
   } else if (var->BaseType() & T_BaseType::btConstReference) {
      error(erUninitialized);
   } else if (part & T_Part::psOneDef) { // condition
      error(erUninitialized);
   }
   VARIABLES_STEP(var,All);
   if (part & T_Part::psOneDef) { // condition
//      T_NodeList *list = new T_NodeList();
//      CURRENT_CHANGE(landlord, list)
      TNodeVar *push_var = new TNodeVar(ident);
      CURRENT_CHILD(landlord, push_var)
      VARIABLES_STEP(push_var, All);
      return true;
   }
   return true;
}

bool DSyntax::Define(TNode* landlord, T_Part part, int constant)
{
   T_Lexeme lexeme = forward;
   TNodeType *type = BaseType(lexeme, constant);

   T_ScanStore store; Store(store);
   T_Lexeme ident;
   if (Match(ident, T_Lexeme::grIdent) && Match(T_Symbol::lxLeftBracket)) {
      if (!(part & psDefFunc)) { return error(erDefFunc); }
      TNodeDefFunc *func = new TNodeDefFunc(type, ident, NULL, NULL);
      CURRENT_CHILD(landlord, func)
      VARIABLES_STEP(func, Begin)
      if (!Match(T_Symbol::lxRightBracket)) {
         if (!DefineParams(func)) return false;
         MATCH_MUST(T_Symbol::lxRightBracket)
      } else {
         func->ChangeChildIndex(1);
      }
      VARIABLES_STEP(func, Param)
      if (Match(T_Symbol::lxLeftCramp)) {
         if (!Compaund(func)) return false;
      }
      if (Match(T_Symbol::lxSemicolon)) {}
      VARIABLES_STEP(func, Body)
      VARIABLES_STEP(func, End)
      return true;
   }

   Restore(store);
   TNodeDefine *def = new TNodeDefine(type, lexeme);
   CURRENT_CHILD(landlord, def)
   do {
      if (!DefineItem(def, lexeme, part, constant)) return false;
      if (part & T_Part::psOneDef) break;
   } while (Match(T_Symbol::lxComma));
   VARIABLES_STEP(def,All)
   if (!(part & T_Part::psNoSemicolon) && !Match(T_Symbol::lxSemicolon)) { return error(erDefine); }
   return true;
}

bool DSyntax::For(TNode* landlord)
{
   TNodeFor *cycle = new TNodeFor(forward);
   CURRENT_CHILD(landlord, cycle)
   VARIABLES_STEP(cycle, Begin)
   MATCH_MUST(T_Symbol::lxLeftBracket)
   if (!Statement(cycle, T_Part::psForBeg)) return false;  // prefix
   if (!Statement(cycle, T_Part::psForExpr)) return false; // condition
   if (!Match(T_Symbol::lxRightBracket)) {
      if (!Expressions(cycle,psExpression)) return false;  // postfix
      MATCH_MUST(T_Symbol::lxRightBracket)
   } else {
      CURRENT_CHILD(cycle, new TNodeNull())
   }
   VARIABLES_STEP(cycle, ForTitle)
   if (!Statement(cycle, T_Part::psBody)) return false;   // body
   VARIABLES_STEP(cycle, Body);
   VARIABLES_STEP(cycle, End)
   return true;
}

bool DSyntax::While(TNode* landlord)
{
   TNodeWhile *cycle = new TNodeWhile(forward);
   CURRENT_CHILD(landlord, cycle)
   MATCH_MUST(T_Symbol::lxLeftBracket)
   VARIABLES_STEP(cycle, Begin)
   if (!Statement(cycle, T_Part::psCondition)) return false;
   MATCH_MUST(T_Symbol::lxRightBracket)
   VARIABLES_STEP(cycle, Condition)
   if (!Statement(cycle, T_Part::psBody)) return false;
   VARIABLES_STEP(cycle, Body)
   VARIABLES_STEP(cycle, End)
   return true;
}

bool DSyntax::Do(TNode* landlord)
{
   TNodeDo *cycle = new TNodeDo(forward);
   CURRENT_CHILD(landlord, cycle)
   VARIABLES_STEP(cycle, Begin)
   if (!Statement(cycle, T_Part::psBody)) return false;
   if (!Match(T_Lexeme::W_Type::rwWhile)) { return error(erStatement); }
   MATCH_MUST(T_Symbol::lxLeftBracket)
   VARIABLES_STEP(cycle, Body)
   if (!Statement(cycle, T_Part::psCondition)) return false;
   VARIABLES_STEP(cycle, Condition)
   MATCH_MUST(T_Symbol::lxRightBracket)
   MATCH_MUST(T_Symbol::lxSemicolon)
   VARIABLES_STEP(cycle, End)
   return true;
}

bool DSyntax::GoTo(TNode* landlord)
{
   if (!Match(T_Lexeme::grIdent)) return error(erNoIdent);
   T_Lexeme lexeme = forward;
   TNodeUserGoTo *statement = new TNodeUserGoTo(lexeme);
   CURRENT_CHILD(landlord, statement)
   MATCH_MUST(T_Symbol::lxSemicolon)
   VARIABLES_STEP(statement, All)
   return true;
}

bool DSyntax::BreakContinue(TNode* landlord, T_Block rate)
{
   TNodeBreakContinue *statement = new TNodeBreakContinue(rate,forward);
   CURRENT_CHILD(landlord,statement)
   MATCH_MUST(T_Symbol::lxSemicolon)
   VARIABLES_STEP(statement, All)
   return true;
}

bool DSyntax::If(TNode* landlord)
{
   TNodeIf *statement = new TNodeIf(forward);
   CURRENT_CHILD(landlord, statement)
   MATCH_MUST(T_Symbol::lxLeftBracket)
   VARIABLES_STEP(statement, Begin)
   if (!Statement(statement, T_Part::psCondition)) return false;
   VARIABLES_STEP(statement, Condition)
   MATCH_MUST(T_Symbol::lxRightBracket)
   if (!Statement(statement,T_Part::psBody)) return false;
   VARIABLES_STEP(statement, IfThen)
   if (Match(T_Lexeme::W_Type::rwElse)) {
      if (!Statement(statement,T_Part::psBody)) return false;
   } else {
      CURRENT_CHILD(statement, new TNodeNull())
   }
   VARIABLES_STEPS(statement, IfElse, IfLabel, End, )
   return true;
}

bool DSyntax::Return(TNode* landlord)
{
   TNodeReturn *ret = new TNodeReturn(forward);
   CURRENT_CHILD(landlord,ret)
   if (!MatchSpot(T_Symbol::lxSemicolon)) {
      if (!Expressions(ret, psValue)) return false;
   }
   MATCH_MUST(T_Symbol::lxSemicolon)
   VARIABLES_STEP(ret, All)
   return true;
}

bool DSyntax::Switch(TNode* landlord)
{
   TNodeSwitch *statement = new TNodeSwitch(forward);
   MATCH_MUST(T_Symbol::lxLeftBracket)
   if (!Statement(landlord, T_Part::psCondition)) return false;
   MATCH_MUST(T_Symbol::lxRightBracket)
   MATCH_MUST(T_Symbol::lxLeftCramp)
   T_NodeList *body = new T_NodeList();
   statement->SetBody(body);
   int case_count = 0, default_count = 0;
   do {
      TNodeSwitchItem *item = new TNodeSwitchItem();  body->Add(item);
      T_NodeList *key_item = new T_NodeList();        item->SetKey(key_item);
      T_NodeList *body_item = new T_NodeList();       item->SetBody(body_item);
      while (Match(T_Lexeme::W_Type::rwCase) || Match(T_Lexeme::W_Type::rwDefault)) {
         TNodeSwitchCase *val = new TNodeSwitchCase(forward); key_item->Add(val);
         if (forward.Match(T_Lexeme::W_Type::rwCase)) {
            case_count++; 
            if (!Question(val)) return false;
         } else {
            if (default_count++) { return error(erSwitch); }
            val->value = false;
         } 
         MATCH_MUST(T_Symbol::lxColon)
      }
      while (!MatchSpot(T_Lexeme::W_Type::rwCase) && !MatchSpot(T_Lexeme::W_Type::rwDefault) && !MatchSpot(T_Symbol::lxRightCramp)) {
         if (!Statement(body_item, T_Part::psCase)) return false;
      }
   } while (!Match(T_Symbol::lxRightCramp));
   if (!case_count || (default_count > 1)) { return error(erSwitch); }
   return true;
}
