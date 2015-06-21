#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DNA_LETTER_COUNT 4

typedef struct DataSet_T {
    int strLength;
    int strNum;
    int** ppStrInNumForm;
    int* pStrUnsortedness;
} DataSet;

typedef struct DataSetNode_T {
    DataSet* pDataSet;
    struct DataSetNode_T* pNextNode;
} DataSetNode;

void QuickSort_StrUnsortedness (DataSet* pDataSet, int start, int end) {
    int index = 0, count = 0, pivot = 0;
    int* pNewUnsortedness = NULL;
    int** ppNewStrData = NULL;

    if (end - start < 1) {
        return;
    }

    pNewUnsortedness = (int*)malloc((end-start+1)*sizeof(int));
    ppNewStrData = (int**)malloc((end-start+1)*sizeof(int*));

    printf("start=%d, end=%d\n", start, end);
    printf("Sort:");

    for (index = start; index <= end; index++) {
        printf(" %d", pDataSet->pStrUnsortedness[index]);
    }

    printf("\n");

    for (index = start + 1; index <= end; index++) {
        if (pDataSet->pStrUnsortedness[index] < pDataSet->pStrUnsortedness[start]) {
            pNewUnsortedness[count] = pDataSet->pStrUnsortedness[index];
            ppNewStrData[count] = pDataSet->ppStrInNumForm[index];
            count++;
        }
    }

    pivot = start + count;
    pNewUnsortedness[count] = pDataSet->pStrUnsortedness[start];
    ppNewStrData[count] = pDataSet->ppStrInNumForm[start];
    count++;

    for (index = start + 1; index <= end; index++) {
        if (pDataSet->pStrUnsortedness[index] >= pDataSet->pStrUnsortedness[start]) {
            pNewUnsortedness[count] = pDataSet->pStrUnsortedness[index];
            ppNewStrData[count] = pDataSet->ppStrInNumForm[index];
            count++;
        }
    }

    printf("After sort:");

    for (index = 0; index <= end - start; index++) {
        pDataSet->pStrUnsortedness[start+index] = pNewUnsortedness[index];
        pDataSet->ppStrInNumForm[start+index] = ppNewStrData[index];
        printf(" %d", pNewUnsortedness[index]);
    }

    printf("\n");
    printf("pivot=%d\n", pivot);

    free(pNewUnsortedness);
    free(ppNewStrData);
    QuickSort_StrUnsortedness(pDataSet, start, pivot-1);
    QuickSort_StrUnsortedness(pDataSet, pivot+1, end);
    return;
}

int CalculateUnsortedness (int* pSequence, int length) {
    int index = 0, unsortedness = 0;
    int letterCount[DNA_LETTER_COUNT] = {0};
    int startPosition[DNA_LETTER_COUNT] = {0};
    int notInPosCount[DNA_LETTER_COUNT] = {0};

    for (index = 0; index < length; index++) {
        letterCount[pSequence[index]]++;
    }

    for (index = 1; index < DNA_LETTER_COUNT; index++) {
        startPosition[index] = letterCount[index-1] + startPosition[index-1];
    }

    for (index = 0; index < length; index++) {
        int i = 0, actualPosition = index;

        for (i = pSequence[index] + 1; i < DNA_LETTER_COUNT; i++) {
            actualPosition -= notInPosCount[i];
        }

        if (actualPosition < startPosition[pSequence[index]]) {
            unsortedness += (startPosition[pSequence[index]] - actualPosition);
            notInPosCount[pSequence[index]]++;
        }

        startPosition[pSequence[index]]++;
    }

    return unsortedness;
}

