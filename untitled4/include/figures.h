#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>


template<class T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<Arithmetic T>
struct Point
{
    T x, y;

    bool operator==(const Point &other) const
    {
        return (x == other.x) && (y == other.y);
    }

    friend std::istream &operator>>(std::istream &is, Point &point)
    {
        return is >> point.x >> point.y;
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point)
    {
        return os << '(' << point.x << "," << point.y << ')';
    }
};

template<Arithmetic T>
class Figure
{
protected:
    Figure() = default;
    virtual ~Figure() = default;

public:
    virtual double getArea() = 0;
    virtual Point<T> getCenter() = 0;
};

template<Arithmetic T>
class Polygon : public Figure<T>
{
protected:
    Point<T> *points = nullptr;
    int pointCount = 0;
    bool compare(const Polygon<T> &other) const
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
public:
    double getArea()
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
    Point<T> getCenter()
    {
        Point<T> result{};
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
};

template<Arithmetic T>
class Triangle : public Polygon<T>
{
public:
    using Polygon<T>::pointCount;
    using Polygon<T>::points;

    Triangle()
    {
        pointCount = 3;
        points = new Point<T>[pointCount];
    }

    Triangle(const std::initializer_list<Point<T>> vertices): Triangle{}
    {
        if ((int)vertices.size() != pointCount) {
            throw std::invalid_argument("Invalid vertex count.");
        }
        std::copy(vertices.begin(), vertices.end(), points);
    }

    explicit operator double()
    {
        return Polygon<T>::getArea();
    }

    bool operator==(const Triangle &other) const
    {
        return Polygon<T>::compare(other);
    }

    Triangle &operator=(const Triangle &other)
    {
        for (int i{}; i < pointCount; ++i)
        {
            points[i] = other.points[i];
        }
        return *this;
    }

    Triangle &operator=(Triangle &&other)
    noexcept {
        points = other.points;
        other.points = nullptr;
        return *this;
    }

    friend std::istream &operator>>(std::istream &is, const Triangle &tr)
    {
        for (int i{}; i < tr.pointCount; ++i)
        {
            is >> tr.points[i];
        }
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Triangle &tr)
    {
        os << "Triangle with points: (";
        for (int i{}; i < tr.pointCount; ++i)
        {
            os << tr.points[i] << ' ';
        }
        return os << ')';
    }

    ~Triangle() override
    {
        delete[] points;
    }
};

template<Arithmetic T>
class Square : public Polygon<T>
{
public:
    using Polygon<T>::pointCount;
    using Polygon<T>::points;
    Square()
    {
        pointCount = 4;
        points = new Point<T>[pointCount];
    }

    Square(std::initializer_list<Point<T>> vertices): Square{}
    {
        if (vertices.size() != pointCount) {
            throw std::invalid_argument("Invalid vertex count.");
        }
        std::copy(vertices.begin(), vertices.end(), points);
    }

    explicit operator double()
    {
        return Polygon<T>::getArea();
    }

    bool operator==(const Square &other) const
    {
        return compare(other);
    }

    Square &operator=(const Square &other)
    {
        for (int i{}; i < pointCount; ++i)
        {
            points[i] = other.points[i];
        }
        return *this;
    }

    Square &operator=(Square &&other)
    noexcept {
        if (points != nullptr)
        {
            delete[] points;
        }
        points = other.points;
        other.points = nullptr;
        return *this;
    }

    friend std::istream &operator>>(std::istream &is, const Square &sq)
    {
        for (int i{}; i < sq.pointCount; ++i)
        {
            is >> sq.points[i];
        }
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Square &sq)
    {
        os << "Octagon with points: ( ";
        for (int i{}; i < sq.pointCount; ++i)
        {
            os << sq.points[i] << ' ';
        }
        return os << ')';
    }

    ~Square() override
    {
        delete[] points;
    }
};

template<Arithmetic T>
class Octagon : public Polygon<T>
{
public:
    using Polygon<T>::pointCount;
    using Polygon<T>::points;
    Octagon()
    {
        pointCount = 8;
        points = new Point<T>[pointCount];
    }
    Octagon(std::initializer_list<Point<T>> vertices): Octagon{}
    {
        if (vertices.size() != pointCount) {
            throw std::invalid_argument("Invalid vertex count.");
        }
        std::copy(vertices.begin(), vertices.end(), points);
    }

    explicit operator double()
    {
        return Polygon<T>::getArea();
    }

    bool operator==(const Octagon &other) const
    {
        return compare(other);
    }

    Octagon &operator=(const Octagon &other)
    {
        for (int i{}; i < pointCount; ++i)
        {
            points[i] = other.points[i];
        }
        return *this;
    }
    Octagon &operator=(Octagon &&other)
    noexcept {
        if (points != nullptr)
        {
            delete[] points;
        }
        points = other.points;
        other.points = nullptr;
        return *this;
    }

    friend std::istream &operator>>(std::istream &is, Octagon &oct)
    {
        for (int i{}; i < oct.pointCount; ++i)
        {
            is >> oct.points[i];
        }
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Octagon &oct)
    {
        os << "Octagon with points: ( ";
        for (int i{}; i < oct.pointCount; ++i)
        {
            os << oct.points[i] << ' ';
        }
        return os << ')';
    }

    ~Octagon() override
    {
        delete[] points;
    }
};




