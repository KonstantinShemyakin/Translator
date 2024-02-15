#include "stdafx.h"

#include "Tables.h"
#include "RSyntax.h"
#include "Grammar.h"

const TAction TAction::none, TAction::error(TAction::taError), TAction::fi(TAction::taFi);

int  TLXkReference::Get(int i) const
{
   if ((*this)[i] == i) {
      return i;
   } else if ((*this)[i] == -1) {
      return -1;
   } else {
      return Get((*this)[i]);
   }
}

void TLXkReference::Set(int i, int j)
{
   int ref_i = Ref(i), ref_j = Ref(j);
   (*this)[ref_i] = ref_j;
}

int  TLXkReference::Ref(int i)
{
   if ((*this)[i] == i) {
      return i;
   } else {
      int ref = Ref((*this)[i]);
      (*this)[i] = ref;
      return ref;
   }
}

int  TLXkReference::Ref(int i, int j)
{
   int ref_i = Ref(i), ref_j = Ref(j);
   if (ref_i < ref_j) {
      (*this)[ref_j] = ref_i;
      return 1;
   } else {
      (*this)[ref_i] = ref_j;
      return -1;
   }
}

void TLXkReference::Delete(int i)
{
   if ((*this)[i] == i) {
      (*this)[i] = -1;
   }
}

void TLXkReference::Rename(TLXkReference& target) const
{
   int used = 0;
   target.resize(count());
   std::vector<int> use(count());
   for (int i = 0; i < count(); i++) {
      if ((*this)[i] == i) {
         use[i] = used++;
      }
   }
   for (int i = 0; i < count(); i++) {
      if ((*this)[i] == i) {
         target[i] = use[i];
      } else {
         int get = Get(i);
         target[i] = (get == -1) ? -1 : use[get];
      }
   }
}

int TTableKey::cast(const TTableKey& key)
{
   if (key.sym.IsTerminal()) {
      if (key.sym.group == T_Lexeme::grOper) {
         const T_Symbol& symbol = symbol_table().Symbol(key.sym.value);
         if (symbol.priority) {
            sym.group = T_Lexeme::grPriority; sym.lexeme_type = symbol.priority;
            return 1;
         }
      } else if (key.sym.group == T_Lexeme::grPriority) {
         const T_Symbol& symbol = symbol_table().Symbol(key.sym.value);
         sym.group = T_Lexeme::grOper; sym.lexeme_type = symbol.type;
         return 1;
      } else if (key.sym.group == T_Lexeme::grSyntax) {
         if ((key.sym.lexeme_type == T_Lexeme::sxDefVar) || (key.sym.lexeme_type == T_Lexeme::sxDefArr)) {
            sym.lexeme_type = T_Lexeme::sxDefType;
            return 1;
         }
      }
   } 
   return 0;
}

void TTableKey::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   if (print_mode == T_PrintMode::pmWriteSymbol) fprintf(file, "TTableKey(");
   key.write(printer);
   if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) fprintf(file, ","); else fprintf(file, " ");
   sym.write(printer);
   if (print_mode == T_PrintMode::pmWriteSymbol) fprintf(file, ")");
}

bool TTableKey::read (FILE *file, const TGrammar* grammar, int print_mode)
{
   key.read(file, grammar,print_mode);
   sym.read(file, grammar,print_mode);
   return true;
}

void TTableKey::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   fprintf(file, "{"); 
   if (!key.IsNone() || !(print_mode & T_PrintMode::pmNoPrintNone)) {
      key.print(printer); 
   } else {
      int len = SYMBOL_PRINT_TITLE_LEN;
      printer.offset(len, false); 
   }
   fprintf(file, ","); sym.print(printer); fprintf(file, "}");
}

bool TTableMap::Add(const TTableKey& key, const GSymbol& produce)
{
   std::pair<const TTableKey&,const GSymbol&> item(key,produce); 
   const_iterator ip = find(key); 
   if (ip != end()) {
      const std::pair<const TTableKey&, const GSymbol&> old = (*ip);
      if (item.second == old.second) {
         return false;
      }
      const GProduce& produce_body = grammar->Produce(produce);
      if (produce_body.head.mode & GSymbol::Warning) { warning++; return false; }
      const GProduce& old_body = grammar->Produce(old.second);
      if (old_body.head.mode & GSymbol::Warning) { warning++; return false; }
      if (duplicate++ < 100) {
         printf("\nDuplicate:\n");
         int print_mode = 0x00;
         TPrinter printer(grammar);
         old.first.print(printer); printf(" -> "); old.second.print(printer); printf("\n");
         item.first.print(printer); printf(" -> "); item.second.print(printer); printf("\n");
      }
      return false;
   }
   insert(item); 
   return true; 
}

const GSymbol& TTableMap::Find(const TTableKey& key) const
{
   const_iterator ip = find(key); 
   if (ip !=end()) {
      return (*ip).second;
   } else {
      return GSymbol::none;
   }
}

const GSymbol& TTableMap::Cell(const TTableKey& key) const
{
   TTableKey my_key(key); my_key.sym.value = 0; my_key.sym.mode = 0;
   const_iterator ip = find(my_key); 
   if (ip != end()) {
      return (*ip).second;
   } else {
      if (key.sym.IsVector()) {
         const GSymbolVector& vec = grammar->Vector(key.sym);
         my_key.sym = vec.front();
      }
      my_key.sym.value = key.sym.value;
      if (my_key.sym.Cast()) {
         my_key.sym.value = 0;
         if (key.sym.IsVector()) {
            GSymbolVector vec = grammar->Vector(key.sym);
            vec.front() = my_key.sym;
            my_key.sym = grammar->Vectors().Find(vec);
         }
         ip = find(my_key);
         if (ip != end()) {
            return (*ip).second;
         }
      }
   }
   return GSymbol::none;
}

int  TTableMap::change(int mode)
{
   int count = 0;
   bool verify = (mode & TChangeSymbolMode::chVerify) != 0;
   iterator ip_change = begin();
   while (ip_change != end()) {
      std::pair<const TTableKey&, const GSymbol&> item = *(ip_change);
      TTableKey key = item.first;
      const GSymbol& sym = item.second;
      int yes_change = key.sym.Change(mode);
      if (yes_change) {
         if (!verify) {
            std::pair<const TTableKey&, const GSymbol&> change_item(key, sym);
            insert(change_item);
            ip_change = erase(ip_change);
         }
         count++;
      } else {
         ip_change++;
      }
   }
   return count;
}

