#pragma once

#include <algorithm>
#include <array>
#include <experimental/optional>
#include <iostream>
#include <tuple>
#include <vector>

using std::array;
using std::begin;
using std::cout;
using std::end;
using std::endl;
using std::experimental::make_optional;
using std::experimental::optional;
using std::pow;
using std::sqrt;

template <typename a, int b> using Point = array<a, b>;
template <typename a, int b> using Cluster = std::vector<Point<a, b>>;

template <typename F> auto pointTransform(F f, auto a, auto b) {
  static_assert(std::tuple_size<decltype(a)>::value > 0,
                "array length must be greater than zero");
  static_assert(std::tuple_size<decltype(a)>::value ==
                    std::tuple_size<decltype(b)>::value,
                "points must be of the same dimensionality");
  Point<typename F::result_type, std::tuple_size<decltype(a)>::value> result;
  std::transform(begin(a), end(a), begin(b), begin(result), f);
  return result;
}

// todo - don't require that the are the same length
// expand the shorter one with zeroes
auto minus = [](auto a, auto b) {
  return pointTransform(std::minus<typename decltype(a)::value_type>(), a, b);
};
auto plus = [](auto a, auto b) {
  return pointTransform(std::plus<typename decltype(a)::value_type>(), a, b);
};
auto divide = [](auto a, auto b) {
  return pointTransform(std::divides<double>(), a, b);
};

double distance(auto a, auto b) {
  static_assert(std::tuple_size<decltype(a)>::value > 0,
                "array length must be greater than zero");
  static_assert(std::tuple_size<decltype(a)>::value ==
                    std::tuple_size<decltype(b)>::value,
                "array length must be greater than zero");
  auto f = [](double a, double b) { return a + pow(b, 2); };
  auto result = minus(a, b);
  auto sum = std::accumulate(begin(result), end(result), 0, f);
  return sqrt(sum);
}

template <unsigned long n> auto average(Cluster<auto, n> arr) {
  auto init = arr[0];
  auto point = std::accumulate(begin(arr) + 1, end(arr), init, plus);
  Point<int, n> denominator;
  denominator.fill(arr.size());
  return divide(point, denominator);
}

unsigned long findClosestCluster(auto point, auto clusterPoints) {
  std::vector<double> distances;
  distances.reserve(clusterPoints.size());
  std::transform(
      begin(clusterPoints), end(clusterPoints), std::back_inserter(distances),
      [&](auto clusterPoint) { return distance(point, clusterPoint); });
  auto maxDistanceIt = std::min_element(begin(distances), end(distances));
  return std::distance(begin(distances), maxDistanceIt);
}

template <long unsigned n>
auto partitionClusters(Cluster<auto, n> points,
                       std::vector<Point<auto, n>> clusterPoints) {
  std::vector<decltype(points)> clusters;
  clusters.resize(clusterPoints.size());
  for (auto p : points) {
    auto index = findClosestCluster(p, clusterPoints);
    clusters[index].push_back(p);
  }
  return clusters;
}

template <int n>
auto iterateKMeans(std::vector<Point<auto, n>> points,
                   std::vector<Point<auto, n>> clusterPoints) {
  auto clusters = partitionClusters(points, clusterPoints);
  decltype(clusterPoints) newClusterPoints;
  newClusterPoints.reserve(clusters.size());
  std::transform(begin(clusters), end(clusters),
                 std::back_inserter(newClusterPoints), average);
  return std::make_tuple(points, newClusterPoints);
}