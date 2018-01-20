#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

using std::array;
using std::vector;
using std::begin;
using std::end;
using std::transform;
using std::pow;
using std::accumulate;
using std::sqrt;

template <int n>
using Point = array<int, n>;

auto minus(auto a, auto b) {
    decltype(a) result;
    transform(begin(a), end(a), begin(b), begin(result), std::minus<int>());
    return result;
}

double distance(auto a, auto b) {
    auto f = [](double a, double b) { return a + pow(b, 2); };
    auto result = minus(a, b);
    auto sum = accumulate(begin(result), end(result), 0, f);
    return sqrt(sum);
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