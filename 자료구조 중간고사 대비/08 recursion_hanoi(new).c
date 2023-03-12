#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

FILE* p;

void hanoi_tower(int n, char from, char tmp, char to)
{
	
	if (n == 1) {
		fprintf(p,"���� 1�� %c ���� %c���� �ű��.\n", from, to);
	}//fprintf ����ؼ� �����غ���.
	else {
		hanoi_tower(n-1, from, to, tmp);
		fprintf(p,"���� %d�� %c���� %c���� �ű��.\n",n,from,to);
		hanoi_tower(n-1, tmp, from, to);
	}
	
}
int main(void)
{
	int n;
	
	p = fopen("result.txt", "w");
	printf("������ ����>>");
	scanf("%d", &n);
	hanoi_tower(n, 'A', 'B', 'C');
	fclose(p);		//���Ͽ� ����
	system("notepad.exe 08 recursion_hanoi.c");
	return 0;
}
