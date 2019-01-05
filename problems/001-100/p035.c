#include "lib/utility.h"
#define LIMIT 1000000

int test_circular_prime(int p) {
    int length = 1 + log10(p);
    int mult = pow(10, length - 1);
    for (int rot = 0; rot < length; rot++) {
        p = 10 * (p % mult) + (p / mult);
        if (!miller_rabin(p)) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    start_time();

    int primes_size;
    int* primes = sieve(LIMIT, &primes_size);

    int count = 0;
    for (int i = 0; i < primes_size; i++) {
        count += test_circular_prime(primes[i]);
    }
    printf("Solution: %d\n", count);

    end_time();
}
