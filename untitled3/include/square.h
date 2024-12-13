#pragma once

#include <iostream>
#include <initializer_list>

#include "polygon.h"

class Square : public Polygon
{
public:
    Square();
    Square(std::initializer_list<Point> vertices);

    explicit operator double();

    bool operator==(const Square &other) const;
    Square &operator=(const Square &other);
    Square &operator=(Square &&other) noexcept ;

    friend std::istream &operator>>(std::istream &is, const Square &tr);
    friend std::ostream &operator<<(std::ostream &os, const Square &tr);

    ~Square() override;
};