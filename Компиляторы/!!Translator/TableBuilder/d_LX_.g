
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
                         :   <Syntax,DefVar>             { YACC(DefType); }          <Ident>                     { CALL(DefVar,1,1); }       DefParInit                  { CALL(DefVar,2,1); }       { NODE(DefVar,(2,1)); }  
                         ;
DefParArr                
                         :   <Syntax,DefArr>             { YACC(DefType); }          <Syntax,IdentArr>           { CALL(DefArr,1,1); }       DefArrDA                    { NODE(DefArr,(3,0,1)); }   DefParInit                  { CALL(DefArr,2,1); }       { NODE(DefArr,(1,2),2); }
                         ;
DefPar                   
                         :   DefParArr                
                         |   DefParVar                
                         ;
DefParItem               
                         :   DefPar                   
                         ;
DefParList               
                         :   <Separator,Comma>           DefParItem                  { YACC(AddToList,6); }      DefParList               
                         |   
                         ;
DefParams                
                         :   { CALL(Define,1,1); }       DefParItem                  { NODE(Define,(1,2),1); }   DefParList                  { CALL(Define,2,1); }    
                         ;
BodyFunc                 
                         :   <Separator,Semicolon>    
                         |   <Syntax,EmptyCramp>         { CALL(Null,0); }           { NODE(Null,(1)); }      
                         |   <Separator,LeftCramp>       StmExpr                     { NODE(None,(1)); }         <Separator,RightCramp>   
                         ;
DefFuncParam             
                         :   <Syntax,EmptyBracket>       { CALL(DefFunc,4); }     
                         |   <Separator,LeftBracket>     DefParams                   { CALL(DefFunc,4,1); }      { NODE(None,(1)); }         <Separator,RightBracket> 
                         ;
DefFunc                  
                         :   <Syntax,DefFunc>            { CALL(DefFunc,1); }        { NODE(DefFunc,(0)); }      <Syntax,IdentFunc>          { NODE(DefFunc,(0),1); }    { CALL(DefFunc,2); }        DefFuncParam                { NODE(DefFunc,(0),2); }    BodyFunc                    { CALL(DefFunc,8); }        { CALL(DefFunc,16); }       { NODE(DefFunc,(0),3); } 
                         ;
AInitialList             
                         :   <Separator,Comma>           AInitItem                   { YACC(AddToList,6); }      AInitialList             
                         |   
                         ;
AInitial                 
                         :   AInitItem                   { YACC(AddToList,6); }      AInitialList             
                         ;
Initializer              
                         :   <Syntax,EmptyCramp>         { CALL(List,1); }           { CALL(List,2); }           { NODE(List,(0)); }      
                         |   <Separator,LeftCramp>       { CALL(List,1); }           { NODE(List,(0,2)); }       AInitial                    { CALL(List,2); }           <Separator,RightCramp>   
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
                         :   <Separator,LeftScrape>      Assign                      { YACC(AddToList,10); }     <Separator,RightScrape>     DRanges                  
                         |   
                         ;
DefArrD1A                
                         :   <Syntax,EmptyScrape>        { CALL(Null,0); }           { NODE(Ranges,(0),5); }  
                         |   <Separator,LeftScrape>      Assign                      { NODE(Ranges,(1),2); }     <Separator,RightScrape>  
                         ;
DefArrDA                 
                         :   { CALL(List,1); }           DefArrD1A                   { NODE(None,(1,2)); }       DRanges                     { CALL(List,2); }        
                         ;
DefArr                   
                         :   <Syntax,IdentArr>           { CALL(DefArr,1); }         DefArrDA                    { CALL(DefArr,4); }         { NODE(DefArr,(0,0,1)); }   DefAInit                    { CALL(DefArr,2); }         { NODE(DefArr,(1,2),2); }
                         ;
DefVarInit               
                         :   <Oper,Assign>               Assign                   
                         |   
                         ;
DefVar                   
                         :   <Ident>                     { CALL(DefVar,1); }         DefVarInit                  { CALL(DefVar,2); }         { NODE(DefVar,(0,1)); }  
                         ;
DefIAV                   
                         :   DefArr                   
                         |   DefVar                   
                         ;
DefItem                  
                         :   <Priority,And>              DefIAV                      { CALL(RefDef,0); }         { NODE(RefDef,(1)); }    
                         |   DefIAV                   
                         ;
DefType                  
                         :   <Syntax,DefArr>          
                         |   <Syntax,DefVar>          
                         ;
DefineList               
                         :   <Separator,Comma>           DefItem                     { YACC(AddToList,6); }      DefineList               
                         |   
                         ;
