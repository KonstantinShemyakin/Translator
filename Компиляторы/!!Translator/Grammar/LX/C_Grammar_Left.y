
S_                       
                         :   translation_unit         
                         ;
primary_expression       
                         :   <Ident>                  
                         |   <Integer>                
                         |   <String>                 
                         |   <Separator,LeftBracket>     expression                  <Separator,RightBracket> 
                         ;
postfix_expression       
                         :   primary_expression          _f_00064_                
                         ;
argument_expression_list 
                         :   assignment_expression       _f_00065_                
                         ;
unary_expression         
                         :   primary_expression          _f_00064_                
                         |   <Oper,PlusPlus>             unary_expression         
                         |   <Oper,MinusMinus>           unary_expression         
                         |   unary_operator              cast_expression          
                         |   <Reserv,Sizeof>             _f_00090_                
                         ;
unary_operator           
                         :   <Oper,And>               
                         |   <Oper,Multi>             
                         |   <Oper,Add>               
                         |   <Oper,Sub>               
                         |   <Oper,Tilda>             
                         |   <Oper,Not>               
                         ;
cast_expression          
                         :   primary_expression          _f_00064_                
                         |   <Oper,PlusPlus>             unary_expression         
                         |   <Oper,MinusMinus>           unary_expression         
                         |   unary_operator              cast_expression          
                         |   <Reserv,Sizeof>             _f_00090_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression          
                         ;
multiplicative_expression
                         :   primary_expression          _f_00064_                   _f_00066_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                
                         |   unary_operator              cast_expression             _f_00066_                
                         |   <Reserv,Sizeof>             _f_00091_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                
                         ;
additive_expression      
                         :   primary_expression          _f_00064_                   _f_00066_                   _f_00067_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                   _f_00067_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                   _f_00067_                
                         |   unary_operator              cast_expression             _f_00066_                   _f_00067_                
                         |   <Reserv,Sizeof>             _f_00092_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                
                         ;
shift_expression         
                         :   primary_expression          _f_00064_                   _f_00066_                   _f_00067_                   _f_00068_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                   _f_00067_                   _f_00068_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                   _f_00067_                   _f_00068_                
                         |   unary_operator              cast_expression             _f_00066_                   _f_00067_                   _f_00068_                
                         |   <Reserv,Sizeof>             _f_00093_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                
                         ;
relational_expression    
                         :   primary_expression          _f_00064_                   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                
                         |   unary_operator              cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                
                         |   <Reserv,Sizeof>             _f_00094_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                
                         ;
equality_expression      
                         :   primary_expression          _f_00064_                   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                
                         |   unary_operator              cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                
                         |   <Reserv,Sizeof>             _f_00095_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                
                         ;
and_expression           
                         :   primary_expression          _f_00064_                   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                
                         |   unary_operator              cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                
                         |   <Reserv,Sizeof>             _f_00096_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                
                         ;
exclusive_or_expression  
                         :   primary_expression          _f_00064_                   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                
                         |   unary_operator              cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                
                         |   <Reserv,Sizeof>             _f_00097_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                
                         ;
inclusive_or_expression  
                         :   primary_expression          _f_00064_                   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                
                         |   unary_operator              cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                
                         |   <Reserv,Sizeof>             _f_00098_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                
                         ;
logical_and_expression   
                         :   primary_expression          _f_00064_                   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                
                         |   unary_operator              cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                
                         |   <Reserv,Sizeof>             _f_00099_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                
                         ;
logical_or_expression    
                         :   primary_expression          _f_00064_                   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                
                         |   unary_operator              cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                
                         |   <Reserv,Sizeof>             _f_00100_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                
                         ;
conditional_expression   
                         :   primary_expression          _f_00064_                   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         |   unary_operator              cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         |   <Reserv,Sizeof>             _f_00102_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         ;
assignment_expression    
                         :   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         |   primary_expression          _f_00064_                   _f_00103_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00103_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00103_                
                         |   unary_operator              cast_expression             _f_00103_                
                         |   <Reserv,Sizeof>             _f_00104_                
                         ;
assignment_operator      
                         :   <Oper,Assign>            
                         |   <Oper,MultiAssign>       
                         |   <Oper,DivAssign>         
                         |   <Oper,ModAssign>         
                         |   <Oper,AddAssign>         
                         |   <Oper,SubAssign>         
                         |   <Oper,LShiftAssign>      
                         |   <Oper,RShiftAssign>      
                         |   <Oper,AndAssign>         
                         |   <Oper,XOrAssign>         
                         |   <Oper,OrAssign>          
                         ;
