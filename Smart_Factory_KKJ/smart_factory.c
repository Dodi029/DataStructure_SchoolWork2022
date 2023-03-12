#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100                 // 10의 승수 만큼 감소/증가 시켜 실험해볼 것
#define MAX_QUEUE_SIZE 100

typedef struct {
    int pen_id;
    char pen_color[5];
} element;
typedef struct {                        // 큐 타입
    element data[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;

// 오류 함수
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueType* q)
{
    q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
    return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
/*
// 원형큐 출력 함수
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

// 삽입 함수
void enqueue(QueueType* q, element item)
{
    if (is_full(q))
        error("큐가 포화상태입니다");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q)
{
    if (is_empty(q))
        error("큐가 공백상태입니다");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 삭제 함수
element peek(QueueType* q)
{
    if (is_empty(q))
        error("큐가 공백상태입니다");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt, red_error_cnt = 0, blue_error_cnt = 0, black_error_cnt = 0;

int main()
{
    QueueType pen;
    QueueType error;
    FILE* fp;
    fp = fopen("Report.txt", "at+"); // 기존 데이터를 누적시키고 

    init_queue(&pen);
    init_queue(&error);
    srand(time(NULL));
    const int error_percent = MAX * 5 / MAX; // 5%의 불량률

    struct tm* t;					// 날짜 표시
    time_t base = time(NULL);
    t = localtime(&base);

    fprintf(fp, "%d년 %d월 %d일 \n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

    for (int i = 0; i < MAX; i++)
    {
        int rand1 = rand();

        fprintf(fp, "%03d개 볼펜생산 -> 볼펜번호%d\n", i + 1, rand1); // 
        fprintf(stdout, "%03d개 볼펜생산 -> 볼펜번호%d\n", i + 1, rand1);
        if (rand1 % 10 == 0)
        {
            red_cnt++;
            if (rand1 % 20 == 0)
            {
                error_cnt++;
                element err_red;
                err_red.pen_id = rand1;
                strcpy(err_red.pen_color, "빨강");
                enqueue(&error, err_red);
            }
            else
            {
                element red;
                red.pen_id = rand1;
                strcpy(red.pen_color, "빨강");
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
                strcpy(err_blue.pen_color, "파랑");
                enqueue(&error, err_blue);
            }
            else
            {
                element blue;
                blue.pen_id = rand1;
                strcpy(blue.pen_color, "파랑");
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
                strcpy(err_black.pen_color, "검정");
                enqueue(&error, err_black);
            }
            else
            {
                element black;
                black.pen_id = rand1;
                strcpy(black.pen_color, "검정");
                enqueue(&pen, black);
            }
        }

    }
    total_cnt = black_cnt + red_cnt + blue_cnt;

    fprintf(fp, "총생산볼펜 %d=> 검%d, 빨%d, 파%d, 불량%d\n\n", total_cnt, black_cnt, red_cnt, blue_cnt, error_cnt);
    fprintf(stdout, "총생산볼펜 %d=> 검%d, 빨%d, 파%d, 불량%d\n", total_cnt, black_cnt, red_cnt, blue_cnt, error_cnt);
    
    fclose(fp);

    FILE* pErr = fopen("Error_report.txt", "at+");

    fprintf(pErr, "%d년 %d월 %d일 \n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    fprintf(pErr, "불량률%d%%\n", error_cnt);
    fprintf(stdout, "불량률%d%%\n", error_cnt);

    int error_id;
    for (int i = 0; i < error_cnt; i++)
    {
        element err = dequeue(&error);
        if (strcmp(err.pen_color, "빨강"))
        {
            error_id = err.pen_id;
            fprintf(pErr, "빨강%d 불량볼펜 번호 -> %d\n", i + 1, error_id);
        }

        else if (strcmp(err.pen_color, "파랑"))
        {
            error_id = err.pen_id;
            fprintf(pErr, "파랑%d 불량볼펜 번호 -> %d\n", i + 1, error_id);
        }

        else if (strcmp(err.pen_color, "검정"))
        {
            error_id = err.pen_id;
            fprintf(pErr, "검정%d 불량볼펜 번호 -> %d\n", i + 1, error_id);
        }
    }
    fprintf(pErr, "\n");
    fclose(pErr);

    system("notepad.exe Report.txt");
    system("notepad.exe Error_report.txt");
    
    return 0;
}