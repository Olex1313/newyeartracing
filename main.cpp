#include <cmath>
#include <iostream>

#include "camera.hpp"
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
  camera cam(kAspectRation, kImageWidth);

  hittableList objects;
  objects.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
  objects.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

  cam.render(objects);

  return 0;
}
