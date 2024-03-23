
S_                       
                         :   Program                  
                         ;
Program                  
                         :   Defines                  
                         ;
DefParInit               
                         :   <Oper,Assign>               { CODE(BegParVarAssign); }                           Assign                      { MAKE(ParVarAssign); }  
                         |   
                         ;
DefParVar                
                         :   <Syntax,DefVar>             { YACC(DefType); }          <Ident>                     { MAKE(DefParVar); }        DefParInit                  { NODE(DefVar,(2,1)); }  
                         ;
DefParArr                
                         :   <Syntax,DefArr>             { YACC(DefType); }          <Syntax,IdentArr>           { MAKE(DefParArr); }        DefArrDA                    { NODE(DefArr,(3,0,1)); }   DefParInit                  { NODE(DefArr,(1,2),2); }
                         ;
DefPar                   
                         :   DefParArr                
                         |   DefParVar                
                         ;
DefParItem               
                         :   DefPar                      { TREE(AddToList); }     
                         ;
DefParList               
                         :   <Separator,Comma>           DefParItem                  { YACC(AddToList,6); }      DefParList               
                         |   
                         ;
DefParams                
                         :   { TREE(Define,2); }         DefParItem                  { NODE(Define,(1,2),1); }   DefParList                  { TREE(EndParams); }     
                         ;
BodyFunc                 
                         :   <Separator,Semicolon>       { MAKE(BodyFunc); }      
                         |   <Syntax,EmptyCramp>         { MAKE(BodyFunc,1); }       { NODE(Null,(1)); }      
                         |   <Separator,LeftCramp>       { CODE(EndParams); }        StmExpr                     { NODE(None,(1)); }         <Separator,RightCramp>      { MAKE(BodyFunc,2); }    
                         ;
DefFunc_                 
                         :   <Syntax,EmptyBracket>       { TREE(EndParams,2); }   
                         |   <Separator,LeftBracket>     DefParams                   { NODE(None,(1)); }         <Separator,RightBracket> 
                         ;
DefFunc                  
                         :   <Syntax,DefFunc>            { NODE(DefFunc,(0)); }      <Syntax,IdentFunc>          { NODE(DefFunc,(0),1); }    { MAKE(FuncIdent); }        DefFunc_                    { NODE(DefFunc,(0),2); }    BodyFunc                    { NODE(DefFunc,(0),3); } 
                         ;
AInitialList             
                         :   <Separator,Comma>           AInitItem                   { YACC(AddToList,6); }      { TREE(AddToList); }        AInitialList             
                         |   
                         ;
AInitial                 
                         :   AInitItem                   { TREE(AddToList); }        { YACC(AddToList,6); }      AInitialList             
                         ;
Initializer              
                         :   <Syntax,EmptyCramp>         { CODE(BegInitial); }       { TREE(NodeListLL); }       { NODE(List,(0)); }      
                         |   <Separator,LeftCramp>       { CODE(BegInitial,1); }     { TREE(NodeListLL); }       { NODE(List,(0,2)); }       AInitial                    <Separator,RightCramp>      { CODE(EndInitial); }    
                         ;
AInitItem                
                         :   Initializer              
                         |   Assign                      { CODE(AInitItem); }     
                         ;
DefAInit                 
                         :   <Oper,Assign>               { CODE(BegAInit); }         Initializer                 { MAKE(EndAInit); }      
                         |   
                         ;
DRanges                  
                         :   <Separator,LeftScrape>      Assign                      { YACC(AddToList,10); }     <Separator,RightScrape>     { MAKE(DRange); }           DRanges                  
                         |   
                         ;
DefArrD1A                
                         :   <Syntax,EmptyScrape>        { MAKE(DefArrD1AEmpty); }   { NODE(Ranges,(0),5); }  
                         |   <Separator,LeftScrape>      Assign                      { NODE(Ranges,(1),2); }     <Separator,RightScrape>     { MAKE(DRange); }        
                         ;
DefArrDA                 
                         :   DefArrD1A                   { NODE(None,(1,2)); }       DRanges                     { CODE(EndRanges); }     
                         ;
DefArr                   
                         :   <Syntax,IdentArr>           { MAKE(DefArray); }         DefArrDA                    { NODE(DefArr,(0,0,1)); }   DefAInit                    { NODE(DefArr,(1,2),2); }
                         ;
DefVarAssign             
                         :   <Oper,Assign>               { CODE(BegDefVarAssign); }                           Assign                      { MAKE(DefVarAssign); }  
                         ;
DefVarInit               
                         :   DefVarAssign             
                         |   
                         ;
DefVar                   
                         :   <Ident>                     { MAKE(DefIdent); }         DefVarInit                  { NODE(DefVar,(0,1)); }  
                         ;
DefIAV                   
                         :   DefArr                   
                         |   DefVar                   
                         ;
DefItem                  
                         :   <Priority,And>              DefIAV                      { TREE(RefDef); }           { NODE(RefDef,(1)); }    
                         |   DefIAV                   
                         ;
