#include "lib/utility.hh"

// constexpr int num_black = 60;
// constexpr int num_white = 40;

constexpr int num_black = 6;
constexpr int num_white = 6;


long single_color_cache[num_black + 1][num_black + 1];
// long mixed_color_cache[num_black + 1][num_black + 1][num_black + 1][num_black + 1];
long mixed_color_cache[num_black + 1][num_black + 1][num_black + 1][num_black + 1][3][2][2];


long count_single_color(int min_group_sz, int remaining) {
    if (remaining == 0) {
        return 1;
    } else if (min_group_sz > remaining) {
        return 0;
    }

    long& cache_v = single_color_cache[min_group_sz][remaining];
    if (cache_v != -1) {
        return cache_v;
    }

    long ans = 0;
    for (int group_sz = min_group_sz; group_sz <= remaining; ++group_sz) {
        ans += count_single_color(group_sz, remaining - group_sz);
    }

    cache_v = ans;
    return ans;
}

// long count_mixed_color(int min_b, int remaining_b, int min_w, int remaining_w) {
//     if (remaining_b == 0 && remaining_w == 0) {
//         return 1;
//     } else if (min_b > remaining_b || min_w > remaining_w) {
//         return 0;
//     }

//     long& cache_v = mixed_color_cache[min_b][remaining_b][min_w][remaining_w];
//     if (cache_v != -1) {
//         return cache_v;
//     }

//     long ans = 0;
//     for (int mb = min_b; mb <= remaining_b; ++mb) {
//         for (int mw = min_w; mw <= remaining_w; ++mw) {
//             ans += count_mixed_color(mb, remaining_b - mb, mw, remaining_w - mw);
//         }
//     }

//     cache_v = ans;
//     return ans;
// }

long count_mixed_color0(int min_b, int remaining_b, int min_w, int remaining_w) {
    if (remaining_b == 0 && remaining_w == 0) {
        return 1;
    } else if (min_b > remaining_b || min_w > remaining_w) {
        return 0;
    }

    long& cache_v = mixed_color_cache[min_b][remaining_b][min_w][remaining_w][0][0][0];
    if (cache_v != -1) {
        return cache_v;
    }

    long ans = 0;
    for (int mb = min_b; mb <= remaining_b; ++mb) {
        for (int mw = min_w; mw <= remaining_w; ++mw) {
            ans += count_mixed_color0(mb, remaining_b - mb, mw, remaining_w - mw);
        }
    }

    cache_v = ans;
    return ans;
}

long count_mixed_color1(int max_b, int remaining_b, int min_w, int remaining_w, int stage, bool has_decreased, bool has_increased, std::string path = "") {
    if (remaining_b == 0 && remaining_w == 0) {
        if (has_decreased && has_increased) {
            fprintf(stderr, "%s\n", path.c_str());
        }
        return has_decreased && has_increased;
    } else if (min_w > remaining_w) {
        return 0;
    }

    long& cache_v = mixed_color_cache[max_b][remaining_b][min_w][remaining_w][stage][has_decreased][has_increased];
    if (cache_v != -1) {
        return cache_v;
    }

    long ans = 0;
    for (int mb = 1; mb <= std::min(max_b, remaining_b); ++mb) {
        for (int mw = min_w; mw <= remaining_w; ++mw) {
            ans += count_mixed_color1(
                mb, remaining_b - mb, mw, remaining_w - mw, 2,
                has_decreased || (stage == 2 && mb < max_b),
                has_increased || (stage == 2 && mw > min_w),
                path + " " + std::string(mb, 'B') + std::string(mw, 'W')
            );
        }
    }

    cache_v = ans;
    return ans;
}

long count_mixed_color(int remaining_b, int remaining_w) {
    // should be getting: 2998

    long ans = 0;

    // count the number of ways using non-decreasing black + white
    ans += count_mixed_color0(1, remaining_b, 1, remaining_w);

    // count the number of ways using decreasing black + increasing white
    ans += count_mixed_color1(remaining_b, remaining_b, 1, remaining_w, 1, false, false);

    return ans;
}


int main() {
    start_time();

    for (int a = 0; a <= num_black; ++a) {
        for (int b = 0; b <= num_black; ++b) {
            single_color_cache[a][b] = -1;
        }
    }

    for (int a = 0; a <= num_black; ++a) {
        for (int b = 0; b <= num_black; ++b) {
            for (int c = 0; c <= num_black; ++c) {
                for (int d = 0; d <= num_black; ++d) {
                    for (int e = 0; e <= 2; ++e) {
                        mixed_color_cache[a][b][c][d][e][0][0] = -1;
                        mixed_color_cache[a][b][c][d][e][0][1] = -1;
                        mixed_color_cache[a][b][c][d][e][1][0] = -1;
                        mixed_color_cache[a][b][c][d][e][1][1] = -1;
                    }
                }
            }
        }
    }

    long ans = 0;
    for (int solo_b = 0; solo_b <= num_black; ++solo_b) {
        for (int solo_w = 0; solo_w <= num_white; ++solo_w) {
            long ways = 1;
            ways *= count_single_color(1, solo_b);
            ways *= count_single_color(1, solo_w);
            ways *= count_mixed_color(num_black - solo_b, num_white - solo_w);
            ans += ways;
        }
    }

    printf("Solution: %li\n", ans);
    end_time();
}
