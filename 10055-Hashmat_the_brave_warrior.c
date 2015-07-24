#include <stdio.h>

int main () {
    unsigned int num1 = 0, num2 = 0;

    while (scanf("%u %u", &num1, &num2) == 2) {
        if (num1 >= num2) {
            printf("%u\n", num1 - num2);
        }
        else {
            printf("%u\n", num2 - num1);
        }
    }

    return 0;
}
