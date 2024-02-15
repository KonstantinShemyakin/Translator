class PSyntax : public P_Syntax {
public:
   PSyntax(T_Scan *s, TGrammar* g) :P_Syntax(s,g) {}
   virtual int translate() { return S_(); }
public:
   int S__0(); 
   int S_();
   int rules_0(); 
   int rules();
   int _f_00002__0(); 
   int _f_00002_();
   int rule_0(); 
   int rule();
   int item_list_0(); 
   int item_list();
   int _f_00005__0(); 
   int _f_00005_();
   int item_symbol_0();    int item_symbol_1(); 
   int item_symbol();
   int item_0();    int item_1();    int item_2();    int item_3(); 
   int item();
   int _f_00008__0();    int _f_00008__1();    int _f_00008__2(); 
   int _f_00008_();
   int _f_00009__0();    int _f_00009__1(); 
   int _f_00009_();
   int _f_00010__0();    int _f_00010__1(); 
   int _f_00010_();
   int _f_00011__0();    int _f_00011__1(); 
   int _f_00011_();
   int _f_00012__0();    int _f_00012__1(); 
   int _f_00012_();
   int or_list_0(); 
   int or_list();
   int _f_00014__0(); 
   int _f_00014_();
   int Ident_Maker_0();    int Ident_Maker_1();    int Ident_Maker_2();    int Ident_Maker_3();    int Ident_Maker_4(); 
   int Ident_Maker();
   int node_body_0();    int node_body_1();    int node_body_2();    int node_body_3();    int node_body_4(); 
   int node_body();
   int int_body_0();    int int_body_1();    int int_body_2();    int int_body_3(); 
   int int_body();
};
