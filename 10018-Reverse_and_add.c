#include <stdio.h>
#include <stdlib.h>

#define MAX_DATABASE_SIZE 100000
#define MAX_DIGIT_SIZE 12

unsigned int ReverseDigits (unsigned int num) {
    int count = 0;
    unsigned int max = 0;
    unsigned int cur10Times = 10, pre10Times = 0;
    int index = 0;
    unsigned int result = 0;
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

int FindPalindrome (int num, unsigned int* pPalindrome, int* pIterCountData, unsigned int* pPalindromeData) {
    if (num < MAX_DATABASE_SIZE) {
        if (pIterCountData[num] > 0) {
            *pPalindrome = pPalindromeData[num];
            return pIterCountData[num];
        }
    }

    if (num == ReverseDigits(num)) {
        *pPalindrome = num;

        if (num < MAX_DATABASE_SIZE) {
            pIterCountData[num] = 0;
            pPalindromeData[num] = num;
        }

        return 0;
    }
    else {
        unsigned int reverseNum = ReverseDigits(num);
        unsigned int sum = num + reverseNum;
        int count = FindPalindrome(sum, pPalindrome, pIterCountData, pPalindromeData);

        if (num < MAX_DATABASE_SIZE) {
            pIterCountData[num] = count + 1;
            pPalindromeData[num] = *pPalindrome;
        }

        if (reverseNum < MAX_DATABASE_SIZE) {
            pIterCountData[reverseNum] = count + 1;
            pPalindromeData[reverseNum] = *pPalindrome;
        }

        return (count + 1);
    }
}

int main () {
    int inputNum = 0;
    int index = 0;
    unsigned int* input = NULL;
    int iterCountDataBase[MAX_DATABASE_SIZE] = {0};
    unsigned int palindromeDataBase[MAX_DATABASE_SIZE] = {0};

    scanf("%d", &inputNum);

    input = (unsigned int*)malloc(inputNum*sizeof(unsigned int));

    for (index = 0; index < inputNum; index++) {
        scanf("%u", &(input[index]));
    }

    for (index = 0; index < inputNum; index++) {
        unsigned int palindrome = 0;
        int count = FindPalindrome(input[index], &palindrome, iterCountDataBase, palindromeDataBase);

        printf("%d %u\n", count, palindrome);
    }

    free(input);
    return 0;
}
