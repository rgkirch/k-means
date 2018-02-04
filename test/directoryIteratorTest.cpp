#include <experimental/filesystem>
#include <iostream>

int main() {
  auto di = std::experimental::filesystem::directory_iterator(
      "/mnt/c/Users/richie/Documents/github/k-means");
  for (auto x : di) {
    std::cout << x << std::endl;
  }
}