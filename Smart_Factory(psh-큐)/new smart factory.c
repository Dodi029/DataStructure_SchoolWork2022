#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100                     // 10�� �¼� ��ŭ ����/���� ���� �����غ� ��
#define MAX_QUEUE_SIZE 100

int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt, red_error_cnt = 0, blue_error_cnt = 0, black_error_cnt = 0;

typedef struct {
    int pen_id;
    char pen_color[20];
} element;

typedef struct { // ť Ÿ��
    element data[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;

// ���� �Լ�
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ����ť ��� �Լ�
void queue_print(QueueType* q) {
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

// ���� �Լ�
void enqueue(QueueType* q, element item) {
    if (is_full(q))
        error("ť�� ��ȭ�����Դϴ�");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q) {
    if (is_empty(q))
        error("ť�� ��������Դϴ�");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// ���� �Լ�
element peek(QueueType* q) {
    if (is_empty(q))
        error("ť�� ��������Դϴ�");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void makefile() {
    FILE* fp;
    FILE* pErr;
    QueueType pen;
    QueueType error;
    init_queue(&pen);
    init_queue(&error);

    int idx = 0;

    srand(time(NULL));

    struct tm* t;					// ��¥ ǥ��
    time_t base = time(NULL);
    t = localtime(&base);

    fp = fopen("report.txt", "w");          //report������ �����Ƿ� ���� ���� ����

    fprintf(fp, "%d�� %d�� %d��\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

    pErr = fopen("error.txt", "at");

    fprintf(pErr, "%d�� %d�� %d��\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

    for (int i = 0; i < MAX; i++) {

        int rand1 = rand();

        if (rand1 % 10 == 0) {
            red_cnt++;
            if (rand() % 20 == 0) {
                error_cnt++;
                element err_red;
                err_red.pen_id = rand1;
                strcpy(err_red.pen_color, "����");
                enqueue(&error, err_red);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_red.pen_color, err_red.pen_id);
                fprintf(pErr, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_red.pen_color, err_red.pen_id);
            }
            else {
                element red;
                red.pen_id = rand1;
                strcpy(red.pen_color, "����");
                enqueue(&pen, red);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", i, red.pen_color, red.pen_id);
            }
        }
        if (rand1 % 10 == 1) {
            blue_cnt++;
            if (rand() % 20 == 0) {
                error_cnt++;
                element err_blue;
                err_blue.pen_id = rand1;
                strcpy(err_blue.pen_color, "�Ķ�");
                enqueue(&error, err_blue);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_blue.pen_color, err_blue.pen_id);
                fprintf(pErr, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_blue.pen_color, err_blue.pen_id);
            }
            else {
                element blue;
                blue.pen_id = rand1;
                strcpy(blue.pen_color, "�Ķ�");
                enqueue(&pen, blue);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", i, blue.pen_color, blue.pen_id);
            }
        }
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9)) {
            black_cnt++;
            if (rand() % 20 == 0) { 
                error_cnt++;
                element err_black;
                err_black.pen_id = rand1;
                strcpy(err_black.pen_color, "����");
                enqueue(&error, err_black);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_black.pen_color, err_black.pen_id);
                fprintf(pErr, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_black.pen_color, err_black.pen_id);
            }
            else {
                element black;
                black.pen_id = rand1;
                strcpy(black.pen_color, "����");
                enqueue(&pen, black);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", i, black.pen_color, black.pen_id);
            }
        } 
    }
    fclose(fp);
   
    const int error_percent = MAX * 5 / MAX;
    fprintf(pErr, "�ҷ��� �� %d%%\n", error_percent);
    total_cnt = black_cnt + red_cnt + blue_cnt;
    fprintf(pErr, "���ϻ��꺼�� %d��=> ��%d��, ��%d��, ��%d�� \n", total_cnt, black_cnt, red_cnt, blue_cnt);
    fclose(pErr);
}
void append() {
    FILE* fp;
    FILE* pErr;
    QueueType pen;
    QueueType error;
    init_queue(&pen);
    init_queue(&error);

    char buffer[1024];
    char* token;
    int idx = 0, i=0;
    int value = 0;

    srand(time(NULL));

    struct tm* t;					// ��¥ ǥ��
    time_t base = time(NULL);
    t = localtime(&base);

    fp = fopen("report.txt", "at+");
    pErr = fopen("error.txt", "at");

    while (!feof(fp)) {                 //report���Ͽ��� ������ ������ ���°���� �о��� value�� ����
        i = 0;
        fgets(buffer, 1024, fp);
        token = strtok(buffer, " ");
        while (token != NULL) {
            if (i == 0) {
                value = atoi(token);
            }
            i++;
            token = strtok(NULL, " ");
        }
        idx++;
    }

    for (int i = value + 1; i < value + 101; i++) {  //value+1��°���� 100�� ����
        int rand1 = rand();

        if (rand1 % 10 == 0) {
            red_cnt++;
            if (rand() % 20 == 0) {
                error_cnt++;
                element err_red;
                err_red.pen_id = rand1;
                strcpy(err_red.pen_color, "����");
                enqueue(&error, err_red);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_red.pen_color, err_red.pen_id);
                fprintf(pErr, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_red.pen_color, err_red.pen_id);
            }
            else {
                element red;
                red.pen_id = rand1;
                strcpy(red.pen_color, "����");
                enqueue(&pen, red);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", i, red.pen_color, red.pen_id);
            }
        }
        if (rand1 % 10 == 1) {
            blue_cnt++;
            if (rand() % 20 == 0) {
                error_cnt++;
                element err_blue;
                err_blue.pen_id = rand1;
                strcpy(err_blue.pen_color, "�Ķ�");
                enqueue(&error, err_blue);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_blue.pen_color, err_blue.pen_id);
                fprintf(pErr, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_blue.pen_color, err_blue.pen_id);
            }
            else {
                element blue;
                blue.pen_id = rand1;
                strcpy(blue.pen_color, "�Ķ�");
                enqueue(&pen, blue);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", i, blue.pen_color, blue.pen_id);
            }
        }
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9)) {
            black_cnt++;
            if (rand() % 20 == 0) {
                error_cnt++;
                element err_black;
                err_black.pen_id = rand1;
                strcpy(err_black.pen_color, "����");
                enqueue(&error, err_black);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_black.pen_color, err_black.pen_id);
                fprintf(pErr, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", i, err_black.pen_color, err_black.pen_id);
            }
            else {
                element black;
                black.pen_id = rand1;
                strcpy(black.pen_color, "����");
                enqueue(&pen, black);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", i, black.pen_color, black.pen_id);
            }
        }
    }
    fclose(fp);

    const int error_percent = MAX * 5 / MAX;
    fprintf(pErr, "�ҷ��� �� %d%%\n", error_percent);
    total_cnt = black_cnt + red_cnt + blue_cnt;
    fprintf(pErr, "���ϻ��꺼�� %d��=> ��%d��, ��%d��, ��%d�� \n", total_cnt, black_cnt, red_cnt, blue_cnt);
    fclose(pErr);
        
}
int main(){
    FILE* fp;
    fp = fopen("report.txt", "r");

    if (fp == NULL) {   //report������ ���ٸ� makefile�Լ� ȣ��
        makefile();
    }
    else {              //report������ �ִٸ� append�Լ� ȣ��
        fclose(fp);
        append();
    }

    system("notepad.exe report.txt");   //����ǰ ��ü�� �����ϴ� ����
    system("notepad.exe error.txt");    //�ҷ�ǰ�� ���� �����ϴ� ����

    return 0;
}
