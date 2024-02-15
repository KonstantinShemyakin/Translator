S_                       
                         : DefExpr_List                        
                         ;

DefExpr_List             
                         : DefExpr_List                  DefExpr
                         | DefExpr
                         ;

DefExpr                  
                         : expression_statement
                         | declaration
                         | ';'
                         ;

declaration              
                         : <Reserv,Int>                 <Ident>                    ';'
                         ;

expression_statement     
                         : expression ';'
//                         | ';'
                         ;
expression               
                         : assign
                         ;
 
assign                   
                         : E '=' assign
                         | E
                         ;

E                        
                         : E                           <Priority,Term>             T                        
                         | T                        
                         ;

T                        
                         : T                           <Priority,Factor>           F                        
                         | F                        
                         ;

F                        
                         : '('                         E                           ')'
                         | <Ident>                 
                         | <Integer>                
                         | <Number>                 
                         ;
