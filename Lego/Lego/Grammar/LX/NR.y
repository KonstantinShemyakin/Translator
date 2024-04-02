
S_                       
                         :   Program                  
                         ;
Program                  
                         :   Defines                     { NODE(None,(1),1); }    
                         ;
DefParType               
                         :   <Reserv,Const>              <Syntax,DefType>            <Oper,And>                  { ALL(DefType,11); }     
                         |   <Syntax,DefType>            <Oper,And>                  { ALL(DefType,9); }      
                         |   <Reserv,Const>              <Syntax,DefType>            { ALL(DefType,3); }      
                         |   <Syntax,DefType>            { ALL(DefType,1); }      
                         ;
DefBegParVar             
                         :   DefParType                  <Ident>                     { MAKE(DefParVar); }        { NODE(DefVar,(2,1),1); }
                         ;
DefParVar                
                         :   DefBegParVar                <Oper,Assign>               { CODE(BegParVarAssign); }                           Assign                      { MAKE(ParVarAssign); }     { NODE(DefVar,(2,1,3),2); }                       
                         |   DefBegParVar             
                         ;
DefBegParArr             
                         :   DefParType                  <Ident>                     { MAKE(DefParArr); }        DefBegRanges                { NODE(DefArr,(2,1,0,3),1); }                     
                         ;
DefParArr                
                         :   DefBegParArr                <Oper,Assign>               { CODE(BegParVarAssign); }                           Assign                      { MAKE(ParVarAssign); }     { NODE(DefArr,(2,1,3),2); }                       
                         |   DefBegParArr             
                         ;
DefParItem               
                         :   DefParArr                
                         |   DefParVar                
                         ;
DefParams                
                         :   DefParams                   <Separator,Comma>           DefParItem                  { TREE(AddToList); }        { YACC(AddToList,5); }   
                         |   DefParItem                  { TREE(AddToList); }        { NODE(Define,(0,0,1)); }
                         ;
BodyFunc                 
                         :   <Separator,Semicolon>       { MAKE(BodyFunc); }         { NODE(NodeOne,(1)); }   
                         |   <Separator,LeftCramp>       <Separator,RightCramp>      { MAKE(BodyFunc,1); }       { NODE(NodeOne,(1),1); } 
                         |   <Separator,LeftCramp>       { CODE(EndParams); }        { MAKE(BegStmExprLR); }     StmExpr                     <Separator,RightCramp>      { MAKE(BodyFunc,2); }       { NODE(NodeOne,(1,2),2); }                        
                         ;
DefFuncParBody           
                         :   <Separator,RightBracket>    { TREE(EndParams,1); }      { NODE(Define,(0)); }    
                         |   DefParams                   <Separator,RightBracket>    { TREE(EndParams); }     
                         ;
DefParBodyFunc           
                         :   { TREE(Define,2); }         DefFuncParBody              BodyFunc                    { NODE(NodeTwo,(0,1,2)); }                        
                         ;
DefVoidType              
                         :   <Reserv,Static>             <Reserv,Void>               { ALL(DefType,36); }     
                         |   <Reserv,Void>               { ALL(DefType,32); }     
                         ;
DefType                  
                         :   <Reserv,Static>             <Reserv,Const>              <Syntax,DefType>            { ALL(DefType,7); }      
                         |   <Reserv,Static>             <Syntax,DefType>            { ALL(DefType,5); }      
                         |   <Reserv,Const>              <Syntax,DefType>            { ALL(DefType,3); }      
                         |   <Syntax,DefType>            { ALL(DefType,1); }      
                         ;
CommaDefItem             
                         :   CommaDefItem                <Separator,Comma>           DefItem                     { TREE(AddToList); }        { YACC(AddToList,5); }   
                         |   DefItem                     { TREE(AddToList); }        { NODE(Define,(0,0,1)); }
                         ;
Define                   
                         :   DefType                     { MAKE(Define,1); }         CommaDefItem                { CODE(EndDefine); }        { NODE(Define,(0,1,0,2),1); }                     
                         ;
DefineBegRanges          
                         :   <Separator,RightScrape>     { MAKE(DefArrD1AEmpty); }   DefRanges                   { NODE(Ranges,(1,2),1); }
                         |   <Separator,RightScrape>     { MAKE(DefArrD1AEmpty); }   { NODE(Ranges,(1)); }    
                         |   Assign                      <Separator,RightScrape>     { MAKE(DRange); }           DefRanges                   { NODE(Ranges,(0,3,1),4); }                       
                         |   Assign                      <Separator,RightScrape>     { MAKE(DRange); }           { NODE(Ranges,(0,1),2); }
                         ;
