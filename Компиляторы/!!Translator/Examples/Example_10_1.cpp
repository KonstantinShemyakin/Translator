void f_goto() { int i; l1: { int j; goto l1; l2: { int k; goto l1; } } }
