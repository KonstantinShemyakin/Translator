#ifndef TRN_RSYNTAX_H
#define TRN_RSYNTAX_H

#include "Parse.h"
#include "ASyntax.h"
#include "TNodes.h"
#include "SNodes.h"
#include "Rules.h"
#include "Tables.h"
#include "CSyntax.h"

class GMaker;
class GMakerTable;
class M_Syntax;
class MC_Syntax;
class GSyntax;
struct T_Lexeme_SNode;

class TLexemeSet : public std::map<const GSymbol, int>
{
public:
   TLexemeSet(const TGrammar* g) :grammar(g) {}
   bool Add(const GSymbol&);
   int  GetAdded(const GSymbol&) const;
   void print(TPrinter& printer) const;
   void YACC(TPrinter& printer) const;
   int  count() const { return (int)size(); }
public:
   T_SyntaxLexeme grammar_type() const;
public:
   const TGrammar* grammar;
};

class SNode;
struct T_Lexeme_SNode
{
   T_Lexeme_SNode() :node(NULL), tree(NULL), unit(NULL) {}
   T_Lexeme lexeme; SNode* node; TNode* tree; T_SyntaxNode* unit;
};

struct TStackRuleItem
{
public:
   TStackRuleItem() :sym(), store(), step(0), auto_number(0) {}
   TStackRuleItem(const GSymbol& s) :sym(s), store(), step(0), auto_number(0) {}
   TStackRuleItem(TNode* t) :sym(), store(), step(0), auto_number(0) { lexeme_node.tree = t; }
   TStackRuleItem(SNode* n) :sym(), store(), step(0), auto_number(0) { lexeme_node.node = n; }
public:
   TNode* Node() { return lexeme_node.tree; }
   SNode* SNode() { return lexeme_node.node; }
   bool Piston(const TStackRuleItem& source, int mode = 0x01); // 0x01 - None, 0x02 - Produce; (lexeme, node, tree) ==>>
   void print(TPrinter& printere) const;
public:
   int   step, auto_number;
   T_ScanStore  store;
   GSymbol sym;
public:
   T_Lexeme_SNode lexeme_node;
};

class TStackRule : public std::vector<TStackRuleItem>
{
public:
   TStackRule() {}
public:
   TStackRuleItem& stack_item(int index) { return (*this)[index]; }
   int  filled() const { return (int)size(); }
   void lexeme_piston(int item_step, const T_Lexeme& lexeme);
public:
   void print(TPrinter& printere) const;
};

class S_Syntax 
{
public:
   S_Syntax(TGrammar*  g) :grammar(g), level(0), max_level(0), step(0) {}
public:
   void entry(const TStackRuleItem& item) { rule_stack.push_back(item); level++; step++; if (max_level < level) max_level = level; }
   void entry(const GSymbol& symbol) { TStackRuleItem item(symbol); entry(item); }
   void leave() { level--; rule_stack.pop_back(); }
   TStackRuleItem& top() { return rule_stack.back(); }
   TStackRuleItem& stack_item(int index) { return rule_stack[index]; }
   void lexeme_piston(int item_step, const T_Lexeme& lexeme) { rule_stack.lexeme_piston(item_step, lexeme); }
   bool empty() const    { return rule_stack.empty(); }
   int  filled() const   { return (int)rule_stack.size(); }
public:
   void print_stack() const { TPrinter printer(NULL, 0x00, grammar); rule_stack.print(printer); }
public:
   TStackRule rule_stack;
public:
   int level, max_level, step;
   TGrammar*  grammar;
};

