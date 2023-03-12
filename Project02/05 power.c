#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX1 2		// 밑
#define MAX2 3		// 지수

double power(double x, int n)
{
	if( n==0 ) return 1;
	else if ( (n%2)==0 ) 
		return power(x*x, n/2);
	else return x*power(x*x, (n-1)/2);
}
int main()
{
	double r1;
	r1 = power(MAX1, MAX2);
	printf("%.1lf", r1);

	return 0;
}