Define                   
                         :   DefType                     { CALL(Define,1); }         { NODE(Define,(4)); }       DefItem                     { YACC(AddToList,2); }      DefineList                  { CALL(Define,2); }         { NODE(Define,(0),2); }  
                         ;
ConditionDef             
                         :   <Priority,And>              DefVar                      { CALL(RefDef,0); }         { NODE(RefDef,(1)); }    
                         |   DefVar                   
                         ;
Condition                
                         :   <Syntax,DefVar>             { TREE(Define); }           ConditionDef                { TREE(PushDef); }          { NODE(None,(1)); }      
                         |   ExpressionCondition      
                         ;
ExprList                 
                         :   <Separator,Comma>           Assign                      { YACC(AddToList,6); }      ExprList                 
                         |   
                         ;
PriorAssign              
                         :   <Priority,Assign>        
                         ;
AssignList               
                         :   PriorAssign                 { CALL(Binary,1); }         { NODE(None,(2),2); }       Assign                      { CALL(Binary,2); }         { NODE(Binary,(2,1)); }  
                         |   
                         ;
Assign                   
                         :   Question                    { NODE(None,(1,2)); }       AssignList               
                         ;
QuestionList             
                         :   <Priority,Question>         { CALL(Trio,1); }           ExpressionValue             { NODE(Trio,(0)); }         <Separator,Colon>           Question                    { NODE(Trio,(0),1); }       { CALL(Trio,2); }        
                         |   
                         ;
Question                 
                         :   OrOr                        { NODE(None,(1,2)); }       QuestionList             
                         ;
OrOr                     
                         :   AndAnd                      { NODE(None,(1,2)); }       OrOr_                    
                         ;
OrOr_                    
                         :   <Priority,OrOr>             { CALL(Binary,1); }         AndAnd                      { CALL(Binary,2); }         { NODE(Binary,(3,1,2)); }   OrOr_                    
                         |   
                         ;
AndAnd                   
                         :   Or                          { NODE(None,(1,2)); }       AndAnd_                  
                         ;
AndAnd_                  
                         :   <Priority,AndAnd>           { CALL(Binary,1); }         Or                          { CALL(Binary,2); }         { NODE(Binary,(3,1,2)); }   AndAnd_                  
                         |   
                         ;
Or                       
                         :   XOr                         { NODE(None,(1,2)); }       Or_                      
                         ;
Or_                      
                         :   <Priority,Or>               { CALL(Binary,1); }         XOr                         { CALL(Binary,2); }         { NODE(Binary,(3,1,2)); }   Or_                      
                         |   
                         ;
XOr                      
                         :   And                         { NODE(None,(1,2)); }       XOr_                     
                         ;
XOr_                     
                         :   <Priority,XOr>              { CALL(Binary,1); }         And                         { CALL(Binary,2); }         { NODE(Binary,(3,1,2)); }   XOr_                     
                         |   
                         ;
And                      
                         :   Equ                         { NODE(None,(1,2)); }       And_                     
                         ;
And_                     
                         :   <Priority,And>              { CALL(Binary,1); }         Equ                         { CALL(Binary,2); }         { NODE(Binary,(3,1,2)); }   And_                     
                         |   
                         ;
Equ                      
                         :   Compare                     { NODE(None,(1,2)); }       Equ_                     
                         ;
Equ_                     
                         :   <Priority,Equ>              { CALL(Binary,1); }         Compare                     { CALL(Binary,2); }         { NODE(Binary,(3,1,2)); }   Equ_                     
                         |   
                         ;
Compare                  
                         :   Shift                       { NODE(None,(1,2)); }       Compare_                 
                         ;
Compare_                 
                         :   <Priority,Compare>          { CALL(Binary,1); }         Shift                       { CALL(Binary,2); }         { NODE(Binary,(3,1,2)); }   Compare_                 
                         |   
                         ;
Shift                    
                         :   Term                        { NODE(None,(1,2)); }       Shift_                   
                         ;
Shift_                   
                         :   <Priority,Shift>            { CALL(Binary,1); }         Term                        { CALL(Binary,2); }         { NODE(Binary,(3,1,2)); }   Shift_                   
                         |   
                         ;
Term                     
                         :   Factor                      { NODE(None,(1,2)); }       Term_                    
                         ;
Term_                    
                         :   <Priority,Term>             { CALL(Binary,1); }         Factor                      { CALL(Binary,2); }         { NODE(Binary,(3,1,2)); }   Term_                    
                         |   
                         ;
Factor                   
                         :   Unary                       { NODE(None,(1,2)); }       Factor_                  
                         ;
