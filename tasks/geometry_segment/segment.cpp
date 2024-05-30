#include "segment.h"

#include <algorithm>
#include <cstdint>

#include "vector.h"
geometry::Segment::Segment() : start_(), end_() {
}
geometry::Segment::Segment(geometry::Point first, geometry::Point second) : start_(first), end_(second) {
}
geometry::Point geometry::Segment::GetStart() const {
    return start_;
}
geometry::Point geometry::Segment::GetEnd() const {
    return end_;
}
double geometry::Segment::Distance(geometry::Point point) const {
    const Point& point_one = GetStart();
    const Point& point_two = GetEnd();
    if (Degenerate()) {
        return std::sqrt((point_two.GetX() - point_one.GetX()) * (point_two.GetX() - point_one.GetX()) +
                         (point_two.GetY() - point_one.GetY()) * ((point_two.GetY() - point_two.GetY())));
    }
    double parameter =
        static_cast<double>(((point.GetX() - point_one.GetX()) * (point_two.GetX() - point_one.GetX()) +
                             (point.GetY() - point_one.GetY()) * (point_two.GetY() - point_one.GetY()))) /
            pow(static_cast<double>(point_two.GetX() - point_one.GetX()), 2) +
        pow(static_cast<double>(point_two.GetY() - point_one.GetY()), 2);
    parameter = std::max(0.0, std::min(parameter, 1.0));

    double proj_x =
        static_cast<double>(point_one.GetX()) + parameter * static_cast<double>(point_two.GetX() - point_one.GetX());
    double proj_y =
        static_cast<double>(point_one.GetY()) + parameter * static_cast<double>(point_two.GetY() - point_one.GetY());
    return std::sqrt((static_cast<double>(point.GetX()) - proj_x) * (static_cast<double>(point.GetX()) - proj_x) +
                     (static_cast<double>(point.GetY()) - proj_y) * (static_cast<double>(point.GetY()) - proj_y));
}
bool geometry::Segment::Degenerate() const {
    return GetStart().GetX() == GetEnd().GetX() && GetStart().GetY() == GetEnd().GetY();
}
geometry::Segment& geometry::Segment::Move(const geometry::Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}
bool geometry::Segment::ContainsPoint(const Point& point) const {
    if (std::min(start_.GetX(), end_.GetX()) <= point.GetX() && point.GetX() <= std::max(start_.GetX(), end_.GetX()) &&
        std::min(start_.GetY(), end_.GetY()) <= point.GetY() && point.GetY() <= std::max(start_.GetY(), end_.GetY())) {
        if ((point.GetX() - start_.GetX()) * (end_.GetY() - start_.GetY()) ==
            (point.GetY() - start_.GetY()) * (end_.GetX() - start_.GetX())) {
            return true;
        }
    }
    return false;
}
int CheckOrientation(geometry::Point a, geometry::Point b, geometry::Point c) {
    int64_t val = (b.GetY() - a.GetY()) * (c.GetX() - b.GetX()) - (b.GetX() - a.GetX()) * (c.GetY() - b.GetY());
    if (val == 0) {
        return 0;
    }
    return (val > 0) ? 1 : -1;
}
bool geometry::Segment::CrossesSegment(const Segment& segment) const {
    int orientation_first = CheckOrientation(start_, end_, segment.start_);
    int orientation_second = CheckOrientation(start_, end_, segment.end_);
    int orientation_third = CheckOrientation(segment.start_, segment.end_, start_);
    int orientation_fourth = CheckOrientation(segment.start_, segment.end_, end_);
    if ((orientation_first > 0 && orientation_second < 0) || (orientation_first < 0 && orientation_second > 0)) {
        if ((orientation_third > 0 && orientation_fourth < 0) || (orientation_third < 0 && orientation_fourth > 0)) {
            return true;
        }
    }
    if (orientation_first == 0 && segment.start_.GetX() >= std::min(start_.GetX(), end_.GetX()) &&
        segment.start_.GetX() <= std::max(start_.GetX(), end_.GetX()) &&
        segment.start_.GetY() >= std::min(start_.GetY(), end_.GetY()) &&
        segment.start_.GetY() <= std::max(start_.GetY(), end_.GetY())) {
        return true;
    }

    if (orientation_second == 0 && segment.end_.GetX() >= std::min(start_.GetX(), end_.GetX()) &&
        segment.end_.GetX() <= std::max(start_.GetX(), end_.GetX()) &&
        segment.end_.GetY() >= std::min(start_.GetY(), end_.GetY()) &&
        segment.end_.GetY() <= std::max(start_.GetY(), end_.GetY())) {
        return true;
    }

    if (orientation_third == 0 && start_.GetX() >= std::min(segment.start_.GetX(), segment.end_.GetX()) &&
        start_.GetX() <= std::max(segment.start_.GetX(), segment.end_.GetX()) &&
        start_.GetY() >= std::min(segment.start_.GetY(), segment.end_.GetY()) &&
        start_.GetY() <= std::max(segment.start_.GetY(), segment.end_.GetY())) {
        return true;
    }

    if (orientation_fourth == 0 && end_.GetX() >= std::min(segment.start_.GetX(), segment.end_.GetX()) &&
        end_.GetX() <= std::max(segment.start_.GetX(), segment.end_.GetX()) &&
        end_.GetY() >= std::min(segment.start_.GetY(), segment.end_.GetY()) &&
        end_.GetY() <= std::max(segment.start_.GetY(), segment.end_.GetY())) {
        return true;
    }

    return false;
}

geometry::Segment* geometry::Segment::Clone() const {
    return new Segment(start_, end_);
}