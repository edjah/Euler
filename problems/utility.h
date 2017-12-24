#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static double tstamp_start = 0;

/* Timing Functions */
double tstamp() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000.0 * tv.tv_sec + tv.tv_usec / 1000.0;
}

void start_time() {
    tstamp_start = tstamp();
}

void end_time() {
    printf("%.3f ms\n", tstamp() - tstamp_start);
}

/* Primality testing functions */
long mod_exp(long x, long exp, long n) {
    long res = 1;
    x %= n;
    while (exp) {
        if (exp & 1)
            res = (res * x) % n;
        exp >>= 1;
        x = (x * x) % n;
    }
    return res;
}

long miller_test(long d, long n) {
    // Pick a random number in [2..n-2]. Corner cases make sure that n > 4
    long a = 2 + rand() % (n - 4);

    // Compute a^d % n
    long x = mod_exp(a, d, n);

    if (x == 1  || x == n - 1)
       return 1;

    // Keep squaring x while one of the following doesn't happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;
        if (x == 1)      return 0;
        if (x == n-1)    return 1;
    }

    // Return composite
    return 0;
}

// It returns false if n is composite and returns true if n
// is probably prime.  k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
// Only works when n < 2^31
int miller_rabin(long n, int k) {
    // Corner cases
    if (n <= 1 || n == 4)  return 0;
    if (n <= 3) return 1;

    // Find r such that n = 2^d * r + 1 for some r >= 1
    long d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // Iterate given number of 'k' times
    for (int i = 0; i < k; i++)
         if (miller_test(d, n) == 0)
              return 0;

    return 1;
}

long* sieve(int n, int* size) {
    char* A = (char*) malloc(sizeof(char) * (n + 1));
    memset(A, 1, n + 1);

    *size = n - 1;
    for (int i = 2; i * i <= n; i++) {
        if (A[i]) {
            for (int j = i * i; j <= n; j += i) {
                *size -= A[j];
                A[j] = 0;
            }
        }
    }

    long *primes = (long*) malloc(sizeof(long) * (*size));
    int k = 0;
    for (int i = 2; i <= n; i++) {
        if (A[i]) {
            primes[k] = i;
            k += 1;
        }
    }
    free(A);

    return primes;
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
