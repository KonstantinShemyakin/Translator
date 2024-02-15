#include "stdafx.h"

#include "RSyntax.h"
#include "Maker.h"
#include "GBuilder.h"

bool TPara::operator == (const TPara& p) const 
{ 
   return ((const GSymbol&)(*this) == (const GSymbol&)p) && (sym == p.sym); 
}
bool TPara::operator <  (const TPara& p) const
{
   return ((const GSymbol&)(*this) < (const GSymbol&)p) || ((const GSymbol&)(*this) == (const GSymbol&)p) && (sym < p.sym); 
}
int  TPara::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   bool compact = (print_mode & T_PrintMode::pmCompactGroup) != 0, simple = (print_mode & T_PrintMode::pmSimplePara) != 0;
   if (!file) file = stdout;
   int len = 0;
   if (!simple) {
      if (sym.IsNone()) {
         fprintf(file, "(%1d)",point); 
      } else {
         fprintf(file, "(%1d,",point); sym.print(printer); fprintf(file, ")");
      }
      if (IsPara()) {
         const GSymbol p(GSymbol::gsProduce, formula, produce);
         const GProduce& pr = grammar->Produce(p);
         TPrinter printer_produce(printer, print_mode | (compact ? T_PrintMode::pmCompact : T_PrintMode::pmNone));
         pr.print(printer_produce, point);
      } else {
         len += ((const GSymbol&)(*this)).print(printer);
      }
   } else {
      len += ((const GSymbol&)(*this)).print(printer);
      if (!sym.IsNone()) {
         fprintf(file, ","); len += 1;
         len += sym.print(printer);
      }
   }
   return len;
}

void TPara::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   GSymbol::write(printer);
   if (!sym.IsNone()) { 
      fprintf(file, ","); sym.write(printer);
   }
   fprintf(file, ";");
}

TParaSet::TParaSet(const TGrammar* g, const TParaSet& I) :grammar(g), mode(0) 
{
   for (const TPara& para : I) {
      Add(para);
   }
}

int TParaSet::operator += (const TPara& s)
{
   int ret = Add(s);
   return ret;
}

int TParaSet::operator += (const TParaSet& m)
{
   int ret = 0;
   for (const TPara& item : m) {
      if (item.IsEmpty()) continue;
      if (Add(item)) ret++;
   }
   return ret;
}

TParaSet TParaSet::Empty(NULL);

bool TParaSet::Add(const TPara& sym)
{ 
   const_iterator ip = find(sym); 
   if (ip != end()) return false;
   insert(sym);
   return true; 
}

bool TParaSet::Have(const TPara& sym) const
{ 
   const_iterator ip = find(sym); 
   return (ip != end());
}

bool TParaSet::ValidLRk() const
{
   if (size() == 1) return true;
   std::vector<TFirst> firsts; firsts.resize(size());
   bool ended = false;
   for (const TPara& para : (*this)) {
      const GProduce& produce = grammar->Produce(para);
      if ((para.point == produce.count()) || produce.IsEmpty()) {
         ended = true; break;
      }
   }
   if (!ended) return true;

   int i = 0;
   for (const TPara& para : (*this)) {
      const GProduce& produce = grammar->Produce(para);
      TFirst& eff_beta2_v = firsts[i];
      if ((para.point < produce.count()) && !produce.IsEmpty()) {
         GSymbolVector beta2_v;
         produce.SymAndTail(para, beta2_v);
         if (para.sym.IsVector()) {
            beta2_v << grammar->Vector(para.sym);
         } else {
            beta2_v << para.sym;
         }
         grammar->EFFs.EFF(beta2_v, eff_beta2_v, grammar->look_ahead);
      } else {
         eff_beta2_v << para.sym;
      }
      i++;
   }

   for (const TPara& para_one : (*this)) {
      const GProduce& produce_one = grammar->Produce(para_one);
      if (produce_one.head.mode & GSymbol::Warning) continue;
      if ((para_one.point < produce_one.count()) && !produce_one.IsEmpty()) continue;
      int j = 0;
      for (const TPara& para_two : (*this)) {
         if (!(para_one == para_two) && !produce_one.IsEmpty()) {
            const TFirst& eff_beta2_v = firsts[j];
            if (eff_beta2_v.Have(para_one.sym)) {
               TPrinter printer(grammar);
               fprintf(stdout, "\nA: "); para_one.print(printer); fprintf(stdout, " B: "); para_two.print(printer);
               return false;
            }
         }
         j++;
      }
   }
   return true;
}

bool TParaSet::ValidSLRk() const
{
   if (size() == 1) return true;
   std::vector<TFirst> firsts; firsts.resize(size());
   bool ended = false;
   for (const TPara& para : (*this)) {
      const GProduce& produce = grammar->Produce(para);
      if ((para.point == produce.count()) || produce.IsEmpty()) {
         ended = true; break;
      }
   }
   if (!ended) return true;

   int i = 0;
   for (const TPara& para : (*this)) {
      const GProduce& produce = grammar->Produce(para);
      TFirst& eff_beta_follow = firsts[i];
      if ((para.point < produce.count()) && !produce.IsEmpty()) {
         GSymbolVector beta;
         produce.SymAndTail(para, beta);
         const GSymbol A = GSymbol(GSymbol::gsFormula, para.formula);
         const TFollow& follow_A = (const TFollow&)grammar->Follow(A);
         for (const GSymbol& item : follow_A) {
            GSymbolVector beta_follow(beta);
            if (item.IsVector()) {
               beta_follow << grammar->Vector(item);
            } else if (!item.IsEmpty() && !item.IsEof()) {
               beta_follow << item;
            }
            TFirst eff_beta_item;
            grammar->EFFs.EFF(beta_follow, eff_beta_item, grammar->look_ahead);
            eff_beta_follow << eff_beta_item;
         }
      }
      i++;
   }

   for (const TPara& para_B : (*this)) {
      const GProduce& produce_B = grammar->Produce(para_B);
      if ((para_B.point < produce_B.count()) || produce_B.IsEmpty()) continue;
      const GSymbol B = GSymbol(GSymbol::gsFormula, para_B.formula);
      int j = 0;
      for (const TPara& para_A : (*this)) {
         if (!(para_A == para_B)) {
            const GSymbol A = GSymbol(GSymbol::gsFormula, para_A.formula);
            const GProduce& produce_A = grammar->Produce(para_A);
            TFirstFollow multi;
            if (!produce_A.IsEmpty()) {
               const TFirst& eff_beta_follow_A = firsts[j];
               multi = grammar->Follow(B) * eff_beta_follow_A;
            } else {
               multi = grammar->Follow(A) * grammar->Follow(B);
            }
            if (!multi.empty()) {
               TPrinter printer(grammar);
               fprintf(stdout, "\nA: "); para_A.print(printer); 
               fprintf(stdout, "\nB: "); para_B.print(printer);
               fprintf(stdout, "\n"); multi.print(printer);
               return false;
            }
         }
         j++;
      }
   }
   return true;
}

TParaSet* TParaSet::Core() const
{
   TParaSet* core = new TParaSet(grammar); 
   for (const TPara& para : (*this)) {
      *core << TPara((GSymbol)para);
   }
   return core;  
}

bool TParaSet::CoreCompare(const TParaSet& join) const
{
   GSymbolSet p1, p2;
   for (const GSymbol& sym : (*this)) {
      p1 << sym;
   }
   for (const GSymbol& sym : join) {
      p2 << sym;
   }
   return p1 == p2;
}

bool TParaSet::Have(const TParaSet& join) const
{
   for (const TPara& para : join) {
      if (!Have(para)) return false;
   }
   return true;
}

int  TParaSet::Change(int mode)
{
   int count = 0;
   bool verify = (mode & TChangeSymbolMode::chVerify) != 0;
   iterator ip_change = begin();
   while (ip_change != end()) {
      TPara item = *(ip_change);
      int yes_change = item.sym.Change(mode);
      if (yes_change) {
         if (!verify) {
            insert(item);
            ip_change = erase(ip_change);
         }
         count++;
      } else {
         ip_change++;
      }
   }
   return count;
}

void TParaSet::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   const char* title = printer.title;
   bool basic = (print_mode & T_PrintMode::pmBasic) != 0, compact = (print_mode & T_PrintMode::pmCompactGroup) != 0, simple = (print_mode & T_PrintMode::pmSimplePara) != 0;
   if (!simple) {
	   fprintf(file, "\n--- ");
      if (title) fprintf(file, "%s",title); else fprintf(file, "ParaSet");
      int count = basic ? 0 : (int)size();
      if (basic) {
         for (const TPara& gamma : *this) {
            if (!gamma.IsPara() || gamma.IsBasic()) count++;
         }
      }
      fprintf(file, " --- <%d> ---\n", count);
   }
   for (const TPara& gamma : *this) {
      if (basic && gamma.IsPara() && !gamma.IsBasic()) continue;
      if (!simple) {
         printer.eol();
         if (gamma.sym.IsNone()) {
            fprintf(file, "(%1d)",gamma.point); 
         } else {
            fprintf(file, "(%1d,",gamma.point); gamma.sym.print(printer); fprintf(file, ")");
         }
         if (gamma.IsPara()) {
            const GSymbol p(GSymbol::gsProduce,gamma.formula,gamma.produce);
            const GProduce& pr = grammar->Produce(p);
            pr.head.print(printer); 
            TPrinter printer_produce(printer, print_mode | (compact ? T_PrintMode::pmCompact : T_PrintMode::pmNone));
            pr.print(printer_produce, gamma.point);
         } else {
            ((const GSymbol&)gamma).print(printer);
         }
      } else {
         const TTableKey to((GSymbol)gamma,gamma.sym);
         to.print(printer);
         fprintf(file, "   ");
      }
   }
   printer.eol();
}

void TParaSet::write(TWriter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   bool basic = (print_mode & T_PrintMode::pmBasic) != 0;
   for (const TPara& para : *this) {
      if (basic && !para.IsBasic()) continue;
      para.write(printer);
   }
   printer.eol();
}

void TSituationMap::Clear()
{
   for (const TParaSet* item : vector) {
      delete item;
   }
   vector.clear(); map.clear();
}

void TSituationMap::Copy(const TSituationMap& join)
{
   for (const TParaSet* item : join.vector) {
      TParaSet* copy = new TParaSet(item->grammar,*item);
      Add(copy);
   }
}

void TSituationMap::Basic()
{
   std::vector<TParaSet*> temp_vector(vector);
   vector.clear(); map.clear();
   for (TParaSet* item : temp_vector) {
      item->Basic();
      Add(item);
   }
}

int TSituationMap::ValidLRk()
{
   int invalid = 0;
   for (const TParaSet* situation : vector) {
      if (!situation->ValidLRk()) {
         invalid++;
      }
   }
   return invalid;
}

int TSituationMap::ValidSLRk()
{
   int invalid = 0;
   int i = 0;
   for (const TParaSet* situation : vector) {
      if (!situation->ValidSLRk()) {
         invalid++;
      }
      i++;
   }
   return invalid;
}

GSymbol TSituationMap::Add(TParaSet* key)
{
   std::map<const Key, const GSymbol>::const_iterator ip = map.find(Key(key)); 
   if (ip != map.end()) {
      std::pair<const Key,const GSymbol&> item = (*ip);
      return item.second;
   }
   GSymbol sym(GSymbol::gsSituation,count());
   vector.push_back(key);
   std::pair<const Key,const GSymbol&> item(key,sym);
   map.insert(item); 
   return sym;
}

GSymbol TSituationMap::Find(const TParaSet& key) const
{
   std::map<const Key, const GSymbol>::const_iterator ip = map.find(Key(&key)); 
   if (ip != map.end()) {
      std::pair<const Key,const GSymbol&> item = (*ip);
      return item.second;
   }
   return GSymbol();
}

TParaSet* TSituationMap::Get(const GSymbol& sym) const
{
   return vector[sym.situation];
}

void TSituationMap::make_NEXTs(const TTableMap& GOTOtable, TNextTab& NEXTs)
{
   TGrammar* grammar = NEXTs.grammar;
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < this->count(); situation.situation++) {
      const TParaSet& situation_items = *this->Get(situation);
      for (const TPara& para : situation_items) {
         if (para.point) continue;
         const GProduce& produce = grammar->Produce(para);
         if (produce.IsEmpty()) continue;
         GSymbol my_situation = situation;
         for (int index = 0; index < produce.count(); index++) {
            const GSymbol& X = produce[index];
            TTableKey key(my_situation, X);
            const GSymbol& next = GOTOtable.Find(key);
            my_situation = next;
         }
         TTableKey key_A(situation, GSymbol(GSymbol::gsFormula, produce.head.formula)); // A -> produce
         const GSymbol& next = GOTOtable.Find(key_A);
         TTwoSym key_next(my_situation, produce.head);
         NEXTs.Add(key_next, next);
      }
   }
}

void TSituationMap::Expansion(const TFirstFollowTable& table, TSituationMap& TO) const
{
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < count(); situation.situation++) {
      const TParaSet& situation_items = *Get(situation);
      TParaSet *I_X = new TParaSet(situation_items.grammar);
      for (const TPara& para : situation_items) {
         const GSymbol& para_sym = para.sym;
         if (para_sym.IsTable()) {
            const TFirstFollow& tab = table.Table(para_sym);
            for (const GSymbol& sym : tab) {
               TPara my_para(para, sym);
               (*I_X) << my_para;
            }
         } else {
            (*I_X) << para;
         }
      }

      int before = TO.count();
      const GSymbol go_to = TO.Add(I_X);
      if (before == TO.count()) {
         delete I_X;
      } else {
      }
   }
}

int  TSituationMap::change(int mode)
{
   int count = 0;
   std::map<const Key, const GSymbol>::iterator ip_change = map.begin();
   while (ip_change != map.end()) {
      std::pair<const Key&, const GSymbol&> item = *(ip_change);
      const GSymbol& situation = item.second;
      TParaSet* para_set = vector[situation.situation];
      int yes_change = para_set->Change(mode);
      if (yes_change) {
         std::pair<const Key, const GSymbol&> change_item(para_set, situation);
         map.insert(change_item);
         ip_change = map.erase(ip_change);
         count++;
      } else {
         ip_change++;
      }
   }
   return count;
}

