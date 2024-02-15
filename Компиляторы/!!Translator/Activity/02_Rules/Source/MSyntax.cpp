
#include "stdafx.h"

#include "MSyntax.h"
#include "TSemantic.h"

// --------------------------- MSyntax ---------------------------
#define MAKE_(FUNC,P,M)   {static GSymbol maker(GSymbol::gsMaker,GMakerTable::maker_table.Find(#FUNC),P,0,M);\
                           if (!Maker(maker)) return false; }
#define MAKE(FUNC)         MAKE_(FUNC,0,GSymbol::Tree | GSymbol::Code)
#define MAKE_TREE(FUNC)    MAKE_(FUNC,0,GSymbol::Tree);
#define MAKE_CODE(FUNC)    MAKE_(FUNC,0,GSymbol::Code);
#define PARAM(FUNC,P)      MAKE_(FUNC,P,GSymbol::Tree | GSymbol::Code) 
#define PARAM_TREE(FUNC,P) MAKE_(FUNC,P,GSymbol::Tree) 
#define PARAM_CODE(FUNC,P) MAKE_(FUNC,P,GSymbol::Code) 
#define EXPRESSION(PART)   PARAM_CODE(Part,T_Part::ps##PART) if (!Expressions()) return false; PARAM_TREE(ExpressionSLL,T_Part::ps##PART)

bool MSyntax::Assign()
{
   if (!Question()) return false;
	if (Match(T_Symbol::prAssign)) {
	   if (!Assign()) return false;
      MAKE(Binary)
	}
   return true;
}

bool MSyntax::Question()
{
   if (!Binary(T_Symbol::prOrOr)) return false;
	if (Match(T_Symbol::prQuestion)) {
      MAKE_CODE(BegQuestion)
	   if (!Question()) return false;
      MAKE_CODE(MidQuestion)
		if (!MatchMust(T_Symbol::lxColon)) return false;
	   if (!Question()) return false;
      MAKE(Question)
	}
   return true;
}

bool MSyntax::Unary()
{
	if (Match(T_Symbol::prUnary) || Match(T_Symbol::prTerm) || Match(T_Symbol::prIncDec)) {
	   if (!Unary()) return false;
      MAKE(Unary)
      return true;
	}
   if (Match(T_Lexeme::sxCastUnary)) { // ([const] int) unary
	   if (!Unary()) return false;
      MAKE(Cast)
      return true;
	}
   if (!Primary()) return false;
	while (Match(T_Symbol::prIncDec)) {
      MAKE(IncDec)
   }
   return true;
}

bool MSyntax::Call()
{
	if (Match(T_Lexeme::sxEmptyBracket)) {
      MAKE(Params)
		return true;
	}
   if (Match(T_Lexeme::grSeparator, T_Symbol::lxLeftBracket)) {
      EXPRESSION(ValueList)
      if (!Match(T_Lexeme::grSeparator, T_Symbol::lxRightBracket)) return false;
      PARAM(Params,0x01)
		return true;
	}
   return false;
}

bool MSyntax::Index()
{
   MAKE(BegIndexLL)
   while (Match(T_Lexeme::grSeparator, T_Symbol::lxLeftScrape)) {
      EXPRESSION(Value) 
      if (!Match(T_Lexeme::grSeparator, T_Symbol::lxRightScrape)) return false;
      MAKE(IndexLL)
   }
   MAKE(EndIndex)
   return true;
}

bool MSyntax::Primary()
{
	if (Match(T_Lexeme::sxIdentFunc)) {
		return Call();
	}
	if (Match(T_Lexeme::sxIdentArr)) {
   	return Index();
	}
   if (Match(T_Lexeme::grIdent)) {
      MAKE(Ident)
		return true;
	}
   if (Match(T_Lexeme::grInteger)) {
      MAKE(Number) 
      return true;
   }
   if (Match(T_Lexeme::grNumber)) {
      MAKE(Number) 
      return true;
   }
   if (Match(T_Lexeme::grSeparator, T_Symbol::lxLeftBracket)) {
      EXPRESSION(None)
      MAKE_TREE(Primary)
      return Match(T_Lexeme::grSeparator, T_Symbol::lxRightBracket);
      }
   if (Match(T_Lexeme::sxCast)) {
	   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
      EXPRESSION(None) 
      if (!MatchMust(T_Symbol::lxRightBracket)) return false;
      MAKE(Cast)
      return true;
   }
   return error(erPrimary);
}

