#ifndef TRN_DOWN_SYNTAX_H
#define TRN_DOWN_SYNTAX_H

#include "Parse.h"
#include "ASyntax.h"
#include <stack>
 
// --------------------------- DSyntax ---------------------------
class TNode     ;
class T_NodeList;
class TNodeError;
class TNodeType ;

class DSyntax : public A_Syntax
{
public:
	DSyntax(T_Scan *s);

   bool Assign(TNode*);
   bool Question(TNode*);
   bool Unary(TNode*);
   bool Primary(TNode*);

   bool Binary(TNode*, T_Symbol::T_Priority priority);

   bool Expressions(TNode*, T_Part part = T_Part::psNone);
   bool Compaund(TNode*);

   bool Statement(TNode*, T_Part part);
   bool Statements(T_Part part);

   bool Define(TNode*,T_Part part, int constant); // 0x02 - static, 0x01 - const
   bool DefineItem(TNode*, const T_Lexeme &l, T_Part part, int constant);  // 0x02 - static, 0x01 - const
   bool DefineParam(TNode*);
   bool DefineParams(TNode*);
   bool Initializer(TNode*);
   bool InitializerItem(TNode*);

   bool For(TNode*);
   bool If(TNode*);
   bool While(TNode*);
   bool Do(TNode*);
   bool GoTo(TNode*);
   bool BreakContinue(TNode*, T_Block rate);
   bool Return(TNode*);
   bool Switch(TNode*);

public:
   virtual bool Translate();
protected:
   TNodeError *current_error;
};

#endif
