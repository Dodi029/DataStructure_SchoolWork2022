#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100 // 10의 승수 만큼 감소/증가 시켜 실험해볼 것
#define DAY 5

const int error_percent = MAX * 5 / MAX; // 5%의 불량률

typedef struct {
	int pen_num;        // 볼펜 생산 번호
	int confirm;  // 볼펜 불량 확인  1 : 정상 ,0 : 비정상
	char error_color[10];  // 불량일때 볼펜 색
	int pen_id;    // 볼펜 고유 번호 (난수로 받을것)
}day;

typedef struct {
	int mons;       // 월
	int days;       // 요일
	int total_cnt;  // 총생산개수
	int black_cnt;  // 검은색 볼펜 개수
	int red_cnt;    // 빨간색 볼펜 개수
	int blue_cnt;   // 파란색 볼펜 개수
	int error_cnt;  // 불량 볼펜 개수
	int error_black_cnt;  // 검은색 불량 볼펜 개수
	int error_red_cnt;    // 빨간색 불량 볼펜 개수
	int error_blue_cnt;   // 파란색 불량 볼펜 개수
}sum;

typedef struct { // 큐 타입
	day  data[DAY][MAX];
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
	return ((q->rear + 1) % MAX == q->front);
}

// 원형큐 출력 함수
void queue_print(QueueType* q, FILE* p, int k)
{
	printf("QUEUE(front=%d rear=%d) = \n", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX);
			//fprintf(stdout, "%d개 볼펜생산->볼펜번호 % d\n", q->data[i].pen_num, q->data[i].pen_id);
			if(q->data[k][i].confirm == 0)
				fprintf(p, "%d개 볼펜생산->볼펜번호 %d --->불량\n", q->data[k][i].pen_num, q->data[k][i].pen_id);
			else
				fprintf(p, "%d개 볼펜생산->볼펜번호 %d\n", q->data[k][i].pen_num, q->data[k][i].pen_id);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	fprintf(stdout, "---------------------------\n\n");
	fprintf(p, "---------------------------\n\n");
}

// 삽입 함수
void enqueue(QueueType* q, int id, int i, int bol, char str[], int k)
{
	if (is_full(q))
		fprintf(stdout, "큐가 포화상태입니다");
	else
	{
		q->rear = (q->rear + 1) % MAX;
		q->data[k][q->rear].pen_id = id;
		q->data[k][q->rear].pen_num = i;
		q->data[k][q->rear].confirm = bol;
		strcpy(q->data[k][q->rear].error_color, str);
	}
}

// 삭제 함수
void dequeue(QueueType* q)
{
	if (is_empty(q)) {}
	//error("큐가 공백상태입니다");
	else
	{
		q->front = (q->front + 1) % MAX;
		//q->data[q->front];
	}
}

//// 삭제 함수
//element peek(QueueType* q)
//{
//	if (is_empty(q))
//		error("큐가 공백상태입니다");
//	return q->data[(q->front + 1) % MAX];
//}
//

void input_file(FILE* p, FILE*sump, QueueType* q, sum* sp, int k)
{
	//fprintf(stdout, "%d월%d일 볼펜 생산량\n", total[k].mons, total[k].days);
	fprintf(p, "%d월%d일 볼펜 생산량\n", sp[k].mons, sp[k].days);

	//fprintf(stdout, "\\n총생산볼펜 %d=> 검%d, 빨%d, 파%d \n\n", total[k].total_cnt, total[k].black_cnt, total[k].red_cnt, total[k].blue_cnt);          // 4. fpritf()함수로 '모니터'와 '파일'에 동시 출력
	fprintf(p, "\n총생산볼펜 %d=> 검%d, 빨%d, 파%d \n\n", sp[k].total_cnt, sp[k].black_cnt, sp[k].red_cnt, sp[k].blue_cnt);

	//fprintf(stdout, "%d월%d일 볼펜 불량 생산량\n", total[k].mons, total[k].days);
	fprintf(p, "%d월%d일 볼펜 불량 생산량\n", sp[k].mons, sp[k].days);

	//fprintf(stdout, "불량률%d%%\n\n", error_percent);
	fprintf(p, "불량률%d%%\n\n", error_percent);

	//fprintf(stdout, "불량볼펜 개수 %d=> 검%d, 빨%d, 파%d\n\n", total[k].error_cnt, total[k].error_black_cnt, total[k].error_red_cnt, total[k].error_blue_cnt);
	fprintf(p, "불량볼펜 개수 %d=> 검%d, 빨%d, 파%d\n\n", sp[k].error_cnt, sp[k].error_black_cnt, sp[k].error_red_cnt, sp[k].error_blue_cnt);

	//fprintf(stdout, "불량 볼펜 상세정보 : \n");
	fprintf(p, "불량 볼펜 상세정보 : \n");

		for (int i = 0; i < MAX; i++)
		{
			if (q->data[k][i].confirm == 0)
			{
				//fprintf(stdout, "생산번호 : %d, 색 : %7s, 고유번호 : %d\n", q.data[i].pen_num, q.data[i].error_color, q.data[i].pen_id);
				fprintf(p, "생산번호 : %d, 색 : %7s, 고유번호 : %d\n", q->data[k][i].pen_num, q->data[k][i].error_color, q->data[k][i].pen_id);
			}
		}
		fprintf(p, "----------------------------------\n\n");
}

