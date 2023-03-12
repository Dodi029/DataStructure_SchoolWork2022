#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct ListNode
{ 	// ��� Ÿ��
	int num;		// �й�
	int name1;		// �̸�
	int name2;		// �̸�
	int name3;		// �̸�
	float score;		// ����

	struct ListNode* link;
} ListNode;

// ����Ʈ�� �׸� ���
void print_list(ListNode* head)
{
	ListNode* p;		// ��� ������

	if (head == NULL) return;		// head�� ��������� �Լ� ����
	p = head->link;			// head�� ��ũ�� ù��° ���� �̵�
	do {		// �ݺ���
		printf("%d\t%c%c%c\t%.2lf\n", p->num, p->name1, p->name2, p->name3, p->score);
		// �й�, �̸� �̴ϼ�, ������ ���
		printf("--------------------\n");
		// �������� ���� �ۼ�
		p = p->link;			// ���� ���� ��ġ �̵�
	} while (p != head);		// �ݺ��� ���� ����
	printf("%d\t%c%c%c\t%.2lf\n", p->num, p->name1, p->name2, p->name3, p->score);
	// ������ ���(�л��� ����)�� ���
}

ListNode* insert_first(ListNode* head, int num, int name1, int name2, int name3, float score)
{			// ����Ʈ ù��°�� ��� ����
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	// ��� ���� �Ҵ����� ����

	node->num = num;		// �Էµ� �й� ����
	node->name1 = name1;		// �Էµ� �̴ϼ� ����
	node->name2 = name2;		// �Էµ� �̴ϼ� ����
	node->name3 = name3;		// �Էµ� �̴ϼ� ����
	node->score = score;	// �Էµ� ���� ����

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

ListNode* insert_last(ListNode* head, int num, int name1, int name2, int name3, float score)
{		// ����Ʈ �������� ��� ����
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	// ��� ���� �Ҵ����� ����

	node->num = num;		// �Էµ� �й� ����
	node->name1 = name1;		// �Էµ� �̸� ����
	node->name2 = name2;	// �Էµ� �̴ϼ� ����
	node->name3 = name3;	// �Էµ� �̴ϼ� ����
	node->score = score;	// �Էµ� ���� ����

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
	srand(time(NULL));		// ���Ģ�� ������ ������ ���⵵�� ����
	ListNode* head = NULL;		// head�� �ʱ�ȭ
	// ��� �ʱ�ȭ
	for (int i = 0; i < 50; i++) {	// 500�� �й�, �̸�, ���� ����
		int num = rand();		// ���� ����
		num = num % 10000;		// ���ڸ� ���� ����
		num = 20220000 + num; // ������ �й� ����

		int name1, name2, name3;		// �̴ϼ� ����
		//int nameary[3];
		//for (int i = 0; i < 3; i++) {	// �л� �̸� ������ ���� �ڵ�
		//	name = 65 + rand() % 26;	// �ƽ�Ű ���� 65 = 'A'�̹Ƿ�
										// �������� 0~25���� ���ϸ� �빮�� ���ĺ��� ����
		//	nameary[i] = name;			// ���� ������ �̸� �迭�� ����
		//}
		name1 = 65 + rand() % 26;		// ù��° �̴ϼ�
		name2 = 65 + rand() % 26;		// �ι�° �̴ϼ�
		name3 = 65 + rand() % 26;		// ����° �̴ϼ�

		float score;		// ������ ���� ����
		score = (float)(rand() % 45) / 10;	//0���� 4.5���� ���� ����

		if (score < 3.0) {	// ���� 3.0 ������ �л��鸸 ���
			head = insert_last(head, num, name1, name2, name3, score);
		}
		// ����Ʈ �� �ڿ� ��� ����
	}

	print_list(head);		// ��������Ʈ ���

	return 0;		// ����
}