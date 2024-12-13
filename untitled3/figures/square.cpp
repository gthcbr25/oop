#include <algorithm>
#include "square.h"

Square::Square()
{
    pointCount = 4;
    points = new Point[pointCount];
}

Square::Square(std::initializer_list<Point> vertices): Square{}
{
    if (vertices.size() != pointCount) {
        throw std::invalid_argument("Invalid vertex count.");
    }
    std::copy(vertices.begin(), vertices.end(), points);
}

Square::operator double()
{
    return Polygon::getArea();
}

Square &Square::operator=(const Square &other)
{
    for (int i{}; i < pointCount; ++i)
    {
        points[i] = other.points[i];
    }
    return *this;
}

Square &Square::operator=(Square &&other)
 noexcept {
    if (points != nullptr)
    {
        delete[] points;
    }
    points = other.points;
    other.points = nullptr;
    return *this;
}

bool Square::operator==(const Square &other) const
{
    return compare(other);
}

std::istream &operator>>(std::istream &is, const Square &sq)
{
    for (int i{}; i < sq.pointCount; ++i)
    {
        is >> sq.points[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Square &sq)
{
    os << "Octagon with points: ( ";
    for (int i{}; i < sq.pointCount; ++i)
    {
        os << sq.points[i] << ' ';
    }
    return os << ')';
}

Square::~Square()
{
    delete[] points;
}