#include <stdio.h>

int main () {
    long long num1 = 0, num2 = 0;

    scanf("%lld %lld", &num1, &num2);

    while ((num1 != 0) || (num2 != 0)) {
        int count = 0, carry = 0;

        while ((num1 > 0) || (num2 > 0)) {
            int digit1 = 0, digit2 = 0, sum = 0;

            if (num1 > 0) {
                digit1 = num1 % 10;
                num1 /= 10;
            }

            if (num2 > 0) {
                digit2 = num2 % 10;
                num2 /= 10;
            }

            sum = digit1 + digit2 + carry;

            if (sum > 10) {
                count++;
            }

            carry = sum / 10;
        }

        if (carry > 0) {
            count++;
        }

        if (count == 0) {
            printf("No carry operation.\n");
        }
        else if (count == 1) {
            printf("1 carry operation.\n");
        }
        else {
            printf("%d carry operations.\n", count);
        }

        scanf("%lld %lld", &num1, &num2);
    }

    return 0;
}
