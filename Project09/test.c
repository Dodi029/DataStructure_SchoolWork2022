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

// ���� �Լ�
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// �ʱ�ȭ �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;
}
// ���� ����� ������ heap_size�� ���� h�� item�� �����Ѵ�.
// ���� �Լ�
void insert_min_heap(HeapType* h, lpt_element item)
{
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.avail < h->heap[i / 2].avail)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // ���ο� ��带 ����
}
// ���� �Լ�
lpt_element delete_min_heap(HeapType* h)
{
	int parent, child;
	lpt_element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ���� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].avail) > h->heap[child + 1].avail)
			child++;
		if (temp.avail < h->heap[child].avail) break;
		// �� �ܰ� �Ʒ��� �̵�
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
			/* �յ��� ���ڵ带 ���� �� ��ü */
			if (list[j] < list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}
/*
int main(void)
{
	int in;
	printf("�� �� ���� �ְڽ��ϱ�?");
	scanf("%d", &in);
	int* jobs = malloc(sizeof(int) * in);

	int tmp;

	for (int i = 0; i < in; i++) {
		printf("%d��° ���� �Է����ּ��� :", i);
		scanf("%d", &tmp);
		jobs[i] = tmp;
	}

	bubble_sort(jobs, in);

	// int jobs[JOBS] = { 8, 7, 6, 5, 3, 2, 1 };	// �۾��� ���ĵǾ� �ִٰ� ����
	lpt_element m = { 0, 0 };
	HeapType* h;
	h = create();
	init(h);

	// ���⼭ avail ���� ��谡 ��� �����ϰ� �Ǵ� �ð��̴�. 
	for (int i = 0; i < MACHINES; i++) {
		m.id = i + 1;
		m.avail = 0;
		insert_min_heap(h, m);
	}
	// �ּ� �������� ��踦 ������ �۾��� �Ҵ��ϰ� ��밡�� �ð��� ���� ��Ų �Ŀ� 
	// �ٽ� �ּ� ������ �߰��Ѵ�. 
	for (int i = 0; i < in; i++) {
		m = delete_min_heap(h);
		printf("JOB %d�� �ð�=%d���� �ð�=%d���� ��� %d���� �Ҵ��Ѵ�. \n",
			i, m.avail, m.avail + jobs[i] - 1, m.id);
		m.avail += jobs[i];
		insert_min_heap(h, m);
	}
	return 0;
}
*/

int main() {
	printf("100�� ���� ������ �� �� �Ͻðڽ��ϱ�? ");
	int in, ary;
	scanf("%d", &in);
	ary = in * 3;
	int i = 0;

	//char* jobs = malloc(sizeof(char) * ary);
	
	//for (int j = 0; j < ary; j++) {
	//	strcpy(jobs[i], "��");
	//}
	char* jobs[8];
	//for (int i = 0; i < 3; i++) {
	//	jobs[i] = (char*)malloc(strlen("��") + 1);
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