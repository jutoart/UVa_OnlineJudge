#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 1000000

typedef struct NumSet_T {
    int firstNum;
    int secondNum;
} NumSet;

typedef struct LinkedListNode_T {
    NumSet* pNumSet;
    struct LinkedListNode_T* pNextNode;
} LinkedListNode;

typedef struct NumListNode_T {
    int number;
    struct NumListNode_T* pNextNode;
} NumListNode;

void AppendLinkedListNode (LinkedListNode** ppLastNode, LinkedListNode* pNewNode) {
    (*ppLastNode)->pNextNode = pNewNode;
    *ppLastNode = pNewNode;
    return;
}

int main () {
    LinkedListNode* pStartNode = NULL;
    LinkedListNode* pIndexNode = NULL;
    int countBuf[MAX_NUM] = {0};

    countBuf[0] = 1;

    while (1) {
        int inputFirstNum = 0, inputSecondNum = 0;
        NumSet* pNewNumSet = NULL;
        LinkedListNode* pNewNode = NULL;

        if (scanf("%d %d", &inputFirstNum, &inputSecondNum) != 2) {
            break;
        }

        pNewNumSet = (NumSet*)malloc(sizeof(NumSet));
        pNewNumSet->firstNum = inputFirstNum;
        pNewNumSet->secondNum = inputSecondNum;
        pNewNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
        pNewNode->pNumSet = pNewNumSet;

        if (pStartNode == NULL) {
            pStartNode = pNewNode;
            pIndexNode = pStartNode;
        }
        else {
            AppendLinkedListNode(&pIndexNode, pNewNode);
        }
    }

    pIndexNode = pStartNode;

    while (pIndexNode != NULL) {
        int index = 0, maxCount = 0, startNum = 0, endNum = 0;

        if (pIndexNode->pNumSet->firstNum <= pIndexNode->pNumSet->secondNum) {
            startNum = pIndexNode->pNumSet->firstNum;
            endNum = pIndexNode->pNumSet->secondNum;
        }
        else {
            startNum = pIndexNode->pNumSet->secondNum;
            endNum = pIndexNode->pNumSet->firstNum;
        }

        for (index = startNum; index <= endNum; index++) {
            int num = index;
            NumListNode* pStartNumNode = NULL;

            while (num > 0) {
                if ((num < MAX_NUM) && (countBuf[num-1] > 0)) {
                    int count = countBuf[num-1];

                    while(pStartNumNode != NULL) {
                        NumListNode* pCurNumNode = pStartNumNode;

                        count++;

                        if (pStartNumNode->number < MAX_NUM) {
                            countBuf[pStartNumNode->number-1] = count;
                        }

                        pStartNumNode = pStartNumNode->pNextNode;
                        free(pCurNumNode);
                    }

                    break;
                }
                else {
                    NumListNode* pNewNumNode = (NumListNode*)malloc(sizeof(NumListNode));

                    pNewNumNode->number = num;
                    pNewNumNode->pNextNode = pStartNumNode;
                    pStartNumNode = pNewNumNode;

                    if (num % 2 == 0) {
                        num = num >> 1;
                    }
                    else {
                        num = num * 3 + 1;
                    }
                }
            }

            if (maxCount < countBuf[index-1]) {
                maxCount = countBuf[index-1];
            }
        }

        printf("%d %d %d\n", pIndexNode->pNumSet->firstNum, pIndexNode->pNumSet->secondNum, maxCount);

        pIndexNode = pIndexNode->pNextNode;
    }

    pIndexNode = pStartNode;

    while (pIndexNode != NULL) {
        LinkedListNode* pNextNode = pIndexNode->pNextNode;

        free(pIndexNode->pNumSet);
        free(pIndexNode);
        pIndexNode = pNextNode;
    }

    return 0;
}
