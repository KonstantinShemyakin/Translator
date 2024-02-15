
// -------------------- ETF_LL_S_ --------------------
int PSyntax::ETF_LL_S__0()
{
   int s_ret;
   if ((s_ret = ETF_LL__E()) <= 0) return s_ret;
   return 1;
}
int PSyntax::ETF_LL_S_()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = ETF_LL_S__0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- ETF_LL__E --------------------
int PSyntax::ETF_LL__E_0()
{
   int s_ret;
   MAKE(BegStmExprLL);
   if ((s_ret = ETF_LL_E()) <= 0) return s_ret;
   MAKE_TREE(AddToList);
   MAKE_CODE(EndBlock);
   return 1;
}
int PSyntax::ETF_LL__E()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = ETF_LL__E_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- ETF_LL_E_ --------------------
int PSyntax::ETF_LL_E__0()
{
   if (!Match(T_Symbol::T_Priority::prTerm)) return -1;
   if (ETF_LL_T() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::ETF_LL_E_()
{
   int p_ret;
   while ((p_ret = ETF_LL_E__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- ETF_LL_E --------------------
int PSyntax::ETF_LL_E_0()
{
   int s_ret;
   if ((s_ret = ETF_LL_T()) <= 0) return s_ret;
   if (ETF_LL_E_() <= 0) return 0;
   return 1;
}
int PSyntax::ETF_LL_E()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = ETF_LL_E_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- ETF_LL_T_ --------------------
int PSyntax::ETF_LL_T__0()
{
   if (!Match(T_Symbol::T_Priority::prFactor)) return -1;
   if (ETF_LL_F() <= 0) return 0;
   MAKE(Binary);
   return 1;
}
int PSyntax::ETF_LL_T_()
{
   int p_ret;
   while ((p_ret = ETF_LL_T__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- ETF_LL_T --------------------
int PSyntax::ETF_LL_T_0()
{
   int s_ret;
   if ((s_ret = ETF_LL_F()) <= 0) return s_ret;
   if (ETF_LL_T_() <= 0) return 0;
   return 1;
}
int PSyntax::ETF_LL_T()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = ETF_LL_T_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- ETF_LL_F --------------------
int PSyntax::ETF_LL_F_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return -1;
   if (ETF_LL_E() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   return 1;
}
int PSyntax::ETF_LL_F_1()
{
   if (!Match(T_Lexeme::T_Group::grInteger)) return -1;
   MAKE(Number);
   return 1;
}
int PSyntax::ETF_LL_F()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = ETF_LL_F_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = ETF_LL_F_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}