Factor_                  
                         :   <Priority,Factor>           { CALL(Binary,1); }         Unary                       { CALL(Binary,2); }         { NODE(Binary,(3,1,2)); }   Factor_                  
                         |   
                         ;
UnaryIncDec              
                         :   <Priority,IncDec>           { CALL(Unary,4); }          { NODE(Unary,(2),1); }   
                         |   
                         ;
Unary                    
                         :   <Priority,Unary>            { CALL(Unary,1); }          Unary                       { CALL(Unary,2); }          { NODE(Unary,(1,2)); }   
                         |   <Priority,Term>             { CALL(Unary,1,1); }        Unary                       { CALL(Unary,2); }          { NODE(Unary,(1,2),1); } 
                         |   <Priority,IncDec>           { CALL(Unary,1); }          Unary                       { CALL(Unary,2); }          { NODE(Unary,(1,2)); }   
                         |   <Syntax,CastUnary>          { CALL(Cast,1); }           Unary                       { CALL(Cast,2); }           { NODE(Cast,(1,2)); }    
                         |   PrimaryExpr                 { NODE(None,(1,2)); }       UnaryIncDec              
                         ;
Primary                  
                         :   <Separator,LeftBracket>     ExpressionNone              { NODE(None,(1)); }         <Separator,RightBracket> 
                         ;
PrimaryExpr              
                         :   <Integer>                   { CALL(Number,0); }         { NODE(Number,(1)); }    
                         |   <Number>                    { CALL(Number,0); }         { NODE(Number,(1)); }    
                         |   <Syntax,IdentArr>           { CALL(Index,1); }          Ranges                      { CALL(Index,2); }          { NODE(Index,(1)); }     
                         |   <Syntax,IdentFunc>          { CALL(Call,1); }           CallParams                  { CALL(Call,2); }           { NODE(Call,(1)); }      
                         |   <Syntax,Cast>               { CALL(Cast,1); }           Primary                     { CALL(Cast,2); }           { NODE(Cast,(1)); }      
                         |   <Ident>                     { CALL(Var,0); }            { NODE(Var,(1)); }       
                         |   Primary                  
                         ;
RangesList               
                         :   <Separator,LeftScrape>      ExpressionValue             { YACC(AddToList,10); }     <Separator,RightScrape>     RangesList               
                         |   
                         ;
Ranges                   
                         :   { CALL(List,1); }           { NODE(List,(2,3)); }       RangesList                  { CALL(List,2); }        
                         ;
CallParams               
                         :   <Syntax,EmptyBracket>    
                         |   <Separator,LeftBracket>     ExpressionValueList         { NODE(None,(1)); }         <Separator,RightBracket> 
                         ;
CompaundStmnt            
                         :   <Syntax,EmptyCramp>         { CALL(Null,0); }           { NODE(Null,(1)); }      
                         |   <Separator,LeftCramp>       { CALL(Statements,1); }     StmExpr                     { NODE(None,(1)); }         { CALL(Statements,4); }     <Separator,RightCramp>   
                         ;
IfStmnt_                 
                         :   <Reserv,Else>               DefExpr                  
                         |   
                         ;
IfStmnt                  
                         :   <Reserv,If>                 <Separator,LeftBracket>     { CALL(If,1); }             { NODE(If,(0),-1); }        Condition                   { CALL(If,2); }             { NODE(If,(1)); }           <Separator,RightBracket>    DefExpr                     { CALL(If,4); }             { NODE(If,(1),1); }         IfStmnt_                    { CALL(If,8); }             { NODE(If,(1),2); }      
                         ;
ForPrefix                
                         :   <Separator,Semicolon>       { CALL(Null,0); }           { NODE(Null,(1)); }      
                         |   DefineSemi               
                         |   ExprSemi                 
                         ;
ForCondition             
                         :   <Separator,Semicolon>       { CALL(Null,0); }           { NODE(Null,(1)); }      
                         |   Condition                   { NODE(None,(1)); }         <Separator,Semicolon>    
                         ;
ForPosfix                
                         :   <Separator,RightBracket>    { CALL(Null,0); }           { NODE(Null,(1)); }      
                         |   ExpressionExpression        { NODE(None,(1)); }         <Separator,RightBracket> 
                         ;
ForStmnt                 
                         :   <Reserv,For>                <Separator,LeftBracket>     { CALL(For,1); }            { NODE(For,(0),-1); }       ForPrefix                   { NODE(For,(1)); }          ForCondition                { NODE(For,(1),1); }        ForPosfix                   { NODE(For,(1),2); }        { CALL(For,2); }            DefExpr                     { NODE(For,(1),3); }        { CALL(For,4); }            { NODE(For,(0),-2); }       { CALL(For,8); }         
                         ;
