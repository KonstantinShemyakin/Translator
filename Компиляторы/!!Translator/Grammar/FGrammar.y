%{

enum class T_Maker { DefType, ExpressionSLL, ExpressionSLR, AddToList, MakerSNode, SaveLexeme, Number, Ident, 
                     Label, Params, BegIndexLL, BegIndexLR, IndexLL, IndexLR, EndIndex, Binary, 
                     Unary, IncDec, Primary, Cast, Question, ExpressionsLL, ExpressionsLR, DefParVar, 
                     DefParArr, ParVarAssign, EndParams, FuncIdent, BodyFunc, EndAInit, DefArray, DRange, 
                     DefArrD1AEmpty, DefIdent, DefVarAssign, PushDef, RefDef, Define, Do, While, 
                     For, If, GoTo, Break, Continue, Return, BegStmExprLL, BegStmExprLR, 
                     Compaund, NodeNull, NodeListLL, NodeListLR, EndBlock, Part, PopType, AddToExpr, 
                     BegQuestion, MidQuestion, BegDo, MidDo, BegWhile, MidWhile, BegIf, Then, 
                     Else, BegFor, PrefFor, ConditionFor, PostFor, EndDefine, EndRanges, BegAInit, 
                     AInitItem, BegInitial, EndInitial, BegDefVarAssign, BegParVarAssign, MakerTurn, SimpleLexeme, LexTypeName, 
                     Expressions
};


enum class S_Node  { None, Node, Unary, Binary, Logical, Trio, Number, Primary, 
                     Type, Cast, IncDec, Expressions, Compaund, Statements, DefVar, DefArr, 
                     DefFunc, Define, Var, Call, Index, For, While, Do, 
                     Label, GoTo, Break, Continue, Return, If, SwitchCase, SwitchItem, 
                     Switch, List, Ranges, Null, NodeOne, NodeTwo, RefDef,
                     Lexeme, Param, Formula, Produce, Maker, Tokens, Enums, Item
};

%}

%token Oper_Add                  257 // 0X0101
%token Oper_Sub                  258 // 0X0102
%token Oper_Multi                259 // 0X0103
%token Oper_Div                  260 // 0X0104
%token Oper_Mod                  261 // 0X0105
%token Oper_AddAssign            262 // 0X0106
%token Oper_SubAssign            263 // 0X0107
%token Oper_MultiAssign          264 // 0X0108
%token Oper_DivAssign            265 // 0X0109
%token Oper_ModAssign            266 // 0X010A
%token Oper_AndAssign            267 // 0X010B
%token Oper_OrAssign             268 // 0X010C
%token Oper_XOrAssign            269 // 0X010D
%token Oper_Assign               270 // 0X010E
%token Oper_Or                   271 // 0X010F
%token Oper_And                  272 // 0X0110
%token Oper_OrOr                 273 // 0X0111
%token Oper_AndAnd               274 // 0X0112
%token Oper_XOr                  275 // 0X0113
%token Oper_Tilda                276 // 0X0114
%token Oper_Not                  277 // 0X0115
%token Oper_PlusPlus             278 // 0X0116
%token Oper_MinusMinus           279 // 0X0117
%token Oper_Equ                  280 // 0X0118
%token Oper_NotEqu               281 // 0X0119
%token Oper_LT                   282 // 0X011A
%token Oper_LE                   283 // 0X011B
%token Oper_GT                   284 // 0X011C
%token Oper_GE                   285 // 0X011D
%token Oper_LShift               286 // 0X011E
%token Oper_RShift               287 // 0X011F
%token Oper_LShiftAssign         288 // 0X0120
%token Oper_RShiftAssign         289 // 0X0121
%token Oper_Question             296 // 0X0128
%token Separator_LeftCramp       546 // 0X0222
%token Separator_RightCramp      547 // 0X0223
%token Separator_LeftBracket     548 // 0X0224
%token Separator_RightBracket    549 // 0X0225
%token Separator_LeftScrape      550 // 0X0226
%token Separator_RightScrape     551 // 0X0227
%token Separator_ColonColon      553 // 0X0229
%token Separator_Comma           556 // 0X022C
%token Separator_Semicolon       557 // 0X022D
%token Separator_Colon           558 // 0X022E
%token Separator_ModMod          565 // 0X0235
%token Separator_ModBegin        566 // 0X0236
%token Separator_ModEnd          567 // 0X0237
%token Separator_ModToken        568 // 0X0238
%token Separator_ModLeft         569 // 0X0239
%token Separator_ModRight        570 // 0X023A
%token Integer_lexeme            768 // 0X0300
%token Number_lexeme            1024 // 0X0400
%token Ident_lexeme             1536 // 0X0600
%token Reserv_Enum              1807 // 0X070f
%token Reserv_For               1793 // 0X0701
%token Reserv_While             1794 // 0X0702
%token Reserv_If                1795 // 0X0703
%token Reserv_Else              1796 // 0X0704
%token Reserv_Do                1797 // 0X0705
%token Reserv_GoTo              1798 // 0X0706
%token Reserv_Continue          1799 // 0X0707
%token Reserv_Break             1800 // 0X0708
%token Reserv_Return            1801 // 0X0709
%token Reserv_Void              1809 // 0X0711
%token Reserv_Const             1816 // 0X0718
%token Reserv_Static            1817 // 0X0719
%token Reserv_All               1834 // 0X072A
%token Reserv_Make              1835 // 0X072B
%token Reserv_Node              1836 // 0X072C
%token Reserv_Code              1837 // 0X072D
%token Reserv_Tree              1838 // 0X072E
%token Reserv_Yacc              1839 // 0X072F
%token Reserv_Turn              1840 // 0X0730
%token Reserv_Call              1841 // 0X0731
%token Reserv_Class             1842 // 0X0732
%token Syntax_DefType           3078 // 0X0C06
%%

