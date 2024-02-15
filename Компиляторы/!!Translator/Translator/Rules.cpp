#include "stdafx.h"

#include "Rules.h"
#include "RSyntax.h"
#include "Maker.h"
#include "Grammar.h"

const GSymbol GSymbol::none; const GSymbol GSymbol::empty(GSymbol::gsEmpty); const GSymbol GSymbol::eof(GSymbol::gsEof);
const GSymbol GSymbol::sharp(GSymbol::gsTerminal, T_Lexeme::grSpace);
const GSymbolSet GSymbolSet::none;

GSymbol::GSymbol(const T_Lexeme &lexeme)
{
   *this = lexeme;
}

GSymbol& GSymbol::operator = (const T_Lexeme &lexeme)
{
   if (lexeme.group == T_Lexeme::grEof) {
      type = gsEof; group = T_Lexeme::grNone; lexeme_type = 0; mode = 0; value = 0;
   } else {
      type = gsTerminal; group = lexeme.group; lexeme_type = lexeme.type; mode = 0; value = lexeme.value;
   }
   return *this;
}

bool GSymbol::operator == (const GSymbol& t2) const
{ 
   return ((type == t2.type) && (formula == t2.formula) && (produce == t2.produce) && 
           ((point == t2.point) || !IsPara() && !IsPoint() && !IsMaker()) && 
           ((mode  == t2.mode ) || !IsMaker())
          ); 
}

bool GSymbol::operator <  (const GSymbol& t2) const
{ 

   if (IsPara() && t2.IsPara() || IsMaker() && t2.IsMaker()) {
      return ((point > t2.point) ||
              (point == t2.point) && ((type <  t2.type) || 
                                      (type == t2.type) && ((formula <  t2.formula) || 
                                                            (formula == t2.formula) && ((produce <  t2.produce) ||
                                                                                        (produce == t2.produce) && (mode < t2.mode) && IsMaker()
                                                                                       )
                                                           ) 
                                     ) 
             ); 
   }

   return ((type <  t2.type) || 
           (type == t2.type) && ((formula <  t2.formula) || 
                                 (formula == t2.formula) && ((produce <  t2.produce) ||
                                                             (produce == t2.produce) && IsPoint() && (point <  t2.point)
                                                            )
                                ) 
          ); 
}

bool GSymbol::IsSaved() const
{
   if (!IsTerminal()) return false;
   if ((group == T_Lexeme::grOper) || (group == T_Lexeme::grInteger) || (group == T_Lexeme::grNumber) || (group == T_Lexeme::grIdent) || (group == T_Lexeme::grPriority)) return true;
   if ((group == T_Lexeme::grReserv) && (lexeme_type >= T_Lexeme::rwVoid) && (lexeme_type <= T_Lexeme::rwDefine)) return true; 
   if ((group == T_Lexeme::grSyntax) && (lexeme_type != T_Lexeme::sxEmptyBracket) && (lexeme_type != T_Lexeme::sxEmptyCramp) && (lexeme_type != T_Lexeme::sxEmptyScrape)) return true; 
   return false;
}

bool GSymbol::Cast()
{
   if (IsTerminal()) {
      if (group == T_Lexeme::grOper) {
         const T_Symbol& symbol = symbol_table().Symbol(value);
         if (symbol.priority) {
            group = T_Lexeme::grPriority; lexeme_type = symbol.priority;
            return true;
         }
      } else if (group == T_Lexeme::grPriority) {
         const T_Symbol& symbol = symbol_table().Symbol(value);
         group = T_Lexeme::grOper; lexeme_type = symbol.type;
         return true;
      } else if (group == T_Lexeme::grSyntax) {
         if ((lexeme_type == T_Lexeme::sxDefVar) || (lexeme_type == T_Lexeme::sxDefArr)) {
            lexeme_type = T_Lexeme::sxDefType;
            return true;
         } else if (lexeme_type == T_Lexeme::sxDefType) {
            group = T_Lexeme::grReserv; lexeme_type = T_Lexeme::W_Type::rwDefine;
            return true;
         }
      }
   } else if (IsEmpty()) {
      type = gsEof;
      return true;
   } else if (IsEof()) {
      type = gsEmpty;
      return true;
   }
   return false;
}

int GSymbol::Change(int mode)
{
   int mode_change = TChangeSymbolMode::chNone;
   if ((mode & TChangeSymbolMode::chEmptyToEof) && IsEmpty()) {
      *this = GSymbol::eof; mode_change |= TChangeSymbolMode::chEmptyToEof;
   }
   if ((mode & TChangeSymbolMode::chEofToEmpty) && IsEof()) {
      *this = GSymbol::empty; mode_change |= TChangeSymbolMode::chEofToEmpty;
   }
   return mode_change;
}

bool T_Lexeme::IsSaved() const
{
   return GSymbol(*this).IsSaved();
}

bool T_Lexeme::Cast()
{
   if (group == T_Lexeme::grOper) {
      const T_Symbol& symbol = symbol_table().Symbol(value);
      if (symbol.priority) {
         group = T_Lexeme::grPriority; type = symbol.priority;
         return true;
      }
   } else if (group == T_Lexeme::grPriority) {
      const T_Symbol& symbol = symbol_table().Symbol(value);
      group = T_Lexeme::grOper; type = symbol.type;
      return true;
   } else if (group == T_Lexeme::grSyntax) {
      if ((type == T_Lexeme::sxDefVar) || (type == T_Lexeme::sxDefArr)) {
         type = T_Lexeme::sxDefType;
         return true;
      } else if (type == T_Lexeme::sxDefType) {
         group = T_Lexeme::grReserv; type = T_Lexeme::W_Type::rwDefine;
         return true;
      }
   }
   return false;
}

const char* snode_title(int t);
void tree_syn(int s, int &s1, int &s2, int &s3, int &s4, int &s5); 

