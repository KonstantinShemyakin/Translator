   FORMULA(S_) 
      PRODUCE RULE(Program) END
   END

   FORMULA(Program)
#if   defined(DEFINE_RULE_FULL)
      PRODUCE RULE(Defines) MAKE_NODE(None, L(1), 1) END
#elif defined(DEFINE_RULE_DEF)
      PRODUCE RULE(Define) MAKE_NODE(None, L(1), 1) END
#elif defined(DEFINE_RULE_EXPR)
      PRODUCE EXPRESSION(Expression) MAKE_NODE(None, L(1), 1) END
#elif defined(DEFINE_RULE_STMT)
      PRODUCE RULE(StmExpr) MAKE_NODE(None, L(1), 1) END
#else
#endif
   END

#define NO_PRIOR_SYMBOL
#if  defined(NO_PRIOR_SYMBOL)
#undef PRIOR
#define PRIOR(P) RULE(Prior##P)
#endif

#undef WORD_Define
#define WORD_Define  GROUP(DefType)

   FORMULA(DefParType)
      PRODUCE WORD(Const) WORD_Define OPER(And) PARAM(MAKE_ALL(DefType),0x0B) END
      PRODUCE             WORD_Define OPER(And) PARAM(MAKE_ALL(DefType),0x09) END
      PRODUCE WORD(Const) WORD_Define           PARAM(MAKE_ALL(DefType),0x03) END
      PRODUCE             WORD_Define           PARAM(MAKE_ALL(DefType),0x01) END
   END

   FORMULA(DefBegParVar) 
      PRODUCE RULE(DefParType) LEX(Ident) MAKE(DefParVar) MAKE_NODE(DefVar,L(2,1),1) END
   END
   FORMULA(DefParVar) 
      PRODUCE RULE(DefBegParVar) OPER(Assign) MAKE_CODE(BegParVarAssign) RULE(Assign) MAKE(ParVarAssign) MAKE_NODE(DefVar,L(2,1,3),2) END
      PRODUCE RULE(DefBegParVar) END
   END

   FORMULA(DefBegParArr) 
      PRODUCE RULE(DefParType) LEX(Ident) MAKE(DefParArr) RULE(DefBegRanges) MAKE_NODE(DefArr,L(2,1,0,3),1) END
   END
   FORMULA(DefParArr) 
      PRODUCE RULE(DefBegParArr) OPER(Assign) MAKE_CODE(BegParVarAssign) RULE(Assign) MAKE(ParVarAssign) MAKE_NODE(DefArr,L(2,1,3),2) END 
      PRODUCE RULE(DefBegParArr) END // !!!
   END

   FORMULA(DefParItem) 
      PRODUCE RULE(DefParArr) END
      PRODUCE RULE(DefParVar) END
   END

   FORMULA(DefParams)
      PRODUCE MASTER SYM(Comma) RULE(DefParItem) MAKE_TREE(AddToList) PARAM(MAKE_YACC(AddToList),0x05) END
      PRODUCE RULE(DefParItem) MAKE_TREE(AddToList) MAKE_NODE(Define,L(0,0,1),0) END
   END

   FORMULA(BodyFunc)
      PRODUCE SYM(Semicolon) PARAM(MAKE(BodyFunc),0x00) MAKE_NODE(NodeOne,L(1),0) END
      PRODUCE SYM(LeftCramp) SYM(RightCramp) PARAM(MAKE(BodyFunc),0x01) MAKE_NODE(NodeOne,L(1),1) END
      PRODUCE SYM(LeftCramp) MAKE_CODE(EndParams) MAKE(BegStmExprLR) RULE(StmExpr) SYM(RightCramp) PARAM(MAKE(BodyFunc),0x02) MAKE_NODE(NodeOne,L(1,2),2) END
   END

   FORMULA(DefFuncPar)
      PRODUCE SYM(RightBracket) PARAM(MAKE_TREE(EndParams),0x01) MAKE_NODE(Define,L(0),0) END
      PRODUCE RULE(DefParams) SYM(RightBracket) MAKE_TREE(EndParams) END
   END

   FORMULA(DefPBFuncMaker)
      PRODUCE PARAM(MAKE_TREE(Define), 0x02) RULE(DefFuncPar) MAKE_NODE(DefFunc,L(0,1),2) END
   END

   FORMULA(DefParBodyFunc)
      PRODUCE RULE(DefPBFuncMaker) RULE(BodyFunc) MAKE_NODE(NodeTwo,L(0,1,2),0) END
   END

   FORMULA(DefVoidType)
      PRODUCE WORD(Static)             WORD(Void) PARAM(MAKE_ALL(DefType),0x24) END
      PRODUCE                          WORD(Void) PARAM(MAKE_ALL(DefType),0x20) END
   END

   FORMULA(DefType)
      PRODUCE WORD(Static) WORD(Const) WORD_Define PARAM(MAKE_ALL(DefType),0x07) END
      PRODUCE WORD(Static)             WORD_Define PARAM(MAKE_ALL(DefType),0x05) END
      PRODUCE              WORD(Const) WORD_Define PARAM(MAKE_ALL(DefType),0x03) END
      PRODUCE                          WORD_Define PARAM(MAKE_ALL(DefType),0x01) END
   END

   FORMULA(CommaDefItem)
      PRODUCE MASTER SYM(Comma) RULE(DefItem) MAKE_TREE(AddToList) PARAM(MAKE_YACC(AddToList),0x05) END
      PRODUCE RULE(DefItem) MAKE_TREE(AddToList) MAKE_NODE(Define,L(0,0,1),0) END
   END

   FORMULA(Define)
      PRODUCE RULE(DefType) PARAM(MAKE(Define),0x01) RULE(CommaDefItem) MAKE_CODE(EndDefine) MAKE_NODE(Define,L(0,1,0,2),1) END
   END

   FORMULA(DefineBegRanges)
      PRODUCE SYM(RightScrape) MAKE(DefArrD1AEmpty) RULE(DefRanges) MAKE_NODE(Ranges, L(1, 2), 1) END // ins(Null) 
      PRODUCE SYM(RightScrape) MAKE(DefArrD1AEmpty) MAKE_NODE(Ranges, L(1), 0) END // Null 
      PRODUCE RULE(Assign) SYM(RightScrape) MAKE(DRange) RULE(DefRanges) MAKE_NODE(Ranges, L(0, 3, 1), 4) END // ins
      PRODUCE RULE(Assign) SYM(RightScrape) MAKE(DRange) MAKE_NODE(Ranges, L(0, 1), 2) END // create
   END

   FORMULA(DefineBegArr) 
      PRODUCE RULE(DefineBegRanges) MAKE_CODE(EndRanges) END
   END

   FORMULA(DefineArr) 
      PRODUCE RULE(IdentLeftScrape) OPER(Assign) MAKE_CODE(BegAInit) RULE(Initializer) MAKE(EndAInit) MAKE_NODE(DefArr,L(0,1,3),2) END 
      PRODUCE RULE(IdentLeftScrape) END
   END

   FORMULA(IdentLeftScrape) 
      PRODUCE LEX(Ident) SYM(LeftScrape) MAKE(Define) MAKE(DefArray) RULE(DefineBegArr) MAKE_NODE(DefArr,L(1,0,0,3),1) END
   END

   FORMULA(DefineVarAssign) 
      PRODUCE SYM(Comma) RULE(CommaDefItem) SYM(Semicolon) MAKE_CODE(EndDefine) MAKE_NODE(None,L(2),0) END
      PRODUCE SYM(Semicolon) MAKE_CODE(EndDefine) END
   END

   FORMULA(DefVariableAssign)
      PRODUCE LEX(Ident) MAKE(Define) MAKE(DefIdent) OPER(Assign) MAKE_CODE(BegDefVarAssign) RULE(Assign) MAKE(DefVarAssign) MAKE_TREE(AddToList) MAKE_NODE(DefVar, L(1, 0, 3), 1) END
   END

   FORMULA(DefVarComma)
      PRODUCE LEX(Ident) MAKE(Define) MAKE(DefIdent) MAKE_TREE(AddToList) MAKE_NODE(DefVar, L(1), 0) END
   END

   FORMULA(DefVarSemicolon)
      PRODUCE LEX(Ident) MAKE(Define) MAKE(DefIdent) MAKE_TREE(AddToList) MAKE_NODE(DefVar, L(1), 0) END
   END

   FORMULA(DefFuncAVMaker)
      PRODUCE RULE(DefType) LEX(Ident) SYM(LeftBracket) MAKE(FuncIdent) MAKE_NODE(DefFunc,L(2,1),1)  END
   END

   FORMULA(DefFuncArrVar)
      PRODUCE 
         RULE(DefType) LEX(Ident) SYM(LeftBracket) MAKE(FuncIdent) MAKE_NODE(DefFunc,L(2,1),1) RULE(DefParBodyFunc) MAKE_NODE(DefFunc,L(2,1,5),0)
      END
      PRODUCE 
         RULE(DefType) RULE(DefineArr) MAKE_TREE(AddToList) SYM(Comma) RULE(CommaDefItem) SYM(Semicolon) MAKE_CODE(EndDefine) MAKE_NODE(Define,L(0,1,2,4),1)
      END
      PRODUCE 
         RULE(DefType) RULE(DefineArr) MAKE_TREE(AddToList) SYM(Semicolon) MAKE_CODE(EndDefine) MAKE_NODE(Define,L(0,1,2),0) 
      END 
      PRODUCE 
         RULE(DefType) RULE(DefVariableAssign) RULE(DefineVarAssign) MAKE_NODE(Define,L(0,1,2,3),1)
      END
      PRODUCE 
         RULE(DefType) RULE(DefVarComma) SYM(Comma) RULE(CommaDefItem) SYM(Semicolon) MAKE_CODE(EndDefine) MAKE_NODE(Define,L(0,1,2,4),1)
      END
      PRODUCE 
         RULE(DefType) RULE(DefVarSemicolon) SYM(Semicolon) MAKE_CODE(EndDefine) MAKE_NODE(Define,L(0,1,2),0) 
      END 
   END

   FORMULA(DefFuncDefine)
      PRODUCE RULE(DefVoidType) LEX(Ident) SYM(LeftBracket) MAKE(FuncIdent) MAKE_NODE(DefFunc,L(2,1),1) RULE(DefParBodyFunc) MAKE_NODE(DefFunc,L(2,1,5),0) END
      PRODUCE RULE(DefFuncArrVar) END
   END

   FORMULA(AInitItem)
      PRODUCE RULE(Initializer) END
      PRODUCE RULE(Assign) MAKE_CODE(AInitItem) END
   END

   FORMULA(AInitial)
      PRODUCE MASTER SYM(Comma) RULE(AInitItem) MAKE_TREE(AddToList) MAKE_NODE(List,L(0,3,1),1) END
      PRODUCE RULE(AInitItem) MAKE_TREE(AddToList) MAKE_NODE(List,L(1,1),0) END
   END

   FORMULA(Initializer)
      PRODUCE SYM(LeftCramp) SYM(RightCramp) MAKE_CODE(BegInitial) MAKE_TREE(NodeListLR) MAKE_NODE(List,L(1),0) END
      PRODUCE SYM(LeftCramp) PARAM(MAKE_CODE(BegInitial),0x01) MAKE_TREE(NodeListLR) RULE(AInitial) SYM(RightCramp) MAKE_CODE(EndInitial) MAKE_NODE(None,L(2),0) END
   END

   FORMULA(DefRange)
      PRODUCE SYM(LeftScrape) RULE(Assign) SYM(RightScrape) MAKE_NODE(None, L(2), 0) END
   END

   FORMULA(DefRanges)
      PRODUCE MASTER RULE(DefRange) MAKE(DRange) MAKE_NODE(Ranges,L(0,1,2),3) END // add
      PRODUCE RULE(DefRange) MAKE(DRange) MAKE_NODE(Ranges,L(0,1),2) END // create
   END

   FORMULA(DefBegRanges) 
      PRODUCE SYM(LeftScrape) SYM(RightScrape) MAKE(DefArrD1AEmpty) RULE(DefRanges) MAKE_NODE(Ranges,L(1,3),1) END // ins(Null)
      PRODUCE SYM(LeftScrape) SYM(RightScrape) MAKE(DefArrD1AEmpty) MAKE_NODE(Ranges,L(1),0) END // Null
      PRODUCE RULE(DefRanges) END
   END

   FORMULA(DefBegArr) 
      PRODUCE LEX(Ident) MAKE(DefArray) RULE(DefBegRanges) MAKE_CODE(EndRanges) MAKE_NODE(DefArr,L(1,0,0,2),1) END // (Lexeme,Type,Assign,Range)
   END

   FORMULA(DefArr) 
      PRODUCE RULE(DefBegArr) OPER(Assign) MAKE_CODE(BegAInit) RULE(Initializer) MAKE(EndAInit) MAKE_NODE(DefArr,L(0,1,3),2) END // (,Node,Assign)
      PRODUCE RULE(DefBegArr) END
   END

   FORMULA(DefVarIdent) 
      PRODUCE LEX(Ident) MAKE(DefIdent) MAKE_NODE(DefVar, L(1), 0) END
   END

   FORMULA(DefVarAssign)
      PRODUCE OPER(Assign) MAKE_CODE(BegDefVarAssign) RULE(Assign) MAKE(DefVarAssign) MAKE_NODE(None, L(2),0) END
   END
   FORMULA(DefVar)
      PRODUCE RULE(DefVarIdent) RULE(DefVarAssign) MAKE_NODE(DefVar, L(0, 1, 2), 2) END
      PRODUCE RULE(DefVarIdent) END
   END

   FORMULA(DefIAV) 
      PRODUCE RULE(DefArr) END
      PRODUCE RULE(DefVar) END
   END
   FORMULA(RefDefIAV)
      PRODUCE OPER(And) RULE(DefIAV) MAKE_TREE(RefDef) MAKE_NODE(RefDef,L(1,2),0) END
   END
   FORMULA(DefItem) 
      PRODUCE RULE(RefDefIAV) END 
      PRODUCE RULE(DefIAV) END 
   END

   FORMULA(Expressions)
      PRODUCE MASTER SYM(Comma) RULE(Assign) MAKE_TREE(AddToList) MAKE_CODE(AddToExpr) PARAM(MAKE_YACC(AddToList),0x05) END
      PRODUCE RULE(Assign) MAKE(ExpressionsLR) MAKE_NODE(Expressions,L(1,1),0) END
   END

   FORMULA(PriorAssign) 
      PRODUCE OPER(AddAssign) END PRODUCE OPER(SubAssign) END PRODUCE OPER(MultiAssign) END PRODUCE OPER(DivAssign)    END PRODUCE OPER(ModAssign)    END PRODUCE OPER(Assign) END
      PRODUCE OPER(OrAssign)  END PRODUCE OPER(XOrAssign) END PRODUCE OPER(AndAssign)   END PRODUCE OPER(LShiftAssign) END PRODUCE OPER(RShiftAssign) END
   END

   FORMULA(PriorQuestion) PRODUCE OPER(Question) END END
   FORMULA(PriorOrOr)     PRODUCE OPER(OrOr)     END END
   FORMULA(PriorAndAnd)   PRODUCE OPER(AndAnd)   END END
   FORMULA(PriorOr)       PRODUCE OPER(Or)       END END
   FORMULA(PriorXOr)      PRODUCE OPER(XOr)      END END
   FORMULA(PriorAnd)      PRODUCE OPER(And)      END END
   FORMULA(PriorEqu)      PRODUCE OPER(Equ)      END PRODUCE OPER(NotEqu)     END END
   FORMULA(PriorCompare)  PRODUCE OPER(LE)       END PRODUCE OPER(LT)         END PRODUCE OPER(GE) END PRODUCE OPER(GT) END END
   FORMULA(PriorShift)    PRODUCE OPER(LShift)   END PRODUCE OPER(RShift)     END END
   FORMULA(PriorTerm)     PRODUCE OPER(Add)      END PRODUCE OPER(Sub)        END END
   FORMULA(PriorFactor)   PRODUCE OPER(Multi)    END PRODUCE OPER(Div)        END PRODUCE OPER(Mod) END END
   FORMULA(PriorUnary)    PRODUCE OPER(Not)      END PRODUCE OPER(Tilda)      END END
   FORMULA(PriorIncDec)   PRODUCE OPER(PlusPlus) END PRODUCE OPER(MinusMinus) END END

   FORMULA(Assign)
      PRODUCE RULE(Question) PRIOR(Assign) MASTER MAKE(Binary) MAKE_NODE(Binary,L(2,1,3),0) END
      PRODUCE RULE(Question) END
   END

   FORMULA(Question)
      PRODUCE RULE(OrOr) PRIOR(Question) MAKE_CODE(BegQuestion) EXPRESSION(Value) SYM(Colon) MAKE_CODE(MidQuestion) MASTER MAKE(Question) MAKE_NODE(Trio,L(2,1,3,5),0) END
      PRODUCE RULE(OrOr) END
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
      PRODUCE RULE(PrimaryExpr) PRIOR(IncDec) MAKE(IncDec) MAKE_NODE(Unary, L(2, 1), 1) END
      PRODUCE RULE(PrimaryExpr) END
   END

   FORMULA(DefTypeCast)
      PRODUCE WORD(Const) WORD_Define PARAM(MAKE_ALL(DefType), 0x03) END
      PRODUCE             WORD_Define PARAM(MAKE_ALL(DefType), 0x01) END
   END

   FORMULA(Unary)
      PRODUCE PRIOR(Unary)     RULE(Unary) MAKE(Unary) MAKE_NODE(Unary,L(1,2),0) END
      PRODUCE PRIOR(Term)      RULE(Unary) MAKE(Unary) MAKE_NODE(Unary,L(1,2),1) END
      PRODUCE PRIOR(IncDec)    RULE(Unary) MAKE(Unary) MAKE_NODE(Unary,L(1,2),0) END
      PRODUCE SYM(LeftBracket) RULE(DefTypeCast) SYM(RightBracket) RULE(Unary) MAKE(Cast) MAKE_NODE(Cast,L(2,4),0) END
      PRODUCE RULE(UnaryIncDec) END
   END

   FORMULA(Primary) 
      PRODUCE SYM(LeftBracket) EXPRESSION(None) SYM(RightBracket) MAKE_TREE(Primary) MAKE_NODE(Primary, L(1, 2), 0) END 
   END

   FORMULA(PrimaryExpr) 
      PRODUCE LEX(Integer) MAKE(Number) MAKE_NODE(Number,L(1),0) END
      PRODUCE LEX(Number)  MAKE(Number) MAKE_NODE(Number,L(1),0) END
      PRODUCE LEX(Ident)   RULE(Ranges) MAKE(EndIndex) MAKE_NODE(Index,L(1,2),0) END
      PRODUCE LEX(Ident)   RULE(CallParams) MAKE_NODE(Call,L(1,2),0) END
      PRODUCE WORD_Define  RULE(Primary) MAKE(Cast) MAKE_NODE(Cast,L(1,2),0) END
      PRODUCE LEX(Ident)   MAKE(Ident) MAKE_NODE(Var,L(1),0) END  // !LR0
      PRODUCE RULE(Primary) END
   END

   FORMULA(Range) 
      PRODUCE SYM(LeftScrape) EXPRESSION(Value) SYM(RightScrape) MAKE_NODE(None, L(2), 0) END
   END

   FORMULA(Ranges)
      PRODUCE MASTER RULE(Range) MAKE(IndexLR) PARAM(MAKE_YACC(AddToList),0x03) END
      PRODUCE RULE(Range) MAKE(BegIndexLR) MAKE_NODE(List,L(0,1),0) END 
   END

   FORMULA(CallParams) 
      PRODUCE SYM(LeftBracket) SYM(RightBracket) MAKE(Params) MAKE_NODE(List,L(1),0) END
      PRODUCE SYM(LeftBracket) EXPRESSION(ValueList) SYM(RightBracket) PARAM(MAKE(Params),0x01) MAKE_NODE(None,L(2),0) END
   END

   FORMULA(CompaundStmnt)
      PRODUCE SYM(LeftCramp) SYM(RightCramp) MAKE(Compaund) MAKE_CODE(EndBlock) MAKE_NODE(Statements,L(1),0) END
      PRODUCE SYM(LeftCramp) MAKE(Compaund) RULE(StmExpr) SYM(RightCramp) MAKE_NODE(None,L(2),0) END
   END
      
   FORMULA(ConditionVar)
      PRODUCE OPER(And) RULE(DefVar) MAKE_TREE(RefDef) MAKE_NODE(RefDef, L(1, 2), 0) END
      PRODUCE RULE(DefVar) END
   END

   FORMULA(Condition)
      PRODUCE RULE(DefType) PARAM(MAKE(Define),0x01) RULE(ConditionVar) MAKE(PushDef) MAKE_NODE(Define,L(0,1,2),0) END
      PRODUCE EXPRESSION(Condition) END
   END

   FORMULA(ForPrefix) // prefix
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) MAKE_NODE(Null, L(1), 0) END
      PRODUCE RULE(DefineSemi) END
      PRODUCE RULE(ExprSemi) END
   END
   FORMULA(ForCondition) // condition
      PRODUCE SYM(Semicolon) MAKE(NodeNull) MAKE_NODE(Null, L(1), 0) END
      PRODUCE RULE(Condition) SYM(Semicolon) END
   END
   FORMULA(ForPostfix) // postfix
      PRODUCE SYM(RightBracket) MAKE_TREE(NodeNull) MAKE_NODE(Null, L(1), 0) END
      PRODUCE EXPRESSION(Expression) SYM(RightBracket) END
   END

   FORMULA(ForStmnt) 
      PRODUCE
         WORD(For) SYM(LeftBracket) MAKE(BegFor)
         RULE(ForPrefix) MAKE_CODE(PrefFor)
         RULE(ForCondition) MAKE_CODE(ConditionFor)
         RULE(ForPostfix) MAKE_CODE(PostFor)
         RULE(DefExpr) // body
         MAKE(For) MAKE_NODE(For,L(1,3,4,5,6),0) 
      END
   END 

   FORMULA(DoStmnt      ) PRODUCE WORD(Do      ) MAKE(BegDo)      RULE(DefExpr)    WORD(While) SYM(LeftBracket) RULE(Condition) SYM(RightBracket) SYM(Semicolon) MAKE(Do) MAKE_NODE(Do,L(1,5,2),0) END END
   FORMULA(WhileStmnt   ) PRODUCE WORD(While   ) MAKE(BegWhile)   SYM(LeftBracket) RULE(Condition)   SYM(RightBracket) RULE(DefExpr) MAKE(While) MAKE_NODE(While,L(1,3,5),0) END END
