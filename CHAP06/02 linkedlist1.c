#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// 노드 타입
	element data;
	struct ListNode *link;
} ListNode;

// 오류 처리 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
ListNode* insert_first(ListNode *head, int value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));	//(1)	// 동적메모리 할당을 하는 코드
			// &p2를 만드는 코드
	p->data = value;					// (2)
			// &p2에 1을 저장
	p->link = head;	// 헤드 포인터의 값을 복사	//(3)
			// &p1을 &p2->link에 저장
	head = p;	// 헤드 포인터 변경		//(4)
			// head = &p2를 가짐
			// main에 있는 head와 다른 head
	return head;	// 변경된 헤드 포인터 반환
}

// 노드 pre 뒤에 새로운 노드 삽입
ListNode*  insert(ListNode *head, ListNode *pre, element value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));	//(1)  MAX값 없음
	p->data = value;		//(2)
	p->link = pre->link;	//(3)	
	pre->link = p;		//(4)	
	return head;		//(5)	
}

ListNode* delete_first(ListNode *head)
{
	ListNode *removed;
	if (head == NULL) return NULL;
	removed = head;	// (1)
	head = removed->link;	// (2)
	free(removed);		// (3)
	return head;		// (4)
}
// pre가 가리키는 노드의 다음 노드를 삭제한다. 
ListNode* delete(ListNode *head, ListNode *pre)
{
	ListNode *removed;
	removed = pre->link;
	pre->link = removed->link;		// (2)
	free(removed);			// (3)
	return head;			// (4)
}

void print_list(ListNode *head)
{
	for (ListNode *p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}

// 테스트 프로그램
int main(void)									// 단일 연결 리스트
{
	ListNode *head = NULL;						// head는 무조건 4바이트

	for (int i = 0; i < 5; i++) {
		head = insert_first(head, i);			// insert_firsts MAX사이즈 없음	(동적 메모리 할당 사용)
							// head 는 main에 있는 head
		print_list(head);
	}
	for (int i = 0; i < 5; i++) {
		head = delete_first(head);
		print_list(head);
	}
	return 0;
}