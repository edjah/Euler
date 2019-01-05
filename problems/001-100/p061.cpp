#include "lib/utility.hh"

#define START_POS 3
#define END_POS 9

std::vector<int> fig[END_POS];

void fill_figurate(std::vector<int>& fig, int (*formula)(int)) {
    for (int i = 0; formula(i) < 10000; ++i) {
        if (formula(i) >= 1000) {
            fig.push_back(formula(i));
        }
    }
}

int search(std::vector<int>& numbers, bool taken[]) {
    if (numbers.size() == END_POS - START_POS) {
        if (numbers.back() % 100 == numbers.front() / 100) {
            print_vec(numbers);
            return std::accumulate(numbers.begin(), numbers.end(), 0);
        } else {
            return 0;
        }
    }

    for (int pos = START_POS; pos < END_POS; ++pos) {
        if (!taken[pos]) {
            taken[pos] = true;
            for (int x : fig[pos]) {
                if (numbers.empty() || numbers.back() % 100 == x / 100) {
                    numbers.push_back(x);
                    int result = search(numbers, taken);
                    if (result > 0) {
                        return result;
                    }
                    numbers.pop_back();
                }
            }
            taken[pos] = false;
        }
    }
    return 0;

}

int main(void) {
    start_time();

    fill_figurate(fig[3], [](int n) { return n * (n + 1) / 2; });
    fill_figurate(fig[4], [](int n) { return n * n; });
    fill_figurate(fig[5], [](int n) { return n * (3*n - 1) / 2; });
    fill_figurate(fig[6], [](int n) { return n * (2*n - 1); });
    fill_figurate(fig[7], [](int n) { return n * (5*n - 3) / 2; });
    fill_figurate(fig[8], [](int n) { return n * (3*n - 2); });

    std::vector<int> numbers;
    bool taken[END_POS] = {};
    printf("Solution: %d\n", search(numbers, taken));

    end_time();
}
