#include "lib/utility.hh"

double target = 0.5;

void subset_sums(const std::vector<double>& nums, double acc,
                 size_t i, double remain, std::vector<double>& results,
                 bool check_too_small) {
    if ((check_too_small && acc + remain < target) || acc > target) {
        return;
    }

    if (i >= nums.size()) {
        results.push_back(acc);
        return;
    }

    remain -= nums[i];
    subset_sums(nums, acc + nums[i], i + 1, remain, results, check_too_small);
    subset_sums(nums, acc, i + 1, remain, results, check_too_small);
}

int max_prime_factor(int n) {
    int p = 1;
    while (n > 1) {
        p++;
        while (n % p == 0) {
            n /= p;
        }
    }
    return p;
}

bool close(double a, double b) {
    return abs(a - b) < 1e-15;
}

int let_me_count_the_ways() {
    std::vector<double> left_nums, right_nums;
    std::vector<int> valid_nums;

    for (int n = 2; n <= 80; ++n) {
        if (max_prime_factor(n) <= 13 && max_prime_factor(n) != 11) {
            valid_nums.push_back(n);
        }
    }

    size_t split = 2 + valid_nums.size() / 2;
    for (size_t i = 0; i < split; ++i) {
        left_nums.push_back(1.0 / (valid_nums[i] * valid_nums[i]));
    }
    for (size_t i = split; i < valid_nums.size(); ++i) {
        right_nums.push_back(1.0 / (valid_nums[i] * valid_nums[i]));
    }

    std::vector<double> x_sums, y_sums;
    double pi_sq_over_six_minus_one = (M_PI * M_PI / 6.0) - 1;
    subset_sums(left_nums, 0, 0, pi_sq_over_six_minus_one, x_sums, true);
    subset_sums(right_nums, 0, 0, pi_sq_over_six_minus_one, y_sums, false);

    std::sort(x_sums.begin(), x_sums.end());
    std::sort(y_sums.begin(), y_sums.end(), std::greater<double>());

    int count = 0;
    size_t i = 0;
    size_t j = 0;

    while (i < x_sums.size() && j < y_sums.size()) {
        double r = x_sums[i] + y_sums[j];
        if (close(r, target)) {
            int nx = 0;
            int ny = 0;

            while (i + nx < x_sums.size() && close(x_sums[i + nx], x_sums[i])) {
                nx++;
            }
            while (j + ny < y_sums.size() && close(y_sums[j + ny], y_sums[j])) {
                ny++;
            }

            i += nx;
            j += ny;
            count += nx * ny;
        } else if (r < target) {
            i++;
        } else if (r > target) {
            j++;
        }
    }

    return count;
}



int main() {
    start_time();
    printf("Solution: %d\n", let_me_count_the_ways());
    end_time();
}
