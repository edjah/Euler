#include "lib/utility.hh"

constexpr int limit = 12001;
std::vector<int> min_sols = std::vector<int>(limit, INT_MAX);

// This takes a partition of prime factors in `nums` represented by a restricted
// growth string `a`. It computes the product of each partition and computes the
// sum of the products. Then, this computes the number of ones that would need
// to be added to it a product-sum set of size `num_ele`. If the number
// represented by the product `prod` of the prime factors in `nums` is less than
// the existing minimum product-sum number for a set of size `num_ele`, then
// `min_sols[num_ele]` is set to `prod`.
void visit_partition(const std::vector<int>& nums, const std::vector<int>& a) {
    int num_groups = 1 + *std::max_element(a.begin(), a.end());
    std::vector<int> groups = std::vector<int>(num_groups, 1);

    int prod = 1;
    for (size_t i = 0; i < a.size(); ++i) {
        groups[a[i]] *= nums[i];
        prod *= nums[i];
    }

    int sum = std::accumulate(groups.begin(), groups.end(), 0);
    if (sum <= prod) {
        // number of ones that need to added on it (prod - sum)
        int num_ele = num_groups + (prod - sum);
        if (num_ele < limit && prod < min_sols[num_ele]) {
            min_sols[num_ele] = prod;
        }
    }
}

// This enumerates all of the partitions of a multiset. source: TAOCP pre-fasc3b
// This could be optimized by avoiding generating duplicate partitions.
void enumerate_partitions(const std::vector<int>& numbers) {
    std::vector<int> a = std::vector<int>(numbers.size());
    std::vector<int> b = std::vector<int>(numbers.size(), 1);
    int m = 1;
    int n = int(a.size()) - 1;

    if (n < 0) {
        return;
    }

    if (n == 0) {
        visit_partition(numbers, a);
        return;
    }

    while (1) {
        visit_partition(numbers, a);
        if (a[n] == m) {
            int j = n - 1;
            while (a[j] == b[j]) {
                j -= 1;
            }
            if (j == 0) {
                break;
            }
            a[j] += 1;

            m = b[j] + (a[j] == b[j]);
            for (j = j + 1; j < n; ++j) {
                a[j] = 0;
                b[j] = m;
            }
            a[n] = 0;
        } else {
            a[n] += 1;
        }
    }
}

int main(void) {
    start_time();

    std::vector<std::vector<int>> prime_factors = prime_factors_table(13000);

    for (size_t i = 2; i < prime_factors.size(); ++i) {
        enumerate_partitions(prime_factors[i]);
    }
    std::unordered_set<int> uniq{min_sols.begin() + 2, min_sols.end()};
    int total = std::accumulate(uniq.begin(), uniq.end(), 0);
    printf("Solution: %d\n", total);

    end_time();
}
