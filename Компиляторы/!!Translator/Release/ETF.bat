del /Q ETF\*.*
TableBuilder 405 000915FF ..\ETF\ETF_LL_LL1.tab 
TableBuilder 515 000915FF ..\ETF\ETF_LL_TC_LL1.tab 

TableBuilder 404 000915FF ..\ETF\ETF_LL_PROG.tab 
TableBuilder 514 000915FF ..\ETF\ETF_LL_TC_PROG.tab 

TranGrammar.exe 0 4FF8 ETFtest.cpp ..\ETF\ETF_LL_LL1.tab      >..\ETF\ETF_LL_LL1.journal
TranGrammar.exe 1 4FF8 ETFtest.cpp ..\ETF\ETF_LL_TC_LL1.tab   >..\ETF\ETF_LL_T_LL1.journal
move ETFtest.code ..\ETF\ETF_LL_Tree_LL1.code
move ETFtest.tree ..\ETF\ETF_LL_Tree_LL1.tree
TranGrammar.exe 2 4FF8 ETFtest.cpp ..\ETF\ETF_LL_TC_LL1.tab   >..\ETF\ETF_LL_C_LL1.journal
move ETFtest.code ..\ETF\ETF_LL_Code_LL1.code

TableBuilder 606 000915FF ..\ETF\ETF_LR_LR0.tab 
TableBuilder 716 000915FF ..\ETF\ETF_LR_TC_LR0.tab

TranGrammar.exe 0 4FF8 ETFtest.cpp ..\ETF\ETF_LR_LR0.tab      >..\ETF\ETF_LR_LR0.journal
TranGrammar.exe 1 4FF8 ETFtest.cpp ..\ETF\ETF_LR_TC_LR0.tab   >..\ETF\ETF_LR_T_LR0.journal
move ETFtest.code ..\ETF\ETF_LR_Tree_LR0.code
move ETFtest.tree ..\ETF\ETF_LR_Tree_LR0.tree
TranGrammar.exe 2 4FF8 ETFtest.cpp ..\ETF\ETF_LR_TC_LR0.tab   >..\ETF\ETF_LR_C_LR0.journal
move ETFtest.code ..\ETF\ETF_LR_Code_LR0.code

TableBuilder 608 000915FF ..\ETF\ETF_LR_LR1.tab 
TableBuilder 718 000915FF ..\ETF\ETF_LR_TC_LR1.tab

TableBuilder 020608 000915FF ..\ETF\ETF_LR_LR2.tab 
TableBuilder 020718 000915FF ..\ETF\ETF_LR_TC_LR2.tab

TranGrammar.exe 0 4FF8 ETFtest.cpp ..\ETF\ETF_LR_LR1.tab      >..\ETF\ETF_LR_LR1.journal
TranGrammar.exe 1 4FF8 ETFtest.cpp ..\ETF\ETF_LR_TC_LR1.tab   >..\ETF\ETF_LR_T_LR1.journal
move ETFtest.code ..\ETF\ETF_LR_Tree_LR1.code
move ETFtest.tree ..\ETF\ETF_LR_Tree_LR1.tree
TranGrammar.exe 2 4FF8 ETFtest.cpp ..\ETF\ETF_LR_TC_LR1.tab   >..\ETF\ETF_LR_C_LR1.journal
move ETFtest.code ..\ETF\ETF_LR_Code_LR1.code

rem TableBuilder 60A 000915FF ..\ETF\ETF_LR_LALR.tab 
rem TableBuilder 71A 000915FF ..\ETF\ETF_LR_TC_LALR.tab

rem TranGrammar.exe 0 4FF8 ETFtest.cpp ..\ETF\ETF_LR_LALR.tab      >..\ETF\ETF_LR_LALR.journal
rem TranGrammar.exe 1 4FF8 ETFtest.cpp ..\ETF\ETF_LR_TC_LALR.tab   >..\ETF\ETF_LR_T_LALR.journal
rem move ETFtest.code ..\ETF\ETF_LR_Tree_LALR.code
rem move ETFtest.tree ..\ETF\ETF_LR_Tree_LALR.tree
rem TranGrammar.exe 2 4FF8 ETFtest.cpp ..\ETF\ETF_LR_TC_LALR.tab   >..\ETF\ETF_LR_C_LALR.journal
rem move ETFtest.code ..\ETF\ETF_LR_Code_LALR.code

