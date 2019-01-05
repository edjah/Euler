#include <iostream>
#include "lib/utility.h"
using namespace std;

#define N 1000000000000000000

bool test_prime(int p) {
    return p >= 7 && mod_exp(10, N % (p - 1), p) == 1;
}

int main(void) {
    start_time();

    int size;
    int* primes = sieve(100000, &size);

    long solution = 0;
    for (int i = 0; i < size; i++) {
        if (!test_prime(primes[i])) {
            solution += primes[i];
        }
    }

    cout << "Solution: " << solution << endl;

    end_time();
}
