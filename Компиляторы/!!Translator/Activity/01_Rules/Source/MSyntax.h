#ifndef TRN_MSYNTAX_H
#define TRN_MSYNTAX_H

#include "Maker.h"
 
// --------------------------- MSyntax ---------------------------
class MSyntax : public MC_Syntax
{
public:
	MSyntax(T_Scan *s, TGrammar* g) :MC_Syntax(s), grammar(g) {}

	bool Assign();	
	bool Question();

	bool Unary();
   bool Index();
   bool Call();
	bool Primary();

	bool Binary(T_Symbol::T_Priority priority);

	bool error(T_Error code, int value = 0) { return error(code,lex,value); }
	bool error(T_Error code, const T_Lexeme &l, int value) {  return Error.error(code,l,value); }

	bool Expressions();
   bool Condition();
   int  Statement();

   bool DefParArr();
   bool DefParVar();
   bool DefParItem();
   bool DefParams();
   bool DefFunc();
   bool BodyFunc();

   bool DefArrDA();
   bool AInitial();
   bool AInitItem();
   int  Initializer();
   bool DefArr();
   bool DefVar();
   bool DefVarInit();
   bool DefItem();
   bool DefineSemi();
   bool ExprSemi();
   bool DefExpr();
   bool StmExpr();
   bool Defines();
   bool DefFuncArrVar();
   bool Compaund();

	bool For();
	bool If();
	bool While();
	bool Do();
	bool GoTo();
	bool Continue();
	bool Break();
	bool Return();
	bool Switch();

   virtual bool Translate();
public:
   TGrammar*  grammar;
};

#endif

