#include "lib/utility.hh"

constexpr int limit = 10000000;
int cache[limit];


int chain_end(int n) {
    if (n == 1 || n == 89) {
        return n;
    } else if (cache[n]) {
        return cache[n];
    }

    int tot = 0;
    int n_copy = n;
    while (n_copy > 0) {
        tot += (n_copy % 10) * (n_copy % 10);
        n_copy /= 10;
    }
    cache[n] = chain_end(tot);
    return cache[n];

}

int main(void) {
    start_time();

    int count = 0;
    for (int i = 1; i < limit; ++i) {
        count += (chain_end(i) == 89);
    }
    printf("Solution: %d\n", count);

    end_time();
}
