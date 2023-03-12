#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode { 	// ��� Ÿ��
	element data;			// ��忡 �����͸� ������ �κ�
	struct ListNode* link;	// ���� ��Ʈ�� ��ũ�� ������ �κ�
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
	if (pre == NULL) {
		p->data = value;		// ����� data �κп� �� ����
		p->link = head;		// ��� �������� ���� ����(3)
		head = p;		// ��� ������ ����
	}
	else {
		p->data = value;		// ����� daTa �κп� �� ����
		p->link = pre->link;	// ���� ��帵ũ ����
		pre->link = p;		// ���� ��� ��ũ ����
	}	
	return head;		//(5)	
}

void print_list(ListNode* head)							// ����� �����͸� ����ϴ� �Լ�
{
	for (ListNode* p = head; p != NULL; p = p->link)	// ����� ��ũ�� NULL�� �ƴϸ� ��� �ݺ�
														// NULL�� ���� ������ �ݺ�
		printf("%d->", p->data);						// ����� ������ ���
	printf("NULL \n");									// �ݺ����� ������ NULL���
}
ListNode* reverse(ListNode* head)	// ����Ʈ�� �������� ����� �Լ�
{
	// ��ȸ �����ͷ� p, q, r�� ���
	ListNode* p, * q, * r;

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

	int a1, a2, a3;

	//head1 = insert_first(head1, 10);// ����Ʈ1 �� �տ� 10 ����
	//head1 = insert_first(head1, 20);// ����Ʈ1 �� �տ� 20 ����
	//head1 = insert_first(head1, 30);// ����Ʈ1 �� �տ� 30 ����
	//print_list(head1);				// ����Ʈ1 ���

	printf("ù ��° ��忡 ��ġ�� ������ �Է��ϼ��� : ");
	// ����ڷκ��� ���ϴ� ���� �Է¹���
	scanf("%d", &a1);
	// �Է¹��� �� ����
	printf("�� ��° ��忡 ��ġ�� ������ �Է��ϼ��� : ");
	// ����ڷκ��� ���ϴ� ���� �Է¹���
	scanf("%d", &a2);
	// �Է¹��� �� ����
	printf("�� ��° ��忡 ��ġ�� ������ �Է��ϼ��� : ");
	// ����ڷκ��� ���ϴ� ���� �Է¹���
	scanf("%d", &a3);
	// �Է¹��� �� ����

	head1 = insert(head1, 0, a2);				// �� ��° ��忡 a2�� ����� �� ����
	head1 = insert(head1, head1->link, a1);		// ù ��° ��忡 a1�� ����� �� ����
	head1 = insert(head1, head1->link, a3);		// �� ��° ��忡 a3�� ����� �� ����
	print_list(head1);				// ����� ����Ʈ ���

	head2 = reverse(head1);			// ����Ʈ2�� ����Ʈ1�� ����
	print_list(head2);				// ����Ʈ2 ���
	return 0;
}
