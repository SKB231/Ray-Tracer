#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include "rtweekend.h"

class vec3
{
public:
    double e[3];

    vec3()
    {
        e[0] = 0;
        e[1] = 0;
        e[2] = 0;
    }
    vec3(double e0, double e1, double e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    };

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    // Overload vector arethematic operations:

    // unary minus
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    // [] operator overload. Depending on how it's used the 1) or 2) overload is used.

    // 1) [] operator for read.
    double operator[](int i) const { return e[i]; }
    // 2) [] operator for read/write
    double &operator[](int i) { return e[i]; }

    vec3 &operator+=(const vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 &operator*=(const vec3 &v)
    {
        e[0] *= v.e[0];
        e[1] *= v.e[1];
        e[2] *= v.e[2];
        return *this;
    }

    vec3 &operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 &operator/=(const double t)
    {
        *this *= (1 / t);
        return *this;
    }

    double length_squared()
    {
        return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }

    double length()
    {
        return std::sqrt(length_squared());
    }

    inline static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    inline bool near_zero() const
    {
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }
};

// aliases:
using point3 = vec3;
using color = vec3;

// add
inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// subtract
inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// multiply
inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// scale
inline vec3 operator*(double t, const vec3 &v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

// scale
inline vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}

// divide
inline vec3 operator/(vec3 v, double t)
{
    return (1 / t) * v;
}

// dot
inline double dot(const vec3 &u, const vec3 &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// unit vec
inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

// cross product
inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// output
inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

/**
 * @brief We need a way to pick a random point in a unit radius sphere. We’ll use what is usually the easiest algorithm: a rejection method. First, pick a random point in the unit cube where x, y, and z all range from −1 to +1. Reject this point and try again if the point is outside the sphere.
 *
 */
vec3 random_in_unit_sphere()
{
    while (true)
    {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}

vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}

/**
 * @brief
 * Refraction is based on the following formula:
 * R'(perpendicular component) = (n / n') * (R + n(cosine_theta)); \n
 * R'(parallel component) = (-n) * (sqrt(1 - R'_perp_length_square)) \n
 *
 * R' = R_perp + R_parallel
 *
 * @param etai_over_etat Same as (n/n')
 * @param uv Ray direction of R
 * @param n Normal of the surface (opposite of the ray.)
 *
 */
vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat)
{
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);

    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

vec3 random_in_unit_disk()
{
    while (true)
    {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}

#endif