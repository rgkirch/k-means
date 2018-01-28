#include <Magick++.h>
#include <iostream>
#include <string>
using namespace Magick;

using std::cout;
using std::endl;

void writeImage(std::vector<char> data, std::string geometry,
                std::string targetFileName) {
  InitializeMagick("");
  Image image(geometry, Color("white"));
  image.modifyImage();
  try {
    auto width = image.columns();
    auto height = image.rows();
    PixelPacket *pixels = image.getPixels(0, 0, width, height);
    // std::transform(pixels, pixels + width * height,
    // std::back_inserter(data));
    for (int i = 0; i < width * height; i++) {
      *pixels = ColorRGB(data[i * 3] / 255.0, data[i * 3 + 1] / 255.0,
                         data[i * 3 + 2] / 255.0);
      pixels++;
    }
    image.syncPixels();
    image.write(targetFileName.c_str());
  } catch (Exception &error_) {
    cout << "Caught exception: " << error_.what() << endl;
  }
}

std::vector<char> readImage(std::string sourceFileName) {
  InitializeMagick("");
  Image image;
  std::vector<char> data;
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
  } catch (Exception &error_) {
    cout << "Caught exception: " << error_.what() << endl;
  }
  return data;
}