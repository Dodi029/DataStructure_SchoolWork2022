#define _CRT_SECURE_NO_WARNINGS  //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시
//#pragma warning(disable:4996)  //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시

#include <stdio.h>
#include <stdlib.h>

//void main()
//{
//	char  szCommand1[512] = {0};
//	
//	printf("Input command: ");
//	gets(szCommand1);
//	system(szCommand1);
//	
//	// system("notepad.exe report.txt");
//	// system("notepad.exe D:\\report.txt");
//}

void main()
{
	char  szCommand1[512] = "notepad.exe report.txt";
	char* szCommand2 = szCommand1;
	system(szCommand2);
	
	// 파일의 이름을 scanf로 입력받아서 파일을 지정할 수 있도록 하는 코드 -> scanf로 받게 하기 위함

	// system("notepad.exe report.txt");
	// system("notepad.exe D:\\report.txt");
}