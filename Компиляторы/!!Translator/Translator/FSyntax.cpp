// Parse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Rules.h"
#include "FSyntax.h"
#include "Maker.h"
#include "InHelp.h"

int TTokenTable::Add(const char* name, int index)
{
   int ret = TNameTable::Add(name);
   tokens.push_back(index);
   return ret;
}

int TTokenTable::Token(const char* name) const
{
   int ret = Find(name);
   if (ret < 0) return ret;
   return tokens[ret];
}

void TTokenTable::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   if (Enum_name) {
      fprintf(file, "%s:\n", Enum_name);
   }
   TTokenNames::print(printer);
}

void MyTable::print(TPrinter& printer) const
{
   lexemes.print(printer);
   for (const TTokenTable& table : enums) {
      table.print(printer);
   }
}

// --------------------------- FSyntax ---------------------------

bool FSyntax::Translate()
{
   if (MatchSpot(T_Symbol::lxModBegin) || MatchSpot(T_Symbol::lxModToken) || MatchSpot(T_Symbol::lxModMod)) {
      if (Match(T_Symbol::lxModBegin))
         if (!Enums()) return false;

      if (Match(T_Symbol::lxModToken))
         if (!Tokens()) return false;

      if (!Match(T_Symbol::lxModMod)) return false;
   }

	bool ret = Formulas();

   if (ret) {
      ret = data->formulas->make(*data->names);
   }

   return ret;
}

bool FSyntax::Enums()
{  
   T_Lexeme l;

   while (Match(l,T_Lexeme::rwEnum)) {
      TTokenTable Enum;

      if (Match(l,T_Lexeme::grReserv,T_Lexeme::rwClass)) {
         T_Lexeme enum_name;
         if (!Match(enum_name,T_Lexeme::grIdent)) return false;
         Enum.Enum_name = Text(enum_name);
      } else if (Match(l,T_Lexeme::grIdent)) {
         Enum.Enum_name = Text(l);
      }

      if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxLeftCramp)) return false;

      T_Lexeme enum_element;

      for (int i = 0; Match(enum_element,T_Lexeme::grIdent); i++) {
         if (Enum.Token(Text(enum_element)) >= 0) return false;
         if (Match(l,T_Lexeme::grOper,T_Symbol::lxAssign)) {
            if (!Match(l,T_Lexeme::grInteger)) return false;
            i = Integer(l);
         }

         Enum.Add(Text(enum_element),i);

         if (Match(l,T_Lexeme::grSeparator,T_Symbol::lxRightCramp)) break;
         if (!Match(T_Symbol::lxComma)) return false;
      }

      if (!Match(T_Symbol::lxSemicolon)) return false;
      enums.push_back(Enum);
   }

   if (!Match(T_Symbol::lxModEnd)) return false;

	return true;
}

bool FSyntax::Tokens()
{
	T_Lexeme l;

   do {
      T_Lexeme name;

		if (!Match(name,T_Lexeme::grIdent)) return false;
		if (!Match(l,T_Lexeme::grInteger)) return false;

		if (lexemes.Token(Text(name)) < 0) {
			lexemes.Add(Text(name), Integer(l));
		} else return false;
   } while (Match(T_Symbol::lxModToken));

	return true;
}

bool FSyntax::Formulas()
{
   while (!Match(T_Lexeme::grEof)) {
      if (!Formula()) return false;
   }

   return true;
}

bool FSyntax::Formula()
{
	T_Lexeme l;

	if (!Match(l,T_Lexeme::grIdent)) return false;
	if (!Match(T_Symbol::lxColon)) return false;

	GFormula* formula = new GFormula(GSymbol(GSymbol::gsFormula,data->names->Add(Text(l)))); 
	formula->title = Scan().Text(l); 
   BREAK_POINT_TITLE(formula->title, "E_")
   BREAK_POINT_END
   int index;
   if (!data->formulas->Add(formula, index)) {
      delete formula;
      return false;
   }

	do {
		if (!Produce()) return false;
      int yes_empty = 0;
      for (const GProduce& rule : *data->formulas->back()) {
         if (rule.IsEmpty()) yes_empty++;
      }
      if (yes_empty > 1) {
         return false;
      }
   } while (Match(T_Symbol::lxOr));

	if (!Match(T_Symbol::lxSemicolon)) return false;

	return true;
}

