rem GOTO DIFF

TableBuilder 000015 10800000 Auto\LL_TC_LL1.tab 
TableBuilder 000035 10800000 Auto\LL_SN_LL1.tab 
TableBuilder 010015 10800000 Auto\LL_TC_LLk.tab 
TableBuilder 010035 10800000 Auto\LL_SN_LLk.tab 
TableBuilder 000016 10800000 Auto\LL_TC_LR0.tab 
TableBuilder 010018 10800000 Auto\LL_TC_LRk.tab 
TableBuilder 01001A 10800000 Auto\LL_TC_LARLk.tab 
:DIFF
                    
TranGrammar.exe 1 40830 text.cpp  Auto\LL_TC_LL1.tab
move text.auto Auto\LL_Tree_LL1.auto
TranGrammar.exe 3 40830 text.cpp  Auto\LL_SN_LL1.tab
move text.auto Auto\LL_Node_LL1.auto
TranGrammar.exe 2 40830 text.cpp  Auto\LL_TC_LLk.tab
move text.auto Auto\LL_Code_LLk.auto
TranGrammar.exe 5 40830 text.cpp  Auto\LL_SN_LLk.tab
move text.auto Auto\LL_Made_LLk.auto
TranGrammar.exe 1 40830 text.cpp  Auto\LL_TC_LR0.tab
move text.auto Auto\LL_Tree_LR0.auto
TranGrammar.exe 1 40830 text.cpp  Auto\LL_TC_LRk.tab
move text.auto Auto\LL_Tree_LRk.auto
TranGrammar.exe 1 40830 text.cpp  Auto\LL_TC_LARLk.tab
move text.auto Auto\LL_Tree_LARLk.auto
                   
fc /L /N Auto\LL_Tree_LR0.auto Auto\LL_Tree_LL1.auto
fc /L /N Auto\LL_Tree_LR0.auto Auto\LL_Node_LL1.auto
fc /L /N Auto\LL_Tree_LR0.auto Auto\LL_Code_LLk.auto
fc /L /N Auto\LL_Tree_LR0.auto Auto\LL_Made_LLk.auto
fc /L /N Auto\LL_Tree_LR0.auto Auto\LL_Tree_LRk.auto
fc /L /N Auto\LL_Tree_LR0.auto Auto\LL_Tree_LARLk.auto


