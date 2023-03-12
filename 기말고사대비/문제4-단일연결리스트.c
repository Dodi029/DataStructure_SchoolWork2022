#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;
typedef struct ListNode { 	// ��� Ÿ��
	int Rnum;
	char Snum[1024];
	char name[20];
	float score;
	int rank;
	struct ListNode* link;
} ListNode;

// ���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
ListNode* insert_first(ListNode* head, int Rnum, char* Snum, char* name, float score)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)	// �����޸� �Ҵ��� �ϴ� �ڵ�
			
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
	fprintf(fp, "���ڵ� ��ȣ\t�й�\t\t�̸�\t����\t���\n");
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

// �׽�Ʈ ���α׷�
int main(void)									// ���� ���� ����Ʈ
{
	ListNode* head = NULL;						// head�� ������ 4����Ʈ

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
		printf("�й��� �Է��ϼ��� : ");
		scanf("%s", NUM);

		if (strcmp(NUM,"q") == 0) {
			return 0;
		}
		for (ListNode* k = head; k != NULL; k = k->link) {
			if (strcmp(NUM, k->Snum) == 0) {
				printf("���� : %.2lf\t ��� : %d\n", k->score, k->rank);

			}
		}
	}

	system("notepad.exe 04.txt");

	return 0;
}