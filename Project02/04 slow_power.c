#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>		// �ð��� �����ϱ� ���� include��
#define MAX1 2		// ��
#define MAX2 3		// ����

double slow_power(double x, int n)
{
	int i;
	double result = 1.0;

	for (i = 0; i<n; i++)
		result = result * x;
	return(result);
}
int main()
{
	clock_t start, stop;        // �ð��� �����ϱ� ���� ���۰� ���� ����
	double duration;        // �ɸ��� �ð��� ������
	start = clock();            // ���� ����

	double r1;
	r1 = slow_power(MAX1, MAX2);
	printf("%.1lf\n", r1);

	stop = clock();     // ���� ����
	duration = (double)(stop - start) / CLOCKS_PER_SEC;     // �ɸ��� �ð� ���
	printf("����ð��� %.10lf�Դϴ�.\n", duration);      // �Ҽ��� 5��° ���� �������� ��

	return 0;
} 