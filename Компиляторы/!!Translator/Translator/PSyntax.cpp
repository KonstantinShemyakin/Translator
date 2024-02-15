
#include "stdafx.h"

#include "PSyntax.h"
#include "TSemantic.h"

bool P_Syntax::Translate()
{
   makers = &GMakerTable::maker_table;
   bool ret = translate() > 0;

   return ret;
}
