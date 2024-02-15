rem Grammar       = 0x00000001, Follow        = 0x00000002, Maker        = 0x00000004, Lexeme        = 0x00000008,
rem First         = 0x00000010, EFF           = 0x00000020, BNF          = 0x00000040,
rem Formula       = 0x00000100, Rule          = 0x00000200, Output       = 0x00000400, C2A           = 0x00000800, Ahead = C2A,
rem Action        = 0x00001000, TableCpp      = 0x00002000, Cell         = Action,   
rem State         = 0x00010000, StateCore     = 0x00020000, StateSort    = 0x00040000, GoTo          = 0x00080000, 
rem Association   = 0x00100000, Compression   = 0x00200000, AssignOper   = 0x00400000, NoPriorAssign = 0x00800000,
rem Eof2Empty     = 0x10000000
 
TableBuilder 015 1009313F ..\Table\LL_TC_LL1.tab 
TableBuilder 016 10091000 ..\Table\LL_TC_LR0.tab 
TableBuilder 017 10091000 ..\Table\LL_TC_LR0_Core.tab 
TableBuilder 018 10091000 ..\Table\LL_TC_LR1.tab 
TableBuilder 019 10091000 ..\Table\LL_TC_LR1_Core.tab 
TableBuilder 01A 10091000 ..\Table\LL_TC_LALR.tab 
TableBuilder 01B 10091000 ..\Table\LL_TC_Tab.tab 
TableBuilder 01C 10091000 ..\Table\LL_TC_Full.tab 
TableBuilder 01D 10091000 ..\Table\LL_TC_Core.tab 
                    
TableBuilder 035 1009113F ..\Table\LL_SN_LL1.tab 
                    
TableBuilder 216 1009103F ..\Table\LR_TC_LR0.tab 
TableBuilder 217 10091000 ..\Table\LR_TC_LR0_Core.tab 
TableBuilder 218 10091000 ..\Table\LR_TC_LR1.tab 
TableBuilder 219 10091000 ..\Table\LR_TC_LR1_Core.tab 
TableBuilder 21A 10091000 ..\Table\LR_TC_LALR.tab 
TableBuilder 21B 10091000 ..\Table\LR_TC_Tab.tab 
TableBuilder 21C 10091000 ..\Table\LR_TC_Full.tab 
TableBuilder 21D 10091000 ..\Table\LR_TC_Core.tab 
                    
TableBuilder 246 1009303F ..\Table\LR_UR_LR0.tab 
TableBuilder 247 10091000 ..\Table\LR_UR_LR0_Core.tab 
TableBuilder 248 10091000 ..\Table\LR_UR_LR1.tab 
TableBuilder 249 10091000 ..\Table\LR_UR_LR1_Core.tab 
TableBuilder 24A 10091000 ..\Table\LR_UR_LALR.tab 
TableBuilder 24B 10091000 ..\Table\LR_UR_Tab.tab 
TableBuilder 24C 10091000 ..\Table\LR_UR_Full.tab 
TableBuilder 24D 10091000 ..\Table\LR_UR_Core.tab 
                    
rem TableBuilder 316 1009103F ..\Table\NR_TC_LR0.tab 
rem TableBuilder 317 10091000 ..\Table\NR_TC_LR0_Core.tab 
TableBuilder 318 10091000 ..\Table\NR_TC_LR1.tab 
TableBuilder 319 10091000 ..\Table\NR_TC_LR1_Core.tab 
TableBuilder 31A 10091000 ..\Table\NR_TC_LALR.tab 
TableBuilder 31B 10091000 ..\Table\NR_TC_Tab.tab 
TableBuilder 31C 10091000 ..\Table\NR_TC_Full.tab 
TableBuilder 31D 10091000 ..\Table\NR_TC_Core.tab 
                    
rem TableBuilder 336 1009303F ..\Table\NR_SN_LR0.tab 
rem TableBuilder 337 10091000 ..\Table\NR_SN_LR0_Core.tab 
TableBuilder 338 10091000 ..\Table\NR_SN_LR1.tab 
TableBuilder 339 10091000 ..\Table\NR_SN_LR1_Core.tab 
TableBuilder 33A 10091000 ..\Table\NR_SN_LALR.tab 
TableBuilder 33B 10093000 ..\Table\NR_SN_Tab.tab 
TableBuilder 33C 10091000 ..\Table\NR_SN_Full.tab 
TableBuilder 33D 10091000 ..\Table\NR_SN_Core.tab 
