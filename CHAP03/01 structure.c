#include <stdio.h>

typedef struct studentTag {			// tryedef ���Ŀ��� student; ���� �߰��� ��� ���� ����
	char name[10]; // ���ڹ迭�� �� �̸�
	int age;	  // ���̸� ��Ÿ���� ������
	double gpa;	  // ��������� ��Ÿ���� �Ǽ���
} student;

int main(void)
{
	student a = { "kim", 20, 4.3 };
	student b = { "park", 21, 4.2 };
	return 0;
}