#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101
#define MAX_QUEUE_SIZE 100
#define MAX_STACK_SIZE 100

FILE* fp1;

typedef float element;
typedef int element1;
typedef struct { 		
	int degree;			// 다항식의 차수
	float coef[MAX_DEGREE];	// 다항식의 계수

	int  front;
	int rear;
	
	element data[MAX_QUEUE_SIZE];
	element1 data1[MAX_STACK_SIZE];
	int top;
} QueueType;
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// C = A+B 여기서 A와 B는 다항식이다. 구조체가 반환된다. 
QueueType poly_add1(QueueType A, QueueType B)
{
	QueueType C;				// 결과 다항식
	int Apos = 0, Bpos = 0, Cpos = 0;	// 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {  // A항 > B항
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {  // A항 == B항
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else {			// B항 > A항
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

void init_queue(QueueType* q)
{
	q->rear = -1;
	q->front = -1;
}
void queue_print(QueueType* q) {
	for (int i = 0; i <q->degree; i++) {
		if (i <= q->front || i > q->rear) {}
		else
			if (q->data[i] != 0) {
				fprintf(fp1, "%3.1fx^%d + ", q->data[i], q->degree - i);
			}
	}
	fprintf(fp1, "%3.1f \n", q->data[q->degree]);
	fclose(fp1);
}

int is_full(QueueType* q)
{
	if (q->rear == MAX_QUEUE_SIZE - 1)
		return 1;
	else
		return 0;
}
int is_empty(QueueType* q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}
void enqueue(QueueType* q) {
	if (is_full(q)) {
		error("큐가 포화상태입니다.");
		return;
	}
	for (int i = q->degree; i > 0; i--) {
		q->data[++(q->rear)] = q->coef[q->degree-i];
	}
	q->data[++(q->rear)] = q->coef[q->degree];
}

int dequeue(QueueType* q) {
	if (is_empty_stack(q)) {
		error("큐가 공백상태입니다.");
		return -1;
	}
	int item = q->data[++(q->front)];
	return item;
}

// ===== 스택 코드의 시작 ===================================================================
typedef struct {
	int degree;			// 다항식의 차수
	float coef[MAX_DEGREE];	// 다항식의 계수

	int  front;
	int rear;

	element data[MAX_QUEUE_SIZE];
	element1 data1[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(QueueType* s)
{
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty_stack(QueueType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full_stack(QueueType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
QueueType push(QueueType* s)
{
	if (is_full_stack(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data1[++(s->top)];
	}
}
// 삭제함수
element1 pop(QueueType* s)
{
	if (is_empty_stack(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else {
		for (int i = 0; i < s->degree; i++) {
			if (i <= s->front || i > s->rear) {}
			else
				if (s->data[i] != 0) {
					printf( "%3.1fx^%d + ", s->data[i], s->degree - i);
				}
		}
		printf("%3.1f \n", s->data[s->degree]);
		(s->top)--;
	}
}
// 피크함수
element1 peek(QueueType* s)
{
	if (is_empty_stack(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

// 주함수
int main(void) {
	QueueType a = { 5,{ 10, 0, 0, 0, 6, 3 } };
	QueueType b = { 4,{ 1, 0, 5, 0, 7 } };

	QueueType A = { 5,{ 9, 0, 0, 0, 6, 2 } };
	QueueType B = { 4,{ 1, 0, 5, 0, 7 } };

	QueueType c;
	QueueType C;

	init_stack(&s);

	fp1 = fopen("05-1.txt", "at+");

	fprintf(fp1, "[다항식 1]\n");
	init_queue(&a);
	enqueue(&a);
	queue_print(&a);

	init_queue(&b);
	enqueue(&b);
	queue_print(&b);
	c = poly_add1(a, b);

	push(&c);

	fprintf(fp1, "[다항식 2]");
	init_queue(&A);
	enqueue(&A);
	queue_print(&A);

	init_queue(&B);
	enqueue(&B);
	queue_print(&B);
	C = poly_add1(A, B);

	push(&C);

	FILE* fp2 = open("05-2.txt", "at+");
	pop(&s);
	pop(&s);
	//fprintf(fp2, "%lf\n", pop(s));
	//fprintf(fp2, "lf\n", pop(s));

	fclose(fp1);
	fclose(fp2);
	system("notepad.exe 05-1.txt");

	return 0;
}