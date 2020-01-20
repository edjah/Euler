/*
We can get: pq + pr + rq = 1  -->  r = (1 - pq)/(p + q)
Dumb brute force below...

A smarter solution would be to rewrite as (p + r) * (q + r) == r^2 + 1
and then look at the divisors of r^2 + 1
*/
#include "lib/utility.hh"

int main() {
    start_time();

    size_t desired_idx = 150000;
    std::unordered_set<__int128> nums;


    // 1x = 779603369894231610
    // 2x = 6486885711472350
    // 4x = 2134329764599620
    // 8x = 1884161251122450

    for (__int128 q = -1; nums.size() < 8 * desired_idx; --q) {
        #pragma omp parallel for
        for (__int128 p = 1; p < -q; ++p) {
            __int128 num = 1 - p*q;
            __int128 den = p + q;
            if (num % den == 0) {
                #pragma omp critical
                {
                    __int128 r = num / den;
                    nums.insert(p * q * r);
                }
            }
        }
    }

    std::vector<__int128> sorted_nums(nums.begin(), nums.end());
    std::sort(sorted_nums.begin(), sorted_nums.end());
    printf("Solution: %li\n", (long) sorted_nums[desired_idx - 1]);

    end_time();
}
