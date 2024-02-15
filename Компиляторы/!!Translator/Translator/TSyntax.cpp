// Parse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TNodes.h"
#include "TSyntax.h"
#include "TSemantic.h"

#define PARSE_EXPRESSION(NAME,FUNC,CLEAR) TNode *NAME = FUNC; if (NAME->error()) { CLEAR; return NAME; }

#define MATCH_MUST(SYM,CLEAR) if (!MatchMust(SYM)) { CLEAR; return error(); }

#define syntax this
#define VARIABLES_STEP(NODE,STEP) if (NODE && SYNTAX_MODE(Phase, TwoPhase)) NODE->Variables(*(syntax->data->semantic), T_Step::ts##STEP);
#define VARIABLES_STEPS(NODE,S1,S2,S3,S4) if (NODE && SYNTAX_MODE(Phase, TwoPhase)) \
        NODE->Variables(*(syntax->data->semantic), T_Step::ts##S1 | T_Step::ts##S2 | T_Step::ts##S3 | T_Step::ts##S4);

// --------------------------- TSyntax ---------------------------

TSyntax::TSyntax(T_Scan *s) : A_Syntax(s), current_error(NULL) 
{
   option_mode = mmNode;
}

TNodeError* TSyntax::error(T_Error code, const T_Lexeme &l, int value)
{
   TNodeError* err = new TNodeError();
   err->SetLexeme(l);
   Error.error(code,l,value);
   return err;
}

void TSyntax::clear(TNode* node)
{
   if (node) { node->clear(); delete node; } 
}

bool TSyntax::MatchMust(T_Symbol::T_Type t)
{
	if (Match(t)) return true;
   current_error = error(T_Error::erSymbol,t);
	return false;
}

TNode* TSyntax::Assign()
{
   TNode* left = Question(); if (left->error()) return left;
	if (Match(T_Symbol::prAssign)) {
      T_Lexeme lexeme = forward;
      PARSE_EXPRESSION(right,Assign(),clear(left))
      TNodeBinary *assign = new TNodeBinary(lexeme, left, right);
      VARIABLES_STEP(assign, All)
      return assign;
	}
   return left;
}

TNode* TSyntax::Question()
{
   PARSE_EXPRESSION(expr,Binary(T_Symbol::prOrOr),)
	if (!Match(T_Symbol::prQuestion)) return expr;
   T_Lexeme lexeme = forward;
   PARSE_EXPRESSION(left,Question(),clear(expr))
   MATCH_MUST(T_Symbol::lxColon,clear(expr))
   PARSE_EXPRESSION(right,Question(),clear(expr); clear(left))
   TNodeTrio *question = new TNodeTrio(lexeme, expr, left, right);
   VARIABLES_STEP(question, All);
   return question;
}

TNode* TSyntax::Unary()
{
	if (Match(T_Symbol::prUnary) || Match(T_Symbol::prTerm) || Match(T_Symbol::prIncDec)) {
      T_Lexeme lexeme = forward;
      ChangeUnary(lexeme,true);
      TNode *expr = Unary(); if (expr->error()) return expr;
      TNodeUnary *unary = new TNodeUnary(lexeme, expr);
      VARIABLES_STEP(unary, All)
      return unary;
	}
   T_ScanStore store; Store(store);
   if (Match(T_Symbol::lxLeftBracket)) { // ([const] int) unary
   	int detail = Match(T_Lexeme::W_Type::rwConst) ? 0x02 : 0x00;
      if (Match(T_Lexeme::W_Type::rwDefine)) {
         T_Lexeme lexeme = forward;
         if (Match(T_Symbol::lxRightBracket)) {
            TNode *expr = Unary(); if (expr->error()) return expr;
            TNodeType *type = BaseType(lexeme,detail);
            TNodeCast *cast = new TNodeCast(lexeme, type, expr);
            VARIABLES_STEP(cast, All)
            return cast;
         }
      } else {
         if (detail) return error(erUnknownCast);
      } 
	}
   Restore(store);
   TNode *expr = Primary(); if (expr->error()) return expr;
	while (Match(T_Symbol::prIncDec)) {
      T_Lexeme lexeme = forward;
      ChangeUnary(lexeme,false);
      TNodeUnary *unary = new TNodeUnary(lexeme, expr);
      VARIABLES_STEP(unary, All)
      expr = unary;
   }
   return expr;
}

TNode* TSyntax::Primary()
{
   if (Match(T_Lexeme::grIdent)) {
      T_Lexeme lexeme = forward;
		if (Match(T_Symbol::lxLeftBracket)) {
         TNodeCall *call = new TNodeCall(lexeme,NULL);
			if (!Match(T_Symbol::lxRightBracket)) {
            PARSE_EXPRESSION(expr,Expressions(psValueList),clear(call))
            call->SetList((T_NodeList*)expr);
			   MATCH_MUST(T_Symbol::lxRightBracket,clear(call))
			}
         VARIABLES_STEP(call, All)
         return call;
		}
		if (MatchSpot(T_Symbol::lxLeftScrape)) {
         T_NodeList *list = new T_NodeList(forward);
         TNodeIndex *index = new TNodeIndex(lexeme,list);
			while (Match(T_Symbol::lxLeftScrape)) {
            PARSE_EXPRESSION(expr,Expressions(psValue),clear(index))
				list->Add(expr);
			   MATCH_MUST(T_Symbol::lxRightScrape,clear(index))
			}
         VARIABLES_STEP(index, All)
         return index;
		}
      TNodeVar *var = new TNodeVar(lexeme);
      VARIABLES_STEP(var, All)
      return var;
	}
   if (Match(T_Lexeme::grInteger) || Match(T_Lexeme::grNumber)) {
      TNodeNumber *expr = new TNodeNumber(forward);
      return expr;
   }
   if (Match(T_Symbol::lxLeftBracket)) {
      T_Lexeme lexeme = forward;
      PARSE_EXPRESSION(expr,Expressions(),)
      TNodePrimary *primary = new TNodePrimary(lexeme, expr);
      VARIABLES_STEP(primary, All)
      MATCH_MUST(T_Symbol::lxRightBracket,clear(primary))
		return primary;
   }
   if (Match(T_Lexeme::W_Type::rwDefine)) {
      T_Lexeme lexeme = forward;
      MATCH_MUST(T_Symbol::lxLeftBracket, )
      PARSE_EXPRESSION(expr,Expressions(psValue),)
      TNodeType *type = BaseType(lexeme,0);
      TNodeCast *cast = new TNodeCast(lexeme, type, expr);
      VARIABLES_STEP(cast, All)
      MATCH_MUST(T_Symbol::lxRightBracket,clear(cast))
	   return cast;
   }
   return error(erPrimary);
}

TNode* TSyntax::Binary(T_Symbol::T_Priority priority)
{
   TNode *left;
   if ((priority + 1) < T_Symbol::prUnary) {
      left = Binary(T_Symbol::T_Priority(priority + 1));
   } else {
      left = Unary(); 
   }
   if (left->error()) return left;
   while (Match(priority)) {
      T_Lexeme lexeme = forward;
      TNode *right;
      if ((priority + 1) < T_Symbol::prUnary) {
         right = Binary(T_Symbol::T_Priority(priority + 1));
      } else {
         right = Unary(); 
      }
      if (right->error()) { clear(left); return right; }
      if ((priority == T_Symbol::prOrOr ) || (priority == T_Symbol::prAndAnd)) {
         left = new TNodeLogical(lexeme, left, right);
      } else {
         left = new TNodeBinary(lexeme, left, right);
      }
      VARIABLES_STEP(left, All)
   }
   return left;
}

TNode* TSyntax::Expressions(T_Part part)
{
   TNodeExpressions *expression = new TNodeExpressions(forward);
   expression->part = part;
   do {
      PARSE_EXPRESSION(expr,Assign(),clear(expression))
      expression->Add(expr);
   } while (Match(T_Symbol::lxComma));
   return expression;
}

TNode* TSyntax::Compaund()
{
   TNodeStatements *compaund = new TNodeStatements();
   VARIABLES_STEP(compaund, Begin)
   while (!Match(T_Symbol::lxRightCramp)) {
      PARSE_EXPRESSION(statement,Statement(T_Part::psBody),clear(compaund))
      if (!statement->null())
         compaund->Add(statement);
      else
         clear(statement);
   }
   VARIABLES_STEP(compaund, End)
   return compaund;
}

TNode* TSyntax::Statements(T_Part part)
{
   TNodeStatements *statements = new TNodeStatements();
   VARIABLES_STEP(statements, Begin)
   while (!Match(T_Lexeme::grEof)) {
      PARSE_EXPRESSION(statement,Statement(part),clear(statements))
      if (!statement->null())
         statements->Add(statement);
      else
         clear(statement);
   }
   VARIABLES_STEP(statements, End)
   return statements;
}

bool TSyntax::Translate()
{
   program = Statements(T_Part::psMain);
   return !program->error();
}

TNode* TSyntax::Statement(T_Part part)
{

	if (Match(T_Symbol::lxSemicolon)) {
      if ((part & T_Part::psNoSemicolon)) return error(erSymbol);
      return new TNodeNull();
   }
   if (part & T_Part::psDefine) {
      T_Lexeme l;
      int def = SCDefine(l,0x26); // -1 - error, 0, 0x01 - define, 0x02 - const, 0x04 - static, 0x20 - void
		if (def < 0) return error(erDefine);
 		if (def) {
         forward = l;
		   return Define(part,def);
		}
	}

   if (part & T_Part::psStatement) {
      T_Lexeme lexeme;
      T_ScanStore store; Store(store);
      if (Match(lexeme,T_Lexeme::grIdent) && Match(T_Symbol::lxColon)) {
         T_NodeList *compaund = new T_NodeList();
			TNodeUserLabel* label = new TNodeUserLabel(lexeme);
         compaund->Add(label);
         VARIABLES_STEP(label, All)
         PARSE_EXPRESSION(approval,Statement(T_Part::psLabel),clear(compaund))
         compaund->Add(approval);
         return compaund;
      } 
      Restore(store);
      if (Match(T_Lexeme::W_Type::rwIf))       return If();
      if (Match(T_Lexeme::W_Type::rwFor))      return For();
      if (Match(T_Lexeme::W_Type::rwWhile))    return While();
      if (Match(T_Lexeme::W_Type::rwDo))       return Do();
      if (Match(T_Lexeme::W_Type::rwGoTo))     return GoTo();
      if (Match(T_Lexeme::W_Type::rwContinue)) return BreakContinue(T_Block::tbContinue);
      if (Match(T_Lexeme::W_Type::rwBreak))    return BreakContinue(T_Block::tbBreak);
      if (Match(T_Lexeme::W_Type::rwReturn))   return Return();
      if (Match(T_Lexeme::W_Type::rwSwitch))   return Switch();
	}

   if (part & T_Part::psCompaund) {
      if (Match(T_Symbol::lxLeftCramp)) return Compaund();
	}

   if (part & T_Part::psExpression) {
      PARSE_EXPRESSION(expr,Expressions(part),)
      if (!(part & T_Part::psNoSemicolon)) {
         MATCH_MUST(T_Symbol::lxSemicolon,clear(expr))
         }
      return expr;
	}

   return error(erStatement);
}

TNode* TSyntax::DefineParam()
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
      int scrape = 0;
		while (Match(T_Symbol::lxLeftScrape)) {
		   if (!scrape++ && Match(T_Symbol::lxRightScrape)) {
            range->Add(new TNodeNull());
            continue;
         }
         PARSE_EXPRESSION(expr,Assign(),clear(param))
         range->Add(expr);
		   MATCH_MUST(T_Symbol::lxRightScrape,clear(param))
		}
      VARIABLES_STEP(param, Begin);
      if (Match(T_Symbol::lxAssign)) {
         PARSE_EXPRESSION(expr,Assign(),clear(param))
         param->SetAssign(expr);
      } else if (param->BaseType() & T_BaseType::btReference) {
         error(erUninitialized);
      }
      VARIABLES_STEP(param, DefArrAssign);
      return param;
   }
   TNodeDefVar *param = new TNodeDefVar(type,ident);
   if (Match(T_Symbol::lxAssign)) {
      PARSE_EXPRESSION(expr,Assign(),clear(param))
      param->SetAssign(expr);
   } else if (param->BaseType() & T_BaseType::btReference) {
      error(erUninitialized);
   }
   VARIABLES_STEP(param, All)
   return param;
}

