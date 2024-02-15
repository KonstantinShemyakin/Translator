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

S_                   : rules                        
                     ;

rules                : rules                    rule                         { NODE(Formula,(0,1,2),1); }  // rules(Formulas).add(rule)
                     | rule                     { NODE(Formula,(0,1),0); }   // create(Formulas).add(rule)
                     ;

rule                 : <Space>                  <Separator,BNFSet>           item_list                     { NODE(Formula,(1,3),0); }      // create(Formula).add(item_list(Produce))
                     ;

item_list            : item_list                item_symbol                  { NODE(Produce,(2,1),7); }    // item_list.add(item)
                     | item_symbol              { NODE(Produce,(1),8); }     // create(Produce).add(item)
                     ;

item_symbol          : <Space>
                     | item
                     ;

item                 : <Separator,LeftScrape>   or_list                      <Separator,RightScrape>       { NODE(Item,(1,2),5); }         // create(Item).ref(or_list(Formula))
                     | <Separator,LeftScrape>   or_list                      <Separator,RightScrape>       <Separator,Ellipsis>            { NODE(Item,(4,2),5); }         // create(Item).ref(or_list(Formula))
                     | <Separator,LeftCramp>    or_list                      <Separator,RightCramp>        { NODE(Item,(1,2),5); }         // create(Item).ref(or_list(Formula))
                     | Maker_item
                     ;

or_list              : or_list                  <Oper,Or>                    item_list                     { NODE(Formula,(2,1,3),1); }    // or_list(Formula).add(item_list(Produce))
                     | item_list                { NODE(Formula,(0,1),0); }   // create(Formula).add(item_list(Produce))
                     ;

Maker_item:            Maker_Make
                     | Maker_Node
                     | Maker_Turn
                     | Maker_Call
                     ;

Maker_Make:            <Separator,LeftMaker>    Ident_Maker                  <Separator,LeftBracket>       <Ident>                <Separator,Comma>               int_body                       <Separator,RightBracket>     <Separator,Semicolon>        <Separator,RightMaker>       { NODE(Maker,(2,4,6),0); }
                     | <Separator,LeftMaker>    Ident_Maker                  <Separator,LeftBracket>       <Ident>                <Separator,RightBracket>        <Separator,Semicolon>          <Separator,RightMaker>       { NODE(Maker,(2,4),0); }
                     ;

Ident_Maker:           <Reserv,All>
                     | <Reserv,Make>
                     | <Reserv,Code>
                     | <Reserv,Tree>
                     | <Reserv,Yacc>
                     ;

Maker_Node:            <Separator,LeftMaker>    <Reserv,Node>                <Separator,LeftBracket>       <Ident>                <Separator,Comma>               node_body                      <Separator,Comma>            int_body                     <Separator,RightBracket>     <Separator,Semicolon>        <Separator,RightMaker>       { NODE(Maker,(4,6,8),1); }
                     | <Separator,LeftMaker>    <Reserv,Node>                <Separator,LeftBracket>       <Ident>                <Separator,Comma>               node_body                      <Separator,RightBracket>     <Separator,Semicolon>        <Separator,RightMaker>       { NODE(Maker,(4,6),1); }
                     ;

node_body:             <Separator,LeftBracket>  int_body                     <Separator,RightBracket>      { NODE(Maker,(2),2); }
                     | <Separator,LeftBracket>  int_body                     <Separator,Comma>             int_body               <Separator,RightBracket>        { NODE(Maker,(2,4),2); }
                     | <Separator,LeftBracket>  int_body                     <Separator,Comma>             int_body               <Separator,Comma>               int_body                       <Separator,RightBracket>     { NODE(Maker,(2,4,6),2); }
                     | <Separator,LeftBracket>  int_body                     <Separator,Comma>             int_body               <Separator,Comma>               int_body                       <Separator,Comma>            int_body                     <Separator,RightBracket>     { NODE(Maker,(2,4,6,8),2); }
                     | <Separator,LeftBracket>  int_body                     <Separator,Comma>             int_body               <Separator,Comma>               int_body                       <Separator,Comma>            int_body                     <Separator,Comma>            int_body                     <Separator,RightBracket>     { NODE(Maker,(2,4,6,8,10),2); }
                     ;

int_body:              <Integer>                { NODE(Maker,(1),3); }
                     | <Ident>                  { NODE(Maker,(1),3); }
                     | <Ident>                  <Separator,ColonColon>       <Ident>                       { NODE(Maker,(1,3),3); }
                     | <Oper,Sub>               <Integer>                    { NODE(Maker,(2),4); }
                     ;

Maker_Turn:            <Separator,LeftMaker>    <Reserv,Turn>                <Separator,LeftBracket>       <Ident>                <Separator,Comma>               <Ident>                        <Separator,Comma>            int_body                     <Separator,RightBracket>     <Separator,Semicolon>        <Separator,RightMaker>       { NODE(Maker,(4,6,8),5); }
                     | <Separator,LeftMaker>    <Reserv,Turn>                <Separator,LeftBracket>       <Ident>                <Separator,Comma>               <Ident>                        <Separator,RightBracket>     <Separator,Semicolon>        <Separator,RightMaker>       { NODE(Maker,(4,6),5); }
                     ;

Maker_Call:            <Separator,LeftMaker>    <Reserv,Turn>                <Separator,LeftBracket>       int_body               <Separator,Comma>               <Ident>                        <Separator,Comma>            int_body                     <Separator,RightBracket>     <Separator,Semicolon>        <Separator,RightMaker>       { NODE(Maker,(4,6,8),6); }
                     | <Separator,LeftMaker>    <Reserv,Turn>                <Separator,LeftBracket>       int_body               <Separator,Comma>               <Ident>                        <Separator,RightBracket>     <Separator,Semicolon>        <Separator,RightMaker>       { NODE(Maker,(4,6),6); }
                     ;
