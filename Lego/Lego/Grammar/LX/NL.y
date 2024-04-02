
S_                       
                         :   Program                  
                         ;
Program                  
                         :   Defines                  
                         ;
DefineParType            
                         :   <Reserv,Const>              <Reserv,Define>             <Oper,And>                  { MAKE(DefType,11); }    
                         |   <Reserv,Define>             <Oper,And>                  { MAKE(DefType,9); }     
                         |   <Reserv,Const>              <Reserv,Define>             { MAKE(DefType,3); }     
                         |   <Reserv,Define>             { MAKE(DefType,1); }     
                         ;
DefParType               
                         :   DefineParType               <Ident>                  
                         ;
DefPar                   
                         :   <Oper,Assign>               Assign                      { MAKE(ParVarAssign); }  
                         |   
                         ;
DefParItem               
                         :   DefParType                  <Separator,LeftScrape>      { MAKE(DefParArr); }        DefArrDA                    DefPar                   
                         |   DefParType                  { MAKE(DefParVar); }        DefPar                   
                         ;
DefParamsList            
                         :   <Separator,Comma>           DefParItem                  { TREE(AddToList); }        DefParamsList            
                         |   
                         ;
DefParams                
                         :   { TREE(Define,2); }         DefParItem                  { TREE(AddToList); }        DefParamsList               { TREE(EndParams); }     
                         ;
BodyFunc                 
                         :   <Separator,Semicolon>       { MAKE(BodyFunc); }      
                         |   <Separator,LeftCramp>       <Separator,RightCramp>      { MAKE(BodyFunc,1); }    
                         |   <Separator,LeftCramp>       { MAKE(BegStmExprLL); }     StmExpr                     <Separator,RightCramp>      { MAKE(BodyFunc,2); }    
                         ;
DefFuncType              
                         :   <Reserv,Static>             <Reserv,Const>              <Reserv,Define>             { MAKE(DefType,7); }     
                         |   <Reserv,Static>             <Reserv,Define>             { MAKE(DefType,5); }     
                         |   <Reserv,Const>              <Reserv,Define>             { MAKE(DefType,3); }     
                         |   <Reserv,Define>             { MAKE(DefType,1); }     
                         |   <Reserv,Static>             <Reserv,Void>               { MAKE(DefType,36); }    
                         |   <Reserv,Void>               { MAKE(DefType,32); }    
                         ;
DefFuncParams            
                         :   <Separator,RightBracket>    { TREE(EndParams,2); }   
                         |   DefParams                   <Separator,RightBracket> 
                         ;
DefFunc                  
                         :   DefFuncType                 <Ident>                     <Separator,LeftBracket>     { MAKE(FuncIdent); }        DefFuncParams               BodyFunc                 
                         ;
AInitialList             
                         :   <Separator,Comma>           AInitItem                   { TREE(AddToList); }        AInitialList             
                         |   
                         ;
AInitial                 
                         :   AInitItem                   { TREE(AddToList); }        AInitialList             
                         ;
Initializer              
                         :   <Separator,LeftCramp>       <Separator,RightCramp>      { TREE(NodeListLL); }    
                         |   <Separator,LeftCramp>       { TREE(NodeListLL); }       AInitial                    <Separator,RightCramp>   
                         ;
AInitItem                
                         :   Initializer              
                         |   Assign                   
                         ;
DefAInit                 
                         :   <Oper,Assign>               Initializer                 { MAKE(EndAInit); }      
                         |   
                         ;
DRanges                  
                         :   <Separator,LeftScrape>      Assign                      <Separator,RightScrape>     { MAKE(DRange); }           DRanges                  
                         |   
                         ;
DefArrD1A                
                         :   <Separator,RightScrape>     { MAKE(DefArrD1AEmpty); }
                         |   Assign                      <Separator,RightScrape>     { MAKE(DRange); }        
                         ;
DefArrDA                 
                         :   DefArrD1A                   DRanges                  
                         ;
DefArr                   
                         :   <Ident>                     <Separator,LeftScrape>      { MAKE(DefArray); }         DefArrDA                    DefAInit                 
                         ;
DefVarInit               
                         :   <Oper,Assign>               Assign                      { MAKE(DefVarAssign); }  
                         |   
                         ;
DefVar                   
                         :   <Ident>                     { MAKE(DefIdent); }         DefVarInit               
                         ;
DefItem                  
                         :   <Oper,And>                  DefArr                      { TREE(RefDef); }        
                         |   <Oper,And>                  DefVar                      { TREE(RefDef); }        
                         |   DefArr                   
                         |   DefVar                   
                         ;
DefType                  
                         :   <Reserv,Static>             <Reserv,Const>              <Reserv,Define>             { MAKE(DefType,7); }        { MAKE(Define,1); }      
                         |   <Reserv,Static>             <Reserv,Define>             { MAKE(DefType,5); }        { MAKE(Define,1); }      
                         |   <Reserv,Const>              <Reserv,Define>             { MAKE(DefType,3); }        { MAKE(Define,1); }      
                         |   <Reserv,Define>             { MAKE(DefType,1); }        { MAKE(Define,1); }      
                         ;
