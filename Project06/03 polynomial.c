#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode { // ��� Ÿ��
	int coef;				// ���
	int expon;				// ����
	struct ListNode *link;
} ListNode;

// ���� ����Ʈ ���
typedef struct ListType { // ����Ʈ ��� Ÿ��
	int size;				// ����
	ListNode *head;			// ���
	ListNode *tail;			// ����
} ListType;

// ���� �Լ�
void error(char *message)	// ������ ���
{
	fprintf(stderr, "%s\n", message);
		// ���� ������ printf()�� ����� ��µ��� ���� �� �ֱ� ������
		// fprintf()�� stderr�� ����Ͽ� ���� ���� ����ϰ� ��
	exit(1);	// ���μ��� ����
				// exit(1)�� "�����޽��� ����"
}

//  ����Ʈ ��� ���� �Լ�
ListType* create()
{
	ListType *plist = (ListType *)malloc(sizeof(ListType));	// ����Ʈ Ÿ�� ũ�⸸ŭ ���� ����
	plist->size = 0;										// size �ʱ�ȭ
	plist->head = plist->tail = NULL;						// ���, ���� �ʱ�ȭ
	return plist;
}															// ������ ����Ʈ ��� ����

// plist�� ���� ����Ʈ�� ����� ����Ű�� ������, coef�� ���, 
// expon�� ����
void insert_last(ListType* plist, int coef, int expon)		// ����Ʈ �� �ڿ� ��� ���� �Լ�
{
	ListNode* temp =
		(ListNode *)malloc(sizeof(ListNode));				// ����Ʈ ���� ����
	if (temp == NULL) error("�޸� �Ҵ� ����");				// ����Ʈ�� ������� ��� ���� ���
	temp->coef = coef;										// ��� ����
	temp->expon = expon;									// ���� ����
	temp->link = NULL;										// ��ũ�� NULL ����
	if (plist->tail == NULL) {								// ����Ʈ Ÿ�Կ� ������ NULL�� ���
															// ������ ������� ���
		plist->head = plist->tail = temp;					/// ���� ���Ͽ� ������ ��� ����
	}
	else {													// ������ ������� ���� ���
		plist->tail->link = temp;							// ������ ��ũ�� ������ ��� ����
		plist->tail = temp;									// ���Ͽ� ������ ��� ����
	}
	plist->size++;											// ����Ʈ Ÿ���� ���� ����
}

// list3 = list1 + list2
void poly_add(ListType* plist1, ListType* plist2, ListType* plist3)
{		// �� ���Ḯ��Ʈ (=�� ���׽�)�� ���� ����Ʈ(=���׽�)�� ����� �Լ�
	ListNode* a = plist1->head;									// ù ���� ����Ʈ(���׽�) head ����
	ListNode* b = plist2->head;									// ù ���� ����Ʈ(���׽�) head ����
	int sum;

	while (a && b) {											// �� ����Ʈ(���׽�)�� ������ ���
		if (a->expon == b->expon) {   // a�� ���� == b�� ���� �� ���
			sum = a->coef + b->coef;		// ����� ����� �����͸� ��ħ
			if (sum != 0)					// ���� �����Ͱ� 0�� �ƴ� ���
				insert_last(plist3, sum, a->expon);		// ���� ���� ����Ʈ�� �� �� ���� �κп� ����
			a = a->link; b = b->link;					// ����Ʈ1�� ����Ʈ2 ��� ��ġ �̵�
		}
		else if (a->expon > b->expon) {  // a�� ���� > b�� ���� �� ��� 
			insert_last(plist3, a->coef, a->expon);		// ���� ���� ����Ʈ �� �ڿ� ����Ʈ1 ����, ��� ����
			a = a->link;								// ����Ʈ1�� ��� ��ġ �̵�
		}
		else {					// a�� ���� < b�� ����
			insert_last(plist3, b->coef, b->expon);		// ���� ���� ����Ʈ �� �ڿ� ����Ʈ2 ����, ��� ����
			b = b->link;								// ����Ʈ2�� ��� ��ġ �̵�
		}
	}

	// a�� b���� �ϳ��� ���� ������ �Ǹ� �����ִ� �׵��� ��� 
	// ��� ���׽����� ����
	for (; a != NULL; a = a->link)					// ����Ʈ1�� ��尡 �������� ���
		insert_last(plist3, a->coef, a->expon);		// ���� ���� ����Ʈ �� �ڿ� ����Ʈ1 ����, ��� ����
	for (; b != NULL; b = b->link)					// ����Ʈ2�� ��尡 �������� ���
		insert_last(plist3, b->coef, b->expon);		// ���� ���� ����Ʈ �� �ھ� ����Ʈ2 ����, ��� ����
}

void poly_print(ListType* plist)		// ����Ʈ(=���׽�) ����ϴ� �Լ�
{
	ListNode* p = plist->head;			// ����Ʈ head�� ����

	printf("polynomial = ");			// ����Ʈ(=���׽�) ���
	for (; p; p = p->link) {			// ��� ��ġ �̵�
		printf("%d^%d + ", p->coef, p->expon);	// ��忡 ����� ����, ��� ���
	}
	printf("\n");
}
//
int main(void)
{
	ListType *list1, *list2, *list3;	// ����Ʈ(=���׽�) 3�� ����

	// ���� ����Ʈ ��� ����
	list1 = create();					// ����Ʈ1 ����
	list2 = create();					// ����Ʈ2 ����
	list3 = create();					// ����Ʈ3 ����

	// ���׽� 1�� ���� 
	insert_last(list1, 3, 12);			// ����Ʈ1�� ����, ��� ����
	insert_last(list1, 2, 8);			// ����Ʈ1�� ����, ��� ����
	insert_last(list1, 1, 0);			// ����Ʈ1�� ����, ��� ����

	// ���׽� 2�� ���� 
	insert_last(list2, 8, 12);			// ����Ʈ2�� ����, ��� ����
	insert_last(list2, -3, 10);			// ����Ʈ2�� ����, ��� ����
	insert_last(list2, 10, 6);			// ����Ʈ2�� ����, ��� ����

	poly_print(list1);					// ����Ʈ1 ���
	poly_print(list2);					// ����Ʈ2 ���

	// ���׽� 3 = ���׽� 1 + ���׽� 2
	poly_add(list1, list2, list3);		// ����Ʈ3�� ����Ʈ1, 2�� ���ϰ� ����
	poly_print(list3);					// ����Ʈ3 ���

	free(list1); free(list2); free(list3);	// ���� ������ �޸𸮵� ����
}