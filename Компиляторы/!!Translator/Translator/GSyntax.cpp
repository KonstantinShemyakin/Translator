
#include "stdafx.h"

#include "Grammar.h"
#include "GSyntax.h"
#include "TSemantic.h"

// --------------------------- GSyntax ---------------------------

bool GSyntax::MatchAddLexeme(T_Lexeme& cur, const GSymbol& cur_sym, const GSymbol& sym)
{
   const T_Lexeme must(T_Lexeme(T_Lexeme::T_Group((sym.type == GSymbol::gsEof) ? T_Lexeme::grEof : sym.group),sym.lexeme_type));
   T_Lexeme cur_lex(T_Lexeme(T_Lexeme::T_Group((cur_sym.type == GSymbol::gsEof) ? T_Lexeme::grEof : cur_sym.group), cur_sym.lexeme_type));
   cur_lex.value = cur_sym.value;
   if (cur.group == T_Lexeme::grPriority) {
      int i = 11; i++;
   }
   bool ret = cur_lex.Match(must);
   if (!ret) {
      int i = 13; i++;
   }
   if (!ret && (must.group == T_Lexeme::grSyntax) && (cur.group == T_Lexeme::grSyntax)) {
   	if ((must.type == T_Lexeme::sxDefType) && ((cur.type == T_Lexeme::sxDefVar) || (cur.type == T_Lexeme::sxDefArr))) {
         ret = true;
      }
   }
   if (ret) {
      if ((!ACTION(None)) && !(syntax_lexeme & T_SyntaxLexeme::slNoSave)) {
         if (IsSaved(cur)) {
            push_lexeme(cur);
         }
      }
      Lexeme(cur);
   }
   return ret;
}

void GSyntax::SaveLexeme(const T_Lexeme& cur, const GSymbol& must)
{
   if (((must.group == T_Lexeme::T_Group::grPriority) || (must.group == T_Lexeme::T_Group::grIdent) || 
        (must.group == T_Lexeme::T_Group::grInteger)  || (must.group == T_Lexeme::T_Group::grNumber) ||
        (must.group == T_Lexeme::T_Group::grReserv)   && ((must.lexeme_type == T_Lexeme::W_Type::rwDefine) || (must.lexeme_type == T_Lexeme::W_Type::rwVoid)))) {
      push_lexeme(forward);
   } else if ((cur.group == T_Lexeme::T_Group::grSyntax) && 
             !((cur.type == T_Lexeme::sxEmptyBracket) || (cur.type == T_Lexeme::sxEmptyCramp) || (cur.type == T_Lexeme::sxEmptyScrape))) {
      push_lexeme(cur);
   }
}

struct GSymbolLexeme {
public:
   T_Lexeme lexeme;
   GSymbol  symbol, first;
};

class TQueueLexeme {
public:
   TQueueLexeme(GSyntax* s) :syntax(s) {}
   void Fill(GSymbolLexeme& current);
   bool Next(GSymbolLexeme& current);
protected:
   int  next(GSymbolLexeme& current);
   void cursor(GSymbolLexeme& current) const;
private:
   std::vector<T_Lexeme> lexeme_chain;
   GSymbolVector symbol_chain;
   GSyntax* syntax;
};

int  TQueueLexeme::next(GSymbolLexeme& current)
{
   if (current.lexeme.Match(T_Lexeme::grEof)) return -1;
   lexeme_chain.push_back(current.lexeme);
   GSymbol current_sym;
   int ret = syntax->LexemeToSymbol(current.lexeme, current_sym) ? 1 : 0;
   current_sym.value = 0; current_sym.mode = 0;
   symbol_chain << current_sym;
   return ret;
}

void TQueueLexeme::cursor(GSymbolLexeme& current) const
{
   current.symbol = symbol_chain.empty() ? GSymbol::empty : syntax->grammar->Vectors().Find(symbol_chain);
   current.lexeme = lexeme_chain.empty() ? T_Lexeme(T_Lexeme::grEof, T_Lexeme::lxNone) : lexeme_chain.front();
   current.first  = symbol_chain.empty() ? GSymbol::empty : symbol_chain.front();
   if (current.symbol.type == GSymbol::gsNone) {
      int i = 12; i++;
   }
}

void TQueueLexeme::Fill(GSymbolLexeme& current)
{
   while ((int)lexeme_chain.size() < syntax->look_ahead) {
      syntax->Lexeme(current.lexeme);
      if (next(current) < 0) break;
   }
   cursor(current);
}

bool TQueueLexeme::Next(GSymbolLexeme& current)
{
   if (!lexeme_chain.empty()) lexeme_chain.erase(lexeme_chain.begin());
   if (!symbol_chain.empty()) symbol_chain.erase(symbol_chain.begin());
   bool ret = next(current) != 0;
   cursor(current);
   return ret;
}

bool GSyntax::Translate()
{
   TPrinter printer;
   PRINTER_FILE_MODE_GRAMMAR_IF
   bool ret = false;
   if (syntax_mode == smParseLR0) {
      if (!Match(T_Lexeme::grEof)) {
         if (ACTION(Node) || ACTION(Made)) {
            if (look_ahead > 0) {
               ret = ParseLRk_SN();
            } else {
               ret = ParseLR0_SN();
            }
         } else if ((ACTION(None)) ||
                   ((ACTION(Tree)) || (ACTION(Code))) && (syntax_lexeme & (T_Grammar::mtTree | T_Grammar::mtCode)) ||
                    (ACTION(Turn)) && (syntax_lexeme & T_Grammar::mtTurn) ||
                    (ACTION(Call)) && (syntax_lexeme & T_Grammar::mtCall)
                   ) {
            if (look_ahead > 0) {
               ret = ParseLRk();
            } else {
               ret = ParseLR0();
            }
         }
      } else {
         ret = true;
      }
   } else if (syntax_mode == smParseLL1) {
      if (syntax_lexeme & T_Grammar::gtLR) {
         ret = false;
      } else if (ACTION(Node) || ACTION(Made)) {
         syntax_lexeme = T_SyntaxLexeme(syntax_lexeme | T_SyntaxLexeme::slNoSave);
         if (look_ahead > 0) {
            ret = ParseLLk_SN();
         } else {
            ret = ParseLL1_SN();
         }
      } else {
         if (look_ahead > 0) {
            ret = ParseLLk();
         } else {
            ret = ParseLL1();
         }
      }
   }
   fprintf(file, "\nlevel=%d, step=%d", max_level, step);
   fprintf(file, "\n--- semantic_tree = %d, syntax_tree = %d, lexemes = %d ----\n", CountNodes(), tree ? 1 : 0, (int)lexemes.size());
   return ret;
}

