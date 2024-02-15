#ifndef TRN_TREE_NODES_H
#define TRN_TREE_NODES_H

#include "Parse.h"
#include "define_enum.h"

// --------------------------- TNode ---------------------------
class A_Syntax;
class TSemantic;
class TOperProfile;
class TFuncProfile;
class TNode;
class TNodeLabel;
class TNodeLogical;
class TNodeType;

enum T_Block { 
   tbNone = 0x00, tbBreak = 0x01, tbContinue = 0x02, tbParam = 0x04,
   tbBlock = 0x010000, tbFor = 0x020000 | tbBreak | tbContinue, tbWhile = 0x030000 | tbBreak | tbContinue, tbDo = 0x040000 | tbBreak | tbContinue, 
   tbIf = 0x050000, tbSwitch = 0x060000 | tbBreak, tbSwitchItem = 0x070000, tbFunc = 0x080000 | tbParam, 
   tbStatements = 0x090000
};

enum T_BaseType {
   btVoid   = 0x0000, btShort   = 0x0001, btInt   = 0x0002, btLong   = 0x0003, btFloat   = 0x0004, btDouble   = 0x0005,
   btCVoid  = 0x0100, btCShort  = 0x0101, btCInt  = 0x0102, btCLong  = 0x0103, btCFloat  = 0x0104, btCDouble  = 0x0105,
   btRVoid  = 0x0200, btRShort  = 0x0201, btRInt  = 0x0202, btRLong  = 0x0203, btRFloat  = 0x0204, btRDouble  = 0x0205,
   btCRVoid = 0x0300, btCRShort = 0x0301, btCRInt = 0x0302, btCRLong = 0x0303, btCRFloat = 0x0304, btCRDouble = 0x0305,
   btConst  = 0x0100, btReference = 0x0200, btStatic = 0x0400, btConstReference = btConst | btReference, btType  = 0x000F,
   btUnknown = 0x80000000, btLogical = 0x40000000
};

class TBaseType {
public:
   TBaseType();
   static TNodeType* BaseType(const T_Lexeme &l, int detail);
   static TNodeType* Or(const TNodeType* type, T_BaseType maska);
   static int Index(T_BaseType type);
   static const char* Title(T_BaseType type);
   static T_BaseType Const(T_BaseType type);
   static T_BaseType Or(T_BaseType type, T_BaseType maska);
   static T_BaseType And(T_BaseType type, T_BaseType maska);
   static T_BaseType Tilda(T_BaseType type, T_BaseType maska);
   static void Clear();
};

class TBlock {
public:
   TBlock() :type(tbNone)    , offset(0), size(0), number(0), continue_label(NULL), break_label(NULL), one_label(NULL), two_label(NULL) {}
   TBlock(T_Block t) :type(t), offset(0), size(0), number(0), continue_label(NULL), break_label(NULL), one_label(NULL), two_label(NULL) {}
public:
   virtual void BlockBegin(TSemantic& semantic);
   virtual void BlockEnd(TSemantic& semantic, bool del = false);
   bool LabelDelVar(TNodeLabel* &label, int &del, int rate) const;
   void BreakContinueLabel(TNodeLabel* label_break, TNodeLabel* label_continue);
public:
   T_Block type;
   int     offset, size, number;
   TNodeLabel *continue_label, *break_label;
   TNodeLabel *one_label, *two_label;
public:
   void print(TPrinter& printer) const;
};

class TFinder {
public:
   enum { mfNone = 0x0000, 
          mfDuplicateSearch = 0x0001, mfBreak = 0x0002, mfContinue = 0x0004,
          mfVar             = 0x0010, mfLabel = 0x0020, mfFunction = 0x0040, mfFunctionType = 0x0040,
          mfOffset          = 0x0100
        };
public:
   TFinder(TSemantic& s, int m) :mode(m), level(0), count(0), weight(0), index(0), place(NULL), result(NULL), lexeme(NULL), semantic(&s), is_stack(false) {}
   TFinder(TNode* p, int m) :mode(m), level(0), count(0), weight(0), index(0), place(p), result(NULL), lexeme(NULL), semantic(NULL), is_stack(false) {}
   TFinder(int m) :mode(m), level(0), count(0), weight(0), index(0), place(NULL), result(NULL), lexeme(NULL), semantic(NULL), is_stack(false) {}
   bool Compare(const T_Lexeme& l);
   int  Match(const TFuncProfile &profile, const TFuncProfile &join);
   bool IsStack() const { return is_stack; }
   void Reset(int m);
public:
   bool   is_stack;
   int    mode, level, count, weight, index;
   TNode* place;
   TNode* result;
   const T_Lexeme* lexeme;
   TSemantic* semantic;
};

enum T_Alloc {
   taNone, taGlobal, taLocal, taParam, taInteger, taNumber, taOper, taLabel, taCommand
};

class TQuadruple;
struct TAddress
{
public:
   TAddress(TQuadruple* q = NULL) :alloc(T_Alloc::taNone), number(0), quad(q) {}
   bool operator == (const TAddress& a) const { return (alloc == a.alloc) && (number == a.number); }
public:
   void write(TWriter& printer) const;
public:
   T_Alloc alloc; int number; TQuadruple* quad;
};

const char* title_alloc(T_Alloc a);

//#define CLEAR_NODE(N) if (N && (!N->Owner() || (N->Owner() == (TNode*)this))) { N->clear(); delete N; N = NULL; }
#define CLEAR_NODE(N) if (this->ClearNode(N)) { N = NULL; }
#define PRINT_NODE(N) if (N) { N->print(level + 1, printer); }
#define WRITE_NODE(N) if (N) { N->write(printer); }

