:TrueBIF
TableBuilder.exe 0x0000F0 0x000000C1 ..\Table\LL_BIF.grammar
TableBuilder.exe 0x000AF4 0x02000101 ..\Table\LL_TRUE_BIF_PROG.tab ..\Table\LL_BIF.grammar
copy ..\Table\LL_TRUE_BIF_PROG.h       ..\Generated\LL_TRUE_BIF_PROG.h
copy ..\Table\LL_TRUE_BIF_PROG.cpp     ..\Generated\LL_TRUE_BIF_PROG.cpp
