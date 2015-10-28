#pragma once

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
