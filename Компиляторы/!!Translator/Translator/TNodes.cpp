// Parse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TNodes.h"
#include "TSemantic.h"

void TNode::InsertAfter(TNode *b)
{
   if (after) {
      TNode* node = after;
      while (node->after) node = node->after;
      node->after = b;  b->SetBefore(node);
   } else {
      after = b; b->SetBefore(this);
   }
   b->SetOwner(this);
}
void TNode::InsertBefore(TNode *b)
{
   if (before) {
      TNode* node = before;
      while (node->before) node = node->before;
      node->before = b;  b->SetAfter(node);
   } else {
      before = b; b->SetAfter(this);
   }
   b->SetOwner(this);
}

void TNode::SetOwner(TNode *o) 
{ 
   if (!owner) {
      owner = o;
   }
}

int  TNode::Passport(int mode) 
{ 
   int pass = ~passport & mode; passport |= pass; return pass; 
}
void TNode::Passport(A_Syntax* syntax, int mode) 
{
   if (SYNTAX_MODE(Phase, TwoPhase)) if (int my_mode = Passport(mode)) Variables(*(syntax->data->semantic), my_mode);
}
void TNode::Passport(TSemantic &semantic, int mode) 
{
   if (!SEMANTIC_MODE(Phase, TwoPhase) || (passport & T_Step::tsChildren)) if (int my_mode = Passport(mode)) Variables(semantic, my_mode);
}

bool TNode::ClearNode(TNode* N)
{
   if (N && (!N->Owner() || (N->Owner() == this))) {
      if (TNodeType *type = dynamic_cast<TNodeType*>(N)) {
         int i=12; i++;
      } else if (T_NodeList *list = dynamic_cast<T_NodeList*>(N)) {
         T_NodeList::iterator p = list->begin();
         while (p != list->end()) {
            list->ClearNode(*p);
            p = list->erase(p);
         }
      }
      N->clear(); GarbageCollectorAdd(N,0x01);
      return true; 
   }
   return false;
}

void TNode::clear()   {}

const T_Lexeme& TNodeDefVar::FirstLexeme() const
{
   if (!mid || !lexeme.IsNone()) return lexeme;
   return ((T_NodeList*)mid)->FirstLexeme();
}

bool T_NodeList::IsNull() const
{
   for (const TNode *node : (*this)) {
      if (!node->IsNull()) return false;
   }
   return true;
}
const T_Lexeme& T_NodeList::FirstLexeme() const
{
   if (!Count() || !lexeme.IsNone()) return lexeme;
   return front()->FirstLexeme();
}
void T_NodeList::Add(TNode *r)
{
   r->SetOwner(this); if (r->Owner() == (TNode*)this) r->child_number = Count();  push_back(r);
}
void T_NodeList::Insert(int i, TNode *r)
{
   r->SetOwner(this); insert(begin() + i, r);
   if (r->Owner() == (TNode*)this) {
      for (; i < Count(); i++) {
         (*this)[i]->child_number = i;
      }
   }
}

void T_NodeList::clear()
{
	iterator p = begin();
   while (p != end()) { 
      ClearNode(*p);
      p = erase(p);
   }
}

void TNodeDefFunc::clear() { if (profile) { delete profile; profile = NULL; } T_NodeThree<TNodeType, TNodeDefine, TNode>::clear(); }
void TNodeCall::clear()    { if (profile) { delete profile; profile = NULL; } T_NodeTwo<TNodeDefFunc, T_NodeList>::clear(); }

void print_offset(int level, int mode, FILE *file) // 0x01 - eol, 0x02 - !offset
{
   bool eol = (mode & 0x01) != 0x00, not_offset = (mode & 0x02) != 0x00;
   if (eol) fprintf(file, "\n");
   if (!not_offset) {
      if (level > 0) fprintf(file,"%*c",level * 2, ' ');
   } else {
      fprintf(file,"*%05d* ", level);
   }
}
 
void TNode::print(int level, TPrinter& printer) const
{
   PRINTER_FILE_MODE
   if (level >= 0) print_offset(level, true, file);
   fprintf(file, "%-15s", title());
   if (level >= 0) {
      fprintf(file, " type = %-10s, ",TBaseType::Title(BaseType()));
      if (lexeme.group != lexeme.grNone) {
         TPrinter printer_lexeme(printer, 0x02);
         fprintf(file, "  "); lexeme.print(printer_lexeme, T_Lexeme::print_scan); // !pos
      }
   } else {
      fprintf(file, " line=%03d, column=%03d, len=%02d", lexeme.line, lexeme.column, lexeme.len);
      fprintf(file, ", text=");
      if (lexeme.Text()) {
         fprintf(file, "%s", lexeme.Text());
      } else {
         for (int i = 0; i < lexeme.len; i++) fprintf(file, "%c", T_Lexeme::print_scan->Char(lexeme.pos + i));
      }
   }
}

