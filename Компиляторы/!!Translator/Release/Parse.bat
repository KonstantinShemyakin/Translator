TranParse.exe
rem   0 - source
TranParse.exe 0 0007
rem   1 - scan
TranParse.exe 1 0001
rem   2 - next
TranParse.exe 2 0001
rem   3 - control
TranParse.exe 3 0001
rem   4 - lexeme
TranParse.exe 4 0008
rem   5 - prior
TranParse.exe 5 0008
rem   6 - syntax
TranParse.exe 6 0008 test_group.cpp
rem   7 - restore
TranParse.exe 7 0007
rem   8 - Z(),E(),T(),F()
TranParse.exe 8 4001 zetf.cpp
rem   9 - write
TranParse.exe 9 0008
rem   A - lexer
TranParse.exe A 0007 test_lexer.cpp
