#include <stdio.h>
#include <time.h>
#include <math.h>
#define LIMIT 333333333

int is_perfect_square(__uint128_t n) {
    __uint128_t t = (__uint128_t) sqrt((double) n);
    return t * t == n;
}

int works_out(__uint128_t a, __uint128_t b, __uint128_t c) {
    __uint128_t k = (a - b - c) * (a + b - c) * (a - b + c) * (a + b + c);
    if (k % 16 != 0) {
        return 0;
    }
    return is_perfect_square(-k / 16);
}


int main(void) {
    clock_t start = clock();

    long long tot = 0;
    for (int s = 5; s < LIMIT; s += 4) {
        if (works_out(s, s, s + 1)) {
            printf("%d %d %d\n", s, s, s + 1);
            tot += 3 * s + 1;
        } else if (works_out(s, s, s - 1)) {
            printf("%d %d %d\n", s, s, s - 1);
            tot += 3 * s - 1;
        }
    }

    printf("Solution: %llu\n", tot);
    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds to run\n", time);

}
