
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
                         :   DefBegParVar                _f_00091_                
                         ;
DefBegParArr             
                         :   <Syntax,IdentArr>           { MAKE(DefParArr); }        { TURN(Make,List); }        DefBegRanges                { TURN(Make,DefArr,-2); }
                         ;
DefParArr                
                         :   DefBegParArr                _f_00091_                
                         ;
DefParItem               
                         :   <Syntax,DefArr>             { TURN(Push,Type); }        DefParArr                
                         |   <Syntax,DefVar>             { TURN(Push,Type); }        DefParVar                
                         ;
DefParams                
                         :   DefParItem                  { TREE(AddToList); }        { TURN(Down,None); }        _f_00073_                
                         ;
BodyFunc                 
                         :   <Separator,Semicolon>       { MAKE(BodyFunc); }         { TURN(Make,Null); }     
                         |   <Syntax,EmptyCramp>         { MAKE(BodyFunc,1); }       { TURN(Make,Statements); }                        
                         |   <Separator,LeftCramp>       { CODE(EndParams); }        { MAKE(BegStmExprLR); }     { TURN(Make,Statements); }                           StmExpr                     <Separator,RightCramp>      { MAKE(BodyFunc,2); }    
                         ;
DefFunc_                 
                         :   <Syntax,EmptyBracket>       { TURN(Make,Null); }        { TURN(Down,None); }     
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
                         :   Initializer                 { TREE(AddToList); }        { TURN(Down,None); }        _f_00074_                
                         |   Assign                      { CODE(AInitItem); }        { TREE(AddToList); }        { TURN(Down,None); }        _f_00074_                
                         ;
Initializer              
                         :   <Syntax,EmptyCramp>         { CODE(BegInitial); }       { TREE(NodeListLR); }       { TURN(Make,List); }     
                         |   <Separator,LeftCramp>       { CODE(BegInitial,1); }     { TREE(NodeListLR); }       { TURN(Make,List); }        AInitial                    <Separator,RightCramp>      { CODE(EndInitial); }    
                         ;
DefRanges_               
                         :   <Separator,LeftScrape>      Assign                      <Separator,RightScrape>  
                         ;
DefRanges                
                         :   DefRanges_                  { MAKE(DRange); }           { TURN(Down,None); }        _f_00075_                
                         ;
DefBegRanges             
                         :   <Syntax,EmptyScrape>        { MAKE(DefArrD1AEmpty); }   { TURN(Put,Null); }         { TURN(Down,None); }        _f_00092_                
                         |   DefRanges_                  { MAKE(DRange); }           { TURN(Down,None); }        _f_00075_                
                         ;
DefBegArr                
                         :   <Syntax,IdentArr>           { MAKE(DefArray); }         { TURN(Push,DefArr); }      { TURN(Make,Ranges); }      DefBegRanges                { CODE(EndRanges); }        { TURN(Down,None); }     
                         ;
DefArr                   
                         :   DefBegArr                   _f_00093_                
                         ;
DefVarIdent              
                         :   <Ident>                     { MAKE(DefIdent); }         { TURN(Push,DefVar); }   
                         ;
DefVarAssign             
                         :   <Oper,Assign>               { CODE(BegDefVarAssign); }                           { TURN(Command,Lexeme,-1); }                         Assign                      { MAKE(DefVarAssign); }     { TURN(Down,None); }     
                         ;
DefVar                   
                         :   DefVarIdent                 _f_00094_                
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
                         :   DefItem                     { TREE(AddToList); }        { TURN(Down,None); }        _f_00076_                
                         ;
Define                   
                         :   DefType                     { MAKE(Define); }           { TURN(Push,Type); }        { TURN(Make,Define,1); }    DefineComma                 { CODE(EndDefine); }     
                         ;
