#include "lib/utility.hh"
#include "lib/fraction.hh"


Fraction e_convergent(unsigned max, unsigned n = 0) {
    if (max == 0) {
        return 0;
    }

    int k = 1;
    if (n % 3 == 1) {
        k = 2 * (1 + n / 3);
    }

    if (n + 1 >= max) {
        return Fraction(1, k);
    }
    return Fraction(1) / (k + e_convergent(max, n + 1));
}

int main(void) {
    start_time();

    int total = 0;
    Fraction e_approx = 2 + e_convergent(100 - 1);
    for (char c : e_approx.num().to_string()) {
        total += (c - '0');
    }
    printf("Solution: %d\n", total);

    end_time();
}
