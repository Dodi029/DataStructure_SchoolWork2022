#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;
//           +
//        *       +
//    1      4   16  25




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
    FILE* fp;
    fp = fopen("05_in_PSH.txt", "r");
    int i = 0, j = 0;
    char buffer[1024];
    char* token;
    int a[MAX];
    int a2[MAX];

    while (!feof(fp)) {
        i = 0;
        fgets(buffer, 1024, fp);
        token = strtok(buffer, " ");        //'/0'를 만날때마다 문자열 분할
        while (token != NULL) {
            if (strcmp(token, "+") == 0) {
                a[i++] = '+';
            }
            else if (strcmp(token, "-") == 0) {
                a[i++] = '-';
            }
            else if (strcmp(token, "*") == 0) {
                a[i++] = '*';
            }
            else if (strcmp(token, "/") == 0) {
                a[i++] = '/';
            }
            else {
                a2[j++] = atoi(token);
            }

            token = strtok(NULL, " ");      //마지막 '/0'에서부터 다시 검색
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
    fclose(fp);
    return 0;
}