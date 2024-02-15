#ifndef TRN_TREE_SYNTAX_H
#define TRN_TREE_SYNTAX_H

#include "Parse.h"
#include "ASyntax.h"
#include <stack>
 
// --------------------------- TSyntax ---------------------------
class TNode     ;
class T_NodeList;
class TNodeError;
class TNodeType ;

class TSyntax : public A_Syntax
{
public:
	TSyntax(T_Scan *s);

	TNode* Assign();	
	TNode* Question();
	TNode* Unary();
	TNode* Primary();

	TNode* Binary(T_Symbol::T_Priority priority);

	TNodeError* error() { return current_error; }
	TNodeError* error(T_Error code, int value = 0) { return error(code,lex,value); }
	TNodeError* error(T_Error code, const T_Lexeme &l, int value);
	virtual bool MatchMust(T_Symbol::T_Type t);
   virtual void clear(TNode* node);

	TNode* Expressions(T_Part part = T_Part::psNone);
   TNode* Compaund();

   TNode* Statement(T_Part part);
   TNode* Statements(T_Part part);

	TNode* Define(T_Part part, int constant); // 0x02 - static, 0x01 - const
	TNode* DefineItem(const T_Lexeme &l, T_Part part, int constant);  // 0x02 - static, 0x01 - const
   TNode* DefineParam();
   TNode* DefineParams();
   TNode* Initializer();
   TNode* InitializerItem();

	TNode* For();
	TNode* If();
	TNode* While();
	TNode* Do();
	TNode* GoTo();
	TNode* BreakContinue(T_Block rate);
	TNode* Return();
	TNode* Switch();

public:
   virtual bool Translate();
protected:
   TNodeError *current_error;
};

#endif