int  GSymbol::print_maker(TPrinter& printer) const
{
   PRINTER_FILE_MODE;
   bool yacc_mode = (print_mode & T_PrintMode::pmYACCMode) != 0, macro_mode = (print_mode & T_PrintMode::pmMacroMode) != 0, 
        bif_mode = (print_mode & T_PrintMode::pmBIF) != 0, head_mode = (print_mode & T_PrintMode::pmProduceHead) != 0;
   bool syntax_tree = (print_mode & T_PrintMode::pmYACCStack) != 0;
   int my_mode = mode & (GSymbol::Tree | GSymbol::Code | GSymbol::Yacc | GSymbol::SNode | GSymbol::Turn | GSymbol::Call);
   const char *left_cramp = bif_mode ? "/." : "{", *right_cramp = bif_mode ? "./" : "}";
   if (head_mode) {
      left_cramp = ""; right_cramp = "";
   }
   int len_cramp = (int)strlen(left_cramp);
   const char *yacc_sufix = "";
   if (syntax_tree) {
      if (yacc_mode) {
         yacc_sufix = ",$$,$1";
         my_mode &= (GSymbol::Yacc | GSymbol::SNode);
      }
   } else {
      if (yacc_mode) {
         my_mode &= (GSymbol::Tree | GSymbol::Code | GSymbol::Turn);
      }
   }
   char buffer[20] = {};
   int len = 0;
   const char* title, *func_title, *command_title, *mode_title = "";
   if (my_mode & GSymbol::SNode) {
      func_title = snode_title(maker);
      title = "NODE";
      int s1, s2, s3, s4, s5;
      tree_syn(point, s1, s2, s3, s4, s5);
      int count_s = 0;
      if (s5) count_s = 5; else if (s4) count_s = 4; else if (s3) count_s = 3; else if (s2) count_s = 2; else count_s = 1;
      if (macro_mode) {
	      fprintf(file, "MAKE_%s(%s,L(", title, func_title); len += (int)strlen(title) + 9 + (int)strlen(func_title);
      } else {
	      fprintf(file, "%s %s(%s,(", left_cramp, title, func_title); len += len_cramp + (int)strlen(title) + 4 + (int)strlen(func_title);
      }
      if (syntax_tree) {
         s1 = point; count_s = 1;
      }
      SPRINTF(buffer,"%d",s1); fprintf(file, "%s", buffer); len += (int)strlen(buffer);
      if (count_s > 1) { SPRINTF(buffer,",%d",s2); fprintf(file, "%s", buffer); len += (int)strlen(buffer); }
      if (count_s > 2) { SPRINTF(buffer,",%d",s3); fprintf(file, "%s", buffer); len += (int)strlen(buffer); }
      if (count_s > 3) { SPRINTF(buffer,",%d",s4); fprintf(file, "%s", buffer); len += (int)strlen(buffer); }
      if (count_s > 4) { SPRINTF(buffer,",%d",s5); fprintf(file, "%s", buffer); len += (int)strlen(buffer); }
      if (macro_mode) {
         SPRINTF(buffer,",%d",param);
         fprintf(file, ")%s)", buffer); len += 2 + (int)strlen(buffer);
      } else {
         if (param || yacc_mode) SPRINTF(buffer,",%d",param); else buffer[0] = 0;
         fprintf(file, ")%s%s); %s", buffer, yacc_sufix, right_cramp); len += len_cramp + 4 + (int)strlen(buffer) + (int)strlen(yacc_sufix);
      }
   } else if (my_mode & GSymbol::Turn) {
      title = "TURN";
      command_title = turn_title(SNode::T_Turn(maker));
      func_title = snode_title(point);
      if (macro_mode) {
         SPRINTF(buffer,",%d",param);
   	   fprintf(file, "MAKE_%s(%s,%s%s)", title, command_title, func_title, buffer); 
         len += (int)strlen(title) + 8 + (int)strlen(command_title) + (int)strlen(func_title) + (int)strlen(buffer);
      } else {
         if (param || yacc_mode) SPRINTF(buffer,",%d",param); else buffer[0] = 0;
   	   fprintf(file, "%s %s(%s,%s%s); %s", left_cramp, title, command_title, func_title, buffer, right_cramp); 
         len += 2 * len_cramp + (int)strlen(title) + 6 + (int)strlen(command_title) + (int)strlen(func_title) + (int)strlen(buffer);
      }
   } else if (my_mode & GSymbol::Call) {
      title = "CALL";
      char step_buffer[20] = {};
      SPRINTF(step_buffer, "%d", step);
      func_title = snode_title(node);
      if (macro_mode) {
         SPRINTF(buffer, ",%d", param);
         fprintf(file, "MAKE_%s(%s,%s%s)", title, func_title, step_buffer, buffer);
         len += (int)strlen(title) + 8 + (int)strlen(step_buffer) + (int)strlen(func_title) + (int)strlen(buffer);
      } else {
         if (param || yacc_mode) SPRINTF(buffer, ",%d", param); else buffer[0] = 0;
         fprintf(file, "%s %s(%s,%s%s); %s", left_cramp, title, func_title, step_buffer, buffer, right_cramp);
         len += 2 * len_cramp + (int)strlen(title) + 6 + (int)strlen(step_buffer) + (int)strlen(func_title) + (int)strlen(buffer);
      }
   } else if (my_mode) {
      func_title = maker_title(maker);
      switch (my_mode) {
      case (GSymbol::Tree | GSymbol::Code | GSymbol::Yacc) : mode_title = macro_mode ? "MAKE_ALL"  : "ALL" ; break;
      case (                                GSymbol::Yacc) : mode_title = macro_mode ? "MAKE_YACC" : "YACC"; break;
      case (GSymbol::Tree | GSymbol::Code                ) : mode_title = macro_mode ? "MAKE"      : "MAKE"; break;
      case (GSymbol::Tree                                ) : mode_title = macro_mode ? "MAKE_TREE" : "TREE"; break;
      case (                GSymbol::Code                ) : mode_title = macro_mode ? "MAKE_CODE" : "CODE"; break;
      }
      if (macro_mode) {
         fprintf(file, "%s(%s)", mode_title, func_title); len += 2 + (int)strlen(func_title) + (int)strlen(mode_title);
      } else {
         if (param || yacc_mode) SPRINTF(buffer,",%d",param); else buffer[0] = 0;
         fprintf(file, "%s %s(%s%s%s); %s", left_cramp, mode_title, func_title, buffer, yacc_sufix, right_cramp); 
         len += 2 * len_cramp + 5 + (int)strlen(func_title) + (int)strlen(buffer) + (int)strlen(mode_title) + (int)strlen(yacc_sufix);
      }
   }
   return len;
}

int  GSymbol::print(TPrinter& printer, int p) const
{
   PRINTER_FILE_MODE_GRAMMAR;
   if (p != -1) print_mode = p;
   int len = 0;
   if (type == gsTerminal) {
      bool yes_print = false;
      if (print_mode & T_PrintMode::pmBNF) {
         if ((group == T_Lexeme::grOper) || (group == T_Lexeme::grSeparator)) {
            const T_Symbol& symbol = symbol_table().Symbol((T_Symbol::T_Type)lexeme_type);
            if ((lexeme_type == T_Symbol::lxOr) || (lexeme_type == T_Symbol::lxLeftCramp) || (lexeme_type == T_Symbol::lxRightCramp) ||
               (print_mode & T_PrintMode::pmBIF) && ((lexeme_type == T_Symbol::lxLeftScrape) || (lexeme_type == T_Symbol::lxRightScrape))) {
               fprintf(file, "\'%c\'", symbol.text[0]);
               len += (int)strlen(symbol.text) + 2;
            } else if (lexeme_type == T_Symbol::lxBNFSet) {
               const char *title = group_title(group), *type_title = lexeme_type_title((T_Symbol::T_Type)lexeme_type);
               fprintf(file, "%s_%s", title, type_title);
               len += (int)strlen(title) + 1 + (int)strlen(type_title);
            } else {
               fprintf(file, "%s", symbol.text);
               len += (int)strlen(symbol.text);
            }
         } else if (group == T_Lexeme::grMeta) {
            const char *title = group_title(group), *type_title = lexeme_type_title((T_Symbol::T_Type)lexeme_type);
            fprintf(file, "%s_%s", title, type_title);
            len += (int)strlen(title) + 1 + (int)strlen(type_title);
         } else if (group == T_Lexeme::grReserv) {
            const char* title = T_Lexeme::word_table->Word((T_Lexeme::W_Type)lexeme_type).text;
            fprintf(file, "%s", title);
            len += (int)strlen(title);
         } else if ((group == T_Lexeme::grIdent) && T_Lexeme::print_scan) {
            T_Lexeme lexeme(group, type); lexeme.value = value;
            const char* title = T_Lexeme::print_scan->Text(lexeme);
            fprintf(file, "%s", title);
            len += (int)strlen(title);
         } else if ((group == T_Lexeme::grIdent) || (group == T_Lexeme::grInteger) || (group == T_Lexeme::grNumber) || (group == T_Lexeme::grSpace)) {
            const char* title = group_title(group);
            fprintf(file, "%s_lexeme", title);
            len += (int)strlen(title) + 7;
         } else if (group == T_Lexeme::grSyntax) {
            const char* title_group = group_title(group); len += (int)strlen(title_group);
            const char* title_type  = lexeme_syntax_title((T_Lexeme::T_Syntax)lexeme_type); len += (int)strlen(title_type) + 1;
            fprintf(file, "%s_%s", title_group, title_type);
         } else if (group == T_Lexeme::grPriority) {
            const char* title_group = group_title(group); len += (int)strlen(title_group);
            const char* title_type  = lexeme_priority_title((T_Symbol::T_Priority)lexeme_type); len += (int)strlen(title_type) + 1;
            fprintf(file, "%s_%s", title_group, title_type);
         }
         yes_print = true;
      } else if (print_mode & T_PrintMode::pmSymbolOper) {
         if ((group == T_Lexeme::grOper) || (group == T_Lexeme::grSeparator)) {
            const T_Symbol& symbol = symbol_table().Symbol((T_Symbol::T_Type)lexeme_type);
            if (!symbol.text[1]) { // len == 1
               fprintf(file, "\'%c\'",symbol.text[0]); 
               len += 3;
               yes_print = true;
            } else {
               fprintf(file, "\'%s\'", symbol.text);
               len += (int)strlen(symbol.text) + 2;
               yes_print = true;
            }
         }
      }
      if (!yes_print) {
         fprintf(file, "<"); 
         TPrinter printer_lexeme(printer, T_PrintMode::pmPrintItem | print_mode);
         T_Lexeme lexeme(T_Lexeme::T_Group(group), lexeme_type);
         len += 2 + lexeme.print(printer_lexeme);
         fprintf(file, ">"); 
      }
   } else if (type == gsFormula) {
      const GFormula& f = *(const GFormula*)grammar->formulas[formula];
      TPrinter printer_prefix(printer, T_PrintMode::pmNone);
      len += f.write_title(printer_prefix);
   } else if (type == gsProduce) {
      const GFormula& f = *(const GFormula*)grammar->formulas[formula]; 
      const GProduce& p = f[produce];
      const char* title = f.title;
      if (title) {
         fprintf(file, "[%3d] %s", produce, title); len += 6 + (int)strlen(title); 
      } else {
         fprintf(file, "[%3d] _f_%05d_", produce, formula); len += 15;
      }
   } else if ((type == gsPara) || (type == gsPoint)) {
      const GFormula& f = *(const GFormula*)grammar->formulas[formula]; 
      const GProduce& p = f[produce];
      const char* title = f.title;
      if (title) {
         fprintf(file, "(%d)[%3d] %s"  , point, produce, title); len += 9 + (int)strlen(title); 
      } else {
         fprintf(file, "(%d)[%3d] _f_%05d_", point, produce, formula); len += 18;
      }
   } else if (type == gsMaker) {
      len += print_maker(printer);
   } else if (type == gsSituation) {
      const char* title = symbol_title(type);
	   fprintf(file, "%s: %05d", title, situation); len += (int)strlen(title) + 7;
   } else if (type == gsPoint) {
      const char* title = symbol_title(type);
	   fprintf(file, "(%s,%d,%d,%d)", title,formula,produce,point); len += (int)strlen(title);
   } else if (type == gsVector) {
      union { const TGrammar* c_grammar; TGrammar* n_grammar; } my_grammar; my_grammar.c_grammar = grammar;
      const GSymbolVector& vector = my_grammar.n_grammar->Vector(*this);
      if (vector.count() == 1) return vector.front().print(printer);
      fprintf(file, " { ");
      vector.print(printer);
      fprintf(file, " } ");
      len = SYMBOL_PRINT_TITLE_LEN;
   } else if (type == gsTable) {
      if (!(print_mode & T_PrintMode::pmTableLLk)) {
         const char* title = symbol_title(type);
         fprintf(file, "%s: %05d", title, situation); len += (int)strlen(title) + 7;
      } else {
         return grammar->GetLLkA(*this).print(printer);
      }
   } else if (type == gsEof) {
      const char* title = symbol_title((print_mode & T_PrintMode::pmEofToEmpty) ? gsEmpty : type);
      fprintf(file, "%s", title); len += (int)strlen(title);
   } else {
      const char* title = symbol_title(type);
	   fprintf(file, "%s", title); len += (int)strlen(title);
   }
   printer.trail(len, TPrinter::trLenPlus);
   return len;
}

