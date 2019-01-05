#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <string>


#define BASE 1000000000
#define CHARS_PER_DIGIT 9
#define KARATSUBA_CUTOFF 35


class Bignum {
    public:
        Bignum() {
            // initializes the bignum to 0 with calloc
            sign = 1;
            size = 1;
            max_size = 2;
            digits = (int*) calloc(max_size, sizeof(int));
        }

        Bignum& operator=(const Bignum& other) {
            if (this != &other) {
                free(digits);
                size = other.size;
                sign = other.sign;
                max_size = other.max_size;
                digits = (int*) malloc(sizeof(int) * other.max_size);
                memcpy(digits, other.digits, sizeof(int) * other.max_size);
            }
            return *this;
        }

        Bignum& operator=(Bignum&& other) {
            if (this != &other) {
                free(digits);
                sign = other.sign;
                size = other.size;
                max_size = other.max_size;
                digits = other.digits;
                other.digits = nullptr;
            }
            return *this;
        }

        Bignum(Bignum&& other) {
            *this = std::move(other);
        }

        Bignum(const Bignum& other) {
            *this = other;
        }

        ~Bignum() {
            free(digits);
        }

        Bignum(const long n);
        Bignum(const int n);
        Bignum(const char* s);
        Bignum(const std::string& s);

        long to_long() const;
        std::string to_string() const;

        static bool compare(const Bignum& a, const Bignum& b);
        bool operator<(const Bignum& other) const;
        bool operator<=(const Bignum& other) const;
        bool operator>(const Bignum& other) const;
        bool operator>=(const Bignum& other) const;
        bool operator==(const Bignum& other) const;
        bool operator!=(const Bignum& other) const;

        std::pair<Bignum, Bignum> karatsuba_split(unsigned m) const;
        Bignum karatsuba_mult(const Bignum& a, const Bignum& b);
        Bignum& basic_mult(const Bignum& other);

        Bignum operator+(const Bignum& other) const;
        Bignum& operator+=(const Bignum& other);
        Bignum operator-(const Bignum& other) const;
        Bignum& operator-=(const Bignum& other);
        Bignum operator*(const Bignum& other) const;
        Bignum& operator*=(const Bignum& other);
        Bignum operator/(const Bignum& other) const;
        Bignum& operator/=(const Bignum& other);
        Bignum operator%(const Bignum& other) const;
        Bignum& operator%=(const Bignum& other);

        Bignum operator<<(unsigned x) const;
        Bignum& operator<<=(unsigned x);
        Bignum operator>>(unsigned x) const;
        Bignum& operator>>=(unsigned x);


        Bignum exp(Bignum& exp) const;
        Bignum mod_exp(const Bignum& exp, const Bignum& mod) const;


        // TOOD: add more operators here

    private:
        Bignum& cleanup();
        void resize(int new_max_size);
        static int compare_int(const Bignum& a, const Bignum& b);

        int* digits = nullptr;
        int sign;
        int size;
        int max_size;
};


/**************************************
 * Constructors and Memory Management *
 **************************************/
Bignum& Bignum::cleanup() {
    if (size == 0) {
        digits[0] = 0;
        size = 1;
    }
    while (size > 1 && digits[size - 1] == 0) {
        size -= 1;
    }
    if (size == 1 && digits[0] == 0) {
        sign = 1;
    }
    return *this;
}

void Bignum::resize(int new_max_size) {
    if (new_max_size <= 0) {
        *this = Bignum(0);
        return;
    }
    size_t alloc_size = new_max_size * sizeof(int);
    int* new_digits = (int*) realloc(digits, alloc_size);
    if (new_digits == nullptr) {
        throw std::runtime_error("Unable to resize bignum");
    }

    digits = new_digits;
    for (int i = max_size; i < new_max_size; ++i) {
        digits[i] = 0;
    }
    max_size = new_max_size;
    size = std::min(size, max_size);
}

Bignum::Bignum(long n) : Bignum() {
    sign = n < 0 ? -1 : 1;
    n *= sign;

    if (n > 0) {
        size = 0;
        while (n > 0) {
            assert(size < 2);
            digits[size++] = n % BASE;
            n /= BASE;
        }
    }
}

Bignum::Bignum(int n) : Bignum((long) n) {}

