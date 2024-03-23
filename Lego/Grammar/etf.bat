rem   opGrammar     = 0x00000001, opFollow      = 0x00000002, opMaker          = 0x00000004, opLexeme        = 0x00000008,
rem   opFirst       = 0x00000010, opEFF         = 0x00000020, opBNF            = 0x00000040, opBIF           = 0x00000080,
rem   opFormula     = 0x00000100, opAuto        = 0x00000200, opOutput         = 0x00000400, opC2A           = 0x00000800,
rem   opAction      = 0x00001000, opTable       = 0x00002000, opFiUnattainable = 0x00004000, opSplitting     = 0x00008000,
rem   opState       = 0x00010000, opStateCore   = 0x00020000, opStateSort      = 0x00040000, opGoTo          = 0x00080000,
rem   opAssociation = 0x00100000, opCompression = 0x00200000, opNoDefType      = 0x00400000, opNoPriorAssign = 0x00800000,
rem   opChainRule   = 0x01000000, opTrueBIF     = 0x02000000, opLeftFactoring  = 0x04000000, opLeftRecursion = 0x08000000,
rem   opEof2Empty   = 0x10000000,                                                            opSelfParsing   = 0x80000000,
rem   opCell        = opAction  , opAhead = opC2A, opLLk = opC2A, opFiUn = opC2A, opSplittingAddition = opFiUnattainable
..\Exec\TableBuilder.exe 000A00 000910C1 ETF_BIF.tab ETF.bif
..\Exec\TableBuilder.exe 000B00 00091041 ETF_LL_BNF.tab ETF_LL.bnf
..\Exec\TableBuilder.exe 000E00 00091001 ETF_LR_Y.tab ETF_LR.y