void GSymbol::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   if (print_mode == T_PrintMode::pmWriteSymbol) {
      fprintf(file, "GSymbol(GSymbol::gs%s,%d,%d,%d,%d)",symbol_title(type),formula,produce,point,mode);
   } else if (print_mode == T_PrintMode::pmWriteZero) {
      fprintf(file, "%02d %04d %04d %04d %04d",type,formula,produce,point,mode);
   } else if (print_mode == T_PrintMode::pmWriteProg) {
      fprintf(file, "%d,%d,%d,%d,%d",type,formula,produce,point,mode);
   } else {
      fprintf(file, "%d %d %d %d %d",type,formula,produce,point,mode);
   }
}

bool GSymbol::read (FILE *file, const TGrammar* grammar, int print_mode)
{
   FSCANF(file, "%d %d %d %d %d",&type,&formula,&produce,&point,&mode);
   return true;
}

GSymbolVector::GSymbolVector(const GSymbolVector& v, int mask)
{
   for (const GSymbol& sym : v) {
      int m = 0x01 << (sym.type - 1);
      if (m  & mask) {
         Add(sym);
      }
   }
}

GSymbolVector& GSymbolVector::operator << (const GSymbolVector& v) 
{ 
   for (const GSymbol& s : v) {
      push_back(s); 
   }
   return *this; 
}

int  GSymbolVector::Find(const GSymbol& sym, int beg) const
{
   for (int i = beg; i < count(); i++) {
      if (sym == (*this)[i]) return i;
   }
   return -1;
}

void GSymbolVector::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   for (const GSymbol &item : *this) {
      item.print(printer);
      if (print_mode & T_PrintMode::pmCompact) fprintf(file, "  ");
   }
}

void GSymbolVector::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) {
   } else if (print_mode == T_PrintMode::pmWriteZero) {
      fprintf(file, "%05d\n",count());
   } else if (print_mode == T_PrintMode::pmWriteSimple) {
      fprintf(file, "%d",count());
   }
   int row = 0;
   for (const GSymbol &item : *this) {
      if ((print_mode == T_PrintMode::pmWriteSimple) || (print_mode == T_PrintMode::pmWriteZero)) fprintf(file, " ");
      if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, "{");
      item.write(printer);
      if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, "}");
      if (++row < count()) { if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, ","); }
   }
   if (print_mode == T_PrintMode::pmWriteSimple) printer.eol();
}

bool GSymbolVector::Have(const GSymbol& sym) const
{
   for (const GSymbol& item : *this) 
   {
      if (item == sym) return true;
   }
   return false;
}

bool GSymbolVector::IsEmpty() const 
{ 
#ifdef PRODUCE_ITEM_EMPTY
   return empty() || (count() == 1) && HaveEmpty();
#else
   return empty();
#endif
};

GSymbol GVectors::Add(const GSymbolVector& key)
{ 
//   if (key.empty()) return GSymbol::none;
//   if (key.IsEmpty()) return GSymbol::empty;
//   if (key.count() == 1) return key.front();
   std::map<const Key, const GSymbol>::const_iterator ip = map.find(Key(&key));
   if (ip != map.end()) {
      std::pair<const Key, const GSymbol&> item = (*ip);
      return item.second;
   }
   GSymbol sym(GSymbol::gsVector, count());
   GSymbolVector* body = new GSymbolVector(key);
   vector.push_back(body);
   std::pair<const Key, const GSymbol&> item(body, sym);
   map.insert(item);
   return sym;
}

const GSymbol& GVectors::Find(const GSymbolVector& key) const
{
   std::map<const Key, const GSymbol>::const_iterator ip = map.find(Key(&key));
   if (ip != map.end()) {
      std::pair<const Key, const GSymbol&> item = (*ip);
      return item.second;
   }
   return GSymbol::none;
}

void GVectors::clear()
{
   map.clear();
   std::vector<const GSymbolVector*>::iterator ip = vector.begin();
   while (ip != vector.end())
   {
      delete *ip; 
      ip = vector.erase(ip);
   }
}

bool GVectors::read(FILE* file, int print_mode)
{
   int my_count;
   FSCANF(file, "%d", &my_count);
   for (int i = 0; i < my_count; i++) {
      GSymbolVector body; int sym_count;
      FSCANF(file, "%d", &sym_count);
      for (int i = 0; i < sym_count; i++) {
         GSymbol sym;
         sym.read(file, NULL, print_mode);
         body << sym;
      }
      Add(body);
   }
   return true;
}

void GVectors::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) {
      fprintf(file, "\nvoid make_vectors(TGrammar& grammar)\n{\n");
   } else {
      fprintf(file, "%d\n", count());
   }
   for (const GSymbolVector* body : vector)
   {
      if (print_mode == T_PrintMode::pmWriteProg) {
         fprintf(file, "{ static const int I[][5] = {");
      }
      body->write(printer);
      if (print_mode == T_PrintMode::pmWriteProg) {
         fprintf(file, "}; ");
         fprintf(file, "grammar.AddVector(");
         fprintf(file, "%d, I);", body->count());
         fprintf(file, " }");
         printer.eol();
      }
   }
   if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) {
      fprintf(file, "}\n");
   }
}

int GSymbolSet::operator += (const GSymbol& s)
{
   int ret = Add(s);
   return ret;
}

GSymbolSet& GSymbolSet::operator << (const GSymbol& s)
{
   Add(s);
   return *this;
}

int GSymbolSet::operator += (const GSymbolSet& m)
{
   int ret = 0;
   for (const GSymbol& item : m) {
      if (Add(item)) ret++;
   }
   return ret;
}

GSymbolSet GSymbolSet::operator * (const GSymbolSet& join) const
{
   GSymbolSet ret;
   for (const GSymbol& sym : join) {
      if (Have(sym)) ret += sym;
   }
   return ret;
}

GSymbolSet GSymbolSet::operator - (const GSymbolSet& join) const
{
   GSymbolSet ret;
   for (const GSymbol& sym : (*this)) {
      if (!join.Have(sym)) ret += sym;
   }
   return ret;
}

bool GSymbolSet::Have(const GSymbol& sym) const
{ 
   const_iterator ip = find(sym); 
   return (ip != end());
}

