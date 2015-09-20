#pragma once
// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>

// Include GLFW
#include <glfw3.h>

#include <stdarg.h>
#include <stdexcept>
#include <memory>
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