bool TGrammar::read(const char* title, int &table_type, int print_mode)
{
   FILE *file = NULL;
   if (!title) title = "def_rule.tab";
	FOPEN(file, title, "r");
   if (!file) {
      printf("\nfile error : %s", title);
      return false;
   }
   FSCANF(file,"%d",&table_type);
   if (table_type & T_Grammar::gtLL) {
      Mtable.read(file, 0x00);
   }
   if (table_type & T_Grammar::gtLR) {
      LRtable.read(file, 0x00);
   }
   read(file, 0x01);
   make_produces();
   if (count()) root = formulas.front();
   if ((table_type & (T_Grammar::gtLL | T_Grammar::gtLR)) && (look_ahead > 0)) {
      int ref_count;
      FSCANF(file, "%d", &ref_count);
      references.resize(ref_count);
      for (int i = 0; i < ref_count; i++) {
         FSCANF(file, "%d", &references[i]);
      }
   }
   fclose(file);
   return true;
}

bool TGrammar::read(const char* title, int print_mode)
{
   FILE *file = NULL;
   if (!title) title = "def_rule.tab";
	FOPEN(file, title, "r");
   if (!file) {
      printf("\nfile error : %s", title);
      return false;
   }
   read(file, T_PrintMode::pmWriteSimple);
   fclose(file);
   return true;
}

void TGrammar::AddAction(const TTableKey& key, const TAction& action)
{
   LRtable.Add(key,action);
}

void TGrammar::AddActions(int count, const int A[][16])
{
   for (int i = 0; i < count; i++) {
      TTableKey key(GSymbol((GSymbol::T_Type)A[i][0],A[i][1],A[i][2],A[i][3],A[i][4]), GSymbol((GSymbol::T_Type)A[i][5],A[i][6],A[i][7],A[i][8],A[i][9])); 
      TAction action((TAction::T_Type)A[i][10],GSymbol((GSymbol::T_Type)A[i][11],A[i][12],A[i][13],A[i][14],A[i][15]));
      AddAction(key,action);
   }
}

void TGrammar::AddCell(const TTableKey& key, const GSymbol& cell)
{
   Mtable.Add(key,cell);
}

void TGrammar::AddCells(int count, const int A[][15])
{
   for (int i = 0; i < count; i++) {
      TTableKey key(GSymbol((GSymbol::T_Type)A[i][0],A[i][1],A[i][2],A[i][3],A[i][4]), GSymbol((GSymbol::T_Type)A[i][5],A[i][6],A[i][7],A[i][8],A[i][9])); 
      GSymbol cell((GSymbol::T_Type)A[i][10],A[i][11],A[i][12],A[i][13],A[i][14]);
      AddCell(key,cell);
   }
}

class TKeyVector : public std::map<const GSymbol, GSymbolVector> {
public:
   bool Add(const GSymbol& key, const GSymbol& sym);
};

bool TKeyVector::Add(const GSymbol& key, const GSymbol& sym)
{
   iterator ip = find(key);
   if (ip != end()) {
      (*ip).second.push_back(sym);
      return false;
   } else {
      value_type item(key, GSymbolVector());
      item.second.push_back(sym);
      insert(item);
      return true;
   }
}

bool TTableMap::read(const char* title, int print_mode)
{
   FILE *file = NULL;
	FOPEN(file, title, "r");
   if (!file) return false;
   read(file, print_mode);
   fclose(file);
   return true;
}

bool TTableMap::read (FILE* file, int print_mode)
{
   clear();
   int my_count;
   FSCANF(file,"%d",&my_count);
   for (int i = 0; i < my_count; i++) {
      TTableKey key;
      GSymbol action;
      key.read(file,grammar,print_mode);
      action.read(file,grammar,print_mode);
      Add(key,action);
   }
   return true;
}

void TTableMap::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) {
      fprintf(file, "\nvoid make_cells(TGrammar& grammar)\n{\n");
   } else if (print_mode == T_PrintMode::pmWriteZero) {
      fprintf(file, "%05d\n",count());
   } else {
      fprintf(file, "%d\n",count());
   }
   if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, "static const int A[][15] = {\n");
   int row = 0;
   for (const std::pair<const TTableKey&,const GSymbol&> item : *this) {
      const TTableKey &key = item.first;
      if (print_mode == T_PrintMode::pmWriteSymbol) fprintf(file, "grammar.AddCell(");
      if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, "{");
      key.write(printer); 
      if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) fprintf(file, ","); else fprintf(file, " ");
      const GSymbol& action = item.second;
      action.write(printer);
      if (print_mode == T_PrintMode::pmWriteSymbol) fprintf(file, ");");
      if (print_mode == T_PrintMode::pmWriteProg) { fprintf(file, "}"); if (++row != count()) fprintf(file, ","); else fprintf(file, "};"); }
      printer.eol();
   }
   if (print_mode == T_PrintMode::pmWriteSymbol) fprintf(file, "}\n");
   if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, "grammar.AddCells(%d,A);}\n",count());
}

void TTableMap::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   if (!printer.file_name) {
      fprintf(file, "\n--- M table --- <%d> ---\n", (int)size());
   }
   if (printer.print_mode == 0x00) return;
   int situation_old = -1;
   for (const std::pair<const TTableKey&,const GSymbol&> item : *this) {
      TTableKey key(item.first);
      if (key.key.situation != situation_old) {
         situation_old = key.key.situation;
      } else {
         key.key.type = GSymbol::gsNone;
      }
      key.print(printer);
      const GSymbol& p = item.second;
      if (p.IsProduce()) {
         const GProduce& pr = grammar->Produce(p);
         //pr.head.print(grammar, print_mode,file); 
         pr.print(printer);
      } else {
         fprintf(file, " -> ");
         p.print(printer);
      }
      printer.eol();
   }
}