DefineBegArr             
                         :   DefineBegRanges             { CODE(EndRanges); }     
                         ;
DefineArr                
                         :   IdentLeftScrape             <Oper,Assign>               { CODE(BegAInit); }         Initializer                 { MAKE(EndAInit); }         { NODE(DefArr,(0,1,3),2); }                       
                         |   IdentLeftScrape          
                         ;
IdentLeftScrape          
                         :   <Ident>                     <Separator,LeftScrape>      { MAKE(Define); }           { MAKE(DefArray); }         DefineBegArr                { NODE(DefArr,(1,0,0,3),1); }                     
                         ;
DefineVarAssign          
                         :   <Separator,Comma>           CommaDefItem                <Separator,Semicolon>       { CODE(EndDefine); }        { NODE(None,(2)); }      
                         |   <Separator,Semicolon>       { CODE(EndDefine); }     
                         ;
DefVariableAssign        
                         :   <Ident>                     { MAKE(Define); }           { MAKE(DefIdent); }         <Oper,Assign>               { CODE(BegDefVarAssign); }                           Assign                      { MAKE(DefVarAssign); }     { TREE(AddToList); }        { NODE(DefVar,(1,0,3),1); }                       
                         ;
DefVarComma              
                         :   <Ident>                     { MAKE(Define); }           { MAKE(DefIdent); }         { TREE(AddToList); }        { NODE(DefVar,(1)); }    
                         ;
DefVarSemicolon          
                         :   <Ident>                     { MAKE(Define); }           { MAKE(DefIdent); }         { TREE(AddToList); }        { NODE(DefVar,(1)); }    
                         ;
DefFuncArrVar            
                         :   DefType                     <Ident>                     <Separator,LeftBracket>     { MAKE(FuncIdent); }        DefParBodyFunc              { NODE(DefFunc,(2,1,4)); }                        
                         |   DefType                     DefineArr                   { TREE(AddToList); }        <Separator,Comma>           CommaDefItem                <Separator,Semicolon>       { CODE(EndDefine); }        { NODE(Define,(0,1,2,4),1); }                     
                         |   DefType                     DefineArr                   { TREE(AddToList); }        <Separator,Semicolon>       { CODE(EndDefine); }        { NODE(Define,(0,1,2)); }
                         |   DefType                     DefVariableAssign           DefineVarAssign             { NODE(Define,(0,1,2,3),1); }                     
                         |   DefType                     DefVarComma                 <Separator,Comma>           CommaDefItem                <Separator,Semicolon>       { CODE(EndDefine); }        { NODE(Define,(0,1,2,4),1); }                     
                         |   DefType                     DefVarSemicolon             <Separator,Semicolon>       { CODE(EndDefine); }        { NODE(Define,(0,1,2)); }
                         ;
DefFuncDefine            
                         :   DefVoidType                 <Ident>                     <Separator,LeftBracket>     { MAKE(FuncIdent); }        DefParBodyFunc              { NODE(DefFunc,(2,1,4)); }                        
                         |   DefFuncArrVar            
                         ;
AInitItem                
                         :   Initializer              
                         |   Assign                      { CODE(AInitItem); }     
                         ;
AInitial                 
                         :   AInitial                    <Separator,Comma>           AInitItem                   { TREE(AddToList); }        { NODE(List,(0,3,1),1); }
                         |   AInitItem                   { TREE(AddToList); }        { NODE(List,(1,1)); }    
                         ;
Initializer              
                         :   <Separator,LeftCramp>       <Separator,RightCramp>      { CODE(BegInitial); }       { TREE(NodeListLR); }       { NODE(List,(1)); }      
                         |   <Separator,LeftCramp>       { CODE(BegInitial,1); }     { TREE(NodeListLR); }       AInitial                    <Separator,RightCramp>      { CODE(EndInitial); }       { NODE(None,(2)); }      
                         ;
DefRange                 
                         :   <Separator,LeftScrape>      Assign                      <Separator,RightScrape>     { NODE(None,(2)); }      
                         ;
DefRanges                
                         :   DefRanges                   DefRange                    { MAKE(DRange); }           { NODE(Ranges,(0,1,2),3); }                       
                         |   DefRange                    { MAKE(DRange); }           { NODE(Ranges,(0,1),2); }
                         ;
DefBegRanges             
                         :   <Separator,LeftScrape>      <Separator,RightScrape>     { MAKE(DefArrD1AEmpty); }   DefRanges                   { NODE(Ranges,(1,3),1); }
                         |   <Separator,LeftScrape>      <Separator,RightScrape>     { MAKE(DefArrD1AEmpty); }   { NODE(Ranges,(1)); }    
                         |   DefRanges                
                         ;
