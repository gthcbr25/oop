#pragma once

#include <iostream>
#include <initializer_list>

#include "polygon.h"

class Triangle : public Polygon
{
	public:
    	Triangle();
    	Triangle(std::initializer_list<Point> vertices);

    	operator double();

    	bool operator==(const Triangle &other) const;
    	Triangle &operator=(const Triangle &other);
    	Triangle &operator=(Triangle &&other) noexcept ;

    	friend std::istream &operator>>(std::istream &is, const Triangle &tr);
    	friend std::ostream &operator<<(std::ostream &os, const Triangle &tr);

    	~Triangle() override;
};