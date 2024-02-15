#define MAKE_CALL(M,S,P) { GSymbol item(GSymbol::gsMaker,SNode::st##M,P,T_Step::ts##S,GSymbol::Call | (0x01 << 24)); rule->Add(item); }

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

   FORMULA(DefParVarInit)
      PRODUCE OPER(Assign) RULE(Assign) MAKE_CALL(DefVar,DefVarAssign,1) END
      EMPTY 
   END

   FORMULA(DefParVar)
      PRODUCE GROUP(DefVar) MAKE_YACC(DefType) LEX(Ident) MAKE_CALL(DefVar,Begin,1) RULE(DefParVarInit) MAKE_CALL(DefVar,End,1) MAKE_NODE(DefVar,L(2,1),0) END
   END

   FORMULA(DefParArrInit)
      PRODUCE OPER(Assign) RULE(Assign) MAKE_CALL(DefArr,DefArrAssign,1) END
      EMPTY 
   END

   FORMULA(DefParArr)
      PRODUCE GROUP(DefArr) MAKE_YACC(DefType) GROUP(IdentArr) MAKE_CALL(DefArr,Begin,1) RULE(DefArrDA) MAKE_NODE(DefArr,L(3,0,1),0) RULE(DefParArrInit) MAKE_CALL(DefArr,End,1) MAKE_NODE(DefArr,L(1,2),2) END
   END

   FORMULA(DefPar) 
      PRODUCE RULE(DefParArr) END
      PRODUCE RULE(DefParVar) END
   END

   FORMULA(DefParItem)
      PRODUCE RULE(DefPar) END
   END

   FORMULA(DefParList)
      PRODUCE SYM(Comma) RULE(DefParItem) MAKE_CALL(List, Append, 0) PARAM(MAKE_YACC(AddToList),0x06) MASTER END
      EMPTY 
   END

   FORMULA(DefParams)
      PRODUCE MAKE_CALL(Define,Begin,1) RULE(DefParItem) MAKE_CALL(List, Append, 0) MAKE_NODE(Define,L(1,2),1) RULE(DefParList) MAKE_CALL(Define,End,1) END
   END

   FORMULA(BodyFunc)
      PRODUCE SYM(Semicolon) END
      PRODUCE GROUP(EmptyCramp) MAKE_CALL(Null, Create, 0) MAKE_NODE(Null,L(1),0) END
      PRODUCE SYM(LeftCramp) RULE(StmExpr) MAKE_NODE(Copy,L(1),0) SYM(RightCramp) END
   END

   FORMULA(DefParam)
      PRODUCE GROUP(EmptyBracket) MAKE_CALL(DefFunc,Param,0) END
      PRODUCE SYM(LeftBracket) RULE(DefParams) MAKE_CALL(DefFunc,Param,1) MAKE_NODE(Copy, L(1), 0) SYM(RightBracket) END
   END

   FORMULA(DefFunc)
      PRODUCE GROUP(DefFunc) MAKE_CALL(DefFunc,Begin,0) MAKE_NODE(DefFunc,L(0),0) GROUP(IdentFunc) MAKE_NODE(DefFunc,L(0),1) MAKE_CALL(DefFunc,FuncIdent,0) RULE(DefParam) MAKE_NODE(DefFunc,L(0),2) RULE(BodyFunc) MAKE_CALL(DefFunc,Body,0) MAKE_CALL(DefFunc,End,0) MAKE_NODE(DefFunc,L(0),3) END
   END

   FORMULA(AInitialList)
      PRODUCE SYM(Comma) RULE(AInitItem) PARAM(MAKE_YACC(AddToList), 0x06) MASTER END
      EMPTY
   END
  
   FORMULA(AInitial)
      PRODUCE RULE(AInitItem) PARAM(MAKE_YACC(AddToList),0x06) RULE(AInitialList) END
   END

   FORMULA(Initializer)
      PRODUCE GROUP(EmptyCramp) MAKE_CALL(List,Begin,0) MAKE_CALL(List,End,0) MAKE_NODE(List,L(0),0) END
      PRODUCE SYM(LeftCramp) MAKE_CALL(List,Begin,0) MAKE_NODE(List,L(0,2),0) RULE(AInitial) MAKE_CALL(List,End,0) SYM(RightCramp) END
   END

   FORMULA(AInitItem)
      PRODUCE RULE(Initializer) END
      PRODUCE RULE(Assign) END
   END

   FORMULA(DefAInit)
      PRODUCE OPER(Assign) RULE(Initializer) MAKE_CALL(DefArr,DefArrAssign,0) END 
      EMPTY
   END

   FORMULA(DRanges)
      PRODUCE SYM(LeftScrape) RULE(Assign) PARAM(MAKE_YACC(AddToList),0x0A) SYM(RightScrape) MASTER END
      EMPTY
   END

   FORMULA(DefArrD1A) 
      PRODUCE GROUP(EmptyScrape) MAKE_CALL(Null, Create, 0) MAKE_NODE(Ranges,L(0),5) END // Null
      PRODUCE SYM(LeftScrape) RULE(Assign) MAKE_NODE(Ranges,L(1),2) SYM(RightScrape) END // create
   END

   FORMULA(DefArrDA)
      PRODUCE MAKE_CALL(List,Begin,0) RULE(DefArrD1A) MAKE_NODE(Copy,L(1,2),0) RULE(DRanges) MAKE_CALL(List,End,0) END
   END

   FORMULA(DefArr)
      PRODUCE GROUP(IdentArr) MAKE_CALL(DefArr,Begin,0) RULE(DefArrDA) MAKE_CALL(DefArr,DefArrRanges,0) MAKE_NODE(DefArr,L(0,0,1),0) RULE(DefAInit) MAKE_CALL(DefArr,End,0) MAKE_NODE(DefArr,L(1,2),2) END
   END

   FORMULA(DefVarInit) 
      PRODUCE OPER(Assign) RULE(Assign) MAKE_CALL(DefVar,DefVarAssign,0) END
      EMPTY 
   END

   FORMULA(DefVar)
      PRODUCE LEX(Ident) MAKE_CALL(DefVar,Begin,0) RULE(DefVarInit) MAKE_CALL(DefVar,End,0) MAKE_NODE(DefVar,L(0,1),0) END
   END

   FORMULA(DefIAV) 
      PRODUCE RULE(DefArr) END
      PRODUCE RULE(DefVar) END
   END

   FORMULA(DefItem) 
      PRODUCE PRIOR(And) RULE(DefIAV) MAKE_CALL(RefDef,,0) MAKE_NODE(RefDef, L(1), 0) END
      PRODUCE RULE(DefIAV) END
   END

   FORMULA(DefType) 
      PRODUCE GROUP(DefArr) END
      PRODUCE GROUP(DefVar) END
   END

   FORMULA(DefineList)
      PRODUCE SYM(Comma) RULE(DefItem) MAKE_CALL(List, Append, 0) PARAM(MAKE_YACC(AddToList),0x06) MASTER END
      EMPTY 
   END

   FORMULA(Define)
      PRODUCE RULE(DefType) MAKE_CALL(Define,Begin,0) MAKE_NODE(Define,L(4),0) RULE(DefItem) MAKE_CALL(List, Append, 0) PARAM(MAKE_YACC(AddToList),0x02) RULE(DefineList) MAKE_CALL(Define,End,0) MAKE_NODE(Define,L(0),2) END
   END

   FORMULA(ConditionDef)
      PRODUCE PRIOR(And) RULE(DefVar) MAKE_CALL(RefDef,,0) MAKE_NODE(RefDef, L(1), 0) END
      PRODUCE RULE(DefVar) END
   END

   FORMULA(Condition)
      PRODUCE GROUP(DefVar) MAKE_TREE(Define) RULE(ConditionDef) MAKE_TREE(PushDef) MAKE_NODE(Copy,L(1),0) END
      PRODUCE EXPRESSION(Condition) END
   END

   FORMULA(ExprList)
      PRODUCE SYM(Comma) RULE(Assign) PARAM(MAKE_YACC(AddToList),0x06) MASTER END
      EMPTY 
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
      PRODUCE RULE(PriorAssign) MAKE_CALL(Binary,Begin,0) MAKE_NODE(Copy,L(2),2) RULE(Assign) MAKE_CALL(Binary,End,0) MAKE_NODE(Binary,L(2,1),0) END
      EMPTY 
   END
   
   FORMULA(Assign)
      PRODUCE RULE(Question) MAKE_NODE(Copy,L(1,2),0) RULE(AssignList) END
   END

   FORMULA(QuestionList)  
      PRODUCE PRIOR(Question) MAKE_CALL(Trio,Begin,0) EXPRESSION(Value) MAKE_NODE(Trio,L(0),0) SYM(Colon) RULE(Question) MAKE_NODE(Trio,L(0),1) MAKE_CALL(Trio,End,0) END
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
      PRODUCE PRIOR(IncDec) MAKE_CALL(Unary,UnaryIncDec,0) MAKE_NODE(Unary,L(2),1) END
      EMPTY
   END

   FORMULA(Unary)
      PRODUCE PRIOR(Unary)      MAKE_CALL(Unary,Begin,0) RULE(Unary) MAKE_CALL(Unary,End,0) MAKE_NODE(Unary,L(1,2),0) END
      PRODUCE PRIOR(Term)       MAKE_CALL(Unary,Begin,1) RULE(Unary) MAKE_CALL(Unary,End,0) MAKE_NODE(Unary,L(1,2),1) END
      PRODUCE PRIOR(IncDec)     MAKE_CALL(Unary,Begin,0) RULE(Unary) MAKE_CALL(Unary,End,0) MAKE_NODE(Unary,L(1,2),0) END
      PRODUCE GROUP(CastUnary)  MAKE_CALL(Cast, Begin, 0)   RULE(Unary) MAKE_CALL(Cast,End,0) MAKE_NODE(Cast,L(1,2),0) END
      PRODUCE RULE(PrimaryExpr) MAKE_NODE(Copy,L(1,2),0)    RULE(UnaryIncDec) END 
   END

   FORMULA(Primary) 
      PRODUCE SYM(LeftBracket) EXPRESSION(None) MAKE_NODE(Copy,L(1),0) SYM(RightBracket) END //MAKE_CALL(Primary,,0) END
   END

   FORMULA(PrimaryExpr) 
      PRODUCE LEX(Integer) MAKE_CALL(Number,,0) MAKE_NODE(Number,L(1),0) END
      PRODUCE LEX(Number)  MAKE_CALL(Number,,0) MAKE_NODE(Number,L(1),0) END
      PRODUCE GROUP(IdentArr)  MAKE_CALL(Index, Begin, 0) RULE(Ranges) MAKE_CALL(Index, End, 0) MAKE_NODE(Index,L(1),0) END
      PRODUCE GROUP(IdentFunc) MAKE_CALL(Call, Begin, 0) RULE(CallParams) MAKE_CALL(Call, End, 0) MAKE_NODE(Call,L(1),0) END
      PRODUCE GROUP(Cast)  MAKE_CALL(Cast, Begin, 0) RULE(Primary) MAKE_CALL(Cast,End,0) MAKE_NODE(Cast,L(1),0) END
      PRODUCE LEX(Ident)   MAKE_CALL(Var,,0)   MAKE_NODE(Var,L(1),0) END
      PRODUCE RULE(Primary) END
   END

   FORMULA(RangesList)
      PRODUCE SYM(LeftScrape) EXPRESSION(Value) MAKE_CALL(List, Append, 0) PARAM(MAKE_YACC(AddToList),0x0A) SYM(RightScrape) MASTER END 
      EMPTY
   END

   FORMULA(Ranges)
      PRODUCE MAKE_CALL(List,Begin,0) MAKE_NODE(List,L(2,3),0) RULE(RangesList) MAKE_CALL(List,End,0) END
   END

   FORMULA(CallParams) 
      PRODUCE GROUP(EmptyBracket) MAKE_CALL(List, Empty, 0) END //) MAKE_NODE(List,L(0),0) END
      PRODUCE SYM(LeftBracket) EXPRESSION(ValueList) MAKE_NODE(Copy,L(1),0) SYM(RightBracket) END
   END

   FORMULA(CompaundStmnt)
      PRODUCE GROUP(EmptyCramp) MAKE_CALL(Null, Create, 0) MAKE_NODE(Null,L(1),0) END
      PRODUCE SYM(LeftCramp) MAKE_CALL(Statements, Begin, 0) RULE(StmExpr) MAKE_NODE(Copy,L(1),0) MAKE_CALL(Statements, End, 0) SYM(RightCramp) END
   END

   FORMULA(IfStmnt_)
      PRODUCE WARNING WORD(Else) RULE(DefExpr) END
      PRODUCE WARNING MAKE_CALL(Null, Empty, 0) END
   END

   FORMULA(IfStmnt)
      PRODUCE WORD(If) SYM(LeftBracket) MAKE_CALL(If,Begin,0) MAKE_NODE(If, L(0), -1) RULE(Condition) MAKE_CALL(If,Condition,0) MAKE_NODE(If,L(1),0) SYM(RightBracket) RULE(DefExpr) MAKE_CALL(If,IfThen,0) MAKE_NODE(If,L(1),1) RULE(IfStmnt_) MAKE_CALL(If,IfElse,0) MAKE_NODE(If,L(1),2) END
   END 

   FORMULA(ForPrefix) // prefix
      PRODUCE SYM(Semicolon) MAKE_CALL(Null, Empty, 0) MAKE_NODE(Null, L(1), 0) END
      PRODUCE RULE(DefineSemi) END
      PRODUCE RULE(ExprSemi) END
   END

   FORMULA(ForCondition) // condition
      PRODUCE SYM(Semicolon) MAKE_CALL(Null, Empty, 0) MAKE_NODE(Null, L(1), 0) END
      PRODUCE RULE(Condition) MAKE_NODE(Copy, L(1), 0) SYM(Semicolon) END
   END

   FORMULA(ForPosfix) // postfix
      PRODUCE SYM(RightBracket) MAKE_CALL(Null, Empty, 0) MAKE_NODE(Null, L(1), 0) END
      PRODUCE EXPRESSION(Expression) MAKE_NODE(Copy, L(1), 0) SYM(RightBracket) END
   END

   FORMULA(ForStmnt)
      PRODUCE WORD(For) SYM(LeftBracket) MAKE_CALL(For, Begin,0) MAKE_NODE(For, L(0), -1) RULE(ForPrefix) MAKE_NODE(For,L(1),0) RULE(ForCondition) MAKE_NODE(For,L(1),1) RULE(ForPosfix) MAKE_NODE(For,L(1),2) MAKE_CALL(For,ForTitle,0) RULE(DefExpr) MAKE_NODE(For,L(1),3) MAKE_CALL(For,Body,0) MAKE_NODE(For, L(0), -2) MAKE_CALL(For,End,0) END // body
   END 

   FORMULA(DoStmnt) 
      PRODUCE WORD(Do) MAKE_CALL(Do,Begin,0) MAKE_NODE(Do,L(0),-1) RULE(DefExpr) MAKE_CALL(Do,Body,0) MAKE_NODE(Do,L(1),1) WORD(While) SYM(LeftBracket) RULE(Condition) MAKE_NODE(Do,L(1),0) MAKE_CALL(Do,Condition,0) SYM(RightBracket) MAKE_NODE(Do,L(0),-2) MAKE_CALL(Do,End,0) SYM(Semicolon) END
   END 
   FORMULA(WhileStmnt) 
      PRODUCE WORD(While) MAKE_NODE(While,L(0),-1) MAKE_CALL(While,Begin,0) SYM(LeftBracket) RULE(Condition) MAKE_CALL(While,Condition,0) MAKE_NODE(While,L(1),0) SYM(RightBracket) RULE(DefExpr) MAKE_CALL(While,Body,0) MAKE_NODE(While,L(1),1) MAKE_NODE(While,L(0),-2) MAKE_CALL(While,End,0) END
   END 

