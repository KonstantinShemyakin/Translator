#ifndef TRN_MAKER_H
#define TRN_MAKER_H

#include "Parse.h"
#include "RSyntax.h"
#include "CSyntax.h"
#include "SNodes.h"
 
class GSyntax;

// --------------------------- GMaker ---------------------------
class GMaker
{
public:
   GMaker(const char* t, GMakerTable* table);
   GMaker(bool (*f)(const GSymbol&, M_Syntax*), const char* t, GMakerTable* table);
//   GMaker(bool (*f)(const GSymbol&, M_Syntax*), const char* t);
   GMaker(bool (*f)(const GSymbol&, MC_Syntax*, TSemantic*), const char* t, GMakerTable* table);
   GMaker(bool (*y)(const GSymbol&, M_Syntax*, T_Lexeme_SNode*[]), const char* t, GMakerTable* table);
public:
   bool (*make_tree)(const GSymbol& item, M_Syntax* syntax);
   bool (*make_code)(const GSymbol& item, MC_Syntax* syntax, TSemantic* semantic);
   bool (*make_yacc)(const GSymbol& item, M_Syntax* syntax, T_Lexeme_SNode* data_stack[]);
public:
   const char* title;
   void print(TPrinter& printer) const;
public:
   mutable int used;
};

class GMakerTable : public std::vector<GMaker*>
{
public:
   GMakerTable() :maker_node(-1), maker_turn(-1), maker_call(-1) {}
   ~GMakerTable();
public:
   void Add(GMaker& m);
   int  Find(const char* k) const;
   int  count() const { return (int)size(); }
   void print(TPrinter& printer) const;
   void YACC(TPrinter& printer) const;
   void Clear();
protected:
   struct Key {
      Key(const char* k) :key(k) {}
      const char* key;
      bool operator == (const Key& k) const { return strcmp(key,k.key) == 0; }
      bool operator <  (const Key& k) const { return strcmp(key,k.key) <  0; }
   };
   class TMakerIndex : public std::map<const Key, int> {
   } indexs;
public:
   int maker_node, maker_turn, maker_call;
public:
   static GMakerTable maker_table;
};

#define SYNTREE_SHIFT 6 
#define SYNTREE_MASK  0x3F 

void tree_syn(int s, int &s1, int &s2, int &s3, int &s4, int &s5); 

#endif

