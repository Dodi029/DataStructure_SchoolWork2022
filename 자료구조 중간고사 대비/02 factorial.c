#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>        // �ɸ��� �ð��� �����ϱ� ���� include
#define MAX 12      // ���� ���� �ٲٱ� ���� define MAX�� ����

int factorial(int n)
{
    printf("factorial(%d)\n",n);
    if( n <= 1 ) return(1);
    else return (n * factorial(n-1) );      // ���� ���丮�� �Լ� ���
}

int main()
{
    clock_t start, stop;        // �ð��� �����ϱ� ���� ���۰� ���� ����
    double duration;        // �ɸ��� �ð��� ������
    start = clock();            // ���� ����
    
    int r1;
    r1 = factorial(MAX);
    printf("%d\n", r1);

    stop = clock();     // ���� ����
    duration = (double)(stop - start) / CLOCKS_PER_SEC;     // �ɸ��� �ð� ���
    printf("����ð��� %.5lf�Դϴ�.\n", duration);      // �Ҽ��� 5��° ���� �������� ��

    return 0;
}