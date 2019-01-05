#include "lib/utility.hh"
#include "lib/bignum.hh"

#define PRIME_LIMIT 10000
#define PRIME_SET_LIMIT PRIME_LIMIT * 100

std::vector<int> primes;
std::unordered_set<int> prime_set;

bool is_prime(int x) {
    if (x < PRIME_SET_LIMIT) {
        return prime_set.count(x);
    }
    return Bignum(x).is_prime();
}

int int_concat(int x, int y) {
    int mult = 1;
    while (mult <= y) {
        mult *= 10;
    }
    return mult * x + y;
}

bool is_compatible(int x, int y) {
    return is_prime(int_concat(x, y)) && is_prime(int_concat(y, x));
}

int search(std::vector<int>& acc, size_t cur_pos) {
    if (acc.size() == 5) {
        print_vec(acc);
        return std::accumulate(acc.begin(), acc.end(), 0);
    }

    for (size_t i = cur_pos; i < primes.size(); ++i) {
        bool flag = true;
        for (size_t j = 0; j < acc.size(); ++j) {
            if (!is_compatible(primes[i], acc[j])) {
                flag = false;
                break;
            }
        }

        if (flag) {
            acc.push_back(primes[i]);
            int result = search(acc, i + 1);
            if (result > 0) {
                return result;
            }
            acc.pop_back();
        }
    }
    return 0;
}

int main(void) {
    start_time();

    primes = get_primes(PRIME_LIMIT);
    prime_set = get_prime_set(PRIME_SET_LIMIT);

    std::vector<int> acc;
    int result = search(acc, 0);
    printf("Solution: %d\n", result);

    end_time();
}
