#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#define MAX 100 // 10의 승수 만큼 감소/증가 시켜 실험해볼 것
#define MAX_QUEUE_SIZE 100

int black_cnt, red_cnt, blue_cnt;
int error_cnt, error_percent, total_cnt;
int red_error_cnt = 0, blue_error_cnt = 0, black_error_cnt = 0;
char filename[20];

typedef struct {            // 구조체로 저장
    int pen_id;
    char pen_color[5];
    int pen_cnt;
    char date;
} element;

typedef struct { // 큐 타입
    element data[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;

// 오류 함수
void error(char* message)
{
    fprintf(stderr, "%s\n", message);   // 실행창에 오류 메시지 출력
    exit(1);            // 실행중인 프로그램 종료
}

// 공백 상태 검출 함수
void init_queue(QueueType* q)
{
    q->front = q->rear = 0;         // 원형큐이기 때문에 초기값 = 0
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
void queue_print(QueueType* q) {            // 불량품만 따로 저장하는 파일을 만드는 함수
    FILE* fp;           // 파일 포인터
    char err[20] = "error";         // 제목에 입력받은 날짜뒤에 error를 붙여서 에러파일만 모아 놓았음을 표시
    char* p;
    p = strcat(err, filename);          // 입력받은 날짜 뒤에 error를 붙이는 코드

    fp = fopen(p, "at+");           // at+모드로 파일을 불러와서 기존에 파일이 없으면 새로 생성하고, 파일이 있으면 기존 파일에 이어서 작성
    if (!is_empty(q)) {         // 큐 타입이 비어있지 않은 경우 프로그램을 실행함
        int i = q->front;           // front 위치 이동
        do {
            i = (i + 1) % (MAX_QUEUE_SIZE);         // i의 값은 i + 1 을 MAX(100)으로 나눈 나머지 이므로 i+1값이 됨 (처음 한번만 실행)
            fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", q->data[i].pen_cnt, q->data[i].pen_color, q->data[i].pen_id); // fprintf로 파일에 입출력함
            if (i == q->rear)           // i의 값이 rear 가게되면 더 늘어갈 값이 없으므로
                break;              // break로 반복문 탈출
        } while (i != q->front);            // i 값이 front값이 아니면 계속 반복
    }
    printf("\n");           // 가독성을 위해 줄 띄우기

    error_cnt = red_error_cnt + blue_error_cnt + black_error_cnt;           // 불량품 총 개수 = 빨간볼펜불량 + 파랑볼펜불량 + 검은볼펜불량
    total_cnt = black_cnt + red_cnt + blue_cnt;             // 총 개수 = 빨간볼펜 수 + 파란볼펜 수 + 검은볼펜 수

    double error_percent = (double)error_cnt / (double)total_cnt * MAX;         // 불량볼펜개수 / 총 볼펜개수로 불량률 계산

    fprintf(fp, "불량률 약 %.1lf %%\n", error_percent);         // 계산한 불량률을 파일입출력으로 파일에 출력
    fprintf(fp, "금일생산볼펜 %d개=> 검%d개, 빨%d개, 파%d개 \n", total_cnt, black_cnt, red_cnt, blue_cnt);

    fclose(fp);         // 작성이 완료된 파일을 닫음
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

void makefile() {           // 입력받은 날짜를 이름으로 하는 파일을 생성하는 함수
    FILE* fp;                   // 입력받은 날짜를 제목으로 하는 파일
    FILE* total = fopen("total_report.txt", "at+");         // 총 생산품을 저장하는 파일
    QueueType pen;
    QueueType error;
    init_queue(&pen);
    init_queue(&error);
    char* p;                // 파일이름을 저장할 변수
    srand(time(NULL));          // rand()의 랜덤값이 반복되는 것을 방지하기 위해 작성

    p = filename;               // 파일이름을 저장함
    fp = fopen(p, "w");
    fprintf(total, "\n금일 날짜 : %s\n", filename);         // 총 생산품을 저장하는 파일에 파일이름(=입력받은 날짜)를 입력

    for (int i = 0; i < MAX; i++) {             // max만큼 반복하여 max 만큼 볼펜 생산

        int rand1 = rand();         // 랜덤값 생성 코드

        if (rand1 % 10 == 0) {          // 10으로 나눈 나머지가 0일 확률 = 10%
            red_cnt++;              // 총 빨간 볼펜 생산 ( 생산한 개수만큼 red_cnt 증가)
            if (rand() % 20 == 0) {            // 0부터 20-1 까지의 수 중 무작위로 뽑았을 때 0인 경우 (5%확률)일때 실행
                red_error_cnt++;            // 불량 빨간 볼펜 수 증가
                element err_red;            // 구조체에 넣음
                err_red.pen_cnt = i;            // 빨간 볼펜 번호 (몇번인지) 저장
                err_red.pen_id = rand1;                 // 볼펜 고유 id 저장
                strcpy(err_red.pen_color, "빨강");            // 무슨 색깔인지 저장
                enqueue(&error, err_red);               // 출력
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
                // 불량임을 표시해서 입력받은 날짜 파일에 출력
                fprintf(total, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
                // 총 생산품을 저장하는 파일에 출력
            }
            else {          // 나머지의 경우 = 불량이 아닐 경우
                element red;            // 구조체 빨강 선언
                red.pen_cnt = i;            // 볼펜 번호 저장
                red.pen_id = rand1;         // 볼펜 고유 id 저장
                strcpy(red.pen_color, "빨강");            // 볼펜 색깔 저장
                enqueue(&pen, red);             // 출력
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
                // 생산된 볼펜을 입력받은 날짜 파일에 출력
                fprintf(total, "%d 번 %s 색 볼펜번호: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
                // 생산된 볼펜을 총 생산량 파일에 출력
            }
        }
        if (rand1 % 10 == 1) {              // 10으로 나눈 나머지가 1인 경우 ( 10% 확률)
            blue_cnt++;             // 총 파란 볼펜 수 증가
            if (rand() % 20 == 1) {             // 0부터 20-1까지의 수 중 무작위로 뽑았을 때 1인 경우 (5%확률)에 실행
                blue_error_cnt++;               // 불량 파란 볼펜 수 증가
                element err_blue;           // 구조체에 넣음
                err_blue.pen_cnt = i;           // 볼펜 번호 저장
                err_blue.pen_id = rand1;            // 볼펜 고유 id 저장
                strcpy(err_blue.pen_color, "파랑");           // 볼펜 숫자 저장
                enqueue(&error, err_blue);              // 불량 파랑 볼펜 출력
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
                // 불량임을 표시해서 입력받은 날짜 파일에 출력
                fprintf(total, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
                // 총 생산품을 저장하는 파일에 출력
            }
            else {              // 나머지의 경우 = 불량이 아닐 경우
                element blue;       // 구조체 파랑 선언
                blue.pen_cnt = i;           // 볼펜 번호 저장
                blue.pen_id = rand1;            // 볼펜 고유 id 저장
                strcpy(blue.pen_color, "파랑");           // 볼펜 색깔 저장
                enqueue(&pen, blue);            // 출력
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
                // 불량임을 표시해서 입력받은 날짜 파일에 출력
                fprintf(total, "%d 번 %s 색 볼펜번호: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
                // 총 생산품을 저장하는 파일에 출력
            }
        }
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9)) {       // 그 이외의 경우(80%확률)
            black_cnt++;            // 총 검은색 볼펜 수 증가
            if (rand() % 20 == 0) {         // 0부터 20-1 까지의 수 중 무작위로 뽑았을 때 0인 경우 (5%확률)일때 실행
                black_error_cnt++;          // 불량 검은 볼펜 수 증가
                element err_black;          // 구조체에 넣음
                err_black.pen_cnt = i;          // 볼펜 번호 저장
                err_black.pen_id = rand1;           // 볼펜 고유 id 저장
                strcpy(err_black.pen_color, "검정");          // 볼펜 색깔 저장
                enqueue(&error, err_black);             // 출력
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
                // 불량임을 표시해서 입력받은 날짜 파일에 출력
                fprintf(total, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
                //  총 생산품을 저장하는 파일에 출력
            }
            else {          // 나머지의 경우 = 불량이 아닐 경우
                element black;          // 검은색 구조체 선언
                black.pen_cnt = i;          // 볼펜 번호 저장
                black.pen_id = rand1;           // 볼펜 고유 id 저장
                strcpy(black.pen_color, "검정");          // 볼펜 색깔 저장
                enqueue(&pen, black);           // 출력
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
                //  불량임을 표시해서 입력받은 날짜 파일에 출력
                fprintf(total, "%d 번 %s 색 볼펜번호: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
                // 총 생산품을 저장하는 파일에 출력
            }
        }

    }
    fclose(fp);
    fclose(total);

    queue_print(&error);
}
void append() {         // 입력받은 날짜를 제목으로 하는 파일이 존재할 경우, 그 파일을 열고 이어서 작성하는 함수
    FILE* fp;
    FILE* total = fopen("total_report.txt", "at+");         // 지금까지 생산한 볼펜을 저장하는 파일을 열고 이어서 작성함
    QueueType pen;
    QueueType error;
    init_queue(&pen);
    init_queue(&error);

    char buffer[1024];
    char* token;
    char* p;
    int i = 0;
    int value = 0;

    srand(time(NULL));          // 난수 생성함수로 time을 넣어 난수가 반복되는 것을 방지함
    p = filename;       // 파일 이름(입력한 날짜)를 이름으로 하는 파일을 가리킴

    fp = fopen(p, "at+");           // 파일 이름(입력한 날짜)으로 된 파일을 at+모드로 열기
    fprintf(total, "\n금일 날짜 : %s\n", filename);         // 총 생산량을 저장하는 파일에 입력한 날짜도 저장하여 언제 만들어졌는지 알아볼 수 있게 함

    while (!feof(fp)) {                 //report파일에서 마지막 볼팬이 몇번째인지 읽어들여 value에 저장
        i = 0;
        fgets(buffer, 1024, fp);            // fgets를 사용하여 enter가 입력된 곳까지 값을 읽어옴
        token = strtok(buffer, " ");        // strtok(문자열 자르기) 함수로 " "이 나올때까지 = 끝까지 읽어들인다
        while (token != NULL) {         // 파일의 맨 끝까지 읽기
            if (i == 0) {
                value = atoi(token);            // atoi 함수는 형변환 함수로 token(char형)을 value(int형)으로 바꿔줌
            }
            i++;
            token = strtok(NULL, " ");
        }
    }
    for (i = value + 1; i < value + MAX + 1; i++) {  //value+1번째부터 100개 생산
        int rand1 = rand();
        if (rand1 % 10 == 0) {          // 10으로 나눴을 때 나머지가 0인 경우 = 10%의 경우
            red_cnt++;              // 빨간 볼펜 생성
            if (rand() % 20 == 0) {            // 그 중 0부터 20-1까지의 숫자를 골랐을 때 0인 경우( = 5%확률)에는 불량볼펜
                red_error_cnt++;            // 빨간 불량 볼펜의 개수 증가
                element err_red;            // 구조체에 저장
                err_red.pen_cnt = i;            // 볼벤 번호 저장
                err_red.pen_id = rand1;             // 볼펜 고유 id 저장
                strcpy(err_red.pen_color, "빨강");            // 빨간색임을 저장
                enqueue(&error, err_red);           // error 구조체에 err_red구조체 저장
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);      // 금일 날짜 파일에 불량임을 표시하여 출력
                fprintf(total, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);           // 총 생산량 파일에 불량임을 표시하여 출력 
            }
            else {          // 그 이외의 경우 = 정상 볼펜의 경우
                element red;            // 빨간 볼펜 구조체에 저장
                red.pen_cnt = i;            // 볼펜 번호 저장
                red.pen_id = rand1;         // 볼펜 고유 id 저장
                strcpy(red.pen_color, "빨강");            // 빨간색임을 저장
                enqueue(&pen, red);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", red.pen_cnt, red.pen_color, red.pen_id);        // 금일 날짜 파일에 볼펜 저장
                fprintf(total, "%d 번 %s 색 볼펜번호: %d\n", red.pen_cnt, red.pen_color, red.pen_id);         // 총 생산량 파일에 볼펜 저장
            }
        }
        if (rand1 % 10 == 1) {              // 10으로 나눈 나머지가 1인경우 = 10%확률
            blue_cnt++;         // 파란 볼펜 개수 증가
            if (rand() % 20 == 1) {     // 0부터 20-1 까지의 숫자 중 1인 경우 = 5%확률
                blue_error_cnt++;           // 파랑 불량 볼펜 개수 증가
                element err_blue;           // 파랑 불량 볼펜 구조체에 저장
                err_blue.pen_cnt = i;           // 볼펜 번호 저장
                err_blue.pen_id = rand1;            // 볼펜 고유 id 저장
                strcpy(err_blue.pen_color, "파랑");           // 파란색임을 저장
                enqueue(&error, err_blue);          // error구조체에 파랑 불량 볼펜 구조체 저장
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);       // 금일 날짜 파일에 불량임을 표시하여 저장
                fprintf(total, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);        // 총 생산량 파일에 불량임을 표시하여 저장
            }
            else {
                element blue;           // 파랑 볼펜 구조체에 저장
                blue.pen_cnt = i;           // 볼펜 번호 저장
                blue.pen_id = rand1;            // 볼펜 고유 id 저장
                strcpy(blue.pen_color, "파랑");           // 파란색임을 저장
                enqueue(&pen, blue);            // pen 구조체에 파란 볼펜 구조체 저장
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);     // 금일 날짜 파일에 볼펜 출력
                fprintf(total, "%d 번 %s 색 볼펜번호: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);          // 총 생산량 파일에 볼펜 출력
            }
        }  
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9)) {       // 10으로 나눈 나머지가 2보다 크거나 같고 9보다 작거나 같은 경우 = 80%확률
            black_cnt++;            // 검정 볼펜 개수 증가
            if (rand() % 20 == 0) {         // 0부터 20-1까지 수 중 0이 나올 경우 = 5%확률
                black_error_cnt++;          // 검정 불량 볼펜 개수 증가
                element err_black;          // 검정 불량 볼펜 구조체에 저장
                err_black.pen_cnt = i;          // 검정 볼펜 번호 저장
                err_black.pen_id = rand1;           // 볼펜 고유 id 저장
                strcpy(err_black.pen_color, "검정");          // 검정색임을 저장
                enqueue(&error, err_black);         // error구조체에 검정 불량 볼펜 구조체 저장
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);         // 금일 날짜 파일에 불량임을 표시하여 저장
                fprintf(total, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);     // 총 생산량 파일에 불량임을 표시하여 저장
            }
            else {
                element black;          // 검정 볼펜 구조체에 저장
                black.pen_cnt = i;          // 검정 볼펜 번호 저장
                black.pen_id = rand1;           // 검정 볼펜 고유 id 저장
                strcpy(black.pen_color, "검정");          // 검정색임을 저장
                enqueue(&pen, black);           // pen 구조체에 검정 볼펜 구조체 저장
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", black.pen_cnt, black.pen_color, black.pen_id);      // 금일 날짜 파일에 볼펜 저장
                fprintf(total, "%d 번 %s 색 볼펜번호: %d\n", black.pen_cnt, black.pen_color, black.pen_id);       // 총 생샌량 파일에 볼펜 저장
            }
        }
    }
    fclose(fp);         // 열었던 금일 날짜 파일 닫기
    fclose(total);          // 열었던 총 생산량 파일 닫기

    queue_print(&error);        // 에러 파일 출력
}
int main() {
    FILE* fp;       // 특정 날짜에 생성된 볼펜 개수를 저장하는 파일의 포인터
    char err[20] = "error";         // 입력받은 날짜에 생성된 볼펜 중 불량품만 저장하는 파일의 이름을 만들기 위해 선언
    char txt[] = ".txt";        // 입력받은 날짜를 이름으로 하는 텍스트 파일을 만들기 위해 선언
    char openfile1[MAX] = "notepad.exe ";       // 텍스트 파일로 선언
    char openfile2[MAX] = "notepad.exe ";       // 텍스트 파일로 선언
    char* p1, p2;

    printf("원하는 날짜 입력(여섯숫자)>>");        // 날짜를 입력받는 코드
    scanf("%s", &filename);             // 입력 받은 날짜를 filename공간에 저장함

    p1 = strcat(filename, txt);         // 입력받은 날짜를 제목으로 하는 파일 생성

    fp = fopen(p1, "r");            // 파일을 read 모드로 불러옴

    if (fp == NULL) {   // 입력받은 날짜를 제목으로 하는 파일이 존재하지 않으면
                        // 새롭게 입력받은 날짜를 제목으로 하는 파일을 생성
        makefile();     // 파일을 생성하는 makefile 함수 실행
    }
    else {              // 입력받은 날짜를 제목으로 하는 파일이 존재한다면
        fclose(fp);     // read 모드로 읽은 파일을 닫고
        append();       // 입력받은 날짜를 제목으로 하는 파일을 불러와서 이어서 작성
    }
    system(strcat(openfile1, filename));   // 금일 생산품을 저장하는 파일을 불러옴
    strcat(err, filename);       // 입력받은 날짜를 제목으로 하는 불량품만 저장하는 파일이름 생성
    system(strcat(openfile2, err));         // 불량품만 따로 저장하는 파일을 불러옴
    system("notepad.exe total_report.txt");         // 지금까지 생상한 모든 볼펜을 저장하는 파일을 불러옴

    return 0;
}