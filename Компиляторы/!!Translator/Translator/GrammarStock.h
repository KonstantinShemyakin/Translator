#ifndef TRN_GRAMMAR_STOCK_H
#define TRN_GRAMMAR_STOCK_H

class TGrammar;

enum T_Stock {
              msNone     = 0x000000, 

              msMedia    = 0x0F0000, msMASK = 0x00F000, msPhase      = 0xF0000000,
                                     msTree = 0x001000, msOnePhase   = 0x10000000,
              msMFormula = 0x020000, msCode = 0x002000, msTwoPhase   = 0x20000000,
              msMCpp     = 0x030000, msNode = 0x003000, msThreePhase = 0x30000000,
              msMTab     = 0x040000, msTurn = 0x004000, 
              msMGrammar = 0x050000, msMade = 0x005000,
                                     msMake = 0x006000,

              msGrammar  = 0x000FFF, msLLLR = 0x000800,
              msLL       = 0x000801,  
              msNL       = 0x000802, 
              msLR       = 0x000003, 
              msNR       = 0x000004,
              msETF_LL   = 0x000805,
              msETF_LR   = 0x000006,
              msEEE      = 0x000007,
              msEbEpE    = 0x000008,
              msEXPR_LR  = 0x00000C,         
             };

bool build_grammar(TGrammar &table, int option_mode, int mode); // 0x02 - !make
bool grammar_build(TGrammar &table, int stock_mode, int mode); // 0x02 - !make

#endif
