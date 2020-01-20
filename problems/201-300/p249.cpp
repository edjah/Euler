#include "lib/utility.hh"

using namespace std;

long count_mod = 1e16;

long count(int prime_limit) {
    // DP[i][k] = num of subsets (mod 10^16) of {p[0], ..., p[i]} that add to k
    // Let n = num primes and t = sum of primes
    // Runs in O(nt) time and can be optimized to O(k) space
    vector<int> primes = get_primes(prime_limit);

    int max_total = 0;
    for (int p : primes) {
        max_total += p;
    }

    // counts the number (modulo 10^16) of subsets that generate a given total
    vector<long> DP_row(max_total, 0);

    for (int p : primes) {
        vector<long> new_DP_row = DP_row;

        // count the singleton prime
        new_DP_row[p] = (DP_row[p] + 1) % count_mod;

        // count the ways using other subsets
        for (int tot = 1; tot <= max_total - p; ++tot) {
            new_DP_row[tot + p] = (DP_row[tot + p] + DP_row[tot]) % count_mod;
        }

        DP_row = new_DP_row;
    }

    long ans = 0;
    for (int p : get_primes(max_total)) {
        ans = (ans + DP_row[p]) % count_mod;
    }
    return ans;
}

int main() {
    start_time();
    printf("%li\n", count(5000));
    end_time();
}
