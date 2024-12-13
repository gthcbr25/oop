#include "DinamicArray.hpp"

int main() {
    ListMemoryResource memory_resource;
    DynamicArray<int> dynamic_array(&memory_resource);

    dynamic_array.push_back(10);
    dynamic_array.push_back(20);
    dynamic_array.push_back(30);

    for (int value : dynamic_array) {
        std::cout << value << " ";
    }

    struct Complex {
        int id;
        std::string name;
    };

    DynamicArray<Complex> complex_array(&memory_resource);
    complex_array.push_back({1, "Alice"});
    complex_array.push_back({2, "Bob"});

    for (const auto& obj : complex_array) {
        std::cout << "{id: " << obj.id << ", name: " << obj.name << "} ";
    }

    return 0;
}