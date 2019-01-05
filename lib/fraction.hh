#pragma once
#include "bignum.hh"

class Fraction {
    public:
        Fraction() {
            mpq_init(value);
        }

        Fraction& operator=(const Fraction& other) {
            if (this != &other) {
                mpq_init(value);
                mpq_set(value, other.value);
            }
            return *this;
        }

        Fraction& operator=(Fraction&& other) {
            if (this != &other) {
                // swap without initializing value for efficiency
                std::swap(value, other.value);

                // we need to avoid calling mpq_clear in the destructor of
                // other, so we use this gross hack to indicate that the
                // value is invalid instead of adding another field in the class
                other.value->_mp_num._mp_size = INT_MAX;
            }
            return *this;
        }

        Fraction(Fraction&& other) {
            *this = std::move(other);
        }

        Fraction(const Fraction& other) {
            *this = other;
        }

        ~Fraction() {
            if (value->_mp_num._mp_size != INT_MAX) {
                mpq_clear(value);
            }
        }

        Fraction(const Bignum& n, const Bignum& d = Bignum::ONE);
        Fraction(const int n, const int d = 1);
        Fraction(const long n, const long d = 1);
        Fraction(const double f);
        Fraction(const char* s, int base = 0);
        Fraction(const std::string& s, int base = 0);

        Bignum num() const;
        Bignum den() const;
        long to_long() const;
        double to_double() const;
        std::string to_string(int base = 10) const;

        static bool compare(const Fraction& a, const Fraction& b);
        int cmp(const Bignum& other) const;
        int cmp(const Fraction& other) const;
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

        Fraction abs() const;
        Fraction negate() const;

        Fraction operator+(const Fraction& other) const;
        Fraction& operator+=(const Fraction& other);

        Fraction operator-(const Fraction& other) const;
        Fraction& operator-=(const Fraction& other);

        Fraction operator*(const Fraction& other) const;
        Fraction& operator*=(const Fraction& other);

        Fraction operator/(const Fraction& other) const;
        Fraction& operator/=(const Fraction& other);

        Fraction pow(long exp) const;

        static const Fraction ZERO;
        static const Fraction ONE;

        friend class Decimal;

        template<typename numeric_type>
        friend Fraction operator+(const numeric_type& left, const Fraction& right);

        template<typename numeric_type>
        friend Fraction operator-(const numeric_type& left, const Fraction& right);

        template<typename numeric_type>
        friend Fraction operator*(const numeric_type& left, const Fraction& right);

        template<typename numeric_type>
        friend Fraction operator/(const numeric_type& left, const Fraction& right);


        friend std::ostream& operator<<(std::ostream& os, const Fraction& f);

    private:
        mpq_t value;
};


/**************************************
 * Constructors and Memory Management *
 **************************************/
Fraction::Fraction(const long n, const long d) : Fraction() {
    if (d == 0) {
        throw std::invalid_argument("Denominator of 0");
    } else if (d < 0) {
        mpq_set_si(value, -n, -d);
    } else {
        mpq_set_si(value, n, d);
    }
    mpq_canonicalize(value);
}

Fraction::Fraction(const int n, const int d) : Fraction((long) n, (long) d) {
}

Fraction::Fraction(const Bignum& n, const Bignum& d) : Fraction() {
    if (d == 0) {
        throw std::invalid_argument("Denominator of 0");
    }
    mpq_set_num(value, n.value);
    mpq_set_den(value, d.value);
}

Fraction::Fraction(const double d) : Fraction() {
    mpq_set_d(value, d);
}

Fraction::Fraction(const char* s, int base) : Fraction() {
    if (mpq_set_str(value, s, base) != 0) {
        throw std::invalid_argument("Argument is not a valid fraction");
    }
}

Fraction::Fraction(const std::string& s, int base) : Fraction(s.c_str(), base) {
}


/************************
 * Conversion Functions *
 ***********************/
Bignum Fraction::num() const {
    Bignum b;
    mpq_get_num(b.value, value);
    return b;
}

Bignum Fraction::den() const {
    Bignum b;
    mpq_get_den(b.value, value);
    return b;
}

long Fraction::to_long() const {
    return mpq_get_d(value);
}

