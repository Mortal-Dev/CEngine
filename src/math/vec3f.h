#ifndef VEC3F_H
#define VEC3F_H

#include "vec3f.h"
#include <math.h>

typedef struct
{
    float x, y, z;
} Vec3f;

static inline Vec3f vec3f_add(const Vec3f a, const Vec3f b) 
{
    Vec3f result = { a.x + b.x, a.y + b.y, a.z + b.z };
    return result;
}

static inline Vec3f vec3f_sub(const Vec3f a, const Vec3f b) 
{
    Vec3f result = { a.x - b.x, a.y - b.y, a.z - b.z };
    return result;
}

// Multiply two vectors component-wise
static inline Vec3f vec3f_mul(const Vec3f a, const Vec3f b) 
{
    Vec3f result = { a.x * b.x, a.y * b.y, a.z * b.z };
    return result;
}

// Divide two vectors component-wise
static inline Vec3f vec3f_div(const Vec3f a, const Vec3f b) 
{
    Vec3f result = {
        b.x != 0.0f ? a.x / b.x : 0.0f,
        b.y != 0.0f ? a.y / b.y : 0.0f,
        b.z != 0.0f ? a.z / b.z : 0.0f
    };
    return result;
}

// Add vector components by scalar value
static inline Vec3f vec3f_add_scalar(const Vec3f v, const float s) 
{
    Vec3f result = { v.x + s, v.y + s, v.z + s };
    return result;
}

// Multiply vector components by scalar value
static inline Vec3f vec3f_mul_scalar(const Vec3f v, const float s) 
{
    Vec3f result = { v.x * s, v.y * s, v.z * s };
    return result;
}

static inline float vec3f_dot_product(const Vec3f a, const Vec3f b) 
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline Vec3f vec3f_normalized(const Vec3f a) 
{
    float length = sqrtf((a.x * a.x) + (a.y * a.y) + (a.z * a.z));

    Vec3f result = a;

    if (length != 0.0f) 
    {
        result.x /= length;
        result.y /= length;
        result.z /= length;
    }

    return result;
}

// Cross product of a × b
static inline Vec3f vec3f_crossed(const Vec3f a, const Vec3f b) 
{
    Vec3f result =
    {
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    };

    return result;
}

static inline void vec3f_print(const Vec3f a) 
{
    char vec_buf[256];

    sprintf_s(vec_buf, sizeof(vec_buf), "\n%f %f %f", a.x, a.y, a.z);

    log_info(vec_buf);
}


#endif