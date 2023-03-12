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
    clock_t start, stop;        // 시간을 측정하기 위해 시작과 종료 지정
    double duration;        // 걸리는 시간을 저장함
    start = clock();            // 시작 지점

    int r1 = fib_iter(MAX);
    printf("%d\n", r1);

    stop = clock();     // 종료 지점
    duration = (double)(stop - start) / CLOCKS_PER_SEC;     // 걸리는 시간 계산
    printf("수행시간은 %.5lf입니다.\n", duration);      // 소수점 5번째 까지 나오도록 함
    return 0;
}