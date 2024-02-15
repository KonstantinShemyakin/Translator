
S_                       
                         :   Program                  
                         ;
Program                  
                         :   Defines                  
                         ;
DefBegParVar             
                         :   <Ident>                  
                         ;
DefParVar                
                         :   DefBegParVar                <Oper,Assign>               Assign                   
                         |   DefBegParVar             
                         ;
DefBegParArr             
                         :   <Syntax,IdentArr>           DefBegRanges             
                         ;
DefParArr                
                         :   DefBegParArr                <Oper,Assign>               Assign                   
                         |   DefBegParArr             
                         ;
DefParItem               
                         :   <Syntax,DefArr>             DefParArr                
                         |   <Syntax,DefVar>             DefParVar                
                         ;
DefParams                
                         :   DefParams                   <Separator,Comma>           DefParItem               
                         |   DefParItem               
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
AInitItem                
                         :   Initializer              
                         |   Assign                   
                         ;
AInitial                 
                         :   AInitial                    <Separator,Comma>           AInitItem                
                         |   AInitItem                
                         ;
Initializer              
                         :   <Syntax,EmptyCramp>      
                         |   <Separator,LeftCramp>       AInitial                    <Separator,RightCramp>   
                         ;
DefRanges_               
                         :   <Separator,LeftScrape>      Assign                      <Separator,RightScrape>  
                         ;
DefRanges                
                         :   DefRanges                   DefRanges_               
                         |   DefRanges_               
                         ;
DefBegRanges             
                         :   <Syntax,EmptyScrape>        DefRanges                
                         |   <Syntax,EmptyScrape>     
                         |   DefRanges                
                         ;
DefBegArr                
                         :   <Syntax,IdentArr>           DefBegRanges             
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
                         :   <Priority,And>              DefIAV                   
                         ;
DefItem                  
                         :   RefDefIAV                
                         |   DefIAV                   
                         ;
DefType                  
                         :   <Syntax,DefArr>          
                         |   <Syntax,DefVar>          
                         ;
DefineComma              
                         :   DefineComma                 <Separator,Comma>           DefItem                  
                         |   DefItem                  
                         ;
Define                   
                         :   DefType                     DefineComma              
                         ;
Expressions              
                         :   Expressions                 <Separator,Comma>           Assign                   
                         |   Assign                   
                         ;
PriorAssign              
                         :   <Priority,Assign>        
                         ;
Assign                   
                         :   Question                    PriorAssign                 Assign                   
                         |   Question                 
                         ;
Question                 
                         :   OrOr                        <Priority,Question>         ExpressionValue             <Separator,Colon>           Question                 
                         |   OrOr                     
                         ;
OrOr                     
                         :   OrOr                        <Priority,OrOr>             AndAnd                   
                         |   AndAnd                   
                         ;
AndAnd                   
                         :   AndAnd                      <Priority,AndAnd>           Or                       
                         |   Or                       
                         ;
Or                       
                         :   Or                          <Priority,Or>               XOr                      
                         |   XOr                      
                         ;
XOr                      
                         :   XOr                         <Priority,XOr>              And                      
                         |   And                      
                         ;
And                      
                         :   And                         <Priority,And>              Equ                      
                         |   Equ                      
                         ;
Equ                      
                         :   Equ                         <Priority,Equ>              Compare                  
                         |   Compare                  
                         ;
Compare                  
                         :   Compare                     <Priority,Compare>          Shift                    
                         |   Shift                    
                         ;
Shift                    
                         :   Shift                       <Priority,Shift>            Term                     
                         |   Term                     
                         ;
Term                     
                         :   Term                        <Priority,Term>             Factor                   
                         |   Factor                   
                         ;
Factor                   
                         :   Factor                      <Priority,Factor>           Unary                    
                         |   Unary                    
                         ;
UnaryIncDec              
                         :   PrimaryExpr                 <Priority,IncDec>        
                         |   PrimaryExpr              
                         ;
Unary                    
                         :   <Priority,Unary>            Unary                    
                         |   <Priority,Term>             Unary                    
                         |   <Priority,IncDec>           Unary                    
                         |   <Syntax,CastUnary>          Unary                    
                         |   UnaryIncDec              
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
Range                    
                         :   <Separator,LeftScrape>      ExpressionValue             <Separator,RightScrape>  
                         ;
Ranges                   
                         :   Ranges                      Range                    
                         |   Range                    
                         ;
CallParams               
                         :   <Syntax,EmptyBracket>    
                         |   <Separator,LeftBracket>     ExpressionValueList         <Separator,RightBracket> 
                         ;
CompaundStmnt            
                         :   <Syntax,EmptyCramp>      
                         |   <Separator,LeftCramp>       StmExpr                     <Separator,RightCramp>   
                         ;
Condition_V              
                         :   <Priority,And>              DefVarAssign             
                         |   DefVarAssign             
                         ;
Condition                
                         :   <Syntax,DefVar>             Condition_V              
                         |   ExpressionCondition      
                         ;
For_Prefix               
                         :   <Separator,Semicolon>    
                         |   DefineSemi               
                         |   ExprSemi                 
                         ;
For_Condition            
                         :   <Separator,Semicolon>    
                         |   Condition                   <Separator,Semicolon>    
                         ;
For_Postfix              
                         :   <Separator,RightBracket> 
                         |   ExpressionExpression        <Separator,RightBracket> 
                         ;
ForStmnt                 
                         :   <Reserv,For>                <Separator,LeftBracket>     For_Prefix                  For_Condition               For_Postfix                 DefExpr                  
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
Statement                
                         :   BegIfStmnt                  <Reserv,Else>               DefExpr                  
                         |   BegIfStmnt               
                         |   <Syntax,Label>              <Separator,Colon>           DefExpr                  
                         |   <Reserv,Do>                 DefExpr                     <Reserv,While>              <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    <Separator,Semicolon>    
                         |   <Reserv,While>              <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    DefExpr                  
                         |   ForStmnt                 
                         |   <Reserv,Switch>             <Separator,LeftBracket>     <Separator,RightBracket> 
                         |   <Reserv,GoTo>               <Ident>                     <Separator,Semicolon>    
                         |   <Reserv,Break>              <Separator,Semicolon>    
                         |   <Reserv,Continue>           <Separator,Semicolon>    
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
                         |   DefFunc                  
                         |   DefineSemi               
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
