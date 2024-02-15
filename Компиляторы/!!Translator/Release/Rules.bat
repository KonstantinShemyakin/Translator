:RULE_STACK
TranRules.exe 011 0830 text.cpp
move text.code ..\Code\Formula_LL_Tree_PSR.code
move text.tree ..\Code\Formula_LL_Tree_PSR.tree
TranRules.exe 021 0820 text.cpp
move text.code ..\Code\Formula_LL_Code_PSR.code
TranRules.exe 031 1830 text.cpp
move text.code ..\Code\Formula_LL_Node_PSR.code
move text.tree ..\Code\Formula_LL_Node_PSR.tree
move text.node ..\Code\Formula_LL_Node_PSR.node
TranRules.exe 051 0830 text.cpp
move text.code ..\Code\Formula_LL_Made_PSR.code
move text.tree ..\Code\Formula_LL_Made_PSR.tree
:FORMULA_STACK
TranRules.exe 012 0830 text.cpp
move text.code ..\Code\Formula_LL_Tree_PSS.code
move text.tree ..\Code\Formula_LL_Tree_PSS.tree
TranRules.exe 022 0820 text.cpp
move text.code ..\Code\Formula_LL_Code_PSS.code
:FORMULA_PRODUCE
TranRules.exe 024 0830 text.cpp
move text.code ..\Code\Formula_LL_Code_PF.code
TranRules.exe 114 0830 text.cpp
move text.code ..\Code\Formula_NL_Tree_PF.code
move text.tree ..\Code\Formula_NL_Tree_PF.tree

fc /L /N ..\Code\C_Code.code ..\Code\Formula_LL_Tree_PSR.code
fc /L /N ..\Code\C_Code.code ..\Code\Formula_LL_Code_PSR.code
fc /L /N ..\Code\C_Code.code ..\Code\Formula_LL_Node_PSR.code
fc /L /N ..\Code\C_Code.code ..\Code\Formula_LL_Made_PSR.code
fc /L /N ..\Code\C_Code.code ..\Code\Formula_LL_Tree_PSS.code
fc /L /N ..\Code\C_Code.code ..\Code\Formula_LL_Code_PSS.code
fc /L /N ..\Code\C_Code.code ..\Code\Formula_LL_Code_PF.code
fc /L /N ..\Code\C_Code.code ..\Code\Formula_NL_Tree_PF.code
