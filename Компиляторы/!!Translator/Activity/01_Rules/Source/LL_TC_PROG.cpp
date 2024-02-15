
// -------------------- LL_S_ --------------------
int PSyntax::LL_S__0()
{
   PRODUCE(S_,0)
   int s_ret;
   if ((s_ret = LL_Program()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_S_()
{
   FORMULA(S_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_S__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Program --------------------
int PSyntax::LL_Program_0()
{
   PRODUCE(Program,0)
   int s_ret;
   if ((s_ret = LL_Defines()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_Program()
{
   FORMULA(Program)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Program_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefParInit --------------------
int PSyntax::LL_DefParInit_0()
{
   PRODUCE(DefParInit,0)
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) RETURN (-1);
   MAKE_CODE(BegParVarAssign);
   if (LL_Assign() <= 0) RETURN (0);
   MAKE(ParVarAssign);
   RETURN (1);
}
int PSyntax::LL_DefParInit_1()
{
   PRODUCE(DefParInit,1)
   RETURN (1);
}
int PSyntax::LL_DefParInit()
{
   FORMULA(DefParInit)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefParInit_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefParInit_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefParVar --------------------
int PSyntax::LL_DefParVar_0()
{
   PRODUCE(DefParVar,0)
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) RETURN (-1);
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (0);
   MAKE(DefParVar);
   if (LL_DefParInit() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_DefParVar()
{
   FORMULA(DefParVar)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefParVar_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefParArr --------------------
int PSyntax::LL_DefParArr_0()
{
   PRODUCE(DefParArr,0)
   if (!Match(T_Lexeme::T_Syntax::sxDefArr)) RETURN (-1);
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) RETURN (0);
   MAKE(DefParArr);
   if (LL_DefArrDA() <= 0) RETURN (0);
   if (LL_DefParInit() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_DefParArr()
{
   FORMULA(DefParArr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefParArr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefPar --------------------
int PSyntax::LL_DefPar_0()
{
   PRODUCE(DefPar,0)
   int s_ret;
   if ((s_ret = LL_DefParArr()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_DefPar_1()
{
   PRODUCE(DefPar,1)
   int s_ret;
   if ((s_ret = LL_DefParVar()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_DefPar()
{
   FORMULA(DefPar)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefPar_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefPar_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefParItem --------------------
int PSyntax::LL_DefParItem_0()
{
   PRODUCE(DefParItem,0)
   int s_ret;
   if ((s_ret = LL_DefPar()) <= 0) RETURN (s_ret);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::LL_DefParItem()
{
   FORMULA(DefParItem)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefParItem_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefParList --------------------
int PSyntax::LL_DefParList_0()
{
   PRODUCE(DefParList,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (LL_DefParItem() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_DefParList()
{
   FORMULA(DefParList)
   int p_ret;
   while ((p_ret = LL_DefParList_0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_DefParams --------------------
int PSyntax::LL_DefParams_0()
{
   PRODUCE(DefParams,0)
   int s_ret;
   PARAM_TREE(Define,2);
   if ((s_ret = LL_DefParItem()) <= 0) RETURN (s_ret);
   if (LL_DefParList() <= 0) RETURN (0);
   MAKE_TREE(EndParams);
   RETURN (1);
}
int PSyntax::LL_DefParams()
{
   FORMULA(DefParams)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefParams_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_BodyFunc --------------------
int PSyntax::LL_BodyFunc_0()
{
   PRODUCE(BodyFunc,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE(BodyFunc);
   RETURN (1);
}
int PSyntax::LL_BodyFunc_1()
{
   PRODUCE(BodyFunc,1)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) RETURN (-1);
   PARAM(BodyFunc,1);
   RETURN (1);
}
int PSyntax::LL_BodyFunc_2()
{
   PRODUCE(BodyFunc,2)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) RETURN (-1);
   MAKE_CODE(EndParams);
   if (LL_StmExpr() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) RETURN (0);
   PARAM(BodyFunc,2);
   RETURN (1);
}
int PSyntax::LL_BodyFunc()
{
   FORMULA(BodyFunc)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_BodyFunc_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_BodyFunc_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_BodyFunc_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -3) ? -1 : 0);
}

// -------------------- LL_DefFunc_ --------------------
int PSyntax::LL_DefFunc__0()
{
   PRODUCE(DefFunc_,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyBracket)) RETURN (-1);
   PARAM_TREE(EndParams,2);
   RETURN (1);
}
int PSyntax::LL_DefFunc__1()
{
   PRODUCE(DefFunc_,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (-1);
   if (LL_DefParams() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_DefFunc_()
{
   FORMULA(DefFunc_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefFunc__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefFunc__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefFunc --------------------
int PSyntax::LL_DefFunc_0()
{
   PRODUCE(DefFunc,0)
   if (!Match(T_Lexeme::T_Syntax::sxDefFunc)) RETURN (-1);
   if (!Match(T_Lexeme::T_Syntax::sxIdentFunc)) RETURN (0);
   MAKE(FuncIdent);
   if (LL_DefFunc_() <= 0) RETURN (0);
   if (LL_BodyFunc() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_DefFunc()
{
   FORMULA(DefFunc)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefFunc_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_AInitialList --------------------
int PSyntax::LL_AInitialList_0()
{
   PRODUCE(AInitialList,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (LL_AInitItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::LL_AInitialList()
{
   FORMULA(AInitialList)
   int p_ret;
   while ((p_ret = LL_AInitialList_0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_AInitial --------------------
int PSyntax::LL_AInitial_0()
{
   PRODUCE(AInitial,0)
   int s_ret;
   if ((s_ret = LL_AInitItem()) <= 0) RETURN (s_ret);
   MAKE_TREE(AddToList);
   if (LL_AInitialList() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_AInitial()
{
   FORMULA(AInitial)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_AInitial_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Initializer --------------------
int PSyntax::LL_Initializer_0()
{
   PRODUCE(Initializer,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) RETURN (-1);
   MAKE_CODE(BegInitial);
   MAKE_TREE(NodeListLL);
   RETURN (1);
}
int PSyntax::LL_Initializer_1()
{
   PRODUCE(Initializer,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) RETURN (-1);
   PARAM_CODE(BegInitial,1);
   MAKE_TREE(NodeListLL);
   if (LL_AInitial() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) RETURN (0);
   MAKE_CODE(EndInitial);
   RETURN (1);
}
int PSyntax::LL_Initializer()
{
   FORMULA(Initializer)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Initializer_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Initializer_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_AInitItem --------------------
int PSyntax::LL_AInitItem_0()
{
   PRODUCE(AInitItem,0)
   int s_ret;
   if ((s_ret = LL_Initializer()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_AInitItem_1()
{
   PRODUCE(AInitItem,1)
   int s_ret;
   if ((s_ret = LL_Assign()) <= 0) RETURN (s_ret);
   MAKE_CODE(AInitItem);
   RETURN (1);
}
int PSyntax::LL_AInitItem()
{
   FORMULA(AInitItem)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_AInitItem_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_AInitItem_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefAInit --------------------
int PSyntax::LL_DefAInit_0()
{
   PRODUCE(DefAInit,0)
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) RETURN (-1);
   MAKE_CODE(BegAInit);
   if (LL_Initializer() <= 0) RETURN (0);
   MAKE(EndAInit);
   RETURN (1);
}
int PSyntax::LL_DefAInit_1()
{
   PRODUCE(DefAInit,1)
   RETURN (1);
}
int PSyntax::LL_DefAInit()
{
   FORMULA(DefAInit)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefAInit_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefAInit_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DRanges --------------------
int PSyntax::LL_DRanges_0()
{
   PRODUCE(DRanges,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) RETURN (-1);
   if (LL_Assign() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) RETURN (0);
   MAKE(DRange);
   RETURN (1);
}
int PSyntax::LL_DRanges()
{
   FORMULA(DRanges)
   int p_ret;
   while ((p_ret = LL_DRanges_0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_DefArrD1A --------------------
int PSyntax::LL_DefArrD1A_0()
{
   PRODUCE(DefArrD1A,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyScrape)) RETURN (-1);
   MAKE(DefArrD1AEmpty);
   RETURN (1);
}
int PSyntax::LL_DefArrD1A_1()
{
   PRODUCE(DefArrD1A,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) RETURN (-1);
   if (LL_Assign() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) RETURN (0);
   MAKE(DRange);
   RETURN (1);
}
int PSyntax::LL_DefArrD1A()
{
   FORMULA(DefArrD1A)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefArrD1A_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefArrD1A_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefArrDA --------------------
int PSyntax::LL_DefArrDA_0()
{
   PRODUCE(DefArrDA,0)
   int s_ret;
   if ((s_ret = LL_DefArrD1A()) <= 0) RETURN (s_ret);
   if (LL_DRanges() <= 0) RETURN (0);
   MAKE_CODE(EndRanges);
   RETURN (1);
}
int PSyntax::LL_DefArrDA()
{
   FORMULA(DefArrDA)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefArrDA_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefArr --------------------
int PSyntax::LL_DefArr_0()
{
   PRODUCE(DefArr,0)
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) RETURN (-1);
   MAKE(DefArray);
   if (LL_DefArrDA() <= 0) RETURN (0);
   if (LL_DefAInit() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_DefArr()
{
   FORMULA(DefArr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefArr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefVarAssign --------------------
int PSyntax::LL_DefVarAssign_0()
{
   PRODUCE(DefVarAssign,0)
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) RETURN (-1);
   MAKE_CODE(BegDefVarAssign);
   if (LL_Assign() <= 0) RETURN (0);
   MAKE(DefVarAssign);
   RETURN (1);
}
int PSyntax::LL_DefVarAssign()
{
   FORMULA(DefVarAssign)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefVarAssign_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefVarInit --------------------
int PSyntax::LL_DefVarInit_0()
{
   PRODUCE(DefVarInit,0)
   int s_ret;
   if ((s_ret = LL_DefVarAssign()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_DefVarInit_1()
{
   PRODUCE(DefVarInit,1)
   RETURN (1);
}
int PSyntax::LL_DefVarInit()
{
   FORMULA(DefVarInit)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefVarInit_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefVarInit_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefVar --------------------
int PSyntax::LL_DefVar_0()
{
   PRODUCE(DefVar,0)
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (-1);
   MAKE(DefIdent);
   if (LL_DefVarInit() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_DefVar()
{
   FORMULA(DefVar)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefVar_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefIAV --------------------
int PSyntax::LL_DefIAV_0()
{
   PRODUCE(DefIAV,0)
   int s_ret;
   if ((s_ret = LL_DefArr()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_DefIAV_1()
{
   PRODUCE(DefIAV,1)
   int s_ret;
   if ((s_ret = LL_DefVar()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_DefIAV()
{
   FORMULA(DefIAV)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefIAV_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefIAV_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefItem --------------------
int PSyntax::LL_DefItem_0()
{
   PRODUCE(DefItem,0)
   if (!Match(T_Symbol::T_Priority::prAnd)) RETURN (-1);
   if (LL_DefIAV() <= 0) RETURN (0);
   MAKE_TREE(RefDef);
   RETURN (1);
}
int PSyntax::LL_DefItem_1()
{
   PRODUCE(DefItem,1)
   int s_ret;
   if ((s_ret = LL_DefIAV()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_DefItem()
{
   FORMULA(DefItem)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefItem_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefItem_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefType --------------------
int PSyntax::LL_DefType_0()
{
   PRODUCE(DefType,0)
   if (!Match(T_Lexeme::T_Syntax::sxDefArr)) RETURN (-1);
   RETURN (1);
}
int PSyntax::LL_DefType_1()
{
   PRODUCE(DefType,1)
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) RETURN (-1);
   RETURN (1);
}
int PSyntax::LL_DefType()
{
   FORMULA(DefType)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefType_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefType_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefineList --------------------
int PSyntax::LL_DefineList_0()
{
   PRODUCE(DefineList,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (LL_DefItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::LL_DefineList()
{
   FORMULA(DefineList)
   int p_ret;
   while ((p_ret = LL_DefineList_0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_Define --------------------
int PSyntax::LL_Define_0()
{
   PRODUCE(Define,0)
   int s_ret;
   if ((s_ret = LL_DefType()) <= 0) RETURN (s_ret);
   MAKE(Define);
   if (LL_DefItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   if (LL_DefineList() <= 0) RETURN (0);
   MAKE_CODE(EndDefine);
   RETURN (1);
}
int PSyntax::LL_Define()
{
   FORMULA(Define)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Define_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ConditionDef --------------------
int PSyntax::LL_ConditionDef_0()
{
   PRODUCE(ConditionDef,0)
   if (!Match(T_Symbol::T_Priority::prAnd)) RETURN (-1);
   if (LL_DefVar() <= 0) RETURN (0);
   MAKE_TREE(RefDef);
   RETURN (1);
}
int PSyntax::LL_ConditionDef_1()
{
   PRODUCE(ConditionDef,1)
   int s_ret;
   if ((s_ret = LL_DefVar()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_ConditionDef()
{
   FORMULA(ConditionDef)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ConditionDef_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ConditionDef_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_Condition --------------------
int PSyntax::LL_Condition_0()
{
   PRODUCE(Condition,0)
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) RETURN (-1);
   MAKE(Define);
   if (LL_ConditionDef() <= 0) RETURN (0);
   MAKE(PushDef);
   RETURN (1);
}
int PSyntax::LL_Condition_1()
{
   PRODUCE(Condition,1)
   int s_ret;
   if ((s_ret = LL_ExpressionCondition()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_Condition()
{
   FORMULA(Condition)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Condition_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Condition_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_ExprList --------------------
int PSyntax::LL_ExprList_0()
{
   PRODUCE(ExprList,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (LL_Assign() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   MAKE_CODE(AddToExpr);
   RETURN (1);
}
int PSyntax::LL_ExprList()
{
   FORMULA(ExprList)
   int p_ret;
   while ((p_ret = LL_ExprList_0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_Expressions --------------------
int PSyntax::LL_Expressions_0()
{
   PRODUCE(Expressions,0)
   int s_ret;
   if ((s_ret = LL_Assign()) <= 0) RETURN (s_ret);
   MAKE(ExpressionsLL);
   if (LL_ExprList() <= 0) RETURN (0);
   MAKE_CODE(ExpressionSLL);
   RETURN (1);
}
int PSyntax::LL_Expressions()
{
   FORMULA(Expressions)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Expressions_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_PriorAssign --------------------
int PSyntax::LL_PriorAssign_0()
{
   PRODUCE(PriorAssign,0)
   if (!Match(T_Symbol::T_Priority::prAssign)) RETURN (-1);
   RETURN (1);
}
int PSyntax::LL_PriorAssign()
{
   FORMULA(PriorAssign)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_PriorAssign_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_AssignList --------------------
int PSyntax::LL_AssignList_0()
{
   PRODUCE(AssignList,0)
   int s_ret;
   if ((s_ret = LL_PriorAssign()) <= 0) RETURN (s_ret);
   if (LL_Assign() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::LL_AssignList_1()
{
   PRODUCE(AssignList,1)
   RETURN (1);
}
int PSyntax::LL_AssignList()
{
   FORMULA(AssignList)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_AssignList_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_AssignList_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_Assign --------------------
int PSyntax::LL_Assign_0()
{
   PRODUCE(Assign,0)
   int s_ret;
   if ((s_ret = LL_Question()) <= 0) RETURN (s_ret);
   if (LL_AssignList() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_Assign()
{
   FORMULA(Assign)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Assign_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_QuestionList --------------------
int PSyntax::LL_QuestionList_0()
{
   PRODUCE(QuestionList,0)
   if (!Match(T_Symbol::T_Priority::prQuestion)) RETURN (-1);
   MAKE_CODE(BegQuestion);
   if (LL_ExpressionValue() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxColon)) RETURN (0);
   MAKE_CODE(MidQuestion);
   if (LL_Question() <= 0) RETURN (0);
   MAKE(Question);
   RETURN (1);
}
int PSyntax::LL_QuestionList_1()
{
   PRODUCE(QuestionList,1)
   RETURN (1);
}
int PSyntax::LL_QuestionList()
{
   FORMULA(QuestionList)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_QuestionList_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_QuestionList_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_Question --------------------
int PSyntax::LL_Question_0()
{
   PRODUCE(Question,0)
   int s_ret;
   if ((s_ret = LL_OrOr()) <= 0) RETURN (s_ret);
   if (LL_QuestionList() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_Question()
{
   FORMULA(Question)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Question_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_OrOr --------------------
int PSyntax::LL_OrOr_0()
{
   PRODUCE(OrOr,0)
   int s_ret;
   if ((s_ret = LL_AndAnd()) <= 0) RETURN (s_ret);
   if (LL_OrOr_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_OrOr()
{
   FORMULA(OrOr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_OrOr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_OrOr_ --------------------
int PSyntax::LL_OrOr__0()
{
   PRODUCE(OrOr_,0)
   if (!Match(T_Symbol::T_Priority::prOrOr)) RETURN (-1);
   if (LL_AndAnd() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::LL_OrOr_()
{
   FORMULA(OrOr_)
   int p_ret;
   while ((p_ret = LL_OrOr__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_AndAnd --------------------
int PSyntax::LL_AndAnd_0()
{
   PRODUCE(AndAnd,0)
   int s_ret;
   if ((s_ret = LL_Or()) <= 0) RETURN (s_ret);
   if (LL_AndAnd_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_AndAnd()
{
   FORMULA(AndAnd)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_AndAnd_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_AndAnd_ --------------------
int PSyntax::LL_AndAnd__0()
{
   PRODUCE(AndAnd_,0)
   if (!Match(T_Symbol::T_Priority::prAndAnd)) RETURN (-1);
   if (LL_Or() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::LL_AndAnd_()
{
   FORMULA(AndAnd_)
   int p_ret;
   while ((p_ret = LL_AndAnd__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_Or --------------------
int PSyntax::LL_Or_0()
{
   PRODUCE(Or,0)
   int s_ret;
   if ((s_ret = LL_XOr()) <= 0) RETURN (s_ret);
   if (LL_Or_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_Or()
{
   FORMULA(Or)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Or_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Or_ --------------------
int PSyntax::LL_Or__0()
{
   PRODUCE(Or_,0)
   if (!Match(T_Symbol::T_Priority::prOr)) RETURN (-1);
   if (LL_XOr() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::LL_Or_()
{
   FORMULA(Or_)
   int p_ret;
   while ((p_ret = LL_Or__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_XOr --------------------
int PSyntax::LL_XOr_0()
{
   PRODUCE(XOr,0)
   int s_ret;
   if ((s_ret = LL_And()) <= 0) RETURN (s_ret);
   if (LL_XOr_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_XOr()
{
   FORMULA(XOr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_XOr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_XOr_ --------------------
int PSyntax::LL_XOr__0()
{
   PRODUCE(XOr_,0)
   if (!Match(T_Symbol::T_Priority::prXOr)) RETURN (-1);
   if (LL_And() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::LL_XOr_()
{
   FORMULA(XOr_)
   int p_ret;
   while ((p_ret = LL_XOr__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_And --------------------
int PSyntax::LL_And_0()
{
   PRODUCE(And,0)
   int s_ret;
   if ((s_ret = LL_Equ()) <= 0) RETURN (s_ret);
   if (LL_And_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_And()
{
   FORMULA(And)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_And_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_And_ --------------------
int PSyntax::LL_And__0()
{
   PRODUCE(And_,0)
   if (!Match(T_Symbol::T_Priority::prAnd)) RETURN (-1);
   if (LL_Equ() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::LL_And_()
{
   FORMULA(And_)
   int p_ret;
   while ((p_ret = LL_And__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_Equ --------------------
int PSyntax::LL_Equ_0()
{
   PRODUCE(Equ,0)
   int s_ret;
   if ((s_ret = LL_Compare()) <= 0) RETURN (s_ret);
   if (LL_Equ_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_Equ()
{
   FORMULA(Equ)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Equ_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Equ_ --------------------
int PSyntax::LL_Equ__0()
{
   PRODUCE(Equ_,0)
   if (!Match(T_Symbol::T_Priority::prEqu)) RETURN (-1);
   if (LL_Compare() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::LL_Equ_()
{
   FORMULA(Equ_)
   int p_ret;
   while ((p_ret = LL_Equ__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_Compare --------------------
int PSyntax::LL_Compare_0()
{
   PRODUCE(Compare,0)
   int s_ret;
   if ((s_ret = LL_Shift()) <= 0) RETURN (s_ret);
   if (LL_Compare_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_Compare()
{
   FORMULA(Compare)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Compare_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Compare_ --------------------
int PSyntax::LL_Compare__0()
{
   PRODUCE(Compare_,0)
   if (!Match(T_Symbol::T_Priority::prCompare)) RETURN (-1);
   if (LL_Shift() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::LL_Compare_()
{
   FORMULA(Compare_)
   int p_ret;
   while ((p_ret = LL_Compare__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_Shift --------------------
int PSyntax::LL_Shift_0()
{
   PRODUCE(Shift,0)
   int s_ret;
   if ((s_ret = LL_Term()) <= 0) RETURN (s_ret);
   if (LL_Shift_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_Shift()
{
   FORMULA(Shift)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Shift_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Shift_ --------------------
int PSyntax::LL_Shift__0()
{
   PRODUCE(Shift_,0)
   if (!Match(T_Symbol::T_Priority::prShift)) RETURN (-1);
   if (LL_Term() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::LL_Shift_()
{
   FORMULA(Shift_)
   int p_ret;
   while ((p_ret = LL_Shift__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_Term --------------------
int PSyntax::LL_Term_0()
{
   PRODUCE(Term,0)
   int s_ret;
   if ((s_ret = LL_Factor()) <= 0) RETURN (s_ret);
   if (LL_Term_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_Term()
{
   FORMULA(Term)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Term_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Term_ --------------------
int PSyntax::LL_Term__0()
{
   PRODUCE(Term_,0)
   if (!Match(T_Symbol::T_Priority::prTerm)) RETURN (-1);
   if (LL_Factor() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::LL_Term_()
{
   FORMULA(Term_)
   int p_ret;
   while ((p_ret = LL_Term__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_Factor --------------------
int PSyntax::LL_Factor_0()
{
   PRODUCE(Factor,0)
   int s_ret;
   if ((s_ret = LL_Unary()) <= 0) RETURN (s_ret);
   if (LL_Factor_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_Factor()
{
   FORMULA(Factor)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Factor_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Factor_ --------------------
int PSyntax::LL_Factor__0()
{
   PRODUCE(Factor_,0)
   if (!Match(T_Symbol::T_Priority::prFactor)) RETURN (-1);
   if (LL_Unary() <= 0) RETURN (0);
   MAKE(Binary);
   RETURN (1);
}
int PSyntax::LL_Factor_()
{
   FORMULA(Factor_)
   int p_ret;
   while ((p_ret = LL_Factor__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_UnaryIncDec --------------------
int PSyntax::LL_UnaryIncDec_0()
{
   PRODUCE(UnaryIncDec,0)
   if (!Match(T_Symbol::T_Priority::prIncDec)) RETURN (-1);
   MAKE(IncDec);
   RETURN (1);
}
int PSyntax::LL_UnaryIncDec_1()
{
   PRODUCE(UnaryIncDec,1)
   RETURN (1);
}
int PSyntax::LL_UnaryIncDec()
{
   FORMULA(UnaryIncDec)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_UnaryIncDec_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_UnaryIncDec_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_Unary --------------------
int PSyntax::LL_Unary_0()
{
   PRODUCE(Unary,0)
   if (!Match(T_Symbol::T_Priority::prUnary)) RETURN (-1);
   if (LL_Unary() <= 0) RETURN (0);
   MAKE(Unary);
   RETURN (1);
}
int PSyntax::LL_Unary_1()
{
   PRODUCE(Unary,1)
   if (!Match(T_Symbol::T_Priority::prTerm)) RETURN (-1);
   if (LL_Unary() <= 0) RETURN (0);
   MAKE(Unary);
   RETURN (1);
}
int PSyntax::LL_Unary_2()
{
   PRODUCE(Unary,2)
   if (!Match(T_Symbol::T_Priority::prIncDec)) RETURN (-1);
   if (LL_Unary() <= 0) RETURN (0);
   MAKE(Unary);
   RETURN (1);
}
int PSyntax::LL_Unary_3()
{
   PRODUCE(Unary,3)
   if (!Match(T_Lexeme::T_Syntax::sxCastUnary)) RETURN (-1);
   if (LL_Unary() <= 0) RETURN (0);
   MAKE(Cast);
   RETURN (1);
}
int PSyntax::LL_Unary_4()
{
   PRODUCE(Unary,4)
   int s_ret;
   if ((s_ret = LL_PrimaryExpr()) <= 0) RETURN (s_ret);
   if (LL_UnaryIncDec() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_Unary()
{
   FORMULA(Unary)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Unary_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Unary_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Unary_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Unary_3()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Unary_4()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -5) ? -1 : 0);
}

// -------------------- LL_Primary --------------------
int PSyntax::LL_Primary_0()
{
   PRODUCE(Primary,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (-1);
   if (LL_ExpressionNone() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   MAKE_TREE(Primary);
   RETURN (1);
}
int PSyntax::LL_Primary()
{
   FORMULA(Primary)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Primary_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_PrimaryExpr --------------------
int PSyntax::LL_PrimaryExpr_0()
{
   PRODUCE(PrimaryExpr,0)
   if (!Match(T_Lexeme::T_Group::grInteger)) RETURN (-1);
   MAKE(Number);
   RETURN (1);
}
int PSyntax::LL_PrimaryExpr_1()
{
   PRODUCE(PrimaryExpr,1)
   if (!Match(T_Lexeme::T_Group::grNumber)) RETURN (-1);
   MAKE(Number);
   RETURN (1);
}
int PSyntax::LL_PrimaryExpr_2()
{
   PRODUCE(PrimaryExpr,2)
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) RETURN (-1);
   if (LL_Ranges() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_PrimaryExpr_3()
{
   PRODUCE(PrimaryExpr,3)
   if (!Match(T_Lexeme::T_Syntax::sxIdentFunc)) RETURN (-1);
   if (LL_CallParams() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_PrimaryExpr_4()
{
   PRODUCE(PrimaryExpr,4)
   if (!Match(T_Lexeme::T_Syntax::sxCast)) RETURN (-1);
   if (LL_Primary() <= 0) RETURN (0);
   MAKE(Cast);
   RETURN (1);
}
int PSyntax::LL_PrimaryExpr_5()
{
   PRODUCE(PrimaryExpr,5)
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (-1);
   MAKE(Ident);
   RETURN (1);
}
int PSyntax::LL_PrimaryExpr_6()
{
   PRODUCE(PrimaryExpr,6)
   int s_ret;
   if ((s_ret = LL_Primary()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_PrimaryExpr()
{
   FORMULA(PrimaryExpr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_PrimaryExpr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_3()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_4()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_5()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_6()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -7) ? -1 : 0);
}

// -------------------- LL_RangesList --------------------
int PSyntax::LL_RangesList_0()
{
   PRODUCE(RangesList,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) RETURN (-1);
   if (LL_ExpressionValue() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) RETURN (0);
   MAKE(IndexLL);
   RETURN (1);
}
int PSyntax::LL_RangesList()
{
   FORMULA(RangesList)
   int p_ret;
   while ((p_ret = LL_RangesList_0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_Ranges --------------------
int PSyntax::LL_Ranges_0()
{
   PRODUCE(Ranges,0)
   int s_ret;
   MAKE(BegIndexLL);
   if ((s_ret = LL_RangesList()) <= 0) RETURN (s_ret);
   MAKE(EndIndex);
   RETURN (1);
}
int PSyntax::LL_Ranges()
{
   FORMULA(Ranges)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Ranges_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_CallParams --------------------
int PSyntax::LL_CallParams_0()
{
   PRODUCE(CallParams,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyBracket)) RETURN (-1);
   MAKE(Params);
   RETURN (1);
}
int PSyntax::LL_CallParams_1()
{
   PRODUCE(CallParams,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (-1);
   if (LL_ExpressionValueList() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   PARAM(Params,1);
   RETURN (1);
}
int PSyntax::LL_CallParams()
{
   FORMULA(CallParams)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_CallParams_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_CallParams_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_CompaundStmnt --------------------
int PSyntax::LL_CompaundStmnt_0()
{
   PRODUCE(CompaundStmnt,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) RETURN (-1);
   MAKE(Compaund);
   MAKE_CODE(EndBlock);
   RETURN (1);
}
int PSyntax::LL_CompaundStmnt_1()
{
   PRODUCE(CompaundStmnt,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) RETURN (-1);
   MAKE(Compaund);
   if (LL_StmExpr() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) RETURN (0);
   MAKE_CODE(EndBlock);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::LL_CompaundStmnt()
{
   FORMULA(CompaundStmnt)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_CompaundStmnt_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_CompaundStmnt_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_IfStmnt_ --------------------
int PSyntax::LL_IfStmnt__0()
{
   PRODUCE(IfStmnt_,0)
   if (!Match(T_Lexeme::W_Type::rwElse)) RETURN (-1);
   MAKE_CODE(Else);
   if (LL_DefExpr() <= 0) RETURN (0);
   PARAM(If,1);
   RETURN (1);
}
int PSyntax::LL_IfStmnt__1()
{
   PRODUCE(IfStmnt_,1)
   MAKE(If);
   RETURN (1);
}
int PSyntax::LL_IfStmnt_()
{
   FORMULA(IfStmnt_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_IfStmnt__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_IfStmnt__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_IfStmnt --------------------
int PSyntax::LL_IfStmnt_0()
{
   PRODUCE(IfStmnt,0)
   if (!Match(T_Lexeme::W_Type::rwIf)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   MAKE_CODE(BegIf);
   if (LL_Condition() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   MAKE_CODE(Then);
   if (LL_DefExpr() <= 0) RETURN (0);
   if (LL_IfStmnt_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_IfStmnt()
{
   FORMULA(IfStmnt)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_IfStmnt_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ForPrefix --------------------
int PSyntax::LL_ForPrefix_0()
{
   PRODUCE(ForPrefix,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE_TREE(NodeNull);
   RETURN (1);
}
int PSyntax::LL_ForPrefix_1()
{
   PRODUCE(ForPrefix,1)
   int s_ret;
   if ((s_ret = LL_DefineSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_ForPrefix_2()
{
   PRODUCE(ForPrefix,2)
   int s_ret;
   if ((s_ret = LL_ExprSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_ForPrefix()
{
   FORMULA(ForPrefix)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ForPrefix_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ForPrefix_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ForPrefix_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -3) ? -1 : 0);
}

// -------------------- LL_ForCondition --------------------
int PSyntax::LL_ForCondition_0()
{
   PRODUCE(ForCondition,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE(NodeNull);
   RETURN (1);
}
int PSyntax::LL_ForCondition_1()
{
   PRODUCE(ForCondition,1)
   int s_ret;
   if ((s_ret = LL_Condition()) <= 0) RETURN (s_ret);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_ForCondition()
{
   FORMULA(ForCondition)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ForCondition_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ForCondition_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_ForPosfix --------------------
int PSyntax::LL_ForPosfix_0()
{
   PRODUCE(ForPosfix,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (-1);
   MAKE_TREE(NodeNull);
   RETURN (1);
}
int PSyntax::LL_ForPosfix_1()
{
   PRODUCE(ForPosfix,1)
   int s_ret;
   if ((s_ret = LL_ExpressionExpression()) <= 0) RETURN (s_ret);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_ForPosfix()
{
   FORMULA(ForPosfix)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ForPosfix_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ForPosfix_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_ForStmnt --------------------
int PSyntax::LL_ForStmnt_0()
{
   PRODUCE(ForStmnt,0)
   if (!Match(T_Lexeme::W_Type::rwFor)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   MAKE(BegFor);
   if (LL_ForPrefix() <= 0) RETURN (0);
   MAKE_CODE(PrefFor);
   if (LL_ForCondition() <= 0) RETURN (0);
   MAKE_CODE(ConditionFor);
   if (LL_ForPosfix() <= 0) RETURN (0);
   MAKE_CODE(PostFor);
   if (LL_DefExpr() <= 0) RETURN (0);
   MAKE(For);
   RETURN (1);
}
int PSyntax::LL_ForStmnt()
{
   FORMULA(ForStmnt)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ForStmnt_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DoStmnt --------------------
int PSyntax::LL_DoStmnt_0()
{
   PRODUCE(DoStmnt,0)
   if (!Match(T_Lexeme::W_Type::rwDo)) RETURN (-1);
   MAKE(BegDo);
   if (LL_DefExpr() <= 0) RETURN (0);
   if (!Match(T_Lexeme::W_Type::rwWhile)) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   MAKE_CODE(MidDo);
   if (LL_Condition() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(Do);
   RETURN (1);
}
int PSyntax::LL_DoStmnt()
{
   FORMULA(DoStmnt)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DoStmnt_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_WhileStmnt --------------------
int PSyntax::LL_WhileStmnt_0()
{
   PRODUCE(WhileStmnt,0)
   if (!Match(T_Lexeme::W_Type::rwWhile)) RETURN (-1);
   MAKE(BegWhile);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   if (LL_Condition() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   MAKE_CODE(MidWhile);
   if (LL_DefExpr() <= 0) RETURN (0);
   MAKE(While);
   RETURN (1);
}
int PSyntax::LL_WhileStmnt()
{
   FORMULA(WhileStmnt)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_WhileStmnt_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_GoToStmnt --------------------
int PSyntax::LL_GoToStmnt_0()
{
   PRODUCE(GoToStmnt,0)
   if (!Match(T_Lexeme::W_Type::rwGoTo)) RETURN (-1);
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(GoTo);
   RETURN (1);
}
int PSyntax::LL_GoToStmnt()
{
   FORMULA(GoToStmnt)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_GoToStmnt_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_BreakStmnt --------------------
int PSyntax::LL_BreakStmnt_0()
{
   PRODUCE(BreakStmnt,0)
   if (!Match(T_Lexeme::W_Type::rwBreak)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(Break);
   RETURN (1);
}
int PSyntax::LL_BreakStmnt()
{
   FORMULA(BreakStmnt)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_BreakStmnt_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ContinueStmnt --------------------
int PSyntax::LL_ContinueStmnt_0()
{
   PRODUCE(ContinueStmnt,0)
   if (!Match(T_Lexeme::W_Type::rwContinue)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(Continue);
   RETURN (1);
}
int PSyntax::LL_ContinueStmnt()
{
   FORMULA(ContinueStmnt)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ContinueStmnt_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ReturnVal --------------------
int PSyntax::LL_ReturnVal_0()
{
   PRODUCE(ReturnVal,0)
   int s_ret;
   if ((s_ret = LL_ExpressionValue()) <= 0) RETURN (s_ret);
   PARAM(Return,1);
   RETURN (1);
}
int PSyntax::LL_ReturnVal_1()
{
   PRODUCE(ReturnVal,1)
   MAKE(Return);
   RETURN (1);
}
int PSyntax::LL_ReturnVal()
{
   FORMULA(ReturnVal)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ReturnVal_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ReturnVal_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_ReturnStmnt --------------------
int PSyntax::LL_ReturnStmnt_0()
{
   PRODUCE(ReturnStmnt,0)
   if (!Match(T_Lexeme::W_Type::rwReturn)) RETURN (-1);
   if (LL_ReturnVal() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_ReturnStmnt()
{
   FORMULA(ReturnStmnt)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ReturnStmnt_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Statement --------------------
int PSyntax::LL_Statement_0()
{
   PRODUCE(Statement,0)
   if (!Match(T_Lexeme::T_Syntax::sxLabel)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxColon)) RETURN (0);
   MAKE_CODE(Label);
   if (LL_DefExpr() <= 0) RETURN (0);
   MAKE_TREE(Label);
   RETURN (1);
}
int PSyntax::LL_Statement_1()
{
   PRODUCE(Statement,1)
   int s_ret;
   if ((s_ret = LL_IfStmnt()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_Statement_2()
{
   PRODUCE(Statement,2)
   int s_ret;
   if ((s_ret = LL_DoStmnt()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_Statement_3()
{
   PRODUCE(Statement,3)
   int s_ret;
   if ((s_ret = LL_WhileStmnt()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_Statement_4()
{
   PRODUCE(Statement,4)
   int s_ret;
   if ((s_ret = LL_ForStmnt()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_Statement_5()
{
   PRODUCE(Statement,5)
   int s_ret;
   if ((s_ret = LL_GoToStmnt()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_Statement_6()
{
   PRODUCE(Statement,6)
   int s_ret;
   if ((s_ret = LL_BreakStmnt()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_Statement_7()
{
   PRODUCE(Statement,7)
   int s_ret;
   if ((s_ret = LL_ContinueStmnt()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_Statement_8()
{
   PRODUCE(Statement,8)
   int s_ret;
   if ((s_ret = LL_ReturnStmnt()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_Statement_9()
{
   PRODUCE(Statement,9)
   int s_ret;
   if ((s_ret = LL_CompaundStmnt()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_Statement()
{
   FORMULA(Statement)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Statement_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_3()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_4()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_5()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_6()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_7()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_8()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_9()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -10) ? -1 : 0);
}

// -------------------- LL_DefineSemi --------------------
int PSyntax::LL_DefineSemi_0()
{
   PRODUCE(DefineSemi,0)
   int s_ret;
   if ((s_ret = LL_Define()) <= 0) RETURN (s_ret);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_DefineSemi()
{
   FORMULA(DefineSemi)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefineSemi_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExprSemi --------------------
int PSyntax::LL_ExprSemi_0()
{
   PRODUCE(ExprSemi,0)
   int s_ret;
   if ((s_ret = LL_ExpressionExpression()) <= 0) RETURN (s_ret);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   RETURN (1);
}
int PSyntax::LL_ExprSemi()
{
   FORMULA(ExprSemi)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExprSemi_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefExpr --------------------
int PSyntax::LL_DefExpr_0()
{
   PRODUCE(DefExpr,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE_TREE(NodeNull);
   RETURN (1);
}
int PSyntax::LL_DefExpr_1()
{
   PRODUCE(DefExpr,1)
   int s_ret;
   if ((s_ret = LL_DefineSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_DefExpr_2()
{
   PRODUCE(DefExpr,2)
   int s_ret;
   if ((s_ret = LL_Statement()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_DefExpr_3()
{
   PRODUCE(DefExpr,3)
   int s_ret;
   if ((s_ret = LL_ExprSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_DefExpr()
{
   FORMULA(DefExpr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefExpr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefExpr_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefExpr_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefExpr_3()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -4) ? -1 : 0);
}

// -------------------- LL_StmExprList --------------------
int PSyntax::LL_StmExprList_0()
{
   PRODUCE(StmExprList,0)
   int s_ret;
   if ((s_ret = LL_DefExpr()) <= 0) RETURN (s_ret);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::LL_StmExprList()
{
   FORMULA(StmExprList)
   int p_ret;
   while ((p_ret = LL_StmExprList_0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_StmExpr --------------------
int PSyntax::LL_StmExpr_0()
{
   PRODUCE(StmExpr,0)
   int s_ret;
   MAKE(BegStmExprLL);
   if ((s_ret = LL_StmExprList()) <= 0) RETURN (s_ret);
   MAKE_CODE(EndBlock);
   RETURN (1);
}
int PSyntax::LL_StmExpr()
{
   FORMULA(StmExpr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_StmExpr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefFAV --------------------
int PSyntax::LL_DefFAV_0()
{
   PRODUCE(DefFAV,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE_TREE(NodeNull);
   RETURN (1);
}
int PSyntax::LL_DefFAV_1()
{
   PRODUCE(DefFAV,1)
   int s_ret;
   if ((s_ret = LL_DefFunc()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_DefFAV_2()
{
   PRODUCE(DefFAV,2)
   int s_ret;
   if ((s_ret = LL_DefineSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::LL_DefFAV()
{
   FORMULA(DefFAV)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefFAV_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefFAV_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefFAV_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -3) ? -1 : 0);
}

// -------------------- LL_DefinesList --------------------
int PSyntax::LL_DefinesList_0()
{
   PRODUCE(DefinesList,0)
   int s_ret;
   if ((s_ret = LL_DefFAV()) <= 0) RETURN (s_ret);
   MAKE_TREE(AddToList);
   RETURN (1);
}
int PSyntax::LL_DefinesList()
{
   FORMULA(DefinesList)
   int p_ret;
   while ((p_ret = LL_DefinesList_0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- LL_Defines --------------------
int PSyntax::LL_Defines_0()
{
   PRODUCE(Defines,0)
   int s_ret;
   MAKE(BegStmExprLL);
   if ((s_ret = LL_DefinesList()) <= 0) RETURN (s_ret);
   MAKE_CODE(EndBlock);
   RETURN (1);
}
int PSyntax::LL_Defines()
{
   FORMULA(Defines)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Defines_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExpressionExpression --------------------
int PSyntax::LL_ExpressionExpression_0()
{
   PRODUCE(ExpressionExpression,0)
   int s_ret;
   PARAM_CODE(Part,16);
   if ((s_ret = LL_Expressions()) <= 0) RETURN (s_ret);
   PARAM_TREE(ExpressionSLL,16);
   RETURN (1);
}
int PSyntax::LL_ExpressionExpression()
{
   FORMULA(ExpressionExpression)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExpressionExpression_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExpressionCondition --------------------
int PSyntax::LL_ExpressionCondition_0()
{
   PRODUCE(ExpressionCondition,0)
   int s_ret;
   PARAM_CODE(Part,241);
   if ((s_ret = LL_Expressions()) <= 0) RETURN (s_ret);
   PARAM_TREE(ExpressionSLL,241);
   RETURN (1);
}
int PSyntax::LL_ExpressionCondition()
{
   FORMULA(ExpressionCondition)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExpressionCondition_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExpressionNone --------------------
int PSyntax::LL_ExpressionNone_0()
{
   PRODUCE(ExpressionNone,0)
   int s_ret;
   MAKE_CODE(Part);
   if ((s_ret = LL_Expressions()) <= 0) RETURN (s_ret);
   MAKE_TREE(ExpressionSLL);
   RETURN (1);
}
int PSyntax::LL_ExpressionNone()
{
   FORMULA(ExpressionNone)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExpressionNone_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExpressionValue --------------------
int PSyntax::LL_ExpressionValue_0()
{
   PRODUCE(ExpressionValue,0)
   int s_ret;
   PARAM_CODE(Part,256);
   if ((s_ret = LL_Expressions()) <= 0) RETURN (s_ret);
   PARAM_TREE(ExpressionSLL,256);
   RETURN (1);
}
int PSyntax::LL_ExpressionValue()
{
   FORMULA(ExpressionValue)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExpressionValue_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExpressionValueList --------------------
int PSyntax::LL_ExpressionValueList_0()
{
   PRODUCE(ExpressionValueList,0)
   int s_ret;
   PARAM_CODE(Part,512);
   if ((s_ret = LL_Expressions()) <= 0) RETURN (s_ret);
   PARAM_TREE(ExpressionSLL,512);
   RETURN (1);
}
int PSyntax::LL_ExpressionValueList()
{
   FORMULA(ExpressionValueList)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExpressionValueList_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}
