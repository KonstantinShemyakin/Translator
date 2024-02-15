#include "stdafx.h"

#include "RSyntax.h"
#include "Maker.h"
#include "Grammar.h"
#include "TSemantic.h"

RSyntax::RSyntax(T_Scan *s, TGrammar* g) :S_Syntax(g), MC_Syntax(s), 
 rules_true(0), rules_false(0), produce_count(0), failure_count(0), luck_count(0)
{
   unit.grammar = g;
}

bool RSyntax::MatchLexeme(const GSymbol& sym, int mode)
{
   bool ret = true, no_save = (mode & 0x01) != 0;
   const T_Lexeme lexeme(T_Lexeme(T_Lexeme::T_Group((sym.type == GSymbol::gsEof) ? T_Lexeme::grEof: sym.group),sym.lexeme_type));
   T_Lexeme l;
   if (lexeme.group == T_Lexeme::T_Group::grSyntax) {
      ret = MatchSyntax(l,lexeme);
      if (ret && !no_save && sym.IsSaved()) push_lexeme(l);
   } else {
      ret = A_Syntax::Match(lexeme);
      if (ret && !no_save && sym.IsSaved()) push_lexeme(forward);
   }
   return ret;
}

int RSyntax::MatchSymbol(const GSymbol& sym, int mode)
{
   int ret = true;
   if (sym.IsEmpty()) {
      ret = true;
   } else if (sym.IsTerminal() || sym.IsEof()) {
      ret = MatchLexeme(sym, mode);
   } else if (sym.IsFormula()) {
      const GFormula* formula = (*grammar).formulas[sym.formula];
      ret = Parse(*formula);
   } else if (sym.IsMaker()) {
      if (sym.maker < 0) return false; 
      ret = -1;
      const GMaker& maker = *(*makers)[sym.maker];
      if ((ACTION(Tree)) && sym.IsMakerTree()) {
         if (!maker.make_tree || !maker.make_tree(sym,this)) {
            ret = 0; 
         } else {
            ret = 1;
         }
      }
      if ((ACTION(Code)) && sym.IsMakerCode()) {
         if (!maker.make_code || !maker.make_code(sym,this,semantic)) {
            ret = 0; 
         } else {
            ret = 1;
         }
      }
      if ((ACTION(Call)) && sym.IsMakerCall()) {
         const GMaker& maker = *(*makers)[GMakerTable::maker_table.maker_call];
         if (!maker.make_tree || !maker.make_tree(sym, this)) {
            ret = 0;
         } else {
            ret = 1;
         }
      }
   } else {
      ret = false;
   }
   return ret;
}

bool RSyntax::Translate()
{
   bool ret = false;
   if (syntax_mode == A_Syntax::smParseStackRule) {
      if (ACTION(Node) || ACTION(Made)) {
         ret = ParseStack_SN();
      } else {
         ret = ParseStack();
      }
   } else if (syntax_mode == A_Syntax::smParseStackSymbol) {
      ret = Parse();
   } else if (syntax_mode == A_Syntax::smParseFormula) {
      const GFormula& formula = *grammar->root;
      ret = Parse(formula);
   }
   if (ret && !Match(T_Lexeme::grEof)) ret = false;
   printf("\nlevel=%d, step=%d, rules_true=%d, rules_false=%d, produce_count=%d, failure_count=%d, luck_count=%d\n", max_level, step, rules_true, rules_false, produce_count, failure_count, luck_count);

   return ret;
}

// produce ==>> stack
int  RSyntax::ProduceToStack()
{
   TPrinter printer;
   PRINTER_FILE_MODE_GRAMMAR_IF
   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, select_produce = (option & T_OptionMode::omSelectProduce) != 0;
   TStackRuleItem& item = top();
   GSymbol& sym = item.sym;
   T_Lexeme current_lexeme, current_cast;
   bool yes_cast = false;
   if (select_produce) {
      Lexeme(current_lexeme); current_cast = current_lexeme;
      yes_cast = current_cast.Cast();
      Restore(item.store);
   }
   while (sym.produce < item.step) { // !end
      const GProduce& produce = grammar->Produce(sym);
      if (produce.empty()) break;
      const GSymbol& front = produce.front();
      if (select_produce) {
         if (front.IsEmpty() || front.IsMaker()) break;
         if (grammar->FIRSTsP.Have(produce.head, current_lexeme) || yes_cast && grammar->FIRSTsP.Have(produce.head, current_cast)) {
            //|| grammar->FIRSTsP.HaveEmpty(produce.head)) {
            break;
         }
      } else {
         if (!front.IsTerminal()) break;
         bool beg = MatchLexeme(front, 0x01); // !save
         Restore(item.store);
         if (beg) break;
      }
      sym.produce++;
   }
   if (sym.produce >= item.step) { // last
      leave(); 
      ret = -1; 
      return ret;
   }
   const GProduce& produce = grammar->Produce(sym);
   GProduce::const_reverse_iterator p = produce.rbegin();
   if (print_rule) {
      printer.print_offset(level, 0x03); printf(" <<");
   }
   while (p != produce.rend()) {
      const GSymbol& item = (*p);
      if (item.IsMaker()) {
         bool not_ours = !item.IsMakerTree() && !item.IsMakerCode() && !item.IsMakerTurn() && !item.IsMakerCall();
         if (not_ours) { p++; continue; }
      }
      if (print_rule) {
         printf(" "); item.print(printer, T_PrintMode::pmCompact);
      }
      entry((*p++));
   }
   if (print_rule) {
      printf("\n");
   }
   produce_count++;
   return ret;
}

