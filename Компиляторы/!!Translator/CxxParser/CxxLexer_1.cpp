//
//	  Title:			C++ Grammar Lexer support compilation unit.
//
//	  File Name:		CxxLexer.cpp
//
//	  Author:			E.D.Willink
//END
//
#include "stdafx.h"

int isatty(int handle) { return 0; }
#define fileno 0
//int fileno(FILE *stream) { return 0; }
extern "C" int yywrap() { return 1; }

#include "CxxLexer.lex.c"
