#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>
#include <assert.h>

#define __UTILITYH__

#define MIN(a, b) ({ \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a < _b ? _a : _b; })

#define MAX(a, b) ({ \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b; })



/* Timing Functions */
static double tstamp_start = 0;

double tstamp() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double) tv.tv_sec + tv.tv_usec / 1000000.0;
}

void start_time() {
    tstamp_start = tstamp();
}

void end_time() {
    double time = tstamp() - tstamp_start;
    if (time < 1e-3) {
        printf("%.3f µs\n", 1000000.0 * time);
    }
    else if (time < 1) {
        printf("%.3f ms\n", 1000.0 * time);
    } else if (time < 60) {
        printf("%.3f sec\n", time);
    } else {
        printf("%d min %d sec\n", (int) time / 60, (int) time % 60);
    }
}


/* Primality testing functions */
unsigned long mod_exp(unsigned long b, unsigned long exp, unsigned long mod) {
    unsigned long result = 1;
    b %= mod;
    while (exp) {
        if (exp & 1) {
            result = (result * b) % mod;
        }
        exp >>= 1;
        b = (b * b) % mod;
    }
    return result;
}

bool __miller(unsigned d, unsigned n, unsigned a) {
    if (n == a) {
        return true;
    }

    unsigned long x = mod_exp(a, d, n);
    if (x == 1 || x == n - 1) {
       return true;
    }

    // Keep squaring x while one of the following doesn't happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1

    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;
        if (x == 1) {
            return false;
        } else if (x == n - 1) {
            return true;
        }
    }

    return false;
}

// Returns false if n is composite and returns true if n is prime.
// Due to overflow, this only works when n < 2^32, so to optimize the function,
// we use a determinstic variant of the Miller-Rabin test (from Wikipedia):
//     if n < 4,759,123,141, it is enough to test a = 2, 7, and 61
bool miller_rabin(unsigned n) {
    if (n <= 1) {
        return false;
    }

    // Find d such that n - 1 = 2^d * r for some r >= 1
    unsigned d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    return __miller(d, n, 2) && __miller(d, n, 7) && __miller(d, n, 61);
}

// https://stackoverflow.com/questions/2068372/fastest-way-to-list-all-primes-below-n-in-python/3035188#3035188
// Input n >= 6. Returns a list of primes, 2 <= p < n
int* sieve(int n, int* size) {
    int correction = n % 6 > 1;
    n = (int[6]){n, n - 1, n + 4, n + 3, n + 2, n + 1}[n % 6];

    int sieve_size = n / 3;
    bool* sieve = (bool*) malloc(sizeof(bool) * sieve_size);
    memset(sieve, true, sizeof(bool) * sieve_size);
    sieve[0] = false;

    for (int i = 0, lim = lim = 1 + ((int) sqrt(n)) / 3; i < lim; i++) {
        if (sieve[i]) {
            int k = (3*i + 1) | 1;
            int step = 2 * k;
            int m1 = (k * k) / 3;
            int m2 = (k*k + 4*k - 2*k*(i & 1)) / 3;

            for (int j = m1; j < sieve_size; j += step) {
                sieve[j] = false;
            }
            for (int j = m2; j < sieve_size; j += step) {
                sieve[j] = false;
            }
        }
    }

    *size = 2;
    for (int i = 1; i < sieve_size - correction; i++) {
        *size += sieve[i];
    }

    int* primes = (int*) malloc(sizeof(int) * (*size));
    primes[0] = 2;
    primes[1] = 3;

    for (int i = 1, idx = 2, lim = sieve_size - correction; i < lim; i++) {
        if (sieve[i]) {
            primes[idx++] = (3*i + 1) | 1;
        }
    }

    return primes;
}

int** prime_factors_tbl(int n, int** _sizes) {
    int max_size = 1 + log(n) / log(2);
    int** tbl = (int**) calloc(n + 1, sizeof(int*));
    int* sizes = (int*) calloc(n + 1, sizeof(int));

    for (int i = 0; i <= n; i++) {
        tbl[i] = (int*) calloc(max_size, sizeof(int));
    }

    for (int i = 2; i <= n; i++) {
        if (sizes[i] == 0) {
            for (int j = i; j <= n; j += i) {
                int k = j;
                while (k % i == 0) {
                    tbl[j][sizes[j]++] = i;
                    k /= i;
                }
            }
        }
    }

    *_sizes = sizes;
    return tbl;
}

/* Other utility functions */
unsigned long nCk(unsigned n, unsigned k) {
    unsigned long ans = 1;
    unsigned lim = MIN(k, n - k);
    for (unsigned long i = 0; i < lim; i++) {
        ans = (ans * (n - i)) / (i + 1);
    }
    return ans;
}

long gcd(long a, long b) {
    long tmp;
    while (b > 0) {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}
