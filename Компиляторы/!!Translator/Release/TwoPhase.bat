:CSYNTAX
TranSyntax.exe 3 0820 text.cpp
move text.code ..\Code\C_Code.code

TranSyntax.exe 0x20011061 0x00000830 text.cpp
move text.code ..\Code\LL_DSyntax_BlockTable.code
move text.tree ..\Code\LL_DSyntax_BlockTable.tree
TranSyntax.exe 0x20012061 0x00000830 text.cpp
move text.code ..\Code\LL_DSyntax_TreeSearch.code
move text.tree ..\Code\LL_DSyntax_TreeSearch.tree
TranSyntax.exe 0x20011021 0x00000830 text.cpp
move text.code ..\Code\LL_TSyntax_BlockTable.code
move text.tree ..\Code\LL_TSyntax_BlockTable.tree

TranRules.exe  0x20011015 0x00000830 text.cpp
move text.code ..\Code\LL_Made_BlockTable_PSR.code
move text.tree ..\Code\LL_Made_BlockTable_PSR.tree

TableBuilder.exe 0x20000035 0x1009113F ..\Table\LL_SN_LL1_Block.tab
 
TranGrammar.exe  0x20F11015 0x00000830 text.cpp ..\Table\LL_SN_LL1_Block.tab
move text.code ..\Code\LL_Made_BlockTable_LL1.code
move text.tree ..\Code\LL_Made_BlockTable_LL1.tree
TranRules.exe    0x20F11015 0x00000830 text.cpp ..\Table\LL_SN_LL1_Block.tab
move text.code ..\Code\LL_Made_BlockTable_PSR_Tab.code
move text.tree ..\Code\LL_Made_BlockTable_PSR_Tab.tree

TableBuilder.exe 0x20000065 0x1009113F ..\Table\LL_Call_LL1_Block.tab
 
TranGrammar.exe  0x20F11016 0x00000830 text.cpp ..\Table\LL_Call_LL1_Block.tab
move text.code ..\Code\LL_Call_BlockTable_LL1.code
move text.tree ..\Code\LL_Call_BlockTable_LL1.tree
TranRules.exe    0x20F11016 0x00000830 text.cpp ..\Table\LL_Call_LL1_Block.tab
move text.code ..\Code\LL_Call_BlockTable_PSR_Tab.code
move text.tree ..\Code\LL_Call_BlockTable_PSR_Tab.tree

TranGrammar.exe  0x20F12016 0x00000830 text.cpp ..\Table\LL_Call_LL1_Block.tab
move text.code ..\Code\LL_Call_TreeSearch_LL1.code
move text.tree ..\Code\LL_Call_TreeSearch_LL1.tree
TranRules.exe    0x20F12016 0x00000830 text.cpp ..\Table\LL_Call_LL1_Block.tab
move text.code ..\Code\LL_Call_TreeSearch_PSR_Tab.code
move text.tree ..\Code\LL_Call_TreeSearch_PSR_Tab.tree

TableBuilder.exe 0x20000066 0x1009113F ..\Table\LL_Call_LR0_Block.tab
 
TranGrammar.exe  0x20F11016 0x00000830 text.cpp ..\Table\LL_Call_LR0_Block.tab
move text.code ..\Code\LL_Call_BlockTable_LR0.code
move text.tree ..\Code\LL_Call_BlockTable_LR0.tree
TranGrammar.exe  0x20F12016 0x00000830 text.cpp ..\Table\LL_Call_LR0_Block.tab
move text.code ..\Code\LL_Call_TreeSearch_LR0.code
move text.tree ..\Code\LL_Call_TreeSearch_LR0.tree

fc /L /N ..\Code\C_Code.code ..\Code\LL_DSyntax_BlockTable.code
fc /L /N ..\Code\C_Code.code ..\Code\LL_DSyntax_TreeSearch.code
fc /L /N ..\Code\C_Code.code ..\Code\LL_TSyntax_BlockTable.code

fc /L /N ..\Code\C_Code.code ..\Code\LL_Made_BlockTable_PSR.code
fc /L /N ..\Code\C_Code.code ..\Code\LL_Made_BlockTable_PSR_Tab.code
fc /L /N ..\Code\C_Code.code ..\Code\LL_Made_BlockTable_LL1.code

fc /L /N ..\Code\C_Code.code ..\Code\LL_Call_BlockTable_PSR_Tab.code
fc /L /N ..\Code\C_Code.code ..\Code\LL_Call_BlockTable_LL1.code

fc /L /N ..\Code\C_Code.code ..\Code\LL_Call_TreeSearch_PSR_Tab.code
fc /L /N ..\Code\C_Code.code ..\Code\LL_Call_TreeSearch_LL1.code

fc /L /N ..\Code\C_Code.code ..\Code\LL_Call_BlockTable_LR0.code
fc /L /N ..\Code\C_Code.code ..\Code\LL_Call_TreeSearch_LR0.code
