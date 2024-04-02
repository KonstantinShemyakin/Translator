Z        :     E
         ;                        

E        :     E     '+'     T  
         |     E     '-'     T
         |     T
         ;

T        :     T     '*'     F                       
         |     T     '/'     F
         |     F
         ;

F        :    '('     E     ')'     |  <Integer>  |  <Number>  |  <Ident>  
         ;