#include <gtest/gtest.h>
#include <stdexcept>
#include "Hex.h"
#include <iostream>

TEST(InitTest, Start1) {
    Hex const first(6);
    Hex const second(6);
    ASSERT_TRUE(first.equal(second));
}
TEST(InitTest, Start2) {
    Hex const first(1);
    Hex const second(first);
    ASSERT_TRUE(first.equal(second));
}

TEST(CompareTest, Equal) {
    Hex const first(12);
    Hex const second(12);
    ASSERT_TRUE(first.equal(second));
 }

TEST(CompareTest, more) {
    Hex const first(14);
    Hex const second(12);
    ASSERT_TRUE(first.more(second));
}

TEST(CompareTest, less) {
    Hex const first(10);
    Hex const second(12);
    ASSERT_TRUE(first.less(second));
}

TEST(ArithmeticTest, summ) {
    Hex const first(5);
    Hex const second(5);
    Hex const res(10);
    ASSERT_TRUE(res.equal(first.summ(second)));
}

TEST(ArithmeticTest, subb) {
    Hex const first(10);
    Hex const second(5);
    Hex const res(5);
    ASSERT_TRUE(res.equal(first.subb(second)));
}

TEST(ArithmeticTest_Death, SubstractInvalid) {
    EXPECT_THROW({
        try {
            Hex tmp(3);
            Hex tmp2(5);
            tmp.subb(tmp2);
        }
        catch (const std::invalid_argument& e) {
            EXPECT_STREQ("Cannot subtract", e.what());
            throw;
        }
    }, std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}