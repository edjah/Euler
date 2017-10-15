#include <stdio.h>
#include <time.h>
#include <string.h>


int count, n, str_size;

long bin_to_num(char *s) {
    int n = strlen(s);
    long acc = 0;
    long mult = 1;
    for (int i = n - 1; i >= 0; i--) {
        acc += mult * (s[i] - 48);
        mult *= 2;
    }
    return acc;

}

long S(int n, int r, char str[str_size + 1]) {
    if (r == 0) {
        char tmp[str_size + n];
        for (int i = 0; i < str_size; i++) {
            tmp[i] = str[i];
        }
        for (int i = 0; i < n - 1; i++) {
            tmp[str_size + i] = str[i];
        }
        for (int i = 0; i < str_size; i++) {
            char lol[n + 1];
            for (int j = 0; j < n; j++) {
                lol[j] = str[i + j];
            }
            lol[n] = '\0';
            char last = tmp[i + n - 1];
            tmp[i + n - 1] = '\0';
            if (strstr(tmp, lol)) {
                return 0;
            }
            tmp[i + n - 1] = last;
        }
        count += 1;
        return bin_to_num(str);
    }

    char tmp[n + 1];
    strncpy(tmp, str, n);
    tmp[n] = '\0';
    char last = str[str_size - r - 1];
    str[str_size - r - 1] = '\0';

    printf("%s vs %s\n", tmp, str);
    if (strstr(str, tmp)) {
        str[str_size - r - 1] = last;
        return 0;
    }
    str[str_size - r - 1] = last;

    char a[str_size + 1];
    char b[str_size + 1];
    strncpy(str, a, str_size - r);
    strncpy(str, b, str_size - r);
    a[str_size - r] = '0';
    a[str_size - r + 1] = '\0';
    b[str_size - r] = '1';
    b[str_size - r + 1] = '\0';
    long tot = 0;
    tot += S(n, r - 1, a);
    tot += S(n, r - 1, b);
    return tot;
}

int main(int argc, char *argv[]) {
    clock_t start = clock();

    count = 0, n = 5, str_size = 1 << n;
    char s[str_size + 1];

    for (int i = 0; i < n; i++) {
        s[i] = '0';
    }
    s[n] = '\0';
    long sol = S(n, str_size - n, s);
    printf("Solution: %lu\n", sol);
    printf("Count: %i\n", count);

    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds to run\n", time);
}
