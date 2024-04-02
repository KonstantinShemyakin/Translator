// Parse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Syntax.h"

// --------------------------- T_Syntax ---------------------------

bool T_Syntax::Assign()
{
   if (!Question()) return false;
	if (Match(T_Symbol::prAssign)) {
	   return Assign();
	}
   return true;
}

bool T_Syntax::Question()
{
#ifndef EXPRESION_BINARY
   if (!OrOr()) return false;
#else
   if (!Binary(T_Symbol::prOrOr)) return false;
#endif
	if (Match(T_Symbol::prQuestion)) {
	   if (!Expressions()) return false;
		if (!MatchMust(T_Symbol::lxColon)) return false;
	   return Question();
	}
   return true;
}

#ifndef EXPRESION_BINARY
bool T_Syntax::OrOr()
{
   if (!AndAnd()) return false;
   while (Match(T_Symbol::prOrOr)) {
      if (!AndAnd()) return false;
      }
   return true;
}

bool T_Syntax::AndAnd()
{
   if (!Or()) return false;
   while (Match(T_Symbol::prAndAnd)) {
      if (!Or()) return false;
      }
   return true;
}

bool T_Syntax::Or()
{
   if (!XOr()) return false;
   while (Match(T_Symbol::prOr)) {
      if (!XOr()) return false;
      }
   return true;
}

bool T_Syntax::XOr()
{
   if (!And()) return false;
   while (Match(T_Symbol::prXOr)) {
      if (!And()) return false;
      }
   return true;
}

bool T_Syntax::And()
{
   if (!Equ()) return false;
   while (Match(T_Symbol::prAnd)) {
      if (!Equ()) return false;
      }
   return true;
}

bool T_Syntax::Equ()
{
   if (!Compare()) return false;
   while (Match(T_Symbol::prEqu)) {
      if (!Compare()) return false;
      }
   return true;
}

bool T_Syntax::Compare()
{
   if (!Shift()) return false;
   while (Match(T_Symbol::prCompare)) {
      if (!Shift()) return false;
      }
   return true;
}

bool T_Syntax::Shift()
{
   if (!Term()) return false;
   while (Match(T_Symbol::prShift)) {
      if (!Term()) return false;
      }
   return true;
}

bool T_Syntax::Term()
{
   if (!Factor()) return false;
   while (Match(T_Symbol::prTerm)) {
      if (!Factor()) return false;
      }
   return true;
}

bool T_Syntax::Factor()
{
   if (!Unary()) return false;
   while (Match(T_Symbol::prFactor)) {
      if (!Unary()) return false;
      }
   return true;
}
#endif

bool T_Syntax::Unary()
{
	if (Match(T_Symbol::prUnary) || Match(T_Symbol::prTerm) || Match(T_Symbol::prIncDec)) {
	   return Unary();
	}
   T_ScanStore store; Store(store);
   if (Match(T_Symbol::lxLeftBracket)) { // ([const] int) unary
   	bool constant = Match(T_Lexeme::W_Type::rwConst);
      if (Match(T_Lexeme::W_Type::rwDefine) && Match(T_Symbol::lxRightBracket)) {
   	   return Unary();
      } else {
         if (constant) return error(erUnknownCast);
      } 
	}
   Restore(store);
   if (!Primary()) return false;
	while (Match(T_Symbol::prIncDec)) {}
   return true;
}

bool T_Syntax::Primary()
{
   if (Match(T_Lexeme::grIdent)) {
		if (Match(T_Symbol::lxLeftBracket)) {
			if (!Match(T_Symbol::lxRightBracket)) {
			   do {
					if (!Expressions()) return false;
				} while (Match(T_Symbol::lxComma));
			   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
			}
			return true;
		}
		while (Match(T_Symbol::lxLeftScrape)) {
			if (!Expressions()) return false;
		   if (!MatchMust(T_Symbol::lxRightScrape)) return false;
		}
		return true;
	}
   if (Match(T_Lexeme::grInteger)) return true;
   if (Match(T_Lexeme::grNumber)) return true;
   if (Match(T_Symbol::lxLeftBracket)) {
      return Expressions() && Match(T_Symbol::lxRightBracket);
      }
   if (Match(T_Lexeme::W_Type::rwDefine)) {
	   return MatchMust(T_Symbol::lxLeftBracket) && Expressions() && MatchMust(T_Symbol::lxRightBracket);
   }
   return error(erPrimary);
}

