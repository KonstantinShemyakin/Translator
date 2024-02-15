#ifndef TRN_GBUILDER_H
#define TRN_GBUILDER_H

#include "Grammar.h"

class TPara : public GSymbol
{
public:
   TPara(T_Type t = gsNone, int g = 0, int s = 0, int p = 0, int m = 0) :GSymbol(t, g, s, p, m), sym() {}
   TPara(const GSymbol& s) :GSymbol(s), sym() { /*type = gsPara;*/ }
   TPara(const GSymbol& p, const GSymbol& s) :GSymbol(p), sym(s) { /*type = gsPara;*/ }
   TPara(const TPara& p) :GSymbol(p), sym(p.sym) { /*type = gsPara;*/ }
public:
   bool operator == (const TPara& p) const;
   bool operator <  (const TPara& p) const;
   int  print(TPrinter& printer) const;
   void write(TWriter& printer) const;
public:
   GSymbol sym;
};

class TParaSet : public std::set<TPara>
{
public:
   TParaSet(const TGrammar* g) :grammar(g), mode(0) {}
   TParaSet(const TGrammar* g, const TParaSet& I);
   TParaSet(const TGrammar* g, const TPara& s) :grammar(g), mode(0) { (*this) << s; }
public:
   TParaSet& operator << (const TPara& s) { Add(s); return *this; }
   TParaSet& operator << (const TParaSet& s) { *this += s; return *this; }
   int  operator += (const TPara& s);
   int  operator += (const TParaSet& m);
   bool Add(const TPara& sym);
   bool Have(const TPara& para) const;
   bool Have(const TParaSet& join) const;
   bool ValidLRk() const;
   bool ValidSLRk() const;
   void Basic();
   bool CoreCompare(const TParaSet& join) const;
   TParaSet* Core() const;
   int  Change(int mode);
   int  count() const { return (int)size(); }
public:
   void print(TPrinter& printer) const;
   void write(TWriter& printer) const;
public:
   int mode;
   const TGrammar* grammar;
   static TParaSet Empty;
};

// Red(p=244)
// ------------------------------------------------ TC2A -----------------------------------------------

#define TC2A_MAKE_QUEUE_
class TAmu {
public:
   TAmu(const GSymbol& p) :point(p), step(0), produce(0) {}
   //   bool operator == (const TAmu& p) const { return ((*this).point == p.point); }
   //   bool operator <  (const TAmu& p) const { return ((*this).point <  p.point); }
   //   bool operator == (const TAmu& p) const { return ((*this).point == p.point) && ((*this).mu == p.mu); }
   //   bool operator <  (const TAmu& p) const { return ((*this).point <  p.point) || ((*this).point == p.point) && ((*this).mu < p.mu); }
public:
   const GSymbol point;
   mutable TFirst mu, half;
   mutable int step, produce;
};

class TAmus : public std::map<const GSymbol, TAmu> {
public:
   TAmus() {}
   bool Add(const TAmu& mu);
public:
   static const TAmus none;
};

class TBTailItem {
public:
   TBTailItem() :step(0), count(0) {}
   void print(TPrinter& printer) const;
public:
   TFirst delta, half;
   int step, count;
};

class TBTails : public std::map<const GSymbol, TBTailItem> {
public:
   TBTails(TGrammar *g) :grammar(g) {}
   TBTailItem* Get(const GSymbol& point);
public:
   void print(TPrinter& printer) const;
public:
   TGrammar *grammar;
};

class Tc2a : public std::map<const GSymbol, TAmus> {
public:
   Tc2a() :step(0) {}
   bool Add(const GSymbol& A, const TAmu& mu);
public:
   const TAmus& Get(const GSymbol& C);
   void print(TPrinter& printer) const;
public:
   GSymbolSet terminals;
#ifdef TC2A_MAKE_QUEUE
   GSymbolVector points;
#endif
public:
   int step;
};

class TC2A : public std::map<const GSymbol, Tc2a> {
public:
   TC2A(TGrammar *g = NULL) :grammar(g), step(0), modif_count(0), point_tails(g) {}
   void Init();
   void Core();
   bool Verify() const;
public:
   Tc2a& Get(const GSymbol& C);
   const Tc2a& Get(const GSymbol& A) const { return at(A); }
   TAmus& Get(const GSymbol& C, const GSymbol& A);
#ifdef TC2A_MAKE_QUEUE
   void Make(const GSymbol& point, const GSymbol& C);
   void Make(const GSymbol& C);
#else
   int  Make(const GSymbol& B, const GSymbol& C, const GSymbol& point);
   int  Make();
#endif
public:
   void Split();
   void Merge();
public:
   void print(TPrinter& printer) const;
   int  modif_count;
public:
   TGrammar *grammar;
   int step;
   TBTails point_tails;
#ifdef TC2A_MAKE_QUEUE
   GSymbolQueue queue;
#endif
};

