#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int element;
typedef struct DListNode {	// 이중연결 노드 타입
	char name[1024];				// 제목
	char time[1024];
	char like[1024];
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
	FILE* fp = fopen("06.txt", "w");
	for (p = phead->rlink; p != phead; p = p->rlink) {
		// head의 다음 링크부터 head가 될때까지 다음 링크로 계속 이동
		fprintf(fp, "%s\t%s\t%s\n", p->name, p->time,p->like);
	}	// 노드의 데이터 출력
	fclose(fp);
}
// 새로운 데이터를 노드 before의 오른쪽에 삽입한다.
void dinsert(DListNode* before, char* name, char* time, char* like)
{	// 새로운 노드 삽입하는 함수
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	// 새로운 노드를 동적 할당으로 생성
	//strcpy(newnode->data, data);
	strcpy(newnode->name, name);
	strcpy(newnode->time, time);
	strcpy(newnode->like, like);
	newnode->llink = before;	// 이전노드의 링크를 왼쪽 링크에 저장
	newnode->rlink = before->rlink;	// 다음 노드의 링크를 기존 링크의 다음 링크로 받아옴
	before->rlink->llink = newnode;	// 다음 노드의 이전노드 링크에 새로운 노드링크 저장
	before->rlink = newnode;		// 이전 노드의 다음링크 부분에 새로운 노드 저장
}
void bubbleSortNode(DListNode* head) {
	DListNode* p, * q;
	for (p = head->rlink; p != head; p = p->rlink)
	{
		for (q = head->rlink; q->rlink != head; q = q->rlink)
			if (strcmp(q->name, q->rlink->name) == 1)
			{
				char tmp;
				tmp = q->name;
				q->name = q->rlink->name;
				q->rlink->name = tmp;
			}
	}
}

// 이중 연결 리스트 테스트 프로그램
int main(void)
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	// head 노드 동적 생성
	init(head);		// head 초기화
	bubbleSortNode(head);

	dinsert(head, "Bohemian Rhapsody", "05분57초", "1,109,566");
	dinsert(head, "I was born to love you", "04분50초", "1,112,154");
	dinsert(head, "Love of my life", "03분38초", "1,060,154");
	dinsert(head, "Radio Ga Ga", "05분48초", "1,022,562");
	dinsert(head, "We will Rock you", "03분08초", "1,010,666");

	//char al[1024] = "Dynamite";

	for (DListNode* k = head; k != NULL; k = k->rlink) {
		if (strcmp(k->name, "Dynamite") == -1) {
			//k = k->llink;
			dinsert(k->llink, "Dynamite", "03분40초", "10,040,154");
		}
	}
	print_dlist(head);
	
	free(head);

	system("notepad.exe 06.txt");
	// 동적 할당된 head 삭제
	return 0;
}