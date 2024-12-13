#include <stdexcept>
#include <gtest/gtest.h>

#include "figures.h"

TEST(exceptionSuite, invalidArgCount) {
    EXPECT_THROW(Triangle<int>({{0, 0}}), std::invalid_argument);
}

TEST(compareSuite, baseCase) {
    Triangle<int> tr1{{0, 0}, {1, 1}, {2, 0}};
    Triangle<int> tr2{{0, 0}, {1, 1}, {2, 0}};
    ASSERT_TRUE(tr1 == tr2);
}

TEST(compareSuite, differentOrder) {
    Triangle<int> tr1{{0, 0}, {1, 1}, {2, 0}};
    Triangle<int> tr2{{0, 0}, {2, 0}, {1, 1}};
    ASSERT_TRUE(tr1 == tr2);
}

TEST(compareSuite, failOnDifferentPoints) {
    Triangle<int> tr1{{0, 1}, {1, 1}, {2, 0}};
    Triangle<int> tr2{{0, 0}, {2, 0}, {1, 1}};
    ASSERT_FALSE(tr1 == tr2);
}

TEST(areaCalculationSuite, baseCase) {
    double answer{4.5};
    Triangle<int> tr{ {0, 0}, {3, 0}, {0, 3} };
    ASSERT_EQ(tr.getArea(), answer);
}

TEST(centerCalculationSuite, baseCase) {
    Point<int> answer{};
    answer.x = answer.y = 1;
    Triangle<int> tr{ {0, 0}, {3, 0}, {0, 3} };
    ASSERT_EQ(tr.getCenter(), answer);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}