/*
// ���丮�� '��ȯ(���)' �˰��� (�Է�, ó��, ���)
// �Է� : ����
// ó�� : ���丮��
// ��� : ����
int factorial(int n)
{
    //printf("factorial(%d)\n",n);
    if( n <= 1 ) return(1);
    else return (n * factorial(n-1) );
}
��ȯ���� § �ڵ�
*/

#define _CRT_SECURE_NO_WARNINGS     // �� ���ٿ� �ۼ��س��� ��
#include<stdio.h>
#define MAX 3                       // 3�� ���ȭ ����

int factorial(int n);               // �Լ��� ���� ( = �Լ��� ����Ʈ)

int main(void)                      // void ��������
{
    // �Լ��� ȣ���� ������ ��
    factorial(MAX);                 // MAX�� factorial()�Լ��� ȣ��
    

    int num;                        //define ���� �Է��ؼ� �� �ޱ�
    scanf("*%d*", &num);            // ���� ��, �ڿ� *�� �ٿ����� �� = 
                                    // #define MAX ���� �� �����ؼ�
                                    // factorial(MAX); �� �Լ��� ȣ�� �� ���� ����
    factorial(num);
    printf("%d", factorial(num));
    
    return 0;
}

int factorial(int n)
{
    //printf("factorial(%d)\n",n);
    if (n <= 1) return(1);
    else return (n * factorial(n - 1));
}

// ������Ҷ� int main()�Լ��� F9, int factorial()�Լ��� F9�� ������ ���������� ����׸� �� �� ����
// int factorial()�Լ��� F9�� ���� ������ int factorial()�Լ��� �����Ǵ� ����� �� �� ����(������)