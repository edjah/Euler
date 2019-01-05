#include "lib/utility.hh"

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

std::unordered_map<int, int> cache;

int chain_length(int n) {
    const int orig_n = n;
    std::unordered_set<int> history;

    while (!history.count(n)) {
        if (cache.count(n)) {
            cache[orig_n] = history.size() + cache[n];
            return cache[orig_n];
        }

        history.insert(n);
        std::vector<int> digits = digits_of_long(n);
        n = 0;
        for (int d : digits) {
            n += factorial(d);
        }
    }
    cache[orig_n] = history.size();
    return history.size();
}

int main(void) {
    start_time();

    int count = 0;
    for (int i = 0; i < 1000000; ++i) {
        count += (chain_length(i) == 60);
    }
    printf("Solution: %d\n", count);

    end_time();
}
