#include "stdafx.h"

#include "RSyntax.h"
#include "Maker.h"
#include "GBuilder.h"
#include "LRBuilder.h"

extern int not_find, count_empty, shift_count, reduce_count, goto_count, equ_count;
extern int delete_count, empty_count, add_count;

// Green(v=1,5.1)
// -------------------------------------------------- LL(k) --------------------------------------------------
class TLLkItem
{
public:
   TLLkItem() {}
   TLLkItem(const GSymbol& p, const GSymbol& s) :produce(p), source(s) {}
public:
   GSymbol produce, source;
};

class TableLLk;
class TLLk : public std::map<const GSymbol, TLLkItem>
{
public:
   TLLk(const GSymbol& a, const TFirst& l, TGrammar *g, int t) : A(a), L(l), del(false), table(t), grammar(g) {}
   bool make(TableLLk& owner);
   TLLkItem& Get(const GSymbol& u) { return at(u);  }
   bool Add(const GSymbol& u, const GSymbol& produce, const GSymbol& source);
   int  Compare(const TLLk& join, TLXkReference& references) const;
   void Merge(const TLLk& join);
public:
   void print(TPrinter& printer) const;
   int  count() const { return (int)size(); }
public:
   GSymbol A;
   TFirst  L;
   TGrammar *grammar;
   bool del;
   int table;
};

class TableLLk
{
public:
   TableLLk(TGrammar *g) :grammar(g) {}
   ~TableLLk() { Clear(); }
   const GSymbol Add(const GSymbol& key_A, const TFirst&  key_L);
   TLLk& Get(const GSymbol& tab) { return *vector[tab.table]; }
   int  Compression();
public:
   int  count() const { return (int)vector.size(); }
   void print(TPrinter& printer) const;
   void Clear();
public:
   struct Key {
      Key(const GSymbol* a, const TFirst* l) :A(a), L(l) {}
      bool operator == (const Key& k) const { return (*A == *k.A) && (*L == *k.L); }
      bool operator <  (const Key& k) const { return (*A <  *k.A) || (*A == *k.A) && (*L < *k.L); }
   public:
      const GSymbol* A;
      const TFirst*  L;
   };
   std::map<const Key, const GSymbol> map;
   std::vector<TLLk*> vector;
public:
   TGrammar * grammar;
};

bool TLLk::Add(const GSymbol& u, const GSymbol& produce, const GSymbol& source)
{
   const_iterator ip = find(u);
   if (ip != end()) return false;
   std::pair<const GSymbol&, TLLkItem> item(u, TLLkItem(produce, source));
   insert(item);
   return true;
}

int  TLLk::Compare(const TLLk& join, TLXkReference& references) const
{
   int compare = 0;
   for (std::pair<const GSymbol&, const TLLkItem&> item : (*this)) {
      const_iterator ip = join.find(item.first);
      if (ip == join.end()) continue;
      const TLLkItem& this_item = item.second;
      const TLLkItem& join_item = (*ip).second;
      if (!(this_item.source == join_item.source)) {
         return -1;
      } else {
//         compare++; continue; // LL1 = LLk(1)
      }
      if (this_item.produce == join_item.produce) { compare++; continue; }
      const GSymbolVector& vec_this = grammar->Vector(this_item.produce);
      const GSymbolVector& vec_join = grammar->Vector(join_item.produce);
      for (int i = 0; i < vec_this.count(); i++) {
         const GSymbol& sym_this = vec_this[i];
         if (!sym_this.IsTable()) continue;
         if (sym_this.table == table) continue;
         const GSymbol& sym_join = vec_join[i];
         if (references.Ref(sym_this.table) != references.Ref(sym_join.table)) return -1;
      }
      compare++;
   }
   if ((compare == count()) && (compare == join.count())) return 0; // this == join
   if (compare == join.count()) return 1; // this > join
   if (compare ==      count()) return 2; // this < join
   return compare ? 3 : -1; // this != join
}

void TLLk::Merge(const TLLk& join)
{
   for (std::pair<const GSymbol&, const TLLkItem&> item : join) {
      const_iterator ip = find(item.first);
      if (ip == end()) {
         insert(item);
      }
   }
}

void TLLk::print(TPrinter& printer) const
{
   for (const std::pair<const GSymbol&, const TLLkItem&> item : *this) {
      const GSymbol& u = item.first;
      u.print(printer);
      item.second.produce.print(printer);
      printer.eol();
   }
}

// Green(v=1,p=390,a=5.2)
bool TLLk::make(TableLLk& owner)
{

   const GFormula& formula_A = grammar->Formula(A);
   int k = grammar->look_ahead;
   for (const GProduce& produce : formula_A) {
      TFirst first, U;
      if (!produce.empty() && !produce.IsEmpty()) {
         if (!grammar->FIRSTs.FIRST(produce, first, k)) continue;
      } else {
         first << GSymbol::empty;
      }
      grammar->Vectors().Plus(first, L, U, k);

      GSymbolVector reduce;
      int i = 0;
      while (i < produce.count()) {
         while ((i < produce.count()) && !produce[i].IsFormula()) {
            reduce << produce[i];
            i++; // x0, x1, ... xM
         }
         if ((i < produce.count()) && produce[i].IsFormula()) {
            const GSymbol sym_B = produce[i];
            i++;
            GSymbolVector alpha;
            produce.TailWithoutMaker(i, alpha);
            TFirst first, Y;
            if (!alpha.empty()) {
               if (!grammar->FIRSTs.FIRST(alpha, first, k)) continue;
            } else {
               first << GSymbol::empty;
            }
            grammar->Vectors().Plus(first, L, Y, k);
            const GSymbol B_Y = owner.Add(sym_B, Y);
            reduce << B_Y;
         }
      }
      const GSymbol head = (reduce.empty() || reduce.IsEmpty()) ? GSymbol::empty : grammar->AddVector(reduce);
      for (const GSymbol& u : U) {
         Add(u, head, produce.head);
      }
   }
   return true;
}

const GSymbol TableLLk::Add(const GSymbol& key_A, const TFirst&  key_L)
{
   const Key my_key(&key_A, &key_L);
   std::map<const Key, const GSymbol>::const_iterator ip = map.find(my_key);
   if (ip != map.end()) return (*ip).second;
   TLLk* table = new TLLk(key_A, key_L, grammar, (int)vector.size());
   std::pair<const Key, const GSymbol> item(Key(&table->A, &table->L), GSymbol(GSymbol::gsTable, (int)vector.size()));
   vector.push_back(table);
   map.insert(item);
   return item.second;
}