S_:                    Grammar                  
                     ;

Grammar:               Enum_part                Token_part                   Rules                         Separator_ModMod       { NODE(Formula,(0,1,2,3),5); }
                     | Enum_part                Token_part                   Rules                         { NODE(Formula,(0,1,2,3),5); }
                     ;

Enum_part:             Separator_ModBegin       Enums                        Separator_ModEnd              { NODE(Enums,(0,2),7); }
                     | Empty
                     ;
                     
Enums:                 Enums                    Enum                         { NODE(Enums,(0,1,2),6); } 
                     | Enum                     { NODE(Enums,(0,1),5); } 
                     ;

Enum:                  Reserv_Enum              Separator_LeftCramp          enum_list                     Separator_RightCramp   Separator_Semicolon             { NODE(Enums,(0,3),4); }
                     | Reserv_Enum              Ident_lexeme                 Separator_LeftCramp           enum_list              Separator_RightCramp            Separator_Semicolon            { NODE(Enums,(2,4),4); }
                     | Reserv_Enum              Reserv_Class                 Ident_lexeme                  Separator_LeftCramp    enum_list                       Separator_RightCramp           Separator_Semicolon          { NODE(Enums,(3,5),4); } 
                     ;

enum_list:             enum_list                Separator_Comma              enum_item                     { NODE(Enums,(0,1,3),3); }   
                     | enum_item                { NODE(Enums,(0,1),2); } 
                     ;

enum_item:             Ident_lexeme             Oper_Assign                  Integer_lexeme                { NODE(Enums,(1,3),1); }
                     | Ident_lexeme             { NODE(Enums,(1),0); }
                     ;

Token_part:            Tokens                   Separator_ModMod
                     | Empty
                     ;
    
Tokens:                Tokens                   Token                        { NODE(Tokens,(0,1,2),2); }
                     | Token                    { NODE(Tokens,(0,1),1); }
                     ;       

Token:                 Separator_ModToken       Ident_lexeme                 Integer_lexeme                { NODE(Tokens,(2,3),0); }
                     ;

Rules:                 Rules                    Formula                      { NODE(Formula,(0,1,2),1); }
                     | Formula                  { NODE(Formula,(0,1),0); }
                     ;

