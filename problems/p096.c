#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int* possible(int **sol, int a, int b) {
    int seen[10] = {};
    int available = 9;
    int x, y;
    for (int i = 0; i < 9; i++) {
        x = sol[a][i];
        y = sol[i][b];
        if (x != 0 && seen[x] == 0)
            available -= 1;
        seen[x] = 1;
        if (y != 0 && seen[y] == 0)
            available -= 1;
        seen[y] = 1;
    }

    int q = 3 * (a / 3), w = 3 * (b / 3);
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            int c = sol[q + j][w + k];
            if (c != 0 && seen[c] == 0)
                available -= 1;
            seen[c] = 1;
        }
    }

    int *candidates = malloc(sizeof(int) * (1 + available));
    candidates[0] = available;
    int idx = 1;
    for (int i = 1; i < 10; i++) {
        if (seen[i] == 0) {
            candidates[idx++] = i;
        }
    }

    return candidates;
}

int** dfs(int *cycles, int idx, int num_blanks, int **blanks, int **sol) {
    *cycles += 1;
    if (idx >= num_blanks) {
        return (int**) sol;
    }
    int a = blanks[idx][0], b = blanks[idx][1];
    int *candidates = possible(sol, a, b);
    for (int i = 1; i <= candidates[0]; i++) {
        sol[a][b] = candidates[i];
        int **x = dfs(cycles, idx + 1, num_blanks, blanks, sol);
        if (x != NULL) {
            free(candidates);
            return x;
        } else {
            sol[a][b] = 0;
        }
    }
    free(candidates);
    return NULL;
}

int** sudoku_solve(int G[9][9]) {
    int num_blanks = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (G[i][j] == 0) {
                num_blanks += 1;
            }
        }
    }

    int **blanks = malloc(sizeof(int*) * num_blanks);
    int idx = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (G[i][j] == 0) {
                blanks[idx] = malloc(sizeof(int) * 2);
                blanks[idx][0] = i;
                blanks[idx][1] = j;
                idx++;
            }
        }
    }

    int cycles = 0;

    int **sol = malloc(sizeof(int*) * 9);
    for (int i = 0; i < 9; i++) {
        sol[i] = malloc(sizeof(int) * 9);
        memcpy(sol[i], G[i], sizeof(int) * 9);
    }


    sol = dfs(&cycles, 0, num_blanks, blanks, sol);
    for (int i = 0; i < num_blanks; i++) {
        free(blanks[i]);
    }
    free(blanks);

    if (sol == NULL) {
        printf("Unable to find a solution.\n");
        return (int**) G;
    } else {
        printf("It took %d cycles\n", cycles);
        return sol;
    }

}

int main(int argc, char *argv[]) {
    clock_t start = clock();

    FILE *fp = fopen("p096_sudoku.txt", "r");
    if (fp == NULL) {
        printf("Error: unable to open file %s\n", "p096_sudoku.txt");
        return 1;
    }
    int grids[50][9][9];
    char buffer[11];
    int r = 0, g = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (buffer[0] == 'G')
            continue;
        for (int i = 0; i < 9; i++) {
            grids[g][r][i] = buffer[i] - 48;
        }
        r = (r + 1) % 9;
        if (r == 0) {
            g += 1;
        }
    }
    fclose(fp);

    int ans = 0;
    for (int i = 0; i < 50; i++) {
        printf("Solving Grid #%d...", i + 1);
        int **g = sudoku_solve(grids[i]);
        ans += g[0][0] * 100 + g[0][1] * 10 + g[0][2];
        for (int i = 0; i < 9; i++) {
            free(g[i]);
        }
        free(g);
    }

    printf("Solution: %d\n", ans);


    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds to run\n", time);
}
