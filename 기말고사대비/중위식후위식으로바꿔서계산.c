// 1*4+(6+5) 텍스트 파일 안에 있는 식
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
typedef char element;		// 교체!
							// 차후에 스택이 필요하면 여기만 복사하여 붙인다. 
							// ===== 스택 코드의 시작 ===== 
#define MAX_STACK_SIZE 100


typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 
int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}// 연산자의 우선순위 반환
element* infix_to_postfix(element exp[])
{
	int i, idx = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;
	element* postfix_arr = (element*)malloc(MAX_STACK_SIZE);

	init_stack(&s);					// 스택 초기화 

	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': // 연산자
											// 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			{
				postfix_arr[idx++] = peek(&s);
				postfix_arr[idx++] = ' ';
				pop(&s);
			}
			push(&s, ch);
			break;
		case '(':	// 왼쪽 괄호
			push(&s, ch);
			break;
		case ')':	// 오른쪽 괄호
			top_op = pop(&s);
			// 왼쪽 괄호를 만날때까지 출력
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
	while (!is_empty(&s))	// 스택에 저장된 연산자들 출력
	{
		top_op = peek(&s);
		pop(&s);
		postfix_arr[idx++] = top_op;
		postfix_arr[idx++] = ' ';
	}
	postfix_arr[idx++] = '\0';
	return postfix_arr;
}//중위표기식 - > 후기 표기식
// 후위 표기 수식 계산 함수
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
			value = ch - '0';	//핵심코드 문자를 숫자로 바꾸는 코드 '0'=아스키코드 48
								// 입력이 피연산자이면
			push(&s, value);
		}
		else {	//연산자이면 피연산자를 스택에서 제거
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { //연산을 수행하고 스택에 저장 
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);		//최종 결과값을 리턴
}

// 수식 계산 함수
int evaluate(TreeNode* root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return root->data;
	else {
		int op1 = evaluate(root->left);
		int op2 = evaluate(root->right);
		printf("%d %c %d을 계산합니다.\n", op1, root->data, op2);
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
	printf("수식의 값은 %d입니다. \n", evaluate(exp));
	free(postfix);
	fclose(fp);
	fclose(fp2);
	return 0;
}