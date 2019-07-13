#include "lib/utility.h"

#define NUM_TOSSES 1000


double P(double f) {
    static double res[NUM_TOSSES + 1][NUM_TOSSES + 1];

    for (int total = NUM_TOSSES; total >= 0; --total) {
        if (total == NUM_TOSSES) {
            for (int wins = 0; wins <= total; ++wins) {
                int losses = total - wins;
                double log_score = wins * log(1 + 2*f) + losses * log(1 - f);
                res[wins][losses] = (log_score >= log(1e9));
            }
        } else {
            for (int wins = 0; wins <= total; ++wins) {
                int losses = total - wins;
                double p = (res[wins + 1][losses] + res[wins][losses + 1]) / 2;
                res[wins][losses] = p;
            }
        }
    }
    return res[0][0];
}

double linear_search_best_f() {
    double best_f = 0, best_p = 0;
    for (double f = 0; f < 1.0; f += 0.01) {
        if (P(f) > best_p) {
            best_p = P(f);
            best_f = f;
        }
    }
    return best_f;
}

int main() {
    start_time();
    double f = linear_search_best_f();
    printf("Solution: %.12f\n", P(f));
    end_time();
}
