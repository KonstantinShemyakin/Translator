
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

   FORMULA(DefParInit)
      PRODUCE OPER(Assign) MAKE_CODE(BegParVarAssign) RULE(Assign) MAKE(ParVarAssign) END
      EMPTY 
   END

   FORMULA(DefParVar)
      PRODUCE GROUP(DefVar) MAKE_YACC(DefType) LEX(Ident) MAKE(DefParVar) RULE(DefParInit) MAKE_NODE(DefVar,L(2,1),0) END
   END

   FORMULA(DefParArr)
      PRODUCE GROUP(DefArr) MAKE_YACC(DefType) GROUP(IdentArr) MAKE(DefParArr) RULE(DefArrDA) MAKE_NODE(DefArr,L(3,0,1),0) RULE(DefParInit) MAKE_NODE(DefArr,L(1,2),2) END
   END

   FORMULA(DefPar) 
      PRODUCE RULE(DefParArr) END
      PRODUCE RULE(DefParVar) END
   END

   FORMULA(DefParItem)
      PRODUCE RULE(DefPar) MAKE_TREE(AddToList) END
   END

   FORMULA(DefParList)
      PRODUCE SYM(Comma) RULE(DefParItem) PARAM(MAKE_YACC(AddToList),0x06) MASTER END
      EMPTY 
   END

   FORMULA(DefParams)
      PRODUCE PARAM(MAKE_TREE(Define), 0x02) RULE(DefParItem) MAKE_NODE(Define,L(1,2),1) RULE(DefParList) MAKE_TREE(EndParams) END
   END

   FORMULA(BodyFunc)
      PRODUCE SYM(Semicolon) PARAM(MAKE(BodyFunc),0x00) END
      PRODUCE GROUP(EmptyCramp) PARAM(MAKE(BodyFunc),0x01) MAKE_NODE(Null,L(1),0) END
      PRODUCE SYM(LeftCramp) MAKE_CODE(EndParams) RULE(StmExpr) MAKE_NODE(Copy,L(1),0) SYM(RightCramp) PARAM(MAKE(BodyFunc),0x02) END
   END

   FORMULA(DefFunc_)
      PRODUCE GROUP(EmptyBracket) PARAM(MAKE_TREE(EndParams), 0x02) END
      PRODUCE SYM(LeftBracket) RULE(DefParams) MAKE_NODE(Copy, L(1), 0) SYM(RightBracket) END
   END

   FORMULA(DefFunc)
      PRODUCE GROUP(DefFunc) MAKE_NODE(DefFunc,L(0),0) GROUP(IdentFunc) MAKE_NODE(DefFunc,L(0),1) MAKE(FuncIdent) RULE(DefFunc_) MAKE_NODE(DefFunc,L(0),2) RULE(BodyFunc) MAKE_NODE(DefFunc,L(0),3) END
   END

   FORMULA(AInitialList)
      PRODUCE SYM(Comma) RULE(AInitItem) PARAM(MAKE_YACC(AddToList), 0x06)  MAKE_TREE(AddToList) MASTER END
      EMPTY
   END
  
   FORMULA(AInitial)
      PRODUCE RULE(AInitItem) MAKE_TREE(AddToList) PARAM(MAKE_YACC(AddToList),0x06) RULE(AInitialList) END
   END

   FORMULA(Initializer)
      PRODUCE GROUP(EmptyCramp) MAKE_CODE(BegInitial) MAKE_TREE(NodeListLL) MAKE_NODE(List,L(0),0) END
      PRODUCE SYM(LeftCramp) PARAM(MAKE_CODE(BegInitial),0x01) MAKE_TREE(NodeListLL) MAKE_NODE(List,L(0,2),0) RULE(AInitial) SYM(RightCramp) MAKE_CODE(EndInitial) END
   END

   FORMULA(AInitItem)
      PRODUCE RULE(Initializer) END
      PRODUCE RULE(Assign) MAKE_CODE(AInitItem) END
   END

   FORMULA(DefAInit)
      PRODUCE OPER(Assign) MAKE_CODE(BegAInit) RULE(Initializer) MAKE(EndAInit) END 
      EMPTY
   END

   FORMULA(DRanges)
      PRODUCE SYM(LeftScrape) RULE(Assign) PARAM(MAKE_YACC(AddToList),0x0A)  SYM(RightScrape) MAKE(DRange) MASTER END
      EMPTY
   END

   FORMULA(DefArrD1A) 
      PRODUCE GROUP(EmptyScrape) MAKE(DefArrD1AEmpty) MAKE_NODE(Ranges,L(0),5) END // Null
      PRODUCE SYM(LeftScrape) RULE(Assign) MAKE_NODE(Ranges,L(1),2) SYM(RightScrape) MAKE(DRange) END // create
   END

   FORMULA(DefArrDA)
      PRODUCE RULE(DefArrD1A) MAKE_NODE(Copy,L(1,2),0) RULE(DRanges) MAKE_CODE(EndRanges) END
   END

   FORMULA(DefArr)
      PRODUCE GROUP(IdentArr) MAKE(DefArray) RULE(DefArrDA) MAKE_NODE(DefArr,L(0,0,1),0) RULE(DefAInit) MAKE_NODE(DefArr,L(1,2),2) END
   END

   FORMULA(DefVarAssign)
      PRODUCE OPER(Assign) MAKE_CODE(BegDefVarAssign) RULE(Assign) MAKE(DefVarAssign) END
   END

   FORMULA(DefVarInit) 
      PRODUCE RULE(DefVarAssign) END
      EMPTY 
   END

   FORMULA(DefVar)
      PRODUCE LEX(Ident) MAKE(DefIdent) RULE(DefVarInit) MAKE_NODE(DefVar,L(0,1),0) END
   END

   FORMULA(DefIAV) 
      PRODUCE RULE(DefArr) END
      PRODUCE RULE(DefVar) END
   END

   FORMULA(DefItem) 
      PRODUCE PRIOR(And) RULE(DefIAV) MAKE_TREE(RefDef) MAKE_NODE(RefDef, L(1), 0) END
      PRODUCE RULE(DefIAV) END
   END

   FORMULA(DefType) 
      PRODUCE GROUP(DefArr) END
      PRODUCE GROUP(DefVar) END
   END

   FORMULA(DefineList)
      PRODUCE SYM(Comma) RULE(DefItem) PARAM(MAKE_YACC(AddToList),0x06) MAKE_TREE(AddToList) MASTER END
      EMPTY 
   END

   FORMULA(Define)
      PRODUCE RULE(DefType) MAKE(Define) MAKE_NODE(Define,L(4),0) RULE(DefItem) PARAM(MAKE_YACC(AddToList),0x02) MAKE_TREE(AddToList) RULE(DefineList) MAKE_CODE(EndDefine) END
   END

   FORMULA(ConditionDef)
      PRODUCE PRIOR(And) RULE(DefVar) MAKE_TREE(RefDef) MAKE_NODE(RefDef, L(1), 0) END
      PRODUCE RULE(DefVar) END
   END

   FORMULA(Condition)
      PRODUCE GROUP(DefVar) MAKE(Define) RULE(ConditionDef) MAKE(PushDef) MAKE_NODE(Copy,L(1),0) END
      PRODUCE EXPRESSION(Condition) END
   END

   FORMULA(ExprList)
      PRODUCE SYM(Comma) RULE(Assign) PARAM(MAKE_YACC(AddToList),0x06) MAKE_TREE(AddToList) MAKE_CODE(AddToExpr) MASTER END
      EMPTY 
   END

   FORMULA(Expressions)
      PRODUCE RULE(Assign) MAKE(ExpressionsLL) MAKE_NODE(Expressions,L(2,3),1) RULE(ExprList) MAKE_CODE(ExpressionSLL) END
   END

   bool PRIOR_ASSIGN = ((table.option & TGrammar::POption::opNoPriorAssign) == 0);

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

   FORMULA(AssignList)
      PRODUCE RULE(PriorAssign) MAKE_NODE(Copy,L(2),2) RULE(Assign) MAKE(Binary) MAKE_NODE(Binary,L(2,1),0) END
      EMPTY 
   END
   
   FORMULA(Assign)
      PRODUCE RULE(Question) MAKE_NODE(Copy,L(1,2),0) RULE(AssignList) END
   END

   FORMULA(QuestionList)  
      PRODUCE PRIOR(Question) MAKE_CODE(BegQuestion) EXPRESSION(Value) MAKE_NODE(Trio,L(0),0) SYM(Colon) MAKE_CODE(MidQuestion) RULE(Question) MAKE_NODE(Trio,L(0),1) MAKE(Question) END
      EMPTY 
   END
   
   FORMULA(Question)
      PRODUCE RULE(OrOr) MAKE_NODE(Copy,L(1,2),0) RULE(QuestionList) END
   END

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

   FORMULA(UnaryIncDec)
      PRODUCE PRIOR(IncDec) MAKE(IncDec) MAKE_NODE(Unary,L(2),1) END
      EMPTY
   END

   FORMULA(Unary)
      PRODUCE PRIOR(Unary)     RULE(Unary) MAKE(Unary) MAKE_NODE(Unary,L(1,2),0) END
      PRODUCE PRIOR(Term)      RULE(Unary) MAKE(Unary) MAKE_NODE(Unary,L(1,2),1) END
      PRODUCE PRIOR(IncDec)    RULE(Unary) MAKE(Unary) MAKE_NODE(Unary,L(1,2),0) END
      PRODUCE GROUP(CastUnary) RULE(Unary) MAKE(Cast)  MAKE_NODE(Cast,L(1,2),0) END
      PRODUCE RULE(PrimaryExpr) MAKE_NODE(Copy,L(1,2),0) RULE(UnaryIncDec) END 
   END

   FORMULA(Primary) 
      PRODUCE SYM(LeftBracket) EXPRESSION(None) MAKE_NODE(Copy,L(1),0) SYM(RightBracket) MAKE_TREE(Primary) END
   END

   FORMULA(PrimaryExpr) 
      PRODUCE LEX(Integer) MAKE(Number) MAKE_NODE(Number,L(1),0) END
      PRODUCE LEX(Number)  MAKE(Number) MAKE_NODE(Number,L(1),0) END
      PRODUCE GROUP(IdentArr)  RULE(Ranges) MAKE_NODE(Index,L(1),0) END
      PRODUCE GROUP(IdentFunc) RULE(CallParams) MAKE_NODE(Call,L(1),0) END
      PRODUCE GROUP(Cast)  RULE(Primary) MAKE(Cast) MAKE_NODE(Cast,L(1),0) END
      PRODUCE LEX(Ident)   MAKE(Ident)   MAKE_NODE(Var,L(1),0) END
      PRODUCE RULE(Primary) END
   END

   FORMULA(RangesList)
      PRODUCE SYM(LeftScrape) EXPRESSION(Value) PARAM(MAKE_YACC(AddToList),0x0A)  SYM(RightScrape) MAKE(IndexLL) MASTER END 
      EMPTY
   END

   FORMULA(Ranges)
      PRODUCE MAKE(BegIndexLL) MAKE_NODE(List,L(2,3),0) RULE(RangesList) MAKE(EndIndex) END
   END

   FORMULA(CallParams) 
      PRODUCE GROUP(EmptyBracket) MAKE(Params) MAKE_NODE(List,L(0),0) END
      PRODUCE SYM(LeftBracket) EXPRESSION(ValueList) MAKE_NODE(Copy,L(1),0) SYM(RightBracket) PARAM(MAKE(Params),0x01) END
   END

   FORMULA(CompaundStmnt)
      PRODUCE GROUP(EmptyCramp) MAKE(Compaund) MAKE_CODE(EndBlock) MAKE_NODE(Null,L(1),0) END
      PRODUCE SYM(LeftCramp) MAKE(Compaund) RULE(StmExpr) MAKE_NODE(Copy,L(1),0) SYM(RightCramp) MAKE_CODE(EndBlock) MAKE_TREE(AddToList) END
   END

   FORMULA(IfStmnt_)
      PRODUCE WARNING WORD(Else) MAKE_CODE(Else) RULE(DefExpr) PARAM(MAKE(If), 0x01) END
      PRODUCE WARNING MAKE(If) END
   END

   FORMULA(IfStmnt)
      PRODUCE WORD(If) SYM(LeftBracket) MAKE_CODE(BegIf) RULE(Condition) MAKE_NODE(If,L(1),0) SYM(RightBracket) MAKE_CODE(Then) RULE(DefExpr) MAKE_NODE(If,L(1),1) RULE(IfStmnt_) MAKE_NODE(If,L(1),2) END
   END 

   FORMULA(ForPrefix) // prefix
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) MAKE_NODE(Null, L(1), 0) END
      PRODUCE RULE(DefineSemi) END
      PRODUCE RULE(ExprSemi) END
   END

   FORMULA(ForCondition) // condition
      PRODUCE SYM(Semicolon) MAKE(NodeNull) MAKE_NODE(Null, L(1), 0) END
      PRODUCE RULE(Condition) MAKE_NODE(Copy, L(1), 0) SYM(Semicolon) END
   END

   FORMULA(ForPosfix) // postfix
      PRODUCE SYM(RightBracket) MAKE_TREE(NodeNull) MAKE_NODE(Null, L(1), 0) END
      PRODUCE EXPRESSION(Expression) MAKE_NODE(Copy, L(1), 0) SYM(RightBracket) END
   END

   FORMULA(ForStmnt)
      PRODUCE WORD(For) SYM(LeftBracket) MAKE(BegFor) RULE(ForPrefix) MAKE_CODE(PrefFor) MAKE_NODE(For,L(1),0) RULE(ForCondition) MAKE_CODE(ConditionFor) MAKE_NODE(For,L(1),1) RULE(ForPosfix) MAKE_CODE(PostFor) MAKE_NODE(For,L(1),2) RULE(DefExpr) MAKE_NODE(For,L(1),3) MAKE(For) END // body
   END 

   FORMULA(DoStmnt) 
      PRODUCE WORD(Do) MAKE(BegDo) RULE(DefExpr) MAKE_NODE(Copy,L(1),0) WORD(While) SYM(LeftBracket) MAKE_CODE(MidDo) RULE(Condition) MAKE_NODE(Do,L(1,4),0) SYM(RightBracket) SYM(Semicolon) MAKE(Do) END
   END 
   FORMULA(WhileStmnt) 
      PRODUCE WORD(While) MAKE(BegWhile) SYM(LeftBracket) RULE(Condition) MAKE_NODE(Copy,L(1),0) SYM(RightBracket) MAKE_CODE(MidWhile) RULE(DefExpr) MAKE(While) MAKE_NODE(While,L(2,1),0) END
   END 

