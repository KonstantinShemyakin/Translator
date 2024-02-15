
S_                       
                         :   Program                  
                         ;
Program                  
                         :   Defines                  
                         ;
DefineParType            
                         :   <Reserv,Const>              <Reserv,Define>             <Oper,And>               
                         |   <Reserv,Define>             <Oper,And>               
                         |   <Reserv,Const>              <Reserv,Define>          
                         |   <Reserv,Define>          
                         ;
DefParType               
                         :   DefineParType               <Ident>                  
                         ;
DefPar                   
                         :   <Oper,Assign>               Assign                   
                         |   
                         ;
DefParItem               
                         :   DefParType                  <Separator,LeftScrape>      DefArrDA                    DefPar                   
                         |   DefParType                  DefPar                   
                         ;
DefParamsList            
                         :   <Separator,Comma>           DefParItem                  DefParamsList            
                         |   
                         ;
DefParams                
                         :   DefParItem                  DefParamsList            
                         ;
BodyFunc                 
                         :   <Separator,Semicolon>    
                         |   <Separator,LeftCramp>       <Separator,RightCramp>   
                         |   <Separator,LeftCramp>       StmExpr                     <Separator,RightCramp>   
                         ;
DefFuncType              
                         :   <Reserv,Static>             <Reserv,Const>              <Reserv,Define>          
                         |   <Reserv,Static>             <Reserv,Define>          
                         |   <Reserv,Const>              <Reserv,Define>          
                         |   <Reserv,Define>          
                         |   <Reserv,Static>             <Reserv,Void>            
                         |   <Reserv,Void>            
                         ;
DefFuncParams            
                         :   <Separator,RightBracket> 
                         |   DefParams                   <Separator,RightBracket> 
                         ;
DefFunc                  
                         :   DefFuncType                 <Ident>                     <Separator,LeftBracket>     DefFuncParams               BodyFunc                 
                         ;
AInitialList             
                         :   <Separator,Comma>           AInitItem                   AInitialList             
                         |   
                         ;
AInitial                 
                         :   AInitItem                   AInitialList             
                         ;
Initializer              
                         :   <Separator,LeftCramp>       <Separator,RightCramp>   
                         |   <Separator,LeftCramp>       AInitial                    <Separator,RightCramp>   
                         ;
AInitItem                
                         :   Initializer              
                         |   Assign                   
                         ;
DefAInit                 
                         :   <Oper,Assign>               Initializer              
                         |   
                         ;
DRanges                  
                         :   <Separator,LeftScrape>      Assign                      <Separator,RightScrape>     DRanges                  
                         |   
                         ;
DefArrD1A                
                         :   <Separator,RightScrape>  
                         |   Assign                      <Separator,RightScrape>  
                         ;
DefArrDA                 
                         :   DefArrD1A                   DRanges                  
                         ;
DefArr                   
                         :   <Ident>                     <Separator,LeftScrape>      DefArrDA                    DefAInit                 
                         ;
DefVarInit               
                         :   <Oper,Assign>               Assign                   
                         |   
                         ;
DefVar                   
                         :   <Ident>                     DefVarInit               
                         ;
DefItem                  
                         :   <Oper,And>                  DefArr                   
                         |   <Oper,And>                  DefVar                   
                         |   DefArr                   
                         |   DefVar                   
                         ;
DefType                  
                         :   <Reserv,Static>             <Reserv,Const>              <Reserv,Define>          
                         |   <Reserv,Static>             <Reserv,Define>          
                         |   <Reserv,Const>              <Reserv,Define>          
                         |   <Reserv,Define>          
                         ;
DefineList               
                         :   <Separator,Comma>           DefItem                     DefineList               
                         |   
                         ;
Define                   
                         :   DefType                     DefItem                     DefineList               
                         ;
ConditionVar             
                         :   <Oper,And>                  DefVar                   
                         |   DefVar                   
                         ;
Condition                
                         :   DefType                     ConditionVar             
                         |   ExpressionCondition      
                         ;
ExpressionsList          
                         :   <Separator,Comma>           Assign                      ExpressionsList          
                         |   
                         ;
Expressions              
                         :   Assign                      ExpressionsList          
                         ;
AssignList               
                         :   <Priority,Assign>           Assign                   
                         |   
                         ;
Assign                   
                         :   Question                    AssignList               
                         ;
QuestionList             
                         :   <Priority,Question>         ExpressionValue             <Separator,Colon>           Question                 
                         |   
                         ;
Question                 
                         :   OrOr                        QuestionList             
                         ;
OrOr                     
                         :   AndAnd                      OrOr_                    
                         ;
OrOr_                    
                         :   <Priority,OrOr>             AndAnd                      OrOr_                    
                         |   
                         ;
AndAnd                   
                         :   Or                          AndAnd_                  
                         ;
AndAnd_                  
                         :   <Priority,AndAnd>           Or                          AndAnd_                  
                         |   
                         ;
Or                       
                         :   XOr                         Or_                      
                         ;
Or_                      
                         :   <Priority,Or>               XOr                         Or_                      
                         |   
                         ;
XOr                      
                         :   And                         XOr_                     
                         ;
XOr_                     
                         :   <Priority,XOr>              And                         XOr_                     
                         |   
                         ;
