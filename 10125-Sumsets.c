#include <stdio.h>
#include <stdlib.h>

typedef struct NumSet_T {
    int num;
    int* pElements;
} NumSet;

typedef struct NumSetNode_T {
    NumSet* pSet;
    struct NumSetNode_T* pNextNode;
} NumSetNode;

void Swap (int* px, int* py) {
    int temp = *px;
    *px = *py;
    *py = temp;
    return;
}

void QuickSort (int* pNumArray, int arrayLength) {
    int index = 0, pivot = 0;

    if (arrayLength <= 1) {
        return;
    }

    for (index = 0; index < arrayLength; index++) {
        if (((index > pivot) && (pNumArray[index] < pNumArray[pivot])) ||
                ((index < pivot) && (pNumArray[index] > pNumArray[pivot]))) {
            Swap(&(pNumArray[index]), &(pNumArray[pivot]));
            pivot = index;
        }
    }

    if (pivot > 0) {
        QuickSort(pNumArray, pivot);
    }

    if (pivot < arrayLength - 1) {
        QuickSort(&(pNumArray[pivot+1]), arrayLength - 1 - pivot);
    }

    return;
}

int main () {
    int num = 0;
    NumSetNode* pInputSetList = NULL;
    NumSetNode* pIndexSetNode = NULL;

    scanf("%d", &num);

    while (num > 0) {
        int index = 0;
        NumSetNode* pNewSetNode = (NumSetNode*)malloc(sizeof(NumSetNode));
        pNewSetNode->pSet = (NumSet*)malloc(sizeof(NumSet));
        pNewSetNode->pNextNode = NULL;
        pNewSetNode->pSet->num = num;
        pNewSetNode->pSet->pElements = (int*)malloc(num*sizeof(int));

        for (index = 0; index < num; index++) {
            scanf("%d", &(pNewSetNode->pSet->pElements[index]));
        }

        if (pInputSetList == NULL) {
            pInputSetList = pNewSetNode;
        }
        else {
            pIndexSetNode->pNextNode = pNewSetNode;
        }

        pIndexSetNode = pNewSetNode;
        scanf("%d", &num);
    }

    pIndexSetNode = pInputSetList;

    while (pIndexSetNode != NULL) {
        int index = 0;

        printf("%d\n", pIndexSetNode->pSet->num);

        for (index = 0; index < pIndexSetNode->pSet->num; index++) {
            printf("%d ", pIndexSetNode->pSet->pElements[index]);
        }

        printf("\n");
        pIndexSetNode = pIndexSetNode->pNextNode;
    }

    while (pIndexSetNode != NULL) {
        pIndexSetNode = pInputSetList;
        pInputSetList = pIndexSetNode->pNextNode;
        free(pIndexSetNode->pSet);
        free(pIndexSetNode);
    }

    return 0;
}
