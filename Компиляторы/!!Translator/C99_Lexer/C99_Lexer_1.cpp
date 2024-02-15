// C99_Lexer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

void yyerror(const char *s);
void error(const char *s) { yyerror(s); }

#include "C99_Lexer.lex.c"

void yyerror(char const *s)
{
   fflush(stdout);
   printf("\n%s",s);
//   printf("\n%*s\n%*s\n", column, "^", column, s);
}

#include "Parse.h"

#define TOKEN_WORD(C,T)      { int t = T_Lexeme::T_Group::grReserv << 8 | T_Lexeme::W_Type::rw##T;    printf("\n   %-20s = 0x%04X,",#C,t); }
#define TOKEN_OPER(C,T)      { int t = T_Lexeme::T_Group::grOper << 8 | A_Symbol::T_Type::lx##T;      printf("\n   %-20s = 0x%04X,",#C,t); }
#define TOKEN_SEPORATOR(C,T) { int t = T_Lexeme::T_Group::grSeparator << 8 | A_Symbol::T_Type::lx##T; printf("\n   %-20s = 0x%04X,",#C,t); }
#define TOKEN_LEXEME(C,G,T)  { int t = T_Lexeme::T_Group::gr##G << 8 | T;                             printf("\n   %-20s = 0x%04X,",#C,t); }

void token()
{

   TOKEN_LEXEME(IDENTIFIER, Ident, 0)
   TOKEN_LEXEME(CONSTANT, Integer, 0)
   TOKEN_LEXEME(STRING_LITERAL, String, 0)

   TOKEN_OPER(INC_OP, PlusPlus)
   TOKEN_OPER(DEC_OP, MinusMinus)
   TOKEN_OPER(LEFT_OP, LShift)
   TOKEN_OPER(RIGHT_OP, RShift)
   TOKEN_OPER(LE_OP, LE)
   TOKEN_OPER(GE_OP, GE)
   TOKEN_OPER(EQ_OP, Equ)
   TOKEN_OPER(NE_OP, NotEqu)
   TOKEN_OPER(ANDAND_OP, AndAnd)
   TOKEN_OPER(OROR_OP,  OrOr)
   TOKEN_OPER(AND_OP,   And)
   TOKEN_OPER(NOT_OP,   Not)
   TOKEN_OPER(TILDA_OP, Tilda)
   TOKEN_OPER(SUB_OP,   Sub)
   TOKEN_OPER(ADD_OP ,  Add )
   TOKEN_OPER(MULTI_OP, Multi)
   TOKEN_OPER(DIV_OP, Div)
   TOKEN_OPER(MOD_OP, Mod)
   TOKEN_OPER(LT_OP,  LT)
   TOKEN_OPER(GT_OP,  GT)
   TOKEN_OPER(XOR_OP, XOr)
   TOKEN_OPER(OR_OP,  Or)
   TOKEN_OPER(QUEST_OP, Question)

   TOKEN_OPER(ASSIGN, Assign)
   TOKEN_OPER(MUL_ASSIGN, MultiAssign)
   TOKEN_OPER(MUL_ASSIGN, MultiAssign)
   TOKEN_OPER(DIV_ASSIGN, DivAssign)
   TOKEN_OPER(MOD_ASSIGN, ModAssign)
   TOKEN_OPER(ADD_ASSIGN, AddAssign)
   TOKEN_OPER(SUB_ASSIGN, SubAssign)
   TOKEN_OPER(LEFT_ASSIGN, LShiftAssign)
   TOKEN_OPER(RIGHT_ASSIGN, RShiftAssign)
   TOKEN_OPER(AND_ASSIGN, AndAssign)
   TOKEN_OPER(XOR_ASSIGN, XOrAssign)
   TOKEN_OPER(OR_ASSIGN, OrAssign)

   TOKEN_SEPORATOR(ELLIPSIS, Ellipsis)
   TOKEN_SEPORATOR(PTR_OP, Pointer)
   TOKEN_SEPORATOR(POINT, Point)
   TOKEN_SEPORATOR(COMMA, Comma)

   TOKEN_SEPORATOR(SEMICOLON,Semicolon)
   TOKEN_SEPORATOR(LCRAMP,LeftCramp)
   TOKEN_SEPORATOR(RCRAMP,RightCramp)
   TOKEN_SEPORATOR(COLON,Colon)
   TOKEN_SEPORATOR(LBRACKET,LeftBracket)
   TOKEN_SEPORATOR(RBRACKET,RightBracket)
   TOKEN_SEPORATOR(LSCRAPE,LeftScrape)
   TOKEN_SEPORATOR(RSCRAPE,RightScrape)

   TOKEN_WORD(TYPEDEF, Typedef)
   TOKEN_WORD(EXTERN, Extern)
   TOKEN_WORD(STATIC, Static)
   TOKEN_WORD(AUTO, Auto)
   TOKEN_WORD(REGISTER, Register)
   TOKEN_WORD(CHAR_DEF, Char)
   TOKEN_WORD(SHORT_DEF, Short)
   TOKEN_WORD(INT_DEF, Int)
   TOKEN_WORD(LONG_DEF, Long)
   TOKEN_WORD(SIGNED, Signed)
   TOKEN_WORD(UNSIGNED, Unsigned)
   TOKEN_WORD(FLOAT_DEF, Float)
   TOKEN_WORD(DOUBLE_DEF, Double)
   TOKEN_WORD(CONST, Const)
   TOKEN_WORD(VOLATILE, Volatile)
   TOKEN_WORD(VOID, Void)
   TOKEN_WORD(STRUCT, Struct)
   TOKEN_WORD(UNION, Union)
   TOKEN_WORD(ENUM, Enum)
   TOKEN_WORD(SIZEOF, Sizeof)
   TOKEN_WORD(CASE, Case)
   TOKEN_WORD(DEFAULT, Default)
   TOKEN_WORD(IF, If)
   TOKEN_WORD(ELSE, Else)
   TOKEN_WORD(SWITCH, Switch)
   TOKEN_WORD(WHILE, While)
   TOKEN_WORD(DO, Do)
   TOKEN_WORD(FOR, For)
   TOKEN_WORD(GOTO, GoTo)
   TOKEN_WORD(CONTINUE, Continue)
   TOKEN_WORD(BREAK, Break)
   TOKEN_WORD(RETURN, Return)

   TOKEN_WORD(BOOL_DEF,  Bool);
   TOKEN_WORD(COMPLEX,   Complex);
   TOKEN_WORD(IMAGINARY, Imaginary);
   TOKEN_WORD(INLINE,    Inline);
   TOKEN_WORD(RESTRICT,  Restrict);

   TOKEN_WORD(TYPE_NAME, Define)

   printf("\n\n");

}


int main() {

//   token();

   std::ifstream ifs;
   std::ofstream ofs;

   ifs.open("test_const.cpp", std::ifstream::in);
   ofs.open("test.out", std::ifstream::out);

   yyFlexLexer lexer;// (&ifs, NULL);
   lexer.switch_streams(ifs, ofs);// std::cout);
   lexer.column = 0;
   lexer.unterminated_comment = false;

   while (int token = lexer.yylex())
   {
      printf("%04X %03d %03d %03d %s\n", token, lexer.lineno() - 1, lexer.column - lexer.YYLeng(), lexer.YYLeng(), lexer.YYText());
   }

   ifs.close();
   ofs.close();

   return 0;
}
