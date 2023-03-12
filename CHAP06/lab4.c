#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode { 	// ��� Ÿ��
	element data;			// ��忡 �����͸� ������ �κ�
	struct ListNode *link;	// ���� ��Ʈ�� ��ũ�� ������ �κ�
} ListNode;					// ListNode ����ü�� ����

ListNode* insert_first(ListNode* head, element value)		// ���Ḯ��Ʈ�� ù ���� ��忡 �����ϴ� �Լ�
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));		//(1) ��� ���� (���� ����)
	p->data = value;										//(2)	�Է��� ��(value)�� ����� �����Ϳ� ����
	p->link = head;											//(3)��� �������� ���� ����	head�� ������ �ִ� �ּҰ��� ��ũ�� �����Ͽ�
															//		ù ��° ��忡 ��ġ�ϵ��� ��
	head = p;												//(4)��� ������ ����		// head�� ������ ����� �ּҸ� �����ϵ��� ��
	return head;											// head �ּҰ� ����
}

// ��� pre �ڿ� ���ο� ��� ����
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)  MAX�� ����
	p->data = value;		//(2)
	p->link = pre->link;	//(3)	
	pre->link = p;		//(4)	
	return head;		//(5)	
}

void print_list(ListNode* head)							// ����� �����͸� ����ϴ� �Լ�
{
	for (ListNode* p = head; p != NULL; p = p->link)	// ����� ��ũ�� NULL�� �ƴϸ� ��� �ݺ�
														// NULL�� ���� ������ �ݺ�
		printf("%d->", p->data);						// ����� ������ ���
	printf("NULL \n");									// �ݺ����� ������ NULL���
}
ListNode* reverse(ListNode *head)	// ����Ʈ�� �������� ����� �Լ�
{
									// ��ȸ �����ͷ� p, q, r�� ���
	ListNode *p, *q, *r;

	p = head;					   // p�� �������� ���� ����Ʈ
	q = NULL;					  // q�� �������� ���� ���
	while (p != NULL) {				// p�� ����Ʈ�� ���(������� ���� ���)
		r = q;          // r�� �������� �� ����Ʈ.    
						// r�� q, q�� p�� ���ʷ� ���󰣴�.
		q = p;
		p = p->link;
		q->link = r;      // q�� ��ũ ������ �ٲ۴�.
	}
	return q;
}
// �׽�Ʈ ���α׷�
int main(void)
{
	ListNode* head1 = NULL;			// ����Ʈ1 ����
	ListNode* head2 = NULL;			// ����Ʈ2 ����

	//head1 = insert_first(head1, 10);// ����Ʈ1 �� �տ� 10 ����
	//head1 = insert_first(head1, 20);// ����Ʈ1 �� �տ� 20 ����
	//head1 = insert_first(head1, 30);// ����Ʈ1 �� �տ� 30 ����
	//print_list(head1);				// ����Ʈ1 ���

	head1 = insert(head1, 0, 10);
	head1 = insert(head1, 0, 20);
	head1 = insert(head1, 0, 30);
	print_list(head1);

	head2 = reverse(head1);			// ����Ʈ2�� ����Ʈ1�� ����
	print_list(head2);				// ����Ʈ2 ���
	return 0;
}
