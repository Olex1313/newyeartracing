#pragma once

#include <memory>
#include <vector>

#include "ray.hpp"

struct hitRecord {
  point3 p;
  vec3 normal;
  double t;
  bool frontFace;

  void setFaceNormal(const ray &r, const vec3 &outwardNormal) {
    frontFace = dot(r.direction(), outwardNormal) < 0;
    normal = frontFace ? outwardNormal : -outwardNormal;
  }
};

class hittable {
public:
  virtual ~hittable() = default;

  virtual bool hit(const ray &r, double rayTmin, double rayTmax,
                   hitRecord &rec) const = 0;
};

class hittableList : public hittable {
public:
  std::vector<std::shared_ptr<hittable>> objects_;

  hittableList() = default;

  hittableList(std::shared_ptr<hittable> obj) : objects_{obj} {}

  void clear() { objects_.clear(); }

  void add(std::shared_ptr<hittable> obj) { objects_.push_back(obj); }

  bool hit(const ray &r, double rayTmin, double rayTmax,
           hitRecord &rec) const override {
    hitRecord hitRec;
    bool hitAnything = false;
    auto closestHit = rayTmax;

    for (const auto &obj : objects_) {
      if (obj->hit(r, rayTmin, closestHit, hitRec)) {
        hitAnything = true;
        closestHit = hitRec.t;
        rec = hitRec;
      }
    }

    return hitAnything;
  }
};
