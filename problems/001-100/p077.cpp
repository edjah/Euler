#include "lib/utility.hh"

// almost exactly the same as p076.cpp... just check if curr_num is prime first
std::unordered_map<long, int> cache;
std::unordered_set<int> primes;

long count_ways(long n, long limit) {
    if (n == 0) {
        return 1;
    } else if (n < 0) {
        return 0;
    } else if (cache.count(n << 32 | limit)) {
        return cache[n << 32 | limit];
    }

    long result = 0;
    for (int curr_num = 2; curr_num <= limit; ++curr_num) {
        if (primes.count(curr_num)) {
            result += count_ways(n - curr_num, curr_num);
        }
    }
    cache[n << 32 | limit] = result;
    return result;
}

int main(void) {
    start_time();

    primes = get_prime_set(1000);
    int i = 2;
    while (count_ways(i, i - 1) < 5000) {
        i++;
    }
    printf("Solution: %d\n", i);

    end_time();
}
