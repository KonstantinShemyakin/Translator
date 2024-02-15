#ifndef TRN_S_NODES_H
#define TRN_S_NODES_H

#include "Parse.h"

#define CLEAR_NODE(N) if (this->ClearNode(N)) { N = NULL; }
#define PRINT_NODE(N) if (N) { N->print(level + 1, printer); }
 
// --------------------------- SNode ---------------------------
class TNode;
class A_Syntax;
struct T_Lexeme_SNode;

class SNode {
public:
   enum S_Type { stNone, stNode, stUnary, stBinary, stLogical, stTrio, stNumber, stPrimary, stType, stCast, stIncDec,
                 stExpressions, stCompaund, stStatements, stDefVar, stDefArr, stDefFunc, stDefine, stVar,
                 stCall, stIndex, stFor, stWhile, stDo, stLabel, stGoTo, stBreak, stContinue, stReturn, stIf, 
                 stSwitchCase, stSwitchItem, stSwitch, stList, stRanges, stNull, stNodeOne, stNodeTwo, stRefDef, stLexeme, stParam,
                 stFormula, stProduce, stMaker, stTokens, stEnums, stItem,
                 st = stNone, st0 = stNone, stAddToList = stNone, stCopy = stNone
               }; 
   enum T_Turn { ttNone, ttPush, ttPut, ttAdd, ttMake, ttDown, ttUp, ttSwap, ttCommand };
   S_Type type;
   int    option;
public:
   SNode(S_Type s = stNone) :owner(NULL), lexeme(), type(s), option(0) {}
   SNode(const T_Lexeme& l, S_Type s = stNone) :owner(NULL), lexeme(l), type(s), option(0) {}
   virtual ~SNode() {}
   virtual TNode* Create(A_Syntax* syntax);
   virtual TNode* Make(A_Syntax* syntax) { return NULL; }
public:
   virtual void Add(SNode *r)          {} 
   virtual SNode *Get(int i)           { return NULL; }
   virtual int  Count() const          { return 0; }
public:
   bool ClearNode(SNode* N);
   virtual void clear();
public:
   const T_Lexeme& Lexeme() const      { return lexeme; }
   void SetLexeme(const T_Lexeme& l)   { lexeme = l; }
   virtual const T_Lexeme& FirstLexeme() const { return lexeme; }
protected:
   T_Lexeme lexeme;
public:
   SNode *Owner()                      { return owner; }
   void SetOwner(SNode *o)             { if (!owner || !o) owner = o; } 
protected:
   SNode *owner;
public:
   virtual const char* title() const   { return "SNode"; }
   virtual void print(int level, TPrinter& printer) const;
   static void YACC(TPrinter& printer);
};

class SNodeList : public SNode, public std::vector<SNode*> {
public:
   SNodeList(S_Type s = stNone) :SNode(s) {}
   SNodeList(const T_Lexeme& h, S_Type s) :SNode(h,s) {}
   SNodeList(const T_Lexeme& l, S_Type s, SNode *c) :SNode(l, s) { SetChild(c); }
   SNodeList(const T_Lexeme& h, S_Type s, SNode *l, SNode *r) :SNode(h, s) { SetBoth(l, r); }
   SNodeList(const T_Lexeme& h, S_Type s, SNode *l, SNode *m, SNode *r) :SNode(h, s) { SetThree(l, m, r); }
   SNodeList(const T_Lexeme& h, S_Type s, SNode *l, SNode *m, SNode *r, SNode *f) :SNode(h, s) { SetAll(l, m, r, f); }
   virtual ~SNodeList() {}
   virtual TNode* Create(A_Syntax* syntax);
   virtual TNode* Make(A_Syntax* syntax);
public:
   virtual const T_Lexeme& FirstLexeme() const;
public:
   SNode *Last()                       { if (empty()) return NULL; return back(); }
   void Insert(int i,SNode *r)         { r->SetOwner(this); insert(begin() + i, r); } 
public:
   virtual void Add(SNode *r)          { r->SetOwner(this); push_back(r); } 
   virtual SNode *Get(int i)           { return (*this)[i]; }
   virtual int  Count() const          { return (int)size(); }
public:
   SNode *Child()                      { if (size() < 1) return NULL; return (*this)[0]; }
   void SetChild(SNode *c)             { if (c) c->SetOwner(this); if (size() < 1) push_back(c); else (*this)[0] = c; }
   void MoveChild(SNode* c)            { if (c) c->SetOwner(NULL); SetChild(c); }
public:
   SNode *Left()                       { return Child(); }
   void SetLeft(SNode *l)              { SetChild(l); }
   void MoveLeft(SNode *l)             { MoveChild(l); }
   SNode *Right()                      { if (size() < 2) return NULL; return (*this)[1]; }
   void SetRight(SNode *r)             { if (r) r->SetOwner(this); if (size() < 1) push_back(NULL); if (size() < 2) push_back(r); else (*this)[1] = r; }
   void MoveRight(SNode *r)            { if (r) r->SetOwner(NULL); SetRight(r); }
   void SetBoth(SNode *l, SNode *r)    { SetLeft(l); SetRight(r); }
public:
   SNode *Mid()                        { if (size() < 3) return NULL; return (*this)[2]; }
   void SetMid(SNode *m)               { if (m) m->SetOwner(this); if (size() < 1) push_back(NULL); if (size() < 2) push_back(NULL); if (size() < 3) push_back(m); else (*this)[2] = m; }
   void SetThree(SNode *l, SNode *m, SNode *r) { SetBoth(l, r); SetMid(m); }
public:
   SNode *Four()                       { if (size() < 4) return NULL; return (*this)[3]; }
   void SetFour(SNode *f)              { if (f) f->SetOwner(this); if (size() < 1) push_back(NULL); if (size() < 2) push_back(NULL); if (size() < 3) push_back(NULL); if (size() < 4) push_back(f); else (*this)[3] = f; }
   void SetAll(SNode *l, SNode *m, SNode *r, SNode *f) { SetThree(l, m, r); SetFour(f); }
public:
   virtual void clear();
   virtual const char* title() const   { return "SNodeList"; }
   virtual void print(int level, TPrinter& printer) const;
};

