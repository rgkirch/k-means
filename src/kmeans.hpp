#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

using std::accumulate;
using std::array;
using std::begin;
using std::end;
using std::pow;
using std::sqrt;
using std::transform;
using std::vector;

template <typename a, int b>
using Point = array<a, b>;

auto minus(auto a, auto b)
{
    decltype(a) result;
    transform(begin(a), end(a), begin(b), begin(result), std::minus<int>());
    return result;
}

auto plus(auto a, auto b)
{
    decltype(a) result;
    transform(begin(a), end(a), begin(b), begin(result), std::plus<int>());
    return result;
}

double distance(auto a, auto b)
{
    auto f = [](double a, double b) { return a + pow(b, 2); };
    auto result = minus(a, b);
    auto sum = accumulate(begin(result), end(result), 0, f);
    return sqrt(sum);
}

template <unsigned long n, unsigned long x>
auto average(array<Point<auto, n>, x> arr)
{
    auto init = arr[0];
    auto divide = [=](auto a) -> double { return (double)a / arr.size(); };
    auto p = [](auto a, auto b) { return plus(a, b); };
    auto acc = accumulate(begin(arr) + 1, end(arr), init, p);
    Point<double, n> result;
    transform(begin(acc), end(acc), begin(result), divide);
    return result;
}

// auto closestCluster(auto point, auto clusters) {
//     for(auto c : clusters) {

//     }
// }

// template <int n>
// auto kMean(vector<Point<n>> points, vector<Point<n>> clusters) {
//     vector<Point<n>> clusterDiffs;
//     clusterDiffs.resize(clusters.size());
//     // clusterDiffs.reserve(clusters.size());
//     // for(int i = 0; i < clusters.size(); i++) {
//     //     clusterDiffs.emplace_back();
//     // }
//     // std::fill(clusterDiffs.begin(), clusterdiffs.end(), 0);
//     for(auto point : points) {
//         for(auto cluster : clusters) {
//             f(point, cluster, clusterDiffs[]);
//         }
//     }
// }