Expressions              
                         :   Assign                      { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                
                         ;
PriorAssign              
                         :   <Priority,Assign>        
                         ;
Assign                   
                         :   Question                    _f_00095_                
                         ;
Question                 
                         :   OrOr                        _f_00096_                
                         ;
OrOr                     
                         :   AndAnd                      _f_00078_                
                         ;
AndAnd                   
                         :   Or                          _f_00079_                
                         ;
Or                       
                         :   XOr                         _f_00080_                
                         ;
XOr                      
                         :   And                         _f_00081_                
                         ;
And                      
                         :   Equ                         _f_00082_                
                         ;
Equ                      
                         :   Compare                     _f_00083_                
                         ;
Compare                  
                         :   Shift                       _f_00084_                
                         ;
Shift                    
                         :   Term                        _f_00085_                
                         ;
Term                     
                         :   Factor                      _f_00086_                
                         ;
Factor                   
                         :   Unary                       _f_00087_                
                         ;
UnaryIncDec              
                         :   PrimaryExpr                 _f_00097_                
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
                         :   Range                       { MAKE(BegIndexLR); }       { TURN(Make,Ranges,1); }    _f_00088_                
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
                         |   <Syntax,DefVar>             { MAKE(Define); }           Condition_V                 { MAKE(PushDef); }          <Separator,Semicolon>    
                         |   ExpressionCondition         <Separator,Semicolon>    
                         ;
For_Postfix              
                         :   <Separator,RightBracket>    { TREE(NodeNull); }         { TURN(Make,Null); }     
                         |   ExpressionExpression        <Separator,RightBracket> 
                         ;
ForStmnt                 
                         :   <Reserv,For>                <Separator,LeftBracket>     { CODE(BegFor); }           For_Prefix                  { CODE(PrefFor); }          For_Condition               { CODE(ConditionFor); }     For_Postfix                 { CODE(PostFor); }          DefExpr                     { MAKE(For); }              { TURN(Make,For,4); }    
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
                         :   BegIfStmnt                  _f_00098_                
                         |   <Syntax,Label>              <Separator,Colon>           { CODE(Label); }            { TURN(Push,Label); }       DefExpr                     { TREE(Label); }            { TURN(Make,List,2); }   
                         |   <Reserv,Do>                 DefExpr                     <Reserv,While>              <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    <Separator,Semicolon>       { MAKE(Do); }               { TURN(Make,Do,-2); }    
                         |   <Reserv,While>              <Separator,LeftBracket>     Condition                   <Separator,RightBracket>    DefExpr                     { MAKE(While); }            { TURN(Make,While,-2); } 
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
                         |   ExpressionExpression        <Separator,Semicolon>    
                         ;
StmExprList              
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { TURN(Make,Null); }        { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                
                         |   DefineSemi                  { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                
                         |   Statement                   { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                
                         |   ExpressionExpression        <Separator,Semicolon>       { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                
                         ;
StmExpr                  
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { TURN(Make,Null); }        { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                   { CODE(EndBlock); }      
                         |   DefineSemi                  { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                   { CODE(EndBlock); }      
                         |   Statement                   { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                   { CODE(EndBlock); }      
                         |   ExpressionExpression        <Separator,Semicolon>       { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                   { CODE(EndBlock); }      
                         ;
DefFAV                   
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { TURN(Make,Null); }     
                         |   DefFunc                  
                         |   DefineSemi               
                         ;
DefinesList              
                         :   DefFAV                      { TREE(BegStmExprLR,1); }   { TURN(Down,None); }        _f_00090_                
                         ;
Defines                  
                         :   { CODE(BegStmExprLR); }     { TURN(Make,Statements); }                           DefinesList                 { CODE(EndBlock); }      
                         ;
ExpressionExpression     
                         :   Unary                       _f_00087_                   _f_00086_                   _f_00085_                   _f_00084_                   _f_00083_                   _f_00082_                   _f_00081_                   _f_00080_                   _f_00079_                   _f_00078_                   _f_00100_                
                         ;
ExpressionCondition      
                         :   Unary                       _f_00087_                   _f_00086_                   _f_00085_                   _f_00084_                   _f_00083_                   _f_00082_                   _f_00081_                   _f_00080_                   _f_00079_                   _f_00078_                   _f_00102_                
                         ;
ExpressionNone           
                         :   Unary                       _f_00087_                   _f_00086_                   _f_00085_                   _f_00084_                   _f_00083_                   _f_00082_                   _f_00081_                   _f_00080_                   _f_00079_                   _f_00078_                   _f_00104_                
                         ;
ExpressionValue          
                         :   Unary                       _f_00087_                   _f_00086_                   _f_00085_                   _f_00084_                   _f_00083_                   _f_00082_                   _f_00081_                   _f_00080_                   _f_00079_                   _f_00078_                   _f_00106_                
                         ;
ExpressionValueList      
                         :   Unary                       _f_00087_                   _f_00086_                   _f_00085_                   _f_00084_                   _f_00083_                   _f_00082_                   _f_00081_                   _f_00080_                   _f_00079_                   _f_00078_                   _f_00108_                
                         ;
_f_00073_                
                         :   <Separator,Comma>           DefParItem                  { TREE(AddToList); }        { TURN(Down,None); }        _f_00073_                
                         |   
                         ;
_f_00074_                
                         :   <Separator,Comma>           AInitItem                   { TREE(AddToList); }        { TURN(Down,None); }        _f_00074_                
                         |   
                         ;
_f_00075_                
                         :   DefRanges_                  { MAKE(DRange); }           { TURN(Down,None); }        _f_00075_                
                         |   
                         ;
_f_00076_                
                         :   <Separator,Comma>           DefItem                     { TREE(AddToList); }        { TURN(Down,None); }        _f_00076_                
                         |   
                         ;
_f_00077_                
                         :   <Separator,Comma>           Assign                      { TREE(AddToList); }        { TURN(Down,None); }        { CODE(AddToExpr); }        _f_00077_                
                         |   
                         ;
_f_00078_                
                         :   <Priority,OrOr>             AndAnd                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   _f_00078_                
                         |   
                         ;
_f_00079_                
                         :   <Priority,AndAnd>           Or                          { MAKE(Binary); }           { TURN(Make,Binary,-2); }   _f_00079_                
                         |   
                         ;
_f_00080_                
                         :   <Priority,Or>               XOr                         { MAKE(Binary); }           { TURN(Make,Binary,-2); }   _f_00080_                
                         |   
                         ;
_f_00081_                
                         :   <Priority,XOr>              And                         { MAKE(Binary); }           { TURN(Make,Binary,-2); }   _f_00081_                
                         |   
                         ;
_f_00082_                
                         :   <Priority,And>              Equ                         { MAKE(Binary); }           { TURN(Make,Binary,-2); }   _f_00082_                
                         |   
                         ;
_f_00083_                
                         :   <Priority,Equ>              Compare                     { MAKE(Binary); }           { TURN(Make,Binary,-2); }   _f_00083_                
                         |   
                         ;
_f_00084_                
                         :   <Priority,Compare>          Shift                       { MAKE(Binary); }           { TURN(Make,Binary,-2); }   _f_00084_                
                         |   
                         ;
_f_00085_                
                         :   <Priority,Shift>            Term                        { MAKE(Binary); }           { TURN(Make,Binary,-2); }   _f_00085_                
                         |   
                         ;
_f_00086_                
                         :   <Priority,Term>             Factor                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   _f_00086_                
                         |   
                         ;
_f_00087_                
                         :   <Priority,Factor>           Unary                       { MAKE(Binary); }           { TURN(Make,Binary,-2); }   _f_00087_                
                         |   
                         ;
_f_00088_                
                         :   Range                       { MAKE(IndexLR); }          { TURN(Down,None); }        _f_00088_                
                         |   
                         ;
_f_00089_                
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { TURN(Make,Null); }        { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                
                         |   DefineSemi                  { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                
                         |   Statement                   { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                
                         |   Unary                       _f_00087_                   _f_00086_                   _f_00085_                   _f_00084_                   _f_00083_                   _f_00082_                   _f_00081_                   _f_00080_                   _f_00079_                   _f_00078_                   _f_00110_                
                         |   
                         ;
_f_00090_                
                         :   DefFAV                      { TREE(AddToList); }        { TURN(Down,None); }        _f_00090_                
                         |   
                         ;
_f_00091_                
                         :   
                         |   <Oper,Assign>               { CODE(BegParVarAssign); }                           { TURN(Command,Lexeme,-1); }                         Assign                      { MAKE(ParVarAssign); }     { TURN(Down,None); }     
                         ;
_f_00092_                
                         :   
                         |   DefRanges                
                         ;
_f_00093_                
                         :   
                         |   <Oper,Assign>               { CODE(BegAInit); }         { TURN(Command,Lexeme,-1); }                         Initializer                 { MAKE(EndAInit); }         { TURN(Down,None); }     
                         ;
_f_00094_                
                         :   
                         |   DefVarAssign             
                         ;
_f_00095_                
                         :   
                         |   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }
                         ;
_f_00096_                
                         :   
                         |   <Priority,Question>         { CODE(BegQuestion); }      ExpressionValue             <Separator,Colon>           { CODE(MidQuestion); }      Question                    { MAKE(Question); }         { TURN(Make,Trio,-3); }  
                         ;
_f_00097_                
                         :   
                         |   <Priority,IncDec>           { MAKE(IncDec); }           { TURN(Make,IncDec,-1); }
                         ;
_f_00098_                
                         :   <Reserv,Else>               { CODE(Else); }             DefExpr                     { MAKE(If,1); }             { TURN(Down,None); }     
                         |   { MAKE(If); }            
                         ;
_f_00099_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,16); }                          { TURN(Command,Param,16); }                       
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,16); }                          { TURN(Command,Param,16); }                       
                         ;
_f_00100_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,16); }                          { TURN(Command,Param,16); }                       
                         |   <Priority,Question>         { CODE(BegQuestion); }      ExpressionValue             <Separator,Colon>           { CODE(MidQuestion); }      Question                    { MAKE(Question); }         { TURN(Make,Trio,-3); }     _f_00099_                
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,16); }                          { TURN(Command,Param,16); }                       
                         ;
_f_00101_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,241); }                         { TURN(Command,Param,241); }                      
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,241); }                         { TURN(Command,Param,241); }                      
                         ;
