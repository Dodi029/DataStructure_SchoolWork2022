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
TreeNode* insert_node(TreeNode* node, double key, char* num, char* name, int score)
{
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) return new_node(key);

	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (key < node->key)
		node->left = insert_node(node->left, key, num, name, score);
	else if (key > node->key)
		node->right = insert_node(node->right, key, num, name, score);

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