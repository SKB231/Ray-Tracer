#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record
{
    point3 p;
    vec3 normal;
    double t;

    bool front_face;

    // r: the ray
    // outward_normal: The sphere's outward normal from the center point
    inline void set_face_normal(const ray &r, const vec3 &outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0; // if dot product is -ve then ray and outward normal are on opposite sides
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
public:
    virtual bool hit(const ray &r, const double t_min, const double t_max, hit_record &rec) const = 0;
};

#endif