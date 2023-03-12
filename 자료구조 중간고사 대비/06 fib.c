#include<stdio.h>
#include<time.h>
#define MAX 30

int fib(int n);
int main()
{
	clock_t start, stop;        // 시간을 측정하기 위해 시작과 종료 지정
	double duration;        // 걸리는 시간을 저장함
	start = clock();            // 시작 지점

	int r1 = fib(MAX);
	printf("%d\n",r1);

	stop = clock();     // 종료 지점
	duration = (double)(stop - start) / CLOCKS_PER_SEC;     // 걸리는 시간 계산
	printf("수행시간은 %.5lf입니다.\n", duration);      // 소수점 5번째 까지 나오도록 함

	return 0;
}

int fib(int n)
{
	printf("현재 호출된함수 fib(%d)\n", n);
	
	if( n==0 ) return 0;
    if( n==1 ) return 1;
	return (fib(n-1) + fib(n-2));
}
// 시간 수행 측정 시간