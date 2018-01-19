#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

using std::array;
using std::vector;

template <int n>
using Point = array<int, n>;

auto minus(auto a, auto b) {
    decltype(a) result;
    std::transform(a.begin(), a.end(), b.begin(), result.begin(), std::minus<int>());
    return result;
}

// auto f(auto point, auto cluster, auto diff) {

// }

double distance(auto a, auto b) {
    struct SumSquares {
        int operator()(int n) {
            sum += std::pow(n, 2);
        }
        double sum = 0.0;
    };
    auto result = minus(a, b);
    auto sum = std::for_each(result.begin(), result.end(), SumSquares()).sum;
    return std::sqrt(sum);
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