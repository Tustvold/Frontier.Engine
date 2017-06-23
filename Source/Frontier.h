#pragma once
// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

// Include GLFW
#include <GLFW/glfw3.h>

#include <stdarg.h>
#include <stdexcept>
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Util/FTLog.h>

class FTException : public std::exception {
public:
    explicit FTException(const char* message) : msg_(message) {

    }

    virtual ~FTException() throw () {
    }

    virtual const char* what() const throw () override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

#define FTAssert(value, ...) if (!(value)) { \
    FTLogPrint("", false, "Assertion failed with error: "); \
    FTLogPrint("", false, __VA_ARGS__); \
    FTLogPrint("", true, " at %s:%i",__FILE__, __LINE__); \
    throw FTException("Failed FTAssert"); \
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

#define NS_FT_BEGIN namespace frontier {
#define NS_FT_END }
#define USING_NS_FT using namespace frontier;