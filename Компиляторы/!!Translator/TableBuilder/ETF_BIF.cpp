
// -------------------- S_ --------------------
int PSyntax::S__0()
{
   int s_ret;
   if ((s_ret = rules()) <= 0) return s_ret;
   return 1;
}
int PSyntax::S_()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = S__0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- rules --------------------
int PSyntax::rules_0()
{
   int s_ret;
   if ((s_ret = rule()) <= 0) return s_ret;
   if (_f_00002_() <= 0) return 0;
   return 1;
}
int PSyntax::rules()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = rules_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- _f_00002_ --------------------
int PSyntax::_f_00002__0()
{
   int s_ret;
   if ((s_ret = rule()) <= 0) return s_ret;
   return 1;
}
int PSyntax::_f_00002_()
{
   int p_ret;
   while ((p_ret = _f_00002__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- rule --------------------
int PSyntax::rule_0()
{
   if (!Match(T_Lexeme::T_Group::grSpace)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxBNFSet)) return 0;
   if (item_list() <= 0) return 0;
   return 1;
}
int PSyntax::rule()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = rule_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- item_list --------------------
int PSyntax::item_list_0()
{
   int s_ret;
   if ((s_ret = item_symbol()) <= 0) return s_ret;
   if (_f_00005_() <= 0) return 0;
   return 1;
}
int PSyntax::item_list()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = item_list_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- _f_00005_ --------------------
int PSyntax::_f_00005__0()
{
   int s_ret;
   if ((s_ret = item_symbol()) <= 0) return s_ret;
   return 1;
}
int PSyntax::_f_00005_()
{
   int p_ret;
   while ((p_ret = _f_00005__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- item_symbol --------------------
int PSyntax::item_symbol_0()
{
   if (!Match(T_Lexeme::T_Group::grSpace)) return -1;
   return 1;
}
int PSyntax::item_symbol_1()
{
   int s_ret;
   if ((s_ret = item()) <= 0) return s_ret;
   return 1;
}
int PSyntax::item_symbol()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = item_symbol_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = item_symbol_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- item --------------------
int PSyntax::item_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) return -1;
   if (or_list() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) return 0;
   return 1;
}
int PSyntax::item_1()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) return -1;
   if (or_list() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) return 0;
   if (!Match(T_Lexeme::T_Group::grMeta)) return 0;
   return 1;
}
int PSyntax::item_2()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) return -1;
   if (or_list() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) return 0;
   return 1;
}
int PSyntax::item_3()
{
   int s_ret;
   if ((s_ret = _f_00008_()) <= 0) return s_ret;
   return 1;
}
int PSyntax::item()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = item_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = item_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = item_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = item_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -4) ? -1 : 0);
}

// -------------------- _f_00008_ --------------------
int PSyntax::_f_00008__0()
{
   int s_ret;
   if ((s_ret = _f_00009_()) <= 0) return s_ret;
   return 1;
}
int PSyntax::_f_00008__1()
{
   int s_ret;
   if ((s_ret = _f_00010_()) <= 0) return s_ret;
   return 1;
}
int PSyntax::_f_00008__2()
{
   int s_ret;
   if ((s_ret = _f_00011_()) <= 0) return s_ret;
   return 1;
}
int PSyntax::_f_00008_()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = _f_00008__0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = _f_00008__1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = _f_00008__2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -3) ? -1 : 0);
}

