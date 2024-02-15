S_
                         : Program                        
                         ;
Program             
                         : DefExpr_List               // ';'
//                         | Empty
                         ;
DefExpr_List_            
                         : ';'                         DefExpr_List
                         | Empty                    
                         ;
DefExpr_List             
                         : DefExpr                     DefExpr_List_            
                         ;
DefExpr                  
                         : expression_statement
                         | declaration
                         | Empty                         
                         ;

declaration              
                         : <Reserv,Int>                <Ident>
                         ;

expression_statement     
                         : expression
                         ;
expression               
                         : Assign
                         ;
AssignList               
                         : <Priority,Assign>           Assign
                         | Empty                    
                         ;
Assign                   
                         : E                           AssignList               
                         ;
E                        
                         : T                           E_                       
                         ;
E_                       
                         : <Priority,Term>             T                           E_                       
                         | Empty                    
                         ;
T                        
                         : F                           T_                       
                         ;
T_                       
                         : <Priority,Factor>           F                           T_                       
                         | Empty                    
                         ;
F                        
                         : '('                         E                           ')'
                         | <Ident>                 
                         | <Integer>                
                         | <Number>                 
                         ;
