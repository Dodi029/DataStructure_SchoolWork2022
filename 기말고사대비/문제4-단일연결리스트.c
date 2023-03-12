#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;
typedef struct ListNode { 	// 노드 타입
	int Rnum;
	char Snum[1024];
	char name[20];
	float score;
	int rank;
	struct ListNode* link;
} ListNode;

// 오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
ListNode* insert_first(ListNode* head, int Rnum, char* Snum, char* name, float score)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)	// 동적메모리 할당을 하는 코드
			
	p->Rnum = Rnum;
	strcpy(p->Snum, Snum);
	strcpy(p->name, name);
	p->score = score;
	p->link = head;	
	head = p;
		
	return head;
}

ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;	// (1)
	head = removed->link;	// (2)
	free(removed);		// (3)
	return head;		// (4)
}

void print_list(ListNode* head)
{
	FILE* fp;
	fp = fopen("04.txt", "w");
	fprintf(fp, "레코드 번호\t학번\t\t이름\t학점\t등수\n");
	for (ListNode* p = head; p != NULL; p = p->link)
		fprintf(fp, "%d\t\t%s\t%s\t%.2lf\t%d\n", p->Rnum, p->Snum, p->name, p->score,p->rank);
	printf("NULL \n");
	fclose(fp);
}

void insert_rank(ListNode* head) {
	for (ListNode* s = head; s != NULL; s = s->link) {
		s->rank = 1;
		for (ListNode* p = head->link; p != NULL; p = p->link) {
			if (s->score < p->score)
				s->rank++;
		}
	}
}

// 테스트 프로그램
int main(void)									// 단일 연결 리스트
{
	ListNode* head = NULL;						// head는 무조건 4바이트

	head = insert_first(head, 5, "2020132022", "bjm", 4.25);
	head = insert_first(head, 4, "2020132033", "yjm", 4.2);
	head = insert_first(head, 3, "2020132044", "ajm", 4.3);
	head = insert_first(head, 2, "2020131011", "sjm", 3.99);
	head = insert_first(head, 1, "2020131055", "ojm", 3.82);

	// setRank(head);
	insert_rank(head);
	print_list(head);

	char NUM[1024];

	while (1) {
		printf("학번을 입력하세요 : ");
		scanf("%s", NUM);

		if (strcmp(NUM,"q") == 0) {
			return 0;
		}
		for (ListNode* k = head; k != NULL; k = k->link) {
			if (strcmp(NUM, k->Snum) == 0) {
				printf("학점 : %.2lf\t 등수 : %d\n", k->score, k->rank);

			}
		}
	}

	system("notepad.exe 04.txt");

	return 0;
}