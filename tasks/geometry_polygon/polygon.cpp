#include "polygon.h"

#include "segment.h"
geometry::Polygon::Polygon() : points_(), num_points_(0) {
}
geometry::Polygon::Polygon(std::vector<Point> points) : points_(points), num_points_(points.size()) {
}
geometry::Polygon& geometry::Polygon::Move(const geometry::Vector& vector) {
    for (auto& point : points_) {
        point.Move(vector);
    }
    return *this;
}
bool geometry::Polygon::ContainsPoint(const geometry::Point& point) const {
    int64_t min_x = std::numeric_limits<int64_t>::max();
    int64_t max_x = std::numeric_limits<int64_t>::min();
    int64_t min_y = std::numeric_limits<int64_t>::max();
    int64_t max_y = std::numeric_limits<int64_t>::min();
    for (size_t i = 0; i < points_.size() - 1; ++i) {
        if (Segment(points_[i], points_[i + 1]).ContainsPoint(point)) {
            return true;
        }
    }
    for (const auto& p : points_) {
        min_x = std::min(min_x, p.GetX());
        max_x = std::max(max_x, p.GetX());
        min_y = std::min(min_y, p.GetY());
        max_y = std::max(max_y, p.GetY());
    }

    if (point.GetX() < min_x || point.GetX() > max_x || point.GetY() < min_y || point.GetY() > max_y) {
        return false;
    }
    bool contains = false;
    size_t j = num_points_ - 1;
    for (size_t i = 0; i < points_.size(); i++) {
        if (((points_[i].GetY() > point.GetY()) != (points_[j].GetY() > point.GetY())) &&
            (point.GetX() < (points_[j].GetX() - points_[i].GetX()) * (point.GetY() - points_[i].GetY()) /
                                    (points_[j].GetY() - points_[i].GetY()) +
                                points_[i].GetX())) {
            contains = !contains;
        }
        j = i;
    }
    return contains;
}
bool geometry::Polygon::CrossesSegment(const geometry::Segment& segment) const {
    for (size_t i = 0; i < points_.size() - 1; ++i) {
        if (Segment(points_[i], points_[i + 1]).CrossesSegment(segment)) {
            return true;
        }
    }
    return false;
}
geometry::Polygon* geometry::Polygon::Clone() const {
    return new Polygon(*this);
}