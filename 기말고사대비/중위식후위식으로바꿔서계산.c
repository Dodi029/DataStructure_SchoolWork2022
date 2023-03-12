// 1*4+(6+5) �ؽ�Ʈ ���� �ȿ� �ִ� ��
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;
//		     +
//	     *		 +
//    1	   4   16  25
typedef char element;		// ��ü!
							// ���Ŀ� ������ �ʿ��ϸ� ���⸸ �����Ͽ� ���δ�. 
							// ===== ���� �ڵ��� ���� ===== 
#define MAX_STACK_SIZE 100


typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 
int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}// �������� �켱���� ��ȯ
element* infix_to_postfix(element exp[])
{
	int i, idx = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;
	element* postfix_arr = (element*)malloc(MAX_STACK_SIZE);

	init_stack(&s);					// ���� �ʱ�ȭ 

	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': // ������
											// ���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			{
				postfix_arr[idx++] = peek(&s);
				postfix_arr[idx++] = ' ';
				pop(&s);
			}
			push(&s, ch);
			break;
		case '(':	// ���� ��ȣ
			push(&s, ch);
			break;
		case ')':	// ������ ��ȣ
			top_op = pop(&s);
			// ���� ��ȣ�� ���������� ���
			while (top_op != '(') {
				postfix_arr[idx++] = top_op;
				postfix_arr[idx++] = ' ';
				top_op = pop(&s);
			}
			break;
		default:
			postfix_arr[idx++] = ch;
			postfix_arr[idx++] = ' ';
			break;
		}
	}
	while (!is_empty(&s))	// ���ÿ� ����� �����ڵ� ���
	{
		top_op = peek(&s);
		pop(&s);
		postfix_arr[idx++] = top_op;
		postfix_arr[idx++] = ' ';
	}
	postfix_arr[idx++] = '\0';
	return postfix_arr;
}//����ǥ��� - > �ı� ǥ���
// ���� ǥ�� ���� ��� �Լ�
int eval(char exp[])		//== char* exp
{
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';	//�ٽ��ڵ� ���ڸ� ���ڷ� �ٲٴ� �ڵ� '0'=�ƽ�Ű�ڵ� 48
								// �Է��� �ǿ������̸�
			push(&s, value);
		}
		else {	//�������̸� �ǿ����ڸ� ���ÿ��� ����
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { //������ �����ϰ� ���ÿ� ���� 
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);		//���� ������� ����
}

// ���� ��� �Լ�
int evaluate(TreeNode* root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return root->data;
	else {
		int op1 = evaluate(root->left);
		int op2 = evaluate(root->right);
		printf("%d %c %d�� ����մϴ�.\n", op1, root->data, op2);
		switch (root->data) {
		case '+':
			return op1 + op2;
		case '-':
			return op1 - op2;
		case '*':
			return op1 * op2;
		case '/':
			return op1 / op2;
		}
	}
	return 0;
}
// 

int main(void)
{
	FILE* fp, * fp2;
	fp = fopen("05in.txt", "r");
	fp2 = fopen("05infix.txt", "w");
	int i = 0, j = 0;
	char buffer[1024];
	element infix[MAX];
	char* token, ch[MAX] = { NULL };
	int a[MAX];
	int a2[MAX];
	while (!feof(fp)) {
		fgets(infix, MAX, fp);
	}
	element* postfix = infix_to_postfix(infix);
	fprintf(fp2, "%s", postfix);
	fclose(fp2);
	fp2 = fopen("05infix.txt", "r");
	while (!feof(fp2)) {
		fscanf(fp2, "%s", ch);
		token = &ch;
		while (token != NULL) {
			if (strcmp(token, "+") == 0) {
				a[i] = '+';
				i++;
				break;
			}
			else if (strcmp(token, "-") == 0) {
				a[i] = '-';
				i++;
				break;
			}
			else if (strcmp(token, "*") == 0) {
				a[i] = '*';
				i++;
				break;
			}
			else if (strcmp(token, "/") == 0) {
				a[i] = '/';
				i++;
				break;
			}
			else {
				a2[j] = atoi(token);
				j++;
				break;
			}
		}

	}

	TreeNode n1 = { a2[0],  NULL, NULL };
	TreeNode n2 = { a2[1],  NULL,  NULL };
	TreeNode n3 = { a[0],  &n1,  &n2 };
	TreeNode n4 = { a2[2], NULL, NULL };
	TreeNode n5 = { a2[3], NULL, NULL };
	TreeNode n6 = { a[1], &n4,  &n5 };
	TreeNode n7 = { a[2], &n3,  &n6 };
	TreeNode* exp = &n7;
	printf("������ ���� %d�Դϴ�. \n", evaluate(exp));
	free(postfix);
	fclose(fp);
	fclose(fp2);
	return 0;
}