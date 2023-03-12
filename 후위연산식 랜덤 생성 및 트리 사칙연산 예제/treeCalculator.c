//
// Created by 박현준 on 2022/05/23.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "calculatorSetValue.h"

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

int getNextData(FILE *file) {
    char input[10];
    fscanf(file, "%s", &input);

    if ('0' <= input[0] && input[0] <= '9') {
        return atoi(input);
    }
    return input[0];
}

void setRelation(Node *tree, int pivot, int leftTierGap) {

    if (leftTierGap == 1) {
        return;
    }

    tree[pivot].left = tree + (pivot - leftTierGap);
    tree[pivot].right = tree + pivot - 1;

    setRelation(tree, (pivot - leftTierGap), leftTierGap / 2);
    setRelation(tree, (pivot - 1), leftTierGap / 2);
}

int evaluate(Node *pivot, FILE *file) {
    if (pivot == NULL)
        return 0;
    if (pivot->left == NULL && pivot->right == NULL)
        return pivot->data;
    else {
        int op1 = evaluate(pivot->left, file);
        int op2 = evaluate(pivot->right, file);
        fprintf(file, "%d %c %d을 계산합니다.\n", op1, pivot->data, op2);
        switch (pivot->data) {
            case '+':
                return op1 + op2;
            case '-':
                return op1 - op2;
            case '*':
                return op1 * op2;
            case '/':
                return op1 / op2;
        }
    }
    return 0;
}

int main() {
    Node *tree = malloc(sizeof(Node) * NUMBER_OF_NODE);
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "a+");

    setRelation(tree, NUMBER_OF_NODE - 1, (NUMBER_OF_NODE / 2) + 1);

    for (int i = 0; i < NUMBER_OF_NODE; i++) {
        tree[i].data = getNextData(inputFile);
    }

    int result = evaluate(tree + NUMBER_OF_NODE - 1, outputFile);

    fprintf(outputFile, "수식의 값은 %d입니다. \n", result);

    fclose(inputFile);
    fclose(outputFile);
    free(tree);

    return 0;
}
