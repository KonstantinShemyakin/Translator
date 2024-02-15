#include "stdafx.h"

#include "LRBuilder.h"

void A_LRBuilder::clear_count()
{
   not_find = 0; count_empty = 0; shift_count = 0; reduce_count = 0; goto_count = 0; equ_count = 0;
   delete_count = 0; empty_count = 0; add_count = 0;
   true_count = 0; false_count = 0;
}

bool A_LRBuilder::AddAction(const TTableKey& key, const TAction& action)
{
   int before = LRtable->count();
   bool ret = LRtable->Add(key, action);
   if (before == LRtable->count()) equ_count++; else { if (action.IsShift()) shift_count++; else reduce_count++; }
   return ret;
}

const GSymbol A_LRBuilder::Find(const TTableKey& key_goto)
{
   GSymbol I_j;
   bool go_to = (mode & tmGOTO) != 0, make_go_to = (mode & tmMakeGOTO) != 0;
   if (go_to) {
      I_j = GOTOtable.Find(key_goto);
   } else {
      const TParaSet& situation_items = *Stable->Get(key_goto.key);
      TParaSet* I_A = GOTO(situation_items, key_goto.sym);
      if (!I_A->empty()) {
         I_j = Stable->Find(*I_A);
      } else {
         count_empty++;
      }
      delete I_A;

      if (make_go_to && I_j.IsSituation()) {
         GOTOtable.Add(key_goto, I_j);
      }
   }
   if (!I_j.IsSituation()) {
      not_find += go_to ? -1 : 1;
   }
   return I_j;
}

void A_LRBuilder::FirstTailSym(const TPara& para, TFirst& first_beta_a) const
{
   const GProduce& produce = grammar->Produce(para);
   const GSymbol& a = para.sym;

   GSymbolVector beta;
   produce.Tail(para, beta);
   if (a.IsVector()) {
      beta << grammar->Vector(a);
   } else {
      beta << a;
   }
   grammar->FIRSTs.FIRST(beta, first_beta_a, grammar->look_ahead);
}

void A_LRBuilder::make_Action(const GSymbol& situation)
{
   const TParaSet& situation_items = *Stable->Get(situation);
   bool go_to = (mode & tmGOTO) != 0, make_go_to = (mode & tmMakeGOTO) != 0;
   for (const TPara& para : situation_items) {
      const GProduce& produce = grammar->Produce(para);
      if ((para.point < produce.count()) && produce[para.point].IsTerminal()) {
         const GSymbol& a = produce[para.point];

         TFirst eff_beta2_v;
         ActionShift(para, eff_beta2_v);

         TTableKey key_goto(situation, a);
         GSymbol I_j = Find(key_goto);

         if (I_j.IsSituation()) {
            TAction action(TAction::taShift, I_j);
            for (const GSymbol& u : eff_beta2_v) {
               TTableKey key(situation, u);
               AddAction(key, action);
            }
         }
      }
      if ((para.point == produce.count()) || produce.IsEmpty()) {
         if (grammar->IsStart(produce.head)) {
            TAction action(TAction::taAccept, produce.head);
            TTableKey key(situation, GSymbol::empty);
            AddAction(key, action);
         } else {
            TAction action(TAction::taReduce, produce.head);

            TFirstFollow follow;
            ActionReduce(para, follow);

            for (const GSymbol& a : follow) {
               TTableKey key(situation, a);
               AddAction(key, action);
            }
         }
      }
   }
   for (const GFormula* formula : grammar->formulas) {
      const GSymbol& A = formula->head;
      if (grammar->IsStart(A)) continue;

      TTableKey key(situation, A);
      GSymbol I_j = Find(key);

      if (I_j.IsSituation()) {
         TAction action(TAction::taGoto, I_j);
         AddAction(key, action);
      }
   }
}

bool A_LRBuilder::make_Table()
{
   bool ret = true;
   printf("\nAction");
   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable->count(); situation.situation++) {
      if ((situation.situation % 100) == 0) {
         printf("\n%05d,%05d", situation.situation, LRtable->count());
      }
      const TParaSet& situation_items = *Stable->Get(situation);
      make_Action(situation);
   }
   printf("\n%05d,%05d, not_find=%d, empty=%d, shift=%d, reduce=%d, goto=%d, equ=%d\n", Stable->count(), LRtable->count(), not_find, count_empty, shift_count, reduce_count, goto_count, equ_count);

   return ret;
}

void A_LRBuilder::make_State(const GSymbol& situation, const GSymbol& X)
{
   const TParaSet *I = Stable->Get(situation);
   TParaSet *I_X = GOTO(*I, X);
   if (I_X->empty()) { delete I_X; delete_count++; empty_count++; return; }
   //   I_X->print(NULL, 0x00, stdout);
   int before = Stable->count();
   const GSymbol go_to = Stable->Add(I_X);
   if (before == Stable->count()) {
      delete I_X;
      delete_count++;
   } else {
      add_count++;
   }
   TTableKey key(situation, X);
   GOTOtable.Add(key, go_to);
}

