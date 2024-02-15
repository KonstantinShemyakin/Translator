#ifndef TRN_GRAMMAR_H
#define TRN_GRAMMAR_H

#include "RSyntax.h"

class TFirstFollowMap;
class TFirstFollow : public GSymbolSet
{
public:
   TFirstFollow(const TFirstFollowMap* g = NULL) :owner(g), k(-1) {}
   int  operator += (const GSymbol& sym) { return (GSymbolSet&)(*this) += sym; }
   int  operator += (const TFirstFollow& join);
   TFirstFollow operator * (const TFirstFollow& join) const;
public:
   int  Length(TGrammar * grammar);
   int  count() const { return (int)size(); }
   void print(TPrinter& printer) const;
public:
   int  k;
   const TFirstFollowMap* owner;
};

class TFirst : public TFirstFollow
{
public:
   TFirst(const TFirstFollowMap* g = NULL) :TFirstFollow(g) {}
   TFirst(const GSymbolVector& s, const TFirstFollowMap* g = NULL);
   int  operator += (const GSymbolVector& symbols);
   int  operator += (const GSymbol& sym) { return (GSymbolSet&)(*this) += sym; }
   int  operator += (const TFirst& join) { return (GSymbolSet&)(*this) += (GSymbolSet&)join; }
};

class TFollow : public TFirstFollow
{
public:
   TFollow(const TFirstFollowMap* g = NULL) :TFirstFollow(g) {}
};

class TFirstFollowMap : public std::map<const GSymbol, TFirstFollow>
{
public:
   TFirstFollowMap(TGrammar* g) :grammar(g) {}
   bool Add(const GSymbol& key, TFirstFollow& item);
   bool Have(const GSymbol& key, const GSymbol& sym) const;
   bool HaveEmpty(const GSymbol& key) const { return Have(key, GSymbol::empty); };
   bool FIRST(const GSymbolVector& alpha, TFirst& first) const;
   bool FIRST(const GSymbolVector& alpha, TFirst& first, int k) const;
   bool EFF(const GSymbolVector& alpha, TFirst& first, int k) const;
   bool FirstTail(const GSymbol& point, TFirst& first) const;
   bool FirstTail(const GSymbol& point, TFirst& first, int k) const;
   bool make_FIRSTs();
   bool make_FOLLOWs(const TFirstFollowMap& FIRSTs);
public:
   int  count() const;
   void print(TPrinter& printer) const;
public:
   TGrammar * grammar;
};

class TLangFirstMap;
class TLangFirst : public std::set<TFirst>
{
public:
   TLangFirst() :owner(NULL) {}
   bool Insert(const TFirst& item);
   void print(TPrinter& printer) const;
   void Merge(TFirstFollow& lang) const;
public:
   const TLangFirstMap* owner;
};

class TLangFirstMap : public std::map<const GSymbol, TLangFirst>
{
public:
   TLangFirstMap(TGrammar* g) :grammar(g) {}
   bool Add(const GSymbol& key, TLangFirst& item);
public:
   TGrammar * grammar;
};

class TFirstFollowTable
{
public:
   TFirstFollowTable() {}
   ~TFirstFollowTable() { Clear(); }
   GSymbol Add(const TFirstFollow& key);
   const TFirstFollow& Get(const GSymbol& sym) const;
   const TFirstFollow& Table(const GSymbol& tab) const { return Get(tab); }
   GSymbol Table(const TFirstFollow& key) { return Add(key); }
public:
   int  count() const { return (int)vector.size(); }
   void Clear();
   void Copy(const TFirstFollowTable& join);
   void print(TPrinter& printer) const;
protected:
   struct Key {
      Key(const TFirstFollow *p) :key(p) {}
      bool operator == (const Key& k) const { return *key == *k.key; }
      bool operator <  (const Key& k) const { return *key <  *k.key; }
   public:
      const TFirstFollow *key;
   };
   std::map<const Key, const GSymbol> map;
   std::vector<const TFirstFollow*> vector;
};

class TNextTab : public TwoSymGSymbolSetMap {
public:
   TNextTab(TGrammar* g) :grammar(g) {}
public:
   void print(TPrinter& printer) const;
public:
   TGrammar * grammar;
};

