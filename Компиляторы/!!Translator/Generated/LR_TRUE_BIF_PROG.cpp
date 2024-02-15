
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
   MAKE_CODE(BegStmExprLR);
   MAKE_TURN(Make,Statements,0);
   if ((s_ret = BIF_DefFAV()) <= 0) RETURN (s_ret);
   PARAM_TREE(BegStmExprLR,1);
   MAKE_TURN(Down,None,0);
   if (BIF__f_00002_() <= 0) RETURN (0);
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
   if ((s_ret = BIF_DefFAV()) <= 0) RETURN (s_ret);
   MAKE_TREE(AddToList);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF__f_00002_()
{
   FORMULA(_f_00002_)
   int p_ret;
   while ((p_ret = BIF__f_00002__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_DefBegParVar --------------------
int PSyntax::BIF_DefBegParVar_0()
{
   PRODUCE(DefBegParVar,0)
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (-1);
   MAKE(DefParVar);
   MAKE_TURN(Make,DefVar,-1);
   RETURN (1);
}
int PSyntax::BIF_DefBegParVar()
{
   FORMULA(DefBegParVar)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefBegParVar_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_DefBegParArr --------------------
int PSyntax::BIF_DefBegParArr_0()
{
   PRODUCE(DefBegParArr,0)
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) RETURN (-1);
   MAKE(DefParArr);
   MAKE_TURN(Make,List,0);
   if (BIF_DefBegRanges() <= 0) RETURN (0);
   MAKE_TURN(Make,DefArr,-2);
   RETURN (1);
}
int PSyntax::BIF_DefBegParArr()
{
   FORMULA(DefBegParArr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefBegParArr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_DefParItem --------------------
int PSyntax::BIF_DefParItem_0()
{
   PRODUCE(DefParItem,0)
   if (!Match(T_Lexeme::T_Syntax::sxDefArr)) RETURN (-1);
   MAKE_TURN(Push,Type,0);
   if (BIF_DefBegParArr() <= 0) RETURN (0);
   if (BIF__f_00077_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_DefParItem_1()
{
   PRODUCE(DefParItem,1)
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) RETURN (-1);
   MAKE_TURN(Push,Type,0);
   if (BIF_DefBegParVar() <= 0) RETURN (0);
   if (BIF__f_00077_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_DefParItem()
{
   FORMULA(DefParItem)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefParItem_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_DefParItem_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
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

// -------------------- BIF_Initializer --------------------
int PSyntax::BIF_Initializer_0()
{
   PRODUCE(Initializer,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) RETURN (-1);
   MAKE_CODE(BegInitial);
   MAKE_TREE(NodeListLR);
   MAKE_TURN(Make,List,0);
   RETURN (1);
}
int PSyntax::BIF_Initializer_1()
{
   PRODUCE(Initializer,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) RETURN (-1);
   PARAM_CODE(BegInitial,1);
   MAKE_TREE(NodeListLR);
   MAKE_TURN(Make,List,0);
   if (BIF_AInitItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   MAKE_TURN(Down,None,0);
   if (BIF__f_00008_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00008_ --------------------
int PSyntax::BIF__f_00008__0()
{
   PRODUCE(_f_00008_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (BIF_AInitItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF__f_00008_()
{
   FORMULA(_f_00008_)
   int p_ret;
   while ((p_ret = BIF__f_00008__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_DefRanges_ --------------------
int PSyntax::BIF_DefRanges__0()
{
   PRODUCE(DefRanges_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) RETURN (-1);
   if (BIF_Assign() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_DefRanges_()
{
   FORMULA(DefRanges_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefRanges__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_DefRanges --------------------
int PSyntax::BIF_DefRanges_0()
{
   PRODUCE(DefRanges,0)
   int s_ret;
   if ((s_ret = BIF_DefRanges_()) <= 0) RETURN (s_ret);
   MAKE(DRange);
   MAKE_TURN(Down,None,0);
   if (BIF__f_00011_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_DefRanges()
{
   FORMULA(DefRanges)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefRanges_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF__f_00011_ --------------------
int PSyntax::BIF__f_00011__0()
{
   PRODUCE(_f_00011_,0)
   int s_ret;
   if ((s_ret = BIF_DefRanges_()) <= 0) RETURN (s_ret);
   MAKE(DRange);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF__f_00011_()
{
   FORMULA(_f_00011_)
   int p_ret;
   while ((p_ret = BIF__f_00011__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_DefBegRanges --------------------
int PSyntax::BIF_DefBegRanges_0()
{
   PRODUCE(DefBegRanges,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyScrape)) RETURN (-1);
   MAKE(DefArrD1AEmpty);
   MAKE_TURN(Put,Null,0);
   MAKE_TURN(Down,None,0);
   if (BIF__f_00013_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_DefBegRanges_1()
{
   PRODUCE(DefBegRanges,1)
   int s_ret;
   if ((s_ret = BIF_DefRanges()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF_DefBegRanges()
{
   FORMULA(DefBegRanges)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefBegRanges_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_DefBegRanges_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00013_ --------------------
int PSyntax::BIF__f_00013__0()
{
   PRODUCE(_f_00013_,0)
   int s_ret;
   if ((s_ret = BIF_DefRanges()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF__f_00013_()
{
   FORMULA(_f_00013_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00013__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? 1 : 0);
}

// -------------------- BIF_DefBegArr --------------------
int PSyntax::BIF_DefBegArr_0()
{
   PRODUCE(DefBegArr,0)
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) RETURN (-1);
   MAKE(DefArray);
   MAKE_TURN(Push,DefArr,0);
   MAKE_TURN(Make,Ranges,0);
   if (BIF_DefBegRanges() <= 0) RETURN (0);
   MAKE_CODE(EndRanges);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF_DefBegArr()
{
   FORMULA(DefBegArr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefBegArr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_DefVarIdent --------------------
int PSyntax::BIF_DefVarIdent_0()
{
   PRODUCE(DefVarIdent,0)
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (-1);
   MAKE(DefIdent);
   MAKE_TURN(Push,DefVar,0);
   RETURN (1);
}
int PSyntax::BIF_DefVarIdent()
{
   FORMULA(DefVarIdent)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefVarIdent_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_DefVarAssign --------------------
int PSyntax::BIF_DefVarAssign_0()
{
   PRODUCE(DefVarAssign,0)
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) RETURN (-1);
   MAKE_CODE(BegDefVarAssign);
   MAKE_TURN(Command,Lexeme,-1);
   if (BIF_Assign() <= 0) RETURN (0);
   MAKE(DefVarAssign);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF_DefVarAssign()
{
   FORMULA(DefVarAssign)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefVarAssign_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_DefIAV --------------------
int PSyntax::BIF_DefIAV_0()
{
   PRODUCE(DefIAV,0)
   int s_ret;
   if ((s_ret = BIF_DefBegArr()) <= 0) RETURN (s_ret);
   if (BIF__f_00018_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_DefIAV_1()
{
   PRODUCE(DefIAV,1)
   int s_ret;
   if ((s_ret = BIF_DefVarIdent()) <= 0) RETURN (s_ret);
   if (BIF__f_00019_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00018_ --------------------
int PSyntax::BIF__f_00018__0()
{
   PRODUCE(_f_00018_,0)
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) RETURN (-1);
   MAKE_CODE(BegAInit);
   MAKE_TURN(Command,Lexeme,-1);
   if (BIF_Initializer() <= 0) RETURN (0);
   MAKE(EndAInit);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF__f_00018_()
{
   FORMULA(_f_00018_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00018__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? 1 : 0);
}

// -------------------- BIF__f_00019_ --------------------
int PSyntax::BIF__f_00019__0()
{
   PRODUCE(_f_00019_,0)
   int s_ret;
   if ((s_ret = BIF_DefVarAssign()) <= 0) RETURN (s_ret);
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
   MAKE_TURN(Command,Lexeme,-1);
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

// -------------------- BIF_Expressions --------------------
int PSyntax::BIF_Expressions_0()
{
   PRODUCE(Expressions,0)
   int s_ret;
   if ((s_ret = BIF_Assign()) <= 0) RETURN (s_ret);
   MAKE(ExpressionsLR);
   MAKE_TURN(Make,Expressions,1);
   if (BIF__f_00022_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00022_ --------------------
int PSyntax::BIF__f_00022__0()
{
   PRODUCE(_f_00022_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (BIF_Assign() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   MAKE_TURN(Down,None,0);
   MAKE_CODE(AddToExpr);
   RETURN (1);
}
int PSyntax::BIF__f_00022_()
{
   FORMULA(_f_00022_)
   int p_ret;
   while ((p_ret = BIF__f_00022__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Assign --------------------
int PSyntax::BIF_Assign_0()
{
   PRODUCE(Assign,0)
   int s_ret;
   if ((s_ret = BIF_Question()) <= 0) RETURN (s_ret);
   if (BIF__f_00024_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00024_ --------------------
int PSyntax::BIF__f_00024__0()
{
   PRODUCE(_f_00024_,0)
   if (!Match(T_Symbol::T_Priority::prAssign)) RETURN (-1);
   if (BIF_Assign() <= 0) RETURN (0);
   MAKE(Binary);
   MAKE_TURN(Make,Binary,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00024_()
{
   FORMULA(_f_00024_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00024__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? 1 : 0);
}

// -------------------- BIF_Question --------------------
int PSyntax::BIF_Question_0()
{
   PRODUCE(Question,0)
   int s_ret;
   if ((s_ret = BIF_OrOr()) <= 0) RETURN (s_ret);
   if (BIF__f_00026_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00026_ --------------------
int PSyntax::BIF__f_00026__0()
{
   PRODUCE(_f_00026_,0)
   if (!Match(T_Symbol::T_Priority::prQuestion)) RETURN (-1);
   MAKE_CODE(BegQuestion);
   if (BIF_ExpressionValue() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxColon)) RETURN (0);
   MAKE_CODE(MidQuestion);
   if (BIF_Question() <= 0) RETURN (0);
   MAKE(Question);
   MAKE_TURN(Make,Trio,-3);
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

// -------------------- BIF_OrOr --------------------
int PSyntax::BIF_OrOr_0()
{
   PRODUCE(OrOr,0)
   int s_ret;
   if ((s_ret = BIF_AndAnd()) <= 0) RETURN (s_ret);
   if (BIF__f_00028_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_OrOr()
{
   FORMULA(OrOr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_OrOr_0()) > 0) RETURN (1) else f_ret += p_ret;
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
   MAKE_TURN(Make,Binary,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00028_()
{
   FORMULA(_f_00028_)
   int p_ret;
   while ((p_ret = BIF__f_00028__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_AndAnd --------------------
int PSyntax::BIF_AndAnd_0()
{
   PRODUCE(AndAnd,0)
   int s_ret;
   if ((s_ret = BIF_Or()) <= 0) RETURN (s_ret);
   if (BIF__f_00030_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00030_ --------------------
int PSyntax::BIF__f_00030__0()
{
   PRODUCE(_f_00030_,0)
   if (!Match(T_Symbol::T_Priority::prAndAnd)) RETURN (-1);
   if (BIF_Or() <= 0) RETURN (0);
   MAKE(Binary);
   MAKE_TURN(Make,Binary,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00030_()
{
   FORMULA(_f_00030_)
   int p_ret;
   while ((p_ret = BIF__f_00030__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Or --------------------
int PSyntax::BIF_Or_0()
{
   PRODUCE(Or,0)
   int s_ret;
   if ((s_ret = BIF_XOr()) <= 0) RETURN (s_ret);
   if (BIF__f_00032_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00032_ --------------------
int PSyntax::BIF__f_00032__0()
{
   PRODUCE(_f_00032_,0)
   if (!Match(T_Symbol::T_Priority::prOr)) RETURN (-1);
   if (BIF_XOr() <= 0) RETURN (0);
   MAKE(Binary);
   MAKE_TURN(Make,Binary,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00032_()
{
   FORMULA(_f_00032_)
   int p_ret;
   while ((p_ret = BIF__f_00032__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_XOr --------------------
int PSyntax::BIF_XOr_0()
{
   PRODUCE(XOr,0)
   int s_ret;
   if ((s_ret = BIF_And()) <= 0) RETURN (s_ret);
   if (BIF__f_00034_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00034_ --------------------
int PSyntax::BIF__f_00034__0()
{
   PRODUCE(_f_00034_,0)
   if (!Match(T_Symbol::T_Priority::prXOr)) RETURN (-1);
   if (BIF_And() <= 0) RETURN (0);
   MAKE(Binary);
   MAKE_TURN(Make,Binary,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00034_()
{
   FORMULA(_f_00034_)
   int p_ret;
   while ((p_ret = BIF__f_00034__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_And --------------------
int PSyntax::BIF_And_0()
{
   PRODUCE(And,0)
   int s_ret;
   if ((s_ret = BIF_Equ()) <= 0) RETURN (s_ret);
   if (BIF__f_00036_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00036_ --------------------
int PSyntax::BIF__f_00036__0()
{
   PRODUCE(_f_00036_,0)
   if (!Match(T_Symbol::T_Priority::prAnd)) RETURN (-1);
   if (BIF_Equ() <= 0) RETURN (0);
   MAKE(Binary);
   MAKE_TURN(Make,Binary,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00036_()
{
   FORMULA(_f_00036_)
   int p_ret;
   while ((p_ret = BIF__f_00036__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Equ --------------------
int PSyntax::BIF_Equ_0()
{
   PRODUCE(Equ,0)
   int s_ret;
   if ((s_ret = BIF_Compare()) <= 0) RETURN (s_ret);
   if (BIF__f_00038_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00038_ --------------------
int PSyntax::BIF__f_00038__0()
{
   PRODUCE(_f_00038_,0)
   if (!Match(T_Symbol::T_Priority::prEqu)) RETURN (-1);
   if (BIF_Compare() <= 0) RETURN (0);
   MAKE(Binary);
   MAKE_TURN(Make,Binary,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00038_()
{
   FORMULA(_f_00038_)
   int p_ret;
   while ((p_ret = BIF__f_00038__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Compare --------------------
int PSyntax::BIF_Compare_0()
{
   PRODUCE(Compare,0)
   int s_ret;
   if ((s_ret = BIF_Shift()) <= 0) RETURN (s_ret);
   if (BIF__f_00040_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00040_ --------------------
int PSyntax::BIF__f_00040__0()
{
   PRODUCE(_f_00040_,0)
   if (!Match(T_Symbol::T_Priority::prCompare)) RETURN (-1);
   if (BIF_Shift() <= 0) RETURN (0);
   MAKE(Binary);
   MAKE_TURN(Make,Binary,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00040_()
{
   FORMULA(_f_00040_)
   int p_ret;
   while ((p_ret = BIF__f_00040__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Shift --------------------
int PSyntax::BIF_Shift_0()
{
   PRODUCE(Shift,0)
   int s_ret;
   if ((s_ret = BIF_Term()) <= 0) RETURN (s_ret);
   if (BIF__f_00042_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00042_ --------------------
int PSyntax::BIF__f_00042__0()
{
   PRODUCE(_f_00042_,0)
   if (!Match(T_Symbol::T_Priority::prShift)) RETURN (-1);
   if (BIF_Term() <= 0) RETURN (0);
   MAKE(Binary);
   MAKE_TURN(Make,Binary,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00042_()
{
   FORMULA(_f_00042_)
   int p_ret;
   while ((p_ret = BIF__f_00042__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Term --------------------
int PSyntax::BIF_Term_0()
{
   PRODUCE(Term,0)
   int s_ret;
   if ((s_ret = BIF_Factor()) <= 0) RETURN (s_ret);
   if (BIF__f_00044_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00044_ --------------------
int PSyntax::BIF__f_00044__0()
{
   PRODUCE(_f_00044_,0)
   if (!Match(T_Symbol::T_Priority::prTerm)) RETURN (-1);
   if (BIF_Factor() <= 0) RETURN (0);
   MAKE(Binary);
   MAKE_TURN(Make,Binary,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00044_()
{
   FORMULA(_f_00044_)
   int p_ret;
   while ((p_ret = BIF__f_00044__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Factor --------------------
int PSyntax::BIF_Factor_0()
{
   PRODUCE(Factor,0)
   int s_ret;
   if ((s_ret = BIF_Unary()) <= 0) RETURN (s_ret);
   if (BIF__f_00046_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00046_ --------------------
int PSyntax::BIF__f_00046__0()
{
   PRODUCE(_f_00046_,0)
   if (!Match(T_Symbol::T_Priority::prFactor)) RETURN (-1);
   if (BIF_Unary() <= 0) RETURN (0);
   MAKE(Binary);
   MAKE_TURN(Make,Binary,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00046_()
{
   FORMULA(_f_00046_)
   int p_ret;
   while ((p_ret = BIF__f_00046__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_Unary --------------------
int PSyntax::BIF_Unary_0()
{
   PRODUCE(Unary,0)
   if (!Match(T_Symbol::T_Priority::prUnary)) RETURN (-1);
   if (BIF_Unary() <= 0) RETURN (0);
   MAKE(Unary);
   MAKE_TURN(Make,Unary,-1);
   RETURN (1);
}
int PSyntax::BIF_Unary_1()
{
   PRODUCE(Unary,1)
   if (!Match(T_Symbol::T_Priority::prTerm)) RETURN (-1);
   if (BIF_Unary() <= 0) RETURN (0);
   MAKE(Unary);
   MAKE_TURN(Make,Unary,-1);
   RETURN (1);
}
int PSyntax::BIF_Unary_2()
{
   PRODUCE(Unary,2)
   if (!Match(T_Symbol::T_Priority::prIncDec)) RETURN (-1);
   if (BIF_Unary() <= 0) RETURN (0);
   MAKE(Unary);
   MAKE_TURN(Make,Unary,-1);
   RETURN (1);
}
int PSyntax::BIF_Unary_3()
{
   PRODUCE(Unary,3)
   if (!Match(T_Lexeme::T_Syntax::sxCastUnary)) RETURN (-1);
   if (BIF_Unary() <= 0) RETURN (0);
   MAKE(Cast);
   MAKE_TURN(Make,Cast,-1);
   RETURN (1);
}
int PSyntax::BIF_Unary_4()
{
   PRODUCE(Unary,4)
   int s_ret;
   if ((s_ret = BIF_PrimaryExpr()) <= 0) RETURN (s_ret);
   if (BIF__f_00048_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00048_ --------------------
int PSyntax::BIF__f_00048__0()
{
   PRODUCE(_f_00048_,0)
   if (!Match(T_Symbol::T_Priority::prIncDec)) RETURN (-1);
   MAKE(IncDec);
   MAKE_TURN(Make,IncDec,-1);
   RETURN (1);
}
int PSyntax::BIF__f_00048_()
{
   FORMULA(_f_00048_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00048__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? 1 : 0);
}

// -------------------- BIF_Primary --------------------
int PSyntax::BIF_Primary_0()
{
   PRODUCE(Primary,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (-1);
   if (BIF_Expressions() <= 0) RETURN (0);
   MAKE(ExpressionSLR);
   MAKE_TURN(Command,Param,0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   MAKE_TREE(Primary);
   MAKE_TURN(Make,Primary,1);
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

// -------------------- BIF_PrimaryExpr --------------------
int PSyntax::BIF_PrimaryExpr_0()
{
   PRODUCE(PrimaryExpr,0)
   if (!Match(T_Lexeme::T_Group::grInteger)) RETURN (-1);
   MAKE(Number);
   MAKE_TURN(Push,Number,0);
   RETURN (1);
}
int PSyntax::BIF_PrimaryExpr_1()
{
   PRODUCE(PrimaryExpr,1)
   if (!Match(T_Lexeme::T_Group::grNumber)) RETURN (-1);
   MAKE(Number);
   MAKE_TURN(Push,Number,0);
   RETURN (1);
}
int PSyntax::BIF_PrimaryExpr_2()
{
   PRODUCE(PrimaryExpr,2)
   if (!Match(T_Lexeme::T_Syntax::sxIdentArr)) RETURN (-1);
   MAKE_TURN(Push,Index,0);
   if (BIF_Range() <= 0) RETURN (0);
   MAKE(BegIndexLR);
   MAKE_TURN(Make,Ranges,1);
   if (BIF__f_00051_() <= 0) RETURN (0);
   MAKE(EndIndex);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF_PrimaryExpr_3()
{
   PRODUCE(PrimaryExpr,3)
   if (!Match(T_Lexeme::T_Syntax::sxIdentFunc)) RETURN (-1);
   MAKE_TURN(Push,Call,0);
   if (BIF__f_00052_() <= 0) RETURN (0);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF_PrimaryExpr_4()
{
   PRODUCE(PrimaryExpr,4)
   if (!Match(T_Lexeme::T_Syntax::sxCast)) RETURN (-1);
   if (BIF_Primary() <= 0) RETURN (0);
   MAKE(Cast);
   MAKE_TURN(Make,Cast,-1);
   RETURN (1);
}
int PSyntax::BIF_PrimaryExpr_5()
{
   PRODUCE(PrimaryExpr,5)
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (-1);
   MAKE(Ident);
   MAKE_TURN(Push,Var,0);
   RETURN (1);
}
int PSyntax::BIF_PrimaryExpr_6()
{
   PRODUCE(PrimaryExpr,6)
   int s_ret;
   if ((s_ret = BIF_Primary()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF_PrimaryExpr()
{
   FORMULA(PrimaryExpr)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_PrimaryExpr_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_PrimaryExpr_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_PrimaryExpr_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_PrimaryExpr_3()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_PrimaryExpr_4()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_PrimaryExpr_5()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_PrimaryExpr_6()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -7) ? -1 : 0);
}

// -------------------- BIF__f_00051_ --------------------
int PSyntax::BIF__f_00051__0()
{
   PRODUCE(_f_00051_,0)
   int s_ret;
   if ((s_ret = BIF_Range()) <= 0) RETURN (s_ret);
   MAKE(IndexLR);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF__f_00051_()
{
   FORMULA(_f_00051_)
   int p_ret;
   while ((p_ret = BIF__f_00051__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF__f_00052_ --------------------
int PSyntax::BIF__f_00052__0()
{
   PRODUCE(_f_00052_,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyBracket)) RETURN (-1);
   MAKE(Params);
   MAKE_TURN(Make,Null,0);
   RETURN (1);
}
int PSyntax::BIF__f_00052__1()
{
   PRODUCE(_f_00052_,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (-1);
   if (BIF_Expressions() <= 0) RETURN (0);
   PARAM(ExpressionSLR,512);
   MAKE_TURN(Command,Param,512);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   PARAM(Params,1);
   RETURN (1);
}
int PSyntax::BIF__f_00052_()
{
   FORMULA(_f_00052_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00052__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00052__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF_Range --------------------
int PSyntax::BIF_Range_0()
{
   PRODUCE(Range,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftScrape)) RETURN (-1);
   if (BIF_ExpressionValue() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightScrape)) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF_Range()
{
   FORMULA(Range)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_Range_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_Condition --------------------
int PSyntax::BIF_Condition_0()
{
   PRODUCE(Condition,0)
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) RETURN (-1);
   MAKE(Define);
   if (BIF__f_00055_() <= 0) RETURN (0);
   MAKE(PushDef);
   RETURN (1);
}
int PSyntax::BIF_Condition_1()
{
   PRODUCE(Condition,1)
   int s_ret;
   if ((s_ret = BIF_Expressions()) <= 0) RETURN (s_ret);
   PARAM(ExpressionSLR,241);
   MAKE_TURN(Command,Param,241);
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

// -------------------- BIF__f_00055_ --------------------
int PSyntax::BIF__f_00055__0()
{
   PRODUCE(_f_00055_,0)
   if (!Match(T_Symbol::T_Priority::prAnd)) RETURN (-1);
   if (BIF_DefVarAssign() <= 0) RETURN (0);
   MAKE_TREE(RefDef);
   MAKE_TURN(Command,Lexeme,-1);
   RETURN (1);
}
int PSyntax::BIF__f_00055__1()
{
   PRODUCE(_f_00055_,1)
   int s_ret;
   if ((s_ret = BIF_DefVarAssign()) <= 0) RETURN (s_ret);
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

// -------------------- BIF_BegIfStmnt --------------------
int PSyntax::BIF_BegIfStmnt_0()
{
   PRODUCE(BegIfStmnt,0)
   if (!Match(T_Lexeme::W_Type::rwIf)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   MAKE_CODE(BegIf);
   if (BIF_Condition() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   MAKE_CODE(Then);
   if (BIF_DefExpr() <= 0) RETURN (0);
   MAKE_TURN(Make,If,2);
   RETURN (1);
}
int PSyntax::BIF_BegIfStmnt()
{
   FORMULA(BegIfStmnt)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_BegIfStmnt_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? -1 : 0);
}

// -------------------- BIF_DefineSemi --------------------
int PSyntax::BIF_DefineSemi_0()
{
   PRODUCE(DefineSemi,0)
   int s_ret;
   if ((s_ret = BIF__f_00058_()) <= 0) RETURN (s_ret);
   MAKE(Define);
   MAKE_TURN(Push,Type,0);
   MAKE_TURN(Make,Define,1);
   if (BIF_DefItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   MAKE_TURN(Down,None,0);
   if (BIF__f_00059_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00058_ --------------------
int PSyntax::BIF__f_00058__0()
{
   PRODUCE(_f_00058_,0)
   if (!Match(T_Lexeme::T_Syntax::sxDefArr)) RETURN (-1);
   RETURN (1);
}
int PSyntax::BIF__f_00058__1()
{
   PRODUCE(_f_00058_,1)
   if (!Match(T_Lexeme::T_Syntax::sxDefVar)) RETURN (-1);
   RETURN (1);
}
int PSyntax::BIF__f_00058_()
{
   FORMULA(_f_00058_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00058__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00058__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00059_ --------------------
int PSyntax::BIF__f_00059__0()
{
   PRODUCE(_f_00059_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (BIF_DefItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF__f_00059_()
{
   FORMULA(_f_00059_)
   int p_ret;
   while ((p_ret = BIF__f_00059__0()) > 0);
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
   MAKE_TURN(Make,Null,0);
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
   if ((s_ret = BIF__f_00062_()) <= 0) RETURN (s_ret);
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

// -------------------- BIF__f_00062_ --------------------
int PSyntax::BIF__f_00062__0()
{
   PRODUCE(_f_00062_,0)
   int s_ret;
   if ((s_ret = BIF_BegIfStmnt()) <= 0) RETURN (s_ret);
   if (BIF__f_00063_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00062__1()
{
   PRODUCE(_f_00062_,1)
   if (!Match(T_Lexeme::T_Syntax::sxLabel)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxColon)) RETURN (0);
   MAKE_CODE(Label);
   MAKE_TURN(Push,Label,0);
   if (BIF_DefExpr() <= 0) RETURN (0);
   MAKE_TREE(Label);
   MAKE_TURN(Make,List,2);
   RETURN (1);
}
int PSyntax::BIF__f_00062__2()
{
   PRODUCE(_f_00062_,2)
   if (!Match(T_Lexeme::W_Type::rwDo)) RETURN (-1);
   MAKE(BegDo);
   if (BIF_DefExpr() <= 0) RETURN (0);
   if (!Match(T_Lexeme::W_Type::rwWhile)) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   if (BIF_Condition() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(Do);
   MAKE_TURN(Make,Do,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00062__3()
{
   PRODUCE(_f_00062_,3)
   if (!Match(T_Lexeme::W_Type::rwWhile)) RETURN (-1);
   MAKE(BegWhile);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   if (BIF_Condition() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   if (BIF_DefExpr() <= 0) RETURN (0);
   MAKE(While);
   MAKE_TURN(Make,While,-2);
   RETURN (1);
}
int PSyntax::BIF__f_00062__4()
{
   PRODUCE(_f_00062_,4)
   if (!Match(T_Lexeme::W_Type::rwFor)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   MAKE(BegFor);
   if (BIF__f_00064_() <= 0) RETURN (0);
   MAKE_CODE(PrefFor);
   if (BIF__f_00065_() <= 0) RETURN (0);
   MAKE_CODE(ConditionFor);
   if (BIF__f_00066_() <= 0) RETURN (0);
   MAKE_CODE(PostFor);
   if (BIF_DefExpr() <= 0) RETURN (0);
   MAKE(For);
   MAKE_TURN(Make,For,4);
   RETURN (1);
}
int PSyntax::BIF__f_00062__5()
{
   PRODUCE(_f_00062_,5)
   if (!Match(T_Lexeme::W_Type::rwSwitch)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00062__6()
{
   PRODUCE(_f_00062_,6)
   if (!Match(T_Lexeme::W_Type::rwGoTo)) RETURN (-1);
   if (!Match(T_Lexeme::T_Group::grIdent)) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(GoTo);
   MAKE_TURN(Push,GoTo,0);
   RETURN (1);
}
int PSyntax::BIF__f_00062__7()
{
   PRODUCE(_f_00062_,7)
   if (!Match(T_Lexeme::W_Type::rwBreak)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(Break);
   MAKE_TURN(Make,Break,0);
   RETURN (1);
}
int PSyntax::BIF__f_00062__8()
{
   PRODUCE(_f_00062_,8)
   if (!Match(T_Lexeme::W_Type::rwContinue)) RETURN (-1);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   MAKE(Continue);
   MAKE_TURN(Make,Continue,0);
   RETURN (1);
}
int PSyntax::BIF__f_00062__9()
{
   PRODUCE(_f_00062_,9)
   if (!Match(T_Lexeme::W_Type::rwReturn)) RETURN (-1);
   if (BIF__f_00067_() <= 0) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00062__10()
{
   PRODUCE(_f_00062_,10)
   int s_ret;
   if ((s_ret = BIF__f_00068_()) <= 0) RETURN (s_ret);
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
   if ((p_ret = BIF__f_00062__2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00062__3()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00062__4()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00062__5()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00062__6()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00062__7()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00062__8()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00062__9()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00062__10()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -11) ? -1 : 0);
}

// -------------------- BIF__f_00063_ --------------------
int PSyntax::BIF__f_00063__0()
{
   PRODUCE(_f_00063_,0)
   if (!Match(T_Lexeme::W_Type::rwElse)) RETURN (-1);
   MAKE_CODE(Else);
   if (BIF_DefExpr() <= 0) RETURN (0);
   PARAM(If,1);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF__f_00063__1()
{
   PRODUCE(_f_00063_,1)
   MAKE(If);
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
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE_TREE(NodeNull);
   MAKE_TURN(Make,Null,0);
   RETURN (1);
}
int PSyntax::BIF__f_00064__1()
{
   PRODUCE(_f_00064_,1)
   int s_ret;
   if ((s_ret = BIF_DefineSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF__f_00064__2()
{
   PRODUCE(_f_00064_,2)
   int s_ret;
   if ((s_ret = BIF_ExprSemi()) <= 0) RETURN (s_ret);
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
   if ((p_ret = BIF__f_00064__2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -3) ? -1 : 0);
}

// -------------------- BIF__f_00065_ --------------------
int PSyntax::BIF__f_00065__0()
{
   PRODUCE(_f_00065_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE(NodeNull);
   MAKE_TURN(Make,Null,0);
   RETURN (1);
}
int PSyntax::BIF__f_00065__1()
{
   PRODUCE(_f_00065_,1)
   int s_ret;
   if ((s_ret = BIF_Condition()) <= 0) RETURN (s_ret);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
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

// -------------------- BIF__f_00066_ --------------------
int PSyntax::BIF__f_00066__0()
{
   PRODUCE(_f_00066_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (-1);
   MAKE_TREE(NodeNull);
   MAKE_TURN(Make,Null,0);
   RETURN (1);
}
int PSyntax::BIF__f_00066__1()
{
   PRODUCE(_f_00066_,1)
   int s_ret;
   if ((s_ret = BIF_ExpressionExpression()) <= 0) RETURN (s_ret);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00066_()
{
   FORMULA(_f_00066_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00066__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00066__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00067_ --------------------
int PSyntax::BIF__f_00067__0()
{
   PRODUCE(_f_00067_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE(Return);
   MAKE_TURN(Make,Return,0);
   RETURN (1);
}
int PSyntax::BIF__f_00067__1()
{
   PRODUCE(_f_00067_,1)
   int s_ret;
   if ((s_ret = BIF_ExpressionValue()) <= 0) RETURN (s_ret);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (0);
   PARAM(Return,1);
   MAKE_TURN(Make,Return,1);
   RETURN (1);
}
int PSyntax::BIF__f_00067_()
{
   FORMULA(_f_00067_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00067__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00067__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00068_ --------------------
int PSyntax::BIF__f_00068__0()
{
   PRODUCE(_f_00068_,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) RETURN (-1);
   MAKE(Compaund);
   MAKE_CODE(EndBlock);
   MAKE_TURN(Make,Statements,0);
   RETURN (1);
}
int PSyntax::BIF__f_00068__1()
{
   PRODUCE(_f_00068_,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) RETURN (-1);
   MAKE(Compaund);
   MAKE_TURN(Make,Statements,0);
   if (BIF_StmExpr() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) RETURN (0);
   RETURN (1);
}
int PSyntax::BIF__f_00068_()
{
   FORMULA(_f_00068_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00068__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00068__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF_StmExpr --------------------
int PSyntax::BIF_StmExpr_0()
{
   PRODUCE(StmExpr,0)
   int s_ret;
   if ((s_ret = BIF_DefExpr()) <= 0) RETURN (s_ret);
   MAKE_TREE(AddToList);
   MAKE_TURN(Down,None,0);
   if (BIF__f_00070_() <= 0) RETURN (0);
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

// -------------------- BIF__f_00070_ --------------------
int PSyntax::BIF__f_00070__0()
{
   PRODUCE(_f_00070_,0)
   int s_ret;
   if ((s_ret = BIF_DefExpr()) <= 0) RETURN (s_ret);
   MAKE_TREE(AddToList);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF__f_00070_()
{
   FORMULA(_f_00070_)
   int p_ret;
   while ((p_ret = BIF__f_00070__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF_DefFAV --------------------
int PSyntax::BIF_DefFAV_0()
{
   PRODUCE(DefFAV,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE_TREE(NodeNull);
   MAKE_TURN(Make,Null,0);
   RETURN (1);
}
int PSyntax::BIF_DefFAV_1()
{
   PRODUCE(DefFAV,1)
   if (!Match(T_Lexeme::T_Syntax::sxDefFunc)) RETURN (-1);
   MAKE_TURN(Push,Type,0);
   if (!Match(T_Lexeme::T_Syntax::sxIdentFunc)) RETURN (0);
   MAKE(FuncIdent);
   MAKE_TURN(Make,DefFunc,-1);
   if (BIF__f_00072_() <= 0) RETURN (0);
   if (BIF__f_00074_() <= 0) RETURN (0);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF_DefFAV_2()
{
   PRODUCE(DefFAV,2)
   int s_ret;
   if ((s_ret = BIF_DefineSemi()) <= 0) RETURN (s_ret);
   RETURN (1);
}
int PSyntax::BIF_DefFAV()
{
   FORMULA(DefFAV)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF_DefFAV_0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_DefFAV_1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF_DefFAV_2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -3) ? -1 : 0);
}

// -------------------- BIF__f_00072_ --------------------
int PSyntax::BIF__f_00072__0()
{
   PRODUCE(_f_00072_,0)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyBracket)) RETURN (-1);
   PARAM_TREE(EndParams,2);
   MAKE_TURN(Make,Null,0);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF__f_00072__1()
{
   PRODUCE(_f_00072_,1)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftBracket)) RETURN (-1);
   PARAM_TREE(Define,2);
   MAKE_TURN(Make,Define,0);
   if (BIF_DefParItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   MAKE_TURN(Down,None,0);
   if (BIF__f_00073_() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightBracket)) RETURN (0);
   MAKE_TREE(EndParams);
   MAKE_TURN(Down,None,1);
   RETURN (1);
}
int PSyntax::BIF__f_00072_()
{
   FORMULA(_f_00072_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00072__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00072__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -2) ? -1 : 0);
}

// -------------------- BIF__f_00073_ --------------------
int PSyntax::BIF__f_00073__0()
{
   PRODUCE(_f_00073_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxComma)) RETURN (-1);
   if (BIF_DefParItem() <= 0) RETURN (0);
   MAKE_TREE(AddToList);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF__f_00073_()
{
   FORMULA(_f_00073_)
   int p_ret;
   while ((p_ret = BIF__f_00073__0()) > 0);
   RETURN (!p_ret ? 0 : 1);
}

// -------------------- BIF__f_00074_ --------------------
int PSyntax::BIF__f_00074__0()
{
   PRODUCE(_f_00074_,0)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxSemicolon)) RETURN (-1);
   MAKE(BodyFunc);
   MAKE_TURN(Make,Null,0);
   RETURN (1);
}
int PSyntax::BIF__f_00074__1()
{
   PRODUCE(_f_00074_,1)
   if (!Match(T_Lexeme::T_Syntax::sxEmptyCramp)) RETURN (-1);
   PARAM(BodyFunc,1);
   MAKE_TURN(Make,Statements,0);
   RETURN (1);
}
int PSyntax::BIF__f_00074__2()
{
   PRODUCE(_f_00074_,2)
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxLeftCramp)) RETURN (-1);
   MAKE_CODE(EndParams);
   MAKE(BegStmExprLR);
   MAKE_TURN(Make,Statements,0);
   if (BIF_StmExpr() <= 0) RETURN (0);
   if (!Match(T_Lexeme::grSeparator,T_Symbol::T_Type::lxRightCramp)) RETURN (0);
   PARAM(BodyFunc,2);
   RETURN (1);
}
int PSyntax::BIF__f_00074_()
{
   FORMULA(_f_00074_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00074__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00074__1()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   if ((p_ret = BIF__f_00074__2()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -3) ? -1 : 0);
}

// -------------------- BIF_ExpressionExpression --------------------
int PSyntax::BIF_ExpressionExpression_0()
{
   PRODUCE(ExpressionExpression,0)
   int s_ret;
   if ((s_ret = BIF_Expressions()) <= 0) RETURN (s_ret);
   PARAM(ExpressionSLR,16);
   MAKE_TURN(Command,Param,16);
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
   if ((s_ret = BIF_Expressions()) <= 0) RETURN (s_ret);
   PARAM(ExpressionSLR,256);
   MAKE_TURN(Command,Param,256);
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

// -------------------- BIF__f_00077_ --------------------
int PSyntax::BIF__f_00077__0()
{
   PRODUCE(_f_00077_,0)
   if (!Match(T_Lexeme::grOper,T_Symbol::T_Type::lxAssign)) RETURN (-1);
   MAKE_CODE(BegParVarAssign);
   MAKE_TURN(Command,Lexeme,-1);
   if (BIF_Assign() <= 0) RETURN (0);
   MAKE(ParVarAssign);
   MAKE_TURN(Down,None,0);
   RETURN (1);
}
int PSyntax::BIF__f_00077_()
{
   FORMULA(_f_00077_)
   int f_ret = 0, p_ret;
   T_ScanStore store; Store(store);
   if ((p_ret = BIF__f_00077__0()) > 0) RETURN (1) else f_ret += p_ret;
   Restore(store);
   RETURN ((f_ret == -1) ? 1 : 0);
}
