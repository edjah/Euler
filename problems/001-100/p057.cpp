#include "lib/utility.hh"
#include "lib/fraction.hh"

int main(void) {
    start_time();

    int count = 0;
    Fraction fractional_part = 0;
    for (int i = 0; i < 1000; ++i) {
        fractional_part = 1 / (2 + fractional_part);
        Fraction aprx = 1 + fractional_part;
        count += aprx.num().to_string().size() > aprx.den().to_string().size();
    }

    printf("Solution: %d\n", count);
    end_time();
}
