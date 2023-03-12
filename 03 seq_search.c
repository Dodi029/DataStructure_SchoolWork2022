#pragma warning(disable:4996)	

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 10

int seq_search(int* list, int n, int key);

int main(void)
{
	char array[MAX];
	int i;

	clock_t start, stop;
	double duration;
	for (i = 0; i < MAX; i++)
	{
		scanf_s("%c", &array[i]);
	}
	int result, search;

	scanf_s("%d", &search);
	start = clock();
	result = seq_search(array1, MAX, search);
	stop = clock();
	printf("%d\n", result);

	duration = (double)(stop - start) / CLOCK_PER_SEC;
	printf("수행시간은 %.lf초 입니다.\n", duration);
}

int seq_search(int list[], int n, int key)
{
	int i;
	for (i = 0; i < n; i++)
		if (list[i] == key)
			return i;  // 탐색에 성공하면 키 값의 인덱스 반환 
	return -1;    // 탐색에 실패하면 -1 반환
}