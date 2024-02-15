rem Grammar       = 0x00000001, Follow        = 0x00000002, Maker        = 0x00000004, Lexeme        = 0x00000008,
rem First         = 0x00000010, EFF           = 0x00000020, BNF          = 0x00000040,
rem Formula       = 0x00000100, Rule          = 0x00000200, Output       = 0x00000400, C2A           = 0x00000800, Ahead = C2A,
rem Action        = 0x00001000, TableCpp      = 0x00002000, Cell         = Action,   
rem State         = 0x00010000, StateCore     = 0x00020000, StateSort    = 0x00040000, GoTo          = 0x00080000, 
rem Association   = 0x00100000, Compression   = 0x00200000, AssignOper   = 0x00400000, NoPriorAssign = 0x00800000,
rem Eof2Empty     = 0x10000000
 
TableBuilder 015 000931BF ..\Table\LL_TC_LL1.tab 
TableBuilder 035 000911BF ..\Table\LL_SN_LL1.tab 

TableBuilder 018 00091000 ..\Table\LL_TC_LR1.tab 

TableBuilder 218 000931BF ..\Table\LR_TC_LR1.tab 
TableBuilder 248 00091000 ..\Table\LR_UR_LR1.tab 

TableBuilder 318 000931BF ..\Table\NR_TC_LR1.tab 
TableBuilder 338 00091000 ..\Table\NR_SN_LR1.tab 

rem NoPriorAssign = 0x00800000
TableBuilder 015 008931BF ..\Table\LL_TC_LL1_NPA.tab 
TableBuilder 035 008911BF ..\Table\LL_SN_LL1_NPA.tab 

TableBuilder 018 00891000 ..\Table\LL_TC_LR1_NPA.tab 

TableBuilder 218 008931BF ..\Table\LR_TC_LR1_NPA.tab 
TableBuilder 248 00891000 ..\Table\LR_UR_LR1_NPA.tab 

rem Association   = 0x00100000
TableBuilder 218 001931BF ..\Table\LR_TC_LR1_ASS.tab 
TableBuilder 248 00191000 ..\Table\LR_UR_LR1_ASS.tab 
