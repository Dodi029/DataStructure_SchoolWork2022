int seq_search(int list[], int n, int key)
{
	int i;
	for (i = 0; i < n; i++)
		if (list[i] == key)
			return i;  /* Ž���� �����ϸ� Ű ���� �ε��� ��ȯ */
	return -1;    /* Ž���� �����ϸ� -1 ��ȯ */
}