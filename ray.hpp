#pragma once

#include "color.hpp"

class ray {
public:
  ray() {}

  ray(const point3 &origin, const vec3 &dir) : origin_(origin), dir_(dir) {}

  ray(const ray &other) : origin_(other.origin_), dir_(other.dir_) {}

  const point3 &origin() const { return origin_; }
  const vec3 &direction() const { return dir_; }

  point3 at(double t) const { return origin_ + t * dir_; }

private:
  point3 origin_;
  vec3 dir_;
};