expression               
                         :   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00105_                
                         |   primary_expression          _f_00064_                   _f_00106_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00106_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00106_                
                         |   unary_operator              cast_expression             _f_00106_                
                         |   <Reserv,Sizeof>             _f_00107_                
                         ;
constant_expression      
                         :   primary_expression          _f_00064_                   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         |   unary_operator              cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         |   <Reserv,Sizeof>             _f_00102_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         ;
declaration              
                         :   declaration_specifiers      _f_00108_                
                         ;
declaration_specifiers   
                         :   storage_class_specifier     _f_00109_                
                         |   type_specifier              _f_00109_                
                         |   type_qualifier              _f_00109_                
                         ;
init_declarator_list     
                         :   init_declarator             _f_00077_                
                         ;
init_declarator          
                         :   declarator                  _f_00110_                
                         ;
storage_class_specifier  
                         :   { TREE(LexTypeName,2); }    <Reserv,Typedef>         
                         |   <Reserv,Extern>          
                         |   <Reserv,Static>          
                         |   <Reserv,Auto>            
                         |   <Reserv,Register>        
                         ;
type_specifier           
                         :   <Reserv,Void>            
                         |   <Reserv,Char>            
                         |   <Reserv,Short>           
                         |   <Reserv,Int>             
                         |   <Reserv,Long>            
                         |   <Reserv,Float>           
                         |   <Reserv,Double>          
                         |   <Reserv,Signed>          
                         |   <Reserv,Unsigned>        
                         |   struct_or_union_specifier
                         |   enum_specifier           
                         |   <Ident,1>                
                         ;
struct_or_union_specifier
                         :   struct_or_union             _f_00112_                
                         ;
struct_or_union          
                         :   <Reserv,Struct>          
                         |   <Reserv,Union>           
                         ;
struct_declaration_list  
                         :   struct_declaration          _f_00078_                
                         ;
struct_declaration       
                         :   specifier_qualifier_list    struct_declarator_list      <Separator,Semicolon>    
                         ;
specifier_qualifier_list 
                         :   type_specifier              _f_00113_                
                         |   type_qualifier              _f_00113_                
                         ;
struct_declarator_list   
                         :   struct_declarator           _f_00079_                
                         ;
struct_declarator        
                         :   declarator                  _f_00114_                
                         |   <Separator,Colon>           constant_expression      
                         ;
enum_specifier           
                         :   <Reserv,Enum>               _f_00116_                
                         ;
enumerator_list          
                         :   enumerator                  _f_00080_                
                         ;
enumerator               
                         :   <Ident,3>                   _f_00117_                
                         ;
type_qualifier           
                         :   <Reserv,Const>           
                         |   <Reserv,Volatile>        
                         ;
declarator               
                         :   pointer                     direct_declarator        
                         |   direct_declarator        
                         ;
direct_declarator        
                         :   <Ident,2>                   _f_00081_                
                         |   <Separator,LeftBracket>     declarator                  <Separator,RightBracket>    _f_00081_                
                         ;
pointer                  
                         :   <Oper,Multi>                _f_00119_                
                         ;
type_qualifier_list      
                         :   type_qualifier              _f_00082_                
                         ;
parameter_type_list      
                         :   parameter_list              _f_00120_                
                         ;
parameter_list           
                         :   parameter_declaration       _f_00083_                
                         ;
parameter_declaration    
                         :   { TREE(LexTypeName,2); }    <Reserv,Typedef>            _f_00122_                
                         |   <Reserv,Extern>             _f_00122_                
                         |   <Reserv,Static>             _f_00122_                
                         |   <Reserv,Auto>               _f_00122_                
                         |   <Reserv,Register>           _f_00122_                
                         |   type_specifier              _f_00122_                
                         |   type_qualifier              _f_00122_                
                         ;
identifier_list          
                         :   <Ident>                     _f_00084_                
                         ;
type_name                
                         :   specifier_qualifier_list    _f_00123_                
                         ;
abstract_declarator      
                         :   pointer                     _f_00124_                
                         |   direct_abstract_declarator                        
                         ;
