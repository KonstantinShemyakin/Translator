
// -------------------- S_ --------------------
int PSyntax::S__0()
{
   PRODUCE(S_,0)
   int s_ret;
   if ((s_ret = E()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::S_()
{
   FORMULA(S_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = S__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- E --------------------
int PSyntax::E_0()
{
   PRODUCE(E,0)
   int s_ret;
   if ((s_ret = T()) <= 0) RETURN (s_ret);
   if (E_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::E()
{
   FORMULA(E)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = E_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- E_ --------------------
int PSyntax::E__0()
{
   PRODUCE(E_,0)
   if (!Match(T_Symbol::T_Priority::prTerm)) RETURN (-1);
   if (T() <= 0) RETURN (0);
   if (E_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::E__1()
{
   PRODUCE(E_,1)
   RETURN (1);
}
int PSyntax::E_()
{
   FORMULA(E_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = E__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = E__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- T --------------------
int PSyntax::T_0()
{
   PRODUCE(T,0)
   int s_ret;
   if ((s_ret = F()) <= 0) RETURN (s_ret);
   if (T_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::T()
{
   FORMULA(T)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = T_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- T_ --------------------
int PSyntax::T__0()
{
   PRODUCE(T_,0)
   if (!Match(T_Symbol::T_Priority::prFactor)) RETURN (-1);
   if (F() <= 0) RETURN (0);
   if (T_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::T__1()
{
   PRODUCE(T_,1)
   RETURN (1);
}
int PSyntax::T_()
{
   FORMULA(T_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = T__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = T__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- F --------------------
int PSyntax::F_0()
{
   PRODUCE(F,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (-1);
   if (E() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   RETURN (1);
}
int PSyntax::F_1()
{
   PRODUCE(F,1)
   if (!Match(T_Lexeme::T_Group::grInteger)) RETURN (-1);
   RETURN (1);
}
int PSyntax::F_2()
{
   PRODUCE(F,2)
   if (!Match(T_Lexeme::T_Group::grNumber)) RETURN (-1);
   RETURN (1);
}
int PSyntax::F_3()
{
   PRODUCE(F,3)
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (-1);
   RETURN (1);
}
int PSyntax::F()
{
   FORMULA(F)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = F_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = F_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = F_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = F_3()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -4) ? -1 : 0);
}
