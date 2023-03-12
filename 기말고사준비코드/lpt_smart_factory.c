#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100 // 10의 승수 만큼 감소/증가 시켜 실험해볼 것
#define MAX_QUEUE_SIZE 100
#define MAX_HEAP_ELEMENT 200

int black_cnt, red_cnt, blue_cnt;
int error_cnt, error_percent, total_cnt;
int red_error_cnt = 0, blue_error_cnt = 0, black_error_cnt = 0;
char filename[20];

typedef struct {            // 구조체로 저장
    int pen_id;
    char pen_color[5];
    int pen_cnt;
    char date;
    int time;
} element;

typedef struct {
    int id;
    int avail;
} lpt_element;

typedef struct {
    lpt_element heap[MAX_HEAP_ELEMENT];
    int heap_size;
} HeapType;

// 생성 함수
HeapType* create()
{
    return (HeapType*)malloc(sizeof(HeapType));
}

// 초기화 함수
void init(HeapType* h)
{
    h->heap_size = 0;
}
// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_min_heap(HeapType* h, lpt_element item)
{
    int i;
    i = ++(h->heap_size);

    //  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while ((i != 1) && (item.avail < h->heap[i / 2].avail)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;     // 새로운 노드를 삽입
}
// 삭제 함수
lpt_element delete_min_heap(HeapType* h)
{
    int parent, child;
    lpt_element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        // 현재 노드의 자식노드중 더 작은 자식노드를 찾는다.
        if ((child < h->heap_size) &&
            (h->heap[child].avail) > h->heap[child + 1].avail)
            child++;
        if (temp.avail < h->heap[child].avail) break;
        // 한 단계 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}
#define JOBS 6
#define MACHINES 3

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
            fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", q->data[i].pen_cnt, q->data[i].pen_color, q->data[i].pen_id);       // fprintf로 파일에 입출력함
            if (i == q->rear)           // i의 값이 rear 가게되면 더 늘어갈 값이 없으므로
                break;              // break로 반복문 탈출
        } while (i != q->front);            // i 값이 front값이 아니면 계속 반복
    }
    printf("\n");           // 가독성을 위해 줄 띄우기

    error_cnt = red_error_cnt + blue_error_cnt + black_error_cnt;           // 불량품 총 개수 = 빨간볼펜불량 + 파랑볼펜불량 + 검은볼펜불량
    total_cnt = black_cnt + red_cnt + blue_cnt;             // 총 개수 = 빨간볼펜 수 + 파란볼펜 수 + 검은볼펜 수

    double error_percent = (double)error_cnt / (double)total_cnt * MAX;         // 불량볼펜개수 / 총 볼펜개수로 불량률 계산

    fprintf(fp, "불량률 약 %.1lf %%\n", error_percent);         // 계산한 불량률을 파일입출력으로 파일에 출력
    fprintf(fp, "\n금일생산볼펜 %d개=> 검%d개, 빨%d개, 파%d개 \n", total_cnt, black_cnt, red_cnt, blue_cnt);

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