void A_LRBuilder::make_State(const GSymbol& situation)
{
   bool FormulaAndLexeme = (mode & tmFormulaAndLexeme) != 0;
   TParaSet *I = Stable->Get(situation);
   I->mode = -1;
   int new_step = Stable->step++;
   if (FormulaAndLexeme || (I->count() > (grammar->lexemes.count() + grammar->formulas.count()))) {
      for (const GFormula* formula : grammar->formulas) {
         FORMULA_DELETED_CONTINUE(formula);
         const GSymbol& X = formula->head;
         make_State(situation, X);
      }
      for (const std::pair<const GSymbol&, int> item : grammar->lexemes) {
         const GSymbol& X = item.first;
         make_State(situation, X);
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
         make_State(situation, X);
      }
   }
   I->mode = new_step;
}

bool A_LRBuilder::make_States()
{
   bool ret = true;

   Init();

   clear_count();
   printf("\nSituation");

   for (GSymbol situation(GSymbol::gsSituation); situation.situation < Stable->count(); situation.situation++) {
      if ((situation.situation % 100) == 0) {
         printf("\n%05d,%05d,%05d", situation.situation, Stable->count(), (int)GOTOtable.size());
      }
      make_State(situation);
   }
   printf("\n%05d,%05d", Stable->count(), GOTOtable.count());
   Stable->print();
   printf("\n--- GOTOtable --- <%d> ---\n", GOTOtable.count());

   return ret;
}

TParaSet* A_LRBuilder::CLOSURE(const TParaSet& I)
{
   TParaSet* closure = new TParaSet(grammar, I);
   Added.Next();
   int work;
   do {
      work = 0;
      const TParaSet J(*closure);
      for (const TPara& para : J) {
         const GSymbol& a = para.sym;
         const GProduce& produce = grammar->Produce(para);
         if (para.point < produce.count()) {
            const GSymbol& sym_B = produce[para.point];
            if (!sym_B.IsFormula()) continue;
            const GFormula& formula_B = grammar->Formula(sym_B);

            TFirst first_beta_a;
            Closure(para, first_beta_a);

            for (const GSymbol& b : first_beta_a) {
               bool added = Added.Added(sym_B, b);
               if (added) { false_count--; continue; }
               TPara gamma(GSymbol(GSymbol::gsPara, sym_B.formula), b);
               for (gamma.produce = 0; gamma.produce < formula_B.count(); gamma.produce++) {
                  if (!closure->Have(gamma)) {
                     (*closure) << gamma; work++;
                     true_count++;
                  } else {
                     false_count++;
                  }
               }
            }
         }
      }
   } while (work);
   return closure;
}

TParaSet* A_LRBuilder::GOTO(const TParaSet& I, const GSymbol& X)
{
   TParaSet closure(grammar);
   for (const TPara& para : I) {
      const GProduce& produce = grammar->Produce(para);
      if (para.point < produce.count()) {
         const GSymbol& sym_B = produce[para.point];
         if (!(sym_B == X)) continue; // (B !== X) 
         TPara shift_para(para); shift_para.point++;
         closure << shift_para;
      }
   }
   return CLOSURE(closure);
}

// ---------------------------- T_LRBuilderInit3 -------------------------
void T_LRBuilderInit3::Init()
{
   Added.Init(3);

   const GSymbol eof(GSymbol::empty);
   TPara S(GSymbol(GSymbol::T_Type::gsPara), eof);
   TParaSet I(grammar, S);
   TParaSet* J = CLOSURE(I);
   Stable->Add(J);
}

// ---------------------------- T_LRBuilderParaSymReduce -------------------------
void T_LRBuilderParaSymReduce::ActionReduce(const TPara& para, TFirstFollow& follow) const
{
   follow << para.sym;
}

// ---------------------------- T_LRBuilderFollowReduce ----------------------
void T_LRBuilderFollowReduce::ActionReduce(const TPara& para, TFirstFollow& follow) const
{
   GSymbol A(GSymbol::gsFormula, para.formula);
   follow = grammar->Follow(A);
}

// ---------------------------- T_LRBuilderSymShift -------------------------
void T_LRBuilderSymShift::ActionShift(const TPara& para, TFirst& first) const
{
   const GProduce& produce = grammar->Produce(para);
   const GSymbol& a = produce[para.point];
   //   first.owner = &grammar->FIRSTs;
   first << a;
}

// ---------------------------- T_LRBuilderEFFShift -------------------------
void T_LRBuilderEFFShift::ActionShift(const TPara& para, TFirst& eff_beta2_v) const
{
   const GProduce& produce = grammar->Produce(para);
   //   eff_beta2_v.owner = &grammar->EFFs;

   GSymbolVector beta2_v;
   produce.SymAndTail(para, beta2_v);
   if (para.sym.IsVector()) {
      beta2_v << grammar->Vector(para.sym);
   } else {
      beta2_v << para.sym;
   }
   grammar->EFFs.EFF(beta2_v, eff_beta2_v, look_ahead);
}

