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
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // ���ο� ��带 ����
}
// ���� �Լ�
element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
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
	fprintf(fp, "ǥ������ : %.1lf", std);
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
	heap = create(); 	// ���� ����
	init(heap);	// �ʱ�ȭ
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
			fprintf(fp2, "���� 5�� : ");
		}
		else if (i == j - 6) {
			fprintf(fp2, "\n���� 5�� : ");
		}
		if (i < 5) {
			fprintf(fp2, "%d�� ", output[i]);
		}
		else if ((i >= j - 6) && (i != j - 1)) {
			fprintf(fp2, "%d�� ", output[i]);
		}

	}

	fprintf(fp2, "\n��� %.1lf��\n", average);
	qyencha(fp2, average, output, j);

	fclose(fp1);
	fclose(fp2);
	free(heap);

	system("notepad.exe heap_input.txt");
	system("notepad.exe heap_output.txt");

	return 0;
}
//100���� �������� ����(100�� ����)�� ���Ͽ� ����� �̸� �о��� ��հ��� ã�� ���� 5�� ���� 5���� ã�� ǥ�������� ���� ���Ͽ� ���
//���� ��������� �о��� ����Ʈ���� ������.