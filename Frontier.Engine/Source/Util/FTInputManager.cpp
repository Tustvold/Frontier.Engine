#include "FTInputManager.h"
#include "Rendering/FTDirector.h"
#include "Frontier.h"


//Static Methods
bool FTInputManager::trust_mouse_ = false;

static bool s_initialised = false;
static FTInputManager* s_instance = nullptr;

FTInputManager* FTInputManager::getSharedInstance() {
	if (!s_initialised) {
		s_instance = new FTInputManager();
		s_initialised = true;
	}
	return s_instance;
}

FTInputManager::FTInputManager() {
	for (int i = 0; i < GLFW_KEY_LAST + 1; i++) {
		key_mappings_[i] = KeyNameOther;
	}

	for (int i = 0; i < KeyNameOther; i++) {
		key_down_[i] = false;
	}

	key_mappings_[GLFW_KEY_W] = KeyNameForward;
	key_mappings_[GLFW_KEY_S] = KeyNameBackward;
	key_mappings_[GLFW_KEY_A] = KeyNameLeft;
	key_mappings_[GLFW_KEY_D] = KeyNameRight;
	key_mappings_[GLFW_KEY_SPACE] = KeyNameUp;
	key_mappings_[GLFW_KEY_LEFT_SHIFT] = KeyNameDown;
	key_mappings_[GLFW_KEY_EQUAL] = KeyNameFreezeFrustrum;

	FTDirector* director = FTDirector::getSharedInstance();
	director->getPreDrawEventHandler()->Connect(this, &FTInputManager::update);
}

void FTInputManager::keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods) {
	s_instance->keyCallback(window, key, scancode, action, mods); // If this method is being called s_instance has been initialized
}

void FTInputManager::cursorPosCallbackStatic(GLFWwindow* window, double x, double y) {
	s_instance->cursorPosCallback(window, x, y); // If this method is being called s_instance has been initialized
}

void FTInputManager::cursorEnterCallback(GLFWwindow* window, int entered) {
	trust_mouse_ = false; //Otherwise when the mouse cursor re-enters we get a massive delta
}

//Non-Static Methods

void FTInputManager::registerWithWindow(GLFWwindow* window) {
	window_ = window;
	glfwSetKeyCallback(window, &keyCallbackStatic);
	glfwSetCursorPosCallback(window, &cursorPosCallbackStatic);
	glfwSetCursorEnterCallback(window, &cursorEnterCallback);
}


void FTInputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_UNKNOWN || action == GLFW_REPEAT)
		return;

	KeyName name = key_mappings_[key];
	if (name == KeyNameOther)
		return;
	button_pressed_event_handler_(name, (KeyState)action);
	key_down_[name] = action == GLFW_PRESS;
}

void FTInputManager::cursorPosCallback(GLFWwindow* window, double x, double y) {
	glm::vec2 screensize = FTDirector::getSharedInstance()->getWindowSize();


	float delta_x = (float)(x - screensize.x / 2.0f);
	float delta_y = (float)(screensize.y / 2.0f - y); // Change coords to be centred in the bottom left not top left

	if (trust_mouse_)
		cursor_pos_update_event_handler_(delta_x, delta_y);
	glfwSetCursorPos(window_, screensize.x / 2.0f, screensize.y / 2.0f);
	trust_mouse_ = true;
}