bool GSymbolSet::IsEmpty() const
{
#ifdef PRODUCE_ITEM_EMPTY
   return empty() || (count() == 1) && HaveEmpty();
#else
   return empty();
#endif
};


bool GSymbolSet::Add(const GSymbol& sym)
{ 
   const_iterator ip = find(sym); 
   if (ip != end()) return false;
   insert(sym);
   return true; 
}

bool GSymbolSet::Del(const GSymbol& sym)
{
   const_iterator ip = find(sym);
   if (ip == end()) return false;
   erase(ip);
   return true;
}

void GSymbolSet::Plus(const GSymbolSet& left, const GSymbolSet& right)
{
   GSymbolSet& result = *this;
   if (left.empty())  { result = right; return; }
   if (right.empty()) { result = left;  return; }
   for (const GSymbol& v1 : left) {
      if (v1.IsEmpty()) {
         result += right;
      } else {
         result += v1;
      }
   }
}

void GSymbolSet::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   int i = 0;
   for (const GSymbol& item : *this) {
      if (!(i++ % 10) && (i > 1) && (print_mode & T_PrintMode::pmMultiLine) || (print_mode & T_PrintMode::pmPrintItem)) {
         printer.eol();
         if (print_mode & T_PrintMode::pmSpaces) fprintf(file, "   ");
         int len = 0;
         printer.trail(len, TPrinter::trOffset);
      }
      item.print(printer);
      if (print_mode & T_PrintMode::pmCompactGroup) fprintf(file, "   ");
   }
}

void TTwoSym::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   fprintf(file, "{");
   if (!one.IsNone() || !(print_mode & T_PrintMode::pmNoPrintNone)) {
      one.print(printer);
   } else {
      int len = SYMBOL_PRINT_TITLE_LEN;
      printer.offset(len, false);
   }
   fprintf(file, ","); two.print(printer); fprintf(file, "}");
}

bool TwoSymGSymbolSetMap::Add(const TTwoSym& key, const GSymbol& sym)
{
   iterator ip = find(key);
   if (ip == end()) {
      std::pair<const TTwoSym&, GSymbolSet> item(key, GSymbolSet());
      insert(item);
      ip = find(key);
   }
   return (*ip).second.Add(sym);
}

const GSymbolSet& TwoSymGSymbolSetMap::Get(const TTwoSym& key) const
{
   const_iterator ip = find(key);
   return (ip == end()) ? GSymbolSet::none : (*ip).second;

}

bool TRuleNames::verify(const GFormulaTable& formulas) const
{
	printf("\n--- RuleNames --- <%d> ---\n", (int)indexs.size());
   bool ret = true;
   return ret;
}

bool GProduce::IsEmpty(bool maker) const
{
   for (const GSymbol &sym : *this) {
      if (!sym.IsEmpty() && (!maker || !sym.IsMaker())) return false;
   }
   return true;
}

bool GProduce::IsChain() const
{
   return (count() == 1) && maker.IsNone() && front().IsFormula();
}

bool GProduce::HaveMaster() const
{
   bool ret = false;
   for (const GSymbol &sym : *this) {
      if (sym.mode & GSymbol::Master) { ret = true; break; }
   }
   return ret;
}

void GProduce::Tail(int point, GSymbolVector& tail) const
{
   for (int i = point; i < count(); i++) {
      tail << (*this)[i];
   }
}

void GProduce::TailWithoutMaker(int point, GSymbolVector& tail) const
{
   for (int i = point; i < count(); i++) {
      const GSymbol& sym_tail = (*this)[i];
      if (sym_tail.IsMaker()) continue;
      tail << sym_tail;
   }
}

int  GProduce::Count() const
{
#ifdef PRODUCE_ITEM_EMPTY
   int ret = 0;
   for (const GSymbol &sym : *this) {
      if (sym.IsTerminal() || sym.IsFormula()) ret++;
   }
   return ret;
#else
   return count();
#endif
}

int  GProduce::Real(int mode) const
{
   int ret = 0;
   for (const GSymbol &sym : *this) {
      if ((sym.IsTerminal() && (sym.IsSaved() || (mode & 0x01) && (sym == GSymbol::sharp))) || sym.IsFormula()) ret++;
   }
   return ret;
}

int  GProduce::Master() const
{
   int master = 0, index = 0;
   for (const GSymbol &sym : *this) {
      index++;
      if (sym.IsMaster()) {
         if (master) return 0;
         master = index;
      }
   }
   return master;
}

int  GProduce::MasterMask() const
{
   int mask = 0, bit = 1;
   for (const GSymbol &sym : *this) {
      if (sym.IsFormula() && (sym.formula == head.formula)) {
         mask |= bit;
      }
      bit <<= 1;
   }
   return mask;
}

bool GProduce::Compare(const GProduce& join) const
{
   if (count() != join.count()) return false;
   if (!(maker == join.maker)) return false;
   for (int i = 0; i < count(); i++) {
      const GSymbol& item = (*this)[i];
      const GSymbol& item_join = join[i];
      if (!(item == item_join)) return false;
   }
   return true;
}

void GProduce::Add(const GSymbol& s)
{ 
#ifndef PRODUCE_ITEM_EMPTY
   if (s.IsEmpty()) return;
#endif
   push_back(s); 
}

void GProduce::Shift(GSymbol& para) const
{
   para.point++;
}

void GProduce::write(TWriter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   if (print_mode == T_PrintMode::pmWriteSymbol) {
      fprintf(file, "grammar.AddProduce(");
   } else if (print_mode != T_PrintMode::pmWriteProg) {
      fprintf(file, "%d ",count());
   }
   if ((print_mode != T_PrintMode::pmWriteProg) && ((print_mode != T_PrintMode::pmWriteSymbol) || maker.IsMaker())) {
      maker.write(printer); 
   }
   if (print_mode == T_PrintMode::pmWriteSymbol) {
      fprintf(file, ");\n");
   } else if (print_mode != T_PrintMode::pmWriteProg) {
      fprintf(file, " ");
   }
   if (print_mode == T_PrintMode::pmWriteProg) {
      fprintf(file, "{ static const int I[][5] = {");
   }
   int row = 0;
   for (const GSymbol& item : *this) {
      if (print_mode == T_PrintMode::pmWriteSymbol) fprintf(file, "grammar.AddItem(");
      if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, "{");
      item.write(printer); 
      if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, "}");
      if (print_mode == T_PrintMode::pmWriteSymbol) fprintf(file, ");");
      if (++row < count()) { if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, ","); else fprintf(file, " "); }
   }
   if (print_mode == T_PrintMode::pmWriteProg) {
      if (empty()) { 
         fprintf(file, "{"); 
#ifdef PRODUCE_ITEM_EMPTY
         GSymbol::empty.write(printer);
#endif
         fprintf(file, "}"); 
      }
      fprintf(file, "}; ");
      fprintf(file, "grammar.AddProduce(");
      if (!maker.IsNone()) {
         TPrinter printer_maker(printer, T_PrintMode::pmWriteSymbol);
         maker.write(printer_maker);
         fprintf(file, ", ");
      }
      fprintf(file, "%d, I);",count());
      fprintf(file, " }");
   }
   printer.eol();
}

bool GProduce::read (FILE *file, const TGrammar* grammar, int print_mode)
{
   int my_count;
   FSCANF(file,"%d",&my_count);
   maker.read(file, grammar,print_mode);
   for (int i = 0; i < my_count; i++) {
      GSymbol sym;
      sym.read(file, grammar,print_mode);
      Add(sym);
   }
   return true;
}

void GProduce::print(TPrinter& printer, int point) const
{
   PRINTER_FILE_MODE_GRAMMAR
   int len = 0;
   if (print_mode & T_PrintMode::pmProduceHead) {
      len += head.print(printer);
      len = 0;
      if (print_mode & T_PrintMode::pmCompact) { fprintf(file, "   "); len += 3; }
      if (!maker.IsNone()) {
         len += maker.print(printer) - 1;
      }
      printer.trail(len, TPrinter::trLen | TPrinter::trMaker | TPrinter::trElse);
   }
   if (!(print_mode & T_PrintMode::pmGrammar)) fprintf(file, "-> ");
   bool compact = (print_mode & T_PrintMode::pmCompactGroup) != 0;
   int  i = 0;
   TPrinter printer_item(printer, print_mode & ~T_PrintMode::pmProduceHead);
   for (const GSymbol& item : *this) {
      if ((print_mode & T_PrintMode::pmWithoutMaster) && item.IsFormula() && (item.formula == head.formula)) {
         i++; continue;
      }
      if (i == point) fprintf(file, " . ");
      bool used_one = false;
      if (head.formula && (print_mode & T_PrintMode::pmBIF) && item.IsFormula()) {
         const GFormula& formula = printer.grammar->Formula(item);
         if (formula.used == 1) {
            TPrinter printer_used(printer, print_mode | T_PrintMode::pmProduceOnly);
            printer_used.shift(SYMBOL_PRINT_TITLE_LEN); //  printer.length;
            formula.print(printer_used);
            used_one = true;
         }
      }
      if (!used_one) {
         int len = item.print(printer_item);
         printer_item.trail(len, TPrinter::trSkip);
      }
      i++;
      if ((i != point) && (i < count()) && compact) fprintf(file, "   ");
   }
   if (i == point) fprintf(file, " . ");
}

