#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int cmp(const void * a, const void * b) {
   return *(long*)a - *(long*)b;
}

int is_progressive(long n) {
    long lim = sqrt(n) + 1;
    long q, r;
    for (long d = 1; d < lim; d++) {
        q = n / d;
        r = n % d;
        if (d * d == r * q) {
            printf("%lu: (d=%lu, q=%lu, r=%lu) - ", n, d, q, r);
            return 1;
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    clock_t start = clock();

    if (argc != 2) {
        printf("Usage: p141 limit\n");
        return 1;
    }
    long tot = 0;
    long lim = sqrt(atof(argv[1])) + 1;
    for (long i = 1; i < lim; i++) {
        long n = i * i;
        if (is_progressive(n)) {
            printf("%lu\n", i);
            tot += n;
        }
    }

    printf("Solution: %lu\n", tot);


    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds to run\n", time);
}
