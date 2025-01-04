#pragma once

#include <limits>
#include <random>

const double kInfinity = std::numeric_limits<double>::infinity();
const double kPi = 3.1415926535897932385;

inline double degreesToRadius(double degrees) { return degrees * kPi / 180.0; }

inline double randomDouble(double min = 0.0, double max = 1.0) {
  static std::uniform_real_distribution<double> distribution(min, max);
  static std::mt19937 generator;
  return distribution(generator);
}