TNode* TSyntax::DefineParams()
{
   TNodeDefine *params = new TNodeDefine(forward);
   do {
      PARSE_EXPRESSION(param,DefineParam(),clear(params))
      params->Add(param);
   } while (Match(T_Symbol::lxComma));
   VARIABLES_STEP(params, All)
   return params;
}

TNode* TSyntax::InitializerItem()
{
   if (MatchSpot(T_Symbol::lxLeftCramp)) return Initializer();
   return Assign();
}

TNode* TSyntax::Initializer()
{
   if (!MatchMust(T_Symbol::lxLeftCramp)) return error();
   T_NodeList *list = new T_NodeList(forward);
   if (Match(T_Symbol::lxRightCramp)) return list;
   do {
      PARSE_EXPRESSION(item,InitializerItem(),clear(list))
      list->Add(item);
   } while (Match(T_Symbol::lxComma));
   MATCH_MUST(T_Symbol::lxRightCramp,clear(list))
   return list;
}

TNode* TSyntax::DefineItem(const T_Lexeme &lexeme, T_Part part, int detail)
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
      int scrape = 0;
		while (Match(T_Symbol::lxLeftScrape)) {
		   if (!scrape++ && Match(T_Symbol::lxRightScrape)) {
            range->Add(new TNodeNull());
            continue;
         }
         PARSE_EXPRESSION(expr,Assign(),clear(arr))
         range->Add(expr);
		   MATCH_MUST(T_Symbol::lxRightScrape,clear(arr))
		}
      VARIABLES_STEP(arr, Begin);
      if (Match(T_Symbol::lxAssign)) {
         PARSE_EXPRESSION(assign,Initializer(),clear(arr))
         arr->SetAssign(assign);
      } else if (arr->BaseType() & T_BaseType::btConstReference) {
         error(erUninitialized);
      }
      VARIABLES_STEP(arr, DefArrAssign);
      return arr;
   }
   TNodeDefVar *var = new TNodeDefVar(type, ident);
   if (Match(T_Symbol::lxAssign)) {
      T_Lexeme lexeme = forward;
      PARSE_EXPRESSION(expr,Assign(),clear(var))
      var->SetAssign(lexeme,expr, SYNTAX_MODE(Phase, TwoPhase) ? syntax->data->semantic : NULL);
   } else if (var->BaseType() & T_BaseType::btConstReference) {
      error(erUninitialized);
   } else if (part & T_Part::psOneDef) { // condition
      error(erUninitialized);
   }
   VARIABLES_STEP(var, All);
   return var;
}