DefineList               
                         :   <Separator,Comma>           DefItem                     { TREE(AddToList); }        DefineList               
                         |   
                         ;
Define                   
                         :   DefType                     DefItem                     { TREE(AddToList); }        DefineList               
                         ;
ConditionVar             
                         :   <Oper,And>                  DefVar                      { TREE(RefDef); }        
                         |   DefVar                   
                         ;
Condition                
                         :   DefType                     ConditionVar                { MAKE(PushDef); }       
                         |   ExpressionCondition      
                         ;
ExpressionsList          
                         :   <Separator,Comma>           Assign                      { TREE(AddToList); }        ExpressionsList          
                         |   
                         ;
Expressions              
                         :   Assign                      { MAKE(ExpressionsLL); }    ExpressionsList          
                         ;
AssignList               
                         :   <Priority,Assign>           Assign                      { MAKE(Binary); }        
                         |   
                         ;
Assign                   
                         :   Question                    AssignList               
                         ;
QuestionList             
                         :   <Priority,Question>         ExpressionValue             <Separator,Colon>           Question                    { MAKE(Question); }      
                         |   
                         ;
Question                 
                         :   OrOr                        QuestionList             
                         ;
OrOr                     
                         :   AndAnd                      { NODE(None,(1,2)); }       OrOr_                    
                         ;
OrOr_                    
                         :   <Priority,OrOr>             AndAnd                      { MAKE(Binary); }           { NODE(Binary,(3,1,2)); }   OrOr_                    
                         |   
                         ;
AndAnd                   
                         :   Or                          { NODE(None,(1,2)); }       AndAnd_                  
                         ;
AndAnd_                  
                         :   <Priority,AndAnd>           Or                          { MAKE(Binary); }           { NODE(Binary,(3,1,2)); }   AndAnd_                  
                         |   
                         ;
Or                       
                         :   XOr                         { NODE(None,(1,2)); }       Or_                      
                         ;
Or_                      
                         :   <Priority,Or>               XOr                         { MAKE(Binary); }           { NODE(Binary,(3,1,2)); }   Or_                      
                         |   
                         ;
XOr                      
                         :   And                         { NODE(None,(1,2)); }       XOr_                     
                         ;
XOr_                     
                         :   <Priority,XOr>              And                         { MAKE(Binary); }           { NODE(Binary,(3,1,2)); }   XOr_                     
                         |   
                         ;
And                      
                         :   Equ                         { NODE(None,(1,2)); }       And_                     
                         ;
And_                     
                         :   <Priority,And>              Equ                         { MAKE(Binary); }           { NODE(Binary,(3,1,2)); }   And_                     
                         |   
                         ;
Equ                      
                         :   Compare                     { NODE(None,(1,2)); }       Equ_                     
                         ;
Equ_                     
                         :   <Priority,Equ>              Compare                     { MAKE(Binary); }           { NODE(Binary,(3,1,2)); }   Equ_                     
                         |   
                         ;
Compare                  
                         :   Shift                       { NODE(None,(1,2)); }       Compare_                 
                         ;
Compare_                 
                         :   <Priority,Compare>          Shift                       { MAKE(Binary); }           { NODE(Binary,(3,1,2)); }   Compare_                 
                         |   
                         ;
Shift                    
                         :   Term                        { NODE(None,(1,2)); }       Shift_                   
                         ;
Shift_                   
                         :   <Priority,Shift>            Term                        { MAKE(Binary); }           { NODE(Binary,(3,1,2)); }   Shift_                   
                         |   
                         ;
Term                     
                         :   Factor                      { NODE(None,(1,2)); }       Term_                    
                         ;
Term_                    
                         :   <Priority,Term>             Factor                      { MAKE(Binary); }           { NODE(Binary,(3,1,2)); }   Term_                    
                         |   
                         ;
Factor                   
                         :   Unary                       { NODE(None,(1,2)); }       Factor_                  
                         ;
Factor_                  
                         :   <Priority,Factor>           Unary                       { MAKE(Binary); }           { NODE(Binary,(3,1,2)); }   Factor_                  
                         |   
                         ;
UnaryIncDec              
                         :   <Priority,IncDec>           { MAKE(IncDec); }           UnaryIncDec              
                         |   
                         ;
DefineCast               
                         :   <Reserv,Const>              <Reserv,Define>             { MAKE(DefType,3); }     
                         |   <Reserv,Define>             { MAKE(DefType,1); }     
                         ;
Unary                    
                         :   <Priority,Unary>            Unary                       { MAKE(Unary); }         
                         |   <Priority,Term>             Unary                       { MAKE(Unary); }         
                         |   <Priority,IncDec>           Unary                       { MAKE(Unary); }         
                         |   <Separator,LeftBracket>     DefineCast                  <Separator,RightBracket>    Unary                       { MAKE(Cast); }          
                         |   PrimaryExpr                 UnaryIncDec              
                         ;
Primary                  
                         :   <Separator,LeftBracket>     ExpressionNone              <Separator,RightBracket>    { TREE(Primary); }       
                         ;
