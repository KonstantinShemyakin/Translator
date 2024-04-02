// Parse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Parse.h"
#include <stack>

// --------------------------- T_Source ---------------------------
T_Source::T_Sym T_Source::Sym(int &sym)
{
	if (!text || (index >= length) || (!Char(index)))
	{
		if (index < length) length = index; 
		sym = 0;
		return slEof;
	}
	sym = Char(index);
	if (sym == '\n') return slEol;
	if ((sym == ' ') || (sym == '\t') || (sym == '\r')) return slSpace;
	if ((sym >= '0') && (sym <= '9'))  return slDigit;
	if ((sym >= 'a') && (sym <= 'z') || (sym >= 'A') && (sym <= 'Z') || (sym == '_')) return slAlpha;
	if ((sym == '.') || (sym == ',') || (sym == ';') || (sym == ':')) return slSeparator;
	if ((sym == '+') || (sym == '-') || (sym == '*') || (sym == '/')) return slOper;
   if ((sym == '\'') || (sym == '\"')) return slLimiter;
	return slUnknown;
}
 
T_Source::T_Sym T_Source::Read(int &sym)
{
	T_Sym ret = Sym(sym);
	index++;
	return ret;
}

// --------------------------- T_SourceFile ---------------------------
bool  T_SourceFile::Open(const char* name)
{
	if (name) text = name;
	FOPEN(file, text, "rb");
	return file != NULL;
}
int   T_SourceFile::Char(int pos) const  
{
	fseek(file, pos, SEEK_SET);
	int c = getc(file);
	if (c == EOF) c = 0x00;
	return c; 
}
T_Source::T_Type T_SourceFile::Type() const 
{ 
   return (T_Type)get_file_type(text);
}

// --------------------------- T_Lexeme ---------------------------
T_Scan* T_Lexeme::print_scan = NULL;
const T_WordTable* T_Lexeme::word_table = NULL;

bool T_Lexeme::Match(A_Symbol::T_Priority priority) const
{
   if ((group == T_Lexeme::grPriority) && ((A_Symbol::T_Priority)type == priority)) return true;
	if (!((group == grOper) || (group == grSeparator))) return false;
	const T_Symbol& symbol = symbol_table().Symbol(value);
	return symbol.priority == priority;
}

bool T_Lexeme::Match(T_Lexeme::W_Type keyword) const
{
	if (group != grReserv) return false;
   if (type == keyword) return true;
   const T_Word& key = T_KeyWordTable::key_word_table.Word(value);
   if (keyword == T_Lexeme::W_Type::rwDefine) {
		if ((key.type >= T_Lexeme::W_Type::rwShort) && (key.type <= T_Lexeme::W_Type::rwDouble)) return true;
   }
	return false;
}

bool T_Lexeme::Match(const T_Lexeme &l) const
{
   if (l.group == T_Lexeme::grPriority) {
   	return Match((A_Symbol::T_Priority)l.type);
   } else if (l.group == T_Lexeme::grReserv) {
   	return Match((T_Lexeme::W_Type)l.type);
   } else if ((l.group == T_Lexeme::grOper) || (l.group == T_Lexeme::grSeparator)) {
   	return Match((A_Symbol::T_Type)l.type);
   } else if (l.group == T_Lexeme::grSyntax) {
   	return Match(l.group,l.type);
   } else {
   	return Match(l.group);
   }
}

bool T_Lexeme::Match(A_Symbol::T_Type t) const
{ 
   T_Symbol::T_Type oper;
   if (group == T_Lexeme::grPriority) {
      const T_Symbol& symbol = symbol_table().Symbol(value);
      oper = T_Symbol::T_Type(symbol.type);
   } else if ((group == grOper) || (group == grSeparator) || (group == grPreproc)) {
      oper = T_Symbol::T_Type(type);
   } else {
      return false;
   }
   return (oper == t);
}

int T_Lexeme::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   if (print_mode) {
      bool no_group_mode = (print_mode & T_PrintMode::pmNoGroupLexeme) != 0;
      int len = 0;
      const char* title = group_title(group);
      if (!no_group_mode || (group != grOper) && (group != grSeparator) && (group != grMeta)) {
	      fprintf(file, "%s", title);     len += (int)strlen(title);
      }
      if ((group == grOper) || (group == grSeparator) || (group == grMeta)) {
         title = lexeme_type_title((T_Symbol::T_Type)type);
         if (no_group_mode) {
         	fprintf(file, "%s", title); len += (int)strlen(title);
         } else {
         	fprintf(file, ",%s", title); len += (int)strlen(title) + 1;
         }
   	} else if ((group == grIdent) && type) {
         fprintf(file, ",%d", type); len += 2;
   	} else if (group == grReserv) {
      	title = lexeme_word_title((T_Lexeme::W_Type)type);
      	fprintf(file, ",%s", title); len += (int)strlen(title) + 1;
   	} else if (group == grPriority) {
      	title = lexeme_priority_title((T_Symbol::T_Priority)type);
      	fprintf(file, ",%s", title); len += (int)strlen(title) + 1;
   	} else if (group == grSyntax) {
      	title = lexeme_syntax_title((T_Lexeme::T_Syntax)type);
      	fprintf(file, ",%s", title); len += (int)strlen(title) + 1;
      } else if (group == grGrammar) {
         fprintf(file, ",%03d", type); len += 4;
      } else {
      }
      return len;
   } else {
	   fprintf(file, "group=%-10s", group_title(group));
   	if ((group == grOper) || (group == grSeparator)) {
      	fprintf(file, ", type=%-12s", lexeme_type_title((T_Symbol::T_Type)type));
   	} else if (group == grReserv) {
      	fprintf(file, ", type=%-12s", lexeme_word_title((T_Lexeme::W_Type)type));
   	} else if (group == grPriority) {
      	fprintf(file, ", type=%-12s", lexeme_priority_title((T_Symbol::T_Priority)type));
   	} else if (group == grSyntax) {
      	fprintf(file, ", type=%-12s", lexeme_syntax_title((T_Lexeme::T_Syntax)type));
      } else {
      	fprintf(file, ", type=%02d          ", type);
      }
      return 6 + 10 + 7 + 12;
   }
}

void T_Lexeme::print(TPrinter& printer, const T_Scan *scan) const
{
   PRINTER_FILE_MODE
   bool eol = (print_mode & 0x01) != 0, no_pos = (print_mode & 0x02) != 0;
   TPrinter printer_group(printer, 0x00);
   print(printer_group);
   if (!no_pos) fprintf(file, ", pos=%04d", pos);
   fprintf(file,", line=%03d, column=%03d, len=%02d", line, column, len);
   if (group == grInteger) {
      fprintf(file, ", value=%d", scan ? scan->Integer(*this) : value);
   } else if (group == grPriority) {
      fprintf(file, ", value=%d", value);
   } else if (group == grNumber) {
      if (scan) fprintf(file, ", number=%lf", scan->Number(*this)); else fprintf(file, ", value=%d", value);
   } else if ((group == grOper) || (group == grSeparator) || (group == grReserv) || (group == grSyntax)) {
      fprintf(file, ", value=%d", value);
   }
	if (len || (group == grReserv)) {
      const char* my_text = Text();
      if (!my_text && scan) my_text = scan->Text(*this);
		fprintf(file,", text=");
      if (my_text) {
			fprintf(file,"%s", my_text);
      } else if (scan && (group != grLine)) {
			for (int i = 0; i < len; i++) fprintf(file,"%c", scan->Char(pos + i));
		}
	}
	if (eol) fprintf(file,"\n");
}