bool GFormula::HaveEmpty(bool maker) const
{
   bool ret = !size();
   for (const GProduce& produce : (*this)) {
      if (produce.IsEmpty(maker)) return true;
   }
   return ret;
}

bool GFormula::HaveChain() const
{
   for (const GProduce& produce : (*this)) {
      if (produce.IsChain()) return true;
   }
   return false;
}

bool GFormula::Compare(const GFormula& join) const
{
   if (count() != join.count()) return false;
   for (int p = 0; p < count(); p++) {
      const GProduce& produce = (*this)[p];
      const GProduce& produce_join = join[p];
      if (!produce.Compare(produce_join)) return false;
   }
   return true;
}

bool GFormula::IsRecursive() const
{
   for (const GProduce& produce : (*this)) {
      if (produce.HaveMaster()) return true;
   }
   return false;
}

// Purple(p=277,a=4.8,4.3.3)
bool GFormula::ReplaceFirst(const GFormula& formula_first)
{
   bool ret = false;
   if (head == formula_first.head) return false;
   iterator i_f = begin();
   while (i_f != end()) {
      GProduce& produce = (*i_f);
      if (produce.count()) {
         const GSymbol& first_sym = produce.front();
         if (first_sym.IsFormula() && (first_sym == formula_first.head)) {
            produce.erase(produce.begin()); // delete first_sym
            if (formula_first.count() > 1) {
               iterator i_insert = i_f;
               i_insert = insert(++i_insert, formula_first.count() - 1, produce);
               i_f = i_insert - 1;
            }
            for (const GProduce& produce_first : formula_first) {
               GProduce& produce = (*i_f);
               GProduce::iterator i_p_insert = produce.count() ? produce.begin() : produce.end();
               for (const GSymbol& gamma_sym : produce_first) {
                  i_p_insert = produce.insert(i_p_insert, gamma_sym);
                  i_p_insert++;
               }
               i_f++;
            }
            ret = true;
            continue;
         }
      }
      i_f++;
   }
   if (ret) {
      int p = 0;
      for (GProduce& produce : (*this)) {
         produce.head.produce = p++;
      }
   }
   return ret;
}

void GFormulaTable::terminal_only_first()
{
   for (GFormula* formula : (*this)) {
      formula->prepared = T_Perepare::prNone;
   }
   bool yes_change;
   do {
      yes_change = false;
      for (GFormula* formula : (*this)) {
         if (formula->prepared == T_Perepare::prTerminalOnly) continue;
         bool terminal_only = true;
         for (const GProduce& produce : (*formula)) {
            if (produce.empty()) continue;
            const GSymbol& first_item = produce.front();
            if (first_item.IsTerminal()) continue;
            if (first_item.IsFormula()) {
               const GFormula& formula_item = *(*this)[first_item.formula];
               if (formula_item.prepared == T_Perepare::prTerminalOnly) continue;
            }
            terminal_only = false;
            break;
         }
         if (terminal_only) {
            formula->prepared = T_Perepare::prTerminalOnly;
            yes_change = true;
         }
      }
   } while (yes_change);
}

// Purple(p=277,a=4.8,4.3.3)
// Green(v=1,p=180,a=2.13,2.4.4)
bool GFormulaTable::delete_left_recursion(bool terminal_only)
{
   bool ret = false;
   if (terminal_only) terminal_only_first();
   for (int i = 0; i < count(); i++) {
      GFormula& formula_A_i = *(*this)[i];
      for (int j = 0; j < i; j++) {
         const GFormula& formula_A_j = *(*this)[j];
         if (terminal_only && (formula_A_j.prepared == T_Perepare::prTerminalOnly)) continue;
         if (formula_A_i.ReplaceFirst(formula_A_j)) ret = true;
      }
      if (formula_A_i.DeleteImmediateLeftRecursion(*this)) ret = true;
   }
   return ret;
}

// Purple(p=276,4.3.3)
bool GFormula::DeleteImmediateLeftRecursion(GFormulaTable& table)
{
   bool ret = false;
   std::vector<bool> recursive;
   int alpha_count = 0, beta_count = 0;
   for (const GProduce& produce : (*this)) {
      if (produce.count()) {
         const GSymbol& first_sym = produce.front();
         if (first_sym.IsFormula() && (first_sym.formula == head.formula)) {
            recursive.push_back(true); ret = true; alpha_count++;
            continue; 
         }
      }
      recursive.push_back(false); beta_count++;
   }
   if (!ret) return ret;
   GSymbol A_(GSymbol::gsFormula, table.count());
   GFormula* formula_A_ = new GFormula(A_);
   int p = 0; alpha_count = 0, beta_count = 0;
   for (GProduce& produce : (*this)) {
      if (recursive[p++]) {
         produce.erase(produce.begin());
         produce.Add(A_);
         produce.head.formula = A_.formula;
         produce.head.produce = alpha_count++;
         formula_A_->Add(produce);
      } else {
         produce.push_back(A_);
         produce.head.produce = beta_count++;
      }
   }
   GProduce produce(GSymbol(GSymbol::gsProduce, A_.formula, alpha_count)); // empty
   formula_A_->Add(produce);
   table.push_back(formula_A_);
   p = 0;
   iterator i_f = begin();
   while (i_f != end()) {
      if (recursive[p++]) i_f = erase(i_f); else i_f++;
   }
   return ret;
}

