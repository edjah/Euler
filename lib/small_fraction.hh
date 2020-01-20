/*
    This class only supports non-negative fractions
    whose numerator and denominator do not exceed 2^64 - 1.
*/
struct Fraction {
    Fraction() : num_(0), den_(1) {
    }

    Fraction(uint64_t a) : num_(a), den_(1) {
    }

    Fraction(uint64_t a, uint64_t b) : num_(a), den_(b) {
        reduce();
    }

    uint64_t num() const {
        return num_;
    }

    uint64_t den() const {
        return den_;
    }

    Fraction operator+(const Fraction& other) const {
        Fraction res = *this;
        return (res += other);
    }

    Fraction& operator+=(const Fraction& other) {
        num_ = (num_ * other.den_) + (other.num_ * den_);
        den_ = den_ * other.den_;
        reduce();
        return *this;
    }

    Fraction operator-(const Fraction& other) const {
        Fraction res = *this;
        return (res -= other);
    }

    Fraction& operator-=(const Fraction& other) {
        num_ = (num_ * other.den_) - (other.num_ * den_);
        den_ = den_ * other.den_;
        reduce();
        return *this;
    }

    Fraction operator/(const Fraction& other) const {
        Fraction res = *this;
        return (res /= other);
    }

    Fraction& operator/=(const Fraction& other) {
        num_ *= other.den_;
        den_ *= other.num_;
        reduce();
        return *this;
    }

    // a/b == c/d   => a*d == c*b
    bool operator==(const Fraction& other) const {
        return num_ * other.den_ == other.num_ * den_;
    }

    bool operator<(const Fraction& other) const {
        return num_ * other.den_ < other.num_ * den_;
    }

    bool operator<=(const Fraction& other) const {
        return num_ * other.den_ <= other.num_ * den_;
    }

    bool operator>(const Fraction& other) const {
        return num_ * other.den_ > other.num_ * den_;
    }

    bool operator>=(const Fraction& other) const {
        return num_ * other.den_ >= other.num_ * den_;
    }

    std::string to_string() const {
        if (num_ == 0) {
            return "0";
        }
        return std::to_string(num_) + "/" + std::to_string(den_);
    }

  private:
    void reduce() {
        uint64_t g = gcd(num_, den_);
        num_ /= g;
        den_ /= g;
    }

    uint64_t num_;
    uint64_t den_;
};


Fraction operator*(uint64_t scalar, const Fraction& f) {
    return Fraction(scalar * f.den(), f.num());
}

Fraction operator/(uint64_t scalar, const Fraction& f) {
    return Fraction(scalar * f.den(), f.num());
}


namespace std {
    template <>
    struct hash<Fraction> {
        size_t operator()(const Fraction& f) const {
            return 61 * f.num() + f.den();
        }
    };
}
