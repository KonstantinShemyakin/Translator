   FORMULA(S_) 
      PRODUCE RULE(Program) END
   END

   FORMULA(Program)
#if   defined(DEFINE_RULE_FULL)
      PRODUCE RULE(Defines) END
#elif defined(DEFINE_RULE_DEF)
      PRODUCE RULE(Define) END
#elif defined(DEFINE_RULE_EXPR)
      PRODUCE EXPRESSION(Expression) END
#elif defined(DEFINE_RULE_STMT)
      PRODUCE RULE(StmExpr) END
#else
#endif
   END

   FORMULA(DefBegParVar) 
      PRODUCE LEX(Ident) MAKE(DefParVar) MAKE_TURN(Make,DefVar,-1) END
   END
   FORMULA(DefParVar) 
      PRODUCE RULE(DefBegParVar) OPER(Assign) MAKE_CODE(BegParVarAssign) MAKE_TURN(Command,Lexeme,-1) RULE(Assign) MAKE(ParVarAssign) MAKE_TURN(Down,0,0) END
      PRODUCE RULE(DefBegParVar) END
   END

   FORMULA(DefBegParArr) 
      PRODUCE GROUP(IdentArr) MAKE(DefParArr) MAKE_TURN(Make,List,0) RULE(DefBegRanges) MAKE_TURN(Make,DefArr,-2) END
   END

   FORMULA(DefParArr) 
      PRODUCE RULE(DefBegParArr) OPER(Assign) MAKE_CODE(BegParVarAssign) MAKE_TURN(Command,Lexeme,-1) RULE(Assign) MAKE(ParVarAssign) MAKE_TURN(Down,0,0) END 
      PRODUCE RULE(DefBegParArr) END // !!!
   END

   FORMULA(DefParItem) 
      PRODUCE GROUP(DefArr) MAKE_TURN(Push,Type,0) RULE(DefParArr) END
      PRODUCE GROUP(DefVar) MAKE_TURN(Push,Type,0) RULE(DefParVar) END
   END

   FORMULA(DefParams)
      PRODUCE MASTER SYM(Comma) RULE(DefParItem) MAKE_TREE(AddToList) MAKE_TURN(Down,0,0) END
      PRODUCE RULE(DefParItem) MAKE_TREE(AddToList) MAKE_TURN(Down,0,0) END
   END

   FORMULA(BodyFunc)
      PRODUCE SYM(Semicolon) PARAM(MAKE(BodyFunc),0x00) MAKE_TURN(Make,Null,0) END
      PRODUCE GROUP(EmptyCramp) PARAM(MAKE(BodyFunc),0x01) MAKE_TURN(Make, Statements,0) END
      PRODUCE SYM(LeftCramp) MAKE_CODE(EndParams) MAKE(BegStmExprLR) MAKE_TURN(Make,Statements,0) RULE(StmExpr) SYM(RightCramp) PARAM(MAKE(BodyFunc),0x02) END
   END

   FORMULA(DefFunc_)
      PRODUCE GROUP(EmptyBracket) PARAM(MAKE_TREE(EndParams), 0x02) MAKE_TURN(Make, Null, 0) MAKE_TURN(Down, 0, 0) END
      PRODUCE SYM(LeftBracket) PARAM(MAKE_TREE(Define), 0x02) MAKE_TURN(Make, Define, 0) RULE(DefParams) SYM(RightBracket) MAKE_TREE(EndParams) MAKE_TURN(Down, 0, 1) END
   END

   FORMULA(DefFunc) 
      PRODUCE GROUP(DefFunc) MAKE_TURN(Push,Type,0) GROUP(IdentFunc) MAKE(FuncIdent) MAKE_TURN(Make,DefFunc,-1) RULE(DefFunc_) RULE(BodyFunc) MAKE_TURN(Down,0,0) END
   END

   FORMULA(AInitItem)
      PRODUCE RULE(Initializer) END
      PRODUCE RULE(Assign) MAKE_CODE(AInitItem) END
   END

   FORMULA(AInitial)
      PRODUCE MASTER SYM(Comma) RULE(AInitItem) MAKE_TREE(AddToList) MAKE_TURN(Down,0,0) END
      PRODUCE RULE(AInitItem) MAKE_TREE(AddToList) MAKE_TURN(Down,0,0) END
   END

   FORMULA(Initializer)
      PRODUCE GROUP(EmptyCramp) MAKE_CODE(BegInitial) MAKE_TREE(NodeListLR) MAKE_TURN(Make,List,0) END
      PRODUCE SYM(LeftCramp) PARAM(MAKE_CODE(BegInitial),0x01) MAKE_TREE(NodeListLR) MAKE_TURN(Make,List,0) RULE(AInitial) SYM(RightCramp) MAKE_CODE(EndInitial) END
   END

   FORMULA(DefRanges_)
      PRODUCE SYM(LeftScrape) RULE(Assign) SYM(RightScrape) END
   END

   FORMULA(DefRanges)
      PRODUCE MASTER RULE(DefRanges_) MAKE(DRange) MAKE_TURN(Down,0,0) END
      PRODUCE RULE(DefRanges_) MAKE(DRange) MAKE_TURN(Down,0,0) END 
   END

   FORMULA(DefBegRanges) 
      PRODUCE GROUP(EmptyScrape) MAKE(DefArrD1AEmpty) MAKE_TURN(Put,Null,0) MAKE_TURN(Down,0,0) RULE(DefRanges) END 
      PRODUCE GROUP(EmptyScrape) MAKE(DefArrD1AEmpty) MAKE_TURN(Put,Null,0) MAKE_TURN(Down,0,0) END 
      PRODUCE RULE(DefRanges) END
   END

   FORMULA(DefBegArr) 
      PRODUCE GROUP(IdentArr) MAKE(DefArray) MAKE_TURN(Push,DefArr,0) MAKE_TURN(Make,Ranges,0) RULE(DefBegRanges) MAKE_CODE(EndRanges) MAKE_TURN(Down,0,0) END
   END

   FORMULA(DefArr) 
      PRODUCE RULE(DefBegArr) OPER(Assign) MAKE_CODE(BegAInit) MAKE_TURN(Command,Lexeme,-1) RULE(Initializer) MAKE(EndAInit) MAKE_TURN(Down,0,0) END 
      PRODUCE RULE(DefBegArr) END
   END

   FORMULA(DefVarIdent) 
      PRODUCE LEX(Ident) MAKE(DefIdent) MAKE_TURN(Push, DefVar, 0) END
   END
   FORMULA(DefVarAssign) 
      PRODUCE OPER(Assign) MAKE_CODE(BegDefVarAssign) MAKE_TURN(Command,Lexeme,-1) RULE(Assign) MAKE(DefVarAssign) MAKE_TURN(Down, 0, 0) END
   END

   FORMULA(DefVar) 
      PRODUCE RULE(DefVarIdent) RULE(DefVarAssign) END
      PRODUCE RULE(DefVarIdent) END
   END

   FORMULA(DefIAV) 
      PRODUCE RULE(DefArr) END
      PRODUCE RULE(DefVar) END
   END
   FORMULA(RefDefIAV) 
      PRODUCE PRIOR(And) RULE(DefIAV) MAKE_TREE(RefDef) MAKE_TURN(Command,Lexeme,-1) END
   END
   FORMULA(DefItem) 
      PRODUCE RULE(RefDefIAV) END
      PRODUCE RULE(DefIAV)    END
   END

   FORMULA(DefType) 
      PRODUCE GROUP(DefArr) END
      PRODUCE GROUP(DefVar) END
   END

   FORMULA(DefineComma)
      PRODUCE MASTER SYM(Comma) RULE(DefItem) MAKE_TREE(AddToList) MAKE_TURN(Down, 0, 0) END
      PRODUCE RULE(DefItem) MAKE_TREE(AddToList) MAKE_TURN(Down, 0, 0) END
   END

   FORMULA(Define)
      PRODUCE RULE(DefType) MAKE(Define) MAKE_TURN(Push,Type,0) MAKE_TURN(Make,Define,1) RULE(DefineComma) MAKE_CODE(EndDefine) END
   END

   FORMULA(Expressions)
      PRODUCE MASTER SYM(Comma) RULE(Assign) MAKE_TREE(AddToList) MAKE_TURN(Down,0,0) MAKE_CODE(AddToExpr) END
      PRODUCE RULE(Assign) MAKE(ExpressionsLR) MAKE_TURN(Make,Expressions,1) END
   END

   bool PRIOR_ASSOCIATION = ((table.option & TGrammar::POption::opAssociation  ) != 0);
   bool PRIOR_ASSIGN      = ((table.option & TGrammar::POption::opNoPriorAssign) == 0);

   FORMULA(PriorAssign)