_f_00102_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,241); }                         { TURN(Command,Param,241); }                      
                         |   <Priority,Question>         { CODE(BegQuestion); }      ExpressionValue             <Separator,Colon>           { CODE(MidQuestion); }      Question                    { MAKE(Question); }         { TURN(Make,Trio,-3); }     _f_00101_                
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,241); }                         { TURN(Command,Param,241); }                      
                         ;
_f_00103_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR); }    { TURN(Command,Param); } 
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR); }    { TURN(Command,Param); } 
                         ;
_f_00104_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR); }    { TURN(Command,Param); } 
                         |   <Priority,Question>         { CODE(BegQuestion); }      ExpressionValue             <Separator,Colon>           { CODE(MidQuestion); }      Question                    { MAKE(Question); }         { TURN(Make,Trio,-3); }     _f_00103_                
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR); }    { TURN(Command,Param); } 
                         ;
_f_00105_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,256); }                         { TURN(Command,Param,256); }                      
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,256); }                         { TURN(Command,Param,256); }                      
                         ;
_f_00106_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,256); }                         { TURN(Command,Param,256); }                      
                         |   <Priority,Question>         { CODE(BegQuestion); }      ExpressionValue             <Separator,Colon>           { CODE(MidQuestion); }      Question                    { MAKE(Question); }         { TURN(Make,Trio,-3); }     _f_00105_                
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,256); }                         { TURN(Command,Param,256); }                      
                         ;