bool T_Syntax::Binary(T_Symbol::T_Priority priority)
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
   }
   return true;
}

bool T_Syntax::Statements(T_Part part)
{
   while (!Match(T_Lexeme::grEof)) {
      if (!Statement(part)) return false;
   }
   return true;
}

bool T_Syntax::Translate()
{
   return Statements(T_Part::psMain);
}

bool T_Syntax::Statement(T_Part part)
{

	if (Match(T_Symbol::lxSemicolon)) return !(part & T_Part::psNoSemicolon);

   if (part & T_Part::psDefine) {
      T_Lexeme l;
      int def = SCDefine(l,0x26); // -1 - error, 0, 0x01 - define, 0x02 - const, 0x04 - static, 0x20 - void
		if (def < 0) return false;
		if (def) {
         forward = l;
		   return Define(part);
		}
	}
   if (part & T_Part::psStatement) {
      T_ScanStore store; Store(store);
      if (Match(T_Lexeme::grIdent) && Match(T_Symbol::lxColon)) {
         return Statement(T_Part::psLabel);
      } 
      Restore(store);
      if (Match(T_Lexeme::W_Type::rwFor))      return For();
      if (Match(T_Lexeme::W_Type::rwWhile))    return While();
      if (Match(T_Lexeme::W_Type::rwIf))       return If();
      if (Match(T_Lexeme::W_Type::rwDo))       return Do();
      if (Match(T_Lexeme::W_Type::rwContinue)) return Continue();
      if (Match(T_Lexeme::W_Type::rwBreak))    return Break();
      if (Match(T_Lexeme::W_Type::rwGoTo))     return GoTo();
      if (Match(T_Lexeme::W_Type::rwReturn))   return Return();
      if (Match(T_Lexeme::W_Type::rwSwitch))   return Switch();
	}
   if (part & T_Part::psCompaund) {
      if (Match(T_Symbol::lxLeftCramp)) return Compaund();
	}

   if (part & T_Part::psExpression) {
      return Expressions() && ((part & T_Part::psNoSemicolon) || Match(T_Symbol::lxSemicolon));
	}

   return false;
}

bool T_Syntax::Expressions()
{
   do {
      if (!Assign()) return false;
   } while (Match(T_Symbol::lxComma));
   return true;
}

bool T_Syntax::Compaund()
{
   while (!Match(T_Symbol::lxRightCramp)) {
      if (!Statement(T_Part::psBody)) return false;
   }
   return true;
}

bool T_Syntax::DefineParam()
{
   T_Lexeme l;
   int def = SCDefine(l, 0x0A); // -1 - error, 0, 0x01 - define, 0x02 - const, 0x04 - static, 0x08 - &
	if (def < 0) return false;
   if (!def) return error(erDefine);
   if (Match(T_Lexeme::grIdent)) {}
   int scrape = 0;
	while (Match(T_Symbol::lxLeftScrape)) {
	   if (!scrape++ && Match(T_Symbol::lxRightScrape)) continue;
		if (!Assign()) return false;
	   if (!MatchMust(T_Symbol::lxRightScrape)) return false;
	}
   if (Match(T_Symbol::lxAssign)) {
      return Assign();
   }
   return true;
}

bool T_Syntax::DefineParams()
{
   do {
      if (!DefineParam()) return false;
   } while (Match(T_Symbol::lxComma));
   return true;
}

bool T_Syntax::InitializerItem()
{
   if (MatchSpot(T_Symbol::lxLeftCramp)) return Initializer();
   return Assign();
}

