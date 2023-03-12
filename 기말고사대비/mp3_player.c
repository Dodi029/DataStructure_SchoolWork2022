#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct element {
    char music[MAX];
    int num;
}element;

typedef struct DListNode {   // ���߿��� ��� Ÿ��
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

DListNode* current;

// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DListNode* phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}

// ���� ���� ����Ʈ�� ��带 ���
void print_dlist(DListNode* phead)
{
    FILE* fp;
    fp = fopen("musiclist.txt", "w");
    DListNode* p;
    for (p = phead->rlink; p != phead; p = p->rlink) {
        if (p == current)
            printf("<-| #%s# |-> ", p->data.music);
        else
            printf("<-| %s |-> ", p->data.music);
    }
    printf("\n");
    for (p = phead->rlink; p != phead; p = p->rlink)
    {
        fprintf(fp, "%d %s\n", p->data.num, p->data.music);
    }
    fclose(fp);
}
// ��� newnode�� ��� before�� �����ʿ� �����Ѵ�.
void dinsert(DListNode* before, element data)
{
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    strcpy(newnode->data.music, data.music);
    newnode->data.num = data.num;
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}
// ��� removed�� �����Ѵ�.
void ddelete(DListNode* head,
    DListNode* removed)
{
    if (removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

void bubbleSortNode(DListNode* head) {
    DListNode* p, * q;
    for (p = head->rlink; p != head; p = p->rlink)
    {
        for (q = head->rlink; q->rlink != head; q = q->rlink)
            if (q->data.num > q->rlink->data.num)
            {
                element tmp;
                tmp = q->data;
                q->data = q->rlink->data;
                q->rlink->data = tmp;
            }
    }
}

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
    char ch;
    element mp3;
    int i;
    FILE* fp1, * fp2;
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    init(head);
    fp1 = fopen("list.txt", "r");
    fp2 = fopen("number.txt", "r");
    while ((!feof(fp1)) && (!feof(fp2)))
    {
        fscanf(fp2, "%d\n", &mp3.num);
        fgets(mp3.music, sizeof(mp3.music), fp1);
        if (mp3.music[strlen(mp3.music) - 1] == '\n')
            mp3.music[strlen(mp3.music) - 1] = '\0';
        dinsert(head, mp3);
    }
    //dinsert(head, "Mamamia");
    //dinsert(head, "Dancing Queen");
    //dinsert(head, "Fernando");
    bubbleSortNode(head);
    current = head->rlink;
    print_dlist(head);

    do {
        printf("\n��ɾ �Է��Ͻÿ�(<, >, q): ");
        ch = getchar();
        if (ch == '<') {
            current = current->llink;
            if (current == head)
                current = current->llink;
        }
        else if (ch == '>') {
            current = current->rlink;
            if (current == head)
                current = current->rlink;
        }
        print_dlist(head);
        getchar();
    } while (ch != 'q');
    fclose(fp1); fclose(fp2);
    free(head);
    // ���� �޸� ���� �ڵ带 ���⿡
}