TNode* TSyntax::Define(T_Part part, int constant)
{
   T_Lexeme lexeme = forward;
   TNodeType *type = BaseType(lexeme,constant);

   T_ScanStore store; Store(store);
   T_Lexeme ident;
   if (Match(ident, T_Lexeme::grIdent) && Match(T_Symbol::lxLeftBracket)) {
      if (!(part & psDefFunc)) { return error(erDefFunc); }
      TNodeDefFunc *func = new TNodeDefFunc(type, ident, NULL, NULL);
      VARIABLES_STEP(func, Begin)
      if (!Match(T_Symbol::lxRightBracket)) {
         PARSE_EXPRESSION(params, DefineParams(), clear(func))
         func->SetParams((TNodeDefine*)params);
         MATCH_MUST(T_Symbol::lxRightBracket, clear(func))
      }
      VARIABLES_STEP(func, Param)
      if (Match(T_Symbol::lxLeftCramp)) {
         PARSE_EXPRESSION(body, Compaund(), clear(func))
         func->SetBody(body);
      }
      VARIABLES_STEP(func, Body)
      VARIABLES_STEP(func, End)
      return func;
   }

   Restore(store);
   TNodeDefine *def = new TNodeDefine(type, lexeme);
   do {
      PARSE_EXPRESSION(var,DefineItem(lexeme, part, constant),clear(def))
      def->Add(var);
      if (part & T_Part::psOneDef) break;
   } while (Match(T_Symbol::lxComma));
   VARIABLES_STEP(def, All)
   if (!(part & T_Part::psNoSemicolon) && !Match(T_Symbol::lxSemicolon)) { clear(def); return error(erDefine); }
   return def;
}

