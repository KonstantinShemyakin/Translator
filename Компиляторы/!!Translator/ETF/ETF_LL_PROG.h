class PSyntax : public P_Syntax {
public:
   PSyntax(T_Scan *s, TGrammar* g) :P_Syntax(s,g) {}
   virtual int translate() { return ETF_LL_S_(); }
public:
   int ETF_LL_S__0(); 
   int ETF_LL_S_();
   int ETF_LL_E_0(); 
   int ETF_LL_E();
   int ETF_LL_E__0(); 
   int ETF_LL_E_();
   int ETF_LL_T_0(); 
   int ETF_LL_T();
   int ETF_LL_T__0(); 
   int ETF_LL_T_();
   int ETF_LL_F_0();    int ETF_LL_F_1(); 
   int ETF_LL_F();
};