bool T_Syntax::Initializer()
{
   if (!MatchMust(T_Symbol::lxLeftCramp)) return false;
   if (Match(T_Symbol::lxRightCramp)) return true;
   do {
      if (!InitializerItem()) return false;
   } while (Match(T_Symbol::lxComma));
   if (!MatchMust(T_Symbol::lxRightCramp)) return false;
   return true;
}

int T_Syntax::DefineItem(const T_Lexeme &lexeme, T_Part part)
{
	bool reference = (Match(T_Symbol::lxAnd));
   if (!Match(T_Lexeme::grIdent)) return error(erNoIdent);
   if (Match(T_Symbol::lxLeftBracket)) {
      if (!(part & psDefFunc)) return error(erDefFunc);
		if (!Match(T_Symbol::lxRightBracket)) {
         if (!DefineParams()) return false;
		   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
         }
      return -1;
   }
   if (lexeme.Match(T_Lexeme::W_Type::rwVoid)) return false;
   if (Match(T_Symbol::lxAssign)) {
      return Assign();
   }
   int scrape = 0;
	while (Match(T_Symbol::lxLeftScrape)) {
	   if (!scrape++ && Match(T_Symbol::lxRightScrape)) continue;
		if (!Assign()) return false;
	   if (!MatchMust(T_Symbol::lxRightScrape)) return false;
	}
   if (scrape && Match(T_Symbol::lxAssign)) {
      return Initializer();
   }
   return true;
}

bool T_Syntax::Define(T_Part part)
{
   T_Lexeme lexeme = forward;
   int count = 0, def;
   do {
      def = DefineItem(lexeme, part);
      if (!def) return false;
      count++;
   } while (Match(T_Symbol::lxComma));
   if ((count == 1) && (def == -1)) {
      if (Match(T_Symbol::lxLeftCramp)) {
         if (!Compaund()) return false;
         def = -2;
      }
   }
   return (part & T_Part::psNoSemicolon) || Match(T_Symbol::lxSemicolon) || (def == -2);
}

bool T_Syntax::For()
{
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   if (!Statement(T_Part::psForBeg)) return false;
   if (!Statement(T_Part::psForExpr)) return false;
   if (!Match(T_Symbol::lxRightBracket)) {
      if (!Expressions()) return false;
      if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   }
   if (!Statement(T_Part::psBody)) return false;
   return true;
}

bool T_Syntax::While()
{
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   if (!Statement(T_Part::psCondition)) return false;
   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   if (!Statement(T_Part::psBody)) return false;
   return true;
}

bool T_Syntax::If()
{
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   if (!Statement(T_Part::psCondition)) return false;
   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   if (!Statement(T_Part::psBody)) return false;
   if (Match(T_Lexeme::W_Type::rwElse)) {
      if (!Statement(T_Part::psBody)) return false;
   }
   return true;
}

bool T_Syntax::Do()
{
   if (!Statement(T_Part::psBody)) return false;
   if (!Match(T_Lexeme::W_Type::rwWhile)) return false;
   if (!MatchMust(T_Symbol::lxLeftBracket)) return false;
   if (!Statement(T_Part::psCondition)) return false;
   if (!MatchMust(T_Symbol::lxRightBracket)) return false;
   return MatchMust(T_Symbol::lxSemicolon);
}

bool T_Syntax::GoTo()
{
   return Match(T_Lexeme::grIdent) && MatchMust(T_Symbol::lxSemicolon);
}

bool T_Syntax::Continue()
{
   return MatchMust(T_Symbol::lxSemicolon);
}

bool T_Syntax::Break()
{
   return MatchMust(T_Symbol::lxSemicolon);
}

bool T_Syntax::Return()
{
	if (Match(T_Symbol::lxSemicolon)) return true;
   if (!Expressions()) return false;
   return MatchMust(T_Symbol::lxSemicolon);
}

bool T_Syntax::Switch()
{
	const int i = 0;
	switch (i) {
	case (i + 5) :;
	}


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
         if (!Statement(T_Part::psCase)) return false;
      }
   } while (!Match(T_Symbol::lxRightCramp));
   if (!case_count || (default_count > 1)) return false;
   return true;
}
