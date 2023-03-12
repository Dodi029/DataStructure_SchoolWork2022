#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100 // 10�� �¼� ��ŭ ����/���� ���� �����غ� ��
#define DAY 5

const int error_percent = MAX * 5 / MAX; // 5%�� �ҷ���

typedef struct {
	int pen_num;        // ���� ���� ��ȣ
	int confirm;  // ���� �ҷ� Ȯ��  1 : ���� ,0 : ������
	char error_color[10];  // �ҷ��϶� ���� ��
	int pen_id;    // ���� ���� ��ȣ (������ ������)
}day;

typedef struct {
	int mons;       // ��
	int days;       // ����
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
	day  data[DAY][MAX];
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
void queue_print(QueueType* q, FILE* p, int k)
{
	printf("QUEUE(front=%d rear=%d) = \n", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX);
			//fprintf(stdout, "%d�� �������->�����ȣ % d\n", q->data[i].pen_num, q->data[i].pen_id);
			if(q->data[k][i].confirm == 0)
				fprintf(p, "%d�� �������->�����ȣ %d --->�ҷ�\n", q->data[k][i].pen_num, q->data[k][i].pen_id);
			else
				fprintf(p, "%d�� �������->�����ȣ %d\n", q->data[k][i].pen_num, q->data[k][i].pen_id);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	fprintf(stdout, "---------------------------\n\n");
	fprintf(p, "---------------------------\n\n");
}

// ���� �Լ�
void enqueue(QueueType* q, int id, int i, int bol, char str[], int k)
{
	if (is_full(q))
		fprintf(stdout, "ť�� ��ȭ�����Դϴ�");
	else
	{
		q->rear = (q->rear + 1) % MAX;
		q->data[k][q->rear].pen_id = id;
		q->data[k][q->rear].pen_num = i;
		q->data[k][q->rear].confirm = bol;
		strcpy(q->data[k][q->rear].error_color, str);
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
		//q->data[q->front];
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

void input_file(FILE* p, FILE*sump, QueueType* q, sum* sp, int k)
{
	//fprintf(stdout, "%d��%d�� ���� ���귮\n", total[k].mons, total[k].days);
	fprintf(p, "%d��%d�� ���� ���귮\n", sp[k].mons, sp[k].days);

	//fprintf(stdout, "\\n�ѻ��꺼�� %d=> ��%d, ��%d, ��%d \n\n", total[k].total_cnt, total[k].black_cnt, total[k].red_cnt, total[k].blue_cnt);          // 4. fpritf()�Լ��� '�����'�� '����'�� ���� ���
	fprintf(p, "\n�ѻ��꺼�� %d=> ��%d, ��%d, ��%d \n\n", sp[k].total_cnt, sp[k].black_cnt, sp[k].red_cnt, sp[k].blue_cnt);

	//fprintf(stdout, "%d��%d�� ���� �ҷ� ���귮\n", total[k].mons, total[k].days);
	fprintf(p, "%d��%d�� ���� �ҷ� ���귮\n", sp[k].mons, sp[k].days);

	//fprintf(stdout, "�ҷ���%d%%\n\n", error_percent);
	fprintf(p, "�ҷ���%d%%\n\n", error_percent);

	//fprintf(stdout, "�ҷ����� ���� %d=> ��%d, ��%d, ��%d\n\n", total[k].error_cnt, total[k].error_black_cnt, total[k].error_red_cnt, total[k].error_blue_cnt);
	fprintf(p, "�ҷ����� ���� %d=> ��%d, ��%d, ��%d\n\n", sp[k].error_cnt, sp[k].error_black_cnt, sp[k].error_red_cnt, sp[k].error_blue_cnt);

	//fprintf(stdout, "�ҷ� ���� ������ : \n");
	fprintf(p, "�ҷ� ���� ������ : \n");

		for (int i = 0; i < MAX; i++)
		{
			if (q->data[k][i].confirm == 0)
			{
				//fprintf(stdout, "�����ȣ : %d, �� : %7s, ������ȣ : %d\n", q.data[i].pen_num, q.data[i].error_color, q.data[i].pen_id);
				fprintf(p, "�����ȣ : %d, �� : %7s, ������ȣ : %d\n", q->data[k][i].pen_num, q->data[k][i].error_color, q->data[k][i].pen_id);
			}
		}
		fprintf(p, "----------------------------------\n\n");
}

int main()
{
	FILE* fp; // 1. ���� ������ ����
	FILE* sumfp;
	//FILE* errorfp;
	FILE* day1fp;
	FILE* day2fp;
	FILE* day3fp;
	FILE* day4fp;
	FILE* day5fp;


	struct tm* t;                                        //���� ��¥ ���ϱ�
	time_t base = time(NULL);                            //
	t = localtime(&base);                                //

	QueueType q;
	sum total[DAY] = {0,0,0,0,0,0,0,0,0,0 };
	int id;
	srand(time(NULL));

	fp = fopen("report.txt", "wt+");   // 2. �����͸� ������Ű��, +������� read&write ����� ��.
	sumfp = fopen("sumation.txt", "wt+");
	//errorfp = fopen("error.txt", "wt+");
	day1fp = fopen("day1", "at+");
	day2fp = fopen("day2", "at+");
	day3fp = fopen("day3", "at+");
	day4fp = fopen("day4", "at+");
	day5fp = fopen("day5", "at+");

	for (int k = 0; k < DAY; k++)
	{
		init_queue(&q);              // ť �ʱ�ȭ
		total[k].mons = t->tm_mon + 1;            //���� �������
		total[k].days = t->tm_mday + k;           //���� �Ϻ��� DAY����
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
					enqueue(&q, id, i, 0, "red", k);
					total[k].error_red_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "", k);

			}

			if (id % 10 == 1)
			{
				total[k].blue_cnt++;
				if (rand() % 20 == 0)         //�ҷ��� ���
				{
					enqueue(&q, id, i, 0, "blue", k);

					total[k].error_blue_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "blue", k);

			}

			if ((id % 10 >= 2) && (id % 10 <= 9))
			{
				total[k].black_cnt++;
				if (rand() % 20 == 0)         //�ҷ��� ���
				{
					enqueue(&q, id, i, 0, "black", k);
					total[k].error_black_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "black", k);
			}
		}
		queue_print(&q, fp, k);
		total[k].total_cnt = total[k].black_cnt + total[k].red_cnt + total[k].blue_cnt;
		total[k].error_cnt = total[k].error_black_cnt + total[k].error_red_cnt + total[k].error_blue_cnt;
		
	}

	input_file(day1fp, sumfp, &q, total, 0);
	input_file(day2fp, sumfp, &q, total, 1);
	input_file(day3fp, sumfp, &q, total, 2);
	input_file(day4fp, sumfp, &q, total, 3);
	input_file(day5fp, sumfp, &q, total, 4);


	fclose(fp);
	fclose(sumfp);
	fclose(day1fp);
	fclose(day2fp);
	fclose(day3fp);
	fclose(day4fp);
	fclose(day5fp);
	//fclose(errorfp);

	int month_s, day_s;
	fprintf(stdout, "���ϴ½ô� ��¥�� �Է��Ͻÿ�\n");
	fprintf(stdout, "�� : ");
	fscanf(stdin, "%d", &month_s);
	fprintf(stdout, "�� : ");
	fscanf(stdin, "%d", &day_s);
	
	char ch[100]="";
	for (int i = 0; i < DAY; i++)
	{
		if (total[i].mons == month_s && total[i].days == day_s)
		{
			if (i == 0) strcpy(ch, "notepad.exe day1");
			else if (i == 1) strcpy(ch, "notepad.exe day2");
			else if (i == 2) strcpy(ch, "notepad.exe day3");
			else if (i == 3) strcpy(ch, "notepad.exe day4");
			else if (i == 4) strcpy(ch, "notepad.exe day5");
		}
	}
	if (ch == "")
		fprintf(stdout, "��¥�� �߸��ԷµǾ����ϴ�.");
	else
		system(ch);

	//system("notepad.exe report.txt");  // �ڵ����� �޸����� ����
	//system("notepad.exe error.txt");  // �ڵ����� �޸����� ����
	//system("notepad.exe sumation.txt");  // �ڵ����� �޸����� ����


	return 0;
}