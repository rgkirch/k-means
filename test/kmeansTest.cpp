#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "kmeans.hpp"

using ::testing::DoubleEq;
using std::array;
using std::cout;
using std::endl;

TEST(minus, twoPoints)
{
    Point<int, 3> a{1, 3, 9};
    Point<int, 3> b{0, 4, 12};
    auto result = minus(a, b);
    Point<int, 3> expected{1, -1, -3};
    ASSERT_EQ(expected, result);
}

TEST(minus, fiveDSpace)
{
    Point<int, 5> a{1, 2, 3, 4, 5};
    Point<int, 5> b{5, 4, 3, 2, 1};
    auto result = minus(a, b);
    Point<int, 5> expected{-4, -2, 0, 2, 4};
    ASSERT_EQ(expected, result);
}

TEST(distance, one)
{
    Point<int, 1> a{0};
    Point<int, 1> b{0};
    auto result = distance(a, b);
    double expected{0};
    ASSERT_NEAR(expected, result, 0.01);
}

TEST(distance, two)
{
    Point<int, 1> a{1};
    Point<int, 1> b{1};
    auto result = distance(a, b);
    double expected{0};
    ASSERT_NEAR(expected, result, 0.01);
}

TEST(distance, three)
{
    Point<int, 5> a{4, 3, 2, 1, 0};
    Point<int, 5> b{-2, -1, 0, 1, 2};
    auto result = distance(a, b);
    auto expected{std::sqrt(60)};
    ASSERT_NEAR(expected, result, 0.01);
}

TEST(distance, four)
{
    Point<int, 2> a{-51, 37};
    Point<int, 2> b{86, -40};
    auto result = distance(a, b);
    double expected = 157.1559;
    ASSERT_NEAR(expected, result, 0.01);
}

TEST(distance, five)
{
    Point<int, 2> a{-52, 38};
    Point<int, 2> b{87, -41};
    auto result = distance(a, b);
    double expected = 159.8812;
    ASSERT_NEAR(expected, result, 0.01);
}

TEST(distance, six)
{
    Point<int, 2> a{100, 100};
    Point<int, 2> b{0, 0};
    auto result = distance(a, b);
    double expected = 141.421;
    ASSERT_NEAR(expected, result, 0.01);
}

TEST(averageOfCluster, one)
{
    array<Point<int, 2>, 4> arr{1, 1, 2, 2, 1, 2, 2, 1};
    auto avg = average(arr);
    ASSERT_NEAR(avg[0], 1.5, .01);
    ASSERT_NEAR(avg[1], 1.5, .01);
}