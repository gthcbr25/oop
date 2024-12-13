#include "Hex.h"
#include <iostream>
#include <cstddef>
#include <cmath>
#include <string>

Hex::Hex() {
    _size = 0;
    array = new unsigned char[1]{0};
    decimal = 0;
}

Hex::Hex(unsigned int decimal_value) {
    decimal = decimal_value;
    unsigned int decimal_value_copy = decimal_value;
    size_t size = 0;

    while (decimal_value_copy > 0) {
        size++;
        decimal_value_copy /= 16;
    }

    _size = size;
    array = new unsigned char[size]{};
    std::string q = "0123456789ABCDEF";

    for (size_t i = 0; i < _size; ++i) {
        array[size - 1 - i] = q[decimal_value % 16];
        decimal_value /= 16;
    }
}

Hex::Hex(const Hex &other) {
    _size = other._size;
    array = new unsigned char[_size]{};
    decimal = other.decimal;
    for (size_t i = 0; i < _size; ++i) {
        array[i] = other.array[i];
    }
}

Hex::~Hex() noexcept{
    this->_size = 0;
    this->decimal = 0;
    delete []this->array;
    this->array = nullptr;
}

Hex Hex::summ(const Hex& other) const {
    return Hex(this->decimal + other.decimal);
}

Hex Hex::subb(const Hex& other) const {
    if (other.decimal < this->decimal) {
        return Hex(this->decimal - other.decimal);
    }
    throw std::invalid_argument("Cannot subtract");

}

bool Hex::more(const Hex& other) const {
    return this->decimal > other.decimal;
}

bool Hex::less(const Hex& other) const {
    return this->decimal < other.decimal;
}

bool Hex::equal(const Hex& other) const {
    return this->decimal == other.decimal;
}