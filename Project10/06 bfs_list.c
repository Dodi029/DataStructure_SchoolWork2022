void bfs_list(GraphType* g, int v)
{
	GraphNode* w;
	QueueType q;

	init(&q);    				// ť �ʱ� ȭ 
	visited[v] = TRUE;      // ���� v �湮 ǥ�� 
	printf("%d �湮 -> ", v);
	enqueue(&q, v);			// ���������� ť�� ���� 
	while (!is_empty(&q)) {
		v = dequeue(&q);		// ť�� ����� ���� ���� 
		for (w = g->adj_list[v]; w; w = w->link) //���� ���� Ž��
			if (!visited[w->vertex]) {	// �̹湮 ���� Ž�� 
				visited[w->vertex] = TRUE;   // �湮 ǥ��
				printf("%d �湮 -> ", w->vextex);
				enqueue(&q, w->vertex);	//������ ť�� ����
			}
	}
}