/*
   FORMULA(SwitchStmnt) 
      PRODUCE WORD(Switch) SYM(LeftBracket) SYM(RightBracket) END 
   END
*/
   FORMULA(GoToStmnt) 
      PRODUCE WORD(GoTo) LEX(Ident) SYM(Semicolon) MAKE_CALL(GoTo,,0) MAKE_NODE(GoTo,L(1),0) END
   END

   FORMULA(BreakStmnt) 
      PRODUCE WORD(Break) SYM(Semicolon) MAKE_CALL(Break,,0) MAKE_NODE(Break,L(1),0) END 
   END

   FORMULA(ContinueStmnt) 
      PRODUCE WORD(Continue) SYM(Semicolon) MAKE_CALL(Continue,,0) MAKE_NODE(Continue,L(1),0) END 
   END

   FORMULA(ReturnVal)
      PRODUCE EXPRESSION(Value) END
      PRODUCE MAKE_CALL(Null, Empty, 0) END
   END

   FORMULA(ReturnStmnt)
      PRODUCE WORD(Return) MAKE_CALL(Return, Begin, 0) RULE(ReturnVal) MAKE_CALL(Return, End, 0) MAKE_NODE(Return,L(1),0) SYM(Semicolon) END
   END 

   FORMULA(Statement) 
