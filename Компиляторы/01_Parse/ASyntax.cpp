
#include "stdafx.h"

#include "Parse.h"
#include "ASyntax.h"
#include "TNodes.h"

// --------------------------- TError ---------------------------
bool TError::error(T_Error code, const T_Lexeme &l, int value)
{
  	printf("\nError:%-14s, error=%02d, value=%02d", syntax_error_title(code), code, value);
   if (code == T_Error::erSymbol) {
   	const char* text = symbol_table().Text(T_Symbol::T_Type(value));
   	printf(", symbol=%s", text);
   }
   printf("\n");
   l.print(Scan);
   return false;
}

void TErrorTable::Add(T_Error code, const T_Lexeme &l, int value)
{
   push_back(TErrorItem(code, l, value));
}

void TErrorTable::print() const
{
	printf("\n--- ErrorTable ---- %d ----\n",(int)size());
   for (const TErrorItem item : *this) {
      syntax->Error.error(item.code,item.lexeme,item.value);
   }
}

// ------------------------- A_Syntax -------------------------
A_Syntax::~A_Syntax()
{
}

bool A_Syntax::MatchMust(T_Symbol::T_Type t)
{
	if (Match(t)) return true;
	return error(T_Error::erSymbol,lex,t);
}

bool A_Syntax::error(T_Error code, const T_Lexeme &l, int value) 
{ 
   ErrorTable.Add(code,l,value);
   return false; //  Error.error(code, l, value);
}

// (result & mode): -1 - error, 0, 0x01 - define, 0x02 - const, 0x04 - static, 0x08 - &, 0x10 - after define, 0x20 - void
int  A_Syntax::SCDefine(T_Lexeme &l, int mode) 
{
   int def = 0;
   bool next;
   T_Lexeme l_;
   do {
      next = false;
		if (Match(l_, T_Lexeme::W_Type::rwDefine)) {
         l = l_;
         next = true;
         if (def & 0x21) { def = -1; break; }
         def |= 0x01;
         }
      if (Match(T_Lexeme::W_Type::rwVoid)) {
         l = l_;
         next = true;
         if (def & 0x21) { def = -1; break; }
         def |= 0x20;
         }
      if (Match(T_Lexeme::W_Type::rwConst)) {
         next = true;
         if ((def & 0x02) || !(mode & 0x02)) { def = -1; break; }
         def |= 0x02;
         if (def & 0x01) def |= 0x10;
         }
      if (Match(T_Lexeme::W_Type::rwStatic)) {
         next = true;
         if ((def & 0x04) || !(mode & 0x04)) { def = -1; break; }
         def |= 0x04;
         if (def & 0x01) def |= 0x10;
      }
   } while (next);

   if ((def > 0) && !(def & 0x21)) def = -1; // not define
   if ((def > 0) && (mode & 0x08) && Match(T_Symbol::T_Type::lxAnd)) def |= 0x08; // reference
   if (def < 0) { error(erDefine); }

   return def;
}

