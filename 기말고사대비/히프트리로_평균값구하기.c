#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX_ELEMENT 200


typedef struct {
	int key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;


// 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}
// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}
// 삭제 함수
element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
void qyencha(FILE* fp, double average, element output[], int size) {
	double ary[100];
	double std;
	for (int i = 0; i < size - 1; i++) {
		ary[i] = pow(average - output[i].key, 2);
	}
	for (int i = 1; i < size - 1; i++) {
		ary[0] = ary[0] + ary[i];
	}
	std = sqrt(ary[0] / size - 1);
	fprintf(fp, "표준편차 : %.1lf", std);
}

int main(void)
{
	element input[MAX_ELEMENT];
	element output[MAX_ELEMENT];
	HeapType* heap;
	FILE* fp1, * fp2;
	int j = 0, score = 0;
	double average;
	double total = 0;
	char* token;
	fp1 = fopen("heap_input.txt", "w");
	fp2 = fopen("heap_output.txt", "w");

	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		score = rand();
		fprintf(fp1, "%d ", score % 101);
	}
	fclose(fp1);


	fp1 = fopen("heap_input.txt", "r");
	heap = create(); 	// 히프 생성
	init(heap);	// 초기화
	while (!feof(fp1)) {
		fscanf(fp1, "%d", &input[j]);
		insert_max_heap(heap, input[j]);
		j++;
	}
	for (int i = 0; i < j; i++) {
		output[i] = delete_max_heap(heap);
		if (i != j - 1) {
			total = output[i].key + total;
		}

	}
	average = total / (double)j - 1;

	for (int i = 0; i < j; i++) {
		if (i == 0) {
			fprintf(fp2, "상위 5명 : ");
		}
		else if (i == j - 6) {
			fprintf(fp2, "\n하위 5명 : ");
		}
		if (i < 5) {
			fprintf(fp2, "%d점 ", output[i]);
		}
		else if ((i >= j - 6) && (i != j - 1)) {
			fprintf(fp2, "%d점 ", output[i]);
		}

	}

	fprintf(fp2, "\n평균 %.1lf점\n", average);
	qyencha(fp2, average, output, j);

	fclose(fp1);
	fclose(fp2);
	free(heap);

	system("notepad.exe heap_input.txt");
	system("notepad.exe heap_output.txt");

	return 0;
}
//100개의 랜덤으로 점수(100점 만점)를 파일에 출력후 이를 읽어드려 평균값을 찾고 상위 5등 하위 5등을 찾아 표준편차와 같이 파일에 출력
//위의 출력파일을 읽어드려 히프트리를 만들어볼것.