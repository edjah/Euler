#include "lib/utility.h"

int main(void) {
    start_time();

    // file has the preprocessed using sublime
    FILE* fp = fopen("files/p042_words.txt", "r");
    if (!fp) {
        fprintf(stderr, "Cannot open: files/p042_words.txt\n");
        return 1;
    }

    char buffer[100];
    int count = 0;
    while (fscanf(fp, "%s", buffer) != -1) {
        int tot = 0;
        for (int i = 0, n = strlen(buffer); i < n; i++) {
            tot += buffer[i] - 'A' + 1;
        }

        int k = (sqrt(8*tot + 1) - 1) / 2;
        if (k * (k + 1) == 2 * tot) {
            count += 1;
        }
    }

    fclose(fp);
    printf("Solution: %d\n", count);


    end_time();
}
