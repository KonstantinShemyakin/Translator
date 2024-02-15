#if !defined(DEFINE_RULE_MACRO_H)
#define DEFINE_RULE_MACRO_H

#define FORMULA(TYPE)  { GFormula* formula = new GFormula(GSymbol(GSymbol::gsFormula,names.Add(#TYPE))); formula->title = #TYPE; formulas.Add(formula);
#define PRODUCE        { GProduce produce(GSymbol(GSymbol::gsProduce,formula->head.formula,formula->count())); formula->Add(produce); GProduce* rule = &formula->back();
#define END } 
#define TITLE(T)       rule->title = #T;

#define LEX(G)       { GSymbol item(GSymbol::gsTerminal,T_Lexeme::T_Group::gr##G,0); rule->Add(item); }
#define SYM(S)       { GSymbol item(GSymbol::gsTerminal,T_Lexeme::T_Group::grSeparator,A_Symbol::T_Type::lx##S); rule->Add(item); }
#define OPER(O)      { GSymbol item(GSymbol::gsTerminal,T_Lexeme::T_Group::grOper,A_Symbol::T_Type::lx##O); rule->Add(item); }
#define WORD(W)      { GSymbol item(GSymbol::gsTerminal,T_Lexeme::T_Group::grReserv,T_Lexeme::W_Type::rw##W); rule->Add(item); }
#define GROUP(G)     { GSymbol item(GSymbol::gsTerminal,T_Lexeme::T_Group::grSyntax,T_Lexeme::T_Syntax::sx##G); rule->Add(item); }
#define PRIOR(P)     { GSymbol item(GSymbol::gsTerminal,T_Lexeme::T_Group::grPriority,A_Symbol::T_Priority::pr##P); rule->Add(item); }
#define ERRORRULE(E) rule->error = T_Error::er##E;

#define MAKE(FUNC)      MODE(MAKE_(FUNC),GSymbol::Tree | GSymbol::Code)
#define MAKE_TREE(FUNC) MODE(MAKE_(FUNC),GSymbol::Tree)
#define MAKE_CODE(FUNC) MODE(MAKE_(FUNC),GSymbol::Code)
#define MAKE_YACC(FUNC) MODE(MAKE_(FUNC),GSymbol::Yacc)
#define MAKE_ALL(FUNC)  MODE(MAKE_(FUNC),GSymbol::Yacc | GSymbol::Code | GSymbol::Tree)

#define WARNING         rule->head.mode |= GSymbol::Warning;

#undef MAKE_
#if !defined(NO_GEN_MAKE)
   #define MAKE_(FUNC)  { GSymbol item(GSymbol::gsMaker,GMakerTable::maker_table.Find(#FUNC)); rule->Add(item); }
   #define PARAM(I,P)   I rule->OrParam(P);
   #define MODE(I,M)    I rule->OrMode(M);
   #define L            syn_tree
   #define MAKE_NODE(M,S,P) { GSymbol item(GSymbol::gsMaker,SNode::st##M,P,S,GSymbol::SNode); rule->Add(item); }
   #define MAKE_TURN(M,S,P) { GSymbol item(GSymbol::gsMaker,SNode::tt##M,P,SNode::st##S,GSymbol::Turn); rule->Add(item); }
#else
   #define PARAM(I,P)      
   #define MODE(I,M) 
   #define MAKE_(FUNC)      
   #define MAKE_NODE(M,S,P) 
   #define MAKE_TURN(M,S,P) 
#endif

#endif

#undef PRIOR
#define PRIOR(P)     { GSymbol item(GSymbol::gsTerminal,T_Lexeme::T_Group::grPriority,A_Symbol::T_Priority::pr##P); rule->Add(item); }

#undef MUST
#if   defined(DEFINE_GRAMMAR_LL) || defined(DEFINE_GRAMMAR_NL) || defined(DEFINE_GRAMMAR_ETF_LL)
#define MUST(I)      I rule->OrMode(GSymbol::T_Mode::Must);
#elif   defined(DEFINE_GRAMMAR_LR) || defined(DEFINE_GRAMMAR_ETF_LR) || defined(DEFINE_GRAMMAR_EEE_LR) || defined(DEFINE_GRAMMAR_NR)
#define MUST(I)      I
#endif

#undef FORMULA_PRIOR
#if   defined(DEFINE_GRAMMAR_LL) || defined(DEFINE_GRAMMAR_NL)

#define FORMULA_PRIOR(T,P)  \
   FORMULA(T) \
      PRODUCE RULE(P) MAKE_NODE(Copy,L(1,2),0) RULE(T##_) END \
   END \
   FORMULA(T##_) \
      PRODUCE PRIOR(T) RULE(P) MAKE(Binary) MAKE_NODE(Binary,L(3,1,2),0) MASTER END \
      EMPTY \
   END 

#elif   defined(DEFINE_GRAMMAR_LR) || defined(DEFINE_GRAMMAR_NR)

#define FORMULA_PRIOR(T,P)  \
   FORMULA(T) \
      PRODUCE MASTER PRIOR(T) RULE(P) MAKE(Binary) MAKE_TURN(Make,Binary,-2) MAKE_NODE(Binary,L(2,1,3),0) END \
      PRODUCE RULE(P) END \
   END

#define FORMULA_ASSOCIAT(T)  \
   PRODUCE MASTER PRIOR(T) MASTER MAKE(Binary) MAKE_TURN(Make,Binary,-2) MAKE_NODE(Binary,L(2,1,3),0) END

#endif

#undef MASTER
#undef EMPTY
#define MASTER       { GSymbol item(formula->head); item.mode |= GSymbol::Master; rule->Add(item); } 
#define RULE(T)      { GSymbol item(GSymbol::gsFormula,names.Add(#T)); rule->Add(item); }
#define EMPTY        PRODUCE END

