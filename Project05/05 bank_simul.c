#define _CRT_SECURE_NO_WARNINTGS
# include <stdio.h>
# include <stdlib.h>
#define MAX_MINUTE 6		// ������ �ð� ����

// ���α׷� 5.2���� ������ ���� �κ��� �����Ѵ�. 
// ================ ����ť �ڵ� ���� =================
typedef struct { // ��� Ÿ��
	int id;		// ����ȣ
	int arrival_time;
	int service_time;
} element;			// ��ü!
// ================ ����ť �ڵ� ���� =================
// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE 5
typedef struct { // ť Ÿ��
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;		// ����ť�̹Ƿ� 0���� �ʱ�ȭ
}

// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ����ť ��� �Լ�
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

// ���� �Լ�
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// ���� �Լ�
element peek(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== ����ť �ڵ� �� ======

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
		printf("����ð�=%d\n", clock);
		if ((rand()%10) < 3) {			// 30%Ȯ���� �մ��� ����
			element customer;			// customer ����ü ����
			customer.id = total_customers++;		// ���� ��ȣ = �� ���� ���� �� ��° ������ Ȯ��
			customer.arrival_time = clock;			// ���� �ð� = clock(�ݺ� Ƚ��)
			customer.service_time = rand() % 3+1;		// ����ó���ð� (0~3���� ���� �� �ϳ��� ����)
			enqueue(&queue, customer);			// �������� enqueue�Լ��� ����ť�� ����
			printf("�� %d�� %d�п� ���ɴϴ�. ����ó���ð�= %d��\n",			// �� ��° ���� ���� ���Դ���
				customer.id, customer.arrival_time, customer.service_time);		// ���� ó�� �ð��� �󸶳� �Ǵ��� ���
		}
		if (service_time > 0) {			// ���� ó�� �ð��� ���� ���� �� = ���� ���� ���� ��
			printf("�� %d ����ó�����Դϴ�. \n", service_customer);			// ���� ���� ������ ���
			service_time--;			// �ݺ���(�ð�)�� ���� ������ �ܿ� ���� ó�� �ð� ����
		}
		else {			// �� �̿��� ���	 = ���� �ȵ�����, ���� ���� ���� ���� ���
			if (!is_empty(&queue)) {		// ����ť�� ������� �ʴٸ�
				element customer = dequeue(&queue);			// ����ť�� ����� �� ������ ������
				service_customer = customer.id;			// ���� ���� ������ ���� ��ȣ�� ����
				service_time = customer.service_time;			// ���� �ð��� ���� ���� ó�� �ð� ����
				printf("�� %d�� %d�п� ������ �����մϴ�. ���ð��� %d���̾����ϴ�.\n",	// �� �� ���� ���� ������ �����ϴ���
					customer.id, clock, clock - customer.arrival_time);			// ���ݱ��� �󸶳� ��ٷȴ��� ���
				total_wait += clock - customer.arrival_time;			// �� ��ٸ� �ð� = �ݺ�Ƚ��(�ð�) - ���� ������ �ð�
			}
		}
	}
	printf("��ü ��� �ð�=%d�� \n", total_wait);		// �� ��ٸ� �ð� ���
	return 0;
}