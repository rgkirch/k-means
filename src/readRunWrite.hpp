#pragma once
#include "kmeans.hpp"
#include <Magick++.h>
#include <iostream>
#include <string>
using namespace Magick;

using std::cout;
using std::endl;

void writeImage(char *data, unsigned width, unsigned height,
                std::string targetFileName) {
  InitializeMagick("");
  try {
    Image image(width, height, "RGB", CharPixel, (void *)data);
    image.write(targetFileName.c_str());
  } catch (Exception &error_) {
    cout << "Caught exception in write image: " << error_.what() << endl;
  }
}

void printDepth(std::string sourceFileName) {
  InitializeMagick("");
  Image image;
  try {
    image.read(sourceFileName.c_str());
    auto width = image.columns();
    auto height = image.rows();
  } catch (Exception &error_) {
    cout << "Caught exception: " << error_.what() << endl;
  }
  ChannelType channelType;
  std::cout << "channel depth " << image.channelDepth(channelType) << '\n';
  std::cout << "depth " << image.depth() << '\n';
  std::cout << "density " << image.density().width() << "x"
            << image.density().height() << '\n';
  std::cout << "size " << image.size().width() << "x" << image.size().height()
            << '\n';
  std::cout << "width height " << image.columns() << "x" << image.rows()
            << '\n';
  std::cout << "modulus depth " << image.modulusDepth() << std::endl;
}

std::tuple<unsigned, unsigned, std::vector<char>>
readImage2(std::string sourceFileName) {
  InitializeMagick("");
  std::vector<char> data;
  Image image(sourceFileName.c_str());
  auto width = image.columns();
  auto height = image.rows();
  try {
    data.resize(width * height);
    image.write(0, 0, width, height, "RGB", CharPixel, data.data());
  } catch (Exception &error_) {
    cout << "Caught exception in read image: " << error_.what() << endl;
  }
  return std::make_tuple(width, height, data);
}

std::tuple<unsigned, unsigned, std::vector<char>>
readImage3(std::string sourceFileName) {
  InitializeMagick("");
  Image image(sourceFileName.c_str());
  std::vector<char> data;
  auto width = image.columns();
  auto height = image.rows();
  try {
    data.reserve(width * height);
    for (int y = 0; y < width * height; y++) {
      for (int x = 0; x < width * height; x++) {
        auto c = image.pixelColor(x, y);
        data.push_back(ScaleQuantumToChar(c.redQuantum()));
        data.push_back(ScaleQuantumToChar(c.greenQuantum()));
        data.push_back(ScaleQuantumToChar(c.blueQuantum()));
      }
    }
  } catch (Exception &error_) {
    cout << "Caught exception in read image: " << error_.what() << endl;
  }
  return std::make_tuple(width, height, data);
}
std::tuple<unsigned, unsigned, std::vector<char>>
readImage(std::string sourceFileName) {
  InitializeMagick("");
  Image image;
  std::vector<char> data;
  image.read(sourceFileName.c_str());
  auto width = image.columns();
  auto height = image.rows();
  try {
    PixelPacket *pixels = image.getPixels(0, 0, width, height);
    data.reserve(width * height);
    for (int i = 0; i < width * height; i++) {
      data.push_back(ScaleQuantumToChar(pixels[i].red));
      data.push_back(ScaleQuantumToChar(pixels[i].green));
      data.push_back(ScaleQuantumToChar(pixels[i].blue));
    }
  } catch (Exception &error_) {
    cout << "Caught exception in read image: " << error_.what() << endl;
  }
  return std::make_tuple(width, height, data);
}

void runKMeansOnImage(int k, std::string sourceFileName,
                      std::string targetFileName) {
  std::vector<char> sourceData;
  unsigned width;
  unsigned height;
  std::tie(width, height, sourceData) = readImage(sourceFileName);
  std::vector<Point<3>> points;
  for (int i = 0; i < sourceData.size(); i += 3) {
    Point<3> pt{sourceData[i], sourceData[i + 1], sourceData[i + 2]};
    points.push_back(pt);
  }
  std::vector<Point<3>> clusterPoints = runKMeans(k, points);
  std::vector<char> targetData;
  targetData.reserve(sourceData.size());
  for (auto point : points) {
    auto index = findClosestCluster(point, clusterPoints);
    auto color = clusterPoints[index];
    targetData.push_back((char)(color[0]));
    targetData.push_back((char)(color[1]));
    targetData.push_back((char)(color[2]));
  }
  writeImage(targetData.data(), width, height, targetFileName);
}