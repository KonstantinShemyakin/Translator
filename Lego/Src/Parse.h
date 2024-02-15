#ifndef TRN_PARSE_H
#define TRN_PARSE_H
 
#if defined(_MSC_VER)
   #define SSCANF(B,F,V)    sscanf_s(B,F,V)
   #define FOPEN(F,N,M)     fopen_s(&F,N,M)
   #define STRCPY(D,L,S)    strcpy_s(D,L,S)
   #define SPRINTF(B,F,V)   sprintf_s(B,F,V)
   #define MIN(a,b)         (((a) < (b)) ? (a) : (b))
   #define FSCANF           fscanf_s
#elif defined(__GNUC__)
   #define SSCANF(B,F,V)    sscanf(B,F,V)
   #define FOPEN(F,N,M)     F = fopen(N,M)
   #define STRCPY(D,L,S)    strcpy(D,S)
   #define SPRINTF(B,F,V)   sprintf(B,F,V)
   #define MIN(a,b)         (((a) < (b)) ? (a) : (b))
   #define FSCANF           fscanf
#endif

#define PRINT_FILE_OPEN_NO_RETURN(F,N,M) \
   FILE* F; \
   if (N) { \
      FOPEN(F, N, M); \
   } else { \
      F = stdout; \
   }

#define PRINT_FILE_OPEN(F,N,M) \
   PRINT_FILE_OPEN_NO_RETURN(F,N,M) \
   if (!F) return;

#define PRINTER_FILE_MODE \
   FILE* file = printer.file; int print_mode = printer.print_mode; 

#define PRINTER_FILE_GRAMMAR \
   FILE* file = printer.file;\
   const TGrammar* grammar = printer.grammar;

#define PRINTER_FILE_MODE_GRAMMAR \
   PRINTER_FILE_MODE\
   const TGrammar* grammar = printer.grammar;

#define PRINTER_FILE_MODE_GRAMMAR_IF \
   PRINTER_FILE_MODE\
   if (!printer.grammar) printer.grammar = grammar;

#define PRINTER_FILE_MODE_GRAMMAR_THIS \
   PRINTER_FILE_MODE\
   printer.grammar = this;

#define MAKER_CRAMP

#ifdef MAKER_CRAMP
   #define SYMBOL_PRINT_TITLE_LEN  25
   #define MAKER_PRINT_TITLE_LEN   25
#else
   #define SYMBOL_PRINT_TITLE_LEN  30
   #define MAKER_PRINT_TITLE_LEN   40
#endif
#define PRODUCE_PRINT_TITLE_LEN    20

#define BREAK_POINT_TITLE(FIELD,TITLE) if (FIELD && !strcmp(FIELD,TITLE)) { int _i_ = 0; 
#define BREAK_POINT_END                _i_++; }

#define BREAK_POINT_POS(LEXEME,POS) if (LEXEME.pos == POS) { int _i_ = 0; 

