#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>        // 걸리는 시간을 측정하기 위해 include
#define MAX 12      // 값을 쉽게 바꾸기 위해 define MAX로 선언

int factorial(int n)
{
    printf("factorial(%d)\n",n);
    if( n <= 1 ) return(1);
    else return (n * factorial(n-1) );      // 기존 팩토리얼 함수 사용
}

int main()
{
    clock_t start, stop;        // 시간을 측정하기 위해 시작과 종료 지정
    double duration;        // 걸리는 시간을 저장함
    start = clock();            // 시작 지점
    
    int r1;
    r1 = factorial(MAX);
    printf("%d\n", r1);

    stop = clock();     // 종료 지점
    duration = (double)(stop - start) / CLOCKS_PER_SEC;     // 걸리는 시간 계산
    printf("수행시간은 %.5lf입니다.\n", duration);      // 소수점 5번째 까지 나오도록 함

    return 0;
}