#include "averageImages.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <experimental/filesystem>
#include <iostream>

// TEST(average, one) {
//   auto di = std::experimental::filesystem::directory_iterator(
//       "/mnt/c/Users/richie/Documents/github/k-means/resources/everything");
//   for (auto x : di) {
//     std::cout << x << std::endl;
//   }
// }

// TEST(average, one) {
//   std::vector<std::string> fileNames;
//   fileNames.emplace_back("/mnt/c/Users/richie/Documents/github/k-means/"
//                          "resources/everything/003/mnms-006.jpg");
//   fileNames.emplace_back("/mnt/c/Users/richie/Documents/github/k-means/"
//                          "resources/everything/003/mnms-007.jpg");
//   std::vector<std::vector<char>> pics;
//   std::transform(begin(fileNames), end(fileNames), std::back_inserter(pics),
//                  readImage);
//   std::vector<double> pic = averageImages(pics);

//   writeImage(pic, "439x292",
//              "/mnt/c/Users/richie/Documents/github/k-means/"
//              "resources/everything/003-67average.jpg",
//              8);
// }

TEST(channelDepth, one) {
  std::string fileName = "/mnt/c/Users/richie/Documents/github/k-means/"
                         "resources/everything/003/mnms-006.jpg";
  printDepth(fileName);
}