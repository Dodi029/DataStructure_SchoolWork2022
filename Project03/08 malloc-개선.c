// ����ڿ��� ������ �� �� �Է����� ����� �� ����ŭ �޸� �����ϱ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(void)
{
	int count, sum = 0;		// �Է��� ������ ����, �� ���� ������ ����
	int* p;			// ������ ����

	printf("������ �� �� �Է��Ͻðڽ��ϱ�>> ");
	scanf("%d", &count);		// �Է��� ������ ������ ����� �� ���� count�� ����

	p = (int*)malloc(count * sizeof(int));			// ���� �޸��Ҵ�
	if (p == NULL) {								// count��ŭ �޸� ����
		fprintf(stderr, "�޸𸮰� �����ؼ� �Ҵ��� �� �����ϴ�.\n");
		exit(1);
	}

	for (int i = 0; i < count; i++) {		// �޸� �� ��ŭ ������ �Է¹���
		printf("%d��° �� : ", i + 1);
		scanf("%d", p + i);			// �Է¹��� ���� ������
	}

	printf("\n�Է��� �� Ȯ��\n");			// ���ݱ��� �Է��� ���� ������
	for (int i = 0; i < count; i++) {
		printf("%d, ", *(p + i));

		sum = sum + *(p + i);			// �Է��� ���� ��� ����
	}
	printf("\n�� ���� : %d", sum);

	free(p);
	return 0;
}