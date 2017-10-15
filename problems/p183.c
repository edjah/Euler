#include <stdio.h>
#include <time.h>
#include <math.h>

double E;
int D(int n) {
    int k =  round(n / E);

    while (k % 2 == 0)
        k /= 2;
    while (k % 5 == 0)
        k /= 5;

    if (k == 1)
        return -n;
    return n;
}

int main(int argc, char *argv[]) {
    clock_t start = clock();

    E = exp(1.0);
    long sum = 0;
    for (int n = 5; n <= 1000000; n++) {
        sum += D(n);
    }
    printf("Solution: %lu\n", sum);

    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds to run\n", time);
}
