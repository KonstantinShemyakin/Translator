TableBuilder.exe 000A18 000910ff ETF\BIF_TC.tab ..\Grammar\BIF_TC.bif
TranGrammar.exe 1 4FF8 test.cpp  ETF\BIF_TC.tab 
move test.code ETF\BIF_Tree_BIF.code
move test.tree ETF\BIF_Tree_BIF.tree
TranGrammar.exe 2 4FF8 test.cpp  ETF\BIF_TC.tab 
move test.code ETF\BIF_Code_BIF.code

