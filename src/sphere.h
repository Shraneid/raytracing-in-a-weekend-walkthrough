#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable
{
public:
    sphere(point3 _center, double _radius) : center(_center), radius(_radius){};

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0)
            return false;
        auto sqrt_discriminant = sqrt(discriminant);

        auto root = (-half_b - sqrt_discriminant) / a;
        if (!ray_t.surrounds(root))
        {
            root = (-half_b + sqrt_discriminant) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.point_of_contact = r.at(rec.t);

        vec3 outward_normal = (rec.point_of_contact - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
};

#endif