void T_Lexeme::write(TWriter& printer, const T_Scan *scan) const
{
   PRINTER_FILE_MODE
	fprintf(file,"%d %d %d %d %d %d %d ", group, type, pos, line, column, len, value);
   if ((group != grNone) && (group != grSpace) && (group != grLine) && (group != grEof)) { 
      const char* text = scan->Text(*this);
      if (text) {
         fprintf(file,"%s", text);
      } else {
			for (int i = 0; i < len; i++) fprintf(file,"%c", scan->Char(pos + i));
      }
   }
   fprintf(file,"\n");
}

const T_SymbolTable& symbol_table()
{ 
   //static const T_SymbolTable* table = NULL; if (!table) table = new T_SymbolTable(); return *table; 
   static T_SymbolTable table;
   return table;
}

TNameTable::~TNameTable()
{
}

void TNameTable::Clear()
{
   std::vector<const char*> ::iterator p = names.begin();
   while (p != names.end()) {
      if (*p) delete (*p);
      p = names.erase(p);
   }
}

void TNameTable::Zero()
{
   std::vector<const char*> ::iterator p = names.begin();
   while (p != names.end()) {
      (*p) = NULL;
      p = names.erase(p);
   }
}

int TNameTable::Find(const char* name) const
{
   TNameIndex::const_iterator ip = indexs.find(name); 
   if (ip != indexs.end()) {
      const std::pair<const Key, const int> item = (*ip);
      return item.second;
   } else {
      return -1;
   }
}

int TNameTable::Add(const char* name)
{
   TNameIndex::const_iterator ip = indexs.find(name); 
   if (ip != indexs.end()) {
      const std::pair<const Key, const int> item = (*ip);
      return item.second;
   } else {
      const std::pair<const Key, const int> item(name,index);
      indexs.insert(item); 
      names.push_back(name);
      return index++;
   }
}

int TNameTable::Add(const char* name, T_Lexeme &l)
{
   int len = (int)strlen(name);
   char* ident_body = (char*)malloc(len + 1);
   STRCPY(ident_body, len + 1, name);
   int old = Count();
   int add = Add(ident_body);
   l.text = Name(add);
   if (old == Count()) free(ident_body);
   return add;
}

int TNameTable::Add(T_Scan &scan, T_Lexeme &l)
{
   char* ident_body = (char*)malloc(l.len + 1);
   for (int len = 0; len < l.len; len++) {
   	int sym = scan.Char(l.pos + len);
      ident_body[len] = sym;
   }
   ident_body[l.len] = 0x00;
   int old = Count();
   int add = Add(ident_body);
   l.text = Name(add);
   if (old == Count()) free(ident_body);
   return add;
}

const char* TNameTable::Name(int index) const
{
   if ((index < 0) || (index >= Count())) return "Undefined";
   return names[index];
}

// --------------------------- T_Scan ---------------------------
T_Scan::T_Scan(T_Source *s) : source(s), line(0), beg_line(0), store_pos(0), old_line(0), mask(A_Symbol::mmTran), word_table(&T_KeyWordTable::key_word_table)
{ 
   symbol_table(); if (source) source->Reset(); 
   T_Lexeme::word_table = word_table;
}

T_Scan::~T_Scan() 
{ 
   names.Clear(); 
}

const char* T_Scan::Text(const T_Lexeme &l) const
{
   const char* text = l.Text();
   if (text) return text;
	if (l.group == T_Lexeme::grIdent) {
      text = names.Name(l.value);
   } else if ((l.group == T_Lexeme::grInteger) || (l.group == T_Lexeme::grNumber)) {
   } else if ((l.group == T_Lexeme::grOper) || (l.group == T_Lexeme::grSeparator) || (l.group == T_Lexeme::grPriority)) {
      text = symbol_table().Symbol(l.value).text;
   } else if (l.group == T_Lexeme::grReserv) {
      text = word_table->Word(l.value).text;
   }
   return text;
}

int T_Scan::Integer(const T_Lexeme &l) const
{
   return integers[l.value];
}

int T_Scan::Integer(int value) 
{ 
   int index = 0;
   for (int item : integers) {
      if (item == value) return index;
      index++;
   }
   integers.push_back(value); return (int)integers.size() - 1; 
}

double T_Scan::Number(const T_Lexeme &l) const
{
   return numbers[l.value];
}

int T_Scan::Number(const double& value)
{
   int index = 0;
   for (const double& item : numbers) {
      if (item == value) return index;
      index++;
   }
   numbers.push_back(value); return (int)numbers.size() - 1;
}

bool T_Scan::Compare(const T_Lexeme &l, const T_Lexeme &r) const 
{ 
   const char *text_l = Text(l), *text_r = Text(r);
   if ((text_l != NULL) && (text_r != NULL) ) {
      return !strcmp(text_l,text_r);
   }
   return !compare(l,r); 
}

int  T_Scan::compare(const T_Lexeme &l, const T_Lexeme &r) const
{
	int l_pos = l.pos, r_pos = r.pos;
	int len = MIN(l.len,r.len);
   while (len--) {
		int l_sym = Char(l_pos++), r_sym = Char(r_pos++), diff = l_sym - r_sym;
      if (diff) return diff;
   }
   return (l.len - r.len);
}

bool T_Scan::Compare(T_Lexeme &l, const char* title) const
{
   const char *text_l = Text(l);
   if (text_l != NULL) {
      return !strcmp(text_l, title);
   }
	int pos = l.pos;
	const char *p = title;
	int len = 0;
	while (p[0])
	{
		int sym = Char(pos + len);
		len++;
		if ((len > l.len) || (p[0] != sym)) { len = -1; break; }
		p++;
	}
	return (len == l.len);
}

T_Lexeme::T_Group T_Scan::Lex(T_Lexeme &l)
{
   store_pos = Pos(); old_line = line;
	int sym;
	l.set(T_Lexeme::grError,T_Lexeme::lxNone);
	l.pos = Pos();
	l.len = 0; l.text = NULL;
   l.value = 0;
   l.line = line;
   l.column = l.pos - beg_line;
	T_Source::T_Sym type = Read(sym);
	if (sym == '/') {
		int my_sym;
		T_Source::T_Sym my_type = Read(my_sym);
		if (my_sym == '/') {
			l.len = 2;
			my_type = Read(my_sym);
			while ((my_type != T_Source::slEof) && (my_type != T_Source::slEol)) 
			{
				l.len++;
				my_type = Read(my_sym);
			}
			Back();
			l.set(T_Lexeme::grSpace,T_Lexeme::lxComment);
			return l.group;
		} else {
			Back();
		}
	}
	if (type == T_Source::slEof) {
		l.group = T_Lexeme::grEof;
	} else if (type == T_Source::slEol) {
		l.group = T_Lexeme::grLine;
		l.len = 1;
      line++; beg_line = l.pos + 1;
	} else if (type == T_Source::slSpace) {
		do {
			l.len++;
			type = source->Read(sym);
		} while (type == T_Source::slSpace);
		l.set(T_Lexeme::grSpace,T_Lexeme::lxSpace);
		Back();
	} else if (type == T_Source::slDigit) {
      bool eight = (sym == '0');
		int value = 0, value_eight = 0, count = 0;
      double number = 0;
		do {
//			if (++count > 8) return l.group; // T_Lexeme::grError
			l.len++;
			value *= 10; value += (sym - '0');
         if (eight && (sym < '8')) {
			   value_eight *= 8; value_eight += (sym - '0');
         } else {
            eight = false;
         }
			type = Read(sym);
		} while (type == T_Source::slDigit);
		
		if ((type == T_Source::slSeparator) && (sym == '.') && !eight) {
			count = 0;
			l.len++;
			type = Read(sym);
			number = value;
			if (type == T_Source::slDigit) {
				int fraction = 0, digits = 1;
				do {
//					if (++count > 8) return l.group; // T_Lexeme::grError
					l.len++; digits *= 10;
					fraction *= 10; fraction += (sym - '0');
					type = Read(sym);
				} while (type == T_Source::slDigit);
				number += (((double)fraction) / digits);
			}
			l.group = T_Lexeme::grNumber;
         l.value = Number(number);
		} else {
			l.group = T_Lexeme::grInteger;
			value = eight ? value_eight : value;
         l.value = Integer(value);
      }
      names.Add(*this, l);
		Back();
	} else if (type == T_Source::slAlpha) {
		do {
//			if (++count > 8) return l.group; // T_Lexeme::grError
			l.len++;
			type = Read(sym);
		} while ((type == T_Source::slDigit) || (type == T_Source::slAlpha));
		Back();
		
		if (!word_table->Find(l,*this))  {
		   l.group = T_Lexeme::grIdent;
         l.value = names.Add(*this, l);
      }
	} else if ((type == T_Source::slLimiter) && (sym == '\'')) {
		l.len++;
		type = Read(sym);
      if (sym == '\'') {
		   l.len++; // error ''
	   } else  {
         if (sym == '\\') {
			   l.len++;
      		type = Read(sym);
            switch (sym) {
               case 't' : sym = 0x09; break;
               case 'n' : sym = 0x0A; break;
               case 'r' : sym = 0x0D; break;
               case 'v' : sym = 0x0B; break;
               case '0' : sym = 0x00; break;
            }
      	}
		   l.len++;
         l.value = Integer(sym);
         type = Read(sym);
         if (sym == '\'') {
			   l.len++; // 'X'
   			l.group = T_Lexeme::grInteger;
      	} else {
			   Back(); // error 'X
		   }
	   }
	} else {
		Back();
		if (symbol_table().Find(l,*this)) return l.group;
		l.len++;
		type = Read(sym);
	}
	return l.group;
}

