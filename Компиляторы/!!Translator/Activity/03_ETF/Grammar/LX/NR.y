
S_                       
                         :   Program                  
                         ;
Program                  
                         :   Defines                  
                         ;
DefParType               
                         :   <Reserv,Const>              <Syntax,DefType>            <Oper,And>               
                         |   <Syntax,DefType>            <Oper,And>               
                         |   <Reserv,Const>              <Syntax,DefType>         
                         |   <Syntax,DefType>         
                         ;
DefBegParVar             
                         :   DefParType                  <Ident>                  
                         ;
DefParVar                
                         :   DefBegParVar                <Oper,Assign>               Assign                   
                         |   DefBegParVar             
                         ;
DefBegParArr             
                         :   DefParType                  <Ident>                     DefBegRanges             
                         ;
DefParArr                
                         :   DefBegParArr                <Oper,Assign>               Assign                   
                         |   DefBegParArr             
                         ;
DefParItem               
                         :   DefParArr                
                         |   DefParVar                
                         ;
DefParams                
                         :   DefParams                   <Separator,Comma>           DefParItem               
                         |   DefParItem               
                         ;
BodyFunc                 
                         :   <Separator,Semicolon>    
                         |   <Separator,LeftCramp>       <Separator,RightCramp>   
                         |   <Separator,LeftCramp>       StmExpr                     <Separator,RightCramp>   
                         ;
DefFuncParBody           
                         :   <Separator,RightBracket> 
                         |   DefParams                   <Separator,RightBracket> 
                         ;
DefParBodyFunc           
                         :   DefFuncParBody              BodyFunc                 
                         ;
DefVoidType              
                         :   <Reserv,Static>             <Reserv,Void>            
                         |   <Reserv,Void>            
                         ;
DefType                  
                         :   <Reserv,Static>             <Reserv,Const>              <Syntax,DefType>         
                         |   <Reserv,Static>             <Syntax,DefType>         
                         |   <Reserv,Const>              <Syntax,DefType>         
                         |   <Syntax,DefType>         
                         ;
CommaDefItem             
                         :   CommaDefItem                <Separator,Comma>           DefItem                  
                         |   DefItem                  
                         ;
Define                   
                         :   DefType                     CommaDefItem             
                         ;
DefineBegRanges          
                         :   <Separator,RightScrape>     DefRanges                
                         |   <Separator,RightScrape>  
                         |   Assign                      <Separator,RightScrape>     DefRanges                
                         |   Assign                      <Separator,RightScrape>  
                         ;
DefineBegArr             
                         :   DefineBegRanges          
                         ;
DefineArr                
                         :   IdentLeftScrape             <Oper,Assign>               Initializer              
                         |   IdentLeftScrape          
                         ;
IdentLeftScrape          
                         :   <Ident>                     <Separator,LeftScrape>      DefineBegArr             
                         ;
DefineVarAssign          
                         :   <Separator,Comma>           CommaDefItem                <Separator,Semicolon>    
                         |   <Separator,Semicolon>    
                         ;
DefVariableAssign        
                         :   <Ident>                     <Oper,Assign>               Assign                   
                         ;
DefVarComma              
                         :   <Ident>                  
                         ;
DefVarSemicolon          
                         :   <Ident>                  
                         ;
DefFuncArrVar            
                         :   DefType                     <Ident>                     <Separator,LeftBracket>     DefParBodyFunc           
                         |   DefType                     DefineArr                   <Separator,Comma>           CommaDefItem                <Separator,Semicolon>    
                         |   DefType                     DefineArr                   <Separator,Semicolon>    
                         |   DefType                     DefVariableAssign           DefineVarAssign          
                         |   DefType                     DefVarComma                 <Separator,Comma>           CommaDefItem                <Separator,Semicolon>    
                         |   DefType                     DefVarSemicolon             <Separator,Semicolon>    
                         ;
DefFuncDefine            
                         :   DefVoidType                 <Ident>                     <Separator,LeftBracket>     DefParBodyFunc           
                         |   DefFuncArrVar            
                         ;
AInitItem                
                         :   Initializer              
                         |   Assign                   
                         ;
AInitial                 
                         :   AInitial                    <Separator,Comma>           AInitItem                
                         |   AInitItem                
                         ;
Initializer              
                         :   <Separator,LeftCramp>       <Separator,RightCramp>   
                         |   <Separator,LeftCramp>       AInitial                    <Separator,RightCramp>   
                         ;
DefRange                 
                         :   <Separator,LeftScrape>      Assign                      <Separator,RightScrape>  
                         ;
DefRanges                
                         :   DefRanges                   DefRange                 
                         |   DefRange                 
                         ;
DefBegRanges             
                         :   <Separator,LeftScrape>      <Separator,RightScrape>     DefRanges                
                         |   <Separator,LeftScrape>      <Separator,RightScrape>  
                         |   DefRanges                
                         ;
DefBegArr                
                         :   <Ident>                     DefBegRanges             
                         ;
DefArr                   
                         :   DefBegArr                   <Oper,Assign>               Initializer              
                         |   DefBegArr                
                         ;