// ---------------------------- T_LRBuilderBetaFirstKClosure -------------------------
void T_LRBuilderBetaFirstKClosure::Closure(const TPara& para, TFirst& first_beta_a) const
{
   FirstTailSym(para, first_beta_a);
}

#ifdef LRK_TABLE_BUILDER
TEmptyChain& TEmptyChainTab::Get(const GSymbol& key)
{
   iterator ip = find(key);
   if (ip != end()) return (*ip).second;
   std::pair<const GSymbol, TEmptyChain> item(key, TEmptyChain());
   insert(item);
   return (*find(key)).second;
}

TParaSet* TLRTabBuilder::CLOSURE(const TParaSet& I)
{
   TParaSet queue(grammar, I);
   TEmptyChainTab Us;

   while (!queue.empty()) {
      const TPara para = *queue.begin(); queue.erase(queue.begin());
      const GProduce& key = grammar->Produce(para);
      if (para.point < key.count()) {
         const GSymbol& sym_B = key[para.point];
         if (!sym_B.IsFormula()) continue;
         const GFormula& formula_B = grammar->Formula(sym_B);

         TFirst first_beta_a;
         Closure(para, first_beta_a);

#ifdef LRK_EMPTY_TABLE_BUILDER
         bool yes_empty = first_beta_a.Del(GSymbol::empty);
#else
         bool yes_empty = false;
#endif
         GSymbol u;

         bool change_empty = false, change_chain = false;
         TPara gamma(GSymbol(GSymbol::gsPara, sym_B.formula));
         for (gamma.key = 0; gamma.key < formula_B.count(); gamma.key++) {
            TEmptyChain& U = Us.Get(gamma);
            if (!gamma.key) {
               change_empty = yes_empty && !U.empty.IsEmpty();

               if (!first_beta_a.empty()) {
                  if (U.chain.IsNone()) {
                     u = table.Table(first_beta_a);
                     change_chain = true;
                  } else {
                     TFirstFollow look_ahead_symbols = table.Table(U.chain);
                     if (look_ahead_symbols += first_beta_a) {
                        u = table.Table(look_ahead_symbols);
                        change_chain = true;
                     }
                  }
               }
               if (!change_empty && !change_chain) break;
            }
            if (change_empty) {
               gamma.sym = U.empty = GSymbol::empty;
               queue << gamma;
            }
            if (change_chain) {
               gamma.sym = U.chain = u;
               queue << gamma;
            }
         }
      }
   }

   TParaSet* closure = new TParaSet(grammar, I);
   for (std::pair<const GSymbol&, const TEmptyChain&> item : Us) {
      TPara gamma(item.first);
      const TEmptyChain& U = item.second;
      if (!U.empty.IsNone()) {
         gamma.sym = U.empty;
         (*closure) << gamma;
      }
      if (!U.chain.IsNone()) {
         gamma.sym = U.chain;
         (*closure) << gamma;
      }
   }
   return closure;
}

void TLRTabBuilder::Closure(const TPara& para, TFirst& first_beta_a) const
{
   const GProduce& key = grammar->Produce(para);
   const GSymbol& para_sym = para.sym;

   GSymbolVector beta;
   key.Tail(para, beta);
   if (para_sym.IsTable()) {
      const TFirstFollow& tab = table.Table(para_sym);
      for (const GSymbol& sym : tab) {
         GSymbolVector my_beta(beta);
         if (sym.IsVector()) {
            my_beta << grammar->Vector(sym);
         } else {
            my_beta << sym;
         }
         TFirst first_delta_b;
         grammar->FIRSTs.FIRST(my_beta, first_delta_b, look_ahead);
         first_beta_a << first_delta_b;
      }
   } else {
      if (para_sym.IsVector()) {
         beta << grammar->Vector(para_sym);
      } else {
         beta << para_sym;
      }
      grammar->FIRSTs.FIRST(beta, first_beta_a, look_ahead);
   }
}

void TLRTabBuilder::ActionReduce(const TPara& para, TFirstFollow& follow) const
{
   const GSymbol& para_sym = para.sym;
   if (para_sym.IsTable()) {
      const TFirstFollow& tab = table.Table(para_sym);
      for (const GSymbol& sym : tab) {
         follow << sym;
      }
   } else {
      follow << para_sym;
   }
}

