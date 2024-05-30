#include "ray.h"

#include "line.h"
#include "segment.h"
geometry::Ray::Ray() : start_(), end_() {
}
geometry::Ray::Ray(geometry::Point first, geometry::Point second) : start_(first), end_(second) {
}
geometry::Ray& geometry::Ray::Move(const geometry::Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool geometry::Ray::ContainsPoint(const geometry::Point& point) const {
    return (ScalarMult(geometry::Vector(end_.GetX() - start_.GetX(), end_.GetY() - start_.GetY()),
                       geometry::Vector(point.GetX() - start_.GetX(), point.GetY() - start_.GetY()))) >= 0;
}
int64_t GetOrientation(const geometry::Point& a, const geometry::Point& b, const geometry::Point& c) {
    int64_t value = (b.GetY() - a.GetY()) * (c.GetX() - b.GetX()) - (b.GetX() - a.GetX()) * (c.GetY() - b.GetY());

    if (value == 0) {
        return 2;
    } else if (value > 0) {
        return 1;
    } else {
        return 0;
    }
}

bool ArePointsOnDifferentSides(const geometry::Point& p1, const geometry::Point& p2, const geometry::Point& a,
                               const geometry::Point& b) {
    int64_t first = GetOrientation(a, b, p1);
    int64_t second = GetOrientation(a, b, p2);

    if (first == 2 && second == 2) {
        return true;
    }
    return first != second;
}
bool geometry::Ray::CrossesSegment(const geometry::Segment& segment) const {
    if ((Line(start_, end_).CrossesSegment(segment) && segment.Distance(end_) <= segment.Distance(start_)) ||
        segment.ContainsPoint(start_)) {
        return true;
    } else if (Line(start_, end_).CrossesSegment(segment) && segment.Distance(end_) > segment.Distance(start_) &&
               ArePointsOnDifferentSides(start_, end_, segment.GetStart(), segment.GetEnd())) {
        return true;
    }
    return false;
}

geometry::Ray* geometry::Ray::Clone() const {
    return new Ray(start_, end_);
}
geometry::Point geometry::Ray::GetStart() const {
    return start_;
}
geometry::Point geometry::Ray::GetEnd() const {
    return end_;
}
