#include "stdafx.h"

#include "Rules.h"
#include "Maker.h"
#include "Grammar.h"

int  TGrammar::Maker(const char* m) const
{
   return makers->Find(m);
}

const GMaker* TGrammar::Maker(int m) const
{
   return (*makers)[m];
}

GFormula* TGrammar::Find(const char* title) const
{
   for (GFormula* item : formulas) {
      if (!strcmp(item->title, title)) return item;
   }
   return NULL;
}

void TGrammar::Add(GFormula* f)
{
   formulas.push_back(f);
}

const GFormula& TGrammar::Formula(const GSymbol &sym) const
{
   const GFormula& formula = *formulas[sym.formula];
   return formula;
}

const GProduce& TGrammar::Produce(const GSymbol &sym) const
{
   if (sym.formula < 0) {
      return Produce(produces[sym.produce]);
   }
   const GFormula& formula = *formulas[sym.formula];
   const GProduce& produce = formula[sym.produce];
   return produce;
}

int TGrammar::Replace(const GSymbol &from, const GSymbol &to)
{
   int replace = 0;
   for (GFormula* formula : formulas) {
      for (GProduce& produce : (*formula)) {
         for (GSymbol& sym : produce) {
            if (sym == from) {
               sym = to; replace++;
            }
         }
      }
   }
   return replace;
}

const TAction& TGrammar::Action(TTableKey& key) const
{
   return LRtable.Action(key);
}

const GSymbol& TGrammar::Cell(const TTableKey& key) const
{
   return Mtable.Cell(key);
}

bool TGrammar::IsStart(const GSymbol& sym) const 
{
   if (!root || (sym.type != GSymbol::gsProduce) && (sym.type != GSymbol::gsFormula)) return false;
   return root->head.formula == sym.formula;
}

bool TGrammar::make_start()
{
   if (!root) return false;
   if (root->IsChain()) return false;
   GFormula *root_formula = new GFormula(GSymbol(GSymbol::gsFormula, formulas.count()));
   GProduce root_produce(GSymbol(GSymbol::gsProduce, root_formula->head.formula));
   root_produce << root->head;
   root_formula->Add(root_produce);
   formulas.push_back(root_formula);
   root = root_formula;
   return true;
}

void TGrammar::make_lexemes()
{
   for (GFormula* formula : formulas) {
      for (GProduce& produce : *formula) {
         for (GSymbol& sym : produce) {
            if (sym.IsTerminal()) {
               lexemes.Add(sym);
            }
         }
      }
   }
}

void TGrammar::makers_used() const
{
   for (const GFormula* formula : formulas) {
      for (const GProduce& produce : *formula) {
         for (const GSymbol& sym : produce) {
            if (sym.IsMaker()) {
               const GMaker* used;
               if (sym.IsMakerNode()) {
                  used = (const GMaker*)(*makers)[makers->maker_node];
               } else if (sym.IsMakerTurn()) {
                  used = (const GMaker*)(*makers)[makers->maker_turn];
               } else if (sym.IsMakerCall()) {
                  used = (const GMaker*)(*makers)[makers->maker_call];
               } else {
                  if (sym.maker < 0) continue; // unknown_maker
                  used = (const GMaker*)(*makers)[sym.maker];
               }
               used->used++;
            }
         }
      }
   }
}

bool TGrammar::make_produces()
{
   bool ret = true;
   produces.clear();
   for (GFormula* formula : formulas) {
      for (GProduce& produce : *formula) {
         produce.head.value = (int)produces.size();
         produces.push_back(produce.head);
      }
   }
   return ret;
}

bool TGrammar::filter_makers(int filter)
{
   bool ret = true;
   int maker_mode = ~(GSymbol::Tree | GSymbol::Code | GSymbol::Yacc | GSymbol::SNode | GSymbol::Turn) | filter;
   for (GFormula* formula : formulas) {
      for (GProduce& produce : *formula) {
         GProduce::iterator ip = produce.begin();
         while (ip != produce.end()) {
            GSymbol& sym = (*ip);
            if (sym.IsMaker()) {
               if (!(sym.mode & filter)) {
                  ip = produce.erase(ip);
               } else {
                  sym.mode &= maker_mode;
                  ip++;
               }
            } else {
               ip++;
            }
         }
      }
   }
   return ret;
}

#undef ACTION 
#define ACTION(MODE) (make_mode == A_Syntax::M_Mode::mm##MODE)

bool TGrammar::filter_makers(int make_mode, int mode) // 0x01 - !Code
{
   int filter = 0;
   if (ACTION(Tree) || ACTION(Code)) {
      filter |= (GSymbol::Tree);
      if (!(mode & 0x01)) filter |= (GSymbol::Code); // LR !Code
   } else if (ACTION(Node) || ACTION(Made)) {
      filter |= (GSymbol::SNode | GSymbol::Yacc);
   } else if (ACTION(Turn)) {
      filter |= (GSymbol::Turn);
   } else if (ACTION(Call)) {
      filter |= (GSymbol::Call);
   } else if (make_mode == 0x0f) {
      filter |= (GSymbol::Tree | GSymbol::Code | GSymbol::SNode | GSymbol::Yacc | GSymbol::Turn | GSymbol::Call);
   }
   return filter_makers(filter);

}

bool TGrammar::make_head_makers(bool reveal_vector)
{
   TPrinter printer(this);
   bool ret = true;
   for (GFormula* formula : formulas) {
      if (!formula->used) continue;
      for (GProduce& produce : *formula) {
         GProduce::iterator produce_ip = produce.begin();
         while (produce_ip != produce.end()) {
            GSymbol& sym = *produce_ip;
            if (sym.IsFormula()) {
               const GFormula& maker_formula = Formula(sym);
               if (maker_formula.count() == 1) {
                  const GProduce& maker_produce = maker_formula[0];
                  if (maker_produce.IsEmpty(false) && !maker_produce.maker.IsNone()) {
                     if (maker_produce.maker.IsMaker() || !reveal_vector && maker_produce.maker.IsVector()) {
                        sym = maker_produce.maker; 
                     } else { // reveal_vector
                        const GSymbolVector& makers = Vector(maker_produce.maker);
                        sym = makers[0]; // first in vector
                        for (int i = 1; i < makers.count(); i++) {
                           produce_ip = produce.insert(++produce_ip,makers[i]);
                        }
                     }
                     maker_formula.used--;
                  }
               }
            }
            produce_ip++;
         }
         if (!produce.maker.IsNone()) {
            if (produce.maker.IsMaker() || !reveal_vector && produce.maker.IsVector()) {
               produce.push_back(produce.maker);
            } else { // reveal_vector
               const GSymbolVector& makers = Vector(produce.maker);
               for (const GSymbol& maker : makers) {
                  produce.push_back(maker);
               }
            }
            produce.maker = GSymbol::none;
         }
      }
   }
   type = (T_Grammar)(type & ~T_Grammar::mtEmpty);
   return ret;
}

