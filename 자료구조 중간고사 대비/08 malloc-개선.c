// 사용자에게 정수를 몇 개 입력할지 물어보고 그 수만큼 메모리 생성하기
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(void)
{
	int count, sum = 0;		// 입력할 정수의 개수, 그 합을 저장할 변수
	int* p;			// 포인터 변수

	printf("정수를 몇 개 입력하시겠습니까>> ");
	scanf("%d", &count);		// 입력할 정수의 개수를 물어보고 그 수를 count에 저장

	p = (int*)malloc(count * sizeof(int));			// 동적 메모리할당
	if (p == NULL) {								// count만큼 메모리 생성
		fprintf(stderr, "메모리가 부족해서 할당할 수 없습니다.\n");
		exit(1);
	}

	for (int i = 0; i < count; i++) {		// 메모리 수 만큼 정수를 입력받음
		printf("%d번째 수 : ", i + 1);
		scanf("%d", p + i);			// 입력받은 수를 저장함
	}

	printf("\n입력한 값 확인\n");			// 지금까지 입력한 수를 보여줌
	for (int i = 0; i < count; i++) {
		printf("%d, ", *(p + i));

		sum = sum + *(p + i);			// 입력한 수를 모두 더함
	}
	printf("\n총 합은 : %d", sum);

	free(p);
	return 0;
}