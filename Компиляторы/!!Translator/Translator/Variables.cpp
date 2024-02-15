// Parse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TSemantic.h"

// --------------------------- Variables ---------------------------

#define VARIABLES(NODE) if (NODE && (!SEMANTIC_MODE(Phase, TwoPhase) || (NODE->passport & T_Step::tsChildren))) if (int my_mode = NODE->Passport(mode)) NODE->Variables(semantic, my_mode);
#define IMPOSSIBLE  semantic.impossible(this);

#define BLOCK_BEG  BlockBegin(semantic);
#define BLOCK_END  BlockEnd(semantic);

#define STEP_IF(STEP)   if (mode & T_Step::ts##STEP) {
#define STEP_ELSE(STEP) } if (mode & T_Step::ts##STEP) {
#define STEP_END        }

void TNode::After(TSemantic &semantic, int mode)
{
   if (after) {
      after->Codes(semantic, mode);
      after->After(semantic, mode & ~T_VerifyMode::mvOnAfter);
   }
}
void TNode::Before(TSemantic &semantic, int &mode)
{
   if (mode & T_VerifyMode::mvOffBefore) { mode &= ~T_VerifyMode::mvOffBefore; return; }
   if (before) {
      before->Before(semantic, mode);
      before->Codes(semantic, mode | T_VerifyMode::mvOffBefore);
   }
}

void TNodeNull::Codes(TSemantic &semantic, int mode)
{  
   IMPOSSIBLE
   Before(semantic, mode);
   After(semantic, mode);
}

void T_NodeList::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   for (TNode *node : (*this)) {
      if (int my_mode = node->Passport(mode)) node->Variables(semantic, my_mode);
//      VARIABLES(node)
   }
}
void T_NodeList::Codes(TSemantic &semantic, int mode)
{
//   IMPOSSIBLE
   Before(semantic, mode);
   for (TNode *node : (*this)) {
      if (node) node->Codes(semantic, mode);
   }
   After(semantic, mode);
}
void T_NodeList::Verify(TSemantic &semantic, int mode)
{
	for (TNode *node : (*this)) {
      if (node) node->Verify(semantic, mode);
   }
}

void TNodeExpressions::Codes(TSemantic &semantic, int mode)
{
//   IMPOSSIBLE
   Before(semantic, mode);
	iterator p = begin(); 
   while (p != end()) {
      TNode *item = (*p); p++; 
      bool last = (p == end()), condition = last && (part & psIfGoTo), value = (part & psValueList) || last && (part & psValue);
      bool pop = !last && !value || last && part && !(value || condition);
      TNodeLogical* logic = item->Logical();
      if (logic) {
         if (pop) 
            logic->logical = -1;
         else if (value) 
            logic->logical = 0;
         else if (condition) 
            logic->logical = 1;
      }
      item->Codes(semantic, mode);
      if (semantic.IsQuad()) {
         if (last && !(part & psValueList)) {
            quad = item->quad;
         }
      } else {
         if (pop && !logic) {
            T_BaseType item_type = item->BaseType();
            if ((item_type != btUnknown) && (item_type != btVoid)) {
               semantic.GenPop(1);
            }
         }
      }
   }
   After(semantic, mode);
}

TNodeLogical* TNodeExpressions::Logical()
{
   return !empty() ? Last()->Logical() : NULL;
}

void TNodeUnary::Variables(TSemantic &semantic, int mode)
{  
   VEntry entry(&semantic,this);
   if (child) {
      TNodeLogical* logical = child->Logical();
      bool logic = (logical && lexeme.Match(T_Symbol::lxNot));
      if (logic) {
	      base_type = btCInt;
         logical->logical = 1;
         if (SEMANTIC_MODE(Phase, TwoPhase)) {
            TNodeLabel *label = logical->true_label; logical->true_label = logical->false_label; logical->false_label = label;
         }
	   }
      child->Variables(semantic, mode);
//		VARIABLES(child); 
      if (!logic) {
         T_BaseType type = (logical) ? btCInt : child->BaseType(); 
         profile = semantic.Oper(lexeme, type);
	   	if (profile) {
	   		base_type = profile->result;
            if (profile) semantic.GenCastable(child, (*profile)[0], 0x01);
         } else {
            semantic.AddError(this,erUnknownOper);
	   	}
      }
	}
}
void TNodeUnary::Codes(TSemantic &semantic, int mode)
{  
   IMPOSSIBLE
   Before(semantic, mode);
   if (child) child->Codes(semantic, mode); 
   TNodeLogical* logical = Logical();
   if (!logical) {
      if (semantic.IsQuad()) {
         TQuadruple* quadruple = new TQuadruple(TQuadruple::qtUnary, this);
         quadruple->oper = Oper();
         quadruple->arg_one = child->quad;
         semantic.AddQuad(quadruple);
         quad = quadruple->value_number;
      } else {
         semantic.GenCommand(T_Command::command_Oper, Oper(), 0, BaseType());
      }
   }
   After(semantic, mode);
}
T_Symbol::T_Type TNodeUnary::Oper() const 
{ 
   if (profile) return profile->oper; return T_Symbol::T_Type::lxNone; 
}

TNodeLogical* TNodeUnary::Logical()
{
	return (child && lexeme.Match(T_Symbol::lxNot)) ? child->Logical() : NULL;
}

void TNodeBinary::Variables(TSemantic &semantic, int mode)
{  
   VEntry entry(&semantic,this);
   VARIABLES(left); 
   VARIABLES(right); 
	if (!left || !right) return;
   T_BaseType left_type = left->BaseType();
   if (mode_oper & 0x01) { // initialization
      left_type = TBaseType::Tilda(left_type,T_BaseType::btConst);
   }
   profile = semantic.Oper(lexeme, left_type, right->BaseType());
	if (profile && (profile->size() == 2)) {
		base_type = profile->result;
      semantic.GenCastable(left, (*profile)[0], 0x01 | ((mode_oper & 0x01) ? 0x02 : 0x00));
      semantic.GenCastable(right, (*profile)[1], 0x01);
   } else {
      profile = NULL;
      semantic.AddError(this,erUnknownOper);
	}
}
void TNodeBinary::Codes(TSemantic &semantic, int mode)
{  
   IMPOSSIBLE
   Before(semantic, mode);
   if (left) left->Codes(semantic, mode);

   if (right) right->Codes(semantic, mode);
   if (semantic.IsQuad()) {
      TQuadruple* quadruple = new TQuadruple(TQuadruple::qtBinary, this);
      quadruple->oper = Oper();
      quadruple->arg_one = left->quad;
      quadruple->arg_two = right->quad;
      semantic.AddQuad(quadruple);
      quad = quadruple->value_number;
   } else {
      semantic.GenCommand(T_Command::command_Oper,Oper(),0,BaseType());
   }
   After(semantic, mode);
}
T_Symbol::T_Type TNodeBinary::Oper() const 
{ 
   if (profile) return profile->oper; return T_Symbol::T_Type::lxNone; 
}