bool MSyntax::Binary(T_Symbol::T_Priority priority)
{
   if ((priority + 1) < T_Symbol::prUnary) {
      if (!Binary(T_Symbol::T_Priority(priority + 1))) return false;
   } else {
      if (!Unary()) return false;
   }
   while (Match(priority)) {
      if ((priority + 1) < T_Symbol::prUnary) {
         if (!Binary(T_Symbol::T_Priority(priority + 1))) return false;
      } else {
         if (!Unary()) return false;
      }
      MAKE(Binary)
   }
   return true;
}

bool MSyntax::DefParArr()
{
   if (!Match(T_Lexeme::sxIdentArr)) return false;
   MAKE(DefParArr)
   if (!DefArrDA()) return false;
   if (Match(T_Lexeme::grOper, T_Symbol::lxAssign)) {
      MAKE_CODE(BegParVarAssign)
      if (!Assign()) return false;
      MAKE(ParVarAssign)
   }
   return true;
}

bool MSyntax::DefParVar()
{
   if (!Match(T_Lexeme::grIdent)) return false;
   MAKE(DefParVar) 
   if (Match(T_Lexeme::grOper, T_Symbol::lxAssign)) {
      MAKE_CODE(BegParVarAssign)
      if (!Assign()) return false;
      MAKE(ParVarAssign)
   }
   return true;
}

bool MSyntax::DefParItem()
{
   if (Match(T_Lexeme::sxDefArr)) {
      if (!DefParArr()) return false;
   } else if (Match(T_Lexeme::sxDefVar)) {
      if (!DefParVar()) return false;
   } else {
      return false;
   }
   MAKE_TREE(AddToList)
   return true;
}

bool MSyntax::DefParams()
{
   PARAM_TREE(Define,0x02)
   do {
      if (!DefParItem()) return false;
   } while (Match(T_Lexeme::grSeparator, T_Symbol::lxComma));
   MAKE_TREE(EndParams)
   return true;
}

bool MSyntax::DefFunc()
{
   if (!Match(T_Lexeme::sxIdentFunc)) return false;
   MAKE(FuncIdent)
   if (Match(T_Lexeme::sxEmptyBracket)) {
      PARAM_TREE(EndParams,0x02)
   } else {
      if (!(Match(T_Lexeme::grSeparator, T_Symbol::lxLeftBracket) && DefParams() && Match(T_Lexeme::grSeparator, T_Symbol::lxRightBracket))) return false;
   }
   return BodyFunc();
}

bool MSyntax::BodyFunc()
{
   if (Match(T_Lexeme::grSeparator, T_Symbol::lxSemicolon)) {
      PARAM(BodyFunc,0x00)
   } else if (Match(T_Lexeme::sxEmptyCramp)) {
      PARAM(BodyFunc,0x01)
   } else if (Match(T_Lexeme::grSeparator, T_Symbol::lxLeftCramp)) {
      MAKE_CODE(EndParams)
      if (!StmExpr() || !Match(T_Lexeme::grSeparator, T_Symbol::lxRightCramp)) return false;
      PARAM(BodyFunc,0x02)
   } else {
      return false;
   }
   return true;
}

bool MSyntax::DefArrDA() 
{
   if (Match(T_Lexeme::sxEmptyScrape)) {
      MAKE(DefArrD1AEmpty)
   }
   while (Match(T_Lexeme::grSeparator, T_Symbol::lxLeftScrape)) {
      if (!Assign() || !Match(T_Lexeme::grSeparator, T_Symbol::lxRightScrape)) return false;
      MAKE(DRange)
   }
   MAKE_CODE(EndRanges) 
   return true;
}

bool MSyntax::AInitial()
{
   do {
      if (!AInitItem()) return false;
      MAKE_TREE(AddToList)
   } while(Match(T_Lexeme::grSeparator, T_Symbol::lxComma));
   return true;
}

bool MSyntax::AInitItem()
{
   int ret = Initializer();
   if (ret >= 0) return (ret > 0); 
   if (!Assign()) return false;
   MAKE_CODE(AInitItem)
   return true;
}

int  MSyntax::Initializer()
{
   if (Match(T_Lexeme::sxEmptyCramp)) {
      MAKE_CODE(BegInitial) MAKE_TREE(NodeListLL)
      return 1;
   }
   if (Match(T_Lexeme::grSeparator, T_Symbol::lxLeftCramp)) {
      PARAM_CODE(BegInitial,0x01) MAKE_TREE(NodeListLL)
      if (!AInitial()) return 0; 
      if (!MatchMust(T_Symbol::lxRightCramp)) return 0;
      MAKE_CODE(EndInitial)
      return 1;
   }
   return -1;
}

