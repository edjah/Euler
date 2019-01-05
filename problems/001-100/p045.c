#include "lib/utility.h"


bool is_pentagonal(long n) {
    long k = (sqrt(24*n + 1) + 1) / 6;
    return k * (3*k - 1) == 2 * n;
}

int main(void) {
    start_time();

    // all triangle numbers are hexagonal numbers
    long n = 144;
    while (!is_pentagonal(n * (2*n - 1))) {
        n += 1;
    }
    printf("Solution: %li\n", n * (2*n - 1));

    end_time();
}
