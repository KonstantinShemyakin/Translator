   enum T_Priority {
               prNone, prAssign, prQuestion, prOrOr, prAndAnd, prOr, prXOr, prAnd, prEqu, prCompare, prShift, 
               prTerm, prFactor, prUnary, prIncDec
               };

   enum T_Lexeme {
               Priority_None, Priority_Assign, Priority_Question, Priority_OrOr, Priority_AndAnd, Priority_Or, Priority_XOr, Priority_And, 
               Priority_Equ, Priority_Compare, Priority_Shift, 
               Priority_Term, Priority_Factor, Priority_Unary, Priority_IncDec
               };

   enum T_Formula {
               F_Expresion, F_Assign, F_Question, F_OrOr, F_AndAnd, F_Or, F_XOr, F_And, 
               F_Equ, F_Compare, F_Shift, 
               F_Term, F_Factor, F_Unary, F_IncDec, F_Primary
               };
