..\Debug\TranSyntax.exe 0x20012061 0x0830 text.cpp
move text.tree text.tree_ 
move text.code text.code_ 
..\Debug\TranSyntax.exe 2 0x0830 text.cpp
fc /L /N text.tree text.tree_ >tt
fc /L /N text.code text.code_ >tc