bool FSyntax::Produce()
{
	GFormula* formula = data->formulas->back();
	GProduce produce(GSymbol(GSymbol::gsProduce,formula->head.formula,formula->count())); 
	formula->Add(produce); 
	GProduce* rule = &formula->back();
   
	T_Lexeme l;

   while (Match(l,T_Lexeme::grIdent) || Match(l,T_Lexeme::grOper,T_Symbol::lxLT) || Match(l,T_Lexeme::grSeparator,T_Symbol::lxLeftCramp) || Match(l,T_Lexeme::grInteger))
   {
      if (l.Match(T_Lexeme::grIdent)) {
         if (Scan().Compare(l, "Empty")) {
#ifdef PRODUCE_ITEM_EMPTY
			   rule->Add(GSymbol::gsEmpty);
#endif
         } else {
            int token = lexemes.Token(Text(l));
            if (token < 0) {
			      GSymbol item(GSymbol::gsFormula,data->names->Add(Text(l))); 
			      rule->Add(item);
		      } else {
			      GSymbol item(GSymbol::gsTerminal,(token & 0x00FF00) >> 8,(token & 0x00FF));
			      rule->Add(item);
		      }
         }
      } else if (l.Match(T_Symbol::lxLT)) {
         int group;
         if (Match(l,T_Lexeme::grIdent)) group = title_group(Text(l));
         else if (Match(l,T_Lexeme::grInteger)) group = Integer(l);
         else return false;
         if (Match(T_Symbol::lxComma)) {
            T_Lexeme type;
            if (Match(type,T_Lexeme::grIdent)) {
               if (group == T_Lexeme::grReserv) {
                  GSymbol item(GSymbol::gsTerminal,group,title_word(Text(type)));
                  rule->Add(item);
               } else if (group == T_Lexeme::grError) {
                  GSymbol item(GSymbol::gsTerminal,group,title_error(Text(type)));
                  rule->Add(item);
               } else if (group == T_Lexeme::grPriority) {
                  GSymbol item(GSymbol::gsTerminal,group,title_priority(Text(type)));
                  rule->Add(item);
               } else if (group == T_Lexeme::grSyntax) {
                  GSymbol item(GSymbol::gsTerminal,group,title_syntax(Text(type)));
                  rule->Add(item);
               } else {
                  GSymbol item(GSymbol::gsTerminal,group,title_type(Text(type)));
			         rule->Add(item);
               }
            } else if (Match(type,T_Lexeme::grInteger)) {
               GSymbol item(GSymbol::gsTerminal,group, Integer(type));
               rule->Add(item);
            } else return false;
         } else {
            GSymbol item(GSymbol::gsTerminal,group); 
			   rule->Add(item);
         }
         if (!Match(T_Symbol::lxGT)) return false;
      } else if (l.Match(T_Symbol::lxLeftCramp)) {
         T_Lexeme maker;
         if (Match(maker,T_Lexeme::grReserv,T_Lexeme::rwNode)) {
            if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxLeftBracket)) return false;
            if (!Match(l,T_Lexeme::grIdent)) return false;
            int index = title_snode_maker(Text(l));
            if (!Match(T_Symbol::lxComma)) return false;
            if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxLeftBracket)) return false;
            int i = 0;
            int a[5] = {0};
            do {
               T_Lexeme param;
               if (Match(param,T_Lexeme::grInteger)) a[i] = Integer(param);
               else if (!param_to_int(&a[i])) return false;
               i++;
            } while (Match(T_Symbol::lxComma) && i != 5);
            if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxRightBracket)) return false;
            int param_number = 0;
            if (!get_param(param_number)) return false;
            if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxRightBracket)) return false;
            GSymbol maker(GSymbol::gsMaker,index,param_number,syn_tree(a[0], a[1], a[2], a[3], a[4]),GSymbol::SNode);
            rule->Add(maker);
         } else if (Match(maker,T_Lexeme::grReserv,T_Lexeme::rwTurn)) {
            if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxLeftBracket)) return false;
            if (!Match(l,T_Lexeme::grIdent)) return false;
            int indexTT = title_tnode_maker(Text(l));
            if (!Match(T_Symbol::lxComma)) return false;
            if (!Match(l,T_Lexeme::grIdent)) return false;
            int indexST = title_snode_maker(Text(l));
            int param_number = 0;
            if (!get_param(param_number)) return false;
            if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxRightBracket)) return false;
            GSymbol maker(GSymbol::gsMaker,indexTT,param_number,indexST,GSymbol::Turn);
            rule->Add(maker);
         } else if (Match(maker,T_Lexeme::grReserv,T_Lexeme::rwCall)) {
            if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxLeftBracket)) return false;
            if (!Match(l,T_Lexeme::grIdent)) return false;
            int indexST = title_snode_maker(Text(l));
            if (!Match(T_Symbol::lxComma)) return false;
            int step = 0;
            if (!get_integer(step)) return false;
            int param_number = 0;
            if (!get_param(param_number)) return false;
            if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxRightBracket)) return false;
            GSymbol maker(GSymbol::gsMaker,indexST,param_number,step,GSymbol::Call);
            rule->Add(maker);
         } else {
            int mode = 0;
            if (Match(T_Lexeme::rwMake)) mode = GSymbol::Tree | GSymbol::Code;
            else if (Match(T_Lexeme::rwCode)) mode = GSymbol::Code;
            else if (Match(T_Lexeme::rwTree)) mode = GSymbol::Tree;
            else if (Match(T_Lexeme::rwYacc)) mode = GSymbol::Yacc;
            else if (Match(T_Lexeme::rwAll)) mode = GSymbol::Yacc | GSymbol::Code | GSymbol::Tree;
            else return false;
            if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxLeftBracket)) return false;
            if (!Match(l,T_Lexeme::grIdent)) return false; 
            int index = GMakerTable::maker_table.Find(Text(l));
            int param_number = 0;
            if (!get_param(param_number)) return false;
            if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxRightBracket)) return false;
            GSymbol maker(GSymbol::gsMaker,index,param_number,0,mode);
            rule->Add(maker);
         }
         if (!Match(T_Symbol::lxSemicolon)) return false;
         if (!Match(l,T_Lexeme::grSeparator,T_Symbol::lxRightCramp)) return false;
      } else if (l.Match(T_Lexeme::grInteger)) {
         T_Lexeme lex;
         const T_SymbolTable& test = symbol_table();
         if (!test.Find(Integer(l),lex)) return false;
         GSymbol item(GSymbol::gsTerminal,lex.group,lex.type); 
			rule->Add(item);
      }
   }

	return true;
}

bool FSyntax::skip_error(bool check_ident, int n, T_Symbol::T_Type type, ...)
{
   T_Symbol::T_Type *p = &type;

   while (!Match(T_Lexeme::grEof)) {
      bool temp = false;
      int count = n;

      T_Symbol::T_Type *p_temp = p;

      while (count--) {
         temp = MatchSpot(*p_temp);
         if (temp) return true;
         p_temp++;
      }

      if (check_ident) {
         T_Lexeme l;

         temp = MatchSpot(l, T_Lexeme::grIdent);
         if (temp) return true;
      }

      if (!temp) Next();
   }

   return false;
}

