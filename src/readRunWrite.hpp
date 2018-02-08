#pragma once
#include "kmeans.hpp"
#include <Magick++.h>
#include <iostream>
#include <string>
using namespace Magick;

using std::cout;
using std::endl;

void writeImage(std::vector<char> data, std::string geometry,
                std::string targetFileName) {
  InitializeMagick("");
  // std::cout << Blob blob((void *)&data[0], data.size());
  // Image image(geometry, "white");
  try {
    Geometry g(geometry);
    // Image image(blob, geometry, "RGB");
    Image image(g.width(), g.height(), "RGB", CharPixel, (void *)&data[0]);
    // image.modifyImage();
    // auto width = image.columns();
    // auto height = image.rows();
    // PixelPacket *pixels = image.getPixels(0, 0, width, height);
    // std::cout << "write " << (int)data[0] << std::endl;
    // std::cout << "write scaled " << ScaleCharToQuantum(data[0]) << std::endl;
    // for (int i = 0; i < width * height; i++) {
    //   // *pixels = ColorRGB(data[i * 3] / 256.0, data[i * 3 + 1] / 256.0,
    //   //  data[i * 3 + 2] / 256.0);
    //   pixels->red = ScaleCharToQuantum(data[i * 3]);
    //   pixels->green = ScaleCharToQuantum(data[i * 3 + 1]);
    //   pixels->blue = ScaleCharToQuantum(data[i * 3 + 2]);
    //   pixels++;
    // }
    // image.syncPixels();
    image.write(targetFileName.c_str());
  } catch (Exception &error_) {
    cout << "Caught exception in write image: " << error_.what() << endl;
    abort();
    exit(1);
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
readImage2(std::string sourceFileName) {
  InitializeMagick("");
  // Blob blob;
  Image image(sourceFileName.c_str());
  // image.magick("JPEG");
  // image.write(&blob);
  // return blob.data();
  std::string geometry;
  std::vector<char> data;
  try {
    auto width = image.columns();
    auto height = image.rows();
    char *buffer = (char *)malloc(width * height);
    image.write(0, 0, width, height, "RGB", CharPixel, buffer);
    for (int i = 0; i < width * height; i++) {
      data.push_back(buffer[i]);
    }
    delete buffer;
    //   image.read(sourceFileName.c_str());
    //   PixelPacket *pixels = image.getPixels(0, 0, width, height);
    //   std::cout << "read  " << pixels->red << std::endl;
    //   std::cout << "read scaled  " << (int)ScaleQuantumToChar(pixels->red)
    //             << std::endl;
    //   data.reserve(width * height);
    //   // std::transform(pixels, pixels + width * height,
    //   // std::back_inserter(data));
    //   // std::cout << "depth " << image.depth() << std::endl;
    //   for (int i = 0; i < width * height; i++) {
    //     data.push_back(ScaleQuantumToChar(pixels[i].red));
    //     data.push_back(ScaleQuantumToChar(pixels[i].green));
    //     data.push_back(ScaleQuantumToChar(pixels[i].blue));
    //   }
    geometry.append(std::to_string(width));
    geometry.append("x");
    geometry.append(std::to_string(height));
  } catch (Exception &error_) {
    cout << "Caught exception in read image: " << error_.what() << endl;
  }
  return std::make_tuple(data, geometry);
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
    std::cout << "read  " << pixels->red << std::endl;
    std::cout << "read scaled  " << (int)ScaleQuantumToChar(pixels->red)
              << std::endl;
    data.reserve(width * height);
    // std::transform(pixels, pixels + width * height,
    // std::back_inserter(data));
    // std::cout << "depth " << image.depth() << std::endl;
    for (int i = 0; i < width * height; i++) {
      data.push_back(ScaleQuantumToChar(pixels[i].red));
      data.push_back(ScaleQuantumToChar(pixels[i].green));
      data.push_back(ScaleQuantumToChar(pixels[i].blue));
    }
    geometry.append(std::to_string(width));
    geometry.append("x");
    geometry.append(std::to_string(height));
  } catch (Exception &error_) {
    cout << "Caught exception in read image: " << error_.what() << endl;
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
  writeImage(targetData, geometry, targetFileName);
}