if (!PRIOR_ASSIGN) {
      PRODUCE OPER(AddAssign)    END
      PRODUCE OPER(SubAssign)    END
      PRODUCE OPER(MultiAssign)  END
      PRODUCE OPER(DivAssign)    END
      PRODUCE OPER(ModAssign)    END
      PRODUCE OPER(Assign)       END
      PRODUCE OPER(OrAssign)     END
      PRODUCE OPER(XOrAssign)    END
      PRODUCE OPER(AndAssign)    END
      PRODUCE OPER(LShiftAssign) END
      PRODUCE OPER(RShiftAssign) END
} else {
      PRODUCE PRIOR(Assign) END
}
   END

   FORMULA(Assign)
      PRODUCE 
if (PRIOR_ASSOCIATION && PRIOR_ASSIGN) {
         RULE(Question) PRIOR(Assign) MASTER MAKE(Binary) MAKE_TURN(Make, Binary, -2)
} else {
         RULE(Question) RULE(PriorAssign) MASTER MAKE(Binary) MAKE_TURN(Make, Binary, -2)
}
      END
      PRODUCE RULE(Question) END
   END

   FORMULA(Question)
      PRODUCE 
if (PRIOR_ASSOCIATION) {
         RULE(Binary) 
} else {
         RULE(OrOr) 
}
         PRIOR(Question) MAKE_CODE(BegQuestion) EXPRESSION(Value) SYM(Colon) MAKE_CODE(MidQuestion) MASTER MAKE(Question) MAKE_TURN(Make,Trio,-3)
      END
      PRODUCE
