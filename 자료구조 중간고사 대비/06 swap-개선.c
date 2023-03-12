#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>		// strcpy()함수를 사용하기 위해 선언
#define MAX 10			// 한번에 바꾸기 쉽도록 배열의 값을 MAX로 지정

void swap(char* px, char* py)		// 문자열을 받도록 기존 int형에서 char형으로 바꿈
{
	char tmp[MAX];		// MAX 크기의 배열 선언
	
	strcpy(tmp, px);		// 문자열을 복사하는 strcpy함수로 문자열 복사
							// tmp에 px문자열 복사
	strcpy(px, py);			// px에 py문자열 복사
	strcpy(py, tmp);		// py에 tmp문자열 복사(기존에 있던 px문자열이 복사됨)
}

int main(void)
{
	char a[MAX];		// 배열 선언
	char b[MAX];		// 배열 선언

	printf("a에 저장할 문자열 >> ");
	scanf("%s", &a);		// a배열에 사용자가 원하는 문자열 넣기
	printf("b에 저장할 문자열 >> ");
	scanf("%s", &b);		// b배열에 사용자가 원하는 문자열 넣기
	printf("swap을 호출하기 전: a=%s, b=%s\n", a, b);
	swap(&a, &b);		// swap함수로 a배열과 b배열의 문자열 교체
	printf("swap을 호출한 다음: a=%s, b=%s\n", a, b);
	return 0;
}