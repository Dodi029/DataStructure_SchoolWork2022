#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct {
	int id;
	int avail;
} lpt_element;

typedef struct {
	lpt_element heap[MAX_ELEMENT];
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
void insert_min_heap(HeapType* h, lpt_element item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.avail < h->heap[i / 2].avail)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}
// 삭제 함수
lpt_element delete_min_heap(HeapType* h)
{
	int parent, child;
	lpt_element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].avail) > h->heap[child + 1].avail)
			child++;
		if (temp.avail < h->heap[child].avail) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
#define JOBS 7
#define MACHINES 3

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++)
			/* 앞뒤의 레코드를 비교한 후 교체 */
			if (list[j] < list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}
/*
int main(void)
{
	int in;
	printf("몇 번 값을 넣겠습니까?");
	scanf("%d", &in);
	int* jobs = malloc(sizeof(int) * in);

	int tmp;

	for (int i = 0; i < in; i++) {
		printf("%d번째 값을 입력해주세요 :", i);
		scanf("%d", &tmp);
		jobs[i] = tmp;
	}

	bubble_sort(jobs, in);

	// int jobs[JOBS] = { 8, 7, 6, 5, 3, 2, 1 };	// 작업은 정렬되어 있다고 가정
	lpt_element m = { 0, 0 };
	HeapType* h;
	h = create();
	init(h);

	// 여기서 avail 값은 기계가 사용 가능하게 되는 시간이다. 
	for (int i = 0; i < MACHINES; i++) {
		m.id = i + 1;
		m.avail = 0;
		insert_min_heap(h, m);
	}
	// 최소 히프에서 기계를 꺼내서 작업을 할당하고 사용가능 시간을 증가 시킨 후에 
	// 다시 최소 히프에 추가한다. 
	for (int i = 0; i < in; i++) {
		m = delete_min_heap(h);
		printf("JOB %d을 시간=%d부터 시간=%d까지 기계 %d번에 할당한다. \n",
			i, m.avail, m.avail + jobs[i] - 1, m.id);
		m.avail += jobs[i];
		insert_min_heap(h, m);
	}
	return 0;
}
*/

int main() {
	printf("100개 생산 공정을 몇 번 하시겠습니까? ");
	int in, ary;
	scanf("%d", &in);
	ary = in * 3;
	int i = 0;

	//char* jobs = malloc(sizeof(char) * ary);
	
	//for (int j = 0; j < ary; j++) {
	//	strcpy(jobs[i], "안");
	//}
	char* jobs[8];
	//for (int i = 0; i < 3; i++) {
	//	jobs[i] = (char*)malloc(strlen("안") + 1);
	//	strcpy(jobs[i],tmp)
	//}

	for (int i = 0; i < 2; i++) {
		jobs[i] = malloc(sizeof(char) * ary);
		strcpy(jobs[i], "black");
	}
	for (int i = 0; i < ary+1; i++) {
		printf("%s", jobs[i]); 
	}

}