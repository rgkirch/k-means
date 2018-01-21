#include "kmeans.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::DoubleEq;
using std::array;
using std::cout;
using std::endl;
using std::get;

TEST(minus, twoPoints) {
  Point<int, 3> a{1, 3, 9};
  Point<int, 3> b{0, 4, 12};
  auto result = minus(a, b);
  Point<int, 3> expected{1, -1, -3};
  ASSERT_EQ(expected, result);
}

TEST(minus, fiveDSpace) {
  Point<int, 5> a{1, 2, 3, 4, 5};
  Point<int, 5> b{5, 4, 3, 2, 1};
  auto result = minus(a, b);
  Point<int, 5> expected{-4, -2, 0, 2, 4};
  ASSERT_EQ(expected, result);
}

TEST(distance, one) {
  Point<int, 1> a{0};
  Point<int, 1> b{0};
  auto result = distance(a, b);
  double expected{0};
  ASSERT_NEAR(expected, result, 0.01);
}

TEST(distance, two) {
  Point<int, 1> a{1};
  Point<int, 1> b{1};
  auto result = distance(a, b);
  double expected{0};
  ASSERT_NEAR(expected, result, 0.01);
}

TEST(distance, three) {
  Point<int, 5> a{4, 3, 2, 1, 0};
  Point<int, 5> b{-2, -1, 0, 1, 2};
  auto result = distance(a, b);
  auto expected{std::sqrt(60)};
  ASSERT_NEAR(expected, result, 0.01);
}

TEST(distance, four) {
  Point<int, 2> a{-51, 37};
  Point<int, 2> b{86, -40};
  auto result = distance(a, b);
  double expected = 157.1559;
  ASSERT_NEAR(expected, result, 0.01);
}

TEST(distance, five) {
  Point<int, 2> a{-52, 38};
  Point<int, 2> b{87, -41};
  auto result = distance(a, b);
  double expected = 159.8812;
  ASSERT_NEAR(expected, result, 0.01);
}

TEST(distance, six) {
  Point<int, 2> a{100, 100};
  Point<int, 2> b{0, 0};
  auto result = distance(a, b);
  double expected = 141.421;
  ASSERT_NEAR(expected, result, 0.01);
}

TEST(averageOfCluster, one) {
  Cluster<int, 2> arr{{1, 1}, {2, 2}, {1, 2}, {2, 1}};
  auto avg = average(arr);
  if (avg) {
    ASSERT_NEAR(get<0>(*avg), 1.5, .01);
    ASSERT_NEAR(get<1>(*avg), 1.5, .01);
  } else {
    FAIL();
  }
}

TEST(averageOfCluster, two) {
  Cluster<double, 2> arr{{1.1, 1.2}, {2.3, 2.4}, {1.5, 2.6}, {2.7, 1.8}};
  auto avg = average(arr);
  if (avg) {

    ASSERT_NEAR(get<0>(*avg), 7.6 / 4, .001);
    ASSERT_NEAR(get<1>(*avg), 8.0 / 4, .001);
  } else {
    FAIL();
  }
}

TEST(averageOfCluster, three) {
  Cluster<int, 2> arr{{0, 0}, {5, 0}, {0, 5}};
  auto avg = average(arr);
  if (avg) {

    ASSERT_NEAR(get<0>(*avg), (double)5 / 3, .001);
    ASSERT_NEAR(get<1>(*avg), (double)5 / 3, .001);
  } else {
    FAIL();
  }
}

TEST(averageOfCluster, four) {
  Cluster<int, 4> arr{{1, 2, 3, 3}, {0, 5, 5, 4}};
  auto avg = average(arr);
  if (avg) {
    ASSERT_NEAR(get<0>(*avg), (double)1 / 2, .001);
    ASSERT_NEAR(get<1>(*avg), (double)7 / 2, .001);
    ASSERT_NEAR(get<2>(*avg), (double)8 / 2, .001);
    ASSERT_NEAR(get<3>(*avg), (double)7 / 2, .001);
  } else {
    FAIL();
  }
}

TEST(averageOfCluster, five) {
  Cluster<int, 2> arr{{1, 2}};
  auto avg = average(arr);
  if (avg) {
    ASSERT_NEAR(get<0>(*avg), (double)1, .001);
    ASSERT_NEAR(get<1>(*avg), (double)2, .001);
  } else {
    FAIL();
  }
}

TEST(averageOfCluster, six) {
  Cluster<int, 1> arr{{0}};
  auto avg = average(arr);
  if (avg) {
    ASSERT_NEAR(get<0>(*avg), (double)0, .001);
  } else {
    FAIL();
  }
}

TEST(averageOfCluster, seven) {
  Cluster<int, 1> arr;
  auto avg = average(arr);
  if (avg) {
    FAIL();
  } else {
    SUCCEED();
  }
}

TEST(divide, one) {
  Point<int, 3> arr{0, 1, 2};
  Point<int, 3> denom;
  denom.fill(2);
  auto result = divide(arr, denom);
  Point<double, 3> expected{0, .5, 1};
  ASSERT_EQ(expected, result);
}

TEST(closestCluster, one) {
  Point<int, 2> data{0, 0};
  std::vector<Point<int, 2>> clusterPoints{{1, 0}, {4, 6}};
  auto result = closestCluster(data, clusterPoints);
  Point<int, 2> expected{1, 0};
  ASSERT_EQ(expected, result);
}

TEST(closestCluster, two) {
  Point<int, 2> data{4, 0};
  std::vector<Point<int, 2>> clusterPoints{{1, 0}, {4, 2}};
  auto result = closestCluster(data, clusterPoints);
  Point<int, 2> expected{4, 2};
  ASSERT_EQ(expected, result);
}

// TEST(generateCluster, one) {
//   Cluster<int, 2> data{{0, 0}, {5, 5}};
//   std::vector<Point<int, 2>> clusterPoints{{1, 0}, {4, 6}};
//   auto result = cluster(data, clusterPoints);
//   std::vector<Point<int, 2>> expected{{0, 0}, {5, 5}};
//   ASSERT_EQ(expected, result);
// }
// TEST(generateCluster, two) {
//   Cluster<int, 2> data{{1, 0}, {5, 5}};
//   std::vector<Point<int, 2>> clusterPoints{{1, 0}, {4, 6}};
//   auto result = cluster(data, clusterPoints);
//   std::vector<Point<int, 2>> expected{{1, 0}, {5, 5}};
//   ASSERT_EQ(expected, result);
// }