void GFormula::print(TPrinter& printer) const
{
   BREAK_POINT_TITLE(title, "Assign")
   BREAK_POINT_END
   PRINTER_FILE_MODE_GRAMMAR
   int  len_formula = 0;
   bool bif_mode = (print_mode & T_PrintMode::pmBIF) && ((count() > 1)/* || (print_mode & T_PrintMode::pmProduceOnly)*/), yes_empty = bif_mode && HaveEmpty(false);
   int  master_index = 0, master_mask = 0, item_index = 0;
   if (bif_mode && (print_mode & T_PrintMode::pmGrammar) && prepared) {
      switch (prepared) {
      case prNone:  master_index = 0, master_mask = 0x00, item_index = 0;                   break;
      case prLR_0:  master_index = 0, master_mask = 0x01, item_index = 1; bif_mode = false; break;
      case prLR_1:  master_index = 1, master_mask = 0x01, item_index = 0; bif_mode = false; break;
      case prLL_0:  master_index = 0, master_mask = 0x02, item_index = 1; bif_mode = false; break;
      case prLL_1:  master_index = 1, master_mask = 0x02, item_index = 0; bif_mode = false; break;
      case prLR_N1:                   master_mask = 0x01;                 bif_mode = false; break;
      case prLR_1M:                   master_mask = 0x01;                 bif_mode = false; break;
      case prLR_NM:                   master_mask = 0x01;                 bif_mode = false; break;
      case prEqu_0: master_index = 1,                     item_index = 0; bif_mode = false; break;
      case prEqu_1: master_index = 0,                     item_index = 1; bif_mode = false; break;
      }
   }
   if ((prepared == T_Perepare::prLR_N1) || (prepared == T_Perepare::prLR_1M)) {
      int index = 0;
      for (const GProduce& produce : (*this)) {
         int produce_mask = produce.prepare_mask;
         if ((produce_mask == 0x01) && (prepared == T_Perepare::prLR_1M)) {
            master_index = index; break;
         } else if ((produce_mask == 0x00) && (prepared == T_Perepare::prLR_N1)) {
            item_index = index; break;
         }
         index++;
      }
   }
   if (!(print_mode & T_PrintMode::pmProduceOnly)) {
      printer.eol();
      if (print_mode & T_PrintMode::pmGrammar) {
         len_formula = head.print(printer);
         if (print_mode & T_PrintMode::pmCompact) len_formula = 10;
         int len = (print_mode & T_PrintMode::pmCompact) ? len_formula : SYMBOL_PRINT_TITLE_LEN;
         printer.offset(len);
         fprintf(file, (print_mode & T_PrintMode::pmBNF) ? "::= " : ":   ");
         if (bif_mode) {
            fprintf(file, yes_empty ? "[ " : "{ ");
            printer.offset(len + 4);
         }
         printer.shift(len);
      } else {
         TPrinter printer_head(printer, print_mode | T_PrintMode::pmCompact);
         len_formula = head.print(printer_head);
         fprintf(file, ":"); 
         len_formula += (print_mode & T_PrintMode::pmProduceHead) ? 1 : -2;
         printer.trail(len_formula, TPrinter::trElse);
         fprintf(file, "used=%d, %05d", used, head.formula);
      }
   } else {
      if (bif_mode) {
         printer.offset(4);
         fprintf(file, yes_empty ? "[ " : "{ ");
         printer.offset(4);
      }
   }
   if (master_mask) {
      if (master_mask == 0x01) {
         if ((prepared == T_Perepare::prLR_0) || (prepared == T_Perepare::prLR_1) || (prepared == T_Perepare::prLR_N1)) {
            (*this)[item_index].print(printer);
            fprintf(file, "   ");
         } else if ((prepared == T_Perepare::prLR_1M) || (prepared == T_Perepare::prLR_NM)) {
            printer.offset(0);
            fprintf(file, "{"); 
            printer.offset(0);
            int produce_count = 0;
            for (const GProduce& produce : (*this)) {
               int produce_mask = produce.prepare_mask;
               if (produce_mask != 0x00) continue;
               if (produce_count++) {
                  int len = -4;
                  printer.offset(len);
                  fprintf(file, "|   ");
               }
               produce.print(printer);
            }
            printer.offset(0);
            fprintf(file, "}   ");
         }
      }
      printer.offset(0);
      fprintf(file, "["); len_formula = -2;
      printer.offset(0);
      TPrinter printer_no_first(printer, print_mode | T_PrintMode::pmWithoutMaster);
      printer_no_first.shift(printer.length);
      if ((prepared == T_Perepare::prLR_1M) || (prepared == T_Perepare::prLR_NM)) {
         int produce_count = 0;
         for (const GProduce& produce : (*this)) {
            int produce_mask = produce.prepare_mask;
            if (produce_mask != 0x01) continue;
            if (produce_count++) {
               int len = -4;
               printer.offset(len);
               fprintf(file, "|   ");
            }
            produce.print(printer);
         }
      } else {
         (*this)[master_index].print(printer_no_first);
      }
      printer.offset(0);
      fprintf(file, "]... ");
      return;
   }
   if ((prepared == T_Perepare::prEqu_0) || (prepared == T_Perepare::prEqu_1)) {
      const GProduce& produce_item = (*this)[item_index];
      const GProduce& produce_master = (*this)[master_index];
      produce_item.print(printer);
      fprintf(file, " [ ");
      produce_master.print(printer);
      fprintf(file, " ] ");
      return;
   }
   int produce_count = 0;
   for (const GProduce& produce : (*this)) {
      if (print_mode & T_PrintMode::pmGrammar) {
         if (bif_mode && produce.IsEmpty(false)) continue;
         if (produce_count++) {
            int len = 0;
            printer.offset(len);
            fprintf(file, "|   ");
         }
      } else {
         printer.eol();
      }
      produce.print(printer);
   }
   if (print_mode & T_PrintMode::pmGrammar) {
      int len = 0;
      printer.offset(len);
      if (bif_mode) {
         fprintf(file, yes_empty ? "    ] " : "    } ");
      } else if (!(print_mode & T_PrintMode::pmBNF)) {
         fprintf(file, ";");
      }
   }
}

void GFormula::write(TWriter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) {
      fprintf(file, "grammar.AddFormula(\"");
   } else {
      fprintf(file, "%d ",count());
   }
   if (title) {
      fprintf(file, "%s",title);
   } else {
      fprintf(file, "_f_%05d_",head.formula);
   }
   if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) {
      fprintf(file, "\");\n");
   } else {
      printer.eol();
   }
   for (const GProduce& produce : (*this)) {
      produce.write(printer);
   }
}

bool GFormula::read (FILE *file, const TGrammar* grammar, int print_mode)
{
   int my_count;
   char buffer[50];
   FSCANF(file,"%d ",&my_count);
   FSCANF(file,"%50s",buffer,50);
//   fscanf_s(file,"%d %50s",&my_count,&buffer);
   size_t len = strlen(buffer); 
   char* my_title = (char*)malloc(len + 1);
   STRCPY(my_title,len + 1,buffer); 
   title = my_title;
   for (int i = 0; i < my_count; i++) {
      const GProduce produce_(GSymbol(GSymbol::gsProduce,head.formula,i));
      Add(produce_);
      GProduce& produce = back();
      produce.read(file,grammar,print_mode);
   }
   return true;
}

int  GFormula::write_title(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   int len = 0;
   const char *my_prefix = (print_mode & T_PrintMode::pmPrintPrefix) ? grammar->prefix : "";
   if (title) {
      fprintf(file, "%s%s", my_prefix, title); len += (int)strlen(my_prefix) + (int)strlen(title);
   } else {
      fprintf(file, "%s_f_%05d_", my_prefix, head.formula); len += (int)strlen(my_prefix) + 4 + 5;
   }
   return len;
}

GFormulaTable::GFormulaTable(const GFormulaTable& join)
  :root(NULL), readed(false) 
{
   for (const GFormula* item : join) {
      push_back(new GFormula(*item));
   }
   if (join.root) {
      root = (*this)[join.root->head.formula];
   }
}

GFormulaTable::~GFormulaTable()
{
   for (const GFormula* item : (*this)) {
      if (readed) { delete item->title; }
//      delete item;
   }
}

void GFormulaTable::Copy(const GFormulaTable& join)
{
   for (const GFormula* item : join) {
      push_back(new GFormula(*item));
   }
}

void GFormulaTable::prepare(TPrinter& printer)
{
   PRINTER_FILE_MODE
   for (GFormula *formula : *this) {
      BREAK_POINT_TITLE(formula->title, "DefRanges")
      BREAK_POINT_END
      FORMULA_DELETED_CONTINUE(formula);
      if (formula->used < 1) continue;
      int pre = T_Perepare::prNone;
      bool bif_mode = true;
      int  master_index = 0, master_mask = 0, item_index = 0;
      if (formula->count() == 2) {
         master_mask = (*formula)[0].MasterMask(); (*formula)[0].prepare_mask = master_mask;
         int item_mask = (*formula)[1].MasterMask(); (*formula)[1].prepare_mask = item_mask;
         if ((master_mask == 0x01) && (item_mask == 0x00)) {
            item_index = 1; bif_mode = false;
            pre = T_Perepare::prLR_0;
         } else if ((master_mask == 0x00) && (item_mask == 0x01)) {
            master_index = 1; master_mask = item_mask; bif_mode = false;
            pre = T_Perepare::prLR_1;
         } else {
            if ((master_mask > 0x01) && (item_mask == 0x00)) {
               item_index = 1; bif_mode = false;
               pre = T_Perepare::prLL_0;
            } else if ((master_mask == 0x00) && (item_mask > 0x01)) {
               master_index = 1; master_mask = item_mask; bif_mode = false;
               pre = T_Perepare::prLL_1;
            }
            if (!bif_mode) {
               const GProduce& produce_master = (*formula)[master_index];
               int mask = (0x01 << (produce_master.count() - 1));
               if ((master_mask != mask) || !(*formula)[item_index].IsEmpty(false)) {
                  master_mask = 0; bif_mode = true;
                  pre = T_Perepare::prNone;
               }
            }
         }
         if (!pre) {
            const GProduce& produce_one = (*formula)[0];
            const GProduce& produce_two = (*formula)[1];
            int equ_count = 0, one_count = produce_one.count(), two_count = produce_two.count();
            for (int i = 0; (i < one_count && (i < two_count)); i++, equ_count++) {
               if (!(produce_one[i] == produce_two[i])) break;
            }
            if (equ_count) {
               if ((equ_count == one_count) && (equ_count == two_count)) {
                  formula->erase(formula->end());
               } else if (equ_count == one_count) {
                  pre = T_Perepare::prEqu_0;
                  master_index = 1; item_index = 0;
               } else if (equ_count == two_count) {
                  pre = T_Perepare::prEqu_1;
                  master_index = 0; item_index = 1;
               } else {
               }
            }
         }
      } else if (formula->count() > 2) {
         int count = formula->count(), count_LR = 0, count_simple = 0;
         for (GProduce& produce : (*formula)) {
            int produce_mask = produce.MasterMask(); produce.prepare_mask = produce_mask;
            if (produce_mask == 0x01) {
               count_LR++;
            } else if ((produce_mask == 0x00) && !produce.IsEmpty(false)) {
               count_simple++;
            }
         }
         if (count_LR && count_simple && ((count_LR + count_simple) == count)) {
            pre = (count_LR > 1) ? ((count_simple > 1) ? T_Perepare::prLR_NM : T_Perepare::prLR_N1) : (T_Perepare::prLR_1M);
         }
      }

      if (pre && !((pre == T_Perepare::prEqu_0) || (pre == T_Perepare::prEqu_1))) {
         for (GProduce& produce : (*formula)) {
            GProduce::iterator ip = produce.begin();
            while (ip != produce.end()) {
               GSymbol& sym = (*ip);
               if (sym.IsFormula() && (sym.formula == produce.head.formula)) { // Master
                  ip = produce.erase(ip);
                  formula->used--;
               } else {
                  ip++;
               }
            }
         }
      }
      if ((pre == T_Perepare::prEqu_0) || (pre == T_Perepare::prEqu_1)) {
         int equ_count = (*formula)[item_index].count();
         for (int i = 0; i < equ_count; i++) {
            (*formula)[master_index].erase((*formula)[master_index].begin());
         }
      }
      formula->prepared = pre;
   }
}

