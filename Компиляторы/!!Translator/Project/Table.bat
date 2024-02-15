rem Grammar       = 0x00000001, Follow        = 0x00000002, Maker        = 0x00000004, Lexeme = 0x00000008,
rem First         = 0x00000010, 
rem Formula       = 0x00000100, Rule          = 0x00000200, Output       = 0x00000400, C2A    = 0x00000800, Ahead = C2A,
rem Action        = 0x00001000, TableCpp      = 0x00002000, Cell         = Action,   
rem State         = 0x00010000, StateCore     = 0x00020000, StateSort    = 0x00040000, GoTo   = 0x00080000, 
rem Association   = 0x00100000, Compression   = 0x00200000, AssignOper   = 0x00400000
 
TableBuilder 015 003931FF ..\Table\LL_TC_LL1.tab 
TableBuilder 016 00391000 ..\Table\LL_TC_LR0.tab 
TableBuilder 017 00391000 ..\Table\LL_TC_LR0_Core.tab 
TableBuilder 018 00391000 ..\Table\LL_TC_LR1.tab 
TableBuilder 019 00391000 ..\Table\LL_TC_LR1_Core.tab 
TableBuilder 01A 00391000 ..\Table\LL_TC_LALR.tab 
TableBuilder 01B 00391000 ..\Table\LL_TC_Tab.tab 
TableBuilder 01C 00391000 ..\Table\LL_TC_Full.tab 
TableBuilder 01D 00391000 ..\Table\LL_TC_Core.tab 

TableBuilder 035 003911FF ..\Table\LL_SN_LL1.tab 

TableBuilder 216 003910FF ..\Table\LR_TC_LR0.tab 
TableBuilder 217 00391000 ..\Table\LR_TC_LR0_Core.tab 
TableBuilder 218 00391000 ..\Table\LR_TC_LR1.tab 
TableBuilder 219 00391000 ..\Table\LR_TC_LR1_Core.tab 
TableBuilder 21A 00391000 ..\Table\LR_TC_LALR.tab 
TableBuilder 21B 00391000 ..\Table\LR_TC_Tab.tab 
TableBuilder 21C 00391000 ..\Table\LR_TC_Full.tab 
TableBuilder 21D 00391000 ..\Table\LR_TC_Core.tab 

TableBuilder 246 003930FF ..\Table\LR_UR_LR0.tab 
TableBuilder 247 00391000 ..\Table\LR_UR_LR0_Core.tab 
TableBuilder 248 00391000 ..\Table\LR_UR_LR1.tab 
TableBuilder 249 00391000 ..\Table\LR_UR_LR1_Core.tab 
TableBuilder 24A 00391000 ..\Table\LR_UR_LALR.tab 
TableBuilder 24B 00391000 ..\Table\LR_UR_Tab.tab 
TableBuilder 24C 00391000 ..\Table\LR_UR_Full.tab 
TableBuilder 24D 00391000 ..\Table\LR_UR_Core.tab 

TableBuilder 316 003910FF ..\Table\NR_TC_LR0.tab 
TableBuilder 317 00391000 ..\Table\NR_TC_LR0_Core.tab 
TableBuilder 318 00391000 ..\Table\NR_TC_LR1.tab 
TableBuilder 319 00391000 ..\Table\NR_TC_LR1_Core.tab 
TableBuilder 31A 00391000 ..\Table\NR_TC_LALR.tab 
TableBuilder 31B 00391000 ..\Table\NR_TC_Tab.tab 
TableBuilder 31C 00391000 ..\Table\NR_TC_Full.tab 
TableBuilder 31D 00391000 ..\Table\NR_TC_Core.tab 

TableBuilder 336 003930FF ..\Table\NR_SN_LR0.tab 
TableBuilder 337 00391000 ..\Table\NR_SN_LR0_Core.tab 
TableBuilder 338 00391000 ..\Table\NR_SN_LR1.tab 
TableBuilder 339 00391000 ..\Table\NR_SN_LR1_Core.tab 
TableBuilder 33A 00391000 ..\Table\NR_SN_LALR.tab 
TableBuilder 33B 00391000 ..\Table\NR_SN_Tab.tab 
TableBuilder 33C 00391000 ..\Table\NR_SN_Full.tab 
TableBuilder 33D 00391000 ..\Table\NR_SN_Core.tab 