bool LRTableMap::read(const char* title, int print_mode)
{
   FILE *file = NULL;
	FOPEN(file, title, "r");
   if (!file) return false;
   read (file, print_mode);
   fclose(file);
   return true;
}

bool LRTableMap::read (FILE* file, int print_mode)
{
   clear();
   int my_count;
   FSCANF(file,"%d",&my_count);
   for (int i = 0; i < my_count; i++) {
      TTableKey key;
      TAction action;
      key.read(file,grammar,print_mode);
      action.read(file,grammar,print_mode);
      Add(key,action);
   }
   return true;
}

void LRTableMap::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) {
      fprintf(file, "\nvoid make_actions(TGrammar& grammar)\n{\n");
   } else if (print_mode == T_PrintMode::pmWriteZero) {
      fprintf(file, "%05d\n",count());
   } else {
      fprintf(file, "%d\n",count());
   }
   if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, "static const int A[][16] = {\n");
   int row = 0;
   for (const std::pair<const TTableKey&,const TAction&> item : *this) {
      const TTableKey &key = item.first;
      const TAction& action = item.second;
      if (print_mode == T_PrintMode::pmWriteSymbol) fprintf(file, "grammar.AddAction(");
      if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, "{");
      key.write(printer);
      if ((print_mode == T_PrintMode::pmWriteSymbol) || (print_mode == T_PrintMode::pmWriteProg)) fprintf(file, ","); else fprintf(file, " ");
      action.write(printer);
      if (print_mode == T_PrintMode::pmWriteSymbol) fprintf(file, ");");
      if (print_mode == T_PrintMode::pmWriteProg) { fprintf(file, "}"); if (++row != count()) fprintf(file, ","); else fprintf(file, "\n};"); }
      printer.eol();
   }
   if (print_mode == T_PrintMode::pmWriteSymbol) fprintf(file, "\n}\n");
   if (print_mode == T_PrintMode::pmWriteProg) fprintf(file, "grammar.AddActions(%d,A);\n}\n",count());
}

void LRTableMap::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   if (!printer.file_name) {
      int sitsituation = 0;
      const_reverse_iterator  ip = this->crbegin();
      if (ip != crend()) sitsituation = (*ip).first.key.situation + 1;
      fprintf(file, "\n--- LR table --- <%d,%d> ---\n", sitsituation, (int)size());
   }
   if (print_mode == 0x00) return;
   /*
   int old_situation = -1, max_situation = -1;
   for (const std::pair<const TTableKey&,const TAction&> item : *this) {
      int new_situation = item.first.produce.situation;
      if (new_situation > old_situation + 1) {
//         GSymbol skip_situation(GSymbol::gsSituation,old_situation + 1);
//         for (;skip_situation.situation < new_situation; skip_situation.situation++) {
//            printf("!"); skip_situation.print(grammar, print_mode); printf("\n");
//         }
      }
      old_situation = new_situation;
      const TAction& action = item.second;
      if ((action.IsShift() || action.IsGoto()) && (action.sym.situation > max_situation)) max_situation = action.sym.situation; 
   }
   if (max_situation > old_situation) {
      GSymbol skip_situation(GSymbol::gsSituation,old_situation + 1);
//      for (;skip_situation.situation <= max_situation; skip_situation.situation++) {
//         printf("!"); skip_situation.print(grammar, print_mode); printf("\n");
//      }
   }
   */
   GSymbol key_old; key_old.formula = -1;
   for (const std::pair<const TTableKey&,const TAction&> item : *this) {
      const TAction& action = item.second;
      TTableKey key(item.first);
      if (!(key.key == key_old)) {
         key_old = key.key;
      } else {
         key.key.type = GSymbol::gsNone;
      }
      key.print(printer); fprintf(file, " -> "); action.print(printer); printer.eol();
   }
}

bool LRTableMap::AssociationPriority(const TTableKey& key, const TAction& item, const TAction& old)
{
   GSymbol key_sym = key.sym;
   int look_ahead = grammar->look_ahead;
   if ((look_ahead > 0) && key_sym.IsVector()) {
      const GSymbolVector& vector = grammar->Vector(key_sym);
      key_sym = vector.front();
   }
   if (!key_sym.IsTerminal() || (key_sym.group != T_Lexeme::grPriority)) return false;
   if ((key_sym.lexeme_type != T_Symbol::prAssign) && ((key_sym.lexeme_type < T_Symbol::prOrOr) || (key_sym.lexeme_type > T_Symbol::prFactor))) return false;
   const TAction *shift = NULL, *reduce = NULL;
   if (item.IsShift())   shift = &item; if (old.IsShift())   shift = &old;
   if (item.IsReduce()) reduce = &item; if (old.IsReduce()) reduce = &old;
   if (!shift || !reduce) return false;
   const GProduce& produce = Produce(reduce->sym);
   if (produce.count() < 3) return false;
   const GSymbol& produce_sym = produce[1];
   if (!produce_sym.IsTerminal() || (produce_sym.group != T_Lexeme::grPriority)) return false;
   if ((produce_sym.lexeme_type != T_Symbol::prAssign) && ((produce_sym.lexeme_type < T_Symbol::prOrOr) || (produce_sym.lexeme_type > T_Symbol::prFactor))) return false;
   if (!(produce[0] == produce[2]) || !produce[0].IsFormula() || (produce.head.formula != produce[0].formula)) return false;
/*
   int print_mode = 0x00;
   printf("\n");
   const TAction&  old_action = old;
   key.print(grammar, print_mode); printf(" -> ");  old_action.print(grammar, print_mode); 
   if ( old_action.type == TAction::taReduce) {
      const GProduce& produce = Produce(old_action.sym);
      produce.print(grammar, T_PrintMode::pmCompactGroup | T_PrintMode::pmCompact);
   }
   printf("\n");
   const TAction& item_action = item;
   key.print(grammar, print_mode); printf(" -> "); item_action.print(grammar, print_mode); 
   if (item_action.type == TAction::taReduce) {
      const GProduce& produce = Produce(item_action.sym);
      produce.print(grammar, T_PrintMode::pmCompactGroup | T_PrintMode::pmCompact);
   }
   printf("\n");
*/
   bool change = false;
   if (key_sym.lexeme_type == produce_sym.lexeme_type) {
      if ((key_sym.lexeme_type == T_Symbol::prAssign)) {
         if (!old.IsShift()) change = true;
      } else {
         if (!old.IsReduce()) change = true;
      }
   } else if ((key_sym.lexeme_type > produce_sym.lexeme_type) && (produce_sym.lexeme_type != T_Symbol::prAssign)) {
      change = true;
   }
   if (change) {
      TAction& new_action = at(key);
      new_action = item;
   }

   return true;
}

