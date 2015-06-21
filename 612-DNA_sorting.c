#include <stdio.h>
#include <stdlib.h>

#define DNA_LETTER_COUNT 4

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
    return 0;
}
