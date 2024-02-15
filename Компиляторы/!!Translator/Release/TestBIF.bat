:LL_BIF
TableBuilder.exe 0x000000 0x000000C1 ..\Table\LL_BIF.grammar
TableBuilder.exe 0x000A15 0x000911Cf ..\Table\LL_TC_BIF_LL1.tab ..\Table\LL_BIF.grammar
TableBuilder.exe 0x000A16 0x0009110f ..\Table\LL_TC_BIF_LR0.tab ..\Table\LL_BIF.grammar

TranGrammar.exe 1 0830 text.cpp ..\Table\LL_TC_BIF_LL1.tab
move text.code ..\Code\LL_Tree_BIF_LL1.code
move text.tree ..\Code\LL_Tree_BIF_LL1.tree
TranGrammar.exe 2 0830 text.cpp ..\Table\LL_TC_BIF_LR0.tab
move text.code ..\Code\LL_Code_BIF_LR0.code
:LR_BIF
TableBuilder.exe 0x000200 0x000000C1 ..\Table\LR_BIF.grammar
TableBuilder.exe 0x000A16 0x000911Cf ..\Table\LR_TC_BIF_LR0.tab ..\Table\LR_BIF.grammar
TableBuilder.exe 0x000A48 0x0009110f ..\Table\LR_UR_BIF_LR1.tab ..\Table\LR_BIF.grammar

TranGrammar.exe 1 0830 text.cpp ..\Table\LR_TC_BIF_LR0.tab
move text.code ..\Code\LR_Tree_BIF_LR0.code
move text.tree ..\Code\LR_Tree_BIF_LR0.tree
TranGrammar.exe 4 0830 text.cpp ..\Table\LR_UR_BIF_LR1.tab
move text.code ..\Code\LR_Turn_BIF_LR1.code
move text.tree ..\Code\LR_Turn_BIF_LR1.tree
:NR_BIF
TableBuilder.exe 0x000300 0x000000C1 ..\Table\NR_BIF.grammar
TableBuilder.exe 0x000A18 0x000911Cf ..\Table\NR_TC_BIF_LR1.tab ..\Table\NR_BIF.grammar

TranGrammar.exe 1 0830 text.cpp ..\Table\NR_TC_BIF_LR1.tab
move text.code ..\Code\NR_Tree_BIF_LR1.code
move text.tree ..\Code\NR_Tree_BIF_LR1.tree
TranGrammar.exe 2 0830 text.cpp ..\Table\NR_TC_BIF_LR1.tab
move text.code ..\Code\NR_Code_BIF_LR1.code
:COMPARE
fc /L /N ..\Code\C_Code.code ..\Code\LL_Tree_BIF_LL1.code
fc /L /N ..\Code\C_Code.code ..\Code\LL_Code_BIF_LR0.code
fc /L /N ..\Code\C_Code.code ..\Code\LR_Tree_BIF_LR0.code
fc /L /N ..\Code\C_Code.code ..\Code\LR_Turn_BIF_LR1.code
fc /L /N ..\Code\C_Code.code ..\Code\NR_Tree_BIF_LR1.code
fc /L /N ..\Code\C_Code.code ..\Code\NR_Code_BIF_LR1.code
:BIF_CYCLE
TableBuilder.exe 0x000A00 0x000000C1 ..\Table\LL_TC_BIF.grammar ..\Table\LL_TC_BIF_LL1.grammar
fc /L /N ..\Table\LL_TC_BIF.grammar ..\Table\LL_TC_BIF_LL1.grammar
TableBuilder.exe 0x000A00 0x000000C1 ..\Table\LR_TC_BIF.grammar ..\Table\LR_TC_BIF_LR0.grammar
fc /L /N ..\Table\LR_TC_BIF.grammar ..\Table\LR_TC_BIF_LR0.grammar
TableBuilder.exe 0x000A00 0x000000C1 ..\Table\NR_TC_BIF.grammar ..\Table\NR_TC_BIF_LR1.grammar
fc /L /N ..\Table\NR_TC_BIF.grammar ..\Table\NR_TC_BIF_LR1.grammar
:F_BNF
TableBuilder 0x000E00 0x00000041 ..\Table\FGrammarBNF.grammar ..\Grammar\FGrammar.y
TableBuilder 0x000B38 0x00002041 ..\Table\FGrammar.tab ..\Table\FGrammarBNF.grammar
fc /L /N ..\Table\FGrammar.cpp ..\Generated\FGrammar.cpp
fc /L /N ..\Table\FGrammar.grammar ..\Table\FGrammarBNF.grammar
move ..\Table\FGrammar.grammar ..\Grammar\FGrammar.bnf
:B_BNF
TableBuilder 0x000E00 0x00000041 ..\Table\BGrammarBNF.grammar ..\Grammar\BGrammar.y
TableBuilder 0x020B38 0x00002041 ..\Table\BGrammar.tab ..\Table\BGrammarBNF.grammar
fc /L /N ..\Table\BGrammar.cpp ..\Generated\BGrammar.cpp
fc /L /N ..\Table\BGrammar.grammar ..\Table\BGrammarBNF.grammar
move ..\Table\BGrammar.grammar ..\Grammar\BGrammar.bnf
:I_BNF
TableBuilder 0x000E00 0x00000041 ..\Table\IGrammarBNF.grammar ..\Grammar\IGrammar.y
TableBuilder 0x020B38 0x00002041 ..\Table\IGrammar.tab ..\Table\IGrammarBNF.grammar
fc /L /N ..\Table\IGrammar.cpp ..\Generated\IGrammar.cpp
fc /L /N ..\Table\IGrammar.grammar ..\Table\IGrammarBNF.grammar
move ..\Table\IGrammar.grammar ..\Grammar\IGrammar.bnf
:I_BIF_LLk
..\Release\TableBuilder 0x000A15 0x80003140  ..\Table\LL_TC_BIF_Grammar_LLk.tab ..\Grammar\LX\LL.bif
..\Release\TableBuilder 0x000A15 0x00003140  ..\Table\LL_TC_BIF_Grammar_Y.tab ..\Grammar\LX\LL.bif
fc /L /N ..\Table\LL_TC_BIF_Grammar_LLk.tab  ..\Table\LL_TC_BIF_Grammar_Y.tab

..\Release\TranGrammar.exe 1 0820 text.cpp ..\Table\LL_TC_LL1.tab
move text.code ..\Code\LL_TC_LL1.code
..\Release\TranGrammar.exe 1 0820 text.cpp ..\Table\LL_TC_BIF_Grammar_LLk.tab   
move text.code ..\Code\LL_TC_BIF_Grammar_LLk.code
fc /L /N ..\Code\LL_TC_LL1.code ..\Code\LL_TC_BIF_Grammar_LLk.code

..\Release\TableBuilder 0x020A48 0x00093133 ..\Table\IGrammarLRk.tab ..\Grammar\IGrammar.bif
..\Release\TableBuilder 0x000915 0x80003140 ..\Grammar\LX\LL.bif ..\Table\IGrammarLRk.tab
fc /L /N ..\Table\LL_TC_BIF_LLk.tab ..\Grammar\LX\LL.tab
