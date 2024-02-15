TableBuilder 014 00391000 ..\Table\LL_TC_PROG.tab 
TableBuilder 01E 00391000 ..\Table\LL_TC_YACC.y  
TableBuilder 114 003910FF ..\Table\NL_TC_PROG.tab 
TableBuilder 21E 00391000 ..\Table\LR_TC_YACC.y  
TableBuilder 32E 00391000 ..\Table\NR_TC_YACC.y  
TableBuilder 33E 00391000 ..\Table\NR_SN_YACC.y
  
TranYACC.exe 014 0830 text.cpp
move text.code ..\Code\LL_Tree_PROG.code
move text.tree ..\Code\LL_Tree_PROG.tree
TranYACC.exe 024 0820 text.cpp
move text.code ..\Code\LL_Code_PROG.code

TranYACC.exe 114 0830 text.cpp
move text.code ..\Code\NL_Tree_PROG.code
move text.tree ..\Code\NL_Tree_PROG.tree

TranYACC.exe 013 0830 text.cpp
move text.code ..\Code\LL_Tree_TAB.code
move text.tree ..\Code\LL_Tree_TAB.tree

TranYACC.exe 243 1830 text.cpp
move text.code ..\Code\LR_Turn_TAB.code
move text.tree ..\Code\LR_Turn_TAB.tree
move text.node ..\Code\LR_Turn_TAB.node

TranYACC.exe 333 1830 text.cpp
move text.code ..\Code\NR_Node_TAB.code
move text.tree ..\Code\NR_Node_TAB.tree
move text.node ..\Code\NR_Node_TAB.node

TranYACC.exe 01E 0830 text.cpp
move text.code ..\Code\LL_Tree_YACC.code
move text.tree ..\Code\LL_Tree_YACC.tree
TranYACC.exe 02E 0820 text.cpp
move text.code ..\Code\LL_Code_YACC.code

TranYACC.exe 21E 0830 text.cpp
move text.code ..\Code\LR_Tree_YACC.code
move text.tree ..\Code\LR_Tree_YACC.tree
TranYACC.exe 22E 0820 text.cpp
move text.code ..\Code\LR_Code_YACC.code

TranYACC.exe 31E 0830 text.cpp
move text.code ..\Code\NR_Tree_YACC.code
move text.tree ..\Code\NR_Tree_YACC.tree
TranYACC.exe 32E 0820 text.cpp
move text.code ..\Code\NR_Code_YACC.code
TranYACC.exe 33E 1830 text.cpp
move text.code ..\Code\NR_Node_YACC.code
move text.tree ..\Code\NR_Node_YACC.tree
move text.node ..\Code\NR_Node_YACC.node

TranYACC.exe 35E 0830 text.cpp
move text.code ..\Code\NR_Made_YACC.code
move text.tree ..\Code\NR_Made_YACC.tree
