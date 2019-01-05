#include "lib/utility.hh"

bool is_perm(int a, int b) {
    std::string x = std::to_string(a);
    std::string y = std::to_string(b);
    return std::is_permutation(x.begin(), x.end(), y.begin());
}

int main(void) {
    start_time();

    std::vector<int> table = totient_table(10000000);
    std::vector<double> ratios;
    for (size_t i = 0; i < table.size(); ++i) {
        if (i > 1 && is_perm(i, table[i])) {
            ratios.push_back((double) i / table[i]);
        } else {
            ratios.push_back(std::numeric_limits<double>::infinity());
        }
    }
    int n = std::min_element(ratios.begin(), ratios.end()) - ratios.begin();
    printf("Solution: %d\n", n);

    end_time();
}
