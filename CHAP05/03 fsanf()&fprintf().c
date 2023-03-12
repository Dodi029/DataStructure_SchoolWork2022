#define _CRT_SECURE_NO_WARNINGS  //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시
//#pragma warning(disable:4996)  //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

struct SaleData
{
	int  no; // 순번
	char address[100]; // 주소
	double  total; // 판매량
};		// 구조체 선언 => 필드 생성가능

void main() 
{
	FILE *stream; // 파일 스트림 생성
	struct SaleData sale[3]; // 구조체
	int i = 0;

	stream = fopen("report1.txt", "r");// read 모드로 파일 읽기

	// 파일 내용의 끝에 도달할 때까지 반복문 수행
	while(!feof(stream))		// feof = 파일의 끝 ==>!feof = 파일의 끝이 아니면
	{
		// 내용을 읽어들여서 구조체 요소에 저장
		fscanf(stream,"%d %s %lf\n", &sale[i].no, sale[i].address, &sale[i].total);
		fprintf(stdout,"sale[%d] = %d %s %lf\n", i, sale[i].no, sale[i].address, sale[i].total);
		i++;
	}
	printf("\n");
	fclose(stream); // 파일 스트림 닫기
}

 

// 아래는 10000개의 데이터를 파일에 write하고,
// 해당 파일을 읽어들여 소요시간을 계산하는 소스코드입니다.
// 오류가 나는 코드를 붙여넣었습니다. 이를 해결해보세요.

//#include <stdio.h> 
//#include <stdlib.h>
//#include <time.h>
//#define MAX_SIZE 10000
//void InsertData(char *);
//
//struct SaleData
//{
// int no; // 순번
// int address; // 주소
// int sale; // 판매량
//};
//
//void main() 
//{
// FILE *stream; // 파일 스트림 생성, write_stream, read_stream
// clock_t start, end;
//
// struct SaleData sale[MAX_SIZE]; // 구조체
//
// int i = 0;
// char *fname = "report2.txt";
//
// InsertData(fname); // 파일 데이터 입력하기
//
// stream = fopen(fname, "r"); // read 모드로 파일 열기
// start = clock(); // 시작 시간 계산
//
// // 파일 내용의 끝에 도달할 때까지 반복문 수행
// while(!feof(stream))
// {
//  // 내용을 읽어들여서 구조체 요소에 저장
//  fscanf(stream, "\\n address : %d sale[%d]= %d", &sale[i].address, &sale[i].no, &sale[i].sale);
//  printf("sale[%d] = %d\\n", sale[i].no, sale[i].sale);
//  i++;
// }
//
// end  = clock(); // 종료 시간 계산
// printf("\\n");
//
// fclose(stream); // 파일 스트림 닫기
//
// printf("소요 시간 : %.2lf초\\n", (double)(end-start) / CLOCKS_PER_SEC); // 초 단위 계산
// system(fname);
//}
//
//// 파일 데이터 입력하기
//void InsertData(char *fname)
//{
// FILE *stream;
// int sale[MAX_SIZE];
// int i, j;
//
// stream = fopen(fname, "w"); // write 모드로 파일 열기
//
// srand((unsigned)time(NULL));
//
// for(i=0; i<MAX_SIZE; i++)
//  sale[i] = rand() % 500 + 1; // 배열에 랜덤값 생성(1~500)
//
// for(j=0; j<sizeof(sale)/sizeof(int); j++)
// {
//  fprintf(stream, "\\n address : %u sale[%d]= %d", &sale[j], j, sale[j]); // 데이터 넣기
// }
//
// fclose(stream);
//}