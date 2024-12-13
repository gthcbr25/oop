#include <cmath>
#include "polygon.h"

double Polygon::getArea()
{
    double result = 0;
    for (int i{}; i < pointCount; ++i)
    {
        int n = (i + 1) % pointCount;
        result += (points[i].x * points[n].y);
        result -= (points[n].x * points[i].y);
    }
    return std::abs(result / 2);
}

Point Polygon::getCenter()
{
    Point result{};
    result.x = result.y = 0;

    for (int i{}; i < pointCount; ++i)
    {
        result.x += points[i].x;
        result.y += points[i].y;
    }

    result.x /= pointCount;
    result.y /= pointCount;
    return result;
}

bool Polygon::compare(const Polygon &other) const
{
    if (pointCount != other.pointCount)
    {
        return false;
    }

    for (int i{}, j{}; j < pointCount; ++j)
    {
        if (i == pointCount)
        {
            return true;
        }
        if (points[i] == other.points[j])
        {
            ++i;
            j = -1;
        }
    }
    return false;
}