bool GSyntax::ParseLL1()
{
   const GFormula& formula = *data->Root();
   entry(formula.head);

   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = ((option & T_OptionMode::omPrintMaker) != 0);
   bool auto_tree = (option & T_OptionMode::omAutoTree) != 0;
   TPrinter printer;
   PRINTER_FILE_MODE_GRAMMAR_IF  
   T_Lexeme current_lexeme; Lexeme(current_lexeme);
   GSymbol current_sym(current_lexeme);
   while (!empty()) {
      TStackRuleItem& item = top();
      const GSymbol& sym = item.sym;
      if (ret == -1) {
         if (print_rule) {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); sym.print(printer); fprintf(file, ", ret=%d", ret);
         }
         leave();
         continue;
      }
      if (sym.IsTerminal()) {
         if (print_rule) {
            fprintf(file, "\n ? "); current_lexeme.print(&Scan()); fprintf(file, "   "); sym.print(printer); printer.eol();
         }
         if (auto_tree && sym.IsSaved()) stack_item(filled() - item.step - 1).lexeme_node.unit->Add(unit.New(current_lexeme), item.auto_number); // Auto
         int nodes_before=0, lexemes_before=0; Counts(nodes_before, lexemes_before);
         if (MatchAddLexeme(current_lexeme, current_sym, sym)) { // current
            current_sym = current_lexeme;
            ret = 1; 
         } else {
            if (error_recovery & 0x01) {
               ErrorTable.Add(erSymbol,current_lexeme);
               error_recovery |= 0x02;
               ret = 1;
            } else {
               ret = -1;
            }
         }
         if (print_rule) {
            int nodes_after=0, lexemes_after=0; Counts(nodes_after, lexemes_after);
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); sym.print(printer); fprintf(file, ", ret=%d", ret);
   	      fprintf(file, " [%d] -> [%d]\n", lexemes_before, lexemes_after);
         }
         leave(); 
      } else if (sym.IsMaker()) {
         if (Maker(sym)) {
            ret = 1; 
         } else {
            ret = -1; 
         }
         leave(); 
      } else if (sym.IsFormula()) {
         TTableKey key(sym,current_sym);
         if (print_rule) {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); key.print(printer);
         }
         const GSymbol& cell = Cell(key); 
         if (!cell.IsNone()) {
            if (cell.IsProduce()) {
               const GProduce produce = Produce(cell);
               if (auto_tree && !produce.IsEmpty()) {
                  T_SyntaxNode* node = unit.New(produce.head);  // produce.head
                  if (item.step) { // !root
                     stack_item(filled() - item.step - 1).lexeme_node.unit->Add(node, item.auto_number);
                  }
                  top().lexeme_node.unit = node;
                  top().sym.type = GSymbol::gsNone;
               } else {
                  leave();
               }
               GProduce::const_reverse_iterator p = produce.rbegin();
               int len = 0;
               int produce_len = produce.count();
               if (print_rule && produce_len) {
                  printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " <<");
               }
               while (p != produce.rend()) {
                  if (print_rule) {
                     fprintf(file, " "); (*p).print(printer, T_PrintMode::pmCompact);
                  }
                  entry((*p++));
                  top().auto_number = produce_len - len;
                  top().step = ++len;
               }
               if (print_rule && produce_len) {
                  printer.eol();
               }
               ret = 0;
            } else if (cell.IsTerminal() && !sym.IsStart()) {
               leave();
               ret = 0;
            } else if (sym.IsStart() || sym.IsEof()) {
               if (error_recovery & 0x01) {
                  ErrorTable.Add(erSymbol,current_lexeme);
                  Lexeme(current_lexeme);
                  current_sym = current_lexeme;
                  error_recovery |= 0x02;
               } else {
                  ret = -1;
               }
            } else {
               printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " ! "); sym.print(printer);
               ret = -1;
            }
         } else {
            if (error_recovery & 0x01) {
               ErrorTable.Add(erSymbol,current_lexeme);
               Lexeme(current_lexeme);
               current_sym = current_lexeme;
               error_recovery |= 0x02;
               ret = 0;
            } else {
               ret = -1; 
            }
         }
      } else if (sym.IsEmpty()) {
         leave(); 
      } else if (sym.IsNone()) { // Auto
         if ((filled() == 1)) { // Accept
            if (auto_tree) { Auto(item.lexeme_node.unit); }
         }
         leave();
      } else {
         printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " ! "); sym.print(printer);
         ret = -1;
      }
   }
   return (ret != -1) && current_lexeme.Match(T_Lexeme::grEof);
}

