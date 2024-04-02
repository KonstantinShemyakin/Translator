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

DECLARE_PRINT_TITLE(print_names)
DECLARE_PRINT_TITLE(func_item_title)
DECLARE_PRINT_TITLE(func_snode_turn)
DECLARE_PRINT_TITLE(print_title_action)
DECLARE_PRINT_TITLE(title_alloc_type)
DECLARE_PRINT_TITLE(print_quadruple_title)
DECLARE_PRINT_TITLE(print_command_title)

int print_title(const char *file_name)
{
   char *file_title = get_file_name(file_name,"title");
   TPrinter printer(file_title, 0x00);
   if (printer.file == NULL) return -1;;
   int count = 0;

   count += print_names(printer);
   count += func_item_title(printer);
   count += func_snode_turn(printer);
   count += print_title_action(printer);
   count += title_alloc_type(printer);
   count += print_quadruple_title(printer);
   count += print_command_title(printer);

   free(file_title);

	return count;
}

int print_lexeme(const char *file_name, int mask)
{
   char *file_sym = get_file_name(file_name,"lexeme");
   TPrinter printer(file_sym, 0x00);
   if (printer.file == NULL) return -1;;
   PRINTER_FILE_MODE 

   int count = 0;

   int index = -1;
   for (const T_Symbol symbol : symbol_table().table) {
      index++;
      if (!symbol.text) continue;
      if (!(symbol.mask & mask)) continue;
      T_Lexeme lexeme;
      lexeme.group = symbol.group; lexeme.type = symbol.type; lexeme.value = index; 
      lexeme.text = symbol.text; lexeme.len = strlen(lexeme.text);
      lexeme.write(printer);
   }

   index = -1;
   for (const T_Symbol symbol : symbol_table().table) {
      index++;
      if (!symbol.text || !symbol.priority) continue;
      if (!(symbol.mask & mask)) continue;
      T_Lexeme lexeme;
      lexeme.group = T_Lexeme::grPriority; lexeme.type = symbol.priority; lexeme.value = index;
      lexeme.text = symbol.text; lexeme.len = strlen(lexeme.text);
      lexeme.write(printer);
   }

   const T_WordTable& table = T_KeyWordTable::T_KeyWordTable();

   for (int i = 0; i < table.count; i++) {
      const T_Word& item = table.Word(i);
      if (!(item.mask & mask)) continue;
      T_Lexeme lexeme;
      lexeme.group = T_Lexeme::grReserv; lexeme.type = item.type; lexeme.value = i;
      lexeme.text = item.text; lexeme.len = strlen(item.text);
      lexeme.write(printer);
   }

   free(file_sym);

	return count;
}

int print_C(const char *file_name, int mask)
{
   char *file_sym = get_file_name(file_name,"c");
   TPrinter printer(file_sym, 0x00);
   if (printer.file == NULL) return -1;;
   PRINTER_FILE_MODE 

   int count = 0;

   int index = -1;
   for (const T_Symbol symbol : symbol_table().table) {
      index++;
      if (!symbol.text) continue;
      if (!(symbol.mask & mask)) continue;
      fprintf(file,"%s\n", symbol.text);
   }

   const T_WordTable& table = T_KeyWordTable::T_KeyWordTable();

   for (int i = 0; i < table.count; i++) {
      const T_Word& item = table.Word(i);
      if (!(item.mask & mask)) continue;
      fprintf(file,"%s\n", item.text);
   }

   free(file_sym);

   return count;
}

int print_symbol(const char *file_name)
{
   char *file_sym = get_file_name(file_name,"sym");
   TPrinter printer(file_sym, 0x00);
   if (printer.file == NULL) return -1;;
   PRINTER_FILE_MODE 

   int count = 0;

   for (const T_Symbol symbol : symbol_table().table) {
      if (!symbol.text) continue;
      int len_group = strlen(group_title(symbol.group));
      int len_type = strlen(lexeme_type_title(symbol.type));
      int len_priority = strlen(lexeme_priority_title(symbol.priority));
      fprintf(file,"%s%*c %s%*c %s%*c 0x%08X %s",  
         group_title(symbol.group), 10-len_group, ' ', 
         lexeme_type_title(symbol.type), 15-len_type, ' ', 
         lexeme_priority_title(symbol.priority), 10-len_priority, ' ', 
         symbol.mask, 
         symbol.text);
      fprintf(file,"\n");
   }
   fprintf(file,"\n\n");

   for (const T_Symbol symbol : symbol_table().table) {
      if (!symbol.text) continue;
      fprintf(file,"%02d %02d %02d 0x%08X %s", symbol.group, symbol.type, symbol.priority, symbol.mask, symbol.text);
      fprintf(file,"\n");
   }

   for (const T_Symbol symbol : symbol_table().table) {
      if (!symbol.text) continue;
      fprintf(file,"%02d %02d %02d %08d %s", symbol.group, symbol.type, symbol.priority, symbol.mask, symbol.text);
      fprintf(file,"\n");
   }

   for (const T_Symbol symbol : symbol_table().table) {
      if (!symbol.text) continue;
      fprintf(file,"(%2d, %2d, %2d, %8d, \"%s\")", symbol.group, symbol.type, symbol.priority, symbol.mask, symbol.text);
      fprintf(file,"\n");
   }

   for (const T_Symbol symbol : symbol_table().table) {
      if (!symbol.text) continue;
      fprintf(file,"p.Add(%02d, %02d, %02d, %08d, \"%s\");", symbol.group, symbol.type, symbol.priority, symbol.mask, symbol.text);
      fprintf(file,"\n");
   }

   free(file_sym);

	return count;
}