bool RSyntax::ParseStack()
{
   TPrinter printer;
   PRINTER_FILE_MODE_GRAMMAR_IF
   const GFormula& formula = *grammar->root;
   TStackRuleItem root_item(formula.head);
   entry(root_item);

   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0;
   while (!rule_stack.empty()) {
      TStackRuleItem& item = top();
      GSymbol& sym = item.sym;
      if (ret == -1) { // failure
         failure_count++;
         if (print_rule) {
            printer.print_offset(level, 0x03); printf(" >> "); sym.print(printer);
            printf(", ret=%2d", ret);
         }
         if (sym.IsProduce() && (++sym.produce < item.step)) {
            int current = Current();
            Restore(item.store);
            if (print_rule) {
               printf(" restore=%03d -> %03d step=%d\n", current, item.store.store_pos, item.step);
            }
            // -> (produce ==>> stack)
            ret = ProduceToStack();
         } else { // last
            leave(); 
         }
      } else { // ret == 0, 1
         if (sym.IsFormula()) {
            const GFormula& formula = grammar->Formula(sym);
            const GProduce& produce = grammar->Produce(sym);
            Store(item.store);
            if (print_rule) {
               printer.print_offset(level, 0x03); printf(" >> "); sym.print(printer);
               printf("store=%03d step=%d", item.store.store_pos,item.step);
               printf(", ret=%2d", ret);
            }
            if ((sym.mode & GSymbol::Master) && (filled() > 1)) {
               const TStackRuleItem& master_item = stack_item(filled() - 2);
               if (master_item.sym.IsProduce() && (master_item.sym.formula == sym.formula)) {
                  if (print_rule) {
                     printf(" #Master# ");
                  }
                  leave();
                  Store(top().store);
               }
            }
            if (print_rule) {
               printf("\n");
            }
            top().sym = produce.head; top().step = formula.count();
            // -> (produce ==>> stack)
            ret = ProduceToStack();
         } else if (sym.IsProduce()) { // luck
            if (print_rule) {
               printer.print_offset(level, 0x03); printf(" >> "); sym.print(printer);
            }
            ret = 1; 
            leave(); 
            luck_count++;
         } else {
            bool print_maker = ((option & T_OptionMode::omPrintMaker) != 0) && sym.IsMaker();
            int nodes_before=0, lexemes_before=0; 
            if (print_maker) {
               Counts(nodes_before, lexemes_before);
            }
            int match = MatchSymbol(sym);
            if (match) { 
               ret = 1; 
            } else {
               ret = -1; 
            }
            if ((print_rule || print_maker) && (match >= 0)) {
               printer.print_offset(level, 0x03); printf(" >> "); sym.print(printer); printf(", ret=%2d", ret);
               if (print_maker) {
                  int nodes_after=0, lexemes_after=0; Counts(nodes_after, lexemes_after);
         	      printf(" [%d,%d] -> [%d,%d]", nodes_before, lexemes_before, nodes_after, lexemes_after);
               }
               printf("\n");
            }
            leave(); 
         }
      }
   }
   return (ret != -1);
}

