#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100 // 10�� �¼� ��ŭ ����/���� ���� �����غ� ��
#define DAY 5

typedef struct {
	int pen_num;        // ���� ���� ��ȣ
	int confirm;  // ���� �ҷ� Ȯ��  1 : ���� ,0 : ������
	char error_color[10];  // �ҷ��϶� ���� ��
	int pen_id;    // ���� ���� ��ȣ (������ ������)
}day;

typedef struct {
	int days;       // ��¥
	int total_cnt;  // �ѻ��갳��
	int black_cnt;  // ������ ���� ����
	int red_cnt;    // ������ ���� ����
	int blue_cnt;   // �Ķ��� ���� ����
	int error_cnt;  // �ҷ� ���� ����
	int error_black_cnt;  // ������ �ҷ� ���� ����
	int error_red_cnt;    // ������ �ҷ� ���� ����
	int error_blue_cnt;   // �Ķ��� �ҷ� ���� ����
}sum;

typedef struct { // ť Ÿ��
	day  data[MAX];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX == q->front);
}

// ����ť ��� �Լ�
void queue_print(QueueType* q, FILE* p)
{
	printf("QUEUE(front=%d rear=%d) = \n", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX);
			fprintf(stdout, "%d�� �������->�����ȣ % d\n", q->data[i].pen_num, q->data[i].pen_id);
			fprintf(p, "%d�� �������->�����ȣ % d\n", q->data[i].pen_num, q->data[i].pen_id);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	fprintf(stdout, "---------------------------\n\n");
	fprintf(p, "---------------------------\n\n");
}

// ���� �Լ�
void enqueue(QueueType* q, int id, int i, int bol, char str[])
{
	if (is_full(q))
		fprintf(stdout, "ť�� ��ȭ�����Դϴ�");
	else
	{
		q->rear = (q->rear + 1) % MAX;
		q->data[q->rear].pen_id = id;
		q->data[q->rear].pen_num = i;
		q->data[q->rear].confirm = bol;
		strcpy(q->data[q->rear].error_color, str);
	}
}

// ���� �Լ�
void dequeue(QueueType* q)
{
	if (is_empty(q)) {}
	//error("ť�� ��������Դϴ�");
	else
	{
		q->front = (q->front + 1) % MAX;
		q->data[q->front];
	}
}

//// ���� �Լ�
//element peek(QueueType* q)
//{
//	if (is_empty(q))
//		error("ť�� ��������Դϴ�");
//	return q->data[(q->front + 1) % MAX];
//}
//

int main()
{
	FILE* fp; // 1. ���� ������ ����
	FILE* sumfp;
	FILE* errorfp;

	QueueType q;
	sum total[DAY] = { 0,0,0,0,0,0,0,0,0 };
	int id;
	srand(time(NULL));
	const int error_percent = 5; // 5%�� �ҷ���


	fp = fopen("report.txt", "wt+");   // 2. �����͸� ������Ű��, +������� read&write ����� ��.
	sumfp = fopen("sumation.txt", "wt+");
	errorfp = fopen("error.txt", "wt+");

	for (int k = 0; k < DAY; k++)
	{
		init_queue(&q);              // ť �ʱ�ȭ
		for (int i = 1; i <= MAX; i++)
		{
			id = rand();

			//fprintf(stdout, "%03d�� ������� -> �����ȣ%d\n\n", i, id);                // 3. fpritf()�Լ��� '�����'�� '����'�� ���� ���
			//fprintf(fp,     "%03d�� ������� -> �����ȣ%d\n\n", i, id);
			if (id % 10 == 0)
			{
				total[k].red_cnt++;
				if (rand() % 20 == 0)         //�ҷ��� ���
				{
					enqueue(&q, id, i, 0, "red");
					total[k].error_red_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "");

			}

			if (id % 10 == 1)
			{
				total[k].blue_cnt++;
				if (rand() % 20 == 0)         //�ҷ��� ���
				{
					enqueue(&q, id, i, 0, "blud");

					total[k].error_blue_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "blud");

			}

			if ((id % 10 >= 2) && (id % 10 <= 9))
			{
				total[k].black_cnt++;
				if (rand() % 20 == 0)         //�ҷ��� ���
				{
					enqueue(&q, id, i, 0, "black");
					total[k].error_black_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "black");
			}
		}
		queue_print(&q, fp);
		total[k].total_cnt = total[k].black_cnt + total[k].red_cnt + total[k].blue_cnt;
		total[k].error_cnt = total[k].error_black_cnt + total[k].error_red_cnt + total[k].error_blue_cnt;
		fprintf(stdout,"%d�� ���� ���귮\n", total[k].days);
		fprintf(sumfp, "%d�� ���� ���귮\n", total[k].days);

		fprintf(stdout, "\\n�ѻ��꺼�� %d=> ��%d, ��%d, ��%d \n\n", total[k].total_cnt, total[k].black_cnt, total[k].red_cnt, total[k].blue_cnt);          // 4. fpritf()�Լ��� '�����'�� '����'�� ���� ���
		fprintf(sumfp, "\n�ѻ��꺼�� %d=> ��%d, ��%d, ��%d \n\n", total[k].total_cnt, total[k].black_cnt, total[k].red_cnt, total[k].blue_cnt);

		fprintf(stdout, "%d�� ���� �ҷ� ���귮\n", total[k].days);
		fprintf(errorfp, "%d�� ���� �ҷ� ���귮\n", total[k].days);

		fprintf(stdout, "�ҷ���%d%%\n\n", error_percent);
		fprintf(errorfp, "�ҷ���%d%%\n\n", error_percent);

		fprintf(stdout, "�ҷ����� ���� %d=> ��%d, ��%d, ��%d\n\n", total[k].error_cnt, total[k].error_black_cnt, total[k].error_red_cnt, total[k].error_blue_cnt);
		fprintf(errorfp, "�ҷ����� ���� %d=> ��%d, ��%d, ��%d\n\n", total[k].error_cnt, total[k].error_black_cnt, total[k].error_red_cnt, total[k].error_blue_cnt);

		fprintf(stdout, "�ҷ� ���� ������ : \n");
		fprintf(errorfp, "�ҷ� ���� ������ : \n");

		for (int i = 0; i < MAX; i++)
		{
			if (q.data[i].confirm == 0)
			{
				fprintf(stdout, "�����ȣ : %d, �� : %7s, ������ȣ : %d\n", q.data[i].pen_num, q.data[i].error_color, q.data[i].pen_id);
				fprintf(errorfp, "�����ȣ : %d, �� : %7s, ������ȣ : %d\n", q.data[i].pen_num, q.data[i].error_color, q.data[i].pen_id);
			}
		}
		fprintf(errorfp, "----------------------------------\n\n");
	}




	fclose(fp);
	fclose(sumfp);
	fclose(errorfp);


	system("notepad.exe report.txt");  // �ڵ����� �޸����� ����


	return 0;
}