//   FORMULA(SwitchStmnt  ) PRODUCE WORD(Switch  ) SYM(LeftBracket) SYM(RightBracket) END END
   FORMULA(GoToStmnt    ) PRODUCE WORD(GoTo    ) LEX(Ident)       SYM(Semicolon)  MAKE_NODE(GoTo    ,L(2),0) MAKE(GoTo) END END
   FORMULA(BreakStmnt   ) PRODUCE WORD(Break   ) SYM(Semicolon)   MAKE(Break   )  MAKE_NODE(Break   ,L(1),0) END END
   FORMULA(ContinueStmnt) PRODUCE WORD(Continue) SYM(Semicolon)   MAKE(Continue)  MAKE_NODE(Continue,L(1),0) END END

   FORMULA(ReturnValue)
      PRODUCE SYM(Semicolon) MAKE(Return) MAKE_NODE(Return, L(1), 0) END
      PRODUCE EXPRESSION(Value) SYM(Semicolon) PARAM(MAKE(Return), 0x01) MAKE_NODE(Return, L(1, 1), 0) END
   END
   FORMULA(ReturnStmnt  )
      PRODUCE WORD(Return) RULE(ReturnValue) MAKE_NODE(Return,L(1,2),1) END
   END 

#define IF_ELSE_LR1_

