#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 6		

void get_integers(int list[])
{
	printf("%d���� ������ �Է��Ͻÿ�: ", SIZE);		// SIZE�� ������ ������ŭ ���� �Է¹���
	for (int i = 0; i < SIZE; ++i) {		// SIZE �� ��ŭ ���� �迭�� ������
		scanf("%d", &list[i]);
	}
}

int cal_mul(int list[])			// �Է��� ���� ���ϴ� �Լ�
{
	int mul = 1;		// ���ϱ��̹Ƿ� ó�� ���� 1�� ����
	for (int i = 0; i < SIZE; ++i) {
		mul = mul* *(list + i);			// �ʱⰪ(1)�� �Է��� ������ ����
	}
	return mul;			// ���� ���� ����
}

int cal_sub(int list[])			// �Է��� ���� ���� �Լ�
{
	int sub = 0;		// ����ó�� ó�� ���� 0���� ����
	for (int i = 0; i < SIZE; ++i) {
		sub -= *(list + i);			// �ʱⰪ(0)�� �Է��� ������ ��
	}
	return sub;			// �� ���� ����
}

int main(void)
{
	int list[SIZE];
	get_integers(list);
	printf("�� = %d \n", cal_mul(list));			// ������ ���� ���� ���
	printf("�� = %d \n", cal_sub(list));			// ������ �� ���� ���
	return 0;
}