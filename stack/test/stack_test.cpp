#include <hc/stack.hpp>

#include <gtest/gtest.h>

TEST(Stack, Create) {
    hc::Stack<int> s;
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.capacity(), 2);
    SUCCEED();
}

TEST(Stack, Push) {
    hc::Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.top(), 3);
    SUCCEED();
}

TEST(Stack, Pop) {
    hc::Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
    s.pop();
    EXPECT_THROW(s.pop(), std::out_of_range);
    SUCCEED();
}
