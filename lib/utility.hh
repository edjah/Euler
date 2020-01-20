#pragma once

#include "utility.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <random>
#include <tuple>

std::vector<int> get_primes(int n) {
    int size;
    const int* array = read_primes_less_than(n, &size);
    std::vector<int> result(array, array + size);
    return result;
}

std::unordered_set<int> get_prime_set(int n) {
    int size;
    const int* array = read_primes_less_than(n, &size);
    std::unordered_set<int> result(array, array + size);
    return result;
}

template<typename vec_type>
void print_vec(const std::vector<vec_type>& vec, const std::string& desc = "") {
    if (desc != "") {
        std::cout << desc << " | ";
    }
    std::cout << "vector of size " << vec.size() << " | {";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}

std::vector<std::string> split(const std::string& s, const std::string& delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = s.find(delim, prev);
        if (pos == std::string::npos) {
            pos = s.length();
        }
        std::string token = s.substr(prev, pos-prev);
        if (!token.empty()) {
            tokens.push_back(token);
        }
        prev = pos + delim.length();
    } while (pos < s.length() && prev < s.length());
    return tokens;
}

std::string replace(const std::string& s, const std::string& old,
                    const std::string& replacement) {
    std::string new_s = "";
    size_t pos = 0;
    while (pos < s.size()) {
        size_t new_pos = s.find(old, pos);
        if (new_pos == std::string::npos) {
            new_s.insert(new_s.end(), s.begin() + pos, s.end());
            break;
        } else {
            new_s.insert(new_s.end(), s.begin() + pos, s.begin() + new_pos);
            new_s += replacement;
            pos = new_pos + old.size();
        }
    }
    return new_s;
}


template<typename dtype, typename container_t>
std::vector<std::vector<dtype>> permutations(const container_t& v) {
    std::vector<std::vector<dtype>> result;
    std::vector<dtype> acc(v.begin(), v.end());
    std::sort(acc.begin(), acc.end());

    do {
        result.push_back(acc);
    } while (std::next_permutation(acc.begin(), acc.end()));
    return result;
}

template<typename dtype>
void comb_rec(const std::vector<dtype>& v, const size_t k, size_t start,
              std::vector<dtype>& acc, std::vector<std::vector<dtype>>& res) {
    if (acc.size() == k) {
        res.push_back(acc);
        return;
    }

    for (size_t i = start; i < v.size(); ++i) {
        if (acc.size() + v.size() - i < k) {
            break;
        }
        acc.push_back(v[i]);
        comb_rec(v, k, i + 1, acc, res);
        acc.pop_back();
    }
}


template<typename dtype, typename container_t>
std::vector<std::vector<dtype>> combinations(const container_t& v, size_t k) {
    std::vector<std::vector<dtype>> result;
    std::vector<dtype> acc;
    comb_rec(std::vector<dtype>(v.begin(), v.end()), k, 0, acc, result);
    return result;
}


const char* operator+(const std::string& s) {
    return s.c_str();
}


template<typename container_t>
std::string concat(const container_t& args, const std::string& sep="") {
    std::string result;
    auto it = args.begin();
    for (size_t i = 0; i < args.size(); ++i) {
        result += std::to_string(*it++);
        if (i != args.size() - 1) {
            result += sep;
        }
    }
    return result;
}

template<typename T>
std::string concat(std::initializer_list<T> args, const std::string& sep="") {
    return concat(std::vector(args.begin(), args.end()), sep);
}

std::vector<int> totient_table(int n) {
    std::vector<int> phi(n + 1, 0);
    phi[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            for (int j = 2; i * j <= n; ++j) {
                if (phi[j] == 0) {
                    continue;
                }
                int q = j;
                int f = i - 1;
                while (q % i == 0) {
                    f *= i;
                    q /= i;
                }
                phi[i * j] = f * phi[q];
            }
        }
    }

    return phi;
}

std::tuple<long, long, long> egcd(long a, long b) {
    // returns (d, x, y) such that x*a + y*b == d
    if (b == 0) {
        return {a, 1, 0};
    } else {
        auto [d, x, y] = egcd(b, a % b);
        return {d, y, x - (a / b) * y};
    }
}

std::vector<std::vector<int>> prime_factors_table(unsigned n) {
    std::vector<std::vector<int>> tbl{n + 1};

    for (unsigned i = 2; i <= n; ++i) {
        if (tbl[i].empty()) {
            for (unsigned j = i; j <= n; j += i) {
                unsigned k = j;
                while (k % i == 0) {
                    tbl[j].push_back(i);
                    k /= i;
                }
            }
        }
    }
    return tbl;
}

