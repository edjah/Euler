#include "lib/utility.hh"
#include "lib/decimal.hh"

int digital_expansion_sum(int n) {
    if (round(sqrt(n)) * round(sqrt(n)) == n) {
        return 0;
    }

    std::string expansion = Decimal(n).sqrt().to_string();
    assert(expansion.size() > 100 && expansion[1] == '.');
    expansion[1] = '0';

    int total = 0;
    for (int i = 0; i < 101; ++i) {
        total += expansion[i] - '0';
    }
    return total;
}

int main(void) {
    start_time();

    Decimal::set_precision(1000);
    int total = 0;
    for (int i = 1; i <= 100; ++i) {
        total += digital_expansion_sum(i);
    }
    printf("Solution: %d\n", total);

    end_time();
}
