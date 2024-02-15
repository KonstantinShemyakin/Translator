#include "stdafx.h"

#include "C99_Lexer.h"

void yyerror(const char *s);
void error(const char *s) { yyerror(s); }

#include "C99_Lexer.lex.c"

void yyerror(char const *s)
{
//   fflush(stdout);
//   printf("\n%*s\n%*s\n", column, "^", column, s);
}

#include "Parse.h"

// ------------ T_FlexLexer -----------
class myFlexLexer : public yyFlexLexer {
public:
   myFlexLexer(T_Source *s) :source(s) {}
   virtual int LexerInput(char* buf, int max_size);
public:
   T_Source* source;
};

T_FlexLexer::T_FlexLexer(T_Source *s) : TScanArray(s), lexer(NULL), source(s)
{}

T_FlexLexer::~T_FlexLexer()
{
   if (lexer) delete lexer; lexer = NULL;
}

bool T_FlexLexer::Open()
{
   lexer = new myFlexLexer(source);
   lexer->column = 0;
   lexer->unterminated_comment = false;
   return true;
}

int myFlexLexer::LexerInput(char* buf, int max_size)
{
   int sym;
   int len = 0;
   while (max_size-- > 0) {
      T_Source::T_Sym type = source->Read(sym);
      if (type == T_Source::slEof) break;
      buf[len++] = sym;
   }
   return len;
}

static int char_value(const char* buf)
{
   int value = 0;
   buf++;
   char sym = buf[0];
   if (sym == '\'') {
      return value; // error ''
   } else {
      if (sym == '\\') {
         buf++; sym = buf[0];
         switch (sym) {
         case 't': sym = 0x09; break;
         case 'n': sym = 0x0A; break;
         case 'r': sym = 0x0D; break;
         case 'v': sym = 0x0B; break;
         case '0': sym = 0x00; break;
         }
      }
      value = sym;
      buf++; sym = buf[0];
      if (sym == '\'') {
         // 'X'
      } else {
         // error 'X
      }
   }
   return value;
}

T_Lexeme::T_Group T_FlexLexer::LexMake(T_Lexeme &l)
{
   int token = lexer->yylex();
   l.line = lexer->lineno() - 1; l.len = lexer->YYLeng(); l.text = lexer->YYText();
   T_Lexeme::T_Group group = T_Lexeme::T_Group((token & 0xFF00) >> 8);
   int type = token & 0x00FF; 
   l.group = group; l.type = type;

   if ((group == T_Lexeme::grOper) || (group == T_Lexeme::grSeparator)) {
      l.value = symbol_table().Symbol(type).index;
      const T_Symbol& symbol = symbol_table().Symbol(l.value);
      l.text = symbol.text;
   } else if (group == T_Lexeme::grIdent) {
      if (!T_KeyWordTable::key_word_table.Find(l)) {
         l.value = names.Add(l.text, l);
      }
   } else if (group == T_Lexeme::grInteger) {
      // CONSTANT  = 0x0300, CONST_DEC = 0x0301, CONST_OCT = 0x0302, CONST_HEX = 0x0303, CONST_CHAR = 0x0304
      long l_val; char* str_end;
      if (type == 0x01) {
         l_val = atoi(l.text);
      } else if (type == 0x02) {
         l_val = strtol(l.text, &str_end, 8);
      } else if (type == 0x03) {
         l_val = strtol(l.text, &str_end, 16);
      } else if (type == 0x04) {
         l_val = char_value(l.text);
      }
      names.Add(l.text, l);
      l.type = 0;
      l.value = Integer(l_val);
   } else if (group == T_Lexeme::grNumber) {
      // CONST_NUM = 0x0400, CONST_NUM_1 = 0x0401, CONST_NUM_2 = 0x0402, CONST_NUM_HEX = 0x0403, CONST_NUM_HEX_1 = 0x0404, CONST_NUM_HEX_2 = 0x0405
      double number = atof(l.text);
      names.Add(l.text, l);
      l.type = 0;
      l.value = Number(number);
   } else if (group == T_Lexeme::grString) {
      l.value = names.Add(l.text, l);
   } else if (group == T_Lexeme::grReserv) {
      l.value = T_KeyWordTable::key_word_table.Index((T_Lexeme::W_Type)type);
      const T_Word& word = T_KeyWordTable::key_word_table.Word(l.value);
      if (!(word.mask & mask) || (word.mask & (mask << 16))) {
         l.value = names.Add(l.text, l);
         l.group = T_Lexeme::grIdent; l.type = 0;
      } else {
         l.text = word.text;
      }
   } else if (group == T_Lexeme::grNone) {
      if (lexer->unterminated_comment) {
         l.group = T_Lexeme::grError;
         lexer->unterminated_comment = false;
      } else {
         l.group = T_Lexeme::grEof;
      }
      l.len = 0;
   } else {
   }
   l.column = lexer->column - l.len;

   return l.group;
}

