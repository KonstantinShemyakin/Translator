//S_: S; 
S : B A
  ;
A : '+' B A
  |
  ;
B : D C
  ;
C : '*' D C
  |
  ;
D : '(' S ')'
  | <Ident>
  ;