direct_abstract_declarator
                         :   <Separator,LeftBracket>     _f_00125_                
                         |   <Separator,LeftScrape>      _f_00126_                
                         ;
initializer              
                         :   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         |   primary_expression          _f_00064_                   _f_00103_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00103_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00103_                
                         |   unary_operator              cast_expression             _f_00103_                
                         |   <Reserv,Sizeof>             _f_00104_                
                         |   <Separator,LeftCramp>       initializer_list            _f_00127_                
                         ;
initializer_list         
                         :   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00128_                
                         |   primary_expression          _f_00064_                   _f_00129_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00129_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00129_                
                         |   unary_operator              cast_expression             _f_00129_                
                         |   <Reserv,Sizeof>             _f_00131_                
                         |   <Separator,LeftCramp>       initializer_list            _f_00130_                
                         ;
statement                
                         :   labeled_statement        
                         |   compound_statement       
                         |   expression_statement     
                         |   selection_statement      
                         |   iteration_statement      
                         |   jump_statement           
                         ;
labeled_statement        
                         :   <Ident>                     <Separator,Colon>           statement                
                         |   <Reserv,Case>               constant_expression         <Separator,Colon>           statement                
                         |   <Reserv,Default>            <Separator,Colon>           statement                
                         ;
compound_statement       
                         :   { TREE(LexTypeName,9); }    <Separator,LeftCramp>       _f_00133_                
                         ;
declaration_list         
                         :   { TREE(LexTypeName,2); }    <Reserv,Typedef>            _f_00135_                
                         |   <Reserv,Extern>             _f_00135_                
                         |   <Reserv,Static>             _f_00135_                
                         |   <Reserv,Auto>               _f_00135_                
                         |   <Reserv,Register>           _f_00135_                
                         |   type_specifier              _f_00135_                
                         |   type_qualifier              _f_00135_                
                         ;
statement_list           
                         :   labeled_statement           _f_00088_                
                         |   { TREE(LexTypeName,9); }    <Separator,LeftCramp>       _f_00137_                
                         |   expression_statement        _f_00088_                
                         |   selection_statement         _f_00088_                
                         |   iteration_statement         _f_00088_                
                         |   jump_statement              _f_00088_                
                         ;
expression_statement     
                         :   <Separator,Semicolon>    
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00138_                
                         |   primary_expression          _f_00064_                   _f_00139_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00139_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00139_                
                         |   unary_operator              cast_expression             _f_00139_                
                         |   <Reserv,Sizeof>             _f_00140_                
                         ;
selection_statement      
                         :   <Reserv,If>                 <Separator,LeftBracket>     expression                  <Separator,RightBracket>    statement                   _f_00141_                
                         |   <Reserv,Switch>             <Separator,LeftBracket>     expression                  <Separator,RightBracket>    statement                
                         ;
iteration_statement      
                         :   <Reserv,While>              <Separator,LeftBracket>     expression                  <Separator,RightBracket>    statement                
                         |   <Reserv,Do>                 statement                   <Reserv,While>              <Separator,LeftBracket>     expression                  <Separator,RightBracket>    <Separator,Semicolon>    
                         |   <Reserv,For>                <Separator,LeftBracket>     expression_statement        expression_statement        _f_00142_                
                         ;
jump_statement           
                         :   <Reserv,GoTo>               <Ident>                     <Separator,Semicolon>    
                         |   <Reserv,Continue>           <Separator,Semicolon>    
                         |   <Reserv,Break>              <Separator,Semicolon>    
                         |   <Reserv,Return>             _f_00143_                
                         ;
translation_unit         
                         :   external_declaration        _f_00089_                
                         ;
external_declaration     
                         :   function_definition      
                         |   { TREE(LexTypeName,2); }    <Reserv,Typedef>            _f_00144_                
                         |   <Reserv,Extern>             _f_00144_                
                         |   <Reserv,Static>             _f_00144_                
                         |   <Reserv,Auto>               _f_00144_                
                         |   <Reserv,Register>           _f_00144_                
                         |   type_specifier              _f_00144_                
                         |   type_qualifier              _f_00144_                
                         ;
