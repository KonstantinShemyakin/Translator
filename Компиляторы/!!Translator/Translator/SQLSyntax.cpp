#include "stdafx.h"
#include "Parse.h"
#include "Grammar.h"
#include "SQLReserv.h"
#include "SQLReserv.cpp"
#include "FSyntax.h"
#include "InHelp.h"
#include "TSemantic.h"

static T_WordTable sqlReserv[500];

class SQLGrammarSyntax : public GrammarSyntax
{
public:
   SQLGrammarSyntax(T_Scan *s, TGrammar* g) :GrammarSyntax(s, g) {}
public:
   virtual bool LexemeToSymbol(T_Lexeme& lexeme, GSymbol& sym);
   GFormula* SQL(GFormula* formula_made, T_SyntaxNode* unit);
public:
   TGrammar sql_table;
};

bool SQLGrammarSyntax::LexemeToSymbol(T_Lexeme& lexeme, GSymbol& current_sym)
{
   current_sym = GSymbol(lexeme);
   if (state == T_State::tsSQLProduce) {
      if ((lexeme.Match(A_Symbol::lxLeftCramp)) || (lexeme.Match(A_Symbol::lxRightCramp))) {
         current_sym.group = T_Lexeme::grMeta;
      } else if ((lexeme.Match(A_Symbol::lxLeftScrape)) || (lexeme.Match(A_Symbol::lxRightScrape))) {
         current_sym.group = T_Lexeme::grMeta;
      } else if (lexeme.Match(A_Symbol::lxOr) || lexeme.Match(A_Symbol::lxBNFSet) || lexeme.Match(A_Symbol::lxEllipsis) || lexeme.Match(A_Symbol::lxSemicolon)) {
         current_sym.group = T_Lexeme::grMeta;
      } else {
         current_sym.group = T_Lexeme::grSpace; current_sym.lexeme_type = 0;
      }
   }
   return true;
}

enum T_SQL { S_, rules, rule, item_list, item, or_list };