void TLRTabBuilder::ActionShift(const TPara& para, TFirst& eff_beta2_v) const
{
   const GProduce& key = grammar->Produce(para);
   const GSymbol& para_sym = para.sym;

   GSymbolVector beta;
   key.SymAndTail(para, beta);
   if (para_sym.IsTable()) {
      TFirst first_delta_b;
      const TFirstFollow& tab = table.Table(para_sym);
      for (const GSymbol& sym : tab) {
         GSymbolVector my_beta(beta);
         if (sym.IsVector()) {
            my_beta << grammar->Vector(sym);
         } else {
            my_beta << sym;
         }
         first_delta_b.clear();
         grammar->EFFs.EFF(my_beta, first_delta_b, look_ahead);
         eff_beta2_v << first_delta_b;
      }
   } else {
      if (para_sym.IsVector()) {
         beta << grammar->Vector(para_sym);
      } else {
         beta << para_sym;
      }
      grammar->EFFs.EFF(beta, eff_beta2_v, look_ahead);
   }
}

#endif

// ---------------------------- TSLRBuilder -----------------------------------
// Green(v=2,p=94,7.4.1,a=7.10)
void TSLRBuilder::ActionShift(const TPara& para, TFirst& eff) const
{
   const GProduce& produce = grammar->Produce(para);
   //   eff.owner = &grammar->EFFs;

   GSymbolVector beta;
   produce.SymAndTail(para, beta);
   GSymbol A(GSymbol::gsFormula, para.formula);
   const TFirstFollow& follow_A = grammar->Follow(A);
   for (const GSymbol& a : follow_A) {
      GSymbolVector beta_follow(beta);
      if (a.IsVector()) {
         beta_follow << grammar->Vector(a);
      } else {
         beta_follow << a;
      }
      TFirst eff_follow;
      grammar->EFFs.EFF(beta_follow, eff_follow, look_ahead);
      eff << eff_follow;
   }
}

// ---------------------------- TLR0Builder -----------------------------------
void TLR0Builder::Init()
{
   Added.Init(0);

   TPara S(GSymbol::gsPara);
   TParaSet I(grammar, S);
   TParaSet* J = CLOSURE(I);
   Stable->Add(J); Stable->step++;
}

void TLR0Builder::Closure(const TPara& para, TFirst& first_beta_a) const
{
   first_beta_a << GSymbol::none;
}

// ---------------------------- TLR1Builder -----------------------------------
void TLR1Builder::Init()
{
   Added.Init(1);

   const GSymbol eof(GSymbol::empty);
   TPara S(GSymbol(GSymbol::T_Type::gsPara), eof);
   TParaSet I(grammar, S);
   TParaSet* J = CLOSURE(I);
   Stable->Add(J); Stable->step++;
}

void TLR1Builder::Closure(const TPara& para, TFirst& first_beta_a) const
{
   const GProduce& produce = grammar->Produce(para);
   const GSymbol& a = para.sym;

   GSymbolVector beta;
   produce.Tail(para, beta);
   beta << a;

   first_beta_a = TFirst(beta, &grammar->FIRSTs);
}

// ---------------------------- T_LRCoreBuilder -----------------------------------
void T_LRCoreBuilder::Init()
{
   CtoAa.Core();
   Added.Init((mode & tmLR0) ? 0 : 4);
   CtoAa.Split();

   TPara S(GSymbol(GSymbol::T_Type::gsPara), GSymbol::none);
   if (!(mode & tmLR0)) S.sym = GSymbol::empty;
   TParaSet* I = new TParaSet(grammar, S);
   Stable->Add(I); Stable->step++;
}

void T_LRCoreBuilder::make_Action(const GSymbol& situation)
{
   const TParaSet& situation_items = *Stable->Get(situation);
   for (const TPara& para_B : situation_items) { // [B -> gamma . ? delta, b ]
      const GProduce& produce_B = grammar->Produce(para_B);
      if (para_B.point < produce_B.count()) {
         const GSymbol& sym_B = produce_B[para_B.point];
         if (sym_B.IsFormula()) { // [B -> gamma . C delta, b ]
            const GSymbol& C = sym_B;
            Tc2a& C_A = CtoAa.Get(C);

            TFirst eff_beta2_v;
            ActionShift(para_B, eff_beta2_v);
            for (const GSymbol& u : eff_beta2_v) {
               TTableKey key_goto(situation, u);
               if (u.IsVector()) {
                  const GSymbolVector& u_vector = grammar->Vector(u);
                  key_goto.sym = u_vector.front();
               }
               GSymbol I_j = GOTOtable.Find(key_goto);
               if (I_j.IsSituation()) {
                  TAction action(TAction::taShift, I_j);
                  TTableKey key(situation, u);
                  AddAction(key, action);
               } else {
                  not_find += -1;
               }
            }
            const TAmus& tails = C_A.Get(GSymbol::empty);
            for (std::pair<const GSymbol&, const TAmu&> item_mu : tails) {
               const TAmu& tail = item_mu.second;

               TFirst first_mu_A;
               MuFirstTailSym(para_B, tail, first_mu_A);

               GSymbol A(GSymbol::gsProduce, tail.point.formula, tail.point.produce);
               const GProduce& produce_A = grammar->Produce(A);
               TAction action(TAction::taReduce, produce_A.head);
               for (const GSymbol& a : first_mu_A) {
                  TTableKey key(situation, a); key.sym.value = 0;
                  AddAction(key, action);
               }
            }
         } else if (sym_B.IsTerminal()) {
            TTableKey key_goto(situation, sym_B); key_goto.sym.value = 0;
            GSymbol I_j = GOTOtable.Find(key_goto);

            if (I_j.IsSituation()) {
               TAction action(TAction::taShift, I_j);
               TFirst eff_beta2_v;
               ActionShift(para_B, eff_beta2_v);
               for (const GSymbol& u : eff_beta2_v) {
                  TTableKey key(situation, u);
                  AddAction(key, action);
               }
            } else {
               not_find += -1;
            }
         }
      }
      if ((para_B.point == produce_B.count()) || produce_B.IsEmpty()) {
         if (produce_B.head.IsStart()) {
            TAction action(TAction::taAccept, produce_B.head);
            TTableKey key(situation, (mode & tmLR0) ? GSymbol::eof : GSymbol::empty);
            AddAction(key, action);
         } else {
            TAction action(TAction::taReduce, produce_B.head);
            TFirstFollow follow;
            ActionReduce(para_B, follow);

            for (const GSymbol& a : follow) {
               TTableKey key(situation, a);
               AddAction(key, action);
            }
         }
      }
   }
}

