#include <stdio.h>
#include<stdlib.h>
#define MAX 3

void hanoi_tower(int n, char from, char tmp, char to);

int main(void)
{
	hanoi_tower(MAX, 'A', 'B', 'C');
	// FILE* p;  = 파일 포인터(p는 4바이트짜리 포인터 변수)
	// p = fopen("02.txt", "w"); 파일을 여는 함수(파일을 만들지 않았기 떄문에 새로운 파일(02.txt)파일 생성
	// ... 파일 작성
	// fclose(p);	c언어 파일 입출력 부분을 보고 다시 공부하기
	// fputs(), fgets() 함수 필요
	system("notepad.exe 08 recursion_hanoi.c"); // 텍스트 파일로 열어볼 수 있음
	return 0;
}

void hanoi_tower(int n, char from, char tmp, char to)
{
	if( n==1 ) printf("원판 1을 %c 에서 %c으로 옮긴다.\n",from,to);	// 파일에 저장하기 위해서는 fprintf로 작성해야함
																	// 이렇게 하는게 과제 개선의 숙제
	else {
		hanoi_tower(n-1, from, to, tmp);
		printf("원판 %d을 %c에서 %c으로 옮긴다.\n",n,from,to);
		hanoi_tower(n-1, tmp, from, to);
	}
}