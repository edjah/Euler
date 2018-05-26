#include "lib/utility.h"

bool palindrome(long original) {
    long copy = original;
    long reverse = 0;
    while (copy > 0) {
        reverse = (10 * reverse) + (copy % 10);
        copy /= 10;
    }
    return original == reverse;
}

int main(void) {
    start_time();

    int max = 0;
    for (int a = 999; a >= 100; a--) {
        for (int b = a; b >= 100; b--) {
            if (a * b < max) {
                break;
            }
            else if (palindrome(a * b)) {
                max = MAX(a * b, max);
            }
        }
    }
    printf("Solution: %d\n", max);

    end_time();
}
