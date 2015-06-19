#include <stdio.h>

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
    return 0;
}