void TNode::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   if (print_mode) {
      fprintf(file,"\n%s",title());
      TPrinter printer_lexeme(printer, 0x00);
      lexeme.write(printer_lexeme, T_Lexeme::print_scan);
   } else {
      TNode::print(-1, printer);
   }
}

void T_NodeList::print(int level, TPrinter& printer) const
{
   TNode::print(level, printer);
	const_iterator p = begin();
   while (p != end()) { 
      (*p)->print(level + 1, printer);
      p++;
   }
}

void T_NodeList::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   TNode::write(printer);
   fprintf(file,"\n%d",(int)size());
	const_iterator p = begin();
   while (p != end()) { 
      (*p)->write(printer);
      p++;
   }
}

void TNodeVar::print(int level, TPrinter& printer) const
{
   TNode::print(level, printer);
   if (child) child->TNode::print(level + 1, printer); // type
}

void TNodeVar::write(TWriter& printer) const
{
   TNode::write(printer);
   if (child) child->TNode::write(printer); // type
}

void TNodeCall::print(int level, TPrinter& printer) const
{
   TNode::print(level, printer);
   if (left)  left->TNode::print(level + 1, printer); // type
   if (right) right->print(level + 1, printer); 
}

void TNodeCall::write(TWriter& printer) const
{
   TNode::write(printer);
   if (left)  left->TNode::write(printer); // type
   if (right) right->write(printer);
}

void TNodeIndex::print(int level, TPrinter& printer) const
{
   TNode::print(level, printer);
   if (left)  left->TNode::print(level + 1, printer); // type
   if (right) right->print(level + 1, printer); 
}

void TNodeIndex::write(TWriter& printer) const
{
   TNode::write(printer);
   if (left)  left->TNode::write(printer); // type
   if (right) right->write(printer);
}

void TNodeDefVar::print(int level, TPrinter& printer) const
{
   PRINTER_FILE_MODE
   T_NodeThree::print(level, printer); printer.eol();
   print_offset(level + 1, false, file); fprintf(file, "alloc=%s, offset=%02d",title_alloc(alloc), offset);
}

void TNodeLabel::print(int level, TPrinter& printer) const
{
   PRINTER_FILE_MODE
   TNode::print(level, printer);
   print_offset(level + 1, false, file); fprintf(file, "go_to=%02d",go_to);
   if (child) child-> print(level + 1, printer);
}

void TNodeUserLabel::print(int level, TPrinter& printer) const
{
   TNodeLabel::print(level, printer);
   T_UserGoToLabel::print(printer);
}

void TNodeUserGoTo::print(int level, TPrinter& printer) const
{
   TNodeGoTo::print(level, printer);
   T_UserGoToLabel::print(printer);
}

static const T_BaseType btarr[] =
{
   T_BaseType::btVoid   , T_BaseType::btShort   , T_BaseType::btInt   , T_BaseType::btLong   , T_BaseType::btFloat   , T_BaseType::btDouble   ,
   T_BaseType::btCVoid  , T_BaseType::btCShort  , T_BaseType::btCInt  , T_BaseType::btCLong  , T_BaseType::btCFloat  , T_BaseType::btCDouble  ,
   T_BaseType::btRVoid  , T_BaseType::btRShort  , T_BaseType::btRInt  , T_BaseType::btRLong  , T_BaseType::btRFloat  , T_BaseType::btRDouble  ,
   T_BaseType::btCRVoid , T_BaseType::btCRShort , T_BaseType::btCRInt , T_BaseType::btCRLong , T_BaseType::btCRFloat , T_BaseType::btCRDouble ,
   T_BaseType(T_BaseType::btVoid   | T_BaseType::btStatic), T_BaseType(T_BaseType::btShort   | T_BaseType::btStatic), T_BaseType(T_BaseType::btInt   | T_BaseType::btStatic), T_BaseType(T_BaseType::btLong   | T_BaseType::btStatic), T_BaseType(T_BaseType::btFloat   | T_BaseType::btStatic), T_BaseType(T_BaseType::btDouble   | T_BaseType::btStatic),
   T_BaseType(T_BaseType::btCVoid  | T_BaseType::btStatic), T_BaseType(T_BaseType::btCShort  | T_BaseType::btStatic), T_BaseType(T_BaseType::btCInt  | T_BaseType::btStatic), T_BaseType(T_BaseType::btCLong  | T_BaseType::btStatic), T_BaseType(T_BaseType::btCFloat  | T_BaseType::btStatic), T_BaseType(T_BaseType::btCDouble  | T_BaseType::btStatic),
   T_BaseType(T_BaseType::btRVoid  | T_BaseType::btStatic), T_BaseType(T_BaseType::btRShort  | T_BaseType::btStatic), T_BaseType(T_BaseType::btRInt  | T_BaseType::btStatic), T_BaseType(T_BaseType::btRLong  | T_BaseType::btStatic), T_BaseType(T_BaseType::btRFloat  | T_BaseType::btStatic), T_BaseType(T_BaseType::btRDouble  | T_BaseType::btStatic),
   T_BaseType(T_BaseType::btCRVoid | T_BaseType::btStatic), T_BaseType(T_BaseType::btCRShort | T_BaseType::btStatic), T_BaseType(T_BaseType::btCRInt | T_BaseType::btStatic), T_BaseType(T_BaseType::btCRLong | T_BaseType::btStatic), T_BaseType(T_BaseType::btCRFloat | T_BaseType::btStatic), T_BaseType(T_BaseType::btCRDouble | T_BaseType::btStatic)
};

