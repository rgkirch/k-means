#include "gmock/gmock.h"
#include "kmeans.hpp"
#include "readRunWrite.hpp"
#include "gtest/gtest.h"
using ::testing::DoubleEq;
using std::array;
using std::cout;
using std::endl;
using std::get;

// TEST(dataToPoints, one) {
//   for (int numColors = 22; numColors < 32; numColors++) {
// #pragma omp parallel for
//     for (int fileNumber = 0; fileNumber < 32; fileNumber++) {
//       mainKMeans(numColors, fileNumber);
//     }
//   }
// }

TEST(runKMeansOnPicture, red) {
  InitializeMagick("");
  Geometry geometry("100x100");
  Image imageBefore(geometry, "red");
  imageBefore.write("/tmp/redImage.png");
  runKMeansOnImage(1, "/tmp/redImage.png", "/tmp/redImageOut.png");
  Image imageAfter("/tmp/redImageOut.png");
  for (int y = 0; y < geometry.height(); y++) {
    for (int x = 0; x < geometry.width(); x++) {
      auto c = imageAfter.pixelColor(x, y);
      ASSERT_EQ((unsigned char)255, ScaleQuantumToChar(c.redQuantum()));
      ASSERT_EQ((unsigned char)0, ScaleQuantumToChar(c.greenQuantum()));
      ASSERT_EQ((unsigned char)0, ScaleQuantumToChar(c.blueQuantum()));
    }
  }
}

TEST(runKMeansOnPicture, green) {
  InitializeMagick("");
  Geometry geometry("100x100");
  Image imageBefore(geometry, "green");
  imageBefore.write("/tmp/greenImage.png");
  runKMeansOnImage(1, "/tmp/greenImage.png", "/tmp/greenImageOut.png");
  Image imageAfter("/tmp/greenImageOut.png");
  for (int y = 0; y < geometry.height(); y++) {
    for (int x = 0; x < geometry.width(); x++) {
      auto c = imageAfter.pixelColor(x, y);
      ASSERT_EQ((unsigned char)0, ScaleQuantumToChar(c.redQuantum()));
      ASSERT_EQ((unsigned char)128, ScaleQuantumToChar(c.greenQuantum()));
      ASSERT_EQ((unsigned char)0, ScaleQuantumToChar(c.blueQuantum()));
    }
  }
}

TEST(runKMeansOnPicture, blue) {
  InitializeMagick("");
  Geometry geometry("100x100");
  Image imageBefore(geometry, "blue");
  imageBefore.write("/tmp/blueImage.png");
  runKMeansOnImage(1, "/tmp/blueImage.png", "/tmp/blueImageOut.png");
  Image imageAfter("/tmp/blueImageOut.png");
  for (int y = 0; y < geometry.height(); y++) {
    for (int x = 0; x < geometry.width(); x++) {
      auto c = imageAfter.pixelColor(x, y);
      ASSERT_EQ((unsigned char)0, ScaleQuantumToChar(c.redQuantum()));
      ASSERT_EQ((unsigned char)0, ScaleQuantumToChar(c.greenQuantum()));
      ASSERT_EQ((unsigned char)255, ScaleQuantumToChar(c.blueQuantum()));
    }
  }
}

// TEST(runKMeansOnData, randomPrimary) {
//   InitializeMagick("");
//   std::vector<unsigned char> data;
//   unsigned width = 100;
//   unsigned height = 100;
//   auto wxh = width * height;
//   data.reserve(wxh * 3);
//   std::srand(0);
//   for (int i = 0; i < wxh; i += 3) {
//     switch (std::rand() % 3) {
//     case 0:
//       data.push_back(255);
//       data.push_back(0);
//       data.push_back(0);
//       break;
//     case 1:
//       data.push_back(0);
//       data.push_back(128);
//       data.push_back(0);
//       break;
//     case 2:
//       data.push_back(0);
//       data.push_back(0);
//       data.push_back(255);
//       break;
//     }
//   }
//   imageBefore.write("/tmp/randomPrimary.png");
//   runKMeansOnImage(3, "/tmp/randomPrimary.png", "/tmp/randomPrimaryOut.png");
//   Image imageAfter("/tmp/randomPrimaryOut.png");
//   for (int y = 0; y < height; y++) {
//     for (int x = 0; x < width; x++) {
//       auto c = imageAfter.pixelColor(x, y);
//       ASSERT_EQ(data[x * y], ScaleQuantumToChar(c.redQuantum()));
//       ASSERT_EQ(data[x * y + 1], ScaleQuantumToChar(c.greenQuantum()));
//       ASSERT_EQ(data[x * y + 2], ScaleQuantumToChar(c.blueQuantum()));
//     }
//   }
// }

