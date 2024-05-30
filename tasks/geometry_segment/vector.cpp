#include "vector.h"

#include <cstdint>

geometry::Vector::Vector() : x_coord_(0), y_coord_(0) {
}
geometry::Vector::Vector(int64_t x, int64_t y) : x_coord_(x), y_coord_(y) {
}
int64_t geometry::Vector::GetX() const {
    return x_coord_;
}
int64_t geometry::Vector::GetY() const {
    return y_coord_;
}
geometry::Vector geometry::Vector::operator+(const geometry::Vector& other) const {
    return Vector(GetX() + other.x_coord_, GetY() + other.y_coord_);
}
geometry::Vector geometry::Vector::operator-(const geometry::Vector& other) const {
    return Vector(GetX() - other.x_coord_, GetY() - other.y_coord_);
}
geometry::Vector geometry::Vector::operator+() const {
    return *this;
}
geometry::Vector geometry::Vector::operator-() const {
    return Vector(-GetX(), -GetY());
}
geometry::Vector geometry::Vector::operator*(int64_t number) const {
    return Vector(number * GetX(), number * GetY());
}
geometry::Vector geometry::Vector::operator/(int64_t number) const {
    return Vector(GetX() / number, GetY() / number);
}
geometry::Vector& geometry::Vector::operator-=(const geometry::Vector& other) {
    x_coord_ -= other.x_coord_;
    y_coord_ -= other.y_coord_;
    return *this;
}
geometry::Vector& geometry::Vector::operator+=(const geometry::Vector& other) {
    x_coord_ += other.x_coord_;
    y_coord_ += other.y_coord_;
    return *this;
}
geometry::Vector& geometry::Vector::operator*=(int64_t number) {
    x_coord_ *= number;
    y_coord_ *= number;
    return *this;
}
geometry::Vector& geometry::Vector::operator/=(int64_t number) {
    x_coord_ /= number;
    y_coord_ /= number;
    return *this;
}
bool geometry::Vector::operator==(const geometry::Vector& other) const {
    return (x_coord_ == other.x_coord_) && (y_coord_ == other.y_coord_);
}

int64_t geometry::ScalarMult(const geometry::Vector& first, const geometry::Vector& second) {
    return (first.x_coord_ * second.x_coord_ + first.y_coord_ * second.y_coord_);
}
int64_t geometry::VectorMult(const geometry::Vector& first, const geometry::Vector& second) {
    return (first.x_coord_ * second.y_coord_) - (first.y_coord_ * second.x_coord_);
}
double geometry::Length(geometry::Vector vector) {
    return std::sqrt(vector.GetX() * vector.GetX() + vector.GetY() * vector.GetY());
}
