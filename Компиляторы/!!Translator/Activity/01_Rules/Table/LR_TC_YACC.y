%{

enum class T_Maker { DefType, ExpressionSLL, ExpressionSLR, AddToList, MakerSNode, SaveLexeme, Number, Ident, 
                     Label, Params, BegIndexLL, BegIndexLR, IndexLL, IndexLR, EndIndex, Binary, 
                     Unary, IncDec, Primary, Cast, Question, ExpressionsLL, ExpressionsLR, DefParVar, 
                     DefParArr, ParVarAssign, EndParams, FuncIdent, BodyFunc, EndAInit, DefArray, DRange, 
                     DefArrD1AEmpty, DefIdent, DefVarAssign, PushDef, RefDef, Define, BegDo, Do, 
                     BegWhile, While, BegFor, For, If, GoTo, Break, Continue, 
                     Return, BegStmExprLL, BegStmExprLR, Compaund, NodeNull, NodeListLL, NodeListLR, EndBlock, 
                     Part, PopType, AddToExpr, BegQuestion, MidQuestion, MidDo, MidWhile, BegIf, 
                     Then, Else, PrefFor, ConditionFor, PostFor, EndDefine, EndRanges, BegAInit, 
                     AInitItem, BegInitial, EndInitial, BegDefVarAssign, BegParVarAssign, MakerCall, MakerTurn, LexTypeName, 
                     Expressions
};


enum class S_Node  { None, Node, Unary, Binary, Logical, Trio, Number, Primary, 
                     Type, Cast, IncDec, Expressions, Compaund, Statements, DefVar, DefArr, 
                     DefFunc, Define, Var, Call, Index, For, While, Do, 
                     Label, GoTo, Break, Continue, Return, If, SwitchCase, SwitchItem, 
                     Switch, List, Ranges, Null, NodeOne, NodeTwo, RefDef, Lexeme, 
                     Param, Formula, Produce, Maker, Tokens, Enums, Item
};

#define YYPARSE_PARAM parm
#define YYLEX_PARAM parm
#define YYERROR_VERBOSE
#define YYSTYPE T_Lexeme_SNode
%}
%pure_parser
%name-prefix="yy_"
%no-lines
%debug

%token Oper_AddAssign              262 // 0X0106
%token Oper_SubAssign              263 // 0X0107
%token Oper_MultiAssign            264 // 0X0108
%token Oper_DivAssign              265 // 0X0109
%token Oper_ModAssign              266 // 0X010A
%token Oper_AndAssign              267 // 0X010B
%token Oper_OrAssign               268 // 0X010C
%token Oper_XOrAssign              269 // 0X010D
%token Oper_Assign                 270 // 0X010E
%token Oper_LShiftAssign           288 // 0X0120
%token Oper_RShiftAssign           289 // 0X0121
%token Separator_LeftCramp         546 // 0X0222
%token Separator_RightCramp        547 // 0X0223
%token Separator_LeftBracket       548 // 0X0224
%token Separator_RightBracket      549 // 0X0225
%token Separator_LeftScrape        550 // 0X0226
%token Separator_RightScrape       551 // 0X0227
%token Separator_Comma             556 // 0X022C
%token Separator_Semicolon         557 // 0X022D
%token Separator_Colon             558 // 0X022E
%token Integer_lexeme              768 // 0X0300
%token Number_lexeme              1024 // 0X0400
%token Ident_lexeme               1536 // 0X0600
%token Reserv_For                 1793 // 0X0701
%token Reserv_While               1794 // 0X0702
%token Reserv_If                  1795 // 0X0703
%token Reserv_Else                1796 // 0X0704
%token Reserv_Do                  1797 // 0X0705
%token Reserv_GoTo                1798 // 0X0706
%token Reserv_Continue            1799 // 0X0707
%token Reserv_Break               1800 // 0X0708
%token Reserv_Return              1801 // 0X0709
%token Reserv_Switch              1802 // 0X070A
%token Priority_Question          2818 // 0X0B02
%left  Priority_OrOr              2819 // 0X0B03
%left  Priority_AndAnd            2820 // 0X0B04
%left  Priority_Or                2821 // 0X0B05
%left  Priority_XOr               2822 // 0X0B06
%left  Priority_And               2823 // 0X0B07
%left  Priority_Equ               2824 // 0X0B08
%left  Priority_Compare           2825 // 0X0B09
%left  Priority_Shift             2826 // 0X0B0A
%left  Priority_Term              2827 // 0X0B0B
%left  Priority_Factor            2828 // 0X0B0C
%token Priority_Unary             2829 // 0X0B0D
%token Priority_IncDec            2830 // 0X0B0E
%token Syntax_IdentFunc           3073 // 0X0C01
%token Syntax_IdentArr            3074 // 0X0C02
%token Syntax_DefFunc             3075 // 0X0C03
%token Syntax_DefArr              3076 // 0X0C04
%token Syntax_DefVar              3077 // 0X0C05
%token Syntax_Label               3079 // 0X0C07
%token Syntax_Cast                3080 // 0X0C08
%token Syntax_CastUnary           3081 // 0X0C09
%token Syntax_EmptyCramp          3082 // 0X0C0A
%token Syntax_EmptyBracket        3083 // 0X0C0B
%token Syntax_EmptyScrape         3084 // 0X0C0C
%%