void TSituationMap::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   static char buffer[20] = {};
   bool basic = (print_mode & T_PrintMode::pmBasic) != 0;
   int para_count = 0;
   for (const TParaSet* key : vector) {
      if (basic) {
         for (const TPara& gamma : *key) {
            if (!gamma.IsPara() || gamma.IsBasic()) para_count++;
         }
      } else {
         para_count += key->count();
      }
   }
   fprintf(file, "\n--- Situations --- <%d> --- <%d> ---\n", (int)count(), para_count);
   if (print_mode == T_PrintMode::pmNone) return;
   TPrinter printer_key(printer); printer_key.title = buffer;
   if (print_mode & T_PrintMode::pmSortMode) {
      GSymbol situation;
      for (TParaSet* key : vector) {
         SPRINTF(buffer, "(%05d)", situation.situation++);
         key->print(printer_key);
      }
   } else {
      for (std::pair<const Key&, const GSymbol&> item : map) {
         SPRINTF(buffer, "(%05d)", item.second.situation);
         item.first.key->print(printer_key);
      }
   }
}

void TSituationMap::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   if (print_mode & T_PrintMode::pmWriteZero) {
      fprintf(file, "%05d\n",count());
   } else {
      fprintf(file, "%d\n",count());
   }
   if (print_mode == T_PrintMode::pmNone) return;
   if (print_mode & T_PrintMode::pmSortMode) {
      for (TParaSet* key : vector) {
         const GSymbol& situation = map.at(Key(key));
         key->write(printer);
      }
   } else {
      for (std::pair<const Key&,const GSymbol&> item : map) {
         item.first.key->write(printer);
      }
   }
}

GSymbol TSituationCore::Add(TParaSet* key, int situation)
{
   key = key->Core();
   std::map<const Key, const GSymbol>::const_iterator ip = map.find(Key(key)); 
   if (ip != map.end()) {
      std::pair<const Key,const GSymbol&> item = (*ip);
      core_arr[item.second.situation].push_back(situation);
      delete key;
      return item.second;
   }
   GSymbol sym(GSymbol::gsSituation,count());
   vector.push_back(key);
   core_arr.push_back(TCoreArrItem());
   core_arr.back().push_back(situation); 
   std::pair<const Key,const GSymbol&> item(key,sym);
   map.insert(item); 
   return sym;
}

void TSituationCore::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   TSituationMap::print(printer);
   printer.eol();
   int core = 0;
   for (const TCoreArrItem &list : core_arr) {
    	fprintf(file, "%05d -> ", core++);
      for (int item: list) {
      	fprintf(file, "%d ", item);
      }
   	fprintf(file, ";\n");
   }
	printer.eol();
}

GSymbol TSituationKernel::Add(TParaSet* key)
{
   TParaSet* core = new TParaSet(key->grammar);
   for (const TPara& para : *key) {
      *core << TPara((GSymbol)para);
   }
   std::map<const Key, const GSymbol>::const_iterator ip = map.find(Key(core)); 
   if (ip != map.end()) {
      std::pair<const Key,const GSymbol&> item = (*ip);
      if (yes_queue) {
         TParaSet* old_key = vector[item.second.situation]; int key_count = old_key->count();
         int para_step = old_key->mode ? step : 0;
         for (const TPara& para : *key) {
            TPara new_para(para); new_para.sym.value = para_step;
            *old_key << new_para;
         }
         if (old_key->mode && (key_count < old_key->count())) queue.Push(item.second);
      }
//fprintf(stdout,"\nsituation=:%05d,%05d,%05d",item.second.situation,key->count(),key_count - old_key->count());
      delete core;
      return item.second;
   }
   GSymbol sym(GSymbol::gsSituation,count());
   vector.push_back(key);
   std::pair<const Key,const GSymbol&> item(core,sym);
   map.insert(item); 
   if (yes_queue) queue.Push(sym);
//fprintf(stdout,"\nsituation+:%05d,%05d",sym.situation,key->count());
   return sym;
}

GSymbol TSituationKernel::Find(const TParaSet& key) const
{
   TParaSet core (key.grammar);
   for (const TPara& para : key) {
      core << TPara((GSymbol)para);
   }
   std::map<const Key, const GSymbol>::const_iterator ip = map.find(Key(&core)); 
   if (ip != map.end()) {
      std::pair<const Key,const GSymbol&> item = (*ip);
      return item.second;
   }
   return GSymbol();
}

void TSituationKernel::Clear()
{
   for (std::pair<const Key&,const GSymbol&> item : map) {
      delete item.first.key;
   }
   step = 0;
   TSituationMap::Clear();
}

class T_CLOSURE : public TParaSet
{
public:
   T_CLOSURE(const TGrammar* g, const TParaSet& I);
};

class T_GOTO : public TParaSet
{
public:
   T_GOTO(const TGrammar* g) :TParaSet(g) {}
   T_GOTO(const TGrammar* g, const TParaSet& I, const GSymbol& X);
};

class T_CLOSURE_LR1 : public TParaSet
{
public:
   T_CLOSURE_LR1(const TGrammar* g, const TParaSet& I);
};

class T_GOTO_LR1 : public TParaSet
{
public:
   T_GOTO_LR1(const TGrammar* g, const TParaSet& I, const GSymbol& X);
};

T_CLOSURE::T_CLOSURE(const TGrammar* g, const TParaSet& I) :TParaSet(g,I)
{
   grammar->builder->Added.Next();
   int j_work;
   do {
      j_work = 0;
      const TParaSet J(*this);
      for (const TPara& para : J) {
         const GProduce& produce = grammar->Produce(para);
         if (para.point < produce.count()) {
            const GSymbol& sym_B = produce[para.point];
            if (!sym_B.IsFormula()) continue;
            const GFormula& formula_B = grammar->Formula(sym_B);
            bool added = grammar->builder->Added.Added(sym_B);
            if (added) { 
               grammar->builder->false_count--;
               continue; 
            }
            TPara gamma(GSymbol::gsPara,sym_B.formula);
            int b_work = 0;
            for (gamma.produce = 0; gamma.produce < formula_B.count(); gamma.produce++) {
               if (!Have(gamma)) { 
                  (*this) << gamma; b_work++;
                  grammar->builder->true_count++;
               } else {
                  grammar->builder->false_count++;
               }
            }
            if (b_work) {
               j_work++;
            }
         }
      }
   } while(j_work);
}

T_GOTO::T_GOTO(const TGrammar* g, const TParaSet& I, const GSymbol& X) :TParaSet(g)
{
   TParaSet closure(grammar);
   for (const TPara& para : I) {
      const GProduce& produce = grammar->Produce(para);
      if (para.point < produce.count()) {
         const GSymbol& sym_B = produce[para.point];
         if (!(sym_B == X)) continue; // (B !== X) 
         TPara shift_para(para); produce.Shift(shift_para);
         closure << shift_para;
      }
   }
   T_CLOSURE C(grammar,closure);
   (*this) << C;
}

void TParaSet::Basic()
{
   const TPara S(GSymbol::gsPara);
   const TPara S_Eof(GSymbol(GSymbol::gsPara), GSymbol::eof);
	iterator ip = begin();
   while (ip != end()) {
      const TPara& para = (*ip);
      if (!para.point && ((para.sym.IsNone() && !(para == S)) || (!para.sym.IsNone() && !(para == S_Eof)))) {
         ip = erase(ip);
      } else {
         ip++;
      }
   } 
}

void TClosureAdded::Init(int f, int s) // +Eof, +sharp, +Empty
{ 
   formula_count = f, sym_count = s, current = 0; clear(); resize(formula_count * sym_count, 0); 
}

void TClosureAdded::Init(int m) // -1 - off, 0 - LR0, 1 - LR1, 2 - LALR, 3 - LRk, 4 - Core
{
   if (m == 0) {
      Init(grammar->count(),1);
   } else if (m == 1) {
      Init(grammar->count(),grammar->lexemes.count() + 1 + 1 + 1);
   } else if (m == 2) {
      Init((int)grammar->produces.size(),grammar->lexemes.count() + 1 + 1 + 1);
   } else if (m == 3) {
      Init(grammar->count(), grammar->lexemes.count() + 1 + 1 + 1 + grammar->Vectors().count()); // Vectors
   } else if (m == 4) {
      Init((int)grammar->produces.size(), grammar->lexemes.count() + 1 + 1 + 1 + grammar->Vectors().count()); // Vectors
   }
   type = m;
}

bool TClosureAdded::Added(const GSymbol &formula)
{
   if (type != 0) return false;
   bool added = Get(formula.formula);
   Set(formula.formula);
   return added;
}

bool TClosureAdded::Added(const GSymbol &formula, const GSymbol &lexeme)
{
   if (type == -1) return false;
   if (type == 0) return Added(formula);

   if ((type != 1) && (type != 2) && (type != 3) && (type != 4)) return false;
   int b_added = Index(lexeme);
   int a_formula = ((type != 2) && (type != 4)) ? formula.formula : ((formula.formula < 0) ? formula.produce : formula.value);
   if (b_added > (int)sym_count - 1) {
      sym_count += 100;
      resize(formula_count * sym_count, 0);
   }
   bool added = Get(a_formula,b_added);
   if (type != 2) Set(a_formula,b_added);
   return added;
}

int  TClosureAdded::Index(const GSymbol &lexeme) const
{
   int b_added = 0; // +(Eof.added = 0), +(sharp.added = 1), +(Empty.added = 2)
   if (lexeme.IsEof() || lexeme.IsEmpty())
      b_added = 0;
   else if (lexeme == GSymbol::sharp)
      b_added = 1;
   else if (lexeme.IsEmpty())
      b_added = 2;
   else if (lexeme.IsTerminal())
      b_added = grammar->lexemes.GetAdded(lexeme) + 1 + 1 + 1;
   else if (lexeme.IsVector())
      b_added = grammar->lexemes.count() + 1 + 1 + 1 + lexeme.formula;
   return b_added;
}

void TClosureAdded::Set(const GSymbol &formula, const GSymbol &lexeme)
{
   int b_added = Index(lexeme);
   int a_formula = ((type != 2) && (type != 4)) ? formula.formula : ((formula.formula < 0) ? formula.produce : formula.value);
   Set(a_formula,b_added);
}

T_CLOSURE_LR1::T_CLOSURE_LR1(const TGrammar* g, const TParaSet& I) :TParaSet(g,I)
{
   grammar->builder->Added.Next();
   int work;
   do {
      work = 0;
      const TParaSet J(*this);
      for (const TPara& para : J) {
         const GSymbol& a = para.sym;
         const GProduce& produce = grammar->Produce(para);
         if (para.point < produce.count()) {
            const GSymbol& sym_B = produce[para.point];
            if (!sym_B.IsFormula()) continue;
            const GFormula& formula_B = grammar->Formula(sym_B);

            GSymbolVector beta;
            produce.TailWithoutMaker(para, beta);
            beta << a;
            TFirst first_beta_a(beta, &grammar->FIRSTs);

            for (const GSymbol& b : first_beta_a) {
               bool added = grammar->builder->Added.Added(sym_B,b);
               if (added) { 
                  grammar->builder->false_count--;
                  continue; 
               }
               TPara gamma(GSymbol(GSymbol::gsPara,sym_B.formula),b);
               for (gamma.produce = 0; gamma.produce < formula_B.count(); gamma.produce++) {
                  if (!Have(gamma)) { 
                     (*this) << gamma; work++;
                     grammar->builder->true_count++;
                  } else {
                     grammar->builder->false_count++;
                  }
               }
            }
         }
      }
   } while(work);
}

T_GOTO_LR1::T_GOTO_LR1(const TGrammar* g, const TParaSet& I, const GSymbol& X) :TParaSet(g)
{
   TParaSet closure(grammar);
   for (const TPara& para : I) {
      const GProduce& produce = grammar->Produce(para);
      if (para.point < produce.count()) {
         const GSymbol& sym_B = produce[para.point];
         if (!(sym_B == X)) continue; // (B !== X) 
         TPara shift_para(para); produce.Shift(shift_para);
         closure << shift_para;
      }
   }
   T_CLOSURE_LR1 C(g,closure);
   (*this) << C;
}

bool TGrammarBuilder::make_LL1Table()
{
   bool ret = true;
   int table_table = 0;
   for (const GFormula* formula : grammar->formulas) {
      BREAK_POINT_TITLE(formula->title, "E_")
      BREAK_POINT_END
      if ((table_table++ % 100) == 0) {
         printf("\n%07d,%07d", table_table, Mtable.count());
      }
      for (const GProduce& produce : *formula) {
         TFirst first_produce(produce,&grammar->FIRSTs);
         for (const GSymbol& sym : first_produce) {
            if (sym.IsTerminal()) {
               TTableKey key(formula->head,sym);
               Mtable.Add(key,produce.head);
            }
         }
         if (first_produce.HaveEmpty()) {
            const TFirstFollow& follow_formula = Follow(formula->head);
            for (const GSymbol& b : follow_formula) {
               if (b.IsTerminal()) {
                  TTableKey key(formula->head,b);
                  Mtable.Add(key,produce.head);
               }
            }
            if (follow_formula.Have(GSymbol::eof)) {
               TTableKey key(formula->head,GSymbol::eof);
               Mtable.Add(key,produce.head);
            }
         }
      }
   }
#if defined(ERROR_RECOVERY)
   for (const GFormula* formula : grammar->formulas) {
      const TFirstFollow follow_produce = FOLLOWs.at(formula->head);
      for (const GSymbol& sym : follow_produce) {
         TTableKey key(formula->head,sym);
         if (Mtable.Find(key).IsNone()) Mtable.Add(key,sym);
      }
   }
#endif

   printf("\n%07d,%07d", table_table, Mtable.count());
   if (Mtable.duplicate) printf("\nDuplicate: %d\n", Mtable.duplicate);
   if (Mtable.warning) printf("\nWarning: %d\n", Mtable.warning);
   printf("\nLL1Table: %05d", Mtable.count());

   return ret;
}

bool TGrammar::make_Symple()
{
   bool ret = true;
   bool yes_change;
   do {
      yes_change = false;
      for (int f = 0; f < formulas.count(); f++) {
         GFormula* formula = formulas[f];
         if (formula == root) continue;
         GFormula::iterator i_f = formula->begin();
         while (i_f != formula->end()) {
            GProduce& produce = (*i_f);
            if (produce.empty()) { i_f++; continue; }
            if (produce[0].IsFormula()) {
               const GFormula& simple_formula = *formulas[produce[0].formula];
               if (simple_formula.back().IsEmpty()) { i_f++; continue; } 
               if (&simple_formula == formula) { i_f++; continue; }
               int before = formula->count();
               i_f = formula->insert(i_f,simple_formula.count() - 1, produce);
               int after = formula->count();
//               printf("\n%d %d %d", before, after, simple_formula.count());
               for (int s = 0; s < simple_formula.count(); s++) {
                  GProduce& produce = (*i_f++);
//                  printf("\n"); formula->head.print(this,0x00); printf(" => "); produce[0].print(this,0x00); printf(" -> "); simple_formula[s].head.print(this,0x00); printf(" used=%d",simple_formula.used);
                  GProduce::iterator ip = produce.begin();
                  ip = produce.erase(ip);
                  for (const GSymbol& sym : simple_formula[s]) {
                     ip = produce.insert(ip,sym); ip++;
                     if (sym.IsFormula()) {
                        const GFormula& used = Formula(sym);
                        used.used++;
                     }
                  }
               }
               int p = 0;
               for (GProduce& produce : *formula) {
                  produce.head.produce = p++;
               }
               simple_formula.used--;
               yes_change = true;
            } else if (produce[0].IsMaker()) {
               int i = 0; i++;
//               formula->head.print(this,0x00); printf(" maker \n");
               i_f++;
            } else {
               i_f++;
            }
         }
      }
   } while(yes_change);
   return true;
}

