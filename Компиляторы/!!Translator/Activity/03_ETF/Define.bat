rem TableBuilder.exe 0x000A15 0x000911CB Table\ETF_Define.tab    ETF_Define.bif
copy ETF_Define.tab Table\ETF_Define.tab
TranGrammar.exe 0 0x00060000 Test_Define.cpp Table\ETF_Define.tab
move Test_Define.auto  Code\ETF_Define.auto
