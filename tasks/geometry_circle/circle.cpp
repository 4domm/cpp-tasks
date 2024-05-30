#include "circle.h"

#include "math.h"
#include "segment.h"
geometry::Circle::Circle() : centre_(), radius_() {
}
geometry::Circle::Circle(geometry::Point point, int64_t radius) : centre_(point), radius_(radius) {
}
geometry::Circle& geometry::Circle::Move(const geometry::Vector& vector) {
    centre_.Move(vector);
    return *this;
}
bool geometry::Circle::ContainsPoint(const geometry::Point& point) const {
    return (point.GetX() - centre_.GetX()) * (point.GetX() - centre_.GetX()) +
               (point.GetY() - centre_.GetY()) * (point.GetY() - centre_.GetY()) <=
           radius_ * radius_;
}
double Distance(geometry::Point first, geometry::Point second) {
    return std::sqrt(((second.GetX() - first.GetX()) * (second.GetX() - first.GetX())) +
                     ((second.GetY() - first.GetY()) * (second.GetY() - first.GetY())));
}
bool geometry::Circle::CrossesSegment(const geometry::Segment& segment) const {
    return (segment.Distance(centre_) <= static_cast<double>(radius_) &&
            (Distance(segment.GetStart(), centre_) >= static_cast<double>(radius_) ||
             Distance(segment.GetEnd(), centre_) >= static_cast<double>(radius_)));
}
geometry::Circle* geometry::Circle::Clone() const {
    return new Circle(centre_, radius_);
}
int64_t geometry::Circle::GetRadius() const {
    return radius_;
}
geometry::Point geometry::Circle::GetCenter() const {
    return centre_;
}
