//
//	  Title:			C++ Grammar Parser support compilation unit.
//
//	  File Name:		CxxParser.cpp
//
//	  Author:			E.D.Willink
//END
//

// CxxParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int yydebug = 1;
void yyerror(const char *s);
int  yylex();

#include "C99_Grammar.tab.c"

extern FILE *yyin, *yyout;

int main()
{
   FILE *file = NULL;
   const char* title = "test.cpp";
   int err = fopen_s(&file, title, "r");
   if (!file) {
      printf("\nfile error : %s", title);
      return false;
   }

   yyin = file;
//   while ( yylex());

   int i = yyparse();

   fclose(file);
}


