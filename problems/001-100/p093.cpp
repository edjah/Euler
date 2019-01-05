#include "lib/utility.hh"
#include "lib/expr_eval.hh"

constexpr std::array<char, 4> ops = {'+', '-', '/', '*'};

constexpr int max_parens = 2;

void make_templates_rec(std::vector<std::string>& templates,
                        std::string s, std::unordered_set<char>& vars,
                        int parens) {
    if (vars.empty()) {
        assert(s.size() >= 4);
        for (int i = 0; i < parens; ++i) {
            s += ')';
        }
        templates.push_back(s);
        return;
    }

    if (parens > 0 && !is_op(s.back()) && s.back() != '(') {
        make_templates_rec(templates, s + ')', vars, parens - 1);
    }

    if (s.empty() || is_op(s.back()) || s.back() == '(') {
        // need to put a value
        if (parens < max_parens) {
            make_templates_rec(templates, s + '(', vars, parens + 1);
        }
        auto copy = vars;
        for (char v : copy) {
            vars.erase(v);
            make_templates_rec(templates, s + v, vars, parens);
            vars.insert(v);
        }

    } else {
        // need to put an operation
        for (char op : ops) {
            make_templates_rec(templates, s + op, vars, parens);
        }
    }
}

std::string remove_extra_parens(std::string s) {
    // replacing un-needed parens with a '.'
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '(' && s[i + 2] == ')') {
            s[i] = s[i + 2] = '.';
        }

        if (s[i] == '(' && s[i + 1] == '(') {
            for (size_t j = i + 2; j < s.size(); ++j) {
                if (s[j] == ')') {
                    if (s[j + 1] == ')') {
                        s[i] = s[j] = '.';
                    }
                    break;
                }
            }
        }
    }

    // constructing the new string without the '.'s
    std::string result;
    for (char c : s) {
        if (c != '.') {
            result += c;
        }
    }
    return result;
}

std::vector<std::string> make_templates() {
    std::vector<std::string> templates;
    std::unordered_set<char> vars = {'a', 'b', 'c', 'd'};
    make_templates_rec(templates, "", vars, false);

    // getting rid of excess parentheses
    std::unordered_set<std::string> uniq_templs;
    for (std::string s : templates) {
        while (1) {
            std::string cleaned = remove_extra_parens(s);
            if (s == cleaned) {
                break;
            }
            s = cleaned;
        }
        uniq_templs.insert(s);
    }

    return std::vector<std::string>(uniq_templs.begin(), uniq_templs.end());
}



int main(void) {
    start_time();

    std::vector<std::string> templates = make_templates();

    int max_len = 0;
    std::string best = "";

    for (int a = 1; a < 10; ++a) {
        for (int b = a + 1; b < 10; ++b) {
            for (int c = b + 1; c < 10; ++c) {
                for (int d = c + 1; d < 10; ++d) {
                    std::unordered_set<int> results;
                    for (std::string tmpl : templates) {
                        for (char& ch : tmpl) {
                            if (ch == 'a') {
                                ch = '0' + a;
                            } else if (ch == 'b') {
                                ch = '0' + b;
                            } else if (ch == 'c') {
                                ch = '0' + c;
                            } else if (ch == 'd') {
                                ch = '0' + d;
                            }
                        }
                        double res = eval(tmpl);
                        if (res == int(res)) {
                            results.insert(int(res));
                        }
                    }

                    int i = 1;
                    while (results.count(i)) {
                        i += 1;
                    }
                    i -= 1;
                    if (i > max_len) {
                        max_len = i;
                        best = std::to_string(a) + std::to_string(b) + \
                               std::to_string(c) + std::to_string(d);
                    }
                }
            }
        }
    }

    printf("Solution: %s | %d\n", +best, max_len);

    end_time();
}