// --------------------------- TScanArray ---------------------------

T_Lexeme::T_Group TScanArray::Lex(T_Lexeme &l)
{
   if (!make) { Make(); make = true; }
	if (index < (int)size()) {
		l = (*this)[index++]; 
	} else {
      l.group = T_Lexeme::grEof;
	}
   return l.group;
}

bool TScanArray::Make()
{
	T_Lexeme lex;
	T_Lexeme::T_Group group = LexMake(lex);
	while (group != T_Lexeme::grEof)
	{	
		if (!lex.Match(T_Lexeme::grSpace) && !lex.Match(T_Lexeme::grLine)) push_back(lex);
		group = LexMake(lex);
	}
	push_back(lex);
   return true;
}

T_Lexeme::T_Group TIfdefScan::LexMake(T_Lexeme &lex)
{
   T_Scan::Lex(lex);
   while ((lex.Match(T_Lexeme::grSpace)) || (lex.Match(T_Lexeme::grLine)))
   {
      T_Scan::Lex(lex);
   }
   return lex.group;
}

bool TIfdefScan::GetIdent(T_Lexeme &lex)
{
   if (LexMake(lex) == T_Lexeme::grIdent) return true;
   Error(lex, T_Error::erNoIdent);
   return false;
}

void TIfdefScan::AddDef(const char* name)
{
   T_Lexeme l;
   names.Add(name, l);
   definitions.insert(CharsKey(l.text));
}

void TIfdefScan::DelDef(T_Lexeme &lex)
{
   std::set<CharsKey>::iterator def = definitions.find(CharsKey(lex.text));
   if (def != definitions.end()) {
      definitions.erase(def);
   }
}

void TIfdefScan::Error(T_Lexeme &lex, T_Error e)
{
   lex.set(T_Lexeme::grError, e); error_lex = lex;
   push_back(lex);
}

bool TIfdefScan::Make()
{
   enum { stNone = 0x00, stText = 0x01, stElse = 0x02, stMain = 0x04 };
   std::stack<int> stack;
   stack.push(stText);

   T_Lexeme lex;
   T_Lexeme::T_Group group = LexMake(lex);
   while (group != T_Lexeme::grEof) {
      int& state = stack.top();
      bool yes_text = (state & stText) != 0, yes_main = (state & stMain) != 0;
      if (lex.Match(A_Symbol::lxDefine)) {
         if (yes_text) {
            if (!GetIdent(lex)) break;
            bool yes_def = Find(lex);
            if (yes_def) {
               Error(lex, T_Error::erDuplicateIdent);
               break;
            }
            definitions.insert(CharsKey(lex.text));
         }
      } else if (lex.Match(A_Symbol::lxUndef)) {
         if (yes_text) {
            if (!GetIdent(lex)) break;
            DelDef(lex);
         }
      } else if (lex.Match(A_Symbol::lxIfdef) || lex.Match(A_Symbol::lxIfndef)) {
         int new_state = stNone;
         if (yes_text) {
            new_state |= stMain;
            A_Symbol::T_Type if_type = (A_Symbol::T_Type)lex.type;
            if (!GetIdent(lex)) break;
            bool yes_ident = Find(lex);
            if (yes_ident ^ (if_type == A_Symbol::lxIfndef)) new_state |= stText;
         }
         stack.push(new_state);
      } else if (lex.Match(A_Symbol::lxElse)) {
         if ((stack.size() <= 1) || (state & stElse)) {
            Error(lex, T_Error::erSymbol);
            break;
         }
         if (yes_main) state ^= stText;
         state |= stElse;
      } else if (lex.Match(A_Symbol::lxEndif)) {
         if (stack.size() <= 1) {
            Error(lex, T_Error::erEnd);
            break;
         }
         stack.pop();
      } else {
         if (yes_text) push_back(lex);
      }

      group = LexMake(lex);
   }

   if ((stack.size() != 1) && !lex.Match(T_Lexeme::grError)) {
      Error(lex, T_Error::erNoEnd);
   }
   lex.group = T_Lexeme::grEof;
   push_back(lex);
   return error_lex.IsNone();
}

void TIfdefScan::print_def(TPrinter& printer) const
{
   if (definitions.empty()) return;
   fprintf(printer.file, "\n#define: ");
   for (const CharsKey& key : definitions) {
      fprintf(printer.file, "%s ", key.key);
   }
   fprintf(printer.file, "\n");
}

// --------------------------- T_Parse ---------------------------
T_Lexeme T_Parse::empty_ident(T_Lexeme::grIdent,0);
T_Lexeme T_Parse::oper_assign(T_Lexeme::grOper,T_Symbol::lxAssign);

T_Lexeme::T_Group T_Parse::T_Scan__Lex(T_Lexeme &l)
{
	Scan().Lex(l);
	// 0x01 - other, 0x02 - space, 0x04 - line
	int print = T_OptionMode::omNone;
	if (l.Match(T_Lexeme::grLine)) print = (option & T_OptionMode::omPrintLine);
	else if (l.Match(T_Lexeme::grSpace)) print = (option & T_OptionMode::omPrintSpace);
	else print = (option & T_OptionMode::omPrintOther);
	if (print) l.print(&this->Scan());

   if (l.Match(T_Lexeme::grReserv)) {
      if (l.Match(T_Lexeme::rwReturn) || l.Match(T_Lexeme::rwBreak) || l.Match(T_Lexeme::rwContinue) || l.Match(T_Lexeme::rwGoTo)) {
         last_key_word = l;
      }
   }

   if ((l.line > last_lexeme.line) || (l.line == last_lexeme.line) && (l.column > last_lexeme.column)) {
      last_lexeme = l;
   }

   return l.group;
}

T_Lexeme::T_Group T_Parse::Lex(T_Lexeme &l)
{
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	l = lex; 
	return lex.group;
}

void T_Parse::SkipSpace()
{
	if (lex.IsNone()) T_Scan__Lex(lex);
	while (lex.Match(T_Lexeme::grSpace) || line_is_space && lex.Match(T_Lexeme::grLine))
	{
		T_Scan__Lex(lex);
	}
}