void TNodeTrio::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   VARIABLES(left);  // condition
   VARIABLES(mid);   // then
   VARIABLES(right); // else
   base_type = CastableBetween(mid->BaseType(),right->BaseType());
	if (base_type == btUnknown) {
      semantic.AddError(this,erUnknownCast);
   }
   TNodeLabel *true_label, *false_label, *label_end = new TNodeLabel(&semantic);
   semantic.MakeLogical(left, true_label, false_label);
   mid->InsertBefore(true_label);
   semantic.GenCastable(mid, base_type);
   TNodeGoTo* go_end = new TNodeGoTo(T_GoTo::tgGoTo,label_end);
   mid->InsertAfter(go_end);
   right->InsertBefore(false_label);
   semantic.GenCastable(right, base_type);
   InsertAfter(label_end);
}

void TNodeTrio::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   left->Codes(semantic, mode);   // condition 
   mid->Codes(semantic, mode);    // then
   TQuadruple* quadruple = NULL;
   if (semantic.IsQuad()) {
      quadruple = new TQuadruple(TQuadruple::qtSet, this);
      semantic.AddQuad(quadruple, -1); // before go_end
      semantic.LastQuad().value_number.number++; // go_end
      quad = quadruple->value_number;
      quadruple->arg_one = quad;
      quadruple->arg_two = mid->quad;
   }
   right->Codes(semantic, mode);  // else
   After(semantic, mode);
   if (semantic.IsQuad()) {
      TQuadruple& label_end = semantic.LastQuad(); // before label_end
      int label_number = label_end.value_number.number;
      semantic.Quad().label_quad[label_number]++;
      quadruple = new TQuadruple(TQuadruple::qtSet, this);
      semantic.AddQuad(quadruple, -1); // before label_end
      quadruple->arg_one = quad;
      quadruple->arg_two = right->quad;
   }
}

void TNodeLogical::Variables(TSemantic &semantic, int mode)
{  
   VEntry entry(&semantic,this);
   VARIABLES(left); 
   VARIABLES(right); 
	bool oper_or = Lexeme().Match(T_Symbol::lxOrOr);
	TNodeLabel* left_true_label, *left_false_label;
   semantic.MakeLogical(left , left_true_label, left_false_label);
   semantic.MakeLogical(right,      true_label,      false_label);
	if (oper_or) {
      semantic.Reference(left_true_label,true_label);
   	right->InsertBefore(left_false_label);
	} else {
      semantic.Reference(left_false_label,false_label);
   	right->InsertBefore(left_true_label);
	}
   if (logical) {
      TNodeLabel *label = true_label; true_label = false_label; false_label = label;
   }
}
void TNodeLogical::Codes(TSemantic &semantic, int mode)
{  
   IMPOSSIBLE
   Before(semantic, mode);
   left->Codes(semantic, mode); 
   right->Codes(semantic, mode);
   if (logical == 0) {
      int made = -1;
      semantic.MakeValue(true_label,false_label,made);
      base_type = btCInt;
   } else if (logical == -1) {
      semantic.AddCode(false_label); semantic.AddCode(true_label);
      base_type = btVoid;
   }
   After(semantic, mode);
}

void TNodePrimary::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   VARIABLES(child); 
}
void TNodePrimary::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   child->Codes(semantic, mode); 
   if (semantic.IsQuad()) {
      quad = child->quad;
   }
   After(semantic, mode);
}

void TNodeCast::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   if (right) {
      VARIABLES(right); 
      cast = semantic.GetCastable(right->BaseType(), BaseType());
		if (cast == T_CastType::Illegal) {
         semantic.AddError(right,erUnknownCast);
      }
   }
}
void TNodeCast::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   if (right) right->Codes(semantic, mode);
   if (semantic.IsQuad()) {
      TQuadruple* quadruple = new TQuadruple(TQuadruple::qtCast, this);
      quadruple->oper = cast;
      quadruple->arg_one = right->quad;
      semantic.AddQuad(quadruple);
      quad = quadruple->value_number;
   } else {
      semantic.GenCommand(T_Command::command_Cast, cast, 0, BaseType());
   }
   After(semantic, mode);
}

void TNodeCall::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   profile = new TFuncProfile(lexeme);
   bool yes_error = false, yes_param = right && !right->IsNull();
   if (yes_param) {
      VARIABLES(right); // params
      T_NodeList *params = (T_NodeList*)right;
      for (TNode *param : (*params)) {
         T_BaseType param_type = param->BaseType();
         if ((param_type == btUnknown) || (param_type == btVoid)) {
            semantic.AddError(this,erUnknownParam);
            yes_error = true;
         }
         profile->Add(param_type);
      }
   }
   if (!yes_error) {
      TFinder finder(semantic,TFinder::mfNone);
      TNodeDefFunc* func = semantic.FindFunc(*profile,finder);
      if (func) {
         SetType(func);
         profile->result = func->profile->result;
         if (yes_param) {
            T_NodeList *params = (T_NodeList*)right;
 	         T_NodeList::iterator p = params->begin(); 
            int i = 0;
            while (p != params->end()) {
               TNode* &param = (*p); p++; 
               semantic.GenCastable(param, (*func->profile)[i++]);
            }
         }
      } else {
         semantic.AddError(this,erUnknownFunc);
      }
   }
}
void TNodeCall::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   if (right) right->Codes(semantic, mode); // params
	int number = -1;
	TNodeDefFunc *type = Type();
	if (type) number = type->number;
   if (semantic.IsQuad()) {
      T_NodeList* params = Params();
      int param_count = 0;
      if (params) {
         param_count = params->Count();
         for (TNode* param : (*params)) {
            TQuadruple* quadruple = new TQuadruple(TQuadruple::qtParam, param);
            quadruple->arg_one = param->quad;
            semantic.AddQuad(quadruple);
         }
      }
      TQuadruple* quadruple = new TQuadruple(TQuadruple::qtCall, this);
      quadruple->oper = number;
      quadruple->param = param_count;
      semantic.AddQuad(quadruple);
   } else {
      semantic.GenCommand(T_Command::command_Call,number,0,BaseType());
   }
   After(semantic, mode);
}