TNode* TSyntax::For()
{
   TNodeFor *cycle = new TNodeFor(forward);
   VARIABLES_STEP(cycle, Begin)
   MATCH_MUST(T_Symbol::lxLeftBracket,clear(cycle))
   PARSE_EXPRESSION(beg,Statement(T_Part::psForBeg),clear(cycle))  // prefix
   cycle->SetBeg(beg);
   PARSE_EXPRESSION(condition,Statement(T_Part::psForExpr),clear(cycle)) // condition
   cycle->SetCondition(condition);
   if (!Match(T_Symbol::lxRightBracket)) {
      PARSE_EXPRESSION(end,Expressions(psExpression),clear(cycle)) // postfix
      cycle->SetEnd(end);
      MATCH_MUST(T_Symbol::lxRightBracket,clear(cycle))
   } else {
      cycle->SetEnd(new TNodeNull()); 
   }
   VARIABLES_STEP(cycle, ForTitle)
   PARSE_EXPRESSION(body,Statement(T_Part::psBody),clear(cycle))   // body
   cycle->SetBody(body);
   VARIABLES_STEP(cycle, Body);
   VARIABLES_STEP(cycle, End)
   return cycle;
}

TNode* TSyntax::While()
{
   TNodeWhile *cycle = new TNodeWhile(forward);
   MATCH_MUST(T_Symbol::lxLeftBracket,clear(cycle))
   VARIABLES_STEP(cycle, Begin)
   PARSE_EXPRESSION(condition,Statement(T_Part::psCondition),clear(cycle))
   cycle->SetCondition(condition);
   MATCH_MUST(T_Symbol::lxRightBracket,clear(cycle))
   VARIABLES_STEP(cycle, Condition)
   PARSE_EXPRESSION(body,Statement(T_Part::psBody),clear(cycle))
   cycle->SetBody(body);
   VARIABLES_STEP(cycle, Body)
   VARIABLES_STEP(cycle, End)
   return cycle;
}

