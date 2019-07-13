/*
    b(b - 1) / (t(t - 1)) = 1 / 2
    t(t - 1) - 2b(b - 1) = 0
    t^2 - t - 2b^2 + 2b = 0
    This is a Diophantine equation.
    Solved via: http://www.alpertron.com.ar/QUAD.HTM
*/
#include "lib/utility.hh"

std::pair<long, long> diophantine_solve(int n) {
    if (n <= 0) {
        return {0, 1};
    }
    auto [xn_1, yn_1] = diophantine_solve(n - 1);
    long xn = 3*xn_1 + 4*yn_1 - 3;
    long yn = 2*xn_1 + 3*yn_1 - 2;
    return {xn, yn};
}

int main(void) {
    start_time();
    for (int i = 0;; ++i) {
        auto [t, b] = diophantine_solve(i);
        if (t > 1e12) {
            printf("Solution: %li\n", b);
            break;
        }
    }
    end_time();
}

