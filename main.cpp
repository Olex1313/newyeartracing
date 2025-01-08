#include <cmath>
#include <iostream>
#include <memory>

#include "camera.hpp"
#include "hittable.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "rtweekend.hpp"
#include "sphere.hpp"

constexpr double kAspectRation = 16.0 / 9.0;
constexpr int kImageWidth = 400;

int main() {
  camera cam(kAspectRation, kImageWidth);
  hittableList objects;
  auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left = std::make_shared<metal>(color(0.8, 0.8, 0.8));
  auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2));

  objects.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0,
                                       material_ground));
  objects.add(
      std::make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
  objects.add(
      std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  objects.add(
      std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

  cam.render(objects);

  return 0;
}