TNode* TSyntax::Do()
{
   TNodeDo *cycle = new TNodeDo(forward);
   VARIABLES_STEP(cycle, Begin)
   PARSE_EXPRESSION(body,Statement(T_Part::psBody),clear(cycle))
   cycle->SetBody(body);
   if (!Match(T_Lexeme::W_Type::rwWhile)) { clear(cycle); return error(erStatement); }
   MATCH_MUST(T_Symbol::lxLeftBracket,clear(cycle))
   VARIABLES_STEP(cycle, Body)
   PARSE_EXPRESSION(condition,Statement(T_Part::psCondition),clear(cycle))
   cycle->SetCondition(condition);
   VARIABLES_STEP(cycle, Condition)
   MATCH_MUST(T_Symbol::lxRightBracket,clear(cycle))
   MATCH_MUST(T_Symbol::lxSemicolon,clear(cycle))
   VARIABLES_STEP(cycle, End)
   return cycle;
}

TNode* TSyntax::GoTo()
{
   if (!Match(T_Lexeme::grIdent)) return error(erNoIdent);
   T_Lexeme lexeme = forward;
   TNodeUserGoTo *statement = new TNodeUserGoTo(lexeme);
   MATCH_MUST(T_Symbol::lxSemicolon,clear(statement))
   VARIABLES_STEP(statement, All)
   return statement;
}

