#include <iostream>

#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

constexpr double kAspectRation = 16.0 / 9.0;
constexpr int kImageWidth = 400;

int main() {
  int imageWidth = kImageWidth;
  int imageHeight = static_cast<int>(imageHeight / kAspectRation);
  imageHeight = imageHeight < 1 ? 1 : imageHeight;

  auto viewportHeight = 2.0;
  auto viewportWidth =
      viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

  for (int j = 0; j < imageHeight; j++) {
    std::clog << "\rScanlines remaining: " << imageHeight - j << ' '
              << std::flush;
    for (int i = 0; i < imageWidth; i++) {
      auto pixel = color(static_cast<double>(i) / (imageWidth - 1),
                         static_cast<double>(j) / (imageHeight - 1), 0);
      writeColor(std::cout, pixel);
    }
  }

  std::clog << "\rDone.					\n";

  return 0;
}
