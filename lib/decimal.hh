#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <gmp.h>
#include <mpfr.h>

#include "bignum.hh"
#include "fraction.hh"

static constexpr mpfr_rnd_t ROUND_MODE = MPFR_RNDZ;

class Decimal {
    public:
        static unsigned set_precision(unsigned bits) {
            mpfr_set_default_prec(bits);
            return mpfr_get_default_prec();
        }

        static unsigned get_precision() {
            return mpfr_get_default_prec();
        }

        Decimal() {
            mpfr_init_set_si(value, 0, ROUND_MODE);
        }

        Decimal& operator=(const Decimal& other) {
            if (this != &other) {
                mpfr_init_set(value, other.value, ROUND_MODE);
            }
            return *this;
        }

        Decimal& operator=(Decimal&& other) {
            if (this != &other) {
                // swap without initializing value for efficiency
                std::swap(value, other.value);

                // we need to avoid calling mpz_clear in the destructor of
                // other, so we use this gross hack to indicate that the
                // value is invalid instead of adding another field in the class
                other.value->_mpfr_sign = INT_MAX;
            }
            return *this;
        }

        Decimal(Decimal&& other) {
            *this = std::move(other);
        }

        Decimal(const Decimal& other) {
            *this = other;
        }

        ~Decimal() {
            if (value->_mpfr_sign != INT_MAX) {
                mpfr_clear(value);
            }
        }

        Decimal(const int n);
        Decimal(const long n);
        Decimal(const double d);
        Decimal(const char* s, int base = 0);
        Decimal(const std::string& s, int base = 0);
        Decimal(const Bignum& b);
        Decimal(const Fraction &f);


        long to_long() const;
        double to_double() const;
        Bignum to_bignum() const;
        Fraction to_fraction() const;
        std::string to_string(int base = 10) const;

        static bool compare(const Decimal& a, const Decimal& b);
        int cmp(const Decimal& other) const;
        int cmp(const int other) const;
        int cmp(const long other) const;
        int cmp(const double other) const;
        int cmp(const Bignum& other) const;
        int cmp(const Fraction& other) const;

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

        int sign() const;
        Decimal abs() const;
        Decimal negate() const;

        Decimal operator+(const Decimal& other) const;
        Decimal operator+(const double other) const;
        Decimal& operator+=(const Decimal& other);
        Decimal& operator+=(const double other);

        Decimal operator-(const Decimal& other) const;
        Decimal operator-(const double other) const;
        Decimal& operator-=(const Decimal& other);
        Decimal& operator-=(const double other);

        Decimal operator*(const Decimal& other) const;
        Decimal operator*(const double other) const;
        Decimal& operator*=(const Decimal& other);
        Decimal& operator*=(const double other);

        Decimal operator/(const Decimal& other) const;
        Decimal operator/(const double other) const;
        Decimal& operator/=(const Decimal& other);
        Decimal& operator/=(const double other);

        Decimal pow(const Decimal& exp) const;
        Decimal pow(const Bignum& exp) const;
        Decimal pow(const int exp) const;
        Decimal pow(const long exp) const;
        Decimal pow(const double exp) const;

        Decimal square() const;
        Decimal sqrt() const;
        Decimal cbrt() const;
        Decimal round() const;
        Decimal floor() const;
        Decimal ceil() const;
        Decimal log() const;
        Decimal exp() const;

        static const Decimal ZERO;
        static const Decimal ONE;

        friend std::ostream& operator<<(std::ostream& os, const Decimal& d);

    private:
        mpfr_t value;
};


/**************************************
 * Constructors and Memory Management *
 **************************************/
Decimal::Decimal(int n) {
    mpfr_init_set_si(value, n, ROUND_MODE);
}

Decimal::Decimal(long n) {
    mpfr_init_set_si(value, n, ROUND_MODE);
}

Decimal::Decimal(double d) {
    mpfr_init_set_d(value, d, ROUND_MODE);
}

Decimal::Decimal(const char* s, int base) {
    mpfr_init_set_str(value, s, base, ROUND_MODE);
}

Decimal::Decimal(const std::string& s, int base) {
    mpfr_init_set_str(value, s.c_str(), base, ROUND_MODE);
}

