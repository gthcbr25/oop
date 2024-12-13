#pragma once

#include <iostream>

struct Point
{
	double x, y;

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

class Figure
{
protected:
	Figure() = default;
	virtual ~Figure() = default;

public:
	virtual double getArea() = 0;
	virtual Point getCenter() = 0;
};

class Polygon : public Figure
{
	protected:
    	Point *points = nullptr;
    	int pointCount = 0;
		bool compare(const Polygon &other) const;
	public:
    	double getArea() override;
    	Point getCenter() override;
};