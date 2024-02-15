..\Release\Translator 0x0003 0x0002F0 0x00000001 ..\Grammar\LX\_LX_.grammar
move ..\Grammar\LX\_LX_.grammar ..\Grammar\LX\LR_Left.y
..\Release\TableBuilder 0x000D45 0x00001100 ..\Table\LR_Left_UR_LL1.tab ..\Grammar\LX\LR_Left.y
..\Release\TranGrammar 4 0820 text.cpp ..\Table\LR_Left_UR_LL1.tab   
move text.code ..\Code\LR_Left_TURN_LL1.code
fc /L /N ..\Code\C_CODE.code ..\Code\LR_Left_TURN_LL1.code

..\Release\Translator 0x0003 0x0003F0 0x00000041 ..\Grammar\LX\_LX_.grammar
move ..\Grammar\LX\_LX_.grammar ..\Grammar\LX\NR_Left.bnf
..\Release\TableBuilder 0x000B15 0x00001100 ..\Table\NR_Left_TC_LL1.tab ..\Grammar\LX\NR_Left.bnf
..\Release\TranGrammar 1 0820 text.cpp ..\Table\NR_Left_TC_LL1.tab   
move text.code ..\Code\NR_Left_CODE_LL1.code
fc /L /N ..\Code\C_CODE.code ..\Code\NR_Left_CODE_LL1.code
