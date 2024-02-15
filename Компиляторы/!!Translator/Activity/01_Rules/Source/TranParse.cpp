// TranParse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parse.h"
#include "ASyntax.h"
#include "InHelp.h"

// --------------------------- main ---------------------------

int scan_control(A_Syntax &scan)
{
   enum T_Group { grNone, grOper, grSeparator, grInteger, grNumber, grString, grIdent, grReserv, grSpace, grLine, grError, grPriority, grSyntax, grEof };
   int counts[T_Lexeme::T_Group::grEof + 1] = { 0 };
   int count = 0;
	for (;; count++) {
      if        (scan.Match(T_Lexeme::grOper     )) { counts[T_Lexeme::grOper     ]++;
      } else if (scan.Match(T_Lexeme::grSeparator)) { counts[T_Lexeme::grSeparator]++; 
      } else if (scan.Match(T_Lexeme::grInteger  )) { counts[T_Lexeme::grInteger  ]++;
      } else if (scan.Match(T_Lexeme::grNumber   )) { counts[T_Lexeme::grNumber   ]++;
      } else if (scan.Match(T_Lexeme::grString   )) { counts[T_Lexeme::grString   ]++;
      } else if (scan.Match(T_Lexeme::grIdent    )) { counts[T_Lexeme::grIdent    ]++;
      } else if (scan.Match(T_Lexeme::grReserv   )) { counts[T_Lexeme::grReserv   ]++;
      } else if (scan.Match(T_Lexeme::grSpace    )) { counts[T_Lexeme::grSpace    ]++;
      } else if (scan.Match(T_Lexeme::grLine     )) { counts[T_Lexeme::grLine     ]++;
      } else if (scan.Match(T_Lexeme::grError    )) { counts[T_Lexeme::grError    ]++;
      } else if (scan.Match(T_Lexeme::grPriority )) { counts[T_Lexeme::grPriority ]++;
      } else if (scan.Match(T_Lexeme::grSyntax   )) { counts[T_Lexeme::grSyntax   ]++;
      } else if (scan.Match(T_Lexeme::grEof      )) { counts[T_Lexeme::grEof      ]++; break;
      } else {
        if (!scan.Next()) break;
      }
	}

   int g = 0;
   printf("\n");
   for (int item : counts) {
      printf("%s=%d", group_title(T_Lexeme::T_Group(g++)), item);
      if (g <= T_Lexeme::grEof) printf(", ");
   }
   printf("\ncount=%d\n\n", count);

   count = 0;
   for (int &item : counts) item = 0;
   scan.option = 0x0007;
   scan.Reset();

   T_Lexeme lexeme;
   T_Lexeme::T_Group group;
   do {
      count++;
      group = scan.Lex(lexeme);
      counts[lexeme.group]++;
   } while (group != T_Lexeme::grEof);

   g = 0;
   printf("\n");
   for (int item : counts) {
      printf("%s=%d", group_title(T_Lexeme::T_Group(g++)), item);
      if (g <= T_Lexeme::grEof) printf(", ");
   }
   printf("\n");

   return count;
}

int scan_lexeme(A_Syntax &scan)
{
	int count = 0;
	T_Lexeme lexeme;
	T_Lexeme::T_Group group = scan.Lexeme(lexeme);
	while (group != T_Lexeme::grEof) {
      count++;
		group = scan.Lexeme(lexeme);
	}
	return count;
}

int scan_next(A_Syntax &scan)
{
	int count = 0;
	while (scan.Next()) {
      count++;
	}
	return count;
}

int scan_store(A_Syntax &scan)
{
	int count = 0;
	for (;; count++) {
      T_ScanStore store;
      scan.Store(store);
      if (!scan.Next()) break;
      count++;
      scan.Restore(store);
      if (!scan.Next()) break;
	}
	return count;
}

int scan_write(T_Parse &scan, const char *file_name)
{
   char *file_lexeme = get_file_name(file_name,"lex");
   TPrinter printer(file_lexeme, 0x00);
   if (printer.file == NULL) return -1;;

   int count = 0;
   T_Lexeme lexeme;
   T_Lexeme::T_Group group;
	do {
      count++;
      group = scan.Lex(lexeme);
      lexeme.write(printer, &scan.Scan());
   } while (group != T_Lexeme::grEof);

   free(file_lexeme);

   return count;
}

int scan_lexer(A_Syntax &parse, const char *file_name)
{
   int count = 0;
   while (parse.Next()) {
      count++;
   }
   return count;
}

/* ETF.bif
Z        ::=   E

E        ::=   T  [  {  +  |  -  }  T  ]...

T        ::=   F  [  {  *  |  /  }  F  ]...

F        ::=   {  (  E  )  |  Integer  |  Number  |  Ident  }

*/
/* ETF_LL1.bnf
Z        ::=   E                        

E        ::=   T     E_                       

E_       ::=   +     T     E_                       
         |     -     T     E_
         | 

T        ::=   F     T_                       

T_       ::=   *     F     T_                       
         |     /     F     T_
         | 

F        ::=   (  E  )     |  Integer  |  Number  |  Ident  

*/
// -------------------- ETF_Parse --------------------
#define RETURN_TRUE  { leave(p); return true;  }
#define RETURN_FALSE { leave(p, true); return false; }
#define ENTRY(P)     const char* p = #P; entry(#P);

class A_ETF_Parse : public T_Parse 
{
public:
   A_ETF_Parse(T_Scan *s) :T_Parse(s), level(0) { WordTable(&T_KeyWordTable::key_word_table); }
public:
   bool virtual Z();
   bool virtual E() = 0;
   bool virtual T() = 0;
   bool virtual F();
public:
   void entry(const char* p);
   void leave(const char* p, bool e = false);
public:
   int level;
};

