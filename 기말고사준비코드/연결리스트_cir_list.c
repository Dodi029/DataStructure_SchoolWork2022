#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{ 	// ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

// ����Ʈ�� �׸� ���
void print_list(ListNode* head)
{
	ListNode* p;		// ��� ������

	if (head == NULL) return;		// head�� ��������� �Լ� ����
	p = head->link;			// head�� ��ũ�� ù��° ���� �̵�
	do {		// �ݺ���
		printf("%d->", p->data);		// ����� ������ ���
		p = p->link;			// ���� ���� ��ġ �̵�
	} while (p != head);		// �ݺ��� ���� ����
	printf("%d->", p->data); // ������ ��� ���
}

ListNode* insert_first(ListNode* head, element data)
{			// ����Ʈ ù��°�� ��� ����
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	// ��� ���� �Ҵ����� ����
	node->data = data;		// �Էµ� ������ ����
	if (head == NULL) {		// head�� ���������
		head = node;		// head�� ������ ��� ����
		node->link = head;		// ����� ��ũ�� head�� �����ϸ� ��������Ʈ ����
	}
	else {		// head�� ������� ���� ���
		node->link = head->link;	// (1) ������ ����� ��ũ�� head�� ��ũ ����
		head->link = node;		// (2)	head�� ��ũ�� ��带 �����ϸ� ��������Ʈ ����
	}
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
}

ListNode* insert_last(ListNode* head, element data)
{		// ����Ʈ �������� ��� ����
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	// ��� ���� �Ҵ����� ����
	node->data = data;		// ��忡 �Էµ� ������ ����
	if (head == NULL) {		// head�� ���������
		head = node;		// head�� ��� ����
		node->link = head;		// ����� ��ũ�� head�� �����Ͽ� ��������Ʈ ����
	}
	else {		// head�� ������� ���� ���
		node->link = head->link;	// (1)	����� ��ũ�� head�� ��ũ ����
		head->link = node;		// (2)	head�� ��ũ�� ��� ����
		head = node;		// (3)	head�� ��带 �����Ͽ� ��������Ʈ ����
	}
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
}
// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	ListNode* head = NULL;
	// ��� �ʱ�ȭ
	// list = 10->20->30->40
	head = insert_last(head, 20);	// ��������Ʈ �������� 20����
	head = insert_last(head, 30);	// ��������Ʈ �������� 30����
	head = insert_last(head, 40);	// ��������Ʈ �������� 40����
	head = insert_first(head, 10);	// ��������Ʈ ó���� 10����
	print_list(head);		// ��������Ʈ ���
	return 0;		// ����
}