void GFormulaTable::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   if (print_mode == 0x00) return;
   if (print_mode & T_PrintMode::pmBIF) {
      root->print(printer); // S_
      const GProduce& produce = root->front();
      const GSymbol& sym = produce.front();
      if (sym.IsFormula()) {
         printer.shift();
         const GFormula *formula_program = (*this)[sym.formula];
         formula_program->print(printer); // Programm
         formula_program->used = 0;
      }
   }
   for (const GFormula *formula : *this) {
      FORMULA_DELETED_CONTINUE(formula);
      if ((print_mode & T_PrintMode::pmBIF) && (formula->used <= 1)) continue;
      printer.shift();
      formula->print(printer);
   }
   printer.eol();
}

const char* symbol_title(GSymbol::T_Type type)
{
   static const char* title[] = {
      "None", "Formula", "Produce", "Terminal", "Vector", "Empty", "Eof", "Maker", "Rule", "Point", "Para", "Situation", "Table"
   };
   if ((type < 0) || (type >= sizeof(title))) return "### error ###";
   return title[type];
}

bool GFormulaTable::Add(GFormula* f, int &index)
{
   for (int i = 0; i < (int)(*this).size(); i++) {
      const GFormula *formula = (*this)[i];
      if (formula->title && !strcmp(formula->title, f->title)) {
         index = i;
         return false;
      }
   }
   push_back(f);
   index = count() - 1;
   return true;
}

GFormula* GFormulaTable::Find(const char* title)
{
   for (int i = 0; i < (int)(*this).size(); i++) {
      GFormula *formula = (*this)[i];
      if (formula->title && !strcmp(formula->title, title)) {
         return formula;
      }
   }
   return NULL;
}

bool GFormulaTable::Find(const GFormula& f, int &index) const
{
   for (int i = 0; i < (int)(*this).size(); i++) {
      const GFormula *formula = (*this)[i];
      if (formula->Compare(f)) {
         index = i;
         return true;
      }
   }
   return false;
}

bool GFormulaTable::make(TRuleNames& names)
{
   bool ret = names.verify(*this);
   printf("\n");
   std::vector<int> N2F;

   int max = (names.Count() > count()) ? names.Count() : count();
   N2F.resize(max, -1);
   for (int f = 0; f < count(); f++) {
      const GFormula *formula = (*this)[f];
      if (formula->head.formula >= 0) N2F[formula->head.formula] = f;
   }

   TNameTable errors;
   for (GFormula *formula : *this) {
      formula->head.formula = (formula->head.formula >= 0) ? N2F[formula->head.formula] : -formula->head.formula;
      for (GProduce& produce: *formula) {
         produce.head.formula = formula->head.formula;
         for (GSymbol& sym : produce) {
            if (sym.IsFormula()) {
               if (sym.formula >= 0) {
                  int order_formula = sym.formula;
                  sym.formula = N2F[sym.formula];
                  if (sym.formula < 0) {
                     errors.Add(names.Name(order_formula));
                     ret = false;
                  }
               } else {
                  sym.formula = -sym.formula;
               }
            }
         }
      }
   }

   if (errors.Count()) {
      fprintf(stdout, "\nno rules:\n");
      for (int i = 0; i < errors.Count(); i++) {
         fprintf(stdout, "%s\n", errors.Name(i));
      }
   }
   root = front();

   return ret;
}

bool GFormulaTable::make(TRuleNames& names,TLexemeSet& lexemes)
{
   bool ret = make(names);

   root = front();
   Used(lexemes);
   return ret;
}

void GFormulaTable::used_for_all()
{
   for (const GFormula* formula : (*this)) {
      formula->used = 0;
   }
   for (const GFormula* formula : (*this)) {
      for (const GProduce& produce : *formula) {
         for (const GSymbol& sym : produce) {
            if (sym.IsFormula()) {
               GFormula& used_formula = *(*this)[sym.formula];
               used_formula.used++;
            }
         }
      }
   }
}

void GFormulaTable::used_for_root()
{
   used.clear();
   used.resize(count(),0);
   for (const GFormula* formula : *this) {
      formula->used = 0;
   }
   root = front();
   Used(*root);
}

int  GFormulaTable::deleting_chains(bool without_name)
{
   int deleted_count = 0;
   used_for_root();

   for (GFormula *formula : *this) {
      if (!formula->used || (formula == root)) continue;
      int optimization_mode = 0;
      GFormula* target_formula = NULL;
      for (GProduce& produce : *formula) {
         if ((produce.count() == 1) && produce.maker.IsNone()) {
            const GSymbol& sym = produce.front();
            if (sym.IsFormula()) {
               target_formula = (*this)[sym.formula];
               if (target_formula == formula) continue;
               if (without_name && target_formula->title) continue;
               if (target_formula->used == 1) {
                  if (formula->count() == 1) {
                     optimization_mode = 1;
                  } else if (target_formula->count() == 1) {
                     optimization_mode = 2;
                  }
               }
            }
            if (optimization_mode == 2) {
               GSymbol old_head = produce.head;
               produce = target_formula->front();
               produce.head = old_head;
               target_formula->clear();
               target_formula->used--;
               deleted_count++;
               optimization_mode = 0;
            }
         }
      }
      if (optimization_mode == 1) {
         formula->erase(formula->begin());
         for (const GProduce& target_produce : *target_formula) {
            formula->push_back(target_produce);
         }
         target_formula->clear();
         target_formula->used--;
         deleted_count++;
      }
   }
   return deleted_count;
}

void GFormulaTable::delete_temporary_title(bool del)
{
   for (GFormula *formula : *this) {
      if (formula->title && (!strncmp(formula->title,"_f_0",4))) {
         if (del) delete formula->title;
         formula->title = NULL;
      }
   }
}

void GFormulaTable::Used(TLexemeSet& lexemes)
{
   used_for_root();

   int new_formula = 0;
   for (int& cur_formula : used) {
      cur_formula = cur_formula ? new_formula++ : -1;
   }
   lexemes.clear();
   for (GFormula* formula : *this) {
      int new_formula = used[formula->head.formula];
      formula->head.formula = new_formula;
      if (new_formula < 0) continue;
      for (GProduce& produce : *formula) {
         produce.head.formula = new_formula;
         for (GSymbol& sym : produce) {
            if (sym.IsFormula()) {
               sym.formula = used[sym.formula];
            } else if (sym.IsTerminal()) {
               lexemes.Add(sym);
            }
         }
      }
   }
   iterator ip = begin();
   while(ip != end()) {
      GFormula* formula = *ip;
      if (formula->head.formula < 0) {
         ip = erase(ip);
         delete formula;
      } else {
         ip++;
      }
   }
}

void GFormulaTable::Used(const GFormula& formula)
{
   used[formula.head.formula]++;
   if (formula.used++) return;
   for (const GProduce& produce : formula) {
      for (const GSymbol& sym : produce) {
         if (sym.IsFormula()) {
            const GFormula& used = *(*this)[sym.formula];
            Used(used);
         }
      }
   }
}

void TGrammar::Used()
{
   if (empty()) return;
   formulas.Used(lexemes);
   make_produces();
}

