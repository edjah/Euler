#include <stdio.h>
#include <time.h>
#include "prime.c"

long long connection(int p1, int p2) {
    int tmp = p1, n = 10;
    while (tmp != 0) {
        n *= 10;
        tmp /= 10;
    }
    long long ans = p2;
    while (ans % n != p1) {
        ans += p2;
    }
    return ans;
}

int main(int argc, char *argv[]) {
    clock_t start = clock();

    long *primes = sieve(1000003);
    int num_primes = primes[-1];

    long long sol = 0;
    int pcnt = num_primes / 100;
    for (int i = 2; i < num_primes - 1; i++) {
        if (i % pcnt == 0) {
            printf("%d%% complete...\n", 100 * i / num_primes);
        }
        sol += connection(primes[i], primes[i + 1]);
    }
    printf("Solution: %llu\n", sol);

    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds to run\n", time);
}