#ifdef IF_ELSE_LR1
   FORMULA(IfStatement) 
      PRODUCE RULE(IfSttmnt_M) END 
      PRODUCE RULE(IfSttmnt_U) END
   END

   FORMULA(BegIfStmnt) 
      PRODUCE WORD(If) SYM(LeftBracket) MAKE_CODE(BegIf) RULE(Condition) SYM(RightBracket) MAKE_CODE(Then) MAKE_NODE(If, L(1, 3, 5), 0) END
   END

   FORMULA(IfSttmnt_M)
      PRODUCE RULE(BegIfStmnt)    RULE(IfSttmnt_M)     WORD(Else)  MAKE_CODE(Else)  RULE(IfSttmnt_M) PARAM(MAKE(If), 0x01) MAKE_NODE(If, L(2, 1, 3), 1) END
      PRODUCE RULE(DefExpr) END
   END

   FORMULA(IfSttmnt_U)
      PRODUCE RULE(BegIfStmnt)    RULE(IfStatement)    MAKE(If)    END
      PRODUCE RULE(BegIfStmnt)    RULE(IfSttmnt_M)     WORD(Else)  MAKE_CODE(Else)  RULE(IfSttmnt_U) PARAM(MAKE(If), 0x01) MAKE_NODE(If, L(2, 1, 3), 1) END
   END