DefVarIdent              
                         :   <Ident>                  
                         ;
DefVarAssign             
                         :   <Oper,Assign>               Assign                   
                         ;
DefVar                   
                         :   DefVarIdent                 DefVarAssign             
                         |   DefVarIdent              
                         ;
DefIAV                   
                         :   DefArr                   
                         |   DefVar                   
                         ;
RefDefIAV                
                         :   <Oper,And>                  DefIAV                   
                         ;
DefItem                  
                         :   RefDefIAV                
                         |   DefIAV                   
                         ;
Expressions              
                         :   Expressions                 <Separator,Comma>           Assign                   
                         |   Assign                   
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
                         :   Question                    PriorAssign                 Assign                   
                         |   Question                 
                         ;
Question                 
                         :   OrOr                        PriorQuestion               ExpressionValue             <Separator,Colon>           Question                 
                         |   OrOr                     
                         ;
OrOr                     
                         :   OrOr                        PriorOrOr                   AndAnd                   
                         |   AndAnd                   
                         ;
AndAnd                   
                         :   AndAnd                      PriorAndAnd                 Or                       
                         |   Or                       
                         ;
Or                       
                         :   Or                          PriorOr                     XOr                      
                         |   XOr                      
                         ;
XOr                      
                         :   XOr                         PriorXOr                    And                      
                         |   And                      
                         ;
And                      
                         :   And                         PriorAnd                    Equ                      
                         |   Equ                      
                         ;
Equ                      
                         :   Equ                         PriorEqu                    Compare                  
                         |   Compare                  
                         ;
Compare                  
                         :   Compare                     PriorCompare                Shift                    
                         |   Shift                    
                         ;
Shift                    
                         :   Shift                       PriorShift                  Term                     
                         |   Term                     
                         ;
Term                     
                         :   Term                        PriorTerm                   Factor                   
                         |   Factor                   
                         ;
Factor                   
                         :   Factor                      PriorFactor                 Unary                    
                         |   Unary                    
                         ;
UnaryIncDec              
                         :   PrimaryExpr                 PriorIncDec              
                         |   PrimaryExpr              
                         ;
DefTypeCast              
                         :   <Reserv,Const>              <Syntax,DefType>         
                         |   <Syntax,DefType>         
                         ;
Unary                    
                         :   PriorUnary                  Unary                    
                         |   PriorTerm                   Unary                    
                         |   PriorIncDec                 Unary                    
                         |   <Separator,LeftBracket>     DefTypeCast                 <Separator,RightBracket>    Unary                    
                         |   UnaryIncDec              
                         ;
Primary                  
                         :   <Separator,LeftBracket>     ExpressionNone              <Separator,RightBracket> 
                         ;
PrimaryExpr              
                         :   <Integer>                
                         |   <Number>                 
                         |   <Ident>                     Ranges                   
                         |   <Ident>                     CallParams               
                         |   <Syntax,DefType>            Primary                  
                         |   <Ident>                  
                         |   Primary                  
                         ;
Range                    
                         :   <Separator,LeftScrape>      ExpressionValue             <Separator,RightScrape>  
                         ;
Ranges                   
                         :   Ranges                      Range                    
                         |   Range                    
                         ;
CallParams               
                         :   <Separator,LeftBracket>     <Separator,RightBracket> 
                         |   <Separator,LeftBracket>     ExpressionValueList         <Separator,RightBracket> 
                         ;
CompaundStmnt            
                         :   <Separator,LeftCramp>       <Separator,RightCramp>   
                         |   <Separator,LeftCramp>       StmExpr                     <Separator,RightCramp>   
                         ;
ConditionVar             
                         :   <Oper,And>                  DefVar                   
                         |   DefVar                   
                         ;
Condition                
                         :   DefType                     ConditionVar             
                         |   ExpressionCondition      
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
                         :   <Separator,Semicolon>    
                         |   ExpressionValue             <Separator,Semicolon>    
                         ;
ReturnStmnt              
                         :   <Reserv,Return>             ReturnValue              
                         ;
BegIfStmnt               
                         :   <Reserv,If>                 <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    DefExpr                  
                         ;
LabelIdent               
                         :   <Ident>                     <Separator,Colon>        
                         ;
LabelList                
                         :   LabelIdent               
                         ;
Statement                
                         :   BegIfStmnt                  <Reserv,Else>               DefExpr                  
                         |   BegIfStmnt               
                         |   LabelList                   DefExpr                  
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
                         :   <Separator,Semicolon>    
                         |   DefineSemi               
                         |   Statement                
                         |   ExprSemi                 
                         ;
StmExprList              
                         :   StmExprList                 DefExpr                  
                         |   DefExpr                  
                         ;
StmExpr                  
                         :   StmExprList              
                         ;
DefFAV                   
                         :   <Separator,Semicolon>    
                         |   DefFuncDefine            
                         ;
DefinesList              
                         :   DefinesList                 DefFAV                   
                         |   DefFAV                   
                         ;
Defines                  
                         :   DefinesList              
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
