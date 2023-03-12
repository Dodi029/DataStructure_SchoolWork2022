
#define _CRT_SECURE_NO_WARNINGS  //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int Factorial(int n);
int i=0;             // 전역변수 i가 무엇을 의미할까? 생각해보기... 

int main(void)
{
	clock_t start, finish;
	double duration;
	int num, result;
	
	FILE* fp; // 4바이트 파일포인터 선언...4바이트로 파일의 내용을 참조하는 변수...파일입출력 공부할 것


	while (1)
	{
		i++;
		fprintf(stdout, "팩토리얼 입력(양수): ");  // (stdout의 의미: '모니터에 출력하라'는 뜻), 같은의미 코드: printf("팩토리얼 입력: ");
		fscanf(stdin,"%d",&num);             // (stdin의 의미: '키보드'로 입력받자'는 뜻), 같은의미 코드: scanf("%d",&num);
		// scanf라 stdin을 작성해야함
		
		if (num < 0)
			printf("양수를 입력하세요.\n"); break;		//*****************************8 break를 이동시켜야 코드가 돌아감
														// break는 2줄
					// 
		// {
			// printf("양수를 입력하세요.\n"); break;
			// break'
		// }					로 작성하기
		// 
		
		
		start = clock();                    // 시간측정 시작
			

		///////////////////////////////////////////////////////////////////////////////////////////////////////
		fp = fopen("report.txt", "at+");  // 파일을 만들어 오픈, 현재 프로젝트 폴더에 생성...기존 내용을 누적(append), 텍스트(t) => 누적 및 읽기도 가능하게 함
		result = Factorial(num);          // 팩토리얼 수행시간
		finish = clock();                 // 시간측정 완료
			
		duration = (double)(finish - start) / CLOCKS_PER_SEC; 
		
		fprintf(fp,"%03d--%d!=%d --> 수행시간 %lf초 \n", i, num, result, duration);    // 파일(fp)에 데이터를 출력
		// ********03d => "3칸을 채워라" 나머지는 0으로 채우라는 뜻
		fprintf(stdout,"%03d--%d!=%d --> 수행시간 %lf초 \n",i, num, result, duration);  // 모니터(stdout)에 데이터를 출력
		fclose(fp);                      // 파일 닫음
		///////////////////////////////////////////////////////////////////////////////////////////////////////
	 }
	    //fprintf(fp,"-----------------------------------------------\n");    // 파일(fp)에 데이터를 출력
	    system("notepad.exe report.txt");  // 자동으로 메모장을 오픈
		system("cmd");                     // 메모장이 저장된 경로
		// 메모장을 닫으면 cmd창으 뜨도록 하는 코드
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 팩토리얼 함수
  1. 입          력: int n 
  2. 처리(알고리즘): 입력이 0이면 1을, 입력이 0이 아니면 재귀함수 호출
  3. 출          력: int 값 반환
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Factorial(int n)  
{
	if (n == 0)
		return 1;
	else
		return n * Factorial(n - 1);
}