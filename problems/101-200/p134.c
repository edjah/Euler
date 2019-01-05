#include "lib/utility.h"

long connection(int p1, int p2) {
    int tmp = p1, n = 10;
    while (tmp != 0) {
        n *= 10;
        tmp /= 10;
    }
    long ans = p2;
    while (ans % n != p1) {
        ans += p2;
    }
    return ans;
}

int main(int argc, char *argv[]) {
    start_time();

    int size;
    int *primes = sieve(1000003, &size);

    long sol = 0;
    int pcnt = size / 100;
    for (int i = 2; i < size - 1; i++) {
        if (i % pcnt == 0) {
            fprintf(stderr, "%d%% complete...\n", 100 * i / size);
        }
        sol += connection(primes[i], primes[i + 1]);
    }
    printf("Solution: %li\n", sol);

    end_time();
}