// ---------------------------- TLR0CoreBuilder -----------------------------------
void TLR0CoreBuilder::MuFirstTailSym(const TPara& para, const TAmu& tail, TFirst& first_mu_A)
{
   first_mu_A = (TFirst&)grammar->Follow(GSymbol(GSymbol::gsFormula, tail.point.formula));
}

void TLR0CoreBuilder::ActionShift(const TPara& para, TFirst& eff_beta2_v) const
{
   const GProduce& produce = grammar->Produce(para);
   const GSymbol& sym_B = produce[para.point];
   if (sym_B.IsFormula()) { // [B -> gamma . C delta, b ]
      const GSymbol& C = sym_B;
      const Tc2a& C_A = (const Tc2a)CtoAa.Get(C);
      (GSymbolSet&)eff_beta2_v = C_A.terminals;
   } else if (sym_B.IsTerminal()) {
      eff_beta2_v << sym_B;
   }
}

TParaSet* TLR0CoreBuilder::GOTO(const TParaSet& I, const GSymbol& X)
{
   TParaSet* go_to = new TParaSet(grammar);
   for (const TPara& para_B : I) {
      if ((I.mode > 0) && (para_B.sym.value <= I.mode)) continue;
      const GProduce& produce_B = grammar->Produce(para_B); // [B -> gamma . ? delta, b ]
      if (para_B.point < produce_B.count()) {
         const GSymbol& sym_B = produce_B[para_B.point];
         if (sym_B == X) {  // [B -> gamma . X delta, b ]
            TPara shift_para(para_B); shift_para.point++;
            (*go_to) << shift_para;
         }
         if (sym_B.IsFormula()) { // [B -> gamma . C delta, b ]
            const GSymbol& C = sym_B;
            Tc2a& C_A = CtoAa.Get(C);
            const TAmus& tails = C_A.Get(X);
            for (std::pair<const GSymbol&, const TAmu&> item_mu : tails) {
               const TAmu& tail = item_mu.second;
               GSymbol para(GSymbol::gsPara, tail.point.formula, tail.point.produce, tail.point.point + 1);

               int before = go_to->count();
               (*go_to) << TPara(para, GSymbol::none);
               if (go_to->count() == before) add_count++;

            }
         }
      }
   }
   return go_to;
}

// ---------------------------- TLRkCoreBuilder -----------------------------------
void TLRkCoreBuilder::MuFirstTailSym(const TPara& para, const TAmu& tail, TFirst& first_mu_A)
{
#ifndef CORE_POINT_TAILS
   FirstTailSym(para, first_mu_A);
#else
   TBTailItem* delta = CtoAa.point_tails.Get(para);
   if (!delta->delta.empty()) {
      first_delta_b = delta->delta;
   }
   if (!delta->half.empty()) {
      TFirst first, first_b;
      first_b << para.sym; // b
      grammar->Vectors().Plus(delta->half, first_b, first, look_ahead);
      first_delta_b << first;
   }
   grammar->Vectors().Plus(tail.mu, first_delta_b, first_mu_A, look_ahead);
#endif
}