TNode* TSyntax::BreakContinue(T_Block rate)
{
   TNodeBreakContinue *statement = new TNodeBreakContinue(rate,forward);
   MATCH_MUST(T_Symbol::lxSemicolon,clear(statement))
   VARIABLES_STEP(statement, All)
   return statement;
}

TNode* TSyntax::If()
{
   TNodeIf *statement = new TNodeIf(forward);
   MATCH_MUST(T_Symbol::lxLeftBracket,clear(statement))
   VARIABLES_STEP(statement, Begin)
   PARSE_EXPRESSION(condition,Statement(T_Part::psCondition),clear(statement))
   statement->SetCondition(condition);
   VARIABLES_STEP(statement, Condition)
   MATCH_MUST(T_Symbol::lxRightBracket,clear(statement))
   PARSE_EXPRESSION(then_body,Statement(T_Part::psBody),clear(statement))
   statement->SetThen(then_body);
   VARIABLES_STEP(statement, IfThen)
   if (Match(T_Lexeme::W_Type::rwElse)) {
      PARSE_EXPRESSION(then_else,Statement(T_Part::psBody),clear(statement))
      statement->SetElse(then_else);
   } else {
      statement->SetElse(new TNodeNull()); 
   }
   VARIABLES_STEPS(statement, IfElse, IfLabel, End, )
   return statement;
}

TNode* TSyntax::Return()
{
   TNodeReturn *ret = new TNodeReturn(forward);
   if (!MatchSpot(T_Symbol::lxSemicolon)) {
      PARSE_EXPRESSION(value, Expressions(psValue), clear(ret))
      ret->SetValue(value);
   }
   MATCH_MUST(T_Symbol::lxSemicolon,clear(ret))
   VARIABLES_STEP(ret, All)
   return ret;
}

TNode* TSyntax::Switch()
{
   TNodeSwitch *statement = new TNodeSwitch(forward);
   MATCH_MUST(T_Symbol::lxLeftBracket,clear(statement))
   PARSE_EXPRESSION(key,Statement(T_Part::psCondition),clear(statement))
   statement->SetKey(key);
   MATCH_MUST(T_Symbol::lxRightBracket,clear(statement))
   MATCH_MUST(T_Symbol::lxLeftCramp,clear(statement))
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
	         PARSE_EXPRESSION(item_val,Question(),clear(statement))
            val->SetValue(item_val);
         } else {
            if (default_count++) { clear(statement); return error(erSwitch); }
            val->value = false;
         } 
         MATCH_MUST(T_Symbol::lxColon,clear(statement))
      }
      while (!MatchSpot(T_Lexeme::W_Type::rwCase) && !MatchSpot(T_Lexeme::W_Type::rwDefault) && !MatchSpot(T_Symbol::lxRightCramp)) {
         PARSE_EXPRESSION(item_body,Statement(T_Part::psCase),clear(statement))
         body_item->Add(item_body);
      }
   } while (!Match(T_Symbol::lxRightCramp));
   if (!case_count || (default_count > 1)) { clear(statement); return error(erSwitch); }
   return statement;
}