GFormula* SQLGrammarSyntax::SQL(GFormula* formula_made, T_SyntaxNode* unit)
{
   GFormula* formula_ret = formula_made;
   TProduceNode* produce = (TProduceNode*)unit;
   switch (unit->symbol.formula) {
   case T_SQL::S_: {
      SQL(formula_made, produce->Get(0));
      } break;
   case T_SQL::rules: {
      if (unit->symbol.produce == 0) {
         SQL(formula_made, produce->Get(0)); // rules
         SQL(formula_made, produce->Get(1)); // rule
      } else if (unit->symbol.produce == 1) {
         SQL(formula_made, produce->Get(0)); // rule
      }
      } break;
   case T_SQL::rule: { // <Space> ::= item_list ;
      T_SyntaxNode* ident_unit = produce->Get(0);
      if (ident_unit->symbol.IsTerminal() && (ident_unit->symbol.group == T_Lexeme::grIdent)) {
         T_Lexeme& lexeme = ((TLexemeNode*)ident_unit)->lexeme;
         GFormula* formula = sql_table.FindFormula(lexeme.Text());
         if (!formula) {
            formula = sql_table.AddFormula(lexeme.Text());
            GProduce prod(GSymbol(GSymbol::gsProduce, formula->head.formula));
            formula->Add(prod);
            TProduceNode* item_list = (TProduceNode*)produce->Get(2);
            SQL(formula, item_list);
         } else {
            fprintf(stdout, "%s\n", lexeme.Text());
         }
      }
      } break;
   case T_SQL::item_list: {
      if (unit->symbol.produce == 0) {        // item_list item
         SQL(formula_made, produce->Get(0)); // item_list
         SQL(formula_made, produce->Get(1)); // item
      } else if (unit->symbol.produce == 1) { // item_list symbol
         SQL(formula_made, produce->Get(0)); // item_list
         T_SyntaxNode* symbol_unit = produce->Get(1); // symbol
         formula_made->Add(symbol_unit->symbol);
      } else if (unit->symbol.produce == 2) { // item
         SQL(formula_made, produce->Get(0)); // item
      } else if (unit->symbol.produce == 3) { // symbol
         T_SyntaxNode* symbol_unit = produce->Get(0);
         formula_made->Add(symbol_unit->symbol);
      }
      } break;
   case T_SQL::item: {
      if (unit->symbol.produce == 0) {        // [ or_list ]
         bool nested = false; int level = 0;
         TProduceNode* my_own = unit->owner;
         if (my_own && (my_own->symbol.formula == T_SQL::item_list)) {
            TProduceNode* own_own = my_own->owner;
            while (own_own && (own_own->symbol.formula == T_SQL::or_list)) {
               own_own = own_own->owner; level++;
            }
            TProduceNode* own_own_own = own_own;
            if (own_own_own && (own_own_own->symbol.formula == T_SQL::item)) {// && (own_own_own->symbol.produce == 0)) {
               printf("%d,%d,%d,%d,%d ", own_own_own->symbol.produce, own_own->symbol.produce, my_own->symbol.produce, unit->symbol.produce, level);
//               if (level == 2) 
                  nested = true;
            }
         }
         if (nested && level) {
            SQL(formula_made, produce->Get(1)); // item_list
         } else {
            GFormula* formula = new GFormula(GSymbol(GSymbol::gsFormula, sql_table.count()));
            sql_table.formulas.push_back(formula);
            GProduce prod(GSymbol(GSymbol::gsProduce, formula->head.formula, formula->count()));
            formula->Add(prod);
            SQL(formula, produce->Get(1)); // or_list
            prod.head.produce++;
            formula->Add(prod);  // Empty
            formula_made->Add(formula->head);
         }
      } else if (unit->symbol.produce == 1) { // [ or_list ]...
         GFormula* wrap_formula = new GFormula(GSymbol(GSymbol::gsFormula, sql_table.count()));
         sql_table.formulas.push_back(wrap_formula);
         GProduce wrap_prod(GSymbol(GSymbol::gsProduce, wrap_formula->head.formula, wrap_formula->count()));

         GFormula* formula = new GFormula(GSymbol(GSymbol::gsFormula, sql_table.count()));
         sql_table.formulas.push_back(formula);
         GProduce prod(GSymbol(GSymbol::gsProduce, formula->head.formula, formula->count()));
         prod << formula->head; // Master
         formula->Add(prod);
         GFormula* or_list = SQL(formula, produce->Get(1)); // or_list
         prod.clear();
         prod.head.produce++;
         formula->Add(prod); 
         formula->Add(or_list->head);

         wrap_prod << formula->head;
         wrap_formula->Add(wrap_prod);
         wrap_prod.clear();
         wrap_prod.head.produce++;
         wrap_formula->Add(wrap_prod);   // Empty

         formula_made->Add(wrap_formula->head);
      } else if (unit->symbol.produce == 2) { // { or_list }
         SQL(formula_made, produce->Get(1)); // or_list
      }
      } break;
   case T_SQL::or_list: {
      if (unit->symbol.produce == 0) {        // or_list | item_list
         formula_ret = SQL(formula_made, produce->Get(0)); // or_list
         GProduce prod(GSymbol(GSymbol::gsProduce, formula_ret->head.formula, formula_ret->count()));
         formula_ret->Add(prod);
         SQL(formula_ret, produce->Get(2)); // item_list
      } else if (unit->symbol.produce == 1) { // item_list
         formula_ret = new GFormula(GSymbol(GSymbol::gsFormula, sql_table.count()));
         sql_table.formulas.push_back(formula_ret);
         GProduce prod(GSymbol(GSymbol::gsProduce, formula_ret->head.formula, formula_ret->count()));
         formula_ret->Add(prod);
         SQL(formula_ret, produce->Get(0)); // item_list
         formula_made->Add(formula_ret->head);
      }
      } break;
   }
   return formula_ret;
}

