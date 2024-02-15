#include "stdafx.h"

#include "Rules.h"
#include "CGrammar.h"

int C_GrammarIdentTable::Find(const char* name) const
{
   TNameIndex::const_iterator ip = names.find(name); 
   if (ip != names.end()) {
      const std::pair<const Key, const int> item = (*ip);
      return item.second;
   } else {
      return 0;
   }
}

bool C_GrammarIdentTable::Add(const char* name, int type)
{
   TNameIndex::const_iterator ip = names.find(name); 
   if (ip != names.end()) {
      return false;
   } else {
      const std::pair<const Key, const int> item(name,type);
      names.insert(item); 
      return true;
   }
}

bool C_GrammarIdentTable::Copy(const C_GrammarIdentTable& join)
{
   int ret = 0;
   for (std::pair<const Key, const int> item : join.names) {
      if (!Add(item.first.key, item.second)) ret++;
   }
   return !ret;
}

int C_GrammarBlockTable::Find(const char* name) const
{
   int sign = -1;
   for (int i = (int)blocks.size() -1 ; i >= 0; i--) {
      int type = blocks[i].Find(name);
      if (type) return sign * type; 
      sign = 1;
   }
   return 0;
}

void C_GrammarBlockTable::Down()
{
   int master = (int)blocks.size() - 2 ;
   blocks[master].Copy(blocks.back());
}

void C_GrammarBlockTable::Pop()
{
/*
   for (const std::pair<const C_GrammarIdentTable::Key, const int> item : blocks.back().names) {
      printf("\n%d %s", item.second, item.first.key);
   }
   printf("\n");
*/
   blocks.pop_back(); 
}

void C_GrammarBlockTable::SaveParam()
{
   ClearParam();
   if ((blocks.size() == 2) && (blocks.back().Type() == C_GrammarIdentTable::T_Block::Param)) {
      ParamIdentTable = blocks.back();
   }
}

enum T_Lex { None, Declare, TypeDef, Comma, Semicolon, DeclComma, DeclSemicolon, ExprSemicolon, StmtSemicolon, 
             BegBlock, EndBlock, BegFunc, EndFunc, 
             StructBeg, StructEnd, EnumBeg, EnumEnd, EnumComma, 
             ParamBeg, ParamEnd, ParamComma, ListBeg, ListEnd, ListComma 
           };

bool C_Grammar_Syntax::Command(int command)
{
   switch (command) {
      case T_Lex::None           : break;
      case T_Lex::Declare        : break;
      case T_Lex::TypeDef        : Typedef(true); break;
      case T_Lex::DeclComma      : blocks.ClearParam(); break;
      case T_Lex::DeclSemicolon  : blocks.ClearParam(); Typedef(false); break;
      case T_Lex::BegBlock       : blocks.Push(C_GrammarIdentTable::T_Block::None); break;
      case T_Lex::EndBlock       : blocks.Pop();  break;
      case T_Lex::BegFunc        : blocks.PushParam(); blocks.Push(C_GrammarIdentTable::T_Block::Func); break;
      case T_Lex::EndFunc        : blocks.Pop();  blocks.Pop(); break;
      case T_Lex::StructBeg      : blocks.Push(C_GrammarIdentTable::T_Block::Struct); break;
      case T_Lex::StructEnd      : blocks.Pop();  break;
      case T_Lex::EnumBeg        : blocks.Push(C_GrammarIdentTable::T_Block::Enumer); break;
      case T_Lex::EnumEnd        : blocks.Down(); blocks.Pop(); break;
      case T_Lex::ParamBeg       : blocks.Push(C_GrammarIdentTable::T_Block::Param); break;
      case T_Lex::ParamEnd       : blocks.SaveParam(); blocks.Pop();  break;
      case T_Lex::ListBeg        : blocks.Push(); break;
      case T_Lex::ListEnd        : blocks.Pop();  break;
   }
//   printf("\nLevel %d Ident %d Typedef %d ",(int)blocks.blocks.size(),(int)blocks.blocks.back().names.size(),(int)Typedef()); 
   return true;
}

void C_Grammar_Syntax::UpdateLexeme(T_Lexeme &current_lexeme)
{
   if (current_lexeme.Match(T_Lexeme::grNumber)) {
      current_lexeme.group = T_Lexeme::grInteger;
   } else if (current_lexeme.Match(T_Lexeme::grString)) {
      current_lexeme.group = T_Lexeme::grInteger;
   } else if (current_lexeme.Match(T_Lexeme::grIdent)) {
      GSymbol ident(GSymbol::gsTerminal,T_Lexeme::grIdent,3); // Enumerator
      if (VerifyAction(ident)) {
         current_lexeme.type = 3; // ENUMERATOR
         AddIdentType(0x03); 
      } else {
         ident.lexeme_type = 2; // DECLARATOR
         bool declarator = VerifyAction(ident);
         ident.lexeme_type = 0; // IDENTIFIER
         bool identifier = VerifyAction(ident);
         if (declarator && !identifier) {
            current_lexeme.type = 2; // DECLARATOR
            if (Typedef()) {
               AddIdentType(0x01); // typedef_declarator 
            } else {
               AddIdentType(0x02); // declarator 
            }
         } else {
            if (abs(IdentType()) == 0x01) { // typedef
               current_lexeme.type = 1; // TYPE_NAME
            }
         }
      }
   }
//   printf("\nlevel %d ident %d typedef %d ",(int)blocks.blocks.size(),(int)blocks.blocks.back().names.size(),(int)Typedef()); 
}

int  C_Grammar_Syntax::IdentType(const T_Lexeme& l) const
{
   const char* text = syntax->Scan().Text(l);
   return text ? blocks.Find(text) : 0;
}

bool C_Grammar_Syntax::AddIdentType(const T_Lexeme& l, int type)
{
   bool add = false;
   const char* text = syntax->Scan().Text(l);
   if (text) {
      add = blocks.Add(text,type);
      if (!add) {
         syntax->error(T_Error::erDuplicateIdent);
      }
   }
   return add;
}
