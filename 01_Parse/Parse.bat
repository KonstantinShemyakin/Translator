TranParse.exe
rem   0 - source
TranParse.exe 0 0007 test.cpp
rem   1 - scan
TranParse.exe 1 0001 test.cpp
rem   2 - next
TranParse.exe 2 0001 test.cpp
rem   3 - control
TranParse.exe 3 0001 test.cpp
rem   4 - lexeme
TranParse.exe 4 0008 test.cpp
rem   5 - prior
TranParse.exe 5 0008 test.cpp
rem   6 - syntax
TranParse.exe 6 0008 test_group.cpp
rem   7 - restore
TranParse.exe 7 0007 test.cpp
rem   8 - write
TranParse.exe 8 0008 test.cpp
rem   9 - lexer
TranParse.exe 9 0007 test_lexer.cpp
rem   0x0A - Z(),E(),T(),F()
TranParse.exe 0x0A 4001 zetf.cpp
rem   0x0B - Z(),E(),T(),E_(),T_(),F()
TranParse.exe 0x0B 4001 zetf.cpp