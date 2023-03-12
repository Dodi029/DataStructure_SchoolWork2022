#include <stdio.h>
#include <stdlib.h>
#define MAX 100 // 10�� �¼� ��ŭ ����/���� ���� �����غ� ��

int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt;

int main()
{
	srand(time(NULL));
	const int error_percent = MAX * 5 / 100; // 5%�� �ҷ���
	

	for (int i = 0; i < MAX; i++)
	{

		int rand1 = rand();


		printf("%03d�� ������� -> �����ȣ%d\n\n", i, rand1);

		if (rand1 % 10 == 0)
			red_cnt++;

		if (rand1 % 10 == 1)
			blue_cnt++;

		if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
			black_cnt++;

	}
	total_cnt = black_cnt + red_cnt + blue_cnt;

	printf("\n\n�ѻ��꺼�� %d=> ��%d, ��%d, ��%d \n\n", total_cnt, black_cnt, red_cnt, blue_cnt);
	printf("�ҷ���%d%%\n\n", error_percent);

	return 0;
}