And                      
                         :   Equ                         And_                     
                         ;
And_                     
                         :   <Priority,And>              Equ                         And_                     
                         |   
                         ;
Equ                      
                         :   Compare                     Equ_                     
                         ;
Equ_                     
                         :   <Priority,Equ>              Compare                     Equ_                     
                         |   
                         ;
Compare                  
                         :   Shift                       Compare_                 
                         ;
Compare_                 
                         :   <Priority,Compare>          Shift                       Compare_                 
                         |   
                         ;
Shift                    
                         :   Term                        Shift_                   
                         ;
Shift_                   
                         :   <Priority,Shift>            Term                        Shift_                   
                         |   
                         ;
Term                     
                         :   Factor                      Term_                    
                         ;
Term_                    
                         :   <Priority,Term>             Factor                      Term_                    
                         |   
                         ;
Factor                   
                         :   Unary                       Factor_                  
                         ;
Factor_                  
                         :   <Priority,Factor>           Unary                       Factor_                  
                         |   
                         ;
UnaryIncDec              
                         :   <Priority,IncDec>           UnaryIncDec              
                         |   
                         ;
DefineCast               
                         :   <Reserv,Const>              <Reserv,Define>          
                         |   <Reserv,Define>          
                         ;
Unary                    
                         :   <Priority,Unary>            Unary                    
                         |   <Priority,Term>             Unary                    
                         |   <Priority,IncDec>           Unary                    
                         |   <Separator,LeftBracket>     DefineCast                  <Separator,RightBracket>    Unary                    
                         |   PrimaryExpr                 UnaryIncDec              
                         ;
Primary                  
                         :   <Separator,LeftBracket>     ExpressionNone              <Separator,RightBracket> 
                         ;
PrimaryExpr              
                         :   <Ident>                     <Separator,LeftScrape>      Ranges                   
                         |   <Ident>                     <Separator,LeftBracket>     CallParams               
                         |   <Integer>                
                         |   <Number>                 
                         |   <Ident>                  
                         |   Primary                  
                         |   <Reserv,Define>             Primary                  
                         ;
Range                    
                         :   <Separator,LeftScrape>      ExpressionValue             <Separator,RightScrape>     Range                    
                         |   
                         ;
Ranges                   
                         :   ExpressionValue             <Separator,RightScrape>     Range                    
                         ;
CallParams               
                         :   <Separator,RightBracket> 
                         |   ExpressionValueList         <Separator,RightBracket> 
                         ;
CompaundStmnt            
                         :   <Separator,LeftCramp>       <Separator,RightCramp>   
                         |   <Separator,LeftCramp>       StmExpr                     <Separator,RightCramp>   
                         ;
IfStmntElse              
                         :   <Reserv,Else>               DefExpr                  
                         |   
                         ;
IfStmnt                  
                         :   <Reserv,If>                 <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    DefExpr                     IfStmntElse              
                         ;
ForPrefix                
                         :   <Separator,Semicolon>    
                         |   DefineSemi               
                         |   ExprSemi                 
                         ;
ForCondition             
                         :   <Separator,Semicolon>    
                         |   Condition                   <Separator,Semicolon>    
                         ;
ForPostfix               
                         :   <Separator,RightBracket> 
                         |   ExpressionExpression        <Separator,RightBracket> 
                         ;
ForStmnt                 
                         :   <Reserv,For>                <Separator,LeftBracket>     ForPrefix                   ForCondition                ForPostfix                  DefExpr                  
                         ;
DoStmnt                  
                         :   <Reserv,Do>                 DefExpr                     <Reserv,While>              <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    <Separator,Semicolon>    
                         ;
WhileStmnt               
                         :   <Reserv,While>              <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    DefExpr                  
                         ;
SwitchStmnt              
                         :   <Reserv,Switch>             <Separator,LeftBracket>     <Separator,RightBracket> 
                         ;
GoToStmnt                
                         :   <Reserv,GoTo>               <Ident>                     <Separator,Semicolon>    
                         ;
BreakStmnt               
                         :   <Reserv,Break>              <Separator,Semicolon>    
                         ;
ContinueStmnt            
                         :   <Reserv,Continue>           <Separator,Semicolon>    
                         ;
ReturnValue              
                         :   ExpressionValue          
                         |   
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
                         :   <Separator,Semicolon>    
                         |   <Ident>                     <Separator,Colon>           DefExpr                  
                         |   DefineSemi               
                         |   Statement                
                         |   ExprSemi                 
                         ;
StmExpr                  
                         :   DefExpr                     StmExpr                  
                         |   
                         ;
DefFAV                   
                         :   <Separator,Semicolon>    
                         |   DefFunc                  
                         |   DefineSemi               
                         ;
DefinesBeg               
                         :   DefFAV                      DefinesBeg               
                         |   
                         ;
Defines                  
                         :   DefinesBeg               
                         ;
ExpressionExpression     
                         :   Expressions              
                         ;
ExpressionCondition      
                         :   Expressions              
                         ;
ExpressionNone           
                         :   Expressions              
                         ;
ExpressionValue          
                         :   Expressions              
                         ;
ExpressionValueList      
                         :   Expressions              
                         ;