void GFormulaTable::write(TWriter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR
   if (print_mode == T_PrintMode::pmWriteSimple) {
      fprintf(file, "%d\n",count());
   } else if (print_mode == T_PrintMode::pmWriteZero) {
      fprintf(file, "%05d\n",count());
   } else if (print_mode == T_PrintMode::pmWriteSymbol) {
   }
   for (const GFormula *formula : *this) {
      formula->write(printer);
   }
   if (print_mode == T_PrintMode::pmWriteSymbol) {
   }
}

bool GFormulaTable::read(const char* title, int print_mode)
{
   FILE *file = NULL;
   if (!title) title = "formula_table.txt";
	FOPEN(file, title, "r");
   if (!file) return false;
   read (file, print_mode);
   fclose(file);
   return true;
}

bool GFormulaTable::read(FILE* file, int print_mode)
{
   clear();
   readed = true;
   int my_count, index;
   FSCANF(file,"%d",&my_count);
   for (int i = 0; i < my_count; i++) {
      GFormula* formula = new GFormula(GSymbol(GSymbol::gsFormula,i));
      formula->read(file,NULL,print_mode);
      if (!Add(formula, index)) return false;
   }
   if (count()) root = front();
   return true;
}

TData::TData(TGrammar* g, A_Syntax* syn, TSemantic* sem)
   :names(NULL), grammar(g), formulas(g ? &g->formulas : NULL), root(NULL), 
    lexemes(NULL), makers(NULL), LLTable(g ? &g->Mtable : NULL), LRTable(g ? &g->LRtable : NULL),
    syntax(syn), semantic(sem), option(0), print_mode(0), file(NULL) 
{ 
   if (syn) syn->data = this; 
}

bool TLexemeSet::Add(const GSymbol& sym)
{
   GSymbol key(sym);
   key.value = 0; key.mode = 0;
   const_iterator ip = find(key); 
   if (ip != end()) {
      return false;
   }
   std::pair<const GSymbol, int> item(key,count());
   insert(item); 
   return true; 
}

int  TLexemeSet::GetAdded(const GSymbol& lex) const
{
   int ret = -1;
   GSymbol key(lex);
   key.value = 0; key.mode = 0;
   const_iterator ip = find(key); 
   if (ip != end()) {
      const std::pair<const GSymbol,int> old = (*ip);
      ret = old.second;
   }
   return ret;
}

T_SyntaxLexeme TLexemeSet::grammar_type() const
{
   int type = T_SyntaxLexeme::slNone | T_SyntaxLexeme::slNoDefType | T_SyntaxLexeme::slNoDefArrVar, type_oper = T_SyntaxLexeme::slNone;
   for (const std::pair<const GSymbol&, int> item : *this) {
      const GSymbol& sym = item.first;
      if (sym.group == T_Lexeme::grPriority) {
         type |= T_SyntaxLexeme::slPrior;
         if (sym.lexeme_type == T_Symbol::prAssign) type_oper |= T_SyntaxLexeme::slPriorAssign;
      } else if (sym.group == T_Lexeme::grSyntax) {
         if ((sym.lexeme_type == T_Lexeme::sxDefArr) || (sym.lexeme_type == T_Lexeme::sxDefVar)) {
            type &= ~T_SyntaxLexeme::slNoDefArrVar; type |= T_SyntaxLexeme::slSyntax;
         } else if (sym.lexeme_type == T_Lexeme::sxDefType) {
            type &= ~T_SyntaxLexeme::slNoDefType;
         } else {
            type |= T_SyntaxLexeme::slSyntax;
         }
      } else if (sym.group == T_Lexeme::grMeta) {
         type |= T_SyntaxLexeme::slMeta;
      }
   }
   if (type & T_SyntaxLexeme::slPrior) type |= type_oper;
   return (T_SyntaxLexeme)type;
}

void TLexemeSet::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   fprintf(file, "\n--- Lexemes --- <%d> ---\n", (int)size());
   if (print_mode == T_PrintMode::pmNone) return;
   int old_group = -1;
   for (const std::pair<const GSymbol&, int> item : *this) {
      if (print_mode & T_PrintMode::pmLexemePart) {
         if (old_group != item.first.group) {
            old_group = item.first.group;
            printer.eol();
         }
      }
      item.first.print(printer);
   }
   printer.eol();
}

const char* snode_title(int t);
#define SYNTREE_SHIFT 6 
int syn_tree(int s1) { return s1; }
int syn_tree(int s1, int s2) { return s1 | (s2 << SYNTREE_SHIFT); }
int syn_tree(int s1, int s2, int s3) { return s1 | (s2 << SYNTREE_SHIFT) | (s3 << 2 * SYNTREE_SHIFT); }
int syn_tree(int s1, int s2, int s3, int s4) { return s1 | (s2 << SYNTREE_SHIFT) | (s3 << 2 * SYNTREE_SHIFT) | (s4 << 3 * SYNTREE_SHIFT); }
int syn_tree(int s1, int s2, int s3, int s4, int s5) { return s1 | (s2 << SYNTREE_SHIFT) | (s3 << 2 * SYNTREE_SHIFT) | (s4 << 3 * SYNTREE_SHIFT) | (s5 << 4 * SYNTREE_SHIFT); }

/**/
const GSymbol& TGrammar::GetLLkA(const GSymbol& tab) const
{
   return GSymbol::none;
}
/**/

/*
http://rain.ifmo.ru/cat/view.php/vis/graph-general/topological-sort-2007/algorithm
Топологическая сортировка графа
Описание алгоритма

Топологическая сортировка(Topological sort) — один из основных алгоритмов на графах, применяется для решения множества более сложных задач.
Задача топологической сортировки графа состоит в следующем : указать такой линейный порядок на его вершинах, чтобы любое ребро вело от вершины с меньшим номером к вершине с большим номером.
Очевидно, что если в графе есть циклы, то такого порядка не существует.
Наиболее простая и быстрая реализация этого алгоритма — с помощью обхода в глубину(DFS).
Запускаем обход в глубину, и когда вершина обработана, заносим ее в стек.
По окончании обхода в глубину вершины достаются из стека.Новые номера присваиваются в порядке вытаскивания из стека.

Цвет.Во время обхода в глубину используется 3 цвета.Изначально все вершины белые.
Когда вершина обнаружена, красим ее в серый цвет.Когда просмотрен список всех смежных с ней вершин, красим ее в черный цвет.
Процедура топологической сортировки

Процедура возвращает true, если граф был топологически отсортирован, иначе возвращается false.

Color — массив, в котором хранятся цвета вершин(0 — белый, 1 — серый, 2 — черный).
N — количество вершин.
Edges — массив списков смежных вершин.
Numbers — массив, в котором сохраняются новые номера вершин.
Stack — стек, в котором складываются вершины после их обработки.
Cycle — принимает значение true, если в графе найден цикл.
*/

int TIndexes::Add(int i)
{
   iterator ip = find(i);
   if (ip != end()) return (*ip).second;
   std::pair<int, int> item(i,(int)index.size());
   insert(item);
   index.push_back(i);
   return (int)index.size() - 1;
}

int  TIndexes::Get(int i) const
{
   const_iterator ip = find(i);
   return (*ip).second;
}

int  TIndexes::Teg(int i) const
{
   return index[i];
}

bool TopologicalSort::dfs(int v)
{
   // Если вершина серая, то мы обнаружили цикл.Заканчиваем поиск в глубину.
   if (Color[v] == 1) return true;
   // Если вершина черная, то заканчиваем ее обработку.
   if (Color[v] == 2) return false;
   // Красим вершину в серый цвет.
   Color[v] = 1;
   // Обрабатываем список смежных с ней вершин.
   for (int i = 0; i < (int)Edges[v].size(); i++) {
      if (dfs(Edges[v][i])) return true;
   }
   // Кладем вершину в стек.
   Stack.push(v);
   // Красим вершину в черный цвет.
   Color[v] = 2;
   return false;
}

bool TopologicalSort::sort()
{
   bool Cycle;
   // Вызывается обход в глубину от всех вершин.Заканчиваем работу алгоритма, если обнаружен цикл.
   for (int i = 0; i < N; i++) {
      Cycle = dfs(i);
      if (Cycle) return false;
   }
   // Заносим в массив новые номера вершин.
   for (int i = 0; i < N; i++) {
      Numbers[Stack.top()] = i;
      Stack.pop();
   }
   Indexes.resize(N);
   for (int i = 0; i < N; i++) {
      Indexes[Numbers[i]] = i;
   }
   return true;
}
