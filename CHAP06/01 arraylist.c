#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100 	          // ����Ʈ�� �ִ�ũ��

typedef int element;			      // �׸��� ����
typedef struct {
	element array[MAX_LIST_SIZE];	  // �迭 ����
	int size;		                  // ���� ����Ʈ�� ����� �׸���� ����
} ArrayListType;

// ���� ó�� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ����Ʈ �ʱ�ȭ �Լ�
void init(ArrayListType *L)
{
	L->size = 0;
}

// ����Ʈ�� ��� ������ 1�� ��ȯ
// �׷��� ������ 0�� ��ȯ
int is_empty(ArrayListType *L)
{
	return L->size == 0;
}

// ����Ʈ�� ���� �� ������ 1�� ��ȯ
// �׷��� ������ 1�� ��ȯ
int is_full(ArrayListType *L)
{
	return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType *L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("��ġ ����");
	return L->array[pos];
}

// ����Ʈ ���
void print_list(ArrayListType *L)
{
	int i;
	for (i = 0; i<L->size; i++)
		printf("%d->", L->array[i]);
	printf("\n");
}

void insert_last(ArrayListType *L, element item)
{
	if( L->size >= MAX_LIST_SIZE ) {
		error("����Ʈ �����÷ο�");
	}
	L->array[L->size++] = item;				// *������ ���� �� size�� ����*
}
void insert(ArrayListType *L, int pos, element item)
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = (L->size - 1); i >= pos; i--)		// i�� -1(�ʱⰪ) ���� pos(0)���� Ŭ��=> ���� ����
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;							// item(10)�� pos(0)�� ����
		L->size++;										// size(0)���� size(1)�� ����`
	}
}
element delete(ArrayListType *L, int pos)
{
	element item;

	if (pos < 0 || pos >= L->size)
		error("��ġ ����");
	item = L->array[pos];
	for (int i = pos; i<(L->size - 1); i++)
		L->array[i] = L->array[i + 1];
	L->size--;
	return item;
}


int main(void)
{
	// ArrayListType�� �������� �����ϰ� ArrayListType�� 	
	// ����Ű�� �����͸� �Լ��� �Ű������� �����Ѵ�.
	ArrayListType list;			// ���ڵ� ����

	init(&list);		
	insert(&list, 0, 10);	print_list(&list);	// 0��° ��ġ�� 10 �߰�
	insert(&list, 0, 20);	print_list(&list);	// 0��° ��ġ�� 20 �߰�
	insert(&list, 0, 30);	print_list(&list);	// 0��° ��ġ�� 30 �߰�
	insert_last(&list, 40);	print_list(&list);	// �� ���� 40 �߰�			
	delete(&list, 0);		print_list(&list);	// 0��° �׸� ����
	return 0;
}