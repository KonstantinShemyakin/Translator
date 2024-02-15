#ifndef TRN_C_GRAMMAR_H
#define TRN_C_GRAMMAR_H

#include "Parse.h"
#include "ASyntax.h"

// --------------------------- C_GrammarSyntax ---------------------------

class C_GrammarIdentTable {
public:
   enum T_Block { None, Global, Func, Param, List, Struct, Enumer };
public:
   C_GrammarIdentTable(T_Block t = T_Block::None) :type_name(false) { type = t; }
   bool Add(const char* name, int type);
   int  Find(const char* name) const;
   bool Copy(const C_GrammarIdentTable& join);
   void Clear() { names.clear(); }
   T_Block Type() { return type; }
   void Type(T_Block t) { type = t; }
public:
   struct Key {
      Key(const char* k) :key(k) {}
      const char* key;
      bool operator == (const Key& k) const { return strcmp(key,k.key) == 0; }
      bool operator <  (const Key& k) const { return strcmp(key,k.key) <  0; }
   };
   class TNameIndex : public std::map<const Key, const int> {
   } names;
public:
   bool Typedef() const { return type_name; }
   void Typedef(bool x) { type_name = x; }
protected:
   T_Block type;
   bool type_name;
};

class C_GrammarBlockTable {
public:
   C_GrammarBlockTable() {}
   bool Add(const char* name, int type) { return blocks.back().Add(name, type); }
   int  Find(const char* name) const;
   void Push(C_GrammarIdentTable::T_Block t = C_GrammarIdentTable::T_Block::None) { blocks.push_back(C_GrammarIdentTable(t)); }
   void PushParam() { blocks.push_back(ParamIdentTable); ClearParam(); }
   void Pop();
   void Down(); 
   void SaveParam(); 
   void ClearParam() { ParamIdentTable.Clear(); } 
public:
   std::vector<C_GrammarIdentTable> blocks;
public:
   C_GrammarIdentTable ParamIdentTable;
};

class C_Grammar_Syntax 
{
public:
   enum T_Terminal_Mask { qualifier = 0x01, specifier = 0x02, storage = 0x04, pointer = 0x08, declarator = 0x10 };
public:
   C_Grammar_Syntax(A_Syntax* s) : syntax(s) {}
   void UpdateLexeme(T_Lexeme &l);
   bool Command(int command);
   int  IdentType(const T_Lexeme& l) const;
   int  IdentType() const { return IdentType(current_lexeme); }
   bool AddIdentType(const T_Lexeme& l, int type);
   bool AddIdentType(int type) { return AddIdentType(current_lexeme, type); }
public:
   virtual bool VerifyAction(const GSymbol& current_sym) { return false; }
   bool Typedef() const { return blocks.blocks.back().Typedef(); }
   void Typedef(bool x) { blocks.blocks.back().Typedef(x); }
public:
   C_GrammarBlockTable blocks;
   T_Lexeme current_lexeme;
public:
   A_Syntax* syntax;
};

#endif