#else
   FORMULA(BegIfStmnt) 
      PRODUCE WORD(If) SYM(LeftBracket) MAKE_CODE(BegIf) RULE(Condition) SYM(RightBracket) MAKE_CODE(Then) RULE(DefExpr) MAKE_NODE(If, L(1, 3, 5), 0) END
   END
#endif

   FORMULA(LabelIdent) 
      PRODUCE LEX(Ident) SYM(Colon) MAKE_CODE(Label) MAKE_NODE(Label, L(1), 0) END
   END

   FORMULA(LabelList)
      PRODUCE RULE(LabelIdent) MAKE_NODE(List, L(0, 1), 0) END
   END

   FORMULA(Statement)
#ifdef IF_ELSE_LR1
      PRODUCE RULE(IfStatement) END
#else
      PRODUCE RULE(BegIfStmnt) WORD(Else) MAKE_CODE(Else) RULE(DefExpr) PARAM(MAKE(If),0x01) MAKE_NODE(If,L(2,1,3),1) END
      PRODUCE WARNING RULE(BegIfStmnt) MAKE(If) END
#endif
      PRODUCE 
         RULE(LabelList) RULE(DefExpr) PARAM(MAKE_YACC(AddToList),0x03) MAKE_TREE(Label)
      END
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

   FORMULA(DefineSemi) PRODUCE RULE(Define) SYM(Semicolon) END END
   FORMULA(ExprSemi) PRODUCE EXPRESSION(Expression) SYM(Semicolon) END END
   FORMULA(DefExpr) 
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) MAKE_NODE(Null,L(1),0) END 
      PRODUCE RULE(DefineSemi) END
      PRODUCE RULE(Statement) END
      PRODUCE RULE(ExprSemi) END
   END

   FORMULA(StmExprList)
      PRODUCE MASTER RULE(DefExpr) MAKE_TREE(AddToList) PARAM(MAKE_YACC(AddToList), 0x03) END
      PRODUCE RULE(DefExpr) MAKE_TREE(AddToList) MAKE_NODE(Statements, L(0, 1), 0) END
   END

   FORMULA(StmExpr)
      PRODUCE RULE(StmExprList) MAKE_CODE(EndBlock) END
   END

   FORMULA(DefFAV) 
      PRODUCE SYM(Semicolon) MAKE_TREE(NodeNull) MAKE_NODE(Null,L(1),0) END 
      PRODUCE RULE(DefFuncDefine) END
   END

   FORMULA(DefinesList)
      PRODUCE MASTER RULE(DefFAV) MAKE_TREE(AddToList) PARAM(MAKE_YACC(AddToList),0x03) END
      PRODUCE RULE(DefFAV) PARAM(MAKE_TREE(BegStmExprLR),0x01) MAKE_NODE(Statements,L(0,1),0) END
   END

   FORMULA(Defines)
      PRODUCE MAKE_CODE(BegStmExprLR) RULE(DefinesList) MAKE_CODE(EndBlock) END
   END
