#pragma once

#include "hittable.hpp"

class camera {
public:
  camera(double aspectRatio, int imageWidth)
      : aspectRatio_(aspectRatio), imageWidth_(imageWidth) {

    imageHeight_ = static_cast<int>(imageWidth_ / aspectRatio_);
    imageHeight_ = imageHeight_ < 1 ? 1 : imageHeight_;

    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth =
        viewportHeight * (static_cast<double>(imageWidth_) / imageHeight_);

    center_ = point3(0, 0, 0);
    auto viewportU = vec3(viewportWidth, 0, 0);
    auto viewportY = vec3(0, -viewportHeight, 0);

    pixelDeltaU_ = viewportU / imageWidth_;
    pixelDeltaY_ = viewportY / imageHeight_;

    auto viewportUpperLeft =
        center_ - vec3(0, 0, focalLength) - viewportU / 2 - viewportY / 2;

    pixel00Location_ = viewportUpperLeft + 0.5 * (pixelDeltaU_ + pixelDeltaY_);
  }

  void render(const hittable &world) {
    std::cout << "P3\n" << imageWidth_ << ' ' << imageHeight_ << "\n255\n";

    for (int j = 0; j < imageHeight_; j++) {
      std::clog << "\rScanlines remaining: " << imageHeight_ - j << ' '
                << std::flush;
      for (int i = 0; i < imageWidth_; i++) {
        auto pixelCenter =
            pixel00Location_ + (i * pixelDeltaU_) + (j * pixelDeltaY_);
        auto rayDirection = pixelCenter - center_;

        ray r(center_, rayDirection);
        auto pixelColor = computeRayColor(r, world);
        writeColor(std::cout, pixelColor);
      }
    }

    std::clog << "\rDone.					\n";
  }

private:
  color computeRayColor(const ray &r, const hittable &object) const {
    hitRecord hitRec;
    if (object.hit(r, interval(0, kInfinity), hitRec)) {
      return 0.5 * (hitRec.normal + color(1, 1, 1));
    }

    vec3 unitDirection = unitVector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }

private:
  double aspectRatio_;
  int imageWidth_, imageHeight_;
  point3 center_, pixel00Location_;
  vec3 pixelDeltaU_, pixelDeltaY_;
};