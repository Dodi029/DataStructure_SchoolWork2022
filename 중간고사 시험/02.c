#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 10

typedef struct {
	char name[10];
	int num;
	double score[MAX];
} student;

int main() {
	FILE* p = fopen("02.txt", "at+");
	int data[MAX];
	double data2[MAX];
	student* t;

	double rdata[20]; //실수 난수를 저장할 배열공간
	float fsum = 0.0;

	srand(time(NULL));//랜덤한 숫자
	// t->score[0] = 0;
	for (int i = 0; i < MAX; i++) {
		rdata[i] = rand() % 5 + rand() % 10 / 10;//00.00~99.99 난수구하기
		data2[i] = rdata[i];
	}
	student A = { "kim01", 20220401, data2[0] };
	student B = { "Lee01", 20220402, data2[1] };
	student C = { "Park01", 20220403, data2[2] };
	student D = { "Kim02", 20220404, data2[3] };
	student E = { "Lee02", 20220405, data2[4] };
	student F = { "Park02", 20220406, data2[5] };
	student G = { "Kim03", 20220407, data2[6] };
	student H = { "lee03", 20220408, data2[7] };
	student I = { "Park03", 20220409, data2[8] };
	student J = { "Kim04", 20220410, data2[9] };

	fprintf(p, "%s %d %f\n", A.name, A.num, A.score[0]);
	fprintf(p, "%s %d %f\n", B.name, B.num, B.score[1]);
	fprintf(p, "%s %d %f\n", C.name, C.num, C.score[2]);
	fprintf(p, "%s %d %f\n", D.name, D.num, D.score[3]);
	fprintf(p, "%s %d %f\n", E.name, E.num, E.score[4]);
	fprintf(p, "%s %d %f\n", F.name, F.num, F.score[5]);
	fprintf(p, "%s %d %f\n", G.name, G.num, G.score[6]);
	fprintf(p, "%s %d %f\n", H.name, H.num, H.score[7]);
	fprintf(p, "%s %d %f\n", I.name, I.num, I.score[8]);
	fprintf(p, "%s %d %f\n", J.name, J.num, J.score[9]);

	fclose(p);
	system("notepad.exe 02.txt");
}