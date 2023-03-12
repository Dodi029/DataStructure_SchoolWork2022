//
// Created by 박현준 on 2022/05/23.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "calculatorSetValue.h"

int getLayerCount(int nodeCount) {
    int result = 0;
    int boundary = 1;

    while (nodeCount > 0) {
        nodeCount -= boundary;
        result++;
        boundary *= 2;
    }

    return result;
}

boolean *orderArrayInit(int elementCount) {
    boolean *order = malloc(sizeof(boolean) * elementCount);
    for (int i = 0; i < elementCount; i++) {
        order[i] = 0;
    }
    return order;
}

int getRandomOperand() {
    return rand() % OPERAND_MAX;
}

int getRandomOperator() {
    char operator[] = {'+', '-', '*', '/'};

    return operator[rand() % 4];
}

void execute(FILE *inputFile) {
    const int NUMBER_OF_LAYER = getLayerCount(NUMBER_OF_NODE);
    boolean *orderArray = orderArrayInit(NUMBER_OF_LAYER);

    int pivot = 0;

    while (pivot != NUMBER_OF_NODE) {
        fprintf(inputFile, "%d\n", getRandomOperand());
        fprintf(inputFile, "%d\n", getRandomOperand());
        pivot += 2;
        orderArray[0] = 2;

        for (int i = 0; i < NUMBER_OF_LAYER - 1; i++) {
            if (orderArray[i] == 2) {
                fprintf(inputFile, "%c\n", getRandomOperator());
                orderArray[i] = 0;
                orderArray[i + 1]++;
                pivot++;
            }
        }
    }

    free(orderArray);
}

int main() {
    srand(NULL);
    FILE *inputFile = fopen("input.txt", "w");

    execute(inputFile);

    fclose(inputFile);
    return 0;
}