class GVectors
{
public:
   GVectors() {}
   ~GVectors() { clear(); }
   GSymbol Add(const GSymbolVector& key);
   const GSymbol& Find(const GSymbolVector& key) const;
   const GSymbolVector& Vector(const GSymbol& sym) const { return *vector[sym.group]; }
   bool Plus(const GSymbolSet& left, const GSymbolSet& right, GSymbolSet& result, int k);
   void Tails(GSymbolVector& from, GSymbolVector& to, const TLexemeSet& lexemes);
   int  MinLength(const TFirstFollow& alpha) const;
public:
   int  count() const { return (int)vector.size(); }
   void clear();
   void write(TWriter& printer) const;
   bool read(FILE* file, int print_mode);
public:
   struct Key {
      Key(const GSymbolVector *p) :key(p) {}
      bool operator == (const Key& k) const { return *key == *k.key; }
      bool operator <  (const Key& k) const { return *key <  *k.key; }
   public:
      const GSymbolVector *key;
   };
   std::map<const Key, const GSymbol> map;
   std::vector<const GSymbolVector*> vector;
};

class TGrammarBuilder;
class TableLLk;
class TGrammar
{
public:
   enum POption {
      opNone,
      opGrammar     = 0x00000001, opFollow      = 0x00000002, opMaker          = 0x00000004, opLexeme        = 0x00000008,
      opFirst       = 0x00000010, opEFF         = 0x00000020, opBNF            = 0x00000040, opBIF           = 0x00000080,
      opFormula     = 0x00000100, opAuto        = 0x00000200, opOutput         = 0x00000400, opC2A           = 0x00000800,
      opAction      = 0x00001000, opTable       = 0x00002000, opFiUnattainable = 0x00004000, opSplitting     = 0x00008000,
      opState       = 0x00010000, opStateCore   = 0x00020000, opStateSort      = 0x00040000, opGoTo          = 0x00080000,
      opAssociation = 0x00100000, opCompression = 0x00200000, opNoDefType      = 0x00400000, opNoPriorAssign = 0x00800000,
      opChainRule   = 0x01000000,
      opEof2Empty   = 0x10000000,                                                            opSelfParsing   = 0x80000000,
      opCell = opAction, opAhead = opC2A, opLLk = opC2A, opFiUn = opC2A, opSplittingAddition = opFiUnattainable
   }; // 0x003910FF
   enum T_SourceGrammar {
      sgLL, sgNL, sgLR, sgNR, // grammars
      sgETF_LL, sgETF_LLMake, sgETF_LR, sgETF_LRMake, sgEXPR_LR, // examples
      sgTable, sgBIF, sgBNF, sgYACC, sgY, sgParser, // parsers
      sgGrammar // reader
   };
public:
   TGrammar() :root(NULL), lexemes(this), FIRSTs(this), FOLLOWs(this), FIRSTsP(this), EFFs(this), SIGMAs(this), file(NULL),
      Mtable(this), LRtable(this), type(gtNone), option(0), prefix(""), look_ahead(0), TabLLk(NULL), builder(NULL), makers(NULL), names(NULL) {}
   GFormula* Find(const char* title) const;
   const GFormula& Formula(const GSymbol &sym) const;
   const GProduce& Produce(const GSymbol &sym) const;
   int  Replace(const GSymbol &from, const GSymbol &to);
public:
   void makers_used() const;
   void formulas_used() { formulas.used_for_all(); }
   void used_for_root() { formulas.used_for_root(); }
   bool Make(int type, const char* file);
   bool Print(int type, const char* file);
   void make_lexemes();
   bool make_produces();
   int  deleting_chains(bool without_name = true) { return formulas.deleting_chains(without_name); }
   bool make_start();
   bool make_start(GFormula* start) { root = start; return make_start(); }
   bool filter_makers(int filter);
   bool filter_makers(int make_mode, int mode); // 0x01 - !Code
   bool make_makers_head(bool group_maker);
   bool make_head_makers(bool reveal_vector);
   bool make_FIRSTs() { return FIRSTs.make_FIRSTs(); };
   bool make_FIRSTsP();
   bool make_FOLLOWs() { return FOLLOWs.make_FOLLOWs(FIRSTs); };
   void grammar_type();
   bool make_Symple();
   bool make_LeftFactoring();
   bool delete_LeftRecursion();
   void change_group();
   void delete_temporary_title(bool del = false) { formulas.delete_temporary_title(del); }
   void Used();
   bool NoEmptyLanguage(int mode = 0);
   bool UnacceptableSymbols(int mode = 0);
   bool ExcessRemoval(int mode = 0);
   int  ValidLLk();
   bool verify_LL();
   bool empty() const { return formulas.empty(); }
   int  count() const { return (int)formulas.size(); }
   void Add(GFormula* f);
   int  Maker(const char* m) const;
   const GMaker* Maker(int m) const;
   const GSymbol& Cell(const TTableKey& key) const;
   const TAction& Action(TTableKey& key) const;
   bool IsStart(const GSymbol& sym) const;
public:
   GSymbol AddVector(const GSymbolVector& join) { return Vectors().Add(join); }
   const GSymbolVector& Vector(const GSymbol& sym) const { return Vectors().Vector(sym); }
   virtual GVectors& Vectors() { return vectors; }
   virtual const GVectors& Vectors() const { return vectors; }
   void ClearVectors() { Vectors().clear(); }
private:
   GVectors vectors;
public:
   bool Plus(const TFirstFollow& left, const TFirstFollow& right, TFirstFollow& result, int k) { return Vectors().Plus(left, right, result, k); }
   bool make_FIRST_ks(int k = 1);
   bool make_EFF_ks(int k = 1);
   bool make_FOLLOW_ks(int k = 1);
   bool make_SIGMA_ks(int k = 1);
   bool make_FEFS(int mode = 0x00); // 0x01 - SIGMA
   int  look_ahead;
public:
   const GSymbol& GetLLkA(const GSymbol& tab) const;
   TableLLk *TabLLk;
   std::vector<int> references;
public:
   void YACC(TPrinter& printer) const;
   void MACRO(TPrinter& printer) const;
   void PROG(const char* f, int print_mode = 0x00) const;
   void AUTO(TPrinter& printer) const;
   void write(TWriter& printer) const;
   bool read(FILE* file, int print_mode = 0x00);
   void write_LL(TWriter& printer) const;
   void write_LR(TWriter& printer) const;
   bool read(const char* title, int &table_type, int print_mode = 0x00);
   bool read(const char* title, int print_mode = 0x00);
public:
   GFormula* AddFormula(const char* title);
   GFormula* FindFormula(const char* title) { return formulas.Find(title); }
   void AddProduce(const GSymbol &sym);
   void AddProduce();
   void AddProduce(const GSymbol &sym, int count, const int I[][5]);
   void AddProduce(int count, const int I[][5]);
   void AddItem(const GSymbol &sym);
   void AddItems(int count, const int I[][5]);
   void AddAction(const TTableKey& key, const TAction& action);
   void AddActions(int count, const int A[][16]);
   void AddCell(const TTableKey& key, const GSymbol& cell);
   void AddCells(int count, const int C[][15]);
   void AddVector(int count, const int I[][5]);
public:
   TFirst & Eff(const GSymbol& key) { return (TFirst&)EFFs.at(key); }
   TFirst & First(const GSymbol& key) { return (TFirst&)FIRSTs.at(key); }
   TFollow& Follow(const GSymbol& key) { return (TFollow&)FOLLOWs.at(key); }
   const TFirst & First(const GSymbol& key) const { return (const TFirst&)FIRSTs.at(key); }
   const TFollow& Follow(const GSymbol& key) const { return (const TFollow&)FOLLOWs.at(key); }
   bool Split(GSymbolSet& main, GSymbolSet& half) const;
public:
   std::vector<int> used;
public:
   T_Grammar         type;
   const char*       prefix;
   const char*       file; // print
public:
   void output(TPrinter& printer) const;
   void print(TPrinter& printer) const;
   TGrammar* prepare(TPrinter& printer) const;
public:
   GFormulaTable     formulas;
   std::vector<GSymbol> produces;
   TNameTable*       names;
   TGrammarBuilder*  builder;
   GFormula*         root;
   const GMakerTable*makers;
   TLexemeSet        lexemes;
   TTableMap         Mtable;
   LRTableMap        LRtable;
   int               option;
public:
   TFirstFollowMap   FIRSTs, FIRSTsP, EFFs;
   TFirstFollowMap   FOLLOWs;
   TLangFirstMap     SIGMAs;
};

class GSymbolSetMap : public std::map<GSymbol, GSymbolSet> {
public:
   bool Have(const GSymbol& A) const { return (find(A) != end()); }
   bool Have(const GSymbol& A, const GSymbol& B) const { return Get(A,B); }
   bool Add(const GSymbol& A, const GSymbol& B);
   bool Get(const GSymbol& A, const GSymbol& B) const;
   GSymbolSet& Get(const GSymbol& A);
   int  Count(const GSymbol& A) const;
   int  count() const { return (int)size(); }
};

class TDerivation : public GSymbolSetMap {
public:
   TDerivation(TGrammar* g) :GSymbolSetMap(), grammar(g) {}
   void Make(const GSymbolSet* filter = NULL);
public:
   void print(TPrinter& printer) const;
public:
   TGrammar* grammar;
};

#define FORMULA_DELETED_CONTINUE(F) if (F->IsDeleted()) continue;

const char* maker_title(int maker);

#endif
