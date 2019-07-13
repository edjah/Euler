#include "lib/utility.hh"

constexpr int N = 50000000;

int sol_count[N];

void count_solutions() {
    for (long x = 0; x < 2 * N; x++) {
        for (long a = x / 5 + 1; a <= x / 2; a++) {
            long n = (5*a - x) * (x - a);
            if (n >= N) {
                break;
            }

            long y = x - a;
            long z = y - a;

            if (n < N && x > 2 * a && x*x - y*y - z*z == n) {
                sol_count[n]++;
            }
        }
    }
}

int main(void) {
    start_time();

    count_solutions();
    int count = 0;
    for (int n = 0; n < N; n++) {
        count += sol_count[n] == 1;
    }
    printf("Solution: %d\n", count);

    end_time();
}
