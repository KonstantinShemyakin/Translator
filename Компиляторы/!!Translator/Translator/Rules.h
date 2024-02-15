#ifndef TRN_RULES_H
#define TRN_RULES_H

#include <stack>
#include <set>
#include <vector>
#include <map>
#include "Parse.h"

#define PRODUCE_ITEM_EMPTY_

class TGrammar;
class GFormula;
class Produce;
struct GSymbol 
{
public:
   enum T_Type { gsNone, gsFormula, gsProduce, gsTerminal, gsVector, gsEmpty, gsEof, gsMaker, gsRule, gsPoint, gsPara, gsSituation, gsTable };
   enum T_Mask { msNone = 0x00, msFormula = 0x0001, msProduce = 0x0002, msTerminal  = 0x0004, msVector = 0x0008,
                                msEmpty   = 0x0010, msEof     = 0x0020, msMaker     = 0x0040, msRule   = 0x0080, 
                                msPoint   = 0x0100, msPara    = 0x0200, msSituation = 0x0400 };
   enum T_Mode { None = 0x00, Call = 0x02, Turn = 0x04, Tree = 0x08, Code = 0x10, Master = 0x20, Yacc = 0x0100, SNode = 0x0200, Warning = 0x0400,
                 Used = 0x0800, Deleted = 0x1000, Caller =  0x0F000000 };
public:
   GSymbol(T_Type t = gsNone, int g = 0, int s = 0, int p = 0, int m = 0) :type(t), _formula(g), _produce(s), point(p), mode(m) {}
   GSymbol(const T_Lexeme &l);
   bool IsNone     () const { return type == gsNone     ; }
   bool IsEmpty    () const { return type == gsEmpty    ; }
   bool IsTerminal () const { return type == gsTerminal ; }
   bool IsEof      () const { return (type == gsEof) || IsTerminal() && (group == T_Lexeme::grEof); }
   bool IsFormula  () const { return type == gsFormula  ; }
   bool IsMaster   () const { return (type == gsFormula) && (mode & Master); }
   bool IsProduce  () const { return type == gsProduce  ; }
   bool IsStart    () const { return (type == gsProduce) && !formula  && !produce || (type == gsFormula) && !formula; }
   bool IsMaker    () const { return type == gsMaker    ; }
   bool IsMakerTree() const { return (type == gsMaker) && (mode & Tree); }
   bool IsMakerCode() const { return (type == gsMaker) && (mode & Code); }
   bool IsMakerYACC() const { return (type == gsMaker) && (mode & Yacc); }
   bool IsMakerNode() const { return (type == gsMaker) && (mode & SNode); }
   bool IsMakerTurn() const { return (type == gsMaker) && (mode & Turn); }
   bool IsMakerCall() const { return (type == gsMaker) && (mode & Call); }
   int  MakerCaller() const { return (mode & Caller) >> 24; }
   bool IsPoint    () const { return type == gsPoint    ; }
   bool IsPara     () const { return type == gsPara     ; }
   bool IsBasic    () const { return (type == gsPara) && (point || !formula  && !produce); }
   bool IsSituation() const { return type == gsSituation; }
   bool IsVector   () const { return type == gsVector   ; }
   bool IsTable    () const { return type == gsTable    ; }
   bool IsUsed     () const { return (mode & Used) != 0 ; }
   bool IsDeleted  () const { return (mode & Deleted) != 0; }
   int  MakerParam () const { return param;               }
   bool IsSaved    () const;
   bool Cast();
   int  Change(int mode);
public:
   bool operator == (const GSymbol& t2) const;
   bool operator <  (const GSymbol& t2) const;
   GSymbol& operator = (const T_Lexeme &l);
public:
   int  print_maker(TPrinter& printer) const;
   int  print(TPrinter& printer, int p = -1) const;
   int  YACC (TPrinter& printer) const;
   int  MACRO(TPrinter& printer) const;
   int  PROG (TPrinter& printer) const;
   void write(TWriter& printer) const;
   bool read (FILE *file, const TGrammar* grammar, int print_mode = 0x00);
public:
   T_Type type;
   int    mode;
   union {
      struct { int situation   ;                      }; // Situation
      struct { int formula     , produce;             }; // Formula, Produce
      struct { T_Lexeme::T_Group group; int lexeme_type, value; }; // Lexeme, Terminal
      struct { int maker       , param       , func;  }; // Maker
      struct { int node        , param_      , step ; }; // MakerCall
      struct { int _formula    , _produce    , point; }; // Para
      struct { int vector      ;                      }; // Vector
      struct { int table       ;                      }; // Table
   };
public:
   static const GSymbol none, empty, eof, sharp;
};

