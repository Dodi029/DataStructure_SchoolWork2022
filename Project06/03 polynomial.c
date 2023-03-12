#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode { // 노드 타입
	int coef;				// 계수
	int expon;				// 지수
	struct ListNode *link;
} ListNode;

// 연결 리스트 헤더
typedef struct ListType { // 리스트 헤더 타입
	int size;				// 길이
	ListNode *head;			// 헤드
	ListNode *tail;			// 테일
} ListType;

// 오류 함수
void error(char *message)	// 오류일 경우
{
	fprintf(stderr, "%s\n", message);
		// 버퍼 문제로 printf()가 제대로 출력되지 않을 수 있기 때문에
		// fprintf()에 stderr을 사용하여 버퍼 없이 출력하게 함
	exit(1);	// 프로세스 종료
				// exit(1)은 "에러메시지 종료"
}

//  리스트 헤더 생성 함수
ListType* create()
{
	ListType *plist = (ListType *)malloc(sizeof(ListType));	// 리스트 타입 크기만큼 동적 생성
	plist->size = 0;										// size 초기화
	plist->head = plist->tail = NULL;						// 헤드, 테일 초기화
	return plist;
}															// 생성한 리스트 헤더 리턴

// plist는 연결 리스트의 헤더를 가리키는 포인터, coef는 계수, 
// expon는 지수
void insert_last(ListType* plist, int coef, int expon)		// 리스트 맨 뒤에 노드 삽입 함수
{
	ListNode* temp =
		(ListNode *)malloc(sizeof(ListNode));				// 리스트 동적 생성
	if (temp == NULL) error("메모리 할당 에러");				// 리스트가 비어있을 경우 에러 출력
	temp->coef = coef;										// 계수 저장
	temp->expon = expon;									// 지수 저장
	temp->link = NULL;										// 링크에 NULL 저장
	if (plist->tail == NULL) {								// 리스트 타입에 테일이 NULL일 경우
															// 테일이 비어있을 경우
		plist->head = plist->tail = temp;					/// 헤드와 테일에 삽입한 노드 저장
	}
	else {													// 테일이 비어있지 않은 경우
		plist->tail->link = temp;							// 테일의 링크에 삽입한 노드 저장
		plist->tail = temp;									// 테일에 삽입한 노드 저장
	}
	plist->size++;											// 리스트 타입의 길이 증가
}

// list3 = list1 + list2
void poly_add(ListType* plist1, ListType* plist2, ListType* plist3)
{		// 두 연결리스트 (=두 다항식)을 더한 리스트(=다항식)을 만드는 함수
	ListNode* a = plist1->head;									// 첫 번쨰 리스트(다항식) head 저장
	ListNode* b = plist2->head;									// 첫 번쨰 리스트(다항식) head 저장
	int sum;

	while (a && b) {											// 두 리스트(다항식)이 존재할 경우
		if (a->expon == b->expon) {   // a의 차수 == b의 차수 일 경우
			sum = a->coef + b->coef;		// 계수에 저장된 데이터를 합침
			if (sum != 0)					// 더한 데이터가 0이 아닌 경우
				insert_last(plist3, sum, a->expon);		// 새로 만든 리스트의 맨 뒤 지수 부분에 삽입
			a = a->link; b = b->link;					// 리스트1과 리스트2 노드 위치 이동
		}
		else if (a->expon > b->expon) {  // a의 차수 > b의 차수 인 경우 
			insert_last(plist3, a->coef, a->expon);		// 새로 만든 리스트 맨 뒤에 리스트1 지수, 계수 저장
			a = a->link;								// 리스트1의 노드 위치 이동
		}
		else {					// a의 차수 < b의 차수
			insert_last(plist3, b->coef, b->expon);		// 새로 만든 리스트 맨 뒤에 리스트2 지수, 계수 저장
			b = b->link;								// 리스트2의 노드 위치 이동
		}
	}

	// a나 b중의 하나가 먼저 끝나게 되면 남아있는 항들을 모두 
	// 결과 다항식으로 복사
	for (; a != NULL; a = a->link)					// 리스트1에 노드가 남아있을 경우
		insert_last(plist3, a->coef, a->expon);		// 새로 만든 리스트 맨 뒤에 리스트1 지수, 계수 저장
	for (; b != NULL; b = b->link)					// 리스트2에 노드가 남아있을 경우
		insert_last(plist3, b->coef, b->expon);		// 새로 만든 리스트 맨 뒤애 리스트2 지수, 계수 저장
}

void poly_print(ListType* plist)		// 리스트(=다항식) 출력하는 함수
{
	ListNode* p = plist->head;			// 리스트 head값 저장

	printf("polynomial = ");			// 리스트(=다항식) 출력
	for (; p; p = p->link) {			// 노드 위치 이동
		printf("%d^%d + ", p->coef, p->expon);	// 노드에 저장된 지수, 계수 출력
	}
	printf("\n");
}
//
int main(void)
{
	ListType *list1, *list2, *list3;	// 리스트(=다항식) 3개 선언

	// 연결 리스트 헤더 생성
	list1 = create();					// 리스트1 생성
	list2 = create();					// 리스트2 생성
	list3 = create();					// 리스트3 생성

	// 다항식 1을 생성 
	insert_last(list1, 3, 12);			// 리스트1에 지수, 계수 저장
	insert_last(list1, 2, 8);			// 리스트1에 지수, 계수 저장
	insert_last(list1, 1, 0);			// 리스트1에 지수, 계수 저장

	// 다항식 2를 생성 
	insert_last(list2, 8, 12);			// 리스트2에 지수, 계수 저장
	insert_last(list2, -3, 10);			// 리스트2에 지수, 계수 저장
	insert_last(list2, 10, 6);			// 리스트2에 지수, 계수 저장

	poly_print(list1);					// 리스트1 출력
	poly_print(list2);					// 리스트2 출력

	// 다항식 3 = 다항식 1 + 다항식 2
	poly_add(list1, list2, list3);		// 리스트3에 리스트1, 2를 더하고 저장
	poly_print(list3);					// 리스트3 출력

	free(list1); free(list2); free(list3);	// 동적 생성한 메모리들 해제
}