bool T_Parse::Next()
{
	SkipSpace();
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	return (lex.group != T_Lexeme::grEof);
}

bool T_Parse::Match(T_Lexeme::T_Group group)
{
	SkipSpace();
	if (!lex.Match(group)) return false;
   forward = lex;
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	return true;
}

bool T_Parse::Match(T_Lexeme::T_Group group, int type)
{
	SkipSpace();
	if (!lex.Match(group,type)) return false;
   forward = lex;
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	return true;
}

bool T_Parse::Match(T_Lexeme &l, T_Lexeme::T_Group group)
{
	SkipSpace();
	l = lex; 
	if (!lex.Match(group)) return false;
   forward = lex;
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	return true;
}

bool T_Parse::MatchSpot(T_Lexeme &l, T_Lexeme::T_Group group)
{
	SkipSpace();
	l = lex; 
	if (!lex.Match(group)) return false;
	return true;
}

bool T_Parse::Match(T_Lexeme &l, T_Lexeme::T_Group group, int type)
{
	SkipSpace();
	l = lex; 
	if (!lex.Match(group,type)) return false;
   forward = lex;
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	return true;
}

bool T_Parse::Match(T_Symbol::T_Type type)
{
	SkipSpace();
	if (!lex.Match(type)) return false;
   forward = lex;
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	return true;
}

bool T_Parse::MatchSpot(T_Symbol::T_Type type)
{
	SkipSpace();
	if (!lex.Match(type)) return false;
	return true;
}

bool T_Parse::Match(A_Symbol::T_Priority priority)
{
	SkipSpace();
	if (!lex.Match(priority)) return false;
   forward = lex;
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	return true;
}

bool T_Parse::MatchSpot(A_Symbol::T_Priority priority)
{
	SkipSpace();
	if (!lex.Match(priority)) return false;
	return true;
}

bool T_Parse::Match(T_Lexeme &l, T_Symbol::T_Priority priority)
{
	SkipSpace();
	l = lex; 
	if (!lex.Match(priority)) return false;
   forward = lex;
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	return true;
}

bool T_Parse::Match(T_Lexeme::W_Type keyword)
{
	SkipSpace();
	if (!lex.Match(keyword)) return false;
   forward = lex;
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	return true;
}

bool T_Parse::Match(T_Lexeme &l, T_Lexeme::W_Type keyword)
{
	SkipSpace();
	l = lex; 
	if (!lex.Match(keyword)) return false;
   forward = lex;
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	return true;
}

bool T_Parse::MatchSpot(T_Lexeme::W_Type keyword)
{
	SkipSpace();
	if (!lex.Match(keyword)) return false;
	return true;
}

bool T_Parse::Match(const T_Lexeme &l)
{
	SkipSpace();
	if (!lex.Match(l)) return false;
   forward = lex;
	if (!lex.Match(T_Lexeme::grEof)) T_Scan__Lex(lex);
	return true;
}

void T_Parse::Reset()                 
{ 
	Scan().Reset();
	lex.set(T_Lexeme::grNone,T_Lexeme::lxNone); 
   store_count = 0; restore_count = 0;
}

void T_Parse::Change(T_Lexeme &l,T_Symbol::T_Type t)
{
	symbol_table().Change(l,t);
}

void T_Parse::ChangeUnary(T_Lexeme &lexeme, bool only_term)
{
   T_Symbol::T_Type oper;
   if (lexeme.group == T_Lexeme::grPriority) {
      const T_Symbol& symbol = symbol_table().Symbol(lexeme.value);
      oper = T_Symbol::T_Type(symbol.type);
   } else {
      oper = T_Symbol::T_Type(lexeme.type);
   }
   if (oper == T_Symbol::lxAdd) {
      Change(lexeme,T_Symbol::lxUnaryAdd);
   } else if (oper == T_Symbol::lxSub) {
      Change(lexeme,T_Symbol::lxUnarySub);
   } 
   if (!only_term) {
      if (oper == T_Symbol::lxPlusPlus) {
         Change(lexeme,T_Symbol::lxPostInc);
      } else if (oper == T_Symbol::lxMinusMinus) {
         Change(lexeme,T_Symbol::lxPostDec);
      }
   }
}

// --------------------------- T_Symbol ---------------------------
bool T_Symbol::Compare(T_Lexeme &lex, T_Scan &scan) const
{
	int pos = scan.Pos(), len = 0;
	const char *p = text;
	while (p[0])
	{
		int sym;
		T_Source::T_Sym t = scan.Read(sym);
		len++;
		if ((t == T_Source::slEof) || (p[0] != sym)) 
		{
			while (len--) scan.Back();
			return false;
		}
		p++;
	}
	lex.pos = pos; lex.len = len;
	lex.set(group,type);
	return true;
}

// --------------------------- T_SymbolTable ---------------------------
#define ADD_SYMBOL(GROUP, TYPE, TEXT, MASK) Add(T_Symbol(T_Lexeme::gr##GROUP, T_Symbol::lx##TYPE, TEXT, A_Symbol::mm##MASK))
#define SYMBOL_ADD(GROUP, TYPE, TEXT, PRIOR, MASK) Add(T_Symbol(T_Lexeme::gr##GROUP, T_Symbol::lx##TYPE, TEXT, T_Symbol::pr##PRIOR, A_Symbol::mm##MASK))

