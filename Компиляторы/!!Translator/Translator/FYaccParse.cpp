#include "stdafx.h"

#include "YSyntax.h"
#include "FSyntax.h"
#include "Maker.h"

// --------------------------- ParseYACC ---------------------------
#define yy_nl_lex yylex
#define yy_nl_error yyerror

int yylex (void *yylval, void *param);
void yyerror(const char* mess);

#define MAKER_Enum_Create(S1) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   TTokenTable Enum; \
   if (S1.lexeme.Match(T_Lexeme::grIdent)) Enum.Enum_name = syntax->Text(S1.lexeme); \
   syntax->enums.push_back(Enum);

#define MAKER_Enum_FirstItem(S1, S2) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   TTokenTable* Enum = &syntax->enums[syntax->enums.size()-1]; \
   if (Enum->Token(syntax->Text(S1.lexeme)) < 0 && syntax->Integer(S2.lexeme) >= 0) Enum->Add(syntax->Text(S1.lexeme),syntax->Integer(S2.lexeme)); \
   // else return false;

#define MAKER_Enum_Item(S1) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   TTokenTable* Enum = &syntax->enums[syntax->enums.size()-1]; \
   if (Enum->Token(syntax->Text(S1.lexeme)) < 0) { \
      if (!Enum->Count()) { \
         Enum->Add(syntax->Text(S1.lexeme),0); \
      } else { \
         Enum->Add(syntax->Text(S1.lexeme),Enum->tokens[Enum->tokens.size() - 1] + 1); \
      } /* else return false; */ \
   } // else return false;

#define MAKER_Enum_1(S1, S2) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   if (S1.lexeme.Match(T_Lexeme::grInteger)) S2.lexeme = S1.lexeme; \
   else if (S1.lexeme.Match(T_Lexeme::grIdent)) { \
      for (int j = 0; j < (int)syntax->enums.size(); j++) { \
         int check_param = syntax->enums[j].Token(syntax->Text(S1.lexeme)); \
         if (syntax->enums[j].Enum_name == NULL && check_param >= 0) { \
            S2.lexeme.group = T_Lexeme::grInteger; \
            S2.lexeme.value = syntax->Integer(check_param); \
         } \
      } \
   } // else return false;

#define MAKER_Enum_2(S1, S2, S3) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   for (int j = 0; j < (int)syntax->enums.size(); j++) { \
      if (syntax->enums[j].Enum_name && syntax->Scan().Compare(S1.lexeme, syntax->enums[j].Enum_name)) { \
         int check_param = syntax->enums[j].Token(syntax->Text(S2.lexeme)); \
         if (check_param >= 0) { \
            S3.lexeme.group = T_Lexeme::grInteger; \
            S3.lexeme.value = syntax->Integer(check_param); \
         } \
      } \
   }

#define MAKER_Enum_3(S1, S2) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   if (S1.lexeme.Match(T_Lexeme::grInteger)) { \
      S2.lexeme = S1.lexeme; \
      S2.lexeme.value = syntax->Integer((-1) * syntax->Integer(S1.lexeme)); \
   } // else return false;

#define MAKER_Tokens(S3, S4) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   if (syntax->lexemes.Token(syntax->Text(S3.lexeme)) < 0) { \
		syntax->lexemes.Add(syntax->Text(S3.lexeme), syntax->Integer(S4.lexeme)); \
	} \

#define MAKER_Formulas \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   syntax->data->formulas->make(*syntax->data->names);

#define MAKER_Formula(S1) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   GFormula* formula = new GFormula(GSymbol(GSymbol::gsFormula,syntax->data->names->Add(syntax->Text(S1.lexeme)))); \
	formula->title = syntax->Scan().Text(S1.lexeme); \
   syntax->data->formulas->Add(formula); 

#define MAKER_Produce \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   GFormula* formula = syntax->data->formulas->back(); \
	GProduce produce(GSymbol(GSymbol::gsProduce,formula->head.formula,formula->count())); \
   formula->Add(produce);

