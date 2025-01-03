#include <cmath>
#include <iostream>

#include "hittable.hpp"
#include "ray.hpp"
#include "rtweekend.hpp"
#include "sphere.hpp"

constexpr double kAspectRation = 16.0 / 9.0;
constexpr int kImageWidth = 400;

color computeRayColor(const ray &r, const hittable &object) {
  hitRecord hitRec;
  if (object.hit(r, interval(0, kInfinity), hitRec)) {
    return 0.5 * (hitRec.normal + color(1, 1, 1));
  }

  vec3 unitDirection = unitVector(r.direction());
  auto a = 0.5 * (unitDirection.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
  int imageWidth = kImageWidth;
  int imageHeight = static_cast<int>(imageWidth / kAspectRation);
  imageHeight = imageHeight < 1 ? 1 : imageHeight;

  // World

  hittableList objects;
  objects.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
  objects.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

  // Setup camera
  auto focalLength = 1.0;
  auto viewportHeight = 2.0;
  auto viewportWidth =
      viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

  auto cameraCenter = point3(0, 0, 0);
  auto viewportU = vec3(viewportWidth, 0, 0);
  auto viewportY = vec3(0, -viewportHeight, 0);

  auto pixelDeltaU = viewportU / imageWidth;
  auto pixelDeltaY = viewportY / imageHeight;

  auto viewportUpperLeft =
      cameraCenter - vec3(0, 0, focalLength) - viewportU / 2 - viewportY / 2;
  auto pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaY);

  // Render
  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

  for (int j = 0; j < imageHeight; j++) {
    std::clog << "\rScanlines remaining: " << imageHeight - j << ' '
              << std::flush;
    for (int i = 0; i < imageWidth; i++) {
      auto pixelCenter =
          pixel00Location + (i * pixelDeltaU) + (j * pixelDeltaY);
      auto rayDirection = pixelCenter - cameraCenter;

      ray r(cameraCenter, rayDirection);
      auto pixelColor = computeRayColor(r, objects);
      writeColor(std::cout, pixelColor);
    }
  }

  std::clog << "\rDone.					\n";

  return 0;
}
