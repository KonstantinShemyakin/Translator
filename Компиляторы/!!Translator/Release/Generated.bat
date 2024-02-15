rem  C99_Lexer.lex.c
rem C99_Lexer.tab.h
rem C_Grammar.tab.cpp

TableBuilder 015 10093000 ..\Table\LL_TC_LL1.tab 
TableBuilder 246 10093000 ..\Table\LR_UR_LR0.tab 
TableBuilder 33A 10093000 ..\Table\NR_SN_LALR.tab 

copy ..\Table\LL_TC_LL1.cpp  ..\Generated\LL_TC_LL1.cpp
copy ..\Table\LR_UR_LR0.cpp  ..\Generated\LR_UR_LR0.cpp
copy ..\Table\NR_SN_LALR.cpp ..\Generated\NR_SN_LALR.cpp
     
..\Release\TableBuilder 01E 00B91000 ..\Table\LL_TC_YACC.y  
..\Release\TableBuilder 21E 00B91000 ..\Table\LR_TC_YACC.y  
..\Release\TableBuilder 32E 00391000 ..\Table\NR_TC_YACC.y  
..\Release\TableBuilder 33E 00391000 ..\Table\NR_SN_YACC.y

..\YACC\win_bison.exe -l -t -o ..\Generated\LL_TC_YACC.tab.c ..\Table\LL_TC_YACC.y
..\YACC\win_bison.exe -l -t -o ..\Generated\LR_TC_YACC.tab.c ..\Table\LR_TC_YACC.y
..\YACC\win_bison.exe -l -t -o ..\Generated\NR_TC_YACC.tab.c ..\Table\NR_TC_YACC.y
..\YACC\win_bison.exe -l -t -o ..\Generated\NR_SN_YACC.tab.c ..\Table\NR_SN_YACC.y

..\Release\TableBuilder 014 00391000 ..\Table\LL_TC_PROG.tab 
copy ..\Table\LL_TC_PROG.h       ..\Generated\LL_TC_PROG.h
copy ..\Table\LL_TC_PROG.cpp     ..\Generated\LL_TC_PROG.cpp
..\Release\TableBuilder 114 00391000 ..\Table\NL_TC_PROG.tab 
copy ..\Table\NL_TC_PROG.h       ..\Generated\NL_TC_PROG.h
copy ..\Table\NL_TC_PROG.cpp     ..\Generated\NL_TC_PROG.cpp
..\Release\TableBuilder 514 00091000 ..\Table\ETF_LL_TC_PROG.tab 
copy ..\Table\ETF_LL_TC_PROG.h   ..\Generated\ETF_LL_TC_PROG.h
copy ..\Table\ETF_LL_TC_PROG.cpp ..\Generated\ETF_LL_TC_PROG.cpp

..\YACC\win_bison.exe -l -t -o ..\Generated\FGrammar.tab.c ..\Grammar\FGrammar.yacc

..\Release\TableBuilder 0x000E38 0x00003101 ..\Table\FGrammar.tab ..\Grammar\FGrammar.y
copy ..\Table\FGrammar.cpp ..\Generated\FGrammar.cpp
..\Release\TableBuilder 0x020E38 0x00003101 ..\Table\BGrammar.tab ..\Grammar\BGrammar.y
copy ..\Table\BGrammar.cpp ..\Generated\BGrammar.cpp
..\Release\TableBuilder 0x020E38 0x00003101 ..\Table\IGrammar.tab ..\Grammar\IGrammar.y
copy ..\Table\IGrammar.cpp ..\Generated\IGrammar.cpp

..\Release\TableBuilder 0x020A45 0x00002141 ..\Table\IGrammarBIF.tab ..\Grammar\IGrammarLLk.bif
copy ..\Table\IGrammarBIF.cpp ..\Generated\IGrammarBIF.cpp