bool TGrammar::verify_LL()
{
   TPrinter printer;
   int first_first = 0, first_ffollow = 0;
   bool ret = true;
   for (GFormula* formula : formulas) {
//      if (!formula->used) continue;
      const TFirstFollow& follow_A = FOLLOWs.at(formula->head);
      for (int i = 0; i < formula->count() - 1; i++) {
         TFirst first_apha(&FIRSTs);
         first_apha += (*formula)[i];
         for (int j = i + 1; j < formula->count(); j++) {
            TFirst first_beta(&FIRSTs);
            first_beta += (*formula)[j];
            TFirstFollow first_ij = first_apha * first_beta;
            if (!first_ij.empty()) {
               ret = false; first_first++;
               printf("\nfirst*first:\n");
               formula->head.print(printer); printf(" : ");
               (*formula)[i].head.print(printer); (*formula)[j].head.print(printer); 
               printf(" -> "); first_ij.GSymbolSet::print(printer); printf("\n");
            }
            if (first_beta.HaveEmpty()) {
               TFirstFollow first_follow = first_apha * follow_A;
               if (!first_follow .empty()) {
                  ret = false; first_ffollow++;
                  printf("\nfirst*ffollow:\n");
                  formula->head.print(printer); printf(" : ");
                  (*formula)[i].head.print(printer); (*formula)[j].head.print(printer); 
                  printf(" -> "); first_follow .GSymbolSet::print(printer); printf("\n");
               }
            }
            if (first_apha.HaveEmpty()) {
               TFirstFollow first_follow = first_beta * follow_A;
               if (!first_follow .empty()) {
                  ret = false; first_ffollow++;
                  printf("\nfirst*ffollow:\n");
                  formula->head.print(printer); printf(" : ");
                  (*formula)[i].head.print(printer); (*formula)[j].head.print(printer); 
                  printf(" -> "); first_follow .GSymbolSet::print(printer); printf("\n");
               }
            }
         }
      }
   }
   if (first_first || first_ffollow) printf("\n");
   if (first_first)   printf("first*first: %d", first_first);
   if (first_first && first_ffollow) printf(", ");
   if (first_ffollow) printf("first*ffollow: %d", first_ffollow);
   if (first_first || first_ffollow) printf("\n");
   return ret;
}

void TGrammar::change_group()
{
   int change = 0;
   for (GFormula* formula : formulas) {
      for (GProduce& produce : *formula) {
         GProduce::iterator ip = produce.begin();
         while (ip != produce.end()) {
            GSymbol& sym = (*ip);
            if (sym.IsTerminal() && (sym.group == T_Lexeme::grSyntax)) {
               switch (sym.lexeme_type) {
               case T_Lexeme::T_Syntax::sxIdentFunc    :
                  sym.group = T_Lexeme::grIdent; sym.lexeme_type = 0;
                  change++;
                  break;
               case T_Lexeme::T_Syntax::sxIdentArr     :
                  sym.group = T_Lexeme::grIdent; sym.lexeme_type = 0;
                  change++;
                  break;
               case T_Lexeme::T_Syntax::sxDefFunc      :
                  sym.lexeme_type = T_Lexeme::sxDefType;
                  change++;
                  break;
               case T_Lexeme::T_Syntax::sxDefArr       :
                  sym.lexeme_type = T_Lexeme::sxDefType;
                  change++;
                  break;
               case T_Lexeme::T_Syntax::sxDefVar       :
                  sym.lexeme_type = T_Lexeme::sxDefType;
                  change++;
                  break;
               case T_Lexeme::T_Syntax::sxDefType      :
                  break;
               case T_Lexeme::T_Syntax::sxLabel        :
                  sym.group = T_Lexeme::grIdent; sym.lexeme_type = 0;
                  change++;
                  break;
               case T_Lexeme::T_Syntax::sxCast         :
                  sym.lexeme_type = T_Lexeme::sxDefType;
                  change++;
                  break;
               case T_Lexeme::T_Syntax::sxCastUnary    : {
                  sym.lexeme_type = T_Lexeme::sxDefType;
                  GSymbol  left(GSymbol::gsTerminal, T_Lexeme::grSeparator, T_Symbol::lxLeftBracket); 
                  ip = produce.insert(ip, left);
                  GSymbol right(GSymbol::gsTerminal, T_Lexeme::grSeparator, T_Symbol::lxRightBracket); 
                  ip = produce.insert(ip + 2, right);
                  change++;
                   } break;
               case T_Lexeme::T_Syntax::sxEmptyCramp   : {
                  sym.group = T_Lexeme::grSeparator; sym.lexeme_type = T_Symbol::lxLeftCramp;
                  GSymbol right(GSymbol::gsTerminal, T_Lexeme::grSeparator, T_Symbol::lxRightCramp); 
                  ip = produce.insert(++ip, right);
                  change++;
                  } break;
               case T_Lexeme::T_Syntax::sxEmptyBracket : {
                  sym.group = T_Lexeme::grSeparator; sym.lexeme_type = T_Symbol::lxLeftBracket;
                  GSymbol right(GSymbol::gsTerminal, T_Lexeme::grSeparator, T_Symbol::lxRightBracket); 
                  ip = produce.insert(++ip, right);
                  change++;
                  } break;
               case T_Lexeme::T_Syntax::sxEmptyScrape  : {
                  sym.group = T_Lexeme::grSeparator; sym.lexeme_type = T_Symbol::lxLeftScrape;
                  GSymbol right(GSymbol::gsTerminal, T_Lexeme::grSeparator, T_Symbol::lxRightScrape); 
                  ip = produce.insert(++ip, right);
                  change++;
                  } break;
               default:
                  break;
               }
            }
            ip++;
         }
      }
   }
   printf("\nchange terminal: %d\n", change);
}

// Green(v=1,p=169,a=2.7)
bool TGrammar::NoEmptyLanguage(int mode)
{
   for (GFormula* formula : formulas) {
      formula->ClearUsed();
   }
   int change, cycle = 0;
   do {
      change = 0;
      for (GFormula* formula : formulas) {
         for (const GProduce& produce : *formula) {
            bool yes_symbol = true;
            if (!produce.IsEmpty()) {
               for (const GSymbol& item : produce) {
                  if (!item.IsTerminal() && !(item.IsFormula() && Formula(item).IsUsed()) && !item.IsMaker()) {
                     yes_symbol = false; break;
                  }
               }
            } else { // empty
               if (produce.maker.IsNone()) { // !maker
                  yes_symbol = false; break;
               }
            }
            if (yes_symbol) {
               if (!formula->IsUsed()) {
                  formula->SetUsed();
                  change++;
               }
            }
         }
      }
      cycle++;
   } while (change && (cycle <= count() + 1));

   for (GFormula* formula : formulas) {
      if (formula->IsUsed()) {
         formula->ClearUsed();
      } else {
         formula->SetDeleted();
      }
   }

   return root && !root->IsDeleted();
}

// Green(v=1,p=171,a=2.8)
bool TGrammar::UnacceptableSymbols(int mode)
{
   formulas.root->SetUsed();

   TLexemeSet my_lexemes(this);

   int change;
   do {
      change = 0;
      for (GFormula* formula : formulas) {
         FORMULA_DELETED_CONTINUE(formula);
         if (!formula->IsUsed()) continue;
         for (const GProduce& produce : *formula) {
            for (const GSymbol& item : produce) {
               if (item.IsTerminal()) {
                  my_lexemes.Add(item);
               } else if (item.IsFormula()) {
                  GFormula* item_formula = formulas[item.formula];
                  if (!item_formula->IsUsed() && !item_formula->IsDeleted()) {
                     item_formula->SetUsed();
                     change++;
                  }
               } else if (item.IsMaker()) {
               }
            }
         }
      }
   } while (change);

   for (GFormula* formula : formulas) {
      if (formula->IsUsed()) {
         formula->ClearUsed();
      } else {
         formula->SetDeleted();
      }
   }
   lexemes = my_lexemes;

   return true;
}

// Green(v=1,p=171,a=2.9)
bool TGrammar::ExcessRemoval(int mode)
{
   if (formulas.empty() || !root || !NoEmptyLanguage()) return false;
   if (!UnacceptableSymbols()) return false;

   int new_formula = 0;
   std::vector<int> new_formulas(formulas.count(),0);
   for (const GFormula* formula : formulas) {
      if (!formula->IsDeleted()) {
         new_formulas[formula->head.formula] = new_formula++;
      }
   }

   GFormulaTable::iterator ip_formula = formulas.begin();
   while (ip_formula != formulas.end()) {
      GFormula& formula = *(*ip_formula);
      if (!formula.IsDeleted()) {
         new_formula = new_formulas[formula.head.formula];
         formula.head.formula = new_formula;
         formula.ClearUsed();
         GFormula::iterator ip_produce = formula.begin();
         int new_produce = 0;
         while (ip_produce != formula.end()) {
            GProduce& produce = *ip_produce;
            if (!produce.IsDeleted()) {
               produce.head.formula = new_formula;
               produce.head.produce = new_produce++;
               for (GSymbol& item : produce) {
                  if (item.IsFormula()) {
                     item.formula = new_formulas[item.formula];
                  }
               }
               ip_produce++;
            } else {
               ip_produce = (*ip_formula)->erase(ip_produce);
            }
         }
         ip_formula++;
      } else {
         ip_formula = formulas.erase(ip_formula);
      }
   }

   return true;
}

void TLookAhead::Add(const TElement& key)
{
   std::pair<TElement, TItem> item(key, TItem());
   map.insert(item); 
}

void TLookAhead::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   static char buffer[20] = {};
   int exp_count = 0, sym_count = 0;
   for (std::pair<const TElement&, const TItem&> item : map) {
      exp_count += (int)item.second.expansions.size();
      sym_count += item.second.symbols.count();
   }
   fprintf(file, "\n--- LookAhead --- <%d> --- <%d> --- <%d> ---\n", count(), exp_count, sym_count);
   if (print_mode == T_PrintMode::pmNone) return;
   TPrinter printer_syms(printer, T_PrintMode::pmNone);
   TPrinter printer_key(printer, T_PrintMode::pmCompact);
   TPrinter printer_exp(printer, T_PrintMode::pmSimplePara);
   if (print_mode & T_PrintMode::pmSortMode) {
      for (std::pair<const TElement&, const TItem&> item : map) {
         const GSymbolSet& syms = item.second.symbols;
      	fprintf(file, "\n--- ");
         syms.print(printer_syms);
      }
      for (std::pair<const TElement&, const TItem&> item : map) {
         fprintf(file, "\n--> ");
         for (const TElement& exp : item.second.expansions) {
            exp.print(printer_exp);
         }
      }
   } else {
      for (std::pair<const TElement&, const TItem&> item : map) {
         const TElement& key = item.first;
      	printer.eol();
         key.print(printer_key);
         if (item.second.symbols.count()) {
      	   fprintf(file, "\n--- ");
            item.second.symbols.print(printer_syms);
         }
         if (item.second.expansions.size()) {
      	   fprintf(file, "\n--> ");
            for (const TElement& exp : item.second.expansions) {
               exp.print(printer_exp); fprintf(file, " ");
            }
         }
      }
   }
   printer.eol();
}

void TLookAhead::TElement::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   TPrinter printer_situation(printer, T_PrintMode::pmCompact);
   TPrinter printer_para(printer, T_PrintMode::pmSimplePara);
   fprintf(file, "{");
   situation.print(printer_situation);
   fprintf(file, ",");
   para.print(printer_para);
   fprintf(file, "}");
}

int not_find = 0, count_empty = 0, shift_count = 0, reduce_count = 0, goto_count = 0, equ_count = 0;
int delete_count = 0, empty_count = 0, add_count = 0;

class T_GOTO_CtoAa : public TParaSet
{
public:
   T_GOTO_CtoAa(TGrammarBuilder* g_b, const TParaSet& I, const GSymbol& X, A_Syntax::T_SyntaxMode mode);
public:
   TGrammarBuilder* builder;
};

T_GOTO_CtoAa::T_GOTO_CtoAa(TGrammarBuilder* g_b, const TParaSet& I, const GSymbol& X, A_Syntax::T_SyntaxMode mode) :TParaSet(g_b->grammar), builder(g_b)
{
   TClosureAdded& Added = grammar->builder->Added;
   Added.Next();
   for (const TPara& para_B : I) {
      if ((I.mode > 0) && (para_B.sym.value <= I.mode)) continue;
      const GProduce& produce_B = grammar->Produce(para_B); // [B -> gamma . ? delta, b ]
      if (para_B.point < produce_B.count()) {
         const GSymbol& sym_B = produce_B[para_B.point];
         if (sym_B == X) {  // [B -> gamma . X delta, b ]
            TPara shift_para(para_B); produce_B.Shift(shift_para);
            (*this) << shift_para;
         }
         if (sym_B.IsFormula()) { // [B -> gamma . C delta, b ]
            const GSymbol& C = sym_B;
            Tc2a& C_A = builder->CtoAa.Get(C);
            const TAmus& tails = C_A.Get(X);
            if (tails.empty()) continue;

            TFirst first_delta_b;
            if (mode != A_Syntax::smParseLR0_Core) {
               TBTailItem* delta = builder->CtoAa.point_tails.Get(para_B);
               if (!delta->delta.empty()) {
                  first_delta_b = delta->delta;
               }
               if (!delta->half.empty()) {
                  first_delta_b << para_B.sym; // b
               }
            }

            for (std::pair<const GSymbol&, const TAmu&> item_mu : tails) {
               const TAmu& tail = item_mu.second;
               GSymbol para(GSymbol::gsPara, tail.point.formula, tail.point.produce, tail.point.point + 1);
               if (mode == A_Syntax::smParseLR0_Core) {
                  (*this) << TPara(para);
               } else {
                  // [ A -> X . beta , ?]
                  if (!tail.half.empty()) {
                     for (const GSymbol& a : first_delta_b) {
                        (*this) << TPara(para, a);
                     }
                  }
                  if (tail.step != Added.Current()) {
                     for (const GSymbol& a : tail.mu) {
                        (*this) << TPara(para, a);
                     }
                  } else {
                     count_empty++;
                  }
                  tail.step = Added.Current();
               }
            }
         }
      }
   }
}