bool LRTableMap::Add(const TTableKey& key, const TAction& action)
{
   std::pair<const TTableKey&,const TAction&> item(key,action); 
   const_iterator ip = find(key); 
   if (ip != end()) {
      const std::pair<const TTableKey&,const TAction&> old = (*ip);
      if (item.second == old.second) return true;
      if (AssociationPriority(key, item.second, old.second)) return true;
      const TAction& item_action = item.second;
      const TAction&  old_action = old.second;
      if (item_action.type == TAction::taReduce) {
         const GProduce& produce = Produce(item_action.sym);
         if (produce.head.mode & GSymbol::Warning) { warning++; return false; }
      }

      TPrinter printer(grammar);
      if (duplicate < 100) {
         printf("\nDuplicate:\n");
         int print_mode = 0x00;
         old.first.print(printer); printf(" -> ");  old_action.print(printer);
         if (old_action.type == TAction::taReduce) {
            const GProduce& produce = Produce(old_action.sym);
            TPrinter printer_reduce(printer, T_PrintMode::pmCompactGroup | T_PrintMode::pmCompact);
            produce.print(printer_reduce);
         }
         printf("\n");
         item.first.print(printer); printf(" -> "); item_action.print(printer);
         if (item_action.type == TAction::taReduce) {
            const GProduce& produce = Produce(item_action.sym);
            TPrinter printer_reduce(printer, T_PrintMode::pmCompactGroup | T_PrintMode::pmCompact);
            produce.print(printer_reduce);
         }
         printf("\n");
      }

      if (old.second.IsReduce() && item.second.IsShift()) {
         TAction& new_action = at(key);
         new_action = action;
         if (duplicate < 100) {
            printf(":="); item.second.print(printer); printf("\n");
         }
      }
      duplicate++;
      return false;
   }
   insert(item); 
   return true; 
}

const TAction& LRTableMap::Action(const TTableKey& key) const
{
   TTableKey my_key(key); my_key.sym.point = 0; my_key.sym.mode = 0;
   const_iterator ip = find(my_key); 
   if (ip != end()) {
      return (*ip).second;
   } else {
      if (!key.sym.IsVector() || (grammar->look_ahead < 2)) {
         if (key.sym.IsVector()) {
            const GSymbolVector& vec = grammar->Vector(key.sym);
            my_key.sym = vec.front();
         }
         my_key.sym.value = key.sym.value;
         if (my_key.sym.Cast()) {
            my_key.sym.value = 0;
            if (key.sym.IsVector()) {
               GSymbolVector vec = grammar->Vector(key.sym);
               vec.front() = my_key.sym;
               my_key.sym = grammar->Vectors().Find(vec);
            }
            ip = find(my_key);
            if (ip != end()) {
               return (*ip).second;
            }
         }
      }
      my_key.sym = GSymbol::none; // Compression
      ip = find(my_key);
      if (ip != end()) {
         return (*ip).second;
      }
   }
   return TAction::none;
}

int  LRTableMap::GOTO(const TTableMap& join)
{
   int ret = 0;
   for (const std::pair<const TTableKey&,const GSymbol&> item : join) {
      const TTableKey &key = item.first;
      if (!key.sym.IsFormula()) continue;
      TAction action(TAction::taGoto,item.second);
      Add(key,action);
      ret++;
      }
   return ret;
}

int  LRTableMap::Compression()
{
   int old_count = count(), del_count = 0, none_count = 0;
   const_iterator ip_situation = begin();
   while (ip_situation != end()) {
      const GSymbol situation = (*ip_situation).first.key;
      TKeyVector reduces;
      while (ip_situation != end() && (situation == (*ip_situation).first.key)) {
         const TAction& action = (*ip_situation).second;
         if (action.IsReduce()) {
            reduces.Add(action.sym, (*ip_situation).first.sym);
         }
         ip_situation++;
      }
      GSymbol key_max; int max = 1;
      for (const std::pair<const GSymbol&, GSymbolVector> item : reduces) {
         int vector_size = (int)item.second.size();
         if (vector_size > max) {
            key_max = item.first; max = vector_size;
         }
      }
      if (max >= 2) {
         TTableKey key_del(situation,GSymbol::none);
         std::pair<const TTableKey, TAction> compres(key_del,TAction(TAction::taReduce,key_max));
         insert(compres); none_count++;
         const GSymbolVector& symbols = reduces.at(key_max);
         for (const GSymbol& sym : symbols) {
            key_del.sym = sym;
            iterator ip_del = find(key_del);
            erase(ip_del); del_count--;
         }
      }
   }
   if (old_count) {
      printf("\nCompression: %d%%, %d -> %d, %d, +%d\n", ((old_count - count()) * 100)/ old_count, old_count, count(), del_count, none_count);
   }
   return true;
}

int LRTableMap::change(int mode)
{
   int count = 0;
   iterator ip_change = begin();
   while (ip_change != end()) {
      std::pair<const TTableKey&, const TAction&> item = *(ip_change);
      TTableKey key = item.first; 
      const TAction& action = item.second;
      int yes_change = key.sym.Change(mode);
      if (yes_change) {
         std::pair<const TTableKey&, const TAction&> change_item(key, action);
         insert(change_item);
         ip_change = erase(ip_change);
         count++;
      } else {
         ip_change++;
      }
   }
   return count;
}