bool FSyntax::param_to_int(int* param_int) 
{
   T_Lexeme param;

   if (!Match(param,T_Lexeme::grIdent)) return false;

   if (Match(T_Symbol::lxColonColon)) {
      T_Lexeme enum_param;
      if (!Match(enum_param,T_Lexeme::grIdent)) return false;
      for (int j = 0; j < (int)enums.size(); j++) {
         if (enums[j].Enum_name && Scan().Compare(param, enums[j].Enum_name)) {
            int check_param = enums[j].Token(Text(enum_param));
            if (check_param >= 0) {
               *param_int = check_param;
               return true;
            }
         }
      }
   } else {
      for (int j = 0; j < (int)enums.size(); j++) {
         int check_param = enums[j].Token(Text(param));
         if (enums[j].Enum_name == NULL && check_param >= 0) {
            *param_int = check_param;
            return true;
         }
      }
   }

   return false;
}

bool FSyntax::get_integer(int& param_number)
{
   T_Lexeme param;
   if (Match(param,T_Lexeme::grInteger)) param_number = Integer(param);
   else if (Match(T_Symbol::lxSub))
      if (Match(param,T_Lexeme::grInteger)) param_number = (-1) * Integer(param);
      else return false;
   else if (!param_to_int(&param_number)) return false;
   return true;
}

bool FSyntax::get_param(int& param_number)
{
   if (Match(T_Symbol::lxComma)) {
      if (!get_integer(param_number)) return false;
   }
   return true;
}

// --------------------------- GrammarSyntax ---------------------------
#include "Grammar.h"

T_Lexeme::T_Group GrammarSyntax::Lexeme(T_Lexeme &l)
{
   A_Syntax::Lexeme(l);
   return l.group;
}

bool GrammarSyntax::Grammar()
{
   if (!Tree()) return false;

   int index = 0;

   SNode* list = Tree()->Get(index);

   if (!list) return false;

   data->formulas->clear();

   if (Enums(list)) {
      index++;
      list = tree->Get(index);
   }
   if (Tokens(list)) {
      index++;
      list = tree->Get(index);
   }
   if (!Formulas(list)) return false;

   return data->formulas->make(*data->names);

}

bool GrammarSyntax::Enums(SNode* list) 
{
   if (list->type != SNode::stEnums) return false;

   for (int i = 0; i < list->Count(); i++) {
      SNode* enum_node = list->Get(i);
      TTokenTable Enum;
      int index = 0;
      Enum.Enum_name = Text(enum_node->Lexeme());

      for (int j = 0; j < enum_node->Count(); j++, index++) {
         SNode* enum_item = enum_node->Get(j);
         T_Lexeme ident = enum_item->Lexeme();
         if (enum_item->Count()) {
            T_Lexeme integer = enum_item->Get(0)->Lexeme();
            index = Integer(integer);
         }
         Enum.Add(Text(ident), index);
      }
      enums.push_back(Enum);
   }

   return true;
}

bool GrammarSyntax::Tokens(SNode* list) 
{
   if (list->type != SNode::stTokens) return false;

   for (int i = 0; i < list->Count(); i++) {
      SNode* token_node = list->Get(i);
      T_Lexeme name = token_node->Lexeme();
      T_Lexeme integer = token_node->Get(0)->Lexeme();
      if (MyTable::lexemes.Token(Text(name)) < 0) {
         MyTable::lexemes.Add(Text(name), Integer(integer));
      }
   }

   return true;
}

bool GrammarSyntax::Formulas(SNode* list) 
{
   if (list->type != SNode::stFormula) return false;

   for (int i = 0; i < list->Count(); i++) {
      if (Formula(list->Get(i)) < 0) return false;
   }

   return true;
}

int GrammarSyntax::Formula(SNode* list) 
{
   T_Lexeme name = list->Lexeme();

   GFormula* formula = new GFormula(GSymbol(GSymbol::gsFormula));
   int& formula_id = formula->head.formula;
   int index;
   if (!name.Match(T_Lexeme::grIdent)) {
      data->formulas->push_back(formula);
      index = data->formulas->count() - 1;
      formula_id = -index;
   } else {
      formula_id = data->names->Add(Text(name));
      formula->title = Scan().Text(name);
      bool add = data->formulas->Add(formula, index);
      if (!add) {
         delete formula;
      }
   }
   GFormula* formula_new_old = (*data->formulas)[index];
   if (list->Count() == 1) {
      SNode* produce_node = list->Get(0);
      if (produce_node->type == SNode::stProduce) {
         SNodeList* produce_list = (SNodeList*)produce_node;
         if ((produce_list->Count() == 1) && (produce_list->option == 8)) {   // BIF
            SNode* produce_item = produce_list->Get(0);
            if (produce_item->type == SNode::stFormula) {
               SNodeList* formula_list = (SNodeList*)produce_item;
               if ((formula_list->Lexeme().Match(A_Symbol::lxLeftCramp)) || (formula_list->option == 53)) { // { or_list }
                  list = formula_list;
               } else if (formula_list->Lexeme().Match(A_Symbol::lxLeftScrape)) { // [ or_list ]
//                  list = formula_list;
               }
            }
         }
      }
   }
   for (int i = 0; i < list->Count(); i++) {
      GProduce produce(GSymbol(GSymbol::gsProduce, formula_new_old->head.formula, formula_new_old->count()));
      formula_new_old->Add(produce);
      if (!Produce(formula_new_old, list->Get(i))) {
         return -1;
      }
      int yes_empty = 0;
      for (const GProduce& rule : *formula_new_old) {
         if (rule.IsEmpty()) yes_empty++;
      }
      if (yes_empty > 1) {
         error_lex = list->Get(i)->Lexeme();
         return -1;
      }
   }

   return index;
}