class M_Syntax : public A_Syntax 
{
public:
	M_Syntax(T_Scan *s);
   ~M_Syntax();
public:
   virtual void Store(T_ScanStore& store);
   virtual bool Restore(const T_ScanStore& store);
   virtual void print_store(TPrinter& printer) const; 
   virtual bool Command(int command) { return false; }
   void Counts(int &tns, int &tls) const { tns = CountNodes(); tls = CountLexemes(); }
   void Trunc(int tns, int tls)          { TruncNodes(tns); TruncLexemes(tls); }
   virtual void PushLexeme(const T_Lexeme& lexeme);
   virtual void push_lexeme(const T_Lexeme& lexeme);
   bool Empty() const { return !tree_stack.size(); }
   void PushNode(TNode* node)   { tree_stack.push_back(node); }
   TNode* TopNode()             { if (tree_stack.empty()) return NULL; return tree_stack.back().Node(); }
   TNode* PopNode()             { if (tree_stack.empty()) return NULL; TNode* node = tree_stack.back().Node(); tree_stack.pop_back(); return node; }
   int  CountNodes() const      { return (int)tree_stack.size(); }
   void TruncNodes(int trunc)   { while (trunc < CountNodes()) { tree_stack.back().Node()->clear(); tree_stack.pop_back(); trunc_node++; } }
   int  CountSNodes() const     { return (int)tree_stack.size(); }
   void TruncSNodes(int trunc)  { while (trunc < CountSNodes()) { tree_stack.back().SNode()->clear(); tree_stack.pop_back(); trunc_snode++; } }
   virtual TNode* Node() { return CountNodes() ? TopNode() : NULL; }
   virtual void print_stack(bool all = false);
public:
   int  CountLexemes() const    { return (int)lexemes.size(); }
   void TruncLexemes(int trunc) { while (trunc < CountLexemes()) { lexemes.pop(); trunc_lexeme++; } }
   T_Lexeme& TopLexeme()        { return lexemes.top(); }
   T_Lexeme PopLexeme();
public:
   SNode& STop()         { return *tree_stack.back().SNode(); }
   SNode* SPop()         { SNode* ret = tree_stack.back().SNode(); tree_stack.pop_back(); return ret; }
   void SPush(SNode* n)  { tree_stack.push_back(n); }
   void SAdd(SNode* n)   { STop().Add(n); }
   bool SEmpty() const   { return !tree_stack.size(); }
public:
   T_SyntaxNode& ATop() { return *anodes.back(); }
   T_SyntaxNode* APop() { T_SyntaxNode* ret = anodes.back(); anodes.pop_back(); return ret; }
   void APush(T_SyntaxNode* n) { anodes.push_back(n); }
   T_SyntaxNode& AItem(int index) { return *anodes[index]; }
   bool AEmpty()  const { return !anodes.size(); }
   int  AFilled() const { return (int)anodes.size(); }
public:
   virtual void Tree(SNode* node) { tree = node; }
   virtual SNode* Tree()          { if (tree) return tree; if (SEmpty()) return NULL; return &STop(); }
protected:
   int trunc_node, trunc_lexeme, trunc_snode;
protected:
   std::stack<T_Lexeme> lexemes;
   std::vector<T_SyntaxNode*> anodes;
public:
   TStackRule tree_stack;
public:
   virtual void ClearProgram();
public:
   void Accept();
   void Accept(const TStackRuleItem& item);
public:
   SNode* tree;
public:
   virtual TSyntaxTree* Auto() { return &unit; }
   virtual void Auto(T_SyntaxNode* node) { unit = node; }
public:
   TSyntaxTree unit;
public:
   const GMakerTable* makers;
};

// --------------------------- MC_Syntax ---------------------------
class MC_Syntax : public M_Syntax, public C_Syntax
{
public:
	MC_Syntax(T_Scan *s) :M_Syntax(s) {}

   bool Match(T_Lexeme::T_Syntax);
	bool Match(T_Lexeme::T_Group g);
	bool Match(T_Lexeme::T_Group g, T_Symbol::T_Type t);
	bool Match(A_Symbol::T_Priority priority);
	bool Match(T_Lexeme::W_Type keyword);

   bool Maker(const GSymbol& sym);
   bool MakerSyntaxNode(const GSymbol& sym, T_Lexeme_SNode* data_stack[], int maker_index = -1);
   virtual void Counts(int &tns, int &tls) const { tns = CountNodes(); tls = CountLexemes(); }
   virtual void Counts(int &tns, int &tls, int &tts) const { tns = CountNodes(); tls = CountLexemes(); tts = CountTypes(); }
   virtual void Store(T_ScanStore& store);
   virtual bool Restore(const T_ScanStore& store);
   virtual void print_store(TPrinter& printer) const; 
};

class RSyntax : public MC_Syntax, public S_Syntax
{
public:
	RSyntax(T_Scan *s, TGrammar* g);
   virtual bool Parse();
   virtual bool ParseStack();
   virtual bool ParseStack_SN();
   virtual bool Parse(const GFormula& formula);
   virtual bool Parse(const GProduce& produce);
           int  MatchSymbol(const GSymbol& sym, int mode = 0x00); // 0x01 -!save
           bool MatchLexeme(const GSymbol& sym, int mode = 0x00); // 0x01 -!save
protected:
           int  ProduceToStack();
public:
   virtual bool Translate();
   virtual void clear(TNode* node);
public:
   void set_syntax_mode(T_SyntaxMode m) { syntax_mode = m; }
   int rules_true, rules_false, produce_count, failure_count, luck_count;
};

#endif