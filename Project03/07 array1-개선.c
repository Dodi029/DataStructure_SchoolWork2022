#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 6		

void get_integers(int list[])
{
	printf("%d개의 정수를 입력하시오: ", SIZE);		// SIZE로 지정한 개수만큼 값을 입력받음
	for (int i = 0; i < SIZE; ++i) {		// SIZE 수 만큼 값을 배열에 저장함
		scanf("%d", &list[i]);
	}
}

int cal_mul(int list[])			// 입력한 값을 곱하는 함수
{
	int mul = 1;		// 곱하기이므로 처음 값을 1로 지정
	for (int i = 0; i < SIZE; ++i) {
		mul = mul* *(list + i);			// 초기값(1)에 입력한 값들을 곱함
	}
	return mul;			// 곱한 값을 리턴
}

int cal_sub(int list[])			// 입력한 값을 빼는 함수
{
	int sub = 0;		// 덧셈처럼 처음 값을 0으로 지정
	for (int i = 0; i < SIZE; ++i) {
		sub -= *(list + i);			// 초기값(0)에 입력한 값들을 뺌
	}
	return sub;			// 뺀 값을 리턴
}

int main(void)
{
	int list[SIZE];
	get_integers(list);
	printf("곱 = %d \n", cal_mul(list));			// 리턴한 곱한 값을 출력
	printf("차 = %d \n", cal_sub(list));			// 리턴한 뺀 값을 출력
	return 0;
}