class TTwoSym {
public:
   TTwoSym() :one(), two() {}
   TTwoSym(GSymbol o, GSymbol t) :one(o), two(t) {}
   bool operator == (const TTwoSym& p) const { return ((*this).one == p.one) && ((*this).two == p.two); }
   bool operator <  (const TTwoSym& p) const { return ((*this).one <  p.one) || ((*this).one == p.one) && ((*this).two < p.two); }
public:
   void print(TPrinter& printer) const;
public:
   GSymbol one, two;
};

class TTwoSymVector : public std::vector<TTwoSym> {
public:
   void Add(const TTwoSym& item) { push_back(item); }
};

template <class T_Item> class T_SetQueue : public std::set<T_Item> {
public:
   bool Push(const T_Item& item) { if (std::set<T_Item>::find(item) != std::set<T_Item>::end()) return false; std::set<T_Item>::insert(item); return true; }
   bool Pop(T_Item& item) { if (std::set<T_Item>::empty()) return false; item = *std::set<T_Item>::begin(); std::set<T_Item>::erase(std::set<T_Item>::begin()); return true; }
};

class TTwoSymQueue : public T_SetQueue<TTwoSym> {
};

class GSymbolVector : public std::vector<GSymbol>
{
public:
   GSymbolVector() {}
   GSymbolVector(const GSymbolVector& v, int mask);
   GSymbolVector& operator << (const GSymbol& s) { push_back(s); return *this; }
   GSymbolVector& operator << (const GSymbolVector& v);
public:
   void Add(const GSymbol& sym) { push_back(sym); }
   int  Find(const GSymbol& sym, int beg = 0) const;
   bool Have(const GSymbol& sym) const;
   bool HaveEmpty() const { return Have(GSymbol::empty); };
   bool IsEmpty() const;
public:
   int  count() const { return (int)size(); }
   void print(TPrinter& printer) const;
   void write(TWriter& printer) const;
};

class GSymbolSet : public std::set<GSymbol>
{
public:
   GSymbolSet() {}
   GSymbolSet(const GSymbol& s) { (*this) << s; }
public:
   GSymbolSet& operator << (const GSymbol& s);
   GSymbolSet& operator << (const GSymbolSet& s) { *this += s; return *this; }
   bool operator == (const GSymbol& s) const { return ((int)size() == 1) && (find(s) != end()); }
   int  operator += (const GSymbol& s);
   int  operator += (const GSymbolSet& m);
   GSymbolSet operator * (const GSymbolSet& join) const;
   GSymbolSet operator - (const GSymbolSet& join) const;
   bool Add(const GSymbol& sym);
   bool Del(const GSymbol& sym);
   bool Have(const GSymbol& sym) const;
   bool HaveEmpty() const { return Have(GSymbol::empty); };
   bool IsEmpty() const;
   void Plus(const GSymbolSet& left, const GSymbolSet& right);
public:
   int  count() const { return (int)size(); }
   void print(TPrinter& printer) const;
public:
   static const GSymbolSet none;
};

class GSymbolQueue : public T_SetQueue<GSymbol> {
};

