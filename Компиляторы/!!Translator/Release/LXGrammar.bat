..\Release\TableBuilder 0x000E15 0x00091000 ..\Table\LLy_TC_LL1.tab ..\Grammar\LX\LL.grammar
..\Release\TableBuilder 0x000E35 0x00091000 ..\Table\LLy_SN_LL1.tab ..\Grammar\LX\LL.grammar

..\Release\TableBuilder 0x000E16 0x00091000 ..\Table\LRy_TC_LR0.tab ..\Grammar\LX\LR.grammar
..\Release\TableBuilder 0x000E48 0x00091000 ..\Table\LRy_UR_LR1.tab ..\Grammar\LX\LR.grammar

..\Release\TableBuilder 0x000E18 0x00091000 ..\Table\NRy_TC_LR1.tab ..\Grammar\LX\NR.grammar
..\Release\TableBuilder 0x000E38 0x00091000 ..\Table\NRy_SN_LR1.tab ..\Grammar\LX\NR.grammar

TranGrammar.exe 1 0830 text.cpp ..\Table\LLy_TC_LL1.tab
move text.code ..\Code\LLy_Tree_LL1.code
move text.tree ..\Code\LLy_Tree_LL1.tree
TranGrammar.exe 2 0820 text.cpp ..\Table\LLy_TC_LL1.tab
move text.code ..\Code\LLy_Code_LL1.code
TranGrammar.exe 5 1830 text.cpp ..\Table\LLy_SN_LL1.tab
move text.code ..\Code\LLy_Made_LL1.code
move text.tree ..\Code\LLy_Made_LL1.tree

TranGrammar.exe 1 0830 text.cpp ..\Table\LRy_TC_LR0.tab
move text.code ..\Code\LRy_Tree_LR0.code
move text.tree ..\Code\LRy_Tree_LR0.tree
TranGrammar.exe 2 0820 text.cpp ..\Table\LRy_TC_LR0.tab
move text.code ..\Code\LRy_Code_LR0.code
TranGrammar.exe 4 1830 text.cpp ..\Table\LRy_UR_LR1.tab
move text.code ..\Code\LRy_Turn_LR1.code
move text.tree ..\Code\LRy_Turn_LR1.tree
move text.node ..\Code\LRy_Turn_LR1.node

TranGrammar.exe 1 0830 text.cpp ..\Table\NRy_TC_LR1.tab
move text.code ..\Code\NRy_Tree_LR1.code
move text.tree ..\Code\NRy_Tree_LR1.tree
TranGrammar.exe 2 0820 text.cpp ..\Table\NRy_TC_LR1.tab
move text.code ..\Code\LRy_Code_LR1.code
TranGrammar.exe 5 1830 text.cpp ..\Table\NRy_SN_LR1.tab
move text.code ..\Code\NRy_Made_LR1.code
move text.tree ..\Code\NRy_Made_LR1.tree

