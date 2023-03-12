#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX 2

/*
void hanoi_tower(int n, char from, char tmp, char to)
{
    FILE* fp;
    fp = fopen_s("08.txt", "w");
    if (n == 1) fprintf(fp, "원판 1을 %c 에서 %c으로 옮긴다.\n", from, to);
    else {
        hanoi_tower(n - 1, from, to, tmp);
        fprintf(fp, "원판 %d을 %c에서 %c으로 옮긴다.\n", n, from, to);
        hanoi_tower(n - 1, tmp, from, to);
    }
    fclose(fp);
}
/////////////////////
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
    if (n == 1) fprintf(fp, "원판 1을 %c 에서 %c으로 옮긴다.\n", from, to);
    else {
        hanoi_tower(n - 1, from, to, tmp);
        fprintf(fp, "원판 %d을 %c에서 %c으로 옮긴다.\n", n, from, to);
        hanoi_tower(n - 1, tmp, from, to);
    }
    fclose(fp);

    return 0;
}
*/
#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 3
void hanoi_tower(int n, char from, char tmp, char to)
{
    if (n == 1) printf("원판 1을 %c 에서 %c으로 옮긴다.\n", from, to);
    else {
        hanoi_tower(n - 1, from, to, tmp);
        printf("원판 %d을 %c에서 %c으로 옮긴다.\n", n, from, to);
        hanoi_tower(n - 1, tmp, from, to);
    }
}
int main(void)
{
    hanoi_tower(MAX, 'A', 'B', 'C');
    system("notepad.exe 08 recursion_hanoi.c");
    return 0;
}