T_SymbolTable::T_SymbolTable() :count(0), make(false), mask(A_Symbol::mmTran)
{
   if (make) return; make = true;
   
   ADD_SYMBOL(Separator, Ellipsis,   "...", C | A_Symbol::mmC_99 | A_Symbol::mmSQL | A_Symbol::mmGrammar);
	ADD_SYMBOL(Separator, Pointer ,    "->", C | A_Symbol::mmC_99);
/*
	ADD_SYMBOL(Separator, LeftCramp ,  "<%");
	ADD_SYMBOL(Separator, RightCramp , "%>");
	ADD_SYMBOL(Separator, LeftScrape , "<:");
	ADD_SYMBOL(Separator, RightScrape ,":>");
*/
   ADD_SYMBOL(Separator, BNFSet      ,"::="   , BNF | A_Symbol::mmSQL);

   ADD_SYMBOL(Separator, BegHint     ,"/*+"   , SQL);
   ADD_SYMBOL(Separator, EndHint     ,"*/"    , SQL);
   ADD_SYMBOL(Separator, Hint        ,"--+"   , SQL);
   ADD_SYMBOL(Separator, At          ,"@"     , SQL);

	ADD_SYMBOL(Separator, ModMod      ,"%%"    , Grammar);
	ADD_SYMBOL(Separator, ModBegin    ,"%{"    , Grammar);
	ADD_SYMBOL(Separator, ModEnd      ,"%}"    , Grammar);
   ADD_SYMBOL(Separator, ModToken    ,"%token", Grammar);
   ADD_SYMBOL(Separator, ModLeft     ,"%left" , Grammar);
   ADD_SYMBOL(Separator, ModRight    ,"%right", Grammar);
   ADD_SYMBOL(Separator, LeftMaker   ,"/."    , Grammar);
   ADD_SYMBOL(Separator, RightMaker  ,"./"    , Grammar);

	SYMBOL_ADD(Oper, AddAssign,      "+=",Assign, );
	SYMBOL_ADD(Oper, SubAssign,      "-=",Assign, );
	SYMBOL_ADD(Oper, MultiAssign,    "*=",Assign, );
	SYMBOL_ADD(Oper, DivAssign,      "/=",Assign, );
	SYMBOL_ADD(Oper, ModAssign,      "%=",Assign, );
	SYMBOL_ADD(Oper, AndAssign,      "&=",Assign, );
	SYMBOL_ADD(Oper, OrAssign,       "|=",Assign, );
	SYMBOL_ADD(Oper, XOrAssign,      "^=",Assign, );
	SYMBOL_ADD(Oper, OrOr,           "||",OrOr  , );
	SYMBOL_ADD(Oper, Or,              "|",Or    , );
	SYMBOL_ADD(Oper, AndAnd,         "&&",AndAnd, );
	SYMBOL_ADD(Oper, And,             "&",And   , );
	SYMBOL_ADD(Oper, XOr,             "^",XOr   , );
	SYMBOL_ADD(Oper, Tilda,           "~",Unary , );
				   
	SYMBOL_ADD(Oper, Multi,           "*",Factor, ); 
	SYMBOL_ADD(Oper, Div,             "/",Factor, );
	SYMBOL_ADD(Oper, Mod,             "%",Factor, );
				   
	SYMBOL_ADD(Oper, PlusPlus,       "++",IncDec, );
	SYMBOL_ADD(Oper, Add,             "+",Term  , );
	SYMBOL_ADD(Oper, MinusMinus,     "--",IncDec, );
	SYMBOL_ADD(Oper, Sub,             "-",Term  , );
				   
	SYMBOL_ADD(Oper, Equ,            "==",Equ   , );
	SYMBOL_ADD(Oper, Assign,          "=",Assign, );
	SYMBOL_ADD(Oper, NotEqu,         "!=",Equ   , );
	SYMBOL_ADD(Oper, Not,             "!",Unary , );
				  
	SYMBOL_ADD(Oper, LShiftAssign,  "<<=",Assign  , );
	SYMBOL_ADD(Oper, LE,             "<=",Compare , );
	SYMBOL_ADD(Oper, LShift,         "<<",Shift   , );
	SYMBOL_ADD(Oper, LT,              "<",Compare , );
   SYMBOL_ADD(Oper, RZShiftAssign,">>>=",Assign  , ); // JAVA);
   SYMBOL_ADD(Oper, RZShift,       ">>>",Shift   , ); // JAVA);
	SYMBOL_ADD(Oper, RShiftAssign,  ">>=",Assign  , );
	SYMBOL_ADD(Oper, RShift,         ">>",Shift   , );
	SYMBOL_ADD(Oper, GE,             ">=",Compare , );
	SYMBOL_ADD(Oper, GT,              ">",Compare , );
	SYMBOL_ADD(Oper, Question,        "?",Question, );

   SYMBOL_ADD(Oper, UnaryAdd,        "+",Unary   , );
   SYMBOL_ADD(Oper, UnarySub,        "-",Unary   , );
   SYMBOL_ADD(Oper, PostInc,        "++",IncDec  , );
   SYMBOL_ADD(Oper, PostDec,        "--",IncDec  , );
	
	ADD_SYMBOL(Separator, LeftCramp,    "{", );
	ADD_SYMBOL(Separator, RightCramp,   "}", );
	ADD_SYMBOL(Separator, LeftBracket,  "(", );
	ADD_SYMBOL(Separator, RightBracket, ")", );
	ADD_SYMBOL(Separator, LeftScrape,   "[", );
	ADD_SYMBOL(Separator, RightScrape,  "]", );
	ADD_SYMBOL(Separator, ColonColon,  "::", );
	ADD_SYMBOL(Separator, Slach,       "\\", );
	ADD_SYMBOL(Separator, Point,        ".", );
	ADD_SYMBOL(Separator, Semicolon,    ";", );
	ADD_SYMBOL(Separator, Colon,        ":", );
	ADD_SYMBOL(Separator, Comma,        ",", );

   ADD_SYMBOL(Preproc,   Define, "#define", Ifdef);
   ADD_SYMBOL(Preproc,   Undef,  "#undef" , Ifdef);
   ADD_SYMBOL(Preproc,   Ifdef,  "#ifdef" , Ifdef);
   ADD_SYMBOL(Preproc,   Ifndef, "#ifndef", Ifdef);
   ADD_SYMBOL(Preproc,   Else,   "#else"  , Ifdef);
   ADD_SYMBOL(Preproc,   Endif,  "#endif" , Ifdef);

}

void T_SymbolTable::Add(const T_Symbol &sym)
{ 
   int index = table[count].index; table[count] = sym; table[count].index = index; 
   table[sym.type].index = count++;
}

const T_Symbol* T_SymbolTable::Symbol(const char* text) const
{
   size_t len = strlen(text) + 1;
	for (int i = 0; i < count; i++)
	{
		const T_Symbol& symbol = Symbol(i);
		if (!memcmp(text,symbol.text,len)) { return &symbol; }
	}
	return NULL;
}

bool T_SymbolTable::Find(T_Lexeme &lex, T_Scan &scan) const
{
	for (int i = 0; i < count; i++)
	{
		const T_Symbol& symbol = Symbol(i);
      if (!(symbol.mask & scan.mask) || (symbol.mask & (scan.mask << 16))) continue;
		if (symbol.Compare(lex, scan)) { lex.value = i; lex.text = symbol.text; return true; }
	}
	return false;
}

bool T_SymbolTable::Find(const char* text, T_Lexeme &lex) const
{
	for (int i = 0; i < count; i++)
	{
		const T_Symbol& symbol = Symbol(i);
      if (!(symbol.mask & mask) || (symbol.mask & (mask << 16))) continue;
		if (strcmp(symbol.text, text) == 0) {
         lex.group = symbol.group; lex.type = symbol.type; lex.value = i;
         return true; 
      }
	}
	return false;
}
bool T_SymbolTable::Find(char c, T_Lexeme &lex) const
{
   const char text[] = { c, 0x00 };
	return Find(text,lex);
}

void T_SymbolTable::Change(T_Lexeme &lex, T_Symbol::T_Type t) const
{
   const T_Symbol* symbol = &symbol_table().Symbol(t);
   size_t offset = symbol - symbol_table().table;
   int index = (int)offset;
   if (lex.group == T_Lexeme::grPriority) {
      lex.type = symbol->priority;
   } else {
      lex.type = t; 
   }
   lex.value = index; 
}

void T_SymbolTable::print() const
{
	int row = 0;
   for (const T_Symbol &sym : table) {
      printf("sym %2d: %d %2d %2d %2d %2d %d %s\n", row++, sym.group, sym.type, sym.priority, sym.index, sym.oper_index, sym.oper_count, sym.text);
   }
}

// --------------------------- T_Word ---------------------------
bool T_Word::Compare(const T_Lexeme &lex, T_Scan &scan) const
{
   const char *text_lex = lex.Text();
   if (text_lex != NULL) {
      return !strcmp(text_lex, text);
   }
   int pos = lex.pos, len = 0;
	const char *p = text;
	while (p[0])
	{
		int sym = scan.Char(pos + len);
		len++;
		if ((len > lex.len) || (p[0] != sym)) { len = -1; break; }
		p++;
	}
	return (len == lex.len);
}

// --------------------------- T_WordTable ---------------------------
bool T_WordTable::Find(T_Lexeme &lex, T_Scan &scan) const
{
	for (int i = 0; i < count; i++)
	{
		const T_Word& word = Word(i);
      if (!(word.mask & mask) || (word.mask & (mask << 16))) continue;
		if (word.Compare(lex, scan)) { 
         lex.set(T_Lexeme::grReserv,word.type); lex.value = i; lex.text = word.text; 
         return true; 
      }
	}
	return false;
}

bool T_WordTable::Find(T_Lexeme &lex) const
{
   for (int i = 0; i < count; i++)
   {
      const T_Word& word = Word(i);
      if (!(word.mask & mask) || (word.mask & (mask << 16))) continue;
      if (!strcmp(word.text, lex.text)) { lex.set(T_Lexeme::grReserv, word.type); lex.value = i; lex.text = word.text; return true; }
   }
   return false;
}

const T_Word& T_WordTable::Word(T_Lexeme::W_Type w) const
{
   for (int i = 0; i < count; i++)
   {
      const T_Word& word = Word(i);
      if (word.type == w) return word;
   }
   return Word(0);

}