function_definition      
                         :   { TREE(LexTypeName,2); }    <Reserv,Typedef>            _f_00146_                
                         |   <Reserv,Extern>             _f_00146_                
                         |   <Reserv,Static>             _f_00146_                
                         |   <Reserv,Auto>               _f_00146_                
                         |   <Reserv,Register>           _f_00146_                
                         |   type_specifier              _f_00146_                
                         |   type_qualifier              _f_00146_                
                         |   pointer                     direct_declarator           { TREE(LexTypeName,11); }   _f_00145_                
                         |   <Ident,2>                   _f_00081_                   { TREE(LexTypeName,11); }   _f_00145_                
                         |   <Separator,LeftBracket>     declarator                  <Separator,RightBracket>    _f_00081_                   { TREE(LexTypeName,11); }   _f_00145_                
                         ;
_f_00064_                
                         :   <Separator,LeftScrape>      expression                  <Separator,RightScrape>     _f_00064_                
                         |   <Separator,LeftBracket>     _f_00147_                
                         |   <Separator,Point>           <Ident>                     _f_00064_                
                         |   <Separator,Pointer>         <Ident>                     _f_00064_                
                         |   <Oper,PlusPlus>             _f_00064_                
                         |   <Oper,MinusMinus>           _f_00064_                
                         |   
                         ;
_f_00065_                
                         :   <Separator,Comma>           assignment_expression       _f_00065_                
                         |   
                         ;
_f_00066_                
                         :   <Oper,Multi>                cast_expression             _f_00066_                
                         |   <Oper,Div>                  cast_expression             _f_00066_                
                         |   <Oper,Mod>                  cast_expression             _f_00066_                
                         |   
                         ;
_f_00067_                
                         :   <Oper,Add>                  multiplicative_expression   _f_00067_                
                         |   <Oper,Sub>                  multiplicative_expression   _f_00067_                
                         |   
                         ;
_f_00068_                
                         :   <Oper,LShift>               additive_expression         _f_00068_                
                         |   <Oper,RShift>               additive_expression         _f_00068_                
                         |   
                         ;
_f_00069_                
                         :   <Oper,LT>                   shift_expression            _f_00069_                
                         |   <Oper,GT>                   shift_expression            _f_00069_                
                         |   <Oper,LE>                   shift_expression            _f_00069_                
                         |   <Oper,GE>                   shift_expression            _f_00069_                
                         |   
                         ;
_f_00070_                
                         :   <Oper,Equ>                  relational_expression       _f_00070_                
                         |   <Oper,NotEqu>               relational_expression       _f_00070_                
                         |   
                         ;
_f_00071_                
                         :   <Oper,And>                  equality_expression         _f_00071_                
                         |   
                         ;
_f_00072_                
                         :   <Oper,XOr>                  and_expression              _f_00072_                
                         |   
                         ;
_f_00073_                
                         :   <Oper,Or>                   exclusive_or_expression     _f_00073_                
                         |   
                         ;
_f_00074_                
                         :   <Oper,AndAnd>               inclusive_or_expression     _f_00074_                
                         |   
                         ;
_f_00075_                
                         :   <Oper,OrOr>                 logical_and_expression      _f_00075_                
                         |   
                         ;
_f_00076_                
                         :   <Separator,Comma>           assignment_expression       _f_00076_                
                         |   
                         ;
_f_00077_                
                         :   { TREE(LexTypeName,5); }    <Separator,Comma>           init_declarator             _f_00077_                
                         |   
                         ;
_f_00078_                
                         :   struct_declaration          _f_00078_                
                         |   
                         ;
_f_00079_                
                         :   <Separator,Comma>           struct_declarator           _f_00079_                
                         |   
                         ;
_f_00080_                
                         :   <Separator,Comma>           enumerator                  _f_00080_                
                         |   
                         ;
_f_00081_                
                         :   <Separator,LeftScrape>      _f_00149_                
                         |   { TREE(LexTypeName,18); }   <Separator,LeftBracket>     _f_00148_                
                         |   
                         ;
_f_00082_                
                         :   type_qualifier              _f_00082_                
                         |   
                         ;
_f_00083_                
                         :   <Separator,Comma>           parameter_declaration       _f_00083_                
                         |   
                         ;
_f_00084_                
                         :   <Separator,Comma>           <Ident>                     _f_00084_                
                         |   
                         ;
_f_00085_                
                         :   <Separator,LeftScrape>      _f_00126_                
                         |   <Separator,LeftBracket>     _f_00150_                
                         |   
                         ;
_f_00086_                
                         :   <Separator,Comma>           initializer                 _f_00086_                
                         |   
                         ;
