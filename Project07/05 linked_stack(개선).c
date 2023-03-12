#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include<stdlib.h>
#include <string.h>

typedef int element;
typedef struct StackNode {
	int hour, minute;		// �ð� ����
	int name1, name2, name3;	// �̸� �̴ϼ� ����
	int num1, num2;		// ��ȭ��ȣ �� �� ����
	struct StackNode* link;	// ��ũ ����
} StackNode;		// ����ü ����

typedef struct {
	StackNode* top;		// ������ top ����
} LinkedStackType;	// ���� ����
// �ʱ�ȭ �Լ�
void init(LinkedStackType* s)	// top �ʱ�ȭ �Լ�
{
	s->top = NULL;		// top �ʱ�ȭ
}
// ���� ���� ���� �Լ�
int is_empty(LinkedStackType* s)
{ // ������ ����ִ��� Ȯ���ϴ� �Լ�
	return (s->top == NULL);	// top�� NULL���� ����
}
// ��ȭ ���� ���� �Լ�
int is_full(LinkedStackType* s)
{	// ������ �������ִ��� Ȯ���ϴ� �Լ�
	return 0;	// ������������ 0 ����
}
// ���� �Լ�
void push(LinkedStackType* s, int name1,int name2, int name3, int num1, int num2)
{	// ���ؿ� �����ϴ� �Լ�
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	// ���ÿ� ������ ��� ���� ����
	temp->name1 = name1;		// ������ ù��° �̴ϼ� ����
	temp->name2 = name2;		// ������ �ι�° �̴ϼ� ����
	temp->name3 = name3;		// ������ ����° �̴ϼ� ����
	temp->num1 = num1;		// ������ �� ��ȭ��ȣ ����
	temp->num2 = num2;		// ������ �� ��ȭ��ȣ ����
	temp->link = s->top;	// ������ ž�� ������ ����� ���� ��ũ�� ����
	s->top = temp;		// ������ ��带 ������ top�� ����
}
void print_stack(LinkedStackType* s)
{	//������ ����ϴ� �Լ�
	for (StackNode* p = s->top; p != NULL; p = p->link) {
		// top���� ������ NULL�� �ɶ����� ��ġ�� �̵� �ݺ�
		printf("%c%c%c\t", p->name1, p->name2, p->name3);
		// �ð� �� �̴ϼ� 3�ڸ� ���
		printf("010-%d-%d\n",p->num1, p->num2);
		// ��ȭ��ȣ ���
	}
}
// ���� �Լ�
element pop(LinkedStackType* s)
{	// ���� �� ���� �ִ� ��带 ����ϴ� �Լ�
	if (is_empty(s)) {		// ������ ����ִٸ�
		fprintf(stderr, "������ �������\n");	// ����ִٰ� ���
		exit(1);	// ���μ��� ����
	}
	else {		// ������ ������� �ʴ� ���
		StackNode* temp = s->top;	// top�� ��ġ�� ���� temp�� ����
		int name1 = temp->name1;	// temp�� ù��° �̴ϼ��� name1�� ����
		int name2 = temp->name2;	// temp�� �ι�° �̴ϼ��� name2�� ����
		int name3 = temp->name3;	// temp�� ����° �̴ϼ��� name3�� ����
		int num1 = temp->num1;		// temp�� �� ��ȭ��ȣ�� num1�� ����
		int num2 = temp->num2;		// temp�� �� ��ȭ��ȣ�� num2�� ����
		s->top = s->top->link;		// top�� ��ġ�� �������� ����
		free(temp);					// temp ��� ����
		return name1, name2, name3, num1, num2;	// ������ ������ ����
	}
}
// ��ũ �Լ�
element peek(LinkedStackType* s)
{		// �� ���� �ִ� ��尡 �������� ����ϴ� �Լ�
	if (is_empty(s)) {	// ������ ����ִٸ�
		fprintf(stderr, "������ �������\n");
		exit(1);	// ���μ��� ����
	}
	else {		// ������ ������� ���� ���
		return s->top->hour;	// top�� �ִ� ������ ����
	}
}
// �� �Լ�
int main(void)
{
	LinkedStackType s;		// ����Ʈ ���� ����
	init(&s);		// ���� �ʱ�ȭ
	srand(time(NULL));	// ���Ģ�� ���� ����

	for (int i = 0; i < 5; i++) {	// 5�� ����

		int name1, name2, name3;		// �̸� ����
		name1 = 65 + rand() % 26;		// ù��° �̴ϼ�
		name2 = 65 + rand() % 26;		// �ι�° �̴ϼ�
		name3 = 65 + rand() % 26;		// ����° �̴ϼ�

		int num1, num2;			// ��ȭ��ȣ �� �� ����
		num1 = rand();			// �� ��ȭ��ȣ ���� ����
		num2 = rand();			// �� ��ȭ��ȣ ���� ����
		num1 = num1 % 10000;		// ������ �� ��ȭ��ȣ 4�ڸ� ����
		num2 = num2 % 10000;		// ������ �� ��ȭ��ȣ 4�ڸ� ����

		push(&s, name1, name2, name3, num1, num2);
		// ������ ��,�� ,�̸� �̴ϼ� 3�ڸ�, ��ȭ��ȣ ������ 8�ڸ� ����
		print_stack(&s);	// ���ÿ� ���� �� ���
	}
	for (int i = 0; i < 5; i++) {  // ������ ���� ��ŭ ����
		pop(&s); print_stack(&s);		// ���� pop�� ���
	}
	
	return 0;
}