static TNodeType*& arr_type(int i)
{
   static TNodeType* arr_type_[sizeof(btarr) / sizeof(int)];
   static bool make = false;
   if (!make) {
      const int count = sizeof(btarr) / sizeof(int);
      for (int i = 0; i < count; i++) {
         T_BaseType type = btarr[i];
         T_Lexeme lexeme; lexeme.group = lexeme.grReserv; lexeme.value = type & 0x00FF; 
         lexeme.text = T_KeyWordTable::key_word_table.Word(lexeme.value).text;
         lexeme.type = lexeme.value + lexeme.rwVoid;
         TNodeType* node = new TNodeType(lexeme); node->base_type = type;
         node->SetOwner(node);
         arr_type_[i] = node;
      }
      make = true;
   }
   if (make && (i == -1)) 
   {
      for (TNodeType* node : arr_type_) {
         delete node;
      }
      i = 0;
   }
   return arr_type_[i];
}

TBaseType::TBaseType()
{
}

void TBaseType::Clear()
{
   arr_type(-1);
}

TNodeType* TBaseType::BaseType(const T_Lexeme &l, int detail)
{
   T_Lexeme lexeme(l);
   int def = 0;
   if (l.group == T_Lexeme::grSyntax) {
      def = (l.value >> 16) & 0x0000FFFF;
      lexeme.group = T_Lexeme::grReserv; lexeme.type = l.value & 0x0000FFFF;
   } else {
      def = detail;
   }
   const int offset = T_BaseType::btDouble - T_BaseType::btVoid + 1;
   int type = lexeme.type - T_Lexeme::W_Type::rwVoid;
   if ((def & 0x02) != 0) type +=     offset; // const
   if ((def & 0x04) != 0) type += 4 * offset; // static
   if ((def & 0x08) != 0) type += 2 * offset; // reference
   return arr_type(type);
}

TNodeType* TBaseType::Or(const TNodeType* type, T_BaseType maska)
{
   T_BaseType new_type = Or(type->base_type,maska);
   int index = Index(new_type);
   return arr_type(index);
}

int TBaseType::Index(T_BaseType type)
{
   if (type == btUnknown) return -1;
   const int offset = T_BaseType::btDouble - T_BaseType::btVoid + 1;
   int index = type & 0x00FF;
   if (type & btConst) index += offset;
   if (type & btStatic) index += 4 * offset;
   if (type & btReference) index += 2 * offset;
   return index;
}

T_BaseType TBaseType::Const(T_BaseType type)
{
   return Or(type,T_BaseType::btConst);
}

T_BaseType TBaseType::Or(T_BaseType type, T_BaseType maska)
{
   if (type == btUnknown) return btUnknown;
   return T_BaseType(type | maska);
}

T_BaseType TBaseType::And(T_BaseType type, T_BaseType maska)
{
   if (type == btUnknown) return btUnknown;
   return T_BaseType(type & maska);
}

T_BaseType TBaseType::Tilda(T_BaseType type, T_BaseType maska)
{
   if (type == btUnknown) return btUnknown;
   return T_BaseType(type & ~maska);
}

const char* TBaseType::Title(T_BaseType type)
{
   static const char* title[] = {
   "Void"  ,"Short"  ,"Int"  ,"Long"  ,"Float"  ,"Double"  ,"CVoid"  ,"CShort"  ,"CInt"  ,"CLong"  ,"CFloat"  ,"CDouble"  ,
   "RVoid" ,"RShort" ,"RInt" ,"RLong" ,"RFloat" ,"RDouble" ,"CRVoid" ,"CRShort" ,"CRInt" ,"CRLong" ,"CRFloat" ,"CRDouble" ,
   "SVoid" ,"SShort" ,"SInt" ,"SLong" ,"SFloat" ,"SDouble" ,"SCVoid" ,"SCShort" ,"SCInt" ,"SCLong" ,"SCFloat" ,"SCDouble" ,
   "SRVoid","SRShort","SRInt","SRLong","SRFloat","SRDouble","SCRVoid","SCRShort","SCRInt","SCRLong","SCRFloat","SCRDouble"
   };
   if (type == btUnknown) return "Unknown";
   if (type == btLogical) return "Logical";
   return title[Index(type)];
}


static int statement_count = 0;
TNodeStatements::TNodeStatements() :T_NodeList(), TBlock(tbStatements), step(++statement_count) {}

static const char* alloc_title[] = { "None   ", "Global ", "Local  ", "Param  ", "Integer", "Number ", "Oper   ", "Label  ", "Command " };
const char* title_alloc(T_Alloc a) { return alloc_title[a]; }