bool MSyntax::DefArr()
{
   MAKE(DefArray) 
   if (!DefArrDA()) return false;
   if (Match(T_Lexeme::grOper, T_Symbol::lxAssign)) {
      MAKE_CODE(BegAInit)
      if (Initializer() <= 0) return false; 
      MAKE(EndAInit)
   }
   return true;
}

bool MSyntax::DefVar()
{
   MAKE(DefIdent)
   return DefVarInit();
}

bool MSyntax::DefVarInit()
{
   if (Match(T_Lexeme::grOper, T_Symbol::lxAssign)) {
      MAKE_CODE(BegDefVarAssign) 
      if (!Assign()) return false;
      MAKE(DefVarAssign)
   }
   return true;
}

bool MSyntax::DefItem()
{
   bool reference = Match(T_Lexeme::grOper, T_Symbol::lxAnd);
   if (Match(T_Lexeme::sxIdentArr)) {
      if (!DefArr()) return false;
   } else if (Match(T_Lexeme::grIdent)) {
      if (!DefVar()) return false;
   } else {
      return false;
   }
   if (reference) {
      MAKE_TREE(RefDef)
   }
   return true;
}

bool MSyntax::DefineSemi()
{
   MAKE(Define)
   do {
      if (!DefItem()) return false;
      MAKE_TREE(AddToList)
   } while (Match(T_Lexeme::grSeparator, T_Symbol::lxComma));
   MAKE_CODE(EndDefine) 
   return Match(T_Lexeme::grSeparator, T_Symbol::lxSemicolon);
}

bool MSyntax::ExprSemi()
{
   EXPRESSION(Expression)
   return Match(T_Lexeme::grSeparator, T_Symbol::lxSemicolon);
}

bool MSyntax::DefExpr()
{ 
   if (Match(T_Lexeme::grSeparator, T_Symbol::lxSemicolon)) {
      MAKE_TREE(NodeNull) 
      return true;
   }
   if (Match(T_Lexeme::sxDefType)) {
      return DefineSemi();
   }
   int ret = Statement();
   if (ret >= 0) return (ret == 1);
   return ExprSemi();
}

bool MSyntax::StmExpr()
{ 
   MAKE(BegStmExprLL)
   do {
      if (!DefExpr()) return false;
      MAKE_TREE(AddToList)
   } while(!MatchSpot(T_Symbol::lxRightCramp)); 
   MAKE_CODE(EndBlock)
   return true;
}

bool MSyntax::DefFuncArrVar()
{
   if (Match(T_Lexeme::grSeparator, T_Symbol::lxSemicolon)) {
      MAKE_TREE(NodeNull)
      return true;
   }
   if (Match(T_Lexeme::sxDefFunc)) {
      return DefFunc();
   }
   if (Match(T_Lexeme::sxDefType)) {
      return DefineSemi();
   }
   return false;
}

bool MSyntax::Defines()
{
   MAKE(BegStmExprLL)
   while (!Match(T_Lexeme::grEof)) {
      if (!DefFuncArrVar()) return false;
      MAKE_TREE(AddToList)
   }
   MAKE_CODE(EndBlock)
   return true;
}

bool MSyntax::Translate()
{
   makers = &GMakerTable::maker_table;
   bool ret = Defines();
   return ret;
}

int  MSyntax::Statement()
{
   if (Match(T_Lexeme::sxLabel) && Match(T_Lexeme::grSeparator, T_Symbol::lxColon)) {
      MAKE_CODE(Label) 
      if (!DefExpr()) return false;
      MAKE_TREE(Label)
      return true;
   } 
   if (Match(T_Lexeme::W_Type::rwFor))      return For();
   if (Match(T_Lexeme::W_Type::rwWhile))    return While();
   if (Match(T_Lexeme::W_Type::rwIf))       return If();
   if (Match(T_Lexeme::W_Type::rwDo))       return Do();
   if (Match(T_Lexeme::W_Type::rwContinue)) return Continue();
   if (Match(T_Lexeme::W_Type::rwBreak))    return Break();
   if (Match(T_Lexeme::W_Type::rwGoTo))     return GoTo();
   if (Match(T_Lexeme::W_Type::rwReturn))   return Return();
   if (Match(T_Lexeme::W_Type::rwSwitch))   return Switch();
   if (Match(T_Lexeme::grSeparator, T_Symbol::lxLeftCramp)) return Compaund();

   return -1;
}