Bignum::Bignum(const char* s) : Bignum() {
    // skipping past leading whitespace
    int i = 0;
    while (isspace(s[i])) {
        i += 1;
    }

    // detecting sign
    if (s[i] == '-' || s[i] == '+') {
        sign = s[i] == '-' ? -1 : 1;
        i += 1;
    }

    // detecting when the digits end and/or catching a parse error
    int start = -1;
    bool seen_digits = false;
    while (s[i] != '\0') {
        if (s[i] >= '0' && s[i] <= '9') {
            // skipping leading zeros
            if (s[i] != '0') {
                seen_digits = true;
                if (start == -1) {
                    start = i;
                }
            }
        } else if (seen_digits) {
            break;
        } else  {
            throw std::invalid_argument("Parse error");
        }
        i += 1;
    }

    if (start == -1) {
        throw std::invalid_argument("Parse error");
    }

    // parsing the digits
    int end = i - 1;
    int tmp = 0;
    int mult = 1;
    int nchars = 0;

    size = 0;
    resize(1 + (end - start) / CHARS_PER_DIGIT);

    while (end >= start) {
        assert(size <= max_size);
        tmp = tmp + (s[end] - '0') * mult;
        nchars++;
        mult *= 10;
        if (nchars == CHARS_PER_DIGIT) {
            digits[size++] = tmp;
            tmp = 0;
            mult = 1;
            nchars = 0;
        }
        end -= 1;
    }

    if (tmp) {
        digits[size++] = tmp;
    }
}

Bignum::Bignum(const std::string& s) : Bignum(s.c_str()) {}


/************************
 * Conversion Functions *
 ***********************/
long Bignum::to_long() const {
    // this function does not test for overflow, so take care with the results
    long result = 0;
    for (int i = size - 1; i >= 0; i--) {
        result = digits[i] + result * BASE;
    }
    return result * sign;
}

std::string Bignum::to_string() const {
    char* buf = (char*) calloc(CHARS_PER_DIGIT * size + 2, sizeof(char));

    // figuring out sign
    int pos = 0;
    if (sign == -1) {
        buf[0] = '-';
        pos = 1;
    }

    // writing the unsigned digits to a pre-allocated buffer (in reverse)
    for (int i = 0; i < size; i++) {
        int dig = digits[i];
        int num_written = 0;
        do {
            buf[pos++] = '0' + (dig % 10);
            dig /= 10;
            num_written += 1;
        } while (dig > 0);

        if (i < size - 1) {
            for (int k = num_written; k < CHARS_PER_DIGIT; k++) {
                buf[pos++] = '0';
            }
        }
    }

    // reversing the buffer
    int init = (sign == -1) ? 1 : 0;
    for (int i = init; i < (pos + init) / 2; i++) {
        char tmp = buf[i];
        buf[i] = buf[pos - i - 1 + init];
        buf[pos - i - 1 + init] = tmp;
    }

    // freeing the buffer and returning a std::string
    buf[pos] = '\0';
    std::string result = std::string(buf);
    free(buf);
    return result;
}

/************************
 * Comparison Functions *
 ***********************/
int Bignum::compare_int(const Bignum& a, const Bignum& b) {
    if (a.sign != b.sign) {
        return a.sign;
    }

    if (a.size > b.size) {
        return a.sign;
    } else if (a.size < b.size) {
        return -a.sign;
    }

    for (int i = a.size - 1; i >= 0; --i) {
        if (a.digits[i] > b.digits[i]) {
            return a.sign;
        } else if (a.digits[i] < b.digits[i]) {
            return -a.sign;
        }
    }
    return 0;
}

bool Bignum::compare(const Bignum& a, const Bignum& b) {
    return compare_int(a, b) < 0;
}

bool Bignum::operator<(const Bignum& other) const {
    return compare_int(*this, other) < 0;
}

bool Bignum::operator<=(const Bignum& other) const {
    return compare_int(*this, other) <= 0;
}

bool Bignum::operator>(const Bignum& other) const {
    return compare_int(*this, other) > 0;
}

bool Bignum::operator>=(const Bignum& other) const {
    return compare_int(*this, other) >= 0;
}

bool Bignum::operator==(const Bignum& other) const {
    return compare_int(*this, other) == 0;
}

bool Bignum::operator!=(const Bignum& other) const {
    return compare_int(*this, other) != 0;
}


/********************
 * Basic Arithmetic *
 *******************/
Bignum Bignum::operator+(const Bignum& other) const {
    Bignum result(*this);
    result += other;
    return result;
}

Bignum& Bignum::operator+=(const Bignum& other) {
    if (sign != other.sign) {
        sign *= -1;
        *this -= other;
        sign *= -1;
        return this->cleanup();
    }

    resize(1 + std::max(size, other.size));
    size = max_size;

    int carry = 0;
    int i = 0;
    while (i < other.size) {
        int n = digits[i] + other.digits[i] + carry;
        digits[i++] = n % BASE;
        carry = n / BASE;
    }

    while (carry > 0) {
        int n = digits[i] + carry;
        digits[i++] = n % BASE;
        carry = n / BASE;
    }

    return this->cleanup();
}

Bignum Bignum::operator-(const Bignum& other) const {
    Bignum result(*this);
    result -= other;
    return result;
}

