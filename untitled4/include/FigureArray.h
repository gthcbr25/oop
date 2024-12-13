#include <initializer_list>
#include <memory>
#include "figures.h"

template <class T>
class FigureContainer
{
private:
    static constexpr int allocatedSize = 32;
    std::shared_ptr<Figure<T>> shapeArray[allocatedSize]{nullptr};
    int top = 0;

public:
    FigureContainer() = default;
    FigureContainer(const std::initializer_list<std::shared_ptr<Figure<T>>> shapes) {
        int i{};
        for (std::shared_ptr<Figure<T>> ptr : shapes) {
            shapeArray[i] = ptr;
            ++i;
        }
    }

    std::shared_ptr<Figure<T>> at(const int index) const {
        return shapeArray[index];
    }

    int append(std::shared_ptr<Figure<T>> figPtr) {
        if (top >= allocatedSize) {
            return -1;
        }
        shapeArray[top] = figPtr;
        return top++;
    }

    void remove(const int index) {
        for (int i{index + 1}; i < top; ++i) {
            std::cout << "deleting element " << i << std::endl;
            shapeArray[i - 1] = shapeArray[i];
        }
        --top;
    }

    ~FigureContainer() = default;
};