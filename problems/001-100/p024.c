#include "lib/utility.h"
#define TARGET_PERMUTATION 1000000

int perm_count = 0;

void permute(char res[], int used[], int idx, int n) {
    if (idx == n) {
        perm_count++;
        if (perm_count == TARGET_PERMUTATION) {
            printf("Solution: %s\n", res);
            end_time();
            exit(0);
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            res[idx] = '0' + i;
            used[i] = 1;
            permute(res, used, idx + 1, n);
            used[i] = 0;
        }
    }
}


int main(void) {
    start_time();
    char* result = calloc(11, sizeof(char));
    int* used = calloc(10, sizeof(int));
    permute(result, used, 0, 10);
}