bool TGrammar::make_makers_head(bool group_maker)
{
   TPrinter printer(this);
   bool ret = true;
   int formulas_count = formulas.count();
   for (int f = 0; f < formulas_count; f++) {
      GFormula& formula = *formulas[f];
      BREAK_POINT_TITLE(formula.title,"int_body")
      BREAK_POINT_END
      GFormula::iterator fi = formula.begin();
      while (fi != formula.end()) {
         GProduce& produce = (*fi);
         GProduce::iterator ip = produce.begin();
         while (ip != produce.end()) {
            GSymbol& produce_sym = (*ip);
            GSymbol sym = produce_sym;
            if (sym.IsMaker()) {
               if (sym.maker < 0) {
                  printf("\nerror maker: "); formula.head.print(printer); printf(", ");
                  produce.head.print(printer); printf(", "); sym.print(printer); printf("\n");
                  ret = false;
                  break;
               }
               if (group_maker && !sym.IsMakerNode() && !sym.IsMakerYACC() && (ip < (produce.end() - 1))) {
                  GSymbolVector group_makers; 
                  GProduce::iterator group_ip = ip + 1;
                  while (group_ip != produce.end()) {
                     const GSymbol& group_sym = (*group_ip);
                     if (group_sym.IsMaker()) {
                        if (group_sym.maker < 0) {
                           printf("\nerror maker: "); formula.head.print(printer); printf(", ");
                           produce.head.print(printer); printf(", "); group_sym.print(printer); printf("\n");
                           ret = false;
                           break;
                        }
                        if (!group_sym.IsMakerNode() && !group_sym.IsMakerYACC()) {
                           if (group_makers.empty()) group_makers << sym;
                           group_makers << group_sym;
                           group_ip = produce.erase(group_ip);
                        } else {
                           break;
                        }
                     } else {
                        break;
                     }
                  }
                  if (!group_makers.empty()) {
                     sym = AddVector(group_makers);
                  }
               }
               if ((ip == (produce.end() - 1)) && produce.maker.IsNone()) {
                  produce.maker = sym;
                  ip = produce.erase(ip);
               } else {
                  bool yes_m_f = false;
                  for (int m_f = formulas_count; m_f < formulas.count(); m_f++) {
                     const GFormula& m_formula = *formulas[m_f];
                     const GProduce& m_produce = m_formula.front();
                     if ((m_produce.maker == sym) && (m_produce.maker.mode == sym.mode)) {
                        produce_sym = m_formula.head; m_formula.used++;
                        yes_m_f = true;
                        break;
                     }
                  }
                  if (!yes_m_f) {
                     GFormula *maker_formula = new GFormula(GSymbol(GSymbol::gsFormula, formulas.count()));
                     formulas.push_back(maker_formula);
                     GProduce maker_produce(GSymbol(GSymbol::gsProduce, maker_formula->head.formula));
                     maker_produce.maker = sym;
#ifdef PRODUCE_ITEM_EMPTY
                     maker_produce << GSymbol::empty;
#endif
                     maker_formula->Add(maker_produce);
                     produce_sym = maker_formula->head; maker_formula->used++;
                  }
                  ip++;
               }
            } else {
               ip++;
            }
         }
         fi++;
      }
   }
   type = (T_Grammar)(type | T_Grammar::mtEmpty);
   return ret;
}

class TProduceSet
{
public:
   TProduceSet() {}
   bool Add(GProduce* key);
public:
   int  count() const { return (int)set.size(); }
public:
   struct Key {
      Key(GProduce *p) :key(p) {}
      bool operator == (const Key& k) const { return *(GSymbolVector*)key == *(GSymbolVector*)k.key; }
      bool operator <  (const Key& k) const { return *(GSymbolVector*)key < *(GSymbolVector*)k.key; }
   public:
      GProduce *key;
   };
   std::set<Key> set;
};

bool TProduceSet::Add(GProduce* key)
{
   std::set<Key>::const_iterator ip = set.find(Key(key));
   if (ip != set.end()) {
      return false;
   }
   set.insert(key);
   return true;
}

// Purple(p=278,a=4.10,4.3.4)
// Green(v=1,p=385)
bool TGrammar::make_LeftFactoring()
{
   TPrinter printer(this);
   bool ret = true;
   for (int f = 0; f < formulas.count(); f++) {
      bool yes_change = false;
      GFormula* formula = formulas[f];
      if (formula->count() == 1) continue;
      TProduceSet p_set;
      for (int i = 0; i < formula->count(); i++) {
         GProduce& produce = (*formula)[i];
         produce.prepare_mask = 0x00;
         p_set.Add(&produce);
      }

      std::vector<GProduce*> arr;
      for (TProduceSet::Key item : p_set.set) {
         arr.push_back(item.key);
      }
      std::vector<int> equs;
      int equ_max = 0, arr_max = 0;
      for (int i_arr = 0; i_arr < (int)arr.size() - 1; i_arr++) {
         const GProduce& one = *arr[i_arr], two = *arr[i_arr + 1];
         int equ = 0;
         while ((equ < one.count()) && (equ < two.count())) {
            if (!(one[equ] == two[equ])) break;
            equ++;
            if (equ > equ_max) { equ_max = equ; arr_max = i_arr; }
         }
         equs.push_back(equ);
      }
      if (!equ_max) continue;

      yes_change = true;
      int beg = arr_max, end = beg, p = 0;
      for (end = beg + 1; (end < (int)equs.size()) && (equs[end] == equ_max); end++);
      printf("\n"); formula->head.print(printer); printf("equ_max=%d, beg=%d, end=%d", equ_max, beg, end);
      GFormula *left_formula = new GFormula(GSymbol(GSymbol::gsFormula, formulas.count()));
      for (int i = beg; i <= end; i++) {
         GProduce new_produce(GSymbol(GSymbol::gsProduce, left_formula->head.formula));
         new_produce.head.produce = p++;
         GProduce* old = arr[i];
         for (int s = equ_max; s < old->count(); s++) {
            new_produce << (*old)[s];
         }
         left_formula->Add(new_produce);
         if (i == beg) {
            GProduce::iterator ip = old->begin() + equ_max;
            while (ip != old->end()) ip = old->erase(ip);
            (*old) << left_formula->head;
            left_formula->used++;
         } else {
            old->clear();
            old->prepare_mask = 0x01; // delete
         }
      }
      int index_equ;
      if (formulas.Find(*left_formula, index_equ)) {
         GProduce* old = arr[beg];
         GFormula *equ_formula = formulas[index_equ];
         old->back() = equ_formula->head;
         equ_formula->used++;
         delete left_formula;
      } else {
         formulas.push_back(left_formula);
      }
      p = 0;
      GFormula::iterator ip = formula->begin();
      while (ip != formula->end()) {
         if ((*ip).prepare_mask == 0x01) {
            ip = formula->erase(ip);
         } else {
            (*ip).head.produce = p++;
            ip++;
         }
      }
      f--;
   }
   return ret;
}

// Purple(p=277,a=4.8,4.3.3)
// Green(v=1,p=180,a=2.13,2.4.4)
bool TGrammar::delete_LeftRecursion()
{
   bool ret;
   if (ret = formulas.delete_left_recursion()) {
      int filter = (GSymbol::Tree | GSymbol::Code | GSymbol::Turn);
      filter_makers(filter);
      make_LeftFactoring();
   }
   return ret;
}

void TGrammar::write(TWriter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_THIS
      if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) {
         fprintf(file, "\nvoid make_formulas(TGrammar& grammar)\n{\n");
         fprintf(file, "grammar.type = T_Grammar(%d); grammar.look_ahead = %d;\n", type, look_ahead);
      } else {
         fprintf(file, "%d %d\n", type, look_ahead);
      }
   formulas.write(printer);
   if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) {
      fprintf(file, "}\n");
   }
   Vectors().write(printer);
}

