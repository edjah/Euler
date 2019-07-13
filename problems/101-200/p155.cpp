#include "lib/utility.hh"
#include "lib/small_fraction.hh"

// max numerator/denominator is 4181
constexpr int maximum_numerator = 5000;
static bool cache[maximum_numerator][maximum_numerator];

int D(int n) {
    std::vector<Fraction> caps[n + 1];
    caps[1].push_back(Fraction(1, 1));

    for (int num_caps = 2; num_caps <= n; ++num_caps) {
        for (int i = 1; i <= num_caps / 2; ++i) {
            int j = num_caps - i;

            for (const Fraction& c1 : caps[i]) {
                for (const Fraction& c2 : caps[j]) {
                    for (auto& res : {c1 + c2, 1 / (1/c1 + 1/c2)}) {
                        if (!cache[res.num()][res.den()]) {
                            cache[res.num()][res.den()] = 1;
                            caps[num_caps].push_back(res);
                        }
                    }
                }
            }
        }
    }

    int answer = 0;
    for (int i = 0; i < maximum_numerator; ++i) {
        for (int j = 0; j < maximum_numerator; ++j) {
            answer += cache[i][j];
        }
    }
    return answer;
}

int main() {
    start_time();
    printf("Solution: %d\n", D(18));
    end_time();
}
