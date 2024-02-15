#ifndef TRN_PARSE_H
#define TRN_PARSE_H
 
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
               _lx_end_
				   };
   enum T_Priority {
               prNone, prAssign, prQuestion, prOrOr, prAndAnd, prOr, prXOr, prAnd, prEqu, prCompare, prShift, 
               prTerm, prFactor, prUnary, prIncDec
               };
   enum M_Mask {
               mmInclude = 0x0000FFFF, mmExclude = mmInclude << 16, mmAll  = mmInclude, mm = mmAll, 
               mmTran = 0x00000001, mmNoTran = mmTran << 16, mmGrammar = 0x00000002, mmNoGrammar = mmGrammar << 16,
               mmC    = 0x00000004, mmNoC    = mmC    << 16, mmC_99    = 0x00000008, mmNoC_99    = mmC_99    << 16
               };
}; 

// --------------------------- T_Lexeme ---------------------------

#define C99_GRAMMAR 

struct T_Scan;
struct T_Lexeme
{
	enum T_Group  { grNone, grOper, grSeparator, grInteger, grNumber, grString, grIdent, grReserv, grSpace, grLine, grError, grPriority, grSyntax, grEof };
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
                  ,rwALL, rwMAKE, rwNODE, rwCODE, rwTREE, rwYACC, rwTURN, rwClass
				     };
   enum T_Syntax { sxNone, sxIdentFunc, sxIdentArr, sxDefFunc, sxDefArr, sxDefVar, sxDefType, sxLabel, sxCast, sxCastUnary, sxEmptyCramp, sxEmptyBracket, sxEmptyScrape
				     };
	T_Group group;
	int     type;
	int     pos, len, line, column;
	int     value;
	double  number;
public:
   const char* text;
public:
	T_Lexeme() : group(grNone), type(lxNone), pos(0), len(0), line(0), column(0), value(0), number(0.0), text(NULL) {}
	T_Lexeme(T_Group g, int t) : group(g), type(t), pos(0), len(0), line(0), column(0), value(0), number(0.0), text(NULL) {}
   const char* Text() const                     { return text; }
	bool Match(T_Lexeme::T_Group g) const        { return (group == g); }
	bool Match(T_Lexeme::T_Group g, int t) const { return (group == g) && (type == t); }
	bool Match(A_Symbol::T_Type t) const;
	bool Match(A_Symbol::T_Priority priority) const;
	bool Match(T_Lexeme::W_Type keyword) const;
	bool Match(const T_Lexeme &l) const;
   bool IsSaved() const;
   bool Cast();
   void set(T_Lexeme::T_Group g, int t)         { group = g; type = t; }
public:
	void print(const T_Scan *scan = NULL, bool eol = true, FILE *file = stdout) const;
	void write(const T_Scan *scan = NULL, FILE *file = stdout) const;
   static int print(T_Lexeme::T_Group g, int t, int mode = 0x00, FILE *file = stdout);
   static int YACC (FILE *file, T_Lexeme::T_Group g, int t, int mode = 0x00);
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


#endif

