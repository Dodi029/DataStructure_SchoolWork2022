#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101
#define MAX_QUEUE_SIZE 100
#define MAX_STACK_SIZE 100

int value;
typedef float element;
typedef struct {
	int degree;			// ���׽��� ����
	float coef[MAX_DEGREE];	// ���׽��� ���

	int  front;
	int rear;

	int top;

	element data[MAX_QUEUE_SIZE];
	element data2[MAX_STACK_SIZE];
} QueueType;

FILE* fp1;
FILE* fp2;

// ���� �Լ�
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// C = A+B ���⼭ A�� B�� ���׽��̴�. ����ü�� ��ȯ�ȴ�. 
QueueType poly_add1(QueueType A, QueueType B) {
	QueueType C;				// ��� ���׽�
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

void init_queue(QueueType* q) {
	q->rear = -1;
	q->front = -1;
}
void queue_print(QueueType* q) {
	for (int i = 0; i < q->degree; i++) {
		if (i <= q->front || i > q->rear) {}
		else
			if (q->data[i] != 0) {
				fprintf(fp1, "%3.1fx^%d + ", q->data[i], q->degree - i);
			}
	}
	fprintf(fp1, "%3.1f \n", q->data[q->degree]);
}

int is_full(QueueType* q) {
	if (q->rear == MAX_QUEUE_SIZE - 1)
		return 1;
	else
		return 0;
}

int is_empty(QueueType* q) {
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

void enqueue(QueueType* q) {
	if (is_full(q)) {
		error("ť�� ��ȭ�����Դϴ�.");
		return;
	}
	for (int i = q->degree; i > 0; i--) {
		q->data[++(q->rear)] = q->coef[q->degree - i];
	}
	q->data[++(q->rear)] = q->coef[q->degree];

}

int dequeue(QueueType* q) {
	if (is_empty(q)) {
		error("ť�� ��������Դϴ�.");
		return -1;
	}
	int item = q->data[++(q->front)];
	return item;
}


// ���� �ʱ�ȭ �Լ�
void init_stack(QueueType* s) {
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty_stack(QueueType* s) {
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full_stack(QueueType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(QueueType* s) {
	if (is_full_stack(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else {
		for (int i = s->degree; i > 0; i--) {
			s->data2[++(s->top)] = s->coef[s->degree - i];
		}
	}
	s->data2[++(s->top)] = s->coef[s->degree];
	value = s->top;

}
// �����Լ�
element pop(QueueType* s) {
	float buffer[1024];
	if (is_empty_stack(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else {
		for (int i = 0; i < value + 1; i++) {
			buffer[i] = s->data2[(s->top)--];
		}
	}

	for (int i = value; i > 0; i--) {
		if (buffer[i] != 0) {
			fprintf(fp2, "%3.1fx^%d + ", buffer[i], i);
		}
	}
	fprintf(fp2, "%3.1f\n", buffer[0]);
}
// ��ũ�Լ�
element peek(QueueType* s) {
	if (is_empty_stack(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}

// ���Լ�
int main(void)
{
	QueueType a = { 5,{ 10, 0, 0, 0, 6, 3 } };
	QueueType b = { 4,{ 1, 0, 5, 0, 7 } };
	QueueType A = { 5,{ 9, 0, 0, 0, 6, 2 } };
	QueueType B = { 4,{ 1, 0, 5, 0, 7 } };
	QueueType c;
	QueueType C;

	fp1 = fopen("05-1.txt", "at+");
	fprintf(fp1, "[���׽� 1]\n");
	init_queue(&a);
	enqueue(&a);
	queue_print(&a);

	init_queue(&b);
	enqueue(&b);
	queue_print(&b);

	fprintf(fp1, "[���׽� 2]\n");
	init_queue(&A);
	enqueue(&A);
	queue_print(&A);

	init_queue(&B);
	enqueue(&B);
	queue_print(&B);

	fclose(fp1);


	c = poly_add1(a, b);
	init_stack(&c);
	push(&c);

	C = poly_add1(A, B);
	init_stack(&C);
	push(&C);

	fp2 = fopen("05-2.txt", "at+");
	fprintf(fp2, "[���׽� 1]\n");
	pop(&c);
	fprintf(fp2, "[���׽� 2]\n");
	pop(&C);

	fclose(fp2);

	system("notepad.exe 05-1.txt");
	system("notepad.exe 05-2.txt");

	return 0;
}