int  T_WordTable::Index(T_Lexeme::W_Type w) const
{
   for (int i = 0; i < count; i++)
   {
      const T_Word& word = Word(i);
      if (word.type == w) return i;
   }
   return -1;

}

#define ADD_WORD(TEXT, TYPE, MASK) Add(T_Word(T_Lexeme::W_Type::rw##TYPE, TEXT, ""#TYPE"", A_Symbol::mm##MASK))

T_KeyWordTable::T_KeyWordTable()
{	
	ADD_WORD("void"      ,Void         ,);
 	ADD_WORD("short"     ,Short        ,);
 	ADD_WORD("int"       ,Int          ,);
 	ADD_WORD("long"      ,Long         ,);
   ADD_WORD("float"     ,Float        ,);
	ADD_WORD("double"    ,Double       ,);
   ADD_WORD("for"       ,For          ,);
   ADD_WORD("while"     ,While        ,);
   ADD_WORD("if"        ,If           ,);
   ADD_WORD("else"      ,Else         ,);
   ADD_WORD("do"        ,Do           ,);
   ADD_WORD("goto"      ,GoTo         ,);
   ADD_WORD("continue"  ,Continue     ,);
   ADD_WORD("break"     ,Break        ,);
   ADD_WORD("return"    ,Return       ,);
   ADD_WORD("switch"    ,Switch       ,);
   ADD_WORD("case"      ,Case         ,);
   ADD_WORD("try"       ,Try          ,);
   ADD_WORD("throw"     ,Throw        ,);
   ADD_WORD("catch"     ,Catch        ,);
   ADD_WORD("enum"      ,Enum         ,);
   ADD_WORD("default"   ,Default      ,);
	ADD_WORD("const"     ,Const        ,);
	ADD_WORD("static"    ,Static       ,);

   ADD_WORD("auto"		,Auto		     ,C | A_Symbol::mmC_99);	
   ADD_WORD("char"      ,Char         ,); // C | A_Symbol::mmC_99);
	ADD_WORD("extern"		,Extern	     ,C | A_Symbol::mmC_99);	   
	ADD_WORD("register"	,Register     ,C | A_Symbol::mmC_99);		
	ADD_WORD("signed"		,Signed	     ,C | A_Symbol::mmC_99);	   
	ADD_WORD("sizeof"	   ,Sizeof	     ,C | A_Symbol::mmC_99);  	
	ADD_WORD("struct"		,Struct	     ,C | A_Symbol::mmC_99);	   
	ADD_WORD("typedef"	,Typedef	     ,C | A_Symbol::mmC_99);	
	ADD_WORD("union"		,Union	     ,C | A_Symbol::mmC_99);		
	ADD_WORD("unsigned"	,Unsigned     ,C | A_Symbol::mmC_99);		
   ADD_WORD("volatile"  ,Volatile     ,); // C | A_Symbol::mmC_99);
#ifdef C99_GRAMMAR 
	ADD_WORD("_Bool"		,Bool		     ,C_99);	
	ADD_WORD("_Complex"	,Complex	     ,C_99);	
	ADD_WORD("_Imaginary",Imaginary    ,C_99);	
	ADD_WORD("inline"		,Inline	     ,C_99);	   
	ADD_WORD("restrict"	,Restrict     ,C_99);		
#endif
   ADD_WORD("ALL"       , All         ,Grammar);
   ADD_WORD("MAKE"      , Make        ,Grammar);
   ADD_WORD("NODE"      , Node        ,Grammar);
   ADD_WORD("CODE"      , Code        ,Grammar);
   ADD_WORD("TREE"      , Tree        ,Grammar);
   ADD_WORD("YACC"      , Yacc        ,Grammar);
   ADD_WORD("TURN"      , Turn        ,Grammar);
   ADD_WORD("CALL"      , Call        ,Grammar);
   ADD_WORD("class"     , Class       ,Grammar);
#ifdef JAVA
   ADD_WORD("package"      ,  Package        ,);
   ADD_WORD("import"       ,  Import         ,);
   ADD_WORD("public"       ,  Public         ,);
   ADD_WORD("abstract"     ,  Abstract       ,);
   ADD_WORD("final"        ,  Final          ,);
   ADD_WORD("extends"      ,  Extends        ,);
   ADD_WORD("implements"   ,  Implements     ,);
   ADD_WORD("protected"    ,  Protected      ,);
   ADD_WORD("private"      ,  Private        ,);
   ADD_WORD("throws"       ,  Throws         ,);
   ADD_WORD("this"         ,  This           ,);
   ADD_WORD("super"        ,  Super          ,);
   ADD_WORD("transient"    ,  Transient      ,);
   ADD_WORD("synchronized" ,  Synchronized   ,);
   ADD_WORD("native"       ,  Native         ,);
   ADD_WORD("interface"    ,  Interface      ,);
   ADD_WORD("boolean"      ,  Boolean        ,);
   ADD_WORD("byte"         ,  Byte           ,);
   ADD_WORD("finally"      ,  Finally        ,);
   ADD_WORD("instanceof"   ,  Instanceof     ,);
   ADD_WORD("new"          ,  New            ,);
   ADD_WORD("null"         ,  Null           ,);
#endif
}

const T_KeyWordTable T_KeyWordTable::key_word_table;

void T_Parse::Mask(A_Symbol::M_Mask mask) 
{ 
   scan->mask = mask; 
   scan->word_table->mask = mask;
   symbol_table().mask = mask;
}

static const char* group[] = { 
   "None", "Oper", "Separator", "Integer", "Number", "String", "Ident", "Reserv", "Space", "Line", "Error", "Priority", "Syntax", "Eof", "Preproc", "Meta", "Grammar"
}; 

static const char* lexeme_type[] = {
   "None","Add","Sub","Multi","Div","Mod",
	"AddAssign","SubAssign","MultiAssign","DivAssign","ModAssign","AndAssign","OrAssign","XOrAssign","Assign",
   "Or","And","OrOr","AndAnd","XOr","Tilda","Not","PlusPlus","MinusMinus",
	"Equ","NotEqu","LT","LE","GT","GE",
   "LShift","RShift","LShiftAssign","RShiftAssign",
   "LeftCramp","RightCramp","LeftBracket","RightBracket","LeftScrape","RightScrape",
   "Question","ColonColon","Slach","Point","Comma","Semicolon","Colon",
   "UnaryAdd", "UnarySub", "PostInc", "PostDec", "Pointer", "Ellipsis", 
   "ModMod", "ModBegin", "ModEnd", "ModToken", "ModLeft", "ModRight", "BNFSet",
   "Define", "Undef", "Ifdef", "Ifndef", "Else", "Endif","LeftMaker","RightMaker",
   "Hint", "BegHint", "EndHint", "At", "RZShift", "RZShiftAssign"
};

static const char* lexeme_word[] = {
	"None","For","While","If","Else","Do","GoTo","Continue","Break","Return",
   "Switch","Case","Try","Throw","Catch","Enum","Default","Void","Short","Int","Long","Float","Double","Define","Const", "Static",
   "Auto","Char","Extern","Register","Signed","Sizeof","Struct","Typedef","Union","Unsigned","Volatile"
#ifdef C99_GRAMMAR 
   ,"Bool","Complex","Imaginary","Inline","Restrict"
#endif
   ,"All","Make","Node","Code","Tree","Yacc","Turn","Call","Class"
};

static const char* lexeme_priority[] = {
   "None","Assign","Question","OrOr","AndAnd","Or","XOr","And","Equ","Compare","Shift", 
   "Term","Factor","Unary","IncDec"
};

