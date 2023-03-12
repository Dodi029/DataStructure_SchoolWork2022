#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 10 // 10의 승수 만큼 감소/증가 시켜 실험해볼 것

int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt;

typedef struct ballpen {
	int a;
	char b[MAX];
	int c;

} StackType;


int main()
{
	srand(time(NULL));
	const int error_percent = MAX * 5 / MAX; // 5%의 불량률

	FILE* fp;
	StackType jot[1024];
	char buffer[1024];
	char* token;
	int i = 0;
	int idx = 0;
	int value = 0;

	fp = fopen("report.txt", "r");

	if (fp == NULL) {
		fp = fopen("report.txt", "w");
		for (int i = 0; i < MAX; i++)
		{

			int rand1 = rand();


			jot[idx].a = i;
			jot[idx].c = rand1;

			if (rand1 % 10 == 0) {
				red_cnt++;
				strcpy(jot[idx].b, "빨간색");
			}
			if (rand1 % 10 == 1) {
				blue_cnt++;
				strcpy(jot[idx].b, "파랑색");
			}
			if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9)) {
				black_cnt++;
				strcpy(jot[idx].b, "검정색");
			}
			fprintf(fp, "%d 번 %s 볼펜번호: %d\n", jot[idx].a, jot[idx].b, jot[idx].c);
			idx++;
		}
		fclose(fp);
	}
	else {
		fclose(fp);
		fp = fopen("report.txt", "at+");
		while (!feof(fp)) {
			i = 0;
			fgets(buffer, 1024, fp);
			token = strtok(buffer, " ");
			while (token != NULL) {
				if (i == 0) {
					jot[idx].a = atoi(token);
					value = atoi(token);
				}
				i++;
				token = strtok(NULL, " ");
			}
			idx++;
		}
		idx = value + 1;
		for (int i = value + 1; i < value + 11; i++)		//10개씩 생산
		{

			int rand1 = rand();


			jot[idx].a = i;
			jot[idx].c = rand1;

			if (rand1 % 10 == 0) {
				red_cnt++;
				strcpy(jot[idx].b, "빨간색");
			}
			if (rand1 % 10 == 1) {
				blue_cnt++;
				strcpy(jot[idx].b, "파랑색");
			}
			if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9)) {
				black_cnt++;
				strcpy(jot[idx].b, "검정색");
			}
			fprintf(fp, "%03d 번 %s 볼펜번호: %d\n", jot[idx].a, jot[idx].b, jot[idx].c);
			idx++;
		}

	}

	fclose(fp);



	total_cnt = black_cnt + red_cnt + blue_cnt;

	FILE* pErr = fopen("error.txt", "at+");

	struct tm* t;					// 날짜 표시
	time_t base = time(NULL);
	t = localtime(&base);

	fprintf(pErr, "%d년 %d월 %d일", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
	fprintf(pErr, " 생산볼펜 % d개 = > 검 % d개, 빨 % d개, 파 % d개 \n", total_cnt, black_cnt, red_cnt, blue_cnt);
	fprintf(pErr, "불량률%d%%\n", error_percent);
	fclose(pErr);

	return 0;
}