Program:                    Defines                  
                          ;

DefBegParVar:               Ident_lexeme             { SAVE($1); }            { MAKE(DefParVar,0); }   
                          ;

DefParVar:                  DefBegParVar             Oper_Assign              { SAVE($2); }            { CODE(BegParVarAssign,0); }                      Assign                   { MAKE(ParVarAssign,0); }
                          | DefBegParVar             
                          ;

DefBegParArr:               Syntax_IdentArr          { SAVE($1); }            { MAKE(DefParArr,0); }   DefBegRanges             
                          ;

DefParArr:                  DefBegParArr             Oper_Assign              { SAVE($2); }            { CODE(BegParVarAssign,0); }                      Assign                   { MAKE(ParVarAssign,0); }
                          | DefBegParArr             
                          ;

DefParItem:                 Syntax_DefArr            { SAVE($1); }            DefParArr                
                          | Syntax_DefVar            { SAVE($1); }            DefParVar                
                          ;

DefParams:                  DefParams                Separator_Comma          DefParItem               { TREE(AddToList,0); }   
                          | DefParItem               { TREE(AddToList,0); }   
                          ;

BodyFunc:                   Separator_Semicolon      { MAKE(BodyFunc,0); }    
                          | Syntax_EmptyCramp        { MAKE(BodyFunc,1); }    
                          | Separator_LeftCramp      { CODE(EndParams,0); }   { MAKE(BegStmExprLR,0); }StmExpr                  Separator_RightCramp     { MAKE(BodyFunc,2); }    
                          ;

DefFunc_:                   Syntax_EmptyBracket      { TREE(EndParams,2); }   
                          | Separator_LeftBracket    { TREE(Define,2); }      DefParams                Separator_RightBracket   { TREE(EndParams,0); }   
                          ;

DefFunc:                    Syntax_DefFunc           { SAVE($1); }            Syntax_IdentFunc         { SAVE($3); }            { MAKE(FuncIdent,0); }   DefFunc_                 BodyFunc                 
                          ;

AInitItem:                  Initializer              
                          | Assign                   { CODE(AInitItem,0); }   
                          ;

AInitial:                   AInitial                 Separator_Comma          AInitItem                { TREE(AddToList,0); }   
                          | AInitItem                { TREE(AddToList,0); }   
                          ;

Initializer:                Syntax_EmptyCramp        { CODE(BegInitial,0); }  { TREE(NodeListLR,0); }  
                          | Separator_LeftCramp      { CODE(BegInitial,1); }  { TREE(NodeListLR,0); }  AInitial                 Separator_RightCramp     { CODE(EndInitial,0); }  
                          ;

DefRanges_:                 Separator_LeftScrape     Assign                   Separator_RightScrape    
                          ;

DefRanges:                  DefRanges                DefRanges_               { MAKE(DRange,0); }      
                          | DefRanges_               { MAKE(DRange,0); }      
                          ;

DefBegRanges:               Syntax_EmptyScrape       { MAKE(DefArrD1AEmpty,0); }                       DefRanges                
                          | Syntax_EmptyScrape       { MAKE(DefArrD1AEmpty,0); }                       
                          | DefRanges                
                          ;

DefBegArr:                  Syntax_IdentArr          { SAVE($1); }            { MAKE(DefArray,0); }    DefBegRanges             { CODE(EndRanges,0); }   
                          ;

DefArr:                     DefBegArr                Oper_Assign              { SAVE($2); }            { CODE(BegAInit,0); }    Initializer              { MAKE(EndAInit,0); }    
                          | DefBegArr                
                          ;

DefVarIdent:                Ident_lexeme             { SAVE($1); }            { MAKE(DefIdent,0); }    
                          ;

DefVarAssign:               Oper_Assign              { SAVE($1); }            { CODE(BegDefVarAssign,0); }                      Assign                   { MAKE(DefVarAssign,0); }
                          ;

DefVar:                     DefVarIdent              DefVarAssign             
                          | DefVarIdent              
                          ;

DefIAV:                     DefArr                   
                          | DefVar                   
                          ;

RefDefIAV:                  Priority_And             { SAVE($1); }            DefIAV                   { TREE(RefDef,0); }      
                          ;

DefItem:                    RefDefIAV                
                          | DefIAV                   
                          ;

