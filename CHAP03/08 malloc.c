// MALLOC.C: malloc을 이용하여 정수 10를 저장할 수 있는 동적 메모리를 
// 할당하고 free를 이용하여 메모리를 반납한다. 
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define SIZE 10

int main(void)
{
	int *p;

	p = (int *)malloc(SIZE * sizeof(int));
	if (p == NULL) {
		fprintf(stderr, "메모리가 부족해서 할당할 수 없습니다.\n");
		exit(1);
	}

	for (int i = 0; i<SIZE; i++)
		p[i] = i;

	for (int i = 0; i<SIZE; i++)
		printf("%d ", p[i]);

	free(p);
	return 0;
}