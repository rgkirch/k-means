#pragma once

#include <algorithm>
#include <array>
#include <experimental/optional>
#include <iostream>
#include <random>
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

template <long unsigned a> using Point = array<double, a>;
template <long unsigned a> using Cluster = std::vector<Point<a>>;

template <typename F, long unsigned n>
auto pointTransform(F f, Point<n> a, Point<n> b) {
  static_assert(std::tuple_size<decltype(a)>::value > 0,
                "array length must be greater than zero");
  static_assert(std::tuple_size<decltype(a)>::value ==
                    std::tuple_size<decltype(b)>::value,
                "points must be of the same dimensionality");
  Point<n> result;
  std::transform(begin(a), end(a), begin(b), begin(result), f);
  return result;
}

// todo - don't require that the are the same length
// expand the shorter one with zeroes
auto minus = [](auto a, auto b) {
  return pointTransform(std::minus<double>(), a, b);
};
auto plus = [](auto a, auto b) {
  return pointTransform(std::plus<double>(), a, b);
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
  auto sum = std::accumulate(begin(result), end(result), 0.0, f);
  return sqrt(sum);
}

template <unsigned long n> auto average(std::vector<Point<n>> arr) -> Point<n> {
  auto init = arr[0];
  auto point = std::accumulate(begin(arr) + 1, end(arr), init, plus);
  Point<n> denominator;
  denominator.fill(arr.size());
  return divide(point, denominator);
}

template <unsigned long n>
unsigned long findClosestCluster(Point<n> point,
                                 std::vector<Point<n>> clusterPoints) {
  std::vector<double> distances;
  distances.reserve(clusterPoints.size());
  std::transform(
      begin(clusterPoints), end(clusterPoints), std::back_inserter(distances),
      [&](Point<n> clusterPoint) { return distance(point, clusterPoint); });
  auto maxDistanceIt = std::min_element(begin(distances), end(distances));
  return std::distance(begin(distances), maxDistanceIt);
}

template <long unsigned n>
auto partitionClusters(std::vector<Point<n>> points,
                       std::vector<Point<n>> clusterPoints)
    -> std::vector<std::vector<Point<n>>> {
  std::vector<decltype(points)> clusters;
  clusters.resize(clusterPoints.size());
  for (auto p : points) {
    auto index = findClosestCluster(p, clusterPoints);
    clusters[index].push_back(p);
  }
  return clusters;
}

template <long unsigned n>
auto iterateKMeans(std::vector<Point<n>> points,
                   std::vector<Point<n>> clusterPoints)
    -> std::vector<Point<n>> {
  auto clusters = partitionClusters(points, clusterPoints);
  std::vector<Point<n>> newClusterPoints;
  newClusterPoints.reserve(clusters.size());
  auto avgFun = [](std::vector<Point<n>> c) { return average(c); };
  std::transform(begin(clusters), end(clusters),
                 std::back_inserter(newClusterPoints), avgFun);
  return newClusterPoints;
}

// range(0, points.size())
// shuffle
// walk through
// if in set then skip
template <long unsigned n>
auto initialClusterPoints(unsigned long k, std::vector<Point<n>> points) {
  std::vector<int> xs;
  xs.resize(points.size());
  std::iota(begin(xs), end(xs), 0);
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(xs.begin(), xs.end(), g);
  std::vector<Point<n>> seen;
  std::vector<Point<n>> clusterPoints;
  clusterPoints.reserve(k);
  for (auto x = begin(xs); x != end(xs) && clusterPoints.size() < k; x++) {
    auto p = begin(points) + *x;
    if (std::find(begin(seen), end(seen), *p) == end(seen)) {
      clusterPoints.push_back(*p);
      seen.push_back(*p);
    }
  }
  if (clusterPoints.size() < k)
    throw std::runtime_error("couldn't find k unique points");
  return clusterPoints;
}

template <long unsigned n>
auto runKMeans(unsigned long k, std::vector<Point<n>> points) {
  if (points.size() < k)
    throw std::logic_error("k must not be smaller than the number of points");
  auto intClusterPoints = initialClusterPoints(k, points);
  auto clusterPoints = iterateKMeans(points, intClusterPoints);
  auto newClusterPoints = iterateKMeans(points, clusterPoints);
  for (int i = 1; i > 0 && clusterPoints != newClusterPoints; i++) {
    std::swap(clusterPoints, newClusterPoints);
    newClusterPoints = iterateKMeans(points, clusterPoints);
  }
  return newClusterPoints;
}
