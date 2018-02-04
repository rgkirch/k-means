#include "gmock/gmock.h"
#include "kmeans.hpp"
#include "readImage.hpp"
#include "readRunWrite.hpp"
#include "gtest/gtest.h"

using ::testing::DoubleEq;
using std::array;
using std::cout;
using std::endl;
using std::get;

TEST(copyImage, one) {
  writeImage(readImage("/mnt/c/Users/richie/Documents/github/k-means/"
                       "resources/mnms-tiny.jpg"),
             "439x292",
             "/mnt/c/Users/richie/Documents/github/k-means/resources/copy.jpg");
}