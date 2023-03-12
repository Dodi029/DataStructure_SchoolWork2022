/*
// 팩토리얼 '순환(재귀)' 알고리즘 (입력, 처리, 출력)
// 입력 : 정수
// 처리 : 팩토리얼
// 출력 : 정수
int factorial(int n)
{
    //printf("factorial(%d)\n",n);
    if( n <= 1 ) return(1);
    else return (n * factorial(n-1) );
}
순환으로 짠 코드
*/

#define _CRT_SECURE_NO_WARNINGS     // 맨 윗줄에 작성해놔야 함
#include<stdio.h>
#define MAX 3                       // 3을 상수화 선언

int factorial(int n);               // 함수의 선언 ( = 함수의 리스트)

int main(void)                      // void 생략가능
{
    // 함수의 호출이 있으면 됨
    factorial(MAX);                 // MAX를 factorial()함수에 호출
    

    int num;                        //define 없이 입력해서 값 받기
    scanf("*%d*", &num);            // 숫자 앞, 뒤에 *을 붙여놔야 함 = 
                                    // #define MAX 숫자 로 선언해서
                                    // factorial(MAX); 로 함수를 호출 할 수도 있음
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

// 디버그할때 int main()함수에 F9, int factorial()함수에 F9를 눌러야 정상적으로 디버그를 볼 수 있음
// int factorial()함수에 F9를 하지 않으면 int factorial()함수가 구동되는 모습을 볼 수 없음(생략됨)