rem title, sym, key, c, lexeme
Exec\TranParse.exe D 00000001 Scanner\scanner
rem *.c -> *.lex
Exec\TranParse.exe 8 00000001 Scanner\scanner.c