class TTableMap;
class TNextTab;
class TSituationMap
{
public:
   TSituationMap() :step(0) {}
   virtual GSymbol Add(TParaSet* key);
   TSituationMap& operator << (TParaSet& s) { Add(&s); return *this; }
   TParaSet* Get(const GSymbol& sym) const;
   virtual GSymbol Find(const TParaSet&) const;
   virtual void Clear();
   int  ValidLRk();
   int  ValidSLRk();
   void Basic();
   void Copy(const TSituationMap& join);
   void make_NEXTs(const TTableMap& GOTOtable, TNextTab& NEXTs);
   void Expansion(const TFirstFollowTable& table, TSituationMap& TO) const;
   int  change(int mode);
public:
   int  count() const { return (int)vector.size(); }
   void print(TPrinter& printer) const;
   void print() const { TPrinter printer; print(printer); }
   void write(TWriter& printer) const;
public:
   int step;
protected:
   struct Key {
      Key(const TParaSet *p) :key(p) {}
      bool operator == (const Key& k) const { return *key == *k.key; }
      bool operator <  (const Key& k) const { return *key <  *k.key; }
   public:
      const TParaSet *key;
   };
   std::map<const Key, const GSymbol> map;
   std::vector<TParaSet*> vector;
};

class TCoreArrItem : public std::vector<int> { };
class TCoreArr : public std::vector<TCoreArrItem>
{
public:
};

class TSituationCore : public TSituationMap
{
public:
   TSituationCore() {}
   GSymbol Add(TParaSet* key, int situation);
   const TCoreArr& Core() const { return core_arr; }
   void print(TPrinter& printer) const;
protected:
   TCoreArr core_arr;
};

class TClosureAdded : protected std::vector<int>
{
public:
   TClosureAdded(TGrammar* g) :current(0), formula_count(0), sym_count(0), grammar(g), type(-1) {}
   void Init(int m); // -1 - off, 0 - LR0, 1 - LR1, 2 - LALR, 3 - LRk, 4 - Core
   void Next() { current++; }
   bool Added(const GSymbol &formula);
   bool Added(const GSymbol &formula, const GSymbol &lexeme);
   void Set(const GSymbol &formula, const GSymbol &lexeme);
   int  Current() const { return current; }
   int  Index(const GSymbol &lexeme) const;
protected:
   void Init(int f, int s);
   void Set(int f, int s = 0) { (*this)[s * formula_count + f] = current; }
   bool Get(int f, int s = 0) const { return (*this)[s * formula_count + f] == current; }
protected:
   TGrammar * grammar;
   size_t formula_count, sym_count;
   int  type;
   int  current;
};

class TSituationKernel : public TSituationMap
{
public:
   TSituationKernel() :yes_queue(false) {}
   ~TSituationKernel() { Clear(); }
   virtual GSymbol Add(TParaSet* key);
   virtual GSymbol Find(const TParaSet&) const;
   virtual void Clear();
public:
   GSymbolQueue queue;
   bool yes_queue;
};

class TLookAhead
{
public:
   class TElement {
   public:
      TElement() {}
      TElement(const TElement& e) :situation(e.situation), para(e.para) {}
      TElement(const GSymbol& s, const TPara& p) :situation(s), para(p) {}
   public:
      bool operator == (const TElement& k) const { return (situation == k.situation) && (para == k.para); }
      bool operator <  (const TElement& k) const { return (situation <  k.situation) || (situation == k.situation) && (para <  k.para); }
   public:
      void print(TPrinter& printer) const;
   public:
      GSymbol situation; TPara para;
   };
public:
   TLookAhead(const TGrammar* g = NULL) :grammar(g) {}
   void Add(const TElement& key);
public:
   class TItem {
   public:
      TItem() :symbols() {};
      void Add(const TElement& expansion) { expansions.push_back(expansion); }
   public:
      GSymbolSet symbols;
      std::vector<TElement> expansions;
   };
public:
   TLookAhead::TItem& Get(const TElement& key) { return map.at(key); }
   int  count() const { return (int)map.size(); }
   void print(TPrinter& printer) const;
public:
   std::map<const TElement, TItem> map;
public:
   const TGrammar* grammar;
};

