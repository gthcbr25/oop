#include <iostream>
#include "Hex.h"

int main() {
    Hex first = Hex(50);
    Hex second = Hex(51);
    std::cout<< first.equal(second) << std::endl;
    return 0;
}