// -------------------- _f_00009_ --------------------
int PSyntax::_f_00009__0()
{
   if (!Match(T_Lexeme::T_Group::grMeta)) return -1;
   if (Ident_Maker() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   if (!Match(T_Lexeme::T_Group::grMeta)) return 0;
   return 1;
}
int PSyntax::_f_00009__1()
{
   if (!Match(T_Lexeme::T_Group::grMeta)) return -1;
   if (Ident_Maker() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   if (!Match(T_Lexeme::T_Group::grMeta)) return 0;
   return 1;
}
int PSyntax::_f_00009_()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = _f_00009__0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = _f_00009__1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- _f_00010_ --------------------
int PSyntax::_f_00010__0()
{
   if (!Match(T_Lexeme::T_Group::grMeta)) return -1;
   if (!Match(T_Lexeme::W_Type::rwNode)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (node_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   if (!Match(T_Lexeme::T_Group::grMeta)) return 0;
   return 1;
}
int PSyntax::_f_00010__1()
{
   if (!Match(T_Lexeme::T_Group::grMeta)) return -1;
   if (!Match(T_Lexeme::W_Type::rwNode)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (node_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   if (!Match(T_Lexeme::T_Group::grMeta)) return 0;
   return 1;
}
int PSyntax::_f_00010_()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = _f_00010__0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = _f_00010__1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- _f_00011_ --------------------
int PSyntax::_f_00011__0()
{
   if (!Match(T_Lexeme::T_Group::grMeta)) return -1;
   if (!Match(T_Lexeme::W_Type::rwTurn)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   if (!Match(T_Lexeme::T_Group::grMeta)) return 0;
   return 1;
}
int PSyntax::_f_00011__1()
{
   if (!Match(T_Lexeme::T_Group::grMeta)) return -1;
   if (!Match(T_Lexeme::W_Type::rwTurn)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   if (!Match(T_Lexeme::T_Group::grMeta)) return 0;
   if (_f_00012_() <= 0) return 0;
   return 1;
}
int PSyntax::_f_00011_()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = _f_00011__0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = _f_00011__1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- _f_00012_ --------------------
int PSyntax::_f_00012__0()
{
   if (!Match(T_Lexeme::T_Group::grMeta)) return -1;
   if (!Match(T_Lexeme::W_Type::rwCall)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   if (!Match(T_Lexeme::T_Group::grMeta)) return 0;
   return 1;
}
int PSyntax::_f_00012__1()
{
   if (!Match(T_Lexeme::T_Group::grMeta)) return -1;
   if (!Match(T_Lexeme::W_Type::rwCall)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return 0;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) return 0;
   if (!Match(T_Lexeme::T_Group::grMeta)) return 0;
   return 1;
}
int PSyntax::_f_00012_()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = _f_00012__0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = _f_00012__1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -2) ? -1 : 0);
}

// -------------------- or_list --------------------
int PSyntax::or_list_0()
{
   int s_ret;
   if ((s_ret = item_list()) <= 0) return s_ret;
   if (_f_00014_() <= 0) return 0;
   return 1;
}
int PSyntax::or_list()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = or_list_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -1) ? -1 : 0);
}

// -------------------- _f_00014_ --------------------
int PSyntax::_f_00014__0()
{
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxOr)) return -1;
   if (item_list() <= 0) return 0;
   return 1;
}
int PSyntax::_f_00014_()
{
   int p_ret;
   while ((p_ret = _f_00014__0()) > 0);
   return (!p_ret ? 0 : 1);
}

// -------------------- Ident_Maker --------------------
int PSyntax::Ident_Maker_0()
{
   if (!Match(T_Lexeme::W_Type::rwAll)) return -1;
   return 1;
}
int PSyntax::Ident_Maker_1()
{
   if (!Match(T_Lexeme::W_Type::rwMake)) return -1;
   return 1;
}
int PSyntax::Ident_Maker_2()
{
   if (!Match(T_Lexeme::W_Type::rwCode)) return -1;
   return 1;
}
int PSyntax::Ident_Maker_3()
{
   if (!Match(T_Lexeme::W_Type::rwTree)) return -1;
   return 1;
}
int PSyntax::Ident_Maker_4()
{
   if (!Match(T_Lexeme::W_Type::rwYacc)) return -1;
   return 1;
}
int PSyntax::Ident_Maker()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = Ident_Maker_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = Ident_Maker_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = Ident_Maker_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = Ident_Maker_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = Ident_Maker_4()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -5) ? -1 : 0);
}

// -------------------- node_body --------------------
int PSyntax::node_body_0()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return -1;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   return 1;
}
int PSyntax::node_body_1()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return -1;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   return 1;
}
int PSyntax::node_body_2()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return -1;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   return 1;
}
int PSyntax::node_body_3()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return -1;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   return 1;
}
int PSyntax::node_body_4()
{
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) return -1;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) return 0;
   if (int_body() <= 0) return 0;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) return 0;
   return 1;
}
int PSyntax::node_body()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = node_body_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = node_body_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = node_body_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = node_body_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = node_body_4()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -5) ? -1 : 0);
}

// -------------------- int_body --------------------
int PSyntax::int_body_0()
{
   if (!Match(T_Lexeme::T_Group::grInteger)) return -1;
   return 1;
}
int PSyntax::int_body_1()
{
   if (!Match(T_Lexeme::T_Group::grIdent)) return -1;
   return 1;
}
int PSyntax::int_body_2()
{
   if (!Match(T_Lexeme::T_Group::grIdent)) return -1;
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxColonColon)) return 0;
   if (!Match(T_Lexeme::T_Group::grIdent)) return 0;
   return 1;
}
int PSyntax::int_body_3()
{
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxSub)) return -1;
   if (!Match(T_Lexeme::T_Group::grInteger)) return 0;
   return 1;
}
int PSyntax::int_body()
{
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = int_body_0()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = int_body_1()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = int_body_2()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   if ((p_ret = int_body_3()) > 0) return 1; else f_ret += p_ret;
   Restore(store);
   return ((f_ret == -4) ? -1 : 0);
}