class TwoSymGSymbolSetMap : public std::map<const TTwoSym, GSymbolSet>
{
public:
   bool Add(const TTwoSym& key, const GSymbol& sym);
   const GSymbolSet& Get(const TTwoSym& key) const;
   bool Have(const TTwoSym& key) const { return (find(key) != end()); }
};

class TData; class TRuleNames;

class GProduce : public GSymbolVector
{
public:
   GProduce() :head(GSymbol::gsProduce), maker(), prepare_mask(0) {}
   GProduce(const GSymbol& s) :head(s), maker(), prepare_mask(0) {}
   int  count() const { return (int)size(); } 
   int  Count() const;
   int  Real(int mode = 0x00) const; // 0x01 - space
   int  Master() const;
   int  MasterMask() const;
   bool Compare(const GProduce& join) const;
   void Add(const GSymbol& s);
   void Shift(GSymbol& para) const;
   bool IsEmpty(bool maker = true) const;
   bool IsChain() const;
   bool HaveMaster() const;
   void OrMode(int mode)   { if (empty()) return; back().mode  |= mode;  }
   void OrParam(int param) { if (empty()) return; back().param |= param; }
   void Tail(int point, GSymbolVector& tail) const;
   void Tail(const GSymbol& point, GSymbolVector& tail) const { Tail(point.point + 1, tail); }
   void TailWithoutMaker(int point, GSymbolVector& tail) const;
   void TailWithoutMaker(const GSymbol& point, GSymbolVector& tail) const { TailWithoutMaker(point.point + 1, tail); }
   void SymAndTail(const GSymbol& point, GSymbolVector& tail) const { Tail(point.point, tail); }
public:
   bool IsUsed() const { return head.IsUsed(); }
   void SetUsed() { head.mode |= GSymbol::Used; }
   void ClearUsed() { head.mode &= ~GSymbol::Used; }
   bool IsDeleted() const { return head.IsDeleted(); }
   void SetDeleted() { head.mode |= GSymbol::Deleted; }
public:
   GSymbol head, maker;
   int  prepare_mask;
public:
   void PROG (TPrinter& printer, int print_mode = 0x00) const; // FORMULA_TITLE_PREFIX - prefix
   void write(TWriter& printer) const;
   bool read (FILE *file, const TGrammar* grammar, int print_mode = 0x00);
   void print(TPrinter& printer, int point = -1) const;
};

class TLexemeSet;
class GFormulaTable : public std::vector<GFormula*>
{
public:
   GFormulaTable() :root(NULL), readed(false) {}
   GFormulaTable(const GFormulaTable& join); 
   ~GFormulaTable();
   void Copy(const GFormulaTable& join);
   bool Add(GFormula* f, int &index);
   bool Add(GFormula* f) { int index; return Add(f, index); }
   GFormula* Find(const char* title);
   bool Find(const GFormula& f, int &index) const;
   bool make(TRuleNames& names);
   int  count() const { return (int)size(); } 
   void prepare(TPrinter& printer);
   void print(TPrinter& printer) const;
   bool read (const char* title, int print_mode = 0x00);
   void write(TWriter& printer) const;
   bool read (FILE* file, int print_mode = 0x00);
public:
   void Used(TLexemeSet& lexemes);
   void Used(const GFormula&);
   bool make(TRuleNames& names,TLexemeSet& lexemes);
   void used_for_all();
   void used_for_root();
   int  deleting_chains(bool without_name = true);
   bool delete_left_recursion(bool terminal_only = true);
   void terminal_only_first();
   void delete_temporary_title(bool del = false);
public:
   GFormula* root;
   std::vector<int> used;
   bool readed;
};

enum T_Perepare { prNone, prLL_0, prLL_1, prLR_0, prLR_1, prLR_N1, prLR_1M, prLR_NM, prEqu_0, prEqu_1, prTerminalOnly };