DefBegArr                
                         :   <Ident>                     { MAKE(DefArray); }         DefBegRanges                { CODE(EndRanges); }        { NODE(DefArr,(1,0,0,2),1); }                     
                         ;
DefArr                   
                         :   DefBegArr                   <Oper,Assign>               { CODE(BegAInit); }         Initializer                 { MAKE(EndAInit); }         { NODE(DefArr,(0,1,3),2); }                       
                         |   DefBegArr                
                         ;
DefVarIdent              
                         :   <Ident>                     { MAKE(DefIdent); }         { NODE(DefVar,(1)); }    
                         ;
DefVarAssign             
                         :   <Oper,Assign>               { CODE(BegDefVarAssign); }                           Assign                      { MAKE(DefVarAssign); }     { NODE(None,(2)); }      
                         ;
DefVar                   
                         :   DefVarIdent                 DefVarAssign                { NODE(DefVar,(0,1,2),2); }                       
                         |   DefVarIdent              
                         ;
DefIAV                   
                         :   DefArr                   
                         |   DefVar                   
                         ;
RefDefIAV                
                         :   <Oper,And>                  DefIAV                      { TREE(RefDef); }           { NODE(RefDef,(1,2)); }  
                         ;
DefItem                  
                         :   RefDefIAV                
                         |   DefIAV                   
                         ;
Expressions              
                         :   Expressions                 <Separator,Comma>           Assign                      { TREE(AddToList); }        { CODE(AddToExpr); }        { YACC(AddToList,5); }   
                         |   Assign                      { MAKE(ExpressionsLR); }    { NODE(Expressions,(1,1)); }                      
                         ;
PriorAssign              
                         :   <Oper,AddAssign>         
                         |   <Oper,SubAssign>         
                         |   <Oper,MultiAssign>       
                         |   <Oper,DivAssign>         
                         |   <Oper,ModAssign>         
                         |   <Oper,Assign>            
                         |   <Oper,OrAssign>          
                         |   <Oper,XOrAssign>         
                         |   <Oper,AndAssign>         
                         |   <Oper,LShiftAssign>      
                         |   <Oper,RShiftAssign>      
                         ;
PriorQuestion            
                         :   <Oper,Question>          
                         ;
PriorOrOr                
                         :   <Oper,OrOr>              
                         ;
PriorAndAnd              
                         :   <Oper,AndAnd>            
                         ;
PriorOr                  
                         :   <Oper,Or>                
                         ;
PriorXOr                 
                         :   <Oper,XOr>               
                         ;
PriorAnd                 
                         :   <Oper,And>               
                         ;
PriorEqu                 
                         :   <Oper,Equ>               
                         |   <Oper,NotEqu>            
                         ;
PriorCompare             
                         :   <Oper,LE>                
                         |   <Oper,LT>                
                         |   <Oper,GE>                
                         |   <Oper,GT>                
                         ;
PriorShift               
                         :   <Oper,LShift>            
                         |   <Oper,RShift>            
                         ;
PriorTerm                
                         :   <Oper,Add>               
                         |   <Oper,Sub>               
                         ;
PriorFactor              
                         :   <Oper,Multi>             
                         |   <Oper,Div>               
                         |   <Oper,Mod>               
                         ;
PriorUnary               
                         :   <Oper,Not>               
                         |   <Oper,Tilda>             
                         ;
PriorIncDec              
                         :   <Oper,PlusPlus>          
                         |   <Oper,MinusMinus>        
                         ;
Assign                   
                         :   Question                    PriorAssign                 Assign                      { MAKE(Binary); }           { NODE(Binary,(2,1,3)); }
                         |   Question                 
                         ;
Question                 
                         :   OrOr                        PriorQuestion               { CODE(BegQuestion); }      ExpressionValue             <Separator,Colon>           { CODE(MidQuestion); }      Question                    { MAKE(Question); }         { NODE(Trio,(2,1,3,5)); }
                         |   OrOr                     
                         ;
OrOr                     
                         :   OrOr                        PriorOrOr                   AndAnd                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   AndAnd                   
                         ;
