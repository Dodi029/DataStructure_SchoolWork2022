#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100 // 10�� �¼� ��ŭ ����/���� ���� �����غ� ��
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

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
    s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
    return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else s->data[++(s->top)] = item;
}
// �����Լ�
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
            fprintf(fp, "%d �� %s �� �����ȣ: %d\n", s->data[s->top].pen_cnt, s->data[s->top].pen_color, s->data[s->top].pen_id);
            (s->top)--;
            if (s->top == -1)
                break;
        } while (i != s->top);
    }
    printf("\n");

    error_cnt = red_error_cnt + blue_error_cnt + black_error_cnt;
    total_cnt = black_cnt + red_cnt + blue_cnt;

    double error_percent = (double)error_cnt / (double)total_cnt * MAX;

    fprintf(fp, "�ҷ��� �� %.1lf %%\n", error_percent);

    fprintf(fp, "���ϻ��꺼�� %d��=> ��%d��, ��%d��, ��%d�� \n", total_cnt, black_cnt, red_cnt, blue_cnt);
    fprintf(fp, "-------------------------------------------------------------\n");
    fclose(fp);
}
// ��ũ�Լ�
element peek(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 

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
                strcpy(err_red.pen_color, "����");
                push(&error, err_red);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
            }
            else
            {
                element red;
                red.pen_cnt = i;
                red.pen_id = rand1;
                strcpy(red.pen_color, "����");
                push(&pen, red);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
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
                strcpy(err_blue.pen_color, "�Ķ�");
                push(&error, err_blue);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
            }
            else
            {
                element blue;
                blue.pen_cnt = i;
                blue.pen_id = rand1;
                strcpy(blue.pen_color, "�Ķ�");
                push(&pen, blue);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
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
                strcpy(err_black.pen_color, "����");
                push(&error, err_black);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
            }
            else
            {
                element black;
                black.pen_cnt = i;
                black.pen_id = rand1;
                strcpy(black.pen_color, "����");
                push(&pen, black);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
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
    }

    for (i = value + 1; i < value + 11; i++) {  //value+1��°���� 10�� ����
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
                strcpy(err_red.pen_color, "����");
                push(&error, err_red);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
            }
            else
            {
                element red;
                red.pen_cnt = i;
                red.pen_id = rand1;
                strcpy(red.pen_color, "����");
                push(&pen, red);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
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
                strcpy(err_blue.pen_color, "�Ķ�");
                push(&error, err_blue);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
            }
            else
            {
                element blue;
                blue.pen_cnt = i;
                blue.pen_id = rand1;
                strcpy(blue.pen_color, "�Ķ�");
                push(&pen, blue);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
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
                strcpy(err_black.pen_color, "����");
                push(&error, err_black);
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
            }
            else
            {
                element black;
                black.pen_cnt = i;
                black.pen_id = rand1;
                strcpy(black.pen_color, "����");
                push(&pen, black);
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
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

    printf("���ϴ� ��¥ �Է�(��������)>>");
    scanf("%s", &filename);

    p1 = strcat(filename, txt);

    fp = fopen(p1, "r");

    if (fp == NULL) {   //report������ ���ٸ� makefile�Լ� ȣ��
        makefile();
    }
    else {              //report������ �ִٸ� append�Լ� ȣ��
        fclose(fp);
        append();
    }



    system(strcat(openfile1, filename));   //����ǰ ��ü�� �����ϴ� ����

    strcat(err, filename);
    system(strcat(openfile2, err));    //�ҷ�ǰ�� ���� �����ϴ� ����
    return 0;
}