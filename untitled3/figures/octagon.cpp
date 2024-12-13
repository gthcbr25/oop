#include <algorithm>
#include "octagon.h"

Octagon::Octagon()
{
    pointCount = 8;
    points = new Point[pointCount];
}

Octagon::Octagon(std::initializer_list<Point> vertices): Octagon{}
{
    if (vertices.size() != pointCount) {
        throw std::invalid_argument("Invalid vertex count.");
    }
    std::copy(vertices.begin(), vertices.end(), points);
}

Octagon::operator double()
{
    return Polygon::getArea();
}

Octagon &Octagon::operator=(const Octagon &other)
{
    for (int i{}; i < pointCount; ++i)
    {
        points[i] = other.points[i];
    }
    return *this;
}

Octagon &Octagon::operator=(Octagon &&other)
 noexcept {
    if (points != nullptr)
    {
        delete[] points;
    }
    points = other.points;
    other.points = nullptr;
    return *this;
}

bool Octagon::operator==(const Octagon &other) const
{
    return compare(other);
}

std::istream &operator>>(std::istream &is, Octagon &oct)
{
    for (int i{}; i < oct.pointCount; ++i)
    {
        is >> oct.points[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Octagon &oct)
{
    os << "Octagon with points: ( ";
    for (int i{}; i < oct.pointCount; ++i)
    {
        os << oct.points[i] << ' ';
    }
    return os << ')';
}

Octagon::~Octagon()
{
    delete[] points;
}