bool GrammarSyntax::Produce(GFormula* formula, SNode* list)
{
   GProduce* rule = &formula->back();

   for (int i = 0; i < list->Count(); i++) {
      SNode* produce_node = list->Get(i);

      if (produce_node->type == SNode::stItem) {
         T_Lexeme item_lexeme = produce_node->Lexeme();
         if (produce_node->option == 0) { // Item(Lexeme)
            const char* text_ident = Text(item_lexeme);

            if (Scan().Compare(item_lexeme, "Empty")) {
#ifdef PRODUCE_ITEM_EMPTY
               rule->Add(GSymbol::empty);
#endif
            } else if (item_lexeme.group == T_Lexeme::grIdent) {
               int token = MyTable::lexemes.Token(text_ident);

               if (token < 0) {
                  if (data->tokens) {
                     int index = data->tokens->Find(text_ident);
                     if (index >= 0) {
                        token = data->tokens->Token(index);
                     }
                  }
               }
               if (token < 0) {
                  GSymbol item(GSymbol::gsFormula, data->names->Add(text_ident));
                  rule->Add(item);
               } else {
                  GSymbol item(GSymbol::gsTerminal, (token & 0x00FF00) >> 8, (token & 0x00FF));
                  rule->Add(item);
               }
            } else if (item_lexeme.group == T_Lexeme::grInteger) { // BNF
               T_Lexeme lex;
               const T_SymbolTable& test = symbol_table();
               if (!test.Find(Integer(item_lexeme), lex)) {
                  error_lex = item_lexeme;
                  return false;
               }

               GSymbol item(GSymbol::gsTerminal, lex.group, lex.type);
               rule->Add(item);
            } else { // <symbol>
               item_lexeme.value = 0;
               rule->Add(item_lexeme);
            }
         } else if (produce_node->option == 1) { // Item(Integer)
            T_Lexeme lex;
            const T_SymbolTable& test = symbol_table();
            if (!test.Find(Integer(item_lexeme), lex)) {
               error_lex = item_lexeme;
               return false;
            }

            GSymbol item(GSymbol::gsTerminal, lex.group, lex.type);
            rule->Add(item);
         } else if (produce_node->option == 2) { // Item(<Group>)
            int group = T_Lexeme::grNone;

            if (item_lexeme.group == T_Lexeme::grIdent) group = title_group(Text(item_lexeme));
            else if (item_lexeme.group == T_Lexeme::grInteger) group = Integer(item_lexeme);

            GSymbol item(GSymbol::gsTerminal, group);
            rule->Add(item);
         } else if (produce_node->option == 3) { // Item(<Group,Type>)

            T_Lexeme lexeme_type = produce_node->Get(0)->Lexeme();

            if (item_lexeme.group == T_Lexeme::grIdent) {
               int group = title_group(Text(item_lexeme));
               const char* text_type = Text(lexeme_type);
               GSymbol item(GSymbol::gsTerminal, group);
               if (group == T_Lexeme::grReserv) {
                  item.lexeme_type = title_word(text_type);
               } else if (group == T_Lexeme::grError) {
                  item.lexeme_type = title_error(text_type);
               } else if (group == T_Lexeme::grPriority) {
                  item.lexeme_type = title_priority(text_type);
               } else if (group == T_Lexeme::grSyntax) {
                  item.lexeme_type = title_syntax(text_type);
               } else if (group == T_Lexeme::grIdent) {
                  if (lexeme_type.group == T_Lexeme::grInteger) {
                     item.lexeme_type = Integer(lexeme_type);
                  }
               } else {
                  item.lexeme_type = title_type(text_type);
               }
               rule->Add(item);
            } else if (item_lexeme.group == T_Lexeme::grInteger) {
               int group = Integer(item_lexeme);
               GSymbol item(GSymbol::gsTerminal, group, Integer(lexeme_type));
               rule->Add(item);
            }
         }
      } else if (produce_node->type == SNode::stMaker) {
         if (produce_node->option == 0) { // MAKE, CODE, TREE, YACC, ALL
            T_Lexeme ident = produce_node->Get(0)->Lexeme();

            int index = GMakerTable::maker_table.Find(Text(ident));
            int param_number = 0;

            if (!check_param(produce_node, &param_number)) {
               error_lex = ident;
               return false;
            }

            int mode = 0;
            T_Lexeme maker_ident = produce_node->Lexeme();

            if (maker_ident.type == T_Lexeme::rwMake) mode = GSymbol::Tree | GSymbol::Code;
            else if (maker_ident.type == T_Lexeme::rwCode) mode = GSymbol::Code;
            else if (maker_ident.type == T_Lexeme::rwTree) mode = GSymbol::Tree;
            else if (maker_ident.type == T_Lexeme::rwYacc) mode = GSymbol::Yacc;
            else if (maker_ident.type == T_Lexeme::rwAll) mode = GSymbol::Yacc | GSymbol::Code | GSymbol::Tree;

            GSymbol maker(GSymbol::gsMaker, index, param_number, 0, mode);
            rule->Add(maker);
         } else if (produce_node->option == 1) { // NODE
            T_Lexeme ident = produce_node->Lexeme();

            int index = title_snode_maker(Text(ident));
            int i = 0;
            int a[5] = { 0 };
            SNode* int_node = produce_node->Get(0);

            for (int i = 0; i < int_node->Count(); i++) {
               T_Lexeme param = int_node->Get(i)->Lexeme();
               if (param.group == T_Lexeme::grInteger) {
                  a[i] = Integer(param);
               } else if (!param_to_int(param, int_node->Get(i), &a[i])) {
                  error_lex = param;
                  return false;
               }
            }

            int param_number = 0;
            if (!check_param(produce_node, &param_number)) {
               error_lex = ident;
               return false;
            }

            GSymbol maker(GSymbol::gsMaker, index, param_number, syn_tree(a[0], a[1], a[2], a[3], a[4]), GSymbol::SNode);
            rule->Add(maker);
         } else if (produce_node->option == 5) { // TURN
            int indexTT = title_tnode_maker(Text(produce_node->Lexeme()));
            int indexST = title_snode_maker(Text(produce_node->Get(0)->Lexeme()));

            int param_number = 0;
            if (!check_param(produce_node, &param_number)) {
               error_lex = produce_node->Lexeme();
               return false;
            }

            GSymbol maker(GSymbol::gsMaker, indexTT, param_number, indexST, GSymbol::Turn);
            rule->Add(maker);
         } else if (produce_node->option == 6) { // CALL
            int indexST = title_snode_maker(Text(produce_node->Lexeme()));
            int step = 0;
            if (!check_param(produce_node->Get(0), &step)) {
               error_lex = produce_node->Lexeme();
               return false;
            }

            int param_number = 0;
            if (!check_param(produce_node, &param_number)) {
               error_lex = produce_node->Lexeme();
               return false;
            }

            GSymbol maker(GSymbol::gsMaker, indexST, param_number, step, GSymbol::Call);
            rule->Add(maker);
         }
      } else if (produce_node->type == SNode::stFormula) { // BIF - { or_list } , [ or_list ] , [ or_list ]...
         if ((produce_node->Lexeme().Match(A_Symbol::lxLeftCramp)) || (produce_node->option == 53)) { // { or_list }
            int index_formula = Formula(produce_node);
            if (index_formula < 0) {
               return false;
            }
            GSymbol item(GSymbol::gsFormula, -index_formula);
            rule->Add(item);
         } else if ((produce_node->Lexeme().Match(A_Symbol::lxLeftScrape)) || (produce_node->option == 51)) {       // [ or_list ]
            SNodeList* formula_list = (SNodeList*)produce_node;
            bool prod_one = (formula_list->Count() == 1) && (list->Count() == 1);
            if (prod_one) {
               if (!Produce(formula, formula_list->Get(0))) {
                  return false;
               }
               GProduce prod(GSymbol(GSymbol::gsProduce, formula->head.formula, formula->count()));
               formula->Add(prod);  // Empty
            } else {
               int index_formula = Formula(formula_list);
               if (index_formula < 0) {
                  return false;
               }
               GSymbol item(GSymbol::gsFormula, -index_formula);
               GFormula* list_formula = (*data->formulas)[index_formula];
               bool list_produce_empty = list_formula->HaveEmpty(true);
               if (list_produce_empty) {
                  rule->Add(item);
               } else {
                  GFormula* bif_formula = new GFormula(GSymbol(GSymbol::gsFormula, -data->formulas->count()));
                  data->formulas->push_back(bif_formula);
                  GProduce prod(GSymbol(GSymbol::gsProduce, bif_formula->head.formula, bif_formula->count()));
                  prod << item;            // B ::= item
                  bif_formula->Add(prod);  //     |
                  prod.clear();
                  prod.head.produce++;
                  bif_formula->Add(prod);  // Empty
                  rule->Add(bif_formula->head);
               }
            }
         } else if ((produce_node->Lexeme().Match(A_Symbol::lxEllipsis)) || (produce_node->option == 52)) {  // [ or_list ]...
            bool left = false;
            GFormula* bif_formula = NULL;
            if (left) {
               bif_formula = new GFormula(GSymbol(GSymbol::gsFormula, -data->formulas->count()));
               data->formulas->push_back(bif_formula);
            }
            int index_formula = Formula(produce_node);
            if (index_formula < 0) {
               return false;
            }
            GSymbol item(GSymbol::gsFormula, -index_formula);
            GFormula* wrap_formula = new GFormula(GSymbol(GSymbol::gsFormula, -data->formulas->count()));
            data->formulas->push_back(wrap_formula);
            GProduce wrap_prod(GSymbol(GSymbol::gsProduce, wrap_formula->head.formula, wrap_formula->count()));
            if (left) {
               wrap_prod << wrap_formula->head; // Master
               wrap_prod << item;
               wrap_formula->Add(wrap_prod);    // W ::= W    item
               wrap_prod.clear();               //     | item
               wrap_prod.head.produce++;        // 
               wrap_prod << item;               // B ::= W
               wrap_formula->Add(wrap_prod);    //     |

               GProduce prod(GSymbol(GSymbol::gsProduce, bif_formula->head.formula, bif_formula->count()));
               prod << wrap_formula->head;
               bif_formula->Add(prod);
               prod.clear();
               prod.head.produce++;
               bif_formula->Add(prod);          // Empty
               rule->Add(bif_formula->head);
            } else {
               wrap_prod << item;
               wrap_prod << wrap_formula->head; // Master
               wrap_formula->Add(wrap_prod);    // W ::= item W
               wrap_prod.clear();               //     | 
               wrap_prod.head.produce++;        // 
               wrap_formula->Add(wrap_prod);    
               rule->Add(wrap_formula->head);
            }
         }
      }
   }

   return true;
}