/*
   FORMULA(SwitchStmnt) 
      PRODUCE WORD(Switch) SYM(LeftBracket) SYM(RightBracket) END 
   END
*/
   FORMULA(GoToStmnt) 
      PRODUCE WORD(GoTo) LEX(Ident) SYM(Semicolon) MAKE_NODE(GoTo,L(1),0) MAKE(GoTo) END 
   END

   FORMULA(BreakStmnt) 
      PRODUCE WORD(Break) SYM(Semicolon) MAKE(Break) MAKE_NODE(Break,L(1),0) END 
   END

   FORMULA(ContinueStmnt) 
      PRODUCE WORD(Continue) SYM(Semicolon) MAKE(Continue) MAKE_NODE(Continue,L(1),0) END 
   END

   FORMULA(ReturnVal)
      PRODUCE EXPRESSION(Value) PARAM(MAKE(Return), 0x01) END
      PRODUCE MAKE(Return) END
   END

   FORMULA(ReturnStmnt)
      PRODUCE WORD(Return) RULE(ReturnVal) MAKE_NODE(Return,L(1),0) SYM(Semicolon) END
   END 

   FORMULA(Statement) 
      PRODUCE GROUP(Label) SYM(Colon) MAKE_CODE(Label) RULE(DefExpr) MAKE_NODE(Label,L(1),0) MAKE_TREE(Label) END
      PRODUCE RULE(IfStmnt      ) END
      PRODUCE RULE(DoStmnt      ) END
      PRODUCE RULE(WhileStmnt   ) END
      PRODUCE RULE(ForStmnt     ) END
