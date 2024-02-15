#ifndef TRN_TABLES_H
#define TRN_TABLES_H

#include "Rules.h"

enum TChangeSymbolMode { chNone = 0x00, chEofToEmpty = 0x01, chEmptyToEof = 0x02, chVerify = 0x80000000 };

class TLXkReference : public std::vector<int>
{
public:
   TLXkReference() {}
   TLXkReference(int s) { resize(s, 0); }
   void Init(int s) { if (s != count()) resize(s, 0); for (int i = 0; i < s; i++) (*this)[i] = i; }
   void Rename(TLXkReference& target) const;
   int  Ref(int i);
   int  Get(int i) const;
   void Set(int i, int j);
   int  Item(int i) const { return (*this)[i]; }
   int  Ref(int i, int j);
   bool Deleted(int i) const { return ((*this)[i] != i); };
   void Delete(int i);
public:
   int count() const { return (int)size(); }
};

class TTableKey
{
public:
   TTableKey() :key(), sym() {}
   TTableKey(const GSymbol& p, const GSymbol& s) :key(p), sym(s) {}
   bool operator <  (const TTableKey& k) const { return (key <  k.key) || (key == k.key) && (sym < k.sym); }
   bool operator == (const TTableKey& k) const { return (key == k.key) && (sym == k.sym); }
   int  cast(const TTableKey& key);
public:
   void write(TWriter& printer) const;
   bool read (FILE *file, const TGrammar* grammar, int print_mode = 0x00);
   void print(TPrinter& printer) const;
public:
   GSymbol key;
   GSymbol sym;
};

class TTableMap : public std::map<const TTableKey, const GSymbol>
{
public:
   TTableMap(const TGrammar* g = NULL) :grammar(g), duplicate(0), warning(0) {}
   bool Add(const TTableKey&, const GSymbol&);
   const GSymbol& Find(const TTableKey&) const;
   const GSymbol& Cell(const TTableKey& key) const;
public:
   int  change(int mode);
   void print(TPrinter& printer) const;
   void write(TWriter& printer) const;
   bool read (const char* title, int print_mode = 0x00);
   bool read (FILE* file, int print_mode = 0x00);
   int  count() const { return (int)size(); }
public:
   const TGrammar* grammar;
   int duplicate, warning;
};

struct TAction
{
   enum T_Type { taNone, taShift, taReduce, taAccept, taGoto, taError, taFi, taProduce, taPop };
public:
   TAction() :type(taNone) {}
   TAction(T_Type t) :type(t) {}
   TAction(T_Type t, const GSymbol& s) :type(t), sym(s) {}
   bool IsNone   () const { return (type == taNone   ); }
   bool IsShift  () const { return (type == taShift  ); }
   bool IsReduce () const { return (type == taReduce ); }
   bool IsAccept () const { return (type == taAccept ); }
   bool IsGoto   () const { return (type == taGoto   ); }
   bool IsError  () const { return (type == taError  ); }
   bool IsFi     () const { return (type == taFi     ); }
   bool IsProduce() const { return (type == taProduce); }
   bool IsPop    () const { return (type == taPop    ); }
   bool operator == (const TAction& a) const { return ((type == a.type) && (sym == a.sym)); }
public:
   int  print(TPrinter& printer) const;
   void write(TWriter& printer) const;
   bool read (FILE *file, const TGrammar* grammar, int print_mode = 0x00);
public:
   T_Type  type;
   GSymbol sym;
public:
   static const TAction none, error, fi;
};

class LRTableMap : public std::map<const TTableKey, TAction>
{
public:
   LRTableMap(TGrammar* g = NULL) :grammar(g), duplicate(0), warning(0) {}
   bool Add(const TTableKey&, const TAction&);
   const TAction& Action(const TTableKey& key) const;
   bool AssociationPriority(const TTableKey& key, const TAction& item, const TAction& old);
   int  GOTO(const TTableMap& join);
   const GProduce& Produce(const GSymbol &sym) const;
   int  Compression();
   bool verify(const TTableMap& go_to) const;
   int  change(int mode);
public:
   int  count() const { return (int)size(); }
   void print(TPrinter& printer) const;
   void write(TWriter& printer) const;
   bool read (const char* title, int print_mode = 0x00);
   bool read (FILE* file, int print_mode = 0x00);
public:
   TGrammar* grammar;
   int  duplicate, warning;
};

// ------------------------------------- FiUnattainable --------------------------------------
// Green(v=2,(7.3.3,7.3.4))
class LRFiTable : public std::map<const GSymbol, TAction>
{
public:
   LRFiTable(TGrammar* g) :grammar(g), deleted(false), step(0) {}
   const TAction& Action(const GSymbol& key) const;
   const TAction& FiAction(const GSymbol& key) const;
   bool AddError(const GSymbol& sym) { return errors.Add(sym); }
   int  FiCompare(const LRFiTable& join, TLXkReference& references) const;
   void FiMerge(const LRFiTable& join);
   bool ChainCompare(const LRFiTable& join, const GSymbol& p, TLXkReference& references) const;
   void ChainMerge(const LRFiTable& join, const GSymbol& p);
   int  DelAction(const GSymbol& key, const TAction& action);
   bool Delete(const GSymbol& U);
public:
   int  count() const { return (int)size(); }
   void print(TPrinter& printer) const;
public:
   bool deleted;
   int  step;
   GSymbolSet  errors;
   TGrammar*   grammar;
};

class LRFiColumn : public std::vector<LRFiTable*>
{
public:
   LRFiColumn(const GSymbol& a, const GSymbol& b) :A(a), B(b) {}
   void Add(LRFiTable* item) { push_back(item); }
public:
   bool Compare() const;
   void Merge();
public:
   GSymbol A, B;
};

class TNextTab;
class LRFiTableMap : public std::map<const GSymbol, LRFiTable>
{
public:
   LRFiTableMap(TGrammar* g) :grammar(g) {}
   bool Make(const LRTableMap& general);
   bool FiUnattainable(int k);
   bool JointSplitting();
public:
   bool ChainRule();
   bool ChainCompare(const GSymbol& T_1, const GSymbol& p, const TTwoSymVector& NEXT);
   void ChainMerge(const GSymbol& T_1, const GSymbol& p, const GSymbol& B, const TTwoSymVector& NEXT);
   void MakeNEXT(const GSymbol& T_1, const GSymbol& p, const GSymbol& B, TTwoSymVector& NEXT) const;
   void MakeColumn(LRFiColumn& column);
   int  DeleteColumn(const GSymbol& D);
public:
   int  DelAction(const GSymbol& key, const TAction& action);
   int  Copy(LRTableMap& general, TTableMap& go_to) const;
   void Copy(LRFiTableMap& target) const;
   void GoToRef();
   void Statistic(int& table_count, int& item_count) const;
public:
   int  count() const { return (int)size(); }
   void print(TPrinter& printer) const;
public:
   TGrammar* grammar;
   TLXkReference references;
};

#endif