DefType                  
                         :   <Syntax,DefArr>          
                         |   <Syntax,DefVar>          
                         ;
DefineList               
                         :   <Separator,Comma>           DefItem                     { YACC(AddToList,6); }      { TREE(AddToList); }        DefineList               
                         |   
                         ;
Define                   
                         :   DefType                     { MAKE(Define); }           { NODE(Define,(4)); }       DefItem                     { YACC(AddToList,2); }      { TREE(AddToList); }        DefineList                  { CODE(EndDefine); }     
                         ;
ConditionDef             
                         :   <Priority,And>              DefVar                      { TREE(RefDef); }           { NODE(RefDef,(1)); }    
                         |   DefVar                   
                         ;
Condition                
                         :   <Syntax,DefVar>             { MAKE(Define); }           ConditionDef                { MAKE(PushDef); }          { NODE(None,(1)); }      
                         |   ExpressionCondition      
                         ;
ExprList                 
                         :   <Separator,Comma>           Assign                      { YACC(AddToList,6); }      { TREE(AddToList); }        { CODE(AddToExpr); }        ExprList                 
                         |   
                         ;
Expressions              
                         :   Assign                      { MAKE(ExpressionsLL); }    { NODE(Expressions,(2,3),1); }                       ExprList                    { CODE(ExpressionSLL); } 
                         ;
PriorAssign              
                         :   <Priority,Assign>        
                         ;
AssignList               
                         :   PriorAssign                 { NODE(None,(2),2); }       Assign                      { MAKE(Binary); }           { NODE(Binary,(2,1)); }  
                         |   
                         ;
Assign                   
                         :   Question                    { NODE(None,(1,2)); }       AssignList               
                         ;
QuestionList             
                         :   <Priority,Question>         { CODE(BegQuestion); }      ExpressionValue             { NODE(Trio,(0)); }         <Separator,Colon>           { CODE(MidQuestion); }      Question                    { NODE(Trio,(0),1); }       { MAKE(Question); }      
                         |   
                         ;
Question                 
                         :   OrOr                        { NODE(None,(1,2)); }       QuestionList             
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
                         :   <Priority,IncDec>           { MAKE(IncDec); }           { NODE(Unary,(2),1); }   
                         |   
                         ;
Unary                    
                         :   <Priority,Unary>            Unary                       { MAKE(Unary); }            { NODE(Unary,(1,2)); }   
                         |   <Priority,Term>             Unary                       { MAKE(Unary); }            { NODE(Unary,(1,2),1); } 
                         |   <Priority,IncDec>           Unary                       { MAKE(Unary); }            { NODE(Unary,(1,2)); }   
                         |   <Syntax,CastUnary>          Unary                       { MAKE(Cast); }             { NODE(Cast,(1,2)); }    
                         |   PrimaryExpr                 { NODE(None,(1,2)); }       UnaryIncDec              
                         ;
Primary                  
                         :   <Separator,LeftBracket>     ExpressionNone              { NODE(None,(1)); }         <Separator,RightBracket>    { TREE(Primary); }       
                         ;
PrimaryExpr              
                         :   <Integer>                   { MAKE(Number); }           { NODE(Number,(1)); }    
                         |   <Number>                    { MAKE(Number); }           { NODE(Number,(1)); }    
                         |   <Syntax,IdentArr>           Ranges                      { NODE(Index,(1)); }     
                         |   <Syntax,IdentFunc>          CallParams                  { NODE(Call,(1)); }      
                         |   <Syntax,Cast>               Primary                     { MAKE(Cast); }             { NODE(Cast,(1)); }      
                         |   <Ident>                     { MAKE(Ident); }            { NODE(Var,(1)); }       
                         |   Primary                  
                         ;
RangesList               
                         :   <Separator,LeftScrape>      ExpressionValue             { YACC(AddToList,10); }     <Separator,RightScrape>     { MAKE(IndexLL); }          RangesList               
                         |   
                         ;
Ranges                   
                         :   { MAKE(BegIndexLL); }       { NODE(List,(2,3)); }       RangesList                  { MAKE(EndIndex); }      
                         ;
CallParams               
                         :   <Syntax,EmptyBracket>       { MAKE(Params); }           { NODE(List,(0)); }      
                         |   <Separator,LeftBracket>     ExpressionValueList         { NODE(None,(1)); }         <Separator,RightBracket>    { MAKE(Params,1); }      
                         ;
CompaundStmnt            
                         :   <Syntax,EmptyCramp>         { MAKE(Compaund); }         { CODE(EndBlock); }         { NODE(Null,(1)); }      
                         |   <Separator,LeftCramp>       { MAKE(Compaund); }         StmExpr                     { NODE(None,(1)); }         <Separator,RightCramp>      { CODE(EndBlock); }         { TREE(AddToList); }     
                         ;
IfStmnt_                 
                         :   <Reserv,Else>               { CODE(Else); }             DefExpr                     { MAKE(If,1); }          
                         |   { MAKE(If); }            
                         ;