_f_00087_                
                         :   { TREE(LexTypeName,2); }    <Reserv,Typedef>            _f_00135_                
                         |   <Reserv,Extern>             _f_00135_                
                         |   <Reserv,Static>             _f_00135_                
                         |   <Reserv,Auto>               _f_00135_                
                         |   <Reserv,Register>           _f_00135_                
                         |   type_specifier              _f_00135_                
                         |   type_qualifier              _f_00135_                
                         |   
                         ;
_f_00088_                
                         :   labeled_statement           _f_00088_                
                         |   { TREE(LexTypeName,9); }    <Separator,LeftCramp>       _f_00137_                
                         |   <Separator,Semicolon>       _f_00088_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    cast_expression             _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00151_                
                         |   primary_expression          _f_00064_                   _f_00152_                
                         |   <Oper,PlusPlus>             unary_expression            _f_00152_                
                         |   <Oper,MinusMinus>           unary_expression            _f_00152_                
                         |   unary_operator              cast_expression             _f_00152_                
                         |   <Reserv,Sizeof>             _f_00153_                
                         |   selection_statement         _f_00088_                
                         |   iteration_statement         _f_00088_                
                         |   jump_statement              _f_00088_                
                         |   
                         ;
_f_00089_                
                         :   pointer                     direct_declarator           { TREE(LexTypeName,11); }   _f_00154_                
                         |   <Ident,2>                   _f_00081_                   { TREE(LexTypeName,11); }   _f_00154_                
                         |   <Separator,LeftBracket>     declarator                  <Separator,RightBracket>    _f_00081_                   { TREE(LexTypeName,11); }   _f_00154_                
                         |   { TREE(LexTypeName,2); }    <Reserv,Typedef>            _f_00156_                
                         |   <Reserv,Extern>             _f_00156_                
                         |   <Reserv,Static>             _f_00156_                
                         |   <Reserv,Auto>               _f_00156_                
                         |   <Reserv,Register>           _f_00156_                
                         |   type_specifier              _f_00156_                
                         |   type_qualifier              _f_00156_                
                         |   
                         ;
_f_00090_                
                         :   unary_expression         
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket> 
                         ;
_f_00091_                
                         :   unary_expression            _f_00066_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00066_                
                         ;
_f_00092_                
                         :   unary_expression            _f_00066_                   _f_00067_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00066_                   _f_00067_                
                         ;
_f_00093_                
                         :   unary_expression            _f_00066_                   _f_00067_                   _f_00068_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00066_                   _f_00067_                   _f_00068_                
                         ;
_f_00094_                
                         :   unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                
                         ;
_f_00095_                
                         :   unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                
                         ;
_f_00096_                
                         :   unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                
                         ;
_f_00097_                
                         :   unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                
                         ;
_f_00098_                
                         :   unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                
                         ;
_f_00099_                
                         :   unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                
                         ;
_f_00100_                
                         :   unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                
                         ;
_f_00101_                
                         :   
                         |   <Oper,Question>             expression                  <Separator,Colon>           conditional_expression   
                         ;
_f_00102_                
                         :   unary_expression            _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         ;
_f_00103_                
                         :   assignment_operator         assignment_expression    
                         |   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00101_                
                         ;
_f_00104_                
                         :   unary_expression            _f_00103_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00103_                
                         ;
_f_00105_                
                         :   _f_00076_                
                         |   <Oper,Question>             expression                  <Separator,Colon>           conditional_expression      _f_00076_                
                         ;
_f_00106_                
                         :   assignment_operator         assignment_expression       _f_00076_                
                         |   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00105_                
                         ;
_f_00107_                
                         :   unary_expression            _f_00106_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00106_                
                         ;
_f_00108_                
                         :   init_declarator_list        { TREE(LexTypeName,6); }    <Separator,Semicolon>    
                         |   { TREE(LexTypeName,6); }    <Separator,Semicolon>    
                         ;
_f_00109_                
                         :   
                         |   declaration_specifiers   
                         ;
_f_00110_                
                         :   
                         |   <Oper,Assign>               initializer              
                         ;
_f_00111_                
                         :   
                         |   { TREE(LexTypeName,13); }   <Separator,LeftCramp>       struct_declaration_list     { TREE(LexTypeName,14); }   <Separator,RightCramp>   
                         ;
