#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(NULL));
	int ary[3];
	int a;
	for (int i = 0; i < 3; i++) {
		a = 65 + rand() % 26;
		ary[i] = a;
	}
	for (int i = 0; i < 3; i++) {
		printf("%c", ary[i]);
	}
	printf("\n");

	float score;
	score = (float)(rand() % 45) / 10;
	printf("%.2lf", score);

	return 0;
}