double Fraction::to_double() const {
    return mpq_get_d(value);
}

std::string Fraction::to_string(int base) const {
    char* s = mpq_get_str(nullptr, base, value);
    std::string result(s);
    free(s);
    return result;
}


/************************
 * Comparison Functions *
 ***********************/
int Fraction::cmp(const Fraction& other) const {
    return mpq_cmp(value, other.value);
}

int Fraction::cmp(const Bignum& b) const {
    return mpq_cmp_z(value, b.value);
}

int Fraction::cmp(const int n) const {
    return mpq_cmp_si(value, n, 1);
}

int Fraction::cmp(const long n) const {
    return mpq_cmp_si(value, n, 1);
}

int Fraction::cmp(const double d) const {
    return cmp(Fraction(d));
}

bool Fraction::compare(const Fraction& a, const Fraction& b) {
    return a.cmp(b) < 0;
}

template<typename numeric_type>
bool Fraction::operator<(const numeric_type& other) const {
    return cmp(other) < 0;
}

template<typename numeric_type>
bool Fraction::operator<=(const numeric_type& other) const {
    return cmp(other) <= 0;
}

template<typename numeric_type>
bool Fraction::operator>(const numeric_type& other) const {
    return cmp(other) > 0;
}

template<typename numeric_type>
bool Fraction::operator>=(const numeric_type& other) const {
    return cmp(other) >= 0;
}

template<typename numeric_type>
bool Fraction::operator==(const numeric_type& other) const {
    return cmp(other) == 0;
}

template<typename numeric_type>
bool Fraction::operator!=(const numeric_type& other) const {
    return cmp(other) != 0;
}

/******************************
 * Basic Arithmetic Functions *
 ******************************/
Fraction Fraction::abs() const {
    Fraction result;
    mpq_abs(result.value, value);
    return result;
}

Fraction Fraction::negate() const {
    Fraction result;
    mpq_neg(result.value, value);
    return result;
}

Fraction Fraction::operator+(const Fraction& other) const {
    Fraction result(*this);
    result += other;
    return result;
}

template<typename numeric_type>
Fraction operator+(const numeric_type& left, const Fraction& right) {
    return right + left;
}


Fraction& Fraction::operator+=(const Fraction& other) {
    mpq_add(value, value, other.value);
    return *this;
}


Fraction Fraction::operator-(const Fraction& other) const {
    Fraction result(*this);
    result -= other;
    return result;
}

template<typename numeric_type>
Fraction operator-(const numeric_type& left, const Fraction& right) {
    Fraction result = right - left;
    mpq_neg(result.value, result.value);
    return result;
}


Fraction& Fraction::operator-=(const Fraction& other) {
    mpq_sub(value, value, other.value);
    return *this;
}

/*******************************
 * Multiplication and Division *
 ******************************/
Fraction Fraction::operator*(const Fraction& other) const {
    Fraction result(*this);
    result *= other;
    return result;
}

template<typename numeric_type>
Fraction operator*(const numeric_type& left, const Fraction& right) {
    return right * left;
}

Fraction& Fraction::operator*=(const Fraction& other) {
    mpq_mul(value, value, other.value);
    return *this;
}

Fraction Fraction::operator/(const Fraction& other) const {
    Fraction result(*this);
    result /= other;
    return result;
}

template<typename numeric_type>
Fraction operator/(const numeric_type& left, const Fraction& right) {
    return Fraction(left) / right;
}

Fraction& Fraction::operator/=(const Fraction& other) {
    mpq_div(value, value, other.value);
    return *this;
}

/******************
 * Exponentiation *
 ******************/
Fraction Fraction::pow(long exp) const {
    Fraction result(*this);
    if (exp < 0) {
        mpq_inv(result.value, result.value);
        exp *= -1;
    }
    mpz_pow_ui(mpq_numref(result.value), mpq_numref(result.value), exp);
    mpz_pow_ui(mpq_denref(result.value), mpq_denref(result.value), exp);
    mpq_canonicalize(result.value);
    return result;
}

/********************
 * Useful constants *
 ********************/
const Fraction Fraction::ZERO = Fraction(0);
const Fraction Fraction::ONE = Fraction(1);


std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << "Fraction(" << f.to_string() << ")";
    return os;
}
