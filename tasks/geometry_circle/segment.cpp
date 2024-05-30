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
    double value = static_cast<double>((point.GetX() - start_.GetX()) * (end_.GetX() - start_.GetX()) +
                                       (point.GetY() - start_.GetY()) * (end_.GetY() - start_.GetY())) /
                   static_cast<double>((start_.GetX() - end_.GetX()) * (start_.GetX() - end_.GetX()) +
                                       (start_.GetY() - end_.GetY()) * (start_.GetY() - end_.GetY()));

    if (value < 0) {
        value = 0;
    }
    if (value > 1) {
        value = 1;
    }
    double distance = std::sqrt((static_cast<double>(start_.GetX()) - static_cast<double>(point.GetX()) +
                                 static_cast<double>(end_.GetX() - start_.GetX()) * value) *
                                    (static_cast<double>(start_.GetX()) - static_cast<double>(point.GetX()) +
                                     static_cast<double>(end_.GetX() - start_.GetX()) * value) +
                                (static_cast<double>(start_.GetY()) - static_cast<double>(point.GetY()) +
                                 static_cast<double>(end_.GetY() - start_.GetY()) * value) *
                                    (static_cast<double>(start_.GetY()) - static_cast<double>(point.GetY()) +
                                     static_cast<double>(end_.GetY() - start_.GetY()) * value));
    return (distance);
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