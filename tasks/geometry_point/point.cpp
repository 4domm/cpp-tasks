#include "point.h"

#include "segment.h"
int64_t geometry::Point::GetX() const {
    return x_coord_;
}
int64_t geometry::Point::GetY() const {
    return y_coord_;
}
void geometry::Point::SetX(int64_t x) {
    x_coord_ = x;
}
void geometry::Point::SetY(int64_t y) {
    y_coord_ = y;
}
geometry::Point &geometry::Point::Move(const geometry::Vector &vector) {
    x_coord_ += vector.GetX();
    y_coord_ += vector.GetY();
    return *this;
}
bool geometry::Point::ContainsPoint(const geometry::Point &other) const {
    return (x_coord_ == other.x_coord_ && y_coord_ == other.y_coord_);
}
bool geometry::Point::CrossesSegment(const geometry::Segment &segment) const {
    int64_t vec_prod =
        (y_coord_ - segment.GetStart().y_coord_) * (segment.GetEnd().x_coord_ - segment.GetStart().x_coord_) -
        (x_coord_ - segment.GetStart().x_coord_) * (segment.GetEnd().y_coord_ - segment.GetStart().y_coord_);
    if (vec_prod != 0) {
        return false;
    }
    int64_t scalar_prod =
        (x_coord_ - segment.GetStart().x_coord_) * (segment.GetEnd().x_coord_ - segment.GetStart().x_coord_) +
        (y_coord_ - segment.GetStart().y_coord_) * (segment.GetEnd().y_coord_ - segment.GetStart().y_coord_);
    if (scalar_prod < 0) {
        return false;
    }
    int64_t length_vec = (segment.GetEnd().x_coord_ - segment.GetStart().x_coord_) *
                             (segment.GetEnd().x_coord_ - segment.GetStart().x_coord_) +
                         (segment.GetEnd().y_coord_ - segment.GetStart().y_coord_) *
                             (segment.GetEnd().y_coord_ - segment.GetStart().y_coord_);
    if (scalar_prod > length_vec) {
        return false;
    }
    return true;
}
geometry::Point *geometry::Point::Clone() const {
    return new Point(x_coord_, y_coord_);
}
geometry::Point::Point(int64_t x, int64_t y) : x_coord_(x), y_coord_(y) {
}
geometry::Vector geometry::Point::operator-(geometry::Point other) const {
    return Vector(x_coord_ - other.x_coord_, y_coord_ - other.y_coord_);
}