bool TGrammar::read(FILE* file, int print_mode)
{
   int _type; FSCANF(file, "%d %d", &_type, &look_ahead); type = (T_Grammar)_type;
   if (!formulas.read(file, T_PrintMode::pmWriteSimple)) return false;
   return Vectors().read(file, T_PrintMode::pmWriteSimple);
}

void TGrammar::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_THIS
      if (!(print_mode & T_PrintMode::pmGrammar)) {
         int produce_count = 0, item_count = 0, maker_count = 0, used_count = 0;
         for (const GFormula *formula : formulas) {
            FORMULA_DELETED_CONTINUE(formula);
            produce_count += formula->count();
            if (formula->used) used_count++;
            for (const GProduce& produce : *formula) {
               item_count += produce.count();
               if (!produce.maker.IsNone()) maker_count++;
               for (const GSymbol& item : produce) {
                  if (item.IsMaker()) maker_count++;
               }
            }
         }
         fprintf(file, "\n--- %sGrammar --- formula=%d, produce=%d, item=%d, maker=%d, used=%d, vector=%d, type=%06X ---\n", prefix, count(), produce_count, item_count, maker_count, used_count, Vectors().count(), type);
      }
   if (print_mode & T_PrintMode::pmBIF) {
      TGrammar* grammar = prepare(printer);
      printer.grammar = grammar;
      grammar->formulas.prepare(printer);
      //      printer.print_mode |= T_PrintMode::pmCompact;
      grammar->formulas.print(printer);
      delete grammar;
   } else {
      formulas.print(printer);
   }
}

TGrammar* TGrammar::prepare(TPrinter& printer) const
{
   TGrammar* grammar = new TGrammar();
   grammar->formulas = GFormulaTable(formulas);
   grammar->root = grammar->formulas.root;
   int filter = (GSymbol::Tree | GSymbol::Code | GSymbol::Turn);
   grammar->filter_makers(filter);
//   grammar->make_Symple();
   grammar->make_LeftFactoring();
   return grammar;
}

void TGrammar::grammar_type()
{
   int type_type = T_Grammar::gtNone, type_lexeme = lexemes.grammar_type();
   int type_maker = T_Grammar::mtNone, type_grammar = T_Grammar::gtLL;
   for (GFormula* formula : formulas) {
      for (GProduce& produce : *formula) {
         for (GSymbol& sym : produce) {
            if (sym.IsMaker()) {
               if (sym.IsMakerTree()) type_maker |= T_Grammar::mtTree;
               if (sym.IsMakerCode()) type_maker |= T_Grammar::mtCode;
               if (sym.IsMakerYACC()) type_maker |= T_Grammar::mtYacc;
               if (sym.IsMakerNode()) type_maker |= T_Grammar::mtSNode;
               if (sym.IsMakerTurn()) type_maker |= T_Grammar::mtTurn;
               if (sym.IsMakerCall()) type_maker |= T_Grammar::mtCall;
            } else if (sym.IsFormula() && (sym == formula->head)) {
               sym.mode |= GSymbol::Master;
            }
         }
         const GSymbol& sym = produce.maker;
         if (sym.IsMaker()) {
            if (sym.IsMakerTree()) type_maker |= T_Grammar::mtTree;
            if (sym.IsMakerCode()) type_maker |= T_Grammar::mtCode;
            if (sym.IsMakerYACC()) type_maker |= T_Grammar::mtYacc;
            if (sym.IsMakerNode()) type_maker |= T_Grammar::mtSNode;
            if (sym.IsMakerTurn()) type_maker |= T_Grammar::mtTurn;
            if (sym.IsMakerCall()) type_maker |= T_Grammar::mtCall;
         }
         if (produce.count()) {
            if (produce[0].IsMaster()) { 
               type_grammar |= T_Grammar::gtLR; type_grammar &= ~T_Grammar::gtLL; 
            }
         }
      }
   }
   type_type |= type_lexeme | type_maker | type_grammar;
   type = (T_Grammar)type_type;
}

GFormula*  TGrammar::AddFormula(const char* title)
{
   GFormula* formula = new GFormula(GSymbol(GSymbol::gsFormula, formulas.count()));
   formula->title = title;
   int index;
   if (!formulas.Add(formula, index)) {
      delete formula;
      formula = formulas[index];
   }
   return formula;
}

void TGrammar::AddProduce()
{
   GFormula* formula = formulas.back();
   GProduce produce(GSymbol(GSymbol::gsProduce, formula->head.formula, formula->count()));
   formula->Add(produce);
}

void TGrammar::AddProduce(const GSymbol &sym)
{
   AddProduce();
   GFormula* formula = formulas.back();
   GProduce& produce = formula->back();
   produce.maker = sym;
}

void TGrammar::AddProduce(int count, const int I[][5])
{
   AddProduce(); AddItems(count, I);
}

void TGrammar::AddProduce(const GSymbol &sym, int count, const int I[][5])
{
   AddProduce(sym); AddItems(count, I);
}

void TGrammar::AddItem(const GSymbol &sym)
{
   GFormula* formula = formulas.back();
   GProduce& produce = formula->back();
   produce.Add(sym);
}

void TGrammar::AddItems(int count, const int I[][5])
{
   GFormula* formula = formulas.back();
   GProduce& produce = formula->back();
   for (int i = 0; i < count; i++) {
      const GSymbol sym((GSymbol::T_Type)I[i][0], I[i][1], I[i][2], I[i][3], I[i][4]);
      produce.Add(sym);
   }
}

void TGrammar::AddVector(int count, const int I[][5])
{
   GSymbolVector vector;
   for (int i = 0; i < count; i++) {
      const GSymbol sym((GSymbol::T_Type)I[i][0], I[i][1], I[i][2], I[i][3], I[i][4]);
      vector << sym;
   }
   AddVector(vector);
}

// Red(p=195,196)
bool TFirstFollowMap::make_FIRSTs()
{
   bool ret = true;

   printf("\nFIRST");
   for (const std::pair<const GSymbol&, int> item : grammar->lexemes) {
      const GSymbol& sym = item.first;
      TFirst FIRST; FIRST += sym;
      Add(sym, FIRST);
   }

   for (const GFormula* formula : grammar->formulas) {
      TFirst FIRST;
      for (const GProduce& produce : *formula) {
         if (produce.IsEmpty()) {
            FIRST << GSymbol::empty; break;
         }
      }
      Add(formula->head, FIRST);
   }

   bool cycle = false;
   do {
      cycle = false;
      for (const GFormula* formula : grammar->formulas) {
         TFirst& first_formula = (TFirst&)at(formula->head);
         for (const GProduce& produce : *formula) {
            if (first_formula += produce) cycle = true;
         }
      }
   } while (cycle);

   return true;
}

