#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Sequence_T {
    int num;
    int* elements;
} Sequence;

typedef struct SeqNode_T {
    Sequence* pSeq;
    struct SeqNode_T* pNextNode;
} SeqNode;

int main () {
    SeqNode* pStartNode = NULL;
    SeqNode* pIndexNode = NULL;
    int elemNum = 0;

    while (scanf("%d", &elemNum) == 1) {
        int elemIndex = 0;
        SeqNode* pNewNode = (SeqNode*)malloc(sizeof(SeqNode));
        pNewNode->pNextNode = NULL;
        pNewNode->pSeq = (Sequence*)malloc(sizeof(Sequence));
        pNewNode->pSeq->num = elemNum;

        if (elemNum <= 0) {
            pNewNode->pSeq->elements = NULL;
        }
        else {
            pNewNode->pSeq->elements = (int*)malloc(elemNum*sizeof(int));

            for (elemIndex = 0; elemIndex < elemNum; elemIndex++) {
                scanf(" %d", &(pNewNode->pSeq->elements[elemIndex]));
            }
        }

        if (pStartNode == NULL) {
            pStartNode = pNewNode;
        }
        else {
            pIndexNode->pNextNode = pNewNode;
        }

        pIndexNode = pNewNode;
    }

    pIndexNode = pStartNode;

    while (pIndexNode != NULL) {
        if (pIndexNode->pSeq->num <= 0) {
            printf("Not jolly\n");
        }
        else if (pIndexNode->pSeq->num == 1) {
            printf("Jolly\n");
        }
        else {
            int index = 0, jolly = 1;
            int* elemDiff = (int*)malloc((pIndexNode->pSeq->num-1)*sizeof(int));

            memset(elemDiff, 0, (pIndexNode->pSeq->num-1)*sizeof(int));

            for (index = 1; index < pIndexNode->pSeq->num; index++) {
                int diff = abs(pIndexNode->pSeq->elements[index] - pIndexNode->pSeq->elements[index-1]);

                if ((diff > 0) && (diff < pIndexNode->pSeq->num)) {
                    if (elemDiff[diff-1] > 0) {
                        jolly = 0;
                        break;
                    }
                    else {
                        elemDiff[diff-1]++;
                    }
                }
                else {
                    jolly = 0;
                    break;
                }
            }

            if (jolly == 1) {
                for (index = 0; index < pIndexNode->pSeq->num-1; index++) {
                    if (elemDiff[index] != 1) {
                        jolly = 0;
                        break;
                    }
                }

                if (jolly == 1) {
                    printf("Jolly\n");
                }
                else {
                    printf("Not jolly\n");
                }
            }
            else {
                printf("Not jolly\n");
            }

            free(elemDiff);
        }

        pIndexNode = pIndexNode->pNextNode;
    }

    pIndexNode = pStartNode;

    while (pIndexNode != NULL) {
        pStartNode = pIndexNode->pNextNode;
        free(pIndexNode->pSeq->elements);
        free(pIndexNode->pSeq);
        free(pIndexNode);
        pIndexNode = pStartNode;
    }

    return 0;
}