DoStmnt                  
                         :   <Reserv,Do>                 { CALL(Do,1); }             { NODE(Do,(0),-1); }        DefExpr                     { CALL(Do,4); }             { NODE(Do,(1),1); }         <Reserv,While>              <Separator,LeftBracket>     Condition                   { NODE(Do,(1)); }           { CALL(Do,2); }             <Separator,RightBracket>    { NODE(Do,(0),-2); }        { CALL(Do,8); }             <Separator,Semicolon>    
                         ;
WhileStmnt               
                         :   <Reserv,While>              { NODE(While,(0),-1); }     { CALL(While,1); }          <Separator,LeftBracket>     Condition                   { CALL(While,2); }          { NODE(While,(1)); }        <Separator,RightBracket>    DefExpr                     { CALL(While,4); }          { NODE(While,(1),1); }      { NODE(While,(0),-2); }     { CALL(While,8); }       
                         ;
GoToStmnt                
                         :   <Reserv,GoTo>               <Ident>                     <Separator,Semicolon>       { CALL(GoTo,0); }           { NODE(GoTo,(1)); }      
                         ;
BreakStmnt               
                         :   <Reserv,Break>              <Separator,Semicolon>       { CALL(Break,0); }          { NODE(Break,(1)); }     
                         ;
ContinueStmnt            
                         :   <Reserv,Continue>           <Separator,Semicolon>       { CALL(Continue,0); }       { NODE(Continue,(1)); }  
                         ;
ReturnVal                
                         :   ExpressionValue          
                         |   
                         ;
ReturnStmnt              
                         :   <Reserv,Return>             { CALL(Return,1); }         ReturnVal                   { CALL(Return,2); }         { NODE(Return,(1)); }       <Separator,Semicolon>    
                         ;
Statement                
                         :   <Syntax,Label>              <Separator,Colon>           { CALL(Label,0); }          { NODE(Label,(1)); }     
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
                         :   Define                      { NODE(None,(1)); }         <Separator,Semicolon>    
                         ;
ExprSemi                 
                         :   ExpressionExpression        { NODE(None,(1)); }         <Separator,Semicolon>    
                         ;
DefExpr                  
                         :   <Separator,Semicolon>       { CALL(Null,0); }           { NODE(Null,(1)); }      
                         |   DefineSemi               
                         |   Statement                
                         |   ExprSemi                 
                         ;
StmExprList              
                         :   DefExpr                     { YACC(AddToList,6); }      StmExprList              
                         |   
                         ;
StmExpr                  
                         :   { CALL(Statements,1); }     { NODE(Statements,(2)); }   StmExprList                 { CALL(Statements,4); }     { NODE(Statements,(0),-2); }                      
                         ;
DefFAV                   
                         :   <Separator,Semicolon>       { CALL(Null,0); }           { NODE(Null,(1)); }      
                         |   DefFunc                  
                         |   DefineSemi               
                         ;
DefinesList              
                         :   DefFAV                      { YACC(AddToList,6); }      DefinesList              
                         |   
                         ;
Defines                  
                         :   { CALL(Statements,1); }     { NODE(Statements,(2)); }   DefinesList                 { CALL(Statements,4); }     { NODE(Statements,(0),-2); }                      
                         ;
ExpressionExpression     
                         :   Assign                      { CALL(Expressions,1); }    { NODE(Expressions,(2,3),1); }                       ExprList                    { CALL(Expressions,2,16); }                          { YACC(ExpressionSLL,16); }                       
                         ;
ExpressionCondition      
                         :   Assign                      { CALL(Expressions,1); }    { NODE(Expressions,(2,3),1); }                       ExprList                    { CALL(Expressions,2,241); }                         { YACC(ExpressionSLL,241); }                      
                         ;
ExpressionNone           
                         :   Assign                      { CALL(Expressions,1); }    { NODE(Expressions,(2,3),1); }                       ExprList                    { CALL(Expressions,2); }    { YACC(ExpressionSLL); } 
                         ;
ExpressionValue          
                         :   Assign                      { CALL(Expressions,1); }    { NODE(Expressions,(2,3),1); }                       ExprList                    { CALL(Expressions,2,256); }                         { YACC(ExpressionSLL,256); }                      
                         ;
ExpressionValueList      
                         :   Assign                      { CALL(Expressions,1); }    { NODE(Expressions,(2,3),1); }                       ExprList                    { CALL(Expressions,2,512); }                         { YACC(ExpressionSLL,512); }                      
                         ;