#ifdef PRODUCE_ITEM_EMPTY
#define PRODUCE_EMPTY_ADD \
   GSymbol item(GSymbol::gsEmpty); \
   rule->Add(item);
#else
#define PRODUCE_EMPTY_ADD 
#endif

#define MAKER_Ident(S1) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
	GFormula* formula = syntax->data->formulas->back(); \
	GProduce* rule = &formula->back(); \
   if (S1.lexeme.Match(T_Lexeme::grIdent)) { \
      if (syntax->Scan().Compare(S1.lexeme, "Empty")) { \
         PRODUCE_EMPTY_ADD \
      } else { \
         int token = syntax->lexemes.Token(syntax->Text(S1.lexeme)); \
	      if (token < 0) { \
		      GSymbol item(GSymbol::gsFormula,syntax->data->names->Add(syntax->Text(S1.lexeme))); \
		      rule->Add(item); \
	      } else { \
		      GSymbol item(GSymbol::gsTerminal,(token & 0x00FF00) >> 8,(token & 0x00FF)); \
		      rule->Add(item); \
	      } \
      } \
   }

#define MAKER_Lexeme1(S1) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   GFormula* formula = syntax->data->formulas->back(); \
	GProduce* rule = &formula->back(); \
   int group; \
   if (S1.lexeme.Match(T_Lexeme::grIdent)) group = title_group(syntax->Text(S1.lexeme)); \
   else if (S1.lexeme.Match(T_Lexeme::grInteger)) group = syntax->Integer(S1.lexeme); \
   GSymbol item(GSymbol::gsTerminal,group); \
   rule->Add(item);

#define MAKER_Lexeme2(S1, S2) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   GFormula* formula = syntax->data->formulas->back(); \
	GProduce* rule = &formula->back(); \
   int group; \
   if (S1.lexeme.Match(T_Lexeme::grIdent)) group = title_group(syntax->Text(S1.lexeme)); \
   else if (S1.lexeme.Match(T_Lexeme::grInteger)) group = syntax->Integer(S1.lexeme); \
   /*T_Lexeme::T_Group group = title_group(syntax->Text(S1.lexeme)); */ \
   if (S2.lexeme.Match(T_Lexeme::grIdent)) { \
      if (group == T_Lexeme::grReserv) { \
         GSymbol item(GSymbol::gsTerminal,group,title_word(syntax->Text(S2.lexeme))); \
         rule->Add(item); \
      } else if (group == T_Lexeme::grError) { \
         GSymbol item(GSymbol::gsTerminal,group,title_error(syntax->Text(S2.lexeme))); \
         rule->Add(item); \
      } else if (group == T_Lexeme::grPriority) { \
         GSymbol item(GSymbol::gsTerminal,group,title_priority(syntax->Text(S2.lexeme))); \
         rule->Add(item); \
      } else if (group == T_Lexeme::grSyntax) { \
         GSymbol item(GSymbol::gsTerminal,group,title_syntax(syntax->Text(S2.lexeme))); \
         rule->Add(item); \
      } else { \
         GSymbol item(GSymbol::gsTerminal,group,title_type(syntax->Text(S2.lexeme))); \
		   rule->Add(item); \
      } \
   } else if (S2.lexeme.Match(T_Lexeme::grInteger)) { \
      GSymbol item(GSymbol::gsTerminal,group,syntax->Integer(S2.lexeme)); \
      rule->Add(item); \
   }

#define MAKER_Integer(S1) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   GFormula* formula = syntax->data->formulas->back(); \
	GProduce* rule = &formula->back(); \
   T_Lexeme lex; \
   const T_SymbolTable& test = symbol_table(); \
   if (test.Find(syntax->Integer(S1.lexeme),lex)) { \
      GSymbol item(GSymbol::gsTerminal,lex.group,lex.type); \
	   rule->Add(item); \
   }

