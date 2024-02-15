#ifndef TRN_FSYNTAX_H
#define TRN_FSYNTAX_H

#include "Parse.h"
#include "ASyntax.h"
#include "RSyntax.h"
#include "GSyntax.h"

// --------------------------- FSyntax ---------------------------

class TTokenTable : public TTokenNames {
public:
   TTokenTable() :Enum_name(NULL) {}
public:
   const char* Enum_name;

   int Add(const char* name, int index);
   int Token(const char* name) const;

public:
   void print(TPrinter& printer) const;
};

class MyTable {
public:
	TTokenTable lexemes;
   //TTokenTable enums;
   //TTokenTable names;

public:
   void print(TPrinter& printer) const;
public:
   std::vector<TTokenTable> enums;
};

class FSyntax : public A_Syntax, public MyTable {
public:
	FSyntax(T_Scan *s) : A_Syntax(s) {}

	bool error(T_Error code, int value = 0) { return error(code,lex,value); }
	bool error(T_Error code, const T_Lexeme &l, int value) {  return Error.error(code,l,value); }
   
   bool Enums();
	bool Tokens();
   bool Formulas();
   bool Formula();
   bool Produce();
	
   bool param_to_int(int*);
   bool get_param(int&);
   bool get_integer(int&);
   bool skip_error(bool check_ident, int n, T_Symbol::T_Type, ...);

	virtual bool Translate();
};

class MyYSyntax : public A_Syntax, public MyTable {
public:  
   MyYSyntax(T_Scan *s) : A_Syntax(s) {}
   
   bool MakerYACC(const GSymbol& sym, T_Lexeme_SNode* S0, T_Lexeme_SNode* S1, int maker_index = -1);

   virtual bool ParseYACC();

   virtual bool Translate();
};

//enum T_TypeIdent { tiNone, tiToken, tiMake, tiNode, tiCode, tiTree, tiYacc, tiAll, tiTurn, tiClass };

// --------------------------- GrammarSyntax ---------------------------

class GrammarSyntax : public GSyntax, public MyTable
{
public:
   GrammarSyntax(T_Scan *s, TGrammar* g) :GSyntax(s, g), state(T_State::tsNone) {}
   virtual T_Lexeme::T_Group Lexeme(T_Lexeme &l);

   bool Grammar();
   bool Enums(SNode* list);
   bool Tokens(SNode* list);
   bool Formulas(SNode* list);
   int  Formula(SNode* list);
   bool Produce(GFormula* formula, SNode* list);
   bool check_param(SNode* produce_node, int* param_number);
   bool param_to_int(T_Lexeme param, SNode* param_node, int* param_int);
public:
   virtual bool LexemeToSymbol(T_Lexeme& lexeme, GSymbol& sym);
   virtual bool IsSaved(const T_Lexeme& lexeme) const;
public:
   enum T_State { tsNone, tsYACCHead, tsBNFProduce, tsBNFMaker, tsBIFProduce, tsBIFMaker, tsSQLProduce };
   T_State state;
public:
   T_Lexeme error_lex;
};

#endif