void TNodeVar::Variables(TSemantic &semantic, int mode)
{ 
   VEntry entry(&semantic,this);
   TNodeDefVar *type = NULL; 
   TFinder finder(this, TFinder::mfVar); finder.lexeme = &lexeme;
   semantic.Search(finder);
   type = (TNodeDefVar*)finder.result;
   if (type) {
      SetType(type); 
      quad = type->quad;
   } else {
      semantic.AddError(this,erUnknownIdent);
   }
}
void TNodeVar::Codes(TSemantic &semantic, int mode)
{ 
   IMPOSSIBLE
   Before(semantic, mode);
   TNodeDefVar *def_var = dynamic_cast<TNodeDefVar*>(child);
   if (def_var && !semantic.IsQuad()) {
      semantic.GenCommand(T_Command::command_PushVar,def_var->offset,def_var->alloc,def_var->BaseType()); 
   }
   After(semantic, mode);
}

void TNodeNumber::Variables(TSemantic &semantic, int mode)
{ 
   VEntry entry(&semantic,this);
}
void TNodeNumber::Codes(TSemantic &semantic, int mode)
{ 
   IMPOSSIBLE
   Before(semantic, mode);
   if (semantic.IsQuad()) {
      quad.alloc = (lexeme.group == lexeme.grInteger) ? taInteger : taNumber;
      quad.number = lexeme.value;
   } else {
      semantic.GenNumber(lexeme);
   }
   After(semantic, mode);
}

void TNodeIndex::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   TNodeDefVar* ident = NULL;
   TFinder finder(this, TFinder::mfVar); finder.lexeme = &lexeme;
   semantic.Search(finder);
   ident = (TNodeDefVar*)finder.result;
   if (ident) {
      TNodeDefArr *type = dynamic_cast<TNodeDefArr*> (ident);
      if (type) {
         SetType(type); 
         quad = type->quad;
      } else {
         semantic.AddError(this,erInvalidType);
      }
   } else {
      semantic.AddError(this,erUnknownIdent);
   }
   VARIABLES(right); // range
   for (TNode *&range : (*Ranges())) {
      semantic.GenCastable(range, btCInt, 0x00);
   }
}
void TNodeIndex::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   TNodeDefArr *def_var = dynamic_cast<TNodeDefArr*>(left);
   if (def_var) {
      if (semantic.IsQuad()) {
         TNode *range = (*Ranges())[0];
         range->Codes(semantic, mode);
         TQuadruple* quadruple = new TQuadruple(TQuadruple::qtSet, NULL);
         semantic.AddQuad(quadruple);
         TAddress index = quadruple->value_number;
         quadruple->arg_one = index;
         quadruple->arg_two = range->quad;
         for (int r = 1; r < (int)Ranges()->size(); r++) {
            range = (*Ranges())[r];
            range->Codes(semantic, mode);
            quadruple = new TQuadruple(TQuadruple::qtBinary, NULL);
            quadruple->oper = T_Symbol::lxMultiAssign;
            quadruple->arg_one = index;
            quadruple->arg_two = def_var->quad; quadruple->arg_two.number += r;
            semantic.AddQuad(quadruple);
            quadruple = new TQuadruple(TQuadruple::qtBinary, NULL);
            quadruple->oper = T_Symbol::lxAddAssign;
            quadruple->arg_one = index;
            quadruple->arg_two = range->quad;
            semantic.AddQuad(quadruple);
         }
         quadruple = new TQuadruple(TQuadruple::qtIndex, this);
         semantic.AddQuad(quadruple);
         quad = quadruple->value_number;
         T_CastType result_type = semantic.GetCastable(Owner()->BaseType(), T_BaseType(Owner()->BaseType() | T_BaseType::btReference));
         if (result_type == T_CastType::None) {
            quadruple->arg_one = index;
            quadruple->arg_two = def_var->quad;
            quadruple->result = def_var->quad;
         } else {
            quadruple->arg_one = def_var->quad;
            quadruple->arg_two = index;
            quadruple->result = quad;
         }
      } else {
         if (right) right->Codes(semantic, mode); // range
         semantic.GenCommand(T_Command::command_PushArr, def_var->offset, def_var->alloc, def_var->BaseType());
      }
   }
   After(semantic, mode);
}

// --------------------------- Define ---------------------------

void TNodeDefVar::SetAssign(const T_Lexeme& lexeme, TNode* expr, TSemantic* semantic)
{
   TNodeVar *lvar = new TNodeVar(this->Lexeme());
   TNodeExpressions *expression = new TNodeExpressions(); 
   expression->Add(expr);
   expression->part = psValue;
   TNodeBinary *assign = new TNodeBinary(lexeme, lvar, expression);
   assign->mode_oper = 0x01;// initialization
   TNodeExpressions *expression_assign = new TNodeExpressions();
   expression_assign->Add(assign);
   expression_assign->part = psExpression;
   SetAssign(expression_assign);
   if (semantic && semantic->IsStack()) {
      lvar->SetType(this);
   }
   if (semantic) {
//      lvar->Variables(*semantic, T_Step::tsAll);
//      expression->Variables(*semantic, T_Step::tsAll);
//      assign->Variables(*semantic, T_Step::tsAll);
//      expression_assign->Variables(*semantic, T_Step::tsAll);
      lvar->passport |= T_Step::tsChildren;
      expression->passport |= T_Step::tsChildren;
      assign->passport |= T_Step::tsChildren;
      expression_assign->passport |= T_Step::tsChildren;
   }
}

void TNodeDefVar::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   semantic.AddDefVar(this);

   quad.alloc = alloc; quad.number = offset;
   VARIABLES(right); // assign
}
void TNodeDefVar::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   if (semantic.IsQuad()) {
   } else {
      semantic.GenCommand(T_Command::command_NewVar, offset, alloc, BaseType());
   }
   if (right) right->Codes(semantic, mode); // assign
   After(semantic, mode);
}
void TNodeDefVar::Verify(TSemantic &semantic, int mode)
{
   T_BaseType type = BaseType();
   bool must_initial = (alloc == T_Alloc::taNone) || 
                       (alloc != T_Alloc::taParam) && (type & T_BaseType::btConstReference) ||
                       (alloc == T_Alloc::taParam) && (type & T_BaseType::btReference);
   if (!right && must_initial) {
      semantic.AddError(this,erUninitialized);
   }
}
T_BaseType TNodeDefVar::BaseType() const 
{ 
   if (left) return left->BaseType();
   TNodeDefine* def = dynamic_cast<TNodeDefine*>(owner);
   if (def) {
      TNodeType *define_type = def->Type();
      if (define_type) return define_type->BaseType();
   }
   return btUnknown; 
}

