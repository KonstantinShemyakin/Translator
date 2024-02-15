#ifndef TRN_CSYNTAX_H
#define TRN_CSYNTAX_H

#include "Parse.h"
#include "ASyntax.h"
#include "TNodes.h"
 
// --------------------------- CSyntax ---------------------------
class TSemantic;

struct TExprStackItem {
public:
   TExprStackItem() :part(T_Part::psNone), param(0), made(0), type(T_BaseType::btUnknown), node(NULL), true_label(NULL), false_label(NULL) {}
   TExprStackItem(T_Part p) :part(p), param(0), made(0), type(T_BaseType::btUnknown), node(NULL), true_label(NULL), false_label(NULL) {}
   TExprStackItem(T_BaseType t) :part(T_Part::psNone), param(0), made(0), type(t), node(NULL), true_label(NULL), false_label(NULL) {}
   TExprStackItem(T_BaseType t, const T_Lexeme &l) :lexeme(l), part(T_Part::psNone), param(0), made(0), type(t), node(NULL), true_label(NULL), false_label(NULL) {}
   TExprStackItem(TNode* n) :part(T_Part::psNone), param(0), made(0), type(T_BaseType::btUnknown), node(n), true_label(NULL), false_label(NULL) {}
   bool value() const { return (type != btVoid) && (type != btLogical) && (type != btUnknown); }
public:
   T_Part part;
   int    made, param;
   TNodeLabel *true_label, *false_label;
   T_BaseType type;
   T_Lexeme   lexeme;
   TNode*     node;
};

class TExprStack : public std::stack<TExprStackItem> {
public:
   TExprStack() {}
   void Push(const TExprStackItem& item) { push(item); }
   void Push(T_BaseType t)               { Push(TExprStackItem(t)); }
   TExprStackItem& Top()                 { return top(); }
   void Pop()                            { pop(); }
   T_BaseType PopType()                  { if (empty()) return btUnknown; T_BaseType ret = Top().type; Pop(); return ret; }
public:
};

class C_Syntax
{
public:
	C_Syntax() :stack(), semantic(NULL), trunc_type(0) {}
   bool UnaryOper(const T_Lexeme &l);
   bool BinaryOper(const T_Lexeme &l);
   bool BinaryLogic(const T_Lexeme &l);
   bool GenCastable(T_BaseType from, T_BaseType to, int& made);
   bool GenCastable(T_BaseType from, T_BaseType to) { int made = -1; return GenCastable(from, to, made); }
   bool MakeLogic();
   void MakeValue();
   void GenReturn(bool value);
   bool GenBreakContinue(T_Block r, const T_Lexeme &l);
   void GenGoTo(const T_Lexeme &l);

   T_BaseType PopType()                  { return stack.PopType(); }
   void Push(const TExprStackItem& item) { stack.Push(item); stack.Top().made = made(); } // +made
   void Push(T_BaseType t)               { Push(TExprStackItem(t)); }
   void PushWithoutMade(const TExprStackItem& item) { stack.Push(item); } // !made
   void Pop()                            { stack.Pop(); }
   TExprStackItem& Top()                 { return stack.Top(); }
   TExprStackItem  TipTop()              { TExprStackItem item = stack.Top(); stack.Pop(); return item; }
   int  CountTypes() const               { return (int)stack.size(); }
   void TruncTypes(int trunc)            { while (trunc < CountTypes()) { stack.pop(); trunc_type++; } }

   void AddCode(TNode* code, int counter = -1);
   void InsCode(TNode* code, int counter);
   int  made();
   TNode* GetCommand(int counter);

   void set_semantic(TSemantic* s) { semantic = s; }

	virtual bool error_code(T_Error code, int value = 0) { return false; }

public:
   TSemantic* semantic;
   TExprStack stack;
   int trunc_type;
};

class CSyntax : public A_Syntax, public C_Syntax
{
public:
   CSyntax(T_Scan *s) :A_Syntax(s) { option_mode = mmCode; }

	bool Assign();	
	bool Question();
	bool Unary();
	bool Primary();
   bool Call(const T_Lexeme &l);
   bool Index(const T_Lexeme &l);
   bool Function(TNodeDefFunc *function, int &def);
   bool Array(TNodeDefArr *arr);

	bool Binary(T_Symbol::T_Priority priority);

	bool Expressions(T_Part part = T_Part::psNone);
   bool Statement(T_Part part);
   bool Statements(T_Part part);
   bool Compaund();

	bool Define(T_Part part, int constant); // 0x02 - static, 0x01 - const
	int  DefineItem(const T_Lexeme &l, T_Part part, int constant, TNode* &node); // 0x02 - static, 0x01 - const
   bool DefineParam(TNodeDefVar* &par);
   bool Initializer(TNodeDefArr &arr, int level);
	bool For();
	bool If();
	bool While();
	bool Do();
	bool GoTo();
	bool BreakContinue(T_Block rate);
	bool Return();
	bool Switch();

public:
   virtual bool Translate();
   virtual void clear(TNode* node);
	virtual bool error_code(T_Error code, int value = 0) { return A_Syntax::error(code,value); }

};

#endif

