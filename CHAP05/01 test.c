#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* p; // 파일 포인터 생성
	int a;
	char b[40];
	double c;
	
	p = fopen("report.txt", "r"); // 1. 기존 파일이 존재하면, read 모드로 파일 읽기 
	
	if (p == NULL)
		printf("파일오픈 에러\n");

	fscanf(p,"%d %s %lf",&a,b,&c);		// p 대신 stdin을 쓰면 키보드로부터 값을 입력받음  p를 쓰면 파일로 부터 테이터를 읽어옴
	printf("%d %s %lf",a,b,c);			// fprintf(stdout, "%d %s %lf". a b c)를 쓰면 기본출력=화면으로 출력함
	fclose(p);

	system("notepad.exe report.txt");
	//system("notepad.exe D:\\report1.txt"); => 절대 경로를 지정하는 경우(D드라이브에 위치함)

	return 0;
	
	
}