// Green(v=1,p=397,a=5.5)
bool TGrammar::make_FIRST_ks(int k)
{
   bool ret = true;
   FIRSTs.clear();
   int step = 0;
   std::vector<int> change_step; change_step.resize(formulas.count(), -1);

   printf("\nFIRST");
   TFirst first_empty; first_empty << GSymbol::empty;
   FIRSTs.Add(GSymbol::empty, first_empty);

   for (const std::pair<const GSymbol&, int> item : lexemes) {
      const GSymbol& sym = item.first;
      TFirst FIRST;
      GSymbolVector vector;
      vector << sym;
      const GSymbol header = AddVector(vector);
      FIRST += header;
      FIRSTs.Add(sym, FIRST);
   }

   for (const GFormula* formula : formulas) {
      FORMULA_DELETED_CONTINUE(formula);
      TFirst FIRST;
      for (const GProduce& produce : *formula) {
         if (produce.IsEmpty()) {
            FIRST += GSymbol::empty;
            continue;
         }
         GSymbolVector vector;
         int item = 0;
         for (const GSymbol& sym : produce) {
            if (++item > k) break;
            if (sym.IsTerminal()) {
               vector << sym;
            } else if (sym.IsMaker()) {
            } else {
               vector.clear();
               break;
            }
         }
         if (!vector.empty()) {
            const GSymbol header = AddVector(vector);
            FIRST += header;
         }
      }
      FIRSTs.Add(formula->head, FIRST);
      if (!FIRST.empty()) change_step[formula->head.formula] = step;
   }

   int cycle = 0, attempt_all = 0;
   do {
      step++;
      cycle = 0;
      int attempt = 0;
      for (const GFormula* formula : formulas) {
         FORMULA_DELETED_CONTINUE(formula);
         int A = formula->head.formula;
         TFirst& first_formula = (TFirst&)FIRSTs.at(formula->head);
         for (const GProduce& produce : *formula) {
            if (produce.IsEmpty()) continue;
            bool yes_change = false;
            for (const GSymbol& sym : produce) {
               if (sym.IsFormula()) {
                  int B = sym.formula;
                  if (change_step[B] < 0) { yes_change = false; break; }
                  if (change_step[B] >= step - 1) yes_change = true;
               }
            }
            if (!yes_change) continue;
            TFirst first;
            if (!FIRSTs.FIRST(produce, first, k)) continue;
            attempt++;
            if (int change = first_formula += first) {
               cycle += change;
               change_step[A] = step;
            }
         }
      }
      attempt_all += attempt;
      printf("\nstep = %2d, change = %7d, item = %7d, attempt = (%5d, %7d), vector = %4d", step, cycle, FIRSTs.count(), attempt, attempt_all, Vectors().count());
   } while (cycle);
   printf("\n");

   /*
   GVectors vectors_sort;
   std::vector<int> indexs; indexs.resize(Vectors().count(),-1);
   for (std::pair<const GVectors::Key, const GSymbol> item : Vectors().map) {
   const GSymbolVector *vector = item.first.key;
   const GSymbol v = vectors_sort.Add(*vector);
   indexs[item.second.formula] = v.formula;
   }
   vectors = vectors_sort;

   TFirstFollowMap   FIRSTs_V(this);
   for (const std::pair<const GSymbol, const TFirstFollow&> item : FIRSTs) {
   TFirst first_sort;
   const TFirst &first = (TFirst&)item.second;
   for (const GSymbol& sym : first) {
   GSymbol sym_sort(sym);
   if (sym.IsVector()) {
   sym_sort.formula = indexs[sym.formula];
   }
   first_sort << sym_sort;
   }
   FIRSTs_V.Add(item.first, first_sort);
   }
   FIRSTs = FIRSTs_V;

   FIRSTs.print("FIRSTs_V", "", 0x0702);
   */
   return true;
}

// Green(v=1,p=450,e=5.2.19)
bool TGrammar::make_EFF_ks(int k)
{
   bool ret = true;
   EFFs.clear();
   int step = 0;
   std::vector<int> change_step; change_step.resize(formulas.count(), -1);

   printf("\nEFF");
   TFirst eff_empty; eff_empty << GSymbol::empty;
   EFFs.Add(GSymbol::empty, eff_empty);

   for (const std::pair<const GSymbol&, int> item : lexemes) {
      const GSymbol& sym = item.first;
      TFirst eff;
      GSymbolVector vector;
      vector << sym;
      const GSymbol header = AddVector(vector);
      eff += header;
      EFFs.Add(sym, eff);
   }

   for (const GFormula* formula : formulas) {
      FORMULA_DELETED_CONTINUE(formula);
      TFirst eff;
      for (const GProduce& produce : *formula) {
         if (produce.IsEmpty()) continue;
         if (produce.front().IsTerminal()) {
            TFirst first;
            if (!FIRSTs.FIRST(produce, first, k)) continue;
            eff += first;
         }
      }
      EFFs.Add(formula->head, eff);
      if (!eff.empty()) change_step[formula->head.formula] = step;
   }

   int cycle = 0, attempt_all = 0;
   do {
      step++;
      cycle = 0;
      int attempt = 0;
      for (const GFormula* formula : formulas) {
         FORMULA_DELETED_CONTINUE(formula);
         int A = formula->head.formula;
         TFirst& eff_formula = (TFirst&)EFFs.at(formula->head);
         for (const GProduce& produce : *formula) {
            if (produce.IsEmpty()) continue;
            GSymbolVector symbols_produce(produce, GSymbol::msTerminal | GSymbol::msFormula);
            if (symbols_produce.empty()) continue;
            const GSymbol& X = symbols_produce.front();
            if (X.IsFormula()) {
               if (change_step[X.formula] < step - 1) continue;
               TFirst eff_X = (TFirst&)EFFs.at(X), eff_produce;
               GSymbolVector alpha;
               for (int index_a = 1; index_a < symbols_produce.count(); index_a++) {
                  alpha << symbols_produce[index_a];
               }
               TFirst first;
               if (!alpha.empty()) {
                  if (FIRSTs.FIRST(alpha, first, k)) {
                  }
               } else {
                  first << GSymbol::empty;
               }
               Vectors().Plus(eff_X, first, eff_produce, k);
               attempt++;
               if (int change = eff_formula += eff_produce) {
                  cycle += change;
                  change_step[A] = step;
               }
            }
         }
      }
      attempt_all += attempt;
      printf("\nstep = %2d, change = %7d, item = %7d, attempt = (%5d, %7d), vector = %4d", step, cycle, EFFs.count(), attempt, attempt_all, Vectors().count());
   } while (cycle);
   printf("\n");

   return true;
}

bool TGrammar::make_FIRSTsP()
{
   bool ret = true;

   for (const GFormula* formula : formulas) {
      for (const GProduce& produce : *formula) {
         TFirst FIRST(produce, &FIRSTs);
         FIRSTsP.Add(produce.head, FIRST);
      }
   }

   return ret;
}

bool TGrammar::make_FEFS(int mode) // 0x01 - SIGMA
{
   if (look_ahead > 0) {
      make_FIRST_ks(look_ahead);
      make_EFF_ks(look_ahead);
      make_FOLLOW_ks(look_ahead);
      if (mode & 0x01) {
         make_SIGMA_ks(look_ahead);
      }
   } else {
      make_FIRSTs();
      make_FOLLOWs();
   }
   return true;
}

