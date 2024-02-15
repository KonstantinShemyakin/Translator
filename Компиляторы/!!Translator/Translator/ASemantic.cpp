#include "stdafx.h"

#include "TSemantic.h"

// --------------------------- TBlock---------------------------
void TBlock::BlockBegin(TSemantic& semantic)
{
   number = semantic.block_number++;
   semantic.BlockBegin(this);
}

void TBlock::BlockEnd(TSemantic& semantic, bool del)
{
   TNode* node = dynamic_cast<TNode*> (this);
   semantic.BlockEnd(node, del);
}

bool TBlock::LabelDelVar(TNodeLabel* &label, int &del, int rate) const
{
   if ((type != T_Block::tbFor) || (rate != T_Block::tbContinue)) {
      del += size;
   }
   if (type & rate) {
      if (rate == tbBreak) {
         label = break_label;
      } else if (rate == tbContinue) {
         label = continue_label;
      }
      return true;
   }
   return false;
}

void TBlock::BreakContinueLabel(TNodeLabel* label_break, TNodeLabel* label_continue)
{
   break_label = label_break; continue_label = label_continue;
}

void TBlock::print(TPrinter& printer) const
{
   PRINTER_FILE_MODE
   fprintf(file, " number=%d, size=%d", number, size);
}

#undef ACTION
#define ACTION(MODE) ((semantic->semantic->syntax->option_mode & 0x0000000F) == A_Syntax::mm##MODE)

// --------------------------- Tables ---------------------------
TNodeDefVar* TIdentTable::find(const T_Lexeme &l) const
{
   for (const_reverse_iterator r = rbegin(); r < rend(); r++) {
      if (semantic->semantic->Compare((*r)->Lexeme(), l)) return (*r);
   }
   return NULL;
}

void TIdentTable::Add(TNodeDefVar* var)
{
   if (var->alloc == T_Alloc::taGlobal) {
      var->offset = (int)size();
   } else if (var->alloc == T_Alloc::taParam) {
      const TBlock* block = ((BlockSemantic*)semantic)->BlockTable.Block();
      var->offset = block->size;
   } else if (var->alloc == T_Alloc::taLocal) {
      int offset = 0;
      if (!empty()) {
         TNodeDefVar* def = back();
         if ((def->alloc != T_Alloc::taGlobal) && (def->alloc != T_Alloc::taParam)) {
            offset = def->offset + 1;
         }
      }
      var->offset = offset;
   }
   push_back(var);
   if (var->Owner() == NULL) {
      int i = 0;
   }
   if (ACTION(Code)) var->SetOwner(this);
}

void TIdentTable::DelBack()
{
   if (back()->Owner() == this) {
      back()->clear(); delete back();
   }
   pop_back();
}

void TIdentTable::print(TPrinter& printer) const
{
   printf("\n--- IdentTable ---- %d ----\n", (int)size());
   for (const TNodeDefVar* var : (*this)) { var->print(0, printer); }
}

void TBlockTable::Add(TBlock* block)
{
   TNode *node = dynamic_cast<TNode*>(block);
   if (node && (ACTION(Code) && (block->type != T_Block::tbFunc))) {
      node->SetOwner(this);
   }
   push_back(block);
}

TNodeLabel* TBlockTable::BreakContinueLabel(T_Block type) const
{
   TNodeLabel* label = NULL;
   for (const_reverse_iterator r = rbegin(); r < rend(); r++) {
      const TBlock* block = (*r);
      if (type == tbBreak) {
         label = block->break_label;
      } else if (type == tbContinue) {
         label = block->continue_label;
      }
      if (label) return label;
   }
   return label;
}

TBlock* TBlockTable::Block(T_Block type) const
{
   if (empty()) return NULL;
   if (type == T_Block::tbNone) return back();
   for (const_reverse_iterator r = rbegin(); r < rend(); r++) {
      TBlock* block = (*r);
      if ((type < tbBlock) && (block->type & type) || (block->type == type)) return block;
   }
   return NULL;
}

void TBlockTable::print(TPrinter& printer) const
{
   printf("\n--- BlockTable ---- %d ----\n", (int)size());
   for (const TBlock* block : (*this)) { block->print(printer); }
}

// --------------------------- ASemantic ---------------------------
void ASemantic::AddError(TNode* node, T_Error error)
{ 
   return semantic->AddError(node, error);
}

#undef ACTION
#define ACTION(MODE) ((semantic->syntax->option_mode & 0x0000000F) == A_Syntax::mm##MODE)

// --------------------------- BlockSemantic ---------------------------
bool BlockSemantic::Search(TFinder& finder)
{
   if (finder.mode == TFinder::mfVar) {
      finder.result = IdentTable.find(*finder.lexeme);
   } else if (finder.mode == TFinder::mfFunctionType) {
      TNodeDefFunc* func = NULL;
      func = dynamic_cast<TNodeDefFunc*> (BlockTable.Block(T_Block::tbFunc));
      finder.result = func->Left();
   }
   return finder.result != NULL;
}

