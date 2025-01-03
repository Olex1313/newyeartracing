#include <cmath>
#include <iostream>

#include "camera.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "rtweekend.hpp"
#include "sphere.hpp"

constexpr double kAspectRation = 16.0 / 9.0;
constexpr int kImageWidth = 400;

int main() {
  camera cam(kAspectRation, kImageWidth);

  hittableList objects;
  objects.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
  objects.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

  cam.render(objects);

  return 0;
}
