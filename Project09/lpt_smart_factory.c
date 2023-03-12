#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100 // 10�� �¼� ��ŭ ����/���� ���� �����غ� ��
#define MAX_QUEUE_SIZE 100
#define MAX_HEAP_ELEMENT 200

int black_cnt, red_cnt, blue_cnt;
int error_cnt, error_percent, total_cnt;
int red_error_cnt = 0, blue_error_cnt = 0, black_error_cnt = 0;
char filename[20];

typedef struct {            // ����ü�� ����
    int pen_id;
    char pen_color[5];
    int pen_cnt;
    char date;
    int time;
} element;

typedef struct {
    int id;
    int avail;
} lpt_element;

typedef struct {
    lpt_element heap[MAX_HEAP_ELEMENT];
    int heap_size;
} HeapType;

// ���� �Լ�
HeapType* create()
{
    return (HeapType*)malloc(sizeof(HeapType));
}

// �ʱ�ȭ �Լ�
void init(HeapType* h)
{
    h->heap_size = 0;
}
// ���� ����� ������ heap_size�� ���� h�� item�� �����Ѵ�.
// ���� �Լ�
void insert_min_heap(HeapType* h, lpt_element item)
{
    int i;
    i = ++(h->heap_size);

    //  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
    while ((i != 1) && (item.avail < h->heap[i / 2].avail)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;     // ���ο� ��带 ����
}
// ���� �Լ�
lpt_element delete_min_heap(HeapType* h)
{
    int parent, child;
    lpt_element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        // ���� ����� �ڽĳ���� �� ���� �ڽĳ�带 ã�´�.
        if ((child < h->heap_size) &&
            (h->heap[child].avail) > h->heap[child + 1].avail)
            child++;
        if (temp.avail < h->heap[child].avail) break;
        // �� �ܰ� �Ʒ��� �̵�
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}
#define JOBS 6
#define MACHINES 3

typedef struct { // ť Ÿ��
    element data[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType* q)
{
    q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
    return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ����ť ��� �Լ�
void queue_print(QueueType* q) {            // �ҷ�ǰ�� ���� �����ϴ� ������ ����� �Լ�
    FILE* fp;           // ���� ������
    char err[20] = "error";         // ���� �Է¹��� ��¥�ڿ� error�� �ٿ��� �������ϸ� ��� �������� ǥ��
    char* p;
    p = strcat(err, filename);          // �Է¹��� ��¥ �ڿ� error�� ���̴� �ڵ�

    fp = fopen(p, "at+");           // at+���� ������ �ҷ��ͼ� ������ ������ ������ ���� �����ϰ�, ������ ������ ���� ���Ͽ� �̾ �ۼ�
    if (!is_empty(q)) {         // ť Ÿ���� ������� ���� ��� ���α׷��� ������
        int i = q->front;           // front ��ġ �̵�
        do {
            i = (i + 1) % (MAX_QUEUE_SIZE);         // i�� ���� i + 1 �� MAX(100)���� ���� ������ �̹Ƿ� i+1���� �� (ó�� �ѹ��� ����)
            fprintf(fp, "%d �� %s �� �����ȣ: %d\n", q->data[i].pen_cnt, q->data[i].pen_color, q->data[i].pen_id);       // fprintf�� ���Ͽ� �������
            if (i == q->rear)           // i�� ���� rear ���ԵǸ� �� �þ ���� �����Ƿ�
                break;              // break�� �ݺ��� Ż��
        } while (i != q->front);            // i ���� front���� �ƴϸ� ��� �ݺ�
    }
    printf("\n");           // �������� ���� �� ����

    error_cnt = red_error_cnt + blue_error_cnt + black_error_cnt;           // �ҷ�ǰ �� ���� = ��������ҷ� + �Ķ�����ҷ� + ��������ҷ�
    total_cnt = black_cnt + red_cnt + blue_cnt;             // �� ���� = �������� �� + �Ķ����� �� + �������� ��

    double error_percent = (double)error_cnt / (double)total_cnt * MAX;         // �ҷ����氳�� / �� ���氳���� �ҷ��� ���

    fprintf(fp, "�ҷ��� �� %.1lf %%\n", error_percent);         // ����� �ҷ����� ������������� ���Ͽ� ���
    fprintf(fp, "\n���ϻ��꺼�� %d��=> ��%d��, ��%d��, ��%d�� \n", total_cnt, black_cnt, red_cnt, blue_cnt);

    fclose(fp);         // �ۼ��� �Ϸ�� ������ ����
}

// ���� �Լ�
void enqueue(QueueType* q, element item)
{
    if (is_full(q))
        error("ť�� ��ȭ�����Դϴ�");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q)
{
    if (is_empty(q))
        error("ť�� ��������Դϴ�");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// ���� �Լ�
element peek(QueueType* q)
{
    if (is_empty(q))
        error("ť�� ��������Դϴ�");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void makefile(int n) {           // �Է¹��� ��¥�� �̸����� �ϴ� ������ �����ϴ� �Լ�
    FILE* fp;                   // �Է¹��� ��¥�� �������� �ϴ� ����
    FILE* total = fopen("total_report.txt", "at+");         // �� ����ǰ�� �����ϴ� ����
    QueueType pen;
    QueueType error;
    init_queue(&pen);
    init_queue(&error);
    char* p;                // �����̸��� ������ ����
    srand(time(NULL));          // rand()�� �������� �ݺ��Ǵ� ���� �����ϱ� ���� �ۼ�

    p = filename;               // �����̸��� ������
    fp = fopen(p, "at+");
    fprintf(fp, "\n");
    fprintf(total, "\n���� ��¥ : %s\n", filename);         // �� ����ǰ�� �����ϴ� ���Ͽ� �����̸�(=�Է¹��� ��¥)�� �Է�
    
    for (int i = n; i < n + MAX; i++) {             // max��ŭ �ݺ��Ͽ� max ��ŭ ���� ����

        int rand1 = rand();         // ������ ���� �ڵ�

        if (rand1 % 10 == 0) {          // 10���� ���� �������� 0�� Ȯ�� = 10%
            red_cnt++;              // �� ���� ���� ���� ( ������ ������ŭ red_cnt ����)
            if (rand() % 20 == 0) {            // 0���� 20-1 ������ �� �� �������� �̾��� �� 0�� ��� (5%Ȯ��)�϶� ����
                red_error_cnt++;            // �ҷ� ���� ���� �� ����
                element err_red;            // ����ü�� ����
                err_red.pen_cnt = i;            // ���� ���� ��ȣ (�������) ����
                err_red.pen_id = rand1;                 // ���� ���� id ����
                strcpy(err_red.pen_color, "����");            // ���� �������� ����
                enqueue(&error, err_red);               // ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
                // �ҷ����� ǥ���ؼ� �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_red.pen_cnt, err_red.pen_color, err_red.pen_id);
                // �� ����ǰ�� �����ϴ� ���Ͽ� ���
            }
            else {          // �������� ��� = �ҷ��� �ƴ� ���
                element red;            // ����ü ���� ����
                red.pen_cnt = i;            // ���� ��ȣ ����
                red.pen_id = rand1;         // ���� ���� id ����
                strcpy(red.pen_color, "����");            // ���� ���� ����
                enqueue(&pen, red);             // ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
                // ����� ������ �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d\n", red.pen_cnt, red.pen_color, red.pen_id);
                // ����� ������ �� ���귮 ���Ͽ� ���
            }
        }
        if (rand1 % 10 == 1) {              // 10���� ���� �������� 1�� ��� ( 10% Ȯ��)
            blue_cnt++;             // �� �Ķ� ���� �� ����
            if (rand() % 20 == 1) {             // 0���� 20-1������ �� �� �������� �̾��� �� 1�� ��� (5%Ȯ��)�� ����
                blue_error_cnt++;               // �ҷ� �Ķ� ���� �� ����
                element err_blue;           // ����ü�� ����
                err_blue.pen_cnt = i;           // ���� ��ȣ ����
                err_blue.pen_id = rand1;            // ���� ���� id ����
                strcpy(err_blue.pen_color, "�Ķ�");           // ���� ���� ����
                enqueue(&error, err_blue);              // �ҷ� �Ķ� ���� ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
                // �ҷ����� ǥ���ؼ� �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_blue.pen_cnt, err_blue.pen_color, err_blue.pen_id);
                // �� ����ǰ�� �����ϴ� ���Ͽ� ���
            }
            else {              // �������� ��� = �ҷ��� �ƴ� ���
                element blue;       // ����ü �Ķ� ����
                blue.pen_cnt = i;           // ���� ��ȣ ����
                blue.pen_id = rand1;            // ���� ���� id ����
                strcpy(blue.pen_color, "�Ķ�");           // ���� ���� ����
                enqueue(&pen, blue);            // ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
                // �ҷ����� ǥ���ؼ� �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d\n", blue.pen_cnt, blue.pen_color, blue.pen_id);
                // �� ����ǰ�� �����ϴ� ���Ͽ� ���
            }
        }
        if ((rand1 % 10 >= 2) && (rand1 % 10 <= 9)) {       // �� �̿��� ���(80%Ȯ��)
            black_cnt++;            // �� ������ ���� �� ����
            if (rand() % 20 == 0) {         // 0���� 20-1 ������ �� �� �������� �̾��� �� 0�� ��� (5%Ȯ��)�϶� ����
                black_error_cnt++;          // �ҷ� ���� ���� �� ����
                element err_black;          // ����ü�� ����
                err_black.pen_cnt = i;          // ���� ��ȣ ����
                err_black.pen_id = rand1;           // ���� ���� id ����
                strcpy(err_black.pen_color, "����");          // ���� ���� ����
                enqueue(&error, err_black);             // ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
                // �ҷ����� ǥ���ؼ� �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d -> �ҷ�\n", err_black.pen_cnt, err_black.pen_color, err_black.pen_id);
                //  �� ����ǰ�� �����ϴ� ���Ͽ� ���
            }
            else {          // �������� ��� = �ҷ��� �ƴ� ���
                element black;          // ������ ����ü ����
                black.pen_cnt = i;          // ���� ��ȣ ����
                black.pen_id = rand1;           // ���� ���� id ����
                strcpy(black.pen_color, "����");          // ���� ���� ����
                enqueue(&pen, black);           // ���
                fprintf(fp, "%d �� %s �� �����ȣ: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
                //  �ҷ����� ǥ���ؼ� �Է¹��� ��¥ ���Ͽ� ���
                fprintf(total, "%d �� %s �� �����ȣ: %d\n", black.pen_cnt, black.pen_color, black.pen_id);
                // �� ����ǰ�� �����ϴ� ���Ͽ� ���
            }
        }

    }
    fclose(fp);
    fclose(total);

    queue_print(&error);
}

void delay(clock_t n) {         // ���α׷������� ������ ����
                                // srand(time(NULL))�� ������� �� ���� �������� ������ ����
    clock_t start = clock();
    while (clock() - start < n);        // �Է��� �ð���ŭ �ݺ��Ͽ� delay(1)�� 1/1000�ʸ� ��������

}

int main() {
    element data[MAX];
    FILE* fp;       // Ư�� ��¥�� ������ ���� ������ �����ϴ� ������ ������
    char err[20] = "error";         // �Է¹��� ��¥�� ������ ���� �� �ҷ�ǰ�� �����ϴ� ������ �̸��� ����� ���� ����
    char txt[] = ".txt";        // �Է¹��� ��¥�� �̸����� �ϴ� �ؽ�Ʈ ������ ����� ���� ����
    char job[20] = "Jobs";
    char openfile1[MAX] = "notepad.exe ";       // �ؽ�Ʈ ���Ϸ� ����
    char openfile2[MAX] = "notepad.exe ";       // �ؽ�Ʈ ���Ϸ� ����
    // char openfile3[MAX] = "notepad.exe ";       // �ؽ�Ʈ ���Ϸ� ����
    char* p1, p2;
    lpt_element m = { 0, 0 };       // �۾� ��ȣ�� �۵� ������ �ð��� �ʱ�ȭ
    HeapType* h;
    h = create();       // ����Ʈ�� ����
    init(h);            // ����Ʈ�� �ʱ�ȭ

    printf("���ϴ� ��¥ �Է�(��������)>>");        // ��¥�� �Է¹޴� �ڵ�
    scanf("%s", &filename);             // �Է� ���� ��¥�� filename������ ������

    p1 = strcat(filename, txt);         // �Է¹��� ��¥�� �������� �ϴ� ���� ����
    fp = fopen(p1, "at+");            // ������ read ���� �ҷ���

    printf("������ �� �� ������Ű�ڽ��ϱ�? ");     // 100�� ���� ������ �� �� �� ������ �Է¹���
    int in, ary;
    scanf("%d", &in);       // �Է��� ���� ����
    ary = in * 3;           // �� �� ���� �� ����, ����, �Ķ� �������� �� 3�� �۾��� �ϹǷ� *3�� ��
    int i = 0, j = 0;           // i, j �ʱ�ȭ

    printf("�����̰� �ֽ��ϴ�. ��ø� ��ٷ��ּ���.\n");     // srand(time(NULL))�� ������ ���� �� ���� ���� ����
                                                          // ������ ������ ���ϱ� ���� �����̸� ����

    int tmp;            // �ɸ� �ð��� ������ �ӽ� ����
    char tmp2[MAX];          // ���ڿ� ������ �ӽ� ����
   
    for (int k = 0; k < in; k++) {      // �Է��� ����ŭ 100�� ���� ���� �ݺ�
        makefile(k * 100);          // �ݺ����� �� * 100���� �Ű� ������ ���� �Ѱ���
        data[i].time = black_cnt * 1;  //���������� ���� 1��
        strcpy(data[i].pen_color, "����");        // ������ �������� �迭�� ����
        i++;
        data[i].time = red_cnt * 2;      //���� ������ ���� 2��
        strcpy(data[i].pen_color, "����");        // ������ �������� �迭�� ����
        i++;
        data[i].time = blue_cnt * 2;    //�Ķ� ������ ���� 2��
        strcpy(data[i].pen_color, "�Ķ�");        // �Ķ��� �������� �迭�� ����
        i++;
        black_cnt = red_cnt = blue_cnt = 0;     // �ѹ� 100�� ���� ������ �� �Ŀ��� ���� �ݺ��� ����
        black_error_cnt = red_error_cnt = blue_error_cnt = 0;       // �� ���� �ʱ�ȭ ����
        printf("delay %d��...\n", in - k);       // Ȥ�� �� ������ �߿� ���Ḧ �����ϱ� ���� ������ �ǰ� ������ ���
        delay(1000);        //srand(time(NULL))���� �������� �޸����ֱ����� delay�� ��
    }
    for (int j = 0; j < i; j++) {   //���������� ���� ���� ���꿡 �ɸ� �ð��� ������
        for (int k = 0; k < i - j; k++) {       // lpt �˰����� ������ ���ؼ��� �����Ͱ� ���ĵǾ�� �ϹǷ�
            if (data[k].time < data[k + 1].time) {      // ������������ ������
                tmp = data[k].time;
                strcpy(tmp2, (data + k)->pen_color);

                data[k].time = data[k + 1].time;
                strcpy(data[k].pen_color, data[k + 1].pen_color);

                data[k + 1].time = tmp;
                strcpy(data[k + 1].pen_color, tmp2);
            }
        }
    }
    // avail ���� ��谡 ��� �����ϰ� �Ǵ� �ð�e
    for (int a = 0; a < MACHINES; a++) {
        m.id = a + 1;
        m.avail = 0;
        insert_min_heap(h, m);
    }
    // �ּ� �������� ��踦 ������ �۾��� �Ҵ��ϰ� ��밡�� �ð��� ���� ��Ų �Ŀ� 
    // �ٽ� �ּ� ������ �߰�
    fprintf(fp, "\n");      // �������� ���� �ٶ���

    for (int a = 0; a < i; a++) {       // lpt.c�� �ִ� �˰����� �״�� ������
        m = delete_min_heap(h);     // JOB ��� � �������� �����
        fprintf(fp, "% s�� �ð� = % d�ʺ��� �ð� = % d�ʱ��� ��� % d���� �Ҵ��Ѵ�. \n", (data + a)->pen_color, m.avail, m.avail + (data + a)->time - 1, m.id);
        m.avail += (data + a)->time;
        insert_min_heap(h, m);
    }

    fclose(fp);
    system(strcat(openfile1, filename));   //�Է��� ��¥�� �ش��ϴ� ���� ���� //openfile1 = "notepad.exe filename.txt"

    strcat(err, filename);
    system(strcat(openfile2, err));    //�ҷ�ǰ�� ���� ������ ���� ����  //openfile2 = "notepad.exe errorfilename.txt"

    system("notepad.exe total_report.txt");         //��¥�� ������� ���±����� ��� ����ǰ�� ����� ���� ����
    return 0;
}