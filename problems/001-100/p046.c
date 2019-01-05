#include "lib/utility.h"

int *primes;
int nprimes;

bool golbach_test(int n) {
    for (int i = 0; i < nprimes && primes[i] < n; i++) {
        int k = sqrt((n - primes[i]) / 2);
        if (2 * k * k == n - primes[i]) {
            return true;
        }
    }
    return false;
}

int main(void) {
    start_time();

    primes = sieve(100000, &nprimes);
    int n = 9;
    while (miller_rabin(n) || golbach_test(n)) {
        n += 2;
    }
    printf("Solution: %d\n", n);

    end_time();
}
