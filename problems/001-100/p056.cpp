#include "lib/utility.hh"
#include "lib/bignum.hh"

int digital_sum(int a, int b) {
    int total = 0;
    std::string digits = Bignum(a).pow(b).to_string();
    for (const char c : digits) {
        total += c - '0';
    }
    return total;
}

int main(void) {
    start_time();
    int max_sum = 0;
    for (int a = 1; a < 100; ++a) {
        for (int b = 1; b < 100; ++b) {
            max_sum = std::max(max_sum, digital_sum(a, b));
        }
    }
    printf("Solution: %d\n", max_sum);
    end_time();
}