void TGrammarBuilder::make_ActionC2Aa(const TSituationMap& stable, const GSymbol& situation, A_Syntax::T_SyntaxMode mode)
{
   const TParaSet& situation_items = *stable.Get(situation);
   for (const TPara& para_B : situation_items) { // [B -> gamma . ? delta, b ]
      const GProduce& produce_B = grammar->Produce(para_B);
      if (para_B.point < produce_B.count()) {
         const GSymbol& sym_B = produce_B[para_B.point];
         if (sym_B.IsFormula()) { // [B -> gamma . C delta, b ]
            const GSymbol& C = sym_B;
            Tc2a& C_A = CtoAa.Get(C);
            for (const GSymbol& a : C_A.terminals) {
               TTableKey key(situation,a);
               const GSymbol& I_j = GOTOtable.Find(key);
               if (I_j.IsSituation()) {
                  TAction action(TAction::taShift,I_j);
                  int before = LRtable.count();
                  LRtable.Add(key,action);
                  if (before == LRtable.count()) equ_count++; else shift_count++;
               } else {
                  not_find++;
               }
            }

            const TAmus& tails = C_A.Get(GSymbol::empty);
            TFirst first_delta_b;
            if ((mode == A_Syntax::smParseLR1_Core) && !tails.empty()) {
               TBTailItem* delta = CtoAa.point_tails.Get(para_B);
               if (!delta->delta.empty()) {
                  first_delta_b = delta->delta;
               }
               if (!delta->half.empty()) {
                  first_delta_b << para_B.sym; // b
               }
            }

            for (std::pair<const GSymbol&, const TAmu&> item_mu : tails) {
               const TAmu& tail = item_mu.second;
               TFirst first_mu_A;
                if (mode == A_Syntax::smParseLR0_Core) {
                   first_mu_A = (TFirst&)Follow(GSymbol(GSymbol::gsFormula,tail.point.formula));
                } else {
                   first_mu_A.Plus(tail.mu, first_delta_b);
                }
                GSymbol A(GSymbol::gsProduce,tail.point.formula,tail.point.produce);
                const GProduce& produce_A = grammar->Produce(A);
                TAction action(TAction::taReduce,produce_A.head);
                for (const GSymbol& a : first_mu_A) {
                   TTableKey key(situation,a); key.sym.value = 0;
                   int before = LRtable.count();
                   LRtable.Add(key,action);
                   if (before == LRtable.count()) equ_count++; else reduce_count++;
                }
             }
         } else if (sym_B.IsTerminal()) {
            TTableKey key(situation,sym_B); key.sym.value = 0;
            const GSymbol& I_j = GOTOtable.Find(key);
            if (I_j.IsSituation()) {
               TAction action(TAction::taShift,I_j);
               int before = LRtable.count();
               LRtable.Add(key,action);
               if (before == LRtable.count()) equ_count++; else shift_count++;
            } else {
               not_find++;
            }
         }
      }
      if ((para_B.point == produce_B.count()) || produce_B.IsEmpty()) {
         if (produce_B.head.IsStart()) {
            TAction action(TAction::taAccept,produce_B.head);
            TTableKey key(situation,GSymbol::eof);
            LRtable.Add(key,action);
         } else {
            TAction action(TAction::taReduce,produce_B.head);
            GSymbol A(GSymbol::gsFormula,produce_B.head.formula);
            TFirstFollow follow_A;
            if (mode == A_Syntax::smParseLR0_Core) {
               follow_A = Follow(A);
            } else {
               follow_A << para_B.sym;
            }
            for (const GSymbol& a : follow_A) {
               TTableKey key(situation,a); key.sym.value = 0;
               int before = LRtable.count();
               LRtable.Add(key,action);
               if (before == LRtable.count()) equ_count++; else reduce_count++;
            }
         }
      }
   }
}

void TGrammarBuilder::make_StateC2Aa(TSituationMap& stable, const GSymbol& situation, const GSymbol& X, A_Syntax::T_SyntaxMode mode)
{
   const TParaSet *I = stable.Get(situation);
   TParaSet *I_X = new T_GOTO_CtoAa(this,*I,X,mode);
   if (I_X->empty()) { delete I_X; delete_count++; empty_count++; return; }
   int before = stable.count();
   GSymbol go_to = stable.Add(I_X);
   if (before == stable.count()) {
      delete I_X;
      delete_count++;
   } else {
      add_count++;
   }
   TTableKey key(situation,X);
   GOTOtable.Add(key,go_to);
}

void TGrammarBuilder::make_StateC2Aa(TSituationMap& stable, const GSymbol& situation, A_Syntax::T_SyntaxMode mode)
{
   TParaSet *I = stable.Get(situation);
   I->mode = -1;
   int new_step = stable.step++;
   for (const GFormula* formula : grammar->formulas) {
      const GSymbol& X = formula->head;
      make_StateC2Aa(stable, situation, X, mode);
   }
   for (const std::pair<const GSymbol&, int> item : grammar->lexemes) {
      const GSymbol& X = item.first;
      make_StateC2Aa(stable, situation, X, mode);
   }
   I->mode = new_step;
}

bool TGrammarBuilder::make_C2Aa_LR(A_Syntax::T_SyntaxMode mode)
{
   CtoAa.Core();
   CtoAa.Split();
   Added.Init((mode == A_Syntax::smParseLR0_Core) ? 0 : 4);

   bool ret = true;
   printf("\nSituation");

   {
   TPara S(GSymbol::gsPara);
   if (mode == A_Syntax::smParseLR1_Core) {
      S.sym = GSymbol::empty;
   }
   TParaSet* I = new TParaSet(grammar,S);
   Stable.Add(I);
   Stable.step++;
   }

   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable.count(); situation.situation++) {
      if ((situation.situation % 100) == 0) {
         printf("\n%05d,%05d,%05d",situation.situation,Stable.count(), (int)GOTOtable.size());
      }
      make_StateC2Aa(Stable, situation, mode);
   }
   CtoAa.Merge();
   printf("\n%05d,%05d",Stable.count(),GOTOtable.count());
   Stable.print();
   printf("\n--- GOTOtable --- <%d> ---\n",GOTOtable.count());

   LRtable.GOTO(GOTOtable);
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable.count(); situation.situation++) {
      if ((situation.situation % 100) == 0) {
         printf("\n%05d,%05d",situation.situation, LRtable.count());
      }
      make_ActionC2Aa(Stable, situation, mode);
   }
   printf("\n%05d,%05d, not_find=%d, empty=%d, shift=%d, reduce=%d, goto=%d\n", Stable.count(), LRtable.count(), not_find, count_empty, shift_count, reduce_count, goto_count);

   ret = LRtable.verify(GOTOtable);

   return ret;
}

bool TGrammarBuilder::make_C2Aa_LALR()
{
   CtoAa.Core();
   Added.Init(4);
   CtoAa.Split();

   printf("\nSituation");
   bool ret = true;
   LALRStable.yes_queue = true;

   {
   TPara S(GSymbol(GSymbol::T_Type::gsPara), GSymbol::empty);
   TParaSet* I = new TParaSet(grammar,S);
   LALRStable.Add(I);
   LALRStable.step++;
   }

   int step = 0;
   for (GSymbol situation; LALRStable.queue.Pop(situation); ) {
      if ((++step % 100) == 0) {
         printf("\n%05d,%05d,%05d",situation.situation,LALRStable.count(), (int)GOTOtable.size());
      }
      make_StateC2Aa(LALRStable, situation, A_Syntax::smParseLR1_Core);

   }
   CtoAa.Merge();
   printf("\n%05d,%05d",LALRStable.count(),GOTOtable.count());
   LALRStable.print();
   printf("\n--- GOTOtable --- <%d> ---\n",GOTOtable.count());

   int before = LRtable.count();
   LRtable.GOTO(GOTOtable);
   goto_count += (LRtable.count() - before);

   for (GSymbol situation(GSymbol::gsSituation); situation.situation < LALRStable.count(); situation.situation++) {
      if ((situation.situation % 100) == 0) {
         printf("\n%05d,%05d",situation.situation, LRtable.count());
      }
      make_ActionC2Aa(LALRStable, situation, A_Syntax::smParseLR1_Core);
   }
   printf("\n%05d,%05d, not_find=%d, empty=%d, shift=%d, reduce=%d, goto=%d, equ=%d\n", LALRStable.count(), LRtable.count(), not_find, count_empty, shift_count, reduce_count, goto_count, equ_count);

   Stable.Copy(LALRStable); // print

   ret = LRtable.verify(GOTOtable);
   LRtable.change(TChangeSymbolMode::chEmptyToEof);
   GOTOtable.change(TChangeSymbolMode::chEmptyToEof);
   Stable.change(TChangeSymbolMode::chEmptyToEof);

   return ret;
}

class TLink {
public:
   TLink() {}
   void print(TPrinter& printerL) const;
public:
   GSymbolSet provides;
};

void TLink::print(TPrinter& printer) const
{
   provides.print(printer); fprintf(printer.file, "\n");
}

class TGrammarLink : public std::map<const GSymbol, TLink> {
public:
   TGrammarLink(const TGrammar* g) :grammar(g), maker_tree(0), maker_code(0), maker_node(0), maker_yacc(0), maker_turn(0), maker_call(0) {}
   int Add(const GSymbol& used, const GSymbol& owner);
   void make();
   void print(TPrinter& printer) const;
public:
   const TGrammar * grammar;
   GSymbolVector left, right;
   int maker_tree, maker_code, maker_node, maker_turn, maker_yacc, maker_call;
};

int  TGrammarLink::Add(const GSymbol& used, const GSymbol& owner)
{
   int ret = 0;
   iterator ip = find(used);
   if (ip != end()) {
      TLink& item = (*ip).second;
      GSymbolSet& owners = item.provides;
      if (owners.Add(owner)) ret++;
   } else {
      std::pair<GSymbol, TLink> item; item.first = used;
      GSymbolSet& owners = item.second.provides;
      if (owners.Add(owner)) ret++;
      insert(item); ret++;
   }
   return ret;
}

void TGrammarLink::make()
{
   for (const GFormula* formula : grammar->formulas) {
      for (const GProduce& produce : *formula) {
         int p = 0;
         for (const GSymbol& item : produce) {
            GSymbol point(GSymbol::gsPoint, produce.head.formula, produce.head.produce, p);
            if (item.IsMaster()) {
               if (!p) left.Add(point); else right.Add(point);
            }
            if (item.IsMaker()) {
               if (item.IsMakerTree()) maker_tree++;
               if (item.IsMakerCode()) maker_code++;
               if (item.IsMakerNode()) maker_node++;
               if (item.IsMakerYACC()) maker_yacc++;
               if (item.IsMakerTurn()) maker_turn++;
               if (item.IsMakerCall()) maker_call++;
            }
            Add(item, point);
            p++;
         }
         const GSymbol& maker = produce.maker;
         if (maker.IsMaker()) {
            if (maker.IsMakerTree()) maker_tree++;
            if (maker.IsMakerCode()) maker_code++;
            if (maker.IsMakerNode()) maker_node++;
            if (maker.IsMakerYACC()) maker_yacc++;
            if (maker.IsMakerTurn()) maker_turn++;
            if (maker.IsMakerCall()) maker_call++;
         }
      }
   }
}

void TGrammarLink::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   GSymbol::T_Type old_type = GSymbol::T_Type::gsNone;
   for (std::pair<const GSymbol&, const TLink&> item : (*this)) {
      if (item.first.type != old_type) {
         old_type = item.first.type;
         fprintf(file, "-------- %s --------\n", symbol_title(old_type));
      }
      item.first.print(printer); fprintf(file, " -> %d\n", (int)item.second.provides.size());
      TPrinter printer_item(printer, print_mode | T_PrintMode::pmCompactGroup);
      item.second.print(printer_item);
      printer.eol();
   }

   print_mode |= T_PrintMode::pmCompactGroup;
   if (!left.empty()) {
      fprintf(file, "Lleft recursion: %d\n", (int)left.size());
      left.print(printer); printer.eol();
      if (!right.empty()) printer.eol();
   }

   if (!right.empty()) {
      fprintf(file, "Right recursion: %d\n", (int)right.size());
      right.print(printer); printer.eol();
   }

   if (maker_tree || maker_code || maker_node || maker_turn || maker_yacc || maker_call) {
      fprintf(file, "\nMakers: Tree(%d), Code(%d), Node(%d), YACC(%d), Turn(%d), Call(%d)\n", maker_tree, maker_code, maker_node, maker_yacc, maker_turn, maker_call);
   }
   if (printer.file_name) {
      printer.eol();
   }
}

void TGrammar::output(TPrinter& printer) const
{

   PRINTER_FILE_MODE
   fprintf(file, "Type:");
   char seporator = ' ';
   if (type & T_Grammar::gtLL         ) { fprintf(file, "%c LL"         , seporator); seporator = ','; }
   if (type & T_Grammar::gtLR         ) { fprintf(file, "%c LR"         , seporator); seporator = ','; }
   if (type & T_Grammar::slSyntax     ) { fprintf(file, "%c Syntax"     , seporator); seporator = ','; }
   if (type & T_Grammar::slPrior      ) { fprintf(file, "%c Prior"      , seporator); seporator = ','; }
   if (type & T_Grammar::slPriorAssign) { fprintf(file, "%c PriorAssign", seporator); seporator = ','; }
   if (type & T_Grammar::slSimple     ) { fprintf(file, "%c Simple"     , seporator); seporator = ','; }
   if (type & T_Grammar::slNoDefType  ) { fprintf(file, "%c NoDefType"  , seporator); seporator = ','; }
   if (type & T_Grammar::slNoDefArrVar) { fprintf(file, "%c NoDefArrVar", seporator); seporator = ','; }
   if (type & T_Grammar::slNoSave     ) { fprintf(file, "%c NoSave"     , seporator); seporator = ','; }
   if (type & T_Grammar::slMeta       ) { fprintf(file, "%c Meta"       , seporator); seporator = ','; }
   if (type & (T_Grammar::mtTree | T_Grammar::mtCode | T_Grammar::mtSNode | T_Grammar::mtYacc | T_Grammar::mtTurn | T_Grammar::mtCall)) {
      fprintf(file, "%c Makers(", seporator); const char* seporator = "";
      if (type & T_Grammar::mtTree ) { fprintf(file, "%sTree" , seporator); seporator = ", "; }
      if (type & T_Grammar::mtCode ) { fprintf(file, "%sCode" , seporator); seporator = ", "; }
      if (type & T_Grammar::mtSNode) { fprintf(file, "%sNode" , seporator); seporator = ", "; }
      if (type & T_Grammar::mtYacc ) { fprintf(file, "%sYacc" , seporator); seporator = ", "; }
      if (type & T_Grammar::mtTurn ) { fprintf(file, "%sTurn" , seporator); seporator = ", "; }
      if (type & T_Grammar::mtCall ) { fprintf(file, "%sCall" , seporator); seporator = ", "; }
      if (type & T_Grammar::mtEmpty) { fprintf(file, "%sEmpty", seporator); seporator = ", "; }
      if (type & T_Grammar::mtHead ) { fprintf(file, "%sHead" , seporator); seporator = ", "; }
      fprintf(file, ")");
   }
   fprintf(file, "\nPrefix: %s",prefix);
   printer.eol();

   TGrammarLink link(this);
   link.make();
   fprintf(file, "\n--- Link --- <%d> ---\n\n", (int)link.size());
   printer.print_mode |= T_PrintMode::pmCompact;
   link.print(printer);

}