// Red(p=195,196)
bool TFirstFollowMap::make_FOLLOWs(const TFirstFollowMap& FIRSTs)
{
   bool ret = true;
   bool cycle = false;
   for (const GFormula* formula : grammar->formulas) {
      TFollow follow;
      Add(formula->head, follow);
   }

   printf("\nFOLLOW");
   at((*grammar->root).head) += GSymbol::eof;
   do {
      cycle = false;
      for (const GFormula* formula : grammar->formulas) {
         const TFollow& follow_A = (const TFollow&)at(formula->head);
         for (const GProduce& produce : *formula) {
            GSymbolVector symbols_produce(produce, GSymbol::msTerminal | GSymbol::msFormula);
            for (int index_B = 0; index_B < symbols_produce.count(); index_B++) {
               const GSymbol& sym_B = symbols_produce[index_B];
               if (!sym_B.IsFormula()) continue;
               TFollow& follow_B = (TFollow&)at(sym_B);
               GSymbolVector symbols_tail;
               for (int index = index_B + 1; index < symbols_produce.count(); index++) {
                  const GSymbol& sym_tail = symbols_produce[index];
                  if (sym_tail.IsTerminal() || sym_tail.IsFormula()) {
                     symbols_tail.Add(sym_tail);
                  }
               }
               bool must_follow = false;
               if (!symbols_tail.empty()) {
                  TFirst first_tail(symbols_tail, &FIRSTs);
                  for (const GSymbol& sym : first_tail) {
                     if (!sym.IsEmpty()) {
                        if (follow_B += sym) cycle = true;
                     } else {
                        must_follow = true;
                     }
                  }
               } else {
                  must_follow = true;
               }
               if (must_follow) {
                  if (follow_B += follow_A) cycle = true;
               }
            }
         }
      }
   } while (cycle);
   return ret;
}

class TFirstFollowSigma : public std::map<const TTableKey, TLangFirst>
{
public:
   TFirstFollowSigma(TGrammar* g) :grammar(g) {}
   bool Add(const TTableKey& key, const TLangFirst& item);
public:
   int  count() const;
   void print(TPrinter& printer) const;
public:
   TGrammar * grammar;
};

class TFirstFollowTab : public std::map<const TTableKey, TFirstFollow>
{
public:
   TFirstFollowTab(TGrammar* g) :grammar(g) {}
   bool Add(const TTableKey& key, const TFirstFollow& item);
public:
   int  count() const;
   void print(TPrinter& printer) const;
public:
   TGrammar * grammar;
};

// L&T(p=181,2.9)
bool TGrammar::make_FOLLOW_ks(int k)
{
   TFirstFollowTab Fi(this);
   int formula_count = formulas.count();
   std::vector<int> change_step; change_step.resize(formula_count * formula_count, -1);

   printf("\nFOLLOW");
   int step = 0;
   bool ret = true;
   for (const GFormula* formula_A : formulas) {
      FORMULA_DELETED_CONTINUE(formula_A);
      const GSymbol& sym_A = formula_A->head;
      for (const GFormula* formula_B : formulas) {
         FORMULA_DELETED_CONTINUE(formula_B);
         const GSymbol& sym_B = formula_B->head;
         TTableKey A_B(sym_A, sym_B);
         TFollow follow;
         for (const GProduce& produce : *formula_A) {
            for (int index_B = 0; index_B < produce.count(); index_B++) {
               if (!(sym_B == produce[index_B])) continue;
               GSymbolVector alpha;
               produce.TailWithoutMaker(index_B + 1, alpha);
               if (!alpha.empty()) {
                  TFirst first;
                  if (FIRSTs.FIRST(alpha, first, k)) {
                     follow << (TFollow&)(TFirstFollow&)first;
                  }
               } else {
                  follow << GSymbol::empty;
               }
            }
         }
         Fi.Add(A_B, follow);
         if (!follow.empty()) change_step[formula_count * sym_A.formula + sym_B.formula] = step;
      }
   }

   int cycle = 0, attempt_all = 0;
   do {
      step++;
      cycle = 0;
      int attempt = 0;
      for (const GFormula* formula_A : formulas) {
         FORMULA_DELETED_CONTINUE(formula_A);
         const GSymbol& sym_A = formula_A->head;
         for (const GProduce& produce : *formula_A) {
            for (int index_P = 0; index_P < produce.count(); index_P++) {
               const GSymbol& sym_P = produce[index_P];
               if (!sym_P.IsFormula()) continue;
               GSymbolVector alpha;
               produce.TailWithoutMaker(index_P + 1, alpha);
               TFirst first;
               if (!alpha.empty()) {
                  if (!FIRSTs.FIRST(alpha, first, k)) continue;
               } else {
                  first << GSymbol::empty;
               }
               for (const GFormula* formula_B : formulas) {
                  FORMULA_DELETED_CONTINUE(formula_B);
                  const GSymbol& sym_B = formula_B->head;
                  if (change_step[formula_count * sym_P.formula + sym_B.formula] < step - 1) continue;
                  TTableKey A_B(sym_A, sym_B);
                  TFollow& fi_A_B = (TFollow&)Fi.at(A_B);
                  TTableKey P_B(sym_P, sym_B);
                  const TFollow& fi_P_B = (TFollow&)Fi.at(P_B);
                  TFollow follow;
                  Vectors().Plus(fi_P_B, first, follow, k);
                  attempt++;
                  if (int change = fi_A_B += follow) {
                     cycle += change;
                     change_step[formula_count * sym_A.formula + sym_B.formula] = step;
                  }
               }
            }
         }
      }
      attempt_all += attempt;
      printf("\nstep = %2d, change = %7d, item = %7d, attempt = (%5d, %7d), vector = %4d", step, cycle, Fi.count(), attempt, attempt_all, Vectors().count());
   } while (cycle);
   printf("\n");

   FOLLOWs.clear();
   const GSymbol& sym_S = root->head;
   for (const GFormula* formula_A : formulas) {
      FORMULA_DELETED_CONTINUE(formula_A);
      const GSymbol& sym_A = formula_A->head;
      TTableKey S_A(sym_S, sym_A);
      TFollow& fi_S_A = (TFollow&)Fi.at(S_A);
      FOLLOWs.Add(sym_A, fi_S_A);
   }
   TFollow& follow_S = Follow(sym_S);
   follow_S += GSymbol::empty;

   return ret;
}