struct TTwoInt {
   TTwoInt() :one(0), two(0) {}
   TTwoInt(int o, int t) :one(o), two(t) {}
   int one, two;
};

int  TableLLk::Compression()
{
   if (!map.size()) return 0;
   std::vector<TTwoInt> begs_ends;  begs_ends.resize(grammar->count(), TTwoInt());
   std::vector<int>        indexs;     indexs.resize(count());
   TLXkReference references(count());
   GSymbol A_old = vector.front()->A; // S_
   int table_index = 0;
   begs_ends[A_old.formula].one = table_index;
   for (const std::pair<const TableLLk::Key&, const GSymbol&> item : map) {
      indexs[table_index] = item.second.table;
      references[table_index] = table_index;
      const GSymbol& A = *item.first.A;
      if (!(A == A_old)) {
         begs_ends[A_old.formula].two = table_index - 1;
         A_old = A;
         begs_ends[A_old.formula].one = table_index;
      }
      table_index++;
   }
   begs_ends[A_old.formula].two = table_index - 1;
   fprintf(stdout, "\nbegs_ends=%d", (int)begs_ends.size());

   int step = 0;
   int compare_all = 0, merge_all = 0;
   bool cycle;
   do {
      cycle = false;

      int compare_change = 0, merge_change = 0;
      for (const TTwoInt& beg_end : begs_ends) {
         const TLLk& table = *vector[indexs[beg_end.one]];
         int merge_A = 0, compare_A = 0;
         for (int i = beg_end.one; i < beg_end.two; i++) {
            if (references.Deleted(indexs[i])) continue;
            int ref_i = references.Ref(indexs[i]);
            TLLk& table_i = *vector[indexs[i]];
            for (int j = i + 1; j <= beg_end.two; j++) {
               if (references.Deleted(indexs[j])) continue;
               int ref_j = references.Ref(indexs[j]);
               TLLk& table_j = *vector[indexs[j]];
               int merge = table_i.Compare(table_j, references);
               if ((merge < 0) || (merge > 0)) continue; // > 3
               if (merge == 0) { // this == join
                  compare_change++; compare_A++;
               } else if (merge == 1) { // this > join
                  if (ref_i > ref_j) {
                     table_j.Merge(table_i);
                  }
               } else if (merge == 2) { // this < join
                  if (ref_i < ref_j) {
                     table_i.Merge(table_j);
                  }
               } else { // 3 - this != join
                  if (ref_i > ref_j) {
                     table_j.Merge(table_i);
                  } else {
                     table_i.Merge(table_j);
                  }
               }
               cycle = true;
               if (merge != 0) {
                  merge_change++; merge_A++;
               }
               if (references.Ref(ref_i, ref_j) > 0) {
                  TLLk& table_ref_j = *vector[ref_j];
                  table_ref_j.del = true;
               } else {
                  TLLk& table_ref_i = *vector[ref_i];
                  table_ref_i.del = true;
                  break;
               }
            }
         }
//         fprintf(stdout, "  compare=%d, merge=%d", compare_A, merge_A);
      }
      fprintf(stdout, "\ncompare_change=%d, merge_change=%d", compare_change, merge_change);
      compare_all += compare_change; merge_all += merge_change;
      step++;
   } while (cycle);
   printf("\nstep=%d, compare_all=%d, merge_all=%d", step, compare_all, merge_all);

   int old_count = count(), new_count = 0;
   for (int item = 0; item < old_count; item++ ) {
      if (!references.Deleted(item)) new_count++;
   }
   if (old_count) {
      printf("\nCompression: %d%%, %d -> %d\n", ((old_count - new_count) * 100) / old_count, old_count, new_count);
   }

   grammar->references = references;

   return 0;
}

void TableLLk::Clear()
{
   map.clear();
   for (TLLk* item : vector) {
      delete item; item = NULL;
   }
   vector.clear();
}

void TableLLk::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   if (!printer.file_name) {
      fprintf(file, "\n--- TLLk table --- <%d> ---\n", count());
   }
   if (print_mode == 0x00) return;
   GSymbol A_old; A_old.formula = -1;
   for (const std::pair<const TableLLk::Key&, const GSymbol&> item : map) {
      const TLLk& table = *vector[item.second.table];
      if (table.del) continue;
      GSymbol A = *item.first.A;
      if (!(A == A_old)) {
         A_old = A;
      } else {
         A.type = GSymbol::gsNone;
      }
      fprintf(file, "[");
      if (!A.IsNone() || !(print_mode & T_PrintMode::pmNoPrintNone)) {
         A.print(printer);
      } else {
         int len = SYMBOL_PRINT_TITLE_LEN;
         printer.offset(len, false);
      }
      item.second.print(printer); // Table
      const TFirst& L = *item.first.L;
      L.print(printer);

      fprintf(file, "]");
      printer.eol();
      table.print(printer);
      printer.eol();
   }
}

/** /
const GSymbol& TGrammar::GetLLkA(const GSymbol& tab) const
{
   if (TabLLk) {
      return TabLLk->vector[tab.table]->A;
   } else {
      return GSymbol::none;
   }
}
/ **/

// Green(v=1,p=391,a=5.3)
bool TGrammarBuilder::make_LLkTable(int k)
{
   bool ret = true;
   look_ahead = k;
   grammar->look_ahead = k;

   TableLLk TLLks(grammar);

   TFirst L; L << GSymbol::empty;
   TLLk S_e(grammar->root->head, L, grammar, 0);
   TLLks.Add(S_e.A, S_e.L);

   for (GSymbol table(GSymbol::gsTable); table.table < TLLks.count(); table.table++) {
      if ((table.table % 100) == 0) {
         printf("\n%07d,%07d, vector = %4d", table.table, TLLks.count(), grammar->Vectors().count());
      }
      TLLk& table_B_Y = TLLks.Get(table);
      table_B_Y.make(TLLks);
   }
   printf("\n%07d, vector = %4d", TLLks.count(), grammar->Vectors().count());

   if (grammar->option & TGrammar::POption::opCompression) {
      TLLks.Compression();
   }

   for (GSymbol table(GSymbol::gsTable); table.table < TLLks.count(); table.table++) {
      if ((table.table % 100) == 0) {
         printf("\n%07d,%07d", table.table, Mtable.count());
      }
      const TLLk& table_A_L = TLLks.Get(table);
      if (table_A_L.del) continue;
      for (std::pair<const GSymbol&, const TLLkItem&> item : table_A_L) {
         const GSymbol& u = item.first;
         TTableKey key(table, u); key.key.table = table_A_L.table;
         GSymbol cell = item.second.produce; cell.mode = item.second.source.value; // AutoTree
         if (Mtable.Add(key, cell)) {
         }
      }
   }
   printf("\n%07d,%07d", TLLks.count(), Mtable.count());

   printf("\n\nLLkTable: %07d, Cell: %07d", TLLks.count(), Mtable.count());
   if (Mtable.duplicate) printf("\nDuplicate: %d\n", Mtable.duplicate);
   if (Mtable.warning) printf("\nWarning: %d\n", Mtable.warning);

   if (grammar->option & TGrammar::POption::opLLk) {
      grammar->TabLLk = &TLLks;

      char *file_LLk = NULL;
      if (file) file_LLk = get_file_name(file, "LLk");
      TPrinter printer(file_LLk, T_PrintMode::pmNoPrintNone | T_PrintMode::pmPrintItem);
      TLLks.print(printer);
      if (file_LLk) free(file_LLk);

      char *file_LLkTab = NULL;
      if (file) file_LLkTab = get_file_name(file, "LLkTab");
//      Mtable.print(file_LLkTab, T_PrintMode::pmTableLLk | T_PrintMode::pmNoPrintNone | T_PrintMode::pmPrintItem);
      if (file_LLkTab) free(file_LLkTab);

      grammar->TabLLk = NULL;
   }

   return ret;
}

