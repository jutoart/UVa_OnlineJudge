#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    int setNum = 0, setIndex = 0;
    int* pSetAmplitude = NULL;
    int* pSetFrequency = NULL;

    scanf("%d", &setNum);

    if (setNum > 0) {
        pSetAmplitude = (int*)malloc(setNum*sizeof(int));
        pSetFrequency = (int*)malloc(setNum*sizeof(int));
        memset(pSetAmplitude, 0, setNum*sizeof(int));
        memset(pSetFrequency, 0, setNum*sizeof(int));
    }

    for (setIndex = 0; setIndex < setNum; setIndex++) {
        scanf("");
        scanf("%d", &(pSetAmplitude[setIndex]));
        scanf("%d", &(pSetFrequency[setIndex]));
    }

    for (setIndex = 0; setIndex < setNum; setIndex++) {
        int freqIndex = 0;

        for (freqIndex = 0; freqIndex < pSetFrequency[setIndex]; freqIndex++) {
            int height = 1, inc = 1;

            while (height > 0) {
                int ampIndex = 0;

                for (ampIndex = 0; ampIndex < height; ampIndex++) {
                    printf("%d", height);
                }

                printf("\n");

                if (height == pSetAmplitude[setIndex]) {
                    inc = -1;
                }

                height += inc;
            }

            if ((freqIndex < pSetFrequency[setIndex] - 1) || (setIndex < setNum - 1)) {
                printf("\n");
            }
        }
    }

    return 0;
}