Decimal::Decimal(const Bignum& b) {
    mpfr_init_set_z(value, b.value, ROUND_MODE);
}

Decimal::Decimal(const Fraction &f) {
    mpfr_init_set_q(value, f.value, ROUND_MODE);
}

/************************
 * Conversion Functions *
 ***********************/
long Decimal::to_long() const {
    return mpfr_get_si(value, ROUND_MODE);
}

double Decimal::to_double() const {
    return mpfr_get_d(value, ROUND_MODE);
}

Bignum Decimal::to_bignum() const {
    Bignum result;
    mpfr_get_z(result.value, value, ROUND_MODE);
    return result;
}

Fraction Decimal::to_fraction() const {
    Fraction result;
    mpfr_get_q(result.value, value);
    return result;
}


std::string Decimal::to_string(int base) const {
    if (sign() == 0) {
        return std::string("0");
    }

    mpfr_exp_t exp;
    char* s = mpfr_get_str(NULL, &exp, base, 0, value, ROUND_MODE);
    std::string result(s);
    free(s);

    // removing trailing zeros...
    for (size_t i = result.size() - 1; i >= 0; --i) {
        if (result[i] != '0') {
            result = result.substr(0, i + 1);
            break;
        }
    }

    // placing leading 0's and the decimal point appropriately
    int sign_offset = (sign() < 0);
    if (exp >= -3 && exp <= 0) {
        result.insert(sign_offset, -exp + 1, '0');
        result.insert(1 + sign_offset, 1, '.');
    } else if (exp > 0 && exp <= 16) {
        if (result.size() - sign_offset <= (size_t) exp) {
            result.insert(result.size(), exp - result.size() + sign_offset, '0');
        } else {
            result.insert(exp + sign_offset, 1, '.');
        }
    } else {
        result.insert(1 + sign_offset, 1, '.');
        result += "e" + std::to_string(exp - 1);
    }

    return result;
}

/************************
 * Comparison Functions *
 ***********************/
int Decimal::cmp(const Decimal& other) const {
    return mpfr_cmp(value, other.value);
}

int Decimal::cmp(int n) const {
    return mpfr_cmp_si(value, n);
}

int Decimal::cmp(long n) const {
    return mpfr_cmp_si(value, n);
}

int Decimal::cmp(double d) const {
    return mpfr_cmp_d(value, d);
}

int Decimal::cmp(const Bignum& b) const {
    return mpfr_cmp_z(value, b.value);
}

int Decimal::cmp(const Fraction& f) const {
    return mpfr_cmp_q(value, f.value);
}

bool Decimal::compare(const Decimal& a, const Decimal& b) {
    return a.cmp(b) < 0;
}

template<typename numeric_type>
bool Decimal::operator<(const numeric_type& other) const {
    return cmp(other) < 0;
}

template<typename numeric_type>
bool Decimal::operator<=(const numeric_type& other) const {
    return cmp(other) <= 0;
}

template<typename numeric_type>
bool Decimal::operator>(const numeric_type& other) const {
    return cmp(other) > 0;
}

template<typename numeric_type>
bool Decimal::operator>=(const numeric_type& other) const {
    return cmp(other) >= 0;
}

template<typename numeric_type>
bool Decimal::operator==(const numeric_type& other) const {
    return cmp(other) == 0;
}

template<typename numeric_type>
bool Decimal::operator!=(const numeric_type& other) const {
    return cmp(other) != 0;
}

/******************************
 * Basic Arithmetic Functions *
 ******************************/
int Decimal::sign() const {
    return mpfr_sgn(value);
}

Decimal Decimal::abs() const {
    Decimal result;
    mpfr_abs(result.value, value, ROUND_MODE);
    return result;
}

Decimal Decimal::negate() const {
    Decimal result;
    mpfr_neg(result.value, value, ROUND_MODE);
    return result;
}

Decimal Decimal::operator+(const Decimal& other) const {
    Decimal result(*this);
    result += other;
    return result;
}

Decimal Decimal::operator+(const double other) const {
    Decimal result(*this);
    result += other;
    return result;
}

Decimal& Decimal::operator+=(const Decimal& other) {
    mpfr_add(value, value, other.value, ROUND_MODE);
    return *this;
}