int TDefArrRange::calc()
{
   int volume = 1;
   for (int r = (int)size() - 1; r >= 0; r--) {
      TDefArrRangeItem &item = (*this)[r];
      if (r && (item.range < 1)) return 0;
      volume *= item.range;
      item.volume = volume;
      if (r == ((int)size() - 1)) item.index = -1;
   }
//   printf("\ncalc: level=%d, volume=%d", level, volume);
   return volume;
}

int TDefArrRange::offset() const
{
   int offset_ = 0, volume = 1;
   for (int r = (int)size() - 1; r >= 0; r--) {
      const TDefArrRangeItem &item = (*this)[r];
      offset_ += volume * item.index;
      volume *= item.range;
   }
//   printf("\noffset: level=%d, offset=%d", level, offset_);
   return offset_;
}

bool TDefArrRange::next()
{
//   printf("\nnext: level=%d", level);
   for (int r = (int)size() - 1; r >= 0; r--) {
      TDefArrRangeItem &item = (*this)[r];
      if ((++item.index < item.range) || (!r && (item.range < 0))) return true;
      for (int p = r; p < (int)size(); p++) {
         (*this)[p].index = 0;
      }
   }
   return false;
}

void TDefArrRange::jump(int level)
{
//   printf("\njump: p_level=%d, t_level=%d", level, this->level);
   if (!level) return;
   int r = (int)size() - 1;
   (*this)[r--].index = -1;
   for (; r > level; r--) {
      TDefArrRangeItem &item = (*this)[r];
      item.index = 0;
   }
   for (; r >= 0; r--) {
      TDefArrRangeItem &item = (*this)[r];
      if ((++item.index < item.range) || (!r && (item.range < 0))) break;
      item.index = 0;
   }
}

bool TDefArrRange::variable_range() const
{
   for (int r = 0; r < (int)size(); r++) {
      const TDefArrRangeItem &item = (*this)[r];
      if (item.range < -1) return true;
   }
   return false;
}

bool TNodeDefArr::parse_init(T_NodeList *items, int level)
{
   for (unsigned int item = 0; item < items->size(); item++) {
      T_NodeList *list = dynamic_cast<T_NodeList*> ((*items)[item]);
      if (list) {
         if ((level + 1) >= ranges.count()) return false;
         if (!parse_init(list,level + 1)) return false; 
      } else {
         if (!ranges.next()) return false;
         TDefArrInitItem init(ranges.offset(), (*items)[item]);
         initializer.push_back(init);
      }
   }
   ranges.jump(level);
   return true;
}

void TNodeDefArr::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
STEP_IF(Begin)
   dimension = (int)Range()->size();
   semantic.AddDefVar(this);

   quad.alloc = alloc; quad.number = offset;
STEP_ELSE(DefArrAssign)
   VARIABLES(mid); // range
   bool unknown_range = false, variable_range = false;
   for (TNode *&node : (*Range())) {
      if (ranges.empty() && node->IsNull()) {
         ranges.push_back(-1);
         unknown_range = true;
      } else {
         const TNodeNumber *number = dynamic_cast<const TNodeNumber*>(node);
         if (number && (number->BaseType() == btCInt)) {
            int value = semantic.syntax->Integer(number->Lexeme());
            if (value > 0) {
               ranges.push_back(value);
            } else {
               semantic.AddError(this,erRanges);
            }
         } else {
            ranges.push_back(-2);
            variable_range = true;
            semantic.GenCastable(node, btCInt, 0x00);
         }
      }
   }
   if (right && variable_range) {
      semantic.AddError(this,erInvalidInit);
   }
   if (error()) return;
   ranges.calc();

   if (right) {
      VARIABLES(right); // assign
      T_NodeList* init_list = dynamic_cast<T_NodeList*>(right);
      if (init_list) {
         if (parse_init(init_list, 0)) {
            if (unknown_range) {
               ranges[0].range = ranges[0].index;
               if (ranges.count() == 1) ranges[0].range++;
            }
         } else {
            semantic.AddError(this, erInvalidInit);
         }
      }
      for (unsigned int item = 0; item < initializer.size(); item++) {
         TDefArrInitItem& init = initializer[item];
         if (!semantic.GenCastable(init.value, TBaseType::Const(BaseType()), 0x00)) {
            semantic.AddError(this, erUnknownCast);
         }
      }
   }
   if (unknown_range) {
      TNode *range =  new TNodeCommand(T_Command::command_PushInt,ranges[0].range,0,btCInt); 
      GarbageCollectorAdd((*Range())[0], 0x01);
      (*Range())[0] = range;
   }
STEP_END
}
void TNodeDefArr::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   Range()->Codes(semantic, mode); // range
   int count = ranges.count();
   semantic.GenCommand(T_Command::command_NewArr,count,alloc,BaseType()); 
   if (right) { // assign
      for (unsigned int item = 0; item < initializer.size(); item++) {
         TDefArrInitItem& init = initializer[item];
         init.value->Codes(semantic, mode);
         semantic.GenCommand(T_Command::command_PushInt,init.offset,0,btCInt);
         semantic.GenCommand(T_Command::command_InitArr,offset,alloc,BaseType()); 
      }
   }
   After(semantic, mode);
}

void TNodeDefFunc::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
STEP_IF(Begin)
   semantic.function = this;
   BLOCK_BEG;
STEP_ELSE(Param)
   profile = new TFuncProfile(Lexeme());
   profile->result = left->BaseType();
   if (right && !right->IsNull()) {
      VARIABLES(right); // params
      for (TNode *node : (*right)) {
         TNodeDefVar *param = (TNodeDefVar*)node;
         profile->Add(param->BaseType());
      }
   }
   semantic.AddDefFunc(this);
STEP_ELSE(Body)
   if (mid) {
      VARIABLES(mid); // body
   
      if (true/*semantic.IsBlock() || semantic.IsTree() && SEMANTIC_MODE(Phase, TwoPhase)*/) {
         semantic.UserGoToTable.Verify();
         semantic.UserLabelTable.Verify();
         semantic.UserGoToTable.clear();
         semantic.UserLabelTable.clear();
      }

      if (!semantic.IsQuad()) {
         TNodeCommand* command = new TNodeCommand(T_Command::command_Exit, number, 0, T_BaseType::btVoid);
         InsertAfter(command);
      }
   }