#define PRINT_TITLE(TITLE,TYPE) \
   fprintf(file,"enum "#TYPE" { "); \
   for (const char* item : TITLE) {\
   	fprintf(file,"%s, ", item);\
      count++; \
   }\
   fprintf(file," };\n"); \
   fprintf(file,"const char* "#TITLE"[] = { "); \
   for (const char* item : TITLE) {\
   	fprintf(file,"\"%s\", ", item);\
      count++; \
   }\
   fprintf(file," };\n\n");

#define DECLARE_PRINT_TITLE(FUNC) \
int FUNC(TPrinter& printer);

#define FUNCTION_PRINT_TITLE(FUNC) \
int FUNC(TPrinter& printer) \
{  \
   int count = 0; \
   PRINTER_FILE_MODE 

#define END_PRINT_TITLE \
   return count; \
}

class TGrammar; class TSemantic;
// --------------------------- TPrinter ---------------------------
class TPrinter
{
public:
   enum T_Trail  { trNone = 0x00, trElse = 0x01, trOffset = 0x02, trLen = 0x04, trSkip = 0x08, trMaker = 0x10, trLenPlus = 0x20 };
   enum T_Offset { toNone = 0x00, toEol  = 0x01, toNoOffset = 0x02 };
public:
   TPrinter(int p = 0x00);
   TPrinter(TPrinter& o, int p = -1);
   TPrinter(const char* t, int p, const TGrammar* g = NULL);
   TPrinter(const TGrammar* g, int p = 0x00);
   ~TPrinter();
public:
   bool opened() const { return (file != NULL); }
   void eol();
   void reset(const char* f_m, int p = -1);
   void print_offset(int level, int mode); // 0x01 - eol, 0x02 - !offset
   void offset(int len, bool yes_eol = true);
   void trail(int &len, int mode = 0x00);
   void shift(int len);
   void shift() { shift_ = 0; };
public:
   FILE* file;
   int print_mode, length, shift_;
   const TGrammar* grammar;
   const TSemantic* semantic;
   const char* file_name;
   const char* title;
   void* param;
protected:
   TPrinter* owner;
};

typedef TPrinter TWriter;

void print_offset(int level, int mode = 0x01, FILE *file = stdout); // 0x01 - eol, 0x02 - !offset

// --------------------------- T_Source ---------------------------

struct T_Source
{
   enum T_Type { ftNone, ftUnknown, ftYACC, ftY, ftBNF, ftBIF };
   enum T_Sym { slNone, slDigit, slAlpha, slOper, slSeparator, slLimiter, slSpace, slEol, slUnknown, slError, slEof };
	const char* text;
	int index, length;
	T_Source() : text(NULL), index(0), length(MAX_LENGTH) {}
	T_Source(const char* t) : text(t), index(0), length(MAX_LENGTH) {}
	T_Sym Sym(int &sym);
	T_Sym Read(int &sym);
	virtual int Char(int pos) const { return text[pos]; }
	int  Pos() const          { return index; }
	void Pos(int p)           { index = p; }
	void Back()               { if (index && text) index--; }
	void Reset()              { index = 0; }
	void Reset(const char* t) { text = t; length = MAX_LENGTH; index = 0; }
   virtual T_Type Type() const { return ftNone; }

	static const int MAX_LENGTH = 10000000;
}; 

// --------------------------- A_Symbol ---------------------------
struct A_Symbol
{
	enum T_Type { 
               lxNone, lxAdd, lxSub, lxMulti, lxDiv, lxMod,
				   lxAddAssign, lxSubAssign, lxMultiAssign, lxDivAssign, lxModAssign, lxAndAssign, lxOrAssign, lxXOrAssign, lxAssign,
				   lxOr, lxAnd, lxOrOr, lxAndAnd, lxXOr, lxTilda, lxNot,
				   lxPlusPlus, lxMinusMinus,
				   lxEqu, lxNotEqu, lxLT, lxLE, lxGT, lxGE,
				   lxLShift, lxRShift, lxLShiftAssign, lxRShiftAssign,
				   lxLeftCramp, lxRightCramp, lxLeftBracket, lxRightBracket, lxLeftScrape, lxRightScrape, lxQuestion,
				   lxColonColon, lxSlach, lxPoint, lxComma, lxSemicolon, lxColon, lxUnaryAdd, lxUnarySub, lxPostInc, lxPostDec,
               lxPointer, lxEllipsis, 
               lxModMod, lxModBegin, lxModEnd, lxModToken, lxModLeft, lxModRight,
               lxBNFSet,
               lxDefine, lxUndef, lxIfdef, lxIfndef, lxElse, lxEndif, lxLeftMaker, lxRightMaker,
               lxHint, lxBegHint, lxEndHint, lxAt, lxRZShift, lxRZShiftAssign,
               _lx_end_
				   };
   enum T_Priority {
               prNone, prAssign, prQuestion, prOrOr, prAndAnd, prOr, prXOr, prAnd, prEqu, prCompare, prShift, 
               prTerm, prFactor, prUnary, prIncDec
               };
   enum M_Mask {
               mmInclude = 0x0000FFFF, mmExclude = mmInclude << 16, mmAll  = mmInclude, mm = mmAll, 
               mmTran = 0x00000001, mmNoTran = mmTran << 16, mmGrammar = 0x00000002, mmNoGrammar = mmGrammar << 16,
               mmC    = 0x00000004, mmNoC    = mmC    << 16, mmC_99    = 0x00000008, mmNoC_99    = mmC_99    << 16,
               mmBNF  = 0x00000010, mmNoBNF  = mmBNF  << 16, mmIfdef   = 0x00000020, mmNoIfdef   = mmIfdef   << 16,
               mmSQL  = 0x00000040, mmNoSQL  = mmSQL  << 16,
               mmJAVA = 0x00000080
               };
}; 

// --------------------------- T_Lexeme ---------------------------

#define C99_GRAMMAR 

struct T_Scan;
struct T_WordTable;
struct T_Lexeme
{
	enum T_Group  { grNone, grOper, grSeparator, grInteger, grNumber, grString, grIdent, grReserv, grSpace, grLine, grError, grPriority, grSyntax, grEof, 
                   grPreproc, grMeta, grGrammar
                 };
	enum T_Type   { lxNone, lxSpace, lxComment, lxEol
				     };
	enum W_Type   { rwNone, rwFor, rwWhile, rwIf, rwElse, rwDo,
                   rwGoTo, rwContinue, rwBreak, rwReturn, rwSwitch, rwCase, rwTry, rwThrow, rwCatch, rwEnum, rwDefault, 
                   /* define types */
                   rwVoid, rwShort, rwInt, rwLong, rwFloat, rwDouble, 
                   /*    ordnung   */
                   rwDefine, rwConst, rwStatic,  
                   rwAuto, rwChar, rwExtern, rwRegister, rwSigned, rwSizeof, rwStruct, rwTypedef, rwUnion, rwUnsigned, rwVolatile
#ifdef C99_GRAMMAR 
                  ,rwBool, rwComplex, rwImaginary, rwInline, rwRestrict
#endif
                  ,rwAll, rwMake, rwNode, rwCode, rwTree, rwYacc, rwTurn, rwCall, rwClass,

                  rwPackage,  rwImport, rwPublic, rwAbstract, rwFinal, rwExtends, rwImplements, rwProtected, rwPrivate, rwThrows, rwThis,
                  rwSuper, rwTransient, rwSynchronized, rwNative, rwInterface, rwBoolean, rwByte, rwFinally, rwInstanceof, 
                  rwNew, rwNull
				     };
   enum T_Syntax { sxNone, sxIdentFunc, sxIdentArr, sxDefFunc, sxDefArr, sxDefVar, sxDefType, sxLabel, sxCast, sxCastUnary, sxEmptyCramp, sxEmptyBracket, sxEmptyScrape
				     };
	T_Group group;
	int     type;
	int     pos, len, line, column;
	int     value;
public:
   const char* text;
public:
	T_Lexeme() : group(grNone), type(lxNone), pos(0), len(0), line(0), column(0), value(0), text(NULL) {}
	T_Lexeme(T_Group g, int t) : group(g), type(t), pos(0), len(0), line(0), column(0), value(0), text(NULL) {}
   const char* Text() const                     { return text; }
	bool Match(T_Lexeme::T_Group g) const        { return (group == g); }
	bool Match(T_Lexeme::T_Group g, int t) const { return (group == g) && (type == t); }
	bool Match(A_Symbol::T_Type t) const;
	bool Match(A_Symbol::T_Priority priority) const;
	bool Match(T_Lexeme::W_Type keyword) const;
	bool Match(const T_Lexeme &l) const;
	bool Real();
   bool IsSaved() const;
   bool IsNone() const { return (group == T_Lexeme::grNone); }
   bool Cast();
   void set(T_Lexeme::T_Group g, int t)         { group = g; type = t; }
public:
	void print(TPrinter& printer, const T_Scan *scan) const; // 0x01 - eol, 0x02 - !pos
   int  print(TPrinter& printer) const;
   void print(const T_Scan *scan = NULL, int mode = 0x01) const { TPrinter printer(mode); print(printer, scan); }// 0x01 - eol, 0x02 - !pos
   void write(TWriter& printer, const T_Scan *scan = NULL) const;
   int  YACC (TPrinter& printer);
public:
   static T_Scan *print_scan;
   static const T_WordTable* word_table;
};

const char* group_title(T_Lexeme::T_Group g);
const char* lexeme_word_title(T_Lexeme::W_Type w);  
const char* lexeme_type_title(A_Symbol::T_Type t);
const char* lexeme_syntax_title(T_Lexeme::T_Syntax s);  
const char* lexeme_priority_title(A_Symbol::T_Priority p); 
T_Lexeme::T_Group title_group(const char* t);
A_Symbol::T_Type title_type(const char* t);
T_Lexeme::W_Type title_word(const char* t);
T_Lexeme::T_Syntax title_syntax(const char* t) ;
A_Symbol::T_Priority title_priority(const char* t);

// --------------------------- T_Symbol ---------------------------
struct T_Symbol : A_Symbol
{
	T_Lexeme::T_Group group;
	T_Type            type;
   T_Priority        priority;
	const char* text;
   int index;
   unsigned int mask;
	T_Symbol() : group(T_Lexeme::grNone), type(T_Symbol::lxNone), priority(prNone), text(NULL), index(-1), mask(A_Symbol::mmAll), oper_index(0), oper_count(0) {}
	T_Symbol(T_Lexeme::T_Group g, T_Symbol::T_Type t, const char* s, unsigned int m = A_Symbol::mmAll) : group(g), type(t), priority(prNone), text(s), index(-1), mask(m), oper_index(0), oper_count(0) {}
	T_Symbol(T_Lexeme::T_Group g, T_Symbol::T_Type t, const char* s, T_Priority p, unsigned int m = A_Symbol::mmAll) : group(g), type(t), priority(p), text(s), index(-1), mask(m), oper_index(0), oper_count(0) {}
	bool Compare(T_Lexeme &lex, T_Scan &scan) const;
public: // TSemantic
   void MakeOper(const int oper) const { if (!oper_count++) oper_index = oper; }
   mutable int oper_index, oper_count;
}; 

// --------------------------- T_SymbolTable ---------------------------

struct T_SymbolTable
{
	T_Symbol table[T_Symbol::_lx_end_];
	int count;
	T_SymbolTable();
	void Add(const T_Symbol &sym);
	bool inside(int sym) const                       { return (0 <= sym) && (sym < count); }
	const T_Symbol& Symbol(int index) const          { return table[index]; }
	const T_Symbol& Symbol(T_Symbol::T_Type t) const { return Symbol(Symbol((int)t).index); }
   const T_Symbol* Symbol(const char* text) const;
	const char* Text(T_Symbol::T_Type t) const       { return Symbol(t).text; }
	bool Find(T_Lexeme &lex, T_Scan &scan) const;
	bool Find(const char* text, T_Lexeme &lex) const;
	bool Find(char c, T_Lexeme &lex) const;
   void Change(T_Lexeme &lex,T_Symbol::T_Type t) const;
	void print() const;
public:
   mutable A_Symbol::M_Mask mask;
private:
   bool make;
}; 

const T_SymbolTable& symbol_table();

// --------------------------- T_Scan ---------------------------

struct T_ScanStore
{
   T_ScanStore() :store_pos(0), store_line(0), store_lexeme(0), store_node(0), store_tree(0), store_type(0) {}
public:
   int  store_pos, store_line; // scan
   int  store_lexeme, store_node, store_tree, store_type; // syntax
};

struct CharsKey {
   CharsKey(const char* k) :key(k) {}
   const char* key;
   bool operator == (const CharsKey& k) const { return strcmp(key, k.key) == 0; }
   bool operator <  (const CharsKey& k) const { return strcmp(key, k.key) <  0; }
};

class TNameTable {
public:
   TNameTable() :index(0) {}
   ~TNameTable();
public:
   int Add(const char* name);
   int Add(T_Scan &scan, T_Lexeme &l);
   int Add(const char* name, T_Lexeme &l);
   int Find(const char* name) const;
   int Index() { return index++; }
   int Count() const { return (int)indexs.size(); }
   const char* Name(int index) const;
public:
   void Clear();
   void Zero();
public:
   struct Key {
      Key(const char* k) :key(k) {}
      const char* key;
      bool operator == (const Key& k) const { return strcmp(key,k.key) == 0; }
      bool operator <  (const Key& k) const { return strcmp(key,k.key) <  0; }
   };
   class TNameIndex : public std::map<const Key, const int> {
   } indexs;
   std::vector<const char*> names;
protected:
   int index;
};

struct T_WordTable;
struct T_Scan
{
public:
   T_Scan(T_Source *s);
   ~T_Scan();
public:
   virtual T_Lexeme::T_Group Lex(T_Lexeme &l);
	virtual void Store(T_ScanStore& store)         { store.store_pos = store_pos; store.store_line = old_line; }
   virtual bool Restore(const T_ScanStore& store) { if (source->Pos() == store.store_pos) return false; source->Pos(store.store_pos); line = store.store_line; return true; }
   virtual int  Current()         { return Pos(); }
	T_Source::T_Sym Read(int &sym) { return source->Read(sym); }
	int  Char(int pos) const       { return source->Char(pos); }
	int  Pos()  const              { return source->Pos(); }
	void Back() const              { source->Back(); }
	void Reset()                   { source->Reset(); line = 0; beg_line = 0; store_pos = 0; old_line = 0; }
	int  compare(const T_Lexeme &l, const T_Lexeme &r) const;
	bool Compare(T_Lexeme &l, const char* title) const;
	bool Compare(const T_Lexeme &l, const T_Lexeme &r) const;
   const char* Text(const T_Lexeme &l) const;
   int  Integer(const T_Lexeme &l) const;
   double Number(const T_Lexeme &l) const;
   int  Integer(int value);
   int  Number(const double& value);
   T_Source::T_Type SourceType() const { return (!source) ? T_Source::ftNone : source->Type(); }
public:
   int  line, beg_line;
   int  store_pos, old_line;
   A_Symbol::M_Mask mask;
public:
   TNameTable names;
   T_Source *source;
   const T_WordTable* word_table;
public:
   std::vector<int> integers;
   std::vector<double> numbers;
};

// --------------------------- T_SourceFile ---------------------------

struct T_SourceFile : T_Source
{
	FILE *file;
	T_SourceFile() : T_Source(), file(NULL) {}
	T_SourceFile(const char* name) : T_Source(name), file(NULL) {}
	bool Open(const char* name = NULL);
	void Close() { if (file) fclose(file); file = NULL; }
	virtual int  Char(int pos) const;
   virtual T_Type Type() const;

}; 

// --------------------------- TScanArray ---------------------------

class TScanArray : public T_Scan, public  std::vector<T_Lexeme> 
{
public:
	TScanArray(T_Source *s) : T_Scan(s), index(0), make(false) {}
	virtual T_Lexeme::T_Group Lex(T_Lexeme &l);
   virtual T_Lexeme::T_Group LexMake(T_Lexeme &l) { return T_Scan::Lex(l); }
   virtual void Store(T_ScanStore& store)    { store.store_pos = index ? index - 1 : 0; }
   virtual bool Restore(const T_ScanStore& store)  { if (!index || index == store.store_pos + 1) return false; index = store.store_pos; return true; }
   virtual int  Current()         { return index ? index - 1 : 0; }
   virtual bool Make();
	void Reset()                   { index = 0; }
public:
	int index;
private:
   bool make;
}; 

enum T_Error {
   er__Warning__ = 0x01000000, er__Maska__ = 0x0000FFFF,
   erNone = 0x0000, erSymbol, erEnd, erNoEnd, erPrimary, erNoInteger, erNoIdent, erNoValue, erDefArr, erDefFunc, erDefine, erDefVoid, erStatement, erSwitch,
   erUnknownIdent, erDuplicateIdent, erBreak, erContinue, erUnknownOper, erUnknownCast, erUnknownParam, erUnknownFunc, erDuplicateBody, erUnknownBody,
   erUnknownLabel, erDuplicateLabel, erErrorLabel, er_UnusedLabel, erInvalidType, erNoReturn, erRanges, erUninitialized, erInvalidInit, erImpossible,
   erUnusedLabel = er_UnusedLabel | er__Warning__
};

#include <set>

// --------------------------- TIfdefScan ---------------------------
struct TIfdefScan : public TScanArray
{
public:
   TIfdefScan(T_Source *s) : TScanArray(s) {}
   virtual T_Lexeme::T_Group LexMake(T_Lexeme &l);
   virtual bool Make();
   bool GetIdent(T_Lexeme &l);
   void AddDef(const char* name);
   void DelDef(T_Lexeme &l);
   bool Find(const T_Lexeme &l) const { return definitions.find(CharsKey(l.text)) != definitions.end(); }
   void Reset() { definitions.clear(); TScanArray::Reset(); }
   void Error(T_Lexeme &lex, T_Error e);
public:
   void print_def(TPrinter& printer) const;
public:
   std::set<CharsKey> definitions;
   T_Lexeme error_lex;
};

// --------------------------- T_Parse ---------------------------
class TTokenNames;

struct T_Parse 
{
	int option; // print(0x01 - other, 0x02 - space, 0x04 - line, 0x08 - eof, 0x10 - lexeme, 0x20 - erase_code, 0x40 - print_code, 0x80 - print_operator, 
               //       0x0100 - print_rule, 0x0200 - print_maker )
	bool line_is_space;
	T_Parse(T_Scan *s) : scan(s), lex(), forward(), option(0), line_is_space(false), store_count(0), restore_count(0) {}
	T_Lexeme::T_Group Lex(T_Lexeme &l);
	T_Lexeme::T_Group T_Scan__Lex(T_Lexeme &l);
	const T_Lexeme& Cur() { SkipSpace(); return lex; }
	T_Scan& Scan() { return *scan; }
   void Scan(T_Scan *s) { scan = s; }
   void Mask(A_Symbol::M_Mask mask);
   A_Symbol::M_Mask Mask() const { return scan->mask; }
   bool Compare(const T_Lexeme &l, const T_Lexeme &r) const { return scan->Compare(l,r); }
	void SkipSpace();
	bool Match(T_Lexeme::T_Group group);
	bool Match(T_Lexeme::T_Group group, int type);
	bool Match(T_Lexeme &l, T_Lexeme::T_Group group);
	bool Match(T_Lexeme &l, T_Lexeme::T_Group group, int type);
	bool Match(T_Symbol::T_Type t);
	bool Match(T_Symbol::T_Priority priority);
	bool Match(T_Lexeme &l, T_Symbol::T_Priority priority);
	bool Match(T_Lexeme::W_Type keyword);
	bool Match(T_Lexeme &l, T_Lexeme::W_Type keyword);
	bool Match(const T_Lexeme &l);
	bool MatchSpot(T_Lexeme &l, T_Lexeme::T_Group group);
	bool MatchSpot(T_Lexeme::W_Type keyword);
	bool MatchSpot(T_Symbol::T_Type t);
	bool MatchSpot(T_Symbol::T_Priority priority);
	bool Next();
	void Reset();
   void Change(T_Lexeme &l,T_Symbol::T_Type t);
   void ChangeUnary(T_Lexeme &l, bool only_term);
   T_Source::T_Type SourceType() const { return (!scan) ? T_Source::ftNone : scan->SourceType(); }

public:
   virtual void Store(T_ScanStore& store)         { scan->Store(store); store_count++; }
   virtual bool Restore(const T_ScanStore& store) { if (!scan->Restore(store)) return false; lex.set(T_Lexeme::grNone,T_Lexeme::lxNone); SkipSpace(); restore_count++; return true; }
   virtual int  Current()                         { return scan->Current(); }
public:
   int  Integer(const T_Lexeme &l) const { return scan->Integer(l); }
   double Number(const T_Lexeme &l) const { return scan->Number(l); }
   const char* Text(const T_Lexeme &l) const { return scan->Text(l); }
   int Integer(int value) { return scan->Integer(value); }
   int Number(const double& value) { return scan->Number(value); }
public:
   void MakeTokens(TTokenNames& tokens, int mode = 0x00);
   void WordTable(const T_WordTable* word_table) { scan->word_table = word_table; }
public:
	T_Lexeme forward, lex;
public:
   int store_count, restore_count;
public:
	static T_Lexeme empty_ident, oper_assign;
private:
	T_Scan *scan;
public:
   T_Lexeme last_key_word, last_lexeme;
};

// --------------------------- T_Word ---------------------------
struct T_Word
{
public:
   T_Word() : type(0), text(NULL), mask(A_Symbol::mmAll), title(NULL) {}
	T_Word(int t, const char *w, const char *l, unsigned int m = A_Symbol::mmAll) : type(t), text(w), mask(m), title(l) {}
	bool Compare(const T_Lexeme &lex, T_Scan &scan) const;
public:
   int          type;
   const char*  text;
   unsigned int mask;
   const char*  title;
};

struct T_WordTable
{
	static const int TABLE_LENGTH = 500;
	T_Word table[TABLE_LENGTH];
	int count;
	T_WordTable() : count(0), mask(A_Symbol::mmTran) {}
	void Add(const T_Word &word)   { if (count < TABLE_LENGTH) table[count++] = word; }
	bool inside(int word) const    { return (0 <= word) && (word < count); }
	const T_Word& Word(int index) const { return table[index]; }
   const T_Word& Word(T_Lexeme::W_Type w) const;
   int  Index(T_Lexeme::W_Type w) const;
   bool Find(T_Lexeme &lex, T_Scan &scan) const;
   bool Find(T_Lexeme &lex) const;
   //	void print() const;
public:
   mutable A_Symbol::M_Mask mask;
}; 

// --------------------------- T_KeyWordTable ---------------------------
struct T_KeyWordTable : T_WordTable
{
	T_KeyWordTable();

	static const T_KeyWordTable key_word_table;

}; 

// --------------------------- TTokenNames ---------------------------
class TTokenNames : public TNameTable
{
public:
   TTokenNames() : TNameTable() {}
public:
   int Add(const char* group, const char* type, int token);
   int Token(int index) const { return tokens[index]; }
public:
   void print(TPrinter& printer) const;
public:
   std::vector<int> tokens;
};


// --------------------------- T_Xxxxxx ---------------------------

enum T_Part { 
   psNone = 0x00, psDefine = 0x01, psDefFunc = 0x02, psStatement = 0x04, psCompaund = 0x08, psExpression = 0x10, psNoSemicolon = 0x20, psOneDef = 0x40, 
   psIfGoTo    = 0x80, psValue = 0x0100, psValueList = 0x0200,
   psMain      = psDefine | psDefFunc,
   psBody      = psDefine | psStatement | psCompaund | psExpression,
   psLabel     = psDefine | psStatement | psCompaund | psExpression,
   psCase      =            psStatement | psCompaund | psExpression,
   psForBeg    = psDefine | psExpression,
   psForExpr   = psDefine | psExpression | psIfGoTo | psOneDef,
   psCondition = psDefine | psExpression | psIfGoTo | psOneDef | psNoSemicolon
};

enum T_PrintMode {   pmNone        = 0x00000000, 
   pmPrintItem   = 0x00000001, pmLexemePart    = 0x00000001, pmPrintPrefix = 0x00000001,
   pmCompact     = 0x00000004, pmRuleUsed      = 0x00000004,
   pmMultiLine   = 0x00000100, pmOffset        = 0x00000200, pmSpaces      = 0x00000400,
   pmYACCStack   = 0x00000100, pmNoPrintNone   = 0x00000200, pmSortMode    = 0x00000400, pmCompactGroup  = 0x00000800,
   pmBasic       = 0x00000100, 
   pmSimplePara  = 0x00001000, pmTableLLk      = 0x00002000, pmEofToEmpty  = 0x00004000, pmWithoutMaster = 0x00008000,
   pmGrammar     = 0x00010000, pmBNF           = 0x00020000, pmBIF         = 0x00040000, pmProduceHead   = 0x00080000,
   pmFormulaHead = 0x00010000, pmParamMacro    = 0x00020000, pmProduceOnly = 0x00400000,
   pmYACCMode    = 0x01000000, pmNoGroupLexeme = 0x02000000, pmMacroMode   = 0x04000000, 
   pmSymbolOper  = pmCompact,
   pmMakerNone   = 0x00000000, pmMakerItem     = 0x00000001, pmMakerCompact= 0x00000004,
   pmWriteSimple = 0x00000001, pmWriteZero     = 0x00000002, pmWriteSymbol = 0x00000003, pmWriteProg     = 0x00000004,
   pmProgHeader  = 0x00000001, pmProgBody      = 0x00000002, pmProgCall    = 0x00000003, pmProgList      = 0x00000004,
   pmAutoHeader  = 0x00000005, pmAutoBody      = 0x00000006
};

enum T_OptionMode {   omNone    = 0x00000000,
    omPrintOther    = 0x00000001, omPrintSpace   = 0x00000002, omPrintLine   = 0x00000004, omPrintLexeme   = 0x00000008,
    omPrintTree     = 0x00000010, omEraseCode    = 0x00000020, omPrintCode   = 0x00000040, omPrintOperator = 0x00000080,
    omPrintRule     = 0x00000100, omPrintMaker   = 0x00000200, omPrintStack  = 0x00000400, omPrintCodes    = 0x00000800,
    omPrintSNode    = 0x00001000, omPrintSyntax  = 0x00002000, omPrintSource = 0x00004000, omPrintSemantic = 0x00008000,
    omSelectProduce = 0x00010000, omTrimUnit     = 0x00020000, omAutoTree    = 0x00040000, omTreeTraversal = 0x00080000,
    omQuadruple     = 0x00100000, omAtOnce       = 0x00200000, omAutoNoDigit = 0x00400000, omSyntaxOnly    = 0x00800000,
    omWriteLexeme   = 0x01000000
};

const char* syntax_error_title(T_Error e);  
T_Error title_error(const char* t);

char* get_file_name(const char*file, const char* ext);
int   get_file_type(const char*file);

int print_source(T_Source &source, const char* file_name = NULL);
int scan_source(T_Parse &scan);

#endif