T_Lexeme::T_Group A_Syntax::Lexeme(T_Lexeme &l)
{
	SkipSpace();
   l = lex;
   if (!(syntax_lexeme & T_SyntaxLexeme::slSyntax)) {
      if (!(syntax_lexeme & T_SyntaxLexeme::slNoDefType) && (l.group == T_Lexeme::T_Group::grReserv) && (l.type >= T_Lexeme::W_Type::rwShort) && (l.type <= T_Lexeme::W_Type::rwDouble)) {
         l.value = l.type;
         l.group = T_Lexeme::T_Group::grSyntax; l.type = T_Lexeme::T_Syntax::sxDefType;
      } else if ((syntax_lexeme & T_SyntaxLexeme::slPrior) && (l.group == T_Lexeme::grOper)) {
         const T_Symbol& symbol = symbol_table().Symbol(l.value);
         bool prior = !!symbol.priority;
         if ((symbol.priority == T_Symbol::prAssign) && !(syntax_lexeme & T_SyntaxLexeme::slPriorAssign)) prior = false;
         if (prior) {
            l.group = T_Lexeme::grPriority; l.type = symbol.priority;
         }
      }
      forward = l;
      Next();
   	if (option & T_OptionMode::omPrintLexeme) l.print(&this->Scan());
      return l.group;
   }
   int def = 0;
	if (Match(T_Lexeme::T_Group::grIdent)) {
      T_ScanStore store_ident; T_Parse::Store(store_ident);
		if (Match(T_Symbol::lxLeftBracket) || Match(T_Symbol::lxLeftScrape) || Match(T_Symbol::lxColon)) {
         int type = (forward.type == T_Symbol::lxLeftBracket) ? T_Lexeme::T_Syntax::sxIdentFunc : (
                    (forward.type == T_Symbol::lxLeftScrape ) ? T_Lexeme::T_Syntax::sxIdentArr  : T_Lexeme::T_Syntax::sxLabel);
         forward = l;
         l.group = T_Lexeme::T_Group::grSyntax; 
         l.type = type;
         T_Parse::Restore(store_ident);
      }
   } else if (l.Match(T_Lexeme::T_Group::grReserv)) {
      def = SCDefine(l,0x026); // 0x02 - const, 0x04 - static, 0x20 - void
      if (def < 0) { 
         l.group = T_Lexeme::T_Group::grError; 
      	if (option & T_OptionMode::omPrintLexeme) l.print(&this->Scan());
         return l.group;
      }
      T_ScanStore store_ref; T_Parse::Store(store_ref);
      if ((def > 0) && Match(T_Symbol::T_Type::lxAnd)) def |= 0x08; // reference
      if (def > 0) { // 0x02 - const, 0x04 - static, 0x08 - &, 0x20 - void
         T_ScanStore store_func; T_Parse::Store(store_func);
         if (Match(T_Lexeme::grIdent)) {
            int type ;
            if (Match(T_Symbol::lxLeftBracket)) {
               type = T_Lexeme::T_Syntax::sxDefFunc;
            } else if ((def > 0) && Match(T_Symbol::lxLeftScrape)) {
               type = !(syntax_lexeme & T_SyntaxLexeme::slNoDefArrVar) ? T_Lexeme::T_Syntax::sxDefArr : T_Lexeme::T_Syntax::sxDefType;
            } else {
               type = !(syntax_lexeme & T_SyntaxLexeme::slNoDefArrVar) ? T_Lexeme::T_Syntax::sxDefVar : T_Lexeme::T_Syntax::sxDefType;
            }
            forward = l;
            l.value = (def << 16) | l.type;
            l.group = T_Lexeme::T_Group::grSyntax; 
            l.type = type;
            T_Parse::Restore(store_func);
         } else {
            if ((def == 0x01) && Match(T_Symbol::lxLeftBracket)) { // only define
               forward = l;
               l.value = (def << 16) | l.type;
               l.group = T_Lexeme::T_Group::grSyntax; l.type = T_Lexeme::T_Syntax::sxCast;
               T_Parse::Restore(store_func);
            } else if (def > 0) { 
               forward = l;
               l.value = (def << 16) | l.type;
               l.group = T_Lexeme::T_Group::grSyntax; l.type = T_Lexeme::T_Syntax::sxDefType;
               if (def & 0x08) { // reference
                  def &= ~0x08;
               } 
               T_Parse::Restore(store_ref);
            } else { // void
               l.group = T_Lexeme::T_Group::grError; 
            }
         }
      } else {
         forward = lex;
         Next();
      }
   } else if (Match(T_Symbol::lxLeftBracket)) { // cast, ()
      T_Lexeme lexeme = forward;
      if (Match(T_Symbol::lxRightBracket)) { 
         l.group = T_Lexeme::T_Group::grSyntax; l.type = T_Lexeme::T_Syntax::sxEmptyBracket;
      	if (option & T_OptionMode::omPrintLexeme) l.print(&this->Scan());
         return l.group;
      }
      T_ScanStore store; T_Parse::Store(store);
      def = SCDefine(l,0x02); // 0x02 - const
      if (def < 0) { 
         l.group = T_Lexeme::T_Group::grError; 
      	if (option & T_OptionMode::omPrintLexeme) l.print(&this->Scan());
         return l.group;
      } else if ((def > 0) && Match(T_Symbol::lxRightBracket)) { 
         forward = l;
         l.value = (def << 16) | l.type;
         l.group = T_Lexeme::T_Group::grSyntax; l.type = T_Lexeme::T_Syntax::sxCastUnary;
      } else {
         T_Parse::Restore(store);
         forward = lexeme;
         l = lexeme;
      }
   } else if (Match(T_Symbol::lxLeftCramp))  { // {}
      T_Lexeme lexeme = forward;
      if (Match(T_Symbol::lxRightCramp)) { 
         l.group = T_Lexeme::T_Group::grSyntax; l.type = T_Lexeme::T_Syntax::sxEmptyCramp;
         forward = lexeme;
      	if (option & T_OptionMode::omPrintLexeme) l.print(&this->Scan());
         return l.group;
      }
      l = lexeme;
   } else if (Match(T_Symbol::lxLeftScrape)) { // []
      T_Lexeme lexeme = forward;
      if (Match(T_Symbol::lxRightScrape)) { 
         l.group = T_Lexeme::T_Group::grSyntax; l.type = T_Lexeme::T_Syntax::sxEmptyScrape;
         forward = lexeme;
      	if (option & T_OptionMode::omPrintLexeme) l.print(&this->Scan());
         return l.group;
      }
      l = lexeme;
   } else if (Match(T_Symbol::lxRightScrape)) { // ]
      l = forward;
   } else if ((syntax_lexeme & T_SyntaxLexeme::slPrior) && (Match(T_Lexeme::grOper))) {
      const T_Symbol& symbol = symbol_table().Symbol(l.value);
      bool prior = !!symbol.priority;
      if ((symbol.priority == T_Symbol::prAssign) && !(syntax_lexeme & T_SyntaxLexeme::slPriorAssign)) prior = false;
      if (prior) {
         l.group = T_Lexeme::grPriority; l.type = symbol.priority;
         forward = l;
      }
   } else {
      forward = lex;
      Next();
   }
 	if (option & T_OptionMode::omPrintLexeme) l.print(&this->Scan());
   return l.group;
}

