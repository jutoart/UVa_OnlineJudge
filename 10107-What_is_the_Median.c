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
    int minHeapNum = 0;
    int maxHeapNum = 0;
    unsigned int minHeap[MAX_INPUT_NUM/2] = {0};
    unsigned int maxHeap[MAX_INPUT_NUM/2] = {0};
    unsigned int input = 0;

    while (scanf("%u", &input) == 1) {
        if (maxHeapNum == 0) {
            maxHeap[0] = input;
            maxHeapNum++;
            printf("%d\n", input);
            continue;
        }
        else {
            if ((input <= maxHeap[0]) && (maxHeapNum > minHeapNum)) {
                minHeap[minHeapNum] = maxHeap[0];
                minHeapNum++;
                UpHeap(minHeap, minHeapNum, CompareLess);
                maxHeap[0] = input;
                DownHeap(maxHeap, maxHeapNum, CompareLess);
            }
            else {
            }
        }
    }

    return 0;
}
