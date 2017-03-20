#pragma once

#include <glm/glm.hpp>

#define INT_TO_FVECTOR(a, b, c) (irr::f32)(a),(irr::f32)(b),(irr::f32)(c)

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2         1.57079632679489661923
#endif

#define FTMAX(a, b) ( (a > b) ? a : b )
#define FTMIN(a, b) ( (a < b) ? a : b )

// Maths utility functions
#define DEG2RAD 0.01745329251f
#define RAD2DEG 57.2957795131f

static inline glm::vec3 vec3xor(const glm::vec3 &av, const glm::vec3 &bv) {
    union converter {
        struct {
            float x;
            float y;
            float z;
        } f;
        struct {
            int32_t x;
            int32_t y;
            int32_t z;
        } i;
    };

    converter a, b, c;
    a.f.x = av.x;
    a.f.y = av.y;
    a.f.z = av.z;


    b.f.x = bv.x;
    b.f.y = bv.y;
    b.f.z = bv.z;

    c.i.x = a.i.x ^ b.i.x;
    c.i.y = a.i.y ^ b.i.y;
    c.i.z = a.i.z ^ b.i.z;
    return glm::vec3(c.f.x, c.f.y, c.f.z);
}
