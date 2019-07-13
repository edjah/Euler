/*
    y = (x - a) and z = (x - 2a)   =>   x^2 - y^2 - z^2 = (x - a)(5a - x)
    (x - a)(5a - x) = n   =>   (x - a)|n  and (5a - x)|n
    system of equations: d = (x - a) and c = (5a - x)
    solution:   x = (c + 5d) / 4  and   a = (c + d) / 4
*/

#include "lib/utility.hh"

constexpr int N = 1000000;

std::vector<int> divisors[N + 1];

void populate_divisors(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            divisors[j].push_back(i);
        }
    }
}

int count_sols(int n) {
    int count = 0;

    for (int d : divisors[n]) {
        int c = n / d;
        int a = (d + c) / 4;

        int x = (c + 5*d) / 4;
        int y = x - a;
        int z = y - a;

        if (x > 2 * a && x*x - y*y - z*z == n) {
            count++;
        }
    }
    return count;
}

int main(void) {
    start_time();

    populate_divisors(N);
    int count = 0;
    for (int n = 1; n < N; ++n) {
        count += (count_sols(n) == 10);
    }
    printf("Solution: %d\n", count);

    end_time();
}
