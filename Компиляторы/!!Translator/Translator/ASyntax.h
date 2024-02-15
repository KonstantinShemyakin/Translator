#ifndef TRN_ASYNTAX_H
#define TRN_ASYNTAX_H
 
#include "Parse.h"
#include <stack>

class TNode;
class TNodeType;
class SNode;
class T_SyntaxNode;
class TSyntaxTree;
class A_Syntax;
class TData;

class TError 
{
public:
   TError(T_Scan* s) :Scan(s) {} 
	bool error(T_Error code, const T_Lexeme &l, int value = 0);
public:
   T_Scan* Scan;
};

struct TErrorItem {
   TErrorItem() :code(erNone), value(0) {}
   TErrorItem(T_Error c, const T_Lexeme &l, int v) :lexeme(l), code(c), value(v) {}
public:
   T_Lexeme lexeme;
   T_Error  code;
   int      value;
};

class TErrorTable : public std::vector<TErrorItem> {
public:
   TErrorTable(A_Syntax *s) : syntax(s) {}
public:
   void Add(T_Error code, const T_Lexeme &l, int value = 0);
public:
   void print() const;
protected:
   A_Syntax *syntax;
};

// ------------------------- T_GrammarType ------------------------
enum T_Grammar { 
   gtNone = 0x0000, gtLL        = 0x00000001, gtLR     = 0x00000002, gtLLk         = 0x00000004,
   slNone = 0x0000, slSyntax    = 0x00000010, slPrior  = 0x00000020, slPriorAssign = 0x00000040, slMeta      = 0x00000080,
   mtNone = 0x0000, mtTree      = 0x00000100, mtCode   = 0x00000200, mtSNode       = 0x00000400, mtYacc      = 0x00000800, 
                    mtTurn      = 0x00001000, mtEmpty  = 0x00002000, mtHead        = 0x00004000, slSimple    = 0x00008000,
                    slNoDefType = 0x00010000, slNoSave = 0x00020000, slNoDefArrVar = 0x00040000, mtCall      = 0x00080000
};
typedef T_Grammar T_SyntaxLexeme;

// --------------------------- A_Syntax ---------------------------
class A_Syntax : public T_Parse
{
public:
   enum T_SyntaxMode   { smNone, smParseStackRule, smParseStackSymbol, smParseRule, smParseFormula, smParseLL1, smParseLR0, smParseLR0_Core, smParseLR1, smParseLR1_Core, smParseLALR, smParseLALR_Tab, smParseLALR_Full, smParseLALR_Core, smParseYACC };
public:
	A_Syntax(T_Scan *s) :T_Parse(s), Error(s), ErrorTable(this), syntax_lexeme(slSyntax), syntax_mode(smNone), data(NULL), program(NULL), store_count(0), restore_count(0), error_recovery(0), option_mode(mmNone)
                       { WordTable(&T_KeyWordTable::key_word_table); }
   ~A_Syntax();
public:
   virtual T_Lexeme::T_Group Lexeme(T_Lexeme &l);
	bool MatchSyntax(T_Lexeme &l, const T_Lexeme &match);
   bool MatchLexeme(const T_Lexeme &lexeme);
   virtual void PushLexeme(const T_Lexeme& lexeme) {}
   virtual bool IsSaved(const T_Lexeme& lexeme) const;
   virtual bool MatchMust(T_Symbol::T_Type t);
   virtual bool Translate() { return false; }
   virtual void clear(TNode* node) {}
   virtual void ClearProgram() {}
   virtual TNode* Program() { return program; }
   virtual void Program(TNode* p) { program = p; }
   virtual TNode* Node() { return NULL; }
   virtual void print_stack(bool all = false) {}
   virtual SNode* Tree() { return NULL; }
   virtual void Tree(SNode* node) {}
   virtual TSyntaxTree* Auto() { return NULL; }
   virtual void Auto(T_SyntaxNode* node) {}
   int  SCDefine(T_Lexeme &l, int mode); // -1 - error, 0, 0x01 - define, 0x02 - const, 0x04 - static, 0x08 - &, 0x10 - after define, 0x20 - void
   TNodeType* BaseType(const T_Lexeme &l, int detail = 0x00);
public:
   virtual void Store(T_ScanStore& store) { T_Parse::Store(store); store_count++; }
   virtual bool Restore(const T_ScanStore& store) { if (!T_Parse::Restore(store)) return false; restore_count++; return true; }
   virtual void print_store(TPrinter& printer) const; 
   bool Source(T_SourceFile& source, const char* file, const T_WordTable* word_table = &T_KeyWordTable::key_word_table);
   T_Scan& Scan() { return T_Parse::Scan(); }
   void Scan(T_Scan *s) { T_Parse::Scan(s);  Error.Scan = s; }
public:
	bool error(T_Error code, int value = 0)        { return error(code,forward,value); }
   bool error_true(T_Error code, int value = 0)   { error(code,value); return true; }
	bool error(T_Error code, const T_Lexeme &l, int value = 0);

