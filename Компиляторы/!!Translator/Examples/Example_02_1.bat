TableBuilder 405 3C3FFCF Table\02_ETF_LL_LL1.tab 
TableBuilder 606 3C3FFCF Table\02_ETF_LR_LR0.tab 
TableBuilder 515 3C3FFCF Table\02_ETF_LL_TC_LL1.tab 
TableBuilder 716 3C3FFCF Table\02_ETF_LR_TC_LR0.tab 

TranGrammar.exe 1 4FF8 Example_02.cpp Table\02_ETF_LR_TC_LR0.tab
move Example_02.code Code\02_ETF_LR_Tree_LR0.code
move Example_02.tree Code\02_ETF_LR_Tree_LR0.tree

TranGrammar.exe 1 4FF8 Example_02.cpp Table\02_ETF_LL_TC_LL1.tab
move Example_02.code Code\02_ETF_LL_Tree_LL1.code
move Example_02.tree Code\02_ETF_LL_Tree_LL1.tree
