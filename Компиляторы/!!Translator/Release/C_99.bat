:C
TableBuilder.exe E1A 0x00001101 ..\Table\C_Grammar.tab ..\Grammar\C_Grammar.y
TranGrammar.exe C 0000 text_c.cpp ..\Table\C_Grammar.tab
TranGrammar.exe C 0000 test_c.cpp ..\Table\C_Grammar.tab
:C_99
TableBuilder.exe E1D 0x00001101 ..\Table\C99_Grammar.tab ..\Grammar\C99_Grammar.y
TranGrammar.exe D 0000 text_c.cpp ..\Table\C99_Grammar.tab
TranGrammar.exe D 0000 test_c.cpp ..\Table\C99_Grammar.tab
:C_YACC
TranYACC.exe C1E 0000 test_c.cpp