STEP_ELSE(End)
   BLOCK_END;
   semantic.function = NULL;
STEP_END
}
void TNodeDefFunc::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   VEntry entry(&semantic, this);
   semantic.function = this;
   if ((mode & T_VerifyMode::mvNoFunction)/* || !mid*/) return;
   Before(semantic, mode);
//   if (right) right->Codes(semantic, mode); // params
   if (mid) {
      semantic.ExecStack.Push();
      mid->Codes(semantic, mode); // body
      int exec_mode = semantic.ExecStack.Pop();
      if (!(exec_mode & T_ExecMode::meRestituer)) {
         if ((TBaseType::Tilda(BaseType(), T_BaseType::btStatic) != T_BaseType::btVoid) && (BaseType() != T_BaseType::btUnknown)) {
            semantic.AddError(this, erNoReturn);
         }
      }
   }
   After(semantic, mode);
   if (!semantic.IsQuad()) {
      if (semantic.syntax->option & T_OptionMode::omEraseCode) semantic.Code().Erase();
      semantic.Code().Labels();
   }
   semantic.function = NULL;
}
void TNodeDefFunc::Verify(TSemantic &semantic, int mode)
{
   if (right) right->Verify(semantic, mode); // params
   if (mid) mid->Verify(semantic, mode); // body
}

void TNodeDefine::Variables(TSemantic &semantic, int mode)
{
   T_Alloc alloc = T_Alloc::taLocal;
   if (semantic.IsTree()) {
      if (dynamic_cast<TNodeDefFunc*>(owner)) {
         alloc = T_Alloc::taParam;
      } else if (!owner->Owner()) {
         alloc = T_Alloc::taGlobal;
      }
   }
   TNodeType *define_type = Type();
   for (TNode *node : (*this)) {
      if (TNodeDefVar* var = dynamic_cast<TNodeDefVar*>(node)) {
         TNodeType* type = var->Type();
         if (!type) type = define_type;
         if (var->referenced) {
            type = TBaseType::Or(type, T_BaseType::btReference);
         }
         var->SetType(type);
         if (semantic.IsTree()) var->alloc = alloc;
      }
      VARIABLES(node);
   }
}
void TNodeDefine::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   T_NodeList::Codes(semantic, mode); 
   After(semantic, mode);
}

// --------------------------- Label, GoTo ---------------------------

TNodeLabel* TNodeLabel::Reference() const 
{ 
   if (!reference) return NULL;
   TNodeLabel* ref = reference; 
   while (ref->reference) {
      if (ref == ref->reference) {
         return NULL; 
      }
      ref = ref->reference;
   }
   return ref; 
}
void TNodeLabel::SetReference(TNodeLabel* r) 
{
   if (r) { r = r->Label(); r->go_to += go_to; go_to = 0; } reference = r; 
}

TNodeLabel* TNodeGoTo::GetLabel()
{
   TNodeLabel* l = (TNodeLabel*)child; if (l) l = l->Label();
   return l;
}

TNodeLabel* TSemantic::Merge(TNodeLabel* l1, TNodeLabel* l2)
{
   TNodeLabel* l = new TNodeLabel(this); l1->SetReference(l); l2->SetReference(l);
   GarbageCollectorAdd(l1, 0x01);  GarbageCollectorAdd(l2, 0x01);
   return l;
}
void TSemantic::Reference(TNodeLabel* label, TNodeLabel* refer)
{
   label->SetReference(refer);  GarbageCollectorAdd(label, 0x01);
}

void TNodeGoTo::SetLabel(TNodeLabel* l) 
{ 
   TNodeLabel* label = child; if (label) { label = label->Label(); label->go_to--; }
   if (l) { l = l->Label(); l->go_to++; } child = l;
}

TNodeLabel::TNodeLabel(TSemantic* semantic) :T_NodeOne(), reference(NULL), go_to(0), command(-1)
{
   if (semantic && semantic->IsQuad()) {
      quad.alloc = T_Alloc::taLabel;
      semantic->ValueNumber(quad);
   }
}

TNodeLabel::TNodeLabel(const T_Lexeme& l) :T_NodeOne(l, NULL), reference(NULL), go_to(0), command(-1)
{
}

void TNodeLabel::Codes(TSemantic &semantic, int mode)
{
   if (!Reference()) {
      if (semantic.IsQuad()) {
         TQuadruple* quadruple = new TQuadruple(TQuadruple::qtLabel, this);
         quadruple->value_number = quad;
         semantic.AddQuad(quadruple);
      } else {
         semantic.AddCode(this);
      }
   }
}
void TNodeGoTo::Codes(TSemantic &semantic, int mode)
{
   if (semantic.IsQuad()) {
      TNodeLabel *label = GetLabel();
      if (label) {
         TQuadruple* quadruple = new TQuadruple(TQuadruple::qtGoto, this);
         quadruple->oper = type;
         quadruple->arg_one = label->quad;
         if ((type == T_GoTo::tgIf) || (type == T_GoTo::tgElse)) {
            quadruple->arg_two = Owner()->quad;
         }
         semantic.AddQuad(quadruple);
      }
   } else {
      if (del_count) semantic.GenPop(del_count);
      semantic.AddCode(this);
   }
}

void TNodeUserGoTo::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   semantic.MakeGoToLabel(this);
   /*
   if (semantic.IsTree()) {
      TFinder finder(semantic, TFinder::mfLabel); finder.lexeme = &lexeme;
      if (Search(finder)) {
         SetLabel((TNodeLabel*)finder.result);
      } else {
         if (!SEMANTIC_MODE(Phase, TwoPhase)) {
            semantic.AddError(this, erUnknownLabel);
         } else {
            semantic.UserGoToTable.Add(this);
         }
      }
   } else if (semantic.IsBlock()) {
   */
      semantic.UserGoToTable.Add(this);
//   }
}
void TNodeUserGoTo::Verify(TSemantic &semantic, int mode)
{
   if (false && semantic.IsTree()) {
      const TNodeUserLabel* label = (const TNodeUserLabel*)GetLabel();
      if (label && !label->Compare(*this)) {
         semantic.AddError(this, erErrorLabel);
      }
   }
}
void TNodeUserGoTo::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   TNodeUserLabel *label = (TNodeUserLabel*)GetLabel();
   if (label) {
      int label_offset = 0, goto_offset = 0;
      for (const T_UserGoToItem& item : (*label)) { label_offset += item.offset; }
      for (const T_UserGoToItem& item : (*this))  { goto_offset  += item.offset; }
      del_count = goto_offset - label_offset;
	   TNodeGoTo::Codes(semantic, mode);
   }
   After(semantic, mode);

   semantic.ExecStack.GoTo();
}

