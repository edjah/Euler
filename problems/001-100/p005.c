#include "lib/utility.h"


long lcm(long a, long b) {
    return (a * b) / gcd(a, b);
}

int main(void) {
    start_time();

    long res = 1;
    for (int i = 2; i <= 20; i++) {
        res = lcm(res, i);
    }
    printf("Solution: %li\n", res);

    end_time();
}
