#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct ListNode { 	// 노드 타입
	element data;
	struct ListNode* link;
} ListNode;

typedef struct CListType {
	ListNode* head;
} CListType;

// 리스트의 항목 출력
void print_list(CListType* L)
{
	ListNode* p;

	if (L->head == NULL) return;
	p = L->head->link;
	do {
		printf("%s->", p->data);
		p = p->link;
	} while (p != L->head);
	printf("%s->", p->data); // 마지막 노드 출력
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
// 원형 연결 리스트 테스트 프로그램
int main(void)
{
	CListType list = { NULL };

	insert_first(&list, "KIM");
	insert_first(&list, "PARK");
	insert_first(&list, "CHOI");

	ListNode* p = list.head;
	//for (int i = 0; i< 10; i++) {
	//	printf("현재 차례=%s \n", p->data);
	//	p = p->link;
	//}
	int d1, d2;
	for (int i = 0; i < 5; i++) {
		printf("현재 차례=%s\n", p->data);
		p = p->link;
		fprintf(stdout, "주사위 눈을 2개 입력하세요 : \n");
		fscanf(stdin, "%d %d", &d1, &d2);
		fprintf(stdout, "---------------------------------\n");
	}
	return 0;
}
