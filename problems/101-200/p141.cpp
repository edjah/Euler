/*
    d*d = r*q  => r = d*d / q
    n = d*q + r

    Strategy
    ========
    - Try every d, but only try values of q which can divide d^2..
    - Generate these q's by multiplying subsets of the prime factors of d^2.
    - Stop testing when the max_n has reached k * n_limit. (I set k = 100 here)
*/
#include "lib/utility.hh"
#include "lib/fast_hashmap.hh"

constexpr size_t n_limit = 1e12;
constexpr size_t prime_factor_limit = 5e6;

size_t max_n = 0;
ska::flat_hash_set<size_t> sols;

struct factor {
    size_t prime;
    size_t count;
};

std::vector<factor> prime_factors[prime_factor_limit];
ska::flat_hash_map<size_t, int> prime_pos;

void build_prime_factors() {
    for (size_t i = 2; i < prime_factor_limit; ++i) {
        if (prime_factors[i].size() == 0) {
            for (size_t j = i; j < prime_factor_limit; j += i) {
                size_t pos = (j << 32) | i;
                if (!prime_pos.count(pos)) {
                    prime_pos[pos] = prime_factors[j].size();
                    prime_factors[j].push_back({.prime = i, .count = 1});
                }
                factor& fac = prime_factors[j][prime_pos[pos]];

                size_t k = j;
                while (k % i == 0) {
                    fac.count += 2;
                    k /= i;
                }
            }
        }
    }
}

void try_subsets(const size_t d, size_t q, size_t facs_idx, size_t p_idx) {
    const auto& facs = prime_factors[d];
    if (facs_idx >= facs.size() || p_idx >= facs[facs_idx].count) {
        return;
    }

    if (p_idx > 0 && q != 1) {
        size_t r = d*d / q;
        size_t n = d*q + r;
        size_t s = sqrt(n);
        if (s * s == n and n / d == q and n % d == r) {
            max_n = std::max(max_n, n);
            if (n < n_limit) {
                sols.insert(n);
            }
        }
    }

    try_subsets(d, q * facs[facs_idx].prime, facs_idx, p_idx + 1);
    try_subsets(d, q, facs_idx + 1, 0);
}

int main(int argc, char *argv[]) {
    start_time();

    build_prime_factors();
    for (int d = 0; max_n < 100 * n_limit; ++d) {
        try_subsets(d, 1, 0, 0);
    }
    size_t ans = std::accumulate(sols.begin(), sols.end(), 0L);
    printf("Solution: %zu\n", ans);

    end_time();
}
