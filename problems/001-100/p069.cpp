#include "lib/utility.hh"

int main(void) {
    start_time();

    std::vector<int> table = totient_table(1000000);
    std::vector<double> ratios;
    for (size_t i = 0; i < table.size(); ++i) {
        ratios.push_back((double) i / std::max(1, table[i]));
    }
    int n = std::max_element(ratios.begin(), ratios.end()) - ratios.begin();
    printf("Solution: %d\n", n);

    end_time();
}