bool GrammarSyntax::check_param(SNode* produce_node, int* param_number)
{
   if (produce_node->Count() != 2) return true;

   SNode* param_node = produce_node->Get(1);
   T_Lexeme param = produce_node->Get(1)->Lexeme();

   if (param_node->option == 3) {
      if (param.group == T_Lexeme::grInteger) {
         *param_number = Integer(param);
      } else {
         return param_to_int(param, param_node, param_number);
      }
   } else if (param_node->option == 4) {
      *param_number = (-1) * Integer(param);
   }

   return true;
}

bool GrammarSyntax::param_to_int(T_Lexeme param, SNode* param_node, int* param_int)
{
   if (param_node->Count() == 1) {
      T_Lexeme enum_param = param_node->Get(0)->Lexeme();

      for (int i = 0; i < (int)enums.size(); i++) {
         if (enums[i].Enum_name && Scan().Compare(param, enums[i].Enum_name)) {
            int check_param = enums[i].Token(Text(enum_param));

            if (check_param >= 0) {
               *param_int = check_param;
               return true;
            }
         }
      }
   } else {
      for (int i = 0; i < (int)enums.size(); i++) {
         int check_param = enums[i].Token(Text(param));
         if (enums[i].Enum_name == NULL && check_param >= 0) {
            *param_int = check_param;
            return true;
         }
      }
   }

   return false;
}

