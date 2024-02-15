S_                       
                         :  E                        
                         ;
E                        
                         :   E              '+'             T                        
                         |   E              '-'             T                        
                         |   T                        
                         ;
T                        
                         :   T              '*'             F                        
                         |   T              '/'             F                        
                         |   F                        
                         ;
F                        
                         :  '('             E            ')'
                         |   <Integer>
#define IDENT
#ifndef 12345 IDENT
                         |   <Number>
#else
                         |   <Ident>
#endif
                         ;
