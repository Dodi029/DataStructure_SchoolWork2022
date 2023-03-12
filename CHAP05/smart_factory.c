#include <stdio.h>
#include <stdlib.h>x`
#define MAX 100 // 10의 승수 만큼 감소/증가 시켜 실험해볼 것

int black_cnt, red_cnt, blue_cnt, error_cnt, error_percent, total_cnt;

int main()
{
	FILE* p;

	srand(time(NULL));
	const int error_percent = MAX * 5 / 100; // 5%의 불량률
	

	for (int i = 0; i < MAX; i++)
	{

		int rand1 = rand();

		// fprintf
		printf("%03d개 볼펜생산 -> 볼펜번호%d\n\n", i, rand1);

		if (rand1 % 10 == 0)
			red_cnt++;

		if (rand1 % 10 == 1)
			blue_cnt++;

		if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9))
			black_cnt++;

	}
	total_cnt = black_cnt + red_cnt + blue_cnt;

	// fprintf함수로 "모니터"와 "파일"에 동시 출력
	fprintf(stdout"\n\n총생산볼펜 %d=> 검%d, 빨%d, 파%d \n\n", total_cnt, black_cnt, red_cnt, blue_cnt);
	fprintf(stdout"불량률%d%%\n\n", error_percent);

	return 0;
}