bool MSyntax::Expressions()
{
   if (!Assign()) return false;
   MAKE(ExpressionsLL)
   while (Match(T_Lexeme::grSeparator, T_Symbol::lxComma)) {
      if (!Assign()) return false;
      MAKE_TREE(AddToList) MAKE_CODE(AddToExpr)
   }
   MAKE_CODE(ExpressionSLL)
   return true;
}

bool MSyntax::Condition()
{
   if (Match(T_Lexeme::sxDefType)) {
      MAKE(Define)
      bool ref = Match(T_Lexeme::grOper, T_Symbol::lxAnd); 
      if (!Match(T_Lexeme::grIdent) || !DefVar()) return false;
      if (ref) {
         MAKE_TREE(RefDef)
      }
      MAKE(PushDef) 
      return true;
   } 
   EXPRESSION(Condition)
   return true;
}

bool MSyntax::Compaund()
{
   if (Match(T_Lexeme::grSeparator, T_Symbol::lxRightCramp)) {
      MAKE(Compaund) 
      MAKE_CODE(EndBlock) 
      return true;
   }
   MAKE(Compaund) 
   if (!StmExpr()) return false; 
   MAKE_CODE(EndBlock) 
   MAKE_TREE(AddToList)
   return Match(T_Lexeme::grSeparator, T_Symbol::lxRightCramp);
}

bool MSyntax::For()
{
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   MAKE(BegFor)
// prefix
   if (Match(T_Lexeme::grSeparator, T_Symbol::lxSemicolon)) {
      MAKE_TREE(NodeNull)
   } else if (Match(T_Lexeme::sxDefType)) {
      if (!DefineSemi()) return false;
   } else {
      if (!ExprSemi()) return false;
   }
   MAKE_CODE(PrefFor)
// condition
   if (Match(T_Lexeme::grSeparator, T_Symbol::lxSemicolon)) {
      MAKE(NodeNull)
   } else {
      if (!Condition() || !MatchMust(T_Symbol::lxSemicolon)) return false;
   }
   MAKE_CODE(ConditionFor)
// postfix
   if (Match(T_Lexeme::grSeparator, T_Symbol::lxRightBracket)) {
      MAKE_TREE(NodeNull)
   } else {
      EXPRESSION(Expression)
      if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   }
   MAKE_CODE(PostFor)
// body
   if (!DefExpr()) return false;
   MAKE(For)
   return true;
}

bool MSyntax::While()
{
   MAKE(BegWhile) 
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   if (!Condition()) return false;
   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   MAKE_CODE(MidWhile) 
   if (!DefExpr()) return false;
   MAKE(While) 
   return true;
}

bool MSyntax::If()
{
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   MAKE_CODE(BegIf)
   if (!Condition()) return false;
   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   MAKE_CODE(Then)
   if (!DefExpr()) return false;
   if (Match(T_Lexeme::W_Type::rwElse)) {
      MAKE_CODE(Else) 
      if (!DefExpr()) return false;
      PARAM(If,0x01)
   } else {
      MAKE(If)
   }
   return true;
}

bool MSyntax::Do()
{
   MAKE(BegDo)
   if (!DefExpr()) return false;
   if (!Match(T_Lexeme::W_Type::rwWhile)) return false;
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   MAKE_CODE(MidDo) 
   if (!Condition()) return false;
   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   MAKE(Do)
   return MatchMust(T_Symbol::lxSemicolon);
}

bool MSyntax::GoTo()
{
   if (!Match(T_Lexeme::grIdent)) return false;
   MAKE(GoTo)
   return MatchMust(T_Symbol::lxSemicolon);
}

bool MSyntax::Continue()
{
   MAKE(Continue)
   return MatchMust(T_Symbol::lxSemicolon);
}

bool MSyntax::Break()
{
   MAKE(Break)
   return MatchMust(T_Symbol::lxSemicolon);
}

bool MSyntax::Return()
{
	if (Match(T_Lexeme::grSeparator, T_Symbol::lxSemicolon)) {
      MAKE(Return)
      return true;
   }
   EXPRESSION(Value)
   PARAM(Return,0x01)
   return MatchMust(T_Symbol::lxSemicolon);
}

bool MSyntax::Switch()
{

   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   if (!Expressions()) return false;
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
//         if (!Statement(T_Part::psCase)) return false;
      }
   } while (!Match(T_Lexeme::grSeparator, T_Symbol::lxRightCramp));
   if (!case_count || (default_count > 1)) return false;
   return true;
}


