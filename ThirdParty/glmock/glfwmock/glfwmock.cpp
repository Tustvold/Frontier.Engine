#include "glfwmock.h"
#include <GLFW/glfw3.h>

GlfwMock::GlfwMock() {

}

GlfwMock::~GlfwMock() {

}

GlfwMock* GlfwMock::getMock() {
    return (GlfwMock*)IGLMock::getMock();
}


int glfwInit(void) {
    return 0;
}

void glfwTerminate(void) {
    
}

void glfwGetVersion(int* major, int* minor, int* rev) {
}

const char* glfwGetVersionString(void) {
    return 0;
}

GLFWerrorfun glfwSetErrorCallback(GLFWerrorfun cbfun) {
    return 0;
}

GLFWmonitor** glfwGetMonitors(int* count) {
    return 0;
}

GLFWmonitor* glfwGetPrimaryMonitor(void) {
    return 0;
}

void glfwGetMonitorPos(GLFWmonitor* monitor, int* xpos, int* ypos) {
    
}

void glfwGetMonitorPhysicalSize(GLFWmonitor* monitor, int* widthMM, int* heightMM) {
    
}

const char* glfwGetMonitorName(GLFWmonitor* monitor) {
    return 0;
}

GLFWmonitorfun glfwSetMonitorCallback(GLFWmonitorfun cbfun) {
    return 0;
}

const GLFWvidmode* glfwGetVideoModes(GLFWmonitor* monitor, int* count) {
    return 0;
}

const GLFWvidmode* glfwGetVideoMode(GLFWmonitor* monitor) {
    return 0;
}

void glfwSetGamma(GLFWmonitor* monitor, float gamma) {
    
}

const GLFWgammaramp* glfwGetGammaRamp(GLFWmonitor* monitor) {
    return 0;
}

void glfwSetGammaRamp(GLFWmonitor* monitor, const GLFWgammaramp* ramp) {
    
}

void glfwDefaultWindowHints(void) {
    
}

void glfwWindowHint(int target, int hint) {
    
}

GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
    return 0;
}

void glfwDestroyWindow(GLFWwindow* window) {
    
}

int glfwWindowShouldClose(GLFWwindow* window) {
    return 0;
}

void glfwSetWindowShouldClose(GLFWwindow* window, int value) {
    
}

void glfwSetWindowTitle(GLFWwindow* window, const char* title) {
    
}

void glfwGetWindowPos(GLFWwindow* window, int* xpos, int* ypos) {
    
}

void glfwSetWindowPos(GLFWwindow* window, int xpos, int ypos) {
    
}

void glfwGetWindowSize(GLFWwindow* window, int* width, int* height) {
    
}

void glfwSetWindowSize(GLFWwindow* window, int width, int height) {
    
}

void glfwGetFramebufferSize(GLFWwindow* window, int* width, int* height) {
    
}

void glfwGetWindowFrameSize(GLFWwindow* window, int* left, int* top, int* right, int* bottom) {
    
}

void glfwIconifyWindow(GLFWwindow* window) {
    
}

void glfwRestoreWindow(GLFWwindow* window) {
    
}

void glfwShowWindow(GLFWwindow* window) {
    
}

void glfwHideWindow(GLFWwindow* window) {
    
}

GLFWmonitor* glfwGetWindowMonitor(GLFWwindow* window) {
    return 0;
}

int glfwGetWindowAttrib(GLFWwindow* window, int attrib) {
    return 0;
}

void glfwSetWindowUserPointer(GLFWwindow* window, void* pointer) {
    
}

void* glfwGetWindowUserPointer(GLFWwindow* window) {
    return 0;
}

GLFWwindowposfun glfwSetWindowPosCallback(GLFWwindow* window, GLFWwindowposfun cbfun) {
    return GlfwMock::getMock()->window_pos_callback_ = cbfun;
}

GLFWwindowsizefun glfwSetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun cbfun) {
    return GlfwMock::getMock()->window_size_callback_ = cbfun;
}

GLFWwindowclosefun glfwSetWindowCloseCallback(GLFWwindow* window, GLFWwindowclosefun cbfun) {
    return GlfwMock::getMock()->window_close_callback_ = cbfun;
}

GLFWwindowrefreshfun glfwSetWindowRefreshCallback(GLFWwindow* window, GLFWwindowrefreshfun cbfun) {
    return GlfwMock::getMock()->window_refresh_callback_ = cbfun;
}

