#ifndef TRN_GRAMMAR_CFG_H
#define TRN_GRAMMAR_CFG_H

#define DEFINE_RULE_FULL
//#define DEFINE_RULE_EXPR
//#define DEFINE_RULE_DEF
//#define DEFINE_RULE_STMT

//#define DEFINE_GRAMMAR_EXPR_LR
//#define DEFINE_GRAMMAR_ETF_LL
//#define DEFINE_GRAMMAR_ETF_LR
//#define DEFINE_GRAMMAR_EEE_LR
//#define DEFINE_GRAMMAR_EbEpE
//#define DEFINE_GRAMMAR_SCC
//#define DEFINE_GRAMMAR_SLR

//#define DEFINE_GRAMMAR_NL
#define DEFINE_GRAMMAR_LL
//#define DEFINE_GRAMMAR_NR
//#define DEFINE_GRAMMAR_LR

#define PARSE_GRAMMAR

#if   defined(PARSE_GRAMMAR)
   #if   defined(DEFINE_GRAMMAR_LL)
//      #define PARSE_LL
      #define PARSE_LR1
   #elif defined(DEFINE_GRAMMAR_NL)
      #define PARSE_NLL
//      #define PARSE_YACC
   #elif defined(DEFINE_GRAMMAR_LR)
      #define PARSE_LR0
//      #define PARSE_LR1
//      #define PARSE_YACC
//      #define PARSE_LALR
   #elif defined(DEFINE_GRAMMAR_NR)
//      #define PARSE_LR0
      #define PARSE_NLR
//      #define PARSE_YACC
//      #define PARSE_LALR
   #elif defined(DEFINE_GRAMMAR_SLR) || defined(DEFINE_GRAMMAR_SCC)
//      #define PARSE_LR0
//      #define PARSE_LR1
      #define PARSE_LALR
//      #define PARSE_YACC
   #elif defined(DEFINE_GRAMMAR_ETF_LL)
//      #define PARSE_LL
//      #define PARSE_LR0
//      #define PARSE_LR1
      #define PARSE_LALR
   #elif defined(DEFINE_GRAMMAR_ETF_LR) || defined(DEFINE_GRAMMAR_EXPR_LR) || defined(DEFINE_GRAMMAR_EEE_LR) || defined(DEFINE_GRAMMAR_EbEpE)
//      #define PARSE_LR0
//      #define PARSE_LR1
      #define PARSE_LALR
   #endif
#endif

//#define NO_GEN_MAKE

#endif

