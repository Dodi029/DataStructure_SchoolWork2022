#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// ��� Ÿ��
	element data;
	struct ListNode *link;
} ListNode;

// ���� ó�� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
ListNode* insert_first(ListNode *head, int value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));	//(1)	// �����޸� �Ҵ��� �ϴ� �ڵ�
			// &p2�� ����� �ڵ�
	p->data = value;					// (2)
			// &p2�� 1�� ����
	p->link = head;	// ��� �������� ���� ����	//(3)
			// &p1�� &p2->link�� ����
	head = p;	// ��� ������ ����		//(4)
			// head = &p2�� ����
			// main�� �ִ� head�� �ٸ� head
	return head;	// ����� ��� ������ ��ȯ
}

// ��� pre �ڿ� ���ο� ��� ����
ListNode*  insert(ListNode *head, ListNode *pre, element value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));	//(1)  MAX�� ����
	p->data = value;		//(2)
	p->link = pre->link;	//(3)	
	pre->link = p;		//(4)	
	return head;		//(5)	
}

ListNode* delete_first(ListNode *head)
{
	ListNode *removed;
	if (head == NULL) return NULL;
	removed = head;	// (1)
	head = removed->link;	// (2)
	free(removed);		// (3)
	return head;		// (4)
}
// pre�� ����Ű�� ����� ���� ��带 �����Ѵ�. 
ListNode* delete(ListNode *head, ListNode *pre)
{
	ListNode *removed;
	removed = pre->link;
	pre->link = removed->link;		// (2)
	free(removed);			// (3)
	return head;			// (4)
}

void print_list(ListNode *head)
{
	for (ListNode *p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}

// �׽�Ʈ ���α׷�
int main(void)									// ���� ���� ����Ʈ
{
	ListNode *head = NULL;						// head�� ������ 4����Ʈ

	for (int i = 0; i < 5; i++) {
		head = insert_first(head, i);			// insert_firsts MAX������ ����	(���� �޸� �Ҵ� ���)
							// head �� main�� �ִ� head
		print_list(head);
	}
	for (int i = 0; i < 5; i++) {
		head = delete_first(head);
		print_list(head);
	}
	return 0;
}