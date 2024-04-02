Exec\TranParse.exe 4 01000001 Test\test_group.cpp
move Test\test_group.lex Test\test_group_simple.lex
Exec\TranParse.exe 5 01000001 Test\test_group.cpp
move Test\test_group.lex Test\test_group_prior.lex
Exec\TranParse.exe 6 01000001 Test\test_group.cpp
move Test\test_group.lex Test\test_group_syntax.lex
