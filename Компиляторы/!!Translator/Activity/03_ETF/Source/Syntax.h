#ifndef TRN_SYNTAX_H
#define TRN_SYNTAX_H

#include "Parse.h"
#include "ASyntax.h"
 
// --------------------------- T_Syntax ---------------------------

#define EXPRESION_BINARY
class T_Syntax : public A_Syntax
{
public:
	T_Syntax(T_Scan *s) : A_Syntax(s) {}

	bool Assign();	
	bool Question();
#ifndef EXPRESION_BINARY
   bool OrOr();
	bool AndAnd();
	bool Or();
	bool XOr();
	bool And();
	bool Equ();
	bool Compare();
	bool Shift();
	bool Term();
	bool Factor();
#endif
   bool Unary();
	bool Primary();

	bool Binary(T_Symbol::T_Priority priority);

	bool error(T_Error code, int value = 0) { return error(code,lex,value); }
	bool error(T_Error code, const T_Lexeme &l, int value) {  return Error.error(code,l,value); }

	bool Expressions();
   bool Statement(T_Part part);
   bool Statements(T_Part part);
   bool Compaund();

	bool Define(T_Part part);
	int  DefineItem(const T_Lexeme &l, T_Part part);
   bool DefineParam();
   bool DefineParams();
   bool Initializer();
   bool InitializerItem();
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

protected:
};

#endif

