#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode 
{
	int data;
	struct TreeNode *left, *right;
} TreeNode;

//		  15
//	   4		 20
//    1	      16  25
TreeNode n1 = { 1,  NULL, NULL };
TreeNode n2 = { 4,  &n1,  NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3,  &n4 };
TreeNode n6 = { 15, &n2,  &n5 };
TreeNode *root = &n6;     //��Ʈ����

int get_node_count(TreeNode *node);   // ��ü����� ��
int get_leaf_count(TreeNode *node);   // �ܸ������ ��
int get_height(TreeNode *node);       // ����

int main()
{
	int result1, result2, result3;
	
	result1 = get_node_count(root);
	printf("��ü��� ��: %d \n", result1);

	result2 = get_leaf_count(root);
	printf("�ܸ���� ��: %d \n", result2);

	result3 = get_height(root);
	printf("Ʈ���� ����: %d \n", result3);

	return 0;
}

int get_node_count(TreeNode *node) // ��ü����� ��
{
	int count = 0;

	if (node != NULL)
		count = 1 + get_node_count(node->left) +
		get_node_count(node->right);

	return count;
}

int get_leaf_count(TreeNode *node)  // �ܸ������ ��
{
	int count = 0;

	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_leaf_count(node->left) +
			get_leaf_count(node->right);
	}
	return count;
}

int get_height(TreeNode *node) // Ʈ���� ����
{
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left),
			get_height(node->right));

	return height;
}