bool RSyntax::ParseStack_SN()
{
   TPrinter printer;
   PRINTER_FILE_MODE_GRAMMAR_IF
   
   const GFormula& formula = *grammar->root;
   TStackRuleItem root_item(formula.head);
   entry(root_item);

   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = ((option & T_OptionMode::omPrintMaker) != 0);
   const int S_count = 15;
   T_Lexeme_SNode* data_stack[S_count] = {};
   while (!rule_stack.empty()) {
      TStackRuleItem& item = top();
      GSymbol& sym = item.sym;
      if (ret == -1) { // failure
         failure_count++;
         if (print_rule) {
            printer.print_offset(level, 0x03); printf(" >> "); sym.print(printer);
            printf(", ret=%2d", ret);
         }
         if (sym.IsProduce()) {
            const GFormula& formula = grammar->Formula(sym);
            sym.produce++;
            if (sym.produce >= formula.count()) { // last
               leave(); 
               continue;
            }
            int current = Current();
            Restore(item.store);
            if (print_rule) {
               printf("restore=%03d -> %03d step=%d", current, item.store.store_pos, item.step);
            }
            // -> (produce ==>> stack)
         } else {
            leave(); 
            continue;
         }
      } else { // ret == 0, 1
         if (sym.IsFormula()) {
            const GFormula& formula = grammar->Formula(sym);
            const GProduce& produce = grammar->Produce(sym);
            Store(item.store);
            if (print_rule) {
               printer.print_offset(level, 0x03); printf(" >> "); sym.print(printer);
               printf("store=%03d step=%d", item.store.store_pos,item.step);
               printf(", ret=%2d", ret);
            }
            if ((sym.mode & GSymbol::Master) && (filled() > 1)) {
               const TStackRuleItem& master_item = stack_item(filled() - 2);
               if (master_item.sym.IsProduce() && (master_item.sym.formula == sym.formula)) {
                  if (print_rule) {
                     printf(" #Master# ");
                  }
                  leave();
                  Store(top().store);
               }
            }
            top().sym = produce.head;
            // -> (produce ==>> stack)
         } else if (sym.IsProduce()) { // luck
            luck_count++;
            if (print_rule) {
               printer.print_offset(level, 0x03); printf(" >> "); sym.print(printer);
               printf(" %03d", filled() - 1);
               const T_Lexeme_SNode& lexeme_node = stack_item(filled() - 1).lexeme_node;
               if (lexeme_node.node) printf("<%s>", snode_title(lexeme_node.node->type));
               if (lexeme_node.tree) printf("<%s>", lexeme_node.tree->title());
               printf(" ");
            }
            if (filled() > 1) {
               TStackRuleItem& next_item = stack_item(filled() - 2);
               if (next_item.Piston(item, 0x02)) { // 0x02 - Produce; (lexeme, node, tree) ==>>
                  if (print_rule) {
                     printf(" %03d", filled() - 2);
                     const T_Lexeme_SNode& lexeme_node = stack_item(filled() - 2).lexeme_node;
                     if (lexeme_node.node) printf("<%s>", snode_title(lexeme_node.node->type));
                     if (lexeme_node.tree) printf("<%s>", lexeme_node.tree->title());
                     printf("; ");
                  }
               }
            }
            if ((filled() == 1)) { // Accept
               Accept(item);
            }
            ret = 1;
            leave(); 
            continue;
         } else if (sym.IsTerminal()) {
            bool match, save = false;
            const T_Lexeme lexeme(T_Lexeme(T_Lexeme::T_Group(sym.group),sym.lexeme_type));
            T_Lexeme l;
            if (lexeme.group == T_Lexeme::T_Group::grSyntax) {
               match = MatchSyntax(l,lexeme);
               if (match && (sym.IsSaved())) save = true;
            } else {
               match = A_Syntax::Match(lexeme);
               if (match && (sym.IsSaved())) { l = forward; save = true; }
            }
            ret = match ? 1 : -1; 
            if (print_rule) {
               printer.print_offset(level, 0x03); printf(" >> "); sym.print(printer); printf(", ret=%2d", ret);
            }
            if (save) {
               int maker = item.step - 1;
               while ((maker >= 0) && !stack_item(filled() - item.step + maker).sym.IsMaker()) {
                  maker--;
               }
               stack_item(filled() - item.step + maker).lexeme_node.lexeme = l;
            }
            leave(); 
            continue;
         } else if (sym.IsEmpty()) {
            leave(); 
            continue;
         } else if (sym.IsMaker()) {
            int nodes_before=0, lexemes_before=0; 
            if (print_maker) {
               Counts(nodes_before, lexemes_before);
            }
            int stack_top = filled() - 1;
            for (int i = 0; i <= item.step; i++) {
               if (i >= S_count - 1) {
                  ret = -1; 
                  break;
               }
               data_stack[i + 1] = &S_Syntax::rule_stack[stack_top - i].lexeme_node;
               if (print_maker) { 
                  printf(" %03d", (stack_top - i));
                  const T_Lexeme_SNode& lexeme_node = *data_stack[i + 1];
                  if (lexeme_node.node) printf("<%s>", snode_title(lexeme_node.node->type)); 
                  printf(" ");
               }
            }
            data_stack[0] = &S_Syntax::rule_stack[stack_top - item.step].lexeme_node;
            if (print_maker) printf(" %03d --->>> ",(stack_top - item.step));
            const GSymbol& maker = sym;
            int match = -1;
            int save_print = (option & (T_OptionMode::omPrintRule | T_OptionMode::omPrintMaker)); option &= ~(T_OptionMode::omPrintRule | T_OptionMode::omPrintMaker);
            if (maker.IsMakerYACC()) {
               match = 0;
               if (!MakerSyntaxNode(maker,data_stack)) {
                  ret = -1; 
               }
            } else if (maker.IsMakerNode()) {
               match = 0;
               if (!MakerSyntaxNode(maker,data_stack,GMakerTable::maker_table.maker_node)) {
                  ret = -1; 
               }
            }
            option |= save_print;
            if ((print_rule || print_maker) && (match >= 0)) {
               if (print_maker) {
                  for (int i = 0; i <= item.step; i++) {
                     if (i >= S_count - 1) {
                        ret = -1;
                        break;
                     }
                     printf(" %03d", (stack_top - i));
                     const T_Lexeme_SNode& lexeme_node = *data_stack[i + 1];
                     if (lexeme_node.node) printf("<%s>", snode_title(lexeme_node.node->type));
                     printf(" ");
                  }
               }
               printer.print_offset(level, 0x03); sym.print(printer); printf(", ret=%2d", ret);
               if (print_maker) {
                  int nodes_after=0, lexemes_after=0; Counts(nodes_after, lexemes_after);
         	      printf(" [%d,%d] -> [%d,%d]", nodes_before, lexemes_before, nodes_after, lexemes_after);
               }
               printf("\n");
            }
            leave(); 
            continue;
         }
      }
      // produce ==>> stack
      produce_count++;
      const GProduce& produce = grammar->Produce(top().sym);
      GProduce::const_reverse_iterator p = produce.rbegin();
      if (print_rule) {
         printer.print_offset(level, 0x03); printf(" <<");
      }
      int len = 0;
      while (p != produce.rend()) {
         if ((*p).IsMaker() && !(*p).IsMakerYACC() && !(*p).IsMakerNode()) {
            p++; continue;
         }
         if (print_rule) {
            printf(" "); (*p).print(printer, T_PrintMode::pmCompact);
         }
         entry((*p++));
         top().step = ++len;
      }
      if (print_rule) {
         printf("\n");
      }
      ret = 0;
   }
   return (ret != -1);
}

