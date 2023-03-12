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

// 순환적인 탐색 함수
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
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) return new_node(key);

	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);

	// 변경된 루트 포인터를 반환한다. 
	return node;
}
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;

	return current;
}
// 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고 
// 새로운 루트 노드를 반환한다. 
TreeNode* delete_node(TreeNode* root, double key)
{
	if (root == NULL) return root;

	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (key < root->key)
		root->left = delete_node(root->left, key);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else {
		// 첫 번째나 두 번째 경우
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
		// 세 번째 경우
		TreeNode* temp = min_value_node(root->right);

		// 중외 순회시 후계 노드를 복사한다. 
		root->key = temp->key;
		// 중외 순회시 후계 노드를 삭제한다. 
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

// 중위 순회
void inorder(TreeNode* root)
{
	if (root)
	{
		inorder(root->left);// 왼쪽서브트리 순회
		printf("[%.0lf] ", root->key);  // 노드 방문
		inorder(root->right);// 오른쪽서브트리 순회
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

	printf("이진 탐색 트리 중위 순회 결과 \n");
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
			fprintf(fp2, "이진탐색트리 탐색실패 \n");

	}

	fclose(fp1);
	fclose(fp2);
	system("notepad.exe input.txt");
	system("notepad.exe output.txt");
	return 0;
}