   TErrorTable    ErrorTable;
   TError         Error;
   int            error_recovery;
public:
   enum M_Mode { mmNone = 0x00000000, mmTree   = 0x00000001, mmCode  = 0x00000002, mmNode     = 0x00000003, mmTurn     = 0x00000004, mmMade    = 0x00000005, mmCall  = 0x00000006, mmC_Syntax = 0x0000000C, mmC99_Syntax = 0x0000000D,
                 mmMain = 0x00000000, mmMethod = 0x00000001, mmLexer = 0x00000002, mmSemantic = 0x00000003, mmGenerate = 0x00000004, mmGrammar = 0x00000005, mmPhase = 0x00000007,
                 mmMineLexer = 0x00000000, mmFLexLexer = 0x00000001,
                 mmOnePhase  = 0x00000001, mmTwoPhase = 0x00000002, mmThreePhase = 0x00000003,
                 mmBlockTable = 0x00000001, mmTreeSearch = 0x00000002, mmTreeStack = 0x00000003, mmRuleStack = 0x00000004,
                 mmCodeGenerate = 0x00000001, mmQuadGenerate = 0x00000002,
                 mmLL, mmNL, mmLR, mmNR, // grammars
                 mmETF_LL, mmETF_LLMake, mmETF_LR, mmETF_LRMake, mmEXPR_LR, // examples
                 mmTable, mmBIF, mmBNF, mmYACC, mmY, mmParser, // parsers
                 mmFile, // reader
                 mm = 0x00000000, mm0 = 0x00000000, mm1, mm2, mm3, mm4, mm5, mm6, mm7, mm8, mm9, mmA, mmB, mmC, mmD, mmE, mmF,
   };
   bool SemanticMode(M_Mode area, M_Mode mode) const;
   void set_make_mode(int m) { option_mode = m; }
public:
   int            option_mode;
public:
   T_SyntaxMode   syntax_mode;
   T_SyntaxLexeme syntax_lexeme;
public:
   TData*         data;
protected:
   TNode* program;
protected:
   int store_count, restore_count;
};

#define ACTION(MODE) ((option_mode & 0x0000000F) == A_Syntax::mm##MODE)

#define OPTION_MODE(P7,P6,P5,P4,P3,P2,P1,P0) (A_Syntax::M_Mode)(\
    (A_Syntax::M_Mode::mm##P0) | ((A_Syntax::M_Mode::mm##P1) << 4) | ((A_Syntax::M_Mode::mm##P2) << 8) | ((A_Syntax::M_Mode::mm##P3) << 12) \
     | ((A_Syntax::M_Mode::mm##P4) << 16) | ((A_Syntax::M_Mode::mm##P5) << 20) | ((A_Syntax::M_Mode::mm##P6) << 24) | ((A_Syntax::M_Mode::mm##P7) << 28) \
    )

#define OPTION_METHOD(P7,P6,P5,P4,P3,P2,P1,P0) (A_Syntax::M_Mode)(\
    (P0) | (P1 << 4) | (P2 << 8) | ((A_Syntax::M_Mode::mm##P3) << 12) \
     | ((A_Syntax::M_Mode::mm##P4) << 16) | (P5 << 20) | ((A_Syntax::M_Mode::mm##P6) << 24) | ((A_Syntax::M_Mode::mm##P7) << 28) \
    )

#define OPTION_AREA(OPTION,AREA) (((OPTION >> (4 * A_Syntax::M_Mode::mm##AREA)) & 0x0000000F))

#define OPTION_EMPTY(OPTION,AREA) (OPTION_AREA(OPTION,AREA) == A_Syntax::M_Mode::mmNone)


#endif

