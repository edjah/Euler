#include <iostream>
#include <vector>
#include "lib/utility.h"
using namespace std;

#define N 20000000
#define R 15000000

vector<int> prime_factors[N + 1];

void init_prime_factors() {
    for (int i = 2; i <= N; i++) {
        if (prime_factors[i].size() == 0) {
            for (int j = i; j <= N; j += i) {
                int k = j;
                while (k % i == 0) {
                    prime_factors[j].push_back(i);
                    k /= i;
                }
            }
        }
    }
}

unsigned long nCr_factor_sum(int n, int r) {
    char* count = (char*) calloc(n + 1, sizeof(unsigned char));
    r = min(r, n - r);

    for (int i = 0; i < r; i++) {
        for (int x : prime_factors[n - i]) {
            count[x] += 1;
        }
        for (int x : prime_factors[i + 1]) {
            count[x] -= 1;
        }
    }

    unsigned long res = 0;
    for (int i = 0; i <= n; i++) {
        res += count[i] * i;
    }
    free(count);

    return res;
}

int main(void) {
    start_time();

    init_prime_factors();
    unsigned long ans = nCr_factor_sum(N, R);
    cout << "Solution: " << ans << endl;

    end_time();
}
