#include <stdio.h>
#include <malloc.h>

typedef int element;
typedef struct StackNode {
	element data;		// ����� ������ ����
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
void push(LinkedStackType* s, element item)
{	// ���ؿ� �����ϴ� �Լ�
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	// ���ÿ� ������ ��� ���� ����
	temp->data = item;	// �Է��� �� item�� ����� �����Ϳ� ����
	temp->link = s->top;	// ������ ž�� ������ ����� ���� ��ũ�� ����
	s->top = temp;		// ������ ��带 ������ top�� ����
}
void print_stack(LinkedStackType* s)
{	//������ ����ϴ� �Լ�
	for (StackNode* p = s->top; p != NULL; p = p->link)
		// top���� ������ NULL�� �ɶ����� ��ġ�� �̵� �ݺ�
		printf("%d->", p->data);
	// �̵��ϸ鼭 ���
	printf("NULL \n");	// ���������� NULL ���
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
		int data = temp->data;		// temp�� �����͸� int data�� ����
		s->top = s->top->link;		// top�� ��ġ�� �������� ����
		free(temp);					// temp ��� ����
		return data;				// ������ ������ ����
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
		return s->top->data;	// top�� �ִ� ������ ����
	}
}
// �� �Լ�
int main(void)
{
	LinkedStackType s;		// ����Ʈ ���� ����
	init(&s);		// ���� �ʱ�ȭ
	push(&s, 1); print_stack(&s);	// ���ÿ� 1���� �� ���
	push(&s, 2); print_stack(&s);	// ���ÿ� 2���� �� ���
	push(&s, 3); print_stack(&s);	// ���ÿ� 3���� �� ���
	pop(&s); print_stack(&s);		// ���� pop�� ���
	pop(&s); print_stack(&s);		// ���� pop�� ���
	pop(&s); print_stack(&s);		// ���� pop�� ���
	return 0;
}