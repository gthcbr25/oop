#include <gtest/gtest.h>
#include "NOD.h"

TEST(BasicTest, BasicTest_0) {
    EXPECT_EQ(NOD(15, 5), 5);
}

TEST(BasicTest, BasicTest_1) {
    EXPECT_EQ(NOD(7, 0), 7);
}

TEST(BasicTest, BasicTest_2) {
    EXPECT_EQ(NOD(17, 13), 1);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}