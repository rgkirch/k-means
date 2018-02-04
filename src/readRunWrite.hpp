#pragma once
#include "kmeans.hpp"
#include <Magick++.h>
#include <iostream>
#include <string>
using namespace Magick;

using std::cout;
using std::endl;

void writeImage(std::vector<auto> data, std::string geometry,
                std::string targetFileName, unsigned channelDepth) {
  InitializeMagick("");
  Image image(geometry, Color("white"));
  image.modifyImage();
  try {
    auto width = image.columns();
    auto height = image.rows();
    PixelPacket *pixels = image.getPixels(0, 0, width, height);
    double dividend = std::pow(2, channelDepth);
    for (int i = 0; i < width * height; i++) {
      *pixels = ColorRGB(data[i * 3] / dividend, data[i * 3 + 1] / dividend,
                         data[i * 3 + 2] / dividend);
      pixels++;
    }
    image.syncPixels();
    image.write(targetFileName.c_str());
  } catch (Exception &error_) {
    cout << "Caught exception: " << error_.what() << endl;
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

std::tuple<std::vector<char>, std::string>
readImage(std::string sourceFileName) {
  InitializeMagick("");
  Image image;
  std::vector<char> data;
  std::string geometry;
  try {
    image.read(sourceFileName.c_str());
    auto width = image.columns();
    auto height = image.rows();
    PixelPacket *pixels = image.getPixels(0, 0, width, height);
    data.reserve(width * height);
    // std::transform(pixels, pixels + width * height,
    // std::back_inserter(data));
    for (int i = 0; i < width * height; i++) {
      data.push_back((char)(pixels->red / 65535.0 * 255));
      data.push_back((char)(pixels->green / 65535.0 * 255));
      data.push_back((char)(pixels->blue / 65535.0 * 255));
      pixels++;
    }
    geometry.append(std::to_string(width));
    geometry.append("x");
    geometry.append(std::to_string(height));
  } catch (Exception &error_) {
    cout << "Caught exception: " << error_.what() << endl;
  }
  return std::make_tuple(data, geometry);
}

void mainKMeans(int numColors, int fileNumber) {
  cout << "fileNumber: " << fileNumber << " numColors: " << numColors << endl;
  std::string sourceFileName = "/mnt/c/Users/richie/Documents/github/k-means/"
                               "resources/mnms-tiny.jpg";
  std::vector<char> sourceData;
  std::string geometry;
  std::tie(sourceData, geometry) = readImage(sourceFileName);
  std::vector<Point<3>> points;
  for (int i = 0; i < sourceData.size(); i += 3) {
    Point<3> pt{sourceData[i], sourceData[i + 1], sourceData[i + 2]};
    points.push_back(pt);
  }
  std::vector<Point<3>> clusterPoints = runKMeans(numColors, points);
  std::vector<char> targetData;
  targetData.reserve(sourceData.size());
  for (auto point : points) {
    auto index = findClosestCluster(point, clusterPoints);
    auto color = clusterPoints[index];
    targetData.push_back((char)(color[0]));
    targetData.push_back((char)(color[1]));
    targetData.push_back((char)(color[2]));
  }
  char numColorsBuffer[7];
  snprintf(numColorsBuffer, 7, "%03d", numColors);
  char fileNumberBuffer[7];
  snprintf(fileNumberBuffer, 7, "%03d", fileNumber);
  std::string targetFileName =
      "/mnt/c/Users/richie/Documents/github/k-means/resources/";
  targetFileName.append(numColorsBuffer);
  targetFileName.append("/mnms-");
  targetFileName.append(fileNumberBuffer);
  targetFileName.append(".jpg");
  writeImage(targetData, geometry, targetFileName, 8);
}