void TNodeUserLabel::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   if (semantic.IsQuad() && (quad.alloc == T_Alloc::taNone)) {
      quad.alloc = T_Alloc::taLabel;
      semantic.ValueNumber(quad);
   }
   semantic.MakeGoToLabel(this);
   /*
   if (semantic.IsTree()) {
      TFinder finder(semantic, TFinder::mfLabel); finder.lexeme = &lexeme;
      if (Search(finder)) {
         semantic.AddError(this, erDuplicateLabel);
      } else {
         if (SEMANTIC_MODE(Phase, TwoPhase)) {
            semantic.UserLabelTable.Add(this);
         }
      }
   } else if (semantic.IsBlock()) {
   */
      semantic.UserLabelTable.Add(this);
//   }
}
void TNodeUserLabel::Codes(TSemantic &semantic, int mode)
{
//   IMPOSSIBLE
   semantic.ExecStack.Label();
   Before(semantic, mode);
   if (semantic.IsQuad()) {
      TQuadruple* quadruple = new TQuadruple(TQuadruple::qtLabel, this);
      quadruple->value_number = quad;
      semantic.AddQuad(quadruple);
   } else {
      semantic.AddCode(this);
   }
   After(semantic, mode);
}
void TNodeUserLabel::Verify(TSemantic &semantic, int mode)
{
   if (semantic.IsTree() && !go_to) {
      semantic.AddError(this, erUnusedLabel);
   }
}

void TNodeBreakContinue::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   semantic.FindLabel(*this);
}
void TNodeBreakContinue::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   TNodeGoTo::Codes(semantic, mode);
   After(semantic, mode);
   semantic.ExecStack.GoTo();
}

void TNodeReturn::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   TFinder finder(this, TFinder::mfFunctionType); finder.lexeme = &lexeme;
   if (semantic.Search(finder)) {
      if (TNodeType* type = (TNodeType*)finder.result) {
         base_type = type->BaseType();
      }
   }
   if (child) {
      VARIABLES(child); 
      if (!semantic.GenCastable(child, base_type, 0x00)) {
         semantic.AddError(child, erUnknownCast);
      }
   } else {
      if ((base_type != T_BaseType::btVoid) && (base_type != T_BaseType::btUnknown)) {
         semantic.AddError(this, erNoValue);
      }
   }
}
void TNodeReturn::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   if (child) {
      child->Codes(semantic, mode); 
   }
   if (semantic.IsQuad()) {
      TQuadruple* quadruple = new TQuadruple(TQuadruple::qtReturn, this);
      if (child) quadruple->arg_one = child->quad;
      semantic.AddQuad(quadruple);
   } else {
      semantic.GenCommand(T_Command::command_Return, 0, base_type);
   }
   After(semantic, mode);
   semantic.ExecStack.Return();
}

// --------------------------- Statements ---------------------------

#define FOR_CODE_1243_
void TNodeFor::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
STEP_IF(Begin)
   BLOCK_BEG;
STEP_ELSE(ForTitle)
   VARIABLES(left);  // prefix
   VARIABLES(mid);   // condition
   VARIABLES(right); // postfix
   TNodeLabel *label_condition = new TNodeLabel(&semantic), *label_body = NULL, *label_end;
   TNodeLabel *label_continue = new TNodeLabel(&semantic), *&label_break = label_end;
   mid->InsertBefore(label_condition);
   if (!mid->IsNull()) {
      semantic.MakeLogical(mid, label_body, label_end);
   }
   BreakContinueLabel(label_break, label_continue);
   one_label = label_condition; two_label = label_body;
STEP_ELSE(Body)
   TNodeLabel* &label_end = break_label, *&label_condition = one_label, *&label_body = two_label;
   if (!mid->IsNull()) {
      four->InsertBefore(label_body);
   } else  {
#if !defined(FOR_CODE_1243)
      label_body = new TNodeLabel(&semantic);
      four->InsertBefore(label_body);
#endif
      label_end = new TNodeLabel(&semantic);
   }

   VARIABLES(four);   // body

#if !defined(FOR_CODE_1243)
   TNodeGoTo* go_continue = new TNodeGoTo(T_GoTo::tgGoTo,continue_label);
   four->InsertAfter(go_continue);
#endif

   right->InsertBefore(continue_label); // postfix
   TNodeGoTo* go_cycle = new TNodeGoTo(T_GoTo::tgGoTo,label_condition); 
   right->InsertAfter(go_cycle);
   InsertAfter(label_end);
STEP_ELSE(End)
   BLOCK_END;
STEP_END
}
void TNodeFor::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   left->Codes(semantic, mode);   // prefix
   mid->Codes(semantic, mode );   // condition
   semantic.ExecStack.Push();

#if defined(FOR_CODE_1243)
   four->Codes(semantic, mode);   // body
   right->Codes(semantic, mode);  // postfix
#else
   right->Codes(semantic, mode);  // postfix
   four->Codes(semantic, mode);   // body
#endif

   semantic.ExecStack.Pop();
   After(semantic, mode);
}
void TNodeFor::Verify(TSemantic &semantic, int mode)
{
   left ->Verify(semantic, mode);  // prefix
   mid  ->Verify(semantic, mode ); // condition
   right->Verify(semantic, mode);  // postfix
   four ->Verify(semantic, mode);  // body
}

void TNodeWhile::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
STEP_IF(Begin)
   BLOCK_BEG
STEP_ELSE(Condition)
   TNodeLabel *&label_body = one_label, *label_end;
   VARIABLES(left); // condition 
   semantic.MakeLogical(left, label_body, label_end);

   TNodeLabel *label_while = new TNodeLabel(&semantic);
   left->InsertBefore(label_while);
   
   BreakContinueLabel(label_end, label_while);
STEP_ELSE(Body)
   VARIABLES(right); // body    
   TNodeLabel* &label_while = continue_label, *&label_end = break_label, *&label_body = one_label;
   right->InsertBefore(label_body);
   TNodeGoTo* go_cycle = new TNodeGoTo(T_GoTo::tgGoTo,label_while);
   right->InsertAfter(go_cycle);
   InsertAfter(label_end);
