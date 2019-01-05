#include "lib/utility.h"
#define LIMIT 1000000

bool palindrome(int n, int base) {
    int digits[64];
    int len = 0;

    while (n > 0) {
        digits[len++] = n % base;
        n /= base;
    }

    for (int i = 0; i < len / 2; i++) {
        if (digits[i] != digits[len - i - 1]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    start_time();

    // even numbers >= 2 cannot be base-2 palindromes
    int tot = 0;
    for (int n = 1; n < LIMIT; n += 2) {
        if (palindrome(n, 2) && palindrome(n, 10)) {
            tot += n;
        }
    }
    printf("Solution: %d\n", tot);

    end_time();
}
