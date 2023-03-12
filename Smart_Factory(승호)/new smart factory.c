#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100 // 10의 승수 만큼 감소/증가 시켜 실험해볼 것
#define MAX_QUEUE_SIZE 100

int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt, red_error_cnt = 0, blue_error_cnt = 0, black_error_cnt = 0;


typedef struct {
    int pen_id;
    char pen_color[5];
    int pen_cnt;
} element;

typedef struct { // 큐 타입
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

// 원형큐 출력 함수
void queue_print(QueueType* q)
{
    FILE* fp;
    fp=fopen("error.txt","at+");
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % (MAX_QUEUE_SIZE);
            fprintf(fp,"%s %d번 불량,볼펜 번호 -> %d\n", q->data[i].pen_color,q->data[i].pen_cnt, q->data[i].pen_id);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
    fclose(fp);
}

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

void makefile() {
    FILE* fp;
    QueueType pen;
    QueueType error;
    init_queue(&pen);
    init_queue(&error);

    int idx = 0;

    srand(time(NULL));

    fp = fopen("report.txt", "w");          //report파일이 없으므로 파일 새로 생성

    for (int i = 0; i < MAX; i++)
    {

        int rand1 = rand();

        if (rand1 % 10 == 0)
        {                                                                                                      
            red_cnt++;
            if (rand() % 20 == 0)
            {
                error_cnt++;
                element err_red;
                err_red.pen_cnt = i;
                err_red.pen_id = rand1;
                strcpy(err_red.pen_color, "빨강");
                enqueue(&error, err_red);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
            }
            else
            {
                element red;
                red.pen_cnt = i;
                red.pen_id = rand1;
                strcpy(red.pen_color, "빨강");
                enqueue(&pen, red);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
            }
        }
        if (rand1 % 10 == 1)
        {
            blue_cnt++;
            if (rand() % 20 == 0)
            {
                error_cnt++;
                element err_blue;
                err_blue.pen_cnt = i;
                err_blue.pen_id = rand1;
                strcpy(err_blue.pen_color, "파랑");
                enqueue(&error, err_blue);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
            }
            else
            {
                element blue;
                blue.pen_cnt = i;
                blue.pen_id = rand1;
                strcpy(blue.pen_color, "파랑");
                enqueue(&pen, blue);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
            }
        }
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
        {
            black_cnt++;
            if (rand() % 20 == 0)
            {
                error_cnt++;
                element err_black;
                err_black.pen_cnt = i;
                err_black.pen_id = rand1;
                strcpy(err_black.pen_color, "검정");
                enqueue(&error, err_black);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
            }
            else
            {
                element black;
                black.pen_cnt = i;
                black.pen_id = rand1;
                strcpy(black.pen_color, "검정");
                enqueue(&pen, black);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
            }
        }
       
    }
    fclose(fp);
        
    queue_print(&error);

    fp = fopen("error.txt", "at");

    const int error_percent = MAX * 5 / MAX;

    fprintf(fp, "불량률 약 %d%%\n", error_percent);

    total_cnt = black_cnt + red_cnt + blue_cnt;

    fprintf(fp, "금일생산볼펜 %d개=> 검%d개, 빨%d개, 파%d개 \n", total_cnt, black_cnt, red_cnt, blue_cnt);
    fclose(fp);
}
void append() {
    FILE* fp;
    QueueType pen;
    QueueType error;
    init_queue(&pen);
    init_queue(&error);

    char buffer[1024];
    char* token;
    int idx = 0, i=0;
    int err[MAX];
    int value = 0;

    srand(time(NULL));

    fp = fopen("report.txt", "at+");

    while (!feof(fp)) {                 //report파일에서 마지막 볼팬이 몇번째인지 읽어드려 value에 저장
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

    for (int i = value + 1; i < value + 11; i++) {  //value+1번째부터 10개 생산
        int rand1 = rand();

        if (rand1 % 10 == 0)
        {
            red_cnt++;
            if (rand() % 20 == 0)
            {
                error_cnt++;
                element err_red;
                err_red.pen_cnt = i;
                err_red.pen_id = rand1;
                strcpy(err_red.pen_color, "빨강");
                enqueue(&error, err_red);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
            }
            else
            {
                element red;
                red.pen_cnt = i;
                red.pen_id = rand1;
                strcpy(red.pen_color, "빨강");
                enqueue(&pen, red);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
            }
        }
        if (rand1 % 10 == 1)
        {
            blue_cnt++;
            if (rand() % 20 == 0)
            {
                error_cnt++;
                element err_blue;
                err_blue.pen_cnt = i;
                err_blue.pen_id = rand1;
                strcpy(err_blue.pen_color, "파랑");
                enqueue(&error, err_blue);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
            }
            else
            {
                element blue;
                blue.pen_cnt=i;
                blue.pen_id = rand1;
                strcpy(blue.pen_color, "파랑");
                enqueue(&pen, blue);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
            }
        }
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
        {
            black_cnt++;
            if (rand() % 20 == 0)
            {
                error_cnt++;
                element err_black;
                err_black.pen_cnt=i;
                err_black.pen_id = rand1;
                strcpy(err_black.pen_color, "검정");
                enqueue(&error, err_black);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
            }
            else
            {
                element black;
                black.pen_cnt=i;
                black.pen_id = rand1;
                strcpy(black.pen_color, "검정");
                enqueue(&pen, black);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
            }
        }
    }
    fclose(fp);


    queue_print(&error);


    fp = fopen("error.txt", "at");
    const int error_percent = MAX * 5 / MAX;
    fprintf(fp, "불량률 약 %d%%\n", error_percent);
    total_cnt = black_cnt + red_cnt + blue_cnt;
    fprintf(fp, "금일생산볼펜 %d개=> 검%d개, 빨%d개, 파%d개 \n", total_cnt, black_cnt, red_cnt, blue_cnt);
    fclose(fp);

        
}
int main()
{
    FILE* fp;
    fp = fopen("report.txt", "r");

    if (fp == NULL) {   //report파일이 없다면 makefile함수 호출
        makefile();
    }
    else {              //report파일이 있다면 append함수 호출
        fclose(fp);
        append();
    }

    system("notepad.exe report.txt");   //생산품 전체를 저장하는 파일
    system("notepad.exe error.txt");    //불량품만 따로 저장하는 파일
    return 0;
}