T_Alloc BlockSemantic::Alloc() const
{
   if (BlockTable.size() == 1) return T_Alloc::taGlobal;
   const TBlock* block = BlockTable.Block();
   if (block->type == tbFunc) return T_Alloc::taParam;
   return T_Alloc::taLocal;
}

int BlockSemantic::AddDefVar(TNodeDefVar* var)
{
   TBlock* block = BlockTable.Block();
   if (!block) {
      return 0;
   }
   var->alloc = Alloc();
   const T_Lexeme& lexeme = var->Lexeme();
   if (lexeme.len) {
      TNodeDefVar* old = IdentTable.find(lexeme);
      if (old && (old->alloc == var->alloc) && (old->offset >= block->offset)) {
         AddError(var, erDuplicateIdent);
      }
   }
   IdentTable.Add(var);
   block->size++;
   return 0;
}

TNodeDefVar* BlockSemantic::GetDefVar()
{
   return (IdentTable.empty()) ? NULL : IdentTable.back();
}

TNodeDefVar* BlockSemantic::FindIdent(const T_Lexeme &l) const 
{ 
   return IdentTable.find(l);
}

void BlockSemantic::BlockBegin(TBlock* block)
{
   block->size = 0;
   block->offset = (int)IdentTable.size();
   BlockTable.Add(block);
   if (ACTION(Code)) {
      TNode *node_block = dynamic_cast<TNode*>(block);
      TNodeDefFunc* func = dynamic_cast<TNodeDefFunc*>(node_block);
      if (func) {
         semantic->function = func;
      }
   }
}

int  BlockSemantic::BlockSize() const
{
   if (!BlockTable.size()) return 0;
   const TBlock* block = BlockTable.Block();
   return block->size;
}

void BlockSemantic::BlockTrunc(int trunc)
{
   TBlock* block = BlockTable.Block();
   while (trunc > block->size) {
      IdentTable.DelBack(); block->size--;
   }
}

void BlockSemantic::BlockEnd(TNode *node, bool del)
{
   TBlock* block = BlockTable.back();
   while ((int)IdentTable.size() > block->offset) {
      IdentTable.DelBack();
   }
   if ((block->size) && (block->type != T_Block::tbFunc)) {
      if (node) {
         TNodeDel* del_pop = new TNodeDel();
         del_pop->count = block->size;
         node->InsertAfter(del_pop);
      } else if (del) {
         semantic->GenPop(block->size);
      }
   }
   if (ACTION(Code)) {
      TNode *node_block = dynamic_cast<TNode*>(block);
      TNodeDefFunc* func = dynamic_cast<TNodeDefFunc*>(node_block);
      if (node_block && !func) {
         delete node_block;
      }
      if (func) {
         if (semantic->syntax->option & T_OptionMode::omEraseCode) semantic->Code().Erase(true);
         semantic->Code().Gotos();
         semantic->Code().Labels(true);
         semantic->function = NULL;
      }
   }
   BlockTable.pop_back();
}

void BlockSemantic::BreakContinueLabel(TNodeLabel* label_break, TNodeLabel* label_continue)
{
   BlockTable.back()->BreakContinueLabel(label_break, label_continue);
}

bool BlockSemantic::FindLabel(TNodeBreakContinue &goto_node)
{
   int del = 0;
   TNodeLabel* label = NULL;
   for (TBlockTable::const_reverse_iterator r = BlockTable.rbegin(); r < BlockTable.rend(); r++) {
      const TBlock* block = (*r);
      if (block->LabelDelVar(label, del, goto_node.rate)) break;
   }
   if (label) {
      goto_node.SetLabel(label);
      goto_node.del_count = del;
      return true;
   } else {
      AddError(&goto_node, (goto_node.rate == T_Block::tbBreak) ? erBreak : erContinue);
      return false;
   }
}

void BlockSemantic::MakeGoToLabel(T_UserGoToLabel* item)
{
   bool yes_local = false;
   item->clear();
   for (const TBlock *block : BlockTable) {
      if (yes_local) {
         item->push_back(T_UserGoToItem(block->number, block->size));
      }
      if (block->type == tbFunc) yes_local = true;
   }
}

void BlockSemantic::print(TPrinter& printer) const
{
   if (BlockTable.size()) BlockTable.print(printer);
   if (IdentTable.size()) IdentTable.print(printer);
}

void BlockSemantic::Count(int& blocks, int& idents) const
{
   blocks = (int)BlockTable.size(); idents = (int)IdentTable.size();
}

