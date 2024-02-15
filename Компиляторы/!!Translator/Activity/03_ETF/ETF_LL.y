S_                       
                         : E                        
                         ;
E                        
                         : T                           E_                       
                         ;
E_                       
                         : <Priority,Term>             T                           E_                       
                         | 
                         ;
T                        
                         : F                           T_                       
                         ;
T_                       
                         : <Priority,Factor>           F                           T_                       
                         | 
                         ;
F                        
                         : <Separator,LeftBracket>     E                           <Separator,RightBracket> 
                         | <Integer>                
                         | <Number>                
                         ;
