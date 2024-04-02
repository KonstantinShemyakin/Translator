
S_                       
                         :   Program                  
                         ;
Program                  
                         :   Defines                  
                         ;
DefBegParVar             
                         :   <Ident>                     { MAKE(DefParVar); }        { TURN(Make,DefVar,-1); }
                         ;
DefParVar                
                         :   DefBegParVar                <Oper,Assign>               { CODE(BegParVarAssign); }                           { TURN(Command,Lexeme,-1); }                         Assign                      { MAKE(ParVarAssign); }     { TURN(Down,None); }     
                         |   DefBegParVar             
                         ;
DefBegParArr             
                         :   <Syntax,IdentArr>           { MAKE(DefParArr); }        { TURN(Make,List); }        DefBegRanges                { TURN(Make,DefArr,-2); }
                         ;
DefParArr                
                         :   DefBegParArr                <Oper,Assign>               { CODE(BegParVarAssign); }                           { TURN(Command,Lexeme,-1); }                         Assign                      { MAKE(ParVarAssign); }     { TURN(Down,None); }     
                         |   DefBegParArr             
                         ;
DefParItem               
                         :   <Syntax,DefArr>             { TURN(Push,Type); }        DefParArr                
                         |   <Syntax,DefVar>             { TURN(Push,Type); }        DefParVar                
                         ;
DefParams                
                         :   DefParams                   <Separator,Comma>           DefParItem                  { TREE(AddToList); }        { TURN(Down,None); }     
                         |   DefParItem                  { TREE(AddToList); }        { TURN(Down,None); }     
                         ;
BodyFunc                 
                         :   <Separator,Semicolon>       { MAKE(BodyFunc); }         { TURN(Make,Null); }     
                         |   <Syntax,EmptyCramp>         { MAKE(BodyFunc,1); }       { TURN(Make,Statements); }                        
                         |   <Separator,LeftCramp>       { CODE(EndParams); }        { MAKE(BegStmExprLR); }     { TURN(Make,Statements); }                           StmExpr                     <Separator,RightCramp>      { MAKE(BodyFunc,2); }    
                         ;
DefFunc_                 
                         :   <Syntax,EmptyBracket>       { TREE(EndParams,2); }      { TURN(Make,Null); }        { TURN(Down,None); }     
                         |   <Separator,LeftBracket>     { TREE(Define,2); }         { TURN(Make,Define); }      DefParams                   <Separator,RightBracket>    { TREE(EndParams); }        { TURN(Down,None,1); }   
                         ;
DefFunc                  
                         :   <Syntax,DefFunc>            { TURN(Push,Type); }        <Syntax,IdentFunc>          { MAKE(FuncIdent); }        { TURN(Make,DefFunc,-1); }                           DefFunc_                    BodyFunc                    { TURN(Down,None); }     
                         ;
AInitItem                
                         :   Initializer              
                         |   Assign                      { CODE(AInitItem); }     
                         ;
AInitial                 
                         :   AInitial                    <Separator,Comma>           AInitItem                   { TREE(AddToList); }        { TURN(Down,None); }     
                         |   AInitItem                   { TREE(AddToList); }        { TURN(Down,None); }     
                         ;
Initializer              
                         :   <Syntax,EmptyCramp>         { CODE(BegInitial); }       { TREE(NodeListLR); }       { TURN(Make,List); }     
                         |   <Separator,LeftCramp>       { CODE(BegInitial,1); }     { TREE(NodeListLR); }       { TURN(Make,List); }        AInitial                    <Separator,RightCramp>      { CODE(EndInitial); }    
                         ;
DefRanges_               
                         :   <Separator,LeftScrape>      Assign                      <Separator,RightScrape>  
                         ;
DefRanges                
                         :   DefRanges                   DefRanges_                  { MAKE(DRange); }           { TURN(Down,None); }     
                         |   DefRanges_                  { MAKE(DRange); }           { TURN(Down,None); }     
                         ;
DefBegRanges             
                         :   <Syntax,EmptyScrape>        { MAKE(DefArrD1AEmpty); }   { TURN(Put,Null); }         { TURN(Down,None); }        DefRanges                
                         |   <Syntax,EmptyScrape>        { MAKE(DefArrD1AEmpty); }   { TURN(Put,Null); }         { TURN(Down,None); }     
                         |   DefRanges                
                         ;
DefBegArr                
                         :   <Syntax,IdentArr>           { MAKE(DefArray); }         { TURN(Push,DefArr); }      { TURN(Make,Ranges); }      DefBegRanges                { CODE(EndRanges); }        { TURN(Down,None); }     
                         ;
DefArr                   
                         :   DefBegArr                   <Oper,Assign>               { CODE(BegAInit); }         { TURN(Command,Lexeme,-1); }                         Initializer                 { MAKE(EndAInit); }         { TURN(Down,None); }     
                         |   DefBegArr                
                         ;
DefVarIdent              
                         :   <Ident>                     { MAKE(DefIdent); }         { TURN(Push,DefVar); }   
                         ;
