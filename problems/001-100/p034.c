#include "lib/utility.h"

int factorial[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

int digit_factorial_sum(int n) {
    int res = 0;
    while (n > 0) {
        res += factorial[n % 10];
        n /= 10;
    }
    return res;
}

int main(void) {
    start_time();

    // 9999999 is a simple upper bound since 7 * 9! < 9999999
    int tot = 0;
    for (int n = 3; n < 9999999; n++) {
        if (n == digit_factorial_sum(n)) {
            tot += n;
        }
    }
    printf("Solution: %d\n", tot);

    end_time();
}
