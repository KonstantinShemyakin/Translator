TableBuilder.exe 010E18 000910ff ETF\ETF_LR_TC_LRk.tab ..\Grammar\ETF_LR_TC.grammar
TranGrammar.exe 1 4FF8 test.cpp  ETF\ETF_LR_TC_LRk.tab 
move test.code ETF\ETF_LR_Tree_LRk.code
move test.tree ETF\ETF_LR_Tree_LRk.tree
TableBuilder.exe 020E18 000910ff ETF\ETF_LR_TC_LR2.tab ..\Grammar\ETF_LR_TC.grammar
TranGrammar.exe 1 4FF8 test.cpp  ETF\ETF_LR_TC_LR2.tab 
move test.code ETF\ETF_LR_Tree_LR2.code
move test.tree ETF\ETF_LR_Tree_LR2.tree