IfStmnt                  
                         :   <Reserv,If>                 <Separator,LeftBracket>     { CODE(BegIf); }            Condition                   { NODE(If,(1)); }           <Separator,RightBracket>    { CODE(Then); }             DefExpr                     { NODE(If,(1),1); }         IfStmnt_                    { NODE(If,(1),2); }      
                         ;
ForPrefix                
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { NODE(Null,(1)); }      
                         |   DefineSemi               
                         |   ExprSemi                 
                         ;
ForCondition             
                         :   <Separator,Semicolon>       { MAKE(NodeNull); }         { NODE(Null,(1)); }      
                         |   Condition                   { NODE(None,(1)); }         <Separator,Semicolon>    
                         ;
ForPosfix                
                         :   <Separator,RightBracket>    { TREE(NodeNull); }         { NODE(Null,(1)); }      
                         |   ExpressionExpression        { NODE(None,(1)); }         <Separator,RightBracket> 
                         ;
ForStmnt                 
                         :   <Reserv,For>                <Separator,LeftBracket>     { MAKE(BegFor); }           ForPrefix                   { CODE(PrefFor); }          { NODE(For,(1)); }          ForCondition                { CODE(ConditionFor); }     { NODE(For,(1),1); }        ForPosfix                   { CODE(PostFor); }          { NODE(For,(1),2); }        DefExpr                     { NODE(For,(1),3); }        { MAKE(For); }           
                         ;
DoStmnt                  
                         :   <Reserv,Do>                 { MAKE(BegDo); }            DefExpr                     { NODE(None,(1)); }         <Reserv,While>              <Separator,LeftBracket>     { CODE(MidDo); }            Condition                   { NODE(Do,(1,4)); }         <Separator,RightBracket>    <Separator,Semicolon>       { MAKE(Do); }            
                         ;
WhileStmnt               
                         :   <Reserv,While>              { MAKE(BegWhile); }         <Separator,LeftBracket>     Condition                   { NODE(None,(1)); }         <Separator,RightBracket>    { CODE(MidWhile); }         DefExpr                     { MAKE(While); }            { NODE(While,(2,1)); }   
                         ;
GoToStmnt                
                         :   <Reserv,GoTo>               <Ident>                     <Separator,Semicolon>       { NODE(GoTo,(1)); }         { MAKE(GoTo); }          
                         ;
BreakStmnt               
                         :   <Reserv,Break>              <Separator,Semicolon>       { MAKE(Break); }            { NODE(Break,(1)); }     
                         ;
ContinueStmnt            
                         :   <Reserv,Continue>           <Separator,Semicolon>       { MAKE(Continue); }         { NODE(Continue,(1)); }  
                         ;
ReturnVal                
                         :   ExpressionValue             { MAKE(Return,1); }      
                         |   { MAKE(Return); }        
                         ;
ReturnStmnt              
                         :   <Reserv,Return>             ReturnVal                   { NODE(Return,(1)); }       <Separator,Semicolon>    
                         ;
Statement                
                         :   <Syntax,Label>              <Separator,Colon>           { CODE(Label); }            DefExpr                     { NODE(Label,(1)); }        { TREE(Label); }         
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
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { NODE(Null,(1)); }      
                         |   DefineSemi               
                         |   Statement                
                         |   ExprSemi                 
                         ;
StmExprList              
                         :   DefExpr                     { YACC(AddToList,6); }      { TREE(AddToList); }        StmExprList              
                         |   
                         ;
StmExpr                  
                         :   { MAKE(BegStmExprLL); }     { NODE(Statements,(2,3)); }                          StmExprList                 { CODE(EndBlock); }      
                         ;
DefFAV                   
                         :   <Separator,Semicolon>       { TREE(NodeNull); }         { NODE(Null,(1)); }      
                         |   DefFunc                  
                         |   DefineSemi               
                         ;
DefinesList              
                         :   DefFAV                      { YACC(AddToList,6); }      { TREE(AddToList); }        DefinesList              
                         |   
                         ;
Defines                  
                         :   { MAKE(BegStmExprLL); }     { NODE(Statements,(2,3)); }                          DefinesList                 { CODE(EndBlock); }      
                         ;
ExpressionExpression     
                         :   { CODE(Part,16); }          Expressions                 { TREE(ExpressionSLL,16); }                          { YACC(ExpressionSLL,16); }                       
                         ;
ExpressionCondition      
                         :   { CODE(Part,241); }         Expressions                 { TREE(ExpressionSLL,241); }                         { YACC(ExpressionSLL,241); }                      
                         ;
ExpressionNone           
                         :   { CODE(Part); }             Expressions                 { TREE(ExpressionSLL); }    { YACC(ExpressionSLL); } 
                         ;
ExpressionValue          
                         :   { CODE(Part,256); }         Expressions                 { TREE(ExpressionSLL,256); }                         { YACC(ExpressionSLL,256); }                      
                         ;
ExpressionValueList      
                         :   { CODE(Part,512); }         Expressions                 { TREE(ExpressionSLL,512); }                         { YACC(ExpressionSLL,512); }                      
                         ;
