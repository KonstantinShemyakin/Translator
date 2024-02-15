#ifndef TRN_TREE_SEMANTIC_H
#define TRN_TREE_SEMANTIC_H

#include <stack>
#include "Parse.h"
#include "ASyntax.h"
#include "TNodes.h"
#include "ASemantic.h"

#include "define_enum.h"
#include <set>

// --------------------------- Tables ---------------------------
class TSemantic;

class TQuadTable;
class TCodeTable;
struct TFuncTableItem {
public:
   TFuncTableItem() :func(NULL), quad(NULL), code(NULL) {}
   TFuncTableItem(TNodeDefFunc* f, TQuadTable* q = NULL) :func(f), quad(q), code(NULL) {}
public:
   TNodeDefFunc* func;
   TQuadTable*   quad;
   TCodeTable*   code;
};

class TFuncTable : public TNode, public std::vector<TFuncTableItem> {
public:
   TFuncTable(TSemantic *s) : semantic(s) {}
   ~TFuncTable();
public:
   void Add(TNodeDefFunc* func);
   TNodeDefFunc *Find(const TFuncProfile &profile, TFinder& finder) const;
   TNodeDefFunc *find(const TFuncProfile &profile, TFinder& finder) const;
   void Codes();
   void Clear();
public:
   void print(TPrinter& printer);
protected:
   TSemantic *semantic;
};

class TLabelTable : public std::vector<TNodeLabel*> {
public:
   TLabelTable(TSemantic *s) : semantic(s) {}
public:
   void Push(TNodeLabel* label) { push_back(label); }
   void Pop()                   { pop_back(); }
   TNodeLabel* Top() const      { return back(); }
public:
   void print(TPrinter& printer);
protected:
   TSemantic *semantic;
};

class TUserLabelTable : public std::vector<TNodeUserLabel*> {
public:
   TUserLabelTable(TSemantic *s) : semantic(s) {}
public:
   void Add(TNodeUserLabel* label);
   TNodeUserLabel* Find(const T_Lexeme& ident);
   bool Find(TNodeUserGoTo* go_to);
   void Verify();
public:
   void print(TPrinter& printer);
protected:
   TSemantic *semantic;
};

class TUserGoToTable : public std::vector<TNodeUserGoTo*> {
public:
   TUserGoToTable(TSemantic *s) : semantic(s) {}
public:
   void Add(TNodeUserGoTo* go_to);
   void Verify();
public:
   void print(TPrinter& printer);
protected:
   TSemantic *semantic;
};

class TNodeDel : public TNode {
public:
   TNodeDel() :TNode(), count(0) {}
   TNodeDel(int c) :TNode(), count(c) {}
   virtual void Codes(TSemantic &semantic, int mode);
public:
   int count;
public:
   virtual const char* title() const   { return "TNodeDel"; }
   virtual void print(int level, TPrinter& printer) const;
};

class TCodeTable : public std::vector<TNode*> {
public:
   TCodeTable(TSemantic *s) : semantic(s) {}
   ~TCodeTable();
public:
   void Add(TNode* code, int counter = -1);
   void Gotos();
   void Labels(bool del = false);
   void Erase(bool del = false);
   void Clear();
public:
   void write(TWriter& printer) const;
   void print(TPrinter& printer) const;
protected:
   TSemantic *semantic;
};

class TGarbageTable : public std::set<TNode*> {
public:
   TGarbageTable(TSemantic *s = NULL) : semantic(s) {}
   ~TGarbageTable();
public:
   void Add(TNode* node, int mode_del);
   void Clear();
public:
   void print(TPrinter& printer);
protected:
   TSemantic *semantic;
};

enum T_ExecMode { meNone = 0x00, meImpossible = 0x01, meRestituer = 0x02
};

class T_ExecStack : public std::vector<int> {
public:
   void Push()     { push_back(meNone); }
   void GoTo()     { back() |= meImpossible; }
   void Label()    { back() &= ~meImpossible; }
   void Return()   { back() |= meImpossible | meRestituer; }
   void Down()     { int up = back(); pop_back(); if (!empty()) back() |= up; /* back() &= ~meImpossible | (up & meImpossible);*/ }
   int  Pop()      { int ret = back(); pop_back(); return ret; }
   void Up(int up) { if (empty()) return; back() |= (up & meImpossible); back() |= (up & meRestituer); }
   bool CheckExec() { if (empty()) return false; bool ret = (back() & meImpossible) != 0; back() &= ~meImpossible; return ret; }
};

enum T_Command {
   command_None, command_Cast, command_Oper, command_Call, command_GoTo, command_Label, 
   command_NewVar, command_NewArr, command_PushVar, command_PushVal, command_PushArr, command_PushAal, 
   command_PushInt, command_PushNum, command_Pop,
   command_Return, command_Exit, command_InitArr
};

