#include "lib/utility.hh"

struct triple {
    int a;
    int b;
    int c;

    bool operator==(const triple& other) const {
        return other.a == a && other.b == b && other.c == c;
    }
};

namespace std {
    template <>
    struct hash<triple> {
        size_t operator()(const triple& t) const {
            return t.a * t.b * t.c;
        }
    };
}


std::unordered_set<triple> make_triples(int perim_limit) {
    std::unordered_set<triple> result;

    int m_limit = 1 + sqrt(perim_limit);
    for (int m = 2; m < m_limit; ++m) {
        for (int n = 1; n < m; ++n) {
            int a = m*m - n*n;
            int b = 2 * m * n;
            int c = m*m + n*n;

            if (a > b) {
                std::swap(a, b);
            }

            int k = 1;
            while (k * (a + b + c) <= perim_limit) {
                result.insert({k * a, k * b, k * c});
                k++;
            }
        }
    }

    return result;
}

int count_unique_perim(const std::unordered_set<triple>& triples) {
    std::unordered_map<int, int> perim_counts;
    for (const triple& t : triples) {
        perim_counts[t.a + t.b + t.c] += 1;
    }

    int result = 0;
    for (const auto& [key, value] : perim_counts) {
        result += (value == 1);
    }
    return result;
}

int main(void) {
    start_time();
    std::unordered_set<triple> triples = make_triples(1500000);
    printf("Solution: %d\n", count_unique_perim(triples));
    end_time();
}
