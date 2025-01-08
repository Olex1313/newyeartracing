#pragma once

#include "hittable.hpp"

class sphere : public hittable {
public:
  sphere(const point3 &center, double radius, std::shared_ptr<material> mat)
      : center_(center), radius_(std::fmax(0, radius)), mat_(mat) {
    // FIXME: add material pointer
  }

  bool hit(const ray &r, interval rayT, hitRecord &rec) const override {
    vec3 oc = center_ - r.origin();
    auto a = r.direction().lengthSquared();
    auto h = dot(r.direction(), oc);
    auto c = oc.lengthSquared() - radius_ * radius_;

    auto discriminant = h * h - a * c;
    if (discriminant < 0) {
      return false;
    }

    auto sqrtd = std::sqrt(discriminant);
    auto root = (h - sqrtd) / a;
    if (!rayT.surrounds(root)) {
      root = (h + sqrtd) / a;
      if (!rayT.surrounds(root)) {
        return false;
      }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outwardNormal = (rec.p - center_) / radius_;
    rec.setFaceNormal(r, outwardNormal);
    rec.mat = mat_;

    return true;
  }

private:
  point3 center_;
  double radius_;
  std::shared_ptr<material> mat_;
};
