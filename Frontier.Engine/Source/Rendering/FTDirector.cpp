#include "FTDirector.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>

// Include GLFW
#include <glfw3.h>
#include <Util/FTInputManager.h>

#include <Rendering/Shader/FTShaderCache.h>
#include <Rendering/Textures/FTTexture.h>
#include "Shader/FTVertexColorShaderProgram.h"
#include "Shader/FTVertexTextureShaderProgram.h"
#include "Shader/FTFontShader.h"
#include "Text/FTFontCache.h"

FTDirector* FTDirector::getSharedInstance() {
	static FTDirector* instance = new FTDirector();
	return instance;
}

FTDirector::FTDirector() : scene_(nullptr) {
}


FTDirector::~FTDirector() {
	FTLOG("Director destroyed");
	if (scene_ != nullptr)
		scene_->release();
}

int FTDirector::setup() {
	// Setup Graphics
	if (!glfwInit()) {
		FTLOG( "Failed to initialize GLFW\n");
		return -1;
	}

	window_size_ = glm::vec2(1024, 768);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window_ = glfwCreateWindow((int)window_size_.x, (int)window_size_.y, "FPS:", nullptr, nullptr);
	if (window_ == nullptr) {
		FTLogError("Failed to open GLFW window. Most likely your system doesn't support OpenGL version 3.3");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window_);

	glfwSwapInterval(0);

	glewExperimental = true;

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	loadDefaultShaderPrograms();
	loadDefaultFonts();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//Setup Misc
	glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowSizeCallback(window_, &windowSizeChangeCallback);
	FTInputManager::getSharedInstance()->registerWithWindow(window_);
	return 0;
}

void FTDirector::loadDefaultShaderPrograms() {
	FTShaderCache* shaderCache = FTShaderCache::getSharedInstance();

	FTShaderProgram* shader = new FTVertexColorShaderProgram();
	shaderCache->loadShaderProgram(shader);
	shader->release();

	shader = new FTVertexTextureShaderProgram();
	shaderCache->loadShaderProgram(shader);
	shader->release();

	shader = new FTFontShader();
	shaderCache->loadShaderProgram(shader);
	shader->release();
}

void FTDirector::loadDefaultFonts() {
	FTFontCache* fontCache = FTFontCache::getSharedInstance();

	fontCache->loadFont("Fonts/Vera.ttf");
}


int FTDirector::run() {

	float fps = 60;
	float fps_time_acc = 0;
	last_tick_time_ = glfwGetTime();

	do {
		double current_time = glfwGetTime();
		float dt = (float)(current_time - last_tick_time_);
		last_tick_time_ = current_time;
		if (dt > 0) {
			fps = 0.1f * fps + 0.9f / dt;
			fps_time_acc += dt;
		}

		if (fps_time_acc > 1.0f) {
			fps_time_acc -= 1.0f;

			std::ostringstream ss;
			ss << "FPS: " << fps;
			glfwSetWindowTitle(window_, ss.str().c_str());
		}

		pre_draw_event_handler_(dt);

		// clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene_->draw();

		// Swap buffers
		glfwSwapBuffers(window_);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window_, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window_) == 0);

	FTShaderCache::getSharedInstance()->unloadAllShaders();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();


	return 0;
}

void FTDirector::windowSizeChange(GLFWwindow* window, int width, int height) {
	//FTLOG("Window size change");
	glViewport(0, 0, width, height);
	window_size_.x = (float)width;
	window_size_.y = (float)height;
	window_size_change_event_handler_((float)width, (float)height);
}
