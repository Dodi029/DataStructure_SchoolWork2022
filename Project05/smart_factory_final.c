#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#define MAX 100 // 10�� �¼� ��ŭ ����/���� ���� �����غ� ��
#define MAX_QUEUE_SIZE 100

int black_cnt, red_cnt, blue_cnt;
int error_cnt, error_percent, total_cnt;
int red_error_cnt = 0, blue_error_cnt = 0, black_error_cnt = 0;
char filename[20];

typedef struct {            // ����ü�� ����
    int pen_id;
    char pen_color[5];
    int pen_cnt;
    char date;
} element;

typedef struct { // ť Ÿ��
    element data[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
    fprintf(stderr, "%s\n", message);   // ����â�� ���� �޽��� ���
    exit(1);            // �������� ���α׷� ����
}

// ���� ���� ���� �Լ�
void init_queue(QueueType* q)
{
    q->front = q->rear = 0;         // ����ť�̱� ������ �ʱⰪ = 0
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

// ����ť ��� �Լ�
void queue_print(QueueType* q) {            // �ҷ�ǰ�� ���� �����ϴ� ������ ����� �Լ�
    FILE* fp;           // ���� ������
    char err[20] = "error";         // ���� �Է¹��� ��¥�ڿ� error�� �ٿ��� �������ϸ� ��� �������� ǥ��
    char* p;
    p = strcat(err, filename);          // �Է¹��� ��¥ �ڿ� error�� ���̴� �ڵ�

    fp = fopen(p, "at+");           // at+���� ������ �ҷ��ͼ� ������ ������ ������ ���� �����ϰ�, ������ ������ ���� ���Ͽ� �̾ �ۼ�
    if (!is_empty(q)) {         // ť Ÿ���� ������� ���� ��� ���α׷��� ������
        int i = q->front;           // front ��ġ �̵�
        do {
            i = (i + 1) % (MAX_QUEUE_SIZE);         // i�� ���� i + 1 �� MAX(100)���� ���� ������ �̹Ƿ� i+1���� �� (ó�� �ѹ��� ����)
            fprintf(fp, "%d �� %s �� �����ȣ: %d\n", q->data[i].pen_cnt, q->data[i].pen_color, q->data[i].pen_id); // fprintf�� ���Ͽ� �������
            if (i == q->rear)           // i�� ���� rear ���ԵǸ� �� �þ ���� �����Ƿ�
                break;              // break�� �ݺ��� Ż��
        } while (i != q->front);            // i ���� front���� �ƴϸ� ��� �ݺ�
    }
    printf("\n");           // �������� ���� �� ����

    error_cnt = red_error_cnt + blue_error_cnt + black_error_cnt;           // �ҷ�ǰ �� ���� = ��������ҷ� + �Ķ�����ҷ� + ��������ҷ�
    total_cnt = black_cnt + red_cnt + blue_cnt;             // �� ���� = �������� �� + �Ķ����� �� + �������� ��

    double error_percent = (double)error_cnt / (double)total_cnt * MAX;         // �ҷ����氳�� / �� ���氳���� �ҷ��� ���

    fprintf(fp, "�ҷ��� �� %.1lf %%\n", error_percent);         // ����� �ҷ����� ������������� ���Ͽ� ���
    fprintf(fp, "���ϻ��꺼�� %d��=> ��%d��, ��%d��, ��%d�� \n", total_cnt, black_cnt, red_cnt, blue_cnt);

    fclose(fp);         // �ۼ��� �Ϸ�� ������ ����
}

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

void makefile() {           // �Է¹��� ��¥�� �̸����� �ϴ� ������ �����ϴ� �Լ�
    FILE* fp;                   // �Է¹��� ��¥�� �������� �ϴ� ����
    FILE* total = fopen("total_report.txt", "at+");         // �� ����ǰ�� �����ϴ� ����
    QueueType pen;
    QueueType error;
    init_queue(&pen);
    init_queue(&error);
    char* p;                // �����̸��� ������ ����
    srand(time(NULL));          // rand()�� �������� �ݺ��Ǵ� ���� �����ϱ� ���� �ۼ�

    p = filename;               // �����̸��� ������
    fp = fopen(p, "w");
    fprintf(total, "\n���� ��¥ : %s\n", filename);         // �� ����ǰ�� �����ϴ� ���Ͽ� �����̸�(=�Է¹��� ��¥)�� �Է�

    for (int i = 0; i < MAX; i++) {             // max��ŭ �ݺ��Ͽ� max ��ŭ ���� ����

        int rand1 = rand();         // ������ ���� �ڵ�

        if (rand1 % 10 == 0) {          // 10���� ���� �������� 0�� Ȯ�� = 10%
            red_cnt++;              // �� ���� ���� ���� ( ������ ������ŭ red_cnt ����)
            if (rand() % 20 == 0) {            // 0���� 20-1 ������ �� �� �������� �̾��� �� 0�� ��� (5%Ȯ��)�϶� ����
                red_error_cnt++;            // �ҷ� ���� ���� �� ����
                element err_red;            // ����ü�� ����
                err_red.pen_cnt = i;            // ���� ���� ��ȣ (�������) ����
                err_red.pen_id = rand1;                 // ���� ���� id ����
                strcpy(err_red.pen_color, "����");            // ���� �������� ����
                enqueue(&error, err_red);               // ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
                // �ҷ����� ǥ���ؼ� �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
                // �� ����ǰ�� �����ϴ� ���Ͽ� ���
            }
            else {          // �������� ��� = �ҷ��� �ƴ� ���
                element red;            // ����ü ���� ����
                red.pen_cnt = i;            // ���� ��ȣ ����
                red.pen_id = rand1;         // ���� ���� id ����
                strcpy(red.pen_color, "����");            // ���� ���� ����
                enqueue(&pen, red);             // ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
                // ����� ������ �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
                // ����� ������ �� ���귮 ���Ͽ� ���
            }
        }
        if (rand1 % 10 == 1) {              // 10���� ���� �������� 1�� ��� ( 10% Ȯ��)
            blue_cnt++;             // �� �Ķ� ���� �� ����
            if (rand() % 20 == 1) {             // 0���� 20-1������ �� �� �������� �̾��� �� 1�� ��� (5%Ȯ��)�� ����
                blue_error_cnt++;               // �ҷ� �Ķ� ���� �� ����
                element err_blue;           // ����ü�� ����
                err_blue.pen_cnt = i;           // ���� ��ȣ ����
                err_blue.pen_id = rand1;            // ���� ���� id ����
                strcpy(err_blue.pen_color, "�Ķ�");           // ���� ���� ����
                enqueue(&error, err_blue);              // �ҷ� �Ķ� ���� ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
                // �ҷ����� ǥ���ؼ� �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
                // �� ����ǰ�� �����ϴ� ���Ͽ� ���
            }
            else {              // �������� ��� = �ҷ��� �ƴ� ���
                element blue;       // ����ü �Ķ� ����
                blue.pen_cnt = i;           // ���� ��ȣ ����
                blue.pen_id = rand1;            // ���� ���� id ����
                strcpy(blue.pen_color, "�Ķ�");           // ���� ���� ����
                enqueue(&pen, blue);            // ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
                // �ҷ����� ǥ���ؼ� �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
                // �� ����ǰ�� �����ϴ� ���Ͽ� ���
            }
        }
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9)) {       // �� �̿��� ���(80%Ȯ��)
            black_cnt++;            // �� ������ ���� �� ����
            if (rand() % 20 == 0) {         // 0���� 20-1 ������ �� �� �������� �̾��� �� 0�� ��� (5%Ȯ��)�϶� ����
                black_error_cnt++;          // �ҷ� ���� ���� �� ����
                element err_black;          // ����ü�� ����
                err_black.pen_cnt = i;          // ���� ��ȣ ����
                err_black.pen_id = rand1;           // ���� ���� id ����
                strcpy(err_black.pen_color, "����");          // ���� ���� ����
                enqueue(&error, err_black);             // ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
                // �ҷ����� ǥ���ؼ� �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
                //  �� ����ǰ�� �����ϴ� ���Ͽ� ���
            }
            else {          // �������� ��� = �ҷ��� �ƴ� ���
                element black;          // ������ ����ü ����
                black.pen_cnt = i;          // ���� ��ȣ ����
                black.pen_id = rand1;           // ���� ���� id ����
                strcpy(black.pen_color, "����");          // ���� ���� ����
                enqueue(&pen, black);           // ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
                //  �ҷ����� ǥ���ؼ� �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
                // �� ����ǰ�� �����ϴ� ���Ͽ� ���
            }
        }

    }
    fclose(fp);
    fclose(total);

    queue_print(&error);
}
void append() {         // �Է¹��� ��¥�� �������� �ϴ� ������ ������ ���, �� ������ ���� �̾ �ۼ��ϴ� �Լ�
    FILE* fp;
    FILE* total = fopen("total_report.txt", "at+");         // ���ݱ��� ������ ������ �����ϴ� ������ ���� �̾ �ۼ���
    QueueType pen;
    QueueType error;
    init_queue(&pen);
    init_queue(&error);

    char buffer[1024];
    char* token;
    char* p;
    int i = 0;
    int value = 0;

    srand(time(NULL));          // ���� �����Լ��� time�� �־� ������ �ݺ��Ǵ� ���� ������
    p = filename;       // ���� �̸�(�Է��� ��¥)�� �̸����� �ϴ� ������ ����Ŵ

    fp = fopen(p, "at+");           // ���� �̸�(�Է��� ��¥)���� �� ������ at+���� ����
    fprintf(total, "\n���� ��¥ : %s\n", filename);         // �� ���귮�� �����ϴ� ���Ͽ� �Է��� ��¥�� �����Ͽ� ���� ����������� �˾ƺ� �� �ְ� ��

    while (!feof(fp)) {                 //report���Ͽ��� ������ ������ ���°���� �о�鿩 value�� ����
        i = 0;
        fgets(buffer, 1024, fp);            // fgets�� ����Ͽ� enter�� �Էµ� ������ ���� �о��
        token = strtok(buffer, " ");        // strtok(���ڿ� �ڸ���) �Լ��� " "�� ���ö����� = ������ �о���δ�
        while (token != NULL) {         // ������ �� ������ �б�
            if (i == 0) {
                value = atoi(token);            // atoi �Լ��� ����ȯ �Լ��� token(char��)�� value(int��)���� �ٲ���
            }
            i++;
            token = strtok(NULL, " ");
        }
    }
    for (i = value + 1; i < value + MAX + 1; i++) {  //value+1��°���� 100�� ����
        int rand1 = rand();
        if (rand1 % 10 == 0) {          // 10���� ������ �� �������� 0�� ��� = 10%�� ���
            red_cnt++;              // ���� ���� ����
            if (rand() % 20 == 0) {            // �� �� 0���� 20-1������ ���ڸ� ����� �� 0�� ���( = 5%Ȯ��)���� �ҷ�����
                red_error_cnt++;            // ���� �ҷ� ������ ���� ����
                element err_red;            // ����ü�� ����
                err_red.pen_cnt = i;            // ���� ��ȣ ����
                err_red.pen_id = rand1;             // ���� ���� id ����
                strcpy(err_red.pen_color, "����");            // ���������� ����
                enqueue(&error, err_red);           // error ����ü�� err_red����ü ����
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);      // ���� ��¥ ���Ͽ� �ҷ����� ǥ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);           // �� ���귮 ���Ͽ� �ҷ����� ǥ���Ͽ� ��� 
            }
            else {          // �� �̿��� ��� = ���� ������ ���
                element red;            // ���� ���� ����ü�� ����
                red.pen_cnt = i;            // ���� ��ȣ ����
                red.pen_id = rand1;         // ���� ���� id ����
                strcpy(red.pen_color, "����");            // ���������� ����
                enqueue(&pen, red);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", red.pen_cnt, red.pen_color, red.pen_id);        // ���� ��¥ ���Ͽ� ���� ����
                fprintf(total, "%d �� %s �� �����ȣ: %d\n", red.pen_cnt, red.pen_color, red.pen_id);         // �� ���귮 ���Ͽ� ���� ����
            }
        }
        if (rand1 % 10 == 1) {              // 10���� ���� �������� 1�ΰ�� = 10%Ȯ��
            blue_cnt++;         // �Ķ� ���� ���� ����
            if (rand() % 20 == 1) {     // 0���� 20-1 ������ ���� �� 1�� ��� = 5%Ȯ��
                blue_error_cnt++;           // �Ķ� �ҷ� ���� ���� ����
                element err_blue;           // �Ķ� �ҷ� ���� ����ü�� ����
                err_blue.pen_cnt = i;           // ���� ��ȣ ����
                err_blue.pen_id = rand1;            // ���� ���� id ����
                strcpy(err_blue.pen_color, "�Ķ�");           // �Ķ������� ����
                enqueue(&error, err_blue);          // error����ü�� �Ķ� �ҷ� ���� ����ü ����
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);       // ���� ��¥ ���Ͽ� �ҷ����� ǥ���Ͽ� ����
                fprintf(total, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);        // �� ���귮 ���Ͽ� �ҷ����� ǥ���Ͽ� ����
            }
            else {
                element blue;           // �Ķ� ���� ����ü�� ����
                blue.pen_cnt = i;           // ���� ��ȣ ����
                blue.pen_id = rand1;            // ���� ���� id ����
                strcpy(blue.pen_color, "�Ķ�");           // �Ķ������� ����
                enqueue(&pen, blue);            // pen ����ü�� �Ķ� ���� ����ü ����
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);     // ���� ��¥ ���Ͽ� ���� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);          // �� ���귮 ���Ͽ� ���� ���
            }
        }  
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9)) {       // 10���� ���� �������� 2���� ũ�ų� ���� 9���� �۰ų� ���� ��� = 80%Ȯ��
            black_cnt++;            // ���� ���� ���� ����
            if (rand() % 20 == 0) {         // 0���� 20-1���� �� �� 0�� ���� ��� = 5%Ȯ��
                black_error_cnt++;          // ���� �ҷ� ���� ���� ����
                element err_black;          // ���� �ҷ� ���� ����ü�� ����
                err_black.pen_cnt = i;          // ���� ���� ��ȣ ����
                err_black.pen_id = rand1;           // ���� ���� id ����
                strcpy(err_black.pen_color, "����");          // ���������� ����
                enqueue(&error, err_black);         // error����ü�� ���� �ҷ� ���� ����ü ����
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);         // ���� ��¥ ���Ͽ� �ҷ����� ǥ���Ͽ� ����
                fprintf(total, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);     // �� ���귮 ���Ͽ� �ҷ����� ǥ���Ͽ� ����
            }
            else {
                element black;          // ���� ���� ����ü�� ����
                black.pen_cnt = i;          // ���� ���� ��ȣ ����
                black.pen_id = rand1;           // ���� ���� ���� id ����
                strcpy(black.pen_color, "����");          // ���������� ����
                enqueue(&pen, black);           // pen ����ü�� ���� ���� ����ü ����
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", black.pen_cnt, black.pen_color, black.pen_id);      // ���� ��¥ ���Ͽ� ���� ����
                fprintf(total, "%d �� %s �� �����ȣ: %d\n", black.pen_cnt, black.pen_color, black.pen_id);       // �� ������ ���Ͽ� ���� ����
            }
        }
    }
    fclose(fp);         // ������ ���� ��¥ ���� �ݱ�
    fclose(total);          // ������ �� ���귮 ���� �ݱ�

    queue_print(&error);        // ���� ���� ���
}
int main() {
    FILE* fp;       // Ư�� ��¥�� ������ ���� ������ �����ϴ� ������ ������
    char err[20] = "error";         // �Է¹��� ��¥�� ������ ���� �� �ҷ�ǰ�� �����ϴ� ������ �̸��� ����� ���� ����
    char txt[] = ".txt";        // �Է¹��� ��¥�� �̸����� �ϴ� �ؽ�Ʈ ������ ����� ���� ����
    char openfile1[MAX] = "notepad.exe ";       // �ؽ�Ʈ ���Ϸ� ����
    char openfile2[MAX] = "notepad.exe ";       // �ؽ�Ʈ ���Ϸ� ����
    char* p1, p2;

    printf("���ϴ� ��¥ �Է�(��������)>>");        // ��¥�� �Է¹޴� �ڵ�
    scanf("%s", &filename);             // �Է� ���� ��¥�� filename������ ������

    p1 = strcat(filename, txt);         // �Է¹��� ��¥�� �������� �ϴ� ���� ����

    fp = fopen(p1, "r");            // ������ read ���� �ҷ���

    if (fp == NULL) {   // �Է¹��� ��¥�� �������� �ϴ� ������ �������� ������
                        // ���Ӱ� �Է¹��� ��¥�� �������� �ϴ� ������ ����
        makefile();     // ������ �����ϴ� makefile �Լ� ����
    }
    else {              // �Է¹��� ��¥�� �������� �ϴ� ������ �����Ѵٸ�
        fclose(fp);     // read ���� ���� ������ �ݰ�
        append();       // �Է¹��� ��¥�� �������� �ϴ� ������ �ҷ��ͼ� �̾ �ۼ�
    }
    system(strcat(openfile1, filename));   // ���� ����ǰ�� �����ϴ� ������ �ҷ���
    strcat(err, filename);       // �Է¹��� ��¥�� �������� �ϴ� �ҷ�ǰ�� �����ϴ� �����̸� ����
    system(strcat(openfile2, err));         // �ҷ�ǰ�� ���� �����ϴ� ������ �ҷ���
    system("notepad.exe total_report.txt");         // ���ݱ��� ������ ��� ������ �����ϴ� ������ �ҷ���

    return 0;
}