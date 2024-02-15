S_                       
                         : E                        
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
                         : <Separator,LeftBracket>     E                           <Separator,RightBracket> 
                         | <Integer>                
                         | <Number>                 
                         ;
