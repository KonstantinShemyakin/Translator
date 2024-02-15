#ifndef TRN_GSYNTAX_H
#define TRN_GSYNTAX_H

#include "Maker.h"

// --------------------------- GSyntax ---------------------------
class GSyntax : public MC_Syntax, public S_Syntax
{
public:
   GSyntax(T_Scan *s, TGrammar* g) :S_Syntax(g), MC_Syntax(s), look_ahead(-1), rule_top(0) { unit.grammar = g; }

   virtual bool MatchAddLexeme(T_Lexeme& cur, const GSymbol& cur_sym, const GSymbol& must);
	virtual bool error_code(T_Error code, int value = 0) { return A_Syntax::error(code,value); }
   void SaveLexeme(const T_Lexeme& cur, const GSymbol& must);

   virtual bool ParseLL1();
   virtual bool ParseLLk();
   virtual bool ParseLL1_SN();
   virtual bool ParseLLk_SN();

   virtual bool ParseLR0();
   virtual bool ParseLRk();
   virtual bool ParseLR0_SN();
   virtual bool ParseLRk_SN();
   virtual bool VerifyLR0(const GSymbol& sym);

   virtual bool Translate();
public:
   virtual bool LexemeToSymbol(T_Lexeme& lexeme, GSymbol& sym) { sym = GSymbol(lexeme); return true; }
public:
   int look_ahead;
public:
   const GFormula& Formula(const GSymbol &sym) const;
   const GProduce& Produce(const GSymbol &sym) const;
   const GSymbol&  Cell(const TTableKey& key) const;
   const TAction&  Action(const TTableKey& key) const;
private:
   void va_entry(const GSymbol& symbol) { va_stack.push_back(TStackRuleItem(symbol)); }
   void va_leave()          { if (!va_stack.empty()) va_stack.pop_back(); else rule_top--; }
   TStackRuleItem& va_top() { return va_stack.empty() ? rule_stack[rule_top - 1] : va_stack.back(); }
   bool va_empty() const    { return va_stack.empty() && (rule_top <= 0); }
   void va_clear()          { va_stack.clear(); rule_top = (int)rule_stack.size(); }
private:
   TStackRule va_stack;
   int  rule_top;
};

#endif

