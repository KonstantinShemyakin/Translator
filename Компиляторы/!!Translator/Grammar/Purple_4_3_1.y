rexpr: 
         rexpr '|' rterm 
       | rterm
       ;
rterm:
         rterm rfactor 
       | rfactor
       ;
rfactor:
         rfactor '*' 
       | rprimary
       ;
rprimary:
         <Ineger> 
       | <Number>
       ;

