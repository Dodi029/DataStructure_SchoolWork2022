#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>		// strcpy()�Լ��� ����ϱ� ���� ����
#define MAX 10			// �ѹ��� �ٲٱ� ������ �迭�� ���� MAX�� ����

void swap(char* px, char* py)		// ���ڿ��� �޵��� ���� int������ char������ �ٲ�
{
	char tmp[MAX];		// MAX ũ���� �迭 ����
	
	strcpy(tmp, px);		// ���ڿ��� �����ϴ� strcpy�Լ��� ���ڿ� ����
							// tmp�� px���ڿ� ����
	strcpy(px, py);			// px�� py���ڿ� ����
	strcpy(py, tmp);		// py�� tmp���ڿ� ����(������ �ִ� px���ڿ��� �����)
}

int main(void)
{
	char a[MAX];		// �迭 ����
	char b[MAX];		// �迭 ����

	printf("a�� ������ ���ڿ� >> ");
	scanf("%s", &a);		// a�迭�� ����ڰ� ���ϴ� ���ڿ� �ֱ�
	printf("b�� ������ ���ڿ� >> ");
	scanf("%s", &b);		// b�迭�� ����ڰ� ���ϴ� ���ڿ� �ֱ�
	printf("swap�� ȣ���ϱ� ��: a=%s, b=%s\n", a, b);
	swap(&a, &b);		// swap�Լ��� a�迭�� b�迭�� ���ڿ� ��ü
	printf("swap�� ȣ���� ����: a=%s, b=%s\n", a, b);
	return 0;
}