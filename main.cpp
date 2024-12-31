#include "iostream"

int main() {
  int imageWidth = 256;
  int imageHeight = 256;

  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

  for (int j = 0; j < imageHeight; j++) {
    for (int i = 0; i < imageWidth; i++) {
      std::clog << "\rScanlines remaining: " << imageHeight - i << ' ' << std::flush;
      auto r = static_cast<double>(i) / (imageWidth - 1);
      auto g = static_cast<double>(j) / (imageHeight - 1);
      auto b = 0;

      int ir = static_cast<int>(255.999 * r);
      int ig = static_cast<int>(255.999 * g);
      int ib = static_cast<int>(255.999 * b);

      std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }

  std::clog << "\rDone.					\n";

  return 0;
}
