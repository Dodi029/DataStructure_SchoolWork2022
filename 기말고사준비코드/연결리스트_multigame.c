#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct ListNode { 	// ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

typedef struct CListType {
	ListNode* head;
} CListType;

// ����Ʈ�� �׸� ���
void print_list(CListType* L)
{
	ListNode* p;

	if (L->head == NULL) return;
	p = L->head->link;
	do {
		printf("%s->", p->data);
		p = p->link;
	} while (p != L->head);
	printf("%s->", p->data); // ������ ��� ���
}

void insert_first(CListType* L, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	strcpy(node->data, data);
	if (L->head == NULL) {
		L->head = node;
		node->link = L->head;
	}
	else {
		node->link = L->head->link;	// (1)
		L->head->link = node;		// (2)
	}
}
// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	CListType list = { NULL };

	insert_first(&list, "KIM");
	insert_first(&list, "PARK");
	insert_first(&list, "CHOI");

	ListNode* p = list.head;
	//for (int i = 0; i< 10; i++) {
	//	printf("���� ����=%s \n", p->data);
	//	p = p->link;
	//}
	int d1, d2;
	for (int i = 0; i < 5; i++) {
		printf("���� ����=%s\n", p->data);
		p = p->link;
		fprintf(stdout, "�ֻ��� ���� 2�� �Է��ϼ��� : \n");
		fscanf(stdin, "%d %d", &d1, &d2);
		fprintf(stdout, "---------------------------------\n");
	}
	return 0;
}
