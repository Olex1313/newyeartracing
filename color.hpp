#pragma once

#include "vec3.hpp"

using color = vec3;

void writeColor(std::ostream &out, const color &pixelColor) {
  auto r = pixelColor.x();
  auto g = pixelColor.y();
  auto b = pixelColor.z();

  auto rbyte = static_cast<int>(255.999 * r);
  auto gbyte = static_cast<int>(255.999 * g);
  auto bbyte = static_cast<int>(255.999 * b);

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
