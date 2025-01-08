#pragma once

#include "hittable.hpp"

class material {
public:
  virtual ~material() = default;

  virtual bool scatter(const ray &r, const hitRecord &hitRec,
                       color &attenuation, ray &scattered) const {
    return false;
  }
};

class lambertian : public material {
public:
  lambertian(const color &albedo) : albedo_(albedo) {}

  bool scatter(const ray &r, const hitRecord &rec, color &attenuation,
               ray &scattered) const override {
    auto scatterDirection = rec.normal + randomUnitVector();

    if (scatterDirection.nearZero()) {
      scatterDirection = rec.normal;
    }

    scattered = ray(rec.p, scatterDirection);
    attenuation = albedo_;
    return true;
  }

private:
  color albedo_;
};

class metal : public material {
public:
  metal(const color &albedo) : albedo_(albedo) {}

  bool scatter(const ray &r, const hitRecord &rec, color &attenuation,
               ray &scattered) const override {
    auto reflected = reflect(r.direction(), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo_;
    return true;
  }

private:
  color albedo_;
};