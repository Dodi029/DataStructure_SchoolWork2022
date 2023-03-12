#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX_ELEMENT 200


typedef struct {
	int rank;
} element;
typedef struct {
	int heap[MAX_ELEMENT];
	char num[1024];
	char name[1024];
	float score;
	int rank;

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
void insert_max_heap(HeapType* h, char* num, char* name, float score, int rank)
{
	int i;
	i = ++(h->heap_size);
	strcpy(h->num, num);
	strcpy(h->name, name);
	h->score = score;
	h->rank = rank;
	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (rank > h->heap[i / 2].rank)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = rank;     // 새로운 노드를 삽입
}

int main(void)
{
	element input[MAX_ELEMENT];
	element output[MAX_ELEMENT];
	HeapType* heap;
	
	int j = 0, score = 0;
	double average;
	double total = 0;
	char* token;

	heap = create(); 	// 히프 생성
	init(heap);	// 초기화

	insert_max_heap(heap, "2020131055", "ojm", 3.82, 5);
	insert_max_heap(heap, "2020131011", "sjm", 3.99, 4);
	insert_max_heap(heap, "2020132044", "ajm", 4.3, 1);
	insert_max_heap(heap, "2020132033", "yjm", 4.2, 3);
	insert_max_heap(heap, "2020132022", "bjm", 4.25, 2);
	insert_max_heap(heap, "2020132077", "cjm", 3.7, 7);
	insert_max_heap(heap, "2020132000", "rjm", 3.54, 10);
	insert_max_heap(heap, "2020132066", "tjm", 3.66, 8);
	insert_max_heap(heap, "2020132099", "xjm", 3.65, 9);
	insert_max_heap(heap, "2020132088", "zjm", 3.72, 6);

	FILE* fp = fopen("08.txt");
	fprintf(fp, "%s\t%s\%.2lf\t%d", h->num,h->)
	return 0;
}
//100개의 랜덤으로 점수(100점 만점)를 파일에 출력후 이를 읽어드려 평균값을 찾고 상위 5등 하위 5등을 찾아 표준편차와 같이 파일에 출력
//위의 출력파일을 읽어드려 히프트리를 만들어볼것.