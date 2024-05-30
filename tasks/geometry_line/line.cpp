#include "line.h"

#include "segment.h"
geometry::Line::Line() : start_(), end_() {
}
int64_t geometry::Line::GetA() const {
    return end_.GetY() - start_.GetY();
}
int64_t geometry::Line::GetB() const {
    return start_.GetX() - end_.GetX();
}
int64_t geometry::Line::GetC() const {
    return (start_.GetY() * end_.GetX()) - (start_.GetX() * end_.GetY());
}
geometry::Line::Line(geometry::Point start, geometry::Point end) : start_(start), end_(end) {
}
double geometry::Line::Distance(geometry::Point point) const {
    return static_cast<double>(std::abs(GetA() * point.GetX() + GetB() * point.GetY() + GetC())) /
           (std::sqrt(GetA() * GetA() + GetB() * GetB()));
}
geometry::Line& geometry::Line::Move(const geometry::Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}
bool geometry::Line::ContainsPoint(const geometry::Point& point) const {
    return GetA() * point.GetX() + GetB() * point.GetY() + GetC() == 0;
}
bool geometry::Line::CrossesSegment(const geometry::Segment& segment) const {
    int64_t first_side = GetA() * segment.GetStart().GetX() + GetB() * segment.GetStart().GetY() + GetC();
    int64_t second_side = GetA() * segment.GetEnd().GetX() + GetB() * segment.GetEnd().GetY() + GetC();
    return (first_side <= 0 && 0 <= second_side) || (first_side >= 0 && second_side <= 0);
}
geometry::Line* geometry::Line::Clone() const {
    return new Line(*this);
}
