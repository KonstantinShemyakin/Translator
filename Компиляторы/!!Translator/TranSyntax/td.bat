..\Debug\TranSyntax.exe 0x20012061 0x00000810 test_L.cpp
move test_L.tree test_L.tree_ 
move test_L.code test_L.code_ 
..\Debug\TranSyntax.exe 2 0x00000810 test_L.cpp
fc /L /N test_L.tree test_L.tree_ >tt
fc /L /N test_L.code test_L.code_ >tc
