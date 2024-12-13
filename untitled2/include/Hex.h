#pragma onсe
#include <string>

class Hex {
public:
    Hex();
    Hex(unsigned int decimal_value);
    Hex(const Hex& src);

    virtual ~Hex() noexcept;

    Hex summ(const Hex& other) const;
    Hex subb(const Hex& other) const;

    bool equal(const Hex& other) const;
    bool less(const Hex& other) const ;
    bool more(const Hex& other) const;


private:
    size_t _size;
    unsigned char *array;
    unsigned int decimal;
};