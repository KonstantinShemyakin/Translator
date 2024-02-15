#ifndef TRN_LEXER_H
#define TRN_LEXER_H

#include "Parse.h"
#include <fstream>      // std::ifstream

class myFlexLexer;
class T_FlexLexer : public TScanArray
{
public:
   T_FlexLexer(T_Source *s = NULL);
   ~T_FlexLexer();
   virtual T_Lexeme::T_Group LexMake(T_Lexeme &l);
   bool Open();
protected:
   myFlexLexer* lexer;
   T_Source*    source;
};

#endif