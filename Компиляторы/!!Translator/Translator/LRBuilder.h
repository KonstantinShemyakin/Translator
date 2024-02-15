#ifndef TRN_LRBUILDER_H
#define TRN_LRBUILDER_H

#include "GBuilder.h"

// ------------------------------------------------ A_LRBuilder -----------------------------------------------
#pragma warning( disable : 4250 )
class A_LRBuilder
{
public:
   A_LRBuilder(TGrammar* g) :grammar(g), Added(g), GOTOtable(g), mode(0) { clear_count(); }
   enum T_Mode {
      tmNone = 0x0000, tmBasic = 0x0001, tmGOTO = 0x0002, tmLALR = 0x0004, tmMakeGOTO = 0x0008, tmLR0 = 0x0010, tmFormulaAndLexeme = 0x0020
   };
public:
   bool make_Table();
   void make_State(const GSymbol& situation, const GSymbol& X);
   void make_State(const GSymbol& situation);
   bool AddAction(const TTableKey& key, const TAction& action);
   const GSymbol Find(const TTableKey&);
   virtual void FirstTailSym(const TPara& para, TFirst& first_beta_a) const;
   virtual bool make_States();
   virtual void make_Action(const GSymbol& situation); // 0x01 - basic, 0x02 - GOTO, 0x04 - LALR, 0x08 - make_go_to
   virtual void Init() = 0;
   virtual void Closure(const TPara& para, TFirst& beta) const = 0;
   virtual void ActionShift(const TPara& para, TFirst& beta) const = 0;
   virtual void ActionReduce(const TPara& para, TFirstFollow& follow) const = 0;
public:
   virtual TParaSet* CLOSURE(const TParaSet& I);
   virtual TParaSet* GOTO(const TParaSet& I, const GSymbol& X);
public:
   TSituationMap* Stable;
   LRTableMap*    LRtable;
   TTableMap      GOTOtable;
   TGrammar*      grammar;
   int            look_ahead;
   int            mode;  // T_Mode
   TClosureAdded  Added;
protected:
   void clear_count();
public: // print
   int not_find, count_empty, shift_count, reduce_count, goto_count, equ_count;
   int delete_count, empty_count, add_count;
   int true_count, false_count;
};

// ---------------------------- T_LRBuilderInit3 -------------------------
class T_LRBuilderInit3 : public virtual A_LRBuilder
{
public:
   T_LRBuilderInit3(TGrammar* g) :A_LRBuilder(g) {}
   virtual void Init();
};

// ---------------------------- T_LRBuilderParaSymReduce -------------------------
class T_LRBuilderParaSymReduce : public virtual A_LRBuilder
{
public:
   T_LRBuilderParaSymReduce(TGrammar* g) :A_LRBuilder(g) {}
   virtual void ActionReduce(const TPara& para, TFirstFollow& follow) const;
};

// ---------------------------- T_LRBuilderFollowReduce ----------------------
class T_LRBuilderFollowReduce : public virtual A_LRBuilder
{
public:
   T_LRBuilderFollowReduce(TGrammar* g) :A_LRBuilder(g) {}
   virtual void ActionReduce(const TPara& para, TFirstFollow& follow) const;
};

// ---------------------------- T_LRBuilderSymShift -------------------------
class T_LRBuilderSymShift : public virtual A_LRBuilder
{
public:
   T_LRBuilderSymShift(TGrammar* g) :A_LRBuilder(g) {}
   void ActionShift(const TPara& para, TFirst& follow) const;
};

// ---------------------------- T_LRBuilderEFFShift -------------------------
class T_LRBuilderEFFShift : public virtual A_LRBuilder
{
public:
   T_LRBuilderEFFShift(TGrammar* g) :A_LRBuilder(g) {}
   void ActionShift(const TPara& para, TFirst& follow) const;
};

// ---------------------------- T_LRBuilderBetaFirstKClosure -------------------------
class T_LRBuilderBetaFirstKClosure : public virtual A_LRBuilder
{
public:
   T_LRBuilderBetaFirstKClosure(TGrammar* g) :A_LRBuilder(g) {}
   virtual void Closure(const TPara& para, TFirst& beta) const;
};