Decimal& Decimal::operator+=(const double other) {
    mpfr_add_d(value, value, other, ROUND_MODE);
    return *this;
}

Decimal Decimal::operator-(const Decimal& other) const {
    Decimal result(*this);
    result -= other;
    return result;
}

Decimal Decimal::operator-(const double other) const {
    Decimal result(*this);
    result -= other;
    return result;
}

Decimal& Decimal::operator-=(const Decimal& other) {
    mpfr_sub(value, value, other.value, ROUND_MODE);
    return *this;
}

Decimal& Decimal::operator-=(const double other) {
    mpfr_sub_d(value, value, other, ROUND_MODE);
    return *this;
}

/*******************************
 * Multiplication and Division *
 ******************************/
Decimal Decimal::operator*(const Decimal& other) const {
    Decimal result(*this);
    result *= other;
    return result;
}

Decimal Decimal::operator*(const double other) const {
    Decimal result(*this);
    result *= other;
    return result;
}

Decimal& Decimal::operator*=(const Decimal& other) {
    mpfr_mul(value, value, other.value, ROUND_MODE);
    return *this;
}

Decimal& Decimal::operator*=(const double other) {
    mpfr_mul_d(value, value, other, ROUND_MODE);
    return *this;
}

Decimal Decimal::operator/(const Decimal& other) const {
    Decimal result(*this);
    result /= other;
    return result;
}

Decimal Decimal::operator/(const double other) const {
    Decimal result(*this);
    result /= other;
    return result;
}

Decimal& Decimal::operator/=(const Decimal& other) {
    mpfr_div(value, value, other.value, ROUND_MODE);
    return *this;
}

Decimal& Decimal::operator/=(const double other) {
    mpfr_div_d(value, value, other, ROUND_MODE);
    return *this;
}


/******************
 * Exponentiation *
 ******************/
Decimal Decimal::pow(const int exp) const {
    Decimal result;
    mpfr_pow_si(result.value, value, exp, ROUND_MODE);
    return result;
}

Decimal Decimal::pow(const long exp) const {
    Decimal result;
    mpfr_pow_si(result.value, value, exp, ROUND_MODE);
    return result;
}

Decimal Decimal::pow(const double exp) const {
    Decimal result;
    mpfr_pow(result.value, value, Decimal(exp).value, ROUND_MODE);
    return result;
}

Decimal Decimal::pow(const Decimal& exp) const {
    Decimal result;
    mpfr_pow(result.value, value, exp.value, ROUND_MODE);
    return result;
}

Decimal Decimal::pow(const Bignum& exp) const {
    Decimal result;
    mpfr_pow_z(result.value, value, exp.value, ROUND_MODE);
    return result;
}


/*********************
 * Special Functions *
 *********************/
Decimal Decimal::square() const {
    Decimal result;
    mpfr_sqr(result.value, value, ROUND_MODE);
    return result;
}

Decimal Decimal::sqrt() const {
    Decimal result;
    mpfr_sqrt(result.value, value, ROUND_MODE);
    return result;
}

Decimal Decimal::cbrt() const {
    Decimal result;
    mpfr_cbrt(result.value, value, ROUND_MODE);
    return result;
}

Decimal Decimal::round() const {
    Decimal result;
    mpfr_round(result.value, value);
    return result;
}

Decimal Decimal::floor() const {
    Decimal result;
    mpfr_floor(result.value, value);
    return result;
}

Decimal Decimal::ceil() const {
    Decimal result;
    mpfr_ceil(result.value, value);
    return result;
}

Decimal Decimal::log() const {
    Decimal result;
    mpfr_log(result.value, value, ROUND_MODE);
    return result;
}

Decimal Decimal::exp() const {
    Decimal result;
    mpfr_log(result.value, value, ROUND_MODE);
    return result;
}


/********************
 * Useful constants *
 ********************/
const Decimal Decimal::ZERO = Decimal(0);
const Decimal Decimal::ONE = Decimal(1);


std::ostream& operator<<(std::ostream& os, const Decimal& d) {
    os << "Decimal(" << d.to_string() << ")";
    return os;
}
