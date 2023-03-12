#include<stdio.h>
#pragma warning(disable:4996)				// scanf_s() 함수를 사용하지 않아 생기는 문제 해결

#define MAX_ELEMENTS 3						// 입력 횟수 (3번)
int scores[MAX_ELEMENTS];					// 자료구조, 전역배열

int get_max_score(int n);					 // 함수의 선언, 함수의 리스트

int main(void)
{
	int result;

	for (int i = 0; i < MAX_ELEMENTS; i++)	// scanf_s()함수를 사용해서
	{										// scores 배열에 값 대입
		scanf_s("%d", &scores[i]);
	}

	result = get_max_score(MAX_ELEMENTS);	//result에 get_max_score 반환 값 largest 대입
	printf("결과:%d\n ",result);				//결과 출력
	
	return 0;								// main 함수 값이 void이므로 0으로 반환
}

int get_max_score(int n)					// 학생의 숫자는 n
{
	int i, largest;
	largest = scores[0];					// 알고리즘
	for (i = 1; i<n; i++) 
	{
		if (scores[i] > largest) 
		{
			largest = scores[i];
		}
	}
	return largest;
}// 입력: n, 처리: 큰점수 획득, 출력: int(정수)