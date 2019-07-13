#include "lib/utility.hh"
#include "lib/fraction.hh"

std::unordered_map<long, std::unordered_set<Fraction>> cache;

std::unordered_set<Fraction> reachable_fracs(int first_digit, int last_digit) {
    long cache_key = (long(first_digit) << 32L) + last_digit;
    if (cache.count(cache_key)) {
        return cache[cache_key];
    }

    std::unordered_set<Fraction> results;
    int full_concat = 0;
    for (int d = first_digit; d < last_digit; ++d) {
        full_concat = 10 * full_concat + d;
    }
    results.insert(full_concat);

    for (int i = first_digit + 1; i < last_digit; ++i) {
        for (const Fraction a : reachable_fracs(first_digit, i)) {
            for (const Fraction b : reachable_fracs(i, last_digit)) {
                results.insert(a + b);
                results.insert(a - b);
                results.insert(a * b);
                if (b != 0) {
                    results.insert(a / b);
                }
            }
        }
    }

    cache[cache_key] = results;
    return results;
}

int main() {
    start_time();
    Bignum total = 0;
    for (const Fraction& f : reachable_fracs(1, 10)) {
        if (f > 0 && f.den() == 1) {
            total += f.num();
        }
    }
    printf("Solution: %s\n", +total.to_string());
    end_time();
}