bool GSyntax::ParseLLk()
{
   entry(GSymbol(GSymbol::gsTable)); // Table_00000

   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = ((option & T_OptionMode::omPrintMaker) != 0);
   bool auto_tree = (option & T_OptionMode::omAutoTree) != 0;
   TPrinter printer;
   PRINTER_FILE_MODE_GRAMMAR_IF

   TQueueLexeme queue(this);
   GSymbolLexeme current;
   queue.Fill(current);

   const GSymbol& current_sym = current.symbol;
   T_Lexeme& current_lexeme = current.lexeme;

   while (!empty()) {
      TStackRuleItem& item = top();
      const GSymbol& sym = item.sym;
      if (ret == -1) {
         if (print_rule) {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); sym.print(printer); fprintf(file, ", ret=%d", ret);
         }
         leave();
         continue;
      }
      if (sym.IsTerminal()) {
         if (print_rule) {
            fprintf(file, "\n ? "); current_lexeme.print(); fprintf(file, "   "); sym.print(printer); printer.eol();
         }
         if (auto_tree && sym.IsSaved()) stack_item(filled() - item.step - 1).lexeme_node.unit->Add(unit.New(current_lexeme), item.auto_number); // Auto
         int nodes_before = 0, lexemes_before = 0; Counts(nodes_before, lexemes_before);
         if (MatchAddLexeme(current_lexeme, current.first, sym)) { // current
            ret = queue.Next(current) ? 1 : -1;
         } else {
            ret = -1;
         }
         if (print_rule) {
            int nodes_after = 0, lexemes_after = 0; Counts(nodes_after, lexemes_after);
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); sym.print(printer); fprintf(file, ", ret=%d", ret);
            fprintf(file, " [%d] -> [%d]\n", lexemes_before, lexemes_after);
         }
         leave();
      } else if (sym.IsMaker()) {
         if (Maker(sym)) {
            ret = 1;
         } else {
            ret = -1;
         }
         leave();
      } else if (sym.IsTable()) {
         TTableKey key(sym, current_sym);
         if (!grammar->references.empty()) {
            key.key.table = grammar->references[key.key.table];
         }
         key.sym.value = current_lexeme.value;
         if (print_rule) {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); key.print(printer);
         }
         const GSymbol& cell = Cell(key);
         if (cell.IsVector()) {
            const GSymbolVector produce = grammar->Vector(cell);
            if (auto_tree) {
               const GSymbol& source_head = grammar->produces[cell.mode];
               T_SyntaxNode* node = unit.New(source_head);  // produce.head
               if (item.step) { // !root
                  stack_item(filled() - item.step - 1).lexeme_node.unit->Add(node, item.auto_number);
               }
               top().lexeme_node.unit = node;
               top().sym.type = GSymbol::gsNone;
            } else {
               leave();
            }
            GProduce::const_reverse_iterator p = produce.rbegin();
            if (print_rule) {
               printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " <<");
            }
            int len = 0;
            int produce_len = produce.count();
            while (p != produce.rend()) {
               if (print_rule) {
                  fprintf(file, " "); (*p).print(printer, T_PrintMode::pmCompact);
               }
               entry((*p++));
               top().auto_number = produce_len - len;
               top().step = ++len;
            }
            if (print_rule) {
               printer.eol();
            }
            ret = 0;
         } else if (cell.IsEmpty()) {
            leave();
            entry(GSymbol::empty);
         } else {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " ! "); sym.print(printer);  fprintf(file, " "); current_sym.print(printer, 0x01);
            ret = -1;
         }
      } else if (sym.IsEmpty()) {
         leave();
      } else if (sym.IsNone()) { // Auto
         if ((filled() == 1)) { // Accept
            if (auto_tree) { Auto(item.lexeme_node.unit); }
         }
         leave();
      } else {
         printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " ! "); sym.print(printer);
         ret = -1;
      }
   }
   return (ret != -1) && current_lexeme.Match(T_Lexeme::grEof);
}

bool GSyntax::ParseLL1_SN()
{
   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = ((option & T_OptionMode::omPrintMaker) != 0);
   bool auto_tree = (option & T_OptionMode::omAutoTree) != 0;
   TPrinter printer;
   PRINTER_FILE_MODE_GRAMMAR_IF

   const GFormula& formula = *data->Root();
   entry(GSymbol()); // Action
   if (auto_tree) top().lexeme_node.unit = unit.New(GSymbol(GSymbol::gsProduce, formula.head.formula, 0));
   entry(formula.head); top().step = 1;

   T_Lexeme current_lexeme; Lexeme(current_lexeme);
   GSymbol current_sym(current_lexeme);

   const int S_count = 15;
   T_Lexeme_SNode* data_stack[S_count] = {};
   while (!empty()) {
      TStackRuleItem& item = top();
      const GSymbol& sym = item.sym;
      if (ret == -1) {
         if (print_rule) {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); sym.print(printer); fprintf(file, ", ret=%d", ret);
         }
         leave();
         continue;
      }
      if (sym.IsTerminal()) {
         if (print_rule) {
            fprintf(file, "\n ? "); current_lexeme.print(); fprintf(file, "   "); sym.print(printer); printer.eol();
         }
         if (sym.IsSaved()) {
            lexeme_piston(item.step,current_lexeme);
            if (auto_tree) stack_item(filled() - item.step - 1).lexeme_node.unit->Add(unit.New(current_lexeme), item.auto_number); // Action
         }
         if (MatchAddLexeme(current_lexeme, current_sym, sym)) { // current
            current_sym = current_lexeme;
            ret = 1; 
         } else {
            ret = -1;
         }
         if (print_rule) {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); sym.print(printer); fprintf(file, ", ret=%d\n", ret);
         }
         leave(); 
      } else if (sym.IsMaker()) {
         for (int s = 0, i = 0; i <= item.step; i++) {
            if (S_Syntax::rule_stack[filled() - 1 - i].sym.IsFormula()) continue;
            if (s >= S_count - 1) {
               ret = -1; 
               break;
            }
            data_stack[s + 1] = &S_Syntax::rule_stack[filled() - 1 - i].lexeme_node; s++;
            if (print_maker) {
               fprintf(file, " %03d", (filled() - 1 - i));
               const T_Lexeme_SNode& lexeme_node = stack_item(filled() - 1 - i).lexeme_node;
               if (lexeme_node.node) fprintf(file, "<%s>", snode_title(lexeme_node.node->type));
               if (lexeme_node.tree) fprintf(file, "<%s>", lexeme_node.tree->title());
               fprintf(file, " ");
            }
         }
         data_stack[0] = &S_Syntax::rule_stack[filled() - item.step - 1].lexeme_node;
         if (print_maker) fprintf(file, " %03d \n",(filled() - item.step - 1));
         const GSymbol& maker = sym;
         if (maker.IsMakerYACC()) {
            if (!MakerSyntaxNode(maker,data_stack)) {
               ret = -1; 
            }
         } else if (maker.IsMakerNode()) {
            if (!MakerSyntaxNode(maker,data_stack,GMakerTable::maker_table.maker_node)) {
               ret = -1; 
            }
         }
         leave(); 
      } else if (sym.IsFormula()) {
         TTableKey key(sym,current_sym);
         if (print_rule) {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); key.print(printer);
         }
         const GSymbol& cell = Cell(key); 
         if (cell.IsProduce()) {
            const GProduce produce = Produce(cell);
            T_SyntaxNode* node = NULL;
            if (auto_tree && !produce.IsEmpty()) {
               node = unit.New(produce.head);
               stack_item(filled() - item.step - 1).lexeme_node.unit->Add(node, item.auto_number); // Action
               leave();
               top().lexeme_node.unit = node;
            } else {
               leave();
            }
            GProduce::const_reverse_iterator p = produce.rbegin();
            if (print_rule) {
               printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " <<");
            }
            int len = 0;
            int produce_len = produce.count();
            while (p != produce.rend()) {
               if (print_rule) {
                  fprintf(file, " "); (*p).print(printer, T_PrintMode::pmCompact);
               }
               if ((*p).IsFormula()) {
                  entry(GSymbol()); // Action
                  top().step = ++len;
               }
               entry((*p++));
               top().auto_number = produce_len--;
               top().step = ++len;
            }
            if (print_rule) {
               printer.eol();
            }
            ret = 0;
         } else {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " ! "); sym.print(printer);
            ret = -1;
         }
      } else if (sym.IsNone()) { // Action
         if (filled() > 1) {
            TStackRuleItem& next_item = stack_item(filled() - 2);
            next_item.Piston(item); // (lexeme, node, tree) ==>>
         }
         if ((filled() == 1)) { // Accept
            if (auto_tree) { Auto(item.lexeme_node.unit); }
            Accept(item);
         }
         leave();
      } else if (sym.IsEmpty()) {
         leave(); 
      } else {
         printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " ! "); sym.print(printer);
         ret = -1;
      }
   }
   return (ret != -1);
}

