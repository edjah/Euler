#include "lib/utility.hh"
#include "lib/matrix.hh"

constexpr int64_t mod = 20092010;
constexpr int lag = 2000;


int64_t fast_fibonacci(uint64_t n) {
    Matrix current = Matrix(lag, lag);

    for (int i = 0; i < lag - 1; ++i) {
        current[i][i + 1] = 1;
    }
    current[lag - 1][0] = current[lag - 1][1] = 1;
    Matrix result = Matrix(lag, 1).add(1);

    while (n > 0) {
        if (n % 2 == 1) {
            result = current.mm(result).mod(mod);
        }
        current = current.mm(current).mod(mod);
        n /= 2;
    }

    result = 0 + result;
    return result[0][0] % mod;
}


int main() {
    start_time();
    int64_t sol = fast_fibonacci(1e18);
    printf("Solution: %li\n", sol);
    end_time();
}