#define CURRENT_CHILD(M,N,T) if (current_child == N) { Set##M((T*)c); current_child++; return true; }
#define CHANGE_CHILD(M,N,T)  if (current_child == N + 1) { T* old = M(); old->SetOwner(); c->SetCurrentChild(old); Set##M((T*)c); return true; }
#define GET_CURRENT_CHILD(M,N,T) if (current_child == N + 1) return M();

class TNode {
public:
   TNode() :owner(NULL), after(NULL), before(NULL), lexeme(), error_code(erNone), child_number(-1), current_child(0), passport(0) {}
   TNode(const T_Lexeme& l) :owner(NULL), after(NULL), before(NULL), lexeme(l), error_code(erNone), child_number(-1), current_child(0), passport(0) {}
   virtual ~TNode() {}
public:
   bool ClearNode(TNode* N);
   virtual bool null() const   { return false; }
   virtual bool IsNull() const { return null(); }
   virtual void clear();
   virtual void Variables(TSemantic &semantic, int mode = 0x00) {}
   virtual void Codes(TSemantic &semantic, int mode) {}
   virtual void Verify(TSemantic &semantic, int mode) {}
   virtual T_BaseType BaseType() const { return btUnknown; } 
	virtual TNodeLogical* Logical() { return NULL; }
   virtual bool Search(TFinder& finder);
   virtual bool SearchInside(TFinder& finder);
public:
   virtual bool error()   { return (error_code != erNone); }
   void SetError(T_Error code) { if ((error_code == erNone) || (code == erNone)) error_code = code; }
   T_Error error_code;
public:
   const T_Lexeme& Lexeme() const { return lexeme; }
   void SetLexeme(const T_Lexeme& l) { lexeme = l; }
   virtual const T_Lexeme& FirstLexeme() const { return lexeme; }
protected:
   T_Lexeme lexeme;
public:
   TNode *Owner()           { return owner; }
   void SetOwner(TNode *o);
   void SetOwner() { owner = NULL; }
   void SetAfter(TNode *a)  { after = a; } 
   void SetBefore(TNode *b) { before = b; } 
   void InsertAfter(TNode *b);
   void InsertBefore(TNode *b);
   void After(TSemantic &semantic, int mode);
   void Before(TSemantic &semantic, int &mode);
protected:
   TNode *owner, *after, *before;
public:
   int child_number;
public:
   virtual bool SetCurrentChild(TNode *) { return false; }
   virtual TNode* GetCurrentChild() { return NULL; }
   virtual bool ChangeCurrentChild(TNode *) { return false; }
   void ChangeChildIndex(int delta) { current_child += delta; }
   void SetChildIndex(int step) { current_child = step; }
public:
   int current_child;
public:
   virtual const char* title() const   { return "TNode"; }
   virtual void print(int level, TPrinter& printer) const;
   virtual void write(TWriter& printer) const;
   int depth() { if (!owner) return 0; return owner->depth() + 1; }
   TNode* root() { if (!owner) return this; return owner->root(); }
public:
   TAddress quad;
public:
   int  Passport(int mode);
   void Passport(A_Syntax* syntax, int mode);
   void Passport(TSemantic &semantic, int mode);
public:
   int passport;
};

class TNodeNull : public TNode {
public:
   TNodeNull() :TNode() {}
public:
   virtual void Codes(TSemantic &semantic, int mode);
   virtual bool null()  const  { return true; }
public:
   virtual const char* title() const  { return "TNodeNull"; }
};

class TNodeError : public TNode {
public:
   TNodeError() :TNode() {}
   TNodeError(const T_Lexeme& l) :TNode(l) {}
   ~TNodeError() {}
public:
   virtual bool error()   { return true; }
public:
   virtual const char* title() const  { return "TNodeError"; }
};

template <class C_ONE> class T_NodeOne : public TNode {
public:
   T_NodeOne() :TNode(), child(NULL) {}
   T_NodeOne(const T_Lexeme& l, C_ONE *c) :TNode(l) { SetChild(c); }
   ~T_NodeOne() {}
public:
   C_ONE *Child()           { return child; }
   void SetChild(C_ONE *c)  { child = c; if (child) child->SetOwner(this); } 
   void SetChildWithoutOwner(C_ONE *c) { child = c; }
protected:
   C_ONE *child;
public:
   virtual bool SetCurrentChild(TNode *c) { CURRENT_CHILD(Child, 0, C_ONE) return false; }
   virtual TNode * GetCurrentChild() { GET_CURRENT_CHILD(Child, 0, C_ONE) return NULL; }
   virtual bool ChangeCurrentChild(TNode *c) { CHANGE_CHILD(Child, 0, C_ONE) return false; }
public:
   virtual void clear()     { CLEAR_NODE(child) TNode::clear(); }
   virtual void print(int level, TPrinter& printer) const { TNode::print(level, printer); PRINT_NODE(child) }
   virtual void write(TWriter& printer) const { TNode::write(printer); WRITE_NODE(child) }
};