static const char* lexeme_syntax[] = { 
   "None","IdentFunc","IdentArr","DefFunc","DefArr","DefVar","DefType","Label","Cast","CastUnary","EmptyCramp","EmptyBracket","EmptyScrape"
}; 

static const char* syntax_error[] = {
	"None", "Symbol", "End", "NoEnd", "Primary", "NoInteger", "NoIdent", "NoValue", "DefArr", "DefFunc", "Define", "DefVoid", "Statement", "Switch",
   "UnknownIdent", "DuplicateIdent", "Break", "Continue", "UnknownOper", "UnknownCast", "UnknownParam", "UnknownFunc", "DuplicateBody", "UnknownBody",
   "UnknownLabel", "DuplicateLabel", "ErrorLabel", "UnusedLabel", "InvalidType","NoReturn", "Ranges", "Uninitialized", "InvalidInit", "Impossible"
};

FUNCTION_PRINT_TITLE(print_names)
   PRINT_TITLE(group,TLexeme::TGroup)
   PRINT_TITLE(lexeme_word,TLexeme::TWord)
   PRINT_TITLE(lexeme_type,TLexeme::TType)
   PRINT_TITLE(lexeme_priority,TLexeme::TPriority)
   PRINT_TITLE(lexeme_syntax,TLexeme::TSyntax)
   PRINT_TITLE(syntax_error,TError)
END_PRINT_TITLE

class T_Title {
public:
   T_Title(const char* t) :title_(&t) {}
public:
   const char* title(int item);
   int item(const char* title);
protected:
   int count;
   const char** title_;
};

const char* T_Title::title(int item)              { return title_[item]; }
int T_Title::item(const char* t) 
{
   int i = 0;
   for (int i = 0; ; i++) {
      const char* item = (title_[i]);
      if (!item) return 0;
      if (strcmp(item, t) == 0) return i;
   }
   return 0;
}

T_Title lexeme_group(*group);

class T_Title_Error : public T_Title {
public:
   T_Title_Error(const char* t) :T_Title(t) {}
public:
   const char* title(int item)              { return title_[item & T_Error::er__Maska__]; }
} syntax_error_(*syntax_error);

const char* group_title(T_Lexeme::T_Group g)              { return group[g]; }
const char* lexeme_word_title(T_Lexeme::W_Type w)
{ 
   if (w == T_Lexeme::W_Type::rwDefine) {
      return "Define";
   }
   const T_Word& word = T_Lexeme::word_table->Word(w);
   return word.title; 
}
const char* lexeme_type_title(A_Symbol::T_Type t)         { return lexeme_type[t]; }
const char* syntax_error_title(T_Error e)                 { return syntax_error[e & T_Error::er__Maska__]; }  
const char* lexeme_syntax_title(T_Lexeme::T_Syntax s)     { return lexeme_syntax[s]; }  
const char* lexeme_priority_title(A_Symbol::T_Priority p) { return lexeme_priority[p]; }  
T_Lexeme::T_Group title_group(const char* t) 
{
   int i = 0;
   for (const char* item : group) {
      if (strcmp(item, t) == 0) return (T_Lexeme::T_Group)i;
      i++;
   }
   return T_Lexeme::T_Group::grNone;
}
T_Lexeme::W_Type title_word(const char* t) 
{
   int i = 0;
   for (const char* item : lexeme_word) {
      if (strcmp(item, t) == 0) return (T_Lexeme::W_Type)i;
      i++;
   }
   return T_Lexeme::W_Type::rwNone;
}
A_Symbol::T_Type title_type(const char* t) 
{
   int i = 0;
   for (const char* item : lexeme_type) {
      if (strcmp(item, t) == 0) return (A_Symbol::T_Type)i;
      i++;
   }
   return A_Symbol::T_Type::lxNone;
}
T_Error title_error(const char* t) 
{
   int i = 0;
   for (const char* item : syntax_error) {
      if (strcmp(item, t) == 0) return (T_Error)i;
      i++;
   }
   return T_Error::erNone;
}
T_Lexeme::T_Syntax title_syntax(const char* t) 
{
   int i = 0;
   for (const char* item : lexeme_syntax) {
      if (strcmp(item, t) == 0) return (T_Lexeme::T_Syntax)i;
      i++;
   }
   return T_Lexeme::T_Syntax::sxNone;
}
A_Symbol::T_Priority title_priority(const char* t) 
{
   int i = 0;
   for (const char* item : lexeme_priority) {
      if (strcmp(item, t) == 0) return (A_Symbol::T_Priority)i;
      i++;
   }
   return A_Symbol::T_Priority::prNone;
}

int TTokenNames::Add(const char* group, const char* type, int token)
{
   int len_g = (int)strlen(group), len_t = (type != NULL) ? (int)strlen(type) : 0;
   int len = len_g + len_t + 1;
   char* ident_body = (char*)malloc(len + 1);
   STRCPY(ident_body, len_g + 1, group);
   if (type != NULL) {
      ident_body[len_g] = '_'; STRCPY(ident_body + len_g + 1, len_t + 1, type);
   }
   int old = Count();
   int add = TNameTable::Add(ident_body);
   if (old == Count()) free(ident_body); else tokens.push_back(token);
   tokens[add] = token;
   return add;

}

void TTokenNames::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   for (std::pair<const Key, const int> item : indexs) {
      fprintf(file, "%-25s = 0x%04X\n", item.first.key, tokens[item.second]);
   }
   printer.eol();
}

void T_Parse::MakeTokens(TTokenNames& tokens, int mode) // T_Lexeme::YACC
{
   bool bnf = (mode & T_PrintMode::pmBNF) != 0, bif = (mode & T_PrintMode::pmBIF) != 0;
   tokens.Add(group_title(T_Lexeme::grIdent  ), NULL    , T_Lexeme::grIdent   << 8);
   tokens.Add(group_title(T_Lexeme::grInteger), NULL    , T_Lexeme::grInteger << 8);
   tokens.Add(group_title(T_Lexeme::grNumber ), NULL    , T_Lexeme::grNumber  << 8);
   tokens.Add(group_title(T_Lexeme::grIdent  ), "Lexeme", T_Lexeme::grIdent   << 8);
   tokens.Add(group_title(T_Lexeme::grInteger), "Lexeme", T_Lexeme::grInteger << 8);
   tokens.Add(group_title(T_Lexeme::grNumber ), "Lexeme", T_Lexeme::grNumber  << 8);
   tokens.Add(group_title(T_Lexeme::grIdent  ), "lexeme", T_Lexeme::grIdent   << 8);
   tokens.Add(group_title(T_Lexeme::grInteger), "lexeme", T_Lexeme::grInteger << 8);
   tokens.Add(group_title(T_Lexeme::grNumber ), "lexeme", T_Lexeme::grNumber  << 8);
#ifdef JAVA
   tokens.Add("IDENTIFIER"               , NULL    , 0x0600);
   tokens.Add("TYPE_NAME"                , NULL    , 0x0601);
   tokens.Add("PACKAGE_NAME"             , NULL    , 0x0604); 
   tokens.Add("EXPRESSION_NAME"          , NULL    , 0x0605);
   tokens.Add("METHOD_NAME"              , NULL    , 0x0606);
   tokens.Add("method_modifier"          , NULL    , 0x0607);
   tokens.Add("field_modifier"           , NULL    , 0x0608);
   tokens.Add("constructor_modifier"     , NULL    , 0x0609);
   tokens.Add("constant_modifiers"       , NULL    , 0x060A);
   tokens.Add("class_modifier"           , NULL    , 0x060B);
   tokens.Add("interface_modifier"       , NULL    , 0x060C);
   tokens.Add("abstract_method_modifier" , NULL    , 0x060D);
   tokens.Add("class_type"               , NULL    , 0x060E);
   tokens.Add("interface_type"           , NULL    , 0x060F);
   tokens.Add("primitive_type"           , NULL    , 0x0610);
   tokens.Add("field_type"               , NULL    , 0x0611);
#endif
   if (bnf) {
      tokens.Add(group_title(T_Lexeme::grSpace), NULL   , T_Lexeme::grSpace   << 8);
      tokens.Add(group_title(T_Lexeme::grSpace),"Lexeme", T_Lexeme::grSpace   << 8);
      tokens.Add(group_title(T_Lexeme::grSpace),"lexeme", T_Lexeme::grSpace   << 8);
      tokens.Add(group_title(T_Lexeme::grSeparator), lexeme_type_title(T_Symbol::lxBNFSet), (T_Lexeme::grSeparator << 8) | T_Symbol::lxBNFSet);
      if (bif) {
         tokens.Add(group_title(T_Lexeme::grMeta), lexeme_type_title(T_Symbol::lxLeftMaker ), (T_Lexeme::grMeta << 8) | T_Symbol::lxLeftMaker );
         tokens.Add(group_title(T_Lexeme::grMeta), lexeme_type_title(T_Symbol::lxRightMaker), (T_Lexeme::grMeta << 8) | T_Symbol::lxRightMaker);
         tokens.Add(group_title(T_Lexeme::grMeta), lexeme_type_title(T_Symbol::lxEllipsis  ), (T_Lexeme::grMeta << 8) | T_Symbol::lxEllipsis  );
      }
   }

   const char* title_group = group_title(T_Lexeme::grSyntax);
   for (int sx = T_Lexeme::sxIdentFunc; sx <= T_Lexeme::sxEmptyScrape; sx++ ) {
      tokens.Add(title_group, lexeme_syntax_title((T_Lexeme::T_Syntax)sx), (T_Lexeme::grSyntax << 8) | sx);
   }

   title_group = group_title(T_Lexeme::grPriority);
   for (int pr = T_Symbol::prAssign; pr <= T_Symbol::prIncDec; pr++) {
      tokens.Add(title_group, lexeme_priority_title((T_Symbol::T_Priority)pr), (T_Lexeme::grPriority << 8) | pr);
   }

   for (T_Symbol symbol : symbol_table().table) {
      if (!symbol.text) continue;
      if (bnf && ((symbol.group != T_Lexeme::grOper) || (symbol.priority != T_Symbol::prOr))) continue;
      tokens.Add(group_title(symbol.group), lexeme_type_title(symbol.type), (symbol.group << 8) | symbol.type);
   }
}