void makefile(int n) {           // 입력받은 날짜를 이름으로 하는 파일을 생성하는 함수
    FILE* fp;                   // 입력받은 날짜를 제목으로 하는 파일
    FILE* total = fopen("total_report.txt", "at+");         // 총 생산품을 저장하는 파일
    QueueType pen;
    QueueType error;
    init_queue(&pen);
    init_queue(&error);
    char* p;                // 파일이름을 저장할 변수
    srand(time(NULL));          // rand()의 랜덤값이 반복되는 것을 방지하기 위해 작성

    p = filename;               // 파일이름을 저장함
    fp = fopen(p, "at+");
    fprintf(fp, "\n");
    fprintf(total, "\n금일 날짜 : %s\n", filename);         // 총 생산품을 저장하는 파일에 파일이름(=입력받은 날짜)를 입력

    for (int i = n; i < n + MAX; i++) {             // max만큼 반복하여 max 만큼 볼펜 생산

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

void delay(clock_t n) {         // 프로그램실행을 딜레이 시켜
                                // srand(time(NULL))을 사용했을 때 값이 같아지는 오류를 피함
    clock_t start = clock();
    while (clock() - start < n);        // 입력한 시간만큼 반복하여 delay(1)당 1/1000초를 딜레이함

}

int main() {
    element data[MAX];
    FILE* fp;       // 특정 날짜에 생성된 볼펜 개수를 저장하는 파일의 포인터
    char err[20] = "error";         // 입력받은 날짜에 생성된 볼펜 중 불량품만 저장하는 파일의 이름을 만들기 위해 선언
    char txt[] = ".txt";        // 입력받은 날짜를 이름으로 하는 텍스트 파일을 만들기 위해 선언
    char job[20] = "Jobs";
    char openfile1[MAX] = "notepad.exe ";       // 텍스트 파일로 선언
    char openfile2[MAX] = "notepad.exe ";       // 텍스트 파일로 선언
    // char openfile3[MAX] = "notepad.exe ";       // 텍스트 파일로 선언
    char* p1, p2;
    lpt_element m = { 0, 0 };       // 작업 번호와 작동 가능한 시간을 초기화
    HeapType* h;
    h = create();       // 히프트리 생성
    init(h);            // 히프트리 초기화

    printf("원하는 날짜 입력(여섯숫자)>>");        // 날짜를 입력받는 코드
    scanf("%s", &filename);             // 입력 받은 날짜를 filename공간에 저장함

    p1 = strcat(filename, txt);         // 입력받은 날짜를 제목으로 하는 파일 생성
    fp = fopen(p1, "at+");            // 파일을 read 모드로 불러옴

    printf("공장을 몇 번 가동시키겠습니까? ");     // 100개 생산 공정을 몇 번 할 것인지 입력받음
    int in, ary;
    scanf("%d", &in);       // 입력한 값을 저장
    ary = in * 3;           // 한 번 공정 당 검정, 빨강, 파랑 볼펜으로 총 3개 작업을 하므로 *3을 함
    int i = 0, j = 0;           // i, j 초기화

    printf("딜레이가 있습니다. 잠시만 기다려주세요.\n");     // srand(time(NULL))로 여러번 공정 시 같은 랜던 값이
                                                          // 나오는 오류를 피하기 위해 딜레이를 넣음

    int tmp;            // 걸린 시간을 저장할 임시 공간
    char tmp2[MAX];          // 문자열 저장할 임시 변수

    for (int k = 0; k < in; k++) {      // 입력한 값만큼 100개 생산 공정 반복
        makefile(k * 100);          // 반복문의 수 * 100으로 매개 변수에 값을 넘겨줌
        data[i].time = black_cnt * 1;  //검정볼팬은 개당 1초
        strcpy(data[i].pen_color, "검정");        // 검정색 볼펜임을 배열에 복사
        i++;
        data[i].time = red_cnt * 2;      //빨간 볼팬은 개당 2초
        strcpy(data[i].pen_color, "빨강");        // 빨간색 볼펜임을 배열에 복사
        i++;
        data[i].time = blue_cnt * 2;    //파란 볼팬은 개당 2초
        strcpy(data[i].pen_color, "파랑");        // 파란색 볼펜임을 배열에 복사
        i++;
        black_cnt = red_cnt = blue_cnt = 0;     // 한번 100개 생산 공정을 한 후에는 다음 반복을 위해
        black_error_cnt = red_error_cnt = blue_error_cnt = 0;       // 각 값을 초기화 해줌
        printf("delay %d초...\n", in - k);       // 혹시 모를 딜레이 중에 종료를 방지하기 위해 딜레이 되고 있음을 출력
        delay(1000);        //srand(time(NULL))값을 공정마다 달리해주기위해 delay를 함
    }
    for (int j = 0; j < i; j++) {   //버블정렬을 통한 볼펜 생산에 걸린 시간을 정렬함
        for (int k = 0; k < i - j; k++) {       // lpt 알고리즘을 돌리기 위해서는 데이터가 정렬되어야 하므로
            if (data[k].time < data[k + 1].time) {      // 내림차순으로 정렬함
                tmp = data[k].time;
                strcpy(tmp2, (data + k)->pen_color);

                data[k].time = data[k + 1].time;
                strcpy(data[k].pen_color, data[k + 1].pen_color);

                data[k + 1].time = tmp;
                strcpy(data[k + 1].pen_color, tmp2);
            }
        }
    }
    // avail 값은 기계가 사용 가능하게 되는 시간e
    for (int a = 0; a < MACHINES; a++) {
        m.id = a + 1;
        m.avail = 0;
        insert_min_heap(h, m);
    }
    // 최소 히프에서 기계를 꺼내서 작업을 할당하고 사용가능 시간을 증가 시킨 후에 
    // 다시 최소 히프에 추가
    fprintf(fp, "\n");      // 가독성을 위한 줄띄우기

    for (int a = 0; a < i; a++) {       // lpt.c에 있는 알고리즘을 그대로 가져옴
        m = delete_min_heap(h);     // JOB 대신 어떤 색깔인지 출력함
        fprintf(fp, "% s을 시간 = % d초부터 시간 = % d초까지 기계 % d번에 할당한다. \n", (data + a)->pen_color, m.avail, m.avail + (data + a)->time - 1, m.id);
        m.avail += (data + a)->time;
        insert_min_heap(h, m);
    }

    fclose(fp);
    system(strcat(openfile1, filename));   //입력한 날짜에 해당하는 파일 실행 //openfile1 = "notepad.exe filename.txt"

    strcat(err, filename);
    system(strcat(openfile2, err));    //불량품만 따로 저장한 파일 실행  //openfile2 = "notepad.exe errorfilename.txt"

    system("notepad.exe total_report.txt");         //날짜에 상관없이 여태까지의 모든 생산품을 기록한 파일 실행
    return 0;
}