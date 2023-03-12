#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100 // 10�� �¼� ��ŭ ����/���� ���� �����غ� ��

int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt;

typedef struct ballpen {
    int a;
    char b[MAX];
    double c;
} StackType;


int main()
{
    srand(time(NULL));
    const int error_percent = MAX * 5 / MAX; // 5%�� �ҷ���

    FILE* fp;
    StackType jot[MAX];
    char buffer[1024];
    char* token;
    int i = 0;
    int idx = 0;
    int value = 0;

    fp = fopen("report_final_psh.txt", "r");

    if (fp == NULL) {
        fp = fopen("report_final_psh.txt", "w");
        for (int i = 0; i < MAX; i++)
        {

            int rand1 = rand();


            fprintf(fp, "%03d ���������->�����ȣ %d\n", i, rand1);

            if (rand1 % 10 == 0)
                red_cnt++;

            if (rand1 % 10 == 1)
                blue_cnt++;

            if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
                black_cnt++;

        }
        fclose(fp);
    }
    else {
        fclose(fp);
        fp = fopen("report_final_psh.txt", "at+");
        while (!feof(fp)) {
            i = 0;
            fgets(buffer, 1024, fp);
            token = strtok(buffer, " ");
            while (token != NULL) {
                if (i == 0) {
                    jot[idx].a = atoi(token);
                    value = atoi(token);
                }
                else if (i == 1) {
                    strcpy(jot[idx].b, token);
                }
                else {
                    jot[idx].c = atoi(token);
                }
                i++;
                token = strtok(NULL, " ");
            }
            idx++;
        }
        for (int i = value + 1; i < value + 11; i++)   //10���� �߰�����
        {
            int rand1 = rand();

            fprintf(fp, "%03d ���������->�����ȣ %d\n", i, rand1);

            if (rand1 % 10 == 0)
                red_cnt++;

            if (rand1 % 10 == 1)
                blue_cnt++;

            if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
                black_cnt++;

        }

    }

    fclose(fp);

    total_cnt = black_cnt + red_cnt + blue_cnt;
    FILE* pErr = fopen("error2.txt", 'w');
    fprintf(pErr, "�ѻ��꺼�� %d=> ��%d, ��%d, ��%d \n", total_cnt, black_cnt, red_cnt, blue_cnt);
    fprintf(pErr, "�ҷ���%d%%\n", error_percent);
    fclose(pErr);

    return 0;
}