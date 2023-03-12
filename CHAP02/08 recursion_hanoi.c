#include <stdio.h>
#include<stdlib.h>
#define MAX 3

void hanoi_tower(int n, char from, char tmp, char to);

int main(void)
{
	hanoi_tower(MAX, 'A', 'B', 'C');
	// FILE* p;  = ���� ������(p�� 4����Ʈ¥�� ������ ����)
	// p = fopen("02.txt", "w"); ������ ���� �Լ�(������ ������ �ʾұ� ������ ���ο� ����(02.txt)���� ����
	// ... ���� �ۼ�
	// fclose(p);	c��� ���� ����� �κ��� ���� �ٽ� �����ϱ�
	// fputs(), fgets() �Լ� �ʿ�
	system("notepad.exe 08 recursion_hanoi.c"); // �ؽ�Ʈ ���Ϸ� ��� �� ����
	return 0;
}

void hanoi_tower(int n, char from, char tmp, char to)
{
	if( n==1 ) printf("���� 1�� %c ���� %c���� �ű��.\n",from,to);	// ���Ͽ� �����ϱ� ���ؼ��� fprintf�� �ۼ��ؾ���
																	// �̷��� �ϴ°� ���� ������ ����
	else {
		hanoi_tower(n-1, from, to, tmp);
		printf("���� %d�� %c���� %c���� �ű��.\n",n,from,to);
		hanoi_tower(n-1, tmp, from, to);
	}
}