std::vector<int> digits_of_long(unsigned long n) {
    if (n == 0) {
        return {0};
    }

    std::vector<int> res;
    while (n > 0) {
        res.push_back(n % 10);
        n /= 10;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

template <typename container_t>
void random_shuffle(container_t& c, int seed = -1) {
    seed = (seed == -1) ? time(nullptr) : seed;
    static auto rng = std::default_random_engine(seed);
    std::shuffle(std::begin(c), std::end(c), rng);
}

bool starts_with(const std::string& s, const std::string& prefix,
                 size_t start = 0) {
    return s.compare(start, prefix.size(), prefix) == 0;
}

long bsearch_lower_bound(long lo, long hi, bool(*predicate)(long)) {
    while (lo < hi) {
        long mid = (lo + hi) / 2;
        if (predicate(mid)) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

template<typename T>
std::vector<T> arange(T start, T stop, T step = 1) {
    std::vector<T> values;
    for (T value = start; value < stop; value += step) {
        values.push_back(value);
    }
    return values;
}

template<typename T>
std::vector<T> arange(T stop) {
    return arange<T>(0, stop);
}

template<typename T>
std::pair<size_t, T> argmin(const std::vector<T>& vec, const size_t start = 0) {
    T lowest_value = std::numeric_limits<T>::max();
    size_t best_idx = 0;

    for (size_t i = start; i < vec.size(); ++i) {
        if (vec[i] < lowest_value) {
            lowest_value = vec[i];
            best_idx = i;
        }
    }

    return {best_idx, lowest_value};
}

template<typename T>
std::pair<size_t, T> argmax(const std::vector<T>& vec, const size_t start = 0) {
    T highest_value = std::numeric_limits<T>::lowest();
    size_t best_idx = 0;

    for (size_t i = start; i < vec.size(); ++i) {
        if (vec[i] > highest_value) {
            highest_value = vec[i];
            best_idx = i;
        }
    }

    return {best_idx, highest_value};
}


template<typename AccumT, typename container_t>
AccumT vector_sum(const container_t& vec) {
    AccumT tot = AccumT();
    for (auto x : vec) {
        tot += x;
    }
    return tot;
}

template<typename T>
T vector_sum(const std::vector<T>& vec) {
    return vector_sum<T>(vec);
}


template<typename container_t>
std::vector<size_t> idx_sort(const container_t& vec, bool reverse = false) {
    std::vector<size_t> idx = arange(vec.size());
    std::sort(idx.begin(), idx.end(), [&vec, reverse](size_t i, size_t j) {
        return reverse ? (vec[i] > vec[j]) : (vec[i] < vec[j]);
    });
    return idx;
}


// from: https://www.variadic.xyz/2018/01/15/hashing-stdpair-and-stdtuple/
template<typename T>
inline void hash_combine(size_t& seed, const T& val) {
    std::hash<T> hasher;
    seed ^= hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


namespace std {
    template <typename T1, typename T2>
    struct hash<pair<T1, T2>> {
        size_t operator()(const pair<T1, T2>& p) const {
            size_t seed = 0;
            hash_combine(seed, p.first);
            hash_combine(seed, p.second);
            return seed;
        }
    };

    template <typename... TupleArgs>
    struct hash<tuple<TupleArgs...>> {
      private:
        // this is a termination condition: N == sizeof...(TupleArgs)
        template <size_t N = 0>
        inline typename std::enable_if<N == sizeof...(TupleArgs), void>::type
        hash_combine_tup(size_t& seed, const tuple<TupleArgs...>& tup) const {
        }

        // this is the computation workhorse: N < sizeof...(TupleArgs)
        template <size_t N = 0>
        inline typename std::enable_if<N != sizeof...(TupleArgs), void>::type
        hash_combine_tup(size_t& seed, const tuple<TupleArgs...>& tup) const {
            hash_combine(seed, std::get<N>(tup));
            hash_combine_tup<N + 1>(seed, tup);
        }


      public:
        size_t operator()(const tuple<TupleArgs...>& tup) const {
            size_t seed = 0;
            hash_combine_tup(seed, tup);
            return seed;
        }
    };

    template <>
    struct hash<__int128> {
        size_t operator()(const __int128& p) const {
            const uint64_t* data = reinterpret_cast<const uint64_t*>(&p);

            size_t seed = 0;
            hash_combine(seed, data[0]);
            hash_combine(seed, data[1]);
            return seed;
        }
    };

    template <>
    struct hash<unsigned __int128> {
        size_t operator()(const unsigned __int128& p) const {
            const uint64_t* data = reinterpret_cast<const uint64_t*>(&p);

            size_t seed = 0;
            hash_combine(seed, data[0]);
            hash_combine(seed, data[1]);
            return seed;
        }
    };
}
