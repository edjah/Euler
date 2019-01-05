#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <gmp.h>


class Bignum {
    public:
        Bignum() {
            mpz_init(value);
        }

        Bignum& operator=(const Bignum& other) {
            if (this != &other) {
                mpz_init_set(value, other.value);
            }
            return *this;
        }

        Bignum& operator=(Bignum&& other) {
            if (this != &other) {
                // swap without initializing value for efficiency
                std::swap(value, other.value);

                // we need to avoid calling mpz_clear in the destructor of
                // other, so we use this gross hack to indicate that the
                // value is invalid instead of adding another field in the class
                other.value->_mp_size = INT_MAX;
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
            if (value->_mp_size != INT_MAX) {
                mpz_clear(value);
            }
        }

        Bignum(const int n);
        Bignum(const long n);
        Bignum(const double d);
        Bignum(const char* s, int base = 0);
        Bignum(const std::string& s, int base = 0);


        long to_long() const;
        std::string to_string(int base = 10) const;

        static bool compare(const Bignum& a, const Bignum& b);
        int cmp(const Bignum& other) const;
        int cmp(const int other) const;
        int cmp(const long other) const;
        int cmp(const double other) const;

        template<typename numeric_type>
        bool operator<(const numeric_type& other) const;

        template<typename numeric_type>
        bool operator<=(const numeric_type& other) const;

        template<typename numeric_type>
        bool operator>(const numeric_type& other) const;

        template<typename numeric_type>
        bool operator>=(const numeric_type& other) const;

        template<typename numeric_type>
        bool operator==(const numeric_type& other) const;

        template<typename numeric_type>
        bool operator!=(const numeric_type& other) const;

        Bignum abs() const;
        Bignum negate() const;

        Bignum operator+(const Bignum& other) const;
        Bignum operator+(const long other) const;
        Bignum& operator+=(const Bignum& other);
        Bignum& operator+=(const long other);

        Bignum operator-(const Bignum& other) const;
        Bignum operator-(const long other) const;
        Bignum& operator-=(const Bignum& other);
        Bignum& operator-=(const long other);

        Bignum operator*(const Bignum& other) const;
        Bignum operator*(const long other) const;
        Bignum& operator*=(const Bignum& other);
        Bignum& operator*=(const long other);

        Bignum operator/(const Bignum& other) const;
        Bignum operator/(const long other) const;
        Bignum& operator/=(const Bignum& other);
        Bignum& operator/=(const long other);

        Bignum operator%(const Bignum& other) const;
        Bignum operator%(const long other) const;
        Bignum& operator%=(const Bignum& other);
        Bignum& operator%=(const long other);

        Bignum pow(const Bignum& exp, const Bignum& mod) const;
        Bignum pow(const unsigned long exp, const Bignum& mod) const;
        Bignum pow(const unsigned long exp) const;

        bool is_prime(int reps = 32) const;
        size_t hash() const;

        static const Bignum ZERO;
        static const Bignum ONE;

        friend class Fraction;
        friend class Decimal;

        friend std::ostream& operator<<(std::ostream& os, const Bignum& b);

    private:
        mpz_t value;
};


/**************************************
 * Constructors and Memory Management *
 **************************************/
Bignum::Bignum(int n) {
    mpz_init_set_si(value, n);
}

Bignum::Bignum(long n) {
    mpz_init_set_si(value, n);
}

Bignum::Bignum(double d) {
    mpz_init_set_d(value, d);
}

Bignum::Bignum(const char* s, int base) {
    mpz_init_set_str(value, s, base);
}

Bignum::Bignum(const std::string& s, int base) {
    mpz_init_set_str(value, s.c_str(), base);
}


/************************
 * Conversion Functions *
 ***********************/
long Bignum::to_long() const {
    return mpz_get_si(value);
}

std::string Bignum::to_string(int base) const {
    char* s = mpz_get_str(NULL, base, value);
    std::string result(s);
    free(s);
    return result;
}

/************************
 * Comparison Functions *
 ***********************/
int Bignum::cmp(const Bignum& other) const {
    return mpz_cmp(value, other.value);
}

int Bignum::cmp(int n) const {
    return mpz_cmp_si(value, n);
}

int Bignum::cmp(long n) const {
    return mpz_cmp_si(value, n);
}

int Bignum::cmp(double d) const {
    return mpz_cmp_d(value, d);
}

bool Bignum::compare(const Bignum& a, const Bignum& b) {
    return a.cmp(b) < 0;
}

template<typename numeric_type>
bool Bignum::operator<(const numeric_type& other) const {
    return cmp(other) < 0;
}

template<typename numeric_type>
bool Bignum::operator<=(const numeric_type& other) const {
    return cmp(other) <= 0;
}

template<typename numeric_type>
bool Bignum::operator>(const numeric_type& other) const {
    return cmp(other) > 0;
}

template<typename numeric_type>
bool Bignum::operator>=(const numeric_type& other) const {
    return cmp(other) >= 0;
}

template<typename numeric_type>
bool Bignum::operator==(const numeric_type& other) const {
    return cmp(other) == 0;
}

template<typename numeric_type>
bool Bignum::operator!=(const numeric_type& other) const {
    return cmp(other) != 0;
}

/******************************
 * Basic Arithmetic Functions *
 ******************************/
Bignum Bignum::abs() const {
    Bignum result;
    mpz_abs(result.value, value);
    return result;
}

Bignum Bignum::negate() const {
    Bignum result;
    mpz_neg(result.value, value);
    return result;
}

Bignum Bignum::operator+(const Bignum& other) const {
    Bignum result(*this);
    result += other;
    return result;
}

Bignum Bignum::operator+(const long other) const {
    Bignum result(*this);
    result += other;
    return result;
}

Bignum& Bignum::operator+=(const Bignum& other) {
    mpz_add(value, value, other.value);
    return *this;
}

Bignum& Bignum::operator+=(const long other) {
    if (other >= 0) {
        mpz_add_ui(value, value, other);
    } else {
        mpz_sub_ui(value, value, -other);
    }
    return *this;
}


Bignum Bignum::operator-(const Bignum& other) const {
    Bignum result(*this);
    result -= other;
    return result;
}

Bignum Bignum::operator-(const long other) const {
    Bignum result(*this);
    result -= other;
    return result;
}

Bignum& Bignum::operator-=(const Bignum& other) {
    mpz_sub(value, value, other.value);
    return *this;
}

Bignum& Bignum::operator-=(const long other) {
    if (other >= 0) {
        mpz_sub_ui(value, value, other);
    } else {
        mpz_add_ui(value, value, -other);
    }
    return *this;
}

/*******************************
 * Multiplication and Division *
 ******************************/
Bignum Bignum::operator*(const Bignum& other) const {
    Bignum result(*this);
    result *= other;
    return result;
}

Bignum Bignum::operator*(const long other) const {
    Bignum result(*this);
    result *= other;
    return result;
}

Bignum& Bignum::operator*=(const Bignum& other) {
    mpz_mul(value, value, other.value);
    return *this;
}

Bignum& Bignum::operator*=(const long other) {
    mpz_mul_si(value, value, other);
    return *this;
}


Bignum Bignum::operator/(const Bignum& other) const {
    Bignum result(*this);
    result /= other;
    return result;
}

Bignum Bignum::operator/(const long other) const {
    Bignum result(*this);
    result /= other;
    return result;
}

Bignum& Bignum::operator/=(const Bignum& other) {
    mpz_fdiv_q(value, value, other.value);
    return *this;
}

Bignum& Bignum::operator/=(const long other) {
    long other_abs = other < 0 ? -other : other;
    mpz_fdiv_q_ui(value, value, other_abs);
    if (other < 0) {
        mpz_neg(value, value);
    }
    return *this;
}


Bignum Bignum::operator%(const Bignum& other) const {
    Bignum result(*this);
    result %= other;
    return result;
}

Bignum Bignum::operator%(const long other) const {
    Bignum result(*this);
    result %= other;
    return result;
}

Bignum& Bignum::operator%=(const Bignum& other) {
    mpz_fdiv_r(value, value, other.value);
    return *this;
}

Bignum& Bignum::operator%=(const long other) {
    long other_abs = other < 0 ? -other : other;
    mpz_fdiv_r_ui(value, value, other_abs);
    if (other < 0) {
        mpz_neg(value, value);
    }
    return *this;
}

/******************
 * Exponentiation *
 ******************/
Bignum Bignum::pow(const Bignum& exp, const Bignum& mod) const {
    if (exp < 0) {
        throw std::invalid_argument("Negative exponent in Bignum::pow()");
    }
    Bignum result;
    mpz_powm(result.value, value, exp.value, mod.value);
    return result;
}

Bignum Bignum::pow(const unsigned long exp, const Bignum& mod) const {
    Bignum result;
    mpz_powm_ui(result.value, value, exp, mod.value);
    return result;
}

Bignum Bignum::pow(const unsigned long exp) const {
    Bignum result;
    mpz_pow_ui(result.value, value, exp);
    return result;
}

/***************************
 * Miscellaneous Functions *
 ***************************/
bool Bignum::is_prime(int reps) const {
    return mpz_probab_prime_p(value, reps) >= 1;
}

/********************
 * Useful constants *
 ********************/
const Bignum Bignum::ZERO = Bignum(0);
const Bignum Bignum::ONE = Bignum(1);


/******************
 * Hash functions *
 ******************/
size_t Bignum::hash() const {
    static_assert(sizeof(mp_limb_t) == 8);

    const mp_limb_t* limbs = mpz_limbs_read(value);
    size_t hash = 0;
    for (size_t i = 0, n = mpz_size(value); i < n; ++i) {
        hash = 61 * hash + limbs[i];
    }
    return hash;
}

namespace std {
    template <>
    struct hash<Bignum> {
        size_t operator()(const Bignum& b) const {
            return b.hash();
        }
    };
}


std::ostream& operator<<(std::ostream& os, const Bignum& b) {
    os << "Bignum(" << b.to_string() << ")";
    return os;
}
