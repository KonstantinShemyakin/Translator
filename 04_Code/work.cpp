�������������� ���������
	int a; int b; int c; c = (a + 5) * (6 - b); 
	int a; int b; int c; c = (((((a + 1) + 2) + 3) + 4) + 5); // tree
	int a; int b; int c; c = (1 + (2 + (3 + (4 + (5 + a))))); // tree
���������� ���������
	int a; int b; int c; a & b; a && b; a | b; a || b;
	int a; int b; int c; (a || b) && (a || c);
	int a; int b; int c; c = (((((a || 1) || 2) || 3) || 4) || 5); // tree         
	int a; int b; int c; c = (1 || (2 || (3 || (4 || (5 || a))))); // tree
	int a; int b; int c; c = (a || b) && (a || 1);
	int a; int b; int c; c = (a || 1); c = (1 || a); c = (a && 1); c = (1 && a);
	int a; int b; int c; c = (a || 0); c = (0 || a); c = (a && 0); c = (0 && a);
	
����������� ����������
	int i; int j; int k;
	int i, j, k;
	int i = 1; int j = 2; int k = 1 + 2;
	int i = 12, j = 13, k = i + j;
	int i = 12 + i;
����������� ��������
	int a[5]; int b[2][3]; int c[2][3][4];
	int a[5] = { 1, 2, 3, 4, 5}; int b[2][3] = { {1,2,3}, {4,5,6} };
	int a[]  = { 1, 2, 3, 4}; int b[][3] = { {1,2,3}, {4,5,6} };
	int a[5]; int i; int j; i = a[2]; i = a[i];
������������� ����������, ����� � ������
	int i; int j; i = 3; I = j;
������������� ��������� ����������, ����� � ������
	int a[5]; int i; i = a[2]; a[3] = 1;
�������� ��������
	int i,j; if (i) j = 1; else j = 0;
	int i,j; if (i) j = 1;
	int i,j; j = (i) ? 1 : 0;
�������� �����
	for (;;);
	int s = 0; for (int i = 1; i <= 10; i++) s++;
	for (int i = 1, j = 0; i <= 10; i++, j--);
��������� do while 
	int i = 10; do { i -= 2; } while (i);
	int i = 10;  while (i) { i -= 2; };
���������� goto
	int i; for (;;) if (i) continue; else break; 
	for (int i = 1; i <= 10; i++) if (i%2) continue; else break;
����������� �������
	void f() {}
	int f() { return 12; };
������������� �������
	int f() { return 12; }; int i = f();
