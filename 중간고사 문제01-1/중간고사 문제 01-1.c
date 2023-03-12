#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 10
#define MAX_DEGREE 101
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef int element;
typedef struct { 				// ť Ÿ�� ����
	int  front;
	int rear;
	element data[MAX_QUEUE_SIZE];
} QueueType;

typedef struct { 			// ���׽� ����ü Ÿ�� ����
	int degree;			// ���׽��� ����
	float coef[MAX_DEGREE];	// ���׽��� ���
} polynomial;

int item = 0;
QueueType q;

// C = A+B ���⼭ A�� B�� ���׽��̴�. ����ü�� ��ȯ�ȴ�. 
polynomial poly_add1(polynomial A, polynomial B)
{
	polynomial C;				// ��� ���׽�
	int Apos = 0, Bpos = 0, Cpos = 0;	// �迭 �ε��� ����
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree); // ��� ���׽� ����

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {  // A�� > B��
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {  // A�� == B��
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else {			// B�� > A��
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

void print_poly(polynomial p)
{
	int item = 0;
	QueueType q;
	StackType* s;

	init_queue(&q);

	for (int i = p.degree; i > 0; i--) {
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
		item = p.coef[p.degree];
		push(s, item);
		enqueue(&q, item);
	}
	printf("%3.1f \n", p.coef[p.degree]);
	item = p.coef[p.degree];
	enqueue(&q, item);
}

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// �ʱ�ȭ
int init_queue(QueueType* q)
{
	q->rear = -1;
	q->front = -1;
}

void queue_print(QueueType* q)
{
	FILE* p1 = fopen("05-1.txt", "at+");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		if (i <= q->front || i > q->rear)
			fprintf(p1, "");
		else
			fprintf(p1, "%d", q->data[i]);
	}
	printf("\n");
	fclose(p1);
}
// �������ִ°�
int is_full(QueueType* q)
{
	if (q->rear == MAX_QUEUE_SIZE - 1)
		return 1;
	else
		return 0;
}
// ����ִ°�
int is_empty(QueueType* q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

int enqueue(QueueType* q, int item)
{
	if (is_full(q)) {
		error("ť�� ��ȭ�����Դϴ�.");
		return 0;
	}
	q->data[++(q->rear)] = item;
}

int dequeue(QueueType* q)
{
	if (is_empty(q)) {
		error("ť�� ��������Դϴ�.");
		return -1;
	}
	int item = q->data[++(q->front)];
	return item;
}
// ===== ���� �ڵ��� ���� ===== 
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 


int main(void)
{
	polynomial a = { 5,{ 10, 0, 0, 0, 6, 3 } };
	polynomial b = { 4,{ 1, 0, 5, 0, 7 } };
	polynomial c;

	print_poly(a);
	print_poly(b);
	c = poly_add1(a, b);
	printf("---------------------------------------------------------------------------- - \n");
	print_poly(c);

	enqueue(&q, 20); queue_print(&q);
	enqueue(&q, 30); queue_print(&q);

	item = dequeue(&q); queue_print(&q);
	item = dequeue(&q); queue_print(&q);
	item = dequeue(&q); queue_print(&q);
	return 0;
}