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



static void FTLog(const char* format, ...) {
    va_list args;
    va_start(args, format);

    FTLogPrint("Info: ", format, args);

    va_end(args);
}

static void FTLogWarn(const char* format, ...) {
    va_list args;
    va_start(args, format);

    FTLogPrint("Warning: ", format, args);

    va_end(args);
}

static void FTLogError(const char* format, ...) {
    va_list args;
    va_start(args, format);

    FTLogPrint("Error: ", format, args);

    va_end(args);
}

class FTException : public std::exception {
public:
    explicit FTException(const char* message) : msg_(message) {

    }

    virtual ~FTException() throw () {
    }

    virtual const char* what() const throw () {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

static void FTAssert(bool value, const char* format, ...) {
    if (value)
        return;
    va_list args;
    va_start(args, format);
    FTLogPrint("Fatal: ", format, args);

    va_end(args);
    throw FTException("Uncaught FTException");
}

#define FTLOG(...) FTLog(__VA_ARGS__)

// A number of functions (mainly those talking to OpenGL) assumes that the glm vectors 
// are not padded. We make sure this assumption holds here
static_assert(sizeof(glm::vec2) == sizeof(GLfloat) * 2, "glm::vec2 has been padded by the compiler");
static_assert(sizeof(glm::vec3) == sizeof(GLfloat) * 3, "glm::vec3 has been padded by the compiler");
static_assert(sizeof(glm::vec4) == sizeof(GLfloat) * 4, "glm::vec4 has been padded by the compiler");

#if defined(_MSC_VER)
#define ALIGNED_(x) __declspec(align(x))
#else
#if defined(__GNUC__)
#define ALIGNED_(x) __attribute__ ((aligned(x)))
#endif
#endif