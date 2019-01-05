#include "lib/utility.hh"

// should have a >= b >= c
double solution(int a, int b, int c) {
    double x = 1.0 * (a * b) / (b + c);
    return sqrt(x*x + b*b) + sqrt((a - x) * (a - x) + c * c);
}


int count_solutions(int M) {
    static std::vector<int> count_cache(4000, -1);

    int count = 0;
    for (int a = 1; a <= M; ++a) {
        if (count_cache[a] != -1) {
            count += count_cache[a];
            continue;
        }
        int sub_count = 0;
        for (int b = 1; b <= a; ++b) {
            for (int c = 1; c <= b; ++c) {
                double s = solution(a, b, c);
                sub_count += (abs(s - round(s)) < 1e-6);
            }
        }
        count_cache[a] = sub_count;
        count += sub_count;
    }
    return count;
}

int main(void) {
    start_time();
    auto predicate = [](long x) { return count_solutions(x) < 1000000; };
    printf("Solution: %li\n", bsearch_lower_bound(1, 2000, predicate));
    end_time();
}
