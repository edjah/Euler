#include "lib/utility.h"

char* word_map[91] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven",
    "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen",
    "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty"
};
unsigned long extensions_nums[7] = {
    100, 1000, 1000000, 1000000000, 1000000000000UL,
    1000000000000000UL, 1000000000000000000UL
};
char* extensions_words[7] = {
    "hundred", "thousand", "million", "billion", "trillion",
    "quadrillion", "quintillion"
};

void complete_word_map() {
    word_map[30] = "thirty";
    word_map[40] = "forty";
    word_map[50] = "fifty";
    word_map[60] = "sixty";
    word_map[70] = "seventy";
    word_map[80] = "eighty";
    word_map[90] = "ninety";
}

char* num_to_word(unsigned long n) {
    char* buffer = calloc(300, sizeof(char));

    if (n <= 20) {
        strcat(buffer, word_map[n]);
    } else if (n < 100) {
        strcat(buffer, word_map[n - (n % 10)]);
        if (n % 10 > 0) {
            strcat(buffer, "-");
            strcat(buffer, word_map[n % 10]);
        }
    } else {
        for (int i = 0; i < 7; i++) {
            unsigned long k = extensions_nums[i];
            if (n >= k && (i == 6 || (i < 6 && n < extensions_nums[i + 1]))) {
                char* prefix = num_to_word(n / k);
                strcat(buffer, prefix);
                strcat(buffer, " ");
                strcat(buffer, extensions_words[i]);
                free(prefix);

                if (n % k > 0) {
                    if (i == 0) {
                        strcat(buffer, " and ");
                    } else {
                        strcat(buffer, ", ");
                    }
                    char* suffix = num_to_word(n % k);
                    strcat(buffer, suffix);
                    free(suffix);
                }
            }
        }
    }

    buffer = realloc(buffer, sizeof(char) * (strlen(buffer) + 1));
    return buffer;
}

int main(void) {
    start_time();

    complete_word_map();
    int letter_count = 0;
    for (int n = 1; n <= 1000; n++) {
        char* s = num_to_word(n);
        for (int i = 0, k = strlen(s); i < k; i++) {
            if (s[i] != ' ' && s[i] != '-' && s[i] != ',') {
                letter_count += 1;
            }
        }
        free(s);
    }
    printf("Solution: %d\n", letter_count);

    end_time();
}
