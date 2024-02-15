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

#define GRAMMAR_FULL

#undef WORD_Define
//#define WORD_Define GROUP(DefType)
#define WORD_Define WORD(Define)

#if defined(PARSE_YACC)
   #define Prior_Assign RULE(PriorAssign)
   #define Prior_And    PRIOR(And)
#else
   #define Prior_Assign PRIOR(Assign)
   #define Prior_And    OPER(And)
#endif

   FORMULA(DefineParType)
      PRODUCE WORD(Const) WORD_Define OPER(And) PARAM(MAKE(DefType), 0x0B) END
      PRODUCE             WORD_Define OPER(And) PARAM(MAKE(DefType), 0x09) END
      PRODUCE WORD(Const) WORD_Define            PARAM(MAKE(DefType), 0x03) END
      PRODUCE             WORD_Define            PARAM(MAKE(DefType), 0x01) END
   END

   FORMULA(DefParType)
      PRODUCE RULE(DefineParType) LEX(Ident) END
   END

   FORMULA(DefPar) 
      PRODUCE OPER(Assign) RULE(Assign) MAKE(ParVarAssign) END
      EMPTY
   END

   FORMULA(DefParItem) 
      PRODUCE RULE(DefParType) SYM(LeftScrape) MAKE(DefParArr) RULE(DefArrDA) RULE(DefPar)  END
      PRODUCE RULE(DefParType) MAKE(DefParVar) RULE(DefPar) END
   END

   FORMULA(DefParamsList)
      PRODUCE SYM(Comma) RULE(DefParItem) MAKE_TREE(AddToList) MASTER END
      EMPTY
   END

   FORMULA(DefParams) 
      PRODUCE PARAM(MAKE_TREE(Define), 0x02) RULE(DefParItem) MAKE_TREE(AddToList) RULE(DefParamsList) MAKE_TREE(EndParams) END
   END

   FORMULA(BodyFunc)
      PRODUCE SYM(Semicolon) PARAM(MAKE(BodyFunc),0x00) END
      PRODUCE SYM(LeftCramp) SYM(RightCramp) PARAM(MAKE(BodyFunc),0x01) END
      PRODUCE SYM(LeftCramp) MAKE(BegStmExprLL) RULE(StmExpr) SYM(RightCramp) PARAM(MAKE(BodyFunc),0x02) END
   END

   FORMULA(DefFuncType)
      PRODUCE WORD(Static) WORD(Const) WORD_Define PARAM(MAKE(DefType),0x07) END
      PRODUCE WORD(Static)             WORD_Define PARAM(MAKE(DefType),0x05) END
      PRODUCE              WORD(Const) WORD_Define PARAM(MAKE(DefType),0x03) END
      PRODUCE                          WORD_Define PARAM(MAKE(DefType),0x01) END
      PRODUCE WORD(Static)             WORD(Void) PARAM(MAKE(DefType),0x24) END
      PRODUCE                          WORD(Void) PARAM(MAKE(DefType),0x20) END
   END

   FORMULA(DefFuncParams)
      PRODUCE SYM(RightBracket) PARAM(MAKE_TREE(EndParams), 0x02) END
      PRODUCE RULE(DefParams) SYM(RightBracket) END
   END

   FORMULA(DefFunc) 
      PRODUCE RULE(DefFuncType) LEX(Ident) SYM(LeftBracket) MAKE(FuncIdent) RULE(DefFuncParams) RULE(BodyFunc) END
   END

   FORMULA(AInitialList)
      PRODUCE SYM(Comma) RULE(AInitItem) MAKE_TREE(AddToList) MASTER END
      EMPTY
   END

   FORMULA(AInitial) 
      PRODUCE RULE(AInitItem) MAKE_TREE(AddToList) RULE(AInitialList) END
   END

   FORMULA(Initializer)
      PRODUCE SYM(LeftCramp) SYM(RightCramp) MAKE_TREE(NodeListLL) END
      PRODUCE SYM(LeftCramp) MAKE_TREE(NodeListLL) RULE(AInitial) SYM(RightCramp) END
   END

   FORMULA(AInitItem)
      PRODUCE RULE(Initializer) END
      PRODUCE RULE(Assign) END
   END

   FORMULA(DefAInit)
      PRODUCE OPER(Assign) RULE(Initializer) MAKE(EndAInit) END 
      EMPTY
   END

   FORMULA(DRanges)
      PRODUCE SYM(LeftScrape) RULE(Assign) SYM(RightScrape) MAKE(DRange) MASTER END
      EMPTY
   END

   FORMULA(DefArrD1A)
      PRODUCE SYM(RightScrape) MAKE(DefArrD1AEmpty) END
      PRODUCE  RULE(Assign) SYM(RightScrape) MAKE(DRange) END
   END

   FORMULA(DefArrDA) 
      PRODUCE RULE(DefArrD1A) RULE(DRanges) END
   END

   FORMULA(DefArr) 
      PRODUCE LEX(Ident) SYM(LeftScrape) MAKE(DefArray) RULE(DefArrDA) RULE(DefAInit) END
   END

   FORMULA(DefVarInit) 
      PRODUCE OPER(Assign) RULE(Assign) MAKE(DefVarAssign) END
      EMPTY
   END
   FORMULA(DefVar) 
      PRODUCE LEX(Ident) MAKE(DefIdent) RULE(DefVarInit) END
   END

   FORMULA(DefItem) 
      PRODUCE OPER(And) RULE(DefArr) MAKE_TREE(RefDef) END 
      PRODUCE OPER(And) RULE(DefVar) MAKE_TREE(RefDef) END 
      PRODUCE RULE(DefArr) END
      PRODUCE RULE(DefVar) END
   END

   FORMULA(DefType)
      PRODUCE WORD(Static) WORD(Const) WORD_Define PARAM(MAKE(DefType),0x07) PARAM(MAKE(Define),0x01) END
      PRODUCE WORD(Static)             WORD_Define PARAM(MAKE(DefType),0x05) PARAM(MAKE(Define),0x01) END
      PRODUCE              WORD(Const) WORD_Define PARAM(MAKE(DefType),0x03) PARAM(MAKE(Define),0x01) END
      PRODUCE                          WORD_Define PARAM(MAKE(DefType),0x01) PARAM(MAKE(Define),0x01) END
   END

   FORMULA(DefineList)
      PRODUCE SYM(Comma) RULE(DefItem) MAKE_TREE(AddToList) MASTER END
      EMPTY
   END

   FORMULA(Define)
      PRODUCE RULE(DefType) RULE(DefItem) MAKE_TREE(AddToList) RULE(DefineList) END
   END

   FORMULA(ConditionVar)
      PRODUCE OPER(And) RULE(DefVar) MAKE_TREE(RefDef) END
      PRODUCE RULE(DefVar) END
   END

   FORMULA(Condition)
      PRODUCE RULE(DefType) RULE(ConditionVar) MAKE(PushDef) END
      PRODUCE EXPRESSION(Condition) END
   END

   FORMULA(ExpressionsList)
      PRODUCE SYM(Comma) RULE(Assign) MAKE_TREE(AddToList) MASTER END
      EMPTY
   END

   FORMULA(Expressions)
      PRODUCE RULE(Assign) MAKE(ExpressionsLL) RULE(ExpressionsList) END
   END

   FORMULA(PriorAssign) 
      PRODUCE OPER(AddAssign) END PRODUCE OPER(SubAssign) END PRODUCE OPER(MultiAssign) END PRODUCE OPER(DivAssign)    END PRODUCE OPER(ModAssign)    END PRODUCE OPER(Assign) END
      PRODUCE OPER(OrAssign)  END PRODUCE OPER(XOrAssign) END PRODUCE OPER(AndAssign)   END PRODUCE OPER(LShiftAssign) END PRODUCE OPER(RShiftAssign) END
   END

   FORMULA(AssignList)
      PRODUCE PRIOR(Assign) RULE(Assign) MAKE(Binary) END
      EMPTY
   END

   FORMULA(Assign)
      PRODUCE RULE(Question) RULE(AssignList) END
   END

   FORMULA(QuestionList)
      PRODUCE PRIOR(Question) EXPRESSION(Value) SYM(Colon) RULE(Question) MAKE(Question) END
      EMPTY
   END

   FORMULA(Question)
      PRODUCE RULE(OrOr) RULE(QuestionList) END
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
      PRODUCE PRIOR(IncDec) MAKE(IncDec) MASTER END
      EMPTY
   END

   FORMULA(DefineCast)
      PRODUCE WORD(Const) WORD_Define PARAM(MAKE(DefType), 0x03) END
      PRODUCE             WORD_Define PARAM(MAKE(DefType), 0x01) END
   END

   FORMULA(Unary)
      PRODUCE PRIOR(Unary)     RULE(Unary) MAKE(Unary) END
      PRODUCE PRIOR(Term)      RULE(Unary) MAKE(Unary) END
      PRODUCE PRIOR(IncDec)    RULE(Unary) MAKE(Unary) END
