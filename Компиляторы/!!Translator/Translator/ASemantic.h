#ifndef TRN_ASEMANTIC_H
#define TRN_ASEMANTIC_H

#include "RSyntax.h"

class TSemantic;
class ASemantic;

// --------------------------- Tables ---------------------------
class TIdentTable : public TNode, public std::vector<TNodeDefVar*> {
public:
   TIdentTable(ASemantic *s) : semantic(s) {}
public:
   TNodeDefVar* find(const T_Lexeme &l) const;
   void Add(TNodeDefVar* var);
   void DelBack();
public:
   void print(TPrinter& printer) const;
protected:
   ASemantic *semantic;
};

class TBlockTable : public TNode, public std::vector<TBlock*> {
public:
   TBlockTable(ASemantic *s) : semantic(s) {}
public:
   void Add(TBlock* block);
   TBlock* Block(T_Block type = T_Block::tbNone) const;
   TNodeLabel* BreakContinueLabel(T_Block type) const;
public:
   void print(TPrinter& printer) const;
protected:
   ASemantic *semantic;
};

class ASemantic {
public:
   ASemantic(TSemantic* t) :semantic(t) {}
public:
   virtual bool Search(TFinder& finder) { return false; }
   virtual int  AddDefVar(TNodeDefVar* var) { return 0; }
   virtual TNodeDefVar* GetDefVar() { return NULL; }
   virtual TNodeDefVar* FindIdent(const T_Lexeme &l) const { return NULL; }
public:
   virtual TBlock* Block(T_Block type = T_Block::tbNone) const { return NULL; }
   TNodeLabel*  BreakContinueLabel(T_Block type) const { return NULL; }
   virtual void BreakContinueLabel(TNodeLabel* label_break, TNodeLabel* label_continue) {}
   virtual void BlockBegin(TBlock* block) {}
   virtual void BlockTrunc(int trunc) {}
   virtual void BlockEnd(TNode *node, bool del = false) {}
   virtual int  BlockSize() const { return 0; }
public:
   virtual bool FindLabel(TNodeBreakContinue &goto_node) = 0;
   virtual void MakeGoToLabel(T_UserGoToLabel* item) {}
public:
   void AddError(TNode* node, T_Error error = T_Error::erNone);
   virtual void print(TPrinter& printer) const {}
   virtual void Count(int& blocks, int& idents) const { blocks = 0; idents = 0; }
public:
   TSemantic* semantic;
};

class BlockSemantic : public ASemantic  {
public:
   BlockSemantic(TSemantic* t) :ASemantic(t), BlockTable(this), IdentTable(this) {}
public:
   virtual bool Search(TFinder& finder);
   virtual int  AddDefVar(TNodeDefVar* var);
   virtual TNodeDefVar* GetDefVar();
   virtual TNodeDefVar* FindIdent(const T_Lexeme &l) const;
public:
   virtual TBlock* Block(T_Block type = T_Block::tbNone) const { return BlockTable.Block(type); }
   TNodeLabel*  BreakContinueLabel(T_Block type) const { return BlockTable.BreakContinueLabel(type); }
   virtual void BreakContinueLabel(TNodeLabel* label_break, TNodeLabel* label_continue);
   virtual void BlockBegin(TBlock* block);
   virtual void BlockTrunc(int trunc);
   virtual void BlockEnd(TNode *node, bool del = false);
   virtual int  BlockSize() const;
public:
   virtual bool FindLabel(TNodeBreakContinue &goto_node);
   virtual void MakeGoToLabel(T_UserGoToLabel* item);
public:
   virtual void print(TPrinter& printer) const;
   virtual void Count(int& blocks, int& idents) const;
protected:
   T_Alloc Alloc() const;
public:
   TIdentTable IdentTable;
   TBlockTable BlockTable;
};

class TreeSemantic : public ASemantic {
public:
   TreeSemantic(TSemantic* t) :ASemantic(t) {}
public:
   virtual bool Search(TFinder& finder);
   virtual int  AddDefVar(TNodeDefVar* var);
public:
   virtual void BlockBegin(TBlock* block);
   virtual void BlockEnd(TNode *node, bool del = false);
public:
   virtual bool FindLabel(TNodeBreakContinue &goto_node);
   virtual void MakeGoToLabel(T_UserGoToLabel* item);
public:
};

class StackSemantic : public ASemantic {
public:
   StackSemantic(TSemantic* t, TStackRule* s) :ASemantic(t), stack(s) {}
public:
   virtual bool Search(TFinder& finder);
public:
   virtual bool FindLabel(TNodeBreakContinue &goto_node);
public:
   TStackRule* stack;
};

#endif
