#include <hc/vector.hpp>

#include <gtest/gtest.h>

TEST(Vector, Create) {
    hc::Vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 2);
    SUCCEED();
}

TEST(Vector, PushBack) {
    hc::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    EXPECT_EQ(v.size(), 3);
    SUCCEED();
}