template <class C_ONE, class C_TWO> class T_NodeTwo : public TNode {
public:
   T_NodeTwo() :TNode(), left(NULL), right(NULL) {}
   T_NodeTwo(const T_Lexeme& h, C_ONE *l, C_TWO *r) :TNode(h) { SetBoth(l,r); }
   ~T_NodeTwo() {}
public:
   C_ONE *Left()                    { return left; }
   void SetLeft(C_ONE *l)           { left = l; if (left) left->SetOwner(this); } 
   C_TWO *Right()                   { return right; }
   void SetRight(C_TWO *r)          { right = r; if (right) right->SetOwner(this); } 
   void SetBoth(C_ONE *l, C_TWO *r) { SetLeft(l); SetRight(r); } 
protected:
   C_ONE *left; C_TWO *right;
public:
   virtual bool SetCurrentChild(TNode *c) { CURRENT_CHILD(Left, 0, C_ONE) CURRENT_CHILD(Right, 1, C_TWO) return false; }
   virtual TNode * GetCurrentChild() { GET_CURRENT_CHILD(Left, 0, C_ONE) GET_CURRENT_CHILD(Right, 1, C_TWO) return NULL; }
   virtual bool ChangeCurrentChild(TNode *c) { CHANGE_CHILD(Left, 0, C_ONE) CHANGE_CHILD(Right, 1, C_TWO) return false; }
public:
   virtual void clear()                { CLEAR_NODE(left) CLEAR_NODE(right) TNode::clear(); }
   virtual void print(int level, TPrinter& printer) const { TNode::print(level, printer); PRINT_NODE(left) PRINT_NODE(right) }
   virtual void write(TWriter& printer) const { TNode::write(printer); WRITE_NODE(left) WRITE_NODE(right) }
};

template <class C_ONE, class C_TWO, class C_THREE> class T_NodeThree : public T_NodeTwo<C_ONE, C_TWO> {
public:
   T_NodeThree() :T_NodeTwo<C_ONE, C_TWO>(), mid(NULL) {}
   T_NodeThree(const T_Lexeme& h, C_ONE *l, C_THREE *m, C_TWO *r) :T_NodeTwo<C_ONE, C_TWO>(h,l,r), mid(m) { if (mid) mid->SetOwner(this); }
   ~T_NodeThree() {}
public:
   C_THREE *Mid()                     { return mid; }
   void SetMid(C_THREE *m)            { mid = m; if (mid) mid->SetOwner(this); } 
   void SetThree(C_ONE *l, C_THREE *m, C_TWO *r) { SetBoth(l,r); SetMid(m); } 
protected:
   C_THREE *mid;
public:
   virtual bool SetCurrentChild(TNode *c) { CURRENT_CHILD(Left, 0, C_ONE) CURRENT_CHILD(Right, 1, C_TWO) CURRENT_CHILD(Mid, 2, C_THREE) return false; }
   virtual TNode * GetCurrentChild() { GET_CURRENT_CHILD(Left, 0, C_ONE) GET_CURRENT_CHILD(Right, 1, C_TWO) GET_CURRENT_CHILD(Mid, 2, C_THREE) return NULL; }
   virtual bool ChangeCurrentChild(TNode *c) { CHANGE_CHILD(Left, 0, C_ONE) CHANGE_CHILD(Right, 1, C_TWO) CHANGE_CHILD(Mid, 2, C_THREE) return false; }
public:
   virtual void clear()               { CLEAR_NODE(mid) T_NodeTwo<C_ONE, C_TWO>::clear(); }
   virtual void print(int level, TPrinter& printer) const { TNode::print(level, printer); PRINT_NODE(this->left) PRINT_NODE(this->mid) PRINT_NODE(this->right) }
   virtual void write(TWriter& printer) const { TNode::write(printer); WRITE_NODE(this->left) WRITE_NODE(this->mid) WRITE_NODE(this->right) }
};

template <class C_ONE, class C_TWO, class C_THREE, class C_FOUR> class T_NodeFour : public T_NodeThree<C_ONE, C_TWO, C_THREE> {
public:
   T_NodeFour() :T_NodeThree<C_ONE, C_TWO, C_THREE>(), four(NULL) {}
   T_NodeFour(const T_Lexeme& h, C_ONE *l, C_THREE *m, C_TWO *r, C_FOUR *f) :T_NodeThree<C_ONE, C_TWO, C_THREE>(h,l,m,r), four(f) { if (four) four->SetOwner(this); }
   ~T_NodeFour() {}
public:
   C_FOUR *Four()                     { return four; }
   void SetFour(C_FOUR *f)            { four = f; if (four) four->SetOwner(this); } 
   void SetAll(C_ONE *l, C_THREE *m, C_TWO *r, C_FOUR *f) { SetThree(l,m,r); SetFour(f); } 
protected:
   C_FOUR *four;
public:
   virtual bool SetCurrentChild(TNode *c) { CURRENT_CHILD(Left, 0, C_ONE) CURRENT_CHILD(Right, 1, C_TWO) CURRENT_CHILD(Mid, 2, C_THREE) CURRENT_CHILD(Four, 3, C_FOUR) return false; }
   virtual TNode * GetCurrentChild() { GET_CURRENT_CHILD(Left, 0, C_ONE) GET_CURRENT_CHILD(Right, 1, C_TWO) GET_CURRENT_CHILD(Mid, 2, C_THREE) GET_CURRENT_CHILD(Four, 3, C_FOUR) return NULL; }
   virtual bool ChangeCurrentChild(TNode *c) { CHANGE_CHILD(Left, 0, C_ONE) CHANGE_CHILD(Right, 1, C_TWO) CHANGE_CHILD(Mid, 2, C_THREE) CHANGE_CHILD(Four, 3, C_FOUR) return false; }
public:
   virtual void clear()               { CLEAR_NODE(four) T_NodeThree<C_ONE, C_TWO, C_THREE>::clear(); }
   virtual void print(int level, TPrinter& printer) const { TNode::print(level, printer); PRINT_NODE(this->left) PRINT_NODE(this->mid) PRINT_NODE(this->right) PRINT_NODE(four) }
   virtual void write(TWriter& printer) const { TNode::write(printer); WRITE_NODE(this->left) WRITE_NODE(this->mid) WRITE_NODE(this->right) WRITE_NODE(this->four) }
};

