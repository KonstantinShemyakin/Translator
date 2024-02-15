TranBuilder.exe 0 0000 ..\Grammar\C_Grammar.y
TableBuilder.exe F1A 0x003931FF ..\Table\C_Grammar.tab ..\Grammar\C_Grammar.tab
TranGrammar.exe C 0000 text_c.cpp ..\Table\C_Grammar.tab
TranGrammar.exe C 0000 test_c.cpp ..\Table\C_Grammar.tab

TableBuilder.exe E1D 0x003931FF ..\Table\C99_Grammar.tab ..\Grammar\C99_Grammar.y
TranGrammar.exe D 0000 text_c.cpp ..\Table\C99_Grammar.tab
TranGrammar.exe D 0000 test_c.cpp ..\Table\C99_Grammar.tab

TranYACC.exe C1E 0000 test_c.cpp
