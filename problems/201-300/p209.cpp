#include "lib/utility.hh"

using namespace std;
using input = tuple<int, int, int, int, int, int>;

vector<input> possible_inputs;

int eval_table(uint64_t tbl, int a, int b, int c, int d, int e, int f) {
    int idx = a + 2*b + 4*c + 8*d + 16*e + 32*f;
    return tbl & (1 << idx);
}

int test(uint64_t tbl, int i) {
    auto [a, b, c, d, e, f] = possible_inputs[i];
    int x = eval_table(tbl, a, b, c, d, e, f);
    int y = eval_table(tbl, b, c, d, e, f, a ^ (b & c));
    return (x & y) == 0;
}

uint64_t dfs(uint64_t tbl, int num_inputs) {
    if (!test(tbl, num_inputs)) {
        return 0;
    }

    if (num_inputs == 64) {
        return 1;
    }

    uint64_t ans = dfs(tbl, num_inputs + 1) + dfs((1 << num_inputs) | tbl, num_inputs + 1);

    if (num_inputs < 35) {
        fprintf(stderr, "finished level %d\n", num_inputs);
    }
    return ans;
}

int main() {
    start_time();

    for (int i = 0; i < 64; ++i) {
        possible_inputs.push_back({
            i & (1 << 0), i & (1 << 1), i & (1 << 2),
            i & (1 << 3), i & (1 << 4), i & (1 << 5)
        });
    }

    printf("Solution: %li\n", dfs(0, 0));

    end_time();
}
