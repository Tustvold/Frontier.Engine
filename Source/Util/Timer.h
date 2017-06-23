#pragma once

#include <GLFW/glfw3.h>

NS_FT_BEGIN

class Timer {
private:
    bool IsRunning;
    double Clock;
    double ElapsedSeconds;
public:
    Timer() : IsRunning(false), ElapsedSeconds(0) {
    }


    void Start() {
        IsRunning = true;
        Clock = glfwGetTime();
    }

    void Stop() {
        double end = glfwGetTime();
        ElapsedSeconds += double(end - Clock);
        IsRunning = false;
    }

    void Reset() {
        ElapsedSeconds = 0.0;
    }

    double GetElapsedSeconds() {
        return ElapsedSeconds;
    }
};

NS_FT_END