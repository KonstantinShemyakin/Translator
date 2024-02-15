S_
                         : E                        
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
