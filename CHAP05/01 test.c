#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* p; // ���� ������ ����
	int a;
	char b[40];
	double c;
	
	p = fopen("report.txt", "r"); // 1. ���� ������ �����ϸ�, read ���� ���� �б� 
	
	if (p == NULL)
		printf("���Ͽ��� ����\n");

	fscanf(p,"%d %s %lf",&a,b,&c);		// p ��� stdin�� ���� Ű����κ��� ���� �Է¹���  p�� ���� ���Ϸ� ���� �����͸� �о��
	printf("%d %s %lf",a,b,c);			// fprintf(stdout, "%d %s %lf". a b c)�� ���� �⺻���=ȭ������ �����
	fclose(p);

	system("notepad.exe report.txt");
	//system("notepad.exe D:\\report1.txt"); => ���� ��θ� �����ϴ� ���(D����̺꿡 ��ġ��)

	return 0;
	
	
}
