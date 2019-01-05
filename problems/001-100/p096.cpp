#include "lib/utility.hh"

using sudoku_grid = std::array<std::array<int, 9>, 9>;


std::vector<int> available_set(const sudoku_grid& grid, int x, int y) {
    int used[10] = {};

    // in the 3x3 square
    for (int i = round_down(x, 3); i < round_down(x, 3) + 3; ++i) {
        for (int j = round_down(y, 3); j < round_down(y, 3) + 3; ++j) {
            used[grid[i][j]] = 1;
        }
    }

    // in the the row and column
    for (int i = 0; i < 9; ++i) {
        used[grid[x][i]] = 1;
        used[grid[i][y]] = 1;
    }

    // computing the available set
    std::vector<int> available;
    for (int i = 1; i < 10; ++i) {
        if (!used[i]) {
            available.push_back(i);
        }
    }

    return available;
}

bool backtrack(sudoku_grid& grid, const std::vector<int>& free, size_t pos) {
    if (pos == free.size()) {
        return true;
    }

    int x = free[pos] / 9;
    int y = free[pos] % 9;

    for (int i : available_set(grid, x, y)) {
        grid[x][y] = i;
        if (backtrack(grid, free, pos + 1)) {
            return true;
        }
        grid[x][y] = 0;
    }

    return false;
}

int solve(sudoku_grid& grid) {
    std::vector<int> free;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (grid[i][j] == 0) {
                free.push_back(9 * i + j);
            }
        }
    }

    if (!backtrack(grid, free, 0)) {
        fprintf(stderr, "Unsolvable grid!\n");
        return 0;
    }
    return 100 * grid[0][0] + 10 * grid[0][1] + grid[0][2];
}

int main(void) {
    start_time();

    const char* filename = "files/p096_sudoku.txt";
    std::ifstream ifs(filename);
    if (!ifs.good()) {
        fprintf(stderr, "unable to open %s\n", filename);
        return 1;
    }

    sudoku_grid grid;
    int total = 0;
    int lineno = 0;
    std::string line;
    while (std::getline(ifs, line)) {
        if (lineno % 10 == 0) {
            if (lineno != 0) {
                total += solve(grid);
            }
            lineno++;
            continue;
        }
        for (int i = 0; i < 9; ++i) {
            grid[(lineno % 10) - 1][i] = line[i] - '0';
        }
        lineno++;
    }
    total += solve(grid);
    printf("Solution: %d\n", total);

    end_time();
}

