#include <stdio.h>
#include <stdlib.h>

#define MAX_DATABASE_SIZE 100000
#define MAX_DIGIT_SIZE 12

long long ReverseDigits (long long num) {
    int index = 0;
    long long result = 0;

    if (num < 0) {
        num = -num;
    }

    while (num > 0) {
        result = result * 10 + (num % 10);
        num /= 10;
    }

    return result;
}

int FindPalindrome (long long num, long long* pPalindrome, int* pIterCountData, long long* pPalindromeData) {
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
        long long reverseNum = ReverseDigits(num);
        long long sum = num + reverseNum;
        int count = FindPalindrome(sum, pPalindrome, pIterCountData, pPalindromeData);

        if (num < MAX_DATABASE_SIZE) {
            pIterCountData[num] = count + 1;
            pPalindromeData[num] = *pPalindrome;
        }

        return (count + 1);
    }
}

int main () {
    int inputNum = 0;
    int index = 0;
    long long* input = NULL;
    int iterCountDataBase[MAX_DATABASE_SIZE] = {0};
    long long palindromeDataBase[MAX_DATABASE_SIZE] = {0};

    scanf("%d", &inputNum);

    input = (long long*)malloc(inputNum*sizeof(long long));

    for (index = 0; index < inputNum; index++) {
        scanf("%lld", &(input[index]));
    }

    for (index = 0; index < inputNum; index++) {
        long long reverseNum = ReverseDigits(input[index]);
        long long sum = input[index] + reverseNum;
        long long palindrome = 0;
        int count = FindPalindrome(sum, &palindrome, iterCountDataBase, palindromeDataBase);

        printf("%d %lld\n", count, palindrome);
    }

    free(input);
    return 0;
}
