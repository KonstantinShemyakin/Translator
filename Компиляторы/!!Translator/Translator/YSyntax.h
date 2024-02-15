#ifndef TRN_YSYNTAX_H
#define TRN_YSYNTAX_H

#include "Maker.h"
#include "CGrammar.h"

// --------------------------- YSyntax ---------------------------
class YSyntax : public MC_Syntax, public S_Syntax
{
public:
   YSyntax(T_Scan *s, TGrammar* g) :MC_Syntax(s), S_Syntax(g), tree(NULL), yy_parse(NULL) {}

   bool MakerYACC(const GSymbol& sym, T_Lexeme_SNode* S0, T_Lexeme_SNode* S1, int maker_index = -1);
	virtual bool error_code(T_Error code, int value = 0) { return A_Syntax::error(code,value); }

   virtual bool ParseYACC();
   virtual void Tree(SNode* node) { tree = node; }
   virtual SNode* Tree()          { return tree; }

   virtual bool Translate();
public:
   SNode* tree;
   int (*yy_parse)(void *YYPARSE_PARAM);
};

int syn_tree(int s1);
int syn_tree(int s1, int s2);
int syn_tree(int s1, int s2, int s3);
int syn_tree(int s1, int s2, int s3, int s4);
int syn_tree(int s1, int s2, int s3, int s4, int s5);

#define L         syn_tree

// --------------------------- ParseYACC ---------------------------
#undef MAKE
#define MAKE(F,P) \
   YSyntax* syntax = (YSyntax*)YYPARSE_PARAM; \
   GSymbol maker(GSymbol::gsMaker,(int)T_Maker::F,P,0,GSymbol::Tree | GSymbol::Code); \
   if (!syntax->Maker(maker)) { \
   }

#define TREE(F,P) \
   YSyntax* syntax = (YSyntax*)YYPARSE_PARAM; \
   GSymbol maker(GSymbol::gsMaker,(int)T_Maker::F,P,0,GSymbol::Tree); \
   if (!syntax->Maker(maker)) { \
   }

#define CODE(F,P) \
   YSyntax* syntax = (YSyntax*)YYPARSE_PARAM; \
   GSymbol maker(GSymbol::gsMaker,(int)T_Maker::F,P,0,GSymbol::Code); \
   if (!syntax->Maker(maker)) { \
   }

#define NODE(T,K,P,S0_,S1_) \
   YSyntax* syntax = (YSyntax*)YYPARSE_PARAM; \
   GSymbol maker(GSymbol::gsMaker,(int)S_Node::T,P,K,GSymbol::SNode); \
   if (!syntax->MakerYACC(maker,&S0_,&S1_,1)) { \
   }

#define YACC(F,P,S0_,S1_) \
   YSyntax* syntax = (YSyntax*)YYPARSE_PARAM; \
   GSymbol maker(GSymbol::gsMaker,(int)T_Maker::F,P,0,GSymbol::Yacc); \
   if (!syntax->MakerYACC(maker,&S0_,&S1_)) { \
   }

#define SAVE(L) \
   YSyntax* syntax = (YSyntax*)YYPARSE_PARAM; \
   syntax->push_lexeme(*(T_Lexeme*)&L);

// --------------------------- C_Grammar_Syntax ---------------------------

class C_GrammarYSyntax : public YSyntax, public C_Grammar_Syntax
{
public:
   C_GrammarYSyntax(T_Scan *s, TGrammar* g) :YSyntax(s,g), C_Grammar_Syntax(this) {}
   virtual bool Command(int command) { return C_Grammar_Syntax::Command(command); }
	virtual T_Lexeme::T_Group Lexeme(T_Lexeme &l);
};

#endif