bool TGrammarBuilder::make_LALRTable()
{
   bool ret = make_LR0States(); // Stable, GOTOtable
   Stable.Basic();
   Stable.print();

   true_count = 0; false_count = 0;

   {
   TFirstFollow FIRST(&grammar->FIRSTs); FIRST += GSymbol::sharp;
   grammar->FIRSTs.Add(GSymbol::sharp,FIRST);
   }

   bool start = true;
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable.count(); situation.situation++) {
      const TParaSet *I = Stable.Get(situation);
      for (const TPara& para : *I) {
         TLookAhead::TElement key(situation,para);
         LookAhead.Add(key);
         if (start) { start = false; (*LookAhead.map.begin()).second.symbols.Add(GSymbol::eof); }
      }
   }

   Added.Init(1);
   int step = 0, para_count = 0, sym_count = 0;
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable.count(); situation.situation++) {
      const TParaSet *I = Stable.Get(situation);
      if ((step % 100) == 0) {
         printf("\n%05d,%05d,%05d",step,para_count,sym_count);
      }
      step++;
      for (const TPara& A_ab : *I) {
         TLookAhead::TElement key_core(situation, A_ab);
         TLookAhead::TItem& item_from = LookAhead.Get(key_core);
         TPara sharp_para((GSymbol)A_ab, GSymbol::sharp);
         TParaSet P(grammar,sharp_para);
         T_CLOSURE_LR1 J(grammar,P);
         for (const TPara& B_gXd : J) {
            const GProduce& produce = grammar->Produce(B_gXd);
            if ((B_gXd.point < produce.count()) && !produce.IsEmpty()) {
               const GSymbol& X = produce[B_gXd.point];
               TTableKey key_goto(situation,X);
               const GSymbol& goto_X = GOTOtable.Find(key_goto); 
               TPara to_para(B_gXd); to_para.point++; to_para.sym = GSymbol::none;
               const TLookAhead::TElement key_to(goto_X, to_para);
               TLookAhead::TItem& to_item = LookAhead.Get(key_to);
               GSymbolSet& to_symbols = to_item.symbols;
               TLookAhead::TElement expansion(goto_X, to_para);
               if (B_gXd.sym == GSymbol::sharp) {
                  item_from.Add(expansion);
               } else {
                  to_symbols.Add(B_gXd.sym);
               }
               sym_count++;
            }
         }
         para_count++;
      }
   }
   printf("\n%05d,%05d,%05d\n",step,para_count,sym_count);
   printf("\ntrue_count=%d, false_count=%d, closure_count=%d\n",true_count, false_count, Added.Current());

   std::set<TLookAhead::TElement> queue;
   for (std::pair<const TLookAhead::TElement&, const TLookAhead::TItem&> item : LookAhead.map) {
      if (item.second.expansions.empty()) continue;
      queue.insert(item.first);
   }

   step = 0;
   while (!queue.empty()) {
      const TLookAhead::TElement queue_item = *queue.begin(); queue.erase(queue.begin());
      int all_work = 0;
      TLookAhead::TItem& from_item = LookAhead.Get(queue_item);
      const GSymbolSet& symbols = from_item.symbols;
      for (const TLookAhead::TElement& expansion : from_item.expansions) {
         TLookAhead::TElement key_to(expansion);
         TLookAhead::TItem& to_item = LookAhead.Get(key_to);
         GSymbolSet& to_symbols = to_item.symbols;
         int work = 0;
         for (const GSymbol sym : symbols) {
            if (to_symbols.Add(sym)) work++;
         }
         if (work && (queue.find(key_to) == queue.end())) {
            queue.insert(key_to);
         }
         all_work += work;
      }
      if ((step % 100) == 0) {
         printf("\n%05d,%05d", step, all_work);
      }
      step++;
   }
   printf("\n%05d\n", step);

   TSituationMap  LALRStable;
   step = 0;
   para_count = 0;
   true_count = 0; false_count = 0;
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable.count(); situation.situation++) {
      if ((step % 100) == 0) {
         printf("\n%05d,%05d",step,para_count);
      }
      step++;
      const TParaSet *I = Stable.Get(situation);
      TParaSet LALR_I(grammar); 
      for (const TPara& A_ab : *I) {
         const TLookAhead::TElement key_core(situation, A_ab);
         const TLookAhead::TItem& item = LookAhead.Get(key_core);
         const GSymbolSet& symbols = item.symbols;
         for (const GSymbol sym : symbols) {
            TPara LALR_para((const GSymbol)A_ab, sym);
            LALR_I.Add(LALR_para);
         }
         para_count++;
      }

      T_CLOSURE_LR1* I_X = new T_CLOSURE_LR1(grammar,LALR_I);
      TParaSet *I_X_P = new TParaSet(grammar,LALR_I); TablePrint.Add(I_X_P);
      const GSymbol go_to = LALRStable.Add(I_X);
   }
   printf("\n%05d,%05d", step, para_count);
   printf("\ntrue_count=%d, false_count=%d, closure_count=%d", true_count, false_count, Added.Current());

   LALRStable.print();

   ret = make_LR1Table(LALRStable, 0x02); // go_to

   TPrinter printer;
   LRtable.print(printer);
   Stable.Clear();
   Stable.Copy(LALRStable); // print
   LALRStable.Clear();

   ret = LRtable.verify(GOTOtable);

   return ret;
}

void TGrammarBuilder::make_ActionLR0(const TSituationMap& stable, const GSymbol& situation)
{
   const TParaSet& situation_items = *stable.Get(situation);
   for (const GSymbol& para : situation_items) {
      const GProduce& produce = grammar->Produce(para);
      if (para.point < produce.count()) {
         const GSymbol& a = produce[para.point];
         if (a.IsTerminal()) {
            TTableKey key(situation,a);
            const GSymbol& I_j = GOTOtable.Find(key);
            if (I_j.IsSituation()) {
               TAction action(TAction::taShift,I_j);
               int before = LRtable.count();
               LRtable.Add(key,action);
               if (before == LRtable.count()) equ_count++; else shift_count++;
            } else {
               not_find++;
            }
         }
      }
      if ((para.point == produce.count()) || produce.IsEmpty()) {
         if (produce.head.IsStart()) {
            TAction action(TAction::taAccept,produce.head);
            TTableKey key(situation,GSymbol::eof);
            LRtable.Add(key,action);
         } else {
            TAction action(TAction::taReduce,produce.head);
            GSymbol A(GSymbol::gsFormula,produce.head.formula);
            const TFirstFollow& follow_A = Follow(A);
            for (const GSymbol& a : follow_A) {
               TTableKey key(situation,a);
               int before = LRtable.count();
               LRtable.Add(key,action);
               if (before == LRtable.count()) equ_count++; else reduce_count++;
            }
         }
      }
   }
   for (const GFormula* formula : grammar->formulas) {
      const GSymbol& A = formula->head;
      if (A.IsStart()) continue;
      TTableKey key(situation,A);
      const GSymbol& I_j = GOTOtable.Find(key);
      if (I_j.IsSituation()) {
         TAction action(TAction::taGoto,I_j);
         int before = LRtable.count();
         LRtable.Add(key,action);
         if (before == LRtable.count()) equ_count++; else goto_count++;
      } else {
         not_find++;
      }
   }
}

void TGrammarBuilder::make_StateLR0(const GSymbol& situation, const GSymbol& X)
{
   const TParaSet *I = Stable.Get(situation);
   TParaSet *I_X = new T_GOTO(grammar,*I,X);
   if (I_X->empty()) { delete I_X; delete_count++; empty_count++; return; }
   int before = Stable.count();
   const GSymbol go_to = Stable.Add(I_X);
   if (before == Stable.count()) {
      delete I_X;
      delete_count++;
   } else {
      add_count++;
   }
   TTableKey key(situation,X);
   GOTOtable.Add(key,go_to);
}

void TGrammarBuilder::make_StateLR0(const GSymbol& situation)
{
   const TParaSet *I = Stable.Get(situation);
   if (I->count() > (grammar->lexemes.count() + grammar->formulas.count())) {
      for (const GFormula* formula : grammar->formulas) {
         const GSymbol& X = formula->head;
         make_StateLR0(situation, X);
      }
      for (const std::pair<const GSymbol&, int> item :  grammar->lexemes) {
         const GSymbol& X = item.first;
         make_StateLR0(situation, X);
      }
   } else {
      GSymbolSet symbols;
      for (const TPara& para : *I) {
         const GProduce& produce = grammar->Produce(para);
         if (para.point < produce.count()) {
            const GSymbol& sym_B = produce[para.point];
            if (sym_B.IsTerminal() || sym_B.IsFormula()) { 
               symbols << sym_B;
            }
         }
      }
      for (const GSymbol& X : symbols) {
         make_StateLR0(situation, X);
      }
   }
}

bool TGrammarBuilder::make_LR0States()
{
   bool ret = true;
   Added.Init(0);

   {
   TPara S(GSymbol::gsPara);
   TParaSet I(grammar,S);
   T_CLOSURE* J = new T_CLOSURE(grammar,I);
   Stable.Add(J);
   }

   printf("\nSituation");
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable.count(); situation.situation++) {
      if ((situation.situation % 100) == 0) {
         printf("\n%05d",situation.situation);
      }
      make_StateLR0(situation);
   }
   printf("\n%05d, delete=%d, empty=%d, add=%d, true_count=%d, false_count=%d, closure_count=%d",Stable.count(),delete_count, empty_count, add_count, true_count, false_count, Added.Current());
   Stable.print();
   printf("\n--- GOTOtable --- <%d> ---\n", (int)GOTOtable.size());
   return ret;
}

bool TGrammarBuilder::make_LR0Table()
{
   bool ret = make_LR0States();

   printf("\nAction");
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable.count(); situation.situation++) {
      if ((situation.situation % 100) == 0) {
         printf("\n%05d,%05d",situation.situation, LRtable.count());
      }
      make_ActionLR0(Stable, situation);
   }
   printf("\n%05d,%05d, not_find=%d, empty=%d, shift=%d, reduce=%d, goto=%d\n", Stable.count(), LRtable.count(), not_find, count_empty, shift_count, reduce_count, goto_count);
   TablePrint.Copy(Stable); // print
   TPrinter printer;
   LRtable.print(printer);
   
   ret = LRtable.verify(GOTOtable);

   return ret;
}

void TGrammarBuilder::make_StateLR1(TSituationMap& stable, const GSymbol& situation, const GSymbol& X)
{
   const TParaSet *I = stable.Get(situation);
   TParaSet *I_X = new T_GOTO_LR1(grammar,*I,X);
   if (I_X->empty()) { delete I_X; delete_count++; empty_count++; return; }
   int before = stable.count();
   const GSymbol go_to = stable.Add(I_X);
   if (before == stable.count()) {
      delete I_X;
      delete_count++;
   } else {
      add_count++;
   }
   TTableKey key(situation,X);
   GOTOtable.Add(key,go_to);
}

void TGrammarBuilder::make_StateLR1(TSituationMap& stable, const GSymbol& situation)
{
   const TParaSet *I = stable.Get(situation);
   if (I->count() > (grammar->lexemes.count() + grammar->formulas.count())) {
      for (const GFormula* formula : grammar->formulas) {
         const GSymbol& X = formula->head;
         make_StateLR1(stable, situation, X);
      }
      for (const std::pair<const GSymbol&, int> item : grammar->lexemes) {
         const GSymbol& X = item.first;
         make_StateLR1(stable, situation, X);
      }
   } else {
      GSymbolSet symbols;
      for (const TPara& para : *I) {
         const GProduce& produce = grammar->Produce(para);
         if (para.point < produce.count()) {
            const GSymbol& sym_B = produce[para.point];
            if (sym_B.IsTerminal() || sym_B.IsFormula()) { 
               symbols << sym_B;
            }
         }
      }
      for (const GSymbol& X : symbols) {
         make_StateLR1(stable, situation, X);
      }
   }
}

