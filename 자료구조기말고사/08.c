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
void insert_max_heap(HeapType* h, char* num, char* name, float score, int rank)
{
	int i;
	i = ++(h->heap_size);
	strcpy(h->num, num);
	strcpy(h->name, name);
	h->score = score;
	h->rank = rank;
	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (rank > h->heap[i / 2].rank)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = rank;     // ���ο� ��带 ����
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

	heap = create(); 	// ���� ����
	init(heap);	// �ʱ�ȭ

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
//100���� �������� ����(100�� ����)�� ���Ͽ� ����� �̸� �о��� ��հ��� ã�� ���� 5�� ���� 5���� ã�� ǥ�������� ���� ���Ͽ� ���
//���� ��������� �о��� ����Ʈ���� ������.