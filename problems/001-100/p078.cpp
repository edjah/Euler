#include "lib/utility.hh"
#include "lib/fast_hashmap.hh"

ska::flat_hash_map<int, int> cache;
int modulo = 1000000;

// from http://mathworld.wolfram.com/PartitionFunctionP.html
int P(int n) {
    if (n < 0) {
        return 0;
    } else if (n <= 1) {
        return 1;
    } else if (cache[n] != 0) {
        return cache[n];
    }

    int res = 0;
    for (int k = 1; k <= n; ++k) {
        int m1 = n - k * (3 * k - 1) / 2;
        int m2 = n - k * (3 * k + 1) / 2;
        if (m1 < 0) {
            break;
        }
        res += (P(m1) + P(m2)) * (k % 2 == 0 ? -1 : 1);
    }
    cache[n] = res % modulo;
    return res % modulo;
}

int main(void) {
    start_time();

    int n = 2;
    while (P(n) % modulo != 0) {
        n++;
    }
    printf("Solution: %d\n", n);

    end_time();
}