DefType:                    Syntax_DefArr            { SAVE($1); }            
                          | Syntax_DefVar            { SAVE($1); }            
                          ;

DefineComma:                DefineComma              Separator_Comma          DefItem                  { TREE(AddToList,0); }   
                          | DefItem                  { TREE(AddToList,0); }   
                          ;

Define:                     DefType                  { MAKE(Define,0); }      DefineComma              { CODE(EndDefine,0); }   
                          ;

Expressions:                Expressions              Separator_Comma          Assign                   { TREE(AddToList,0); }   { CODE(AddToExpr,0); }   
                          | Assign                   { MAKE(ExpressionsLR,0); }                        
                          ;

PriorAssign:                Oper_AddAssign           { SAVE($1); }            
                          | Oper_SubAssign           { SAVE($1); }            
                          | Oper_MultiAssign         { SAVE($1); }            
                          | Oper_DivAssign           { SAVE($1); }            
                          | Oper_ModAssign           { SAVE($1); }            
                          | Oper_Assign              { SAVE($1); }            
                          | Oper_OrAssign            { SAVE($1); }            
                          | Oper_XOrAssign           { SAVE($1); }            
                          | Oper_AndAssign           { SAVE($1); }            
                          | Oper_LShiftAssign        { SAVE($1); }            
                          | Oper_RShiftAssign        { SAVE($1); }            
                          ;

Assign:                     Question                 PriorAssign              Assign                   { MAKE(Binary,0); }      
                          | Question                 
                          ;

Question:                   Binary                   Priority_Question        { SAVE($2); }            { CODE(BegQuestion,0); } ExpressionValue          Separator_Colon          { CODE(MidQuestion,0); } Question                 { MAKE(Question,0); }    
                          | Binary                   
                          ;

Binary:                     Binary                   Priority_OrOr            { SAVE($2); }            Binary                   { MAKE(Binary,0); }      
                          | Binary                   Priority_AndAnd          { SAVE($2); }            Binary                   { MAKE(Binary,0); }      
                          | Binary                   Priority_Or              { SAVE($2); }            Binary                   { MAKE(Binary,0); }      
                          | Binary                   Priority_XOr             { SAVE($2); }            Binary                   { MAKE(Binary,0); }      
                          | Binary                   Priority_And             { SAVE($2); }            Binary                   { MAKE(Binary,0); }      
                          | Binary                   Priority_Equ             { SAVE($2); }            Binary                   { MAKE(Binary,0); }      
                          | Binary                   Priority_Compare         { SAVE($2); }            Binary                   { MAKE(Binary,0); }      
                          | Binary                   Priority_Shift           { SAVE($2); }            Binary                   { MAKE(Binary,0); }      
                          | Binary                   Priority_Term            { SAVE($2); }            Binary                   { MAKE(Binary,0); }      
                          | Binary                   Priority_Factor          { SAVE($2); }            Binary                   { MAKE(Binary,0); }      
                          | Unary                    
                          ;

UnaryIncDec:                PrimaryExpr              Priority_IncDec          { SAVE($2); }            { MAKE(IncDec,0); }      
                          | PrimaryExpr              
                          ;

Unary:                      Priority_Unary           { SAVE($1); }            Unary                    { MAKE(Unary,0); }       
                          | Priority_Term            { SAVE($1); }            Unary                    { MAKE(Unary,0); }       
                          | Priority_IncDec          { SAVE($1); }            Unary                    { MAKE(Unary,0); }       
                          | Syntax_CastUnary         { SAVE($1); }            Unary                    { MAKE(Cast,0); }        
                          | UnaryIncDec              
                          ;

Primary:                    Separator_LeftBracket    ExpressionNone           Separator_RightBracket   { TREE(Primary,0); }     
                          ;

PrimaryExpr:                Integer_lexeme           { SAVE($1); }            { MAKE(Number,0); }      
                          | Number_lexeme            { SAVE($1); }            { MAKE(Number,0); }      
                          | Syntax_IdentArr          { SAVE($1); }            Ranges                   { MAKE(EndIndex,0); }    
                          | Syntax_IdentFunc         { SAVE($1); }            CallParams               
                          | Syntax_Cast              { SAVE($1); }            Primary                  { MAKE(Cast,0); }        
                          | Ident_lexeme             { SAVE($1); }            { MAKE(Ident,0); }       
                          | Primary                  
                          ;

Range:                      Separator_LeftScrape     ExpressionValue          Separator_RightScrape    
                          ;

Ranges:                     Ranges                   Range                    { MAKE(IndexLR,0); }     
                          | Range                    { MAKE(BegIndexLR,0); }  
                          ;

CallParams:                 Syntax_EmptyBracket      { MAKE(Params,0); }      
                          | Separator_LeftBracket    ExpressionValueList      Separator_RightBracket   { MAKE(Params,1); }      
                          ;