STEP_ELSE(End)
   BLOCK_END
STEP_END
}
void TNodeWhile::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   left->Codes(semantic, mode); 
   if (right) {
      semantic.ExecStack.Push();
      right->Codes(semantic, mode); // body 
      semantic.ExecStack.Pop();
   }
   After(semantic, mode);
}
void TNodeWhile::Verify(TSemantic &semantic, int mode)
{
   left->Verify(semantic, mode); 
   if (right) right->Verify(semantic, mode); // body 
}

void TNodeDo::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
STEP_IF(Begin)
   BLOCK_BEG
   TNodeLabel *label_do = new TNodeLabel(&semantic), *label_while = new TNodeLabel(&semantic), *label_end = new TNodeLabel(&semantic);
   BreakContinueLabel(label_end, label_while);
   one_label = label_do;
STEP_ELSE(Body)
   VARIABLES(right); // body 
STEP_ELSE(Condition)
   TNodeLabel *label_do, *label_end;
   VARIABLES(left); // condition 
   semantic.MakeLogical(left, label_do, label_end);
   semantic.Reference(label_do, one_label);
   semantic.Reference(label_end, break_label);

   InsertBefore(label_do);
   TNodeLabel* &label_while = continue_label;
   left->InsertBefore(label_while);
   InsertAfter(break_label);
STEP_ELSE(End)
   BLOCK_END
STEP_END
}
void TNodeDo::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   if (right) {
      semantic.ExecStack.Push();
      right->Codes(semantic, mode); // body 
      semantic.ExecStack.Down();
   }
   left->Codes(semantic, mode); 
   After(semantic, mode);
}
void TNodeDo::Verify(TSemantic &semantic, int mode)
{
   if (right) right->Verify(semantic, mode); // body 
   left->Verify(semantic, mode); 
}

void TNodeIf::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
STEP_IF(Begin)
   BLOCK_BEG;
STEP_ELSE(Condition)
   VARIABLES(left);    // condition
   trunc = size;
   TNodeLabel* &true_label = one_label, * &false_label = two_label;
   TNode* *my_left = &left;
   if (T_NodeList* condition_def = dynamic_cast<T_NodeList*>(left)) {
      my_left = &condition_def->back();
   }
   semantic.MakeLogical(*my_left, true_label, false_label);
STEP_ELSE(IfThen)
   VARIABLES(mid);    // then
   TNodeLabel* &true_label = one_label;
   semantic.BlockTrunc(trunc);
   mid->InsertBefore(true_label);     // then
STEP_ELSE(IfElse)
   VARIABLES(right);  // else
STEP_ELSE(IfLabel)
   TNodeLabel* &false_label = two_label;
   TNodeLabel *label_end = new TNodeLabel(&semantic);
   TNodeGoTo* go_then = new TNodeGoTo(T_GoTo::tgGoTo,label_end);
   mid->InsertAfter(go_then);
   right->InsertBefore(false_label);  // else
   InsertAfter(label_end);
STEP_ELSE(End)
   BLOCK_END;
STEP_END
}
void TNodeIf::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   left->Codes(semantic, mode);// condition
   semantic.ExecStack.Push();
   if (mid) mid->Codes(semantic, mode); // then
   int then_exec = semantic.ExecStack.Pop();
   semantic.ExecStack.Push();
   if (right) right->Codes(semantic, mode);  // else
   int else_exec = semantic.ExecStack.Pop();
   semantic.ExecStack.Up(then_exec & else_exec);
   After(semantic, mode);
}
void TNodeIf::Verify(TSemantic &semantic, int mode)
{
   left->Verify(semantic, mode);// condition
   if (mid) mid->Verify(semantic, mode); // then
   if (right) right->Verify(semantic, mode);  // else
}

void TNodeSwitchItem::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   BLOCK_BEG;
   VARIABLES(right); // body 
   BLOCK_END;
}
void TNodeSwitchItem::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   if (right) right->Codes(semantic, mode); // body 
   After(semantic, mode);
}

void TNodeSwitch::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
   BLOCK_BEG;
   VARIABLES(right); // body 
   BLOCK_END;
}
void TNodeSwitch::Codes(TSemantic &semantic, int mode)
{
   IMPOSSIBLE
   Before(semantic, mode);
   if (right) right->Codes(semantic, mode); // body 
   After(semantic, mode);
}

void TNodeStatements::Variables(TSemantic &semantic, int mode)
{
   VEntry entry(&semantic,this);
STEP_IF(Begin)
   BLOCK_BEG;
STEP_ELSE(Body)
   T_NodeList::Variables(semantic, mode);
STEP_ELSE(End)
   BLOCK_END;
STEP_END
};

// --------------------------- Search ---------------------------

bool TFinder::Compare(const T_Lexeme& l)
{
   return semantic->Compare(*lexeme, l);
}

void TFinder::Reset(int m)
{
   mode = m; level = 0; count = 0;
   result = NULL;
}

bool TNode::Search(TFinder& finder)
{
   if (!owner) return false;
   finder.place = this;
   finder.level++;
   return owner->Search(finder);  
}

bool TNode::SearchInside(TFinder& finder)
{
   return false;
}

bool T_NodeList::Search(TFinder& finder)
{
   TNode* skip = finder.place;
   for (const_reverse_iterator r = rbegin(); r < rend(); r++) {
      TNode* child = (*r);
      if (skip) {
         if (finder.mode == TFinder::mfLabel) {
            if (skip == child) continue;
         } else {
            if (skip == child) skip = NULL;
            continue;
         }
      }
      if (child->SearchInside(finder)) return true;
   }
   if ((finder.mode & TFinder::mfDuplicateSearch) && dynamic_cast<TBlock*> (this)) return false;
   return TNode::Search(finder);
}

bool T_NodeList::SearchInside(TFinder& finder)
{
   if ((finder.mode == TFinder::mfLabel) || (finder.mode == TFinder::mfVar)/* && finder.IsStack()*/) {
      for (TNode* child : (*this)) {
         if (child->SearchInside(finder)) return true;
      }
   }
   return false;
}

bool TNodeStatements::Search(TFinder& finder)
{
   return T_NodeList::Search(finder);
}

bool TNodeDefFunc::Search(TFinder& finder)
{
   if (finder.mode & TFinder::mfFunction) {
      finder.result = this;
      return true;
   }
   if (finder.mode & TFinder::mfOffset) return false;
   if (right && (right != finder.place)) {
      if (right->SearchInside(finder)) return true;
   }
   if (finder.mode & TFinder::mfDuplicateSearch) return false;
   return TNode::Search(finder);
}