if (PRIOR_ASSOCIATION) {
         RULE(Binary) 
} else {
         RULE(OrOr) 
}
      END
   END

if (PRIOR_ASSOCIATION) {
   FORMULA(Binary)
      FORMULA_ASSOCIAT(OrOr)
      FORMULA_ASSOCIAT(AndAnd)
      FORMULA_ASSOCIAT(Or)
      FORMULA_ASSOCIAT(XOr)
      FORMULA_ASSOCIAT(And)
      FORMULA_ASSOCIAT(Equ)
      FORMULA_ASSOCIAT(Compare)
      FORMULA_ASSOCIAT(Shift)
      FORMULA_ASSOCIAT(Term)
      FORMULA_ASSOCIAT(Factor)
      PRODUCE RULE(Unary) END
   END
} else {
   FORMULA_PRIOR(OrOr,AndAnd)
   FORMULA_PRIOR(AndAnd,Or)
   FORMULA_PRIOR(Or,XOr)
   FORMULA_PRIOR(XOr,And)
   FORMULA_PRIOR(And,Equ)
   FORMULA_PRIOR(Equ,Compare)
   FORMULA_PRIOR(Compare,Shift)
   FORMULA_PRIOR(Shift,Term)
   FORMULA_PRIOR(Term,Factor)
   FORMULA_PRIOR(Factor,Unary)
}

   FORMULA(UnaryIncDec)
      PRODUCE RULE(PrimaryExpr) PRIOR(IncDec) MAKE(IncDec) MAKE_TURN(Make, IncDec, -1) END
      PRODUCE RULE(PrimaryExpr) END
   END

   FORMULA(Unary)
      PRODUCE PRIOR(Unary)      RULE(Unary) MAKE(Unary) MAKE_TURN(Make,Unary,-1) END
      PRODUCE PRIOR(Term)       RULE(Unary) MAKE(Unary) MAKE_TURN(Make,Unary,-1) END
      PRODUCE PRIOR(IncDec)     RULE(Unary) MAKE(Unary) MAKE_TURN(Make,Unary,-1) END
      PRODUCE GROUP(CastUnary)  RULE(Unary) MAKE(Cast)  MAKE_TURN(Make,Cast,-1)  END
      PRODUCE RULE(UnaryIncDec) END
   END

   FORMULA(Primary)
      PRODUCE SYM(LeftBracket) EXPRESSION(None) SYM(RightBracket) MAKE_TREE(Primary) MAKE_TURN(Make, Primary, 1) END
   END

   FORMULA(PrimaryExpr) 
      PRODUCE LEX(Integer) MAKE(Number) MAKE_TURN(Push,Number,0) END
      PRODUCE LEX(Number)  MAKE(Number) MAKE_TURN(Push,Number,0) END
      PRODUCE GROUP(IdentArr)  MAKE_TURN(Push,Index,0) RULE(Ranges) MAKE(EndIndex) MAKE_TURN(Down,0,0) END
      PRODUCE GROUP(IdentFunc) MAKE_TURN(Push,Call,0)  RULE(CallParams) MAKE_TURN(Down,0,0) END
      PRODUCE GROUP(Cast) RULE(Primary) MAKE(Cast) MAKE_TURN(Make,Cast,-1) END
      PRODUCE LEX(Ident)  MAKE(Ident)   MAKE_TURN(Push,Var,0)  END
      PRODUCE RULE(Primary) END
   END

   FORMULA(Range)
      PRODUCE SYM(LeftScrape) EXPRESSION(Value) SYM(RightScrape) END
   END

   FORMULA(Ranges)
      PRODUCE MASTER RULE(Range) MAKE(IndexLR) MAKE_TURN(Down,0,0) END
      PRODUCE RULE(Range) MAKE(BegIndexLR) MAKE_TURN(Make,Ranges,1) END 
   END

   FORMULA(CallParams) 
      PRODUCE GROUP(EmptyBracket) MAKE(Params) MAKE_TURN(Make,Null,0) END
      PRODUCE SYM(LeftBracket) EXPRESSION(ValueList) SYM(RightBracket) PARAM(MAKE(Params),0x01) END
   END

   FORMULA(CompaundStmnt)
      PRODUCE GROUP(EmptyCramp) MAKE(Compaund) MAKE_CODE(EndBlock) MAKE_TURN(Make,Statements,0) END
      PRODUCE SYM(LeftCramp) MAKE(Compaund) MAKE_TURN(Make,Statements,0) RULE(StmExpr) SYM(RightCramp) END
   END

   FORMULA(Condition_V)
      PRODUCE PRIOR(And) RULE(DefVarAssign) MAKE_TREE(RefDef) MAKE_TURN(Command,Lexeme,-1) END
      PRODUCE RULE(DefVarAssign) END
   END

   FORMULA(Condition)
      PRODUCE GROUP(DefVar) MAKE(Define) RULE(Condition_V) MAKE(PushDef) END
      PRODUCE EXPRESSION(Condition) END
   END

   FORMULA(For_Prefix) // prefix
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) MAKE_TURN(Make, Null, 0) END
      PRODUCE RULE(DefineSemi) END
      PRODUCE RULE(ExprSemi) END
   END

   FORMULA(For_Condition) // condition
      PRODUCE SYM(Semicolon)  MAKE(NodeNull) MAKE_TURN(Make, Null, 0) END
      PRODUCE RULE(Condition) SYM(Semicolon) END
   END

   FORMULA(For_Postfix) // postfix
      PRODUCE SYM(RightBracket) MAKE_TREE(NodeNull) MAKE_TURN(Make, Null, 0) END
      PRODUCE EXPRESSION(Expression) SYM(RightBracket) END
   END

   FORMULA(ForStmnt) 
      PRODUCE
      WORD(For) SYM(LeftBracket) MAKE(BegFor)
      RULE(For_Prefix) MAKE_CODE(PrefFor)
      RULE(For_Condition) MAKE_CODE(ConditionFor)
      RULE(For_Postfix) MAKE_CODE(PostFor)
      RULE(DefExpr) MAKE(For) MAKE_TURN(Make,For,4) // body
      END
   END 

   FORMULA(ReturnValue)
      PRODUCE SYM(Semicolon)    MAKE(Return)   MAKE_TURN(Make, Return, 0) END
      PRODUCE EXPRESSION(Value) SYM(Semicolon) PARAM(MAKE(Return), 0x01) MAKE_TURN(Make, Return, 1) END
   END

   FORMULA(ReturnStmnt  )
      PRODUCE WORD(Return) RULE(ReturnValue) END
   END 

   FORMULA(BegIfStmnt) 
      PRODUCE WORD(If) SYM(LeftBracket) MAKE_CODE(BegIf) RULE(Condition) SYM(RightBracket) MAKE_CODE(Then) RULE(DefExpr) MAKE_TURN(Make, If, 2) END
   END

   FORMULA(Statement)
      PRODUCE RULE(BegIfStmnt) WORD(Else) MAKE_CODE(Else) RULE(DefExpr) PARAM(MAKE(If),0x01) MAKE_TURN(Down,0,0) END
      PRODUCE WARNING RULE(BegIfStmnt) MAKE(If) END
      PRODUCE GROUP(Label) SYM(Colon) MAKE_CODE(Label) MAKE_TURN(Push,Label,0) RULE(DefExpr) MAKE_TREE(Label) MAKE_TURN(Make,List,2) END
      PRODUCE WORD(Do)    MAKE(BegDo) RULE(DefExpr)    WORD(While) SYM(LeftBracket) RULE(Condition) SYM(RightBracket) SYM(Semicolon) MAKE(Do) MAKE_TURN(Make, Do, -2) END
      PRODUCE WORD(While) MAKE(BegWhile) SYM(LeftBracket) RULE(Condition)   SYM(RightBracket) RULE(DefExpr) MAKE(While) MAKE_TURN(Make, While, -2) END
      PRODUCE RULE(ForStmnt     ) END 
      PRODUCE WORD(Switch)   SYM(LeftBracket) SYM(RightBracket) END
      PRODUCE WORD(GoTo)     LEX(Ident)       SYM(Semicolon)  MAKE(GoTo) MAKE_TURN(Push, GoTo, 0) END
      PRODUCE WORD(Break)    SYM(Semicolon)   MAKE(Break)     MAKE_TURN(Make, Break, 0) END
      PRODUCE WORD(Continue) SYM(Semicolon)   MAKE(Continue)  MAKE_TURN(Make, Continue, 0) END
      PRODUCE RULE(ReturnStmnt  ) END
      PRODUCE RULE(CompaundStmnt) END
   END

   FORMULA(DefineSemi)
      PRODUCE RULE(Define) SYM(Semicolon) END
   END

   FORMULA(ExprSemi)
      PRODUCE EXPRESSION(Expression) SYM(Semicolon) END
   END

   FORMULA(DefExpr) 
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) MAKE_TURN(Make,Null,0) END 
      PRODUCE RULE(DefineSemi) END
      PRODUCE RULE(Statement)  END
      PRODUCE RULE(ExprSemi)   END
   END

   FORMULA(StmExprList)
      PRODUCE MASTER RULE(DefExpr) MAKE_TREE(AddToList) MAKE_TURN(Down, 0, 0) END
      PRODUCE RULE(DefExpr) MAKE_TREE(AddToList) MAKE_TURN(Down, 0, 0) END
   END

   FORMULA(StmExpr)
      PRODUCE RULE(StmExprList) MAKE_CODE(EndBlock) END
   END

   FORMULA(DefFAV) 
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) MAKE_TURN(Make,Null,0) END 
      PRODUCE RULE(DefFunc) END
      PRODUCE RULE(DefineSemi) END
   END

   FORMULA(DefinesList)
      PRODUCE MASTER RULE(DefFAV) MAKE_TREE(AddToList) MAKE_TURN(Down,0,0) END
      PRODUCE RULE(DefFAV) PARAM(MAKE_TREE(BegStmExprLR),0x01) MAKE_TURN(Down,0,0) END
   END

   FORMULA(Defines)
      PRODUCE MAKE_CODE(BegStmExprLR) MAKE_TURN(Make, Statements, 0) RULE(DefinesList) MAKE_CODE(EndBlock) END
   END