CompaundStmnt:              Syntax_EmptyCramp        { MAKE(Compaund,0); }    { CODE(EndBlock,0); }    
                          | Separator_LeftCramp      { MAKE(Compaund,0); }    StmExpr                  Separator_RightCramp     
                          ;

Condition_V:                Priority_And             { SAVE($1); }            DefVarAssign             { TREE(RefDef,0); }      
                          | DefVarAssign             
                          ;

Condition:                  Syntax_DefVar            { SAVE($1); }            { MAKE(Define,0); }      Condition_V              { MAKE(PushDef,0); }     
                          | ExpressionCondition      
                          ;

For_Prefix:                 Separator_Semicolon      { TREE(NodeNull,0); }    
                          | DefineSemi               
                          | ExprSemi                 
                          ;

For_Condition:              Separator_Semicolon      { MAKE(NodeNull,0); }    
                          | Condition                Separator_Semicolon      
                          ;

For_Postfix:                Separator_RightBracket   { TREE(NodeNull,0); }    
                          | ExpressionExpression     Separator_RightBracket   
                          ;

ForStmnt:                   Reserv_For               Separator_LeftBracket    { MAKE(BegFor,0); }      For_Prefix               { CODE(PrefFor,0); }     For_Condition            { CODE(ConditionFor,0); }For_Postfix              { CODE(PostFor,0); }     DefExpr                  { MAKE(For,0); }         
                          ;

ReturnValue:                Separator_Semicolon      { MAKE(Return,0); }      
                          | ExpressionValue          Separator_Semicolon      { MAKE(Return,1); }      
                          ;

ReturnStmnt:                Reserv_Return            ReturnValue              
                          ;

BegIfStmnt:                 Reserv_If                Separator_LeftBracket    { CODE(BegIf,0); }       Condition                Separator_RightBracket   { CODE(Then,0); }        DefExpr                  
                          ;

Statement:                  BegIfStmnt               Reserv_Else              { CODE(Else,0); }        DefExpr                  { MAKE(If,1); }          
                          | BegIfStmnt               { MAKE(If,0); }          
                          | Syntax_Label             { SAVE($1); }            Separator_Colon          { CODE(Label,0); }       DefExpr                  { TREE(Label,0); }       
                          | Reserv_Do                { MAKE(BegDo,0); }       DefExpr                  Reserv_While             Separator_LeftBracket    Condition                Separator_RightBracket   Separator_Semicolon      { MAKE(Do,0); }          
                          | Reserv_While             { MAKE(BegWhile,0); }    Separator_LeftBracket    Condition                Separator_RightBracket   DefExpr                  { MAKE(While,0); }       
                          | ForStmnt                 
                          | Reserv_Switch            Separator_LeftBracket    Separator_RightBracket   
                          | Reserv_GoTo              Ident_lexeme             { SAVE($2); }            Separator_Semicolon      { MAKE(GoTo,0); }        
                          | Reserv_Break             Separator_Semicolon      { MAKE(Break,0); }       
                          | Reserv_Continue          Separator_Semicolon      { MAKE(Continue,0); }    
                          | ReturnStmnt              
                          | CompaundStmnt            
                          ;

DefineSemi:                 Define                   Separator_Semicolon      
                          ;

ExprSemi:                   ExpressionExpression     Separator_Semicolon      
                          ;

DefExpr:                    Separator_Semicolon      { TREE(NodeNull,0); }    
                          | DefineSemi               
                          | Statement                
                          | ExprSemi                 
                          ;

StmExprList:                StmExprList              DefExpr                  { TREE(AddToList,0); }   
                          | DefExpr                  { TREE(AddToList,0); }   
                          ;

StmExpr:                    StmExprList              { CODE(EndBlock,0); }    
                          ;

DefFAV:                     Separator_Semicolon      { TREE(NodeNull,0); }    
                          | DefFunc                  
                          | DefineSemi               
                          ;

DefinesList:                DefinesList              DefFAV                   { TREE(AddToList,0); }   
                          | DefFAV                   { TREE(BegStmExprLR,1); }
                          ;

Defines:                    { CODE(BegStmExprLR,0); }DefinesList              { CODE(EndBlock,0); }    
                          ;

ExpressionExpression:       Expressions              { MAKE(ExpressionSLR,16); }                       
                          ;

ExpressionCondition:        Expressions              { MAKE(ExpressionSLR,241); }                      
                          ;

ExpressionNone:             Expressions              { MAKE(ExpressionSLR,0); }                        
                          ;

ExpressionValue:            Expressions              { MAKE(ExpressionSLR,256); }                      
                          ;

ExpressionValueList:        Expressions              { MAKE(ExpressionSLR,512); }                      
                          ;
%%
