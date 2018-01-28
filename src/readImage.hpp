#include <Magick++.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace Magick;

using std::cout;
using std::endl;

int readImage() {
  InitializeMagick("");
  Image image;
  try {
    image.read("/mnt/c/Users/richie/Documents/github/k-means/"
               "resources/mnms.jpg");
    // image.modifyImage();
    Pixels view(image);
    auto width = image.columns();
    auto height = image.rows();
    PixelPacket *pixels = view.get(0, 0, width, height);
    int x = 0;
    for (int i = 0; i < width * height; ++i) {
      *pixels++ =
          ColorRGB(pixels->red + x, pixels->green + x, pixels->blue + x);
    }

    image.write("/mnt/c/Users/richie/Documents/github/k-means/"
                "resources/plus.jpg");
  } catch (Exception &error_) {
    cout << "Caught exception: " << error_.what() << endl;
    return 1;
  }
  return 0;
}