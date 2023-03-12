#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i>0; i--) {
		for (j = 0; j<i; j++)
			/* 앞뒤의 레코드를 비교한 후 교체 */
			if (list[j]>list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}