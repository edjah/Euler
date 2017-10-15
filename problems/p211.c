#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h>

mpz_t* divisor_square_sum_tbl(int n) {
    mpz_t *tbl = malloc(sizeof(mpz_t) * (n + 1));
    for (int i = 0; i < n + 1; i++) {
        mpz_init(tbl[i]);
    }
    for (long i = 1; i < n + 1; i++) {
        for (long j = i; j < n + 1; j += i) {
            mpz_add_ui(tbl[j], tbl[j], i * i);
        }
    }

    return tbl;
}

int main(int argc, char *argv[]) {
    clock_t start = clock();

    int lim = 640000;

    mpz_t *x = divisor_square_sum_tbl(lim);
    long tot = 0;
    for (int i = 0; i <= lim; i++) {
        if (mpz_perfect_square_p(x[i])) {
            tot += i;
        }
    }
    printf("Solution: %lu\n", tot);

    free(x);

    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds to run\n", time);
}
