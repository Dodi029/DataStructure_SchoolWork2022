#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode { 	// 노드 타입
	element data;			// 노드에 데이터를 저장할 부분
	struct ListNode *link;	// 다음 노트의 링크를 저장할 부분
} ListNode;					// ListNode 구조체로 선언

ListNode* insert_first(ListNode* head, element value)		// 연결리스트의 첫 번쨰 노드에 삽입하는 함수
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));		//(1) 노드 생성 (동적 생성)
	p->data = value;										//(2)	입력한 값(value)을 노드의 데이터에 저장
	p->link = head;											//(3)헤드 포인터의 값을 복사	head가 가지고 있는 주소값을 링크에 저장하여
															//		첫 번째 노드에 위치하도록 함
	head = p;												//(4)헤드 포인터 변경		// head에 삽입한 노드의 주소를 저장하도록 함
	return head;											// head 주소값 리턴
}

// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)  MAX값 없음
	p->data = value;		//(2)
	p->link = pre->link;	//(3)	
	pre->link = p;		//(4)	
	return head;		//(5)	
}

void print_list(ListNode* head)							// 노드의 데이터를 출력하는 함수
{
	for (ListNode* p = head; p != NULL; p = p->link)	// 노드의 링크가 NULL이 아니면 계속 반복
														// NULL이 나올 때까지 반복
		printf("%d->", p->data);						// 노드의 데이터 출력
	printf("NULL \n");									// 반복문이 끝나면 NULL출력
}
ListNode* reverse(ListNode *head)	// 리스트를 역순으로 만드는 함수
{
									// 순회 포인터로 p, q, r을 사용
	ListNode *p, *q, *r;

	p = head;					   // p는 역순으로 만들 리스트
	q = NULL;					  // q는 역순으로 만들 노드
	while (p != NULL) {				// p가 리스트일 경우(비어있지 않을 경우)
		r = q;          // r은 역순으로 된 리스트.    
						// r은 q, q는 p를 차례로 따라간다.
		q = p;
		p = p->link;
		q->link = r;      // q의 링크 방향을 바꾼다.
	}
	return q;
}
// 테스트 프로그램
int main(void)
{
	ListNode* head1 = NULL;			// 리스트1 선언
	ListNode* head2 = NULL;			// 리스트2 선언

	//head1 = insert_first(head1, 10);// 리스트1 맨 앞에 10 저장
	//head1 = insert_first(head1, 20);// 리스트1 맨 앞에 20 저장
	//head1 = insert_first(head1, 30);// 리스트1 맨 앞에 30 저장
	//print_list(head1);				// 리스트1 출력

	head1 = insert(head1, 0, 10);
	head1 = insert(head1, 0, 20);
	head1 = insert(head1, 0, 30);
	print_list(head1);

	head2 = reverse(head1);			// 리스트2는 리스트1의 역순
	print_list(head2);				// 리스트2 출력
	return 0;
}