Bignum& Bignum::operator-=(const Bignum& other) {
    // if the signs don't match, switch one and do an addition
    if (sign != other.sign) {
        sign *= -1;
        *this += other;
        sign *= -1;
        return this->cleanup();
    }

    // allocate enough space for the result
    resize(std::max(size, other.size));
    size = max_size;

    // making sure that `a` has the bigger absolute value
    const Bignum* a = this;
    const Bignum* b = &other;
    if (compare_int(*this, other) == -sign) {
        std::swap(a, b);
        sign *= -1;
    }

    // doing the subtraction
    bool borrow_flag = false;
    for (int i = 0; i < size; i++) {
        int adigit = i < a->size ? a->digits[i] : 0;
        int bdigit = i < b->size ? b->digits[i] : 0;
        if (borrow_flag) {
            adigit -= 1;
        }
        if (adigit >= bdigit) {
            digits[i] = adigit - bdigit;
            borrow_flag = false;
        } else {
            digits[i] = BASE + adigit - bdigit;
            borrow_flag = true;
        }
    }

    return this->cleanup();
}

/******************
 * Multiplication *
 *****************/

Bignum Bignum::operator<<(unsigned x) const {
    Bignum result(*this);
    result <<= x;
    return result;
}

Bignum& Bignum::operator<<=(unsigned x) {
    resize(size + x);
    memmove(digits + x, digits, sizeof(int) * size);
    memset(digits, 0, sizeof(int) * x);
    size += x;
    return *this;
}

Bignum Bignum::operator>>(unsigned x) const {
    Bignum result(*this);
    result >>= x;
    return result;
}

Bignum& Bignum::operator>>=(unsigned x) {
    if ((int) x >= size) {
        size = 1;
        resize(size);
        digits[0] = 0;
    } else {
        memmove(digits, digits + x, sizeof(int) * (size - x));
        size -= x;
        resize(size);
    }
    return *this;
}

Bignum Bignum::operator*(const Bignum& other) const {
    Bignum result(*this);
    result *= other;
    return result;
}


Bignum& Bignum::basic_mult(const Bignum& other) {
    // copying over the original digits into a temporary buffer
    int* orig_digits = (int*) malloc(sizeof(int) * size);
    memcpy(orig_digits, digits, sizeof(int) * size);

    // zeroing out all of the digits before adding onto them
    resize(1 + size + other.size);
    memset(digits, 0, sizeof(int) * max_size);

    // multiplying
    for (int i = 0; i < size; i++) {
        int carry = 0;
        for (int j = 0; j < other.size; j++) {
            long tmp = (long) digits[i + j] + carry;
            tmp += (long) orig_digits[i] * (long) other.digits[j];
            carry = tmp / BASE;
            digits[i + j] = tmp % BASE;
        }
        digits[i + other.size] += carry;
    }

    free(orig_digits);
    size = max_size;
    sign *= other.sign;
    return this->cleanup();
}

std::pair<Bignum, Bignum> Bignum::karatsuba_split(unsigned m) const {
    Bignum low, high;

    low.sign = high.sign = sign;
    low.size = m;
    high.size = size - m;
    low.resize(low.size);
    high.resize(high.size);

    memcpy(low.digits, digits, low.size * sizeof(int));
    memcpy(high.digits, digits + low.size, high.size * sizeof(int));

    return std::make_pair(low, high);
}

Bignum Bignum::karatsuba_mult(const Bignum& a, const Bignum& b) {
    int m2 = std::min(a.size, b.size) / 2;
    auto [low1, high1] = a.karatsuba_split(m2);
    auto [low2, high2] = b.karatsuba_split(m2);
    Bignum z0 = low1 * low2;
    Bignum z1 = (low1 + high1) * (low2 + high2);
    Bignum z2 = high1 * high2;
    return (z2 << (2 * m2)) + ((z1 - z2 - z0) << m2) + z0;
}

Bignum& Bignum::operator*=(const Bignum& other) {
    if (size < KARATSUBA_CUTOFF || other.size < KARATSUBA_CUTOFF) {
        return basic_mult(other);
    }
    *this = karatsuba_mult(*this, other);
    return *this;
}

Bignum Bignum::operator/(const Bignum& other) const {
    Bignum result(*this);
    result /= other;
    return result;
}

Bignum& Bignum::operator/=(const Bignum& other) {
    throw std::runtime_error("TODO: /=");
    return *this;
}

Bignum Bignum::operator%(const Bignum& other) const {
    Bignum result(*this);
    result %= other;
    return result;
}

Bignum& Bignum::operator%=(const Bignum& other) {
    throw std::runtime_error("TODO: %=");
    return *this;
}

Bignum Bignum::exp(Bignum& exp) const {
    throw std::runtime_error("TODO: exp");
    return *this;
}

Bignum Bignum::mod_exp(const Bignum& exp, const Bignum& mod) const {
    throw std::runtime_error("TODO: mod_exp");
    return *this;
}
