
#include "stdafx.h"

#include "YSyntax.h"
#include "TSemantic.h"

// --------------------------- YSyntax ---------------------------

bool YSyntax::MakerYACC(const GSymbol& sym, T_Lexeme_SNode* S0, T_Lexeme_SNode* S1, int maker_index)
{
   const int S_count = 15;
   T_Lexeme_SNode* data_stack[S_count] = {};
   for (int s = 1; s < S_count; s++) {
      data_stack[s] = S1 + s - 1;
   }
   data_stack[0] = S0;
   return MakerSyntaxNode(sym,data_stack,maker_index);
}

bool YSyntax::Translate()
{
   bool ret = false;
   if (!Match(T_Lexeme::grEof)) {
//      syntax_lexeme = T_SyntaxLexeme::slNone;
      ret = ParseYACC();
   } else {
      ret = true;
   }
   return ret;
}

// --------------------------- ParseYACC ---------------------------
int yylex (void *yylval, void *param)
{
   YSyntax* syntax = (YSyntax*)param; 
   T_Lexeme current_lexeme;
   syntax->Lexeme(current_lexeme);
   (*(T_Lexeme_SNode*)yylval).lexeme = current_lexeme;
   int token = !current_lexeme.Match(T_Lexeme::grEof) ? ((current_lexeme.group << 8) | current_lexeme.type) : 0;
   return token;
}

void yyerror(const char* mess)
{
   printf("%s\n",mess);
}

bool YSyntax::ParseYACC()
{
   int ret = 1; 
   if (!yy_parse) return !ret;
   if (ACTION(Tree) || ACTION(Code)) {
      ret = yy_parse(this);
   } else if (ACTION(Node) || ACTION(Made)) {
      ret = yy_parse(this);
   } else if (ACTION(None)) {
      ret = yy_parse(this);
   }

   return !ret;
}

#define CHAR_LEX(G,T,S)  case (T_Lexeme::gr##G << 8) | T_Symbol::lx##T : current_lexeme.set(T_Lexeme::grNone,S); break;

T_Lexeme::T_Group C_GrammarYSyntax::Lexeme(T_Lexeme &l)
{
   T_Lexeme& current_lexeme = l;
   A_Syntax::Lexeme(current_lexeme);
   UpdateLexeme(current_lexeme);

   int token = !current_lexeme.Match(T_Lexeme::grEof) ? ((current_lexeme.group << 8) | current_lexeme.type) : 0;
   switch (token) {
	CHAR_LEX(Oper,      Or,          '|');
	CHAR_LEX(Oper,      And,         '&');
	CHAR_LEX(Oper,      XOr,         '^');
	CHAR_LEX(Oper,      Tilda,       '~');
	CHAR_LEX(Oper,      Multi,       '*'); 
	CHAR_LEX(Oper,      Div,         '/');
	CHAR_LEX(Oper,      Mod,         '%');
	CHAR_LEX(Oper,      Add,         '+');
	CHAR_LEX(Oper,      Sub,         '-');
	CHAR_LEX(Oper,      Assign,      '=');
	CHAR_LEX(Oper,      Not,         '!');
	CHAR_LEX(Oper,      LT,          '<');
	CHAR_LEX(Oper,      GT,          '>');
	CHAR_LEX(Oper,      Question,    '?');
	CHAR_LEX(Separator, LeftCramp   ,'{');
	CHAR_LEX(Separator, RightCramp  ,'}');
	CHAR_LEX(Separator, LeftBracket ,'(');
	CHAR_LEX(Separator, RightBracket,')');
	CHAR_LEX(Separator, LeftScrape  ,'[');
	CHAR_LEX(Separator, RightScrape ,']');
	CHAR_LEX(Separator, Point,       '.');
	CHAR_LEX(Separator, Semicolon,   ';');
	CHAR_LEX(Separator, Colon,       ':');
	CHAR_LEX(Separator, Comma,       ',');
   }
   return l.group;
}
