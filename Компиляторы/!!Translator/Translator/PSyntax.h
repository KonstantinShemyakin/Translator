#ifndef TRN_PSYNTAX_H
#define TRN_PSYNTAX_H

#include "Maker.h"
 
// --------------------------- PSyntax ---------------------------
class P_Syntax : public MC_Syntax
{
public:
	P_Syntax(T_Scan *s, TGrammar* g) :MC_Syntax(s), grammar(g) {}

   virtual bool Translate();
   virtual int translate() { return 0; }

public:
   TGrammar*  grammar;
};

#endif

