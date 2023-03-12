#include<stdio.h>
#include <time.h>
#define MAX 30
int fib_iter(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
        
    int pp = 0;	
    int p = 1;
    int result = 0;
        
    for (int i = 2; i <= n; i++) {
        result = p + pp;
        pp = p;
        p = result;
    }
    return result;
}
int main()
{
    clock_t start, stop;        // �ð��� �����ϱ� ���� ���۰� ���� ����
    double duration;        // �ɸ��� �ð��� ������
    start = clock();            // ���� ����

    int r1 = fib_iter(MAX);
    printf("%d\n", r1);

    stop = clock();     // ���� ����
    duration = (double)(stop - start) / CLOCKS_PER_SEC;     // �ɸ��� �ð� ���
    printf("����ð��� %.5lf�Դϴ�.\n", duration);      // �Ҽ��� 5��° ���� �������� ��
    return 0;
}