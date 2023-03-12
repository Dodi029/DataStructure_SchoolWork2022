#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101
#define MAX_STACK_SIZE 100

typedef struct { 			// ���׽� ����ü Ÿ�� ����-------------------
	int degree;			// ���׽��� ����
	float coef[MAX_DEGREE];	// ���׽��� ���
} polynomial;

int item = 0;
QueueType q;
int degree;
float coef[MAX_DEGREE];
int i;

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

int print_poly(polynomial p)
{
	for (int i = p.degree; i > 0; i--) {
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
		degree = p.coef[p.degree - i];
		coef[i] = i;
		enqueue(&q, degree, coef[]);
	}
	printf("%3.1f \n", p.coef[p.degree]);
	degree = p.coef[p.degree];
	coef[p.degree + 1] = 0;
	enqueue(&q, item, coef[MAX_DEGREE]);
}			// ���׽� ����ü---------------

typedef int element;		// ����ť ���ۺκ� -------------------
typedef struct { 				// ť Ÿ��
	int  front;
	int rear;
	element  data[MAX_QUEUE_SIZE];
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// front rear �ʱ�ȭ
void init_queue(QueueType* q)
{
	q->rear = -1;
	q->front = -1;
}
void queue_print(QueueType* q)
{
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		if (i <= q->front || i > q->rear)
			printf("");
		else
			printf("%d | ", q->data[i]);
	}
	printf("\n");
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
void enqueue(QueueType* q, int item,float ceof[MAX_DEGREE])
{
	if (is_full(q)) {
		error("ť�� ��ȭ�����Դϴ�.");
		return;
	}
	q->data[++(q->rear)] = item;
	queue_print(&q);
	q->data[(q->rear)] = ceof[MAX_DEGREE];
	queue_print(&q);
}

int dequeue(QueueType* q)
{
	if (is_empty(q)) {
		error("ť�� ��������Դϴ�.");
		return -1;
	}
	int item = q->data[++(q->front)];
	return item;
}		//����ť----------------------

// ===== ���� �ڵ��� ���� =====
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

int main(void)			// ����ť ���Լ�
{
	int item = 0;
	QueueType q;

	init_queue(&q);

	enqueue(&q, 10); queue_print(&q);
	enqueue(&q, 20); queue_print(&q);
	enqueue(&q, 30); queue_print(&q);

	item = dequeue(&q); queue_print(&q);
	item = dequeue(&q); queue_print(&q);
	item = dequeue(&q); queue_print(&q);
	return 0;
}

int main(void)			// ���׽� ����ü ���Լ�
{
	polynomial a = { 5,{ 10, 0, 0, 0, 6, 3 } };
	polynomial b = { 4,{ 1, 0, 5, 0, 7 } };
	polynomial c;

	print_poly(a);
	print_poly(b);
	c = poly_add1(a, b);
	printf("---------------------------------------------------------------------------- - \n");
	print_poly(c);
	return 0;
}

int main(void)			// ���� ���Լ�
{
	StackType* s;

	s = (StackType*)malloc(sizeof(StackType));
	init_stack(s);
	push(s, 1);
	push(s, 2);
	push(s, 3);
	printf("%d\n", pop(s));
	printf("%d\n", pop(s));

	printf("%d\n", pop(s));
	free(s);
}
