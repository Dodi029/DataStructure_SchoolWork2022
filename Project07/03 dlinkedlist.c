#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int element;
typedef struct DListNode {	// 이중연결 노드 타입
	element data;				// 데이터 저장
	struct DListNode* llink;	// 이전 링크 저장
	struct DListNode* rlink;	// 다음 링크 저장
} DListNode;					// 구조체 선언

// 이중 연결 리스트를 초기화
void init(DListNode* phead)
{
	phead->llink = phead;	// head의 이전 링크가 head가 되도록 초기화
	phead->rlink = phead;	// head의 당므 링크가 head가 되도록 초기화
}

// 이중 연결 리스트의 노드를 출력
void print_dlist(DListNode* phead)
{
	DListNode* p;			// 구조체 포인터 선언
	for (p = phead->rlink; p != phead; p = p->rlink) {
	// head의 다음 링크부터 head가 될때까지 다음 링크로 계속 이동
		printf("<-| |%d| |-> ", p->data);
	}	// 노드의 데이터 출력
	printf("\n");
}
// 새로운 데이터를 노드 before의 오른쪽에 삽입한다.
void dinsert(DListNode *before, element data)
{	// 새로운 노드 삽입하는 함수
	DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
	// 새로운 노드를 동적 할당으로 생성
	//strcpy(newnode->data, data);
	newnode->data = data;		// 데이터 삽입
	newnode->llink = before;	// 이전노드의 링크를 왼쪽 링크에 저장
	newnode->rlink = before->rlink;	// 다음 노드의 링크를 기존 링크의 다음 링크로 받아옴
	before->rlink->llink = newnode;	// 다음 노드의 이전노드 링크에 새로운 노드링크 저장
	before->rlink = newnode;		// 이전 노드의 다음링크 부분에 새로운 노드 저장
}
// 노드 removed를 삭제한다.  
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;		// 삭제할 노드가 head면 함수 종료
	removed->llink->rlink = removed->rlink;
	// 삭제할 노드의 이전 노드의 다음 노드링크 부분에 삭제할 노드의 다음 노드링크를 저장
	removed->rlink->llink = removed->llink;
	// 삭제할 노드의 다음 노드의 이전노드링크에 삭제할 노드의 이전 노드 링크 저장
	free(removed);
	// 삭제할 노드를 free()를 통해 동적 할당 해제
}

// 이중 연결 리스트 테스트 프로그램
int main(void)
{
	DListNode* head = (DListNode *)malloc(sizeof(DListNode));
	// head 노드 동적 생성
	init(head);		// head 초기화
	printf("추가 단계\n");
	for (int i = 0; i < 5; i++) {
		// 헤드 노드의 오른쪽에 삽입
		dinsert(head, i);
		// 반복문 횟수만큼 데이터에 값 저장
		print_dlist(head);
		// 리스트 출력
	}
	printf("\n삭제 단계\n");
	for (int i = 0; i < 5; i++) {
		// 삽입했던 횟수만큼 노드 삭제
		print_dlist(head);
		// 리스트 출력
		ddelete(head, head->rlink);
		// head의 다음 노드 삭제
	}
	free(head);
		// 동적 할당된 head 삭제
	return 0;
}