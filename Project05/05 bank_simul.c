#define _CRT_SECURE_NO_WARNINTGS
# include <stdio.h>
# include <stdlib.h>
#define MAX_MINUTE 6		// 수행할 시간 선언

// 프로그램 5.2에서 다음과 같은 부분을 복사한다. 
// ================ 원형큐 코드 시작 =================
typedef struct { // 요소 타입
	int id;		// 고객번호
	int arrival_time;
	int service_time;
} element;			// 교체!
// ================ 원형큐 코드 종료 =================
// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 5
typedef struct { // 큐 타입
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;		// 원형큐이므로 0으로 초기화
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형큐 출력 함수
//void queue_print(QueueType *q)
//{
//	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
//	if (!is_empty(q)) {
//			int i = q->front;
//			do {
//				i = (i + 1) % (MAX_QUEUE_SIZE);
//				printf("%d | ", q->data[i]);
//				if (i == q->rear)
//					break;
//			} while (i != q->front);
//		}
//	printf("\n");
//}

// 삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 삭제 함수
element peek(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== 원형큐 코드 끝 ======

int main(void) 
{
	int minutes = MAX_MINUTE;
	int total_wait = 0;
	int total_customers = 0;
	int service_time = 0;
	int service_customer;
	QueueType queue;
	init_queue(&queue);

	srand(time(NULL));
	for (int clock = 0; clock < minutes; clock++) {
		printf("현재시각=%d\n", clock);
		if ((rand()%10) < 3) {			// 30%확률로 손님이 들어옴
			element customer;			// customer 구조체 선언
			customer.id = total_customers++;		// 고객의 번호 = 총 고객의 수로 몇 번째 고객인지 확인
			customer.arrival_time = clock;			// 도착 시간 = clock(반복 횟수)
			customer.service_time = rand() % 3+1;		// 업무처리시간 (0~3까지 숫자 중 하나가 나옴)
			enqueue(&queue, customer);			// 고객정보를 enqueue함수로 선형큐에 저장
			printf("고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n",			// 몇 번째 고객이 언제 들어왔는지
				customer.id, customer.arrival_time, customer.service_time);		// 업무 처리 시간은 얼마나 되는지 출력
		}
		if (service_time > 0) {			// 업무 처리 시간이 남아 있을 때 = 아직 업무 중일 때
			printf("고객 %d 업무처리중입니다. \n", service_customer);			// 아직 업무 중임을 출력
			service_time--;			// 반복문(시간)이 지날 때마다 잔여 업무 처리 시간 감소
		}
		else {			// 그 이외의 경우	 = 고객이 안들어오고, 업무 중인 고객이 없을 경우
			if (!is_empty(&queue)) {		// 원형큐가 비어있지 않다면
				element customer = dequeue(&queue);			// 선형큐에 저장된 고객 정보를 가져옴
				service_customer = customer.id;			// 업무 고객에 가져온 고객의 번호를 저장
				service_time = customer.service_time;			// 업무 시간에 고객의 업무 처리 시간 저장
				printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다.\n",	// 몇 번 고객이 언제 업무를 시작하는지
					customer.id, clock, clock - customer.arrival_time);			// 지금까지 얼마나 기다렸는지 출력
				total_wait += clock - customer.arrival_time;			// 총 기다린 시간 = 반복횟수(시간) - 고객이 도착한 시간
			}
		}
	}
	printf("전체 대기 시간=%d분 \n", total_wait);		// 총 기다린 시간 출력
	return 0;
}