void TGrammarBuilder::make_ActionLR1(TSituationMap& stable, const GSymbol& situation, int mode)
{
   const TParaSet& situation_items = *stable.Get(situation);
   bool basic = mode & 0x01, go_to = (mode & 0x02) != 0, make_go_to = (mode & 0x08) != 0;
   for (const TPara& para : situation_items) {
      const GProduce& produce = grammar->Produce(para);
      if (para.point < produce.count()) {
         const GSymbol& a = produce[para.point];
         if (a.IsTerminal()) {
            TTableKey key(situation,a);
            GSymbol I_j;
            if (go_to) {
               I_j = GOTOtable.Find(key);
            } else {
               T_GOTO_LR1 I_A(grammar,situation_items,a);
               if (!I_A.empty()) {
                  if (basic) I_A.Basic();
                  I_j = stable.Find(I_A);
               } else {
                  count_empty++;
               }
            }
            if (I_j.IsSituation()) {
               TAction action(TAction::taShift,I_j);
               int before = LRtable.count();
               LRtable.Add(key,action);
               if (before == LRtable.count()) equ_count++; else shift_count++;
               if (make_go_to) {
                  GOTOtable.Add(key,I_j);
               }
            } else {
               not_find+=go_to?-1:1;
            }
         }
      }
      if ((para.point == produce.count()) || produce.IsEmpty()) {
         if (produce.head.IsStart()) {
            TAction action(TAction::taAccept,produce.head);
            TTableKey key(situation,GSymbol::eof);
            LRtable.Add(key,action);
         } else {
            TAction action(TAction::taReduce,produce.head);
            const GSymbol& a = para.sym;
            TTableKey key(situation,a);
            int before = LRtable.count();
            LRtable.Add(key,action);
            if (before == LRtable.count()) equ_count++; else reduce_count++;
         }
      }
   }
   for (const GFormula* formula : grammar->formulas) {
      const GSymbol& A = formula->head;
      if (A.IsStart()) continue;
      TTableKey key(situation,A);
      GSymbol I_j;
      if (go_to) {
         I_j = GOTOtable.Find(key);
      } else {
         T_GOTO_LR1 I_A(grammar,situation_items,A);
         if (I_A.empty()) {
            count_empty++;
            continue;
         }
         if (basic) I_A.Basic();
         I_j = stable.Find(I_A);
      }
      if (I_j.IsSituation()) {
         TAction action(TAction::taGoto,I_j);
         int before = LRtable.count();
         LRtable.Add(key,action);
         if (before == LRtable.count()) equ_count++; else goto_count++;
         if (make_go_to) {
            GOTOtable.Add(key,I_j);
         }
      } else {
         not_find+=go_to?-1:1;
      }
   }
}

bool TGrammarBuilder::make_LR1Table(TSituationMap& stable, int mode)
{
   bool ret = true;
   printf("\nAction");
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < stable.count(); situation.situation++) {
      if ((situation.situation % 100) == 0) {
         printf("\n%05d,%05d",situation.situation, LRtable.count());
      }
      const TParaSet& situation_items = *stable.Get(situation);
      make_ActionLR1(stable, situation, mode);
   }
   printf("\n%05d,%05d, not_find=%d, empty=%d, shift=%d, reduce=%d, goto=%d, equ=%d\n", stable.count(), LRtable.count(), not_find, count_empty, shift_count, reduce_count, goto_count, equ_count);

   return ret;
}

bool TGrammarBuilder::make_LR1States()
{
   bool ret = true;
   Added.Init(1);

   {
   const GSymbol eof(GSymbol::gsEof);
   TPara S(GSymbol(GSymbol::T_Type::gsPara),eof);
   TParaSet I(grammar,S);
   T_CLOSURE_LR1* J = new T_CLOSURE_LR1(grammar,I);
   Stable.Add(J);
   }

   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable.count(); situation.situation++) {
      if ((situation.situation % 100) == 0) {
         printf("\n%05d,%05d,%05d",situation.situation,Stable.count(), (int)GOTOtable.size());
      }
      make_StateLR1(Stable, situation);
   }
   printf("\n%05d,%05d",Stable.count(),GOTOtable.count());
   Stable.print();
   printf("\n--- GOTOtable --- <%d> ---\n",GOTOtable.count());

   return ret;
}

bool TGrammarBuilder::make_LR1Table()
{
   bool ret = true;

   ret = make_LR1States();
   ret = make_LR1Table(Stable, 0x02); // go_to
   TablePrint.Copy(Stable); // print
   TPrinter printer;
   LRtable.print(printer);

   ret = LRtable.verify(GOTOtable);

   return ret;
}

bool TGrammarBuilder::make_LALR_FullTable(A_Syntax::T_SyntaxMode syntax_mode)
{
   bool ret = true;

   ret = make_LR1States(); // Stable, GOTOtable

   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable.count(); situation.situation++) {
      const TParaSet* item = Stable.Get(situation);
      TParaSet* core = item->Core();
      COREtable.Add(core, situation.situation);
   }
   const TCoreArr& core_arr = COREtable.Core();

   std::vector<int> move; move.resize(Stable.count(),-1);
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

   if (syntax_mode == A_Syntax::smParseLALR_Full) {
      GOTOtable.clear(); // print
      ret = make_LR1Table(LALRStable, 0x08); // make_go_to
   } else {
      TTableMap  old_GOTOtable(GOTOtable);
      GOTOtable.clear();
      for (const std::pair<const TTableKey&,const GSymbol&> item : old_GOTOtable) {
         TTableKey key = item.first; key.key.situation = move[key.key.situation];
         GSymbol go_to = item.second; go_to.situation = move[go_to.situation];
         GOTOtable.Add(key,go_to);
      }
   
      ret = make_LR1Table(LALRStable, 0x02); // goto
   }

   Stable.Clear();
   Stable.Copy(LALRStable); // print
   LALRStable.Clear();
   TPrinter printer;
   LRtable.print(printer);

   ret = LRtable.verify(GOTOtable);

   return ret;
}

// 0x0100 - YACC_SYNTREE SyntaxTree, 0x0200 - union { lexeme, node }
char* get_file_name(const char*file, const char* ext);

bool TGrammarBuilder::Analyze(A_Syntax::T_SyntaxMode syntax_mode, const char* file)
{
   return true;
}

bool TGrammarBuilder::Make(A_Syntax::T_SyntaxMode syntax_mode, const char* file)
{
   bool ret = true;
   char *file_state = NULL, *file_action = NULL, *file_cell = NULL, *file_goto = NULL, 
        *file_C2A   = NULL, *file_core   = NULL, *file_look = NULL, *file_cpp  = NULL,
        *file_tab   = NULL;

   look_ahead = grammar->look_ahead;

   if ((syntax_mode >= A_Syntax::smParseLR0) && (syntax_mode <= A_Syntax::smParseLALR_Core)) {
      if (syntax_mode == A_Syntax::smParseLR0) {
         if (look_ahead > 0) {
            make_SLRkTable(look_ahead);
         } else {
            make_LR0Table();
//            make_SLRkTable(0);
         }
      } else if (syntax_mode == A_Syntax::smParseLR1) {
         if (look_ahead > 0) {
            if (grammar->option & TGrammar::opSplitting) {
               make_GrammarSplitting(look_ahead);
            } else {
               make_LRkTable(look_ahead);
               if (grammar->option & (TGrammar::opFiUnattainable | TGrammar::opChainRule)) {
                  make_FiUnattainable(look_ahead);
               }
            }
         } else {
            make_LR1Table();
         }
      } else if (syntax_mode == A_Syntax::smParseLR0_Core) {
//         make_C2Aa_LR(syntax_mode);
         make_LR0Core();
      } else if (syntax_mode == A_Syntax::smParseLR1_Core) {
         if (look_ahead > 0) {
            make_LRkCore(look_ahead);
         } else {
            make_C2Aa_LR(syntax_mode);
         }
      } else if (syntax_mode == A_Syntax::smParseLALR) {
         if (look_ahead > 0) {
            make_LALRkTable(look_ahead);
         } else {
            make_LALRTable();
         }
      } else if (syntax_mode == A_Syntax::smParseLALR_Core) {
         if (look_ahead > 0) {
            make_LALRkCore(look_ahead);
         } else {
            make_C2Aa_LALR();
         }
      } else { // smParseLALR_Tab | smParseLALR_Full
         if (look_ahead > 0) {
            make_LALRk_FullTable(syntax_mode, look_ahead);
         } else {
            make_LALR_FullTable(syntax_mode);
         }
      }
      if (grammar->option & TGrammar::POption::opCompression) {
         LRtable.Compression();
      }
      if (LRtable.duplicate) printf("\nDuplicate: %d\n", LRtable.duplicate);
      if (LRtable.warning) printf("\nWarning: %d\n", LRtable.warning);
//      if (Stable.invalid) printf("\nInvalid: %d\n", Stable.invalid);
      grammar->grammar_type();
      file_tab = get_file_name(file, "tab");
      TPrinter writer_simple(file_tab, T_PrintMode::pmWriteSimple);
      grammar->write_LR(writer_simple);
      int option_state = 0x0000, option_action = 0x0000;
      if (grammar->option & TGrammar::POption::opTable) {
         file_cpp = get_file_name(file,"cpp");
         TPrinter writer_LR(file_cpp, T_PrintMode::pmWriteProg);
         grammar->write_LR(writer_LR);
      }
      if (grammar->option & TGrammar::POption::opEof2Empty) {
         option_state |= T_PrintMode::pmEofToEmpty; option_action |= T_PrintMode::pmEofToEmpty;
      }
      if (grammar->option & TGrammar::POption::opState) {
         option_state |= T_PrintMode::pmCompactGroup; // compact
         if (!(grammar->option & TGrammar::POption::opStateSort)) option_state |= T_PrintMode::pmSortMode;
         if   (grammar->option & TGrammar::POption::opStateCore)  option_state |= T_PrintMode::pmBasic;
         file_state  = get_file_name(file,"state");
         TPrinter printer(file_state, option_state);
         Stable.print(printer);
         option_state |= T_PrintMode::pmCompactGroup | T_PrintMode::pmSortMode | T_PrintMode::pmBasic;
         if (TablePrint.count()) {
            file_core  = get_file_name(file,"core");
            if (grammar->option & TGrammar::opSplitting) option_state &= ~T_PrintMode::pmBasic;
            TPrinter printer(file_core, option_state);
            TablePrint.print(printer);
         } else if (COREtable.count()) {
            file_core  = get_file_name(file,"core");
            TPrinter printer(file_core, option_state);
            COREtable.print(printer);
            }
         }
      Stable.Clear(); TablePrint.Clear(); COREtable.Clear();
      if (grammar->option & TGrammar::POption::opAction) {
         file_action = get_file_name(file,"action");
         TPrinter printer(file_action, T_PrintMode::pmNoPrintNone | T_PrintMode::pmPrintItem | option_action);
         LRtable.print(printer);
      }
      if (GOTOtable.count() && (grammar->option & TGrammar::POption::opGoTo)) {
         file_goto = get_file_name(file,"goto");
         TPrinter printer(file_goto, T_PrintMode::pmNoPrintNone | T_PrintMode::pmPrintItem);
         GOTOtable.print(printer);
      }
      if (CtoAa.size() && (grammar->option & TGrammar::POption::opC2A)) {
         file_C2A = get_file_name(file,"c2a");
         TPrinter printer(file_C2A, T_PrintMode::pmCompactGroup | T_PrintMode::pmSortMode | T_PrintMode::pmCompact);
         CtoAa.print(printer);
      }
      if (LookAhead.count() && (grammar->option & TGrammar::POption::opAhead)) {
         file_look = get_file_name(file,"look");
         TPrinter printer(file_look, T_PrintMode::pmCompact);
         LookAhead.print(printer);
      }
   } else if (syntax_mode == A_Syntax::smParseLL1) {
      if (look_ahead > 0) {

         int invalid = grammar->ValidLLk();
         if (invalid) printf("\nInvalid: %d\n", invalid);

         make_LLkTable(look_ahead);
      } else {
         make_LL1Table();
      }
      grammar->grammar_type();
      file_tab = get_file_name(file, "tab");
      TPrinter writer_simple(file_tab, T_PrintMode::pmWriteSimple);
      grammar->write_LL(writer_simple);
      if (grammar->option & TGrammar::POption::opCell) {
         file_cell = get_file_name(file,"cell");
         TPrinter printer(file_cell, T_PrintMode::pmProduceHead | T_PrintMode::pmNoPrintNone | T_PrintMode::pmPrintItem | ((grammar->option & TGrammar::POption::opEof2Empty) ? T_PrintMode::pmEofToEmpty : T_PrintMode::pmNone));
         Mtable.print(printer);
      }
      if (grammar->option & TGrammar::POption::opTable) {
         file_cpp = get_file_name(file,"cpp");
         TPrinter writer_LL(file_cpp, T_PrintMode::pmWriteProg);
         grammar->write_LL(writer_LL);
      }
   }
   if (file_state)  free(file_state);
   if (file_action) free(file_action);
   if (file_cell)   free(file_cell);
   if (file_cpp)    free(file_cpp);
   if (file_goto)   free(file_goto);
   if (file_core)   free(file_core);
   if (file_look)   free(file_look);
   if (file_C2A)    free(file_C2A);
   if (file_tab)    free(file_tab);
   return ret;
}

bool TGrammar::Make(int make_type, const char* file)
{
   int def_rule_mode = ((make_type & 0xF00) >> 8); // 0 - LL, 1 - NL, 2 - LR, 3 - NR
   A_Syntax::M_Mode make_mode = A_Syntax::M_Mode((make_type & 0x0F0) >> 4);
   A_Syntax::T_SyntaxMode syntax_mode = A_Syntax::T_SyntaxMode(make_type & 0x00F);
   bool ret = true;
   TGrammarBuilder my_builder(this, file);
   builder = &my_builder;

   Used();

   filter_makers(make_mode, ((def_rule_mode == 2) && (option & TGrammar::POption::opSplitting)) ? 0x01 : 0x00); // 0x01 - !Code

   if ((syntax_mode >= A_Syntax::smParseLL1) && (syntax_mode <= A_Syntax::smParseLALR_Core)) {
      if (syntax_mode >= A_Syntax::smParseLR0) {
         make_makers_head(true);
      }

      int mode_FEFS = 0x00;
      if (look_ahead > 0) {
         if ((syntax_mode == A_Syntax::smParseLR1) && (option & TGrammar::opSplitting) && (option & TGrammar::opSplittingAddition)) {
            mode_FEFS = -1;
         } else if (syntax_mode == A_Syntax::smParseLL1) {
            mode_FEFS = 0x01;
         }
      }
      if (mode_FEFS >= 0) {
         make_FEFS(mode_FEFS);
      }

      my_builder.Make(syntax_mode, file);

   } else if (syntax_mode == A_Syntax::smNone) {
      char* file_tab = NULL;
      grammar_type();
      file_tab = get_file_name(file, "tab");
      TPrinter writer_simple(file_tab, T_PrintMode::pmWriteSimple);
      if (type & T_Grammar::gtLL) {
         write_LL(writer_simple);
      } else if (type & T_Grammar::gtLR) {
         write_LR(writer_simple);
      }
      if (file_tab) free(file_tab);
   }

   return true;
}

#undef ACTION 
#define ACTION(MODE) (make_mode == A_Syntax::M_Mode::mm##MODE)

