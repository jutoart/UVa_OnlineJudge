#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NumSet_T {
    int num;
    int* pElements;
} NumSet;

typedef struct NumSetNode_T {
    NumSet* pSet;
    struct NumSetNode_T* pNextNode;
} NumSetNode;

typedef struct TwoNumSumNode_T {
    int sum;
    int firstNumIndex;
    int secondNumIndex;
} TwoNumSum;

void Swap_Integer (int* px, int* py) {
    int temp = *px;
    *px = *py;
    *py = temp;
    return;
}

void QuickSort_Integer (int* pNumArray, int arrayLength) {
    int index = 0, pivot = 0;

    if (arrayLength <= 1) {
        return;
    }

    for (index = 0; index < arrayLength; index++) {
        if (((index > pivot) && (pNumArray[index] < pNumArray[pivot])) ||
                ((index < pivot) && (pNumArray[index] > pNumArray[pivot]))) {
            Swap_Integer(&(pNumArray[index]), &(pNumArray[pivot]));
            pivot = index;
        }
    }

    if (pivot > 0) {
        QuickSort_Integer(pNumArray, pivot);
    }

    if (pivot < arrayLength - 1) {
        QuickSort_Integer(&(pNumArray[pivot+1]), arrayLength - 1 - pivot);
    }

    return;
}

void Swap_TwoNumSum (TwoNumSum* px, TwoNumSum* py) {
    TwoNumSum temp = *px;
    *px = *py;
    *py = temp;
    return;
}

void QuickSort_TwoNumSum (TwoNumSum* pArray, int arrayLength) {
    int index = 0, pivot = 0;

    if (arrayLength <= 1) {
        return;
    }

    for (index = 0; index < arrayLength; index++) {
        if (((index > pivot) && (pArray[index].sum < pArray[pivot].sum)) ||
                ((index < pivot) && (pArray[index].sum > pArray[pivot].sum))) {
            Swap_TwoNumSum(&(pArray[index]), &(pArray[pivot]));
            pivot = index;
        }
    }

    if (pivot > 0) {
        QuickSort_TwoNumSum(pArray, pivot);
    }

    if (pivot < arrayLength - 1) {
        QuickSort_TwoNumSum(&(pArray[pivot+1]), arrayLength - 1 - pivot);
    }

    return;
}

int BinarySearchSumArray (TwoNumSum* pArray, int arrayLength, int searchNum) {
    int index = arrayLength / 2;

    while (index > 0) {
        if (pArray[index-1].sum == searchNum) {
            index--;
        }
        else {
            break;
        }
    }

    printf("searched %d for %d\n", pArray[index].sum, searchNum);

    if (pArray[index].sum == searchNum) {
        return index;
    }
    else {
        if (index == 0) {
            return -1;
        }
        else {
            int leftResult = BinarySearchSumArray(pArray, index, searchNum);
            int rightResult = -1;

            if (leftResult != -1) {
                return leftResult;
            }

            if (index != arrayLength - 1) {
                rightResult = BinarySearchSumArray(&(pArray[index+1]), arrayLength - 1 - index, searchNum);

                if (rightResult != -1) {
                    rightResult = rightResult + index + 1;
                }
            }

            return rightResult;
        }
    }
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

        QuickSort_Integer(pNewSetNode->pSet->pElements, num);

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
        int firstNumIndex = 0, secondNumIndex = 0, count = 0, arrayLength = 0;
        int solutionFound = 0;
        TwoNumSum* pSumArray = NULL;

        if (pIndexSetNode->pSet->num < 4) {
            printf("no solution\n");
            continue;
        }

        arrayLength = (pIndexSetNode->pSet->num * (pIndexSetNode->pSet->num - 1)) / 2;
        pSumArray = (TwoNumSum*)malloc(arrayLength*sizeof(TwoNumSum));
        memset(pSumArray, 0, sizeof(arrayLength*sizeof(TwoNumSum)));

        printf("%d\n", pIndexSetNode->pSet->num);
        printf("array length = %d\n", arrayLength);

        for (firstNumIndex = 0; firstNumIndex < pIndexSetNode->pSet->num - 1; firstNumIndex++) {
            for (secondNumIndex = firstNumIndex + 1; secondNumIndex < pIndexSetNode->pSet->num; secondNumIndex++) {
                pSumArray[count].sum = pIndexSetNode->pSet->pElements[firstNumIndex] + pIndexSetNode->pSet->pElements[secondNumIndex];
                pSumArray[count].firstNumIndex = firstNumIndex;
                pSumArray[count].secondNumIndex = secondNumIndex;
                printf("sum=%d, a=%d, b=%d\n", pSumArray[count].sum, firstNumIndex, secondNumIndex);
                count++;
            }
        }

        QuickSort_TwoNumSum(pSumArray, arrayLength);
        printf("array length = %d\n", arrayLength);
        solutionFound = 0;

        for (firstNumIndex = pIndexSetNode->pSet->num - 1; firstNumIndex >= 0; firstNumIndex--) {
            for (secondNumIndex = 0; secondNumIndex < pIndexSetNode->pSet->num; secondNumIndex++) {
                int sumIndex = 0;

                if (firstNumIndex == secondNumIndex) {
                    continue;
                }

                printf("try d=%d, c=%d\n", pIndexSetNode->pSet->pElements[firstNumIndex], pIndexSetNode->pSet->pElements[secondNumIndex]);
                printf("array length = %d\n", arrayLength);

                sumIndex = BinarySearchSumArray(pSumArray, arrayLength, pIndexSetNode->pSet->pElements[firstNumIndex] - pIndexSetNode->pSet->pElements[secondNumIndex]);

                if (sumIndex >= 0) {
                    printf("found %d length=%d\n", sumIndex, arrayLength);

                    while (sumIndex < arrayLength) {
                        if (pSumArray[sumIndex].sum != pIndexSetNode->pSet->pElements[firstNumIndex] - pIndexSetNode->pSet->pElements[secondNumIndex]) {
                            break;
                        }

                        printf("a=%d, b=%d, c=%d, d=%d\n", pSumArray[sumIndex].firstNumIndex, pSumArray[sumIndex].secondNumIndex, secondNumIndex, firstNumIndex);

                        if ((pSumArray[sumIndex].firstNumIndex != firstNumIndex) &&
                                (pSumArray[sumIndex].firstNumIndex != secondNumIndex) &&
                                (pSumArray[sumIndex].secondNumIndex != firstNumIndex) &&
                                (pSumArray[sumIndex].secondNumIndex != secondNumIndex)) {
                            printf("%d\n", pIndexSetNode->pSet->pElements[firstNumIndex]);
                            solutionFound = 1;
                            break;
                        }

                        sumIndex++;
                    }
                }

                if (solutionFound == 1) {
                    break;
                }
            }

            if (solutionFound == 1) {
                break;
            }
        }

        if (solutionFound == 0) {
            printf("no solution\n");
        }

        free(pSumArray);
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
