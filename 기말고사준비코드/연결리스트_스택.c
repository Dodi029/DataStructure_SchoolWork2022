#include <stdio.h>
#include <malloc.h>

typedef int element;
typedef struct StackNode {
	element data;		// 노드의 데이터 저장
	struct StackNode* link;	// 링크 저장
} StackNode;		// 구조체 선언

typedef struct {
	StackNode* top;		// 스택의 top 선언
} LinkedStackType;	// 스택 선언
// 초기화 함수
void init(LinkedStackType* s)	// top 초기화 함수
{
	s->top = NULL;		// top 초기화
}
// 공백 상태 검출 함수
int is_empty(LinkedStackType* s)
{ // 스택이 비어있는지 확인하는 함수
	return (s->top == NULL);	// top이 NULL임을 리턴
}
// 포화 상태 검출 함수
int is_full(LinkedStackType* s)
{	// 스택이 가득차있는지 확인하는 함수
	return 0;	// 가득차있으면 0 리턴
}
// 삽입 함수
void push(LinkedStackType* s, element item)
{	// 스텍에 삽입하는 함수
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	// 스택에 삽입할 노드 동적 생성
	temp->data = item;	// 입력한 값 item을 노드의 데이터에 저장
	temp->link = s->top;	// 스택의 탑을 삽입한 노드의 다음 링크에 저장
	s->top = temp;		// 생성안 노드를 스택의 top에 저장
}
void print_stack(LinkedStackType* s)
{	//스택을 출력하는 함수
	for (StackNode* p = s->top; p != NULL; p = p->link)
		// top부터 시작해 NULL이 될때까지 위치를 이동 반복
		printf("%d->", p->data);
	// 이동하면서 출력
	printf("NULL \n");	// 마지막에는 NULL 출력
}
// 삭제 함수
element pop(LinkedStackType* s)
{	// 스택 맨 위에 있는 노드를 출력하는 함수
	if (is_empty(s)) {		// 스택이 비어있다면
		fprintf(stderr, "스택이 비어있음\n");	// 비어있다고 출력
		exit(1);	// 프로세스 종료
	}
	else {		// 스택이 비어있지 않는 경우
		StackNode* temp = s->top;	// top이 위치한 곳이 temp로 설정
		int data = temp->data;		// temp의 데이터를 int data에 저장
		s->top = s->top->link;		// top의 위치를 이전노드로 변경
		free(temp);					// temp 노드 삭제
		return data;				// 저장한 데이터 리턴
	}
}
// 피크 함수
element peek(LinkedStackType* s)
{		// 맨 위에 있는 노드가 무엇인지 출력하는 함수
	if (is_empty(s)) {	// 스택이 비어있다면
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);	// 프로세스 종료
	}
	else {		// 스택이 비어있지 않은 경우
		return s->top->data;	// top에 있는 데이터 리턴
	}
}
// 주 함수
int main(void)
{
	LinkedStackType s;		// 리스트 스택 선언
	init(&s);		// 스택 초기화
	push(&s, 1); print_stack(&s);	// 스택에 1삽입 후 출력
	push(&s, 2); print_stack(&s);	// 스택에 2삽입 후 출력
	push(&s, 3); print_stack(&s);	// 스택에 3삽입 후 출력
	pop(&s); print_stack(&s);		// 스택 pop후 출력
	pop(&s); print_stack(&s);		// 스택 pop후 출력
	pop(&s); print_stack(&s);		// 스택 pop후 출력
	return 0;
}

