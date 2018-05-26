#include "lib/utility.h"


int main(void) {
    start_time();

    int n = 1;
    int size = 0;
    long* primes = NULL;
    while (size < 10000) {
        free(primes);
        primes = sieve(n, &size);
        n *= 2;
    }
    printf("Solution: %li\n", primes[10000]);


    end_time();
}