bool TGrammar::Print(int type, const char* file)
{
   bool ret = true;
   A_Syntax::M_Mode make_mode = A_Syntax::M_Mode((type & 0x0F0) >> 4);
   A_Syntax::T_SyntaxMode syntax_mode = A_Syntax::T_SyntaxMode(type & 0x00F);

   if (syntax_mode == A_Syntax::smParseYACC) {
      if (ACTION(Node) || ACTION(Made)) {
         TPrinter printer(file, T_PrintMode::pmYACCMode | T_PrintMode::pmYACCStack);
         YACC(printer);
      } else {
         TPrinter printer(file, T_PrintMode::pmYACCMode);
         YACC(printer);
      }
   } else if (syntax_mode == A_Syntax::smParseFormula) { // DEFINE_GRAMMAR_(LL,NL)
      PROG(file, T_PrintMode::pmCompact);
   }
   
   if (option & TGrammar::POption::opLexeme) {
      char *file_lexeme = get_file_name(file, "lexeme");
      TPrinter printer(file_lexeme, T_PrintMode::pmLexemePart);
      lexemes.print(printer);
      free(file_lexeme);
   }

   if ((option & TGrammar::POption::opMaker) && (make_mode != M_Syntax::mmNone)) {
      char *file_make = get_file_name(file, "make");
      TPrinter printer(file_make, T_PrintMode::pmMakerItem);
      makers->print(printer);
      free(file_make);
   }

   if (option & TGrammar::POption::opGrammar) {
      char *file_grammar = get_file_name(file, "grammar");
      TPrinter printer(file_grammar, T_PrintMode::pmGrammar | T_PrintMode::pmCompactGroup |
         ((option & TGrammar::opBNF) ? T_PrintMode::pmBNF : 0) |
         ((option & TGrammar::opBIF) ? (T_PrintMode::pmBIF /*| T_PrintMode::pmCompact*/) : 0), this);
      print(printer);
      free(file_grammar);
   }

   int print_F_F_E = T_PrintMode::pmSpaces | T_PrintMode::pmMultiLine | T_PrintMode::pmOffset;
   if (option & TGrammar::POption::opFirst) {
      char *file_first = get_file_name(file, "first");
      TPrinter printer(file_first, print_F_F_E); printer.title = "FIRSTs";
      FIRSTs.print(printer);
      free(file_first);
   }
   if (option & TGrammar::POption::opFollow) {
      char *file_follow = get_file_name(file, "follow");
      TPrinter printer(file_follow, print_F_F_E); printer.title = "FOLLOWs";
      FOLLOWs.print(printer);
      free(file_follow);
   }
   if ((look_ahead > 0) && (option & TGrammar::POption::opEFF)) {
      char *file_eff = get_file_name(file, "eff");
      TPrinter printer(file_eff, print_F_F_E); printer.title = "EFFs";
      EFFs.print(printer);
      free(file_eff);
   }
   if (option & TGrammar::POption::opFormula) {
      char *file_formula = get_file_name(file,"formula");
      TPrinter printer(file_formula, T_PrintMode::pmProduceHead | T_PrintMode::pmPrintItem); 
      print(printer);
      free(file_formula);
   }
   if (option & TGrammar::POption::opOutput) {
      char *file_output = get_file_name(file, "output");
      TPrinter printer(file_output, 0x00);
      output(printer);
      free(file_output);
   }

   if (option & TGrammar::POption::opAuto) {
      char *file_auto = get_file_name(file, "auto");
      TPrinter printer(file_auto, 0x00);
      AUTO(printer);
      free(file_auto);
   }

   return ret;
}

int T_Lexeme::YACC(TPrinter& printer)
{
   PRINTER_FILE_MODE
   int len = 0;
   const char* title = group_title(group);
	fprintf(file, "%s", title);     len += (int)strlen(title);
   if ((group == grOper) || (group == grSeparator)) {
      title = lexeme_type_title((T_Symbol::T_Type)type);
   	fprintf(file, "_%s", title); len += (int)strlen(title) + 1;
   } else if (group == grReserv) {
   	title = lexeme_word_title((T_Lexeme::W_Type)type);
   	fprintf(file, "_%s", title); len += (int)strlen(title) + 1;
   } else if (group == grPriority) {
   	title = lexeme_priority_title((T_Symbol::T_Priority)type);
   	fprintf(file, "_%s", title); len += (int)strlen(title) + 1;
   } else if (group == grSyntax) {
   	title = lexeme_syntax_title((T_Lexeme::T_Syntax)type);
   	fprintf(file, "_%s", title); len += (int)strlen(title) + 1;
   } else {
   	fprintf(file, "_lexeme"); len += 7;
   }
   return len;
}

void tree_syn(int s, int &s1, int &s2, int &s3, int &s4, int &s5); 
int GSymbol::YACC(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   int len = 0;
   if (type == gsTerminal) {
      T_Lexeme lexeme(T_Lexeme::T_Group(group), lexeme_type);
      len += lexeme.YACC(printer);
   } else if (type == gsFormula) {
      const GFormula& f = *grammar->formulas[formula];
      TPrinter printer_title(printer, T_PrintMode::pmNone);
      len += f.write_title(printer_title);
   } else if (type == gsMaker) {
      len += print_maker(printer);
   } else if  (type == gsEmpty) {
      fprintf(file, "/* empty */");
   } else {
      const char* title = symbol_title(type);
	   fprintf(file, "%s", title); len += (int)strlen(title);
   }
   printer.trail(len,TPrinter::trLen);
   return len;
}

void TLexemeSet::YACC(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   for (const std::pair<const GSymbol&, int> item : *this) {
      const GSymbol& sym = item.first;
      if (print_mode & T_PrintMode::pmBNF) {
         if ((sym.group != T_Lexeme::grSyntax) && (sym.group != T_Lexeme::grIdent) && (sym.group != T_Lexeme::grInteger) && (sym.group != T_Lexeme::grNumber)) continue;
      }
      if (((grammar->option & TGrammar::POption::opAssociation) != 0) && (sym.group == T_Lexeme::grPriority)) {
         if ((sym.lexeme_type >= T_Symbol::prOrOr) && (sym.lexeme_type <= T_Symbol::prFactor)) {
            fprintf(file, "\n%%left  ");
         } else if (sym.lexeme_type == T_Symbol::prAssign) {
            fprintf(file, "\n%%right ");
         } else {
            fprintf(file, "\n%%token ");
         }
      } else {
         fprintf(file, "\n%%token ");
      }
      sym.YACC(printer);
      int token = (sym.group << 8) | sym.lexeme_type;
      fprintf(file, " %5d // %#06X",token,token);
   }
   printer.eol(); 
}

void GMakerTable::YACC(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   fprintf(file, "\nenum class T_Maker { ");
   int m = 0;
   for (const GMaker* maker : *this) {
      if (m) fprintf(file, ", ");
      if (m && !(m % 8)) fprintf(file, "\n                     ");
      fprintf(file, "%s", maker->title);
      m++;
   } 
   fprintf(file, "\n};\n\n");
}

void SNode::YACC(TPrinter& printer)
{
   PRINTER_FILE_MODE
   fprintf(file, "\nenum class S_Node  { ");
   int m = 0;
   for (int t = stNone; t <= stItem; t++) {
      if (m) fprintf(file, ", ");
      if (m && !(m % 8)) fprintf(file, "\n                     ");
      fprintf(file, "%s", snode_title((SNode::S_Type)t));
      m++;
   } 
   fprintf(file, "\n};\n\n");
}

void TGrammar::YACC(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_THIS
   static const char *offset = "                         ";
   static const int len_offset = (int)strlen(offset);
   fprintf(file, "%%{\n");
   makers->YACC(printer);
   SNode::YACC(printer);
   fprintf(file, "#define YYPARSE_PARAM parm\n");
   fprintf(file, "#define YYLEX_PARAM parm\n");
   fprintf(file, "#define YYERROR_VERBOSE\n");
   fprintf(file, "#define YYSTYPE T_Lexeme_SNode\n");
   fprintf(file, "%%}\n");
   fprintf(file, "%%pure_parser\n");
   fprintf(file, "%%name-prefix=\"yy_\"\n");
   fprintf(file, "%%no-lines\n");
   fprintf(file, "%%debug\n");
   lexemes.YACC(printer);
   fprintf(file, "%%%%\n");
   bool syntax_tree = (print_mode & T_PrintMode::pmYACCStack) != 0;
   const GFormula* start_formula = NULL;
   for (const GFormula* my_formula : formulas) {
      const GFormula* formula;
      if (!start_formula) {
         const GSymbol& start_sym = my_formula->front().front();
         formula = start_formula = &Formula(start_sym);
      } else {
         formula = my_formula;
         if (formula == start_formula) continue;
      }

      int len = 0;
      printer.eol(); 
      TPrinter printer_head(printer, T_PrintMode::pmCompact);
      len += formula->head.YACC(printer_head) + 1; fprintf(file, ":");
      while (len++ < len_offset) fprintf(file, " ");
      const char *seporator = "   ";
      for (const GProduce& produce : *formula) {
         fprintf(file, "%s", seporator);
         int item = 0;
         for (const GSymbol& sym : produce) {
            len = sym.YACC(printer);
            printer.trail(len, TPrinter::trSkip);
            item++;
            if (!syntax_tree && (sym.type == GSymbol::gsTerminal) && (sym.IsSaved())) {
               fprintf(file, "{ SAVE($%d); }", item); item++;
               len = 13; printer.trail(len);
            }
         }
         if (!produce.maker.IsNone()) {
            produce.maker.YACC(printer);
         }
         fprintf(file, "\n%s", offset);
         seporator = " | ";
      }
      fprintf(file, " ;\n");
   }
   fprintf(file, "%%%%\n");
}

void write_offset(FILE *file, int level)
{
   fprintf(file,"\n");
   while (level--) fprintf(file, "   ");
}

int GSymbol::MACRO(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   static char buffer[20] = {};
   int len = 0;
   if (type == gsTerminal) {
      const char* title = "", *macro = "";
      if (group == T_Lexeme::grOper) {
         macro = "OPER";
         title = lexeme_type_title((T_Symbol::T_Type)lexeme_type);
      } else if (group == T_Lexeme::grSeparator) {
         macro = "SYM";
         title = lexeme_type_title((T_Symbol::T_Type)lexeme_type);
      } else if (group == T_Lexeme::grReserv) {
         macro = "WORD";
      	title = lexeme_word_title((T_Lexeme::W_Type)lexeme_type);
      } else if (group == T_Lexeme::grPriority) {
         macro = "PRIOR";
      	title = lexeme_priority_title((T_Symbol::T_Priority)lexeme_type);
      } else if (group == T_Lexeme::grSyntax) {
         macro = "GROUP";
      	title = lexeme_syntax_title((T_Lexeme::T_Syntax)lexeme_type);
      } else {
         macro = "LEX";
         title = group_title((T_Lexeme::T_Group)group);
      }
      fprintf(file, "%s", macro); len += (int)strlen(macro);
     	fprintf(file, "(%s)", title); len += (int)strlen(title) + 2;
   } else if (type == gsFormula) {
      if (mode & GSymbol::Master) {
         fprintf(file, "MASTER"); len += 6;
         printer.trail(len);
         return len;
      }
      if (print_mode & T_PrintMode::pmFormulaHead) {
         fprintf(file, "FORMULA("); len += 8;
      } else {
         fprintf(file, "RULE("); len += 5;
      } 
      const GFormula& f = *grammar->formulas[formula];
      TPrinter printer_title(printer, T_PrintMode::pmNone);
      len += f.write_title(printer_title);
      fprintf(file, ")"); len += 1;
   } else if  (type == gsMaker) {
      if (param && !(print_mode & T_PrintMode::pmParamMacro) && !(mode & (GSymbol::SNode | GSymbol::Turn))) {
         SPRINTF(buffer,"%d",param);
         TPrinter printer_maker(printer, print_mode | T_PrintMode::pmParamMacro | T_PrintMode::pmCompact);
         fprintf(file, "PARAM("); len += MACRO(printer);
         fprintf(file, ",%s)", buffer); len += 8 + (int)strlen(buffer);
         printer.trail(len);
         return len;
      }
      len += print_maker(printer);
   } else if  (type == gsEmpty) {
      fprintf(file, "EMPTY"); len += 5;
   } else {
      const char* title = symbol_title(type);
	   fprintf(file, "%s", title); len += (int)strlen(title);
   }
   printer.trail(len);
   return len;
}

void TGrammar::MACRO(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_THIS
   print_mode |= 0x04;
   TPrinter printer_head(printer, print_mode | T_PrintMode::pmFormulaHead);
   for (const GFormula* formula : formulas) {
      int len = 0;
      write_offset(file, 1); len += formula->head.MACRO(printer_head);
      for (const GProduce& produce : (*formula)) {
         int len = 0;
         write_offset(file, 2);
         fprintf(file, "PRODUCE "); len += 8;
         printer.trail(len);
         for (const GSymbol& sym : produce) {
            fprintf(file, " "); len += sym.MACRO(printer);
         }
         if (produce.maker.IsMaker()) {
            fprintf(file, " "); len += produce.maker.MACRO(printer);
         }
         fprintf(file, " END");
      }
      write_offset(file, 1); fprintf(file, "END\n");
   }
}

int GSymbol::PROG(TPrinter& printer) const
{
   PRINTER_FILE_GRAMMAR
   static char buffer[20] = {};
   int len = 0;
   if (type == gsTerminal) {
      const char* title = "", *macro = "";
      if (group == T_Lexeme::grOper) {
         macro = "T_Lexeme::grOper,T_Symbol::T_Type::lx";
         title = lexeme_type_title((T_Symbol::T_Type)lexeme_type);
      } else if (group == T_Lexeme::grSeparator) {
         macro = "T_Lexeme::grSeparator,T_Symbol::T_Type::lx";
         title = lexeme_type_title((T_Symbol::T_Type)lexeme_type);
      } else if (group == T_Lexeme::grReserv) {
         macro = "T_Lexeme::W_Type::rw";
      	title = lexeme_word_title((T_Lexeme::W_Type)lexeme_type);
      } else if (group == T_Lexeme::grPriority) {
         macro = "T_Symbol::T_Priority::pr";
      	title = lexeme_priority_title((T_Symbol::T_Priority)lexeme_type);
      } else if (group == T_Lexeme::grSyntax) {
         macro = "T_Lexeme::T_Syntax::sx";
      	title = lexeme_syntax_title((T_Lexeme::T_Syntax)lexeme_type);
      } else {
         macro = "T_Lexeme::T_Group::gr";
         title = group_title((T_Lexeme::T_Group)group);
      }
      fprintf(file, "Match(%s%s)", macro, title); len += (int)strlen(macro) + (int)strlen(title) + 7;
   } else if (type == gsFormula) {
      const GFormula& f = *grammar->formulas[formula];
      TPrinter printer_prefix(printer, T_PrintMode::pmPrintPrefix);
      len += f.write_title(printer_prefix);
      fprintf(file, "()"); len += 1;
   } else if  (type == gsMaker) {
      const char *func_title = maker_title(maker), *maker_mode = "", *make_title;
      if (param) {
         make_title = "PARAM";
         SPRINTF(buffer,",%d",param);
      } else {
         make_title = "MAKE";
         buffer[0] = 0x00;
      }
      if ((mode & GSymbol::Tree) && (mode & GSymbol::Code) && (mode & GSymbol::Yacc))
         maker_mode = "_ALL";
      else if ((mode & GSymbol::Tree) && !(mode & GSymbol::Code))
         maker_mode = "_TREE";
      else if ((mode & GSymbol::Code) && !(mode & GSymbol::Tree))
         maker_mode = "_CODE";
      else if (mode & GSymbol::Yacc)
         maker_mode = "_YACC";
	   fprintf(file, "%s%s(%s%s)",make_title , maker_mode, func_title, buffer); 
      len += 2 + (int)strlen(make_title) + (int)strlen(maker_mode) + (int)strlen(func_title) + (int)strlen(buffer);
   } else if  (type == gsEmpty) {
      fprintf(file, "true"); len += 4;
   } else {
      const char* title = symbol_title(type);
	   fprintf(file, "%s", title); len += (int)strlen(title);
   }
   printer.trail(len);
   return len;
}

