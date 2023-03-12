#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef int element;
typedef struct ListNode {    // 노드 타입
    element data;
    char name[20];
    int no;
    double ID;
    double score;
    struct ListNode* link;
} ListNode;

// 오류 처리 함수
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
ListNode* insert_first(ListNode* head, int no, double value, char* name, double score)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));   //(1)
    p->no = no;
    p->ID = value;               // (2)
    strcpy(p->name, name);
    p->score = score;
    p->link = head;   // 헤드 포인터의 값을 복사   //(3)
    head = p;   // 헤드 포인터 변경      //(4)
    return head;   // 변경된 헤드 포인터 반환
}

// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));   //(1)
    p->data = value;      //(2)
    p->link = pre->link;   //(3)   
    pre->link = p;      //(4)   
    return head;      //(5)   
}

ListNode* delete_first(ListNode* head)
{
    ListNode* removed;
    if (head == NULL) return NULL;
    removed = head;   // (1)
    head = removed->link;   // (2)
    free(removed);      // (3)
    return head;      // (4)
}
// pre가 가리키는 노드의 다음 노드를 삭제한다. 
ListNode* delete(ListNode* head, ListNode* pre)
{
    ListNode* removed;
    removed = pre->link;
    pre->link = removed->link;      // (2)
    free(removed);         // (3)
    return head;         // (4)
}

void print_list(ListNode* head)
{
    for (ListNode* p = head; p != NULL; p = p->link) {
        printf("%d %.0lf %s %.2lf\n", p->no, p->ID, p->name, p->score);
    }
}

// 테스트 프로그램
int main(void)
{
    ListNode* head = NULL;
    ListNode data[MAX];
    int i = 0;
    char select = NULL;

    do {
        printf("\n명령어를 입력하시오(c(계속), q(종료)): ");
        select = getchar();
        if (select == 'c') {
            printf("학번 : ");
            scanf("%lf", &(data + i)->ID);
            printf("\n이름 : ");
            scanf("%s", &(data + i)->name);
            printf("\n학점 : ");
            scanf("%lf", &(data + i)->score);
            i++;
        }
        getchar();
    } while (select != 'q');

    for (int j = 0; j < i; j++) {
        head = insert_first(head, j + 1, (data + i)->ID, (data + i)->name, (data + i)->score);
        print_list(head);
    }
    return 0;
}