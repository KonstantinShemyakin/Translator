TableBuilder 514 000915FF ..\Table\ETF_LL_TC_PROG.tab 
TableBuilder 405 000915FF ..\Table\ETF_LL_LL1.tab 
TableBuilder 515 000915FF ..\Table\ETF_LL_TC_LL1.tab 
TableBuilder 606 000915FF ..\Table\ETF_LR_LR0.tab 
TableBuilder 608 000915FF ..\Table\ETF_LR_LR1.tab 
TableBuilder 61A 000915FF ..\Table\ETF_LR_LALR.tab 
TableBuilder 716 000915FF ..\Table\ETF_LR_TC_LR0.tab
TableBuilder 71A 000915FF ..\Table\ETF_LR_TC_LALR.tab 

TableBuilder 714 000915FF ..\Table\ETF_LR_TC_PROG.tab 
TableBuilder 71E 000915FF ..\Table\ETF_LR_TC_YACC.y  

TranGrammar.exe 0 4FF8 test.cpp ..\Table\ETF_LR_LR0.tab
TranGrammar.exe 1 4FF8 test.cpp ..\Table\ETF_LR_TC_LR0.tab
move test.code ..\Code\ETF_LR_Tree_LR0.code
move test.tree ..\Code\ETF_LR_Tree_LR0.tree
TranGrammar.exe 2 4FF8 test.cpp ..\Table\ETF_LR_TC_LR0.tab
move test.code ..\Code\ETF_LR_Code_LR0.code

TranGrammar.exe 0 4FF8 test.cpp ..\Table\ETF_LL_TC_LL1.tab
TranGrammar.exe 1 4FF8 test.cpp ..\Table\ETF_LL_TC_LL1.tab
move test.code ..\Code\ETF_LL_Tree_LL1.code
move test.tree ..\Code\ETF_LL_Tree_LL1.tree
TranGrammar.exe 2 4FF8 test.cpp ..\Table\ETF_LL_TC_LL1.tab
move test.code ..\Code\ETF_LL_Code_LL1.code

TableBuilder 916 000915FF ..\Table\EEE_TC_LR0.tab
TableBuilder A06 000915FF ..\Table\IFE_LR_LR0.tab
TableBuilder B06 000915FF ..\Table\SCC_LR0.tab
TableBuilder D06 000915FF ..\Table\SLR_LR0.tab

TranGrammar.exe 1 4FF8 test.cpp ..\Table\EEE_TC_LR0.tab
move test.code ..\Code\EEE_Tree_LR0.code
move test.tree ..\Code\EEE_Tree_LR0.tree
TranGrammar.exe 2 4FF8 test.cpp ..\Table\EEE_TC_LR0.tab
move test.code ..\Code\EEE_Code_LR0.code

TranYACC.exe 514 4FF8 test.cpp
move test.code ..\Code\ETF_LL_Tree_PROG.code
move test.tree ..\Code\ETF_LL_Tree_PROG.tree
TranYACC.exe 524 4FF8 test.cpp
move test.code ..\Code\ETF_LL_Code_PROG.code

