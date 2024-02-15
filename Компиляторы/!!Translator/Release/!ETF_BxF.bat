TableBuilder.exe 000B18 000910ff ETF\ETF_LR_TC_BNF.tab ..\Grammar\ETF_LR_TC.bnf
TranGrammar.exe 1 4FF8 test.cpp  ETF\ETF_LR_TC_BNF.tab 
move test.code ETF\ETF_LR_Tree_BNF.code
move test.tree ETF\ETF_LR_Tree_BNF.tree

TableBuilder.exe 000A18 000910ff ETF\ETF_TC_BIF.tab ..\Grammar\ETF_TC.bif
TranGrammar.exe 1 4FF8 test.cpp  ETF\ETF_TC_BIF.tab 
move test.code ETF\ETF_Tree_BIF.code
move test.tree ETF\ETF_Tree_BIF.tree