bool RSyntax::Parse()
{
   TPrinter printer;
   PRINTER_FILE_MODE_GRAMMAR_IF

   const GFormula& formula = *grammar->root;
   TStackRuleItem root_item(formula.head);
   entry(root_item);

   int ret = 0;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0, print_maker = (option & T_OptionMode::omPrintMaker) != 0;
   while (!rule_stack.empty()) {
      TStackRuleItem& item = top();
      const GSymbol& sym = item.sym;
      if (print_rule && (ret == 0) && (sym.IsFormula() || sym.IsProduce())) {
//         printer.print_offset(level, 0x03); sym.print(printer);
      }
      if (sym.IsFormula()) {
         const GFormula& formula = *grammar->formulas[sym.formula]; 
         if (ret == 0) { // begin
            Store(item.store);
            if (print_rule) {
               printer.print_offset(level, 0x03); sym.print(printer); printf("store=%03d \n", item.store.store_pos);
            }
         } else if (ret ==  1) { // after true down
         } else if (ret == -1) { // after false down
            int current = Current();
            Restore(item.store);
            if (print_rule) {
               printer.print_offset(level, 0x03); sym.print(printer); printf("restore=%03d -> %03d\n", current, item.store.store_pos);
            }
         }
         if ((ret == 1) || (item.step == formula.count())) { // after true down, end
            if (ret == 0) { // items_count == 0
               ret = -1;
            } else if (ret == 1) {
            }
            if (print_rule) {
               printer.print_offset(level, 0x03); printf("->"); sym.print(printer); printf(", ret=%2d", ret);
            }
            if (ret == 1) rules_true++; else rules_false++;
            leave(); 
         } else { // after false down, begin
            TStackRuleItem sub_item(formula[item.step++].head); // produce
            entry(sub_item);
            ret = 0;
         }
      } else if (sym.IsProduce()) {
         const GFormula& formula = *grammar->formulas[sym.formula]; 
         const GProduce& produce = formula[sym.produce];
         if (ret == 0) { // begin rule
         } else if (ret == 1) { // after true down
         }
         if ((ret == -1) || (item.step == produce.count())) { // after false down, end
            if (ret == -1) { // after false down
            } else { // end
               ret = 1;
            }
            if (ret == 1) rules_true++; else rules_false++;
            if (print_rule) {
               printer.print_offset(level, 0x03); printf("->"); sym.print(printer); printf(", ret=%2d", ret);
            }
            leave(); 
         } else { // after true down, begin
            TStackRuleItem sub_item(produce[item.step++]);
            if ((sub_item.sym.mode & GSymbol::Master) && (item.step == produce.count())) {
               if (print_rule || print_maker) {
                  printf(" !Master! ");
               }
               leave(); // produce
               TStackRuleItem& master = top(); // formula
               master = sub_item;
            } else {
               entry(sub_item);
            }
            ret = 0;
         }
      } else { // sym
         int nodes_before = 0, lexemes_before = 0, execs_before = 0, blocks_before = 0, idents_before = 0;
         if (print_maker && sym.IsMaker()) {
            Counts(nodes_before, lexemes_before);
            if (semantic) semantic->Count(execs_before, blocks_before, idents_before);
         }
         int match = MatchSymbol(sym);
         if (match) { 
            ret = 1; 
         } else {
            ret = -1; 
         }
         if ((print_rule || (print_maker && sym.IsMaker())) && (match >= 0)) {
            printer.print_offset(level, 0x03); sym.print(printer); printf(", ret=%2d", ret);
            if (print_maker && sym.IsMaker()) {
               int nodes_after=0, lexemes_after=0, execs_after = 0, blocks_after = 0, idents_after = 0; 
               Counts(nodes_after, lexemes_after);
      	      printf(" [%d,%d] -> [%d,%d]", nodes_before, lexemes_before, nodes_after, lexemes_after);
               if (semantic) {
                  semantic->Count(execs_after, blocks_after, idents_after);
         	      printf(" [%d,%d,%d] -> [%d,%d,%d]", execs_before, blocks_before, idents_before, execs_after, blocks_after, idents_after);
               }
            }
            printf("\n");
         }
         leave(); 
      }
   }
   return (ret != -1);
}

