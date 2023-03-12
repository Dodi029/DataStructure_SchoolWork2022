#include<stdio.h>
#include<time.h>
#define MAX 30

int fib(int n);
int main()
{
	clock_t start, stop;        // �ð��� �����ϱ� ���� ���۰� ���� ����
	double duration;        // �ɸ��� �ð��� ������
	start = clock();            // ���� ����

	int r1 = fib(MAX);
	printf("%d\n",r1);

	stop = clock();     // ���� ����
	duration = (double)(stop - start) / CLOCKS_PER_SEC;     // �ɸ��� �ð� ���
	printf("����ð��� %.5lf�Դϴ�.\n", duration);      // �Ҽ��� 5��° ���� �������� ��

	return 0;
}

int fib(int n)
{
	printf("���� ȣ����Լ� fib(%d)\n", n);
	
	if( n==0 ) return 0;
    if( n==1 ) return 1;
	return (fib(n-1) + fib(n-2));
}
// �ð� ���� ���� �ð