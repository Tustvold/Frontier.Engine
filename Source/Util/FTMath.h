#pragma once

#include <glm/glm.hpp>

#define INT_TO_FVECTOR(a,b,c) (irr::f32)(a),(irr::f32)(b),(irr::f32)(c)

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2         1.57079632679489661923
#endif

#define FTMAX(a, b) ( (a > b) ? a : b )
#define FTMIN(a, b) ( (a < b) ? a : b )
#define FTABS(a) (((a)<0) ? -(a) : (a))
#define FTSGN(a) (((a)<0) ? -1 : (a)>0 ? 1 : 0)

// Maths utility functions
#define DEG2RAD 0.01745329251f
#define RAD2DEG 57.2957795131f

static inline float fastabs(float f) {
    int i = ((*(int*)&f) & 0x7fffffff);
    return (*(float*)&i);
}

static inline float fastneg(float f) {
    int i = ((*(int*)&f) ^ 0x80000000);
    return (*(float*)&i);
}

static inline int fastsgn(float f) {
    return 1 + (((*(int*)&f) >> 31) << 1);
}

// Roughly 2 times faster than the built in approach
static inline glm::vec4 fastabsvec4(const glm::vec4& vec) {
    return glm::vec4(fastabs(vec.x), fastabs(vec.y), fastabs(vec.z), fastabs(vec.w));
}

static inline glm::vec4 fastnegvec4(const glm::vec4& vec) {
    return glm::vec4(fastneg(vec.x), fastneg(vec.y), fastneg(vec.z), fastneg(vec.w));
}


static inline glm::vec3 vec3xor(const glm::vec3& av, const glm::vec3& bv) {
    int x = (*(int*)&(av.x)) ^ (*(int*)&(bv.x));
    int y = (*(int*)&(av.y)) ^ (*(int*)&(bv.y));
    int z = (*(int*)&(av.z)) ^ (*(int*)&(bv.z));
    return glm::vec3((*(float*)&x), (*(float*)&y), (*(float*)&z));
}
