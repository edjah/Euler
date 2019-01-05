#include "lib/utility.hh"

std::unordered_map<long, int> cache;

long count_ways(long n, long limit) {
    if (n == 0) {
        return 1;
    } else if (n < 0) {
        return 0;
    } else if (cache.count(n << 32 | limit)) {
        return cache[n << 32 | limit];
    }

    long result = 0;
    for (int curr_num = 1; curr_num <= limit; ++curr_num) {
        result += count_ways(n - curr_num, curr_num);
    }
    cache[n << 32 | limit] = result;
    return result;
}

int main(void) {
    start_time();
    printf("Solution: %li\n", count_ways(100, 99));
    end_time();
}
