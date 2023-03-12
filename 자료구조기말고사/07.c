#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100


typedef struct element2 {
	char num[1024];
	char name[1024];
	float score;
	int rank;
}element2;
typedef struct TreeNode {
	double key;
	char num[1024];
	char name[1024];
	float score;
	int rank;

	struct TreeNode* left, * right;
} TreeNode;

// ��ȯ���� Ž�� �Լ�
TreeNode* search(TreeNode* node, double key)
{
	if (node == NULL) return NULL;
	if (key == node->key) {
		printf("%.0lf", node->key);
		return node;
	}
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}
TreeNode* new_node(double key)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = key;
	temp->left = temp->right = NULL;
	return temp;
}
TreeNode* insert_node(TreeNode* node, double key, char* num, char* name, int score)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) return new_node(key);

	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (key < node->key)
		node->left = insert_node(node->left, key, num, name, score);
	else if (key > node->key)
		node->right = insert_node(node->right, key, num, name, score);

	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return node;
}
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;

	return current;
}
// ���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ� 
// ���ο� ��Ʈ ��带 ��ȯ�Ѵ�. 
TreeNode* delete_node(TreeNode* root, double key)
{
	if (root == NULL) return root;

	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (key < root->key)
		root->left = delete_node(root->left, key);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		// ù ��°�� �� ��° ���
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// �� ��° ���
		TreeNode* temp = min_value_node(root->right);

		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->key = temp->key;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

// ���� ��ȸ
void inorder(TreeNode* root)
{
	if (root)
	{
		inorder(root->left);// ���ʼ���Ʈ�� ��ȸ
		printf("[%.0lf] ", root->key);  // ��� �湮
		inorder(root->right);// �����ʼ���Ʈ�� ��ȸ
	}
}

void insert_rank(TreeNode* head) {
	for (TreeNode* s = head; s != NULL; s = s->left) {
		s->rank = 1;
		for (TreeNode* p = head->left; p != NULL; p = p->left) {
			if (s->score < p->score)
				s->rank++;
		}
	}
}
int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;

	root = insert_node(root, 1, "2020131055", "ojm", 3.82);
	root = insert_node(root, 2, "2020131011", "sjm", 3.99);
	root = insert_node(root, 3, "2020132044", "ajm", 4.3);
	root = insert_node(root, 4, "2020132033", "yjm", 4.2);
	root = insert_node(root, 5, "2020132022", "bjm", 4.25);
	root = insert_node(root, 6, "2020132077", "cjm", 3.7);
	root = insert_node(root, 7, "2020132000", "rjm", 3.54);
	root = insert_node(root, 8, "2020132066", "tjm", 3.66);
	root = insert_node(root, 9, "2020132099", "xjm", 3.65);
	root = insert_node(root, 10, "2020132088", "zjm", 3.72);
	
	insert_rank(root);


	return 0;
}