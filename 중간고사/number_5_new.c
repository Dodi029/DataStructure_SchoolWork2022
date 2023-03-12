#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 15

int avail;
int stop;
typedef struct {
	float coef;
	int expon;
} polynomial;

typedef struct { // 큐 타입
	polynomial  data[MAX_TERMS];
	int  front, rear;
} QueueType;

typedef struct {
	polynomial data[MAX_TERMS];
	int top;
} StackType;

void enqueue(QueueType* q, float coef1, int expon1);            // 삽입 함수 선언
void push(StackType* s, QueueType* q, int i);                   // 삽입 함수 언언

// 두개의 정수를 비교
char compare(int a, int b)
{
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

void poly_add2(QueueType* q, int As, int Ae, int Bs, int Be, int* Cs,
	int* Ce)
{
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be)
		switch (compare(q->data[As].expon, q->data[Bs].expon)) {
		case '>': 	// A의 차수 > B의 차수
			enqueue(q, q->data[As].coef, q->data[As].expon);
			avail++;
			(As)++;			break;
		case '=': 	// A의 차수 == B의 차수
			tempcoef = q->data[As].coef + q->data[Bs].coef;
			if (tempcoef)
				enqueue(q, tempcoef, q->data[As].expon);
			avail++;
			(As)++; (Bs)++;		break;
		case '<': 	// A의 차수 < B의 차수
			enqueue(q, q->data[Bs].coef, q->data[Bs].expon);
			avail++;
			(Bs)++;			break;
		}
	// A의 나머지 항들을 이동함
	//for (; As <= Ae; As++)
	//	enqueue(&q, q->data[*As].coef, q->data[*As].expon);
	// B의 나머지 항들을 이동함
	//for (; Bs <= Be; Bs++)
	//	enqueue(&q, q->data[*Bs].coef, q->data[*Bs].expon);
	*Ce = avail - 1;
}
void print_poly(FILE* fp, QueueType* q, int s, int e)
{
	for (int i = s; i < e; i++)
		fprintf(fp, "%3.1fx^%d + ", q->data[i].coef, q->data[i].expon);
	fprintf(fp, "%3.1fx^%d\n", q->data[e].coef, q->data[e].expon);
}
//
void init_pos(int* As, int* Ae, int* Bs, int* Be)
{
	*As = 0; *Ae = 2; *Bs = 3; *Be = 5;
	avail = *Be + 1;
}



// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty_stack(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full_stack(StackType* s)
{
	return (s->top == (MAX_TERMS - 1));
}
// 삽입함수
void push(StackType* s, QueueType* q, int i)
{
	if (is_full_stack(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else {
		(s->top)++;
		s->data[s->top].coef = q->data[i].coef;
		s->data[s->top].expon = q->data[i].expon;
	}


}
// 삭제함수
void pop(FILE* fp, StackType* s)
{
	if (is_empty_stack(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else {
		if (s->top == stop || s->top == 0)
			fprintf(fp, "%3.1fx^%d\n", s->data[s->top].coef, s->data[s->top].expon);
		else
			fprintf(fp, "%3.1fx^%d + ", s->data[s->top].coef, s->data[s->top].expon);

		(s->top)--;
	}
}

// ===== 스택 코드의 끝 ===== 




// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q)
{
	q->rear = -1;
	q->front = -1;
}

// 공백 상태 검출 함수
int is_full(QueueType* q)
{
	return (q->rear == MAX_TERMS - 1);
}
// 포화 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}



// 원형큐 출력 함수
//void queue_print(QueueType* q)
//{
//	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
//	if (!is_empty(q)) {
//		int i = q->front;
//		do {
//			i = (i + 1) % (MAX_TERMS);
//			printf("%d | ", q->data[i]);
//			if (i == q->rear)
//				break;
//		} while (i != q->front);
//	}
//	printf("\n");
//}

// 삽입 함수
void enqueue(QueueType* q, float coef1, int expon1)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_TERMS;
	q->data[q->rear].coef = coef1;
	q->data[q->rear].expon = expon1;
}

// 삭제 함수
void dequeue(FILE* fp, QueueType* q, int pos)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_TERMS;
	if (q->front == pos)
		fprintf(fp, "%3.1fx^%d\n", q->data[q->front].coef, q->data[q->front].expon);
	else
		fprintf(fp, "%3.1fx^%d + ", q->data[q->front].coef, q->data[q->front].expon);

}



int main(void)
{
	FILE* fp;
	FILE* sum_fp;
	fp = fopen("05-1.txt", "at+");
	sum_fp = fopen("05-2.txt", "at+");

	int As, Ae, Bs, Be, Cs, Ce;
	QueueType q;
	StackType s;


	init_stack(&s);
	init_pos(&As, &Ae, &Bs, &Be);
	init_queue(&q);
	enqueue(&q, 10, 5);
	enqueue(&q, 6, 1);
	enqueue(&q, 3, 0);
	enqueue(&q, 1, 4);
	enqueue(&q, 5, 2);
	enqueue(&q, 7, 0);
	poly_add2(&q, As, Ae, Bs, Be, &Cs, &Ce);
	dequeue(fp, &q, Ae);
	dequeue(fp, &q, Ae);
	dequeue(fp, &q, Ae);
	dequeue(fp, &q, Be);
	dequeue(fp, &q, Be);
	dequeue(fp, &q, Be);
	fprintf(fp, "---------------------------------------------------------------------------- - \n");
	//print_poly(sum_fp, &q, Cs, Ce);

	for (int i = Ce; i >= Cs; i--)
	{
		push(&s, &q, i);
	}
	stop = s.top + 1;

	init_pos(&As, &Ae, &Bs, &Be);
	init_queue(&q);
	enqueue(&q, 9, 5);
	enqueue(&q, 6, 1);
	enqueue(&q, 2, 0);
	enqueue(&q, 1, 4);
	enqueue(&q, 5, 2);
	enqueue(&q, 7, 0);
	poly_add2(&q, As, Ae, Bs, Be, &Cs, &Ce);
	dequeue(fp, &q, Ae);
	dequeue(fp, &q, Ae);
	dequeue(fp, &q, Ae);
	dequeue(fp, &q, Be);
	dequeue(fp, &q, Be);
	dequeue(fp, &q, Be);

	for (int i = Ce; i >= Cs; i--)
	{
		push(&s, &q, i);
	}
	pop(sum_fp, &s);
	pop(sum_fp, &s);
	pop(sum_fp, &s);
	pop(sum_fp, &s);
	pop(sum_fp, &s);
	pop(sum_fp, &s);
	pop(sum_fp, &s);
	pop(sum_fp, &s);
	pop(sum_fp, &s);
	pop(sum_fp, &s);


	/*print_poly(sum_fp, &q, Cs, Ce);*/


	fclose(fp);
	fclose(sum_fp);
	system("notepad.exe 05-1.txt");
	system("notepad.exe 05-2.txt");

	return 0;
}