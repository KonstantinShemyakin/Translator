
// -------------------- LL_S_ --------------------
int PSyntax::LL_S__0()
{
   int s_ret;
   if ((s_ret = LL_Program()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_S_()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_S__0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Program --------------------
int PSyntax::LL_Program_0()
{
   int s_ret;
   if ((s_ret = LL_Defines()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_Program()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Program_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefParInit --------------------
int PSyntax::LL_DefParInit_0()
{
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) return -1;
   MAKE_CODE(BegParVarAssign);
   if (LL_Assign() <= 0) return 0;
   MAKE(ParVarAssign);
   return 1;
}
int PSyntax::LL_DefParInit_1()
{
   return 1;
}
int PSyntax::LL_DefParInit()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefParInit_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefParInit_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefParVar --------------------
int PSyntax::LL_DefParVar_0()
{
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) return -1;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   MAKE(DefParVar);
   if (LL_DefParInit() <= 0) return 0;
   return 1;
}
int PSyntax::LL_DefParVar()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefParVar_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefParArr --------------------
int PSyntax::LL_DefParArr_0()
{
   if (!Match(T_Lexeme::T_Syntax::sxDefArr)) return -1;
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) return 0;
   MAKE(DefParArr);
   if (LL_DefArrDA() <= 0) return 0;
   if (LL_DefParInit() <= 0) return 0;
   return 1;
}
int PSyntax::LL_DefParArr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefParArr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefPar --------------------
int PSyntax::LL_DefPar_0()
{
   int s_ret;
   if ((s_ret = LL_DefParArr()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_DefPar_1()
{
   int s_ret;
   if ((s_ret = LL_DefParVar()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_DefPar()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefPar_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefPar_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefParItem --------------------
int PSyntax::LL_DefParItem_0()
{
   int s_ret;
   if ((s_ret = LL_DefPar()) <= 0) return s_ret;
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::LL_DefParItem()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefParItem_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefParList --------------------
int PSyntax::LL_DefParList_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return -1;
   if (LL_DefParItem() <= 0) return 0;
   return 1;
}
int PSyntax::LL_DefParList()
{
   int p_ret;
   while ((p_ret = LL_DefParList_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_DefParams --------------------
int PSyntax::LL_DefParams_0()
{
   int s_ret;
   PARAM_TREE(Define,2);
   if ((s_ret = LL_DefParItem()) <= 0) return s_ret;
   if (LL_DefParList() <= 0) return 0;
   MAKE_TREE(EndParams);
   return 1;
}
int PSyntax::LL_DefParams()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefParams_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_BodyFunc --------------------
int PSyntax::LL_BodyFunc_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return -1;
   MAKE(BodyFunc);
   return 1;
}
int PSyntax::LL_BodyFunc_1()
{
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) return -1;
   PARAM(BodyFunc,1);
   return 1;
}
int PSyntax::LL_BodyFunc_2()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) return -1;
   MAKE_CODE(EndParams);
   if (LL_StmExpr() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) return 0;
   PARAM(BodyFunc,2);
   return 1;
}
int PSyntax::LL_BodyFunc()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_BodyFunc_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_BodyFunc_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_BodyFunc_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -3) ? -1 : 0);
}

// -------------------- LL_DefFunc_ --------------------
int PSyntax::LL_DefFunc__0()
{
   if (!Match(T_Lexeme::T_Syntax::sxEmptyBracket)) return -1;
   PARAM_TREE(EndParams,2);
   return 1;
}
int PSyntax::LL_DefFunc__1()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return -1;
   if (LL_DefParams() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   return 1;
}
int PSyntax::LL_DefFunc_()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefFunc__0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefFunc__1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefFunc --------------------
int PSyntax::LL_DefFunc_0()
{
   if (!Match(T_Lexeme::T_Syntax::sxDefFunc)) return -1;
   if (!Match(T_Lexeme::T_Syntax::sxIdentFunc)) return 0;
   MAKE(FuncIdent);
   if (LL_DefFunc_() <= 0) return 0;
   if (LL_BodyFunc() <= 0) return 0;
   return 1;
}
int PSyntax::LL_DefFunc()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefFunc_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_AInitialList --------------------
int PSyntax::LL_AInitialList_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return -1;
   if (LL_AInitItem() <= 0) return 0;
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::LL_AInitialList()
{
   int p_ret;
   while ((p_ret = LL_AInitialList_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_AInitial --------------------
int PSyntax::LL_AInitial_0()
{
   int s_ret;
   if ((s_ret = LL_AInitItem()) <= 0) return s_ret;
   MAKE_TREE(AddToList);
   if (LL_AInitialList() <= 0) return 0;
   return 1;
}
int PSyntax::LL_AInitial()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_AInitial_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Initializer --------------------
int PSyntax::LL_Initializer_0()
{
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) return -1;
   MAKE_CODE(BegInitial);
   MAKE_TREE(NodeListLL);
   return 1;
}
int PSyntax::LL_Initializer_1()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) return -1;
   PARAM_CODE(BegInitial,1);
   MAKE_TREE(NodeListLL);
   if (LL_AInitial() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) return 0;
   MAKE_CODE(EndInitial);
   return 1;
}
int PSyntax::LL_Initializer()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Initializer_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Initializer_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_AInitItem --------------------
int PSyntax::LL_AInitItem_0()
{
   int s_ret;
   if ((s_ret = LL_Initializer()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_AInitItem_1()
{
   int s_ret;
   if ((s_ret = LL_Assign()) <= 0) return s_ret;
   MAKE_CODE(AInitItem);
   return 1;
}
int PSyntax::LL_AInitItem()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_AInitItem_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_AInitItem_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefAInit --------------------
int PSyntax::LL_DefAInit_0()
{
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) return -1;
   MAKE_CODE(BegAInit);
   if (LL_Initializer() <= 0) return 0;
   MAKE(EndAInit);
   return 1;
}
int PSyntax::LL_DefAInit_1()
{
   return 1;
}
int PSyntax::LL_DefAInit()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefAInit_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefAInit_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DRanges --------------------
int PSyntax::LL_DRanges_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) return -1;
   if (LL_Assign() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) return 0;
   MAKE(DRange);
   return 1;
}
int PSyntax::LL_DRanges()
{
   int p_ret;
   while ((p_ret = LL_DRanges_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_DefArrD1A --------------------
int PSyntax::LL_DefArrD1A_0()
{
   if (!Match(T_Lexeme::T_Syntax::sxEmptyScrape)) return -1;
   MAKE(DefArrD1AEmpty);
   return 1;
}
int PSyntax::LL_DefArrD1A_1()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) return -1;
   if (LL_Assign() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) return 0;
   MAKE(DRange);
   return 1;
}
int PSyntax::LL_DefArrD1A()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefArrD1A_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefArrD1A_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefArrDA --------------------
int PSyntax::LL_DefArrDA_0()
{
   int s_ret;
   if ((s_ret = LL_DefArrD1A()) <= 0) return s_ret;
   if (LL_DRanges() <= 0) return 0;
   MAKE_CODE(EndRanges);
   return 1;
}
int PSyntax::LL_DefArrDA()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefArrDA_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefArr --------------------
int PSyntax::LL_DefArr_0()
{
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) return -1;
   MAKE(DefArray);
   if (LL_DefArrDA() <= 0) return 0;
   if (LL_DefAInit() <= 0) return 0;
   return 1;
}
int PSyntax::LL_DefArr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefArr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefVarAssign --------------------
int PSyntax::LL_DefVarAssign_0()
{
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) return -1;
   MAKE_CODE(BegDefVarAssign);
   if (LL_Assign() <= 0) return 0;
   MAKE(DefVarAssign);
   return 1;
}
int PSyntax::LL_DefVarAssign()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefVarAssign_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefVarInit --------------------
int PSyntax::LL_DefVarInit_0()
{
   int s_ret;
   if ((s_ret = LL_DefVarAssign()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_DefVarInit_1()
{
   return 1;
}
int PSyntax::LL_DefVarInit()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefVarInit_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefVarInit_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefVar --------------------
int PSyntax::LL_DefVar_0()
{
   if (!Match(T_Lexeme::T_Group::grIdent)) return -1;
   MAKE(DefIdent);
   if (LL_DefVarInit() <= 0) return 0;
   return 1;
}
int PSyntax::LL_DefVar()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefVar_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefIAV --------------------
int PSyntax::LL_DefIAV_0()
{
   int s_ret;
   if ((s_ret = LL_DefArr()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_DefIAV_1()
{
   int s_ret;
   if ((s_ret = LL_DefVar()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_DefIAV()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefIAV_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefIAV_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefItem --------------------
int PSyntax::LL_DefItem_0()
{
   if (!Match(T_Symbol::T_Priority::prAnd)) return -1;
   if (LL_DefIAV() <= 0) return 0;
   MAKE_TREE(RefDef);
   return 1;
}
int PSyntax::LL_DefItem_1()
{
   int s_ret;
   if ((s_ret = LL_DefIAV()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_DefItem()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefItem_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefItem_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefType --------------------
int PSyntax::LL_DefType_0()
{
   if (!Match(T_Lexeme::T_Syntax::sxDefArr)) return -1;
   return 1;
}
int PSyntax::LL_DefType_1()
{
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) return -1;
   return 1;
}
int PSyntax::LL_DefType()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefType_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefType_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_DefineList --------------------
int PSyntax::LL_DefineList_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return -1;
   if (LL_DefItem() <= 0) return 0;
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::LL_DefineList()
{
   int p_ret;
   while ((p_ret = LL_DefineList_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_Define --------------------
int PSyntax::LL_Define_0()
{
   int s_ret;
   if ((s_ret = LL_DefType()) <= 0) return s_ret;
   MAKE(Define);
   if (LL_DefItem() <= 0) return 0;
   MAKE_TREE(AddToList);
   if (LL_DefineList() <= 0) return 0;
   MAKE_CODE(EndDefine);
   return 1;
}
int PSyntax::LL_Define()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Define_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ConditionDef --------------------
int PSyntax::LL_ConditionDef_0()
{
   if (!Match(T_Symbol::T_Priority::prAnd)) return -1;
   if (LL_DefVar() <= 0) return 0;
   MAKE_TREE(RefDef);
   return 1;
}
int PSyntax::LL_ConditionDef_1()
{
   int s_ret;
   if ((s_ret = LL_DefVar()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_ConditionDef()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ConditionDef_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ConditionDef_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_Condition --------------------
int PSyntax::LL_Condition_0()
{
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) return -1;
   MAKE(Define);
   if (LL_ConditionDef() <= 0) return 0;
   MAKE(PushDef);
   return 1;
}
int PSyntax::LL_Condition_1()
{
   int s_ret;
   if ((s_ret = LL_ExpressionCondition()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_Condition()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Condition_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Condition_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_ExprList --------------------
int PSyntax::LL_ExprList_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return -1;
   if (LL_Assign() <= 0) return 0;
   MAKE_TREE(AddToList);
   MAKE_CODE(AddToExpr);
   return 1;
}
int PSyntax::LL_ExprList()
{
   int p_ret;
   while ((p_ret = LL_ExprList_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_Expressions --------------------
int PSyntax::LL_Expressions_0()
{
   int s_ret;
   if ((s_ret = LL_Assign()) <= 0) return s_ret;
   MAKE(ExpressionsLL);
   if (LL_ExprList() <= 0) return 0;
   MAKE_CODE(ExpressionSLL);
   return 1;
}
int PSyntax::LL_Expressions()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Expressions_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_PriorAssign --------------------
int PSyntax::LL_PriorAssign_0()
{
   if (!Match(T_Symbol::T_Priority::prAssign)) return -1;
   return 1;
}
int PSyntax::LL_PriorAssign()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_PriorAssign_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_AssignList --------------------
int PSyntax::LL_AssignList_0()
{
   int s_ret;
   if ((s_ret = LL_PriorAssign()) <= 0) return s_ret;
   if (LL_Assign() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::LL_AssignList_1()
{
   return 1;
}
int PSyntax::LL_AssignList()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_AssignList_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_AssignList_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_Assign --------------------
int PSyntax::LL_Assign_0()
{
   int s_ret;
   if ((s_ret = LL_Question()) <= 0) return s_ret;
   if (LL_AssignList() <= 0) return 0;
   return 1;
}
int PSyntax::LL_Assign()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Assign_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_QuestionList --------------------
int PSyntax::LL_QuestionList_0()
{
   if (!Match(T_Symbol::T_Priority::prQuestion)) return -1;
   MAKE_CODE(BegQuestion);
   if (LL_ExpressionValue() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxColon)) return 0;
   MAKE_CODE(MidQuestion);
   if (LL_Question() <= 0) return 0;
   MAKE(Question);
   return 1;
}
int PSyntax::LL_QuestionList_1()
{
   return 1;
}
int PSyntax::LL_QuestionList()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_QuestionList_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_QuestionList_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_Question --------------------
int PSyntax::LL_Question_0()
{
   int s_ret;
   if ((s_ret = LL_OrOr()) <= 0) return s_ret;
   if (LL_QuestionList() <= 0) return 0;
   return 1;
}
int PSyntax::LL_Question()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Question_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_OrOr --------------------
int PSyntax::LL_OrOr_0()
{
   int s_ret;
   if ((s_ret = LL_AndAnd()) <= 0) return s_ret;
   if (LL_OrOr_() <= 0) return 0;
   return 1;
}
int PSyntax::LL_OrOr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_OrOr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_OrOr_ --------------------
int PSyntax::LL_OrOr__0()
{
   if (!Match(T_Symbol::T_Priority::prOrOr)) return -1;
   if (LL_AndAnd() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::LL_OrOr_()
{
   int p_ret;
   while ((p_ret = LL_OrOr__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_AndAnd --------------------
int PSyntax::LL_AndAnd_0()
{
   int s_ret;
   if ((s_ret = LL_Or()) <= 0) return s_ret;
   if (LL_AndAnd_() <= 0) return 0;
   return 1;
}
int PSyntax::LL_AndAnd()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_AndAnd_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_AndAnd_ --------------------
int PSyntax::LL_AndAnd__0()
{
   if (!Match(T_Symbol::T_Priority::prAndAnd)) return -1;
   if (LL_Or() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::LL_AndAnd_()
{
   int p_ret;
   while ((p_ret = LL_AndAnd__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_Or --------------------
int PSyntax::LL_Or_0()
{
   int s_ret;
   if ((s_ret = LL_XOr()) <= 0) return s_ret;
   if (LL_Or_() <= 0) return 0;
   return 1;
}
int PSyntax::LL_Or()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Or_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Or_ --------------------
int PSyntax::LL_Or__0()
{
   if (!Match(T_Symbol::T_Priority::prOr)) return -1;
   if (LL_XOr() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::LL_Or_()
{
   int p_ret;
   while ((p_ret = LL_Or__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_XOr --------------------
int PSyntax::LL_XOr_0()
{
   int s_ret;
   if ((s_ret = LL_And()) <= 0) return s_ret;
   if (LL_XOr_() <= 0) return 0;
   return 1;
}
int PSyntax::LL_XOr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_XOr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_XOr_ --------------------
int PSyntax::LL_XOr__0()
{
   if (!Match(T_Symbol::T_Priority::prXOr)) return -1;
   if (LL_And() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::LL_XOr_()
{
   int p_ret;
   while ((p_ret = LL_XOr__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_And --------------------
int PSyntax::LL_And_0()
{
   int s_ret;
   if ((s_ret = LL_Equ()) <= 0) return s_ret;
   if (LL_And_() <= 0) return 0;
   return 1;
}
int PSyntax::LL_And()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_And_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_And_ --------------------
int PSyntax::LL_And__0()
{
   if (!Match(T_Symbol::T_Priority::prAnd)) return -1;
   if (LL_Equ() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::LL_And_()
{
   int p_ret;
   while ((p_ret = LL_And__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_Equ --------------------
int PSyntax::LL_Equ_0()
{
   int s_ret;
   if ((s_ret = LL_Compare()) <= 0) return s_ret;
   if (LL_Equ_() <= 0) return 0;
   return 1;
}
int PSyntax::LL_Equ()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Equ_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Equ_ --------------------
int PSyntax::LL_Equ__0()
{
   if (!Match(T_Symbol::T_Priority::prEqu)) return -1;
   if (LL_Compare() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::LL_Equ_()
{
   int p_ret;
   while ((p_ret = LL_Equ__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_Compare --------------------
int PSyntax::LL_Compare_0()
{
   int s_ret;
   if ((s_ret = LL_Shift()) <= 0) return s_ret;
   if (LL_Compare_() <= 0) return 0;
   return 1;
}
int PSyntax::LL_Compare()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Compare_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Compare_ --------------------
int PSyntax::LL_Compare__0()
{
   if (!Match(T_Symbol::T_Priority::prCompare)) return -1;
   if (LL_Shift() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::LL_Compare_()
{
   int p_ret;
   while ((p_ret = LL_Compare__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_Shift --------------------
int PSyntax::LL_Shift_0()
{
   int s_ret;
   if ((s_ret = LL_Term()) <= 0) return s_ret;
   if (LL_Shift_() <= 0) return 0;
   return 1;
}
int PSyntax::LL_Shift()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Shift_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Shift_ --------------------
int PSyntax::LL_Shift__0()
{
   if (!Match(T_Symbol::T_Priority::prShift)) return -1;
   if (LL_Term() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::LL_Shift_()
{
   int p_ret;
   while ((p_ret = LL_Shift__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_Term --------------------
int PSyntax::LL_Term_0()
{
   int s_ret;
   if ((s_ret = LL_Factor()) <= 0) return s_ret;
   if (LL_Term_() <= 0) return 0;
   return 1;
}
int PSyntax::LL_Term()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Term_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Term_ --------------------
int PSyntax::LL_Term__0()
{
   if (!Match(T_Symbol::T_Priority::prTerm)) return -1;
   if (LL_Factor() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::LL_Term_()
{
   int p_ret;
   while ((p_ret = LL_Term__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_Factor --------------------
int PSyntax::LL_Factor_0()
{
   int s_ret;
   if ((s_ret = LL_Unary()) <= 0) return s_ret;
   if (LL_Factor_() <= 0) return 0;
   return 1;
}
int PSyntax::LL_Factor()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Factor_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Factor_ --------------------
int PSyntax::LL_Factor__0()
{
   if (!Match(T_Symbol::T_Priority::prFactor)) return -1;
   if (LL_Unary() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::LL_Factor_()
{
   int p_ret;
   while ((p_ret = LL_Factor__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_UnaryIncDec --------------------
int PSyntax::LL_UnaryIncDec_0()
{
   if (!Match(T_Symbol::T_Priority::prIncDec)) return -1;
   MAKE(IncDec);
   return 1;
}
int PSyntax::LL_UnaryIncDec_1()
{
   return 1;
}
int PSyntax::LL_UnaryIncDec()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_UnaryIncDec_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_UnaryIncDec_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_Unary --------------------
int PSyntax::LL_Unary_0()
{
   if (!Match(T_Symbol::T_Priority::prUnary)) return -1;
   if (LL_Unary() <= 0) return 0;
   MAKE(Unary);
   return 1;
}
int PSyntax::LL_Unary_1()
{
   if (!Match(T_Symbol::T_Priority::prTerm)) return -1;
   if (LL_Unary() <= 0) return 0;
   MAKE(Unary);
   return 1;
}
int PSyntax::LL_Unary_2()
{
   if (!Match(T_Symbol::T_Priority::prIncDec)) return -1;
   if (LL_Unary() <= 0) return 0;
   MAKE(Unary);
   return 1;
}
int PSyntax::LL_Unary_3()
{
   if (!Match(T_Lexeme::T_Syntax::sxCastUnary)) return -1;
   if (LL_Unary() <= 0) return 0;
   MAKE(Cast);
   return 1;
}
int PSyntax::LL_Unary_4()
{
   int s_ret;
   if ((s_ret = LL_PrimaryExpr()) <= 0) return s_ret;
   if (LL_UnaryIncDec() <= 0) return 0;
   return 1;
}
int PSyntax::LL_Unary()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Unary_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Unary_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Unary_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Unary_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Unary_4()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -5) ? -1 : 0);
}

// -------------------- LL_Primary --------------------
int PSyntax::LL_Primary_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return -1;
   if (LL_ExpressionNone() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   MAKE_TREE(Primary);
   return 1;
}
int PSyntax::LL_Primary()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Primary_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_PrimaryExpr --------------------
int PSyntax::LL_PrimaryExpr_0()
{
   if (!Match(T_Lexeme::T_Group::grInteger)) return -1;
   MAKE(Number);
   return 1;
}
int PSyntax::LL_PrimaryExpr_1()
{
   if (!Match(T_Lexeme::T_Group::grNumber)) return -1;
   MAKE(Number);
   return 1;
}
int PSyntax::LL_PrimaryExpr_2()
{
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) return -1;
   if (LL_Ranges() <= 0) return 0;
   return 1;
}
int PSyntax::LL_PrimaryExpr_3()
{
   if (!Match(T_Lexeme::T_Syntax::sxIdentFunc)) return -1;
   if (LL_CallParams() <= 0) return 0;
   return 1;
}
int PSyntax::LL_PrimaryExpr_4()
{
   if (!Match(T_Lexeme::T_Syntax::sxCast)) return -1;
   if (LL_Primary() <= 0) return 0;
   MAKE(Cast);
   return 1;
}
int PSyntax::LL_PrimaryExpr_5()
{
   if (!Match(T_Lexeme::T_Group::grIdent)) return -1;
   MAKE(Ident);
   return 1;
}
int PSyntax::LL_PrimaryExpr_6()
{
   int s_ret;
   if ((s_ret = LL_Primary()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_PrimaryExpr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_PrimaryExpr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_4()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_5()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_PrimaryExpr_6()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -7) ? -1 : 0);
}

// -------------------- LL_RangesList --------------------
int PSyntax::LL_RangesList_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) return -1;
   if (LL_ExpressionValue() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) return 0;
   MAKE(IndexLL);
   return 1;
}
int PSyntax::LL_RangesList()
{
   int p_ret;
   while ((p_ret = LL_RangesList_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_Ranges --------------------
int PSyntax::LL_Ranges_0()
{
   int s_ret;
   MAKE(BegIndexLL);
   if ((s_ret = LL_RangesList()) <= 0) return s_ret;
   MAKE(EndIndex);
   return 1;
}
int PSyntax::LL_Ranges()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Ranges_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_CallParams --------------------
int PSyntax::LL_CallParams_0()
{
   if (!Match(T_Lexeme::T_Syntax::sxEmptyBracket)) return -1;
   MAKE(Params);
   return 1;
}
int PSyntax::LL_CallParams_1()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return -1;
   if (LL_ExpressionValueList() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   PARAM(Params,1);
   return 1;
}
int PSyntax::LL_CallParams()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_CallParams_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_CallParams_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_CompaundStmnt --------------------
int PSyntax::LL_CompaundStmnt_0()
{
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) return -1;
   MAKE(Compaund);
   MAKE_CODE(EndBlock);
   return 1;
}
int PSyntax::LL_CompaundStmnt_1()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) return -1;
   MAKE(Compaund);
   if (LL_StmExpr() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) return 0;
   MAKE_CODE(EndBlock);
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::LL_CompaundStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_CompaundStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_CompaundStmnt_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_IfStmnt_ --------------------
int PSyntax::LL_IfStmnt__0()
{
   if (!Match(T_Lexeme::W_Type::rwElse)) return -1;
   MAKE_CODE(Else);
   if (LL_DefExpr() <= 0) return 0;
   PARAM(If,1);
   return 1;
}
int PSyntax::LL_IfStmnt__1()
{
   MAKE(If);
   return 1;
}
int PSyntax::LL_IfStmnt_()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_IfStmnt__0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_IfStmnt__1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_IfStmnt --------------------
int PSyntax::LL_IfStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwIf)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   MAKE_CODE(BegIf);
   if (LL_Condition() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   MAKE_CODE(Then);
   if (LL_DefExpr() <= 0) return 0;
   if (LL_IfStmnt_() <= 0) return 0;
   return 1;
}
int PSyntax::LL_IfStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_IfStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ForPrefix --------------------
int PSyntax::LL_ForPrefix_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return -1;
   MAKE_TREE(NodeNull);
   return 1;
}
int PSyntax::LL_ForPrefix_1()
{
   int s_ret;
   if ((s_ret = LL_DefineSemi()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_ForPrefix_2()
{
   int s_ret;
   if ((s_ret = LL_ExprSemi()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_ForPrefix()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ForPrefix_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ForPrefix_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ForPrefix_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -3) ? -1 : 0);
}

// -------------------- LL_ForCondition --------------------
int PSyntax::LL_ForCondition_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return -1;
   MAKE(NodeNull);
   return 1;
}
int PSyntax::LL_ForCondition_1()
{
   int s_ret;
   if ((s_ret = LL_Condition()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   return 1;
}
int PSyntax::LL_ForCondition()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ForCondition_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ForCondition_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_ForPosfix --------------------
int PSyntax::LL_ForPosfix_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return -1;
   MAKE_TREE(NodeNull);
   return 1;
}
int PSyntax::LL_ForPosfix_1()
{
   int s_ret;
   if ((s_ret = LL_ExpressionExpression()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   return 1;
}
int PSyntax::LL_ForPosfix()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ForPosfix_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ForPosfix_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_ForStmnt --------------------
int PSyntax::LL_ForStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwFor)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   MAKE(BegFor);
   if (LL_ForPrefix() <= 0) return 0;
   MAKE_CODE(PrefFor);
   if (LL_ForCondition() <= 0) return 0;
   MAKE_CODE(ConditionFor);
   if (LL_ForPosfix() <= 0) return 0;
   MAKE_CODE(PostFor);
   if (LL_DefExpr() <= 0) return 0;
   MAKE(For);
   return 1;
}
int PSyntax::LL_ForStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ForStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DoStmnt --------------------
int PSyntax::LL_DoStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwDo)) return -1;
   MAKE(BegDo);
   if (LL_DefExpr() <= 0) return 0;
   if (!Match(T_Lexeme::W_Type::rwWhile)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   MAKE_CODE(MidDo);
   if (LL_Condition() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   MAKE(Do);
   return 1;
}
int PSyntax::LL_DoStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DoStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_WhileStmnt --------------------
int PSyntax::LL_WhileStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwWhile)) return -1;
   MAKE(BegWhile);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (LL_Condition() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   MAKE_CODE(MidWhile);
   if (LL_DefExpr() <= 0) return 0;
   MAKE(While);
   return 1;
}
int PSyntax::LL_WhileStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_WhileStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_GoToStmnt --------------------
int PSyntax::LL_GoToStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwGoTo)) return -1;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   MAKE(GoTo);
   return 1;
}
int PSyntax::LL_GoToStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_GoToStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_BreakStmnt --------------------
int PSyntax::LL_BreakStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwBreak)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   MAKE(Break);
   return 1;
}
int PSyntax::LL_BreakStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_BreakStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ContinueStmnt --------------------
int PSyntax::LL_ContinueStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwContinue)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   MAKE(Continue);
   return 1;
}
int PSyntax::LL_ContinueStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ContinueStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ReturnVal --------------------
int PSyntax::LL_ReturnVal_0()
{
   int s_ret;
   if ((s_ret = LL_ExpressionValue()) <= 0) return s_ret;
   PARAM(Return,1);
   return 1;
}
int PSyntax::LL_ReturnVal_1()
{
   MAKE(Return);
   return 1;
}
int PSyntax::LL_ReturnVal()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ReturnVal_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_ReturnVal_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- LL_ReturnStmnt --------------------
int PSyntax::LL_ReturnStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwReturn)) return -1;
   if (LL_ReturnVal() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   return 1;
}
int PSyntax::LL_ReturnStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ReturnStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_Statement --------------------
int PSyntax::LL_Statement_0()
{
   if (!Match(T_Lexeme::T_Syntax::sxLabel)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxColon)) return 0;
   MAKE_CODE(Label);
   if (LL_DefExpr() <= 0) return 0;
   MAKE_TREE(Label);
   return 1;
}
int PSyntax::LL_Statement_1()
{
   int s_ret;
   if ((s_ret = LL_IfStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_Statement_2()
{
   int s_ret;
   if ((s_ret = LL_DoStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_Statement_3()
{
   int s_ret;
   if ((s_ret = LL_WhileStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_Statement_4()
{
   int s_ret;
   if ((s_ret = LL_ForStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_Statement_5()
{
   int s_ret;
   if ((s_ret = LL_GoToStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_Statement_6()
{
   int s_ret;
   if ((s_ret = LL_BreakStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_Statement_7()
{
   int s_ret;
   if ((s_ret = LL_ContinueStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_Statement_8()
{
   int s_ret;
   if ((s_ret = LL_ReturnStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_Statement_9()
{
   int s_ret;
   if ((s_ret = LL_CompaundStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_Statement()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Statement_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_4()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_5()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_6()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_7()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_8()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_Statement_9()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -10) ? -1 : 0);
}

// -------------------- LL_DefineSemi --------------------
int PSyntax::LL_DefineSemi_0()
{
   int s_ret;
   if ((s_ret = LL_Define()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   return 1;
}
int PSyntax::LL_DefineSemi()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefineSemi_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExprSemi --------------------
int PSyntax::LL_ExprSemi_0()
{
   int s_ret;
   if ((s_ret = LL_ExpressionExpression()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   return 1;
}
int PSyntax::LL_ExprSemi()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExprSemi_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefExpr --------------------
int PSyntax::LL_DefExpr_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return -1;
   MAKE_TREE(NodeNull);
   return 1;
}
int PSyntax::LL_DefExpr_1()
{
   int s_ret;
   if ((s_ret = LL_DefineSemi()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_DefExpr_2()
{
   int s_ret;
   if ((s_ret = LL_Statement()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_DefExpr_3()
{
   int s_ret;
   if ((s_ret = LL_ExprSemi()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_DefExpr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefExpr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefExpr_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefExpr_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefExpr_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -4) ? -1 : 0);
}

// -------------------- LL_StmExprList --------------------
int PSyntax::LL_StmExprList_0()
{
   int s_ret;
   if ((s_ret = LL_DefExpr()) <= 0) return s_ret;
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::LL_StmExprList()
{
   int p_ret;
   while ((p_ret = LL_StmExprList_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_StmExpr --------------------
int PSyntax::LL_StmExpr_0()
{
   int s_ret;
   MAKE(BegStmExprLL);
   if ((s_ret = LL_StmExprList()) <= 0) return s_ret;
   MAKE_CODE(EndBlock);
   return 1;
}
int PSyntax::LL_StmExpr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_StmExpr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_DefFAV --------------------
int PSyntax::LL_DefFAV_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return -1;
   MAKE_TREE(NodeNull);
   return 1;
}
int PSyntax::LL_DefFAV_1()
{
   int s_ret;
   if ((s_ret = LL_DefFunc()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_DefFAV_2()
{
   int s_ret;
   if ((s_ret = LL_DefineSemi()) <= 0) return s_ret;
   return 1;
}
int PSyntax::LL_DefFAV()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_DefFAV_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefFAV_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = LL_DefFAV_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -3) ? -1 : 0);
}

// -------------------- LL_DefinesList --------------------
int PSyntax::LL_DefinesList_0()
{
   int s_ret;
   if ((s_ret = LL_DefFAV()) <= 0) return s_ret;
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::LL_DefinesList()
{
   int p_ret;
   while ((p_ret = LL_DefinesList_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- LL_Defines --------------------
int PSyntax::LL_Defines_0()
{
   int s_ret;
   MAKE(BegStmExprLL);
   if ((s_ret = LL_DefinesList()) <= 0) return s_ret;
   MAKE_CODE(EndBlock);
   return 1;
}
int PSyntax::LL_Defines()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_Defines_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExpressionExpression --------------------
int PSyntax::LL_ExpressionExpression_0()
{
   int s_ret;
   PARAM_CODE(Part,16);
   if ((s_ret = LL_Expressions()) <= 0) return s_ret;
   PARAM_TREE(ExpressionSLL,16);
   return 1;
}
int PSyntax::LL_ExpressionExpression()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExpressionExpression_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExpressionCondition --------------------
int PSyntax::LL_ExpressionCondition_0()
{
   int s_ret;
   PARAM_CODE(Part,241);
   if ((s_ret = LL_Expressions()) <= 0) return s_ret;
   PARAM_TREE(ExpressionSLL,241);
   return 1;
}
int PSyntax::LL_ExpressionCondition()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExpressionCondition_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExpressionNone --------------------
int PSyntax::LL_ExpressionNone_0()
{
   int s_ret;
   MAKE_CODE(Part);
   if ((s_ret = LL_Expressions()) <= 0) return s_ret;
   MAKE_TREE(ExpressionSLL);
   return 1;
}
int PSyntax::LL_ExpressionNone()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExpressionNone_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExpressionValue --------------------
int PSyntax::LL_ExpressionValue_0()
{
   int s_ret;
   PARAM_CODE(Part,256);
   if ((s_ret = LL_Expressions()) <= 0) return s_ret;
   PARAM_TREE(ExpressionSLL,256);
   return 1;
}
int PSyntax::LL_ExpressionValue()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExpressionValue_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- LL_ExpressionValueList --------------------
int PSyntax::LL_ExpressionValueList_0()
{
   int s_ret;
   PARAM_CODE(Part,512);
   if ((s_ret = LL_Expressions()) <= 0) return s_ret;
   PARAM_TREE(ExpressionSLL,512);
   return 1;
}
int PSyntax::LL_ExpressionValueList()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = LL_ExpressionValueList_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}