bool GSyntax::ParseLLk_SN()
{
   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = ((option & T_OptionMode::omPrintMaker) != 0);
   bool auto_tree = (option & T_OptionMode::omAutoTree) != 0;
   TPrinter printer;
   PRINTER_FILE_MODE_GRAMMAR_IF

   entry(GSymbol()); // Action
   if (auto_tree) top().lexeme_node.unit = unit.New(GSymbol(GSymbol::gsProduce, 0, 0));
   entry(GSymbol(GSymbol::gsTable)); // Table_00000
   top().step = 1;

   TQueueLexeme queue(this);
   GSymbolLexeme current;
   queue.Fill(current);

   const GSymbol& current_sym = current.symbol;
   T_Lexeme& current_lexeme = current.lexeme;

   const int S_count = 15;
   T_Lexeme_SNode* data_stack[S_count] = {};
   while (!empty()) {
      TStackRuleItem& item = top();
      const GSymbol& sym = item.sym;
      if (ret == -1) {
         if (print_rule) {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); sym.print(printer); fprintf(file, ", ret=%d", ret);
         }
         leave();
         continue;
      }
      if (sym.IsTerminal()) {
         if (print_rule) {
            fprintf(file, "\n ? "); current_lexeme.print(); fprintf(file, "   "); sym.print(printer); printer.eol();
         }
         if (sym.IsSaved()) {
            lexeme_piston(item.step,current_lexeme);
            if (auto_tree) stack_item(filled() - item.step - 1).lexeme_node.unit->Add(unit.New(current_lexeme), item.auto_number); // Action
         }
         if (MatchAddLexeme(current_lexeme, current.first, sym)) { // current
            ret = queue.Next(current) ? 1 : -1;
         } else {
            ret = -1;
         }
         if (print_rule) {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); sym.print(printer); fprintf(file, ", ret=%d\n", ret);
         }
         leave();
      } else if (sym.IsMaker()) {
         for (int s = 0, i = 0; i <= item.step; i++) {
            if (S_Syntax::rule_stack[filled() - 1 - i].sym.IsTable()) continue;
            if (s >= S_count - 1) {
               ret = -1;
               break;
            }
            data_stack[s + 1] = &S_Syntax::rule_stack[filled() - 1 - i].lexeme_node; s++;
            if (print_maker) {
               fprintf(file, " %03d", (filled() - 1 - i));
               const T_Lexeme_SNode& lexeme_node = stack_item(filled() - 1 - i).lexeme_node;
               if (lexeme_node.node) fprintf(file, "<%s>", snode_title(lexeme_node.node->type));
               if (lexeme_node.tree) fprintf(file, "<%s>", lexeme_node.tree->title());
               fprintf(file, " ");
            }
         }
         data_stack[0] = &S_Syntax::rule_stack[filled() - item.step - 1].lexeme_node;
         if (print_maker) fprintf(file, " %03d \n", (filled() - item.step - 1));
         const GSymbol& maker = sym;
         if (maker.IsMakerYACC()) {
            if (!MakerSyntaxNode(maker, data_stack)) {
               ret = -1;
            }
         } else if (maker.IsMakerNode()) {
            if (!MakerSyntaxNode(maker, data_stack, GMakerTable::maker_table.maker_node)) {
               ret = -1;
            }
         }
         leave();
      } else if (sym.IsTable()) {
         TTableKey key(sym, current_sym);
         if (!grammar->references.empty()) {
            key.key.table = grammar->references[key.key.table];
         }
         key.sym.value = current_lexeme.value;
         if (print_rule) {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); key.print(printer);
         }
         const GSymbol& cell = Cell(key);
         if (cell.IsVector()) {
            const GSymbolVector produce = grammar->Vector(cell);
            T_SyntaxNode* node = NULL;
            if (auto_tree) {
               const GSymbol& source_head = grammar->produces[cell.mode];
               node = unit.New(source_head); // produce.head
               stack_item(filled() - item.step - 1).lexeme_node.unit->Add(node, item.auto_number); // Action
               leave();
               top().lexeme_node.unit = node;
            } else {
               leave();
            }
            GProduce::const_reverse_iterator p = produce.rbegin();
            if (print_rule) {
               printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " <<");
            }
            int len = 0;
            int produce_len = produce.count();
            while (p != produce.rend()) {
               if (print_rule) {
                  fprintf(file, " "); (*p).print(printer, T_PrintMode::pmCompact);
               }
               if ((*p).IsTable()) {
                  entry(GSymbol()); // Action
                  top().step = ++len;
               }
               entry((*p++));
               top().auto_number = produce_len--;
               top().step = ++len;
            }
            if (print_rule) {
               printer.eol();
            }
            ret = 0;
         } else if (cell.IsEmpty()) {
            leave();
            entry(GSymbol::empty);
         } else {
            printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " ! "); sym.print(printer);
            ret = -1;
         }
      } else if (sym.IsNone()) { // Action
         if (filled() > 1) {
            TStackRuleItem& next_item = stack_item(filled() - 2);
            next_item.Piston(item); // (lexeme, node, tree) ==>> 
         }
         if ((filled() == 1)) { // Accept
            if (auto_tree) { Auto(item.lexeme_node.unit); }
            Accept(item);
         }
         leave();
      } else if (sym.IsEmpty()) {
         leave();
      } else {
         printer.print_offset(level, TPrinter::toEol | TPrinter::toNoOffset); fprintf(file, " ! "); sym.print(printer);
         ret = -1;
      }
   }
   return (ret != -1);
}

