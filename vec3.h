#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

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

#endif