AndAnd                   
                         :   AndAnd                      PriorAndAnd                 Or                          { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Or                       
                         ;
Or                       
                         :   Or                          PriorOr                     XOr                         { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   XOr                      
                         ;
XOr                      
                         :   XOr                         PriorXOr                    And                         { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   And                      
                         ;
And                      
                         :   And                         PriorAnd                    Equ                         { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Equ                      
                         ;
Equ                      
                         :   Equ                         PriorEqu                    Compare                     { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Compare                  
                         ;
Compare                  
                         :   Compare                     PriorCompare                Shift                       { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Shift                    
                         ;
Shift                    
                         :   Shift                       PriorShift                  Term                        { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Term                     
                         ;
Term                     
                         :   Term                        PriorTerm                   Factor                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Factor                   
                         ;
Factor                   
                         :   Factor                      PriorFactor                 Unary                       { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Unary                    
                         ;
UnaryIncDec              
                         :   PrimaryExpr                 PriorIncDec                 { MAKE(IncDec); }           { NODE(Unary,(2,1),1); } 
                         |   PrimaryExpr              
                         ;
DefTypeCast              
                         :   <Reserv,Const>              <Syntax,DefType>            { ALL(DefType,3); }      
                         |   <Syntax,DefType>            { ALL(DefType,1); }      
                         ;
Unary                    
                         :   PriorUnary                  Unary                       { MAKE(Unary); }            { NODE(Unary,(1,2)); }   
                         |   PriorTerm                   Unary                       { MAKE(Unary); }            { NODE(Unary,(1,2),1); } 
                         |   PriorIncDec                 Unary                       { MAKE(Unary); }            { NODE(Unary,(1,2)); }   
                         |   <Separator,LeftBracket>     DefTypeCast                 <Separator,RightBracket>    Unary                       { MAKE(Cast); }             { NODE(Cast,(2,4)); }    
                         |   UnaryIncDec              
                         ;
Primary                  
                         :   <Separator,LeftBracket>     ExpressionNone              <Separator,RightBracket>    { TREE(Primary); }          { NODE(Primary,(1,2)); } 
                         ;
PrimaryExpr              
                         :   <Integer>                   { MAKE(Number); }           { NODE(Number,(1)); }    
                         |   <Number>                    { MAKE(Number); }           { NODE(Number,(1)); }    
                         |   <Ident>                     Ranges                      { MAKE(EndIndex); }         { NODE(Index,(1,2)); }   
                         |   <Ident>                     CallParams                  { NODE(Call,(1,2)); }    
                         |   <Syntax,DefType>            Primary                     { MAKE(Cast); }             { NODE(Cast,(1,2)); }    
                         |   <Ident>                     { MAKE(Ident); }            { NODE(Var,(1)); }       
                         |   Primary                  
                         ;
Range                    
                         :   <Separator,LeftScrape>      ExpressionValue             <Separator,RightScrape>     { NODE(None,(2)); }      
                         ;
Ranges                   
                         :   Ranges                      Range                       { MAKE(IndexLR); }          { YACC(AddToList,3); }   
                         |   Range                       { MAKE(BegIndexLR); }       { NODE(List,(0,1)); }    
                         ;
CallParams               
                         :   <Separator,LeftBracket>     <Separator,RightBracket>    { MAKE(Params); }           { NODE(List,(1)); }      
                         |   <Separator,LeftBracket>     ExpressionValueList         <Separator,RightBracket>    { MAKE(Params,1); }         { NODE(None,(2)); }      
                         ;
CompaundStmnt            
                         :   <Separator,LeftCramp>       <Separator,RightCramp>      { MAKE(Compaund); }         { CODE(EndBlock); }         { NODE(Statements,(1)); }
                         |   <Separator,LeftCramp>       { MAKE(Compaund); }         StmExpr                     <Separator,RightCramp>      { NODE(None,(2)); }      
                         ;
ConditionVar             
                         :   <Oper,And>                  DefVar                      { TREE(RefDef); }           { NODE(RefDef,(1,2)); }  
                         |   DefVar                   
                         ;
Condition                
                         :   DefType                     { MAKE(Define,1); }         ConditionVar                { MAKE(PushDef); }          { NODE(Define,(0,1,2)); }
                         |   ExpressionCondition      
                         ;
ForPrefix                
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { NODE(Null,(1)); }      
                         |   DefineSemi               
                         |   ExprSemi                 
                         ;
ForCondition             
                         :   <Separator,Semicolon>       { MAKE(NodeNull); }         { NODE(Null,(1)); }      
                         |   Condition                   <Separator,Semicolon>    
                         ;
ForPostfix               
                         :   <Separator,RightBracket>    { TREE(NodeNull); }         { NODE(Null,(1)); }      
                         |   ExpressionExpression        <Separator,RightBracket> 
                         ;
ForStmnt                 
                         :   <Reserv,For>                <Separator,LeftBracket>     { MAKE(BegFor); }           ForPrefix                   { CODE(PrefFor); }          ForCondition                { CODE(ConditionFor); }     ForPostfix                  { CODE(PostFor); }          DefExpr                     { MAKE(For); }              { NODE(For,(1,3,4,5,6)); }                        
                         ;
DoStmnt                  
                         :   <Reserv,Do>                 { MAKE(BegDo); }            DefExpr                     <Reserv,While>              <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    <Separator,Semicolon>       { MAKE(Do); }               { NODE(Do,(1,5,2)); }    
                         ;
WhileStmnt               
                         :   <Reserv,While>              { MAKE(BegWhile); }         <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    DefExpr                     { MAKE(While); }            { NODE(While,(1,3,5)); } 
                         ;
GoToStmnt                
                         :   <Reserv,GoTo>               <Ident>                     <Separator,Semicolon>       { NODE(GoTo,(2)); }         { MAKE(GoTo); }          
                         ;
BreakStmnt               
                         :   <Reserv,Break>              <Separator,Semicolon>       { MAKE(Break); }            { NODE(Break,(1)); }     
                         ;
ContinueStmnt            
                         :   <Reserv,Continue>           <Separator,Semicolon>       { MAKE(Continue); }         { NODE(Continue,(1)); }  
                         ;
ReturnValue              
                         :   <Separator,Semicolon>       { MAKE(Return); }           { NODE(Return,(1)); }    
                         |   ExpressionValue             <Separator,Semicolon>       { MAKE(Return,1); }         { NODE(Return,(1,1)); }  
                         ;
ReturnStmnt              
                         :   <Reserv,Return>             ReturnValue                 { NODE(Return,(1,2),1); }
                         ;
BegIfStmnt               
                         :   <Reserv,If>                 <Separator,LeftBracket>     { CODE(BegIf); }            Condition                   <Separator,RightBracket>    { CODE(Then); }             DefExpr                     { NODE(If,(1,3,5)); }    
                         ;
LabelIdent               
                         :   <Ident>                     <Separator,Colon>           { CODE(Label); }            { NODE(Label,(1)); }     
                         ;
LabelList                
                         :   LabelIdent                  { NODE(List,(0,1)); }    
                         ;
Statement                
                         :   BegIfStmnt                  <Reserv,Else>               { CODE(Else); }             DefExpr                     { MAKE(If,1); }             { NODE(If,(2,1,3),1); }  
                         |   BegIfStmnt                  { MAKE(If); }            
                         |   LabelList                   DefExpr                     { YACC(AddToList,3); }      { TREE(Label); }         
                         |   DoStmnt                  
                         |   WhileStmnt               
                         |   ForStmnt                 
                         |   GoToStmnt                
                         |   BreakStmnt               
                         |   ContinueStmnt            
                         |   ReturnStmnt              
                         |   CompaundStmnt            
                         ;
DefineSemi               
                         :   Define                      <Separator,Semicolon>    
                         ;
ExprSemi                 
                         :   ExpressionExpression        <Separator,Semicolon>    
                         ;
DefExpr                  
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { NODE(Null,(1)); }      
                         |   DefineSemi               
                         |   Statement                
                         |   ExprSemi                 
                         ;
StmExprList              
                         :   StmExprList                 DefExpr                     { TREE(AddToList); }        { YACC(AddToList,3); }   
                         |   DefExpr                     { TREE(AddToList); }        { NODE(Statements,(0,1)); }                       
                         ;
StmExpr                  
                         :   StmExprList                 { CODE(EndBlock); }      
                         ;
DefFAV                   
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { NODE(Null,(1)); }      
                         |   DefFuncDefine            
                         ;
DefinesList              
                         :   DefinesList                 DefFAV                      { TREE(AddToList); }        { YACC(AddToList,3); }   
                         |   DefFAV                      { TREE(BegStmExprLR,1); }   { NODE(Statements,(0,1)); }                       
                         ;
Defines                  
                         :   { CODE(BegStmExprLR); }     DefinesList                 { CODE(EndBlock); }      
                         ;
ExpressionExpression     
                         :   Expressions                 { ALL(ExpressionSLR,16); }                        
                         ;
ExpressionCondition      
                         :   Expressions                 { ALL(ExpressionSLR,241); }                       
                         ;
ExpressionNone           
                         :   Expressions                 { ALL(ExpressionSLR); }  
                         ;
ExpressionValue          
                         :   Expressions                 { ALL(ExpressionSLR,256); }                       
                         ;
ExpressionValueList      
                         :   Expressions                 { ALL(ExpressionSLR,512); }                       
                         ;
