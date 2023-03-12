#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>		// 시간을 측정하기 위해 include함
#define MAX1 2		// 밑
#define MAX2 3		// 지수

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
	clock_t start, stop;        // 시간을 측정하기 위해 시작과 종료 지정
	double duration;        // 걸리는 시간을 저장함
	start = clock();            // 시작 지점

	double r1;
	r1 = slow_power(MAX1, MAX2);
	printf("%.1lf\n", r1);

	stop = clock();     // 종료 지점
	duration = (double)(stop - start) / CLOCKS_PER_SEC;     // 걸리는 시간 계산
	printf("수행시간은 %.10lf입니다.\n", duration);      // 소수점 5번째 까지 나오도록 함

	return 0;
} 