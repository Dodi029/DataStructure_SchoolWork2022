#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode { 		// 노드 타입
	element data;				// 노드에 데이터를 저장할 부분
	struct ListNode *link;		// 다음 노트의 링크를 저장할 부분
} ListNode;						// ListNode 구조체로 선언


ListNode* insert_first(ListNode *head, element value)	// 연결리스트의 첫 번쨰 노드에 삽입하는 함수
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));	//(1) 노드 생성 (동적 생성)
	p->data = value;									//(2)	입력한 값(value)을 노드의 데이터에 저장
	p->link = head;										//(3)헤드 포인터의 값을 복사	head가 가지고 있는 주소값을 링크에 저장하여
														//		첫 번째 노드에 위치하도록 함
	head = p;											//(4)헤드 포인터 변경		// head에 삽입한 노드의 주소를 저장하도록 함
	return head;										// head 주소값 리턴
}

void print_list(ListNode *head)							// 노드의 데이터를 출력하는 함수
{
	for (ListNode *p = head; p != NULL; p = p->link)	// 노드의 링크가 NULL이 아니면 계속 반복
														// NULL이 나올 때까지 반복
		printf("%d->", p->data);						// 노드의 데이터 출력
	printf("NULL \n");									// 반복문이 끝나면 NULL출력
}
ListNode* concat_list(ListNode *head1, ListNode *head2)	// 두 리스트를 합치는 함수
{
	if (head1 == NULL) return head2;					// 리스트1이 없으면 리스트2 리턴
	else if (head2 == NULL) return head1;				// 리스트2가 없으면 리스트1 리턴
	else {												// 둘다 아닌경우 (리스트1, 2가 있을 경우)
		ListNode *p;						
		p = head1;										// 리스트1의 head가 가진 주소값을 p에 저장
		while (p->link != NULL)							// 리스트1에서 링크가 NULL이 나올 때까지
			p = p->link;								// 노드 이동
		p->link = head2;								// 리스트1에서 링크가 NULL일 경우 링크에 리스트2 head값 저장
		return head1;									// 리스트2와 합쳐진 리스트1의 head 주소값 리턴
	}
}
// 테스트 프로그램
int main(void)
{
	ListNode* head1 = NULL;								// 리스트1 선언
	ListNode* head2 = NULL;								// 리스트2 선언

	head1 = insert_first(head1, 10);					// 리스트1 맨 앞에 10 저장
	head1 = insert_first(head1, 20);					// 리스트1 맨 앞에 20 저장
	head1 = insert_first(head1, 30);					// 리스트1 맨 앞에 30 저장
	print_list(head1);									// 리스트1 출력

	head2 = insert_first(head2, 40);					// 리스트2 맨 앞에 40 저장
	head2 = insert_first(head2, 50);					// 리스트2 맨 앞에 50 저장
	print_list(head2);									// 리스트2 출력

	ListNode *total = concat_list(head1, head2);		// 리스트1, 2를 합치는 함수 실행
	print_list(total);									// 합쳐진 리스트 출력
	return 0;											// 끝내기
}
