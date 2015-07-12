#include <stdio.h>
#include <stdlib.h>

#define MAX_DATABASE_SIZE 100000
#define MAX_DIGIT_SIZE 12

int ReverseDigits (int num) {
    int count = 0;
    int max = 0;
    int cur10Times = 10, pre10Times = 0;
    int index = 0;
    int result = 0;
    int buffer[MAX_DIGIT_SIZE] = {0};

    while (num > max) {
        max = max * 10 + 9;

        if (cur10Times == 10) {
            buffer[count] = num % cur10Times;
        }
        else {
            buffer[count] = ((num % cur10Times) - (num % pre10Times)) / pre10Times;
        }

        pre10Times = cur10Times;
        cur10Times *= 10;
        count++;
    }

    cur10Times = 1;

    for (index = count-1; index >= 0; index--) {
        result += buffer[index] * cur10Times;
        cur10Times *= 10;
    }

    return result;
}

void FindPalindrome (int num, int* pIterCount, int* pPalindrome) {
}

int main () {
    int inputNum = 0;
    int index = 0;
    int* input = NULL;
    int iterCountDataBase[MAX_DATABASE_SIZE] = {0};
    int palindromeDataBase[MAX_DATABASE_SIZE] = {0};

    scanf("%d", &inputNum);

    input = (int*)malloc(inputNum*sizeof(int));

    for (index = 0; index < inputNum; index++) {
        scanf("%d", &(input[index]));
    }

    for (index = 0; index < inputNum; index++) {
        printf("%d\n", ReverseDigits(input[index]));
    }

    return 0;
}
