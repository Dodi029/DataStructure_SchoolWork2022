#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;
//		     +
//	     *		 +
//    1	   4   16  25
TreeNode n1 = { 1,  NULL, NULL };
TreeNode n2 = { 4,  NULL,  NULL };
TreeNode n3 = { '*',  &n1,  &n2 };
TreeNode n4 = { 16, NULL, NULL };
TreeNode n5 = { 25, NULL, NULL };
TreeNode n6 = { '+', &n4,  &n5 };
TreeNode n7 = { '+', &n3,  &n6 };
TreeNode* exp = &n7;

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
	printf("������ ���� %d�Դϴ�. \n", evaluate(exp));
	return 0;
}#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;
//		     +
//	     *		 +
//    1	   4   16  25
TreeNode n1 = { 1,  NULL, NULL };
TreeNode n2 = { 4,  NULL,  NULL };
TreeNode n3 = { '*',  &n1,  &n2 };
TreeNode n4 = { 16, NULL, NULL };
TreeNode n5 = { 25, NULL, NULL };
TreeNode n6 = { '+', &n4,  &n5 };
TreeNode n7 = { '+', &n3,  &n6 };
TreeNode* exp = &n7;

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
	printf("������ ���� %d�Դϴ�. \n", evaluate(exp));
	return 0;
}

// ������ ��������
/*
 #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 7
// ���� Ʈ�� ���

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

//           +
//        *       +
//    1      4   16  25

TreeNode n1 = { NULL,  NULL, NULL };
TreeNode n2 = { NULL,  NULL,  NULL };
TreeNode n3 = { NULL,  &n1,  &n2 };
TreeNode n4 = { NULL, NULL, NULL };
TreeNode n5 = { NULL, NULL, NULL };
TreeNode n6 = { NULL, &n4,  &n5 };
TreeNode n7 = { NULL, &n3,  &n6 };
TreeNode* exp = &n7;
// ���� ��������� ������ �޾ƿ���
// ���� ��� �Լ�
int evaluate(TreeNode* root)
{
    FILE* fp;
    fp = fopen("05_out_KKJ.txt", "a+");
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return root->data;
    else {
        int op1 = evaluate(root->left);
        int op2 = evaluate(root->right);
        fprintf(fp, "%d %c %d�� ����մϴ�.\n", op1, root->data, op2);
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
    fclose(fp);
    return 0;
}
// 
int main(void)
{
    FILE* fp1, * fp2;
    char ary[MAX][MAX]; TreeNode trees[MAX] = { n1, n2, n3, n4, n5, n6, n7 };
    int num[MAX]; char ary2[MAX];
    fp1 = fopen("05_in_KKJ.txt", "r");
    for (int i = 0; i < MAX; i++)
    {
        fscanf(fp1, "%s", &ary[i]);
        if ('0' <= ary[i][0] && ary[i][0] <= '9')
        {
            num[i] = atoi(ary[i]);
            if (num[i] != NULL)
                trees[i].data = num[i];
        }
        else
        {
            ary2[i] = ary[i][0];
            if (ary2[i] != NULL)
                trees[i].data = ary2[i];
        }
    }
    n1.data = num[0];
    n2.data = num[1];
    n3.data = ary2[2];
    n4.data = num[3];
    n5.data = num[4];
    n6.data = ary2[5];
    n7.data = ary2[6];
    fp2 = fopen("05_out_KKJ.txt", "a+");
    fprintf(fp2, "������ ���� %d�Դϴ�. \n", evaluate(exp));
    fclose(fp1); fclose(fp2);
    return 0;
}
//rand�� ���� �߻����� ���Ͽ� ��� �� ������ �о�ͼ� ���İ�� ���Ͽ� ���
*/