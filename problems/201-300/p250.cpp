#include "lib/utility.hh"

using namespace std;

long count_mod = 1e16;
long DP[250250][250];


long count(vector<int>& A) {
    // DP[i][k] counts the number (modulo 10^16) of subsets of
    // {A[0] ..., A[i]} that sum to `k` mod 250
    // Runs in O(nk) time. Could be optimized to O(k) space
    int sz = A.size();

    // initialize the counts with the singleton sets
    for (int i = 0; i < sz; ++i) {
        DP[i][A[i]] = 1;
    }

    for (int i = 1; i < sz; ++i) {
        for (int tot = 0; tot < 250; ++tot) {
            // number of subsets if we don't include A[i]
            DP[i][tot] = (DP[i][tot] + DP[i - 1][tot]) % count_mod;

            // number of subsets if we do include A[i]
            int tot2 = tot - A[i];
            if (tot2 < 0) {
                tot2 = 250 + tot2;
            }
            DP[i][tot] = (DP[i][tot] + DP[i - 1][tot2]) % count_mod;
        }
    }

    return DP[sz - 1][0];
}

int main() {
    start_time();

    vector<int> A;
    for (int i = 1; i <= 250250; ++i) {
        A.push_back(mod_exp(i, i, 250));
    }

    long ans = count(A);
    printf("Solution: %li\n", ans);

    end_time();
}