int print_word(const char *file_name)
{
   char *file_sym = get_file_name(file_name,"key");
   TPrinter printer(file_sym, 0x00);
   if (printer.file == NULL) return -1;;
   PRINTER_FILE_MODE

   int count = 0;
   const T_WordTable& table = T_KeyWordTable::T_KeyWordTable();

   for (int i = 0; i < table.count; i++) {
      const T_Word& item = table.Word(i);
      int len_title = strlen(item.title);
      fprintf(file,"%02d %s%*c 0x%08X %s", item.type, item.title, 15-len_title, ' ',item.mask, item.text);
      fprintf(file,"\n");
   }
   fprintf(file,"\n\n");

   for (int i = 0; i < table.count; i++) {
      const T_Word& item = table.Word(i);
      fprintf(file,"(%2d, %8d, \"%s\")", item.type, item.mask, item.text);
      fprintf(file,"\n");
   }

   free(file_sym);

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
      group = scan.Lexeme(lexeme);
      if (!lexeme.Match(T_Lexeme::grSpace) && !lexeme.Match(T_Lexeme::grLine)) {
         lexeme.write(printer, &scan.Scan());
      }
   } while (group != T_Lexeme::grEof);

   free(file_lexeme);

   return count;
}

int scan_read(T_Parse &scan, const char *file_name)
{
   int count = 0;
   char *file_lexeme = get_file_name(file_name,"lex");
   TPrinter printer(file_lexeme, 0x00);
   if (printer.file == NULL) return -1;;

   T_Lexeme lexeme;
   T_Lexeme::T_Group group;
	do {
      count++;
      group = scan.Lex(lexeme);
//      lexeme.write(printer, &scan.Scan());
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

enum TLex { a1, a2, a3, };

bool test(int type, int option, const char *file)
{
   A_Symbol::M_Mask mask(A_Symbol::M_Mask(A_Symbol::mmC | A_Symbol::mmC_99)); // A_Symbol::mmAll

   int count = 0;
   if (type == 0x0D) {
   	count = print_title(file);
   	count = print_symbol(file);
   	count = print_word(file);
   	count = print_lexeme(file, mask);
   	count = print_C(file, mask);
      return true;
      } 
   
   T_SourceFile source;

   T_Scan scan(&source);
   T_FlexLexer lexer(&source);
   TFileLexer filer(&source);
   A_Syntax parse(&scan);
   parse.option = option;
   parse.Mask(mask);
   parse.Source(source,file);

   switch (type & 0x00FF) {
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
      parse.syntax_lexeme = T_SyntaxLexeme::slNoDefType;
   	count = scan_lexeme(parse);
      break;
   case 5 :
      parse.syntax_lexeme = T_SyntaxLexeme(T_SyntaxLexeme::slPrior | T_SyntaxLexeme::slPriorAssign);
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
      parse.syntax_lexeme = T_SyntaxLexeme(type >> 8);
   	count = scan_write(parse, file);
      } break;
   case 0x09 : { // FlexLexer
      if (!lexer.Open()) return false;
      parse.Scan(&lexer);
      count = scan_lexer(parse, file);
      } break;
   case 0x0C : { // FileLexer
      parse.Scan(&filer);
      count = scan_read(parse, file);
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
   in_help.type = 0x0C;
   in_help.file = "test.cpp";
   in_help.option = 0x4001;

   in_help.type = 0x0D;
   in_help.file = "scanner";
/*
// TranParse.exe 6 01000001 test_group.cpp
   in_help.type = 4;
   in_help.option = 0x01000008;
   in_help.file = "test.cpp";

// TranParse.exe 8 0001 scaner.c
   in_help.option = 0x0001;
   in_help.type = 0x08;
   in_help.file = "scaner.c";
*/
// TranParse.exe 0x00047008 8 test_g.cpp
   int syntax_lexeme = T_SyntaxLexeme::slNoDefArrVar | T_SyntaxLexeme::slSyntax;
   syntax_lexeme |= T_SyntaxLexeme::slPrior | T_SyntaxLexeme::slPriorAssign;
   syntax_lexeme |= T_SyntaxLexeme::slNoDefType;
   in_help.type = (syntax_lexeme << 8) | 0x08;
   in_help.option = 0x00000008;
   in_help.file = "test_g.cpp";

   if (!in_help.input(argc,argv)) return 0;
   test(in_help.type, in_help.option, in_help.file);

	return 0;
}

