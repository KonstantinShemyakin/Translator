
// -------------------- NL_S_ --------------------
int PSyntax::NL_S__0()
{
   int s_ret;
   if ((s_ret = NL_Program()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_S_()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_S__0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_Program --------------------
int PSyntax::NL_Program_0()
{
   int s_ret;
   if ((s_ret = NL_Defines()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Program()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Program_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_DefineParType --------------------
int PSyntax::NL_DefineParType_0()
{
   if (!Match(T_Lexeme::W_Type::rwConst)) return -1;
   if (!Match(T_Lexeme::W_Type::rwDefine)) return 0;
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAnd)) return 0;
   PARAM(DefType,11);
   return 1;
}
int PSyntax::NL_DefineParType_1()
{
   if (!Match(T_Lexeme::W_Type::rwDefine)) return -1;
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAnd)) return 0;
   PARAM(DefType,9);
   return 1;
}
int PSyntax::NL_DefineParType_2()
{
   if (!Match(T_Lexeme::W_Type::rwConst)) return -1;
   if (!Match(T_Lexeme::W_Type::rwDefine)) return 0;
   PARAM(DefType,3);
   return 1;
}
int PSyntax::NL_DefineParType_3()
{
   if (!Match(T_Lexeme::W_Type::rwDefine)) return -1;
   PARAM(DefType,1);
   return 1;
}
int PSyntax::NL_DefineParType()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefineParType_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefineParType_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefineParType_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefineParType_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -4) ? -1 : 0);
}

// -------------------- NL_DefParType --------------------
int PSyntax::NL_DefParType_0()
{
   int s_ret;
   if ((s_ret = NL_DefineParType()) <= 0) return s_ret;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   return 1;
}
int PSyntax::NL_DefParType()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefParType_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_DefPar --------------------
int PSyntax::NL_DefPar_0()
{
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) return -1;
   if (NL_Assign() <= 0) return 0;
   MAKE(ParVarAssign);
   return 1;
}
int PSyntax::NL_DefPar_1()
{
   return 1;
}
int PSyntax::NL_DefPar()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefPar_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefPar_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_DefParItem --------------------
int PSyntax::NL_DefParItem_0()
{
   int s_ret;
   if ((s_ret = NL_DefParType()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) return 0;
   MAKE(DefParArr);
   if (NL_DefArrDA() <= 0) return 0;
   if (NL_DefPar() <= 0) return 0;
   return 1;
}
int PSyntax::NL_DefParItem_1()
{
   int s_ret;
   if ((s_ret = NL_DefParType()) <= 0) return s_ret;
   MAKE(DefParVar);
   if (NL_DefPar() <= 0) return 0;
   return 1;
}
int PSyntax::NL_DefParItem()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefParItem_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefParItem_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_DefParamsList --------------------
int PSyntax::NL_DefParamsList_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return -1;
   if (NL_DefParItem() <= 0) return 0;
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::NL_DefParamsList()
{
   int p_ret;
   while ((p_ret = NL_DefParamsList_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_DefParams --------------------
int PSyntax::NL_DefParams_0()
{
   int s_ret;
   PARAM_TREE(Define,2);
   if ((s_ret = NL_DefParItem()) <= 0) return s_ret;
   MAKE_TREE(AddToList);
   if (NL_DefParamsList() <= 0) return 0;
   MAKE_TREE(EndParams);
   return 1;
}
int PSyntax::NL_DefParams()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefParams_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_BodyFunc --------------------
int PSyntax::NL_BodyFunc_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return -1;
   MAKE(BodyFunc);
   return 1;
}
int PSyntax::NL_BodyFunc_1()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) return 0;
   PARAM(BodyFunc,1);
   return 1;
}
int PSyntax::NL_BodyFunc_2()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) return -1;
   MAKE(BegStmExprLL);
   if (NL_StmExpr() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) return 0;
   PARAM(BodyFunc,2);
   return 1;
}
int PSyntax::NL_BodyFunc()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_BodyFunc_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_BodyFunc_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_BodyFunc_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -3) ? -1 : 0);
}

