#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int* divisor_count_tbl(int n) {
    int *tbl = calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) {
        for (int j = i + i; j <= n; j += i) {
            tbl[j] += 1;
        }
    }
    return tbl;
}

int main(int argc, char *argv[]) {
    clock_t start = clock();

    if (argc != 2) {
        printf("Usage: p179 num\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Argument must be greater than 0\n");
        return 2;
    }

    int *a = divisor_count_tbl(n);
    int tot = 0;
    for (int i = 1; i < n; i++) {
        tot += a[i] == a[i + 1];
    }
    free(a);
    printf("Solution: %d\n", tot);


    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds to run\n", time);
}
