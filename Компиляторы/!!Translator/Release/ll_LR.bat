:TrueBIF
TableBuilder.exe 0x0002F0 0x000000C1 ..\Table\LR_BIF.grammar
TableBuilder.exe 0x000AF4 0x02000101 ..\Table\LR_TRUE_BIF_PROG.tab ..\Table\LR_BIF.grammar
copy ..\Table\LR_TRUE_BIF_PROG.h       ..\Generated\LR_TRUE_BIF_PROG.h
copy ..\Table\LR_TRUE_BIF_PROG.cpp     ..\Generated\LR_TRUE_BIF_PROG.cpp
