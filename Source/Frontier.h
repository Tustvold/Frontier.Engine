#pragma once
// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

// Include GLFW
#include <glfw3.h>

#include <stdarg.h>
#include <stdexcept>
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Util/FTLog.h>
#include <Util/FTAssert.h>


// Provide constructors for smart pointers which can infer the required type
// from the provided pointer
template <typename T>
std::unique_ptr<T> construct_unique(T* ptr) {
    return std::unique_ptr<T>(ptr);
}

template <typename T>
std::shared_ptr<T> construct_shared(T* ptr) {
    return std::shared_ptr<T>(ptr);
}

// MSVC doesn't appear to set __cplusplus correctly
#ifndef _MSC_VER
#if __cplusplus < 201402L
// no make_unique support
namespace std {
    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique(Args&& ...args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
#endif
#endif

// A number of functions (mainly those talking to OpenGL) assume that the glm vectors 
// are not padded. We make sure this assumption holds here
static_assert(sizeof(glm::vec2) == sizeof(GLfloat) * 2, "glm::vec2 has been padded by the compiler");
static_assert(sizeof(glm::vec3) == sizeof(GLfloat) * 3, "glm::vec3 has been padded by the compiler");
static_assert(sizeof(glm::vec4) == sizeof(GLfloat) * 4, "glm::vec4 has been padded by the compiler");

// Note there is a bug in VS which means that you can't use this on a templated struct
#if defined(_MSC_VER)
#define ALIGNED_(x) __declspec(align(x))
#else
#if defined(__GNUC__)
#define ALIGNED_(x) __attribute__ ((aligned(x)))
#endif
#endif