char* get_file_name(const char*file, const char* ext)
{
   if (!file) return NULL;
   int len_file = (int)strlen(file), len_ext = (int)strlen(ext);
   char* file_ext = (char*)malloc(len_file + len_ext + 1 + 1);
   int pos_point = len_file - 1;
   for (; (pos_point >= 0) && (file[pos_point] != '.'); pos_point--);
   if (pos_point < 0) pos_point = len_file;
   for (int i = 0; i < pos_point; i++) file_ext[i] = file[i];
   file_ext[pos_point++] = '.';
   for (int i = 0; i < len_ext; i++) file_ext[pos_point++] = ext[i];
   file_ext[pos_point++] = 0x00;
   return file_ext;
}

int get_file_type(const char*file)
{
   if (!file) return T_Source::ftNone;
   int len_file = (int)strlen(file);
   int pos_point = len_file - 1;
   for (; (pos_point >= 0) && (file[pos_point] != '.'); pos_point--);
   if (pos_point < 0) return T_Source::ftUnknown;
   file += pos_point + 1;
   if (!strcmp(file, "YACC") || !strcmp(file, "yacc")) return T_Source::ftYACC;
   if (!strcmp(file, "y"   )) return T_Source::ftY;
   if (!strcmp(file, "bnf" )) return T_Source::ftBNF;
   if (!strcmp(file, "bif" )) return T_Source::ftBIF;
   return T_Source::ftUnknown;
}

int print_source(T_Source &source, const char* file_name)
{
   PRINT_FILE_OPEN_NO_RETURN(file, file_name, "wb");
   int count = 0;
   if (file == NULL) return count;
   int sym;
   T_Source::T_Sym type;
   while ((type = source.Read(sym)) != T_Source::slEof)
   {
      fprintf(file, "%c", sym); count++;
   }
   fprintf(file, "\n");
   if (file_name) {
      fclose(file);
   }
   return count;
}

int scan_source(T_Parse &scan)
{
   int count = 0;
   T_Lexeme lexeme;
   T_Lexeme::T_Group group = scan.Lex(lexeme);
   while (group != T_Lexeme::grEof) {
      count++;
      group = scan.Lex(lexeme);
   }
   return count;
}

// --------------------------- TPrinter ---------------------------
TPrinter::TPrinter(int p) :owner(NULL), file(stdout), grammar(NULL), file_name(NULL), print_mode(p), title(NULL), param(NULL), semantic(NULL), length(0), shift_(0) {}

TPrinter::TPrinter(const TGrammar* g, int p) :owner(NULL), file(stdout), grammar(g), file_name(NULL), print_mode(p), title(NULL), param(NULL), semantic(NULL), length(0), shift_(0) {}

TPrinter::TPrinter(const char* t, int p, const TGrammar* g) :owner(NULL), file(NULL), grammar(g), file_name(t), print_mode(p), title(NULL), param(NULL), semantic(NULL), length(0), shift_(0)
{
   if (file_name) {
      FOPEN(file, file_name, "w");
      if (!file) file = stdout;
   } else {
      file = stdout;
   }
}

TPrinter::TPrinter(TPrinter& o, int p) :owner(&o), file(o.file), file_name(NULL), grammar(o.grammar), title(NULL), param(NULL), semantic(NULL), length(0), shift_(o.shift_)
{
   if (p == -1) print_mode = owner->print_mode; else print_mode = p;
}

void TPrinter::reset(const char* f_m, int p)
{
   if (file_name) {
      fclose(file);
   }
   file_name = f_m;
   if (file_name) {
      FOPEN(file, file_name, "w");
      if (!file) file = stdout;
   } else {
      file = stdout;
   }
   if (p != -1) print_mode = p;
}

void TPrinter::print_offset(int level, int mode)
{
   ::print_offset(level, mode, file);
}

void TPrinter::offset(int len, bool yes_eol)
{
   if (yes_eol) eol();
   if (shift_ < 0) {
      shift_ = -shift_;
   }
   len += shift_;
   if (len > 0) { 
      fprintf(file, "%*c", len, ' '); // length += len;
   }
}

void TPrinter::shift(int len)
{
   if (shift_ >= 0) {
      shift_ += len;
      shift_ = -shift_;
   }
}

void TPrinter::eol() 
{ 
   fprintf(file,"\n"); 
   length = 0;
}

void TPrinter::trail(int &len, int mode)
{
   int LEN = (mode & TPrinter::trMaker) ? MAKER_PRINT_TITLE_LEN : SYMBOL_PRINT_TITLE_LEN;
   if ((mode & TPrinter::trLen) && !len) return;
   if (!(print_mode & T_PrintMode::pmCompact) && !(mode & TPrinter::trOffset) || (print_mode & T_PrintMode::pmOffset) && (mode & TPrinter::trOffset)) {
      if ((mode & TPrinter::trSkip) && (len > SYMBOL_PRINT_TITLE_LEN + 1)) {
         len -= SYMBOL_PRINT_TITLE_LEN + 1;
      }
      if (mode & TPrinter::trLenPlus) length += len;
      length += LEN - len;
      while (len++ < LEN) fprintf(file, " "); 
   } else if (mode & TPrinter::trElse) {
      fprintf(file, "   ");
      length += 3;
   }
}

TPrinter::~TPrinter()
{
   if (owner) {
   } else {
      if (file_name && (file != NULL) && (file != stdout)) {
         fclose(file);
      }
   }
}

