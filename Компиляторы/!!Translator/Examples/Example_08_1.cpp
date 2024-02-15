void f_if() { int i,j; if (i > 0) j++; }
void f_if_else() { int i,j; if (i > 0) j++; else --j;  if (1) ++j; else j--;}
void f_do() { int i, j, k; do { k++; } while (i > j); }
void f_while() { int i, j, k; while (i > j) { k++; } }
void f_for() { int j, k; for (int i = 0; i < 10; i++) { j = k; } }
void f_for_null() { for (;;); }