TParaSet* TLRkCoreBuilder::GOTO(const TParaSet& I, const GSymbol& X)
{
   Added.Next(); GSymbol added_produce(GSymbol::gsProduce);
   TParaSet* go_to = new TParaSet(grammar);
   for (const TPara& para_B : I) {
      if ((I.mode > 0) && (para_B.sym.value <= I.mode)) continue;
      const GProduce& produce_B = grammar->Produce(para_B); // [B -> gamma . ? delta, b ]
      if (para_B.point < produce_B.count()) {
         const GSymbol& sym_B = produce_B[para_B.point];
         if (sym_B == X) {  // [B -> gamma . X delta, b ]
            TPara shift_para(para_B); shift_para.point++;
            (*go_to) << shift_para;
         }
         if (sym_B.IsFormula()) { // [B -> gamma . C delta, b ]
            const GSymbol& C = sym_B;
            Tc2a& C_A = CtoAa.Get(C);
            const TAmus& tails = C_A.Get(X);
            if (tails.empty()) continue;

            TFirst first_delta_b;
#ifndef CORE_POINT_TAILS
            FirstTailSym(para_B, first_delta_b);
#else
            TBTailItem* delta = CtoAa.point_tails.Get(para_B);
            if (!delta->delta.empty()) {
               first_delta_b = delta->delta;
            }
            if (!delta->half.empty()) {
               TFirst first, first_b;
               first_b << para_B.sym; // b
               grammar->Vectors().Plus(delta->half, first_b, first, look_ahead);
               first_delta_b << first;
            }
#endif
            for (std::pair<const GSymbol&, const TAmu&> item_mu : tails) {
               const TAmu& tail = item_mu.second;
               added_produce.value = tail.produce;
               GSymbol para(GSymbol::gsPara, tail.point.formula, tail.point.produce, tail.point.point + 1);
               TFirst first_mu_A;
               // [ A -> X . beta , ?]
               if (!tail.half.empty()) {
                  grammar->Vectors().Plus(tail.half, first_delta_b, first_mu_A, look_ahead);
               }
               if (!tail.mu.empty() && (tail.step != Added.Current())) {
                  for (const GSymbol& a : tail.mu) {
                     bool added = Added.Added(added_produce, a);
                     if (added) { false_count--; continue; }
                     (*go_to) << TPara(para, a);
                  }
               } else {
                  count_empty++;
               }
               for (const GSymbol& a : first_mu_A) {
                  bool added = Added.Added(added_produce, a);
                  if (added) { false_count--; continue; }
                  (*go_to) << TPara(para, a);
               }
               tail.step = Added.Current();
            }
         }
      }
   }
   return go_to;
}

// ---------------------------- T_LALRCoreBuilder -----------------------------------
bool T_LALRCoreBuilder::make_States()
{
   bool ret = true;
   Init();

   int step = 0;
   for (GSymbol situation; LALRStable->queue.Pop(situation); ) {
      if ((++step % 100) == 0) {
         printf("\n%05d,%05d,%05d,%05d", situation.situation, LALRStable->count(), (int)GOTOtable.size(), (int)LALRStable->queue.size());
      }
      make_State(situation);
   }
   printf("\n%05d,%05d", LALRStable->count(), GOTOtable.count());
   LALRStable->print();
   printf("\n--- GOTOtable --- <%d> ---\n", GOTOtable.count());

   return ret;
}

#ifdef CORE_TABLE_BUILDER
void TLRkCoreTabBuilder::ActionReduce(const TPara& para, TFirstFollow& follow) const
{
   const GSymbol& para_sym = para.sym;
   if (para_sym.IsTable()) {
      const TFirstFollow& tab = table.Table(para_sym);
      for (const GSymbol& sym : tab) {
         follow << sym;
      }
   } else {
      follow << para_sym;
   }
}

void TLRkCoreTabBuilder::ActionShift(const TPara& para, TFirst& eff_beta2_v) const
{
   const GProduce& key = grammar->Produce(para);
   const GSymbol& para_sym = para.sym;

   GSymbolVector beta;
   key.SymAndTail(para, beta);
   if (para_sym.IsTable()) {
      TFirst first_delta_b;
      const TFirstFollow& tab = table.Table(para_sym);
      for (const GSymbol& sym : tab) {
         GSymbolVector my_beta(beta);
         if (sym.IsVector()) {
            my_beta << grammar->Vector(sym);
         } else {
            my_beta << sym;
         }
         first_delta_b.clear();
         grammar->EFFs.EFF(my_beta, first_delta_b, look_ahead);
         eff_beta2_v << first_delta_b;
      }
   } else {
      if (para_sym.IsVector()) {
         beta << grammar->Vector(para_sym);
      } else {
         beta << para_sym;
      }
      grammar->EFFs.EFF(beta, eff_beta2_v, look_ahead);
   }
}

