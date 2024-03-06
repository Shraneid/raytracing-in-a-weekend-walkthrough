#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3
{
public:
    double e[3];

    vec3() : e{0, 0, 0} {}
    vec3(double x, double y, double z) : e{x, y, z} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double &operator[](int i) { return e[i]; }

    vec3 &operator+=(const vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 &operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 &operator/=(double t)
    {
        return *this *= 1 / t;
    }

    double length() const
    {
        return sqrt(length_squared());
    }

    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    bool near_zero() const
    {
        auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

using point3 = vec3;

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline vec3 operator*(double t, const vec3 &u)
{
    return vec3(u[0] * t, u[1] * t, u[2] * t);
}

inline vec3 operator*(const vec3 &u, double t)
{
    return t * u;
}

inline vec3 operator/(const vec3 &u, double t)
{
    return (1 / t) * u;
}

inline double dot(const vec3 &u, const vec3 &v)
{
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0]);
}

inline vec3 unit_vector(const vec3 &u)
{
    return u / u.length();
}

inline vec3 random_in_unit_disk()
{
    while (true)
    {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() < 1)
        {
            return p;
        }
    }
}

// TODO:
// not sure if this is really needed ? if it is I don't understand yet why.
// I think it is to have a perfect distribution, whereas not having it
// would generate a vector in the unit cube and therefore having a bias towards the corners.
// same thing in random unit disk above which made me realize this
// Will have to check later on in the project but since we take the unit vector
// in the end, then I don't really see the point. For now, it doesn't seem to affect the rendering
inline vec3 random_in_unit_sphere()
{
    while (true)
    {
        auto v = vec3::random(-1, 1);
        if (v.length_squared() < 1)
        {
            return v;
        }
    }
}

inline vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3 &normal)
{
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0)
    {
        return on_unit_sphere;
    }
    else
    {
        return -on_unit_sphere;
    }
}

inline vec3 reflect(const vec3 &v, const vec3 &normal)
{
    return v - 2 * dot(v, normal) * normal;
}

inline vec3 refract(const vec3 &unit_direction_vector, const vec3 &normal, const double &etai_over_etat)
{
    auto cos_theta = fmin(dot(-unit_direction_vector, normal), 1.0);

    vec3 refracted_perpendicular = etai_over_etat * (unit_direction_vector + cos_theta * normal);
    vec3 refracted_parallel = -sqrt(fabs(1 - refracted_perpendicular.length_squared())) * normal;

    return refracted_parallel + refracted_perpendicular;
}

#endif
