#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "kmeans.hpp"

TEST(minus, twoPoints) {
    Point<3> a {1,3,9};
    Point<3> b {0,4,12};
    auto result = minus(a,b);
    Point<3> expected {1, -1, -3};
    ASSERT_EQ(expected, result);
}

TEST(minus, fiveDSpace) {
    Point<5> a {1,2,3,4,5};
    Point<5> b {5,4,3,2,1};
    auto result = minus(a,b);
    Point<5> expected {-4,-2,0,2,4};
    ASSERT_EQ(expected, result);
}

TEST(distance, one) {
    Point<1> a {0};
    Point<1> b {0};
    auto result = distance(a,b);
    auto expected {0};
    ASSERT_EQ(expected, result);
}

TEST(distance, two) {
    Point<1> a {1};
    Point<1> b {1};
    auto result = distance(a,b);
    auto expected {0};
    ASSERT_EQ(expected, result);
}

TEST(distance, three) {
    Point<5> a {4,3,2,1,0};
    Point<5> b {-2,-1,0,1,2};
    auto result = distance(a,b);
    auto expected {std::sqrt(60)};
    ASSERT_EQ(expected, result);
}

TEST(distance, four) {
    Point<2> a {-52, 38};
    Point<2> b {87, -41};
    auto result = distance(a,b);
    double expected = 1598.81;
    ASSERT_EQ(expected, result);
}
