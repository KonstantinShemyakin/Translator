..\Release\Translator 0x0003 0x000DF0 0x00000001 ..\Grammar\LX\_LX_.grammar ..\Grammar\LX\C_Grammar.y
move ..\Grammar\LX\_LX_.grammar ..\Grammar\LX\C_Grammar_Left.y
..\Release\TableBuilder 0x020D1A 0x00001101 ..\Table\C_Grammar_Left_LRk.tab ..\Grammar\LX\C_Grammar_Left.y
TranGrammar.exe 6 0000 test_c.cpp ..\Table\C_Grammar_Left_LRk.tab