// LRTable != GOTO  <- ((option & TGrammar::POption::opAssociation) != 0);
bool LRTableMap::verify(const TTableMap& go_to) const
{
   TPrinter printer(T_OptionMode::omPrintOther); 
   PRINTER_FILE_MODE_GRAMMAR_IF
   if (grammar->look_ahead > 1) return true;
   if ((grammar->option & TGrammar::POption::opAssociation) != 0) return true;
   bool ret = true;
   int different = 0;
              const_iterator ip_table = begin();
   TTableMap::const_iterator  ip_goto = go_to.begin();
   while ((ip_table != end()) && (ip_goto != go_to.end())) {
            TTableKey  key_table = (*ip_table).first;
      const TTableKey& key_goto  = (*ip_goto ).first;
      const TAction& action = (*ip_table).second;
      const GSymbol& sym_goto = (*ip_goto).second;
      if (action.IsAccept() || action.IsReduce()) { ip_table++; continue; }
      if (grammar->look_ahead > 0) {
         if (key_table.sym.IsVector()) {
            const GSymbolVector& vector = grammar->Vector(key_table.sym);
            key_table.sym = vector.front();
         }
      }
      if ((key_table == key_goto) && (action.sym == sym_goto)) { ip_table++; ip_goto++; continue; }
      if (ret) {
         fprintf(file, "\nLRTable != GOTO\n");
         key_table.print(printer); fprintf(file, " -> "); action.print(printer); printer.eol();
         key_goto.print(printer); fprintf(file, " -> "); sym_goto.print(printer); printer.eol();
      }
      ret = false; different++;
      if (key_table.key == key_goto.key) { ip_table++; ip_goto++; continue; }
      while ((ip_table != end()) && ((*ip_table).first.key < (*ip_goto).first.key)) { ip_table++; different++; }
      if (ip_table == end()) break;
      while ((ip_goto != go_to.end()) && ((*ip_goto).first.key < (*ip_table).first.key)) { ip_goto++;  different++; }
      if (ip_goto == go_to.end()) break;
   }
   while (ip_table != end()) {
      const TTableKey& key_table = (*ip_table).first;
      const TAction&   action = (*ip_table).second;
      if (action.IsAccept() || action.IsReduce()) { ip_table++; continue; }
      ret = false; different++;
      ip_table++;

   }
   while (ip_goto != go_to.end()) {
      const TTableKey& key_goto = (*ip_goto).first;
      const GSymbol&   sym_goto = (*ip_goto).second;
      ret = false; different++;
      ip_goto++;
   }
   if (different) {
      fprintf(file, "\nDifferent : %d\n", different);
   }

   return ret;
}

const char* action_title(TAction::T_Type type)
{
   static const char* title[] = {
      "None", "Shift", "Reduce", "Accept", "Goto", "Error", "Fi", "Produce", "Pop"
   };
   return title[type];
}

int  TAction::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   int len = 0;
   const char* title = action_title(type);
	fprintf(file, "%-7s ", title); len += 1 + (int)strlen(title);
   if (type != taAccept) {
      len += sym.print(printer);
   }
   return len;
}

void TAction::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   const char* title[] = { "None", "Shift", "Reduce", "Accept", "Goto" };
   if (print_mode == T_PrintMode::pmWriteSymbol) {
      fprintf(file, "TAction(TAction::ta%s,",title[type]);
   } else if (print_mode == T_PrintMode::pmWriteZero) {
      fprintf(file,"%02d ",type);
   } else if (print_mode == T_PrintMode::pmWriteProg) {
      fprintf(file,"%d,",type);
   } else {
      fprintf(file,"%d ",type);
   }
   sym.write(printer);
   if (print_mode == T_PrintMode::pmWriteSymbol) {
      fprintf(file, ")");
   }
}

bool TAction::read (FILE *file, const TGrammar* grammar, int print_mode)
{
   FSCANF(file,"%d",&type);
   sym.read(file, grammar,print_mode);
   return true;
}

const GFormula& TData::Formula(const GSymbol &sym) const
{
   const GFormula& formula = *(*formulas)[sym.formula];
   return formula;
}
const GProduce& TData::Produce(const GSymbol &sym) const
{
   return grammar->Produce(sym);
}
const GSymbol&  TData::Cell(const TTableKey& key) const
{
   return LLTable->Cell(key);
}
const TAction&  TData::Action(const TTableKey& key) const
{
   return LRTable->Action(key);
}

const GFormula* TData::Root() const
{
   if (root) return root;
   if (formulas) {
      if (formulas->root) return formulas->root;
      return formulas->front();
   }
   if (grammar) {
   }
   return NULL;
}

const GProduce& LRTableMap::Produce(const GSymbol &sym) const
{
   return grammar->Produce(sym);
}

const TAction& LRFiTable::Action(const GSymbol& key) const
{
   const_iterator ip = find(key);
   if (ip != end()) {
      return (*ip).second;
   } else {
      return TAction::none;
   }
}

const TAction& LRFiTable::FiAction(const GSymbol& key) const
{
   const_iterator ip = find(key);
   if (ip != end()) {
      return (*ip).second;
   } else {
      if (errors.Have(key)) {
         return TAction::error;
      }
      return TAction::fi;
   }
}

// ------------------------------------- FiUnattainable --------------------------------------
// Green(v=2,(7.3.3,7.3.4))
int  LRFiTable::FiCompare(const LRFiTable& join, TLXkReference& references) const
{
   int ret = 0;
   for (const std::pair<const GSymbol&, const TAction&> item : *this) {
      const TAction& action = item.second; // !error && !fi
      const GSymbol& key = item.first;
      const TAction& join_action = join.FiAction(key);
      if (join_action.IsError()) { // action error
         ret = -1; break;
      } else if (join_action.IsFi()) { // action fi
      } else if (join_action.type == action.type) {
         if (join_action.sym == action.sym) { // action == action
         } else if (action.IsGoto() || action.IsShift()) {
            if (references.Ref(action.sym.situation) == references.Ref(join_action.sym.situation)) {
            } else { // goto != goto
               ret++;
            }
         } else { // action != action
            ret = -1; break;
         }
      } else { // action.type != join.type
         ret = -1; break;
      }
   }
   if (ret < 0) return ret;
   for (const GSymbol& err : errors) {
      const TAction& join_action = join.FiAction(err);
      if (join_action.IsError()) { // error == error
      } else if (join_action.IsFi()) { // error == fi
      } else {
         ret = -1; break;
      }
   }
   return ret;
}

