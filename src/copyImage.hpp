#include <Magick++.h>
#include <iostream>
#include <string>
using namespace Magick;

using std::cout;
using std::endl;

int copyImage() {
  InitializeMagick("");
  Image image;
  try {
    image.read("/mnt/c/Users/richie/Documents/github/k-means/"
               "resources/mnms.jpg");
    image.modifyImage();
    auto width = image.columns();
    auto height = image.rows();
    PixelPacket *pixels = image.getPixels(0, 0, width, height);

    double x = 65535; // unpleasant
    for (int i = 0; i < width * height; ++i) {
      *pixels = ColorRGB(pixels->red / x, pixels->green / x,
                         pixels->blue / x); // unpleasant
      pixels++;
    }

    image.syncPixels();
    image.write("/mnt/c/Users/richie/Documents/github/k-means/"
                "resources/copy.jpg");
  } catch (Exception &error_) {
    cout << "Caught exception: " << error_.what() << endl;
    return 1;
  }
  return 0;
}