#include<stdio.h>
int fib(int n);
int main()
{
	int r1 = fib(6);
	printf("%d\n",r1);
	return 0;
}

int fib(int n)
{
	printf("현재 호출된함수 fib(%d)\n", n);
	
	if( n==0 ) return 0;
    if( n==1 ) return 1;
	return (fib(n-1) + fib(n-2));
}
