#include "lib/utility.hh"
#include "lib/fast_hashmap.hh"

int count_solutions_less_than(int limit) {
    std::vector<int> primes = get_primes(sqrt(limit) + 1);
    std::vector<int> powers[3];

    for (int power = 0; power < 3; ++power) {
        for (int prime : primes) {
            if (pow(prime, power + 2) >= limit) {
                break;
            }
            powers[power].push_back(pow(prime, power + 2));
        }
    }

    ska::flat_hash_set<int> numbers;
    for (size_t i = 0; i < powers[0].size(); ++i) {
        for (size_t j = 0; j < powers[1].size(); ++j) {
            for (size_t k = 0; k < powers[2].size(); ++k) {
                int tot = powers[0][i] + powers[1][j] + powers[2][k];
                if (tot < limit) {
                    numbers.insert(tot);
                }
            }
        }
    }

    return numbers.size();
}

int main(void) {
    start_time();
    printf("Solution: %d\n", count_solutions_less_than(50000000));
    end_time();
}
