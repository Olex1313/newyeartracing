#pragma once

#include <limits>

const double kInfinity = std::numeric_limits<double>::infinity();
const double kPi = 3.1415926535897932385;

inline double degreesToRadius(double degrees) { return degrees * kPi / 180.0; }
