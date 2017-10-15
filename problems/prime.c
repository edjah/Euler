#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    while (d != n-1) {
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

long* sieve(long n) {
    char *A = malloc(sizeof(char) * (n + 1));
    memset(A, 1, n + 1);
    for (long i = 2; i * i <= n; i++)
        if (A[i])
            for (long j = i*i; j <= n; j += i)
                A[j] = 0;

    int count = 0;
    for (long i = 2; i <= n; i++) {
        if (A[i])
            count += 1;
    }
    long *primes = malloc(sizeof(long) * (count + 1));
    primes[0] = count;
    long k = 1;
    for (long i = 2; i <= n; i++) {
        if (A[i]) {
            primes[k] = i;
            k += 1;
        }
    }
    free(A);

    // return the primes. the first ele is the number of them
    return &primes[1];
}


// int main(int argc, char *argv[]) {
//     srand(time(NULL));
//     clock_t start = clock();

//     if (argc != 2) {
//         printf("Usage: prime num\n");
//         return 1;
//     }
//     long n = atol(argv[1]);

//     long* primes = sieve(n);
//     int num = primes[-1];
//     printf("Num: %d\n", num);

//     double time = (double) (clock() - start) / CLOCKS_PER_SEC;
//     printf("Time: %f seconds\n", time);
// }

