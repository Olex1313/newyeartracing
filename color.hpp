#pragma once

#include "interval.hpp"
#include "vec3.hpp"

using color = vec3;

void writeColor(std::ostream &out, const color &pixelColor) {
  auto r = pixelColor.x();
  auto g = pixelColor.y();
  auto b = pixelColor.z();

  static const interval intensivity(0.000, 0.999);
  auto rbyte = static_cast<int>(256 * intensivity.clamp(r));
  auto gbyte = static_cast<int>(256 * intensivity.clamp(g));
  auto bbyte = static_cast<int>(256 * intensivity.clamp(b));

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
