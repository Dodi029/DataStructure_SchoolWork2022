#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100 // 10의 승수 만큼 감소/증가 시켜 실험해볼 것
#define DAY 5

typedef struct {
	int pen_num;        // 볼펜 생산 번호
	int confirm;  // 볼펜 불량 확인  1 : 정상 ,0 : 비정상
	char error_color[10];  // 불량일때 볼펜 색
	int pen_id;    // 볼펜 고유 번호 (난수로 받을것)
}day;

typedef struct {
	int days;       // 날짜
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
	day  data[MAX];
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
void queue_print(QueueType* q, FILE* p)
{
	printf("QUEUE(front=%d rear=%d) = \n", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX);
			fprintf(stdout, "%d개 볼펜생산->볼펜번호 % d\n", q->data[i].pen_num, q->data[i].pen_id);
			fprintf(p, "%d개 볼펜생산->볼펜번호 % d\n", q->data[i].pen_num, q->data[i].pen_id);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	fprintf(stdout, "---------------------------\n\n");
	fprintf(p, "---------------------------\n\n");
}

// 삽입 함수
void enqueue(QueueType* q, int id, int i, int bol, char str[])
{
	if (is_full(q))
		fprintf(stdout, "큐가 포화상태입니다");
	else
	{
		q->rear = (q->rear + 1) % MAX;
		q->data[q->rear].pen_id = id;
		q->data[q->rear].pen_num = i;
		q->data[q->rear].confirm = bol;
		strcpy(q->data[q->rear].error_color, str);
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
		q->data[q->front];
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

int main()
{
	FILE* fp; // 1. 파일 포인터 생성
	FILE* sumfp;
	FILE* errorfp;

	QueueType q;
	sum total[DAY] = { 0,0,0,0,0,0,0,0,0 };
	int id;
	srand(time(NULL));
	const int error_percent = 5; // 5%의 불량률


	fp = fopen("report.txt", "wt+");   // 2. 데이터를 누적시키고, +기능으로 read&write 기능을 함.
	sumfp = fopen("sumation.txt", "wt+");
	errorfp = fopen("error.txt", "wt+");

	for (int k = 0; k < DAY; k++)
	{
		init_queue(&q);              // 큐 초기화
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
					enqueue(&q, id, i, 0, "red");
					total[k].error_red_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "");

			}

			if (id % 10 == 1)
			{
				total[k].blue_cnt++;
				if (rand() % 20 == 0)         //불량률 계산
				{
					enqueue(&q, id, i, 0, "blud");

					total[k].error_blue_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "blud");

			}

			if ((id % 10 >= 2) && (id % 10 <= 9))
			{
				total[k].black_cnt++;
				if (rand() % 20 == 0)         //불량률 계산
				{
					enqueue(&q, id, i, 0, "black");
					total[k].error_black_cnt++;
				}
				else
					enqueue(&q, id, i, 1, "black");
			}
		}
		queue_print(&q, fp);
		total[k].total_cnt = total[k].black_cnt + total[k].red_cnt + total[k].blue_cnt;
		total[k].error_cnt = total[k].error_black_cnt + total[k].error_red_cnt + total[k].error_blue_cnt;
		fprintf(stdout,"%d일 볼펜 생산량\n", total[k].days);
		fprintf(sumfp, "%d일 볼펜 생산량\n", total[k].days);

		fprintf(stdout, "\\n총생산볼펜 %d=> 검%d, 빨%d, 파%d \n\n", total[k].total_cnt, total[k].black_cnt, total[k].red_cnt, total[k].blue_cnt);          // 4. fpritf()함수로 '모니터'와 '파일'에 동시 출력
		fprintf(sumfp, "\n총생산볼펜 %d=> 검%d, 빨%d, 파%d \n\n", total[k].total_cnt, total[k].black_cnt, total[k].red_cnt, total[k].blue_cnt);

		fprintf(stdout, "%d일 볼펜 불량 생산량\n", total[k].days);
		fprintf(errorfp, "%d일 볼펜 불량 생산량\n", total[k].days);

		fprintf(stdout, "불량률%d%%\n\n", error_percent);
		fprintf(errorfp, "불량률%d%%\n\n", error_percent);

		fprintf(stdout, "불량볼펜 개수 %d=> 검%d, 빨%d, 파%d\n\n", total[k].error_cnt, total[k].error_black_cnt, total[k].error_red_cnt, total[k].error_blue_cnt);
		fprintf(errorfp, "불량볼펜 개수 %d=> 검%d, 빨%d, 파%d\n\n", total[k].error_cnt, total[k].error_black_cnt, total[k].error_red_cnt, total[k].error_blue_cnt);

		fprintf(stdout, "불량 볼펜 상세정보 : \n");
		fprintf(errorfp, "불량 볼펜 상세정보 : \n");

		for (int i = 0; i < MAX; i++)
		{
			if (q.data[i].confirm == 0)
			{
				fprintf(stdout, "생산번호 : %d, 색 : %7s, 고유번호 : %d\n", q.data[i].pen_num, q.data[i].error_color, q.data[i].pen_id);
				fprintf(errorfp, "생산번호 : %d, 색 : %7s, 고유번호 : %d\n", q.data[i].pen_num, q.data[i].error_color, q.data[i].pen_id);
			}
		}
		fprintf(errorfp, "----------------------------------\n\n");
	}




	fclose(fp);
	fclose(sumfp);
	fclose(errorfp);


	system("notepad.exe report.txt");  // 자동으로 메모장을 오픈


	return 0;
}