TableBuilder 71A 000915FF ..\ETF\ETF_LR_TC_LALR.tab
TableBuilder 71B 000915FF ..\ETF\ETF_LR_TC_Tab.tab
TableBuilder 71C 000915FF ..\ETF\ETF_LR_TC_Full.tab
TableBuilder 71D 000915FF ..\ETF\ETF_LR_TC_Core.tab
TableBuilder 716 000915FF ..\ETF\ETF_LR_TC_LR0.tab
TableBuilder 718 000915FF ..\ETF\ETF_LR_TC_LR1.tab

fc /L /N ..\ETF\ETF_LR_TC_Core.state  ..\ETF\ETF_LR_TC_LALR.core

fc /L /N ..\ETF\ETF_LR_TC_Core.action ..\ETF\ETF_LR_TC_Full.action
fc /L /N ..\ETF\ETF_LR_TC_Core.action ..\ETF\ETF_LR_TC_Tab.action
fc /L /N ..\ETF\ETF_LR_TC_Core.action ..\ETF\ETF_LR_TC_LALR.action

fc /L /N ..\ETF\ETF_LR_TC_Core.tab ..\ETF\ETF_LR_TC_Full.tab
fc /L /N ..\ETF\ETF_LR_TC_Core.tab ..\ETF\ETF_LR_TC_Tab.tab
fc /L /N ..\ETF\ETF_LR_TC_Core.tab ..\ETF\ETF_LR_TC_LALR.tab
fc /L /N ..\ETF\ETF_LR_TC_Core.tab ..\ETF\ETF_LR_TC_LR0.tab

fc /L /N ..\ETF\ETF_LR_TC_Core.goto ..\ETF\ETF_LR_TC_Full.goto
fc /L /N ..\ETF\ETF_LR_TC_Core.goto ..\ETF\ETF_LR_TC_Tab.goto
fc /L /N ..\ETF\ETF_LR_TC_Core.goto ..\ETF\ETF_LR_TC_LALR.goto

TranGrammar.exe 1 4FF8 ETFtest.cpp ..\ETF\ETF_LR_TC_LALR.tab   >..\ETF\ETF_LR_T_LALR.journal
move ETFtest.code ..\ETF\ETF_LR_Tree_LALR.code
move ETFtest.tree ..\ETF\ETF_LR_Tree_LALR.tree
TranGrammar.exe 2 4FF8 ETFtest.cpp ..\ETF\ETF_LR_TC_LALR.tab   >..\ETF\ETF_LR_C_LALR.journal
move ETFtest.code ..\ETF\ETF_LR_Code_LALR.code

