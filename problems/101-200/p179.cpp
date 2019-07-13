#include "lib/utility.hh"

constexpr int N = 10000000;
int divisor_counts[N + 1];

int main(void) {
    start_time();

    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            divisor_counts[j] += 1;
        }
    }

    int tot = 0;
    for (int i = 1; i < N; i++) {
        tot += divisor_counts[i] == divisor_counts[i + 1];
    }
    printf("Solution: %d\n", tot);

    end_time();
}
