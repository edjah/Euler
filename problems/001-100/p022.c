#include "lib/utility.h"

int main(void) {
    start_time();

    FILE* fp = fopen("files/p022_names.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open: files/p022_names.txt\n");
        return 1;
    }

    // names file has been pre-processed using sublime
    int tot = 0;
    char buffer[255];
    for (int i = 1; fscanf(fp, "%s", buffer) != EOF; i++) {
        int score = 0;
        for (int j = 0, n = strlen(buffer); j < n; j++) {
            score += buffer[j] - 'A' + 1;
        }
        tot += score * i;
    }
    printf("Solution: %d\n", tot);


    end_time();
}
