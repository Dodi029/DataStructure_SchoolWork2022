#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100 // 10의 승수 만큼 감소/증가 시켜 실험해볼 것
#define MAX_STACK_SIZE 100


int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt, red_error_cnt = 0, blue_error_cnt = 0, black_error_cnt = 0;
char filename[20];

typedef struct {
    int pen_id;
    char pen_color[5];
    int pen_cnt;
    char date;
}element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
    s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
    return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
    FILE* fp;
    char err[20] = "error";
    char* p;
    p = strcat(err, filename);

    fp = fopen(p, "at+");

    if (!is_empty(s)) {
        int i = s->top;
        do {
            fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", s->data[s->top].pen_cnt, s->data[s->top].pen_color, s->data[s->top].pen_id);
            (s->top)--;
            if (s->top == -1)
                break;
        } while (i != s->top);
    }
    printf("\n");

    error_cnt = red_error_cnt + blue_error_cnt + black_error_cnt;
    total_cnt = black_cnt + red_cnt + blue_cnt;

    double error_percent = (double)error_cnt / (double)total_cnt * MAX;

    fprintf(fp, "불량률 약 %.1lf %%\n", error_percent);

    fprintf(fp, "금일생산볼펜 %d개=> 검%d개, 빨%d개, 파%d개 \n", total_cnt, black_cnt, red_cnt, blue_cnt);
    fprintf(fp, "-------------------------------------------------------------\n");
    fclose(fp);
}
// 피크함수
element peek(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

void makefile() {
    FILE* fp;
    StackType pen;
    StackType error;
    init_stack(&pen);
    init_stack(&error);
    char* p;
    srand(time(NULL));

    p = filename;
    fp = fopen(p, "w");

    for (int i = 0; i < MAX; i++)
    {

        int rand1 = rand();

        if (rand1 % 10 == 0)
        {
            red_cnt++;
            if (rand() % 20 == 0)
            {
                red_error_cnt++;
                element err_red;
                err_red.pen_cnt = i;
                err_red.pen_id = rand1;
                strcpy(err_red.pen_color, "빨강");
                push(&error, err_red);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
            }
            else
            {
                element red;
                red.pen_cnt = i;
                red.pen_id = rand1;
                strcpy(red.pen_color, "빨강");
                push(&pen, red);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
            }
        }
        if (rand1 % 10 == 1)
        {
            blue_cnt++;
            if (rand() % 20 == 1)
            {
                blue_error_cnt++;
                element err_blue;
                err_blue.pen_cnt = i;
                err_blue.pen_id = rand1;
                strcpy(err_blue.pen_color, "파랑");
                push(&error, err_blue);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
            }
            else
            {
                element blue;
                blue.pen_cnt = i;
                blue.pen_id = rand1;
                strcpy(blue.pen_color, "파랑");
                push(&pen, blue);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
            }
        }
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
        {
            black_cnt++;
            if (rand() % 20 == 0)
            {
                black_error_cnt++;
                element err_black;
                err_black.pen_cnt = i;
                err_black.pen_id = rand1;
                strcpy(err_black.pen_color, "검정");
                push(&error, err_black);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
            }
            else
            {
                element black;
                black.pen_cnt = i;
                black.pen_id = rand1;
                strcpy(black.pen_color, "검정");
                push(&pen, black);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
            }
        }

    }
    fclose(fp);



    pop(&error);
}

void append() {
    FILE* fp;
    StackType pen;
    StackType error;
    init_stack(&pen);
    init_stack(&error);

    char buffer[1024];
    char* token;
    char* p;
    int i = 0;
    int value = 0;

    srand(time(NULL));
    p = filename;

    fp = fopen(p, "at+");

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
    }

    for (i = value + 1; i < value + 11; i++) {  //value+1번째부터 10개 생산
        int rand1 = rand();
        if (rand1 % 10 == 0)
        {
            red_cnt++;
            if (rand() % 20 == 0)
            {
                red_error_cnt++;
                element err_red;
                err_red.pen_cnt = i;
                err_red.pen_id = rand1;
                strcpy(err_red.pen_color, "빨강");
                push(&error, err_red);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
            }
            else
            {
                element red;
                red.pen_cnt = i;
                red.pen_id = rand1;
                strcpy(red.pen_color, "빨강");
                push(&pen, red);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
            }
        }
        if (rand1 % 10 == 1)
        {
            blue_cnt++;
            if (rand() % 20 == 1)
            {
                blue_error_cnt++;
                element err_blue;
                err_blue.pen_cnt = i;
                err_blue.pen_id = rand1;
                strcpy(err_blue.pen_color, "파랑");
                push(&error, err_blue);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
            }
            else
            {
                element blue;
                blue.pen_cnt = i;
                blue.pen_id = rand1;
                strcpy(blue.pen_color, "파랑");
                push(&pen, blue);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
            }
        }
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
        {
            black_cnt++;
            if (rand() % 20 == 0)
            {
                black_error_cnt++;
                element err_black;
                err_black.pen_cnt = i;
                err_black.pen_id = rand1;
                strcpy(err_black.pen_color, "검정");
                push(&error, err_black);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d -> 불량\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
            }
            else
            {
                element black;
                black.pen_cnt = i;
                black.pen_id = rand1;
                strcpy(black.pen_color, "검정");
                push(&pen, black);
                fprintf(fp, "%d 번 %s 색 볼펜번호: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
            }
        }
    }
    fclose(fp);


    pop(&error);
}

int main(void)
{

    FILE* fp;
    char err[20] = "error";
    char txt[] = ".txt";
    char openfile1[MAX] = "notepad.exe ";
    char openfile2[MAX] = "notepad.exe ";
    char* p1;

    printf("원하는 날짜 입력(여섯숫자)>>");
    scanf("%s", &filename);

    p1 = strcat(filename, txt);

    fp = fopen(p1, "r");

    if (fp == NULL) {   //report파일이 없다면 makefile함수 호출
        makefile();
    }
    else {              //report파일이 있다면 append함수 호출
        fclose(fp);
        append();
    }



    system(strcat(openfile1, filename));   //생산품 전체를 저장하는 파일

    strcat(err, filename);
    system(strcat(openfile2, err));    //불량품만 따로 저장하는 파일
    return 0;
}