bool RSyntax::Parse(const GProduce& produce)
{
   TPrinter printer;
   PRINTER_FILE_MODE_GRAMMAR_IF

   bool ret = true;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0; 
   if (print_rule) {
      printer.print_offset(level, 0x03); produce.head.print(printer);
   }
   for (const GSymbol& sym : produce) {
      bool print_maker = ((option & T_OptionMode::omPrintMaker) != 0) && sym.IsMaker();
      int nodes_before=0, lexemes_before=0; 
      if (print_maker) {
         Counts(nodes_before, lexemes_before);
      }
      int match = MatchSymbol(sym);
      if (match) { 
         ret = true; 
      } else {
         ret = false; 
      }
      if ((print_rule || print_maker) && (match >= 0)) {
         printer.print_offset(level, 0x03); sym.print(printer); printf(", ret=%d", ret);
         if (print_maker) {
            int nodes_after=0, lexemes_after=0; Counts(nodes_after, lexemes_after);
      	   printf(" [%d,%d] -> [%d,%d]", nodes_before, lexemes_before, nodes_after, lexemes_after);
         }
      }
      if (!ret) break;
   }
   if (print_rule) {
      printer.print_offset(level, 0x03);  printf("->"); produce.head.print(printer); printf(", ret=%d ", ret);
   }
   if (ret) rules_true++; else rules_false++;
   return ret;
}

bool RSyntax::Parse(const GFormula& formula)
{
   TPrinter printer;
   PRINTER_FILE_MODE_GRAMMAR_IF

   bool ret = false;
   bool print_rule = (option & T_OptionMode::omPrintRule) != 0;
   if (print_rule) {
      printer.print_offset(level, 0x03); formula.head.print(printer);
   }
   level++;
   T_ScanStore store; Store(store);
   if (print_rule) {
      printer.print_offset(level, 0x03); printf("store=%03d \n", store.store_pos);
   }
   for (const GProduce& produce : formula) {
      ret = Parse(produce); 
      if (ret) break; 
      int current = Current();
      Restore(store);
      if (print_rule) {
         printer.print_offset(level, 0x03); printf("restore: %03d -> %03d\n", current, store.store_pos);
      }
   }
   level--;
   if (print_rule) {
      printer.print_offset(level, 0x03); printf("->"); formula.head.print(printer); printf(", ret=%d ", ret);
   }
   if (ret) luck_count++; else failure_count++;
   return ret;
}

void RSyntax::clear(TNode* node)
{
   if (node) { node->clear(); delete node; } 
}
