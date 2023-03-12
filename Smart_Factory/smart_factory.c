#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 50 // 10의 승수 만큼 감소/증가 시켜 실험해볼 것

int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt;

int main()
{
	FILE* fp; // 1. 파일 포인터 생성

	srand(time(NULL));
	const int error_percent = MAX * 5 / MAX; // 5%의 불량률
	
	fp = fopen("report.txt", "at+");   // 2. 데이터를 누적시키고, +기능으로 read&write 기능을 함.

	for (int i = 0; i < MAX; i++)
	{

		int rand1 = rand();

		// 3. fpritf()함수로 '모니터'와 '파일'에 동시 출력
		fprintf(stdout, "%03d개 볼펜생산 -> 볼펜번호%d\n", i, rand1);
		fprintf(fp,     "%03d개 볼펜생산 -> 볼펜번호%d\n", i, rand1);

		if (rand1 % 10 == 0)
			red_cnt++;

		if (rand1 % 10 == 1)
			blue_cnt++;

		if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
			black_cnt++;

	}
	total_cnt = black_cnt + red_cnt + blue_cnt;

	// 4. fpritf()함수로 '모니터'와 '파일'에 동시 출력
	fprintf(stdout,"총생산볼펜 %d=> 검%d, 빨%d, 파%d \n", total_cnt, black_cnt, red_cnt, blue_cnt);
	fprintf(fp, "총생산볼펜 %d=> 검%d, 빨%d, 파%d \n", total_cnt, black_cnt, red_cnt, blue_cnt);

	fprintf(stdout, "불량률%d%%\n", error_percent);
	fprintf(fp, "불량률%d%%\n", error_percent);
	fclose(fp);

	system("notepad.exe report.txt");  // 자동으로 메모장을 오픈
	
	return 0;
}