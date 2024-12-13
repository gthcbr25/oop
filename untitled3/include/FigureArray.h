#include <initializer_list>

#include "polygon.h"

class FigureContainer
{
private:
    static constexpr int allocatedSize = 32;
    Figure* shapeArray[allocatedSize]{nullptr};
    int top = 0;

public:
    FigureContainer() = default;
    FigureContainer(std::initializer_list<Figure*> shapes);

    [[nodiscard]] Figure* at(int index) const;
    int append(Figure* figPtr);
    void remove(int index);

    ~FigureContainer() = default;
};