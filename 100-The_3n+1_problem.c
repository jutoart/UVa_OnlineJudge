#include <stdio.h>
#include <stdlib.h>

typedef struct NumSet_T {
    int firstNum;
    int secondNum;
} NumSet;

typedef struct LinkedListNode_T {
    NumSet* pNumSet;
    struct LinkedListNode_T* pNextNode;
} LinkedListNode;

void AppendLinkedListNode (LinkedListNode** ppLastNode, LinkedListNode* pNewNode) {
    (*ppLastNode)->pNextNode = pNewNode;
    *ppLastNode = pNewNode;
    return;
}

int main () {
    LinkedListNode* pStartNode = NULL;
    LinkedListNode* pIndexNode = NULL;

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
            int count = 1;
            int num = index;

            while (num > 1) {
                if (num % 2 == 0) {
                    num = num >> 1;
                    count++;
                }
                else {
                    num = ((num + 1) >> 1) + num;
                    count += 2;
                }
            }

            if (maxCount < count) {
                maxCount = count;
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
