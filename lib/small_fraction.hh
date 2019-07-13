struct Fraction {
    Fraction() : num_(0), den_(1) {
    }

    Fraction(uint64_t a) : num_(a), den_(1) {
    }

    Fraction(uint64_t a, uint64_t b) : num_(a), den_(b) {
    }

    uint64_t num() const {
        return num_;
    }

    uint64_t den() const {
        return den_;
    }

    Fraction operator+(const Fraction& other) const {
        Fraction res = *this;
        res += other;
        return res;
    }

    Fraction& operator+=(const Fraction& other) {
        num_ = (num_ * other.den_) + (other.num_ * den_);
        den_ = den_ * other.den_;
        reduce();
        return *this;
    }

    Fraction operator-(const Fraction& other) const {
        Fraction res = *this;
        res -= other;
        return res;
    }

    Fraction& operator-=(const Fraction& other) {
        num_ = (num_ * other.den_) - (other.num_ * den_);
        den_ = den_ * other.den_;
        reduce();
        return *this;
    }

    void reduce() {
        uint64_t g = gcd(num_, den_);
        num_ /= g;
        den_ /= g;
    }

    // a/b == c/d   => a*d == c*b
    bool operator==(const Fraction& other) const {
        return num_ * other.den_ == other.num_ * den_;
    }

    bool operator<(const Fraction& other) const {
        return num_ * other.den_ < other.num_ * den_;
    }

    bool operator>(const Fraction& other) const {
        return num_ * other.den_ > other.num_ * den_;
    }

    std::string to_string() const {
        if (num_ == 0) {
            return "0";
        }
        return std::to_string(num_) + "/" + std::to_string(den_);
    }

    uint64_t num_;
    uint64_t den_;
};

Fraction operator/(uint64_t mult, const Fraction& f) {
    Fraction res;
    res.num_ = mult * f.den_;
    res.den_ = f.num_;
    return res;
}


namespace std {
    template <>
    struct hash<Fraction> {
        size_t operator()(const Fraction& f) const {
            return 61 * f.num_ + f.den_;
        }
    };
}
