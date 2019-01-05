#include "lib/utility.hh"

bool combo_works(const std::vector<int>& a, const std::vector<int>& b) {
    for (int n = 1; n < 10; ++n) {
        int square = n * n;
        int first_digit = square / 10;
        int second_digit = square % 10;

        bool flag = false;
        for (int i : a) {
            for (int j : b) {
                if ((i == first_digit && j == second_digit) ||
                    (i == second_digit && j == first_digit)) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }

        if (!flag) {
            return false;
        }
    }

    return true;
}

int main(void) {
    start_time();

    // generate 6-size combinations of {0 .. 9}.
    std::vector<std::vector<int>> combos = combinations<int>(arange(10), 6);
    for (auto& combo : combos) {
        // add a 9 when the combo has a 6 or vice versa
        if (std::find(combo.begin(), combo.end(), 6) != combo.end()) {
            combo.push_back(9);
        } else if (std::find(combo.begin(), combo.end(), 9) != combo.end()) {
            combo.push_back(6);
        }
    }

    // try out all possible pairs of combos. each pair is intrinsically distinct
    int successes = 0;
    for (size_t i = 0; i < combos.size(); ++i) {
        for (size_t j = i; j < combos.size(); ++j) {
            successes += combo_works(combos[i], combos[j]);
        }
    }
    printf("Solution: %d\n", successes);

    end_time();
}
