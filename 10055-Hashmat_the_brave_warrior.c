#include <stdio.h>

int main () {
    unsigned long long num1 = 0, num2 = 0;

    while (scanf("%llu %llu", &num1, &num2) == 2) {
        if (num1 >= num2) {
            printf("%llu\n", num1 - num2);
        }
        else {
            printf("%llu\n", num2 - num1);
        }
    }

    return 0;
}