// Red(p=244)
// ------------------------------------------------ TC2A -----------------------------------------------

bool TAmus::Add(const TAmu& mu_)
{
   TAmu mu = mu_; if (mu.mu.empty()) mu.mu << GSymbol::empty;
   iterator ip = find(mu.point);
   if (ip != end()) {
      return ((*ip).second.mu += mu.mu) != 0;
   }
   std::pair<const GSymbol, TAmu> item(mu.point, TAmu(mu.point));
   item.second.mu << mu.mu;
   insert(item);
   return true;
}

const TAmus TAmus::none;

TBTailItem* TBTails::Get(const GSymbol& point)
{
   iterator ip = find(point);
   if (ip == end()) {
      std::pair<const GSymbol, TBTailItem> item(point, TBTailItem());
      item.second.count++;
      insert(item);
      ip = find(point);
      GSymbolVector beta;
      const GProduce& produce = grammar->Produce(point);
      produce.Tail(point, beta); // delta
      if (!beta.empty()) {
         if (grammar->look_ahead) {
            grammar->FIRSTs.FIRST(beta, (*ip).second.delta, grammar->look_ahead);
         } else {
            grammar->FIRSTs.FIRST(beta, (*ip).second.delta);
         }
      } else {
         (*ip).second.delta << GSymbol::empty;
      }
      grammar->Split((*ip).second.delta, (*ip).second.half);
   } else {
      (*ip).second.count++;
   }
   return &(*ip).second;
}

void TBTails::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   int volume = 0, delta = 0, half = 0;
   for (std::pair<const GSymbol&, const TBTailItem&> item : *this) {
      volume += item.second.count; delta += !item.second.delta.empty(); half += !item.second.half.empty();
      fprintf(file, "\n%7d ", item.second.count); item.first.print(printer);
      item.second.print(printer);
   }
   fprintf(file, "\ncount=%d, volume=%d, delta=%d, half=%d\n", (int)size(), volume, delta, half);
}

void TBTailItem::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   printer.eol(); delta.print(printer);
   printer.eol(); half.print(printer);
}

bool Tc2a::Add(const GSymbol& A, const TAmu& mu)
{
   iterator ip = find(A);
   if (ip == end()) {
      std::pair<const GSymbol, TAmus> item(A, TAmus());
      insert(item); ip = find(A);
   }
   int add = (*ip).second.Add(mu);
   return add != 0;
}

const TAmus& Tc2a::Get(const GSymbol& C)
{
   iterator ip = find(C);
   if (ip != end()) return (*ip).second;
   return TAmus::none;
}

Tc2a& TC2A::Get(const GSymbol& C)
{
   iterator ip = find(C);
   if (ip != end()) return (*ip).second;
   std::pair<const GSymbol, Tc2a> item(C, Tc2a());
   insert(item); ip = find(C);
   return (*ip).second;
}

TAmus& TC2A::Get(const GSymbol& C, const GSymbol& A)
{
   Tc2a& c2a = Get(C);
   Tc2a::iterator ip = c2a.find(A);
   if (ip == c2a.end()) {
      std::pair<const GSymbol, TAmus> item(A, TAmus());
      c2a.insert(item); ip = c2a.find(A);
   }
   return (*ip).second;
}

void TC2A::Init()
{
   for (const GFormula* formula : grammar->formulas) {
      Tc2a& c2a_C = Get(formula->head);
      for (const GProduce& produce : *formula) {
         GSymbol A = produce.IsEmpty() ? GSymbol::empty : produce.front();
         const GSymbol point(GSymbol::gsPoint, produce.head.formula, produce.head.produce, 0);
         TAmu mu_C_A(point);
         c2a_C.Add(A, mu_C_A);
#ifdef TC2A_MAKE_QUEUE
         if (A.IsFormula()) {
            Tc2a& c2a_A = Get(A);
            c2a_A.points << point;
            queue.Push(A);
         }
#endif
      }
   }
}

#ifdef TC2A_MAKE_QUEUE
void TC2A::Make(const GSymbol& point, const GSymbol& C)
{
   int modif = 0;
   GSymbol B(GSymbol::gsFormula, point.formula);
   const Tc2a& c2a_C = Get(C);
   TFirst first_B_C;
   if (grammar->look_ahead) {
      grammar->FIRSTs.FirstTail(point, first_B_C, grammar->look_ahead);
   } else {
      grammar->FIRSTs.FirstTail(point, first_B_C);
   }
   for (std::pair<const GSymbol&, const TAmus&> item : c2a_C) {
      const GSymbol& A = item.first;
      const TAmus& mus_C_A = item.second;
      TAmus& mus_B_A = Get(B, A);
      for (std::pair<const GSymbol&, const TAmu&> item : mus_C_A) {
         const TAmu& mu_C_A = item.second;
         TAmu mu_B_A(mu_C_A.point);
         if (grammar->look_ahead) {
            grammar->Vectors().Plus(mu_C_A.mu, first_B_C, mu_B_A.mu, grammar->look_ahead);
         } else {
            mu_B_A.mu.Plus(mu_C_A.mu, first_B_C);
         }
         if (mus_B_A.Add(mu_B_A)) {
            modif++;
         }
      }
   }
   if (modif) {
      queue.Push(B);
      modif_count += modif;
   }
}

void TC2A::Make(const GSymbol& C)
{
   int ret = 0;
   step++; modif_count = 0;
   const Tc2a& c2a_C = Get(C);
   for (const GSymbol point : c2a_C.points) {
      Make(point, C);
   }
}