// Green(v=2,p=221,9.2.4)
bool GSyntax::ParseLR0()
{
   GSymbol start(GSymbol::gsSituation);
   entry(start);

   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = ((option & T_OptionMode::omPrintMaker) != 0), print_stack = (option & T_OptionMode::omPrintStack) != 0; 
   bool auto_tree = (option & T_OptionMode::omAutoTree) != 0;
   TPrinter printer; 
   PRINTER_FILE_MODE_GRAMMAR_IF

   T_Lexeme current_lexeme; Lexeme(current_lexeme);
   GSymbol current_sym(current_lexeme);
   if (print_rule) {
      fprintf(file, "\n>> "); current_lexeme.print(&Scan());
   }
   while (!empty()) {
      TStackRuleItem& item = top();
      if (ret == -1) {
         if (print_rule) {
            fprintf(file, ">%d ",filled()); item.sym.print(printer); fprintf(file, ", ret=%d\n", ret);
         }
         leave();
         continue;
      }
      const GSymbol& situation = item.sym;
      TTableKey key(situation,current_sym);
      const TAction& action = Action(key); 
      if (print_rule) {
         key.print(printer); fprintf(file, " -> "); action.print(printer); printer.eol();
      }
      if (action.IsAccept()) {
         if (auto_tree) {
            T_SyntaxNode* S_unit = unit.New(GSymbol(GSymbol::gsProduce)); // unit.New(action.sym);
            S_unit->Insert(item.lexeme_node.unit, 1);
            Auto(S_unit);
         }
         Accept();
         ret = 1;
         break;
      } else if (action.IsShift()) {
         int nodes_before=0, lexemes_before=0;
         if (print_rule) {
            Counts(nodes_before, lexemes_before); 
         }
         if ((!ACTION(None)) && !(syntax_lexeme & T_SyntaxLexeme::slNoSave)) {
            if (current_lexeme.IsSaved()) {
               push_lexeme(current_lexeme);
            }
         }
         int nodes_after = 0, lexemes_after = 0;
         if (print_rule) {
            Counts(nodes_after, lexemes_after);
            fprintf(file, "\n>> [%d] -> [%d] ", lexemes_before, lexemes_after); current_lexeme.print(&Scan());
         }
         entry(action.sym);  // S
         if (auto_tree) top().lexeme_node.lexeme = current_lexeme; // AutoTree
         if (print_stack) {
            fprintf(file, "<%d ",filled()); action.sym.print(printer); printer.eol();
         }
         Lexeme(current_lexeme);
         current_sym = current_lexeme;
      } else if (action.IsReduce()) {
         const GProduce& produce = Produce(action.sym);
         int produce_len = produce.Count();
         if (produce.maker.IsMaker()) {
            if (!Maker(produce.maker)) {
               ret = -1; 
            }
         } else if (produce.maker.IsVector()) {
            const GSymbolVector& makers = grammar->Vector(produce.maker);
            for (const GSymbol& maker : makers) {
               if (!Maker(maker)) {
                  ret = -1; break;
               }
            }
         }
         T_Lexeme_SNode S0;
         if (produce_len && auto_tree) {
            S0.unit = unit.New(action.sym);
         }
         for (int r = produce_len; r; r--) {
            const T_Lexeme_SNode& lexeme_node = stack_item(filled() - 1).lexeme_node;
            if (auto_tree) {
               if (lexeme_node.unit) { 
                  S0.unit->Insert(lexeme_node.unit, r); 
               } else if (lexeme_node.lexeme.IsSaved()) { 
                  S0.unit->Insert(unit.New(lexeme_node.lexeme), r);
               }
            }
            if (print_stack) {
               fprintf(file, ">%d ",filled()); top().sym.print(printer);  
               if (auto_tree) {
                  if (lexeme_node.unit) fprintf(file, "<.%s.>", lexeme_node.unit->title());
                  if (!lexeme_node.lexeme.IsNone()) fprintf(file, "<.%s.>", group_title(lexeme_node.lexeme.group));
               }
            }
            leave(); 
         }
         if (print_stack) printer.eol();
         GSymbol A(GSymbol::gsFormula,action.sym.formula);
         TTableKey key(top().sym,A);
         const TAction& go_to = Action(key); 
         if (print_rule) {
            key.print(printer); fprintf(file, " => "); go_to.print(printer); printer.eol();
         }
         if (go_to.IsGoto()) {
            entry(go_to.sym);  // S
            if (auto_tree) top().lexeme_node = S0;
            if (print_stack) {
               fprintf(file, "<%d ",filled()); go_to.sym.print(printer); printer.eol();
               if (auto_tree) {
                  if (S0.unit) fprintf(file, "<.%s.>", S0.unit->title());
                  if (!S0.lexeme.IsNone()) fprintf(file, "<.%s.>", group_title(S0.lexeme.group));
               }
            }
         } else {
            ret = -1;
         }
      } else if (action.IsNone()) {
         ret = -1;
      } else {
         ret = -1;
      }
   }

   return (ret != -1);
}

