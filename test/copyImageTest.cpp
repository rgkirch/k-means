
#include "copyImage.hpp"
#include "gmock/gmock.h"
#include "kmeans.hpp"
#include "gtest/gtest.h"

using ::testing::DoubleEq;
using std::array;
using std::cout;
using std::endl;
using std::get;

TEST(copyImage, one) { copyImage(); }