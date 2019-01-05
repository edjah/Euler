#include "lib/utility.hh"

int main(void) {
    start_time();

    const char* filename = "files/p099_base_exp.txt";
    std::ifstream ifs(filename);
    if (!ifs.good()) {
        fprintf(stderr, "unable to open %s\n", filename);
        return 1;
    }

    int best_lineno = 0;
    double best_value = 0;

    int lineno = 0;
    std::string line;
    while (ifs >> line) {
        std::vector<std::string> tokens = split(line, ",");
        assert(tokens.size() == 2);
        int base = std::stoi(tokens[0]);
        int exp = std::stoi(tokens[1]);

        double value = exp * log(base);
        if (value > best_value) {
            best_value = value;
            best_lineno = lineno;
        }
        lineno += 1;
    }

    printf("Solution: %d\n", 1 + best_lineno);

    end_time();
}

