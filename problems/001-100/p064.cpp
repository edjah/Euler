#include "lib/utility.hh"
#include "lib/decimal.hh"

unsigned _ = Decimal::set_precision(1000);
static const Decimal epsilon = Decimal(1e-20);

int period(int n) {
    Decimal z = Decimal(n).sqrt();
    if (z.floor() * z.floor() == n) {
        return 0;
    }

    int count = 0;
    Decimal first = Decimal::ONE / (z - z.floor());
    z = Decimal::ONE / (z - z.floor());

    while (count == 0 || (z - first).abs() > epsilon) {
        z = Decimal::ONE / (z - z.floor());
        count += 1;
    }
    return count;
}

int main(void) {
    start_time();

    int count = 0;
    for (int i = 1; i <= 10000; ++i) {
        count += (period(i) % 2 == 1);
    }
    printf("Solution: %d\n", count);

    end_time();
}