bool TNodeDefFunc::SearchInside(TFinder& finder)
{
   if (right && (right != finder.place)) {
      if (right->SearchInside(finder)) return true;
   }
   return false;
}

bool TNodeExpressions::Search(TFinder& finder)
{
   return TNode::Search(finder);
}

bool TNodeDefVar::SearchInside(TFinder& finder)
{
   if (finder.mode & TFinder::mfOffset) finder.count++;
   if (!(finder.mode & TFinder::mfVar) && !(finder.mode & TFinder::mfDuplicateSearch) || !finder.Compare(lexeme)) return false;
   finder.result = this;
   return true;
}

bool TNodeDefine::Search(TFinder& finder)
{
   for (TNode* child : (*this)) {
      if ((finder.mode & (TFinder::mfDuplicateSearch | TFinder::mfOffset)) && (child == finder.place)) break;
      if (child->SearchInside(finder)) return true;
      if (child == finder.place) break;
   }
   return TNode::Search(finder);
}

bool TNodeDefine::SearchInside(TFinder& finder)
{
   for (TNode* child : (*this)) {
      if (child->SearchInside(finder)) return true;
   }
   return false;
}

bool TNodeFor::Search(TFinder& finder)
{
   if (left && (left != finder.place)) {
      if (left->SearchInside(finder)) return true;
   }
   if (finder.mode & TFinder::mfDuplicateSearch) return false;
   return TNode::Search(finder);
}

bool TNodeFor::SearchInside(TFinder& finder)
{
   if ((finder.mode == TFinder::mfLabel) && Body()) return Body()->SearchInside(finder);
   return false;
}

bool TNodeWhile::SearchInside(TFinder& finder)
{
   if ((finder.mode == TFinder::mfLabel) && Body()) return Body()->SearchInside(finder);
   return false;
}

bool TNodeDo::SearchInside(TFinder& finder)
{
   if ((finder.mode == TFinder::mfLabel) && Body()) return Body()->SearchInside(finder);
   return false;
}

bool TNodeIf::SearchInside(TFinder& finder)
{
   if (finder.mode == TFinder::mfLabel) {
      if (Then() && Then()->SearchInside(finder)) return true;
      if (Else()) return Else()->SearchInside(finder);
   }
   return false;
}

bool TNodeUserLabel::SearchInside(TFinder& finder)
{
   if ((finder.mode != TFinder::mfLabel) || !finder.Compare(lexeme)) return false;
   finder.result = this;
   return true;
}

// --------------------------- Command ---------------------------

void TNodeCommand::Codes(TSemantic &semantic, int mode)
{
   semantic.AddCode(this); 
}

#include "define_title.cpp"

static const char* command_title[] = { "None", "Cast", "Oper", "Call", "GoTo", "Label", "NewVar", "NewArr", 
                                       "PushVar", "PushVal", "PushArr", "PushAal", "PushInt", "PushNum", "Pop", "Return", "Exit", "InitArr" };
static const char* command_title_mode_goto[] = { "None", "If", "Else", "GoTo" };
static const char* command_title_alloc[] = { "None", "Global", "Local", "Param" };

const char* title_cast_type(T_CastType cast) { return cast_type_title[cast]; }
const char* title_command_mode_goto(int mode) { return command_title_mode_goto[mode]; }

void TNodeCommand::print(int level, TPrinter& printer) const
{
   PRINTER_FILE_MODE
   TNode::print(level,printer);
   print_offset(level + 1,false,file); 
   fprintf(file,"command = %-10s",command_title[command]);
   if (command == T_Command::command_Oper)
      fprintf(file,", oper  = %-14s",lexeme_type_title((T_Symbol::T_Type)param));
   else if (command == T_Command::command_Cast)
      fprintf(file,", cast  = %-14s",cast_type_title[param]);
   else if (command == T_Command::command_GoTo)
      fprintf(file,", label = %03d, %-4s ",param,title_command_mode_goto(mode));
   else if (command == T_Command::command_NewArr)
      fprintf(file,", range = %03d, %-6s ",param,command_title_alloc[mode]);
   else if ((command >= T_Command::command_PushVar) && (command <= T_Command::command_PushAal) || (command == T_Command::command_InitArr) || (command == T_Command::command_NewVar))
      fprintf(file,", addr  = %03d, %-6s ",param,command_title_alloc[mode]);
   else 
      fprintf(file,", param = %03d",param);
   fprintf(file,", mode = %03d, type = %-10s",mode,TBaseType::Title(base_type));
}

void TNodeCommand::write(TWriter& printer) const
{
   PRINTER_FILE_MODE
   fprintf(file,"command = %-10s",command_title[command]);
   if (command == T_Command::command_Oper)
      fprintf(file,", oper  = %-14s",lexeme_type_title((T_Symbol::T_Type)param));
   else if (command == T_Command::command_Cast)
      fprintf(file,", cast  = %-14s",cast_type_title[param]);
   else if (command == T_Command::command_GoTo)
      fprintf(file,", label = %03d, %-4s ",param,command_title_mode_goto[mode]);
   else if (command == T_Command::command_NewArr)
      fprintf(file,", range = %03d, %-6s ",param,command_title_alloc[mode]);
   else if ((command >= T_Command::command_PushVar) && (command <= T_Command::command_PushAal) || (command == T_Command::command_InitArr) || (command == T_Command::command_NewVar))
      fprintf(file,", addr  = %03d, %-6s ",param,command_title_alloc[mode]);
   else 
      fprintf(file,", param = %03d",param);
   fprintf(file,", mode = %03d, type = %-10s",mode,TBaseType::Title(base_type));
}

void TNodeDel::Codes(TSemantic &semantic, int mode)
{
   if (!semantic.IsQuad()) {
      if (count) semantic.GenPop(count);
   }
   GarbageCollectorAdd(this, 0x01);
}

void TNodeDel::print(int level, TPrinter& printer) const
{
   PRINTER_FILE_MODE
   TNode::print(level, printer);
   print_offset(level + 1, false, file); fprintf(file, "delete=%02d", count);
}


VEntry::VEntry(TSemantic* s, TNode* node) 
   :semantic(s) 
{ 
   TPrinter printer;
   if (semantic->print_mode & 0x0000) { // T_OptionMode::omPrintTree
      node->TNode::print(semantic->level, printer);
   }
   semantic->level++; 
}
VEntry::~VEntry() 
{ 
   semantic->level--; 
}
