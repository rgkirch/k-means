#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

using std::array;
using std::vector;

template <int n>
using Point = array<int, n>;

template <int n>
auto minus(auto a, auto b) {
    Point<n> result;
    result.reserve(a.size());
    std::transform(a.begin(), a.end(), b.begin(), result.begin(), std::minus<int>());
    return result;
}

// auto f(auto point, auto cluster, auto diff) {

// }

// auto distance(auto a, auto b) {
//     auto result = minus(a, b);
//     return 0;
// }

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