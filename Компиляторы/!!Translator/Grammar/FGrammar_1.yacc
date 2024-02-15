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
                     Switch, List, Ranges, Null, NodeOne, NodeTwo, RefDef
};

#define YYPARSE_PARAM parm
#define YYLEX_PARAM parm
#define YYERROR_VERBOSE
#define YYSTYPE T_Lexeme_SNode
%}
%pure_parser
%name-prefix="yy_nl_"
%no-lines
%debug

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

Grammar:               Enum_part                Token_part                   Rules                         Separator_ModMod       { MAKER_Formulas; }
                     | Enum_part                Token_part                   Rules                         { MAKER_Formulas; }
                     ;

Enum_part:             /*empty*/
                     | Separator_ModBegin       Enums                        Separator_ModEnd
                     ;
                     
Enums:                 Enums                    Enum
                     | Enum
                     ;

Enum:                  Reserv_Enum              Separator_LeftCramp          { MAKER_Enum_Create($2); }    enum_list              Separator_RightCramp            Separator_Semicolon
                     | Reserv_Enum              Ident_lexeme                 { MAKER_Enum_Create($2); }    Separator_LeftCramp    enum_list                       Separator_RightCramp           Separator_Semicolon
                     | Reserv_Enum              Reserv_Class                 Ident_lexeme                  Separator_LeftCramp    { MAKER_Enum_Create($3); }      enum_list                      Separator_RightCramp         Separator_Semicolon
                     ;

enum_list:             enum_list                Separator_Comma              enum_item                       
                     | enum_item                
                     ;

enum_item:             Ident_lexeme             Oper_Assign                  Integer_lexeme                { MAKER_Enum_FirstItem($1, $3); } 
                     | Ident_lexeme             { MAKER_Enum_Item($1); }
                     ;

Token_part:            /*empty*/
                     | Tokens                   Separator_ModMod
                     ;
    
Tokens:                Tokens                   Token
                     | Token                    
                     ;       

Token:                 Separator_ModToken       Ident_lexeme                  Integer_lexeme         { MAKER_Tokens($2, $3); }
                     ;

Rules:                 Rules                    Formula 
                     | Formula
                     ;

Formula:               Ident_lexeme             Separator_Colon              { MAKER_Formula($1); }        Produces               Separator_Semicolon
                     ;

Produces:              Produces                 Oper_Or                      Produce
                     | Produce
                     ;

Produce:               Produce                  produce_item
                     | { MAKER_Produce; }
                     ;

produce_item:          Maker_Make
                     | Maker_Node
                     | Maker_Turn
                     | Maker_Call
                     | Ident_lexeme             { MAKER_Ident($1); }
                     | Integer_lexeme           { MAKER_Integer($1); }
                     | Oper_LT                  lexeme_item                  Oper_GT                       { MAKER_Lexeme1($2); }
                     | Oper_LT                  lexeme_item                  Separator_Comma               lexeme_item            Oper_GT                         { MAKER_Lexeme2($2, $4); }
                     ;

lexeme_item:           Ident_lexeme
                     | Integer_lexeme
                     ;

Maker_Make:            Separator_LeftCramp      Ident_Maker                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 int_body                       Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { MAKER_Make($2, $4, $6); }
                     | Separator_LeftCramp      Ident_Maker                  Separator_LeftBracket         Ident_lexeme           Separator_RightBracket          Separator_Semicolon            Separator_RightCramp         { MAKER_Make($2, $4, $$); }
                     ;

Ident_Maker:           Reserv_Make
                     | Reserv_Code
                     | Reserv_Tree
                     | Reserv_Yacc
                     | Reserv_All
                     ;

Maker_Node:            Separator_LeftCramp      Reserv_Node                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 node_body                      Separator_Comma              int_body                     Separator_RightBracket       Separator_Semicolon          Separator_RightCramp        { MAKER_Node($4, $6, $8); }
                     | Separator_LeftCramp      Reserv_Node                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 node_body                      Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { MAKER_Node($4, $6, $0); }
                     ;

node_body:             Separator_LeftBracket    int_body                     Separator_RightBracket        { MAKER_Syn_Tree($2, $$, $$, $$, $$, $$); }
                     | Separator_LeftBracket    int_body                     Separator_Comma               int_body               Separator_RightBracket          { MAKER_Syn_Tree($2, $4, $$, $$, $$, $$); }
                     | Separator_LeftBracket    int_body                     Separator_Comma               int_body               Separator_Comma                 int_body                       Separator_RightBracket       { MAKER_Syn_Tree($2, $4, $6, $$, $$, $$); }
                     | Separator_LeftBracket    int_body                     Separator_Comma               int_body               Separator_Comma                 int_body                       Separator_Comma              int_body                     Separator_RightBracket       { MAKER_Syn_Tree($2, $4, $6, $8, $$, $$); }
                     | Separator_LeftBracket    int_body                     Separator_Comma               int_body               Separator_Comma                 int_body                       Separator_Comma              int_body                     Separator_Comma              int_body                    Separator_RightBracket     { MAKER_Syn_Tree($2, $4, $6, $8, $10, $$); }
                     ;

int_body:              Integer_lexeme           { MAKER_Enum_1($1, $$); } 
                     | Ident_lexeme             { MAKER_Enum_1($1, $$); } 
                     | Ident_lexeme             Separator_ColonColon         Ident_lexeme                  { MAKER_Enum_2($1, $3, $$); }
                     | Oper_Sub                 Integer_lexeme               { MAKER_Enum_3($2, $$); }
                     ;

Maker_Turn:            Separator_LeftCramp      Reserv_Turn                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 Ident_lexeme                   Separator_Comma              int_body                     Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { MAKER_Turn($4, $6, $8); }
                     | Separator_LeftCramp      Reserv_Turn                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 Ident_lexeme                   Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { MAKER_Turn($4, $6, $0); }
                     ;

Maker_Call:            Separator_LeftCramp      Reserv_Call                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 int_body                       Separator_Comma              int_body                     Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { MAKER_Call($4, $6, $8); }
                     | Separator_LeftCramp      Reserv_Call                  Separator_LeftBracket         Ident_lexeme           Separator_Comma                 int_body                       Separator_RightBracket       Separator_Semicolon          Separator_RightCramp         { MAKER_Call($4, $6, $0); }
                     ;