// Green(v=1,p=399,a=5.6)
bool TGrammar::make_SIGMA_ks(int k)
{
   TPrinter printer(this);
   TFirstFollowSigma Sigma(this);
   int formula_count = formulas.count();
   std::vector<int> change_step; change_step.resize(formula_count * formula_count, -1);

   printf("\nSIGMA");
   int step = 0;
   bool ret = true;
   for (const GFormula* formula_A : formulas) {
      const GSymbol& sym_A = formula_A->head;
      for (const GFormula* formula_B : formulas) {
         const GSymbol& sym_B = formula_B->head;
         TTableKey A_B(sym_A, sym_B);
         TLangFirst langs;
         for (const GProduce& produce : *formula_A) {
            for (int index_B = 0; index_B < produce.count(); index_B++) {
               if (!(sym_B == produce[index_B])) continue;
               GSymbolVector alpha;
               produce.TailWithoutMaker(index_B + 1, alpha);
               TFirst first;
               if (!alpha.empty()) {
                  if (FIRSTs.FIRST(alpha, first, k)) {
                     langs.Insert(first);
                  }
               } else {
                  first << GSymbol::empty;
                  langs.Insert(first);
               }
            }
         }
         Sigma.Add(A_B, langs);
         if (!langs.empty()) change_step[formula_count * sym_A.formula + sym_B.formula] = step;
      }
   }

   int cycle = 0, attempt_all = 0;
   do {
      step++;
      cycle = 0;
      int attempt = 0;
      for (const GFormula* formula_A : formulas) {
         const GSymbol& sym_A = formula_A->head;
         for (const GProduce& produce : *formula_A) {
            for (int index_P = 0; index_P < produce.count(); index_P++) {
               const GSymbol& sym_P = produce[index_P];
               if (!sym_P.IsFormula()) continue;
               GSymbolVector alpha;
               produce.TailWithoutMaker(index_P + 1, alpha);
               TFirst first;
               if (!alpha.empty()) {
                  if (!FIRSTs.FIRST(alpha, first, k)) continue;
               } else {
                  first << GSymbol::empty;
               }
               for (const GFormula* formula_B : formulas) {
                  const GSymbol& sym_B = formula_B->head;
                  if (change_step[formula_count * sym_P.formula + sym_B.formula] < step - 1) continue;
                  TTableKey A_B(sym_A, sym_B);
                  TLangFirst& langs_A_B = Sigma.at(A_B);
                  TTableKey P_B(sym_P, sym_B);
                  const TLangFirst& langs_P_B = Sigma.at(P_B);
                  for (const TFirst& L_P_B : langs_P_B) {
                     TFirst lang;
                     Vectors().Plus(L_P_B, first, lang, k);
                     attempt++;
                     if (langs_A_B.Insert(lang)) {
                        cycle++;
                        change_step[formula_count * sym_A.formula + sym_B.formula] = step;
                     }
                  }
               }
            }
         }
      }
      attempt_all += attempt;
      printf("\nstep = %2d, change = %7d, item = %7d, attempt = (%5d, %7d), vector = %4d", step, cycle, Sigma.count(), attempt, attempt_all, Vectors().count());
   } while (cycle);
   printf("\n");

   SIGMAs.clear();
   const GSymbol& sym_S = root->head;
   for (const GFormula* formula_A : formulas) {
      const GSymbol& sym_A = formula_A->head;
      TTableKey S_A(sym_S, sym_A);
      TLangFirst& langs_S_A = Sigma.at(S_A);
      SIGMAs.Add(sym_A, langs_S_A);
   }

   TFirst lang_S; lang_S << GSymbol::empty;
   TLangFirst& langs_S = SIGMAs.at(sym_S);
   langs_S.Insert(lang_S);

   for (const GFormula* formula_A : formulas) {
      const GSymbol& sym_A = formula_A->head;
      const TLangFirst& langs_A = SIGMAs.at(sym_A);
      const TFollow& follow_A = (TFollow&)FOLLOWs.at(sym_A);
      TFollow lang;
      langs_A.Merge(lang);
      if (!(follow_A == lang)) {
         printer.eol(); sym_A.print(printer);
      }
   }

   return ret;
}

// Green(v=1,p=396,a=5.4)
int TGrammar::ValidLLk()
{
   TPrinter printer(this);
   int invalid = 0;
   for (const GFormula* formula_A : formulas) {
      int count = formula_A->count();
      if (count < 2) continue;
      const GSymbol& sym_A = formula_A->head;
      const TLangFirst& langs_A = SIGMAs.at(sym_A);
      for (int i = 0; i < count - 1; i++) {
         const GProduce& produce_I = (*formula_A)[i];
         GSymbolVector tail_I;
         produce_I.TailWithoutMaker(0, tail_I);
         TFirst first_I;
         if (!tail_I.empty()) {
            if (!FIRSTs.FIRST(tail_I, first_I, look_ahead)) continue;
         } else {
            first_I << GSymbol::empty;
         }
         for (int j = i + 1; j < count; j++) {
            const GProduce& produce_J = (*formula_A)[j];
            GSymbolVector tail_J;
            produce_J.TailWithoutMaker(0, tail_J);
            TFirst first_J;
            if (!tail_J.empty()) {
               if (!FIRSTs.FIRST(tail_J, first_J, look_ahead)) continue;
            } else {
               first_J << GSymbol::empty;
            }
            for (const TFirst& lang_A : langs_A) {
               TFirst lang_I;
               Vectors().Plus(first_I, lang_A, lang_I, look_ahead);
               TFirst lang_J;
               Vectors().Plus(first_J, lang_A, lang_J, look_ahead);
               GSymbolSet I_J = lang_I * lang_J;
               if (!I_J.empty()) {
                  invalid++;
                  fprintf(stdout, "\n"); sym_A.print(printer);
                  fprintf(stdout, " : "); I_J.print(printer);
                  break;
               }
            }
         }
      }
   }
   if (!invalid) type = T_Grammar(type | gtLLk);
   return invalid;
}

bool TGrammar::Split(GSymbolSet& main, GSymbolSet& half) const
{
   TFirst::iterator ip = main.begin();
   bool ret = false;
   while (ip != main.end()) {
      const GSymbol& sym = (*ip);
      bool migrate = false;
      if (sym.IsEmpty() || sym.IsEof()) {
         migrate = true;
      } else if (sym.IsTerminal()) {
         if (look_ahead > 1) migrate = true;
      } else if (sym.IsVector()) {
         const GSymbolVector& vec = Vector(sym);
         if (vec.count() < look_ahead) migrate = true;
      }
      if (migrate) {
         half << sym;
         ip = main.erase(ip);
         ret = true;
      } else {
         ip++;
      }
   }
   return ret;
}

TFirst::TFirst(const GSymbolVector& symbols, const TFirstFollowMap* g) :TFirstFollow(g)
{
   (*this) += symbols;
}

int TFirstFollow::operator += (const TFirstFollow& join)
{
   return ((GSymbolSet&)(*this)) += ((const GSymbolSet&)join);
}

// Red(p=195,196)
int TFirst::operator += (const GSymbolVector& symbols)
{
   int ret = 0;
   bool yes = true;
   TFirst& first_formula = (*this);
   for (const GSymbol& sym : symbols) {
      if (sym.IsMaker()) continue;
      if (sym.IsTerminal() || sym.IsFormula()) {
         const TFirst& first_sym = (const TFirst&)owner->at(sym);
         bool have_empty = false;
         for (const GSymbol& sym_sym : first_sym) {
            if (!sym_sym.IsEmpty()) {
               ret += first_formula += sym_sym;
            } else {
               have_empty = true;
            }
         }
         if (!have_empty) { yes = false; break; }
      } else if (sym.IsEof()) {
         ret += (first_formula += sym);
         yes = false; break;
      } else if (sym.IsEmpty()) {
         yes = true;
      } else {
         yes = false;
      }
   }
   if (yes) {
      ret += (first_formula += GSymbol::empty);
   }
   return ret;
}

TFirstFollow TFirstFollow::operator * (const TFirstFollow& join) const
{
   TFirstFollow ret(owner);
   for (const GSymbol& sym : join) {
      if (Have(sym)) ret += sym;
   }
   return ret;
}

int  TFirstFollow::Length(TGrammar * grammar)
{
   k = 10000;
   for (const GSymbol& sym : (*this)) {
      if (sym.IsEmpty() || sym.IsEof()) { k = 0; break; }
      if (sym.IsTerminal()) { k = 1; continue; } 
      const GSymbolVector& vec = grammar->Vector(sym);
      if (vec.count() < k) k = vec.count();
   }
   return k;
}

bool TFirstFollowMap::Add(const GSymbol& key, TFirstFollow& item)
{
   const_iterator ip = find(key);
   if (ip != end()) return false;
   item.owner = this;
   std::pair<const GSymbol&, const TFirstFollow&> my_item(key, item);
   insert(my_item);
   return true;
}

bool TFirstFollowMap::Have(const GSymbol& key, const GSymbol& sym) const
{
   const_iterator ip = find(key);
   if (ip == end()) return false;
   std::pair<const GSymbol&, const TFirstFollow&> item = (*ip);
   return item.second.Have(sym);
}