bool A_ETF_Parse::Z()
{
   ENTRY(Z);
   if (!E() || !Match(T_Lexeme::T_Group::grEof)) RETURN_FALSE;
   RETURN_TRUE;
}

bool A_ETF_Parse::F()
{
   ENTRY(F);
   if (Match(T_Lexeme::grIdent))   RETURN_TRUE;
   if (Match(T_Lexeme::grInteger)) RETURN_TRUE;
   if (Match(T_Lexeme::grNumber))  RETURN_TRUE;
   if (Match(T_Symbol::lxLeftBracket) && E() && Match(T_Symbol::lxRightBracket)) RETURN_TRUE;
   RETURN_FALSE;
}

void A_ETF_Parse::entry(const char* p)
{
   level++;
   printf("%*c", level * 2, ' ');
   printf("%s\n", p);
}

void A_ETF_Parse::leave(const char* p, bool e)
{
   printf("%*c~", level * 2 - 1, ' ');
   if (e) printf("!");
   printf("%s\n", p);
   level--;
}

class BIF_ETF_Parse : public A_ETF_Parse 
{
public:
   BIF_ETF_Parse(T_Scan *s) :A_ETF_Parse(s) {}
public:
   bool virtual E();
   bool virtual T();
};

bool BIF_ETF_Parse::E()
{
   ENTRY(E);
   if (!T()) RETURN_FALSE;
   while (Match(T_Lexeme::grOper, T_Symbol::lxAdd) || Match(T_Lexeme::grOper, T_Symbol::lxSub)) {
      if (!T()) RETURN_FALSE;
   }
   RETURN_TRUE;
}

bool BIF_ETF_Parse::T()
{
   ENTRY(T);
   if (!F()) RETURN_FALSE;
   while (Match(T_Lexeme::grOper, T_Symbol::lxMulti) || Match(T_Lexeme::grOper, T_Symbol::lxDiv)) {
      if (!F()) RETURN_FALSE;
   }
   RETURN_TRUE;
}

class LL1_ETF_Parse : public A_ETF_Parse 
{
public:
   LL1_ETF_Parse(T_Scan *s) :A_ETF_Parse(s) {}
public:
   bool virtual E();
   bool virtual E_();
   bool virtual T();
   bool virtual T_();
};

bool LL1_ETF_Parse::E()
{
   ENTRY(E);
   if (!T() || !E_()) RETURN_FALSE;
   RETURN_TRUE;
}

bool LL1_ETF_Parse::E_()
{
   ENTRY(E_);
   if (Match(T_Lexeme::grOper, T_Symbol::lxAdd) || Match(T_Lexeme::grOper, T_Symbol::lxSub)) {
      if (!T() || !E_()) RETURN_FALSE;
   }
   RETURN_TRUE;
}

bool LL1_ETF_Parse::T()
{
   ENTRY(T);
   if (!F() || !T_()) RETURN_FALSE;
   RETURN_TRUE;
}

bool LL1_ETF_Parse::T_()
{
   ENTRY(T_);
   if (Match(T_Lexeme::grOper, T_Symbol::lxMulti) || Match(T_Lexeme::grOper, T_Symbol::lxDiv)) {
      if (!F() || !T_()) RETURN_FALSE;
   }
   RETURN_TRUE;
}

#include "C99_Lexer.h"

bool test(int type, int option, const char *file)
{
	T_SourceFile source;
	if (!source.Open(file)) {
      printf("\nfile error : %s", file);
      return false;
   }
	
   if (option & T_OptionMode::omPrintSource) {
   	print_source(source);
	   source.Reset();
   }

	T_Scan scan(&source);
   T_FlexLexer lexer(&source);
   A_Syntax parse(&scan);
   parse.option = option;

   int count = 0;
   switch (type) {
   case 0 :
      count = print_source(source);
      break;
   case 1 :
   	count = scan_source(parse);
      break;
   case 2 :
   	count = scan_next(parse);
      break;
   case 3 :
   	count = scan_control(parse);
      break;
   case 4 :
      parse.syntax_lexeme = T_SyntaxLexeme::slNone;
   	count = scan_lexeme(parse);
      break;
   case 5 :
      parse.syntax_lexeme = T_SyntaxLexeme(T_SyntaxLexeme::slNone | T_SyntaxLexeme::slPrior | T_SyntaxLexeme::slPriorAssign);
   	count = scan_lexeme(parse);
      break;
   case 6 :
      parse.syntax_lexeme = T_SyntaxLexeme::slSyntax;
   	count = scan_lexeme(parse);
      break;
   case 7 :
   	count = scan_store(parse);
      break;
   case 8 : {
   	count = scan_write(parse, file);
      } break;
   case 9: {
      if (!lexer.Open()) return false;
      parse.Scan(&lexer);
      count = scan_lexer(parse, file);
      } break;
   case 0x0A : {
      BIF_ETF_Parse etf_parse(&scan);
      etf_parse.option = option;
      etf_parse.line_is_space = true;
      bool ret = etf_parse.Z();
      } break;
   case 0x0B : {
      LL1_ETF_Parse etf_parse(&scan);
      etf_parse.option = option;
      etf_parse.line_is_space = true;
      bool ret = etf_parse.Z();
      } break;
   }
   printf("\ncount=%d\n", count);

	return true;
}

int main(int argc, const char* argv[])
{
   TInHelp in_help(TInHelp::Parse);
// TranParse.exe 8 4001 zetf.cpp
   in_help.type = 0x08;
   in_help.file = "zetf.cpp";
   in_help.option = 0x4001;

   if (!in_help.input(argc,argv)) return 0;
   test(in_help.type, in_help.option, in_help.file);

	return 0;
}

