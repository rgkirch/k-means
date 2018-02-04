#pragma once
#include "readRunWrite.hpp"
#include <Magick++.h>
#include <iostream>
#include <string>
using namespace Magick;

using std::cout;
using std::endl;

std::vector<double> averageImages(std::vector<std::vector<auto>> pics) {
  std::vector<double> result;
  result.resize(pics[0].size());
  for (auto pic : pics) {
    for (int i = 0; i < pic.size(); i++) {
      result[i] += pic[i];
    }
  }
  std::transform(begin(result), end(result), begin(result),
                 [&](auto x) { return x / pics.size(); });
  return result;
}