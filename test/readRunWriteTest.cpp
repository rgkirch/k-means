#include "readRunWrite.hpp"
#include "gmock/gmock.h"
#include "kmeans.hpp"
#include "readRunWrite.hpp"
#include "gtest/gtest.h"

using ::testing::DoubleEq;
using std::array;
using std::cout;
using std::endl;
using std::get;

TEST(copyImage, one) {
  auto genFileName = [](int num) {
    char buffer[8];
    snprintf(buffer, sizeof(buffer), "%03d", num);
    std::string baseFileName = "/tmp/k-means-test";
    baseFileName.append(buffer);
    baseFileName.append(".jpg");
    return baseFileName;
  };
  std::vector<char> data;
  unsigned width;
  unsigned height;
  std::string sourceFileName = "/mnt/c/Users/richie/Documents/github/k-means/"
                               "resources/mnms-tiny.jpg";
  std::tie(width, height, data) = readImage(sourceFileName);
  writeImage(data.data(), width, height, genFileName(0));

  std::vector<char> data2;
  for (int k = 0; k < 20; k++) {
    for (int i = 0; i < 20; i++) {
      std::tie(width, height, data2) = readImage(genFileName(k));
      writeImage(data2.data(), width, height, genFileName(k));
    }
    std::tie(width, height, data2) = readImage(genFileName(k));
    writeImage(data2.data(), width, height, genFileName(k + 1));
  }
  ASSERT_EQ(data, data2);
}

// TEST(copyImage, two) {
//   std::vector<char> data;
//   std::string geometry;
//   std::tie(data, geometry) =
//       readImage("/mnt/c/Users/richie/Documents/github/k-means/"
//                 "resources/mnms-tiny.jpg");
//   writeImage(data, geometry, "mnms-tiny-copy-test.jpg");
// }