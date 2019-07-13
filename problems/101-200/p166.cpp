#include "lib/utility.hh"

using row = std::array<int, 4>;


int count_grids_with_goal(int goal, std::vector<row>& rows) {
    std::array<row, 4> grid;
    int count = 0;

    #define compute_and_check_column_total(grid, total, n) ({       \
        bool flag = true;                                           \
        for (int c = 0; flag && c < 4; ++c) {                       \
            total[c] = 0;                                           \
            for (int r = 0; r < n; ++r) {                           \
                total[c] += grid[r][c];                             \
            }                                                       \
            bool not_too_big = (total[c] <= goal);                  \
            bool not_too_small = (goal - total[c] <= 9 * (4 - n));  \
            flag = flag && not_too_big && not_too_small ;           \
        }                                                           \
        if (!flag) {                                                \
            continue;                                               \
        }                                                           \
    })

    #define check_diag(goal, grid) ({                                   \
        (grid[0][0] + grid[1][1] + grid[2][2] + grid[3][3] == goal) &&  \
        (grid[0][3] + grid[1][2] + grid[2][1] + grid[3][0] == goal);    \
    })

    row total;
    for (size_t a = 0; a < rows.size(); ++a) {
        grid[0] = rows[a];
        compute_and_check_column_total(grid, total, 1);

        for (size_t b = 0; b < rows.size(); ++b) {
            grid[1] = rows[b];
            compute_and_check_column_total(grid, total, 2);

            for (size_t c = 0; c < rows.size(); ++c) {
                grid[2] = rows[c];
                compute_and_check_column_total(grid, total, 3);

                for (int i = 0; i < 4; ++i) {
                    grid[3][i] = goal - total[i];
                }
                count += check_diag(goal, grid);
            }
        }
    }
    return count;
}

int criss_cross_count() {
    std::vector<row> rows_by_sum[37];
    for (int a = 0; a < 10; ++a) {
        for (int b = 0; b < 10; ++b) {
            for (int c = 0; c < 10; ++c) {
                for (int d = 0; d < 10; ++d) {
                    rows_by_sum[a + b + c + d].push_back({a, b, c, d});
                }
            }
        }
    }

    int count = 0;
    for (int goal = 0; goal <= 36; ++goal) {
        count += count_grids_with_goal(goal, rows_by_sum[goal]);
    }
    return count;
}

int main() {
    start_time();
    printf("Solution: %d\n", criss_cross_count());
    end_time();
}