// Green(v=2,p=218,9.2.3) - AutoTree
bool GSyntax::ParseLRk()
{
   GSymbol start(GSymbol::gsSituation);
   entry(start);

   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = ((option & T_OptionMode::omPrintMaker) != 0), print_stack = (option & T_OptionMode::omPrintStack) != 0;
   bool auto_tree  = (option & T_OptionMode::omAutoTree) != 0;
   TPrinter printer; PRINTER_FILE_MODE_GRAMMAR_IF

   TQueueLexeme queue(this);
   GSymbolLexeme current;
   queue.Fill(current);

   const GSymbol& current_sym = current.symbol;
   T_Lexeme& current_lexeme = current.lexeme;

   while (!empty()) {
      TStackRuleItem& item = top();
      if (ret == -1) {
         if (print_rule) {
            fprintf(file, ">%d ", filled()); item.sym.print(printer); fprintf(file, ", ret=%d\n", ret);
         }
         leave();
         continue;
      }
      const GSymbol& situation = item.sym;
      TTableKey key(situation, current_sym);
      key.sym.value = current_lexeme.value;
      TAction action = Action(key);
      if (action.IsNone()) {
         if (print_rule) {
            key.print(printer); fprintf(file, " !> "); action.print(printer); printer.eol();
         }
         GSymbol my_sym(current_lexeme);
         my_sym.value = 0; my_sym.mode = 0;
         GSymbolVector vec; vec << my_sym;
         key.sym = data->grammar->Vectors().Find(vec);
         key.sym.value = current_lexeme.value;
         action = Action(key);
      }
      if (print_rule) {
         key.print(printer); fprintf(file, " -> "); action.print(printer); printer.eol();
      }
      if (action.IsAccept()) {
         if (auto_tree) {
            T_SyntaxNode* S_unit = unit.New(GSymbol(GSymbol::gsProduce)); // unit.New(action.sym);
            S_unit->Insert(item.lexeme_node.unit, 1);
            Auto(S_unit);
         }
         Accept();
         ret = 1;
         break;
      } else if (action.IsShift()) {
         int nodes_before = 0, lexemes_before = 0;
         if (print_rule) {
            Counts(nodes_before, lexemes_before);
         }
         if ((!ACTION(None)) && !(syntax_lexeme & T_SyntaxLexeme::slNoSave)) {
            if (IsSaved(current_lexeme)) {
               push_lexeme(current_lexeme);
            }
         }
         int nodes_after = 0, lexemes_after = 0;
         if (print_rule) {
            Counts(nodes_after, lexemes_after);
            fprintf(file, "\n>> [%d] -> [%d] ", lexemes_before, lexemes_after); current_lexeme.print(&Scan());
         }
         entry(action.sym);  // S
         if (auto_tree) top().lexeme_node.lexeme = current_lexeme; // AutoTree
         if (print_stack) {
            fprintf(file, "<%d ", filled()); action.sym.print(printer); printer.eol();
         }

         Lexeme(current.lexeme);
         if (!queue.Next(current)) ret = -1;

      } else if (action.IsReduce()) {
         const GProduce& produce = Produce(action.sym);
         int produce_len = produce.Count();
         if (produce.maker.IsMaker()) {
            if (!Maker(produce.maker)) {
               ret = -1;
            }
         } else if (produce.maker.IsVector()) {
            const GSymbolVector& makers = grammar->Vector(produce.maker);
            for (const GSymbol& maker : makers) {
               if (!Maker(maker)) {
                  ret = -1; break;
               }
            }
         }
         T_Lexeme_SNode S0;
         if (produce_len && auto_tree) {
            S0.unit = unit.New(action.sym);
         }
         for (int r = produce_len; r; r--) {
            const T_Lexeme_SNode& lexeme_node = stack_item(filled() - 1).lexeme_node;
            if (auto_tree) {
               if (lexeme_node.unit) { 
                  S0.unit->Insert(lexeme_node.unit, r); 
               } else if (lexeme_node.lexeme.IsSaved() || (Scan().mask & (A_Symbol::mmBNF | A_Symbol::mmSQL)) && (!lexeme_node.lexeme.IsNone())) {
                  S0.unit->Insert(unit.New(lexeme_node.lexeme), r); 
               }
            }

            if (print_stack) {
               fprintf(file, ">%d ", filled() - 1); top().sym.print(printer);
               if (auto_tree) {
                  if (lexeme_node.unit) fprintf(file, "<.%s.>", lexeme_node.unit->title());
                  if (!lexeme_node.lexeme.IsNone()) fprintf(file, "<.%s.>", group_title(lexeme_node.lexeme.group));
               }
               fprintf(file, " ");
            }
            leave();
         }
         if (print_stack) printer.eol();
         GSymbol A(GSymbol::gsFormula, action.sym.formula);
         TTableKey key(top().sym, A);
         if (!grammar->references.empty()) {
            key.sym.formula = grammar->references[key.sym.formula];
         }
         const TAction& go_to = Action(key);
         if (print_rule) {
            key.print(printer); fprintf(file, " => "); go_to.print(printer); printer.eol();
         }
         if (go_to.IsGoto()) {
            entry(go_to.sym);  // S
            top().lexeme_node = S0;
            if (print_stack) {
               fprintf(file, "<%d ", filled()); go_to.sym.print(printer); printer.eol();
               if (auto_tree) {
                  if (S0.unit) fprintf(file, "<.%s.>", S0.unit->title());
                  if (!S0.lexeme.IsNone()) fprintf(file, "<.%s.>", group_title(S0.lexeme.group));
               }
            }
         } else {
            ret = -1;
         }
      } else if (action.IsNone()) {
         ret = -1;
      } else {
         ret = -1;
      }
   }

   return (ret != -1);
}

bool GSyntax::VerifyLR0(const GSymbol& current_sym)
{
   va_clear();
   int ret = 0;
   while (!va_empty()) {
      TStackRuleItem& item = va_top();
      const GSymbol& situation = item.sym;
      TTableKey key(situation,current_sym);
      const TAction& action = Action(key); 
      if (action.IsAccept()) {
         ret = 1;
         break;
      } else if (action.IsShift()) {
         break;
      } else if (action.IsReduce()) {
         const GProduce& produce = Produce(action.sym);
         int produce_len = produce.Count();
         for (int r = 1; r <= produce_len; r++) { 
            va_leave(); 
         }
         GSymbol A(GSymbol::gsFormula,action.sym.formula);
         TTableKey key(va_top().sym,A);
         const TAction& go_to = Action(key); 
         if (go_to.IsGoto()) {
            va_entry(go_to.sym);  // S
         } else {
            ret = -1;
            break;
         }
      } else {
         ret = -1;
         break;
      }
   }

   return (ret != -1);
}

