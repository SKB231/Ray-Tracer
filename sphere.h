#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class sphere : public hittable
{
public:
    point3 center;
    double radius;

    sphere() {}
    sphere(point3 &cen, double rad)
    {
        center = cen;
        radius = rad;
    }

    virtual bool hit(const ray &r, const double t_min, const double t_max, hit_record &rec) const override;
};

bool sphere::hit(const ray &r, const double t_min, const double t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = (dot(r.direction(), oc));
    auto c = dot(oc, oc) - radius * radius;

    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

    auto sqrtd = sqrt(discriminant);

    // Find the root that lies in the accepted range of t to avoid situations such as rendering items at the back of the camera
    auto root = (-half_b - sqrt(discriminant)) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrt(discriminant)) / a;
        if (root < t_min || root > t_max)
        {
            return false;
        }
    }

    rec.p = r.at(root);
    rec.t = root;

    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    

    return true;
}

#endif