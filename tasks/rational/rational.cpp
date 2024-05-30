#include <rational.h>
Rational::Rational() {
    Set(0, 1);
}
Rational::Rational(int value) {  // NOLINT
    Set(value, 1);
}
Rational::Rational(int numer, int denom) {
    Set(numer, denom);
}
int Rational::GetNumerator() const {
    return numer_;
}
int Rational::GetDenominator() const {
    return denom_;
}
void Rational::SetNumerator(int value) {
    Set(value, denom_);
}
void Rational::SetDenominator(int value) {
    Set(numer_, value);
}
Rational& operator+=(Rational& lhs, const Rational& rhs) {
    lhs.SetNumerator(lhs.GetNumerator() * rhs.GetDenominator() + lhs.GetDenominator() * rhs.GetNumerator());
    lhs.SetDenominator(lhs.GetDenominator() * rhs.GetDenominator());
    return lhs;
}
Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.SetNumerator(lhs.GetNumerator() * rhs.GetNumerator());
    lhs.SetDenominator(lhs.GetDenominator() * rhs.GetDenominator());
    return lhs;
}
Rational& operator++(Rational& ratio) {
    ratio += 1;
    return ratio;
}
Rational& operator--(Rational& ratio) {
    ratio -= 1;
    return ratio;
}
std::istream& operator>>(std::istream& is, Rational& ratio) {
    int64_t numer{};
    int64_t denom = 1;
    is >> numer;
    if (is.peek() == '/') {
        is.get();
        is >> denom;
    }
    ratio.Set(numer, denom);
    return is;
}
Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs += (-rhs);
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    lhs.SetNumerator(lhs.GetNumerator() * rhs.GetDenominator());
    lhs.SetDenominator(lhs.GetDenominator() * rhs.GetNumerator());
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational sum_result = lhs;
    sum_result += rhs;
    return sum_result;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational diff_result = lhs;
    diff_result -= rhs;
    return diff_result;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.GetNumerator() * rhs.GetNumerator(), lhs.GetDenominator() * rhs.GetDenominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator());
}

Rational operator++(Rational& ratio, int) {
    Rational result = ratio;
    ++ratio;
    return result;
}

Rational operator--(Rational& ratio, int) {
    Rational result = ratio;
    --ratio;
    return result;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return (lhs.GetNumerator() * rhs.GetDenominator()) < (rhs.GetNumerator() * lhs.GetDenominator());
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return (lhs.GetNumerator() * rhs.GetDenominator()) > (rhs.GetNumerator() * lhs.GetDenominator());
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.GetNumerator() * rhs.GetDenominator()) == (rhs.GetNumerator() * lhs.GetDenominator());
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}
std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1) {
        os << ratio.GetNumerator();
        return os;
    } else if (ratio.GetNumerator() == 0) {
        os << ratio.GetNumerator();
        return os;
    } else {
        os << ratio.GetNumerator() << '/' << ratio.GetDenominator();
        return os;
    }
}
void Rational::Set(int64_t numer, int64_t denom) {
    int64_t gcd = std::gcd(std::abs(numer), std::abs(denom));
    if (denom == 0) {
        throw RationalDivisionByZero();
    }
    if (denom < 0) {
        numer = -numer;
        denom = -denom;
    }
    numer_ = static_cast<int>(numer / gcd);
    denom_ = static_cast<int>(denom / gcd);
}