class GFormula : public std::vector<GProduce>
{
public:
   GFormula() :head(GSymbol::gsFormula), title(NULL), used(0), prepared(0) {}
   GFormula(const GSymbol sym) :head(sym), title(NULL), used(0), prepared(0) {}
   void Add(const GProduce& p) { push_back(p); }
   void Add(const GSymbol item) { back() << item; }
   int  count() const { return (int)size(); } 
   bool IsRecursive() const;
   bool IsEmpty() const { return (!size() || (count() == 1) && front().IsEmpty()); }
   bool IsChain() const { return (count() == 1) && front().IsChain(); }
   bool HaveEmpty(bool maker = true) const;
   bool HaveChain() const;
   bool Compare(const GFormula& join) const;
   bool IsUsed() const { return head.IsUsed(); }
   void SetUsed() { head.mode |= GSymbol::Used; }
   void ClearUsed() { head.mode &= ~GSymbol::Used; }
   bool IsDeleted() const { return head.IsDeleted(); }
   void SetDeleted() { head.mode |= GSymbol::Deleted; }
   bool DeleteImmediateLeftRecursion(GFormulaTable& table);
   bool ReplaceFirst(const GFormula& formula_first);
public:
   GSymbol head;
public:
   mutable int used;
   int  prepared;
public:
   void PROG (TPrinter& printer, int print_mode = 0x00) const; // FORMULA_TITLE_PREFIX - prefix
   void write(TWriter& printer) const;
   bool read (FILE *file, const TGrammar* grammar, int print_mode = 0x00);
   void print(TPrinter& printer) const;
public:
   int  write_title(TPrinter& printer) const;
   const char* title;
};

class TRuleNames : public TNameTable {
public:
   bool verify(const GFormulaTable& formulas) const;
};

class GMakerTable; class A_Syntax; class TSemantic; class TRuleNames; class TLexemeSet; 
class TTableKey; class TTableMap; class LRTableMap; struct TAction;
class TData {
public:
   TData() :names(NULL), grammar(NULL), formulas(NULL), lexemes(NULL), makers(NULL), LLTable(NULL), LRTable(NULL),
            syntax(NULL), semantic(NULL), root(NULL), option(0), print_mode(0), file(NULL), tokens(NULL) {}
   TData(TGrammar* g, A_Syntax* syn, TSemantic* sem);
public:
   const GFormula& Formula(const GSymbol &sym) const;
   const GProduce& Produce(const GSymbol &sym) const;
   const GSymbol&  Cell(const TTableKey& key) const;
   const TAction&  Action(const TTableKey& key) const;
   const GFormula* Root() const;
public:
   const char*    file;
   TTokenNames*   tokens;
   TRuleNames*    names;
   GFormulaTable* formulas;
   GFormula*      root;
   TGrammar*      grammar;
   GMakerTable*   makers;
   A_Syntax*      syntax;
   TSemantic*     semantic;
   TLexemeSet*    lexemes;
   TTableMap*     LLTable;
   LRTableMap*    LRTable;
public:
   int            option, print_mode;
};

class TIndexes : public std::map<int, int> {
public:
   TIndexes() {}
   int  Add(int i);
   int  Get(int i) const;
   int  Teg(int i) const;
   void Clear() { clear(); index.clear(); }
private:
   std::vector<int> index;
};

class TopologicalSort {
public:
   TopologicalSort(int n) :N(n) { Color.resize(n, 0); Numbers.resize(n); Edges.resize(n); }
   bool sort();
   void add(int i, int j) { Edges[i].push_back(j); }
private:
   bool dfs(int v);
public:
   std::vector<int> Color;
   std::stack<int>  Stack;
   std::vector<int> Numbers, Indexes;
   int N;
   std::vector< std::vector<int> > Edges;
};

int syn_tree(int s1);
int syn_tree(int s1, int s2);
int syn_tree(int s1, int s2, int s3);
int syn_tree(int s1, int s2, int s3, int s4);
int syn_tree(int s1, int s2, int s3, int s4, int s5);

const char* symbol_title(GSymbol::T_Type type);

#endif