DefVarAssign             
                         :   <Oper,Assign>               { CODE(BegDefVarAssign); }                           { TURN(Command,Lexeme,-1); }                         Assign                      { MAKE(DefVarAssign); }     { TURN(Down,None); }     
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
                         :   <Priority,And>              DefIAV                      { TREE(RefDef); }           { TURN(Command,Lexeme,-1); }                      
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
                         :   DefineComma                 <Separator,Comma>           DefItem                     { TREE(AddToList); }        { TURN(Down,None); }     
                         |   DefItem                     { TREE(AddToList); }        { TURN(Down,None); }     
                         ;
Define                   
                         :   DefType                     { MAKE(Define); }           { TURN(Push,Type); }        { TURN(Make,Define,1); }    DefineComma                 { CODE(EndDefine); }     
                         ;
Expressions              
                         :   Expressions                 <Separator,Comma>           Assign                      { TREE(AddToList); }        { TURN(Down,None); }        { CODE(AddToExpr); }     
                         |   Assign                      { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                     
                         ;
PriorAssign              
                         :   <Priority,Assign>        
                         ;
Assign                   
                         :   Question                    PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }
                         |   Question                 
                         ;
Question                 
                         :   OrOr                        <Priority,Question>         { CODE(BegQuestion); }      ExpressionValue             <Separator,Colon>           { CODE(MidQuestion); }      Question                    { MAKE(Question); }         { TURN(Make,Trio,-3); }  
                         |   OrOr                     
                         ;
OrOr                     
                         :   OrOr                        <Priority,OrOr>             AndAnd                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   AndAnd                   
                         ;
