#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int element;
typedef struct DListNode {	// ���߿��� ��� Ÿ��
	element data;				// ������ ����
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
	for (p = phead->rlink; p != phead; p = p->rlink) {
	// head�� ���� ��ũ���� head�� �ɶ����� ���� ��ũ�� ��� �̵�
		printf("<-| |%d| |-> ", p->data);
	}	// ����� ������ ���
	printf("\n");
}
// ���ο� �����͸� ��� before�� �����ʿ� �����Ѵ�.
void dinsert(DListNode *before, element data)
{	// ���ο� ��� �����ϴ� �Լ�
	DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
	// ���ο� ��带 ���� �Ҵ����� ����
	//strcpy(newnode->data, data);
	newnode->data = data;		// ������ ����
	newnode->llink = before;	// ��������� ��ũ�� ���� ��ũ�� ����
	newnode->rlink = before->rlink;	// ���� ����� ��ũ�� ���� ��ũ�� ���� ��ũ�� �޾ƿ�
	before->rlink->llink = newnode;	// ���� ����� ������� ��ũ�� ���ο� ��帵ũ ����
	before->rlink = newnode;		// ���� ����� ������ũ �κп� ���ο� ��� ����
}
// ��� removed�� �����Ѵ�.  
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;		// ������ ��尡 head�� �Լ� ����
	removed->llink->rlink = removed->rlink;
	// ������ ����� ���� ����� ���� ��帵ũ �κп� ������ ����� ���� ��帵ũ�� ����
	removed->rlink->llink = removed->llink;
	// ������ ����� ���� ����� ������帵ũ�� ������ ����� ���� ��� ��ũ ����
	free(removed);
	// ������ ��带 free()�� ���� ���� �Ҵ� ����
}

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	DListNode* head = (DListNode *)malloc(sizeof(DListNode));
	// head ��� ���� ����
	init(head);		// head �ʱ�ȭ
	printf("�߰� �ܰ�\n");
	for (int i = 0; i < 5; i++) {
		// ��� ����� �����ʿ� ����
		dinsert(head, i);
		// �ݺ��� Ƚ����ŭ �����Ϳ� �� ����
		print_dlist(head);
		// ����Ʈ ���
	}
	printf("\n���� �ܰ�\n");
	for (int i = 0; i < 5; i++) {
		// �����ߴ� Ƚ����ŭ ��� ����
		print_dlist(head);
		// ����Ʈ ���
		ddelete(head, head->rlink);
		// head�� ���� ��� ����
	}
	free(head);
		// ���� �Ҵ�� head ����
	return 0;
}