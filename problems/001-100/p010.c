#include "lib/utility.h"


int main(void) {
    start_time();

    int size;
    long* primes = sieve(2000000, &size);
    long tot = 0;
    for (int i = 0; i < size; i++) {
        tot += primes[i];
    }
    printf("Solution: %li\n", tot);

    end_time();
}