void LRFiTable::FiMerge(const LRFiTable& join)
{
   for (const std::pair<const GSymbol&, const TAction&> item : join) {
      const TAction& join_action = item.second; // !error && !fi
      const GSymbol& key = item.first;
      const TAction& action = FiAction(key);
      if (action.IsFi()) { // fi <- action
         std::pair<const GSymbol, TAction> item_table(key, join_action);
         insert(item_table);
      }
   }
   errors << join.errors;
}

// Green(v=2,7.3.6)
bool LRFiTable::ChainCompare(const LRFiTable& T1, const GSymbol& p, TLXkReference& references) const
{
   for (const std::pair<const GSymbol&, const TAction&> item : *this) {
      const TAction& action = item.second;
      const GSymbol& key = item.first;
      const TAction& T1_action = T1.FiAction(key);
      if (action == T1_action) continue;
      if (T1_action.IsFi()) continue;
      if (T1_action.IsReduce() && (T1_action.sym == p)) continue;
      return false;
   }
   for (const GSymbol& err : errors) {
      const TAction& T1_action = T1.FiAction(err);
      if (T1_action.IsError()) continue; // error == error
      if (T1_action.IsFi()) continue; // error == fi
      return false;
   }
   return true;
}

void LRFiTable::ChainMerge(const LRFiTable& T1, const GSymbol& p)
{
   for (const std::pair<const GSymbol&, const TAction&> item : T1) {
      const TAction& T1_action = item.second; // !error && !fi
      if (T1_action.IsReduce() && (T1_action.sym == p)) continue;
      const GSymbol& key = item.first;
      const TAction& action = FiAction(key);
      if (action.IsFi()) { // fi <- action
         std::pair<const GSymbol, TAction> item_table(key, T1_action);
         insert(item_table);
      }
   }
   errors << T1.errors;
}

bool LRFiTable::Delete(const GSymbol& U)
{
   iterator ip = find(U);
   if (ip != end()) {
      erase(ip);
      return true;
   }
   if (errors.Have(U)) {
      errors.Del(U);
      return true;
   }
   return false;
}

int  LRFiTable::DelAction(const GSymbol& key, const TAction& action)
{
   int ret = 0;
   iterator ip = find(key);
   if (ip != end()) {
      const TAction& my_action = (*ip).second;
      if (my_action == action) {
         ip = erase(ip);
      }
   }
   return ret;
}

void LRFiTable::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   for (const std::pair<const GSymbol&, const TAction&> item : *this) {
      const TAction& action = item.second;
      const GSymbol& key = item.first;
      key.print(printer); fprintf(file, " -> "); action.print(printer); printer.eol();
   }
   fprintf(file, ">> "); errors.print(printer);
   printer.eol();
}

bool LRFiColumn::Compare() const
{
   for (const LRFiTable* table : (*this)) {
      const TAction& action = table->FiAction(A);
      const TAction& join_action = table->FiAction(B);
      if (action == join_action) continue;
      if (action.IsFi() || join_action.IsFi()) continue;
      return false;
   }
   return true;
}

void LRFiColumn::Merge()
{
   for (LRFiTable* table : (*this)) {
      const TAction& action = table->FiAction(A);
      const TAction& join_action = table->FiAction(B);
      if (action.IsFi()) {
         std::pair<const GSymbol, TAction> item_table(A, join_action);
         table->insert(item_table);
      }
   }
}

bool LRFiTableMap::Make(const LRTableMap& general)
{
   GSymbol key_old; key_old.formula = -1;
   LRFiTable* table;
   for (const std::pair<const TTableKey&, const TAction&> general_item : general) {
      const TTableKey& key = general_item.first;
      if (!(key.key == key_old)) {
         key_old = key.key;
         std::pair<const GSymbol, LRFiTable> new_table(key.key, LRFiTable(grammar));
         insert(new_table);
         iterator ip = find(key.key);
         table = &(*ip).second;
      }
      std::pair<const GSymbol, TAction> item_table(key.sym, general_item.second);
      table->insert(item_table);
   }
   return true;
}

void LRFiTableMap::Copy(LRFiTableMap& target) const
{
   TLXkReference refer;
   references.Rename(refer);
   target.clear();
   for (const std::pair<const GSymbol&, const LRFiTable&> item_table : *this) {
      const LRFiTable& table = item_table.second;
      if (table.deleted) continue;
      GSymbol key_table = item_table.first;
      key_table.situation = refer.Item(key_table.situation);
      std::pair<const GSymbol, LRFiTable> new_table(key_table, LRFiTable(grammar));
      target.insert(new_table);
      LRFiTable& target_table = (*target.find(key_table)).second;
      for (const std::pair<const GSymbol&, const TAction&> item_action : table) {
         std::pair<GSymbol, TAction> new_action(item_action.first, item_action.second);
         TAction& action = new_action.second;
         if (action.IsGoto() || action.IsShift()) {
            action.sym.situation = refer.Item(action.sym.situation);
         }
         target_table.insert(new_action);
      }
      target_table.errors = table.errors;
   }
   target.references.Init(target.count());
}

int LRFiTableMap::Copy(LRTableMap& general, TTableMap& go_to) const
{
   TLXkReference refer;
   references.Rename(refer);

   general.clear(); go_to.clear();
   int table_count = 0;
   for (const std::pair<const GSymbol&, const LRFiTable&> item_table : *this) {
      const LRFiTable& table = item_table.second;
      if (table.deleted) continue;
      TTableKey key; key.key = item_table.first;
      key.key.situation = refer.Item(key.key.situation);
      for (const std::pair<const GSymbol&, const TAction&> item_action : table) {
         TAction action = item_action.second;
         key.sym = item_action.first;
         if (action.IsGoto() || action.IsShift()) {
            action.sym.situation = refer.Item(action.sym.situation);
            go_to.Add(key, action.sym);
         }
         general.Add(key, action);
      }
      table_count++;
   }
   return table_count;
}

