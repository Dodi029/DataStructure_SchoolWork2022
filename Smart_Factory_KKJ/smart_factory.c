#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100                 // 10�� �¼� ��ŭ ����/���� ���� �����غ� ��
#define MAX_QUEUE_SIZE 100

typedef struct {
    int pen_id;
    char pen_color[5];
} element;
typedef struct {                        // ť Ÿ��
    element data[MAX_QUEUE_SIZE];
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
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
/*
// ����ť ��� �Լ�
void queue_print(QueueType* q)
{
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % (MAX_QUEUE_SIZE);
            printf("%d | ", q->data[i]);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
}
*/

// ���� �Լ�
void enqueue(QueueType* q, element item)
{
    if (is_full(q))
        error("ť�� ��ȭ�����Դϴ�");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q)
{
    if (is_empty(q))
        error("ť�� ��������Դϴ�");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// ���� �Լ�
element peek(QueueType* q)
{
    if (is_empty(q))
        error("ť�� ��������Դϴ�");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt, red_error_cnt = 0, blue_error_cnt = 0, black_error_cnt = 0;

int main()
{
    QueueType pen;
    QueueType error;
    FILE* fp;
    fp = fopen("Report.txt", "at+"); // ���� �����͸� ������Ű�� 

    init_queue(&pen);
    init_queue(&error);
    srand(time(NULL));
    const int error_percent = MAX * 5 / MAX; // 5%�� �ҷ���

    struct tm* t;					// ��¥ ǥ��
    time_t base = time(NULL);
    t = localtime(&base);

    fprintf(fp, "%d�� %d�� %d�� \n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

    for (int i = 0; i < MAX; i++)
    {
        int rand1 = rand();

        fprintf(fp, "%03d�� ������� -> �����ȣ%d\n", i + 1, rand1); // 
        fprintf(stdout, "%03d�� ������� -> �����ȣ%d\n", i + 1, rand1);
        if (rand1 % 10 == 0)
        {
            red_cnt++;
            if (rand1 % 20 == 0)
            {
                error_cnt++;
                element err_red;
                err_red.pen_id = rand1;
                strcpy(err_red.pen_color, "����");
                enqueue(&error, err_red);
            }
            else
            {
                element red;
                red.pen_id = rand1;
                strcpy(red.pen_color, "����");
                enqueue(&pen, red);
            }
        }
        if (rand1 % 10 == 1)
        {
            blue_cnt++;
            if (rand1 % 20 == 0)
            {
                error_cnt++;
                element err_blue;
                err_blue.pen_id = rand1;
                strcpy(err_blue.pen_color, "�Ķ�");
                enqueue(&error, err_blue);
            }
            else
            {
                element blue;
                blue.pen_id = rand1;
                strcpy(blue.pen_color, "�Ķ�");
                enqueue(&pen, blue);
            }
        }
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
        {
            black_cnt++;
            if (rand1 % 20 == 0)
            {
                error_cnt++;
                element err_black;
                err_black.pen_id = rand1;
                strcpy(err_black.pen_color, "����");
                enqueue(&error, err_black);
            }
            else
            {
                element black;
                black.pen_id = rand1;
                strcpy(black.pen_color, "����");
                enqueue(&pen, black);
            }
        }

    }
    total_cnt = black_cnt + red_cnt + blue_cnt;

    fprintf(fp, "�ѻ��꺼�� %d=> ��%d, ��%d, ��%d, �ҷ�%d\n\n", total_cnt, black_cnt, red_cnt, blue_cnt, error_cnt);
    fprintf(stdout, "�ѻ��꺼�� %d=> ��%d, ��%d, ��%d, �ҷ�%d\n", total_cnt, black_cnt, red_cnt, blue_cnt, error_cnt);
    
    fclose(fp);

    FILE* pErr = fopen("Error_report.txt", "at+");

    fprintf(pErr, "%d�� %d�� %d�� \n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    fprintf(pErr, "�ҷ���%d%%\n", error_cnt);
    fprintf(stdout, "�ҷ���%d%%\n", error_cnt);

    int error_id;
    for (int i = 0; i < error_cnt; i++)
    {
        element err = dequeue(&error);
        if (strcmp(err.pen_color, "����"))
        {
            error_id = err.pen_id;
            fprintf(pErr, "����%d �ҷ����� ��ȣ -> %d\n", i + 1, error_id);
        }

        else if (strcmp(err.pen_color, "�Ķ�"))
        {
            error_id = err.pen_id;
            fprintf(pErr, "�Ķ�%d �ҷ����� ��ȣ -> %d\n", i + 1, error_id);
        }

        else if (strcmp(err.pen_color, "����"))
        {
            error_id = err.pen_id;
            fprintf(pErr, "����%d �ҷ����� ��ȣ -> %d\n", i + 1, error_id);
        }
    }
    fprintf(pErr, "\n");
    fclose(pErr);

    system("notepad.exe Report.txt");
    system("notepad.exe Error_report.txt");
    
    return 0;
}