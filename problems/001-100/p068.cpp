#include "lib/utility.hh"

std::vector<long> five_gon_ring_solutions() {
    std::array<int, 10> digits;
    for (int i = 0; i < 10; ++i) {
        digits[i] = i + 1;
    }

    std::vector<long> solutions;
    for (std::vector<int>& perm : permutations<int>(digits)) {
        std::vector<std::vector<int>> groups;
        int first_value = perm[5] + perm[0] + perm[1];
        bool flag = true;

        for (int i = 0; i < 5; ++i) {
            int tot = perm[5 + i] + perm[i] + perm[(i + 1) % 5];
            if (tot != first_value) {
                flag = false;
                break;
            }
            groups.push_back({perm[5 + i], perm[i], perm[(i + 1) % 5]});
        }

        if (flag) {
            auto start = std::min_element(groups.begin(), groups.end());
            long start_idx = start - groups.begin();
            std::string result = "";
            for (size_t i = 0; i < groups.size(); ++i) {
                result += concat(groups[(i + start_idx) % groups.size()]);
            }
            solutions.push_back(std::stol(result));
        }
    }
    return solutions;
}

int main() {
    start_time();

    long best_solution = 0;
    long limit = 1e16;

    for (long sol : five_gon_ring_solutions()) {
        if (sol < limit && sol > best_solution) {
            best_solution = sol;
        }
    }
    printf("Solution: %li\n", best_solution);

    end_time();
}