#else

int TC2A::Make(const GSymbol& B, const GSymbol& C, const GSymbol& point)
{
   int ret = 0;
   const Tc2a& c2a_C = Get(C);
   Tc2a& c2a_B = Get(B);
   TFirst first_B_C;
   if (grammar->look_ahead) {
      grammar->FIRSTs.FirstTail(point, first_B_C, grammar->look_ahead);
   } else {
      grammar->FIRSTs.FirstTail(point, first_B_C);
   }
   for (std::pair<const GSymbol&, const TAmus&> item : c2a_C) {
      const GSymbol& A = item.first;
      const TAmus& mus_C_A = item.second;
      TAmus& mus_B_A = Get(B, A);
      for (std::pair<const GSymbol&, const TAmu&> item : mus_C_A) {
         const TAmu& mu_C_A = item.second;
         TAmu mu_B_A(mu_C_A.point);
         if (grammar->look_ahead) {
            grammar->Vectors().Plus(mu_C_A.mu, first_B_C, mu_B_A.mu, grammar->look_ahead);
         } else {
            mu_B_A.mu.Plus(mu_C_A.mu, first_B_C);
         }
         if (mus_B_A.Add(mu_B_A)) {
            ret++;
            if (c2a_B.step < step) { c2a_B.step = step; modif_count++; }
         }
      }
   }
   return ret;
}

int TC2A::Make()
{
   int ret = 0;
   step++; modif_count = 0;
   for (const GFormula* formula : grammar->formulas) {
      const GSymbol& B = formula->head;
      for (const GProduce& produce : *formula) {
         if (produce.IsEmpty()) continue;
         const GSymbol& C = produce.front();
         if (!C.IsFormula()) continue;
         const Tc2a& c2a_C = Get(C);
         if (c2a_C.step < step - 1) continue;
         const GSymbol point(GSymbol::gsPoint, produce.head.formula, produce.head.produce, 0);
         ret += Make(B, C, point);
      }
   }
   return ret;
}
#endif

void TC2A::Split()
{
   for (std::pair<const GSymbol&, const Tc2a&> item : *this) {
      for (std::pair<const GSymbol&, const TAmus&> tail : item.second) {
         for (std::pair<const GSymbol&, const TAmu&> item_mu : tail.second) {
            const TAmu& amu = item_mu.second;
            const GProduce& produce = grammar->Produce(amu.point);
            amu.produce = produce.head.value;
            grammar->Split(amu.mu, amu.half);
         }
      }
   }
}

void TC2A::Merge()
{
   for (std::pair<const GSymbol&, const Tc2a&> item : *this) {
      for (std::pair<const GSymbol&, const TAmus&> tail : item.second) {
         for (std::pair<const GSymbol&, const TAmu&> item_mu : tail.second) {
            const TAmu& amu = item_mu.second;
            amu.mu << amu.half;
            amu.half.clear();
         }
      }
   }
}

bool TC2A::Verify() const
{
   TPrinter printer(grammar);

   int different = 0;
   for (std::pair<const GSymbol&, const Tc2a&> item : *this) {
      const GSymbol& A = item.first;
      const Tc2a& C_A = item.second;
      const TFirst& eff_A = grammar->Eff(A);
      TFirst first_A;
      for (const GSymbol& sym : eff_A) {
         if (sym.IsVector()) {
            const GSymbolVector& vec = grammar->Vector(sym);
            first_A << vec.front();
         } else {
            first_A << sym;
         }
      }
      if (C_A.terminals != first_A) {
         fprintf(stdout, "\neff != terminals: "); A.print(printer);
         different++;
      }
   }
   if (different) {
      fprintf(stdout, "\nDifferent : %d\n", different);
   }
   return !different;
}

void TC2A::Core()
{
   Init();

#ifdef TC2A_MAKE_QUEUE
   int m_all = 0;
   for (GSymbol C; queue.Pop(C); ) {
      Make(C);
      if ((step % 100) == 0) {
         printf("\n%05d,%05d,%05d", step, (int)queue.size(), modif_count);
      }
      m_all += modif_count;
   }
   printf("\n%05d,%05d\n", step, m_all);

#else
   int i_all = 0, m_all = 0;
   while (int i = Make()) {
      printf("\n%05d,%05d,%05d",step, modif_count, i);
      i_all += i; m_all += modif_count;
   }
   printf("\n%05d,%05d\n", m_all, i_all);
#endif

   // Make Terminals
   iterator ip = begin();
   while (ip != end()) {
      Tc2a& c2a_C = (*ip).second;
      for (std::pair<const GSymbol&, const TAmus&> tail : c2a_C) {
         if (tail.first.IsTerminal()) c2a_C.terminals << tail.first;
      }
      ip++;
   }

   if (grammar->look_ahead) Verify();

}

void TC2A::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   int A_count = 0, T_C_count = 0;
   for (std::pair<const GSymbol&, const Tc2a&> item : *this) {
      A_count += (int)item.second.size();
      for (std::pair<const GSymbol&, const TAmus&> tail : item.second) {
         T_C_count += (int)tail.second.size();
      }
   }
   fprintf(file, "\n--- TC2A table --- <%d> --- <%d> --- <%d> ---\n", (int)size(), A_count, T_C_count);

   for (std::pair<const GSymbol&, const Tc2a&> item : *this) {
      fprintf(file, "\n--- <%d> --- ", (int)item.second.size());
      item.first.print(printer);
      item.second.print(printer);
   }

   point_tails.print(printer);

   printer.eol();
}

void Tc2a::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   fprintf(file, "\nLs:");
   terminals.print(printer);
   fprintf(file, "\nXc:");
   for (std::pair<const GSymbol&, const TAmus&> item : *this) {
      item.first.print(printer);
      fprintf(file, "   ");
   }
   printer.eol();
   for (std::pair<const GSymbol&, const TAmus&> item : *this) {
      item.first.print(printer);
      fprintf(file, " => --- (%d) ---", (int)item.second.size());
      for (std::pair<const GSymbol&, const TAmu&> item_mu : item.second) {
         const TAmu& mu = item_mu.second;
         printer.eol(); mu.point.print(printer); fprintf(file, " "); mu.mu.print(printer);
         printer.eol(); mu.half.print(printer);
      }
      printer.eol();
   }
}