void TLRkCoreTabBuilder::MuFirstTailSym(const TPara& para, const TAmu& tail, TFirst& first_mu_A)
{
   const GProduce& key = grammar->Produce(para);
   const GSymbol& para_sym = para.sym;

   GSymbolVector beta;
   key.Tail(para, beta);
   if (para_sym.IsTable()) {
      const TFirstFollow& tab = table.Table(para_sym);
      for (const GSymbol& sym : tab) {
         GSymbolVector my_beta(beta);
         if (sym.IsVector()) {
            my_beta << grammar->Vector(sym);
         } else {
            my_beta << sym;
         }
         TFirst first_delta_b, my_first_mu_A;
         grammar->FIRSTs.FIRST(my_beta, first_delta_b, look_ahead);
         grammar->Vectors().Plus(tail.mu, first_delta_b, my_first_mu_A, look_ahead);
         first_mu_A << my_first_mu_A;
      }
   } else {
      if (para_sym.IsVector()) {
         beta << grammar->Vector(para_sym);
      } else {
         beta << para_sym;
      }
      TFirst first_delta_b;
      grammar->FIRSTs.FIRST(beta, first_delta_b, look_ahead);
      grammar->Vectors().Plus(tail.mu, first_delta_b, first_mu_A, look_ahead);
   }
}

TParaSet* TLRkCoreTabBuilder::GOTO(const TParaSet& I, const GSymbol& X)
{
   Added.Next();
   TEmptyChainTab Us;
   for (const TPara& para_B : I) {
      if ((I.mode > 0) && (para_B.sym.value <= I.mode)) continue;
      const GProduce& produce_B = grammar->Produce(para_B); // [B -> gamma . ? delta, b ]
      if (para_B.point < produce_B.count()) {
         const GSymbol& sym_B = produce_B[para_B.point];
         if (sym_B == X) {  // [B -> gamma . X delta, b ]
            TPara shift_para(para_B); shift_para.point++;
            TEmptyChain& U = Us.Get(shift_para);
            if (U.chain.IsNone()) {
               U.chain = shift_para.sym;
            } else {
               TFirstFollow symbols = table.Table(U.chain);
               const TFirstFollow& symbols_para = table.Table(shift_para.sym);
               if (symbols += symbols_para) {
                  U.chain = table.Table(symbols);
               }
            }
         }
         if (sym_B.IsFormula()) { // [B -> gamma . C delta, b ]
            const GSymbol& C = sym_B;
            Tc2a& C_A = CtoAa.Get(C);
            const TAmus& tails = C_A.Get(X);
            if (tails.empty()) continue;

            std::vector<TFirst> first_delta_b_s;
            const GSymbol& para_sym = para_B.sym;

            GSymbolVector beta;
            produce_B.Tail(para_B, beta);
            if (para_sym.IsTable()) {
               const TFirstFollow& tab = table.Table(para_sym);
               for (const GSymbol& sym : tab) {
                  GSymbolVector my_beta(beta);
                  if (sym.IsVector()) {
                     my_beta << grammar->Vector(sym);
                  } else {
                     my_beta << sym;
                  }
                  TFirst first_delta_b;
                  grammar->FIRSTs.FIRST(my_beta, first_delta_b, grammar->look_ahead);
                  first_delta_b_s.push_back(first_delta_b);
                  CtoAa.point_tails.Add(para_B);
               }
            } else {
               if (para_sym.IsVector()) {
                  beta << grammar->Vector(para_sym);
               } else {
                  beta << para_sym;
               }
               TFirst first_delta_b;
               grammar->FIRSTs.FIRST(beta, first_delta_b, grammar->look_ahead);
               first_delta_b_s.push_back(first_delta_b);
            }

            for (std::pair<const GSymbol&, const TAmu&> item_mu : tails) {
               const TAmu& tail = item_mu.second;
               GSymbol para(GSymbol::gsPara, tail.point.formula, tail.point.key, tail.point.point + 1);
               // [ A -> X . beta , ?]
               TFirstFollow look_ahead_symbols;
               if (!tail.half.empty()) {
                  for (const TFirst& first_delta_b : first_delta_b_s) {
                     TFirst first_mu_A;
                     grammar->Vectors().Plus(tail.half, first_delta_b, first_mu_A, look_ahead);
                     look_ahead_symbols << first_mu_A;
                  }
               }

               look_ahead_symbols << tail.mu;
               if (look_ahead_symbols.empty()) continue;

               TEmptyChain& U = Us.Get(para);
               if (U.chain.IsNone()) {
                  U.chain = table.Table(look_ahead_symbols);
               } else {
                  TFirstFollow symbols = table.Table(U.chain);
                  if (symbols += look_ahead_symbols) {
                     U.chain = table.Table(symbols);
                  }
               }
            }
         }
      }
   }

   TParaSet* go_to = new TParaSet(grammar);
   for (std::pair<const GSymbol&, const TEmptyChain&> item : Us) {
      const TEmptyChain& U = item.second;
      TPara para(item.first); para.sym = U.chain;
      (*go_to) << para;
   }
   return go_to;
}

#endif

