int visited[MAX_VERTICES];

// ���� ����Ʈ�� ǥ���� �׷����� ���� ���� �켱 Ž��
void dfs_list(GraphType* g, int v)
{
	GraphNode* w;
	visited[v] = TRUE;   		// ���� v�� �湮 ǥ�� 
	printf("���� %d -> ", v);		// �湮�� ���� ���
	for (w = g->adj_list[v]; w; w = w->link)// ���� ���� Ž�� 
		if (!visited[w->vertex])
			dfs_list(g, w->vertex); //���� w���� DFS ���� ����
}