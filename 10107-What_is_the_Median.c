#include <stdio.h>

#define MAX_INPUT_NUM 10000

typedef int (*CompareFunc) (unsigned int x, unsigned int y);

int CompareLess (unsigned int x, unsigned int y) {
    return ((x < y) ? 1 : 0);
}

int CompareGreater (unsigned int x, unsigned int y) {
    return ((x > y) ? 1 : 0);
}

void UpHeap (unsigned int* heap, int size, CompareFunc Compare) {
    int index = size - 1;

    if (heap == NULL) {
        return;
    }

    while ((index != 0) && Compare(heap[index], heap[(index+1)/2-1])) {
        unsigned int temp = heap[index];
        heap[index] = heap[(index+1)/2-1];
        heap[(index+1)/2-1] = temp;
        index = (index + 1) / 2 - 1;
    }

    return;
}

void DownHeap (unsigned int* heap, int size, CompareFunc Compare) {
    int index = 0;

    if (heap == NULL) {
        return;
    }

    while (1) {
        if ((index + 1) * 2 - 1 >= size) {
            break;
        }
        else {
            if(Compare(heap[index], heap[(index+1)*2-1])) {
                unsigned int temp = heap[index];
                heap[index] = heap[(index+1)*2-1];
                heap[(index+1)*2-1] = temp;
                index = (index + 1) * 2 - 1;
                continue;
            }
        }

        if ((index + 1) * 2 >= size) {
            break;
        }
        else {
            if(Compare(heap[index], heap[(index+1)*2])) {
                unsigned int temp = heap[index];
                heap[index] = heap[(index+1)*2];
                heap[(index+1)*2] = temp;
                index = (index + 1) * 2;
                continue;
            }
            else {
                break;
            }
        }
    }

    return;
}

int main () {
    int minHeapSize = 0;
    int maxHeapSize = 0;
    unsigned int minHeap[MAX_INPUT_NUM/2] = {0};
    unsigned int maxHeap[MAX_INPUT_NUM/2] = {0};
    unsigned int input = 0;

    while (scanf("%u", &input) == 1) {
        if (maxHeapSize == 0) {
            maxHeap[0] = input;
            maxHeapSize++;
            printf("%d\n", input);
            continue;
        }
        else {
            if (input <= maxHeap[0]) {
                if (maxHeapSize > minHeapSize) {
                    minHeap[minHeapSize] = maxHeap[0];
                    minHeapSize++;
                    UpHeap(minHeap, minHeapSize, CompareLess);
                    maxHeap[0] = input;
                    DownHeap(maxHeap, maxHeapSize, CompareLess);
                }
                else {
                    maxHeap[maxHeapSize] = input;
                    maxHeapSize++;
                    UpHeap(maxHeap, maxHeapSize, CompareGreater);
                }
            }
            else {
                if (minHeapSize > maxHeapSize) {
                    maxHeap[maxHeapSize] = minHeap[0];
                    maxHeapSize++;
                    UpHeap(maxHeap, maxHeapSize, CompareGreater);
                    minHeap[0] = input;
                    DownHeap(minHeap, minHeapSize, CompareGreater);
                }
                else {
                    minHeap[minHeapSize] = input;
                    minHeapSize++;
                    UpHeap(minHeap, minHeapSize, CompareLess);
                }
            }
        }

        if (maxHeapSize == minHeapSize) {
            printf("%u\n", (maxHeap[0] + minHeap[0]) / 2);
        }
        else if (maxHeapSize > minHeapSize) {
            printf("%u\n", maxHeap[0]);
        }
        else {
            printf("%u\n", minHeap[0]);
        }
    }

    return 0;
}