TEST(runKMeansOnPicture, randomPrimary) {
  InitializeMagick("");
  Geometry geometry("100x100");
  std::vector<unsigned char> data;
  auto width = geometry.width();
  auto height = geometry.height();
  auto wxh = width * height;
  data.reserve(wxh * 3);
  std::srand(0);
  for (int i = 0; i < wxh * 3; i += 3) {
    switch (std::rand() % 3) {
    case 0:
      data.push_back(255);
      data.push_back(0);
      data.push_back(0);
      break;
    case 1:
      data.push_back(0);
      data.push_back(128);
      data.push_back(0);
      break;
    case 2:
      data.push_back(0);
      data.push_back(0);
      data.push_back(255);
      break;
    }
  }
  Image imageBefore(width, height, "RGB", CharPixel, (void *)data.data());
  imageBefore.write("/tmp/randomPrimary.png");
  runKMeansOnImage(3, "/tmp/randomPrimary.png", "/tmp/randomPrimaryOut.png");
  Image imageAfter("/tmp/randomPrimaryOut.png");
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      auto c = imageAfter.pixelColor(x, y);
      ASSERT_EQ(data[(x + y * width) * 3 + 0],
                ScaleQuantumToChar(c.redQuantum()));
      ASSERT_EQ(data[(x + y * width) * 3 + 1],
                ScaleQuantumToChar(c.greenQuantum()));
      ASSERT_EQ(data[(x + y * width) * 3 + 2],
                ScaleQuantumToChar(c.blueQuantum()));
    }
  }
}

TEST(runKMeansOnPicture, withVariation) {
  InitializeMagick("");
  Geometry geometry("100x100");
  std::vector<unsigned char> data;
  auto width = geometry.width();
  auto height = geometry.height();
  auto wxh = width * height;
  data.reserve(wxh * 3);
  std::srand(0);
  unsigned darkSum = 0;
  unsigned greenSum = 0;
  unsigned blueSum = 0;
  for (int i = 0; i < wxh * 3; i += 3) {
    unsigned char r;
    switch (std::rand() % 3) {
    case 0:
      r = std::rand() % 256;
      data.push_back(r);
      data.push_back(50);
      data.push_back(50);
      darkSum += r;
      break;
    case 1:
      r = std::rand() % 256;
      data.push_back(r);
      data.push_back(200);
      data.push_back(150);
      greenSum += r;
      break;
    case 2:
      r = std::rand() % 256;
      data.push_back(r);
      data.push_back(50);
      data.push_back(200);
      blueSum += r;
      break;
    }
  }
  unsigned char dark = darkSum / wxh;
  unsigned char green = greenSum / wxh;
  unsigned char blue = blueSum / wxh;
  Image imageBefore(width, height, "RGB", CharPixel, (void *)data.data());
  imageBefore.write("/tmp/randomVariation.png");
  runKMeansOnImage(3, "/tmp/randomVariation.png",
                   "/tmp/randomVariationOut.png");
  Image imageAfter("/tmp/randomVariationOut.png");
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      auto c = imageAfter.pixelColor(x, y);
      auto redQuantum = ScaleQuantumToChar(c.redQuantum());
      auto greenQuantum = ScaleQuantumToChar(c.greenQuantum());
      auto blueQuantum = ScaleQuantumToChar(c.blueQuantum());
      if (greenQuantum == 50 && blueQuantum == 50) {
        ASSERT_EQ(dark, redQuantum);
      } else if (greenQuantum == 200 && blueQuantum == 150) {
        ASSERT_EQ(green, redQuantum);
      } else if (greenQuantum == 50 && blueQuantum == 200) {
        ASSERT_EQ(blue, redQuantum);
      } else {
        std::cout << "redQuantum " << (int)redQuantum << " greenQuantum "
                  << (int)greenQuantum << " blueQuantum " << (int)blueQuantum
                  << " dark " << (int)dark << " green " << (int)green
                  << " blue " << (int)blue << std::endl;
        FAIL();
      }
    }
  }
}
