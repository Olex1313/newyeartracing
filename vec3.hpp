#pragma once

#include <array>
#include <iostream>

class vec3 {
private:
  std::array<double, 3> e_;

public:
  vec3() : e_{0, 0, 0} {}

  vec3(double x, double y, double z) : e_{x, y, z} {}

  double x() const { return e_[0]; }
  double y() const { return e_[1]; }
  double z() const { return e_[2]; }

  vec3 operator-() const { return vec3(-e_[0], -e_[1], -e_[3]); }

  vec3 &operator+=(const vec3 &other) {
    e_[0] += other.e_[0];
    e_[1] += other.e_[1];
    e_[2] += other.e_[2];
    return *this;
  }

  vec3 &operator*=(const vec3 &other) {
    e_[0] *= other.e_[0];
    e_[1] *= other.e_[1];
    e_[2] *= other.e_[2];
    return *this;
  }

  vec3 &operator*=(double t) { return *this *= vec3(t, t, t); }

  vec3 &operator/=(double t) { return *this *= 1 / t; }

  double length() const { return std::sqrt(lengthSquared()); }

  double lengthSquared() const {
    return e_[0] * e_[0] + e_[1] * e_[1] + e_[2] * e_[2];
  }

  static vec3 random() {
    return vec3(randomDouble(), randomDouble(), randomDouble());
  }

  static vec3 random(double min, double max) {
    return vec3(randomDouble(min, max), randomDouble(min, max),
                randomDouble(min, max));
  }
};

using point3 = vec3;

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
  return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
  return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator*(double t, const vec3 &v) {
  return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator*(const vec3 &v, double t) { return t * v; }

inline vec3 operator/(const vec3 &v, double t) { return (1 / t) * v; }

inline double dot(const vec3 &u, const vec3 &v) {
  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(),
              u.x() * v.y() - u.y() * v.x());
}

inline vec3 unitVector(const vec3 &v) { return v / v.length(); }

inline vec3 randomUnitVector() {
  while (true) {
    auto p = vec3::random(-1, 1);
    auto lensq = p.lengthSquared();
    if (1e-160 < lensq && lensq <= 1) {
      return p / sqrt(lensq);
    }
  }
}

inline vec3 randomOnHemisphere(const vec3 &normal) {
  vec3 onUnitSphere = randomUnitVector();
  if (dot(onUnitSphere, normal) > 0.0) {
    return onUnitSphere;
  } // In the same hemisphere as the normal
  return -onUnitSphere;
}