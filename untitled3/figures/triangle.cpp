#include "triangle.h"
#include <algorithm>

Triangle::Triangle()
{
    pointCount = 3;
    points = new Point[pointCount];
}

Triangle::Triangle(const std::initializer_list<Point> vertices): Triangle{}
{
    if (vertices.size() != pointCount) {
        throw std::invalid_argument("Invalid vertex count.");
    }
    std::copy(vertices.begin(), vertices.end(), points);
}

Triangle::operator double()
{
    return Polygon::getArea();
}

Triangle &Triangle::operator=(const Triangle &other)
{
    for (int i{}; i < pointCount; ++i)
    {
        points[i] = other.points[i];
    }
    return *this;
}

Triangle &Triangle::operator=(Triangle &&other)
 noexcept {
    points = other.points;
    other.points = nullptr;
    return *this;
}

bool Triangle::operator==(const Triangle &other) const
{
    return compare(other);
}

std::istream &operator>>(std::istream &is, const Triangle &tr)
{
    for (int i{}; i < tr.pointCount; ++i)
    {
        is >> tr.points[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Triangle &tr)
{
    os << "Triangle with points: (";
    for (int i{}; i < tr.pointCount; ++i)
    {
        os << tr.points[i] << ' ';
    }
    return os << ')';
}

Triangle::~Triangle()
{
    delete[] points;
}