#include "Rules.h"
// ------------------------- T_SyntaxNode ----------------------
class TProduceNode;
class T_SyntaxNode {
public:
   T_SyntaxNode() :child(0), owner(NULL) {}
   T_SyntaxNode(const GSymbol& sym) :symbol(sym), child(0), owner(NULL) {}
   virtual ~T_SyntaxNode() {}
   virtual void Add(T_SyntaxNode* node, int index) {}
   virtual void Insert(T_SyntaxNode* node, int index) {}
   virtual T_SyntaxNode* Get(int index) const { return NULL; }
public:
   virtual T_SyntaxNode* trim() { return NULL; }
   virtual void clear();
   virtual void print(TPrinter& printer, int level) const;
   virtual const char* title() const;
public:
   TProduceNode* owner;
   GSymbol symbol;
   int child;
};

class TLexemeNode : public T_SyntaxNode {
public:
   TLexemeNode() {}
   TLexemeNode(const GSymbol& sym) :T_SyntaxNode(sym) {}
   TLexemeNode(const T_Lexeme& lex) :T_SyntaxNode(lex), lexeme(lex) {}
   virtual ~TLexemeNode() {}
public:
   virtual void clear();
   virtual void print(TPrinter& printer, int level) const;
   virtual const char* title() const;
public:
   T_Lexeme lexeme;
};

class TProduceNode : public T_SyntaxNode, public std::vector<T_SyntaxNode*> {
public:
   TProduceNode() {}
   TProduceNode(const GSymbol& sym) :T_SyntaxNode(sym), children(0), master(0) {}
   virtual ~TProduceNode() {}
   virtual void Add(T_SyntaxNode* node, int index);
   virtual void Insert(T_SyntaxNode* node, int index);
   virtual T_SyntaxNode* Get(int index) const { return (*this)[index]; }
public:
   virtual T_SyntaxNode* trim();
   virtual void clear();
   virtual void print(TPrinter& printer, int level) const;
   virtual const char* title() const;
public:
   int children, master;
};

class TSyntaxTree {
public:
   TSyntaxTree() :root(NULL), grammar(NULL) {}
   T_SyntaxNode* tree() { return root; }
   T_SyntaxNode* New(const GSymbol& type);
   T_SyntaxNode* New(const T_Lexeme& lexeme);
   void operator = (T_SyntaxNode* join) { root = join; }
public:
   void trim();
   virtual void clear();
   void print(TPrinter& printer) const;
public:
   T_SyntaxNode* root;
   TGrammar* grammar;
};

const char* snode_title(SNode::S_Type t);
const char*  turn_title(SNode::T_Turn t);
SNode::S_Type title_snode_maker(const char* t);
SNode::T_Turn title_tnode_maker(const char* t);
#endif

