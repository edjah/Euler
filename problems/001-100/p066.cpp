#include "lib/utility.hh"

#include "lib/decimal.hh"
#include "lib/fraction.hh"

unsigned _ = Decimal::set_precision(1000);

std::vector<int> sqrt_continued_frac(int n, int num_digits) {
    std::vector<int> digits;

    Decimal z = Decimal(n).sqrt();
    digits.push_back(z.to_long());

    if (z.floor() * z.floor() == n) {
        return digits;
    }

    for (int i = 0; i < num_digits; ++i) {
        z = Decimal::ONE / (z - z.floor());
        digits.push_back(z.to_long());
    }
    return digits;
}


Bignum sqrt_convergents_min_sol(int D) {
    size_t last_start = 0;
    size_t num_convergents = 2;

    while (true) {
        std::vector<int> digits = sqrt_continued_frac(D, num_convergents);
        for (size_t i = last_start; i < digits.size(); ++i) {
            Fraction approx = digits[i];
            for (int j = i - 1; j >= 0; --j) {
                approx = digits[j] + Fraction::ONE / approx;
            }

            Bignum x = approx.num();
            Bignum y = approx.den();
            if (x*x - D*y*y == 1) {
                return x;
            }
        }
        num_convergents *= 2;
    }
}


int main(void) {
    start_time();

    Bignum largest_solution = 0;
    long best_D = 0;
    for (long D = 2; D <= 1000; ++D) {
        if (long(sqrt(D)) * long(sqrt(D)) == D) {
            continue;
        }
        Bignum sol = sqrt_convergents_min_sol(D);
        if (sol > largest_solution) {
            best_D = D;
            largest_solution = sol;
        }
    }

    printf("Largest minimal x: %s\n", +largest_solution.to_string());
    printf("Solution: %li\n", best_D);

    end_time();
}