// ------------------------------ GrammarSplitting -------------------------------
// Green(v=2,7.4.3)
// Green(v=2,p=104,a=7.12)
void TGGBuilder::Init()
{
   Added.Init(3);
   GFormula* formula = grammar->root;
   TParaSet I(grammar);

   if (grammar->option & TGrammar::opSplittingAddition) {
      GSymbol S_(((TGrammarGroupItem*)grammar)->S_);
      TPara S(GSymbol(GSymbol::T_Type::gsPara, S_.formula, 0, 0), GSymbol::empty);
      I.Add(S);
   } else {
      const TFollow& follow = ((TGrammarGroupItem*)grammar)->general->Follow(formula->head);
      for (const GSymbol& a : follow) {
         TPara S(GSymbol(GSymbol::T_Type::gsPara, formula->head.formula, 0, 0), a);
         for (; S.produce < formula->count(); S.produce++) {
            I.Add(S);
         }
      }
   }

   TParaSet* J = CLOSURE(I);
   Stable->Add(J);
}

void TGGBuilder::FirstTailSym(const TPara& para, TFirst& first_beta_a) const
{
   if (grammar->option & TGrammar::opSplittingAddition) {
      first_beta_a << GSymbol::none;
   } else {
      const GProduce& produce = grammar->Produce(para);
      const GSymbol& a = para.sym;

      GSymbolVector beta;
      produce.Tail(para, beta);
      if (a.IsVector()) {
         beta << grammar->Vector(a);
      } else {
         beta << a;
      }
      for (GSymbol& sym : beta) {
         group->TerminalToFormula(sym);
      }
      ((TGrammarGroupItem*)grammar)->general->FIRSTs.FIRST(beta, first_beta_a, grammar->look_ahead);
   }
}

// Green(v=2,p=106,a=7.13)
void TGGroupBuilder::Init()
{
   GSymbolSet filter;
   for (std::pair<const GSymbol&, const TGrammarGroupItem*> item : (*group)) {
      filter.Add(item.first);
   }
   derivation.Make(&filter);
   for (const GSymbol& S : filter) {
      if (!derivation.Count(S)) {
         derivation.Add(S, S);
      }
   }

   Added.Init(-1);
   GFormula* formula = grammar->root;
   TParaSet I(grammar);
   if (grammar->option & TGrammar::opSplittingAddition) {
      TPara S_P(GSymbol(GSymbol::gsPara, formula->head.formula, 0, 0), GSymbol::empty); I.Add(S_P);
   } else {
      TPara S_S(GSymbol(GSymbol::gsSituation, 0), GSymbol(GSymbol::gsFormula, 0)); I.Add(S_S);
   }

   TParaSet* J = CLOSURE(I);
   Stable->Add(J);
}

TParaSet* TGGroupBuilder::CLOSURE(const TParaSet& I)
{
   TParaSet* closure = new TParaSet(grammar, I);
   int work;
   do {
      work = 0;
      const TParaSet J(*closure);
      for (const TPara& para_B : J) {
         TParaSet para_set(grammar); const TParaSet* pointer;
         if (para_B.IsPara()) {
            para_set << para_B;
            pointer = &para_set;
         } else { // situation
            TGrammarGroup::const_iterator ig = group->find(para_B.sym);
            const TGrammarGroupItem& item_grammar = *(*ig).second;
            pointer = item_grammar.Stable.Get(para_B);
         }
         for (const TPara& para : *pointer) {
            const GProduce& produce = grammar->Produce(para);
            if (para.point < produce.count()) {
               const GSymbol& sym_B = produce[para.point];
               if (sym_B.IsFormula() && derivation.Count(sym_B)) {
                  const GSymbolSet& set_S = derivation.Get(sym_B);
                  for (const GSymbol& Si : set_S) {
                     TPara para_Si(GSymbol(GSymbol::gsSituation, 0), Si);
                     if ((*closure) += para_Si) work++;
                  }
               }
            }
         }
      }
   } while (work);
   return closure;
}

TParaSet* TGGroupBuilder::GOTO(const TParaSet& I, const GSymbol& X)
{
   TParaSet closure(grammar);
   for (const TPara& para : I) {
      if (para.IsPara()) {
         const GProduce& produce = grammar->Produce(para);
         if (para.point < produce.count()) {
            const GSymbol& sym_B = produce[para.point];
            if (!(sym_B == X)) continue; // (B !== X) 
            TPara shift_para(para); shift_para.point++;
            closure << shift_para;
         }
      } else { // situation
         TGrammarGroup::const_iterator ig = group->find(para.sym);
         const TGrammarGroupItem& item_grammar = *(*ig).second;
         TTableKey key_goto((const GSymbol&)para, X);
         group->FormulaToTerminal(key_goto.sym);
         const GSymbol& I_j = item_grammar.GOTOtable.Find(key_goto);
         if (!I_j.IsNone()) {
            TPara para_goto(I_j, para.sym);
            closure << para_goto;
         }
      }
   }
   return CLOSURE(closure);
}
