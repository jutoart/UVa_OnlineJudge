#include <stdio.h>

#define MAX_INPUT_NUM 10000

typedef int (*CompareFunc) (int x, int y);

int CompareLess (int x, int y) {
    return ((x < y) ? 1 : 0);
}

int CompareGreater (int x, int y) {
    return ((x > y) ? 1 : 0);
}

void UpHeap (int* heap, int size, CompareFunc Compare) {
    int index = size - 1;

    if (heap == NULL) {
        return;
    }

    while ((index != 0) && Compare(heap[index], heap[(index+1)/2-1])) {
        int temp = heap[index];
        heap[index] = heap[(index+1)/2-1];
        heap[(index+1)/2-1] = temp;
        index = (index + 1) / 2 - 1;
    }

    return;
}

void DownHeap (int* heap, int size, CompareFunc Compare) {
    int index = 0;

    if (heap == NULL) {
        return;
    }

    while (1) {
        if ((index + 1) * 2 - 1 >= size) {
            break;
        }
        else {
            int compIndex = 0;

            if ((index + 1) * 2 >= size) {
                compIndex = (index + 1) * 2 - 1;
            }
            else {
                if (!Compare(heap[(index+1)*2-1], heap[(index+1)*2])) {
                    compIndex = (index + 1) * 2 - 1;
                }
                else {
                    compIndex = (index + 1) * 2;
                }
            }

            if(Compare(heap[index], heap[compIndex])) {
                int temp = heap[index];
                heap[index] = heap[compIndex];
                heap[compIndex] = temp;
                index = compIndex;
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
    int minHeap[MAX_INPUT_NUM/2+1] = {0};
    int maxHeap[MAX_INPUT_NUM/2+1] = {0};
    int input = 0;

    while (scanf("%d", &input) == 1) {
        if (maxHeapSize == 0) {
            maxHeap[0] = input;
            maxHeapSize++;
            printf("%d\n", input);
            continue;
        }
        else {
            if (input <= maxHeap[0]) {
                maxHeap[maxHeapSize] = input;
                maxHeapSize++;
                UpHeap(maxHeap, maxHeapSize, CompareGreater);
                DownHeap(maxHeap, maxHeapSize, CompareLess);
            }
            else {
                minHeap[minHeapSize] = input;
                minHeapSize++;
                UpHeap(minHeap, minHeapSize, CompareLess);
                DownHeap(minHeap, minHeapSize, CompareGreater);
            }
        }

        if (maxHeapSize - minHeapSize == 2) {
            minHeap[minHeapSize] = maxHeap[0];
            minHeapSize++;
            UpHeap(minHeap, minHeapSize, CompareLess);
            DownHeap(minHeap, minHeapSize, CompareGreater);
            maxHeap[0] = maxHeap[maxHeapSize-1];
            maxHeapSize--;
            DownHeap(maxHeap, maxHeapSize, CompareLess);
        }

        if (minHeapSize - maxHeapSize == 2) {
            maxHeap[maxHeapSize] = minHeap[0];
            maxHeapSize++;
            UpHeap(maxHeap, maxHeapSize, CompareGreater);
            DownHeap(maxHeap, maxHeapSize, CompareLess);
            minHeap[0] = minHeap[minHeapSize-1];
            minHeapSize--;
            DownHeap(minHeap, minHeapSize, CompareGreater);
        }

        if (maxHeapSize == minHeapSize) {
            printf("%d\n", (maxHeap[0] + minHeap[0]) / 2);
        }
        else if (maxHeapSize > minHeapSize) {
            printf("%d\n", maxHeap[0]);
        }
        else {
            printf("%d\n", minHeap[0]);
        }
    }

    return 0;
}
