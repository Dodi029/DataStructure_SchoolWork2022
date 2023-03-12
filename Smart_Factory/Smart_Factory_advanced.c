#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 50 // 10�� �¼� ��ŭ ����/���� ���� �����غ� ��

int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt;

int main()
{
	FILE* fp; // 1. ���� ������ ����

	srand(time(NULL));
	const int error_percent = MAX * 5 / MAX; // 5%�� �ҷ���

	fp = fopen("report_final.txt", "r");   // 2. �����͸� ������Ű��, +������� read&write ����� ��.

	if (fp == NULL) {
		for (int i = 0; i < MAX; i++)
		{
			fp = fopen("report_final.txt", "at+");

			int rand1 = rand();

			// 3. fpritf()�Լ��� '�����'�� '����'�� ���� ���
			fprintf(stdout, "%03d�� ������� -> �����ȣ%d\n", i, rand1);
			fprintf(fp, "%03d�� ������� -> �����ȣ%d\n", i, rand1);

			if (rand1 % 10 == 0)
				red_cnt++;

			if (rand1 % 10 == 1)
				blue_cnt++;

			if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
				black_cnt++;

		}
		total_cnt = black_cnt + red_cnt + blue_cnt;

		// 4. fpritf()�Լ��� '�����'�� '����'�� ���� ���
		fprintf(stdout, "�ѻ��꺼�� %d=> ��%d, ��%d, ��%d \n", total_cnt, black_cnt, red_cnt, blue_cnt);
		fprintf(fp, "�ѻ��꺼�� %d=> ��%d, ��%d, ��%d \n", total_cnt, black_cnt, red_cnt, blue_cnt);

		FILE* pErr = fopen("Error.txt", "w");
		fprintf(stdout, "�ҷ���%d%%\n", error_percent);
		fprintf(pErr, "�ҷ���%d%%\n", error_percent);
		fclose(fp);
		fclose(pErr);

		system("notepad.exe report_final.txt");  // �ڵ����� �޸����� ����

		return 0;
	}
	else {
		fclose(fp);
		fp = fopen("report_final.txt", "at+");
		while (!feof(fp)) {
			for (int i = 0; i < MAX; i++)
			{
				fp = fopen("report_final.txt", "at+");

				int rand1 = rand();

				// 3. fpritf()�Լ��� '�����'�� '����'�� ���� ���
				fprintf(stdout, "%03d�� ������� -> �����ȣ%d\n", i, rand1);
				fprintf(fp, "%03d�� ������� -> �����ȣ%d\n", i, rand1);

				if (rand1 % 10 == 0)
					red_cnt++;

				if (rand1 % 10 == 1)
					blue_cnt++;

				if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
					black_cnt++;

			}
			total_cnt = black_cnt + red_cnt + blue_cnt;

			// 4. fpritf()�Լ��� '�����'�� '����'�� ���� ���
			fprintf(stdout, "�ѻ��꺼�� %d=> ��%d, ��%d, ��%d \n", total_cnt, black_cnt, red_cnt, blue_cnt);
			fprintf(fp, "�ѻ��꺼�� %d=> ��%d, ��%d, ��%d \n", total_cnt, black_cnt, red_cnt, blue_cnt);

			FILE* pErr = fopen("Error.txt", "w");
			fprintf(stdout, "�ҷ���%d%%\n", error_percent);
			fprintf(pErr, "�ҷ���%d%%\n", error_percent);
			fclose(fp);
			fclose(pErr);

			system("notepad.exe report_final.txt");  // �ڵ����� �޸����� ����
			system("notepad.exe Error.txt");

			return 0;
		}
	}
}