// ---------------------------- make_Table -----------------------------------
// Green(v=2,p=94,7.4.1,a=7.10)
bool TGrammarBuilder::make_SLRkTable(int k) // T_SyntaxMode::smParseLR0
{
   bool ret = true;
   look_ahead = k;

   TLR0Builder LR0_builder(grammar);
   LR0_builder.Stable = &Stable;
   LR0_builder.look_ahead = 0;
   LR0_builder.make_States();

   if (k) {
      TSLRBuilder builder(grammar);
      builder.Stable = &Stable;
      builder.LRtable = &LRtable;
      builder.look_ahead = k;
      builder.GOTOtable = LR0_builder.GOTOtable;

      int invalid = LR0_builder.Stable->ValidSLRk();
      if (invalid) printf("\nInvalid: %d\n", invalid);

      builder.mode |= builder.tmGOTO;
      builder.make_Table(); // go_to

      TablePrint.Copy(*builder.Stable); // print
      GOTOtable = builder.GOTOtable;
   } else {
      LR0_builder.LRtable = &LRtable;
      LR0_builder.mode |= LR0_builder.tmGOTO;
      LR0_builder.make_Table(); // go_to

      GOTOtable = LR0_builder.GOTOtable;
   }
   return ret;
}

bool TGrammarBuilder::make_LRkTable(int k) // T_SyntaxMode::smParseLR1
{
   bool ret = true;
   look_ahead = k;
#ifdef LRK_TABLE_BUILDER
   TLRTabBuilder builder(grammar);
#else
   TLRBuilder builder(grammar);
#endif
   builder.Stable = &Stable;
   builder.LRtable = &LRtable;
   builder.look_ahead = k;

   builder.make_States();

   builder.mode = A_LRBuilder::tmGOTO;
   builder.make_Table(); // go_to

/*
   TNextTab NEXTs(grammar);
   Stable.make_NEXTs(builder.GOTOtable, NEXTs);
   char* file_next = get_file_name(file, "next");
   TPrinter printer(file_next, 0x0200);
   NEXTs.print(printer);
   free(file_next);

   TNextTab PREDs(grammar);

   for (const std::pair<const MTableKey&, const GSymbolSet&> item : NEXTs) {
      for (const GSymbol to : item.second) {
         MTableKey key_pred(to, item.first.sym);
         PREDs.Add(key_pred, item.first.produce);
      }
   }

   char* file_pred = get_file_name(file, "pred");
   PREDs.print(file_pred, 0x0200);
   free(file_pred);
*/

   GOTOtable = builder.GOTOtable;
   TablePrint.Copy(Stable); // print

#ifdef LRK_TABLE_BUILDER
   builder.Stable->Expansion(builder.table, TablePrint);
   int invalid = TablePrint.ValidLRk();
   if (invalid) printf("\nInvalid: %d\n", invalid);
#else
   int invalid = builder.Stable->ValidLRk();
   if (invalid) printf("\nInvalid: %d\n", invalid);
#endif

   return ret;
}

// Red(p=244)
bool TGrammarBuilder::make_LR0Core() // T_SyntaxMode::smParseLR0_Core
{
   bool ret = true;

   TLR0CoreBuilder builder(grammar);
   builder.Stable = &Stable;
   builder.LRtable = &LRtable;
   builder.look_ahead = 0;
   builder.mode = builder.tmLR0 | builder.tmFormulaAndLexeme;
   builder.make_States();

   int before = builder.LRtable->count();
   builder.LRtable->GOTO(builder.GOTOtable);
   goto_count += (builder.LRtable->count() - before);

   builder.mode |= builder.tmGOTO;
   builder.make_Table();

   GOTOtable = builder.GOTOtable;

   return ret;
}

bool TGrammarBuilder::make_LRkCore(int k) // T_SyntaxMode::smParseLR1_Core
{
   bool ret = true;
   look_ahead = k;
#ifdef CORE_TABLE_BUILDER
   TLRkCoreTabBuilder builder(grammar);
#else
   TLRkCoreBuilder builder(grammar);
#endif
   builder.Stable = &Stable;
   builder.LRtable = &LRtable;
   builder.look_ahead = k;
   builder.mode = builder.tmFormulaAndLexeme;
   builder.make_States();
   builder.CtoAa.Merge();

   printf("\n!add=%d, %d, %d", builder.add_count, builder.empty_count, builder.count_empty);
   printf("\ntrue_count=%d, false_count=%d, closure_count=%d\n", builder.true_count, builder.false_count, builder.Added.Current());

   int before = builder.LRtable->count();
   builder.LRtable->GOTO(builder.GOTOtable);
   goto_count += (builder.LRtable->count() - before);

   builder.mode |= builder.tmGOTO;
   builder.make_Table();
   TPrinter printer;
   LRtable.print(printer);

   GOTOtable = builder.GOTOtable;

   if (builder.CtoAa.size() && (grammar->option & TGrammar::POption::opC2A)) {
      char* file_C2A = get_file_name(grammar->file, "C2A");
      TPrinter printer(file_C2A, T_PrintMode::pmCompactGroup | T_PrintMode::pmSortMode | T_PrintMode::pmCompact);
      builder.CtoAa.print(printer);
      free(file_C2A);
   }

#ifdef CORE_TABLE_BUILDER
   builder.Stable->Expansion(builder.table, TablePrint);
//   builder.table.print(stdout, grammar, 0x00);
#endif

   return ret;
}

bool TGrammarBuilder::make_LALRkCore(int k) // T_SyntaxMode::smParseLALR_Core
{
   bool ret = true;
   look_ahead = k;

#ifdef CORE_TABLE_BUILDER
   TLALRkCoreTabBuilder builder(grammar);
#else
   TLALRkCoreBuilder builder(grammar);
#endif
   builder.Stable = &LALRStable;
   builder.LALRStable = &LALRStable;
   builder.LALRStable->yes_queue = true;
   builder.LRtable = &LRtable;
   builder.look_ahead = k;
   builder.mode = builder.tmFormulaAndLexeme;
   builder.make_States();
   builder.CtoAa.Merge();

   int before = builder.LRtable->count();
   builder.LRtable->GOTO(builder.GOTOtable);
   goto_count += (builder.LRtable->count() - before);

   builder.mode |= builder.tmGOTO;
   builder.make_Table();

   TPrinter printer;
   LRtable.print(printer);

   if (builder.CtoAa.size() && (grammar->option & TGrammar::POption::opC2A)) {
      char* file_C2A = get_file_name(grammar->file, "C2A");
      TPrinter printer(file_C2A, T_PrintMode::pmCompactGroup | T_PrintMode::pmSortMode | T_PrintMode::pmCompact);
      builder.CtoAa.print(printer);
      free(file_C2A);
   }

   Stable.Copy(*builder.LALRStable);
   GOTOtable = builder.GOTOtable;

#ifdef CORE_TABLE_BUILDER
   builder.Stable->Expansion(builder.table, TablePrint);
   int invalid = TablePrint.ValidLRk();
   if (invalid) printf("\nInvalid: %d\n", invalid);
//   builder.table.print(stdout, grammar, 0x00);
#else
   int invalid = builder.Stable->ValidLRk();
   if (invalid) printf("\nInvalid: %d\n", invalid);
#endif

   return ret;
}

