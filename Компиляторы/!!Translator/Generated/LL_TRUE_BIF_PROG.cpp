
// -------------------- BIF_S_ --------------------
int PSyntax::BIF_S__0()
{
   PRODUCE(S_,0)
   int s_ret;
   if ((s_ret = BIF_Program()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF_S_()
{
   FORMULA(S_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_S__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_Program --------------------
int PSyntax::BIF_Program_0()
{
   PRODUCE(Program,0)
   int s_ret;
   MAKE(BegStmExprLL);
   if ((s_ret = BIF__f_00002_()) <= 0) RETURN (s_ret);
   MAKE_CODE(EndBlock);
   RETURN (1);
}
int PSyntax::BIF_Program()
{
   FORMULA(Program)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Program_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00002_ --------------------
int PSyntax::BIF__f_00002__0()
{
   PRODUCE(_f_00002_,0)
   int s_ret;
   if ((s_ret = BIF__f_00003_()) <= 0) RETURN (s_ret);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::BIF__f_00002_()
{
   FORMULA(_f_00002_)
   int p_ret;
   while ((p_ret = BIF__f_00002__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF__f_00003_ --------------------
int PSyntax::BIF__f_00003__0()
{
   PRODUCE(_f_00003_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE_TREE(NodeNull);
   RETURN (1);
}
int PSyntax::BIF__f_00003__1()
{
   PRODUCE(_f_00003_,1)
   if (!Match(T_Lexeme::T_Syntax::sxDefFunc)) RETURN (-1);
   if (!Match(T_Lexeme::T_Syntax::sxIdentFunc)) RETURN (0);
   MAKE(FuncIdent);
   if (BIF__f_00004_() <= 0) RETURN (0);
   if (BIF__f_00006_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00003__2()
{
   PRODUCE(_f_00003_,2)
   int s_ret;
   if ((s_ret = BIF_DefineSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF__f_00003_()
{
   FORMULA(_f_00003_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00003__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00003__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00003__2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -3) ? -1 : 0);
}

// -------------------- BIF__f_00004_ --------------------
int PSyntax::BIF__f_00004__0()
{
   PRODUCE(_f_00004_,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyBracket)) RETURN (-1);
   PARAM_TREE(EndParams,2);
   RETURN (1);
}
int PSyntax::BIF__f_00004__1()
{
   PRODUCE(_f_00004_,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (-1);
   PARAM_TREE(Define,2);
   if (BIF_DefParItem() <= 0) RETURN (0);
   if (BIF__f_00005_() <= 0) RETURN (0);
   MAKE_TREE(EndParams);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00004_()
{
   FORMULA(_f_00004_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00004__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00004__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00005_ --------------------
int PSyntax::BIF__f_00005__0()
{
   PRODUCE(_f_00005_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (BIF_DefParItem() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00005_()
{
   FORMULA(_f_00005_)
   int p_ret;
   while ((p_ret = BIF__f_00005__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF__f_00006_ --------------------
int PSyntax::BIF__f_00006__0()
{
   PRODUCE(_f_00006_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE(BodyFunc);
   RETURN (1);
}
int PSyntax::BIF__f_00006__1()
{
   PRODUCE(_f_00006_,1)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) RETURN (-1);
   PARAM(BodyFunc,1);
   RETURN (1);
}
int PSyntax::BIF__f_00006__2()
{
   PRODUCE(_f_00006_,2)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) RETURN (-1);
   MAKE_CODE(EndParams);
   if (BIF_StmExpr() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) RETURN (0);
   PARAM(BodyFunc,2);
   RETURN (1);
}
int PSyntax::BIF__f_00006_()
{
   FORMULA(_f_00006_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00006__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00006__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00006__2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -3) ? -1 : 0);
}

// -------------------- BIF_DefParInit --------------------
int PSyntax::BIF_DefParInit_0()
{
   PRODUCE(DefParInit,0)
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) RETURN (-1);
   MAKE_CODE(BegParVarAssign);
   if (BIF_Assign() <= 0) RETURN (0);
   MAKE(ParVarAssign);
   RETURN (1);
}
int PSyntax::BIF_DefParInit()
{
   FORMULA(DefParInit)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefParInit_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? 1 : 0);
}

// -------------------- BIF_DefParItem --------------------
int PSyntax::BIF_DefParItem_0()
{
   PRODUCE(DefParItem,0)
   int s_ret;
   if ((s_ret = BIF__f_00009_()) <= 0) RETURN (s_ret);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::BIF_DefParItem()
{
   FORMULA(DefParItem)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefParItem_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00009_ --------------------
int PSyntax::BIF__f_00009__0()
{
   PRODUCE(_f_00009_,0)
   if (!Match(T_Lexeme::T_Syntax::sxDefArr)) RETURN (-1);
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) RETURN (0);
   MAKE(DefParArr);
   if (BIF_DefArrDA() <= 0) RETURN (0);
   if (BIF_DefParInit() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00009__1()
{
   PRODUCE(_f_00009_,1)
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) RETURN (-1);
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (0);
   MAKE(DefParVar);
   if (BIF_DefParInit() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00009_()
{
   FORMULA(_f_00009_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00009__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00009__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF_Initializer --------------------
int PSyntax::BIF_Initializer_0()
{
   PRODUCE(Initializer,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) RETURN (-1);
   MAKE_CODE(BegInitial);
   MAKE_TREE(NodeListLL);
   RETURN (1);
}
int PSyntax::BIF_Initializer_1()
{
   PRODUCE(Initializer,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) RETURN (-1);
   PARAM_CODE(BegInitial,1);
   MAKE_TREE(NodeListLL);
   if (BIF_AInitItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   if (BIF__f_00011_() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) RETURN (0);
   MAKE_CODE(EndInitial);
   RETURN (1);
}
int PSyntax::BIF_Initializer()
{
   FORMULA(Initializer)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Initializer_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_Initializer_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00011_ --------------------
int PSyntax::BIF__f_00011__0()
{
   PRODUCE(_f_00011_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (BIF_AInitItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::BIF__f_00011_()
{
   FORMULA(_f_00011_)
   int p_ret;
   while ((p_ret = BIF__f_00011__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_AInitItem --------------------
int PSyntax::BIF_AInitItem_0()
{
   PRODUCE(AInitItem,0)
   int s_ret;
   if ((s_ret = BIF_Initializer()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF_AInitItem_1()
{
   PRODUCE(AInitItem,1)
   int s_ret;
   if ((s_ret = BIF_Assign()) <= 0) RETURN (s_ret);
   MAKE_CODE(AInitItem);
   RETURN (1);
}
int PSyntax::BIF_AInitItem()
{
   FORMULA(AInitItem)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_AInitItem_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_AInitItem_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF_DefArrDA --------------------
int PSyntax::BIF_DefArrDA_0()
{
   PRODUCE(DefArrDA,0)
   int s_ret;
   if ((s_ret = BIF__f_00014_()) <= 0) RETURN (s_ret);
   if (BIF__f_00015_() <= 0) RETURN (0);
   MAKE_CODE(EndRanges);
   RETURN (1);
}
int PSyntax::BIF_DefArrDA()
{
   FORMULA(DefArrDA)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefArrDA_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00014_ --------------------
int PSyntax::BIF__f_00014__0()
{
   PRODUCE(_f_00014_,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyScrape)) RETURN (-1);
   MAKE(DefArrD1AEmpty);
   RETURN (1);
}
int PSyntax::BIF__f_00014__1()
{
   PRODUCE(_f_00014_,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) RETURN (-1);
   if (BIF_Assign() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) RETURN (0);
   MAKE(DRange);
   RETURN (1);
}
int PSyntax::BIF__f_00014_()
{
   FORMULA(_f_00014_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00014__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00014__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00015_ --------------------
int PSyntax::BIF__f_00015__0()
{
   PRODUCE(_f_00015_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) RETURN (-1);
   if (BIF_Assign() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) RETURN (0);
   MAKE(DRange);
   RETURN (1);
}
int PSyntax::BIF__f_00015_()
{
   FORMULA(_f_00015_)
   int p_ret;
   while ((p_ret = BIF__f_00015__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_DefVar --------------------
int PSyntax::BIF_DefVar_0()
{
   PRODUCE(DefVar,0)
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (-1);
   MAKE(DefIdent);
   if (BIF__f_00017_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_DefVar()
{
   FORMULA(DefVar)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefVar_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00017_ --------------------
int PSyntax::BIF__f_00017__0()
{
   PRODUCE(_f_00017_,0)
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) RETURN (-1);
   MAKE_CODE(BegDefVarAssign);
   if (BIF_Assign() <= 0) RETURN (0);
   MAKE(DefVarAssign);
   RETURN (1);
}
int PSyntax::BIF__f_00017_()
{
   FORMULA(_f_00017_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00017__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? 1 : 0);
}

// -------------------- BIF_DefIAV --------------------
int PSyntax::BIF_DefIAV_0()
{
   PRODUCE(DefIAV,0)
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) RETURN (-1);
   MAKE(DefArray);
   if (BIF_DefArrDA() <= 0) RETURN (0);
   if (BIF__f_00019_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_DefIAV_1()
{
   PRODUCE(DefIAV,1)
   int s_ret;
   if ((s_ret = BIF_DefVar()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF_DefIAV()
{
   FORMULA(DefIAV)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefIAV_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_DefIAV_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00019_ --------------------
int PSyntax::BIF__f_00019__0()
{
   PRODUCE(_f_00019_,0)
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) RETURN (-1);
   MAKE_CODE(BegAInit);
   if (BIF_Initializer() <= 0) RETURN (0);
   MAKE(EndAInit);
   RETURN (1);
}
int PSyntax::BIF__f_00019_()
{
   FORMULA(_f_00019_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00019__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? 1 : 0);
}

// -------------------- BIF_DefItem --------------------
int PSyntax::BIF_DefItem_0()
{
   PRODUCE(DefItem,0)
   if (!Match(T_Symbol::T_Priority::prAnd)) RETURN (-1);
   if (BIF_DefIAV() <= 0) RETURN (0);
   MAKE_TREE(RefDef);
   RETURN (1);
}
int PSyntax::BIF_DefItem_1()
{
   PRODUCE(DefItem,1)
   int s_ret;
   if ((s_ret = BIF_DefIAV()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF_DefItem()
{
   FORMULA(DefItem)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefItem_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_DefItem_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF_Condition --------------------
int PSyntax::BIF_Condition_0()
{
   PRODUCE(Condition,0)
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) RETURN (-1);
   MAKE(Define);
   if (BIF__f_00022_() <= 0) RETURN (0);
   MAKE(PushDef);
   RETURN (1);
}
int PSyntax::BIF_Condition_1()
{
   PRODUCE(Condition,1)
   int s_ret;
   PARAM_CODE(Part,241);
   if ((s_ret = BIF_Expressions()) <= 0) RETURN (s_ret);
   PARAM_TREE(ExpressionSLL,241);
   RETURN (1);
}
int PSyntax::BIF_Condition()
{
   FORMULA(Condition)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Condition_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_Condition_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00022_ --------------------
int PSyntax::BIF__f_00022__0()
{
   PRODUCE(_f_00022_,0)
   if (!Match(T_Symbol::T_Priority::prAnd)) RETURN (-1);
   if (BIF_DefVar() <= 0) RETURN (0);
   MAKE_TREE(RefDef);
   RETURN (1);
}
int PSyntax::BIF__f_00022__1()
{
   PRODUCE(_f_00022_,1)
   int s_ret;
   if ((s_ret = BIF_DefVar()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF__f_00022_()
{
   FORMULA(_f_00022_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00022__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00022__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF_Expressions --------------------
int PSyntax::BIF_Expressions_0()
{
   PRODUCE(Expressions,0)
   int s_ret;
   if ((s_ret = BIF_Assign()) <= 0) RETURN (s_ret);
   MAKE(ExpressionsLL);
   if (BIF__f_00024_() <= 0) RETURN (0);
   MAKE_CODE(ExpressionSLL);
   RETURN (1);
}
int PSyntax::BIF_Expressions()
{
   FORMULA(Expressions)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Expressions_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00024_ --------------------
int PSyntax::BIF__f_00024__0()
{
   PRODUCE(_f_00024_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (BIF_Assign() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   MAKE_CODE(AddToExpr);
   RETURN (1);
}
int PSyntax::BIF__f_00024_()
{
   FORMULA(_f_00024_)
   int p_ret;
   while ((p_ret = BIF__f_00024__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Assign --------------------
int PSyntax::BIF_Assign_0()
{
   PRODUCE(Assign,0)
   int s_ret;
   if ((s_ret = BIF_Question()) <= 0) RETURN (s_ret);
   if (BIF__f_00026_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_Assign()
{
   FORMULA(Assign)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Assign_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00026_ --------------------
int PSyntax::BIF__f_00026__0()
{
   PRODUCE(_f_00026_,0)
   if (!Match(T_Symbol::T_Priority::prAssign)) RETURN (-1);
   if (BIF_Assign() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::BIF__f_00026_()
{
   FORMULA(_f_00026_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00026__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? 1 : 0);
}

// -------------------- BIF_Question --------------------
int PSyntax::BIF_Question_0()
{
   PRODUCE(Question,0)
   int s_ret;
   if ((s_ret = BIF_AndAnd()) <= 0) RETURN (s_ret);
   if (BIF__f_00028_() <= 0) RETURN (0);
   if (BIF__f_00029_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_Question()
{
   FORMULA(Question)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Question_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00028_ --------------------
int PSyntax::BIF__f_00028__0()
{
   PRODUCE(_f_00028_,0)
   if (!Match(T_Symbol::T_Priority::prOrOr)) RETURN (-1);
   if (BIF_AndAnd() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::BIF__f_00028_()
{
   FORMULA(_f_00028_)
   int p_ret;
   while ((p_ret = BIF__f_00028__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF__f_00029_ --------------------
int PSyntax::BIF__f_00029__0()
{
   PRODUCE(_f_00029_,0)
   if (!Match(T_Symbol::T_Priority::prQuestion)) RETURN (-1);
   MAKE_CODE(BegQuestion);
   if (BIF_ExpressionValue() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxColon)) RETURN (0);
   MAKE_CODE(MidQuestion);
   if (BIF_Question() <= 0) RETURN (0);
   MAKE(Question);
   RETURN (1);
}
int PSyntax::BIF__f_00029_()
{
   FORMULA(_f_00029_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00029__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? 1 : 0);
}

// -------------------- BIF_AndAnd --------------------
int PSyntax::BIF_AndAnd_0()
{
   PRODUCE(AndAnd,0)
   int s_ret;
   if ((s_ret = BIF_Or()) <= 0) RETURN (s_ret);
   if (BIF__f_00031_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_AndAnd()
{
   FORMULA(AndAnd)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_AndAnd_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00031_ --------------------
int PSyntax::BIF__f_00031__0()
{
   PRODUCE(_f_00031_,0)
   if (!Match(T_Symbol::T_Priority::prAndAnd)) RETURN (-1);
   if (BIF_Or() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::BIF__f_00031_()
{
   FORMULA(_f_00031_)
   int p_ret;
   while ((p_ret = BIF__f_00031__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Or --------------------
int PSyntax::BIF_Or_0()
{
   PRODUCE(Or,0)
   int s_ret;
   if ((s_ret = BIF_XOr()) <= 0) RETURN (s_ret);
   if (BIF__f_00033_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_Or()
{
   FORMULA(Or)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Or_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00033_ --------------------
int PSyntax::BIF__f_00033__0()
{
   PRODUCE(_f_00033_,0)
   if (!Match(T_Symbol::T_Priority::prOr)) RETURN (-1);
   if (BIF_XOr() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::BIF__f_00033_()
{
   FORMULA(_f_00033_)
   int p_ret;
   while ((p_ret = BIF__f_00033__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_XOr --------------------
int PSyntax::BIF_XOr_0()
{
   PRODUCE(XOr,0)
   int s_ret;
   if ((s_ret = BIF_And()) <= 0) RETURN (s_ret);
   if (BIF__f_00035_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_XOr()
{
   FORMULA(XOr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_XOr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00035_ --------------------
int PSyntax::BIF__f_00035__0()
{
   PRODUCE(_f_00035_,0)
   if (!Match(T_Symbol::T_Priority::prXOr)) RETURN (-1);
   if (BIF_And() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::BIF__f_00035_()
{
   FORMULA(_f_00035_)
   int p_ret;
   while ((p_ret = BIF__f_00035__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_And --------------------
int PSyntax::BIF_And_0()
{
   PRODUCE(And,0)
   int s_ret;
   if ((s_ret = BIF_Equ()) <= 0) RETURN (s_ret);
   if (BIF__f_00037_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_And()
{
   FORMULA(And)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_And_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00037_ --------------------
int PSyntax::BIF__f_00037__0()
{
   PRODUCE(_f_00037_,0)
   if (!Match(T_Symbol::T_Priority::prAnd)) RETURN (-1);
   if (BIF_Equ() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::BIF__f_00037_()
{
   FORMULA(_f_00037_)
   int p_ret;
   while ((p_ret = BIF__f_00037__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Equ --------------------
int PSyntax::BIF_Equ_0()
{
   PRODUCE(Equ,0)
   int s_ret;
   if ((s_ret = BIF_Compare()) <= 0) RETURN (s_ret);
   if (BIF__f_00039_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_Equ()
{
   FORMULA(Equ)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Equ_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00039_ --------------------
int PSyntax::BIF__f_00039__0()
{
   PRODUCE(_f_00039_,0)
   if (!Match(T_Symbol::T_Priority::prEqu)) RETURN (-1);
   if (BIF_Compare() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::BIF__f_00039_()
{
   FORMULA(_f_00039_)
   int p_ret;
   while ((p_ret = BIF__f_00039__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Compare --------------------
int PSyntax::BIF_Compare_0()
{
   PRODUCE(Compare,0)
   int s_ret;
   if ((s_ret = BIF_Shift()) <= 0) RETURN (s_ret);
   if (BIF__f_00041_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_Compare()
{
   FORMULA(Compare)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Compare_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00041_ --------------------
int PSyntax::BIF__f_00041__0()
{
   PRODUCE(_f_00041_,0)
   if (!Match(T_Symbol::T_Priority::prCompare)) RETURN (-1);
   if (BIF_Shift() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::BIF__f_00041_()
{
   FORMULA(_f_00041_)
   int p_ret;
   while ((p_ret = BIF__f_00041__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Shift --------------------
int PSyntax::BIF_Shift_0()
{
   PRODUCE(Shift,0)
   int s_ret;
   if ((s_ret = BIF_Term()) <= 0) RETURN (s_ret);
   if (BIF__f_00043_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_Shift()
{
   FORMULA(Shift)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Shift_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00043_ --------------------
int PSyntax::BIF__f_00043__0()
{
   PRODUCE(_f_00043_,0)
   if (!Match(T_Symbol::T_Priority::prShift)) RETURN (-1);
   if (BIF_Term() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::BIF__f_00043_()
{
   FORMULA(_f_00043_)
   int p_ret;
   while ((p_ret = BIF__f_00043__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Term --------------------
int PSyntax::BIF_Term_0()
{
   PRODUCE(Term,0)
   int s_ret;
   if ((s_ret = BIF_Factor()) <= 0) RETURN (s_ret);
   if (BIF__f_00045_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_Term()
{
   FORMULA(Term)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Term_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00045_ --------------------
int PSyntax::BIF__f_00045__0()
{
   PRODUCE(_f_00045_,0)
   if (!Match(T_Symbol::T_Priority::prTerm)) RETURN (-1);
   if (BIF_Factor() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::BIF__f_00045_()
{
   FORMULA(_f_00045_)
   int p_ret;
   while ((p_ret = BIF__f_00045__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Factor --------------------
int PSyntax::BIF_Factor_0()
{
   PRODUCE(Factor,0)
   int s_ret;
   if ((s_ret = BIF_Unary()) <= 0) RETURN (s_ret);
   if (BIF__f_00047_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_Factor()
{
   FORMULA(Factor)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Factor_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00047_ --------------------
int PSyntax::BIF__f_00047__0()
{
   PRODUCE(_f_00047_,0)
   if (!Match(T_Symbol::T_Priority::prFactor)) RETURN (-1);
   if (BIF_Unary() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::BIF__f_00047_()
{
   FORMULA(_f_00047_)
   int p_ret;
   while ((p_ret = BIF__f_00047__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Unary --------------------
int PSyntax::BIF_Unary_0()
{
   PRODUCE(Unary,0)
   if (!Match(T_Symbol::T_Priority::prUnary)) RETURN (-1);
   if (BIF_Unary() <= 0) RETURN (0);
   MAKE(Unary);
   RETURN (1);
}
int PSyntax::BIF_Unary_1()
{
   PRODUCE(Unary,1)
   if (!Match(T_Symbol::T_Priority::prTerm)) RETURN (-1);
   if (BIF_Unary() <= 0) RETURN (0);
   MAKE(Unary);
   RETURN (1);
}
int PSyntax::BIF_Unary_2()
{
   PRODUCE(Unary,2)
   if (!Match(T_Symbol::T_Priority::prIncDec)) RETURN (-1);
   if (BIF_Unary() <= 0) RETURN (0);
   MAKE(Unary);
   RETURN (1);
}
int PSyntax::BIF_Unary_3()
{
   PRODUCE(Unary,3)
   if (!Match(T_Lexeme::T_Syntax::sxCastUnary)) RETURN (-1);
   if (BIF_Unary() <= 0) RETURN (0);
   MAKE(Cast);
   RETURN (1);
}
int PSyntax::BIF_Unary_4()
{
   PRODUCE(Unary,4)
   int s_ret;
   if ((s_ret = BIF__f_00049_()) <= 0) RETURN (s_ret);
   if (BIF__f_00052_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_Unary()
{
   FORMULA(Unary)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Unary_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_Unary_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_Unary_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_Unary_3()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_Unary_4()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -5) ? -1 : 0);
}

// -------------------- BIF__f_00049_ --------------------
int PSyntax::BIF__f_00049__0()
{
   PRODUCE(_f_00049_,0)
   if (!Match(T_Lexeme::T_Group::grInteger)) RETURN (-1);
   MAKE(Number);
   RETURN (1);
}
int PSyntax::BIF__f_00049__1()
{
   PRODUCE(_f_00049_,1)
   if (!Match(T_Lexeme::T_Group::grNumber)) RETURN (-1);
   MAKE(Number);
   RETURN (1);
}
int PSyntax::BIF__f_00049__2()
{
   PRODUCE(_f_00049_,2)
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) RETURN (-1);
   MAKE(BegIndexLL);
   if (BIF__f_00050_() <= 0) RETURN (0);
   MAKE(EndIndex);
   RETURN (1);
}
int PSyntax::BIF__f_00049__3()
{
   PRODUCE(_f_00049_,3)
   if (!Match(T_Lexeme::T_Syntax::sxIdentFunc)) RETURN (-1);
   if (BIF__f_00051_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00049__4()
{
   PRODUCE(_f_00049_,4)
   if (!Match(T_Lexeme::T_Syntax::sxCast)) RETURN (-1);
   if (BIF_Primary() <= 0) RETURN (0);
   MAKE(Cast);
   RETURN (1);
}
int PSyntax::BIF__f_00049__5()
{
   PRODUCE(_f_00049_,5)
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (-1);
   MAKE(Ident);
   RETURN (1);
}
int PSyntax::BIF__f_00049__6()
{
   PRODUCE(_f_00049_,6)
   int s_ret;
   if ((s_ret = BIF_Primary()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF__f_00049_()
{
   FORMULA(_f_00049_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00049__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00049__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00049__2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00049__3()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00049__4()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00049__5()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00049__6()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -7) ? -1 : 0);
}

// -------------------- BIF__f_00050_ --------------------
int PSyntax::BIF__f_00050__0()
{
   PRODUCE(_f_00050_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) RETURN (-1);
   if (BIF_ExpressionValue() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) RETURN (0);
   MAKE(IndexLL);
   RETURN (1);
}
int PSyntax::BIF__f_00050_()
{
   FORMULA(_f_00050_)
   int p_ret;
   while ((p_ret = BIF__f_00050__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF__f_00051_ --------------------
int PSyntax::BIF__f_00051__0()
{
   PRODUCE(_f_00051_,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyBracket)) RETURN (-1);
   MAKE(Params);
   RETURN (1);
}
int PSyntax::BIF__f_00051__1()
{
   PRODUCE(_f_00051_,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (-1);
   PARAM_CODE(Part,512);
   if (BIF_Expressions() <= 0) RETURN (0);
   PARAM_TREE(ExpressionSLL,512);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   PARAM(Params,1);
   RETURN (1);
}
int PSyntax::BIF__f_00051_()
{
   FORMULA(_f_00051_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00051__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00051__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00052_ --------------------
int PSyntax::BIF__f_00052__0()
{
   PRODUCE(_f_00052_,0)
   if (!Match(T_Symbol::T_Priority::prIncDec)) RETURN (-1);
   MAKE(IncDec);
   RETURN (1);
}
int PSyntax::BIF__f_00052_()
{
   FORMULA(_f_00052_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00052__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? 1 : 0);
}

// -------------------- BIF_Primary --------------------
int PSyntax::BIF_Primary_0()
{
   PRODUCE(Primary,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (-1);
   MAKE_CODE(Part);
   if (BIF_Expressions() <= 0) RETURN (0);
   MAKE_TREE(ExpressionSLL);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   MAKE_TREE(Primary);
   RETURN (1);
}
int PSyntax::BIF_Primary()
{
   FORMULA(Primary)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Primary_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_DefineSemi --------------------
int PSyntax::BIF_DefineSemi_0()
{
   PRODUCE(DefineSemi,0)
   int s_ret;
   if ((s_ret = BIF__f_00055_()) <= 0) RETURN (s_ret);
   MAKE(Define);
   if (BIF_DefItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   if (BIF__f_00056_() <= 0) RETURN (0);
   MAKE_CODE(EndDefine);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_DefineSemi()
{
   FORMULA(DefineSemi)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefineSemi_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00055_ --------------------
int PSyntax::BIF__f_00055__0()
{
   PRODUCE(_f_00055_,0)
   if (!Match(T_Lexeme::T_Syntax::sxDefArr)) RETURN (-1);
   RETURN (1);
}
int PSyntax::BIF__f_00055__1()
{
   PRODUCE(_f_00055_,1)
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) RETURN (-1);
   RETURN (1);
}
int PSyntax::BIF__f_00055_()
{
   FORMULA(_f_00055_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00055__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00055__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00056_ --------------------
int PSyntax::BIF__f_00056__0()
{
   PRODUCE(_f_00056_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (BIF_DefItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::BIF__f_00056_()
{
   FORMULA(_f_00056_)
   int p_ret;
   while ((p_ret = BIF__f_00056__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_ExprSemi --------------------
int PSyntax::BIF_ExprSemi_0()
{
   PRODUCE(ExprSemi,0)
   int s_ret;
   if ((s_ret = BIF_ExpressionExpression()) <= 0) RETURN (s_ret);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_ExprSemi()
{
   FORMULA(ExprSemi)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_ExprSemi_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_DefExpr --------------------
int PSyntax::BIF_DefExpr_0()
{
   PRODUCE(DefExpr,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE_TREE(NodeNull);
   RETURN (1);
}
int PSyntax::BIF_DefExpr_1()
{
   PRODUCE(DefExpr,1)
   int s_ret;
   if ((s_ret = BIF_DefineSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF_DefExpr_2()
{
   PRODUCE(DefExpr,2)
   int s_ret;
   if ((s_ret = BIF__f_00059_()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF_DefExpr_3()
{
   PRODUCE(DefExpr,3)
   int s_ret;
   if ((s_ret = BIF_ExprSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF_DefExpr()
{
   FORMULA(DefExpr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefExpr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_DefExpr_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_DefExpr_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_DefExpr_3()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -4) ? -1 : 0);
}

// -------------------- BIF__f_00059_ --------------------
int PSyntax::BIF__f_00059__0()
{
   PRODUCE(_f_00059_,0)
   if (!Match(T_Lexeme::T_Syntax::sxLabel)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxColon)) RETURN (0);
   MAKE_CODE(Label);
   if (BIF_DefExpr() <= 0) RETURN (0);
   MAKE_TREE(Label);
   RETURN (1);
}
int PSyntax::BIF__f_00059__1()
{
   PRODUCE(_f_00059_,1)
   if (!Match(T_Lexeme::W_Type::rwIf)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   MAKE_CODE(BegIf);
   if (BIF_Condition() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   MAKE_CODE(Then);
   if (BIF_DefExpr() <= 0) RETURN (0);
   if (BIF__f_00060_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00059__2()
{
   PRODUCE(_f_00059_,2)
   if (!Match(T_Lexeme::W_Type::rwDo)) RETURN (-1);
   MAKE(BegDo);
   if (BIF_DefExpr() <= 0) RETURN (0);
   if (!Match(T_Lexeme::W_Type::rwWhile)) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   MAKE_CODE(MidDo);
   if (BIF_Condition() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(Do);
   RETURN (1);
}
int PSyntax::BIF__f_00059__3()
{
   PRODUCE(_f_00059_,3)
   if (!Match(T_Lexeme::W_Type::rwWhile)) RETURN (-1);
   MAKE(BegWhile);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   if (BIF_Condition() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   MAKE_CODE(MidWhile);
   if (BIF_DefExpr() <= 0) RETURN (0);
   MAKE(While);
   RETURN (1);
}
int PSyntax::BIF__f_00059__4()
{
   PRODUCE(_f_00059_,4)
   if (!Match(T_Lexeme::W_Type::rwFor)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   MAKE(BegFor);
   if (BIF__f_00061_() <= 0) RETURN (0);
   MAKE_CODE(PrefFor);
   if (BIF__f_00062_() <= 0) RETURN (0);
   MAKE_CODE(ConditionFor);
   if (BIF__f_00063_() <= 0) RETURN (0);
   MAKE_CODE(PostFor);
   if (BIF_DefExpr() <= 0) RETURN (0);
   MAKE(For);
   RETURN (1);
}
int PSyntax::BIF__f_00059__5()
{
   PRODUCE(_f_00059_,5)
   if (!Match(T_Lexeme::W_Type::rwGoTo)) RETURN (-1);
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(GoTo);
   RETURN (1);
}
int PSyntax::BIF__f_00059__6()
{
   PRODUCE(_f_00059_,6)
   if (!Match(T_Lexeme::W_Type::rwBreak)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(Break);
   RETURN (1);
}
int PSyntax::BIF__f_00059__7()
{
   PRODUCE(_f_00059_,7)
   if (!Match(T_Lexeme::W_Type::rwContinue)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(Continue);
   RETURN (1);
}
int PSyntax::BIF__f_00059__8()
{
   PRODUCE(_f_00059_,8)
   if (!Match(T_Lexeme::W_Type::rwReturn)) RETURN (-1);
   if (BIF__f_00064_() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00059__9()
{
   PRODUCE(_f_00059_,9)
   int s_ret;
   if ((s_ret = BIF__f_00065_()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF__f_00059_()
{
   FORMULA(_f_00059_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00059__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00059__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00059__2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00059__3()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00059__4()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00059__5()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00059__6()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00059__7()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00059__8()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00059__9()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -10) ? -1 : 0);
}

// -------------------- BIF__f_00060_ --------------------
int PSyntax::BIF__f_00060__0()
{
   PRODUCE(_f_00060_,0)
   if (!Match(T_Lexeme::W_Type::rwElse)) RETURN (-1);
   MAKE_CODE(Else);
   if (BIF_DefExpr() <= 0) RETURN (0);
   PARAM(If,1);
   RETURN (1);
}
int PSyntax::BIF__f_00060__1()
{
   PRODUCE(_f_00060_,1)
   MAKE(If);
   RETURN (1);
}
int PSyntax::BIF__f_00060_()
{
   FORMULA(_f_00060_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00060__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00060__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00061_ --------------------
int PSyntax::BIF__f_00061__0()
{
   PRODUCE(_f_00061_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE_TREE(NodeNull);
   RETURN (1);
}
int PSyntax::BIF__f_00061__1()
{
   PRODUCE(_f_00061_,1)
   int s_ret;
   if ((s_ret = BIF_DefineSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF__f_00061__2()
{
   PRODUCE(_f_00061_,2)
   int s_ret;
   if ((s_ret = BIF_ExprSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF__f_00061_()
{
   FORMULA(_f_00061_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00061__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00061__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00061__2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -3) ? -1 : 0);
}

// -------------------- BIF__f_00062_ --------------------
int PSyntax::BIF__f_00062__0()
{
   PRODUCE(_f_00062_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE(NodeNull);
   RETURN (1);
}
int PSyntax::BIF__f_00062__1()
{
   PRODUCE(_f_00062_,1)
   int s_ret;
   if ((s_ret = BIF_Condition()) <= 0) RETURN (s_ret);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00062_()
{
   FORMULA(_f_00062_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00062__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00062__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00063_ --------------------
int PSyntax::BIF__f_00063__0()
{
   PRODUCE(_f_00063_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (-1);
   MAKE_TREE(NodeNull);
   RETURN (1);
}
int PSyntax::BIF__f_00063__1()
{
   PRODUCE(_f_00063_,1)
   int s_ret;
   if ((s_ret = BIF_ExpressionExpression()) <= 0) RETURN (s_ret);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00063_()
{
   FORMULA(_f_00063_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00063__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00063__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00064_ --------------------
int PSyntax::BIF__f_00064__0()
{
   PRODUCE(_f_00064_,0)
   int s_ret;
   if ((s_ret = BIF_ExpressionValue()) <= 0) RETURN (s_ret);
   PARAM(Return,1);
   RETURN (1);
}
int PSyntax::BIF__f_00064__1()
{
   PRODUCE(_f_00064_,1)
   MAKE(Return);
   RETURN (1);
}
int PSyntax::BIF__f_00064_()
{
   FORMULA(_f_00064_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00064__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00064__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00065_ --------------------
int PSyntax::BIF__f_00065__0()
{
   PRODUCE(_f_00065_,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) RETURN (-1);
   MAKE(Compaund);
   MAKE_CODE(EndBlock);
   RETURN (1);
}
int PSyntax::BIF__f_00065__1()
{
   PRODUCE(_f_00065_,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) RETURN (-1);
   MAKE(Compaund);
   if (BIF_StmExpr() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) RETURN (0);
   MAKE_CODE(EndBlock);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::BIF__f_00065_()
{
   FORMULA(_f_00065_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00065__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00065__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF_StmExpr --------------------
int PSyntax::BIF_StmExpr_0()
{
   PRODUCE(StmExpr,0)
   int s_ret;
   MAKE(BegStmExprLL);
   if ((s_ret = BIF__f_00067_()) <= 0) RETURN (s_ret);
   MAKE_CODE(EndBlock);
   RETURN (1);
}
int PSyntax::BIF_StmExpr()
{
   FORMULA(StmExpr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_StmExpr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00067_ --------------------
int PSyntax::BIF__f_00067__0()
{
   PRODUCE(_f_00067_,0)
   int s_ret;
   if ((s_ret = BIF_DefExpr()) <= 0) RETURN (s_ret);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::BIF__f_00067_()
{
   FORMULA(_f_00067_)
   int p_ret;
   while ((p_ret = BIF__f_00067__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_ExpressionExpression --------------------
int PSyntax::BIF_ExpressionExpression_0()
{
   PRODUCE(ExpressionExpression,0)
   int s_ret;
   PARAM_CODE(Part,16);
   if ((s_ret = BIF_Expressions()) <= 0) RETURN (s_ret);
   PARAM_TREE(ExpressionSLL,16);
   RETURN (1);
}
int PSyntax::BIF_ExpressionExpression()
{
   FORMULA(ExpressionExpression)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_ExpressionExpression_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_ExpressionValue --------------------
int PSyntax::BIF_ExpressionValue_0()
{
   PRODUCE(ExpressionValue,0)
   int s_ret;
   PARAM_CODE(Part,256);
   if ((s_ret = BIF_Expressions()) <= 0) RETURN (s_ret);
   PARAM_TREE(ExpressionSLL,256);
   RETURN (1);
}
int PSyntax::BIF_ExpressionValue()
{
   FORMULA(ExpressionValue)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_ExpressionValue_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}
