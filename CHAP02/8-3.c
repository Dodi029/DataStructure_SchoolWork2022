int main(void)
{
    FILE* fp;
    fp = fopen("08.txt", "w");
    int n;
    n = MAX;
    char A = 0, B = 0, C = 0;
    char from = A;
    char tmp = B;
    char to = C;
    hanoi_tower(MAX, 'A', 'B', 'C');
    if (n == 1) fprintf(fp, "���� 1�� %c ���� %c���� �ű��.\n", from, to);
    else {
        hanoi_tower(n - 1, from, to, tmp);
        fprintf(fp, "���� %d�� %c���� %c���� �ű��.\n", n, from, to);
        hanoi_tower(n - 1, tmp, from, to);
    }
    fclose(fp);
    //for(i=0;i<100;i++)
    //system("notepad.exe 08 recursion_hanoi.c"); // #include <stdlib.h>
    return 0;
}