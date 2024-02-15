:SYNTAX
TranSyntax.exe 1 0830 text.cpp
:TSYNTAX
TranSyntax.exe 2 0830 text.cpp
move text.code ..\Code\T_Tree.code
move text.tree ..\Code\T_Tree.tree
:DSYNTAX
TranSyntax.exe 6 0830 text.cpp
move text.code ..\Code\D_Tree.code
move text.tree ..\Code\D_Tree.tree
:CSYNTAX
TranSyntax.exe 3 0830 text.cpp
move text.code ..\Code\C_Code.code
:MSYNTAX_TREE
TranSyntax.exe 4 0830 text.cpp
move text.code ..\Code\M_Tree.code
move text.tree ..\Code\M_Tree.tree
:MSYNTAX_CODE
TranSyntax.exe 5 0830 text.cpp
move text.code ..\Code\M_Code.code

fc /L /N ..\Code\C_Code.code ..\Code\T_Tree.code
fc /L /N ..\Code\C_Code.code ..\Code\D_Tree.code
fc /L /N ..\Code\C_Code.code ..\Code\M_Tree.code
fc /L /N ..\Code\C_Code.code ..\Code\M_Code.code