// ------------------------------ GrammarSplitting -------------------------------
// Green(v=2,7.4.3)
// Green(v=2,p=104,a=7.12)

class TGrammarGroupItem : public TGrammar {
public:
   TGrammarGroupItem() :general(NULL) {}
   virtual GVectors& Vectors() { return general->Vectors(); }
   virtual const GVectors& Vectors() const { return general->Vectors(); }
public:
   GSymbol       S_;
   TSituationMap Stable;
   TGrammar*     general;
   TTableMap     GOTOtable;
};

class TGrammarGroup : public std::map<GSymbol, TGrammarGroupItem*> {
public:
   TGrammarGroup(TGrammar* g) : general(g), derivation(NULL) {}
   ~TGrammarGroup() { Clear(); }
   bool AddGrammar(const GSymbol& root);
   void FormulaToTerminal(GSymbol& sym);
   void TerminalToFormula(GSymbol& sym);
   void Disclosure(const TSituationMap&, TSituationMap&) const;
public:
   void Clear();
   void print(TPrinter& printer) const;
public:
   TDerivation* derivation; // print
   TGrammar* general;
};

class TGrammarBuilder
{
public:
   TGrammarBuilder(TGrammar* g, const char* f = NULL) :root(NULL), grammar(g), Mtable(g), LRtable(g), GOTOtable(g), level(0), max_level(0), true_count(0), false_count(0), 
      Added(g), CtoAa(g), LookAhead(g), look_ahead(1), file(f), NEXTs(g) {}
   bool make_LL1Table();
   bool make_LR0States();
   bool make_LR0Table();
   void make_ActionLR0(const TSituationMap& stable, const GSymbol& situation);
   void make_StateLR0(const GSymbol& situation, const GSymbol& X);
   void make_StateLR0(const GSymbol& situation);
   void make_StateLR1(TSituationMap& stable, const GSymbol& situation, const GSymbol& X);
   void make_StateLR1(TSituationMap& stable, const GSymbol& situation);
   void make_ActionLR1(TSituationMap& stable, const GSymbol& situation, int mode); // 0x01 - basic, 0x02 - GOTO, 0x04 - LALR, 0x08 - make_go_to
   bool make_LR1Table(TSituationMap& stable, int mode);
   bool make_LR1States();
   bool make_LR1Table();
   void make_ActionC2Aa(const TSituationMap& stable, const GSymbol& situation, A_Syntax::T_SyntaxMode mode);
   void make_StateC2Aa(TSituationMap& stable, const GSymbol& situation, const GSymbol& X, A_Syntax::T_SyntaxMode mode);
   void make_StateC2Aa(TSituationMap& stable, const GSymbol& situation, A_Syntax::T_SyntaxMode mode);
   bool make_C2Aa_LR(A_Syntax::T_SyntaxMode mode);
   bool make_C2Aa_LALR();
   bool make_LALRTable();
   bool make_LALR_FullTable(A_Syntax::T_SyntaxMode mode);
   bool Make(A_Syntax::T_SyntaxMode syntax_mode, const char* file);
   bool Analyze(A_Syntax::T_SyntaxMode syntax_mode, const char* file);
public:
   bool make_LLkTable(int k);
   bool make_SLRkTable(int k);
   bool make_LRkTable(int k);
   bool make_LR0Core();
   bool make_LRkCore(int k);
   bool make_LALRk_FullTable(A_Syntax::T_SyntaxMode mode, int k);
   bool make_LALRkTable(int k);
   bool make_LALRkCore(int k);
public:
   bool make_FiUnattainable(int k);
   bool make_GrammarSplitting(int k);
public:
   int look_ahead;
public:
   GFormula * root;
   TSituationMap     Stable;
   TSituationMap     TablePrint;
   TSituationCore    COREtable;
   TSituationKernel  LALRStable;
   TTableMap         Mtable;
   LRTableMap        LRtable;
   TTableMap         GOTOtable;
   TNextTab          NEXTs;   
public:
   TGrammar*         grammar;
   const char*       file;
public:
   TFirst & First(const GSymbol& key) { return grammar->First(key); }
   TFollow& Follow(const GSymbol& key) { return grammar->Follow(key); }
public:
   TClosureAdded     Added;
   TC2A              CtoAa;
   TLookAhead        LookAhead;
public:
   int level, max_level;
   int true_count, false_count;
};

#endif

