#include "lib/utility.h"
#include "lib/bignum.h"

int main(void) {
    start_time();

    bignum* factorial = BIGNUM_ONE;
    for (int i = 1; i <= 100; i++) {
        factorial = bignum_mult(factorial, bignum_from_long(i));
    }

    int digit_sum = 0;
    char* s = bignum_to_string(factorial);
    for (int i = 0, n = strlen(s); i < n; i++) {
        digit_sum += s[i] - '0';
    }
    free(s);
    printf("Solution: %d\n", digit_sum);

    end_time();
}