int main () {
    char DNA_letters[DNA_LETTER_COUNT] = {'A', 'C', 'G', 'T'};
    DataSetNode* pStartDataSetNode = NULL;
    DataSetNode* pIndexDataSetNode = NULL;
    int dataSetNum = 0, index = 0;

    scanf("%d", &dataSetNum);

    for (index = 0; index < dataSetNum; index++) {
        int strIndex = 0, chrIndex = 0;
        DataSetNode* pNewDataSetNode = NULL;

        pNewDataSetNode = (DataSetNode*)malloc(sizeof(DataSetNode));
        pNewDataSetNode->pNextNode = NULL;
        pNewDataSetNode->pDataSet = (DataSet*)malloc(sizeof(DataSet));

        scanf("");
        scanf("%d %d", &(pNewDataSetNode->pDataSet->strLength), &(pNewDataSetNode->pDataSet->strNum));

        pNewDataSetNode->pDataSet->ppStrInNumForm = (int**)malloc(pNewDataSetNode->pDataSet->strNum*sizeof(int*));
        memset(pNewDataSetNode->pDataSet->ppStrInNumForm, 0, pNewDataSetNode->pDataSet->strNum*sizeof(int*));
        pNewDataSetNode->pDataSet->pStrUnsortedness = (int*)malloc(pNewDataSetNode->pDataSet->strNum*sizeof(int));
        memset(pNewDataSetNode->pDataSet->pStrUnsortedness, 0, pNewDataSetNode->pDataSet->strNum*sizeof(int));

        for (strIndex = 0; strIndex < pNewDataSetNode->pDataSet->strNum; strIndex++) {
            pNewDataSetNode->pDataSet->ppStrInNumForm[strIndex] = (int*)malloc(pNewDataSetNode->pDataSet->strLength*sizeof(int));
            memset(pNewDataSetNode->pDataSet->ppStrInNumForm[strIndex], 0, pNewDataSetNode->pDataSet->strLength*sizeof(int));

            for (chrIndex = 0; chrIndex < pNewDataSetNode->pDataSet->strLength; chrIndex++) {
                char inputCh = getchar();

                while (1) {
                    if (inputCh == 'A') {
                        pNewDataSetNode->pDataSet->ppStrInNumForm[strIndex][chrIndex] = 0;
                        break;
                    }
                    else if (inputCh == 'C') {
                        pNewDataSetNode->pDataSet->ppStrInNumForm[strIndex][chrIndex] = 1;
                        break;
                    }
                    else if (inputCh == 'G') {
                        pNewDataSetNode->pDataSet->ppStrInNumForm[strIndex][chrIndex] = 2;
                        break;
                    }
                    else if (inputCh == 'T') {
                        pNewDataSetNode->pDataSet->ppStrInNumForm[strIndex][chrIndex] = 3;
                        break;
                    }
                    else {
                        inputCh = getchar();
                        continue;
                    }
                }
            }
        }

        if (pStartDataSetNode == NULL) {
            pStartDataSetNode = pNewDataSetNode;
        }
        else {
            pIndexDataSetNode->pNextNode = pNewDataSetNode;
        }

        pIndexDataSetNode = pNewDataSetNode;
    }

    pIndexDataSetNode = pStartDataSetNode;

    while (pIndexDataSetNode != NULL) {
        int strIndex = 0;
        int* pNewUnsortedness = (int*)malloc(pIndexDataSetNode->pDataSet->strNum*sizeof(int));
        int** ppNewStrData = (int**)malloc(pIndexDataSetNode->pDataSet->strNum*sizeof(int*));

        for (strIndex = 0; strIndex < pIndexDataSetNode->pDataSet->strNum; strIndex++) {
            pIndexDataSetNode->pDataSet->pStrUnsortedness[strIndex] = CalculateUnsortedness(pIndexDataSetNode->pDataSet->ppStrInNumForm[strIndex], pIndexDataSetNode->pDataSet->strLength);
        }

        QuickSort_StrUnsortedness(pIndexDataSetNode->pDataSet, 0, pIndexDataSetNode->pDataSet->strNum-1);
        pIndexDataSetNode = pIndexDataSetNode->pNextNode;
    }

    pIndexDataSetNode = pStartDataSetNode;

    while (pIndexDataSetNode != NULL) {
        int strIndex = 0, chrIndex = 0;

        for (strIndex = 0; strIndex < pIndexDataSetNode->pDataSet->strNum; strIndex++) {
            for (chrIndex = 0; chrIndex < pIndexDataSetNode->pDataSet->strLength; chrIndex++) {
                printf("%c", DNA_letters[pIndexDataSetNode->pDataSet->ppStrInNumForm[strIndex][chrIndex]]);
            }

            printf(" %d\n", pIndexDataSetNode->pDataSet->pStrUnsortedness[strIndex]);
        }

        if (dataSetNum > 1) {
            printf("\n");
        }

        pIndexDataSetNode = pIndexDataSetNode->pNextNode;
    }

    pIndexDataSetNode = pStartDataSetNode;

    while (pIndexDataSetNode != NULL) {
        int strIndex = 0;

        pStartDataSetNode = pIndexDataSetNode->pNextNode;

        for (strIndex = 0; strIndex < pIndexDataSetNode->pDataSet->strNum; strIndex++) {
            free(pIndexDataSetNode->pDataSet->ppStrInNumForm[strIndex]);
        }

        free(pIndexDataSetNode->pDataSet->ppStrInNumForm);
        free(pIndexDataSetNode->pDataSet);
        free(pIndexDataSetNode);
        pIndexDataSetNode = pStartDataSetNode;
    }

    return 0;
}
