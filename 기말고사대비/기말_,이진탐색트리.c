#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100


typedef struct element2 {
	char name[20];
	double num;
}element2;
typedef struct TreeNode {
	double key;
	char name[20];
	//element age;
	//double score;

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
TreeNode* insert_node(TreeNode* node, double key)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) return new_node(key);

	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);

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

int main(void)
{
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	int i = 0;
	int j = 0;

	element2 ary[MAX];
	element2 ary2[MAX];
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;

	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "a+");
	fp3 = fopen("input2.txt", "r");
	while (!feof(fp1))
	{
		fscanf(fp1, "%lf", &ary[j].num);
		j++;
	}
	while (!feof(fp3)) {
		fscanf(fp3, "%lf", &ary2[i].num);
		fscanf(fp3, "%s", ary2[i].name);

		i++;
	}

	for (int k = 0; k < i; k++)
		root = insert_node(root, ary2[k].num);

	//root = insert_node(root, 20);
	//root = insert_node(root, 10);
	//root = insert_node(root, 40);
	//root = insert_node(root, 50);
	//root = insert_node(root, 60);

	printf("���� Ž�� Ʈ�� ���� ��ȸ ��� \n");
	inorder(root);
	printf("\n\n");
	for (int k = 0; k < j; k++) {
		if (search(root, ary[k].num) != NULL) {
			for (int t = 0; t < i; t++) {
				if (ary[k].num == ary2[t].num) {
					printf(" %s\n", ary2[t].name);
				}
			}
		}
		else
			fprintf(fp2, "����Ž��Ʈ�� Ž������ \n");

	}

	fclose(fp1);
	fclose(fp2);
	system("notepad.exe input.txt");
	system("notepad.exe output.txt");
	return 0;
}