#include "lib/utility.h"

#define mod 1234567891011UL

ubigint next_prime(ubigint n) {
    n += (n % 2 == 0) ? 1 : 2;
    while (!miller_rabin(n)) {
        n += 2;
    }
    return n;
}

inline void mat_mult(ubigint a[4], ubigint b[4]) {
    ubigint w = (a[0]*b[0] + a[1]*b[2]) % mod;
    ubigint x = (a[0]*b[2] + a[1]*b[3]) % mod;
    ubigint y = (a[2]*b[0] + a[3]*b[2]) % mod;
    ubigint z = (a[2]*b[1] + a[3]*b[3]) % mod;
    a[0] = w, a[1] = x, a[2] = y, a[3] = z;
}

ubigint fast_fibonacci(ubigint n) {
    ubigint current[4] = {0, 1, 1, 1};
    ubigint result[4] = {1, 0, 0, 1};

    while (n != 0) {
        if (n % 2 == 1) {
            mat_mult(result, current);
        }
        mat_mult(current, current);
        n /= 2;
    }

    return result[1];
}

int main() {
    start_time();
    ubigint total = 0;
    ubigint a_n = next_prime(1e14);
    for (int i = 0; i < 100000; ++i) {
        total = (total + fast_fibonacci(a_n)) % mod;
        a_n = next_prime(a_n);
    }
    printf("Solution: %li\n", (long) total);
    end_time();
}
