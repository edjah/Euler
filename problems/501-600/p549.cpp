#include "lib/utility.hh"

int prime_s(int prime, int exponent) {
    int ans = 0;
    int current = 0;
    for (int i = 0; i < exponent; ++i) {
        if (current == 0 || current % prime != 0) {
            ans += prime;
            current = ans;
        }
        current /= prime;
    }
    return ans;
}


std::vector<int> s_table(int n) {
    std::vector<int> tbl = std::vector<int>(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (tbl[i] == 0) {
            for (int j = i; j <= n; j += i) {
                int k = j;
                int exponent = 0;
                while (k % i == 0) {
                    exponent += 1;
                    k /= i;
                }
                tbl[j] = std::max(tbl[j], prime_s(i, exponent));
            }
        }
    }
    return tbl;
}

int main() {
    start_time();

    std::vector<int> s = s_table(1e8);
    long ans = std::accumulate(s.begin(), s.end(), 0L);
    printf("Solution: %li\n", ans);

    end_time();
}
