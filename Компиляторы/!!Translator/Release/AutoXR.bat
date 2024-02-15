rem GOTO DIFF

TableBuilder 000216 10800000 Auto\LR_TC_LR0.tab 
TableBuilder 010248 10800000 Auto\LR_UR_LRk.tab 
TableBuilder 01021A 10800000 Auto\LR_TC_LARLk.tab 

TableBuilder 000216 10900000 Auto\LR_TCA_LR0.tab 
TableBuilder 010248 10900000 Auto\LR_URA_LRk.tab 
TableBuilder 01022A 10900000 Auto\LR_TCA_LARLk.tab 

TableBuilder 000318 10000000 Auto\NR_TC_LR1.tab 
TableBuilder 010338 10000000 Auto\NR_SN_LRk.tab 
TableBuilder 01031A 10000000 Auto\NR_TC_LARLk.tab 
:DIFF
                    
TranGrammar.exe 1 40830 text.cpp  Auto\LR_TC_LR0.tab
move text.auto Auto\LR_Tree_LR0.auto
TranGrammar.exe 4 40830 text.cpp  Auto\LR_UR_LRk.tab
move text.auto Auto\LR_Turn_LRk.auto
TranGrammar.exe 1 40830 text.cpp  Auto\LR_TC_LARLk.tab
move text.auto Auto\LR_Tree_LARLk.auto
TranGrammar.exe 2 40830 text.cpp  Auto\LR_TC_LARLk.tab
move text.auto Auto\LR_Code_LARLk.auto

TranGrammar.exe 1 40830 text.cpp  Auto\LR_TCA_LR0.tab
move text.auto Auto\LR_TreeAss_LR0.auto
TranGrammar.exe 4 40830 text.cpp  Auto\LR_URA_LRk.tab
move text.auto Auto\LR_TurnAss_LRk.auto
TranGrammar.exe 2 40830 text.cpp  Auto\LR_TCA_LARLk.tab
move text.auto Auto\LR_CodeAss_LARLk.auto

TranGrammar.exe 1 40830 text.cpp  Auto\NR_TC_LR1.tab
move text.auto Auto\NR_Tree_LR1.auto
TranGrammar.exe 3 40830 text.cpp  Auto\NR_SN_LRk.tab
move text.auto Auto\NR_Node_LRk.auto
TranGrammar.exe 5 40830 text.cpp  Auto\NR_SN_LRk.tab
move text.auto Auto\NR_Made_LRk.auto
TranGrammar.exe 2 40830 text.cpp  Auto\NR_TC_LARLk.tab
move text.auto Auto\NR_Code_LARLk.auto

                   
fc /L /N Auto\LR_Tree_LR0.auto Auto\LR_Turn_LRk.auto
fc /L /N Auto\LR_Tree_LR0.auto Auto\LR_Tree_LARLk.auto
fc /L /N Auto\LR_Tree_LR0.auto Auto\LR_Code_LARLk.auto
                   
fc /L /N Auto\LR_TreeAss_LR0.auto Auto\LR_TurnAss_LRk.auto
fc /L /N Auto\LR_TreeAss_LR0.auto Auto\LR_CodeAss_LARLk.auto

fc /L /N Auto\NR_Tree_LR1.auto Auto\NR_Node_LRk.auto
fc /L /N Auto\NR_Tree_LR1.auto Auto\NR_Code_LARLk.auto
fc /L /N Auto\NR_Made_LRk.auto Auto\NR_Node_LRk.auto
