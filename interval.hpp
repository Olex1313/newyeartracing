#pragma once

#include "rtweekend.hpp"

struct interval {
public:
  interval() : min(-kInfinity), max(+kInfinity) {}

  interval(double min, double max) : min(min), max(max) {}

  double size() const { return max - min; }

  bool contains(double x) const { return x >= min && x <= max; }

  bool surrounds(double x) const { return x > min && x < max; }

  double clamp(double x) const {
    if (x < min) {
      return min;
    }
    if (x > max) {
      return max;
    }
    return x;
  }

  static const interval empty;
  static const interval universe;

  double min;
  double max;
};

const interval interval::empty = interval(+kInfinity, -kInfinity);
const interval interval::universe = interval(-kInfinity, +kInfinity);