bool TFirstFollowMap::FIRST(const GSymbolVector& alpha, TFirst& first) const
{
   first.owner = this;
   first += alpha;
   return true;
}

// Green(v=1,p=389,l=5.1)
bool TFirstFollowMap::FIRST(const GSymbolVector& alpha, TFirst& first, int k) const
{
   if (k == 0) return FIRST(alpha, first);
   int i = 0;
   while ((i < alpha.count()) && alpha[i].IsMaker()) i++;
   if (i == alpha.count()) return false;
   TFirst FIRST_1 = (TFirst&)at(alpha[i]);
   int min_length = grammar->Vectors().MinLength(FIRST_1);
   if (min_length >= k) i = alpha.count();
   for (int y = i + 1; y < alpha.count(); y++) {
      const GSymbol& sym_y = alpha[y];
      if (sym_y.IsMaker()) continue;
      const TFirstFollow& FIRST_y = at(sym_y);
      TFirst FIRST;
      grammar->Vectors().Plus(FIRST_1, FIRST_y, FIRST, k);
      FIRST_1 = FIRST;
      int min_length = grammar->Vectors().MinLength(FIRST);
      if (min_length >= k) break;
   }
   first = FIRST_1;
   return true;
}

bool TFirstFollowMap::FirstTail(const GSymbol& point, TFirst& first) const
{
   const GProduce& produce = grammar->Produce(point);
   if ((point.point == produce.count()) || produce.IsEmpty()) {
      first << GSymbol::empty;
      return true;
   }
   GSymbolVector beta;
   produce.Tail(point, beta);
   return FIRST(beta, first);
}

bool TFirstFollowMap::FirstTail(const GSymbol& point, TFirst& first, int k) const
{
   const GProduce& produce = grammar->Produce(point);
   if ((point.point == produce.count()) || produce.IsEmpty()) {
      first << GSymbol::empty;
      return true;
   }
   GSymbolVector beta;
   produce.Tail(point, beta);
   return FIRST(beta, first, k);
}

#define MY_FIRST_K
// Green(v=1,p=450,e=5.2.19)
bool TFirstFollowMap::EFF(const GSymbolVector& alpha, TFirst& eff, int k) const
{
   if (alpha.IsEmpty()) return false;
   int i = 0;
   while ((i < alpha.count()) && alpha[i].IsMaker()) i++;
   if (i == alpha.count()) return false;
   const_iterator ip = find(alpha[i]);
   if (ip == end()) return false;
   TFirst FIRST_1 = (TFirst&)(*ip).second;
   int min_length = grammar->Vectors().MinLength(FIRST_1);
   if (min_length == k) i = alpha.count();
#ifdef MY_FIRST_K
   for (int y = i + 1; y < alpha.count(); y++) {
      const GSymbol& sym_y = alpha[y];
      if (sym_y.IsMaker()) continue;
      if (!sym_y.IsEmpty()) {
         const TFirstFollow& FIRST_y = grammar->FIRSTs.at(sym_y);
         TFirst FIRST;
         grammar->Vectors().Plus(FIRST_1, FIRST_y, FIRST, k);
         FIRST_1 = FIRST;
         int min_length = grammar->Vectors().MinLength(FIRST);
         if (min_length == k) break;
      }
   }
   eff = FIRST_1;
#else
   GSymbolVector first_alpha;
   for (int y = i + 1; y < alpha.count(); y++) {
      if (alpha[y].IsMaker()) continue;
      first_alpha << alpha[y];
   }
   if (!first_alpha.empty()) {
      TFirst FIRST;
      grammar->FIRSTs.FIRST(first_alpha, FIRST, k);
      grammar->Vectors().Plus(FIRST_1, FIRST, eff, k);
   } else {
      eff = FIRST_1;
   }
#endif
   return true;
}

void TFirstFollow::print(TPrinter& printer) const
{
   fprintf(printer.file, "-> ");
   GSymbolSet::print(printer);
}

void TFirstFollowMap::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF;
   const char* file_name = printer.file_name, *title = printer.title;
   if (!file_name) {
      int sym_count = 0;
      for (const std::pair<const GSymbol, const TFirstFollow&> item : *this) {
         sym_count += item.second.count();
      }
      fprintf(file, "\n--- ");
      if (!title) title = "FirstFollow";
      fprintf(file, "%s --- <%d> --- <%d> ---\n", title, (int)size(), sym_count);
   }
   if (print_mode == T_PrintMode::pmNone) return;
   int number_item = 0;
   for (const std::pair<const GSymbol&, const TFirstFollow&> item : *this) {
      if (number_item++) printer.eol();
      item.first.print(printer);
      item.second.print(printer);
   }
   printer.eol();
}

int  TFirstFollowMap::count() const
{
   int ret = 0;
   for (const std::pair<const GSymbol&, const TFirstFollow&> item : *this) {
      ret += item.second.count();
   }
   return ret;
}

int  TFirstFollowTab::count() const
{
   int ret = 0;
   for (const std::pair<const TTableKey&, const TFirstFollow&> item : *this) {
      ret += item.second.count();
   }
   return ret;
}

bool TFirstFollowTab::Add(const TTableKey& key, const TFirstFollow& item)
{
   const_iterator ip = find(key);
   if (ip != end()) return false;
   std::pair<const TTableKey&, const TFirstFollow&> my_item(key, item);
   insert(my_item);
   return true;
}

void TFirstFollowTab::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   if (!printer.file_name) {
      int sym_count = 0;
      for (const std::pair<const TTableKey, const TFirstFollow&> item : *this) {
         sym_count += item.second.count();
      }
      fprintf(file, "\n--- ");
      fprintf(file, "%s --- <%d> --- <%d> ---\n", "FirstFollow", (int)size(), sym_count);
   }
   if (print_mode == 0x00) return;
   int number_item = 0;
   for (const std::pair<const TTableKey&, const TFirstFollow&> item : *this) {
      if (number_item++) printer.eol();
      item.first.print(printer);
      item.second.print(printer);
   }
   printer.eol();
}

int  TFirstFollowSigma::count() const
{
   int ret = 0;
   for (const std::pair<const TTableKey&, const TLangFirst&> item : *this) {
      ret += (int)item.second.size();
   }
   return ret;
}

bool TFirstFollowSigma::Add(const TTableKey& key, const TLangFirst& item)
{
   const_iterator ip = find(key);
   if (ip != end()) return false;
   std::pair<const TTableKey&, const TLangFirst&> my_item(key, item);
   insert(my_item);
   return true;
}

void TFirstFollowSigma::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   if (!printer.file_name) {
      int sym_count = 0;
      for (const std::pair<const TTableKey, const TLangFirst&> item : *this) {
         sym_count += (int)item.second.size();
      }
      fprintf(file, "\n--- ");
      fprintf(file, "%s --- <%d> --- <%d> ---\n", "LangFirst", (int)size(), sym_count);
   }
   if (print_mode == 0x00) return;
   int number_item = 0;
   for (const std::pair<const TTableKey&, const TLangFirst&> item : *this) {
      if (number_item++) printer.eol();
      item.first.print(printer);
      item.second.print(printer);
   }
   printer.eol();
}

bool TLangFirst::Insert(const TFirst& item)
{  
   iterator ip = find(item);
   if (ip != end()) return false;
   insert(item);
   return true;
}

void TLangFirst::Merge(TFirstFollow& lang) const
{
   for (const TFirst& item : (*this)) {
      lang << item;
   }
}

