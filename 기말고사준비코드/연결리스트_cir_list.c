#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{ 	// 노드 타입
	element data;
	struct ListNode* link;
} ListNode;

// 리스트의 항목 출력
void print_list(ListNode* head)
{
	ListNode* p;		// 노드 포인터

	if (head == NULL) return;		// head가 비어있으면 함수 종료
	p = head->link;			// head의 링크로 첫번째 노드로 이동
	do {		// 반복문
		printf("%d->", p->data);		// 노드의 데이터 출력
		p = p->link;			// 다음 노드로 위치 이동
	} while (p != head);		// 반복문 종료 조건
	printf("%d->", p->data); // 마지막 노드 출력
}

ListNode* insert_first(ListNode* head, element data)
{			// 리스트 첫번째에 노드 삽입
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	// 노드 동적 할당으로 생성
	node->data = data;		// 입력된 데이터 저장
	if (head == NULL) {		// head가 비어있으면
		head = node;		// head에 생성한 노드 저장
		node->link = head;		// 노드의 링크에 head를 저장하며 원형리스트 생성
	}
	else {		// head가 비어있지 않은 경우
		node->link = head->link;	// (1) 생성한 노드의 링크에 head의 링크 저장
		head->link = node;		// (2)	head의 링크에 노드를 저장하며 원형리스트 구현
	}
	return head;	// 변경된 헤드 포인터를 반환한다. 
}

ListNode* insert_last(ListNode* head, element data)
{		// 리스트 마지막에 노드 삽입
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	// 노드 동적 할당으로 생성
	node->data = data;		// 노드에 입력된 데이터 저장
	if (head == NULL) {		// head가 비어있으면
		head = node;		// head에 노드 저장
		node->link = head;		// 노드의 링크에 head를 저장하여 원형리스트 구현
	}
	else {		// head가 비어있지 않은 경우
		node->link = head->link;	// (1)	노드의 링크에 head의 링크 저장
		head->link = node;		// (2)	head의 링크에 노드 저장
		head = node;		// (3)	head에 노드를 저장하여 원형리스트 구현
	}
	return head;	// 변경된 헤드 포인터를 반환한다. 
}
// 원형 연결 리스트 테스트 프로그램
int main(void)
{
	ListNode* head = NULL;
	// 헤드 초기화
	// list = 10->20->30->40
	head = insert_last(head, 20);	// 원형리스트 마지막에 20저장
	head = insert_last(head, 30);	// 원형리스트 마지막에 30저장
	head = insert_last(head, 40);	// 원형리스트 마지막에 40저장
	head = insert_first(head, 10);	// 원형리스트 처음에 10저장
	print_list(head);		// 원형리스트 출력
	return 0;		// 종료
}