AndAnd                   
                         :   AndAnd                      <Priority,AndAnd>           Or                          { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Or                       
                         ;
Or                       
                         :   Or                          <Priority,Or>               XOr                         { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   XOr                      
                         ;
XOr                      
                         :   XOr                         <Priority,XOr>              And                         { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   And                      
                         ;
And                      
                         :   And                         <Priority,And>              Equ                         { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Equ                      
                         ;
Equ                      
                         :   Equ                         <Priority,Equ>              Compare                     { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Compare                  
                         ;
Compare                  
                         :   Compare                     <Priority,Compare>          Shift                       { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Shift                    
                         ;
Shift                    
                         :   Shift                       <Priority,Shift>            Term                        { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Term                     
                         ;
Term                     
                         :   Term                        <Priority,Term>             Factor                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Factor                   
                         ;
Factor                   
                         :   Factor                      <Priority,Factor>           Unary                       { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { NODE(Binary,(2,1,3)); }
                         |   Unary                    
                         ;
UnaryIncDec              
                         :   PrimaryExpr                 <Priority,IncDec>           { MAKE(IncDec); }           { TURN(Make,IncDec,-1); }
                         |   PrimaryExpr              
                         ;
Unary                    
                         :   <Priority,Unary>            Unary                       { MAKE(Unary); }            { TURN(Make,Unary,-1); } 
                         |   <Priority,Term>             Unary                       { MAKE(Unary); }            { TURN(Make,Unary,-1); } 
                         |   <Priority,IncDec>           Unary                       { MAKE(Unary); }            { TURN(Make,Unary,-1); } 
                         |   <Syntax,CastUnary>          Unary                       { MAKE(Cast); }             { TURN(Make,Cast,-1); }  
                         |   UnaryIncDec              
                         ;
Primary                  
                         :   <Separator,LeftBracket>     ExpressionNone              <Separator,RightBracket>    { TREE(Primary); }          { TURN(Make,Primary,1); }
                         ;
PrimaryExpr              
                         :   <Integer>                   { MAKE(Number); }           { TURN(Push,Number); }   
                         |   <Number>                    { MAKE(Number); }           { TURN(Push,Number); }   
                         |   <Syntax,IdentArr>           { TURN(Push,Index); }       Ranges                      { MAKE(EndIndex); }         { TURN(Down,None); }     
                         |   <Syntax,IdentFunc>          { TURN(Push,Call); }        CallParams                  { TURN(Down,None); }     
                         |   <Syntax,Cast>               Primary                     { MAKE(Cast); }             { TURN(Make,Cast,-1); }  
                         |   <Ident>                     { MAKE(Ident); }            { TURN(Push,Var); }      
                         |   Primary                  
                         ;
Range                    
                         :   <Separator,LeftScrape>      ExpressionValue             <Separator,RightScrape>  
                         ;
Ranges                   
                         :   Ranges                      Range                       { MAKE(IndexLR); }          { TURN(Down,None); }     
                         |   Range                       { MAKE(BegIndexLR); }       { TURN(Make,Ranges,1); } 
                         ;
CallParams               
                         :   <Syntax,EmptyBracket>       { MAKE(Params); }           { TURN(Make,Null); }     
                         |   <Separator,LeftBracket>     ExpressionValueList         <Separator,RightBracket>    { MAKE(Params,1); }      
                         ;
CompaundStmnt            
                         :   <Syntax,EmptyCramp>         { MAKE(Compaund); }         { CODE(EndBlock); }         { TURN(Make,Statements); }                        
                         |   <Separator,LeftCramp>       { MAKE(Compaund); }         { TURN(Make,Statements); }                           StmExpr                     <Separator,RightCramp>   
                         ;
Condition_V              
                         :   <Priority,And>              DefVarAssign                { TREE(RefDef); }           { TURN(Command,Lexeme,-1); }                      
                         |   DefVarAssign             
                         ;
Condition                
                         :   <Syntax,DefVar>             { MAKE(Define); }           Condition_V                 { MAKE(PushDef); }       
                         |   ExpressionCondition      
                         ;
For_Prefix               
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { TURN(Make,Null); }     
                         |   DefineSemi               
                         |   ExprSemi                 
                         ;
For_Condition            
                         :   <Separator,Semicolon>       { MAKE(NodeNull); }         { TURN(Make,Null); }     
                         |   Condition                   <Separator,Semicolon>    
                         ;
For_Postfix              
                         :   <Separator,RightBracket>    { TREE(NodeNull); }         { TURN(Make,Null); }     
                         |   ExpressionExpression        <Separator,RightBracket> 
                         ;
ForStmnt                 
                         :   <Reserv,For>                <Separator,LeftBracket>     { MAKE(BegFor); }           For_Prefix                  { CODE(PrefFor); }          For_Condition               { CODE(ConditionFor); }     For_Postfix                 { CODE(PostFor); }          DefExpr                     { MAKE(For); }              { TURN(Make,For,4); }    
                         ;
ReturnValue              
                         :   <Separator,Semicolon>       { MAKE(Return); }           { TURN(Make,Return); }   
                         |   ExpressionValue             <Separator,Semicolon>       { MAKE(Return,1); }         { TURN(Make,Return,1); } 
                         ;
ReturnStmnt              
                         :   <Reserv,Return>             ReturnValue              
                         ;
BegIfStmnt               
                         :   <Reserv,If>                 <Separator,LeftBracket>     { CODE(BegIf); }            Condition                   <Separator,RightBracket>    { CODE(Then); }             DefExpr                     { TURN(Make,If,2); }     
                         ;
Statement                
                         :   BegIfStmnt                  <Reserv,Else>               { CODE(Else); }             DefExpr                     { MAKE(If,1); }             { TURN(Down,None); }     
                         |   BegIfStmnt                  { MAKE(If); }            
                         |   <Syntax,Label>              <Separator,Colon>           { CODE(Label); }            { TURN(Push,Label); }       DefExpr                     { TREE(Label); }            { TURN(Make,List,2); }   
                         |   <Reserv,Do>                 { MAKE(BegDo); }            DefExpr                     <Reserv,While>              <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    <Separator,Semicolon>       { MAKE(Do); }               { TURN(Make,Do,-2); }    
                         |   <Reserv,While>              { MAKE(BegWhile); }         <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    DefExpr                     { MAKE(While); }            { TURN(Make,While,-2); } 
                         |   ForStmnt                 
                         |   <Reserv,Switch>             <Separator,LeftBracket>     <Separator,RightBracket> 
                         |   <Reserv,GoTo>               <Ident>                     <Separator,Semicolon>       { MAKE(GoTo); }             { TURN(Push,GoTo); }     
                         |   <Reserv,Break>              <Separator,Semicolon>       { MAKE(Break); }            { TURN(Make,Break); }    
                         |   <Reserv,Continue>           <Separator,Semicolon>       { MAKE(Continue); }         { TURN(Make,Continue); } 
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
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { TURN(Make,Null); }     
                         |   DefineSemi               
                         |   Statement                
                         |   ExprSemi                 
                         ;
StmExprList              
                         :   StmExprList                 DefExpr                     { TREE(AddToList); }        { TURN(Down,None); }     
                         |   DefExpr                     { TREE(AddToList); }        { TURN(Down,None); }     
                         ;
StmExpr                  
                         :   StmExprList                 { CODE(EndBlock); }      
                         ;
DefFAV                   
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { TURN(Make,Null); }     
                         |   DefFunc                  
                         |   DefineSemi               
                         ;
DefinesList              
                         :   DefinesList                 DefFAV                      { TREE(AddToList); }        { TURN(Down,None); }     
                         |   DefFAV                      { TREE(BegStmExprLR,1); }   { TURN(Down,None); }     
                         ;
Defines                  
                         :   { CODE(BegStmExprLR); }     { TURN(Make,Statements); }                           DefinesList                 { CODE(EndBlock); }      
                         ;
ExpressionExpression     
                         :   Expressions                 { MAKE(ExpressionSLR,16); }                          { TURN(Command,Param,16); }                       
                         ;
ExpressionCondition      
                         :   Expressions                 { MAKE(ExpressionSLR,241); }                         { TURN(Command,Param,241); }                      
                         ;
ExpressionNone           
                         :   Expressions                 { MAKE(ExpressionSLR); }    { TURN(Command,Param); } 
                         ;
ExpressionValue          
                         :   Expressions                 { MAKE(ExpressionSLR,256); }                         { TURN(Command,Param,256); }                      
                         ;
ExpressionValueList      
                         :   Expressions                 { MAKE(ExpressionSLR,512); }                         { TURN(Command,Param,512); }                      
                         ;
