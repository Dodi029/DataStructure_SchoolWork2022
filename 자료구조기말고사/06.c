#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int element;
typedef struct DListNode {	// ���߿��� ��� Ÿ��
	char name[1024];				// ����
	char time[1024];
	char like[1024];
	struct DListNode* llink;	// ���� ��ũ ����
	struct DListNode* rlink;	// ���� ��ũ ����
} DListNode;					// ����ü ����

// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DListNode* phead)
{
	phead->llink = phead;	// head�� ���� ��ũ�� head�� �ǵ��� �ʱ�ȭ
	phead->rlink = phead;	// head�� ��� ��ũ�� head�� �ǵ��� �ʱ�ȭ
}

// ���� ���� ����Ʈ�� ��带 ���
void print_dlist(DListNode* phead)
{
	DListNode* p;			// ����ü ������ ����
	FILE* fp = fopen("06.txt", "w");
	for (p = phead->rlink; p != phead; p = p->rlink) {
		// head�� ���� ��ũ���� head�� �ɶ����� ���� ��ũ�� ��� �̵�
		fprintf(fp, "%s\t%s\t%s\n", p->name, p->time,p->like);
	}	// ����� ������ ���
	fclose(fp);
}
// ���ο� �����͸� ��� before�� �����ʿ� �����Ѵ�.
void dinsert(DListNode* before, char* name, char* time, char* like)
{	// ���ο� ��� �����ϴ� �Լ�
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	// ���ο� ��带 ���� �Ҵ����� ����
	//strcpy(newnode->data, data);
	strcpy(newnode->name, name);
	strcpy(newnode->time, time);
	strcpy(newnode->like, like);
	newnode->llink = before;	// ��������� ��ũ�� ���� ��ũ�� ����
	newnode->rlink = before->rlink;	// ���� ����� ��ũ�� ���� ��ũ�� ���� ��ũ�� �޾ƿ�
	before->rlink->llink = newnode;	// ���� ����� ������� ��ũ�� ���ο� ��帵ũ ����
	before->rlink = newnode;		// ���� ����� ������ũ �κп� ���ο� ��� ����
}
void bubbleSortNode(DListNode* head) {
	DListNode* p, * q;
	for (p = head->rlink; p != head; p = p->rlink)
	{
		for (q = head->rlink; q->rlink != head; q = q->rlink)
			if (strcmp(q->name, q->rlink->name) == 1)
			{
				char tmp;
				tmp = q->name;
				q->name = q->rlink->name;
				q->rlink->name = tmp;
			}
	}
}

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	// head ��� ���� ����
	init(head);		// head �ʱ�ȭ
	bubbleSortNode(head);

	dinsert(head, "Bohemian Rhapsody", "05��57��", "1,109,566");
	dinsert(head, "I was born to love you", "04��50��", "1,112,154");
	dinsert(head, "Love of my life", "03��38��", "1,060,154");
	dinsert(head, "Radio Ga Ga", "05��48��", "1,022,562");
	dinsert(head, "We will Rock you", "03��08��", "1,010,666");

	//char al[1024] = "Dynamite";

	for (DListNode* k = head; k != NULL; k = k->rlink) {
		if (strcmp(k->name, "Dynamite") == -1) {
			//k = k->llink;
			dinsert(k->llink, "Dynamite", "03��40��", "10,040,154");
		}
	}
	print_dlist(head);
	
	free(head);

	system("notepad.exe 06.txt");
	// ���� �Ҵ�� head ����
	return 0;
}