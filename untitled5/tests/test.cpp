#include "DinamicArray.hpp"
#include <gtest\gtest.h>
#include <memory>


TEST(DynamicArrayTest, PushBackAndAccess) {
ListMemoryResource memory_resource;
DynamicArray<int> array(&memory_resource);

array.push_back(10);
array.push_back(20);
array.push_back(30);

EXPECT_EQ(array.size(), 3);
EXPECT_EQ(array[0], 10);
EXPECT_EQ(array[1], 20);
EXPECT_EQ(array[2], 30);
}

TEST(DynamicArrayTest, OutOfRangeAccess) {
ListMemoryResource memory_resource;
DynamicArray<int> array(&memory_resource);

array.push_back(10);

EXPECT_THROW(array[1], std::out_of_range);
}

TEST(DynamicArrayTest, IteratorTest) {
ListMemoryResource memory_resource;
DynamicArray<int> array(&memory_resource);

array.push_back(1);
array.push_back(2);
array.push_back(3);

int sum = 0;
for (int value : array) {
sum += value;
}

EXPECT_EQ(sum, 6);
}

TEST(DynamicArrayTest, ComplexTypeTest) {
struct Complex {
    int id;
    std::string name;

    bool operator==(const Complex& other) const {
        return id == other.id && name == other.name;
    }
};

ListMemoryResource memory_resource;
DynamicArray<Complex> array(&memory_resource);

array.push_back({1, "Alice"});
array.push_back({2, "Bob"});

EXPECT_EQ(array.size(), 2);
EXPECT_EQ(array[0], (Complex{1, "Alice"}));
EXPECT_EQ(array[1], (Complex{2, "Bob"}));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}