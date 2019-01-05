#include "lib/utility.hh"
#include "lib/fraction.hh"

int main(void) {
    start_time();

    int target_num = 3;
    int target_den = 7;
    int max_den = 1000000;
    double target = double(target_num) / double(target_den);
    Fraction best = Fraction(0);

    for (int den = 1; den <= max_den; ++den) {
        int num = target * den;
        while (gcd(num, den) != 1 && num > 0) {
            num -= 1;
        }
        Fraction curr = Fraction(num, den);
        if (den != target_den && curr > best) {
            best = curr;
        }
    }

    printf("Solution: %s\n", +best.to_string());

    end_time();
}