void GProduce::PROG(TPrinter& printer, int print_mode) const
{
   PRINTER_FILE_GRAMMAR
   TPrinter printer_prefix(printer, T_PrintMode::pmPrintPrefix);
   if (print_mode == T_PrintMode::pmProgCall) { // call
      const GFormula& formula = grammar->Formula(head);
      formula.write_title(printer_prefix);
      fprintf(file, "_%d()",head.produce);
   } else if (print_mode == T_PrintMode::pmProgHeader) { // *.h
      const GFormula& formula = grammar->Formula(head);
      fprintf(file, "   int ");
      formula.write_title(printer_prefix);
      fprintf(file, "_%d(); ",head.produce);
   } else { // body
      bool yes_list = (print_mode == T_PrintMode::pmProgList), yes_ret = false;
      for (const GSymbol& item : *this) {
         if (item.IsTerminal()) { yes_ret = false; break; };
         if (item.IsFormula())  { yes_ret =  true; break; }
      }
      const GFormula& formula = grammar->Formula(head);
      fprintf(file, "int PSyntax::");
      formula.write_title(printer_prefix);
      fprintf(file, "_%d()\n{\n",head.produce);
      if (yes_ret) fprintf(file, "   int s_ret;\n");
      bool first = true;
      int row = 0;
      for (const GSymbol& item : *this) {
         if ((++row == count()) && yes_list) continue;
         if (item.IsEmpty()) continue;
         if (item.IsMaker()) {
            fprintf(file, "   ");
            item.PROG(printer);
            fprintf(file, ";\n");
//            first = false;
         } else {
            fprintf(file, "   if (");
            if (first && yes_ret) fprintf(file, "(s_ret = ");
            if (item.IsTerminal()) fprintf(file, "!");
            item.PROG(printer);
            if (first) {
               first = false;
               if (item.IsTerminal()) {
                  fprintf(file, ") return -1;\n");
               } else {
                  fprintf(file, ") <= 0) return s_ret;\n");
               }
            } else {
               if (item.IsTerminal()) {
                  fprintf(file, ") return 0;\n");
               } else {
                  fprintf(file, " <= 0) return 0;\n");
               }
            }
         }
      }
      if (maker.IsMaker()) {
         fprintf(file, "   ");
         maker.PROG(printer);
         fprintf(file, ";\n");
      }
      fprintf(file, "   return 1;\n}\n");
   }
}

void GFormula::PROG(TPrinter& printer, int print_mode) const
{
   PRINTER_FILE_GRAMMAR
   TPrinter printer_prefix(printer, T_PrintMode::pmPrintPrefix);
   bool yes_list = ((count() == 2) && back().IsEmpty() && front().back().IsMaster());

   if (print_mode == T_PrintMode::pmProgHeader) { // *.h
      for (const GProduce& produce : (*this)) {
         produce.PROG(printer, T_PrintMode::pmProgHeader);
         if (yes_list) break;
      }
      printer.eol();

      fprintf(file, "   int ");
      write_title(printer_prefix);
      fprintf(file, "();\n");
   } else { // *.cpp T_PrintMode::pmProgBody
      fprintf(file, "\n// -------------------- ");
      write_title(printer_prefix);
      fprintf(file, " --------------------\n");

      for (const GProduce& produce : (*this)) {
         produce.PROG(printer, (yes_list ? T_PrintMode::pmProgList : T_PrintMode::pmProgBody)); // body
         if (yes_list) break;
      }

      fprintf(file, "int PSyntax::");
      write_title(printer_prefix);
      fprintf(file, "()\n{\n");

      if (yes_list) {
         fprintf(file,"   int p_ret;\n   while ((p_ret = ");
         front().PROG(printer, T_PrintMode::pmProgCall); // call
         fprintf(file,") > 0);\n   return (!p_ret ? 0 : 1);\n");
      } else {
         fprintf(file,"   int f_ret = 0, p_ret;\n");
         fprintf(file,"   T_ScanStore store; Store(store);\n");
         int row = 0;
         for (const GProduce& produce : (*this)) {
            fprintf(file, "   if ((p_ret = ");
            produce.PROG(printer, T_PrintMode::pmProgCall); // call
            fprintf(file, ") > 0) return 1; else f_ret += p_ret;\n");
            fprintf(file,"   Restore(store);\n");
         }
         fprintf(file, "   return ((f_ret == -%d) ? -1 : 0);\n",count());
      }
      fprintf(file, "}\n");
   }
}

void TGrammar::PROG(const char* title, int print_mode) const
{
   char *file_h = get_file_name(title,"h");
   TPrinter printer(file_h, print_mode, this);
   FILE* &file = printer.file;
   if (file == NULL) return;
   free(file_h);
   fprintf(file, 
   "class PSyntax : public P_Syntax {"
   "\npublic:"
	"\n   PSyntax(T_Scan *s, TGrammar* g) :P_Syntax(s,g) {}"
   "\n   virtual int translate() { return ");
   TPrinter printer_prefix(printer, T_PrintMode::pmPrintPrefix);
   (*formulas.front()).write_title(printer_prefix); fprintf(file, "(); }\n");
   fprintf(file, "public:\n");
   for (const GFormula* formula : formulas) {
      formula->PROG(printer, T_PrintMode::pmProgHeader);
   }
   fprintf(file, "};\n");

   char *file_cpp = get_file_name(title,"cpp");
   printer.reset(file_cpp);
   free(file_cpp);
   if (file == NULL) return;
   for (const GFormula* formula : formulas) {
      formula->PROG(printer, T_PrintMode::pmProgBody);
   }
}

void TGrammar::AUTO(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_THIS
   fprintf(file, "enum %sAutoType {", prefix );
   int paragraph = 0;
   TPrinter printer_prefix(printer, T_PrintMode::pmPrintPrefix);
   for (const GFormula* formula : formulas) {
      if (!(paragraph++ % 16)) {
         printer.eol(); fprintf(file, "   ");
      }
      formula->write_title(printer_prefix); 
      if (paragraph < count()) fprintf(file, ", ");
   }
   fprintf(file, "\n};\n");

   fprintf(file, "\n   switch(type) {\n");
   for (const GFormula* formula : formulas) {
      fprintf(file, "\n   case ");
      formula->write_title(printer_prefix);
      fprintf(file, ": {\n");
      fprintf(file, "      } break;\n");
   }
   fprintf(file, "   default: {\n      } break;\n   }\n");
}


void TGrammar::write_LL(TWriter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_THIS
   if ((print_mode != T_PrintMode::pmWriteSymbol) && (print_mode != T_PrintMode::pmWriteProg)) fprintf(file, "%d\n", T_Grammar::gtLL | ((look_ahead > 0) ? 0x04 : 0));
   builder->Mtable.write(printer);
   write(printer);
   if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) {
      if (look_ahead > 0) {
         fprintf(file, "\nvoid make_references(TGrammar& grammar)\n{"); 
         if (!references.empty()) {
            fprintf(file, "\nstd::vector<int> I = {");
            int i = 0; for (int ref : references) { fprintf(file, "%d", ref); if (++i < (int)references.size()) fprintf(file, ","); }
            fprintf(file, " };\ngrammar.references = I;");
         }
         fprintf(file, "\n}\n");
      }
      fprintf(file, "\nvoid make_grammar(TGrammar& grammar) { make_cells(grammar); make_formulas(grammar); make_vectors(grammar);");
      if (look_ahead > 0) {
         fprintf(file, " make_references(grammar);");
      }
      fprintf(file, " }\n");
   } else if (look_ahead > 0) {
      fprintf(file, "%d\n", (int)references.size());
      for (int ref : references) { fprintf(file, "%d ", ref); }
   }
}

void TGrammar::write_LR(TWriter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_THIS
   if ((print_mode != T_PrintMode::pmWriteSymbol) && (print_mode != T_PrintMode::pmWriteProg)) fprintf(file, "%d\n",T_Grammar::gtLR);
   builder->LRtable.write(printer);
   write(printer);
   if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) {
      if (look_ahead > 0) {
         fprintf(file, "\nvoid make_references(TGrammar& grammar)\n{");
         if (!references.empty()) {
            fprintf(file, "\nstd::vector<int> I = {");
            int i = 0; for (int ref : references) { fprintf(file, "%d", ref); if (++i < (int)references.size()) fprintf(file, ","); }
            fprintf(file, " };\ngrammar.references = I;");
         }
         fprintf(file, "\n}\n");
      }
      fprintf(file, "\nvoid make_grammar(TGrammar& grammar) { make_actions(grammar); make_formulas(grammar); make_vectors(grammar);");
      if (look_ahead > 0) {
         fprintf(file, " make_references(grammar);");
      }
      fprintf(file, " }\n");
   } else if (look_ahead > 0) {
      fprintf(file, "%d\n", (int)references.size());
      for (int ref : references) { fprintf(file, "%d ", ref); }
   }
}

// ------------------------------ GrammarSplitting -------------------------------

// Green(v=2,7.4.3)
// Green(v=2,p=104,a=7.12)
bool TGrammarGroup::AddGrammar(const GSymbol& root)
{
   GSymbol addition(root);
   if (general->option & TGrammar::opSplittingAddition) {
      if (!general->IsStart(addition)) {
         GFormula *root_formula = new GFormula(GSymbol(GSymbol::gsFormula, general->formulas.count()));
         GProduce root_produce(GSymbol(GSymbol::gsProduce, root_formula->head.formula));
         root_produce << addition;
         root_formula->Add(root_produce);
         addition = root_formula->head;
         general->formulas.push_back(root_formula);
      }
   }
   iterator ip = find(root);
   if (ip != end()) return false;
   std::pair<GSymbol, TGrammarGroupItem*> item(root, new TGrammarGroupItem());
   insert(item);
   ip = find(root);
   TGrammarGroupItem& grammar = *((*ip).second);
   grammar.formulas.Copy(general->formulas);
   if (general->option & TGrammar::opSplittingAddition) {
      grammar.S_ = addition;
   }
   grammar.root = grammar.formulas.root = grammar.formulas[addition.formula];
   grammar.general = general;
   grammar.look_ahead = general->look_ahead;
   grammar.option = general->option;
   return true;
}

void TGrammarGroup::FormulaToTerminal(GSymbol& sym)
{
   if (sym.IsFormula() && (find(sym) != end())) {
      sym.type = GSymbol::gsTerminal; sym.lexeme_type = sym.formula; sym.group = T_Lexeme::grGrammar;
   }
}

void TGrammarGroup::TerminalToFormula(GSymbol& sym)
{
   if (sym.IsTerminal() && (sym.group == T_Lexeme::grGrammar)) {
      sym.type = GSymbol::gsFormula; sym.formula = sym.lexeme_type; sym.produce = 0;
   }
}

void TGrammarGroup::Disclosure(const TSituationMap& from, TSituationMap& to) const
{
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < from.count(); situation.situation++) {
      const TParaSet& situation_items = *from.Get(situation);
      TParaSet* opened = new TParaSet(general);
      for (const TPara& para : situation_items) {
         if (para.IsPara()) {
//printf("\n"); para.GSymbol::print(general); printf(" -> "); para.print(general);
            (*opened) << para;
         } else { // situation
            TGrammarGroup::const_iterator ig = find(para.sym);
            const TGrammarGroupItem& item_grammar = *(*ig).second;
            const TParaSet* pointer = item_grammar.Stable.Get(para);
            if (general->option & TGrammar::opSplittingAddition) {
               for (const TPara& para_my : *pointer) {
//printf("\n"); para_my.GSymbol::print(general); printf(" -> "); para_my.print(general);
                  if (general->IsStart(para_my) || (para_my.formula != item_grammar.S_.formula) || (para_my.produce != item_grammar.S_.produce)) {
                     (*opened) << para_my;
                  }
               }
            } else {
               (*opened) << (*pointer);
            }
         }
      }
      to.Add(opened);
//printf("\n");
   }
}

void TGrammarGroup::Clear()
{
   for (std::pair<const GSymbol&, TGrammarGroupItem*> item : (*this)) {
      delete item.second;
   }
   clear();
}

void TGrammarGroup::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   for (std::pair<const GSymbol&, const TGrammarGroupItem*> item : (*this)) {
      TPrinter printer_item(printer);
      item.second->print(printer_item);
      int print_F_F_E = T_PrintMode::pmSpaces | T_PrintMode::pmMultiLine | T_PrintMode::pmOffset;
      TPrinter printer_FFE(printer, print_F_F_E);
      fprintf(file, "\nF I R S T:\n");
      item.second->FIRSTs.print(printer_FFE);
      fprintf(file, "\nE F F:\n");
      item.second->EFFs.print(printer_FFE);
      fprintf(file, "\nF O L L O W:\n");
      item.second->FOLLOWs.print(printer_FFE);
      int option_state = 0x0000; option_state |= T_PrintMode::pmSortMode;
      TPrinter printer_state(printer); printer_state.print_mode = option_state;
      item.second->Stable.print(printer_state);
      fprintf(file, "\nG O T O:\n");
      printer.print_mode = T_PrintMode::pmNoPrintNone | T_PrintMode::pmPrintItem;
      item.second->GOTOtable.print(printer);
      fprintf(file, "\nL E X E M E S:\n");
      item.second->lexemes.print(printer);
   }
   if (derivation) {
      fprintf(file, "\nD E R I V A T I O N:\n");
      derivation->print(printer);
   }
}