// --------------------------- TreeSemantic ---------------------------
bool TreeSemantic::Search(TFinder& finder)
{
   if (finder.mode == TFinder::mfVar) {
      finder.place->Search(finder);
   } else if (finder.mode == TFinder::mfFunctionType) {
      TNodeDefFunc* func = NULL;
      finder.mode = TFinder::mfFunction;
      if (finder.place->Search(finder)) {
         func = (TNodeDefFunc*)finder.result;
         finder.result = func->Left();
      }
   }
   return finder.result != NULL;
}

int  TreeSemantic::AddDefVar(TNodeDefVar* var)
{
   TFinder finder(*semantic, TFinder::mfDuplicateSearch); finder.lexeme = &var->Lexeme();
   if (Search(finder)) {
      AddError(var, erDuplicateIdent);
   }

   TNode* node = var->Owner();
   while (node) {
      TBlock* block = dynamic_cast<TBlock*> (node);
      if (block) {
         var->offset = block->offset + block->size;
         block->size++;
         break;
      }
      node = node->Owner();
   }
   return 0;
}

void TreeSemantic::BlockBegin(TBlock* block)
{
   if (block->type != T_Block::tbFunc) {
      TNode *node = dynamic_cast<TNode*> (block);
      TBlock *owner_block = dynamic_cast<TBlock*> (node->Owner());
      if (owner_block && (owner_block->type != T_Block::tbFunc)) {
         block->offset = owner_block->offset + owner_block->size;
      }
   }
}

void TreeSemantic::BlockEnd(TNode *node, bool del)
{
   TBlock *block = dynamic_cast<TBlock*> (node);
   if (block && block->size && (block->type != T_Block::tbFunc)) {
      TNodeDel* del_pop = new TNodeDel();
      del_pop->count = block->size;
      node->InsertAfter(del_pop);
   }
}

bool TreeSemantic::FindLabel(TNodeBreakContinue &goto_node)
{
   int del = 0;
   TNodeLabel* label = NULL;
   TNode* node = &goto_node;
   while (node) {
      const TBlock* block = dynamic_cast<const TBlock*> (node);
      if (block && (block->LabelDelVar(label, del, goto_node.rate))) break;
      node = node->Owner();
   }
   if (label) {
      goto_node.SetLabel(label);
      goto_node.del_count = del;
      return true;
   } else {
      AddError(&goto_node, (goto_node.rate == T_Block::tbBreak) ? erBreak : erContinue);
      return false;
   }
}

void TreeSemantic::MakeGoToLabel(T_UserGoToLabel* item)
{
   TNode* node = dynamic_cast<TNode*> (item);
   while (node) {
      const TBlock* block = dynamic_cast<TBlock*> (node);
      if (block) {
         if (block->type == tbFunc) break;
         item->insert(item->begin(), T_UserGoToItem(block->number, block->size));
      }
      node = node->Owner();
   }
}

// --------------------------- StackSemantic ---------------------------
bool StackSemantic::Search(TFinder& finder)
{
   if (finder.mode == TFinder::mfVar) {
      finder.is_stack = true;
      semantic->mode = (TSemantic::T_Mode)(semantic->mode & ~TSemantic::tmStack | TSemantic::tmTree);
      for (int index = stack->filled() - 1; index >= 0; index--) {
         TStackRuleItem& stack_item = stack->stack_item(index);
         if (stack_item.lexeme_node.tree) {
            finder.Reset(finder.mode);
            finder.place = stack_item.lexeme_node.tree;
            finder.place->SearchInside(finder);
            if (finder.result) {
               break;
            }
         }
      }
      semantic->mode = (TSemantic::T_Mode)(semantic->mode & ~TSemantic::tmTree | TSemantic::tmStack);
   } else if (finder.mode == TFinder::mfFunctionType) {
      TNodeDefFunc* func = NULL;
      for (int index = 0; index < stack->filled(); index++) {
         TStackRuleItem& stack_item = stack->stack_item(index);
         TNodeDefFunc* func_item = dynamic_cast<TNodeDefFunc*> (stack_item.lexeme_node.tree);
         if (func_item) {
            func = func_item;
            finder.result = func->Left();
            break;
         }
      }
   }
   return finder.result != NULL;
}

bool StackSemantic::FindLabel(TNodeBreakContinue &goto_node)
{
   int del = 0;
   TNodeLabel* label = NULL;
   for (int index = stack->filled() - 1; index >= 0; index--) {
      TStackRuleItem& stack_item = stack->stack_item(index);
      const TBlock* block = dynamic_cast<const TBlock*> (stack_item.lexeme_node.tree);
      if (block && (block->LabelDelVar(label, del, goto_node.rate))) break;
   }
   if (label) {
      goto_node.SetLabel(label);
      goto_node.del_count = del;
      return true;
   } else {
      AddError(&goto_node, (goto_node.rate == T_Block::tbBreak) ? erBreak : erContinue);
      return false;
   }
}

