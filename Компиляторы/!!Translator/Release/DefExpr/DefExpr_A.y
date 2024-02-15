S_                       
                         : assign
                         ;

assign
                         : assign                      <Priority,Assign>           assign                        
                         | E                        
                         ;

E                        
                         : E                           <Priority,Term>             E                        
                         | E                           <Priority,Factor>           E                        
                         | '('                         E                           ')'
                         | <Ident>                 
                         | <Integer>                
                         | <Number>                 
                         ;
