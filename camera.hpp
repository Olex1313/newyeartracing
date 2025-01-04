#pragma once

#include "hittable.hpp"

class camera {
public:
  static const int kSamplesPerPixel = 100;
  static const int kMaxDepth = 50;
  static constexpr double kGammaFactor = 0.5;

public:
  camera(double aspectRatio, int imageWidth)
      : aspectRatio_(aspectRatio), pixelSamplesScale(1.0 / kSamplesPerPixel),
        imageWidth_(imageWidth) {

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
        color pixelColor(0, 0, 0);
        for (int sample = 0; sample < kSamplesPerPixel; sample++) {
          ray r = getRay(i, j);
          pixelColor += computeRayColor(r, kMaxDepth, world);
        }
        writeColor(std::cout, pixelSamplesScale * pixelColor);
      }
    }

    std::clog << "\rDone.					\n";
  }

private:
  color computeRayColor(const ray &r, int depth, const hittable &object) const {
    if (depth <= 0) {
      return color(0, 0, 0);
    }
    hitRecord hitRec;
    if (object.hit(r, interval(0.001, kInfinity), hitRec)) {
      auto direction = hitRec.normal + randomUnitVector();
      return kGammaFactor *
             computeRayColor(ray(hitRec.p, direction), depth - 1, object);
    }

    vec3 unitDirection = unitVector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }

  vec3 sampleSquare() const {
    return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
  }

  ray getRay(int i, int j) const {
    auto offset = sampleSquare();
    auto pixelSample = pixel00Location_ + ((i + offset.x()) * pixelDeltaU_) +
                       ((j + offset.y()) * pixelDeltaY_);

    auto rayOrigin = center_;
    auto rayDirection = pixelSample - rayOrigin;

    return ray(rayOrigin, rayDirection);
  }

private:
  double aspectRatio_;
  double pixelSamplesScale;
  int imageWidth_, imageHeight_;
  point3 center_, pixel00Location_;
  vec3 pixelDeltaU_, pixelDeltaY_;
};