void TLangFirst::print(TPrinter& printer) const
{
   for (const TFirst& item : (*this)) {
      item.print(printer);
   }
}

bool TLangFirstMap::Add(const GSymbol& key, TLangFirst& item)
{
   const_iterator ip = find(key);
   if (ip != end()) return false;
   item.owner = this;
   std::pair<const GSymbol&, const TLangFirst&> my_item(key, item);
   insert(my_item);
   return true;
}

GSymbol TFirstFollowTable::Add(const TFirstFollow& key)
{
   std::map<const Key, const GSymbol>::const_iterator ip = map.find(Key(&key));
   if (ip != map.end()) {
      std::pair<const Key, const GSymbol&> item = (*ip);
      return item.second;
   }
   GSymbol sym(GSymbol::gsTable, count());
   const TFirstFollow* my_key = new TFirstFollow(key);
   vector.push_back(my_key);
   std::pair<const Key, const GSymbol&> item(my_key, sym);
   map.insert(item);
   return sym;
}

void TFirstFollowTable::Copy(const TFirstFollowTable& join)
{
   for (const TFirstFollow* item : join.vector) {
      Add(*item);
   }
}

void TFirstFollowTable::Clear()
{
   for (const TFirstFollow* item : vector) {
      delete item;
   }
   vector.clear(); map.clear();
}

const TFirstFollow& TFirstFollowTable::Get(const GSymbol& sym) const
{
   return *vector[sym.situation];
}

void TFirstFollowTable::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   int t = 0;
   for (const TFirstFollow* item : vector) {
      fprintf(file, "\nTable: %05d", t++);
      item->print(printer);
   }
}

void TNextTab::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   if (!printer.file_name) {
      fprintf(file, "\n--- NEXTs table --- <%d> ---\n", (int)size());
   }
   if (print_mode == 0x00) return;
   GSymbol T_old; T_old.formula = -1;
   for (const std::pair<const TTwoSym&, const GSymbolSet&> item : *this) {
      TTwoSym key = item.first;
      GSymbol& T = key.one;
      if (!(T == T_old)) {
         T_old = T;
      } else {
         T.type = GSymbol::gsNone;
      }
      key.print(printer);
      fprintf(file, " -> ");
      item.second.print(printer);
      printer.eol();
   }
}

bool GVectors::Plus(const GSymbolSet& left, const GSymbolSet& right, GSymbolSet& result, int k)
{
//   if (left.empty() || right.empty()) return false;
   if (left.empty()) { result = right; return true; }
   if (right.empty()) { result = left; return true; }
   for (const GSymbol& v1 : left) {
      for (const GSymbol& vy : right) {
         if ((v1.IsEmpty()) && (vy.IsEmpty())) {
            result += GSymbol::empty;
         } else if (v1.IsEmpty()) {
            result += vy;
         } else if (vy.IsEmpty() || (k == 0)) {
            result += v1;
         } else {
            const GSymbolVector *vec_1 = NULL;
            if (v1.IsVector()) vec_1 = &Vector(v1);
            if (vec_1 && (vec_1->count() == k)) {
               result += v1;
               break;
            }
            const GSymbolVector *vec_y = NULL;
            if (vy.IsVector()) vec_y = &Vector(vy);
            GSymbolVector vector;
            int len = 0;
            if (vec_1) {
               for (const GSymbol& sym : *vec_1) {
                  if (len++ >= k) break;
                  vector << sym;
               }
            } else {
               vector << v1;
            }
            if (vec_y) {
               for (const GSymbol& sym : *vec_y) {
                  if (len++ >= k) break;
                  vector << sym;
               }
            } else {
               vector << vy;
            }
            const GSymbol header = Add(vector);
            result += header;
         }
      }
   }
   return true;
}

int  GVectors::MinLength(const TFirstFollow& alpha) const
{
   if (alpha.empty()) return 0;
   int min = 1000000000;
   for (const GSymbol& v : alpha) {
      if (v.IsEmpty()) {
         return 0;
      } else if (v.IsTerminal()) {
         if (1 < min) {
            min = 1;
         }
      } else {
         const GSymbolVector &vec = Vector(v);
         if (vec.count() < min) {
            min = vec.count();
         }
      }
   }
   return min;
}

void GVectors::Tails(GSymbolVector& from, GSymbolVector& to, const TLexemeSet& lexemes)
{
   from.push_back(GSymbol());
   to.clear();
   for (const std::pair<const GSymbol&, int> item : lexemes) {
      from.back() = item.first; // lexeme
      GSymbol vector = Add(from);
      to.push_back(vector);
   }
   from.pop_back();
}

// -------------------------------- TDerivation -------------------------------
void TDerivation::Make(const GSymbolSet* filter)
{
   for (const GFormula* formula : grammar->formulas) {
      FORMULA_DELETED_CONTINUE(formula);
      for (const GProduce& produce : *formula) {
         if (produce.IsEmpty()) continue;
         const GSymbol& sym = produce.front();
         if (sym.IsFormula() && ((filter == NULL) || filter->Have(sym))) {
            Add(formula->head, sym);
         }
      }
   }
   int change;
   do {
      change = 0;
      for (const GFormula* formula : grammar->formulas) {
         FORMULA_DELETED_CONTINUE(formula);
         for (const GProduce& produce : *formula) {
            if (produce.IsEmpty()) continue;
            for (const GSymbol& sym : produce) {
               if (!sym.IsFormula()) break;
               if (Count(sym)) {
                  const GSymbolSet& set_B = Get(sym);
                  for (const GSymbol& sym_B : set_B) {
                     if (Add(formula->head, sym_B)) change++;
                  }
                  break;
               } else {
                  const GFormula& prefix = grammar->Formula(sym);
                  if (!prefix.IsEmpty()) break;
               }
            }
         }
      }
   } while (change);
}

void TDerivation::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   TPrinter printer_item(printer, T_PrintMode::pmCompactGroup | T_PrintMode::pmMultiLine | T_PrintMode::pmOffset);
   int number_item = 0;
   for (const std::pair<const GSymbol&, const GSymbolSet&> item : *this) {
      if (number_item++) printer.eol();
      item.first.print(printer_item);
//      fprintf(file, " -> ");
      item.second.print(printer_item);
   }
   printer.eol();
}

bool GSymbolSetMap::Add(const GSymbol& A, const GSymbol& B)
{
   iterator ip = find(A);
   if (ip == end()) {
      std::pair<const GSymbol&, GSymbolSet> item(A, GSymbolSet());
      item.second.Add(B);
      insert(item);
      return true;
   }
   GSymbolSet& item = (*ip).second;
   if (item.Have(B)) return false;
   return item.Add(B);
}

bool GSymbolSetMap::Get(const GSymbol& A, const GSymbol& B) const
{
   const_iterator ip = find(A);
   if (ip == end()) return false;
   const GSymbolSet& item = (*ip).second;
   return item.Have(B);
}

GSymbolSet& GSymbolSetMap::Get(const GSymbol& A)
{
   iterator ip = find(A);
   if (ip == end()) {
      std::pair<const GSymbol&, GSymbolSet> item(A, GSymbolSet());
      insert(item);
      ip = find(A);
   }
   return (*ip).second;
}

int GSymbolSetMap::Count(const GSymbol& A) const
{
   const_iterator ip = find(A);
   if (ip == end()) return 0;
   return (int)((*ip).second).size();
}