GLFWwindowfocusfun glfwSetWindowFocusCallback(GLFWwindow* window, GLFWwindowfocusfun cbfun) {
    return GlfwMock::getMock()->window_focus_callback_ = cbfun;
}

GLFWwindowiconifyfun glfwSetWindowIconifyCallback(GLFWwindow* window, GLFWwindowiconifyfun cbfun) {
    return GlfwMock::getMock()->window_iconify_callback_ = cbfun;
}

GLFWframebuffersizefun glfwSetFramebufferSizeCallback(GLFWwindow* window, GLFWframebuffersizefun cbfun) {
    return GlfwMock::getMock()->window_set_frame_buffer_size_callback_ = cbfun;
}

void glfwPollEvents(void) {
    
}

void glfwWaitEvents(void) {
    
}

void glfwPostEmptyEvent(void) {
    
}

int glfwGetInputMode(GLFWwindow* window, int mode) {
    return 0;
}

void glfwSetInputMode(GLFWwindow* window, int mode, int value) {
    
}

int glfwGetKey(GLFWwindow* window, int key) {
    return 0;
}

int glfwGetMouseButton(GLFWwindow* window, int button) {
    return 0;
}

void glfwGetCursorPos(GLFWwindow* window, double* xpos, double* ypos) {
    
}

void glfwSetCursorPos(GLFWwindow* window, double xpos, double ypos) {
    
}

GLFWcursor* glfwCreateCursor(const GLFWimage* image, int xhot, int yhot) {
    return 0;
}

GLFWcursor* glfwCreateStandardCursor(int shape) {
    return 0;
}

void glfwDestroyCursor(GLFWcursor* cursor) {
    
}

void glfwSetCursor(GLFWwindow* window, GLFWcursor* cursor) {
    
}

GLFWkeyfun glfwSetKeyCallback(GLFWwindow* window, GLFWkeyfun cbfun) {
    return GlfwMock::getMock()->key_callback_ = cbfun;
}

GLFWcharfun glfwSetCharCallback(GLFWwindow* window, GLFWcharfun cbfun) {
    return GlfwMock::getMock()->char_callback_ = cbfun;
}

GLFWcharmodsfun glfwSetCharModsCallback(GLFWwindow* window, GLFWcharmodsfun cbfun) {
    return GlfwMock::getMock()->char_mods_callback_ = cbfun;
}

GLFWmousebuttonfun glfwSetMouseButtonCallback(GLFWwindow* window, GLFWmousebuttonfun cbfun) {
    return GlfwMock::getMock()->mouse_button_callback_ = cbfun;
}

GLFWcursorposfun glfwSetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun cbfun) {
    return GlfwMock::getMock()->mouse_pos_callback_ = cbfun;
}

GLFWcursorenterfun glfwSetCursorEnterCallback(GLFWwindow* window, GLFWcursorenterfun cbfun) {
    return GlfwMock::getMock()->mouse_enter_callback_ = cbfun;
}

GLFWscrollfun glfwSetScrollCallback(GLFWwindow* window, GLFWscrollfun cbfun) {
    return GlfwMock::getMock()->mouse_scroll_callback_ = cbfun;
}

GLFWdropfun glfwSetDropCallback(GLFWwindow* window, GLFWdropfun cbfun) {
    return GlfwMock::getMock()->drop_callback_ = cbfun;
}

int glfwJoystickPresent(int joy) {
    return 0;
}

const float* glfwGetJoystickAxes(int joy, int* count) {
    return 0;
}

const unsigned char* glfwGetJoystickButtons(int joy, int* count) {
    return 0;
}

const char* glfwGetJoystickName(int joy) {
    return 0;
}

void glfwSetClipboardString(GLFWwindow* window, const char* string) {
    
}

const char* glfwGetClipboardString(GLFWwindow* window) {
    return 0;
}

double glfwGetTime(void) {
    return 0;
}

void glfwSetTime(double time) {
    
}

void glfwMakeContextCurrent(GLFWwindow* window) {
    
}

GLFWwindow* glfwGetCurrentContext(void) {
    return 0;
}

void glfwSwapBuffers(GLFWwindow* window) {
    
}

void glfwSwapInterval(int interval) {
    
}

int glfwExtensionSupported(const char* extension) {
    return 0;
}

GLFWglproc glfwGetProcAddress(const char* procname) {
    return 0;
}