void LRFiTableMap::GoToRef()
{
   for (iterator ip_table = begin(); ip_table != end(); ip_table++) {
      LRFiTable& table = (*ip_table).second;
      if (table.deleted) continue;
      for (LRFiTable::iterator ip_action = table.begin(); ip_action != table.end(); ip_action++) {
         TAction& action = (*ip_action).second;
         if (action.IsGoto() || action.IsShift()) {
            action.sym.situation = references.Ref(action.sym.situation);
         }
      }
   }
}

void LRFiTableMap::Statistic(int& table_count, int& item_count) const
{
   table_count = 0; item_count = 0;
   for (const std::pair<const GSymbol&, const LRFiTable&> tab : *this) {
      const LRFiTable& table = tab.second;
      if (table.deleted) continue;
      table_count++; item_count += table.count();
   }
}

// Green(v=2,p=56,a=7.6)
bool LRFiTableMap::FiUnattainable(int k)
{
   for (iterator ip_table = begin(); ip_table != end(); ip_table++) {
      LRFiTable& table_shift = (*ip_table).second;
      if (table_shift.deleted) continue;
      for (LRFiTable::const_iterator ip_action = table_shift.begin(); ip_action != table_shift.end(); ip_action++) {
         const TAction& action = (*ip_action).second;
         if (!action.IsShift()) continue;
         iterator ip = find(action.sym);
         if (ip == end()) return false;
         LRFiTable& table = (*ip).second;
         const GSymbol& key = (*ip_action).first;
         GSymbolVector av = grammar->Vectors().Vector(key);
         av.erase(av.begin()); const GSymbolVector& v = av;
         if (!v.empty()) {
            GSymbol u = grammar->Vectors().Add(v);
            if (table.Action(u).IsNone()) {
               table.AddError(u);
            }
         } else {
            if (table.Action(GSymbol::empty).IsNone()) {
               table.AddError(GSymbol::empty);
            }
         }
         if (v.count() == (k - 1)) {
            GSymbolVector vbs;
            grammar->Vectors().Tails(av, vbs, grammar->lexemes);
            for (const GSymbol& vb : vbs) {
               if (table.Action(vb).IsNone()) {
                  table.AddError(vb);
               }
            }
         }
      }
   }
   return true;
}

// Green(v=2,p=60,a=7.7)
bool LRFiTableMap::JointSplitting()
{
   printf("\n--- FiUnattainable ---\n");

   if (references.count() != count()) references.Init(count());
   int step = 0;
   int cycle = 0, change = 0;
   do {
      cycle = 0; change = 0;  step++;
      for (GSymbol situation(GSymbol::gsSituation, 1); situation.situation < count() - 1; situation.situation++) {
         if (references.Deleted(situation.situation)) continue;
         iterator ip = find(situation);
         LRFiTable& table = (*ip).second;
         if ((step > 1) && (table.step < step - 1)) continue;
         for (GSymbol join(GSymbol::gsSituation, situation.situation + 1); join.situation < count(); join.situation++) {
            if (references.Deleted(join.situation)) continue;
            iterator ip_join = find(join);
            LRFiTable& table_join = (*ip_join).second;
            if ((step > 1) && (table_join.step < step - 1)) continue;
            int compare = table.FiCompare(table_join, references);
            if (compare < 0) continue;
            if (compare > 0) { // goto != goto
               table.step = step; table_join.step = step;
               cycle++;
               continue;
            }
            table.FiMerge(table_join);
            references.Set(join.situation, references.Ref(situation.situation));
            table_join.deleted = true;
            change++;
         }
      }
      printf("cycle=%d, change=%d\n", cycle, change);
   } while (cycle && change);

   GoToRef();
   return true;
}

// Green(v=2,7.3.6)
// Green(v=2,p=82,a=7.9)
bool LRFiTableMap::ChainRule()
{
   GSymbolSetMap B_p, p_T;
   TopologicalSort topological_sort(grammar->count());
   for (const GFormula* formula : grammar->formulas) {
      if (grammar->IsStart(formula->head)) continue;
      for (const GProduce& produce : *formula) {
         if (!produce.IsChain()) continue;
         const GSymbol& B = produce.front();
         topological_sort.add(formula->head.formula,B.formula);
         B_p.Add(B,produce.head);
         p_T.Get(produce.head);
      }
   }

   for (const std::pair<const GSymbol&, const LRFiTable&> tab : *this) {
      const LRFiTable& table = tab.second;
      if (table.deleted) continue;
      for (const std::pair<const GSymbol&, const TAction&> act : table) {
         const TAction& action = act.second;
         if (action.IsReduce() && p_T.Have(action.sym)) {
            p_T.Add(action.sym,tab.first);
         }
      }
   }

   int B_p_item = 0, p_T_item = 0, NEXT_item = 0, merge_count = 0;
   for (std::pair<const GSymbol&, const GSymbolSet&> item : B_p) {
      B_p_item += item.second.count();
   }
   for (std::pair<const GSymbol&, const GSymbolSet&> item : p_T) {
      p_T_item += item.second.count();
   }
   printf("\n--- ChainRule --- ");

   int ret = topological_sort.sort();

   if (references.count() != count()) references.Init(count());

   for (int i = 0; i < topological_sort.N; i++) {
      int index = topological_sort.Indexes[i];
      GSymbol B(GSymbol(GSymbol::gsFormula,index));
      if (B_p.Count(B)) {
         const GSymbolSet& p_s = B_p.Get(B);
         for (const GSymbol& p : p_s) {
            if (!p_T.Count(p)) continue;
            const GSymbolSet& T_s = p_T.Get(p);
            for (const GSymbol& T_1 : T_s) {
               TTwoSymVector NEXT;
               MakeNEXT(T_1,p,B,NEXT); 
               NEXT_item += (int)NEXT.size();
               if (ChainCompare(T_1,p,NEXT)) {
                  ChainMerge(T_1,p,B,NEXT);
                  merge_count++;
               }
            }
         }
      }
   }

   int column_del = 0, action_del = 0;
   TLXkReference chains;
   chains.Init(grammar->count());
   for (int i = topological_sort.N - 1; i >= 0; i--) {
      int index = topological_sort.Indexes[i];
      GSymbol B(GSymbol(GSymbol::gsFormula, index));
      if (B_p.Count(B)) {
         const GSymbolSet& p_s = B_p.Get(B);
         GSymbolSet As;
         int yes_del = 0;
         for (const GSymbol& p : p_s) {
            GSymbol A(GSymbol::gsFormula, p.formula);
            if (As.Add(A)) {
               LRFiColumn column_AB(A, B);
               MakeColumn(column_AB);
               if (column_AB.Compare()) {
                  column_AB.Merge();
                  yes_del++;
               }
            }
         }
         if ((yes_del == As.count()) && (As.count() == 1)) {
            action_del += DeleteColumn(B);
            const GSymbol A = *As.begin();
            chains.Set(B.formula,A.formula);
            column_del++;
         }
      }
   }
   // GSynax.ParseLRx!!!
   for (int i = 0; i < chains.count(); i++) chains.Ref(i);
   grammar->references = chains;

   int situation = 0, ref_del = 0;
   for (const std::pair<const GSymbol&, const LRFiTable&> tab : *this) {
      const LRFiTable& table = tab.second;
      if (table.deleted && !references.Deleted(situation)) {
         references.Delete(situation);
         ref_del++;
      }
      situation++;
   }

   printf("<%d> --- <%d> --- <%d> --- <%d> --- merge_count=%d, ref_del=%d, column_del=%d, action_del=%d\n", 
          B_p.count(), B_p_item, p_T_item, NEXT_item, merge_count, ref_del, column_del, action_del);

   return true;
}

