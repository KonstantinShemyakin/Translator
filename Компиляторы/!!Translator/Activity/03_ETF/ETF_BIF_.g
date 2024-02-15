
S_                       
                         ::= Assign                   
                         
Assign                   
                         ::= Question                    
                             [ 
                             Priority_Assign             Assign                   
                             ] 
                         
Question                 
                         ::= AndAnd                      
                         [
                         Priority_OrOr               AndAnd                   
                         
                         ]... 
                            
                             [ 
                             Priority_Question           Assign                      :                           Question                 
                             ] 
                         
AndAnd                   
                         ::= Or                          
                         [
                         Priority_AndAnd             Or                       
                         
                         ]... 
                         
Or                       
                         ::= E                        
                         
E                        
                         ::= T                           
                         [
                         Priority_Term               T                        
                         
                         ]... 
                         
T                        
                         ::= F                           
                         [
                         Priority_Factor             F                        
                         
                         ]... 
                         
F                        
                         ::= { 
                             (                           E                           )                        
                         |   Ident                    
                         |   Integer                  
                         |   Number                   
                             } 
