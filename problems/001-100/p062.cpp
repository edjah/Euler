#include "lib/utility.hh"
#include "lib/bignum.hh"

#define CUBE_LIMIT 10000
#define NUM_CUBES 5

Bignum solve() {
    // group cubes by their permutations
    std::unordered_map<std::string, std::vector<Bignum>> cubes;
    for (int i = 0; i < CUBE_LIMIT; ++i) {
        Bignum b = Bignum(i).pow(3);
        std::string digits = b.to_string();
        std::sort(digits.begin(), digits.end());
        cubes[digits].push_back(b);
    }

    // find the smallest cube which is 5-permutable
    Bignum res = Bignum("9999999999999999999999999999999999999999999999999999");
    for (auto& [digits, nums] : cubes) {
        if (nums.size() == NUM_CUBES) {
            res = std::min(res, *std::min_element(nums.begin(), nums.end()));
        }
    }
    return res;
}

int main(void) {
    start_time();
    printf("Solution: %s\n", solve().to_string().c_str());
    end_time();
}
