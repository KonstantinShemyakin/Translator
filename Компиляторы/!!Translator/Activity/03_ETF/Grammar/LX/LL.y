
S_                       
                         :   Program                  
                         ;
Program                  
                         :   Defines                  
                         ;
DefParInit               
                         :   <Oper,Assign>               Assign                   
                         |   
                         ;
DefParVar                
                         :   <Syntax,DefVar>             <Ident>                     DefParInit               
                         ;
DefParArr                
                         :   <Syntax,DefArr>             <Syntax,IdentArr>           DefArrDA                    DefParInit               
                         ;
DefPar                   
                         :   DefParArr                
                         |   DefParVar                
                         ;
DefParItem               
                         :   DefPar                   
                         ;
DefParList               
                         :   <Separator,Comma>           DefParItem                  DefParList               
                         |   
                         ;
DefParams                
                         :   DefParItem                  DefParList               
                         ;
BodyFunc                 
                         :   <Separator,Semicolon>    
                         |   <Syntax,EmptyCramp>      
                         |   <Separator,LeftCramp>       StmExpr                     <Separator,RightCramp>   
                         ;
DefFunc_                 
                         :   <Syntax,EmptyBracket>    
                         |   <Separator,LeftBracket>     DefParams                   <Separator,RightBracket> 
                         ;
DefFunc                  
                         :   <Syntax,DefFunc>            <Syntax,IdentFunc>          DefFunc_                    BodyFunc                 
                         ;
AInitialList             
                         :   <Separator,Comma>           AInitItem                   AInitialList             
                         |   
                         ;
AInitial                 
                         :   AInitItem                   AInitialList             
                         ;
Initializer              
                         :   <Syntax,EmptyCramp>      
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
                         :   <Syntax,EmptyScrape>     
                         |   <Separator,LeftScrape>      Assign                      <Separator,RightScrape>  
                         ;
DefArrDA                 
                         :   DefArrD1A                   DRanges                  
                         ;
DefArr                   
                         :   <Syntax,IdentArr>           DefArrDA                    DefAInit                 
                         ;
DefVarAssign             
                         :   <Oper,Assign>               Assign                   
                         ;
DefVarInit               
                         :   DefVarAssign             
                         |   
                         ;
DefVar                   
                         :   <Ident>                     DefVarInit               
                         ;
DefIAV                   
                         :   DefArr                   
                         |   DefVar                   
                         ;
DefItem                  
                         :   <Priority,And>              DefIAV                   
                         |   DefIAV                   
                         ;
DefType                  
                         :   <Syntax,DefArr>          
                         |   <Syntax,DefVar>          
                         ;
DefineList               
                         :   <Separator,Comma>           DefItem                     DefineList               
                         |   
                         ;
Define                   
                         :   DefType                     DefItem                     DefineList               
                         ;
ConditionDef             
                         :   <Priority,And>              DefVar                   
                         |   DefVar                   
                         ;
Condition                
                         :   <Syntax,DefVar>             ConditionDef             
                         |   ExpressionCondition      
                         ;
ExprList                 
                         :   <Separator,Comma>           Assign                      ExprList                 
                         |   
                         ;
Expressions              
                         :   Assign                      ExprList                 
                         ;
PriorAssign              
                         :   <Priority,Assign>        
                         ;
AssignList               
                         :   PriorAssign                 Assign                   
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
                         :   <Priority,IncDec>        
                         |   
                         ;
Unary                    
                         :   <Priority,Unary>            Unary                    
                         |   <Priority,Term>             Unary                    
                         |   <Priority,IncDec>           Unary                    
                         |   <Syntax,CastUnary>          Unary                    
                         |   PrimaryExpr                 UnaryIncDec              
                         ;
Primary                  
                         :   <Separator,LeftBracket>     ExpressionNone              <Separator,RightBracket> 
                         ;
PrimaryExpr              
                         :   <Integer>                
                         |   <Number>                 
                         |   <Syntax,IdentArr>           Ranges                   
                         |   <Syntax,IdentFunc>          CallParams               
                         |   <Syntax,Cast>               Primary                  
                         |   <Ident>                  
                         |   Primary                  
                         ;
RangesList               
                         :   <Separator,LeftScrape>      ExpressionValue             <Separator,RightScrape>     RangesList               
                         |   
                         ;
Ranges                   
                         :   RangesList               
                         ;
CallParams               
                         :   <Syntax,EmptyBracket>    
                         |   <Separator,LeftBracket>     ExpressionValueList         <Separator,RightBracket> 
                         ;
CompaundStmnt            
                         :   <Syntax,EmptyCramp>      
                         |   <Separator,LeftCramp>       StmExpr                     <Separator,RightCramp>   
                         ;
IfStmnt_                 
                         :   <Reserv,Else>               DefExpr                  
                         |   
                         ;
IfStmnt                  
                         :   <Reserv,If>                 <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    DefExpr                     IfStmnt_                 
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
ForPosfix                
                         :   <Separator,RightBracket> 
                         |   ExpressionExpression        <Separator,RightBracket> 
                         ;
ForStmnt                 
                         :   <Reserv,For>                <Separator,LeftBracket>     ForPrefix                   ForCondition                ForPosfix                   DefExpr                  
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
ReturnVal                
                         :   ExpressionValue          
                         |   
                         ;
ReturnStmnt              
                         :   <Reserv,Return>             ReturnVal                   <Separator,Semicolon>    
                         ;
Statement                
                         :   <Syntax,Label>              <Separator,Colon>           DefExpr                  
                         |   IfStmnt                  
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
                         :   DefExpr                     StmExprList              
                         |   
                         ;
StmExpr                  
                         :   StmExprList              
                         ;
DefFAV                   
                         :   <Separator,Semicolon>    
                         |   DefFunc                  
                         |   DefineSemi               
                         ;
DefinesList              
                         :   DefFAV                      DefinesList              
                         |   
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