//      PRODUCE RULE(SwitchStmnt  ) END
      PRODUCE RULE(GoToStmnt    ) END
      PRODUCE RULE(BreakStmnt   ) END
      PRODUCE RULE(ContinueStmnt) END
      PRODUCE RULE(ReturnStmnt  ) END
      PRODUCE RULE(CompaundStmnt) END
   END

   FORMULA(DefineSemi) 
      PRODUCE RULE(Define) MAKE_NODE(Copy,L(1),0) SYM(Semicolon) END 
   END

   FORMULA(ExprSemi) 
     PRODUCE EXPRESSION(Expression) MAKE_NODE(Copy,L(1),0) SYM(Semicolon) END 
   END

   FORMULA(DefExpr) 
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) MAKE_NODE(Null,L(1),0) END 
      PRODUCE RULE(DefineSemi) END
      PRODUCE RULE(Statement) END
      PRODUCE RULE(ExprSemi) END
   END

   FORMULA(StmExprList)
      PRODUCE RULE(DefExpr) PARAM(MAKE_YACC(AddToList),0x06) MAKE_TREE(AddToList) MASTER END
      EMPTY
   END 

   FORMULA(StmExpr) 
      PRODUCE MAKE(BegStmExprLL) MAKE_NODE(Statements,L(2,3),0) RULE(StmExprList) MAKE_CODE(EndBlock) END
   END

   FORMULA(DefFAV) 
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) MAKE_NODE(Null,L(1),0) END 
      PRODUCE RULE(DefFunc) END
      PRODUCE RULE(DefineSemi) END
   END

   FORMULA(DefinesList)
      PRODUCE RULE(DefFAV) PARAM(MAKE_YACC(AddToList),0x06) MAKE_TREE(AddToList) MASTER END
      EMPTY
   END 

   FORMULA(Defines)
      PRODUCE MAKE(BegStmExprLL) MAKE_NODE(Statements,L(2,3),0) RULE(DefinesList) MAKE_CODE(EndBlock) END
   END