Formula:               Ident_lexeme             Separator_Colon              Produces                      Separator_Semicolon    { NODE(Formula,(1,3),2); }
                     ;

Produces:              Produces                 Oper_Or                      Produce                       { NODE(Formula,(0,1,3),1); }
                     | Produce                  { NODE(Formula,(0,1),0); }
                     ;

Produce:               Produce                  produce_item                 { NODE(Produce,(0,1,2),5); }
                     | { NODE(Produce,(0),4); }
                     ;

produce_item:          Maker_Make
                     | Maker_Node
                     | Maker_Turn
                     | Maker_Call
                     | Ident_lexeme             { NODE(Item,(1),0); }
                     | Integer_lexeme           { NODE(Item,(1),1); }
                     | Oper_LT                  lexeme_item                  Oper_GT                       { NODE(Item,(2),2); }
                     | Oper_LT                  lexeme_item                  Separator_Comma               lexeme_item            Oper_GT                         { NODE(Item,(2,4),3); }
                     ;

lexeme_item:           Ident_lexeme
                     | Integer_lexeme
                     ;

Maker_Make:            Separator_LeftCramp      Ident_Maker                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 int_body                       Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { NODE(Maker,(2,4,6),0); }
                     | Separator_LeftCramp      Ident_Maker                  Separator_LeftBracket         Ident_lexeme           Separator_RightBracket          Separator_Semicolon            Separator_RightCramp         { NODE(Maker,(2,4),0); }
                     ;

Ident_Maker:           Reserv_All
                     | Reserv_Make
                     | Reserv_Code
                     | Reserv_Tree
                     | Reserv_Yacc
                     ;

Maker_Node:            Separator_LeftCramp      Reserv_Node                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 node_body                      Separator_Comma              int_body                     Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { NODE(Maker,(4,6,8),1); }
                     | Separator_LeftCramp      Reserv_Node                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 node_body                      Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { NODE(Maker,(4,6),1); }
                     ;

node_body:             Separator_LeftBracket    int_body                     Separator_RightBracket        { NODE(Maker,(2),2); }
                     | Separator_LeftBracket    int_body                     Separator_Comma               int_body               Separator_RightBracket          { NODE(Maker,(2,4),2); }
                     | Separator_LeftBracket    int_body                     Separator_Comma               int_body               Separator_Comma                 int_body                       Separator_RightBracket       { NODE(Maker,(2,4,6),2); }
                     | Separator_LeftBracket    int_body                     Separator_Comma               int_body               Separator_Comma                 int_body                       Separator_Comma              int_body                     Separator_RightBracket       { NODE(Maker,(2,4,6,8),2); }
                     | Separator_LeftBracket    int_body                     Separator_Comma               int_body               Separator_Comma                 int_body                       Separator_Comma              int_body                     Separator_Comma              int_body                     Separator_RightBracket       { NODE(Maker,(2,4,6,8,10),2); }
                     ;

int_body:              Integer_lexeme           { NODE(Maker,(1),3); }
                     | Ident_lexeme             { NODE(Maker,(1),3); }
                     | Ident_lexeme             Separator_ColonColon         Ident_lexeme                  { NODE(Maker,(1,3),3); }
                     | Oper_Sub                 Integer_lexeme               { NODE(Maker,(2),4); }
                     ;

Maker_Turn:            Separator_LeftCramp      Reserv_Turn                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 Ident_lexeme                   Separator_Comma              int_body                     Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { NODE(Maker,(4,6,8),5); }
                     | Separator_LeftCramp      Reserv_Turn                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 Ident_lexeme                   Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { NODE(Maker,(4,6),5); }
                     ;

Maker_Call:            Separator_LeftCramp      Reserv_Call                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 int_body                       Separator_Comma              int_body                     Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { NODE(Maker,(4,6,8),6); }
                     | Separator_LeftCramp      Reserv_Call                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 int_body                       Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { NODE(Maker,(4,6),6); }
                     ;