#define MAKER_Make(S1, S2, S3) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   GFormula* formula = syntax->data->formulas->back(); \
	GProduce* rule = &formula->back(); \
   int index = GMakerTable::maker_table.Find(syntax->Text(S2.lexeme)); \
   int param = 0; \
   if (S3.lexeme.Match(T_Lexeme::grInteger)) param = syntax->Integer(S3.lexeme); \
   int mode = 0; \
   if (S1.lexeme.Match(T_Lexeme::grIdent,T_Lexeme::rwMake)) mode = GSymbol::Tree | GSymbol::Code; \
   else if (S1.lexeme.Match(T_Lexeme::grIdent,T_Lexeme::rwCode)) mode = GSymbol::Code; \
   else if (S1.lexeme.Match(T_Lexeme::grIdent,T_Lexeme::rwTree)) mode = GSymbol::Tree; \
   else if (S1.lexeme.Match(T_Lexeme::grIdent,T_Lexeme::rwYacc)) mode = GSymbol::Yacc; \
   else if (S1.lexeme.Match(T_Lexeme::grIdent,T_Lexeme::rwAll)) mode = GSymbol::Yacc | GSymbol::Code | GSymbol::Tree; \
   GSymbol maker(GSymbol::gsMaker,index,param,0,mode); \
   rule->Add(maker);

#define MAKER_Node(S1, S2, S3) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   GFormula* formula = syntax->data->formulas->back(); \
	GProduce* rule = &formula->back(); \
   int param = 0; \
   if (S3.lexeme.Match(T_Lexeme::grInteger)) param = syntax->Integer(S3.lexeme); \
   GSymbol maker(GSymbol::gsMaker,title_snode_maker(syntax->Text(S1.lexeme)),param,syntax->Integer(S2.lexeme),GSymbol::SNode); \
   rule->Add(maker);

#define MAKER_Turn(S1, S2, S3) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   GFormula* formula = syntax->data->formulas->back(); \
	GProduce* rule = &formula->back(); \
   int indexTT = title_tnode_maker(syntax->Text(S1.lexeme)); \
   int indexST = title_snode_maker(syntax->Text(S2.lexeme)); \
   int param = 0; \
   if (S3.lexeme.Match(T_Lexeme::grInteger)) param = syntax->Integer(S3.lexeme); \
   GSymbol maker(GSymbol::gsMaker,indexTT,param,indexST,GSymbol::Turn); \
   rule->Add(maker);

#define MAKER_Call(S1, S2, S3) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   GFormula* formula = syntax->data->formulas->back(); \
	GProduce* rule = &formula->back(); \
   int indexST = title_snode_maker(syntax->Text(S2.lexeme)); \
   int step = syntax->Integer(S1.lexeme); \
   int param = 0; \
   if (S3.lexeme.Match(T_Lexeme::grInteger)) param = syntax->Integer(S3.lexeme); \
   GSymbol maker(GSymbol::gsMaker,indexST,param,step,GSymbol::Call); \
   rule->Add(maker);

#define MAKER_Syn_Tree(S1, S2, S3, S4, S5, S6) \
   MyYSyntax* syntax = (MyYSyntax*)YYPARSE_PARAM; \
   int a[5] = {0}; \
   a[0] = syntax->Integer(S1.lexeme); \
   if (S2.lexeme.Match(T_Lexeme::grInteger)) a[1] = syntax->Integer(S2.lexeme); \
   if (S3.lexeme.Match(T_Lexeme::grInteger)) a[2] = syntax->Integer(S3.lexeme); \
   if (S4.lexeme.Match(T_Lexeme::grInteger)) a[3] = syntax->Integer(S4.lexeme); \
   if (S5.lexeme.Match(T_Lexeme::grInteger)) a[4] = syntax->Integer(S5.lexeme); \
   S6.lexeme.value = syntax->Integer(syn_tree(a[0], a[1], a[2], a[3], a[4]));

int yy_nl_parse (void *YYPARSE_PARAM); // { return 0; }

#pragma warning( disable : 4065 )
#include "FGrammar.tab.c"