bool TGrammarBuilder::make_LALRk_FullTable(A_Syntax::T_SyntaxMode syntax_mode, int k) // T_SyntaxMode::smParseLALR_Tab, T_SyntaxMode::smParseLALR_Full
{
   bool ret = true;
   look_ahead = k;

#ifdef LRK_TABLE_BUILDER
   TLRTabBuilder LRk_builder(grammar);
#else
   TLRBuilder LRk_builder(grammar);
#endif
   LRk_builder.Stable = &Stable;
   LRk_builder.look_ahead = k;

   LRk_builder.make_States(); // Stable, GOTOtable

   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable.count(); situation.situation++) {
      const TParaSet* item = Stable.Get(situation);
      TParaSet* core = item->Core();
      COREtable.Add(core, situation.situation);
   }
   const TCoreArr& core_arr = COREtable.Core();

   std::vector<int> move; move.resize(Stable.count(), -1);
   GSymbol situation(GSymbol::gsSituation);

   for (const TCoreArrItem &core : core_arr) {
      TParaSet *I = new TParaSet(grammar);
      for (int item : core) {
         situation.situation = item;
         (*I) << *Stable.Get(situation); move[situation.situation] = LALRStable.count();
      }
      LALRStable.Add(I);
   }

   for (int i = 0; i < (int)move.size(); i++) {
      if (move[i] < 0) {
         situation.situation = i; move[situation.situation] = LALRStable.count();
         LALRStable.Add(new TParaSet(grammar, *Stable.Get(situation)));
      }
   }

#ifdef LRK_TABLE_BUILDER
   TLRTabBuilder LALRk_builder(grammar);
   LALRk_builder.table.Copy(LRk_builder.table);
#else
   TLRBuilder LALRk_builder(grammar);
#endif
   LALRk_builder.Stable = &LALRStable;
   LALRk_builder.LRtable = &LRtable;
   LALRk_builder.look_ahead = k;

   if (syntax_mode == A_Syntax::smParseLALR_Full) {
      LALRk_builder.mode = A_LRBuilder::tmMakeGOTO;
      ret = LALRk_builder.make_Table(); // make_go_to
   } else {
      TTableMap  old_GOTOtable(LRk_builder.GOTOtable);
      LALRk_builder.GOTOtable.clear();
      for (const std::pair<const TTableKey&, const GSymbol&> item : old_GOTOtable) {
         TTableKey key = item.first; key.key.situation = move[key.key.situation];
         GSymbol go_to = item.second; go_to.situation = move[go_to.situation];
         LALRk_builder.GOTOtable.Add(key, go_to);
      }

      LALRk_builder.mode = A_LRBuilder::tmGOTO;
      ret = LALRk_builder.make_Table(); // goto
   }

   GOTOtable = LALRk_builder.GOTOtable;

   Stable.Clear();
#ifdef LRK_TABLE_BUILDER
   LALRStable.Expansion(LALRk_builder.table, Stable);
#else
   Stable.Copy(LALRStable); // print
#endif
   LALRStable.Clear();
   TPrinter printer;
   LRtable.print(printer);

   ret = LRtable.verify(GOTOtable);

   return ret;
}

bool TGrammarBuilder::make_LALRkTable(int k) // T_SyntaxMode::smParseLALR
{
   TLR0Builder LR0_builder(grammar);
   LR0_builder.Stable = &Stable;
   LR0_builder.look_ahead = 0;
   bool ret =  LR0_builder.make_States(); // Stable, GOTOtable

   Stable.Basic();
   Stable.print();

   true_count = 0; false_count = 0;

   {
      TFirstFollow FIRST(&grammar->FIRSTs); FIRST += GSymbol::sharp;
      grammar->FIRSTs.Add(GSymbol::sharp, FIRST);
      grammar->EFFs.Add(GSymbol::sharp, FIRST);
   }

   // Red(p=245,a=4.12)
   bool start = true;
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < LR0_builder.Stable->count(); situation.situation++) {
      const TParaSet *I = LR0_builder.Stable->Get(situation);
      for (const TPara& para : *I) {
         TLookAhead::TElement key(situation, para);
         LookAhead.Add(key);
         if (start) { start = false; (*LookAhead.map.begin()).second.symbols.Add(GSymbol::empty); }
      }
   }

