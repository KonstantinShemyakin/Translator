#include "stdafx.h"

#include "GrammarStock.h"
#include "Grammar.h"

#undef  DEFINE_RULE_FULL
#define DEFINE_RULE_FULL
//#define DEFINE_RULE_EXPR

#include "Maker.h"

#define FORMULA_MACRO_DEFINE

#pragma optimize("", on)

#undef  DEFINE_GRAMMAR_LR
#define DEFINE_GRAMMAR_LL
#include "RuleMacro.h"

static bool build_formulas_ll(TGrammar &table, TRuleNames &names, int mode)
{
   GFormulaTable &formulas = table.formulas;

   T_Stock def_rule_mode = (T_Stock)(mode & T_Stock::msGrammar), make_mode = (T_Stock)(mode & T_Stock::msMASK), phase_mode = (T_Stock)(mode & T_Stock::msPhase);

   if ((def_rule_mode == T_Stock::msETF_LL) && (make_mode == T_Stock::msNone)) {

     FORMULA(S_) 
        PRODUCE RULE(E) END
     END
     
     FORMULA(E)
        PRODUCE RULE(T) RULE(E_) END 
     END 
     
     FORMULA(E_)
        PRODUCE OPER(Add) RULE(T) MASTER END 
        EMPTY 
     END 
     
     FORMULA(T) 
        PRODUCE RULE(F) RULE(T_) END 
     END 
     
     FORMULA(T_)
        PRODUCE OPER(Multi) RULE(F) MASTER END 
        EMPTY 
     END 
     
     FORMULA(F)
        PRODUCE SYM(LeftBracket) RULE(E) SYM(RightBracket) END 
        PRODUCE LEX(Ident) END
     END

   } else if ((def_rule_mode == T_Stock::msETF_LL) && ((make_mode == T_Stock::msTree) || (make_mode == T_Stock::msCode))) {

      FORMULA(S_)
         PRODUCE RULE(_E) END
      END

      FORMULA(_E)
         PRODUCE MAKE(BegStmExprLL) RULE(E) MAKE_TREE(AddToList) MAKE_CODE(EndBlock) END
      END

      FORMULA(E_)
         PRODUCE PRIOR(Term) RULE(T) MAKE(Binary) MASTER END
         EMPTY
      END

      FORMULA(E)
         PRODUCE RULE(T) RULE(E_) END
      END

      FORMULA(T_)
         PRODUCE PRIOR(Factor) RULE(F) MAKE(Binary) MASTER END
         EMPTY
      END

      FORMULA(T)
         PRODUCE RULE(F) RULE(T_) END
      END

      FORMULA(F)
         PRODUCE SYM(LeftBracket) RULE(E) SYM(RightBracket) END
         PRODUCE LEX(Integer) MAKE(Number) END
//         PRODUCE LEX(Number) MAKE(Number) END 
      END

   } else if ((def_rule_mode == T_Stock::msLL) && (phase_mode == T_Stock::msTwoPhase)) {

#undef FORMULA_PRIOR
#define FORMULA_PRIOR(T,P)  \
   FORMULA(T) \
      PRODUCE RULE(P) MAKE_NODE(Copy,L(1,2),0) RULE(T##_) END \
   END \
   FORMULA(T##_) \
      PRODUCE PRIOR(T) MAKE_CALL(Binary,Begin,0) RULE(P) MAKE_CALL(Binary,End,0) MAKE_NODE(Binary,L(3,1,2),0) MASTER END \
      EMPTY \
   END 

      #undef EXPRESSION
      #undef EXPRESSION_BODY
      #define EXPRESSION(PART) RULE(Expression##PART)
      #include "def_block_LL.cpp"
      #define RULE_EXPRESSION(PART) RULE(Assign) MAKE_CALL(Expressions,Begin,0) MAKE_NODE(Expressions,L(2,3),1) RULE(ExprList) MAKE_CALL(Expressions,End,T_Part::ps##PART)
      #define EXPRESSION_BODY(PART) FORMULA(Expression##PART) PRODUCE RULE_EXPRESSION(PART) PARAM(MAKE_YACC(ExpressionSLL),T_Part::ps##PART) END END
      #include "def_rule_expression.cpp"
   } else if (def_rule_mode == T_Stock::msLL) {

#undef FORMULA_PRIOR
#define FORMULA_PRIOR(T,P)  \
   FORMULA(T) \
      PRODUCE RULE(P) MAKE_NODE(Copy,L(1,2),0) RULE(T##_) END \
   END \
   FORMULA(T##_) \
      PRODUCE PRIOR(T) RULE(P) MAKE(Binary) MAKE_NODE(Binary,L(3,1,2),0) MASTER END \
      EMPTY \
   END 

      #undef EXPRESSION
      #undef EXPRESSION_BODY
      #define EXPRESSION(PART) RULE(Expression##PART)
      #include "def_formula_LL.cpp"
      #define EXPRESSION_BODY(PART) FORMULA(Expression##PART) PRODUCE PARAM(MAKE_CODE(Part),T_Part::ps##PART) RULE(Expressions) PARAM(MAKE_TREE(ExpressionSLL),T_Part::ps##PART) PARAM(MAKE_YACC(ExpressionSLL),T_Part::ps##PART) END END
      #include "def_rule_expression.cpp"
   } else if (def_rule_mode == T_Stock::msNL) {
      #undef EXPRESSION
      #undef EXPRESSION_BODY
      #define EXPRESSION(PART) RULE(Expression##PART)
      #include "def_formula_NL.cpp"
      #define EXPRESSION_BODY(PART) FORMULA(Expression##PART) PRODUCE RULE(Expressions) PARAM(MAKE_TREE(ExpressionSLL),T_Part::ps##PART) END END
      #include "def_rule_expression.cpp"
   }

   return formulas.count() != 0;
}

#undef  DEFINE_GRAMMAR_LL
#define DEFINE_GRAMMAR_LR
#include "RuleMacro.h"

static bool build_formulas_lr(TGrammar &table, TRuleNames &names, int mode)
{
   GFormulaTable &formulas = table.formulas;

   T_Stock def_rule_mode = (T_Stock)(mode & T_Stock::msGrammar), make_mode = (T_Stock)(mode & T_Stock::msMASK), phase_mode = (T_Stock)(mode & T_Stock::msPhase);

   if (def_rule_mode == T_Stock::msEXPR_LR) {

     FORMULA(S_) 
        PRODUCE RULE(OrOr) END
     END
     
     FORMULA(OrOr   ) PRODUCE MASTER PRIOR(OrOr   ) RULE(AndAnd ) MAKE(Binary) END PRODUCE RULE(AndAnd ) END END
     FORMULA(AndAnd ) PRODUCE MASTER PRIOR(AndAnd ) RULE(Or     ) MAKE(Binary) END PRODUCE RULE(Or     ) END END
     FORMULA(Or     ) PRODUCE MASTER PRIOR(Or     ) RULE(XOr    ) MAKE(Binary) END PRODUCE RULE(XOr    ) END END
     FORMULA(XOr    ) PRODUCE MASTER PRIOR(XOr    ) RULE(And    ) MAKE(Binary) END PRODUCE RULE(And    ) END END
     FORMULA(And    ) PRODUCE MASTER PRIOR(And    ) RULE(Equ    ) MAKE(Binary) END PRODUCE RULE(Equ    ) END END
     FORMULA(Equ    ) PRODUCE MASTER PRIOR(Equ    ) RULE(Compare) MAKE(Binary) END PRODUCE RULE(Compare) END END
     FORMULA(Compare) PRODUCE MASTER PRIOR(Compare) RULE(Shift  ) MAKE(Binary) END PRODUCE RULE(Shift  ) END END
     FORMULA(Shift  ) PRODUCE MASTER PRIOR(Shift  ) RULE(Term   ) MAKE(Binary) END PRODUCE RULE(Term   ) END END
     FORMULA(Term   ) PRODUCE MASTER PRIOR(Term   ) RULE(Factor ) MAKE(Binary) END PRODUCE RULE(Factor ) END END
     FORMULA(Factor ) PRODUCE MASTER PRIOR(Factor ) RULE(Unary  ) MAKE(Binary) END PRODUCE RULE(Unary  ) END END
     
     FORMULA(Unary)
        PRODUCE SYM(LeftBracket) RULE(OrOr) SYM(RightBracket) END 
        PRODUCE LEX(Ident)   MAKE(Ident) END
        PRODUCE LEX(Integer) MAKE(Number) END
     END

   } else if ((def_rule_mode == T_Stock::msETF_LR) && (make_mode == T_Stock::msNone)) {

      FORMULA(S_) 
         PRODUCE RULE(E) END
      END
      
      FORMULA(E)
         PRODUCE MASTER PRIOR(Term) RULE(T) END
         PRODUCE RULE(T) END 
      END
      
      FORMULA(T)
         PRODUCE MASTER PRIOR(Factor) RULE(F) END
         PRODUCE RULE(F) END 
      END
      
      FORMULA(F)
         PRODUCE SYM(LeftBracket) RULE(E) SYM(RightBracket) END 
         PRODUCE LEX(Ident) END
      END

   } else if ((def_rule_mode == T_Stock::msETF_LR) && ((make_mode == T_Stock::msTree) || (make_mode == T_Stock::msCode))) {

      FORMULA(S_) 
         PRODUCE RULE(E) END
      END
      
      FORMULA(E)
         PRODUCE MASTER PRIOR(Term) RULE(T) MAKE(Binary) END
         PRODUCE RULE(T) END 
      END
      
      FORMULA(T)
         PRODUCE MASTER PRIOR(Factor) RULE(F) MAKE(Binary) END
         PRODUCE RULE(F) END 
      END
      
      FORMULA(F)
         PRODUCE SYM(LeftBracket) RULE(E) SYM(RightBracket) END 
         PRODUCE LEX(Integer) MAKE(Number) END
//         PRODUCE LEX(Number) MAKE(Number) END 
      END

   } else if (def_rule_mode == T_Stock::msEEE) {

      FORMULA(S_) 
         PRODUCE RULE(E) END
      END
      
      FORMULA(E)
         PRODUCE MASTER PRIOR(Term) MASTER MAKE(Binary) END
         PRODUCE MASTER PRIOR(Factor) MASTER MAKE(Binary) END
         PRODUCE SYM(LeftBracket) MASTER SYM(RightBracket) END 
         PRODUCE LEX(Integer) MAKE(Number) END
//         PRODUCE LEX(Number) MAKE(Number) END
      END

   } else if (def_rule_mode == T_Stock::msEbEpE) {

      FORMULA(S_) 
         PRODUCE RULE(E) END
      END
      
      FORMULA(E)
         PRODUCE MASTER OPER(Sub) MASTER OPER(Add) MASTER END
         PRODUCE MASTER OPER(Sub) MASTER END
         PRODUCE MASTER OPER(Add) MASTER END
         PRODUCE SYM(LeftCramp) MASTER SYM(RightCramp) END 
         PRODUCE LEX(Ident) END
      END

   } else if (def_rule_mode == T_Stock::msLR) {

      #undef EXPRESSION
      #undef EXPRESSION_BODY
      #define EXPRESSION(PART) RULE(Expression##PART)
      #include "def_formula_LR.cpp"
      #define EXPRESSION_BODY(PART) FORMULA(Expression##PART) PRODUCE RULE(Expressions) PARAM(MAKE(ExpressionSLR),T_Part::ps##PART) MAKE_TURN(Command,Param,T_Part::ps##PART) END END
      #include "def_rule_expression.cpp"
   } else if ((def_rule_mode == T_Stock::msNR) && (phase_mode == T_Stock::msTwoPhase)) {

      #undef EXPRESSION
      #undef EXPRESSION_BODY
      #define EXPRESSION(PART) RULE(Expression##PART)
      #include "def_stack_NR.cpp"
      #define EXPRESSION_BODY(PART) FORMULA(Expression##PART) PRODUCE RULE(Expressions) PARAM(MAKE_ALL(ExpressionSLR),T_Part::ps##PART) END END
      #include "def_rule_expression.cpp"
   } else if (def_rule_mode == T_Stock::msNR) {

      #undef EXPRESSION
      #undef EXPRESSION_BODY
      #define EXPRESSION(PART) RULE(Expression##PART)
      #include "def_formula_NR.cpp"
      #define EXPRESSION_BODY(PART) FORMULA(Expression##PART) PRODUCE RULE(Expressions) PARAM(MAKE_ALL(ExpressionSLR),T_Part::ps##PART) END END
      #include "def_rule_expression.cpp"
   } else {
      return false;
   }

   return formulas.count() != 0;
}

static bool build_formulas(TRuleNames &names, TGrammar &table, int def_rule_mode, int make_mode) 
{
   GFormulaTable &formulas = table.formulas;
   bool ret = false;
   switch (def_rule_mode) {
      case TGrammar::sgLL:
         table.type = T_Grammar::gtLL; table.prefix = "LL_"; 
         ret = build_formulas_ll(table, names, T_Stock::msLL | (make_mode << 12));
         break;
      case TGrammar::sgNL:
         table.type = T_Grammar::gtLL; table.prefix = "NL_"; 
         ret = build_formulas_ll(table, names, T_Stock::msNL | (make_mode << 12));
         break;
      case TGrammar::sgLR:
         table.type = T_Grammar::gtLR; table.prefix = "LR_"; 
         ret = build_formulas_lr(table, names, T_Stock::msLR | (make_mode << 12));
         break;
      case TGrammar::sgNR:
         table.type = T_Grammar::gtLR; table.prefix = "NR_"; 
         ret = build_formulas_lr(table, names, T_Stock::msNR | (make_mode << 12));
         break;
      case TGrammar::sgETF_LL:
         table.type = T_Grammar::gtLL; table.prefix = "ETF_LL_"; 
         ret = build_formulas_ll(table, names, T_Stock::msETF_LL);
         break;
      case TGrammar::sgETF_LLMake:
         table.type = T_Grammar::gtLL; table.prefix = "ETF_LL_";
         ret = build_formulas_ll(table, names, T_Stock::msETF_LL | (make_mode << 12));
         break;
      case TGrammar::sgETF_LR:
         table.type = T_Grammar::gtLR; table.prefix = "ETF_LR_"; 
         ret = build_formulas_lr(table, names, T_Stock::msETF_LR);
         break;
      case TGrammar::sgETF_LRMake:
         table.type = T_Grammar::gtLR; table.prefix = "ETF_LR_"; 
         ret = build_formulas_lr(table, names, T_Stock::msETF_LR | (make_mode << 12));
         break;
      case TGrammar::sgEXPR_LR:
         table.type = T_Grammar::gtLR; table.prefix = "EXPR_LR_"; 
         ret = build_formulas_lr(table, names, T_Stock::msEXPR_LR | (make_mode << 12));
         break;
      default:
         ret = false;
   }
   if (!ret) return ret;
   formulas.root = formulas.front();
   table.root = formulas.front();
   return ret;
}

bool build_grammar(TGrammar &table, int option_mode, int mode) // 0x02 - !make
{
   A_Syntax::M_Mode make_mode = A_Syntax::M_Mode(OPTION_AREA(option_mode, Main));
   TGrammar::T_SourceGrammar def_rule_mode = TGrammar::T_SourceGrammar(OPTION_AREA(option_mode, Grammar)); // 000 - LL(F), 100 - NL(F)

   TRuleNames names;
   table.makers = &GMakerTable::maker_table;

   bool ret = build_formulas(names, table, def_rule_mode, make_mode | ((option_mode & T_Stock::msPhase) >> 12));
   if (ret && !(mode & 0x02)) ret = table.formulas.make(names, table.lexemes);
   if (ret && !(mode & 0x02)) { 
      table.Used();
   }

   return ret;
}

bool grammar_build(TGrammar &table, int stock_mode, int mode) // 0x02 - !make
{
   TRuleNames names;
   table.makers = &GMakerTable::maker_table;

   bool ret = false;
   if ((stock_mode & T_Stock::msMedia) == T_Stock::msMFormula) {
      if (stock_mode & T_Stock::msLLLR) {
         table.type = T_Grammar::gtLL;
         ret = build_formulas_ll(table, names, stock_mode);
      } else {
         table.type = T_Grammar::gtLR;
         ret = build_formulas_lr(table, names, stock_mode);
      }
      if (ret && !(mode & 0x02)) ret = table.formulas.make(names, table.lexemes);
   } else {
   }
   if (ret && !(mode & 0x02)) { 
      table.Used();
   }
   return ret;
}
