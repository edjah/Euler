#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

long test(long n) {
    long l = n % 10;
    if (n > 6 && (l == 4 || l == 6)) {
        return 0;
    }
    long q = sqrt(n) + 1;
    for (long d = 1; d < q; d++) {
        if (n % d == 0) {
            if (!miller_rabin(d + n/d, 25)) {
                return 0;
            }
        }
    }
    return 1;
}

long main(void) {
    srand(time(NULL));
    clock_t start = clock();
    long tot = 1; // to account for n = 1
    long count = 1;
    for (long i = 0; i < 100000000; i += 2) {
        if (test(i)) {
            tot += i;
            count += 1;
        }
    }
    printf("Total: %lu\n", tot);
    printf("Count: %lu\n", count);
    double time = (double) (clock() - start) / CLOCKS_PER_SEC;
    printf("Time: %f seconds\n", time);
}