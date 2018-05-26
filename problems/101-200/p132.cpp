#include <iostream>
#include "lib/utility.h"
using namespace std;

#define N 1000000000

bool test_prime(long p) {
    return mod_exp(10, N % (p - 1), p) == 1;
}

int main(void) {
    start_time();

    int size;
    long* primes = sieve(200000, &size);

    long tot = 0;
    int count = 0;
    for (int i = 3; i < size; i++) {
        if (test_prime(primes[i])) {
            tot += primes[i];
            if (++count == 40) {
                cout << "Solution: " << tot << endl;
                break;
            }
        }
    }

    end_time();
}