// Green(v=1,5.2.5)
// ---------------------------- TLRBuilder -----------------------------------
class TLRBuilder : public virtual A_LRBuilder, public T_LRBuilderInit3, public T_LRBuilderEFFShift, public T_LRBuilderParaSymReduce, public T_LRBuilderBetaFirstKClosure
{
public:
   TLRBuilder(TGrammar* g) :A_LRBuilder(g), T_LRBuilderInit3(g), T_LRBuilderEFFShift(g), T_LRBuilderParaSymReduce(g), T_LRBuilderBetaFirstKClosure(g) {}
public:
};

#define LRK_TABLE_BUILDER_
#define LRK_EMPTY_TABLE_BUILDER

#ifdef LRK_TABLE_BUILDER
// ---------------------------- TLRTabBuilder -----------------------------------
class TLRTabBuilder : public virtual A_LRBuilder, public T_LRBuilderInit3, public T_LRBuilderEFFShift
{
public:
   TLRTabBuilder(TGrammar* g) :A_LRBuilder(g), T_LRBuilderInit3(g), T_LRBuilderEFFShift(g) {}
public:
   virtual TParaSet* CLOSURE(const TParaSet& I);
   virtual void Closure(const TPara& para, TFirst& beta) const;
   virtual void ActionShift(const TPara& para, TFirst& beta) const;
   virtual void ActionReduce(const TPara& para, TFirstFollow& follow) const;
public:
   TFirstFollowTable table;
};

struct TEmptyChain
{
public:
   TEmptyChain() {}
   TEmptyChain(const GSymbol& e, const GSymbol& c) :empty(e), chain(c) {}
public:
   GSymbol empty, chain;
};

class TEmptyChainTab : public std::map<const GSymbol, TEmptyChain>
{
public:
   TEmptyChain& Get(const GSymbol& key);
};
#endif

// ---------------------------- TSLRBuilder -----------------------------------
// Green(v=2,p=94,7.4.1,a=7.10)
class TSLRBuilder : public virtual A_LRBuilder, public T_LRBuilderInit3, public T_LRBuilderFollowReduce, public T_LRBuilderBetaFirstKClosure
{
public:
   TSLRBuilder(TGrammar* g) :A_LRBuilder(g), T_LRBuilderInit3(g), T_LRBuilderFollowReduce(g), T_LRBuilderBetaFirstKClosure(g) {}
public:
   virtual void ActionShift(const TPara& para, TFirst& beta) const;
};

// ---------------------------- TLR0Builder -----------------------------------
class TLR0Builder : public virtual A_LRBuilder, public T_LRBuilderFollowReduce, public T_LRBuilderSymShift
{
public:
   TLR0Builder(TGrammar* g) :A_LRBuilder(g), T_LRBuilderFollowReduce(g), T_LRBuilderSymShift(g) { mode = tmLR0; }
public:
   virtual void Init();
   virtual void Closure(const TPara& para, TFirst& beta) const;
};

// ---------------------------- TLR1Builder -----------------------------------
class TLR1Builder : public virtual A_LRBuilder, public T_LRBuilderParaSymReduce, public T_LRBuilderSymShift
{
public:
   TLR1Builder(TGrammar* g) :A_LRBuilder(g), T_LRBuilderParaSymReduce(g), T_LRBuilderSymShift(g) {}
public:
   virtual void Init();
   virtual void Closure(const TPara& para, TFirst& beta) const;
};

// Red(p=244)
// ---------------------------- T_LRCoreBuilder -----------------------------------
class T_LRCoreBuilder : public virtual A_LRBuilder
{
public:
   T_LRCoreBuilder(TGrammar* g) :A_LRBuilder(g), CtoAa(g) {}
public:
   virtual void Init();
   virtual void make_Action(const GSymbol& situation);
   virtual void Closure(const TPara& para, TFirst& beta) const {}
   virtual void MuFirstTailSym(const TPara& para, const TAmu& tail, TFirst& first_mu_A) {}
public:
   TC2A CtoAa;
};

// ---------------------------- TLR0CoreBuilder -----------------------------------
class TLR0CoreBuilder : public T_LRCoreBuilder, public T_LRBuilderFollowReduce
{
public:
   TLR0CoreBuilder(TGrammar* g) :A_LRBuilder(g), T_LRCoreBuilder(g), T_LRBuilderFollowReduce(g) { mode = tmLR0 | tmFormulaAndLexeme; }
public:
   virtual TParaSet* GOTO(const TParaSet& I, const GSymbol& X);
   virtual void ActionShift(const TPara& para, TFirst& beta) const;
   virtual void MuFirstTailSym(const TPara& para, const TAmu& tail, TFirst& first_mu_A);
};