_f_00112_                
                         :   <Ident>                     _f_00111_                
                         |   { TREE(LexTypeName,13); }   <Separator,LeftCramp>       struct_declaration_list     { TREE(LexTypeName,14); }   <Separator,RightCramp>   
                         ;
_f_00113_                
                         :   
                         |   specifier_qualifier_list 
                         ;
_f_00114_                
                         :   
                         |   <Separator,Colon>           constant_expression      
                         ;
_f_00115_                
                         :   
                         |   { TREE(LexTypeName,15); }   <Separator,LeftCramp>       enumerator_list             { TREE(LexTypeName,16); }   <Separator,RightCramp>   
                         ;
_f_00116_                
                         :   <Ident>                     _f_00115_                
                         |   { TREE(LexTypeName,15); }   <Separator,LeftCramp>       enumerator_list             { TREE(LexTypeName,16); }   <Separator,RightCramp>   
                         ;
_f_00117_                
                         :   
                         |   <Oper,Assign>               constant_expression      
                         ;
_f_00118_                
                         :   
                         |   pointer                  
                         ;
_f_00119_                
                         :   
                         |   pointer                  
                         |   type_qualifier_list         _f_00118_                
                         ;
_f_00120_                
                         :   
                         |   <Separator,Comma>           <Separator,Ellipsis>     
                         ;
_f_00121_                
                         :   
                         |   declarator               
                         |   abstract_declarator      
                         ;
_f_00122_                
                         :   
                         |   declaration_specifiers      _f_00121_                
                         |   declarator               
                         |   abstract_declarator      
                         ;
_f_00123_                
                         :   
                         |   abstract_declarator      
                         ;
_f_00124_                
                         :   
                         |   direct_abstract_declarator                        
                         ;
_f_00125_                
                         :   abstract_declarator         <Separator,RightBracket>    _f_00085_                
                         |   <Separator,RightBracket>    _f_00085_                
                         |   { TREE(LexTypeName,18); }   parameter_type_list         { TREE(LexTypeName,19); }   <Separator,RightBracket>    _f_00085_                
                         ;
_f_00126_                
                         :   constant_expression         <Separator,RightScrape>     _f_00085_                
                         |   <Separator,RightScrape>     _f_00085_                
                         ;
_f_00127_                
                         :   <Separator,RightCramp>   
                         |   <Separator,Comma>           <Separator,RightCramp>   
                         ;
_f_00128_                
                         :   _f_00086_                
                         |   <Oper,Question>             expression                  <Separator,Colon>           conditional_expression      _f_00086_                
                         ;
_f_00129_                
                         :   assignment_operator         assignment_expression       _f_00086_                
                         |   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00128_                
                         ;
_f_00130_                
                         :   <Separator,RightCramp>      _f_00086_                
                         |   <Separator,Comma>           <Separator,RightCramp>      _f_00086_                
                         ;
_f_00131_                
                         :   unary_expression            _f_00129_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00129_                
                         ;
_f_00132_                
                         :   statement_list              { TREE(LexTypeName,10); }   <Separator,RightCramp>   
                         |   { TREE(LexTypeName,10); }   <Separator,RightCramp>   
                         ;
_f_00133_                
                         :   declaration_list            _f_00132_                
                         |   statement_list              { TREE(LexTypeName,10); }   <Separator,RightCramp>   
                         |   { TREE(LexTypeName,10); }   <Separator,RightCramp>   
                         ;
_f_00134_                
                         :   init_declarator_list        { TREE(LexTypeName,6); }    <Separator,Semicolon>       _f_00087_                
                         |   { TREE(LexTypeName,6); }    <Separator,Semicolon>       _f_00087_                
                         ;
_f_00135_                
                         :   declaration_specifiers      _f_00134_                
                         |   init_declarator_list        { TREE(LexTypeName,6); }    <Separator,Semicolon>       _f_00087_                
                         |   { TREE(LexTypeName,6); }    <Separator,Semicolon>       _f_00087_                
                         ;
_f_00136_                
                         :   statement_list              { TREE(LexTypeName,10); }   <Separator,RightCramp>      _f_00088_                
                         |   { TREE(LexTypeName,10); }   <Separator,RightCramp>      _f_00088_                
                         ;
_f_00137_                
                         :   declaration_list            _f_00136_                
                         |   statement_list              { TREE(LexTypeName,10); }   <Separator,RightCramp>      _f_00088_                
                         |   { TREE(LexTypeName,10); }   <Separator,RightCramp>      _f_00088_                
                         ;