bool GSyntax::ParseLR0_SN()
{
   GSymbol start(GSymbol::gsSituation);
   entry(start);

   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = ((option & T_OptionMode::omPrintMaker) != 0), print_stack = (option & T_OptionMode::omPrintStack) != 0; 
   bool auto_tree = (option & T_OptionMode::omAutoTree) != 0;
   TPrinter printer; PRINTER_FILE_MODE_GRAMMAR_IF

   T_Lexeme current_lexeme; Lexeme(current_lexeme);
   GSymbol current_sym(current_lexeme);
   const int S_count = 15;
   T_Lexeme_SNode* data_stack[S_count] = {};
   if (print_rule) {
      fprintf(file, "\n>> "); current_lexeme.print(&Scan());
   }
   while (!empty()) {
      TStackRuleItem& item = top();
      if (ret == -1) {
         if (print_rule) {
            fprintf(file, ">%d ",filled()); item.sym.print(printer); fprintf(file, ", ret=%d\n", ret);
         }
         leave();
         continue;
      }
      const GSymbol& situation = item.sym;
      TTableKey key(situation,current_sym);
      const TAction& action = Action(key); 
      if (print_rule) {
         key.print(printer); fprintf(file, " -> "); action.print(printer); printer.eol();
      }
      if (action.IsAccept()) {
         if (auto_tree) {
            T_SyntaxNode* S_unit = unit.New(GSymbol(GSymbol::gsProduce)); // unit.New(action.sym);
            S_unit->Insert(item.lexeme_node.unit, 1);
            Auto(S_unit);
         }
         Accept(item);
         ret = 1;
         break;
      } else if (action.IsShift()) {
         entry(action.sym);  // S
         top().lexeme_node.lexeme = current_lexeme;
         if (print_stack) {
            fprintf(file, "<%d ",filled()); action.sym.print(printer); printer.eol();
         }
         Lexeme(current_lexeme);
         current_sym = current_lexeme;
      } else if (action.IsReduce()) {
         const GProduce& produce = Produce(action.sym);
         int produce_len = produce.Count();
         T_Lexeme_SNode S0;
         if (produce_len && auto_tree) {
            S0.unit = unit.New(action.sym);
         }
         if (produce.maker.IsMaker()) {
            for (int s = 0; s < produce_len; s++) {
               if (s >= S_count - 1) {
                  ret = -1; 
                  break;
               }
               data_stack[s + 1] = &S_Syntax::rule_stack[filled() - produce_len + s].lexeme_node;
               if (print_maker) {
                  fprintf(file, " %03d", filled() - produce_len + s);
                  const T_Lexeme_SNode& lexeme_node = stack_item(filled() - produce_len + s).lexeme_node;
                  if (lexeme_node.node) fprintf(file, "<%s>", snode_title(lexeme_node.node->type));
                  if (lexeme_node.tree) fprintf(file, "<%s>", lexeme_node.tree->title());
                  fprintf(file, " ");
               }
            }
            if (produce_len && print_maker) printer.eol();
            data_stack[0] = &S0;
            GSymbol maker(produce.maker);
            if (maker.IsMakerYACC()) {
               if (!MakerSyntaxNode(maker,data_stack)) {
                  ret = -1; 
               }
            } else if (maker.IsMakerNode()) {
               if (!MakerSyntaxNode(maker,data_stack,GMakerTable::maker_table.maker_node)) {
                  ret = -1; 
               }
            }
         } else if (produce.count()) {
            T_SyntaxNode* unit = S0.unit;
            S0 = S_Syntax::rule_stack[filled() - produce.count()].lexeme_node; // $0 <- S1
            S0.unit = unit;
         }
         for (int r = produce_len; r; r--) {
            const T_Lexeme_SNode& lexeme_node = stack_item(filled() - 1).lexeme_node;
            if (auto_tree) {
               if (lexeme_node.unit) { 
                  S0.unit->Insert(lexeme_node.unit, r); 
               } else if (lexeme_node.lexeme.IsSaved()) { 
                  S0.unit->Insert(unit.New(lexeme_node.lexeme), r); 
               }
            }
            if (print_stack) {
               fprintf(file, ">%d ",filled() - 1); top().sym.print(printer);  
               if (lexeme_node.node) fprintf(file, "<%s>", snode_title(lexeme_node.node->type));
               if (lexeme_node.tree) fprintf(file, "<%s>", lexeme_node.tree->title());
               if (auto_tree) {
                  if (lexeme_node.unit) fprintf(file, "<.%s.>", lexeme_node.unit->title());
                  if (!lexeme_node.lexeme.IsNone()) fprintf(file, "<.%s.>", group_title(lexeme_node.lexeme.group));
               }
               fprintf(file, " ");
            }
            leave(); 
         }
         if (print_stack) printer.eol();
         GSymbol A(GSymbol::gsFormula,action.sym.formula);
         TTableKey key(top().sym,A);
         const TAction& go_to = Action(key); 
         if (print_rule) {
            key.print(printer); fprintf(file, " => "); go_to.print(printer); printer.eol();
         }
         if (go_to.IsGoto()) {
            entry(go_to.sym);  // S
            top().lexeme_node = S0;
            if (print_stack) {
               fprintf(file, "<%d ",filled() - 1); go_to.sym.print(printer); 
               if (S0.node) fprintf(file, "<%s>", snode_title(S0.node->type));
               if (S0.tree) fprintf(file, "<%s>", S0.tree->title());
               if (auto_tree) {
                  if (S0.unit) fprintf(file, "<.%s.>", S0.unit->title());
                  if (!S0.lexeme.IsNone()) fprintf(file, "<.%s.>", group_title(S0.lexeme.group));
               }
               printer.eol();
            }
         } else {
            ret = -1;
         }
      } else if (action.IsNone()) {
         ret = -1;
      } else {
         ret = -1;
      }
   }
   return (ret != -1);
}

