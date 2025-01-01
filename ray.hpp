#pragma once

#include "color.hpp"

class ray {
public:
  ray() {}

  ray(const point3 &origin, const vec3 &dir) : origin_(origin), dir_(dir) {}

  const point3 &origin() const { return origin_; }
  const vec3 &direction() const { return dir_; }

private:
  const point3 origin_;
  const vec3 dir_;
};