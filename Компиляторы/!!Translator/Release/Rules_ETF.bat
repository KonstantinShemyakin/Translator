:RULE_STACK
TranRules.exe 511 0830 test.cpp
move test.code ..\Code\Formula_ETF_Tree_PSR.code
move test.tree ..\Code\Formula_ETF_Tree_PSR.tree
:FORMULA_STACK
TranRules.exe 512 0830 test.cpp
move test.code ..\Code\Formula_ETF_Tree_PSS.code
move test.tree ..\Code\Formula_ETF_Tree_PSS.tree
TranRules.exe 522 0830 test.cpp
move test.code ..\Code\Formula_ETF_Code_PSS.code
:FORMULA_PRODUCE
TranRules.exe 514 0830 test.cpp
move test.code ..\Code\Formula_ETF_Tree_PF.code
move test.tree ..\Code\Formula_ETF_Tree_PF.tree