class T_NodeList : public TNode, public std::vector<TNode*> {
public:
   T_NodeList() :TNode() {}
   T_NodeList(const T_Lexeme& h) :TNode(h) {}
   ~T_NodeList() {}
public:
   TNode *Last()                    { if (empty()) return NULL; return back(); }
   void Add(TNode *r);
   void Insert(int i, TNode *r);
   int  Count() const               { return (int)size(); }
   virtual bool IsNull() const;
   virtual const T_Lexeme& FirstLexeme() const;
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual void Verify(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { if (!empty()) return back()->BaseType(); return btUnknown; } 
   virtual bool Search(TFinder& finder);
   virtual bool SearchInside(TFinder& finder);
public:
   virtual bool SetCurrentChild(TNode *c) { Add(c); current_child++; return true; }
   virtual TNode * GetCurrentChild() { if (!empty()) return back(); return NULL; }
   virtual bool ChangeCurrentChild(TNode *c) { TNode* old = back(); old->SetOwner(); c->SetCurrentChild(old); c->SetOwner(this); back() = c; return true; }
public:
   virtual void clear();
   virtual const char* title() const   { return "T_NodeList"; }
   virtual void print(int level, TPrinter& printer) const;
   virtual void write(TWriter& printer) const;
};

class TNodeUnary : public T_NodeOne<TNode> {
public:
   TNodeUnary() :T_NodeOne(), base_type(btUnknown), profile(NULL) {}
   TNodeUnary(const T_Lexeme& l, TNode *c) :T_NodeOne(l,c), base_type(btUnknown), profile(NULL) {}
public:
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { return base_type; }
   virtual TNodeLogical* Logical(); 
   T_Symbol::T_Type Oper() const;
public:
   T_BaseType base_type; 
	const TOperProfile* profile;
public:
   virtual const char* title() const   { return "TNodeUnary"; }
};

class TNodeBinary : public T_NodeTwo<TNode,TNode> {
public:
   TNodeBinary() :T_NodeTwo(), base_type(btUnknown), profile(NULL), mode_oper(0) {}
   TNodeBinary(const T_Lexeme& h, TNode *l, TNode *r) :T_NodeTwo(h,l,r), base_type(btUnknown), profile(NULL), mode_oper(0) {}
public:
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { return base_type; } 
   T_Symbol::T_Type Oper() const;
public:
   T_BaseType base_type;
	const TOperProfile* profile;
public:
   int mode_oper; // 0x01 - initialization
   virtual const char* title() const   { return "TNodeBinary"; }
};

class TNodeLogical : public T_NodeTwo<TNode,TNode> {
public:
   TNodeLogical() :T_NodeTwo(), base_type(btCInt), true_label(NULL), false_label(NULL), logical(0) {}
   TNodeLogical(const T_Lexeme& h, TNode *l, TNode *r) :T_NodeTwo(h,l,r), base_type(btCInt), true_label(NULL), false_label(NULL), logical(0) {}
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { return base_type; } 
	virtual TNodeLogical* Logical() { return this; }
public:
   T_BaseType base_type;
   TNodeLabel *true_label, *false_label;
   int logical;
public:
   virtual const char* title() const   { return "TNodeLogical"; }
};

class TNodeTrio : public T_NodeThree<TNode,TNode,TNode> {
public:
   TNodeTrio() :T_NodeThree(), base_type(btUnknown) {}
   TNodeTrio(const T_Lexeme& h, TNode *l, TNode *m, TNode *r) :T_NodeThree(h,l,m,r), base_type(btUnknown) {}
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { return base_type; } 
public:
   virtual bool SetCurrentChild(TNode *c) { CURRENT_CHILD(Left, 0, TNode) CURRENT_CHILD(Mid, 1, TNode) CURRENT_CHILD(Right, 2, TNode) return false; }
   virtual bool ChangeCurrentChild(TNode *c) { CHANGE_CHILD(Left, 0, TNode) CHANGE_CHILD(Mid, 1, TNode) CHANGE_CHILD(Right, 2, TNode) return false; }
public:
   T_BaseType base_type;
public:
   virtual const char* title() const   { return "TNodeTrio"; }
};

class TNodeNumber : public TNode {
public:
   TNodeNumber() :TNode() {}
   TNodeNumber(const T_Lexeme& h) :TNode(h) {}
public:
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { if (lexeme.group == lexeme.grInteger) return btCInt; if (lexeme.group == lexeme.grNumber) return btCDouble; return btUnknown; } 
public:
   virtual const char* title() const   { return "TNodeNumber"; }
};

class TNodePrimary : public T_NodeOne<TNode> {
public:
   TNodePrimary() :T_NodeOne() {}
   TNodePrimary(const T_Lexeme& l, TNode *c) :T_NodeOne(l,c) {}
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { return child ? child->BaseType() : btUnknown; } 
	virtual TNodeLogical* Logical() { return child ? child->Logical() : NULL; }
public:
   virtual const char* title() const   { return "TNodePrimary"; }
};

class TNodeType : public TNode {
public:
   TNodeType() :TNode(), base_type(btUnknown) {}
   TNodeType(const T_Lexeme& h) :TNode(h), base_type(btUnknown) {}
   TNodeType(const TNodeType& t) :TNode(t.lexeme), base_type(t.base_type) {}
public:
   bool Void() const { return (base_type == btVoid); }
   bool Const() const { return (base_type & btConst) != 0; }
   bool Static() const { return (base_type & btStatic) != 0; }
   bool Reference() const { return (base_type & btReference) != 0; }
   virtual T_BaseType BaseType() const { return base_type; } 
public:
   T_BaseType base_type; 
public:
   virtual const char* title() const   { return "TNodeType"; }
};

class TNodeCast : public T_NodeTwo<TNodeType,TNode> {
public:
   TNodeCast() :T_NodeTwo(), cast(T_CastType(0)), base_type(btUnknown) {}
   TNodeCast(const T_Lexeme& h, TNodeType *l, TNode *r) :T_NodeTwo(h,l,r), cast(T_CastType(0)), base_type(btUnknown) { if (l) current_child++; }
   void SetType(TNodeType *t) { SetLeft(t); }
public:
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { if (left) return left->BaseType(); return base_type; }
   virtual TNodeLogical* Logical() { return right ? right->Logical() : NULL; }
public:
   T_CastType cast;
   T_BaseType base_type;
public:
   virtual const char* title() const   { return "TNodeCast"; }
};

class TNodeExpressions : public T_NodeList {
public:
   TNodeExpressions() :T_NodeList(), part(psNone) {}
   TNodeExpressions(const T_Lexeme& l) :T_NodeList(l), part(psNone) {}
   virtual void Codes(TSemantic &semantic, int mode);
   virtual TNodeLogical* Logical(); 
   virtual bool Search(TFinder& finder);
public:
   T_Part part;
public:
   virtual const char* title() const   { return "TNodeExpressions"; }
   virtual void print(int level, TPrinter& printer) const { PRINTER_FILE_MODE T_NodeList::print(level, printer); fprintf(file," part=%d ",part); }
};

class TNodeStatements : public T_NodeList, public TBlock {
public:
   TNodeStatements();
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
public:
   virtual const char* title() const   { return "TNodeStatements"; }
   virtual void print(int level, TPrinter& printer) const { T_NodeList::print(level, printer); TBlock::print(printer); }
   virtual T_BaseType BaseType() const { return btVoid; }
   virtual bool Search(TFinder& finder);
public:
   int step;
};

class TNodeDefVar : public T_NodeThree<TNodeType, TNode, T_NodeList> { 
public:
   TNodeDefVar() :T_NodeThree(), alloc(T_Alloc::taNone), offset(0), dimension(0), uninitialized(false), referenced(false) {}
   TNodeDefVar(const T_Lexeme& l) :T_NodeThree(l,NULL,NULL,NULL), alloc(T_Alloc::taNone), offset(0), dimension(0), uninitialized(false), referenced(false) {}
   TNodeDefVar(TNodeType *t, const T_Lexeme& l) :T_NodeThree(l, NULL, NULL, NULL), alloc(T_Alloc::taNone), offset(0), dimension(0), uninitialized(false), referenced(false) { if (t) { SetType(t); current_child++; } }
public:
   TNodeType *Type()            { return left; }
   void SetType(TNodeType *t)   { SetLeft(t); }
   void SetAssign(TNode *a)     { SetRight(a); }
   void SetAssign(const T_Lexeme& lexeme, TNode* expr, TSemantic* semantic = NULL);
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual void Verify(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const;
   virtual bool SearchInside(TFinder& finder);
public:
   virtual const T_Lexeme& FirstLexeme() const;
public:
   T_Alloc alloc;
   int     offset, dimension;
	bool    uninitialized, referenced;
public:
   virtual const char* title() const   { return "TNodeDefVar"; }
   virtual void print(int level, TPrinter& printer) const;
};

struct TDefArrRangeItem {
public:
   TDefArrRangeItem()  : range(0), volume(0), index(0), made(0) {}
   TDefArrRangeItem(int r)  : range(r), volume(0), index(0), made(0) {}
public:
   int range, volume, index, made;
};
struct TDefArrRange : public std::vector<TDefArrRangeItem> {
public:
   TDefArrRange() :level(0) {}
   int  calc();
   int  count() const { return (int)size(); }
   int  offset() const;
   bool variable_range() const;
   bool unknown_range() const { return (front().range == -1); }
   bool next();
   void jump(int level);
public:
   int  level;
};

class TNodeDefArr : public TNodeDefVar {
public:
   TNodeDefArr() :TNodeDefVar() {}
   TNodeDefArr(const T_Lexeme& l, T_NodeList *r) :TNodeDefVar(l) { SetRange(r); }
   TNodeDefArr(TNodeType *t, const T_Lexeme& l, T_NodeList *r) :TNodeDefVar(t,l) { SetRange(r); }
   virtual ~TNodeDefArr() {}
public:
   T_NodeList* Range() { return (T_NodeList*)mid; }
   void SetRange(T_NodeList *r) { SetMid(r); }
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   bool parse_init(T_NodeList *items, int level);
public:
   TDefArrRange ranges;
protected:
   struct TDefArrInitItem {
   public:
      TDefArrInitItem() :offset(0), value(NULL) {}
      TDefArrInitItem(int o, TNode* v) :offset(o), value(v) {}
//      ~TDefArrInitItem() { if (value) value->clear(); }
   public:
      int offset; TNode* value;
   };
   std::vector<TDefArrInitItem> initializer;
public:
   virtual const char* title() const   { return "TNodeDefArr"; }
};

class TNodeDefine : public T_NodeList {
public:
   TNodeDefine() :T_NodeList(), left(NULL) {}
   TNodeDefine(const T_Lexeme& l) :T_NodeList(l), left(NULL) {}
   TNodeDefine(TNodeType *t, const T_Lexeme& l) :T_NodeList(l) { SetType(t); }
public:
   TNodeType *Type() { return left; }
   void SetType(TNodeType *l) { left = l; if (left) left->SetOwner(this); }
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { if (left) return left->BaseType(); return btUnknown; }
   virtual bool Search(TFinder& finder);
   virtual bool SearchInside(TFinder& finder);
protected:
   TNodeType *left;
public:
   virtual void print(int level, TPrinter& printer) const { T_NodeList::print(level, printer); }
   virtual const char* title() const { return "TNodeDefine"; }
};

class TNodeDefFunc : public T_NodeThree<TNodeType, TNodeDefine, TNode>, public TBlock {
public:
   TNodeDefFunc() :T_NodeThree(), TBlock(tbFunc), profile(NULL), number(0) {}
   TNodeDefFunc(const T_Lexeme& l) :T_NodeThree(l,NULL,NULL,NULL), TBlock(tbFunc), profile(NULL), number(0) {}
   TNodeDefFunc(TNodeType *t, const T_Lexeme& l, TNodeDefine *p, TNode *b) :T_NodeThree(l, t, b, p), TBlock(tbFunc), profile(NULL), number(0) { if (t) current_child++; }
//   virtual ~TNodeDefFunc() {}
public:
   void SetType(TNodeType *t)    { SetLeft(t); }
   void SetParams(TNodeDefine*r) { SetRight(r); }
   TNode* Body()                 { return mid; }
   void SetBody(TNode *a)        { SetMid(a); }
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual void Verify(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { if (left) return left->BaseType(); return btUnknown; } 
   virtual bool Search(TFinder& finder);
   virtual bool SearchInside(TFinder& finder);
public:
   TFuncProfile *profile;
	int  number;
public:
   virtual void clear();
   virtual const char* title() const   { return "TNodeDefFunc"; }
   virtual void print(int level, TPrinter& printer) const { T_NodeThree::print(level, printer); TBlock::print(printer); }
   virtual void write(TWriter& printer) const { T_NodeThree::write(printer); }
};

class TNodeVar : public T_NodeOne<TNodeDefVar> { // client def
public:
   TNodeVar() :T_NodeOne() {}
   TNodeVar(const T_Lexeme& h) :T_NodeOne() { SetLexeme(h); }
public:
   void SetType(TNodeDefVar *t) { SetChildWithoutOwner(t); }
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { if (child) return child->BaseType(); return btUnknown; } 
public:
	virtual void print(int level, TPrinter& printer) const;
   virtual const char* title() const   { return "TNodeVar"; }
   virtual void write(TWriter& printer) const;
};

class TNodeCall : public T_NodeTwo<TNodeDefFunc, T_NodeList> { // client def
public:
   TNodeCall() :T_NodeTwo(), profile(NULL) {}
   TNodeCall(const T_Lexeme& h) :T_NodeTwo(), profile(NULL) { SetLexeme(h); }
   TNodeCall(const T_Lexeme& h, T_NodeList *r) :T_NodeTwo(h, NULL, r), profile(NULL) { if (r) current_child++; }
public:
   void SetType(TNodeDefFunc *t) { SetLeft(t); }
	TNodeDefFunc* Type()          { return left; }
   T_NodeList* Params()          { return right; }
   void SetList(T_NodeList *l)   { SetRight(l); } // params
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { if (left) return left->BaseType(); return btUnknown; } 
public:
   virtual bool SetCurrentChild(TNode *c) { CURRENT_CHILD(Left, 1, TNodeDefFunc) CURRENT_CHILD(Right, 0, T_NodeList) return false; }
   virtual bool ChangeCurrentChild(TNode *c) { CHANGE_CHILD(Left, 1, TNodeDefFunc) CHANGE_CHILD(Right, 0, T_NodeList) return false; }
public:
   TFuncProfile *profile;
public:
   virtual void clear();
   virtual void print(int level, TPrinter& printer) const;
   virtual const char* title() const   { return "TNodeCall"; }
   virtual void write(TWriter& printer) const;
};

class TNodeIndex : public T_NodeTwo<TNodeDefArr, T_NodeList> { // client def
public:
   TNodeIndex() :T_NodeTwo() {}
   TNodeIndex(const T_Lexeme& h) :T_NodeTwo() { SetLexeme(h); }
   TNodeIndex(const T_Lexeme& h, T_NodeList *r) :T_NodeTwo(h,NULL,r) {}
public:
   void SetType(TNodeDefArr *t) { SetLeft(t); }
   T_NodeList* Ranges()         { return right;}
   void SetList(T_NodeList *l)  { SetRight(l); }
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { if (left) return left->BaseType(); return btUnknown; } 
public:
	virtual void print(int level, TPrinter& printer) const;
   virtual const char* title() const   { return "TNodeIndex"; }
   virtual void write(TWriter& printer) const;
public:
};

class TNodeFor : public T_NodeFour<TNode,TNode,TNode,TNode>, public TBlock {
public:
   TNodeFor() :T_NodeFour(), TBlock(tbFor) {}
   TNodeFor(const T_Lexeme& l) :T_NodeFour(l,NULL,NULL,NULL,NULL), TBlock(tbFor) {}
public:
   void SetBeg(TNode *t)       { SetLeft(t); }
   void SetCondition(TNode *i) { SetMid(i); }
   void SetEnd(TNode *r)       { SetRight(r); }
   void SetBody(TNode *a)      { SetFour(a); }
   TNode* Body()               { return four;  }
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual void Verify(TSemantic &semantic, int mode);
   virtual bool Search(TFinder& finder);
   virtual bool SearchInside(TFinder& finder);
public:
   virtual bool SetCurrentChild(TNode *c) { CURRENT_CHILD(Left, 0, TNode) CURRENT_CHILD(Right, 2, TNode) CURRENT_CHILD(Mid, 1, TNode) CURRENT_CHILD(Four, 3, TNode) return false; }
   virtual bool ChangeCurrentChild(TNode *c) { CHANGE_CHILD(Left, 0, TNode) CHANGE_CHILD(Right, 2, TNode) CHANGE_CHILD(Mid, 1, TNode) CHANGE_CHILD(Four, 3, TNode) return false; }
public:
   virtual const char* title() const   { return "TNodeFor"; }
   virtual void print(int level, TPrinter& printer) const { T_NodeFour::print(level, printer); TBlock::print(printer); }
   virtual void write(TWriter& printer) const { T_NodeFour::write(printer); }
};

class TNodeWhile : public T_NodeTwo<TNode,TNode>, public TBlock {
public:
   TNodeWhile() :T_NodeTwo(), TBlock(tbWhile) {}
   TNodeWhile(const T_Lexeme& l) :T_NodeTwo(l,NULL,NULL), TBlock(tbWhile) {}
public:
   void SetCondition(TNode *c) { SetLeft(c); }
   void SetBody(TNode *b)      { SetRight(b); }
   TNode* Body()               { return right; }
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual void Verify(TSemantic &semantic, int mode);
   virtual bool SearchInside(TFinder& finder);
public:
   virtual void print(int level, TPrinter& printer) const { T_NodeTwo::print(level, printer); TBlock::print(printer); }
   virtual const char* title() const   { return "TNodeWhile"; }
};

class TNodeDo : public T_NodeTwo<TNode,TNode>, public TBlock {
public:
   TNodeDo() :T_NodeTwo(), TBlock(tbDo) {}
   TNodeDo(const T_Lexeme& l) :T_NodeTwo(l,NULL,NULL), TBlock(tbDo) {}
public:
   void SetCondition(TNode *c) { SetLeft(c); }
   void SetBody(TNode *b)      { SetRight(b); }
   TNode* Body()               { return right; }
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual void Verify(TSemantic &semantic, int mode);
   virtual bool SearchInside(TFinder& finder);
public:
   virtual void print(int level, TPrinter& printer) const { T_NodeTwo::print(level, printer); TBlock::print(printer); }
   virtual const char* title() const   { return "TNodeDo"; }
};

enum T_GoTo { 
   tgNone, tgIf, tgElse, tgGoTo
};

class TNodeLabel : public T_NodeOne<TNode> {
public:
   TNodeLabel(TSemantic* semantic);
   virtual ~TNodeLabel() {}
public:
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { return btVoid; } 
   TNodeLabel* Label() { return reference ? Reference() : this; }
   TNodeLabel* Reference() const;
   void SetReference(TNodeLabel* r);
public:
   TNodeLabel* reference;
   int go_to, command;
public:
   virtual void print(int level, TPrinter& printer) const;
   virtual const char* title() const   { return "TNodeLabel"; }
protected:
   TNodeLabel(const T_Lexeme& l);
};

struct T_UserGoToItem
{
   T_UserGoToItem() :block(0), offset(0) {}
   T_UserGoToItem(int b, int o) :block(b), offset(o) {}
   int block, offset;
};

class TBlockTable;
class T_UserGoToLabel : public std::vector<T_UserGoToItem> {
public:
   T_UserGoToLabel() {}
   virtual ~T_UserGoToLabel() {}
public:
   bool Compare(const T_UserGoToLabel &join) const;
public:
   void print(TPrinter& printer) const;
};

class TNodeUserLabel : public TNodeLabel, public T_UserGoToLabel {
public:
   TNodeUserLabel(TSemantic* semantic) :TNodeLabel(semantic) {}
   TNodeUserLabel(const T_Lexeme& l) :TNodeLabel(l) {}
   virtual ~TNodeUserLabel() {}
public:
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Verify(TSemantic &semantic, int mode);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual bool SearchInside(TFinder& finder);
public:
   virtual void print(int level, TPrinter& printer) const;
   virtual const char* title() const   { return "TNodeUserLabel"; }
};

class TNodeGoTo : public T_NodeOne<TNodeLabel> { // client label
public:
   TNodeGoTo() :T_NodeOne(), type(tgNone), del_count(0) {}
   TNodeGoTo(T_GoTo t, TNodeLabel *l = NULL) :T_NodeOne(), type(t), del_count(0) { SetLabel(l); }
   virtual ~TNodeGoTo() {}
public:
   void SetType(T_GoTo t) { type = t; }
   void SetLabel(TNodeLabel* l);
   TNodeLabel* GetLabel();
   virtual void Codes(TSemantic &semantic, int mode);
public:
   T_GoTo type; 
   int del_count;
protected:
   TNodeGoTo(const T_Lexeme& l) :T_NodeOne(l,NULL), type(tgGoTo) {}
public:
   virtual void clear() { child = NULL; /*T_NodeTwo::clear(); */ }
   virtual const char* title() const   { return "TNodeGoTo"; }
};

class TNodeUserGoTo : public TNodeGoTo, public T_UserGoToLabel {
public:
   TNodeUserGoTo() :TNodeGoTo() { SetType(tgGoTo); }
   TNodeUserGoTo(const T_Lexeme& l) :TNodeGoTo(l) {}
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Verify(TSemantic &semantic, int mode);
   virtual void Codes(TSemantic &semantic, int mode);
public:
   virtual void print(int level, TPrinter& printer) const;
   virtual const char* title() const   { return "TNodeUserGoTo"; }
};

class TNodeBreakContinue : public TNodeGoTo {
public:
   TNodeBreakContinue(T_Block r) :TNodeGoTo(), rate(r) { SetType(tgGoTo); }
   TNodeBreakContinue(T_Block r, const T_Lexeme& l) :TNodeGoTo(l), rate(r) { SetType(tgGoTo); }
public:
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
public:
   T_Block rate;
public:
   virtual const char* title() const   { return (rate == T_Block::tbBreak) ? "TNodeBreak" : "TNodeContinue"; }
};

class TNodeReturn : public T_NodeOne<TNode> {
public:
   TNodeReturn() :T_NodeOne(), base_type(btUnknown) {}
   TNodeReturn(const T_Lexeme& l) :T_NodeOne(l,NULL), base_type(btUnknown) {}
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
public:
   void SetValue(TNode *c) { SetChild(c); }
   T_BaseType base_type;
public:
   virtual const char* title() const   { return "TNodeReturn"; }
};

class TNodeIf : public T_NodeThree<TNode,TNode,TNode>, public TBlock {
public:
   TNodeIf() :T_NodeThree(), TBlock(tbIf), trunc(0), then_exec(0) {}
   TNodeIf(const T_Lexeme& h) :T_NodeThree(h,NULL,NULL,NULL), TBlock(tbIf), trunc(0), then_exec(0) {}
public:
   void SetCondition(TNode *c) { SetLeft(c); }
   void SetThen(TNode *b)      { SetMid(b); }
   void SetElse(TNode *b)      { SetRight(b); }
   TNode* Then()               { return mid; }
   TNode* Else()               { return right; }
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
   virtual void Verify(TSemantic &semantic, int mode);
   virtual bool SearchInside(TFinder& finder);
public:
   virtual bool SetCurrentChild(TNode *c) { CURRENT_CHILD(Left, 0, TNode) CURRENT_CHILD(Mid, 1, TNode) CURRENT_CHILD(Right, 2, TNode) return false; }
   virtual bool ChangeCurrentChild(TNode *c) { CHANGE_CHILD(Left, 0, TNode) CHANGE_CHILD(Mid, 1, TNode) CHANGE_CHILD(Right, 2, TNode) return false; }
public:
   virtual void print(int level, TPrinter& printer) const { T_NodeThree::print(level, printer); TBlock::print(printer); }
   virtual const char* title() const   { return "TNodeIf"; }
public:
   int trunc;
   int then_exec;
};

class TNodeSwitchCase : public T_NodeOne<TNode> {
public:
   TNodeSwitchCase() :T_NodeOne(), value(true) {}
   TNodeSwitchCase(const T_Lexeme& l) :T_NodeOne(l,NULL), value(true) {}
public:
   void SetValue(TNode *c) { SetChild(c); }
public:
   bool value;
public:
   virtual const char* title() const   { return "TNodeSwitchCase"; }
};

class TNodeSwitchItem : public T_NodeTwo<TNode,TNode>, public TBlock {
public:
   TNodeSwitchItem() :T_NodeTwo(), TBlock(tbSwitchItem) {}
   TNodeSwitchItem(const T_Lexeme& l) :T_NodeTwo(l,NULL,NULL), TBlock(tbSwitchItem) {}
public:
   void SetKey(T_NodeList *c)  { SetLeft(c); }
   void SetBody(T_NodeList *b) { SetRight(b); }
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
public:
   virtual void print(int level, TPrinter& printer) const { T_NodeTwo::print(level, printer); TBlock::print(printer); }
   virtual const char* title() const   { return "TNodeSwitchItem"; }
};

class TNodeSwitch : public T_NodeTwo<TNode,TNode>, public TBlock {
public:
   TNodeSwitch() :T_NodeTwo(), TBlock(tbSwitch) {}
   TNodeSwitch(const T_Lexeme& l) :T_NodeTwo(l,NULL,NULL), TBlock(tbSwitch) {}
public:
   void SetKey(TNode *c)       { SetLeft(c); }
   void SetBody(T_NodeList *b) { SetRight(b); }
   virtual void Variables(TSemantic &semantic, int mode = 0x00);
   virtual void Codes(TSemantic &semantic, int mode);
public:
   virtual void print(int level, TPrinter& printer) const { T_NodeTwo::print(level, printer); TBlock::print(printer); }
   virtual const char* title() const   { return "TNodeSwitch"; }
};

class TSerializer {
public:
   TSerializer() {}
};

void GarbageCollectorAdd(TNode* node, int mode_del);
void GarbageCollectorClear();

enum T_Step {
   ts = 0x0000, tsAll = 0xFFFF,
   ts1 = 0x0001, ts2 = 0x0002, ts3 = 0x0004, ts4 = 0x0008, ts5 = 0x0010, ts6 = 0x0020, ts7 = 0x0040, ts8 = 0x0080,
   tsFuncIdent = 0x0002,
   tsForTitle = 0x0002, 
   tsIfThen = 0x0004, tsIfElse = 0x0008, tsIfLabel = 0x0010,
   tsBegin = 0x0001, tsCondition = 0x0002, tsParam = 0x0004, tsBody = 0x0008, tsAppend = 0x0010, tsEmpty = 0x0020, tsCreate = 0x0040, tsEnd = 0x0080,
   tsUnaryIncDec= 0x0004,
   tsDefArrAssign = 0x0002, tsDefArrRanges = 0x0004,
   tsDefVarAssign = 0x0002,
   tsChildren = 0x00010000
};

#endif

