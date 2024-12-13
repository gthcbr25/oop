#include <stdexcept>
#include <gtest/gtest.h>

#include "triangle.h"

TEST(exceptionSuite, invalidArgCount) {
    EXPECT_THROW(Triangle({{0, 0}}), std::invalid_argument);
}

TEST(compareSuite, baseCase) {
    Triangle tr1{{0, 0}, {1, 1}, {2, 0}};
    Triangle tr2{{0, 0}, {1, 1}, {2, 0}};
    ASSERT_TRUE(tr1 == tr2);
}

TEST(compareSuite, differentOrder) {
    Triangle tr1{{0, 0}, {1, 1}, {2, 0}};
    Triangle tr2{{0, 0}, {2, 0}, {1, 1}};
    ASSERT_TRUE(tr1 == tr2);
}

TEST(compareSuite, failOnDifferentPoints) {
    Triangle tr1{{0, 1}, {1, 1}, {2, 0}};
    Triangle tr2{{0, 0}, {2, 0}, {1, 1}};
    ASSERT_FALSE(tr1 == tr2);
}

TEST(areaCalculationSuite, baseCase) {
    double answer{4.5};
    Triangle tr{ {0, 0}, {3, 0}, {0, 3} };
    ASSERT_EQ(tr.getArea(), answer);
}

TEST(centerCalculationSuite, baseCase) {
    Point answer{};
    answer.x = answer.y = 1;
    Triangle tr{ {0, 0}, {3, 0}, {0, 3} };
    ASSERT_EQ(tr.getCenter(), answer);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}