#if defined(GRAMMAR_FULL)
      PRODUCE SYM(LeftBracket) RULE(DefineCast) SYM(RightBracket) RULE(Unary) MAKE(Cast) END
#endif
      PRODUCE RULE(PrimaryExpr) RULE(UnaryIncDec) END 
   END

   FORMULA(Primary) 
      PRODUCE SYM(LeftBracket) EXPRESSION(None) SYM(RightBracket) MAKE_TREE(Primary) END 
   END

   FORMULA(PrimaryExpr) 
      PRODUCE LEX(Ident) SYM(LeftScrape)  RULE(Ranges) END
      PRODUCE LEX(Ident) SYM(LeftBracket) RULE(CallParams) END
      PRODUCE LEX(Integer) MAKE(Number) END
      PRODUCE LEX(Number)  MAKE(Number) END
      PRODUCE LEX(Ident)   MAKE(Ident)  END
      PRODUCE RULE(Primary) END
#if defined(GRAMMAR_FULL)
      PRODUCE WORD_Define RULE(Primary) MAKE(Cast) END
#endif
   END

   FORMULA(Range)
      PRODUCE SYM(LeftScrape) EXPRESSION(Value) SYM(RightScrape) MAKE(IndexLL) MASTER END
      EMPTY
   END

   FORMULA(Ranges)
      PRODUCE MAKE(BegIndexLL) EXPRESSION(Value) SYM(RightScrape) MAKE(IndexLL) RULE(Range) MAKE(EndIndex) END
   END

   FORMULA(CallParams) 
      PRODUCE SYM(RightBracket) MAKE(Params) END
      PRODUCE EXPRESSION(ValueList) SYM(RightBracket) PARAM(MAKE(Params),0x01) END
   END

   FORMULA(CompaundStmnt)
      PRODUCE SYM(LeftCramp) SYM(RightCramp) MAKE(Compaund) END
      PRODUCE SYM(LeftCramp) MAKE(Compaund) RULE(StmExpr) SYM(RightCramp) END
   END
   FORMULA(IfStmntElse)
      PRODUCE WORD(Else) RULE(DefExpr) PARAM(MAKE(If), 0x01) END
      PRODUCE WARNING MAKE(If) END
   END
   FORMULA(IfStmnt)
      PRODUCE WORD(If) SYM(LeftBracket) RULE(Condition) SYM(RightBracket) RULE(DefExpr) RULE(IfStmntElse) END
   END 

   FORMULA(ForPrefix) // prefix
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) END
      PRODUCE RULE(DefineSemi) END
      PRODUCE RULE(ExprSemi) END
   END
   FORMULA(ForCondition) // condition
      PRODUCE SYM(Semicolon) MAKE(NodeNull) END
      PRODUCE RULE(Condition) SYM(Semicolon) END
   END
   FORMULA(ForPostfix) // postfix
      PRODUCE SYM(RightBracket) MAKE_TREE(NodeNull) END
      PRODUCE EXPRESSION(Expression) SYM(RightBracket) END
   END

   FORMULA(ForStmnt) 
      PRODUCE WORD(For) SYM(LeftBracket) MAKE(BegFor) RULE(ForPrefix) RULE(ForCondition) RULE(ForPostfix) RULE(DefExpr) MAKE(For) END // body 
   END 
   FORMULA(DoStmnt      ) PRODUCE WORD(Do      ) MAKE(BegDo)      RULE(DefExpr) WORD(While) SYM(LeftBracket) RULE(Condition) SYM(RightBracket) SYM(Semicolon) MAKE(Do) END END
   FORMULA(WhileStmnt   ) PRODUCE WORD(While   ) MAKE(BegWhile)   SYM(LeftBracket) RULE(Condition) SYM(RightBracket) RULE(DefExpr) MAKE(While) END END
   FORMULA(SwitchStmnt  ) PRODUCE WORD(Switch  ) SYM(LeftBracket) SYM(RightBracket) END END
   FORMULA(GoToStmnt    ) PRODUCE WORD(GoTo    ) LEX(Ident)       SYM(Semicolon) MAKE(GoTo) END END
   FORMULA(BreakStmnt   ) PRODUCE WORD(Break   ) SYM(Semicolon)   MAKE(Break   ) END END
   FORMULA(ContinueStmnt) PRODUCE WORD(Continue) SYM(Semicolon)   MAKE(Continue) END END

   FORMULA(ReturnValue)
      PRODUCE EXPRESSION(Value) PARAM(MAKE(Return), 0x01) END
      PRODUCE MAKE(Return) END
   END

   FORMULA(ReturnStmnt  ) 
      PRODUCE WORD(Return) RULE(ReturnValue) SYM(Semicolon) END
   END 

   FORMULA(Statement) 
      PRODUCE RULE(IfStmnt      ) END
      PRODUCE RULE(DoStmnt      ) END
      PRODUCE RULE(WhileStmnt   ) END
      PRODUCE RULE(ForStmnt     ) END
      PRODUCE RULE(SwitchStmnt  ) END
      PRODUCE RULE(GoToStmnt    ) END
      PRODUCE RULE(BreakStmnt   ) END
      PRODUCE RULE(ContinueStmnt) END
      PRODUCE RULE(ReturnStmnt  ) END
      PRODUCE RULE(CompaundStmnt) END
   END

   FORMULA(DefineSemi) PRODUCE RULE(Define) SYM(Semicolon) END END
   FORMULA(ExprSemi) PRODUCE EXPRESSION(Expression) SYM(Semicolon) END END
   FORMULA(DefExpr) 
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) END 
#if defined(GRAMMAR_FULL)
      PRODUCE LEX(Ident) SYM(Colon) RULE(DefExpr) MAKE_TREE(Label) END
#endif
      PRODUCE RULE(DefineSemi) END
      PRODUCE RULE(Statement) END
      PRODUCE RULE(ExprSemi) END
   END

   FORMULA(StmExpr) 
      PRODUCE RULE(DefExpr) MAKE_TREE(AddToList) MASTER END
      EMPTY
   END

   FORMULA(DefFAV) 
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) END 
      PRODUCE RULE(DefFunc) END
      PRODUCE RULE(DefineSemi) END
   END

   FORMULA(DefinesBeg)
      PRODUCE RULE(DefFAV) MAKE_TREE(AddToList) MASTER END
      EMPTY
   END

   FORMULA(Defines)
      PRODUCE MAKE(BegStmExprLL) RULE(DefinesBeg) END
   END
