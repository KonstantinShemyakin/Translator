//void r011() { return; } void f011() { int i=0,j=i; L1:i=12; { int k; goto L15; L15: goto L2; } {{ int jjj; L2: ; }} }

void r011() { goto L15; L15: ; }