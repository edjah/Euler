#include "lib/utility.hh"

const std::vector<std::pair<std::string, int>> numerals = {
    {"M", 1000}, {"CM", 900},
    {"D", 500}, {"CD", 400},
    {"C", 100}, {"XC", 90},
    {"L", 50}, {"XL", 40},
    {"X", 10}, {"IX", 9},
    {"V", 5}, {"IV", 4},
    {"I", 1}
};

int parse_roman_numeral(const std::string& s) {
    size_t pos = 0;
    int total = 0;

    for (const auto& [numeral, value] : numerals) {
        while (starts_with(s, numeral, pos)) {
            total += value;
            pos += numeral.size();
        }
    }
    return total;
}

std::string minimal_roman_numeral(int n) {
    std::string result = "";
    for (const auto& [numeral, value] : numerals) {
        while (n >= value) {
            n -= value;
            result += numeral;
        }
    }
    return result;
}

int main(void) {
    start_time();

    const char* filename = "files/p089_roman.txt";
    std::ifstream ifs(filename);
    if (!ifs.good()) {
        fprintf(stderr, "Unable to open %s\n", filename);
        return 1;
    }

    int saved_chars = 0;
    std::string line;
    while (ifs >> line) {
        int number = parse_roman_numeral(line);
        saved_chars += line.size() - minimal_roman_numeral(number).size();
    }
    printf("Solution: %d\n", saved_chars);

    end_time();
}
