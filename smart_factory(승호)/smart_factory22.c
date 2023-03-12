#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100 // 10�� �¼� ��ŭ ����/���� ���� �����غ� ��

int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt;

typedef struct ballpen {
	int a;
	char b[MAX];
	int c;

} StackType;


int main()
{
	srand(time(NULL));
	const int error_percent = MAX * 5 / MAX; // 5%�� �ҷ���

	FILE* fp;
	StackType jot[1024];
	char buffer[1024];
	char* token;
	int i = 0;
	int idx = 0;
	int value = 0;

	struct tm* t;					// ��¥ ǥ��
	time_t base = time(NULL);
	t = localtime(&base);

	fp = fopen("report.txt", "r");

	if (fp == NULL) {
		fp = fopen("report.txt", "w");

		fprintf(fp, "%d�� %d�� %d��\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

		for (int i = 0; i < MAX; i++) {

			int rand1 = rand();

			jot[idx].a = i;
			jot[idx].c = rand1;

			if (rand1 % 10 == 0) {
				red_cnt++;
				strcpy(jot[idx].b, "������");
			}
			if (rand1 % 10 == 1) {
				blue_cnt++;
				strcpy(jot[idx].b, "�Ķ���");
			}
			if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9)) {
				black_cnt++;
				strcpy(jot[idx].b, "������");
			}
			fprintf(fp, "%d �� %s �����ȣ: %d\n", jot[idx].a, jot[idx].b, jot[idx].c);
			idx++;
		}
		fclose(fp);
	}
	else {
		fclose(fp);
		fp = fopen("report.txt", "at+");

		fprintf(fp, "%d�� %d�� %d��\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

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

		for (int i = value + 1; i < value + 101; i++)		//100���� ����
		{

			int rand1 = rand();


			jot[idx].a = i;
			jot[idx].c = rand1;

			if (rand1 % 10 == 0) {
				red_cnt++;
				strcpy(jot[idx].b, "������");
			}
			if (rand1 % 10 == 1) {
				blue_cnt++;
				strcpy(jot[idx].b, "�Ķ���");
			}
			if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9)) {
				black_cnt++;
				strcpy(jot[idx].b, "������");
			}
			fprintf(fp, "%03d �� %s �����ȣ: %d\n", jot[idx].a, jot[idx].b, jot[idx].c);
			idx++;
		}

	}

	fclose(fp);

	total_cnt = black_cnt + red_cnt + blue_cnt;
	FILE* pErr = fopen("error.txt", "at+");

	fprintf(pErr, "%d�� %d�� %d��\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
	fprintf(pErr, " ���꺼�� % d�� = > �� % d��, �� % d��, �� % d�� \n", total_cnt, black_cnt, red_cnt, blue_cnt);
	fprintf(pErr, "�ҷ���%d%%\n", error_percent);
	fclose(pErr);

	system("notepad.exe report.txt");
	system("notepad.exe error.txt");

	return 0;
}