//   LookAhead.print("1.look", 0x04);

   TSituationMap  LALRStable;
   TLRBuilder LRk_builder(grammar);
   LRk_builder.look_ahead = k;
   LRk_builder.Stable = &LALRStable;
   LRk_builder.LRtable = &LRtable;
   LRk_builder.Init();

   int step = 0, para_count = 0, sym_count = 0;
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < LR0_builder.Stable->count(); situation.situation++) {
      const TParaSet *I = LR0_builder.Stable->Get(situation);
      if ((step % 100) == 0) {
         printf("\n%05d,%05d,%05d", step, para_count, sym_count);
      }
      step++;
      for (const TPara& A_ab : *I) {
         TLookAhead::TElement key_core(situation, A_ab); 
         TLookAhead::TItem& item_from = LookAhead.Get(key_core);

         TPara sharp_para((GSymbol)A_ab, GSymbol::sharp);
         TParaSet P(grammar, sharp_para);
         TParaSet* J = LRk_builder.CLOSURE(P);
         for (const TPara& B_gXd : *J) {
            const GProduce& produce = grammar->Produce(B_gXd);
            if ((B_gXd.point < produce.count()) && !produce.IsEmpty()) {
               const GSymbol& X = produce[B_gXd.point];
               const TTableKey key_goto(situation, X);
               const GSymbol& goto_X = LR0_builder.GOTOtable.Find(key_goto);
               TPara to_para(B_gXd); to_para.point++; to_para.sym = GSymbol::none;
               const TLookAhead::TElement key_to(goto_X, to_para);
               TLookAhead::TItem& to_item = LookAhead.Get(key_to);
               GSymbolSet& to_symbols = to_item.symbols;
               TLookAhead::TElement expansion(goto_X, to_para);
               if (B_gXd.sym == GSymbol::sharp) {
                  item_from.Add(expansion);
               } else {
                  if (B_gXd.sym.IsVector()) {
                     const GSymbolVector& vec = grammar->Vector(B_gXd.sym);
                     GSymbolVector vector;
                     bool yes_sharp = false;
                     for (const GSymbol& sym : vec) {
                        if (sym == GSymbol::sharp) { yes_sharp = true; continue; }
                        vector << sym;
                     }
                     if (yes_sharp) {
                        expansion.para.sym = grammar->AddVector(vector); // B_gXd.sym - sharp
                        item_from.Add(expansion);
                     } else {
                        to_symbols.Add(B_gXd.sym);
                     }
                  } else {
                     to_symbols.Add(B_gXd.sym);
                  }
               }
               sym_count++;
            }
         }
         delete J;
         para_count++;
      }
   }
   printf("\n%05d,%05d,%05d\n", step, para_count, sym_count);
   printf("\ntrue_count=%d, false_count=%d, closure_count=%d\n", LRk_builder.true_count, LRk_builder.false_count, LRk_builder.Added.Current());

 //  LookAhead.print("2.look", 0x04);

   // Red(p=246,a=4.13)
   T_SetQueue<TLookAhead::TElement> queue;
   for (std::pair<const TLookAhead::TElement&, const TLookAhead::TItem&> item : LookAhead.map) {
      if (item.second.expansions.empty()) continue;
      queue.Push(item.first);
   }

   step = 0;
   for (TLookAhead::TElement queue_item; queue.Pop(queue_item); ) {
      int all_work = 0;
      TLookAhead::TItem& from_item = LookAhead.Get(queue_item);
      const GSymbolSet&  from_symbols = from_item.symbols;
      for (TLookAhead::TElement& expansion : from_item.expansions) {
         TLookAhead::TElement key_to(expansion); key_to.para.sym = GSymbol::none;
         TLookAhead::TItem& to_item = LookAhead.Get(key_to);
         GSymbolSet& to_symbols = to_item.symbols;
         int work = 0;
         if (!expansion.para.sym.IsNone()) { // B_gXd.sym - sharp
            const GSymbolVector& vec_u = grammar->Vector(expansion.para.sym);
            bool yes_empty = false;
            for (const GSymbol sym : from_symbols) {
               if (sym.IsEmpty()) {
                  yes_empty = true;
                  continue;
               }
               const GSymbolVector& vec_b = grammar->Vector(sym);
               GSymbolVector vector;
               int len = 0;
               for (const GSymbol& sym : vec_u) {
                  if (len++ >= k) break;
                  vector << sym;
               }
               for (const GSymbol& sym : vec_b) {
                  if (len++ >= k) break;
                  vector << sym;
               }
               const GSymbol header = grammar->AddVector(vector);
               if (to_symbols.Add(header)) work++;
            }
            if (yes_empty) {
               if (to_symbols.Add(expansion.para.sym)) work++;
            }
         } else {
            for (const GSymbol sym : from_symbols) {
               if (to_symbols.Add(sym)) work++;
            }
         }
         if (work) {
            queue.Push(key_to);
         }
         all_work += work;
      }
      if ((step % 100) == 0) {
         printf("\n%05d,%05d", step, all_work);
      }
      step++;
   }
   printf("\n%05d\n", step);

   step = 0;
   para_count = 0;
   LRk_builder.true_count = 0; LRk_builder.false_count = 0;
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < LR0_builder.Stable->count(); situation.situation++) {
      if ((step % 100) == 0) {
         printf("\n%05d,%05d", step, para_count);
      }
      step++;
      const TParaSet *I = LR0_builder.Stable->Get(situation);
      TParaSet LALR_I(grammar);
      for (const TPara& A_ab : *I) {
         TLookAhead::TElement key_core(situation, A_ab);
         const TLookAhead::TItem& item = LookAhead.Get(key_core);
         const GSymbolSet& symbols = item.symbols;
         for (const GSymbol sym : symbols) {
            TPara LALR_para((const GSymbol)A_ab, sym);
            LALR_I.Add(LALR_para);
         }
         para_count++;
      }

      TParaSet* I_X = LRk_builder.CLOSURE(LALR_I);
      TParaSet *I_X_P = new TParaSet(grammar, LALR_I); TablePrint.Add(I_X_P);
      int before_count = LALRStable.count();
      const GSymbol go_to = LALRStable.Add(I_X);
      if (LALRStable.count() == before_count) {
         delete I_X;
      }
   }
   printf("\n%05d,%05d", step, para_count);
   printf("\ntrue_count=%d, false_count=%d, closure_count=%d", LRk_builder.true_count, LRk_builder.false_count, LRk_builder.Added.Current());

   LALRStable.print();

   LRk_builder.GOTOtable = LR0_builder.GOTOtable;
   LRk_builder.mode |= A_LRBuilder::tmGOTO;
   ret = LRk_builder.make_Table(); // go_to
   GOTOtable = LRk_builder.GOTOtable;

   TPrinter printer;
   LRtable.print(printer);
   Stable.Clear();
   Stable.Copy(*LRk_builder.Stable); // print
   LALRStable.Clear();

   ret = LRtable.verify(GOTOtable);

   return ret;
}