bool gif_to_sql_bnf(TInHelp& in_help)
{
//   in_help.file = "..\\SQL\\SQL.txt"; in_help.table = "..\\SQL\\bif_to_bnf.tab";
//   in_help.file = "..\\Grammar\\ETF_.bif"; in_help.table = "..\\SQL\\bif_to_bnf.tab";
   MakeSQLWordTable(sqlReserv);

   T_SourceFile source;

//   print_source(source);
//   source.Reset();

   TIfdefScan my_scan(&source);

   TRuleNames names;
   TGrammar   table;
   SQLGrammarSyntax parse(&my_scan, &table);
   parse.syntax_mode = parse.smParseLR0;
   table.option = TGrammar::POption::opNone;

   TSemantic semantic(&parse);
   TData     data(&table, &parse, &semantic); parse.data = &data; data.makers = &GMakerTable::maker_table;
   data.file = in_help.file;

   int table_type;
   A_Syntax::T_SyntaxMode syntax_type;
   if (!table.read(in_help.table, table_type, 0x00)) return false;

   TPrinter printer;
   if (table_type & T_Grammar::gtLL) {
      table.Mtable.print(printer);
      syntax_type = A_Syntax::smParseLL1;
   }
   if (table_type & T_Grammar::gtLR) {
      table.LRtable.print(printer);
      syntax_type = A_Syntax::smParseLR0;
   }
   table.print(printer);

   parse.syntax_lexeme = T_Grammar(T_SyntaxLexeme::slNone | T_SyntaxLexeme::slNoDefType);
   parse.state = parse.T_State::tsSQLProduce;
   parse.Mask(A_Symbol::M_Mask(A_Symbol::mmGrammar | A_Symbol::mmSQL | A_Symbol::mmIfdef));
   parse.WordTable(sqlReserv);
   parse.set_semantic(&semantic);
   parse.set_make_mode(parse.mmNone);
   parse.look_ahead = table.look_ahead;

   parse.option = 0;
   parse.option |= 0x0008; // lexeme
   parse.option |= 0x0010; // print_tree
   parse.option |= 0x0020; // erase_code
   parse.option |= 0x0040; // print_code
   parse.option |= 0x0100; // print_rule
   parse.option |= 0x0200; // print_maker
   parse.option |= 0x0400; // print_stack
   parse.option |= 0x1000; // print_SNode
   parse.option  = 0x0000;
   parse.option |= T_OptionMode::omAutoTree;
   parse.option |= T_OptionMode::omPrintTree;
//   parse.option |= T_OptionMode::omTrimUnit;
   parse.line_is_space = true;

   if (!parse.Source(source, in_help.file, sqlReserv)) return false;
   source.Reset();
   parse.Reset();

   T_Lexeme::print_scan = &my_scan;
   TBaseType base_type;
   bool gut = semantic.Translate();
   if (parse.option & T_OptionMode::omTrimUnit) {
      parse.unit.trim();
   }

   if (parse.Auto()->root) {
      parse.SQL(NULL, parse.Auto()->root);
   }
   semantic.Result(in_help.file);

   int opton = T_PrintMode::pmGrammar | T_PrintMode::pmCompactGroup | T_PrintMode::pmBNF;
   char *file_table = get_file_name(in_help.file, "table");
   TPrinter printer_bnf(file_table, opton);
   parse.sql_table.print(printer_bnf);
   free(file_table);

   if (gut) {
      printf("\ntrue\n");
   } else {
      printf("\nfalse\n");
   }
   parse.Cur().print(&my_scan);

   return gut;
}

// ..\Release64\TableBuilder.exe 0x020B08 0x000B1801 SQLGrammar.tab SQLGrammar.bnf

extern bool grammar_reception(TInHelp& in_help, TGrammar& table, const T_WordTable* word_table = &T_KeyWordTable::key_word_table);

void make_sql_bnf(TInHelp& in_help)
{
//   in_help.mode = 0x000B08; in_help.option = 0x000B1840;
//   in_help.file = "..\\SQL\\SQL_.tab"; in_help.table = "..\\SQL\\SQL.table";

   A_Syntax::M_Mode make_mode = A_Syntax::M_Mode((in_help.type & 0x0F0) >> 4);
   A_Syntax::T_SyntaxMode syntax_mode = A_Syntax::T_SyntaxMode(in_help.type & 0x00F);
   int look_ahead = (in_help.type & 0x000F0000) >> 16;

   in_help.option |= TGrammar::POption::opNoPriorAssign | TGrammar::POption::opNoDefType;

   TGrammar table;
   TNameTable names; table.names = &names;
   MakeSQLWordTable(sqlReserv);
   if (!grammar_reception(in_help, table, sqlReserv)) return;

   table.Make(in_help.type, in_help.file);
   table.Print(in_help.type, in_help.file);

}