// -------------------- NL_DefFuncType --------------------
int PSyntax::NL_DefFuncType_0()
{
   if (!Match(T_Lexeme::W_Type::rwStatic)) return -1;
   if (!Match(T_Lexeme::W_Type::rwConst)) return 0;
   if (!Match(T_Lexeme::W_Type::rwDefine)) return 0;
   PARAM(DefType,7);
   return 1;
}
int PSyntax::NL_DefFuncType_1()
{
   if (!Match(T_Lexeme::W_Type::rwStatic)) return -1;
   if (!Match(T_Lexeme::W_Type::rwDefine)) return 0;
   PARAM(DefType,5);
   return 1;
}
int PSyntax::NL_DefFuncType_2()
{
   if (!Match(T_Lexeme::W_Type::rwConst)) return -1;
   if (!Match(T_Lexeme::W_Type::rwDefine)) return 0;
   PARAM(DefType,3);
   return 1;
}
int PSyntax::NL_DefFuncType_3()
{
   if (!Match(T_Lexeme::W_Type::rwDefine)) return -1;
   PARAM(DefType,1);
   return 1;
}
int PSyntax::NL_DefFuncType_4()
{
   if (!Match(T_Lexeme::W_Type::rwStatic)) return -1;
   if (!Match(T_Lexeme::W_Type::rwVoid)) return 0;
   PARAM(DefType,36);
   return 1;
}
int PSyntax::NL_DefFuncType_5()
{
   if (!Match(T_Lexeme::W_Type::rwVoid)) return -1;
   PARAM(DefType,32);
   return 1;
}
int PSyntax::NL_DefFuncType()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefFuncType_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefFuncType_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefFuncType_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefFuncType_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefFuncType_4()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefFuncType_5()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -6) ? -1 : 0);
}