bool A_Syntax::MatchSyntax(T_Lexeme &l, const T_Lexeme &lexeme)
{
   bool ret = true;
   if (lexeme.group == T_Lexeme::T_Group::grSyntax) {
      T_ScanStore store; T_Parse::Store(store);
      Lexeme(l);
      if (l.group == T_Lexeme::T_Group::grError) {
         ret = false;
      } else if (l.group == T_Lexeme::T_Group::grSyntax) {
         if ((l.type == T_Lexeme::T_Syntax::sxDefArr) && (lexeme.type == T_Lexeme::T_Syntax::sxDefType)) {
            l.type = lexeme.type;
         } else if ((l.type == T_Lexeme::T_Syntax::sxDefVar) && (lexeme.type == T_Lexeme::T_Syntax::sxDefType)) {
            l.type = lexeme.type;
         } else if ((l.type == T_Lexeme::T_Syntax::sxDefType) && (lexeme.type == T_Lexeme::T_Syntax::sxDefVar)) {
            l.type = lexeme.type;
            if (Match(T_Symbol::T_Type::lxAnd)) l.value |= (0x08 << 16); // reference
         }
         if (l.type != lexeme.type) {
            T_Parse::Restore(store);
            ret = false;
         }
      } else {
         T_Parse::Restore(store);
         ret = false;
      }
   } else {
      ret = T_Parse::Match(lexeme);
      l = forward;
   }
	return ret;
}

bool A_Syntax::MatchLexeme(const T_Lexeme &lexeme)
{
   bool ret = true;
   if (lexeme.group == T_Lexeme::T_Group::grSyntax) {
      T_Lexeme l;
      ret = MatchSyntax(l,lexeme);
      if (ret) PushLexeme(l);
   } else {
      ret = Match(lexeme);
      if (ret) PushLexeme(lexeme);
   }
   return ret;
}

bool A_Syntax::IsSaved(const T_Lexeme& lexeme) const
{
   return lexeme.IsSaved();
}

TNodeType* A_Syntax::BaseType(const T_Lexeme &l, int detail)
{
   TNodeType *type = TBaseType::BaseType(l, detail); // new TNodeType(*)
   return type;
}

void A_Syntax::print_store(TPrinter& printer) const
{
   fprintf(printer.file, "\nstore_parse=%d, restore_parse=%d, store_syntax=%d, restore_syntax=%d\n",T_Parse::store_count, T_Parse::restore_count,store_count, restore_count);
}

bool A_Syntax::Source(T_SourceFile& source, const char* file, const T_WordTable* word_table)
{
	if (!source.Open(file)) {
      printf("\nfile error : %s\n", file);
      return false;
   }
	
   T_Lexeme::print_scan = &Scan();
   T_Lexeme::print_scan->word_table = word_table;
   T_Lexeme::word_table = word_table;

   if (option & T_OptionMode::omPrintSource) {
	   print_source(source);
	   source.Reset();
   }
   return true;
}

bool A_Syntax::SemanticMode(M_Mode area, M_Mode mode) const
{
   int my_mode = (option_mode >> (4 * area)) & 0x0000000F;
   return my_mode == mode;
}
