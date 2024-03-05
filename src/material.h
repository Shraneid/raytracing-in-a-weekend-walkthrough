#ifndef MATERIAL_H
#define MATERIAL_H

#include "common.h"

class hit_record;

class material
{
public:
    virtual ~material() = default;

    virtual bool scatter(
        const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const = 0;
};

class lambertian : public material
{
public:
    lambertian(const color &a) : albedo(a) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered)
        const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.point_of_contact, scatter_direction);
        attenuation = albedo;

        return true;
    }

private:
    color albedo;
};

class metal : public material
{
public:
    metal(const color &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered_ray) const override
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);

        scattered_ray = ray(rec.point_of_contact, reflected + fuzz * (random_unit_vector()));
        attenuation = albedo;

        return dot(scattered_ray.direction(), rec.normal) > 0;
    }

private:
    color albedo;
    double fuzz;
};

class dielectric : public material
{
public:
    dielectric(double ri) : refraction_index(ri) {}

    bool scatter(const ray &in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        attenuation = color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0 / refraction_index) : refraction_index;

        vec3 unit_direction_vector = unit_vector(in.direction());

        auto cos_theta = fmin(dot(-unit_direction_vector, rec.normal), 1.0);
        auto sin_theta = sqrt(1 - cos_theta * cos_theta);

        vec3 out_vector;

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        bool schlick_reflect = reflectance(cos_theta, refraction_ratio) > random_double();

        if (cannot_refract || schlick_reflect)
        {
            // total internal reflection
            out_vector = reflect(unit_direction_vector, rec.normal);
        }
        else
        {
            // refraction
            out_vector = refract(unit_direction_vector, rec.normal, refraction_ratio);
        }

        scattered = ray(rec.point_of_contact, out_vector);
        return true;
    }

private:
    double refraction_index;

    // Using Schlick's approximation
    static double reflectance(double cosine, double refraction_ratio)
    {
        auto r0 = (1 - refraction_ratio) / (1 + refraction_ratio);
        r0 = pow(r0, 2);

        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};

#endif