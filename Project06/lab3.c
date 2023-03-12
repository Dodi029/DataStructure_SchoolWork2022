#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode { 		// ��� Ÿ��
	element data;				// ��忡 �����͸� ������ �κ�
	struct ListNode *link;		// ���� ��Ʈ�� ��ũ�� ������ �κ�
} ListNode;						// ListNode ����ü�� ����


ListNode* insert_first(ListNode *head, element value)	// ���Ḯ��Ʈ�� ù ���� ��忡 �����ϴ� �Լ�
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));	//(1) ��� ���� (���� ����)
	p->data = value;									//(2)	�Է��� ��(value)�� ����� �����Ϳ� ����
	p->link = head;										//(3)��� �������� ���� ����	head�� ������ �ִ� �ּҰ��� ��ũ�� �����Ͽ�
														//		ù ��° ��忡 ��ġ�ϵ��� ��
	head = p;											//(4)��� ������ ����		// head�� ������ ����� �ּҸ� �����ϵ��� ��
	return head;										// head �ּҰ� ����
}

void print_list(ListNode *head)							// ����� �����͸� ����ϴ� �Լ�
{
	for (ListNode *p = head; p != NULL; p = p->link)	// ����� ��ũ�� NULL�� �ƴϸ� ��� �ݺ�
														// NULL�� ���� ������ �ݺ�
		printf("%d->", p->data);						// ����� ������ ���
	printf("NULL \n");									// �ݺ����� ������ NULL���
}
ListNode* concat_list(ListNode *head1, ListNode *head2)	// �� ����Ʈ�� ��ġ�� �Լ�
{
	if (head1 == NULL) return head2;					// ����Ʈ1�� ������ ����Ʈ2 ����
	else if (head2 == NULL) return head1;				// ����Ʈ2�� ������ ����Ʈ1 ����
	else {												// �Ѵ� �ƴѰ�� (����Ʈ1, 2�� ���� ���)
		ListNode *p;						
		p = head1;										// ����Ʈ1�� head�� ���� �ּҰ��� p�� ����
		while (p->link != NULL)							// ����Ʈ1���� ��ũ�� NULL�� ���� ������
			p = p->link;								// ��� �̵�
		p->link = head2;								// ����Ʈ1���� ��ũ�� NULL�� ��� ��ũ�� ����Ʈ2 head�� ����
		return head1;									// ����Ʈ2�� ������ ����Ʈ1�� head �ּҰ� ����
	}
}
// �׽�Ʈ ���α׷�
int main(void)
{
	ListNode* head1 = NULL;								// ����Ʈ1 ����
	ListNode* head2 = NULL;								// ����Ʈ2 ����

	head1 = insert_first(head1, 10);					// ����Ʈ1 �� �տ� 10 ����
	head1 = insert_first(head1, 20);					// ����Ʈ1 �� �տ� 20 ����
	head1 = insert_first(head1, 30);					// ����Ʈ1 �� �տ� 30 ����
	print_list(head1);									// ����Ʈ1 ���

	head2 = insert_first(head2, 40);					// ����Ʈ2 �� �տ� 40 ����
	head2 = insert_first(head2, 50);					// ����Ʈ2 �� �տ� 50 ����
	print_list(head2);									// ����Ʈ2 ���

	ListNode *total = concat_list(head1, head2);		// ����Ʈ1, 2�� ��ġ�� �Լ� ����
	print_list(total);									// ������ ����Ʈ ���
	return 0;											// ������
}