enum T_BNF { S_, bnf, rules, rule, symbol_list };

bool GrammarSyntax::LexemeToSymbol(T_Lexeme& lexeme, GSymbol& current_sym)
{
   bool ret = true;
   current_sym = GSymbol(lexeme);
   if (state == T_State::tsYACCHead) {
      if (lexeme.Match(A_Symbol::lxModMod)) {
         state = T_State::tsBNFProduce;
      }
   } else if (state == T_State::tsBNFProduce) {
      if (lexeme.Match(A_Symbol::lxLeftCramp)) {
         state = T_State::tsBNFMaker;
      } else if (!lexeme.Match(A_Symbol::lxOr) && !lexeme.Match(A_Symbol::lxBNFSet)) {
         current_sym.group = T_Lexeme::grSpace; current_sym.lexeme_type = 0;
      }
   } else if (state == T_State::tsBNFMaker) {
      if (lexeme.Match(A_Symbol::lxRightCramp)) {
         state = T_State::tsBNFProduce;
      }
   } else if (state == T_State::tsBIFProduce) {
      if (lexeme.Match(A_Symbol::lxLeftMaker)) {
         state = T_State::tsBIFMaker;
         if (syntax_lexeme & T_Grammar::slMeta) {
            lexeme.group = T_Lexeme::grMeta; current_sym.group = T_Lexeme::grMeta;
         }
      } else if (lexeme.Match(A_Symbol::lxRightMaker)) {
         ret = false;
      } else if (!lexeme.Match(A_Symbol::lxOr) && !lexeme.Match(A_Symbol::lxBNFSet) && !lexeme.Match(A_Symbol::lxEllipsis) &&
                 !lexeme.Match(A_Symbol::lxLeftScrape) && !lexeme.Match(A_Symbol::lxRightScrape) &&
                 !lexeme.Match(A_Symbol::lxLeftCramp)  && !lexeme.Match(A_Symbol::lxRightCramp)) {
         current_sym.group = T_Lexeme::grSpace; current_sym.lexeme_type = 0;
      } else if (lexeme.Match(A_Symbol::lxEllipsis)) {
         if (syntax_lexeme & T_Grammar::slMeta) {
            lexeme.group = T_Lexeme::grMeta; current_sym.group = T_Lexeme::grMeta;
         }
      }
   } else if (state == T_State::tsBIFMaker) {
      if (lexeme.Match(A_Symbol::lxRightMaker)) {
         state = T_State::tsBIFProduce;
         if (syntax_lexeme & T_Grammar::slMeta) {
            lexeme.group = T_Lexeme::grMeta; current_sym.group = T_Lexeme::grMeta;
         }
      }
   }
   return ret;
}

bool GrammarSyntax::IsSaved(const T_Lexeme& lexeme) const
{
   if (lexeme.IsSaved()) return true;
   return (option & TGrammar::opSelfParsing) && ((Mask() & (A_Symbol::mmGrammar | A_Symbol::mmBNF)) == (A_Symbol::mmGrammar | A_Symbol::mmBNF));
}

bool MyYSyntax::Translate()
{
   bool ret = false;
   if (!Match(T_Lexeme::grEof)) {
      syntax_lexeme = T_SyntaxLexeme::slNone;
      ret = ParseYACC();
   } else {
      ret = true;
   }

   return ret;
}

int yy_nl_parse(void *YYPARSE_PARAM);

bool MyYSyntax::ParseYACC()
{
   int ret = yy_nl_parse(this);

   return !ret;
}

int yylex(void *yylval, void *param)
{
   MyYSyntax* syntax = (MyYSyntax*)param;
   T_Lexeme current_lexeme;
   syntax->Lexeme(current_lexeme);

   bool print_lexeme = (syntax->option & (T_OptionMode::omPrintOther | T_OptionMode::omPrintSpace | T_OptionMode::omPrintLine | T_OptionMode::omPrintLexeme)) != 0;
   if (print_lexeme) { printf(">>  "); current_lexeme.print(&syntax->Scan()); }

   (*(T_Lexeme_SNode*)yylval).lexeme = current_lexeme;
   int token = !current_lexeme.Match(T_Lexeme::grEof) ? ((current_lexeme.group << 8) | current_lexeme.type) : 0;
   return token;
}

