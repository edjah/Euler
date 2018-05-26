#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

int power(int x, unsigned int y, int p) {
    int res = 1;      // Initialize result
    x = x % p;  // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

// This function is called for all k trials. It returns
// false if n is composite and returns false if n is
// probably prime.
// d is an odd number such that  d*2<sup>r</sup> = n-1
// for some r >= 1
int miillerTest(int d, int n) {
    // Pick a random number in [2..n-2]
    // Corner cases make sure that n > 4
    int a = 2 + rand() % (n - 4);

    // Compute a^d % n
    int x = power(a, d, n);

    if (x == 1  || x == n-1)
       return true;

    // Keep squaring x while one of the following doesn't
    // happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n-1)
    {
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
int isPrime(int n, int k) {
    // Corner cases
    if (n <= 1 || n == 4)  return 0;
    if (n <= 3) return 1;

    // Find r such that n = 2^d * r + 1 for some r >= 1
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // Iterate given nber of 'k' times
    for (int i = 0; i < k; i++)
         if (miillerTest(d, n) == 0)
              return 0;

    return 1;
}

int test(int n) {
    int l = n % 10;
    if (n > 6 && (l == 4 || l == 6)) {
        return 0;
    }
    int q = sqrt(n) + 1;
    for (int d = 1; d < q; d++) {
        if (n % d == 0) {
            if (!isPrime(d + n/d, 25)) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void) {
    clock_t start = clock();
    long tot = 0;
    int count = 0;
    for (int i = 0; i < 1000000; i += 2) {
        if (test(i)) {
            tot += i;
            count += 1;
        }
    }
    printf("Total: %lu\n", tot);
    printf("Count: %d\n", count);
    double time = (double) (clock() - start) / CLOCKS_PER_SEC;
    printf("Time: %f seconds\n", time);
}
