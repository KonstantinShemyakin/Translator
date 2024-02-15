class PSyntax : public P_Syntax {
public:
   PSyntax(T_Scan *s, TGrammar* g) :P_Syntax(s,g) {}
   virtual int translate() { return S_(); }
public:
   int S__0(); 
   int S_();
   int E_0(); 
   int E();
   int E__0();    int E__1(); 
   int E_();
   int T_0(); 
   int T();
   int T__0();    int T__1(); 
   int T_();
   int F_0();    int F_1();    int F_2();    int F_3(); 
   int F();
};