bool GSyntax::ParseLRk_SN()
{
   GSymbol start(GSymbol::gsSituation);
   entry(start);

   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = ((option & T_OptionMode::omPrintMaker) != 0), print_stack = (option & T_OptionMode::omPrintStack) != 0;
   bool auto_tree = (option & T_OptionMode::omAutoTree) != 0;
   TPrinter printer; PRINTER_FILE_MODE_GRAMMAR_IF

   TQueueLexeme queue(this);
   GSymbolLexeme current;
   queue.Fill(current);

   const GSymbol& current_sym = current.symbol;
   T_Lexeme& current_lexeme = current.lexeme;

   const int S_count = 15;
   T_Lexeme_SNode* data_stack[S_count] = {};
   if (print_rule) {
      fprintf(file, "\n>> "); current_lexeme.print(&Scan());
   }
   while (!empty()) {
      TStackRuleItem& item = top();
      if (ret == -1) {
         if (print_rule) {
            fprintf(file, ">%d ", filled()); item.sym.print(printer); fprintf(file, ", ret=%d\n", ret);
         }
         leave();
         continue;
      }
      const GSymbol& situation = item.sym;
      TTableKey key(situation, current_sym);
      key.sym.value = current_lexeme.value;
      TAction action = Action(key);
      if (action.IsNone()) {
         if (print_rule) {
            key.print(printer); fprintf(file, " !> "); action.print(printer); printer.eol();
         }
         GSymbol my_sym(current_lexeme);
         my_sym.value = 0; my_sym.mode = 0;
         GSymbolVector vec; vec << my_sym;
         key.sym = data->grammar->Vectors().Find(vec);
         key.sym.value = current_lexeme.value;
         action = Action(key);
      }
      if (print_rule) {
         key.print(printer); fprintf(file, " -> "); action.print(printer); printer.eol();
      }
      if (action.IsAccept()) {
         if (auto_tree) {
            T_SyntaxNode* S_unit = unit.New(GSymbol(GSymbol::gsProduce)); // unit.New(action.sym);
            S_unit->Insert(item.lexeme_node.unit, 1);
            Auto(S_unit);
         }
         Accept(item);
         ret = 1;
         break;
      } else if (action.IsShift()) {
         entry(action.sym);  // S
         top().lexeme_node.lexeme = current_lexeme;
         if (print_stack) {
            fprintf(file, "<%d ", filled()); action.sym.print(printer); printer.eol();
         }

         Lexeme(current.lexeme);
         if (!queue.Next(current)) ret = -1;

      } else if (action.IsReduce()) {
         const GProduce& produce = Produce(action.sym);
         int produce_len = produce.Count();
         T_Lexeme_SNode S0;
         if (produce_len && auto_tree) {
            S0.unit = unit.New(action.sym);
         }
         if (produce.maker.IsMaker()) {
            for (int s = 0; s < produce_len; s++) {
               if (s >= S_count - 1) {
                  ret = -1;
                  break;
               }
               data_stack[s + 1] = &S_Syntax::rule_stack[filled() - produce_len + s].lexeme_node;
               if (print_maker) {
                  fprintf(file, " %03d", filled() - produce_len + s);
                  const T_Lexeme_SNode& lexeme_node = stack_item(filled() - produce_len + s).lexeme_node;
                  if (lexeme_node.node) fprintf(file, "<%s>", snode_title(lexeme_node.node->type));
                  if (lexeme_node.tree) fprintf(file, "<%s>", lexeme_node.tree->title());
                  fprintf(file, " ");
               }
            }
            data_stack[0] = &S0;
            GSymbol maker(produce.maker);
            if (maker.IsMakerYACC()) {
               if (!MakerSyntaxNode(maker, data_stack)) {
                  ret = -1;
               }
            } else if (maker.IsMakerNode()) {
               if (!MakerSyntaxNode(maker, data_stack, GMakerTable::maker_table.maker_node)) {
                  ret = -1;
               }
            }
         } else if (produce.count()) {
            T_SyntaxNode* unit = S0.unit;
            S0 = S_Syntax::rule_stack[filled() - produce.count()].lexeme_node; // $0 <- S1
            S0.unit = unit;
         }
         for (int r = produce_len; r; r--) {
            const T_Lexeme_SNode& lexeme_node = stack_item(filled() - 1).lexeme_node;
            if (auto_tree) {
               if (lexeme_node.unit) {
                  S0.unit->Insert(lexeme_node.unit, r); 
               } else if (lexeme_node.lexeme.IsSaved()) {
                  S0.unit->Insert(unit.New(lexeme_node.lexeme), r); 
               }
            }
            if (print_stack) {
               fprintf(file, ">%d ", filled() - 1); top().sym.print(printer);
               if (lexeme_node.node) fprintf(file, "<%s>", snode_title(lexeme_node.node->type));
               if (lexeme_node.tree) fprintf(file, "<%s>", lexeme_node.tree->title());
               if (auto_tree) {
                  if (lexeme_node.unit) fprintf(file, "<.%s.>", lexeme_node.unit->title());
                  if (!lexeme_node.lexeme.IsNone()) fprintf(file, "<.%s.>", group_title(lexeme_node.lexeme.group));
               }
               fprintf(file, " ");
            }
            leave();
         }
         if (print_stack) printer.eol();
         GSymbol A(GSymbol::gsFormula, action.sym.formula);
         TTableKey key(top().sym, A);
         if (!grammar->references.empty()) {
            key.sym.formula = grammar->references[key.sym.formula];
         }
         const TAction& go_to = Action(key);
         if (print_rule) {
            key.print(printer); fprintf(file, " => "); go_to.print(printer); printer.eol();
         }
         if (go_to.IsGoto()) {
            entry(go_to.sym);  // S
            top().lexeme_node = S0;
            if (print_stack) {
               fprintf(file, "<%d ", filled() - 1); go_to.sym.print(printer);
               if (S0.node) fprintf(file, "<%s>", snode_title(S0.node->type));
               if (S0.tree) fprintf(file, "<%s>", S0.tree->title());
               if (auto_tree) {
                  if (S0.unit) fprintf(file, "<.%s.>", S0.unit->title());
                  if (!S0.lexeme.IsNone()) fprintf(file, "<.%s.>", group_title(S0.lexeme.group));
               }
               printer.eol();
            }
         }  else {
            ret = -1;
         }
      } else if (action.IsNone()) {
         ret = -1;
      } else {
         ret = -1;
      }
   }
   return (ret != -1);
}

// Green(v=2,p=218,9.2.3)
const GFormula& GSyntax::Formula(const GSymbol &sym) const
{
   return data->Formula(sym);
}

const GProduce& GSyntax::Produce(const GSymbol &sym) const
{
   return data->Produce(sym);
}

const GSymbol&  GSyntax::Cell(const TTableKey& key) const
{
   return data->Cell(key);
}

const TAction&  GSyntax::Action(const TTableKey& key) const
{
   return data->Action(key);
}