_f_00107_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,512); }                         { TURN(Command,Param,512); }                      
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,512); }                         { TURN(Command,Param,512); }                      
                         ;
_f_00108_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,512); }                         { TURN(Command,Param,512); }                      
                         |   <Priority,Question>         { CODE(BegQuestion); }      ExpressionValue             <Separator,Colon>           { CODE(MidQuestion); }      Question                    { MAKE(Question); }         { TURN(Make,Trio,-3); }     _f_00107_                
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,512); }                         { TURN(Command,Param,512); }                      
                         ;
_f_00109_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,16); }                          { TURN(Command,Param,16); }                          <Separator,Semicolon>       { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,16); }                          { TURN(Command,Param,16); }                          <Separator,Semicolon>       { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                
                         ;
_f_00110_                
                         :   PriorAssign                 Assign                      { MAKE(Binary); }           { TURN(Make,Binary,-2); }   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,16); }                          { TURN(Command,Param,16); }                          <Separator,Semicolon>       { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                
                         |   <Priority,Question>         { CODE(BegQuestion); }      ExpressionValue             <Separator,Colon>           { CODE(MidQuestion); }      Question                    { MAKE(Question); }         { TURN(Make,Trio,-3); }     _f_00109_                
                         |   { MAKE(ExpressionsLR); }    { TURN(Make,Expressions,1); }                        _f_00077_                   { MAKE(ExpressionSLR,16); }                          { TURN(Command,Param,16); }                          <Separator,Semicolon>       { TREE(AddToList); }        { TURN(Down,None); }        _f_00089_                
                         ;