int main()
{
	FILE* fp; // 1. 파일 포인터 생성
	FILE* sumfp;
	//FILE* errorfp;
	FILE* day1fp;
	FILE* day2fp;
	FILE* day3fp;
	FILE* day4fp;
	FILE* day5fp;


	struct tm* t;                                        //현재 날짜 구하기
	time_t base = time(NULL);                            //
	t = localtime(&base);                                //

	QueueType q;
	sum total[DAY] = {0,0,0,0,0,0,0,0,0,0 };
	int id;
	srand(time(NULL));

	fp = fopen("report.txt", "wt+");   // 2. 데이터를 누적시키고, +기능으로 read&write 기능을 함.
	sumfp = fopen("sumation.txt", "wt+");
	//errorfp = fopen("error.txt", "wt+");
	day1fp = fopen("day1", "at+");
	day2fp = fopen("day2", "at+");
	day3fp = fopen("day3", "at+");
	day4fp = fopen("day4", "at+");
	day5fp = fopen("day5", "at+");

	for (int k = 0; k < DAY; k++)
	{
		init_queue(&q);              // 큐 초기화
		total[k].mons = t->tm_mon + 1;            //오늘 몇월인지
		total[k].days = t->tm_mday + k;           //오늘 일부터 DAY까지
		for (int i = 1; i <= MAX; i++)
		{
			id = rand();

			//fprintf(stdout, "%03d개 볼펜생산 -> 볼펜번호%d\n\n", i, id);                // 3. fpritf()함수로 '모니터'와 '파일'에 동시 출력
			//fprintf(fp,     "%03d개 볼펜생산 -> 볼펜번호%d\n\n", i, id);
			if (id % 10 == 0)
			{
				total[k].red_cnt++;
				if (rand() % 20 == 0)         //불량률 계산
				{
					enqueue(&q, id, i, 0, "red", k);
					total[k].error_red_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "", k);

			}

			if (id % 10 == 1)
			{
				total[k].blue_cnt++;
				if (rand() % 20 == 0)         //불량률 계산
				{
					enqueue(&q, id, i, 0, "blue", k);

					total[k].error_blue_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "blue", k);

			}

			if ((id % 10 >= 2) && (id % 10 <= 9))
			{
				total[k].black_cnt++;
				if (rand() % 20 == 0)         //불량률 계산
				{
					enqueue(&q, id, i, 0, "black", k);
					total[k].error_black_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "black", k);
			}
		}
		queue_print(&q, fp, k);
		total[k].total_cnt = total[k].black_cnt + total[k].red_cnt + total[k].blue_cnt;
		total[k].error_cnt = total[k].error_black_cnt + total[k].error_red_cnt + total[k].error_blue_cnt;
		
	}

	input_file(day1fp, sumfp, &q, total, 0);
	input_file(day2fp, sumfp, &q, total, 1);
	input_file(day3fp, sumfp, &q, total, 2);
	input_file(day4fp, sumfp, &q, total, 3);
	input_file(day5fp, sumfp, &q, total, 4);


	fclose(fp);
	fclose(sumfp);
	fclose(day1fp);
	fclose(day2fp);
	fclose(day3fp);
	fclose(day4fp);
	fclose(day5fp);
	//fclose(errorfp);

	int month_s, day_s;
	fprintf(stdout, "원하는시는 날짜를 입력하시오\n");
	fprintf(stdout, "월 : ");
	fscanf(stdin, "%d", &month_s);
	fprintf(stdout, "일 : ");
	fscanf(stdin, "%d", &day_s);
	
	char ch[100]="";
	for (int i = 0; i < DAY; i++)
	{
		if (total[i].mons == month_s && total[i].days == day_s)
		{
			if (i == 0) strcpy(ch, "notepad.exe day1");
			else if (i == 1) strcpy(ch, "notepad.exe day2");
			else if (i == 2) strcpy(ch, "notepad.exe day3");
			else if (i == 3) strcpy(ch, "notepad.exe day4");
			else if (i == 4) strcpy(ch, "notepad.exe day5");
		}
	}
	if (ch == "")
		fprintf(stdout, "날짜가 잘못입력되었습니다.");
	else
		system(ch);

	//system("notepad.exe report.txt");  // 자동으로 메모장을 오픈
	//system("notepad.exe error.txt");  // 자동으로 메모장을 오픈
	//system("notepad.exe sumation.txt");  // 자동으로 메모장을 오픈


	return 0;
}