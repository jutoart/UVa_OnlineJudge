#include <stdio.h>
#include <stdlib.h>

#define MAX_DATABASE_SIZE 100000
#define MAX_DIGIT_SIZE 12

long ReverseDigits (long num) {
    int count = 0;
    int index = 0;
    long result = 0;
    int buffer[MAX_DIGIT_SIZE] = {0};

    if (num < 0) {
        num = -num;
    }

    while (num > 0) {
        buffer[count] = num % 10;
        num /= 10;
        count++;
    }

    for (index = 0; index < count; index++) {
        result = result * 10 + buffer[index];
    }

    return result;
}

int FindPalindrome (long num, long* pPalindrome, int* pIterCountData, long* pPalindromeData) {
    if (num < MAX_DATABASE_SIZE) {
        if (pIterCountData[num] > 0) {
            *pPalindrome = pPalindromeData[num];
            return pIterCountData[num];
        }
    }

    if (num == ReverseDigits(num)) {
        *pPalindrome = num;
        return 1;
    }
    else {
        long reverseNum = ReverseDigits(num);
        long sum = num + reverseNum;
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
    long* input = NULL;
    int iterCountDataBase[MAX_DATABASE_SIZE] = {0};
    long palindromeDataBase[MAX_DATABASE_SIZE] = {0};

    scanf("%d", &inputNum);

    input = (long*)malloc(inputNum*sizeof(long));

    for (index = 0; index < inputNum; index++) {
        scanf("%ld", &(input[index]));
    }

    for (index = 0; index < inputNum; index++) {
        long reverseNum = ReverseDigits(input[index]);
        long sum = input[index] + reverseNum;
        long palindrome = 0;
        int count = FindPalindrome(sum, &palindrome, iterCountDataBase, palindromeDataBase);

        printf("%d %ld\n", count, palindrome);
    }

    free(input);
    return 0;
}