PrimaryExpr              
                         :   <Ident>                     <Separator,LeftScrape>      Ranges                   
                         |   <Ident>                     <Separator,LeftBracket>     CallParams               
                         |   <Integer>                   { MAKE(Number); }        
                         |   <Number>                    { MAKE(Number); }        
                         |   <Ident>                     { MAKE(Ident); }         
                         |   Primary                  
                         |   <Reserv,Define>             Primary                     { MAKE(Cast); }          
                         ;
Range                    
                         :   <Separator,LeftScrape>      ExpressionValue             <Separator,RightScrape>     { MAKE(IndexLL); }          Range                    
                         |   
                         ;
Ranges                   
                         :   { MAKE(BegIndexLL); }       ExpressionValue             <Separator,RightScrape>     { MAKE(IndexLL); }          Range                       { MAKE(EndIndex); }      
                         ;
CallParams               
                         :   <Separator,RightBracket>    { MAKE(Params); }        
                         |   ExpressionValueList         <Separator,RightBracket>    { MAKE(Params,1); }      
                         ;
CompaundStmnt            
                         :   <Separator,LeftCramp>       <Separator,RightCramp>      { MAKE(Compaund); }      
                         |   <Separator,LeftCramp>       { MAKE(Compaund); }         StmExpr                     <Separator,RightCramp>   
                         ;
IfStmntElse              
                         :   <Reserv,Else>               DefExpr                     { MAKE(If,1); }          
                         |   { MAKE(If); }            
                         ;
IfStmnt                  
                         :   <Reserv,If>                 <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    DefExpr                     IfStmntElse              
                         ;
ForPrefix                
                         :   <Separator,Semicolon>       { TREE(NodeNull); }      
                         |   DefineSemi               
                         |   ExprSemi                 
                         ;
ForCondition             
                         :   <Separator,Semicolon>       { MAKE(NodeNull); }      
                         |   Condition                   <Separator,Semicolon>    
                         ;
ForPostfix               
                         :   <Separator,RightBracket>    { TREE(NodeNull); }      
                         |   ExpressionExpression        <Separator,RightBracket> 
                         ;
ForStmnt                 
                         :   <Reserv,For>                <Separator,LeftBracket>     { MAKE(BegFor); }           ForPrefix                   ForCondition                ForPostfix                  DefExpr                     { MAKE(For); }           
                         ;
DoStmnt                  
                         :   <Reserv,Do>                 { MAKE(BegDo); }            DefExpr                     <Reserv,While>              <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    <Separator,Semicolon>       { MAKE(Do); }            
                         ;
WhileStmnt               
                         :   <Reserv,While>              { MAKE(BegWhile); }         <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    DefExpr                     { MAKE(While); }         
                         ;
SwitchStmnt              
                         :   <Reserv,Switch>             <Separator,LeftBracket>     <Separator,RightBracket> 
                         ;
GoToStmnt                
                         :   <Reserv,GoTo>               <Ident>                     <Separator,Semicolon>       { MAKE(GoTo); }          
                         ;
BreakStmnt               
                         :   <Reserv,Break>              <Separator,Semicolon>       { MAKE(Break); }         
                         ;
ContinueStmnt            
                         :   <Reserv,Continue>           <Separator,Semicolon>       { MAKE(Continue); }      
                         ;
ReturnValue              
                         :   ExpressionValue             { MAKE(Return,1); }      
                         |   { MAKE(Return); }        
                         ;
ReturnStmnt              
                         :   <Reserv,Return>             ReturnValue                 <Separator,Semicolon>    
                         ;
Statement                
                         :   IfStmnt                  
                         |   DoStmnt                  
                         |   WhileStmnt               
                         |   ForStmnt                 
                         |   SwitchStmnt              
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
                         :   <Separator,Semicolon>       { TREE(NodeNull); }      
                         |   <Ident>                     <Separator,Colon>           DefExpr                     { TREE(Label); }         
                         |   DefineSemi               
                         |   Statement                
                         |   ExprSemi                 
                         ;
StmExpr                  
                         :   DefExpr                     { TREE(AddToList); }        StmExpr                  
                         |   
                         ;
DefFAV                   
                         :   <Separator,Semicolon>       { TREE(NodeNull); }      
                         |   DefFunc                  
                         |   DefineSemi               
                         ;
DefinesBeg               
                         :   DefFAV                      { TREE(AddToList); }        DefinesBeg               
                         |   
                         ;
Defines                  
                         :   { MAKE(BegStmExprLL); }     DefinesBeg               
                         ;
ExpressionExpression     
                         :   Expressions                 { TREE(ExpressionSLL,16); }                       
                         ;
ExpressionCondition      
                         :   Expressions                 { TREE(ExpressionSLL,241); }                      
                         ;
ExpressionNone           
                         :   Expressions                 { TREE(ExpressionSLL); } 
                         ;
ExpressionValue          
                         :   Expressions                 { TREE(ExpressionSLL,256); }                      
                         ;
ExpressionValueList      
                         :   Expressions                 { TREE(ExpressionSLL,512); }                      
                         ;