//      PRODUCE GROUP(Label) SYM(Colon) RULE(DefExpr) MAKE_NODE(Label,L(1),0) MAKE_TREE(Label) END
      PRODUCE GROUP(Label) SYM(Colon) MAKE_CALL(Label, , 0) MAKE_NODE(Label, L(1), 0) END
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
      PRODUCE SYM(Semicolon) MAKE_CALL(Null, Create, 0) MAKE_NODE(Null,L(1),0) END 
      PRODUCE RULE(DefineSemi) END
      PRODUCE RULE(Statement) END
      PRODUCE RULE(ExprSemi) END
   END

   FORMULA(StmExprList)
      PRODUCE RULE(DefExpr) PARAM(MAKE_YACC(AddToList),0x06) MASTER END
      EMPTY
   END 

   FORMULA(StmExpr) 
      PRODUCE MAKE_CALL(Statements, Begin, 0) MAKE_NODE(Statements,L(2),0) RULE(StmExprList) MAKE_CALL(Statements, End, 0) MAKE_NODE(Statements,L(0),-2) END
   END

   FORMULA(DefFAV) 
      PRODUCE SYM(Semicolon) MAKE_CALL(Null, Create, 0) MAKE_NODE(Null,L(1),0) END 
      PRODUCE RULE(DefFunc) END
      PRODUCE RULE(DefineSemi) END
   END

   FORMULA(DefinesList)
      PRODUCE RULE(DefFAV) MAKE_CALL(List, Append, 0) PARAM(MAKE_YACC(AddToList),0x06) MASTER END
      EMPTY
   END 

   FORMULA(Defines)
      PRODUCE MAKE_CALL(Statements, Begin, 0) MAKE_NODE(Statements,L(2),0) RULE(DefinesList) MAKE_CALL(Statements, End, 0) MAKE_NODE(Statements,L(0),-2) END
   END