void LRFiTableMap::MakeNEXT(const GSymbol& T_1, const GSymbol& p, const GSymbol& B, TTwoSymVector& NEXT) const
{
   GSymbol A(GSymbol::gsFormula, p.formula);
   for (const std::pair<const GSymbol&, const LRFiTable&> tab : *this) {
      const LRFiTable& table = tab.second;
      if (table.deleted) continue; 
      const TAction& action_B = table.FiAction(B);
      if (action_B.IsGoto() && (action_B.sym == T_1)) {
         const TAction& action_A = table.FiAction(A);
         if (action_A.IsGoto()) {
            TTwoSym item(tab.first, action_A.sym);
            NEXT.Add(item);
         }
      }
   }
}

void LRFiTableMap::MakeColumn(LRFiColumn& column)
{
   iterator tab = begin();
   while (tab != end()) {
      LRFiTable& table = (*tab).second;
      if (table.deleted) { tab++; continue; }
      const TAction& action_A = table.FiAction(column.A);
      const TAction& action_B = table.FiAction(column.B);
      if (!action_A.IsFi() || !action_B.IsFi()) {
         column.Add(&table);
      }
      tab++;
   }
}

int LRFiTableMap::DeleteColumn(const GSymbol& D)
{
   int del = 0;
   iterator tab = begin();
   while (tab != end()) {
      LRFiTable& table = (*tab).second;
      if (!table.deleted) {
         if (table.Delete(D)) del++;
      }
      tab++;
   }
   return del;
}

bool LRFiTableMap::ChainCompare(const GSymbol& T_1, const GSymbol& p, const TTwoSymVector& NEXT)
{
   GSymbol t_1(T_1); t_1.situation = references.Ref(t_1.situation);
   LRFiTableMap::const_iterator ip_T1 = find(t_1);
   const LRFiTable& T1 = (*ip_T1).second;
   for (const TTwoSym& GOTO_1_T_2 : NEXT) {
      const GSymbol& T_2 = GOTO_1_T_2.two;
      GSymbol t_2(T_2); t_2.situation = references.Ref(t_2.situation);
      LRFiTableMap::const_iterator ip_T2 = find(t_2);
      const LRFiTable& T2 = (*ip_T2).second;
      if (!T2.ChainCompare(T1,p,references)) return false;
   }
   return true;
}

void LRFiTableMap::ChainMerge(const GSymbol& T_1, const GSymbol& p, const GSymbol& B, const TTwoSymVector& NEXT)
{
   GSymbol t_1(T_1); t_1.situation = references.Ref(t_1.situation);
   LRFiTableMap::iterator ip_T1 = find(t_1);
   LRFiTable& T1 = (*ip_T1).second;
   for (const TTwoSym& GOTO_1_T_2 : NEXT) {
      const GSymbol& T_2 = GOTO_1_T_2.two;
      GSymbol t_2(T_2); t_2.situation = references.Ref(t_2.situation);
      LRFiTableMap::iterator ip_T2 = find(t_2);
      LRFiTable& T2 = (*ip_T2).second;
      T2.ChainMerge(T1,p);
   }
   GSymbol A(GSymbol::gsFormula, p.formula);
   for (const TTwoSym& GOTO_1_T_2 : NEXT) {
      const GSymbol& goto_1 = GOTO_1_T_2.one;
      LRFiTableMap::iterator ip_goto_1 = find(goto_1);
      LRFiTable& T_GOTO_1 = (*ip_goto_1).second;
      const TAction& action_A = T_GOTO_1.FiAction(A);
      LRFiTable::iterator ip = T_GOTO_1.find(B);
      TAction& action_B = (*ip).second;
      action_B.sym = action_A.sym;
   }
   T1.deleted = true;
}

int  LRFiTableMap::DelAction(const GSymbol& key, const TAction& action)
{
   int ret = 0;
   iterator ip = begin();
   while (ip != end()) {
      LRFiTable& table = (*ip).second;
      if (!table.deleted) {
         ret += table.DelAction(key, action);
      }
      ip++;
   }
   return ret;
}

void LRFiTableMap::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE_GRAMMAR_IF
   if (!printer.file_name) {
      fprintf(file, "\n--- LR Fi table --- <%d> ---\n", count());
   }
   if (print_mode == 0x00) return;
   int no_del = 0, action_count = 0;
   for (const std::pair<const GSymbol&, const LRFiTable&> item : *this) {
      const LRFiTable& table = item.second;
      if (table.deleted) continue;
      const GSymbol& key = item.first;
      key.print(printer); printer.eol(); 
      table.print(printer);
      no_del++;
      action_count += table.count();
   }
   fprintf(file, "\nreferences:");
   for (int item : references) {
      fprintf(file, "%4d ", item);
   }
   fprintf(file, "\ntable=%d, action=%d, vector=%d\n", no_del, action_count, grammar->Vectors().count());
}