class TNodeCommand : public TNode {
public:
   TNodeCommand() :command(command_None), param(0), mode(0), base_type(btUnknown) {}
   TNodeCommand(T_Command c, int p) :command(c), param(p), mode(0), base_type(btUnknown) {}
   TNodeCommand(T_Command c, int p, int m, T_BaseType b) :command(c), param(p), mode(m), base_type(b) {}
public:
   virtual void Codes(TSemantic &semantic, int mode);
   virtual T_BaseType BaseType() const { return base_type; } 
public:
   T_Command command;
   int param, mode;
   T_BaseType base_type; 
public:
   virtual const char* title() const   { return "TNodeCommand"; }
   virtual void print(int level, TPrinter& printer) const;
   virtual void write(TWriter& printer) const;
};

class TQuadruple {
public:
   enum T_Quad {
      qtNone, qtConst, qtBinary, qtUnary, qtCast, qtSet, qtGoto, qtIf, qtParam, qtCall, qtReturn, qtIndex, qtRange, qtVariable, qtArray, qtReferense, qtPointer, qtRefer, qtLabel
   };
public:
   TQuadruple(T_Quad q = qtNone, TNode* n = NULL) :quad(q), value_number(this), param(0), oper(0), mode(0), node(n) {}
public:
   void write(TWriter& printer) const;
public:
   T_Quad quad;
   TAddress value_number, arg_one, arg_two, result;
   int oper;
   int param, mode;
public:
   TNode* node;
};

const char* quadruple_title(TQuadruple::T_Quad quad);

class TQuadTable : public std::vector<TQuadruple*> {
public:
   TQuadTable();
   void Add(TQuadruple* quad, int counter = 0);
   void AddLabel(TQuadruple* quad, int counter);
public:
   bool Verify();
   int  Label(int& current);
   int  LabelGoTo(int& current);
   int  GoToLabel(int& current);
   int  GoToGoToLabel(int& current);
public:
   void write(TWriter& printer) const;
   void write_label(TPrinter& printerL) const;
public:
   void ValueNumber(TAddress& value_number);
   void Reset();
   int  Count() const { return (int)size(); }
protected:
   int value_numbar_maker[T_Alloc::taCommand + 1];
public:
   std::vector<int> label_quad;
};

enum T_VerifyMode { mvNone = 0x00, mvOffBefore = 0x01, mvOnAfter = 0x02, mvNoFunction = 0x04
};

#include "define_cast.h"

struct TCastItem {
public:
   TCastItem() :weight(-2), cast(_______) {}
   TCastItem(int w, T_CastType c) :weight(w), cast(c) {}
public:
   int weight;
   T_CastType cast;
};

class TCastables : public std::vector<T_CastType> {
public:
   TCastables() {}
	T_CastType Cast(int i) const { return (*this)[i]; } 
public:
};

const TCastItem& Castable(T_BaseType from, T_BaseType to);
T_BaseType CastableBetween(T_BaseType one, T_BaseType two);

class T_Profile : public std::vector<T_BaseType> {
public:
   T_Profile() :result(btUnknown) {}
   T_Profile(T_BaseType r) :result(r) {}
   virtual ~T_Profile() {}
public:
   void Add(T_BaseType p) { push_back(p); }
	int  Match(const T_Profile &join) const;
	bool match(const T_Profile &join) const;
	int  Cast(const T_Profile &join, TCastables &castables) const;
public:
   T_BaseType result;
};

class TFuncProfile : public T_Profile {
public:
   TFuncProfile(const T_Lexeme& l) :T_Profile(), ident(l) {}
public:
   T_Lexeme ident;
};

class TOperProfile : public T_Profile {
public:
   TOperProfile() :oper(T_Symbol::T_Type::lxNone), T_Profile() {}
   TOperProfile(T_Symbol::T_Type o, T_BaseType e, T_BaseType l) :oper(o), T_Profile(e) { Add(l); }
   TOperProfile(T_Symbol::T_Type o, T_BaseType e, T_BaseType l, T_BaseType r) :oper(o), T_Profile(e) { Add(l); Add(r); }
public:
   T_Symbol::T_Type oper;
};

class TOperTable : public std::vector<TOperProfile> {
public:
   TOperTable() {}
   const TOperProfile* Oper(T_Symbol::T_Type oper, T_BaseType left, T_BaseType right = btUnknown) const;
public:
   void Clear();
   int count() const { return (int)size(); }
};

// --------------------------- TSemantic ---------------------------

class TSemantic
{
public:
   TSemantic(A_Syntax *s);
   ~TSemantic();
public:
   int  AddDefFunc(TNodeDefFunc* func);
   int  AddDefVar(TNodeDefVar* var) { return semantic->AddDefVar(var); }
   TNodeDefVar* GetDefVar() { return semantic->GetDefVar(); }
public:
   void AddCode(TNode* code, int counter = -1);
   TCodeTable& Code();
   void WriteCode(TPrinter& printer);
public:
   void AddQuad(TQuadruple* quad, int counter = 0);
   TQuadruple& LastQuad() { return *Quad().back(); }
   void ValueNumber(TAddress& value_number) { Quad().ValueNumber(value_number); }
   TQuadTable& Quad();
   void WriteQuad(TPrinter& printer);
   void WriteConst(TPrinter& printer) const;
public:
   void AddError(TNode* node, T_Error error = T_Error::erNone);
   int  yes_error() { return (int)syntax->ErrorTable.size(); }
   void impossible(TNode* node, int mode = 0);
   void clear(TNode* node) { syntax->clear(node); }

