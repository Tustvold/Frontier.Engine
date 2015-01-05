#pragma once

#include "FTObject.h"
#include <glfw3.h>

class FTTimer : public FTObject {
private:
	bool IsRunning;
	double Clock;
	double ElapsedSeconds;
public:
	FTTimer() : IsRunning(false), ElapsedSeconds(0) {
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
