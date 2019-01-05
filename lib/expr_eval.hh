#include <exception>
#include <vector>


enum binop_type {
    add, subtract, multiply, divide
};
enum token_type {
    number, operation, lparen, rparen
};

constexpr bool is_op(char c) {
    return c == '+' || c == '-' || c == '/' || c == '*';
}

bool try_to_consume_digits(const std::string& s, size_t& pos, int& value) {
    size_t old_pos = pos;
    value = 0;
    while (pos < s.size() && s[pos] >= '0' && s[pos] <= '9') {
        value = value * 10 + (s[pos++] - '0');
    }
    return (pos != old_pos);
}

struct token {
    int int_value;
    binop_type binop;
    token_type type;
};

// only evaluates binops for now. no unops
std::vector<token> tokenize(const std::string& s) {
    std::vector<token> tokens;
    size_t pos = 0;

    while (pos < s.size()) {
        // skip past whitespace
        while (s[pos] == ' ') {
            pos++;
        }

        token t;
        if (try_to_consume_digits(s, pos, t.int_value)) {
            t.type = number;
        } else if (is_op(s[pos])) {
            t.type = operation;
            switch (s[pos]) {
                case '*':
                    t.binop = multiply;
                    break;
                case '/':
                    t.binop = divide;
                    break;
                case '-':
                    t.binop = subtract;
                    break;
                case '+':
                    t.binop = add;
                    break;
                default:
                    assert(false);
            }
            pos++;
        } else if (s[pos] == '(') {
            t.type = lparen;
            pos++;
        } else if (s[pos] == ')') {
            t.type = rparen;
            pos++;
        } else {
            throw std::runtime_error("malformed expression: " + s);
        }
        tokens.push_back(t);
    }

    return tokens;
}

double apply_binop(double x, binop_type binop, double y) {
    switch (binop) {
        case add:
            return x + y;
        case subtract:
            return x - y;
        case divide:
            return x / y;
        case multiply:
            return x * y;
        default:
            throw std::runtime_error("invalid binop: " + std::to_string(binop));
    }
}

double eval(const std::vector<token>& tokens) {
    std::vector<token> output_queue;
    std::vector<token> operation_stack;

    for (const token& t : tokens) {
        if (t.type == number) {
            output_queue.push_back(t);
        } else if (t.type == operation) {
            while (!operation_stack.empty() &&
                   operation_stack.back().type != lparen &&
                   operation_stack.back().binop >= multiply) {
                output_queue.push_back(operation_stack.back());
                operation_stack.pop_back();
            }
            operation_stack.push_back(t);
        } else if (t.type == lparen) {
            operation_stack.push_back(t);
        } else if (t.type == rparen) {
            while (!operation_stack.empty()
                   && operation_stack.back().type != lparen) {
                output_queue.push_back(operation_stack.back());
                operation_stack.pop_back();
            }
            if (operation_stack.empty()) {
                throw std::runtime_error("Mismatched parentheses");
            }
            operation_stack.pop_back();
        }
    }

    while (!operation_stack.empty()) {
        if (operation_stack.back().type == lparen) {
            throw std::runtime_error("Mismatched parentheses");
        }
        output_queue.push_back(operation_stack.back());
        operation_stack.pop_back();
    }
    if (output_queue.size() == 0) {
        throw std::runtime_error("Empty expression");
    }

    std::vector<double> value_stack;
    for (token& t : output_queue) {
        assert(t.type == number || t.type == operation);
        if (t.type == number) {
            value_stack.push_back(t.int_value);
        } else {
            assert(value_stack.size() >= 2);
            double b = value_stack.back();
            value_stack.pop_back();
            double a = value_stack.back();
            value_stack.pop_back();
            value_stack.push_back(apply_binop(a, t.binop, b));
        }
    }

    assert(value_stack.size() == 1);
    return value_stack[0];
}

double eval(const std::string& s) {
    return eval(tokenize(s));
}