   TNodeDefFunc* FindFunc(const TFuncProfile &profile, TFinder& finder) const;
   TNodeDefVar*  FindIdent(const T_Lexeme &l) const;

   bool Search(TFinder& finder);

   TBlock* Block(T_Block type = T_Block::tbNone) const { return semantic->Block(type); }
   TNodeLabel* BreakContinueLabel(T_Block type) const { return semantic->BreakContinueLabel(type); }
   void BlockBegin(TBlock* block) { semantic->BlockBegin(block); }
   void BlockTrunc(int trunc) { semantic->BlockTrunc(trunc); }
   void BlockEnd(TNode *node, bool del = false) { semantic->BlockEnd(node, del); }
   int  BlockSize() const { return semantic->BlockSize(); }

   const TOperProfile* Oper(const T_Lexeme &lexeme, T_BaseType left, T_BaseType right = btUnknown) const;
   void MakeBinaryOper(const char* oper, T_BaseType result, T_BaseType left, T_BaseType right);
   void MakeBinaryOper(T_Symbol::T_Type oper, T_BaseType result, T_BaseType left, T_BaseType right);
   void MakeUnaryOper(T_Symbol::T_Type oper, T_BaseType result, T_BaseType param);
   void MakeOperTable();

   void MakeGoToLabel(T_UserGoToLabel* item) { semantic->MakeGoToLabel(item); }
	bool Compare(const T_Lexeme &l, const T_Lexeme &r) const { return syntax->Compare(l,r); }

   bool Translate();
   bool VerifyFunc();

   T_CastType GetCastable(T_BaseType from, T_BaseType to);
   bool GenCastable(TNode* &node, T_BaseType type, int mode = 0x00); // 0x01 - code, 0x02 - const
   bool GenCastable(T_BaseType from, T_BaseType to) { int made = -1; return GenCastable(from, to, made); }
   bool GenCastable(T_BaseType from, T_BaseType to, int& made);
   void GenCommand(T_Command command, int param, int mode, T_BaseType type, int made = -1);
   void GenCommand(T_Command command, int param, T_BaseType type = btUnknown, int made = -1) { GenCommand(command,param,0,type,made); }
   void GenPop(int count, int made = -1) { if (count) GenCommand(T_Command::command_Pop,count,T_BaseType::btVoid,made); }
   void GenNumber(const T_Lexeme &lexeme);
   TNode* GetCommand(int counter);

   TNodeLabel* Merge(TNodeLabel* l1, TNodeLabel* l2);
   void Reference(TNodeLabel* label, TNodeLabel* refer);
   bool MakeLogical(TNode* &node, TNodeLabel* &true_label, TNodeLabel* &false_label);
   void MakeValue(TNodeLabel* true_label, TNodeLabel* false_label, int &made);
   bool FindLabel(TNodeBreakContinue &goto_node) { return semantic->FindLabel(goto_node); }
public:
   void print_tree(const char* title = NULL);
   void Result(const char* file = NULL);
   void Count(int& execs, int& blocks, int& idents) const;

public:
   enum T_Mode { tmNone = 0x000, tmVariable = 0x0001, tmCode = 0x0004, 
      tmTree = 0x0020, tmBlock = 0x0040, tmQuad = 0x0080, 
      tmStack  = 0x0100 
   };
   bool IsTree() const { return (mode & tmTree) != 0; }
   bool IsBlock() const { return (mode & tmBlock) != 0; }
   bool IsStack() const { return (mode & tmStack) != 0; }
   bool IsVariable() const { return (mode & tmVariable) != 0; }
   bool IsQuad() const { return (mode & tmQuad) != 0; }
   void Mode(T_Mode m) { mode = m; }
   bool SemanticMode(A_Syntax::M_Mode area, A_Syntax::M_Mode mode) const;
   void print_semantic_mode();
public:
   T_Mode mode;
   TNodeDefFunc* function;
   TNodeType *type_node;
public:
   ASemantic*  semantic;
public:
   TQuadTable  QuadTable;
   T_ExecStack ExecStack;
   TFuncTable  FuncTable;
   TCodeTable  CodeTable;
   TUserGoToTable   UserGoToTable;
   TUserLabelTable  UserLabelTable;
public:
   A_Syntax* syntax;
   int       level;
   int       print_mode;
   int       block_number;
public:
   int AddInt, MultiInt;
   int code_count, quad_count;
public:
   TPrinter printer;
};

#define SYNTAX_MODE(P1,P2) syntax->SemanticMode(A_Syntax::mm##P1, A_Syntax::mm##P2)
#define SEMANTIC_MODE(P1,P2) semantic.SemanticMode(A_Syntax::mm##P1, A_Syntax::mm##P2)

TOperTable& OperTable();

class VEntry
{
public:
   VEntry(TSemantic* s, TNode* node);
   ~VEntry();
public:
   TSemantic* semantic;
};
#endif

