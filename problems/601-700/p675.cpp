/*
Based on the clever observation by Daniel Qu that:
    S(n) = number of divisiors of n^2
from some number theory text book
*/
#include "lib/utility.hh"

using namespace std;

constexpr long mod = 1000000087;


int main() {
    start_time();

    constexpr long n = 1e7;
    vector<vector<int>> prime_factors= prime_factors_table(n);

    // we need to the count the number of divisors in n^2. algorithm based on:
    // https://en.wikipedia.org/wiki/Divisor_function#Formulas_at_prime_powers
    // but we need to do it in an efficient way that doesn't require a full
    // product each time
    long num_divisors = 1;

    // maintain a prime factorization of the factorial
    vector<int> facs = vector<int>(n + 1, 0);

    long total = 0;
    for (long i = 2; i <= n; ++i) {
        unordered_map<long, long> counts;
        for (int p : prime_factors[i]) {
            counts[p] += 1;
        }

        for (auto [prime, exp] : counts) {
            auto [gcd, inverse, _] = egcd(1 + 2 * facs[prime], mod);
            assert(gcd == 1);

            if (inverse < 0) {
                inverse = mod + inverse;
            }

            num_divisors = (inverse * num_divisors) % mod;
            facs[prime] += exp;
            num_divisors = (num_divisors * (1 + 2 * facs[prime])) % mod;
        }

        total = (total + num_divisors) % mod;
    }

    printf("Solution: %li\n", total);
    end_time();
}
