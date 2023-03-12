#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct ListNode
{ 	// 노드 타입
	int num;		// 학번
	int name1;		// 이름
	int name2;		// 이름
	int name3;		// 이름
	float score;		// 학점

	struct ListNode* link;
} ListNode;

// 리스트의 항목 출력
void print_list(ListNode* head)
{
	ListNode* p;		// 노드 포인터

	if (head == NULL) return;		// head가 비어있으면 함수 종료
	p = head->link;			// head의 링크로 첫번째 노드로 이동
	do {		// 반복문
		printf("%d\t%c%c%c\t%.2lf\n", p->num, p->name1, p->name2, p->name3, p->score);
		// 학번, 이름 이니셜, 학점을 출력
		printf("--------------------\n");
		// 가독성을 위해 작성
		p = p->link;			// 다음 노드로 위치 이동
	} while (p != head);		// 반복문 종료 조건
	printf("%d\t%c%c%c\t%.2lf\n", p->num, p->name1, p->name2, p->name3, p->score);
	// 마지막 노드(학생의 정보)를 출력
}

ListNode* insert_first(ListNode* head, int num, int name1, int name2, int name3, float score)
{			// 리스트 첫번째에 노드 삽입
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	// 노드 동적 할당으로 생성

	node->num = num;		// 입력된 학번 저장
	node->name1 = name1;		// 입력된 이니셜 저장
	node->name2 = name2;		// 입력된 이니셜 저장
	node->name3 = name3;		// 입력된 이니셜 저장
	node->score = score;	// 입력된 학점 저장

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

ListNode* insert_last(ListNode* head, int num, int name1, int name2, int name3, float score)
{		// 리스트 마지막에 노드 삽입
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	// 노드 동적 할당으로 생성

	node->num = num;		// 입력된 학번 저장
	node->name1 = name1;		// 입력된 이름 저장
	node->name2 = name2;	// 입력된 이니셜 저장
	node->name3 = name3;	// 입력된 이니셜 저장
	node->score = score;	// 입력된 학점 저장

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
	srand(time(NULL));		// 비규칙적 무작위 난수가 생기도록 선언
	ListNode* head = NULL;		// head값 초기화
	// 헤드 초기화
	for (int i = 0; i < 50; i++) {	// 500명 학번, 이름, 학점 생성
		int num = rand();		// 난수 생성
		num = num % 10000;		// 네자리 난수 생성
		num = 20220000 + num; // 무작위 학번 생성

		int name1, name2, name3;		// 이니셜 생성
		//int nameary[3];
		//for (int i = 0; i < 3; i++) {	// 학생 이름 무작위 생성 코드
		//	name = 65 + rand() % 26;	// 아스키 값이 65 = 'A'이므로
										// 랜덤으로 0~25까지 더하면 대문자 알파벳이 나옴
		//	nameary[i] = name;			// 나온 난수를 이름 배열에 저장
		//}
		name1 = 65 + rand() % 26;		// 첫번째 이니셜
		name2 = 65 + rand() % 26;		// 두번째 이니셜
		name3 = 65 + rand() % 26;		// 세번째 이니셜

		float score;		// 무작위 학점 생성
		score = (float)(rand() % 45) / 10;	//0부터 4.5까지 난수 생성

		if (score < 3.0) {	// 학점 3.0 이하의 학생들만 출력
			head = insert_last(head, num, name1, name2, name3, score);
		}
		// 리스트 맨 뒤에 노드 생성
	}

	print_list(head);		// 원형리스트 출력

	return 0;		// 종료
}