// -------------------- NL_DefFuncParams --------------------
int PSyntax::NL_DefFuncParams_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return -1;
   PARAM_TREE(EndParams,2);
   return 1;
}
int PSyntax::NL_DefFuncParams_1()
{
   int s_ret;
   if ((s_ret = NL_DefParams()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   return 1;
}
int PSyntax::NL_DefFuncParams()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefFuncParams_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefFuncParams_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_DefFunc --------------------
int PSyntax::NL_DefFunc_0()
{
   int s_ret;
   if ((s_ret = NL_DefFuncType()) <= 0) return s_ret;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   MAKE(FuncIdent);
   if (NL_DefFuncParams() <= 0) return 0;
   if (NL_BodyFunc() <= 0) return 0;
   return 1;
}
int PSyntax::NL_DefFunc()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefFunc_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_AInitialList --------------------
int PSyntax::NL_AInitialList_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return -1;
   if (NL_AInitItem() <= 0) return 0;
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::NL_AInitialList()
{
   int p_ret;
   while ((p_ret = NL_AInitialList_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_AInitial --------------------
int PSyntax::NL_AInitial_0()
{
   int s_ret;
   if ((s_ret = NL_AInitItem()) <= 0) return s_ret;
   MAKE_TREE(AddToList);
   if (NL_AInitialList() <= 0) return 0;
   return 1;
}
int PSyntax::NL_AInitial()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_AInitial_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_Initializer --------------------
int PSyntax::NL_Initializer_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) return 0;
   MAKE_TREE(NodeListLL);
   return 1;
}
int PSyntax::NL_Initializer_1()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) return -1;
   MAKE_TREE(NodeListLL);
   if (NL_AInitial() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) return 0;
   return 1;
}
int PSyntax::NL_Initializer()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Initializer_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Initializer_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_AInitItem --------------------
int PSyntax::NL_AInitItem_0()
{
   int s_ret;
   if ((s_ret = NL_Initializer()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_AInitItem_1()
{
   int s_ret;
   if ((s_ret = NL_Assign()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_AInitItem()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_AInitItem_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_AInitItem_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_DefAInit --------------------
int PSyntax::NL_DefAInit_0()
{
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) return -1;
   if (NL_Initializer() <= 0) return 0;
   MAKE(EndAInit);
   return 1;
}
int PSyntax::NL_DefAInit_1()
{
   return 1;
}
int PSyntax::NL_DefAInit()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefAInit_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefAInit_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_DRanges --------------------
int PSyntax::NL_DRanges_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) return -1;
   if (NL_Assign() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) return 0;
   MAKE(DRange);
   return 1;
}
int PSyntax::NL_DRanges()
{
   int p_ret;
   while ((p_ret = NL_DRanges_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_DefArrD1A --------------------
int PSyntax::NL_DefArrD1A_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) return -1;
   MAKE(DefArrD1AEmpty);
   return 1;
}
int PSyntax::NL_DefArrD1A_1()
{
   int s_ret;
   if ((s_ret = NL_Assign()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) return 0;
   MAKE(DRange);
   return 1;
}
int PSyntax::NL_DefArrD1A()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefArrD1A_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefArrD1A_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_DefArrDA --------------------
int PSyntax::NL_DefArrDA_0()
{
   int s_ret;
   if ((s_ret = NL_DefArrD1A()) <= 0) return s_ret;
   if (NL_DRanges() <= 0) return 0;
   return 1;
}
int PSyntax::NL_DefArrDA()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefArrDA_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_DefArr --------------------
int PSyntax::NL_DefArr_0()
{
   if (!Match(T_Lexeme::T_Group::grIdent)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) return 0;
   MAKE(DefArray);
   if (NL_DefArrDA() <= 0) return 0;
   if (NL_DefAInit() <= 0) return 0;
   return 1;
}
int PSyntax::NL_DefArr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefArr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_DefVarInit --------------------
int PSyntax::NL_DefVarInit_0()
{
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) return -1;
   if (NL_Assign() <= 0) return 0;
   MAKE(DefVarAssign);
   return 1;
}
int PSyntax::NL_DefVarInit_1()
{
   return 1;
}
int PSyntax::NL_DefVarInit()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefVarInit_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefVarInit_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_DefVar --------------------
int PSyntax::NL_DefVar_0()
{
   if (!Match(T_Lexeme::T_Group::grIdent)) return -1;
   MAKE(DefIdent);
   if (NL_DefVarInit() <= 0) return 0;
   return 1;
}
int PSyntax::NL_DefVar()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefVar_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_DefItem --------------------
int PSyntax::NL_DefItem_0()
{
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAnd)) return -1;
   if (NL_DefArr() <= 0) return 0;
   MAKE_TREE(RefDef);
   return 1;
}
int PSyntax::NL_DefItem_1()
{
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAnd)) return -1;
   if (NL_DefVar() <= 0) return 0;
   MAKE_TREE(RefDef);
   return 1;
}
int PSyntax::NL_DefItem_2()
{
   int s_ret;
   if ((s_ret = NL_DefArr()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_DefItem_3()
{
   int s_ret;
   if ((s_ret = NL_DefVar()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_DefItem()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefItem_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefItem_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefItem_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefItem_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -4) ? -1 : 0);
}

// -------------------- NL_DefType --------------------
int PSyntax::NL_DefType_0()
{
   if (!Match(T_Lexeme::W_Type::rwStatic)) return -1;
   if (!Match(T_Lexeme::W_Type::rwConst)) return 0;
   if (!Match(T_Lexeme::W_Type::rwDefine)) return 0;
   PARAM(DefType,7);
   PARAM(Define,1);
   return 1;
}
int PSyntax::NL_DefType_1()
{
   if (!Match(T_Lexeme::W_Type::rwStatic)) return -1;
   if (!Match(T_Lexeme::W_Type::rwDefine)) return 0;
   PARAM(DefType,5);
   PARAM(Define,1);
   return 1;
}
int PSyntax::NL_DefType_2()
{
   if (!Match(T_Lexeme::W_Type::rwConst)) return -1;
   if (!Match(T_Lexeme::W_Type::rwDefine)) return 0;
   PARAM(DefType,3);
   PARAM(Define,1);
   return 1;
}
int PSyntax::NL_DefType_3()
{
   if (!Match(T_Lexeme::W_Type::rwDefine)) return -1;
   PARAM(DefType,1);
   PARAM(Define,1);
   return 1;
}
int PSyntax::NL_DefType()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefType_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefType_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefType_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefType_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -4) ? -1 : 0);
}

// -------------------- NL_DefineList --------------------
int PSyntax::NL_DefineList_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return -1;
   if (NL_DefItem() <= 0) return 0;
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::NL_DefineList()
{
   int p_ret;
   while ((p_ret = NL_DefineList_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_Define --------------------
int PSyntax::NL_Define_0()
{
   int s_ret;
   if ((s_ret = NL_DefType()) <= 0) return s_ret;
   if (NL_DefItem() <= 0) return 0;
   MAKE_TREE(AddToList);
   if (NL_DefineList() <= 0) return 0;
   return 1;
}
int PSyntax::NL_Define()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Define_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_ConditionVar --------------------
int PSyntax::NL_ConditionVar_0()
{
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAnd)) return -1;
   if (NL_DefVar() <= 0) return 0;
   MAKE_TREE(RefDef);
   return 1;
}
int PSyntax::NL_ConditionVar_1()
{
   int s_ret;
   if ((s_ret = NL_DefVar()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_ConditionVar()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ConditionVar_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_ConditionVar_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_Condition --------------------
int PSyntax::NL_Condition_0()
{
   int s_ret;
   if ((s_ret = NL_DefType()) <= 0) return s_ret;
   if (NL_ConditionVar() <= 0) return 0;
   MAKE(PushDef);
   return 1;
}
int PSyntax::NL_Condition_1()
{
   int s_ret;
   if ((s_ret = NL_ExpressionCondition()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Condition()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Condition_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Condition_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_ExpressionsList --------------------
int PSyntax::NL_ExpressionsList_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return -1;
   if (NL_Assign() <= 0) return 0;
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::NL_ExpressionsList()
{
   int p_ret;
   while ((p_ret = NL_ExpressionsList_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_Expressions --------------------
int PSyntax::NL_Expressions_0()
{
   int s_ret;
   if ((s_ret = NL_Assign()) <= 0) return s_ret;
   MAKE(ExpressionsLL);
   if (NL_ExpressionsList() <= 0) return 0;
   return 1;
}
int PSyntax::NL_Expressions()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Expressions_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_AssignList --------------------
int PSyntax::NL_AssignList_0()
{
   if (!Match(T_Symbol::T_Priority::prAssign)) return -1;
   if (NL_Assign() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::NL_AssignList_1()
{
   return 1;
}
int PSyntax::NL_AssignList()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_AssignList_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_AssignList_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_Assign --------------------
int PSyntax::NL_Assign_0()
{
   int s_ret;
   if ((s_ret = NL_Question()) <= 0) return s_ret;
   if (NL_AssignList() <= 0) return 0;
   return 1;
}
int PSyntax::NL_Assign()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Assign_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_QuestionList --------------------
int PSyntax::NL_QuestionList_0()
{
   if (!Match(T_Symbol::T_Priority::prQuestion)) return -1;
   if (NL_ExpressionValue() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxColon)) return 0;
   if (NL_Question() <= 0) return 0;
   MAKE(Question);
   return 1;
}
int PSyntax::NL_QuestionList_1()
{
   return 1;
}
int PSyntax::NL_QuestionList()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_QuestionList_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_QuestionList_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_Question --------------------
int PSyntax::NL_Question_0()
{
   int s_ret;
   if ((s_ret = NL_OrOr()) <= 0) return s_ret;
   if (NL_QuestionList() <= 0) return 0;
   return 1;
}
int PSyntax::NL_Question()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Question_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_OrOr --------------------
int PSyntax::NL_OrOr_0()
{
   int s_ret;
   if ((s_ret = NL_AndAnd()) <= 0) return s_ret;
   if (NL_OrOr_() <= 0) return 0;
   return 1;
}
int PSyntax::NL_OrOr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_OrOr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_OrOr_ --------------------
int PSyntax::NL_OrOr__0()
{
   if (!Match(T_Symbol::T_Priority::prOrOr)) return -1;
   if (NL_AndAnd() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::NL_OrOr_()
{
   int p_ret;
   while ((p_ret = NL_OrOr__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_AndAnd --------------------
int PSyntax::NL_AndAnd_0()
{
   int s_ret;
   if ((s_ret = NL_Or()) <= 0) return s_ret;
   if (NL_AndAnd_() <= 0) return 0;
   return 1;
}
int PSyntax::NL_AndAnd()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_AndAnd_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_AndAnd_ --------------------
int PSyntax::NL_AndAnd__0()
{
   if (!Match(T_Symbol::T_Priority::prAndAnd)) return -1;
   if (NL_Or() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::NL_AndAnd_()
{
   int p_ret;
   while ((p_ret = NL_AndAnd__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_Or --------------------
int PSyntax::NL_Or_0()
{
   int s_ret;
   if ((s_ret = NL_XOr()) <= 0) return s_ret;
   if (NL_Or_() <= 0) return 0;
   return 1;
}
int PSyntax::NL_Or()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Or_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_Or_ --------------------
int PSyntax::NL_Or__0()
{
   if (!Match(T_Symbol::T_Priority::prOr)) return -1;
   if (NL_XOr() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::NL_Or_()
{
   int p_ret;
   while ((p_ret = NL_Or__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_XOr --------------------
int PSyntax::NL_XOr_0()
{
   int s_ret;
   if ((s_ret = NL_And()) <= 0) return s_ret;
   if (NL_XOr_() <= 0) return 0;
   return 1;
}
int PSyntax::NL_XOr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_XOr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_XOr_ --------------------
int PSyntax::NL_XOr__0()
{
   if (!Match(T_Symbol::T_Priority::prXOr)) return -1;
   if (NL_And() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::NL_XOr_()
{
   int p_ret;
   while ((p_ret = NL_XOr__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_And --------------------
int PSyntax::NL_And_0()
{
   int s_ret;
   if ((s_ret = NL_Equ()) <= 0) return s_ret;
   if (NL_And_() <= 0) return 0;
   return 1;
}
int PSyntax::NL_And()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_And_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_And_ --------------------
int PSyntax::NL_And__0()
{
   if (!Match(T_Symbol::T_Priority::prAnd)) return -1;
   if (NL_Equ() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::NL_And_()
{
   int p_ret;
   while ((p_ret = NL_And__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_Equ --------------------
int PSyntax::NL_Equ_0()
{
   int s_ret;
   if ((s_ret = NL_Compare()) <= 0) return s_ret;
   if (NL_Equ_() <= 0) return 0;
   return 1;
}
int PSyntax::NL_Equ()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Equ_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_Equ_ --------------------
int PSyntax::NL_Equ__0()
{
   if (!Match(T_Symbol::T_Priority::prEqu)) return -1;
   if (NL_Compare() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::NL_Equ_()
{
   int p_ret;
   while ((p_ret = NL_Equ__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_Compare --------------------
int PSyntax::NL_Compare_0()
{
   int s_ret;
   if ((s_ret = NL_Shift()) <= 0) return s_ret;
   if (NL_Compare_() <= 0) return 0;
   return 1;
}
int PSyntax::NL_Compare()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Compare_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_Compare_ --------------------
int PSyntax::NL_Compare__0()
{
   if (!Match(T_Symbol::T_Priority::prCompare)) return -1;
   if (NL_Shift() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::NL_Compare_()
{
   int p_ret;
   while ((p_ret = NL_Compare__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_Shift --------------------
int PSyntax::NL_Shift_0()
{
   int s_ret;
   if ((s_ret = NL_Term()) <= 0) return s_ret;
   if (NL_Shift_() <= 0) return 0;
   return 1;
}
int PSyntax::NL_Shift()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Shift_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_Shift_ --------------------
int PSyntax::NL_Shift__0()
{
   if (!Match(T_Symbol::T_Priority::prShift)) return -1;
   if (NL_Term() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::NL_Shift_()
{
   int p_ret;
   while ((p_ret = NL_Shift__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_Term --------------------
int PSyntax::NL_Term_0()
{
   int s_ret;
   if ((s_ret = NL_Factor()) <= 0) return s_ret;
   if (NL_Term_() <= 0) return 0;
   return 1;
}
int PSyntax::NL_Term()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Term_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_Term_ --------------------
int PSyntax::NL_Term__0()
{
   if (!Match(T_Symbol::T_Priority::prTerm)) return -1;
   if (NL_Factor() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::NL_Term_()
{
   int p_ret;
   while ((p_ret = NL_Term__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_Factor --------------------
int PSyntax::NL_Factor_0()
{
   int s_ret;
   if ((s_ret = NL_Unary()) <= 0) return s_ret;
   if (NL_Factor_() <= 0) return 0;
   return 1;
}
int PSyntax::NL_Factor()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Factor_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_Factor_ --------------------
int PSyntax::NL_Factor__0()
{
   if (!Match(T_Symbol::T_Priority::prFactor)) return -1;
   if (NL_Unary() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::NL_Factor_()
{
   int p_ret;
   while ((p_ret = NL_Factor__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_UnaryIncDec --------------------
int PSyntax::NL_UnaryIncDec_0()
{
   if (!Match(T_Symbol::T_Priority::prIncDec)) return -1;
   MAKE(IncDec);
   return 1;
}
int PSyntax::NL_UnaryIncDec()
{
   int p_ret;
   while ((p_ret = NL_UnaryIncDec_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_DefineCast --------------------
int PSyntax::NL_DefineCast_0()
{
   if (!Match(T_Lexeme::W_Type::rwConst)) return -1;
   if (!Match(T_Lexeme::W_Type::rwDefine)) return 0;
   PARAM(DefType,3);
   return 1;
}
int PSyntax::NL_DefineCast_1()
{
   if (!Match(T_Lexeme::W_Type::rwDefine)) return -1;
   PARAM(DefType,1);
   return 1;
}
int PSyntax::NL_DefineCast()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefineCast_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefineCast_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_Unary --------------------
int PSyntax::NL_Unary_0()
{
   if (!Match(T_Symbol::T_Priority::prUnary)) return -1;
   if (NL_Unary() <= 0) return 0;
   MAKE(Unary);
   return 1;
}
int PSyntax::NL_Unary_1()
{
   if (!Match(T_Symbol::T_Priority::prTerm)) return -1;
   if (NL_Unary() <= 0) return 0;
   MAKE(Unary);
   return 1;
}
int PSyntax::NL_Unary_2()
{
   if (!Match(T_Symbol::T_Priority::prIncDec)) return -1;
   if (NL_Unary() <= 0) return 0;
   MAKE(Unary);
   return 1;
}
int PSyntax::NL_Unary_3()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return -1;
   if (NL_DefineCast() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (NL_Unary() <= 0) return 0;
   MAKE(Cast);
   return 1;
}
int PSyntax::NL_Unary_4()
{
   int s_ret;
   if ((s_ret = NL_PrimaryExpr()) <= 0) return s_ret;
   if (NL_UnaryIncDec() <= 0) return 0;
   return 1;
}
int PSyntax::NL_Unary()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Unary_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Unary_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Unary_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Unary_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Unary_4()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -5) ? -1 : 0);
}

// -------------------- NL_Primary --------------------
int PSyntax::NL_Primary_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return -1;
   if (NL_ExpressionNone() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   MAKE_TREE(Primary);
   return 1;
}
int PSyntax::NL_Primary()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Primary_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_PrimaryExpr --------------------
int PSyntax::NL_PrimaryExpr_0()
{
   if (!Match(T_Lexeme::T_Group::grIdent)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) return 0;
   if (NL_Ranges() <= 0) return 0;
   return 1;
}
int PSyntax::NL_PrimaryExpr_1()
{
   if (!Match(T_Lexeme::T_Group::grIdent)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (NL_CallParams() <= 0) return 0;
   return 1;
}
int PSyntax::NL_PrimaryExpr_2()
{
   if (!Match(T_Lexeme::T_Group::grInteger)) return -1;
   MAKE(Number);
   return 1;
}
int PSyntax::NL_PrimaryExpr_3()
{
   if (!Match(T_Lexeme::T_Group::grNumber)) return -1;
   MAKE(Number);
   return 1;
}
int PSyntax::NL_PrimaryExpr_4()
{
   if (!Match(T_Lexeme::T_Group::grIdent)) return -1;
   MAKE(Ident);
   return 1;
}
int PSyntax::NL_PrimaryExpr_5()
{
   int s_ret;
   if ((s_ret = NL_Primary()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_PrimaryExpr_6()
{
   if (!Match(T_Lexeme::W_Type::rwDefine)) return -1;
   if (NL_Primary() <= 0) return 0;
   MAKE(Cast);
   return 1;
}
int PSyntax::NL_PrimaryExpr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_PrimaryExpr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_PrimaryExpr_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_PrimaryExpr_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_PrimaryExpr_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_PrimaryExpr_4()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_PrimaryExpr_5()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_PrimaryExpr_6()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -7) ? -1 : 0);
}

// -------------------- NL_Range --------------------
int PSyntax::NL_Range_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) return -1;
   if (NL_ExpressionValue() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) return 0;
   MAKE(IndexLL);
   return 1;
}
int PSyntax::NL_Range()
{
   int p_ret;
   while ((p_ret = NL_Range_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_Ranges --------------------
int PSyntax::NL_Ranges_0()
{
   int s_ret;
   MAKE(BegIndexLL);
   if ((s_ret = NL_ExpressionValue()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) return 0;
   MAKE(IndexLL);
   if (NL_Range() <= 0) return 0;
   MAKE(EndIndex);
   return 1;
}
int PSyntax::NL_Ranges()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Ranges_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_CallParams --------------------
int PSyntax::NL_CallParams_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return -1;
   MAKE(Params);
   return 1;
}
int PSyntax::NL_CallParams_1()
{
   int s_ret;
   if ((s_ret = NL_ExpressionValueList()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   PARAM(Params,1);
   return 1;
}
int PSyntax::NL_CallParams()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_CallParams_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_CallParams_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_CompaundStmnt --------------------
int PSyntax::NL_CompaundStmnt_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) return 0;
   MAKE(Compaund);
   return 1;
}
int PSyntax::NL_CompaundStmnt_1()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) return -1;
   MAKE(Compaund);
   if (NL_StmExpr() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) return 0;
   return 1;
}
int PSyntax::NL_CompaundStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_CompaundStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_CompaundStmnt_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_IfStmntElse --------------------
int PSyntax::NL_IfStmntElse_0()
{
   if (!Match(T_Lexeme::W_Type::rwElse)) return -1;
   if (NL_DefExpr() <= 0) return 0;
   PARAM(If,1);
   return 1;
}
int PSyntax::NL_IfStmntElse_1()
{
   MAKE(If);
   return 1;
}
int PSyntax::NL_IfStmntElse()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_IfStmntElse_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_IfStmntElse_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_IfStmnt --------------------
int PSyntax::NL_IfStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwIf)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (NL_Condition() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (NL_DefExpr() <= 0) return 0;
   if (NL_IfStmntElse() <= 0) return 0;
   return 1;
}
int PSyntax::NL_IfStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_IfStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_ForPrefix --------------------
int PSyntax::NL_ForPrefix_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return -1;
   MAKE_TREE(NodeNull);
   return 1;
}
int PSyntax::NL_ForPrefix_1()
{
   int s_ret;
   if ((s_ret = NL_DefineSemi()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_ForPrefix_2()
{
   int s_ret;
   if ((s_ret = NL_ExprSemi()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_ForPrefix()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ForPrefix_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_ForPrefix_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_ForPrefix_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -3) ? -1 : 0);
}

// -------------------- NL_ForCondition --------------------
int PSyntax::NL_ForCondition_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return -1;
   MAKE(NodeNull);
   return 1;
}
int PSyntax::NL_ForCondition_1()
{
   int s_ret;
   if ((s_ret = NL_Condition()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   return 1;
}
int PSyntax::NL_ForCondition()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ForCondition_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_ForCondition_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_ForPostfix --------------------
int PSyntax::NL_ForPostfix_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return -1;
   MAKE_TREE(NodeNull);
   return 1;
}
int PSyntax::NL_ForPostfix_1()
{
   int s_ret;
   if ((s_ret = NL_ExpressionExpression()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   return 1;
}
int PSyntax::NL_ForPostfix()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ForPostfix_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_ForPostfix_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_ForStmnt --------------------
int PSyntax::NL_ForStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwFor)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   MAKE(BegFor);
   if (NL_ForPrefix() <= 0) return 0;
   if (NL_ForCondition() <= 0) return 0;
   if (NL_ForPostfix() <= 0) return 0;
   if (NL_DefExpr() <= 0) return 0;
   MAKE(For);
   return 1;
}
int PSyntax::NL_ForStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ForStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_DoStmnt --------------------
int PSyntax::NL_DoStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwDo)) return -1;
   MAKE(BegDo);
   if (NL_DefExpr() <= 0) return 0;
   if (!Match(T_Lexeme::W_Type::rwWhile)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (NL_Condition() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   MAKE(Do);
   return 1;
}
int PSyntax::NL_DoStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DoStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_WhileStmnt --------------------
int PSyntax::NL_WhileStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwWhile)) return -1;
   MAKE(BegWhile);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (NL_Condition() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (NL_DefExpr() <= 0) return 0;
   MAKE(While);
   return 1;
}
int PSyntax::NL_WhileStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_WhileStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_SwitchStmnt --------------------
int PSyntax::NL_SwitchStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwSwitch)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   return 1;
}
int PSyntax::NL_SwitchStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_SwitchStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_GoToStmnt --------------------
int PSyntax::NL_GoToStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwGoTo)) return -1;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   MAKE(GoTo);
   return 1;
}
int PSyntax::NL_GoToStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_GoToStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_BreakStmnt --------------------
int PSyntax::NL_BreakStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwBreak)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   MAKE(Break);
   return 1;
}
int PSyntax::NL_BreakStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_BreakStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_ContinueStmnt --------------------
int PSyntax::NL_ContinueStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwContinue)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   MAKE(Continue);
   return 1;
}
int PSyntax::NL_ContinueStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ContinueStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_ReturnValue --------------------
int PSyntax::NL_ReturnValue_0()
{
   int s_ret;
   if ((s_ret = NL_ExpressionValue()) <= 0) return s_ret;
   PARAM(Return,1);
   return 1;
}
int PSyntax::NL_ReturnValue_1()
{
   MAKE(Return);
   return 1;
}
int PSyntax::NL_ReturnValue()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ReturnValue_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_ReturnValue_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- NL_ReturnStmnt --------------------
int PSyntax::NL_ReturnStmnt_0()
{
   if (!Match(T_Lexeme::W_Type::rwReturn)) return -1;
   if (NL_ReturnValue() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   return 1;
}
int PSyntax::NL_ReturnStmnt()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ReturnStmnt_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_Statement --------------------
int PSyntax::NL_Statement_0()
{
   int s_ret;
   if ((s_ret = NL_IfStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Statement_1()
{
   int s_ret;
   if ((s_ret = NL_DoStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Statement_2()
{
   int s_ret;
   if ((s_ret = NL_WhileStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Statement_3()
{
   int s_ret;
   if ((s_ret = NL_ForStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Statement_4()
{
   int s_ret;
   if ((s_ret = NL_SwitchStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Statement_5()
{
   int s_ret;
   if ((s_ret = NL_GoToStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Statement_6()
{
   int s_ret;
   if ((s_ret = NL_BreakStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Statement_7()
{
   int s_ret;
   if ((s_ret = NL_ContinueStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Statement_8()
{
   int s_ret;
   if ((s_ret = NL_ReturnStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Statement_9()
{
   int s_ret;
   if ((s_ret = NL_CompaundStmnt()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Statement()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Statement_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Statement_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Statement_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Statement_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Statement_4()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Statement_5()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Statement_6()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Statement_7()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Statement_8()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_Statement_9()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -10) ? -1 : 0);
}

// -------------------- NL_DefineSemi --------------------
int PSyntax::NL_DefineSemi_0()
{
   int s_ret;
   if ((s_ret = NL_Define()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   return 1;
}
int PSyntax::NL_DefineSemi()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefineSemi_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_ExprSemi --------------------
int PSyntax::NL_ExprSemi_0()
{
   int s_ret;
   if ((s_ret = NL_ExpressionExpression()) <= 0) return s_ret;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   return 1;
}
int PSyntax::NL_ExprSemi()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ExprSemi_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_DefExpr --------------------
int PSyntax::NL_DefExpr_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return -1;
   MAKE_TREE(NodeNull);
   return 1;
}
int PSyntax::NL_DefExpr_1()
{
   if (!Match(T_Lexeme::T_Group::grIdent)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxColon)) return 0;
   if (NL_DefExpr() <= 0) return 0;
   MAKE_TREE(Label);
   return 1;
}
int PSyntax::NL_DefExpr_2()
{
   int s_ret;
   if ((s_ret = NL_DefineSemi()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_DefExpr_3()
{
   int s_ret;
   if ((s_ret = NL_Statement()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_DefExpr_4()
{
   int s_ret;
   if ((s_ret = NL_ExprSemi()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_DefExpr()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefExpr_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefExpr_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefExpr_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefExpr_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefExpr_4()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -5) ? -1 : 0);
}

// -------------------- NL_StmExpr --------------------
int PSyntax::NL_StmExpr_0()
{
   int s_ret;
   if ((s_ret = NL_DefExpr()) <= 0) return s_ret;
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::NL_StmExpr()
{
   int p_ret;
   while ((p_ret = NL_StmExpr_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_DefFAV --------------------
int PSyntax::NL_DefFAV_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return -1;
   MAKE_TREE(NodeNull);
   return 1;
}
int PSyntax::NL_DefFAV_1()
{
   int s_ret;
   if ((s_ret = NL_DefFunc()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_DefFAV_2()
{
   int s_ret;
   if ((s_ret = NL_DefineSemi()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_DefFAV()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_DefFAV_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefFAV_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = NL_DefFAV_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -3) ? -1 : 0);
}

// -------------------- NL_DefinesBeg --------------------
int PSyntax::NL_DefinesBeg_0()
{
   int s_ret;
   if ((s_ret = NL_DefFAV()) <= 0) return s_ret;
   MAKE_TREE(AddToList);
   return 1;
}
int PSyntax::NL_DefinesBeg()
{
   int p_ret;
   while ((p_ret = NL_DefinesBeg_0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- NL_Defines --------------------
int PSyntax::NL_Defines_0()
{
   int s_ret;
   MAKE(BegStmExprLL);
   if ((s_ret = NL_DefinesBeg()) <= 0) return s_ret;
   return 1;
}
int PSyntax::NL_Defines()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_Defines_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_ExpressionExpression --------------------
int PSyntax::NL_ExpressionExpression_0()
{
   int s_ret;
   if ((s_ret = NL_Expressions()) <= 0) return s_ret;
   PARAM_TREE(ExpressionSLL,16);
   return 1;
}
int PSyntax::NL_ExpressionExpression()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ExpressionExpression_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_ExpressionCondition --------------------
int PSyntax::NL_ExpressionCondition_0()
{
   int s_ret;
   if ((s_ret = NL_Expressions()) <= 0) return s_ret;
   PARAM_TREE(ExpressionSLL,241);
   return 1;
}
int PSyntax::NL_ExpressionCondition()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ExpressionCondition_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_ExpressionNone --------------------
int PSyntax::NL_ExpressionNone_0()
{
   int s_ret;
   if ((s_ret = NL_Expressions()) <= 0) return s_ret;
   MAKE_TREE(ExpressionSLL);
   return 1;
}
int PSyntax::NL_ExpressionNone()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ExpressionNone_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_ExpressionValue --------------------
int PSyntax::NL_ExpressionValue_0()
{
   int s_ret;
   if ((s_ret = NL_Expressions()) <= 0) return s_ret;
   PARAM_TREE(ExpressionSLL,256);
   return 1;
}
int PSyntax::NL_ExpressionValue()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ExpressionValue_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- NL_ExpressionValueList --------------------
int PSyntax::NL_ExpressionValueList_0()
{
   int s_ret;
   if ((s_ret = NL_Expressions()) <= 0) return s_ret;
   PARAM_TREE(ExpressionSLL,512);
   return 1;
}
int PSyntax::NL_ExpressionValueList()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = NL_ExpressionValueList_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}
