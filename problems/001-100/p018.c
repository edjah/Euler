#include "lib/utility.h"

// this is here because p067.c inherits p018.c
#ifndef DATA_FILE
#define DATA_FILE "files/p018_triangle.txt"
#define LIMIT 15
#endif

int arr[LIMIT][LIMIT];
int cache[LIMIT][LIMIT];

int max_path_sum(int r, int c) {
    if (cache[r][c] != 0) {
        return cache[r][c];
    } else if (r == LIMIT - 1) {
        return arr[r][c];
    } else {
        int left = max_path_sum(r + 1, c);
        int right = max_path_sum(r + 1, c + 1);
        cache[r][c] = arr[r][c] + MAX(left, right);
        return cache[r][c];
    }
}

int main(void) {
    start_time();

    FILE* fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open: " DATA_FILE "\n");
        return 1;
    }
    for (int i = 0; i < LIMIT; i++) {
        for (int j = 0; j <= i; j++) {
            int x;
            if (fscanf(fp, "%d", &x) != 1) {
                fprintf(stderr, "Ran out of stuff to read\n");
                return 1;
            }
            arr[i][j] = x;
        }
    }
    fclose(fp);

    printf("Solution: %d\n", max_path_sum(0, 0));
    end_time();
}
