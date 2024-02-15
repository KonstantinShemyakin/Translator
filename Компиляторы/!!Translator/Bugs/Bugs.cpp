/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bugs.cpp
 * Author: svaganov
 *
 * Created on August 2, 2018, 1:59 PM
 */

#include <cstdlib>
#include <stdio.h>

#include <vector>

enum T_BaseType {
   btVoid   = 0x0000, btShort   = 0x0001, btInt   = 0x0002, btLong   = 0x0003, btFloat   = 0x0004, btDouble   = 0x0005,
   btCVoid  = 0x0100, btCShort  = 0x0101, btCInt  = 0x0102, btCLong  = 0x0103, btCFloat  = 0x0104, btCDouble  = 0x0105,
   btRVoid  = 0x0200, btRShort  = 0x0201, btRInt  = 0x0202, btRLong  = 0x0203, btRFloat  = 0x0204, btRDouble  = 0x0205,
   btCRVoid = 0x0300, btCRShort = 0x0301, btCRInt = 0x0302, btCRLong = 0x0303, btCRFloat = 0x0304, btCRDouble = 0x0305,
   btConst  = 0x0100, btReference = 0x0200, btStatic = 0x0400, btConstReference = btConst | btReference, btType  = 0x000F,
   btUnknown = 0x80000000
};

struct T_Symbol
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
               _lx_end_
				   };
}; 

class TOperProfile : public std::vector<T_BaseType> {
public:
   TOperProfile() :oper(T_Symbol::T_Type::lxNone), result(btUnknown) {}
   TOperProfile(T_Symbol::T_Type o, T_BaseType e, T_BaseType l) :oper(o), result(e) { Add(l); }
   TOperProfile(T_Symbol::T_Type o, T_BaseType e, T_BaseType l, T_BaseType r) :oper(o), result(e) { Add(l); Add(r); }
	void Add(T_BaseType p) { push_back(p); }
public:
   T_Symbol::T_Type oper;
   T_BaseType result;
};

class TOperTable : public std::vector<TOperProfile> {
public:
   TOperTable() {}   
};

#define BUG_STATIC
#define BUG_MAKE

#ifdef BUG_STATIC
   static TOperTable OperTable;
#endif

// --------------------------- TSemantic ---------------------------

class TSemantic
{
public:
	TSemantic();
public:
   void MakeBinaryOper(T_Symbol::T_Type oper, T_BaseType result, T_BaseType left, T_BaseType right);
   void MakeUnaryOper(T_Symbol::T_Type oper, T_BaseType result, T_BaseType param);
   void MakeOperTable();
#ifndef BUG_STATIC
public:
   TOperTable OperTable;
#endif
};

TSemantic::TSemantic()
#ifndef BUG_STATIC
   :OperTable()
#endif
{
   int count = (int)OperTable.size();
   printf("mmmmmmmmmmmmmmmm %d\n", count);
   MakeOperTable();
   count = (int)OperTable.size();
   printf("eeeeeeeeeeeeeeee %d\n", count);
}

void TSemantic::MakeBinaryOper(T_Symbol::T_Type oper, T_BaseType result, T_BaseType left, T_BaseType right)
{
   TOperProfile profile(oper, result, left, right);
   OperTable.push_back(profile);
}
void TSemantic::MakeUnaryOper(T_Symbol::T_Type oper, T_BaseType result, T_BaseType param)
{
   TOperProfile profile(oper, result, param);
   OperTable.push_back(profile);
}

#ifdef BUG_MAKE
   #define MAKE_BINARY(OPER, RESULT, LEFT, RIGHT) \
      MakeBinaryOper(T_Symbol::lx##OPER, T_BaseType::bt##RESULT, T_BaseType::bt##LEFT, T_BaseType::bt##RIGHT);
#else
   #define MAKE_BINARY(OPER, RESULT, LEFT, RIGHT) \
      MakeUnaryOper(T_Symbol::lx##OPER, T_BaseType::bt##RESULT, T_BaseType::bt##LEFT); \
      OperTable.back().Add(T_BaseType::bt##RIGHT);
#endif
#define MAKE_UNARY(OPER, RESULT, PARAM) MakeUnaryOper(T_Symbol::lx##OPER, T_BaseType::bt##RESULT, T_BaseType::bt##PARAM);

void TSemantic::MakeOperTable()
{
   MAKE_BINARY(Add          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Add          ,CDouble,CDouble,CDouble)
   MAKE_BINARY(Sub          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Sub          ,CDouble,CDouble,CDouble)
   MAKE_BINARY(Multi        ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Multi        ,CDouble,CDouble,CDouble)
   MAKE_BINARY(Div          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Div          ,CDouble,CDouble,CDouble)
   MAKE_BINARY(Mod          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Or           ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(And          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(OrOr         ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(AndAnd       ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(XOr          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Equ          ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(Equ          ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(NotEqu       ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(NotEqu       ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(LT           ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(LT           ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(LE           ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(LE           ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(GT           ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(GT           ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(GE           ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(GE           ,CInt   ,CDouble,CDouble)
   MAKE_BINARY(LShift       ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(RShift       ,CInt   ,CInt   ,CInt   )
   MAKE_BINARY(LShiftAssign ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(RShiftAssign ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(ModAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(AndAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(OrAssign     ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(XOrAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(Assign       ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(Assign       ,CDouble,RDouble,CDouble)
   MAKE_BINARY(AddAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(AddAssign    ,CDouble,RDouble,CDouble)
   MAKE_BINARY(SubAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(SubAssign    ,CDouble,RDouble,CDouble)
   MAKE_BINARY(MultiAssign  ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(MultiAssign  ,CDouble,RDouble,CDouble)
   MAKE_BINARY(DivAssign    ,CInt   ,RInt   ,CInt   )
   MAKE_BINARY(DivAssign    ,CDouble,RDouble,CDouble)
   MAKE_UNARY (UnaryAdd     ,CInt   ,CInt   )
   MAKE_UNARY (UnaryAdd     ,CDouble,CDouble)
   MAKE_UNARY (UnarySub     ,CInt   ,CInt   )
   MAKE_UNARY (UnarySub     ,CDouble,CDouble)
   MAKE_UNARY (Not          ,CInt   ,CInt   )
   MAKE_UNARY (Not          ,CInt   ,CDouble)
   MAKE_UNARY (Tilda        ,CInt   ,CInt   )
   MAKE_UNARY (PlusPlus     ,RInt   ,RInt   )
   MAKE_UNARY (PlusPlus     ,RDouble,RDouble)
   MAKE_UNARY (MinusMinus   ,RInt   ,RInt   )
   MAKE_UNARY (MinusMinus   ,RDouble,RDouble)
   MAKE_UNARY (PostInc      ,CInt   ,RInt   )
   MAKE_UNARY (PostInc      ,CDouble,RDouble)
   MAKE_UNARY (PostDec      ,CInt   ,RInt   )
   MAKE_UNARY (PostDec      ,CDouble,RDouble)
}

int main(int argc, char** argv) 
{
   TSemantic semantic;
   return 0;
}