// ---------------------------- TLRkCoreBuilder -----------------------------------
class TLRkCoreBuilder : public T_LRCoreBuilder, public T_LRBuilderEFFShift, public T_LRBuilderParaSymReduce
{
public:
   TLRkCoreBuilder(TGrammar* g) :A_LRBuilder(g), T_LRCoreBuilder(g), T_LRBuilderEFFShift(g), T_LRBuilderParaSymReduce(g) { mode = tmFormulaAndLexeme; }
public:
   virtual TParaSet* GOTO(const TParaSet& I, const GSymbol& X);
   virtual void MuFirstTailSym(const TPara& para, const TAmu& tail, TFirst& first_mu_A);
};

#define CORE_POINT_TAILS_
#define CORE_TABLE_BUILDER_

#ifdef CORE_TABLE_BUILDER
// ---------------------------- TLRkCoreTabBuilder -----------------------------------
class TLRkCoreTabBuilder : public TLRkCoreBuilder
{
public:
   TLRkCoreTabBuilder(TGrammar* g) :A_LRBuilder(g), TLRkCoreBuilder(g) { }
public:
   virtual TParaSet* GOTO(const TParaSet& I, const GSymbol& X);
   virtual void ActionShift(const TPara& para, TFirst& beta) const;
   virtual void MuFirstTailSym(const TPara& para, const TAmu& tail, TFirst& first_mu_A);
   virtual void ActionReduce(const TPara& para, TFirstFollow& follow) const;
public:
   TFirstFollowTable table;
};

#endif

// ---------------------------- T_LALRCoreBuilder -----------------------------------
class T_LALRCoreBuilder : public virtual A_LRBuilder
{
public:
   T_LALRCoreBuilder(TGrammar* g) :A_LRBuilder(g) {}
public:
   virtual bool make_States();
public:
   TSituationKernel* LALRStable;
};

// ---------------------------- TLALRkCoreBuilder -----------------------------------
class TLALRkCoreBuilder : public T_LALRCoreBuilder, public TLRkCoreBuilder
{
public:
   TLALRkCoreBuilder(TGrammar* g) :A_LRBuilder(g), T_LALRCoreBuilder(g), TLRkCoreBuilder(g) {}
public:
};

#ifdef CORE_TABLE_BUILDER
// ---------------------------- TLALRkCoreTabBuilder -----------------------------------
class TLALRkCoreTabBuilder : public T_LALRCoreBuilder, public TLRkCoreTabBuilder
{
public:
   TLALRkCoreTabBuilder(TGrammar* g) :A_LRBuilder(g), T_LALRCoreBuilder(g), TLRkCoreTabBuilder(g) {}
public:
};

#endif

// ------------------------------ GrammarSplitting -------------------------------
// Green(v=2,7.4.3)
// Green(v=2,p=104,a=7.12)
class TGGBuilder : public virtual A_LRBuilder, public T_LRBuilderBetaFirstKClosure
{
public:
   TGGBuilder(TGrammarGroup* gr, TGrammar* g) :A_LRBuilder(g), T_LRBuilderBetaFirstKClosure(g), group(gr) {}
   virtual void Init();
   virtual void FirstTailSym(const TPara& para, TFirst& first_beta_a) const;
   virtual void ActionShift(const TPara& para, TFirst& beta) const {}
   virtual void ActionReduce(const TPara& para, TFirstFollow& follow) const {}
public:
   TGrammarGroup* group;
};

// Green(v=2,p=106,a=7.13)
class TGGroupBuilder : public virtual A_LRBuilder
{
public:
   TGGroupBuilder(TGrammarGroup* gr) :A_LRBuilder(gr->general), derivation(gr->general), group(gr) { group->derivation = &derivation; }
   virtual void Init();
   virtual void Closure(const TPara& para, TFirst& beta) const {};
   virtual void ActionShift(const TPara& para, TFirst& beta) const {}
   virtual void ActionReduce(const TPara& para, TFirstFollow& follow) const {}
   virtual TParaSet* CLOSURE(const TParaSet& I);
   virtual TParaSet* GOTO(const TParaSet& I, const GSymbol& X);
public:
   TDerivation derivation;
   TGrammarGroup* group;
};

#endif