#include "GrammarStock.h"

#pragma optimize("", off)
namespace YACCGrammar {
#include "FGrammar.cpp"
}

namespace BNFGrammar {
#include "BGrammar.cpp"
}

namespace BIFGrammar {
#include "IGrammar.cpp"
}

namespace BIFGrammarBIF {
#include "IGrammarBIF.cpp"
}

#include "C99_Lexer.h"

#pragma optimize("", on)

bool grammar_reception(TInHelp& in_help, TGrammar& table, const T_WordTable* word_table)
{
   int type = in_help.type; int option = in_help.option; 
   const char *file = in_help.file; const char *table_file = in_help.table; const char *source_file = table_file;
   A_Syntax::M_Mode make_mode = A_Syntax::M_Mode((type & 0x0F0) >> 4);
   A_Syntax::T_SyntaxMode syntax_mode = A_Syntax::T_SyntaxMode(type & 0x00F);
   TGrammar::T_SourceGrammar def_rule_mode = TGrammar::T_SourceGrammar((type & 0xF00) >> 8); // 0 - LL, 1 - NL, 2 - LR, 3 - NR
   int scan_type = (type & 0xF000) >> 12;
   int look_ahead = (type & 0x000F0000) >> 16;
   int source_type = get_file_type(source_file);

   TPrinter printer;

   table.option = option; table.look_ahead = look_ahead; table.file = file;
   table.makers = &GMakerTable::maker_table;

   if (def_rule_mode == TGrammar::sgGrammar) { // read(*.tab)
      int table_type;
      if (!table.read(table_file, table_type, 0x00)) return false;
      table.Mtable.clear();
      table.LRtable.clear();
      table.root = table.formulas.front();
      table.delete_temporary_title(true);
      if (table.option & TGrammar::POption::opMaker) {
         table.makers_used();
      }
   } else if ((def_rule_mode >= TGrammar::sgTable) && (def_rule_mode <= TGrammar::sgParser)) { // parse(*.grammar)
      T_SourceFile source;

      TGrammar    my_table;       // Parsing grammar
      TIfdefScan  scan(&source);
      T_FlexLexer lexer(&source);
      FSyntax     f_parse(&scan); // ProgParser
      MyYSyntax   y_parse(&scan); // YACC
      GrammarSyntax    parse_G(&scan, &my_table);
      A_Syntax*   parse = NULL;

      int tokens_mode = T_PrintMode::pmNone;
      if (def_rule_mode == TGrammar::sgParser) { // ProgParser
         parse = &f_parse;
         parse->Mask(A_Symbol::mmGrammar);
         parse->option = 0x0000;
      } else if (def_rule_mode == TGrammar::sgYACC) { // YACC
         parse = &y_parse;
         parse->Mask(A_Symbol::mmGrammar);
         parse->option = 0x0000;
      } else if (def_rule_mode == TGrammar::sgY) { // 0x0D - *.y
         parse = &parse_G;
         YACCGrammar::make_grammar(my_table);
         parse->syntax_mode = A_Syntax::smParseLR0;
         parse->syntax_lexeme = my_table.type;
         parse_G.set_make_mode(A_Syntax::M_Mode::mmNode);
         parse->Mask(A_Symbol::mmGrammar);
         parse->option = 0x0000;
      } else if (def_rule_mode == TGrammar::sgBNF) { // 0x0B - *.bnf
         tokens_mode |= T_PrintMode::pmBNF;
         parse = &parse_G;
         BNFGrammar::make_grammar(my_table);
         parse->syntax_mode = A_Syntax::smParseLR0;
         parse->syntax_lexeme = my_table.type;
         parse_G.set_make_mode(A_Syntax::M_Mode::mmNode);
         parse_G.look_ahead = my_table.look_ahead ;
         parse_G.state = parse_G.T_State::tsBNFProduce;
         parse->Mask(A_Symbol::M_Mask(A_Symbol::mmGrammar | A_Symbol::mmBNF));
         parse->option = 0x0000;
      } else if (def_rule_mode == TGrammar::sgBIF) { // 0x0A - BIF - *.bif
         tokens_mode |= T_PrintMode::pmBIF | T_PrintMode::pmBNF;
         parse = &parse_G;
         parse_G.state = parse_G.T_State::tsBIFProduce;
         parse->Mask(A_Symbol::M_Mask(A_Symbol::mmGrammar | A_Symbol::mmBNF));
         parse->option = 0x0000;
         if (option & TGrammar::POption::opSelfParsing) {
            BIFGrammarBIF::make_grammar(my_table);
            parse_G.set_make_mode(A_Syntax::M_Mode::mmTurn);
            parse->option |= TGrammar::POption::opSelfParsing;
            parse->syntax_mode = A_Syntax::smParseLL1;
         } else {
            BIFGrammar::make_grammar(my_table);
            parse_G.set_make_mode(A_Syntax::M_Mode::mmNode);
            parse->syntax_mode = A_Syntax::smParseLR0;
         }
         parse->syntax_lexeme = my_table.type;
         parse_G.look_ahead = my_table.look_ahead;
      } else { // 0x09 - Table - *.tab
         int table_type;
         if (!my_table.read(table_file, table_type, 0x00)) return false;
         parse = &parse_G;
//         parse->option = 0x0308;
//         parse->option |= T_OptionMode::omPrintSNode;
         parse->Mask(A_Symbol::M_Mask(A_Symbol::mmGrammar));
         if (option & TGrammar::POption::opSelfParsing) {
            parse->option |= TGrammar::POption::opSelfParsing;
         }
         if (my_table.type & T_Grammar::mtTurn) {
            parse_G.set_make_mode(A_Syntax::M_Mode::mmTurn);
         } else if (my_table.type & T_Grammar::mtSNode) {
            parse_G.set_make_mode(A_Syntax::M_Mode::mmNode);
         }
         parse->syntax_lexeme = my_table.type;
         parse_G.look_ahead = my_table.look_ahead;
         if (table_type & T_Grammar::gtLL) {
            parse->syntax_mode = A_Syntax::smParseLL1;
         } else if (table_type & T_Grammar::gtLR) {
            parse->syntax_mode = A_Syntax::smParseLR0;
         }
         my_table.print(printer);
         my_table.root = my_table.formulas.front();
         source_file = file;
         source_type = get_file_type(source_file);
         switch (source_type)
         {
         case T_Source::ftNone:
         case T_Source::ftUnknown:
         case T_Source::ftYACC:
         case T_Source::ftY:
            break;
         case T_Source::ftBNF:
            tokens_mode |= T_PrintMode::pmBNF;
            parse_G.state = parse_G.T_State::tsBNFProduce;
            parse->Mask(A_Symbol::M_Mask(parse->Mask() | A_Symbol::mmBNF));
            break;
         case T_Source::ftBIF:
            tokens_mode |= T_PrintMode::pmBIF | T_PrintMode::pmBNF;
            parse_G.state = parse_G.T_State::tsBIFProduce;
            parse->Mask(A_Symbol::M_Mask(parse->Mask() | A_Symbol::mmBNF));
            break;
         default:
            break;
         }
      }

      TRuleNames names;
      TData      data(((def_rule_mode == TGrammar::sgParser) || (def_rule_mode == TGrammar::sgYACC)) ? &table : &my_table, parse, NULL); data.names = &names;

      parse->line_is_space = true;
      if (!parse->Source(source, source_file, word_table)) return false;
      if (scan_type) {
         if (!lexer.Open()) return false;
         parse->Scan(&lexer);
      } else {
         if (table.option & TGrammar::POption::opAssociation) {
            scan.AddDef("PRIOR_ASSOCIATION");
         }
         if (!(table.option & TGrammar::POption::opNoPriorAssign)) {
            scan.AddDef("PRIOR_ASSIGN");
         }
         parse->Mask((A_Symbol::M_Mask)(parse->Mask() | A_Symbol::mmIfdef));
      }

      if (table.option & TGrammar::POption::opNoDefType) {
         parse->syntax_lexeme = T_SyntaxLexeme(parse->syntax_lexeme | T_SyntaxLexeme::slNoDefType);
      }

      TTokenNames tokens; data.tokens = &tokens;
      parse->MakeTokens(tokens, tokens_mode);

      bool ret = parse->Translate();
      if (table.names) {
         *table.names = parse->Scan().names;
      }

      if ((def_rule_mode == TGrammar::sgBIF) || (def_rule_mode == TGrammar::sgBNF) || (def_rule_mode == TGrammar::sgTable)) { // BxF
         if ((source_type != T_Source::ftY) && parse_G.Tree()) {
            SNodeList* formula = new SNodeList(SNode::stFormula);
            formula->Add(parse_G.Tree());
            parse_G.Tree(formula);
         }
      }

      int deleting_chains = 0;
      T_Lexeme error_lex = parse->forward;
      if (ret) {
         if ((def_rule_mode == TGrammar::sgY) || (def_rule_mode == TGrammar::sgBNF) || (def_rule_mode == TGrammar::sgBIF) || (def_rule_mode == TGrammar::sgTable)) {
            if ((parse_G.option & T_OptionMode::omPrintSNode) && parse_G.Tree()) {
               parse_G.Tree()->print(0x00, printer);
            }
            data.grammar = &table;
            data.formulas = &table.formulas;
            if (parse_G.Grammar()) {
               deleting_chains = table.deleting_chains(!(def_rule_mode == TGrammar::sgBIF));
            } else {
               if (!parse_G.error_lex.IsNone()) error_lex = parse_G.error_lex;
               ret = false;
            }
         }
      }
/*
      const MyTable* My_table = NULL;
      if (def_rule_mode == TGrammar::sgParser) {
         My_table = &(const MyTable&)f_parse;
      } else if (def_rule_mode == TGrammar::sgYACC) { // YACC
         My_table = &y_parse;
      } else if ((def_rule_mode == TGrammar::sgY) || (def_rule_mode == TGrammar::sgBNF) || (def_rule_mode == TGrammar::sgBIF)) { // 0x0D, 0x0B, 0x0A  
         My_table = &parse_G;
      }
      if (My_table) {
//         My_table->print(printer); // "token_table.yacc", 0x00);
//         tokens.print(printer); // "token_table.parse", 0x00);
      }
*/
      scan.print_def(printer);

      parse->Scan().names.Zero();
      if (ret) {
         printf("\ntrue\n");
         if (deleting_chains) printf("deleting_chains=%d\n", deleting_chains);
      } else {
         printf("\nfalse\n");
         error_lex.print(&scan);
         return false;
      }

      table.make_produces();
      if (!table.empty()) table.root = table.formulas.front();
      if (table.option & TGrammar::POption::opMaker) {
         table.makers_used();
      }

      table.delete_temporary_title(false);
   } else { // TGrammar::sgLL ... TGrammar::sgEXPR_LR

      type = OPTION_METHOD(, , def_rule_mode, , , scan_type, 0, make_mode);
      type |= in_help.type & 0xF0000000;
      bool ret = build_grammar(table, type, 0x00);
      if (!ret) return false;
   }
   table.print(printer);
   return true;
}

