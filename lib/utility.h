#pragma once

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/mman.h>

#define NUM_PRIMES_ON_DISK 50847534
#define PRIMES_BINARY_LOCATION "/home/nenya/cs/euler/lib/primes.bin"

#define MIN(a, b) ({        \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a < _b ? _a : _b;      \
})

#define MAX(a, b) ({        \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b;      \
})

#define SWAP(a, b) ({       \
    __typeof__(b) tmp = b;  \
    b = a;                  \
    a = tmp;                \
})

#define INSERTION_SORT_CUTOFF 32

typedef __int128 bigint;
typedef unsigned __int128 ubigint;

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
    if (time < 1) {
        printf("%.3f ms\n", 1000.0 * time);
    } else if (time < 60) {
        printf("%.3f sec\n", time);
    } else {
        printf("%d min %d sec\n", (int) time / 60, (int) time % 60);
    }
}


/* Primality testing functions */
ubigint mod_exp(ubigint b, ubigint exp, ubigint mod) {
    ubigint result = 1;
    b %= mod;
    while (exp) {
        if (exp % 2 == 1) {
            result = (result * b) % mod;
        }
        exp /= 2;
        b = (b * b) % mod;
    }
    return result;
}

bool __miller(ubigint d, ubigint n, ubigint a) {
    if (n == a) {
        return true;
    }

    ubigint x = mod_exp(a, d, n);
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
// Due to overflow, this only works when n < 2^64, so to optimize the function,
// we use a determinstic variant of the Miller-Rabin test (from Wikipedia):
//     if n < 2^64, it is enough to test a only a few witnesses is necessary
bool miller_rabin(ubigint n) {
    if (n <= 1) {
        return false;
    }

    // Find d such that n - 1 = 2^d * r for some r >= 1
    ubigint d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    if (n < 4759123141) {
        return __miller(d, n, 2) && __miller(d, n, 7) && __miller(d, n, 61);
    }

    static int large_witnesses[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
    };

    for (size_t i = 0; i < sizeof(large_witnesses) / sizeof(int); ++i) {
        if (!__miller(d, n, large_witnesses[i])) {
            return false;
        }
    }
    return true;
}

static const int* primes_map = NULL;

const int* read_primes() {
    if (primes_map != NULL) {
        return primes_map;
    }

    int fd = open(PRIMES_BINARY_LOCATION, O_RDONLY);
    assert(fd > 0 && "Unable to open primes file");

    size_t fsize = sizeof(int) * NUM_PRIMES_ON_DISK;
    primes_map = (int*) mmap(NULL, fsize, PROT_READ, MAP_SHARED, fd, 0);
    assert(primes_map != MAP_FAILED);
    return primes_map;
}

const int* read_primes_less_than(int x, int* size) {
    const int* primes = read_primes();

    // binary search to find the size
    int lo = 0;
    int hi = NUM_PRIMES_ON_DISK;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (primes[mid] < x) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    *size = lo;
    return primes;
}

// https://stackoverflow.com/questions/2068372/fastest-way-to-list-all-primes-below-n-in-python/3035188#3035188
// Input n >= 6. Returns a list of primes, 2 <= p < n
int* sieve(int n, int* size) {
    int correction = (n % 6) > 1;
    n = (int[6]){n, n - 1, n + 4, n + 3, n + 2, n + 1}[n % 6];

    int sieve_size = n / 3;
    bool* sieve = (bool*) malloc(sizeof(bool) * sieve_size);
    memset(sieve, true, sizeof(bool) * sieve_size);
    sieve[0] = false;

    for (int i = 0, lim = 1 + ((int) sqrt(n)) / 3; i < lim; i++) {
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

    free(sieve);
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
inline unsigned long nCk(unsigned n, unsigned k) {
    unsigned long ans = 1;
    unsigned lim = MIN(k, n - k);
    for (unsigned long i = 0; i < lim; i++) {
        ans = (ans * (n - i)) / (i + 1);
    }
    return ans;
}

inline unsigned long gcd(unsigned long a, unsigned long b) {
    unsigned long tmp;
    while (b > 0) {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}


/* Sorting functions */
#define INSERTION_SORT(a, sz, sort_key) ({                      \
    for (size_t i = 0; i < (size_t) sz; ++i) {                  \
        size_t j = i;                                           \
        while (j > 0 && a[j - 1]sort_key > a[j]sort_key) {      \
            SWAP(a[j - 1], a[j]);                               \
            j -= 1;                                             \
        }                                                       \
    }                                                           \
})

void quicksort(int* a, int sz) {
    // insertion sort in the base case
    if (sz < INSERTION_SORT_CUTOFF) {
        INSERTION_SORT(a, sz,);
        return;
    }

    // median of 3 selection of pivot to avoid worst case performance
    int mid = sz / 2;
    int end = sz - 1;
    if (a[0] <= a[mid] && a[mid] < a[end]) {
        SWAP(a[0], a[mid]);
    } else if (a[0] <= a[end] && a[end] < a[mid]) {
        SWAP(a[0], a[end]);
    }

    // partioning
    int pivot = a[0];
    int i = -1;
    int j = sz;
    while (1) {
        while (a[++i] < pivot);
        while (a[--j] > pivot);
        if (i >= j) {
            break;
        }
        SWAP(a[i], a[j]);
    }

    // recursively sorting
    quicksort(a, j + 1);
    quicksort(a + j + 1, sz - j - 1);
}

inline long round_down(long x, long r) {
    return r * (x / r);
}

inline bool is_square(long n) {
    long x = sqrt(n);
    return x * x == n;
}
