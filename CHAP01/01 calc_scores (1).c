#define MAX_ELEMENTS 3
int scores[MAX_ELEMENTS];	// 자료구조, 전역배열

int get_max_score(int n);   // 함수의 선언, 함수의 리스트

int main(void)
{
	int result;
	result = get_max_score(MAX_ELEMENTS);
	printf("결과:%d\n ",result);
	return 0;
}

int get_max_score(int n) 	// 학생의 숫자는 n
{
	int i, largest;
	largest = scores[0];	// 알고리즘
	for (i = 1; i<n; i++) 
	{
		if (scores[i] > largest) 
		{
			largest = scores[i];
		}
	}
	return largest;
}// 입력: n, 처리: 큰점수 획득, 출력: int(정수)