// 개선버전
/*
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include<stdlib.h>
#include <string.h>

typedef int element;
typedef struct StackNode {
	int hour, minute;		// 시간 저장
	int name1, name2, name3;	// 이름 이니셜 저장
	int num1, num2;		// 전화번호 앞 뒤 저장
	struct StackNode* link;	// 링크 저장
} StackNode;		// 구조체 선언

typedef struct {
	StackNode* top;		// 스택의 top 선언
} LinkedStackType;	// 스택 선언
// 초기화 함수
void init(LinkedStackType* s)	// top 초기화 함수
{
	s->top = NULL;		// top 초기화
}
// 공백 상태 검출 함수
int is_empty(LinkedStackType* s)
{ // 스택이 비어있는지 확인하는 함수
	return (s->top == NULL);	// top이 NULL임을 리턴
}
// 포화 상태 검출 함수
int is_full(LinkedStackType* s)
{	// 스택이 가득차있는지 확인하는 함수
	return 0;	// 가득차있으면 0 리턴
}
// 삽입 함수
void push(LinkedStackType* s, int name1, int name2, int name3, int num1, int num2)
{	// 스텍에 삽입하는 함수
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	// 스택에 삽입할 노드 동적 생성
	temp->name1 = name1;		// 무작위 첫번째 이니셜 저장
	temp->name2 = name2;		// 무작위 두번째 이니셜 저장
	temp->name3 = name3;		// 무작위 세번째 이니셜 저장
	temp->num1 = num1;		// 무작위 앞 전화번호 저장
	temp->num2 = num2;		// 무작위 뒤 전화번호 저장
	temp->link = s->top;	// 스택의 탑을 삽입한 노드의 다음 링크에 저장
	s->top = temp;		// 생성안 노드를 스택의 top에 저장
}
void print_stack(LinkedStackType* s)
{	//스택을 출력하는 함수
	for (StackNode* p = s->top; p != NULL; p = p->link) {
		// top부터 시작해 NULL이 될때까지 위치를 이동 반복
		printf("%c%c%c\t", p->name1, p->name2, p->name3);
		// 시간 분 이니셜 3자리 출력
		printf("010-%d-%d\n", p->num1, p->num2);
		// 전화번호 출력
	}
}
// 삭제 함수
element pop(LinkedStackType* s)
{	// 스택 맨 위에 있는 노드를 출력하는 함수
	if (is_empty(s)) {		// 스택이 비어있다면
		fprintf(stderr, "스택이 비어있음\n");	// 비어있다고 출력
		exit(1);	// 프로세스 종료
	}
	else {		// 스택이 비어있지 않는 경우
		StackNode* temp = s->top;	// top이 위치한 곳이 temp로 설정
		int name1 = temp->name1;	// temp의 첫번째 이니셜을 name1에 저장
		int name2 = temp->name2;	// temp의 두번째 이니셜을 name2에 저장
		int name3 = temp->name3;	// temp의 세번째 이니셜을 name3에 저장
		int num1 = temp->num1;		// temp의 앞 전화번호를 num1에 저장
		int num2 = temp->num2;		// temp의 뒤 전화번호를 num2에 저장
		s->top = s->top->link;		// top의 위치를 이전노드로 변경
		free(temp);					// temp 노드 삭제
		return name1, name2, name3, num1, num2;	// 저장한 데이터 리턴
	}
}
// 피크 함수
element peek(LinkedStackType* s)
{		// 맨 위에 있는 노드가 무엇인지 출력하는 함수
	if (is_empty(s)) {	// 스택이 비어있다면
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);	// 프로세스 종료
	}
	else {		// 스택이 비어있지 않은 경우
		return s->top->hour;	// top에 있는 데이터 리턴
	}
}
// 주 함수
int main(void)
{
	LinkedStackType s;		// 리스트 스택 선언
	init(&s);		// 스택 초기화
	srand(time(NULL));	// 비규칙성 난수 생성

	for (int i = 0; i < 5; i++) {	// 5명 생성

		int name1, name2, name3;		// 이름 선언
		name1 = 65 + rand() % 26;		// 첫번째 이니셜
		name2 = 65 + rand() % 26;		// 두번째 이니셜
		name3 = 65 + rand() % 26;		// 세번째 이니셜

		int num1, num2;			// 전화번호 앞 뒤 선언
		num1 = rand();			// 앞 전화번호 난수 생성
		num2 = rand();			// 뒤 전화번호 난수 생성
		num1 = num1 % 10000;		// 무작위 앞 전화번호 4자리 생성
		num2 = num2 % 10000;		// 무작위 뒤 전화번호 4자리 생성

		push(&s, name1, name2, name3, num1, num2);
		// 생성한 시,분 ,이름 이니셜 3자리, 전화번호 무작위 8자리 저장
		print_stack(&s);	// 스택에 삽입 후 출력
	}
	for (int i = 0; i < 5; i++) {  // 생성한 개수 만큼 삭제
		pop(&s); print_stack(&s);		// 스택 pop후 출력
	}

	return 0;
}
*/