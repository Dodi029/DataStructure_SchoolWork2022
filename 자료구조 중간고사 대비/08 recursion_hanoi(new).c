#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

FILE* p;

void hanoi_tower(int n, char from, char tmp, char to)
{
	
	if (n == 1) {
		fprintf(p,"원판 1을 %c 에서 %c으로 옮긴다.\n", from, to);
	}//fprintf 사용해서 개선해볼것.
	else {
		hanoi_tower(n-1, from, to, tmp);
		fprintf(p,"원판 %d을 %c에서 %c으로 옮긴다.\n",n,from,to);
		hanoi_tower(n-1, tmp, from, to);
	}
	
}
int main(void)
{
	int n;
	
	p = fopen("result.txt", "w");
	printf("원판의 개수>>");
	scanf("%d", &n);
	hanoi_tower(n, 'A', 'B', 'C');
	fclose(p);		//파일에 저장
	system("notepad.exe 08 recursion_hanoi.c");
	return 0;
}