// ------------------------------ GrammarSplitting -------------------------------
// Green(v=2,7.4.3)
// Green(v=2,p=104,a=7.12)
#define FORMULA_GROUP_LR_
#define FORMULA_GROUP_ETF
bool TGrammarBuilder::make_GrammarSplitting(int k)
{
   bool ret = true;
   look_ahead = k;
   if (!grammar->root) return false;
   grammar->make_start();

   TGrammarGroup group(grammar);
   group.AddGrammar(grammar->root->head);
#if defined(FORMULA_GROUP_LR)
   if (GFormula* part = grammar->FindFormula("Expressions")) { group.AddGrammar(part->head); }
   if (GFormula* part = grammar->FindFormula("Assign")) { group.AddGrammar(part->head); }
//   if (GFormula* part = grammar->FindFormula("ExpressionValue")) { group.AddGrammar(part->head); }
//   if (GFormula* part = grammar->FindFormula("ExpressionExpression")) { group.AddGrammar(part->head); }
//   if (GFormula* part = grammar->FindFormula("ExpressionCondition")) { group.AddGrammar(part->head); }
//   if (GFormula* part = grammar->FindFormula("ExpressionNone")) { group.AddGrammar(part->head); }
//   if (GFormula* part = grammar->FindFormula("ExpressionValueList")) { group.AddGrammar(part->head); }
//   if (GFormula* part = grammar->FindFormula("DefFunc")) { group.AddGrammar(part->head); }
//   if (GFormula* part = grammar->FindFormula("Define")) { group.AddGrammar(part->head); }
//   if (GFormula* part = grammar->FindFormula("DefItem")) { group.AddGrammar(part->head); }
//   if (GFormula* part = grammar->FindFormula("DefType")) { group.AddGrammar(part->head); }
   if (GFormula* part = grammar->FindFormula("DefFAV")) { group.AddGrammar(part->head); }
   if (GFormula* part = grammar->FindFormula("Ranges")) { group.AddGrammar(part->head); }
#elif defined(FORMULA_GROUP_ETF)
//   if (GFormula* part = grammar->FindFormula("E")) { group.AddGrammar(part->head); }
   if (GFormula* part = grammar->FindFormula("T")) { group.AddGrammar(part->head); }
   if (GFormula* part = grammar->FindFormula("F")) { group.AddGrammar(part->head); }
#else
   for (GFormula* formula : grammar->formulas) {
      if (!formula->IsEmpty() && !grammar->IsStart(formula->head)) {
         group.AddGrammar(formula->head);
      }
   }
#endif
   TGrammarGroup::iterator ig;

   ig = group.begin();
   if (ig == group.end()) return false;

// Green(v=2,p=102,a=7.11)
   while (ig != group.end()) {
      TGrammar& item_grammar = *(*ig).second;
      for (GFormula* formula : item_grammar.formulas) {
         for (GProduce& produce : (*formula)) {
            for (GSymbol& sym : produce) {
               group.FormulaToTerminal(sym);
            }
         }
      }
      ig++;
   }

   ig = group.begin();
   while (ig != group.end()) {
      const GSymbol& sym = (*ig).first;
      TGrammarGroupItem& item_grammar = *(*ig).second;
      TPrinter printer(&item_grammar);
      sym.print(printer);
      item_grammar.NoEmptyLanguage();
      item_grammar.UnacceptableSymbols();

      if (grammar->option & TGrammar::opSplittingAddition) {
         GSymbol S_(item_grammar.S_);
         GProduce& produce = item_grammar.formulas[S_.formula]->front();
         if ((S_.point < produce.count()) && !grammar->IsStart(S_)) {
            GSymbol& sym_B = produce[S_.point];
            if (sym_B.IsTerminal() && (sym_B.group == T_Lexeme::grGrammar)) {
               sym_B.type = GSymbol::gsFormula; sym_B.formula = sym_B.lexeme_type; sym_B.produce = 0;
            }
         }
      }

      item_grammar.make_FIRST_ks(look_ahead);
      item_grammar.make_EFF_ks(look_ahead);
      item_grammar.make_FOLLOW_ks(look_ahead);

      ig++;
   }

   if (grammar->option & TGrammar::opSplittingAddition) {
      grammar->make_FIRST_ks(look_ahead);
      grammar->make_EFF_ks(look_ahead);
      grammar->make_FOLLOW_ks(look_ahead);
   }

// Green(v=2,p=104,a=7.12)
   ig = group.begin();
   while (ig != group.end()) {
      TGrammarGroupItem& item_grammar = *(*ig).second;
      TSituationMap& Stable = item_grammar.Stable;
      TGGBuilder builder(&group, &item_grammar);
      builder.Stable = &Stable;
      builder.look_ahead = k;

      builder.make_States();

      item_grammar.GOTOtable = builder.GOTOtable;

      int invalid = Stable.ValidLRk();
      if (invalid) printf("\nInvalid: %d\n", invalid);

      ig++;
   }

// Green(v=2,p=106,a=7.13)
   TGGroupBuilder builder_group(&group);
   builder_group.Stable = &TablePrint;
   builder_group.look_ahead = k;
   builder_group.mode = builder_group.tmFormulaAndLexeme;

   builder_group.make_States();

   group.Disclosure(*builder_group.Stable, Stable);

   int invalid = Stable.ValidLRk();
   if (invalid) printf("\nInvalid: %d\n", invalid);

   if (grammar->option & TGrammar::opSplittingAddition) {
      TSLRBuilder builder(grammar);
      builder.Stable = &Stable;
      builder.LRtable = &LRtable;
      builder.mode = builder.tmGOTO;
      builder.look_ahead = k;
      builder.GOTOtable = builder_group.GOTOtable;

      builder.make_Table();
   } else {
      TLRBuilder builder(grammar);
      builder.Stable = &Stable;
      builder.LRtable = &LRtable;
      builder.mode = builder.tmGOTO;
      builder.look_ahead = k;
      builder.GOTOtable = builder_group.GOTOtable;

      builder.make_Table();
   }

   GOTOtable = builder_group.GOTOtable;

   char *file_grammar = get_file_name(file, "group");
   TPrinter printer(file_grammar, T_PrintMode::pmProduceHead | T_PrintMode::pmPrintItem); // T_PrintMode::pmGrammar | T_PrintMode::pmCompactGroup);
   group.print(printer);

   return ret;
}

bool TGrammarBuilder::make_FiUnattainable(int k)
{
   look_ahead = k;

   LRFiTableMap LRFiTable(grammar);
   LRFiTable.Make(LRtable);
/*
   char* file_next = get_file_name(file, "next");
   NEXTs.print(file_next, 0x0200);
   free(file_next);
*/

//      LRFiTable.references.Init(LRFiTable.count());
   LRFiTable.FiUnattainable(k);

   if (grammar->option & TGrammar::opChainRule) {
      LRFiTable.ChainRule();
//      LRFiTable.JointSplitting();

      int table_count, item_count;
      LRFiTable.Statistic(table_count, item_count);
      printf("\n%05d,%05d\n", table_count, item_count);
   }

   if (grammar->option & TGrammar::opFiUnattainable) {
      LRFiTable.JointSplitting();
//      LRFiTable.ChainRule();

      int table_count, item_count;
      LRFiTable.Statistic(table_count, item_count);
      printf("\n%05d,%05d\n", table_count, item_count);
   }

   LRFiTable.Copy(LRtable,GOTOtable);

   if (grammar->option & TGrammar::POption::opFiUn) {
      char* file_Fi = get_file_name(grammar->file, "Fi");
      TPrinter printer(file_Fi, T_PrintMode::pmNoPrintNone | T_PrintMode::pmMultiLine);
      LRFiTable.print(printer);
      free(file_Fi);
   }
/*
   LRFiTableMap NewFiTable(grammar);
   LRFiTable.Copy(NewFiTable);
   if (grammar->option & TGrammar::POption::opFiUn) {
      char* file_Fi = get_file_name(grammar->file, "NewFi");
      NewFiTable.print(file_Fi, T_PrintMode::pmNoPrintNone | T_PrintMode::pmMultiLine);
      free(file_Fi);
   }
*/
   return true;
}