_f_00138_                
                         :   _f_00076_                   <Separator,Semicolon>    
                         |   <Oper,Question>             expression                  <Separator,Colon>           conditional_expression      _f_00076_                   <Separator,Semicolon>    
                         ;
_f_00139_                
                         :   assignment_operator         assignment_expression       _f_00076_                   <Separator,Semicolon>    
                         |   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00138_                
                         ;
_f_00140_                
                         :   unary_expression            _f_00139_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00139_                
                         ;
_f_00141_                
                         :   
                         |   <Reserv,Else>               statement                
                         ;
_f_00142_                
                         :   expression                  <Separator,RightBracket>    statement                
                         |   <Separator,RightBracket>    statement                
                         ;
_f_00143_                
                         :   expression                  <Separator,Semicolon>    
                         |   <Separator,Semicolon>    
                         ;
_f_00144_                
                         :   declaration_specifiers      _f_00108_                
                         |   init_declarator_list        { TREE(LexTypeName,6); }    <Separator,Semicolon>    
                         |   { TREE(LexTypeName,6); }    <Separator,Semicolon>    
                         ;
_f_00145_                
                         :   compound_statement          { TREE(LexTypeName,12); }
                         |   declaration_list            compound_statement          { TREE(LexTypeName,12); }
                         ;
_f_00146_                
                         :   declaration_specifiers      declarator                  { TREE(LexTypeName,11); }   _f_00145_                
                         |   declarator                  { TREE(LexTypeName,11); }   _f_00145_                
                         ;
_f_00147_                
                         :   argument_expression_list    <Separator,RightBracket>    _f_00064_                
                         |   <Separator,RightBracket>    _f_00064_                
                         ;
_f_00148_                
                         :   parameter_type_list         { TREE(LexTypeName,19); }   <Separator,RightBracket>    _f_00081_                
                         |   identifier_list             { TREE(LexTypeName,19); }   <Separator,RightBracket>    _f_00081_                
                         |   { TREE(LexTypeName,19); }   <Separator,RightBracket>    _f_00081_                
                         ;
_f_00149_                
                         :   constant_expression         <Separator,RightScrape>     _f_00081_                
                         |   <Separator,RightScrape>     _f_00081_                
                         ;
_f_00150_                
                         :   <Separator,RightBracket>    _f_00085_                
                         |   { TREE(LexTypeName,18); }   parameter_type_list         { TREE(LexTypeName,19); }   <Separator,RightBracket>    _f_00085_                
                         ;
_f_00151_                
                         :   _f_00076_                   <Separator,Semicolon>       _f_00088_                
                         |   <Oper,Question>             expression                  <Separator,Colon>           conditional_expression      _f_00076_                   <Separator,Semicolon>       _f_00088_                
                         ;
_f_00152_                
                         :   assignment_operator         assignment_expression       _f_00076_                   <Separator,Semicolon>       _f_00088_                
                         |   _f_00066_                   _f_00067_                   _f_00068_                   _f_00069_                   _f_00070_                   _f_00071_                   _f_00072_                   _f_00073_                   _f_00074_                   _f_00075_                   _f_00151_                
                         ;
_f_00153_                
                         :   unary_expression            _f_00152_                
                         |   <Separator,LeftBracket>     type_name                   <Separator,RightBracket>    _f_00152_                
                         ;
_f_00154_                
                         :   compound_statement          { TREE(LexTypeName,12); }   _f_00089_                
                         |   declaration_list            compound_statement          { TREE(LexTypeName,12); }   _f_00089_                
                         ;
_f_00155_                
                         :   init_declarator_list        { TREE(LexTypeName,6); }    <Separator,Semicolon>       _f_00089_                
                         |   declarator                  { TREE(LexTypeName,11); }   _f_00154_                
                         |   { TREE(LexTypeName,6); }    <Separator,Semicolon>       _f_00089_                
                         ;
_f_00156_                
                         :   declaration_specifiers      _f_00155_                
                         |   init_declarator_list        { TREE(LexTypeName,6); }    <Separator,Semicolon>       _f_00089_                
                         |   declarator                  { TREE(LexTypeName,11); }   _f_00154_                
                         |   { TREE(LexTypeName,6); }    <Separator,Semicolon>       _f_00089_                
                         ;
